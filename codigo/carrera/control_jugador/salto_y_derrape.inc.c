// Salto y derrape

void funcion_80029B4C(Jugador* jugador, SIN_USO f32 parametro1, f32 parametro2, SIN_USO f32 parametro3) {
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    Vec3f sp8_c;
    Vec3f sp80;
    Mat3 sp5_c;
    SIN_USO s32 relleno;
    f32 temporal_f0_2;
    f32 temporal_f2_3;
    s16 temporal_v0;
    f32 variable_f12;

    if ((jugador->efectos & EFECTO_RAYO) == EFECTO_RAYO) {
        variable_f12 = 18.0f * ((((tamanio_personaje[jugador->id_personaje] / 2)) * ((jugador->size) * 1.5)));
    } else {
        variable_f12 = 18.0f * (tamanio_personaje[jugador->id_personaje] / 2);
    }

    calcular_matriz_orientacion(sp5_c, 0.0f, 1.0f, 0.0f, (jugador->rotacion[1] + jugador->desconocido_0C0));
    sp8_c[0] = variable_f12 - 3.6;
    sp8_c[1] = -jugador->tamanio_caja_envolvente;
    sp8_c[2] = variable_f12 - 2.0f;
    transformar_mat3_vec3f_mtxf(sp8_c, sp5_c);
    sp80[0] = jugador->ruedas[IZQUIERDA_FRENTE].pos[0];
    sp80[1] = jugador->ruedas[IZQUIERDA_FRENTE].pos[1];
    sp80[2] = jugador->ruedas[IZQUIERDA_FRENTE].pos[2];
    jugador->ruedas[IZQUIERDA_FRENTE].pos[0] = jugador->pos[0] + sp8_c[0];
    jugador->ruedas[IZQUIERDA_FRENTE].pos[1] = jugador->pos[1] + sp8_c[1];
    jugador->ruedas[IZQUIERDA_FRENTE].pos[2] = jugador->pos[2] + sp8_c[2];
    colision_terreno_jugador(jugador, &jugador->ruedas[IZQUIERDA_FRENTE], sp80[0], sp80[1], sp80[2]);
    sp8_c[0] = (-variable_f12) + 3.6;
    sp8_c[1] = -jugador->tamanio_caja_envolvente;
    sp8_c[2] = variable_f12 - 2.0f;
    transformar_mat3_vec3f_mtxf(sp8_c, sp5_c);
    sp80[0] = jugador->ruedas[DERECHA_FRENTE].pos[0];
    sp80[1] = jugador->ruedas[DERECHA_FRENTE].pos[1];
    sp80[2] = jugador->ruedas[DERECHA_FRENTE].pos[2];
    jugador->ruedas[DERECHA_FRENTE].pos[0] = jugador->pos[0] + sp8_c[0];
    jugador->ruedas[DERECHA_FRENTE].pos[1] = jugador->pos[1] + sp8_c[1];
    jugador->ruedas[DERECHA_FRENTE].pos[2] = jugador->pos[2] + sp8_c[2];
    colision_terreno_jugador(jugador, &jugador->ruedas[DERECHA_FRENTE], sp80[0], sp80[1], sp80[2]);
    sp8_c[0] = variable_f12 - 2.6;
    sp8_c[1] = -jugador->tamanio_caja_envolvente;
    sp8_c[2] = (-variable_f12) + 4.0f;
    transformar_mat3_vec3f_mtxf(sp8_c, sp5_c);
    sp80[0] = jugador->ruedas[IZQUIERDA_ATRAS].pos[0];
    sp80[1] = jugador->ruedas[IZQUIERDA_ATRAS].pos[1];
    sp80[2] = jugador->ruedas[IZQUIERDA_ATRAS].pos[2];
    jugador->ruedas[IZQUIERDA_ATRAS].pos[0] = jugador->pos[0] + sp8_c[0];
    jugador->ruedas[IZQUIERDA_ATRAS].pos[1] = jugador->pos[1] + sp8_c[1];
    jugador->ruedas[IZQUIERDA_ATRAS].pos[2] = jugador->pos[2] + sp8_c[2];
    colision_terreno_jugador(jugador, &jugador->ruedas[IZQUIERDA_ATRAS], sp80[0], sp80[1], sp80[2]);
    sp8_c[0] = (-variable_f12) + 2.6;
    sp8_c[1] = -jugador->tamanio_caja_envolvente;
    sp8_c[2] = (-variable_f12) + 4.0f;
    transformar_mat3_vec3f_mtxf(sp8_c, sp5_c);
    sp80[0] = jugador->ruedas[DERECHA_ATRAS].pos[0];
    sp80[1] = jugador->ruedas[DERECHA_ATRAS].pos[1];
    sp80[2] = jugador->ruedas[DERECHA_ATRAS].pos[2];
    jugador->ruedas[DERECHA_ATRAS].pos[0] = jugador->pos[0] + sp8_c[0];
    jugador->ruedas[DERECHA_ATRAS].pos[1] = jugador->pos[1] + sp8_c[1];
    jugador->ruedas[DERECHA_ATRAS].pos[2] = jugador->pos[2] + sp8_c[2];
    colision_terreno_jugador(jugador, &jugador->ruedas[DERECHA_ATRAS], sp80[0], sp80[1], sp80[2]);
    if (!(jugador->efectos & EFECTO_EN_EL_AIRE)) {
        a = (jugador->ruedas[IZQUIERDA_ATRAS].altura_base + jugador->ruedas[IZQUIERDA_FRENTE].altura_base) / 2;
        mover_f32_hacia(&jugador->desconocido_230, a, 0.5f);

        b = (jugador->ruedas[DERECHA_ATRAS].altura_base + jugador->ruedas[DERECHA_FRENTE].altura_base) / 2;
        mover_f32_hacia(&jugador->desconocido_23C, b, 0.5f);

        c = (jugador->ruedas[DERECHA_FRENTE].altura_base + jugador->ruedas[IZQUIERDA_FRENTE].altura_base) / 2;
        mover_f32_hacia(&jugador->desconocido_1FC, c, 0.5f);

        d = (jugador->ruedas[DERECHA_ATRAS].altura_base + jugador->ruedas[IZQUIERDA_ATRAS].altura_base) / 2;
        mover_f32_hacia(&jugador->desconocido_1F8, d, 0.5f);
    }
    temporal_f2_3 = ((tamanio_personaje[jugador->id_personaje] * 18.0f) + 1.0f) * jugador->size;
    temporal_f0_2 = jugador->desconocido_23C - jugador->desconocido_230;
    jugador->desconocido_206 = -atan1s(temporal_f0_2 / temporal_f2_3);
    if (((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == MANTENIDO_POR_LAKITU) || (jugador->efectos & EFECTO_EN_EL_AIRE)) {
        jugador->desconocido_206 = 0;
    }
    if ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) {
        temporal_f0_2 = jugador->desconocido_1F8 - jugador->desconocido_1FC;
        mover_s16_hacia(&jugador->acel_pendiente, atan1s(temporal_f0_2 / temporal_f2_3), 0.5f);
    } else {
        temporal_f0_2 = jugador->pos_viejo[1] - parametro2;
        temporal_v0 = atan1s(temporal_f0_2 / temporal_f2_3);
        if (temporal_f0_2 >= 0.0f) {
            temporal_v0 /= 4;
        } else {
            temporal_v0 *= 10;
        }
        mover_s16_hacia(&jugador->acel_pendiente, temporal_v0, 0.5f);
    }
    if (((jugador->efectos & EFECTO_EN_EL_AIRE) == EFECTO_EN_EL_AIRE) &&
        ((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == MANTENIDO_POR_LAKITU)) {
        jugador->acel_pendiente = (s16) ((s32) jugador->desconocido_D9C);
    }
    jugador->tipo_superficie = obtener_tipo_superficie(jugador->colision.indice_zx_malla) & 0xFF;
    if (jugador->tipo_superficie == ASFALTO_RAMPA_IMPULSO) {
        if (((jugador->efectos & IMPULSO_RAMPA_ASFALTO_EFECTO) != IMPULSO_RAMPA_ASFALTO_EFECTO) &&
            ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE)) {
            jugador->disparadores |= IMPULSO_RAMPA_ASFALTO_DISPARADOR;
        }
    }
    if (jugador->tipo_superficie == MADERA_RAMPA_IMPULSO) {
        if (((jugador->efectos & IMPULSO_RAMPA_MADERA_EFECTO) != IMPULSO_RAMPA_MADERA_EFECTO) &&
            ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE)) {
            jugador->disparadores |= IMPULSO_RAMPA_MADERA_DISPARADOR;
        }
    }
}

