#ifndef SISTEMA_CRC32_H
#define SISTEMA_CRC32_H

#include <PR/ultratypes.h>

// CRC32 IEEE 802.3 (polinomio reflejado 0xEDB88320, valor inicial y final
// invertidos): el de zlib. Lo comparten la imagen de guardado y el archivo de
// opciones, así que cambiarlo invalida los datos de las Memory Card existentes.
static inline u32 crc32(const u8 *p, u32 n)
{
    u32 crc = 0xFFFFFFFFu;

    while (n--) {
        int k;

        crc ^= *p++;
        for (k = 0; k < 8; k++) {
            crc = (crc >> 1) ^ (0xEDB88320u & -(crc & 1));
        }
    }
    return ~crc;
}

#endif
