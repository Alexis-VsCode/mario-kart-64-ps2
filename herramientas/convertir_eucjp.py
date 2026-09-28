#!/usr/bin/env python3
"""Pasa un fuente de UTF-8 a EUC-JP, la codificacion que espera la fuente del juego.

    convertir_eucjp.py <entrada> <salida>

Da los mismos bytes que 'iconv -f UTF-8 -t EUC-JP', pero no depende del iconv
del sistema: el de musl (imagen de ps2dev) no tiene JIS X 0212, que es donde
EUC-JP guarda las letras con tilde, la enie, la dieresis y los signos de
apertura. Un caracter que EUC-JP no puede representar corta el build con su
posicion en lugar de convertirse en basura.
"""
import os
import sys


def ubicar(texto, indice):
    """Linea y columna (desde 1) de un indice del texto."""
    linea = texto.count("\n", 0, indice) + 1
    columna = indice - (texto.rfind("\n", 0, indice) + 1) + 1
    return linea, columna


def convertir(ruta):
    """Devuelve los bytes en EUC-JP o lanza ValueError con un mensaje legible."""
    datos = open(ruta, "rb").read()
    try:
        texto = datos.decode("utf-8")
    except UnicodeDecodeError as e:
        raise ValueError("%s: byte %d: no es UTF-8" % (ruta, e.start))
    try:
        return texto.encode("euc_jp")
    except UnicodeEncodeError as e:
        linea, columna = ubicar(texto, e.start)
        caracter = texto[e.start]
        raise ValueError("%s:%d:%d: '%s' (U+%04X) no existe en EUC-JP" % (ruta, linea, columna, caracter, ord(caracter)))


def main():
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    entrada, salida = sys.argv[1:]
    try:
        datos = convertir(entrada)
    except ValueError as e:
        sys.exit("error: %s" % e)
    temporal = salida + ".tmp"
    with open(temporal, "wb") as f:
        f.write(datos)
    os.replace(temporal, salida)


if __name__ == "__main__":
    main()
