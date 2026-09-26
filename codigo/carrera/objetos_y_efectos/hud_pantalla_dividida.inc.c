// Hud pantalla dividida

void funcion_800591B4(void) {

    if ((desactivar_hud == 0) && (dato_800DC5B8 != 0)) {
        funcion_80057C60();
        gSPDisplayList(display_list_cabeza++, &dato_0D0076F8);

        if (es_visible_hud != 0) {
            if (dato_801657D8 == 0) {
                if (dato_801657F0 != false) {
                    funcion_800514BC();
                }
                if ((!modo_demo) && (dato_801657E8 != false)) {
                    if (dato_80165800[0] != 0) {
                        funcion_8004EE54(0);
                        if (seleccion_modo != BATALLA) {
                            renderizar_minimapa_linea_meta(0);
                        }
                        funcion_8004F3E4(0);
                    }
                    if ((seleccion_modo_pantalla == PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL) && (dato_80165800[1] != 0)) {
                        funcion_8004EE54(1);
                        if (seleccion_modo != BATALLA) {
                            renderizar_minimapa_linea_meta(1);
                        }
                        funcion_8004F3E4(1);
                    }
                }
            }
            if ((dato_801657E4 != 2) && (seleccion_modo == GRAN_PREMIO) && (dato_8018D2BC != 0)) {
                funcion_80050320();
            }
            funcion_800590D4();
        }
        funcion_8005902C();
        funcion_80057DD0();
        funcion_80057CE4();
    }
}

void funcion_80059358(void) {
}

void renderizar_hud_2j_horizontal_jugador_dos_horizontal_jugador_uno(void) {
    if (desactivar_hud == 0) {
        renderizar_temporizador_hud(JUGADOR_UNO);
        if (h_ud_jugador[JUGADOR_UNO].cantidad_vuelta != 3) {
            dibujar_textura_32x_hud_2d_8(h_ud_jugador[JUGADOR_UNO].vuelta_x, h_ud_jugador[JUGADOR_UNO].vuelta_y,
                                     (u8*) comun_textura_hud_vuelta);
            dibujar_cantidad_vuelta(h_ud_jugador[JUGADOR_UNO].vuelta_x + 0xC, h_ud_jugador[JUGADOR_UNO].vuelta_y - 4,
                           h_ud_jugador[JUGADOR_UNO].cantidad_vuelta_tambien);
            dibujar_ventana_item(JUGADOR_UNO);
        }
    }
}

void funcion_800593F0(void) {
}

void renderizar_jugador_dos_horizontal_hud_2j(void) {
    if (desactivar_hud == 0) {
        renderizar_temporizador_hud(JUGADOR_DOS);
        if (h_ud_jugador[JUGADOR_DOS].cantidad_vuelta != 3) {
            dibujar_textura_32x_hud_2d_8(h_ud_jugador[JUGADOR_DOS].vuelta_x, h_ud_jugador[JUGADOR_DOS].vuelta_y,
                                     (u8*) comun_textura_hud_vuelta);
            dibujar_cantidad_vuelta(h_ud_jugador[JUGADOR_DOS].vuelta_x + 0xC, h_ud_jugador[JUGADOR_DOS].vuelta_y - 4,
                           h_ud_jugador[JUGADOR_DOS].cantidad_vuelta_tambien);
            dibujar_ventana_item(JUGADOR_DOS);
        }
    }
}

void dibujar_hud_simplificado(s32 id_jugador) {
    if ((seleccion_modo != BATALLA) && (dato_80165800[id_jugador] == 0) && (es_visible_hud != 0)) {
        renderizar_temporizador_hud(id_jugador);
        dibujar_cantidad_vuelta_simplificado(id_jugador);
    }
    dibujar_ventana_item(id_jugador);
}

void funcion_800594F0(void) {
}

void renderizar_jugador_uno_vertical_hud_2j(void) {
    if (desactivar_hud == 0) {
        dibujar_hud_simplificado(JUGADOR_UNO);
    }
}

void funcion_80059528(void) {
}

void renderizar_jugador_dos_vertical_hud_2j(void) {
    if (desactivar_hud == 0) {
        dibujar_hud_simplificado(JUGADOR_DOS);
    }
}

