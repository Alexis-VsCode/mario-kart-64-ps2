#!/usr/bin/env python3
"""Pruebas del generador de glifos del espanol (herramientas/generar_glifos_es.py)."""
import os
import subprocess
import sys
import tempfile

RAIZ = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))
sys.path.insert(0, os.path.join(RAIZ, "herramientas"))
import generar_glifos_es as g  # noqa: E402

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def generar_en(carpeta):
    subprocess.run([sys.executable, os.path.join(RAIZ, "herramientas", "generar_glifos_es.py"), carpeta], check=True)
    return {a: open(os.path.join(carpeta, a + ".i4"), "rb").read() for a in g.ARCHIVOS}


def filas_con_tinta(imagen):
    return [y for y, fila in enumerate(imagen) if any(fila)]


def columnas_con_tinta(imagen):
    return [x for x in range(g.ANCHO) if any(fila[x] for fila in imagen)]


def main():
    with tempfile.TemporaryDirectory() as a, tempfile.TemporaryDirectory() as b:
        primera, segunda = generar_en(a), generar_en(b)
    comprobar(primera == segunda, "dos ejecuciones dan bytes distintos")
    imagenes = g.generar()

    # Paso 1: tamanios
    for archivo, datos in primera.items():
        alto = g.ALTO_DIACRITICO if archivo.startswith("diacritico_") else g.ALTO_LETRA
        comprobar(len(datos) == g.ANCHO * alto // 2, "%s: %d bytes" % (archivo, len(datos)))

    # Paso 2: los signos quedan en las filas 2-5, sobre la parte alta de la letra
    for archivo, base, _ in g.DIACRITICOS:
        imagen = imagenes[archivo]
        filas = filas_con_tinta(imagen)
        comprobar(filas and min(filas) >= 2 and max(filas) <= 5, "%s: filas con tinta %s" % (archivo, filas))
        columnas = columnas_con_tinta(imagen)
        centro = (min(columnas) + max(columnas)) / 2.0
        letra = g.centro_superior(g.leer_i4("fuente_letra_" + base))
        comprobar(-2 <= centro - letra <= 5, "%s: centro %.1f, letra %.1f" % (archivo, centro, letra))
        comprobar(max(columnas) < g.COLUMNAS_VISIBLES, "%s: tinta en una columna que no se ve" % archivo)

    # Paso 3: los glifos de 26x16 no usan la fila 15 ni la columna 25 (no se ven)
    for archivo in [x[0] for x in g.GIRADOS + g.ORDINALES]:
        imagen = imagenes[archivo]
        comprobar(max(filas_con_tinta(imagen)) < g.FILAS_VISIBLES, "%s: tinta en la fila 15" % archivo)
        comprobar(max(columnas_con_tinta(imagen)) < g.COLUMNAS_VISIBLES, "%s: tinta en la columna 25" % archivo)

    # Paso 4: los signos de apertura son el ! y el ? girados, texel a texel
    for archivo, original in g.GIRADOS:
        o = g.leer_i4(original)
        x0, y0, x1, y1 = g.caja_tinta(o)
        girado = imagenes[archivo]
        iguales = all(girado[y][x] == o[y0 + y1 - y][x0 + x1 - x] for y in range(y0, y1 + 1) for x in range(x0, x1 + 1))
        comprobar(iguales, "%s no es el giro de %s" % (archivo, original))
        comprobar(g.caja_tinta(girado) == (x0, y0, x1, y1), "%s cambia de caja" % archivo)

    # Paso 5: el Makefile genera exactamente estos archivos
    r = subprocess.run(["make", "-s", "PS2SDK=/nada", "print-GLIFOS_ES_NOMBRES"], cwd=RAIZ, capture_output=True, text=True)
    comprobar(sorted(r.stdout.split()) == sorted(g.ARCHIVOS), "GLIFOS_ES_NOMBRES del Makefile no coincide")

    # Paso 6: los ordinales van arriba, a la mitad de alto, con subrayado
    for archivo, _ in g.ORDINALES:
        filas = filas_con_tinta(imagenes[archivo])
        comprobar(max(filas) <= 10, "%s: filas con tinta %s" % (archivo, filas))

    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
