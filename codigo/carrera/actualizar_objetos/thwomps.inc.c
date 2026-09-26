// Thwomps

void funcion_8007F280(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 1:
            if (funcion_80073E18(indice_objeto, (u16*) &lista_objeto[indice_objeto].orientacion[1], 0x0400U, 0x00010000) != 0) {
                lista_objeto[indice_objeto].desconocido_01C[0] = (f32) ((f64) orientacion_x * -200.0);
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 2:
            if (paso_f32_hacia(lista_objeto[indice_objeto].offset, lista_objeto[indice_objeto].desconocido_01C[0], 4.0f) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 3:
            if (funcion_80073E18(indice_objeto, (u16*) &lista_objeto[indice_objeto].orientacion[1], 0x0400U, 0x00010000) != 0) {
                funcion_800726CC(indice_objeto, 3);
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 5:
            if (funcion_80073E18(indice_objeto, (u16*) &lista_objeto[indice_objeto].orientacion[1], 0x0400U, 0x00004000) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 6:
            if (arriba_paso_f32_hacia(&lista_objeto[indice_objeto].offset[2], 100.0f, 2.0f) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 7:
            if (funcion_80073E18(indice_objeto, (u16*) &lista_objeto[indice_objeto].orientacion[1], 0x0400U, 0x0000C000) != 0) {
                funcion_80086FD4(indice_objeto);
                funcion_800726CC(indice_objeto, 3);
            }
            break;
        case 9:
            if (funcion_80073E18(indice_objeto, (u16*) &lista_objeto[indice_objeto].orientacion[1], 0x0400U, 0x00008000) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 10:
            if (paso_f32_hacia(lista_objeto[indice_objeto].offset, 0.0f, 4.0f) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 11:
            if (funcion_80073E18(indice_objeto, (u16*) &lista_objeto[indice_objeto].orientacion[1], 0x0400U, 0x00008000) != 0) {
                funcion_80086FD4(indice_objeto);
                funcion_800726CC(indice_objeto, 3);
            }
            break;
        case 13:
            if (funcion_80073E18(indice_objeto, (u16*) &lista_objeto[indice_objeto].orientacion[1], 0x0400U, 0x0000C000) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 14:
            if (abajo_paso_f32_hacia(&lista_objeto[indice_objeto].offset[2], 0.0f, 2.0f) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 15:
            if (funcion_80073E18(indice_objeto, (u16*) &lista_objeto[indice_objeto].orientacion[1], 0x0400U, 0x00014000) != 0) {
                funcion_80086FD4(indice_objeto);
                funcion_800726CC(indice_objeto, 3);
            }
            break;
        case 17:
            funcion_8008701C(indice_objeto, 1);
            break;
        case 0:
        default:
            break;
    }
}

void funcion_8007F544(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0DD) { /* irregular */
        case 1:
            funcion_8007EFBC(indice_objeto);
            break;
        case 2:
            funcion_8007F280(indice_objeto);
            break;
    }
}

void funcion_8007F5A8(s32 indice_objeto) {

    switch (lista_objeto[indice_objeto].state) { /* irregular */
        case 0:
            break;
        case 1:
            funcion_8007EE5C(indice_objeto);
            break;
        case 3:
            funcion_80072568(indice_objeto, 0x00000032);
            break;
        case 4:
            funcion_80086FD4(indice_objeto);
            estado_siguiente_objeto(indice_objeto);
            break;
    }
    funcion_8007E63C(indice_objeto);
    funcion_8007F544(indice_objeto);
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
    funcion_80073514(indice_objeto);
}

void funcion_8007F660(s32 indice_objeto, s32 parametro1, s32 parametro2) {
    Objeto* objeto;

    funcion_800722A4(indice_objeto, 8);
    funcion_80086E70(indice_objeto);
    objeto = &lista_objeto[indice_objeto];
    objeto->desconocido_0DD = 1;
    objeto->desconocido_0D1 = parametro1;
    objeto->desconocido_048 = parametro2;
}

void funcion_8007F6C4(s32 indice_objeto, s32 id_jugador) {
    Jugador* jugador;

    jugador = &jugador_uno[id_jugador];
    funcion_800722A4(indice_objeto, 8);
    funcion_80086E70(indice_objeto);
    lista_objeto[indice_objeto].desconocido_0DD = 2;
    lista_objeto[indice_objeto].desconocido_01C[0] = jugador->pos[0] - lista_objeto[indice_objeto].pos_origen[0];
    lista_objeto[indice_objeto].desconocido_0D1 = id_jugador;
}

s32 funcion_8007F75C(s32 id_jugador) {
    s32 algun_indice;
    s32 indice_objeto;
    s32 temporal_s7;
    s32 variable_s6;
    s32 punto_camino;

    punto_camino = punto_camino_mas_cercano_por_id_jugador[id_jugador];
    variable_s6 = 0;
    if ((punto_camino >= 0xAA) && (punto_camino < 0xB5)) {
        temporal_s7 = int_aleatorio(0x0032U) + 0x32;
        for (algun_indice = 0; algun_indice < thwomps_activo_num; algun_indice++) {
            indice_objeto = lista_objeto_indice_1[algun_indice];
            if (lista_objeto[indice_objeto].desconocido_0D5 == 3) {
                variable_s6 = 1;
                funcion_8007F660(indice_objeto, id_jugador, temporal_s7);
            }
        }
    } else if ((punto_camino >= 0xD7) && (punto_camino < 0xE2)) {
        for (algun_indice = 0; algun_indice < thwomps_activo_num; algun_indice++) {
            indice_objeto = lista_objeto_indice_1[algun_indice];
            if (lista_objeto[indice_objeto].desconocido_0D5 == 3) {
                variable_s6 = 1;
                funcion_8007F6C4(indice_objeto, id_jugador);
            }
        }
    }
    return variable_s6;
}

void funcion_8007F8D8(void) {
    Jugador* jugador;
    s32 indice_objeto;
    s32 variable_s0;
    s32 algun_indice;
    s32 variable_s4;
    Objeto* objeto;

    jugador = jugador_uno;
    variable_s4 = 1;
    for (algun_indice = 0; algun_indice < thwomps_activo_num; algun_indice++) {
        indice_objeto = lista_objeto_indice_1[algun_indice];
        objeto = &lista_objeto[indice_objeto];
        if (objeto->desconocido_0D5 == 3) {
            variable_s0 = 0;
            if ((objeto->state >= 2) && (funcion_80072354(indice_objeto, 8) != 0)) {
                variable_s0 = 1;
            }
            variable_s4 *= variable_s0;
        }
    }
    if (variable_s4 != 0) {
        for (variable_s0 = 0; variable_s0 < 4; variable_s0++, jugador++) {
            if ((jugador->type & EXISTE_JUGADOR) && !(jugador->type & CPU_JUGADOR)) {
                if (funcion_8007F75C(variable_s0) != 0) {
                    break;
                }
            }
        }
    }
}

void funcion_8007FA08(s32 indice_objeto) {
    Objeto* objeto;

    inicializar_objeto_textura(indice_objeto, d_circuito_bowsers_castle_thwomp_tlut, (u8*) d_circuito_bowsers_castle_thwomp_caras,
                        0x10U, (u16) 0x00000040);
    objeto = &lista_objeto[indice_objeto];
    objeto->model = d_circuito_bowsers_castle_dl_thwomp;
    objeto->tamanio_caja_envolvente = 0x000C;
    objeto->escalado_tamanio = 1.0f;
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x04000220);
    objeto->type = 0;
    objeto->altura_superficie = 0.0f;
    objeto->pos_origen[1] = 0.0f;
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    fijar_angulo_sentido_obj(indice_objeto, 0U, 0U, 0U);
    if (es_modo_espejo != 0) {
        fijar_orientacion_obj(indice_objeto, 0U, 0xC000U, 0U);
    } else {
        fijar_orientacion_obj(indice_objeto, 0U, 0x4000U, 0U);
    }
    objeto->velocidad[0] = 0.0f;
    objeto->angulo_sentido[1] = objeto->orientacion[1];
    objeto->desconocido_0DD = 1;
    objeto->desconocido_0DF = 8;
    objeto->offset[1] = 15.0f;
    objeto->desconocido_01C[1] = 15.0f;
    estado_siguiente_objeto(indice_objeto);
}

void funcion_8007FB48(s32 indice_objeto) {
    s32 variable_v0;
    SIN_USO s32 margen_pila;
    Jugador* jugador;

    jugador = &jugador_uno[lista_objeto[indice_objeto].desconocido_0D1];
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 1:
            lista_objeto[indice_objeto].desconocido_0B0 = 0x00A0;
            lista_objeto[indice_objeto].offset[0] = 0.0f;
            lista_objeto[indice_objeto].offset[2] = 0.0f;
            lista_objeto[indice_objeto].velocidad[2] = 0.0f;
            funcion_80086FD4(indice_objeto);
            break;
        case 2:
            lista_objeto[indice_objeto].velocidad[0] = jugador->speed * orientacion_x * 1.25;
            if (lista_objeto[indice_objeto].desconocido_048 >= lista_objeto[indice_objeto].desconocido_0B0) {
                if (lista_objeto[indice_objeto].desconocido_0B0 == lista_objeto[indice_objeto].desconocido_048) {
                    if (dato_8018D400 & 1) {
                        lista_objeto[indice_objeto].velocidad[2] = 1.5f;
                    } else {
                        lista_objeto[indice_objeto].velocidad[2] = -1.5f;
                    }
                }
                if (lista_objeto[indice_objeto].velocidad[2] >= 0.0) {
                    if (lista_objeto[indice_objeto].offset[2] >= 40.0) {
                        lista_objeto[indice_objeto].velocidad[2] = -1.5f;
                    }
                } else if ((f64) lista_objeto[indice_objeto].offset[2] <= -40.0) {
                    lista_objeto[indice_objeto].velocidad[2] = 1.5f;
                }
            }
            agregar_desplazamiento_xz_velocidad_objeto(indice_objeto);
            if (lista_objeto[indice_objeto].desconocido_0B0 < 0x65) {
                lista_objeto[indice_objeto].orientacion[1] = funcion_800417B4(
                    lista_objeto[indice_objeto].orientacion[1], (lista_objeto[indice_objeto].angulo_sentido[1] + 0x8000));
                if (lista_objeto[indice_objeto].desconocido_0B0 == 0x0064) {
                    lista_objeto[indice_objeto].textura_indice_lista = 1;
                }
            }
            variable_v0 = 0;
            if (es_modo_espejo != 0) {
                if (lista_objeto[indice_objeto].offset[0] <= -1000.0) {
                    variable_v0 = 1;
                }
            } else if (lista_objeto[indice_objeto].offset[0] >= 1000.0) {
                variable_v0 = 1;
            }
            lista_objeto[indice_objeto].desconocido_0B0--;
            if ((lista_objeto[indice_objeto].desconocido_0B0 == 0) || (variable_v0 != 0)) {
                lista_objeto[indice_objeto].desconocido_034 = 0.0f;
                funcion_800726CC(indice_objeto, 3);
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 4:
            paso_f32_hacia(&lista_objeto[indice_objeto].offset[2], 0.0f, 2.0f);
            paso_f32_hacia(lista_objeto[indice_objeto].offset, 0.0f, 5.0f);
            if ((lista_objeto[indice_objeto].offset[0] + lista_objeto[indice_objeto].offset[2]) == 0.0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 5:
            lista_objeto[indice_objeto].orientacion[1] =
                funcion_800417B4(lista_objeto[indice_objeto].orientacion[1], lista_objeto[indice_objeto].angulo_sentido[1]);
            if (lista_objeto[indice_objeto].orientacion[1] == lista_objeto[indice_objeto].angulo_sentido[1]) {
                funcion_800722CC(indice_objeto, 8);
                funcion_80086FD4(indice_objeto);
                lista_objeto[indice_objeto].textura_indice_lista = 0;
            }
            break;
        case 0:
        case 3:
        default:
            break;
    }
}

void funcion_8007FEA4(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    switch (objeto->desconocido_0AE) {
        case 1:
            if (paso_f32_hacia(&objeto->offset[0], objeto->desconocido_01C[0], 5.0f) != 0) {
                funcion_800726CC(indice_objeto, 3);
                funcion_80086FD4(indice_objeto);
                break;
            }
        case 0:
        case 2:
            break;
        case 3:
            if (paso_f32_hacia(&objeto->offset[0], 0.0f, 5.0f) != 0) {
                funcion_80086FD4(indice_objeto);
                funcion_800722CC(indice_objeto, 8);
            }
            break;
    }
}

void funcion_8007FF5C(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0DD) {
        case 1:
            funcion_8007FB48(indice_objeto);
            break;
        case 2:
            funcion_8007FEA4(indice_objeto);
            break;
    }
}

void funcion_8007FFC0(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) { /* irregular */
        case 0:
            break;
        case 1:
            funcion_8007FA08(indice_objeto);
            break;
        case 3:
            funcion_80072568(indice_objeto, 0x00000032);
            break;
        case 4:
            estado_siguiente_objeto(indice_objeto);
            funcion_80086FD4(indice_objeto);
            break;
    }
    funcion_8007E63C(indice_objeto);
    funcion_8007FF5C(indice_objeto);
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
    funcion_80073514(indice_objeto);
}

void funcion_80080078(s32 indice_objeto) {
    Objeto* objeto;

    inicializar_objeto_textura(indice_objeto, d_circuito_bowsers_castle_thwomp_tlut, (u8*) d_circuito_bowsers_castle_thwomp_caras,
                        0x10U, (u16) 0x00000040);
    objeto = &lista_objeto[indice_objeto];
    objeto->model = d_circuito_bowsers_castle_dl_thwomp;
    objeto->tamanio_caja_envolvente = 0x000C;
    objeto->escalado_tamanio = 1.0f;
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x04000220);
    objeto->type = 2;
    objeto->desconocido_0DF = 8;
    fijar_angulo_sentido_obj(indice_objeto, 0U, 0U, 0U);
    objeto->altura_superficie = 0.0f;
    objeto->pos_origen[1] = 0.0f;
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    objeto->desconocido_01C[1] = 30.0f;
    if (es_modo_espejo != 0) {
        fijar_orientacion_obj(indice_objeto, 0U, 0x4000U, 0U);
    } else {
        fijar_orientacion_obj(indice_objeto, 0U, 0xC000U, 0U);
    }
    switch (objeto->prim_alpha) { /* irregular */
        case 0:
            objeto->temporizador = 2;
            break;
        case 1:
            objeto->temporizador = 0x0000003C;
            break;
        case 2:
            objeto->temporizador = 0x00000078;
            break;
        case 3:
            objeto->temporizador = 0x000000B4;
            break;
    }
    funcion_800724DC(indice_objeto);
    estado_siguiente_objeto(indice_objeto);
}

void funcion_800801FC(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    switch (objeto->state) {
        case 0:
            break;
        case 1:
            funcion_80080078(indice_objeto);
            break;
        case 2:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, objeto->temporizador);
            break;
        case 3:
            funcion_80072568(indice_objeto, 0x00000032);
            break;
        case 4:
            objeto->temporizador = 0x0000003C;
            funcion_800726CC(indice_objeto, 2);
            break;
    }
    funcion_8007E63C(indice_objeto);
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
    funcion_80073514(indice_objeto);
}

void funcion_800802C0(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->desconocido_0D8 = 0;
    inicializar_objeto_textura(indice_objeto, d_circuito_bowsers_castle_thwomp_tlut, (u8*) d_circuito_bowsers_castle_thwomp_caras,
                        0x10U, (u16) 0x00000040);
    objeto->model = d_circuito_bowsers_castle_dl_thwomp;
    objeto->textura_indice_lista = 0;
    objeto->tamanio_caja_envolvente = 0x000C;
    objeto->escalado_tamanio = 1.5f;
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x05000220);
    objeto->type = 1;
    objeto->desconocido_0DF = 6;
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    fijar_angulo_sentido_obj(indice_objeto, 0U, 0U, 0U);
    objeto->altura_superficie = 0.0f;
    objeto->pos_origen[1] = 0.0f;
    objeto->offset[1] = 10.0f;
    objeto->desconocido_01C[1] = 10.0f;
    if (es_modo_espejo != 0) {
        fijar_orientacion_obj(indice_objeto, 0U, 0x4000U, 0U);
    } else {
        fijar_orientacion_obj(indice_objeto, 0U, 0xC000U, 0U);
    }
    objeto->offset[0] = 0.0f;
    objeto->offset[2] = 0.0f;
    funcion_800724DC(indice_objeto);
    estado_siguiente_objeto(indice_objeto);
}

void funcion_80080408(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) {
        case 0:
            break;
        case 1:
            funcion_800802C0(indice_objeto);
            break;
        case 2:
            funcion_8008A6DC(indice_objeto, 100.0f);
            if (es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) {
                funcion_800C98B8(lista_objeto[indice_objeto].pos, lista_objeto[indice_objeto].velocidad,
                              SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x45));
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 3:
            if (funcion_800730BC(indice_objeto, 3, 5, 1, 6, 6) != 0) {
                lista_objeto[indice_objeto].textura_indice_lista = 0;
            }
            break;
        case 4:
            if (ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x0000012C) != 0) {
                funcion_800726CC(indice_objeto, 2);
            }
            break;
    }
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
    funcion_80073514(indice_objeto);
}

