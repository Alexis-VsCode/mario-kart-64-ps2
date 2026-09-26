// Splines y vectores

f32 dato_802856B0 = 98.0f;
f32 dato_802856B4 = 12.0f;
f32 ordenado_tamanio_deslizando_bordes = 52.0f;
f32 dato_802856BC = 52.0f;
f32 bordes_deslizando_tamanio = 0.0f;
s32 dato_802856C4 = 0;

s32 dato_802856C8[3] = { 0 };

s16 disparo_cinematica;
s16 temporizador_disparo_cinematica;
s32 dato_802876D4;
s32 dato_802876D8;
s32 dato_802876DC;

CamaraCinematica dato_802876E0;
struct struct_80283431 dato_80287750[10];
struct struct_80283430 dato_80287818[32];
struct struct_80283430 dato_80287998[32];
f32 cinematica_spline_segmento_progreso;
s16 segmento_spline_cinematica;
s16 dato_80287B1E;
s8 dato_80287B20;

void fijar_duplicado_vec3f(Vec3f dest, f32 parametro1, f32 parametro2, f32 parametro3) {
    dest[0] = parametro1;
    dest[1] = parametro2;
    dest[2] = parametro3;
}

void fijar_duplicado_vec3s(Vec3s dest, s16 parametro1, s16 parametro2, s16 parametro3) {
    dest[0] = parametro1;
    dest[1] = parametro2;
    dest[2] = parametro3;
}

void borrar_vec3f(Vec3f parametro0) {
    parametro0[0] = parametro0[1] = parametro0[2] = 0.0f;
}

void borrar_vec3s(Vec3s parametro0) {
    parametro0[0] = parametro0[1] = parametro0[2] = 0;
}

void copiar_duplicado_retorno_vec3f(Vec3f dest, Vec3f orig_) {
    dest[0] = orig_[0];
    dest[1] = orig_[1];
    dest[2] = orig_[2];
}

void copiar_duplicado_vec3s(Vec3s dest, Vec3s orig_) {
    dest[0] = orig_[0];
    dest[1] = orig_[1];
    dest[2] = orig_[2];
}

void funcion_80282040(void) {
}

void funcion_80282048(void) {
}

SIN_USO void rotar_eje_y_vec3f(Vec3f dest, Vec3f orig_, s16 angulo) {
    Vec3f sp2_c;

    copiar_duplicado_retorno_vec3f(sp2_c, orig_);
    dest[0] = (sp2_c[2] * senos(angulo)) + (sp2_c[0] * coss(angulo));
    dest[1] = sp2_c[1];
    dest[2] = (sp2_c[2] * coss(angulo)) - (sp2_c[0] * senos(angulo));
}

SIN_USO void rotar_vec3f_x(Vec3f dest, Vec3f orig_, s16 angulo) {
    Vec3f sp2_c;

    copiar_duplicado_retorno_vec3f(sp2_c, orig_);
    dest[2] = (sp2_c[2] * coss(angulo)) - (sp2_c[1] * senos(angulo));
    dest[1] = (sp2_c[2] * senos(angulo)) + (sp2_c[1] * coss(angulo));
    dest[0] = sp2_c[0];
}

s32 interpolacion_f32(f32* dest, f32 orig_, f32 lerp) {
    if (lerp > 1.0f) {
        lerp = 1.0f;
    }

    *dest = *dest + ((orig_ - *dest) * lerp);

    if (orig_ == *dest) {
        return 0;
    }
    return 1;
}

SIN_USO bool suavizar_transicion_salida(s16* variable_, s16 dest, s16 factor_rapidez) {
    s16 temporal_v0 = *variable_;

    if (factor_rapidez == 0) {
        *variable_ = dest;
    } else {
        temporal_v0 -= dest;
        temporal_v0 -= (temporal_v0 / factor_rapidez);
        temporal_v0 += dest;
        *variable_ = temporal_v0;
    }

    if (dest == *variable_) {
        return false;
    }
    return true;
}

bool ajustar_transicion_valor_f32(f32* variable_, f32 dest, f32 factor_rapidez) {
    f32 temporal_f0 = dest - *variable_;

    if (factor_rapidez < 0.0f) {
        factor_rapidez = -1.0f * factor_rapidez;
    }

    if (temporal_f0 > 0.0f) {
        temporal_f0 -= factor_rapidez;
        if (temporal_f0 > 0.0f) {
            *variable_ = dest - temporal_f0;
        } else {
            *variable_ = dest;
        }
    } else {
        temporal_f0 += factor_rapidez;
        if (temporal_f0 < 0.0f) {
            *variable_ = dest - temporal_f0;
        } else {
            *variable_ = dest;
        }
    }

    if (dest == *variable_) {
        return false;
    }
    return true;
}

bool ajustar_transicion_valor_s16(s16* variable_, s16 meta_, s16 factor_rapidez) {
    s16 temporal_v0 = meta_ - *variable_;

    if (factor_rapidez < 0) {
        factor_rapidez = factor_rapidez * -1;
    }
    if (temporal_v0 > 0) {
        temporal_v0 -= factor_rapidez;
        if (temporal_v0 >= 0) {
            *variable_ = meta_ - temporal_v0;
        } else {
            *variable_ = meta_;
        }
    } else {
        temporal_v0 += factor_rapidez;
        if (temporal_v0 <= 0) {
            *variable_ = meta_ - temporal_v0;
        } else {
            *variable_ = meta_;
        }
    }

    if (meta_ == *variable_) {
        return false;
    }
    return true;
}

