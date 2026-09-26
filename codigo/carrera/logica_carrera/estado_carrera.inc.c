// Estado carrera

#pragma intrinsic(sqrtf)

extern s16 cantidad_globo_jugador[];
extern s16 dato_8016348C;

extern s32 cantidad_vuelta_por_id_jugador[];
extern u16 dato_802BA048;

extern s32 dato_8018D2AC;
extern s32 dato_802B91E0;

u16 dato_802BA030;
u16 dato_802BA032;

float dato_802BA034;

s32 temporizador_demo;
SIN_USO s32 dato_802BA03C;

s16 dato_802BA040[4];
u16 dato_802BA048;

void funcion_8028DF00(void) {
    struct Mando* mandos_2 = &mandos[0];
    s32 i;
    for (i = 0; i < 4; i++) {
        dato_802BA040[i] = mandos_2->button;
        mandos_2++;
    }
}

void funcion_8028DF38(void) {
    struct Mando* mandos_2 = &mandos[0];
    s32 i;
    for (i = 0; i < 4; i++) {
        mandos_2->boton_pulsado = (mandos_2->button & (dato_802BA040[i] ^ mandos_2->button));
        mandos_2->boton_apretado = (dato_802BA040[i] & (dato_802BA040[i] ^ mandos_2->button));
        mandos_2->button = dato_802BA040[i];
        mandos_2++;
    }
}

void funcion_8028E028(void) {

    switch (seleccion_cantidad_jugador_1) {
        case 2:
            *(desconocido_nmi_4 + indice_ganador_jugador) += 1;
            break;
        case 3:
            *(desconocido_nmi_5 + indice_ganador_jugador) += 1;
            break;
        case 4:
            *(desconocido_nmi_6 + indice_ganador_jugador) += 1;
            break;
    }
    funcion_800CA118((u8) indice_ganador_jugador);
    estado_carrera = HECHO_CARRERA;
    temporizador_demo = 10;
}

void actualizar_situacion_batalla_jugador(void) {
    Jugador* jugador;
    s32 indice_jugador;
    s16 vivo_jugadores[4];
    s16 muerto_jugadores[4];
    s16 contador_vivo = 0;
    s16 contador_muerto = 0;

    for (indice_jugador = 0; indice_jugador < 4; indice_jugador++) {
        jugador = &jugadores[indice_jugador];
        if (!(jugador->type & EXISTE_JUGADOR)) {
            continue;
        }
        if (jugador->type & MODO_CINEMATICA_JUGADOR) {
            continue;
        }
        if (cantidad_globo_jugador[indice_jugador] < 0) {
            jugador->type |= MODO_CINEMATICA_JUGADOR;
            muerto_jugadores[contador_muerto] = (s16) (jugador - jugador_uno);
            contador_muerto++;
            funcion_800CA118((u8) indice_jugador);
        } else {
            vivo_jugadores[contador_vivo] = (s16) (jugador - jugador_uno);
            contador_vivo++;
        }
    }
    if (contador_vivo == 1) {
        indice_ganador_jugador = (s32) vivo_jugadores[0];
        funcion_8028E028();
    } else if (contador_vivo == 0) {
        indice_ganador_jugador = (s32) muerto_jugadores[0];
        funcion_8028E028();
    }
}

void funcion_8028E298(void) {
    f32 temporal_v0;
    s32 i;
    u16 temporal_a2;

    for (i = 0; i < JUGADORES_NUM; i++) {

        if ((jugadores[i].type & MODO_CINEMATICA_JUGADOR)) {
            continue;
        }
        temporal_a2 = indice_camino_por_id_jugador[i];

        temporal_v0 = ((2 - jugadores[i].cantidad_vuelta) * cantidad_camino_por_indice_camino[temporal_a2]);
        temporal_v0 += cantidad_camino_por_indice_camino[temporal_a2] * (1.0f - porciento_finalizacion_vuelta_por_id_jugador[i]);
        temporal_v0 /= 15.0f;

        tiempo_jugador_ultimo_tocado_linea_meta[i] = temporizador_circuito + temporal_v0;
    }
    dato_8016348C = 1;
    actualizar_clasificacion_jugador();
}

