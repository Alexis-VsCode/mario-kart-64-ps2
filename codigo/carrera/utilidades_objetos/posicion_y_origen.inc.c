// Posicion y origen

f32 funcion_8008933C(Jugador* jugador, s32 indice_objeto, f32 parametro2, f32 parametro3) {
    f32 variable_f2;
    f32 algo_;
    s32 id_jugador;
    Objeto* objeto;
    struct_d_8018CE10* temporal_v1;

    id_jugador = jugador - jugador_uno;
    temporal_v1 = &dato_8018CE10[id_jugador];
    variable_f2 = 0.0f;
    if (temporal_v1->desconocido_18[6] == 0) {
        objeto = &lista_objeto[indice_objeto];
        jugador->desconocido_046 |= TOCAR_BICHO;
        jugador->efectos |= EFECTO_GOLPE_ENEMIGO;
        temporal_v1->desconocido_18[6] = 4;
        algo_ = (jugador->pos[0] - objeto->pos[0]) * objeto->velocidad[0];
        if (algo_ >= 0.0f) {
            temporal_v1->desconocido_04[0] = (-jugador->velocidad[0] * parametro2) + (objeto->velocidad[0] * parametro3);
        } else {
            temporal_v1->desconocido_04[0] = -jugador->velocidad[0] * parametro2;
        }
        algo_ = (jugador->pos[2] - objeto->pos[2]) * objeto->velocidad[2];
        if (algo_ >= 0.0f) {
            temporal_v1->desconocido_04[2] = (-jugador->velocidad[2] * parametro2) + (objeto->velocidad[2] * parametro3);
        } else {
            temporal_v1->desconocido_04[2] = -jugador->velocidad[2] * parametro2;
        }
        variable_f2 = (temporal_v1->desconocido_04[0] * temporal_v1->desconocido_04[0]) + (temporal_v1->desconocido_04[2] * temporal_v1->desconocido_04[2]);
    }
    return variable_f2;
}

void funcion_80089474(s32 indice_objeto, s32 id_jugador, f32 parametro2, f32 parametro3, u32 sonido_bits) {
    SIN_USO s32 margen_pila;
    Jugador* jugador;

    jugador = &jugador_uno[id_jugador];
    if (es_obj_bandera_situacion_activo(indice_objeto, 0x04000000) != 0) {
        funcion_80072180();
    }
    if ((funcion_8008933C(jugador, indice_objeto, parametro2, parametro3) >= 4.0) && ((jugador->type & CPU_JUGADOR) != CPU_JUGADOR)) {
        funcion_800C9060(id_jugador, sonido_bits);
    }
}

void funcion_80089538(s32 indice_objeto, s32 id_jugador, f32 parametro2, f32 parametro3, u32 sonido_bits) {
    SIN_USO s32 margen_pila;
    Jugador* jugador;

    jugador = &jugador_uno[id_jugador];
    if ((funcion_8008933C(jugador, indice_objeto, parametro2, parametro3) >= 4.0) && ((jugador->type & CPU_JUGADOR) != CPU_JUGADOR)) {
        funcion_800C9060((u8) id_jugador, sonido_bits);
    }
}

s32 funcion_800895E4(s32 indice_objeto) {
    Jugador* jugador;
    s32 indice_jugador;
    s32 variable_s6;

    variable_s6 = 0;
    jugador = jugador_uno;
    if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000200) != 0) {
        for (indice_jugador = 0; indice_jugador < dato_8018D158; indice_jugador++, jugador++) {
            if ((lista_objeto[indice_objeto].state != 0) &&
                (tiene_horizontalmente_chocado_con_jugador(indice_objeto, jugador) != 0)) {
                if (es_obj_bandera_situacion_activo(indice_objeto, 0x04000000) != 0) {
                    funcion_80072180();
                }
                variable_s6 = 1;
            }
        }
    }
    return variable_s6;
}

void funcion_800896D4(s32 indice_objeto, f32 parametro1, f32 parametro2) {
    Jugador* jugador;
    s32 indice_jugador;

    jugador = jugador_uno;
    if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000200) != 0) {
        for (indice_jugador = 0; indice_jugador < dato_8018D158; indice_jugador++, jugador++) {
            if ((lista_objeto[indice_objeto].state != 0) && !(jugador->efectos & (EFECTO_ESTRELLA | BOO_EFECTO)) &&
                (tiene_horizontalmente_chocado_con_jugador(indice_objeto, jugador) != 0)) {
                funcion_8008933C(jugador, indice_objeto, parametro1, parametro2 * 1.1);
                if (es_obj_bandera_situacion_activo(indice_objeto, 0x04000000) != 0) {
                    funcion_80072180();
                }
            }
        }
    }
}

