// Particulas superficie

void funcion_8005F90C(Jugador* jugador, s16 parametro1, s32 parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4) {
    s32 variable_t1;
    u8 tipo_superficie;
    f32 x;
    f32 y;
    f32 z;

    variable_t1 = 0;
    if ((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) {
        x = jugador->pos[0];
        y = jugador->pos[1] - jugador->tamanio_caja_envolvente;
        z = jugador->pos[2];
        variable_t1 = 1;
        tipo_superficie = jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie & 0xFF;
    } else {
        x = jugador->pos[0];
        y = jugador->pos[1] - jugador->tamanio_caja_envolvente;
        z = jugador->pos[2];
        tipo_superficie = jugador->ruedas[DERECHA_ATRAS].tipo_superficie & 0xFF;
    }
    switch (tipo_superficie) {
        case TIERRA:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 4, 0.46f);
                if ((id_circuito_actual == CIRCUITO_CHOCO_MOUNTAIN) || (id_circuito_actual == CIRCUITO_ROYAL_RACEWAY)) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 1, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_KALAMARI_DESERT) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 7, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_MOO_MOO_FARM) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 8, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_WARIO_STADIUM) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 9, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_YOSHI_VALLEY) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 0x000A, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_DK_JUNGLE) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 0x000B, 0, 0x0080);
                }
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 4, 0.46f);
                if ((id_circuito_actual == CIRCUITO_CHOCO_MOUNTAIN) || (id_circuito_actual == CIRCUITO_ROYAL_RACEWAY)) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 1, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_KALAMARI_DESERT) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 7, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_MOO_MOO_FARM) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 8, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_WARIO_STADIUM) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 9, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_YOSHI_VALLEY) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 0x000A, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_DK_JUNGLE) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 0x000B, 0, 0x0080);
                }
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case PASTO:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 4, 0.1f);
                fijar_color_particula(&jugador->pool_particula_1[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x00FF);
                jugador->pool_particula_1[parametro1].rojo -= parametro1 * 8;
                jugador->pool_particula_1[parametro1].verde -= parametro1 * 8;
                jugador->pool_particula_1[parametro1].azul -= parametro1 * 8;
            } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 4, 0.1f);
                fijar_color_particula(&jugador->pool_particula_1[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x00FF);
                jugador->pool_particula_1[parametro1].rojo -= parametro1 * 8;
                jugador->pool_particula_1[parametro1].verde -= parametro1 * 8;
                jugador->pool_particula_1[parametro1].azul -= parametro1 * 8;
            }
            jugador->pool_particula_1[parametro1].pos[1] -= 1.5;
            break;
        case FUERA_PISTA_ARENA:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 4, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 2, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 4, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 2, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case ARENA:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 4, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 3, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 4, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 3, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case ARENA_HUMEDO:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 4, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 4, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 4, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 4, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case FUERA_PISTA_TIERRA:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 4, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 5, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 4, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 5, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case NIEVE:
        case FUERA_PISTA_NIEVE:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 4, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 6, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 4, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 6, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case ASFALTO:
        case PIEDRA:
        case PUENTE:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 4, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 0, 0, 0x0080);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 4, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 0, 0, 0x0080);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        default:
            break;
    }
}

