// Efectos basicos

s32 dato_8018D900[8];
s16 dato_8018D920[8];
s32 jugador_estrella_efecto_inicio_tiempo[8];
s32 jugador_boo_tiempo_inicio_efecto[8];
s32 jugador_otro_pantallas_alpha[8];
s32 dato_8018D990[8];

SIN_USO void func_sin_nombre(void) {
}

s32 funcion_8008C1D8(SIN_USO s32* parametro0) {
}

void funcion_8008C1E0(SIN_USO s32* parametro0, SIN_USO s32 parametro1) {
    parametro1 = 4;
}

SIN_USO void func_sin_nombre1(SIN_USO s32 parametro0) {
}

SIN_USO void func_sin_nombre2(SIN_USO s32 parametro0) {
}

SIN_USO void func_sin_nombre3(void) {
}

void funcion_8008C204(void) {
}

SIN_USO void func_sin_nombre4(void) {
}

SIN_USO void funcion_8008C214(void) {
}

SIN_USO void func_sin_nombre5(void) {
}

SIN_USO void func_sin_nombre6(void) {
}

SIN_USO void func_sin_nombre7(void) {
}

SIN_USO void func_sin_nombre8(void) {
}

SIN_USO void funcion_8008C23C(void) {
}

SIN_USO void func_sin_nombre9(void) {
}
SIN_USO void func_sin_nombre10(void) {
}
SIN_USO void func_sin_nombre11(void) {
}
SIN_USO void func_sin_nombre12(void) {
}
SIN_USO void func_sin_nombre13(void) {
}
SIN_USO void func_sin_nombre14(void) {
}
SIN_USO void func_sin_nombre15(void) {
}
SIN_USO void func_sin_nombre16(void) {
}
SIN_USO void func_sin_nombre17(void) {
}
SIN_USO void func_sin_nombre18(void) {
}
SIN_USO void func_sin_nombre19(void) {
}
SIN_USO void func_sin_nombre20(void) {
}
SIN_USO void func_sin_nombre21(void) {
}

SIN_USO void func_sin_nombre22(SIN_USO s32 parametro0, SIN_USO s32 parametro1) {
    parametro1 = 4;
}

SIN_USO void func_sin_nombre23(void) {
}

SIN_USO void func_sin_nombre24(void) {
}

SIN_USO void func_sin_nombre25(void) {
}

SIN_USO void func_sin_nombre26(void) {
}

SIN_USO void func_sin_nombre27(void) {
}

SIN_USO void func_sin_nombre28(void) {
}

SIN_USO void func_sin_nombre29(void) {
}

SIN_USO void func_sin_nombre30(void) {
}

SIN_USO void func_sin_nombre31(void) {
}

SIN_USO void func_sin_nombre32(void) {
}

SIN_USO void func_sin_nombre33(void) {
}

void funcion_8008C310(Jugador* jugador) {
    if ((jugador->disparadores & DISPARADOR_VUELCO_ALTO) || (jugador->disparadores & DISPARADOR_VUELCO_BAJO) ||
        ((jugador->disparadores << 9) < 0) || (jugador->disparadores & GOLPE_POR_DISPARADOR_ESTRELLA)) {
        jugador->graficos_kart = ((u16) jugador->graficos_kart | EXPLOSION);
    }
}

SIN_USO void func_sin_nombre34(void) {
}

