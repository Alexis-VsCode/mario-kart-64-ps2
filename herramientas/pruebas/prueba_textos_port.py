#!/usr/bin/env python3
"""Los textos de las pantallas propias del port van en espanol y con tildes.

    prueba_textos_port.py [<fuente que el build pasa a EUC-JP> ...]

Lee los literales de cadena que el port manda a sus pantallas y a su
registro y falla si alguno lleva una palabra en ingles o sin la tilde que
le toca. Es una lista negra: solo encuentra las palabras que conoce. Los
nombres con '_' o con cifras (funciones, registros, formatos) no se miran,
salvo en los nombres de fase, que no pueden ser nombres de funcion.

En los fuentes que el build pasa a EUC-JP los textos del port van solo en
ASCII: el registro se lee en UTF-8.

Las palabras que el registro busca y los grupos del cronometro salen de
marcas_registro.h: ningun fuente las escribe a mano.
"""
import os
import re
import sys

RAIZ = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))

TODO_EL_CODIGO = None

# (que se revisa, archivos, llamadas o tablas cuyos literales se leen)
REVISIONES = (
    ("panel", ("codigo/depuracion/medidor_rendimiento.c", "codigo/depuracion/monitor_audio.c"),
     ("snprintf", "texto_escribir_linea", "LINEA")),
    ("fase", TODO_EL_CODIGO, ("marcar_tiempos_ps2", "MARCAR_TIEMPOS_PS2")),
    ("punto de control", TODO_EL_CODIGO, ("marcar_punto_control", "MARCAR_PUNTO_CONTROL")),
)
# En estas revisiones un nombre con '_' es un nombre de funcion
SIN_IDENTIFICADORES = ("fase", "punto de control")

MARCAS_REGISTRO = "incluir/depuracion/marcas_registro.h"
# Llamadas que solo reciben macros de MARCAS_REGISTRO, nunca literales
SOLO_MACROS = (
    ("palabra clave", ("codigo/depuracion/depuracion.c",), ("strstr",)),
    ("grupo del cronometro", TODO_EL_CODIGO,
     ("empezar_tiempos_ps2", "EMPEZAR_TIEMPOS_PS2", "summary_tiempos_ps2", "informe_tiempos_ps2")),
)

# Palabra (en minuscula) -> como se escribe
INGLES = {
    "frame": "cuadro",
    "pool": "reserva",
    "vtx": "vért",
    "tris": "tri",
    "seq": "sec",
    "max": "máx",
    "min": "mín",
    "display": "lista de dibujo",
    "lists": "listas",
    "offsets": "desplazamientos",
    "render": "dibujo",
}
SIN_TILDE = {
    "musica": "música",
    "depuracion": "depuración",
    "colision": "colisión",
    "vertices": "vértices",
    "camaras": "cámaras",
    "cuadricula": "cuadrícula",
    "logica": "lógica",
    "graficos": "gráficos",
}

FORMATO = re.compile(r"%[-+ #0]*(\d+|\*)?(\.(\d+|\*))?[hlLqjzt]*[diouxXeEfFgGaAcspn%]")
ESCAPE = re.compile(r"\\(x[0-9A-Fa-f]+|[0-7]{1,3}|.)")
PALABRA = re.compile(r"\w+")

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def fichas(texto):
    """(tipo, valor, linea) de un fuente C: 'lit', 'id' o 'sig'; sin comentarios ni #include."""
    i, linea, n = 0, 1, len(texto)
    while i < n:
        c = texto[i]
        if c == "\n":
            linea += 1
            i += 1
        elif texto.startswith("//", i) or texto.startswith("#include", i):
            i = texto.find("\n", i) if texto.find("\n", i) >= 0 else n
        elif texto.startswith("/*", i):
            fin = texto.find("*/", i + 2)
            fin = n if fin < 0 else fin + 2
            linea += texto.count("\n", i, fin)
            i = fin
        elif c in "\"'":
            j = i + 1
            while j < n and texto[j] != c:
                j += 2 if texto[j] == "\\" else 1
            if c == '"':
                yield ("lit", texto[i + 1:j], linea)
            i = j + 1
        elif c.isalpha() or c == "_":
            j = i
            while j < n and (texto[j].isalnum() or texto[j] == "_"):
                j += 1
            yield ("id", texto[i:j], linea)
            i = j
        else:
            if not c.isspace():
                yield ("sig", c, linea)
            i += 1