void funcion_80060504(Jugador* jugador, s16 parametro1, s32 parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4) {
    SIN_USO s32 cosa1;
    s16 cosa2;
    SIN_USO s32 cosa3;
    f32 x;
    f32 y;
    f32 z;
    f32 variable_f0;
    s32 variable_v0;
    s32 temporal_v0;
    SIN_USO s32 probar;

    if ((jugador->kart_props & ACELERADOR) == ACELERADOR) {
        variable_v0 = 5;
    } else {
        variable_v0 = 0xE;
    }
    temporal_v0 = int_aleatorio(variable_v0);
    if ((temporal_v0 == 1) || (temporal_v0 == 2) || (temporal_v0 == 3)) {
        if ((parametro1 == 0) && ((jugador->pool_particula_0[parametro2].temporizador > 0) || (jugador->pool_particula_0[parametro2].vivo_es == 0))) {
            y = jugador->pos[1] - 2.5;
            z = jugador->pos[2];
            x = jugador->pos[0];
            fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_0[parametro1], x, y, z, 0, 0);
            inicializar_jugador_particula(&jugador->pool_particula_0[parametro1], 1, 0.5f);
        } else if (jugador->pool_particula_0[parametro2].temporizador > 0) {
            y = jugador->pos[1] - 2.5;
            z = jugador->pos[2];
            x = jugador->pos[0];
            fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_0[parametro1], x, y, z, 0, 0);
            inicializar_jugador_particula(&jugador->pool_particula_0[parametro1], 1, 0.5f);
        }
    }
    jugador->pool_particula_0[parametro1].desconocido_024 = 0.0f;
    if ((jugador->kart_props & ACELERADOR) == ACELERADOR) {
        jugador->pool_particula_0[parametro1].desconocido_040 = 0;
        if ((jugador->efectos & EFECTO_HONGO) == EFECTO_HONGO) {
            fijar_color_particula(&jugador->pool_particula_0[parametro1], RGB32(0xFF, 0xFF, 0x00), 0x0080);
            jugador->pool_particula_0[parametro1].rojo = 1;
        } else {
            fijar_color_particula(&jugador->pool_particula_0[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x0070);
            jugador->pool_particula_0[parametro1].rojo = 0;
        }
    } else {
        jugador->pool_particula_0[parametro1].desconocido_040 = 1;
        if ((jugador->efectos & EFECTO_HONGO) == EFECTO_HONGO) {
            fijar_color_particula(&jugador->pool_particula_0[parametro1], RGB32(0xFF, 0xFF, 0x00), 0x0080);
            jugador->pool_particula_0[parametro1].rojo = 1;
        } else {
            fijar_color_particula(&jugador->pool_particula_0[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x0070);
            jugador->pool_particula_0[parametro1].rojo = 0;
        }
    }
    cosa2 = (jugador->pool_particula_0[parametro1].rotacion - (jugador->desconocido_0C0 / 2));
    if (jugador->pool_particula_0[parametro1].desconocido_040 == 0) {
        variable_f0 = -((jugador->desconocido_098 / 3000.0f) + 0.1);
    } else {
        variable_f0 = -((jugador->desconocido_098 / 5000.0f) + 0.1);
    }
    funcion_80062B18(&x, &y, &z, 0.0f, 4.5f, (jugador->pool_particula_0[parametro1].temporizador * variable_f0) + -5.5, -cosa2,
                  -jugador->desconocido_206 * 2);
    jugador->pool_particula_0[parametro1].pos[0] = jugador->pos[0] + x;
    y = y + (jugador->pos[1] - jugador->tamanio_caja_envolvente);
    jugador->pool_particula_0[parametro1].pos[2] = jugador->pos[2] + z;
    jugador->pool_particula_0[parametro1].pos[1] = jugador->pool_particula_0[parametro1].desconocido_024 + y;
    jugador->pool_particula_0[parametro1].desconocido_010 = 0;
}

void funcion_800608E0(Jugador* jugador, s16 parametro1, SIN_USO s32 parametro2, s8 parametro3, SIN_USO s8 parametro4) {
    f32 variable_f0;
    f32 sp50;
    f32 sp4_c;
    f32 sp48;

    variable_f0 = 8.0f - (dato_801652A0[parametro3] - jugador->pos[1]);
    if ((f64) variable_f0 <= 0.0) {
        variable_f0 = 0.0f;
    }
    sp4_c = (dato_801652A0[parametro3] - jugador->pos[1]) - 3.0f;
    if ((jugador->oob_props & BAJO_OOB_O_NIVEL_FLUIDO) && (id_circuito_actual != CIRCUITO_KOOPA_BEACH)) {
        variable_f0 = 2.5f;
        sp4_c = (f32) ((f64) (dato_801652A0[parametro3] - jugador->pos[1]) + 0.1);
    }
    fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_0[parametro1], 0.0f, 0.0f, 0.0f, (s8) 0, (s8) 0);
    inicializar_jugador_particula(&jugador->pool_particula_0[parametro1], 3, variable_f0);
    if ((id_circuito_actual == CIRCUITO_BOWSER_CASTLE) || (id_circuito_actual == CIRCUITO_BIG_DONUT)) {
        fijar_color_particula(&jugador->pool_particula_0[parametro1], RGB32(0x0, 0x0, 0x0), 0x00AF);
    } else {
        fijar_color_particula(&jugador->pool_particula_0[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x00CF);
    }
    funcion_80062B18(&sp50, &sp4_c, &sp48, 0.0f, sp4_c,
                  ((-jugador->pool_particula_0[parametro1].temporizador * (jugador->speed / 18.0f) * 216.0f) / 10.0f) + -4.0f,
                  -jugador->pool_particula_0[parametro1].rotacion, -jugador->desconocido_206 * 2);
    jugador->pool_particula_0[parametro1].pos[0] = jugador->pos[0] + sp50;
    jugador->pool_particula_0[parametro1].pos[2] = jugador->pos[2] + sp48;
    jugador->pool_particula_0[parametro1].pos[1] = jugador->pos[1] + sp4_c;
}

void funcion_80060B14(Jugador* jugador, s16 parametro1, s32 parametro2, s8 parametro3, s8 parametro4) {
    if ((id_circuito_actual != CIRCUITO_SKYSCRAPER) && (id_circuito_actual != CIRCUITO_RAINBOW_ROAD)) {
        if ((parametro1 == 0) && ((jugador->pool_particula_0[parametro2].temporizador > 0) || (jugador->pool_particula_0[parametro2].vivo_es == 0))) {
            funcion_800608E0(jugador, parametro1, parametro2, parametro3, parametro4);
        } else if (jugador->pool_particula_0[parametro2].temporizador > 0) {
            funcion_800608E0(jugador, parametro1, parametro2, parametro3, parametro4);
        }
    }
}

void funcion_80060BCC(Jugador* jugador, s16 parametro1, s32 parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4) {
    s32 sp54;
    SIN_USO s32 relleno;
    s32 sp4_c;
    f32 sp48;
    f32 sp44;

    if (id_circuito_actual == CIRCUITO_SKYSCRAPER) {
        return;
    }
    if (id_circuito_actual == CIRCUITO_RAINBOW_ROAD) {
        return;
    }
    sp54 = int_aleatorio(0x0168U) - 0xB4;
    sp4_c = int_aleatorio(6U);
    sp44 = int_aleatorio(6U);
    sp48 = int_aleatorio(3U);
    if (jugador != jugador_uno) {
        return;
    }
    if ((parametro1 == 0) && ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
        fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], 0.0f, 0.0f, 0.0f, (s8) 0, (s8) 0);
        inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 0x0B, 0.4f);
        fijar_color_particula(&jugador->pool_particula_1[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x00FF);
        jugador->pool_particula_1[parametro1].pos[2] = jugador->pos[2] + (coss(sp54 * GRADOS(1)) * -1.8);
        jugador->pool_particula_1[parametro1].pos[0] = jugador->pos[0] + (senos(sp54 * GRADOS(1)) * -1.8);
        jugador->pool_particula_1[parametro1].pos[1] = (jugador->pos[1] - jugador->tamanio_caja_envolvente) + sp4_c + 2.0f;
        jugador->pool_particula_1[parametro1].desconocido_018 = sp44 + 1.0f;
        jugador->pool_particula_1[parametro1].scale = (sp48 + 2.0f) / 10.0f;
    } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
        fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], 0.0f, 0.0f, 0.0f, (s8) 0, (s8) 0);
        inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 0x0B, 0.4f);
        fijar_color_particula(&jugador->pool_particula_1[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x00FF);
        jugador->pool_particula_1[parametro1].pos[2] = jugador->pos[2] + (coss(sp54 * GRADOS(1)) * -1.8);
        jugador->pool_particula_1[parametro1].pos[0] = jugador->pos[0] + (senos(sp54 * GRADOS(1)) * -1.8);
        jugador->pool_particula_1[parametro1].pos[1] = (jugador->pos[1] - jugador->tamanio_caja_envolvente) + sp4_c + 2.0f;
        jugador->pool_particula_1[parametro1].desconocido_018 = sp44 + 1.0f;
        jugador->pool_particula_1[parametro1].scale = (sp48 + 2.0f) / 10.0f;
    }
}

