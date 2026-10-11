#!/usr/bin/env python3
"""Los carteles de pista en espanol llegan a la pista con su tamanio real: el de
la granja (GRANJA / MU-MU) y el de bienvenida de Banshee Boardwalk (BIENVE / NIDOS).

    prueba_cartel_es.py <carpeta build>   (despues de 'make es')

texturas_dma copia el MIO0 de cada mitad con el tamanio comprimido que dice
el desplazamientos.c de su pista. Ese tamanio tiene que salir de la cabecera
que genera el build (TAMANIO_ES_*), no escrito a mano, y ser el del .mio0
que incluye otras_texturas.s; el .mio0 da los pixeles del PNG.
"""
import os
import re
import sys

RAIZ = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
sys.path.insert(0, os.path.join(RAIZ, "herramientas"))

import formatos_textura as ft  # noqa: E402
import texturas_es  # noqa: E402

LISTA_S = os.path.join(RAIZ, "codigo", "datos", "otras_texturas.s")
# pista: [(simbolo en otras_texturas.s y en desplazamientos.c, id del manifiesto, texto)]
CARTELES = {
    "moo_moo_farm": [("textura_moo_moo_farm_izquierda_cartel", "cartel_granja_izquierda", "GRANJA"),
                     ("textura_moo_moo_farm_derecha_cartel", "cartel_granja_derecha", "MU-MU")],
    "banshee_boardwalk": [("textura_cartel_bienvenida_0", "cartel_bienvenida_0", "BIENVE"),
                          ("textura_cartel_bienvenida_1", "cartel_bienvenida_1", "NIDOS")],
}

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
    lista = open(LISTA_S).read()
    cabecera = os.path.join(build, "es", "tamanios_es.h")
    generados = dict(re.findall(r"#define\s+(TAMANIO_ES_\w+)\s+(0x[0-9A-Fa-f]+)", open(cabecera).read())) \
        if os.path.exists(cabecera) else {}
    for pista, mitades in sorted(CARTELES.items()):
        fuente = open(os.path.join(RAIZ, "recursos", "pistas", pista, "desplazamientos.c")).read()
        comprobar('#include "es/tamanios_es.h"' in fuente, "%s/desplazamientos.c no incluye es/tamanios_es.h" % pista)
        for simbolo, id_, texto in mitades:
            fila = filas.get(id_, {})
            comprobar(fila.get("texto_es") == texto, "%s: se espera %s" % (id_, texto))
            png = fila.get("png", "")
            comprobar(png.startswith("recursos/es/mio0/"), "%s: el PNG va en recursos/es/mio0/" % id_)
            if not png:
                continue
            incbin = texturas_es.salida_build(png, "es")
            m = re.search(r"glabel %s\s*\n\.incbin \"([^\"]+)\"" % simbolo, lista)
            comprobar(m is not None and m.group(1) == incbin, "otras_texturas.s: %s no incluye %s" % (simbolo, incbin))
            macro = "TAMANIO_ES_" + id_.upper()
            m = re.search(r"\{\s*%s,\s*(\w+),\s*0x1000," % simbolo, fuente)
            comprobar(m is not None and m.group(1) == macro, "%s/desplazamientos.c: %s no usa %s" % (pista, simbolo, macro))
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
