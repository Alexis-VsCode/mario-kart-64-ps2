#ifndef MEMORIA_TABLAS_TRIGONOMETRICAS_H
#define MEMORIA_TABLAS_TRIGONOMETRICAS_H

extern f32 tabla_seno[];
#ifdef AVOID_UB
#define tabla_coseno (tabla_seno + 0x400)
#else
extern f32 tabla_coseno[];
#endif

extern s16 tabla_arctan[];

#endif
