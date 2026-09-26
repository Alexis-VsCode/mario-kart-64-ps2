// Objetos pista y hud jugadores

void inicializar_objetos_circuito(void) {
    s32 id_objeto;
    s32 i;

#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_MARIO_RACEWAY:
            if (estado_juego != 9) {
                if (seleccion_modo == GRAN_PREMIO) {
                    funcion_80070714();
                }
                for (i = 0; i < dato_80165738; i++) {
                    buscar_indice_obj_sin_uso(&particula_objeto_3[i]);
                    inicializar_objeto(particula_objeto_3[i], 0);
                }
            }
            break;
        case CIRCUITO_BOWSER_CASTLE:
            thwomps_activo_num = NUM_THWOMPS_100CC_EXTRA;
            lista_aparicion_thowmp = thwomp_extra_apariciones_100CC;
            switch (seleccion_cc) {
                case CC_100:
                case CC_EXTRA:
                    break;
                case CC_50:
                    thwomps_activo_num = NUM_THWOMPS_50CC;
                    lista_aparicion_thowmp = apariciones_thomwp_50CC;
                    break;
                case CC_150:
                    thwomps_activo_num = NUM_THWOMPS_150CC;
                    lista_aparicion_thowmp = apariciones_thomwp_150CC;
                    break;
            }
            for (i = 0; i < thwomps_activo_num; i++) {
                id_objeto = lista_objeto_indice_1[i];
                inicializar_objeto(id_objeto, 0);
                lista_objeto[id_objeto].pos_origen[0] = lista_aparicion_thowmp[i].inicio_x * orientacion_x;
                lista_objeto[id_objeto].pos_origen[2] = lista_aparicion_thowmp[i].inicio_z;
                lista_objeto[id_objeto].desconocido_0D5 = lista_aparicion_thowmp[i].desconocido_4;
                lista_objeto[id_objeto].prim_alpha = lista_aparicion_thowmp[i].desconocido_6;
            }
            id_objeto = lista_objeto_indice_2[0];
            inicializar_objeto(id_objeto, 0);
            lista_objeto[id_objeto].pos[0] = -68.0 * orientacion_x;
            lista_objeto[id_objeto].pos[1] = 80.0f;
            lista_objeto[id_objeto].pos[2] = -1840.0f;
            for (i = 0; i < RESPIROS_FUEGO_NUM; i++) {
                id_objeto = lista_objeto_indice_3[i];
                inicializar_objeto(id_objeto, 0);
                lista_objeto[id_objeto].pos[0] = apariciones_respiros_fuego[i][0] * orientacion_x;
                lista_objeto[id_objeto].pos[1] = apariciones_respiros_fuego[i][1];
                lista_objeto[id_objeto].pos[2] = apariciones_respiros_fuego[i][2];
                lista_objeto[id_objeto].angulo_sentido[1] = 0;
                if (i % 2U) {
                    lista_objeto[id_objeto].angulo_sentido[1] += 0x8000;
                }
            }
            for (i = 0; i < 32; i++) {
                eliminar_objeto(&lista_objeto_indice_4[i]);
            }
            break;
        case CIRCUITO_BANSHEE_BOARDWALK:
            if (estado_juego != SECUENCIA_CREDITOS) {
                id_objeto = lista_objeto_indice_1[0];
                inicializar_objeto_textura(id_objeto, d_circuito_banshee_boardwalk_tlut_murcielago, *d_circuito_banshee_boardwalk_murcielago,
                                    0x20U, (u16) 0x00000040);
                lista_objeto[id_objeto].orientacion[0] = 0;
                lista_objeto[id_objeto].orientacion[1] = 0;
                lista_objeto[id_objeto].orientacion[2] = 0x8000;
                inicializar_objeto(lista_objeto_indice_1[1], 0);
                inicializar_objeto(lista_objeto_indice_1[2], 0);
            }
            break;
        case CIRCUITO_YOSHI_VALLEY:
            for (i = 0; i < NUM_YV_BANDERA_POSTES; i++) {
                inicializar_objeto(lista_objeto_indice_1[i], 0);
            }
            if (estado_juego != SECUENCIA_CREDITOS) {
                for (i = 0; i < ERIZOS_NUM; i++) {
                    id_objeto = lista_objeto_indice_2[i];
                    inicializar_objeto(id_objeto, 0);
                    lista_objeto[id_objeto].pos[0] = lista_objeto[id_objeto].pos_origen[0] =
                        apariciones_erizo[i].pos[0] * orientacion_x;
                    lista_objeto[id_objeto].pos[1] = lista_objeto[id_objeto].altura_superficie =
                        apariciones_erizo[i].pos[1] + 6.0;
                    lista_objeto[id_objeto].pos[2] = lista_objeto[id_objeto].pos_origen[2] = apariciones_erizo[i].pos[2];
                    lista_objeto[id_objeto].desconocido_0D5 = apariciones_erizo[i].desconocido_06;
                    lista_objeto[id_objeto].desconocido_09C = puntos_patrulla_erizo[i][0] * orientacion_x;
                    lista_objeto[id_objeto].desconocido_09E = puntos_patrulla_erizo[i][2];
                }
            }
            break;
        case CIRCUITO_FRAPPE_SNOWLAND:
            for (i = 0; i < COPOS_NUM; i++) {
                buscar_indice_obj_sin_uso(&particula_objeto_1[i]);
            }
            if (estado_juego != SECUENCIA_CREDITOS) {
                for (i = 0; i < MUNIECOS_NIEVE_NUM; i++) {
                    id_objeto = lista_objeto_indice_2[i];
                    inicializar_objeto(id_objeto, 0);
                    lista_objeto[id_objeto].pos_origen[0] = apariciones_munieco_nieve[i].pos[0] * orientacion_x;
                    lista_objeto[id_objeto].pos_origen[1] = apariciones_munieco_nieve[i].pos[1] + 5.0 + 3.0;
                    lista_objeto[id_objeto].pos_origen[2] = apariciones_munieco_nieve[i].pos[2];
                    id_objeto = lista_objeto_indice_1[i];
                    inicializar_objeto(id_objeto, 0);
                    lista_objeto[id_objeto].pos_origen[0] = apariciones_munieco_nieve[i].pos[0] * orientacion_x;
                    lista_objeto[id_objeto].pos_origen[1] = apariciones_munieco_nieve[i].pos[1] + 3.0;
                    lista_objeto[id_objeto].pos_origen[2] = apariciones_munieco_nieve[i].pos[2];
                    lista_objeto[id_objeto].desconocido_0D5 = apariciones_munieco_nieve[i].desconocido_6;
                }
            }
            break;
        case CIRCUITO_KOOPA_BEACH:
            if (estado_juego != SECUENCIA_CREDITOS) {
                for (i = 0; i < CANGREJOS_NUM; i++) {
                    id_objeto = lista_objeto_indice_1[i];
                    inicializar_objeto(id_objeto, 0);
                    lista_objeto[id_objeto].pos[0] = lista_objeto[id_objeto].pos_origen[0] =
                        apariciones_cangrejo[i].inicio_x * orientacion_x;
                    lista_objeto[id_objeto].desconocido_01C[0] = apariciones_cangrejo[i].patrulla_x * orientacion_x;

                    lista_objeto[id_objeto].pos[2] = lista_objeto[id_objeto].pos_origen[2] = apariciones_cangrejo[i].inicio_z;
                    lista_objeto[id_objeto].desconocido_01C[2] = apariciones_cangrejo[i].patrulla_z;
                }
            }
            for (i = 0; i < GAVIOTAS_NUM; i++) {
                id_objeto = lista_objeto_indice_2[i];
                inicializar_objeto(id_objeto, 0);
                if (i < (GAVIOTAS_NUM / 2)) {
                    lista_objeto[id_objeto].desconocido_0D5 = 0;
                } else {
                    lista_objeto[id_objeto].desconocido_0D5 = 1;
                }
            }
            break;
        case CIRCUITO_ROYAL_RACEWAY:
            if (estado_juego != SECUENCIA_CREDITOS) {
                if (seleccion_modo == GRAN_PREMIO) {
                    funcion_80070714();
                }
                for (i = 0; i < dato_80165738; i++) {
                    buscar_indice_obj_sin_uso(&particula_objeto_3[i]);
                    inicializar_objeto(particula_objeto_3[i], 0);
                }
            }
            break;
        case CIRCUITO_LUIGI_RACEWAY:
            if (estado_juego != SECUENCIA_CREDITOS) {
                if (seleccion_modo == GRAN_PREMIO) {
                    funcion_80070714();
                }
                dato_80165898 = 0;
                inicializar_objeto(lista_objeto_indice_1[0], 0);
                for (i = 0; i < dato_80165738; i++) {
                    buscar_indice_obj_sin_uso(&particula_objeto_3[i]);
                    inicializar_objeto(particula_objeto_3[i], 0);
                }
            }
            break;
        case CIRCUITO_MOO_MOO_FARM:
            if (estado_juego != SECUENCIA_CREDITOS) {
                if ((cantidad_jugador == 1) || ((cantidad_jugador == 2) && (seleccion_modo == VERSUS))) {
                    switch (seleccion_cc) {
                        case CC_50:
                            dato_8018D1C8 = 4;
                            dato_8018D1D0 = 6;
                            dato_8018D1D8 = 6;
                            break;
                        case CC_100:
                            dato_8018D1C8 = 5;
                            dato_8018D1D0 = 8;
                            dato_8018D1D8 = 8;
                            break;
                        case CC_150:
                            dato_8018D1C8 = 5;
                            dato_8018D1D0 = 8;
                            dato_8018D1D8 = 10;
                            break;
                        case CC_EXTRA:
                            dato_8018D1C8 = 5;
                            dato_8018D1D0 = 8;
                            dato_8018D1D8 = 8;
                            break;
                    }
                } else {
                    dato_8018D1C8 = 4;
                    dato_8018D1D0 = 6;
                    dato_8018D1D8 = 6;
                }
                for (i = 0; i < TOPOS_GROUP1_NUM; i++) {
                    dato_8018D198[i] = 0;
                    buscar_indice_obj_sin_uso(&lista_objeto_indice_1[i]);
                }
                for (i = 0; i < TOPOS_GROUP2_NUM; i++) {
                    dato_8018D1A8[i] = 0;
                    buscar_indice_obj_sin_uso(&lista_objeto_indice_1[i]);
                }
                for (i = 0; i < TOPOS_GROUP3_NUM; i++) {
                    dato_8018D1B8[i] = 0;
                    buscar_indice_obj_sin_uso(&lista_objeto_indice_1[i]);
                }
                for (i = 0; i < TOPOS_TOTAL_NUM; i++) {
                    buscar_indice_obj_sin_uso(&particula_objeto_1[i]);
                    id_objeto = particula_objeto_1[i];
                    inicializar_objeto(id_objeto, 0);
                    lista_objeto[id_objeto].pos[0] = apariciones_topo.como_lista_vec_3_s[i][0] * orientacion_x;
                    lista_objeto[id_objeto].pos[2] = apariciones_topo.como_lista_vec_3_s[i][2];
                    funcion_800887C0(id_objeto);
                    lista_objeto[id_objeto].escalado_tamanio = 0.7f;
                }
                for (i = 0; i < objeto_particula_2_tamanio; i++) {
                    buscar_indice_obj_sin_uso(&particula_objeto_2[i]);
                }
            }
            break;
        case CIRCUITO_KALAMARI_DESERT:
            if (estado_juego != SECUENCIA_CREDITOS) {
                buscar_indice_obj_sin_uso(&dato_8018CF10);
                inicializar_objeto(dato_8018CF10, 0);
                for (i = 0; i < 50; i++) {
                    buscar_indice_obj_sin_uso(&particula_objeto_1[i]);
                }
                for (i = 0; i < 5; i++) {
                    buscar_indice_obj_sin_uso(&particula_objeto_2[i]);
                }
                for (i = 0; i < 32; i++) {
                    buscar_indice_obj_sin_uso(&particula_objeto_3[i]);
                }
            }
            break;
        case CIRCUITO_SHERBET_LAND:
            for (i = 0; i < PINGUINOS_NUM; i++) {
                inicializar_objeto(lista_objeto_indice_1[i], 0);
            }
            break;
        case CIRCUITO_RAINBOW_ROAD:
            if (estado_juego != SECUENCIA_CREDITOS) {
                for (i = 0; i < CARTELES_NEON_NUM; i++) {
                    inicializar_objeto(lista_objeto_indice_1[i], 0);
                }
                for (i = 0; i < CHOMPS_CADENA_NUM; i++) {
                    inicializar_objeto(lista_objeto_indice_2[i], 0);
                }
            }
            break;
        case CIRCUITO_DK_JUNGLE:
            for (i = 0; i < ANTORCHAS_NUM; i++) {
                inicializar_particulas_humo(i);
                if (dato_8018CF10) {}
            }
            break;
        default:
            break;
    }
