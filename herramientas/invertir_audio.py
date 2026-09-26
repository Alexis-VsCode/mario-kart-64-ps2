#!/usr/bin/env python3
"""Pasa los bancos de instrumentos y la tabla de muestras a little-endian.

    invertir_audio.py bancos.bin muestras.bin salida_bancos.bin salida_muestras.bin
"""
import struct
import sys


class Swapper:
    def __init__(self, data):
        self.src = bytes(data)
        self.out = bytearray(data)
        self.done = {}  # (offset, formato) ya convertidos

    def swap(self, off, fmt):
        """Reescribe en little-endian los campos de fmt (sin prefijo) en off."""
        key = (off, fmt)
        if key in self.done:
            return
        self.done[key] = True
        vals = struct.unpack_from('>' + fmt, self.src, off)
        struct.pack_into('<' + fmt, self.out, off, *vals)
        return vals

    def u32(self, off):
        return struct.unpack_from('>I', self.src, off)[0]

    def s16(self, off):
        return struct.unpack_from('>h', self.src, off)[0]


def convert_seqfile_header(sw):
    """ALSeqFile: s16 revision, s16 seqCount, {u32 offset, u32 len}[]."""
    rev, count = sw.swap(0, 'hh')
    for i in range(count):
        sw.swap(4 + 8 * i, 'II')
    return count


def convert_banks(data):
    sw = Swapper(data)
    count = convert_seqfile_header(sw)
    stats = {'bancos': 0, 'instrumentos': 0, 'baterias': 0, 'muestras': 0, 'envolventes': 0}
    for i in range(count):
        off, length = struct.unpack_from('>II', data, 4 + 8 * i)
        num_inst, num_drums, _a, _b = sw.swap(off, 'IIII')
        base = off + 0x10
        stats['bancos'] += 1

        def envelope(rel):
            stats['envolventes'] += 1

        def sample(rel):
            p = base + rel
            if (p, 'xxxxIIII') in sw.done:
                return
            vals = sw.swap(p, 'xxxxIIII')
            _addr, loop_rel, book_rel, _size = vals
            stats['muestras'] += 1
            lp = base + loop_rel
            _s, _e, lcount, _pad = sw.swap(lp, 'IIII') or struct.unpack_from('>IIII', data, lp)
            if lcount != 0:
                sw.swap(lp + 16, '16h')
            bp = base + book_rel
            order, npred = sw.swap(bp, 'ii') or struct.unpack_from('>ii', data, bp)
            sw.swap(bp + 8, '%dh' % (8 * order * npred))

        def sound(p):
            # AudioBankSound: u32 sample, f32 tuning
            sample_rel, _tuning = sw.swap(p, 'If') or struct.unpack_from('>If', data, p)
            if sample_rel != 0:
                sample(sample_rel)

        # AudioBank: u32 drums, u32 instruments[num_inst]
        drums_rel = sw.swap(base, 'I')[0]
        inst_rels = sw.swap(base + 4, '%dI' % num_inst) if num_inst else ()
        for rel in inst_rels:
            if rel == 0:
                continue
            p = base + rel
            if (p + 4, 'I') in sw.done:
                continue
            # Instrument: u8 x4, u32 envelope, 3 x AudioBankSound
            env_rel = sw.swap(p + 4, 'I')[0]
            for k in range(3):
                sound(p + 8 + 8 * k)
            envelope(env_rel)
            stats['instrumentos'] += 1
        if drums_rel != 0 and num_drums:
            drum_rels = sw.swap(base + drums_rel, '%dI' % num_drums)
            for rel in drum_rels:
                if rel == 0:
                    continue
                p = base + rel
                if (p + 12, 'I') in sw.done:
                    continue
                sound(p + 4)
                env_rel = sw.swap(p + 12, 'I')[0]
                envelope(env_rel)
                stats['baterias'] += 1
    return bytes(sw.out), stats


def convert_tables(data):
    """Solo la cabecera: el resto son muestras ADPCM (bytes)."""
    sw = Swapper(data)
    convert_seqfile_header(sw)
    return bytes(sw.out)


def main():
    if len(sys.argv) != 5:
        sys.exit(__doc__)
    banks = open(sys.argv[1], 'rb').read()
    tables = open(sys.argv[2], 'rb').read()
    out_banks, stats = convert_banks(banks)
    out_tables = convert_tables(tables)
    open(sys.argv[3], 'wb').write(out_banks)
    open(sys.argv[4], 'wb').write(out_tables)
    print('invertir_audio: ' + ', '.join('%s %d' % kv for kv in stats.items()))


if __name__ == '__main__':
    main()
