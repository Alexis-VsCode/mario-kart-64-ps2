#include <ultra64.h>
#include <juego/macros.h>
#include <juego/definiciones.h>
#include <juego/camino.h>
#include <juego/pista.h>
#include "sistema/bucle_principal.h"
#include "carrera/ia_vehiculos_y_camara.h"

bool son_en_curva(SIN_USO s32 parametro0, u16 indice_punto_camino) {
    s16 cosa = actual_pista_consecutivo_curva_cantidades_camino[indice_punto_camino];
    if (cosa > 0) {
        return true;
    }
    return false;
}

bool es_lejos_desde_camino(s32 indice_jugador) {
    f32 value = factor_posicion_pista[indice_jugador];
    if ((1.1f <= value) || (value <= -1.1f)) {
        return true;
    }
    return false;
}

f32 calcular_factor_posicion_pista(f32 pos_x, f32 pos_z, u16 indice_punto_camino, s32 indice_camino) {
    f32 izquierda_x;
    f32 izquierda_z;
    f32 derecha_x;
    f32 derecha_z;
    f32 distancia_al_cuadrado_limite;
    f32 factor_posicion;
    PuntoCaminoPista* punto_camino_izquierda;
    PuntoCaminoPista* punto_camino_derecha;

    punto_camino_izquierda = &caminos_izquierda_pista[indice_camino][indice_punto_camino];
    punto_camino_derecha = &caminos_derecha_pista[indice_camino][indice_punto_camino];

    izquierda_x = punto_camino_izquierda->pos_x;
    izquierda_z = punto_camino_izquierda->pos_z;
    derecha_x = punto_camino_derecha->pos_x;
    derecha_z = punto_camino_derecha->pos_z;

    distancia_al_cuadrado_limite = ((derecha_x - izquierda_x) * (derecha_x - izquierda_x)) + ((derecha_z - izquierda_z) * (derecha_z - izquierda_z));

    if (distancia_al_cuadrado_limite < 0.01f) {
        return 0.0f;
    }
    factor_posicion =
        ((2.0f * ((derecha_x - izquierda_x) * (pos_x - izquierda_x) + (derecha_z - izquierda_z) * (pos_z - izquierda_z))) / distancia_al_cuadrado_limite) -
        1.0f;
    return factor_posicion;
}

void actualizar_factor_posicion_jugador(s32 id_jugador, u16 indice_punto_camino, s32 indice_camino) {
    SIN_USO Vec3f relleno;
    factor_posicion_pista[id_jugador] = 0.0f;
    if ((s32) obtener_circuito_ai_maximo_separacion >= 0) {
        if ((jugadores[id_jugador].type & EXISTE_JUGADOR) != 0) {
            factor_posicion_pista[id_jugador] = calcular_factor_posicion_pista(
                jugadores[id_jugador].pos[0], jugadores[id_jugador].pos[2], indice_punto_camino, indice_camino);
        }
    }
}

void calcular_posicion_desplazamiento_pista(u16 indice_punto_camino, f32 interpolar_factor, f32 distancia_desplazamiento, s16 indice_camino) {
    SIN_USO s32 relleno[4];
    f32 punto_uno_x_camino;
    f32 punto_uno_z_camino;
    f32 punto_dos_x_camino;
    f32 punto_dos_z_camino;
    SIN_USO s32 relleno2;
    f32 xdiff;
    f32 zdiff;
    f32 longitud_segmento;
    SIN_USO f32 temporal_f12;
    SIN_USO f32 temporal_f2_2;
    SIN_USO PuntoCaminoPista* path;
    PuntoCaminoPista* punto_dos_camino;
    PuntoCaminoPista* punto_uno_camino;

    punto_uno_camino = &caminos_pista[indice_camino][indice_punto_camino];
    punto_uno_x_camino = punto_uno_camino->pos_x;
    punto_uno_z_camino = punto_uno_camino->pos_z;
    punto_dos_camino = &caminos_pista[indice_camino][(indice_punto_camino + 1) % cantidad_camino_seleccionado];
    punto_dos_x_camino = punto_dos_camino->pos_x;
    punto_dos_z_camino = punto_dos_camino->pos_z;

    zdiff = punto_dos_z_camino - punto_uno_z_camino;
    xdiff = punto_dos_x_camino - punto_uno_x_camino;
    if (xdiff && xdiff) {}

    longitud_segmento = sqrtf((xdiff * xdiff) + (zdiff * zdiff));
    if (longitud_segmento < 0.01f) {
        posicion_desplazamiento[0] = punto_dos_x_camino;
        posicion_desplazamiento[2] = punto_dos_z_camino;
    } else {
        posicion_desplazamiento[0] =
            ((0.5f - (interpolar_factor * 0.5f)) * (((distancia_desplazamiento * zdiff) / longitud_segmento) + punto_uno_x_camino)) +
            ((1.0f - (0.5f - (interpolar_factor * 0.5f))) * (((distancia_desplazamiento * -zdiff) / longitud_segmento) + punto_uno_x_camino));
        posicion_desplazamiento[2] =
            ((0.5f - (interpolar_factor * 0.5f)) * (((distancia_desplazamiento * -xdiff) / longitud_segmento) + punto_uno_z_camino)) +
            ((1.0f - (0.5f - (interpolar_factor * 0.5f))) * (((distancia_desplazamiento * xdiff) / longitud_segmento) + punto_uno_z_camino));
    }
}