#else

#endif
}

void inicializar_jugador_hud_uno(void) {
    s32 algun_indice;
    f32 algo_;
    // permuter magic
    long long por_que;
    s32 one = 1;

    dato_8018D140 = 0;
    dato_8018D150 = 0;
    dato_8018CFCC = 1.0f;
    buscar_indice_obj_sin_uso(&dato_80183DA0);
    buscar_indice_obj_sin_uso(&indice_lakitu_lista[0]);
    buscar_indice_obj_sin_uso(&indice_lakitu_lista[1]);
    buscar_indice_obj_sin_uso(&ventana_item_objeto_por_id_jugador[0]);
    buscar_indice_obj_sin_uso(&ventana_item_objeto_por_id_jugador[1]);
    inicializar_indice_lista_objeto();
    inicializar_nube_circuito();
    inicializar_nube_circuito();
    inicializar_objetos_circuito();
    h_ud_jugador[JUGADOR_UNO].velocimetro_x = 0x0156;
    h_ud_jugador[JUGADOR_UNO].velocimetro_y = 0x0106;
    dato_8018CFEC = h_ud_jugador[JUGADOR_UNO].velocimetro_x + 0x18;
    dato_8018CFF4 = h_ud_jugador[JUGADOR_UNO].velocimetro_y + 6;
    dato_8016579E = 0xDD00;
    h_ud_jugador[JUGADOR_UNO].puesto_x = 0x0034;
    h_ud_jugador[JUGADOR_UNO].puesto_y = 0x00C8;
    h_ud_jugador[JUGADOR_UNO].puesto_x_deslizamiento = 0;
    h_ud_jugador[JUGADOR_UNO].puesto_y_deslizamiento = 0;
    h_ud_jugador[JUGADOR_UNO].posicion_preparacion = gp_actual_carrera_puesto_por_id_jugador[0];
    h_ud_jugador[JUGADOR_UNO].temporizador_x = 0x012C;
    h_ud_jugador[JUGADOR_UNO].vuelta_finalizacion_tiempo_xs[0] = 0x012C;
    h_ud_jugador[JUGADOR_UNO].vuelta_finalizacion_tiempo_xs[1] = 0x012C;
    h_ud_jugador[JUGADOR_UNO].temporizador_y = 0x0011;
    h_ud_jugador[JUGADOR_UNO].vuelta_x = -0x0028;
    h_ud_jugador[JUGADOR_UNO].vuelta_despues_imagen_1_x = -0x0028;
    h_ud_jugador[JUGADOR_UNO].vuelta_despues_imagen_2_x = -0x0028;
    h_ud_jugador[JUGADOR_UNO].vuelta_y = 0x0019;
    h_ud_jugador[JUGADOR_UNO].caja_item_x = 0x00A0;
    h_ud_jugador[JUGADOR_UNO].caja_item_y = -0x0020;
    h_ud_jugador[JUGADOR_UNO].deslizamiento_caja_item_x = 0;
    h_ud_jugador[JUGADOR_UNO].deslizamiento_caja_item_y = 0;
    // permuter magic
    por_que = 0x000000A0;
    inicializar_ventana_item(ventana_item_objeto_por_id_jugador[0]);
    for (algun_indice = 0, algo_ = 35.0f; algun_indice < 8; algun_indice++, algo_ += 32.0) {
        dato_8018D0C8[algun_indice] = 40.0f;
        dato_8018D028[algun_indice] = -24.0f;
        dato_8018D050[algun_indice] = algo_;
        dato_8018D0F0[algun_indice] = algo_;
        dato_8018D0A0[algun_indice] = 0.0f;
        dato_8018D078[algun_indice] = 0.0f;
    }
    dato_8018CFD4 = 1.0f;
    dato_8018D3D4 = dato_8018D3D8 = dato_8018D3DC = 0x000000FF;
    dato_8018D3E0 = por_que;
    dato_8018D3E4 = 0x000000FF;
    dato_8018D3E8 = 0x000000FF;
    dato_8018D3EC = 0x000000FF;
    dato_8018D3F0 = 0x000000FF;
    dato_8018D3F4 = one;
    h_ud_jugador[JUGADOR_UNO].desconocido_4C = 0x0078;
    h_ud_jugador[JUGADOR_UNO].desconocido_4A = 0x00A0;
    h_ud_jugador[JUGADOR_UNO].escalado_puesto = 0.5f;
    dato_801656B0 = 0;
    dato_80165708 = 0x0028;
    dato_8018D00C = 5.0f;
    dato_8018D388 = 4;
    dato_8018D380 = 0x00A0;
    dato_8018D384 = 0x0078;
    dato_8018D3C4 = 0x00000032;
    dato_8018D3BC = 0x0028;
    dato_8018D3C0 = 0x00000050;
    dato_801657A2 = (4.5f * GRADOS(1));
    switch (seleccion_modo) { /* irregular */
        case 0:
            dato_8018D158 = 8;
            break;
        case 1:
            dato_80165638 = (funcion_800B4F2C() & 0xFFFFF) - 1;
            dato_80165648 = funcion_800B4E24(0) & 0xFFFFF;
            dato_80165888 = 1;
            dato_80165890 = 1;
            dato_8018D158 = 1;
            break;
    }
}

