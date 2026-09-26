// Estados menu

void cargar_estados_menu(s32 menu_seleccion) {
    s32 i;

    seleccion_menu_depuracion = SELECCION_MENU_DEPURACION;
    contador_tiempos_menu = 0;
    temporizador_retardo_menu = 0;
    mando_usar_demo = 0;
    dato_8015F890 = 0;
    dato_8015F892 = 0;
    escena_goto_depuracion = CARRERA_GOTO_DEPURACION;
    inicializacion_jugador_fantasma = 0;
    dato_8016556E = 0;
    b_jugador_fantasma_desactivado = 1;
    dato_80162DD8 = 1;
    dato_80162E00 = 0;
    dato_80162DC8 = 1;
    dato_80162DCC = 0;

    switch (menu_seleccion) {
        case MENU_OPCIONES:
            seleccion_menu_sub = SUB_MENU_OPCION_RETORNO_JUEGO_SELECCION;
            break;
        case MENU_DATOS:
            seleccion_menu_sub = DATOS_MENU_SUB;
            break;
        case MENU_DATOS_CIRCUITO:
            seleccion_menu_sub = SUB_MENU_DATOS_OPCIONES;
            break;
        case LOGO_INTRO_MENU:
            funcion_800CA008(0, 0);
            break;
        case CONTROLLER_PAK_MENU: {
            controller_pak_seleccion_menu = CONTROLLER_PAK_REGISTRO_SELECCION_MENU;
            funcion_800CA008(0, 0);
            break;
        }
        case 0:
        case MENU_INICIO: {
            es_modo_espejo = 0;
            modo_depuracion_activacion = ALTERNAR_MODO_DEPURACION;
            seleccion_copa = COPA_HONGO;
            indice_circuito_en_copa = 0;
            contrarreloj_indice_circuito_datos = 0;
            if (cantidad_jugador <= 0) {
                cantidad_jugador = 1;
            }
            if (cantidad_jugador >= 5) {
                cantidad_jugador = 4;
            }
            pantalla_modo_lista_indice = idx_modo_pantalla_desde_modo_jugador[cantidad_jugador - 1];
            funcion_800CA008(0, 0);
            reproducir_secuencia(SEC_PANTALLA_TITULO_MENU);
            inicializacion_mapa_circuito = 0;
            break;
        }
        case 1:
        case MENU_PRINCIPAL: {
            modo_depuracion_activacion = ALTERNAR_MODO_DEPURACION;
            es_modo_espejo = 0;
            inicializacion_mapa_circuito = 0;
            funcion_800B5F30();
            funcion_8000F0E0();

            if (estado_juego != 0) {
                funcion_800CA008(0, 0);
                funcion_800CB2C4();
                estado_juego = 0;
                siguiente_estado_juego = 0;
                reproducir_secuencia(SEC_MENU_MENU_PRINCIPAL);
            }

            switch (tipo_fundido_menu) {
                case MENU_FUNDIDO_TIPO_PRINCIPAL: {
                    menu_principal_seleccion = MENU_PRINCIPAL_SELECCION_JUGADOR;
                    reproducir_secuencia(SEC_MENU_MENU_PRINCIPAL);
                    cantidad_jugador = 1;
                    if (seleccion_modo_pantalla >= MODOS_PANTALLA_NUM || seleccion_modo_pantalla < 0) {
                        seleccion_modo_pantalla = MODO_PANTALLA_1P;
                    }
                    break;
                }
                case MENU_FUNDIDO_TIPO_ATRAS: {
                    menu_principal_seleccion = MENU_PRINCIPAL_OK_SELECCION_IR_ATRAS;
                    break;
                }
                case MENU_FUNDIDO_TIPO_DATOS: {
                    switch (menu_principal_seleccion) {
                        default:
                            menu_principal_seleccion = MENU_PRINCIPAL_MODO_SUB_SELECCION_IR_ATRAS;
                            break;
                        case MENU_PRINCIPAL_OPCION:
                        case MENU_PRINCIPAL_DATOS:
                            menu_principal_seleccion = MENU_PRINCIPAL_SELECCION_JUGADOR;
                            break;
                    }
                    break;
                }
                case MENU_FUNDIDO_TIPO_OPCION: {
                    menu_principal_seleccion = MENU_PRINCIPAL_SELECCION_JUGADOR;
                    break;
                }
            }
            break;
        }
        case 2:
        case MENU_SELECCION_PERSONAJE: {
            switch (tipo_fundido_menu) {
                case MENU_FUNDIDO_TIPO_PRINCIPAL: {
                    jugador_seleccion_menu_seleccion = JUGADOR_SELECCION_MENU_PRINCIPAL;
                    if (estado_juego == 0) {
                        for (i = 0; i < CANTIDAD_ARREGLO(selecciones_cuadricula_personaje); i++) {
                            if (i < cantidad_jugador) {
                                selecciones_cuadricula_personaje[i] = i + 1;
                            } else {
                                selecciones_cuadricula_personaje[i] = 0;
                            }
                            personaje_cuadricula_es_seleccionado[i] = false;
                            selecciones_personaje[i] = i;
                        }
                        reproducir_sonido2(SONIDO_JUGADOR_SELECCION_MENU);
                    } else {
                        funcion_800CA008(0, 0);
                        funcion_800CB2C4();
                        estado_juego = 0;
                        siguiente_estado_juego = 0;
                        reproducir_secuencia(SEC_MENU_MENU_PRINCIPAL);
                        for (i = 0; i < CANTIDAD_ARREGLO(personaje_cuadricula_es_seleccionado); i++) {
                            personaje_cuadricula_es_seleccionado[i] = false;
                        }
                    }
                    break;
                }
                case MENU_FUNDIDO_TIPO_ATRAS: {
                    jugador_seleccion_menu_seleccion = JUGADOR_SELECCION_MENU_OK_IR_ATRAS;
                    for (i = 0; i < CANTIDAD_ARREGLO(personaje_cuadricula_es_seleccionado); i++) {
                        if (cantidad_jugador > i) {
                            personaje_cuadricula_es_seleccionado[i] = true;
                        } else {
                            personaje_cuadricula_es_seleccionado[i] = false;
                        }
                    }
                    break;
                }
            }
            break;
        }
        case 3:
        case MENU_SELECCION_CIRCUITO: {
            if (seleccion_modo == BATALLA) {
                seleccion_copa = COPA_BATALLA;
                dato_800DC540 = 4;
                seleccion_menu_sub = SUB_MENU_MAPA_SELECCION_BATALLA_CIRCUITO;
            } else {
                if (seleccion_copa == COPA_BATALLA) {
                    seleccion_copa = COPA_HONGO;
                }
                seleccion_menu_sub = SUB_MENU_MAPA_SELECCION_COPA;
            }
            if (estado_juego != 0) {
                funcion_800CA008(0, 0);
                funcion_800CB2C4();
                estado_juego = 0;
                siguiente_estado_juego = 0;
                reproducir_secuencia(SEC_MENU_MENU_PRINCIPAL);
            }
            reproducir_sonido2(SONIDO_MAPA_SELECCION_MENU);
            seleccion_copa_temporal = 0;
            if (seleccion_modo == GRAN_PREMIO) {
                indice_circuito_en_copa = 0;
            }

            for (i = 0; i < CANTIDAD_ARREGLO(puntos_gp_por_id_personaje); i++) {
                puntos_gp_por_id_personaje[i] = 0;
            }
            break;
        }
    }
    reiniciar_menu_destello_ciclo();
}

