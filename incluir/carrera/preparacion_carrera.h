#ifndef CARRERA_PREPARACION_CARRERA_H
#define CARRERA_PREPARACION_CARRERA_H

#include <juego/macros.h>
#include <ultra64.h>
#include <juego/tipos_actores.h>
#include "camara.h"

struct desconocido_struct_800DC5EC {
     struct Mando* mandos;
     Camara* camara;
     Jugador* jugador;
     s32* desconocido_c;
     Vp viewport;
     s32 pad[2];
     s16 altura_camara;
     s16 desconocido;
     s16 ancho_pantalla;
     s16 altura_pantalla;
     s16 inicio_x_pantalla;
     s16 inicio_y_pantalla;
     s16 desconocido_3c;
     s16 sentido_jugador;
     s16 contador_camino;
     s16 desconocido42;
     s32 pad2;
};

void funcion_800029B0(void);
void preparar_carrera(void);
void funcion_80002DAC(void);
void borrar_buffer_nmi(void);
void funcion_80003040(void);

extern s16 ahora_cargado_circuito_id;
extern u16 dato_800DC5A8;
extern s32 dato_800DC5AC;
extern u16 dato_800DC5B0;
extern u16 dato_800DC5B4;
extern u16 dato_800DC5B8;
extern u16 dato_800DC5BC;
extern u16 es_en_abandonar_a_transicion_menu;
extern u16 abandonar_a_contador_transicion_menu;
extern u16 dato_800DC5C8;
extern u16 dato_800DC5CC;
extern s32 dato_800DC5D0;
extern s32 dato_800DC5D4;
extern s32 dato_800DC5D8;
extern s32 dato_800DC5DC;
extern s32 dato_800DC5E0;
extern u16 dato_800DC5E4;
extern s32 indice_ganador_jugador;

extern struct desconocido_struct_800DC5EC dato_8015F480[4];
extern struct desconocido_struct_800DC5EC* dato_800DC5EC;
extern struct desconocido_struct_800DC5EC* dato_800DC5F0;
extern struct desconocido_struct_800DC5EC* dato_800DC5F4;
extern struct desconocido_struct_800DC5EC* dato_800DC5F8;
extern u16 juego_en_pausa;
extern u8* p_app_nmi_buffer;
extern s32 es_modo_espejo;
extern s16 id_circuito_creditos;
extern s16 cajas_item_lugar;

extern TrianguloColision* malla_colision;
extern u16* indices_colision;
extern u16 cantidad_malla_colision;
extern u16 triangulos_colision_num;
extern u32 dato_8015F58C;

extern Vec3f dato_8015F590;
extern s32 dato_8015F59C;
extern s32 dato_8015F5A0;
extern s32 dato_8015F5A4;

extern Vtx* vtx_buffer[];
extern s16 max_x_circuito;
extern s16 min_x_circuito;

extern s16 max_y_circuito;
extern s16 min_y_circuito;

extern s16 max_z_circuito;
extern s16 min_z_circuito;
extern s16 dato_8015F6F4;
extern s16 dato_8015F6F6;
extern u16 dato_8015F6F8;
extern s16 dato_8015F6FA;
extern s16 dato_8015F6FC;
extern u16 caparazones_aparecido_num;

extern u16 dato_8015F700;
extern u16 dato_8015F702;
extern f32 dato_8015F704;
extern Vec3f dato_8015F708;
extern SIN_USO u32 dato_8015F718[3];
extern size_t tamanio_memoria_libre;
extern uintptr_t siguiente_libre_memoria_direccion;
extern uintptr_t ptr_fin_monton;

extern u32 dato_8015F730;
extern uintptr_t libre_memoria_reinicio_ancla;
extern Vec3f dato_8015F738;
extern Vec3f dato_8015F748;
extern Vec3f dato_8015F758;
extern Vec3f dato_8015F768;
extern Vec3f dato_8015F778;

extern f32 sentido_circuito;
extern s32 dato_8015F788;

extern s32 dato_8015F790[];
extern u16 dato_8015F890;
extern u16 dato_8015F892;
extern u16 dato_8015F894;
extern f32 tiempo_jugador_ultimo_tocado_linea_meta[];

extern u8* nmi_g_versus_resultados_2_p;
extern u8* nmi_g_versus_resultados_3_p;
extern u8* nmi_g_versus_resultados_4_p;
extern u8* desconocido_nmi_4;
extern u8* desconocido_nmi_5;
extern u8* desconocido_nmi_6;

extern Vec3f dato_8015F8D0;
extern s32 dato_8015F8DC;

extern s32 dato_8015F8E0;
extern f32 dato_8015F8E4;
extern f32 dato_8015F8E8;
extern s16 lut_posicion_jugador[];
extern u16 actores_permanente_num;

extern SIN_USO u8 dato_80162578[];
extern s16 cantidad_camino_depuracion;
extern s16 es_mando_1_desconectado;
extern s32 dato_801625EC;
extern s32 dato_801625F0;
extern s32 dato_801625F4;
extern s32 dato_801625F8;
extern f32 dato_801625FC;

#endif
