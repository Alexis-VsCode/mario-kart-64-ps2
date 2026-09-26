#ifndef SISTEMA_MATEMATICAS_2_H
#define SISTEMA_MATEMATICAS_2_H

#include <juego/estructuras_comunes.h>
#include "carrera/camara.h"

void operador_o(s32*, s32);
void operador_y_no(s32*, s32);
void xor_operador(s32*, s32);
SIN_USO bool funcion_80040E84(s32*, s32);
s32 funcion_80040EA4(s32*, s32);
s32 arriba_paso_f32_hacia_alternativo(f32*, f32, f32*);
s32 abajo_paso_f32_hacia_alternativo(f32*, f32, f32*);
s32 arriba_paso_s32_hacia_alternativo(s32*, s32, s32*);
s32 abajo_paso_s32_hacia_alternativo(s32*, s32, s32*);
s32 arriba_paso_s16_hacia_alternativo(s16*, s16, s16*);
s32 abajo_paso_s16_hacia_alternativo(s16*, s16, s16*);
s32 paso_s32_hacia(s32*, s32, s32);
s32 es_dentro_distancia_2d(f32, f32, f32, f32, f32);
s32 funcion_80041680(f32, f32);
s32 funcion_800416AC(f32, f32);
void funcion_80041F54(s32, s32);
void funcion_80042000(u16);
void funcion_800420A8(f32);
void funcion_8004214C(u16, f32);
void funcion_800421FC(s32, s32, f32);
void funcion_800423F0(Mat4, u16, u16, u16);
void funcion_8004252C(Mat4, u16, u16);
void mtxf_multiplicar_primer_columna(Mat4, f32);
void mtxf_multiplicar_segundo_columna(Mat4, f32);
void mtxf_multiplicar_tercer_columna(Mat4, f32);
void rotar_vec3f(Vec3f, Vec3f, Vec3s);
void fijar_matriz_dif_traslacion_escala_rsp(Vec3f, Vec3f, f32);

void copiar_vec3f(Vec3f, Vec3f);
s32 arriba_paso_f32_hacia(f32*, f32, f32);
s32 abajo_paso_f32_hacia(f32*, f32, f32);
s32 arriba_paso_s32_hacia(s32*, s32, s32);
s32 abajo_paso_s32_hacia(s32*, s32, s32);
s32 arriba_paso_s16_hacia(s16*, s16, s16);
s32 arriba_paso_u16_hacia(u16*, u16, u16);
s32 abajo_paso_s16_hacia(s16*, s16, s16);
s32 abajo_paso_u16_hacia(u16*, s32, s32);
s32 paso_s16_hacia(s16*, s16, s16);
s32 paso_f32_hacia(f32*, f32, f32);
void funcion_80041480(s16*, s16, s16, s16*);
Vec3f* fijar_xyz_vec3f(Vec3f, f32, f32, f32);
Vec3f* normalizar_vec3f(Vec3f dest);
Vec3f* producto_cruce_vec3f(Vec3f, Vec3f, Vec3f);
s32 funcion_80041658(f32, f32);
f32 funcion_800416D8(f32, f32, u16);
f32 funcion_80041724(f32, f32, u16);
s32 obtener_angulo_entre_xy(f32, f32, f32, f32);
u16 funcion_800417B4(u16, u16);
s32 funcion_800418AC(f32, f32, Vec3f);
s32 funcion_800418E8(f32, f32, Vec3f);
s32 funcion_80041924(Colision*, Vec3f);
bool es_particula_en_pantalla(Vec3f, Camara*, u16);
void funcion_800419F8(void);
void traslacion_x_y_mtfx(Mat4, s32, s32);
void rotar_z_mtxf_u16(Mat4, u16);
void escalar_x_y_mtxf(Mat4, f32);
void rotar_escala_x_y_z_mtxf(Mat4, u16, f32);
void rotar_escala_x_y_z_traslacion_x_y_mtxf(Mat4, s32, s32, u16, f32);
void funcion_80041D24(void);
void funcion_80041D34(void);
void fijar_pantalla_hud_matriz(void);
void funcion_80042330(s32, s32, u16, f32);
void fijar_transformacion_matriz_mtxf(Mat4, Vec3f, Vec3su, f32);
void fijar_trasl_escala_matriz_mtxf(Mat4, Vec3f, Vec3f, f32);
void mtxf_conjunto_matriz_g_objeto_lista(s32, Mat4);
void transformar_matriz_conjunto(Mat4, Vec3f, Vec3f, u16, f32);
void rotar_x_y_vec3f(Vec3f, Vec3f, Vec3s);
void fijar_transformacion_matriz_rsp(Vec3f, Vec3su, f32);
void fijar_matriz_transformacion_invertido_x_y_orientacion_rsp(Vec3f, Vec3su, f32);
void fijar_matriz_trasl_rot_escala_rsp(Vec3f, Vec3f, f32);
void rsp_conjunto_matriz_g_objeto_lista(s32);

extern s8 dato_801658FE;

#endif
