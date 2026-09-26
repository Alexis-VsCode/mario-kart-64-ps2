// Movimiento cpu

void funcion_8002E594(Jugador* jugador, SIN_USO Camara* camara, s8 id_pantalla, s8 id_jugador) {
    Vec3f sp_ec = { 0.0f, 0.0f, 1.0f };
    Vec3f sp_e0 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp_d4 = { 0.0f, 0.0f, 0.0f };
    f32 siguiente_x;
    f32 siguiente_y;
    f32 siguiente_z;
    f32 multiplicador_rapidez_arriba;
    SIN_USO s32 relleno;
    f32 pos_x;
    f32 pos_y;
    f32 pos_z;
    SIN_USO s32 relleno2[12];
    f32 gravedad_x;
    f32 gravedad_y;
    f32 gravedad_z;
    f32 distancia_superficie;
    SIN_USO s32 relleno3[4];
    f32 temporal_;
    Vec3f velocidad_nuevo;
    Vec3f sp48;
    s16 sp46;
    funcion_8002B830(jugador, id_jugador, id_pantalla);
    if ((((((((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
             ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO)) ||
            ((jugador->efectos & TEMPRANO_INICIO_TROMPO_EFECTO) == TEMPRANO_INICIO_TROMPO_EFECTO)) ||
           ((jugador->efectos & desconocido_efecto_0_x_80000) == desconocido_efecto_0_x_80000)) ||
          ((jugador->efectos & desconocido_efecto_0_x_800000) == desconocido_efecto_0_x_800000)) ||
         ((jugador->efectos & EFECTO_GOLPE_RAYO) == EFECTO_GOLPE_RAYO)) ||
        (jugador->kart_props & sin_uso_0_x_800)) {
        sp46 = 1;
    } else {
        sp46 = 0;
    }
    aplicar_efecto(jugador, id_jugador, id_pantalla);
    funcion_8002AB70(jugador);
    funcion_8002FCA8(jugador, id_jugador);
    if ((((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
         ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO)) ||
        ((jugador->efectos & EFECTO_GOLPE_RAYO) == EFECTO_GOLPE_RAYO)) {
        gravedad_x =
            -1 * (jugador->desconocido_064[0]) + (((-jugador->colision.vector_orientacion[0]) * jugador->gravedad_kart) * 0.1);
        gravedad_y = (-jugador->colision.vector_orientacion[1]) * jugador->gravedad_kart;
        gravedad_z =
            -1 * (jugador->desconocido_064[2]) + (((-jugador->colision.vector_orientacion[2]) * jugador->gravedad_kart) * 0.1);
    } else {
        gravedad_x = -1 * jugador->desconocido_064[0];
        gravedad_y = -1 * jugador->gravedad_kart;
        gravedad_z = -1 * jugador->desconocido_064[2];
    }
    funcion_8002C7E4(jugador, id_jugador, id_pantalla);
    if (sp46 == 1) {
        calcular_matriz_orientacion(jugador->matriz_orientacion, jugador->desconocido_058, jugador->desconocido_05C, jugador->desconocido_060,
                                     (s16) ((s32) jugador->rotacion[1]));
        calcular_matriz_orientacion(jugador->desconocido_150, jugador->desconocido_058, jugador->desconocido_05C, jugador->desconocido_060,
                                     (s16) ((s32) jugador->desconocido_0AE));
    } else {
        calcular_matriz_orientacion(jugador->matriz_orientacion, jugador->desconocido_058, jugador->desconocido_05C, jugador->desconocido_060,
                                     (s16) ((s32) jugador->rotacion[1]));
    }
    sp_ec[2] = funcion_80030150(jugador, id_jugador);
    if (sp46 == 1) {
        transformar_mat3_vec3f_mtxf(sp_ec, jugador->desconocido_150);
    } else {
        transformar_mat3_vec3f_mtxf(sp_ec, jugador->matriz_orientacion);
    }
    velocidad_nuevo[0] = jugador->velocidad[0];
    velocidad_nuevo[1] = jugador->velocidad[1];
    velocidad_nuevo[2] = jugador->velocidad[2];
    if ((jugador->desconocido_10C < 3) && ((jugador->desconocido_256) < 3) &&
        ((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) != GOLPE_POR_CAPARAZON_VERDE_EFECTO) &&
        ((jugador->efectos & EFECTO_ERROR_EXPLOSION) != EFECTO_ERROR_EXPLOSION) &&
        ((jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA) != GOLPE_POR_EFECTO_ESTRELLA)) {
        velocidad_nuevo[0] +=
            (((((sp_ec[0] + gravedad_x) + sp_d4[0])) - (velocidad_nuevo[0] * (0.12 * jugador->friccion_kart))) / 6000) /
            ((jugador->desconocido_20C * 5.0f) + 1.0f);
        velocidad_nuevo[2] +=
            (((((sp_ec[2] + gravedad_z) + sp_d4[2])) - (velocidad_nuevo[2] * (0.12 * jugador->friccion_kart))) / 6000) /
            ((jugador->desconocido_20C * 5.0f) + 1.0f);
    } else {
        velocidad_nuevo[0] +=
            ((((f64) (sp_ec[0] + gravedad_x + sp_d4[0]) - (velocidad_nuevo[0] * (0.2 * (f64) jugador->friccion_kart))) / 6000) *
             0.08);
        velocidad_nuevo[2] +=
            ((((f64) (sp_ec[2] + gravedad_z + sp_d4[2]) - (velocidad_nuevo[2] * (0.2 * (f64) jugador->friccion_kart))) / 6000) *
             0.08);
    }
    velocidad_nuevo[1] += (((((sp_ec[1] + gravedad_y) + sp_d4[1])) - (velocidad_nuevo[1] * (0.12 * jugador->friccion_kart))) / 6000) /
                      jugador->desconocido_dac;

    if (((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == MANTENIDO_POR_LAKITU) ||
        ((jugador->lakitu_props & LAKITU_ESCENA) == LAKITU_ESCENA)) {
        velocidad_nuevo[0] = 0.0f;
        velocidad_nuevo[1] = 0.0f;
        velocidad_nuevo[2] = 0.0f;
    }
    pos_x = jugador->pos[0];
    pos_y = jugador->pos[1];
    pos_z = jugador->pos[2];

    jugador->pos_viejo[0] = jugador->pos[0];
    jugador->pos_viejo[1] = jugador->pos[1];
    jugador->pos_viejo[2] = jugador->pos[2];

    siguiente_x = pos_x + jugador->velocidad[0] + dato_8018CE10[id_jugador].desconocido_04[0];
    siguiente_y = pos_y + jugador->velocidad[1];
    siguiente_z = pos_z + jugador->velocidad[2] + dato_8018CE10[id_jugador].desconocido_04[2];
    funcion_8002AAC0(jugador);
    siguiente_y += jugador->velocidad_salto_kart;
    colision_terreno_actor(&jugador->colision, jugador->tamanio_caja_envolvente, siguiente_x, siguiente_y, siguiente_z, jugador->pos_viejo[0],
                            jugador->pos_viejo[1], jugador->pos_viejo[2]);
    jugador->efectos |= EFECTO_EN_EL_AIRE;
    jugador->desconocido_0C2 += 1;
    jugador->desconocido_058 = 0.0f;
    jugador->desconocido_060 = 0.0f;
    jugador->desconocido_05C = 1.0f;
    distancia_superficie = jugador->colision.distancia_superficie[2];
    if (distancia_superficie <= 0.0f) {
        jugador->efectos &= ~EFECTO_SALTO;
        jugador->efectos &= ~EFECTO_EN_EL_AIRE;
        if ((((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) != GOLPE_POR_CAPARAZON_VERDE_EFECTO) &&
             ((jugador->efectos & EFECTO_ERROR_EXPLOSION) != EFECTO_ERROR_EXPLOSION)) &&
            ((jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA) != GOLPE_POR_EFECTO_ESTRELLA)) {
            if (jugador->desconocido_0C2 >= 0x1C) {
                if (jugador->desconocido_0C2 >= 0x32) {
                    jugador->desconocido_0C2 = 0x0032;
                }
                jugador->desconocido_DB4.unk18 = 0;
                jugador->graficos_kart |= POOMP;
                jugador->desconocido_DB4.desconocido_c = 3.0f;
                if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
                    ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
                    funcion_800CADD0((u8) id_jugador, ((f32) jugador->desconocido_0C2) / 50.0f);
                }
                if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
                    jugador->kart_props |= ACELERADOR_VUELCO_PUBLICAR;
                }
            }
            if (((jugador->desconocido_0C2 < 0x1C) && (jugador->desconocido_0C2 >= 0xA)) &&
                (((jugador->speed / 18.0f) * 216.0f) >= 20.0f)) {
                jugador->desconocido_DB4.desconocido_c = 2.0f;
                jugador->desconocido_DB4.unk18 = 0;
                if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
                    ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
                    funcion_800CADD0((u8) id_jugador, ((f32) jugador->desconocido_0C2) / 50.0f);
                }
                if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
                    jugador->kart_props |= ACELERADOR_VUELCO_PUBLICAR;
                }
            }
            jugador->desconocido_0C2 = 0;
        } else {
            if (jugador->desconocido_0C2 >= 0xA) {
                if (jugador->desconocido_0C2 >= 0x32) {
                    jugador->desconocido_0C2 = 0x0032;
                }
                if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
                    ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
                    funcion_800CADD0((u8) id_jugador, ((f32) jugador->desconocido_0C2) / 20.0f);
                }
                if (jugador->desconocido_0C2 >= 0x28) {
                    jugador->desconocido_0C2 = 0x0014;
                }
                if ((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) == GOLPE_POR_CAPARAZON_VERDE_EFECTO) {
                    jugador->desconocido_0C2 /= 6.5;
                    jugador->tiron_salto_kart = 0.06f;
                    jugador->aceleracion_salto_kart = 0.0f;
                } else {
                    jugador->desconocido_0C2 /= 7.5;
                    jugador->tiron_salto_kart = 0.06f;
                    jugador->aceleracion_salto_kart = 0.0f;
                    if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
                        jugador->kart_props |= ACELERADOR_VUELCO_PUBLICAR;
                    }
                }
            } else {
                jugador->desconocido_0C2 = 0;
            }
        }
        jugador->velocidad_salto_kart = (f32) jugador->desconocido_0C2;
    }
    distancia_superficie = jugador->colision.distancia_superficie[2];
    if (distancia_superficie <= 0.0f) {
        funcion_8003F46C(jugador, sp48, velocidad_nuevo, sp_e0, &distancia_superficie, &siguiente_x, &siguiente_y, &siguiente_z);
    }
    distancia_superficie = jugador->colision.distancia_superficie[0];
    if (distancia_superficie < 0.0f) {
        funcion_8003F734(jugador, sp48, velocidad_nuevo, &distancia_superficie, &siguiente_x, &siguiente_y, &siguiente_z);
        funcion_8002C954(jugador, id_jugador, velocidad_nuevo);
        alternativo_desacelerar_jugador(jugador, 6.0f);
    }
    distancia_superficie = jugador->colision.distancia_superficie[1];
    if (distancia_superficie < 0.0f) {
        funcion_8003FBAC(jugador, sp48, velocidad_nuevo, &distancia_superficie, &siguiente_x, &siguiente_y, &siguiente_z);
        funcion_8002C954(jugador, id_jugador, velocidad_nuevo);
        alternativo_desacelerar_jugador(jugador, 6.0f);
    }
    distancia_superficie = jugador->colision.distancia_superficie[0];
    if (distancia_superficie >= 0.0f) {
        distancia_superficie = jugador->colision.distancia_superficie[1];
        if (distancia_superficie >= 0.0f) {
            jugador->desconocido_046 &= 0xFFDF;
            if (jugador->desconocido_256 != 0) {
                jugador->desconocido_256++;
                if ((jugador->desconocido_256) >= 0xA) {
                    jugador->desconocido_256 = 0;
                }
            }
        }
    }
    if (((funcion_802ABDB8(jugador->colision.indice_zx_malla) != 0) &&
         ((jugador->efectos & EFECTO_VUELCO_TERRENO) != EFECTO_VUELCO_TERRENO)) &&
        (((jugador->speed / 18.0f) * 216.0f) >= 20.0f)) {
        if ((!(jugador->lakitu_props & MANTENIDO_POR_LAKITU)) || (!(jugador->lakitu_props & LAKITU_ESCENA))) {
            funcion_8008F494(jugador, id_jugador);
        }
    } else if (((!(jugador->efectos & EFECTO_EN_EL_AIRE)) && (funcion_802ABDB8(jugador->colision.indice_zx_malla) == 0)) &&
               (jugador->efectos & EFECTO_VUELCO_TERRENO)) {
        funcion_8008F5A4(jugador, id_jugador);
    }
    jugador->desconocido_074 = calcular_altura_superficie(siguiente_x, siguiente_y, siguiente_z, jugador->colision.indice_zx_malla);
    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        (((modo_pantalla_activo == MODO_PANTALLA_1P) || (modo_pantalla_activo == PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL)) ||
         (modo_pantalla_activo == PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL))) {
        funcion_80029B4C(jugador, siguiente_x, siguiente_y, siguiente_z);
    } else {
        funcion_8002A194(jugador, siguiente_x, siguiente_y, siguiente_z);
    }
    funcion_8002AE38(jugador, id_jugador, pos_x, pos_z, siguiente_x, siguiente_z);
    temporal_ = (velocidad_nuevo[0] * velocidad_nuevo[0]) + (velocidad_nuevo[2] * velocidad_nuevo[2]);
    jugador->anterior_rapidez = jugador->speed;
    jugador->speed = sqrtf(temporal_);
    if ((((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) != GOLPE_POR_CAPARAZON_VERDE_EFECTO) && (jugador->desconocido_08C <= 0) &&
         (jugador->speed < 0.13)) ||
        (((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) != GOLPE_POR_CAPARAZON_VERDE_EFECTO) && (jugador->desconocido_08C <= 0) &&
         (jugador->speed < 0.20) && ((jugador->efectos & EFECTO_FRENADO) == EFECTO_FRENADO))) {
        velocidad_nuevo[0] = velocidad_nuevo[0] + (-1 * velocidad_nuevo[0]);
        velocidad_nuevo[2] = velocidad_nuevo[2] + (-1 * velocidad_nuevo[2]);
    } else {
        jugador->pos[0] = siguiente_x;
        jugador->pos[2] = siguiente_z;
    }
    jugador->pos[1] = siguiente_y;
    jugador->desconocido_064[0] = sp_e0[0];
    jugador->desconocido_064[2] = sp_e0[2];
    jugador->velocidad[0] = velocidad_nuevo[0];
    jugador->velocidad[1] = velocidad_nuevo[1];
    jugador->velocidad[2] = velocidad_nuevo[2];
    if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
        if (kart_arriba_rapidez_tabla[jugador->id_personaje] < jugador->speed) {
            multiplicador_rapidez_arriba = kart_arriba_rapidez_tabla[jugador->id_personaje] / jugador->speed;
            jugador->velocidad[0] *= multiplicador_rapidez_arriba;
            jugador->velocidad[1] *= multiplicador_rapidez_arriba;
            jugador->velocidad[2] *= multiplicador_rapidez_arriba;
            jugador->speed = kart_arriba_rapidez_tabla[jugador->id_personaje];
        }
    }
    funcion_8002C4F8(jugador, id_jugador);
}