void funcion_80089820(s32 indice_objeto, f32 parametro1, f32 parametro2, u32 parametro3) {
    Jugador* jugador;
    s32 indice_jugador;

    jugador = jugador_uno;
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x02000000);
    if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000200) != 0) {
        for (indice_jugador = 0; indice_jugador < dato_8018D158; indice_jugador++, jugador++) {
            if ((lista_objeto[indice_objeto].state != 0) && !(jugador->efectos & BOO_EFECTO)) {
                if ((jugador->type & EXISTE_JUGADOR) && !(jugador->type & INVISIBLE_JUGADOR_O_BOMBA) &&
                    (tiene_horizontalmente_chocado_con_jugador(indice_objeto, jugador) != 0)) {
                    if (jugador->efectos & EFECTO_ESTRELLA) {
                        fijar_objeto_bandera_situacion_true(indice_objeto, 0x02000000);
                    } else {
                        if (es_obj_bandera_situacion_activo(indice_objeto, 0x04000000) != 0) {
                            funcion_80072180();
                        }
                        if ((funcion_8008933C(jugador, indice_objeto, parametro1, parametro2 * 1.1) >= 4.0) &&
                            ((jugador->type & CPU_JUGADOR) != CPU_JUGADOR)) {
                            funcion_800C9060(indice_jugador, parametro3);
                        }
                    }
                }
            }
        }
    }
}

void funcion_80089A04(s32 indice_objeto, f32 parametro1, f32 parametro2) {
    Jugador* jugador;
    s32 indice_jugador;

    jugador = jugador_uno;
    if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000200) != 0) {
        for (indice_jugador = 0; indice_jugador < dato_8018D158; indice_jugador++, jugador++) {
            if ((lista_objeto[indice_objeto].state != 0) && !(jugador->efectos & (BOO_EFECTO | EFECTO_ESTRELLA)) &&
                (tiene_chocado_con_jugador(indice_objeto, jugador) != 0)) {
                funcion_8008933C(jugador, indice_objeto, parametro1, parametro2 * 1.1);
                if (es_obj_bandera_situacion_activo(indice_objeto, 0x04000000) != 0) {
                    funcion_80072180();
                }
            }
        }
    }
}

s32 funcion_80089B50(s32 indice_objeto) {
    Jugador* jugador;
    s32 sp40;
    s32 indice_jugador;
    s32 probar;

    probar = 0;
    sp40 = 0;
    jugador = jugador_uno;
    if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000200) != 0) {
        for (indice_jugador = 0; indice_jugador < dato_8018D158; indice_jugador++, jugador++, probar++) {
            if ((lista_objeto[indice_objeto].state != 0) && !(jugador->efectos & (BOO_EFECTO | EFECTO_ERROR_EXPLOSION)) &&
                (jugador->type & EXISTE_JUGADOR) && !(jugador->type & INVISIBLE_JUGADOR_O_BOMBA) &&
                (tiene_horizontalmente_chocado_con_jugador(indice_objeto, jugador) != 0)) {
                if (!(jugador->efectos & EFECTO_ESTRELLA)) {
                    jugador->disparadores |= DISPARADOR_VUELCO_VERTICAL;
                    if (es_obj_bandera_situacion_activo(indice_objeto, 0x04000000) != 0) {
                        funcion_80072180();
                    }
                } else {
                    funcion_800C9060(probar, 0x19018010U);
                }
                sp40 = 1;
            }
        }
    }
    return sp40;
}

s32 funcion_80089CBC(s32 indice_objeto, f32 parametro1) {
    Jugador* jugador;
    s32 indice_jugador;
    s32 variable_s7;

    variable_s7 = 0;
    jugador = jugador_uno;
    if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000200) != 0) {
        for (indice_jugador = 0; indice_jugador < dato_8018D158; indice_jugador++, jugador++) {
            if ((lista_objeto[indice_objeto].state != 0) && !(jugador->efectos & (BOO_EFECTO | EFECTO_ERROR_EXPLOSION))) {
                if ((jugador->type & EXISTE_JUGADOR) && !(jugador->type & INVISIBLE_JUGADOR_O_BOMBA) &&
                    (tiene_chocado_con_jugador_y_dentro_altura(indice_objeto, jugador, parametro1) != 0)) {
                    if (!(jugador->efectos & EFECTO_ESTRELLA)) {
                        jugador->disparadores |= DISPARADOR_VUELCO_VERTICAL;
                        if (es_obj_bandera_situacion_activo(indice_objeto, 0x04000000) != 0) {
                            funcion_80072180();
                        }
                    }
                    variable_s7 = 1;
                }
            }
        }
    }
    return variable_s7;
}

s32 funcion_80089E18(s32 indice_objeto) {
    Jugador* jugador;
    s32 indice_jugador;
    s32 variable_s6;

    variable_s6 = 0;
    jugador = jugador_uno;
    if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000200) != 0) {
        for (indice_jugador = 0; indice_jugador < dato_8018D158; indice_jugador++, jugador++) {
            if ((lista_objeto[indice_objeto].state != 0) &&
                !(jugador->efectos & (BOO_EFECTO | EFECTO_TROMPO_BANANA | EFECTO_TROMPO_CONDUCIENDO)) &&
                (tiene_horizontalmente_chocado_con_jugador(indice_objeto, jugador) != 0)) {
                if (jugador->efectos & EFECTO_ESTRELLA) {
                    variable_s6 = 1;
                } else {
                    jugador->disparadores |= DISPARADOR_BANANA_GOLPE;
                }
            }
        }
    }
    return variable_s6;
}

