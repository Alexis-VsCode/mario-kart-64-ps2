#!/usr/bin/env python3
"""Pruebas de texturas_es.py y del manifiesto recursos/es/texturas.tsv.

    prueba_texturas_es.py <herramienta tkmk00>

El manifiesto lista las 63 texturas TKMK00 con el alfa que usa el juego y
el motivo de las que no se traducen. Exportar e importar cada una da
exactamente los bytes originales decodificados (SHA-1 de
referencias_tkmk00.txt); comprobar rechaza PNG que no sirven y la hoja de
contacto marca solo lo que cambio.
"""
import contextlib
import hashlib
import io
import os
import subprocess
import sys
import tempfile

RAIZ = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
sys.path.insert(0, os.path.join(RAIZ, "herramientas"))

import png_simple  # noqa: E402
import texturas_es  # noqa: E402

MANIFIESTO = os.path.join(RAIZ, "recursos", "es", "texturas.tsv")
REFERENCIAS = os.path.join(RAIZ, "herramientas", "pruebas", "referencias_tkmk00.txt")
CARPETA_TKMK00 = "recursos/texturas/menus/tkmk00"
NO_SE_TRADUCEN = ["nombre_bowser", "nombre_dk", "nombre_luigi", "nombre_mario", "nombre_peach", "nombre_toad",
                  "nombre_wario", "nombre_yoshi", "50cc", "100cc", "150cc", "extra", "modo_vs", "menu_con_item",
                  "menu_sin_item", "cielo_azul_fondo", "atardecer_fondo", "barra_oro", "barra_rosa",
                  "franja_blanco", "franja_oro", "franja_oro_verde"]

# Pantalla del Controller Pak: el port no la abre
CONTROLLER_PAK = ["n64_controller_pak_seleccion_datos", "borrar_datos_registro_confirmacion", "registro_no_borrado",
                  "lugar_n64_controller_pak_en_mando_1", "original_n64_reinsertar_por_favor_controller_pak",
                  "registro_seleccionado_borrando", "registro_seleccion", "fin_texto", "tabla_de_contenido",
                  "hash_texto", "datos_juego_texto", "paginas_texto", "libre_paginas_texto", "borrar_texto",
                  "abandonar_texto"]

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def ejecutar(*args):
    """(codigo, salida, errores) de texturas_es.main sin ensuciar la salida de la prueba."""
    salida, errores = io.StringIO(), io.StringIO()
    with contextlib.redirect_stdout(salida), contextlib.redirect_stderr(errores):
        try:
            codigo = texturas_es.main(list(args))
        except SystemExit as e:
            codigo = e.code
    return codigo, salida.getvalue(), errores.getvalue()


def leer_referencias():
    refs = {}
    for linea in open(REFERENCIAS):
        if linea.strip() and not linea.startswith("#"):
            nombre, _, _, alfa, sha1 = linea.split()
            refs[nombre] = (alfa, sha1)
    return refs


def filas_tkmk00(filas):
    return [f for f in filas if f["origen"].startswith(CARPETA_TKMK00 + "/")]


def probar_manifiesto(filas, refs):
    """Paso 1: una fila por textura TKMK00, con el alfa del juego y los motivos del diseno."""
    tkmk00 = filas_tkmk00(filas)
    comprobar(len(tkmk00) == 63, "se esperaban 63 filas TKMK00, hay %d" % len(tkmk00))
    origenes = sorted(os.path.basename(f["origen"]) for f in tkmk00)
    comprobar(origenes == sorted(refs), "el manifiesto no lista las mismas texturas que %s" % CARPETA_TKMK00)
    por_id = {f["id"]: f for f in filas}
    for f in tkmk00:
        nombre = os.path.basename(f["origen"])
        comprobar(f["id"] == nombre.split(".")[0] and f["formato"] == "rgba16", "%s: id o formato" % f["id"])
        alfa = refs.get(nombre, ("?",))[0]
        comprobar({"0xBE": "clave_00BE", "0x01": "opaco"}.get(alfa) == f["alfa"],
                  "%s: alfa %s, la referencia usa %s" % (f["id"], f["alfa"], alfa))
    for f in filas:
        comprobar(not (f["texto_es"] and f["motivo_no"]), "%s: tiene texto_es y motivo_no a la vez" % f["id"])
    for id_ in NO_SE_TRADUCEN:
        comprobar(por_id.get(id_, {}).get("motivo_no"), "%s tiene que llevar motivo_no" % id_)
    for id_ in CONTROLLER_PAK:
        f = por_id.get(id_, {})
        comprobar(f.get("motivo_no") == "no se muestra" and f.get("origen") == "recursos/texturas/generales/%s.ia16.mio0"
                  % id_, "%s (Controller Pak) tiene que estar como 'no se muestra'" % id_)