void funcion_8028E3A0(void) {

    if (dato_80150120) {

        if (indice_circuito_en_copa == CIRCUITO_CUATRO) {
            modo_goto = FINAL;
        } else {
            dato_800DC544++;
            indice_circuito_en_copa++;
            modo_goto = CARRERA;
        }
    } else {
        dato_800DC544++;
        indice_circuito_en_copa++;
        modo_goto = CARRERA;
    }
}

void funcion_8028E438(void) {
    struct desconocido_struct_800DC5EC* temporal_v0 = &dato_8015F480[indice_ganador_jugador];
    s32 phi_v1_4;

    dato_800DC5B0 = 1;

    switch (dato_8015F894) {
        case 0:
            dato_800DC5B8 = 0;
            dato_8015F894 = 1;
            if (seleccion_cantidad_jugador_1 == 3) {
                funcion_800925CC();
            }
            break;
        case 1:
            if (temporal_v0->ancho_pantalla < ANCHO_PANTALLA) {
                temporal_v0->ancho_pantalla += 2;
            }
            if (temporal_v0->altura_pantalla < ALTURA_PANTALLA) {
                temporal_v0->altura_pantalla += 2;
            }
            if (temporal_v0->inicio_x_pantalla < 160) {
                temporal_v0->inicio_x_pantalla += 1;

            } else if (temporal_v0->inicio_x_pantalla > 160) {
                temporal_v0->inicio_x_pantalla -= 1;
            }
            if (temporal_v0->inicio_y_pantalla < 120) {
                temporal_v0->inicio_y_pantalla += 1;
            } else if (temporal_v0->inicio_y_pantalla > 120) {
                temporal_v0->inicio_y_pantalla -= 1;
            }
            phi_v1_4 = 0;

            if (temporal_v0->altura_pantalla >= ALTURA_PANTALLA) {
                phi_v1_4++;
                temporal_v0->altura_pantalla = ALTURA_PANTALLA;
            }
            if (temporal_v0->ancho_pantalla >= ANCHO_PANTALLA) {
                temporal_v0->ancho_pantalla = ANCHO_PANTALLA;
                phi_v1_4++;
            }

            if (temporal_v0->inicio_y_pantalla == 120) {
                phi_v1_4++;
            }
            if (temporal_v0->inicio_x_pantalla == 160) {
                phi_v1_4++;
            }
            aspecto_pantalla = (f32) ((f32) temporal_v0->ancho_pantalla / (f32) temporal_v0->altura_pantalla);
            if (phi_v1_4 == 4) {
                dato_8015F894 = 2;
                modo_pantalla_activo = MODO_PANTALLA_1P;
                dato_800DC5EC->ancho_pantalla = temporal_v0->ancho_pantalla;
                dato_800DC5EC->altura_pantalla = temporal_v0->altura_pantalla;
                dato_800DC5EC->inicio_x_pantalla = temporal_v0->inicio_x_pantalla;
                dato_800DC5EC->inicio_y_pantalla = temporal_v0->inicio_y_pantalla;
                if (seleccion_modo == BATALLA) {
                    funcion_80092604();
                } else if (seleccion_modo == VERSUS) {
                    funcion_80092604();
                    funcion_80019DF4();
                } else {
                    funcion_80092564();
                    estado_carrera = RESULTADOS_CUADRANTE_CARRERA;
                }
            }
            break;
        case 2:
            break;
    }
}

