// Camara jugador

f32 dato_800DDB30[] = { 0.4f, 0.6f, 0.275f, 0.3f };

Camara camaras[4];
Camara* camara1 = &camaras[0];
Camara* camara2 = &camaras[1];
Camara* camara3 = &camaras[2];
Camara* camara4 = &camaras[3];

SIN_USO s32 dato_801649D0[2];

f32 dato_801649D8[4];
f32 dato_801649E8[4];
f32 dato_801649F8[4];
s32 dato_80164A08[4];
s32 dato_80164A18[4];
s32 dato_80164A28;
s32 dato_80164A2C;
f32 dato_80164A30;
SIN_USO f32 dato_80164A34;
f32 dato_80164A38[4];
f32 dato_80164A48[4];
SIN_USO s32 dato_80164A58[8];
f32 dato_80164A78[4];
s8 dato_80164A88;
s8 dato_80164A89;
f32 dato_80164A90[4];
f32 dato_80164AA0[4];

extern f32 dato_80164498[];
extern s16 dato_80164678[];

void inicializar_camara(f32 pos_x, f32 pos_y, f32 pos_z, SIN_USO s16 rot, u32 parametro4, s32 id_camara) {
    Jugador* jugador = jugador_uno;
    Camara* camara = &camaras[id_camara];

    dato_80152300[id_camara] = parametro4;
    switch (parametro4) {
        case 0:
        case 1:
        case 3:
        case 8:
        case 9:
        case 10:
            dato_80164A89 = 0;
            camara->pos[0] = pos_x;
            camara->pos[1] = pos_y;
            camara->pos[2] = pos_z;
            camara->algun_banderas_bit = 0;
            camara->mirar_a[0] = 0.0f;
            camara->mirar_a[2] = 150.0f;
            camara->mirar_a[1] = pos_y - 3.0;
            camara->arriba[0] = 0.0f;
            camara->arriba[1] = 1.0f;
            camara->arriba[2] = 0.0f;
            camara->id_jugador = (s16) id_camara;
            camara->desconocido_B0 = 0;
            camara->desconocido_A0 = 0.0f;

            dato_801649D8[id_camara] = 20.0f;
            dato_801649E8[id_camara] = 10.0f;
            dato_801649F8[id_camara] = 7.0f;
            dato_80164A2C = 0;
            dato_80164A30 = 30.0f;
            dato_80164A38[id_camara] = 0.0f;
            dato_80164A48[id_camara] = 0.0f;

            dato_80164A90[id_camara] = 0.0f;
            dato_80164AA0[id_camara] = 0.0f;
            dato_80164A78[id_camara] = dato_800DDB30[modo_pantalla_activo];
            dato_80164A18[id_camara] = 0;
            dato_80164A08[id_camara] = 0;
            dato_80164498[id_camara] = 0.0f;
            camara->desconocido_94.desconocido_8 = 0;
            camara->desconocido_94.desconocido_0 = 0.0f;

            jugador += id_camara;
            camara->desconocido_2C = jugador->rotacion[1];
            camara->desconocido_ac = jugador->rotacion[1];
            switch (modo_pantalla_activo) {
                case MODO_PANTALLA_1P:
                case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
                    if (seleccion_modo == BATALLA) {
                        camara->desconocido_30[0] = 0.0f;
                        camara->desconocido_30[1] = 11.6f;
                        camara->desconocido_30[2] = -38.5f;
                        camara->desconocido_3C[0] = 0.0f;
                        camara->desconocido_3C[1] = 0.0f;
                        camara->desconocido_3C[2] = 19.2f;
                        dato_80164A88 = 0;
                    } else {
                        camara->desconocido_30[0] = 0.0f;
                        camara->desconocido_30[1] = 9.5f;
                        camara->desconocido_30[2] = -50.0f;
                        camara->desconocido_3C[0] = 0.0f;
                        camara->desconocido_3C[1] = 0.0f;
                        camara->desconocido_3C[2] = 70.0f;
                    }
                    break;
                case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
                    if (seleccion_modo == BATALLA) {
                        camara->desconocido_30[0] = 0.0f;
                        camara->desconocido_30[1] = 11.6f;
                        camara->desconocido_30[2] = -38.5f;
                        camara->desconocido_3C[0] = 0.0f;
                        camara->desconocido_3C[1] = 0.0f;
                        camara->desconocido_3C[2] = 19.2f;
                    } else {
                        camara->desconocido_30[0] = 0.0f;
                        camara->desconocido_30[1] = 9.6f;
                        camara->desconocido_30[2] = -35.0f;
                        camara->desconocido_3C[0] = 0.0f;
                        camara->desconocido_3C[1] = 0.0f;
                        camara->desconocido_3C[2] = 30.0f;
                    }
                    break;
                case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
                    if (seleccion_modo == BATALLA) {
                        camara->desconocido_30[0] = 0.0f;
                        camara->desconocido_30[1] = 11.6f;
                        camara->desconocido_30[2] = -38.5f;
                        camara->desconocido_3C[0] = 0.0f;
                        camara->desconocido_3C[1] = 0.0f;
                        camara->desconocido_3C[2] = 19.2f;
                    } else {
                        camara->desconocido_30[0] = 0.0f;
                        camara->desconocido_30[1] = 9.0f;
                        camara->desconocido_30[2] = -40.0f;
                        camara->desconocido_3C[0] = 0.0f;
                        camara->desconocido_3C[1] = 0.0f;
                        camara->desconocido_3C[2] = 18.0f;
                    }
                    break;
            }

            funcion_80014DE4(id_camara);

            if (dato_80164678[id_camara] == 0) {
                if (dato_80164A28 == 1) {
                    acercar_camara[id_camara] = 80.0f;
                } else {
                    acercar_camara[id_camara] = 40.0f;
                }
                camara->desconocido_B4 = acercar_camara[id_camara];
            }
            if (dato_80164678[id_camara] == 1) {
                if (dato_80164A28 == 1) {
                    acercar_camara[id_camara] = 100.0f;
                } else {
                    acercar_camara[id_camara] = 60.0f;
                }
                camara->desconocido_B4 = acercar_camara[id_camara];
            }
            if (dato_80164678[id_camara] == 2) {
                if (dato_80164A28 == 1) {
                    acercar_camara[id_camara] = 100.0f;
                } else {
                    acercar_camara[id_camara] = 60.0f;
                }
                camara->desconocido_B4 = acercar_camara[id_camara];
                dato_80164A38[id_camara] = 20.0f;
                dato_80164A48[id_camara] = 1.5f;
                dato_80164A78[id_camara] = 1.0f;
            }
            break;
    }
    angulos_plano(camara->pos, camara->mirar_a, camara->rot);
}

