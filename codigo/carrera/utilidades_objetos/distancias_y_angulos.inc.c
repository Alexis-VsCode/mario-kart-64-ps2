// Distancias y angulos

void funcion_80086E70(s32 indice_objeto) {
    lista_objeto[indice_objeto].desconocido_0AE = 1;
    fijar_objeto_bandera_situacion_false(indice_objeto, 8);
}

void funcion_80086EAC(s32 indice_objeto, s32 parametro1, s16 parametro2) {
    lista_objeto[indice_objeto].desconocido_0DD = parametro1;
    lista_objeto[indice_objeto].desconocido_0AE = parametro2;
    fijar_objeto_bandera_situacion_false(indice_objeto, 8);
}

void funcion_80086EF0(s32 indice_objeto) {
    funcion_80086E70(indice_objeto);
}

void funcion_80086F10(s32 indice_objeto, s32 parametro1, DatosSpline* spline) {
    funcion_80086E70(indice_objeto);
    lista_objeto[indice_objeto].desconocido_0DE = parametro1;
    lista_objeto[indice_objeto].spline = spline;
}

void funcion_80086F60(s32 indice_objeto) {
    lista_objeto[indice_objeto].desconocido_0AE = 0;
    lista_objeto[indice_objeto].desconocido_0DD = 0;
    lista_objeto[indice_objeto].desconocido_0DE = 0;
    fijar_objeto_bandera_situacion_false(indice_objeto, 8);
}

bool funcion_80086FA4(s32 indice_objeto) {
    bool devuelto = false;
    if (lista_objeto[indice_objeto].desconocido_0AE == 0) {
        devuelto = true;
    }
    return devuelto;
}

void funcion_80086FD4(s32 indice_objeto) {
    fijar_objeto_bandera_situacion_false(indice_objeto, 8);
    lista_objeto[indice_objeto].desconocido_0AE += 1;
}

void funcion_8008701C(s32 indice_objeto, s32 parametro1) {
    fijar_objeto_bandera_situacion_false(indice_objeto, 8);
    lista_objeto[indice_objeto].desconocido_0AE = parametro1;
}

s32 funcion_80087060(s32 indice_objeto, s32 parametro1) {
    s32 sp1_c;

    sp1_c = 0;
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 8) != false) {
        fijar_objeto_bandera_situacion_true(indice_objeto, 8);
        lista_objeto[indice_objeto].desconocido_0B0 = parametro1;
    }
    lista_objeto[indice_objeto].desconocido_0B0--;
    if (lista_objeto[indice_objeto].desconocido_0B0 < 0) {
        fijar_objeto_bandera_situacion_false(indice_objeto, 8);
        sp1_c = 1;
    }
    return sp1_c;
}

s32 funcion_80087104(s32 indice_objeto, u16 parametro1) {
    s32 sp24;

    sp24 = 0;
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 8) != false) {
        fijar_objeto_bandera_situacion_true(indice_objeto, 8);
        lista_objeto[indice_objeto].desconocido_0B0 = int_aleatorio(parametro1);
    }
    lista_objeto[indice_objeto].desconocido_0B0--;
    if (lista_objeto[indice_objeto].desconocido_0B0 < 0) {
        fijar_objeto_bandera_situacion_false(indice_objeto, 8);
        sp24 = 1;
    }
    return sp24;
}

s32 funcion_800871AC(s32 indice_objeto, s32 parametro1) {
    s32 sp24;

    sp24 = 0;
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 8) != false) {
        fijar_objeto_bandera_situacion_true(indice_objeto, 8);
        lista_objeto[indice_objeto].desconocido_0B0 = (s16) parametro1;
    }
    lista_objeto[indice_objeto].desconocido_0B0--;
    if (lista_objeto[indice_objeto].desconocido_0B0 < 0) {
        fijar_objeto_bandera_situacion_false(indice_objeto, 8);
        funcion_80086FD4(indice_objeto);
        sp24 = 1;
    }
    return sp24;
}

SIN_USO void funcion_80087258(s32 indice_objeto, SIN_USO s32 parametro1, f32 parametro2) {
    lista_objeto[indice_objeto].offset[1] += parametro2;
    lista_objeto[indice_objeto].offset[2] -= parametro2;
}

SIN_USO s32 obtener_angulo_entre_objeto_jugador(s32 indice_objeto, Jugador* jugador) {
    return obtener_angulo_entre_xy(jugador->pos[0], lista_objeto[indice_objeto].pos[0], jugador->pos[2],
                                lista_objeto[indice_objeto].pos[2]);
}

s32 angulo_entre_camara_objeto(s32 indice_objeto, Camara* camara) {
    return atan2s(lista_objeto[indice_objeto].pos[0] - camara->pos[0], lista_objeto[indice_objeto].pos[2] - camara->pos[2]);
}

u16 obtener_angulo_sentido_x(s32 indice_objeto) {
    return -atan2s(lista_objeto[indice_objeto].velocidad[1], lista_objeto[indice_objeto].velocidad[2]);
}

