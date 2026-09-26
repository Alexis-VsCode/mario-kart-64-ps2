// Particulas jugador

void funcion_8005CB60(s32 id_jugador, s32 cantidad_vuelta) {
    s32 temporal_a0_2;
    SIN_USO s32 margen_pila;
    s8* huh;
    s8* huhthedeuce;
    Jugador* jugador;

    jugador = &jugador_uno[id_jugador];
    huh = &h_ud_jugador[id_jugador].cantidad_vuelta_tambien;
    huhthedeuce = &h_ud_jugador[id_jugador].cantidad_vuelta;
    if (h_ud_jugador[id_jugador].cantidad_vuelta < dato_8018D320) {
        h_ud_jugador[id_jugador].algun_temporizador = (u32) (s32) (temporizador_circuito * 100.0f);
        if (*huh < cantidad_vuelta) {
            temporal_a0_2 = tiempo_jugador_ultimo_tocado_linea_meta[id_jugador] * 100.0f;
            h_ud_jugador[id_jugador].tiempo_ultimo_tocado_linea_meta = temporal_a0_2;
            h_ud_jugador[id_jugador].veces_finalizacion_vuelta[*huh] = temporal_a0_2;
            if (*huh == 0) {
                h_ud_jugador[id_jugador].duraciones_vuelta[*huh] = h_ud_jugador[id_jugador].tiempo_ultimo_tocado_linea_meta;
            } else {
                h_ud_jugador[id_jugador].duraciones_vuelta[*huh] =
                    h_ud_jugador[id_jugador].veces_finalizacion_vuelta[*huh] - h_ud_jugador[id_jugador].veces_finalizacion_vuelta[*huh - 1];
            }
            h_ud_jugador[id_jugador].algun_temporizador_1 = h_ud_jugador[id_jugador].duraciones_vuelta[*huh];
            h_ud_jugador[id_jugador].temporizador_parpadear = 0x003C;
            if (cantidad_vuelta == 3) {
                h_ud_jugador[id_jugador].algun_temporizador = h_ud_jugador[id_jugador].veces_finalizacion_vuelta[*huh];
            }
            if (seleccion_modo == (s32) 1) {
                if (dato_80165638 >= h_ud_jugador[id_jugador].algun_temporizador_1) {
                    if (dato_80165638 != h_ud_jugador[id_jugador].algun_temporizador_1) {
                        dato_80165658[0] = dato_80165658[1] = 0;
                    }
                    funcion_800C90F4(0U, (jugador->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x0D));
                    dato_80165638 = h_ud_jugador[id_jugador].algun_temporizador_1;
                    dato_80165658[cantidad_vuelta - 1] = 1;
                    dato_801657E3 = 1;
                }
                if ((cantidad_vuelta == 3) && ((u32) h_ud_jugador[id_jugador].algun_temporizador < (u32) dato_80165648)) {
                    dato_801657E5 = 1;
                }
            }
            *huh += 1;
            if (dato_8018D320 == *huh) {
                *huh = dato_8018D320 - 1;
            }
            *huhthedeuce += 1;
            if (1) {}
            switch (*huhthedeuce) {
                case 0:
                    break;
                case 1:
                    funcion_80079084(id_jugador);
                    funcion_800C9060(id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0xF0, 0x15));
                    if ((id_circuito_actual == CIRCUITO_LUIGI_RACEWAY) && (dato_80165898 == 0) &&
                        (seleccion_modo != (s32) 1)) {
                        dato_80165898 = 1;
                    }
                    break;
                case 2:
                    funcion_800790B4(id_jugador);
                    break;
                case 3:
                    if ((dato_8018D114 == 0) || (dato_8018D114 == 1)) {
                        dato_801657E4 = 0;
                        dato_801657E6 = 0;
                        dato_801657F0 = 0;
                        dato_801657E8 = 1;
                        dato_80165800[0] = 1;
                        dato_80165800[1] = 1;
                        dato_8018D204 = (s32) 1;
                    }
                    h_ud_jugador[id_jugador].bool_completo_carrera = 1;
                    if (dato_8018D114 == 2) {
                        dato_80165800[id_jugador] = 0;
                    }
                    if (id_circuito_actual == CIRCUITO_YOSHI_VALLEY) {
                        h_ud_jugador[id_jugador].desconocido_81 = 1;
                    }
                    h_ud_jugador[id_jugador].tiempo_x_finalizacion_vuelta_1 = 0x0140;
                    h_ud_jugador[id_jugador].tiempo_x_finalizacion_vuelta_2 = 0x01E0;
                    h_ud_jugador[id_jugador].tiempo_x_finalizacion_vuelta_3 = 0x0280;
                    h_ud_jugador[id_jugador].tiempo_x_total = 0x0320;
                    dato_8016587C = (s32) 1;
                    if (dato_8018D20C == 0) {
                        funcion_80079054(id_jugador);
                        dato_8018D20C = 1;
                        if (cantidad_jugador == (s8) 1) {
                            dato_8018D1CC = 0x00000064;
                        }
                    }
                    break;
            }
        }
    } else {
        paso_f32_hacia(&h_ud_jugador[id_jugador].escalado_puesto, 1.0f, 0.125f);
        switch (seleccion_modo_pantalla) { /* irregular */
            case 0:
                paso_s16_hacia(&h_ud_jugador[id_jugador].puesto_x_deslizamiento, 0x001C, 7);
                if (dato_8018D1FC != 0) {
                    paso_s16_hacia(&h_ud_jugador[id_jugador].puesto_y_deslizamiento, -0x0028, 1);
                } else {
                    paso_s16_hacia(&h_ud_jugador[id_jugador].puesto_y_deslizamiento, -0x0010, 4);
                }
                break;
            case 2:
                paso_s16_hacia(&h_ud_jugador[id_jugador].puesto_x_deslizamiento, 0x001C, 7);
                paso_s16_hacia(&h_ud_jugador[id_jugador].puesto_y_deslizamiento, -0x0010, 4);
                break;
            case 1:
                paso_s16_hacia(&h_ud_jugador[id_jugador].puesto_x_deslizamiento, 0x001C, 7);
                paso_s16_hacia(&h_ud_jugador[id_jugador].puesto_y_deslizamiento, -0x0010, 4);
                paso_s16_hacia(&h_ud_jugador[id_jugador].tiempo_x_finalizacion_vuelta_1, 0x00E4, 0x0010);
                paso_s16_hacia(&h_ud_jugador[id_jugador].tiempo_x_finalizacion_vuelta_2, 0x00E4, 0x0010);
                paso_s16_hacia(&h_ud_jugador[id_jugador].tiempo_x_finalizacion_vuelta_3, 0x00E4, 0x0010);
                paso_s16_hacia(&h_ud_jugador[id_jugador].tiempo_x_total, 0x00E4, 0x0010);
                break;
            case 3:
                if ((id_jugador & 1) == 1) {
                    paso_s16_hacia(&h_ud_jugador[id_jugador].puesto_x_deslizamiento, -8, 2);
                } else {
                    paso_s16_hacia(&h_ud_jugador[id_jugador].puesto_x_deslizamiento, 8, 2);
                }
                paso_s16_hacia(&h_ud_jugador[id_jugador].puesto_y_deslizamiento, -0x0010, 4);
                break;
        }
    }
    if (h_ud_jugador[id_jugador].temporizador_parpadear == 0) {
        h_ud_jugador[id_jugador].algun_temporizador_1 = h_ud_jugador[id_jugador].algun_temporizador;
        dato_801657E3 = 0;
        return;
    }
    if (dato_80165594 == 0) {
        h_ud_jugador[id_jugador].estado_parpadear += 1;
        h_ud_jugador[id_jugador].estado_parpadear &= 1;
    }
    h_ud_jugador[id_jugador].temporizador_parpadear -= 1;
    if (h_ud_jugador[id_jugador].temporizador_parpadear == 0) {
        h_ud_jugador[id_jugador].estado_parpadear = 0;
    }
}