void reiniciar_spline(void) {
    segmento_spline_cinematica = 0;
    cinematica_spline_segmento_progreso = 0.0f;
    dato_80287B1E = 0;
    dato_80287B20 = 0;
}

void reiniciar_envoltura_spline(SIN_USO CamaraCinematica* parametro0) {
    reiniciar_spline();
}

void calcular_angulo_y_distancia_y_angulo_y_a_xz(Vec3f vec1, Vec3f vec2, f32* distancia, s16* angulo_ya_xz, s16* angulo_y) {
    f32 xdist;
    f32 ydist;
    f32 zdist;

    xdist = vec2[0] - vec1[0];
    ydist = vec2[1] - vec1[1];
    zdist = vec2[2] - vec1[2];
    *distancia = sqrtf((xdist * xdist) + (ydist * ydist) + (zdist * zdist));
    *angulo_ya_xz = atan2s(ydist, sqrtf((xdist * xdist) + (zdist * zdist)));
    *angulo_y = atan2s(xdist, zdist);
}

void aplicar_angulo_y_distancia_y_angulo_y_a_xz(Vec3f vec1, Vec3f vec2, f32 coef, s16 angulo_ya_xz, s16 angulo_y) {
    vec2[0] = vec1[0] + (coef * coss(angulo_ya_xz) * senos(angulo_y));
    vec2[1] = vec1[1] + (coef * senos(angulo_ya_xz));
    vec2[2] = vec1[2] + (coef * coss(angulo_ya_xz) * coss(angulo_y));
}

SIN_USO void funcion_cinematica_aborting(Vec3f parametro0, Vec3f parametro1, Vec3f parametro2, Vec3s parametro3) {
    Vec3f sp3_c;
    Vec3f sp30;

    copiar_duplicado_retorno_vec3f(sp3_c, parametro1);
    sp30[2] = -((parametro2[2] * coss(parametro3[0])) - (parametro2[1] * senos(parametro3[0])));
    sp30[1] = (parametro2[2] * senos(parametro3[0])) + (parametro2[1] * coss(parametro3[0]));
    sp30[0] = parametro2[0];
    parametro0[0] = parametro1[0] + (sp30[2] * senos(parametro3[1])) + (sp30[0] * coss(parametro3[1]));
    parametro0[1] = parametro1[1] + sp30[1];
    parametro0[2] = parametro1[2] + (sp30[2] * coss(parametro3[1])) - (sp30[0] * senos(parametro3[1]));
}

void evaluar_spline_cubico(f32 parametro0, Vec3f punto, f32* parametro2, f32 puntos_control_1[], f32 puntos_control_2[],
                           f32 puntos_control_3[], f32 puntos_control_4[]) {
    f32 B[4];

    if (parametro0 > 1.0f) {
        parametro0 = 1.0f;
    }
    B[0] = (((1.0f - parametro0) * (1.0f - parametro0)) * (1.0f - parametro0)) / 6.0f;
    B[1] = ((((parametro0 * parametro0) * parametro0) / 2.0f) - (parametro0 * parametro0)) + 0.6666667f;
    B[2] = ((((((-parametro0) * parametro0) * parametro0) / 2.0f) + ((parametro0 * parametro0) / 2.0f)) + (parametro0 / 2.0f)) + 0.16666667f;
    B[3] = ((parametro0 * parametro0) * parametro0) / 6.0f;

    punto[0] =
        B[0] * puntos_control_1[0] + B[1] * puntos_control_2[0] + B[2] * puntos_control_3[0] + B[3] * puntos_control_4[0];
    punto[1] =
        B[0] * puntos_control_1[1] + B[1] * puntos_control_2[1] + B[2] * puntos_control_3[1] + B[3] * puntos_control_4[1];
    punto[2] =
        B[0] * puntos_control_1[2] + B[1] * puntos_control_2[2] + B[2] * puntos_control_3[2] + B[3] * puntos_control_4[2];
    *parametro2 = B[0] * puntos_control_1[3] + B[1] * puntos_control_2[3] + B[2] * puntos_control_3[3] + B[3] * puntos_control_4[3];
}

s32 mover_punto_junto_spline(Vec3f punto, f32* parametro1, struct struct_80283430 spline[], s16* segmento_spline,
                            f32* progreso) {
    s32 terminado = 0;
    Mat4 puntos_control;
    s32 i = 0;
    f32 u = *progreso;
    f32 cambio_progreso;
    f32 primer_rapidez = 0;
    f32 segundo_rapidez = 0;
    s32 segmento = *segmento_spline;

    if (*segmento_spline < 0) {
        u = 0;
    }

    if ((spline[segmento].desconocido0 == -1) || (spline[segmento + 1].desconocido0 == -1) || (spline[segmento + 2].desconocido0 == -1)) {
        return 1;
    }

    for (i = 0; i < 4; i++) {
        puntos_control[i][0] = spline[segmento + i].desconocido6[0];
        puntos_control[i][1] = spline[segmento + i].desconocido6[1];
        puntos_control[i][2] = spline[segmento + i].desconocido6[2];
        puntos_control[i][3] = spline[segmento + i].desconocido4 * 256.0f;
    }

    evaluar_spline_cubico(u, punto, parametro1, puntos_control[0], puntos_control[1], puntos_control[2], puntos_control[3]);

    if (spline[*segmento_spline + 1].desconocido2 != 0) {
        primer_rapidez = 1.0f / spline[*segmento_spline + 1].desconocido2;
    }

    if (spline[*segmento_spline + 2].desconocido2 != 0) {
        segundo_rapidez = 1.0f / spline[*segmento_spline + 2].desconocido2;
    }

#ifdef VERSION_EU
    if (estado_juego == SECUENCIA_CREDITOS) {
        primer_rapidez *= 1.14999997f;
        segundo_rapidez *= 1.14999997f;
    }
#endif

    cambio_progreso = (((segundo_rapidez - primer_rapidez)) * *progreso + primer_rapidez);
    if (1 <= (*progreso += cambio_progreso)) {
        (*segmento_spline)++;
        if (spline[*segmento_spline + 3].desconocido0 == -1) {
            *segmento_spline = 0;
            terminado = 1;
        }
        (*progreso)--;
    }
    return terminado;
}

