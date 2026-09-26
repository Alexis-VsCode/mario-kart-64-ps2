// Particulas derrape

void funcion_80062F98(Jugador* jugador, s16 parametro1, s8 parametro2, SIN_USO s8 parametro3) {
    f32 temporal_f0;

    temporal_f0 = jugador->pool_particula_1[parametro1].desconocido_018 / 10.0f;
    ++jugador->pool_particula_1[parametro1].temporizador;
    jugador->pool_particula_1[parametro1].pos[1] += temporal_f0;
    if ((jugador->lakitu_props & LAKITU_RECUPERACION) == LAKITU_RECUPERACION) {
        jugador->pool_particula_1[parametro1].pos[1] += (temporal_f0 + 0.3);
        if ((jugador->pool_particula_1[parametro1].temporizador == 0x10) ||
            ((dato_801652A0[parametro2] - jugador->pool_particula_1[parametro1].pos[1]) < 3.0f)) {
            jugador->pool_particula_1[parametro1].vivo_es = 0;
            jugador->pool_particula_1[parametro1].temporizador = 0;
            jugador->pool_particula_1[parametro1].type = SIN_PARTICULA;
        }
    } else if ((jugador->pool_particula_1[parametro1].temporizador == 0xA) ||
               ((dato_801652A0[parametro2] - jugador->pool_particula_1[parametro1].pos[1]) < 3.0f)) {
        jugador->pool_particula_1[parametro1].vivo_es = 0;
        jugador->pool_particula_1[parametro1].temporizador = 0;
        jugador->pool_particula_1[parametro1].type = SIN_PARTICULA;
    }
}

void fijar_oob_salpicadura_particula_posicion(Jugador* jugador, s16 parametro1, s8 parametro2, SIN_USO s8 parametro3) {
    ++jugador->pool_particula_0[parametro1].temporizador;
    jugador->pool_particula_0[parametro1].pos[2] = jugador->pos[2] + coss(jugador->pool_particula_0[parametro1].rotacion) * -5.8;
    jugador->pool_particula_0[parametro1].pos[0] = jugador->pos[0] + senos(jugador->pool_particula_0[parametro1].rotacion) * -5.8;
    jugador->pool_particula_0[parametro1].pos[1] = dato_801652A0[parametro2];
    if (jugador->pool_particula_0[parametro1].temporizador == 15) {
        jugador->pool_particula_0[parametro1].vivo_es = 0;
        jugador->pool_particula_0[parametro1].temporizador = 0;
        jugador->pool_particula_0[parametro1].type = SIN_PARTICULA;
    }
}

void funcion_800631A8(Jugador* jugador, s16 parametro1, SIN_USO s8 parametro2, SIN_USO s8 parametro3) {
    ++jugador->pool_particula_0[parametro1].temporizador;
    if ((s32) jugador->pool_particula_0[parametro1].temporizador < 9) {
        if ((jugador->pool_particula_0[parametro1].temporizador & 1) != 0) {
            jugador->pool_particula_0[parametro1].rojo = 8;
        } else {
            jugador->pool_particula_0[parametro1].rojo = 0;
        }
    } else if (((jugador->pool_particula_0[parametro1].temporizador & 1) != 0) ||
               ((jugador->pool_particula_0[parametro1].temporizador >= 9) && (jugador->pool_particula_0[parametro1].temporizador < 12))) {
        jugador->pool_particula_0[parametro1].rojo = 0xFF;
    } else if ((jugador->pool_particula_0[parametro1].temporizador & 2) != 0) {
        jugador->pool_particula_0[parametro1].rojo = 8;
    } else {
        jugador->pool_particula_0[parametro1].rojo = 0;
    }
    jugador->pool_particula_0[parametro1].verde = 0;
    jugador->pool_particula_0[parametro1].azul = 0;
    if ((s32) jugador->pool_particula_0[parametro1].temporizador >= 0x19) {
        jugador->pool_particula_0[parametro1].vivo_es = 0;
        jugador->pool_particula_0[parametro1].temporizador = 0;
        jugador->pool_particula_0[parametro1].type = SIN_PARTICULA;
    }
}

void funcion_80063268(Jugador* jugador, s16 parametro1, SIN_USO s8 parametro2, SIN_USO s8 parametro3) {
    if (jugador->pool_particula_0[parametro1].temporizador >= 0x1E) {
        jugador->pool_particula_0[parametro1].desconocido_040 += 0x1FFE;
    } else {
        jugador->pool_particula_0[parametro1].desconocido_040 += 0x1554;
    }

    jugador->pool_particula_0[parametro1].desconocido_024 += 0.25;
    jugador->pool_particula_0[parametro1].pos[2] =
        jugador->pos[2] + (coss((jugador->pool_particula_0[parametro1].rotacion + jugador->pool_particula_0[parametro1].desconocido_040)) * 5.5);
    jugador->pool_particula_0[parametro1].pos[0] =
        jugador->pos[0] + (senos((jugador->pool_particula_0[parametro1].rotacion + jugador->pool_particula_0[parametro1].desconocido_040)) * 5.5);
    jugador->pool_particula_0[parametro1].pos[1] = ((jugador->pos[1] - 5.0f) + jugador->pool_particula_0[parametro1].desconocido_024);
    ++jugador->pool_particula_0[parametro1].temporizador;
    jugador->pool_particula_0[parametro1].scale += 0.05;
    jugador->pool_particula_0[parametro1].alpha -= 5;

    if ((s32) jugador->pool_particula_0[parametro1].alpha <= 0) {
        jugador->pool_particula_0[parametro1].alpha = 0;
    }

    if ((s32) jugador->pool_particula_0[parametro1].temporizador >= 0x28) {
        jugador->pool_particula_0[parametro1].vivo_es = 0;
        jugador->pool_particula_0[parametro1].temporizador = 0;
        jugador->pool_particula_0[parametro1].type = SIN_PARTICULA;
    }
}