void funcion_80060F50(Jugador* jugador, s16 parametro1, SIN_USO s32 parametro2, s8 parametro3, SIN_USO s8 parametro4) {
    fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_0[parametro1], 0.0f, 0.0f, 0.0f, 0, 0);
    inicializar_jugador_particula(&jugador->pool_particula_0[parametro1], 5, 4.0f);

    if ((id_circuito_actual == CIRCUITO_BOWSER_CASTLE) || (id_circuito_actual == CIRCUITO_BIG_DONUT)) {
        fijar_color_particula(&jugador->pool_particula_0[parametro1], RGB32(0xFF, 0x00, 0x00), 0xFF);
    } else {
        fijar_color_particula(&jugador->pool_particula_0[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0xFF);
    }

    jugador->pool_particula_0[parametro1].pos[2] = jugador->pos[2] + (coss(jugador->pool_particula_0[parametro1].rotacion) * -5.8);
    jugador->pool_particula_0[parametro1].pos[0] = jugador->pos[0] + (senos(jugador->pool_particula_0[parametro1].rotacion) * -5.8);
    jugador->pool_particula_0[parametro1].pos[1] = dato_801652A0[parametro3];
    jugador->oob_props &= ~BAJO_NIVEL_OOB;
}

void funcion_80061094(Jugador* jugador, s16 parametro1, SIN_USO s32 parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4) {
    if (parametro1 == 0) {
        fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_0[parametro1], 0.0f, 0.0f, 0.0f, 0, 0);
        inicializar_jugador_particula(&jugador->pool_particula_0[parametro1], 6, 3.8f);
        fijar_color_particula(&jugador->pool_particula_0[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0xFF);
        jugador->pool_particula_0[parametro1].rojo = 0;
        jugador->pool_particula_0[parametro1].verde = 0;
        jugador->pool_particula_0[parametro1].azul = 0;
    }
}

void funcion_80061130(Jugador* jugador, s16 parametro1, SIN_USO s32 parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4) {
    fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_0[parametro1], 0.0f, 0.0f, 0.0f, 0, 0);
    inicializar_jugador_particula(&jugador->pool_particula_0[parametro1], 7, 0.6f);
    fijar_color_particula(&jugador->pool_particula_0[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0xD0);

    jugador->pool_particula_0[parametro1].pos[2] = jugador->pos[2] + (coss(jugador->pool_particula_0[parametro1].rotacion) * 6.0f);
    jugador->pool_particula_0[parametro1].pos[0] = jugador->pos[0] + (senos(jugador->pool_particula_0[parametro1].rotacion) * 6.0f);
    jugador->pool_particula_0[parametro1].pos[1] = jugador->pos[1] - 5.0f;
    jugador->pool_particula_0[parametro1].desconocido_040 = 0;
    jugador->pool_particula_0[parametro1].desconocido_024 = 0.0f;
}

void funcion_80061224(Jugador* jugador, s16 parametro1, s32 parametro2, s8 parametro3, s8 parametro4) {
    if ((parametro1 == 0) && ((jugador->pool_particula_0[parametro2].temporizador > 0) || (jugador->pool_particula_0[parametro1].vivo_es == 0))) {
        funcion_80061130(jugador, parametro1, parametro2, parametro3, parametro4);
    } else if (jugador->pool_particula_0[parametro2].temporizador >= 2) {
        funcion_80061130(jugador, parametro1, parametro2, parametro3, parametro4);
        if (parametro1 == 9) {
            jugador->kart_props &= ~INVISIBLE_VOLVERSE;
        }
    }
}

void funcion_800612F8(Jugador* jugador, SIN_USO s32 parametro1, SIN_USO s32 parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4) {
    s32 variable_s2;

    for (variable_s2 = 0; variable_s2 < 10; variable_s2++) {
        jugador->pool_particula_3[variable_s2].vivo_es = 1;
        jugador->pool_particula_3[variable_s2].desconocido_028 = jugador->pos[1] + 5.0f;
        jugador->pool_particula_3[variable_s2].rotacion = (40 * GRADOS(1) * variable_s2) - jugador->rotacion[1];
        jugador->pool_particula_3[variable_s2].desconocido_024 = (int_aleatorio(0x0064U) / 100.0f) + 1.5;
        jugador->pool_particula_3[variable_s2].verde = 0;
        jugador->pool_particula_3[variable_s2].type = 1;
        jugador->pool_particula_3[variable_s2].temporizador = 0;
        jugador->pool_particula_3[variable_s2].alpha = 0x00FF;
        jugador->pool_particula_3[variable_s2].pos[2] = jugador->pos[2];
        jugador->pool_particula_3[variable_s2].pos[0] = jugador->pos[0];
    }
    jugador->desconocido_046 &= ~0x0008;
}

void funcion_80061430(Jugador* jugador, SIN_USO s32 parametro1, SIN_USO s32 parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4) {
    s32 variable_s2;

    for (variable_s2 = 0; variable_s2 < 7; variable_s2++) {
        jugador->pool_particula_3[variable_s2].vivo_es = 1;
        jugador->pool_particula_3[variable_s2].desconocido_028 = jugador->pos[1] - 4.0f;
        jugador->pool_particula_3[variable_s2].rotacion = (40 * GRADOS(1) * variable_s2) - jugador->rotacion[1];
        jugador->pool_particula_3[variable_s2].desconocido_024 = (int_aleatorio(0x0064U) / 100.0f) + 1.9;
        jugador->pool_particula_3[variable_s2].desconocido_024 = (int_aleatorio(0x0064U) / 100.0f) + 1.5;
        jugador->pool_particula_3[variable_s2].verde = 0;
        jugador->pool_particula_3[variable_s2].type = 9;
        jugador->pool_particula_3[variable_s2].temporizador = 0;
        jugador->pool_particula_3[variable_s2].alpha = 0x00FF;
        jugador->pool_particula_3[variable_s2].pos[2] = jugador->pos[2];
        jugador->pool_particula_3[variable_s2].pos[0] = jugador->pos[0];
    }
    jugador->kart_props &= ~sin_uso_0_x_1000;
}

