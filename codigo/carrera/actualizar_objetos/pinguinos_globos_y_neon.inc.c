// Pinguinos globos y neon

void funcion_800842C8(void) {
    s32 indice_objeto;
    s32 id_jugador;

    dato_80165834[0] += 0x200;
    dato_80165834[1] += 0x400;
    funcion_800419F8();
    dato_8016582C[0] += 0x2000;
    dato_8016582C[1] += 0x1000;
    dato_8016582C[2] += 0x1800;
    for (id_jugador = 0; id_jugador < seleccion_cantidad_jugador_1; id_jugador++) {
        indice_objeto = indice_lakitu_lista[id_jugador];
        if (funcion_80072320(indice_objeto, 0x00000020) != 0) {
            funcion_800722CC(indice_objeto, 0x00000020);
            funcion_8008421C(indice_objeto, id_jugador);
        }
    }
    for (id_jugador = 0; id_jugador < objeto_particula_2_tamanio; id_jugador++) {
        indice_objeto = particula_objeto_2[id_jugador];
        if (indice_objeto != ID_OBJETO_ELIMINADO) {
            if (lista_objeto[indice_objeto].state != 0) {
                funcion_80083F18(indice_objeto);
                if (lista_objeto[indice_objeto].state == 0) {
                    eliminar_envoltorio_objeto(&particula_objeto_2[id_jugador]);
                }
            }
        }
    }
}

void funcion_80084430(s32 indice_objeto, SIN_USO s32 parametro1) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->desconocido_0D8 = 0;
    objeto->model = (Gfx*) d_circuito_sherbet_land_datos1_desconocido;
    objeto->vertice = (Vtx*) d_circuito_sherbet_land_datos11_desconocido;
    objeto->escalado_tamanio = 0.2f;
    objeto->tamanio_caja_envolvente = 0x000C;
    objeto->desconocido_09C = 1;
    fijar_pos_origen_obj(indice_objeto, orientacion_x * -383.0, 2.0f, -690.0f);
    fijar_angulo_sentido_obj(indice_objeto, 0U, 0U, 0U);
    objeto->desconocido_0DD = 1;
    funcion_80086EF0(indice_objeto);
    objeto->spline = dato_800E672C[0];
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x04000800);
    objeto->type = obtener_longitud_animacion(d_circuito_sherbet_land_datos11_desconocido, 0);
    estado_siguiente_objeto(indice_objeto);
}

void funcion_8008453C(s32 indice_objeto, s32 parametro1) {
    switch (lista_objeto[indice_objeto].state) { /* irregular */
        case 0:
            break;
        case 1:
            if (seleccion_cantidad_jugador_1 == 1) {
                funcion_80084430(indice_objeto, parametro1);
            }
            break;
        case 2:
            funcion_80072E54(indice_objeto, 0, lista_objeto[indice_objeto].type, 1, 0, -1);
            break;
    }
}

