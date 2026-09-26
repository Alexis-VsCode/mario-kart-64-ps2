void cargar_camino_pista(s32 indice_camino) {

    PuntoCaminoPista* ptr;
    PuntoCaminoPista* dest_camino;
    PuntoCaminoPista* path;
    s32 variable_v0;
    s32 sp24;
    SIN_USO s32 relleno[2];
    s16 camino_invalido_b;
    s32 i;

    if ((s32) obtener_circuito_ai_maximo_separacion >= 0) {
        dest_camino = caminos_pista[indice_camino];
        camino_invalido_b = 1;
        if (id_circuito_actual != CEREMONIA_PREMIO_CIRCUITO) {
            variable_v0 = procesar_datos_camino(dest_camino, obtener_circuito_camino_tabla_2(indice_camino));
            cantidad_camino_por_indice_camino[indice_camino] = (u16) variable_v0;
        } else {
            path = obtener_circuito_camino_tabla(indice_camino);
            ptr = path;

            for (i = 0; i < 3000; i++, ptr++) {
                if ((u16) ptr->pos_x == 0x8000) {
                    sp24 = i - 1;
                    camino_invalido_b = 0;
                    break;
                }
            }

            if (!camino_invalido_b) {
                variable_v0 = funcion_80011014(dest_camino, path, sp24, indice_camino);
                cantidad_camino_por_indice_camino[indice_camino] = (u16) variable_v0;
            }
        }
    }
}

void calcular_limites_pista(s32 indice_camino) {
    f32 ancho_punto_camino;
    f32 x1;
    f32 y1;
    f32 z1;
    f32 x2;
    f32 y2;
    f32 z2;
    f32 x_dist;
    f32 z_dist;
    f32 neg_x_dist;
    f32 neg_z_dist;
    f32 xz_dist;
    s32 temporal_f16;
    s32 indice_punto_camino;
    PuntoCaminoPista* punto_camino;
    PuntoCaminoPista* punto_camino_siguiente;
    PuntoCaminoPista* variable_s1;
    PuntoCaminoPista* variable_s2;

    if (((s32) obtener_circuito_ai_maximo_separacion) >= 0) {
        ancho_punto_camino = obtener_circuito_ai_maximo_separacion;
        punto_camino = &caminos_pista[indice_camino][0];
        variable_s1 = &caminos_izquierda_pista[indice_camino][0];
        variable_s2 = &caminos_derecha_pista[indice_camino][0];
        for (indice_punto_camino = 0; indice_punto_camino < cantidad_camino_por_indice_camino[indice_camino];
             indice_punto_camino++, variable_s1++, variable_s2++) {
            x1 = punto_camino->pos_x;
            y1 = punto_camino->pos_y;
            z1 = punto_camino->pos_z;
            punto_camino++;
            punto_camino_siguiente = &caminos_pista[indice_camino][(indice_punto_camino + 1) % ((s32) cantidad_camino_por_indice_camino[indice_camino])];
            x2 = punto_camino_siguiente->pos_x;
            y2 = punto_camino_siguiente->pos_y;
            z2 = punto_camino_siguiente->pos_z;
            x_dist = x2 - x1;
            z_dist = z2 - z1;
            neg_x_dist = x1 - x2;
            neg_z_dist = z1 - z2;
            xz_dist = sqrtf((x_dist * x_dist) + (z_dist * z_dist));
            temporal_f16 = (f32) ((y1 + y2) * 0.5);

            variable_s1->pos_x = ((ancho_punto_camino * z_dist) / xz_dist) + x1;
            variable_s1->pos_y = temporal_f16;
            variable_s1->pos_z = ((ancho_punto_camino * neg_x_dist) / xz_dist) + z1;

            variable_s2->pos_x = ((ancho_punto_camino * neg_z_dist) / xz_dist) + x1;
            variable_s2->pos_y = temporal_f16;
            variable_s2->pos_z = ((ancho_punto_camino * x_dist) / xz_dist) + z1;
        }
    }
}

