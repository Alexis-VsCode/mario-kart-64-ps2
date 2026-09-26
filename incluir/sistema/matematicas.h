#ifndef SISTEMA_MATEMATICAS_H
#define SISTEMA_MATEMATICAS_H

#include <PR/ultratypes.h>

#define cuad(x) ((x) * (x))

double fabs(double x);

void funcion_802B5794(Mat4, Vec3f, Vec3f);
s32 funcion_802B4F60(s32, Vec3f, s32, f32, f32);
s32 fijar_posicion_render(Mat4, s32);
f32 dist_al_cuadrado_con_error(Vec3f, Vec3f);
s32 obtener_angulo_xz_entre_puntos(Vec3f, Vec3f);
u32 funcion_802B5258(Vec3f, Vec3s);
void fijar_vec3f(Vec3f, f32, f32, f32);
void fijar_vec3s(Vec3s, s16, s16, s16);
void* copiar_retorno_vec3f(Vec3f, Vec3f);
void copiar_vec3s(Vec3s, Vec3s);
void* fijar_retorno_vec3f(Vec3f, f32, f32, f32);
void copiar_mtxf(Mat4, Mat4);
void copiar_elemento_n_mtxf(s32*, s32*, s32);
void identidad_mtxf(Mat4);
void trasladar_vec3f_mat4_agregar(Mat4, Mat4, Vec3f);
void trasladar_ligero_vec3f_mat4_agregar(Mat4, Mat4, Vec3f);
void trasladar_mtxf(Mat4, Vec3f);
void proyeccion_mtxf(Mat4, u16*, f32, f32, f32, f32, f32);
void mirada_mtxf(Mat4, Vec3f, Vec3f);
void rotar_x_mtxf(Mat4, s16);
void rotar_y_mtxf(Mat4, s16);
void rotar_z_mtxf_s16(Mat4, s16);
void funcion_802B5B14(Vec3f b, Vec3s rotar);
void funcion_802B5CAC(s16, s16, Vec3f);
void funcion_802B5D30(s16, s16, s32);
void fijar_iluminacion_circuito(Lights1*, s16, s16, s32);
void escalar_mtxf(Mat4, f32);
void rotar_traslacion_zxy_mtxf(Mat4, Vec3f, Vec3s);
void transformar_mat3_vec3f_mtxf(Vec3f, Mat3);
void transformar_mat4_vec3f_mtxf(Vec3f, Mat4);
void vec3f_rotar_eje_y(Vec3f, s16);
void calcular_matriz_orientacion(Mat3, f32, f32, f32, s16);
void calcular_matriz_rotacion(Mat3, s16, f32, f32, f32);
void funcion_802B6BC0(Mat4, s16, f32, f32, f32);
void funcion_802B6D58(Mat4, Vec3f, Vec3f);
void multiplicacion_mtxf(Mat4, Mat4, Mat4);
void mtxf_a_mtx(Mtx*, Mat4);
u16 busqueda_atan2(f32, f32);
u16 atan2s(f32, f32);
f32 atan2f(f32, f32);
s16 atan1s(f32);
s16 asin1s(f32);
f32 acos1f(f32);
u16 aleatorio_u16(void);
u16 int_aleatorio(u16);
s16 angulo_desde_coords(f32, f32, f32, f32);
void angulos_plano(Vec3f, Vec3f, Vec3s);
f32 senos(u16);
f32 coss(u16);
s32 es_entre_angulo(u16, u16, u16);
f32 distancia_si_visible(Vec3f, Vec3f, u16, f32, f32, f32);

extern s32 dato_802B91C0[];
extern Vec3f dato_802B91C8;

/* Definida en matematicas.c; faltaba su declaracion. */
void vec_unidad_z_rot_x_rot_y(s16 rot_y, s16 rot_x, Vec3f parametro2);

#endif
