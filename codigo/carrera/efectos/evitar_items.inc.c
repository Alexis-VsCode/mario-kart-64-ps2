// Evitar items

void funcion_80090868(Jugador* jugador) {
    s32 indice_jugador;

    jugador->desconocido_078 = 0;
    jugador->posicion_giro = 0;
    jugador->desconocido_0C0 = 0;
    jugador->desconocido_08C = 0.0f;
    indice_jugador = obtener_indice_jugador_para_jugador(jugador);

    if ((jugador->lakitu_props & MANTENIDO_POR_LAKITU) != MANTENIDO_POR_LAKITU) {
        jugador->desconocido_D98 = 1;
        jugador->desconocido_D9C = 0.0f;
        jugador->desconocido_DA0 = 0.5f;
        actualizar_punto_camino_circuito(jugador, indice_jugador);
        jugador->desconocido_222 = 0;
        jugador->lakitu_props |= MANTENIDO_POR_LAKITU;
        jugador->desconocido_0C8 = 0;
        if ((jugador->oob_props & BAJO_OOB_O_NIVEL_FLUIDO) == BAJO_OOB_O_NIVEL_FLUIDO) {
            if ((id_circuito_actual == CIRCUITO_BOWSER_CASTLE) || (id_circuito_actual == CIRCUITO_BIG_DONUT)) {
                jugador->lakitu_props |= LAKITU_LAVA;
            } else {
                jugador->lakitu_props |= LAKITU_AGUA;
            }
            if ((id_circuito_actual == CIRCUITO_SHERBET_LAND) || (id_circuito_actual == CIRCUITO_SKYSCRAPER) ||
                (id_circuito_actual == CIRCUITO_RAINBOW_ROAD)) {
                jugador->lakitu_props &= ~(LAKITU_LAVA | LAKITU_AGUA);
            }
        }
    }
}

