#ifndef GRAFICOS_VISTA_PANORAMICA_H
#define GRAFICOS_VISTA_PANORAMICA_H

#include "sistema/opciones_port.h"

// Vista panorámica Hor+: en FORMATO_PANORAMICO la tele estira la
// imagen a 16:9, así que se ve 4/3 más de ancho con el mismo alto. Se aplica a
// aspecto_pantalla donde la carrera, la vista dividida y la ceremonia lo
// asignan, nunca en guPerspectiveF, para que los menús no cambien.

static inline f32 aspecto_panoramico(f32 base, int formato)
{
    return formato == FORMATO_PANORAMICO ? base * 4.0f / 3.0f : base;
}

// Cono horizontal de es_visible_objeto_en_camara (0x10000 = una vuelta).
// Se ensancha 4/3 en lineal y no en tangente: atan(4/3 * tan(a)) <= 4/3 * a
// para todo a entre 0 y 90 grados, así que el cono lineal cubre siempre el
// campo visible real (solo dibuja algún objeto de más) y no necesita
// trigonometría. Una vuelta completa es el tope.
static inline u16 cono_visibilidad(u16 angulo, int formato)
{
    u32 ancho;

    if (formato != FORMATO_PANORAMICO) {
        return angulo;
    }
    ancho = (u32) angulo * 4 / 3;
    return ancho > 0xFFFF ? 0xFFFF : (u16) ancho;
}

#endif