void funcion_800615AC(Jugador* jugador, s16 parametro1, SIN_USO s32 parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4) {
    s32 probar = 2;
    SIN_USO s32 margen_pila_0;
    SIN_USO s32 margen_pila_1;
    f32 temporal_f0;
    f32 sp28[10] = { (f32) -GRADOS(1), (f32) GRADOS(1), (f32) GRADOS(2), (f32) -GRADOS(2), GRADOS(3), -GRADOS(3), GRADOS(4), -GRADOS(4), GRADOS(5), -GRADOS(5) };

    if (int_aleatorio(3U) == 2.0f) {
        jugador->pool_particula_3[parametro1].vivo_es = 1;
        jugador->pool_particula_3[parametro1].pos[0] = jugador->pos[0];
        jugador->pool_particula_3[parametro1].pos[2] = jugador->pos[2];
        jugador->pool_particula_3[parametro1].rotacion = -jugador->rotacion[1] + sp28[parametro1];
        jugador->pool_particula_3[parametro1].desconocido_018 = int_aleatorio(1U) + 2.0f;
        temporal_f0 = int_aleatorio(4U);
        temporal_f0 -= probar;
        jugador->pool_particula_3[parametro1].tipo_superficie = temporal_f0;
        jugador->pool_particula_3[parametro1].pos[1] = jugador->pos[1] + temporal_f0;
        jugador->pool_particula_3[parametro1].scale = 0.15f;
        jugador->pool_particula_3[parametro1].type = 5;
        jugador->pool_particula_3[parametro1].temporizador = 0;
        jugador->pool_particula_3[parametro1].alpha = 0x00FF;
        jugador->pool_particula_3[parametro1].rojo = 0;
    }
}

void funcion_80061754(Jugador* jugador, s16 parametro1, SIN_USO s32 parametro2, SIN_USO s32 parametro3, SIN_USO s32 parametro4) {
    s32 sp54;
    s16 temporal_s1;
    s32 sp4_c;
    f32 sp48;
    f32 sp44;

    sp54 = int_aleatorio(0x0168U) - 0xB4;
    sp4_c = int_aleatorio(6U);
    temporal_s1 = int_aleatorio(0x0060U);
    sp44 = int_aleatorio(6U);
    sp48 = int_aleatorio(2U);
    fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_3[parametro1], 0.0f, 0.0f, 0.0f, (s8) 0, (s8) 0);
    inicializar_jugador_particula(&jugador->pool_particula_3[parametro1], 6, 1.0f);
    if ((jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA) || ((jugador->efectos) & EFECTO_ERROR_EXPLOSION) ||
        ((jugador->efectos) & GOLPE_POR_CAPARAZON_VERDE_EFECTO) || ((jugador->efectos) & BOO_EFECTO)) {
        fijar_color_particula(&jugador->pool_particula_3[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x00A0);
        jugador->pool_particula_3[parametro1].rojo -= temporal_s1;
        jugador->pool_particula_3[parametro1].verde -= temporal_s1;
        jugador->pool_particula_3[parametro1].azul -= temporal_s1;
    } else {
        fijar_color_particula(&jugador->pool_particula_3[parametro1], RGB32(0x0, 0x0, 0x0), 0x00A0);
        jugador->pool_particula_3[parametro1].rojo += temporal_s1;
        jugador->pool_particula_3[parametro1].verde += temporal_s1;
        jugador->pool_particula_3[parametro1].azul += temporal_s1;
    }
    jugador->pool_particula_3[parametro1].pos[2] = jugador->pos[2] + (coss(sp54 * GRADOS(1)) * -5.0f);
    jugador->pool_particula_3[parametro1].pos[0] = jugador->pos[0] + (senos(sp54 * GRADOS(1)) * -5.0f);
    jugador->pool_particula_3[parametro1].pos[1] = (jugador->pos[1] - jugador->tamanio_caja_envolvente) + sp4_c + 2.0f;
    jugador->pool_particula_3[parametro1].desconocido_018 = sp44 + 1.0f;
    jugador->pool_particula_3[parametro1].scale = sp48 + 1.0f;
}

void funcion_8006199C(Jugador* jugador, s16 parametro1, s32 parametro2, s8 parametro3, s8 parametro4) {
    if ((parametro1 == 0) && ((jugador->pool_particula_3[parametro2].temporizador > 0) || (jugador->pool_particula_3[parametro2].vivo_es == 0))) {
        funcion_80061754(jugador, parametro1, parametro2, (s32) parametro3, parametro4);
    } else if (jugador->pool_particula_3[parametro2].temporizador > 0) {
        funcion_80061754(jugador, parametro1, parametro2, (s32) parametro3, parametro4);
    }
}