s32 obtener_angulo_sentido_y(s32 indice_objeto) {
    return atan2s(lista_objeto[indice_objeto].velocidad[0], lista_objeto[indice_objeto].velocidad[2]);
}

SIN_USO void funcion_800873A4(s32 indice_objeto) {
    lista_objeto[indice_objeto].angulo_sentido[0] =
        funcion_800417B4(lista_objeto[indice_objeto].angulo_sentido[0], obtener_angulo_sentido_x(indice_objeto));
}

void funcion_800873F4(s32 indice_objeto) {
    lista_objeto[indice_objeto].angulo_sentido[1] =
        funcion_800417B4(lista_objeto[indice_objeto].angulo_sentido[1], obtener_angulo_sentido_y(indice_objeto));
}

SIN_USO void funcion_80087444(s32 indice_objeto) {
    lista_objeto[indice_objeto].velocidad[0] =
        lista_objeto[indice_objeto].desconocido_034 * senos(lista_objeto[indice_objeto].angulo_sentido[1]);
}

SIN_USO void funcion_8008748C(s32 indice_objeto) {
    lista_objeto[indice_objeto].velocidad[1] =
        lista_objeto[indice_objeto].desconocido_034 * coss(lista_objeto[indice_objeto].angulo_sentido[0]);
}

SIN_USO void funcion_800874D4(s32 indice_objeto) {
    lista_objeto[indice_objeto].velocidad[2] =
        lista_objeto[indice_objeto].desconocido_034 * coss(lista_objeto[indice_objeto].angulo_sentido[1]);
}

void funcion_8008751C(s32 indice_objeto) {
    lista_objeto[indice_objeto].velocidad[0] =
        lista_objeto[indice_objeto].desconocido_034 * senos(lista_objeto[indice_objeto].angulo_sentido[1]);
    lista_objeto[indice_objeto].velocidad[2] =
        lista_objeto[indice_objeto].desconocido_034 * coss(lista_objeto[indice_objeto].angulo_sentido[1]);
}

void funcion_8008757C(s32 indice_objeto) {
    f32 sp24;

    sp24 = coss(lista_objeto[indice_objeto].angulo_sentido[0]);
    lista_objeto[indice_objeto].velocidad[0] =
        (lista_objeto[indice_objeto].desconocido_034 * sp24) * senos(lista_objeto[indice_objeto].angulo_sentido[1]);
    lista_objeto[indice_objeto].velocidad[1] =
        -lista_objeto[indice_objeto].desconocido_034 * senos(lista_objeto[indice_objeto].angulo_sentido[0]);
    sp24 = coss(lista_objeto[indice_objeto].angulo_sentido[0]);
    lista_objeto[indice_objeto].velocidad[2] =
        (lista_objeto[indice_objeto].desconocido_034 * sp24) * coss(lista_objeto[indice_objeto].angulo_sentido[1]);
}

void funcion_80087620(s32 indice_objeto) {
    lista_objeto[indice_objeto].velocidad[0] =
        lista_objeto[indice_objeto].desconocido_034 * senos(lista_objeto[indice_objeto].angulo_sentido[1] + 0x8000);
    lista_objeto[indice_objeto].velocidad[2] =
        lista_objeto[indice_objeto].desconocido_034 * coss(lista_objeto[indice_objeto].angulo_sentido[1] + 0x8000);
}

void funcion_800876A0(s32 indice_objeto) {
    lista_objeto[indice_objeto].offset[0] +=
        lista_objeto[indice_objeto].desconocido_034 * senos(lista_objeto[indice_objeto].angulo_sentido[1]);
    lista_objeto[indice_objeto].offset[2] +=
        lista_objeto[indice_objeto].desconocido_034 * coss(lista_objeto[indice_objeto].angulo_sentido[1]);
}

void agregar_desplazamiento_xyz_velocidad_objeto(s32 indice_objeto) {
    lista_objeto[indice_objeto].offset[0] += lista_objeto[indice_objeto].velocidad[0];
    lista_objeto[indice_objeto].offset[1] += lista_objeto[indice_objeto].velocidad[1];
    lista_objeto[indice_objeto].offset[2] += lista_objeto[indice_objeto].velocidad[2];
}

void agregar_desplazamiento_xz_velocidad_objeto(s32 indice_objeto) {
    lista_objeto[indice_objeto].offset[0] += lista_objeto[indice_objeto].velocidad[0];
    lista_objeto[indice_objeto].offset[2] += lista_objeto[indice_objeto].velocidad[2];
}

SIN_USO void agregar_desplazamiento_x_velocidad_objeto(s32 indice_objeto) {
    lista_objeto[indice_objeto].offset[0] += lista_objeto[indice_objeto].velocidad[0];
}

void agregar_desplazamiento_y_velocidad_objeto(s32 indice_objeto) {
    lista_objeto[indice_objeto].offset[1] += lista_objeto[indice_objeto].velocidad[1];
}

SIN_USO void agregar_desplazamiento_z_velocidad_objeto(s32 indice_objeto) {
    lista_objeto[indice_objeto].offset[2] += lista_objeto[indice_objeto].velocidad[2];
}

