#include <carrera/actores.h>
#include <juego/camino.h>
#include <juego/definiciones.h>
#include <sistema/bucle_principal.h>
#include <carrera/actores_extendidos.h>
#include <carrera/preparacion_carrera.h>

void funcion_802B3B44(struct ActorCaparazon* caparazon) {
    u16 punto_camino_actual;
    u16 punto_camino_siguiente;
    f32 temporal_f0;
    f32 temporal_f0_2;
    f32 temporal_f0_3;
    f32 temporal_f12_3;
    f32 temporal_f14_2;
    f32 temporal_f16_2;
    f32 temporal_f2;
    f32 temporal_f12;
    f32 temporal_f28;
    f32 temporal_f20;
    f32 temporal_f22;
    f32 temporal_f24;
    f32 temporal_f12_0;
    f32 temporal_f12_1;
    f32 temporal_f12_2;
    f32 temporal_f18_3;
    f32 temporal_f16_3;
    f32 temporal_f26;
    Vec3f orig_pos;

    punto_camino_actual = caparazon->indice_camino;
    temporal_f2 = camino_pista_actual[punto_camino_actual].pos_x;
    temporal_f12 = camino_pista_actual[punto_camino_actual].pos_y;
    temporal_f28 = camino_pista_actual[punto_camino_actual].pos_z;
    punto_camino_siguiente = punto_camino_actual + 1;

    if (punto_camino_siguiente >= cantidad_camino_seleccionado) {
        punto_camino_siguiente -= cantidad_camino_seleccionado;
    }

    temporal_f20 = temporal_f2 - caparazon->pos[0];
    temporal_f22 = temporal_f12 - caparazon->pos[1];
    temporal_f24 = temporal_f28 - caparazon->pos[2];
    temporal_f0 = (temporal_f20 * temporal_f20) + (temporal_f22 * temporal_f22) + (temporal_f24 * temporal_f24);
    if (temporal_f0 > 400.0f) {
        temporal_f18_3 = camino_pista_actual[punto_camino_siguiente].pos_x;
        temporal_f16_3 = camino_pista_actual[punto_camino_siguiente].pos_y;
        temporal_f26 = camino_pista_actual[punto_camino_siguiente].pos_z;

        temporal_f12_0 = temporal_f18_3 - caparazon->pos[0];
        temporal_f12_1 = temporal_f16_3 - caparazon->pos[1];
        temporal_f12_2 = temporal_f26 - caparazon->pos[2];

        temporal_f0_3 = (temporal_f12_0 * temporal_f12_0) + (temporal_f12_1 * temporal_f12_1) + (temporal_f12_2 * temporal_f12_2);
        if (temporal_f0_3 < temporal_f0) {
            caparazon->indice_camino = punto_camino_siguiente;
        } else {
            temporal_f0_2 = sqrtf(temporal_f0) * 4.0f;
            temporal_f20 /= temporal_f0_2;
            temporal_f22 /= temporal_f0_2;
            temporal_f24 /= temporal_f0_2;

            temporal_f12_3 = caparazon->velocidad[0];
            temporal_f14_2 = caparazon->velocidad[1];
            temporal_f16_2 = caparazon->velocidad[2];

            temporal_f12_3 += temporal_f20;
            temporal_f14_2 += temporal_f22;
            temporal_f16_2 += temporal_f24;
            temporal_f0 = sqrtf((temporal_f12_3 * temporal_f12_3) + (temporal_f14_2 * temporal_f14_2) + (temporal_f16_2 * temporal_f16_2));
            if (temporal_f0 > 6.0f) {
                temporal_f0 /= 6.0f;
                temporal_f12_3 /= temporal_f0;
                temporal_f14_2 /= temporal_f0;
                temporal_f16_2 /= temporal_f0;
            }
            caparazon->velocidad[0] = temporal_f12_3;
            caparazon->velocidad[1] = temporal_f14_2;
            caparazon->velocidad[2] = temporal_f16_2;

            orig_pos[0] = caparazon->pos[0];
            orig_pos[1] = caparazon->pos[1];
            orig_pos[2] = caparazon->pos[2];

            caparazon->pos[0] += temporal_f12_3;
            caparazon->pos[1] += temporal_f14_2;
            caparazon->pos[2] += temporal_f16_2;
            colision_terreno_actor(&caparazon->desconocido30, 4.0f, caparazon->pos[0], caparazon->pos[1], caparazon->pos[2], orig_pos[0],
                                    orig_pos[1], orig_pos[2]);
            funcion_802B4E30((struct Actor*) caparazon);
        }
    } else {
        if (temporal_f0 > 5.0f) {
            caparazon->pos[0] = temporal_f2;
            caparazon->pos[1] = caparazon->tamanio_caja_envolvente + temporal_f12;
            caparazon->pos[2] = temporal_f28;
            caparazon->indice_camino = punto_camino_siguiente;
        } else {
            temporal_f18_3 = camino_pista_actual[punto_camino_siguiente].pos_x;
            temporal_f16_3 = camino_pista_actual[punto_camino_siguiente].pos_y;
            temporal_f26 = camino_pista_actual[punto_camino_siguiente].pos_z;

            caparazon->pos[0] = (temporal_f2 + temporal_f18_3) * 0.5f;
            caparazon->pos[1] = ((temporal_f12 + temporal_f16_3) * 0.5f) + caparazon->tamanio_caja_envolvente;
            caparazon->pos[2] = (temporal_f28 + temporal_f26) * 0.5f;

            caparazon->velocidad[0] = (temporal_f18_3 - temporal_f2) * 0.5f;
            caparazon->velocidad[1] = (temporal_f16_3 - temporal_f12) * 0.5f;
            caparazon->velocidad[2] = (temporal_f26 - temporal_f28) * 0.5f;
        }
    }
}

