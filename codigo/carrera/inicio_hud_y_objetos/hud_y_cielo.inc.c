// Hud y cielo

void inicializar_hud(void) {

    reiniciar_variable_objeto();
    funcion_8006FA94();

    switch (seleccion_modo_pantalla) {
        case MODO_PANTALLA_1P:
            inicializar_jugador_hud_uno();
            break;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            inicializar_vertical_jugador_hud_dos();
            break;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
            inicializar_horizontal_jugador_hud_dos();
            break;
        case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
            inicializar_jugador_hud_tres_cuatro();
            break;
    }
    funcion_80070148();
}

void reiniciar_variable_objeto(void) {
    s32 i;
    s32 j;
    funcion_8006EB10();
    borrar_lista_objeto();
    bzero(h_ud_jugador, TAMANIO_JUGADORES_HUD * sizeof(jugador_hud));

    for (i = 0; i < TAMANIO_JUGADORES_HUD; i++) {
        h_ud_jugador[i].cantidad_vuelta = 0;
        h_ud_jugador[i].cantidad_vuelta_tambien = 0;
        h_ud_jugador[i].desconocido_81 = 0;
    }
    for (j = 0; j < TAMANIO_JUGADORES_HUD; j++) {
        h_ud_jugador[j].bool_completo_carrera = 0;
    }
}

void funcion_8006EB10(void) {
    s32 i;

    for (i = 0; i < objeto_particula_1_tamanio; i++) {
        particula_objeto_1[i] = ID_OBJETO_NULO;
    }

    for (i = 0; i < objeto_particula_2_tamanio; i++) {
        particula_objeto_2[i] = ID_OBJETO_NULO;
    }

    for (i = 0; i < objeto_particula_3_tamanio; i++) {
        particula_objeto_3[i] = ID_OBJETO_NULO;
    }

    for (i = 0; i < objeto_particula_4_tamanio; i++) {
        particula_objeto_4[i] = ID_OBJETO_NULO;
    }

    for (i = 0; i < hoja_particula_tamanio; i++) { particula_hoja[i] = ID_OBJETO_NULO; }

    dato_8018CF18 = dato_8018CF20 = dato_8018CF48 = dato_8018CF60 = dato_8018CF78 = dato_8018CF90 = dato_8018CFA8 = 0;
    dato_8018CFB0 = dato_8018CFB8 = dato_8018CFC0 = dato_8018CFC8 = dato_8018CFD0 = dato_8018CFD8 = dato_8018CFE0 = 0;
    dato_8018D018 = 0;
    dato_8018D010 = 0;
    dato_8018D008 = 0;
    dato_8018D000 = 0;
    dato_8018CFF8 = 0;
    dato_8018CFF0 = 0;
    dato_8018CFE8 = 0;
    dato_8018D110 = 0;
    dato_8018D0E8 = 0;
    dato_8018D0C0 = 0;
    dato_8018D020 = dato_8018D048 = dato_8018D070 = dato_8018D098 = 0;
    siguiente_libre_objeto_particula_1 = siguiente_libre_objeto_particula_2 = siguiente_libre_objeto_particula_3 = siguiente_libre_objeto_particula_4 =
        siguiente_libre_hoja_particula = 0;
}

void borrar_lista_objeto() {
    bzero(lista_objeto, TAMANIO_LISTA_OBJETO * sizeof(Objeto));
    tamanio_lista_objeto = -1;
}

u8* copiar_texturas_varios_base_dma(u8* direccion_dev, u8* direccion_base, u32 size, u32 desplazamiento) {
    u8** direccion_temporal;
    u8* direccion_2;
    direccion_2 = direccion_base + desplazamiento;

    size = ALIGN16(size);
    osInvalDCache(direccion_2, (size));
    osPiStartDma(&msj_io_dma, 0, 0, (uintptr_t) &_other_texturesSegmentRomStart[((u32) direccion_dev) & 0xFFFFFF], direccion_2,
                 size, &cola_msj_dma);
    osRecvMesg(&cola_msj_dma, &msj_recibido_principal, 1);
    direccion_temporal = &direccion_2;
    mio0decode(*direccion_temporal, (u8*) direccion_base);
    return direccion_base;
}