void fijar_posicion_desplazamiento_pista(u16 indice_punto_camino, f32 desplazamiento_pista, s16 indice_camino) {
    PuntoCaminoPista* camino1;
    PuntoCaminoPista* camino2;
    f32 x1;
    f32 z1;
    f32 x3;
    f32 z3;
    f32 x2;
    f32 z2;
    f32 x4;
    f32 z4;
    f32 temporal_f0;
    f32 temporal_f12;

    camino1 = &caminos_izquierda_pista[indice_camino][indice_punto_camino];
    camino2 = &caminos_derecha_pista[indice_camino][indice_punto_camino];

    x1 = (f32) camino1->pos_x;
    z1 = (f32) camino1->pos_z;

    x2 = (f32) camino2->pos_x;
    z2 = (f32) camino2->pos_z;

    indice_punto_camino += 1;
    indice_punto_camino = indice_punto_camino % cantidad_camino_por_indice_camino[indice_camino];

    camino1 = &caminos_izquierda_pista[indice_camino][indice_punto_camino];
    camino2 = &caminos_derecha_pista[indice_camino][indice_punto_camino];

    x3 = (f32) camino1->pos_x;
    z3 = (f32) camino1->pos_z;

    x4 = (f32) camino2->pos_x;
    z4 = (f32) camino2->pos_z;

    temporal_f0 = 0.5f - (desplazamiento_pista / 2.0f);
    temporal_f12 = 1.0f - temporal_f0;
    posicion_desplazamiento[0] = ((temporal_f0 * (x1 + x3)) / 2.0f) + ((temporal_f12 * (x2 + x4)) / 2.0f);
    posicion_desplazamiento[2] = ((temporal_f0 * (z1 + z3)) / 2.0f) + ((temporal_f12 * (z2 + z4)) / 2.0f);
}

s16 funcion_8000BD94(f32 pos_x, f32 pos_y, f32 pos_z, s32 indice_camino) {
    f32 x_dist;
    f32 y_dist;
    f32 z_dist;
    f32 considerar_distancia_al_cuadrado;
    f32 distancia_al_cuadrado_minimo;
    s32 considerar_indice_punto_camino;
    s32 camino_camino_punto_cantidad;
    s16 mas_cercano_camino_punto_indice;
    PuntoCaminoPista* puntos_camino_camino;
    PuntoCaminoPista* considerar_punto_camino;

    puntos_camino_camino = caminos_pista[indice_camino];
    camino_camino_punto_cantidad = cantidad_camino_por_indice_camino[indice_camino];
    considerar_punto_camino = &puntos_camino_camino[0];
    x_dist = (f32) considerar_punto_camino->pos_x - pos_x;
    y_dist = (f32) considerar_punto_camino->pos_y - pos_y;
    z_dist = (f32) considerar_punto_camino->pos_z - pos_z;
    distancia_al_cuadrado_minimo = (x_dist * x_dist) + (y_dist * y_dist) + (z_dist * z_dist);
    mas_cercano_camino_punto_indice = 0;
    for (considerar_indice_punto_camino = 1; considerar_indice_punto_camino < camino_camino_punto_cantidad;
         considerar_punto_camino++, considerar_indice_punto_camino++) {
        x_dist = (f32) considerar_punto_camino->pos_x - pos_x;
        y_dist = (f32) considerar_punto_camino->pos_y - pos_y;
        z_dist = (f32) considerar_punto_camino->pos_z - pos_z;
        considerar_distancia_al_cuadrado = (x_dist * x_dist) + (y_dist * y_dist) + (z_dist * z_dist);
        if (considerar_distancia_al_cuadrado < distancia_al_cuadrado_minimo) {
            mas_cercano_camino_punto_indice = considerar_indice_punto_camino;
            distancia_al_cuadrado_minimo = considerar_distancia_al_cuadrado;
        }
    }
    return mas_cercano_camino_punto_indice;
}