void renderizar_vuelta_3j_4j_hud(s32 id_jugador) {
    if (seleccion_modo != BATALLA) {
        if (dato_801657F8 && es_visible_hud) {
            dibujar_textura_32x_hud_2d_8(h_ud_jugador[id_jugador].vuelta_x, h_ud_jugador[id_jugador].vuelta_y, (u8*) comun_textura_hud_vuelta);
            dibujar_cantidad_vuelta(h_ud_jugador[id_jugador].vuelta_x - 12, h_ud_jugador[id_jugador].vuelta_y + 4,
                           h_ud_jugador[id_jugador].cantidad_vuelta_tambien);
        }
        if (dato_801657E4 == 2) {
            if (h_ud_jugador[id_jugador].desconocido_74 && dato_80165608) {
                funcion_80047910(h_ud_jugador[id_jugador].desconocido_6C, h_ud_jugador[id_jugador].desconocido_6E, 0, 1.0f,
                              (u8*) retrato_tlut_comun_kart_bomba_y_signo_pregunta, retrato_textura_comun_kart_bomba,
                              dato_0D005AE0, 0x20, 0x20, 0x20, 0x20);
            }
        }
    }
    funcion_8004E6C4(id_jugador);
}

void funcion_800596A8(void) {
    if (desactivar_hud == 0) {
        fijar_pantalla_hud_matriz();
    }
}

void renderizar_multi_hud_1j(void) {
    if (desactivar_hud == 0) {
        fijar_pantalla_hud_matriz();
        renderizar_vuelta_3j_4j_hud(JUGADOR_UNO);
    }
}

void funcion_80059710(void) {
}

void renderizar_multi_hud_2j(void) {
    if (desactivar_hud == 0) {
        fijar_pantalla_hud_matriz();
        renderizar_vuelta_3j_4j_hud(JUGADOR_DOS);
    }
}

void funcion_80059750(void) {
    if (desactivar_hud == 0) {
        fijar_pantalla_hud_matriz();
    }
}

void renderizar_multi_hud_3j(void) {
    if (desactivar_hud == 0) {
        fijar_pantalla_hud_matriz();
        renderizar_vuelta_3j_4j_hud(JUGADOR_TRES);
    }
}

void funcion_800597B8(void) {
    if (desactivar_hud == 0) {
        fijar_pantalla_hud_matriz();
    }
}

void renderizar_multi_hud_4j(void) {
    if (desactivar_hud == 0) {
        fijar_pantalla_hud_matriz();
        renderizar_vuelta_3j_4j_hud(JUGADOR_CUATRO);
    }
}

void funcion_80059820(s32 id_jugador) {
    jugador_hud* temporal_v0;

    dato_8018CF1C = &jugador_uno[id_jugador];
    dato_8018CF14 = &camara1[id_jugador];
    temporal_v0 = &h_ud_jugador[id_jugador];
    temporal_v0->pos_x_int = (s32) dato_8018CF1C->pos[0];
    temporal_v0->pos_y_int = (s32) dato_8018CF1C->pos[1];
    temporal_v0->pos_z_int = (s32) dato_8018CF1C->pos[2];
}

void aleatorizar_semilla_desde_mando(s32 parametro0) {
    struct Mando* mando = &mando_uno[parametro0];

    if ((mando->button & A_BUTTON) != 0) {
        aleatorio_mando++;
    }
    if ((mando->button & B_BUTTON) != 0) {
        aleatorio_mando++;
    }
    if ((mando->button & R_TRIG) != 0) {
        aleatorio_mando++;
    }
}

void funcion_8005994C(void) {
    dato_8018D214 = true;
}

void funcion_8005995C(void) {
    s32 i;
    Jugador* jugador = jugador_uno;
    for (i = 0; i < 4; i++) {
        if ((dato_80165890 != 0) && (jugador->type & INVISIBLE_JUGADOR_O_BOMBA)) {
            jugador->copia_item_actual = HONGO_ITEM;

            h_ud_jugador[i].desconocido_75 = 2;
        }
        if ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) && (jugador->copia_item_actual == NINGUNO_ITEM)) {
            if (h_ud_jugador[i].desconocido_75) {
                jugador->copia_item_actual = HONGO_ITEM;
                --h_ud_jugador[i].desconocido_75;
            }
        }
        ++jugador;
    }
    dato_80165890 = 0;
}

void funcion_80059A88(s32 id_jugador) {
    funcion_80059820(id_jugador);
    if (!modo_demo) {
        actualizar_objeto_lakitu(id_jugador);
        funcion_8007BB9C(id_jugador);
    }
}

