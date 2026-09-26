// Ventana item y objetos

f32 dato_800E43B0[] = { 65536.0, 0.0, 1.0, 0.0, 0.0, 65536.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

Vtx dato_800E43F0[] = {
    { { { -24, -19, 0 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { 23, -19, 0 }, 0, { 3008, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { 23, 20, 0 }, 0, { 3008, 2496 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { -24, 20, 0 }, 0, { 0, 2496 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { -24, -19, 0 }, 0, { 3008, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { 23, -19, 0 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { 23, 20, 0 }, 0, { 0, 2496 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { -24, 20, 0 }, 0, { 3008, 2496 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
};

Vtx dato_800E4470[] = {
    { { { -24, -19, 0 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { 23, -19, 0 }, 0, { 3008, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { 23, 20, 0 }, 0, { 3008, 2496 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { -24, 20, 0 }, 0, { 0, 2496 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
};

Vtx dato_800E44B0[] = {
    { { { -24, -19, 0 }, 0, { 3008, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { 23, -19, 0 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { 23, 20, 0 }, 0, { 0, 2496 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { -24, 20, 0 }, 0, { 3008, 2496 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
};

u16* ventana_item_ts_tlu[] = { tlut_comun_ventana_item_ninguno,
                            tlut_comun_ventana_item_banana,
                            tlut_comun_ventana_item_grupo_banana,
                            tlut_comun_ventana_item_caparazon_verde,
                            tlut_comun_ventana_item_triple_caparazon_verde,
                            tlut_comun_ventana_item_caparazon_rojo,
                            tlut_comun_ventana_item_triple_caparazon_rojo,
                            tlut_comun_ventana_item_caparazon_azul,
                            tlut_comun_ventana_item_rayo,
                            tlut_comun_ventana_item_caja_item_falsa,
                            tlut_comun_ventana_item_estrella,
                            tlut_comun_ventana_item_boo,
                            tlut_comun_ventana_item_hongo,
                            tlut_comun_ventana_item_doble_hongo,
                            tlut_comun_ventana_item_triple_hongo,
                            tlut_comun_ventana_item_super_hongo };

u8* ventana_item_texturas[] = { textura_comun_ventana_item_ninguno,
                              textura_comun_ventana_item_banana,
                              textura_comun_ventana_item_grupo_banana,
                              textura_comun_ventana_item_caparazon_verde,
                              textura_comun_ventana_item_triple_caparazon_verde,
                              textura_comun_ventana_item_caparazon_rojo,
                              textura_comun_ventana_item_triple_caparazon_rojo,
                              textura_comun_ventana_item_caparazon_azul,
                              textura_comun_ventana_item_rayo,
                              textura_comun_ventana_item_caja_item_falsa,
                              textura_comun_ventana_item_estrella,
                              textura_comun_ventana_item_boo,
                              textura_comun_ventana_item_hongo,
                              textura_comun_ventana_item_doble_hongo,
                              textura_comun_ventana_item_triple_hongo,
                              textura_comun_ventana_item_super_hongo };

u16* texturas_vuelta_hud[] = { comun_textura_hud_vuelta_1_en_3, comun_textura_hud_vuelta_2_en_3,
                           comun_textura_hud_vuelta_3_en_3 };

u16* ts_tlu_retrato[] = { retrato_tlut_comun_mario, retrato_tlut_comun_luigi,       retrato_tlut_comun_yoshi,
                          retrato_tlut_comun_toad,  retrato_tlut_comun_donkey_kong, retrato_tlut_comun_wario,
                          retrato_tlut_comun_peach, retrato_tlut_comun_bowser };

u8* texturas_retrato[] = { retrato_textura_comun_mario,       retrato_textura_comun_luigi,
                            retrato_textura_comun_yoshi,       retrato_textura_comun_toad,
                            retrato_textura_comun_donkey_kong, retrato_textura_comun_wario,
                            retrato_textura_comun_peach,       retrato_textura_comun_bowser };

s32 buscar_indice_obj_sin_uso(s32* parametro0) {
    s32 temporal_v0;
    s32 temporal_v1;

    temporal_v1 = tamanio_lista_objeto;
    temporal_v0 = 0; do {
        ++temporal_v1;
        ++temporal_v0;

        if (temporal_v1 == TAMANIO_LISTA_OBJETO) {
            temporal_v1 = 0;
        }
    } while ((lista_objeto[temporal_v1].desconocido_0CA != 0) && (temporal_v0 != TAMANIO_LISTA_OBJETO));

    lista_objeto[temporal_v1].desconocido_0CA = 1;

    *parametro0 = temporal_v1;
    tamanio_lista_objeto = temporal_v1;
    return temporal_v1;
}

void eliminar_objeto(s32* indice_objeto) {
    funcion_80072428(*indice_objeto);
    lista_objeto[*indice_objeto].desconocido_0CA = 0;
    *indice_objeto = ID_OBJETO_NULO;
}

s32 funcion_80071FBC(void) {
    s32 indice_objeto;
    s32 algun_cantidad = 0;
    for (indice_objeto = 0; indice_objeto < TAMANIO_LISTA_OBJETO; indice_objeto++) {
        if (lista_objeto[indice_objeto].desconocido_0CA != 0) {
            algun_cantidad++;
        }
    }
    return algun_cantidad;
}

s32 agregar_indice_obj_sin_uso(s32* idx_lista, s32* libre_siguiente, s32 size) {
    s32 cantidad;
    s32 indice_objeto;
    s32* id;

    if (*libre_siguiente >= size) {
        *libre_siguiente = 0;
    }
    cantidad = 0;
    id = &idx_lista[*libre_siguiente];

    for (cantidad = 0; cantidad < size; cantidad++) {
        if (*id == ID_OBJETO_NULO) {
            indice_objeto = buscar_indice_obj_sin_uso(id);
            *libre_siguiente += 1;
            break;
        } else {
            *libre_siguiente += 1;
            if (*libre_siguiente >= size) {
                *libre_siguiente = 0;
            }
            id = &idx_lista[*libre_siguiente];
        }
    }
    if (cantidad == size) {
        indice_objeto = ID_OBJETO_NULO;
    }
    return indice_objeto;
}

void eliminar_envoltorio_objeto(s32* parametro0) {
    eliminar_objeto(parametro0);
}

void funcion_80072120(s32* parametro0, s32 parametro1) {
    s32 i;

    for (i = 0; i < parametro1; i++) {
        fijar_objeto_bandera_situacion_false(*parametro0, 0x00600000);
        parametro0++;
    }
}

void funcion_80072180(void) {
    if (seleccion_modo == CONTRARRELOJ) {
        if (((jugador_uno->type & EXISTE_JUGADOR) != 0) &&
            ((jugador_uno->type & (INVISIBLE_JUGADOR_O_BOMBA | CPU_JUGADOR)) == 0)) {
            publicar_contrarreloj_guardado_no_puede_repeticion = 1;
        }
    }
}

void fijar_objeto_bandera_situacion_true(s32 indice_objeto, s32 bandera) {
    lista_objeto[indice_objeto].status |= bandera;
}

void fijar_objeto_bandera_situacion_false(s32 indice_objeto, s32 bandera) {
    lista_objeto[indice_objeto].status &= ~bandera;
}

SIN_USO void funcion_80072214(s32 indice_objeto, s32 parametro1) {
    lista_objeto[indice_objeto].status ^= parametro1;
}

bool es_obj_bandera_situacion_activo(s32 indice_objeto, s32 parametro1) {
    s32 phi_v1 = false;
    if ((lista_objeto[indice_objeto].status & parametro1) != 0) {
        phi_v1 = true;
    }
    return phi_v1;
}

s32 es_obj_indice_bandera_situacion_inactivo(s32 indice_objeto, s32 parametro1) {
    s32 phi_v1 = 0;
    if ((lista_objeto[indice_objeto].status & parametro1) == 0) {
        phi_v1 = 1;
    }
    return phi_v1;
}

void funcion_800722A4(s32 indice_objeto, s32 parametro1) {
    lista_objeto[indice_objeto].desconocido_058 |= parametro1;
}

void funcion_800722CC(s32 indice_objeto, s32 parametro1) {
    lista_objeto[indice_objeto].desconocido_058 &= ~parametro1;
}

SIN_USO void funcion_800722F8(s32 indice_objeto, s32 parametro1) {
    lista_objeto[indice_objeto].desconocido_058 ^= parametro1;
}

bool funcion_80072320(s32 indice_objeto, s32 parametro1) {
    s32 b = false;
    if ((lista_objeto[indice_objeto].desconocido_058 & parametro1) != 0) {
        b = true;
    }
    return b;
}

bool funcion_80072354(s32 indice_objeto, s32 parametro1) {
    s32 b = false;
    if ((lista_objeto[indice_objeto].desconocido_058 & parametro1) == 0) {
        b = true;
    }
    return b;
}

void fijar_estado_temporizador_objeto(s32 indice_objeto, s32 parametro1) {
    lista_objeto[indice_objeto].activo_temporizador_es = parametro1;
}

void inicializar_objeto(s32 indice_objeto, s32 parametro1) {
    lista_objeto[indice_objeto].status = 0;
    lista_objeto[indice_objeto].desconocido_058 = 0;
    lista_objeto[indice_objeto].desconocido_05C = 0;
    lista_objeto[indice_objeto].desconocido_0CD = 0;
    lista_objeto[indice_objeto].desconocido_0CF = 0;
    fijar_estado_temporizador_objeto(indice_objeto, 0);
    lista_objeto[indice_objeto].desconocido_0D8 = parametro1;
    lista_objeto[indice_objeto].state = 1;
}

SIN_USO void funcion_80072408(s32 indice_objeto) {
    fijar_estado_temporizador_objeto(indice_objeto, 0);
}

void funcion_80072428(s32 indice_objeto) {
    lista_objeto[indice_objeto].state = 0;
    lista_objeto[indice_objeto].desconocido_0D8 = 0;
    fijar_estado_temporizador_objeto(indice_objeto, 0);
    lista_objeto[indice_objeto].status = 0;
    lista_objeto[indice_objeto].desconocido_058 = 0;
    lista_objeto[indice_objeto].desconocido_05C = 0;
    funcion_80086F60(indice_objeto);
}

void estado_siguiente_objeto(s32 indice_objeto) {
    fijar_estado_temporizador_objeto(indice_objeto, 0);
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x2000);
    lista_objeto[indice_objeto].state++;
}

void funcion_800724DC(s32 indice_objeto) {
    lista_objeto[indice_objeto].desconocido_0D7 = 0;
}

void funcion_800724F8(s32 indice_objeto, s32 parametro1) {
    lista_objeto[indice_objeto].desconocido_084[lista_objeto[indice_objeto].desconocido_0D7] = parametro1;
    lista_objeto[indice_objeto].desconocido_0D7++;
}

s16 funcion_80072530(s32 indice_objeto) {
    lista_objeto[indice_objeto].desconocido_0D7--;
    return lista_objeto[indice_objeto].desconocido_084[lista_objeto[indice_objeto].desconocido_0D7];
}

void funcion_80072568(s32 indice_objeto, s32 parametro1) {
    fijar_estado_temporizador_objeto(indice_objeto, 0);
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x2000);
    fijar_objeto_bandera_situacion_false(indice_objeto, 8);
    estado_siguiente_objeto(indice_objeto);
    funcion_800724F8(indice_objeto, lista_objeto[indice_objeto].state);
    lista_objeto[indice_objeto].state = parametro1;
}

void funcion_800725E8(s32 indice_objeto, s32 parametro1, s32 parametro2) {
    fijar_estado_temporizador_objeto(indice_objeto, 0);
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x2000);
    fijar_objeto_bandera_situacion_false(indice_objeto, 8);
    lista_objeto[indice_objeto].state = parametro2;
    funcion_800724F8(indice_objeto, lista_objeto[indice_objeto].state);
    lista_objeto[indice_objeto].state = parametro1;
}

s16 funcion_80072530(s32);

void funcion_8007266C(s32 indice_objeto) {
    fijar_estado_temporizador_objeto(indice_objeto, 0);
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x2000);
    fijar_objeto_bandera_situacion_false(indice_objeto, 8);
    lista_objeto[indice_objeto].state = funcion_80072530(indice_objeto);
}

void funcion_800726CC(s32 indice_objeto, s32 parametro1) {
    fijar_estado_temporizador_objeto(indice_objeto, 0);
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x2000);
    lista_objeto[indice_objeto].state = parametro1;
}

SIN_USO void funcion_8007271C(s32 indice_objeto, s32 parametro1) {
    if (lista_objeto[indice_objeto].activo_temporizador_es == 0) {
        lista_objeto[indice_objeto].state = parametro1;
    }
}

SIN_USO void funcion_8007274C(s32 indice_objeto) {
    if (lista_objeto[indice_objeto].activo_temporizador_es == 0) {
        estado_siguiente_objeto(indice_objeto);
    }
}

bool ejecutar_objeto_temporizador_conjunto_y(s32 indice_objeto, s32 temporizador) {
    bool phi_v1;

    phi_v1 = false;
    if (lista_objeto[indice_objeto].activo_temporizador_es == false) {
        fijar_estado_temporizador_objeto(indice_objeto, true);
        lista_objeto[indice_objeto].temporizador = temporizador;
    }

    lista_objeto[indice_objeto].temporizador--;
    if (lista_objeto[indice_objeto].temporizador < 0) {
        fijar_estado_temporizador_objeto(indice_objeto, false);
        estado_siguiente_objeto(indice_objeto);
        phi_v1 = true;
    }

    return phi_v1;
}

SIN_USO s32 funcion_8007281C(s32 indice_objeto, s32 parametro1) {
    s32 phi_a2;

    phi_a2 = 0;
    if (lista_objeto[indice_objeto].activo_temporizador_es == 0) {
        fijar_estado_temporizador_objeto(indice_objeto, 1);
        lista_objeto[indice_objeto].temporizador = int_aleatorio((u16) parametro1);
    }

    lista_objeto[indice_objeto].temporizador--;
    if (lista_objeto[indice_objeto].temporizador < 0) {
        fijar_estado_temporizador_objeto(indice_objeto, 0);
        estado_siguiente_objeto(indice_objeto);
        phi_a2 = 1;
    }

    return phi_a2;
}

SIN_USO s32 funcion_800728B0(s32 indice_objeto, s32 parametro1, s32 parametro2) {
    s32 phi_a3;

    phi_a3 = 0;
    if (lista_objeto[indice_objeto].activo_temporizador_es == 0) {
        fijar_estado_temporizador_objeto(indice_objeto, 1);
        lista_objeto[indice_objeto].temporizador = int_aleatorio((u16) parametro2) + parametro1;
    }

    lista_objeto[indice_objeto].temporizador--;
    if (lista_objeto[indice_objeto].temporizador < 0) {
        fijar_estado_temporizador_objeto(indice_objeto, 0);
        estado_siguiente_objeto(indice_objeto);
        phi_a3 = 1;
    }

    return phi_a3;
}

void funcion_80072950(s32 indice_objeto, s32 parametro1, s32 parametro2, s32 parametro3) {
    if (parametro1 == parametro2) {
        lista_objeto[indice_objeto].state = parametro3;
    }
}

SIN_USO void funcion_80072974(s32 indice_objeto, s32 parametro1, s32 parametro2, s32 parametro3) {
    if (parametro1 != parametro2) {
        lista_objeto[indice_objeto].state = parametro3;
    }
}

SIN_USO void funcion_80072998(s32 indice_objeto) {
    lista_objeto[indice_objeto].desconocido_0CC = 0;
}

void funcion_800729B4(s32 indice_objeto, s32 parametro1) {
    lista_objeto[indice_objeto].desconocido_0A2 = parametro1;
}

void fijar_objeto_tipo(s32 indice_objeto, s32 parametro1) {
    lista_objeto[indice_objeto].type = parametro1;
}

void funcion_800729EC(s32 indice_objeto) {
    u32 temporal_v1 = 1;
    s32 i;

    empezar_carrera();
    estado_siguiente_objeto(indice_objeto);
    dato_8018D2BC = 1;
    dato_8018D2A4 = 1;

    if (id_circuito_actual != CIRCUITO_YOSHI_VALLEY) {
        for (i = 0; i < cantidad_jugador; i++) {
            h_ud_jugador[i].desconocido_81 = temporal_v1;
        }
    }
    funcion_8005AB20();
}

SIN_USO void funcion_80072A78(s32 indice_objeto, s32 parametro1) {
    lista_objeto[indice_objeto].textura_indice_lista = parametro1;
    estado_siguiente_objeto(indice_objeto);
}

s32 funcion_80072AAC(s32 indice_objeto, s32 parametro1, s32 parametro2) {
    s32 phi_v1;

    phi_v1 = 0;
    if (lista_objeto[indice_objeto].activo_temporizador_es == 0) {

        fijar_estado_temporizador_objeto(indice_objeto, 1);
        lista_objeto[indice_objeto].textura_indice_lista = parametro1;
        lista_objeto[indice_objeto].temporizador = parametro2;
    }

    lista_objeto[indice_objeto].temporizador--;
    if (lista_objeto[indice_objeto].temporizador < 0) {
        fijar_estado_temporizador_objeto(indice_objeto, 0);
        estado_siguiente_objeto(indice_objeto);
        phi_v1 = 1;
    }

    return phi_v1;
}

s32 funcion_80072B48(s32 indice_objeto, s32 parametro1) {
    s32 phi_v1;

    phi_v1 = 0;
    if (lista_objeto[indice_objeto].activo_temporizador_es == 0) {
        fijar_estado_temporizador_objeto(indice_objeto, 1);
        fijar_objeto_bandera_situacion_true(indice_objeto, 0x80000);
        lista_objeto[indice_objeto].textura_indice_lista = dato_8018D140;
        lista_objeto[indice_objeto].temporizador = parametro1;
    }

    lista_objeto[indice_objeto].temporizador--;
    if (lista_objeto[indice_objeto].temporizador < 0) {
        fijar_objeto_bandera_situacion_false(indice_objeto, 0x80000);
        fijar_estado_temporizador_objeto(indice_objeto, 0);
        estado_siguiente_objeto(indice_objeto);
        phi_v1 = 1;
    }

    return phi_v1;
}

void funcion_80072C00(s32 indice_objeto, s32 parametro1, s32 parametro2, s32 parametro3) {
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 0x2000) != 0) {
        lista_objeto[indice_objeto].temporizador = parametro2;
        lista_objeto[indice_objeto].textura_indice_lista = parametro1;
        lista_objeto[indice_objeto].desconocido_0D4 = 1;
        lista_objeto[indice_objeto].desconocido_0CC = parametro3;
        fijar_objeto_bandera_situacion_true(indice_objeto, 0x2000);
    } else {
        lista_objeto[indice_objeto].temporizador--;
        if (lista_objeto[indice_objeto].temporizador < 0) {
            lista_objeto[indice_objeto].temporizador = parametro2;
            lista_objeto[indice_objeto].desconocido_0D4--;
            if ((lista_objeto[indice_objeto].desconocido_0D4 & 1) != 0) {
                fijar_objeto_bandera_situacion_false(indice_objeto, 0x80000);
            } else {
                fijar_objeto_bandera_situacion_true(indice_objeto, 0x80000);
            }

            if (lista_objeto[indice_objeto].desconocido_0D4 < 0) {
                lista_objeto[indice_objeto].desconocido_0D4 = 1;

                if (lista_objeto[indice_objeto].desconocido_0CC > 0) {
                    lista_objeto[indice_objeto].desconocido_0CC--;
                }

                if (lista_objeto[indice_objeto].desconocido_0CC == 0) {
                    fijar_objeto_bandera_situacion_false(indice_objeto, 0x2000);
                    estado_siguiente_objeto(indice_objeto);
                }
            }
        }
    }
}

void funcion_80072D3C(s32 indice_objeto, s32 parametro1, s32 parametro2, s32 parametro3, s32 parametro4) {
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 0x2000) != 0) {
        lista_objeto[indice_objeto].temporizador = parametro3;
        lista_objeto[indice_objeto].textura_indice_lista = parametro1;
        lista_objeto[indice_objeto].desconocido_0D4 = 1;
        lista_objeto[indice_objeto].desconocido_0CC = parametro4;
        fijar_objeto_bandera_situacion_true(indice_objeto, 0x2000);
        return;
    }

    lista_objeto[indice_objeto].temporizador--;
    if (lista_objeto[indice_objeto].temporizador < 0) {
        lista_objeto[indice_objeto].temporizador = parametro3;
        lista_objeto[indice_objeto].desconocido_0D4--;
        if ((lista_objeto[indice_objeto].desconocido_0D4 & 1) != 0) {
            lista_objeto[indice_objeto].textura_indice_lista = parametro1;
        } else {
            lista_objeto[indice_objeto].textura_indice_lista = parametro2;
        }

        if (lista_objeto[indice_objeto].desconocido_0D4 < 0) {
            lista_objeto[indice_objeto].desconocido_0D4 = 1;
            if (lista_objeto[indice_objeto].desconocido_0CC > 0) {
                lista_objeto[indice_objeto].desconocido_0CC--;
            }

            if (lista_objeto[indice_objeto].desconocido_0CC == 0) {
                fijar_objeto_bandera_situacion_false(indice_objeto, 0x2000);
                estado_siguiente_objeto(indice_objeto);
            }
        }
    }
}

s32 funcion_80072E54(s32 indice_objeto, s32 parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5) {
    s32 sp24;

    sp24 = 0;
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 0x2000) != 0) {
        lista_objeto[indice_objeto].textura_indice_lista = parametro1;
        lista_objeto[indice_objeto].temporizador = parametro4;
        lista_objeto[indice_objeto].desconocido_0CC = parametro5;
        fijar_estado_temporizador_objeto(indice_objeto, 1);
        fijar_objeto_bandera_situacion_true(indice_objeto, 0x2000);
    } else {
        lista_objeto[indice_objeto].temporizador--;
        if (lista_objeto[indice_objeto].temporizador <= 0) {
            lista_objeto[indice_objeto].temporizador = parametro4;
            lista_objeto[indice_objeto].textura_indice_lista += parametro3;
            if (parametro2 < lista_objeto[indice_objeto].textura_indice_lista) {

                if (lista_objeto[indice_objeto].desconocido_0CC > 0) {
                    lista_objeto[indice_objeto].desconocido_0CC--;
                }
                if (lista_objeto[indice_objeto].desconocido_0CC == 0) {
                    lista_objeto[indice_objeto].textura_indice_lista = parametro2;
                    fijar_objeto_bandera_situacion_false(indice_objeto, 0x2000);
                    fijar_estado_temporizador_objeto(indice_objeto, 0);
                    estado_siguiente_objeto(indice_objeto);
                    sp24 = 1;
                } else {
                    lista_objeto[indice_objeto].textura_indice_lista = parametro1;
                }
            }
        }
    }
    return sp24;
}

bool funcion_80072F88(s32 indice_objeto, s32 parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5) {
    s32 sp24;

    sp24 = false;
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 0x2000) != 0) {
        lista_objeto[indice_objeto].textura_indice_lista = parametro1;
        lista_objeto[indice_objeto].temporizador = parametro4;
        lista_objeto[indice_objeto].desconocido_0CC = parametro5;
        fijar_estado_temporizador_objeto(indice_objeto, 1);
        fijar_objeto_bandera_situacion_true(indice_objeto, 0x2000);
    } else {
        lista_objeto[indice_objeto].temporizador--;
        if (lista_objeto[indice_objeto].temporizador <= 0) {
            lista_objeto[indice_objeto].temporizador = parametro4;
            lista_objeto[indice_objeto].textura_indice_lista -= parametro3;
            if (lista_objeto[indice_objeto].textura_indice_lista < parametro2) {
                if (lista_objeto[indice_objeto].desconocido_0CC > 0) {
                    lista_objeto[indice_objeto].desconocido_0CC--;
                }
                if (lista_objeto[indice_objeto].desconocido_0CC == 0) {
                    lista_objeto[indice_objeto].textura_indice_lista = parametro2;
                    fijar_objeto_bandera_situacion_false(indice_objeto, 0x2000);
                    fijar_estado_temporizador_objeto(indice_objeto, 0);
                    estado_siguiente_objeto(indice_objeto);
                    sp24 = true;
                } else {
                    lista_objeto[indice_objeto].textura_indice_lista = parametro1;
                }
            }
        }
    }
    return sp24;
}

bool funcion_800730BC(s32 indice_objeto, s32 parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5) {
    s32 sp24;

    sp24 = false;
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 0x2000) != 0) {
        lista_objeto[indice_objeto].textura_indice_lista = parametro1;
        lista_objeto[indice_objeto].temporizador = parametro4;
        lista_objeto[indice_objeto].desconocido_0CC = parametro5;
        fijar_estado_temporizador_objeto(indice_objeto, 1);
        fijar_objeto_bandera_situacion_true(indice_objeto, 0x2000);
        fijar_objeto_bandera_situacion_false(indice_objeto, 0x4000);
    } else {
        lista_objeto[indice_objeto].temporizador--;
        if (lista_objeto[indice_objeto].temporizador <= 0) {
            lista_objeto[indice_objeto].temporizador = parametro4;
            if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 0x4000) != 0) {
                lista_objeto[indice_objeto].textura_indice_lista += parametro3;
                if (lista_objeto[indice_objeto].textura_indice_lista >= parametro2) {
                    lista_objeto[indice_objeto].textura_indice_lista = parametro2;
                    fijar_objeto_bandera_situacion_true(indice_objeto, 0x4000);
                }
            } else {
                lista_objeto[indice_objeto].textura_indice_lista -= parametro3;
                if (parametro1 >= lista_objeto[indice_objeto].textura_indice_lista) {
                    lista_objeto[indice_objeto].textura_indice_lista = parametro1;
                    if (lista_objeto[indice_objeto].desconocido_0CC > 0) {
                        lista_objeto[indice_objeto].desconocido_0CC--;
                    }

                    if (lista_objeto[indice_objeto].desconocido_0CC == 0) {
                        fijar_objeto_bandera_situacion_false(indice_objeto, 0x80);
                        fijar_objeto_bandera_situacion_false(indice_objeto, 0x2000);
                        fijar_estado_temporizador_objeto(indice_objeto, 0);
                        estado_siguiente_objeto(indice_objeto);
                        sp24 = true;
                    } else {
                        fijar_objeto_bandera_situacion_false(indice_objeto, 0x4000);
                        fijar_objeto_bandera_situacion_true(indice_objeto, 0x80);
                    }
                }
            }
        }
    }
    return sp24;
}

s32 funcion_8007326C(s32 indice_objeto, s32 parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5) {
    s32 sp24;

    sp24 = 0;
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 0x2000) != 0) {
        lista_objeto[indice_objeto].textura_indice_lista = parametro1;
        lista_objeto[indice_objeto].temporizador = parametro4;
        lista_objeto[indice_objeto].desconocido_0CC = parametro5;
        fijar_estado_temporizador_objeto(indice_objeto, 1);
        fijar_objeto_bandera_situacion_true(indice_objeto, 0x2000);
        fijar_objeto_bandera_situacion_false(indice_objeto, 0x4000);
    } else {
        lista_objeto[indice_objeto].temporizador--;
        if (lista_objeto[indice_objeto].temporizador <= 0) {
            lista_objeto[indice_objeto].temporizador = parametro4;
            if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 0x4000) != 0) {
                lista_objeto[indice_objeto].textura_indice_lista -= parametro3;
                if (parametro2 >= lista_objeto[indice_objeto].textura_indice_lista) {
                    lista_objeto[indice_objeto].textura_indice_lista = parametro2;
                    fijar_objeto_bandera_situacion_true(indice_objeto, 0x4000);
                }
            } else {
                lista_objeto[indice_objeto].textura_indice_lista += parametro3;
                if (lista_objeto[indice_objeto].textura_indice_lista >= parametro1) {
                    lista_objeto[indice_objeto].textura_indice_lista = parametro1;
                    if (lista_objeto[indice_objeto].desconocido_0CC > 0) {
                        lista_objeto[indice_objeto].desconocido_0CC--;
                    }
                    if (lista_objeto[indice_objeto].desconocido_0CC == 0) {
                        fijar_objeto_bandera_situacion_false(indice_objeto, 0x2000);
                        fijar_estado_temporizador_objeto(indice_objeto, 0);
                        estado_siguiente_objeto(indice_objeto);
                        sp24 = 1;
                    } else {
                        fijar_objeto_bandera_situacion_false(indice_objeto, 0x4000);
                    }
                }
            }
        }
    }
    return sp24;
}

void funcion_80073404(s32 indice_objeto, u8 parametro1, u8 parametro2, Vtx* parametro3) {
    lista_objeto[indice_objeto].vertice = parametro3;
    lista_objeto[indice_objeto].textura_ancho = parametro1;
    lista_objeto[indice_objeto].textura_altura = parametro2;
    lista_objeto[indice_objeto].textura_indice_lista = 0;
    lista_objeto[indice_objeto].desconocido_0D3 = -1;
    lista_objeto[indice_objeto].status = 0;
}

void inicializar_objeto_textura(s32 indice_objeto, u8* textura, u8* parametro2, u8 parametro3, u16 parametro4) {
    lista_objeto[indice_objeto].tlut_lista = textura;
    lista_objeto[indice_objeto].textura_lista = parametro2;
    lista_objeto[indice_objeto].textura_ancho = parametro3;
    lista_objeto[indice_objeto].textura_altura = parametro4;
    lista_objeto[indice_objeto].textura_indice_lista = 0;
    lista_objeto[indice_objeto].desconocido_0D3 = -1;
    lista_objeto[indice_objeto].status = 0;
}

SIN_USO void funcion_8007348C(s32 indice_objeto, u8* parametro1, u8 parametro2, u8 parametro3, Vtx* parametro4) {
    lista_objeto[indice_objeto].t_lut_activo = parametro1;
    lista_objeto[indice_objeto].tlut_lista = parametro1;
    lista_objeto[indice_objeto].textura_ancho = parametro2;
    lista_objeto[indice_objeto].textura_altura = parametro3;
    lista_objeto[indice_objeto].vertice = parametro4;
    lista_objeto[indice_objeto].textura_indice_lista = 0;
    lista_objeto[indice_objeto].desconocido_0D3 = -1;
    lista_objeto[indice_objeto].status = 0;
}

SIN_USO void funcion_800734D4() {
}

void actualizar_textura_neon(s32 indice_objeto) {
    lista_objeto[indice_objeto].t_lut_activo =
        (u8*) ((u32*) lista_objeto[indice_objeto].tlut_lista + (lista_objeto[indice_objeto].textura_indice_lista * 128));
    lista_objeto[indice_objeto].textura_activo = lista_objeto[indice_objeto].textura_lista;
}

void funcion_80073514(s32 indice_objeto) {
    lista_objeto[indice_objeto].t_lut_activo = lista_objeto[indice_objeto].tlut_lista;
    lista_objeto[indice_objeto].textura_activo =
        lista_objeto[indice_objeto].textura_lista +
        (lista_objeto[indice_objeto].textura_ancho * lista_objeto[indice_objeto].textura_altura *
         lista_objeto[indice_objeto].textura_indice_lista);
}

SIN_USO void funcion_80073568() {
}

SIN_USO void funcion_80073570(s32 indice_objeto) {
    s16* probar = &lista_objeto[indice_objeto].state;

    dato_8018D1EC++;
    if (dato_8018D1EC == 5) {
        dato_8018D1EC = 0;
    }
    (*probar)++;
}

void funcion_800735BC(s32 indice_objeto, Gfx* parametro1, f32 parametro2) {
    lista_objeto[indice_objeto].status = 0;
    lista_objeto[indice_objeto].model = parametro1;
    lista_objeto[indice_objeto].escalado_tamanio = parametro2;
    estado_siguiente_objeto(indice_objeto);
}

void funcion_80073600(s32 indice_objeto) {
    fijar_estado_temporizador_objeto(indice_objeto, 0);
    lista_objeto[indice_objeto].desconocido_0D6 = 0;
    lista_objeto[indice_objeto].desconocido_04C = -1;
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x8000);
}

void funcion_80073654(s32 indice_objeto) {
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x8000);
    ++lista_objeto[indice_objeto].desconocido_0D6;
}