void limpiar_efecto(Jugador* jugador, s8 indice_jugador) {

    if ((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) == GOLPE_POR_CAPARAZON_VERDE_EFECTO) {
        funcion_8008C6D0(jugador, indice_jugador);
    }

    if (((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
        (jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO) {
        quitar_efectos_trompo(jugador, indice_jugador);
    }
    if ((jugador->efectos & BANANA_CERCA_EFECTO_TROMPO) == BANANA_CERCA_EFECTO_TROMPO) {
        quitar_banana_cerca_efecto_trompo(jugador, indice_jugador);
    }
    if ((jugador->kart_props & CONDUCIENDO_CERCA_TROMPO) != 0) {
        quitar_conduciendo_cerca_efecto_trompo(jugador, indice_jugador);
    }
    if ((jugador->efectos & EFECTO_HONGO) == EFECTO_HONGO) {
        quitar_efecto_hongo(jugador);
    }
    if ((jugador->efectos & desconocido_efecto_0_x_80000) == desconocido_efecto_0_x_80000) {
        funcion_8008D760(jugador);
    }
    if ((jugador->efectos & desconocido_efecto_0_x_800000) == desconocido_efecto_0_x_800000) {
        funcion_8008D97C(jugador);
    }
    if ((jugador->efectos & EFECTO_ERROR_EXPLOSION) == EFECTO_ERROR_EXPLOSION) {
        funcion_8008E884(jugador, indice_jugador);
    }
    if ((jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA) == GOLPE_POR_EFECTO_ESTRELLA) {
        quitar_golpe_por_efecto_estrella(jugador, indice_jugador);
    }
    if ((jugador->efectos & IMPULSO_RAMPA_ASFALTO_EFECTO) == IMPULSO_RAMPA_ASFALTO_EFECTO) {
        quitar_impulso_rampa_asfalto_efecto(jugador);
    }
    if ((jugador->efectos & IMPULSO_RAMPA_MADERA_EFECTO) == IMPULSO_RAMPA_MADERA_EFECTO) {
        quitar_impulso_rampa_madera_efecto(jugador);
    }
    if ((jugador->efectos & TEMPRANO_INICIO_TROMPO_EFECTO) == TEMPRANO_INICIO_TROMPO_EFECTO) {
        funcion_8008F3E0(jugador);
    }
    if ((jugador->efectos & EFECTO_VUELCO_TERRENO) == EFECTO_VUELCO_TERRENO) {
        funcion_8008F5A4(jugador, indice_jugador);
    }
    if ((jugador->efectos & desconocido_efecto_0_x_10000000) == desconocido_efecto_0_x_10000000) {
        funcion_8008FEDC(jugador, indice_jugador);
    }
    jugador->kart_props = (s16) (jugador->kart_props & ~ARRIBA_ATRAS);
    jugador->efectos = (s32) (jugador->efectos & ~EFECTO_GIRO_AB);
}

void funcion_8008C528(Jugador* jugador, s8 indice_jugador) {
    SIN_USO s32 sp24;
    s32 temporal_v1;
    limpiar_efecto(jugador, indice_jugador);
    funcion_8008C310(jugador);
    temporal_v1 = jugador->id_personaje;
    jugador->desconocido_0C2 = 0;
    jugador->tiron_salto_kart = dato_800E37B0[temporal_v1];
    jugador->aceleracion_salto_kart = 0.0f;

    jugador->velocidad_salto_kart = dato_800E3790[temporal_v1];
    jugador->desconocido_0A8 = 0;
    jugador->efectos = jugador->efectos | GOLPE_POR_CAPARAZON_VERDE_EFECTO;
    jugador->efectos = jugador->efectos & ~EFECTO_DERRAPANDO;
    jugador->desconocido_0C0 = 0;
    jugador->desconocido_236 = 2;
    jugador->desconocido_042 = 0;
    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
        funcion_800C90F4(indice_jugador, (temporal_v1 * 0x10) + 0x29008005);
        funcion_800C9060(indice_jugador, SONIDO_EXPLOSION_ACCION);
    } else {
        reproducir_cpu_efecto_sonido(indice_jugador, jugador);
    }
    jugador->disparadores = (s32) (jugador->disparadores & ~DISPARADOR_VUELCO_BAJO);
}

void funcion_8008C62C(Jugador* jugador, s8 indice_jugador) {

    alternativo_desacelerar_jugador(jugador, 5.0f);
    jugador->desconocido_0A8 += (s16) 0xA0;
    jugador->desconocido_042 += (s16) GRADOS(10);
    if (jugador->desconocido_0A8 >= 0x2000) {
        jugador->desconocido_0A8 = 0;
        jugador->desconocido_236 = (s16) (jugador->desconocido_236 - 1);
        if (jugador->desconocido_236 == 0) {
            jugador->desconocido_0A8 = 0x2000;
            funcion_8008C6D0(jugador, indice_jugador);
            if (seleccion_modo == BATALLA) {
                sacar_globo_jugador(jugador, indice_jugador);
            }
        }
    }
}

void funcion_8008C6D0(Jugador* jugador, s8 indice_jugador) {

    jugador->desconocido_206 = 0;
    jugador->acel_pendiente = 0;
    jugador->efectos = (s32) (jugador->efectos & ~GOLPE_POR_CAPARAZON_VERDE_EFECTO);
    jugador->desconocido_0A8 = 0;
    jugador->desconocido_0C0 = 0;
    jugador->posicion_giro = 0;
    jugador->desconocido_236 = 0;
    jugador->desconocido_078 = 0;
    jugador->actual_rapidez = 0.0f;
    dato_80165190[0][indice_jugador] = 1;
    dato_80165190[1][indice_jugador] = 1;
    dato_80165190[2][indice_jugador] = 1;
    dato_80165190[3][indice_jugador] = 1;
    jugador->desconocido_042 = 0;
}

void agregar_efecto_trompo(Jugador* jugador, s8 indice_jugador) {
    limpiar_efecto(jugador, indice_jugador);
    if (((jugador->efectos & EFECTO_TROMPO_BANANA) != EFECTO_TROMPO_BANANA) &&
        ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) != EFECTO_TROMPO_CONDUCIENDO)) {
        jugador->efectos &= ~EFECTO_DERRAPANDO;

        if ((jugador->desconocido_0C0 / GRADOS(1)) >= 0) {
            jugador->efectos |= EFECTO_TROMPO_CONDUCIENDO;
        } else {
            jugador->efectos |= EFECTO_TROMPO_BANANA;
        }

        jugador->graficos_kart |= WHIRRR;
        jugador->desconocido_0C0 = 0; jugador->posicion_giro = 0; jugador->desconocido_078 = 0; jugador->desconocido_0AE = jugador->rotacion[1]; jugador->desconocido_0B2 = 2;
        dato_80165190[0][indice_jugador] = 1;
        dato_80165190[1][indice_jugador] = 1;
        dato_80165190[2][indice_jugador] = 1;
        dato_80165190[3][indice_jugador] = 1;
        jugador_actual_rapidez[indice_jugador] = jugador->actual_rapidez;
        temporizador_impulso_triple_a_combo[indice_jugador] = 0;
        es_jugador_triple_a_boton_combo[indice_jugador] = false;
        interruptor_cantidad_a[indice_jugador] = 0;
        frame_desde_ultimo_combo_a[indice_jugador] = 0;
        dato_8018D920[indice_jugador] = 0;

        if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
            ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
            funcion_800C90F4(indice_jugador, (jugador->id_personaje * 0x10) + 0x29008003);
        } else {
            reproducir_cpu_efecto_sonido(indice_jugador, jugador);
        }
    }
}