void funcion_80059AC8(void) {
    s32 i;

    if (juego_en_pausa == false) {
        funcion_8008C1D8(&dato_80165678);
        contador_frame_carrera++;
        for (i = 0; i < JUGADORES_NUM; i++) {
            dato_8018CF68[i] = funcion_8008A890(&camara1[i]);
            funcion_800892E0(i);
        }
        switch (seleccion_modo_pantalla) {
            case MODO_PANTALLA_1P:
                if (estado_juego != 9) {
                    funcion_80059A88(JUGADOR_UNO);
                    if (seleccion_modo == CONTRARRELOJ) {
                        funcion_8005995C();
                    }
                } else {
                    funcion_80059820(JUGADOR_UNO);
                }
                break;
            case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
                funcion_80059A88(JUGADOR_UNO);
                funcion_80059A88(JUGADOR_DOS);
                break;
            case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
                funcion_80059A88(JUGADOR_UNO);
                funcion_80059A88(JUGADOR_DOS);
                break;
            case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
                funcion_80059A88(JUGADOR_UNO);
                funcion_80059A88(JUGADOR_DOS);
                funcion_80059A88(JUGADOR_TRES);
                funcion_80059A88(JUGADOR_CUATRO);
                break;
        }
        funcion_8005A71C();
    }
}

void funcion_80059C50(void) {
    s32 algun_indice;
    s32 id_jugador;

    funcion_8005A3C0();
    for (algun_indice = 0; algun_indice < JUGADORES_NUM; algun_indice++) {
        id_jugador = gp_actual_carrera_jugador_id_por_puesto[algun_indice];
        gp_actual_carrera_personaje_id_por_puesto[algun_indice] = (jugador_uno + id_jugador)->id_personaje;
    }
    for (algun_indice = 0; algun_indice < JUGADORES_NUM; algun_indice++) {
        dato_8018CF98[algun_indice] = gp_actual_carrera_puesto_por_id_jugador[algun_indice];
    }
}

void funcion_80059D00(void) {

    funcion_8005A99C();
    funcion_8005A3C0();
    funcion_8005A380();

    if (dato_801657AE == 0) {
        switch (seleccion_modo_pantalla) {
            case MODO_PANTALLA_1P:
                aleatorizar_semilla_desde_mando(JUGADOR_UNO);
                if (dato_8018D214 == false) {
                    funcion_80059820(JUGADOR_UNO);
                    funcion_8005B914();
                    if (!modo_demo) {
                        funcion_8007AA44(0);
                    }
                    actualizar_nubes_circuito(0);
                    if (h_ud_jugador[JUGADOR_UNO].bool_completo_carrera == 0) {
                        funcion_8005C360((copia_jugador_uno->speed / 18.0f) * 216.0f);
                    }
                    funcion_8005D0FC(JUGADOR_UNO);
                } else {
                    funcion_80059820(JUGADOR_UNO);
                    actualizar_nubes_circuito(1);
                    funcion_80059820(JUGADOR_DOS);
                    actualizar_nubes_circuito(2);
                }
                actualizar_objeto();
                break;
            case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
                aleatorizar_semilla_desde_mando(JUGADOR_UNO);
                aleatorizar_semilla_desde_mando(JUGADOR_DOS);
                funcion_80059820(JUGADOR_UNO);
                funcion_8005D0FC(JUGADOR_UNO);
                if (!modo_demo) {
                    funcion_8007AA44(0);
                }
                actualizar_nubes_circuito(1);
                funcion_8005D1F4(0);
                funcion_80059820(JUGADOR_DOS);
                funcion_8005D0FC(JUGADOR_DOS);
                if (!modo_demo) {
                    funcion_8007AA44(1);
                }
                actualizar_nubes_circuito(2);
                funcion_8005D1F4(1);
                actualizar_objeto();
                break;
            case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
                aleatorizar_semilla_desde_mando(JUGADOR_UNO);
                aleatorizar_semilla_desde_mando(JUGADOR_DOS);
                funcion_80059820(JUGADOR_UNO);
                funcion_8005D0FC(JUGADOR_UNO);
                if (!modo_demo) {
                    funcion_8007AA44(0);
                }
                actualizar_nubes_circuito(3);
                funcion_8005D1F4(0);
                funcion_80059820(JUGADOR_DOS);
                funcion_8005D0FC(JUGADOR_DOS);
                if (!modo_demo) {
                    funcion_8007AA44(1);
                }
                actualizar_nubes_circuito(4);
                funcion_8005D1F4(1);
                actualizar_objeto();
                break;
            case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
                aleatorizar_semilla_desde_mando(JUGADOR_UNO);
                aleatorizar_semilla_desde_mando(JUGADOR_DOS);
                aleatorizar_semilla_desde_mando(JUGADOR_TRES);
                aleatorizar_semilla_desde_mando(JUGADOR_CUATRO);
                funcion_80059820(JUGADOR_UNO);
                funcion_8005D0FC(JUGADOR_UNO);
                if (!modo_demo) {
                    funcion_8007AA44(0);
                }
                funcion_8005D1F4(0);
                funcion_80059820(JUGADOR_DOS);
                funcion_8005D0FC(JUGADOR_DOS);
                if (!modo_demo) {
                    funcion_8007AA44(1);
                }
                funcion_8005D1F4(1);
                funcion_80059820(JUGADOR_TRES);
                funcion_8005D0FC(JUGADOR_TRES);
                if (!modo_demo) {
                    funcion_8007AA44(2);
                }
                funcion_8005D1F4(2);
                if (seleccion_cantidad_jugador_1 == 4) {
                    funcion_80059820(JUGADOR_CUATRO);
                    funcion_8005D0FC(JUGADOR_CUATRO);
                    if ((!modo_demo) && (seleccion_cantidad_jugador_1 == 4)) {
                        funcion_8007AA44(3);
                    }
                    funcion_8005D1F4(3);
                }
                actualizar_objeto();
                break;
        }
        funcion_800744CC();
    }
}