void funcion_8028E678(void) {
    s32 phi_a0_10 = 0;

    dato_800DC5B0 = 1;

    switch (dato_8015F894) {
        case 0:
            switch (seleccion_modo) {
                case GRAN_PREMIO:
                case VERSUS:
                    break;
                case CONTRARRELOJ:
                    break;
            }
            dato_800DC5B8 = 0;
            switch (seleccion_modo_pantalla) {
                case MODO_PANTALLA_1P:
                    dato_8015F894 = 1;
                    break;
                case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
                    dato_8015F894 = 5;
                    break;
                case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
                    dato_8015F894 = 6;
                    break;
            }
            break;
        case 5:
            dato_800DC5EC->ancho_pantalla -= 4;

            dato_800DC5F0->ancho_pantalla -= 4;

            dato_800DC5EC->inicio_x_pantalla -= 2;

            dato_800DC5F0->inicio_x_pantalla += 2;

            if (dato_800DC5EC->ancho_pantalla < 160) {
                dato_800DC5EC->ancho_pantalla = 160;
                phi_a0_10++;
            }

            if (dato_800DC5F0->ancho_pantalla < 160) {
                dato_800DC5F0->ancho_pantalla = 160;
                phi_a0_10++;
            }

            if (dato_800DC5EC->inicio_x_pantalla < 80) {
                dato_800DC5EC->inicio_x_pantalla = 80;
                phi_a0_10++;
            }

            if (dato_800DC5F0->inicio_x_pantalla > ALTURA_PANTALLA) {
                dato_800DC5F0->inicio_x_pantalla = ALTURA_PANTALLA;
                phi_a0_10++;
            }

            aspecto_pantalla = (f32) ((f32) dato_800DC5EC->ancho_pantalla / (f32) dato_800DC5EC->altura_pantalla);
            if (phi_a0_10 == 4) {
                dato_8015F894 = 3;
                funcion_80092500();
                funcion_80019DE4();
                funcion_80041D24();
            }
            break;
        case 6:
            dato_800DC5EC->altura_pantalla -= 4;
            dato_800DC5F0->altura_pantalla -= 4;
            dato_800DC5EC->inicio_y_pantalla -= 2;
            dato_800DC5F0->inicio_y_pantalla += 2;

            if (dato_800DC5EC->altura_pantalla < 120) {
                dato_800DC5EC->altura_pantalla = 120;
                phi_a0_10++;
            }

            if (dato_800DC5F0->altura_pantalla < 120) {
                dato_800DC5F0->altura_pantalla = 120;
                phi_a0_10++;
            }

            if (dato_800DC5EC->inicio_y_pantalla < 60) {
                dato_800DC5EC->inicio_y_pantalla = 60;
                phi_a0_10++;
            }

            if (dato_800DC5F0->inicio_y_pantalla > 180) {
                dato_800DC5F0->inicio_y_pantalla = 180;
                phi_a0_10++;
            }

            aspecto_pantalla = (f32) ((f32) dato_800DC5EC->ancho_pantalla / (f32) dato_800DC5EC->altura_pantalla);
            if (phi_a0_10 == 4) {
                dato_8015F894 = 3;
                funcion_80092500();
                funcion_80019DE4();
            }
            break;
        case 1:
            dato_800DC5EC->altura_pantalla -= 2;
            dato_800DC5EC->ancho_pantalla = (dato_800DC5EC->altura_pantalla * ANCHO_PANTALLA) / ALTURA_PANTALLA;

            if (dato_800DC5EC->altura_pantalla < 120) {

                dato_800DC5EC->altura_pantalla = 120;
                dato_800DC5EC->ancho_pantalla = (dato_800DC5EC->altura_pantalla * ANCHO_PANTALLA) / ALTURA_PANTALLA;
                dato_8015F894 = 2;

                dato_800DC5F0->ancho_pantalla = dato_800DC5EC->ancho_pantalla;
                dato_800DC5F0->altura_pantalla = dato_800DC5EC->altura_pantalla;
                dato_800DC5F0->inicio_x_pantalla = dato_800DC5EC->inicio_x_pantalla;
                dato_800DC5F0->inicio_y_pantalla = dato_800DC5EC->inicio_y_pantalla;

                modo_pantalla_activo = PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL;
                aspecto_pantalla = 1.33333337;
                seleccion_cantidad_jugador_1 = 2;
                funcion_8003DB5C();
                funcion_8005994C();
            }
            break;
        case 2:
            dato_800DC5EC->inicio_x_pantalla -= 4;

            dato_800DC5EC->inicio_y_pantalla -= 2;

            if (dato_800DC5EC->inicio_x_pantalla < 80) {
                dato_800DC5EC->inicio_x_pantalla = 80;
                phi_a0_10++;
            }

            if (dato_800DC5EC->inicio_y_pantalla < 60) {
                dato_800DC5EC->inicio_y_pantalla = 60;
                phi_a0_10++;
            }
            dato_800DC5F0->inicio_x_pantalla += 4;
            dato_800DC5F0->inicio_y_pantalla += 2;

            if (dato_800DC5F0->inicio_x_pantalla > ALTURA_PANTALLA) {
                dato_800DC5F0->inicio_x_pantalla = ALTURA_PANTALLA;
                phi_a0_10++;
            }
            if (dato_800DC5F0->inicio_y_pantalla > 180) {
                dato_800DC5F0->inicio_y_pantalla = 180;
                phi_a0_10++;
            }
            if (phi_a0_10 == 4) {
                dato_8015F894 = 7;
                dato_802BA030 = 3;
            }
            break;
        case 7:
            dato_802BA030--;
            if (dato_802BA030 == 0) {
                dato_8015F894 = 3;
                funcion_80092500();
                if (seleccion_modo == GRAN_PREMIO) {
                    funcion_80019DE4();
                } else {
                    funcion_80019E58();
                }
            }
            break;
        case 4:
            es_en_abandonar_a_transicion_menu = 1;
            abandonar_a_contador_transicion_menu = 5;
            estado_carrera = RESULTADOS_CUADRANTE_CARRERA;
            funcion_8028E3A0();
            break;
    }
}

