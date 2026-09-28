#include <stdint.h>
#include <string.h>

#include "sistema/descompresion_mio0.h"
#include "sistema/descompresion_textura_menu.h"
#include "sistema/descompresion_tkmk00.h"

static int es_tkmk00(const uint8_t *datos)
{
    return memcmp(datos, "TKMK00", 6) == 0;
}

static int es_mio0(const uint8_t *datos)
{
    return memcmp(datos, "MIO0", 4) == 0;
}

uint32_t tamanio_textura_menu(const uint8_t *datos)
{
    if (es_tkmk00(datos)) {
        /* ancho y alto en 0x8 y 0xA */
        return (((uint32_t) datos[8] << 8) | datos[9]) * (((uint32_t) datos[10] << 8) | datos[11]) * 2;
    }
    if (es_mio0(datos)) {
        return ((uint32_t) datos[4] << 24) | ((uint32_t) datos[5] << 16) | ((uint32_t) datos[6] << 8) | datos[7];
    }
    return 0;
}

int decodificar_textura_menu(uint8_t *datos, uint8_t *tmp, uint8_t *rgba16, int32_t alfa)
{
    if (es_tkmk00(datos)) {
        decodificar_tkmk00(datos, tmp, rgba16, alfa);
        return TEXTURA_MENU_OK;
    }
    if (es_mio0(datos)) {
        decodificar_mio0(datos, rgba16, NULL);
        return TEXTURA_MENU_OK;
    }
    return TEXTURA_MENU_FIRMA_DESCONOCIDA;
}