void funcion_8001CA10(Camara* camara) {
    camara->desconocido_94.desconocido_8 = 0;
    camara->desconocido_94.desconocido_0 = 6.0f;
}

void funcion_8001CA24(Jugador* jugador, f32 parametro1) {
    Camara* camara = &camaras[0];

    if (jugador == jugador_dos) {
        camara += 1;
    }
    if (jugador == jugador_tres) {
        camara += 2;
    }
    if (jugador == jugador_cuatro) {
        camara += 3;
    }
    camara->desconocido_94.desconocido_8 = 0;
    camara->desconocido_94.desconocido_0 = parametro1;
}

void funcion_8001CA78(SIN_USO Jugador* jugador, Camara* camara, Vec3f parametro2, f32* parametro3, f32* parametro4, f32* parametro5, SIN_USO s32 huh,
                   SIN_USO s32 wut) {
    Mat3 sp74;
    Vec3f sp68;
    Vec3f sp5_c;
    f32 pos_x;
    f32 pos_y;
    f32 pos_z;
    f32 variable_f14;
    f32 temporal_f18;
    f32 temporal_f16;
    SIN_USO s32 relleno;
    PuntoCaminoPista* temporal_s2;

    temporal_s2 = &caminos_pista[0][cantidad_camino_por_indice_camino[0] - 10];
    sp68[0] = camara->desconocido_30[0];
    sp68[1] = camara->desconocido_30[1];
    sp68[2] = camara->desconocido_30[2];
    sp5_c[0] = camara->desconocido_3C[0];
    sp5_c[1] = camara->desconocido_3C[1];
    sp5_c[2] = camara->desconocido_3C[2];
    parametro2[0] = camara->mirar_a[0];
    parametro2[1] = camara->mirar_a[1];
    parametro2[2] = camara->mirar_a[2];
    calcular_matriz_orientacion(sp74, 0, 1, 0, -0x00008000);
    transformar_mat3_vec3f_mtxf(sp5_c, sp74);
    if (id_circuito_actual == CIRCUITO_TOADS_TURNPIKE) {
        variable_f14 = sp5_c[0];
    } else {
        variable_f14 = sp5_c[0] + temporal_s2->pos_x;
    }
    temporal_f16 = dato_80165230[7] + sp5_c[2];
    temporal_f18 = sp5_c[1] + (temporal_s2->pos_y + dato_80164A30);
    parametro2[0] += (variable_f14 - camara->mirar_a[0]) * 1;
    parametro2[1] += (temporal_f18 - camara->mirar_a[1]) * 1;
    parametro2[2] += (temporal_f16 - camara->mirar_a[2]) * 1;
    transformar_mat3_vec3f_mtxf(sp68, sp74);
    if (id_circuito_actual == CIRCUITO_TOADS_TURNPIKE) {
        variable_f14 = sp68[0];
    } else {
        variable_f14 = sp68[0] + temporal_s2->pos_x;
    }
    temporal_f16 = dato_80165230[7] + sp68[2];
    temporal_f18 = sp68[1] + (temporal_s2->pos_y + dato_80164A30 + 6.0f);
    mover_f32_hacia(&dato_80164A30, 0, 0.02f);
    pos_x = camara->pos[0];
    *parametro3 = ((variable_f14 - pos_x) * 1) + pos_x;
    pos_y = camara->pos[1];
    *parametro4 = ((temporal_f18 - pos_y) * 1) + pos_y;
    pos_z = camara->pos[2];
    *parametro5 = ((temporal_f16 - pos_z) * 1) + pos_z;
}