void funcion_802B3E7C(struct ActorCaparazon* caparazon, Jugador* jugador) {
    f32 velocidad_x;
    f32 velocidad_z;
    f32 xz_dist;
    Vec3f posicion_nuevo;

    velocidad_x = jugador->pos[0];
    velocidad_x -= caparazon->pos[0];
    velocidad_z = jugador->pos[2];
    velocidad_z -= caparazon->pos[2];
    xz_dist = sqrtf((velocidad_x * velocidad_x) + (velocidad_z * velocidad_z)) / 8;
    if (xz_dist == 0.0f) {
        velocidad_x = 0.0f;
        velocidad_z = 0.0f;
    } else {
        velocidad_x /= xz_dist;
        velocidad_z /= xz_dist;
    }

    posicion_nuevo[0] = caparazon->pos[0];
    posicion_nuevo[1] = caparazon->pos[1];
    posicion_nuevo[2] = caparazon->pos[2];
    caparazon->pos[0] += velocidad_x;
    caparazon->pos[1] -= 2.0f;
    caparazon->pos[2] += velocidad_z;
    caparazon->velocidad[0] = velocidad_x;
    caparazon->velocidad[1] = -2.0f;
    caparazon->velocidad[2] = velocidad_z;

    if (jugador->efectos & BOO_EFECTO) {
        destruir_actor_destructible((struct Actor*) caparazon);
    } else {
        colision_terreno_actor(&caparazon->desconocido30, 4.0f, caparazon->pos[0], caparazon->pos[1], caparazon->pos[2], posicion_nuevo[0],
                                posicion_nuevo[1], posicion_nuevo[2]);
        funcion_802B4E30((struct Actor*) caparazon);
        funcion_802B4104(caparazon);
    }
}

s16 funcion_802B3FD0(Jugador* duenio, struct ActorCaparazon* caparazon) {
    Jugador* jugador;
    s32 indice_jugador;
    f32 jugador_a_distancia_caparazon;
    s16 id_jugador = -1;
    f32 distancia_mas_chico = 25000000.0f;

    for (indice_jugador = 0; indice_jugador < 4; indice_jugador++) {
        jugador = &jugadores[indice_jugador];
        if ((jugador->type & EXISTE_JUGADOR) == 0) {
            continue;
        }
        if (jugador == duenio) {
            continue;
        }
        if (cantidad_globo_jugador[indice_jugador] < 0) {
            continue;
        }
        jugador_a_distancia_caparazon = dist_al_cuadrado_con_error(jugador->pos, caparazon->pos);
        if (jugador_a_distancia_caparazon < distancia_mas_chico) {
            distancia_mas_chico = jugador_a_distancia_caparazon;
            id_jugador = jugador - jugador_uno;
        }
    }

    return id_jugador;
}

void funcion_802B4104(struct ActorCaparazon* caparazon) {
    if ((caparazon->desconocido30.distancia_superficie[0] < 0.0f) &&
        ((caparazon->desconocido30.desconocido48[1] < 0.25f) || (caparazon->desconocido30.desconocido48[1] > -0.25f))) {
        destruir_actor_destructible((struct Actor*) caparazon);
        funcion_800C98B8(caparazon->pos, caparazon->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x54));
        caparazon->flags |= 0x80;
    } else if ((caparazon->desconocido30.distancia_superficie[1] < 0.0f) &&
               ((caparazon->desconocido30.desconocido54[1] < 0.25f) || (caparazon->desconocido30.desconocido54[1] < -0.25f))) {
        destruir_actor_destructible((struct Actor*) caparazon);
        funcion_800C98B8(caparazon->pos, caparazon->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x54));
        caparazon->flags |= 0x80;
    }
}

