#!/usr/bin/env python3
"""Comprueba la regla del README: ningun archivo de codigo pasa de 1000 lineas.

    comprobar_lineas.py [raiz]

Revisa los .c, .h, .py y .sh de codigo/, incluir/ y herramientas/. Quedan
fuera los datos que no son codigo y la API original de libultra, que se
conserva tal cual.
"""
import fnmatch
import os
import sys

MAXIMO = 1000
CARPETAS = ("codigo", "incluir", "herramientas")
EXTENSIONES = (".c", ".h", ".py", ".sh")
EXCEPCIONES = (
    "incluir/libultra/*",                   # API de la N64 sin tocar
    "codigo/memoria/tablas_trigonometricas.c",  # tabla de datos
)


def archivos(raiz):
    for carpeta in CARPETAS:
        for base, _, nombres in os.walk(os.path.join(raiz, carpeta)):
            for nombre in nombres:
                if nombre.endswith(EXTENSIONES):
                    yield os.path.relpath(os.path.join(base, nombre), raiz).replace(os.sep, "/")


def excedidos(raiz):
    for ruta in sorted(archivos(raiz)):
        if any(fnmatch.fnmatch(ruta, e) for e in EXCEPCIONES):
            continue
        with open(os.path.join(raiz, ruta), "rb") as f:
            lineas = f.read().count(b"\n")
        if lineas > MAXIMO:
            yield ruta, lineas


def main():
    raiz = sys.argv[1] if len(sys.argv) > 1 else "."
    malos = list(excedidos(raiz))
    for ruta, lineas in malos:
        print("FALLO %s: %d lineas (maximo %d); lo que crece va a un archivo propio" % (ruta, lineas, MAXIMO))
    print("tope de lineas: %d archivos por encima" % len(malos))
    sys.exit(1 if malos else 0)


if __name__ == "__main__":
    main()
