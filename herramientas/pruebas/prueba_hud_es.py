#!/usr/bin/env python3
"""Las palabras del HUD en espanol: textura, superposicion, codigo y que no pisen nada.

    prueba_hud_es.py <carpeta build>   (despues de 'make es')

TIEMPO y VUELTA no entran en 32 columnas: sus texturas pasan a 64x16 y se
dibujan alineadas por la derecha donde terminaban las de 32 (PALABRA_HUD_X),
asi el borde que da a los digitos no se mueve. La textura chica de VUELTA
lleva debajo VTA., que es la que se usa con 3 y 4 jugadores. La prueba
comprueba que el build superpone los .inc.c en espanol (y que al invertir
los bytes se usan esos), que todo el codigo dibuja estas texturas con el
ancho nuevo, y que con 1 a 4 jugadores ninguna palabra pisa digitos, la
caja del item en 1 jugador ni se sale de su parte de la pantalla.
"""
import os
import re
import subprocess
import sys
import tempfile

RAIZ = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
sys.path.insert(0, os.path.join(RAIZ, "herramientas"))

import formatos_textura as ft  # noqa: E402
import png_simple  # noqa: E402
import texturas_es  # noqa: E402

TEXTURAS = "recursos/comunes/texturas/"
PALABRAS = {"tiempo_hud": "comun_textura_hud_tiempo", "tiempo_vuelta_hud": "comun_textura_hud_vuelta_tiempo",
            "vuelta_hud": "comun_textura_hud_vuelta"}
FUENTES_C = ["codigo/graficos/dibujar_objetos/ventana_item_y_minimapa.inc.c",
             "codigo/carrera/objetos_y_efectos/hud_pantalla_dividida.inc.c"]
INICIO_HUD = "codigo/carrera/inicio_hud_y_objetos/objetos_pista_y_hud_jugadores.inc.c"
HUD_ANIMADO = "codigo/carrera/objetos_y_efectos/hud_animado.inc.c"
ORDINALES = ("hud_1ro", "hud_2do", "hud_3ro", "hud_4to", "hud_5to", "hud_6to", "hud_7mo", "hud_8vo")
CAJA_ITEM_1J = (140, 16, 180, 48)   # 40x32 centrada en (0xA0, -0x20 + 0x40)

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def leer(ruta):
    return open(os.path.join(RAIZ, ruta)).read()


def probar_manifiesto(filas):
    """Paso 1: las tres palabras se traducen a 64x16 desde recursos/es/inc/; TOTAL queda."""
    por_id = {f["id"]: f for f in filas}
    for id_ in PALABRAS:
        f = por_id.get(id_, {})
        comprobar(f.get("tamanio_es") == "64x16" and f.get("png") == "recursos/es/inc/%s%s.rgba16.png" % (TEXTURAS, id_),
                  "%s: se espera tamanio_es 64x16 y su PNG en recursos/es/inc/" % id_)
    comprobar(por_id.get("tiempo_total_hud", {}).get("motivo_no"), "tiempo_total_hud (TOTAL) no se traduce")


def probar_ordinales(filas):
    """Paso 1b: 1st..8th pasan a 1.o..8.o (letra volada) en i4 128x64, desde recursos/es/inc/."""
    por_id = {f["id"]: f for f in filas}
    for n, id_ in enumerate(ORDINALES, 1):
        f = por_id.get(id_, {})
        comprobar(f.get("texto_es") == "%d.\u00ba" % n and f.get("formato") == "i4" and f.get("tamanio") == "128x64"
                  and f.get("png") == "recursos/es/inc/%s%s.i4.png" % (TEXTURAS, id_),
                  "%s: se espera %d.\u00ba en i4 128x64 desde recursos/es/inc/" % (id_, n))
    for id_ in ("primer_lugar", "segundo_lugar", "tercer_lugar", "cuarto_lugar"):
        comprobar(por_id.get(id_, {}).get("motivo_no") == "solo la cifra", "%s: solo tiene la cifra" % id_)


