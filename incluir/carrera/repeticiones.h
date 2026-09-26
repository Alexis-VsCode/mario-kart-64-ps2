#ifndef CARRERA_REPETICIONES_H
#define CARRERA_REPETICIONES_H

#include <PR/os.h>
#include <juego/estructuras_comunes.h>

void funcion_80005B18(void);
void cargar_fantasma_circuito(void);
void publicar_contrarreloj_repeticion_carga(void);
void cargar_fantasma_jugador(void);
void fijar_fantasma_personal(void);
s32 funcion_800051C4(void);
void funcion_8000522C(void);
void funcion_800052A4(void);
void funcion_80005310(void);
void publicar_contrarreloj_repeticion_proceso(void);
void procesar_repeticion_fantasma_circuito(void);
void procesar_repeticion_fantasma_jugador(void);
void funcion_8000599C(void);
void funcion_80005AE8(Jugador*);
void funcion_80005E6C(void);
void bucle_repeticiones(void);

extern s32 mio0encode(s32 entrada, s32, s32);
extern s32 funcion_80040174(void*, s32, s32);

extern s32 dato_80162DC8;
extern s32 dato_80162DCC;
extern u16 b_jugador_fantasma_desactivado;
extern u16 b_circuito_fantasma_desactivado;
extern u16 dato_80162DD8;
extern s32 dato_80162E00;
extern s32 dato_80162DE0;
extern s32 dato_80162DE4;
extern s32 dato_80162DE8;
extern s32 pausa_disparado;
extern s32 publicar_contrarreloj_guardado_no_puede_repeticion;

#endif