void funcion_8008781C(s32 parametro0) {
    funcion_8008751C(parametro0);
    agregar_desplazamiento_xz_velocidad_objeto(parametro0);
}

void funcion_80087844(s32 parametro0) {
    funcion_8008757C(parametro0);
    agregar_desplazamiento_xyz_velocidad_objeto(parametro0);
}

f32 funcion_8008786C(f32 parametro0, f32 parametro1, f32 parametro2, f32 parametro3, f32 parametro4) {
    return (((parametro4 - parametro2) / (parametro3 - parametro1)) * (parametro0 - parametro1)) + parametro2;
}

s32 funcion_8008789C(s32 indice_objeto, s32 parametro1) {
    s32 sp24;

    sp24 = 0;
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 8) != false) {
        fijar_objeto_bandera_situacion_true(indice_objeto, 8);
        funcion_8008751C(indice_objeto);
        lista_objeto[indice_objeto].desconocido_0B0 = parametro1;
    }
    lista_objeto[indice_objeto].desconocido_0B0--;
    if (lista_objeto[indice_objeto].desconocido_0B0 < 0) {
        fijar_objeto_bandera_situacion_false(indice_objeto, 8);
        sp24 = 1;
    } else {
        agregar_desplazamiento_xz_velocidad_objeto(indice_objeto);
    }
    return sp24;
}

s32 funcion_80087954(s32 indice_objeto, s32 parametro1) {
    s32 sp24;

    sp24 = 0;
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 8) != false) {
        fijar_objeto_bandera_situacion_true(indice_objeto, 8);
        funcion_80087620(indice_objeto);
        lista_objeto[indice_objeto].desconocido_0B0 = parametro1;
    }
    lista_objeto[indice_objeto].desconocido_0B0--;
    if (lista_objeto[indice_objeto].desconocido_0B0 < 0) {
        fijar_objeto_bandera_situacion_false(indice_objeto, 8);
        sp24 = 1;
    } else {
        agregar_desplazamiento_xz_velocidad_objeto(indice_objeto);
    }
    return sp24;
}

bool funcion_80087A0C(s32 indice_objeto, s16 parametro1, s16 parametro2, s16 parametro3, s16 parametro4) {
    s16 dist;
    s16 temporal_a0;
    s16 temporal_v0;
    bool sp2_c;

    sp2_c = false;
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 8) != false) {
        fijar_objeto_bandera_situacion_true(indice_objeto, 8);
        temporal_v0 = parametro2 - parametro1;
        temporal_a0 = parametro4 - parametro3;
        dist = sqrtf((temporal_v0 * temporal_v0) + (temporal_a0 * temporal_a0));
        lista_objeto[indice_objeto].pos_origen[1] = 0.0f;
        lista_objeto[indice_objeto].angulo_sentido[1] = atan2s(temporal_v0, temporal_a0);
        funcion_8008751C(indice_objeto);
        lista_objeto[indice_objeto].desconocido_0B0 = dist / lista_objeto[indice_objeto].desconocido_034;
    }
    lista_objeto[indice_objeto].desconocido_0B0--;
    if (lista_objeto[indice_objeto].desconocido_0B0 < 0) {
        fijar_objeto_bandera_situacion_false(indice_objeto, 8);
        sp2_c = true;
    } else {
        agregar_desplazamiento_xz_velocidad_objeto(indice_objeto);
    }
    return sp2_c;
}

s32 funcion_80087B84(s32 indice_objeto, f32 parametro1, f32 parametro2) {
    s32 sp24;

    sp24 = 0;
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 8) != false) {
        fijar_objeto_bandera_situacion_true(indice_objeto, 8);
        lista_objeto[indice_objeto].velocidad[1] = -parametro1;
    }
    agregar_desplazamiento_y_velocidad_objeto(indice_objeto);
    if (lista_objeto[indice_objeto].pos[1] <= parametro2) {
        fijar_objeto_bandera_situacion_false(indice_objeto, 8);
        funcion_80086FD4(indice_objeto);
        sp24 = 1;
    }
    return sp24;
}

s32 funcion_80087C48(s32 indice_objeto, f32 parametro1, f32 parametro2, s32 parametro3) {
    s32 sp24;

    sp24 = 0;
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 8) != false) {
        fijar_objeto_bandera_situacion_true(indice_objeto, 8);
        lista_objeto[indice_objeto].velocidad[1] = parametro1;
        lista_objeto[indice_objeto].desconocido_0B0 = (s16) parametro3;
    }
    lista_objeto[indice_objeto].desconocido_0B0--;
    if (lista_objeto[indice_objeto].desconocido_0B0 < 0) {
        fijar_objeto_bandera_situacion_false(indice_objeto, 8);
        funcion_80086FD4(indice_objeto);
        sp24 = 1;
    } else {
        lista_objeto[indice_objeto].velocidad[1] -= parametro2;
        agregar_desplazamiento_y_velocidad_objeto(indice_objeto);
    }
    return sp24;
}

