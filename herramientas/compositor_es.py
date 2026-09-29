#!/usr/bin/env python3
"""Compone las texturas en espanol con glifos recortados de las propias texturas del juego.

    compositor_es.py componer [--solo ID ...]     reescribe los PNG de recursos/es/
    compositor_es.py autoprueba [--solo ID ...]   recompone el ingles y mide cuanto coincide

Cada familia (recursos/es/glifos/<familia>/) tiene:
  familia.tsv  parametros: fondo (negro, transparente o fila: el color saturado mas
               frecuente de cada fila, para placas con degradado), filas (y0,y1 de la linea),
               ventana (columnas a cada lado donde buscar el corte), umbral (luminancia
               que separa contorno de relleno), muestras (pixeles minimos de una fila
               para tomar su color de referencia; si no, se usa la fila mas cercana)
  cajas.tsv    un glifo por fila: caracter, textura (id del manifiesto) y las columnas
               aproximadas de su corte izquierdo y derecho. El corte real es el camino
               mas oscuro que baja por esa zona, asi dos letras que se tocan se separan
               por su contorno. Dos glifos seguidos comparten el corte; 'espacio' es el
               hueco entre palabras.
  elegidas.tsv (opcional) como cajas.tsv, una instancia por caracter: la que se usa en
               espanol en todas las texturas de la familia (letras que se tocan, donde
               no todos los cortes salen limpios)
  recetas.tsv  glifos que no existen, armados con otros (ver RECETAS), con partes
               dibujadas en partes/<nombre>.txt ('#' contorno, '+' relleno, 'o' sombra,
               'x' borra, '.' nada) o con la forma de una letra diminuta del juego
               (forma("a", fila): la letra de 5x7 de las texturas fuente_*_diminuto
               con un contorno de 1 pixel).

recursos/es/composicion.tsv dice, por textura: familia, caja (x,y,ancho,alto) donde se
reescribe, texto en ingles y columna de su primer corte (autoprueba) y opciones:
  juntar=N      acerca las letras por filas dejando N columnas (negativo: se montan)
  espacio=N     columnas entre letras si no se juntan
  condensar=F   estrecha cada letra a F de su ancho (F:LETRAS solo esas letras)
  lineas=Y,...  fila de cada linea (desplazamiento; con formas, fila de la letra)
  formas=si     todas las letras salen de las diminutas (textos de dos lineas)
  placa=N       fondo del color del contorno detras del texto, N pixeles mas grande
  alinear=M,... izquierda, derecha o centro por linea; M@N ancla el borde (o el centro) en N
  area=X,Y,W,H  zona que ocupa el espanol si no es la caja del ingles
  lienzo=AxB+X,Y  la version en espanol mide AxB y lleva la original en (X, Y)
  color_lineas=si  cada linea toma el degradado de las filas del original, no el de abajo
  sangrado=si   los transparentes junto a las letras toman su color (texturas sin clave)
  fijo=N        los N primeros caracteres del espanol ya estan en la textura (fuera del area)
El texto en espanol sale de la columna texto_es del manifiesto ('|' separa lineas).

Cada pixel pegado se recolorea por fila: si viene de la misma textura y la misma fila
queda igual; si no, conserva su diferencia con el color mediano de su clase (contorno o
relleno) en su fila de origen y la suma al de la fila de destino. Se pega en dos pasadas,
primero contornos y despues rellenos, para que una letra no tape el relleno de la otra.
"""
import argparse
import ast
import os
import sys

import formatos_textura as ft
import png_simple
import texturas_es

RAIZ = texturas_es.RAIZ
GLIFOS = os.path.join(RAIZ, "recursos", "es", "glifos")
COMPOSICION = os.path.join(RAIZ, "recursos", "es", "composicion.tsv")
MINIMO_AUTOPRUEBA = 0.95
CLAVE_RGBA = (0, 16, 255, 0)
DIMINUTAS = os.path.join(RAIZ, "recursos", "texturas", "generales", "%s.ia16.mio0")
# Signos de las letras diminutas (las letras son fuente_<letra>_diminuto)
SIGNOS_DIMINUTOS = {"-": "menos_fuente_diminuto", "+": "mas_fuente_diminuto", "?": "pregunta_fuente_diminuto",
                    "!": "fuente_diminuto_signo_exclamacion", ",": "coma_fuente_diminuto",
                    ":": "dos_puntos_fuente_diminuto", "/": "diminuto_fuente_adelante_barra"}