void cargar_mario_kart_64_logo(void) {
    direccion_logo_juego =
        copiar_texturas_varios_base_dma((u8*) &logo_mario_kart_64, (u8*) buffer_textura_menu, 0x79E1, 0x20000);
}

void inicializar_ventana_item(s32 indice_objeto) {
    VentanaItemObjetos* temporal_v0;

    temporal_v0 = (VentanaItemObjetos*) &lista_objeto[indice_objeto];
    temporal_v0->item_actual = NINGUNO_ITEM;
    temporal_v0->textura_indice_lista = temporal_v0->item_actual;
    temporal_v0->tlut_lista = (u8*) tlut_comun_ventana_item_ninguno;
    temporal_v0->t_lut_activo = (u8*) tlut_comun_ventana_item_ninguno;
    temporal_v0->textura_lista = textura_comun_ventana_item_ninguno;
    temporal_v0->textura_activo = textura_comun_ventana_item_ninguno;
    temporal_v0->desconocido_04C = -1;
    temporal_v0->desconocido_09C = 0x00A0;
    temporal_v0->desconocido_09E = -0x0020; // Screen Y position
    temporal_v0->escalado_tamanio = 1.0f;
}

void funcion_8006EEE8(s32 id_circuito) {
    dato_8018D240 = (s32) texturas_dma(texturas_contorno_circuito[id_circuito], dato_800E5520[id_circuito], dato_800E5520[id_circuito]);
    dato_8018D2B0 = dato_800E5548[id_circuito * 2];
    dato_8018D2B8 = dato_800E5548[id_circuito * 2 + 1];
}

void funcion_8006EF60(void) {
    s32 i;
    s16 huh;
    u8* wut;

    wut = (u8*) &buffer_comprimido_menu[0x3FFFC000];
    huh = 0x14; if (0) {} for (i = 0; i < huh; i++) { dato_8018D248[i] = copiar_texturas_varios_base_dma(texturas_contorno_circuito[i], wut, dato_800E5520[i], dato_800E5520[i]); wut += dato_800E5520[i]; }
}