void inicializar_vertical_jugador_hud_dos(void) {
    buscar_indice_obj_sin_uso(&dato_80183DA0);

    buscar_indice_obj_sin_uso(&indice_lakitu_lista[0]);
    buscar_indice_obj_sin_uso(&indice_lakitu_lista[1]);

    buscar_indice_obj_sin_uso(&ventana_item_objeto_por_id_jugador[0]);
    buscar_indice_obj_sin_uso(&ventana_item_objeto_por_id_jugador[1]);

    inicializar_indice_lista_objeto();
    inicializar_nube_circuito();
    inicializar_nube_circuito();
    inicializar_objetos_circuito();

    h_ud_jugador[JUGADOR_UNO].caja_item_x = -0x52;
    h_ud_jugador[JUGADOR_UNO].caja_item_y = 0x32;
    h_ud_jugador[JUGADOR_UNO].deslizamiento_caja_item_x = 0;
    h_ud_jugador[JUGADOR_UNO].deslizamiento_caja_item_y = 0;
    h_ud_jugador[JUGADOR_UNO].desconocido_4A = 0x50;
    h_ud_jugador[JUGADOR_UNO].desconocido_4C = 0x78;
    h_ud_jugador[JUGADOR_UNO].puesto_x = 0x32;
    h_ud_jugador[JUGADOR_UNO].puesto_y = 0xD2;
    h_ud_jugador[JUGADOR_UNO].puesto_x_deslizamiento = 0;
    h_ud_jugador[JUGADOR_UNO].puesto_y_deslizamiento = 0;
    h_ud_jugador[JUGADOR_UNO].temporizador_x = 0x4B;
    h_ud_jugador[JUGADOR_UNO].temporizador_y = 0x10;
    h_ud_jugador[JUGADOR_UNO].vuelta_x = 0x67;
    h_ud_jugador[JUGADOR_UNO].vuelta_y = 0x28;
    inicializar_ventana_item(ventana_item_objeto_por_id_jugador[JUGADOR_UNO]);

    h_ud_jugador[JUGADOR_DOS].caja_item_x = 0x43;
    h_ud_jugador[JUGADOR_DOS].caja_item_y = 0x32;
    h_ud_jugador[JUGADOR_DOS].deslizamiento_caja_item_x = 0;
    h_ud_jugador[JUGADOR_DOS].deslizamiento_caja_item_y = 0;
    h_ud_jugador[JUGADOR_DOS].desconocido_4A = 0xF0;
    h_ud_jugador[JUGADOR_DOS].desconocido_4C = 0x78;
    h_ud_jugador[JUGADOR_DOS].puesto_x = 0xC8;
    h_ud_jugador[JUGADOR_DOS].puesto_y = 0xD2;
    h_ud_jugador[JUGADOR_DOS].puesto_x_deslizamiento = 0;
    h_ud_jugador[JUGADOR_DOS].puesto_y_deslizamiento = 0;
    h_ud_jugador[JUGADOR_DOS].temporizador_x = 0xDC;
    h_ud_jugador[JUGADOR_DOS].temporizador_y = 0x10;
    h_ud_jugador[JUGADOR_DOS].vuelta_x = 0xF7;
    h_ud_jugador[JUGADOR_DOS].vuelta_y = 0x28;
    inicializar_ventana_item(ventana_item_objeto_por_id_jugador[JUGADOR_DOS]);

    h_ud_jugador[JUGADOR_UNO].posicion_preparacion = (s16) gp_actual_carrera_puesto_por_id_jugador[0];
    h_ud_jugador[JUGADOR_DOS].posicion_preparacion = (s16) gp_actual_carrera_puesto_por_id_jugador[1];

    h_ud_jugador[JUGADOR_UNO].escalado_puesto = h_ud_jugador[JUGADOR_DOS].escalado_puesto = 0.5f;

    dato_8018D3C4 = 0x1E;
    dato_8018D3BC = 0x18;
    dato_8018D3C0 = 0x28;
    dato_801657A2 = GRADOS(9);
    switch (seleccion_modo) { /* irregular */
        case GRAN_PREMIO:
            dato_8018D158 = 8;
            break;
        case VERSUS:
            dato_8018D158 = 2;
            break;
        case BATALLA:
            dato_8018D158 = 2;
            break;
    }
}

