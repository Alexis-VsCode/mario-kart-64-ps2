#!/usr/bin/env python3
"""Los carteles de Lakitu en espanol.

    prueba_lakitu_es.py <carpeta build>   (despues de 'make es')

Por animacion: la tira PNG usa la paleta original y es la salida de
lakitu_es.py; en cada cuadro solo cambian pixeles del cartel (nunca los
de Lakitu ni fuera de la placa); el cuadro plano tiene el texto con al
menos 8 filas de alto; otras_texturas.s incluye los 16 .bin del build en
orden y seguidos (el juego solo conoce el primero) y cada .bin es el
cuadro de la tira. Ningun cuadro (tampoco los del giro) pinta colores que
el cartel no tenia ni deja bloques blancos.
"""
import os
import re
import sys

RAIZ = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
sys.path.insert(0, os.path.join(RAIZ, "herramientas"))

import compositor_es as ce  # noqa: E402
import lakitu_es as le  # noqa: E402
import png_simple  # noqa: E402

LISTA_S = os.path.join(RAIZ, "codigo", "datos", "otras_texturas.s")
TEXTOS = {"lakitu_vuelta_final": "¡ÚLTIMA!", "lakitu_segunda_vuelta": "VUELTA 2",
          "lakitu_marcha_atras": "¡REVÉS!"}

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def probar_colores(fila, n, viejo, nuevo, pal, z):
    """Lo pintado usa solo colores que el cartel ya tenia en ese cuadro, y no deja bloques
    blancos: 2x3 pixeles cambiados mas claros que todo lo que habia en su fila del cartel."""
    placa = {viejo[y * le.ANCHO + x] for y in range(z[1], z[3]) for x in range(z[0], z[2])}
    fuera = sorted({b for a, b in zip(viejo, nuevo) if a != b and b not in placa})
    comprobar(not fuera, "%s cuadro %d: colores fuera de la paleta del cartel: %s" % (fila["id"], n, fuera[:8]))
    tope = [max((ce.lum(pal[viejo[y * le.ANCHO + x]]) for x in range(z[0], z[2]) if pal[viejo[y * le.ANCHO + x]][3]
                 and not le.es_lakitu(pal[viejo[y * le.ANCHO + x]])), default=0) for y in range(le.ALTO)]
    claro = [a != b and ce.lum(pal[b]) > tope[i // le.ANCHO] + 10 for i, (a, b) in enumerate(zip(viejo, nuevo))]
    bloques = [(x, y) for y in range(le.ALTO - 1) for x in range(le.ANCHO - 2)
               if all(claro[(y + dy) * le.ANCHO + x + dx] for dy in range(2) for dx in range(3))]
    comprobar(not bloques, "%s cuadro %d: bloques blancos en %s" % (fila["id"], n, bloques[:4]))


def probar_tira(fila):
    """Paso 1: la tira es la salida de la herramienta y solo toca el cartel."""
    ruta = os.path.join(RAIZ, fila["png"])
    comprobar(os.path.exists(ruta), "%s: falta %s" % (fila["id"], fila["png"]))
    if not os.path.exists(ruta):
        return None
    try:
        nuevos = le.partir_tira(png_simple.leer(ruta), fila)
    except le.ErrorLakitu as e:
        comprobar(False, "%s: %s" % (fila["id"], e))
        return None
    comprobar(nuevos == le.animacion_espanol(fila), "%s: la tira no es la salida de lakitu_es.py" % fila["id"])
    pal = le.paleta(fila)
    canal = le.CANAL[fila["placa"]]
    for n, (viejo, nuevo) in enumerate(zip(le.cuadros(fila), nuevos), 1):
        rgba = [pal[i] for i in viejo]
        z = le.zona(rgba, canal)
        for i, (a, b) in enumerate(zip(viejo, nuevo)):
            if a == b:
                continue
            x, y = i % le.ANCHO, i // le.ANCHO
            comprobar(z is not None and z[0] <= x < z[2] and z[1] <= y < z[3],
                      "%s cuadro %d: cambia (%d, %d), fuera de la placa" % (fila["id"], n, x, y))
            comprobar(not le.es_lakitu(rgba[i]), "%s cuadro %d: pisa a Lakitu en (%d, %d)" % (fila["id"], n, x, y))
        if z is not None:
            probar_colores(fila, n, viejo, nuevo, pal, z)
    plano = [pal[i] for i in nuevos[int(fila["plano"]) - 1]]
    mascara = le.mascara_texto(plano, le.zona(plano, canal))
    alto = len({y for _, y in mascara})
    comprobar(alto >= 8, "%s: el texto del cuadro plano mide %d filas" % (fila["id"], alto))
    return nuevos


def probar_lista(fila, nuevos, build):
    """Paso 2: otras_texturas.s incluye los 16 cuadros del build, en orden y seguidos."""
    texto = open(LISTA_S).read()
    base = os.path.splitext(fila["patron"])[0]
    patron = r'\.balign 4, 0x00\s*\nglabel textura_(%s)\s*\n\.incbin "([^"]+)"\s*\n' % base.replace("%02d", r"\d\d")
    entradas = re.findall(patron, texto)
    esperadas = [("es/lakitu/%s/%s" % (fila["carpeta"], fila["patron"] % n)) for n in range(1, le.CUADROS + 1)]
    comprobar([r for _, r in entradas] == esperadas, "%s: otras_texturas.s no incluye los 16 cuadros del build en orden"
              % fila["id"])
    bloque = re.search(r"glabel textura_%s\s*\n(.*?)glabel textura_%s\s*\n\.incbin \"[^\"]+\"" %
                       (base % 1, base % le.CUADROS), texto, re.S)
    sobra = re.sub(r'\.balign 4, 0x00|glabel \w+|\.incbin "[^"]+"|\s', "", bloque.group(1)) if bloque else "?"
    comprobar(sobra == "", "%s: entre los cuadros hay algo mas que .balign 4 (%r)" % (fila["id"], sobra[:40]))
    for n, esperada in enumerate(esperadas, 1):
        ruta = os.path.join(build, esperada)
        datos = open(ruta, "rb").read() if os.path.exists(ruta) else b""
        comprobar(len(datos) == le.ANCHO * le.ALTO, "%s: falta o mide mal %s (make es)" % (fila["id"], ruta))
        if nuevos is not None and datos:
            comprobar(datos == nuevos[n - 1], "%s: %s no es el cuadro %d de la tira" % (fila["id"], ruta, n))


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    filas = {f["id"]: f for f in le.leer_manifiesto()}
    comprobar(sorted(filas) == sorted(TEXTOS), "lakitu.tsv tiene que tener las tres animaciones con texto")
    for id_, texto in TEXTOS.items():
        fila = filas.get(id_)
        if fila is None:
            continue
        comprobar(fila["texto_es"] == texto, "%s: se espera %s" % (id_, texto))
        nuevos = probar_tira(fila)
        probar_lista(fila, nuevos, sys.argv[1])
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
