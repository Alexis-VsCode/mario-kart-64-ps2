#!/usr/bin/env python3
"""El cartel de la granja (GRANJA / MU-MU) llega a la pista con su tamanio real.

    prueba_cartel_es.py <carpeta build>   (despues de 'make es')

texturas_dma copia el MIO0 de cada mitad con el tamanio comprimido que dice
recursos/pistas/moo_moo_farm/desplazamientos.c. Ese tamanio tiene que salir
de la cabecera que genera el build (TAMANIO_ES_*), no escrito a mano, y ser
el del .mio0 que incluye otras_texturas.s; el .mio0 da los pixeles del PNG.
"""
import os
import re
import sys

RAIZ = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
sys.path.insert(0, os.path.join(RAIZ, "herramientas"))

import formatos_textura as ft  # noqa: E402
import texturas_es  # noqa: E402

DESPLAZAMIENTOS = os.path.join(RAIZ, "recursos", "pistas", "moo_moo_farm", "desplazamientos.c")
LISTA_S = os.path.join(RAIZ, "codigo", "datos", "otras_texturas.s")
MITADES = {"izquierda": ("cartel_granja_izquierda", "GRANJA"), "derecha": ("cartel_granja_derecha", "MU-MU")}

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    build = sys.argv[1]
    filas = {f["id"]: f for f in texturas_es.leer_manifiesto(texturas_es.MANIFIESTO)}
    fuente = open(DESPLAZAMIENTOS).read()
    lista = open(LISTA_S).read()
    cabecera = os.path.join(build, "es", "tamanios_es.h")
    generados = dict(re.findall(r"#define\s+(TAMANIO_ES_\w+)\s+(0x[0-9A-Fa-f]+)", open(cabecera).read())) \
        if os.path.exists(cabecera) else {}
    comprobar('#include "es/tamanios_es.h"' in fuente, "desplazamientos.c no incluye es/tamanios_es.h")
    for lado, (id_, texto) in MITADES.items():
        fila = filas.get(id_, {})
        comprobar(fila.get("texto_es") == texto, "%s: se espera %s" % (id_, texto))
        png = fila.get("png", "")
        comprobar(png.startswith("recursos/es/mio0/"), "%s: el PNG va en recursos/es/mio0/" % id_)
        if not png:
            continue
        incbin = texturas_es.salida_build(png, "es")
        m = re.search(r"glabel textura_moo_moo_farm_%s_cartel\s*\n\.incbin \"([^\"]+)\"" % lado, lista)
        comprobar(m is not None and m.group(1) == incbin, "otras_texturas.s: la mitad %s no incluye %s" % (lado, incbin))
        macro = "TAMANIO_ES_" + id_.upper()
        m = re.search(r"\{\s*textura_moo_moo_farm_%s_cartel,\s*(\w+),\s*0x1000," % lado, fuente)
        comprobar(m is not None and m.group(1) == macro, "desplazamientos.c: la mitad %s no usa %s" % (lado, macro))
        ruta = texturas_es.salida_build(png, os.path.join(build, "es"))
        datos = open(ruta, "rb").read() if os.path.exists(ruta) else b""
        comprobar(datos[:4] == b"MIO0", "falta %s (make es)" % ruta)
        if not datos:
            continue
        comprobar(int(generados.get(macro, "0"), 16) == len(datos), "%s no es el tamanio de %s" % (macro, ruta))
        comprobar(ft.descomprimir_mio0(datos) == texturas_es.convertir(os.path.join(RAIZ, png)),
                  "%s: el .mio0 no da los pixeles del PNG" % id_)
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