void funcion_8001CCEC(Jugador* jugador, Camara* camara, Vec3f parametro2, f32* parametro3, f32* parametro4, f32* parametro5, SIN_USO s32* parametro6,
                   s16 parametro7, s16 index) {
    Mat3 sp9_c;
    Vec3f sp90;
    Vec3f sp84;
    SIN_USO s32 relleno[3];
    f32 x;
    f32 y;
    f32 z;
    SIN_USO s32 relleno2;
    f32 variable_f2;
    s16 variable_v1;
    f32 temporal_f0;
    f32 variable_f0;
    s16 variable_v0;
    f32 temporal_f12;

    variable_v1 = jugador->desconocido_DB4.desconocido0;
    variable_f2 = jugador->desconocido_DB4.desconocido8;

    variable_v1++;
    temporal_f0 = ((variable_f2 * variable_v1) - (0.7 * (variable_v1 * variable_v1)));
    if ((variable_v1 != 0) && (temporal_f0 < 0)) {
        variable_v1 = 0;
        variable_f2 *= 0.8;
        if (variable_f2 <= 0.1) {
            variable_f2 = 0;
        }
    }
    if (temporal_f0 <= 0) {
        temporal_f0 = 0;
    }
    jugador->desconocido_DB4.desconocido0 = variable_v1;
    jugador->desconocido_DB4.desconocido8 = variable_f2;
    variable_v0 = camara->desconocido_94.desconocido_8;
    variable_f0 = camara->desconocido_94.desconocido_0;
    variable_v0++;
    temporal_f12 = (variable_v0 * variable_f0) - (1.25 * (variable_v0 * variable_v0));
    if ((variable_v0 != 0) && (temporal_f12 < 0)) {
        variable_v0 = 0;
        variable_f0 *= 0.9;
        if (variable_f0 <= 0.1) {
            variable_f0 = 0;
        }
    }
    if (temporal_f12 <= 0) {
        temporal_f12 = 0;
        if (!variable_v0) {}
    }
    camara->desconocido_94.desconocido_8 = variable_v0;
    camara->desconocido_94.desconocido_0 = variable_f0;
    if (dato_80164678[index] == 2) {
        mover_f32_hacia(&dato_80164A38[index], 20.0f, 0.1f);
        mover_f32_hacia(&dato_80164A48[index], 1.5f, 0.1f);
        dato_80164A78[index] += 0.1;
        if (dato_80164A78[index] >= 1) {
            dato_80164A78[index] = 1;
        }

    } else {
        mover_f32_hacia(&dato_80164A38[index], 0, 0.1f);
        mover_f32_hacia(&dato_80164A48[index], 0, 0.1f);
        dato_80164A78[index] -= 0.1;
        if (dato_800DDB30[modo_pantalla_activo] >= dato_80164A78[index]) {
            dato_80164A78[index] = dato_800DDB30[modo_pantalla_activo];
        }
    }
    if ((jugador->lakitu_props & WENT_SOBRE_OOB) == WENT_SOBRE_OOB) {
        switch (modo_pantalla_activo) {
            case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
            case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
                mover_f32_hacia(&dato_80164A90[index], 20, 0.02f);
                mover_f32_hacia(&dato_80164AA0[index], 10, 0.02f);
                break;
            default:
                if (id_circuito_actual == CIRCUITO_YOSHI_VALLEY) {
                    mover_f32_hacia(&dato_80164A90[index], 50, 0.04f);
                    mover_f32_hacia(&dato_80164AA0[index], 35, 0.04f);
                } else {
                    mover_f32_hacia(&dato_80164A90[index], 40, 0.02f);
                    mover_f32_hacia(&dato_80164AA0[index], 20, 0.02f);
                }
                break;
        }
    } else {
        mover_f32_hacia(&dato_80164A90[index], 0, 0.04f);
        mover_f32_hacia(&dato_80164AA0[index], 0, 0.04f);
    }
    sp90[0] = camara->desconocido_30[0];
    sp90[1] =
        camara->desconocido_30[1] + (jugador->desconocido_DB4.desconocido_1e * 0.85) - dato_80164A48[index] + dato_80164AA0[index] + (temporal_f12 / 2);
    sp90[2] = camara->desconocido_30[2] + temporal_f0 + dato_80164A38[index];
    sp84[0] = camara->desconocido_3C[0];
    sp84[1] = camara->desconocido_3C[1] + (jugador->desconocido_DB4.desconocido_1e * 0.85) + temporal_f12;
    sp84[2] = camara->desconocido_3C[2] + temporal_f0 - dato_80164A90[index];
    parametro2[0] = camara->mirar_a[0];
    parametro2[1] = camara->mirar_a[1];
    parametro2[2] = camara->mirar_a[2];
    if ((jugador->efectos & EFECTO_ERROR_EXPLOSION) == EFECTO_ERROR_EXPLOSION) {
        sp84[2] /= 3.0f;
    }
    calcular_matriz_orientacion(sp9_c, 0, 1, 0, parametro7);
    transformar_mat3_vec3f_mtxf(sp84, sp9_c);

    x = jugador->pos[0] + sp84[0];
    z = jugador->pos[2] + sp84[2];
    y = jugador->pos[1] + sp84[1];

    parametro2[0] += (x - camara->mirar_a[0]) * dato_80164A78[index];
    parametro2[2] += ((z - camara->mirar_a[2]) * dato_80164A78[index]);

    if ((((jugador->speed / 18) * 216) <= 5.0f) && ((jugador->efectos & EFECTO_SALTO) == EFECTO_SALTO)) {
        parametro2[1] += ((y - camara->mirar_a[1]) * 0.02);
    } else {
        parametro2[1] += ((y - camara->mirar_a[1]) * 0.5);
    }
    transformar_mat3_vec3f_mtxf(sp90, sp9_c);
    x = jugador->pos[0] + sp90[0];
    z = jugador->pos[2] + sp90[2];
    if ((jugador->efectos & EFECTO_ERROR_EXPLOSION) != EFECTO_ERROR_EXPLOSION) {
        variable_f0 = jugador->pos[1] + sp90[1];
        y = variable_f0;
    } else {
        y = jugador->desconocido_074 + jugador->tamanio_caja_envolvente + sp90[1];
    }

    *parametro3 = camara->pos[0] + ((x - camara->pos[0]) * dato_80164A78[index]);
    *parametro5 = camara->pos[2] + ((z - camara->pos[2]) * dato_80164A78[index]);

    if ((((jugador->speed / 18) * 216) <= 5.0f) && ((jugador->efectos & EFECTO_SALTO) == EFECTO_SALTO)) {
        *parametro4 = camara->pos[1] + (((y - camara->pos[1]) * 0.01));
    } else {
        *parametro4 = camara->pos[1] + (((y - camara->pos[1]) * 0.15));
    }

    if ((jugador->oob_props & BAJO_OOB_O_NIVEL_FLUIDO) != 0) {
        *parametro4 = dato_801652A0[index];
    }
}

