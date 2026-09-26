#ifndef CARRERA_APARICION_JUGADORES_H
#define CARRERA_APARICION_JUGADORES_H

#include "camara.h"
#include <juego/estructuras_comunes.h>

void aparecer_jugador(Jugador*, s8, f32, f32, f32, f32, u16, s16);
void funcion_80039AE4(void);
void funcion_80039DA4(void);
void aparecer_jugador_gp_uno_jugadores(f32*, f32*, f32);
void aparecer_jugadores_versus_un_jugador(f32*, f32*, f32);
void aparecer_jugador_gp_dos_jugadores(f32* parametro0, f32* parametro1, f32);
void aparecer_jugadores_versus_dos_jugador(f32*, f32*, f32);
void aparecer_batalla_jugadores_2j(f32*, f32*, f32);
void funcion_8003B318(f32*, f32*, f32);
void aparecer_batalla_jugadores_3j(f32*, f32*, f32);
void funcion_8003B870(f32*, f32*, f32);
void aparecer_batalla_jugadores_4j(f32*, f32*, f32);
void funcion_8003BE30(void);
void funcion_8003C0F0(void);
void funcion_8003CD78(void);
void funcion_8003CD98(Jugador*, Camara*, s8, s8);
void funcion_8003D080(void);
void funcion_8003DB5C(void);

extern f32 dato_80165210[];
extern f32 dato_80165230[];
extern s16 dato_80165270[];
extern f32 jugador_actual_rapidez[];
extern f32 dato_801652A0[];
extern s32 dato_801652C0[];
extern s32 dato_801652E0[];
extern s16 dato_80165300[];
extern u16 indice_camino_copia_por_id_jugador[];
extern s16 copia_mas_cercano_camino_punto_por_id_jugador[];
extern s16 dato_80165330[];
extern s16 dato_80165340;
extern Jugador* dato_801653C0[];
extern bool jugador_es_acelerador_activo[];
extern s32 dato_80165400[];
extern s32 frame_desde_ultimo_combo_a[];
extern s32 interruptor_cantidad_a[];
extern bool es_jugador_triple_a_boton_combo[];
extern s32 temporizador_impulso_triple_a_combo[];
extern bool jugador_es_freno_activo[];
extern s32 dato_801654C0[];
extern s32 frame_desde_ultimo_combo_b[];
extern s32 cambio_cantidad_b[];
extern bool es_jugador_triple_b_boton_combo[];
extern s32 temporizador_impulso_triple_b_combo[];
extern s16 cpu_elegir_personajes[];
extern s16 dato_8016556E;
extern s16 dato_80165570;
extern s16 dato_80165572;
extern s16 dato_80165574;
extern s16 dato_80165576;
extern s16 dato_80165578;
extern s16 dato_8016557A;
extern s16 dato_8016557C;
extern s16 dato_8016557E;
extern s16 dato_80165580;
extern s16 dato_80165582;

#endif