void quitar_efectos_trompo(Jugador* jugador, s8 id_jugador) {
    jugador->efectos &= ~EFECTO_TROMPO_BANANA;
    jugador->efectos &= ~EFECTO_TROMPO_CONDUCIENDO;
    jugador->desconocido_0A8 = 0;
    jugador->rotacion[1] = jugador->desconocido_0AE;
    jugador->posicion_giro = 0;
    jugador->desconocido_0C0 = 0;
    jugador->efectos &= ~BANANA_CERCA_EFECTO_TROMPO;

    dato_80165190[0][id_jugador] = 1;
    dato_80165190[1][id_jugador] = 1;
    dato_80165190[2][id_jugador] = 1;
    dato_80165190[3][id_jugador] = 1;

    jugador->desconocido_046 &= ~TROMPO_INSTANTE;

    if ((es_jugador_triple_a_boton_combo[id_jugador] == true) && ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR)) {
        jugador->actual_rapidez = (f32) (jugador->actual_rapidez + 100.0f);
    }
    if ((seleccion_modo == VERSUS) && ((jugador->type & CPU_JUGADOR) == CPU_JUGADOR) && (!modo_demo) &&
        ((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == 0) && (gp_actual_carrera_puesto_por_id_jugador[id_jugador] != 0)) {
        jugador->disparadores = (s32) (jugador->disparadores | DISPARADOR_VUELCO_VERTICAL);
    }
}

void funcion_8008C9EC(Jugador* jugador, s8 indice_jugador) {
    s16 margen_pila_1;
    s16 margen_pila_2;
    s16 sp30[5] = { GRADOS(6), GRADOS(6), GRADOS(12), GRADOS(9), GRADOS(10) };

    jugador->desconocido_206 = 0;
    jugador->acel_pendiente = 0;
    if ((jugador->desconocido_046 & TROMPO_INSTANTE) == TROMPO_INSTANTE) {
        alternativo_desacelerar_jugador(jugador, 100.0f);
    } else {
        if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
            alternativo_desacelerar_jugador(jugador, 1.0f);
        } else {
            alternativo_desacelerar_jugador(jugador, 4.0f);
        }
        if (!(jugador->type & HUMANO_JUGADOR)) {
            alternativo_desacelerar_jugador(jugador, 30.0f);
        }
    }
    if ((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) {
        jugador->rotacion[1] -= sp30[jugador->desconocido_0B2];
        dato_8018D920[indice_jugador] -= sp30[jugador->desconocido_0B2];
        margen_pila_1 = (u16) dato_8018D920[indice_jugador] / (0x10000 / (0x168 / (sp30[jugador->desconocido_0B2] / GRADOS(1))));
        if (margen_pila_1 == 0) {
            jugador->desconocido_0B2--;
            if (jugador->desconocido_0B2 <= 0) {
                if (seleccion_modo == BATALLA) {
                    sacar_globo_jugador(jugador, indice_jugador);
                }
                quitar_efectos_trompo(jugador, indice_jugador);
            }
        }
    } else {
        jugador->rotacion[1] += sp30[jugador->desconocido_0B2];
        dato_8018D920[indice_jugador] -= sp30[jugador->desconocido_0B2];
        margen_pila_2 = (u16) dato_8018D920[indice_jugador] / (0x10000 / (0x168 / (sp30[jugador->desconocido_0B2] / GRADOS(1))));
        if (margen_pila_2 == 0) {
            jugador->desconocido_0B2--;
            if (jugador->desconocido_0B2 <= 0) {
                quitar_efectos_trompo(jugador, indice_jugador);
                if (seleccion_modo == BATALLA) {
                    sacar_globo_jugador(jugador, indice_jugador);
                }
            }
        }
    }
    if ((es_jugador_triple_a_boton_combo[indice_jugador] == true) && ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR)) {
        temporizador_impulso_triple_a_combo[indice_jugador] = 0x00000078;
        if (jugador->actual_rapidez <= 90.0f) {
            jugador->actual_rapidez = 90.0f;
        }
    }
}