void ajustes_minimapa_pista(void) {
    dato_801655C8 = 0;
    orientacion_x = 1.0f;
    if (es_modo_espejo != 0) {
        orientacion_x = -1.0f;
    }
    minimapa_linea_meta_x[0] = 257;
    minimapa_linea_meta_y[0] = 170;
    dato_8018D300 = 255;
    dato_8018D308 = 255;
    dato_8018D310 = 255;
    dato_8018D318 = 255;
    if (id_circuito_actual < CIRCUITOS_NUM - 1) {
        funcion_8006EEE8((s32) id_circuito_actual);
    }
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_MARIO_RACEWAY:
            dato_8018D220 = (void*) texturas_dma(textura_escape_5, 0x443, 0x1000);
            minimapa_escala_marcador = 0.022f;
            minimapa_x = 6;
            minimapa_y = 28;
            minimapa_linea_meta_x[0] = 260;
            minimapa_linea_meta_y[0] = 170;
            dato_80165718 = 0;
            dato_80165720 = 5;
            dato_80165728 = -240;
            break;
        case CIRCUITO_CHOCO_MOUNTAIN:
            minimapa_escala_marcador = 0.022f;
            minimapa_linea_meta_x[0] = 265;
            minimapa_x = 19;
            minimapa_y = 37;
            break;
        case CIRCUITO_BOWSER_CASTLE:
            minimapa_linea_meta_x[0] = 265;
            minimapa_escala_marcador = 0.0174f;
            minimapa_x = 12;
            minimapa_y = 48;
            break;
        case CIRCUITO_BANSHEE_BOARDWALK:
            dato_80165880 = (void*) texturas_dma(textura_fantasmas, 0x4CC2, 0xD980);
            minimapa_escala_marcador = 0.016f;
            minimapa_linea_meta_x[0] = 0x0106;
            minimapa_x = 55;
            minimapa_y = 39;
            break;
        case CIRCUITO_YOSHI_VALLEY:
            dato_8018D220 = (void*) texturas_dma(textura_escape_0, 0x479, 0xC00);
            minimapa_escala_marcador = 0.018f;
            minimapa_x = 61;
            minimapa_y = 38;
            break;
        case CIRCUITO_FRAPPE_SNOWLAND:
            minimapa_linea_meta_x[0] = 262;
            minimapa_escala_marcador = 0.016f;
            minimapa_x = 36;
            minimapa_y = 40;
            dato_8018D300 = 72;
            dato_8018D308 = 100;
            dato_8018D310 = 255;
            break;
        case CIRCUITO_KOOPA_BEACH:
            dato_8018D220 = (void*) texturas_dma(textura_escape_3, 0x3C8U, 0x1000);
            minimapa_escala_marcador = 0.014f;
            minimapa_linea_meta_x[0] = 268;
            minimapa_x = 40;
            minimapa_y = 21;
            break;
        case CIRCUITO_ROYAL_RACEWAY:
            dato_8018D220 = (void*) texturas_dma(textura_escape_4, 0x3F8, 0x1000);
            minimapa_linea_meta_x[0] = 262;
            minimapa_escala_marcador = 0.014f;
            minimapa_x = 37;
            minimapa_y = 50;
            dato_80165718 = -64;
            dato_80165720 = 5;
            dato_80165728 = -330;
            break;
        case CIRCUITO_LUIGI_RACEWAY:
            dato_8018D220 = (void*) texturas_dma(textura_escape_2, 0x4F4U, 0xC00);
            minimapa_escala_marcador = 0.0155f;
            minimapa_linea_meta_x[0] = 271;
            minimapa_x = 45;
            minimapa_y = 60;
            dato_80165718 = -140;
            dato_80165720 = -44;
            dato_80165728 = -215;
            break;
        case CIRCUITO_MOO_MOO_FARM:
            dato_8018D220 = (void*) texturas_dma(textura_escape_0, 0x479, 0xC00);
            minimapa_escala_marcador = 0.0155f;
            minimapa_linea_meta_x[0] = 271;
            minimapa_x = 18;
            minimapa_y = 36;
            break;
        case CIRCUITO_TOADS_TURNPIKE:
            minimapa_escala_marcador = 0.013f;
            minimapa_linea_meta_x[0] = 252;
            minimapa_x = 57;
            minimapa_y = 44;
            break;
        case CIRCUITO_KALAMARI_DESERT:
            minimapa_linea_meta_x[0] = 263;
            minimapa_linea_meta_y[0] = 165;
            dato_8018D220 = (void*) texturas_dma(textura_escape_5, 0x443, 0x1000);
            minimapa_escala_marcador = 0.015f;
            minimapa_x = 55;
            minimapa_y = 27;
            break;
        case CIRCUITO_SHERBET_LAND:
            dato_8018D220 = (void*) texturas_dma(textura_escape_1, 0x485, 0xC00);
            minimapa_escala_marcador = 0.015f;
            minimapa_linea_meta_x[0] = 262;
            minimapa_x = 52;
            minimapa_y = 33;
            dato_8018D300 = 72;
            dato_8018D308 = 100;
            dato_8018D310 = 255;
            break;
        case CIRCUITO_RAINBOW_ROAD:
            minimapa_escala_marcador = 0.0103f;
            minimapa_linea_meta_x[0] = 261;
            minimapa_linea_meta_y[0] = 166;
            minimapa_x = 39;
            minimapa_y = 55;
            break;
        case CIRCUITO_WARIO_STADIUM:
            minimapa_escala_marcador = 0.0155f;
            minimapa_linea_meta_x[0] = 0x0106;
            minimapa_x = 53;
            minimapa_y = 35;
            break;
        case CIRCUITO_BLOCK_FORT:
            minimapa_escala_marcador = 0.0335f;
            minimapa_x = 32;
            minimapa_y = 32;
            break;
        case CIRCUITO_SKYSCRAPER:
            minimapa_escala_marcador = 0.0445f;
            minimapa_x = 32;
            minimapa_y = 32;
            break;
        case CIRCUITO_DOUBLE_DECK:
            minimapa_escala_marcador = 0.0285f;
            minimapa_x = 32;
            minimapa_y = 32;
            break;
        case CIRCUITO_DK_JUNGLE:
            minimapa_escala_marcador = 0.0155f;
            minimapa_linea_meta_x[0] = 255;
            minimapa_x = 29;
            minimapa_y = 47;
            break;
        case CIRCUITO_BIG_DONUT:
            minimapa_escala_marcador = 0.0257f;
            minimapa_x = 32;
            minimapa_y = 31;
    }
