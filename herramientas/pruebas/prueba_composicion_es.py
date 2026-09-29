#!/usr/bin/env python3
"""Las texturas en espanol salen del compositor, con glifos del propio juego.

    prueba_composicion_es.py

Para cada textura de recursos/es/composicion.tsv: el texto del manifiesto
tiene glifo para cada caracter y cabe en su caja, recomponer el ingles
reproduce al menos el 95 % de la caja (los cortes de los glifos estan
bien), fuera de la caja no cambia nada y el PNG versionado es exactamente
lo que da el compositor (salvo que el manifiesto lo marque 'retocado').
"""
import os
import sys

RAIZ = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
sys.path.insert(0, os.path.join(RAIZ, "herramientas"))

import compositor_es as ce  # noqa: E402
import png_simple  # noqa: E402
import texturas_es  # noqa: E402

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def probar_familias():
    """Paso 1: los cortes de cada glifo caen dentro de su textura y las recetas se arman."""
    for nombre in sorted(os.listdir(ce.GLIFOS)):
        familia = ce.Familia(nombre)
        for caja in familia.cajas:
            textura = ce.Textura.cargar(caja["textura"])
            izq, der = int(caja["x_izq"]), int(caja["x_der"])
            comprobar(0 <= izq < der <= textura.ancho and familia.filas[1] <= textura.alto,
                      "%s: glifo %r fuera de %s" % (nombre, caja["caracter"], caja["textura"]))
        for caracter in familia.recetas:
            try:
                if caracter.startswith("diminuta "):
                    familia.glifo_forma(caracter[len("diminuta "):], 10)
                else:
                    familia.glifo(caracter)
            except (ce.ErrorComposicion, OSError, TypeError) as e:
                comprobar(False, "%s: receta de %r: %s" % (nombre, caracter, e))


def probar_textura(id_, comp, fila):
    """Paso 2: una textura compuesta."""
    comprobar(bool(fila["texto_es"]), "%s: sin texto_es en el manifiesto" % id_)
    comprobar(fila["png"].startswith("recursos/es/"), "%s: sin PNG en el manifiesto" % id_)
    try:
        parecido = ce.autoprueba(id_, comp)
        comprobar(parecido >= ce.MINIMO_AUTOPRUEBA, "%s: recomponer el ingles da %.1f%% de la caja"
                  % (id_, 100 * parecido))
        imagen = ce.png_compuesto(id_, fila, comp)
    except (ce.ErrorComposicion, OSError) as e:
        comprobar(False, "%s: %s" % (id_, e))
        return
    ancho, alto, base = ce.lienzo(comp, ce.Textura.cargar(id_))
    cx, cy, cw, ch = ce.area_de(comp)
    nuevo = imagen.a_rgba()
    fuera = [(x, y) for y in range(alto) for x in range(ancho)
             if not (cx <= x < cx + cw and cy <= y < cy + ch) and nuevo[y * ancho + x] != base[y * ancho + x]]
    comprobar(not fuera, "%s: cambian %d pixeles fuera de la caja" % (id_, len(fuera)))
    ruta = os.path.join(RAIZ, fila["png"])
    if fila["retocado"] == "no" and os.path.exists(ruta):
        comprobar(png_simple.leer(ruta).a_rgba() == nuevo, "%s: %s no es la salida del compositor" % (id_, fila["png"]))


def main():
    manifiesto = {f["id"]: f for f in texturas_es.leer_manifiesto(texturas_es.MANIFIESTO)}
    comps = ce.leer_composicion()
    comprobar(len(comps) >= 4, "se esperaban texturas en %s" % ce.COMPOSICION)
    probar_familias()
    for id_, comp in sorted(comps.items()):
        comprobar(id_ in manifiesto and comp["familia"] in os.listdir(ce.GLIFOS), "%s: fila invalida" % id_)
        if id_ in manifiesto:
            probar_textura(id_, comp, manifiesto[id_])
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