s32 funcion_80087D24(s32 indice_objeto, f32 parametro1, f32 parametro2, f32 parametro3) {
    s32 sp24;

    sp24 = 0;
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 8) != 0) {
        fijar_objeto_bandera_situacion_true(indice_objeto, 8);
        lista_objeto[indice_objeto].velocidad[1] = parametro1;
    }
    lista_objeto[indice_objeto].velocidad[1] -= parametro2;
    agregar_desplazamiento_y_velocidad_objeto(indice_objeto);
    if (lista_objeto[indice_objeto].offset[1] <= parametro3) {
        fijar_objeto_bandera_situacion_false(indice_objeto, 8);
        lista_objeto[indice_objeto].offset[1] = parametro3;
        funcion_80086FD4(indice_objeto);
        sp24 = 1;
    }
    return sp24;
}

bool funcion_80087E08(s32 indice_objeto, f32 parametro1, f32 parametro2, f32 parametro3, s16 parametro4, s32 parametro5) {
    bool sp2_c;
    SIN_USO s32 relleno;

    sp2_c = false;
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 8) != 0) {
        fijar_objeto_bandera_situacion_true(indice_objeto, 8);
        lista_objeto[indice_objeto].offset[2] = 0.0f;
        lista_objeto[indice_objeto].offset[1] = 0.0f;
        lista_objeto[indice_objeto].offset[0] = 0.0f;
        lista_objeto[indice_objeto].desconocido_034 = parametro3;
        lista_objeto[indice_objeto].velocidad[1] = parametro1;
        lista_objeto[indice_objeto].angulo_sentido[1] = parametro4;
        funcion_8008751C(indice_objeto);
        lista_objeto[indice_objeto].desconocido_0B0 = parametro5;
    }
    lista_objeto[indice_objeto].desconocido_0B0--;
    if (lista_objeto[indice_objeto].desconocido_0B0 < 0) {
        fijar_objeto_bandera_situacion_false(indice_objeto, 8);
        funcion_80086FD4(indice_objeto);
        sp2_c = true;
    } else {
        lista_objeto[indice_objeto].velocidad[1] -= parametro2;
        agregar_desplazamiento_xyz_velocidad_objeto(indice_objeto);
    }
    return sp2_c;
}

SIN_USO s32 funcion_80087F14(s32 indice_objeto, f32 parametro1, f32 parametro2, f32 parametro3, s16 parametro4, s32 parametro5) {
    s32 sp2_c;
    SIN_USO s32 margen_pila;

    sp2_c = 0;
    if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 8) != 0) {
        fijar_objeto_bandera_situacion_true(indice_objeto, 8);
        lista_objeto[indice_objeto].offset[2] = 0.0f;
        lista_objeto[indice_objeto].offset[1] = 0.0f;
        lista_objeto[indice_objeto].offset[0] = 0.0f;
        lista_objeto[indice_objeto].desconocido_034 = parametro3;
        lista_objeto[indice_objeto].velocidad[1] = parametro1;
        lista_objeto[indice_objeto].angulo_sentido[1] = parametro4;
        funcion_8008751C(indice_objeto);
        lista_objeto[indice_objeto].desconocido_0B0 = temporizador_vblank;
    }
    if (lista_objeto[indice_objeto].offset[1] <= parametro5) {
        fijar_objeto_bandera_situacion_false(indice_objeto, 8);
        funcion_80086FD4(indice_objeto);
        sp2_c = 1;
    } else {
        lista_objeto[indice_objeto].velocidad[1] -= parametro2;
        agregar_desplazamiento_xyz_velocidad_objeto(indice_objeto);
    }
    return sp2_c;
}

void funcion_80088038(s32 indice_objeto, f32 parametro1, u16 parametro2) {
    f32 temporal_f4;
    f32 sp20;

    temporal_f4 = lista_objeto[indice_objeto].offset[0];
    sp20 = lista_objeto[indice_objeto].offset[2];
    lista_objeto[indice_objeto].desconocido_0C4 += parametro2;
    lista_objeto[indice_objeto].offset[0] = senos(lista_objeto[indice_objeto].desconocido_0C4) * parametro1;
    lista_objeto[indice_objeto].offset[2] = coss(lista_objeto[indice_objeto].desconocido_0C4) * parametro1;
    lista_objeto[indice_objeto].velocidad[0] = lista_objeto[indice_objeto].offset[0] - temporal_f4;
    lista_objeto[indice_objeto].velocidad[2] = lista_objeto[indice_objeto].offset[2] - sp20;
}

SIN_USO void funcion_800880DC(void) {
}

void funcion_800880E4(s32 indice_objeto) {
    PuntoControlSpline* phi_v0;
    s32 algun_indice;
    phi_v0 = lista_objeto[indice_objeto].puntos_control;
    for (algun_indice = 0; algun_indice < 2; algun_indice++, phi_v0++) {
        dato_80165760[algun_indice] = phi_v0->pos[0];
        dato_80165770[algun_indice] = phi_v0->pos[1];
        dato_80165780[algun_indice] = phi_v0->pos[2];
    }
}

