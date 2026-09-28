#!/usr/bin/env python3
"""La herramienta tkmk00 del PC decodifica las texturas de menu como el juego.

    prueba_tkmk00.py <herramienta tkmk00>

Para cada una de recursos/texturas/menus/tkmk00 comprueba que su alfa en
referencias_tkmk00.txt corresponde al type de la TexturaMenu que la usa
(1 -> 0xBE, 0 -> 0x01), y que la herramienta da w*h*2 bytes con la SHA-1
fijada con el decodificador original.
"""
import hashlib
import os
import re
import subprocess
import sys
import tempfile

RAIZ = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
CARPETA = os.path.join(RAIZ, "recursos", "texturas", "menus", "tkmk00")
REFERENCIAS = os.path.join(RAIZ, "herramientas", "pruebas", "referencias_tkmk00.txt")
LISTA_S = os.path.join(RAIZ, "codigo", "datos", "texturas_tkmk00.s")
TABLAS = [os.path.join(RAIZ, "codigo", "datos", "texturas", n)
          for n in ("fuentes_y_menus.inc.c", "vistas_previas_pistas.inc.c")]

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def leer_referencias():
    """{archivo: (ancho, alto, alfa, sha1)}"""
    refs = {}
    for linea in open(REFERENCIAS):
        if linea.strip() and not linea.startswith("#"):
            nombre, ancho, alto, alfa, sha1 = linea.split()
            refs[nombre] = (int(ancho), int(alto), int(alfa, 16), sha1)
    return refs


def tipos_texturas_menu():
    """{archivo: conjunto de types de las TexturaMenu que lo usan}"""
    simbolos = re.findall(r'glabel\s+(\w+)\s*\n\s*\.incbin\s+"([^"]+\.tkmk00)"', open(LISTA_S).read())
    archivo = {s: os.path.basename(r) for s, r in simbolos}
    tipos = {}
    for tabla in TABLAS:
        for tipo, simbolo in re.findall(r"\{\s*(\d+),\s*(\w+),", open(tabla).read()):
            if simbolo in archivo:
                tipos.setdefault(archivo[simbolo], set()).add(int(tipo))
    return tipos


def decodificar(herramienta, ruta, alfa, salida):
    args = [herramienta] + (["-a", "0x%X" % alfa] if alfa is not None else []) + [ruta, salida]
    r = subprocess.run(args, capture_output=True, text=True)
    comprobar(r.returncode == 0, "%s: tkmk00 fallo: %s" % (os.path.basename(ruta), r.stderr.strip()))
    return open(salida, "rb").read() if r.returncode == 0 else b""


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    herramienta = sys.argv[1]
    refs = leer_referencias()
    tipos = tipos_texturas_menu()
    archivos = sorted(n for n in os.listdir(CARPETA) if n.endswith(".tkmk00"))
    comprobar(len(archivos) == 63, "se esperaban 63 texturas TKMK00, hay %d" % len(archivos))
    comprobar(sorted(refs) == archivos, "referencias_tkmk00.txt no lista las mismas texturas que %s" % CARPETA)
    with tempfile.TemporaryDirectory() as tmp:
        salida = os.path.join(tmp, "salida.bin")
        for nombre in archivos:
            if nombre not in refs:
                continue
            ancho, alto, alfa, sha1 = refs[nombre]
            ruta = os.path.join(CARPETA, nombre)
            tipo = sorted(tipos.get(nombre, ()))
            esperado = {(1,): 0xBE, (0,): 0x01}.get(tuple(tipo))
            comprobar(alfa == esperado, "%s: alfa 0x%02X con TexturaMenu type %r" % (nombre, alfa, tipo))
            cabecera = open(ruta, "rb").read(12)
            comprobar((int.from_bytes(cabecera[8:10], "big"), int.from_bytes(cabecera[10:12], "big")) == (ancho, alto),
                      "%s: tamanio distinto de la cabecera" % nombre)
            datos = decodificar(herramienta, ruta, alfa, salida)
            comprobar(len(datos) == ancho * alto * 2, "%s: %d bytes, se esperaban %d" % (nombre, len(datos),
                                                                                      ancho * alto * 2))
            comprobar(hashlib.sha1(datos).hexdigest() == sha1, "%s: SHA-1 distinta de la referencia" % nombre)
        # Sin -a la herramienta usa 0x01, el alfa de las de type 0
        nombre = "seleccion_juego.rgba16.tkmk00"
        datos = decodificar(herramienta, os.path.join(CARPETA, nombre), None, salida)
        comprobar(hashlib.sha1(datos).hexdigest() == refs[nombre][3], "tkmk00 sin -a no usa el alfa 0x01")
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
