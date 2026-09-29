#!/usr/bin/env python3
"""Genera los glifos del espanol de la fuente del menu a partir de los originales.

    generar_glifos_es.py <carpeta de salida> [--ver]

Los glifos del juego son I4 de 26x16 (dos texeles por byte, el alto primero)
y dibujan la letra en las filas 0-14. Salen dos clases de archivo:

- diacritico_*.i4 (26x8): la tilde, la virgulilla o la dieresis de una letra.
  El juego la dibuja como segunda parte del glifo, encima de la letra base,
  asi que la letra es la original. La tinta va en las filas 2-5 (el quad
  muestrea 7 filas y la 6 queda de separacion) y se centra sobre la parte
  alta de la letra, que es cursiva.
- abre_*.i4 y ordinal_*.i4 (26x16): los signos de apertura (el ! y el ?
  girados) y los ordinales (la O y la A a la mitad, arriba, con subrayado).

--ver imprime los glifos en texto para revisarlos a ojo.
"""
import os
import sys

RAIZ = os.path.normpath(os.path.join(os.path.dirname(__file__), ".."))
ORIGINALES = os.path.join(RAIZ, "recursos", "texturas", "sin_comprimir")
ANCHO = 26
ALTO_LETRA = 16
ALTO_DIACRITICO = 8
FILAS_VISIBLES = 15     # T=960 en el quad de 16: se ven las filas 0-14
COLUMNAS_VISIBLES = 25  # S=1600 en el quad de 26: se ven las columnas 0-24
CURSIVA = 2             # la fuente se inclina ~2 texeles en 4 filas hacia arriba

# Dibujos de los signos: un caracter hexadecimal por texel ('.' = 0)
AGUDA = ["...8f", "..cf8", ".8fc.", "4c4.."]
VIRGULILLA = [".5de8..9e", "ce58ddfd4", "a2...6a3."]
DIERESIS = ["6fe..6fe", "cf6..cf6"]
FILA_SIGNO = 2          # primera fila con tinta en la parte de 26x8

DIACRITICOS = [
    # (archivo, letra base, dibujo)
    ("diacritico_a_aguda", "a", AGUDA),
    ("diacritico_e_aguda", "e", AGUDA),
    ("diacritico_i_aguda", "i", AGUDA),
    ("diacritico_o_aguda", "o", AGUDA),
    ("diacritico_u_aguda", "u", AGUDA),
    ("diacritico_n_virgulilla", "n", VIRGULILLA),
    ("diacritico_u_dieresis", "u", DIERESIS),
]
GIRADOS = [("abre_exclamacion", "fuente_signo_exclamacion"), ("abre_interrogacion", "fuente_marcar_pregunta")]
ORDINALES = [("ordinal_o", "o"), ("ordinal_a", "a")]
ARCHIVOS = [d[0] for d in DIACRITICOS] + [g[0] for g in GIRADOS] + [o[0] for o in ORDINALES]


def leer_i4(nombre, alto=ALTO_LETRA):
    datos = open(os.path.join(ORIGINALES, nombre + ".i4"), "rb").read()
    assert len(datos) == ANCHO * alto // 2, nombre
    return [[(datos[(y * ANCHO + x) // 2] >> (4 if x % 2 == 0 else 0)) & 0xF for x in range(ANCHO)] for y in range(alto)]


def escribir_i4(imagen):
    salida = bytearray()
    for fila in imagen:
        for x in range(0, ANCHO, 2):
            salida.append((fila[x] << 4) | fila[x + 1])
    return bytes(salida)


def vacia(alto):
    return [[0] * ANCHO for _ in range(alto)]


def centro_superior(letra):
    """Columna media de la tinta de las tres primeras filas de la letra."""
    columnas = [x for y in range(3) for x in range(ANCHO) if letra[y][x] >= 8]
    return (min(columnas) + max(columnas)) / 2.0


def diacritico(base, dibujo):
    letra = leer_i4("fuente_letra_" + base)
    ancho_dibujo = max(len(f) for f in dibujo)
    x0 = int(round(centro_superior(letra) + CURSIVA - (ancho_dibujo - 1) / 2.0))
    x0 = max(0, min(x0, COLUMNAS_VISIBLES - ancho_dibujo))
    imagen = vacia(ALTO_DIACRITICO)
    for dy, fila in enumerate(dibujo):
        for dx, c in enumerate(fila):
            imagen[FILA_SIGNO + dy][x0 + dx] = 0 if c == "." else int(c, 16)
    return imagen


def caja_tinta(imagen):
    """(x0, y0, x1, y1) de la tinta visible, con los extremos incluidos."""
    puntos = [(x, y) for y in range(FILAS_VISIBLES) for x in range(COLUMNAS_VISIBLES) if imagen[y][x]]
    xs = [p[0] for p in puntos]
    ys = [p[1] for p in puntos]
    return min(xs), min(ys), max(xs), max(ys)


def girado(nombre):
    """Giro de 180 grados dentro de la caja de tinta: conserva la cursiva y el ancho."""
    original = leer_i4(nombre)
    x0, y0, x1, y1 = caja_tinta(original)
    imagen = vacia(ALTO_LETRA)
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            imagen[y][x] = original[y0 + y1 - y][x0 + x1 - x]
    return imagen


def ordinal(base):
    """La letra a la mitad, arriba, con un subrayado debajo."""
    letra = leer_i4("fuente_letra_" + base)
    x0, y0, x1, y1 = caja_tinta(letra)
    imagen = vacia(ALTO_LETRA)
    ancho = (x1 - x0) // 2 + 1
    for y in range(0, (y1 - y0) // 2 + 1):
        for x in range(ancho):
            muestras = [letra[min(y0 + 2 * y + j, y1)][min(x0 + 2 * x + i, x1)] for j in (0, 1) for i in (0, 1)]
            imagen[y][x0 + CURSIVA + x] = (sum(muestras) + 2) // 4
    fila_raya = (y1 - y0) // 2 + 2
    for x in range(ancho):
        imagen[fila_raya][x0 + x] = 0xF
    return imagen


def generar():
    """Diccionario archivo -> imagen."""
    imagenes = {}
    for archivo, base, dibujo in DIACRITICOS:
        imagenes[archivo] = diacritico(base, dibujo)
    for archivo, original in GIRADOS:
        imagenes[archivo] = girado(original)
    for archivo, base in ORDINALES:
        imagenes[archivo] = ordinal(base)
    return imagenes


def main():
    argumentos = [a for a in sys.argv[1:] if a != "--ver"]
    if len(argumentos) != 1:
        sys.exit(__doc__)
    salida = argumentos[0]
    os.makedirs(salida, exist_ok=True)
    for archivo, imagen in sorted(generar().items()):
        with open(os.path.join(salida, archivo + ".i4"), "wb") as f:
            f.write(escribir_i4(imagen))
        if "--ver" in sys.argv:
            print(archivo)
            for fila in imagen:
                print("  " + "".join(".123456789abcdef"[v] for v in fila))


if __name__ == "__main__":
    main()