void funcion_8005A070(void) {
    funcion_8008C1D8(&dato_80165678);
    cantidad_hud_matriz = 0;
    dato_801655C0 = 0;
    funcion_80041D34();
    if (juego_en_pausa == false) {
        funcion_8005C728();
        if (estado_juego == FINAL) {
            funcion_80086604();
            funcion_80086D80();
            actualizar_cheep_cheep(1);
            funcion_80077640();
        } else if (estado_juego == SECUENCIA_CREDITOS) {
            funcion_80059820(JUGADOR_UNO);
            actualizar_nubes_circuito(0);
            actualizar_objeto();
        } else {
            funcion_80059D00();
        }
    }
    funcion_8008C204();
    funcion_8008C1E0(&dato_80165678, (s32) &dato_801655F0);
}

void funcion_8005A14C(s32 id_jugador) {
    s32 indice_objeto;
    s32 cantidad_vuelta;
    Jugador* jugador;
    SIN_USO s32 margen_pila;

    jugador = &jugador_uno[id_jugador];
    indice_objeto = dato_8018CE10[id_jugador].indice_objeto;
    cantidad_vuelta = cantidad_vuelta_por_id_jugador[id_jugador];
    if (jugador->type & EXISTE_JUGADOR) {
        if (jugador->efectos &
            (EFECTO_GOLPE_RAYO | GOLPE_POR_CAPARAZON_VERDE_EFECTO | EFECTO_TROMPO_BANANA | EFECTO_TROMPO_CONDUCIENDO)) {
            lista_objeto[indice_objeto].angulo_sentido[2] += 0x1000;
        } else {
            if (lista_objeto[indice_objeto].angulo_sentido[2] != 0) {
                lista_objeto[indice_objeto].angulo_sentido[2] += 0x1000;
            }
        }
        if (jugador->efectos & EFECTO_RAYO) {
            paso_f32_hacia(&lista_objeto[indice_objeto].escalado_tamanio, 0.3f, 0.02f);
        } else {
            paso_f32_hacia(&lista_objeto[indice_objeto].escalado_tamanio, 0.6f, 0.02f);
        }
        if (jugador->efectos & EFECTO_APLASTAMIENTO) {
            arriba_paso_u16_hacia(&lista_objeto[indice_objeto].angulo_sentido[0], 0x0C00U, 0x0100U);
        } else {
            abajo_paso_u16_hacia(&lista_objeto[indice_objeto].angulo_sentido[0], 0, 0x00000100);
        }
        if (jugador->efectos & (GOLPE_POR_EFECTO_ESTRELLA | EFECTO_ERROR_EXPLOSION)) {
            funcion_80087D24(indice_objeto, 6.0f, 1.5f, 0.0f);
        } else {
            paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], 0.0f, 1.0f);
        }
        if ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) || (jugador->efectos & BOO_EFECTO)) {
            lista_objeto[indice_objeto].prim_alpha = 0x0050;
        } else {
            lista_objeto[indice_objeto].prim_alpha = 0x00FF;
        }
        if (cantidad_vuelta >= 3) {
            lista_objeto[indice_objeto].angulo_sentido[2] = 0;
            lista_objeto[indice_objeto].angulo_sentido[1] = 0;
            lista_objeto[indice_objeto].angulo_sentido[0] = 0;
            lista_objeto[indice_objeto].offset[2] = 0.0f;
            lista_objeto[indice_objeto].offset[1] = 0.0f;
            lista_objeto[indice_objeto].offset[0] = 0.0f;
            lista_objeto[indice_objeto].escalado_tamanio = 0.6f;
            lista_objeto[indice_objeto].prim_alpha = 0x00FF;
        }
    }
}

