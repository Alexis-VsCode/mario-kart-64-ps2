#!/usr/bin/env python3
"""Los textos de las pantallas propias del port van en espanol y con tildes.

    prueba_textos_port.py

Lee los literales de cadena que el port manda a sus pantallas y a su
registro y falla si alguno lleva una palabra en ingles o sin la tilde que
le toca. Es una lista negra: solo encuentra las palabras que conoce. Los
nombres con '_' o con cifras (funciones, registros, formatos) no se miran.
"""
import os
import re
import sys

RAIZ = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))

# (que se revisa, archivos, llamadas o tablas cuyos literales se leen)
REVISIONES = (
    ("panel", ("codigo/depuracion/medidor_rendimiento.c", "codigo/depuracion/monitor_audio.c"),
     ("snprintf", "texto_escribir_linea", "LINEA")),
)

# Palabra (en minuscula) -> como se escribe
PROHIBIDAS = {
    "frame": "cuadro",
    "pool": "reserva",
    "vtx": "vért",
    "tris": "tri",
    "seq": "sec",
    "max": "máx",
    "min": "mín",
    "musica": "música",
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
    """Literales (linea, texto) dentro de las llamadas o tablas con esos nombres."""
    with open(os.path.join(RAIZ, ruta), encoding="utf-8") as f:
        lista = list(fichas(f.read()))
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


def revisar_palabras(que, ruta, linea, literal):
    for p in palabras(literal):
        bien = PROHIBIDAS.get(p.lower())
        comprobar(bien is None, "%s:%d (%s): '%s' se escribe '%s'" % (ruta, linea, que, p, bien))


def main():
    for que, archivos, llamadas in REVISIONES:
        for ruta in archivos:
            for linea, literal in literales_de(ruta, llamadas):
                revisar_palabras(que, ruta, linea, literal)
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
