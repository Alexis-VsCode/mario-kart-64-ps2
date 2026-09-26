#ifndef JUEGO_CAMINO_H
#define JUEGO_CAMINO_H

#include <juego/estructuras_comunes.h>

typedef struct {
     s16 pos_x;
     s16 pos_y;
     s16 pos_z;
     u16 id_seccion_pista;
} PuntoCaminoPista;

enum {
    CURVA_INCLINADO_DERECHA = 0,
    CURVA_INCLINADO_IZQUIERDA = 1,
    CURVA_DERECHA = 2,
    CURVA_IZQUIERDA = 3,
    RECTO = 4
};

extern PuntoCaminoPista* caminos_pista[];
extern PuntoCaminoPista* caminos_izquierda_pista[];
extern PuntoCaminoPista* caminos_derecha_pista[];

extern s16* tipos_seccion_pista[];
extern s16* rotacion_esperado_camino[];
// No idea. Adjacency list?
extern s16* pista_consecutivo_curva_cantidades[];

extern s16 algun_punto_camino_mas_cercano;
extern s32 indice_camino_jugador;
extern PuntoCaminoPista* actual_pista_izquierda_camino;
extern PuntoCaminoPista* actual_pista_derecha_camino;
extern s16* actual_pista_seccion_tipos_camino;
extern s16* actual_camino_punto_esperado_rotacion_camino;
extern u16 cantidad_camino_seleccionado;
extern PuntoCaminoPista* camino_pista_actual;
extern s16* actual_pista_consecutivo_curva_cantidades_camino;

extern u16 punto_camino_mas_cercano_por_id_jugador[];
extern s32 num_camino_puntos_recorrido[];
extern u16 indice_camino_por_id_jugador[];
extern u16 cantidad_camino_por_indice_camino[];
extern s16 punto_camino_mas_cercano_por_id_camara[];

extern f32 factor_posicion_pista[];
extern u16 jugadores_pista_seccion_id[];
extern s32 camino_tamanio[];
extern f32 inicio_z_camino;
extern s16 cpu_entrando_camino_interseccion[];
extern s16 cpu_saliendo_camino_interseccion[];
extern s16 b_en_multi_seccion_camino[];

#endif