void funcion_8002A194(Jugador* jugador, f32 x, f32 y, f32 z) {
    SIN_USO s32 relleno[2];
    f32 temporal_f12;
    f32 variable_f20;
    s32 temporal_v0;
    s16 temporal_v1;
    s16 variable_a1;
    SIN_USO s32 relleno2;
    f32 temporal_f0;

    temporal_v1 = -jugador->rotacion[1] - jugador->desconocido_0C0;
    if ((jugador->efectos & EFECTO_RAYO) == EFECTO_RAYO) {
        variable_f20 = (((tamanio_personaje[jugador->id_personaje] * 18) / 2) * (jugador->size * 1.5)) - 1;
    } else {
        variable_f20 = (((tamanio_personaje[jugador->id_personaje] * 18) / 2) * jugador->size) - 1;
    }

    jugador->ruedas[IZQUIERDA_FRENTE].pos[2] = (coss(temporal_v1 + 0x2000) * variable_f20) + z;
    temporal_f12 = (senos(temporal_v1 + 0x2000) * variable_f20) + x;
    jugador->ruedas[IZQUIERDA_FRENTE].pos[0] = temporal_f12;
    jugador->ruedas[IZQUIERDA_FRENTE].altura_base =
        calcular_altura_superficie(temporal_f12, y, jugador->ruedas[IZQUIERDA_FRENTE].pos[2], jugador->colision.indice_zx_malla);

    jugador->ruedas[DERECHA_FRENTE].pos[2] = (coss(temporal_v1 - 0x2000) * variable_f20) + z;
    temporal_f12 = (senos(temporal_v1 - 0x2000) * variable_f20) + x;
    jugador->ruedas[DERECHA_FRENTE].pos[0] = temporal_f12;
    jugador->ruedas[DERECHA_FRENTE].altura_base =
        calcular_altura_superficie(temporal_f12, y, jugador->ruedas[DERECHA_FRENTE].pos[2], jugador->colision.indice_zx_malla);

    jugador->ruedas[IZQUIERDA_ATRAS].pos[2] = (coss(temporal_v1 + 0x6000) * variable_f20) + z;
    temporal_f12 = (senos(temporal_v1 + 0x6000) * variable_f20) + x;
    jugador->ruedas[IZQUIERDA_ATRAS].pos[0] = temporal_f12;
    jugador->ruedas[IZQUIERDA_ATRAS].altura_base =
        calcular_altura_superficie(temporal_f12, y, jugador->ruedas[IZQUIERDA_ATRAS].pos[2], jugador->colision.indice_zx_malla);

    jugador->ruedas[DERECHA_ATRAS].pos[2] = (coss(temporal_v1 - 0x6000) * variable_f20) + z;
    jugador->ruedas[DERECHA_ATRAS].pos[0] = (senos(temporal_v1 - 0x6000) * variable_f20) + x;
    jugador->ruedas[DERECHA_ATRAS].altura_base = calcular_altura_superficie(
        jugador->ruedas[IZQUIERDA_ATRAS].pos[0], y, jugador->ruedas[IZQUIERDA_ATRAS].pos[2], jugador->colision.indice_zx_malla);

    if ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) {
        jugador->desconocido_230 = (jugador->ruedas[IZQUIERDA_ATRAS].altura_base + jugador->ruedas[IZQUIERDA_FRENTE].altura_base) / 2;
        jugador->desconocido_23C = (jugador->ruedas[DERECHA_ATRAS].altura_base + jugador->ruedas[DERECHA_FRENTE].altura_base) / 2;
        jugador->desconocido_1FC = (jugador->ruedas[DERECHA_FRENTE].altura_base + jugador->ruedas[IZQUIERDA_FRENTE].altura_base) / 2;
        jugador->desconocido_1F8 = (jugador->ruedas[DERECHA_ATRAS].altura_base + jugador->ruedas[IZQUIERDA_ATRAS].altura_base) / 2;
    }
    jugador->tipo_superficie = (u8) obtener_tipo_superficie(jugador->colision.indice_zx_malla);
    jugador->ruedas[DERECHA_ATRAS].tipo_superficie = jugador->tipo_superficie;
    jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie = jugador->tipo_superficie;
    jugador->ruedas[DERECHA_FRENTE].tipo_superficie = jugador->tipo_superficie;
    jugador->ruedas[IZQUIERDA_FRENTE].tipo_superficie = jugador->tipo_superficie;
    variable_f20 = (tamanio_personaje[jugador->id_personaje] * 18) + 1;
    temporal_f0 = (jugador->desconocido_23C - jugador->desconocido_230);
    jugador->desconocido_206 = -atan1s(temporal_f0 / variable_f20);
    if ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) {
        temporal_f0 = (jugador->desconocido_1F8 - jugador->desconocido_1FC);
        mover_s16_hacia(&jugador->acel_pendiente, atan1s(temporal_f0 / variable_f20), 0.5f);
    } else {
        temporal_f0 = jugador->pos_viejo[1] - y;
        temporal_v0 = atan1s(temporal_f0 / variable_f20);
        if (temporal_f0 >= 0.0f) {
            variable_a1 = temporal_v0 * 2;
        } else {
            variable_a1 = temporal_v0 * 0xA;
        }
        mover_s16_hacia(&jugador->acel_pendiente, variable_a1, 0.5f);
    }
    if (funcion_802ABD7C(jugador->colision.indice_zx_malla) != 0) {
        jugador->ruedas[DERECHA_ATRAS].desconocido_14 |= 1;
    } else {
        jugador->ruedas[DERECHA_ATRAS].desconocido_14 &= ~1;
    }
    if (jugador->tipo_superficie == ASFALTO_RAMPA_IMPULSO) {
        if (((jugador->efectos & IMPULSO_RAMPA_ASFALTO_EFECTO) != IMPULSO_RAMPA_ASFALTO_EFECTO) &&
            ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE)) {
            jugador->disparadores |= IMPULSO_RAMPA_ASFALTO_DISPARADOR;
        }
    }
    if (jugador->tipo_superficie == MADERA_RAMPA_IMPULSO) {
        if (((jugador->efectos & IMPULSO_RAMPA_MADERA_EFECTO) != IMPULSO_RAMPA_MADERA_EFECTO) &&
            ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE)) {
            jugador->disparadores |= IMPULSO_RAMPA_MADERA_DISPARADOR;
        }
    }
}