void funcion_800845C8(s32 indice_objeto, s32 parametro1) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->desconocido_0D8 = 0;
    objeto->model = (Gfx*) d_circuito_sherbet_land_datos1_desconocido;
    objeto->vertice = (Vtx*) d_circuito_sherbet_land_datos11_desconocido;
    objeto->tamanio_caja_envolvente = 4;
    objeto->desconocido_09C = 2;
    objeto->desconocido_04C = int_aleatorio(0x012CU);
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x04000220);
    if ((parametro1 > 0) && (parametro1 < 9)) {
        if ((parametro1 == 1) || (parametro1 == 2)) {
            fijar_pos_origen_obj(indice_objeto, orientacion_x * -2960.0, -80.0f, 1521.0f);
            objeto->desconocido_0C6 = 0x0150;
            objeto->desconocido_01C[1] = 100.0f;
        } else if ((parametro1 == 3) || (parametro1 == 4)) {
            fijar_pos_origen_obj(indice_objeto, orientacion_x * -2490.0, -80.0f, 1612.0f);
            objeto->desconocido_0C6 = 0x0100;
            objeto->desconocido_01C[1] = 80.0f;
        } else if ((parametro1 == 5) || (parametro1 == 6)) {
            fijar_pos_origen_obj(indice_objeto, orientacion_x * -2098.0, -80.0f, 1624.0f);
            objeto->desconocido_0C6 = 0xFF00;
            objeto->desconocido_01C[1] = 80.0f;
        } else if ((parametro1 == 7) || (parametro1 == 8)) {
            fijar_pos_origen_obj(indice_objeto, orientacion_x * -2080.0, -80.0f, 1171.0f);
            objeto->desconocido_0C6 = 0x0150;
            objeto->desconocido_01C[1] = 80.0f;
        }
        objeto->desconocido_0C4 = (parametro1 << 0xF) & 0xFFFF;
        objeto->altura_superficie = -80.0f;
        objeto->escalado_tamanio = 0.08f;
        objeto->desconocido_0DD = 2;
        funcion_800722A4(indice_objeto, 8);
    } else if ((parametro1 > 8) && (parametro1 < 15)) {
        switch (parametro1) { /* irregular */
            case 9:
                if (estado_juego != 9) {
                    fijar_pos_origen_obj(indice_objeto, orientacion_x * 146.0, 0.0f, -380.0f);
                } else {
                    fijar_pos_origen_obj(indice_objeto, orientacion_x * 380.0, 0.0f, -535.0f);
                    objeto->escalado_tamanio = 0.15f;
                }
                objeto->desconocido_0C6 = 0x9000;
                if (es_modo_espejo != 0) {
                    objeto->desconocido_0C6 -= 0x4000;
                }
                objeto->desconocido_0DD = 3;
                break;
            case 10:
                fijar_pos_origen_obj(indice_objeto, orientacion_x * 380.0, 0.0f, -766.0f);
                objeto->desconocido_0C6 = 0x5000;
                if (es_modo_espejo != 0) {
                    objeto->desconocido_0C6 += 0x8000;
                }
                objeto->desconocido_0DD = 4;
                break;
            case 11:
                fijar_pos_origen_obj(indice_objeto, orientacion_x * -2300.0, 0.0f, -210.0f);
                objeto->desconocido_0C6 = 0xC000;
                objeto->desconocido_0DD = 6;
                if (es_modo_espejo != 0) {
                    objeto->desconocido_0C6 += 0x8000;
                }
                break;
            case 12:
                fijar_pos_origen_obj(indice_objeto, orientacion_x * -2500.0, 0.0f, -250.0f);
                objeto->desconocido_0C6 = 0x4000;
                objeto->desconocido_0DD = 6;
                if (es_modo_espejo != 0) {
                    objeto->desconocido_0C6 += 0x8000;
                }
                break;
            case 13:
                fijar_pos_origen_obj(indice_objeto, orientacion_x * -535.0, 0.0f, 875.0f);
                objeto->desconocido_0C6 = 0x8000;
                objeto->desconocido_0DD = 6;
                if (es_modo_espejo != 0) {
                    objeto->desconocido_0C6 -= 0x4000;
                }
                break;
            case 14:
                fijar_pos_origen_obj(indice_objeto, orientacion_x * -250.0, 0.0f, 953.0f);
                objeto->desconocido_0C6 = 0x9000;
                objeto->desconocido_0DD = 6;
                if (es_modo_espejo != 0) {
                    objeto->desconocido_0C6 -= 0x4000;
                }
                break;
            default:
                break;
        }
        fijar_angulo_sentido_obj(indice_objeto, 0U, objeto->desconocido_0C6 + 0x8000, 0U);
        objeto->altura_superficie = 5.0f;
        objeto->escalado_tamanio = 0.04f;
        funcion_800722A4(indice_objeto, 0x00000014);
    }
    funcion_80086EF0(indice_objeto);
    objeto->desconocido_034 = 0.0f;
    objeto->type = obtener_longitud_animacion(d_circuito_sherbet_land_datos11_desconocido, 0);
    estado_siguiente_objeto(indice_objeto);
}

void funcion_80084B7C(s32 indice_objeto, s32 parametro1) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    switch (objeto->state) {
        case 0:
            break;
        case 1:
            funcion_800845C8(indice_objeto, parametro1);
            break;
        case 2:
            funcion_80072E54(indice_objeto, 0, (s32) objeto->type, (s32) objeto->desconocido_09C, 0, -1);
            if (funcion_80072354(indice_objeto, 0x00000020) != 0) {
                if (objeto->desconocido_084[6] == 0) {
                    objeto->desconocido_084[6] = int_aleatorio(0x005AU) + 0x5A;
                    funcion_800722A4(indice_objeto, 0x00000080);
                } else {
                    objeto->desconocido_084[6]--;
                }
            }
            break;
        case 3:
            funcion_80072E54(indice_objeto, 0, objeto->type, 1, 0, 0);
            break;
        case 4:
            funcion_800722CC(indice_objeto, 2);
            estado_siguiente_objeto(indice_objeto);
            break;
    }
    if (funcion_80072320(indice_objeto, 0x00000020) != 0) {
        if (objeto->desconocido_084[6] == 0) {
            funcion_800722A4(indice_objeto, 0x00000080);
            objeto->desconocido_084[6] = 0x0010;
        } else {
            objeto->desconocido_084[6]--;
        }
    }
    if (funcion_80072320(indice_objeto, 0x00000080) != 0) {
        funcion_800722CC(indice_objeto, 0x00000080);
        if (funcion_80072320(indice_objeto, 0x00000010) != 0) {
            funcion_800C98B8(objeto->pos, objeto->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x70, 0x49));
        } else {
            funcion_800C98B8(objeto->pos, objeto->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x70, 0x17));
        }
    }
}

