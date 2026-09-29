#!/usr/bin/env python3
"""Hojas de contacto de las texturas en espanol (make hoja-es).

    hojas_es.py <carpeta>

Una hoja PNG por familia de recursos/es/composicion.tsv: por textura, una
fila con la original, la version en espanol (el PNG versionado) y la
mascara de los pixeles que cambian, todo a escala 3. Si la version en
espanol es mas grande (lienzo), la original se muestra en su lugar dentro
de ese lienzo. Para Lakitu, una hoja por animacion con los 16 cuadros en
tira: originales, en espanol y mascara.
"""
import os
import sys

import compositor_es as ce
import lakitu_es
import png_simple
import texturas_es

ESCALA = 3
SEPARACION = 4          # pixeles de textura entre columnas y entre filas
FONDO = (64, 64, 64)
MARCADO = (255, 255, 255)
SIN_CAMBIO = (0, 0, 0)


def par(id_):
    """((ancho, alto, original), (ancho, alto, espanol)) en RGBA, del mismo tamanio."""
    filas = {f["id"]: f for f in texturas_es.leer_manifiesto(texturas_es.MANIFIESTO)}
    comp = ce.leer_composicion()[id_]
    original = ce.Textura.cargar(id_)
    ancho, alto, base = ce.lienzo(comp, original)
    imagen = png_simple.leer(os.path.join(texturas_es.RAIZ, filas[id_]["png"]))
    return (ancho, alto, base), (imagen.ancho, imagen.alto, imagen.a_rgba())


def distintos(a, b):
    """Se ven distintos: dos transparentes son iguales aunque guarden otro color."""
    return a != b and bool(a[3] or b[3])


def mascara(original, nuevo):
    return [distintos(a, b) for a, b in zip(original[2], nuevo[2])]


def _visible(p):
    """Transparente como damero: se ve la forma sin el color de la clave."""
    return p[:3] if p[3] else None


def hoja(filas_img):
    """filas_img: [[(ancho, alto, pixeles o None, mascara o None), ...], ...] -> Imagen rgb."""
    ancho = max(sum(c[0] for c in fila) + SEPARACION * (len(fila) - 1) for fila in filas_img)
    alto = sum(max(c[1] for c in fila) for fila in filas_img) + SEPARACION * (len(filas_img) - 1)
    lienzo = [[FONDO] * ancho for _ in range(alto)]
    y0 = 0
    for fila in filas_img:
        x0 = 0
        for w, h, pixeles, marcas in fila:
            for y in range(h):
                for x in range(w):
                    if marcas is not None:
                        color = MARCADO if marcas[y * w + x] else SIN_CAMBIO
                    else:
                        color = _visible(pixeles[y * w + x]) or ((200, 0, 200) if (x + y) % 2 else (150, 0, 150))
                    lienzo[y0 + y][x0 + x] = color
            x0 += w + SEPARACION
        y0 += max(c[1] for c in fila) + SEPARACION
    datos = bytearray()
    for fila in lienzo:
        linea = bytearray()
        for color in fila:
            linea += bytes(color) * ESCALA
        datos += bytes(linea) * ESCALA
    return png_simple.Imagen(ancho * ESCALA, alto * ESCALA, "rgb", bytes(datos))


def hojas_familias(carpeta):
    por_familia = {}
    for id_, comp in sorted(ce.leer_composicion().items()):
        por_familia.setdefault(comp["familia"], []).append(id_)
    for familia, ids in sorted(por_familia.items()):
        filas_img = []
        for id_ in ids:
            original, nuevo = par(id_)
            filas_img.append([(original[0], original[1], original[2], None),
                              (nuevo[0], nuevo[1], nuevo[2], None),
                              (nuevo[0], nuevo[1], None, mascara(original, nuevo))])
        png_simple.escribir(os.path.join(carpeta, familia + ".png"), hoja(filas_img))


def hojas_lakitu(carpeta):
    for fila in lakitu_es.leer_manifiesto():
        if not fila["png"]:
            continue
        pal = lakitu_es.paleta(fila)
        originales = lakitu_es.cuadros(fila)
        nuevos = lakitu_es.partir_tira(png_simple.leer(os.path.join(texturas_es.RAIZ, fila["png"])), fila)
        w, h = lakitu_es.ANCHO, lakitu_es.ALTO
        filas_img = [[(w, h, [pal[i] for i in c], None) for c in originales],
                     [(w, h, [pal[i] for i in c], None) for c in nuevos],
                     [(w, h, None, [a != b for a, b in zip(o, n)]) for o, n in zip(originales, nuevos)]]
        png_simple.escribir(os.path.join(carpeta, fila["id"] + ".png"), hoja(filas_img))


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    if len(argv) != 1:
        print(__doc__, file=sys.stderr)
        return 2
    os.makedirs(argv[0], exist_ok=True)
    try:
        hojas_familias(argv[0])
        hojas_lakitu(argv[0])
    except (ce.ErrorComposicion, texturas_es.ErrorManifiesto, lakitu_es.ErrorLakitu, png_simple.ErrorPng,
            OSError) as e:
        print("hojas_es: error: %s" % e, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
