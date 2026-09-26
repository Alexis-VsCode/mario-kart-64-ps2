// Agregar items menu

void funcion_8009E17C(u32 parametro0) {
    if (tipo_transicion[4] != 4) {
        tipo_transicion[4] = 4;
        duracion_transicion[4] = parametro0;
        if (duracion_transicion[4] >= 0x100U) {
            duracion_transicion[4] = 0x000000FFU;
        }
        dato_8018E7E0 = 0;
    }
}

void funcion_8009E1C0(void) {
    funcion_8009DFE0(10);
    tipo_fundido_menu = MENU_FUNDIDO_TIPO_PRINCIPAL;
}

void funcion_8009E1E4(void) {
    funcion_8009E000(10);
    tipo_fundido_menu = MENU_FUNDIDO_TIPO_PRINCIPAL;
}

void funcion_8009E208(void) {
    funcion_8009DFE0(10);
    tipo_fundido_menu = MENU_FUNDIDO_TIPO_ATRAS;
}

void funcion_8009E230(void) {
    funcion_8009DFE0(10);
    tipo_fundido_menu = MENU_FUNDIDO_TIPO_DEMO;
}

void funcion_8009E258(void) {
    funcion_8009DFE0(10);
    tipo_fundido_menu = MENU_FUNDIDO_TIPO_DATOS;
}

void funcion_8009E280(void) {
    funcion_8009DFE0(10);
    tipo_fundido_menu = MENU_FUNDIDO_TIPO_OPCION;
}

void funcion_8009E2A8(s32 parametro0) {
    switch (dato_8018E838[parametro0]) {
        case 0:
            break;
        case 1:
            funcion_8009E2F0(parametro0);
            break;
        default:
            dato_8018E838[parametro0] = 0;
            break;
    }
}

void funcion_8009E2F0(s32 parametro0) {
    SIN_USO s32 margen_pila_0;
    SIN_USO s32 margen_pila_1;
    s32 algun_indice;
    s32 temporal_t7;
    f32 temporal_t7_2;
    RGBA16* temporal_v0;
    struct desconocido_struct_8018E7E8* temporal_t0;
    struct desconocido_struct_8018E7E8* temporal_t1;

    temporal_t7 = dato_800F0B28[dato_8018E840[parametro0]];
    if (temporal_t7 != 0) {
        temporal_t1 = &dato_8018E7E8[parametro0];
        temporal_t0 = &dato_8018E810[parametro0];
        temporal_v0 = &dato_800E7AC8[temporal_t7];
        if ((u32) dato_8018E840[parametro0] < 0x1BU) {
            display_list_cabeza = dibujar_caja(display_list_cabeza, temporal_t1->x - (temporal_t0->x / 2), temporal_t1->y - (temporal_t0->y / 2),
                                        temporal_t1->x + (temporal_t0->x / 2), temporal_t1->y + (temporal_t0->y / 2), temporal_v0->rojo,
                                        temporal_v0->verde, temporal_v0->azul, temporal_v0->alpha);
        } else {
            temporal_t7_2 = ((u32) (38 - dato_8018E840[parametro0])) / 11.0;
            display_list_cabeza = dibujar_caja(display_list_cabeza, temporal_t1->x - (temporal_t0->x / 2), temporal_t1->y - (temporal_t0->y / 2),
                                        temporal_t1->x + (temporal_t0->x / 2), temporal_t1->y + (temporal_t0->y / 2), temporal_v0->rojo,
                                        temporal_v0->verde, temporal_v0->azul, (u32) (temporal_v0->alpha * temporal_t7_2));
        }
    }
    dato_8018E840[parametro0]++;
    if ((u32) dato_8018E840[parametro0] >= 0x26U) {
        for (algun_indice = 0; algun_indice < 4; algun_indice++) {
            dato_8018E838[algun_indice] = 0;
        }
    }
}

void funcion_8009E5BC(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        funcion_8009E5FC(i);
    }
}

void funcion_8009E5FC(s32 parametro0) {
    dato_8018E838[parametro0] = 1;
    dato_8018E840[parametro0] = 0;
}