void funcion_8001D53C(Jugador* jugador, Camara* camara, Vec3f parametro2, f32* parametro3, f32* parametro4, f32* parametro5, s16 parametro6, s16 parametro7) {
    Mat3 sp74;
    Vec3f sp68;
    Vec3f sp5_c;
    f32 margen_pila_0;
    f32 margen_pila_1;
    f32 margen_pila_2;
    SIN_USO f32 relleno[4];
    f32 cosa;

    if (((u16) jugador->desconocido_222 == 0) && (camara->desconocido_A0 == 0.0f)) {
        camara->desconocido_A0 = 0.0f;
    }
    if ((u16) jugador->desconocido_222 != 4) {
        mover_f32_hacia(&camara->desconocido_A0, 20.0f, 0.06f);
    } else {
        mover_f32_hacia(&camara->desconocido_A0, 0.0f, 0.06f);
    }
    cosa = dato_801652A0[parametro7];
    sp68[0] = camara->desconocido_30[0];
    sp68[1] = camara->desconocido_30[1];
    sp68[2] = camara->desconocido_30[2];
    sp5_c[0] = camara->desconocido_3C[0];
    sp5_c[1] = camara->desconocido_3C[1] + camara->desconocido_A0;
    sp5_c[2] = camara->desconocido_3C[2];
    parametro2[0] = camara->mirar_a[0];
    parametro2[1] = camara->mirar_a[1];
    parametro2[2] = camara->mirar_a[2];
    calcular_matriz_orientacion(sp74, 0.0f, 1.0f, 0.0f, parametro6);
    transformar_mat3_vec3f_mtxf(sp5_c, sp74);
    margen_pila_0 = jugador->pos[0] + sp5_c[0];
    margen_pila_2 = jugador->pos[2] + sp5_c[2];
    margen_pila_1 = jugador->pos[1] + sp5_c[1];
    parametro2[0] += (margen_pila_0 - camara->mirar_a[0]) * 1;
    parametro2[2] += (margen_pila_2 - camara->mirar_a[2]) * 1;
    parametro2[1] += (margen_pila_1 - camara->mirar_a[1]) * 1;
    transformar_mat3_vec3f_mtxf(sp68, sp74);
    margen_pila_0 = jugador->pos[0] + sp68[0];
    margen_pila_2 = jugador->pos[2] + sp68[2];
    margen_pila_1 = sp68[1] + (jugador->desconocido_074 + 1.5);
    if ((jugador->lakitu_props & LAKITU_RECUPERACION) == LAKITU_RECUPERACION) {
        margen_pila_1 = sp68[1] + (cosa + 10.0f);
    }
    *parametro3 = margen_pila_0;
    *parametro4 = margen_pila_1;
    *parametro5 = margen_pila_2;
    dato_80164A90[parametro7] = 0.0f;
    dato_80164AA0[parametro7] = 0.0f;
}

void funcion_8001D794(Jugador* jugador, Camara* camara, Vec3f parametro2, f32* parametro3, f32* parametro4, f32* parametro5, s16 parametro6) {
    Mat3 sp6_c;
    Vec3f sp60;
    Vec3f sp54;
    SIN_USO f32 margen_pila[4];
    f32 probar1;
    f32 probar2;
    f32 probar3;

    sp60[0] = camara->desconocido_30[0];
    sp60[1] = camara->desconocido_30[1];
    sp60[2] = camara->desconocido_30[2] - 6;

    sp54[0] = camara->desconocido_3C[0];
    sp54[1] = camara->desconocido_3C[1];
    sp54[2] = camara->desconocido_3C[2];

    parametro2[0] = camara->mirar_a[0];
    parametro2[1] = camara->mirar_a[1];
    parametro2[2] = camara->mirar_a[2];

    calcular_matriz_orientacion(sp6_c, 0, 1, 0, parametro6);
    transformar_mat3_vec3f_mtxf(sp54, sp6_c);

    probar1 = jugador->pos[0] + sp54[0];
    probar3 = jugador->pos[2] + sp54[2];
    probar2 = jugador->pos[1] + sp54[1];
    parametro2[0] += (probar1 - camara->mirar_a[0]) * 1;
    parametro2[1] += (probar2 - camara->mirar_a[1]) * 1;
    parametro2[2] += (probar3 - camara->mirar_a[2]) * 1;

    transformar_mat3_vec3f_mtxf(sp60, sp6_c);

    probar1 = jugador->pos[0] + sp60[0];
    probar3 = jugador->pos[2] + sp60[2];
    probar2 = jugador->pos[1] + sp60[1];
    *parametro3 = camara->pos[0] + ((probar1 - camara->pos[0]) * 1);
    *parametro4 = camara->pos[1] + ((probar2 - camara->pos[1]) * 1);
    *parametro5 = camara->pos[2] + ((probar3 - camara->pos[2]) * 1);
}