void funcion_8005D0FC(s32 id_jugador) {
    if (seleccion_modo != BATALLA) {
        switch (id_jugador) { /* irregular */
            case JUGADOR_UNO:
                funcion_8005CB60(id_jugador, cantidad_vuelta_por_id_jugador[JUGADOR_UNO]);
                break;
            case JUGADOR_DOS:
                funcion_8005CB60(id_jugador, cantidad_vuelta_por_id_jugador[JUGADOR_DOS]);
                break;
            case JUGADOR_TRES:
                funcion_8005CB60(id_jugador, cantidad_vuelta_por_id_jugador[JUGADOR_TRES]);
                break;
            case JUGADOR_CUATRO:
                funcion_8005CB60(id_jugador, cantidad_vuelta_por_id_jugador[JUGADOR_CUATRO]);
                break;
        }
    }
}

void funcion_8005D18C(void) {
    if ((seleccion_modo == GRAN_PREMIO) && (seleccion_cantidad_jugador_1 == CONTRARRELOJ)) {
        dato_801657D8 = 1;
        dato_8018D2BC = 0;
        dato_8018D2A4 = 0;
        if (gp_actual_carrera_puesto_por_id_jugador[0] >= 4) {
            dato_8018D1FC = 1;
            dato_8018D2A4 = 1;
            dato_8018D2BC = 1;
        }
    }
}