void funcion_80088150(s32 parametro0) {
    lista_objeto[parametro0].puntos_control++;
}

void funcion_80088178(s32 indice_objeto, s32 parametro1) {
    s16 temporal_a1;
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    temporal_a1 = atan2s(dato_80165760[1] - dato_80165760[0], dato_80165780[1] - dato_80165780[0]);
    temporal_a1 -= objeto->angulo_sentido[1];
    if (temporal_a1 > 0) {
        objeto->angulo_sentido[1] += (parametro1 << 8);
    } else if (temporal_a1 < 0) {
        objeto->angulo_sentido[1] -= (parametro1 << 8);
    }
}

void funcion_80088228(s32 indice_objeto) {
    Objeto* objeto;
    objeto = &lista_objeto[indice_objeto];
    objeto->desconocido_084[9] = 0;
    objeto->puntos_control = objeto->spline->puntos_control;
    objeto->desconocido_084[8] = *((s16*) objeto->puntos_control - 1);
    objeto->offset[0] = objeto->puntos_control[0].pos[0];
    objeto->offset[1] = objeto->puntos_control[0].pos[1];
    objeto->offset[2] = objeto->puntos_control[0].pos[2];
    funcion_80086FD4(indice_objeto);
}

s32 funcion_800882B0(s32 indice_objeto, s32 parametro1) {
    s32 temporal_f0;
    s32 temporal_f12;
    s32 temporal_f2;
    s32 variable_v1;

    variable_v1 = 0;
    temporal_f0 = (s32) ((dato_80165760[1] - lista_objeto[indice_objeto].offset[0]) *
                     (dato_80165760[1] - lista_objeto[indice_objeto].offset[0]));
    temporal_f12 = (s32) ((dato_80165770[1] - lista_objeto[indice_objeto].offset[1]) *
                      (dato_80165770[1] - lista_objeto[indice_objeto].offset[1]));
    temporal_f2 = (s32) ((dato_80165780[1] - lista_objeto[indice_objeto].offset[2]) *
                     (dato_80165780[1] - lista_objeto[indice_objeto].offset[2]));
    if ((temporal_f0 + temporal_f12 + temporal_f2 - (parametro1 * parametro1)) <= 0) {
        variable_v1 = 1;
    }
    return variable_v1;
}

void funcion_80088364(s32 indice_objeto) {
    Objeto* objeto;

    funcion_800880E4(indice_objeto);
    funcion_80088178(indice_objeto, 1);
    funcion_800876A0(indice_objeto);
    if (funcion_800882B0(indice_objeto, 0x0000000A) != 0) {
        objeto = &lista_objeto[indice_objeto];
        objeto->desconocido_084[9] = (u16) objeto->desconocido_084[9] + 1;
        if (((u16) objeto->desconocido_084[9] + 3) == (u16) objeto->desconocido_084[8]) {
            objeto->desconocido_0AE += 1;
        } else {
            funcion_80088150(indice_objeto);
        }
    }
}

void funcion_800883FC(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 0:
            break;
        case 1:
            funcion_80088228(indice_objeto);
            break;
        case 2:
            funcion_80088364(indice_objeto);
            break;
        case 3:
            funcion_80086F60(indice_objeto);
            break;
    }
}

s32 funcion_8008847C(s32 indice_objeto) {
    s32 sp2_c;

    sp2_c = 0;
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00800000);
    if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000400) != 0) {
        comprobar_colision_envolvente(&dato_8018C3B0, 10.0f, lista_objeto[indice_objeto].pos[0], 20.0f,
                                 lista_objeto[indice_objeto].pos[2]);
        if (dato_8018C3B0.unk34 == 1) {
            sp2_c = 1;
            fijar_objeto_bandera_situacion_true(indice_objeto, 0x00800000);
        }
        lista_objeto[indice_objeto].altura_superficie = calcular_altura_superficie(
            lista_objeto[indice_objeto].pos[0], 0.0f, lista_objeto[indice_objeto].pos[2], dato_8018C3B0.indice_zx_malla);
    }
    return sp2_c;
}

s32 funcion_80088538(s32 indice_objeto) {
    s32 sp2_c;

    sp2_c = 0;
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00800000);
    if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000400) != 0) {
        comprobar_colision_envolvente(&dato_8018C3B0, 10.0f, lista_objeto[indice_objeto].pos[0], 20.0f,
                                 lista_objeto[indice_objeto].pos[2]);
        if (dato_8018C3B0.unk34 == 1) {
            sp2_c = 1;
            fijar_objeto_bandera_situacion_true(indice_objeto, 0x00800000);
        }
        lista_objeto[indice_objeto].altura_superficie = calcular_altura_superficie(
            lista_objeto[indice_objeto].pos[0], 0.0f, lista_objeto[indice_objeto].pos[2], dato_8018C3B0.indice_zx_malla);
        lista_objeto[indice_objeto].desconocido_0B8[0] =
            atan2s(dato_8018C3B0.vector_orientacion[2], dato_8018C3B0.vector_orientacion[1]) + 0x4000;
        lista_objeto[indice_objeto].desconocido_0B8[2] = atan2s(dato_8018C3B0.vector_orientacion[0], dato_8018C3B0.vector_orientacion[1]);
    }
    return sp2_c;
}