s32 funcion_80089F24(s32 indice_objeto) {
    Jugador* jugador;
    s32 indice_jugador;
    s32 variable_s7;

    variable_s7 = 0;
    jugador = jugador_uno;
    if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000200) != 0) {
        for (indice_jugador = 0; indice_jugador < dato_8018D158; indice_jugador++, jugador++) {
            if ((lista_objeto[indice_objeto].state != 0) &&
                !(jugador->efectos & (BOO_EFECTO | EFECTO_ESTRELLA | EFECTO_TROMPO_BANANA | EFECTO_TROMPO_CONDUCIENDO))) {
                if ((jugador->type & EXISTE_JUGADOR) && !(jugador->type & INVISIBLE_JUGADOR_O_BOMBA) &&
                    (tiene_horizontalmente_chocado_con_jugador(indice_objeto, jugador) != 0)) {
                    variable_s7 = 1;
                    if (es_obj_bandera_situacion_activo(indice_objeto, 0x04000000) != 0) {
                        funcion_80072180();
                    }
                    jugador->disparadores |= DISPARADOR_TROMPO;
                }
            }
        }
    }
    return variable_s7;
}

s32 funcion_8008A060(s32 indice_objeto, Camara* camara, u16 parametro2) {
    u16 temporal_t3;
    s32 variable_v1;

    variable_v1 = 0;
    temporal_t3 = (((u16) camara->rot[1] - lista_objeto[indice_objeto].angulo_sentido[1]) + (parametro2 >> 1));

    if ((temporal_t3 >= 0) && (parametro2 >= temporal_t3)) {
        variable_v1 = 1;
    }
    return variable_v1;
}

s32 funcion_8008A0B4(s32 indice_objeto, Jugador* jugador, Camara* camara, u16 parametro3) {
    u16 temporal_t3;
    f32 dif_x;
    f32 dif_z;
    s32 variable_t0;

    variable_t0 = 0;
    dif_x = lista_objeto[indice_objeto].pos[0] - jugador->pos[0];
    dif_z = lista_objeto[indice_objeto].pos[2] - jugador->pos[2];
    temporal_t3 = ((u16) camara->rot[1] - atan2s(dif_x, dif_z)) + (parametro3 >> 1);
    if ((temporal_t3 >= 0) && (parametro3 >= temporal_t3)) {
        variable_t0 = 1;
    }
    return variable_t0;
}

bool es_visible_objeto_en_camara(s32 indice_objeto, Camara* camara, u16 angulo) {
    u16 temporal_t2;
    s32 variable_t0;

    variable_t0 = false;
    temporal_t2 = (obtener_angulo_entre_xy(camara->pos[0], lista_objeto[indice_objeto].pos[0], camara->pos[2],
                                    lista_objeto[indice_objeto].pos[2]) +
               ((s32) angulo / 2)) -
              camara->rot[1];
    if ((temporal_t2 >= 0) && (angulo >= temporal_t2)) {
        variable_t0 = true;
    }
    return variable_t0;
}

void funcion_8008A1D0(s32 indice_objeto, s32 id_camara, s32 parametro2, s32 parametro3) {
    u32 temporal_v0;
    u16 variable_a2;
    Camara* camara;

    camara = &camara1[id_camara];
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00100000 | VISIBLE);
    temporal_v0 = obtener_distancia_horizontal_a_camara(indice_objeto, camara);
    if (temporal_v0 < 0x2711U) {
        variable_a2 = 0x5555;
    } else if (temporal_v0 < 0x9C41U) {
        variable_a2 = 0x4000;
    } else {
        variable_a2 = 0x2AAB;
    }
    if ((es_visible_objeto_en_camara(indice_objeto, camara, variable_a2) != 0) && ((u32) (parametro3 * parametro3) >= temporal_v0)) {
        fijar_objeto_bandera_situacion_true(indice_objeto, VISIBLE);
        if (temporal_v0 >= (u32) (parametro2 * parametro2)) {
            fijar_objeto_bandera_situacion_true(indice_objeto, 0x00100000);
        }
    }
}

SIN_USO void funcion_8008A2CC(s32 indice_objeto, s32 id_camara, u16 parametro2) {
    Camara* camara;
    u32 inicializar_no;
    u16 variable_a2;

    camara = &camara1[id_camara];
    fijar_objeto_bandera_situacion_false(indice_objeto, VISIBLE);
    if (inicializar_no < 0x2711U) {
        variable_a2 = 0x5555;
    } else if (inicializar_no < 0x9C41U) {
        variable_a2 = 0x4000;
    } else {
        variable_a2 = parametro2;
    }
    if (es_visible_objeto_en_camara(indice_objeto, camara, variable_a2) != 0) {
        fijar_objeto_bandera_situacion_true(indice_objeto, VISIBLE);
    }
}