void funcion_8005D1F4(s32 parametro0) {
    s32 punto_camino_jugador;
    s32 punto_camino_bomba;
    s32 variable_a2;
    s32 dif_punto_camino;

    if (seleccion_modo == 2) {
        punto_camino_jugador = punto_camino_mas_cercano_por_id_jugador[parametro0];
        h_ud_jugador[parametro0].desconocido_74 = 0;
        for (variable_a2 = 0; variable_a2 < NUM_KARTS_BOMBA_VERSUS; variable_a2++) {
            if ((karts_bomba[variable_a2].state == BOMBA_ESTADO_EXPLOTADO) ||
                (karts_bomba[variable_a2].state == INACTIVO_ESTADO_BOMBA)) {
                continue;
            }
            punto_camino_bomba = karts_bomba[variable_a2].indice_punto_camino;
            dif_punto_camino = punto_camino_bomba - punto_camino_jugador;
            if ((dif_punto_camino < -5) || (dif_punto_camino > 0x1E)) {
                continue;
            }
            h_ud_jugador[parametro0].desconocido_74 = 1;
            break;
        }
    }
}

void funcion_8005D290(void) {
    dato_8018D488 = texturas_dma(textura_69C80C, 0x400, 0x400);
    cargado_textura_kart_sombra = texturas_dma(textura_sombra_kart, 0x1000, 0x1000);
    dato_8018D420 = texturas_dma(textura_69B03C, 0x100, 0x100);
    dato_8018D424 = texturas_dma(textura_69B140, 0x400, 0x400);
    dato_8018D478 = texturas_dma(textura_69C1E8, 0x200, 0x200);
    dato_8018D480 = texturas_dma(textura_burbuja_voz, 0x400, 0x400);
    dato_8018D484 = texturas_dma(textura_nota_musica, 0x400, 0x400);
    dato_8018D48C = texturas_dma(textura_bocanada_humo, 0x400, 0x400);
    polvo_suelo_cargado = texturas_dma(polvo_suelo, 0x400, 0x400);
    dato_8018D490 = dato_8018D48C;
    particula_pasto_cargado = texturas_dma(particula_pasto, 0x1000, 0x1000);
    dato_8018D4BC = texturas_dma(textura_globo_1, 0x800, 0x800);
    dato_8018D4C0 = texturas_dma(textura_globo_2, 0x800, 0x800);
    dato_8018D49C = texturas_dma(textura_69C9C4, 0x200, 0x200);
    dato_8018D4A0 = texturas_dma(textura_exclamacion_boing, 0x800, 0x800);
    textura_poomp_onomatopeya_cargado_1 = texturas_dma(textura_poomp_onomatopeya_1, 0x800, 0x800);
    textura_poomp_onomatopeya_cargado_2 = texturas_dma(textura_poomp_onomatopeya_2, 0x800, 0x800);
    textura_whrrrr_onomatopeya_cargado_1 = texturas_dma(textura_whrrrr_onomatopeya_1, 0x800, 0x800);
    textura_whrrrr_onomatopeya_cargado_2 = texturas_dma(textura_whrrrr_onomatopeya_2, 0x800, 0x800);
    textura_error_onomatopeya_cargado_1 = texturas_dma(textura_error_onomatopeya_1, 0x800, 0x800);
    textura_error_onomatopeya_cargado_2 = texturas_dma(textura_error_onomatopeya_2, 0x800, 0x800);
    dato_8018D438 = texturas_dma(textura_69CB84, 0x800, 0x800);
    dato_8018D43C = texturas_dma(textura_69CCEC, 0x800, 0x800);
    dato_8018D440 = texturas_dma(textura_69CEB8, 0x800, 0x800);
    dato_8018D444 = texturas_dma(textura_69D148, 0x800, 0x800);
    dato_8018D448 = texturas_dma(textura_69D4E0, 0x800, 0x800);
    dato_8018D44C = texturas_dma(textura_69D8FC, 0x800, 0x800);
    dato_8018D450 = texturas_dma(textura_69DCB4, 0x800, 0x800);
    dato_8018D454 = texturas_dma(textura_69DFA0, 0x800, 0x800);
    dato_8018D458 = texturas_dma(textura_69E25C, 0x800, 0x800);
    dato_8018D45C = texturas_dma(textura_69E518, 0x800, 0x800);
    dato_8018D460 = texturas_dma(textura_69E7A8, 0x800, 0x800);
    dato_8018D464 = texturas_dma(textura_69EA18, 0x800, 0x800);
    dato_8018D468 = texturas_dma(textura_69EC54, 0x800, 0x800);
    dato_8018D46C = texturas_dma(textura_69EE38, 0x800, 0x800);
    dato_8018D470 = texturas_dma(textura_69EFE0, 0x800, 0x800);
    textura_cargado_rayo_0 = texturas_dma(textura_rayo_0, 0x800, 0x800);
    textura_cargado_rayo_1 = texturas_dma(textura_rayo_1, 0x800, 0x800);
}