void reiniciar_menu_destello_ciclo(void) {
    menu_destello_ciclo = 0x20;
}

void fijar_modo_sonido(void) {
    SIN_USO u32 relleno;
    union PaqueteModoJuego empaquetar;

    empaquetar = sonido_paquete_menu;
    if ((sonido_modo == SONIDO_ESTEREO) || (sonido_modo == SONIDO_AURICULARES) || (sonido_modo == SONIDO_MONO)) {
        funcion_800C3448(empaquetar.modos[sonido_modo] | 0xE0000000);
    }
}

bool es_pantalla_siendo_fundido(void) {
    if ((tipo_transicion[4] == 2) || (tipo_transicion[4] == 3) || (tipo_transicion[4] == 4) ||
        (tipo_transicion[4] == 7)) {
        return true;
    }
    return false;
}

SIN_USO void imprimir_fantasma_kart_personaje_id_depuracion(s32 parametro0, s32 parametro1) {
    struct_8018EE10_entrada* pak1 = dato_8018EE10;
    struct_8018EE10_entrada* pak2 = (struct_8018EE10_entrada*) algun_buffer_dl;

    rmon_printf("ghost_kart=%d,", dato_80162DE0);
    rmon_printf("pak1_ghost_kart=%d,", (pak1 + parametro0)->id_personaje);
    rmon_printf("pak2_ghost_kart=%d\n", (pak2 + parametro1)->id_personaje);
}