s32 funcion_8008A364(s32 indice_objeto, s32 id_camara, u16 parametro2, s32 parametro3) {
    Camara* camara;
    u32 dist;
    u16 variable_a2;

    camara = &camara1[id_camara];
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00020000 | VISIBLE);
    dist = obtener_distancia_horizontal_a_camara(indice_objeto, camara);
    if (dist < (parametro3 * parametro3)) {
        fijar_objeto_bandera_situacion_true(indice_objeto, 0x00020000);
        if (dist < 0x2711U) {
            variable_a2 = 0x5555;
        } else if (dist < 0x9C41U) {
            variable_a2 = 0x4000;
        } else {
            variable_a2 = parametro2;
        }
        if (es_visible_objeto_en_camara(indice_objeto, camara, variable_a2) != 0) {
            fijar_objeto_bandera_situacion_true(indice_objeto, VISIBLE);
        }
    }
    return dist;
}

void funcion_8008A454(s32 indice_objeto, s32 id_camara, s32 parametro2) {
    if (obtener_distancia_horizontal_a_camara(indice_objeto, &camara1[id_camara]) < (u32) (parametro2 * parametro2)) {
        fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000020);
    } else {
        fijar_objeto_bandera_situacion_false(indice_objeto, 0x00000020);
    }
}

void funcion_8008A4CC(s32 indice_objeto) {
    s32 indice_bucle;
    Camara* camara;

    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00070000);
    for (indice_bucle = 0, camara = camara1; indice_bucle < seleccion_cantidad_jugador_1; indice_bucle++, camara++) {
        if (lista_objeto[indice_objeto].state != 0) {
            if ((dato_8018CF68[indice_bucle] >= (lista_objeto[indice_objeto].desconocido_0DF - 1)) &&
                ((lista_objeto[indice_objeto].desconocido_0DF + 1) >= dato_8018CF68[indice_bucle])) {
                fijar_objeto_bandera_situacion_true(indice_objeto, 0x00010000);
                if (dato_8018CF68[indice_bucle] == lista_objeto[indice_objeto].desconocido_0DF) {
                    fijar_objeto_bandera_situacion_true(indice_objeto, 0x00020000);
                }
                if (es_visible_objeto_en_camara(indice_objeto, camara, 0x2AABU) != 0) {
                    fijar_objeto_bandera_situacion_true(indice_objeto, VISIBLE);
                }
            }
        }
    }
}

SIN_USO void funcion_8008A610(s32 indice_objeto) {
    s32 indice_bucle;
    Camara* camara;

    fijar_objeto_bandera_situacion_false(indice_objeto, VISIBLE);
    for (camara = camara1, indice_bucle = 0; indice_bucle < seleccion_cantidad_jugador_1; indice_bucle++, camara++) {
        if ((lista_objeto[indice_objeto].state != 0) && (es_visible_objeto_en_camara(indice_objeto, camara, 0x2AABU) != 0)) {
            fijar_objeto_bandera_situacion_true(indice_objeto, VISIBLE);
        }
    }
}

void funcion_8008A6DC(s32 indice_objeto, f32 parametro1) {
    u16 variable_a2;
    s32 indice_bucle;
    Camara* camara;

    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00060000);
    for (camara = camara1, indice_bucle = 0; indice_bucle < seleccion_cantidad_jugador_1; indice_bucle++, camara++) {
        if ((lista_objeto[indice_objeto].state != 0) &&
            (es_dentro_distancia_horizontal_a_camara(indice_objeto, camara, parametro1) != 0)) {
            fijar_objeto_bandera_situacion_true(indice_objeto, 0x00020000);
            if (parametro1 <= 500.0) {
                variable_a2 = 0x4000;
            } else {
                variable_a2 = 0x2AAB;
            }
            if (es_visible_objeto_en_camara(indice_objeto, camara, variable_a2) != 0) {
                fijar_objeto_bandera_situacion_true(indice_objeto, VISIBLE);
            }
        }
    }
}

SIN_USO void funcion_8008A810(s32 parametro0) {
    funcion_8008A6DC(parametro0, 500.0f);
}

SIN_USO void funcion_8008A830(s32 parametro0) {
    funcion_8008A6DC(parametro0, 1000.0f);
}

SIN_USO void funcion_8008A850(s32 parametro0) {
    funcion_8008A6DC(parametro0, 2000.0f);
}

SIN_USO s32 funcion_8008A870(Jugador* jugador) {
    return obtener_id_seccion_pista(jugador->colision.indice_zx_malla);
}

s32 funcion_8008A890(Camara* camara) {
    return obtener_id_seccion_pista(camara->colision.indice_zx_malla);
}

s32 funcion_8008A8B0(s16 parametro0, s16 parametro1) {
    s32 variable_v1;
    s16* variable_v0;
    s32 i;
    variable_v1 = 0;
    for (i = 0; i < seleccion_cantidad_jugador_1; i++) {
        variable_v0 = &dato_8018CF68[i];
        if ((*variable_v0 >= parametro0) && (parametro1 >= *variable_v0)) {
            variable_v1 = 1;
        }
    }
    return variable_v1;
}

