// Tablas menus

#if MODO_DEPURACION_ACTIVACION
#define ALTERNAR_MODO_DEPURACION true
#define SELECCION_MENU_DEPURACION DEPURACION_MENU_DEPURACION_MODO
#else
#define ALTERNAR_MODO_DEPURACION false
#define SELECCION_MENU_DEPURACION DEPURACION_MENU_DESACTIVADO
#endif

s32 ojo_modelo_z_intro;
f32 escala_modelo_intro;
f32 rot_x_modelo_intro;
f32 rot_y_modelo_intro;
f32 rot_z_modelo_intro;
f32 pos_x_modelo_intro;
f32 pos_y_modelo_intro;
f32 pos_z_modelo_intro;

s32 tipo_fundido_menu;
s8 selecciones_cuadricula_personaje[4];
bool8 personaje_cuadricula_es_seleccionado[4];
s8 seleccion_menu_sub;
s8 menu_principal_seleccion;
s8 jugador_seleccion_menu_seleccion;
s8 seleccion_menu_depuracion;
s8 controller_pak_seleccion_menu;
s8 pantalla_modo_lista_indice;
u8 sonido_modo;
s8 cantidad_jugador;
s8 versus_seleccion_cursor_resultado;
s8 contrarreloj_seleccion_cursor_resultado;
s8 batalla_resultado_cursor_seleccion;
s8 contrarreloj_indice_circuito_datos;
s8 circuito_registros_menu_seleccion;
s8 circuito_registros_sub_menu_seleccion;
s8 escena_goto_depuracion;
bool8 inicializacion_jugador_fantasma;
bool8 inicializacion_mapa_circuito;
s32 contador_tiempos_menu;
s32 temporizador_retardo_menu;
s8 mando_usar_demo;
s8 seleccion_copa;
s8 seleccion_copa_temporal;
s8 indice_circuito_en_copa;
s8 sin_ref_8018EE0C;

s32 seleccion_menu = LOGO_INTRO_MENU;
s32 seleccion_modo_fundido = NINGUNO_MODO_FUNDIDO;

s8 selecciones_personaje[4] = { MARIO, LUIGI, YOSHI, TOAD };

s8 juego_modo_menu_columna[4] = { 0, 0, 0, 0 };

s8 juego_modo_sub_menu_columna[4][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };

s8 id_demo_siguiente = 0;
s8 controller_pak_renglon_tabla_seleccionado = 0;

s8 controller_pak_renglones_tabla_visible[12] = { 0, 0, 1, 2, 3, 4, 5, 6, 0, 0, 0, 0 };

s8 controller_pak_sentido_desplazamiento = CONTROLLER_PAK_NINGUNO_DIR_DESPLAZAMIENTO;
s8 sin_ref_d_800E86D4[12] = { 0 };
s8 sin_ref_d_800E86E0[4] = { 0, 0, 0, 1 };

u32 vi_gamma_apagado_tramar_en = (OS_VI_GAMMA_OFF | OS_VI_DITHER_FILTER_ON);

const s8 pantalla_modo_jugador_tabla[] = { MODO_PANTALLA_1P, PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL,
                                      PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL, PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA,
                                      PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA };

const s8 pantalla_modo_jugador_cantidad[] = { 1, 2, 2, 3, 4 };

const s8 seleccion_modo_jugador[] = { 1, 2, 1, 1 };

const s8 juego_modo_jugador_columna_predeterminado[][3] = {
    { 2, 1, 0 },
    { 2, 2, 0 },
    { 2, 0, 0 },
    { 2, 0, 0 },
};

const s8 juego_modo_jugador_columna_extra[][3] = {
    { 3, 1, 0 },
    { 3, 3, 0 },
    { 3, 0, 0 },
    { 3, 0, 0 },
};

const s32 juego_modo_jugador_seleccion[][3] = {
    { GRAN_PREMIO, CONTRARRELOJ, 0x00000000 },
    { GRAN_PREMIO, VERSUS, BATALLA },
    { VERSUS, BATALLA, 0x00000000 },
    { VERSUS, BATALLA, 0x00000000 },
};

const s8 orden_cuadricula_personaje[] = {
    MARIO, LUIGI, PEACH, TOAD, YOSHI, DK, WARIO, BOWSER,
};