void funcion_80080524(s32 indice_objeto) {
    Objeto* objeto;

    inicializar_objeto_textura(indice_objeto, d_circuito_bowsers_castle_thwomp_tlut, (u8*) d_circuito_bowsers_castle_thwomp_caras,
                        0x10U, (u16) 0x00000040);
    objeto = &lista_objeto[indice_objeto];
    objeto->model = d_circuito_bowsers_castle_dl_thwomp;
    objeto->tamanio_caja_envolvente = 0x000C;
    objeto->textura_indice_lista = 0;
    objeto->escalado_tamanio = 1.0f;
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x04000220);
    objeto->type = 0;
    objeto->desconocido_0DF = 0x0A;
    funcion_80086E70(indice_objeto);
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    objeto->altura_superficie = 70.0f;
    objeto->pos_origen[1] = 70.0f;
    objeto->desconocido_01C[1] = 0.0f;
    fijar_angulo_sentido_obj(indice_objeto, 0U, 0U, 0U);
    if ((es_modo_espejo != 0) || (estado_juego == 9)) {
        fijar_orientacion_obj(indice_objeto, 0U, 0xC000U, 0U);
    } else {
        fijar_orientacion_obj(indice_objeto, 0U, 0x4000U, 0U);
    }
    switch (objeto->prim_alpha) { /* irregular */
        case 0:
            objeto->desconocido_0DD = 2;
            objeto->velocidad[2] = -1.0f;
            break;
        case 1:
            objeto->desconocido_0DD = 2;
            objeto->velocidad[2] = -1.5f;
            break;
    }
    funcion_800722A4(indice_objeto, 0x00000080);
    estado_siguiente_objeto(indice_objeto);
}