def probar_ida_y_vuelta(filas, refs, herramienta, tmp):
    """Paso 2: exportar e importar da los bytes originales, y comprobar los acepta."""
    codigo, _, errores = ejecutar("exportar", "--manifiesto", MANIFIESTO, "--salida", tmp, "--tkmk00", herramienta)
    comprobar(codigo == 0, "exportar fallo: %s" % errores.strip())
    pngs = []
    for f in filas:
        png = os.path.join(tmp, "%s.%s.png" % (f["id"], f["formato"]))
        binario = os.path.join(tmp, f["id"] + ".bin")
        comprobar(os.path.exists(png), "falta %s" % png)
        if not os.path.exists(png):
            continue
        pngs.append(png)
        codigo, _, errores = ejecutar("importar", png, binario)
        comprobar(codigo == 0, "%s: importar fallo: %s" % (f["id"], errores.strip()))
        datos = open(binario, "rb").read() if codigo == 0 else b""
        if f in filas_tkmk00(filas):
            esperado = refs.get(os.path.basename(f["origen"]), ("", ""))[1] == hashlib.sha1(datos).hexdigest()
        else:
            esperado = datos == texturas_es.decodificar_original(f, herramienta)[0]
        comprobar(esperado, "%s: exportar + importar no da los bytes originales" % f["id"])
    # Las que en espanol miden otra cosa (tamanio_es) no sirven tal cual
    otro_tamanio = {"%s.%s.png" % (f["id"], f["formato"]) for f in filas
                    if texturas_es.dimensiones_es(f) != texturas_es.dimensiones(f)}
    iguales = [p for p in pngs if os.path.basename(p) not in otro_tamanio]
    codigo, salida, errores = ejecutar("comprobar", "--manifiesto", MANIFIESTO, *iguales)
    comprobar(codigo == 0, "comprobar rechaza las originales: %s%s" % (salida, errores))
    for png in sorted(p for p in pngs if os.path.basename(p) in otro_tamanio):
        codigo, _, _ = ejecutar("comprobar", "--manifiesto", MANIFIESTO, png)
        comprobar(codigo != 0, "%s: comprobar acepta la original aunque tamanio_es es otro" % png)
    r = subprocess.run([sys.executable, os.path.join(RAIZ, "herramientas", "texturas_es.py"), "importar",
                        pngs[0], os.path.join(tmp, "cli.bin")], capture_output=True, text=True)
    comprobar(r.returncode == 0 and os.path.exists(os.path.join(tmp, "cli.bin")), "la linea de comandos no importa")


def cambiar_pixel(png, destino, x, y, rgba):
    img = png_simple.leer(png)
    pix = bytearray(img.pixeles)
    i = (y * img.ancho + x) * 4
    pix[i:i + 4] = bytes(rgba)
    png_simple.escribir(destino, png_simple.Imagen(img.ancho, img.alto, "rgba", pix))


def rechaza(herramienta, png):
    codigo, _, _ = ejecutar("comprobar", "--manifiesto", MANIFIESTO, png)
    return codigo != 0


