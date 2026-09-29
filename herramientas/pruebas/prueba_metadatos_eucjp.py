#!/usr/bin/env python3
"""Los metadatos de pistas que usan los fuentes con texto tienen que llegar en EUC-JP.

    prueba_metadatos_eucjp.py <copia convertida.c> -- <opciones del compilador>

Pide al gcc del PC las dependencias de la copia convertida, con las mismas
rutas de busqueda que usa el build, y comprueba que cada metadato de pista
se resuelve a su copia convertida (build/ps2/jp/...) y no al original en UTF-8.
"""
import subprocess
import sys

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def dependencias(archivo, opciones):
    r = subprocess.run(["gcc", "-MM", "-MG", "-D_LANGUAGE_C", "-DTARGET_PS2=1"] + opciones + [archivo],
                       capture_output=True, text=True)
    comprobar(r.returncode == 0, "gcc -MM fallo: %s" % r.stderr.strip())
    return r.stdout.replace("\\\n", " ").split()[1:]


def main():
    if "--" not in sys.argv or sys.argv.index("--") != 2:
        sys.exit(__doc__)
    copia = sys.argv[1]
    opciones = sys.argv[3:]
    copias_jp = copia[: copia.index("/jp/") + len("/jp/")]
    metadatos = [d for d in dependencias(copia, opciones) if "pistas/metadatos/" in d]
    comprobar(len(metadatos) >= 5, "se esperaban los metadatos de pistas, hay %d" % len(metadatos))
    for dep in metadatos:
        comprobar(dep.startswith(copias_jp), "%s se incluye sin convertir a EUC-JP" % dep)
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