void reiniciar_pool_particula_jugador(Jugador* jugador) {
    s32 temporal_v0;

    for (temporal_v0 = 0; temporal_v0 < 10; ++temporal_v0) {
        jugador->pool_particula_0[temporal_v0].vivo_es = 0;
        jugador->pool_particula_0[temporal_v0].temporizador = 0;
        jugador->pool_particula_0[temporal_v0].type = SIN_PARTICULA;
    }

    for (temporal_v0 = 0; temporal_v0 < 10; ++temporal_v0) {
        jugador->pool_particula_3[temporal_v0].vivo_es = 0;
        jugador->pool_particula_3[temporal_v0].temporizador = 0;
        jugador->pool_particula_3[temporal_v0].type = SIN_PARTICULA;
    }

    for (temporal_v0 = 0; temporal_v0 < 10; ++temporal_v0) {
        jugador->pool_particula_1[temporal_v0].vivo_es = 0;
        jugador->pool_particula_1[temporal_v0].temporizador = 0;
        jugador->pool_particula_1[temporal_v0].type = SIN_PARTICULA;
    }

    for (temporal_v0 = 0; temporal_v0 < 10; ++temporal_v0) {
        jugador->pool_particula_2[temporal_v0].vivo_es = 0;
        jugador->pool_particula_2[temporal_v0].temporizador = 0;
        jugador->pool_particula_2[temporal_v0].type = SIN_PARTICULA;
    }
}

void fijar_posicion_particula_y_rotacion(Jugador* jugador, Particula* parametro1, f32 x, f32 y, f32 z, s8 tipo_superficie, s8 parametro6) {
    parametro1->pos[2] = z;
    parametro1->pos[0] = x;
    parametro1->pos[1] = y;
    parametro1->rotacion = -jugador->rotacion[1];
    parametro1->tipo_superficie = tipo_superficie;
    parametro1->desconocido_010 = parametro6;
}

s32 inicializar_jugador_particula(Particula* parametro0, s8 type, f32 parametro2) {
    parametro0->vivo_es = true;
    parametro0->type = type;
    parametro0->temporizador = 0;
    parametro0->scale = parametro2;
}

s32 fijar_color_particula(Particula* parametro0, s32 color, s16 alpha) {
    parametro0->rojo = (u8) (color >> 16);
    parametro0->verde = (u8) (color >> 8);
    parametro0->azul = (u8) color;
    parametro0->alpha = alpha;
}

s32 funcion_8005D82C(Particula* parametro0, s32 parametro1, s16 alpha) {
    s32 temporal_v0;
    temporal_v0 = int_aleatorio(48);

    parametro0->rojo = (u8) ((u8) (parametro1 >> 16) - temporal_v0);
    parametro0->verde = (u8) ((u8) (parametro1 >> 8) - temporal_v0);
    parametro0->azul = (u8) ((u8) parametro1 - temporal_v0);
    parametro0->alpha = alpha;
}

