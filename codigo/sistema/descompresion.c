#include <stdint.h>
#include <string.h>

#include <ultra64.h>

#include "graficos/memoria_texturas.h"
#include "sistema/descompresion_textura_menu.h"
#include "sistema/sistema_ps2.h"

#define LONGITUD_CABECERA_MIO0 16

int codificar_mio0(const unsigned char *in, unsigned int longitud, unsigned char *salida);

static u32 leer_be_u32(const u8 *p)
{
    return ((u32) p[0] << 24) | ((u32) p[1] << 16) | ((u32) p[2] << 8) | p[3];
}

static void mio0decode_impl(u8 *orig_, u8 *dst);

void mio0decode(u8 *orig_, u8 *dst)
{
    u32 size = leer_be_u32(&orig_[4]);

    escribir_ram_tmem_ps2(dst, size);
    mio0decode_impl(orig_, dst);
    escribir_ram_tmem_ps2(dst, size);
}

static void mio0decode_impl(u8 *orig_, u8 *dst)
{
    u32 tamanio_dest;
    u32 desplazamiento_comp;
    u32 desplazamiento_sin_comp;
    u32 escrito = 0;
    u32 indice_bit = 0;
    u32 indice_comp = 0;
    u32 indice_sin_comp = 0;
    const u8 *bits = &orig_[LONGITUD_CABECERA_MIO0];

    if (orig_[0] != 'M' || orig_[1] != 'I' || orig_[2] != 'O' || orig_[3] != '0') {
        registrar("mio0decode: cabecera inválida en %p", orig_);
        detener_por_error("datos MIO0 corruptos");
    }

    tamanio_dest = leer_be_u32(&orig_[4]);
    desplazamiento_comp = leer_be_u32(&orig_[8]);
    desplazamiento_sin_comp = leer_be_u32(&orig_[12]);

    while (escrito < tamanio_dest) {
        if (bits[indice_bit >> 3] & (0x80 >> (indice_bit & 7))) {
            dst[escrito++] = orig_[desplazamiento_sin_comp + indice_sin_comp++];
        } else {
            const u8 *v = &orig_[desplazamiento_comp + indice_comp];
            u32 longitud = (v[0] >> 4) + 3;
            u32 distancia = (((u32) (v[0] & 0x0F)) << 8) + v[1] + 1;
            u8 *salida = &dst[escrito];
            const u8 *from = salida - distancia;
            u32 i;

            indice_comp += 2;
            for (i = 0; i < longitud; i++) {
                salida[i] = from[i];
            }
            escrito += longitud;
        }
        indice_bit++;
    }
}

void funcion_80040030(u8 *orig_, u8 *dst)
{
    mio0decode(orig_, dst);
}

static const u8 *orig_codificacion;

s32 funcion_80040174(void *buffer, s32 size, s32 dest)
{
    (void) dest;
    /* En N64 esta etapa preparaba el diccionario en `dest` */
    orig_codificacion = (const u8 *) buffer;
    return size;
}

s32 mio0encode(s32 entrada, s32 size, s32 dest)
{
    (void) entrada;
    if (orig_codificacion == NULL || size <= 0) {
        return 0;
    }
    return codificar_mio0(orig_codificacion, (unsigned int) size, (unsigned char *) (uintptr_t) dest);
}

/* Texturas de menu: TKMK00 original o MIO0 reemplazado (ver descompresion_textura_menu.h) */
void tkmk00decode(u32 *orig_, u8 *tmp_buffer, u16 *salida_rgba_16, s32 alpha_color_2)
{
    u32 size = tamanio_textura_menu((const uint8_t *) orig_);

    escribir_ram_tmem_ps2(salida_rgba_16, size);
    if (decodificar_textura_menu((uint8_t *) orig_, tmp_buffer, (uint8_t *) salida_rgba_16, alpha_color_2) !=
        TEXTURA_MENU_OK) {
        registrar("tkmk00decode: firma desconocida en %p", orig_);
        detener_por_error("textura de menú corrupta");
    }
    escribir_ram_tmem_ps2(salida_rgba_16, size);
}
