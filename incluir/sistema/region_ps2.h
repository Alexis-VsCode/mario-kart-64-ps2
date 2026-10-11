#ifndef SISTEMA_REGION_PS2_H
#define SISTEMA_REGION_PS2_H

#include <stddef.h>

typedef enum { REGION_DESCONOCIDA, REGION_NTSC, REGION_PAL } RegionPs2;

// rom0:ROMVER empieza con 14 caracteres «VVVVRTAAAAMMDD»: versión de la BIOS
// en 4 cifras, región (J Japón, A América, E Europa, H Asia, C China), tipo
// (C consola, D desarrollo) y fecha en 8 cifras
#define LARGO_ROMVER 14

static inline int romver_son_cifras(const char *texto, int desde, int hasta)
{
    int i;

    for (i = desde; i < hasta; i++) {
        if (texto[i] < '0' || texto[i] > '9') {
            return 0;
        }
    }
    return 1;
}

// Región de los primeros largo bytes de rom0:ROMVER, que no necesitan el 0
// final. Solo la E es PAL. Un texto NULL, corto o con otro formato da
// REGION_DESCONOCIDA; lo que sigue a los 14 caracteres no se mira.
static inline RegionPs2 region_de_romver(const char *texto, int largo)
{
    if (texto == NULL || largo < LARGO_ROMVER) {
        return REGION_DESCONOCIDA;
    }
    if (!romver_son_cifras(texto, 0, 4) || !romver_son_cifras(texto, 6, LARGO_ROMVER)) {
        return REGION_DESCONOCIDA;
    }
    if (texto[5] != 'C' && texto[5] != 'D') {
        return REGION_DESCONOCIDA;
    }
    switch (texto[4]) {
        case 'E':
            return REGION_PAL;
        case 'J':
        case 'A':
        case 'H':
        case 'C':
            return REGION_NTSC;
        default:
            return REGION_DESCONOCIDA;
    }
}

#endif