const s16 orden_circuito_copa[5][4] = {
    { CIRCUITO_LUIGI_RACEWAY, CIRCUITO_MOO_MOO_FARM, CIRCUITO_KOOPA_BEACH, CIRCUITO_KALAMARI_DESERT },
    // flower cup
    { CIRCUITO_TOADS_TURNPIKE, CIRCUITO_FRAPPE_SNOWLAND, CIRCUITO_CHOCO_MOUNTAIN, CIRCUITO_MARIO_RACEWAY },
    // star cup
    { CIRCUITO_WARIO_STADIUM, CIRCUITO_SHERBET_LAND, CIRCUITO_ROYAL_RACEWAY, CIRCUITO_BOWSER_CASTLE },
    { CIRCUITO_DK_JUNGLE, CIRCUITO_YOSHI_VALLEY, CIRCUITO_BANSHEE_BOARDWALK, CIRCUITO_RAINBOW_ROAD },
    { CIRCUITO_BIG_DONUT, CIRCUITO_BLOCK_FORT, CIRCUITO_DOUBLE_DECK, CIRCUITO_SKYSCRAPER },
};

const s8 sin_ref_800F2BDC[4] = { 1, 0, 0, 0 };

const s8 idx_modo_pantalla_desde_modo_jugador[4] = { 0, 1, 3, 4 };

const union PaqueteModoJuego sonido_paquete_menu = { { SONIDO_ESTEREO, SONIDO_AURICULARES, SONIDO_SIN_USO, SONIDO_MONO } };

void actualizar_menus(void) {
    u16 idx_mando;

    if (seleccion_modo_fundido == NINGUNO_MODO_FUNDIDO) {
        for (idx_mando = 0; idx_mando < 4; idx_mando++) {
            if ((es_pantalla_siendo_fundido() == 0) && (modo_depuracion_activacion) &&
                ((mandos[idx_mando].boton_pulsado & START_BUTTON) != 0)) {
                switch (seleccion_menu) {
                    case MENU_SELECCION_CIRCUITO:
                        funcion_800CA330(0x19);
                    case MENU_PRINCIPAL:
                    case MENU_SELECCION_PERSONAJE:
                        reproducir_sonido2(SONIDO_MENU_OK_CLICKED);
                        break;
                }

                switch (seleccion_menu) {
                    case CONTROLLER_PAK_MENU:
                    case MENU_INICIO:
                        break;
                    default:
                        funcion_8009E1C0();
                }
            }
            osViSetSpecialFeatures(vi_gamma_apagado_tramar_en);
            switch (seleccion_menu) {
                case MENU_OPCIONES:
                    act_menu_opciones(&mandos[idx_mando], idx_mando);
                    break;
                case MENU_DATOS:
                    act_menu_datos(&mandos[idx_mando], idx_mando);
                    break;
                case MENU_DATOS_CIRCUITO:
                    circuito_datos_menu_act(&mandos[idx_mando], idx_mando);
                    break;
                case LOGO_INTRO_MENU:
                    logo_intro_menu_act(&mandos[idx_mando], idx_mando);
                    break;
                case CONTROLLER_PAK_MENU:
                    if (idx_mando == JUGADOR_UNO) {
                        controller_pak_act_menu(&mandos[idx_mando], idx_mando);
                    }
                    break;
                case MENU_INICIO_DESDE_ABANDONAR:
                case MENU_INICIO:
                    act_menu_salpicadura(&mandos[idx_mando], idx_mando);
                    break;
                case MENU_PRINCIPAL_DESDE_ABANDONAR:
                case MENU_PRINCIPAL:
                    menu_principal_act(&mandos[idx_mando], idx_mando);
                    break;
                case MENU_SELECCION_JUGADOR_DESDE_ABANDONAR:
                case MENU_SELECCION_PERSONAJE:
                    seleccionar_act_menu_jugador(&mandos[idx_mando], idx_mando);
                    break;
                case MENU_SELECCION_CIRCUITO_DESDE_ABANDONAR:
                case MENU_SELECCION_CIRCUITO:
                    seleccionar_act_menu_circuito(&mandos[idx_mando], idx_mando);
                    break;
            }
        }
    }
}