void funcion_80084D2C(s32 indice_objeto, s32 parametro1) {
    f32 sp24;

    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 0:
            break;
        case 1:
            lista_objeto[indice_objeto].angulo_sentido[1] =
                funcion_800417B4(lista_objeto[indice_objeto].angulo_sentido[1], lista_objeto[indice_objeto].desconocido_0C6);
            if (lista_objeto[indice_objeto].angulo_sentido[1] == lista_objeto[indice_objeto].desconocido_0C6) {
                lista_objeto[indice_objeto].desconocido_09C = 4;
                lista_objeto[indice_objeto].desconocido_034 = 0.4f;
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 2:
            paso_f32_hacia(&lista_objeto[indice_objeto].desconocido_034, 0.8f, 0.02f);
            if (funcion_80087060(indice_objeto, 0x0000000F) != 0) {
                funcion_800722A4(indice_objeto, 1);
                funcion_800722A4(indice_objeto, 2);
                lista_objeto[indice_objeto].desconocido_09C = 1;
                lista_objeto[indice_objeto].desconocido_0D8 = 1;
                lista_objeto[indice_objeto].textura_indice_lista = 0;
                lista_objeto[indice_objeto].type =
                    obtener_longitud_animacion(d_circuito_sherbet_land_datos11_desconocido, lista_objeto[indice_objeto].desconocido_0D8);
                funcion_800726CC(indice_objeto, 3);
                funcion_80086FD4(indice_objeto);
                if (funcion_80072354(indice_objeto, 0x00000020) != 0) {
                    funcion_800722A4(indice_objeto, 0x00000080);
                }
            }
            break;
        case 3:
            switch (parametro1) {
                case 0:
                    sp24 = 1.0f;
                    break;
                case 1:
                    sp24 = 1.5f;
                    break;
                case 2:
                    sp24 = 2.0f;
                    break;
                case 3:
                    sp24 = 2.5f;
                    break;
            }
            paso_f32_hacia(&lista_objeto[indice_objeto].desconocido_034, sp24, 0.15f);
            if ((funcion_80072354(indice_objeto, 2) != 0) && (sp24 == lista_objeto[indice_objeto].desconocido_034)) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 4:
            if (funcion_80087060(indice_objeto, 0x0000001E) != 0) {
                funcion_800722CC(indice_objeto, 1);
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 5:
            paso_f32_hacia(&lista_objeto[indice_objeto].desconocido_034, 0.4f, 0.2f);
            if (funcion_80087060(indice_objeto, 0x0000000A) != 0) {
                funcion_800722A4(indice_objeto, 2);
                lista_objeto[indice_objeto].desconocido_0D8 = 2;
                lista_objeto[indice_objeto].textura_indice_lista = 0;
                lista_objeto[indice_objeto].type =
                    obtener_longitud_animacion(d_circuito_sherbet_land_datos11_desconocido, lista_objeto[indice_objeto].desconocido_0D8);
                funcion_800726CC(indice_objeto, 3);
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 6:
            if (funcion_80072354(indice_objeto, 2) != 0) {
                lista_objeto[indice_objeto].desconocido_0D8 = 0;
                lista_objeto[indice_objeto].textura_indice_lista = 0;
                lista_objeto[indice_objeto].type =
                    obtener_longitud_animacion(d_circuito_sherbet_land_datos11_desconocido, lista_objeto[indice_objeto].desconocido_0D8);
                lista_objeto[indice_objeto].desconocido_0C6 += 0x8000;
                funcion_800726CC(indice_objeto, 2);
                funcion_8008701C(indice_objeto, 1);
            }
            break;
    }
    funcion_8008781C(indice_objeto);
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void funcion_80085024(void) {
}

void funcion_8008502C(s32 indice_objeto, SIN_USO s32 parametro1) {
    funcion_80088038(indice_objeto, lista_objeto[indice_objeto].desconocido_01C[1], lista_objeto[indice_objeto].desconocido_0C6);
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
    funcion_800873F4(indice_objeto);
}

void funcion_80085080(s32 indice_objeto) {
    funcion_8008B78C(indice_objeto);
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
    funcion_800873F4(indice_objeto);
}

void funcion_800850B0(s32 indice_objeto, s32 parametro1) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    switch (objeto->desconocido_0DD) {
        case 1:
            funcion_80085080(indice_objeto);
            break;
        case 2:
            funcion_8008502C(indice_objeto, parametro1);
            break;
        case 3:
            funcion_80084D2C(indice_objeto, 0);
            break;
        case 4:
            funcion_80084D2C(indice_objeto, 1);
            break;
        case 5:
            funcion_80084D2C(indice_objeto, 2);
            break;
        case 6:
            funcion_80084D2C(indice_objeto, 3);
            break;
    }
    if (funcion_80072320(indice_objeto, 0x00000020) != 0) {
        if (funcion_80072320(indice_objeto, 0x00000040) != 0) {
            funcion_800722CC(indice_objeto, 0x00000040);
            objeto->desconocido_084[6] = 0;
            objeto->desconocido_084[7] = 0x0096;
        }
        if (objeto->desconocido_084[7] == 0) {
            funcion_800722CC(indice_objeto, 0x00000020);
        } else {
            objeto->desconocido_084[7]--;
            objeto->orientacion[0] = objeto->angulo_sentido[0];
            objeto->orientacion[1] += 0x2000;
            objeto->orientacion[2] = objeto->angulo_sentido[2];
        }
    } else {
        objeto->orientacion[0] = objeto->angulo_sentido[0];
        objeto->orientacion[1] = objeto->angulo_sentido[1];
        objeto->orientacion[2] = objeto->angulo_sentido[2];
    }
}

void actualizar_pinguinos(void) {
    SIN_USO s32 variable_s2;
    s32 indice_objeto;
    s32 variable_s1;

    for (variable_s1 = 0; variable_s1 < PINGUINOS_NUM; variable_s1++) {
        indice_objeto = lista_objeto_indice_1[variable_s1];
        if (lista_objeto[indice_objeto].state != 0) {
            if (variable_s1 == 0) {
                funcion_8008453C(indice_objeto, variable_s1);
            } else {
                funcion_80084B7C(indice_objeto, variable_s1);
            }
            funcion_800850B0(indice_objeto, variable_s1);
        }
        if (funcion_80072320(indice_objeto, 1) != 0) {
            funcion_80089820(indice_objeto, 1.75f, 1.5f, 0x1900A046U);
        } else if (funcion_80072320(indice_objeto, 8) != 0) {
            funcion_80089820(indice_objeto, 1.3f, 1.0f, 0x1900A046U);
        } else {
            funcion_80089820(indice_objeto, 1.5f, 1.25f, 0x1900A046U);
        }
        if ((es_obj_bandera_situacion_activo(indice_objeto, 0x02000000) != 0) &&
            (funcion_80072354(indice_objeto, 0x00000020) != 0)) {
            funcion_800722A4(indice_objeto, 0x00000060);
            fijar_objeto_bandera_situacion_false(indice_objeto, 0x02000000);
        }
    }
}

void inicializar_globo_aerostatico(s32 indice_objeto) {
    lista_objeto[indice_objeto].escalado_tamanio = 1.0f;
    lista_objeto[indice_objeto].model = d_circuito_luigi_raceway_dl_F960;
    if (estado_juego != 9) {
        fijar_pos_origen_obj(indice_objeto, orientacion_x * -176.0, 0.0f, -2323.0f);
        fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 300.0f, 0.0f);
    } else {
        fijar_pos_origen_obj(indice_objeto, orientacion_x * -1250.0, 0.0f, 1110.0f);
        fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 300.0f, 0.0f);
    }
    funcion_8008B844(indice_objeto);
    funcion_800886F4(indice_objeto);
    funcion_80086EF0(indice_objeto);
    lista_objeto[indice_objeto].velocidad[1] = -2.0f;
    inicializar_actor_globo_aerostatico_caja_item(0.0f, 0.0f, 0.0f);
    estado_siguiente_objeto(indice_objeto);
}

