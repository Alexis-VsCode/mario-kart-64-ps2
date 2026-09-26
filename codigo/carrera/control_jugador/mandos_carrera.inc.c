// Mandos carrera

void manejar_pulsacion_a_para_todos_jugadores_durante_carrera(void) {
    u16 temporal_v0_3;
    u16 temporal_v0_4;
    u16 temporal_v0_5;
    u16 temporal_v0_6;

    switch (modo_pantalla_activo) {
        case MODO_PANTALLA_1P:
            switch (seleccion_modo) {
                case GRAN_PREMIO:
                    manejar_pulsacion_a_para_jugador_durante_carrera(jugador_uno, mando_uno, 0);
                    return;
                case CONTRARRELOJ:
                    if (dato_8015F890 != 1) {
                        manejar_pulsacion_a_para_jugador_durante_carrera(jugador_uno, mando_uno, 0);
                        temporal_v0_3 = jugador_dos->type;
                        if (((temporal_v0_3 & INVISIBLE_JUGADOR_O_BOMBA) == INVISIBLE_JUGADOR_O_BOMBA) &&
                            ((temporal_v0_3 & MODO_CINEMATICA_JUGADOR) != MODO_CINEMATICA_JUGADOR)) {
                            manejar_pulsacion_a_para_jugador_durante_carrera(jugador_dos, mando_seis, 1);
                        }
                        temporal_v0_4 = jugador_tres->type;
                        if (((temporal_v0_4 & INVISIBLE_JUGADOR_O_BOMBA) == INVISIBLE_JUGADOR_O_BOMBA) &&
                            ((temporal_v0_4 & MODO_CINEMATICA_JUGADOR) != MODO_CINEMATICA_JUGADOR)) {
                            manejar_pulsacion_a_para_jugador_durante_carrera(jugador_tres, mando_siete, 2);
                            return;
                        }
                    } else {
                        if ((jugador_uno->type & MODO_CINEMATICA_JUGADOR) != MODO_CINEMATICA_JUGADOR) {
                            manejar_pulsacion_a_para_jugador_durante_carrera(jugador_uno, mando_ocho, 0);
                        }
                        temporal_v0_5 = jugador_dos->type;
                        if (((temporal_v0_5 & INVISIBLE_JUGADOR_O_BOMBA) == INVISIBLE_JUGADOR_O_BOMBA) &&
                            ((temporal_v0_5 & MODO_CINEMATICA_JUGADOR) != MODO_CINEMATICA_JUGADOR)) {
                            manejar_pulsacion_a_para_jugador_durante_carrera(jugador_dos, mando_seis, 1);
                        }
                        temporal_v0_6 = jugador_tres->type;
                        if (((temporal_v0_6 & INVISIBLE_JUGADOR_O_BOMBA) == INVISIBLE_JUGADOR_O_BOMBA) &&
                            ((temporal_v0_6 & MODO_CINEMATICA_JUGADOR) != MODO_CINEMATICA_JUGADOR)) {
                            manejar_pulsacion_a_para_jugador_durante_carrera(jugador_tres, mando_siete, 2);
                            return;
                        }
                        return;
                    }

                    break;
            }
            break;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            manejar_pulsacion_a_para_jugador_durante_carrera(jugador_uno, mando_uno, 0);
            manejar_pulsacion_a_para_jugador_durante_carrera(jugador_dos, mando_dos, 1);
            return;
        case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
            manejar_pulsacion_a_para_jugador_durante_carrera(jugador_uno, mando_uno, 0);
            manejar_pulsacion_a_para_jugador_durante_carrera(jugador_dos, mando_dos, 1);
            manejar_pulsacion_a_para_jugador_durante_carrera(jugador_tres, mando_tres, 2);
            if (seleccion_cantidad_jugador_1 == 4) {
                manejar_pulsacion_a_para_jugador_durante_carrera(jugador_cuatro, mando_cuatro, 3);
            }
            break;
    }
}