void funcion_80063408(Jugador* jugador, s16 parametro1, SIN_USO s8 parametro2, SIN_USO s8 parametro3) {
    if (jugador->pool_particula_1[parametro1].desconocido_010 == 1) {
        jugador->pool_particula_1[parametro1].pos[2] =
            jugador->ruedas[IZQUIERDA_ATRAS].pos[2] +
            (jugador->pool_particula_1[parametro1].temporizador * -7) * coss(jugador->pool_particula_1[parametro1].rotacion);
        jugador->pool_particula_1[parametro1].pos[0] =
            jugador->ruedas[IZQUIERDA_ATRAS].pos[0] +
            (jugador->pool_particula_1[parametro1].temporizador * -7) * senos(jugador->pool_particula_1[parametro1].rotacion);
    } else {
        jugador->pool_particula_1[parametro1].pos[2] =
            jugador->ruedas[DERECHA_ATRAS].pos[2] +
            (jugador->pool_particula_1[parametro1].temporizador * -7) * coss(jugador->pool_particula_1[parametro1].rotacion);
        jugador->pool_particula_1[parametro1].pos[0] =
            jugador->ruedas[DERECHA_ATRAS].pos[0] +
            (jugador->pool_particula_1[parametro1].temporizador * -7) * senos(jugador->pool_particula_1[parametro1].rotacion);
    }

    ++jugador->pool_particula_1[parametro1].temporizador;
    jugador->pool_particula_1[parametro1].pos[1] += 1.0f;

    if (((jugador->efectos & EFECTO_TROMPO_BANANA) != 0) || ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) != 0)) {
        jugador->pool_particula_1[parametro1].vivo_es = 0;
        jugador->pool_particula_1[parametro1].temporizador = 0;
    }

    if (jugador->pool_particula_1[parametro1].temporizador == 8) {
        jugador->pool_particula_1[parametro1].temporizador = 0;
        jugador->pool_particula_1[parametro1].vivo_es = 0;
        jugador->pool_particula_1[parametro1].type = SIN_PARTICULA;
    }

    jugador->pool_particula_1[parametro1].scale += 0.08;
    if (jugador->pool_particula_1[parametro1].temporizador >= 4) {
        jugador->pool_particula_1[parametro1].alpha -= 16;
    }

    if (jugador->pool_particula_1[parametro1].alpha <= 0) {
        jugador->pool_particula_1[parametro1].alpha = 0;
    }
}

void funcion_800635D4(Jugador* jugador, s16 parametro1, SIN_USO s8 parametro2, SIN_USO s8 parametro3) {
    f32 sp44;
    f32 sp40;
    f32 sp3_c;

    if (jugador->pool_particula_1[parametro1].desconocido_010 == 1) {
        if ((jugador->efectos & EFECTO_RAYO)) {
            funcion_80062B18(&sp44, &sp40, &sp3_c, -2.0f, 0.0f,
                          (-jugador->pool_particula_1[parametro1].temporizador * (jugador->speed / 18.0f) * 216.0f) / 16,
                          -jugador->pool_particula_1[parametro1].rotacion, 2 * -jugador->desconocido_206);
            jugador->pool_particula_1[parametro1].pos[0] = jugador->ruedas[IZQUIERDA_ATRAS].pos[0] + sp44;
            jugador->pool_particula_1[parametro1].pos[2] = jugador->ruedas[IZQUIERDA_ATRAS].pos[2] + sp3_c;
        } else {
            jugador->pool_particula_1[parametro1].pos[2] =
                jugador->ruedas[IZQUIERDA_ATRAS].pos[2] +
                ((-jugador->pool_particula_1[parametro1].temporizador * (jugador->speed / 18.0f) * 216.0f) / 16) *
                    coss(jugador->pool_particula_1[parametro1].rotacion);
            jugador->pool_particula_1[parametro1].pos[0] =
                jugador->ruedas[IZQUIERDA_ATRAS].pos[0] +
                ((-jugador->pool_particula_1[parametro1].temporizador * (jugador->speed / 18.0f) * 216.0f) / 16) *
                    senos(jugador->pool_particula_1[parametro1].rotacion);
        }
    } else if ((jugador->efectos & EFECTO_RAYO)) {
        funcion_80062B18(&sp44, &sp40, &sp3_c, 2.0f, 0.0f,
                      (-jugador->pool_particula_1[parametro1].temporizador * (jugador->speed / 18.0f) * 216.0f) / 16,
                      -jugador->pool_particula_1[parametro1].rotacion, 2 * -jugador->desconocido_206);
        jugador->pool_particula_1[parametro1].pos[0] = jugador->ruedas[DERECHA_ATRAS].pos[0] + sp44;
        jugador->pool_particula_1[parametro1].pos[2] = jugador->ruedas[DERECHA_ATRAS].pos[2] + sp3_c;
    } else {
        jugador->pool_particula_1[parametro1].pos[2] =
            jugador->ruedas[DERECHA_ATRAS].pos[2] +
            ((-jugador->pool_particula_1[parametro1].temporizador * (jugador->speed / 18.0f) * 216.0f) / 16) *
                coss(jugador->pool_particula_1[parametro1].rotacion);
        jugador->pool_particula_1[parametro1].pos[0] =
            jugador->ruedas[DERECHA_ATRAS].pos[0] +
            ((-jugador->pool_particula_1[parametro1].temporizador * (jugador->speed / 18.0f) * 216.0f) / 16) *
                senos(jugador->pool_particula_1[parametro1].rotacion);
    }

    ++jugador->pool_particula_1[parametro1].temporizador;
    jugador->pool_particula_1[parametro1].pos[1] += 0.2;
    if (((jugador->efectos & EFECTO_TROMPO_BANANA) != 0) || ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) != 0)) {
        jugador->pool_particula_1[parametro1].vivo_es = 0;
        jugador->pool_particula_1[parametro1].temporizador = 0;
    }

    if (jugador->pool_particula_1[parametro1].temporizador == 8) {
        jugador->pool_particula_1[parametro1].vivo_es = 0;
        jugador->pool_particula_1[parametro1].temporizador = 0;
        jugador->pool_particula_1[parametro1].type = SIN_PARTICULA;
    }

    jugador->pool_particula_1[parametro1].scale += 0.1;
    if (jugador->pool_particula_1[parametro1].desconocido_040 == 0) {
        if (jugador->pool_particula_1[parametro1].temporizador >= 4) {
            jugador->pool_particula_1[parametro1].alpha -= 12;
        }
        if (jugador->pool_particula_1[parametro1].alpha <= 0) {
            jugador->pool_particula_1[parametro1].alpha = 0;
        }
    } else {
        if (jugador->pool_particula_1[parametro1].temporizador >= 4) {
            jugador->pool_particula_1[parametro1].alpha -= 16;
        }
        if (jugador->pool_particula_1[parametro1].alpha <= 0) {
            jugador->pool_particula_1[parametro1].alpha = 0;
        }
    }
}