void movimiento_cpu_control(Jugador* jugador, SIN_USO Camara* camara, s8 id_pantalla, s8 id_jugador) {
    Vec3f sp_f4 = { 0.0f, 0.0f, 1.0f };
    SIN_USO Vec3f sp_e8 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp_dc = { 0.0f, 0.0f, 0.0f };
    Vec3f sp_d0 = { 0.0f, 0.0f, 0.0f };
    f32 siguiente_x;
    SIN_USO s32 relleno;
    f32 siguiente_z;
    SIN_USO s32 relleno2[15];
    f32 sp84;
    SIN_USO s32 relleno3;
    f32 sp7_c;
    SIN_USO s32 relleno4[2];
    Vec3f velocidad_nuevo;
    SIN_USO f32 relleno5[7];
    f32 a_raiz;
    f32 multiplicador_rapidez_arriba;
    f32 siguiente_y;
    jugador->efectos |= EFECTO_CARRERA_PERDIDO;
    jugador->kart_props |= CARRERA_GP_PERDER;
    siguiente_y = camino_y_jugador[id_jugador];
    jugador->duracion_derrape = 0;
    jugador->efectos &= ~EFECTO_DERRAPANDO;
    funcion_8002B830(jugador, id_jugador, id_pantalla);
    aplicar_efecto(jugador, id_jugador, id_pantalla);
    sp84 = 0 * jugador->desconocido_064[0] + sp_dc[0];
    sp7_c = 0 * jugador->desconocido_064[2] + sp_dc[2];
    jugador->desconocido_10C = 0;
    jugador->desconocido_256 = 0;
    jugador->efectos &= ~EFECTO_GOLPE_ENEMIGO;
    sp_f4[2] = funcion_80030150(jugador, id_jugador);
    transformar_mat3_vec3f_mtxf(sp_f4, jugador->matriz_orientacion);
    velocidad_nuevo[0] = jugador->velocidad[0];
    velocidad_nuevo[1] = 0;
    velocidad_nuevo[2] = jugador->velocidad[2];
    velocidad_nuevo[0] += (((sp_f4[0] + sp84) + sp_d0[0]) - (velocidad_nuevo[0] * (0.12 * jugador->friccion_kart))) / 6000.0;
    velocidad_nuevo[2] += (((sp_f4[2] + sp7_c) + sp_d0[2]) - (velocidad_nuevo[2] * (0.12 * jugador->friccion_kart))) / 6000.0;
    jugador->pos_viejo[0] = jugador->pos[0];
    jugador->pos_viejo[1] = siguiente_y;
    jugador->pos_viejo[2] = jugador->pos[2];
    siguiente_x = jugador->pos[0] + jugador->velocidad[0];
    siguiente_z = jugador->pos[2] + jugador->velocidad[2];
    jugador->desconocido_0C0 = 0;
    jugador->tiron_salto_kart = 0;
    jugador->aceleracion_salto_kart = 0;
    jugador->velocidad_salto_kart = 0;
    calcular_matriz_orientacion(jugador->matriz_orientacion, jugador->desconocido_058, jugador->desconocido_05C, jugador->desconocido_060,
                                 jugador->rotacion[1]);
    jugador->desconocido_0C2 = 0;
    jugador->efectos &= ~EFECTO_SALTO;
    jugador->efectos &= ~EFECTO_EN_EL_AIRE;
    jugador->acel_pendiente = 0;
    jugador->desconocido_206 = 0;
    a_raiz = (velocidad_nuevo[0] * velocidad_nuevo[0]) + (velocidad_nuevo[2] * velocidad_nuevo[2]);
    jugador->anterior_rapidez = jugador->speed;
    jugador->speed = sqrtf(a_raiz);
    jugador->pos[0] = siguiente_x;
    jugador->pos[2] = siguiente_z;
    jugador->pos[1] = siguiente_y;
    jugador->desconocido_064[0] = 0;
    jugador->desconocido_064[2] = 0;
    jugador->velocidad[0] = velocidad_nuevo[0];
    jugador->velocidad[1] = velocidad_nuevo[1];
    jugador->velocidad[2] = velocidad_nuevo[2];
    velocidad_ultimo_jugador[id_jugador][0] = velocidad_nuevo[0];
    velocidad_ultimo_jugador[id_jugador][1] = velocidad_nuevo[1];
    velocidad_ultimo_jugador[id_jugador][2] = velocidad_nuevo[2];
    if (kart_arriba_rapidez_tabla[jugador->id_personaje] < jugador->speed) {
        multiplicador_rapidez_arriba = kart_arriba_rapidez_tabla[jugador->id_personaje] / jugador->speed;
        jugador->velocidad[0] *= multiplicador_rapidez_arriba;
        jugador->velocidad[1] *= multiplicador_rapidez_arriba;
        jugador->velocidad[2] *= multiplicador_rapidez_arriba;
        jugador->speed = kart_arriba_rapidez_tabla[jugador->id_personaje];
    }
}

