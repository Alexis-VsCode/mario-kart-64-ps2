#!/usr/bin/env python3
"""La tabla de texturas de glifos tiene que cubrir todos los glifos.

    prueba_tablas_glifos.py <lista_glifos.inc.c>

car_a_indice_glifo devuelve indices de 0 a 235 (ancho_pantalla_glifo tiene
236 anchos). En la N64 lut_textura_glifo tenia 91 entradas y el resto
seguia en los arreglos que el enlazador ponia a continuacion; en PS2 ese
orden no se cumple. La tabla tiene que tener las 236 entradas por si misma.

Ademas, lut_textura_glifo se define una sola vez, desde la lista GLIFO y fuera
de todo #if, sin alias de las tablas en que la N64 la partia: con otra
definicion para AVOID_UB los glifos del espanol leen fuera de la tabla.

Las letras se dibujan con matrices de la reserva efecto_mtx: bajo AVOID_UB,
funcion_80095BD0 deja de cargar matrices al llegar al tamanio de la reserva.
"""
import glob
import os
import re
import sys

RAIZ = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))
TABLAS = os.path.join(RAIZ, "codigo", "menus", "elementos_menu", "textos_y_tablas.inc.c")
CABECERA_MENU = os.path.join(RAIZ, "incluir", "menus", "elementos_menu.h")
CARGAR_TEXTURAS = os.path.join(RAIZ, "codigo", "menus", "elementos_menu", "cargar_texturas_menu.inc.c")
BUCLE_PRINCIPAL = os.path.join(RAIZ, "incluir", "sistema", "bucle_principal.h")
TAMANIO_RESERVA = "MTX_EFECTO_POOL_TAMANIO"
ALTO_DIACRITICO = 8

GLIFOS_ORIGINALES = 236
GLIFOS_TOTAL = GLIFOS_ORIGINALES + 11

# Tablas de la N64 que siguen a lut_textura_glifo (dato_800E7FF0..dato_800E822C):
# aqui son parte de ella y no tienen nombre propio
TABLAS_PARTIDAS = (0x800E7FF0, 0x800E822C)

# Cuerpo de lut_textura_glifo: solo la lista GLIFO
CUERPO_LUT = [r"#\s*define\s+GLIFO\(\s*(\w+)\s*,\s*\w+\s*\)\s+(\w+)\s*,",
              r'#\s*include\s+"lista_glifos\.inc\.c"',
              r"#\s*undef\s+GLIFO"]

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
    # del espanol, en el orden de CaracterEs (incluir/sistema/caracteres_es.h)
    0xEC: "seg_2_textura_fuente_es_a_aguda",
    0xED: "seg_2_textura_fuente_es_e_aguda",
    0xEE: "seg_2_textura_fuente_es_i_aguda",
    0xEF: "seg_2_textura_fuente_es_o_aguda",
    0xF0: "seg_2_textura_fuente_es_u_aguda",
    0xF1: "seg_2_textura_fuente_es_enie",
    0xF2: "seg_2_textura_fuente_es_u_dieresis",
    0xF3: "seg_2_textura_fuente_es_abre_exclamacion",
    0xF4: "seg_2_textura_fuente_es_abre_interrogacion",
    0xF5: "seg_2_textura_fuente_es_ordinal_o",
    0xF6: "seg_2_textura_fuente_es_ordinal_a",
}

# Glifo nuevo -> glifo original del que toma el ancho (la letra o el signo base)
MISMO_ANCHO = {0xEC: 0, 0xED: 4, 0xEE: 8, 0xEF: 14, 0xF0: 20, 0xF1: 13, 0xF2: 20, 0xF3: 0x1A, 0xF4: 0x1C}

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


def partes_texturas_menu():
    """Nombre de cada TexturaMenu de codigo/datos/texturas -> lista de (ancho, alto) de sus partes."""
    partes = {}
    for ruta in glob.glob(os.path.join(RAIZ, "codigo", "datos", "texturas", "*.inc.c")):
        texto = open(ruta, encoding="utf-8").read()
        for nombre, cuerpo in re.findall(r"TexturaMenu (\w+)\[\d*\] = \{(.*?)\n\};", texto, re.S):
            filas = re.findall(r"\{\s*\d+,\s*(\w+),\s*(\d+),\s*(\w+),", cuerpo)
            partes[nombre] = [(int(a), alto) for datos, a, alto in filas if datos != "NULL"]
    return partes