SIN_USO void funcion_8028EC38(s32 parametro0) {
    modo_goto = parametro0;
    estado_carrera = ABANDONANDO_CARRERA;
    funcion_800CA330(25);
    funcion_800CA388(25);
    dato_800DC5B4 = 1;
    dato_800DC5B0 = 1;
    dato_800DC5B8 = 0;
    temporizador_demo = 5;
}

void reproducir_musica_para_pista_actual(s32 pista) {

    if (seleccion_modo_pantalla == PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
        return;
    }

    funcion_800029B0();

    switch (pista) {
        case CIRCUITO_MARIO_RACEWAY:
        case CIRCUITO_ROYAL_RACEWAY:
        case CIRCUITO_LUIGI_RACEWAY:
        case CIRCUITO_WARIO_STADIUM:
            reproducir_secuencia(SEC_RACEWAY_PISTA);
            break;

        case CIRCUITO_TOADS_TURNPIKE:
            reproducir_secuencia(SEC_TURNPIKE_PISTA);
            break;

        case CIRCUITO_YOSHI_VALLEY:
        case CIRCUITO_MOO_MOO_FARM:
            reproducir_secuencia(SEC_FARM_PISTA);
            break;

        case CIRCUITO_CHOCO_MOUNTAIN:
        case CIRCUITO_BLOCK_FORT:
        case CIRCUITO_DOUBLE_DECK:
            reproducir_secuencia(SEC_MONTANIA_PISTA);
            break;

        case CIRCUITO_KALAMARI_DESERT:
            reproducir_secuencia(SEC_DESIERTO_PISTA);
            break;

        case CIRCUITO_KOOPA_BEACH:
            reproducir_secuencia(SEC_BEACH_PISTA);
            break;

        case CIRCUITO_BOWSER_CASTLE: // Bowser Castle
            reproducir_secuencia(SEC_CASTILLO_PISTA);
            break;

        case CIRCUITO_BANSHEE_BOARDWALK:
            reproducir_secuencia(SEC_ATERRADOR_PISTA);
            break;

        case CIRCUITO_FRAPPE_SNOWLAND:
        case CIRCUITO_SHERBET_LAND:
            reproducir_secuencia(SEC_NIEVE_PISTA);
            break;

        case CIRCUITO_RAINBOW_ROAD:
            reproducir_secuencia(SEC_RAINBOW_PISTA);
            break;

        case CIRCUITO_DK_JUNGLE:
            reproducir_secuencia(SEC_JUNGLE_PISTA);
            break;

        case CIRCUITO_SKYSCRAPER: // Other Battle Stages
        case CIRCUITO_BIG_DONUT:
            reproducir_secuencia(SEC_BATALLA_PISTA);
            break;

#ifdef AVOID_UB
		default:
		    reproducir_secuencia(SEC_RACEWAY_PISTA);
			break;
#endif
    }
}