void fijar_particulas_derrape(Jugador* jugador, s16 parametro1, SIN_USO s32 parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4) {
    s32 temporal_lo;

    if (jugador->desconocido_0C0 >= 0) {
        fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], jugador->ruedas[IZQUIERDA_ATRAS].pos[0],
                      jugador->ruedas[IZQUIERDA_ATRAS].altura_base + 2.0f, jugador->ruedas[IZQUIERDA_ATRAS].pos[2],
                      jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie, 1);
    } else {
        fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], jugador->ruedas[DERECHA_ATRAS].pos[0],
                      jugador->ruedas[DERECHA_ATRAS].altura_base + 2.0f, jugador->ruedas[DERECHA_ATRAS].pos[2],
                      jugador->ruedas[DERECHA_ATRAS].tipo_superficie, 0);
    }

    temporal_lo = jugador->desconocido_0C0 / GRADOS(1);
    if ((temporal_lo >= 7) || (temporal_lo < -6)) {
        inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_DERRAPE, 0.35f);
        if (jugador->estado_derrape == 0) {
            fijar_color_particula(&jugador->pool_particula_1[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x70);
        }

        if (jugador->estado_derrape == 1) {
            fijar_color_particula(&jugador->pool_particula_1[parametro1], RGB32(0xFF, 0xFF, 0x00), 0x70);
        }

        if (jugador->estado_derrape >= 2) {
            fijar_color_particula(&jugador->pool_particula_1[parametro1], RGB32(0xFF, 0x96, 0x00), 0x70);
        }

        if (jugador->estado_derrape >= 2) {
            jugador->pool_particula_1[parametro1].desconocido_040 = 2;
            return;
        }

        jugador->pool_particula_1[parametro1].desconocido_040 = jugador->estado_derrape;
    }
}