s16 buscar_mas_cercano_camino_punto_pista_seccion(f32 pos_x, f32 pos_y, f32 pos_z, u16 id_seccion_pista, s32* indice_camino) {
    PuntoCaminoPista* puntos_camino_camino;
    PuntoCaminoPista* considerar_punto_camino;
    f32 x_dist;
    f32 y_dist;
    f32 z_dist;
    f32 considerar_distancia_al_cuadrado;
    f32 distancia_al_cuadrado_minimo;
    s32 considerar_indice_punto_camino;
    s32 camino_camino_punto_cantidad;
    s32 temporal_t0;
    s32 variable_a1;
    s32 variable_t1;
    s32 considerar_indice_camino;
    s32 variable_t4;
    s16 mas_cercano_camino_punto_indice;

    distancia_al_cuadrado_minimo = 1000000.0f;
    temporal_t0 = *indice_camino;
    mas_cercano_camino_punto_indice = 0;
    variable_t1 = 0;
    variable_a1 = 0;
    puntos_camino_camino = caminos_pista[temporal_t0];
    camino_camino_punto_cantidad = cantidad_camino_por_indice_camino[temporal_t0];
    considerar_punto_camino = &puntos_camino_camino[0];
    for (considerar_indice_punto_camino = 0; considerar_indice_punto_camino < camino_camino_punto_cantidad;
         considerar_indice_punto_camino++, considerar_punto_camino++) {
        if ((considerar_punto_camino->id_seccion_pista == id_seccion_pista) || (id_circuito_actual == CEREMONIA_PREMIO_CIRCUITO)) {
            variable_t1 = 1;
            x_dist = (f32) considerar_punto_camino->pos_x - pos_x;
            y_dist = (f32) considerar_punto_camino->pos_y - pos_y;
            z_dist = (f32) considerar_punto_camino->pos_z - pos_z;
            considerar_distancia_al_cuadrado = (x_dist * x_dist) + (y_dist * y_dist) + (z_dist * z_dist);
            if (considerar_distancia_al_cuadrado < distancia_al_cuadrado_minimo) {
                mas_cercano_camino_punto_indice = considerar_indice_punto_camino;
                variable_a1 = 1;
                distancia_al_cuadrado_minimo = considerar_distancia_al_cuadrado;
            }
        }
    }
    if (variable_t1 == 0) {
        for (considerar_indice_camino = 0; considerar_indice_camino < 4; considerar_indice_camino++) {
            if ((considerar_indice_camino != temporal_t0) && (camino_tamanio[considerar_indice_camino] >= 2)) {
                puntos_camino_camino = caminos_pista[considerar_indice_camino];
                considerar_punto_camino = &puntos_camino_camino[0];
                camino_camino_punto_cantidad = cantidad_camino_por_indice_camino[considerar_indice_camino];
                for (considerar_indice_punto_camino = 0; considerar_indice_punto_camino < camino_camino_punto_cantidad;
                     considerar_indice_punto_camino++, considerar_punto_camino++) {
                    if (considerar_punto_camino->id_seccion_pista == id_seccion_pista) {
                        x_dist = (f32) considerar_punto_camino->pos_x - pos_x;
                        y_dist = (f32) considerar_punto_camino->pos_y - pos_y;
                        z_dist = (f32) considerar_punto_camino->pos_z - pos_z;
                        considerar_distancia_al_cuadrado = (x_dist * x_dist) + (y_dist * y_dist) + (z_dist * z_dist);
                        if (considerar_distancia_al_cuadrado < distancia_al_cuadrado_minimo) {
                            mas_cercano_camino_punto_indice = considerar_indice_punto_camino;
                            variable_t4 = considerar_indice_camino;
                            variable_a1 = 2;
                            distancia_al_cuadrado_minimo = considerar_distancia_al_cuadrado;
                        }
                    }
                }
            }
        }
    }
    if (variable_a1 == 0) {
        puntos_camino_camino = caminos_pista[0];
        camino_camino_punto_cantidad = cantidad_camino_por_indice_camino[0];
        considerar_punto_camino = &puntos_camino_camino[0];
        x_dist = (f32) considerar_punto_camino->pos_x - pos_x;
        y_dist = (f32) considerar_punto_camino->pos_y - pos_y;
        z_dist = (f32) considerar_punto_camino->pos_z - pos_z;
        distancia_al_cuadrado_minimo = (x_dist * x_dist) + (y_dist * y_dist) + (z_dist * z_dist);
        mas_cercano_camino_punto_indice = 0;
        for (considerar_indice_punto_camino = 1; considerar_indice_punto_camino < camino_camino_punto_cantidad;
             considerar_punto_camino++, considerar_indice_punto_camino++) {
            x_dist = (f32) considerar_punto_camino->pos_x - pos_x;
            y_dist = (f32) considerar_punto_camino->pos_y - pos_y;
            z_dist = (f32) considerar_punto_camino->pos_z - pos_z;
            considerar_distancia_al_cuadrado = (x_dist * x_dist) + (y_dist * y_dist) + (z_dist * z_dist);
            if (considerar_distancia_al_cuadrado < distancia_al_cuadrado_minimo) {
                mas_cercano_camino_punto_indice = considerar_indice_punto_camino;
                variable_t4 = 0;
                variable_a1 = 2;
                distancia_al_cuadrado_minimo = considerar_distancia_al_cuadrado;
            }
        }
    }
    if (variable_a1 == 2) {
        *indice_camino = variable_t4;
    }
    return mas_cercano_camino_punto_indice;
}