void empezar_carrera(void) {
    s32 i;

    dato_8015011E = -1;
    if (!modo_demo) {
        reproducir_musica_para_pista_actual(id_circuito_actual);
    }

    if (estado_carrera == PREPARACION_CARRERA) {
        estado_carrera = CARRERA_EN_PROGRESO;
    }

    for (i = 0; i < JUGADORES_NUM; i++) {

        if ((jugadores[i].type & EXISTE_JUGADOR) == 0) {
            continue;
        }

        if (jugadores[i].type & SECUENCIA_INICIO_JUGADOR) {
            jugadores[i].type ^= SECUENCIA_INICIO_JUGADOR;
        }
    }
}

f32 funcion_8028EE8C(s32 parametro0) {
    f32 temporal_v0 = jugadores[parametro0].pos[2];
    f32 temporal_v1 = jugadores[parametro0].pos_viejo[2];
    f32 temporal_f14 = dato_8015F8D0[2] - temporal_v0;
    f32 temporal_f16 = temporal_v1 - dato_8015F8D0[2];
    return temporizador_circuito - ((circuito_temporizador_iter_f * temporal_f14) / (temporal_f14 + temporal_f16));
}

void agregar_modo_cinematica(s32 i) {
    jugadores[i].type |= MODO_CINEMATICA_JUGADOR;
}

void funcion_8028EF28(void) {
    s16 posicion_actual;
    s32 id_jugador;

    for (id_jugador = 0; id_jugador < JUGADORES_NUM; id_jugador++) {
        Jugador* jugador = &jugadores[id_jugador];

        if ((jugador->type & EXISTE_JUGADOR) == 0) {
            continue;
        }

        if (cantidad_vuelta_por_id_jugador[id_jugador] < jugador->cantidad_vuelta) {
            jugador->cantidad_vuelta--;
        } else if (cantidad_vuelta_por_id_jugador[id_jugador] > jugador->cantidad_vuelta) {
            jugador->cantidad_vuelta++;
            if ((jugador->type & HUMANO_JUGADOR) != 0) {
                if (jugador->cantidad_vuelta == 3) {
                    agregar_modo_cinematica(id_jugador);

                    posicion_actual = jugador->puesto_actual;
                    jugador->type |= CPU_JUGADOR;

                    if (posicion_actual < 4) {
                        dato_80150120 = 1;
                    }

                    funcion_800CA118((u8) id_jugador);
                    if ((dato_802BA032 & EXISTE_JUGADOR) == 0) {
                        dato_802BA032 |= EXISTE_JUGADOR;
                    }

                    if (seleccion_modo == GRAN_PREMIO && seleccion_cantidad_jugador_1 == 2 && dato_802BA048 == 0) {
                        dato_802BA048 = 1;
                    }
                    if ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) == 0) {
                        estado_carrera = CARRERA_HUMANO_TERMINADO;
                    }
                    if (seleccion_modo == CONTRARRELOJ) {
                        funcion_80005AE8(jugador);
                    }

                    if (seleccion_modo == VERSUS) {
                        temporizador_demo = 180;
                        if (posicion_actual == 0) {
                            indice_ganador_jugador = id_jugador;
                        }
                        switch (seleccion_cantidad_jugador_1) {
                            case 2:
                                if (posicion_actual == 0) {
                                    *(nmi_g_versus_resultados_2_p + id_jugador) += 1;
                                }
                                if (*(nmi_g_versus_resultados_2_p + id_jugador) > 99) {
                                    *(nmi_g_versus_resultados_2_p + id_jugador) = 99;
                                }
                                estado_carrera = HECHO_CARRERA;
                                id_jugador = lut_posicion_jugador[1];
                                jugadores[id_jugador].disparadores |= DISPARADOR_TROMPO;
                                jugadores[id_jugador].type |= CPU_JUGADOR;
                                funcion_800CA118((u8) id_jugador);
                                break;
                            case 3:
                                if (posicion_actual < 3) {
                                    *(nmi_g_versus_resultados_3_p + id_jugador * 3 + posicion_actual) += 1;
                                }
                                if (*(nmi_g_versus_resultados_3_p + id_jugador * 3 + posicion_actual) > 99) {
                                    *(nmi_g_versus_resultados_3_p + id_jugador * 3 + posicion_actual) = 99;
                                }
                                if (posicion_actual == 1) {
                                    estado_carrera = HECHO_CARRERA;

                                    id_jugador = lut_posicion_jugador[2];
                                    *(nmi_g_versus_resultados_3_p + id_jugador * 3 + 2) += 1;
                                    if (*(nmi_g_versus_resultados_3_p + id_jugador * 3 + 2) > 99) {
                                        *(nmi_g_versus_resultados_3_p + id_jugador * 3 + 2) = 99;
                                    }
                                    jugadores[id_jugador].disparadores |= DISPARADOR_TROMPO;
                                    jugadores[id_jugador].type |= CPU_JUGADOR;
                                    funcion_800CA118((u8) id_jugador);
                                }
                                break;
                            case 4:
                                if (posicion_actual < 3) {
                                    *(nmi_g_versus_resultados_4_p + id_jugador * 3 + posicion_actual) += 1;
                                }
                                if (*(nmi_g_versus_resultados_4_p + id_jugador * 3 + posicion_actual) > 99) {
                                    *(nmi_g_versus_resultados_4_p + id_jugador * 3 + posicion_actual) = 99;
                                }
                                if (posicion_actual == 2) {
                                    estado_carrera = HECHO_CARRERA;
                                    id_jugador = lut_posicion_jugador[3];
                                    jugadores[id_jugador].disparadores |= DISPARADOR_TROMPO;
                                    jugadores[id_jugador].type |= CPU_JUGADOR;
                                    funcion_800CA118((u8) id_jugador);
                                }
                                break;
                        }
                    }

                } else if (jugador->cantidad_vuelta == 2) {
                    if ((jugador->type & 0x100) != 0) {
                        return;
                    }
                    if ((dato_802BA032 & 0x4000) == 0) {
                        dato_802BA032 |= 0x4000;
                        funcion_800CA49C((u8) id_jugador);
                    }
                }
            } else if (jugador->cantidad_vuelta == 3) {
                agregar_modo_cinematica(id_jugador);
                if (seleccion_modo == CONTRARRELOJ) {
                    funcion_80005AE8(jugador);
                }
            }
        }
    }
    if ((dato_802BA048 != 0) && (dato_802BA048 != 100)) {
        dato_802BA048 = 100;
        fijar_circuito_fin_puestos_con_tiempo();
    }
}