void act_menu_opciones(struct Mando* mando, u16 idx_mando) {
    u16 boton_y_palanca;
    MenuItem* sp38;
    s32 res;
    struct_8018EE10_entrada* sp30;
    bool variable_temporal;
    SIN_USO u32 relleno;

    boton_y_palanca = (mando->boton_pulsado | mando->palanca_pulsado);

    if (!modo_depuracion_activacion && (boton_y_palanca & START_BUTTON)) {
        boton_y_palanca |= A_BUTTON;
    }

    if (!es_pantalla_siendo_fundido()) {
        sp38 = buscar_duplicado_items_menu(0xF0);
        sp30 = (struct_8018EE10_entrada*) algun_buffer_dl;
        switch (seleccion_menu_sub) {
            case SUB_MENU_OPCION_RETORNO_JUEGO_SELECCION:
            case SUB_MENU_OPCION_SONIDO_MODO:
            case SUB_MENU_OPCION_COPIA_CONTROLLER_PAK:
            case SUB_MENU_OPCION_BORRAR_TODOS_DATOS: {
                variable_temporal = false;
                if ((boton_y_palanca & D_JPAD) && (seleccion_menu_sub < SUB_MENU_OPCION_MAX)) {
                    seleccion_menu_sub += 1;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (sp38->paramf < 4.2) {
                        sp38->paramf += 4.0;
                    }
                    sp38->estado_sub = 1;
                    variable_temporal = true;
                }
                if ((boton_y_palanca & U_JPAD) && (seleccion_menu_sub > SUB_MENU_OPCION_MIN)) {
                    seleccion_menu_sub -= 1;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (sp38->paramf < 4.2) {
                        sp38->paramf += 4.0;
                    }
                    variable_temporal = true;
                    sp38->estado_sub = -1;
                }
                if (variable_temporal && sonido_modo != sp38->state) {
                    datos_guardado.main.info_guardado.sonido_modo = sonido_modo;
                    guardar_datos_gran_premio_puntos_y_modo_sonido_escritura();
                    guardar_respaldo_datos_actualizacion();
                    sp38->state = sonido_modo;
                }
                if (boton_y_palanca & B_BUTTON) {
                    funcion_8009E280();
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    if (sonido_modo != sp38->state) {
                        datos_guardado.main.info_guardado.sonido_modo = sonido_modo;
                        guardar_datos_gran_premio_puntos_y_modo_sonido_escritura();
                        guardar_respaldo_datos_actualizacion();
                        sp38->state = sonido_modo;
                    }
                    return;
                }
                if (boton_y_palanca & A_BUTTON) {
                    switch (seleccion_menu_sub) {
                        case SUB_MENU_OPCION_SONIDO_MODO:
                            if (sonido_modo < 3) {
                                sonido_modo += 1;
                            } else {
                                sonido_modo = SONIDO_ESTEREO;
                            }
                            if (sonido_modo == SONIDO_SIN_USO) {
                                sonido_modo = SONIDO_MONO;
                            }
                            fijar_modo_sonido();
                            switch (sonido_modo) {
                                case SONIDO_ESTEREO:
                                    reproducir_sonido2(SONIDO_ESTEREO_MENU);
                                    return;
                                case SONIDO_AURICULARES:
                                    reproducir_sonido2(SONIDO_AURICULARES_MENU);
                                    return;
                                case SONIDO_MONO:
                                    reproducir_sonido2(SONIDO_MONO_MENU);
                                    return;
                            }
                            break;
                        case SUB_MENU_OPCION_COPIA_CONTROLLER_PAK:
                            switch (controller_pak_2_situacion()) {
                                case DATOS_INVALIDO_PFS:
                                    seleccion_menu_sub = SUB_MENU_COPIA_PAK_ERROR_SIN_JUEGO_DATOS;
                                    reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                                    return;
                                case ERROR_SIN_PFS:
                                    funcion_800B6798();
                                    variable_temporal = controller_pak_1_situacion();
                                    switch (variable_temporal) {
                                        case DATOS_INVALIDO_PFS:
                                            seleccion_menu_sub = SUB_MENU_COPIA_PAK_CREAR_JUEGO_DATOS_INICIALIZACION;
                                            sp38->state = 0;
                                            reproducir_sonido2(SONIDO_SELECCION_MENU);
                                            break;
                                        case ERROR_SIN_PFS:
                                            funcion_800B6708();
                                            break;
                                        case PFS_SIN_PAK_INSERTADO:
                                            seleccion_menu_sub = SUB_MENU_COPIA_PAK_ERROR_SIN_PAK_1P;
                                            reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                                            break;
                                        case DESBORDE_ARCHIVO_PFS:
                                            seleccion_menu_sub = SUB_MENU_COPIA_PAK_ERROR_SIN_PAGINAS_1P;
                                            reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                                            break;
                                        case PFS_PAK_MALO_LECTURA:
                                        case PFS_PAK_CORRUPTO:
                                        default:
                                            seleccion_menu_sub = SUB_MENU_COPIA_PAK_ERROR_MALO_LECTURA_1P;
                                            reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                                            break;
                                    }
                                    if (variable_temporal == DATOS_INVALIDO_PFS && !sp30[JUGADOR_UNO].fantasma_datos_guardado &&
                                        !sp30[JUGADOR_DOS].fantasma_datos_guardado) {
                                        seleccion_menu_sub = SUB_MENU_COPIA_PAK_ERROR_SIN_FANTASMA_DATOS;
                                        reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                                        return;
                                    }
                                    if (variable_temporal == ERROR_SIN_PFS) {
                                        if (sp30[JUGADOR_UNO].fantasma_datos_guardado) {
                                            seleccion_menu_sub = SUB_MENU_COPIA_PAK_DESDE_GHOST1_1P;
                                            reproducir_sonido2(SONIDO_SELECCION_MENU);
                                        } else if (sp30[JUGADOR_DOS].fantasma_datos_guardado) {
                                            seleccion_menu_sub = SUB_MENU_COPIA_PAK_DESDE_GHOST2_1P;
                                            reproducir_sonido2(SONIDO_SELECCION_MENU);
                                        } else {
                                            seleccion_menu_sub = SUB_MENU_COPIA_PAK_ERROR_SIN_FANTASMA_DATOS;
                                            reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                                        }
                                    }
                                    return;
                                case PFS_SIN_PAK_INSERTADO:
                                    seleccion_menu_sub = SUB_MENU_COPIA_PAK_ERROR_SIN_PAK_2P;
                                    reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                                    return;
                                case PFS_PAK_MALO_LECTURA:
                                default:
                                    seleccion_menu_sub = SUB_MENU_COPIA_PAK_ERROR_MALO_LECTURA_2P;
                                    reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                                    return;
                            }
                        case SUB_MENU_OPCION_BORRAR_TODOS_DATOS: {
                            seleccion_menu_sub = SUB_MENU_BORRAR_ABANDONAR;
                            reproducir_sonido2(SONIDO_SELECCION_MENU);
                            return;
                        }
                        case SUB_MENU_OPCION_RETORNO_JUEGO_SELECCION: {
                            funcion_8009E280();
                            reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                            return;
                        }
                    }
                }
                break;
            }
            case SUB_MENU_BORRAR_ABANDONAR:
            case SUB_MENU_BORRAR_BORRAR: {
                if ((boton_y_palanca & D_JPAD) && (seleccion_menu_sub < SUB_MENU_BORRAR_MAX)) {
                    seleccion_menu_sub += 1;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (sp38->paramf < 4.2) {
                        sp38->paramf += 4.0;
                    }
                    sp38->estado_sub = 1;
                }
                if ((boton_y_palanca & U_JPAD) && (seleccion_menu_sub > SUB_MENU_BORRAR_MIN)) {
                    seleccion_menu_sub -= 1;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (sp38->paramf < 4.2) {
                        sp38->paramf += 4.0;
                    }
                    sp38->estado_sub = -1;
                }
                if (boton_y_palanca & B_BUTTON) {
                    seleccion_menu_sub = SUB_MENU_OPCION_BORRAR_TODOS_DATOS;
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    return;
                }
                if (boton_y_palanca & A_BUTTON) {
                    switch (seleccion_menu_sub) {
                        case SUB_MENU_BORRAR_ABANDONAR:
                            seleccion_menu_sub = SUB_MENU_OPCION_BORRAR_TODOS_DATOS;
                            reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                            break;
                        case SUB_MENU_BORRAR_BORRAR:
                            seleccion_menu_sub = SUB_MENU_GUARDADO_DATOS_BORRADO;
                            funcion_800B46D0();
                            dato_800DC5AC = 0;
                            reproducir_sonido2(SONIDO_EXPLOSION_MENU);
                            break;
                    }
                }
                break;
            }
            case SUB_MENU_GUARDADO_DATOS_BORRADO: {
                if (boton_y_palanca & (A_BUTTON | B_BUTTON | START_BUTTON)) {
                    seleccion_menu_sub = SUB_MENU_OPCION_BORRAR_TODOS_DATOS;
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                }
                break;
            }
            case SUB_MENU_COPIA_PAK_DESDE_GHOST1_1P:
            case SUB_MENU_COPIA_PAK_DESDE_GHOST2_1P: {
                if ((boton_y_palanca & D_JPAD) && (seleccion_menu_sub < SUB_MENU_COPIA_PAK_DESDE_MAX_FANTASMA) &&
                    (sp30[JUGADOR_DOS].fantasma_datos_guardado)) {
                    seleccion_menu_sub += 1;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (sp38->paramf < 4.2) {
                        sp38->paramf += 4.0;
                    }
                    sp38->estado_sub = 1;
                }
                if ((boton_y_palanca & U_JPAD) && (seleccion_menu_sub > SUB_MENU_COPIA_PAK_DESDE_MIN_FANTASMA) &&
                    sp30[JUGADOR_UNO].fantasma_datos_guardado) {
                    seleccion_menu_sub -= 1;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (sp38->paramf < 4.2) {
                        sp38->paramf += 4.0;
                    }
                    sp38->estado_sub = -1;
                }
                if (boton_y_palanca & B_BUTTON) {
                    seleccion_menu_sub = SUB_MENU_OPCION_COPIA_CONTROLLER_PAK;
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    return;
                }
                if (boton_y_palanca & A_BUTTON) {
                    sp38->param2 = seleccion_menu_sub - SUB_MENU_COPIA_PAK_DESDE_MIN_FANTASMA;
                    if (sp30[sp38->param2].indice_circuito == dato_8018EE10[JUGADOR_DOS].indice_circuito &&
                        dato_8018EE10[JUGADOR_DOS].fantasma_datos_guardado) {
                        seleccion_menu_sub = SUB_MENU_COPIA_PAK_A_GHOST2_2P;
                    } else {
                        seleccion_menu_sub = SUB_MENU_COPIA_PAK_A_GHOST1_2P;
                    }
                    reproducir_sonido2(SONIDO_SELECCION_MENU);
                }
                break;
            }
            case SUB_MENU_COPIA_PAK_A_GHOST1_2P:
            case SUB_MENU_COPIA_PAK_A_GHOST2_2P: {
                if ((sp30[sp38->param2].indice_circuito !=
                     ((0, (dato_8018EE10 + (seleccion_menu_sub - SUB_MENU_COPIA_PAK_A_MIN_FANTASMA))->indice_circuito))) ||
                    ((dato_8018EE10 + (seleccion_menu_sub - SUB_MENU_COPIA_PAK_A_MIN_FANTASMA))->fantasma_datos_guardado == 0)) {
                    if ((boton_y_palanca & D_JPAD) && (seleccion_menu_sub < SUB_MENU_COPIA_PAK_A_MAX_FANTASMA)) {
                        seleccion_menu_sub += 1;
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        if (sp38->paramf < 4.2) {
                            sp38->paramf += 4.0;
                        }
                        sp38->estado_sub = 1;
                    }
                    if ((boton_y_palanca & U_JPAD) && (seleccion_menu_sub > SUB_MENU_COPIA_PAK_A_MIN_FANTASMA)) {
                        seleccion_menu_sub -= 1;
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        if (sp38->paramf < 4.2) {
                            sp38->paramf += 4.0;
                        }
                        sp38->estado_sub = -1;
                    }
                }
                if (boton_y_palanca & B_BUTTON) {
                    seleccion_menu_sub = sp38->param2 + SUB_MENU_COPIA_PAK_DESDE_MIN_FANTASMA;
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                } else if (boton_y_palanca & A_BUTTON) {
                    sp38->param1 = seleccion_menu_sub - SUB_MENU_COPIA_PAK_A_MIN_FANTASMA;
                    if (dato_8018EE10[(sp38->param1)].fantasma_datos_guardado) {
                        seleccion_menu_sub = SUB_MENU_COPIA_PAK_AVISO_ABANDONAR;
                    } else {
                        seleccion_menu_sub = SUB_MENU_COPIA_PAK_INICIO;
                        sp38->state = 0;
                    }
                    reproducir_sonido2(SONIDO_SELECCION_MENU);
                }
                break;
            }
            case SUB_MENU_COPIA_PAK_ERROR_SIN_FANTASMA_DATOS:
            case SUB_MENU_COPIA_PAK_ERROR_SIN_JUEGO_DATOS:
            case SUB_MENU_COPIA_PAK_ERROR_SIN_PAK_2P:
            case SUB_MENU_COPIA_PAK_ERROR_MALO_LECTURA_2P:
            case SUB_MENU_COPIA_PAK_ERROR_SIN_PAK_1P:
            case SUB_MENU_COPIA_PAK_ERROR_MALO_LECTURA_1P:
            case SUB_MENU_COPIA_PAK_ERROR_SIN_PAGINAS_1P:
            case SUB_MENU_COPIA_PAK_COMPLETADO:
            case SUB_MENU_COPIA_PAK_INCAPAZ_COPIA_DESDE_1P:
            case SUB_MENU_COPIA_PAK_INCAPAZ_LECTURA_DESDE_2P: {
                if (boton_y_palanca & (A_BUTTON | B_BUTTON | START_BUTTON)) {
                    seleccion_menu_sub = SUB_MENU_OPCION_COPIA_CONTROLLER_PAK;
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                }
                break;
            }
            case SUB_MENU_COPIA_PAK_AVISO_ABANDONAR:
            case SUB_MENU_COPIA_PAK_AVISO_COPIA: {
                if ((boton_y_palanca & R_JPAD) && seleccion_menu_sub < SUB_MENU_COPIA_PAK_AVISO_MAX) {
                    seleccion_menu_sub += 1;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (sp38->paramf < 4.2) {
                        sp38->paramf += 4.0;
                    }
                    sp38->estado_sub = 1;
                }
                if ((boton_y_palanca & L_JPAD) && seleccion_menu_sub > SUB_MENU_COPIA_PAK_AVISO_MIN) {
                    seleccion_menu_sub -= 1;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (sp38->paramf < 4.2) {
                        sp38->paramf += 4.0;
                    }
                    sp38->estado_sub = -1;
                }
                if (boton_y_palanca & B_BUTTON) {
                    seleccion_menu_sub = sp38->param1 + SUB_MENU_COPIA_PAK_A_MIN_FANTASMA;
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    return;
                }
                if (boton_y_palanca & A_BUTTON) {
                    if (seleccion_menu_sub == SUB_MENU_COPIA_PAK_AVISO_ABANDONAR) {
                        seleccion_menu_sub = SUB_MENU_OPCION_COPIA_CONTROLLER_PAK;
                        reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    } else {
                        seleccion_menu_sub = SUB_MENU_COPIA_PAK_INICIO;
                        reproducir_sonido2(SONIDO_SELECCION_MENU);
                        sp38->state = 0;
                    }
                }
                break;
            }
            case SUB_MENU_COPIA_PAK_INICIO: {
                if (idx_mando == JUGADOR_UNO) {
                    sp38->state += 1;
                }
                if (sp38->state >= 3) {
                    seleccion_menu_sub = SUB_MENU_COPIA_PAK_COPIANDO;
                }
                break;
            }
            case SUB_MENU_COPIA_PAK_COPIANDO: {
                res = controller_pak_2_situacion();
                if (res == ERROR_SIN_PFS) {
                    res = funcion_800B65F4(sp38->param2, sp38->param1);
                }
                if (res != 0) {
                    seleccion_menu_sub = SUB_MENU_COPIA_PAK_INCAPAZ_LECTURA_DESDE_2P;
                    reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                    return;
                }
                res = osPfsFindFile(&controller_pak_manejador_1_archivo, codigo_empresa, codigo_juego, (u8*) nombre_juego,
                                    (u8*) codigo_ext, &controller_pak_nota_1_archivo);
                if (res == ERROR_SIN_PFS) {
                    res = funcion_800B6178(sp38->param1);
                }
                if (res != 0) {
                    seleccion_menu_sub = SUB_MENU_COPIA_PAK_INCAPAZ_COPIA_DESDE_1P;
                    reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                    return;
                }
                seleccion_menu_sub = SUB_MENU_COPIA_PAK_COMPLETADO;
                dato_8018EE10[sp38->param1].indice_circuito = (sp30 + sp38->param2)->indice_circuito;
                funcion_800B6088(sp38->param1);
                break;
            }
            case SUB_MENU_COPIA_PAK_CREAR_JUEGO_DATOS_INICIALIZACION: {
                if (idx_mando == JUGADOR_UNO) {
                    sp38->state += 1;
                }
                if (sp38->state >= 3) {
                    seleccion_menu_sub = SUB_MENU_COPIA_PAK_CREAR_JUEGO_DATOS_HECHO;
                }
                break;
            }
            case SUB_MENU_COPIA_PAK_CREAR_JUEGO_DATOS_HECHO: {
                if (funcion_800B6A68()) {
                    seleccion_menu_sub = SUB_MENU_COPIA_PAK_ERROR_NO_PUEDE_CREAR_1P;
                    reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                } else if (sp30[0].fantasma_datos_guardado) {
                    seleccion_menu_sub = SUB_MENU_COPIA_PAK_DESDE_GHOST1_1P;
                } else {
                    seleccion_menu_sub = SUB_MENU_COPIA_PAK_DESDE_GHOST2_1P;
                }
                break;
            }
            default:
                break;
        }
    }
}