void funcion_8001D944(Jugador* jugador, Camara* camara, Vec3f parametro2, f32* parametro3, f32* parametro4, f32* parametro5, SIN_USO s32* parametro6,
                   s16 parametro7, s16 index) {
    Mat3 sp9_c;
    Vec3f sp90;
    Vec3f sp84;
    SIN_USO s32 relleno[3];
    f32 x;
    f32 y;
    f32 z;
    SIN_USO s32 relleno2;
    f32 variable_f2;
    s16 variable_v1;
    f32 temporal_f0;
    f32 variable_f0;
    s16 variable_v0;
    f32 temporal_f12;

    variable_v1 = jugador->desconocido_DB4.desconocido0;
    variable_f2 = jugador->desconocido_DB4.desconocido8;

    variable_v1++;
    temporal_f0 = ((variable_f2 * variable_v1) - (0.7 * (variable_v1 * variable_v1)));
    if ((variable_v1 != 0) && (temporal_f0 < 0)) {
        variable_v1 = 0;
        variable_f2 *= 0.8;
        if (variable_f2 <= 0.1) {
            variable_f2 = 0;
        }
    }
    if (temporal_f0 <= 0) {
        temporal_f0 = 0;
    }
    jugador->desconocido_DB4.desconocido0 = variable_v1;
    jugador->desconocido_DB4.desconocido8 = variable_f2;
    variable_v0 = camara->desconocido_94.desconocido_8;
    variable_f0 = camara->desconocido_94.desconocido_0;
    variable_v0++;
    temporal_f12 = (variable_v0 * variable_f0) - (1.25 * (variable_v0 * variable_v0));
    if ((variable_v0 != 0) && (temporal_f12 < 0)) {
        variable_v0 = 0;
        variable_f0 *= 0.9;
        if (variable_f0 <= 0.1) {
            variable_f0 = 0;
        }
    }
    if (temporal_f12 <= 0) {
        temporal_f12 = 0;
        if (!variable_v0) {}
    }
    camara->desconocido_94.desconocido_8 = variable_v0;
    camara->desconocido_94.desconocido_0 = variable_f0;
    if (dato_80164678[index] == 2) {
        mover_f32_hacia(&dato_80164A38[index], 20.0f, 0.1f);
        mover_f32_hacia(&dato_80164A48[index], 1.5f, 0.1f);
        dato_80164A78[index] += 0.1;
        if (dato_80164A78[index] >= 1) {
            dato_80164A78[index] = 1;
        }

    } else {
        mover_f32_hacia(&dato_80164A38[index], 0, 0.1f);
        mover_f32_hacia(&dato_80164A48[index], 0, 0.1f);
        dato_80164A78[index] -= 0.1;
        if (dato_800DDB30[modo_pantalla_activo] >= dato_80164A78[index]) {
            dato_80164A78[index] = dato_800DDB30[modo_pantalla_activo];
        }
    }
    if ((jugador->lakitu_props & WENT_SOBRE_OOB) == WENT_SOBRE_OOB) {

        mover_f32_hacia(&dato_80164A90[index], 15, 0.02f);
        mover_f32_hacia(&dato_80164AA0[index], 20, 0.02f);
    } else {
        mover_f32_hacia(&dato_80164A90[index], 0, 0.02f);
        mover_f32_hacia(&dato_80164AA0[index], 0, 0.02f);
    }
    sp90[0] = camara->desconocido_30[0];
    sp90[1] =
        camara->desconocido_30[1] + (jugador->desconocido_DB4.desconocido_1e * 0.85) - dato_80164A48[index] + dato_80164AA0[index] + (temporal_f12 / 2);
    sp90[2] = camara->desconocido_30[2] + temporal_f0 + dato_80164A38[index] + dato_80164AA0[index];
    sp84[0] = camara->desconocido_3C[0];
    sp84[1] = camara->desconocido_3C[1] + (jugador->desconocido_DB4.desconocido_1e * 0.85) + temporal_f12;
    sp84[2] = camara->desconocido_3C[2] + temporal_f0 - dato_80164A90[index];
    parametro2[0] = camara->mirar_a[0];
    parametro2[1] = camara->mirar_a[1];
    parametro2[2] = camara->mirar_a[2];
    if ((jugador->efectos & EFECTO_ERROR_EXPLOSION) == EFECTO_ERROR_EXPLOSION) {
        sp84[2] /= 3.0f;
    }
    calcular_matriz_orientacion(sp9_c, 0, 1, 0, parametro7);
    transformar_mat3_vec3f_mtxf(sp84, sp9_c);

    x = jugador->pos[0] + sp84[0];
    z = jugador->pos[2] + sp84[2];
    y = jugador->pos[1] + sp84[1];

    parametro2[0] += (x - camara->mirar_a[0]) * dato_80164A78[index];
    parametro2[2] += ((z - camara->mirar_a[2]) * dato_80164A78[index]);

    if ((((jugador->speed / 18) * 216) <= 5.0f) && ((jugador->efectos & EFECTO_SALTO) == EFECTO_SALTO)) {
        parametro2[1] += ((y - camara->mirar_a[1]) * 0.02);
    } else {
        parametro2[1] += ((y - camara->mirar_a[1]) * 0.5);
    }
    transformar_mat3_vec3f_mtxf(sp90, sp9_c);
    x = jugador->pos[0] + sp90[0];
    z = jugador->pos[2] + sp90[2];
    if ((jugador->efectos & EFECTO_ERROR_EXPLOSION) != EFECTO_ERROR_EXPLOSION) {
        variable_f0 = jugador->pos[1] + sp90[1];
        y = variable_f0;
    } else {
        y = jugador->desconocido_074 + jugador->tamanio_caja_envolvente + sp90[1];
    }

    *parametro3 = camara->pos[0] + ((x - camara->pos[0]) * dato_80164A78[index]);
    *parametro5 = camara->pos[2] + ((z - camara->pos[2]) * dato_80164A78[index]);

    if ((((jugador->speed / 18) * 216) <= 5.0f) && ((jugador->efectos & EFECTO_SALTO) == EFECTO_SALTO)) {
        *parametro4 = camara->pos[1] + (((y - camara->pos[1]) * 0.01));
    } else {
        *parametro4 = camara->pos[1] + (((y - camara->pos[1]) * 0.15));
    }

    if ((jugador->oob_props & BAJO_OOB_O_NIVEL_FLUIDO) != 0) {
        *parametro4 = dato_801652A0[index];
    }
}