void funcion_8028F3E8(void) {
}

void actualizar_datos_posicion_carrera(void) {
    s16 id_jugador;
    s16 posicion;

    for (id_jugador = 0; id_jugador < JUGADORES_NUM; id_jugador++) {
        if (((jugadores[id_jugador].type & EXISTE_JUGADOR) != 0) && ((jugadores[id_jugador].type & MODO_CINEMATICA_JUGADOR) == 0) &&
            ((jugadores[id_jugador].type & INVISIBLE_JUGADOR_O_BOMBA) == 0)) {
            posicion = gp_actual_carrera_puesto_por_id_jugador[id_jugador];
            jugadores[id_jugador].puesto_actual = posicion;
            lut_posicion_jugador[posicion] = id_jugador;
        }
    }
}

void funcion_8028F474(void) {
    s32 i;

    switch (estado_carrera) {
        case CARRERA_EN_PROGRESO:
        case CARRERA_HUMANO_TERMINADO:
        case HECHO_CARRERA:
        case RESULTADOS_CUADRANTE_CARRERA:
            for (i = 0; i < JUGADORES_NUM; i++) {
                actualizar_jugador(i);
            }
        case PREP_CARRERA:
        case PREPARACION_CARRERA:
            actualizar_vehiculos();
            break;
    }
}

void funcion_8028F4E8(void) {
    if (modo_depuracion_activacion) {
        if (((mando_cinco->button & R_TRIG) != 0) && ((mando_cinco->button & L_TRIG) != 0) &&
            ((mando_cinco->button & A_BUTTON) != 0) && ((mando_cinco->button & B_BUTTON) != 0)) {

            funcion_800CA330(0x19);
            funcion_800CA388(0x19);
            modo_goto = MENU_INICIO_DESDE_ABANDONAR;
            estado_carrera = ABANDONANDO_CARRERA;
            dato_800DC5B4 = 1;
            dato_800DC5B0 = 1;
            dato_800DC5B8 = 0;
            temporizador_demo = 5;
        }
    }
}