def probar_rechazos(herramienta, tmp):
    """Paso 3: comprobar e importar rechazan lo que no sirve."""
    opaca = os.path.join(tmp, "seleccion_juego.rgba16.png")
    clave = os.path.join(tmp, "ok.rgba16.png")
    malo = os.path.join(tmp, "malo")
    os.makedirs(malo, exist_ok=True)
    cambiar_pixel(opaca, os.path.join(malo, "seleccion_juego.rgba16.png"), 5, 5, (0, 16, 255, 0))
    comprobar(rechaza(herramienta, os.path.join(malo, "seleccion_juego.rgba16.png")), "transparente en una opaca")
    cambiar_pixel(clave, os.path.join(malo, "ok.rgba16.png"), 0, 0, (0, 0, 0, 0))
    comprobar(rechaza(herramienta, os.path.join(malo, "ok.rgba16.png")), "transparente con un color que no es 0x00BE")
    cambiar_pixel(clave, os.path.join(malo, "ok.rgba16.png"), 0, 0, (1, 0, 0, 255))
    comprobar(rechaza(herramienta, os.path.join(malo, "ok.rgba16.png")), "color que rgba16 no puede guardar")
    codigo, _, _ = ejecutar("importar", os.path.join(malo, "ok.rgba16.png"), os.path.join(malo, "ok.bin"))
    comprobar(codigo != 0 and not os.path.exists(os.path.join(malo, "ok.bin")), "importar tiene que rechazarlo")
    img = png_simple.leer(clave)
    ancho = img.ancho - 1
    recortada = bytes(v for y in range(img.alto) for v in img.pixeles[y * img.ancho * 4:(y * img.ancho + ancho) * 4])
    png_simple.escribir(os.path.join(malo, "ok.rgba16.png"), png_simple.Imagen(ancho, img.alto, "rgba", recortada))
    comprobar(rechaza(herramienta, os.path.join(malo, "ok.rgba16.png")), "tamanio distinto de la original")
    png_simple.escribir(os.path.join(malo, "ok.ia16.png"), png_simple.leer(clave))
    comprobar(rechaza(herramienta, os.path.join(malo, "ok.ia16.png")), "formato distinto del manifiesto")
    png_simple.escribir(os.path.join(malo, "inventada.rgba16.png"), png_simple.leer(clave))
    comprobar(rechaza(herramienta, os.path.join(malo, "inventada.rgba16.png")), "id que no esta en el manifiesto")


def probar_hoja(tmp):
    """Paso 4: original x3, nuevo x3 y mascara con solo los pixeles cambiados en rojo."""
    original = os.path.join(tmp, "ok.rgba16.png")
    nuevo = os.path.join(tmp, "nuevo.png")
    salida = os.path.join(tmp, "hoja.png")
    cambiar_pixel(original, nuevo, 3, 2, (255, 255, 255, 255))
    codigo, _, errores = ejecutar("hoja", original, nuevo, salida)
    comprobar(codigo == 0, "hoja fallo: %s" % errores.strip())
    if codigo != 0:
        return
    img = png_simple.leer(salida)
    base = png_simple.leer(original)
    comprobar((img.ancho, img.alto) == (3 * base.ancho * 3 + 2 * 4, base.alto * 3), "hoja de %dx%d" % (img.ancho,
                                                                                                    img.alto))
    x0 = 2 * (base.ancho * 3 + 4)
    rgba = img.a_rgba()
    rojos = {(x - x0, y) for y in range(img.alto) for x in range(x0, img.ancho)
             if rgba[y * img.ancho + x][:3] == (255, 0, 0)}
    comprobar(rojos == {(x, y) for x in range(9, 12) for y in range(6, 9)}, "mascara: %d pixeles rojos" % len(rojos))


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    herramienta = sys.argv[1]
    refs = leer_referencias()
    filas = texturas_es.leer_manifiesto(MANIFIESTO)
    probar_manifiesto(filas, refs)
    with tempfile.TemporaryDirectory() as tmp:
        probar_ida_y_vuelta(filas, refs, herramienta, tmp)
        probar_rechazos(herramienta, tmp)
        probar_hoja(tmp)
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
