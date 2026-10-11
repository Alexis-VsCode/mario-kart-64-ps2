#!/usr/bin/env python3
"""Toda escritura en gfx_pool->efecto_mtx lleva antes el tope de la reserva.

efecto_mtx tiene MTX_EFECTO_POOL_TAMANIO matrices y cantidad_efecto_matriz
crece con cada elemento dibujado en el cuadro; el juego de la N64 no lo
comprobaba en casi ningún sitio. funcion_80095BD0 (cargar_texturas_menu.inc.c)
compara el índice con la reserva y salta el elemento si no queda matriz. La
prueba exige esa comparación dentro de la misma función y antes de la primera
línea que toca efecto_mtx[cantidad_efecto_matriz...]. Si la función usa
matrices de más (mtx + 1, efecto_mtx[cantidad_efecto_matriz + 1]), el tope
debe sumar al menos ese desplazamiento. Quitarla no da ningún
error de compilación: solo escribe fuera del arreglo cuando el cuadro se llena.
"""
import os
import re
import sys

RAIZ = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))

ARCHIVOS = (
    "codigo/menus/elementos_menu/cargar_texturas_menu.inc.c",
    "codigo/menus/elementos_menu/imprimir_texto.inc.c",
    "codigo/menus/elementos_menu/menus_pausa.inc.c",
    "codigo/carrera/objetos_y_efectos/particulas_derrape.inc.c",
    "codigo/carrera/objetos_y_efectos/globos_batalla.inc.c",
    "codigo/graficos/dibujar_jugador/dibujar_kart_y_sombra.inc.c",
    "codigo/ceremonia/actores_podio.c",
)

ESCRITURA = re.compile(r"efecto_mtx\[\s*cantidad_efecto_matriz")
# Cabecera de función: empieza en la columna 0 y acaba en ') {'
CABECERA = re.compile(r"^[A-Za-z_][^;=]*\)\s*\{\s*$")
# El tope: el índice (más las matrices de más que use la función) contra la reserva
TOPE = re.compile(r"cantidad_efecto_matriz\s*(?:\+\s*(\d+)\s*)?(?:<|>=)\s*MTX_EFECTO_POOL_TAMANIO\b")
# Matrices de más que la función toca tras la del índice
DESPLAZAMIENTO = re.compile(r"(?:\bmtx|efecto_mtx\[\s*cantidad_efecto_matriz)\s*\+\s*(\d+)")

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def main():
    for ruta in ARCHIVOS:
        with open(os.path.join(RAIZ, ruta), encoding="utf-8") as f:
            lineas = f.read().split("\n")
        comprobar(any(ESCRITURA.search(l) for l in lineas), "%s: no escribe efecto_mtx; sobra en la lista" % ruta)
        inicio, vistas = 0, set()
        for n, linea in enumerate(lineas):
            if CABECERA.match(linea):
                inicio = n
            if not ESCRITURA.search(linea) or inicio in vistas:
                continue
            vistas.add(inicio)
            antes = "\n".join(lineas[inicio:n])
            tope = TOPE.search(antes)
            comprobar(tope is not None,
                      "%s:%d: escribe efecto_mtx sin comparar antes cantidad_efecto_matriz con "
                      "MTX_EFECTO_POOL_TAMANIO en %s" % (ruta, n + 1, lineas[inicio].strip()))
            fin = next((m for m in range(n, len(lineas)) if CABECERA.match(lineas[m])), len(lineas))
            extra = max([int(d) for d in DESPLAZAMIENTO.findall("\n".join(lineas[inicio:fin]))] or [0])
            if extra and tope:
                comprobar(int(tope.group(1) or 0) >= extra,
                          "%s:%d: usa cantidad_efecto_matriz + %d pero el tope no lo suma en %s"
                          % (ruta, n + 1, extra, lineas[inicio].strip()))
    print("%d comprobaciones, %d %s" % (comprobaciones, fallos, "fallo" if fallos == 1 else "fallos"))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
