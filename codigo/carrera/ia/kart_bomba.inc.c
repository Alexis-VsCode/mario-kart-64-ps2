void aparecer_posiciones_conjunto_kart_bomba(void) {
    SIN_USO Colision* variable_s2;
    f32 pos_inicial_x;
    f32 pos_inicial_z;
    f32 pos_inicial_y;
    s32 variable_s3;
    PuntoCaminoPista* temporal_v0;
    SIN_USO KartBomba* variable_s0;
    KartBombaAparicion* kart_bomba_aparicion;

    for (variable_s3 = 0; variable_s3 < NUM_KARTS_BOMBA_VERSUS; variable_s3++) {
        kart_bomba_aparicion = &kart_bomba_apariciones[id_circuito_actual][variable_s3];
        switch (id_circuito_actual) {
            case CIRCUITO_YOSHI_VALLEY:
                pos_inicial_x = kart_bomba_aparicion->pos_inicial_x;
                pos_inicial_z = kart_bomba_aparicion->pos_inicial_z;
                pos_inicial_y = obtener_altura_superficie(pos_inicial_x, 2000.0f, pos_inicial_z);
                break;
            case CEREMONIA_PREMIO_CIRCUITO:
                temporal_v0 = &caminos_pista[3][kart_bomba_aparicion->indice_punto_camino];
                pos_inicial_x = temporal_v0->pos_x;
                pos_inicial_y = temporal_v0->pos_y;
                pos_inicial_z = temporal_v0->pos_z;
                break;
            default:
                temporal_v0 = &caminos_pista[0][kart_bomba_aparicion->indice_punto_camino];
                pos_inicial_x = temporal_v0->pos_x;
                pos_inicial_y = temporal_v0->pos_y;
                pos_inicial_z = temporal_v0->pos_z;
                break;
        }
        karts_bomba[variable_s3].pos_bomba[0] = pos_inicial_x;
        karts_bomba[variable_s3].pos_bomba[1] = pos_inicial_y;
        karts_bomba[variable_s3].pos_bomba[2] = pos_inicial_z;
        karts_bomba[variable_s3].pos_rueda_1[0] = pos_inicial_x;
        karts_bomba[variable_s3].pos_rueda_1[1] = pos_inicial_y;
        karts_bomba[variable_s3].pos_rueda_1[2] = pos_inicial_z;
        karts_bomba[variable_s3].pos_rueda_2[0] = pos_inicial_x;
        karts_bomba[variable_s3].pos_rueda_2[1] = pos_inicial_y;
        karts_bomba[variable_s3].pos_rueda_2[2] = pos_inicial_z;
        karts_bomba[variable_s3].pos_rueda_3[0] = pos_inicial_x;
        karts_bomba[variable_s3].pos_rueda_3[1] = pos_inicial_y;
        karts_bomba[variable_s3].pos_rueda_3[2] = pos_inicial_z;
        karts_bomba[variable_s3].pos_rueda_4[0] = pos_inicial_x;
        karts_bomba[variable_s3].pos_rueda_4[1] = pos_inicial_y;
        karts_bomba[variable_s3].pos_rueda_4[2] = pos_inicial_z;
        karts_bomba[variable_s3].indice_punto_camino = kart_bomba_aparicion->indice_punto_camino;
        karts_bomba[variable_s3].desconocido_3C = kart_bomba_aparicion->desconocido_04;
        karts_bomba[variable_s3].temporizador_rebote = 0;
        karts_bomba[variable_s3].temporizador_circulo = 0;
        karts_bomba[variable_s3].state = kart_bomba_aparicion->estado_inicial;
        karts_bomba[variable_s3].desconocido_4A = 0;
        karts_bomba[variable_s3].desconocido_4C = 1;
        karts_bomba[variable_s3].y_pos = pos_inicial_y;
        comprobar_colision_envolvente(&dato_80164038[variable_s3], 2.0f, pos_inicial_x, pos_inicial_y, pos_inicial_z);
    }
}

