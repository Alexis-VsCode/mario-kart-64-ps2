#!/usr/bin/env python3
"""Genera el script del enlazador de la ROM: cada bloque en su direccion segmentada.

    generar_rom_ld.py <carpeta_build> > rom.ld
"""
import sys

COURSES = [
    'mario_raceway', 'choco_mountain', 'bowsers_castle', 'banshee_boardwalk',
    'yoshi_valley', 'frappe_snowland', 'koopa_troopa_beach', 'royal_raceway',
    'luigi_raceway', 'moo_moo_farm', 'toads_turnpike', 'kalimari_desert',
    'sherbet_land', 'rainbow_road', 'wario_stadium', 'block_fort',
    'skyscraper', 'double_deck', 'dks_jungle_parkway', 'big_donut',
]

KARTS = ['luigi', 'mario', 'yoshi', 'peach', 'wario', 'toad', 'donkey_kong', 'bowser']


def segments(b):
    """Dos listas de (nombre, vma, [entradas de entrada], alineacion final, subalign):
    lo que va en el ELF y lo que se carga del disco en segundo plano."""
    head = [
        ('data_segment2', '0x02000000',
         ['%s/codigo/datos/texturas.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON)' % b,
          '%s/codigo/datos/segmento_datos_2.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON)' % b], 0, None),
        ('common_textures', '0x0D000000',
         ['%s/recursos/comunes/datos_comunes.mio0.o(.data)' % b], 0x10, None),
        ('startupLogo', '0x06000000',
         ['%s/recursos/logo_inicio/logo_inicio.mio0.o(.data)' % b], 0x10, None),
        ('audio_banks', '0x0', ['%s/sonido/bancos_instrumentos.o(.data)' % b], 0, None),
        ('sequences', '0x25FD00', ['%s/codigo/datos/secuencias_musica.o(.data)' % b], 0x40, None),
        ('instrument_sets', '.', ['%s/codigo/datos/conjuntos_instrumentos.o(.data)' % b], 0, None),
    ]
    stream = [
        ('audio_tables', '0x13840', ['%s/sonido/muestras_audio.o(.data)' % b], 0, None),
        ('other_textures', '0x0F000000',
         ['%s/codigo/datos/otras_texturas.o(.data)' % b], 0x10, None),
        ('textures_0a', '0x0A000000',
         ['%s/codigo/datos/texturas_seleccion.o(.data)' % b,
          '%s/codigo/datos/texturas_fuentes.o(.data)' % b], 0x10, None),
        ('textures_0b', '0x0B000000',
         ['%s/codigo/datos/texturas_tkmk00.o(.data)' % b], 0x10, None),
        ('kart_textures', '0x0F000000',
         ['%s/codigo/datos/karts/kart_%s.o(.data)' % (b, k) for k in KARTS] +
         ['%s/recursos/pistas/fantasmas_personal.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON)' % b], 0, '0x10'),
        ('ceremonyData', '0x0B000000',
         ['%s/recursos/ceremonia/datos_ceremonia.mio0.o(.data)' % b], 0x10, None),
    ]
    for c in COURSES:
        stream.append(('course_%s_dl_mio0' % c, '0x06000000',
                       ['%s/recursos/pistas/%s/datos_pista.mio0.o(.data)' % (b, c)], 0x10, None))
    for c in COURSES:
        stream.append(('course_%s_offsets' % c, '0x09000000',
                       ['%s/recursos/pistas/%s/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON)' % (b, c)], 0x10, None))
    for c in COURSES:
        stream.append(('%s_vertex' % c, '0x0F000000',
                       ['%s/recursos/pistas/%s/geografia.mio0.o(.data)' % (b, c)], 0x10, None))
    return head, stream


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    b = sys.argv[1]
    out = []
    w = out.append
    w('/* Generado por herramientas/generar_rom_ld.py: no editar. */')
    w('OUTPUT_ARCH(mips:5900)')
    w('SECTIONS')
    w('{')
    w('    __romPos = 0;')
    head, stream = segments(b)
    for group in (head, stream):
        if group is stream:
            w('    __romPos = ALIGN(__romPos + 0x1000, 0x10000);')
            w('    __rom_stream_start = __romPos;')
        for name, vma, inputs, align, subalign in group:
            sub = ' SUBALIGN(%s)' % subalign if subalign else ''
            w('    _%sSegmentStart = ADDR(.%s);' % (name, name))
            w('    __romseg_%s_start = __romPos;' % name)
            w('    .%s %s : AT(__romPos)%s' % (name, vma, sub))
            w('    {')
            for i in inputs:
                w('        KEEP(%s);' % i)
            if align:
                w('        . = ALIGN(0x%x);' % align)
            w('    }')
            w('    _%sSegmentEnd = ADDR(.%s) + SIZEOF(.%s);' % (name, name, name))
            w('    _%sSegmentSize = SIZEOF(.%s);' % (name, name))
            w('    __romseg_%s_end = __romPos + SIZEOF(.%s);' % (name, name))
            w('    __romPos += SIZEOF(.%s);' % name)
            w('    __romPos = ALIGN(__romPos, 16);')
    w('    __rom_size = __romPos;')
    w('    /DISCARD/ : { *(*) }')
    w('}')
    print('\n'.join(out))


if __name__ == '__main__':
    main()