def probar_superposicion(filas, build):
    """Paso 2: make es deja los .inc.c en la ruta original y al invertir bytes se usan esos."""
    carpeta = os.path.join(build, "es")
    with tempfile.TemporaryDirectory() as tmp:
        r = subprocess.run([sys.executable, os.path.join(RAIZ, "herramientas", "invertir_texturas.py"), "--superponer",
                            carpeta, tmp, "codigo", "recursos"], cwd=RAIZ, capture_output=True, text=True)
        comprobar(r.returncode == 0, "invertir_texturas --superponer fallo: %s" % r.stderr.strip())
        for f in filas:
            if not f["png"].startswith("recursos/es/inc/"):
                continue
            generado = texturas_es.salida_build(f["png"], carpeta)
            comprobar(generado == os.path.join(carpeta, f["origen"]), "%s: no se superpone en %s" % (f["id"], f["origen"]))
            if not os.path.exists(generado):
                comprobar(False, "falta %s (make es)" % generado)
                continue
            datos, ancho = ft.leer_inc_c(open(generado).read())
            comprobar(datos == texturas_es.convertir(os.path.join(RAIZ, f["png"])), "%s: el .inc.c no da el PNG" % f["id"])
            comprobar(ancho == ft.leer_inc_c(leer(f["origen"]))[1], "%s: el .inc.c cambia de u8 a u16" % f["id"])
            invertido = os.path.join(tmp, f["origen"])
            # u8: no se invierte, el compilador la toma de $(BUILD)/es porque be/ no la tiene
            comprobar(ancho == 2 or not os.path.exists(invertido), "%s: be/ tapa la de es/" % f["id"])
            if ancho == 2 and os.path.exists(invertido):
                al_reves = bytes(b for i in range(0, len(datos), 2) for b in (datos[i + 1], datos[i]))
                comprobar(ft.leer_inc_c(open(invertido).read())[0] == al_reves, "%s: be/ no usa el espanol" % f["id"])
    make = leer("Makefile")
    comprobar(re.search(r"-I\$\(BUILD\)/be -I\$\(BUILD\)/es ", make), "INCLUDES: -I$(BUILD)/es va justo despues de be/")
    comprobar(re.search(r"invertir_texturas\.py --stamp \$@ --superponer \$\(BUILD\)/es", make),
              "el sello de bytes invertidos no superpone $(BUILD)/es")
    comprobar(re.search(r"^ES_SELLO := .*\$\(ES_INC\).*md5sum", make, re.M), "el sello de es/ no cambia con la lista")
    comprobar(re.search(r"^\$\(SWAP_STAMP\): .*\$\(ES_SELLO\)", make, re.M), "be/ no depende del sello de es/")
    comprobar(re.search(r"datos_comunes\.data\.o: \$\(ES_SELLO\)", make), "datos_comunes no depende del sello de es/")


def probar_codigo():
    """Paso 3: todo el codigo dibuja las palabras con el ancho nuevo."""
    usos = 0
    for ruta in FUENTES_C:
        for llamada in re.findall(r"\w+\([^;{}]*?\);", leer(ruta), re.S):
            if not any(re.search(r"\b%s\b" % s, llamada) for s in list(PALABRAS.values()) + ["PALABRA_HUD_VUELTA_CORTA"]):
                continue
            usos += 1
            comprobar("32x_hud" not in llamada and "PALABRA_HUD_ANCHO" in llamada,
                      "%s: se dibuja con el ancho viejo: %s" % (ruta, " ".join(llamada.split())[:90]))
    comprobar(usos >= 10, "se esperaban los usos de las palabras del HUD, hay %d" % usos)
    cabecera = leer("incluir/graficos/dibujar_objetos.h")
    comprobar("#define PALABRA_HUD_ANCHO 64" in cabecera and "#define PALABRA_HUD_X(x) ((x) - 16)" in cabecera,
              "faltan PALABRA_HUD_ANCHO y PALABRA_HUD_X en dibujar_objetos.h")
    comprobar("#define PALABRA_HUD_VUELTA_CORTA ((u8*) comun_textura_hud_vuelta + PALABRA_HUD_ANCHO * 8 * 2)" in cabecera,
              "PALABRA_HUD_VUELTA_CORTA tiene que apuntar a las filas 8 a 15 de la textura de VUELTA")


def valores(texto, jugador, campo):
    m = re.search(r"h_ud_jugador\[JUGADOR_%s\]\.%s = (-?0x[0-9A-Fa-f]+|-?\d+);" % (jugador, campo), texto)
    return int(m.group(1), 0) if m else None


def disposiciones():
    """Por modo: (region de pantalla, temporizador (x, y) o None, vuelta (x, y), modo de la vuelta)."""
    inicio = leer(INICIO_HUD)
    bloques = {n: inicio[inicio.index("void " + n):] for n in ("inicializar_vertical_jugador_hud_dos",
                                                              "inicializar_horizontal_jugador_hud_dos",
                                                              "inicializar_jugador_hud_tres_cuatro")}
    animado = leer(HUD_ANIMADO)
    ultimo = {c: int(re.findall(r"JUGADOR_UNO\]\.%s, (0x[0-9A-Fa-f]+)" % c, animado)[-1], 0)
              for c in ("temporizador_x", "vuelta_x")}
    uno = inicio[:inicio.index("void inicializar_vertical_jugador_hud_dos")]
    res = {"1 jugador": [((0, 0, 320, 240), (ultimo["temporizador_x"], valores(uno, "UNO", "temporizador_y")),
                          (ultimo["vuelta_x"], valores(uno, "UNO", "vuelta_y")), "simple")]}
    for nombre, clave, regiones, modo in (
            ("2 jugadores, pantalla vertical", "inicializar_vertical_jugador_hud_dos",
             [(0, 0, 160, 240), (160, 0, 320, 240)], "simple"),
            ("2 jugadores, pantalla horizontal", "inicializar_horizontal_jugador_hud_dos",
             [(0, 0, 320, 120), (0, 120, 320, 240)], "horizontal"),
            ("3 o 4 jugadores", "inicializar_jugador_hud_tres_cuatro",
             [(0, 0, 160, 120), (160, 0, 320, 120), (0, 120, 160, 240), (160, 120, 320, 240)], "cuatro")):
        texto = bloques[clave]
        lista = []
        for region, jugador in zip(regiones, ("UNO", "DOS", "TRES", "CUATRO")):
            tx, ty = valores(texto, jugador, "temporizador_x"), valores(texto, jugador, "temporizador_y")
            lista.append((region, (tx, ty) if modo != "cuatro" else None,
                          (valores(texto, jugador, "vuelta_x"), valores(texto, jugador, "vuelta_y")), modo))
        res[nombre] = lista
    return res