f32 calcular_curvatura_pista(s32 indice_camino, u16 indice_punto_camino) {
    f32 segundo_vector_x;
    f32 segundo_vector_z;
    SIN_USO f32 relleno;
    PuntoCaminoPista* puntos_camino_camino;
    f32 x1;
    f32 z1;
    f32 x2;
    f32 z2;
    f32 x3;
    f32 z3;
    f32 primer_vector_x;
    f32 primer_vector_z;
    s32 cantidad_punto_camino;
    PuntoCaminoPista* punto_camino_3;
    PuntoCaminoPista* punto_camino_2;
    PuntoCaminoPista* punto_camino_1;
    f32 segundo_longitud;
    f32 primer_longitud;

    if ((s32) obtener_circuito_ai_maximo_separacion < 0) {
        return 0.0f;
    }
    cantidad_punto_camino = cantidad_camino_por_indice_camino[indice_camino];
    puntos_camino_camino = caminos_pista[indice_camino];

    punto_camino_1 = &puntos_camino_camino[indice_punto_camino];
    punto_camino_2 = &puntos_camino_camino[(indice_punto_camino + 1) % cantidad_punto_camino];
    punto_camino_3 = &puntos_camino_camino[(indice_punto_camino + 2) % cantidad_punto_camino];

    x1 = punto_camino_1->pos_x;
    z1 = punto_camino_1->pos_z;
    x2 = punto_camino_2->pos_x;
    z2 = punto_camino_2->pos_z;
    x3 = punto_camino_3->pos_x;
    z3 = punto_camino_3->pos_z;

    primer_vector_x = (((x2 + x3) * 0.5) - x1);
    primer_vector_z = (((z2 + z3) * 0.5) - z1);

    punto_camino_1 = &puntos_camino_camino[(indice_punto_camino + 3) % cantidad_punto_camino];
    punto_camino_2 = &puntos_camino_camino[(indice_punto_camino + 4) % cantidad_punto_camino];
    punto_camino_3 = &puntos_camino_camino[(indice_punto_camino + 5) % cantidad_punto_camino];

    x1 = punto_camino_1->pos_x;
    z1 = punto_camino_1->pos_z;
    x2 = punto_camino_2->pos_x;
    z2 = punto_camino_2->pos_z;
    x3 = punto_camino_3->pos_x;
    z3 = punto_camino_3->pos_z;

    segundo_vector_x = (((x2 + x3) * 0.5) - x1);
    segundo_vector_z = (((z2 + z3) * 0.5) - z1);

    primer_longitud = sqrtf((primer_vector_z * primer_vector_z) + (primer_vector_x * primer_vector_x));
    segundo_longitud = sqrtf((segundo_vector_x * segundo_vector_x) + (segundo_vector_z * segundo_vector_z));
    return -((primer_vector_z * segundo_vector_x) - (primer_vector_x * segundo_vector_z)) / (segundo_longitud * primer_longitud);
}

void analizar_secciones_pista(s32 indice_camino) {
    f64 curvatura_seccion;
    SIN_USO s32 relleno;
    s32 k;
    s32 i;
    s32 j;
    s16* seccion_actual;
    s32 cantidad_punto_camino;
    s16* seccion_siguiente;

    if ((s32) obtener_circuito_ai_maximo_separacion >= 0) {
        cantidad_punto_camino = cantidad_camino_por_indice_camino[indice_camino];
        seccion_actual = tipos_seccion_pista[indice_camino];
        for (i = 0; i < cantidad_punto_camino; i++, seccion_actual++) {
            curvatura_seccion = calcular_curvatura_pista(indice_camino, i);
            *seccion_actual = RECTO;
            if (curvatura_seccion > 0.1) {
                *seccion_actual = CURVA_DERECHA;
            }
            if (curvatura_seccion < -0.1) {
                *seccion_actual = CURVA_IZQUIERDA;
            }
        }
        seccion_actual = tipos_seccion_pista[indice_camino];
        for (i = 0; i < cantidad_punto_camino; i++, seccion_actual++) {
            if (*seccion_actual == RECTO) {
                for (j = 1; j < cantidad_punto_camino; j++) {
                    seccion_siguiente = &tipos_seccion_pista[indice_camino][(i + j) % cantidad_punto_camino];
                    switch (*seccion_siguiente) {
                        case CURVA_INCLINADO_DERECHA:
                        case CURVA_DERECHA:
                            for (k = 0; k < j; k++) {
                                tipos_seccion_pista[indice_camino][(i + k) % cantidad_punto_camino] = CURVA_INCLINADO_DERECHA;
                            }
                            i += j;
                            seccion_actual += j;
                            j = cantidad_punto_camino;
                            break;
                        case CURVA_INCLINADO_IZQUIERDA:
                        case CURVA_IZQUIERDA:
                            for (k = 0; k < j; k++) {
                                tipos_seccion_pista[indice_camino][(i + k) % cantidad_punto_camino] = CURVA_INCLINADO_IZQUIERDA;
                            }
                            i += j;
                            seccion_actual += j;
                            j = cantidad_punto_camino;
                            break;
                    }
                }
            }
        }
    }
}