#else

#endif
    if (es_modo_espejo != 0) {
        minimapa_x = dato_8018D2B0 - minimapa_x;
    }
    if (cantidad_jugador == 4) {
        minimapa_linea_meta_x[0] = 160;
        minimapa_linea_meta_y[0] = 120;
        return;
    }
    if (cantidad_jugador == 3) {
        minimapa_linea_meta_x[0] = 235;
        minimapa_linea_meta_y[0] = 175;
        return;
    }
    if (cantidad_jugador == 2) {
        if (id_circuito_actual != CIRCUITO_TOADS_TURNPIKE) {
            minimapa_linea_meta_x[1] = 265;
            minimapa_linea_meta_x[0] = minimapa_linea_meta_x[1];
        } else {
            minimapa_linea_meta_x[1] = 255;
            minimapa_linea_meta_x[0] = minimapa_linea_meta_x[1];
        }
        minimapa_linea_meta_y[0] = 65;
        minimapa_linea_meta_y[1] = 180;
    }
}

void funcion_8006F824(s32 parametro0) {
    dato_80165808 = dato_801657E4;
    dato_80165810 = dato_801657E6;
    dato_80165820 = dato_801657F0;
    dato_80165818 = dato_801657E8;
    dato_80165828 = dato_801657F8;
    dato_80165832[0] = dato_80165800[0];
    dato_80165832[1] = dato_80165800[1];
    if ((parametro0 != 0) && (juego_en_pausa == 0)) {
        reproducir_sonido2(SONIDO_PING_ACCION);
    }
}

void funcion_8006F8CC(void) {
    if (inicializacion_mapa_circuito == 0) {
        inicializacion_mapa_circuito = 1;
        dato_801657E4 = 0;
        dato_801657E6 = 0;
        dato_801657F0 = 0;
        dato_801657E8 = 1;
        dato_80165800[0] = dato_80165800[1] = 1;
        if (cantidad_jugador == 4) {
            if (seleccion_modo != BATALLA) {
                dato_801657E4 = 1;
                dato_801657F0 = 1;
                dato_801657F8 = 1;
                dato_80165800[0] = dato_80165800[1] = 0;
            } else {
                dato_801657F8 = 0;
                dato_80165800[0] = dato_80165800[1] = 1;
            }
        } else if (cantidad_jugador == 3) {
            dato_801657E8 = 0;
            dato_801657F8 = 1;
        } else if (cantidad_jugador == 2) {
            if (seleccion_modo != (s32) BATALLA) {
                dato_801657E4 = 1;
                dato_801657F0 = 1;
                dato_80165800[0] = dato_80165800[1] = 0;
            }
            minimapa_linea_meta_y[0] = 0x0041;
            minimapa_linea_meta_y[1] = 0x00B4;
        }
        funcion_8006F824(0);
    } else {
        dato_801657E4 = dato_80165808;
        dato_801657E6 = dato_80165810;
        dato_801657F0 = dato_80165820;
        dato_801657E8 = dato_80165818;
        dato_801657F8 = dato_80165828;
        dato_80165800[0] = dato_80165832[0];
        dato_80165800[1] = dato_80165832[1];
    }
    if (modo_demo != 0) {
        dato_801657F0 = 0;
    }
}