s16 actualizar_indice_camino_con_pista(f32 pos_x, f32 pos_y, f32 pos_z, s16 indice_punto_camino, s32 indice_camino, u16 id_seccion_pista) {
    s16 mas_cercano_camino_punto_indice;
    s16 buscar_indice;
    s16 considerar_indice;
    s32 camino_camino_punto_cantidad;
    f32 x_dist;
    f32 y_dist;
    f32 z_dist;
    f32 distancia_minimo;
    f32 distancia_al_cuadrado;
    PuntoCaminoPista* puntos_camino_camino;
    PuntoCaminoPista* considerar_punto_camino;

    mas_cercano_camino_punto_indice = -1;
    distancia_minimo = 500.0f * 500.0f;
    camino_camino_punto_cantidad = cantidad_camino_por_indice_camino[indice_camino];
    puntos_camino_camino = caminos_pista[indice_camino];
    for (buscar_indice = indice_punto_camino - 3; buscar_indice < indice_punto_camino + 7; buscar_indice++) {
        considerar_indice = (buscar_indice + camino_camino_punto_cantidad) % camino_camino_punto_cantidad;
        considerar_punto_camino = &puntos_camino_camino[considerar_indice];
        if (considerar_punto_camino->id_seccion_pista == id_seccion_pista) {
            x_dist = considerar_punto_camino->pos_x - pos_x;
            y_dist = considerar_punto_camino->pos_y - pos_y;
            z_dist = considerar_punto_camino->pos_z - pos_z;
            distancia_al_cuadrado = (x_dist * x_dist) + (y_dist * y_dist) + (z_dist * z_dist);
            if (distancia_al_cuadrado < distancia_minimo) {
                distancia_minimo = distancia_al_cuadrado;
                mas_cercano_camino_punto_indice = considerar_indice;
            }
        }
    }
    return mas_cercano_camino_punto_indice;
}

s16 actualizar_indice_camino(f32 pos_x, f32 pos_y, f32 pos_z, s16 indice_punto_camino, s32 indice_camino) {
    s16 mas_cercano_camino_punto_indice;
    s16 buscar_indice;
    s16 considerar_indice;
    bool encontrado_punto_camino;
    s32 camino_camino_punto_cantidad;
    f32 x_dist;
    f32 y_dist;
    f32 z_dist;
    f32 distancia_minimo;
    f32 distancia_al_cuadrado;
    PuntoCaminoPista* puntos_camino_camino;
    PuntoCaminoPista* considerar_punto_camino;

    encontrado_punto_camino = false;
    mas_cercano_camino_punto_indice = -1;
    distancia_minimo = 400.0f * 400.0f;
    camino_camino_punto_cantidad = cantidad_camino_por_indice_camino[indice_camino];
    puntos_camino_camino = caminos_pista[indice_camino];
    for (buscar_indice = indice_punto_camino - 3; buscar_indice < indice_punto_camino + 7; buscar_indice++) {
        considerar_indice = (buscar_indice + camino_camino_punto_cantidad) % camino_camino_punto_cantidad;
        considerar_punto_camino = &puntos_camino_camino[considerar_indice];
        x_dist = considerar_punto_camino->pos_x - pos_x;
        y_dist = considerar_punto_camino->pos_y - pos_y;
        z_dist = considerar_punto_camino->pos_z - pos_z;
        distancia_al_cuadrado = (x_dist * x_dist) + (y_dist * y_dist) + (z_dist * z_dist);
        if (distancia_al_cuadrado < distancia_minimo) {
            distancia_minimo = distancia_al_cuadrado;
            mas_cercano_camino_punto_indice = considerar_indice;
            encontrado_punto_camino = true;
        }
    }
    if (encontrado_punto_camino == false) {
        for (buscar_indice = indice_punto_camino - 3; buscar_indice < indice_punto_camino + 7; buscar_indice++) {
            considerar_indice = ((buscar_indice + camino_camino_punto_cantidad) % camino_camino_punto_cantidad);
            considerar_punto_camino = &puntos_camino_camino[considerar_indice];
            if (considerar_punto_camino && considerar_punto_camino) {};
        }
    }
    return mas_cercano_camino_punto_indice;
}

void ajustar_indice_camino_wario_stadium(SIN_USO f32 pos_x, f32 pos_y, SIN_USO f32 pos_z, s16* indice_punto_camino, SIN_USO s32 parametro4) {
    s16 variable_v0;

    variable_v0 = *indice_punto_camino;
    if ((id_circuito_actual == CIRCUITO_WARIO_STADIUM) && (variable_v0 >= 0x475) && (variable_v0 < 0x480) && (pos_y < 0.0f)) {
        variable_v0 = 0x0398;
    }
    *indice_punto_camino = variable_v0;
}

void empezar_linea_camino_ajustar_en(SIN_USO f32 pos_x, SIN_USO f32 pos_y, f32 pos_z, s16* indice_punto_camino, s32 indice_camino) {
    s16 punto_camino;
    punto_camino = *indice_punto_camino;
    if (punto_camino == 0) {
        if (inicio_z_camino < pos_z) {
            punto_camino = cantidad_camino_por_indice_camino[indice_camino] - 1;
        }
    } else if (((punto_camino + 1) == cantidad_camino_por_indice_camino[indice_camino]) && (pos_z <= inicio_z_camino)) {
        punto_camino = 0;
    }
    *indice_punto_camino = punto_camino;
}

s16 actualizar_camino_indice_pista_seccion(f32 pos_x, f32 pos_y, f32 pos_z, Jugador* jugador, s32 id_jugador, s32* indice_camino) {
    u16 id_seccion_pista;
    s16 devuelto;

    id_seccion_pista = obtener_id_seccion_pista(jugador->colision.indice_zx_malla);
    if ((id_seccion_pista <= 0) || (id_seccion_pista >= 0x33)) {
        id_seccion_pista = jugadores_pista_seccion_id[id_jugador];
    }
    jugadores_pista_seccion_id[id_jugador] = id_seccion_pista;
    devuelto = buscar_mas_cercano_camino_punto_pista_seccion(pos_x, pos_y, pos_z, id_seccion_pista, indice_camino);
    indice_camino_por_id_jugador[id_jugador] = *indice_camino;
    return devuelto;
}

