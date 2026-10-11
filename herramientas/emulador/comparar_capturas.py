#!/usr/bin/env python3
"""Compara las capturas del job 'emulador' con las referencias aprobadas.

Uso: comparar_capturas.py <capturas> <referencias> [--tolerancia F] [--umbral N]
     comparar_capturas.py --generar <capturas> <referencias>

Cada referencias/<nombre>.png pide capturas/<nombre>.tga, el TGA sin
comprimir que deja la orden 'captura' del guion. Solo cuenta el RGB: el alfa
del framebuffer no se ve en pantalla. Un píxel es distinto si algún canal se
aparta más de --umbral; la captura falla si la fracción de píxeles distintos
pasa de --tolerancia, si falta, si cambia de tamaño o si es uniforme (una
lectura del GS que no se hizo deja la imagen de un solo color).
--generar escribe las referencias a partir de las capturas.
"""
import argparse
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
import png_simple  # noqa: E402

TOLERANCIA = 0.02
UMBRAL = 24


def leer_tga(datos):
    """Imagen RGB de arriba abajo a partir de un TGA tipo 2 de 24 o 32 bits."""
    if len(datos) < 18:
        raise ValueError("TGA demasiado corto")
    (largo_id, mapa, tipo, _, _, _, _, _, ancho, alto, bits, descriptor) = struct.unpack(
        "<BBBHHBHHHHBB", datos[:18])
    if tipo != 2 or mapa != 0 or bits not in (24, 32):
        raise ValueError("TGA no soportado: tipo %d, %d bits" % (tipo, bits))
    paso = bits // 8
    inicio = 18 + largo_id
    if len(datos) < inicio + ancho * alto * paso:
        raise ValueError("TGA truncado")
    filas = []
    for y in range(alto):
        fila = bytearray(ancho * 3)
        base = inicio + y * ancho * paso
        fila[0::3] = datos[base + 2:base + ancho * paso:paso]
        fila[1::3] = datos[base + 1:base + ancho * paso:paso]
        fila[2::3] = datos[base:base + ancho * paso:paso]
        filas.append(bytes(fila))
    if not descriptor & 0x20:  # origen abajo a la izquierda
        filas.reverse()
    return png_simple.Imagen(ancho, alto, "rgb", b"".join(filas))


def es_uniforme(img):
    return img.pixeles == img.pixeles[:3] * (img.ancho * img.alto)


def fraccion_distinta(a, b, umbral):
    distintos = 0
    pa, pb = a.pixeles, b.pixeles
    for i in range(0, len(pa), 3):
        if (abs(pa[i] - pb[i]) > umbral or abs(pa[i + 1] - pb[i + 1]) > umbral
                or abs(pa[i + 2] - pb[i + 2]) > umbral):
            distintos += 1
    return distintos / (a.ancho * a.alto)


def comparar(capturas, referencias, tolerancia, umbral):
    """Lista de errores (vacía si todas las capturas pasan)."""
    nombres = sorted(n[:-4] for n in os.listdir(referencias) if n.endswith(".png"))
    if not nombres:
        return ["no hay referencias en %s" % referencias]
    errores = []
    for nombre in nombres:
        ruta = os.path.join(capturas, nombre + ".tga")
        if not os.path.exists(ruta):
            errores.append("%s: falta la captura %s" % (nombre, ruta))
            continue
        with open(ruta, "rb") as f:
            cap = leer_tga(f.read())
        ref = png_simple.leer(os.path.join(referencias, nombre + ".png"))
        if ref.tipo != "rgb":
            errores.append("%s: la referencia no es RGB" % nombre)
        elif es_uniforme(cap):
            errores.append("%s: la captura es uniforme" % nombre)
        elif (cap.ancho, cap.alto) != (ref.ancho, ref.alto):
            errores.append("%s: %dx%d frente a %dx%d de la referencia"
                           % (nombre, cap.ancho, cap.alto, ref.ancho, ref.alto))
        else:
            fraccion = fraccion_distinta(cap, ref, umbral)
            print("%s: %.4f %% de píxeles distintos" % (nombre, fraccion * 100))
            if fraccion > tolerancia:
                errores.append("%s: %.4f %% de píxeles distintos, tolerancia %.4f %%"
                               % (nombre, fraccion * 100, tolerancia * 100))
    return errores


def main():
    p = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    p.add_argument("capturas")
    p.add_argument("referencias")
    p.add_argument("--tolerancia", type=float, default=TOLERANCIA)
    p.add_argument("--umbral", type=int, default=UMBRAL)
    p.add_argument("--generar", action="store_true")
    args = p.parse_args()
    if args.generar:
        for n in sorted(os.listdir(args.capturas)):
            if n.endswith(".tga"):
                with open(os.path.join(args.capturas, n), "rb") as f:
                    png_simple.escribir(os.path.join(args.referencias, n[:-4] + ".png"), leer_tga(f.read()))
        return 0
    errores = comparar(args.capturas, args.referencias, args.tolerancia, args.umbral)
    for e in errores:
        print("FALLO " + e)
    return 1 if errores else 0


if __name__ == "__main__":
    sys.exit(main())