void preparar_valido_particulas_derrape_comprobacion(Jugador* jugador, s16 parametro1, s32 parametro2, s8 parametro3, s8 parametro4) {
    if ((parametro1 == 0) && ((jugador->pool_particula_1[parametro2].temporizador >= 3) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
        fijar_particulas_derrape(jugador, parametro1, parametro2, parametro3, parametro4);
    } else if (jugador->pool_particula_1[parametro2].temporizador >= 3) {
        fijar_particulas_derrape(jugador, parametro1, parametro2, parametro3, parametro4);
    }
}

SIN_USO void funcion_8005DAD0(void) {
}

void funcion_8005DAD8(Particula* particula, s16 parametro1, s16 parametro2, s16 parametro3) {
    particula->rojo = parametro1;
    particula->alpha = parametro3;
    particula->desconocido_040 = parametro2;
}

void preparar_particulas_rueda(Jugador* jugador, s16 parametro1, s32 parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4) {
    SIN_USO s32 margen_pila;
    s32 tipo_superficie;
    s32 variable_t3;
    f32 rueda_x;
    f32 rueda_y;
    f32 rueda_z;
    s32 valor_azar;
    static s32 probar = 8;

    tipo_superficie = 0x000000FF;
    valor_azar = int_aleatorio(probar);
    if ((valor_azar == 0) || (valor_azar == 4)) {
        rueda_x = jugador->ruedas[IZQUIERDA_ATRAS].pos[0];
        rueda_y = jugador->ruedas[IZQUIERDA_ATRAS].altura_base + 2.0f;
        rueda_z = jugador->ruedas[IZQUIERDA_ATRAS].pos[2];
        variable_t3 = 1;
        tipo_superficie = jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie;
    }
    if ((valor_azar == 2) || (valor_azar == 6)) {
        rueda_x = jugador->ruedas[DERECHA_ATRAS].pos[0];
        rueda_y = jugador->ruedas[DERECHA_ATRAS].altura_base + 2.0f;
        rueda_z = jugador->ruedas[DERECHA_ATRAS].pos[2];
        variable_t3 = 0;
        tipo_superficie = jugador->ruedas[DERECHA_ATRAS].tipo_superficie;
    }
    switch (tipo_superficie) {
        case TIERRA:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                if (((jugador->speed / 18.0f) * 216.0f) >= 10.0f) {
                    fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], rueda_x, rueda_y, rueda_z, (s8) tipo_superficie, (s8) variable_t3);
                    inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_SUELO, 0.46f);
                    if ((id_circuito_actual == CIRCUITO_CHOCO_MOUNTAIN) || (id_circuito_actual == CIRCUITO_ROYAL_RACEWAY)) {
                        funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 1, 0, 0x0080);
                    }
                    if (id_circuito_actual == CIRCUITO_KALAMARI_DESERT) {
                        funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 7, 0, 0x0080);
                    }
                    if (id_circuito_actual == CIRCUITO_MOO_MOO_FARM) {
                        funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 8, 0, 0x0080);
                    }
                    if (id_circuito_actual == CIRCUITO_WARIO_STADIUM) {
                        funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 9, 0, 0x0080);
                    }
                    if (id_circuito_actual == CIRCUITO_YOSHI_VALLEY) {
                        funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 10, 0, 0x0080);
                    }
                    if (id_circuito_actual == CIRCUITO_DK_JUNGLE) {
                        funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 11, 0, 0x0080);
                    }
                    jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
                }
            } else if ((jugador->pool_particula_1[parametro2].temporizador > 0) && (((jugador->speed / 18.0f) * 216.0f) >= 10.0f)) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], rueda_x, rueda_y, rueda_z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_SUELO, 0.46f);
                if ((id_circuito_actual == CIRCUITO_CHOCO_MOUNTAIN) || (id_circuito_actual == CIRCUITO_ROYAL_RACEWAY)) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 1, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_KALAMARI_DESERT) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 7, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_MOO_MOO_FARM) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 8, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_WARIO_STADIUM) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 9, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_YOSHI_VALLEY) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 10, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_DK_JUNGLE) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 11, 0, 0x0080);
                }
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case PASTO:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                if (((jugador->speed / 18.0f) * 216.0f) >= 10.0f) {
                    fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], rueda_x, rueda_y, rueda_z, (s8) tipo_superficie, (s8) variable_t3);
                    inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_PASTO, 1.0f);
                    fijar_color_particula(&jugador->pool_particula_1[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x00FF);
                    jugador->pool_particula_1[parametro1].rojo -= parametro1 * 8;
                    jugador->pool_particula_1[parametro1].verde -= parametro1 * 8;
                    jugador->pool_particula_1[parametro1].azul -= parametro1 * 8;
                }
            } else if ((jugador->pool_particula_1[parametro2].temporizador > 0) && (((jugador->speed / 18.0f) * 216.0f) >= 10.0f)) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], rueda_x, rueda_y, rueda_z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_PASTO, 1.0f);
                fijar_color_particula(&jugador->pool_particula_1[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x00FF);
                jugador->pool_particula_1[parametro1].rojo -= parametro1 * 8;
                jugador->pool_particula_1[parametro1].verde -= parametro1 * 8;
                jugador->pool_particula_1[parametro1].azul -= parametro1 * 8;
            }
            jugador->pool_particula_1[parametro1].pos[1] -= 1.5;
            break;
        case FUERA_PISTA_ARENA:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                if (((jugador->speed / 18.0f) * 216.0f) >= 10.0f) {
                    fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], rueda_x, rueda_y, rueda_z, (s8) tipo_superficie, (s8) variable_t3);
                    inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_SUELO, 0.46f);
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 2, 1, 0x00A8);
                    jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
                }
            } else if ((jugador->pool_particula_1[parametro2].temporizador > 0) && (((jugador->speed / 18.0f) * 216.0f) >= 10.0f)) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], rueda_x, rueda_y, rueda_z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_SUELO, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 2, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case ARENA:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                if (((jugador->speed / 18.0f) * 216.0f) >= 10.0f) {
                    fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], rueda_x, rueda_y, rueda_z, (s8) tipo_superficie, (s8) variable_t3);
                    inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_SUELO, 0.46f);
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 3, 1, 0x00A8);
                    jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
                }
            } else if ((jugador->pool_particula_1[parametro2].temporizador > 0) && (((jugador->speed / 18.0f) * 216.0f) >= 10.0f)) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], rueda_x, rueda_y, rueda_z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_SUELO, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 3, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case ARENA_HUMEDO:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                if (((jugador->speed / 18.0f) * 216.0f) >= 10.0f) {
                    fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], rueda_x, rueda_y, rueda_z, (s8) tipo_superficie, (s8) variable_t3);
                    inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_SUELO, 0.46f);
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 4, 1, 0x00A8);
                    jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
                }
            } else if ((jugador->pool_particula_1[parametro2].temporizador > 0) && (((jugador->speed / 18.0f) * 216.0f) >= 10.0f)) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], rueda_x, rueda_y, rueda_z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_SUELO, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 4, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case FUERA_PISTA_TIERRA:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                if (((jugador->speed / 18.0f) * 216.0f) >= 10.0f) {
                    fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], rueda_x, rueda_y, rueda_z, (s8) tipo_superficie, (s8) variable_t3);
                    inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_SUELO, 0.46f);
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 5, 1, 0x00A8);
                    jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
                }
            } else if ((jugador->pool_particula_1[parametro2].temporizador > 0) && (((jugador->speed / 18.0f) * 216.0f) >= 10.0f)) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], rueda_x, rueda_y, rueda_z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_SUELO, 0.46f);
                funcion_8005D82C(&jugador->pool_particula_1[parametro1], 0x00FFA54F, 0x00AF);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 5, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case NIEVE:
        case FUERA_PISTA_NIEVE:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                if (((jugador->speed / 18.0f) * 216.0f) >= 10.0f) {
                    fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], rueda_x, rueda_y, rueda_z, (s8) tipo_superficie, (s8) variable_t3);
                    inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_SUELO, 0.46f);
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 6, 1, 0x00A8);
                    jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
                }
            } else if ((jugador->pool_particula_1[parametro2].temporizador > 0) && (((jugador->speed / 18.0f) * 216.0f) >= 10.0f)) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], rueda_x, rueda_y, rueda_z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_SUELO, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 6, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case ASFALTO:
        case PIEDRA:
        case PUENTE:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                if (((((jugador->speed / 18.0f) * 216.0f) >= 30.0f) &&
                     ((((jugador->desconocido_0C0 / GRADOS(1)) > 0x14) || ((jugador->desconocido_0C0 / GRADOS(1)) < (-0x14))))) ||
                    ((jugador->anterior_rapidez - jugador->speed) >= 0.04)) {
                    fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], rueda_x, rueda_y, rueda_z, (s8) tipo_superficie, (s8) variable_t3);
                    inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_SUELO, 0.46f);
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 0, 0, 0x0080);
                    jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
                }
            } else if ((jugador->pool_particula_1[parametro2].temporizador > 0) &&
                       (((((jugador->speed / 18.0f) * 216.0f) >= 30.0f) &&
                         (((jugador->desconocido_0C0 / GRADOS(1)) >= 0x15) || ((jugador->desconocido_0C0 / GRADOS(1)) < -0x14))) ||
                        ((jugador->anterior_rapidez - jugador->speed) >= 0.04))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], rueda_x, rueda_y, rueda_z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], PARTICULA_SUELO, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 0, 0, 0x0080);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        default:
            break;
    }
}