void act_menu_datos(struct Mando* mando, SIN_USO u16 idx_mando) {
    u16 boton_y_palanca = (mando->boton_pulsado | mando->palanca_pulsado);

    if (!modo_depuracion_activacion && ((boton_y_palanca & START_BUTTON) != 0)) {
        boton_y_palanca |= A_BUTTON;
    }

    if (es_pantalla_siendo_fundido() == 0) {
        if (seleccion_menu_sub == DATOS_MENU_SUB) {
            if ((boton_y_palanca & D_JPAD) != 0) {
                if ((contrarreloj_indice_circuito_datos % 4) != 3) {
                    ++contrarreloj_indice_circuito_datos;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
            }
            if ((boton_y_palanca & U_JPAD) != 0) {
                if ((contrarreloj_indice_circuito_datos % 4) != 0) {
                    --contrarreloj_indice_circuito_datos;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
            }
            if ((boton_y_palanca & R_JPAD) != 0) {
                if ((contrarreloj_indice_circuito_datos / 4) != 3) {
                    contrarreloj_indice_circuito_datos += 4;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
            }
            if ((boton_y_palanca & L_JPAD) != 0) {
                if ((contrarreloj_indice_circuito_datos / 4) != 0) {
                    contrarreloj_indice_circuito_datos -= 4;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
            }
            if ((boton_y_palanca & B_BUTTON) != 0) {
                funcion_8009E258();
                reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                return;
            }
            if ((boton_y_palanca & A_BUTTON) != 0) {
                circuito_registros_menu_seleccion = CIRCUITO_REGISTROS_MENU_RETORNO_MENU;
                funcion_8009E1C0();
                reproducir_sonido2(SONIDO_MENU_OK_CLICKED);
            }
        }
        else if ((boton_y_palanca & A_BUTTON) != 0) {
            funcion_8009E258();
            reproducir_sonido2(SONIDO_MENU_OK_CLICKED);
        }
    }
}

void circuito_datos_menu_act(struct Mando* mando, SIN_USO u16 idx_mando) {
    u16 boton_y_palanca;
    MenuItem* sp28;
    CircuitoContrarrelojRegistros* sp24;
    s32 res;

    boton_y_palanca = (mando->boton_pulsado | mando->palanca_pulsado);

    if (!modo_depuracion_activacion && (boton_y_palanca & START_BUTTON)) {
        boton_y_palanca |= A_BUTTON;
    }

    if (!es_pantalla_siendo_fundido()) {
        switch (seleccion_menu_sub) {
            case SUB_MENU_DATOS_OPCIONES: {
                if ((boton_y_palanca & L_JPAD) && (contrarreloj_indice_circuito_datos > 0)) {
                    contrarreloj_indice_circuito_datos -= 1;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }

                if ((boton_y_palanca & R_JPAD) && (contrarreloj_indice_circuito_datos < 15)) {
                    contrarreloj_indice_circuito_datos += 1;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }

                sp28 = buscar_duplicado_items_menu(0xE8);
                sp24 = &datos_guardado.todos_circuito_contrarreloj_registros.registros_copa[contrarreloj_indice_circuito_datos / 4]
                            .registros_circuito[contrarreloj_indice_circuito_datos % 4];
                if (circuito_registros_menu_seleccion == CIRCUITO_REGISTROS_MENU_BORRAR_FANTASMA &&
                    funcion_800B639C(contrarreloj_indice_circuito_datos) < 0) {
                    circuito_registros_menu_seleccion -= 1;
                }

                if (circuito_registros_menu_seleccion == CIRCUITO_REGISTROS_MENU_BORRAR_REGISTROS && sp24->bytes_desconocido[0] == 0) {
                    circuito_registros_menu_seleccion -= 1;
                }

                if ((boton_y_palanca & U_JPAD) && (circuito_registros_menu_seleccion > CIRCUITO_REGISTROS_MENU_MIN)) {
                    circuito_registros_menu_seleccion -= 1;
                    if (circuito_registros_menu_seleccion == 1 && sp24->bytes_desconocido[0] == 0) {
                        circuito_registros_menu_seleccion -= 1;
                    }
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (sp28->paramf < 4.2) {
                        sp28->paramf += 4.0;
                    }
                    sp28->estado_sub = -1;
                }

                if ((boton_y_palanca & D_JPAD) && (circuito_registros_menu_seleccion < CIRCUITO_REGISTROS_MENU_MAX)) {
                    circuito_registros_menu_seleccion += 1;
                    if (circuito_registros_menu_seleccion == CIRCUITO_REGISTROS_MENU_BORRAR_REGISTROS &&
                        sp24->bytes_desconocido[0] == 0) {
                        circuito_registros_menu_seleccion += 1;
                    }

                    if (circuito_registros_menu_seleccion == CIRCUITO_REGISTROS_MENU_BORRAR_FANTASMA &&
                        funcion_800B639C(contrarreloj_indice_circuito_datos) < 0) {
                        if (sp24->bytes_desconocido[0] == 0) {
                            circuito_registros_menu_seleccion = CIRCUITO_REGISTROS_MENU_RETORNO_MENU;
                        } else {
                            circuito_registros_menu_seleccion = CIRCUITO_REGISTROS_MENU_BORRAR_REGISTROS;
                        }
                    } else {
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        if (sp28->paramf < 4.2) {
                            sp28->paramf += 4.0;
                        }
                        sp28->estado_sub = 1;
                    }
                }

                if (boton_y_palanca & B_BUTTON) {
                    funcion_8009E208();
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                } else if (boton_y_palanca & A_BUTTON) {
                    if (sp28->paramf < 4.2) {
                        sp28->paramf += 4.0;
                    }
                    if (circuito_registros_menu_seleccion == CIRCUITO_REGISTROS_MENU_RETORNO_MENU) {
                        funcion_8009E208();
                        reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    } else {
                        seleccion_menu_sub = SUB_MENU_DATOS_BORRAR_CONFIRMAR;
                        circuito_registros_sub_menu_seleccion = CIRCUITO_REGISTROS_SUB_MENU_ABANDONAR;
                        reproducir_sonido2(SONIDO_SELECCION_MENU);
                    }
                }
                break;
            }
            case SUB_MENU_DATOS_BORRAR_CONFIRMAR: {
                sp28 = buscar_duplicado_items_menu(0xE9);
                if ((boton_y_palanca & U_JPAD) && (circuito_registros_sub_menu_seleccion > CIRCUITO_REGISTROS_SUB_MENU_MIN)) {
                    circuito_registros_sub_menu_seleccion -= 1;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (sp28->paramf < 4.2) {
                        sp28->paramf += 4.0;
                    }
                    sp28->estado_sub = -1;
                }

                if ((boton_y_palanca & D_JPAD) && (circuito_registros_sub_menu_seleccion < CIRCUITO_REGISTROS_SUB_MENU_MAX)) {
                    circuito_registros_sub_menu_seleccion += 1;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (sp28->paramf < 4.2) {
                        sp28->paramf += 4.0;
                    }
                    sp28->estado_sub = 1;
                }

                if (boton_y_palanca & B_BUTTON) {
                    seleccion_menu_sub = SUB_MENU_DATOS_OPCIONES;
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                } else if (boton_y_palanca & A_BUTTON) {
                    if (circuito_registros_sub_menu_seleccion != CIRCUITO_REGISTROS_SUB_MENU_ABANDONAR) {
                        res = 0;
                        switch (circuito_registros_menu_seleccion) {
                            case CIRCUITO_REGISTROS_MENU_BORRAR_REGISTROS: {
                                funcion_800B4728(contrarreloj_indice_circuito_datos);
                                funcion_800B559C(contrarreloj_indice_circuito_datos);
                                reproducir_sonido2(SONIDO_EXPLOSION_MENU);
                                res = -1;
                                break;
                            }
                            case CIRCUITO_REGISTROS_MENU_BORRAR_FANTASMA: {
                                res = funcion_800B639C(contrarreloj_indice_circuito_datos);
                                if (res >= 0) {
                                    if (funcion_800B69BC(res) != 0) {
                                        seleccion_menu_sub = SUB_MENU_DATOS_NO_PUEDE_BORRAR;
                                        reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                                    } else {
                                        reproducir_sonido2(SONIDO_EXPLOSION_MENU);
                                        seleccion_menu_sub = SUB_MENU_DATOS_OPCIONES;
                                    }
                                }
                                break;
                            }
                        }

                        if (!(res + 1)) {
                            seleccion_menu_sub = SUB_MENU_DATOS_OPCIONES;
                        }
                    } else {
                        reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                        seleccion_menu_sub = SUB_MENU_DATOS_OPCIONES;
                    }
                }
                break;
            }
            case SUB_MENU_DATOS_NO_PUEDE_BORRAR: {
                if (boton_y_palanca & (A_BUTTON | B_BUTTON | START_BUTTON)) {
                    seleccion_menu_sub = SUB_MENU_DATOS_OPCIONES;
                }
                break;
            }
        }
    }
}

void logo_intro_menu_act(struct Mando* mando, SIN_USO u16 idx_mando) {
    u16 boton_y_palanca = (mando->boton_pulsado | mando->palanca_pulsado);

    if ((es_pantalla_siendo_fundido() == 0) && (boton_y_palanca)) {
        funcion_800CA388(0x3C);

        funcion_8009E1E4();
    }
}