void funcion_800639DC(Jugador* jugador, s16 parametro1, SIN_USO s8 parametro2, SIN_USO s8 parametro3) {
    if (jugador->pool_particula_1[parametro1].desconocido_010 == 1) {
        jugador->pool_particula_1[parametro1].pos[2] =
            jugador->ruedas[IZQUIERDA_ATRAS].pos[2] +
            (-1.8f * jugador->pool_particula_1[parametro1].temporizador) * coss(jugador->pool_particula_1[parametro1].rotacion);
        jugador->pool_particula_1[parametro1].pos[0] =
            jugador->ruedas[IZQUIERDA_ATRAS].pos[0] +
            (-1.8f * jugador->pool_particula_1[parametro1].temporizador) * senos(jugador->pool_particula_1[parametro1].rotacion);
    } else {
        jugador->pool_particula_1[parametro1].pos[2] =
            jugador->ruedas[DERECHA_ATRAS].pos[2] +
            (-1.8f * jugador->pool_particula_1[parametro1].temporizador) * coss(jugador->pool_particula_1[parametro1].rotacion);
        jugador->pool_particula_1[parametro1].pos[0] =
            jugador->ruedas[DERECHA_ATRAS].pos[0] +
            (-1.8f * jugador->pool_particula_1[parametro1].temporizador) * senos(jugador->pool_particula_1[parametro1].rotacion);
    }
    ++jugador->pool_particula_1[parametro1].temporizador;
    jugador->pool_particula_1[parametro1].pos[1] += 0.3;
    if (jugador->pool_particula_1[parametro1].temporizador == 8) {
        jugador->pool_particula_1[parametro1].vivo_es = 0;
        jugador->pool_particula_1[parametro1].temporizador = 0;
        jugador->pool_particula_1[parametro1].type = SIN_PARTICULA;
    }

    jugador->pool_particula_1[parametro1].scale += 0.15;
    if (jugador->pool_particula_1[parametro1].desconocido_040 == 0) {
        if ((s32) jugador->pool_particula_1[parametro1].temporizador >= 4) {
            --jugador->pool_particula_1[parametro1].alpha;
        }
        if ((s32) jugador->pool_particula_1[parametro1].alpha <= 0) {
            jugador->pool_particula_1[parametro1].alpha = 0;
        }
    } else {
        if ((s32) jugador->pool_particula_1[parametro1].temporizador >= 4) {
            jugador->pool_particula_1[parametro1].alpha -= 16;
        }
        if ((s32) jugador->pool_particula_1[parametro1].alpha <= 0) {

            jugador->pool_particula_1[parametro1].alpha = 0;
        }
    }
}

void funcion_80063BD4(Jugador* jugador, s16 parametro1, SIN_USO s8 parametro2, SIN_USO s8 parametro3) {
    if (jugador->pool_particula_1[parametro1].desconocido_010 == 1) {
        jugador->pool_particula_1[parametro1].pos[2] =
            jugador->ruedas[IZQUIERDA_ATRAS].pos[2] +
            (-2 * jugador->pool_particula_1[parametro1].temporizador * coss(jugador->pool_particula_1[parametro1].rotacion));
        jugador->pool_particula_1[parametro1].pos[0] =
            jugador->ruedas[IZQUIERDA_ATRAS].pos[0] +
            (-2 * jugador->pool_particula_1[parametro1].temporizador * senos(jugador->pool_particula_1[parametro1].rotacion));
    } else {
        jugador->pool_particula_1[parametro1].pos[2] =
            jugador->ruedas[DERECHA_ATRAS].pos[2] +
            (-2 * jugador->pool_particula_1[parametro1].temporizador * coss(jugador->pool_particula_1[parametro1].rotacion));
        jugador->pool_particula_1[parametro1].pos[0] =
            jugador->ruedas[DERECHA_ATRAS].pos[0] +
            (-2 * jugador->pool_particula_1[parametro1].temporizador * senos(jugador->pool_particula_1[parametro1].rotacion));
    }

    ++jugador->pool_particula_1[parametro1].temporizador;
    jugador->pool_particula_1[parametro1].pos[1] += 0.2;
    if (jugador->pool_particula_1[parametro1].temporizador == 8) {
        jugador->pool_particula_1[parametro1].vivo_es = 0;
        jugador->pool_particula_1[parametro1].temporizador = 0;
        jugador->pool_particula_1[parametro1].type = SIN_PARTICULA;
    }

    jugador->pool_particula_1[parametro1].desconocido_018 = 2.0f;
    jugador->pool_particula_1[parametro1].scale -= 0.06;
}

void funcion_80063D58(Jugador* jugador, s16 parametro1, SIN_USO s8 parametro2, SIN_USO s8 parametro3) {
    if (jugador->pool_particula_1[parametro1].desconocido_010 == 1) {
        jugador->pool_particula_1[parametro1].pos[2] =
            jugador->ruedas[IZQUIERDA_ATRAS].pos[2] +
            ((-jugador->pool_particula_1[parametro1].temporizador * (jugador->speed / 18.0f) * 216.0f) / 20.0f) *
                coss(jugador->pool_particula_1[parametro1].rotacion);
        jugador->pool_particula_1[parametro1].pos[0] =
            jugador->ruedas[IZQUIERDA_ATRAS].pos[0] +
            ((-jugador->pool_particula_1[parametro1].temporizador * (jugador->speed / 18.0f) * 216.0f) / 20.0f) *
                senos(jugador->pool_particula_1[parametro1].rotacion);
    } else {
        jugador->pool_particula_1[parametro1].pos[2] =
            jugador->ruedas[DERECHA_ATRAS].pos[2] +
            ((-jugador->pool_particula_1[parametro1].temporizador * (jugador->speed / 18.0f) * 216.0f) / 20.0f) *
                coss(jugador->pool_particula_1[parametro1].rotacion);
        jugador->pool_particula_1[parametro1].pos[0] =
            jugador->ruedas[DERECHA_ATRAS].pos[0] +
            ((-jugador->pool_particula_1[parametro1].temporizador * (jugador->speed / 18.0f) * 216.0f) / 20.0f) *
                senos(jugador->pool_particula_1[parametro1].rotacion);
    }

    ++jugador->pool_particula_1[parametro1].temporizador;
    if (jugador->pool_particula_1[parametro1].temporizador == 8) {
        jugador->pool_particula_1[parametro1].temporizador = 0;
        jugador->pool_particula_1[parametro1].vivo_es = 0;
        jugador->pool_particula_1[parametro1].type = SIN_PARTICULA;
    }

    jugador->pool_particula_1[parametro1].scale += 0.2;
    if (jugador->pool_particula_1[parametro1].temporizador >= 4) {
        jugador->pool_particula_1[parametro1].alpha -= 18;
        jugador->pool_particula_1[parametro1].pos[1] -= 0.1;
    } else {
        jugador->pool_particula_1[parametro1].pos[1] += 0.4;
    }

    if (jugador->pool_particula_1[parametro1].alpha <= 0) {
        jugador->pool_particula_1[parametro1].alpha = 0;
    }
}

