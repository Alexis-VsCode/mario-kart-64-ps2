#ifndef SISTEMA_DESCOMPRESION_TEXTURA_MENU_H
#define SISTEMA_DESCOMPRESION_TEXTURA_MENU_H

#include <stdint.h>

/* Texturas de menu del segmento 0x0B: TKMK00 original o MIO0 de un RGBA16
   big-endian con el alfa ya horneado (texturas reemplazadas) */

#define TEXTURA_MENU_OK 0
#define TEXTURA_MENU_FIRMA_DESCONOCIDA (-1)

/* Bytes de RGBA16 que da la textura; 0 si la firma no se conoce */
uint32_t tamanio_textura_menu(const uint8_t *datos);

/* Decodifica segun la firma. tmp: ancho * alto bytes de trabajo del TKMK00.
   alfa: color que el TKMK00 deja transparente; el MIO0 no lo usa */
int decodificar_textura_menu(uint8_t *datos, uint8_t *tmp, uint8_t *rgba16, int32_t alfa);

#endif