class ErrorComposicion(ValueError):
    pass


def leer_tsv(ruta, columnas):
    """Filas de un TSV con cabecera fija; '#' al principio es comentario."""
    with open(ruta, encoding="utf-8") as f:
        lineas = [l for l in f.read().splitlines() if l and not l.startswith("#")]
    if not lineas or lineas[0].split("\t") != columnas:
        raise ErrorComposicion("%s: la cabecera tiene que ser: %s" % (ruta, " ".join(columnas)))
    filas = []
    for linea in lineas[1:]:
        campos = linea.split("\t")
        if len(campos) != len(columnas):
            raise ErrorComposicion("%s: fila con %d columnas: %r" % (ruta, len(campos), linea))
        filas.append(dict(zip(columnas, campos)))
    return filas


def lum(p):
    return 0.299 * p[0] + 0.587 * p[1] + 0.114 * p[2]


def cuantizar(v):
    """Canal de 8 bits al valor mas cercano que guarda rgba16."""
    v = max(0, min(255, int(round(v))))
    c = (v * 31 + 127) // 255
    return (c << 3) | (c >> 2)


class Textura:
    """Una textura original decodificada a RGBA."""
    _cache = {}

    def __init__(self, id_, ancho, alto, pixeles):
        self.id, self.ancho, self.alto, self.pixeles = id_, ancho, alto, pixeles

    @classmethod
    def cargar(cls, id_):
        if id_ not in cls._cache:
            filas = {f["id"]: f for f in texturas_es.leer_manifiesto(texturas_es.MANIFIESTO)}
            if id_ not in filas:
                import lakitu_es
                cuadro = lakitu_es.textura_cuadro(id_)
                if cuadro is None:
                    raise ErrorComposicion("textura %s no esta en el manifiesto" % id_)
                cls._cache[id_] = cls(id_, *cuadro)
                return cls._cache[id_]
            datos, ancho, alto = texturas_es.decodificar_original(filas[id_], texturas_es.TKMK00)
            imagen = ft.a_imagen(filas[id_]["formato"], datos, ancho, alto)
            cls._cache[id_] = cls(id_, ancho, alto, imagen.a_rgba())
        return cls._cache[id_]

    def pixel(self, x, y):
        return self.pixeles[y * self.ancho + x]