s16 actualizar_camino_jugador(f32 pos_x, f32 pos_y, f32 pos_z, s16 indice_punto_camino, Jugador* jugador, s32 id_jugador, s32 indice_camino) {
    s16 punto_camino_nuevo;
    SIN_USO s16 margen_pila_0;
    SIN_USO s32 margen_pila_1;
    SIN_USO s32 margen_pila_2;
    PuntoCaminoPista* temporal_v1;

    if ((jugador->type & HUMANO_JUGADOR) && !(jugador->type & CPU_JUGADOR)) {
        punto_camino_nuevo = actualizar_indice_camino_con_pista(pos_x, pos_y, pos_z, indice_punto_camino, indice_camino,
                                                    (u16) obtener_id_seccion_pista(jugador->colision.indice_zx_malla));
        if (punto_camino_nuevo == -1) {
            punto_camino_nuevo = actualizar_camino_indice_pista_seccion(pos_x, pos_y, pos_z, jugador, id_jugador, &indice_camino);
        }
    } else {
        if (dato_801631E0[id_jugador] == true) {
            if (jugador->lakitu_props & LAKITU_RECUPERACION) {
                temporal_v1 = &caminos_pista[indice_camino][indice_punto_camino];
                jugador->pos[0] = (f32) temporal_v1->pos_x;
                jugador->pos[1] = (f32) temporal_v1->pos_y;
                jugador->pos[2] = (f32) temporal_v1->pos_z;
                jugador->lakitu_props &= ~LAKITU_RECUPERACION;
                return indice_punto_camino;
            }
            if (id_jugador == ((s32) dato_80163488 % 8)) {
                comprobar_colision_envolvente(&jugador->colision, 10.0f, pos_x, pos_y, pos_z);
                jugadores_pista_seccion_id[id_jugador] = obtener_id_seccion_pista(jugador->colision.indice_zx_malla);
                punto_camino_nuevo = actualizar_indice_camino_con_pista(pos_x, pos_y, pos_z, indice_punto_camino, indice_camino,
                                                            jugadores_pista_seccion_id[id_jugador]);
                if (punto_camino_nuevo == -1) {
                    punto_camino_nuevo = actualizar_indice_camino(pos_x, pos_y, pos_z, indice_punto_camino, indice_camino);
                }
                if (punto_camino_nuevo == -1) {
                    punto_camino_nuevo = buscar_mas_cercano_camino_punto_pista_seccion(pos_x, pos_y, pos_z,
                                                                         jugadores_pista_seccion_id[id_jugador], &indice_camino);
                    temporal_v1 = &caminos_pista[indice_camino][punto_camino_nuevo];
                    jugador->pos[0] = (f32) temporal_v1->pos_x;
                    jugador->pos[1] = (f32) temporal_v1->pos_y;
                    jugador->pos[2] = (f32) temporal_v1->pos_z;
                }
            } else {
                punto_camino_nuevo = actualizar_indice_camino(pos_x, pos_y, pos_z, indice_punto_camino, indice_camino);
                if (punto_camino_nuevo == -1) {
                    punto_camino_nuevo = funcion_8000BD94(pos_x, pos_y, pos_z, indice_camino);
                    temporal_v1 = &caminos_pista[indice_camino][punto_camino_nuevo];
                    pos_x = (f32) temporal_v1->pos_x;
                    pos_y = (f32) temporal_v1->pos_y;
                    pos_z = (f32) temporal_v1->pos_z;
                    jugador->pos[0] = pos_x;
                    jugador->pos[1] = pos_y;
                    jugador->pos[2] = pos_z;
                    comprobar_colision_envolvente(&jugador->colision, 10.0f, pos_x, pos_y, pos_z);
                    jugadores_pista_seccion_id[id_jugador] = obtener_id_seccion_pista(jugador->colision.indice_zx_malla);
                }
            }
        } else {
            punto_camino_nuevo = actualizar_indice_camino(pos_x, pos_y, pos_z, indice_punto_camino, indice_camino);
            if (punto_camino_nuevo == -1) {
                punto_camino_nuevo = actualizar_camino_indice_pista_seccion(pos_x, pos_y, pos_z, jugador, id_jugador, &indice_camino);
            }
        }
        ajustar_indice_camino_wario_stadium(pos_x, pos_y, pos_z, &punto_camino_nuevo, indice_camino);
    }
    empezar_linea_camino_ajustar_en(pos_x, pos_y, pos_z, &punto_camino_nuevo, indice_camino);
    return punto_camino_nuevo;
}