void funcion_8006FA94(void) {
    s32 i;
    Jugador *jugador;

    funcion_8006F8CC();
    ajustes_minimapa_pista();
    osSetTime(0);
    dato_8018D170 = 0;
    dato_8018D190 = 0;
    es_visible_hud = 0;
    dato_8018D178 = 0;
    dato_8018D1CC = 0;
    dato_801657E2 = 0;
    dato_80165730 = 0;
    dato_801658FE = 0;

    dato_801657E1 = dato_801657E3 = dato_801657E5 = 0;

    dato_80165658[0] = dato_80165658[1] = dato_80165658[2] = 0;
    dato_801658BC = dato_801658C6 = dato_801658CE = dato_801658DC = dato_801658EC = dato_801658F4 = dato_801658E4 = dato_801658D6 = 0;

    switch (cantidad_jugador) {
    case 1:
        if (seleccion_modo == GRAN_PREMIO) {
            dato_8018D114 = 0;
            dato_8018D178 = 150;
            dato_8018D180 = 240;
        } else {
            dato_8018D114 = 1;
            dato_8018D178 = 10;
            dato_8018D180 = 0;
        }
        break;
    case 2:
        if (seleccion_modo_pantalla == PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL) {
            if (seleccion_modo == GRAN_PREMIO) {
                dato_8018D114 = 2;
                dato_8018D178 = 150;
                dato_8018D180 = 240;
                dato_8018D2AC = 60;
            } else if (seleccion_modo == VERSUS) {
                dato_8018D114 = 3;
                dato_8018D178 = 30;
                dato_8018D180 = 30;
                dato_8018D2AC = 60;
            } else {
                dato_8018D114 = 4;
                dato_8018D178 = 40;
                dato_8018D180 = 40;
                dato_8018D2AC = 60;
            }
        } else if (seleccion_modo == GRAN_PREMIO) {
            dato_8018D114 = 5;
        } else if (seleccion_modo == VERSUS) {
            dato_8018D114 = 6;
        } else {
            dato_8018D114 = 7;
        }
        break;
    case 3:
        if (seleccion_modo == VERSUS) {
            dato_8018D114 = 8;
            dato_8018D178 = 0x00000064;
            dato_8018D180 = 0x00000096;
            dato_8018D2AC = 0x0000003C;
        } else {
            dato_8018D114 = 9;
            dato_8018D178 = 0x00000064;
            dato_8018D180 = 0x00000096;
            dato_8018D2AC = 0x0000003C;
        }
        break;
    case 4:
        if (seleccion_modo == VERSUS) {
            dato_8018D114 = 0x0000000A;
            dato_8018D178 = 0x0000001E;
            dato_8018D180 = 0x0000001E;
            dato_8018D2AC = 0x0000000A;
        } else {
            dato_8018D114 = 0x0000000B;
            dato_8018D178 = 0x0000001E;
            dato_8018D180 = 0x0000001E;
            dato_8018D2AC = 0x0000000A;
        }
        break;
    }
    if (modo_depuracion_activacion == 0) {
        dato_8016576A = 0;
        dato_8016579C = 0;
    }

    for (i = 0; i < cantidad_jugador; i++) {
        dato_8018CFC4[i] = dato_8018CFAC[i] = dato_8018CFBC[i] = 0;
        dato_8018CFB4[i] = 0;
    }

    dato_8018D204 = 1;
    dato_8018D1FC = 0;
    dato_8018D224 = 0;
    dato_8018D1F0 = dato_8018D1F8 = 0;
    dato_8018D228 = 0xFF;

    dato_801655D8 = dato_801655E8 = dato_801655F8 = dato_80165608 = dato_80165618 = dato_80165628 = 0;
    dato_8018D160 = 0;
    dato_8018D1DC = 0;
    dato_8018D1C4 = 0;
    dato_8018D1B4 = 0;
    dato_8018D1A0 = 0;
    dato_8018D168 = 0;
    dato_801656F0 = 0;
    dato_801657AE = desactivar_hud = dato_8018D214 = dato_801657D8 = dato_801657B2 = 0;
    dato_8018D20C = 0;
    dato_8018D2F0 = dato_8018D2F8 = 0;
    dato_8018D320 = 3;
    dato_8018D2AC = 0;
    dato_8018D2A4 = dato_8018D2B4 = dato_8018D2BC = 0;
    dato_8018D2C8[0] = dato_8018D2C8[1] = dato_8018D2C8[2] = dato_8018D2C8[3] = 0;
    dato_8016581C = 0;
    dato_8016580C = 0;
    dato_80165814 = 0;
    dato_80165804 = 0;
    dato_801657FC = 0;
    dato_8018D174 = dato_8018D17C = dato_8018D16C = dato_8018D184 = dato_8018D18C = -1;
    jugador = jugador_uno;
    for (i = 0; i < JUGADORES_NUM; i++) {
        dato_8018D0F0[i] = dato_8018D050[i] = -32.0f;
        dato_8018CE10[i].desconocido_04[0] = dato_8018CE10[i].desconocido_04[1] = dato_8018CE10[i].desconocido_04[2] = 0.0f;
        dato_8018CF50[i] = i;
        dato_8018CF28[i] = jugador;
        jugador->desconocido_040 = -1;
        jugador++;
    }
}