s16 calcular_camino_angulo(s32 indice_camino, s32 indice_punto_camino) {
    s16 devuelto;
    Vec3f sp30;
    Vec3f sp24;
    PuntoCaminoPista* temporal_v0;

    temporal_v0 = &caminos_pista[indice_camino][indice_punto_camino];
    sp30[0] = temporal_v0->pos_x;
    sp30[1] = temporal_v0->pos_y;
    sp30[2] = temporal_v0->pos_z;
    temporal_v0 = &caminos_pista[indice_camino][(indice_punto_camino + 1) % cantidad_camino_por_indice_camino[indice_camino]];
    sp24[0] = temporal_v0->pos_x;
    sp24[1] = temporal_v0->pos_y;
    sp24[2] = temporal_v0->pos_z;
    devuelto = obtener_angulo_xz_entre_puntos(sp30, sp24);
    return -devuelto;
}

void analizar_angulo_camino(s32 indice_camino) {
    s32 indice_punto_camino;
    u16* angulo;

    if ((s32) obtener_circuito_ai_maximo_separacion >= 0) {
        for (angulo = (u16*) &rotacion_esperado_camino[indice_camino][0], indice_punto_camino = 0;
             indice_punto_camino < cantidad_camino_por_indice_camino[indice_camino]; indice_punto_camino++, angulo++) {
            *angulo = calcular_camino_angulo(indice_camino, indice_punto_camino);
        }
    }
}

void analizar_camino_curvo(s32 indice_camino) {
    s16* cantidad_curva_pista;
    s16 cantidad_curva;
    s16 temporal_t0;
    s32 cantidad_punto_camino;
    s16* tipo_seccion_pista;
    s32 i, j;

    cantidad_punto_camino = cantidad_camino_por_indice_camino[indice_camino];
    tipo_seccion_pista = tipos_seccion_pista[indice_camino];
    cantidad_curva_pista = pista_consecutivo_curva_cantidades[indice_camino];

    for (i = 0; i < cantidad_punto_camino; i++) {
        cantidad_curva = 0;
        for (j = 0; j < cantidad_punto_camino; j++) {
            temporal_t0 = tipo_seccion_pista[(i + j) % cantidad_punto_camino];
            if ((temporal_t0 == CURVA_INCLINADO_IZQUIERDA) || (temporal_t0 == CURVA_INCLINADO_DERECHA)) {
                cantidad_curva += 1;
            } else {
                break;
            }
            if (id_circuito_actual == CEREMONIA_PREMIO_CIRCUITO) {
                break;
            }
        }
        *cantidad_curva_pista = cantidad_curva;
        cantidad_curva_pista++;
    }
}

f32 funcion_80010F40(f32 parametro0, f32 parametro1, f32 parametro2, SIN_USO s32 parametro3, SIN_USO s32 parametro4) {
    parametro1 = obtener_altura_superficie(parametro0, 2000.0f, parametro2);
    comprobar_colision_envolvente(&dato_80162E70, 1.0f, parametro0, parametro1, parametro2);
    return parametro1;
}

f32 funcion_80010FA0(f32 parametro0, f32 parametro1, f32 parametro2, SIN_USO s32 parametro3, SIN_USO s32 parametro4) {
    parametro1 = obtener_altura_superficie(parametro0, (f32) ((f64) parametro1 + 30.0), parametro2);
    comprobar_colision_envolvente(&dato_80162E70, 10.0f, parametro0, parametro1, parametro2);
    return parametro1;
}

