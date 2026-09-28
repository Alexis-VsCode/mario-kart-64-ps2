#!/usr/bin/env python3
"""Lee y escribe PNG de 8 bits por muestra, solo con la biblioteca estandar.

Tipos: gris, rgb, indexado (PLTE + tRNS), gris_alfa y rgba. Al leer se
deshacen los 5 filtros; al escribir se usa siempre el filtro 0 y no se
guarda tIME, asi que la misma imagen da siempre los mismos bytes. Se
rechazan 16 bits, menos de 8 bits y el entrelazado.
"""
import struct
import zlib

FIRMA = b"\x89PNG\r\n\x1a\n"
TIPOS = {0: "gris", 2: "rgb", 3: "indexado", 4: "gris_alfa", 6: "rgba"}
CODIGOS = {v: k for k, v in TIPOS.items()}
CANALES = {"gris": 1, "rgb": 3, "indexado": 1, "gris_alfa": 2, "rgba": 4}


class ErrorPng(ValueError):
    pass


class Imagen:
    """pixeles: muestras de 8 bits fila por fila, sin bytes de filtro.
    paleta: lista de (r, g, b, a), solo en indexado."""

    def __init__(self, ancho, alto, tipo, pixeles, paleta=None):
        self.ancho = ancho
        self.alto = alto
        self.tipo = tipo
        self.pixeles = bytes(pixeles)
        self.paleta = paleta

    def a_rgba(self):
        """Lista de (r, g, b, a) por pixel, sea cual sea el tipo."""
        p = self.pixeles
        if self.tipo == "gris":
            return [(v, v, v, 255) for v in p]
        if self.tipo == "gris_alfa":
            return [(p[i], p[i], p[i], p[i + 1]) for i in range(0, len(p), 2)]
        if self.tipo == "rgb":
            return [(p[i], p[i + 1], p[i + 2], 255) for i in range(0, len(p), 3)]
        if self.tipo == "rgba":
            return [tuple(p[i:i + 4]) for i in range(0, len(p), 4)]
        return [self.paleta[v] for v in p]


def _paeth(a, b, c):
    p = a + b - c
    pa, pb, pc = abs(p - a), abs(p - b), abs(p - c)
    if pa <= pb and pa <= pc:
        return a
    return b if pb <= pc else c


def _desfiltrar(datos, ancho_fila, alto, bpp):
    salida = bytearray()
    previa = bytearray(ancho_fila)
    pos = 0
    for _ in range(alto):
        if pos + 1 + ancho_fila > len(datos):
            raise ErrorPng("faltan datos de imagen")
        filtro = datos[pos]
        fila = bytearray(datos[pos + 1:pos + 1 + ancho_fila])
        pos += 1 + ancho_fila
        if filtro == 1:
            for i in range(bpp, ancho_fila):
                fila[i] = (fila[i] + fila[i - bpp]) & 0xFF
        elif filtro == 2:
            for i in range(ancho_fila):
                fila[i] = (fila[i] + previa[i]) & 0xFF
        elif filtro == 3:
            for i in range(ancho_fila):
                a = fila[i - bpp] if i >= bpp else 0
                fila[i] = (fila[i] + ((a + previa[i]) >> 1)) & 0xFF
        elif filtro == 4:
            for i in range(ancho_fila):
                a = fila[i - bpp] if i >= bpp else 0
                c = previa[i - bpp] if i >= bpp else 0
                fila[i] = (fila[i] + _paeth(a, previa[i], c)) & 0xFF
        elif filtro != 0:
            raise ErrorPng("filtro %d desconocido" % filtro)
        salida += fila
        previa = fila
    return bytes(salida)


