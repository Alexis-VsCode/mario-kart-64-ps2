#!/usr/bin/env python3
"""Comprueba en el PC que un refactor no cambia el codigo que ve el compilador.

    comparar_preprocesado.py <ref-antes> <ref-despues> <fuente.c> [<fuente.c> ...]

Para cada referencia de git (o '.' para el arbol actual) prepara una copia,
pasa a EUC-JP los fuentes con texto igual que el build y preprocesa cada
fuente con el gcc del PC y las opciones del Makefile. Compara los tokens:
si son los mismos, el binario de PS2 tambien lo es. No necesita el SDK de PS2;
la prueba definitiva sigue siendo comparar_binario.sh en CI.
"""
import os
import re
import shutil
import subprocess
import sys
import tempfile

TOKEN = re.compile(rb'[A-Za-z_]\w*|0[xX][0-9A-Fa-f]+|\d+\w*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|\S')


def git(*args, cwd=None):
    return subprocess.run(["git"] + list(args), cwd=cwd, check=True, capture_output=True, text=True).stdout


def variable_make(arbol, nombre):
    r = subprocess.run(["make", "-s", "PS2SDK=/nada", "print-" + nombre], cwd=arbol, capture_output=True, text=True)
    return r.stdout.split()


def preparar(ref, tmp):
    """Arbol de trabajo de la referencia ('.' = el actual)."""
    if ref == ".":
        return os.getcwd()
    destino = os.path.join(tmp, "arbol_" + re.sub(r"\W", "_", ref))
    git("worktree", "add", "--detach", destino, ref)
    return destino


def tokens(arbol, fuente, tmp):
    """Tokens del preprocesado de un fuente, convertido a EUC-JP si el build lo hace."""
    jp = os.path.join(tmp, "jp_" + re.sub(r"\W", "_", arbol))
    convertidos = variable_make(arbol, "JP_SRC") + variable_make(arbol, "JP_PARTES")
    for f in convertidos:
        salida = os.path.join(jp, f)
        os.makedirs(os.path.dirname(salida), exist_ok=True)
        subprocess.run([sys.executable, "herramientas/convertir_eucjp.py", f, salida], cwd=arbol, check=True)
    opciones = variable_make(arbol, "DEFINES") + variable_make(arbol, "INCLUDES")
    entrada = fuente
    if fuente in convertidos:
        entrada = os.path.join(jp, fuente)
        opciones += ["-iquote", os.path.dirname(fuente) + "/", "-iquote", jp]
    r = subprocess.run(["gcc", "-E", "-P", "-fsigned-char"] + opciones + [entrada], cwd=arbol, capture_output=True)
    if r.returncode != 0:
        sys.exit("%s: gcc -E fallo en %s:\n%s" % (fuente, arbol, r.stderr.decode(errors="replace")))
    return TOKEN.findall(r.stdout)


def main():
    if len(sys.argv) < 4:
        sys.exit(__doc__)
    antes, despues, fuentes = sys.argv[1], sys.argv[2], sys.argv[3:]
    tmp = tempfile.mkdtemp()
    arboles = []
    distintos = 0
    try:
        arboles = [preparar(antes, tmp), preparar(despues, tmp)]
        for fuente in fuentes:
            a, b = (tokens(arbol, fuente, tmp) for arbol in arboles)
            if a == b:
                print("igual     %s (%d tokens)" % (fuente, len(a)))
            else:
                i = next((i for i, (x, y) in enumerate(zip(a, b)) if x != y), min(len(a), len(b)))
                print("DISTINTO  %s en el token %d: %r / %r" % (fuente, i, b" ".join(a[i:i + 8]), b" ".join(b[i:i + 8])))
                distintos += 1
    finally:
        for arbol in arboles:
            if arbol.startswith(tmp):
                git("worktree", "remove", "--force", arbol)
        shutil.rmtree(tmp, ignore_errors=True)
    sys.exit(1 if distintos else 0)


if __name__ == "__main__":
    main()