void funcion_800806BC(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 0:
            break;
        case 1:
            if (paso_f32_hacia(&lista_objeto[indice_objeto].offset[2], 250.0f, lista_objeto[indice_objeto].velocidad[2]) !=
                0) {
                lista_objeto[indice_objeto].velocidad[2] = -lista_objeto[indice_objeto].velocidad[2];
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 2:
            if (paso_f32_hacia(&lista_objeto[indice_objeto].offset[2], 0.0f, lista_objeto[indice_objeto].velocidad[2]) !=
                0) {
                lista_objeto[indice_objeto].velocidad[2] = -lista_objeto[indice_objeto].velocidad[2];
                funcion_8008701C(indice_objeto, 1);
            }
            break;
    }
}

void funcion_8008078C(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 0:
            break;
        case 1:
            if (paso_f32_hacia(&lista_objeto[indice_objeto].offset[2], -250.0f, lista_objeto[indice_objeto].velocidad[2]) !=
                0) {
                lista_objeto[indice_objeto].velocidad[2] = -lista_objeto[indice_objeto].velocidad[2];
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 2:
            if (paso_f32_hacia(&lista_objeto[indice_objeto].offset[2], 0.0f, lista_objeto[indice_objeto].velocidad[2]) !=
                0) {
                lista_objeto[indice_objeto].velocidad[2] = -lista_objeto[indice_objeto].velocidad[2];
                funcion_8008701C(indice_objeto, 1);
            }
            break;
    }
}