void banana_golpe_disparador(Jugador* jugador, s8 indice_jugador) {
    limpiar_efecto(jugador, indice_jugador);

    jugador->disparadores &= ~DISPARADOR_BANANA_GOLPE;
    jugador->temporizador_esquivar = 0;
    jugador->inicializacion_acel_esquivar = 3.0f;
    jugador->sentido_esquivar = 1;
    jugador->efectos &= ~EFECTO_DERRAPANDO;

    if (((jugador->posicion_giro >> 16) >= 20) || ((jugador->posicion_giro >> 16) <= -20) ||
        (((jugador->speed / 18.0f) * 216.0f) <= 30.0f) || ((jugador->efectos & EFECTO_EN_EL_AIRE) != 0) ||
        (((jugador->type & HUMANO_JUGADOR) == 0) && ((jugador->efectos & EFECTO_CARRERA_PERDIDO) == 0))) {
        agregar_efecto_trompo(jugador, indice_jugador);
    } else {
        jugador->efectos |= BANANA_CERCA_EFECTO_TROMPO;
    }
}

void aplicar_banana_cerca_efecto_trompo(Jugador* jugador, s8 indice_jugador) {
    f32 inicializar_acel_esquivar;
    s16 esquivar_temporizador;
    s16 esquivar_sentido;
    s16 esquivar_actual_vel;

    inicializar_acel_esquivar = jugador->inicializacion_acel_esquivar;
    esquivar_temporizador = jugador->temporizador_esquivar;
    esquivar_sentido = jugador->sentido_esquivar;
    esquivar_temporizador++;
    esquivar_actual_vel = (esquivar_temporizador * inicializar_acel_esquivar) - (0.2 * (esquivar_temporizador * esquivar_temporizador));
    if ((esquivar_temporizador != 0) && (esquivar_actual_vel < 0)) {
        esquivar_temporizador = 0;
        esquivar_sentido = -esquivar_sentido;
        inicializar_acel_esquivar *= 0.8;
        if ((jugador->efectos & EFECTO_FRENADO) == EFECTO_FRENADO) {
            jugador->efectos |= BANANA_TROMPO_GUARDADO_EFECTO;
        }
        if (inicializar_acel_esquivar <= 1.0f) {
            jugador->efectos &= ~BANANA_CERCA_EFECTO_TROMPO;
            if ((jugador->efectos & BANANA_TROMPO_GUARDADO_EFECTO) != BANANA_TROMPO_GUARDADO_EFECTO) {
                agregar_efecto_trompo(jugador, indice_jugador);
                esquivar_temporizador = 0;
            } else {
                jugador->graficos_kart |= SILBATO;
                jugador->efectos &= ~BANANA_TROMPO_GUARDADO_EFECTO;
                if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
                    funcion_800C90F4(indice_jugador, (jugador->id_personaje * 0x10) + 0x29008008);
                    esquivar_temporizador = 0;
                }
            }
        }
    }
    esquivar_actual_vel *= esquivar_sentido;
    if ((esquivar_actual_vel <= 0) && (esquivar_sentido == 1)) {
        esquivar_actual_vel = 0;
    }
    if ((esquivar_actual_vel >= 0) && (esquivar_sentido == -1)) {
        esquivar_actual_vel = 0;
    }
    jugador->desconocido_078 += esquivar_actual_vel * 18;
    jugador->inicializacion_acel_esquivar = inicializar_acel_esquivar;
    jugador->temporizador_esquivar = esquivar_temporizador;
    jugador->sentido_esquivar = esquivar_sentido;
    if (jugador->efectos & EFECTO_EN_EL_AIRE) {
        agregar_efecto_trompo(jugador, indice_jugador);
        jugador->efectos &= ~BANANA_CERCA_EFECTO_TROMPO;
    }
}

void quitar_banana_cerca_efecto_trompo(Jugador* jugador, SIN_USO s8 indice_jugador) {
    jugador->efectos &= ~BANANA_CERCA_EFECTO_TROMPO;
}

void trompo_conduciendo_disparador(Jugador* jugador, s8 indice_jugador) {
    limpiar_efecto(jugador, indice_jugador);

    jugador->disparadores &= ~DISPARADOR_TROMPO_CONDUCIENDO;
    jugador->temporizador_esquivar = 0;
    jugador->inicializacion_acel_esquivar = 2.0f;
    jugador->sentido_esquivar = 1;
    jugador->efectos &= ~EFECTO_DERRAPANDO;
    jugador->kart_props |= CONDUCIENDO_CERCA_TROMPO;
}