void funcion_80061A34(Jugador* jugador, s16 parametro1, s32 parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4) {
    s32 sp54;
    SIN_USO s32 margen_pila_0;
    s32 sp4_c;
    f32 sp48;
    SIN_USO s32 margen_pila_1;

    sp54 = int_aleatorio(0x0168U) - 0xB4;
    sp4_c = int_aleatorio(6U);
    int_aleatorio(6U);
    sp48 = (f32) int_aleatorio(3U);
    if ((parametro1 == 0) && ((jugador->pool_particula_3[parametro2].temporizador > 0) || (jugador->pool_particula_3[parametro2].vivo_es == 0))) {
        fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_3[parametro1], 0.0f, 0.0f, 0.0f, (s8) 0, (s8) 0);
        inicializar_jugador_particula(&jugador->pool_particula_3[parametro1], 7, 1.0f);
        fijar_color_particula(&jugador->pool_particula_3[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x00FF);
        jugador->pool_particula_3[parametro1].pos[2] = jugador->pos[2] + (coss(sp54 * GRADOS(1)) * -2.0);
        jugador->pool_particula_3[parametro1].pos[0] = jugador->pos[0] + (senos(sp54 * GRADOS(1)) * -2.0);
        jugador->pool_particula_3[parametro1].pos[1] = (jugador->pos[1] - jugador->tamanio_caja_envolvente) + sp4_c + 2.0f;
        jugador->pool_particula_3[parametro1].scale = (sp48 + 2.0f) / 10.0f;
    } else if (jugador->pool_particula_3[parametro2].temporizador > 0) {
        fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_3[parametro1], 0.0f, 0.0f, 0.0f, (s8) 0, (s8) 0);
        inicializar_jugador_particula(&jugador->pool_particula_3[parametro1], 7, 1.0f);
        fijar_color_particula(&jugador->pool_particula_3[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x00FF);
        jugador->pool_particula_3[parametro1].pos[2] = jugador->pos[2] + (coss(sp54 * GRADOS(1)) * -2.0);
        jugador->pool_particula_3[parametro1].pos[0] = jugador->pos[0] + (senos(sp54 * GRADOS(1)) * -2.0);
        jugador->pool_particula_3[parametro1].pos[1] = (jugador->pos[1] - jugador->tamanio_caja_envolvente) + (f32) sp4_c + 2.0f;
        jugador->pool_particula_3[parametro1].scale = (sp48 + 2.0f) / 10.0f;
    }
}

void funcion_80061D4C(Jugador* jugador, s16 parametro1, SIN_USO s32 parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4) {
    s32 probar = 2;
    SIN_USO s32 margen_pila_0;
    SIN_USO s32 margen_pila_1;
    SIN_USO s32 margen_pila_2;
    f32 sp20[10] = { (f32) -GRADOS(1), (f32) GRADOS(1), (f32) GRADOS(2), (f32) -GRADOS(2), GRADOS(3), -GRADOS(3), GRADOS(4), -GRADOS(4), GRADOS(5), -GRADOS(5) };

    if (int_aleatorio(3U) == 2.0f) {
        jugador->pool_particula_3[parametro1].vivo_es = 1;
        jugador->pool_particula_3[parametro1].pos[0] = jugador->pos[0];
        jugador->pool_particula_3[parametro1].pos[1] = jugador->pos[1] + 2.0f;
        jugador->pool_particula_3[parametro1].pos[2] = jugador->pos[2];
        jugador->pool_particula_3[parametro1].rotacion = -jugador->rotacion[1] + sp20[parametro1];
        jugador->pool_particula_3[parametro1].desconocido_018 = int_aleatorio(3U) + 2.0f;
        jugador->pool_particula_3[parametro1].tipo_superficie = int_aleatorio(4U);
        jugador->pool_particula_3[parametro1].tipo_superficie -= probar;
        jugador->pool_particula_3[parametro1].scale = 0.4f;
        jugador->pool_particula_3[parametro1].type = 2;
        jugador->pool_particula_3[parametro1].temporizador = 0;
        jugador->pool_particula_3[parametro1].alpha = 0x00FF;
    }
}

void funcion_80061EF4(Jugador* jugador, s16 parametro1, s32 parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4) {
    SIN_USO s32 margen_pila_0;
    s32 variable_t0 = 0x000000FF;
    s32 variable_t1;
    s32 temporal_v1;
    f32 y;
    SIN_USO s32 margen_pila_1;

    if (1) {};
    temporal_v1 = int_aleatorio(8U) & 1;
    if (temporal_v1 == 1) {
        variable_t1 = 1;
        variable_t0 = 0;
        y = jugador->pos[1];
    }
    if (temporal_v1 == 0) {
        variable_t1 = 0;
        variable_t0 = 0;
        y = jugador->pos[1];
    }
    if (variable_t0 == 0) {
        if ((parametro1 == 0) &&
            ((jugador->pool_particula_3[parametro2].temporizador > 0) || (jugador->pool_particula_3[parametro2].vivo_es == 0))) {
            fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_3[parametro1], 0.0f, y, 0.0f, (s8) variable_t0, (s8) variable_t1);
            inicializar_jugador_particula(&jugador->pool_particula_3[parametro1], 3, 0.5f);
            fijar_color_particula(&jugador->pool_particula_3[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x0060);
            jugador->pool_particula_3[parametro1].rotacion = 0;
            if (jugador->pool_particula_3[parametro1].desconocido_010 == 1) {
                jugador->pool_particula_3[parametro1].rotacion += GRADOS(12);
            } else {
                jugador->pool_particula_3[parametro1].rotacion -= GRADOS(12);
            }
            jugador->pool_particula_3[parametro1].pos[2] =
                jugador->pos[2] +
                (coss(jugador->pool_particula_3[parametro1].rotacion - jugador->rotacion[1] - jugador->desconocido_0C0) * 5.0f);
            jugador->pool_particula_3[parametro1].pos[0] =
                jugador->pos[0] +
                (senos(jugador->pool_particula_3[parametro1].rotacion - jugador->rotacion[1] - jugador->desconocido_0C0) * 5.0f);
        } else if (jugador->pool_particula_3[parametro2].temporizador > 0) {
            fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_3[parametro1], 0.0f, y, 0.0f, (s8) variable_t0, (s8) variable_t1);
            inicializar_jugador_particula(&jugador->pool_particula_3[parametro1], 3, 0.5f);
            fijar_color_particula(&jugador->pool_particula_3[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x0060);
            jugador->pool_particula_3[parametro1].rotacion = 0;
            if (jugador->pool_particula_3[parametro1].desconocido_010 == 1) {
                jugador->pool_particula_3[parametro1].rotacion += GRADOS(12);
            } else {
                jugador->pool_particula_3[parametro1].rotacion -= GRADOS(12);
            }
            jugador->pool_particula_3[parametro1].pos[2] =
                jugador->pos[2] +
                (coss(jugador->pool_particula_3[parametro1].rotacion - jugador->rotacion[1] - jugador->desconocido_0C0) * 5.0f);
            jugador->pool_particula_3[parametro1].pos[0] =
                jugador->pos[0] +
                (senos(jugador->pool_particula_3[parametro1].rotacion - jugador->rotacion[1] - jugador->desconocido_0C0) * 5.0f);
        }
    }
}