void funcion_80090970(Jugador* jugador, s8 id_jugador, s8 parametro2) {
    SIN_USO s32 margen_pila_0;
    SIN_USO s32 margen_pila_1;
    Vec3f sp44;
    Vec3f sp38;
    PuntoCaminoPista* punto_camino;
    SIN_USO s32 margen_pila_2;
    SIN_USO s32 margen_pila_3;

    jugador->desconocido_0C2 = 0x000C;
    jugador->desconocido_078 = 0;
    jugador->posicion_giro = 0;
    jugador->desconocido_0C0 = 0;
    jugador->desconocido_08C = 0.0f;
    limpiar_efecto(jugador, id_jugador);
    switch (jugador->desconocido_222) {
        case 0:
            if ((jugador->lakitu_props & LAKITU_RECUPERACION) == LAKITU_RECUPERACION) {
                if ((jugador->desconocido_0C8 < 0x3C) || ((jugador->lakitu_props & MANTENIDO_POR_LAKITU) != MANTENIDO_POR_LAKITU)) {
                    jugador->desconocido_0C8++;
                    if (jugador->desconocido_0C8 >= 0x3C) {
                        jugador->desconocido_0C8 = 0x003C;
                    }
                } else {
                    mover_f32_hacia(&jugador->pos[1], dato_801652A0[id_jugador] + 100.0f, 0.012f);
                    mover_s16_hacia(&jugador->desconocido_0CC[parametro2], 0, 0.2f);
                    if ((dato_801652A0[id_jugador] + 40.0f) <= jugador->pos[1]) {
                        jugador->desconocido_222 = 1;
                        jugador->lakitu_props |= LAKITU_APAGAR;
                        jugador->alpha = 0x00FF;
                    }
                }
            } else if ((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == MANTENIDO_POR_LAKITU) {
                mover_f32_hacia(&jugador->pos[1], jugador->desconocido_074 + 100.0f, 0.025f);
                mover_s16_hacia(&jugador->desconocido_0CC[parametro2], 0, 0.2f);
                if ((jugador->desconocido_074 + 40.0f) <= jugador->pos[1]) {
                    jugador->desconocido_222 = 1;
                    jugador->lakitu_props |= LAKITU_APAGAR;
                    jugador->alpha = 0x00FF;
                }
            }
            if ((jugador->efectos & BOO_EFECTO) == BOO_EFECTO) {
                funcion_8008FB30(jugador, id_jugador);
            }
            break;
        case 1:
            if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) && ((jugador->type & CPU_JUGADOR) == 0)) {
                funcion_8009E088(id_jugador, 0xA);
            }
            if ((jugador->lakitu_props & LAKITU_RECUPERACION) == LAKITU_RECUPERACION) {
                mover_f32_hacia(&jugador->pos[1], dato_801652A0[id_jugador] + 40.0f, 0.02f);
                jugador->alpha -= 8;
                if (jugador->alpha < 9) {
                    jugador->alpha = 0;
                    jugador->desconocido_222 = 2;
                    jugador->lakitu_props &= ~LAKITU_RECUPERACION;
                }
            } else {
                mover_f32_hacia(&jugador->pos[1], jugador->pos_viejo[1] + 40.0f, 0.02f);
                jugador->alpha -= 8;
                if (jugador->alpha < 9) {
                    jugador->alpha = 0;
                    jugador->desconocido_222 = 2;
                }
            }
            jugador->lakitu_props &= ~LAKITU_AGUA;
            break;
        case 2:
            funcion_80090178(jugador, id_jugador, sp44, sp38);
            jugador->rotacion[1] = (u16) -obtener_angulo_xz_entre_puntos(sp44, sp38) & 0xFFFF;
            jugador->pos[0] = sp44[0];
            jugador->pos[1] = sp44[1] + 40.0f;
            jugador->pos[2] = sp44[2];
            jugador->desconocido_222 = 3;
            break;
        case 3:
            dato_80165330[id_jugador] = 0;
            if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) && ((jugador->type & CPU_JUGADOR) == 0)) {
                funcion_8009E020(id_jugador, 0x14);
            }
            funcion_80090178(jugador, id_jugador, sp44, sp38);
            jugador->pos[0] = sp44[0];
            jugador->pos[1] = sp44[1] + 40.0f;
            jugador->pos[2] = sp44[2];
            jugador->pos[2] = jugador->pos[2] + coss((id_jugador * 0x1C70) - jugador->rotacion[1]) * -5.0f;
            jugador->pos[0] = jugador->pos[0] + senos((id_jugador * 0x1C70) - jugador->rotacion[1]) * -5.0f;
            jugador->alpha += 8;
            if (jugador->alpha >= 0xF0) {
                jugador->alpha = 0x00FF;
                jugador->desconocido_222 = 4;
                jugador->lakitu_props &= ~LAKITU_APAGAR;
                jugador->desconocido_0C8 = 0;
            }
            break;
        case 4:
            if ((jugador->desconocido_0C8 == 0x0096) || (jugador->desconocido_0C8 == 0x00C8) || (jugador->desconocido_0C8 == 0x00FA)) {
                jugador->pos[2] = jugador->pos[2] + coss(-jugador->rotacion[1]) * -10.0f;
                jugador->pos[0] = jugador->pos[0] + senos(-jugador->rotacion[1]) * -10.0f;
            }
            if (jugador->desconocido_0C8 == 0x00FC) {
                punto_camino = caminos_pista[0];
                jugador->pos[0] = punto_camino->pos_x;
                jugador->pos[1] = punto_camino->pos_y;
                jugador->pos[2] = punto_camino->pos_z;
            }
            mover_f32_hacia(&jugador->pos[1], (jugador->desconocido_074 + jugador->tamanio_caja_envolvente) - 2.0f, 0.04f);
            jugador->desconocido_0C8++;
            if (((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) || (jugador->efectos & EFECTO_GOLPE_ENEMIGO)) {
                jugador->lakitu_props &= ~LAKITU_LAVA;
                if (jugador->desconocido_0C8 >= 0x5B) {
                    if (jugador->type & HUMANO_JUGADOR) {
                        funcion_800C9018(id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xFA, 0x28));
                    }
                    if (seleccion_modo == BATALLA) {
                        sacar_globo_jugador(jugador, id_jugador);
                    }
                    jugador->lakitu_props &= ~MANTENIDO_POR_LAKITU;
                    jugador->oob_props &= ~BAJO_NIVEL_FLUIDO;
                    if ((jugador->lakitu_props & EFECTO_CONGELADO) != EFECTO_CONGELADO) {
                        jugador->lakitu_props &= ~LAKITU_ESCENA;
                        if ((jugador->arriba_rapidez * 0.9) <= jugador->actual_rapidez) {
                            funcion_8008F104(jugador, id_jugador);
                        }
                    }
                }
            }
            break;
    }
    jugador->desconocido_DA0 += 8.0f;
    if (jugador->desconocido_DA0 >= 180.0f) {
        jugador->desconocido_DA0 = 180.0f;
    }
    if (jugador->desconocido_D98 == 1) {
        jugador->desconocido_D9C += jugador->desconocido_DA0;
        if (jugador->desconocido_D9C >= (f32) GRADOS(10)) {
            jugador->desconocido_DA0 = 0.0f;
            jugador->desconocido_D98 *= -1;
        }
    }
    if (jugador->desconocido_D98 == -1) {
        jugador->desconocido_D9C -= jugador->desconocido_DA0;
        if (jugador->desconocido_D9C <= (f32) -GRADOS(10)) {
            jugador->desconocido_DA0 = 0.0f;
            jugador->desconocido_D98 *= -1;
        }
    }
}