void funcion_8008A920(s32 indice_objeto) {
    PuntoControlSpline* temporal_v0;

    temporal_v0 = lista_objeto[indice_objeto].puntos_control;
    lista_objeto[indice_objeto].velocidad[0] = (f32) (temporal_v0[1].pos[0] - temporal_v0[0].pos[0]) / (f32) temporal_v0[0].velocidad;
    lista_objeto[indice_objeto].velocidad[1] = (f32) (temporal_v0[1].pos[1] - temporal_v0[0].pos[1]) / (f32) temporal_v0[0].velocidad;
    lista_objeto[indice_objeto].velocidad[2] = (f32) (temporal_v0[1].pos[2] - temporal_v0[0].pos[2]) / (f32) temporal_v0[0].velocidad;
}

void funcion_8008A9B8(s32 indice_objeto) {
    SIN_USO s32 temporal_t9;
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->puntos_control++;
    objeto->desconocido_09A = (s16) (10000 / (s16) (objeto->puntos_control[0].velocidad));
    objeto->temporizador_animacion = 0;
    funcion_8008A920(indice_objeto);
}

void funcion_8008AA3C(s32 indice_objeto) {
    Objeto* objeto;
    objeto = &lista_objeto[indice_objeto];
    objeto->puntos_control = objeto->spline->puntos_control;
    objeto->desconocido_084[9] = 0;
    objeto->temporizador_animacion = 0;
    objeto->desconocido_084[8] = *((s16*) objeto->puntos_control - 1);
    objeto->offset[0] = objeto->puntos_control[0].pos[0];
    objeto->offset[1] = objeto->puntos_control[0].pos[1];
    objeto->offset[2] = objeto->puntos_control[0].pos[2];
    objeto->desconocido_09A = (s16) (10000 / objeto->puntos_control[0].velocidad);
    funcion_8008A920(indice_objeto);
    funcion_80086FD4(indice_objeto);
}

void funcion_8008AB10(s32 indice_objeto) {
    SIN_USO s16 temporal_t3;
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->offset[0] += objeto->velocidad[0];
    objeto->offset[1] += objeto->velocidad[1];
    objeto->offset[2] += objeto->velocidad[2];
    objeto->temporizador_animacion += (u16) objeto->desconocido_09A;
    if (objeto->temporizador_animacion >= 0x2710) {
        objeto->desconocido_084[9] = (u16) objeto->desconocido_084[9] + 1;
        if (((u16) objeto->desconocido_084[9] + 1) == (u16) objeto->desconocido_084[8]) {
            objeto->desconocido_0AE += 1;
        } else {
            funcion_8008A9B8(indice_objeto);
        }
    }
}

SIN_USO void funcion_8008ABC0(s32 parametro0) {
    switch (lista_objeto[parametro0].desconocido_0AE) {
        case 1:
            funcion_8008AA3C(parametro0);
            break;
        case 2:
            funcion_8008AB10(parametro0);
            break;
        case 3:
            funcion_80086F60(parametro0);
        case 0:
            break;
    }
}

SIN_USO void funcion_8008AC40(s32 parametro0) {
    switch (lista_objeto[parametro0].desconocido_0AE) {
        case 1:
            funcion_8008AA3C(parametro0);
            break;
        case 2:
            funcion_8008AB10(parametro0);
            break;
        case 3:
            funcion_8008701C(parametro0, 1);
        case 0:
            break;
    }
}

SIN_USO void funcion_8008ACC0(void) {
}

SIN_USO void funcion_8008ACC8(void) {
}

SIN_USO void funcion_8008ACD0(void) {
}

SIN_USO void funcion_8008ACD8(void) {
}

void funcion_8008ACE0(f32 parametro0[], f32 parametro1) {
    parametro0[0] = (f32) ((f64) ((f32) (1.0 - parametro1) * (f32) (1.0 - parametro1) * (f32) (1.0 - parametro1)) / 6.0);
    parametro0[1] = (f32) ((((f64) (parametro1 * parametro1 * parametro1) * 0.5) - parametro1 * parametro1) + 0.6666666666666666);
    parametro0[2] = (f32) (((f64) (parametro1 * parametro1 * parametro1) * -0.5) + (0.5 * (parametro1 * parametro1)) + (0.5 * parametro1) + 0.16666666666666666);
    parametro0[3] = (f32) ((f64) (parametro1 * parametro1 * parametro1) / 6.0);
}

SIN_USO void funcion_8008ADC0(void) {
}

SIN_USO void funcion_8008ADC8(void) {
}

void funcion_8008ADD0(f32 parametro0[], f32 parametro1) {
    parametro0[0] = (f32) (1.0 - parametro1) * -0.5 * (f32) (1.0 - parametro1);
    parametro0[1] = parametro1 * parametro1 * 1.5 - 2.0 * parametro1;
    parametro0[2] = (parametro1 * parametro1 * 3.0 - 2.0 * parametro1 - (f32) 1.0) * -0.5;
    parametro0[3] = parametro1 * parametro1 * 0.5;
}

SIN_USO void funcion_8008AE8C(void) {
}