void aplicar_conduciendo_cerca_efecto_trompo(Jugador* jugador, s8 indice_jugador) {
    f32 inicializar_acel_esquivar;
    s16 esquivar_temporizador;
    s16 esquivar_sentido;
    s16 esquivar_actual_vel;

    inicializar_acel_esquivar = jugador->inicializacion_acel_esquivar;
    esquivar_temporizador = jugador->temporizador_esquivar;
    esquivar_sentido = jugador->sentido_esquivar;
    esquivar_temporizador++;

    esquivar_actual_vel = (inicializar_acel_esquivar * esquivar_temporizador) - (0.1 * (esquivar_temporizador * esquivar_temporizador));

    if ((esquivar_temporizador != 0) && (esquivar_actual_vel < 0)) {
        esquivar_temporizador = 0;
        esquivar_sentido = -esquivar_sentido;
        inicializar_acel_esquivar *= 0.9;
        if (((jugador->efectos & EFECTO_FRENADO) == EFECTO_FRENADO) || !(jugador->kart_props & ACELERADOR)) {
            jugador->efectos |= BANANA_TROMPO_GUARDADO_EFECTO;
        }
        if (inicializar_acel_esquivar <= 1.3) {
            jugador->kart_props &= ~CONDUCIENDO_CERCA_TROMPO;
            if ((jugador->efectos & BANANA_TROMPO_GUARDADO_EFECTO) != BANANA_TROMPO_GUARDADO_EFECTO) {
                agregar_efecto_trompo(jugador, indice_jugador);
                esquivar_temporizador = 0;
            } else {
                jugador->graficos_kart |= SILBATO;
                jugador->efectos &= ~BANANA_TROMPO_GUARDADO_EFECTO;
                if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
                    funcion_800C90F4(indice_jugador, (jugador->id_personaje * 0x10) + 0x29008008);
                    esquivar_temporizador = 0;
                }
            }
        }
    }
    esquivar_actual_vel *= esquivar_sentido;
    if ((esquivar_actual_vel <= 0) && (esquivar_sentido == 1)) {
        esquivar_actual_vel = 0;
    }
    if ((esquivar_actual_vel >= 0) && (esquivar_sentido == -1)) {
        esquivar_actual_vel = 0;
    }
    jugador->desconocido_078 += esquivar_actual_vel * 20;
    jugador->inicializacion_acel_esquivar = inicializar_acel_esquivar;
    jugador->temporizador_esquivar = esquivar_temporizador;
    jugador->sentido_esquivar = esquivar_sentido;
    if (jugador->efectos & EFECTO_EN_EL_AIRE) {
        agregar_efecto_trompo(jugador, indice_jugador);
        jugador->kart_props &= ~CONDUCIENDO_CERCA_TROMPO;
    }
}

void quitar_conduciendo_cerca_efecto_trompo(Jugador* jugador, SIN_USO s8 indice_jugador) {
    jugador->kart_props &= ~CONDUCIENDO_CERCA_TROMPO;
}

void hongo_disparador(Jugador* jugador, s8 indice_jugador) {

    limpiar_efecto(jugador, indice_jugador);

    jugador->efectos |= EFECTO_HONGO;
    jugador->disparadores &= ~DISPARADOR_HONGO;
    jugador->desconocido_DB4.desconocido0 = 0;
    jugador->desconocido_DB4.desconocido8 = 8.0f;

    if (dato_8015F890 != 1) {
        if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
            ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
            funcion_800C9250(indice_jugador);
            funcion_800C9060(indice_jugador, 0x1900A40B);
        }
    } else {
        if (jugador == jugador_uno) {
            funcion_800C9250(indice_jugador);
            funcion_800C9060(indice_jugador, 0x1900A40B);
        }
    }

    jugador->temporizador_impulso = 0x50;
}

void aplicar_efecto_hongo(Jugador* jugador) {
    jugador->actual_rapidez = (f32) jugador->arriba_rapidez;
    if (jugador->temporizador_impulso > 0) {
        --jugador->temporizador_impulso;
    }

    if (jugador->temporizador_impulso != 0) {
        mover_f32_hacia(&jugador->potencia_impulso, 400.0f, 0.5f);
    } else {
        mover_f32_hacia(&jugador->potencia_impulso, 0.0f, 0.1f);
    }

    if (jugador->potencia_impulso <= 1.0f) {
        jugador->efectos &= ~EFECTO_HONGO;
    }
}

void quitar_efecto_hongo(Jugador* jugador) {
    jugador->efectos &= ~EFECTO_HONGO;
    jugador->potencia_impulso = 0.0f;
}

void funcion_8008D570(Jugador* jugador, s8 indice_jugador) {
    limpiar_efecto(jugador, indice_jugador);

    jugador->desconocido_0AE = jugador->rotacion[1];
    jugador->efectos |= desconocido_efecto_0_x_80000;
    jugador->efectos &= ~EFECTO_DERRAPANDO;
    jugador->disparadores &= ~sin_uso_disparador_0_x_1000;
    jugador->tiron_salto_kart = dato_800E3730[jugador->id_personaje];
    jugador->aceleracion_salto_kart = 0.0f;
    jugador->velocidad_salto_kart = (f32) dato_800E3710[jugador->id_personaje];
    jugador->desconocido_0B2 = 1;
    jugador->desconocido_0C0 = 0;
    jugador->posicion_giro = 0;
    jugador->desconocido_078 = 0;
    dato_8018D920[indice_jugador] = 0;

    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
        funcion_800C9060(indice_jugador, 0x19008002);
    }

    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
        funcion_800C90F4(indice_jugador, (jugador->id_personaje * 0x10) + 0x2900800C);
    }
}