class Familia:
    def __init__(self, nombre):
        carpeta = os.path.join(GLIFOS, nombre)
        self.nombre, self.carpeta = nombre, carpeta
        params = {f["clave"]: f["valor"] for f in leer_tsv(os.path.join(carpeta, "familia.tsv"), ["clave", "valor"])}
        self.fondo = params.get("fondo", "transparente")
        self.filas = tuple(int(v) for v in params["filas"].split(","))
        self._filas = {k[len("filas."):]: tuple(int(v) for v in params[k].split(","))
                       for k in params if k.startswith("filas.")}
        self.ventana = int(params.get("ventana", "2"))
        self.umbral = float(params.get("umbral", "60"))
        self.muestras = int(params.get("muestras", "1"))
        self.cajas = leer_tsv(os.path.join(carpeta, "cajas.tsv"), ["caracter", "textura", "x_izq", "x_der"])
        ruta = os.path.join(carpeta, "elegidas.tsv")
        self.elegidas = {f["caracter"]: f for f in leer_tsv(ruta, ["caracter", "textura", "x_izq", "x_der"])} \
            if os.path.exists(ruta) else {}
        ruta = os.path.join(carpeta, "recetas.tsv")
        self.recetas = {f["caracter"]: f["receta"] for f in leer_tsv(ruta, ["caracter", "receta"])} \
            if os.path.exists(ruta) else {}
        self._cortes = {}
        self._refs = {}

    def filas_de(self, textura_id):
        """Filas de la linea de texto en esa textura (filas.<textura> o filas)."""
        return self._filas.get(textura_id, self.filas)

    def es_fondo(self, p, textura=None, y=None):
        if self.fondo == "negro":
            return p[3] == 255 and max(p[:3]) == 0
        if self.fondo == "fila":
            return p[3] and sum((a - b) ** 2 for a, b in zip(p[:3], color_fila(textura, y)[:3])) < 900
        return p[3] == 0

    def clase(self, p):
        return "c" if lum(p) < self.umbral else "r"

    def corte(self, textura, x):
        """Por fila, la primera columna a la derecha del corte (camino mas oscuro, 1 px por fila)."""
        clave = (textura.id, x)
        if clave not in self._cortes:
            y0, y1 = self.filas_de(textura.id)
            xs = list(range(max(0, x - self.ventana), min(textura.ancho, x + self.ventana + 1)))

            def energia(cx, y):
                p = textura.pixel(cx, y)
                return (0 if self.es_fondo(p, textura, y) else 1 + lum(p)) + abs(cx - x) * 0.01

            costo = {cx: energia(cx, y0) for cx in xs}
            atras = []
            for y in range(y0 + 1, y1):
                nuevo, paso = {}, {}
                for cx in xs:
                    previo = min((c for c in (cx - 1, cx, cx + 1) if c in costo), key=lambda c: costo[c])
                    nuevo[cx], paso[cx] = costo[previo] + energia(cx, y), previo
                costo = nuevo
                atras.append(paso)
            cx = min(costo, key=lambda c: costo[c])
            camino = [cx]
            for paso in reversed(atras):
                cx = paso[cx]
                camino.append(cx)
            self._cortes[clave] = list(reversed(camino))
        return self._cortes[clave]

    def glifo_de_caja(self, caja):
        """Sprite de una fila de cajas.tsv: {(x relativo al corte izquierdo, y): pixel}."""
        textura = Textura.cargar(caja["textura"])
        izq, der = int(caja["x_izq"]), int(caja["x_der"])
        y0, y1 = self.filas_de(textura.id)
        ci, cd = self.corte(textura, izq), self.corte(textura, der)
        sprite = {}
        for y in range(y0, y1):
            for x in range(ci[y - y0], cd[y - y0]):
                p = textura.pixel(x, y)
                if not self.es_fondo(p, textura, y):
                    sprite[(x - izq, y)] = (p, self.clase(p), textura.id, y)
        return Glifo(sprite, der - izq, y0)

    def instancias(self, caracter):
        nombre = "espacio" if caracter == " " else caracter
        return [c for c in self.cajas if c["caracter"] == nombre]

    def glifo(self, caracter, preferida=None, indice=None):
        """Glifo de un caracter: la instancia 'indice' de la textura preferida (ingles); en
        espanol la elegida si la hay, si no la primera de esa textura, la receta del caracter
        o la primera instancia de otra."""
        lista = self.instancias(caracter)
        propias = [c for c in lista if c["textura"] == preferida]
        if indice is None and caracter in self.elegidas:
            return self.glifo_de_caja(self.elegidas[caracter])
        if indice is not None and indice < len(propias):
            return self.glifo_de_caja(propias[indice])
        if propias:
            return self.glifo_de_caja(propias[0])
        if caracter in self.recetas:
            return evaluar_receta(self, self.recetas[caracter], preferida)
        if lista:
            return self.glifo_de_caja(lista[0])
        raise ErrorComposicion("familia %s: no hay glifo para %r" % (self.nombre, caracter))

    def glifo_forma(self, caracter, fila):
        """Glifo de la letra diminuta (espacio: 3 columnas), o su receta si la tiene."""
        if caracter == " ":
            return Glifo({}, 3)
        clave = "diminuta " + caracter
        if clave in self.recetas:
            return evaluar_receta(self, self.recetas[clave].replace("FILA", str(fila)), None)
        return _forma(caracter.lower(), fila)

    def referencia(self, textura_id, clase, y):
        """Color de una clase en una fila, sobre los glifos de esa textura: mediana del
        contorno ('c') y del relleno ('r'); 'n' es el color de contorno mas frecuente (el
        que usan las partes dibujadas)."""
        if textura_id not in self._refs:
            por_fila = {}
            for caja in self.cajas:
                if caja["textura"] == textura_id:
                    for p, cl, _, fy in self.glifo_de_caja(caja).pixeles.values():
                        por_fila.setdefault((cl, fy), []).append(p)
            refs = {k: tuple(sorted(c[i] for c in v)[len(v) // 2] for i in range(3)) for k, v in por_fila.items()
                    if len(v) >= self.muestras}
            for (cl, fy), v in por_fila.items():
                if cl == "c":
                    colores = [tuple(c[:3]) for c in v]
                    refs[("n", fy)] = max(sorted(set(colores)), key=colores.count)
            self._refs[textura_id] = refs
        refs = self._refs[textura_id]
        filas = [fy for (cl, fy) in refs if cl == clase] or [fy for (_, fy) in refs]
        if not filas:
            raise ErrorComposicion("textura %s sin glifos en la familia %s" % (textura_id, self.nombre))
        cercana = min(filas, key=lambda fy: (abs(fy - y), fy))
        return refs.get((clase, cercana)) or refs[next(k for k in refs if k[1] == cercana)]


class Glifo:
    """pixeles: {(x, y): (rgba, clase, textura de origen o None, fila de origen)}
    base: primera fila de la linea en su textura (None: filas absolutas, como las partes)."""

    def __init__(self, pixeles, avance, base=None):
        self.pixeles, self.avance, self.base = pixeles, avance, base


# --- Recetas -------------------------------------------------------------------------

def _cols(g, a, b):
    return Glifo({(x - a, y): p for (x, y), p in g.pixeles.items() if a <= x < b}, b - a, g.base)


def _filas(g, a, b):
    return Glifo({(x, y): p for (x, y), p in g.pixeles.items() if a <= y < b}, g.avance, g.base)


def _espejo(g):
    return Glifo({(g.avance - 1 - x, y): p for (x, y), p in g.pixeles.items()}, g.avance, g.base)


def _junto(a, b, solape=0):
    pix = dict(a.pixeles)
    for (x, y), p in b.pixeles.items():
        pix[(x + a.avance - solape, y)] = p
    return Glifo(pix, a.avance + b.avance - solape, a.base)


def _encima(a, b, dx=0, dy=0):
    """b sobre a; los pixeles 'x' de b borran."""
    pix = dict(a.pixeles)
    for (x, y), p in b.pixeles.items():
        if p[1] == "x":
            pix.pop((x + dx, y + dy), None)
        else:
            pix[(x + dx, y + dy)] = p
    return Glifo(pix, a.avance, a.base)


def _girar(g):
    """Media vuelta dentro de su propio alto."""
    if not g.pixeles:
        return g
    ys = [y for _, y in g.pixeles]
    return Glifo({(g.avance - 1 - x, min(ys) + max(ys) - y): p for (x, y), p in g.pixeles.items()}, g.avance,
                 g.base)


def _forma(letra, fila):
    """Letra diminuta (8x8 ia16) como relleno, con un contorno de 1 pixel alrededor."""
    if letra in SIGNOS_DIMINUTOS:
        nombre = SIGNOS_DIMINUTOS[letra]
    elif letra.isdigit():
        nombre = "fuente_diminuto_" + letra
    else:
        nombre = "fuente_%s_diminuto" % letra
    with open(DIMINUTAS % nombre, "rb") as f:
        datos = ft.descomprimir_mio0(f.read())
    celda = ft.a_imagen("ia16", datos[:128], 8, 8).a_rgba()
    relleno = {(x, y) for y in range(8) for x in range(8) if celda[y * 8 + x][3] >= 128}
    if not relleno:
        raise ErrorComposicion("letra diminuta %r vacia" % letra)
    x0 = min(x for x, _ in relleno)
    pix = {}
    for (x, y) in relleno:
        for vx in (-1, 0, 1):
            for vy in (-1, 0, 1):
                v = (x + vx, y + vy)
                if v not in relleno:
                    pix[(v[0] - x0 + 1, v[1] + fila)] = (None, "c", None, v[1] + fila)
        pix[(x - x0 + 1, y + fila)] = (None, "r", None, y + fila)
    return Glifo(pix, max(x for x, _ in relleno) - x0 + 3)


def _mover(g, dx=0, dy=0):
    return Glifo({(x + dx, y + dy): p for (x, y), p in g.pixeles.items()}, g.avance)


def _condensar(g, factor):
    """Estrecha el glifo tomando columnas salteadas (vecino mas cercano)."""
    if not g.pixeles:
        return Glifo({}, int(round(g.avance * factor)))
    x0 = min(x for x, _ in g.pixeles)
    x1 = max(x for x, _ in g.pixeles) + 1
    n = max(1, int(round((x1 - x0) * factor)))
    inicio = int(round(x0 * factor))
    pix = {}
    for i in range(n):
        ox = x0 + int((i + 0.5) * (x1 - x0) / n)
        for (x, y), p in g.pixeles.items():
            if x == ox:
                pix[(inicio + i, y)] = p
    return Glifo(pix, int(round(g.avance * factor)), g.base)


def _avance(g, n):
    return Glifo(dict(g.pixeles), n)


def _borrar(g, x0, y0, x1, y1):
    return Glifo({(x, y): p for (x, y), p in g.pixeles.items() if not (x0 <= x < x1 and y0 <= y < y1)}, g.avance)


def _parte(familia, nombre, y0):
    """Parte dibujada: '#' contorno, '+' relleno; y0 es la fila de su primera linea."""
    with open(os.path.join(familia.carpeta, "partes", nombre + ".txt")) as f:
        lineas = f.read().splitlines()
    pix = {}
    clases = {"#": "c", "+": "r", "o": "s", "x": "x"}
    for dy, linea in enumerate(lineas):
        for x, ch in enumerate(linea):
            if ch in clases:
                pix[(x, y0 + dy)] = (None, clases[ch], None, y0 + dy)
    return Glifo(pix, max(len(l) for l in lineas))


RECETAS = {"cols": _cols, "filas": _filas, "espejo": _espejo, "junto": _junto, "encima": _encima,
           "mover": _mover, "avance": _avance, "borrar": _borrar, "condensar": _condensar, "girar": _girar,
           "forma": _forma}


def evaluar_receta(familia, texto, preferida):
    """Expresion con llamadas a RECETAS, glifo("X") y parte("nombre", fila)."""
    def valor(nodo):
        if isinstance(nodo, ast.Constant) and isinstance(nodo.value, (int, str)):
            return nodo.value
        if isinstance(nodo, ast.UnaryOp) and isinstance(nodo.op, ast.USub):
            return -valor(nodo.operand)
        if isinstance(nodo, ast.BinOp) and isinstance(nodo.op, (ast.Add, ast.Sub)):
            a, b = valor(nodo.left), valor(nodo.right)
            if isinstance(a, int) and isinstance(b, int):
                return a + b if isinstance(nodo.op, ast.Add) else a - b
        if isinstance(nodo, ast.Call) and isinstance(nodo.func, ast.Name) and not nodo.keywords:
            args = [valor(a) for a in nodo.args]
            if nodo.func.id == "glifo":
                return familia.glifo(args[0], preferida)
            if nodo.func.id == "parte":
                return _parte(familia, *args)
            if nodo.func.id in RECETAS:
                return RECETAS[nodo.func.id](*args)
        raise ErrorComposicion("receta invalida: %s" % texto)
    return valor(ast.parse(texto, mode="eval").body)


# --- Composicion ---------------------------------------------------------------------

def leer_composicion():
    filas = leer_tsv(COMPOSICION, ["id", "familia", "caja", "texto_en", "x_en", "opciones"])
    return {f["id"]: f for f in filas}


def opciones(texto):
    res = {}
    for par in texto.split():
        clave, valor = par.split("=")
        res[clave] = valor
    return res


def colocar(familia, destino, lineas, caja, opc, en_ingles=False, x_en=None):
    """[(x0, dy, glifo)] de cada letra. En ingles usa las letras de la propia textura en orden."""
    cx, cy, cw, ch = caja
    espacio = int(opc.get("espacio", "0")) if not en_ingles else 0
    factor, _, solo = opc.get("condensar", "1").partition(":")
    factor = float(factor) if not en_ingles else 1.0
    desplaz = [int(v) for v in opc.get("lineas", "0").split(",")] if not en_ingles else [0]
    if len(desplaz) != len(lineas):
        raise ErrorComposicion("%s: %d lineas y %d desplazamientos" % (destino.id, len(lineas), len(desplaz)))
    colocados = []
    usados = {}
    formas = opc.get("formas") == "si" and not en_ingles
    alineaciones = opc.get("alinear", "centro").split(",")
    for n, (texto, dy) in enumerate(zip(lineas, desplaz)):
        alinear = alineaciones[min(n, len(alineaciones) - 1)]
        linea = dy
        glifos = []
        for c in texto:
            indice = usados.get(c, 0) if en_ingles else None
            usados[c] = usados.get(c, 0) + 1
            if formas:
                glifos.append(familia.glifo_forma(c, dy))
                continue
            g = familia.glifo(c, destino.id, indice)
            glifos.append(_condensar(g, factor) if factor != 1.0 and (not solo or c in solo) else g)
        if formas:
            dy = 0
        if "juntar" in opc and not en_ingles:
            xs = juntar(glifos, int(opc["juntar"]))
        else:
            xs = [sum(g.avance + espacio for g in glifos[:i]) for i in range(len(glifos))]
        pixeles = [x + px for x, g in zip(xs, glifos) for (px, _) in g.pixeles]
        izq, der = (min(pixeles), max(pixeles) + 1) if pixeles else (0, 0)
        modo, _, ancla = alinear.partition("@")
        if en_ingles:
            base = x_en
        elif modo == "izquierda":
            base = (int(ancla) if ancla else cx) - izq
        elif modo == "derecha":
            base = (int(ancla) if ancla else cx + cw) - der
        elif ancla:
            base = int(ancla) - (der - izq) // 2 - izq
        else:
            base = cx + (cw - (der - izq)) // 2 - izq
        propia = familia.filas_de(destino.id)[0]
        colocados += [(base + x, dy + (propia - g.base if g.base is not None else 0), g, linea)
                      for x, g in zip(xs, glifos)]
    return colocados


def juntar(glifos, hueco):
    """Posicion de cada glifo acercandolo por filas: entre lo ya puesto y el siguiente quedan
    al menos 'hueco' columnas en cada fila (negativo: se montan). Un glifo sin pixeles (el
    espacio) deja su avance libre despues de lo ya puesto."""
    derecha = {}
    xs, siguiente, minimo = [], 0, None
    for g in glifos:
        izquierda = {}
        for (px, py) in g.pixeles:
            izquierda[py] = min(px, izquierda.get(py, px))
        if not izquierda:
            x = max(derecha.values()) + 1 if derecha else siguiente
            minimo = x + g.avance
        else:
            comunes = [y for y in izquierda if y in derecha]
            x = max([derecha[y] + 1 + hueco - izquierda[y] for y in comunes] or [siguiente])
            if minimo is not None:
                x = max(x, minimo - min(izquierda.values()))
        xs.append(x)
        for (px, py) in g.pixeles:
            derecha[py] = max(x + px, derecha.get(py, x + px))
        siguiente = x + g.avance
    return xs


def color_fila(textura, y):
    """Color de fondo de una fila (fondo=fila): el mas frecuente entre los saturados."""
    clave = (textura.id, y)
    if clave not in _COLOR_FILA:
        fila = [textura.pixel(x, y) for x in range(textura.ancho)]
        saturados = [p for p in fila if p[3] and max(p[:3]) > 30 and (max(p[:3]) - min(p[:3])) / max(p[:3]) >= 0.6]
        _COLOR_FILA[clave] = max(sorted(set(saturados)), key=saturados.count) if saturados else (0, 0, 0, 255)
    return _COLOR_FILA[clave]


_COLOR_FILA = {}


def transparente(textura, caja):
    """Color de los pixeles transparentes de la textura (el mas comun en la caja; la clave
    0x00BE de las TKMK00 de type 1 si no hay ninguno)."""
    cx, cy, cw, ch = caja
    vistos = [textura.pixel(x, y) for y in range(cy, cy + ch) for x in range(cx, cx + cw)
              if textura.pixel(x, y)[3] == 0]
    return max(sorted(set(vistos)), key=vistos.count) if vistos else CLAVE_RGBA


def lienzo(comp, destino, en_ingles=False, vacio=None):
    """(ancho, alto, pixeles) de partida: la textura original, o con 'lienzo=AxB+X,Y' una mas
    grande con la original en (X, Y) y el resto transparente."""
    opc = opciones(comp["opciones"])
    if en_ingles or "lienzo" not in opc:
        return destino.ancho, destino.alto, list(destino.pixeles)
    medida, _, lugar = opc["lienzo"].partition("+")
    ancho, alto = (int(v) for v in medida.split("x"))
    ox, oy = (int(v) for v in lugar.split(","))
    vacio = vacio or transparente(destino, (0, 0, destino.ancho, destino.alto))
    pixeles = [vacio] * (ancho * alto)
    for y in range(destino.alto):
        for x in range(destino.ancho):
            pixeles[(y + oy) * ancho + x + ox] = destino.pixel(x, y)
    return ancho, alto, pixeles


def area_de(comp, en_ingles=False):
    """Zona que se reescribe: la caja del texto en ingles, o 'area' si el espanol ocupa otra."""
    opc = opciones(comp["opciones"])
    texto = comp["caja"] if en_ingles or "area" not in opc else opc["area"]
    return tuple(int(v) for v in texto.split(","))


def componer(id_, texto, comp, destino=None, en_ingles=False):
    """Pixeles RGBA de la textura con el texto compuesto en la caja."""
    familia = Familia(comp["familia"])
    destino = destino or Textura.cargar(id_)
    opc = opciones(comp["opciones"])
    caja = area_de(comp, en_ingles)
    cx, cy, cw, ch = caja
    if not en_ingles:
        texto = texto[int(opc.get("fijo", "0")):]
    colocados = colocar(familia, destino, texto.split("|"), caja, opc, en_ingles, int(comp["x_en"] or "0"))
    vacio = (0, 0, 0, 255) if familia.fondo == "negro" else transparente(destino, area_de(comp, True))
    ancho, alto, salida = lienzo(comp, destino, en_ingles, vacio)
    for y in range(cy, cy + ch):
        for x in range(cx, cx + cw):
            salida[y * ancho + x] = color_fila(destino, y) if familia.fondo == "fila" else vacio
    puntos = [(x0 + x, y + dy) for x0, dy, g, _ in colocados for (x, y) in g.pixeles]
    if puntos:
        xs, ys = [p[0] for p in puntos], [p[1] for p in puntos]
        if min(xs) < cx or max(xs) >= cx + cw or min(ys) < cy or max(ys) >= cy + ch:
            raise ErrorComposicion("%s: %r no cabe en %s: ocupa x %d..%d, y %d..%d"
                                   % (id_, texto, ",".join(map(str, caja)), min(xs), max(xs), min(ys), max(ys)))
    if "placa" in opc and puntos and not en_ingles:
        margen = int(opc["placa"])
        for y in range(max(cy, min(ys) - margen), min(cy + ch, max(ys) + margen + 1)):
            color = tuple(cuantizar(c) for c in familia.referencia(destino.id, "n", y)) + (255,)
            for x in range(max(cx, min(xs) - margen), min(cx + cw, max(xs) + margen + 1)):
                salida[y * ancho + x] = color
    por_linea = opc.get("color_lineas") == "si" and not en_ingles
    for pasada in ("c", "r"):
        for x0, dy, g, linea in colocados:
            for (x, y), (p, clase, fuente, fy) in g.pixeles.items():
                if clase == pasada:
                    fila = y + dy - linea if por_linea else y + dy
                    salida[(y + dy) * ancho + x0 + x] = recolorear(familia, p, clase, fuente, fy, destino.id, fila)
    if opc.get("sangrado") == "si" and not en_ingles:
        sangrar(salida, ancho, caja)
    return salida


def recolorear(familia, p, clase, fuente, fy, destino, ty):
    if fuente == destino and fy == ty:
        return p
    if fuente is None:
        contorno, relleno = familia.referencia(destino, "n", ty), familia.referencia(destino, "r", ty)
        ref = {"c": contorno, "r": relleno}.get(clase) or tuple((a + b) / 2.0 for a, b in zip(contorno, relleno))
        return tuple(cuantizar(c) for c in ref) + (255,)
    ref = familia.referencia(destino, clase, ty)
    origen = familia.referencia(fuente, clase, fy)
    return tuple(cuantizar(r + c - o) for r, c, o in zip(ref, p, origen)) + (255,)


def sangrar(pixeles, ancho, caja):
    """Los transparentes pegados a una letra toman su color (con alfa 0), como en las
    originales, para que el filtrado no oscurezca el borde."""
    cx, cy, cw, ch = caja
    alto = len(pixeles) // ancho
    copia = list(pixeles)
    for y in range(cy, cy + ch):
        for x in range(cx, cx + cw):
            if copia[y * ancho + x][3]:
                continue
            vecinos = [copia[vy * ancho + vx] for vy in (y - 1, y, y + 1) for vx in (x - 1, x, x + 1)
                       if 0 <= vx < ancho and 0 <= vy < alto and copia[vy * ancho + vx][3]]
            if vecinos:
                pixeles[y * ancho + x] = vecinos[0][:3] + (0,)


def autoprueba(id_, comp):
    """Fraccion de pixeles de la caja iguales al original al recomponer el texto en ingles."""
    destino = Textura.cargar(id_)
    salida = componer(id_, comp["texto_en"], comp, destino, en_ingles=True)
    cx, cy, cw, ch = (int(v) for v in comp["caja"].split(","))
    iguales = sum(salida[y * destino.ancho + x] == destino.pixel(x, y)
                  or salida[y * destino.ancho + x][3] == destino.pixel(x, y)[3] == 0
                  for y in range(cy, cy + ch) for x in range(cx, cx + cw))
    return iguales / float(cw * ch)


def png_compuesto(id_, fila, comp):
    """png_simple.Imagen de la textura en espanol, en su formato (sin perdida)."""
    destino = Textura.cargar(id_)
    pixeles = componer(id_, fila["texto_es"], comp, destino)
    ancho, alto, _ = lienzo(comp, destino)
    if fila["formato"] in ("i4", "ia8"):
        # grises de 4 bits: el mas cercano de 0, 17, ..., 255
        pixeles = [tuple(int(round(c / 17.0)) * 17 for c in p) for p in pixeles]
    imagen = png_simple.Imagen(ancho, alto, "rgba", bytes(c for p in pixeles for c in p))
    return ft.a_imagen(fila["formato"], ft.de_imagen(fila["formato"], imagen), ancho, alto)


def main(argv=None):
    parser = argparse.ArgumentParser(description="Compositor de texturas en espanol")
    parser.add_argument("orden", choices=["componer", "autoprueba"])
    parser.add_argument("--solo", nargs="*")
    args = parser.parse_args(argv)
    manifiesto = {f["id"]: f for f in texturas_es.leer_manifiesto(texturas_es.MANIFIESTO)}
    comps = leer_composicion()
    ids = args.solo or sorted(comps)
    malos = 0
    try:
        for id_ in ids:
            comp, fila = comps[id_], manifiesto[id_]
            if args.orden == "autoprueba":
                parecido = autoprueba(id_, comp)
                malos += parecido < MINIMO_AUTOPRUEBA
                print("%s: %.1f%% de la caja" % (id_, 100 * parecido))
            else:
                ruta = os.path.join(RAIZ, fila["png"])
                os.makedirs(os.path.dirname(ruta), exist_ok=True)
                png_simple.escribir(ruta, png_compuesto(id_, fila, comp))
                print("%s: %s" % (id_, fila["texto_es"]))
    except (ErrorComposicion, texturas_es.ErrorManifiesto, ft.ErrorFormato, KeyError) as e:
        print("compositor_es: error: %s" % e, file=sys.stderr)
        return 1
    return 1 if malos else 0


if __name__ == "__main__":
    sys.exit(main())