SIN_USO void funcion_8008AE94(void) {
}

void funcion_8008AE9C(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->velocidad[0] = (dato_80183DC8[0] * dato_80165760[0]) + (dato_80183DC8[1] * dato_80165760[1]) +
                          (dato_80183DC8[2] * dato_80165760[2]) + (dato_80183DC8[3] * dato_80165760[3]);
    objeto->velocidad[1] = (dato_80183DC8[0] * dato_80165770[0]) + (dato_80183DC8[1] * dato_80165770[1]) +
                          (dato_80183DC8[2] * dato_80165770[2]) + (dato_80183DC8[3] * dato_80165770[3]);
    objeto->velocidad[2] = (dato_80183DC8[0] * dato_80165780[0]) + (dato_80183DC8[1] * dato_80165780[1]) +
                          (dato_80183DC8[2] * dato_80165780[2]) + (dato_80183DC8[3] * dato_80165780[3]);
}

void funcion_8008AFE0(s32 indice_objeto, f32 parametro1) {
    funcion_8008ADD0(dato_80183DC8, parametro1);
    funcion_8008AE9C(indice_objeto);
}

SIN_USO void funcion_8008B018(void) {
}

SIN_USO void funcion_8008B020(void) {
}

SIN_USO void funcion_8008B028(void) {
}

SIN_USO void funcion_8008B030(void) {
}

void funcion_8008B038(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->offset[0] = (dato_80183DA8[0] * dato_80165760[0]) + (dato_80183DA8[1] * dato_80165760[1]) +
                        (dato_80183DA8[2] * dato_80165760[2]) + (dato_80183DA8[3] * dato_80165760[3]);
    objeto->offset[1] = (dato_80183DA8[0] * dato_80165770[0]) + (dato_80183DA8[1] * dato_80165770[1]) +
                        (dato_80183DA8[2] * dato_80165770[2]) + (dato_80183DA8[3] * dato_80165770[3]);
    objeto->offset[2] = (dato_80183DA8[0] * dato_80165780[0]) + (dato_80183DA8[1] * dato_80165780[1]) +
                        (dato_80183DA8[2] * dato_80165780[2]) + (dato_80183DA8[3] * dato_80165780[3]);
}

void funcion_8008B17C(s32 indice_objeto, f32 parametro1) {
    funcion_8008ACE0(dato_80183DA8, parametro1);
    funcion_8008B038(indice_objeto);
}

SIN_USO void funcion_8008B1B4(void) {
}

SIN_USO void funcion_8008B1BC(void) {
}

SIN_USO void funcion_8008B1C4(void) {
}

SIN_USO void funcion_8008B1CC(void) {
}

void funcion_8008B1D4(s32 indice_objeto) {
    s32 algun_indice;
    PuntoControlSpline* probar;

    probar = lista_objeto[indice_objeto].puntos_control;
    for (algun_indice = 0; algun_indice < 4; algun_indice++) {
        dato_80165760[algun_indice] = probar->pos[0];
        dato_80165770[algun_indice] = probar->pos[1];
        dato_80165780[algun_indice] = probar->pos[2];
        probar++;
    }
}

void funcion_8008B284(s32 indice_objeto) {
    s32 algun_indice;
    s32 sp0;
    s32 temporal_a1;
    s32 temporal_a2;
    PuntoControlSpline* probar;

    probar = lista_objeto[indice_objeto].puntos_control;
    temporal_a1 = lista_objeto[indice_objeto].desconocido_084[9];
    temporal_a2 = (u16) lista_objeto[indice_objeto].desconocido_084[8];
    if ((temporal_a2 - 4) >= temporal_a1) {
        sp0 = 10000;
    } else if ((temporal_a1 + 3) == temporal_a2) {
        sp0 = 2;
    } else if ((temporal_a1 + 2) == temporal_a2) {
        sp0 = 1;
    } else if ((temporal_a1 + 1) == temporal_a2) {
        sp0 = 0;
    }
    for (algun_indice = 0; algun_indice < 4; algun_indice++) {
        dato_80165760[algun_indice] = probar->pos[0];
        dato_80165770[algun_indice] = probar->pos[1];
        dato_80165780[algun_indice] = probar->pos[2];
        if (sp0 == algun_indice) {
            probar = lista_objeto[indice_objeto].spline->puntos_control;
        } else {
            probar++;
        }
    }
}

void funcion_8008B3E4(s32 indice_objeto) {
    Objeto* objeto;
    SIN_USO DatosSpline* spline;

    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 8) != 0) {
        objeto = &lista_objeto[indice_objeto];
        objeto->desconocido_084[9] = 0;
        objeto->temporizador_animacion = 0;
        objeto->puntos_control = objeto->spline->puntos_control;
        objeto->desconocido_084[8] = *(((s16*) objeto->puntos_control) - 1);

        fijar_objeto_bandera_situacion_true(indice_objeto, 8);
    }
}

void funcion_8008B44C(s32 indice_objeto) {
    lista_objeto[indice_objeto].temporizador_animacion = 0;
    lista_objeto[indice_objeto].puntos_control++;
}