void actualizar_karts_bomba(s32 kart_bomba_id) {
    SIN_USO s32 margen_pila_0;
    f32 sp118;
    f32 variable_f18;
    PuntoCaminoPista* temporal_v0_2;
    f32 temporal_f0_3;
    f32 sp108;
    SIN_USO s32 margen_pila_1;
    SIN_USO s32 margen_pila_2;
    SIN_USO s32 margen_pila_3;
    f32 temporal_f14;
    SIN_USO s32 margen_pila_4;
    f32 temporal_f16;
    SIN_USO s32 margen_pila_5;
    SIN_USO s32 margen_pila_6;
    SIN_USO s32 margen_pila_7;
    SIN_USO s32 margen_pila_8;
    SIN_USO s32 margen_pila_9;
    SIN_USO s32 margen_a_pila;
    SIN_USO s32 margen_b_pila;
    f32 temporal_f0;
    f32 temporal_f0_4;
    u16 sp_ca;
    f32 sp_c4;
    u16 sp_c2;
    f32 temporal_f12;
    f32 temporal_f12_3;
    f32 temporal_f12_4;
    f32 temporal_f14_2;
    f32 sp_ac;
    SIN_USO s32 margen_c_pila;
    f32 temporal_f16_2;
    f32 sp_a0;
    f32 temporal_f2;
    f32 temporal_f2_4;
    f32 sp94;
    SIN_USO s32 margen_d_pila;
    f32 variable_f20;
    f32 sp88;
    f32 variable_f22;
    f32 variable_f24;
    u16 sp7_e;
    u16 sp7_c;
    SIN_USO u16 sp4_c;
    u16 temporal_t6;
    u16 temporal_t7;
    u16 variable_s1;
    s32 variable_a0;
    SIN_USO s32 margen_e_pila;
    PuntoCaminoPista* temporal_v0_4;
    KartBomba* kart_bomba;
    KartBomba* kart_bomba_2;
    Colision* temporal_a0_4;
    Jugador* variable_v0;

    kart_bomba = &karts_bomba[kart_bomba_id];

    sp7_e = kart_bomba->state;

    if (sp7_e == 0) {
        return;
    }

    if (((kart_bomba->desconocido_4A != 1) || (id_circuito_actual == CEREMONIA_PREMIO_CIRCUITO))) {
        variable_f22 = kart_bomba->pos_bomba[0];
        variable_f20 = kart_bomba->pos_bomba[1];
        variable_f24 = kart_bomba->pos_bomba[2];
        sp_ca = kart_bomba->indice_punto_camino;
        sp_c4 = kart_bomba->desconocido_3C;
        sp_c2 = kart_bomba->algun_rot;
        sp7_c = kart_bomba->temporizador_rebote;
        variable_s1 = kart_bomba->temporizador_circulo;
        if ((sp7_e != 0) && (sp7_e != 4)) {
            if (1) {}
            if (id_circuito_actual == CEREMONIA_PREMIO_CIRCUITO) {
                if (dato_8016347E == 1) {
                    variable_v0 = jugador_cuatro;
                    temporal_f0 = variable_f22 - variable_v0->pos[0];
                    temporal_f2 = variable_f20 - variable_v0->pos[1];
                    temporal_f12 = variable_f24 - variable_v0->pos[2];
                    if ((((temporal_f0 * temporal_f0) + (temporal_f2 * temporal_f2)) + (temporal_f12 * temporal_f12)) < 25.0f) {
                        variable_s1 = 0;
                        sp7_e = 4;
                        variable_v0->disparadores |= DISPARADOR_VUELCO_VERTICAL;
                        variable_v0->type &= ~SECUENCIA_INICIO_JUGADOR;
                    }
                }
            } else {

                for (variable_a0 = 0; variable_a0 < cantidad_jugador; variable_a0++) {
                    variable_v0 = &jugadores[variable_a0];
                    if (!(variable_v0->efectos & BOO_EFECTO)) {
                        temporal_f0 = variable_f22 - variable_v0->pos[0];
                        temporal_f2 = variable_f20 - variable_v0->pos[1];
                        temporal_f12 = variable_f24 - variable_v0->pos[2];
                        if ((((temporal_f0 * temporal_f0) + (temporal_f2 * temporal_f2)) + (temporal_f12 * temporal_f12)) < 25.0f) {
                            sp7_e = 4;
                            variable_s1 = 0;
                            if (id_circuito_actual == CIRCUITO_FRAPPE_SNOWLAND) {
                                variable_v0->disparadores |= GOLPE_POR_DISPARADOR_ESTRELLA;
                            } else {
                                variable_v0->disparadores |= DISPARADOR_VUELCO_VERTICAL;
                            }
                        }
                    }
                }
            }
        }
        switch (sp7_e) {
            case 1:
                variable_s1 = (variable_s1 + 356) % 360;
                temporal_t6 = (variable_s1 * 0xFFFF) / 360;
                sp118 = coss(temporal_t6) * 25.0;
                temporal_f0_3 = senos(temporal_t6) * 25.0;
                temporal_v0_2 = &caminos_pista[0][sp_ca];
                variable_f22 = temporal_v0_2->pos_x + sp118;
                variable_f20 = kart_bomba->y_pos + 3.5f;
                variable_f24 = temporal_v0_2->pos_z + temporal_f0_3;
                dato_80162FB0[0] = variable_f22;
                dato_80162FB0[1] = variable_f20;
                dato_80162FB0[2] = variable_f24;
                temporal_t7 = (((variable_s1 + 1) % 360) * 0xFFFF) / 360;
                sp118 = coss(temporal_t7) * 25.0;
                temporal_f0_3 = senos(temporal_t7) * 25.0;
                dato_80162FC0[0] = temporal_v0_2->pos_x + sp118;
                dato_80162FC0[1] = temporal_v0_2->pos_y;
                dato_80162FC0[2] = temporal_v0_2->pos_z + temporal_f0_3;
                sp_c2 = (obtener_angulo_xz_entre_puntos(dato_80162FB0, dato_80162FC0) * 0xFFFF) / 65520;
                break;
            case 2:
                variable_s1 = (variable_s1 + 4) % 360;
                temporal_t6 = (variable_s1 * 0xFFFF) / 360;
                sp118 = coss(temporal_t6) * 25.0;
                temporal_f0_3 = senos(temporal_t6) * 25.0;
                temporal_v0_2 = &caminos_pista[0][sp_ca];
                variable_f22 = temporal_v0_2->pos_x + sp118;
                variable_f20 = kart_bomba->y_pos + 3.5f;
                variable_f24 = temporal_v0_2->pos_z + temporal_f0_3;
                dato_80162FB0[0] = variable_f22;
                dato_80162FB0[1] = variable_f20;
                dato_80162FB0[2] = variable_f24;
                temporal_t7 = (((variable_s1 + 1) % 360) * 0xFFFF) / 360;
                sp118 = coss(temporal_t7) * 25.0;
                temporal_f0_3 = senos(temporal_t7) * 25.0;
                dato_80162FC0[0] = temporal_v0_2->pos_x + sp118;
                dato_80162FC0[1] = temporal_v0_2->pos_y;
                dato_80162FC0[2] = temporal_v0_2->pos_z + temporal_f0_3;
                sp_c2 = (obtener_angulo_xz_entre_puntos(dato_80162FB0, dato_80162FC0) * 0xFFFF) / 65520;
                break;
            case 3:
                variable_f20 = kart_bomba->y_pos + 3.5f;
                sp_c2 = 0;
                break;

            case 5:
                if ((dato_8016347C == 0) || (punto_camino_mas_cercano_por_id_jugador[3] < 5)) {
                    break;
                } else {
                    sp_ca = funcion_8000D2B4(variable_f22, variable_f20, variable_f24, sp_ca, 3);
                    if ((sp_ca < 0) || (cantidad_camino_por_indice_camino[3] < sp_ca)) {
                        sp_ca = 0;
                    }
                    if (((s32) sp_ca) < 0x1A) {
                        temporal_v0_2 = &caminos_pista[3][(sp_ca + 1) % cantidad_camino_por_indice_camino[3]];
                        dato_80162FB0[0] = temporal_v0_2->pos_x;
                        dato_80162FB0[1] = temporal_v0_2->pos_y;
                        dato_80162FB0[2] = temporal_v0_2->pos_z;
                        temporal_v0_4 = &caminos_pista[3][(sp_ca + 2) % cantidad_camino_por_indice_camino[3]];
                        dato_80162FC0[0] = temporal_v0_4->pos_x;
                        dato_80162FC0[1] = temporal_v0_4->pos_y;
                        dato_80162FC0[2] = temporal_v0_4->pos_z;
                        sp_c2 = (obtener_angulo_xz_entre_puntos(dato_80162FB0, dato_80162FC0) * 0xFFFF) / 65520;
                    } else {
                        dato_80162FB0[0] = variable_f22;
                        dato_80162FB0[1] = variable_f20;
                        dato_80162FB0[2] = variable_f24;
                        dato_80162FC0[0] = -2409.197f;
                        dato_80162FC0[1] = 0.0f;
                        dato_80162FC0[2] = -355.254f;
                        sp_c2 = (obtener_angulo_xz_entre_puntos(dato_80162FB0, dato_80162FC0) * 0xFFFF) / 65520;
                    }
                    temporal_f14 = ((dato_80162FB0[0] + dato_80162FC0[0]) * 0.5f) - variable_f22;
                    temporal_f16 = ((dato_80162FB0[2] + dato_80162FC0[2]) * 0.5f) - variable_f24;
                    temporal_f0_4 = sqrtf((temporal_f14 * temporal_f14) + (temporal_f16 * temporal_f16));
                    if (temporal_f0_4 > 0.01f) {
                        variable_f22 += (kart_bomba->desconocido_3C * temporal_f14) / temporal_f0_4;
                        variable_f24 += (kart_bomba->desconocido_3C * temporal_f16) / temporal_f0_4;
                    } else {
                        variable_f22 += temporal_f14 / 5.0f;
                        variable_f24 += temporal_f16 / 5.0f;
                    }
                    temporal_a0_4 = &dato_80164038[kart_bomba_id];
                    variable_f20 = calcular_altura_superficie(variable_f22, 2000.0f, variable_f24, temporal_a0_4->indice_zx_malla) + 3.5f;
                    if (variable_f20 < (-1000.0)) {
                        variable_f20 = kart_bomba->pos_bomba[1];
                    }
                    comprobar_colision_envolvente(temporal_a0_4, 10.0f, variable_f22, variable_f20, variable_f24);
                }
                break;
            case 4:
                temporal_v0_2 = &caminos_pista[0][sp_ca];
                dato_80162FB0[0] = temporal_v0_2->pos_x;
                dato_80162FB0[1] = temporal_v0_2->pos_y;
                dato_80162FB0[2] = temporal_v0_2->pos_z;
                temporal_v0_4 = &caminos_pista[0][(sp_ca + 1) % cantidad_camino_por_indice_camino[0]];
                dato_80162FC0[0] = temporal_v0_4->pos_x;
                dato_80162FC0[1] = temporal_v0_4->pos_y;
                dato_80162FC0[2] = temporal_v0_4->pos_z;
                variable_f20 += 3.0f - (variable_s1 * 0.3f);
                sp_c2 = (obtener_angulo_xz_entre_puntos(dato_80162FB0, dato_80162FC0) * 0xFFFF) / 65520;
                break;
            default:
                break;
        }

        if (sp7_e == 4) {
            sp108 = 2.0f * variable_s1;
            sp118 = coss(0xFFFF - sp_c2) * variable_s1;
            variable_f18 = senos(0xFFFF - sp_c2) * variable_s1;
            variable_s1++;
            temporal_f2_4 = (variable_f20 - 2.3f) + (sp108 / 3.0f);
            sp_ac = temporal_f2_4;
            sp_a0 = temporal_f2_4;
            sp94 = temporal_f2_4;
            sp88 = temporal_f2_4;
            if (variable_s1 >= 31) {
                sp7_e = 0;
            }
        } else {
            sp118 = coss(0xFFFF - sp_c2) * 1.5f;
            variable_f18 = senos(0xFFFF - sp_c2) * 1.5f;
            temporal_f16_2 = variable_f20 - 2.3f;
            temporal_f12_3 = (sp7_c % 3) * 0.15f;
            temporal_f14_2 = temporal_f16_2 - temporal_f12_3;
            temporal_f12_4 = temporal_f16_2 + temporal_f12_3;
            sp_ac = temporal_f14_2;
            sp94 = temporal_f14_2;
            sp_a0 = temporal_f12_4;
            sp88 = temporal_f12_4;
            variable_f20 += senos((sp7_c * 0x13FFEC) / 360);
            sp7_c = (sp7_c + 1) % 18;
        }
        kart_bomba_2 = kart_bomba;
        kart_bomba_2->pos_rueda_1[0] = (sp118 - variable_f18) + variable_f22;
        kart_bomba_2->pos_rueda_1[1] = sp_ac;
        kart_bomba_2->pos_rueda_1[2] = (variable_f18 + sp118) + variable_f24;
        kart_bomba_2->pos_rueda_2[0] = (variable_f18 + sp118) + variable_f22;
        kart_bomba_2->pos_rueda_2[1] = sp_a0;
        kart_bomba_2->pos_rueda_2[2] = (variable_f18 - sp118) + variable_f24;
        kart_bomba_2->pos_rueda_3[0] = ((-sp118) - variable_f18) + variable_f22;
        kart_bomba_2->pos_rueda_3[1] = sp94;
        kart_bomba_2->pos_rueda_3[2] = ((-variable_f18) + sp118) + variable_f24;
        kart_bomba_2->pos_rueda_4[0] = ((-sp118) + variable_f18) + variable_f22;
        kart_bomba_2->pos_rueda_4[1] = sp88;
        kart_bomba_2->pos_rueda_4[2] = ((-variable_f18) - sp118) + variable_f24;
        kart_bomba_2->pos_bomba[0] = variable_f22;
        kart_bomba_2->pos_bomba[1] = variable_f20;
        kart_bomba_2->pos_bomba[2] = variable_f24;
        kart_bomba_2->indice_punto_camino = sp_ca;
        kart_bomba_2->desconocido_3C = sp_c4;
        kart_bomba_2->algun_rot = sp_c2;
        kart_bomba_2->state = sp7_e;
        kart_bomba_2->temporizador_rebote = sp7_c;
        kart_bomba_2->temporizador_circulo = variable_s1;
    }
}
