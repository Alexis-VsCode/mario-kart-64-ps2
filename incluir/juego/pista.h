#ifndef JUEGO_PISTA_H
#define JUEGO_PISTA_H

#include <ultra64.h>
#include <PR/gbi.h>
#include <juego/macros.h>
#include "camino.h"

typedef struct {
    Gfx* addr;
    u8 tipo_superficie;
    u8 id_seccion;
    u16 flags;
} SeccionesPista;

struct _struct_g_circuito_camino_tamanios_0_x10 {
     u16 primer_camino;
     u16 segundo_camino;
     u16 tercer_camino;
     u16 cuarto_camino;
     u16 desconocido8;
     char relleno_a[6];
};

#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
typedef enum {
     CIRCUITO_MARIO_RACEWAY = 0,
     CIRCUITO_CHOCO_MOUNTAIN,
     CIRCUITO_BOWSER_CASTLE,
     CIRCUITO_BANSHEE_BOARDWALK,
     CIRCUITO_YOSHI_VALLEY,
     CIRCUITO_FRAPPE_SNOWLAND,
     CIRCUITO_KOOPA_BEACH,
     CIRCUITO_ROYAL_RACEWAY,
     CIRCUITO_LUIGI_RACEWAY,
     CIRCUITO_MOO_MOO_FARM,
     CIRCUITO_TOADS_TURNPIKE,
     CIRCUITO_KALAMARI_DESERT,
     CIRCUITO_SHERBET_LAND,
     CIRCUITO_RAINBOW_ROAD,
     CIRCUITO_WARIO_STADIUM,
     CIRCUITO_BLOCK_FORT,
     CIRCUITO_SKYSCRAPER,
     CIRCUITO_DOUBLE_DECK,
     CIRCUITO_DK_JUNGLE,
     CIRCUITO_BIG_DONUT,
     CEREMONIA_PREMIO_CIRCUITO,
     CIRCUITOS_NUM
} CIRCUITOS;

#else

#define CIRCUITO_MARIO_RACEWAY
#define CIRCUITO_CHOCO_MOUNTAIN
#define CIRCUITO_BOWSER_CASTLE
#define CIRCUITO_BANSHEE_BOARDWALK
#define CIRCUITO_YOSHI_VALLEY
#define CIRCUITO_FRAPPE_SNOWLAND
#define CIRCUITO_KOOPA_BEACH
#define CIRCUITO_ROYAL_RACEWAY
#define CIRCUITO_LUIGI_RACEWAY
#define CIRCUITO_MOO_MOO_FARM
#define CIRCUITO_TOADS_TURNPIKE
#define CIRCUITO_KALAMARI_DESERT
#define CIRCUITO_SHERBET_LAND
#define CIRCUITO_RAINBOW_ROAD
#define CIRCUITO_WARIO_STADIUM
#define CIRCUITO_BLOCK_FORT
#define CIRCUITO_SKYSCRAPER
#define CIRCUITO_DOUBLE_DECK
#define CIRCUITO_DK_JUNGLE
#define CIRCUITO_BIG_DONUT
#define CEREMONIA_PREMIO_CIRCUITO
#define CIRCUITOS_NUM

#endif

#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
extern s16 id_circuito_actual;
extern s16* dato_800DCBB4[];
#define CIRCUITO_OBTENER_800DCBB4(n) dato_800DCBB4[id_circuito_actual][n]
extern f32 cpu_circuito_maximo_separacion[];
#define obtener_circuito_ai_maximo_separacion cpu_circuito_maximo_separacion[id_circuito_actual]
extern struct _struct_g_circuito_camino_tamanios_0_x10 tamanios_camino_circuito[];
#define obtener_circuito_camino_tamanios tamanios_camino_circuito[id_circuito_actual]
extern s16 cpu_direccion_sensibilidad[];
#define obtener_circuito_ai_direccion_sensibilidad cpu_direccion_sensibilidad[id_circuito_actual]
extern f32 cpu_circuito_minimo_separacion[];
#define obtener_circuito_ai_minimo_separacion cpu_circuito_minimo_separacion[id_circuito_actual]
extern PuntoCaminoPista* tabla_camino_circuito[][4];
#define obtener_circuito_camino_tabla(p) segmentado_a_duplicado_virtual_2(tabla_camino_circuito[id_circuito_actual][p])
extern PuntoCaminoPista* tabla_camino_circuito_2[][4];
#define obtener_circuito_camino_tabla_2(p) segmentado_a_duplicado_virtual_2(tabla_camino_circuito_2[id_circuito_actual][p])
extern ComportamientoCPU* cpu_comportamiento_lut[];
#define obtener_circuito_ai_comportamiento segmentado_a_duplicado_virtual_2(cpu_comportamiento_lut[i])
extern char* nombres_circuito[];
#define obtener_circuito_nombre nombres_circuito[id_circuito_actual]
extern char* duplicar_nombres_circuito[];
#define obtener_circuito_nombre_duplicar duplicar_nombres_circuito[orden_circuito_copa[seleccion_copa][indice_circuito_en_copa]]
extern char* nombres_circuito_depuracion[];
#define obtener_circuito_depuracion_nombre nombres_circuito_depuracion[id_circuito_actual]
extern f32 persp_lejos_circuito;
#define persp_lejos_circuito persp_lejos_circuito
extern f32 circuito_cerca_persp;
#define circuito_cerca_persp circuito_cerca_persp
#define CIRCUITO_D_OBTENER_0D0096B8(cc) *(f32*) segmentado_a_duplicado_virtual_2(&dato_0D0096B8[id_circuito_actual][cc])
#define obtener_circuito_cpu_apagado_pista_objetivo_rapidez(cc) \
    *(f32*) segmentado_a_duplicado_virtual_2(&cpu_apagado_pista_objetivo_rapidez[id_circuito_actual][cc])
#define obtener_circuito_cpu_curva_objetivo_rapidez(cc) \
    *(f32*) segmentado_a_duplicado_virtual_2(&cpu_curva_objetivo_rapidez[id_circuito_actual][cc])
#define obtener_circuito_cpu_normal_objetivo_rapidez(cc) \
    *(f32*) segmentado_a_duplicado_virtual_2(&cpu_normal_objetivo_rapidez[id_circuito_actual][cc])
#else
#define id_circuito_actual
#define CIRCUITO_OBTENER_800DCBB4(n)
#define obtener_circuito_ai_maximo_separacion
#define obtener_circuito_camino_tamanios
#define obtener_circuito_ai_direccion_sensibilidad
#define obtener_circuito_ai_minimo_separacion
#define obtener_circuito_camino_tabla(p)
#define obtener_circuito_camino_tabla_2(p)
#define obtener_circuito_ai_comportamiento
#define obtener_circuito_nombre
#define obtener_circuito_nombre_duplicar
#define obtener_circuito_depuracion_nombre
#define persp_lejos_circuito
#define circuito_cerca_persp
#define CIRCUITO_D_OBTENER_0D0096B8(cc)
#define obtener_circuito_cpu_apagado_pista_objetivo_rapidez(cc)
#define obtener_circuito_cpu_curva_objetivo_rapidez(cc)
#define obtener_circuito_cpu_normal_objetivo_rapidez(cc)
#endif

#endif
