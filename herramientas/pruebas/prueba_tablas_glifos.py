#!/usr/bin/env python3
"""La tabla de texturas de glifos tiene que cubrir todos los glifos.

    prueba_tablas_glifos.py <lista_glifos.inc.c>

car_a_indice_glifo devuelve indices de 0 a 235 (ancho_pantalla_glifo tiene
236 anchos). En la N64 lut_textura_glifo tenia 91 entradas y el resto
seguia en los arreglos que el enlazador ponia a continuacion; en PS2 ese
orden no se cumple. La tabla tiene que tener las 236 entradas por si misma.
"""
import re
import sys

GLIFOS_TOTAL = 236

# Indice -> textura, sacado del orden de la N64 (direcciones 0x800E7E84..0x800E8234)
FIJOS = {
    0: "seg_2_textura_fuente_letra_a",
    90: "dato_020031AC",
    91: "dato_02003274",
    134: "dato_02003BD4",
    135: "dato_02003594",
    164: "dato_020037C4",
    188: "dato_020039F4",
    190: "dato_02003A1C",
    212: "dato_02004124",   # ー
    216: "dato_020041C4",
    225: "dato_020043A4",   # sufijo ND
    228: "dato_02004494",   # sufijo ST
    234: "seg_2_textura_fuente_coma",
    235: "dato_0200455C",
}

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def glifos(texto):
    """Pares (textura, ancho) de las lineas GLIFO(textura, ancho)."""
    return re.findall(r"^GLIFO\(\s*(\w+)\s*,\s*(\w+)\s*\)", texto, re.M)


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    texto = open(sys.argv[1], encoding="utf-8").read()
    lista = glifos(texto)
    lut = [textura for textura, _ in lista]
    anchos = [ancho for _, ancho in lista]
    comprobar(anchos is not None and len(anchos) == GLIFOS_TOTAL, "ancho_pantalla_glifo: %s anchos" % (anchos and len(anchos)))
    comprobar(lut is not None and len(lut) == GLIFOS_TOTAL, "lut_textura_glifo: %s texturas" % (lut and len(lut)))
    if lut:
        for indice, textura in sorted(FIJOS.items()):
            obtenida = lut[indice] if indice < len(lut) else None
            comprobar(obtenida == textura, "lut_textura_glifo[%d] = %s, se esperaba %s" % (indice, obtenida, textura))
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
