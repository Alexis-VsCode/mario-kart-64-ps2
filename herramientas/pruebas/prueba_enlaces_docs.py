#!/usr/bin/env python3
"""Los enlaces de la página y del README llevan a algún sitio.

Recorre docs/index.html y README.md. Todo enlace relativo debe apuntar a
un archivo o carpeta que exista y, si trae ancla, a un id (HTML) o a un
título (Markdown) que exista. En docs/index.html ningún enlace relativo
puede terminar en .md (las páginas de GitHub sin Jekyll no lo convierten)
ni en un .html que no exista; los enlaces absolutos deben ser https y, si son de blob/main de este
repositorio, apuntar a un archivo local (y a una ancla que exista). Tamaño y
SHA-256 del ELF de la página deben constar en v1.2.1.md y en el CHANGELOG.
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


PREFIJO_REPO = "https://github.com/Alexis-VsCode/mario-kart-64-ps2/blob/main/"


def revisar_absoluto(origen, e):
    """Un enlace blob/main de este repositorio debe llevar a un archivo local y a una ancla que exista."""
    if not e.startswith(PREFIJO_REPO):
        return
    ruta, _, ancla = e[len(PREFIJO_REPO):].partition("#")
    ruta = unquote(ruta.split("?")[0])
    existe = os.path.isfile(os.path.join(RAIZ, ruta))
    comprobar(existe, "%s: el enlace absoluto no tiene archivo local %s (%s)" % (origen, ruta, e))
    if existe and ancla and ruta.endswith((".html", ".md")):
        comprobar(ancla in anclas_de(ruta), "%s: no existe la ancla #%s en %s" % (origen, ancla, ruta))


def revisar_elf():
    """Tamaño y SHA-256 del ELF de la página coinciden con docs/versiones/v1.2.1.md y el CHANGELOG."""
    pagina = leer("docs/index.html")
    nota = leer("docs/versiones/v1.2.1.md")
    m = re.search(r"monolitico\.elf</code></td><td>([\d ]+) bytes</td><td><code>([0-9a-f]{64})</code>", pagina)
    comprobar(m is not None, "la página no tiene la fila del ELF")
    if m:
        tam = m.group(1)
        comprobar(tam + " bytes" in nota, "v1.2.1.md no dice el tamaño del ELF (%s bytes)" % tam)
        comprobar(m.group(2) in nota, "v1.2.1.md no lleva el SHA-256 del ELF")
        comprobar(m.group(2) in leer("CHANGELOG.md"), "el CHANGELOG no lleva el SHA-256 del ELF")


def revisar(origen, enlaces):
    base = os.path.dirname(origen)
    es_pagina = origen == "docs/index.html"
    for e in enlaces:
        if e.startswith("mailto:") or e.startswith("data:"):
            continue
        if re.match(r"^[a-z][a-z0-9+.-]*:", e) or e.startswith("//"):
            comprobar(e.startswith("https://"), "%s: enlace absoluto sin https: %s" % (origen, e))
            revisar_absoluto(origen, e)
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
revisar_elf()
comprobar(len(enlaces_html(leer("docs/index.html"))) > 0, "la página no tiene enlaces")

print("%d %s, %d %s" % (comprobaciones, "comprobación" if comprobaciones == 1 else "comprobaciones",
                        fallos, "fallo" if fallos == 1 else "fallos"))
sys.exit(1 if fallos else 0)