void funcion_80282BE4(struct struct_80283430* parametro0, s8 parametro1, u8 parametro2, s8 parametro3, Vec3s parametro4, s32 parametro5) {
    parametro0->desconocido0 = parametro1;
    parametro0->desconocido2 = parametro2;
    parametro0->desconocido4 = parametro3;
    if (parametro5) {
        parametro0->desconocido6[0] = -parametro4[0];
    } else {
        parametro0->desconocido6[0] = parametro4[0];
    }
    parametro0->desconocido6[1] = parametro4[1];
    parametro0->desconocido6[2] = parametro4[2];
}

void funcion_80282C40(struct struct_80283430* parametro0, struct struct_80282C40* parametro1, s32 parametro2) {
    s32 i = 0;
    s32 j = 0;
    funcion_80282BE4(&parametro0[j], parametro1[j].desconocido0, parametro1[j].desconocido3, parametro1[j].desconocido4, parametro1[j].desconocido6, parametro2);

    j++;
    goto etiqueta_ficticio_888430;
    while (true) {
        do {

        etiqueta_ficticio_888430:;
            funcion_80282BE4(&parametro0[j], parametro1[i].desconocido0, parametro1[i].desconocido3, parametro1[i].desconocido4, parametro1[i].desconocido6, parametro2);
            j++;
            i++;

        } while (parametro1[i].desconocido0 != -1);
        if (j + 3 <= 30) {
            funcion_80282BE4(&parametro0[j], parametro1->desconocido0, parametro1[i].desconocido3, parametro1[i].desconocido4, parametro1[i].desconocido6, parametro2);
            funcion_80282BE4(&parametro0[j + 1], parametro1->desconocido0, 0, parametro1[i].desconocido4, parametro1[i].desconocido6, parametro2);
            funcion_80282BE4(&parametro0[j + 2], parametro1->desconocido0, 0, parametro1[i].desconocido4, parametro1[i].desconocido6, parametro2);
            funcion_80282BE4(&parametro0[j + 3], -1, 0, parametro1[i].desconocido4, parametro1[i].desconocido6, parametro2);
            break;
        }
    }
}

s32 mover_camara_cinematica_junto_spline(CamaraCinematica* camara, struct struct_80286A04* parametro1,
                                       struct struct_80286A04* parametro2, s32 parametro3) {
    s32 res;

    evento_cinematica(reiniciar_envoltura_spline, camara, 0, 0);
    funcion_80282C40(dato_80287818, (struct struct_80282C40*) parametro1, parametro3);
    funcion_80282C40(dato_80287998, (struct struct_80282C40*) parametro2, parametro3);

    if (0) {};

    res = mover_punto_junto_spline(camara->mirar_a, &camara->unk18, dato_80287818, &segmento_spline_cinematica,
                                  &cinematica_spline_segmento_progreso) |
          mover_punto_junto_spline(camara->pos, &camara->unk18, dato_80287998, &segmento_spline_cinematica,
                                  &cinematica_spline_segmento_progreso);
    return res;
}

void funcion_80282E58(CamaraCinematica* camara, struct struct_80282C40* parametro1, s32 parametro2) {
    funcion_80282C40(dato_80287818, parametro1, parametro2);
    mover_punto_junto_spline(camara->mirar_a, &camara->unk18, dato_80287818, &segmento_spline_cinematica,
                            &cinematica_spline_segmento_progreso);
}

void funcion_80282EAC(s32 parametro0, CamaraCinematica* parametro1, s16 parametro2, s16 parametro3, s16 parametro4) {
    if ((parametro0 >= 0) && (parametro0 < 3)) {
        if (parametro1->desconocido48[parametro0] < parametro2) {
            parametro1->desconocido48[parametro0] = parametro2;
            parametro1->desconocido_5a[parametro0] = parametro3;
            parametro1->desconocido54[parametro0] = parametro4;
        }
    }
}

void funcion_80282F00(s16* parametro0, s16 parametro1) {
    if (parametro1 == -0x8000) {
        *parametro0 = (*parametro0 & 0x8000) + 0xC000;
        return;
    }
    *parametro0 += parametro1;
}