void funcion_8002F730(Jugador* jugador, SIN_USO Camara* camara, SIN_USO s8 id_pantalla, s8 id_jugador) {
    Vec3f sp_f4 = { 0.0f, 0.0f, 1.0f };
    Vec3f sp_e8 = { 0.0f, 0.0f, 0.0f };
    SIN_USO Vec3f sp_dc = { 0.0f, 0.0f, 0.0f };
    Vec3f sp_d0 = { 0.0f, 0.0f, 0.0f };
    f32 siguiente_x;
    f32 siguiente_y;
    f32 siguiente_z;

    f32 pos_x;
    f32 pos_y;
    f32 pos_z;
    f32 multiplicador_rapidez_arriba;
    SIN_USO s32 relleno[11];
    f32 sp84;
    SIN_USO s32 relleno2;
    f32 sp7_c;
    f32 distancia_superficie;
    f32 sqrt;
    Vec3f velocidad_nuevo;
    Vec3f sp5_c;
    SIN_USO s32 relleno3[3];

    funcion_80037BB4(jugador, sp_d0);
    sp84 = jugador->desconocido_064[0] * 0;
    sp7_c = jugador->desconocido_064[2] * 0;
    sp_f4[2] = funcion_80030150(jugador, id_jugador);

    transformar_mat3_vec3f_mtxf(sp_f4, jugador->matriz_orientacion);

    velocidad_nuevo[0] = jugador->velocidad[0];
    velocidad_nuevo[1] = jugador->velocidad[1];
    velocidad_nuevo[2] = jugador->velocidad[2];

    velocidad_nuevo[0] += (((f64) (sp_f4[0] + sp84) - (velocidad_nuevo[0] * 780.0)) / 6500.0);
    velocidad_nuevo[2] += (((f64) (sp_f4[2] + sp7_c) - (velocidad_nuevo[2] * 780.0)) / 6500.0);
    velocidad_nuevo[1] += (((f64) (sp_f4[1] + -1100.0f) - (velocidad_nuevo[1] * 780.0)) / 6500.0);

    pos_x = jugador->pos[0];
    pos_y = jugador->pos[1];
    pos_z = jugador->pos[2];

    jugador->pos_viejo[0] = jugador->pos[0];
    jugador->pos_viejo[1] = jugador->pos[1];
    jugador->pos_viejo[2] = jugador->pos[2];

    siguiente_x = jugador->velocidad[0] + pos_x;
    siguiente_y = jugador->velocidad[1] + pos_y;
    siguiente_z = jugador->velocidad[2] + pos_z;

    funcion_8002AAC0(jugador);

    siguiente_y += jugador->velocidad_salto_kart;
    colision_terreno_actor(&jugador->colision, jugador->tamanio_caja_envolvente, siguiente_x, siguiente_y, siguiente_z, jugador->pos_viejo[0],
                            jugador->pos_viejo[1], jugador->pos_viejo[2]);
    jugador->desconocido_058 = 0.0f;
    jugador->desconocido_05C = 1.0f;
    jugador->desconocido_060 = 0.0f;
    calcular_matriz_orientacion(jugador->matriz_orientacion, 0.0f, 1.0f, 0.0f, (s16) (s32) jugador->rotacion[1]);
    jugador->efectos &= ~EFECTO_EN_EL_AIRE;
    distancia_superficie = jugador->colision.distancia_superficie[2];
    if (distancia_superficie <= 0.0f) {
        if (1) {};
        funcion_8003F46C(jugador, sp5_c, velocidad_nuevo, sp_e8, &distancia_superficie, &siguiente_x, &siguiente_y, &siguiente_z);
    }
    jugador->desconocido_074 = calcular_altura_superficie(siguiente_x, siguiente_y, siguiente_z, jugador->colision.indice_zx_malla);
    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        ((modo_pantalla_activo == MODO_PANTALLA_1P) || (modo_pantalla_activo == PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL) ||
         (modo_pantalla_activo == PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL))) {
        funcion_80029B4C(jugador, siguiente_x, siguiente_y, siguiente_z);
    } else {
        funcion_8002A194(jugador, siguiente_x, siguiente_y, siguiente_z);
    }
    funcion_8002AE38(jugador, id_jugador, pos_x, pos_z, siguiente_x, siguiente_z);
    sqrt = (velocidad_nuevo[0] * velocidad_nuevo[0]) + (velocidad_nuevo[1] * velocidad_nuevo[1]) + (velocidad_nuevo[2] * velocidad_nuevo[2]);
    jugador->anterior_rapidez = jugador->speed;
    jugador->speed = sqrtf(sqrt);
    if (((jugador->desconocido_08C <= 0.0f) && ((f64) jugador->speed < 0.13)) ||
        ((jugador->desconocido_08C <= 0.0f) && ((f64) jugador->speed < 0.2) &&
         ((jugador->efectos & EFECTO_FRENADO) == EFECTO_FRENADO))) {
        velocidad_nuevo[0] = velocidad_nuevo[0] + (velocidad_nuevo[0] * -1.0f);
        velocidad_nuevo[2] = velocidad_nuevo[2] + (velocidad_nuevo[2] * -1.0f);
    } else {
        jugador->pos[0] = siguiente_x;
        jugador->pos[2] = siguiente_z;
    }
    jugador->pos[1] = siguiente_y - 0.018;

    jugador->desconocido_064[0] = sp_e8[0];
    jugador->desconocido_064[2] = sp_e8[2];

    jugador->velocidad[0] = velocidad_nuevo[0];
    jugador->velocidad[1] = velocidad_nuevo[1];
    jugador->velocidad[2] = velocidad_nuevo[2];

    velocidad_ultimo_jugador[id_jugador][0] = velocidad_nuevo[0];
    velocidad_ultimo_jugador[id_jugador][1] = velocidad_nuevo[1];
    velocidad_ultimo_jugador[id_jugador][2] = velocidad_nuevo[2];

    if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
        if (kart_arriba_rapidez_tabla[jugador->id_personaje] < jugador->speed) {
            multiplicador_rapidez_arriba = kart_arriba_rapidez_tabla[jugador->id_personaje] / jugador->speed;
            jugador->velocidad[0] *= multiplicador_rapidez_arriba;
            jugador->velocidad[1] *= multiplicador_rapidez_arriba;
            jugador->velocidad[2] *= multiplicador_rapidez_arriba;
            jugador->speed = kart_arriba_rapidez_tabla[jugador->id_personaje];
        }
    }
}