void funcion_80085534(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 1:
            if (lista_objeto[indice_objeto].offset[1] <= 18.0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 2:
            paso_f32_hacia(&lista_objeto[indice_objeto].velocidad[1], 0.0f, 0.05f);
            if (lista_objeto[indice_objeto].velocidad[1] == 0.0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 3:
            funcion_800871AC(indice_objeto, 1);
            break;
        case 4:
            paso_f32_hacia(&lista_objeto[indice_objeto].velocidad[1], 1.0f, 0.05f);
            if (lista_objeto[indice_objeto].velocidad[1] == 1.0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 5:
            funcion_800871AC(indice_objeto, 0x0000005A);
            break;
        case 6:
            paso_f32_hacia(&lista_objeto[indice_objeto].velocidad[1], 0.0f, 0.05f);
            if (lista_objeto[indice_objeto].velocidad[1] == 0.0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 7:
            paso_f32_hacia(&lista_objeto[indice_objeto].velocidad[1], -1.0f, 0.05f);
            if (lista_objeto[indice_objeto].velocidad[1] == -1.0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 8:
            funcion_800871AC(indice_objeto, 0x0000005A);
            break;
        case 9:
            paso_f32_hacia(&lista_objeto[indice_objeto].velocidad[1], 0.0f, 0.05f);
            if (funcion_80087060(indice_objeto, 0x0000005A) != 0) {
                funcion_8008701C(indice_objeto, 3);
            }
            break;
    }
    agregar_desplazamiento_y_velocidad_objeto(indice_objeto);
    lista_objeto[indice_objeto].angulo_sentido[1] += 0x100;
}

void funcion_80085768(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) { /* irregular */
        case 1:
            inicializar_globo_aerostatico(indice_objeto);
            break;
        case 0:
        case 2:
            break;
    }
}

void actualizar_globo_aerostatico(void) {
    s32 indice_objeto;

    indice_objeto = lista_objeto_indice_1[0];
    if (lista_objeto[indice_objeto].state != 0) {
        funcion_80085768(indice_objeto);
        funcion_80085534(indice_objeto);
        calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
        if (lista_objeto[indice_objeto].state >= 2) {
            actor_globo_aerostatico_caja_item->pos[0] = lista_objeto[indice_objeto].pos[0];
            actor_globo_aerostatico_caja_item->pos[1] = lista_objeto[indice_objeto].pos[1] - 10.0;
            actor_globo_aerostatico_caja_item->pos[2] = lista_objeto[indice_objeto].pos[2];
        }
    }
}

void funcion_80085878(s32 indice_objeto, s32 parametro1) {
    PuntoCaminoPista* temporal_v0;
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->desconocido_0D8 = 1;
    objeto->model = (Gfx*) d_rainbow_road_desconocido4;
    objeto->vertice = (Vtx*) d_rainbow_road_desconocido3;
    objeto->escalado_tamanio = 0.03f;
    objeto->tamanio_caja_envolvente = 0x000A;
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x04000200);
    objeto->desconocido_084[8] = (parametro1 * 0x12C) + 0x1F4;
    fijar_pos_origen_obj(indice_objeto, 0.0f, -15.0f, 0.0f);
    temporal_v0 = &camino_pista_actual[(u16) objeto->desconocido_084[8]];
    fijar_desplazamiento_origen_obj(indice_objeto, temporal_v0->pos_x, temporal_v0->pos_y, temporal_v0->pos_z);
    fijar_angulo_sentido_obj(indice_objeto, 0U, 0U, 0U);
    objeto->desconocido_034 = 4.0f;
    objeto->type = obtener_longitud_animacion(d_rainbow_road_desconocido3, 0);
    estado_siguiente_objeto(indice_objeto);
}

void funcion_800859C8(s32 indice_objeto, s32 parametro1) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    switch (objeto->state) { /* irregular */
        case 0:
            break;
        case 1:
            funcion_80085878(indice_objeto, parametro1);
            break;
        case 2:
            funcion_80072E54(indice_objeto, 0, (s32) objeto->type, 1, 0, -1);
            break;
    }
    if (dato_8018D40C == 0) {
        funcion_800C98B8(objeto->pos, objeto->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x57));
    }
    funcion_80074344(indice_objeto, &objeto->altura_superficie, -0.8f, 0.8f, 0.03f, 0, -1);
}

