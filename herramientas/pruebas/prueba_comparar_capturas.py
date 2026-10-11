#!/usr/bin/env python3
"""herramientas/emulador/comparar_capturas.py con TGA sintéticos.

Las capturas del job 'emulador' son TGA sin comprimir de 32 bits (BGRA) con
el origen abajo a la izquierda. La comparación mira solo el RGB: un píxel
cuenta como distinto si algún canal se aparta más que el umbral, y la
captura falla si la fracción de píxeles distintos pasa de la tolerancia.
Una captura uniforme (toda de un color) falla siempre: es la que deja una
lectura del GS que no llegó a hacerse.
"""
import os
import struct
import sys
import tempfile

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "emulador"))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import comparar_capturas as cc  # noqa: E402
import png_simple  # noqa: E402

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def tga(ancho, alto, filas_rgb, bits=32, arriba=False):
    """TGA tipo 2 a partir de filas RGB de arriba abajo."""
    cabecera = struct.pack("<BBBHHBHHHHBB", 0, 0, 2, 0, 0, 0, 0, 0, ancho, alto, bits,
                           (8 if bits == 32 else 0) | (0x20 if arriba else 0))
    filas = filas_rgb if arriba else list(reversed(filas_rgb))
    cuerpo = bytearray()
    for fila in filas:
        for r, g, b in fila:
            cuerpo += bytes((b, g, r)) + (b"\x80" if bits == 32 else b"")
    return cabecera + bytes(cuerpo)


def degradado(ancho, alto):
    return [[(x * 16 % 256, y * 32 % 256, (x + y) * 8 % 256) for x in range(ancho)] for y in range(alto)]


def plano(filas):
    return bytes(c for fila in filas for p in fila for c in p)


def main():
    filas = degradado(10, 4)

    # Lectura: orientación y profundidad
    for bits in (24, 32):
        for arriba in (False, True):
            img = cc.leer_tga(tga(10, 4, filas, bits, arriba))
            comprobar((img.ancho, img.alto, img.tipo) == (10, 4, "rgb"),
                      "TGA %d bits arriba=%s: tamaño o tipo" % (bits, arriba))
            comprobar(img.pixeles == plano(filas), "TGA %d bits arriba=%s: píxeles" % (bits, arriba))
    for malo in (b"", tga(2, 2, degradado(2, 2))[:-1], b"\x00\x00\x0a" + tga(2, 2, degradado(2, 2))[3:]):
        try:
            cc.leer_tga(malo)
            comprobar(False, "un TGA corto o comprimido se rechaza")
        except ValueError:
            comprobar(True, "")

    # Uniformidad: un solo píxel distinto ya no es uniforme; el alfa no cuenta
    negro = [[(0, 0, 0)] * 10 for _ in range(4)]
    comprobar(cc.es_uniforme(cc.leer_tga(tga(10, 4, negro))), "negra es uniforme")
    casi = [fila[:] for fila in negro]
    casi[3][9] = (0, 0, 1)
    comprobar(not cc.es_uniforme(cc.leer_tga(tga(10, 4, casi))), "un píxel distinto no es uniforme")

    # Fracción de píxeles distintos y umbral por canal
    a = cc.leer_tga(tga(10, 4, filas))
    b_filas = [fila[:] for fila in filas]
    r, g, bl = b_filas[0][0]
    b_filas[0][0] = ((r + 20) % 256, g, bl)
    b_filas[1][1] = (b_filas[1][1][0], b_filas[1][1][1], (b_filas[1][1][2] + 21) % 256)
    b = cc.leer_tga(tga(10, 4, b_filas))
    comprobar(cc.fraccion_distinta(a, a, 20) == 0.0, "igual a sí misma")
    comprobar(cc.fraccion_distinta(a, b, 20) == 1 / 40, "umbral 20: solo cuenta el canal que se aparta 21")
    comprobar(cc.fraccion_distinta(a, b, 19) == 2 / 40, "umbral 19: cuentan los dos")

    # Comparación de carpetas: tolerancia en el límite y uno por encima
    with tempfile.TemporaryDirectory() as tmp:
        capturas = os.path.join(tmp, "capturas")
        referencias = os.path.join(tmp, "referencias")
        os.makedirs(capturas)
        os.makedirs(referencias)
        png_simple.escribir(os.path.join(referencias, "menu.png"), a)
        with open(os.path.join(capturas, "menu.tga"), "wb") as f:
            f.write(tga(10, 4, b_filas))
        comprobar(cc.comparar(capturas, referencias, 1 / 40, 20) == [], "en la tolerancia pasa")
        errores = cc.comparar(capturas, referencias, 1 / 40, 19)
        comprobar(len(errores) == 1 and "menu" in errores[0], "por encima de la tolerancia falla: %r" % errores)

        # Uniforme, falta o de otro tamaño: falla aunque la referencia también lo sea
        png_simple.escribir(os.path.join(referencias, "negra.png"), cc.leer_tga(tga(10, 4, negro)))
        with open(os.path.join(capturas, "negra.tga"), "wb") as f:
            f.write(tga(10, 4, negro))
        png_simple.escribir(os.path.join(referencias, "falta.png"), a)
        png_simple.escribir(os.path.join(referencias, "chica.png"), cc.leer_tga(tga(5, 4, degradado(5, 4))))
        with open(os.path.join(capturas, "chica.tga"), "wb") as f:
            f.write(tga(10, 4, filas))
        errores = cc.comparar(capturas, referencias, 1.0, 255)
        for nombre in ("negra", "falta", "chica"):
            comprobar(sum(nombre in e for e in errores) == 1, "%s da un error: %r" % (nombre, errores))
        comprobar(len(errores) == 3, "menu sigue pasando con tolerancia 1: %r" % errores)

        # Sin referencias no hay nada que comparar: es un error, no un verde
        vacia = os.path.join(tmp, "vacia")
        os.makedirs(vacia)
        comprobar(cc.comparar(capturas, vacia, 1.0, 255) != [], "sin referencias falla")

    print("%d comprobaciones, %d %s" % (comprobaciones, fallos, "fallo" if fallos == 1 else "fallos"))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