s16 buscar_mas_cercano_vehiculos_camino_punto(f32 x_pos, SIN_USO f32 y_pos, f32 z_pos, s16 indice_punto_camino) {
    f32 xdiff;
    f32 zdiff;
    f32 distancia_minimo;
    f32 considerar_distancia_al_cuadrado;
    s16 indice_real;
    s16 indice_minimo;
    s16 considerar_indice;
    Camino2D* considerar_punto_camino;

    distancia_minimo = 250000.0f;
    indice_minimo = -1;
    for (indice_real = indice_punto_camino - 2; indice_real < indice_punto_camino + 7; indice_real++) {
        considerar_indice = indice_real;
        if (indice_real < 0) {
            considerar_indice = indice_real + longitud_camino_vehiculo_2d;
        }
        considerar_indice %= longitud_camino_vehiculo_2d;
        considerar_punto_camino = &punto_camino_vehiculo_2d[considerar_indice];
        xdiff = considerar_punto_camino->x - x_pos;
        zdiff = considerar_punto_camino->z - z_pos;
        considerar_distancia_al_cuadrado = (xdiff * xdiff) + (zdiff * zdiff);
        if (considerar_distancia_al_cuadrado < distancia_minimo) {
            distancia_minimo = considerar_distancia_al_cuadrado;
            indice_minimo = considerar_indice;
        }
    }
    if (indice_minimo == -1) {
        indice_minimo = indice_punto_camino;
    }
    return indice_minimo;
}

s16 funcion_8000D24C(f32 pos_x, f32 pos_y, f32 pos_z, s32* indice_camino) {
    SIN_USO s32 relleno;
    Colision sp24;

    comprobar_colision_envolvente(&sp24, 10.0f, pos_x, pos_y, pos_z);
    return buscar_mas_cercano_camino_punto_pista_seccion(pos_x, pos_y, pos_z, obtener_id_seccion_pista(sp24.indice_zx_malla), indice_camino);
}

s16 funcion_8000D2B4(f32 pos_x, f32 pos_y, f32 pos_z, s16 indice_punto_camino, s32 indice_camino) {
    s16 punto_camino;

    punto_camino = actualizar_indice_camino(pos_x, pos_y, pos_z, indice_punto_camino, indice_camino);
    if (punto_camino == -1) {
        punto_camino = funcion_8000D24C(pos_x, pos_y, pos_z, &indice_camino);
    }
    empezar_linea_camino_ajustar_en(pos_x, pos_y, pos_z, &punto_camino, indice_camino);
    return punto_camino;
}

s16 funcion_8000D33C(f32 pos_x, f32 pos_y, f32 pos_z, s16 indice_punto_camino, s32 indice_camino) {
    s16 punto_camino;

    punto_camino = actualizar_indice_camino(pos_x, pos_y, pos_z, indice_punto_camino, indice_camino);
    if (punto_camino == -1) {
        punto_camino = funcion_8000D24C(pos_x, pos_y, pos_z, &indice_camino);
    }
    return punto_camino;
}

f32 cpu_pista_posicion_factor(s32 id_jugador) {
    PistaPosicionFactorInstruccion* temporal_v0;
    f32 objetivo;
    f32 actual_;

    temporal_v0 = &jugador_pista_posicion_factor_instruccion[id_jugador];
    actual_ = temporal_v0->current;
    objetivo = temporal_v0->target;
    if (actual_ < objetivo) {
        actual_ += temporal_v0->paso;
        if (objetivo < actual_) {
            actual_ = objetivo;
        }
    } else if (objetivo < actual_) {
        actual_ -= temporal_v0->paso;
        if (actual_ < objetivo) {
            actual_ = objetivo;
        }
    }
    temporal_v0->current = actual_;
    return actual_;
}

void determinar_ideal_cpu_posicion_desplazamiento(s32 id_jugador, u16 punto_camino) {
    SIN_USO s32 margen_pila_0;
    f32 sp48;
    f32 sp44;
    SIN_USO s32 margen_pila_1;
    SIN_USO s32 margen_pila_2;
    SIN_USO s32 margen_pila_3;
    f32 margen_pila_4;
    f32 margen_pila_5;
    f32 sp2_c;
    s32 mirar_distancia_adelante;
    s16 cantidad_curva;
    u16 cosa;

    cantidad_curva = actual_pista_consecutivo_curva_cantidades_camino[punto_camino];
    mirar_distancia_adelante = 6;
    sp2_c = cpu_pista_posicion_factor(id_jugador);
    cosa = punto_camino;

    switch (id_circuito_actual) {
        case CEREMONIA_PREMIO_CIRCUITO:
            mirar_distancia_adelante = 1;
            break;
        case CIRCUITO_TOADS_TURNPIKE:
            mirar_distancia_adelante = 7;
            break;
        case CIRCUITO_YOSHI_VALLEY:
            break;
        default:
            if (cantidad_curva < 6) {
                mirar_distancia_adelante = 8;
            } else if (cantidad_curva >= 0x15) {
                mirar_distancia_adelante = 20;
            }
            break;
    }

    if (mirar_distancia_adelante >= 8) {
        if ((factor_posicion_pista[id_jugador] > 0.75f) && (actual_pista_seccion_tipos_camino[cosa] == CURVA_INCLINADO_DERECHA)) {
            mirar_distancia_adelante = 7;
        }
        if ((factor_posicion_pista[id_jugador] < -0.75f) && (actual_pista_seccion_tipos_camino[cosa] == CURVA_INCLINADO_IZQUIERDA)) {
            mirar_distancia_adelante = 7;
        }
    }
    if (es_lejos_desde_camino(id_jugador) == true) {
        mirar_distancia_adelante = 5;
    }
    if (actual_jugador_mirada_adelante[id_jugador] < mirar_distancia_adelante) {
        actual_jugador_mirada_adelante[id_jugador]++;
    }
    if (mirar_distancia_adelante < actual_jugador_mirada_adelante[id_jugador]) {
        actual_jugador_mirada_adelante[id_jugador]--;
    }
    punto_camino = (actual_jugador_mirada_adelante[id_jugador] + punto_camino) % cantidad_camino_seleccionado;
    fijar_posicion_desplazamiento_pista(punto_camino, sp2_c, indice_camino_jugador);
    sp48 = posicion_desplazamiento[0];
    sp44 = posicion_desplazamiento[2];
    fijar_posicion_desplazamiento_pista(((punto_camino + 1) % cantidad_camino_seleccionado) & 0xFFFF, sp2_c, indice_camino_jugador);
    margen_pila_5 = posicion_desplazamiento[0];
    posicion_desplazamiento[0] = (sp48 + margen_pila_5) * 0.5f;
    margen_pila_4 = posicion_desplazamiento[2];
    posicion_desplazamiento[2] = (sp44 + margen_pila_4) * 0.5f;
}