void funcion_8002A5F4(Vec3f parametro0, f32 parametro1, Vec3f parametro2, f32 parametro3, f32 parametro4) {
    f32 temporal_f0;
    f32 temporal_f2;
    f32 temporal_f12;
    f32 temporal_f14;
    f32 temporal_f16;
    f32 temporal_f18;
    f32 temporal_f20;
    f32 tmp1;
    f32 tmp2;
    f32 tmp3;

    temporal_f0 = parametro2[0];
    temporal_f2 = parametro2[1];
    temporal_f12 = parametro2[2];
    temporal_f14 = -parametro0[0];
    temporal_f16 = -parametro0[1];
    temporal_f18 = -parametro0[2];
    temporal_f20 = (temporal_f14 * temporal_f0) + (temporal_f16 * temporal_f2) + (temporal_f18 * temporal_f12);
    tmp1 = temporal_f0 - (temporal_f20 * temporal_f14);
    tmp2 = temporal_f2 - (temporal_f20 * temporal_f16);
    tmp3 = temporal_f12 - (temporal_f20 * temporal_f18);
    if (parametro1 < -parametro4) {
        parametro2[0] = tmp1 - (temporal_f20 * temporal_f14 * parametro3);
        parametro2[1] = tmp2 - (temporal_f20 * temporal_f16 * parametro3);
        parametro2[2] = tmp3 - (temporal_f20 * temporal_f18 * parametro3);
    } else {
        parametro2[0] = tmp1;
        parametro2[1] = tmp2;
        parametro2[2] = tmp3;
    }
}

void funcion_8002A704(Jugador* jugador, s8 indice_jugador) {
    jugador->efectos |= EFECTO_HONGO;
    jugador->disparadores &= ~DISPARADOR_IMPULSO_INICIO;
    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
        funcion_800C90F4(0U, (jugador->id_personaje * 0x10) + 0x29008001);
        funcion_800C9060(indice_jugador, 0x1900A40BU);
    }
    jugador->temporizador_impulso = 0x0050;
}

void funcion_8002A79C(Jugador* jugador, s8 indice_jugador) {
    if (((jugador->efectos & MINI_EFECTO_TURBO) != MINI_EFECTO_TURBO) &&
        ((jugador->efectos & EFECTO_DERRAPANDO) != EFECTO_DERRAPANDO) && (jugador->estado_derrape >= 2)) {
        jugador->efectos |= MINI_EFECTO_TURBO;
        jugador->desconocido_23A = 0;
        jugador->estado_derrape = 0;
        jugador->contador_estado_derrape = 0;
        if (dato_8015F890 != 1) {
            if ((jugador->type & HUMANO_JUGADOR) && !(jugador->type & INVISIBLE_JUGADOR_O_BOMBA)) {
                funcion_800C9250(indice_jugador);
            }
        } else if (jugador == jugador_uno) {
            funcion_800C9250(indice_jugador);
        }
    } else if ((jugador->efectos & MINI_EFECTO_TURBO) == MINI_EFECTO_TURBO) {
        jugador->desconocido_23A += 1;
        if (jugador->desconocido_23A >= 0x1F) {
            jugador->desconocido_23A = 0;
            jugador->efectos &= ~MINI_EFECTO_TURBO;
            jugador->estado_derrape = 0;
            jugador->contador_estado_derrape = 0;
        }
    }
}

