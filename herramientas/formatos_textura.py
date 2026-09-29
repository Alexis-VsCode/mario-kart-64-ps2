#!/usr/bin/env python3
"""Conversion sin perdida entre bytes de textura N64 y pixeles (png_simple.Imagen).

Formatos: rgba16 (5551 big-endian), ia16, ia8, i4, i8 y ci8 con su tlut
rgba16. Los canales de 5 o 4 bits se expanden a 8 repitiendo sus bits
altos; al volver, un valor que no salga de esa expansion se rechaza en
lugar de redondearse. Tambien lee y escribe los .inc.c de datos del repo
(listas de 0xNN u8 o 0xNNNN u16) y descomprime MIO0.
"""
import re

from png_simple import Imagen

FORMATOS = ("rgba16", "ia16", "ia8", "i4", "i8", "ci8")
BITS = {"rgba16": 16, "ia16": 16, "ia8": 8, "i4": 4, "i8": 8, "ci8": 8}
TOKEN_RE = re.compile(r"0[xX]([0-9a-fA-F]+)")


class ErrorFormato(ValueError):
    pass


def _de5(v):
    return (v << 3) | (v >> 2)


def _a5(v, que):
    if _de5(v >> 3) != v:
        raise ErrorFormato("%s %d no es un valor de 5 bits expandido" % (que, v))
    return v >> 3


def _a4(v, que):
    if v % 17:
        raise ErrorFormato("%s %d no es un valor de 4 bits expandido" % (que, v))
    return v // 17


def rgba16_a_rgba(v):
    return (_de5(v >> 11), _de5((v >> 6) & 0x1F), _de5((v >> 1) & 0x1F), 255 if v & 1 else 0)


def rgba_a_rgba16(p):
    r, g, b, a = p
    if a not in (0, 255):
        raise ErrorFormato("alfa %d: rgba16 solo tiene 0 o 255" % a)
    return (_a5(r, "rojo") << 11) | (_a5(g, "verde") << 6) | (_a5(b, "azul") << 1) | (a >> 7)


def _u16(datos):
    return [(datos[i] << 8) | datos[i + 1] for i in range(0, len(datos), 2)]


def _bytes_u16(valores):
    return bytes(b for v in valores for b in (v >> 8, v & 0xFF))


def _gris(p, que, con_alfa):
    r, g, b, a = p
    if r != g or g != b:
        raise ErrorFormato("%s: pixel con color %r" % (que, p))
    if not con_alfa and a != 255:
        raise ErrorFormato("%s: pixel transparente %r" % (que, p))
    return r, a


def a_imagen(formato, datos, ancho, alto, tlut=None):
    """Imagen con los pixeles de una textura (ci8 necesita la tlut en bytes rgba16)."""
    if formato not in FORMATOS:
        raise ErrorFormato("formato desconocido %r" % formato)
    n = ancho * alto
    if len(datos) * 8 != n * BITS[formato]:
        raise ErrorFormato("%s de %dx%d necesita %d bytes, hay %d" % (formato, ancho, alto, n * BITS[formato] // 8,
                                                                         len(datos)))
    if formato == "rgba16":
        return Imagen(ancho, alto, "rgba", bytes(c for v in _u16(datos) for c in rgba16_a_rgba(v)))
    if formato == "ia16":
        return Imagen(ancho, alto, "gris_alfa", datos)
    if formato == "ia8":
        return Imagen(ancho, alto, "gris_alfa", bytes(c for v in datos for c in ((v >> 4) * 17, (v & 15) * 17)))
    if formato == "i4":
        return Imagen(ancho, alto, "gris", bytes(c for v in datos for c in ((v >> 4) * 17, (v & 15) * 17)))
    if formato == "i8":
        return Imagen(ancho, alto, "gris", datos)
    if tlut is None or not 0 < len(tlut) <= 512 or len(tlut) % 2:
        raise ErrorFormato("ci8 necesita una tlut rgba16 de 1 a 256 colores")
    return Imagen(ancho, alto, "indexado", datos, [rgba16_a_rgba(v) for v in _u16(tlut)])


def de_imagen(formato, imagen):
    """Bytes de la textura; en ci8 devuelve (indices, tlut). Estricto: no redondea."""
    if formato == "ci8":
        if imagen.tipo != "indexado":
            raise ErrorFormato("ci8 necesita un PNG indexado, este es %s" % imagen.tipo)
        return imagen.pixeles, _bytes_u16(rgba_a_rgba16(c) for c in imagen.paleta)
    if formato not in FORMATOS:
        raise ErrorFormato("formato desconocido %r" % formato)
    pixeles = imagen.a_rgba()
    if formato == "rgba16":
        return _bytes_u16(rgba_a_rgba16(p) for p in pixeles)
    if formato in ("ia16", "ia8"):
        ia = [_gris(p, formato, True) for p in pixeles]
        if formato == "ia16":
            return bytes(c for par in ia for c in par)
        return bytes((_a4(i, "intensidad") << 4) | _a4(a, "alfa") for i, a in ia)
    grises = [_gris(p, formato, False)[0] for p in pixeles]
    if formato == "i8":
        return bytes(grises)
    if len(grises) % 2:
        raise ErrorFormato("i4 necesita un numero par de pixeles")
    return bytes((_a4(grises[i], "intensidad") << 4) | _a4(grises[i + 1], "intensidad")
                 for i in range(0, len(grises), 2))


def leer_inc_c(texto):
    """(bytes big-endian, ancho) de una lista de 0xNN (ancho 1) o 0xNNNN (ancho 2)."""
    if re.search(r"[A-Za-z_]{2,}", TOKEN_RE.sub("", texto)):
        raise ErrorFormato(".inc.c con algo que no es una lista de datos")
    tokens = TOKEN_RE.findall(texto)
    digitos = {len(t) for t in tokens}
    if digitos not in ({2}, {4}):
        raise ErrorFormato(".inc.c con valores de %r digitos (se espera 2 o 4)" % sorted(digitos))
    ancho = digitos.pop() // 2
    return bytes(b for t in tokens for b in int(t, 16).to_bytes(ancho, "big")), ancho


def escribir_inc_c(datos, ancho):
    """Texto .inc.c como los del repo: 16 valores u8 u 8 valores u16 por linea."""
    if ancho not in (1, 2) or len(datos) % ancho:
        raise ErrorFormato("ancho %d invalido para %d bytes" % (ancho, len(datos)))
    valores = ["0x" + datos[i:i + ancho].hex() for i in range(0, len(datos), ancho)]
    por_linea = 16 // ancho
    return "".join(", ".join(valores[i:i + por_linea]) + ",\n" for i in range(0, len(valores), por_linea))


def descomprimir_mio0(datos):
    """Datos de un bloque MIO0 (misma logica que decodificar_mio0 en C)."""
    if datos[:4] != b"MIO0":
        raise ErrorFormato("no empieza con MIO0")
    tamanio = int.from_bytes(datos[4:8], "big")
    comp = int.from_bytes(datos[8:12], "big")
    sin_comp = int.from_bytes(datos[12:16], "big")
    salida = bytearray()
    bit = 0
    while len(salida) < tamanio:
        if datos[16 + (bit >> 3)] & (0x80 >> (bit & 7)):
            salida.append(datos[sin_comp])
            sin_comp += 1
        else:
            longitud = (datos[comp] >> 4) + 3
            distancia = ((datos[comp] & 0x0F) << 8) + datos[comp + 1] + 1
            comp += 2
            for _ in range(longitud):
                salida.append(salida[-distancia])
        bit += 1
    return bytes(salida)
