#ifndef RECURSOS_PISTAS_RAINBOW_ROAD_DATOS_PISTA_H
#define RECURSOS_PISTAS_RAINBOW_ROAD_DATOS_PISTA_H

#include <ultra64.h>
#include <PR/gbi.h>
#include <juego/tipos_actores.h>
#include <juego/camino.h>
#include <juego/pista.h>
#include "carrera/animacion.h"

extern Gfx d_circuito_rainbow_road_dl_0[];
extern Gfx d_circuito_rainbow_road_dl_80[];
extern Gfx d_circuito_rainbow_ruta_dl_D8[];
extern Gfx d_circuito_rainbow_road_dl_178[];
extern Gfx d_circuito_rainbow_road_dl_210[];
extern Gfx d_circuito_rainbow_road_dl_288[];
extern Gfx d_circuito_rainbow_road_dl_338[];
extern Gfx d_circuito_rainbow_ruta_dl_3D0[];
extern Gfx d_circuito_rainbow_ruta_dl_4A0[];
extern Gfx d_circuito_rainbow_road_dl_528[];
extern Gfx d_circuito_rainbow_ruta_dl_5F8[];
extern Gfx d_circuito_rainbow_road_dl_658[];
extern Gfx d_circuito_rainbow_ruta_dl_6E0[];
extern Gfx d_circuito_rainbow_road_dl_730[];
extern Gfx d_circuito_rainbow_ruta_dl_7A8[];
extern Gfx d_circuito_rainbow_ruta_dl_7F8[];
extern Gfx d_circuito_rainbow_road_dl_880[];
extern Gfx d_circuito_rainbow_ruta_dl_8E0[];
extern Gfx d_circuito_rainbow_road_dl_958[];
extern Gfx d_circuito_rainbow_ruta_dl_9C8[];
extern Gfx d_circuito_rainbow_ruta_dl_A70[];
extern Gfx d_circuito_rainbow_ruta_dl_B08[];
extern Gfx d_circuito_rainbow_ruta_dl_B70[];
extern Gfx d_circuito_rainbow_ruta_dl_BF0[];
extern Gfx d_circuito_rainbow_ruta_dl_C70[];
extern Gfx d_circuito_rainbow_ruta_dl_D10[];
extern Gfx d_circuito_rainbow_ruta_dl_D80[];
extern Gfx d_circuito_rainbow_ruta_dl_E08[];
extern Gfx d_circuito_rainbow_ruta_dl_E98[];
extern Gfx d_circuito_rainbow_ruta_dl_F50[];
extern Gfx d_circuito_rainbow_ruta_dl_FB0[];
extern Gfx d_circuito_rainbow_road_dl_1030[];
extern Gfx d_circuito_rainbow_ruta_dl_10A8[];
extern Gfx d_circuito_rainbow_road_dl_1150[];
extern Gfx d_circuito_rainbow_road_dl_1198[];
extern Gfx d_circuito_rainbow_road_dl_1228[];
extern Gfx d_circuito_rainbow_ruta_dl_12A0[];
extern Gfx d_circuito_rainbow_road_dl_1340[];
extern Gfx d_circuito_rainbow_ruta_dl_13F0[];
extern Gfx d_circuito_rainbow_road_dl_1488[];
extern Gfx d_circuito_rainbow_ruta_dl_14E8[];
extern Gfx d_circuito_rainbow_road_dl_1530[];
extern Gfx d_circuito_rainbow_ruta_dl_15D0[];
extern Gfx d_circuito_rainbow_road_dl_1678[];
extern Gfx d_circuito_rainbow_ruta_dl_16C0[];
extern Gfx d_circuito_rainbow_road_dl_1738[];
extern Gfx d_circuito_rainbow_ruta_dl_17D0[];
extern Gfx d_circuito_rainbow_road_dl_1878[];
extern Gfx d_circuito_rainbow_ruta_dl_18D0[];
extern Gfx d_circuito_rainbow_road_dl_1948[];
extern PuntoCaminoPista d_circuito_rainbow_road_camino_desconocido[];
extern PuntoCaminoPista d_circuito_rainbow_road_camino_pista[];
extern u8 d_circuito_rainbow_road_neon_hongo_tlut_lista[][512];
extern u8 d_circuito_rainbow_road_neon_mario_lista_tlut[][512];
extern u8 d_circuito_rainbow_road_neon_boo_lista_tlut[][512];
extern u16 d_circuito_rainbow_road_tluts_estatico[];
extern u8 d_circuito_rainbow_road_hongo_neon[];
extern u8 d_circuito_rainbow_road_neon_mario[];
extern u8 d_circuito_rainbow_road_neon_boo[];
extern u8 d_circuito_rainbow_road_texturas_estatico[][4096];
extern u64 d_circuito_rainbow_road_doble_desconocido;
extern u64 d_circuito_rainbow_road_doble2_desconocido;
extern Lights1 d_circuito_rainbow_road_luz1;
extern u8 d_circuito_rainbow_road_esfera[];
extern u8 d_circuito_rainbow_road_mapa_reflejo_metal[];
extern u8 d_circuito_rainbow_road_mapa_reflejo_oro[];
extern u8 d_circuito_rainbow_road_chain_chomp_lengua[];
extern u8 d_circuito_rainbow_road_chain_chomp_ojo[];
extern Vtx d_circuito_rainbow_road_chomp_modelo_mandibula_inferior[];
extern Gfx d_circuito_rainbow_ruta_dl_151A8[];
extern Vtx d_circuito_rainbow_road_chomp_modelo1_inferior_cuerpo[];
extern Vtx d_circuito_rainbow_road_chomp_modelo2_inferior_cuerpo[];
extern Vtx d_circuito_rainbow_road_chomp_modelo3_inferior_cuerpo[];
extern Gfx d_circuito_rainbow_road_dl_15550[];
extern Vtx d_circuito_rainbow_road_chomp_modelo_mandibula_superior[];
extern Gfx d_circuito_rainbow_ruta_dl_158C0[];
extern Vtx d_circuito_rainbow_road_chomp_cuerpo_superior_atras_modelo1[];
extern Vtx d_circuito_rainbow_road_chomp_cuerpo_superior_atras_modelo2[];
extern Vtx d_circuito_rainbow_road_chomp_cuerpo_superior_atras_modelo3[];
extern Gfx d_circuito_rainbow_ruta_dl_15C68[];
extern Vtx d_circuito_rainbow_road_chomp_modelo_ojos[];
extern Gfx d_circuito_rainbow_ruta_dl_15F18[];
extern s16 d_rainbow_road_chomp_angulo[];
extern VectorMiembroAnimacion d_rainbow_road_chomp_matriz_animacion[];
extern Animacion d_rainbow_road_desconocido2;
extern Animacion* d_rainbow_road_desconocido3[];
extern u32 d_rainbow_road_desconocido4[];
extern u32 d_rainbow_road_desconocido5[];
extern Gfx d_circuito_rainbow_road_dl_16220[];
extern struct DatosAparicionActor d_circuito_rainbow_road_caja_item_apariciones[];
extern SeccionesPista d_circuito_rainbow_road_direccion[];
extern Gfx* d_circuito_rainbow_road_lista_dl[];

#endif