s32 funcion_8008861C(s32 indice_objeto) {
    s32 sp2_c;

    sp2_c = 0;
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00800000);
    if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000400) != 0) {
        comprobar_colision_envolvente(&dato_8018C3B0, 10.0f, lista_objeto[indice_objeto].pos[0], 20.0f,
                                 lista_objeto[indice_objeto].pos[2]);
        if (dato_8018C3B0.unk34 == 1) {
            sp2_c = 1;
            fijar_objeto_bandera_situacion_true(indice_objeto, 0x00800000);
        }
        lista_objeto[indice_objeto].altura_superficie = calcular_altura_superficie(
            lista_objeto[indice_objeto].pos[0], 0.0f, lista_objeto[indice_objeto].pos[2], dato_8018C3B0.indice_zx_malla);
        lista_objeto[indice_objeto].desconocido_01C[0] = dato_8018C3B0.vector_orientacion[0];
        lista_objeto[indice_objeto].desconocido_01C[1] = dato_8018C3B0.vector_orientacion[1];
        lista_objeto[indice_objeto].desconocido_01C[2] = dato_8018C3B0.vector_orientacion[2];
    }
    return sp2_c;
}

void funcion_800886F4(s32 indice_objeto) {
    comprobar_colision_envolvente(&dato_8018C3B0, 10.0f, lista_objeto[indice_objeto].pos[0], 20.0f,
                             lista_objeto[indice_objeto].pos[2]);
    if (dato_8018C3B0.unk34 == 1) {
        fijar_objeto_bandera_situacion_true(indice_objeto, 0x00800000);
        lista_objeto[indice_objeto].altura_superficie = calcular_altura_superficie(
            lista_objeto[indice_objeto].pos[0], 0.0f, lista_objeto[indice_objeto].pos[2], dato_8018C3B0.indice_zx_malla);
        lista_objeto[indice_objeto].desconocido_0B8[0] =
            atan2s(dato_8018C3B0.vector_orientacion[2], dato_8018C3B0.vector_orientacion[1]) + 0x4000;
        lista_objeto[indice_objeto].desconocido_0B8[2] = atan2s(dato_8018C3B0.vector_orientacion[0], dato_8018C3B0.vector_orientacion[1]);
        return;
    }
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00800000);
}

void funcion_800887C0(s32 indice_objeto) {
    comprobar_colision_envolvente(&dato_8018C3B0, 10.0f, lista_objeto[indice_objeto].pos[0], 20.0f,
                             lista_objeto[indice_objeto].pos[2]);
    if (dato_8018C3B0.unk34 == 1) {
        fijar_objeto_bandera_situacion_true(indice_objeto, 0x00800000);
        lista_objeto[indice_objeto].altura_superficie = calcular_altura_superficie(
            lista_objeto[indice_objeto].pos[0], 0.0f, lista_objeto[indice_objeto].pos[2], dato_8018C3B0.indice_zx_malla);
        lista_objeto[indice_objeto].velocidad[0] = dato_8018C3B0.vector_orientacion[0];
        lista_objeto[indice_objeto].velocidad[1] = dato_8018C3B0.vector_orientacion[1];
        lista_objeto[indice_objeto].velocidad[2] = dato_8018C3B0.vector_orientacion[2];
        return;
    }
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00800000);
}

SIN_USO s32 obtener_distancia_horizontal_a_jugador(s32 indice_objeto, Jugador* jugador) {
    s32 x;
    s32 y;

    x = lista_objeto[indice_objeto].pos[0] - jugador->pos[0];
    y = lista_objeto[indice_objeto].pos[2] - jugador->pos[2];
    return (x * x) + (y * y);
}

SIN_USO s32 obtener_distancia_a_jugador(s32 indice_objeto, Jugador* jugador) {
    s32 x;
    s32 z;
    s32 y;

    x = lista_objeto[indice_objeto].pos[0] - jugador->pos[0];
    y = lista_objeto[indice_objeto].pos[1] - jugador->pos[1];
    z = lista_objeto[indice_objeto].pos[2] - jugador->pos[2];
    return (x * x) + (y * y) + (z * z);
}

u32 obtener_distancia_horizontal_a_camara(s32 indice_objeto, Camara* camara) {
    s32 x;
    s32 y;

    x = lista_objeto[indice_objeto].pos[0] - camara->pos[0];
    y = lista_objeto[indice_objeto].pos[2] - camara->pos[2];
    return (x * x) + (y * y);
}

SIN_USO s32 obtener_distancia_a_camara(s32 indice_objeto, Camara* camara) {
    s32 x;
    s32 z;
    s32 y;

    x = lista_objeto[indice_objeto].pos[0] - camara->pos[0];
    y = lista_objeto[indice_objeto].pos[1] - camara->pos[1];
    z = lista_objeto[indice_objeto].pos[2] - camara->pos[2];
    return (x * x) + (y * y) + (z * z);
}