void inicializar_horizontal_jugador_hud_dos() {
    buscar_indice_obj_sin_uso(&dato_80183DA0);

    buscar_indice_obj_sin_uso(&indice_lakitu_lista[0]);
    buscar_indice_obj_sin_uso(&indice_lakitu_lista[1]);

    buscar_indice_obj_sin_uso(&ventana_item_objeto_por_id_jugador[0]);
    buscar_indice_obj_sin_uso(&ventana_item_objeto_por_id_jugador[1]);

    inicializar_indice_lista_objeto();
    inicializar_nube_circuito();
    inicializar_nube_circuito();
    inicializar_objetos_circuito();

    h_ud_jugador[JUGADOR_UNO].caja_item_y = 0x22;
    h_ud_jugador[JUGADOR_UNO].caja_item_x = -0x53;
    h_ud_jugador[JUGADOR_UNO].deslizamiento_caja_item_x = 0;
    h_ud_jugador[JUGADOR_UNO].deslizamiento_caja_item_y = 0;
    h_ud_jugador[JUGADOR_UNO].desconocido_4A = 0xA0;
    h_ud_jugador[JUGADOR_UNO].desconocido_4C = 0x3C;
    h_ud_jugador[JUGADOR_UNO].puesto_x = 0x34;
    h_ud_jugador[JUGADOR_UNO].puesto_y = 0x62;
    h_ud_jugador[JUGADOR_UNO].puesto_x_deslizamiento = 0;
    h_ud_jugador[JUGADOR_UNO].puesto_y_deslizamiento = 0;
    h_ud_jugador[JUGADOR_UNO].temporizador_x = 0xEA;
    h_ud_jugador[JUGADOR_UNO].temporizador_y = 0x10;
    h_ud_jugador[JUGADOR_UNO].vuelta_x = 0x101;
    h_ud_jugador[JUGADOR_UNO].vuelta_y = 0x6A;

    h_ud_jugador[JUGADOR_DOS].caja_item_x = -0x53;
    h_ud_jugador[JUGADOR_DOS].caja_item_y = 0x8F;
    h_ud_jugador[JUGADOR_DOS].deslizamiento_caja_item_x = 0;
    h_ud_jugador[JUGADOR_DOS].deslizamiento_caja_item_y = 0;
    h_ud_jugador[JUGADOR_DOS].desconocido_4A = 0xA0;
    h_ud_jugador[JUGADOR_DOS].desconocido_4C = 0xB4;
    h_ud_jugador[JUGADOR_DOS].puesto_x = 0x34;
    h_ud_jugador[JUGADOR_DOS].puesto_y = 0xD2;
    h_ud_jugador[JUGADOR_DOS].puesto_x_deslizamiento = 0;
    h_ud_jugador[JUGADOR_DOS].puesto_y_deslizamiento = 0;
    h_ud_jugador[JUGADOR_DOS].temporizador_x = 0xEA;
    h_ud_jugador[JUGADOR_DOS].temporizador_y = 0x7F;
    h_ud_jugador[JUGADOR_DOS].vuelta_x = 0x101;
    h_ud_jugador[JUGADOR_DOS].vuelta_y = 0xDA;

    if (seleccion_modo == BATALLA) {
        h_ud_jugador[JUGADOR_UNO].caja_item_y = 0x5E;
        h_ud_jugador[JUGADOR_DOS].caja_item_y = 0xD0;
    }

    h_ud_jugador[JUGADOR_UNO].escalado_puesto = h_ud_jugador[JUGADOR_DOS].escalado_puesto = 0.5f;

    h_ud_jugador[JUGADOR_UNO].posicion_preparacion = (s16) gp_actual_carrera_puesto_por_id_jugador[0];
    h_ud_jugador[JUGADOR_DOS].posicion_preparacion = (s16) gp_actual_carrera_puesto_por_id_jugador[1];

    inicializar_ventana_item(ventana_item_objeto_por_id_jugador[0]);
    inicializar_ventana_item((ventana_item_objeto_por_id_jugador[1]));

    dato_8018D3C4 = 0x1E;
    dato_8018D3BC = 0x18;
    dato_8018D3C0 = 0x28;
    dato_801657A2 = GRADOS(9);
    switch (seleccion_modo) { /* irregular */
        case GRAN_PREMIO:
            dato_8018D158 = 8;
            return;
        case VERSUS:
            dato_8018D158 = 2;
            return;
        case BATALLA:
            dato_8018D158 = 2;
            return;
    }
}

