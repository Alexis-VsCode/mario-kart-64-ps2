#ifndef CARRERA_ANIMACION_H
#define CARRERA_ANIMACION_H

#include <juego/estructuras_comunes.h>

#define INSTRUCCION_ANIMACION_SIMPLE(x) x, 0x00000002

#define ANIMACION_DESACTIVAR_AUTOMATICO_SACAR INSTRUCCION_ANIMACION_SIMPLE(DESACTIVAR_AUTOMATICO_SACAR_MATRIZ)
#define MATRIZ_SACAR_ANIMACION INSTRUCCION_ANIMACION_SIMPLE(MATRIZ_SACAR)
#define PARADA_ANIMACION INSTRUCCION_ANIMACION_SIMPLE(ANIMACION_PARADA)
#define MODELO_RENDER_ANIMACION_EN(modelo, x, y, z) MODELO_RENDER_O_POS_AGREGAR, 0x00000007, 0x00000000, (u32) modelo, x, y, z
#define MODELO_RENDER_ANIMACION(modelo) MODELO_RENDER_ANIMACION_EN(modelo, 0x00000000, 0x00000000, 0x00000000)
#define POS_AGREGAR_ANIMACION(x, y, z) MODELO_RENDER_ANIMACION_EN((u32) NULL, x, y, z)

enum tipo_animacion { MODELO_RENDER_O_POS_AGREGAR, DESACTIVAR_AUTOMATICO_SACAR_MATRIZ, MATRIZ_SACAR, ANIMACION_PARADA };

typedef struct {
     s32 type;
     s32 size;
     s32 siempre_cero_nunca_usado;
     Gfx* model;
     s32 pos[3];
} Armadura;

typedef struct {
     u16 longitud_animacion;
     u16 ciclo_indice;
} EspecCicloAnimacion;

typedef EspecCicloAnimacion VectorMiembroAnimacion[3];

typedef struct {
     s32 conjunto_siempre_a_algo_pero_nunca_usado;
     s32 siempre_cero_nunca_usado;
     s16 longitud_animacion;
     u16 valor_tiene_pero_nunca_usado;
     s16* arreglo_angulo;
     VectorMiembroAnimacion* animacion_ciclo_espec_vector;
} Animacion;

void convertir_a_fijo_punto_matriz_animacion(Mtx* dest, Mat4 orig_);
void trasladar_rotacion2_mtxf(Mat4 dest, Vec3f pos, Vec3s angulo);
s16 obtener_longitud_animacion(Animacion**, s16);
void agregar_mtx_miembro_render_o(Armadura*, s16*, VectorMiembroAnimacion, s32);
void renderizar_armadura(Armadura*, Animacion*, s16);
s16 renderizar_modelo_animado(Armadura*, Animacion**, s16, s16);

#endif