void funcion_8002FCA8(Jugador* jugador, s8 indice_jugador) {
    f32 variable_f0;
    f32 variable_f12;
    s32 temporal_lo;
    s32 variable_v1;

    variable_f0 = 0.0f;
    if ((jugador->efectos & EFECTO_ESTRELLA) != EFECTO_ESTRELLA) {
        if ((s32) jugador->ruedas[DERECHA_ATRAS].tipo_superficie < 0xF) {
            variable_f0 += dato_800E2A90[jugador->id_personaje][jugador->ruedas[DERECHA_ATRAS].tipo_superficie];
        }
        if ((s32) jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie < 0xF) {
            variable_f0 += dato_800E2A90[jugador->id_personaje][jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie];
        }
        if ((s32) jugador->ruedas[DERECHA_FRENTE].tipo_superficie < 0xF) {
            variable_f0 += dato_800E2AB0[jugador->id_personaje][jugador->ruedas[DERECHA_FRENTE].tipo_superficie];
        }
        if ((s32) jugador->ruedas[IZQUIERDA_FRENTE].tipo_superficie < 0xF) {
            variable_f0 += dato_800E2AB0[jugador->id_personaje][jugador->ruedas[IZQUIERDA_FRENTE].tipo_superficie];
        }
    }
    if (dato_801652C0[indice_jugador] & 4) {
        variable_v1 = 2;
    } else {
        variable_v1 = 0;
    }
    if ((jugador->actual_rapidez >= 200.0f) && (variable_v1 == 2)) {
        temporal_lo = (s16) jugador->desconocido_0C0 / GRADOS(1);
        if ((temporal_lo > 0xF) || (temporal_lo < -0xF)) {
            variable_f0 += 1.0;
        }
    }
    if (((jugador->efectos & EFECTO_RAPIDO_CPU) == EFECTO_RAPIDO_CPU) && ((jugador->type & HUMANO_JUGADOR) != HUMANO_JUGADOR)) {
        variable_f0 = -3.0f;
    }

    if (jugador->desconocido_088 >= 0.0f) {
        variable_f12 = jugador->desconocido_088 * variable_f0;
    } else {
        variable_f12 = -jugador->desconocido_088 * variable_f0;
    }
    jugador->desconocido_208 = jugador->desconocido_088 - variable_f12;
}