def decodificar(datos):
    """Imagen a partir de los bytes de un PNG."""
    if not datos.startswith(FIRMA):
        raise ErrorPng("no es un PNG")
    pos = len(FIRMA)
    cabecera = None
    paleta = None
    alfas = b""
    idat = bytearray()
    while True:
        if pos + 12 > len(datos):
            raise ErrorPng("PNG cortado")
        n = struct.unpack(">I", datos[pos:pos + 4])[0]
        tipo = datos[pos + 4:pos + 8]
        contenido = datos[pos + 8:pos + 8 + n]
        if len(contenido) != n or pos + 12 + n > len(datos):
            raise ErrorPng("PNG cortado")
        crc = struct.unpack(">I", datos[pos + 8 + n:pos + 12 + n])[0]
        if crc != zlib.crc32(tipo + contenido) & 0xFFFFFFFF:
            raise ErrorPng("CRC invalido en %s" % tipo.decode("latin-1"))
        pos += 12 + n
        if tipo == b"IHDR":
            cabecera = struct.unpack(">IIBBBBB", contenido)
        elif tipo == b"PLTE":
            paleta = [tuple(contenido[i:i + 3]) for i in range(0, n, 3)]
        elif tipo == b"tRNS":
            alfas = contenido
        elif tipo == b"IDAT":
            idat += contenido
        elif tipo == b"IEND":
            break
        elif not tipo[0] & 0x20:
            raise ErrorPng("trozo critico desconocido %s" % tipo.decode("latin-1"))
    if cabecera is None:
        raise ErrorPng("falta IHDR")
    ancho, alto, bits, codigo, compresion, filtro, entrelazado = cabecera
    if bits != 8:
        raise ErrorPng("solo 8 bits por muestra (tiene %d)" % bits)
    if entrelazado:
        raise ErrorPng("el entrelazado no esta soportado")
    if codigo not in TIPOS or compresion or filtro:
        raise ErrorPng("tipo de color o metodo no soportado")
    tipo = TIPOS[codigo]
    if tipo == "indexado":
        if paleta is None:
            raise ErrorPng("indexado sin PLTE")
        paleta = [c + ((alfas[i] if i < len(alfas) else 255),) for i, c in enumerate(paleta)]
    elif alfas:
        raise ErrorPng("tRNS solo esta soportado en indexado")
    else:
        paleta = None
    canales = CANALES[tipo]
    try:
        crudo = zlib.decompress(bytes(idat))
    except zlib.error as e:
        raise ErrorPng("IDAT corrupto: %s" % e)
    pixeles = _desfiltrar(crudo, ancho * canales, alto, canales)
    if tipo == "indexado" and pixeles and max(pixeles) >= len(paleta):
        raise ErrorPng("indice fuera de la paleta")
    return Imagen(ancho, alto, tipo, pixeles, paleta)


def _trozo(tipo, contenido):
    return (struct.pack(">I", len(contenido)) + tipo + contenido
            + struct.pack(">I", zlib.crc32(tipo + contenido) & 0xFFFFFFFF))


def codificar(imagen):
    """Bytes del PNG de una Imagen (determinista)."""
    if imagen.tipo not in CODIGOS:
        raise ErrorPng("tipo desconocido %r" % imagen.tipo)
    fila = imagen.ancho * CANALES[imagen.tipo]
    if len(imagen.pixeles) != fila * imagen.alto:
        raise ErrorPng("se esperaban %d muestras, hay %d" % (fila * imagen.alto, len(imagen.pixeles)))
    salida = FIRMA + _trozo(b"IHDR", struct.pack(">IIBBBBB", imagen.ancho, imagen.alto, 8,
                                                 CODIGOS[imagen.tipo], 0, 0, 0))
    if imagen.tipo == "indexado":
        paleta = imagen.paleta or []
        if not 0 < len(paleta) <= 256 or (imagen.pixeles and max(imagen.pixeles) >= len(paleta)):
            raise ErrorPng("paleta vacia, de mas de 256 colores o indice fuera de ella")
        salida += _trozo(b"PLTE", bytes(v for c in paleta for v in c[:3]))
        alfas = bytes(c[3] for c in paleta)
        while alfas and alfas[-1] == 255:
            alfas = alfas[:-1]
        if alfas:
            salida += _trozo(b"tRNS", alfas)
    crudo = b"".join(b"\x00" + imagen.pixeles[y * fila:(y + 1) * fila] for y in range(imagen.alto))
    salida += _trozo(b"IDAT", zlib.compress(crudo, 9))
    return salida + _trozo(b"IEND", b"")


def leer(ruta):
    with open(ruta, "rb") as f:
        return decodificar(f.read())


def escribir(ruta, imagen):
    datos = codificar(imagen)
    with open(ruta, "wb") as f:
        f.write(datos)
