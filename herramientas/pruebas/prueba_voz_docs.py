#!/usr/bin/env python3
"""La documentación habla con la voz del proyecto (docs/manual/estilo.md).

Uso: prueba_voz_docs.py [narrativa|proceso]. Sin argumento comprueba ambos
alcances. «narrativa» son la portada, el registro de cambios, CONTRIBUTING,
la página, el caso de estudio, las notas de versión, los créditos y el manual
de usuario; «proceso» son docs/traduccion/*.md, las actas y el manual técnico.

En la prosa quedan prohibidos «Alexis» (salvo en la firma y en los créditos),
«el autor» (salvo «el autor del port»), «el responsable», «la persona que» y
«se» más un verbo de acción propia, que debe escribirse en primera persona o
dirigirse al lector de tú. Se ignoran los bloques de código, el código en
línea, las URL, los destinos de los enlaces y las etiquetas HTML. Los
nombres de terceros (anthoo582 y el autor del port original) no se tocan.
También se rechazan las notas al pie ([^n]) y la sección «Notas».

Falsos positivos revisados a mano: la lista FALSOS_POSITIVOS.
Cada fallo imprime «FALLO» con el archivo y la línea.
"""
import glob
import os
import re
import sys

RAIZ = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))

ALCANCES = {
    "narrativa": ["README.md", "CHANGELOG.md", "CONTRIBUTING.md", "docs/index.html",
                  "docs/caso-de-estudio.md", "docs/versiones/*.md",
                  "docs/manual/creditos.md", "docs/manual/usuario.md",
                  "docs/manual/estilo.md"],
    "proceso": ["docs/traduccion/*.md", "docs/traduccion/revisiones/*.md",
                "docs/manual/tecnico.md"],
}

# Verbos de acción propia, en pasado y en presente. Se escribe en primera
# persona («traduje», «compruebo») o se habla al lector de tú.
VERBOS = (
    "hizo|hicieron|escribió|escribieron|decidió|decidieron|comprobó|comprobaron|"
    "verificó|verificaron|revisó|revisaron|añadió|añadieron|corrigió|corrigieron|"
    "probó|probaron|descartó|descartaron|aprobó|aprobaron|tradujo|tradujeron|"
    "reconstruyó|reconstruyeron|creó|crearon|publicó|publicaron|ejecutó|ejecutaron|"
    "midió|midieron|restauró|restauraron|registró|registraron|aceptó|aceptaron|"
    "reescribió|dejó|dejaron|puso|pusieron|movió|movieron|eligió|eligieron|"
    "compiló|compilaron|mejoró|mejoraron|rompió|rompieron|cerró|cerraron|"
    "integró|integraron|mantuvo|mantuvieron|sustituyó|sustituyeron|"
    "comprueba|comprueban|verifica|verifican|prueba|prueban|publica|publican|"
    "escribe|escriben|revisa|revisan|registra|registran|aprueba|aprueban|"
    "restaura|restauran|compila|compilan|versiona|versionan|rompe|rompen|"
    "ejecuta|ejecutan|mide|miden|añade|añaden|corrige|corrigen|documenta|documentan|"
    "actualiza|actualizan|completa|completan|borra|borran|crea|crean|traduce|traducen|"
    "decide|deciden|hace|hacen|mantiene|mantienen|integra|integran|descarta|descartan|"
    "acepta|aceptan|anota|anotan|enlaza|enlazan|cita|citan|declara|declaran|"
    "toca|tocan|rehace|rehacen|trae|traen|mueve|mueven|elige|eligen|abre|abren|"
    "pide|piden|pasa|pasan|valida|validan|diseña|diseñan"
)
PATRON_SE = re.compile(r"\bse (?:%s)\b" % VERBOS, re.I)
PATRONES = [
    ("«Alexis»", re.compile(r"\bAlexis\b")),
    ("«el autor»", re.compile(r"\bel autor\b(?! del port)", re.I)),
    ("«el responsable»", re.compile(r"\bel responsable\b", re.I)),
    ("«la persona que»", re.compile(r"\bla persona que\b", re.I)),
    ("«se» + verbo de acción propia", PATRON_SE),
]
# «se» + verbo que no es acción mía. Frases revisadas a mano (en minúsculas).
FALSOS_POSITIVOS = []
SECCIONES_FIRMA = re.compile(r"cr[eé]ditos|licencia|aviso legal|firma|autor[ií]a", re.I)
ARCHIVOS_FIRMA = {"docs/manual/creditos.md"}
# estilo.md cita las formas prohibidas para explicarlas; solo se le exigen las notas al pie.
ARCHIVOS_EXENTOS = {"docs/manual/estilo.md"}