SIN_USO void funcion_8007369C(s32 indice_objeto, s32 parametro1) {
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x8000);
    lista_objeto[indice_objeto].desconocido_0D6 = parametro1;
}

void funcion_800736E0(s32 indice_objeto) {
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x8000);
    lista_objeto[indice_objeto].desconocido_0D6 = 1;
}

void funcion_80073720(s32 indice_objeto) {
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x8000);
    lista_objeto[indice_objeto].desconocido_0D6 = 0;
}

bool funcion_8007375C(s32 indice_objeto, s32 parametro1) {
    s32 sp24;

    sp24 = false;
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 0x00008000) != 0) {
        lista_objeto[indice_objeto].desconocido_04C = parametro1;
        fijar_objeto_bandera_situacion_true(indice_objeto, 0x00008000);
    }
    lista_objeto[indice_objeto].desconocido_04C--;
    if (lista_objeto[indice_objeto].desconocido_04C < 0) {
        fijar_objeto_bandera_situacion_false(indice_objeto, 0x00008000);
        funcion_80073654(indice_objeto);
        sp24 = true;
    }
    return sp24;
}

void funcion_80073800(s32 indice_objeto, s32 parametro1) {
    lista_objeto[indice_objeto].desconocido_0CF = parametro1;
}

void funcion_8007381C(s32 indice_objeto) {
    lista_objeto[indice_objeto].desconocido_0DC++;
}

