#!/usr/bin/env python3
"""Copia las texturas u16/u32 con los bytes invertidos para el EE.

    invertir_texturas.py [--stamp sello] [--superponer carpeta] <salida> <carpeta> [<carpeta> ...]

Con --superponer, si existe <carpeta>/<ruta del .inc.c> se invierte esa
version en lugar de la del repo. Como el origen elegido puede cambiar sin
que cambie ningun mtime, en ese modo se compara el resultado con la salida.
"""
import os
import re
import sys

DECL_RE = re.compile(
    r'\b(u16|s16|u32|s32|uint16_t|uint32_t)\s+[A-Za-z_][A-Za-z0-9_]*\s*'
    r'(?:\[[^\]]*\]\s*)+=\s*\{',
    re.S)
INCLUDE_RE = re.compile(r'#\s*include\s+"([^"]+\.inc\.c)"')
HEX_RE = re.compile(r'0[xX]([0-9a-fA-F]+)')
TEXTURE_NAME_RE = re.compile(r'\.(rgba16|rgba32|ia16|tlut)\.inc\.c$')


def swap_value(match, width):
    value = int(match.group(1), 16)
    if width == 2:
        value &= 0xFFFF
        out = ((value & 0xFF) << 8) | (value >> 8)
        return '0x%04x' % out
    value &= 0xFFFFFFFF
    out = int.from_bytes(value.to_bytes(4, 'big'), 'little')
    return '0x%08x' % out


def initializer(text, start):
    """Texto del inicializador que empieza justo despues de su '{' en start."""
    depth, i = 1, start
    while depth and i < len(text):
        if text[i] == '{':
            depth += 1
        elif text[i] == '}':
            depth -= 1
        i += 1
    return text[start:i]


def find_includes(dirs):
    """Devuelve {ruta_incluida: ancho_en_bytes}."""
    found = {}
    for top in dirs:
        for root, _dirs, files in os.walk(top):
            for name in files:
                if not name.endswith('.c') or TEXTURE_NAME_RE.search(name):
                    continue
                path = os.path.join(root, name)
                with open(path, encoding='utf-8', errors='replace') as f:
                    text = f.read()
                for m in DECL_RE.finditer(text):
                    width = 2 if '16' in m.group(1) else 4
                    for inc in INCLUDE_RE.findall(initializer(text, m.end())):
                        if not TEXTURE_NAME_RE.search(os.path.basename(inc)):
                            continue
                        prev = found.get(inc)
                        if prev is not None and prev != width:
                            sys.exit('invertir_texturas: %s declarado con anchos distintos' % inc)
                        found[inc] = width
    return found


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    args = sys.argv[1:]
    stamp = superponer = None
    while args[:1] in (['--stamp'], ['--superponer']) and len(args) > 1:
        if args[0] == '--stamp':
            stamp = args[1]
        else:
            superponer = args[1]
        args = args[2:]
    if len(args) < 2:
        sys.exit(__doc__)
    out_dir = args[0]
    includes = find_includes(args[1:])
    written = 0
    for inc, width in sorted(includes.items()):
        src = inc
        if superponer and os.path.exists(os.path.join(superponer, inc)):
            src = os.path.join(superponer, inc)
        if not os.path.exists(src):
            sys.exit('invertir_texturas: no existe %s (¿faltan los assets?)' % src)
        dst = os.path.join(out_dir, inc)
        if not superponer and os.path.exists(dst) and os.path.getmtime(dst) >= os.path.getmtime(src):
            continue
        with open(src, encoding='utf-8', errors='replace') as f:
            text = f.read()
        if re.search(r'[A-Za-z_]{2,}', HEX_RE.sub('', text)):
            sys.exit('invertir_texturas: %s no es un array de datos puro' % src)
        text = HEX_RE.sub(lambda m: swap_value(m, width), text)
        if superponer and os.path.exists(dst):
            with open(dst) as f:
                if f.read() == text:
                    continue
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        with open(dst, 'w') as f:
            f.write(text)
        written += 1
    wanted = {os.path.normpath(os.path.join(out_dir, inc)) for inc in includes}
    removed = 0
    for root, _dirs, files in os.walk(out_dir):
        for name in files:
            path = os.path.normpath(os.path.join(root, name))
            if name.endswith('.inc.c') and path not in wanted:
                os.remove(path)
                removed += 1
    print('invertir_texturas: %d includes u16/u32, %d regenerados, %d obsoletos borrados'
          % (len(includes), written, removed))
    if stamp and (written or removed or not os.path.exists(stamp)):
        with open(stamp, 'w'):
            pass


if __name__ == '__main__':
    main()