void funcion_8005A380(void) {
    s32 temporal_s0;
    for (temporal_s0 = 0; temporal_s0 < JUGADORES_NUM; ++temporal_s0) {
        funcion_8005A14C(temporal_s0);
    }
}

void funcion_8005A3C0(void) {
    bool b = false;
    if ((estado_juego != FINAL) && (estado_juego != SECUENCIA_CREDITOS) && !dato_8018D204) {
        switch (seleccion_cantidad_jugador_1) {
            case 1:
                if (mando_uno->boton_pulsado & R_CBUTTONS) {
                    if (++dato_801657E4 >= 3) {
                        dato_801657E4 = 0;
                    }
                    if (dato_801657E4 == 2) {
                        dato_801657E8 = false;
                        dato_801657E6 = false;
                        dato_801657F0 = true;
                    } else if (dato_801657E4 == 1) {
                        dato_801657E8 = false;
                        dato_801657E6 = true;
                        dato_801657F0 = false;
                    } else {
                        dato_801657E8 = true;
                        dato_801657E6 = false;
                        dato_801657F0 = false;
                    }
                    b = true;
                }
                break;
            case 2:
                if (seleccion_modo != BATALLA) {
                    if (mando_uno->boton_pulsado & R_CBUTTONS) {
                        dato_80165800[0] = (dato_80165800[0] + 1) & 1;
                        b = true;
                    }
                    if (mando_dos->boton_pulsado & R_CBUTTONS) {
                        dato_80165800[1] = (dato_80165800[1] + 1) & 1;
                        b = true;
                    }
                    if (dato_80165800[0] && dato_80165800[1]) {
                        dato_801657F0 = false;
                    } else {
                        dato_801657F0 = true;
                    }
                    if (modo_demo) {
                        dato_801657F0 = false;
                    }
                }
                break;
            case 3:
                if ((mando_uno->boton_pulsado & R_CBUTTONS) || (mando_dos->boton_pulsado & R_CBUTTONS) ||
                    (mando_tres->boton_pulsado & R_CBUTTONS)) {
                    if (seleccion_modo != BATALLA) {
                        dato_801657F0 = (dato_801657F0 + 1) & 1;
                    }
                    dato_801657E4 = (dato_801657E4 + 1) & 1;
                    b = true;
                }
                break;
            case 4:
                if ((mando_uno->boton_pulsado & R_CBUTTONS) || (mando_dos->boton_pulsado & R_CBUTTONS) ||
                    (mando_tres->boton_pulsado & R_CBUTTONS) || (mando_cuatro->boton_pulsado & R_CBUTTONS)) {
                    dato_801657E4 = (dato_801657E4 + 1) & 1;
                    dato_801657F8 = (dato_801657F8 + 1) & 1;
                    dato_80165800[0] = (dato_80165800[0] + 1) & 1;
                    if (seleccion_modo != BATALLA) {
                        dato_801657F0 = (dato_801657F0 + 1) & 1;
                    }
                    b = true;
                }
                break;
        }
        if (b) {
            funcion_8006F824(1);
        }
    }
}

void funcion_8005A71C(void) {
    if (id_circuito_actual == CIRCUITO_BOWSER_CASTLE) {
        funcion_80081210();
    }
}