void funcion_8008D698(Jugador* jugador, s8 indice_jugador) {
    s16 temporal_;

    if (jugador->desconocido_0B2 == 0) {
        jugador->rotacion[1] = jugador->desconocido_0AE;
        temporal_ = 0;
    } else {
        jugador->rotacion[1] -= GRADOS(10);
        dato_8018D920[indice_jugador] -= GRADOS(10);
        temporal_ = ((u16) dato_8018D920[indice_jugador] / GRADOS(10));
    }
    if (temporal_ == 0) {
        --jugador->desconocido_0B2;
        if (jugador->desconocido_0B2 <= 0) {
            jugador->desconocido_0B2 = 0;
        }
        if ((jugador->desconocido_0B2 == 0) && ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE)) {
            funcion_8008D760(jugador);
        }
    }
}

void funcion_8008D760(Jugador* jugador) {
    jugador->desconocido_0A8 = 0;
    jugador->posicion_giro = 0;
    jugador->desconocido_0C0 = 0;
    jugador->rotacion[1] = jugador->desconocido_0AE;
    jugador->efectos &= ~desconocido_efecto_0_x_80000;
    jugador->gravedad_kart = tabla_gravedad_kart[jugador->id_personaje];
    jugador->type &= ~jugador_desconocido_0_x80;
}

void funcion_8008D7B0(Jugador* jugador, s8 indice_jugador) {
    limpiar_efecto(jugador, indice_jugador);

    jugador->desconocido_0AE = jugador->rotacion[1];
    jugador->efectos |= desconocido_efecto_0_x_800000;
    jugador->efectos &= ~EFECTO_DERRAPANDO;
    jugador->disparadores &= ~sin_uso_disparador_0_x_20000;
    jugador->tiron_salto_kart = dato_800E3770[jugador->id_personaje];
    jugador->aceleracion_salto_kart = 0.0f;
    jugador->velocidad_salto_kart = dato_800E3750[jugador->id_personaje];
    dato_8018D920[indice_jugador] = 0;
    jugador->desconocido_0B2 = 4;
    jugador->desconocido_0C0 = 0;
    jugador->posicion_giro = 0;
    jugador->desconocido_078 = 0;

    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
        funcion_800C90F4(indice_jugador, (jugador->id_personaje * 0x10) + 0x29008003);
    }
}

void funcion_8008D8B4(Jugador* jugador, s8 indice_jugador) {
    s16 temporal_;

    if (jugador->desconocido_0B2 == 0) {
        jugador->rotacion[1] = jugador->desconocido_0AE;
        temporal_ = 0;
    } else {
        jugador->rotacion[1] -= GRADOS(10);
        dato_8018D920[indice_jugador] -= GRADOS(10);
        temporal_ = ((u16) (dato_8018D920[indice_jugador]) / GRADOS(10));
    }
    if (temporal_ == 0) {
        --jugador->desconocido_0B2;
        if (jugador->desconocido_0B2 <= 0) {
            jugador->desconocido_0B2 = 0;
        }
        if ((jugador->desconocido_0B2 == 0) && ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE)) {
            funcion_8008D97C(jugador);
        }
    }
}

void funcion_8008D97C(Jugador* jugador) {
    jugador->desconocido_0A8 = 0;
    jugador->posicion_giro = 0;
    jugador->desconocido_0C0 = 0;
    jugador->rotacion[1] = jugador->desconocido_0AE;
    jugador->efectos &= ~desconocido_efecto_0_x_800000;
    jugador->gravedad_kart = tabla_gravedad_kart[jugador->id_personaje];
}

void funcion_8008D9C0(Jugador* jugador) {
    jugador->desconocido_DA0 += 8.0f;
    if (jugador->desconocido_DA0 >= 140.0f) {
        jugador->desconocido_DA0 = 140.0f;
    }

    if (jugador->desconocido_D98 == 1) {
        jugador->desconocido_D9C += jugador->desconocido_DA0;
        if (2002.0f <= jugador->desconocido_D9C) {
            jugador->desconocido_DA0 = 10.0f;
            jugador->desconocido_D98 *= -1;
        }
    }
    if (jugador->desconocido_D98 == -1) {
        jugador->desconocido_D9C -= jugador->desconocido_DA0;
        if (jugador->desconocido_D9C <= -2002.0f) {
            jugador->desconocido_DA0 = 10.0f;
            jugador->desconocido_D98 *= -1;
        }
    }
}