def literales_de(ruta, llamadas):
    """Literales (linea, texto) dentro de las llamadas o tablas con esos nombres (None: todos)."""
    with open(os.path.join(RAIZ, ruta), encoding="utf-8") as f:
        lista = list(fichas(f.read()))
    if llamadas is None:
        for tipo, valor, linea in lista:
            if tipo == "lit":
                yield linea, valor
        return
    i = 0
    while i < len(lista):
        tipo, valor, _ = lista[i]
        i += 1
        if tipo != "id" or valor not in llamadas:
            continue
        # llamada: nombre( ... ); tabla: nombre[...] = { ... }
        j = i
        while j < len(lista) and lista[j][1] in "[]=" and lista[j][0] == "sig":
            j += 1
        if j >= len(lista) or lista[j][1] not in "({":
            continue
        abre = lista[j][1]
        cierra = ")" if abre == "(" else "}"
        nivel = 0
        for tipo2, valor2, linea2 in lista[j:]:
            j += 1
            if tipo2 == "sig" and valor2 == abre:
                nivel += 1
            elif tipo2 == "sig" and valor2 == cierra:
                nivel -= 1
                if nivel == 0:
                    break
            elif tipo2 == "lit":
                yield linea2, valor2
        i = j


def palabras(literal):
    """Palabras de un literal, sin formatos de printf, escapes ni identificadores."""
    texto = ESCAPE.sub(" ", FORMATO.sub(" ", literal))
    for p in PALABRA.findall(texto):
        if "_" not in p and not any(ch.isdigit() for ch in p):
            yield p


def revisar(que, ruta, linea, literal, en_eucjp):
    lugar = "%s:%d (%s)" % (ruta, linea, que)
    for p in palabras(literal):
        bien = INGLES.get(p.lower()) or (None if en_eucjp else SIN_TILDE.get(p.lower()))
        comprobar(bien is None, "%s: '%s' se escribe '%s'" % (lugar, p, bien))
    if que in SIN_IDENTIFICADORES:
        codigo = [p for p in PALABRA.findall(ESCAPE.sub(" ", literal)) if "_" in p]
        comprobar(not codigo, "%s: '%s' es un nombre de funcion; describe el paso" % (lugar, " ".join(codigo)))
    if en_eucjp:
        comprobar(literal.isascii(), "%s: '%s' se convierte a EUC-JP; solo ASCII" % (lugar, literal))


def fuentes_del_codigo():
    for base, carpetas, nombres in os.walk(os.path.join(RAIZ, "codigo")):
        carpetas.sort()
        for nombre in sorted(nombres):
            ruta = os.path.relpath(os.path.join(base, nombre), RAIZ).replace(os.sep, "/")
            if nombre.endswith(".c") and not ruta.startswith("codigo/sistema/libultra/"):
                yield ruta


def revisar_marcas():
    for que, archivos, llamadas in SOLO_MACROS:
        for ruta in (archivos if archivos is not TODO_EL_CODIGO else fuentes_del_codigo()):
            for linea, literal in literales_de(ruta, llamadas):
                comprobar(False, "%s:%d (%s): '%s' va con su macro de %s" % (ruta, linea, que, literal, MARCAS_REGISTRO))
    existe = os.path.exists(os.path.join(RAIZ, MARCAS_REGISTRO))
    comprobar(existe, "falta " + MARCAS_REGISTRO)
    if not existe:
        return
    with open(os.path.join(RAIZ, MARCAS_REGISTRO), encoding="utf-8") as f:
        marcas = re.findall(r'#define\s+(MARCA_\w+)\s+"([^"]*)"', f.read())
    comprobar(marcas, "%s no define ninguna MARCA_" % MARCAS_REGISTRO)
    # Quien escribe la marca en un mensaje tambien usa la macro
    for ruta in fuentes_del_codigo():
        for linea, literal in literales_de(ruta, None):
            for nombre, palabra in marcas:
                comprobar(palabra not in PALABRA.findall(literal),
                          "%s:%d: '%s' lleva '%s'; usa %s" % (ruta, linea, literal, palabra, nombre))


def main():
    en_eucjp = set(sys.argv[1:])
    revisar_marcas()
    for que, archivos, llamadas in REVISIONES:
        for ruta in (archivos if archivos is not TODO_EL_CODIGO else fuentes_del_codigo()):
            for linea, literal in literales_de(ruta, llamadas):
                revisar(que, ruta, linea, literal, ruta in en_eucjp)
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