void funcion_8008085C(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0DD) {
        case 1:
            funcion_800806BC(indice_objeto);
            break;
        case 2:
            funcion_8008078C(indice_objeto);
            break;
    }
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void funcion_800808CC(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) { /* irregular */
        case 0:
            break;
        case 1:
            funcion_80080524(indice_objeto);
            break;
        case 2:
            funcion_800730BC(indice_objeto, 3, 5, 1, 6, -1);
            break;
    }
    if (lista_objeto[indice_objeto].state >= 2) {
        funcion_8007E63C(indice_objeto);
        funcion_8008085C(indice_objeto);
        funcion_80073514(indice_objeto);
        if (estado_juego != 9) {
            if ((dato_8018D40C == 0) && (lista_objeto[indice_objeto].state == 2)) {
                funcion_800C98B8(lista_objeto[indice_objeto].pos, lista_objeto[indice_objeto].velocidad,
                              SONIDO_CARGA_PARAMETRO(0x19, 0x03, 0x60, 0x45));
            }
        } else if ((temporizador_disparo_cinematica < 0xBF) && (((s16) temporizador_disparo_cinematica % 88) == 0x0000001E)) {
            funcion_800C98B8(lista_objeto[indice_objeto].pos, lista_objeto[indice_objeto].velocidad,
                          SONIDO_CARGA_PARAMETRO(0x19, 0x03, 0x60, 0x45));
        }
    }
}

