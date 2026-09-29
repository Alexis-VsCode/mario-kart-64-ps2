#!/usr/bin/env python3
"""Genera la cabecera con la tinta de cada glifo de la fuente del menu.

    prueba_textos_tinta.py <lista_glifos.inc.c> <salida.h>

prueba_textos.c mide el ancho visible de una cadena como la suma de los
avances de todos los glifos menos el ultimo mas la tinta derecha del ultimo:
la letra puede dibujar mas alla de su avance (la 'O' avanza 12 y pinta hasta
17). Tambien usa donde empieza la tinta de cada glifo, para ver si dos textos
vecinos se tocan. La tinta sale de los .i4 que dibuja el juego: los de la
fuente original y los del espanol que arma herramientas/generar_glifos_es.py.

El quad de un glifo de ancho A muestra A-1 texeles en A pixeles (S=1600 en el
de 26), asi que la tinta en pixeles es (columna + 1) * A / (A - 1).
"""
import glob
import math
import os
import re
import sys

RAIZ = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))
sys.path.insert(0, os.path.join(RAIZ, "herramientas"))
import generar_glifos_es  # noqa: E402

PREFIJO_ES = "glifos_es/"


def glifos(ruta):
    """Textura (TexturaMenu) de cada glifo, en orden de indice."""
    texto = open(ruta, encoding="utf-8").read()
    return re.findall(r"^GLIFO\(\s*(\w+)\s*,\s*\w+\s*\)", texto, re.M)


def partes():
    """TexturaMenu -> lista de (datos, ancho, alto, d_x) de sus partes."""
    resultado = {}
    for ruta in glob.glob(os.path.join(RAIZ, "codigo", "datos", "texturas", "*.inc.c")):
        texto = open(ruta, encoding="utf-8").read()
        for nombre, cuerpo in re.findall(r"TexturaMenu (\w+)\[\d*\] = \{(.*?)\n\};", texto, re.S):
            filas = re.findall(r"\{\s*\d+,\s*(\w+),\s*(\d+),\s*(\w+),\s*(-?\d+),", cuerpo)
            resultado[nombre] = [(d, int(a), alto, int(dx)) for d, a, alto, dx in filas if d != "NULL"]
    return resultado


def incbins():
    """Simbolo de datos -> ruta del .incbin que lo define."""
    resultado = {}
    for ruta in glob.glob(os.path.join(RAIZ, "codigo", "datos", "*.s")):
        texto = open(ruta, encoding="utf-8", errors="replace").read()
        for simbolo, archivo in re.findall(r"glabel (\w+)\s*\n\s*\.incbin \"([^\"]+)\"", texto):
            resultado[simbolo] = archivo
    return resultado


def columnas_i4(archivo, ancho, alto, generados):
    """Filas de texeles de un .i4 (o de un glifo generado del espanol), o None."""
    if archivo.startswith(PREFIJO_ES):
        imagen = generados.get(os.path.splitext(archivo[len(PREFIJO_ES):])[0])
        return imagen
    ruta = os.path.join(RAIZ, archivo)
    if not archivo.endswith(".i4") or not os.path.exists(ruta):
        return None
    datos = open(ruta, "rb").read()
    if len(datos) != ancho * alto // 2:
        return None
    return [[(datos[(y * ancho + x) // 2] >> (4 if x % 2 == 0 else 0)) & 0xF for x in range(ancho)] for y in range(alto)]


def tinta(textura, tabla_partes, tabla_incbin, generados):
    """Pixeles (a escala 1, desde la pluma) donde empieza y termina la tinta del glifo."""
    inicio, fin = None, 0
    for datos, ancho, alto, d_x in tabla_partes.get(textura, []):
        alto = generar_glifos_es.ALTO_DIACRITICO if alto == "ALTO_DIACRITICO" else int(alto)
        imagen = columnas_i4(tabla_incbin.get(datos, ""), ancho, alto, generados)
        visibles = ancho - 1
        if imagen is None:
            columnas = [0, visibles - 1]
        else:
            columnas = [x for x in range(visibles) if any(fila[x] for fila in imagen[:alto - 1])]
        if columnas:
            izquierda = d_x + int(math.floor(min(columnas) * ancho / float(visibles)))
            inicio = izquierda if inicio is None else min(inicio, izquierda)
            fin = max(fin, d_x + int(math.ceil((max(columnas) + 1) * ancho / float(visibles))))
    return inicio or 0, fin


def main():
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    lista = glifos(sys.argv[1])
    tabla_partes, tabla_incbin = partes(), incbins()
    generados = generar_glifos_es.generar()
    valores = [tinta(t, tabla_partes, tabla_incbin, generados) for t in lista]
    salida = ["// Generado por herramientas/pruebas/prueba_textos_tinta.py: no editar"]
    for nombre, lado in (("tinta_izquierda_glifo", 0), ("tinta_derecha_glifo", 1)):
        salida += ["", "static const s16 %s[%d] = {" % (nombre, len(valores))]
        for inicio in range(0, len(valores), 16):
            salida.append("    " + ", ".join("%d" % v[lado] for v in valores[inicio:inicio + 16]) + ",")
        salida.append("};")
    temporal = sys.argv[2] + ".tmp"
    with open(temporal, "w") as f:
        f.write("\n".join(salida) + "\n")
    os.replace(temporal, sys.argv[2])


if __name__ == "__main__":
    main()
