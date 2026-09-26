// Manejar menus

void manejar_menus_con_parametro_prio(s32 especial_prio) {
    s32 j;
    s32 es_renderizado;
    s32 i;
    s32 type;
    MenuItem* entry;

    for (i = 0; i < CANTIDAD_ARREGLO(menu_items); i++) {
        es_renderizado = false;
        entry = &menu_items[i];
        type = entry->type;
        if ((type == MENU_ITEM_IU_SIN_MANDO) || (type == MENU_ITEM_IU_INICIO_REGISTRO_TIEMPO) ||
            (type == PAUSA_ITEM_MENU)) {
            if (especial_prio != 0) {
                es_renderizado = true;
            }
        } else if (especial_prio == 0) {
            es_renderizado = true;
        }

        if (es_renderizado == false) {
            continue;
        }

        switch (type) {
            case MENU_ITEM_IU_LOGO_INTRO:
                if (temporizador_modelo_intro < 0x50) {
                    intro_modelo_rapidez = 3.0f;
                } else if (temporizador_modelo_intro < 0x5A) {
                    if (intro_modelo_movimiento_rapidez < 1.0) {
                        intro_modelo_movimiento_rapidez += 0.1;
                    }
                    intro_modelo_rapidez += 0.1;
                } else if (temporizador_modelo_intro < 0xA0) {
                    intro_modelo_rapidez += 0.1;
                } else if (temporizador_modelo_intro < 0x190) {
                    intro_modelo_rapidez += 0.3;
                }
                rot_y_modelo_intro -= intro_modelo_rapidez;
                temporizador_modelo_intro += 1;
                if (rot_y_modelo_intro < -360.0f) {
                    rot_y_modelo_intro += 360.0f;
                }
                entry->param1++;
                if (entry->param1 == 0x000000B4) {
                    funcion_8009E000(0x00000028);
                    funcion_800CA388(0x64U);
                    tipo_fundido_menu = MENU_FUNDIDO_TIPO_PRINCIPAL;
                }
                if ((entry->param2 != 0) && (entry->param1 >= 3)) {
                    entry->param2 = 0;
                    reproducir_sonido2(SONIDO_LOGO_INTRO);
                }
                break;
            case TIPO_ITEM_MENU_0DA:
                funcion_800A954C(entry);
                break;
            case TIPO_ITEM_MENU_0D6:
                funcion_800A9710(entry);
                break;
            case TIPO_ITEM_MENU_0D4:
                funcion_800A97BC(entry);
                break;
            case MENU_ITEM_IU_INICIO_REGISTRO_TIEMPO:
                switch (entry->state) {
                    case 0:
                        if (mando_cinco->button & R_TRIG) {
                            entry->state = (s32) 1U;
                            reproducir_sonido2(SONIDO_PING_ACCION);
                        } else {
                            entry->visible = 0;
                        }
                        break;
                    case 1:
                    default:
                        entry->visible = 1;
                        break;
                }
                break;
            case MENU_ITEM_IU_JUEGO_SELECCION:
                funcion_800AA280(entry);
                break;
            case MENU_PRINCIPAL_GFX_OPCION:
            case MENU_PRINCIPAL_GFX_DATOS:
                switch (menu_principal_seleccion) {
                    case MENU_PRINCIPAL_OPCION:
                    case MENU_PRINCIPAL_DATOS:
                    case MENU_PRINCIPAL_SELECCION_JUGADOR:
                        funcion_800A9B9C(entry);
                        break;
                    case MENU_PRINCIPAL_SELECCION_MODO:
                    case MENU_PRINCIPAL_SELECCION_SUB_MODO:
                    case MENU_PRINCIPAL_SELECCION_OK:
                    case MENU_PRINCIPAL_OK_SELECCION_IR_ATRAS:
                    case MENU_PRINCIPAL_MODO_SUB_SELECCION_IR_ATRAS:
                        funcion_800A9C40(entry);
                        break;
                }
                break;
            case MENU_ITEM_IU_OK:
                funcion_800AA280(entry);
                actualizar_item_menu_ok(entry);
                break;
            case MENU_ITEM_IU_1J_JUEGO:
            case MENU_ITEM_IU_2J_JUEGO:
            case MENU_ITEM_IU_3J_JUEGO:
            case MENU_ITEM_IU_4J_JUEGO:
                switch (menu_principal_seleccion) {
                    case MENU_PRINCIPAL_OPCION:
                    case MENU_PRINCIPAL_DATOS:
                    case MENU_PRINCIPAL_SELECCION_JUGADOR:
                        funcion_800A9B9C(entry);
                        break;
                    case MENU_PRINCIPAL_SELECCION_MODO:
                    case MENU_PRINCIPAL_SELECCION_SUB_MODO:
                    case MENU_PRINCIPAL_SELECCION_OK:
                    case MENU_PRINCIPAL_OK_SELECCION_IR_ATRAS:
                    case MENU_PRINCIPAL_MODO_SUB_SELECCION_IR_ATRAS:
                        funcion_800A9C40(entry);
                        break;
                }
                funcion_800A9D5C(entry);
                break;
            case MENU_PRINCIPAL_50CC:
            case MENU_PRINCIPAL_100CC:
            case MENU_PRINCIPAL_150CC:
            case MENU_PRINCIPAL_CC_EXTRA:
            case TIPO_ITEM_MENU_016:
            case TIPO_ITEM_MENU_017:
            case MENU_PRINCIPAL_CONTRARRELOJ_EMPEZAR:
            case MENU_PRINCIPAL_CONTRARRELOJ_DATOS:
                funcion_800A9E58(entry);
                break;
            case TIPO_ITEM_MENU_01B:
                funcion_800AA2EC(entry);
                break;
            case PERSONAJE_SELECCION_MENU_1J_CURSOR:
            case PERSONAJE_SELECCION_MENU_2J_CURSOR:
            case PERSONAJE_SELECCION_MENU_3J_CURSOR:
            case PERSONAJE_SELECCION_MENU_4J_CURSOR:
                actualizar_cursor(entry);
                break;
            case MENU_SELECCION_PERSONAJE_MARIO:
            case MENU_SELECCION_PERSONAJE_LUIGI:
            case MENU_SELECCION_PERSONAJE_TOAD:
            case MENU_SELECCION_PERSONAJE_PEACH:
            case MENU_SELECCION_PERSONAJE_YOSHI:
            case MENU_SELECCION_PERSONAJE_DK:
            case MENU_SELECCION_PERSONAJE_WARIO:
            case MENU_SELECCION_PERSONAJE_BOWSER:
                funcion_800AAC18(entry);
                switch (entry->type) {
                    case MENU_SELECCION_PERSONAJE_MARIO:
                    case MENU_SELECCION_PERSONAJE_LUIGI:
                    case MENU_SELECCION_PERSONAJE_TOAD:
                    case MENU_SELECCION_PERSONAJE_PEACH:
                    case MENU_SELECCION_PERSONAJE_YOSHI:
                    case MENU_SELECCION_PERSONAJE_DK:
                    case MENU_SELECCION_PERSONAJE_WARIO:
                    case MENU_SELECCION_PERSONAJE_BOWSER:
                        funcion_800AA69C(entry);
                        break;
                }
                switch (jugador_seleccion_menu_seleccion) {
                    case JUGADOR_SELECCION_MENU_PRINCIPAL:
                        funcion_800AAB90(entry);
                        break;
                    case JUGADOR_SELECCION_MENU_OK:
                    case JUGADOR_SELECCION_MENU_OK_IR_ATRAS:
                        funcion_800AAA9C(entry);
                        break;
                }
                funcion_800AAE18(entry);
                break;
            case PERSONAJE_SELECCION_MENU_OK:
            case OK_SELECCION_CIRCUITO:
                actualizar_item_menu_ok(entry);
                break;
            case SELECCION_CIRCUITO_COPA_HONGO:
            case SELECCION_CIRCUITO_COPA_FLOR:
            case SELECCION_CIRCUITO_COPA_ESTRELLA:
            case SELECCION_CIRCUITO_COPA_ESPECIAL:
                funcion_800AB164(entry);
                switch (seleccion_menu_sub) {
                    case SUB_MENU_MAPA_SELECCION_COPA:
                        funcion_800AB020(entry);
                        break;
                    case SUB_MENU_MAPA_SELECCION_CIRCUITO:
                    case SUB_MENU_MAPA_SELECCION_OK:
                        funcion_800AB098(entry);
                        break;
                }
                break;
            case TIPO_ITEM_MENU_058:
            case CIRCUITO_SELECCION_CIRCUITO_NOMBRES:
            case TIPO_ITEM_MENU_05A:
            case TIPO_ITEM_MENU_05B:
                funcion_800AB260(entry);
                break;
            case TIPO_ITEM_MENU_064:
                funcion_800AB314(entry);
                break;
            case TIPO_ITEM_MENU_05F:
            case TIPO_ITEM_MENU_060:
            case TIPO_ITEM_MENU_061:
            case TIPO_ITEM_MENU_062:
                funcion_800AB290(entry);
                break;
            case TIPO_ITEM_MENU_065:
            case TIPO_ITEM_MENU_066:
                funcion_800AB904(entry);
                break;
            case TIPO_ITEM_MENU_067:
                funcion_800AB9B0(entry);
                break;
            case TIPO_ITEM_MENU_078:
            case TIPO_ITEM_MENU_079:
            case TIPO_ITEM_MENU_07A:
            case TIPO_ITEM_MENU_07B:
            case TIPO_ITEM_MENU_08C:
                funcion_800ABAE8(entry);
                break;
            case TIPO_ITEM_MENU_08D:
                funcion_800ABB24(entry);
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
                funcion_800ABBCC(entry);
                break;
            case TIPO_ITEM_MENU_096:
                funcion_800ABC38(entry);
                break;
            case TIPO_ITEM_MENU_097:
                funcion_800ABEAC(entry);
                break;
            case TIPO_ITEM_MENU_05E:
                funcion_800AC300(entry);
                break;
            case TIPO_ITEM_MENU_0AA:
                funcion_800AC324(entry);
                break;
            case TIPO_ITEM_MENU_0AB:
                funcion_800AC458(entry);
                break;
            case TIPO_ITEM_MENU_0AC:
                funcion_800ACA14(entry);
                break;
            case TIPO_ITEM_MENU_0AF:
                funcion_800AC978(entry);
                break;
            case TIPO_ITEM_MENU_0B0:
                funcion_800ACC50(entry);
                break;
            case TIPO_ITEM_MENU_0B1:
            case TIPO_ITEM_MENU_0B2:
            case TIPO_ITEM_MENU_0B3:
            case TIPO_ITEM_MENU_0B4:
                funcion_800ACF40(entry);
                break;
            case TIPO_ITEM_MENU_0B9:
                funcion_800AD1A4(entry);
                break;
            case TIPO_ITEM_MENU_0BA:
                funcion_800AD2E8(entry);
                break;
            case MENU_ITEM_ANUNCIO_FANTASMA:
                funcion_800AEC54(entry);
                break;
            case PAUSA_ITEM_MENU:
                funcion_800ADF48(entry);
                break;
            case MENU_ITEM_FIN_CIRCUITO_OPCION:
                funcion_800AE218(entry);
                break;
            case MENU_ITEM_DATOS_CIRCUITO_IMAGEN:
                funcion_800AEDBC(entry);
                break;
            case MENU_ITEM_DATOS_CIRCUITO_SELECCIONABLE:
                funcion_800AEE90(entry);
                break;
            case TIPO_ITEM_MENU_0E9:
                funcion_800AEEBC(entry);
                break;
            case TIPO_ITEM_MENU_0EA:
                funcion_800AEEE8(entry);
                break;
            case TIPO_ITEM_MENU_0BE:
                funcion_800AEF14(entry);
                break;
            case TIPO_ITEM_MENU_10E:
                funcion_800AEF74(entry);
                break;
            case TIPO_ITEM_MENU_12B:
                funcion_800AF004(entry);
                break;
            case TIPO_ITEM_MENU_12C:
            case TIPO_ITEM_MENU_12D:
            case TIPO_ITEM_MENU_12E:
            case TIPO_ITEM_MENU_12F:
                funcion_800AF1AC(entry);
                break;
            case TIPO_ITEM_MENU_130:
                funcion_800AF270(entry);
                break;
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
                funcion_800AF480(entry);
                break;
            case MENU_ITEM_IU_NINGUNO:
            case MENU_ITEM_IU_INICIO_FONDO:
            case MENU_ITEM_IU_LOGO_Y_COPYRIGHT:
            case MENU_ITEM_IU_EMPUJE_INICIO_BOTON:
            case MENU_ITEM_IU_SIN_MANDO:
                break;
        }
    }

    for (j = 0; j < MENU_ITEM_PRIORIDAD_MAX; j++) {
        for (i = 0; i < CANTIDAD_ARREGLO(menu_items); i++) {
            es_renderizado = false;
            entry = &menu_items[i];
            if (entry && entry) {}
            type = entry->type;
            if ((type == MENU_ITEM_IU_SIN_MANDO) || (type == MENU_ITEM_IU_INICIO_REGISTRO_TIEMPO) ||
                (type == PAUSA_ITEM_MENU)) {
                if (especial_prio != 0) {
                    es_renderizado = true;
                }
            } else if (especial_prio == 0) {
                es_renderizado = true;
            }
            if ((es_renderizado != 0) && (j == (s8) entry->priority)) {
                renderizar_menus(entry);
            }
        }
    }
}

