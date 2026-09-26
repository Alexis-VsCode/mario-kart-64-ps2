// Camaras iniciales

void funcion_8003C0F0(void) {
    s16 sp5_e;
    s16 sp5_c;
    s16 sp5_a;
    s32 temporal_;
    SIN_USO s32 relleno[4];
    switch (id_circuito_actual) {
        case CIRCUITO_MARIO_RACEWAY:
        case CIRCUITO_CHOCO_MOUNTAIN:
        case CIRCUITO_BOWSER_CASTLE:
        case CIRCUITO_BANSHEE_BOARDWALK:
        case CIRCUITO_YOSHI_VALLEY:
        case CIRCUITO_FRAPPE_SNOWLAND:
        case CIRCUITO_KOOPA_BEACH:
        case CIRCUITO_ROYAL_RACEWAY:
        case CIRCUITO_LUIGI_RACEWAY:
        case CIRCUITO_MOO_MOO_FARM:
        case CIRCUITO_TOADS_TURNPIKE:
        case CIRCUITO_KALAMARI_DESERT:
        case CIRCUITO_SHERBET_LAND:
        case CIRCUITO_RAINBOW_ROAD:
        case CIRCUITO_WARIO_STADIUM:
        case CIRCUITO_DK_JUNGLE:
            inicializar_punto_camino_circuito();
            sp5_e = (f32) caminos_pista[0][0].pos_x;
            sp5_c = (f32) caminos_pista[0][0].pos_z;
            sp5_a = (f32) caminos_pista[0][0].pos_y;
            if (id_circuito_actual == CIRCUITO_TOADS_TURNPIKE) {
                sp5_e = 0;
            }
            break;

        case CIRCUITO_BLOCK_FORT:
        case CIRCUITO_SKYSCRAPER:
        case CIRCUITO_DOUBLE_DECK:
        case CIRCUITO_BIG_DONUT:
            funcion_8000EEDC();
            break;
    }

    switch (id_circuito_actual) {
        case CIRCUITO_MARIO_RACEWAY:
        case CIRCUITO_CHOCO_MOUNTAIN:
        case CIRCUITO_BOWSER_CASTLE:
        case CIRCUITO_BANSHEE_BOARDWALK:
        case CIRCUITO_YOSHI_VALLEY:
        case CIRCUITO_FRAPPE_SNOWLAND:
        case CIRCUITO_KOOPA_BEACH:
        case CIRCUITO_ROYAL_RACEWAY:
        case CIRCUITO_LUIGI_RACEWAY:
        case CIRCUITO_MOO_MOO_FARM:
        case CIRCUITO_TOADS_TURNPIKE:
        case CIRCUITO_KALAMARI_DESERT:
        case CIRCUITO_SHERBET_LAND:
        case CIRCUITO_RAINBOW_ROAD:
        case CIRCUITO_WARIO_STADIUM:
        case CIRCUITO_DK_JUNGLE:
            switch (modo_pantalla_activo) {
                case MODO_PANTALLA_1P:
                    switch (seleccion_modo) {
                        case GRAN_PREMIO:
                            dato_80165210[0] = (dato_80165210[2] = (dato_80165210[4] = (dato_80165210[6] = sp5_e + 0x14)));
                            dato_80165210[1] = (dato_80165210[3] = (dato_80165210[5] = (dato_80165210[7] = sp5_e - 0x14)));
                            dato_80165230[0] = sp5_c + 0x1E;
                            dato_80165230[1] = sp5_c + 0x32;
                            dato_80165230[2] = sp5_c + 0x46;
                            dato_80165230[3] = sp5_c + 0x5A;
                            dato_80165230[4] = sp5_c + 0x6E;
                            dato_80165230[5] = sp5_c + 0x82;
                            dato_80165230[6] = sp5_c + 0x96;
                            dato_80165230[7] = sp5_c + 0xAA;
                            aparecer_jugador_gp_uno_jugadores(dato_80165210, dato_80165230, sp5_a);
                            break;

                        case CONTRARRELOJ:
                            dato_80165210[0] = (dato_80165210[2] = (dato_80165210[4] = (dato_80165210[6] = sp5_e)));
                            dato_80165210[1] = (dato_80165210[3] = (dato_80165210[5] = (dato_80165210[7] = sp5_e)));
                            dato_80165230[0] = sp5_c + 0x1E;
                            dato_80165230[1] = sp5_c + 0x1E;
                            dato_80165230[2] = sp5_c + 0x1E;
                            dato_80165230[3] = sp5_c + 0x1E;
                            dato_80165230[4] = sp5_c + 0x1E;
                            dato_80165230[5] = sp5_c + 0x1E;
                            dato_80165230[6] = sp5_c + 0x1E;
                            dato_80165230[7] = sp5_c + 0x1E;
                            aparecer_jugadores_versus_un_jugador(dato_80165210, dato_80165230, sp5_a);
                            break;
                    }
                    break;

                case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
                case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
                    switch (seleccion_modo) {
                        case GRAN_PREMIO:
                            dato_80165210[0] = (dato_80165210[2] = (dato_80165210[4] = (dato_80165210[6] = sp5_e + 0x14)));
                            dato_80165210[1] = (dato_80165210[3] = (dato_80165210[5] = (dato_80165210[7] = sp5_e - 0x14)));
                            dato_80165230[0] = sp5_c + 0x1E;
                            dato_80165230[1] = sp5_c + 0x32;
                            dato_80165230[2] = sp5_c + 0x46;
                            dato_80165230[3] = sp5_c + 0x5A;
                            dato_80165230[4] = sp5_c + 0x6E;
                            dato_80165230[5] = sp5_c + 0x82;
                            dato_80165230[6] = sp5_c + 0x96;
                            dato_80165230[7] = sp5_c + 0xAA;
                            aparecer_jugador_gp_dos_jugadores(dato_80165210, dato_80165230, sp5_a);
                            break;

                        case VERSUS:
                            dato_80165210[0] = (dato_80165210[2] = (dato_80165210[4] = (dato_80165210[6] = sp5_e + 0xA)));
                            dato_80165210[1] = (dato_80165210[3] = (dato_80165210[5] = (dato_80165210[7] = sp5_e - 0xA)));
                            dato_80165230[0] = sp5_c + 0x1E;
                            dato_80165230[1] = sp5_c + 0x1E;
                            dato_80165230[2] = sp5_c + 0x1E;
                            dato_80165230[3] = sp5_c + 0x1E;
                            dato_80165230[4] = sp5_c + 0x1E;
                            dato_80165230[5] = sp5_c + 0x1E;
                            dato_80165230[6] = sp5_c + 0x1E;
                            dato_80165230[7] = sp5_c + 0x1E;
                            aparecer_jugadores_versus_dos_jugador(dato_80165210, dato_80165230, sp5_a);
                            break;
                    }
                    break;

                case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
                    switch (seleccion_modo) {
                        case VERSUS:
                            dato_80165210[0] = sp5_e + 0x1E;
                            dato_80165210[6] = sp5_e - 0xA;
                            dato_80165210[1] = sp5_e + 0xA;
                            dato_80165210[7] = sp5_e - 0x1E;
                            dato_80165210[4] = sp5_e - 0xA;
                            dato_80165210[2] = sp5_e - 0xA;
                            dato_80165210[5] = sp5_e - 0x1E;
                            dato_80165210[3] = sp5_e - 0x1E;
                            dato_80165230[0] = sp5_c + 0x1E;
                            dato_80165230[1] = sp5_c + 0x1E;
                            dato_80165230[2] = sp5_c + 0x1E;
                            dato_80165230[3] = sp5_c + 0x1E;
                            dato_80165230[4] = sp5_c + 0x1E;
                            dato_80165230[5] = sp5_c + 0x1E;
                            dato_80165230[6] = sp5_c + 0x1E;
                            dato_80165230[7] = sp5_c + 0x1E;
                            if (seleccion_cantidad_jugador_1 == 4) {
                                funcion_8003B870(dato_80165210, dato_80165230, sp5_a);
                            } else {
                                funcion_8003B318(dato_80165210, dato_80165230, sp5_a);
                            }
                            break;
                    }
                    break;
            }
            break;

        case CIRCUITO_BLOCK_FORT:
            switch (modo_pantalla_activo) {
                case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
                case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
                    temporal_ = 5;
                    if (1) {};
                    dato_80165210[0] = 0;
                    dato_80165210[1] = 0;
                    dato_80165230[1] = -200.0f;
                    dato_80165230[0] = 200.0f;
                    aparecer_batalla_jugadores_2j(dato_80165210, dato_80165230, temporal_);
                    break;

                case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
                    temporal_ = 5;
                    dato_80165210[2] = -200.0f;
                    dato_80165230[1] = -200.0f;
                    dato_80165210[0] = 0.0f;
                    dato_80165210[1] = 0.0f;
                    dato_80165230[2] = 0.0f;
                    dato_80165230[3] = 0.0f;
                    dato_80165210[3] = 200.0f;
                    dato_80165230[0] = 200.0f;
                    if (seleccion_cantidad_jugador_1 == 4) {
                        aparecer_batalla_jugadores_4j(dato_80165210, dato_80165230, temporal_);
                    } else {
                        aparecer_batalla_jugadores_3j(dato_80165210, dato_80165230, temporal_);
                    }
                    break;
            }
            break;

        case CIRCUITO_SKYSCRAPER:
            switch (modo_pantalla_activo) {
                case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
                case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
                    temporal_ = 0x1E0;
                    if (1) {};
                    dato_80165210[0] = 0.0f;
                    dato_80165210[1] = 0.0f;
                    dato_80165230[1] = -400.0f;
                    dato_80165230[0] = 400.0f;
                    aparecer_batalla_jugadores_2j(dato_80165210, dato_80165230, temporal_);
                    break;

                case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
                    temporal_ = 0x1E0;
                    dato_80165210[0] = 0.0f;
                    dato_80165210[1] = 0.0f;
                    dato_80165210[2] = -400.0f;
                    dato_80165210[3] = 400.0f;
                    dato_80165230[0] = 400.0f;
                    dato_80165230[1] = -400.0f;
                    dato_80165230[2] = 0.0f;
                    dato_80165230[3] = 0.0f;
                    if (seleccion_cantidad_jugador_1 == 4) {
                        aparecer_batalla_jugadores_4j(dato_80165210, dato_80165230, temporal_);
                    } else {
                        aparecer_batalla_jugadores_3j(dato_80165210, dato_80165230, temporal_);
                    }
                    break;
            }
            break;

        case CIRCUITO_DOUBLE_DECK:
            switch (modo_pantalla_activo) {
                case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
                case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
                    temporal_ = 0x37;
                    if (1) {};
                    dato_80165210[0] = 0.0f;
                    dato_80165210[1] = 0.0f;
                    dato_80165230[1] = -160.0f;
                    dato_80165230[0] = 160.0f;
                    aparecer_batalla_jugadores_2j(dato_80165210, dato_80165230, temporal_);
                    break;

                case 3:
                    temporal_ = 0x37;
                    dato_80165210[0] = 0.0f;
                    dato_80165210[1] = 0.0f;
                    dato_80165210[2] = -160.0f;
                    dato_80165210[3] = 160.0f;
                    dato_80165230[0] = 160.0f;
                    dato_80165230[1] = -160.0f;
                    dato_80165230[2] = 0.0f;
                    dato_80165230[3] = 0.0f;
                    if (seleccion_cantidad_jugador_1 == 4) {
                        aparecer_batalla_jugadores_4j(dato_80165210, dato_80165230, temporal_);
                    } else {
                        aparecer_batalla_jugadores_3j(dato_80165210, dato_80165230, temporal_);
                    }
                    break;
            }
            break;

        case CIRCUITO_BIG_DONUT:
            switch (modo_pantalla_activo) {
                case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
                case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
                    temporal_ = 0xC8;
                    if (1) {};
                    dato_80165210[0] = 0.0f;
                    dato_80165210[1] = 0.0f;
                    dato_80165230[1] = -575.0f;
                    dato_80165230[0] = 575.0f;
                    aparecer_batalla_jugadores_2j(dato_80165210, dato_80165230, temporal_);
                    break;

                case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
                    temporal_ = 0xC8;
                    dato_80165210[0] = 0.0f;
                    dato_80165210[1] = 0.0f;
                    dato_80165210[2] = -575.0f;
                    dato_80165210[3] = 575.0f;
                    dato_80165230[0] = 575.0f;
                    dato_80165230[1] = -575.0f;
                    dato_80165230[2] = 0.0f;
                    dato_80165230[3] = 0.0f;
                    if (seleccion_cantidad_jugador_1 == 4) {
                        aparecer_batalla_jugadores_4j(dato_80165210, dato_80165230, temporal_);
                    } else {
                        aparecer_batalla_jugadores_3j(dato_80165210, dato_80165230, temporal_);
                    }
                    break;
            }
            break;

        default:
            dato_80165210[0] = (dato_80165210[2] = (dato_80165210[4] = (dato_80165210[6] = 20.0f)));
            dato_80165210[1] = (dato_80165210[3] = (dato_80165210[5] = (dato_80165210[7] = -20.0f)));
            dato_80165230[0] = 30.0f;
            dato_80165230[1] = 50.0f;
            dato_80165230[2] = 70.0f;
            dato_80165230[3] = 90.0f;
            dato_80165230[4] = 110.0f;
            dato_80165230[5] = 130.0f;
            dato_80165230[6] = 150.0f;
            dato_80165230[7] = 170.0f;
            aparecer_jugador(copia_jugador_uno, 0, dato_80165210[0], dato_80165230[0], sp5_a, 32768.0f, selecciones_personaje[0],
                         EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
            aparecer_jugador(jugador_dos, 1, dato_80165210[1], dato_80165230[1], sp5_a, 32768.0f, 1,
                         EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
            aparecer_jugador(jugador_tres, 2, dato_80165210[2], dato_80165230[2], sp5_a, 32768.0f, 2,
                         EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
            aparecer_jugador(jugador_cuatro, 3, dato_80165210[3], dato_80165230[3], sp5_a, 32768.0f, 3,
                         EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
            aparecer_jugador(jugador_cinco, 4, dato_80165210[4], dato_80165230[4], sp5_a, 32768.0f, 4,
                         EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
            aparecer_jugador(jugador_seis, 5, dato_80165210[5], dato_80165230[5], sp5_a, 32768.0f, 5,
                         EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
            aparecer_jugador(jugador_siete, 6, dato_80165210[6], dato_80165230[6], sp5_a, 32768.0f, 6,
                         EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
            aparecer_jugador(jugador_ocho, 7, dato_80165210[7], dato_80165230[7], sp5_a, 32768.0f, 7,
                         EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
            dato_80164A28 = 0;
            break;
    }

    if (seleccion_modo != BATALLA) {
        inicializar_jugadores();
    }
}

void funcion_8003CD78(void) {
    funcion_8003BE30();
}

void funcion_8003CD98(Jugador* jugador, Camara* camara, s8 id_jugador, s8 id_pantalla) {
    if (jugador->type & EXISTE_JUGADOR) {
        if (id_pantalla == 0) {
            funcion_8002D268(jugador, camara, id_pantalla, id_jugador);
        }
        funcion_8002934C(jugador, camara, id_pantalla, id_jugador);
        if ((id_pantalla == 0) || (id_pantalla == 1)) {
            cargar_paleta_kart(jugador, id_jugador, id_pantalla, 0);
            cargar_paleta_kart(jugador, id_jugador, id_pantalla, 1);
            cargar_textura_kart(jugador, id_jugador, id_pantalla, id_pantalla, 0);
            mio0decode((u8*) &textura_kart_codificado[0][id_pantalla][id_jugador],
                       (u8*) &dato_802BFB80.tamanio_arreglo_8[0][id_pantalla][id_jugador]);
        } else {
            cargar_paleta_kart(jugador, id_jugador, id_pantalla, 0);
            cargar_paleta_kart(jugador, id_jugador, id_pantalla, 1);
            cargar_textura_kart(jugador, (s8) (id_jugador + 4), id_pantalla, (s8) (id_pantalla - 2), 0);
            mio0decode((u8*) &textura_kart_codificado[0][id_pantalla - 2][id_jugador + 4],
                       (u8*) &dato_802BFB80.tamanio_arreglo_8[0][id_pantalla - 2][id_jugador + 4]);
        }

        ultimo_selector_frame_anim[id_pantalla][id_jugador] = jugador->anim_frame_selector[id_pantalla];
        ultimo_selector_grupo_anim[id_pantalla][id_jugador] = jugador->anim_selector_grupo[id_pantalla];
        dato_80165150[id_pantalla][id_jugador] = jugador->desconocido_0A8;
        dato_801651D0[id_pantalla][id_jugador] = 0;
        renderizar_jugador(jugador, id_jugador, id_pantalla);
    }
}

void funcion_8003D080(void) {
    SIN_USO s32 relleno;
    Jugador* jugador = &jugadores[0];

    funcion_8005D290();
    if (estado_juego == FINAL) {
        funcion_8003CD78();
    } else {
        funcion_8003C0F0();
    }
    if (!modo_demo) {
        switch (modo_pantalla_activo) {
            case MODO_PANTALLA_1P:
                switch (seleccion_modo) {
                    case GRAN_PREMIO:
                        if (id_circuito_actual == CIRCUITO_TOADS_TURNPIKE) {
                            inicializar_camara(0.0f, jugador->pos[1], dato_80165230[7], jugador->rotacion[1], 8, 0);
                        } else {
                            inicializar_camara((dato_80165210[7] + dato_80165210[6]) / 2, jugador->pos[1], dato_80165230[7],
                                        jugador->rotacion[1], 8, 0);
                        }
                        break;

                    case CONTRARRELOJ:
                        inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 1, 0);
                        break;

                    default:
                        inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 10, 0);
                        break;
                }
                break;

            case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
            case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
                switch (seleccion_modo) {
                    case GRAN_PREMIO:
                        inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 1, 0);
                        jugador++;
                        inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 1, 1);
                        break;

                    case BATALLA:
                        inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 9, 0);
                        jugador++;
                        inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 9, 1);
                        break;

                    default:
                        inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 1, 0);
                        jugador++;
                        inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 1, 1);
                        break;
                }
                break;

            case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
                if (seleccion_modo == BATALLA) {
                    inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 9, 0);
                    jugador++;
                    inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 9, 1);
                    jugador++;
                    inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 9, 2);
                    if (seleccion_cantidad_jugador_1 == 4) {
                        jugador++;
                        inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 9, 3);
                    }
                } else {
                    inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 1, 0);
                    jugador++;
                    inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 1, 1);
                    jugador++;
                    inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 1, 2);
                    if (seleccion_cantidad_jugador_1 == 4) {
                        jugador++;
                        inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 1, 3);
                    }
                }
                break;
        }
    } else {
        switch (modo_pantalla_activo) {
            case MODO_PANTALLA_1P:
                inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 3, 0);
                break;

            case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
            case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
                inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 3, 0);
                jugador++;
                inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 3, 1);
                break;

            case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
                inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 3, 0);
                jugador++;
                inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 3, 1);
                jugador++;
                inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 3, 2);
                jugador++;
                inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 3, 3);
                break;
        }
    }

    switch (modo_pantalla_activo) {
        case MODO_PANTALLA_1P:
            funcion_8003CD98(copia_jugador_uno, camara1, 0, 0);
            funcion_8003CD98(jugador_dos, camara1, 1, 0);
            funcion_8003CD98(jugador_tres, camara1, 2, 0);
            funcion_8003CD98(jugador_cuatro, camara1, 3, 0);
            funcion_8003CD98(jugador_cinco, camara1, 4, 0);
            funcion_8003CD98(jugador_seis, camara1, 5, 0);
            funcion_8003CD98(jugador_siete, camara1, 6, 0);
            funcion_8003CD98(jugador_ocho, camara1, 7, 0);
            break;

        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            funcion_8003CD98(copia_jugador_uno, camara1, 0, 0);
            funcion_8003CD98(jugador_dos, camara1, 1, 0);
            funcion_8003CD98(jugador_tres, camara1, 2, 0);
            funcion_8003CD98(jugador_cuatro, camara1, 3, 0);
            funcion_8003CD98(jugador_cinco, camara1, 4, 0);
            funcion_8003CD98(jugador_seis, camara1, 5, 0);
            funcion_8003CD98(jugador_siete, camara1, 6, 0);
            funcion_8003CD98(jugador_ocho, camara1, 7, 0);
            funcion_8003CD98(copia_jugador_uno, camara2, 0, 1);
            funcion_8003CD98(jugador_dos, camara2, 1, 1);
            funcion_8003CD98(jugador_tres, camara2, 2, 1);
            funcion_8003CD98(jugador_cuatro, camara2, 3, 1);
            funcion_8003CD98(jugador_cinco, camara2, 4, 1);
            funcion_8003CD98(jugador_seis, camara2, 5, 1);
            funcion_8003CD98(jugador_siete, camara2, 6, 1);
            funcion_8003CD98(jugador_ocho, camara2, 7, 1);
            break;

        case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
            funcion_8003CD98(copia_jugador_uno, camara1, 0, 0);
            funcion_8003CD98(jugador_dos, camara1, 1, 0);
            funcion_8003CD98(jugador_tres, camara1, 2, 0);
            funcion_8003CD98(jugador_cuatro, camara1, 3, 0);
            funcion_8003CD98(copia_jugador_uno, camara2, 0, 1);
            funcion_8003CD98(jugador_dos, camara2, 1, 1);
            funcion_8003CD98(jugador_tres, camara2, 2, 1);
            funcion_8003CD98(jugador_cuatro, camara2, 3, 1);
            funcion_8003CD98(copia_jugador_uno, camara3, 0, 2);
            funcion_8003CD98(jugador_dos, camara3, 1, 2);
            funcion_8003CD98(jugador_tres, camara3, 2, 2);
            funcion_8003CD98(jugador_cuatro, camara3, 3, 2);
            funcion_8003CD98(copia_jugador_uno, camara4, 0, 3);
            funcion_8003CD98(jugador_dos, camara4, 1, 3);
            funcion_8003CD98(jugador_tres, camara4, 2, 3);
            funcion_8003CD98(jugador_cuatro, camara4, 3, 3);
            break;
    }
}

void funcion_8003DB5C(void) {
    Jugador* jugador = jugador_uno;
    s32 id_jugador;

    inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 3, 0);
    inicializar_camara(jugador->pos[0], jugador->pos[1], jugador->pos[2], jugador->rotacion[1], 3, 1);

    for (id_jugador = 0; id_jugador < JUGADORES_NUM; id_jugador++, jugador++) {
        cargar_paleta_kart(jugador, id_jugador, 1, 0);
        cargar_paleta_kart(jugador, id_jugador, 1, 1);
    }
}
