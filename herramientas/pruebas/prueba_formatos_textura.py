#!/usr/bin/env python3
"""Pruebas de la conversion entre bytes de textura N64 y pixeles.

    prueba_formatos_textura.py <herramienta mio0>

Cada formato va y vuelve sin perder nada (todos los valores posibles y
texturas reales), lo que no se puede representar se rechaza, los .inc.c
del repo se leen y se reescriben igual, y el MIO0 de Python da lo mismo
que 'mio0 -d'.
"""
import os
import re
import subprocess
import sys
import tempfile

RAIZ = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
sys.path.insert(0, os.path.join(RAIZ, "herramientas"))

import formatos_textura as ft  # noqa: E402
import png_simple  # noqa: E402

GENERALES = os.path.join(RAIZ, "recursos", "texturas", "generales")

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def falla(funcion, *args):
    try:
        funcion(*args)
    except ft.ErrorFormato:
        return True
    return False


def ida_y_vuelta(formato, datos, ancho, alto, tlut=None):
    """bytes -> Imagen -> PNG -> Imagen -> bytes."""
    img = ft.a_imagen(formato, datos, ancho, alto, tlut)
    img = png_simple.decodificar(png_simple.codificar(img))
    return ft.de_imagen(formato, img)


def probar_todos_los_valores():
    """Paso 1: cada formato conserva todos sus valores posibles."""
    u16 = bytes(v for i in range(65536) for v in (i >> 8, i & 0xFF))
    u8 = bytes(range(256))
    comprobar(ida_y_vuelta("rgba16", u16, 256, 256) == u16, "rgba16 pierde valores")
    comprobar(ida_y_vuelta("ia16", u16, 256, 256) == u16, "ia16 pierde valores")
    comprobar(ida_y_vuelta("ia8", u8, 16, 16) == u8, "ia8 pierde valores")
    comprobar(ida_y_vuelta("i8", u8, 16, 16) == u8, "i8 pierde valores")
    comprobar(ida_y_vuelta("i4", u8, 32, 16) == u8, "i4 pierde valores")
    tlut = bytes(v for i in range(256) for v in ((i * 0x9E37) >> 8 & 0xFF, (i * 0x9E37) & 0xFF))
    tlut = tlut[:40] + tlut[:40] + tlut[80:]
    indices, paleta = ida_y_vuelta("ci8", u8[::-1], 16, 16, tlut)
    comprobar(indices == u8[::-1] and paleta == tlut, "ci8 pierde indices o paleta (con colores repetidos)")


def probar_valores_concretos():
    """Paso 2: el significado de los bits (orden big-endian y expansion a 8 bits)."""
    rgba = ft.a_imagen("rgba16", bytes([0x00, 0xBE, 0xF8, 0x01]), 2, 1).a_rgba()
    comprobar(rgba == [(0, 16, 255, 0), (255, 0, 0, 255)], "rgba16 0x00BE 0xF801 -> %r" % rgba)
    ia = ft.a_imagen("ia16", bytes([0x12, 0x34]), 1, 1)
    comprobar((ia.tipo, ia.pixeles) == ("gris_alfa", bytes([0x12, 0x34])), "ia16 -> %r" % ia.pixeles)
    ia = ft.a_imagen("ia8", bytes([0x3C]), 1, 1)
    comprobar(ia.pixeles == bytes([0x33, 0xCC]), "ia8 0x3C -> %r" % ia.pixeles)
    i4 = ft.a_imagen("i4", bytes([0x1F]), 2, 1)
    comprobar((i4.tipo, i4.pixeles) == ("gris", bytes([0x11, 0xFF])), "i4 0x1F -> %r" % i4.pixeles)
    ci = ft.a_imagen("ci8", bytes([1, 0]), 2, 1, bytes([0x00, 0x00, 0xF8, 0x01]))
    comprobar(ci.tipo == "indexado" and ci.paleta == [(0, 0, 0, 0), (255, 0, 0, 255)], "ci8 paleta %r" % ci.paleta)