void borrar_menus(void) {
    s32 index;
    for (index = 0; index < CANTIDAD_ARREGLO(menu_items); index++) {
        menu_items[index].type = 0;
    }
}

void agregar_item_menu(s32 type, s32 columna, s32 renglon, s8 prioridad) {
    MenuItem* menu_item;
    s8 temporal_a1;
    s32 i;
    AnimacionMk* variable_a0;
#ifdef AVOID_UB
    TexturaMenu* textura;
#endif

    i = 0;
    menu_item = menu_items;
    while (true) {
        if (menu_item->type == 0) {
            break;
        }
        i++;
        if (i > CANTIDAD_ARREGLO(menu_items)) {
            while (true) {}
        }
        menu_item++;
    }
    menu_item->type = type;
    menu_item->state = 0;
    menu_item->estado_sub = 0;
    menu_item->column = columna;
    menu_item->row = renglon;
    menu_item->priority = prioridad;
    menu_item->visible = 1;
    menu_item->param1 = 0;
    menu_item->param2 = 0;
    switch (type) {
        case MENU_ITEM_IU_LOGO_INTRO:
            temporizador_modelo_intro = 0;
            intro_modelo_movimiento_rapidez = 0;
            intro_modelo_rapidez = 3.0f;
            ojo_modelo_z_intro = 2500;
            rot_x_modelo_intro = 0.0f;
            rot_y_modelo_intro = -270.0f;
            rot_z_modelo_intro = 0.0f;
            pos_x_modelo_intro = 0.0f;
            pos_y_modelo_intro = 0.0f;
            pos_z_modelo_intro = 0.0f;
            escala_modelo_intro = 3;
            menu_item->param1 = -1;
            menu_item->param2 = 1;
            break;
        case MENU_INICIO_BANDERA:
            ojo_modelo_z_intro = 1800;
            rot_x_modelo_intro = -51.0f;
            rot_y_modelo_intro = -12.0f;
            rot_z_modelo_intro = -18.0f;
            pos_x_modelo_intro = -270.0f;
            pos_y_modelo_intro = 750.0f;
            pos_z_modelo_intro = 0.0f;
            escala_modelo_intro = 1.0f;
            menu_item->param1 = -1;
            menu_item->param2 = 1;
            break;
        case TIPO_ITEM_MENU_0D2:
            cargar_menu_img_comp_tipo(dato_020014C8, CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            funcion_8009B954(dato_020014C8);
            gfx_ptr = renderizar_texturas_menu(gfx_ptr, dato_020014C8, menu_item->column, menu_item->row);
            funcion_8009B998();
            break;
        case TIPO_ITEM_MENU_0D3:
            cargar_menu_img_comp_tipo(dato_02001540, CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            funcion_8009B954(dato_02001540);
            gfx_ptr = renderizar_texturas_menu(gfx_ptr, dato_02001540, menu_item->column, menu_item->row);
            funcion_8009B998();
            break;
        case TIPO_ITEM_MENU_0D4:
            cargar_menu_img_comp_tipo(dato_0200157C, CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            cargar_img_menu(dato_02001874);
            menu_item->row = 0x69;
            for (i = 0; i < 133; i++) {
                cargar_img_menu(segmentado_a_duplicado_virtual(dato_800E7AF8[i]));
            }
            break;
        case TIPO_ITEM_MENU_0D5:
            cargar_img_menu(dato_020015A4);
            funcion_8009B954(dato_020015A4);
            gfx_ptr = renderizar_texturas_menu(gfx_ptr, dato_020015A4, menu_item->column, menu_item->row);
            gDPLoadTextureBlock(gfx_ptr++, funcion_8009B8C4(textura_7ED50C), G_IM_FMT_IA, G_IM_SIZ_16b, 256, 5, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gfx_ptr++, 0x80, 0x2C0, 0x480, 0x2D4, G_TX_RENDERTILE, 0, 0x80, 0x0400, 0xFC00);
            funcion_8009B998();
            cargar_img_menu(dato_020015CC);
            funcion_8009B954(dato_020015CC);
            gfx_ptr = renderizar_texturas_menu(gfx_ptr, dato_020015CC, menu_item->column, menu_item->row);
            funcion_8009B998();
            cargar_img_menu(dato_02001630);
            funcion_8009B954(dato_02001630);
            gfx_ptr = renderizar_texturas_menu(gfx_ptr, dato_02001630, menu_item->column, menu_item->row);
            funcion_8009B998();
            cargar_img_menu(dato_02001658);
            funcion_8009B954(dato_02001658);
            gfx_ptr = renderizar_texturas_menu(gfx_ptr, dato_02001658, menu_item->column, menu_item->row);
            funcion_8009B998();
            break;
        case TIPO_ITEM_MENU_0D6:
            menu_item->d_8018DEE0_indice = seleccionar_menu_personaje_animar(segmentado_a_duplicado_virtual_2(dato_800E7D34[0]));
            break;
        case TIPO_ITEM_MENU_0D7:
            for (i = 0; i < 10; i++) {
                cargar_img_menu(segmentado_a_duplicado_virtual(dato_800E7D0C[i]));
            }
            break;
        case TIPO_ITEM_MENU_0D8:
        case TIPO_ITEM_MENU_0D9:
            cargar_img_menu(dato_0200184C);
            break;
        case MENU_ITEM_IU_INICIO_FONDO:
            cargar_menu_img_comp_tipo(fondo_texturas_menu[tiene_modo_extra_desbloqueado()], CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            break;
        case MENU_ITEM_IU_LOGO_Y_COPYRIGHT:
            cargar_mario_kart_64_logo();
            menu_textura_buffer_indice += 0x10000;
            cargar_img_menu(textura_copyright_1996_seg2);
            break;
        case MENU_ITEM_IU_EMPUJE_INICIO_BOTON:
            cargar_img_menu(empujar_textura_boton_inicio_seg2);
            break;
        case MENU_PRINCIPAL_FONDO:
        case FONDO_SELECCION_PERSONAJE:
        case FONDO_SELECCION_CIRCUITO:
            cargar_menu_img_comp_tipo(fondo_texturas_menu[tiene_modo_extra_desbloqueado()], CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            cargar_menu_img_comp_tipo(dato_02004B74, CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            convertir_img_a_escala_grises(0, 0x00000019);
            ajustar_color_img(0, ANCHO_PANTALLA * ALTURA_PANTALLA, color_fondo[type - MENU_PRINCIPAL_FONDO].rojo,
                              color_fondo[type - MENU_PRINCIPAL_FONDO].verde, color_fondo[type - MENU_PRINCIPAL_FONDO].azul);
            break;
        case MENU_ITEM_IU_OK:
            menu_item->param1 = 0x20;
        case MENU_ITEM_IU_JUEGO_SELECCION:
        case MENU_PRINCIPAL_GFX_DATOS:
        case MENU_PRINCIPAL_GFX_OPCION:
        case MENU_PRINCIPAL_50CC:
        case MENU_PRINCIPAL_100CC:
        case MENU_PRINCIPAL_150CC:
        case 0x15:
        case 0x16:
        case 0x17:
        case MENU_PRINCIPAL_CONTRARRELOJ_EMPEZAR:
        case MENU_PRINCIPAL_CONTRARRELOJ_DATOS:
#ifdef AVOID_UB
            if (type < MENU_PRINCIPAL_50CC) {
                textura = dato_800E8254[type - MENU_ITEM_IU_JUEGO_SELECCION];
            } else if (type < TIPO_ITEM_MENU_016) {
                textura = dato_800E8274[type - MENU_PRINCIPAL_50CC];
            } else if (type < MENU_PRINCIPAL_CONTRARRELOJ_EMPEZAR) {
                textura = dato_800E8284[type - TIPO_ITEM_MENU_016];
            } else {
                textura = dato_800E828C[type - MENU_PRINCIPAL_CONTRARRELOJ_EMPEZAR];
            }
            cargar_menu_img_comp_tipo(segmentado_a_duplicado_virtual(textura), CARGA_MENU_IMG_TKMK00_UNA_VEZ);
#else
            cargar_menu_img_comp_tipo(segmentado_a_duplicado_virtual(dato_800E8274[type - 0x12]), CARGA_MENU_IMG_TKMK00_UNA_VEZ);
#endif
            break;
        case MENU_ITEM_IU_1J_JUEGO:
        case MENU_ITEM_IU_2J_JUEGO:
        case MENU_ITEM_IU_3J_JUEGO:
        case MENU_ITEM_IU_4J_JUEGO:
            cargar_menu_img_comp_tipo(segmentado_a_duplicado_virtual(dato_800E8234[((type - 0xB) * 2) + 0]),
                                    CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            cargar_img_menu(segmentado_a_duplicado_virtual(dato_800E8234[((type - 0xB) * 2) + 1]));
            break;
        case PERSONAJE_SELECCION_MENU_JUGADOR_SELECCION_CARTEL:
            cargar_menu_img_comp_tipo(dato_02004B4C, CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            break;
        case PERSONAJE_SELECCION_MENU_OK:
            cargar_menu_img_comp_tipo(dato_02004B74, CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            menu_item->param1 = 0x00000020;
            break;
        case PERSONAJE_SELECCION_MENU_1J_CURSOR:
        case PERSONAJE_SELECCION_MENU_2J_CURSOR:
        case PERSONAJE_SELECCION_MENU_3J_CURSOR:
        case PERSONAJE_SELECCION_MENU_4J_CURSOR:
            cargar_img_menu(segmentado_a_duplicado_virtual(menu_texturas_borde_jugador[type - PERSONAJE_SELECCION_MENU_1J_CURSOR]));
            break;
        case MENU_SELECCION_PERSONAJE_MARIO:
        case MENU_SELECCION_PERSONAJE_LUIGI:
        case MENU_SELECCION_PERSONAJE_TOAD:
        case MENU_SELECCION_PERSONAJE_PEACH:
        case MENU_SELECCION_PERSONAJE_YOSHI:
        case MENU_SELECCION_PERSONAJE_DK:
        case MENU_SELECCION_PERSONAJE_WARIO:
        case MENU_SELECCION_PERSONAJE_BOWSER:
            menu_item->d_8018DEE0_indice =
                seleccionar_menu_personaje_animar(segmentado_a_duplicado_virtual_2(dato_800E8320[type - 0x2B]));
            cargar_menu_img_comp_tipo(segmentado_a_duplicado_virtual(dato_800E7D54[type - 0x2B]), CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            break;
        case TIPO_ITEM_MENU_0A0:
        case TIPO_ITEM_MENU_0A1:
            menu_item->d_8018DEE0_indice =
                seleccionar_menu_personaje_animar(segmentado_a_duplicado_virtual_2(dato_800E8320[type - 0xA0]));
            break;
        case OK_SELECCION_CIRCUITO:
            menu_item->param1 = 0x00000020;
        case CIRCUITO_SELECCION_MAPA_SELECCION:
        case SELECCION_CIRCUITO_COPA_HONGO:
        case SELECCION_CIRCUITO_COPA_FLOR:
        case SELECCION_CIRCUITO_COPA_ESTRELLA:
        case SELECCION_CIRCUITO_COPA_ESPECIAL:
        case TIPO_ITEM_MENU_058:
        case CIRCUITO_SELECCION_CIRCUITO_NOMBRES:
        case TIPO_ITEM_MENU_05A:
        case TIPO_ITEM_MENU_05B:
        case CIRCUITO_SELECCION_BATALLA_NOMBRES:
            cargar_menu_img_comp_tipo(segmentado_a_duplicado_virtual(menu_texturas_pista_seleccion[type - 0x52]),
                                    CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            break;
        case TIPO_ITEM_MENU_05F:
        case TIPO_ITEM_MENU_060:
        case TIPO_ITEM_MENU_061:
        case TIPO_ITEM_MENU_062:
            menu_item->d_8018DEE0_indice = seleccionar_menu_personaje_animar(
                segmentado_a_duplicado_virtual_2(dato_800E7E34[orden_circuito_copa[0][menu_item->type - 0x5F]]));
            break;
        case TIPO_ITEM_MENU_05E:
            menu_item->param2 = int_aleatorio(4) + 2;
            break;
        case TIPO_ITEM_MENU_065:
        case TIPO_ITEM_MENU_066:
            menu_item->column = dato_800E7248[type - 0x65].column;
            menu_item->row = dato_800E7248[type - 0x65].row;
            break;
        case TIPO_ITEM_MENU_067:
            menu_item->param1 = (s32) seleccion_copa;
            menu_item->param2 = funcion_800B54C0(seleccion_copa, seleccion_cc);
            menu_item->d_8018DEE0_indice = seleccionar_menu_personaje_animar(
                segmentado_a_duplicado_virtual_2(dato_800E7E20[((seleccion_cc / 2) * 4) - menu_item->param2]));
            menu_item->column = dato_800E7268[0].column;
            menu_item->row = dato_800E7268[0].row;
            break;
        case TIPO_ITEM_MENU_068:
            cargar_menu_img_comp_tipo(segmentado_a_duplicado_virtual(dato_800E8294[seleccion_cc]), CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            menu_item->column = 0x37;
            menu_item->row = 0xC3;
            break;
        case TIPO_ITEM_MENU_069:
            cargar_menu_img_comp_tipo(segmentado_a_duplicado_virtual(dato_02004A0C), CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            if (controller_pak_1_situacion() == 0) {
                funcion_800B6708();
            } else {
                dato_8018EE10[0].fantasma_datos_guardado = 0;
                dato_8018EE10[1].fantasma_datos_guardado = 0;
            }
            break;
        case TIPO_ITEM_MENU_078:
        case TIPO_ITEM_MENU_079:
        case TIPO_ITEM_MENU_07A:
        case TIPO_ITEM_MENU_07B:
            cargar_menu_img_comp_tipo(segmentado_a_duplicado_virtual(dato_800E82F4[type - 0x78]), CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            break;
        case TIPO_ITEM_MENU_08C:
            cargar_menu_img_comp_tipo(segmentado_a_duplicado_virtual(textura_datos_seg2), CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            if (controller_pak_1_situacion() == 0) {
                funcion_800B6708();
            } else {
                dato_8018EE10[0].fantasma_datos_guardado = 0;
                dato_8018EE10[1].fantasma_datos_guardado = 0;
            }
            break;
        case TIPO_ITEM_MENU_08D:
            cargar_img_menu(segmentado_a_duplicado_virtual(dato_02001FA4));
            break;
        case TIPO_ITEM_MENU_07C:
        case TIPO_ITEM_MENU_07D:
        case TIPO_ITEM_MENU_07E:
        case TIPO_ITEM_MENU_07F:
        case TIPO_ITEM_MENU_080:
        case TIPO_ITEM_MENU_081:
        case TIPO_ITEM_MENU_082:
        case TIPO_ITEM_MENU_083:
        case TIPO_ITEM_MENU_084:
        case TIPO_ITEM_MENU_085:
        case TIPO_ITEM_MENU_086:
        case TIPO_ITEM_MENU_087:
        case TIPO_ITEM_MENU_088:
        case TIPO_ITEM_MENU_089:
        case TIPO_ITEM_MENU_08A:
        case TIPO_ITEM_MENU_08B:
            cargar_menu_img_comp_tipo(
                segmentado_a_duplicado_virtual(dato_800E7D74[orden_circuito_copa[(menu_item->type - TIPO_ITEM_MENU_07C) / 4]
                                                                    [(menu_item->type - TIPO_ITEM_MENU_07C) % 4]]),
                CARGA_MENU_IMG_MIO0_UNA_VEZ);
            cargar_menu_img_comp_tipo(
                segmentado_a_duplicado_virtual(dato_800E7DC4[orden_circuito_copa[(menu_item->type - TIPO_ITEM_MENU_07C) / 4]
                                                                    [(menu_item->type - TIPO_ITEM_MENU_07C) % 4]]),
                CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            cargar_menu_img_comp_tipo(segmentado_a_duplicado_virtual(dato_02004A0C), CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            break;
        case TIPO_ITEM_MENU_0B1:
        case TIPO_ITEM_MENU_0B2:
        case TIPO_ITEM_MENU_0B3:
        case TIPO_ITEM_MENU_0B4: {
            bool variable_v1_3;
            SIN_USO s32 relleno2;
            s32 temporal_a3 = type - TIPO_ITEM_MENU_0B1;
            SIN_USO s32 relleno[0x3];
            temporal_a1 = dato_800EFD64[selecciones_personaje[type - TIPO_ITEM_MENU_0B1]];
            variable_v1_3 = false;
            switch (seleccion_modo) {
                case VERSUS:
                    if (gp_actual_carrera_puesto_por_id_jugador[type - TIPO_ITEM_MENU_0B1] != 0) {
                        variable_v1_3 = true;
                    }
                    break;
                case BATALLA:
                    if ((type - TIPO_ITEM_MENU_0B1) != indice_ganador_jugador) {
                        variable_v1_3 = true;
                    }
                    break;
                default:
                    break;
            }
            if (variable_v1_3) {
                variable_a0 = animacion_derrota_personaje[temporal_a1];
            } else {
                variable_a0 = dato_800E8320[temporal_a1];
            }
            menu_item->d_8018DEE0_indice = funcion_8009A478(segmentado_a_duplicado_virtual_2(variable_a0), temporal_a3);
            cargar_menu_img_comp_tipo(segmentado_a_duplicado_virtual(dato_800E7D54[temporal_a1]), CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            cargar_img_menu(segmentado_a_duplicado_virtual(menu_texturas_borde_jugador[type - TIPO_ITEM_MENU_0B1]));
            break;
        }
        case TIPO_ITEM_MENU_0BB:
            menu_item->param1 = funcion_800B5020(h_ud_jugador[0].algun_temporizador, selecciones_personaje[0]);
            menu_item->param2 = funcion_800B5218();
            if (b_jugador_fantasma_desactivado != 1) {
                if (funcion_800051C4() > 0x3C00) {
                    b_jugador_fantasma_desactivado = 1;
                }
            }
            if ((menu_item->param1 == 0) || (menu_item->param2 != 0)) {
                funcion_800B559C((seleccion_copa * 4) + indice_circuito_en_copa);
            }
            break;
        case MENU_ITEM_DATOS_CIRCUITO_IMAGEN:
            menu_item->d_8018DEE0_indice = seleccionar_menu_personaje_animar(segmentado_a_duplicado_virtual_2(
                dato_800E7E34[orden_circuito_copa[contrarreloj_indice_circuito_datos / 4][contrarreloj_indice_circuito_datos % 4]]));
            menu_item->param1 = contrarreloj_indice_circuito_datos;
            cargar_menu_img_comp_tipo(segmentado_a_duplicado_virtual(dato_02004A0C), CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            funcion_8006EF60();
            if (controller_pak_1_situacion() == 0) {
                funcion_800B6708();
            } else {
                dato_8018EE10[0].fantasma_datos_guardado = 0;
                dato_8018EE10[1].fantasma_datos_guardado = 0;
            }
            break;
        case TIPO_ITEM_MENU_0F0:
            menu_item->state = (s32) sonido_modo;
            break;
        case TIPO_ITEM_MENU_0F1:
            cargar_menu_img_comp_tipo(segmentado_a_duplicado_virtual(dato_02004638), CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            break;
        case TIPO_ITEM_MENU_0BE:
            dato_8018ED90 = 0;
            break;
        case TIPO_ITEM_MENU_130: {
            bool variable_v0_2;
            temporal_a1 = dato_800EFD64[dato_802874D8.desconocido_1e];
            if (dato_802874D8.desconocido_1d >= 3) {
                variable_v0_2 = true;
            } else {
                variable_v0_2 = false;
            }
            if (variable_v0_2) {
                variable_a0 = animacion_derrota_personaje[temporal_a1];
            } else {
                variable_a0 = dato_800E8320[temporal_a1];
            }
            menu_item->d_8018DEE0_indice = funcion_8009A478(segmentado_a_duplicado_virtual_2(variable_a0), 0);
            cargar_menu_img_comp_tipo(segmentado_a_duplicado_virtual(dato_800E7D54[temporal_a1]), CARGA_MENU_IMG_TKMK00_UNA_VEZ);
            break;
        }
        case TIPO_ITEM_MENU_190:
        case TIPO_ITEM_MENU_191:
        case TIPO_ITEM_MENU_192:
        case TIPO_ITEM_MENU_193:
        case TIPO_ITEM_MENU_194:
        case TIPO_ITEM_MENU_195:
        case TIPO_ITEM_MENU_196:
        case TIPO_ITEM_MENU_197:
        case TIPO_ITEM_MENU_198:
        case TIPO_ITEM_MENU_199:
        case TIPO_ITEM_MENU_19A:
        case TIPO_ITEM_MENU_19B:
        case TIPO_ITEM_MENU_19C:
        case TIPO_ITEM_MENU_19D:
        case TIPO_ITEM_MENU_19E:
        case TIPO_ITEM_MENU_19F:
        case TIPO_ITEM_MENU_1A0:
        case TIPO_ITEM_MENU_1A1:
        case TIPO_ITEM_MENU_1A2:
        case TIPO_ITEM_MENU_1A3:
        case TIPO_ITEM_MENU_1A4:
        case TIPO_ITEM_MENU_1A5:
        case TIPO_ITEM_MENU_1A6:
        case TIPO_ITEM_MENU_1A7:
        case TIPO_ITEM_MENU_1A8:
        case TIPO_ITEM_MENU_1A9:
        case TIPO_ITEM_MENU_1AA:
        case TIPO_ITEM_MENU_1AB:
        case TIPO_ITEM_MENU_1AC:
        case TIPO_ITEM_MENU_1AD:
        case TIPO_ITEM_MENU_1AE:
        case TIPO_ITEM_MENU_1AF:
        case TIPO_ITEM_MENU_1B0:
        case TIPO_ITEM_MENU_1B1:
        case TIPO_ITEM_MENU_1B2:
        case TIPO_ITEM_MENU_1B3:
        case TIPO_ITEM_MENU_1B4:
        case TIPO_ITEM_MENU_1B5:
        case TIPO_ITEM_MENU_1B6:
        case TIPO_ITEM_MENU_1B7:
        case TIPO_ITEM_MENU_1B8:
        case TIPO_ITEM_MENU_1B9:
        case TIPO_ITEM_MENU_1BA:
        case TIPO_ITEM_MENU_1BB:
        case TIPO_ITEM_MENU_1BC:
        case TIPO_ITEM_MENU_1BD:
        case TIPO_ITEM_MENU_1BE:
        case TIPO_ITEM_MENU_1BF:
        case TIPO_ITEM_MENU_1C0:
        case TIPO_ITEM_MENU_1C1:
        case TIPO_ITEM_MENU_1C2:
        case TIPO_ITEM_MENU_1C3:
        case TIPO_ITEM_MENU_1C4:
        case TIPO_ITEM_MENU_1C5:
        case TIPO_ITEM_MENU_1C6:
        case TIPO_ITEM_MENU_1C7:
        case TIPO_ITEM_MENU_1C8:
        case TIPO_ITEM_MENU_1C9:
        case TIPO_ITEM_MENU_1CA:
        case TIPO_ITEM_MENU_1CB:
        case TIPO_ITEM_MENU_1CC:
        case TIPO_ITEM_MENU_1CD:
        case TIPO_ITEM_MENU_1CE:
        default:
            break;
    }
}