void funcion_80063FBC(Jugador* jugador, s16 parametro1, SIN_USO s32 parametro2, SIN_USO s32 parametro3) {
    f32 sp3_c;
    f32 sp38;
    f32 sp34;

    if (jugador->pool_particula_1[parametro1].desconocido_010 == 1) {
        funcion_80062B18(&sp3_c, &sp34, &sp38, 3.0f, 0.0f,
                      -5.5 - (jugador->pool_particula_1[parametro1].temporizador * (((jugador->speed / 18.0f) * 216.0f) / 15.0f)),
                      -jugador->pool_particula_1[parametro1].rotacion, 0);
    } else {
        funcion_80062B18(&sp3_c, &sp34, &sp38, -3.0f, 0.0f,
                      -5.5 - (jugador->pool_particula_1[parametro1].temporizador * (((jugador->speed / 18.0f) * 216.0f) / 15.0f)),
                      -jugador->pool_particula_1[parametro1].rotacion, 0);
    }
    jugador->pool_particula_1[parametro1].pos[0] = jugador->pos[0] + sp3_c;
    jugador->pool_particula_1[parametro1].pos[2] = jugador->pos[2] + sp38;
    jugador->pool_particula_1[parametro1].pos[1] = (jugador->pos[1] - jugador->tamanio_caja_envolvente) + sp34;
    jugador->pool_particula_1[parametro1].temporizador++;
    if (jugador->pool_particula_1[parametro1].temporizador == 6) {
        jugador->pool_particula_1[parametro1].vivo_es = 0;
        jugador->pool_particula_1[parametro1].temporizador = 0;
        jugador->pool_particula_1[parametro1].type = SIN_PARTICULA;
    }
}

void funcion_80064184(Jugador* jugador, s16 parametro1, s8 parametro2, SIN_USO s8 parametro3) {
    f32 sp44;
    f32 sp40;
    f32 sp3_c;

    sp40 = dato_801652A0[parametro2] - jugador->pos[1] - 3.0f;
    if (((jugador->oob_props & BAJO_OOB_O_NIVEL_FLUIDO) != 0) && (id_circuito_actual != CIRCUITO_KOOPA_BEACH)) {
        sp40 = dato_801652A0[parametro2] - jugador->pos[1] + 0.1;
    }

    funcion_80062B18(&sp44, &sp40, &sp3_c, 0.0f, sp40,
                  -4.0f + ((-jugador->pool_particula_0[parametro1].temporizador * (jugador->speed / 18.0f) * 216.0f) / 10.0f),
                  -jugador->pool_particula_0[parametro1].rotacion, 2 * -jugador->desconocido_206);
    jugador->pool_particula_0[parametro1].pos[0] = jugador->pos[0] + sp44;
    jugador->pool_particula_0[parametro1].pos[2] = jugador->pos[2] + sp3_c;
    jugador->pool_particula_0[parametro1].pos[1] = jugador->pos[1] + sp40;
    ++jugador->pool_particula_0[parametro1].temporizador;
    if ((jugador->pool_particula_0[parametro1].temporizador == 12) || (dato_801652A0[parametro2] <= (jugador->pos[1] - jugador->tamanio_caja_envolvente))) {
        jugador->pool_particula_0[parametro1].vivo_es = 0;
        jugador->pool_particula_0[parametro1].temporizador = 0;
        jugador->pool_particula_0[parametro1].type = SIN_PARTICULA;
    }
    jugador->pool_particula_0[parametro1].desconocido_018 = 2.0f;
    jugador->pool_particula_0[parametro1].scale -= 0.35;
    if (jugador->pool_particula_0[parametro1].scale < 0.0f) {
        jugador->pool_particula_0[parametro1].scale = 0.0f;
    }

    jugador->pool_particula_0[parametro1].alpha -= 22;
    if (jugador->pool_particula_0[parametro1].alpha <= 0) {
        jugador->pool_particula_0[parametro1].alpha = 0;
    }
}

void funcion_800643A8(Jugador* jugador, s16 parametro1, SIN_USO s8 parametro2, SIN_USO s8 parametro3) {
    jugador->pool_particula_1[parametro1].pos[2] =
        jugador->pos[2] + (-1.2 * jugador->pool_particula_1[parametro1].temporizador * coss(jugador->pool_particula_1[parametro1].rotacion));
    jugador->pool_particula_1[parametro1].pos[0] =
        jugador->pos[0] + (-1.2 * jugador->pool_particula_1[parametro1].temporizador * senos(jugador->pool_particula_1[parametro1].rotacion));
    jugador->pool_particula_1[parametro1].pos[1] = jugador->pool_particula_1[parametro1].pos[1] + 0.5;

    ++jugador->pool_particula_1[parametro1].temporizador;
    if (jugador->pool_particula_1[parametro1].temporizador == 10) {
        jugador->pool_particula_1[parametro1].vivo_es = 0;
        jugador->pool_particula_1[parametro1].temporizador = 0;
        jugador->pool_particula_1[parametro1].type = SIN_PARTICULA;
    }

    jugador->pool_particula_1[parametro1].scale += 0.2;
    jugador->pool_particula_1[parametro1].alpha -= 8;
    if (jugador->pool_particula_1[parametro1].alpha <= 0) {
        jugador->pool_particula_1[parametro1].alpha = 0;
    }
}