def probar_rechazos():
    """Paso 3: lo que el formato no puede guardar se rechaza, no se redondea."""
    def rgba(*pixeles):
        return png_simple.Imagen(len(pixeles), 1, "rgba", bytes(v for p in pixeles for v in p))
    comprobar(falla(ft.de_imagen, "rgba16", rgba((1, 0, 0, 255))), "rgba16 con rojo 1 (no es de 5 bits)")
    comprobar(falla(ft.de_imagen, "rgba16", rgba((0, 0, 0, 128))), "rgba16 con alfa 128")
    comprobar(falla(ft.de_imagen, "ia16", rgba((10, 11, 10, 255))), "ia16 con color")
    comprobar(falla(ft.de_imagen, "ia8", rgba((0x12, 0x12, 0x12, 255))), "ia8 con intensidad 0x12")
    comprobar(falla(ft.de_imagen, "i8", rgba((5, 5, 5, 0))), "i8 con transparencia")
    comprobar(falla(ft.de_imagen, "i4", rgba((0x10, 0x10, 0x10, 255), (0, 0, 0, 255))), "i4 con 0x10")
    comprobar(falla(ft.de_imagen, "i4", rgba((0, 0, 0, 255))), "i4 con un numero impar de pixeles")
    comprobar(falla(ft.de_imagen, "ci8", rgba((0, 0, 0, 255))), "ci8 sin paleta")
    comprobar(falla(ft.a_imagen, "rgba16", bytes(6), 2, 2), "rgba16 con bytes de menos")
    comprobar(falla(ft.a_imagen, "rgba32", bytes(4), 1, 1), "formato desconocido")
    comprobar(falla(ft.leer_inc_c, "0x12, 0x3456,\n"), ".inc.c con anchos mezclados")
    comprobar(falla(ft.leer_inc_c, "0x12, dato,\n"), ".inc.c con un identificador")
    comprobar(falla(ft.descomprimir_mio0, b"MIO1" + bytes(12)), "MIO0 sin firma")


def texturas_inc_c():
    for base, _, nombres in os.walk(os.path.join(RAIZ, "recursos")):
        for nombre in sorted(nombres):
            if re.search(r"\.(rgba16|ia16|ia8|i4|i8|ci8|tlut)\.inc\.c$", nombre):
                yield os.path.join(base, nombre)


def probar_inc_c():
    """Paso 4: los .inc.c de texturas del repo se leen y se reescriben igual."""
    total = iguales = 0
    for ruta in texturas_inc_c():
        texto = open(ruta).read()
        datos, ancho = ft.leer_inc_c(texto)
        otro = ft.escribir_inc_c(datos, ancho)
        total += 1
        comprobar(ft.leer_inc_c(otro) == (datos, ancho), "%s: la ida y vuelta cambia los datos" % ruta)
        if ", " in texto.split("\n", 1)[0]:
            iguales += 1
            comprobar(otro == texto, "%s: no se reescribe igual" % ruta)
    comprobar(total > 400 and iguales > 100, "se esperaban los .inc.c del repo: %d, %d" % (total, iguales))
    comprobar(ft.leer_inc_c("0x0001, 0xabcd,\n") == (bytes([0, 1, 0xAB, 0xCD]), 2), "u16 en big-endian")


def muestras_mio0():
    """Todos los formatos que no son rgba16 ni ia16, y uno de cada 40 del resto."""
    nombres = sorted(n for n in os.listdir(GENERALES) if n.endswith(".mio0"))
    comunes = [n for n in nombres if ".rgba16." in n or ".ia16." in n]
    return [n for n in nombres if n not in comunes] + comunes[::40]


def probar_mio0(herramienta):
    """Paso 5: el MIO0 de Python da lo mismo que la herramienta en C, y que el .inc.c."""
    nombres = muestras_mio0()
    comprobar(len(nombres) > 30, "se esperaban texturas MIO0 en %s" % GENERALES)
    pares = 0
    with tempfile.TemporaryDirectory() as tmp:
        salida = os.path.join(tmp, "salida.bin")
        for nombre in nombres:
            ruta = os.path.join(GENERALES, nombre)
            r = subprocess.run([herramienta, "-d", ruta, salida], capture_output=True)
            comprobar(r.returncode == 0, "%s: mio0 -d fallo" % nombre)
            datos = ft.descomprimir_mio0(open(ruta, "rb").read())
            comprobar(datos == open(salida, "rb").read(), "%s: distinto de mio0 -d" % nombre)
            inc = ruta[:-len(".mio0")] + ".inc.c"
            if os.path.exists(inc):
                pares += 1
                comprobar(ft.leer_inc_c(open(inc).read())[0] == datos, "%s: distinto de su .inc.c" % nombre)
            formato = nombre.split(".")[-2]
            if formato in ft.FORMATOS and formato != "ci8":
                n = len(datos) * 8 // ft.BITS[formato]
                comprobar(ida_y_vuelta(formato, datos, n, 1) == datos, "%s: ida y vuelta" % nombre)
    comprobar(pares > 3, "se esperaban pares .mio0/.inc.c, hay %d" % pares)


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    probar_todos_los_valores()
    probar_valores_concretos()
    probar_rechazos()
    probar_inc_c()
    probar_mio0(sys.argv[1])
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