void actualizar_chomps_cadena(void) {
    s32 indice_objeto;
    s32 variable_s4;
    Objeto* objeto;

    for (variable_s4 = 0; variable_s4 < CHOMPS_CADENA_NUM; variable_s4++) {
        indice_objeto = lista_objeto_indice_2[variable_s4];
        objeto = &lista_objeto[indice_objeto];
        if (objeto->state != 0) {
            funcion_800859C8(indice_objeto, variable_s4);
            copiar_vec3f(objeto->desconocido_01C, objeto->offset);
            funcion_8000D940(objeto->offset, &objeto->desconocido_084[8], objeto->desconocido_034, objeto->altura_superficie, 0);
            objeto->angulo_sentido[1] = obtener_angulo_xz_entre_puntos(objeto->desconocido_01C, objeto->offset);
            calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
            funcion_80089CBC(indice_objeto, 30.0f);
        }
    }
}

void funcion_80085BB4(s32 indice_objeto) {
    lista_objeto[indice_objeto].escalado_tamanio = 8.0f;
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    fijar_orientacion_obj(indice_objeto, 0U, 0U, 0x8000U);
    estado_siguiente_objeto(indice_objeto);
}

void inicializar_hongo_neon_obj(s32 indice_objeto) {
    fijar_pos_origen_obj(indice_objeto, orientacion_x * -1431.0, 827.0f, -2957.0f);
    inicializar_objeto_textura(indice_objeto, (u8*) d_circuito_rainbow_road_neon_hongo_tlut_lista,
                        d_circuito_rainbow_road_hongo_neon, 0x40U, (u16) 0x00000040);
    funcion_80085BB4(indice_objeto);
}