void funcion_80073844(s32 indice_objeto) {
    funcion_80073800(indice_objeto, 0);
    lista_objeto[indice_objeto].desconocido_0DC = 1;
}

void funcion_80073884(s32 indice_objeto) {
    lista_objeto[indice_objeto].desconocido_0DC = 0;
    lista_objeto[indice_objeto].desconocido_0CF = 0;
}

s32 funcion_800738A8(s32 indice_objeto, s16* parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6) {
    s32 phi_t0;

    phi_t0 = 0;
    if (lista_objeto[indice_objeto].desconocido_0CF == 0) {
        *parametro1 = parametro2;
        lista_objeto[indice_objeto].desconocido_0AC = parametro5;
        lista_objeto[indice_objeto].desconocido_0D0 = parametro6;
        funcion_80073800(indice_objeto, 1);
    } else {
        lista_objeto[indice_objeto].desconocido_0AC--;
        if (lista_objeto[indice_objeto].desconocido_0AC < 0) {
            lista_objeto[indice_objeto].desconocido_0AC = parametro5;
            *parametro1 += parametro4;
            if (parametro3 < *parametro1) {
                if (lista_objeto[indice_objeto].desconocido_0D0 > 0) {
                    lista_objeto[indice_objeto].desconocido_0D0--;
                }

                if (lista_objeto[indice_objeto].desconocido_0D0 == 0) {
                    *parametro1 = parametro3;
                    funcion_80073800(indice_objeto, 0);
                    funcion_8007381C(indice_objeto);
                    phi_t0 = 1;
                } else {
                    *parametro1 = parametro2;
                }
            }
        }
    }

    return phi_t0;
}