void funcion_800644E8(Jugador* jugador, s16 parametro1, SIN_USO s8 parametro2, SIN_USO s8 parametro3) {
    f32 cosa2;
    SIN_USO s32 margen_pila_0;
    s32 cosa;
    SIN_USO s32 margen_pila_1;

    if (jugador->pool_particula_3[parametro1].temporizador >= 9) {
        jugador->pool_particula_3[parametro1].temporizador = 9;
    }
    cosa2 = jugador->pool_particula_3[parametro1].desconocido_024;
    cosa = jugador->pool_particula_3[parametro1].temporizador;
    jugador->pool_particula_3[parametro1].pos[2] = jugador->pos[2] + (coss(jugador->pool_particula_3[parametro1].rotacion) * (-0.7 * cosa));
    jugador->pool_particula_3[parametro1].pos[0] = jugador->pos[0] + (senos(jugador->pool_particula_3[parametro1].rotacion) * (-0.7 * cosa));
    jugador->pool_particula_3[parametro1].temporizador++;
    jugador->pool_particula_3[parametro1].pos[1] =
        jugador->pool_particula_3[parametro1].desconocido_028 + (f32) ((cosa * cosa2) - (0.2 * (cosa * cosa)));
    if (jugador->pool_particula_3[parametro1].temporizador == 0x000A) {
        jugador->pool_particula_3[parametro1].temporizador = 0;
        jugador->pool_particula_3[parametro1].vivo_es = 0;
        jugador->pool_particula_3[parametro1].type = SIN_PARTICULA;
    }
    if (jugador->pool_particula_3[parametro1].temporizador >= 7) {
        jugador->pool_particula_3[parametro1].alpha -= 0x60;
        if (jugador->pool_particula_3[parametro1].alpha <= 0) {
            jugador->pool_particula_3[parametro1].alpha = 0;
        }
    }
}

void funcion_80064664(Jugador* jugador, s16 parametro1, SIN_USO s8 parametro2, SIN_USO s8 parametro3) {
    f32 temporal_f4;
    SIN_USO s32 margen_pila_0;
    s32 temporal_v1;
    SIN_USO s32 margen_pila_1;

    temporal_v1 = jugador->pool_particula_3[parametro1].temporizador;
    temporal_f4 = jugador->pool_particula_3[parametro1].desconocido_024;
    jugador->pool_particula_3[parametro1].pos[2] =
        jugador->pos[2] + (coss(jugador->pool_particula_3[parametro1].rotacion) * (-0.6 * temporal_v1));
    jugador->pool_particula_3[parametro1].pos[0] =
        jugador->pos[0] + (senos(jugador->pool_particula_3[parametro1].rotacion) * (-0.6 * temporal_v1));
    jugador->pool_particula_3[parametro1].temporizador++;
    jugador->pool_particula_3[parametro1].pos[1] =
        jugador->pool_particula_3[parametro1].desconocido_028 + (f32) ((temporal_v1 * temporal_f4) - (0.1 * (temporal_v1 * temporal_v1)));
    if (jugador->pool_particula_3[parametro1].temporizador == 0x0019) {
        jugador->pool_particula_3[parametro1].temporizador = 0;
        jugador->pool_particula_3[parametro1].vivo_es = 0;
        jugador->pool_particula_3[parametro1].type = SIN_PARTICULA;
    }
    if (jugador->pool_particula_3[parametro1].temporizador >= 7) {
        jugador->pool_particula_3[parametro1].alpha -= 0x6;
        if (jugador->pool_particula_3[parametro1].alpha <= 0) {
            jugador->pool_particula_3[parametro1].alpha = 0;
        }
    }
}

void funcion_800647C8(Jugador* jugador, s16 parametro1, SIN_USO s8 parametro2, SIN_USO s8 parametro3) {

    ++jugador->pool_particula_3[parametro1].temporizador;
    jugador->pool_particula_3[parametro1].pos[2] =
        jugador->pos[2] + ((-0.8 * (jugador->pool_particula_3[parametro1].temporizador)) * coss(jugador->pool_particula_3[parametro1].rotacion));
    jugador->pool_particula_3[parametro1].pos[0] =
        jugador->pos[0] + ((-0.8 * (jugador->pool_particula_3[parametro1].temporizador)) * senos(jugador->pool_particula_3[parametro1].rotacion));
    jugador->pool_particula_3[parametro1].pos[1] = (jugador->desconocido_074 + 2.0f);

    if (jugador->pool_particula_3[parametro1].temporizador == 14) {
        jugador->pool_particula_3[parametro1].vivo_es = 0;
        jugador->pool_particula_3[parametro1].temporizador = 0;
        jugador->pool_particula_3[parametro1].type = SIN_PARTICULA;
    }

    jugador->pool_particula_3[parametro1].alpha -= 12;
    if (jugador->pool_particula_3[parametro1].alpha <= 0) {
        jugador->pool_particula_3[parametro1].alpha = 0;
    }
}

void funcion_800648E4(Jugador* jugador, s16 parametro1, SIN_USO s8 parametro2, SIN_USO s8 parametro3) {
    ++jugador->pool_particula_3[parametro1].temporizador;
    jugador->pool_particula_3[parametro1].scale -= 0.06;
    jugador->pool_particula_3[parametro1].pos[1] += 0.1;
    jugador->pool_particula_3[parametro1].alpha -= 12;

    if (jugador->pool_particula_3[parametro1].alpha <= 0) {
        jugador->pool_particula_3[parametro1].alpha = 0;
    }

    if (jugador->pool_particula_3[parametro1].temporizador == 10) {
        jugador->pool_particula_3[parametro1].vivo_es = 0;
        jugador->pool_particula_3[parametro1].temporizador = 0;
        jugador->pool_particula_3[parametro1].type = SIN_PARTICULA;
    }
}

void funcion_80064988(Jugador* jugador, s16 parametro1, SIN_USO s8 parametro2, SIN_USO s8 parametro3) {
    ++jugador->pool_particula_3[parametro1].temporizador;
    jugador->pool_particula_3[parametro1].pos[1] -= 0.3;

    if (jugador->pool_particula_3[parametro1].temporizador == 10) {
        jugador->pool_particula_3[parametro1].vivo_es = 0;
        jugador->pool_particula_3[parametro1].temporizador = 0;
        jugador->pool_particula_3[parametro1].type = SIN_PARTICULA;
    }
}