void funcion_80282F44(s32 parametro0, CamaraCinematica* parametro1, Camara* camara) {
    f32 distancia;
    SIN_USO s32 relleno[2];
    s16 cam_angulo[2];
    Vec3f pos;
    Vec3f mirada;

    fijar_duplicado_vec3f(pos, camara->pos[0], camara->pos[1], camara->pos[2]);
    fijar_duplicado_vec3f(mirada, camara->mirar_a[0], camara->mirar_a[1], camara->mirar_a[2]);
    if ((parametro0 == 0) || (parametro0 == 1)) {
        if ((parametro1->desconocido48[0] != 0) || (parametro1->desconocido48[1] != 0)) {
            calcular_angulo_y_distancia_y_angulo_y_a_xz(pos, mirada, &distancia, &cam_angulo[0], &cam_angulo[1]);
            cam_angulo[parametro0] += (((f32) parametro1->desconocido48[parametro0]) * senos(parametro1->desconocido_4e[parametro0]));
            if ((cam_angulo[0] < 0x3800) && (cam_angulo[0] >= -0x37FF)) {
                aplicar_angulo_y_distancia_y_angulo_y_a_xz(pos, mirada, distancia, cam_angulo[0], cam_angulo[1]);
            }
            funcion_80282F00(&parametro1->desconocido_4e[parametro0], parametro1->desconocido54[parametro0]);
            if (ajustar_transicion_valor_s16(&parametro1->desconocido48[parametro0], 0, parametro1->desconocido_5a[parametro0]) == false) {
                parametro1->desconocido_4e[parametro0] = 0;
            }
        }
        camara->mirar_a[0] = mirada[0];
        camara->mirar_a[1] = mirada[1];
        camara->mirar_a[2] = mirada[2];
    }
}

void funcion_802830B4(CamaraCinematica* parametro0, s16 parametro1, s16 parametro2, s16 parametro3) {
    if (parametro0->unk60 < parametro1) {
        parametro0->unk60 = parametro1;
        parametro0->desconocido_6c = parametro2;
        parametro0->desconocido68 = parametro3;
    }
}

void funcion_80283100(CamaraCinematica* parametro0, f32* parametro1) {
    if (parametro0->unk60 != 0) {
        parametro0->desconocido_6e = (coss((u16) parametro0->desconocido64) * parametro0->unk60) / 256;
        parametro0->desconocido64 += parametro0->desconocido68;
        ajustar_transicion_valor_s16(&parametro0->unk60, 0, parametro0->desconocido_6c);
    } else {
        parametro0->desconocido64 = 0.0f;
    }
    *parametro1 = parametro0->unk20 + (f32) parametro0->desconocido_6e;
}

void funcion_80283240(s16 parametro0) {
    if (parametro0 == 1) {
        funcion_80282EAC(0, &dato_802876E0, 0x100, 0x10, 0x4000);
        funcion_80282EAC(1, &dato_802876E0, 0x80, 0x20, 0x2000);
        funcion_802830B4(&dato_802876E0, 0x300, 0x20, 0x4000);
    }
}

s32 evento_cinematica(EventoCamara event, CamaraCinematica* camara, s16 empezar, s16 end) {
    if (temporizador_disparo_cinematica >= empezar) {
        if ((end == -1) || (end >= temporizador_disparo_cinematica)) {
            event(camara);
        }
    }
    return 0;
}

s32 funcion_80283330(s32 parametro0) {
    if (parametro0 != dato_802876D8) {
        dato_802876D8 = parametro0;
        disparo_cinematica = 0;
        temporizador_disparo_cinematica = 0;
        dato_802876D4 = 0;
    }
    return dato_802876D8;
}

extern s32 dato_802876D8;

s32 funcion_8028336C(SIN_USO CamaraCinematica* parametro0, SIN_USO Camara* camara) {
    u8 sp20[] = { 2, 3, 4, 5, 5, 5, 5, 5 };
    if (dato_802876D8 != 0) {
        return dato_802876D8;
    }
    switch (estado_juego) {
        case FINAL:
            dato_802876D8 = sp20[dato_802874D8.desconocido_1d];
            break;

        case SECUENCIA_CREDITOS:
            dato_802876D8 = 6;
            break;
    }

    if (estado_juego == SECUENCIA_CREDITOS) {
        funcion_80283330(6);
    }
    return dato_802876D8;
}

s32 stub_cinematica(void) {
    return 0;
}

void inicializar_camara_cinematica(void) {
    s32 i;
    CamaraCinematica* camara = &dato_802876E0;

    dato_802876D8 = 0;
    camara->cinematica = 0;
    dato_802856C4 = (s32) dato_800DC5E4;
    borrar_vec3f(camara->mirar_a);
    fijar_duplicado_vec3f(camara->pos, 0.0f, 0.0f, 500.0f);
    borrar_vec3f(camara->desconocido30);
    fijar_duplicado_vec3f(camara->unk24, 0.0f, 0.0f, 500.0f);
    fijar_duplicado_vec3f(camara->desconocido_3c, 0.0f, 1.0f, 0.0f);
    camara->unk18 = 0.0f;
    borrar_vec3s(camara->desconocido48);
    borrar_vec3s(camara->desconocido_4e);
    borrar_vec3s(camara->desconocido54);
    borrar_vec3s(camara->desconocido_5a);
    camara->unk60 = 0;
    camara->desconocido64 = 0.0f;
    camara->desconocido68 = 0.0f;
    camara->desconocido_6c = 0;
    camara->desconocido_6e = 0;
    camara->unk20 = acercar_camara[0];
    disparo_cinematica = 0;
    temporizador_disparo_cinematica = 0;
    dato_802876D4 = 0;
    reiniciar_spline();

    for (i = 0; i < 32; i++) {
        dato_80287818[i].desconocido0 = -1;
        dato_80287998[i].desconocido0 = -1;
    }

    for (i = 0; i < 10; i++) {
        borrar_vec3f(dato_80287750[i].desconocido0);
        borrar_vec3s(dato_80287750[i].desconocido_c);
    }

    bordes_deslizando_tamanio = 0.0f;

    if (estado_juego == FINAL) {
        dato_802856B0 = 120.0f;
        dato_802856B4 = 12.0f;
        ordenado_tamanio_deslizando_bordes = 120.0f;
    } else {
        dato_802856B0 = 98.0f;
        dato_802856B4 = 12.0f;
        ordenado_tamanio_deslizando_bordes = 52.0f;
    }
}

