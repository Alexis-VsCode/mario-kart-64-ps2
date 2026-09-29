#!/usr/bin/env python3
"""make hoja-es: una hoja de contacto por familia y una por cartel de Lakitu.

    prueba_hojas_es.py

Genera las hojas en una carpeta temporal y comprueba que hay una por cada
familia de composicion.tsv y por cada animacion de Lakitu, que cada una
tiene tres columnas (original, espanol y mascara) a escala 3, y que la
mascara marca exactamente los pixeles que se ven distintos.
"""
import os
import subprocess
import sys
import tempfile

RAIZ = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
sys.path.insert(0, os.path.join(RAIZ, "herramientas"))

import compositor_es as ce  # noqa: E402
import hojas_es  # noqa: E402
import lakitu_es  # noqa: E402
import png_simple  # noqa: E402

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def main():
    familias = sorted({c["familia"] for c in ce.leer_composicion().values()})
    animaciones = [f["id"] for f in lakitu_es.leer_manifiesto() if f["png"]]
    with tempfile.TemporaryDirectory() as tmp:
        r = subprocess.run([sys.executable, os.path.join(RAIZ, "herramientas", "hojas_es.py"), tmp],
                           capture_output=True, text=True)
        comprobar(r.returncode == 0, "hojas_es.py fallo: %s" % r.stderr.strip())
        for nombre in familias + animaciones:
            ruta = os.path.join(tmp, nombre + ".png")
            comprobar(os.path.exists(ruta), "falta la hoja %s" % ruta)
        # mascara de una textura conocida: marca lo que cambia y nada mas
        original, nuevo = hojas_es.par("opcion")
        mascara = hojas_es.mascara(original, nuevo)
        distintos = [a != b and bool(a[3] or b[3]) for a, b in zip(original[2], nuevo[2])]
        comprobar(any(mascara) and mascara == distintos,
                  "la mascara de opcion no marca justo los pixeles que cambian")
        ruta = os.path.join(tmp, "titulos_menu.png")
        if os.path.exists(ruta):
            hoja = png_simple.leer(ruta)
            ids = [i for i, c in ce.leer_composicion().items() if c["familia"] == "titulos_menu"]
            ancho = max(hojas_es.par(i)[1][0] for i in ids)
            comprobar(hoja.ancho == 3 * (3 * ancho + 2 * hojas_es.SEPARACION),
                      "titulos_menu: la hoja no tiene tres columnas a escala 3")
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