void aplastamiento_disparador(Jugador* jugador, s8 indice_jugador) {
    limpiar_efecto(jugador, indice_jugador);

    if ((jugador->efectos & EFECTO_APLASTAMIENTO) == 0) {
        jugador->desconocido_DB4.desconocido2 = 0;
        jugador->desconocido_238 = 0;
        jugador->desconocido_DB4.unk10 = 4.5f;
        dato_8018D990[indice_jugador] = 0;
        jugador->efectos &= ~(EFECTO_APLASTAMIENTO_PUBLICAR | EFECTO_DERRAPANDO);
        dato_80165190[0][indice_jugador] = 1;
        dato_80165190[1][indice_jugador] = 1;
        dato_80165190[2][indice_jugador] = 1;
        dato_80165190[3][indice_jugador] = 1;
        jugador->desconocido_D98 = 1;
        jugador->desconocido_D9C = 0.0f;
        jugador->desconocido_DA0 = 65.0f;

        if ((jugador->disparadores & THWOMP_DISPARADOR_APLASTAMIENTO) != 0) {
            jugador->desconocido_046 |= 0x80;
        }

        if (((jugador->type & HUMANO_JUGADOR) != 0) && ((jugador->efectos & EFECTO_APLASTAMIENTO) == 0)) {
            funcion_800C90F4(indice_jugador, (jugador->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x05));
        }

        jugador->efectos |= EFECTO_APLASTAMIENTO;
        if (((jugador->type) & CPU_JUGADOR) != 0) {
            reproducir_cpu_efecto_sonido(indice_jugador, jugador);
        }
    }
}

void aplicar_efecto_golpe(Jugador* jugador, s8 indice_jugador) {
    jugador->desconocido_0C2 = 0;
    jugador->desconocido_0A8 = 0;
    jugador->posicion_giro = 0;
    jugador->desconocido_0C0 = 0;
    jugador->desconocido_08C = 0.0f;
    jugador->actual_rapidez = 0.0f;
    if ((jugador->colision.distancia_superficie[2] >= 600.0f) || ((jugador->efectos & EFECTO_CARRERA_PERDIDO) != 0)) { dato_8018D990[indice_jugador] = 3; }

    switch (dato_8018D990[indice_jugador]) {
        case 0:
            jugador->desconocido_DB4.unk10 = 4.5f;
            if (jugador->desconocido_238 < 0x3D) {
                ++jugador->desconocido_238;
            }

            if ((jugador->desconocido_046 & 0x80) != 0) {
                if ((jugador->disparadores & THWOMP_DISPARADOR_APLASTAMIENTO) == 0) {
                    dato_8018D990[indice_jugador] = 1;
                    jugador->desconocido_238 = 0;
                    if ((jugador->type & HUMANO_JUGADOR) != 0) {
                        funcion_800C9060(indice_jugador, 0x1901904B);
                        break;
                    }
                }
            } else {
                ++jugador->desconocido_238;
                if (jugador->desconocido_238 >= 0x1E) {
                    dato_8018D990[indice_jugador] = 1;
                    jugador->desconocido_238 = 0;
                    if ((jugador->type & HUMANO_JUGADOR) != 0) {
                        funcion_800C9060(indice_jugador, 0x1901904B);
                        break;
                    }
                }
                break;
            }

            break;
        case 1:
            jugador->desconocido_DB4.unk10 = 4.5f;
            jugador->pos[1] += 0.13;
            ++jugador->desconocido_238;

            if ((jugador->desconocido_046 & 0x80) != 0) {
                if (jugador->desconocido_238 >= 0x32) {
                    dato_8018D990[indice_jugador] = 2;
                    jugador->desconocido_238 = 0;
                    jugador->desconocido_046 &= 0xFF7F;
                }
            } else if (jugador->desconocido_238 >= 0x50) {
                dato_8018D990[indice_jugador] = 2;
                jugador->desconocido_238 = 0;
            }

            jugador->desconocido_DA0 += 6.0f;
            if (jugador->desconocido_DA0 >= 90.0f) {
                jugador->desconocido_DA0 = 90.0f;
            }

            jugador->desconocido_D9C += jugador->desconocido_DA0;
            if (3458.0f <= jugador->desconocido_D9C) {
                jugador->desconocido_DA0 = 0.0f;
                break;
            }
            break;
        case 2:
            ++jugador->desconocido_238;
            if (jugador->desconocido_238 >= 0x259) {
                dato_8018D990[indice_jugador] = 3;
                jugador->desconocido_238 = 0;
            }

            if (jugador->colision.distancia_superficie[2] >= 600.0f) {
                dato_8018D990[indice_jugador] = 3;
            }

            jugador->desconocido_DB4.unk10 = 4.5f;
            jugador->pos[1] -= 0.085;

            if ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) {
                dato_8018D990[indice_jugador] = 3;
                jugador->desconocido_238 = 0;
            }

            funcion_8008D9C0(jugador);
            break;
        case 3:
            jugador->desconocido_DB4.unk10 = 3.0f;
            jugador->efectos &= ~EFECTO_APLASTAMIENTO;
            jugador->desconocido_DB4.desconocido2 = 0;
            jugador->efectos |= EFECTO_APLASTAMIENTO_PUBLICAR;
            jugador->size = 1.0f;
            jugador->tamanio_caja_envolvente = kart_envolvente_caja_tamanio_tabla[jugador->id_personaje];
            dato_80165190[0][indice_jugador] = 1;
            dato_80165190[1][indice_jugador] = 1;
            dato_80165190[2][indice_jugador] = 1;
            dato_80165190[3][indice_jugador] = 1;

            if ((jugador->type & HUMANO_JUGADOR) != 0) {
                funcion_800C90F4(indice_jugador, (jugador->id_personaje * 0x10) + 0x29008008);
            }
            break;
    }
}