void funcion_8001E0C4(Camara* camara, Jugador* jugador, s8 parametro2) {
    SIN_USO s32 relleno[6];
    f32 temporal_f12;
    f32 sp80;
    f32 temporal_f14;
    SIN_USO s32 relleno2;
    f32 sp74;
    f32 sp70;
    f32 sp6_c;
    Vec3f sp60;
    s16 temporal_t7;
    s16 variable_a2;
    SIN_USO s32 relleno3[8];
    s32 probar = 3;

    if (jugador->desconocido_078 == 0) {
        variable_a2 = 0x0064;
    } else if (jugador->desconocido_078 < 0) {
        variable_a2 = 0x87 - (jugador->desconocido_078 / 3);
    } else {
        variable_a2 = (jugador->desconocido_078 / 3) + 0x87;
    }
    ajustar_angulo(&camara->desconocido_2C, jugador->rotacion[1], variable_a2);
    funcion_8001CA78(jugador, camara, sp60, &sp74, &sp70, &sp6_c, camara->desconocido_2C, parametro2);
    camara->algun_banderas_bit &= ~0x0004;
    temporal_t7 = comprobar_colision_envolvente(&camara->colision, probar, sp74, sp70, sp6_c);
    if (camara->colision.distancia_superficie[2] < 0.0f) {
        sp74 += -camara->colision.vector_orientacion[0] * camara->colision.distancia_superficie[2] * 1;
        sp70 += -camara->colision.vector_orientacion[1] * camara->colision.distancia_superficie[2] * 0.5;
        sp6_c += -camara->colision.vector_orientacion[2] * camara->colision.distancia_superficie[2] * 1;
    }
    if (camara->colision.distancia_superficie[0] < 0.0f) {
        camara->algun_banderas_bit = camara->algun_banderas_bit | 4 | 2;
        sp74 += -camara->colision.desconocido48[0] * camara->colision.distancia_superficie[0] * 1.5;
        sp70 += -camara->colision.desconocido48[1] * camara->colision.distancia_superficie[0] * 1;
        sp6_c += -camara->colision.desconocido48[2] * camara->colision.distancia_superficie[0] * 1.5;
    }
    if (camara->colision.distancia_superficie[1] < 0.0f) {
        camara->algun_banderas_bit = camara->algun_banderas_bit | 4 | 2;
        sp74 += -camara->colision.desconocido54[0] * camara->colision.distancia_superficie[1] * 1.5;
        sp70 += -camara->colision.desconocido54[1] * camara->colision.distancia_superficie[1] * 1;
        sp6_c += -camara->colision.desconocido54[2] * camara->colision.distancia_superficie[1] * 1.5;
    }
    if ((temporal_t7 == 0) && ((camara->algun_banderas_bit & 2) != 2)) {
        camara->desconocido_ac = camara->desconocido_2C;
    }
    camara->mirar_a[0] = sp60[0];
    camara->mirar_a[1] = sp60[1];
    camara->mirar_a[2] = sp60[2];
    camara->pos[0] = sp74;
    camara->pos[1] = sp70;
    camara->pos[2] = sp6_c;
    temporal_f12 = camara->mirar_a[0] - camara->pos[0];
    sp80 = camara->mirar_a[1] - camara->pos[1];
    temporal_f14 = camara->mirar_a[2] - camara->pos[2];
    camara->rot[1] = atan2s(temporal_f12, temporal_f14);
    camara->rot[0] = atan2s(sqrtf((temporal_f12 * temporal_f12) + (temporal_f14 * temporal_f14)), sp80);
    camara->rot[2] = 0;
}

