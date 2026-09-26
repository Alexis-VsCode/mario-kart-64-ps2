// Giro y derrape

void funcion_80033AE0(Jugador* jugador, struct Mando* mando, s8 indice_jugador) {
    s32 girar_posicion;
    s32 limitado_x;
    SIN_USO s32 relleno[2];
    SIN_USO s16 relleno2;
    s16 variable_s1_2;
    s32 girar_delta_posicion;
    s32 girar_giro_chico_resistencia;
    s32 girar_giro_grande_resistencia;
    f32 variable_f2_2;
    f32 variable_f12 = 0.0f;
    f32 zero = 0;
    SIN_USO s32 relleno3;
    s32 variable_a0;
    f32 sp44[156] = { 0.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.6, 0.6, 0.6, 0.6, 0.6, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7,
                      0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6,
                      0.5, 0.5, 0.5, 0.5, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.7, 0.7, 0.7, 0.7,
                      0.7, 0.7, 0.6, 0.6, 0.6, 0.6, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7,
                      0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7,
                      0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7,
                      0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8,
                      0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8,
                      0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8 };

    if (
         (
           ((jugador->efectos & EFECTO_SALTO) != EFECTO_SALTO) &&
           (
             ((jugador->desconocido_0C0 / GRADOS(1) <= 6) && (jugador->desconocido_0C0 / GRADOS(1) >= -6)) ||
             ((mando->button & R_TRIG) != R_TRIG)
           )
         ) ||
         (((jugador->speed / 18.0f) * 216.0f) <= 20.0f) ||
         ((jugador->efectos & EFECTO_GOLPE_ENEMIGO) == EFECTO_GOLPE_ENEMIGO)
       ) {
       cancelar_efecto_derrape(jugador);
    }
    if ((jugador->desconocido_0C0 / GRADOS(1)) < (-5)) {
        jugador->kart_props |= GIRO_IZQUIERDA;
        jugador->kart_props &= ~GIRO_DERECHA;
        dato_801652C0[indice_jugador]++;
    } else if ((jugador->desconocido_0C0 / GRADOS(1)) > 5) {
        jugador->kart_props |= GIRO_DERECHA;
        jugador->kart_props &= ~GIRO_IZQUIERDA;
        dato_801652C0[indice_jugador]++;
    } else {
        jugador->kart_props &= ~(GIRO_IZQUIERDA | GIRO_DERECHA);
        dato_801652C0[indice_jugador] = 0;
    }
    if (((jugador->efectos & EFECTO_SALTO) == EFECTO_SALTO) || ((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO)) {
        jugador->kart_props &= ~(GIRO_IZQUIERDA | GIRO_DERECHA);
    }
    girar_posicion = jugador->posicion_giro;
    limitado_x = obtener_limitado_palanca_x_con_zona_muerta(mando);
    if (((jugador->kart_props & ARRIBA_ATRAS) == ARRIBA_ATRAS) || ((jugador->kart_props & HACIA_ATRAS_MOVIMIENTO) == HACIA_ATRAS_MOVIMIENTO)) {
        limitado_x = -limitado_x;
    }
    jugador->posicion_giro = (limitado_x << 16) & 0xFFFF0000;
    girar_delta_posicion = girar_posicion - jugador->posicion_giro;
    girar_delta_posicion = girar_delta_posicion >> 16;
    jugador->delta_posicion_giro = (s16) girar_delta_posicion;
    if (((girar_delta_posicion >= 90) || (girar_delta_posicion <= -90)) && (!(jugador->kart_props & CONDUCIENDO_CERCA_TROMPO))) {
        if ((((((!(jugador->efectos & EFECTO_DERRAPANDO)) && (seleccion_cc == CC_150)) && (seleccion_modo != BATALLA)) &&
              (!(jugador->efectos & EFECTO_EN_EL_AIRE))) &&
             (((jugador->speed / 18.0f) * 216.0f) >= 40.0f)) &&
            (jugador->duracion_derrape == 0)) {
            jugador->disparadores |= DISPARADOR_TROMPO_CONDUCIENDO;
        }
    }
    if (((s32) jugador->ruedas[DERECHA_ATRAS].tipo_superficie) < 0xF) {
        zero += dato_800E3610[jugador->id_personaje][jugador->ruedas[DERECHA_ATRAS].tipo_superficie];
    }
    if (((s32) jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie) < 0xF) {
        zero += dato_800E3610[jugador->id_personaje][jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie];
    }
    if ((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB) {
        girar_giro_grande_resistencia = 10;
        girar_giro_chico_resistencia = 10;
    } else {
        if (((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) &&
            ((jugador->efectos & EFECTO_SALTO) != EFECTO_SALTO)) {
            variable_a0 = 3;
        } else {
            variable_a0 = 0;
        }
        if (((jugador->speed / 18.0f) * 216.0f) >= 15.0f) {
            if ((jugador->kart_props & GIRO_DERECHA) == GIRO_DERECHA) {
                if ((girar_delta_posicion <= 35) && (girar_delta_posicion >= 0)) {
                    girar_giro_grande_resistencia =
                        (tabla_kart_800E3650[jugador->id_personaje] + 1.0f) * (((f32) (variable_a0 + 15)) * (1.0f + zero));
                    girar_giro_chico_resistencia =
                        (tabla_kart_800E3650[jugador->id_personaje] + 1.0f) * (((f32) (variable_a0 + 15)) * (1.0f + zero));
                } else {
                    girar_giro_grande_resistencia = (s32) (((f32) (variable_a0 + 5)) * (1.0f + zero));
                    girar_giro_chico_resistencia = (s32) (((f32) (variable_a0 + 9)) * (1.0f + zero));
                }
            } else if ((jugador->kart_props & GIRO_IZQUIERDA) == GIRO_IZQUIERDA) {
                if ((girar_delta_posicion >= -35) && (girar_delta_posicion <= 0)) {
                    girar_giro_grande_resistencia =
                        (tabla_kart_800E3650[jugador->id_personaje] + 1.0f) * (((f32) (variable_a0 + 15)) * (1.0f + zero));
                    girar_giro_chico_resistencia =
                        (tabla_kart_800E3650[jugador->id_personaje] + 1.0f) * (((f32) (variable_a0 + 15)) * (1.0f + zero));
                } else {
                    girar_giro_grande_resistencia = (s32) (((f32) (variable_a0 + 5)) * (1.0f + zero));
                    girar_giro_chico_resistencia = (s32) (((f32) (variable_a0 + 9)) * (1.0f + zero));
                }
            } else {
                girar_giro_grande_resistencia = (s32) (((f32) (variable_a0 + 3)) * (1.0f + zero));
                girar_giro_chico_resistencia = (s32) (((f32) (variable_a0 + 6)) * (1.0f + zero));
            }
        } else {
            girar_giro_grande_resistencia = 8;
            girar_giro_chico_resistencia = 8;
        }
    }
    if ((jugador->oob_props & BAJO_OOB_O_NIVEL_FLUIDO) == BAJO_OOB_O_NIVEL_FLUIDO) {
        girar_giro_grande_resistencia *= 1.5;
        girar_giro_chico_resistencia *= 1.5;
    } else {
        if ((jugador->oob_props & OOB_PASADA_O_NIVEL_FLUIDO) == OOB_PASADA_O_NIVEL_FLUIDO) {
            girar_giro_grande_resistencia *= 1.2;
            girar_giro_chico_resistencia *= 1.2;
        }
        if ((((f64) (dato_801652A0[indice_jugador] - jugador->ruedas[IZQUIERDA_ATRAS].altura_base)) >= 3.5) ||
            (((f64) (dato_801652A0[indice_jugador] - jugador->ruedas[DERECHA_ATRAS].altura_base)) >= 3.5)) {
            girar_giro_grande_resistencia *= 1.05;
            girar_giro_chico_resistencia *= 1.05;
        }
    }

    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 90, (120 << 12) / girar_giro_grande_resistencia, 450);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 89, (118 << 12) / girar_giro_grande_resistencia, 440);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 88, (116 << 12) / girar_giro_grande_resistencia, 430);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 87, (114 << 12) / girar_giro_grande_resistencia, 420);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 86, (112 << 12) / girar_giro_grande_resistencia, 410);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 85,  (88 << 12) / girar_giro_grande_resistencia, 400);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 84,  (86 << 12) / girar_giro_grande_resistencia, 395);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 83,  (80 << 12) / girar_giro_grande_resistencia, 390);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 82,  (79 << 12) / girar_giro_grande_resistencia, 390);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 81,  (78 << 12) / girar_giro_grande_resistencia, 380);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 80,  (77 << 12) / girar_giro_grande_resistencia, 370);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 79,  (76 << 12) / girar_giro_grande_resistencia, 360);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 78,  (76 << 12) / girar_giro_grande_resistencia, 360);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 77,  (75 << 12) / girar_giro_grande_resistencia, 350);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 76,  (74 << 12) / girar_giro_grande_resistencia, 340);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 75,  (73 << 12) / girar_giro_grande_resistencia, 330);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 74,  (73 << 12) / girar_giro_grande_resistencia, 330);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 73,  (73 << 12) / girar_giro_grande_resistencia, 330);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 72,  (72 << 12) / girar_giro_grande_resistencia, 320);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 71,  (71 << 12) / girar_giro_grande_resistencia, 315);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 70,  (71 << 12) / girar_giro_grande_resistencia, 315);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 69,  (70 << 12) / girar_giro_grande_resistencia, 305);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 68,  (70 << 12) / girar_giro_grande_resistencia, 305);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 67,  (69 << 12) / girar_giro_grande_resistencia, 280);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 66,  (70 << 12) / girar_giro_grande_resistencia, 270);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 65,  (69 << 12) / girar_giro_grande_resistencia, 270);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 64,  (68 << 12) / girar_giro_grande_resistencia, 260);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 63,  (67 << 12) / girar_giro_grande_resistencia, 250);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 62,  (67 << 12) / girar_giro_grande_resistencia, 250);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 61,  (67 << 12) / girar_giro_grande_resistencia, 250);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 60,  (61 << 12) / girar_giro_grande_resistencia, 245);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 59,  (60 << 12) / girar_giro_grande_resistencia, 245);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 58,  (59 << 12) / girar_giro_grande_resistencia, 245);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 57,  (58 << 12) / girar_giro_grande_resistencia, 245);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 56,  (56 << 12) / girar_giro_grande_resistencia, 245);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 55,  (56 << 12) / girar_giro_grande_resistencia, 230);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 54,  (56 << 12) / girar_giro_grande_resistencia, 230);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 53,  (56 << 12) / girar_giro_grande_resistencia, 230);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 52,  (56 << 12) / girar_giro_grande_resistencia, 230);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 51,  (56 << 12) / girar_giro_grande_resistencia, 230);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 50,  (50 << 12) / girar_giro_grande_resistencia, 220);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 49,  (50 << 12) / girar_giro_grande_resistencia, 220);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 48,  (50 << 12) / girar_giro_grande_resistencia, 220);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 47,  (50 << 12) / girar_giro_grande_resistencia, 220);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 46,  (50 << 12) / girar_giro_grande_resistencia, 220);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 45,  (48 << 12) / girar_giro_grande_resistencia, 110);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 44,  (46 << 12) / girar_giro_grande_resistencia, 110);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 43,  (46 << 12) / girar_giro_grande_resistencia, 110);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 42,  (46 << 12) / girar_giro_grande_resistencia, 110);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 41,  (46 << 12) / girar_giro_grande_resistencia, 110);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 40,  (46 << 12) / girar_giro_grande_resistencia, 110);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 39,  (44 << 12) / girar_giro_grande_resistencia, 110);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 38,  (40 << 12) / girar_giro_grande_resistencia, 110);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 37,  (40 << 12) / girar_giro_grande_resistencia, 110);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 36,  (36 << 12) / girar_giro_grande_resistencia, 110);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 35,  (36 << 12) / girar_giro_grande_resistencia, 110);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 34,  (34 << 12) / girar_giro_grande_resistencia, 110);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 32,  (32 << 12) / girar_giro_grande_resistencia, 100);
    actualizar_grande_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 31,  (32 << 12) / girar_giro_grande_resistencia, 100);

    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 30,  (31 << 12) / girar_giro_chico_resistencia, 0.9f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 29,  (30 << 12) / girar_giro_chico_resistencia, 0.9f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 28,  (29 << 12) / girar_giro_chico_resistencia, 0.9f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 27,  (28 << 12) / girar_giro_chico_resistencia, 0.9f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 26,  (27 << 12) / girar_giro_chico_resistencia, 0.9f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 25,  (26 << 12) / girar_giro_chico_resistencia, 1.0f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 24,  (25 << 12) / girar_giro_chico_resistencia, 1.0f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 23,  (24 << 12) / girar_giro_chico_resistencia, 1.0f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 22,  (23 << 12) / girar_giro_chico_resistencia, 1.0f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 21,  (22 << 12) / girar_giro_chico_resistencia, 1.0f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 20,  (21 << 12) / girar_giro_chico_resistencia, 1.05f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 19,  (20 << 12) / girar_giro_chico_resistencia, 1.05f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 18,  (19 << 12) / girar_giro_chico_resistencia, 1.05f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 17,  (18 << 12) / girar_giro_chico_resistencia, 1.05f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 16,  (17 << 12) / girar_giro_chico_resistencia, 1.05f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 15,  (16 << 12) / girar_giro_chico_resistencia, 1.2f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 14,  (15 << 12) / girar_giro_chico_resistencia, 1.2f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 13,  (14 << 12) / girar_giro_chico_resistencia, 1.2f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 12,  (13 << 12) / girar_giro_chico_resistencia, 1.2f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 11,  (12 << 12) / girar_giro_chico_resistencia, 1.2f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro, 10,  (14 << 12) / girar_giro_chico_resistencia, 1.6f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro,  9,  (13 << 12) / girar_giro_chico_resistencia, 1.6f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro,  8,  (12 << 12) / girar_giro_chico_resistencia, 1.6f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro,  7,  (11 << 12) / girar_giro_chico_resistencia, 1.6f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro,  6,  (10 << 12) / girar_giro_chico_resistencia, 1.6f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro,  5,   (9 << 12) / girar_giro_chico_resistencia, 1.9f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro,  4,   (8 << 12) / girar_giro_chico_resistencia, 1.9f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro,  3,   (7 << 12) / girar_giro_chico_resistencia, 1.9f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro,  2,   (6 << 12) / girar_giro_chico_resistencia, 1.9f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro,  1,   (5 << 12) / girar_giro_chico_resistencia, 1.9f);
    actualizar_chico_direccion(jugador, &girar_delta_posicion, &girar_posicion, jugador->posicion_giro,  0,           0 / girar_giro_chico_resistencia, 1.9f);
    if ((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) {
        variable_f2_2 = (f32) ((girar_posicion >> 16) / 8);
    } else if (((jugador->speed / 18.0f) * 216.0f) <= 25.0f) {
        variable_f2_2 = (f32) ((girar_posicion >> 16) / 12);
    } else {
        variable_f2_2 = ((f32) (girar_posicion >> 16)) / (8.0f + (jugador->actual_rapidez / 50.0f));
    }
    if (variable_f2_2 < 0.0f) {
        variable_f2_2 = -variable_f2_2;
    }
    if ((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB) {
        variable_f2_2 = variable_f2_2 * (sp44[((s16) ((jugador->speed / 18.0f) * 216.0f)) + 10] * 1.5f);
    } else if ((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) {
        variable_f2_2 = variable_f2_2 * sp44[(s16) ((jugador->speed / 18.0f) * 216.0f)];
    } else {
        variable_f2_2 = variable_f2_2 * (sp44[(s16) ((jugador->speed / 18.0f) * 216.0f)] * 1.5f);
    }
    jugador->posicion_giro = girar_posicion;
    if (jugador->desconocido_10C != 0) {
        funcion_8002BD58(jugador);
    }
    jugador->efectos &= ~EFECTO_FUERA_DERRAPE;
    if (((s32) jugador->ruedas[DERECHA_ATRAS].tipo_superficie) > 0xE) {
        variable_f12 = variable_f12;
    } else {
        variable_f12 += dato_800E3410[jugador->id_personaje][jugador->ruedas[DERECHA_ATRAS].tipo_superficie];
    }
    if (((s32) jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie) < 0xF) {
        variable_f12 += dato_800E3410[jugador->id_personaje][jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie];
    }
    if (((jugador->efectos & EFECTO_SALTO) != EFECTO_SALTO) && ((jugador->efectos & EFECTO_DERRAPANDO) != EFECTO_DERRAPANDO)) {
        if ((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB) {
            jugador->desconocido_078 = (jugador->posicion_giro >> 16) * 5 * variable_f2_2;
        } else {
            if ((jugador->efectos & EFECTO_FRENADO) != EFECTO_FRENADO) {
                if (((jugador->posicion_giro >> 16) >= 45) || ((jugador->posicion_giro >> 16) <= -45)) {
                    jugador->desconocido_078 = ((jugador->posicion_giro >> 16) * (variable_f2_2 + (variable_f2_2 * variable_f12))) *
                                      (0.15 + tabla_manejo_kart[jugador->id_personaje]);
                } else {
                    jugador->desconocido_078 = ((jugador->posicion_giro >> 16) * (variable_f2_2 + (variable_f2_2 * variable_f12))) *
                                      tabla_manejo_kart[jugador->id_personaje];
                }
            } else {
                if ((((jugador->speed / 18.0f) * 216.0f) >= 0.0f) && (((jugador->speed / 18.0f) * 216.0f) < 8.0f)) {
                    jugador->desconocido_078 = (jugador->posicion_giro >> 16) * (variable_f2_2 + (variable_f2_2 * variable_f12));
                }
                if ((((jugador->speed / 18.0f) * 216.0f) >= 8.0f) && (((jugador->speed / 18.0f) * 216.0f) < 65.0f)) {
                    jugador->desconocido_078 = (jugador->posicion_giro >> 16) * ((variable_f2_2 + 1.5) + (variable_f2_2 * variable_f12));
                }
                if (((jugador->speed / 18.0f) * 216.0f) >= 65.0f) {
                    jugador->desconocido_078 = (jugador->posicion_giro >> 16) * ((variable_f2_2 + 1.6) + (variable_f2_2 * variable_f12));
                }
            }
            jugador->contador_estado_derrape = 0;
            if (jugador->estado_derrape < 2) {
                jugador->estado_derrape = 0;
            }
        }
    } else if (((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) && ((jugador->efectos & EFECTO_SALTO) != EFECTO_SALTO)) {
        if ((((s16) jugador->desconocido_0C0) / GRADOS(1)) > 0) {
            variable_s1_2 = (((s32) (((jugador->posicion_giro >> 16) * 13) + (13 * 53))) / (2 * 53)) + 40;
            if ((jugador->posicion_giro >> 16) <= -40) {
                jugador->efectos |= EFECTO_FUERA_DERRAPE;
                if ((jugador->posicion_giro >> 16) <= -50) {
                    jugador->efectos |= EFECTO_FUERA_DERRAPE;
                }
            }
            actualizar_contador_estado_derrape(jugador, indice_jugador);
        } else {
            variable_s1_2 = (((s32) (((jugador->posicion_giro >> 16) * 13) + (13 * 53))) / (2 * 53)) - 53;
            if ((jugador->posicion_giro >> 16) >= 40) {
                jugador->efectos |= EFECTO_FUERA_DERRAPE;
                if ((jugador->posicion_giro >> 16) <= -50) {
                    jugador->efectos |= EFECTO_FUERA_DERRAPE;
                }
            }
            actualizar_contador_estado_derrape(jugador, indice_jugador);
        }
        if ((((jugador->speed / 18.0f) * 216.0f) >= 0.0f) && (((jugador->speed / 18.0f) * 216.0f) < 8.0f)) {
            jugador->desconocido_078 = (s16) ((s32) (variable_s1_2 * ((variable_f2_2 + 2.0f) + (variable_f2_2 * variable_f12))));
        }
        if ((((jugador->speed / 18.0f) * 216.0f) >= 8.0f) && (((jugador->speed / 18.0f) * 216.0f) < 65.0f)) {
            jugador->desconocido_078 = variable_s1_2 * ((variable_f2_2 + 3) + (variable_f2_2 * variable_f12));
        }
        if (((jugador->speed / 18.0f) * 216.0f) >= 65.0f) {
            jugador->desconocido_078 = variable_s1_2 * ((((f64) variable_f2_2) + 3.5) + (variable_f2_2 * variable_f12));
        }
        if ((jugador->efectos & EFECTO_FUERA_DERRAPE) == EFECTO_FUERA_DERRAPE) {
            jugador->desconocido_078 *= 0.9;
        } else {
            jugador->desconocido_078 *= 0.65;
        }
    } else {
        variable_s1_2 = jugador->posicion_giro >> 16;
        if (limitado_x == 0) {
            variable_s1_2 = 0;
        }
        if (((jugador->speed / 18.0f) * 216.0f) <= 5.0f) {
            jugador->desconocido_078 = (s16) ((s32) (((f32) variable_s1_2) * (variable_f2_2 + 6.0f)));
        } else {
            jugador->desconocido_078 = ((s16) variable_s1_2) * (variable_f2_2 + 1.5f);
        }
    }
    if (seleccion_modo == BATALLA) {
        jugador->desconocido_078 *= 1.7;
    }
}

void aplicar_giro_cpu(Jugador* jugador, s16 angulo_objetivo) {
    s32 sp304 = 0;
    SIN_USO f32 relleno[6];
    f32 variable_f0;
    s16 variable_v0;
    f32 giro_rapidez[168] = {
        0.0f, 0.1f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f,
        0.7f, 0.7f, 0.6f, 0.5f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f,
        0.4f, 0.4f, 0.5f, 0.5f, 0.5f, 0.5f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.7f,
        0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f,
        0.6f, 0.6f, 0.6f, 0.6f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.6f,
        0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f,
        0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f,
        0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f,
        0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f,
        0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f,
    };
    f32 giro_personaje[8] = {
        3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    };

    if (!((jugador->efectos & EFECTO_TROMPO_BANANA) || (jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) ||
          (jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) || (jugador->efectos & EFECTO_VUELCO_TERRENO) ||
          (jugador->efectos & EFECTO_GOLPE_RAYO) || (jugador->efectos & EFECTO_ERROR_EXPLOSION) ||
          (jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA) || (jugador->efectos & EFECTO_APLASTAMIENTO))) {
        if (!(((jugador->speed / 18.0f) * 216.0f) >= 110.0f)) {
            jugador->efectos &= ~EFECTO_FUERA_DERRAPE;
            jugador->contador_estado_derrape = 0;
            if (!(jugador->efectos & EFECTO_TROMPO_BANANA) && !(jugador->efectos & EFECTO_TROMPO_CONDUCIENDO)) {
                sp304 = (s32) jugador->posicion_giro >> 16;
                mover_s32_hacia(&sp304, (s32) angulo_objetivo, 0.35f);
                sp304 <<= 0x10;
                if ((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) {
                    variable_f0 = (sp304 >> 0x10) / 5;
                } else {
                    variable_f0 = (f32) (sp304 >> 0x10) / (8.0f + (jugador->actual_rapidez / 50.0f));
                }
                if (variable_f0 < 0.0f) {
                    variable_f0 = -variable_f0;
                }

                if ((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) {
                    variable_f0 = giro_rapidez[(s16) ((jugador->speed / 18.0f) * 216.0f)] * variable_f0;
                } else {
                    variable_f0 = giro_rapidez[(s16) ((jugador->speed / 18.0f) * 216.0f)] * giro_personaje[jugador->id_personaje] *
                             variable_f0;
                }
                jugador->posicion_giro = sp304;
                if (((jugador->efectos & EFECTO_SALTO) != EFECTO_SALTO) &&
                    ((jugador->efectos & EFECTO_DERRAPANDO) != EFECTO_DERRAPANDO)) {
                    if ((jugador->efectos & EFECTO_FRENADO) != EFECTO_FRENADO) {
                        jugador->desconocido_078 = (jugador->posicion_giro >> 16) * variable_f0;
                    } else {
                        jugador->desconocido_078 = (jugador->posicion_giro >> 16) * (variable_f0 + 1.5);
                    }
                } else if ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) {
                    if (((s16) jugador->desconocido_0C0 / GRADOS(1)) > 0) {
                        variable_v0 = jugador->posicion_giro >> 16;
                    } else {
                        variable_v0 = jugador->posicion_giro >> 16;
                    }
                    jugador->desconocido_078 = variable_v0 * (variable_f0 + 3.0);
                    jugador->desconocido_078 *= 0.8;
                } else {
                    variable_v0 = (s16) ((s32) jugador->posicion_giro >> 16);
                    if (angulo_objetivo == 0) {
                        variable_v0 = 0;
                    }
                    jugador->desconocido_078 = variable_v0 * variable_f0;
                }
                if ((((jugador->efectos & EFECTO_SALTO) != EFECTO_SALTO) && (jugador->desconocido_0C0 <= 60) && (jugador->desconocido_0C0 >= -60)) ||
                    (((jugador->speed / 18.0f) * 216.0f) <= 20.0f) ||
                    ((jugador->efectos & EFECTO_GOLPE_ENEMIGO) == EFECTO_GOLPE_ENEMIGO)) {
                    cancelar_efecto_derrape(jugador);
                }
            }
        }
    }
}

void funcion_80036C5C(Jugador* jugador) {
    if (((jugador->speed / 18.0f) * 216.0f) > 20.0f) {
        jugador->duracion_derrape = 0;
        jugador->efectos |= EFECTO_DERRAPANDO;
        jugador->graficos_kart |= BOING;
    }
}

void cancelar_efecto_derrape(Jugador* jugador) {
    s32 girar_nuevo_posicion;

    if (((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) && ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR)) {
        if ((jugador->desconocido_0C0 / GRADOS(1)) > 0) {
            girar_nuevo_posicion = ((((jugador->posicion_giro >> 16) * 13) + (13*53)) / (2*53)) + 40;
            jugador->posicion_giro = girar_nuevo_posicion << 16;
        }
        if ((jugador->desconocido_0C0 / GRADOS(1)) < 0) {
            girar_nuevo_posicion = ((((jugador->posicion_giro >> 16) * 13) + (13*53)) / (2*53)) - 53;
            jugador->posicion_giro = girar_nuevo_posicion << 16;
        }
        jugador->efectos &= ~EFECTO_DERRAPANDO;
    }
    if (((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) && ((jugador->type & HUMANO_JUGADOR) != HUMANO_JUGADOR)) {
        jugador->efectos &= ~EFECTO_DERRAPANDO;
    }
}

void funcion_80036DB4(Jugador* jugador, Vec3f parametro1, Vec3f parametro2) {
    s16 girar_delta_posicion;
    SIN_USO s16 relleno;
    f32 sp20;
    f32 variable_f18;
    s32 girar_posicion;

    if (((jugador->efectos & EFECTO_CARRERA_PERDIDO) == EFECTO_CARRERA_PERDIDO) ||
        ((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB)) {
        parametro1[0] = 0.0f;
        parametro1[1] = 0.0f;
        parametro1[2] = 0.0f;
        transformar_mat3_vec3f_mtxf(parametro1, jugador->matriz_orientacion);
    } else {
        if (((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) &&
            ((jugador->efectos & EFECTO_SALTO) != EFECTO_SALTO)) {
            variable_f18 = jugador->desconocido_208 + ((-(jugador->speed / 18.0f) * 216.0f) * 3.0f) + (-jugador->desconocido_20C * 10.0f);
            sp20 = jugador->desconocido_084 * 3.0f;
        } else if (!(jugador->efectos & BANANA_CERCA_EFECTO_TROMPO) && !(jugador->kart_props & CONDUCIENDO_CERCA_TROMPO)) {
            girar_delta_posicion = jugador->delta_posicion_giro;
            if (girar_delta_posicion > 0) {
                girar_delta_posicion *= -1;
            }
            girar_posicion = jugador->posicion_giro >> 16;
            if ((girar_posicion <= 20) && (girar_posicion >= -20)) {
                if (girar_delta_posicion < 20) {
                    variable_f18 = (jugador->desconocido_208 + ((-(jugador->speed / 18.0f) * 216.0f) / 3.0f)) +
                              (-jugador->actual_rapidez * 0.02) + (-jugador->desconocido_20C * 50.0f);
                } else {
                    variable_f18 = (jugador->desconocido_208 + ((-(jugador->speed / 18.0f) * 216.0f) / 3.0f)) +
                              ((girar_posicion * 0.01) + (-jugador->actual_rapidez * 0.05)) + (-jugador->desconocido_20C * 50.0f);
                }
            } else {
                variable_f18 = (jugador->desconocido_208 + ((-(jugador->speed / 18.0f) * 216.0f) / 3.0f)) +
                          ((girar_posicion * 0.1) + (-jugador->actual_rapidez * 0.15)) + (-jugador->desconocido_20C * 50.0f);
            }
            sp20 = jugador->desconocido_084;
        } else {
            variable_f18 = jugador->desconocido_208 + ((-(jugador->speed / 18.0f) * 216.0f) * 1.5) +
                      (((jugador->posicion_giro >> 16) * 0.1) + (-jugador->actual_rapidez * 0.05)) + (-jugador->desconocido_20C * 50.0f);
            sp20 = jugador->desconocido_084;
        }
        if ((jugador->efectos & EFECTO_ESTRELLA) == EFECTO_ESTRELLA) {
            if (((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) &&
                ((jugador->efectos & EFECTO_SALTO) != EFECTO_SALTO)) {
                variable_f18 = jugador->desconocido_208 + ((-(jugador->speed / 18.0f) * 216.0f) * 3.0f) + (-jugador->desconocido_20C * 10.0f);
                sp20 = jugador->desconocido_084 * 3.0f;
            } else {
                variable_f18 = jugador->desconocido_208 + ((-(jugador->speed / 18.0f) * 216.0f) / 3.0f);
                sp20 = jugador->desconocido_084;
            }
        }
        parametro1[0] = (jugador->desconocido_090 + variable_f18) * jugador->speed;
        parametro1[1] = 0.0f;
        parametro1[2] = jugador->speed * sp20;
        transformar_mat3_vec3f_mtxf(parametro1, jugador->matriz_orientacion);
    }
    parametro2[0] = parametro1[0];
    parametro2[1] = parametro1[1];
    parametro2[2] = parametro1[2];
}

void funcion_800371F4(Jugador* jugador, Vec3f parametro1, Vec3f parametro2) {
    s16 girar_delta_posicion;
    f32 sp20;
    f32 variable_f18;
    s32 girar_posicion;

    if (((jugador->efectos & EFECTO_CARRERA_PERDIDO) == EFECTO_CARRERA_PERDIDO) ||
        ((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB)) {
        parametro1[0] = 0.0f;
        parametro1[1] = 0.0f;
        parametro1[2] = 0.0f;
        transformar_mat3_vec3f_mtxf(parametro1, jugador->matriz_orientacion);
    } else {
        if (((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) &&
            ((jugador->efectos & EFECTO_SALTO) != EFECTO_SALTO)) {
            variable_f18 = jugador->desconocido_208 + ((-(jugador->speed / 18.0f) * 216.0f) * 3.0f) + (-jugador->desconocido_20C * 50.0f);
            sp20 = jugador->desconocido_084 * 3.0f;
        } else if (!(jugador->efectos & BANANA_CERCA_EFECTO_TROMPO) && !(jugador->kart_props & CONDUCIENDO_CERCA_TROMPO)) {
            girar_delta_posicion = jugador->delta_posicion_giro;
            if (girar_delta_posicion > 0) {
                girar_delta_posicion *= -1;
            }
            girar_posicion = (s32) jugador->posicion_giro >> 16;
            if ((girar_posicion <= 20) && (girar_posicion >= -20)) {
                if (girar_delta_posicion < 20) {
                    variable_f18 = (jugador->desconocido_208 + ((-(jugador->speed / 18.0f) * 216.0f) / 3.0f)) +
                              (-jugador->actual_rapidez * 0.02) + (-jugador->desconocido_20C * 50.0f);
                } else {
                    variable_f18 = ((jugador->desconocido_208 + ((-(jugador->speed / 18.0f) * 216.0f) / 3.0f)) -
                               ((girar_posicion * 0.01) + (jugador->actual_rapidez * 0.05))) +
                              (-jugador->desconocido_20C * 50.0f);
                }
            } else {
                variable_f18 = ((jugador->desconocido_208 + ((-(jugador->speed / 18.0f) * 216.0f) / 3.0f)) -
                           ((girar_posicion * 0.1) + (jugador->actual_rapidez * 0.15))) +
                          (-jugador->desconocido_20C * 50.0f);
            }
            sp20 = jugador->desconocido_084;
        } else {
            variable_f18 = ((jugador->desconocido_208 + ((f64) (-(jugador->speed / 18.0f) * 216.0f) * 1.5)) -
                       (((jugador->posicion_giro >> 0x10) * 0.1) + (jugador->actual_rapidez * 0.05))) +
                      (-jugador->desconocido_20C * 50.0f);
            sp20 = jugador->desconocido_084;
        }
        if ((jugador->efectos & EFECTO_ESTRELLA) == EFECTO_ESTRELLA) {
            if (((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) &&
                ((jugador->efectos & EFECTO_SALTO) != EFECTO_SALTO)) {
                variable_f18 = jugador->desconocido_208 + ((-(jugador->speed / 18.0f) * 216.0f) * 3.0f) + (-jugador->desconocido_20C * 50.0f);
                sp20 = jugador->desconocido_084 * 3.0f;
            } else {
                variable_f18 = jugador->desconocido_208 + ((-(jugador->speed / 18.0f) * 216.0f) / 3.0f);
                sp20 = jugador->desconocido_084;
            }
        }
        parametro1[0] = -(jugador->desconocido_090 + variable_f18) * jugador->speed;
        parametro1[1] = 0.0f;
        parametro1[2] = jugador->speed * sp20;
        transformar_mat3_vec3f_mtxf(parametro1, jugador->matriz_orientacion);
    }
    parametro2[0] = parametro1[0];
    parametro2[1] = parametro1[1];
    parametro2[2] = parametro1[2];
}

void funcion_80037614(Jugador* jugador, Vec3f parametro1, Vec3f parametro2) {
    f32 variable_f12;
    f32 variable_f2;

    if (((jugador->efectos & EFECTO_CARRERA_PERDIDO) == EFECTO_CARRERA_PERDIDO) ||
        ((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB)) {
        parametro1[0] = 0.0f;
        parametro1[1] = 0.0f;
        parametro1[2] = 0.0f;
        transformar_mat3_vec3f_mtxf(parametro1, jugador->matriz_orientacion);
    } else {
        if (((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) &&
            ((jugador->efectos & EFECTO_SALTO) != EFECTO_SALTO)) {
            variable_f2 = ((-(jugador->speed / 18.0f) * 216.0f) * 2) + -80.0f;
            variable_f12 = -80.0f;
        } else {
            variable_f2 = ((-(jugador->speed / 18.0f) * 216.0f) / 2) + -20.0f;
            variable_f12 = -40.0f;
        }
        parametro1[0] = (variable_f2 + 28.0f) * jugador->speed;
        parametro1[1] = 0.0f;
        parametro1[2] = variable_f12 * jugador->speed;
        transformar_mat3_vec3f_mtxf(parametro1, jugador->matriz_orientacion);
    }
    parametro2[0] = parametro1[0];
    parametro2[1] = parametro1[1];
    parametro2[2] = parametro1[2];
}

void funcion_8003777C(Jugador* jugador, Vec3f parametro1, Vec3f parametro2) {
    f32 variable_f12;
    f32 variable_f2;

    if (((jugador->efectos & EFECTO_CARRERA_PERDIDO) == EFECTO_CARRERA_PERDIDO) ||
        ((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB)) {
        parametro1[0] = 0.0f;
        parametro1[1] = 0.0f;
        parametro1[2] = 0.0f;
        transformar_mat3_vec3f_mtxf(parametro1, jugador->matriz_orientacion);
    } else {
        if (((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) &&
            ((jugador->efectos & EFECTO_SALTO) != EFECTO_SALTO)) {
            variable_f2 = ((-(jugador->speed / 18.0f) * 216.0f) * 2) + -80.0f;
            variable_f12 = -80.0f;
        } else {
            variable_f2 = ((-(jugador->speed / 18.0f) * 216.0f) / 2) + -20.0f;
            variable_f12 = -40.0f;
        }
        parametro1[0] = -(variable_f2 + 28.0f) * jugador->speed;
        parametro1[1] = 0.0f;
        parametro1[2] = variable_f12 * jugador->speed;
        transformar_mat3_vec3f_mtxf(parametro1, jugador->matriz_orientacion);
    }
    parametro2[0] = parametro1[0];
    parametro2[1] = parametro1[1];
    parametro2[2] = parametro1[2];
}

void funcion_800378E8(Jugador* jugador, Vec3f parametro1, Vec3f parametro2) {
    f32 variable_f12;
    f32 variable_f2;

    if ((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB) {
        parametro1[0] = 0.0f;
        parametro1[1] = 0.0f;
        parametro1[2] = 0.0f;
        transformar_mat3_vec3f_mtxf(parametro1, jugador->matriz_orientacion);
    } else {
        if ((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) {
            variable_f2 = jugador->desconocido_208 + (-(jugador->speed / 18.0f) * 216.0f * 5.0f) + (-jugador->desconocido_20C * 10.0f);
            variable_f12 = -100.0f;
        } else {
            variable_f2 = jugador->desconocido_208 + ((-(jugador->speed / 18.0f) * 216.0f) / 40.0f) + (-jugador->desconocido_20C * 50.0f);
            variable_f12 = jugador->desconocido_084;
        }
        parametro1[0] = (jugador->desconocido_090 + variable_f2) * jugador->speed;
        parametro1[1] = 0.0f;
        parametro1[2] = jugador->speed * variable_f12;
        transformar_mat3_vec3f_mtxf(parametro1, jugador->matriz_orientacion);
    }
    parametro2[0] = parametro1[0];
    parametro2[1] = parametro1[1];
    parametro2[2] = parametro1[2];
}

void funcion_80037A4C(Jugador* jugador, Vec3f parametro1, Vec3f parametro2) {
    f32 variable_f12;
    f32 variable_f2;

    if ((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB) {
        parametro1[0] = 0.0f;
        parametro1[1] = 0.0f;
        parametro1[2] = 0.0f;
        transformar_mat3_vec3f_mtxf(parametro1, jugador->matriz_orientacion);
    } else {
        if ((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) {
            variable_f2 = jugador->desconocido_208 + (-(jugador->speed / 18.0f) * 216.0f * 5.0f) + (-jugador->desconocido_20C * 50.0f);
            variable_f12 = -100.0f;
        } else {
            variable_f2 = jugador->desconocido_208 + ((-(jugador->speed / 18.0f) * 216.0f) / 40.0f) + (-jugador->desconocido_20C * 50.0f);
            variable_f12 = jugador->desconocido_084;
        }
        parametro1[0] = -(jugador->desconocido_090 + variable_f2) * jugador->speed;
        parametro1[1] = 0.0f;
        parametro1[2] = jugador->speed * variable_f12;
        transformar_mat3_vec3f_mtxf(parametro1, jugador->matriz_orientacion);
    }
    parametro2[0] = parametro1[0];
    parametro2[1] = parametro1[1];
    parametro2[2] = parametro1[2];
}

void funcion_80037BB4(Jugador* jugador, Vec3f parametro1) {
    SIN_USO s32 relleno[3];
    Vec3f sp20;

    if (jugador->desconocido_078 == 0) {
        parametro1[0] = 0.0f;
        parametro1[1] = 0.0f;
        parametro1[2] = 0.0f;
    } else {
        if (jugador->desconocido_078 < 0) {
            if (((jugador->efectos & EFECTO_FUERA_DERRAPE) != EFECTO_FUERA_DERRAPE) || (jugador->contador_estado_derrape >= 100)) {
                jugador->rotacion[1] += jugador->desconocido_078;
            }
            if (!(jugador->type & CPU_JUGADOR)) {
                if (seleccion_modo == BATALLA) {
                    funcion_800378E8(jugador, sp20, parametro1);
                } else {
                    funcion_80036DB4(jugador, sp20, parametro1);
                }
            } else {
                funcion_80037614(jugador, sp20, parametro1);
            }
        } else {
            if (((jugador->efectos & EFECTO_FUERA_DERRAPE) != EFECTO_FUERA_DERRAPE) || (jugador->contador_estado_derrape >= 100)) {
                jugador->rotacion[1] += jugador->desconocido_078;
            }
            if (!(jugador->type & CPU_JUGADOR)) {
                if (seleccion_modo == BATALLA) {
                    funcion_80037A4C(jugador, sp20, parametro1);
                } else {
                    funcion_800371F4(jugador, sp20, parametro1);
                }
            } else {
                funcion_8003777C(jugador, sp20, parametro1);
            }
        }
    }
}

void funcion_80037CFC(Jugador* jugador, struct Mando* mando, s8 indice_jugador) {
    if (((jugador->efectos & EFECTO_TROMPO_BANANA) != EFECTO_TROMPO_BANANA) &&
        ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) != EFECTO_TROMPO_CONDUCIENDO) &&
        ((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) != GOLPE_POR_CAPARAZON_VERDE_EFECTO) &&
        ((jugador->efectos & TEMPRANO_INICIO_TROMPO_EFECTO) != TEMPRANO_INICIO_TROMPO_EFECTO) &&
        ((jugador->efectos & EFECTO_ERROR_EXPLOSION) != EFECTO_ERROR_EXPLOSION) &&
        ((jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA) != GOLPE_POR_EFECTO_ESTRELLA) &&
        ((jugador->efectos & EFECTO_VUELCO_TERRENO) != EFECTO_VUELCO_TERRENO) &&
        ((jugador->efectos & EFECTO_GOLPE_RAYO) != EFECTO_GOLPE_RAYO)) {
        if (((jugador->efectos & EFECTO_APLASTAMIENTO) != EFECTO_APLASTAMIENTO) &&
            ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) && ((jugador->efectos & EFECTO_SALTO) != EFECTO_SALTO) &&
            ((jugador->efectos & EFECTO_DERRAPANDO) != EFECTO_DERRAPANDO) && (mando->boton_pulsado & R_TRIG)) {
            salto_kart(jugador);
            if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
                ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
                funcion_800C9060(indice_jugador, 0x19008000);
            }
        }
        if ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) {
            funcion_80033AE0(jugador, mando, indice_jugador);
        } else if (((jugador->efectos & EFECTO_SALTO) == EFECTO_SALTO) && (jugador->colision.distancia_superficie[2] <= 5.0f)) {
            funcion_80033AE0(jugador, mando, indice_jugador);
        }
        jugador->efectos &= ~EFECTO_FRENADO;
        if ((!(jugador->efectos & IMPULSO_RAMPA_ASFALTO_EFECTO)) && (!(jugador->efectos & IMPULSO_RAMPA_MADERA_EFECTO))) {
            if (((jugador->speed / 18.0f) * 216.0f) <= 12.0f) {
                if (mando->button & A_BUTTON) {
                    if (mando->button & B_BUTTON) {
                        jugador->efectos |= EFECTO_GIRO_AB;
                        if ((jugador->efectos & EFECTO_GIRO_AB) != EFECTO_GIRO_AB) {
                            jugador->actual_rapidez += 100.0f;
                        }
                    }
                }
            }
            if (((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB) &&
                (((mando->button & B_BUTTON) == 0) || (!(mando->button & A_BUTTON)))) {
                jugador->efectos &= ~EFECTO_GIRO_AB;
            }
        }
        if ((jugador->kart_props & ARRIBA_ATRAS) != ARRIBA_ATRAS) {
            if (mando->button & A_BUTTON) {
                alternativo_acelerar_jugador(jugador);
                detectar_triple_a_combo_a_pulsado(jugador);
            } else {
                if (seleccion_modo == BATALLA) {
                    alternativo_desacelerar_jugador(jugador, 2.0f);
                } else {
                    alternativo_desacelerar_jugador(jugador, 1.0f);
                }
                detectar_triple_a_combo_a_soltado(jugador);
            }
            if (mando->button & B_BUTTON) {
                funcion_800323E4(jugador);
                detectar_triple_b_combo_b_pulsado(jugador);
            } else {
                jugador->desconocido_20C = 0.0f;
                detectar_triple_b_combo_b_soltado(jugador);
            }
        }
        if ((!(jugador->efectos & IMPULSO_RAMPA_ASFALTO_EFECTO)) && (!(jugador->efectos & IMPULSO_RAMPA_MADERA_EFECTO))) {
            if (((obtener_limitado_palanca_y_con_zona_muerta(mando) < (-0x31)) && (((jugador->speed / 18.0f) * 216.0f) <= 5.0f)) &&
                (mando->button & B_BUTTON)) {
                jugador->actual_rapidez = 140.0f;
                jugador->kart_props |= ARRIBA_ATRAS;
                jugador->desconocido_08C = (jugador->actual_rapidez * jugador->actual_rapidez) / 25.0f;
                jugador->desconocido_20C = 0.0f;
            }
            if ((obtener_limitado_palanca_y_con_zona_muerta(mando) >= -0x1D) || (!(mando->button & B_BUTTON))) {
                if ((jugador->kart_props & ARRIBA_ATRAS) == ARRIBA_ATRAS) {
                    jugador->kart_props &= ~(ARRIBA_ATRAS);
                    jugador->actual_rapidez = 0.0f;
                }
            }
        }
    } else {
        if ((jugador->efectos & TEMPRANO_INICIO_TROMPO_EFECTO) == TEMPRANO_INICIO_TROMPO_EFECTO) {
            if (mando->button & A_BUTTON) {
                alternativo_acelerar_jugador(jugador);
            } else {
                alternativo_desacelerar_jugador(jugador, 5.0f);
            }
        }
        if (((((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
              ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO)) ||
             ((jugador->efectos & EFECTO_ERROR_EXPLOSION) == EFECTO_ERROR_EXPLOSION)) ||
            ((jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA) == GOLPE_POR_EFECTO_ESTRELLA)) {
            if (mando->button & A_BUTTON) {
                detectar_triple_a_combo_a_pulsado(jugador);
                global_acelerar_jugador(jugador, indice_jugador);
                return;
            }
            detectar_triple_a_combo_a_soltado(jugador);
            global_desacelerar_jugador(jugador, 5.0f, indice_jugador);
        }
    }
}

void manejar_pulsacion_a_para_jugador_durante_carrera(Jugador* jugador, struct Mando* mando, s8 indice_jugador) {
    if (((jugador->type & EXISTE_JUGADOR) == EXISTE_JUGADOR) && ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        ((jugador->type & CPU_JUGADOR) != CPU_JUGADOR)) {
        if ((jugador->type & SECUENCIA_INICIO_JUGADOR) != SECUENCIA_INICIO_JUGADOR) {
            if (((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == MANTENIDO_POR_LAKITU) ||
                ((jugador->lakitu_props & LAKITU_ESCENA) == LAKITU_ESCENA)) {
                if (mando->button & A_BUTTON) {
                    acelerar_jugador(jugador);
                } else {
                    desacelerar_jugador(jugador, 5.0f);
                }
            } else {
                funcion_80037CFC(jugador, mando, indice_jugador);
            }
            dato_80164A89 = 1;
        } else if (dato_8018D168 == 1) {
            if (dato_801656F0 == 1) {
                if (dato_801652E0[indice_jugador] == 0) {
                    dato_801652E0[indice_jugador] = contador_frame_carrera;
                }
            }
            if (mando->button & A_BUTTON) {
                empezar_secuencia_acelerar_jugador_durante(jugador);
            } else {
                empezar_secuencia_desacelerar_jugador_durante(jugador, 5.0f);
            }
        }
    }
}