void funcion_800621BC(Jugador* jugador, s16 parametro1, s32 parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4) {
    s32 temporal_v1;
    s32 phi_t0;
    s32 phi_t1;
    Jugador* variable_nuevo;
    f32 y;
    Jugador* variable2_nuevo;

    phi_t0 = 0xFF;
    temporal_v1 = int_aleatorio(8) & 1;
    if (temporal_v1 == 1) {
        phi_t1 = 1;
        phi_t0 = 0;
        y = jugador->pos[1];
    }

    if (temporal_v1 == 0) {
        phi_t1 = 0;
        if (1) {
            phi_t0 = 0;
        }
        y = jugador->pos[1];
    }

    if (phi_t0 == 0) {
        if ((parametro1 == 0) && ((jugador->pool_particula_3[parametro2].temporizador > 0) || (jugador->pool_particula_3[parametro2].vivo_es == 0))) {
            fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_3[parametro1], 0.0f, y, 0.0f, phi_t0, phi_t1);
            inicializar_jugador_particula(&jugador->pool_particula_3[parametro1], 8, 1.0f);
            fijar_color_particula(&jugador->pool_particula_3[parametro1], RGB32(0xFF, 0xFF, 0x20), 0xFF);

            jugador->pool_particula_3[parametro1].rotacion = 0;
            if (jugador->pool_particula_3[parametro1].desconocido_010 == 1) {
                jugador->pool_particula_3[parametro1].rotacion += GRADOS(12);
            } else {
                jugador->pool_particula_3[parametro1].rotacion -= GRADOS(12);
            }

            jugador->pool_particula_3[parametro1].pos[2] =
                jugador->pos[2] +
                (coss((jugador->pool_particula_3[parametro1].rotacion - jugador->rotacion[1]) - jugador->desconocido_0C0) * 5.0f);
            jugador->pool_particula_3[parametro1].pos[0] =
                jugador->pos[0] +
                (senos((jugador->pool_particula_3[parametro1].rotacion - jugador->rotacion[1]) - jugador->desconocido_0C0) * 5.0f);
            return;
        }

        variable2_nuevo = jugador;
        if (variable2_nuevo->pool_particula_3[parametro2].temporizador > 0) {
            fijar_posicion_particula_y_rotacion(variable2_nuevo, &variable2_nuevo->pool_particula_3[parametro1], 0.0f, y, 0.0f, phi_t0, phi_t1);
            inicializar_jugador_particula(&variable2_nuevo->pool_particula_3[parametro1], 8, 1.0f);
            fijar_color_particula(&variable2_nuevo->pool_particula_3[parametro1], RGB32(0xFF, 0xFF, 0x20), 0xFF);
            variable2_nuevo->pool_particula_3[parametro1].rotacion = 0;
            if (variable2_nuevo->pool_particula_3[parametro1].desconocido_010 == 1) {
                variable2_nuevo->pool_particula_3[parametro1].rotacion += GRADOS(12);
            } else {
                variable2_nuevo->pool_particula_3[parametro1].rotacion -= GRADOS(12);
            }

            variable_nuevo = variable2_nuevo;
            variable_nuevo->pool_particula_3[parametro1].pos[2] =
                variable_nuevo->pos[2] +
                (coss((variable_nuevo->pool_particula_3[parametro1].rotacion - variable_nuevo->rotacion[1]) - variable_nuevo->desconocido_0C0) * 5.0f);
            variable_nuevo->pool_particula_3[parametro1].pos[0] =
                variable_nuevo->pos[0] +
                (senos((variable_nuevo->pool_particula_3[parametro1].rotacion - variable_nuevo->rotacion[1]) - variable_nuevo->desconocido_0C0) * 5.0f);
        }
    }
}

void funcion_80062484(Jugador* jugador, Particula* parametro1, s32 parametro2) {
    parametro1->vivo_es = 1;
    parametro1->pos[1] = jugador->desconocido_074 + 1.0f;
    parametro1->pos[2] = jugador->pos[2];
    parametro1->pos[0] = jugador->pos[0];
    parametro1->rotacion = (parametro2 * (36 * GRADOS(1))) - jugador->rotacion[1];
    parametro1->type = 4;
    parametro1->temporizador = 0;
}