void funcion_8005EA94(Jugador* jugador, s16 parametro1, s32 parametro2, s8 parametro3, SIN_USO s8 parametro4) {
    s32 temporal_v0;
    s32 tipo_superficie;
    s32 variable_t1;
    f32 x;
    f32 y;
    f32 z;
    static s32 probar = 10;

    tipo_superficie = 0x000000FF;
    temporal_v0 = int_aleatorio(probar);
    if ((temporal_v0 == 0) || (temporal_v0 == 8)) {
        if ((dato_801652A0[parametro3] - jugador->ruedas[IZQUIERDA_ATRAS].altura_base) >= 3.5) {
            x = jugador->ruedas[IZQUIERDA_ATRAS].pos[0];
            y = jugador->ruedas[IZQUIERDA_ATRAS].altura_base + 2.0f;
            z = jugador->ruedas[IZQUIERDA_ATRAS].pos[2];
            variable_t1 = 1;
            tipo_superficie = 0;
        }
    }
    if ((temporal_v0 == 2) || (temporal_v0 == 6)) {
        if ((dato_801652A0[parametro3] - jugador->ruedas[DERECHA_ATRAS].altura_base) >= 3.5) {
            x = jugador->ruedas[DERECHA_ATRAS].pos[0];
            y = jugador->ruedas[DERECHA_ATRAS].altura_base + 2.0f;
            z = jugador->ruedas[DERECHA_ATRAS].pos[2];
            variable_t1 = 0;
            tipo_superficie = 0;
        }
    }
    if (1) {}
    if (tipo_superficie == 0) {
        if ((parametro1 == 0) && ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
            if (((jugador->speed / 18.0f) * 216.0f) >= 10.0f) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 9, 0.8f);
                fijar_color_particula(&jugador->pool_particula_1[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x00AF);
            }
        } else if ((jugador->pool_particula_1[parametro2].temporizador > 0) && (((jugador->speed / 18.0f) * 216.0f) >= 10.0f)) {
            fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t1);
            inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 9, 0.8f);
            fijar_color_particula(&jugador->pool_particula_1[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x00AF);
        }
    }
}