void funcion_80085CA0(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) {
        case 1:
            inicializar_hongo_neon_obj(indice_objeto);
            break;
        case 2:
            funcion_80072E54(indice_objeto, 0, 4, 1, 0x0000000C, 5);
            break;
        case 3:
            funcion_80072D3C(indice_objeto, 3, 4, 4, 0x0000000A);
            break;
        case 4:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x00000014);
            break;
        case 5:
            funcion_80072E54(indice_objeto, 0, 4, 1, 0x0000000C, 5);
            break;
        case 6:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x00000014);
            break;
        case 7:
            funcion_80072D3C(indice_objeto, 3, 4, 0, 0x00000014);
            break;
        case 8:
            funcion_800726CC(indice_objeto, 2);
            break;
        case 0:
        default:
            break;
    }
}

void funcion_80085DB8(s32 indice_objeto) {
    fijar_pos_origen_obj(indice_objeto, orientacion_x * 799.0, 1193.0f, -5891.0f);
    inicializar_objeto_textura(indice_objeto, (u8*) d_circuito_rainbow_road_neon_mario_lista_tlut, d_circuito_rainbow_road_neon_mario,
                        0x40U, (u16) 0x00000040);
    funcion_80085BB4(indice_objeto);
}

void funcion_80085E38(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) {
        case 1:
            funcion_80085DB8(indice_objeto);
            break;
        case 2:
            funcion_80072E54(indice_objeto, 0, 4, 1, 0x0000000C, 1);
            break;
        case 3:
            funcion_80072D3C(indice_objeto, 3, 4, 0x0000000C, 1);
            break;
        case 4:
            funcion_80072B48(indice_objeto, 0x0000000C);
            break;
        case 5:
            funcion_800726CC(indice_objeto, 2);
            break;
        case 0:
        default:
            break;
    }
}

void funcion_80085EF8(s32 indice_objeto) {
    fijar_pos_origen_obj(indice_objeto, orientacion_x * -2013.0, 555.0f, 0.0f);
    inicializar_objeto_textura(indice_objeto, (u8*) d_circuito_rainbow_road_neon_boo_lista_tlut, d_circuito_rainbow_road_neon_boo,
                        0x40U, (u16) 0x00000040);
    funcion_80085BB4(indice_objeto);
}

void funcion_80085F74(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) {
        case 1:
            funcion_80085EF8(indice_objeto);
            break;
        case 2:
            funcion_80072E54(indice_objeto, 0, 4, 1, 5, 1);
            break;
        case 3:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x0000001E);
            break;
        case 4:
            funcion_80072C00(indice_objeto, 4, 0, 7);
            break;
        case 5:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x0000001E);
            break;
        case 6:
            funcion_80072F88(indice_objeto, 3, 0, 1, 5, 1);
            break;
        case 7:
            funcion_80072B48(indice_objeto, 0x0000000F);
            break;
        case 8:
            funcion_800726CC(indice_objeto, 2);
            break;
        case 0:
        default:
            break;
    }
}

void funcion_80086074(s32 indice_objeto, s32 parametro1) {
    fijar_pos_origen_obj(indice_objeto, dato_800E6734[parametro1 * 3 + 0] * orientacion_x, dato_800E6734[parametro1 * 3 + 1], dato_800E6734[parametro1 * 3 + 2]);
    inicializar_objeto_textura(indice_objeto, (u8*) &d_circuito_rainbow_road_tluts_estatico[parametro1 * 256],
                        (u8*) &d_circuito_rainbow_road_texturas_estatico[parametro1], 64, 64);
    funcion_80085BB4(indice_objeto);
}

void funcion_80086110(s32 indice_objeto, s32 parametro1) {
    switch (lista_objeto[indice_objeto].state) {
        case 1:
            funcion_80086074(indice_objeto, parametro1);
            break;
        case 0:
            break;
    }
}

void actualizar_neon_objeto(s32 indice_objeto, s32 id) {
    switch (id) { /* irregular */
        case 0:
            funcion_80085CA0(indice_objeto);
            break;
        case 1:
            funcion_80085E38(indice_objeto);
            break;
        case 2:
            funcion_80085F74(indice_objeto);
            break;
    }
    if (id >= 3) {
        funcion_80086110(indice_objeto, id - 3);
    }
}