void funcion_800649F4(Jugador* jugador, s16 parametro1, SIN_USO s8 parametro2, SIN_USO s8 parametro3) {
    f32 temporal_;
    temporal_ = jugador->pool_particula_3[parametro1].desconocido_018;

    jugador->pool_particula_3[parametro1].pos[2] =
        jugador->desconocido_21C + (((-temporal_) * jugador->pool_particula_3[parametro1].temporizador) * coss(jugador->pool_particula_3[parametro1].rotacion));
    jugador->pool_particula_3[parametro1].pos[0] =
        jugador->desconocido_218 + (((-temporal_) * jugador->pool_particula_3[parametro1].temporizador) * senos(jugador->pool_particula_3[parametro1].rotacion));
    jugador->pool_particula_3[parametro1].pos[1] = jugador->pos[1] + jugador->pool_particula_3[parametro1].tipo_superficie;
    jugador->pool_particula_3[parametro1].scale += 0.04;

    ++jugador->pool_particula_3[parametro1].temporizador;
    if (jugador->pool_particula_3[parametro1].temporizador == 12) {
        jugador->pool_particula_3[parametro1].temporizador = 0;
        jugador->pool_particula_3[parametro1].vivo_es = 0;
        jugador->pool_particula_3[parametro1].type = SIN_PARTICULA;
    }

    if (jugador->pool_particula_3[parametro1].temporizador >= 9) {
        jugador->pool_particula_3[parametro1].alpha -= 0x10;
        if (jugador->pool_particula_3[parametro1].alpha <= 0) {
            jugador->pool_particula_3[parametro1].alpha = 0;
        }
    }
}

void funcion_80064B30(Jugador* jugador, s16 parametro1, SIN_USO s8 parametro2, SIN_USO s8 parametro3) {
    f32 temporal_;
    temporal_ = jugador->pool_particula_3[parametro1].desconocido_018 * 1.2;

    jugador->pool_particula_3[parametro1].pos[2] =
        (jugador->pos[2] + (-temporal_ * jugador->pool_particula_3[parametro1].temporizador) * (coss(jugador->pool_particula_3[parametro1].rotacion)));
    jugador->pool_particula_3[parametro1].pos[0] =
        (jugador->pos[0] + (-temporal_ * jugador->pool_particula_3[parametro1].temporizador) * (senos(jugador->pool_particula_3[parametro1].rotacion)));
    jugador->pool_particula_3[parametro1].pos[1] += 0.1;

    ++jugador->pool_particula_3[parametro1].temporizador;
    if (jugador->pool_particula_3[parametro1].temporizador == 10) {
        jugador->pool_particula_3[parametro1].temporizador = 0;
        jugador->pool_particula_3[parametro1].vivo_es = 0;
        jugador->pool_particula_3[parametro1].type = SIN_PARTICULA;
    }

    jugador->pool_particula_3[parametro1].rojo += GRADOS(10);
    if (jugador->pool_particula_3[parametro1].temporizador >= 6) {
        jugador->pool_particula_3[parametro1].alpha -= 16;
        if (jugador->pool_particula_3[parametro1].alpha <= 0) {
            jugador->pool_particula_3[parametro1].alpha = 0;
        }
    }
}

void funcion_80064C74(Jugador* jugador, s16 parametro1, SIN_USO s8 parametro2, SIN_USO s8 parametro3) {

    if (jugador->pool_particula_3[parametro1].desconocido_010 == 1) {
        jugador->pool_particula_3[parametro1].rotacion += GRADOS(12);
    } else {
        jugador->pool_particula_3[parametro1].rotacion -= GRADOS(12);
    }

    jugador->pool_particula_3[parametro1].pos[2] =
        jugador->pos[2] + (coss(jugador->pool_particula_3[parametro1].rotacion - jugador->rotacion[1] - jugador->desconocido_0C0) * 5.0f);
    jugador->pool_particula_3[parametro1].pos[0] =
        jugador->pos[0] + (senos(jugador->pool_particula_3[parametro1].rotacion - jugador->rotacion[1] - jugador->desconocido_0C0) * 5.0f);
    jugador->pool_particula_3[parametro1].pos[1] = jugador->pos[1] - 1.0f;
    jugador->pool_particula_3[parametro1].scale += 0.4;
    ++jugador->pool_particula_3[parametro1].temporizador;

    if (jugador->pool_particula_3[parametro1].temporizador == 10) {
        jugador->pool_particula_3[parametro1].temporizador = 0;
        jugador->pool_particula_3[parametro1].vivo_es = 0;
        jugador->pool_particula_3[parametro1].type = SIN_PARTICULA;
    }
    if (jugador->pool_particula_3[parametro1].temporizador >= 5) {
        jugador->pool_particula_3[parametro1].alpha -= 20;
        if (jugador->pool_particula_3[parametro1].alpha <= 0) {
            jugador->pool_particula_3[parametro1].alpha = 0;
        }
    }
}

void funcion_80064DEC(Jugador* jugador, SIN_USO s8 parametro1, SIN_USO s8 parametro2, s8 index) {

    jugador->pool_particula_2[index].pos[1] = jugador->pos[1];
    ++jugador->pool_particula_2[index].temporizador;

    if (jugador->pool_particula_2[index].temporizador == 9) {
        jugador->graficos_kart &= ~ERROR_;
        jugador->pool_particula_2[index].vivo_es = 0;
        jugador->pool_particula_2[index].temporizador = 0;
        jugador->pool_particula_2[index].type = SIN_PARTICULA;
    }

    jugador->pool_particula_2[index].scale += 0.8;
    if (jugador->pool_particula_2[index].scale >= (f64) 2.5) {
        jugador->pool_particula_2[index].scale = 2.5f;
    }
}

void funcion_80064EA4(Jugador* jugador, SIN_USO s8 parametro1, SIN_USO s8 parametro2, s8 index) {
    ++jugador->pool_particula_2[index].temporizador;
    if (jugador->pool_particula_2[index].temporizador < 4) {
        jugador->pool_particula_2[index].scale += 1.2;
        if (jugador->pool_particula_2[index].scale >= 3.5) {
            jugador->pool_particula_2[index].scale = 3.5f;
        }
    } else {
        jugador->pool_particula_2[index].scale -= 1.8;
        if (jugador->pool_particula_2[index].scale <= 0.0f) {
            jugador->graficos_kart &= ~EXPLOSION;
            jugador->pool_particula_2[index].vivo_es = 0;
            jugador->pool_particula_2[index].temporizador = 0;
            jugador->pool_particula_2[index].type = SIN_PARTICULA;
        }
    }
}