s16 funcion_8000D6D0(Vec3f posicion, s16* indice_punto_camino, f32 rapidez, f32 parametro3, s16 indice_camino, s16 parametro5) {
    f32 temporal1;
    f32 temporal2;
    f32 medio_x;
    SIN_USO s16 margen_pila_1;
    s16 punto_camino_1;
    s16 punto_camino_2;
    f32 relleno3;
    f32 medio_y;
    f32 relleno4;
    f32 medio_z;
    f32 distancia;
    f32 pos_x_viejo;
    f32 pos_y_viejo;
    f32 pos_z_viejo;
    f32 variable_f2;
    f32 variable_f12;
    f32 variable_f14;
    s16 temporal_v0;
    s32 temporal_v1;
    f32 xdiff;
    f32 ydiff;
    f32 zdiff;
    Vec3f pos_viejo;
    PuntoCaminoPista* path;

    path = caminos_pista[indice_camino];
    pos_viejo[0] = posicion[0];
    pos_viejo[1] = posicion[1];
    pos_viejo[2] = posicion[2];
    pos_x_viejo = posicion[0];
    pos_y_viejo = posicion[1];
    pos_z_viejo = posicion[2];
    temporal_v0 = funcion_8000D2B4(pos_x_viejo, pos_y_viejo, pos_z_viejo, *indice_punto_camino, (s32) indice_camino);
    *indice_punto_camino = temporal_v0;
    temporal_v1 = temporal_v0 + parametro5;
    punto_camino_1 = temporal_v1 % cantidad_camino_por_indice_camino[indice_camino];
    punto_camino_2 = (temporal_v1 + 1) % cantidad_camino_por_indice_camino[indice_camino];
    fijar_posicion_desplazamiento_pista(punto_camino_1, parametro3, indice_camino);
    relleno3 = posicion_desplazamiento[0];
    relleno4 = posicion_desplazamiento[2];
    fijar_posicion_desplazamiento_pista(punto_camino_2, parametro3, indice_camino);
    temporal1 = posicion_desplazamiento[0];
    temporal2 = posicion_desplazamiento[2];
    medio_y = (path[punto_camino_1].pos_y + path[punto_camino_2].pos_y) * 0.5f;
    medio_x = (relleno3 + temporal1) * 0.5f;
    medio_z = (relleno4 + temporal2) * 0.5f;
    xdiff = medio_x - pos_x_viejo;
    ydiff = medio_y - pos_y_viejo;
    zdiff = medio_z - pos_z_viejo;
    distancia = sqrtf((xdiff * xdiff) + (ydiff * ydiff) + (zdiff * zdiff));
    if (distancia > 0.01f) {
        variable_f2 = ((xdiff * rapidez) / distancia) + pos_x_viejo;
        variable_f12 = ((ydiff * rapidez) / distancia) + pos_y_viejo;
        variable_f14 = ((zdiff * rapidez) / distancia) + pos_z_viejo;
    } else {
        variable_f2 = pos_x_viejo;
        variable_f12 = pos_y_viejo;
        variable_f14 = pos_z_viejo;
    }
    posicion[0] = variable_f2;
    posicion[1] = variable_f12;
    posicion[2] = variable_f14;
    return obtener_angulo_entre_camino(pos_viejo, posicion);
}