void actualizar_objeto(void) {
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_MARIO_RACEWAY:
        case CIRCUITO_CHOCO_MOUNTAIN:
            break;
        case CIRCUITO_BOWSER_CASTLE:
            funcion_80081208();
            actualizar_particula_llama();
            break;
        case CIRCUITO_BANSHEE_BOARDWALK:
            if (estado_juego != SECUENCIA_CREDITOS) {
                actualizar_bin_basura();
                funcion_8007E4C4();
                if (seleccion_modo != CONTRARRELOJ) {
                    actualizar_murcielago();
                }
                actualizar_boos_envoltorio();
                actualizar_cheep_cheep(0);
            }
            break;
        case CIRCUITO_YOSHI_VALLEY:
            funcion_80083080();
            if (estado_juego != SECUENCIA_CREDITOS) {
                actualizar_erizos();
            }
            break;
        case CIRCUITO_FRAPPE_SNOWLAND:
            if (estado_juego != SECUENCIA_CREDITOS) {
                actualizar_muniecos_nieve();
            }
            actualizar_copos();
            break;
        case CIRCUITO_KOOPA_BEACH:
            if (estado_juego != SECUENCIA_CREDITOS) {
                actualizar_cangrejos();
            }
            if ((cantidad_jugador == 1) || (cantidad_jugador == 2) || (estado_juego == SECUENCIA_CREDITOS)) {
                actualizar_gaviotas();
            }
            break;
        case CIRCUITO_LUIGI_RACEWAY:
            if (dato_80165898 != 0) {
                actualizar_globo_aerostatico();
            }
            break;
        case CIRCUITO_MOO_MOO_FARM:
            if (estado_juego != SECUENCIA_CREDITOS) {
                actualizar_topos();
            }
            break;
        case CIRCUITO_KALAMARI_DESERT:
            actualizar_humo_tren();
            break;
        case CIRCUITO_SHERBET_LAND:
            if (estado_juego != SECUENCIA_CREDITOS) {
                funcion_800842C8();
            }
            actualizar_pinguinos();
            break;
        case CIRCUITO_RAINBOW_ROAD:
            if (estado_juego != SECUENCIA_CREDITOS) {
                actualizar_neon();
                actualizar_chomps_cadena();
            }
            break;
        case CIRCUITO_DK_JUNGLE:
            actualizar_particula_humo_ferris();
            break;
    }
#else

#endif

    if (dato_80165730 != 0) {
        funcion_80074EE8();
    }
    funcion_80076F2C();
    if ((s16) id_circuito_actual != CIRCUITO_FRAPPE_SNOWLAND) {
        actualizar_hoja();
    }
}

void funcion_8005A99C(void) {
    if (dato_8018D170 == 0) {
        if (dato_8018D178 == 0) {
            if (seleccion_cantidad_jugador_1 == 1) {
                funcion_8005AA34();
            }
            if (seleccion_cantidad_jugador_1 == 3) {
                dato_801657E8 = true;
            }
            es_visible_hud = (s32) 1;
            dato_8018D170 = (s32) 1;
            dato_8018D190 = (s32) 1;
            dato_8018D204 = 0;
            return;
        }
        --dato_8018D178;
    }
}

void funcion_8005AA34(void) {
    dato_8018D1CC = 1;
    dato_8018D1A0 = 0;
}

void funcion_8005AA4C(void) {
    ++dato_8018D1CC;
    dato_8018D1A0 = 0;
}

void funcion_8005AA6C(s32 parametro0) {
    dato_8018D1CC = parametro0;
    dato_8018D1A0 = 0;
}

void funcion_8005AA80(void) {
    dato_8018D1CC = 0;
    dato_8018D1A0 = 0;
}

void funcion_8005AA94(s32 parametro0) {
    if (dato_8018D1A0 == 0) {
        dato_8018D1D4 = parametro0;
        dato_8018D1A0 = 1;
    }

    --dato_8018D1D4;
    if (dato_8018D1D4 < 0) {
        dato_8018D1A0 = 0;
        funcion_8005AA4C();
    }
}

void funcion_8005AAF0(void) {
    dato_8018D1B4 = 1;
    dato_8018D1A0 = 0;
    funcion_8005AA4C();
}

void funcion_8005AB20(void) {
    if ((seleccion_modo == GRAN_PREMIO) && (seleccion_cantidad_jugador_1 == 1)) {
        funcion_8005AA6C(0x14);
    }
}