void actualizar_contador_estado_derrape(Jugador* jugador, s8 indice_jugador) {
    if (((s16) jugador->desconocido_0C0 / GRADOS(1)) > 0) {
        if (((s32) jugador->posicion_giro >> 16) <= -10) {
            if (jugador->contador_estado_derrape <= 100) {
                jugador->contador_estado_derrape++;
            }
            if ((jugador->contador_estado_derrape == 100) && (jugador->type & HUMANO_JUGADOR)) {
                funcion_800C9060(indice_jugador, 0x1900851EU);
            }
        } else {
            if ((jugador->contador_estado_derrape >= 18) && (jugador->contador_estado_derrape < 100)) {
                if (jugador->estado_derrape < 3) {
                    jugador->estado_derrape++;
                }
            }
            if ((jugador->contador_estado_derrape >= 10) && (jugador->contador_estado_derrape < 100)) {
                jugador->contador_estado_derrape = 10;
            } else {
                jugador->contador_estado_derrape = 0;
                jugador->estado_derrape = 0;
            }
        }
    } else if (((s32) jugador->posicion_giro >> 16) >= 10) {
        if (jugador->contador_estado_derrape <= 100) {
            jugador->contador_estado_derrape++;
        }
        if ((jugador->contador_estado_derrape == 100) && (jugador->type & HUMANO_JUGADOR)) {
            funcion_800C9060(indice_jugador, 0x1900851EU);
        }
    } else {
        if ((jugador->contador_estado_derrape >= 18) && (jugador->contador_estado_derrape < 100)) {
            if (jugador->estado_derrape < 3) {
                jugador->estado_derrape++;
            }
        }
        if ((jugador->contador_estado_derrape >= 10) && (jugador->contador_estado_derrape < 100)) {
            jugador->contador_estado_derrape = 10;
        } else {
            jugador->contador_estado_derrape = 0;
            jugador->estado_derrape = 0;
        }
    }
}

void salto_kart(Jugador* jugador) {
    jugador->tiron_salto_kart = kart_salto_tiron_tabla[jugador->id_personaje];
    jugador->aceleracion_salto_kart = 0.0f;
    jugador->velocidad_salto_kart = kart_salto_inicial_velocidad_tabla[jugador->id_personaje];
    jugador->efectos |= EFECTO_SALTO;
    jugador->desconocido_dac = 3.0f;
    jugador->gravedad_kart = 500.0f;
    funcion_80036C5C(jugador);
}

void funcion_8002AAC0(Jugador* jugador) {
    jugador->aceleracion_salto_kart -= jugador->tiron_salto_kart;
    if (jugador->aceleracion_salto_kart >= 9.0f) {
        jugador->aceleracion_salto_kart = 9.0f;
    }

    if (jugador->aceleracion_salto_kart <= -9.0f) {
        jugador->aceleracion_salto_kart = -9.0f;
    }

    jugador->velocidad_salto_kart += jugador->aceleracion_salto_kart;
    if (jugador->velocidad_salto_kart >= 15.0f) {
        jugador->velocidad_salto_kart = 15.0f;
    }

    if (jugador->velocidad_salto_kart <= 0.0f) {
        jugador->tiron_salto_kart = 0.0f;
        jugador->aceleracion_salto_kart = 0.0f;
        jugador->velocidad_salto_kart = 0.0f;
    }
}