def extension(png, fila0, filas):
    """Rectangulo (x0, y0, x1, y1) de lo visible entre esas filas de un PNG."""
    img = png_simple.leer(png)
    px = img.a_rgba()
    puntos = [(x, y) for y in range(fila0, fila0 + filas) for x in range(img.ancho) if px[y * img.ancho + x][3]]
    if not puntos:
        return None
    return (min(p[0] for p in puntos), min(p[1] for p in puntos) - fila0,
            max(p[0] for p in puntos) + 1, max(p[1] for p in puntos) + 1 - fila0)


def mover(r, dx, dy):
    return (r[0] + dx, r[1] + dy, r[2] + dx, r[3] + dy) if r else None


def se_tocan(a, b):
    return a and b and a[0] < b[2] and b[0] < a[2] and a[1] < b[3] and b[1] < a[3]


def probar_geometria(filas):
    """Paso 4: con 1 a 4 jugadores ninguna palabra pisa digitos ni sale de su parte."""
    png = {f["id"]: os.path.join(RAIZ, f["png"]) for f in filas if f["id"] in PALABRAS}
    if not all(os.path.exists(p) for p in png.values()):
        comprobar(False, "faltan los PNG del HUD")
        return
    tiempo = extension(png["tiempo_hud"], 0, 16)
    tiempo_vuelta = extension(png["tiempo_vuelta_hud"], 0, 16)
    vuelta = extension(png["vuelta_hud"], 0, 8)
    corta = extension(png["vuelta_hud"], 8, 8)
    vuelta_cifras = ft.a_imagen("rgba16", ft.leer_inc_c(leer(TEXTURAS + "vuelta_1_hud_en_3.rgba16.inc.c"))[0], 32, 16)
    visibles = [(x, y) for y in range(16) for x in range(32) if vuelta_cifras.a_rgba()[y * 32 + x][3]]
    cifras = (min(p[0] for p in visibles), min(p[1] for p in visibles), max(p[0] for p in visibles) + 1,
              max(p[1] for p in visibles) + 1)
    for nombre, jugadores in disposiciones().items():
        dibujado = []
        for region, temporizador, (vx, vy), modo in jugadores:
            palabras, digitos = [], []
            if temporizador:
                tx, ty = temporizador
                digitos.append((tx, ty, tx + 64, ty + 16))
                for r in (tiempo, tiempo_vuelta):
                    palabras.append(("TIEMPO/VUELTA", mover(r, tx - 0x13 - 16 - 32, ty)))
            if modo == "simple":
                palabras.append(("VUELTA", mover(vuelta, vx - 16 - 32, vy + 3 - 4)))
                digitos.append(mover(cifras, vx + 0x1C - 16, vy - 8))
            elif modo == "horizontal":
                palabras.append(("VUELTA", mover(vuelta, vx - 16 - 32, vy - 4)))
                digitos.append((vx + 0xC, vy - 4, vx + 0xC + 24, vy + 4))
            else:
                palabras.append(("VTA.", mover(corta, vx - 32, vy - 4)))
                digitos.append((vx - 12, vy + 4, vx + 12, vy + 12))
            for texto, r in palabras:
                comprobar(r is not None, "%s: %s vacia" % (nombre, texto))
                comprobar(r and region[0] <= r[0] and r[2] <= region[2] and region[1] <= r[1] and r[3] <= region[3],
                          "%s: %s %r se sale de %r" % (nombre, texto, r, region))
                if nombre == "1 jugador":
                    comprobar(not se_tocan(r, CAJA_ITEM_1J), "%s: %s %r pisa la caja del item" % (nombre, texto, r))
            dibujado.append((palabras, digitos))
        todos = [d for _, ds in dibujado for d in ds]
        for palabras, _ in dibujado:
            for texto, r in palabras:
                for d in todos:
                    comprobar(not se_tocan(r, d), "%s: %s %r pisa los digitos %r" % (nombre, texto, r, d))
        for i, (palabras, _) in enumerate(dibujado):
            for otras, _ in dibujado[i + 1:]:
                for _, a in palabras:
                    for _, b in otras:
                        comprobar(not se_tocan(a, b), "%s: palabras de dos jugadores se pisan %r %r" % (nombre, a, b))


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    filas = texturas_es.leer_manifiesto(texturas_es.MANIFIESTO)
    probar_manifiesto(filas)
    probar_ordinales(filas)
    probar_superposicion(filas, os.path.abspath(sys.argv[1]))
    probar_codigo()
    probar_geometria(filas)
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
