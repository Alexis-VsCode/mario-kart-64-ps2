#ifndef JUEGO_CURVAS_H
#define JUEGO_CURVAS_H

#include <juego/estructuras_comunes.h>

typedef struct PuntoControlSpline {
     Vec3s pos;
     s16 velocidad;
} PuntoControlSpline;

typedef struct DatosSpline {
    s16 puntos_control_num;
    PuntoControlSpline puntos_control[];
} DatosSpline;

#endif
