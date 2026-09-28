#!/usr/bin/env python3
"""Las texturas de menu en espanol llegan al juego desde sus PNG versionados.

    prueba_cableado_es.py <carpeta build>   (despues de 'make es')

Para cada textura del manifiesto que se traduce: su PNG sirve para
reemplazar a la original, texturas_tkmk00.s incluye el .mio0 que genera el
build (alineado a 16), cada TexturaMenu que la usa lleva su TAMANIO_ES_*,
ese tamanio cubre el .mio0 y cabe en buffer_comprimido_menu, y el MIO0
se descomprime a los bytes del PNG. Si el PNG no se toco todavia, esos
bytes son los de la original (SHA-1 de referencias_tkmk00.txt).
"""
import hashlib
import os
import re
import sys

RAIZ = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
sys.path.insert(0, os.path.join(RAIZ, "herramientas"))

import formatos_textura as ft  # noqa: E402
import texturas_es  # noqa: E402

LISTA_S = os.path.join(RAIZ, "codigo", "datos", "texturas_tkmk00.s")
TABLAS = [os.path.join(RAIZ, "codigo", "datos", "texturas", n)
          for n in ("fuentes_y_menus.inc.c", "vistas_previas_pistas.inc.c")]
TEXTURAS_C = os.path.join(RAIZ, "codigo", "datos", "texturas.c")
REFERENCIAS = os.path.join(RAIZ, "herramientas", "pruebas", "referencias_tkmk00.txt")
# buffer_comprimido_menu: 0xCE00 en los menus, 0x2800 en carrera y ceremonia
BUFFER_MENUS = 0xCE00
BUFFER_CARRERA = 0x2800
SOLO_MENUS = ("seleccion_juego", "seleccion_jugador", "seleccion_mapa", "opcion")

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def entradas_lista_s():
    """[(balign_16 antes, simbolo, ruta del .incbin)] de texturas_tkmk00.s"""
    texto = open(LISTA_S).read()
    return [(bool(a), s, r) for a, s, r in
            re.findall(r'(\.balign 16\s*\n)?glabel\s+(\w+)\s*\n\s*\.incbin\s+"([^"]+)"', texto)]


def tamanios_generados(ruta):
    return {m: int(v, 16) for m, v in re.findall(r"#define\s+(TAMANIO_ES_\w+)\s+0x([0-9A-Fa-f]+)", open(ruta).read())}


def probar_pngs(filas):
    """Paso 1: cada textura que se traduce tiene su PNG y sirve para reemplazar a la original."""
    traducidas = [f for f in filas if not f["motivo_no"]]
    comprobar(len(traducidas) >= 40, "se esperaban al menos 40 texturas a traducir, hay %d" % len(traducidas))
    for f in filas:
        comprobar(bool(f["png"]) != bool(f["motivo_no"]), "%s: png y motivo_no se excluyen" % f["id"])
    pngs = [f["png"] for f in traducidas]
    for f in traducidas:
        ruta = os.path.join(RAIZ, f["png"])
        comprobar(os.path.exists(ruta), "%s: no existe %s" % (f["id"], f["png"]))
        if os.path.exists(ruta):
            problemas = texturas_es.problemas(ruta, filas)
            comprobar(not problemas, "%s: %s" % (f["id"], "; ".join(problemas)))
    en_disco = []
    for base, _, nombres in os.walk(os.path.join(RAIZ, "recursos", "es")):
        en_disco += [os.path.relpath(os.path.join(base, n), RAIZ) for n in nombres if n.endswith(".png")]
    sobran = sorted(set(en_disco) - set(pngs))
    comprobar(not sobran, "PNG que el manifiesto no usa: %s" % ", ".join(sobran))
    comprobar(not os.path.exists(os.path.join(RAIZ, "es")), "no puede haber una carpeta es/ en la raiz (.incbin)")


def probar_lista_s(filas):
    """Paso 2: texturas_tkmk00.s incluye el .mio0 de cada traducida y alinea todo a 16."""
    por_origen = {os.path.basename(f["origen"]): f for f in filas}
    entradas = entradas_lista_s()
    comprobar(len(entradas) == 63, "se esperaban 63 texturas en texturas_tkmk00.s, hay %d" % len(entradas))
    simbolos = {}
    for alineada, simbolo, ruta in entradas:
        comprobar(alineada, "%s: falta .balign 16 antes del glabel" % simbolo)
        if ruta.startswith("es/"):
            fila = next((f for f in filas if f["png"] and texturas_es.salida_build(f["png"], "es") == ruta), None)
            comprobar(fila is not None, "%s: %s no sale de ningun PNG del manifiesto" % (simbolo, ruta))
        else:
            fila = por_origen.get(os.path.basename(ruta))
            comprobar(fila is not None and not fila["png"], "%s: %s se traduce y sigue apuntando a la original"
                      % (simbolo, ruta))
        if fila is not None:
            simbolos[simbolo] = fila
    return simbolos