void actualizar_neon(void) {
    s32 indice_objeto;
    s32 id;

    for (id = 0; id < CARTELES_NEON_NUM; id++) {
        indice_objeto = lista_objeto_indice_1[id];
        if (lista_objeto[indice_objeto].state != 0) {
            actualizar_neon_objeto(indice_objeto, id);
            if (lista_objeto[indice_objeto].state >= 2) {
                actualizar_textura_neon(indice_objeto);
                calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
            }
        }
    }
}

void funcion_8008629C(s32 indice_objeto, s32 parametro1) {
    switch (parametro1) { /* irregular */
        case 0:
            lista_objeto[indice_objeto].model = podio_dl3;
            lista_objeto[indice_objeto].desconocido_04C = 0x00000038;
            break;
        case 1:
            lista_objeto[indice_objeto].model = podio2_dl3;
            lista_objeto[indice_objeto].desconocido_04C = 0x0000002B;
            break;
        case 2:
            lista_objeto[indice_objeto].model = podio3_dl3;
            lista_objeto[indice_objeto].desconocido_04C = 0x0000001E;
            break;
        default:
            break;
    }
    lista_objeto[indice_objeto].escalado_tamanio = 1.0f;
    fijar_pos_origen_obj(indice_objeto, dato_800E634C[0][0] - 1.5, dato_800E634C[0][1], dato_800E634C[0][2]);
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, -10.0f, 0.0f);
    fijar_angulo_sentido_obj(indice_objeto, 0U, 0xF8E4U, 0U);
    lista_objeto[indice_objeto].desconocido_048 = 0;
    estado_siguiente_objeto(indice_objeto);
}

