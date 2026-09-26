#ifndef CARRERA_CAMINOS_VEHICULOS_H
#define CARRERA_CAMINOS_VEHICULOS_H

#include <ultra64.h>

#include "juego/camino.h"

s32 busqueda_camino_vehiculo_ps2(void *dest, const PuntoCaminoPista *orig_, s32 puntos_camino_num, s32 espejo);

void comprobar_camino_vehiculo_ps2(const void *computed, s32 cantidad, const PuntoCaminoPista *orig_, s32 puntos_camino_num,
                            s32 espejo);

#endif