void golpe_rayo_disparador(Jugador* jugador, s8 indice_jugador) {
    limpiar_efecto(jugador, indice_jugador);

    jugador->disparadores &= ~DISPARADOR_GOLPE_RAYO;
    jugador->efectos |= (EFECTO_RAYO | EFECTO_GOLPE_RAYO);
    jugador->efectos &= ~EFECTO_DERRAPANDO;
    jugador->desconocido_08C *= 0.6;
    jugador->desconocido_0B0 = 0;
    jugador->size = 1.0f;
    jugador_estrella_efecto_inicio_tiempo[indice_jugador] = temporizador_circuito;
    jugador->desconocido_0AE = jugador->rotacion[1];
    jugador->desconocido_0B2 = 2;
    jugador->desconocido_0C0 = 0;
    jugador->posicion_giro = 0;
    jugador->desconocido_078 = 0;

    dato_80165190[0][indice_jugador] = 1;
    dato_80165190[1][indice_jugador] = 1;
    dato_80165190[2][indice_jugador] = 1;
    dato_80165190[3][indice_jugador] = 1;

    dato_8018D920[indice_jugador] = 0;

    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
        funcion_800C90F4(indice_jugador, (jugador->id_personaje * 0x10) + 0x29008003);
    } else {
        reproducir_cpu_efecto_sonido(indice_jugador, jugador);
    }
    if (seleccion_modo == BATALLA) {
        sacar_globo_jugador(jugador, indice_jugador);
    }
}

void aplicar_efecto_rayo(Jugador* jugador, s8 indice_jugador) {
    s16 probar;
    if (((jugador->efectos & EFECTO_GOLPE_ENEMIGO) == EFECTO_GOLPE_ENEMIGO) &&
        ((jugador->efectos & EFECTO_APLASTAMIENTO) != EFECTO_APLASTAMIENTO)) {
        jugador->efectos &= ~EFECTO_GOLPE_RAYO;
        jugador->desconocido_0A8 = 0;
        jugador->posicion_giro = 0;
        jugador->desconocido_0C0 = 0;
        jugador->rotacion[1] = jugador->desconocido_0AE;
        quitar_efecto_rayo(jugador, indice_jugador);
        dato_80165190[0][indice_jugador] = 1;
        dato_80165190[1][indice_jugador] = 1;
        dato_80165190[2][indice_jugador] = 1;
        dato_80165190[3][indice_jugador] = 1;
        aplastamiento_disparador(jugador, indice_jugador);
    } else if ((jugador->efectos & EFECTO_GOLPE_RAYO) == EFECTO_GOLPE_RAYO) {
        jugador->rotacion[1] -= GRADOS(8);
        dato_8018D920[indice_jugador] -= GRADOS(8);
        probar = (u16) dato_8018D920[indice_jugador] / GRADOS(8);
        if (probar == 0) {
            jugador->desconocido_0B2--;
            if (jugador->desconocido_0B2 <= 0) {
                jugador->desconocido_0A8 = 0;
                jugador->efectos &= ~EFECTO_GOLPE_RAYO;
                jugador->posicion_giro = 0;
                jugador->desconocido_0C0 = 0;
                jugador->rotacion[1] = jugador->desconocido_0AE;
                dato_80165190[0][indice_jugador] = 1;
                dato_80165190[1][indice_jugador] = 1;
                dato_80165190[2][indice_jugador] = 1;
                dato_80165190[3][indice_jugador] = 1;
            }
        }
        alternativo_desacelerar_jugador(jugador, 1.0f);
    } else {
        jugador->desconocido_0B0 += 1;
        jugador->desconocido_08C = (f32) ((f64) jugador->desconocido_08C * 0.6);
        if ((jugador->desconocido_0B0 == 1) && (jugador->type & HUMANO_JUGADOR)) {
            funcion_800C90F4(indice_jugador, (jugador->id_personaje * 0x10) + 0x29008005);
        }
        if ((jugador->desconocido_0B0 >= 0) && (jugador->desconocido_0B0 < 0x1CC)) {
            mover_f32_hacia(&jugador->size, 0.7f, 0.1f);
            mover_f32_hacia(&jugador->tamanio_caja_envolvente,
                             (f32) ((f64) kart_envolvente_caja_tamanio_tabla[jugador->id_personaje] * 0.9), 0.1f);
        } else {
            quitar_efecto_rayo(jugador, indice_jugador);
            if (jugador->type & HUMANO_JUGADOR) {
                funcion_800C90F4(indice_jugador, (jugador->id_personaje * 0x10) + 0x29008008);
            }
        }
    }
}
