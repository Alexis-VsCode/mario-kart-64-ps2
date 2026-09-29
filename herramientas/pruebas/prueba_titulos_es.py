#!/usr/bin/env python3
"""Los titulos de pista con los nombres oficiales en espanol.

    prueba_titulos_es.py

Para cada indice de nombres_circuito: su titulo_* lleva el nombre acordado,
en mayusculas como el original; el PNG es la salida del compositor, ya no
es la original, y el texto cabe en los 140x18 sin tocar el marco (columnas
0 y 139, filas 0 y 17). Las letras en espanol salen de glifos elegidos uno
por uno (elegidas.tsv), y cada letra que se usa tiene el suyo.
"""
import os
import sys

RAIZ = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
sys.path.insert(0, os.path.join(RAIZ, "herramientas"))

import compositor_es as ce  # noqa: E402
import png_simple  # noqa: E402
import texturas_es  # noqa: E402

# indice en nombres_circuito -> (textura, nombre oficial)
NOMBRES = [
    ("titulo_mario_raceway", "PISTA MARIO"), ("titulo_choco_mountain", "MONTE CHOCOLATE"),
    ("titulo_bowsers_castle", "CASTILLO DE BOWSER"), ("titulo_banshee_boardwalk", "MUELLE EMBRUJADO"),
    ("titulo_yoshi_valley", "VALLE DE YOSHI"), ("titulo_frappe_snowland", "CIRCUITO NEVADO"),
    ("titulo_koopa_troopa_beach", "PLAYA KOOPA"), ("titulo_royal_raceway", "PISTA REAL"),
    ("titulo_luigi_raceway", "PISTA LUIGI"), ("titulo_moo_moo_farm", "GRANJA MU-MU"),
    ("titulo_toads_turnpike", "AUTOPISTA TOAD"), ("titulo_kalimari_desert", "DESIERTO KALIMARI"),
    ("titulo_sherbet_land", "TIERRA SORBETE"), ("titulo_rainbow_road", "SENDA ARCO IRIS"),
    ("titulo_wario_stadium", "ESTADIO WARIO"), ("titulo_block_fort", "CIUDAD BLOQUE"),
    ("titulo_skyscraper", "RASCACIELOS"), ("titulo_double_deck", "DOBLE PISO"),
    ("titulo_dks_jungle_parkway", "PISTA DE LA JUNGLA DK"), ("titulo_big_donut", "GRAN DONUT"),
]

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def main():
    filas = {f["id"]: f for f in texturas_es.leer_manifiesto(texturas_es.MANIFIESTO)}
    comps = ce.leer_composicion()
    familia = ce.Familia("titulos_pista")
    for indice, (id_, nombre) in enumerate(NOMBRES):
        fila, comp = filas.get(id_, {}), comps.get(id_)
        comprobar(fila.get("texto_es") == nombre, "%d %s: se espera %s" % (indice, id_, nombre))
        comprobar(comp is not None and comp["familia"] == "titulos_pista", "%s: sin composicion" % id_)
        if comp is None or not fila.get("png"):
            continue
        for c in set(nombre) - {" "}:
            comprobar(c in familia.elegidas or c in familia.recetas, "%s: la letra %r no tiene glifo elegido" % (id_, c))
        original = ce.Textura.cargar(id_)
        try:
            nuevo = ce.png_compuesto(id_, fila, comp).a_rgba()
        except ce.ErrorComposicion as e:
            comprobar(False, "%s: %s" % (id_, e))
            continue
        png = png_simple.leer(os.path.join(RAIZ, fila["png"])).a_rgba()
        comprobar(png == nuevo, "%s: el PNG no es la salida del compositor" % id_)
        comprobar(png != original.pixeles, "%s: el PNG sigue siendo el original" % id_)
        marco = [(x, y) for y in range(18) for x in range(140) if x in (0, 139) or y in (0, 17)]
        comprobar(all(png[y * 140 + x] == original.pixel(x, y) for x, y in marco), "%s: el texto toca el marco" % id_)
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
