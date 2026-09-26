#ifndef GRAFICOS_CIELO_Y_PANTALLA_DIVIDIDA_H
#define GRAFICOS_CIELO_Y_PANTALLA_DIVIDIDA_H

#include <PR/gbi.h>
#include "carrera/preparacion_carrera.h"

#define G_LIMPIEZA_TODOS_MODOS 0xFFFFFFFF

void renderizar_cielo(Vtx*, struct desconocido_struct_800DC5EC*, s32, s32, f32*);

void funcion_802A3730(struct desconocido_struct_800DC5EC*);
void funcion_802A38AC(void);
void funcion_802A38B4(void);
void funcion_802A39E0(struct desconocido_struct_800DC5EC*);
void inicializar_zbuffer(void);
void inicializar_rdp(void);
void funcion_802A40A4(void);
void funcion_802A40AC(void);
void funcion_802A40B4(void);
void funcion_802A40BC(void);
void funcion_802A40C4(void);
void funcion_802A40CC(void);
void funcion_802A40D4(void);
void funcion_802A40DC(void);
s32 fijar_viewport2(void);
void fijar_viewport(void);
void seleccionar_framebuffer(void);
void funcion_802A4300(void);
void fijar_colores_cielo_circuito(Vtx*);
void funcion_802A487C(Vtx*, struct desconocido_struct_800DC5EC*, s32, s32, f32*);
void fijar_perspectiva_y_proporcion_aspecto(void);
void funcion_802A4EF4(void);
void funcion_802A5004(void);
void funcion_802A50EC(void);
void funcion_802A51D4(void);
void funcion_802A52BC(void);
void funcion_802A53A4(void);
void funcion_802A54A8(void);
void funcion_802A5590(void);
void funcion_802A5678(void);
void funcion_802A5760(void);
void renderizar_pantalla_jugador_uno_1j(void);
void renderizar_vertical_pantalla_jugador_uno_2j(void);
void renderizar_vertical_pantalla_jugador_dos_2j(void);
void renderizar_horizontal_pantalla_jugador_uno_2j(void);
void renderizar_horizontal_pantalla_jugador_dos_2j(void);
void renderizar_pantalla_jugador_uno_3j_4j(void);
void renderizar_pantalla_jugador_dos_3j_4j(void);
void renderizar_pantalla_jugador_tres_3j_4j(void);
void renderizar_pantalla_jugador_cuatro_3j_4j(void);
void funcion_802A74BC(void);
void copiar_framebuffer(s32, s32, s32, s32, u16*, u16*);
void funcion_802A7728(void);
void funcion_802A7940(void);

extern Vp dato_802B8880[];

#endif