void manejar_predeterminado_menus(void) {
    manejar_menus_con_parametro_prio(0);
}

void manejar_especial_menus(void) {
    manejar_menus_con_parametro_prio(1);
}

void funcion_800A8270(s32 parametro0, MenuItem* parametro1) {
    s32 temporal_t1;
    s32 temporal_t6;
    s32 variable_s0;
    s32 variable_s2;
    s32 variable_s3;
    s32 variable_s4;

    if (parametro1->param1 < 0x20) {
        temporal_t6 = (parametro1->param1 << 6) / 64;
        temporal_t1 = parametro1->column;
        variable_s0 = parametro1->row;
        variable_s3 = temporal_t1 + temporal_t6;
        variable_s4 = (temporal_t1 - temporal_t6) + 0x3F;
        gDPPipeSync(display_list_cabeza++);
        gDPSetRenderMode(display_list_cabeza++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gDPSetCombineMode(display_list_cabeza++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        if ((parametro0 + 1) == cantidad_jugador) {
            if ((menu_principal_seleccion == MENU_PRINCIPAL_OPCION) || (menu_principal_seleccion == MENU_PRINCIPAL_DATOS) ||
                (menu_principal_seleccion == MENU_PRINCIPAL_SELECCION_JUGADOR)) {
                display_list_cabeza = seleccionar_lento_case_destello_dibujo(display_list_cabeza, variable_s3, variable_s0, variable_s4, variable_s0 + 0x35);
            } else {
                display_list_cabeza = dibujar_relleno_caja(display_list_cabeza, variable_s3, variable_s0, variable_s4, variable_s0 + 0x35, 0x000000FF,
                                                 0x000000F9, 0x000000DC, 0x000000FF);
            }
        } else {
            display_list_cabeza = funcion_80098FC8(display_list_cabeza, variable_s3, variable_s0, variable_s4, variable_s0 + 0x35);
        }
        for (variable_s0 += 0x41, variable_s2 = 0; variable_s2 <= seleccion_modo_jugador[parametro0]; variable_s2++, variable_s0 += 0x12) {
            if ((variable_s2 == juego_modo_menu_columna[parametro0]) && ((parametro0 + 1) == cantidad_jugador) &&
                (menu_principal_seleccion > MENU_PRINCIPAL_SELECCION_JUGADOR)) {
                if (menu_principal_seleccion == MENU_PRINCIPAL_SELECCION_MODO) {
                    display_list_cabeza =
                        seleccionar_lento_case_destello_dibujo(display_list_cabeza, variable_s3, variable_s0, variable_s4, variable_s0 + 0x11);
                } else {
                    display_list_cabeza = dibujar_relleno_caja(display_list_cabeza, variable_s3, variable_s0, variable_s4, variable_s0 + 0x11,
                                                     0x000000FF, 0x000000F9, 0x000000DC, 0x000000FF);
                }
            } else {
                display_list_cabeza =
                    dibujar_relleno_caja(display_list_cabeza, variable_s3, variable_s0, variable_s4, variable_s0 + 0x11, 1, 1, 1, 0x000000FF);
            }
        }
    }
}

void funcion_800A8564(MenuItem* parametro0) {
    s32 sp34;
    s32 variable_a1;
    TexturaMenu* variable_a0;
    s32 temporal_a2;
    s32 temporal_t0;

    variable_a1 = 0;
    switch (parametro0->type) { /* irregular */
        case 0xF:
            variable_a0 = dato_0200487C;
            if ((menu_principal_seleccion == MENU_PRINCIPAL_SELECCION_OK) || (menu_principal_seleccion == MENU_PRINCIPAL_OK_SELECCION_IR_ATRAS)) {
                variable_a1 = 1;
            }
            break;
        case 0x33:
            variable_a0 = dato_02004B74;
            if ((jugador_seleccion_menu_seleccion == JUGADOR_SELECCION_MENU_OK) ||
                (jugador_seleccion_menu_seleccion == JUGADOR_SELECCION_MENU_OK_IR_ATRAS)) {
                variable_a1 = 1;
            }
            break;
        case 0x5D:
            variable_a0 = dato_02004E80;
            if (seleccion_menu_sub == SUB_MENU_MAPA_SELECCION_OK) {
                variable_a1 = 1;
            }
            break;
        default:
            return;
    }
    if (parametro0->param1 < 0x20) {
        sp34 = (parametro0->param1 << 5) / 64;
        variable_a0 = segmentado_a_duplicado_virtual(variable_a0);
        temporal_t0 = parametro0->column + variable_a0->d_x;
        temporal_a2 = parametro0->row + variable_a0->d_y;
        if (variable_a1 != 0) {
            display_list_cabeza = seleccionar_lento_case_destello_dibujo(display_list_cabeza, temporal_t0 + sp34, temporal_a2,
                                                           (temporal_t0 - sp34) + 0x1E, temporal_a2 + 0x12);
        } else {
            display_list_cabeza = dibujar_relleno_caja(display_list_cabeza, temporal_t0 + sp34, temporal_a2, (temporal_t0 - sp34) + 0x1E,
                                             temporal_a2 + 0x12, 1, 1, 1, 0x000000FF);
        }
    }
}

void funcion_800A86E8(MenuItem* parametro0) {
    display_list_cabeza =
        dibujar_relleno_caja(display_list_cabeza, parametro0->column, parametro0->row, parametro0->column + 0x64, parametro0->row + 0x27, 1, 1, 1, 0xFF);
}

void funcion_800A874C(MenuItem* parametro0) {
    SIN_USO s32 margen_pila_0;
    char buffer[3];
    SIN_USO s32 margen_pila_1;
    SIN_USO s32 margen_pila_2;
    s32 temporal_s1;
    SIN_USO u32 variable_v0;
    u32 variable_s2;
    fijar_color_texto(VERDE_TEXTO);
    variable_s2 = parametro0->type == TIPO_ITEM_MENU_065 ? funcion_800B4E24(0) : funcion_800B4F2C();
    temporal_s1 = variable_s2 & 0xFFFFF;
    obtener_minutos_registro_tiempo((temporal_s1 ^ 0), buffer);
    dibujar_texto(parametro0->column + 5, parametro0->row + 0x21, buffer, 0, 0.6f, 0.65f);
    imprimir_modo_texto_1(parametro0->column + 0xE, parametro0->row + 0x21, "'", 0, 0.6f, 0.65f);
    obtener_segundos_registro_tiempo(temporal_s1, buffer);
    dibujar_texto(parametro0->column + 0x16, parametro0->row + 0x21, buffer, 0, 0.6f, 0.65f);
    imprimir_modo_texto_1(parametro0->column + 0x20, parametro0->row + 0x21, "\"", 0, 0.6f, 0.65f);
    obtener_centesimas_registro_tiempo(temporal_s1, buffer);
    dibujar_texto(parametro0->column + 0x29, parametro0->row + 0x21, buffer, 0, 0.6f, 0.65f);
    variable_s2 = (u32) temporal_s1 < 0x927C0U ? variable_s2 >> 0x14 : 8;
    imprimir_izquierda_texto1(parametro0->column + 0x60, parametro0->row + 0x21, dato_800E76A8[variable_s2], 0, 0.6f, 0.65f);
}

void funcion_800A890C(s32 parametro0, MenuItem* parametro1) {
    s32 temporal_a2;
    s32 temporal_t1;
    s32 temporal_t7;

    if (parametro1->param1 < 32) {
        if (1) {}
        temporal_t7 = (parametro1->param1 * 65) / 64;
        temporal_t1 = parametro1->column;
        temporal_a2 = parametro1->row;
        gDPPipeSync(display_list_cabeza++);
        gDPSetRenderMode(display_list_cabeza++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gDPSetCombineMode(display_list_cabeza++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        if (parametro0 == seleccion_copa) {
            if (seleccion_menu_sub == SUB_MENU_MAPA_SELECCION_COPA) {
                display_list_cabeza = seleccionar_lento_case_destello_dibujo(display_list_cabeza, temporal_t1 + temporal_t7, temporal_a2,
                                                               (temporal_t1 - temporal_t7) + 64, temporal_a2 + 39);
            } else {
                display_list_cabeza = dibujar_relleno_caja(display_list_cabeza, temporal_t1 + temporal_t7, temporal_a2, (temporal_t1 - temporal_t7) + 64,
                                                 temporal_a2 + 39, 255, 249, 220, 255);
            }
        } else {
            display_list_cabeza = dibujar_relleno_caja(display_list_cabeza, temporal_t1 + temporal_t7, temporal_a2, (temporal_t1 - temporal_t7) + 64,
                                             temporal_a2 + 39, 1, 1, 1, 255);
        }
    }
}

void funcion_800A8A98(MenuItem* parametro0) {
    s32 temporal_s2;
    s32 temporal_s3;
    s32 algun_indice;

    temporal_s2 = parametro0->column;
    temporal_s3 = parametro0->row;
    gDPPipeSync(display_list_cabeza++);
    gDPSetRenderMode(display_list_cabeza++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCombineMode(display_list_cabeza++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    for (algun_indice = 0; algun_indice < CIRCUITOS_NUM_POR_COPA; algun_indice++) {
        if ((algun_indice == indice_circuito_en_copa) && (seleccion_menu_sub > SUB_MENU_MAPA_SELECCION_COPA) &&
            (seleccion_modo != GRAN_PREMIO)) {
            if ((seleccion_menu_sub == SUB_MENU_MAPA_SELECCION_CIRCUITO) ||
                (seleccion_menu_sub == SUB_MENU_MAPA_SELECCION_BATALLA_CIRCUITO)) {
                display_list_cabeza = seleccionar_lento_case_destello_dibujo(
                    display_list_cabeza, dato_800E7208[algun_indice][0].column + temporal_s2, dato_800E7208[algun_indice][0].row + temporal_s3,
                    dato_800E7208[algun_indice][1].column + temporal_s2, dato_800E7208[algun_indice][1].row + temporal_s3);
            } else {
                display_list_cabeza = dibujar_relleno_caja(
                    display_list_cabeza, dato_800E7208[algun_indice][0].column + temporal_s2, dato_800E7208[algun_indice][0].row + temporal_s3,
                    dato_800E7208[algun_indice][1].column + temporal_s2, dato_800E7208[algun_indice][1].row + temporal_s3, 0x000000FF,
                    0x000000F9, 0x000000DC, 0x000000FF);
            }
        } else {
            display_list_cabeza = dibujar_relleno_caja(
                display_list_cabeza, dato_800E7208[algun_indice][0].column + temporal_s2, dato_800E7208[algun_indice][0].row + temporal_s3,
                dato_800E7208[algun_indice][1].column + temporal_s2, dato_800E7208[algun_indice][1].row + temporal_s3, 1, 1, 1, 0x000000FF);
        }
    }
}

void funcion_800A8CA4(MenuItem* parametro0) {
    s32 temporal_s2;
    s32 temporal_s3;
    s32 variable_s0;
    MenuItem* temporal_v0;

    temporal_v0 = buscar_duplicado_items_menu(TIPO_ITEM_MENU_064);
    temporal_s2 = parametro0->column;
    temporal_s3 = parametro0->row;
    gDPPipeSync(display_list_cabeza++);
    gDPSetRenderMode(display_list_cabeza++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCombineMode(display_list_cabeza++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    if (seleccion_modo == GRAN_PREMIO) {
        if (seleccion_menu_sub != SUB_MENU_MAPA_SELECCION_OK) {
            for (variable_s0 = 0; variable_s0 < 4; variable_s0++) {
                if ((variable_s0 != (temporal_v0->param1 % 4)) != 0) {
                    display_list_cabeza =
                        dibujar_caja(display_list_cabeza, dato_800E7208[variable_s0][0].column + temporal_s2,
                                 dato_800E7208[variable_s0][0].row + temporal_s3, dato_800E7208[variable_s0][1].column + temporal_s2,
                                 dato_800E7208[variable_s0][1].row + temporal_s3, 0, 0, 0, 0x00000064);
                }
            }
        }
    }
}

void renderizar_introduccion_batalla(SIN_USO MenuItem* parametro0) {
    fijar_color_texto(AMARILLO_TEXTO);
    imprimir_modo_centro_texto1_1(0x98, 0x44, introduccion_batalla_texto[0], 0, 1.0f, 1.0f);
    imprimir_modo_texto_1(0x17, 0x58, introduccion_batalla_texto[1], 0, 0.7f, 0.8f);
    imprimir_modo_texto_1(0x17, 0x6A, introduccion_batalla_texto[2], 0, 0.7f, 0.8f);
}

void funcion_800A8EC0(MenuItem* parametro0) {
    if (parametro0->param2 != 0) {
        funcion_8009A76C(parametro0->d_8018DEE0_indice, parametro0->column, parametro0->row, -1);
        fijar_color_texto(AMARILLO_TEXTO);
        imprimir_modo_texto_1(parametro0->column + 0x20, parametro0->row + 0x28, texto_copa[parametro0->param2], 0, 0.7f, 0.7f);
    }
}

void funcion_800A8F48(SIN_USO MenuItem* parametro0) {
    SIN_USO Gfx* temporal_v0_2;
    desconocido_d_800E70A0* temporal_v0;
    s16 temporal_s0;
    s16 temporal_v1;
    s32 temporal_s2;
    s32 variable_s1;

    switch (seleccion_menu_sub) { /* irregular */
        case SUB_MENU_MAPA_SELECCION_COPA:
            for (variable_s1 = 0; variable_s1 < 4; variable_s1++) {
                if (funcion_800B639C((seleccion_copa * 4) + variable_s1) >= 0) {
                    temporal_v0 = &dato_800E7168[variable_s1];
                    temporal_v1 = temporal_v0->column;
                    temporal_s0 = temporal_v0->row;
                    temporal_s2 = temporal_v1 + 0x20;
                    display_list_cabeza =
                        funcion_80098FC8(display_list_cabeza, temporal_s2, (s32) temporal_s0, temporal_v1 + 0x3F, temporal_s0 + 9);
                    display_list_cabeza = funcion_8009C204(display_list_cabeza, segmentado_a_duplicado_virtual(dato_02004A0C), temporal_s2,
                                                     (s32) temporal_s0, 2);
                }
            }
            break;
        case SUB_MENU_MAPA_SELECCION_CIRCUITO:
        default:
            if (funcion_800B639C((seleccion_copa * 4) + indice_circuito_en_copa) >= 0) {
                display_list_cabeza = funcion_80098FC8(display_list_cabeza, 0x00000057, 0x00000070, 0x00000096, 0x00000081);
                display_list_cabeza = renderizar_texturas_menu(display_list_cabeza, dato_02004A0C, 0x00000057, 0x00000070);
            }
            break;
    }
}

void funcion_800A90D4(SIN_USO s32 parametro0, MenuItem* parametro1) {
    s32 temporal_a2;
    s32 temporal_t1;
    s32 temporal_t7;

    if (parametro1->param1 < 0x20) {
        if (1) {}
        temporal_t7 = (parametro1->param1 * 0x41) / 0x40;
        temporal_t1 = parametro1->column;
        temporal_a2 = parametro1->row;
        gDPPipeSync(display_list_cabeza++);
        gDPSetRenderMode(display_list_cabeza++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gDPSetCombineMode(display_list_cabeza++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        display_list_cabeza = dibujar_relleno_caja(display_list_cabeza, temporal_t1 + temporal_t7, temporal_a2, (temporal_t1 - temporal_t7) + 0x40,
                                         temporal_a2 + 0x27, 1, 1, 1, 0xFF);
    }
}

void funcion_800A91D8(MenuItem* parametro0, s32 objetivo_columna, s32 objetivo_renglon) {
    funcion_800A9208(parametro0, objetivo_columna);
    funcion_800A9278(parametro0, objetivo_renglon);
}

void funcion_800A9208(MenuItem* parametro0, s32 objetivo_columna) {
    s32 paso = objetivo_columna - parametro0->column;

    if (paso != 0) {
        if (paso > 0) {
            paso = (paso / 4) + 1;
            if (paso >= 0x11) {
                paso = 0x10;
            }
        } else {
            paso = (paso / 4) - 1;
            if (paso < -0x10) {
                paso = -0x10;
            }
        }
    }
    parametro0->column += paso;
}

void funcion_800A9278(MenuItem* parametro0, s32 objetivo_renglon) {
    s32 paso = objetivo_renglon - parametro0->row;

    if (paso != 0) {
        if (paso > 0) {
            paso = (paso / 4) + 1;
            if (paso >= 0x11) {
                paso = 0x10;
            }
        } else {
            paso = (paso / 4) - 1;
            if (paso < -0x10) {
                paso = -0x10;
            }
        }
    }
    parametro0->row += paso;
}

void funcion_800A92E8(MenuItem* parametro0, s32 objetivo_columna) {
    s32 paso = objetivo_columna - parametro0->column;

    if (paso != 0) {
        if (paso > 0) {
            paso = (paso / 4) + 1;
            if (paso >= 0x11) {
                paso = 0x10;
            }
            if (paso < 8) {
                paso = 8;
            }
            parametro0->column += paso;
            if (objetivo_columna < parametro0->column) {
                parametro0->column = objetivo_columna;
            }
        } else {
            paso = (paso / 4) - 1;
            if (paso < -0x10) {
                paso = -0x10;
            }
            if (paso < -8) {
                paso = -8;
            }
            parametro0->column += paso;
            if (parametro0->column < objetivo_columna) {
                parametro0->column = objetivo_columna;
            }
        }
    }
}

SIN_USO void funcion_800A939C(MenuItem* parametro0, s32 objetivo_renglon) {
    s32 paso = objetivo_renglon - parametro0->row;

    if (paso != 0) {
        if (paso > 0) {
            paso = (paso / 4) + 1;
            if (paso >= 0x11) {
                paso = 0x10;
            }
        } else {
            paso = (paso / 4) - 1;
            if (paso < -0x10) {
                paso = -0x10;
            }
        }
    }
    parametro0->row += paso;
}

void funcion_800A940C(MenuItem* parametro0, s32 objetivo_columna) {
    s32 paso = objetivo_columna - parametro0->column;

    if (paso != 0) {
        paso = 0xC8 / paso;
        if (paso > 0) {
            if (paso >= 0x19) {
                paso = 0x18;
            }
            if (paso < 0x10) {
                paso = 0x10;
            }
            parametro0->column += paso;
            if (objetivo_columna < parametro0->column) {
                parametro0->column = objetivo_columna;
            }
        } else {
            if (paso < -0x18) {
                paso = -0x18;
            }
            if (paso >= -0xF) {
                paso = -0x10;
            }
            parametro0->column += paso;
            if (parametro0->column < objetivo_columna) {
                parametro0->column = objetivo_columna;
            }
        }
    }
}

void funcion_800A94C8(MenuItem* parametro0, s32 objetivo_columna, s32 parametro2) {
    s32 paso;

    if (objetivo_columna == parametro0->column) {
        parametro0->column += parametro2;
    } else {
        paso = objetivo_columna - parametro0->column;
        if (paso != 0) {
            if (paso > 0) {
                paso = (paso / 4) + 1;
                if (paso >= 0x11) {
                    paso = 0x10;
                }
            } else {
                paso = (paso / 4) - 1;
                if (paso < -0x10) {
                    paso = -0x10;
                }
            }
        }
        parametro0->column -= paso;
    }
}

void funcion_800A954C(MenuItem* parametro0) {
    if (parametro0->state == 0) {
        parametro0->param2 = (s32) (u32) ((((f32) (0xC - parametro0->param1) * 127.0f) / 12.0f) + 128.0f);
    } else {
        parametro0->param2 = (s32) (u32) ((((f64) (f32) parametro0->param1 * 127.0) / 12.0) + 128.0);
    }
    parametro0->param1++;
    if (parametro0->param1 >= 0xC) {
        parametro0->param1 = 0;
        parametro0->state ^= 1;
    }
}

void funcion_800A9710(MenuItem* parametro0) {
    s32 phi_v0;

    switch (controller_pak_seleccion_menu) {
        case CONTROLLER_PAK_BORRAR_MENU:
        case CONTROLLER_PAK_ABANDONAR_MENU:
            phi_v0 = 1;
            break;
        case CONTROLLER_PAK_IR_MENU_A_BORRANDO:
        case CONTROLLER_PAK_BORRANDO_MENU:
            phi_v0 = 5;
            break;
        case CONTROLLER_PAK_ERROR_BORRAR_MENU_NO_BORRADO:
            phi_v0 = 2;
            break;
        case CONTROLLER_PAK_MENU_BORRAR_ERROR_SIN_PAK:
            phi_v0 = 3;
            break;
        case CONTROLLER_PAK_MENU_BORRAR_ERROR_PAK_CAMBIADO:
            phi_v0 = 4;
            break;
        default:
            phi_v0 = 0;
            break;
    }
    if (phi_v0 != parametro0->state) {
        parametro0->state = phi_v0;
        funcion_8009A594(parametro0->d_8018DEE0_indice, 0, segmentado_a_duplicado_virtual_2(dato_800E7D34[phi_v0]));
    }
}