#define BLOQUE_ITEM_USAR_EFECTOS                                                                                        \
    EFECTO_RAYO | desconocido_efecto_0_x_10000000 | EFECTO_APLASTAMIENTO_PUBLICAR | EFECTO_APLASTAMIENTO | GOLPE_POR_EFECTO_ESTRELLA |          \
        EFECTO_ERROR_EXPLOSION | desconocido_efecto_0_x_800000 | IMPULSO_RAMPA_ASFALTO_EFECTO | EFECTO_GOLPE_RAYO |      \
        EFECTO_VUELCO_TERRENO | TEMPRANO_INICIO_TROMPO_EFECTO | BANANA_CERCA_EFECTO_TROMPO | GOLPE_POR_CAPARAZON_VERDE_EFECTO | \
        EFECTO_ESTRELLA | EFECTO_TROMPO_BANANA | EFECTO_TROMPO_CONDUCIENDO | IMPULSO_RAMPA_MADERA_EFECTO

bool evitar_usar_item(Jugador* jugador) {
    s32 phi_v0 = 0;
    if ((((((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == MANTENIDO_POR_LAKITU) ||
           ((jugador->lakitu_props & LAKITU_ESCENA) == LAKITU_ESCENA)) ||
          ((jugador->type & jugador_desconocido_0_x40) != 0)) ||
         ((jugador->type & MODO_CINEMATICA_JUGADOR) != 0)) ||
        ((jugador->type & EXISTE_JUGADOR) == 0)) {
        return true;
    }

    switch (jugador->copia_item_actual) {
        case HONGO_ITEM:
        case HONGO_DOBLE_ITEM:
        case ITEM_TRIPLE_HONGO:
        case ITEM_SUPER_HONGO:
            if ((jugador->efectos & EFECTO_EN_EL_AIRE) != 0) {
                return true;
            }
            phi_v0 = BLOQUE_ITEM_USAR_EFECTOS;
            goto evitar_etiqueta_usar_item;
        case ESTRELLA_ITEM:
            phi_v0 = BOO_EFECTO | BLOQUE_ITEM_USAR_EFECTOS;
        case ITEM_BOO:
            phi_v0 = phi_v0 | (BOO_EFECTO | BLOQUE_ITEM_USAR_EFECTOS);
        evitar_etiqueta_usar_item:
        default:
            if ((jugador->efectos & phi_v0) != 0) {
                return true;
            }
            return false;
    }
}

void funcion_800911B4(Jugador* jugador, s8 parametro1) {
    s32 temporal_v0;

    jugador->desconocido_0AE = jugador->rotacion[1];
    jugador->kart_props |= (sin_uso_0_x_1000 | sin_uso_0_x_800);
    jugador->kart_props &= ~sin_uso_0_x_400;
    jugador->kart_props |= sin_uso_0_x_2000;
    jugador->tiron_salto_kart = 0.002f;
    jugador->aceleracion_salto_kart = 0.0f;
    jugador->velocidad_salto_kart = 2.6f;
    jugador->desconocido_0B2 = 2;
    jugador->desconocido_0C0 = 0;
    jugador->posicion_giro = 0;
    jugador->desconocido_078 = 0;
    dato_8018D920[parametro1] = 0;

    jugador->pool_particula_3[1].type = 0;
    jugador->pool_particula_3[1].temporizador = 0;
    jugador->pool_particula_3[1].vivo_es = 0;
    jugador->pool_particula_3[0].type = 0;
    jugador->pool_particula_3[0].temporizador = 0;
    jugador->pool_particula_3[0].vivo_es = 0;

    temporal_v0 = 2; do {
        jugador->pool_particula_3[1 + temporal_v0].vivo_es = 0;
        jugador->pool_particula_3[1 + temporal_v0].temporizador = 0;
        jugador->pool_particula_3[1 + temporal_v0].type = 0;
        jugador->pool_particula_3[2 + temporal_v0].vivo_es = 0;
        jugador->pool_particula_3[2 + temporal_v0].temporizador = 0;
        jugador->pool_particula_3[2 + temporal_v0].type = 0;
        jugador->pool_particula_3[3 + temporal_v0].vivo_es = 0;
        jugador->pool_particula_3[3 + temporal_v0].temporizador = 0;
        jugador->pool_particula_3[3 + temporal_v0].type = 0;

        temporal_v0 += 4;
        jugador->pool_particula_2[6 + temporal_v0].vivo_es = 0;
        jugador->pool_particula_2[6 + temporal_v0].temporizador = 0;
        jugador->pool_particula_2[6 + temporal_v0].type = 0;
    } while (temporal_v0 < 10);
}

void funcion_80091298(Jugador* jugador, s8 parametro1) {
    s16 variable_v1;
    SIN_USO s32 margen_pila_1;
    Vec3f sp_c = { 27.167f, 25.167f, 23.167f };

    jugador->kart_props |= sin_uso_0_x_2000;
    if (jugador->desconocido_0B2 == 0) {
        variable_v1 = 0;
    } else {
        jugador->rotacion[1] -= GRADOS(20);
        dato_8018D920[parametro1] -= GRADOS(20);
        variable_v1 = (u16) dato_8018D920[parametro1] / GRADOS(20);
    }
    if (((variable_v1 == 9) && (jugador->desconocido_0B2 == 1)) || ((variable_v1 == 0) && (jugador->desconocido_0B2 == 2)) ||
        (jugador->desconocido_0B2 == 0)) {
        jugador->desconocido_0B2--;
        if (jugador->desconocido_0B2 <= 0) {
            jugador->desconocido_0B2 = 0;
        }
        if (jugador->desconocido_0B2 == 0) {
            if ((jugador->pos[1] - (jugador->tamanio_caja_envolvente + 1.0f)) <= sp_c[parametro1]) {
                jugador->pos[1] = (f32) ((f64) (sp_c[parametro1] + jugador->tamanio_caja_envolvente) + 1.08);
                jugador->desconocido_DB4.unk18 = 0;
                jugador->desconocido_0A8 = 0;
                jugador->posicion_giro = 0;
                jugador->desconocido_0C0 = 0;
                jugador->desconocido_DB4.desconocido_c = 3.0f;
                jugador->kart_props &= ~sin_uso_0_x_800;
                jugador->gravedad_kart = tabla_gravedad_kart[jugador->id_personaje];
                jugador->desconocido_0D4[0] = 0;
                jugador->type |= SECUENCIA_INICIO_JUGADOR;
                jugador->speed = 0.0f;
                jugador->desconocido_08C = 0.0f;
                jugador->actual_rapidez = 0.0f;
                if (parametro1 == 0) {
                    dato_801658BC = 1;
                }
            }
        }
    }
}

void funcion_80091440(s8 parametro0) {
    if ((jugadores[parametro0].kart_props & sin_uso_0_x_800) == 0) {
        jugadores[parametro0].kart_props |= (sin_uso_0_x_2000 | sin_uso_0_x_400);
        jugadores[parametro0].type &= ~SECUENCIA_INICIO_JUGADOR;
    }
}