void inicializar_jugador_hud_tres_cuatro(void) {
    buscar_indice_obj_sin_uso(&dato_80183DA0);

    buscar_indice_obj_sin_uso(&indice_lakitu_lista[0]);
    buscar_indice_obj_sin_uso(&indice_lakitu_lista[1]);
    buscar_indice_obj_sin_uso(&indice_lakitu_lista[2]);
    buscar_indice_obj_sin_uso(&indice_lakitu_lista[3]);

    buscar_indice_obj_sin_uso(&ventana_item_objeto_por_id_jugador[0]);
    buscar_indice_obj_sin_uso(&ventana_item_objeto_por_id_jugador[1]);
    buscar_indice_obj_sin_uso(&ventana_item_objeto_por_id_jugador[2]);
    buscar_indice_obj_sin_uso(&ventana_item_objeto_por_id_jugador[3]);

    inicializar_indice_lista_objeto();
    inicializar_objetos_circuito();

    h_ud_jugador[JUGADOR_UNO].caja_item_x = -0x36;
    h_ud_jugador[JUGADOR_UNO].caja_item_y = 0x36;
    h_ud_jugador[JUGADOR_UNO].deslizamiento_caja_item_x = 0;
    h_ud_jugador[JUGADOR_UNO].deslizamiento_caja_item_y = 0;
    h_ud_jugador[JUGADOR_UNO].desconocido_4A = 0x50;
    h_ud_jugador[JUGADOR_UNO].desconocido_4C = 0x3C;
    h_ud_jugador[JUGADOR_UNO].puesto_x = 0x25;
    h_ud_jugador[JUGADOR_UNO].puesto_y = 0x64;
    h_ud_jugador[JUGADOR_UNO].puesto_x_deslizamiento = 0;
    h_ud_jugador[JUGADOR_UNO].puesto_y_deslizamiento = 0;
    h_ud_jugador[JUGADOR_UNO].vuelta_x = 0x8C;
    h_ud_jugador[JUGADOR_UNO].vuelta_y = 0x60;
    h_ud_jugador[JUGADOR_UNO].desconocido_6C = 0xDE;
    h_ud_jugador[JUGADOR_UNO].desconocido_6E = 0xC8;

    h_ud_jugador[JUGADOR_DOS].caja_item_x = 0x175;
    h_ud_jugador[JUGADOR_DOS].caja_item_y = 0x36;
    h_ud_jugador[JUGADOR_DOS].deslizamiento_caja_item_x = 0;
    h_ud_jugador[JUGADOR_DOS].deslizamiento_caja_item_y = 0;
    h_ud_jugador[JUGADOR_DOS].desconocido_4A = 0xF0;
    h_ud_jugador[JUGADOR_DOS].desconocido_4C = 0x3C;
    h_ud_jugador[JUGADOR_DOS].puesto_x = 0x11A;
    h_ud_jugador[JUGADOR_DOS].puesto_y = 0x64;
    h_ud_jugador[JUGADOR_DOS].puesto_x_deslizamiento = 0;
    h_ud_jugador[JUGADOR_DOS].puesto_y_deslizamiento = 0;
    h_ud_jugador[JUGADOR_DOS].vuelta_x = 0xB4;
    h_ud_jugador[JUGADOR_DOS].vuelta_y = 0x60;
    h_ud_jugador[JUGADOR_DOS].desconocido_6C = 0xC8;
    h_ud_jugador[JUGADOR_DOS].desconocido_6E = 0xC8;

    h_ud_jugador[JUGADOR_TRES].caja_item_x = -0x36;
    h_ud_jugador[JUGADOR_TRES].caja_item_y = 0x2D;
    h_ud_jugador[JUGADOR_TRES].deslizamiento_caja_item_x = 0;
    h_ud_jugador[JUGADOR_TRES].deslizamiento_caja_item_y = 0;
    h_ud_jugador[JUGADOR_TRES].desconocido_4A = 0x50;
    h_ud_jugador[JUGADOR_TRES].desconocido_4C = 0xB4;
    h_ud_jugador[JUGADOR_TRES].puesto_x = 0x25;
    h_ud_jugador[JUGADOR_TRES].puesto_y = 0xD2;
    h_ud_jugador[JUGADOR_TRES].puesto_x_deslizamiento = 0;
    h_ud_jugador[JUGADOR_TRES].puesto_y_deslizamiento = 0;
    h_ud_jugador[JUGADOR_TRES].vuelta_x = 0x8C;
    h_ud_jugador[JUGADOR_TRES].vuelta_y = 0xD4;
    h_ud_jugador[JUGADOR_TRES].desconocido_6C = 0xDE;
    h_ud_jugador[JUGADOR_TRES].desconocido_6E = 0xC0;

    h_ud_jugador[JUGADOR_CUATRO].caja_item_x = 0x175;
    h_ud_jugador[JUGADOR_CUATRO].caja_item_y = 0x2D;
    h_ud_jugador[JUGADOR_CUATRO].deslizamiento_caja_item_x = 0;
    h_ud_jugador[JUGADOR_CUATRO].deslizamiento_caja_item_y = 0;
    h_ud_jugador[JUGADOR_CUATRO].desconocido_4A = 0xF0;
    h_ud_jugador[JUGADOR_CUATRO].desconocido_4C = 0xB4;
    h_ud_jugador[JUGADOR_CUATRO].puesto_x = 0x11A;
    h_ud_jugador[JUGADOR_CUATRO].puesto_y = 0xD2;
    h_ud_jugador[JUGADOR_CUATRO].puesto_x_deslizamiento = 0;
    h_ud_jugador[JUGADOR_CUATRO].puesto_y_deslizamiento = 0;
    h_ud_jugador[JUGADOR_CUATRO].vuelta_x = 0xB4;
    h_ud_jugador[JUGADOR_CUATRO].vuelta_y = 0xD4;
    h_ud_jugador[JUGADOR_CUATRO].desconocido_6C = 0xC8;
    h_ud_jugador[JUGADOR_CUATRO].desconocido_6E = 0xC0;

    if (seleccion_modo == BATALLA) {
        h_ud_jugador[JUGADOR_UNO].caja_item_y = 0xC8;
        h_ud_jugador[JUGADOR_DOS].caja_item_y = 0xC8;
        h_ud_jugador[JUGADOR_TRES].caja_item_y = 0xB8;
        h_ud_jugador[JUGADOR_CUATRO].caja_item_y = 0xB8;
    }

    h_ud_jugador[JUGADOR_UNO].escalado_puesto = h_ud_jugador[JUGADOR_DOS].escalado_puesto = h_ud_jugador[JUGADOR_TRES].escalado_puesto =
        h_ud_jugador[JUGADOR_CUATRO].escalado_puesto = 0.5f;

    h_ud_jugador[JUGADOR_UNO].posicion_preparacion = (s16) gp_actual_carrera_puesto_por_id_jugador[0];
    h_ud_jugador[JUGADOR_DOS].posicion_preparacion = (s16) gp_actual_carrera_puesto_por_id_jugador[1];
    h_ud_jugador[JUGADOR_TRES].posicion_preparacion = (s16) gp_actual_carrera_puesto_por_id_jugador[2];
    h_ud_jugador[JUGADOR_CUATRO].posicion_preparacion = (s16) gp_actual_carrera_puesto_por_id_jugador[3];

    inicializar_ventana_item(ventana_item_objeto_por_id_jugador[0]);
    inicializar_ventana_item(ventana_item_objeto_por_id_jugador[1]);
    inicializar_ventana_item(ventana_item_objeto_por_id_jugador[2]);
    inicializar_ventana_item(ventana_item_objeto_por_id_jugador[3]);

    h_ud_jugador[JUGADOR_UNO].escalado_desconocido = h_ud_jugador[JUGADOR_DOS].escalado_desconocido =
        h_ud_jugador[JUGADOR_TRES].escalado_desconocido = h_ud_jugador[JUGADOR_CUATRO].escalado_desconocido = 1.5f;

    dato_8018D158 = (s32) cantidad_jugador;
    dato_8018D3C4 = 0x00000014;
    dato_8018D3BC = 0x00000010;
    dato_8018D3C0 = 0x0000001E;
    dato_801657A2 = GRADOS(12);
}
