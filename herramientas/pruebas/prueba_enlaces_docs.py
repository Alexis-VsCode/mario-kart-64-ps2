#!/usr/bin/env python3
"""Los enlaces de la página y del README llevan a algún sitio.

Recorre docs/index.html y README.md. Todo enlace relativo debe apuntar a
un archivo o carpeta que exista y, si trae ancla, a un id (HTML) o a un
título (Markdown) que exista. En docs/index.html ningún enlace relativo
puede terminar en .md (las páginas de GitHub sin Jekyll no lo convierten)
ni en un .html que no exista; los enlaces absolutos deben ser https.
"""
import os
import re
import sys
from urllib.parse import unquote

RAIZ = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))
comprobaciones = 0
fallos = 0


def comprobar(condicion, mensaje):
    global comprobaciones, fallos
    comprobaciones += 1
    if not condicion:
        fallos += 1
        print("FALLO: " + mensaje)


def leer(ruta):
    with open(os.path.join(RAIZ, ruta), encoding="utf-8") as f:
        return f.read()


def anclas_html(texto):
    return set(re.findall(r'\bid="([^"]+)"', texto))


def anclas_md(texto):
    res = set()
    for t in re.findall(r"^#{1,6}\s+(.+?)\s*#*$", texto, re.M):
        t = re.sub(r"[`*_]", "", t.lower())
        t = re.sub(r"[^\w\- ]", "", t).replace(" ", "-")
        res.add(t)
    return res


def anclas_de(ruta):
    texto = leer(ruta)
    return anclas_html(texto) if ruta.endswith(".html") else anclas_md(texto)


def enlaces_html(texto):
    return re.findall(r'\b(?:href|src)="([^"]*)"', texto)


def enlaces_md(texto):
    texto = re.sub(r"```.*?```", "", texto, flags=re.S)
    return [m.strip("<>").split(" ")[0] for m in re.findall(r"\]\(([^)]+)\)", texto)]


def revisar(origen, enlaces):
    base = os.path.dirname(origen)
    es_pagina = origen == "docs/index.html"
    for e in enlaces:
        if e.startswith("mailto:") or e.startswith("data:"):
            continue
        if re.match(r"^[a-z][a-z0-9+.-]*:", e) or e.startswith("//"):
            comprobar(e.startswith("https://"), "%s: enlace absoluto sin https: %s" % (origen, e))
            continue
        ruta, _, ancla = e.partition("#")
        ruta = unquote(ruta.split("?")[0])
        if ruta == "":
            destino = origen
        else:
            destino = os.path.normpath(os.path.join(base, ruta))
            if es_pagina:
                comprobar(not ruta.endswith(".md"), "%s: enlace a .md: %s" % (origen, e))
            existe = os.path.exists(os.path.join(RAIZ, destino))
            comprobar(existe, "%s: no existe %s (%s)" % (origen, destino, e))
            if not existe:
                continue
        if ancla and destino.endswith((".html", ".md")) and os.path.isfile(os.path.join(RAIZ, destino)):
            comprobar(ancla in anclas_de(destino), "%s: no existe la ancla #%s en %s" % (origen, ancla, destino))


revisar("docs/index.html", enlaces_html(leer("docs/index.html")))
revisar("README.md", enlaces_md(leer("README.md")))
comprobar(len(enlaces_html(leer("docs/index.html"))) > 0, "la página no tiene enlaces")

print("%d %s, %d %s" % (comprobaciones, "comprobación" if comprobaciones == 1 else "comprobaciones",
                        fallos, "fallo" if fallos == 1 else "fallos"))
sys.exit(1 if fallos else 0)