s32 funcion_80283648(Camara* camara) {
    s16 angulo_ya_xz;
    s16 angulo_y;
    f32 variable_f2;
    f32 distancia;
    Vec3f pos;
    Vec3f mirar_a;
    Vec3f arriba;
    CamaraCinematica* camara_cinematica = &dato_802876E0;

    stub_cinematica();
    copiar_duplicado_retorno_vec3f(pos, camara->pos);
    copiar_duplicado_retorno_vec3f(mirar_a, camara->mirar_a);
    copiar_duplicado_retorno_vec3f(arriba, camara->arriba);
    camara_cinematica->cinematica = funcion_8028336C(camara_cinematica, camara);
    if (camara_cinematica->cinematica != 0) {
        copiar_duplicado_retorno_vec3f(camara_cinematica->mirar_a, camara->pos);
        copiar_duplicado_retorno_vec3f(camara_cinematica->pos, camara->mirar_a);
        reproducir_cinematica(camara_cinematica);
        calcular_angulo_y_distancia_y_angulo_y_a_xz(camara_cinematica->mirar_a, camara_cinematica->pos, &distancia,
                                                     &angulo_ya_xz, &angulo_y);
        if (angulo_ya_xz >= 0x3800) {
            angulo_ya_xz = 0x3800;
        }
        if (angulo_ya_xz < -0x37FF) {
            angulo_ya_xz = -0x3800;
        }
        if ((angulo_ya_xz == 0x3800) || (angulo_ya_xz == -0x3800)) {
            aplicar_angulo_y_distancia_y_angulo_y_a_xz(camara_cinematica->mirar_a, camara_cinematica->pos, distancia,
                                                     angulo_ya_xz, angulo_y);
        }
        if (camara_cinematica->unk18 > 65536.0f) {
            camara_cinematica->unk18 -= 65536.0f;
        }
        if (camara_cinematica->unk18 < -65536.0f) {
            camara_cinematica->unk18 += 65536.0f;
        }
        if (1) {
            variable_f2 = camara_cinematica->unk18;
        }
        if (variable_f2 < 0.0f) {
            variable_f2 = 65536.0f + variable_f2;
        }
        camara->arriba[0] = senos(variable_f2) * coss(angulo_y);
        camara->arriba[1] = coss(variable_f2);
        camara->arriba[2] = -senos(variable_f2) * senos(angulo_y);
        copiar_duplicado_retorno_vec3f(camara->pos, camara_cinematica->mirar_a);
        copiar_duplicado_retorno_vec3f(camara->mirar_a, camara_cinematica->pos);
        if ((estado_juego == SECUENCIA_CREDITOS) && (es_modo_espejo != 0)) {
            camara->pos[0] = -camara->pos[0];
            camara->mirar_a[0] = -camara->mirar_a[0];
        }
    }
    funcion_80282F44(0, camara_cinematica, camara);
    funcion_80282F44(1, camara_cinematica, camara);
    funcion_80283100(camara_cinematica, acercar_camara);
    copiar_duplicado_retorno_vec3f(camara_cinematica->desconocido30, camara->pos);
    copiar_duplicado_retorno_vec3f(camara_cinematica->unk24, camara->mirar_a);
    copiar_duplicado_retorno_vec3f(camara_cinematica->desconocido_3c, camara->arriba);
    return dato_802876D8;
}

void envoltura_func_8028100C(SIN_USO CamaraCinematica* camara) {
    funcion_8028100C(-0xC6C, 0xD2, -0x1EF);
}

void envoltura_func_80280FFC(SIN_USO CamaraCinematica* camara) {
    funcion_80280FFC();
}

void animacion_aparece_deslizando_bordes(SIN_USO CamaraCinematica* camara) {
    ordenado_tamanio_deslizando_bordes = 52.0f;
}

void animacion_desaparece_deslizando_bordes(SIN_USO CamaraCinematica* camara) {
    ordenado_tamanio_deslizando_bordes = 0.0f;
}

void envoltura_func_80092C80(SIN_USO CamaraCinematica* camara) {
    funcion_80092C80();
}

void reproducir_bienvenida_sonido(SIN_USO CamaraCinematica* camara) {
    if (dato_800DC5E4 == 0) {
        reproducir_sonido2(SONIDO_BIENVENIDA_INTRO);
    }
}

void envoltura_func_800CA0CC(SIN_USO CamaraCinematica* camara) {
    funcion_800CA0CC();
}

void reproducir_felicitacion_sonido(SIN_USO CamaraCinematica* camara) {
    reproducir_sonido2(SONIDO_FELICITACION_CEREMONIA);
}