def probar_partes_de_signo(lut):
    """imprimir_letra toma las partes de alto ALTO_DIACRITICO por el signo de una letra:
    solo pueden estar en segundo lugar en los glifos del espanol."""
    partes = partes_texturas_menu()
    for indice, nombre in enumerate(lut):
        lista = partes.get(nombre)
        comprobar(lista is not None, "no se encuentra la TexturaMenu %s" % nombre)
        if not lista:
            continue
        for orden, (ancho, alto) in enumerate(lista):
            if alto in ("ALTO_DIACRITICO", str(ALTO_DIACRITICO)):
                valida = indice >= GLIFOS_ORIGINALES and orden == 1 and ancho == 26
                comprobar(valida, "%s: parte %d de alto %s fuera de un glifo del espanol" % (nombre, orden, alto))


def probar_definicion_unica():
    """lut_textura_glifo: una definicion, fuera de todo #if y hecha con la lista GLIFO."""
    lineas = open(TABLAS, encoding="utf-8").read().split("\n")
    abiertos = 0
    definiciones = []
    for numero, linea in enumerate(lineas):
        linea = linea.strip()
        if re.match(r"#\s*if", linea):
            abiertos += 1
        elif re.match(r"#\s*endif", linea):
            abiertos -= 1
        elif re.match(r"TexturaMenu\s*\*\s*lut_textura_glifo\s*\[", linea):
            definiciones.append((numero, abiertos))
    comprobar(len(definiciones) == 1, "textos_y_tablas.inc.c define lut_textura_glifo %d veces" % len(definiciones))
    for numero, abierto in definiciones:
        comprobar(abierto == 0, "textos_y_tablas.inc.c:%d: lut_textura_glifo dentro de un #if" % (numero + 1))
        cuerpo = []
        for linea in lineas[numero + 1:]:
            if linea.startswith("};"):
                break
            if linea.strip() and not linea.strip().startswith("//"):
                cuerpo.append(linea.strip())
        coincide = [re.fullmatch(patron, linea) for patron, linea in zip(CUERPO_LUT, cuerpo)]
        valida = len(cuerpo) == len(CUERPO_LUT) and all(coincide) and coincide[0].group(1) == coincide[0].group(2)
        comprobar(valida, "textos_y_tablas.inc.c:%d: lut_textura_glifo no sale solo de la lista GLIFO" % (numero + 1))


def probar_sin_tablas_partidas():
    """Ni la tabla ni la cabecera nombran las partes de lut_textura_glifo de la N64."""
    for ruta in (TABLAS, CABECERA_MENU):
        texto = open(ruta, encoding="utf-8").read()
        for nombre, direccion in sorted(set(re.findall(r"\b(dato_([0-9A-F]{8}))\b", texto))):
            dentro = TABLAS_PARTIDAS[0] <= int(direccion, 16) <= TABLAS_PARTIDAS[1]
            comprobar(not dentro, "%s nombra %s, que es parte de lut_textura_glifo" % (os.path.relpath(ruta, RAIZ), nombre))


def probar_tope_reserva():
    """Bajo AVOID_UB el tope de funcion_80095BD0 es el tamanio con que se declara efecto_mtx."""
    texto = open(CARGAR_TEXTURAS, encoding="utf-8").read()
    funcion = re.search(r"^Gfx\* funcion_80095BD0\(.*?^}", texto, re.S | re.M)
    comprobar(funcion is not None, "no se encuentra funcion_80095BD0")
    rama = re.search(r"#ifdef AVOID_UB\n(.*?)#else", funcion.group(0), re.S) if funcion else None
    topes = re.findall(r"cantidad_efecto_matriz\s*>=\s*(\w+)", rama.group(1)) if rama else []
    comprobar(topes == [TAMANIO_RESERVA], "funcion_80095BD0: bajo AVOID_UB el tope es %s, se esperaba %s"
              % (", ".join(topes) or "ninguno", TAMANIO_RESERVA))
    reserva = re.findall(r"\bMtx\s+efecto_mtx\s*\[\s*(\w+)\s*\]", open(BUCLE_PRINCIPAL, encoding="utf-8").read())
    comprobar(reserva == [TAMANIO_RESERVA], "efecto_mtx se declara con %s matrices, se esperaba %s"
              % (", ".join(reserva) or "ninguna declaracion", TAMANIO_RESERVA))


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
        probar_partes_de_signo(lut)
        for nuevo, base in sorted(MISMO_ANCHO.items()):
            if nuevo < len(anchos):
                comprobar(anchos[nuevo] == anchos[base], "el glifo 0x%02X tiene que medir como el 0x%02X" % (nuevo, base))
    probar_definicion_unica()
    probar_sin_tablas_partidas()
    probar_tope_reserva()
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