void funcion_80080A14(s32 indice_objeto, Jugador* jugador) {
    if (es_dentro_distancia_horizontal_de_jugador(indice_objeto, jugador, 12.0f) != 0) {
        jugador->ruedas[IZQUIERDA_FRENTE].desconocido_14 |= 3;
    }
}

void funcion_80080A4C(s32 indice_objeto, s32 id_jugador_camara) {
    Camara* camara = &camara1[id_jugador_camara];
    Jugador* jugador = &jugador_uno[id_jugador_camara];

    if (seleccion_modo_pantalla != PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
        if ((funcion_80072320(indice_objeto, 0x00000010) != 0) &&
            (es_dentro_distancia_horizontal_de_jugador(indice_objeto, jugador, 500.0f) != false)) {
            funcion_8001CA10(camara);
            funcion_800C98B8(lista_objeto[indice_objeto].pos, lista_objeto[indice_objeto].velocidad,
                          SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x0F));
        }
    }
}

void funcion_80080B28(s32 indice_objeto, s32 id_jugador) {
    f32 temporal_f0;
    Jugador* temporal_s0;

    temporal_s0 = &jugador_uno[id_jugador];
    if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000200) != 0) {
        if (!(temporal_s0->disparadores & THWOMP_DISPARADOR_APLASTAMIENTO)) {
            temporal_f0 = funcion_80088F54(indice_objeto, temporal_s0);
            if ((temporal_f0 <= 9.0) && !(temporal_s0->efectos & EFECTO_APLASTAMIENTO) &&
                (tiene_horizontalmente_chocado_con_jugador(indice_objeto, temporal_s0) != 0)) {
                if ((temporal_s0->type & EXISTE_JUGADOR) && !(temporal_s0->type & INVISIBLE_JUGADOR_O_BOMBA)) {
                    if (!(temporal_s0->efectos & EFECTO_ESTRELLA)) {
                        funcion_80089474(indice_objeto, id_jugador, 1.4f, 1.1f, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0xA0, 0x4C));
                    } else if (funcion_80072354(indice_objeto, 0x00000040) != 0) {
                        if (temporal_s0->type & CPU_JUGADOR) {
                            funcion_800C98B8(temporal_s0->pos, temporal_s0->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0xA2, 0x4A));
                        } else {
                            funcion_800C9060((u8) id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0xA2, 0x4A));
                        }
                        funcion_80080DE4(indice_objeto);
                        funcion_80075304(lista_objeto[indice_objeto].pos, 3, 3, dato_8018D3C4);
                        fijar_objeto_bandera_situacion_false(indice_objeto, 0x00000200);
                        funcion_800722A4(indice_objeto, 0x00000040);
                        funcion_80086F60(indice_objeto);
                        funcion_800726CC(indice_objeto, 0x000000C8);
                    }
                }
            } else if ((temporal_f0 <= 17.5) && (funcion_80072320(indice_objeto, 1) != 0) &&
                       (es_dentro_distancia_horizontal_de_jugador(indice_objeto, temporal_s0, (temporal_s0->speed * 0.5) + 7.0) !=
                        0)) {
                if ((temporal_s0->type & EXISTE_JUGADOR) && !(temporal_s0->type & INVISIBLE_JUGADOR_O_BOMBA)) {
                    if (es_obj_bandera_situacion_activo(indice_objeto, 0x04000000) != 0) {
                        funcion_80072180();
                    }
                    funcion_800722A4(indice_objeto, 2);
                    temporal_s0->desconocido_040 = (s16) indice_objeto;
                    temporal_s0->desconocido_046 |= TOCAR_BICHO;
                    temporal_s0->disparadores |= THWOMP_DISPARADOR_APLASTAMIENTO;
                    funcion_80088FF0(temporal_s0);
                }
            }
        } else {
            funcion_80088FF0(temporal_s0);
        }
    }
}