void funcion_8008B478(s32 indice_objeto, s32 parametro1) {
    f32 sp34;
    f32 temporal_;
    SIN_USO f32 temporal2;
    f32 variable_f6;

    funcion_8008B3E4(indice_objeto);
    if (parametro1 != 0) {
        funcion_8008B284(indice_objeto);
    } else {
        funcion_8008B1D4(indice_objeto);
    }

    sp34 = ((f32) lista_objeto[indice_objeto].temporizador_animacion / 10000.0);
    funcion_8008B17C(indice_objeto, sp34);
    if (es_obj_bandera_situacion_activo(indice_objeto, 0x800) != 0) {
        funcion_8008AFE0(indice_objeto, sp34);
    }

    variable_f6 = lista_objeto[indice_objeto].puntos_control[0].velocidad;
    temporal_ = lista_objeto[indice_objeto].puntos_control[1].velocidad;

    lista_objeto[indice_objeto].desconocido_09A = 10000.0 / (((temporal_ - variable_f6) * sp34) + variable_f6);
    lista_objeto[indice_objeto].temporizador_animacion += lista_objeto[indice_objeto].desconocido_09A;
}

void funcion_8008B620(s32 indice_objeto) {
    SIN_USO s16 temporal_t0;
    Objeto* objeto;

    funcion_8008B478(indice_objeto, 0);
    objeto = &lista_objeto[indice_objeto];
    if (objeto->temporizador_animacion >= 0x2710) {
        objeto->desconocido_084[9] = (u16) objeto->desconocido_084[9] + 1;
        if (((u16) objeto->desconocido_084[9] + 3) == (u16) objeto->desconocido_084[8]) {
            objeto->desconocido_0AE += 1;
        } else {
            funcion_8008B44C(indice_objeto);
        }
    }
}

void funcion_8008B6A4(s32 indice_objeto) {
    Objeto* objeto;

    funcion_8008B478(indice_objeto, 1);
    objeto = &lista_objeto[indice_objeto];
    if (objeto->temporizador_animacion >= 0x2710) {
        objeto->desconocido_084[9] = (u16) objeto->desconocido_084[9] + 1;
        if ((u16) objeto->desconocido_084[9] == (u16) objeto->desconocido_084[8]) {
            fijar_objeto_bandera_situacion_false(indice_objeto, 8);
        } else {
            funcion_8008B44C(indice_objeto);
        }
    }
}

void funcion_8008B724(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 0:
            break;
        case 1:
            funcion_8008B620(indice_objeto);
            break;
        case 2:
            funcion_80086F60(indice_objeto);
            break;
    }
}

void funcion_8008B78C(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 0:
            break;
        case 1:
            funcion_8008B6A4(indice_objeto);
            break;
    }
}

void fijar_pos_origen_obj(s32 indice_objeto, f32 parametro1, f32 parametro2, f32 parametro3) {
    lista_objeto[indice_objeto].pos_origen[0] = parametro1;
    lista_objeto[indice_objeto].pos_origen[1] = parametro2;
    lista_objeto[indice_objeto].pos_origen[2] = parametro3;
}

void fijar_desplazamiento_origen_obj(s32 indice_objeto, f32 parametro1, f32 parametro2, f32 parametro3) {
    lista_objeto[indice_objeto].offset[0] = parametro1;
    lista_objeto[indice_objeto].offset[1] = parametro2;
    lista_objeto[indice_objeto].offset[2] = parametro3;
}

void funcion_8008B844(s32 indice_objeto) {
    f32 temporal_f0 = lista_objeto[indice_objeto].pos_origen[0];

    lista_objeto[indice_objeto].pos[0] = lista_objeto[indice_objeto].offset[0] + temporal_f0;
    lista_objeto[indice_objeto].pos[1] = lista_objeto[indice_objeto].offset[1] + temporal_f0;
    lista_objeto[indice_objeto].pos[2] = lista_objeto[indice_objeto].offset[2] + temporal_f0;
}

void fijar_angulo_sentido_obj(s32 indice_objeto, u16 parametro1, u16 parametro2, u16 parametro3) {
    lista_objeto[indice_objeto].angulo_sentido[0] = parametro1;
    lista_objeto[indice_objeto].angulo_sentido[1] = parametro2;
    lista_objeto[indice_objeto].angulo_sentido[2] = parametro3;
}

void fijar_orientacion_obj(s32 indice_objeto, u16 parametro1, u16 parametro2, u16 parametro3) {
    lista_objeto[indice_objeto].orientacion[0] = parametro1;
    lista_objeto[indice_objeto].orientacion[1] = parametro2;
    lista_objeto[indice_objeto].orientacion[2] = parametro3;
}

void fijar_velocidad_obj(s32 indice_objeto, f32 parametro1, f32 parametro2, f32 parametro3) {
    lista_objeto[indice_objeto].velocidad[0] = parametro1;
    lista_objeto[indice_objeto].velocidad[1] = parametro2;
    lista_objeto[indice_objeto].velocidad[2] = parametro3;
}