void actualizar_actor_rojo_caparazon_azul(struct ActorCaparazon* caparazon) {
    SIN_USO f32 relleno9;
    Jugador* jugador;
    f32 altura;
    SIN_USO f32 temporal_f14;
    f32 temporal_f2;
    s16 temporal_v0;
    SIN_USO s16 relleno3;
    Vec3f algun_vel_pos;
    struct Mando* mando;
    TriplePadreCaparazon* padre;
    SIN_USO f32 relleno0;
    SIN_USO f32 relleno1;
    SIN_USO f32 relleno2;
    SIN_USO f32 relleno4;
    SIN_USO f32 relleno5;
    SIN_USO f32 relleno6;
    SIN_USO f32 relleno7;
    SIN_USO f32 relleno8;
    SIN_USO f32 relleno10;
    SIN_USO f32 relleno11;
    SIN_USO f32 relleno12;
    SIN_USO s16 relleno13;
    SIN_USO s16 relleno13_2;
    SIN_USO f32 relleno14;
    SIN_USO f32 relleno15;
    SIN_USO f32 relleno16;
    SIN_USO f32 relleno17;
    Vec3f orig_pos;

    relleno1 = caparazon->pos[0];
    relleno0 = caparazon->pos[2];
    relleno2 = caparazon->pos[1];
    relleno13 = caparazon->type;
    if ((relleno0 < (f32) min_z_circuito) || ((f32) max_z_circuito < relleno0) || (relleno1 < (f32) min_x_circuito) ||
        ((f32) max_x_circuito < relleno1) || (relleno2 < (f32) min_y_circuito)) {
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
            relleno7 = jugador->pos[1] - algun_vel_pos[1];
            caparazon->pos[2] = jugador->pos[2] + algun_vel_pos[2];
            altura = calcular_altura_superficie(caparazon->pos[0], relleno7, caparazon->pos[2], jugador->colision.indice_zx_malla);
            temporal_f2 = relleno7 - altura;

            if ((temporal_f2 < 5.0f) && (temporal_f2 > -5.0f)) {
                caparazon->pos[1] = caparazon->tamanio_caja_envolvente + altura;
            } else {
                caparazon->pos[1] = relleno7;
            }

            if ((jugador->type & HUMANO_JUGADOR) != 0) {
                if (modo_demo) {
                    mando = mando_uno;
                } else {
                    mando = &mandos[caparazon->id_jugador];
                }
            } else {
                mando = mando_uno;
            }

            if ((mando->boton_apretado & Z_TRIG) != 0) {
                mando->boton_apretado &= ~Z_TRIG;
                caparazon->state = CAPARAZON_SOLTADO;
                if (jugador->desconocido_0C0 > 0) {
                    caparazon->angulo_rot = GRADOS(170);
                } else {
                    caparazon->angulo_rot = -GRADOS(170) - 1;
                }
            }
            break;
        case CAPARAZON_SOLTADO:
            jugador = &jugadores[caparazon->id_jugador];
            if (caparazon->angulo_rot > 0) {
                caparazon->angulo_rot -= GRADOS(10);
                if (caparazon->angulo_rot < 0) {
                    caparazon->state = CAPARAZON_MOVIENDO;
                    funcion_800C9060(caparazon->id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x04));
                    funcion_800C90F4(caparazon->id_jugador,
                                  (jugador->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x00));
                    if (relleno13 == ACTOR_CAPARAZON_ROJO) {
                        agregar_caparazon_rojo_en_lista_actor_vigente((struct Actor*) caparazon - lista_actor);
                    } else {
                        agregar_caparazon_azul_en_lista_actor_vigente((struct Actor*) caparazon - lista_actor);
                        funcion_800C9D80(caparazon->pos, caparazon->velocidad, SONIDO_CARGA_PARAMETRO(0x51, 0x01, 0x80, 0x08));
                    }
                }
            } else {
                caparazon->angulo_rot += GRADOS(10);
                if (caparazon->angulo_rot > 0) {
                    caparazon->state = CAPARAZON_MOVIENDO;
                    funcion_800C9060(caparazon->id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x04));
                    funcion_800C90F4(caparazon->id_jugador,
                                  (jugador->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x00));
                    if (relleno13 == ACTOR_CAPARAZON_ROJO) {
                        agregar_caparazon_rojo_en_lista_actor_vigente((struct Actor*) caparazon - lista_actor);
                    } else {
                        agregar_caparazon_azul_en_lista_actor_vigente((struct Actor*) caparazon - lista_actor);
                        funcion_800C9D80(caparazon->pos, caparazon->velocidad, SONIDO_CARGA_PARAMETRO(0x51, 0x01, 0x80, 0x08));
                    }
                }
            }
            if (caparazon->state == CAPARAZON_MOVIENDO) {
                caparazon->algun_temporizador = 0x001E;
                altura = 8.0f;
                if (jugador->speed > 8.0f) {
                    altura = jugador->speed * 1.2f;
                }
                algun_vel_pos[0] = 0.0f;
                algun_vel_pos[1] = 0.0f;
                algun_vel_pos[2] = altura;
                vec3f_rotar_eje_y(algun_vel_pos, (s16) (jugador->rotacion[1] + jugador->desconocido_0C0));
                caparazon->velocidad[0] = algun_vel_pos[0];
                caparazon->velocidad[1] = algun_vel_pos[1];
                caparazon->velocidad[2] = algun_vel_pos[2];
            } else {
                algun_vel_pos[0] = senos(caparazon->angulo_rot) * 8.0f;
                algun_vel_pos[1] = caparazon->tamanio_caja_envolvente - jugador->tamanio_caja_envolvente;
                algun_vel_pos[2] = coss(caparazon->angulo_rot) * 8.0f;
                transformar_mat3_vec3f_mtxf(algun_vel_pos, jugador->matriz_orientacion);
                caparazon->pos[0] = jugador->pos[0] + algun_vel_pos[0];
                caparazon->pos[1] = jugador->pos[1] + algun_vel_pos[1];
                caparazon->pos[2] = jugador->pos[2] + algun_vel_pos[2];
            }
            break;
        case CAPARAZON_MOVIENDO:
            jugador = &jugadores[caparazon->id_jugador];
            caparazon->algun_temporizador -= 1;
            if (caparazon->algun_temporizador == 0) {
                caparazon->flags &= 0xEFFF;
                if (caparazon->type == AZUL_ACTOR_CAPARAZON_ESPINOSO) {
                    caparazon->jugador_objetivo = lut_posicion_jugador[0];
                    caparazon->state = CAPARAZON_AZUL_BLOQUEO_EN;
                    caparazon->id_caparazon = 1000.0f;
                    temporal_v0 = punto_camino_mas_cercano_por_id_jugador[jugador - jugador_uno] + 8;
                    if ((s32) cantidad_camino_seleccionado < temporal_v0) {
                        temporal_v0 -= cantidad_camino_seleccionado;
                    }
                    caparazon->indice_camino = temporal_v0;
                } else if (seleccion_modo == BATALLA) {
                    caparazon->id_caparazon = 1000.0f;
                    caparazon->jugador_objetivo = funcion_802B3FD0(jugador, caparazon);
                    if (caparazon->jugador_objetivo < 0) {
                        caparazon->flags = 0x8000;
                        caparazon->velocidad[1] = 3.0f;
                        caparazon->indice_camino = 0;
                        caparazon->algun_temporizador = 0x003C;
                        caparazon->state = CAPARAZON_DESTRUIDO;
                    } else {
                        caparazon->state = CAPARAZON_ROJO_BLOQUEO_EN;
                    }
                } else {
                    if (jugador->puesto_actual == 0) {
                        caparazon->state = TRIPLE_CAPARAZON_VERDE;
                        caparazon->algun_temporizador = 0x0258;
                        temporal_v0 = punto_camino_mas_cercano_por_id_jugador[jugador - jugador_uno] + 8;
                        if ((s32) cantidad_camino_seleccionado < temporal_v0) {
                            temporal_v0 -= cantidad_camino_seleccionado;
                        }
                        caparazon->indice_camino = temporal_v0;
                    } else if (jugador->puesto_actual >= 5) {
                        caparazon->state = CAPARAZON_VERDE_CORREDOR_GOLPE_A;
                        caparazon->id_caparazon = 1000.0f;
                        temporal_v0 = punto_camino_mas_cercano_por_id_jugador[jugador - jugador_uno] + 8;
                        if ((s32) cantidad_camino_seleccionado < temporal_v0) {
                            temporal_v0 -= cantidad_camino_seleccionado;
                        }
                        caparazon->indice_camino = temporal_v0;
                        caparazon->jugador_objetivo = lut_posicion_jugador[jugador->puesto_actual - 1];
                    } else {
                        caparazon->state = CAPARAZON_ROJO_BLOQUEO_EN;
                        caparazon->id_caparazon = 1000.0f;
                        caparazon->jugador_objetivo = lut_posicion_jugador[jugador->puesto_actual - 1];
                    }
                }
            }
            caparazon->velocidad[1] -= 0.5;
            if (caparazon->velocidad[1] < -2.0f) {
                caparazon->velocidad[1] = -2.0f;
            }
            orig_pos[0] = caparazon->pos[0];
            orig_pos[1] = caparazon->pos[1];
            orig_pos[2] = caparazon->pos[2];
            caparazon->pos[0] += caparazon->velocidad[0];
            caparazon->pos[1] += caparazon->velocidad[1];
            caparazon->pos[2] += caparazon->velocidad[2];
            colision_terreno_actor(&caparazon->desconocido30, 4.0f, caparazon->pos[0], caparazon->pos[1], caparazon->pos[2], orig_pos[0],
                                    orig_pos[1], orig_pos[2]);
            funcion_802B4E30((struct Actor*) caparazon);
            funcion_802B4104(caparazon);
            break;
        case CAPARAZON_ROJO_BLOQUEO_EN:
            funcion_802B3E7C(caparazon, &jugadores[caparazon->jugador_objetivo]);
            break;
        case TRIPLE_CAPARAZON_VERDE:
            funcion_802B3B44(caparazon);
            if (caparazon->algun_temporizador == 0) {
                if ((caparazon->flags & 0xF) == 0) {
                    destruir_actor_destructible((struct Actor*) caparazon);
                } else {
                    caparazon->algun_temporizador -= 1;
                }
            }
            break;
        case CAPARAZON_VERDE_CORREDOR_GOLPE_A:
            funcion_802B3B44(caparazon);
            jugador = &jugadores[caparazon->jugador_objetivo];
            altura = jugador->pos[0];
            altura -= caparazon->pos[0];
            temporal_f2 = jugador->pos[2];
            temporal_f2 -= caparazon->pos[2];
            if (((altura * altura) + (temporal_f2 * temporal_f2)) < 40000.0f) {
                caparazon->state = CAPARAZON_ROJO_BLOQUEO_EN;
            }
            break;
        case TRIPLE_CAPARAZON_ROJO:
            jugador = &jugadores[caparazon->id_jugador];
            padre = (TriplePadreCaparazon*) &lista_actor[caparazon->indice_padre];
            if (padre->type != TRIPLE_ACTOR_CAPARAZON_ROJO) {
                destruir_actor_destructible((struct Actor*) caparazon);
            } else {
                caparazon->angulo_rot += padre->velocidad_rot;
                algun_vel_pos[0] = senos(caparazon->angulo_rot) * 8.0f;
                algun_vel_pos[1] = caparazon->tamanio_caja_envolvente - jugador->tamanio_caja_envolvente;
                algun_vel_pos[2] = coss(caparazon->angulo_rot) * 8.0f;
                transformar_mat3_vec3f_mtxf(algun_vel_pos, jugador->matriz_orientacion);
                orig_pos[0] = caparazon->pos[0];
                orig_pos[1] = caparazon->pos[1];
                orig_pos[2] = caparazon->pos[2];
                caparazon->pos[0] = jugador->pos[0] + algun_vel_pos[0];
                caparazon->pos[1] = jugador->pos[1] + algun_vel_pos[1];
                caparazon->pos[2] = jugador->pos[2] + algun_vel_pos[2];
                colision_terreno_actor(&caparazon->desconocido30, 4.0f, caparazon->pos[0], caparazon->pos[1], caparazon->pos[2], orig_pos[0],
                                        orig_pos[1], orig_pos[2]);
                funcion_802B4E30((struct Actor*) caparazon);
            }
            break;
        case CAPARAZON_DESTRUIDO:
            caparazon->velocidad[1] -= 0.3f;
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
        case CAPARAZON_AZUL_BLOQUEO_EN:
            funcion_802B3B44(caparazon);
            caparazon->jugador_objetivo = lut_posicion_jugador[0];
            jugador = &jugadores[lut_posicion_jugador[0]];
            altura = jugador->pos[0];
            altura -= caparazon->pos[0];
            temporal_f2 = jugador->pos[2];
            temporal_f2 -= caparazon->pos[2];
            if (((altura * altura) + (temporal_f2 * temporal_f2)) < 40000.0f) {
                caparazon->state = CAPARAZON_AZUL_OBJETIVO_ELIMINADO;
            }
            break;
        case 9:
            funcion_802B3E7C(caparazon, &jugadores[caparazon->jugador_objetivo]);
            break;
        default:
            break;
    }
}