s16 obtener_limitado_palanca_x_con_zona_muerta(struct Mando* mando) {
    s16 temporal_palanca_y_2;
    s16 temporal_palanca_x2_2;
    s16 temporal_palanca_y2_2;
    s16 temporal_palanca_x;

    temporal_palanca_x = mando->palanca_x_crudo;
    temporal_palanca_y_2 = mando->palanca_y_crudo;
    temporal_palanca_x2_2 = temporal_palanca_x;
    temporal_palanca_y2_2 = temporal_palanca_y_2;

    if (temporal_palanca_x > 0xC) {
        temporal_palanca_y2_2 = (temporal_palanca_y_2 * 0x000C) / temporal_palanca_x;
        temporal_palanca_x2_2 = 0x000C;
    }
    if (temporal_palanca_x2_2 < -0xC) {
        temporal_palanca_y2_2 = (temporal_palanca_y2_2 * 0x000C) / -temporal_palanca_x2_2;
        temporal_palanca_x2_2 = -0x000C;
    }
    if (temporal_palanca_y2_2 > 0xC) {
        temporal_palanca_x2_2 = (temporal_palanca_x2_2 * 0x000C) / temporal_palanca_y2_2;
        temporal_palanca_y2_2 = 0x000C;
    }
    if (temporal_palanca_y2_2 < -0xC) {
        temporal_palanca_x2_2 = (temporal_palanca_x2_2 * 0x000C) / -temporal_palanca_y2_2;
        temporal_palanca_y2_2 = -0x000C;
    }
    if ((((mando->palanca_x_crudo > -0xD) && (mando->palanca_x_crudo < 0xD)) && (mando->palanca_y_crudo > -0xD)) &&
        (mando->palanca_y_crudo < 0xD)) {
        temporal_palanca_x = 0;
        temporal_palanca_y_2 = 0;
    } else {
        temporal_palanca_x -= temporal_palanca_x2_2;
        temporal_palanca_y_2 -= temporal_palanca_y2_2;
    }
    if (temporal_palanca_x > 0x35) {
        temporal_palanca_y_2 = (temporal_palanca_y_2 * 0x0035) / temporal_palanca_x;
        temporal_palanca_x = 0x0035;
    }
    if (temporal_palanca_x < -0x35) {
        temporal_palanca_y_2 = (temporal_palanca_y_2 * 0x0035) / -temporal_palanca_x;
        temporal_palanca_x = -0x0035;
    }
    if (temporal_palanca_y_2 > 0x35) {
        temporal_palanca_x = (temporal_palanca_x * 0x0035) / temporal_palanca_y_2;
        temporal_palanca_y_2 = 0x0035;
    }
    if (temporal_palanca_y_2 < -0x35) {
        temporal_palanca_x = (temporal_palanca_x * 0x0035) / -temporal_palanca_y_2;
    }
    return temporal_palanca_x;
}

s16 obtener_limitado_palanca_y_con_zona_muerta(struct Mando* mando) {
    s16 temporal_palanca_y;
    s16 temporal_palanca_x2;
    s16 temporal_palanca_y2;
    s16 temporal_palanca_x_2;

    temporal_palanca_x_2 = mando->palanca_x_crudo;
    temporal_palanca_y = mando->palanca_y_crudo;
    temporal_palanca_x2 = temporal_palanca_x_2;
    temporal_palanca_y2 = temporal_palanca_y;

    if (temporal_palanca_x_2 > 0xC) {
        temporal_palanca_y2 = (temporal_palanca_y * 0x000C) / temporal_palanca_x_2;
        temporal_palanca_x2 = 0x000C;
    }
    if (temporal_palanca_x2 < -0xC) {
        temporal_palanca_y2 = (temporal_palanca_y2 * 0x000C) / -temporal_palanca_x2;
        temporal_palanca_x2 = -0x000C;
    }
    if (temporal_palanca_y2 > 0xC) {
        temporal_palanca_x2 = (temporal_palanca_x2 * 0x000C) / temporal_palanca_y2;
        temporal_palanca_y2 = 0x000C;
    }
    if (temporal_palanca_y2 < -0xC) {
        temporal_palanca_x2 = (temporal_palanca_x2 * 0x000C) / -temporal_palanca_y2;
        temporal_palanca_y2 = -0x000C;
    }
    if ((((mando->palanca_x_crudo > -0xD) && (mando->palanca_x_crudo < 0xD)) && (mando->palanca_y_crudo > -0xD)) &&
        (mando->palanca_y_crudo < 0xD)) {
        temporal_palanca_x_2 = 0;
        temporal_palanca_y = 0;
    } else {
        temporal_palanca_x_2 -= temporal_palanca_x2;
        temporal_palanca_y -= temporal_palanca_y2;
    }
    if (temporal_palanca_x_2 > 0x35) {
        temporal_palanca_y = (temporal_palanca_y * 0x0035) / temporal_palanca_x_2;
        temporal_palanca_x_2 = 0x0035;
    }
    if (temporal_palanca_x_2 < -0x35) {
        temporal_palanca_y = (temporal_palanca_y * 0x0035) / -temporal_palanca_x_2;
        temporal_palanca_x_2 = -0x0035;
    }
    if (temporal_palanca_y > 0x35) {
        temporal_palanca_x_2 = (temporal_palanca_x_2 * 0x0035) / temporal_palanca_y;
        temporal_palanca_y = 0x0035;
    }
    if (temporal_palanca_y < -0x35) {
        temporal_palanca_x_2 = (temporal_palanca_x_2 * 0x0035) / -temporal_palanca_y;
        temporal_palanca_y = -0x0035;
    }
    return temporal_palanca_y;
}