void funcion_8002FE84(Jugador* jugador, f32 parametro1) {
    f32 temporal_f0_3;
    f32 variable_f0;
    s16 temporal_lo;
    s32 probar;

    if ((jugador->efectos & TEMPRANO_INICIO_TROMPO_EFECTO) == TEMPRANO_INICIO_TROMPO_EFECTO) {
        jugador->desconocido_098 = ((jugador->actual_rapidez * jugador->actual_rapidez) / 25.0f) * 1.1;
        return;
    }

    if (((jugador->efectos & TODOS_EFECTOS) & EFECTO_EN_EL_AIRE) == EFECTO_EN_EL_AIRE) {
        jugador->desconocido_098 = ((jugador->actual_rapidez * jugador->actual_rapidez) / 25.0f) * 1.1;
        return;
    }

    variable_f0 = 0.0f;
    jugador->desconocido_098 = parametro1;
    temporal_lo = jugador->acel_pendiente / GRADOS(1);
    if ((temporal_lo > 0x11) || (temporal_lo < -0x11)) {
        variable_f0 += (temporal_lo * 0.0125) / 1.2;
    } else {
        variable_f0 += (temporal_lo * 0.025) / 1.2;
    }
    jugador->desconocido_098 = parametro1 * (1.0f - variable_f0);
    if (jugador->ruedas[DERECHA_ATRAS].tipo_superficie == PASTO) {
        variable_f0 += dato_800E2E90[jugador->id_personaje][jugador->ruedas[DERECHA_ATRAS].tipo_superficie] * 0.7;
    }
    if (jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie == PASTO) {
        variable_f0 += dato_800E2E90[jugador->id_personaje][jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie] * (0.7 * 1.0);
    }
    probar = jugador->desconocido_0C0 / GRADOS(1);
    if (probar < 0) {
        variable_f0 += -probar * 0.004;
    } else {
        variable_f0 += probar * 0.004;
    }
    jugador->desconocido_098 = parametro1 * (1.0 + (variable_f0 * 0.7));
    if ((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB) {
        temporal_f0_3 = jugador->actual_rapidez + 180.0f;
        jugador->desconocido_098 = (temporal_f0_3 * temporal_f0_3) / 25.0f;
    }
}

f32 funcion_80030150(Jugador* jugador, s8 indice_jugador) {
    f32 variable_f0;
    s16 temporal_lo;
    f32 variable_f2;
    s32 variable_v0;

    variable_f0 = 0.0f;
    variable_f2 = (jugador->speed / 18.0f) * 216.0f;
    if (variable_f2 >= 8.0f) {
        if ((jugador->efectos & EFECTO_ESTRELLA) != EFECTO_ESTRELLA) {
            if ((s32) jugador->ruedas[DERECHA_ATRAS].tipo_superficie >= 0xF) {
                if (1) {}
            } else {
                variable_f0 += dato_800E2E90[jugador->id_personaje][jugador->ruedas[DERECHA_ATRAS].tipo_superficie];
            }

            if ((s32) jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie < 0xF) {
                variable_f0 += dato_800E2E90[jugador->id_personaje][jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie];
            }

            if ((s32) jugador->ruedas[DERECHA_FRENTE].tipo_superficie < 0xF) {
                variable_f0 += dato_800E2EB0[jugador->id_personaje][jugador->ruedas[DERECHA_FRENTE].tipo_superficie];
            }

            if ((s32) jugador->ruedas[IZQUIERDA_FRENTE].tipo_superficie < 0xF) {
                variable_f0 += dato_800E2E90[jugador->id_personaje][jugador->ruedas[IZQUIERDA_FRENTE].tipo_superficie];
            }
        }
        if (((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) &&
            ((jugador->lakitu_props & MANTENIDO_POR_LAKITU) != MANTENIDO_POR_LAKITU)) {
            temporal_lo = jugador->acel_pendiente / GRADOS(1);
            if (variable_f2 >= 20.0f) {
                if ((temporal_lo > 0x11) || (temporal_lo < -0x11)) {
                    variable_f0 -= ((temporal_lo * 0.0126) / 3.0);
                } else {
                    variable_f0 -= ((temporal_lo * 0.026) / 3.0);
                }
            } else {
                variable_f0 += -0.2;
                if ((jugador->efectos & EFECTO_RAYO) == EFECTO_RAYO) {
                    variable_f0 += -0.55;
                }
            }
            if (((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) || (jugador->duracion_derrape > 0)) {
                variable_v0 = (s16) jugador->desconocido_0C0 / GRADOS(1);
                if (variable_v0 < 0) {
                    variable_f0 += -variable_v0 * 0.004;
                } else {
                    variable_f0 += variable_v0 * 0.004;
                }
            } else {
                variable_v0 = (s16) jugador->desconocido_0C0 / GRADOS(1);
                if (variable_v0 < 0) {
                    variable_f0 += -variable_v0 * (0.01 + kart_giro_rapidez_reduccion_tabla_0[jugador->id_personaje]);
                } else {
                    variable_f0 += variable_v0 * (0.01 + kart_giro_rapidez_reduccion_tabla_0[jugador->id_personaje]);
                }
            }
            if (((jugador->efectos & EFECTO_FUERA_DERRAPE) == EFECTO_FUERA_DERRAPE) && (jugador->contador_estado_derrape < 10)) {
                if (variable_v0 < 0) {
                    variable_f0 += -variable_v0 * 0.008;
                } else {
                    variable_f0 += variable_v0 * 0.008;
                }
            }
            if ((jugador->efectos & EFECTO_ESTRELLA) == EFECTO_ESTRELLA) {
                variable_f0 += -0.25;
            }
        }
        if ((jugador->oob_props & BAJO_OOB_O_NIVEL_FLUIDO) == BAJO_OOB_O_NIVEL_FLUIDO) {
            variable_f0 += 0.3;
        } else {
            if ((jugador->oob_props & OOB_PASADA_O_NIVEL_FLUIDO) == OOB_PASADA_O_NIVEL_FLUIDO) {
                variable_f0 += 0.15;
            }
            if (((dato_801652A0[indice_jugador] - jugador->ruedas[IZQUIERDA_ATRAS].altura_base) >= 3.5) ||
                ((dato_801652A0[indice_jugador] - jugador->ruedas[DERECHA_ATRAS].altura_base) >= 3.5)) {
                variable_f0 += 0.05;
            }
        }
        if ((jugador->efectos & EFECTO_EN_EL_AIRE) != 0) {
            mover_f32_hacia(&jugador->desconocido_0A0, jugador->desconocido_08C * 0.04, 0.15f);
        } else {
            mover_f32_hacia(&jugador->desconocido_0A0, 0.0f, 0.1f);
        }
    } else {
        jugador->desconocido_0A0 = 0.0f;
        jugador->desconocido_0E8 = 0.0f;
        if (((s16) jugador->acel_pendiente / GRADOS(1)) < 0) {
            variable_f0 += -0.85;
            if (jugador->efectos & EFECTO_RAYO) {
                variable_f0 += -0.55;
            }
        }
    }
    if ((jugador->type & HUMANO_JUGADOR) != HUMANO_JUGADOR) {
        if ((jugador->efectos & EFECTO_RAPIDO_CPU) == EFECTO_RAPIDO_CPU) {
            mover_f32_hacia(&jugador->desconocido_0E8, 380.0f, 0.5f);
        } else {
            mover_f32_hacia(&jugador->desconocido_0E8, 0.0f, 0.1f);
        }
    }
    if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
        if (((jugador->efectos & MINI_EFECTO_TURBO) == MINI_EFECTO_TURBO) &&
            ((jugador->efectos & EFECTO_DERRAPANDO) != EFECTO_DERRAPANDO)) {
            mover_f32_hacia(&jugador->desconocido_0E8, 580.0f, 0.2f);
        } else {
            mover_f32_hacia(&jugador->desconocido_0E8, 0.0f, 0.01f);
        }
        if ((jugador->efectos & EFECTO_RAPIDO_CPU) == EFECTO_RAPIDO_CPU) {
            mover_f32_hacia(&jugador->desconocido_0E4, 580.0f, 0.01f);
        } else {
            mover_f32_hacia(&jugador->desconocido_0E4, 0.0f, 0.01f);
        }
    }
    mover_f32_hacia(&jugador->desconocido_104, variable_f0, kart_giro_rapidez_reduccion_tabla_1[jugador->id_personaje] + 0.05);
    variable_f2 = (jugador->desconocido_08C + jugador->desconocido_0E8 + jugador->potencia_impulso + jugador->desconocido_0E4) - jugador->desconocido_0A0;
    if (variable_f2 < 0.0f) {
        variable_f2 = 0.0f;
    }
    if (((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == MANTENIDO_POR_LAKITU) ||
        ((jugador->lakitu_props & LAKITU_ESCENA) == LAKITU_ESCENA) ||
        ((jugador->type & SECUENCIA_INICIO_JUGADOR) == SECUENCIA_INICIO_JUGADOR)) {
        return (1.0f - jugador->desconocido_104) * variable_f2;
    }
    if (((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
        ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO) ||
        ((jugador->efectos & EFECTO_ERROR_EXPLOSION) == EFECTO_ERROR_EXPLOSION) ||
        ((jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA) == GOLPE_POR_EFECTO_ESTRELLA)) {
        return (1.0f - jugador->desconocido_104) * variable_f2;
    }
    if (((jugador->efectos & EFECTO_HONGO) == EFECTO_HONGO) ||
        ((jugador->efectos & IMPULSO_RAMPA_ASFALTO_EFECTO) == IMPULSO_RAMPA_ASFALTO_EFECTO) ||
        ((jugador->efectos & IMPULSO_RAMPA_MADERA_EFECTO) == IMPULSO_RAMPA_MADERA_EFECTO)) {
        funcion_8002FE84(jugador, jugador->potencia_impulso + jugador->desconocido_08C);
        return jugador->potencia_impulso + jugador->desconocido_08C;
    }
    funcion_8002FE84(jugador, variable_f2);
    return (1.0f - jugador->desconocido_104) * variable_f2;
}

void funcion_80030A34(Jugador* jugador) {
    f32 variable_f0;
    f32 variable_f2;

    if (((jugador->lakitu_props & MANTENIDO_POR_LAKITU) != MANTENIDO_POR_LAKITU) &&
        ((jugador->lakitu_props & LAKITU_ESCENA) != LAKITU_ESCENA)) {
        if ((((jugador->speed / 18.0f) * 216.0f) >= 8.0f) && (jugador->desconocido_DB4.desconocido_c < 1.0f)) {
            switch (jugador->tipo_superficie) { /* irregular */
                case ASFALTO:
                    if (int_aleatorio(0x000AU) != 8) {
                        variable_f0 = 0.35f;
                        variable_f2 = 0.55f;
                    } else {
                        jugador->desconocido_07A = 0;
                        jugador->desconocido_108 = 0.0f;
                        variable_f0 = 0.0f;
                        variable_f2 = 0.0f;
                    }
                    break;
                case PISTA_TREN:
                case PUENTE_CUERDA:
                    variable_f0 = 0.94f;
                    variable_f2 = 0.85f;
                    break;
                default:
                    if (1) {}
                    variable_f0 = 0.46f;
                    variable_f2 = 0.48f;
                    break;
            }
        } else if (int_aleatorio(0x000AU) != 8) {
            variable_f0 = 0.3f;
            variable_f2 = 0.54f;
        } else {
            jugador->desconocido_07A = 0;
            jugador->desconocido_108 = 0.0f;
            variable_f0 = 0.0f;
            variable_f2 = 0.0f;
        }
        jugador->desconocido_07A += 1;
        jugador->desconocido_108 = (jugador->desconocido_07A * variable_f0) - (0.5 * variable_f2 * (jugador->desconocido_07A * jugador->desconocido_07A));
        if ((jugador->desconocido_07A != 0) && (jugador->desconocido_108 < 0.0f)) {
            jugador->desconocido_07A = 0;
        }
        if (jugador->desconocido_108 <= 0.0f) {
            jugador->desconocido_108 = 0.0f;
        }
    }
}

void detectar_triple_a_combo_a_soltado(Jugador* jugador) {
    s32 indice_jugador;

    if (jugador == jugador_uno) {
        indice_jugador = 0;
    }
    if (jugador == jugador_dos) {
        indice_jugador = 1;
    }
    if (jugador == jugador_tres) {
        indice_jugador = 2;
    }
    if (jugador == jugador_cuatro) {
        indice_jugador = 3;
    }
    if (jugador == jugador_cinco) {
        indice_jugador = 4;
    }
    if (jugador == jugador_seis) {
        indice_jugador = 5;
    }
    if (jugador == jugador_siete) {
        indice_jugador = 6;
    }
    if (jugador == jugador_ocho) {
        indice_jugador = 7;
    }
    if (es_jugador_triple_a_boton_combo[indice_jugador] == false) {
        if (jugador_es_acelerador_activo[indice_jugador] == true) {
            if ((frame_desde_ultimo_combo_a[indice_jugador] < 2) || (frame_desde_ultimo_combo_a[indice_jugador] >= 9)) {
                interruptor_cantidad_a[indice_jugador] = 0;
            }
            frame_desde_ultimo_combo_a[indice_jugador] = 0;
            dato_80165400[indice_jugador] = 0;
        }
        jugador_es_acelerador_activo[indice_jugador] = false;
        frame_desde_ultimo_combo_a[indice_jugador]++;
        if (frame_desde_ultimo_combo_a[indice_jugador] >= 9) {
            frame_desde_ultimo_combo_a[indice_jugador] = 9;
        }
        if ((frame_desde_ultimo_combo_a[indice_jugador] >= 2) && (frame_desde_ultimo_combo_a[indice_jugador] < 9)) {
            if (dato_80165400[indice_jugador] == 0) {
                interruptor_cantidad_a[indice_jugador] += 1;
            }
            dato_80165400[indice_jugador] = 1;
        }
        if (interruptor_cantidad_a[indice_jugador] == 5) {
            es_jugador_triple_a_boton_combo[indice_jugador] = true;
            temporizador_impulso_triple_a_combo[indice_jugador] = 120;
            interruptor_cantidad_a[indice_jugador] = 0;
            frame_desde_ultimo_combo_a[indice_jugador] = 0;
        }
    } else {
        temporizador_impulso_triple_a_combo[indice_jugador]--;
        if (temporizador_impulso_triple_a_combo[indice_jugador] <= 0) {
            es_jugador_triple_a_boton_combo[indice_jugador] = false;
        }
    }
}

void detectar_triple_a_combo_a_pulsado(Jugador* jugador) {
    s32 indice_jugador;

    if (jugador == jugador_uno) {
        indice_jugador = 0;
    }
    if (jugador == jugador_dos) {
        indice_jugador = 1;
    }
    if (jugador == jugador_tres) {
        indice_jugador = 2;
    }
    if (jugador == jugador_cuatro) {
        indice_jugador = 3;
    }
    if (jugador == jugador_cinco) {
        indice_jugador = 4;
    }
    if (jugador == jugador_seis) {
        indice_jugador = 5;
    }
    if (jugador == jugador_siete) {
        indice_jugador = 6;
    }
    if (jugador == jugador_ocho) {
        indice_jugador = 7;
    }
    if (es_jugador_triple_a_boton_combo[indice_jugador] == false) {
        if (jugador_es_acelerador_activo[indice_jugador] == false) {
            if ((frame_desde_ultimo_combo_a[indice_jugador] < 2) || (frame_desde_ultimo_combo_a[indice_jugador] >= 9)) {
                interruptor_cantidad_a[indice_jugador] = 0;
            }
            frame_desde_ultimo_combo_a[indice_jugador] = 0;
            dato_80165400[indice_jugador] = 0;
        }
        jugador_es_acelerador_activo[indice_jugador] = true;
        frame_desde_ultimo_combo_a[indice_jugador]++;
        if (frame_desde_ultimo_combo_a[indice_jugador] >= 9) {
            frame_desde_ultimo_combo_a[indice_jugador] = 9;
        }
        if ((frame_desde_ultimo_combo_a[indice_jugador] >= 2) && (frame_desde_ultimo_combo_a[indice_jugador] < 9)) {
            if (dato_80165400[indice_jugador] == 0) {
                interruptor_cantidad_a[indice_jugador] += 1;
            }
            dato_80165400[indice_jugador] = 1;
        }
        if (interruptor_cantidad_a[indice_jugador] == 5) {
            es_jugador_triple_a_boton_combo[indice_jugador] = true;
            temporizador_impulso_triple_a_combo[indice_jugador] = 120;
            interruptor_cantidad_a[indice_jugador] = 0;
            frame_desde_ultimo_combo_a[indice_jugador] = 0;
        }
    } else {
        temporizador_impulso_triple_a_combo[indice_jugador]--;
        if (temporizador_impulso_triple_a_combo[indice_jugador] <= 0) {
            es_jugador_triple_a_boton_combo[indice_jugador] = false;
        }
    }
}
