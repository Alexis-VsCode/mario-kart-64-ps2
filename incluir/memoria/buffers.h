#ifndef MEMORIA_BUFFERS_H
#define MEMORIA_BUFFERS_H

#include <PR/ultratypes.h>
#include <juego/mk64.h>
#include <juego/estructuras_comunes.h>

typedef struct {
    u8 arreglo_indice_pixel[0x1000];
} struct_d_802BFB80_8;

typedef struct {
    u8 arreglo_indice_pixel[0x2000];
} struct_d_802BFB80_4;

typedef union {
    struct_d_802BFB80_4 tamanio_arreglo_4[2][2][4];
    struct_d_802BFB80_8 tamanio_arreglo_8[2][2][8];
} union_d_802BFB80;

typedef struct {
    char desconocido_00[0x920];
} struct_d_802DFB80;

typedef struct {
    u16 rojo : 5;
    u16 verde : 5;
    u16 azul : 5;
    u16 alpha : 1;
} RGBA5551;

typedef struct {
     RGBA5551 paleta_kart[0xC0];
     RGBA5551 paleta_rueda[0x40];
} struct_d_802F1F80;

extern u16 aleatorio_semilla_16;
extern u8 margen_semilla_aleatorio[216];
extern union_d_802BFB80 dato_802BFB80;
extern struct_d_802DFB80 textura_kart_codificado[][2][8];

#ifdef AVOID_UB
extern struct_d_802F1F80 lista_paletas_jugador[2][4][8];
#else
extern u16 lista_paletas_jugador[][4][0x100 * 8];
#endif
extern u16 g_zbuffer[ANCHO_PANTALLA * ALTURA_PANTALLA];

#ifdef AVOID_UB
extern u16 g_framebuffers[3][ANCHO_PANTALLA * ALTURA_PANTALLA];
#define framebuffer_0 g_framebuffers[0]
#define framebuffer_1 g_framebuffers[1]
#define framebuffer_2 g_framebuffers[2]
#else
extern u16 framebuffer_0[ANCHO_PANTALLA * ALTURA_PANTALLA];
extern u16 framebuffer_1[ANCHO_PANTALLA * ALTURA_PANTALLA];
extern u16 framebuffer_2[ANCHO_PANTALLA * ALTURA_PANTALLA];
#endif

#endif