s32 funcion_80011014(PuntoCaminoPista* dest_camino, PuntoCaminoPista* path, s32 puntos_camino_num, SIN_USO s32 indice_camino) {
    f32 temporal_f24_2;
    f32 temporal_f2_3;
    f32 variable_f20_2;
    f32 x1;
    f32 z1;
    f32 x2;
    f32 z2;
    f32 x3;
    f32 z3;
    f32 x1_2;
    f32 z1_3;
    f32 temporal_f20;
    f32 variable_f30;
    f32 temporal_f22;
    f32 temporal_f16;
    s32 i;

    f32 j;
    s32 variable_s0;
    f32 variable_f28;

    PuntoCaminoPista* punto1;
    PuntoCaminoPista* punto2;
    PuntoCaminoPista* punto3;
    f32 temporal_;
    SIN_USO PuntoCaminoPista* dest;
    variable_f30 = 0.0f;
    variable_s0 = 0;
    temporal_f20 = (f32) path[0].pos_x;
    temporal_f22 = (f32) path[0].pos_z;
    variable_f28 = funcion_80010F40(temporal_f20, 2000.0f, temporal_f22, id_circuito_actual, 0);

    for (i = 0; i < puntos_camino_num; i++) {
        punto1 = &path[i % puntos_camino_num];
        punto2 = &path[(i + 1) % puntos_camino_num];
        punto3 = &path[(s32) (i + 2) % puntos_camino_num];
        x1 = (f32) punto1->pos_x;
        z1 = (f32) punto1->pos_z;
        x2 = (f32) punto2->pos_x;
        z2 = (f32) punto2->pos_z;
        x3 = (f32) punto3->pos_x;
        z3 = (f32) punto3->pos_z;

        temporal_ = 0.05 / (sqrtf(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1))) +
                       (sqrtf(((x3 - x2) * (x3 - x2)) + ((z3 - z2) * (z3 - z2)))));

        for (j = 0.0f; j <= 1.0; j += temporal_) {

            temporal_f2_3 = (f32) ((1.0 - j) * 0.5 * (1.0 - j));
            z1_3 = (f32) (((1.0 - j) * j) + 0.5);
            temporal_f16 = (f32) (j * 0.5 * j);

            temporal_f24_2 = (temporal_f2_3 * x1) + (z1_3 * x2) + (temporal_f16 * x3);
            x1_2 = (temporal_f2_3 * z1) + (z1_3 * z2) + (temporal_f16 * z3);

            variable_f30 +=
                sqrtf(((temporal_f24_2 - temporal_f20) * (temporal_f24_2 - temporal_f20)) + ((x1_2 - temporal_f22) * (x1_2 - temporal_f22)));

            temporal_f20 = temporal_f24_2;
            temporal_f22 = x1_2;

            if ((variable_f30 > 20.0f) || ((i == 0) && (j == 0.0))) {
                if (es_modo_espejo) {
                    dest_camino->pos_x = (s16) -temporal_f24_2;
                    variable_f20_2 = funcion_80010FA0(-temporal_f24_2, variable_f28, x1_2, id_circuito_actual, variable_s0);
                } else {
                    dest_camino->pos_x = (s16) temporal_f24_2;
                    variable_f20_2 = funcion_80010FA0(temporal_f24_2, variable_f28, x1_2, id_circuito_actual, variable_s0);
                }

                dest_camino->pos_z = (s16) temporal_f22;
                dest_camino->id_seccion_pista = obtener_id_seccion_pista(dato_80162E70.indice_zx_malla);

                if (variable_f20_2 < -500.0) {
                    variable_f20_2 = variable_f28;
                } else {

                    switch (id_circuito_actual) {
                        case CIRCUITO_RAINBOW_ROAD:
                            if (variable_f20_2 < (variable_f28 - 15.0)) {
                                variable_f20_2 = (f32) variable_f28 - 15.0;
                            }
                            break;
                        case CIRCUITO_WARIO_STADIUM:
                            if ((variable_s0 >= 1140) && (variable_s0 <= 1152)) {
                                variable_f20_2 = variable_f28;
                            } else {
                                if (variable_f20_2 < (variable_f28 - 10.0)) {
                                    variable_f20_2 = (f32) (variable_f28 - 4.0);
                                }
                            }
                            break;
                        case CIRCUITO_DK_JUNGLE:
                            if ((variable_s0 > 204) && (variable_s0 < 220)) {
                                variable_f20_2 = variable_f28;
                            } else {
                                if (variable_f20_2 < (variable_f28 - 10.0)) {
                                    variable_f20_2 = (f32) (variable_f28 - 4.0);
                                }
                            }
                            break;
                        default:
                            if (variable_f20_2 < (variable_f28 - 10.0)) {
                                variable_f20_2 = (f32) variable_f28 - 10.0;
                            }
                            break;
                    }
                }
                variable_f28 = variable_f20_2;
                dest_camino->pos_y = (s16) (s32) variable_f20_2;
                variable_f30 = 0.0f;
                dest_camino++;
                variable_s0 += 1;
            }
        }
    }
    return variable_s0;
}

