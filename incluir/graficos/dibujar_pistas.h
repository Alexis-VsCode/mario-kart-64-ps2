#ifndef GRAFICOS_DIBUJAR_PISTAS_H
#define GRAFICOS_DIBUJAR_PISTAS_H

#include "carrera/preparacion_carrera.h"

void funcion_8029122C(struct desconocido_struct_800DC5EC*, s32);
s32 funcion_80290C20(Camara*);
void analizar_displaylists_circuito(uintptr_t);
void renderizar_segmentos_circuito(uintptr_t, struct desconocido_struct_800DC5EC*);
void funcion_80291198(void);
void funcion_802911C4(void);
void renderizar_mario_raceway(struct desconocido_struct_800DC5EC*);
void renderizar_choco_mountain(struct desconocido_struct_800DC5EC*);
void renderizar_bowsers_castle(struct desconocido_struct_800DC5EC*);
void renderizar_banshee_boardwalk(struct desconocido_struct_800DC5EC*);
void renderizar_yoshi_valley(struct desconocido_struct_800DC5EC*);
void renderizar_frappe_snowland(struct desconocido_struct_800DC5EC*);
void renderizar_koopa_troopa_beach(struct desconocido_struct_800DC5EC*);
void renderizar_royal_raceway(struct desconocido_struct_800DC5EC*);
void renderizar_luigi_raceway(struct desconocido_struct_800DC5EC*);
void renderizar_toads_turnpike(struct desconocido_struct_800DC5EC*);
void renderizar_kalimari_desert(struct desconocido_struct_800DC5EC*);
void renderizar_sherbet_land(struct desconocido_struct_800DC5EC*);
void renderizar_rainbow_road(struct desconocido_struct_800DC5EC*);
void renderizar_wario_stadium(struct desconocido_struct_800DC5EC*);
void renderizar_block_fort(struct desconocido_struct_800DC5EC*);
void renderizar_skyscraper(struct desconocido_struct_800DC5EC*);
void renderizar_double_deck(struct desconocido_struct_800DC5EC*);
void renderizar_dks_jungle_parkway(struct desconocido_struct_800DC5EC*);
void renderizar_big_donut(struct desconocido_struct_800DC5EC*);
void renderizar_creditos_circuito(void);
void renderizar_circuito(struct desconocido_struct_800DC5EC*);
void funcion_80295BF8(s32);
void funcion_80295C6C(void);
void funcion_80295D50(s16, s16);
void funcion_80295D6C(void);
void circuito_generar_colision_malla(void);
void actualizar_agua_circuito(void);
void funcion_802969F8(void);

extern s32 dato_8015F59C;

extern s32 dato_802B87C4;
extern s32 dato_802B87C8;
extern s32 dato_802B87CC;
extern s32 dato_802B87BC;

extern Lights1 dato_800DC610[];

extern Lights1 dato_800DC610[];

extern u16 triangulos_colision_num;

#endif
