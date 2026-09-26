#!/usr/bin/env python3
"""Copia las texturas u16/u32 con los bytes invertidos para el EE.

    invertir_texturas.py [--stamp sello] <salida> <carpeta> [<carpeta> ...]
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
    stamp = None
    if args[:1] == ['--stamp']:
        stamp, args = args[1], args[2:]
    out_dir = args[0]
    includes = find_includes(args[1:])
    written = 0
    for inc, width in sorted(includes.items()):
        if not os.path.exists(inc):
            sys.exit('invertir_texturas: no existe %s (¿faltan los assets?)' % inc)
        dst = os.path.join(out_dir, inc)
        src_mtime = os.path.getmtime(inc)
        if os.path.exists(dst) and os.path.getmtime(dst) >= src_mtime:
            continue
        with open(inc, encoding='utf-8', errors='replace') as f:
            text = f.read()
        if re.search(r'[A-Za-z_]{2,}', HEX_RE.sub('', text)):
            sys.exit('invertir_texturas: %s no es un array de datos puro' % inc)
        text = HEX_RE.sub(lambda m: swap_value(m, width), text)
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