void funcion_80070148(void) {
    s32 variable_s0;

    for (variable_s0 = 0; variable_s0 < 8; variable_s0++) {
        buscar_indice_obj_sin_uso(&dato_8018CE10[variable_s0].indice_objeto);
    }
}

void inicializar_indice_lista_objeto(void) {
    s32 indice_bucle;

    for (indice_bucle = 0; indice_bucle < ALGUN_OBJETO_INDICE_LISTA_TAMANIO; indice_bucle++) {
        buscar_indice_obj_sin_uso(&lista_objeto_indice_1[indice_bucle]);
        buscar_indice_obj_sin_uso(&lista_objeto_indice_2[indice_bucle]);
        buscar_indice_obj_sin_uso(&lista_objeto_indice_3[indice_bucle]);
        buscar_indice_obj_sin_uso(&lista_objeto_indice_4[indice_bucle]);
    }

    for (indice_bucle = 0; indice_bucle < NUM_KARTS_BOMBA_VERSUS; indice_bucle++) {
        buscar_indice_obj_sin_uso(&objeto_indice_kart_bomba[indice_bucle]);
    }
}

void inicializar_objeto_nube(s32 indice_objeto, s32 parametro1, DatosNube* parametro2) {
    VentanaItemObjetos* temporal_v0;

    inicializar_objeto(indice_objeto, parametro1);
    temporal_v0 = (VentanaItemObjetos*) &lista_objeto[indice_objeto];
    temporal_v0->desconocido_0D5 = parametro2->tipo_sub;
    temporal_v0->item_actual = NINGUNO_ITEM;
    temporal_v0->angulo_sentido[1] = parametro2->rot_y;
    temporal_v0->desconocido_09E = parametro2->pos_y;
    temporal_v0->escalado_tamanio = (f32) parametro2->porciento_escala / 100.0;
    temporal_v0->textura_activo = (u8*) &dato_8018D220[parametro2->tipo_sub];
    funcion_80073404(indice_objeto, 0x40U, 0x20U, dato_0D005FB0);
    temporal_v0->prim_alpha = 0x00FF;
}

void inicializar_nubes(DatosNube* lista_nube) {
    s32 variable_s0 = 0;
    DatosNube* probar = &lista_nube[0];
    do {
        if (1) {}
        inicializar_objeto_nube(buscar_indice_obj_sin_uso(&dato_8018CC80[dato_8018D1F8 + variable_s0]), 1, probar);
        variable_s0++;
        probar++;
    } while (probar->rot_y != 0xFFFF);
    dato_8018D1F8 += variable_s0;
    dato_8018D1F0 = variable_s0;
    dato_8018D230 = 0;
}

