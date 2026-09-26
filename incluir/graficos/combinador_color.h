#ifndef GRAFICOS_COMBINADOR_COLOR_H
#define GRAFICOS_COMBINADOR_COLOR_H

#include <PR/ultratypes.h>

/* Valor simbolico de un canal: m*TEXEL + a. */
typedef struct {
    float m, a;
} Simbolo;

/* Selectores de G_SETCOMBINE ya separados por ciclo. */
typedef struct {
    int rgb_a[2], rgb_b[2], rgb_c[2], rgb_d[2];
    int a_a[2], a_b[2], a_c[2], a_d[2];
    int dos_ciclo;
} Combinador;

/* Colores constantes que puede leer el combinador. */
typedef struct {
    u8 prim[4], amb[4];
    u8 prim_lod_frac;
} ColoresCombinador;

void combinador_decodificar(Combinador *cc, u32 combinar0, u32 combinar1, u32 om_h);

int combinador_lee_rgb_texel(const Combinador *cc);
int combinador_lee_alfa_texel(const Combinador *cc);

/* Evalua el combinador para un color de vertice (shade */
void combinador_combinar(const Combinador *cc, const ColoresCombinador *col, const u8 sombreado[4], Simbolo salida[4]);

int combinador_texel_afecta_rgb(const Combinador *cc, const ColoresCombinador *col);

#endif
