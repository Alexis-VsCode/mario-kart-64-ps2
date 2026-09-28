#!/usr/bin/env python3
"""Texturas con texto en espanol: exportar, importar, comprobar y hoja de contacto.

    texturas_es.py exportar [--manifiesto M] [--salida CARPETA] [--tkmk00 HERRAMIENTA]
    texturas_es.py importar <id>.<formato>.png <salida.bin>
    texturas_es.py comprobar [--manifiesto M] [--tkmk00 HERRAMIENTA] <id>.<formato>.png [...]
    texturas_es.py hoja <original.png> <nuevo.png> <salida.png>

El manifiesto (recursos/es/texturas.tsv) tiene una fila por textura
revisada: id, origen, formato, alfa (opaco o clave_00BE), texto_es,
retocado (si/no) y motivo_no (por que no se traduce). Los PNG se llaman
<id>.<formato>.png: importar saca el formato del sufijo y rechaza lo que
no se pueda guardar sin perdida.
"""
import argparse
import os
import subprocess
import sys
import tempfile

import formatos_textura as ft
import png_simple

RAIZ = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
MANIFIESTO = os.path.join(RAIZ, "recursos", "es", "texturas.tsv")
TKMK00 = os.path.join(RAIZ, "build", "herramientas", "tkmk00")
ORIGINALES = os.path.join(RAIZ, "build", "ps2", "es", "originales")
COLUMNAS = ["id", "origen", "formato", "alfa", "texto_es", "retocado", "motivo_no"]
# Alfa con el que el juego decodifica el TKMK00 (TexturaMenu type 1 -> 0xBE)
ALFA_TKMK00 = {"opaco": "0x01", "clave_00BE": "0xBE"}
CLAVE = 0x00BE
ESCALA = 3
SEPARACION = 4


class ErrorManifiesto(ValueError):
    pass


def leer_manifiesto(ruta):
    """Lista de filas (dict por columna)."""
    with open(ruta, encoding="utf-8") as f:
        lineas = f.read().splitlines()
    if not lineas or lineas[0].split("\t") != COLUMNAS:
        raise ErrorManifiesto("%s: la cabecera tiene que ser: %s" % (ruta, " ".join(COLUMNAS)))
    filas = []
    for numero, linea in enumerate(lineas[1:], 2):
        campos = linea.split("\t")
        if len(campos) != len(COLUMNAS):
            raise ErrorManifiesto("%s:%d: %d columnas, se esperaban %d" % (ruta, numero, len(campos), len(COLUMNAS)))
        fila = dict(zip(COLUMNAS, campos))
        if fila["formato"] not in ft.FORMATOS or fila["alfa"] not in ALFA_TKMK00 or fila["retocado"] not in ("si", "no"):
            raise ErrorManifiesto("%s:%d: formato, alfa o retocado invalido" % (ruta, numero))
        filas.append(fila)
    ids = [f["id"] for f in filas]
    if len(set(ids)) != len(ids):
        raise ErrorManifiesto("%s: ids repetidos" % ruta)
    return filas


def decodificar_original(fila, tkmk00):
    """(bytes, ancho, alto) de la textura original tal como la usa el juego."""
    origen = os.path.join(RAIZ, fila["origen"])
    if not origen.endswith(".tkmk00"):
        raise ErrorManifiesto("%s: origen %s todavia no soportado" % (fila["id"], fila["origen"]))
    with open(origen, "rb") as f:
        cabecera = f.read(12)
    ancho, alto = int.from_bytes(cabecera[8:10], "big"), int.from_bytes(cabecera[10:12], "big")
    with tempfile.TemporaryDirectory() as tmp:
        salida = os.path.join(tmp, "textura.bin")
        r = subprocess.run([tkmk00, "-a", ALFA_TKMK00[fila["alfa"]], origen, salida], capture_output=True, text=True)
        if r.returncode != 0:
            raise ErrorManifiesto("%s: tkmk00 fallo: %s" % (fila["id"], r.stderr.strip()))
        with open(salida, "rb") as f:
            return f.read(), ancho, alto


def partes_nombre(ruta):
    """(id, formato) de <id>.<formato>.png"""
    partes = os.path.basename(ruta).split(".")
    if len(partes) != 3 or partes[2] != "png" or partes[1] not in ft.FORMATOS:
        raise ErrorManifiesto("%s: el nombre tiene que ser <id>.<formato>.png" % ruta)
    return partes[0], partes[1]


def exportar(args):
    filas = leer_manifiesto(args.manifiesto)
    os.makedirs(args.salida, exist_ok=True)
    for fila in filas:
        datos, ancho, alto = decodificar_original(fila, args.tkmk00)
        imagen = ft.a_imagen(fila["formato"], datos, ancho, alto)
        png_simple.escribir(os.path.join(args.salida, "%s.%s.png" % (fila["id"], fila["formato"])), imagen)
    print("texturas_es: %d texturas en %s" % (len(filas), args.salida))
    return 0