void funcion_8005ED48(Jugador* jugador, s16 parametro1, s32 parametro2, SIN_USO s8 parametro3, SIN_USO s8 parametro4) {
    s32 temporal_v0;
    s32 tipo_superficie;
    s32 variable_t3;
    f32 x;
    f32 y;
    f32 z;
    static s32 probar = 8;

    tipo_superficie = 0x000000FF;
    temporal_v0 = int_aleatorio(probar);
    if ((temporal_v0 == 2) || (temporal_v0 == 4)) {
        x = jugador->ruedas[IZQUIERDA_ATRAS].pos[0];
        y = jugador->ruedas[IZQUIERDA_ATRAS].altura_base + 2.0f;
        z = jugador->ruedas[IZQUIERDA_ATRAS].pos[2];
        variable_t3 = 1;
        tipo_superficie = jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie;
    }
    if ((temporal_v0 == 0) || (temporal_v0 == 6)) {
        x = jugador->ruedas[DERECHA_ATRAS].pos[0];
        y = jugador->ruedas[DERECHA_ATRAS].altura_base + 2.0f;
        z = jugador->ruedas[DERECHA_ATRAS].pos[2];
        variable_t3 = 0;
        tipo_superficie = jugador->ruedas[DERECHA_ATRAS].tipo_superficie;
    }

    switch (tipo_superficie) {
        case TIERRA:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 5, 0.46f);
                if ((id_circuito_actual == CIRCUITO_CHOCO_MOUNTAIN) || (id_circuito_actual == CIRCUITO_ROYAL_RACEWAY)) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 1, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_KALAMARI_DESERT) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 7, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_MOO_MOO_FARM) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 8, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_WARIO_STADIUM) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 9, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_YOSHI_VALLEY) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 10, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_DK_JUNGLE) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 11, 0, 0x0080);
                }
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, tipo_superficie, variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 5, 0.46f);
                if ((id_circuito_actual == CIRCUITO_CHOCO_MOUNTAIN) || (id_circuito_actual == CIRCUITO_ROYAL_RACEWAY)) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 1, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_KALAMARI_DESERT) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 7, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_MOO_MOO_FARM) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 8, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_WARIO_STADIUM) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 9, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_YOSHI_VALLEY) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 0x000A, 0, 0x0080);
                }
                if (id_circuito_actual == CIRCUITO_DK_JUNGLE) {
                    funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 0x000B, 0, 0x0080);
                }
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case PASTO:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 5, 0.1f);
                fijar_color_particula(&jugador->pool_particula_1[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x00FF);
                jugador->pool_particula_1[parametro1].rojo -= parametro1 * 8;
                jugador->pool_particula_1[parametro1].verde -= parametro1 * 8;
                jugador->pool_particula_1[parametro1].azul -= parametro1 * 8;
            } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 5, 0.1f);
                fijar_color_particula(&jugador->pool_particula_1[parametro1], RGB32(0xFF, 0xFF, 0xFF), 0x00FF);
                jugador->pool_particula_1[parametro1].rojo -= parametro1 * 8;
                jugador->pool_particula_1[parametro1].verde -= parametro1 * 8;
                jugador->pool_particula_1[parametro1].azul -= parametro1 * 8;
            }
            jugador->pool_particula_1[parametro1].pos[1] -= 1.5;
            break;
        case FUERA_PISTA_ARENA:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 5, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 2, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 5, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 2, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case ARENA:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 5, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 3, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 5, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 3, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case ARENA_HUMEDO:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 5, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 4, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 5, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 4, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case FUERA_PISTA_TIERRA:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 5, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 5, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 5, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 5, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case NIEVE:
        case FUERA_PISTA_NIEVE:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 5, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 6, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 5, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 6, 1, 0x00A8);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        case ASFALTO:
        case PIEDRA:
        case PUENTE:
            if ((parametro1 == 0) &&
                ((jugador->pool_particula_1[parametro2].temporizador > 0) || (jugador->pool_particula_1[parametro2].vivo_es == 0))) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 5, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 0, 0, 0x0080);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            } else if (jugador->pool_particula_1[parametro2].temporizador > 0) {
                fijar_posicion_particula_y_rotacion(jugador, &jugador->pool_particula_1[parametro1], x, y, z, (s8) tipo_superficie, (s8) variable_t3);
                inicializar_jugador_particula(&jugador->pool_particula_1[parametro1], 5, 0.46f);
                funcion_8005DAD8(&jugador->pool_particula_1[parametro1], 0, 0, 0x0080);
                jugador->pool_particula_1[parametro1].verde = int_aleatorio(0x0010U);
            }
            break;
        default:
            break;
    }
}