void funcion_80080DE4(s32 parametro0) {
    Jugador* jugador;
    s32 variable_v1;

    jugador = jugador_uno;
    for (variable_v1 = 0; variable_v1 < JUGADORES_NUM; variable_v1++, jugador++) {
        if (parametro0 == jugador->desconocido_040) {
            jugador->disparadores &= ~THWOMP_DISPARADOR_APLASTAMIENTO;
            jugador->desconocido_040 = -1;
        }
    }
}

void funcion_80080E8C(s32 indice_objeto_1, s32 indice_objeto_2, s32 parametro2) {
    u16 un_angulo;
    f32 cosa1;
    f32 cosa0;

    inicializar_objeto(indice_objeto_1, parametro2);
    lista_objeto[indice_objeto_1].desconocido_0D5 = 2;
    un_angulo = lista_objeto[indice_objeto_2].angulo_sentido[1];
    cosa1 = funcion_800416D8(dato_800E594C[parametro2 * 2 + 1], dato_800E594C[parametro2 * 2 + 0], un_angulo);
    cosa0 = funcion_80041724(dato_800E594C[parametro2 * 2 + 1], dato_800E594C[parametro2 * 2 + 0], un_angulo);
    lista_objeto[indice_objeto_1].pos_origen[0] = lista_objeto[indice_objeto_2].pos[0] + cosa0;
    lista_objeto[indice_objeto_1].pos_origen[1] = lista_objeto[indice_objeto_2].altura_superficie - 9.0;
    lista_objeto[indice_objeto_1].pos_origen[2] = lista_objeto[indice_objeto_2].pos[2] + cosa1;
    un_angulo = lista_objeto[indice_objeto_2].angulo_sentido[1] + dato_800E597C[parametro2];
    lista_objeto[indice_objeto_1].velocidad[0] = senos(un_angulo) * 0.6;
    lista_objeto[indice_objeto_1].velocidad[2] = coss(un_angulo) * 0.6;
}