void funcion_80064F88(Jugador* jugador, SIN_USO s8 parametro1, SIN_USO s8 parametro2, s8 index) {
    ++jugador->pool_particula_2[index].temporizador;
    jugador->pool_particula_2[index].scale += 0.15;

    if (1.2 <= jugador->pool_particula_2[index].scale) {
        jugador->pool_particula_2[index].scale = 1.2f;
    }
    if (jugador->pool_particula_2[index].temporizador >= 12) {
        jugador->graficos_kart &= ~BOING;
        jugador->pool_particula_2[index].vivo_es = 0;
        jugador->pool_particula_2[index].temporizador = 0;
        jugador->pool_particula_2[index].type = SIN_PARTICULA;
    }
}

void funcion_80065030(Jugador* jugador, SIN_USO s8 parametro1, SIN_USO s8 parametro2, s8 index) {
    ++jugador->pool_particula_2[index].temporizador;

    jugador->pool_particula_2[index].pos[1] += 0.8;
    jugador->pool_particula_2[index].scale += 0.4;
    if (jugador->pool_particula_2[index].scale >= (f64) 1.5) {
        jugador->pool_particula_2[index].scale = 1.5f;
    }

    if (jugador->pool_particula_2[index].temporizador >= 12) {
        jugador->graficos_kart &= ~POOMP;
        jugador->pool_particula_2[index].vivo_es = 0;
        jugador->pool_particula_2[index].temporizador = 0;
        jugador->pool_particula_2[index].type = SIN_PARTICULA;
    }
}

void funcion_800650FC(Jugador* jugador, SIN_USO s8 parametro1, SIN_USO s8 parametro2, s8 index) {
    jugador->pool_particula_2[index].pos[2] = (f32) jugador->pos[2];
    jugador->pool_particula_2[index].pos[0] = (f32) jugador->pos[0];
    jugador->pool_particula_2[index].pos[1] = (f32) (jugador->pos[1] + 4.0f);
    if ((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) {
        jugador->pool_particula_2[index].rotacion += 26 * GRADOS(1);
    } else {
        jugador->pool_particula_2[index].rotacion -= 26 * GRADOS(1);
    }

    if (((jugador->efectos & EFECTO_TROMPO_BANANA) != EFECTO_TROMPO_BANANA) &&
        ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) != EFECTO_TROMPO_CONDUCIENDO)) {
        jugador->pool_particula_2[index].vivo_es = 0;
        jugador->pool_particula_2[index].temporizador = 0;
        jugador->pool_particula_2[index].type = SIN_PARTICULA;
    }

    jugador->pool_particula_2[index].scale += 0.08;
    if (jugador->pool_particula_2[index].scale >= 1.5) {
        jugador->pool_particula_2[index].scale = 1.5f;
    }
}

void funcion_800651F4(Jugador* jugador, SIN_USO s8 parametro1, SIN_USO s8 parametro2, s8 index) {
    ++jugador->pool_particula_2[index].temporizador;
    if (jugador->pool_particula_2[index].temporizador < 8) {
        jugador->pool_particula_2[index].scale += 0.2;
        if (1.2 <= jugador->pool_particula_2[index].scale) {
            jugador->pool_particula_2[index].scale = 1.2f;
        }
    } else {
        jugador->pool_particula_2[index].scale -= 0.4;
        if (jugador->pool_particula_2[index].scale <= 0.0f) {
            jugador->graficos_kart &= ~SILBATO;
            jugador->pool_particula_2[index].vivo_es = 0;
            jugador->pool_particula_2[index].temporizador = 0;
            jugador->pool_particula_2[index].type = SIN_PARTICULA;
        }
    }
}

void funcion_800652D4(Vec3f parametro0, Vec3s parametro1, f32 escalar) {
    Mat4 sp20;

    trasladar_rotacion_mtxf(sp20, parametro0, parametro1);
    escala2_mtxf(sp20, escalar);
    convertir_a_matriz_punto_fijo(&gfx_pool->efecto_mtx[cantidad_efecto_matriz], sp20);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->efecto_mtx[cantidad_efecto_matriz]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}

