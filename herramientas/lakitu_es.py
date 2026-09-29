#!/usr/bin/env python3
"""Carteles de Lakitu en espanol: 16 cuadros ci8 de 72x56 con la paleta original.

    lakitu_es.py componer [--solo ID ...]        reescribe los PNG de recursos/es/lakitu/
    lakitu_es.py partir <id>.ci8.png <carpeta>   los 16 .bin en <carpeta>/<carpeta del cuadro>/

recursos/es/lakitu/lakitu.tsv tiene una fila por animacion: carpeta y patron de los
cuadros, paleta (tlut), color de la placa, cuadro plano de referencia, la composicion
de ese cuadro (familia, caja, texto_en, x_en, opciones como en composicion.tsv), el
texto en espanol y el PNG (una tira de 16 cuadros, indexada con la paleta original).

El cuadro plano se compone con compositor_es (glifos del propio cuadro). Los demas
salen de ese: por cuadro se busca la banda del texto en ingles (dentro de la placa),
se lleva la del cuadro plano a esa banda (escala por eje) y cada color del plano se
cambia por el que tiene el mismo sitio en ese cuadro (asi siguen el giro, la sombra y
el parpadeo). Solo cambian los pixeles de texto (en ingles o en espanol) de la placa:
la mascara es la diferencia perceptual con la placa, y lo que no es cartel (Lakitu,
su mano, la nube) queda igual. La paleta no cambia.
"""
import argparse
import os
import sys
from collections import Counter

import formatos_textura as ft
import png_simple
import texturas_es

RAIZ = texturas_es.RAIZ
MANIFIESTO = os.path.join(RAIZ, "recursos", "es", "lakitu", "lakitu.tsv")
COLUMNAS = ["id", "carpeta", "patron", "tlut", "placa", "plano", "familia", "caja", "texto_en", "x_en", "opciones",
            "texto_es", "png", "motivo_no"]
ANCHO, ALTO, CUADROS = 72, 56, 16
CANAL = {"rojo": 0, "verde": 1, "azul": 2}


class ErrorLakitu(ValueError):
    pass


def leer_manifiesto(ruta=MANIFIESTO):
    filas = []
    with open(ruta, encoding="utf-8") as f:
        lineas = [l.rstrip("\n") for l in f if l.strip() and not l.startswith("#")]
    if not lineas or lineas[0].split("\t") != COLUMNAS:
        raise ErrorLakitu("%s: cabecera distinta de %s" % (ruta, " ".join(COLUMNAS)))
    for linea in lineas[1:]:
        valores = linea.split("\t")
        valores += [""] * (len(COLUMNAS) - len(valores))  # columnas vacias al final
        if len(valores) != len(COLUMNAS):
            raise ErrorLakitu("%s: fila con %d columnas: %s" % (ruta, len(valores), linea))
        filas.append(dict(zip(COLUMNAS, valores)))
    return filas


def fila_de(id_):
    for f in leer_manifiesto():
        if f["id"] == id_:
            return f
    raise ErrorLakitu("%s no esta en %s" % (id_, MANIFIESTO))


def ruta_cuadro(fila, n):
    return os.path.join(RAIZ, "recursos", "texturas", "lakitu", fila["carpeta"], fila["patron"] % n)


def paleta(fila):
    with open(os.path.join(RAIZ, "recursos", "comunes", "texturas", fila["tlut"])) as f:
        datos = ft.leer_inc_c(f.read())[0]
    return [ft.rgba16_a_rgba((datos[i] << 8) | datos[i + 1]) for i in range(0, len(datos), 2)]


def cuadros(fila):
    """Indices de los 16 cuadros originales."""
    res = []
    for n in range(1, CUADROS + 1):
        with open(ruta_cuadro(fila, n), "rb") as f:
            datos = f.read()
        if len(datos) != ANCHO * ALTO:
            raise ErrorLakitu("%s mide %d bytes" % (ruta_cuadro(fila, n), len(datos)))
        res.append(datos)
    return res


def textura_cuadro(id_textura):
    """(ancho, alto, rgba) de un cuadro por su nombre de archivo (lakitu_reversa_05), para el compositor."""
    for fila in leer_manifiesto():
        for n in range(1, CUADROS + 1):
            if os.path.splitext(fila["patron"] % n)[0] == id_textura:
                pal = paleta(fila)
                return ANCHO, ALTO, [pal[i] for i in cuadros(fila)[n - 1]]
    return None


# --- Mascaras -------------------------------------------------------------------------

def es_texto(p):
    """Texto del cartel: poco saturado (blanco, gris, rosa claro) frente a la placa."""
    mx, mn = max(p[:3]), min(p[:3])
    return p[3] and mx > 60 and (mx - mn) / mx < 0.45