void sacar_globo_sonido_juego(SIN_USO CamaraCinematica* camara) {
    reproducir_sonido2(SONIDO_SACAR_GLOBO_CEREMONIA);
}

void reproducir_pez_sonido(SIN_USO CamaraCinematica* camara) {
    reproducir_sonido2(SONIDO_PEZ_CEREMONIA);
}

void reproducir_pez_sonido_2(SIN_USO CamaraCinematica* camara) {
    reproducir_sonido2(SONIDO_PEZ_CEREMONIA_2);
}

void reproducir_trofeo_disparo_sonido(SIN_USO CamaraCinematica* camara) {
    reproducir_sonido2(SONIDO_TROFEO_DISPARO_CEREMONIA);
}

void reproducir_podio_sonido(SIN_USO CamaraCinematica* camara) {
    reproducir_sonido2(SONIDO_PODIO_CEREMONIA);
}

void reproducir_trofeo_sonido(SIN_USO CamaraCinematica* camara) {
    reproducir_sonido2(SONIDO_TROFEO_CEREMONIA);
}

void funcion_80283B6C(SIN_USO CamaraCinematica* camara) {
    funcion_800CA0B8();
    funcion_800C9060(0, SONIDO_EXPLOSION_ACCION);
    funcion_800CA0A0();
}

void funcion_80283BA4(SIN_USO CamaraCinematica* camara) {
    funcion_800CA0B8();
    funcion_800C90F4(0, (jugador_cuatro->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x04));
    funcion_800CA0A0();
}

void reproducir_ganador_ceremonia_secuencia_parte1(SIN_USO CamaraCinematica* camara) {
    reproducir_secuencia2(SEC_EVENTO_CEREMONIA_PRESENTACION_PART1);
}

void reproducir_ganador_ceremonia_secuencia_parte2(SIN_USO CamaraCinematica* camara) {
    reproducir_secuencia2(SEC_EVENTO_CEREMONIA_PRESENTACION_PART2_VICTORIA);
}

void envoltura_func_800CB134(SIN_USO CamaraCinematica* camara) {
    funcion_800CB134();
}

void reproducir_secuencia_ceremonia_perdiendo(SIN_USO CamaraCinematica* camara) {
    empezar_secuencia_ceremonia_perdiendo();
}

void reproducir_ganador_ceremonia_creditos_secuencia(SIN_USO CamaraCinematica* parametro0) {
    if (dato_800DC5E4 == 0) {
        reproducir_secuencia2(SEC_EVENTO_CEREMONIA_TROFEO_CREDITOS);
    }
}

void funcion_80283CA8(SIN_USO CamaraCinematica* camara) {
    funcion_800CA008(0, 3);
}

void funcion_80283CD0(SIN_USO CamaraCinematica* camara) {
    if (dato_800DC5E4 == 0) {
        funcion_800CA008(0, 2);
    }
}

void reproducir_despedida_sonido(SIN_USO CamaraCinematica* parametro0) {
    reproducir_sonido2(SONIDO_DESPEDIDA_CREDITOS);
}

struct struct_80282C40 dato_802856DC[] = {
    { 0, 0, 0, 0, 0, 0, { 0xF576, 0x014E, 0xFE70 } },  { 0, 0, 0, 0, 0, 0, { 0xF576, 0x014E, 0xFE70 } },
    { 0, 0, 0, 0, 0, 0, { 0xF422, 0x0103, 0xFE3C } },  { 0, 0, 0, 0, 0, 0, { 0xF3E8, 0x0016, 0xFE34 } },
    { -1, 0, 0, 0, 0, 0, { 0xF3E8, 0x0016, 0xFE34 } },
};

struct struct_80282C40 dato_80285718[] = {
    { 0, 0, 0, 61, 0, 0, { 0xF493, 0x0309, 0xFE4E } },  { 0, 0, 0, 149, 0, 0, { 0xF494, 0x030A, 0xFE4E } },
    { 0, 0, 0, 94, 0, 0, { 0xF243, 0x0179, 0xFDF0 } },  { 0, 0, 0, 60, 0, 0, { 0xF213, 0x00B1, 0xFDE9 } },
    { -1, 0, 0, 60, 0, 0, { 0xF213, 0x008D, 0xFDE9 } },
};

struct struct_80282C40 dato_80285754[] = {
    { 0, 0, 0, 0, 0, 0, { 0xF4F4, 0xFFE2, 0xFF67 } },
    { 0, 0, 0, 0, 0, 0, { 0xF51A, 0x0002, 0xFF5D } },
    { 0, 0, 0, 0, 0, 0, { 0xF57B, 0x004A, 0xFFB8 } },
    { -1, 0, 0, 0, 0, 0, { 0xF608, 0x0065, 0xFFE4 } },
};

struct struct_80282C40 dato_80285784[] = {
    { 0, 0, 0, 186, 0, 0, { 0xF33E, 0x0009, 0x0053 } },
    { 0, 0, 0, 89, 0, 0, { 0xF329, 0xFFA4, 0xFF8F } },
    { 0, 0, 0, 60, 0, 0, { 0xF39C, 0x004F, 0xFF2A } },
    { -1, 0, 0, 45, 0, 0, { 0xF44A, 0x00BE, 0xFF16 } },
};