void funcion_800624D8(Jugador* jugador, SIN_USO s32 parametro1, SIN_USO s32 parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4) {
    s32 variable_s1;

    switch (jugador->tipo_superficie) {
        case TIERRA:
            for (variable_s1 = 0; variable_s1 < 10; variable_s1++) {
                if ((id_circuito_actual == CIRCUITO_CHOCO_MOUNTAIN) || (id_circuito_actual == CIRCUITO_ROYAL_RACEWAY)) {
                    funcion_8005DAD8(&jugador->pool_particula_3[variable_s1], 1, 0, 0x00A8);
                }
                if (id_circuito_actual == CIRCUITO_KALAMARI_DESERT) {
                    funcion_8005DAD8(&jugador->pool_particula_3[variable_s1], 7, 0, 0x00A8);
                }
                if (id_circuito_actual == CIRCUITO_MOO_MOO_FARM) {
                    funcion_8005DAD8(&jugador->pool_particula_3[variable_s1], 8, 0, 0x00A8);
                }
                if (id_circuito_actual == CIRCUITO_WARIO_STADIUM) {
                    funcion_8005DAD8(&jugador->pool_particula_3[variable_s1], 9, 0, 0x00A8);
                }
                if (id_circuito_actual == CIRCUITO_YOSHI_VALLEY) {
                    funcion_8005DAD8(&jugador->pool_particula_3[variable_s1], 0x000A, 0, 0x00A8);
                }
                if (id_circuito_actual == CIRCUITO_DK_JUNGLE) {
                    funcion_8005DAD8(&jugador->pool_particula_3[variable_s1], 0x000B, 0, 0x00A8);
                }
                funcion_80062484(jugador, &jugador->pool_particula_3[variable_s1], variable_s1);
            }
            jugador->kart_props &= ~ACELERADOR_VUELCO_PUBLICAR;
            break;
        case PASTO:
            for (variable_s1 = 0; variable_s1 < 10; variable_s1++) {
                funcion_8005DAD8(&jugador->pool_particula_3[variable_s1], 2, 1, 0x00A8);
                funcion_80062484(jugador, &jugador->pool_particula_3[variable_s1], variable_s1);
            }
            jugador->kart_props &= ~ACELERADOR_VUELCO_PUBLICAR;
            break;
        case FUERA_PISTA_ARENA:
            for (variable_s1 = 0; variable_s1 < 10; variable_s1++) {
                funcion_8005DAD8(&jugador->pool_particula_3[variable_s1], 2, 1, 0x00A8);
                funcion_80062484(jugador, &jugador->pool_particula_3[variable_s1], variable_s1);
            }
            jugador->kart_props &= ~ACELERADOR_VUELCO_PUBLICAR;
            break;
        case ARENA:
            for (variable_s1 = 0; variable_s1 < 10; variable_s1++) {
                funcion_8005DAD8(&jugador->pool_particula_3[variable_s1], 3, 1, 0x00A8);
                funcion_80062484(jugador, &jugador->pool_particula_3[variable_s1], variable_s1);
            }
            jugador->kart_props &= ~ACELERADOR_VUELCO_PUBLICAR;
            break;
        case ARENA_HUMEDO:
            for (variable_s1 = 0; variable_s1 < 10; variable_s1++) {
                funcion_8005DAD8(&jugador->pool_particula_3[variable_s1], 4, 1, 0x00A8);
                funcion_80062484(jugador, &jugador->pool_particula_3[variable_s1], variable_s1);
            }
            jugador->kart_props &= ~ACELERADOR_VUELCO_PUBLICAR;
            break;
        case FUERA_PISTA_TIERRA:
            for (variable_s1 = 0; variable_s1 < 10; variable_s1++) {
                funcion_8005DAD8(&jugador->pool_particula_3[variable_s1], 5, 1, 0x00A8);
                funcion_80062484(jugador, &jugador->pool_particula_3[variable_s1], variable_s1);
            }
            jugador->kart_props &= ~ACELERADOR_VUELCO_PUBLICAR;
            break;
        case NIEVE:
        case FUERA_PISTA_NIEVE:
            for (variable_s1 = 0; variable_s1 < 10; variable_s1++) {
                funcion_8005DAD8(&jugador->pool_particula_3[variable_s1], 6, 1, 0x00A8);
                funcion_80062484(jugador, &jugador->pool_particula_3[variable_s1], variable_s1);
            }
            jugador->kart_props &= ~ACELERADOR_VUELCO_PUBLICAR;
            break;
        case ASFALTO:
        case PIEDRA:
        case PUENTE:
            for (variable_s1 = 0; variable_s1 < 10; variable_s1++) {
                funcion_8005DAD8(&jugador->pool_particula_3[variable_s1], 0, 0, 0x00A8);
                funcion_80062484(jugador, &jugador->pool_particula_3[variable_s1], variable_s1);
            }
            jugador->kart_props &= ~ACELERADOR_VUELCO_PUBLICAR;
            break;
        default:
            for (variable_s1 = 0; variable_s1 < 10; variable_s1++) {
                funcion_8005DAD8(&jugador->pool_particula_3[variable_s1], 0, 0, 0x00A8);
                funcion_80062484(jugador, &jugador->pool_particula_3[variable_s1], variable_s1);
            }
            jugador->kart_props &= ~ACELERADOR_VUELCO_PUBLICAR;
            break;
    }
}

void funcion_800628C0(Jugador* jugador, SIN_USO s8 parametro1, SIN_USO s8 parametro2, s8 index) {
    jugador->pool_particula_2[index].vivo_es = 1;
    jugador->pool_particula_2[index].rotacion = -jugador->rotacion[1];
    jugador->pool_particula_2[index].type = 2;
    jugador->pool_particula_2[index].temporizador = 0;
    jugador->pool_particula_2[index].scale = 0.2f;
}

void funcion_80062914(Jugador* jugador, SIN_USO s8 parametro1, SIN_USO s8 parametro2, s8 index) {
    jugador->pool_particula_2[index].vivo_es = 1;
    jugador->pool_particula_2[index].rotacion = -jugador->rotacion[1];
    jugador->pool_particula_2[index].type = 4;
    jugador->pool_particula_2[index].temporizador = 0;
    jugador->pool_particula_2[index].scale = 1.0f;
}

void funcion_80062968(Jugador* jugador, SIN_USO s8 parametro1, SIN_USO s8 parametro2, s8 index) {
    jugador->pool_particula_2[index].vivo_es = 1;
    jugador->pool_particula_2[index].rotacion = -jugador->rotacion[1];
    jugador->pool_particula_2[index].type = 5;
    jugador->pool_particula_2[index].temporizador = 0;
    jugador->pool_particula_2[index].scale = 0.2f;
}

void funcion_800629BC(Jugador* jugador, SIN_USO s8 parametro1, SIN_USO s8 parametro2, s8 index) {
    jugador->pool_particula_2[index].vivo_es = 1;
    jugador->pool_particula_2[index].rotacion = -jugador->rotacion[1];
    jugador->pool_particula_2[index].type = 6;
    jugador->pool_particula_2[index].temporizador = 0;
    jugador->pool_particula_2[index].scale = 0.2f;
    jugador->pool_particula_2[index].pos[1] = 0.0f;
}