def es_placa(p, canal):
    otros = [p[k] for k in range(3) if k != canal]
    return p[3] and p[canal] > 50 and max(otros) < 0.55 * p[canal]


def es_lakitu(p):
    """Amarillo o naranja de Lakitu y su mano: nunca se toca."""
    return p[3] and p[0] > 150 and p[1] > 80 and p[2] < 110


def zona(rgba, canal):
    """(x0, y0, x1, y1) de la placa (filas con al menos 12 pixeles de placa), o None."""
    filas = [y for y in range(ALTO) if sum(es_placa(rgba[y * ANCHO + x], canal) for x in range(ANCHO)) >= 12]
    if not filas:
        return None
    y0, y1 = filas[0], filas[-1] + 1
    xs = [x for y in range(y0, y1) for x in range(ANCHO) if es_placa(rgba[y * ANCHO + x], canal)]
    return min(xs), y0, max(xs) + 1, y1


def mascara_texto(rgba, z):
    """Pixeles de texto de la placa: poco saturados y claros para ese cuadro (el giro los oscurece)."""
    x0, y0, x1, y1 = z
    candidatos = {(x, y): rgba[y * ANCHO + x] for y in range(y0, y1) for x in range(x0, x1)
                  if es_texto(rgba[y * ANCHO + x])}
    if len(candidatos) >= 8:
        tope = max(min(p[:3]) for p in candidatos.values())
        return {k for k, p in candidatos.items() if min(p[:3]) >= 0.4 * tope}
    # placa apagada (el parpadeo de REVERSE): el texto es lo que brilla mas que la placa
    valores = {(x, y): max(rgba[y * ANCHO + x][:3]) for y in range(y0, y1) for x in range(x0, x1)
               if rgba[y * ANCHO + x][3] and not es_lakitu(rgba[y * ANCHO + x])}
    if not valores:
        return set()
    lista = sorted(valores.values())
    fondo, tope = lista[len(lista) // 4], lista[-1]
    umbral = fondo + max(20, 0.4 * (tope - fondo))
    return {k for k, v in valores.items() if v >= umbral}


def color_placa(rgba, z, y, canal):
    """Color de la placa en una fila (el mas frecuente de los de placa)."""
    fila = [rgba[y * ANCHO + x] for x in range(z[0], z[2]) if es_placa(rgba[y * ANCHO + x], canal)]
    return max(sorted(set(fila)), key=fila.count) if fila else None


def distinto(p, q):
    return q is None or sum((a - b) ** 2 for a, b in zip(p[:3], q[:3])) > 900


def ajustar(pf, pr):
    """[a, b) de pf que mejor se parece a todo pr estirado (perfiles normalizados)."""
    tf, tr = float(max(pf) or 1), float(max(pr) or 1)
    f, r = [v / tf for v in pf], [v / tr for v in pr]
    mejor = None
    for a in range(len(f)):
        for b in range(a + 2, len(f) + 1):
            costo = sum(f[:a]) + sum(f[b:])
            for i in range(a, b):
                costo += abs(f[i] - r[min(len(r) - 1, int((i - a + 0.5) * len(r) / (b - a)))])
            if mejor is None or costo < mejor[0]:
                mejor = (costo, a, b)
    return mejor[1], mejor[2]


def banda_plano(mascara):
    """Caja del texto del cuadro plano."""
    xs, ys = [x for x, _ in mascara], [y for _, y in mascara]
    return min(xs), min(ys), max(xs) + 1, max(ys) + 1


def banda(mascara, z, mascara_plano, b_plano, z_plano):
    """Caja del texto de un cuadro. En x, la del plano estirada como la placa; en y, las
    filas de la placa cuyo perfil (pixeles de texto por fila) mas se parece al del plano."""
    x0, y0, x1, y1 = z
    px0, py0, px1, py1 = b_plano
    escala = (x1 - x0) / float(z_plano[2] - z_plano[0])
    bx0 = x0 + int(round((px0 - z_plano[0]) * escala))
    bx1 = x0 + int(round((px1 - z_plano[0]) * escala))
    pf = [sum((x, y) in mascara for x in range(x0, x1)) for y in range(y0, y1)]
    pr = [sum((x, y) in mascara_plano for x in range(px0, px1)) for y in range(py0, py1)]
    ay, by = ajustar(pf, pr)
    return bx0, y0 + ay, bx1, y0 + by


# --- Composicion ----------------------------------------------------------------------

def cuantizar_a_paleta(rgba, originales, pal, usados):
    """Indice de cada pixel: el original si el color no cambio, si no el mas cercano de 'usados'."""
    res = bytearray(originales)
    cache = {}
    for i, p in enumerate(rgba):
        if pal[originales[i]] == p:
            continue
        if p not in cache:
            cache[p] = min(usados, key=lambda k: (sum((a - b) ** 2 for a, b in zip(pal[k][:3], p[:3])), k))
        res[i] = cache[p]
    return bytes(res)


def plano_espanol(fila, originales, pal):
    """Indices del cuadro plano con el texto en espanol."""
    import compositor_es as ce
    n = int(fila["plano"])
    id_textura = os.path.splitext(fila["patron"] % n)[0]
    comp = {k: fila[k] for k in ("familia", "caja", "texto_en", "x_en", "opciones")}
    destino = ce.Textura.cargar(id_textura)
    rgba = ce.componer(id_textura, fila["texto_es"], comp, destino)
    cx, cy, cw, ch = ce.area_de(comp)
    usados = sorted({originales[y * ANCHO + x] for y in range(cy, cy + ch) for x in range(cx, cx + cw)})
    return cuantizar_a_paleta(rgba, originales, pal, usados)


def llevar(b_origen, b_destino, x, y):
    """Punto (x, y) de la banda destino llevado a la banda origen."""
    ox0, oy0, ox1, oy1 = b_origen
    dx0, dy0, dx1, dy1 = b_destino
    sx = (ox1 - ox0) / float(dx1 - dx0)
    sy = (oy1 - oy0) / float(dy1 - dy0)
    return (min(ANCHO - 1, max(0, int(ox0 + (x - dx0 + 0.5) * sx))),
            min(ALTO - 1, max(0, int(oy0 + (y - dy0 + 0.5) * sy))))


def filas_llevadas(b_origen, b_destino, y0, y1):
    """Filas del destino que caen en las filas [y0, y1) del origen."""
    sy = (b_origen[3] - b_origen[1]) / float(b_destino[3] - b_destino[1])
    a = b_destino[1] + int((y0 - b_origen[1]) / sy)
    b = b_destino[1] + int((y1 - b_origen[1]) / sy + 0.999)
    return a, b


def trasladar(mascara, mascara_plano, b_plano):
    """Cartel del mismo tamanio que el plano (solo se mueve): el corrimiento que mas
    pixeles de texto hace coincidir."""
    mejor = max(((sum((x + dx, y + dy) in mascara for x, y in mascara_plano), -abs(dx) - abs(dy), dx, dy)
                 for dx in range(-3, 4) for dy in range(-3, 4)))
    dx, dy = mejor[2], mejor[3]
    return b_plano[0] + dx, b_plano[1] + dy, b_plano[2] + dx, b_plano[3] + dy


def cuadro_espanol(ingles, plano_en, plano_es, contexto, pal, canal):
    """Un cuadro con el texto del plano en espanol llevado a su banda."""
    mascara_plano, b_plano, z_plano, _ = contexto
    rgba = [pal[i] for i in ingles]
    z = zona(rgba, canal)
    mascara = mascara_texto(rgba, z) if z else set()
    if len(mascara) < 8:
        return ingles
    if abs((z[2] - z[0]) - (z_plano[2] - z_plano[0])) <= 3 and abs((z[3] - z[1]) - (z_plano[3] - z_plano[1])) <= 3:
        b = trasladar(mascara, mascara_plano, b_plano)
    else:
        b = banda(mascara, z, mascara_plano, b_plano, z_plano)
    rgba_en = [pal[i] for i in plano_en]
    rgba_es = [pal[i] for i in plano_es]
    pares = {}
    lugares = []
    # tambien las filas del espanol que salen de la banda del ingles (tildes)
    # y todo el texto en ingles del cuadro, aunque quede fuera de la banda
    ya, yb = filas_llevadas(b_plano, b, *contexto_filas(contexto))
    mx0, my0, mx1, my1 = banda_plano(mascara)
    for y in range(max(z[1], min(b[1], ya, my0)), min(z[3], max(b[3], yb, my1))):
        for x in range(max(z[0], min(b[0], mx0)), min(z[2], max(b[2], mx1))):
            xp, yp = llevar(b_plano, b, x, y)
            pares.setdefault(plano_en[yp * ANCHO + xp], Counter())[ingles[y * ANCHO + x]] += 1
            lugares.append((x, y, xp, yp))
    tabla = {k: c.most_common(1)[0][0] for k, c in pares.items()}
    claves = sorted(tabla)
    res = bytearray(ingles)
    for x, y, xp, yp in lugares:
        i, ip = y * ANCHO + x, yp * ANCHO + xp
        if es_lakitu(rgba[i]):
            continue
        fondo, fondo_plano = color_placa(rgba, z, y, canal), color_placa(rgba_en, z_plano, yp, canal)
        if not (distinto(rgba[i], fondo) or distinto(rgba_es[ip], fondo_plano) or distinto(rgba_en[ip], fondo_plano)):
            continue
        nuevo = plano_es[ip]
        if nuevo not in tabla:
            nuevo = min(claves, key=lambda k: (sum((a - b) ** 2 for a, b in zip(pal[k][:3], pal[nuevo][:3])), k))
        res[i] = tabla[nuevo]
    return bytes(res)


def contexto_filas(contexto):
    return contexto[3]


def animacion_espanol(fila):
    """Los 16 cuadros en espanol (indices)."""
    pal = paleta(fila)
    originales = cuadros(fila)
    canal = CANAL[fila["placa"]]
    n = int(fila["plano"])
    plano_en = originales[n - 1]
    plano_es = plano_espanol(fila, plano_en, pal)
    rgba = [pal[i] for i in plano_en]
    z_plano = zona(rgba, canal)
    mascara_plano = mascara_texto(rgba, z_plano)
    mascara_es = mascara_texto([pal[i] for i in plano_es], z_plano)
    ys = [y for _, y in mascara_es] or [0]
    contexto = (mascara_plano, banda_plano(mascara_plano), z_plano, (min(ys), max(ys) + 1))
    res = []
    for k, ingles in enumerate(originales, 1):
        if k == n:
            res.append(bytes(i if es_lakitu(pal[i]) else j for i, j in zip(ingles, plano_es)))
        else:
            res.append(cuadro_espanol(ingles, plano_en, plano_es, contexto, pal, canal))
    return res


def tira(fila, lista):
    """Imagen indexada de 16 cuadros en fila, con la paleta original."""
    datos = bytearray()
    for y in range(ALTO):
        for c in lista:
            datos += c[y * ANCHO:(y + 1) * ANCHO]
    return png_simple.Imagen(ANCHO * CUADROS, ALTO, "indexado", bytes(datos), paleta(fila))


def partir_tira(imagen, fila):
    """Los 16 cuadros de una tira; exige la paleta original."""
    if imagen.tipo != "indexado" or (imagen.ancho, imagen.alto) != (ANCHO * CUADROS, ALTO):
        raise ErrorLakitu("la tira tiene que ser indexada de %dx%d" % (ANCHO * CUADROS, ALTO))
    if [tuple(c) for c in imagen.paleta] != [tuple(c) for c in paleta(fila)]:
        raise ErrorLakitu("la tira no usa la paleta original (%s)" % fila["tlut"])
    return [bytes(b for y in range(ALTO) for b in imagen.pixeles[y * ANCHO * CUADROS + n * ANCHO:
                                                                y * ANCHO * CUADROS + (n + 1) * ANCHO])
            for n in range(CUADROS)]


def componer(args):
    for fila in leer_manifiesto():
        if fila["motivo_no"] or (args.solo and fila["id"] not in args.solo):
            continue
        ruta = os.path.join(RAIZ, fila["png"])
        os.makedirs(os.path.dirname(ruta), exist_ok=True)
        png_simple.escribir(ruta, tira(fila, animacion_espanol(fila)))
        print("%s: %s" % (fila["id"], fila["texto_es"]))
    return 0


def partir(args):
    nombre = os.path.basename(args.png)
    id_ = nombre.split(".")[0]
    fila = fila_de(id_)
    lista = partir_tira(png_simple.leer(args.png), fila)
    carpeta = os.path.join(args.carpeta, fila["carpeta"])
    os.makedirs(carpeta, exist_ok=True)
    for n, datos in enumerate(lista, 1):
        destino = os.path.join(carpeta, fila["patron"] % n)
        if not os.path.exists(destino) or open(destino, "rb").read() != datos:
            with open(destino, "wb") as f:
                f.write(datos)
    return 0


def main(argv=None):
    parser = argparse.ArgumentParser(description="Carteles de Lakitu en espanol")
    sub = parser.add_subparsers(dest="orden", required=True)
    p = sub.add_parser("componer")
    p.add_argument("--solo", nargs="*")
    p.set_defaults(funcion=componer)
    p = sub.add_parser("partir")
    p.add_argument("png")
    p.add_argument("carpeta")
    p.set_defaults(funcion=partir)
    args = parser.parse_args(argv)
    try:
        return args.funcion(args)
    except (ErrorLakitu, ft.ErrorFormato, png_simple.ErrorPng, OSError) as e:
        print("lakitu_es: error: %s" % e, file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