struct struct_80282C40 dato_802857B4[] = {
    { 0, 0, 0, 0, 0, 0, { 0xF22C, 0xFFF4, 0x0067 } },
    { -1, 0, 0, 0, 0, 0, { 0xF22C, 0xFFF4, 0x0067 } },
};

struct struct_80282C40 dato_802857CC[] = {
    { 0, 0, 0, 90, 0, 0, { 0xF3F8, 0xFFDB, 0xFC39 } },
    { 0, 0, 0, 90, 0, 0, { 0xF419, 0xFFF8, 0xFC3B } },
    { -1, 0, 0, 101, 0, 0, { 0xF454, 0x000E, 0xFBFF } },
};

struct struct_80282C40 dato_802857F0[] = {
    { 0, 0, 0, 0, 0, 0, { 0xF208, 0x004F, 0xFDC9 } }, { 0, 0, 0, 0, 0, 0, { 0xF20F, 0x004E, 0xFDCB } },
    { 0, 0, 0, 0, 0, 0, { 0xF23D, 0x0049, 0xFDDC } }, { 0, 0, 0, 0, 0, 0, { 0xF284, 0x0044, 0xFDEF } },
    { 0, 0, 0, 0, 0, 0, { 0xF2BE, 0x0041, 0xFDFA } }, { 0, 0, 0, 0, 0, 0, { 0xF2E5, 0x003E, 0xFE04 } },
    { 0, 0, 0, 0, 0, 0, { 0xF303, 0x0039, 0xFE0A } }, { -1, 0, 0, 0, 0, 0, { 0xF325, 0x0033, 0xFE11 } },
};

struct struct_80282C40 dato_80285850[] = {
    { 0, 0, 0, 30, 0, 0, { 0xF3D7, 0x0004, 0xFE77 } }, { 0, 0, 0, 30, 0, 0, { 0xF3E3, 0x000C, 0xFE6F } },
    { 0, 0, 0, 50, 0, 0, { 0xF421, 0x001E, 0xFE53 } }, { 0, 0, 0, 50, 0, 0, { 0xF468, 0x001C, 0xFE69 } },
    { 0, 0, 0, 30, 0, 0, { 0xF4A4, 0x0016, 0xFE68 } }, { 0, 0, 0, 30, 0, 0, { 0xF4C9, 0xFFFE, 0xFE70 } },
    { 0, 0, 0, 30, 0, 0, { 0xF4E3, 0xFFE1, 0xFE76 } }, { -1, 0, 0, 30, 0, 0, { 0xF505, 0xFFD1, 0xFE72 } },
};

struct struct_80282C40 dato_802858B0[] = {
    { 0, 0, 0, 0, 0, 0, { 0xF42B, 0x002D, 0xFE46 } },
    { -1, 0, 0, 0, 0, 0, { 0xF42B, 0x002D, 0xFE46 } },
};

struct struct_80282C40 dato_802858C8[] = {
    { 0, 0, 0, 30, 0, 0, { 0xF246, 0x0073, 0xFDE7 } },
    { -1, 0, 0, 30, 0, 0, { 0xF246, 0x0073, 0xFDE7 } },
};

struct struct_80282C40 dato_802858E0[] = {
    { 0, 0, 0, 0, 0, 0, { 0xF39F, 0x003C, 0xFE2F } },
    { -1, 0, 0, 0, 0, 0, { 0xF39F, 0x003C, 0xFE2F } },
};

struct struct_80282C40 dato_802858F8[] = {
    { 0, 0, 0, 1, 0, 0, { 0xF245, 0x0187, 0xFDA1 } },
    { -1, 0, 0, 1, 0, 0, { 0xF245, 0x0187, 0xFDA1 } },
};

struct struct_80282C40 dato_80285910[] = {
    { 0, 0, 0, 0, 0, 0, { 0xF4A0, 0x00B7, 0xFF6C } },
    { -1, 0, 0, 0, 0, 0, { 0xF4A0, 0x00B7, 0xFF6C } },
};

struct struct_80282C40 dato_80285928[] = {
    { 0, 0, 0, 6, 0, 0, { 0xF340, 0x0025, 0xFE28 } },
    { -1, 0, 0, 6, 0, 0, { 0xF340, 0x0025, 0xFE28 } },
};

struct struct_80282C40 dato_80285940[] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3C3, 0x006B, 0xFE1A } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3C3, 0x006B, 0xFE1A } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3C3, 0x006B, 0xFE1A } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3C3, 0x006B, 0xFE1A } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3C3, 0x006B, 0xFE1A } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3C3, 0x006B, 0xFE1A } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3C3, 0x006B, 0xFE1A } },
    { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3C3, 0x006B, 0xFE1A } },
    { 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, { 0xF203, 0xFF99, 0xFE62 } },
    { 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, { 0xF200, 0xFFA4, 0xFE6D } },
    { 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, { 0xF1DA, 0x01AF, 0xFE7F } },
    { 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, { 0xF1DA, 0x014B, 0xFE7F } },
    { 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, { 0xF1DA, 0x00E7, 0xFE7F } },
    { 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, { 0xF1E1, 0x0015, 0xFE7D } },
    { 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, { 0xF1E1, 0x000A, 0xFE71 } },
    { 0xFF, 0x00, 0x00, 0x1E, 0x00, 0x00, { 0xF1E0, 0x000C, 0xFE71 } },
};