void funcion_80073998(s32 parametro0, s16* parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6) {
    funcion_800738A8(parametro0, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6);
}

SIN_USO void funcion_800739CC(s32 parametro0, s16* parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6) {
    if (*parametro1 < parametro3) {
        funcion_800738A8(parametro0, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6);
    }
}

bool funcion_80073A10(s32 indice_objeto, s16* parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6) {
    bool phi_t0;

    phi_t0 = false;
    if (lista_objeto[indice_objeto].desconocido_0CF == 0) {
        *parametro1 = parametro2;
        lista_objeto[indice_objeto].desconocido_0AC = parametro5;
        lista_objeto[indice_objeto].desconocido_0D0 = parametro6;
        funcion_80073800(indice_objeto, 1);
    } else {
        lista_objeto[indice_objeto].desconocido_0AC--;
        if (lista_objeto[indice_objeto].desconocido_0AC < 0) {
            lista_objeto[indice_objeto].desconocido_0AC = parametro5;
            *parametro1 -= parametro4;
            if (*parametro1 < parametro3) {
                if (lista_objeto[indice_objeto].desconocido_0D0 > 0) {
                    lista_objeto[indice_objeto].desconocido_0D0--;
                }

                if (lista_objeto[indice_objeto].desconocido_0D0 == 0) {
                    *parametro1 = parametro3;
                    funcion_80073800(indice_objeto, 0);
                    funcion_8007381C(indice_objeto);
                    phi_t0 = true;
                } else {
                    *parametro1 = parametro2;
                }
            }
        }
    }

    return phi_t0;
}

s32 funcion_80073B00(s32 parametro0, s16* parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6) {
    return funcion_80073A10(parametro0, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6);
}