void funcion_80086424(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 0:
            break;
        case 1:
            lista_objeto[indice_objeto].velocidad[1] = 0.75f;
            funcion_80086FD4(indice_objeto);
            break;
        case 2:
            if (lista_objeto[indice_objeto].offset[1] >= -2.0) {
                lista_objeto[indice_objeto].velocidad[1] -= 0.1;
            }
            agregar_desplazamiento_y_velocidad_objeto(indice_objeto);
            if (lista_objeto[indice_objeto].offset[1] >= 0.0) {
                lista_objeto[indice_objeto].offset[1] = 0.0f;
                lista_objeto[indice_objeto].velocidad[1] = 0.0f;
                funcion_80086F60(indice_objeto);
            }
            break;
    }
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void funcion_80086528(s32 indice_objeto, s32 parametro1) {
    switch (lista_objeto[indice_objeto].state) { /* irregular */
        case 1:
            funcion_8008629C(indice_objeto, parametro1);
            break;
        case 2:
            if (ejecutar_objeto_temporizador_conjunto_y(indice_objeto, lista_objeto[indice_objeto].desconocido_04C) != 0) {
                funcion_80091440(parametro1);
                funcion_80086E70(indice_objeto);
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 0:
            break;
        case 3:
            if (lista_objeto[indice_objeto].desconocido_0AE == 0) {
                lista_objeto[indice_objeto].desconocido_048 = 1;
                estado_siguiente_objeto(indice_objeto);
            }
            break;
    }
}

void funcion_80086604(void) {
    s32 indice_objeto;
    s32 variable_s1;

    if ((dato_8016347C != 0) && (dato_802874D8.desconocido_1d < 3)) {
        if (dato_801658C6 == 0) {
            for (variable_s1 = 0; variable_s1 < 3; variable_s1++) {
                indice_objeto = lista_objeto_indice_1[variable_s1];
                inicializar_objeto(indice_objeto, 0);
            }
            dato_801658C6 = 1;
        }
    }
    for (variable_s1 = 0; variable_s1 != 3; variable_s1++) {
        indice_objeto = lista_objeto_indice_1[variable_s1];
        if (lista_objeto[indice_objeto].state != 0) {
            funcion_80086528(indice_objeto, variable_s1);
            funcion_80086424(indice_objeto);
        }
    }
}

void funcion_80086700(s32 indice_objeto) {
    if (seleccion_cc < CC_150) {
        switch (dato_802874D8.desconocido_1d) {
            case 0:
                lista_objeto[indice_objeto].model = trofeo_oro_dl10;
                break;
            case 1:
                lista_objeto[indice_objeto].model = trofeo_oro_dl12;
                break;
            case 2:
                lista_objeto[indice_objeto].model = trofeo_oro_dl14;
                break;
            default:
                break;
        }
    } else {
        switch (dato_802874D8.desconocido_1d) { /* irregular */
            case 0:
                lista_objeto[indice_objeto].model = trofeo_oro_dl11;
                break;
            case 1:
                lista_objeto[indice_objeto].model = trofeo_oro_dl13;
                break;
            case 2:
                lista_objeto[indice_objeto].model = trofeo_oro_dl15;
                break;
            default:
                break;
        }
    }
    lista_objeto[indice_objeto].escalado_tamanio = 0.005f;
    fijar_pos_origen_obj(indice_objeto, lista_objeto[lista_objeto_indice_2[0]].pos[0],
                       lista_objeto[lista_objeto_indice_2[0]].pos[1] + 16.0, lista_objeto[lista_objeto_indice_2[0]].pos[2]);
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    fijar_angulo_sentido_obj(indice_objeto, 0U, 0U, 0U);
    lista_objeto[indice_objeto].desconocido_084[1] = 0x0200;
    estado_siguiente_objeto(indice_objeto);
    funcion_80086E70(indice_objeto);
}

void funcion_80086940(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    switch (objeto->desconocido_0AE) {
        case 0:
            break;
        case 1:
            funcion_80086FD4(indice_objeto);
            break;
        case 2:
            paso_f32_hacia(&objeto->escalado_tamanio, 0.025f, 0.001f);
            funcion_80087C48(indice_objeto, 6.0f, 0.1f, 0x000000C8);
            if ((f64) objeto->velocidad[1] <= 0.0) {
                funcion_8008701C(indice_objeto, 3);
            }
            break;
        case 3:
            funcion_800871AC(indice_objeto, 0x00000064);
            break;
        case 4:
            dato_801658D6 = 1;
            objeto->velocidad[1] = -0.4f;
            funcion_80086FD4(indice_objeto);
            objeto->pos_origen[1] = 90.0f;
            objeto->offset[1] = 60.0f;
            switch (dato_802874D8.desconocido_1d) {
                case 1:
                    objeto->pos_origen[0] -= 3.0;
                    objeto->pos_origen[2] += 15.0;
                    break;
                case 2:
                    objeto->pos_origen[0] -= 2.0;
                    objeto->pos_origen[2] -= 15.0;
                    break;
            }
            break;
        case 5:
            if ((f64) objeto->offset[1] <= 8.0) {
                paso_f32_hacia(&objeto->velocidad[1], -0.1f, -0.01f);
            }
            agregar_desplazamiento_y_velocidad_objeto(indice_objeto);
            if ((f64) objeto->offset[1] <= 0.0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 6:
            if (funcion_800871AC(indice_objeto, 0x00000041) != 0) {
                dato_801658F4 = 1;
            }
            break;
        case 7:
            if (funcion_800871AC(indice_objeto, 0x00000064) != 0) {
                funcion_8009265C();
                funcion_80086F60(indice_objeto);
            }
            break;
    }
    if (dato_801658D6 != 0) {
        objeto->angulo_sentido[0] += 0x400;
        objeto->angulo_sentido[1] = 0xE800;
        objeto->angulo_sentido[2] = 0xDA00;
    } else {
        objeto->angulo_sentido[0] += 0x400;
        objeto->angulo_sentido[1] -= 0x200;
    }
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void funcion_80086C14(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) { /* irregular */
        case 1:
            funcion_80086700(indice_objeto);
            break;
        case 0:
        case 2:
            break;
    }
}

void funcion_80086C6C(s32 indice_objeto) {
    Vec3f sp24;

    sp24[0] = (lista_objeto[indice_objeto].pos[0] - 5.0f) + int_aleatorio(0x000AU);
    sp24[2] = (lista_objeto[indice_objeto].pos[2] - 5.0f) + int_aleatorio(0x000AU);
    if (dato_801658F4 != 0) {
        sp24[1] = lista_objeto[indice_objeto].pos[1] + 14.0;
    } else {
        sp24[1] = lista_objeto[indice_objeto].pos[1] - 2.0;
    }
    funcion_800773D8(sp24, (s32) dato_801658F4);
}

void funcion_80086D80(void) {
    s32 temporal_s2;
    s32 variable_s0;

    if ((dato_801658CE != 0) && (dato_801658DC == 0)) {
        temporal_s2 = lista_objeto_indice_1[3];
        inicializar_objeto(temporal_s2, 0);
        dato_801658DC = 1;
    }
    temporal_s2 = lista_objeto_indice_1[3];
    if (lista_objeto[temporal_s2].state != 0) {
        funcion_80086C14(temporal_s2);
        funcion_80086940(temporal_s2);
        if (dato_801658F4 != 0) {
            if (dato_8016559C == 0) {
                funcion_80086C6C(temporal_s2);
            }
        } else {
            for (variable_s0 = 0; variable_s0 < 2; variable_s0++) {
                funcion_80086C6C(temporal_s2);
            }
        }
    }
}