void funcion_80062A18(Jugador* jugador, s8 parametro1, SIN_USO s8 parametro2, s8 index) {
    jugador->pool_particula_2[index].vivo_es = 1;
    jugador->pool_particula_2[index].type = 3;
    jugador->pool_particula_2[parametro1 ].scale = 0.2f;
    jugador->pool_particula_2[index].temporizador = 1;
    jugador->pool_particula_2[index].rotacion = 0;
    jugador->graficos_kart &= ~WHIRRR;
    jugador->pool_particula_2[index].pos[2] = jugador->pos[2];
    jugador->pool_particula_2[index].pos[0] = jugador->pos[0];
    jugador->pool_particula_2[index].pos[1] = (jugador->pos[1] + 4.0f);
}

void funcion_80062AA8(Jugador* jugador, SIN_USO s8 parametro1, SIN_USO s8 parametro2, s8 index) {
    jugador->pool_particula_2[index].vivo_es = 1;
    jugador->pool_particula_2[index].type = 5;
    jugador->pool_particula_2[index].scale = 0.1f;
    jugador->pool_particula_2[index].temporizador = 0;
    jugador->pool_particula_2[index].pos[1] = (jugador->pos[1] + jugador->tamanio_caja_envolvente) - 2.5;
}

void funcion_80062B18(f32* parametro0, f32* parametro1, f32* parametro2, f32 parametro3, f32 parametro4, f32 parametro5, u16 parametro6, u16 parametro7) {
    SIN_USO f32 relleno;
    f32 sp30;
    f32 sp2_c;
    f32 sp28;
    f32 temporal_f20;

    sp28 = senos(parametro7);
    sp2_c = coss(parametro6);
    sp30 = coss(parametro7);
    temporal_f20 = coss(parametro6);
    *parametro0 = (((parametro3 * temporal_f20) * sp30) + (parametro4 * sp2_c) * sp28) - (senos(parametro6) * parametro5);

    temporal_f20 = senos(parametro7);
    *parametro1 = (coss(parametro7) * parametro4) - (parametro3 * temporal_f20);

    sp28 = senos(parametro7);
    sp2_c = senos(parametro6);
    sp30 = coss(parametro7);
    temporal_f20 = senos(parametro6);
    *parametro2 = (coss(parametro6) * parametro5) + (((parametro3 * temporal_f20) * sp30) + ((parametro4 * sp2_c) * sp28));
}

void funcion_80062C74(Jugador* jugador, s16 parametro1, SIN_USO s32 parametro2, SIN_USO s32 parametro3) {
    f32 sp48[8] = { 4.5f, 4.5f, 4.5f, 4.5f, 4.5f, 5.5f, 4.5f, 6.5f };
    f32 variable_f6;
    f32 sp40;
    f32 sp3_c;
    f32 sp38;
    s16 cosa;

    jugador->pool_particula_0[parametro1].temporizador++;
    if (jugador->pool_particula_0[parametro1].temporizador == 0x000C) {
        jugador->pool_particula_0[parametro1].vivo_es = 0;
        jugador->pool_particula_0[parametro1].temporizador = 0;
        jugador->pool_particula_0[parametro1].type = SIN_PARTICULA;
    }
    jugador->pool_particula_0[parametro1].desconocido_018 = 2.0f;
    if (jugador->pool_particula_0[parametro1].desconocido_040 == 0) {
        jugador->pool_particula_0[parametro1].scale = jugador->pool_particula_0[parametro1].scale + 0.07;
        jugador->pool_particula_0[parametro1].desconocido_024 = jugador->pool_particula_0[parametro1].desconocido_024 + 0.3;
        if (jugador->pool_particula_0[parametro1].temporizador >= 3) {
            jugador->pool_particula_0[parametro1].alpha -= 3;
        }
        if (jugador->pool_particula_0[parametro1].alpha <= 0) {
            jugador->pool_particula_0[parametro1].alpha = 0;
        }
    } else {
        jugador->pool_particula_0[parametro1].scale = jugador->pool_particula_0[parametro1].scale + 0.1;
        jugador->pool_particula_0[parametro1].desconocido_024 = jugador->pool_particula_0[parametro1].desconocido_024 + 0.3;
        if (jugador->pool_particula_0[parametro1].temporizador >= 3) {
            jugador->pool_particula_0[parametro1].alpha -= 2;
        }
        if (jugador->pool_particula_0[parametro1].alpha <= 0) {
            jugador->pool_particula_0[parametro1].alpha = 0;
        }
    }
    cosa = jugador->pool_particula_0[parametro1].rotacion - (jugador->desconocido_0C0 / 2);
    if (jugador->pool_particula_0[parametro1].desconocido_040 == 0) {
        variable_f6 = -((jugador->desconocido_098 / 5000.0f) + 0.1);
    } else {
        variable_f6 = -((jugador->desconocido_098 / 6000.0f) + 0.1);
    }
    if (((jugador->efectos & EFECTO_HONGO) == EFECTO_HONGO) && (jugador->pool_particula_0[parametro1].temporizador >= 6)) {
        jugador->pool_particula_0[parametro1].scale = jugador->pool_particula_0[parametro1].scale + 0.06;
    }
    jugador->pool_particula_0[parametro1].desconocido_010++;
    if (jugador->pool_particula_0[parametro1].desconocido_010 >= 3) {
        jugador->pool_particula_0[parametro1].desconocido_010 = 0;
    }
    funcion_80062B18(&sp40, &sp38, &sp3_c, 0.0f, sp48[jugador->id_personaje],
                  (jugador->pool_particula_0[parametro1].temporizador * variable_f6) + -5.5, -cosa, -jugador->desconocido_206 * 2);
    jugador->pool_particula_0[parametro1].pos[0] = jugador->pos[0] + sp40;
    sp38 = (jugador->pos[1] - jugador->tamanio_caja_envolvente) + sp38;
    jugador->pool_particula_0[parametro1].pos[2] = jugador->pos[2] + sp3_c;
    jugador->pool_particula_0[parametro1].pos[1] = jugador->pool_particula_0[parametro1].desconocido_024 + sp38;
}