s16 funcion_8000D940(Vec3f pos, s16* indice_punto_camino, f32 rapidez, f32 parametro3, s16 indice_camino) {
    SIN_USO f32 relleno;
    f32 cosa1;
    f32 cosa2;
    SIN_USO s16 margen_pila_1;
    s16 punto_camino_1;
    s16 punto_camino_2;
    SIN_USO s16 margen_pila_2;
    f32 relleno2;
    f32 medio_x;
    f32 relleno3;
    f32 medio_y;
    f32 medio_z;
    f32 distancia;
    f32 temporal_f20;
    f32 temporal_f22;
    f32 temporal_f24;
    f32 variable_f2;
    f32 variable_f12;
    f32 variable_f14;
    s16 temporal_v0;
    f32 xdiff;
    f32 ydiff;
    f32 zdiff;
    s32 cantidad_punto_camino;
    Vec3f sp54;

    sp54[0] = pos[0];
    sp54[1] = pos[1];
    sp54[2] = pos[2];
    cantidad_punto_camino = cantidad_camino_por_indice_camino[indice_camino];
    temporal_f20 = pos[0];
    temporal_f22 = pos[1];
    temporal_f24 = pos[2];
    temporal_v0 = funcion_8000D2B4(temporal_f20, temporal_f22, temporal_f24, *indice_punto_camino, (s32) indice_camino);
    *indice_punto_camino = temporal_v0;
    punto_camino_1 = ((temporal_v0 + cantidad_punto_camino) - 3) % cantidad_punto_camino;
    punto_camino_2 = ((temporal_v0 + cantidad_punto_camino) - 4) % cantidad_punto_camino;
    fijar_posicion_desplazamiento_pista(punto_camino_1, parametro3, indice_camino);
    relleno2 = posicion_desplazamiento[0];
    relleno3 = posicion_desplazamiento[2];
    fijar_posicion_desplazamiento_pista(punto_camino_2, parametro3, indice_camino);
    cosa1 = posicion_desplazamiento[0];
    cosa2 = posicion_desplazamiento[2];
    medio_y = (caminos_pista[indice_camino][punto_camino_1].pos_y + caminos_pista[indice_camino][punto_camino_2].pos_y) * 0.5f;
    medio_x = (relleno2 + cosa1) * 0.5f;
    medio_z = (relleno3 + cosa2) * 0.5f;
    xdiff = medio_x - temporal_f20;
    ydiff = medio_y - temporal_f22;
    zdiff = medio_z - temporal_f24;
    distancia = sqrtf((xdiff * xdiff) + (ydiff * ydiff) + (zdiff * zdiff));
    if (distancia > 0.01f) {
        variable_f2 = ((xdiff * rapidez) / distancia) + temporal_f20;
        variable_f12 = ((ydiff * rapidez) / distancia) + temporal_f22;
        variable_f14 = ((zdiff * rapidez) / distancia) + temporal_f24;
    } else {
        variable_f2 = temporal_f20;
        variable_f12 = temporal_f22;
        variable_f14 = temporal_f24;
    }
    pos[0] = variable_f2;
    pos[1] = variable_f12;
    pos[2] = variable_f14;
    return obtener_angulo_entre_camino(sp54, pos);
}

s16 actualizar_camino_siguiente_vehiculo(Vec3f pos, s16* indice_punto_camino, f32 rapidez) {
    f32 orig_x_pos;
    f32 orig_y_pos;
    f32 orig_z_pos;
    SIN_USO s32 margen_pila_0;
    SIN_USO s32 margen_pila_1;
    SIN_USO s32 margen_pila_2;
    SIN_USO s32 margen_pila_3;
    SIN_USO s32 margen_pila_4;
    SIN_USO s32 margen_pila_5;
    SIN_USO s32 margen_pila_6;
    SIN_USO s32 margen_pila_7;
    SIN_USO s32 margen_pila_8;
    f32 lejos_camino_punto_promedio_x;
    f32 lejos_camino_punto_promedio_z;
    f32 x_dist;
    f32 y_dist;
    f32 distancia;
    f32 nuevo_x;
    f32 nuevo_z;
    s16 nuevo_camino_punto_indice;
    s16 punto_camino_lejos_1;
    s16 punto_camino_lejos_2;
    Camino2D* temporal_a0;
    Camino2D* temporal_a2;
    Vec3f sp38;

    orig_x_pos = pos[0];
    orig_y_pos = pos[1];
    orig_z_pos = pos[2];
    sp38[0] = pos[0];
    sp38[1] = pos[1];
    sp38[2] = pos[2];
    nuevo_camino_punto_indice = buscar_mas_cercano_vehiculos_camino_punto(orig_x_pos, orig_y_pos, orig_z_pos, *indice_punto_camino);
    *indice_punto_camino = nuevo_camino_punto_indice;
    punto_camino_lejos_1 = (nuevo_camino_punto_indice + 3) % longitud_camino_vehiculo_2d;
    punto_camino_lejos_2 = (nuevo_camino_punto_indice + 4) % longitud_camino_vehiculo_2d;
    temporal_a0 = &punto_camino_vehiculo_2d[punto_camino_lejos_1];
    temporal_a2 = &punto_camino_vehiculo_2d[punto_camino_lejos_2];
    lejos_camino_punto_promedio_x = (temporal_a0->x + temporal_a2->x) * 0.5f;
    lejos_camino_punto_promedio_z = (temporal_a0->z + temporal_a2->z) * 0.5f;
    x_dist = lejos_camino_punto_promedio_x - orig_x_pos;
    y_dist = lejos_camino_punto_promedio_z - orig_z_pos;
    distancia = sqrtf((x_dist * x_dist) + (y_dist * y_dist));
    if (distancia > 0.01f) {
        nuevo_x = ((x_dist * rapidez) / distancia) + orig_x_pos;
        nuevo_z = ((y_dist * rapidez) / distancia) + orig_z_pos;
    } else {
        nuevo_x = orig_x_pos;
        nuevo_z = orig_z_pos;
    }
    pos[0] = nuevo_x;
    pos[1] = orig_y_pos;
    pos[2] = nuevo_z;
    return obtener_angulo_entre_camino(sp38, pos);
}
