#include <ultra64.h>
#include <juego/macros.h>
#include <juego/mk64.h>
#include "memoria/buffers.h"

ALIGNED8 union_d_802BFB80 dato_802BFB80;
ALIGNED8 struct_d_802DFB80 textura_kart_codificado[2][2][8];
#ifdef AVOID_UB
ALIGNED8 struct_d_802F1F80 lista_paletas_jugador[2][4][8];
#else
ALIGNED8 u16 lista_paletas_jugador[2][4][0x100 * 8];
#endif

ALIGNED8 u16 g_zbuffer[ANCHO_PANTALLA * ALTURA_PANTALLA];

#ifdef AVOID_UB
ALIGNED8 u16 g_framebuffers[3][ANCHO_PANTALLA * ALTURA_PANTALLA];
#else
u16 framebuffer_0[ANCHO_PANTALLA * ALTURA_PANTALLA];
u16 framebuffer_1[ANCHO_PANTALLA * ALTURA_PANTALLA];
u16 framebuffer_2[ANCHO_PANTALLA * ALTURA_PANTALLA];
#endif