void funcion_8001E45C(Camara* camara, Jugador* jugador, s8 parametro2) {
    SIN_USO s32 relleno[6];
    f32 temporal_f12;
    f32 sp90;
    f32 temporal_f14;
    SIN_USO s32 relleno2;
    f32 sp84;
    f32 sp80;
    f32 sp7_c;
    SIN_USO s32 relleno3[3];
    Vec3f sp64;
    SIN_USO s32 relleno4[2];
    s32 sp58;
    SIN_USO s16 relleno5[4];
    s16 variable_a3;
    SIN_USO s16 relleno6;
    s16 temporal_;

    if ((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) {
        variable_a3 = 100;
        if (jugador->desconocido_078 == 0) {
            camara->desconocido_B0 = 0;
        } else {
            if (jugador->desconocido_078 < 0) {
                variable_a3 = 0xA5 - (jugador->desconocido_078 / 2);
                if ((jugador->efectos & EFECTO_FUERA_DERRAPE) == EFECTO_FUERA_DERRAPE) {
                    mover_s16_hacia(&camara->desconocido_B0, -0x0B60, 0.1f);
                } else {
                    mover_s16_hacia(&camara->desconocido_B0, -GRADOS(12), 0.1f);
                }
            } else {
                variable_a3 = (jugador->desconocido_078 / 2) + 0xA5;
                if ((jugador->efectos & EFECTO_FUERA_DERRAPE) == EFECTO_FUERA_DERRAPE) {
                    mover_s16_hacia(&camara->desconocido_B0, 0x0B60, 0.1f);
                } else {
                    mover_s16_hacia(&camara->desconocido_B0, GRADOS(12), 0.1f);
                }
            }
        }
    } else {
        mover_s16_hacia(&camara->desconocido_B0, 0, 0.05f);
        variable_a3 = ((s16) camara->desconocido_2C / GRADOS(1)) - ((s16) jugador->rotacion[1] / GRADOS(1));
        if (jugador->desconocido_078 == 0) {
            if ((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB) {
                variable_a3 = 0x02D8;
            } else {
                variable_a3 = 0x01F4;
            }
        } else if (jugador->desconocido_078 < 0) {
            if ((variable_a3 <= -70) || (variable_a3 >= 70)) {
                variable_a3 = 0xB4 - jugador->desconocido_078;
            } else {
                variable_a3 = 0xA5 - (jugador->desconocido_078 / 2);
            }
        } else if ((variable_a3 <= -70) || (variable_a3 >= 0x46)) {
            variable_a3 = jugador->desconocido_078 + 0xB4;
        } else {
            variable_a3 = (jugador->desconocido_078 / 2) + 0xA5;
        }
    }
    if (((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
        ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO) ||
        ((jugador->efectos & TEMPRANO_INICIO_TROMPO_EFECTO) == TEMPRANO_INICIO_TROMPO_EFECTO) ||
        ((jugador->efectos & desconocido_efecto_0_x_80000) == desconocido_efecto_0_x_80000) ||
        ((jugador->efectos & desconocido_efecto_0_x_800000) == desconocido_efecto_0_x_800000) ||
        (((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB) && (jugador->desconocido_078 != 0)) ||
        (jugador->colision.distancia_superficie[0] <= 0.0f) || (jugador->colision.distancia_superficie[1] <= 0.0f) ||
        ((jugador->efectos & EFECTO_GOLPE_RAYO) == EFECTO_GOLPE_RAYO)) {
        funcion_8001CCEC(jugador, camara, sp64, &sp84, &sp80, &sp7_c, &sp58, (s32) camara->desconocido_2C, (s32) parametro2);
    } else {
        ajustar_angulo(&camara->desconocido_2C, (s16) (jugador->rotacion[1] + camara->desconocido_B0), variable_a3);
        funcion_8001CCEC(jugador, camara, sp64, &sp84, &sp80, &sp7_c, &sp58, (s32) camara->desconocido_2C, (s32) parametro2);
    }
    temporal_ = 3;
    camara->algun_banderas_bit &= 0xFFFB;
    comprobar_colision_envolvente(&camara->colision, temporal_, sp84, sp80, sp7_c);

    camara->pos[0] = sp84;
    camara->pos[1] = sp80;
    camara->pos[2] = sp7_c;

    camara->mirar_a[0] = sp64[0];
    camara->mirar_a[1] = sp64[1];
    camara->mirar_a[2] = sp64[2];

    temporal_f12 = camara->mirar_a[0] - camara->pos[0];
    sp90 = camara->mirar_a[1] - camara->pos[1];
    temporal_f14 = camara->mirar_a[2] - camara->pos[2];

    camara->rot[1] = atan2s(temporal_f12, temporal_f14);
    camara->rot[0] = atan2s(sqrtf((temporal_f12 * temporal_f12) + (temporal_f14 * temporal_f14)), sp90);
    camara->rot[2] = 0;
}

void funcion_8001E8E8(Camara* camara, Jugador* jugador, s8 parametro2) {
    SIN_USO f32 relleno[6];
    f32 temporal_f12;
    f32 sp88;
    f32 temporal_f14;
    SIN_USO f32 relleno2;
    f32 sp7_c;
    f32 sp78;
    f32 sp74;
    SIN_USO Vec3f relleno3;
    Vec3f sp5_c;
    SIN_USO f32 relleno4[10];

    camara->desconocido_B0 = 0;
    camara->desconocido_2C = jugador->rotacion[1];
    funcion_8001D53C(jugador, camara, sp5_c, &sp7_c, &sp78, &sp74, (s16) (s32) jugador->rotacion[1], (s16) (s32) parametro2);
    comprobar_colision_envolvente(&camara->colision, 5.0f, sp7_c, sp78, sp74);
    camara->mirar_a[0] = sp5_c[0];
    camara->mirar_a[1] = sp5_c[1];
    camara->mirar_a[2] = sp5_c[2];
    camara->pos[0] = sp7_c;
    camara->pos[1] = sp78;
    camara->pos[2] = sp74;
    temporal_f12 = camara->mirar_a[0] - camara->pos[0];
    sp88 = camara->mirar_a[1] - camara->pos[1];
    temporal_f14 = camara->mirar_a[2] - camara->pos[2];
    camara->rot[1] = atan2s(temporal_f12, temporal_f14);
    camara->rot[0] = atan2s(sqrtf((temporal_f12 * temporal_f12) + (temporal_f14 * temporal_f14)), sp88);
    camara->rot[2] = 0;
}

void funcion_8001EA0C(Camara* camara, Jugador* jugador, s8 parametro2) {
    SIN_USO s32 relleno[6];
    f32 temporal_f12;
    f32 sp90;
    f32 temporal_f14;
    SIN_USO s32 relleno2;
    f32 sp84;
    f32 sp80;
    f32 sp7_c;
    SIN_USO s32 relleno3[3];
    Vec3f sp64;
    SIN_USO s32 relleno4[2];
    s32 sp58;
    SIN_USO s16 relleno5[4];
    s16 variable_a3;
    SIN_USO s16 relleno6;
    s16 temporal_;

    if ((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) {
        variable_a3 = 100;
        if (jugador->desconocido_078 == 0) {
            camara->desconocido_B0 = 0;
        } else {
            if (jugador->desconocido_078 < 0) {
                variable_a3 = 0xA5 - (jugador->desconocido_078 / 2);

                if ((jugador->efectos & EFECTO_FUERA_DERRAPE) == EFECTO_FUERA_DERRAPE) {
                    mover_s16_hacia(&camara->desconocido_B0, -0x0B60, 0.1f);
                } else {
                    mover_s16_hacia(&camara->desconocido_B0, -GRADOS(12), 0.1f);
                }
            } else {
                variable_a3 = (jugador->desconocido_078 / 2) + 0xA5;
                if ((jugador->efectos & EFECTO_FUERA_DERRAPE) == EFECTO_FUERA_DERRAPE) {
                    mover_s16_hacia(&camara->desconocido_B0, 0x0B60, 0.1f);
                } else {
                    mover_s16_hacia(&camara->desconocido_B0, GRADOS(12), 0.1f);
                }
            }
        }
    } else {
        mover_s16_hacia(&camara->desconocido_B0, 0, 0.05f);
        variable_a3 = ((s16) camara->desconocido_2C / GRADOS(1)) - ((s16) jugador->rotacion[1] / GRADOS(1));
        if (jugador->desconocido_078 == 0) {
            if ((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB) {
                variable_a3 = 0x02D8;
            } else {
                variable_a3 = 0x01F4;
            }
        } else if (jugador->desconocido_078 < 0) {
            if ((variable_a3 <= -70) || (variable_a3 >= 70)) {
                variable_a3 = 0xB4 - jugador->desconocido_078;
            } else {
                variable_a3 = 0xA5 - (jugador->desconocido_078 / 2);
            }
        } else if ((variable_a3 <= -70) || (variable_a3 >= 0x46)) {
            variable_a3 = jugador->desconocido_078 + 0xB4;
        } else {
            variable_a3 = (jugador->desconocido_078 / 2) + 0xA5;
        }
    }
    if (((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
        ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO) ||
        ((jugador->efectos & TEMPRANO_INICIO_TROMPO_EFECTO) == TEMPRANO_INICIO_TROMPO_EFECTO) ||
        ((jugador->efectos & desconocido_efecto_0_x_80000) == desconocido_efecto_0_x_80000) ||
        ((jugador->efectos & desconocido_efecto_0_x_800000) == desconocido_efecto_0_x_800000) ||
        (((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB) && (jugador->desconocido_078 != 0)) ||
        (jugador->colision.distancia_superficie[0] <= 0.0f) || (jugador->colision.distancia_superficie[1] <= 0.0f) ||
        ((jugador->efectos & EFECTO_GOLPE_RAYO) == EFECTO_GOLPE_RAYO)) {
        funcion_8001D944(jugador, camara, sp64, &sp84, &sp80, &sp7_c, &sp58, (s32) camara->desconocido_2C, (s32) parametro2);
    } else {
        ajustar_angulo(&camara->desconocido_2C, (s16) (jugador->rotacion[1] + camara->desconocido_B0), variable_a3);
        funcion_8001D944(jugador, camara, sp64, &sp84, &sp80, &sp7_c, &sp58, (s32) camara->desconocido_2C, (s32) parametro2);
    }
    temporal_ = 3;
    camara->algun_banderas_bit &= 0xFFFB;
    comprobar_colision_envolvente(&camara->colision, temporal_, sp84, sp80, sp7_c);

    camara->pos[0] = sp84;
    camara->pos[1] = sp80;
    camara->pos[2] = sp7_c;

    camara->mirar_a[0] = sp64[0];
    camara->mirar_a[1] = sp64[1];
    camara->mirar_a[2] = sp64[2];

    temporal_f12 = camara->mirar_a[0] - camara->pos[0];
    sp90 = camara->mirar_a[1] - camara->pos[1];
    temporal_f14 = camara->mirar_a[2] - camara->pos[2];

    camara->rot[1] = atan2s(temporal_f12, temporal_f14);
    camara->rot[0] = atan2s(sqrtf((temporal_f12 * temporal_f12) + (temporal_f14 * temporal_f14)), sp90);
    camara->rot[2] = 0;
}