void funcion_8006538C(Jugador* jugador, s8 indice_jugador, s16 parametro2, s8 parametro3) {
    Vec3f sp_b4;
    Vec3s sp_ac;
    s32 colores_prim[] = { HACER_RGB(0xFB, 0xFF, 0xFB), HACER_RGB(0xFF, 0xFB, 0x86) };
    s32 colores_amb[] = { HACER_RGB(0x89, 0x62, 0x8F), HACER_RGB(0xFE, 0x01, 0x09) };
    s16 prim_rojo;
    s16 verde_prim;
    s16 azul_prim;
    s16 prim_alpha;
    s16 amb_rojo;
    s16 verde_amb;
    s16 azul_amb;

    if (jugador->pool_particula_0[parametro2].vivo_es == 1) {
        sp_b4[0] = jugador->pool_particula_0[parametro2].pos[0];
        sp_b4[1] = jugador->pool_particula_0[parametro2].pos[1];
        sp_b4[2] = jugador->pool_particula_0[parametro2].pos[2];
        sp_ac[0] = 0;
        sp_ac[1] = jugador->desconocido_048[parametro3];
        sp_ac[2] = 0;
        if ((jugador->efectos & EFECTO_ESTRELLA) &&
            (((s32) temporizador_circuito - jugador_estrella_efecto_inicio_tiempo[indice_jugador]) < DURACION_EFECTO_ESTRELLA - 1)) {
            prim_rojo = (colores_prim[1] >> 0x10) & 0xFF;
            verde_prim = (colores_prim[1] >> 0x08) & 0xFF;
            azul_prim = (colores_prim[1] >> 0x00) & 0xFF;
            amb_rojo = (colores_amb[1] >> 0x10) & 0xFF;
            verde_amb = (colores_amb[1] >> 0x08) & 0xFF;
            azul_amb = (colores_amb[1] >> 0x00) & 0xFF;
            prim_alpha = jugador->pool_particula_0[parametro2].alpha;
            funcion_800652D4(sp_b4, sp_ac, ((jugador->pool_particula_0[parametro2].scale * jugador->size) * 1.4));
            gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
            gDPLoadTextureBlock(display_list_cabeza++, comun_textura_particula_humo[jugador->pool_particula_0[parametro2].desconocido_010],
                                G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            funcion_8004B72C(prim_rojo, verde_prim, azul_prim, amb_rojo, verde_amb, azul_amb, prim_alpha);
            gDPSetAlphaCompare(display_list_cabeza++, G_AC_DITHER);
            gSPDisplayList(display_list_cabeza++, dato_0D008E48);
        } else {
            prim_rojo = (colores_prim[jugador->pool_particula_0[parametro2].rojo] >> 0x10) & 0xFF;
            verde_prim = (colores_prim[jugador->pool_particula_0[parametro2].rojo] >> 0x08) & 0xFF;
            azul_prim = (colores_prim[jugador->pool_particula_0[parametro2].rojo] >> 0x00) & 0xFF;
            amb_rojo = (colores_amb[jugador->pool_particula_0[parametro2].rojo] >> 0x10) & 0xFF;
            verde_amb = (colores_amb[jugador->pool_particula_0[parametro2].rojo] >> 0x08) & 0xFF;
            azul_amb = (colores_amb[jugador->pool_particula_0[parametro2].rojo] >> 0x00) & 0xFF;
            prim_alpha = jugador->pool_particula_0[parametro2].alpha;
            funcion_800652D4(sp_b4, sp_ac, jugador->pool_particula_0[parametro2].scale * jugador->size);
            gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
            gDPLoadTextureBlock(display_list_cabeza++, comun_textura_particula_humo[jugador->pool_particula_0[parametro2].desconocido_010],
                                G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            funcion_8004B72C(prim_rojo, verde_prim, azul_prim, amb_rojo, verde_amb, azul_amb, prim_alpha);
            gSPDisplayList(display_list_cabeza++, dato_0D008E48);
        }
        cantidad_efecto_matriz += 1;
    }
}

void funcion_800658A0(Jugador* jugador, SIN_USO s8 indice_jugador, s16 parametro2, s8 parametro3) {
    Vec3f sp54;
    Vec3s sp4_c;
    s16 rojo;
    s16 verde;
    s16 azul;
    s16 alpha;

    if (jugador->pool_particula_0[parametro2].vivo_es == 1) {
        rojo = jugador->pool_particula_0[parametro2].rojo;
        verde = jugador->pool_particula_0[parametro2].verde;
        azul = jugador->pool_particula_0[parametro2].azul;
        alpha = jugador->pool_particula_0[parametro2].alpha;
        sp54[0] = jugador->pool_particula_0[parametro2].pos[0];
        sp54[1] = jugador->pool_particula_0[parametro2].pos[1];
        sp54[2] = jugador->pool_particula_0[parametro2].pos[2];
        sp4_c[0] = 0;
        sp4_c[1] = jugador->desconocido_048[parametro3];
        sp4_c[2] = 0;
        funcion_800652D4(sp54, sp4_c, jugador->pool_particula_0[parametro2].scale * jugador->size);
        gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
        gDPLoadTextureBlock(display_list_cabeza++, dato_8018D48C, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        funcion_8004B35C(rojo, verde, azul, alpha);
        gSPDisplayList(display_list_cabeza++, dato_0D008E48);
        cantidad_efecto_matriz += 1;
    }
}

void renderizar_particulas_derrape_jugador(Jugador* jugador, SIN_USO s8 indice_jugador, s16 parametro2, s8 parametro3) {
    Vec3f sp_b4;
    Vec3s sp_ac;
    s32 variable_s0;
    s16 prim_rojo;
    s16 verde_prim;
    s16 azul_prim;
    s16 prim_alpha;
    s16 amb_rojo;
    s16 verde_amb;
    s16 azul_amb;
    s32 sp8_c[] = { 0x00ffffff, 0x00ffff00, 0x00ff9600 };
    if (jugador->pool_particula_1[parametro2].vivo_es == 1) {
        if (jugador->duracion_derrape >= 50) {
            variable_s0 = 1;
        } else {
            variable_s0 = 0;
        }
        prim_rojo = jugador->pool_particula_1[parametro2].rojo;
        verde_prim = jugador->pool_particula_1[parametro2].verde;
        azul_prim = jugador->pool_particula_1[parametro2].azul;
        prim_alpha = jugador->pool_particula_1[parametro2].alpha;
        amb_rojo = (sp8_c[jugador->pool_particula_1[parametro2].desconocido_040] >> 0x10) & 0xFF;
        verde_amb = (sp8_c[jugador->pool_particula_1[parametro2].desconocido_040] >> 0x08) & 0xFF;
        azul_amb = (sp8_c[jugador->pool_particula_1[parametro2].desconocido_040] >> 0x00) & 0xFF;
        sp_b4[0] = jugador->pool_particula_1[parametro2].pos[0];
        sp_b4[1] = jugador->pool_particula_1[parametro2].pos[1];
        sp_b4[2] = jugador->pool_particula_1[parametro2].pos[2];
        sp_ac[0] = 0;
        sp_ac[1] = jugador->desconocido_048[parametro3];
        sp_ac[2] = 0;
        funcion_800652D4(sp_b4, sp_ac, jugador->pool_particula_1[parametro2].scale * jugador->size);
        if (variable_s0 == 0) {
            gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
            gDPLoadTextureBlock(display_list_cabeza++, *dato_800E4770[variable_s0], G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            funcion_8004B72C(prim_rojo, verde_prim, azul_prim, amb_rojo, verde_amb, azul_amb, prim_alpha);
            gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2);
            gSPDisplayList(display_list_cabeza++, dato_0D008DF8);
        } else {
            gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
            gDPLoadTextureBlock(display_list_cabeza++, *dato_800E4770[variable_s0], G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            funcion_8004B72C(prim_rojo, verde_prim, azul_prim, amb_rojo, verde_amb, azul_amb, prim_alpha);
            gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2);
            gSPDisplayList(display_list_cabeza++, dato_0D008E48);
        }
        cantidad_efecto_matriz += 1;
    }
}