void funcion_80038BE4(Jugador* jugador, s16 parametro1) {
    jugador->actual_rapidez += (f32) parametro1;
    if (jugador->actual_rapidez < 0.0f) {
        jugador->actual_rapidez = 0.0f;
    }
    if (jugador->actual_rapidez >= 250.0f) {
        jugador->actual_rapidez = 250.0f;
    }
    jugador->kart_props |= ACELERADOR;
    jugador->desconocido_08C = (jugador->actual_rapidez * jugador->actual_rapidez) / 25.0f;
}

void funcion_80038C6C(Jugador* jugador, SIN_USO Camara* camara, s8 id_pantalla, s8 id_jugador) {
    Vec3f sp114 = { 0.0, 0.0, 1.0 };
    Vec3f sp108 = { 0.0, 0.0, 0.0 };
    Vec3f sp_fc = { 0.0, 0.0, 0.0 };
    Vec3f sp_f0 = { 0.0, 0.0, 0.0 };
    f32 siguiente_x;
    f32 siguiente_y;
    f32 siguiente_z;
    f32 pos_x;
    f32 pos_y;
    f32 pos_z;
    f32 sqrt;

    f32 dividir_optimizar;
    SIN_USO s32 relleno2[10];
    f32 sp_a4;
    f32 sp_a0;
    f32 sp9_c;
    f32 distancia_superficie;
    SIN_USO s32 relleno3;
    Vec3f velocidad_nuevo;
    Vec3f sp7_c;
    SIN_USO s32 relleno[10];

    jugador->desconocido_084 = -10.0f;
    jugador->desconocido_088 = 28.0f;
    jugador->arriba_rapidez = 250.0f;
    funcion_8002B830(jugador, id_jugador, id_pantalla);
    aplicar_efecto(jugador, id_jugador, id_pantalla);
    jugador->rotacion[1] += jugador->desconocido_078;
    sp_f0[0] = 0;
    sp_f0[1] = 0;
    sp_f0[2] = 0;
    funcion_8002AB70(jugador);
    sp_a4 = 0 * (jugador->desconocido_064[0] + sp_fc[0]);
    sp_a0 = -1 * jugador->gravedad_kart;
    sp9_c = 0 * (jugador->desconocido_064[2] + sp_fc[2]);
    sp108[2] = 0;
    sp108[1] = 0;
    sp108[0] = 0;
    transformar_mat3_vec3f_mtxf(sp108, jugador->matriz_orientacion);
    sp_a4 += sp108[0];
    sp9_c += sp108[2];
    sp114[2] = jugador->desconocido_08C;
    transformar_mat3_vec3f_mtxf(sp114, jugador->matriz_orientacion);

    velocidad_nuevo[0] = jugador->velocidad[0];
    velocidad_nuevo[1] = jugador->velocidad[1];
    velocidad_nuevo[2] = jugador->velocidad[2];

    velocidad_nuevo[0] += ((((((sp114[0] + sp_a4) + sp_f0[0])) - (velocidad_nuevo[0] * (0.12 * (jugador->friccion_kart)))) / 6000.0) / 1);
    velocidad_nuevo[2] += ((((((sp114[2] + sp9_c) + sp_f0[2])) - (velocidad_nuevo[2] * (0.12 * (jugador->friccion_kart)))) / 6000.0) / 1);
    velocidad_nuevo[1] += ((((((sp114[1] + sp_a0) + sp_f0[1])) - (velocidad_nuevo[1] * (0.12 * (jugador->friccion_kart)))) / 6000.0) / 1);
    if ((jugador->kart_props & CARRERA_GP_PERDER) == CARRERA_GP_PERDER) {
        jugador->kart_props &= ~CARRERA_GP_PERDER;
    }

    pos_x = jugador->pos[0];
    pos_y = jugador->pos[1];
    pos_z = jugador->pos[2];

    jugador->pos_viejo[0] = jugador->pos[0];
    jugador->pos_viejo[1] = jugador->pos[1];
    jugador->pos_viejo[2] = jugador->pos[2];

    siguiente_x = pos_x + jugador->velocidad[0];
    siguiente_y = pos_y + jugador->velocidad[1];
    siguiente_z = pos_z + jugador->velocidad[2];
    funcion_8002AAC0(jugador);
    siguiente_y += jugador->velocidad_salto_kart;
    siguiente_y -= 0.02;
    colision_terreno_actor(&jugador->colision, jugador->tamanio_caja_envolvente, siguiente_x, siguiente_y, siguiente_z, jugador->pos_viejo[0],
                            jugador->pos_viejo[1], jugador->pos_viejo[2]);
    jugador->desconocido_058 = 0;
    jugador->desconocido_060 = 0;
    jugador->desconocido_05C = 1.0f;
    calcular_matriz_orientacion(jugador->matriz_orientacion, 0, 1.0f, 0, jugador->rotacion[1]);
    jugador->efectos |= EFECTO_EN_EL_AIRE;
    jugador->desconocido_0C2 += 1;
    distancia_superficie = jugador->colision.distancia_superficie[2];
    if (distancia_superficie <= 0) {
        jugador->desconocido_0C2 = 0;
        jugador->efectos &= ~EFECTO_SALTO;
        jugador->efectos &= ~EFECTO_EN_EL_AIRE;
        jugador->velocidad_salto_kart = jugador->desconocido_0C2;
    }
    distancia_superficie = jugador->colision.distancia_superficie[2];
    if (distancia_superficie <= 0) {
        funcion_8003F46C(jugador, sp7_c, velocidad_nuevo, sp108, &distancia_superficie, &siguiente_x, &siguiente_y, &siguiente_z);
    }
    distancia_superficie = jugador->colision.distancia_superficie[0];
    if (distancia_superficie < 0) {
        funcion_8003F734(jugador, sp7_c, velocidad_nuevo, &distancia_superficie, &siguiente_x, &siguiente_y, &siguiente_z);
        funcion_8002C954(jugador, id_jugador, velocidad_nuevo);
    }
    distancia_superficie = jugador->colision.distancia_superficie[1];
    if (distancia_superficie < 0) {
        funcion_8003FBAC(jugador, sp7_c, velocidad_nuevo, &distancia_superficie, &siguiente_x, &siguiente_y, &siguiente_z);
        funcion_8002C954(jugador, id_jugador, velocidad_nuevo);
    }
    distancia_superficie = jugador->colision.distancia_superficie[0];
    if (distancia_superficie >= 0) {
        distancia_superficie = jugador->colision.distancia_superficie[1];
        if (distancia_superficie >= 0) {
            jugador->desconocido_046 &= 0xFFDF;
        }
    }
    jugador->desconocido_074 = calcular_altura_superficie(siguiente_x, siguiente_y, siguiente_z, jugador->colision.indice_zx_malla);
    funcion_80029B4C(jugador, siguiente_x, siguiente_y, siguiente_z);
    funcion_8002AE38(jugador, id_jugador, pos_x, pos_z, siguiente_x, siguiente_z);
    sqrt = (velocidad_nuevo[0] * velocidad_nuevo[0]) + (velocidad_nuevo[2] * velocidad_nuevo[2]);
    jugador->anterior_rapidez = jugador->speed;
    jugador->speed = sqrtf(sqrt);

    jugador->pos[0] = siguiente_x;
    jugador->pos[2] = siguiente_z;
    jugador->pos[1] = siguiente_y;

    jugador->desconocido_064[0] = sp108[0];
    jugador->desconocido_064[2] = sp108[2];

    jugador->velocidad[0] = velocidad_nuevo[0];
    jugador->velocidad[1] = velocidad_nuevo[1];
    jugador->velocidad[2] = velocidad_nuevo[2];

    velocidad_ultimo_jugador[id_jugador][0] = velocidad_nuevo[0];
    velocidad_ultimo_jugador[id_jugador][1] = velocidad_nuevo[1];
    velocidad_ultimo_jugador[id_jugador][2] = velocidad_nuevo[2];

    if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
        if (kart_arriba_rapidez_tabla[jugador->id_personaje] < jugador->speed) {
            dividir_optimizar = kart_arriba_rapidez_tabla[jugador->id_personaje] / jugador->speed;
            jugador->velocidad[0] *= dividir_optimizar;
            jugador->velocidad[1] *= dividir_optimizar;
            jugador->velocidad[2] *= dividir_optimizar;
            jugador->speed = kart_arriba_rapidez_tabla[jugador->id_personaje];
        }
    }
    if ((jugador->kart_props & ARRIBA_ATRAS) == ARRIBA_ATRAS) {
        if (jugador->speed > 1.0f) {
            jugador->velocidad[0] *= 1.0f / jugador->speed;
            jugador->velocidad[1] *= 1.0f / jugador->speed;
            jugador->velocidad[2] *= 1.0f / jugador->speed;
            jugador->speed = 1.0f;
        }
    }
    if (jugador->colision.distancia_superficie[2] >= 500.0f) {
        jugador->desconocido_078 /= 2;
    }
    funcion_8002C4F8(jugador, id_jugador);
}
