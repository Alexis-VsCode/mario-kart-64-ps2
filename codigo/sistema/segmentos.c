#include <malloc.h>
#include <string.h>

#include <ultra64.h>

#include "sistema/sistema_ps2.h"

extern u8 _inicio_datos_carreras[], _fin_datos_carreras[];
extern u8 _inicio_bss_carreras[], _fin_bss_carreras[];
extern u8 _inicio_datos_final[], _fin_datos_final[];
extern u8 _inicio_bss_final[], _fin_bss_final[];

static u8 *copia_carrera;
static u8 *copia_final;

static u8 *copia(const u8 *empezar, const u8 *end)
{
    size_t size = end - empezar;
    u8 *copiar = memalign(16, size ? size : 16);

    if (copiar == NULL) {
        detener_por_error("sin memoria para la copia de los segmentos");
    }
    memcpy(copiar, empezar, size);
    return copiar;
}

void guardar_segmentos_iniciales(void)
{
    copia_carrera = copia(_inicio_datos_carreras, _fin_datos_carreras);
    copia_final = copia(_inicio_datos_final, _fin_datos_final);
    registrar("segmentos: carrera %u+%u B, final %u+%u B",
            (unsigned) (_fin_datos_carreras - _inicio_datos_carreras), (unsigned) (_fin_bss_carreras - _inicio_bss_carreras),
            (unsigned) (_fin_datos_final - _inicio_datos_final), (unsigned) (_fin_bss_final - _inicio_bss_final));
}

void reiniciar_segmento_carreras(void)
{
    memcpy(_inicio_datos_carreras, copia_carrera, _fin_datos_carreras - _inicio_datos_carreras);
    memset(_inicio_bss_carreras, 0, _fin_bss_carreras - _inicio_bss_carreras);
}

void reiniciar_segmento_final(void)
{
    memcpy(_inicio_datos_final, copia_final, _fin_datos_final - _inicio_datos_final);
    memset(_inicio_bss_final, 0, _fin_bss_final - _inicio_bss_final);
}

void rmon_printf(const char *fmt, ...)
{
    (void) fmt;
}