def convertir(ruta):
    _, formato = partes_nombre(ruta)
    if formato == "ci8":
        raise ErrorManifiesto("%s: ci8 necesita su paleta; importar no lo soporta" % ruta)
    return ft.de_imagen(formato, png_simple.leer(ruta))


def importar(args):
    datos = convertir(args.png)
    temporal = args.salida + ".tmp"
    with open(temporal, "wb") as f:
        f.write(datos)
    os.replace(temporal, args.salida)
    return 0


def problemas(ruta, filas, tkmk00):
    """Lista de motivos por los que el PNG no puede reemplazar a su original."""
    id_, formato = partes_nombre(ruta)
    fila = next((f for f in filas if f["id"] == id_), None)
    if fila is None:
        return ["%s no esta en el manifiesto" % id_]
    if formato != fila["formato"]:
        return ["formato %s, el manifiesto dice %s" % (formato, fila["formato"])]
    _, ancho, alto = decodificar_original(fila, tkmk00)
    imagen = png_simple.leer(ruta)
    if (imagen.ancho, imagen.alto) != (ancho, alto):
        return ["mide %dx%d, la original %dx%d" % (imagen.ancho, imagen.alto, ancho, alto)]
    datos = ft.de_imagen(formato, imagen)
    if formato == "rgba16":
        transparentes = {(datos[i] << 8) | datos[i + 1] for i in range(0, len(datos), 2) if not datos[i + 1] & 1}
        if fila["alfa"] == "opaco" and transparentes:
            return ["tiene pixeles transparentes y la original es opaca"]
        if fila["alfa"] == "clave_00BE" and transparentes - {CLAVE}:
            return ["hay transparentes con un color distinto de la clave 0x00BE"]
    return []


def comprobar(args):
    filas = leer_manifiesto(args.manifiesto)
    malos = 0
    for ruta in args.pngs:
        try:
            lista = problemas(ruta, filas, args.tkmk00)
        except (ErrorManifiesto, ft.ErrorFormato, png_simple.ErrorPng) as e:
            lista = [str(e)]
        for motivo in lista:
            print("FALLO %s: %s" % (ruta, motivo))
        malos += bool(lista)
    print("texturas_es: %d comprobadas, %d con problemas" % (len(args.pngs), malos))
    return 1 if malos else 0


def pixel_hoja(p, x, y):
    """RGB de un pixel sobre fondo a cuadros (para ver los transparentes)."""
    fondo = 200 if (x // 6 + y // 6) % 2 else 150
    return bytes((c * p[3] + fondo * (255 - p[3])) // 255 for c in p[:3])


def hoja(args):
    original, nuevo = png_simple.leer(args.original), png_simple.leer(args.nuevo)
    if (original.ancho, original.alto) != (nuevo.ancho, nuevo.alto):
        raise ErrorManifiesto("tamanios distintos: %dx%d y %dx%d" % (original.ancho, original.alto, nuevo.ancho,
                                                                     nuevo.alto))
    a, b = original.a_rgba(), nuevo.a_rgba()
    mascara = [(255, 0, 0, 255) if p != q else (0, 0, 0, 255) for p, q in zip(a, b)]
    ancho, alto = original.ancho * ESCALA, original.alto * ESCALA
    salida = bytearray()
    for y in range(alto):
        for panel, pixeles in enumerate((a, b, mascara)):
            if panel:
                salida += b"\xff" * 3 * SEPARACION
            for x in range(ancho):
                salida += pixel_hoja(pixeles[(y // ESCALA) * original.ancho + x // ESCALA], x, y)
    png_simple.escribir(args.salida, png_simple.Imagen(3 * ancho + 2 * SEPARACION, alto, "rgb", salida))
    print("texturas_es: %d pixeles distintos" % sum(p != q for p, q in zip(a, b)))
    return 0


def main(argv=None):
    parser = argparse.ArgumentParser(description="Texturas con texto en espanol")
    sub = parser.add_subparsers(dest="orden", required=True)
    p = sub.add_parser("exportar", help="originales del manifiesto a PNG")
    p.add_argument("--manifiesto", default=MANIFIESTO)
    p.add_argument("--salida", default=ORIGINALES)
    p.add_argument("--tkmk00", default=TKMK00)
    p.set_defaults(funcion=exportar)
    p = sub.add_parser("importar", help="PNG a binario, sin perdida")
    p.add_argument("png")
    p.add_argument("salida")
    p.set_defaults(funcion=importar)
    p = sub.add_parser("comprobar", help="el PNG puede reemplazar a su original")
    p.add_argument("--manifiesto", default=MANIFIESTO)
    p.add_argument("--tkmk00", default=TKMK00)
    p.add_argument("pngs", nargs="+")
    p.set_defaults(funcion=comprobar)
    p = sub.add_parser("hoja", help="hoja de contacto: original, nuevo y diferencias")
    p.add_argument("original")
    p.add_argument("nuevo")
    p.add_argument("salida")
    p.set_defaults(funcion=hoja)
    args = parser.parse_args(argv)
    try:
        return args.funcion(args)
    except (ErrorManifiesto, ft.ErrorFormato, png_simple.ErrorPng, OSError) as e:
        print("texturas_es: error: %s" % e, file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