s32 procesar_datos_camino(PuntoCaminoPista* dest, PuntoCaminoPista* orig_) {
    s16 temporal_a0;
    s16 temporal_a2;
    s16 temporal_a3;
    s32 variable_v0;
    s32 variable_v1;
    u16 temporal_t0;

    variable_v1 = 0;
    for (variable_v0 = 0; variable_v0 < 0x7D0; variable_v0++) {
        temporal_a0 = orig_->pos_x;
        temporal_a2 = orig_->pos_y;
        temporal_a3 = orig_->pos_z;
        temporal_t0 = orig_->id_seccion_pista;
        orig_++;
        if (((temporal_a0 & 0xFFFF) == 0x8000) && ((temporal_a2 & 0xFFFF) == 0x8000) && ((temporal_a3 & 0xFFFF) == 0x8000)) {
            break;
        }
        if (es_modo_espejo != 0) {
            dest->pos_x = -temporal_a0;
        } else {
            dest->pos_x = temporal_a0;
        }
        variable_v1++;
        dest->pos_y = temporal_a2;
        dest->pos_z = temporal_a3;
        dest->id_seccion_pista = temporal_t0;
        dest++;
    }
    return variable_v1;
}

s32 generar_2d_camino(Camino2D* dest_camino, PuntoCaminoPista* orig_camino, s32 puntos_camino_num) {
    f32 temporal_f14_3;
    f32 temporal_f16_2;
    SIN_USO s32 relleno;

    f32 x1;
    f32 z1;
    f32 x2;
    f32 z2;
    f32 x3;
    f32 z3;

    SIN_USO s32 relleno2;
    f32 temporal_f24;

    f32 sp_a8;
    f32 temporal_f26;
    f32 sp_a0;

    f32 temporal_f2_3;

    PuntoCaminoPista* punto1;
    f32 j;
    PuntoCaminoPista* punto2;
    PuntoCaminoPista* punto3;
    s32 i;
    f32 temporal_f6 = 0.0f;
    s32 elemento_nb;
    f32 sp7_c;

#if defined(TARGET_PS2) && !defined(SMK64_PATH_CHECK)
    elemento_nb = busqueda_camino_vehiculo_ps2(dest_camino, orig_camino, puntos_camino_num, es_modo_espejo);
    if (elemento_nb >= 0) {
        return elemento_nb;
    }
#endif
    sp_a8 = orig_camino[0].pos_x;
    sp_a0 = orig_camino[0].pos_z;
    elemento_nb = 0;

    for (i = 0; i < puntos_camino_num; i++) {
        punto1 = &orig_camino[((i % puntos_camino_num))];
        punto2 = &orig_camino[(((i + 1) % puntos_camino_num))];
        punto3 = &orig_camino[(((i + 2) % puntos_camino_num))];
        x1 = punto1->pos_x;
        z1 = punto1->pos_z;
        x2 = punto2->pos_x;
        z2 = punto2->pos_z;
        x3 = punto3->pos_x;
        z3 = punto3->pos_z;

        sp7_c = 0.05 / (sqrtf(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1))) +
                       sqrtf(((x3 - x2) * (x3 - x2)) + ((z3 - z2) * (z3 - z2))));

        for (j = 0.0f; j <= 1.0; j += sp7_c) {
#ifdef TARGET_PS2
            union {
                f32 f;
                u32 u;
            } wj, w1, w2, w3;

            wj.f = j;
            if (pesos_camino_ps2(wj.u, &w1.u, &w2.u, &w3.u)) {
                temporal_f2_3 = w1.f;
                temporal_f14_3 = w2.f;
                temporal_f16_2 = w3.f;
            } else
#endif
            {
                temporal_f2_3 = (1.0 - j) * 0.5 * (1.0 - j);
                temporal_f14_3 = ((1.0 - j) * j) + 0.5;
                temporal_f16_2 = j * 0.5 * j;
            }

            temporal_f24 = (temporal_f2_3 * x1) + (temporal_f14_3 * x2) + (temporal_f16_2 * x3);
            temporal_f26 = (temporal_f2_3 * z1) + (temporal_f14_3 * z2) + (temporal_f16_2 * z3);
            temporal_f6 += sqrtf(((temporal_f24 - sp_a8) * (temporal_f24 - sp_a8)) + ((temporal_f26 - sp_a0) * (temporal_f26 - sp_a0)));
            sp_a8 = temporal_f24;
            sp_a0 = temporal_f26;
            if ((temporal_f6 > 20.0f) || ((i == 0) && (j == 0.0))) {
                if (es_modo_espejo) {
                    dest_camino->x = (s16) -sp_a8;
                } else {
                    dest_camino->x = (s16) sp_a8;
                }
                dest_camino->z = sp_a0;
                elemento_nb += 1;
                dest_camino++;
                temporal_f6 = 0.0f;
            }
        }
    }
#ifdef SMK64_PATH_CHECK
    comprobar_camino_vehiculo_ps2(dest_camino - elemento_nb, elemento_nb, orig_camino, puntos_camino_num, es_modo_espejo);
#endif
    return elemento_nb;
}