void funcion_8002AB70(Jugador* jugador) {
    SIN_USO s32 relleno[2];
    if (((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) && (jugador->desconocido_08C > 0.0f)) {
        if (((jugador->acel_pendiente / GRADOS(1)) < -1) && ((jugador->acel_pendiente / GRADOS(1)) >= -0x14) &&
            (((jugador->speed / 18.0f) * 216.0f) >= 20.0f)) {
            mover_f32_hacia(&jugador->gravedad_kart, 500.0f, 1.0f);
            mover_f32_hacia(&jugador->desconocido_dac, 3.0f, 0.05f);
        } else {
            mover_f32_hacia(&jugador->gravedad_kart, tabla_gravedad_kart[jugador->id_personaje], 0.1f);
            mover_f32_hacia(&jugador->desconocido_dac, 1.0f, 0.07f);
        }
    } else {
        if (jugador->colision.distancia_superficie[2] >= 50.0f) {
            jugador->desconocido_dac = 2.0f;
        }
        mover_f32_hacia(&jugador->gravedad_kart, tabla_gravedad_kart[jugador->id_personaje], 0.02f);
        if ((jugador->efectos & EFECTO_SALTO) == EFECTO_SALTO) {
            mover_f32_hacia(&jugador->desconocido_dac, 1.0f, 0.07f);
        } else {
            mover_f32_hacia(&jugador->desconocido_dac, 1.0f, 0.07f);
        }
    }
    if ((jugador->efectos & IMPULSO_RAMPA_ASFALTO_EFECTO) == IMPULSO_RAMPA_ASFALTO_EFECTO) {
        mover_f32_hacia(&jugador->desconocido_dac, 20.0f, 1.0f);
        jugador->gravedad_kart = 3500.0f;
    }
    if ((jugador->efectos & IMPULSO_RAMPA_MADERA_EFECTO) == IMPULSO_RAMPA_MADERA_EFECTO) {
        mover_f32_hacia(&jugador->desconocido_dac, 25.0f, 1.0f);
        jugador->gravedad_kart = 1800.0f;
    }
    if ((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) == GOLPE_POR_CAPARAZON_VERDE_EFECTO) {
        jugador->gravedad_kart = 1100.0f;
    }
    if (jugador->efectos & desconocido_efecto_0_x_80000) {
        jugador->gravedad_kart = 1500.0f;
    }
    if ((jugador->kart_props & sin_uso_0_x_800) != 0) {
        jugador->gravedad_kart = 1900.0f;
    }
    if ((jugador->efectos & desconocido_efecto_0_x_800000) == desconocido_efecto_0_x_800000) {
        jugador->gravedad_kart = 300.0f;
    }
    if ((jugador->efectos & EFECTO_ERROR_EXPLOSION) == EFECTO_ERROR_EXPLOSION) {
        jugador->gravedad_kart = 550.0f;
    }
    if ((jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA) == GOLPE_POR_EFECTO_ESTRELLA) {
        jugador->gravedad_kart = 800.0f;
    }
}

SIN_USO void funcion_8002AE20(void) {
}

SIN_USO void funcion_8002AE28(void) {
}

SIN_USO void funcion_8002AE30(void) {
}

void funcion_8002AE38(Jugador* jugador, s8 parametro1, f32 parametro2, f32 parametro3, f32 parametro4, f32 parametro5) {
    SIN_USO s32 relleno[4];
    s16 temporal_v0_3;
    f32 sp28;
    f32 temporal_f16;
    s16 temporal_a0;
    s32 variable_v1;

    sp28 = (senos(-jugador->rotacion[1]) * jugador->speed) + parametro2;
    temporal_f16 = (coss(-jugador->rotacion[1]) * jugador->speed) + parametro3;
    if (((jugador->efectos & BANANA_CERCA_EFECTO_TROMPO) != BANANA_CERCA_EFECTO_TROMPO) &&
        ((jugador->efectos & EFECTO_DERRAPANDO) != EFECTO_DERRAPANDO) && !(jugador->kart_props & CONDUCIENDO_CERCA_TROMPO) &&
        ((((jugador->speed / 18.0f) * 216.0f) <= 8.0f) ||
         (((jugador->posicion_giro >> 16) < 5) && ((jugador->posicion_giro >> 16) > -5)))) {
        if ((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB) {
            jugador->desconocido_0C0 = (f32) (jugador->desconocido_0C0 - (jugador->desconocido_0C0 / 10));
        } else {
            temporal_v0_3 = jugador->desconocido_0C0;
            jugador->desconocido_0C0 = jugador->desconocido_078 * 9;
            temporal_a0 = jugador->desconocido_0C0 - temporal_v0_3;
            jugador->desconocido_0C0 = (f32) (temporal_v0_3 + (temporal_a0 / 15));
        }
    } else {
        temporal_v0_3 = jugador->desconocido_0C0;
        if (dato_801652C0[parametro1] & 8) {
            variable_v1 = 2;
        } else {
            variable_v1 = 0;
        }
        if ((jugador->actual_rapidez >= 200.0f) && (variable_v1 == 2) &&
            (((jugador->desconocido_0C0 / GRADOS(1)) >= 0x10) || ((jugador->desconocido_0C0 / GRADOS(1)) < -0xF))) {
            jugador->desconocido_0C0 = atan2s(parametro2 - parametro4, parametro3 - parametro5) - atan2s(parametro2 - sp28, parametro3 - temporal_f16);
        } else {
            jugador->desconocido_0C0 = (atan2s(parametro2 - parametro4, parametro3 - parametro5) - atan2s(parametro2 - sp28, parametro3 - temporal_f16)) * 2;
        }
        if (((jugador->efectos & EFECTO_DERRAPANDO) != EFECTO_DERRAPANDO) &&
            ((((jugador->posicion_giro >> 16) > 0) && (jugador->desconocido_0C0 < 0)) ||
             (((jugador->posicion_giro >> 16) < 0) && (jugador->desconocido_0C0 > 0)))) {
            if (jugador->desconocido_0C0 > 0) {
                jugador->desconocido_0C0 = jugador->desconocido_078 * 0x14;
            }
            if (jugador->desconocido_0C0 < 0) {
                jugador->desconocido_0C0 = jugador->desconocido_078 * 0x14;
            }
            temporal_a0 = jugador->desconocido_0C0 - temporal_v0_3;
            jugador->desconocido_0C0 = (f32) (temporal_v0_3 + (temporal_a0 / 12));
        } else {
            if (jugador->desconocido_0C0 >= 0x1C71) {
                jugador->desconocido_0C0 = 0x1C70;
            }
            if (jugador->desconocido_0C0 < -0x1C70) {
                jugador->desconocido_0C0 = -0x1C70;
            }
            temporal_a0 = jugador->desconocido_0C0 - temporal_v0_3;
            jugador->desconocido_0C0 = (f32) (temporal_v0_3 + (temporal_a0 / 12));
        }
    }
}

void funcion_8002B218(Jugador* jugador) {
    u16 algun_indice;
    u16 sp38[10] = { 0x0003, 0x0016, 0x0026, 0x003c, 0x0050, 0x0069, 0x0090, 0x009d, 0x00a9, 0x00cc };
    u16 sp24[10] = { 0x000c, 0x0021, 0x002f, 0x0045, 0x005f, 0x007a, 0x0098, 0x00a5, 0x00b3, 0x00d5 };

    for (algun_indice = 0; algun_indice < 10; algun_indice++) {
        if (jugador->desconocido_006 == sp38[algun_indice]) {
            jugador->efectos |= EFECTO_DERRAPANDO;
            salto_kart(jugador);
            jugador->duracion_derrape = 0;
            break;
        }

        if (jugador->desconocido_006 == sp24[algun_indice]) {
            jugador->efectos &= ~EFECTO_DERRAPANDO;
            break;
        }
    }
}

void aplicar_disparadores(Jugador* jugador, s8 id_jugador, SIN_USO s8 id_pantalla) {
    if ((jugador->disparadores & DISPARADOR_VUELCO_ALTO) == DISPARADOR_VUELCO_ALTO) {
        vuelco_alto_disparador(jugador, id_jugador);
    }
    if ((jugador->disparadores & DISPARADOR_VUELCO_BAJO) == DISPARADOR_VUELCO_BAJO) {
        funcion_8008C528(jugador, id_jugador);
    }
    if ((jugador->disparadores & DISPARADOR_BANANA_GOLPE) == DISPARADOR_BANANA_GOLPE) {
        banana_golpe_disparador(jugador, id_jugador);
    }
    if ((jugador->disparadores & DISPARADOR_HONGO) == DISPARADOR_HONGO) {
        hongo_disparador(jugador, id_jugador);
    }
    if ((jugador->disparadores & DISPARADOR_IMPULSO_INICIO) == DISPARADOR_IMPULSO_INICIO) {
        funcion_8002A704(jugador, id_jugador);
    }
    if ((jugador->disparadores & sin_uso_disparador_0_x_1000) == sin_uso_disparador_0_x_1000) {
        funcion_8008D570(jugador, id_jugador);
    }
    if ((jugador->disparadores & sin_uso_disparador_0_x_20000) == sin_uso_disparador_0_x_20000) {
        funcion_8008D7B0(jugador, id_jugador);
    }
    if ((jugador->disparadores & THWOMP_DISPARADOR_APLASTAMIENTO) == THWOMP_DISPARADOR_APLASTAMIENTO) {
        aplastamiento_disparador(jugador, id_jugador);
    }
    if ((jugador->disparadores & DISPARADOR_GOLPE_RAYO) == DISPARADOR_GOLPE_RAYO) {
        golpe_rayo_disparador(jugador, id_jugador);
    }
    if ((jugador->disparadores & DISPARADOR_TROMPO) == DISPARADOR_TROMPO) {
        agregar_efecto_trompo(jugador, id_jugador);
    }
    if ((jugador->disparadores & DISPARADOR_VUELCO_VERTICAL) == DISPARADOR_VUELCO_VERTICAL) {
        vuelco_vertical_disparador(jugador, id_jugador);
    }
    if ((jugador->disparadores & GOLPE_POR_DISPARADOR_ESTRELLA) == GOLPE_POR_DISPARADOR_ESTRELLA) {
        vuelco_alto_disparador(jugador, id_jugador);
    }
    if ((jugador->disparadores & IMPULSO_RAMPA_ASFALTO_DISPARADOR) == IMPULSO_RAMPA_ASFALTO_DISPARADOR) {
        disparador_asfalto_rampa_impulso(jugador, id_jugador);
    }
    if ((jugador->disparadores & IMPULSO_RAMPA_MADERA_DISPARADOR) == IMPULSO_RAMPA_MADERA_DISPARADOR) {
        disparador_madera_rampa_impulso(jugador, id_jugador);
    }
    if ((jugador->disparadores & DISPARADOR_ESTRELLA) == DISPARADOR_ESTRELLA) {
        estrella_disparador(jugador, id_jugador);
    }
    if ((jugador->disparadores & BOO_DISPARADOR) == BOO_DISPARADOR) {
        disparador_boo(jugador, id_jugador);
    }
    if (jugador->disparadores & DISPARADOR_TROMPO_CONDUCIENDO) {
        trompo_conduciendo_disparador(jugador, id_jugador);
    }
    if (jugador->disparadores & GOLPE_PALETA_BARCO_DISPARADOR) {
        vuelco_vertical_disparador(jugador, id_jugador);
    }
}

void funcion_8002B5C0(Jugador* jugador, SIN_USO s8 id_jugador, SIN_USO s8 id_pantalla) {
    if (((jugador->lakitu_props & LAKITU_ESCENA) != 0) || ((jugador->lakitu_props & MANTENIDO_POR_LAKITU) != 0)) {
        jugador->disparadores &=
            TODOS_DISPARADORES & ~(DISPARADORES_GOLPE | CUALQUIER_DISPARADORES_IMPULSO | DISPARADORES_TROMPO_CARRERA | DISPARADORES_TRANSICION_ESTADO);
    }
    if ((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) == GOLPE_POR_CAPARAZON_VERDE_EFECTO) {
        jugador->disparadores &= TODOS_DISPARADORES & ~(CUALQUIER_DISPARADORES_IMPULSO | DISPARADORES_TROMPO_CARRERA | DISPARADORES_TRANSICION_ESTADO);
    }
    if (((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
        ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO)) {
        jugador->disparadores &=
            (TODOS_DISPARADORES & ~(CUALQUIER_DISPARADORES_IMPULSO | DISPARADORES_TROMPO_CARRERA | DISPARADORES_TRANSICION_ESTADO)) |
            sin_uso_disparador_0_x_20000;
    }
    // Near spinout (banana)
    if ((jugador->efectos & BANANA_CERCA_EFECTO_TROMPO) == BANANA_CERCA_EFECTO_TROMPO) {
        jugador->disparadores &= TODOS_DISPARADORES & ~(CUALQUIER_DISPARADORES_IMPULSO | DISPARADORES_TROMPO_CARRERA | DISPARADORES_TRANSICION_ESTADO);
    }
    if ((jugador->kart_props & CONDUCIENDO_CERCA_TROMPO) != 0) {
        jugador->disparadores &= TODOS_DISPARADORES & ~(CUALQUIER_DISPARADORES_IMPULSO | DISPARADORES_TROMPO_CARRERA | DISPARADORES_TRANSICION_ESTADO);
    }
    // unclear
    if ((jugador->efectos & desconocido_efecto_0_x_80000) == desconocido_efecto_0_x_80000) {
        jugador->disparadores &= TODOS_DISPARADORES & ~((DISPARADORES_GOLPE ^ DISPARADOR_GOLPE_RAYO) | CUALQUIER_DISPARADORES_IMPULSO |
                                             DISPARADORES_TROMPO_CARRERA | DISPARADORES_TRANSICION_ESTADO);
    }
    // unclear
    if ((jugador->efectos & desconocido_efecto_0_x_800000) == desconocido_efecto_0_x_800000) {
        jugador->disparadores &=
            TODOS_DISPARADORES & ~(DISPARADORES_GOLPE | CUALQUIER_DISPARADORES_IMPULSO | DISPARADORES_TROMPO_CARRERA | DISPARADORES_TRANSICION_ESTADO);
    }
    if ((jugador->efectos & EFECTO_APLASTAMIENTO) == EFECTO_APLASTAMIENTO) {
        jugador->disparadores &= (TODOS_DISPARADORES & ~(DISPARADORES_GOLPE | CUALQUIER_DISPARADORES_IMPULSO | DISPARADORES_TROMPO_CARRERA |
                                              DISPARADORES_TRANSICION_ESTADO)) |
                            THWOMP_DISPARADOR_APLASTAMIENTO;
    }
    if ((jugador->efectos & EFECTO_ERROR_EXPLOSION) == EFECTO_ERROR_EXPLOSION) {
        jugador->disparadores &= TODOS_DISPARADORES & ~((DISPARADORES_GOLPE ^ DISPARADOR_GOLPE_RAYO) | CUALQUIER_DISPARADORES_IMPULSO |
                                             DISPARADORES_TROMPO_CARRERA | DISPARADORES_TRANSICION_ESTADO);
    }
    if ((jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA) == GOLPE_POR_EFECTO_ESTRELLA) {
        jugador->disparadores &= TODOS_DISPARADORES & ~((DISPARADORES_GOLPE ^ DISPARADOR_GOLPE_RAYO) | CUALQUIER_DISPARADORES_IMPULSO |
                                             DISPARADORES_TROMPO_CARRERA | DISPARADORES_TRANSICION_ESTADO);
    }
    if ((jugador->efectos & IMPULSO_RAMPA_ASFALTO_EFECTO) == IMPULSO_RAMPA_ASFALTO_EFECTO) {
        jugador->disparadores &=
            TODOS_DISPARADORES & ~(DISPARADORES_GOLPE | CUALQUIER_DISPARADORES_IMPULSO | DISPARADORES_TROMPO_CARRERA | DISPARADORES_TRANSICION_ESTADO);
    }
    if ((jugador->efectos & IMPULSO_RAMPA_MADERA_EFECTO) == IMPULSO_RAMPA_MADERA_EFECTO) {
        jugador->disparadores &=
            TODOS_DISPARADORES & ~(DISPARADORES_GOLPE | CUALQUIER_DISPARADORES_IMPULSO | DISPARADORES_TROMPO_CARRERA | DISPARADORES_TRANSICION_ESTADO);
    }
    if ((jugador->efectos & EFECTO_VUELCO_TERRENO) == EFECTO_VUELCO_TERRENO) {
        jugador->disparadores &=
            TODOS_DISPARADORES & ~(DISPARADORES_GOLPE | CUALQUIER_DISPARADORES_IMPULSO | DISPARADORES_TROMPO_CARRERA | DISPARADORES_TRANSICION_ESTADO);
    }
    // star
    if ((jugador->efectos & EFECTO_ESTRELLA) == EFECTO_ESTRELLA) {
        jugador->disparadores &=
            TODOS_DISPARADORES & ~(DISPARADORES_GOLPE | DISPARADOR_HONGO | DISPARADORES_TROMPO_CARRERA | DISPARADORES_TRANSICION_ESTADO);
    }
    if ((jugador->efectos & BOO_EFECTO) == BOO_EFECTO) {
        jugador->disparadores &= TODOS_DISPARADORES & ~(DISPARADORES_GOLPE | DISPARADORES_TROMPO_CARRERA | DISPARADORES_TRANSICION_ESTADO);
    }
    if ((jugador->efectos & TEMPRANO_INICIO_TROMPO_EFECTO) == TEMPRANO_INICIO_TROMPO_EFECTO) {
        jugador->disparadores &= TODOS_DISPARADORES & ~(CUALQUIER_DISPARADORES_IMPULSO | DISPARADOR_TROMPO | DISPARADORES_TRANSICION_ESTADO);
    }
    if ((jugador->efectos & EFECTO_GOLPE_RAYO) == EFECTO_GOLPE_RAYO) {
        jugador->disparadores &=
            TODOS_DISPARADORES & ~(DISPARADORES_GOLPE | CUALQUIER_DISPARADORES_IMPULSO | DISPARADORES_TROMPO_CARRERA | DISPARADORES_TRANSICION_ESTADO);
    }
}

void funcion_8002B830(Jugador* jugador, s8 id_jugador, s8 id_pantalla) {
    if (jugador->disparadores != 0) {
        funcion_8002B5C0(jugador, id_jugador, id_pantalla);
    }
    if (jugador->disparadores != 0) {
        aplicar_disparadores(jugador, id_jugador, id_pantalla);
    }
    if ((jugador->kart_props & sin_uso_0_x_400) != 0) {
        funcion_800911B4(jugador, id_jugador);
    }
}

SIN_USO void funcion_8002B8A4(Jugador* jugador_uno_3, Jugador* jugador_dos_3) {
    s32 variable_v1;

    if (jugador_uno_3 == jugador_uno) {   variable_v1 = 0;
}
    if (jugador_uno_3 == jugador_dos) {   variable_v1 = 1;
}
    if (jugador_uno_3 == jugador_tres) { variable_v1 = 2;
}
    if (jugador_uno_3 == jugador_cuatro) {  variable_v1 = 3;
}
    if (jugador_uno_3 == jugador_cinco) {  variable_v1 = 4;
}
    if (jugador_uno_3 == jugador_seis) {   variable_v1 = 5;
}
    if (jugador_uno_3 == jugador_siete) { variable_v1 = 6;
}
    if (jugador_uno_3 == jugador_ocho) { variable_v1 = 7;
}
    dato_801653C0[variable_v1] = jugador_dos_3;
    if (jugador_dos_3 == jugador_uno) {   variable_v1 = 0;
}
    if (jugador_dos_3 == jugador_dos) {   variable_v1 = 1;
}
    if (jugador_dos_3 == jugador_tres) { variable_v1 = 2;
}
    if (jugador_dos_3 == jugador_cuatro) {  variable_v1 = 3;
}
    if (jugador_dos_3 == jugador_cinco) {  variable_v1 = 4;
}
    if (jugador_dos_3 == jugador_seis) {   variable_v1 = 5;
}
    if (jugador_dos_3 == jugador_siete) { variable_v1 = 6;
}
    if (jugador_dos_3 == jugador_ocho) { variable_v1 = 7;
}
    dato_801653C0[variable_v1] = jugador_uno_3;
}

void funcion_8002B9CC(Jugador* jugador, s8 indice_jugador, SIN_USO s32 parametro2) {
    f32 temporal_f0;
    f32 temporal_f2;
    f32 temporal_f14;
    s16 temporal_;
    s16 temporal2;

    if ((jugador->desconocido_046 & TOCAR_BICHO) == TOCAR_BICHO) {
        temporal_f0 = dato_8018CE10[indice_jugador].desconocido_04[0];
        temporal_f2 = 0;
        temporal_f14 = dato_8018CE10[indice_jugador].desconocido_04[2];
        if (sqrtf((temporal_f0 * temporal_f0) + (temporal_f2 * temporal_f2) + (temporal_f14 * temporal_f14)) >= 6.5) {
            jugador->desconocido_08C /= 4;
            jugador->actual_rapidez /= 4;
            if (!(jugador->efectos & EFECTO_TROMPO_BANANA) && !(jugador->efectos & EFECTO_TROMPO_CONDUCIENDO)) {
                agregar_efecto_trompo(jugador, indice_jugador);
            }
        }
    } else {
        temporal_f0 = velocidad_ultimo_jugador[indice_jugador][0] - jugador->velocidad[0];
        temporal_f2 = velocidad_ultimo_jugador[indice_jugador][1] - jugador->velocidad[1];
        temporal_f14 = velocidad_ultimo_jugador[indice_jugador][2] - jugador->velocidad[2];
        if (sqrtf((temporal_f0 * temporal_f0) + (temporal_f2 * temporal_f2) + (temporal_f14 * temporal_f14)) >= 4.2) {
            jugador->desconocido_08C /= 4;
            jugador->actual_rapidez /= 4;
            if (!(jugador->efectos & EFECTO_TROMPO_BANANA) && !(jugador->efectos & EFECTO_TROMPO_CONDUCIENDO)) {
                agregar_efecto_trompo(jugador, indice_jugador);
            }
        }
        temporal_ = (-(s16) obtener_angulo_xz_entre_puntos(jugador->pos, &jugador->pos_viejo[0]));
        temporal2 = (jugador->rotacion[1] - jugador->desconocido_0C0);
        temporal_ = temporal_ - temporal2;
        jugador->desconocido_234 = temporal_ / GRADOS(1);
    }
}

void funcion_8002BB9C(Jugador* jugador, f32* parametro1, f32* parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4, SIN_USO Vec3f parametro5) {
    Mat3 sp64;
    Vec3f sp58;
    Vec3f sp4_c;
    s16 variable_v0;
    s16 t0;
    SIN_USO s32 relleno;
    s16 sp30[10] = { 0, GRADOS(1), GRADOS(2), GRADOS(3), GRADOS(4), GRADOS(5), GRADOS(6), GRADOS(7), GRADOS(8), GRADOS(9) };

    if (((u16) jugador->desconocido_256) <= 0) {
        return;
    }

    if (((u16) jugador->desconocido_256) > 2) {
        return;
    }

    if (!(jugador->desconocido_046 & 0x20)) {
        return;
    }

    calcular_matriz_orientacion(sp64, 0, 1, 0, (s16) 0);

    sp58[0] = *parametro1;
    sp58[1] = 0;
    sp58[2] = *parametro2;

    transformar_mat3_vec3f_mtxf(sp58, sp64);

    sp4_c[0] = jugador->pos_viejo[0];
    sp4_c[1] = 0;
    sp4_c[2] = jugador->pos_viejo[2];

    transformar_mat3_vec3f_mtxf(sp4_c, sp64);

    variable_v0 = -(s16) obtener_angulo_xz_entre_puntos(sp58, sp4_c);
    t0 = jugador->rotacion[1];
    variable_v0 = 0x10000 + (t0 - variable_v0);
    variable_v0 /= GRADOS(1);

    if (variable_v0 < 0x97 && (variable_v0 > -0x97)) {
        return;
    }

    variable_v0 = (jugador->posicion_giro >> 16) / 6;

    if (variable_v0 < 0) {
        variable_v0 *= -1;
    }

    if (variable_v0 >= 8) {
        variable_v0 = 8;
    }

    if ((jugador->posicion_giro >> 16) < 0) {
        jugador->rotacion[1] -= sp30[variable_v0];
    } else {
        jugador->rotacion[1] += sp30[variable_v0];
    }
}

void funcion_8002BD58(Jugador* jugador) {
    s32 sp2_c[7] = { 47 << 16, 48 << 16, 49 << 16, 50 << 16, 50 << 16, 50 << 16, 50 << 16 };
    s32 sp_c[8] = { 40 << 16, 44 << 16, 48 << 16, 50 << 16, 50 << 16, 50 << 16, 50 << 16, 50 << 16 };
    s16 temporal_t5;

    if (jugador->desconocido_234 >= 0) {
        if ((jugador->desconocido_234 >= 5) && (jugador->desconocido_234 < 30)) {
            jugador->posicion_giro = sp2_c[jugador->desconocido_234 / 6];
        }
        if ((jugador->desconocido_234 >= 30) && (jugador->desconocido_234 < 80)) {
            jugador->posicion_giro = sp_c[(s32) (jugador->desconocido_234 - 30) / 12];
        }
        if (((jugador->desconocido_234 < 80) || (jugador->desconocido_234 > 90)) && (jugador->desconocido_234 > 90) &&
            (jugador->desconocido_234 <= 160)) {
            jugador->posicion_giro = sp_c[1];
        }
    } else {
        temporal_t5 = -jugador->desconocido_234;
        if ((jugador->desconocido_234 < -4) && (jugador->desconocido_234 >= -30)) {
            jugador->posicion_giro = sp2_c[temporal_t5 / 6] * -1;
        }
        if ((jugador->desconocido_234 < -30) && (jugador->desconocido_234 >= -80)) {
            jugador->posicion_giro = sp_c[(s32) (temporal_t5 - 30) / 12] * -1;
        }
        if (((jugador->desconocido_234 >= -80) || (jugador->desconocido_234 < -90)) && (jugador->desconocido_234 < -90) &&
            (jugador->desconocido_234 >= -160)) {
            jugador->posicion_giro = sp_c[1] * -1;
        }
    }
}

void funcion_8002BF4C(Jugador* jugador, s8 indice_jugador) {
    SIN_USO s32 relleno[3];
    SIN_USO s32 asignacion_inutil;
    s32 i;
    s32 variable_a2;
    Jugador* prestamo_jugador;
    Jugador* jugadores_2 = jugador_uno;

    variable_a2 = 0;

    if (((jugador->speed / 18.0f) * 216.0f) < 50.0f) {
        jugador->desconocido_0E2 = 0;
        jugador->efectos &= ~EFECTO_RAPIDO_CPU;
        return;
    }
    if ((jugador->efectos & EFECTO_RAPIDO_CPU) == EFECTO_RAPIDO_CPU) {
        jugador->desconocido_0E2 -= 1;
        if (jugador->desconocido_0E2 <= 0) {
            jugador->efectos &= ~EFECTO_RAPIDO_CPU;
        }
    } else {
        for (i = 0; i < JUGADORES_NUM; i++) {
            prestamo_jugador = &jugadores_2[i];
            if (((jugador != prestamo_jugador) && ((prestamo_jugador->type & INVISIBLE_JUGADOR_O_BOMBA) == 0) &&
                 (prestamo_jugador->type & EXISTE_JUGADOR)) &&
                ((variable_a2 = funcion_8001FD78(jugador, prestamo_jugador->pos[0], prestamo_jugador->pos[1], prestamo_jugador->pos[2]),
                  variable_a2 == 1))) {
                jugador->desconocido_0E2 += 1;
                if (jugador->desconocido_0E2 >= 0x3D) {
                    jugador->efectos |= EFECTO_RAPIDO_CPU;
                    if ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA) {
                        asignacion_inutil = jugador->type & INVISIBLE_JUGADOR_O_BOMBA;
                        funcion_800C90F4(indice_jugador, (jugador->id_personaje * 0x10) + 0x29008001);
                    }
                    if ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA) {
                        asignacion_inutil = variable_a2;
                        funcion_800C9060(indice_jugador, 0x19008011);
                    }
                }
                break;
            }
        }

        if (variable_a2 == 0) {
            jugador->desconocido_0E2 = 0;
        }
    }
}

void actualizar_duracion_derrape_jugador(Jugador* jugador) {
    if ((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) {
        jugador->duracion_derrape += 1;
        if (jugador->duracion_derrape > 100) {
            jugador->duracion_derrape = 100;
        }
    } else {
        jugador->duracion_derrape -= 1;
        if (jugador->duracion_derrape < 0) {
            jugador->duracion_derrape = 0;
        }
    }
}
