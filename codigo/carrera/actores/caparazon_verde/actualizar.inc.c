#include <carrera/actores.h>
#include <sistema/bucle_principal.h>
#include <carrera/preparacion_carrera.h>
#include <juego/definiciones.h>
#include "carrera/colision.h"

void actualizar_actor_caparazon_verde(struct ActorCaparazon* caparazon) {
    Jugador* jugador;
    SIN_USO f32 relleno9;
    SIN_USO f32 relleno_a;
    Vec3f algun_pos_2;
    Vec3f algun_vel_pos;
    f32 variable_f2;
    struct Mando* mando;
    TriplePadreCaparazon* padre;
    f32 altura;
    f32 z;
    SIN_USO f32 relleno2;
    SIN_USO f32 relleno3;
    SIN_USO f32 relleno4;
    SIN_USO f32 relleno5;
    f32 y;
    SIN_USO f32 relleno7;
    SIN_USO f32 relleno8;

    altura = caparazon->pos[0];
    y = caparazon->pos[1];
    z = caparazon->pos[2];
    if ((z < min_z_circuito) || (max_z_circuito < z) || (altura < min_x_circuito) || (max_x_circuito < altura) ||
        (y < min_y_circuito)) {
        destruir_actor_destructible((struct Actor*) caparazon);
    }
    caparazon->velocidad_rot += GRADOS(10);
    switch (caparazon->state) {
        case CAPARAZON_MANTENIDO:
            jugador = &jugadores[caparazon->id_jugador];
            copiar_colision(&jugador->colision, &caparazon->desconocido30);
            algun_vel_pos[0] = 0.0f;
            algun_vel_pos[1] = jugador->tamanio_caja_envolvente;
            algun_vel_pos[2] = -(jugador->tamanio_caja_envolvente + caparazon->tamanio_caja_envolvente + 2.0f);
            transformar_mat3_vec3f_mtxf(algun_vel_pos, jugador->matriz_orientacion);
            caparazon->pos[0] = jugador->pos[0] + algun_vel_pos[0];
            relleno2 = jugador->pos[1] - algun_vel_pos[1];
            caparazon->pos[2] = jugador->pos[2] + algun_vel_pos[2];
            altura = calcular_altura_superficie(caparazon->pos[0], relleno2, caparazon->pos[2], jugador->colision.indice_zx_malla);
            z = relleno2 - altura;
            if ((z < 5.0f) && (z > -5.0f)) {
                caparazon->pos[1] = caparazon->tamanio_caja_envolvente + altura;
            } else {
                caparazon->pos[1] = relleno2;
            }
            if ((jugador->type & HUMANO_JUGADOR) != 0) {
                mando = &mandos[caparazon->id_jugador];
                if ((mando->boton_apretado & Z_TRIG) != 0) {
                    mando->boton_apretado &= ~Z_TRIG;
                    if (mando->palanca_y_crudo < -0x2D) {
                        variable_f2 = 8.0f;
                        if (jugador->speed > 8.0f) {
                            variable_f2 = jugador->speed * 1.2f;
                        }
                        algun_vel_pos[0] = 0.0f;
                        algun_vel_pos[1] = 0.0f;
                        algun_vel_pos[2] = -variable_f2;
                        vec3f_rotar_eje_y(algun_vel_pos, jugador->rotacion[1] + jugador->desconocido_0C0);
                        caparazon->velocidad[0] = algun_vel_pos[0];
                        caparazon->velocidad[1] = algun_vel_pos[1];
                        caparazon->velocidad[2] = algun_vel_pos[2];
                        caparazon->state = 2;
                        funcion_800C9060(caparazon->id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x04));
                        funcion_800C90F4(caparazon->id_jugador,
                                      (jugador->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x00));
                        agregar_caparazon_verde_en_lista_actor_vigente((struct Actor*) caparazon - lista_actor);
                        return;
                    } else {
                        caparazon->state = 1;
                        if (jugador->desconocido_0C0 > 0) {
                            caparazon->angulo_rot = GRADOS(170);
                        } else {
                            caparazon->angulo_rot = -GRADOS(170) - 1;
                        }
                    }
                }
            }
            break;
        case CAPARAZON_SOLTADO:
            jugador = &jugadores[caparazon->id_jugador];
            if (caparazon->angulo_rot > 0) {
                caparazon->angulo_rot -= GRADOS(20);
                if (caparazon->angulo_rot < 0) {
                    caparazon->state = 2;
                    caparazon->algun_temporizador = 0x001E;
                    funcion_800C9060(caparazon->id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x04));
                    funcion_800C90F4(caparazon->id_jugador,
                                  (jugador->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x00));
                    agregar_caparazon_verde_en_lista_actor_vigente((struct Actor*) caparazon - lista_actor);
                }
            } else {
                caparazon->angulo_rot += GRADOS(20);
                if (caparazon->angulo_rot > 0) {
                    caparazon->state = 2;
                    caparazon->algun_temporizador = 0x001E;
                    funcion_800C9060(caparazon->id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x04));
                    funcion_800C90F4(caparazon->id_jugador,
                                  (jugador->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x00));
                    agregar_caparazon_verde_en_lista_actor_vigente((struct Actor*) caparazon - lista_actor);
                }
            }
            if (caparazon->state == 2) {
                variable_f2 = 8.0f;
                if (jugador->speed > 8.0f) {
                    variable_f2 = jugador->speed * 1.2f;
                }
                algun_vel_pos[0] = 0.0f;
                algun_vel_pos[1] = 0.0f;
                algun_vel_pos[2] = variable_f2;
                vec3f_rotar_eje_y(algun_vel_pos, jugador->rotacion[1] + jugador->desconocido_0C0);
                caparazon->velocidad[0] = algun_vel_pos[0];
                caparazon->velocidad[1] = algun_vel_pos[1];
                caparazon->velocidad[2] = algun_vel_pos[2];
            } else {
                algun_vel_pos[0] = senos(caparazon->angulo_rot) * 6.0f;
                algun_vel_pos[1] = caparazon->tamanio_caja_envolvente - jugador->tamanio_caja_envolvente;
                algun_vel_pos[2] = coss(caparazon->angulo_rot) * 6.0f;
                transformar_mat3_vec3f_mtxf(algun_vel_pos, jugador->matriz_orientacion);
                caparazon->pos[0] = jugador->pos[0] + algun_vel_pos[0];
                caparazon->pos[1] = jugador->pos[1] + algun_vel_pos[1];
                caparazon->pos[2] = jugador->pos[2] + algun_vel_pos[2];
            }
            break;
        case CAPARAZON_MOVIENDO:
            if (caparazon->indice_padre > 0) {
                caparazon->indice_padre -= 1;
                if (caparazon->indice_padre == 0) {
                    caparazon->flags &= ~0x1000;
                }
            }
            caparazon->velocidad[1] -= 0.5f;
            if (caparazon->velocidad[1] < -2.0f) {
                caparazon->velocidad[1] = -2.0f;
            }
            algun_pos_2[0] = caparazon->pos[0];
            algun_pos_2[1] = caparazon->pos[1];
            algun_pos_2[2] = caparazon->pos[2];
            caparazon->pos[0] += caparazon->velocidad[0];
            caparazon->pos[1] += caparazon->velocidad[1];
            caparazon->pos[2] += caparazon->velocidad[2];
            colision_terreno_actor(&caparazon->desconocido30, 4.0f, caparazon->pos[0], caparazon->pos[1], caparazon->pos[2], algun_pos_2[0],
                                    algun_pos_2[1], algun_pos_2[2]);
            funcion_802B4E30((struct Actor*) caparazon);
            if ((caparazon->desconocido30.distancia_superficie[0] < 0.0f) || (caparazon->desconocido30.distancia_superficie[1] < 0.0f)) {
                colision_caparazon(&caparazon->desconocido30, caparazon->velocidad);
                funcion_800C98B8(caparazon->pos, caparazon->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x54));
                caparazon->flags |= 0x80;
            }
            break;
        case TRIPLE_CAPARAZON_VERDE:
            jugador = &jugadores[caparazon->id_jugador];
            padre = (TriplePadreCaparazon*) &lista_actor[caparazon->indice_padre];
            if (padre->type != TRIPLE_ACTOR_CAPARAZON_VERDE) {
                destruir_actor_destructible((struct Actor*) caparazon);
            } else {
                caparazon->angulo_rot += padre->velocidad_rot;
                algun_vel_pos[0] = senos(caparazon->angulo_rot) * 8.0f;
                algun_vel_pos[1] = caparazon->tamanio_caja_envolvente - jugador->tamanio_caja_envolvente;
                algun_vel_pos[2] = coss(caparazon->angulo_rot) * 8.0f;
                transformar_mat3_vec3f_mtxf(algun_vel_pos, jugador->matriz_orientacion);
                algun_pos_2[0] = caparazon->pos[0];
                algun_pos_2[1] = caparazon->pos[1];
                algun_pos_2[2] = caparazon->pos[2];
                caparazon->pos[0] = jugador->pos[0] + algun_vel_pos[0];
                caparazon->pos[1] = jugador->pos[1] + algun_vel_pos[1];
                caparazon->pos[2] = jugador->pos[2] + algun_vel_pos[2];
                colision_terreno_actor(&caparazon->desconocido30, 4.0f, caparazon->pos[0], caparazon->pos[1], caparazon->pos[2], algun_pos_2[0],
                                        algun_pos_2[1], algun_pos_2[2]);
                funcion_802B4E30((struct Actor*) caparazon);
            }
            break;
        case CAPARAZON_VERDE_CORREDOR_GOLPE_A:
            caparazon->velocidad[1] -= (0, 0.3f);
            if (caparazon->velocidad[1] < -5.0f) {
                caparazon->velocidad[1] = -5.0f;
            }
            caparazon->angulo_rot += GRADOS(8);
            caparazon->algun_temporizador -= 1;
            caparazon->pos[1] += caparazon->velocidad[1];
            if (caparazon->algun_temporizador == 0) {
                destruir_actor((struct Actor*) caparazon);
            }
            break;
        default:
            break;
    }
}