void funcion_80080FEC(s32 parametro0) {
    s32 indice_objeto;
    s32 i;

    for (i = 0; i < 6; i++) {
        indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_2, &siguiente_libre_objeto_particula_2, objeto_particula_2_tamanio);
        if (indice_objeto == ID_OBJETO_NULO) {
            break;
        }
        funcion_80080E8C(indice_objeto, parametro0, i);
    }
}

void funcion_80081080(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->textura_activo = dato_8018D490;
    objeto->textura_lista = dato_8018D490;
    objeto->prim_alpha = 0x00FF;
    objeto->angulo_sentido[1] = 0;
    objeto->orientacion[0] = 0;
    objeto->orientacion[2] = 0;
    objeto->offset[0] = 0.0f;
    objeto->offset[1] = 0.0f;
    objeto->offset[2] = 0.0f;
    objeto->escalado_tamanio = 0.25f;
    estado_siguiente_objeto(indice_objeto);
}

void funcion_800810F4(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) { /* irregular */
        case 0:
            break;
        case 1:
            funcion_80081080(indice_objeto);
            break;
        case 2:
            agregar_desplazamiento_xz_velocidad_objeto(indice_objeto);
            arriba_paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], 14.0f, 0.5f);
            funcion_8007415C(indice_objeto, &lista_objeto[indice_objeto].escalado_tamanio, 0.25f, 0.75f, 0.025f, 1, 0);
            if (funcion_80073B00(indice_objeto, &lista_objeto[indice_objeto].prim_alpha, 0x000000FF, 0, 4, 0, 0) != 0) {
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 3:
            funcion_80072428(indice_objeto);
            break;
    }
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void funcion_80081208(void) {
}