void funcion_80283D2C(CamaraCinematica* camara) {
    ordenado_tamanio_deslizando_bordes = 120.0f;
    evento_cinematica(funcion_80283CA8, camara, 0, 0);
    evento_cinematica(envoltura_func_800CA0CC, camara, 1, 1);
    evento_cinematica(reproducir_ganador_ceremonia_secuencia_parte1, camara, 0, 0);
    evento_cinematica(sacar_globo_sonido_juego, camara, 45, 45);
    evento_cinematica(sacar_globo_sonido_juego, camara, 65, 65);
    evento_cinematica(sacar_globo_sonido_juego, camara, 70, 70);
    evento_cinematica(sacar_globo_sonido_juego, camara, 94, 94);
    evento_cinematica(sacar_globo_sonido_juego, camara, 110, 110);
    evento_cinematica(sacar_globo_sonido_juego, camara, 130, 130);
    evento_cinematica(sacar_globo_sonido_juego, camara, 152, 152);
    evento_cinematica(sacar_globo_sonido_juego, camara, 160, 160);
    evento_cinematica(envoltura_func_80280FFC, camara, escena_corte[0].duration - 60, escena_corte[0].duration - 60);
    mover_camara_cinematica_junto_spline(camara, (struct struct_80286A04*) dato_802856DC,
                                       (struct struct_80286A04*) dato_80285718, 0);
}

void funcion_80283EA0(CamaraCinematica* camara) {
    mover_camara_cinematica_junto_spline(camara, (struct struct_80286A04*) dato_80285754,
                                       (struct struct_80286A04*) dato_80285784, 0);
}

void copiar_jugador_dos_en_camara(CamaraCinematica* camara) {
    copiar_duplicado_retorno_vec3f(camara->pos, jugador_dos->pos);
}

void interpolar_jugador_dos_en_camara(CamaraCinematica* camara) {
    interpolacion_f32(&camara->pos[0], jugador_dos->pos[0], 0.12f);
    interpolacion_f32(&camara->pos[1], jugador_dos->pos[1], 0.12f);
    interpolacion_f32(&camara->pos[2], jugador_dos->pos[2], 0.12f);
}

void funcion_80283F6C(CamaraCinematica* camara) {
    evento_cinematica(copiar_jugador_dos_en_camara, camara, 0, 0);
    evento_cinematica(interpolar_jugador_dos_en_camara, camara, 0, -1);
    funcion_80282E58(camara, (struct struct_80282C40*) dato_802857B4, 0);
}

void copiar_jugador_tres_en_camara(CamaraCinematica* camara) {
    copiar_duplicado_retorno_vec3f(camara->pos, jugador_tres->pos);
}

void interpolar_jugador_tres_en_camara(CamaraCinematica* camara) {
    interpolacion_f32(&camara->pos[0], jugador_tres->pos[0], 0.12f);
    interpolacion_f32(&camara->pos[1], jugador_tres->pos[1], 0.12f);
    interpolacion_f32(&camara->pos[2], jugador_tres->pos[2], 0.12f);
}

void funcion_80284068(CamaraCinematica* camara) {
    evento_cinematica(copiar_jugador_tres_en_camara, camara, 0, 0);
    evento_cinematica(interpolar_jugador_tres_en_camara, camara, 0, -1);
    funcion_80282E58(camara, (struct struct_80282C40*) dato_802857CC, 0);
}

void funcion_802840C8(CamaraCinematica* camara) {
    evento_cinematica(reproducir_ganador_ceremonia_secuencia_parte2, camara, 5, 5);

    switch (dato_802876D8) {
        case 2:
            funcion_80283EA0(camara);
            break;
        case 3:
            funcion_80283F6C(camara);
            break;
        case 4:
            funcion_80284068(camara);
            break;
    }
}

void funcion_80284154(CamaraCinematica* camara) {
    mover_camara_cinematica_junto_spline(camara, (struct struct_80286A04*) dato_80285910,
                                       (struct struct_80286A04*) dato_80285928, 0);
}

void funcion_80284184(CamaraCinematica* camara) {
    f32 trofeo;
    trofeo = ((lista_objeto[lista_objeto_indice_1[3]].pos[1] - camara->mirar_a[1]) * 0.9f) + camara->mirar_a[1];
    interpolacion_f32(&camara->pos[1], trofeo, 0.5);
}

void funcion_802841E8(CamaraCinematica* camara) {
    funcion_80282E58(camara, (struct struct_80282C40*) dato_80285940, 0);
    fijar_duplicado_vec3f(camara->pos, -3202.0f, 90.0f, -478.0f);
}

void funcion_8028422C(CamaraCinematica* camara) {
    evento_cinematica(reproducir_trofeo_disparo_sonido, camara, 6, 6);
    evento_cinematica(reproducir_trofeo_sonido, camara, 30, 30);
    evento_cinematica(funcion_802841E8, camara, 0, 0);
    evento_cinematica(funcion_80284184, camara, 6, -1);
}

void funcion_802842A8(CamaraCinematica* camara) {
    mover_camara_cinematica_junto_spline(camara, (struct struct_80286A04*) dato_802858B0,
                                       (struct struct_80286A04*) dato_802858C8, 0);
}

void funcion_802842D8(CamaraCinematica* camara) {
    mover_camara_cinematica_junto_spline(camara, (struct struct_80286A04*) dato_802857F0,
                                       (struct struct_80286A04*) dato_80285850, 0);
}