def prosa(texto):
    """Devuelve (número de línea, línea sin código, encabezado) de la prosa."""
    salida = []
    en_codigo = False
    en_script = False
    encabezado = ""
    for n, linea in enumerate(texto.split("\n"), 1):
        if re.match(r"\s*(```|~~~)", linea):
            en_codigo = not en_codigo
            continue
        if en_codigo:
            continue
        if re.search(r"<(script|style)\b", linea):
            en_script = True
        if en_script:
            if re.search(r"</(script|style)>", linea):
                en_script = False
            continue
        m = re.match(r"#{1,6}\s+(.*)", linea)
        if m:
            encabezado = m.group(1)
        m = re.search(r"<h[1-6][^>]*>(.*?)</h[1-6]>", linea)
        if m:
            encabezado = re.sub(r"<[^>]+>", "", m.group(1))
        limpia = re.sub(r"`[^`]*`", "", linea)
        limpia = re.sub(r"\]\([^)]*\)", "]", limpia)
        limpia = re.sub(r"https?://\S+", "", limpia)
        limpia = re.sub(r"<[^>]+>", "", limpia)
        salida.append((n, limpia, encabezado))
    return salida


def archivos(alcance):
    res = []
    for patron in ALCANCES[alcance]:
        res += sorted(glob.glob(os.path.join(RAIZ, patron)))
    return [os.path.relpath(r, RAIZ) for r in res]


def revisar_texto(ruta, texto, comprobar):
    for n, linea, encabezado in ([] if ruta in ARCHIVOS_EXENTOS else prosa(texto)):
        if any(f in linea.lower() for f in FALSOS_POSITIVOS):
            continue
        firma = (ruta in ARCHIVOS_FIRMA or SECCIONES_FIRMA.search(encabezado)
                 or re.match(r"\s*Alexis Barrera\b", linea))
        for nombre, patron in PATRONES:
            if nombre == "«Alexis»" and firma:
                continue
            comprobar(patron.search(linea) is None,
                      "%s:%d: %s en «%s»" % (ruta, n, nombre, linea.strip()[:90]))
    comprobar(re.search(r"\[\^[^\]]+\]", texto) is None, "%s: tiene notas al pie [^n]" % ruta)
    comprobar(re.search(r"^#{1,6}\s+Notas\s*$", texto, re.M) is None, "%s: tiene una sección «Notas»" % ruta)


def main(argv):
    alcances = argv[1:] or ["narrativa", "proceso"]
    cuenta = [0, 0]

    def comprobar(condicion, mensaje):
        cuenta[0] += 1
        if not condicion:
            cuenta[1] += 1
            print("FALLO: " + mensaje)

    for alcance in alcances:
        if alcance not in ALCANCES:
            print("alcance desconocido: " + alcance)
            return 2
        for ruta in archivos(alcance):
            with open(os.path.join(RAIZ, ruta), encoding="utf-8") as f:
                revisar_texto(ruta, f.read(), comprobar)

    # Casos de control: detecta lo prohibido y deja pasar lo permitido.
    def detecta(texto):
        halladas = []
        revisar_texto("control.md", texto, lambda c, m: None if c else halladas.append(m))
        return bool(halladas)
    comprobar(detecta("El autor decidió el cambio."), "control: no detecta «el autor»")
    comprobar(detecta("Se comprobó con 44 pruebas."), "control: no detecta «se comprobó»")
    comprobar(detecta("Lo aprobó el responsable del proyecto."), "control: no detecta «el responsable»")
    comprobar(detecta("Alexis tradujo los textos."), "control: no detecta «Alexis»")
    comprobar(not detecta("El autor del port original añadió el multitap."), "control: rechaza «el autor del port»")
    comprobar(not detecta("Comprobé con 44 pruebas.\n```\nel autor se comprobó\n```"), "control: rechaza el código")
    comprobar(not detecta("Alexis Barrera · fork de anthoo582"), "control: rechaza la firma")
    comprobar(detecta("Texto con nota[^1].\n\n[^1]: algo"), "control: no detecta [^n]")

    print("%d %s, %d %s" % (cuenta[0], "comprobación" if cuenta[0] == 1 else "comprobaciones",
                            cuenta[1], "fallo" if cuenta[1] == 1 else "fallos"))
    return 1 if cuenta[1] else 0


sys.exit(main(sys.argv))