void funcion_8028F588(void) {
    s16 ancho_pantalla;

    switch (modo_pantalla_activo) { /* irregular */
        case MODO_PANTALLA_1P:
            ancho_pantalla = (s16) (s32) (320.0f * dato_802BA034);
            if (ancho_pantalla < 0) {
                ancho_pantalla = 1;
            }
            dato_800DC5EC->ancho_pantalla = ancho_pantalla;
            ancho_pantalla = (s16) (s32) (240.0f * dato_802BA034);
            if (ancho_pantalla < 0) {
                ancho_pantalla = 1;
            }
            dato_800DC5EC->altura_pantalla = ancho_pantalla;
            break;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            ancho_pantalla = (s16) (s32) (160.0f * dato_802BA034);
            if (ancho_pantalla <= 0) {
                ancho_pantalla = 1;
            } else if (ancho_pantalla >= 0x140) {
                ancho_pantalla = 0x013C;
            }
            dato_800DC5EC->ancho_pantalla = ancho_pantalla;
            dato_800DC5F0->ancho_pantalla = ancho_pantalla;
            ancho_pantalla = (s16) (s32) (240.0f * dato_802BA034);
            if (ancho_pantalla <= 0) {
                ancho_pantalla = 1;
            } else if (ancho_pantalla >= 0x1E0) {
                ancho_pantalla = 0x01DC;
            }
            dato_800DC5EC->altura_pantalla = ancho_pantalla;
            dato_800DC5F0->altura_pantalla = ancho_pantalla;
            break;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
            ancho_pantalla = (s16) (s32) (320.0f * dato_802BA034);
            if (ancho_pantalla <= 0) {
                ancho_pantalla = 1;
            } else if (ancho_pantalla >= 0x280) {
                ancho_pantalla = 0x027C;
            }
            dato_800DC5EC->ancho_pantalla = ancho_pantalla;
            dato_800DC5F0->ancho_pantalla = ancho_pantalla;
            ancho_pantalla = (s16) (s32) (120.0f * dato_802BA034);
            if (ancho_pantalla <= 0) {
                ancho_pantalla = 1;
            } else if (ancho_pantalla >= 0xF0) {
                ancho_pantalla = 0x00EC;
            }
            dato_800DC5EC->altura_pantalla = ancho_pantalla;
            dato_800DC5F0->altura_pantalla = ancho_pantalla;
            break;
        case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
            ancho_pantalla = (s16) (s32) (160.0f * dato_802BA034);
            if (ancho_pantalla <= 0) {
                ancho_pantalla = 1;
            } else if (ancho_pantalla >= 0x140) {
                ancho_pantalla = 0x013C;
            }
            dato_800DC5EC->ancho_pantalla = ancho_pantalla;
            dato_800DC5F0->ancho_pantalla = ancho_pantalla;
            dato_800DC5F4->ancho_pantalla = ancho_pantalla;
            dato_800DC5F8->ancho_pantalla = ancho_pantalla;
            ancho_pantalla = (s16) (s32) (120.0f * dato_802BA034);
            if (ancho_pantalla <= 0) {
                ancho_pantalla = 1;
            } else if (ancho_pantalla >= 0xF0) {
                ancho_pantalla = 0x00EC;
            }
            dato_800DC5EC->altura_pantalla = ancho_pantalla;
            dato_800DC5F0->altura_pantalla = ancho_pantalla;
            dato_800DC5F4->altura_pantalla = ancho_pantalla;
            dato_800DC5F8->altura_pantalla = ancho_pantalla;
            break;
    }
}

void funcion_8028F8BC(void) {
    dato_802BA034 = (f32) (dato_802BA034 - 0.017f);
    if (dato_802BA034 < 0.0f) {
        dato_802BA034 = 0.0f;
    }
    funcion_8028F588();
}