bool es_dentro_distancia_horizontal_de_jugador(s32 indice_objeto, Jugador* jugador, f32 distancia) {
    f32 x;
    f32 y;
    bool variable_v1;

    variable_v1 = false;
    x = lista_objeto[indice_objeto].pos[0] - jugador->pos[0];
    y = lista_objeto[indice_objeto].pos[2] - jugador->pos[2];
    if (((x * x) + (y * y)) <= (distancia * distancia)) {
        variable_v1 = true;
    }
    return variable_v1;
}

bool es_en_limites_a_jugador(s32 indice_objeto, Jugador* jugador, f32 min_distancia, f32 max_distancia) {
    f32 x;
    f32 distancia;
    f32 z;
    bool variable_v1;

    variable_v1 = false;
    x = lista_objeto[indice_objeto].pos[0] - jugador->pos[0];
    z = lista_objeto[indice_objeto].pos[2] - jugador->pos[2];
    distancia = (x * x) + (z * z);
    if (((min_distancia * min_distancia) <= distancia) && (distancia <= (max_distancia * max_distancia))) {
        variable_v1 = true;
    }
    return variable_v1;
}

bool es_dentro_distancia_a_jugador(s32 indice_objeto, Jugador* jugador, f32 distancia) {
    f32 x;
    f32 z;
    f32 y;
    bool variable_v1;

    variable_v1 = false;
    x = lista_objeto[indice_objeto].pos[0] - jugador->pos[0];
    y = lista_objeto[indice_objeto].pos[1] - jugador->pos[1];
    z = lista_objeto[indice_objeto].pos[2] - jugador->pos[2];
    if (((x * x) + (y * y) + (z * z)) <= (distancia * distancia)) {
        variable_v1 = true;
    }
    return variable_v1;
}

bool es_dentro_distancia_horizontal_a_camara(s32 indice_objeto, Camara* camara, f32 distancia) {
    f32 x;
    f32 y;
    bool variable_v1;

    variable_v1 = false;
    x = lista_objeto[indice_objeto].pos[0] - camara->pos[0];
    y = lista_objeto[indice_objeto].pos[2] - camara->pos[2];
    if (((x * x) + (y * y)) <= (distancia * distancia)) {
        variable_v1 = true;
    }
    return variable_v1;
}

SIN_USO bool es_dentro_limites_a_camara(s32 indice_objeto, Camara* camara, f32 min_distancia, f32 max_distancia) {
    f32 x;
    f32 distancia;
    f32 z;
    bool variable_v1;

    variable_v1 = false;
    x = lista_objeto[indice_objeto].pos[0] - camara->pos[0];
    z = lista_objeto[indice_objeto].pos[2] - camara->pos[2];
    distancia = (x * x) + (z * z);
    if (((min_distancia * min_distancia) <= distancia) && (distancia <= (max_distancia * max_distancia))) {
        variable_v1 = true;
    }
    return variable_v1;
}

SIN_USO bool es_dentro_distancia_a_camara(s32 indice_objeto, Camara* camara, f32 distancia) {
    f32 x;
    f32 z;
    f32 y;
    bool variable_v1;

    variable_v1 = false;
    x = lista_objeto[indice_objeto].pos[0] - camara->pos[0];
    y = lista_objeto[indice_objeto].pos[1] - camara->pos[1];
    z = lista_objeto[indice_objeto].pos[2] - camara->pos[2];
    if (((x * x) + (y * y) + (z * z)) <= (distancia * distancia)) {
        variable_v1 = true;
    }
    return variable_v1;
}

bool tiene_horizontalmente_chocado_con_jugador(s32 indice_objeto, Jugador* jugador) {
    f32 x;
    f32 distancia;
    f32 z;
    bool variable_v1;

    variable_v1 = false;
    x = lista_objeto[indice_objeto].pos[0] - jugador->pos[0];
    z = lista_objeto[indice_objeto].pos[2] - jugador->pos[2];
    distancia = lista_objeto[indice_objeto].tamanio_caja_envolvente + jugador->tamanio_caja_envolvente;
    if (((x * x) + (z * z)) <= (distancia * distancia)) {
        variable_v1 = true;
    }
    return variable_v1;
}

bool tiene_chocado_con_jugador(s32 indice_objeto, Jugador* jugador) {
    f32 x;
    f32 z;
    f32 distancia;
    f32 y;
    bool variable_v1;

    variable_v1 = false;
    x = lista_objeto[indice_objeto].pos[0] - jugador->pos[0];
    y = lista_objeto[indice_objeto].pos[1] - jugador->pos[1];
    z = lista_objeto[indice_objeto].pos[2] - jugador->pos[2];
    distancia = lista_objeto[indice_objeto].tamanio_caja_envolvente + jugador->tamanio_caja_envolvente;
    if (((x * x) + (y * y) + (z * z)) <= (distancia * distancia)) {
        variable_v1 = true;
    }
    return variable_v1;
}