void funcion_8008B928(s32 indice_objeto, s16 parametro1, s16 parametro2, s16 parametro3, DatosSpline* spline) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->pos_origen[0] = (f32) parametro1;
    objeto->pos_origen[1] = (f32) parametro2;
    objeto->spline = spline;
    objeto->pos_origen[2] = (f32) parametro3;
    objeto->velocidad[0] = (f32) (spline->puntos_control[1].pos[0] - spline->puntos_control[0].pos[0]);
    objeto->velocidad[1] = (f32) (spline->puntos_control[1].pos[1] - spline->puntos_control[0].pos[1]);
    objeto->velocidad[2] = (f32) (spline->puntos_control[1].pos[2] - spline->puntos_control[0].pos[2]);
    objeto->angulo_sentido[1] = obtener_angulo_sentido_y(indice_objeto);
    objeto->velocidad[2] = funcion_800416D8(objeto->velocidad[2], objeto->velocidad[0], -objeto->angulo_sentido[1]);
    objeto->angulo_sentido[0] = obtener_angulo_sentido_x(indice_objeto);
}

SIN_USO void objeto_origen_pos_aleatorizar_alrededor_x(s32 indice_objeto, s16 x, u16 parametro2) {
    s16 desplazamiento_x;

    desplazamiento_x = int_aleatorio(parametro2) - (parametro2 / 2);
    lista_objeto[indice_objeto].pos_origen[0] = x + desplazamiento_x;
}

void objeto_origen_pos_aleatorizar_alrededor_y(s32 indice_objeto, s16 y, u16 parametro2) {
    s16 desplazamiento_y;

    desplazamiento_y = int_aleatorio(parametro2) - (parametro2 / 2);
    lista_objeto[indice_objeto].pos_origen[1] = y + desplazamiento_y;
}

SIN_USO void objeto_origen_pos_aleatorizar_alrededor_z(s32 indice_objeto, s16 z, u16 parametro2) {
    s16 desplazamiento_z;

    desplazamiento_z = int_aleatorio(parametro2) - (parametro2 / 2);
    lista_objeto[indice_objeto].pos_origen[2] = z + desplazamiento_z;
}

SIN_USO void objeto_origen_pos_aleatorizar_alrededor_xy(s32 indice_objeto, s16 x, s16 y, u16 parametro3, u16 parametro4) {
    s16 desplazamiento_x;
    s16 desplazamiento_y;

    desplazamiento_x = int_aleatorio(parametro3) - ((s32) parametro3 / 2);
    desplazamiento_y = int_aleatorio(parametro4) - ((s32) parametro4 / 2);
    lista_objeto[indice_objeto].pos_origen[0] = x + desplazamiento_x;
    lista_objeto[indice_objeto].pos_origen[1] = y + desplazamiento_y;
}

SIN_USO void objeto_origen_pos_aleatorizar_alrededor_xz(s32 indice_objeto, s16 x, s16 z, u16 parametro3, u16 parametro4) {
    s16 desplazamiento_x;
    s16 desplazamiento_z;

    desplazamiento_x = int_aleatorio(parametro3) - ((s32) parametro3 / 2);
    desplazamiento_z = int_aleatorio(parametro4) - ((s32) parametro4 / 2);
    lista_objeto[indice_objeto].pos_origen[0] = x + desplazamiento_x;
    lista_objeto[indice_objeto].pos_origen[2] = z + desplazamiento_z;
}

void objeto_origen_pos_aleatorizar_alrededor_xyz(s32 indice_objeto, s16 x, s16 y, s16 z, u16 parametro4, u16 parametro5, u16 parametro6) {
    s16 desplazamiento_x;
    s16 desplazamiento_y;
    s16 desplazamiento_z;

    desplazamiento_x = int_aleatorio(parametro4) - ((s32) parametro4 / 2);
    desplazamiento_y = int_aleatorio(parametro5) - ((s32) parametro5 / 2);
    desplazamiento_z = int_aleatorio(parametro6) - ((s32) parametro6 / 2);
    lista_objeto[indice_objeto].pos_origen[0] = x + desplazamiento_x;
    lista_objeto[indice_objeto].pos_origen[1] = y + desplazamiento_y;
    lista_objeto[indice_objeto].pos_origen[2] = z + desplazamiento_z;
}

void objeto_origen_pos_alrededor_jugador_uno(s32 indice_objeto, s16 dist, u16 angulo) {
    lista_objeto[indice_objeto].pos_origen[0] = copia_jugador_uno->pos[0] + (senos(angulo) * dist);
    lista_objeto[indice_objeto].pos_origen[2] = copia_jugador_uno->pos[2] + (coss(angulo) * dist);
}

SIN_USO void funcion_8008BEA4(s32 indice_objeto, u16 parametro1, u16 parametro2) {
    u16 cosa;
    u16 cosa2;

    cosa = int_aleatorio(parametro1);
    cosa2 = camara1->rot[1] + int_aleatorio(parametro2) - ((s32) parametro2 / 2);
    objeto_origen_pos_alrededor_jugador_uno(indice_objeto, cosa, cosa2);
}