void funcion_8028F914(void) {
    dato_802BA034 = (f32) (dato_802BA034 + 0.028f);
    if (dato_802BA034 > 1.0f) {
        dato_802BA034 = 1.0f;
    }
    funcion_8028F588();
}

void funcion_8028F970(void) {
    s32 i;

    if (dato_8015F890) {
        return;
    }

    for (i = 0; i < 4; i++) {

        Jugador* jugador = &jugadores[i];
        struct Mando* mando = &mandos[i];

        if (!(jugador->type & HUMANO_JUGADOR)) {
            continue;
        }
        if (jugador->type & CPU_JUGADOR) {
            continue;
        }

        if (modo_pantalla_activo != PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
            if ((mando->boton_pulsado & L_TRIG) && !(mando->button & R_TRIG)) {
                mando->boton_pulsado &= ~L_TRIG;

                dato_800DC5A8++;
                if (dato_800DC5A8 >= 3) {
                    dato_800DC5A8 = 0;
                }
                reproducir_sonido2(SONIDO_PING_ACCION);
                funcion_800029B0();
            }
        }
        if ((mando->boton_pulsado & START_BUTTON) && (!(mando->button & R_TRIG)) &&
            (!(mando->button & L_TRIG))) {
            funcion_8028DF00();
            juego_en_pausa = (mando - mando_uno) + 1;
            mando->boton_pulsado = 0;
            funcion_800C9F90(1);
            pausa_disparado = 1;
            if (seleccion_modo == CONTRARRELOJ) {
                if (jugador_uno->type & (EXISTE_JUGADOR | INVISIBLE_JUGADOR_O_BOMBA)) {
                    funcion_80005AE8(jugador_uno);
                }
                if (jugador_dos->type & (EXISTE_JUGADOR | INVISIBLE_JUGADOR_O_BOMBA)) {
                    funcion_80005AE8(jugador_dos);
                }
                if (jugador_tres->type & (EXISTE_JUGADOR | INVISIBLE_JUGADOR_O_BOMBA)) {
                    funcion_80005AE8(jugador_tres);
                }
            }
            return;
        }
    }

    if (modo_depuracion_activacion) {
        if (seleccion_modo == BATALLA) {
        } else {
            if (mando_uno->boton_pulsado & U_JPAD) {
                cantidad_vuelta_por_id_jugador[0] = 2;
            }
            if (mando_uno->boton_pulsado & R_JPAD) {
                cantidad_vuelta_por_id_jugador[0] = 2;
                cantidad_vuelta_por_id_jugador[1] = 2;
            }
            if (mando_uno->boton_pulsado & D_JPAD) {
                cantidad_vuelta_por_id_jugador[0] = 2;
                cantidad_vuelta_por_id_jugador[1] = 2;
                cantidad_vuelta_por_id_jugador[2] = 2;
                cantidad_vuelta_por_id_jugador[3] = 2;
                cantidad_vuelta_por_id_jugador[4] = 2;
                cantidad_vuelta_por_id_jugador[5] = 2;
                cantidad_vuelta_por_id_jugador[6] = 2;
                cantidad_vuelta_por_id_jugador[7] = 2;
            }
        }
    }
}

void funcion_8028FBD4(void) {
    modo_goto = MENU_INICIO_DESDE_ABANDONAR;
    estado_carrera = ABANDONANDO_CARRERA;
    funcion_800CA330(25);
    funcion_800CA388(25);
    dato_800DC5B4 = 1;
    dato_800DC5B0 = 1;
    dato_800DC5B8 = 0;
    temporizador_demo = 5;
}

#ifdef VERSION_EU
#define demo_temporizador_tamanio 1600
#else
#define demo_temporizador_tamanio 1920
#endif

void actualizar_demo_fin(void) {
    if (temporizador_demo < 0) {
        temporizador_demo = demo_temporizador_tamanio;
        return;
    }
    temporizador_demo--;
    if (mando_cinco->boton_pulsado != 0) {
        funcion_8028FBD4();
        seleccion_menu = MENU_INICIO;
        return;
    }
    if (temporizador_demo == 0) {
        funcion_8028FBD4();
        seleccion_menu = LOGO_INTRO_MENU;
    }
}
