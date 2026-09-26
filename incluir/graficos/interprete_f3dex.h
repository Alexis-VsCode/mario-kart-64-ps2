#ifndef GRAFICOS_INTERPRETE_F3DEX_H
#define GRAFICOS_INTERPRETE_F3DEX_H

#include <ultra64.h>

void inicializar_renderizador(void);
void ejecutar_tarea_graficos(Gfx *dl);
#ifdef SMK64_DEV
void pedir_volcado_display_list(void);
#endif

/* 60 FPS por frame intermedio (ver interprete_f3dex.c) */
void alternar_interp_gfx_ps2(void);
int ps2_gfx_interp_activado(void);

/* Pantalla de fallo */
int ps2_gfx_cuelgue_info(char *salida, int size);

void alimentar_perro_guardian(void);
int pantalla_en_negro(void);

#endif
