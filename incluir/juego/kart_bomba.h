#ifndef JUEGO_KART_BOMBA_H
#define JUEGO_KART_BOMBA_H

#include <juego/estructuras_comunes.h>
#include <juego/mk64.h>
#include <juego/pista.h>

#define NUM_KARTS_BOMBA_MAX 7
#define NUM_KARTS_BOMBA_VERSUS 7
#define NUM_KARTS_BOMBA_BATALLA 4

#define INACTIVO_ESTADO_BOMBA 0
#define CCW_ESTADO_BOMBA 1
#define CW_ESTADO_BOMBA 2
#define QUIETO_ESTADO_BOMBA 3
#define BOMBA_ESTADO_EXPLOTADO 4
#define DESCONOCIDO_ESTADO_BOMBA 5

typedef struct {
     u16 indice_punto_camino;
     u16 estado_inicial;
     f32 desconocido_04;
     f32 pos_inicial_x;
     f32 pos_inicial_z;
     f32 desconocido_10;
     f32 desconocido_14;
} KartBombaAparicion;

typedef struct {
     Vec3f pos_bomba;
     Vec3f pos_rueda_1;
     Vec3f pos_rueda_2;
     Vec3f pos_rueda_3;
     Vec3f pos_rueda_4;
     f32 desconocido_3C;
     u16 algun_rot;
     u16 indice_punto_camino;
     u16 state;
     u16 temporizador_rebote; // timer? state? height?
     u16 temporizador_circulo;
     u16 desconocido_4A;
     s16 desconocido_4C;
     f32 y_pos;
} KartBomba;

extern s32 objeto_indice_kart_bomba[NUM_KARTS_BOMBA_MAX];

extern KartBomba karts_bomba[NUM_KARTS_BOMBA_MAX];
extern Colision dato_80164038[NUM_KARTS_BOMBA_MAX];

extern KartBombaAparicion kart_bomba_apariciones[CIRCUITOS_NUM][NUM_KARTS_BOMBA_MAX];

#endif