void funcion_80081210(void) {
    Jugador* jugador;
    s32 indice_objeto;
    s32 variable_s2_3;
    s32 variable_s4;

    dato_80165834[0] += 0x100;
    dato_80165834[1] += 0x200;
    for (variable_s4 = 0; variable_s4 < thwomps_activo_num; variable_s4++) {
        indice_objeto = lista_objeto_indice_1[variable_s4];
        funcion_800722CC(indice_objeto, 0x00000010);
        funcion_8008A4CC(indice_objeto);
    }
    funcion_8007F8D8();
    for (variable_s4 = 0; variable_s4 < thwomps_activo_num; variable_s4++) {
        indice_objeto = lista_objeto_indice_1[variable_s4];
        if (lista_objeto[indice_objeto].state != 0) {
            switch (lista_objeto[indice_objeto].desconocido_0D5) {
                case 1:
                    funcion_8007ED6C(indice_objeto);
                    break;
                case 2:
                    funcion_8007F5A8(indice_objeto);
                    break;
                case 3:
                    funcion_8007FFC0(indice_objeto);
                    break;
                case 4:
                    funcion_800801FC(indice_objeto);
                    break;
                case 6:
                    funcion_80080408(indice_objeto);
                    break;
                case 5:
                    funcion_800808CC(indice_objeto);
                    break;
            }
        }
    }
    jugador = jugador_uno;
    for (variable_s4 = 0; variable_s4 < JUGADORES_NUM; variable_s4++, jugador++) {
        jugador->ruedas[IZQUIERDA_FRENTE].desconocido_14 &= ~3;
        jugador->desconocido_046 &= ~(PORTON_TOCAR_BICHO | TOCAR_BICHO);
        for (variable_s2_3 = 0; variable_s2_3 < thwomps_activo_num; variable_s2_3++) {
            indice_objeto = lista_objeto_indice_1[variable_s2_3];
            if (!(jugador->efectos & BOO_EFECTO)) {
                funcion_80080B28(indice_objeto, variable_s4);
            }
            if (es_obj_bandera_situacion_activo(indice_objeto, 0x00020000) != 0) {
                funcion_80080A14(indice_objeto, jugador);
            }
            if (es_obj_bandera_situacion_activo(indice_objeto, 0x00010000) != 0) {
                funcion_80080A4C(indice_objeto, variable_s4);
            }
        }
    }
    funcion_8007542C(3);
    for (variable_s4 = 0; variable_s4 < thwomps_activo_num; variable_s4++) {
        indice_objeto = lista_objeto_indice_1[variable_s4];
        if (funcion_80072320(indice_objeto, 0x00000020) == 0) {
            continue;
        }

        funcion_800722CC(indice_objeto, 0x00000020);
        funcion_80080FEC(indice_objeto);
    }
    for (variable_s4 = 0; variable_s4 < objeto_particula_2_tamanio; variable_s4++) {
        indice_objeto = particula_objeto_2[variable_s4];
        if (indice_objeto == ID_OBJETO_ELIMINADO) {
            continue;
        }
        if (lista_objeto[indice_objeto].state == 0) {
            continue;
        }
        funcion_800810F4(indice_objeto);
        if (lista_objeto[indice_objeto].state != 0) {
            continue;
        }
        eliminar_envoltorio_objeto(&particula_objeto_2[variable_s4]);
    }
}

void funcion_8008153C(s32 indice_objeto) {
    SIN_USO s32 margen_pila[3];
    s32 sp70;
    s32 variable_s1;
    s32 variable_s7;
    s32 indice_objeto_bucle;

    if (seleccion_cantidad_jugador_1 == 1) {
        sp70 = 8;
    } else {
        sp70 = 4;
    }

    for (variable_s7 = 0; variable_s7 < sp70; variable_s7++) {
        for (variable_s1 = 0; variable_s1 < objeto_particula_2_tamanio; variable_s1++) {
            indice_objeto_bucle = particula_objeto_2[variable_s1];

            if (lista_objeto[indice_objeto_bucle].state != 0) {
                continue;
            }

            inicializar_objeto(indice_objeto_bucle, 0);
            lista_objeto[indice_objeto_bucle].t_lut_activo = d_circuito_moo_moo_farm_tierra_topo;
            lista_objeto[indice_objeto_bucle].tlut_lista = d_circuito_moo_moo_farm_tierra_topo;
            lista_objeto[indice_objeto_bucle].escalado_tamanio = 0.15f;
            lista_objeto[indice_objeto_bucle].velocidad[1] = int_aleatorio(0x000AU);
            lista_objeto[indice_objeto_bucle].velocidad[1] = (lista_objeto[indice_objeto_bucle].velocidad[1] * 0.1) + 4.8;
            lista_objeto[indice_objeto_bucle].desconocido_034 = int_aleatorio(5U);
            lista_objeto[indice_objeto_bucle].desconocido_034 = (lista_objeto[indice_objeto_bucle].desconocido_034 * 0.01) + 0.8;
            lista_objeto[indice_objeto_bucle].orientacion[1] = (0x10000 / sp70) * variable_s1;
            lista_objeto[indice_objeto_bucle].pos_origen[0] = lista_objeto[indice_objeto].pos_origen[0];
            lista_objeto[indice_objeto_bucle].pos_origen[1] = lista_objeto[indice_objeto].pos_origen[1] - 13.0;
            lista_objeto[indice_objeto_bucle].pos_origen[2] = lista_objeto[indice_objeto].pos_origen[2];
            break;
        }
    }
}

void funcion_80081790(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) {
        case 0:
            break; /* irregular */
        case 1:
            if (funcion_80087E08(indice_objeto, lista_objeto[indice_objeto].velocidad[1], 0.3f, lista_objeto[indice_objeto].desconocido_034,
                              lista_objeto[indice_objeto].orientacion[1], 0x00000032) != 0) {
                estado_siguiente_objeto(indice_objeto);
            }
            calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
            break;
        case 2:
            funcion_80072428(indice_objeto);
            funcion_80086F60(indice_objeto);
            break;
    }
}
