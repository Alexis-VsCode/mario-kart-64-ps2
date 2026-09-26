#ifndef CARRERA_COLISION_H
#define CARRERA_COLISION_H

#include <juego/estructuras_comunes.h>

#define COLISION 0x1
#define SIN_COLISION 0x0

void anular_displaylist(uintptr_t);
void funcion_802AAAAC(Colision*);
f32 funcion_802AAB4C(Jugador*);
s32 comprobar_colision_zx(Colision*, f32, f32, f32, f32, u16);
s32 comprobar_colision_yx(Colision*, f32, f32, f32, f32, u16);
s32 comprobar_colision_zy(Colision*, f32, f32, f32, f32, u16);
s8 obtener_tipo_superficie(u16);
s16 obtener_id_seccion_pista(u16);
s16 funcion_802ABD7C(u16);
s16 funcion_802ABDB8(u16);
s16 funcion_802ABDF4(u16);
f32 calcular_altura_superficie(f32, f32, f32, u16);
f32 funcion_802ABEAC(Colision*, Vec3f);
void colision_caparazon(Colision*, Vec3f);
void procesar_colision_caparazon(Vec3f, f32, Vec3f, f32);
u16 colision_terreno_jugador(Jugador*, RuedaKart*, f32, f32, f32);
void ajustar_ortogonalmente_pos(Vec3f, f32, Vec3f, f32);
s32 detectar_colision_rueda(RuedaKart*);
u16 colision_terreno_actor(Colision*, f32, f32, f32, f32, f32, f32, f32);
u16 comprobar_colision_envolvente(Colision*, f32, f32, f32, f32);
f32 obtener_altura_superficie(f32, f32, f32);
void fijar_buffer_vtx(uintptr_t, u32, u32);
s32 es_rectangulo_intersecando_linea(s16, s16, s16, s16, s16, s16, s16, s16);
s32 es_triangulo_intersecando_envolvente_caja(s16, s16, s16, s16, u16);
void generar_cuadricula_colision(void);
void generar_malla_colision_con_predeterminados(Gfx*);
void generar_malla_colision_con_id_seccion_predeterminado(Gfx*, s8);
void generar_malla_colision(Gfx*, s8, u16);
void fijar_tamanio_tile_buscar_y(uintptr_t, s32, s32);
void fijar_colores_vertice(uintptr_t, u32, s32, s8, u8, u8, u8);
void fijar_colores_vtx_buscar_y(uintptr_t, s8, u8, u8, u8);
void restar_vector_escalado(Vec3f, f32, Vec3f);

#endif
