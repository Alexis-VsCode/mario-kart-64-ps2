#!/usr/bin/env python3
"""Pruebas del lector y escritor de PNG de 8 bits (herramientas/png_simple.py).

    prueba_png_simple.py

Ida y vuelta en los 5 tipos de color, los 5 filtros al leer (con un
codificador de referencia propio de la prueba), los rechazos y la salida
determinista.
"""
import os
import struct
import sys
import tempfile
import zlib

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))

import png_simple  # noqa: E402

fallos = 0
comprobaciones = 0

FIRMA = b"\x89PNG\r\n\x1a\n"
TIPOS = {"gris": 0, "rgb": 2, "indexado": 3, "gris_alfa": 4, "rgba": 6}
CANALES = {"gris": 1, "rgb": 3, "indexado": 1, "gris_alfa": 2, "rgba": 4}


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def falla(funcion, *args):
    """True si la llamada lanza png_simple.ErrorPng."""
    try:
        funcion(*args)
    except png_simple.ErrorPng:
        return True
    return False


def muestras(ancho, alto, canales, semilla):
    """Datos de prueba deterministas con bordes y saltos grandes."""
    return bytes((x * 37 + y * 101 + c * 59 + semilla * 13 + (x * y) % 7) & 0xFF
                 for y in range(alto) for x in range(ancho) for c in range(canales))


def paleta(n):
    return [((i * 5) & 0xFF, (i * 11 + 3) & 0xFF, (255 - i) & 0xFF, 255 if i % 3 else (i * 7) & 0xFF) for i in range(n)]


def trozo(tipo, datos):
    return struct.pack(">I", len(datos)) + tipo + datos + struct.pack(">I", zlib.crc32(tipo + datos) & 0xFFFFFFFF)


def ihdr(ancho, alto, bits, tipo_color, entrelazado=0):
    return trozo(b"IHDR", struct.pack(">IIBBBBB", ancho, alto, bits, tipo_color, 0, 0, entrelazado))


def paeth(a, b, c):
    p = a + b - c
    pa, pb, pc = abs(p - a), abs(p - b), abs(p - c)
    if pa <= pb and pa <= pc:
        return a
    return b if pb <= pc else c