void inicializar_objeto_estrella(s32 indice_objeto, s32 parametro1, DatosEstrella* parametro2) {
    VentanaItemObjetos* temporal_v0;

    inicializar_objeto(indice_objeto, parametro1);
    temporal_v0 = (VentanaItemObjetos*) &lista_objeto[indice_objeto];
    temporal_v0->desconocido_0D5 = parametro2->tipo_sub;
    temporal_v0->item_actual = ITEM_BANANA;
    temporal_v0->angulo_sentido[1] = parametro2->rot_y;
    temporal_v0->desconocido_09E = parametro2->pos_y;                           // screen Y position
    temporal_v0->escalado_tamanio = (f32) parametro2->porciento_escala / 100.0;
    temporal_v0->textura_activo = dato_0D0293D8;
    funcion_80073404(indice_objeto, 0x10U, 0x10U, rectangulo_vtx_comun);
}

void inicializar_estrellas(DatosEstrella* lista_estrella) {
    s32 variable_s0 = 0;
    DatosEstrella* probar = &lista_estrella[0];
    do {
        if (1) {}
        inicializar_objeto_estrella(buscar_indice_obj_sin_uso(&dato_8018CC80[dato_8018D1F8 + variable_s0]), 1, probar);
        variable_s0++;
        probar++;
    } while (probar->rot_y != 0xFFFF);
    dato_8018D1F8 += variable_s0;
    dato_8018D1F0 = variable_s0;
    dato_8018D230 = 1;
}

void inicializar_nube_circuito(void) {
    s32 variable_s0;
    s32 variable_s4;

#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_MARIO_RACEWAY:
            inicializar_nubes(kalimari_desert_nubes);
            break;
        case CIRCUITO_YOSHI_VALLEY:
            inicializar_nubes(yoshi_valley_moo_moo_farm_nubes);
            break;
        case CIRCUITO_FRAPPE_SNOWLAND:
            if (cantidad_jugador == 1) {
                variable_s4 = 0x32;
            } else {
                variable_s4 = 0x19;
            }
            for (variable_s0 = 0; variable_s0 < variable_s4; variable_s0++) {
                buscar_indice_obj_sin_uso(&dato_8018CC80[dato_8018D1F8 + variable_s0]);
            }
            dato_8018D1F8 += variable_s0;
            dato_8018D1F0 = variable_s0;
            break;
        case CIRCUITO_KOOPA_BEACH:
            inicializar_nubes(koopa_troopa_beach_nubes);
            break;
        case CIRCUITO_ROYAL_RACEWAY:
            inicializar_nubes(royal_raceway_nubes);
            break;
        case CIRCUITO_LUIGI_RACEWAY:
            inicializar_nubes(luigi_raceway_nubes);
            break;
        case CIRCUITO_MOO_MOO_FARM:
            inicializar_nubes(yoshi_valley_moo_moo_farm_nubes);
            break;
        case CIRCUITO_TOADS_TURNPIKE:
            inicializar_estrellas(toads_turnpike_rainbow_road_estrellas);
            break;
        case CIRCUITO_KALAMARI_DESERT:
            inicializar_nubes(kalimari_desert_nubes);
            break;
        case CIRCUITO_SHERBET_LAND:
            inicializar_nubes(sherbet_land_nubes);
            break;
        case CIRCUITO_RAINBOW_ROAD:
            inicializar_estrellas(toads_turnpike_rainbow_road_estrellas);
            break;
        case CIRCUITO_WARIO_STADIUM:
            inicializar_estrellas(wario_stadium_estrellas);
            break;
    }
#else

#endif
    funcion_8008C23C();
}

void funcion_80070714(void) {
    dato_80165730 = 1;
    if (cantidad_jugador == UN_JUGADORES_SELECCIONADO) {
        dato_80165738 = 0x64;
        dato_80165740 = 0x3C;
        dato_80165748 = 0x1E;
        return;
    }
    dato_80165738 = 0x32;
    dato_80165740 = 0x1E;
    dato_80165748 = 0xA;
}
