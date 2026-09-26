#ifndef SISTEMA_DESCOMPRESION_TKMK00_H
#define SISTEMA_DESCOMPRESION_TKMK00_H

#include <stdint.h>

void decodificar_tkmk00(uint8_t *tkmk, uint8_t *tmp_buf, uint8_t *rgba16, int32_t alpha_color);

#endif