SIN_USO bool tiene_chocado_con_jugador_1d(s32 indice_objeto, Jugador* jugador, f32 distancia) {
    f32 x;
    bool variable_v1;

    variable_v1 = false;
    x = lista_objeto[indice_objeto].pos[1] - jugador->pos[1];
    if ((x * x) <= (distancia * distancia)) {
        variable_v1 = true;
    }
    return variable_v1;
}

bool tiene_chocado_con_jugador_y_dentro_altura(s32 indice_objeto, Jugador* jugador, f32 distancia_y) {
    f32 x;
    f32 z;
    f32 distancia;
    f32 y;
    bool variable_v1;

    variable_v1 = false;
    x = lista_objeto[indice_objeto].pos[0] - jugador->pos[0];
    y = lista_objeto[indice_objeto].pos[1] - jugador->pos[1];
    z = lista_objeto[indice_objeto].pos[2] - jugador->pos[2];
    distancia = lista_objeto[indice_objeto].tamanio_caja_envolvente + jugador->tamanio_caja_envolvente;
    // abs(y)
    if (y < 0.0f) {
        y = -y;
    }
    if ((((x * x) + (z * z)) <= (distancia * distancia)) && (y <= distancia_y)) {
        variable_v1 = true;
    }
    return variable_v1;
}

f32 funcion_80088F54(s32 indice_objeto, Jugador* jugador) {
    f32 distancia;

    distancia = lista_objeto[indice_objeto].pos[1] - jugador->desconocido_074;
    if (distancia < 0.0f) {
        distancia = -distancia;
    }
    return distancia;
}

SIN_USO bool funcion_80088F94(s32 indice_objeto, Jugador* jugador, f32 parametro2) {
    f32 distancia;
    bool variable_v1;

    distancia = lista_objeto[indice_objeto].pos[1] - jugador->desconocido_074;
    variable_v1 = false;
    if (distancia < 0.0f) {
        distancia = -distancia;
    }
    if (distancia <= parametro2) {
        variable_v1 = true;
    }
    return variable_v1;
}

void funcion_80088FF0(Jugador* jugador) {
    jugador->desconocido_08C = 0.0f;
    jugador->actual_rapidez = 0.0f;
    jugador->velocidad[0] = 0.0f;
    jugador->velocidad[2] = 0.0f;
}

SIN_USO void funcion_8008900C(Jugador* jugador) {
    jugador->desconocido_08C = 0.0f;
    jugador->actual_rapidez = 0.0f;
}

void funcion_80089020(s32 id_jugador, f32* parametro1) {
    f32 variable_f0;
    f32 variable_f2;
    Jugador* jugador = &jugador_uno[id_jugador];

    if (*parametro1 >= 0.0f) {
        variable_f2 = *parametro1;
    } else {
        variable_f2 = -*parametro1;
    }
    if (jugador->efectos & (EFECTO_TROMPO_BANANA | EFECTO_TROMPO_CONDUCIENDO)) {
        if (id_circuito_actual == CIRCUITO_SHERBET_LAND) {
            if (variable_f2 <= 0.5) {
                variable_f0 = 0.025f;
            } else if (variable_f2 <= 2.0) {
                variable_f0 = 0.075f;
            } else if (variable_f2 <= 4.0) {
                variable_f0 = 0.15f;
            } else {
                variable_f0 = 0.25f;
            }
        } else {
            if (variable_f2 <= 2.0) {
                variable_f0 = 0.1f;
            } else if (variable_f2 <= 3.0) {
                variable_f0 = 0.15f;
            } else if (variable_f2 <= 4.0) {
                variable_f0 = 0.2f;
            } else {
                variable_f0 = 0.25f;
            }
        }
    } else if (id_circuito_actual == CIRCUITO_SHERBET_LAND) {
        if (variable_f2 <= 0.5) {
            variable_f0 = 0.025f;
        } else if (variable_f2 <= 2.0) {
            variable_f0 = 0.075f;
        } else if (variable_f2 <= 4.0) {
            variable_f0 = 0.1f;
        } else {
            variable_f0 = 0.15f;
        }
    } else {
        if (variable_f2 <= 2.0) {
            variable_f0 = 0.06f;
        } else if (variable_f2 <= 3.0) {
            variable_f0 = 0.07f;
        } else if (variable_f2 <= 4.0) {
            variable_f0 = 0.075f;
        } else {
            variable_f0 = 0.1f;
        }
    }
    paso_f32_hacia(parametro1, 0.0f, variable_f0);
}

void funcion_800892E0(s32 id_jugador) {
    funcion_80089020(id_jugador, &dato_8018CE10[id_jugador].desconocido_04[0]);
    funcion_80089020(id_jugador, &dato_8018CE10[id_jugador].desconocido_04[2]);
    if (dato_8018CE10[id_jugador].desconocido_18[6] > 0) {
        dato_8018CE10[id_jugador].desconocido_18[6]--;
    }
}