def filtrar(filas, bpp, filtros):
    """Codificador de referencia: aplica a cada fila el filtro indicado."""
    salida = bytearray()
    previa = bytes(len(filas[0]))
    for fila, f in zip(filas, filtros):
        salida.append(f)
        for i, x in enumerate(fila):
            a = fila[i - bpp] if i >= bpp else 0
            b = previa[i]
            c = previa[i - bpp] if i >= bpp else 0
            prediccion = (0, a, b, (a + b) // 2, paeth(a, b, c))[f]
            salida.append((x - prediccion) & 0xFF)
        previa = fila
    return bytes(salida)


def png_a_mano(ancho, alto, tipo, pixeles, filtros, trozos_extra=b"", partir_idat=False):
    canales = CANALES[tipo]
    fila = ancho * canales
    filas = [pixeles[y * fila:(y + 1) * fila] for y in range(alto)]
    comprimido = zlib.compress(filtrar(filas, canales, filtros))
    idat = trozo(b"IDAT", comprimido)
    if partir_idat:
        mitad = len(comprimido) // 2
        idat = trozo(b"IDAT", comprimido[:mitad]) + trozo(b"IDAT", comprimido[mitad:])
    return FIRMA + ihdr(ancho, alto, 8, TIPOS[tipo]) + trozos_extra + idat + trozo(b"IEND", b"")


def trozos(datos):
    """Lista de (tipo, contenido, crc_valido) de un PNG."""
    lista, i = [], len(FIRMA)
    while i < len(datos):
        n = struct.unpack(">I", datos[i:i + 4])[0]
        tipo, contenido = datos[i + 4:i + 8], datos[i + 8:i + 8 + n]
        crc = struct.unpack(">I", datos[i + 8 + n:i + 12 + n])[0]
        lista.append((tipo, contenido, crc == zlib.crc32(tipo + contenido) & 0xFFFFFFFF))
        i += 12 + n
    return lista


def probar_ida_y_vuelta():
    """Paso 1: los 5 tipos salen iguales despues de escribir y leer."""
    for semilla, tipo in enumerate(sorted(TIPOS)):
        ancho, alto = 13, 7
        pal = paleta(200) if tipo == "indexado" else None
        pix = muestras(ancho, alto, CANALES[tipo], semilla)
        if tipo == "indexado":
            pix = bytes(p % 200 for p in pix)
        img = png_simple.Imagen(ancho, alto, tipo, pix, pal)
        datos = png_simple.codificar(img)
        comprobar(datos.startswith(FIRMA), "%s: falta la firma PNG" % tipo)
        otra = png_simple.decodificar(datos)
        comprobar((otra.ancho, otra.alto, otra.tipo) == (ancho, alto, tipo),
                  "%s: cabecera %r" % (tipo, (otra.ancho, otra.alto, otra.tipo)))
        comprobar(otra.pixeles == pix, "%s: los pixeles cambiaron" % tipo)
        comprobar(otra.paleta == pal, "%s: la paleta cambio" % tipo)


def probar_filtros():
    """Paso 2: cada filtro (y una mezcla por fila) se deshace bien, con 1 a 4 canales."""
    for tipo in ("gris", "gris_alfa", "rgb", "rgba"):
        ancho, alto = 9, 6
        pix = muestras(ancho, alto, CANALES[tipo], 3)
        for f in range(5):
            img = png_simple.decodificar(png_a_mano(ancho, alto, tipo, pix, [f] * alto))
            comprobar(img.pixeles == pix, "%s: filtro %d mal deshecho" % (tipo, f))
        mezcla = [4, 3, 2, 1, 0, 4]
        img = png_simple.decodificar(png_a_mano(ancho, alto, tipo, pix, mezcla, partir_idat=True))
        comprobar(img.pixeles == pix, "%s: filtros mezclados o IDAT partido mal leidos" % tipo)


def probar_trozos():
    """Paso 3: tRNS corto, trozos auxiliares ignorados y CRC comprobado."""
    ancho, alto = 4, 2
    pix = bytes(range(8))
    plte = trozo(b"PLTE", bytes(v for i in range(8) for v in (i, i * 2, i * 3)))
    trns = trozo(b"tRNS", bytes([0, 128]))
    texto = trozo(b"tEXt", b"Comment\x00prueba")
    datos = png_a_mano(ancho, alto, "indexado", pix, [0, 0], plte + trns + texto)
    img = png_simple.decodificar(datos)
    esperada = [(i, i * 2, i * 3, (0, 128)[i] if i < 2 else 255) for i in range(8)]
    comprobar(img.paleta == esperada, "tRNS corto: paleta %r" % img.paleta)
    comprobar(img.a_rgba()[1] == esperada[1], "a_rgba del indexado: %r" % (img.a_rgba()[1],))
    roto = bytearray(datos)
    roto[datos.index(b"tEXt") + 4] ^= 0x20
    comprobar(falla(png_simple.decodificar, bytes(roto)), "un CRC malo tiene que fallar")
    gris = png_simple.Imagen(2, 1, "gris_alfa", bytes([10, 20, 30, 40]))
    comprobar(gris.a_rgba() == [(10, 10, 10, 20), (30, 30, 30, 40)], "a_rgba de gris_alfa: %r" % gris.a_rgba())


def probar_rechazos():
    """Paso 4: 16 bits, menos de 8 bits, entrelazado y datos que no son PNG."""
    idat = trozo(b"IDAT", zlib.compress(bytes(8))) + trozo(b"IEND", b"")
    comprobar(falla(png_simple.decodificar, FIRMA + ihdr(2, 2, 16, 0) + idat), "16 bits tiene que fallar")
    comprobar(falla(png_simple.decodificar, FIRMA + ihdr(2, 2, 16, 6) + idat), "RGBA de 16 bits tiene que fallar")
    comprobar(falla(png_simple.decodificar, FIRMA + ihdr(2, 2, 4, 3) + idat), "indexado de 4 bits tiene que fallar")
    comprobar(falla(png_simple.decodificar, FIRMA + ihdr(2, 2, 8, 0, 1) + idat), "entrelazado tiene que fallar")
    comprobar(falla(png_simple.decodificar, b"GIF89a" + bytes(40)), "sin firma PNG tiene que fallar")
    corto = png_a_mano(3, 3, "gris", bytes(9), [0, 0, 0])
    comprobar(falla(png_simple.decodificar, corto[:len(corto) - 20]), "un PNG cortado tiene que fallar")
    comprobar(falla(png_simple.codificar, png_simple.Imagen(2, 2, "rgb", bytes(5))), "pixeles de menos al escribir")
    comprobar(falla(png_simple.codificar, png_simple.Imagen(1, 1, "indexado", bytes(1), [])), "indice fuera de paleta")


def probar_determinismo():
    """Paso 5: misma entrada, mismos bytes; sin tIME; tRNS solo si hace falta."""
    img = png_simple.Imagen(5, 3, "indexado", bytes(range(15)), paleta(16))
    a, b = png_simple.codificar(img), png_simple.codificar(img)
    comprobar(a == b, "dos escrituras iguales tienen que dar los mismos bytes")
    lista = trozos(a)
    tipos = [t for t, _, _ in lista]
    comprobar(tipos == [b"IHDR", b"PLTE", b"tRNS", b"IDAT", b"IEND"], "trozos del indexado: %r" % tipos)
    comprobar(all(ok for _, _, ok in lista), "CRC mal escrito")
    comprobar(b"tIME" not in a, "no tiene que llevar tIME")
    opaca = png_simple.Imagen(2, 1, "indexado", bytes([0, 1]), [(1, 2, 3, 255), (4, 5, 6, 255)])
    tipos = [t for t, _, _ in trozos(png_simple.codificar(opaca))]
    comprobar(b"tRNS" not in tipos, "una paleta opaca no lleva tRNS")
    with tempfile.TemporaryDirectory() as tmp:
        ruta = os.path.join(tmp, "prueba.png")
        png_simple.escribir(ruta, img)
        comprobar(open(ruta, "rb").read() == a, "escribir() tiene que guardar lo mismo que codificar()")
        comprobar(png_simple.leer(ruta).pixeles == img.pixeles, "leer() de un archivo")


def main():
    probar_ida_y_vuelta()
    probar_filtros()
    probar_trozos()
    probar_rechazos()
    probar_determinismo()
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