def probar_tablas(simbolos, generados):
    """Paso 3: las TexturaMenu de las traducidas usan su TAMANIO_ES_*, y solo ellas."""
    usadas = set()
    for tabla in TABLAS:
        entradas = re.findall(r"\{\s*(\d+),\s*(\w+),\s*(\d+),\s*(\d+),\s*\d+,\s*\d+,\s*(\w+),\s*\d+\s*\}",
                              open(tabla).read())
        for _, simbolo, ancho, alto, tamanio in entradas:
            fila = simbolos.get(simbolo)
            if fila is None or not fila["png"]:
                comprobar(not tamanio.startswith("TAMANIO_ES_"), "%s usa %s sin traducirse" % (simbolo, tamanio))
                continue
            macro = "TAMANIO_ES_" + fila["id"].upper()
            usadas.add(fila["id"])
            comprobar(tamanio == macro, "%s: tamanio %s, se esperaba %s" % (simbolo, tamanio, macro))
            comprobar(macro in generados, "%s no esta en la cabecera generada" % macro)
            comprobar("%sx%s" % (ancho, alto) == fila["tamanio"], "%s: %sx%s en la tabla y %s en el manifiesto"
                      % (simbolo, ancho, alto, fila["tamanio"]))
    faltan = sorted(f["id"] for f in simbolos.values() if f["png"] and f["id"] not in usadas)
    comprobar(not faltan, "traducidas sin ninguna TexturaMenu: %s" % ", ".join(faltan))
    comprobar('#include "es/tamanios_es.h"' in open(TEXTURAS_C).read(), "texturas.c no incluye es/tamanios_es.h")


def probar_mio0(filas, build, generados, refs):
    """Paso 4: cada .mio0 cabe, declara w*h*2 y da los bytes del PNG (y de la original si no se toco)."""
    for f in filas:
        if not f["png"].startswith("recursos/es/mio0/"):
            continue
        ruta = texturas_es.salida_build(f["png"], os.path.join(build, "es"))
        comprobar(os.path.exists(ruta), "falta %s (make es)" % ruta)
        if not os.path.exists(ruta):
            continue
        datos = open(ruta, "rb").read()
        ancho, alto = texturas_es.dimensiones(f)
        macro = "TAMANIO_ES_" + f["id"].upper()
        limite = BUFFER_MENUS if f["id"] in SOLO_MENUS else BUFFER_CARRERA
        valor = generados.get(macro, 0)
        comprobar(len(datos) <= valor <= limite, "%s: %s = 0x%X para un .mio0 de 0x%X (limite 0x%X)"
                  % (f["id"], macro, valor, len(datos), limite))
        comprobar(datos[:4] == b"MIO0" and int.from_bytes(datos[4:8], "big") == ancho * alto * 2,
                  "%s: la cabecera MIO0 no declara %dx%dx2 bytes" % (f["id"], ancho, alto))
        rgba16 = ft.descomprimir_mio0(datos)
        comprobar(rgba16 == texturas_es.convertir(os.path.join(RAIZ, f["png"])),
                  "%s: el .mio0 no da los bytes del PNG" % f["id"])
        if not f["texto_es"] and f["retocado"] == "no":
            comprobar(hashlib.sha1(rgba16).hexdigest() == refs.get(os.path.basename(f["origen"])),
                      "%s: sin traducir todavia, tiene que verse igual que la original" % f["id"])


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    build = sys.argv[1]
    filas = texturas_es.leer_manifiesto(texturas_es.MANIFIESTO)
    refs = {l.split()[0]: l.split()[4] for l in open(REFERENCIAS) if l.strip() and not l.startswith("#")}
    cabecera = os.path.join(build, "es", "tamanios_es.h")
    comprobar(os.path.exists(cabecera), "falta %s (make es)" % cabecera)
    generados = tamanios_generados(cabecera) if os.path.exists(cabecera) else {}
    probar_pngs(filas)
    simbolos = probar_lista_s(filas)
    probar_tablas(simbolos, generados)
    probar_mio0(filas, build, generados, refs)
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
