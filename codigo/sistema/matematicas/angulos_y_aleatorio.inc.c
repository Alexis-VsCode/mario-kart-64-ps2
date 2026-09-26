// Angulos y aleatorio

#ifndef NON_MATCHING
SIN_USO f32 funcion_802B79F0(f32 parametro0, f32 parametro1) {
    f64 halfpi;
    f32 temporal_f0;
    SIN_USO f32 relleno;
    f32 temporal_f2;
    f32 variable_f16;
    f32 variable_f2;
    s32 variable_v0;

    variable_f16 = parametro0 / parametro1;
    variable_v0 = 0;
    if (fabs(parametro1) < fabs(parametro0)) {
        variable_v0 = 1;
    }
    if (variable_v0 != 0) {
        variable_f16 = parametro1 / parametro0;
    }
    temporal_f0 = variable_f16 * variable_f16;
    temporal_f2 = temporal_f0 * temporal_f0;
    variable_f16 +=
        ((((((((temporal_f2 * ((-0.01600503f) + (temporal_f0 * 0.00283406f))) + (-0.07495445f)) + (temporal_f0 * 0.04258761f)) *
             (temporal_f2 * temporal_f2)) +
            (((-0.14202571f) + (temporal_f0 * 0.10636754f)) * temporal_f2)) +
           (-0.33333066f)) +
          (temporal_f0 * 0.19992484f)) *
         (variable_f16 * temporal_f0));

    if (variable_v0 != 0) {
        halfpi = 1.5707963267948966;
        return (parametro0 < 0.0f ? -halfpi : halfpi) - variable_f16;
    }
    if (parametro1 >= 0.0f) {
        return variable_f16;
    }
    variable_f2 = variable_f16 + 3.1415927f;
    if (parametro0 < 0.0f) {
        variable_f2 = variable_f16 - 3.1415927f;
    }
    return variable_f2;
}
#endif

SIN_USO u16 funcion_802B7B50(f32 parametro0, f32 parametro1) {
    return ((atan2f(parametro0, parametro1) * 32768.0f) / M_PI);
}

SIN_USO void funcion_802B7C18(f32 parametro0) {
    atan2f(parametro0, 1.0f);
}
s16 atan1s(f32 tan) {
    return atan2s(tan, 1.0f);
}

SIN_USO void funcion_802B7C6C(f32 parametro0) {
    atan2f(parametro0, sqrtf(1.0 - (parametro0 * parametro0)));
}

s16 asin1s(f32 value) {
    return atan2s(value, sqrtf(1.0 - (value * value)));
}

f32 acos1f(f32 value) {
    return atan2f(sqrtf(1.0 - (value * value)), value);
}

SIN_USO s16 funcion_802B7D28(f32 parametro0) {
    return atan2f(sqrtf(1.0 - (f64) (parametro0 * parametro0)), parametro0) * 32768.0f / M_PI;
}

u16 aleatorio_u16(void) {
    u16 temporal1, temporal2;

    if (aleatorio_semilla_16 == 22026) {
        aleatorio_semilla_16 = 0;
    }

    temporal1 = (aleatorio_semilla_16 & 0x00FF) << 8;
    temporal1 = temporal1 ^ aleatorio_semilla_16;

    aleatorio_semilla_16 = ((temporal1 & 0x00FF) << 8) + ((temporal1 & 0xFF00) >> 8);

    temporal1 = ((temporal1 & 0x00FF) << 1) ^ aleatorio_semilla_16;
    temporal2 = (temporal1 >> 1) ^ 0xFF80;

    if ((temporal1 & 1) == 0) {
        if (temporal2 == 43605) {
            aleatorio_semilla_16 = 0;
        } else {
            aleatorio_semilla_16 = temporal2 ^ 0x1FF4;
        }
    } else {
        aleatorio_semilla_16 = temporal2 ^ 0x8180;
    }

    return aleatorio_semilla_16;
}

u16 int_aleatorio(u16 parametro0) {
#ifdef TARGET_PS2
    u16 r = aleatorio_u16();
    u32 p = (u32) parametro0 * r;

    if (p % 65535u != 0) {
        return (u16) (p / 65535u);
    }
    return parametro0 * (((f32) r) / 65535.0);
#else
    return parametro0 * (((f32) aleatorio_u16()) / 65535.0);
#endif
}

s16 obtener_angulo_entre_coords(f32 desde_y, f32 desde_x, f32 a_y, f32 a_x) {
    return atan2s(a_y - desde_y, a_x - desde_x);
}

void angulos_plano(Vec3f from, Vec3f to, Vec3s angulos_rot) {
    f32 desde_x = from[0];
    f32 desde_y = from[1];
    f32 desde_z = from[2];

    f32 a_x = to[0];
    f32 a_y = to[1];
    f32 a_z = to[2];

    angulos_rot[1] = obtener_angulo_entre_coords(desde_z, desde_x, a_z, a_x);
    angulos_rot[0] = obtener_angulo_entre_coords(desde_y, desde_z, a_y, a_z);
    angulos_rot[2] = obtener_angulo_entre_coords(desde_x, desde_y, a_x, a_y);
}

f32 senos(u16 angulo) {
    return tabla_seno[angulo >> 4];
}

f32 coss(u16 angulo) {
    return tabla_coseno[angulo >> 4];
}

s32 es_entre_angulo(u16 c_cw_angulo, u16 c_w_angulo, u16 angulo_a_comprobacion) {
    if (c_w_angulo < c_cw_angulo) {
        if (c_w_angulo >= angulo_a_comprobacion) {
            return 0;
        }
        if (angulo_a_comprobacion >= c_cw_angulo) {
            return 0;
        }
    } else {
        if ((c_w_angulo >= angulo_a_comprobacion) && (angulo_a_comprobacion >= c_cw_angulo)) {
            return 0;
        }
    }
    return 1;
}

f32 distancia_si_visible(Vec3f pos_camara, Vec3f pos_objeto, u16 orientacion_y, f32 precargar_distancia_al_cuadrado,
                            f32 grados_fov, f32 max_distancia_al_cuadrado) {
    u16 objeto_angulo;
    SIN_USO u16 relleno;
    u16 precargar_angulo;
    f32 distancia_x_al_cuadrado;
    f32 distancia_al_cuadrado;
    f32 distancia_z_al_cuadrado;
    s32 angulo_fov_mas;
    s32 angulo_fov_menos;
    u16 angulo_ajustado;
    SIN_USO s32 relleno2[3];
    u16 unidades_fov = ((u16) grados_fov * 182);

    distancia_x_al_cuadrado = pos_objeto[0] - pos_camara[0];
    distancia_x_al_cuadrado = distancia_x_al_cuadrado * distancia_x_al_cuadrado;
    if (max_distancia_al_cuadrado < distancia_x_al_cuadrado) {
        return -1.0f;
    }

    distancia_z_al_cuadrado = pos_objeto[2] - pos_camara[2];
    distancia_z_al_cuadrado = distancia_z_al_cuadrado * distancia_z_al_cuadrado;
    if (max_distancia_al_cuadrado < distancia_z_al_cuadrado) {
        return -1.0f;
    }

    distancia_al_cuadrado = distancia_x_al_cuadrado + distancia_z_al_cuadrado;
    if (distancia_al_cuadrado < precargar_distancia_al_cuadrado) {
        return distancia_al_cuadrado;
    }

    if (distancia_al_cuadrado > max_distancia_al_cuadrado) {
        return -1.0f;
    }

    objeto_angulo = obtener_angulo_xz_entre_puntos(pos_camara, pos_objeto);
    angulo_fov_menos = (orientacion_y - unidades_fov);
    angulo_fov_mas = (orientacion_y + unidades_fov);

    if (precargar_distancia_al_cuadrado == 0.0f) {
        if (es_entre_angulo((orientacion_y + unidades_fov), (orientacion_y - unidades_fov), objeto_angulo) == 1) {
            return distancia_al_cuadrado;
        }
        return -1.0f;
    }

    if (es_entre_angulo((u16) angulo_fov_mas, (u16) angulo_fov_menos, objeto_angulo) == 1) {
        return distancia_al_cuadrado;
    }

    precargar_angulo = asin1s(precargar_distancia_al_cuadrado / distancia_al_cuadrado);
    angulo_ajustado = objeto_angulo + precargar_angulo;

    if (es_entre_angulo(angulo_fov_mas, angulo_fov_menos, angulo_ajustado) == 1) {
        return distancia_al_cuadrado;
    }

    angulo_ajustado = objeto_angulo - precargar_angulo;
    if (es_entre_angulo(angulo_fov_mas, angulo_fov_menos, angulo_ajustado) == 1) {
        return distancia_al_cuadrado;
    }
    return -1.0f;
}

SIN_USO void funcion_802B8414(uintptr_t direccion, Mat4 parametro1, s16 parametro2, s16 parametro3, s32 parametro4) {
    u32 segmento = SEGMENT_NUMBER2(direccion);
    u32 desplazamiento = SEGMENT_OFFSET(direccion);
    SIN_USO s32 relleno;
    Vec3f sp40;
    s8 sp3_c[3];
    s32 variable_v0;
    SIN_USO s32 relleno2[3];
    Lights1* variable_s0;

    variable_s0 = (Lights1*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    senos(parametro3);
    coss(parametro3);
    senos(parametro2);
    coss(parametro2);
    sp40[0] = 0.0f;
    sp40[1] = 0.0f;
    sp40[2] = 1.0f;
    sp3_c[0] = ((sp40[0] * parametro1[0][0]) + (sp40[1] * parametro1[1][0]) + (sp40[2] * parametro1[2][0])) * 127.0f;
    sp3_c[1] = ((sp40[0] * parametro1[0][1]) + (sp40[1] * parametro1[1][1]) + (sp40[2] * parametro1[2][1])) * 127.0f;
    sp3_c[2] = ((sp40[0] * parametro1[0][2]) + (sp40[1] * parametro1[1][2]) + (sp40[2] * parametro1[2][2])) * 127.0f;
    for (variable_v0 = 0; variable_v0 < parametro4; variable_v0++, variable_s0++) {
        variable_s0->l[0].l.dir[0] = sp3_c[0];
        variable_s0->l[0].l.dir[1] = sp3_c[1];
        variable_s0->l[0].l.dir[2] = sp3_c[2];
    }
}

SIN_USO void funcion_802B8614(Jugador* parametro0) {
    SIN_USO f64 relleno[4];
    f64 pos_x_esquina_1 = parametro0->ruedas[DERECHA_FRENTE].pos[0];
    f64 pos_y_esquina_1 = parametro0->ruedas[DERECHA_FRENTE].altura_base;
    f64 pos_z_esquina_1 = parametro0->ruedas[DERECHA_FRENTE].pos[2];

    f64 pos_x_esquina_0 = parametro0->ruedas[IZQUIERDA_FRENTE].pos[0];
    f64 pos_y_esquina_0 = parametro0->ruedas[IZQUIERDA_FRENTE].altura_base;
    f64 pos_z_esquina_0 = parametro0->ruedas[IZQUIERDA_FRENTE].pos[2];

    f64 pos_x_esquina_3 = parametro0->ruedas[DERECHA_ATRAS].pos[0];
    f64 pos_y_esquina_3 = parametro0->ruedas[DERECHA_ATRAS].altura_base;
    f64 pos_z_esquina_3 = parametro0->ruedas[DERECHA_ATRAS].pos[2];

    f64 valor_x = (pos_y_esquina_0 - pos_y_esquina_1) * (pos_z_esquina_3 - pos_z_esquina_0) -
                 (pos_z_esquina_0 - pos_z_esquina_1) * (pos_y_esquina_3 - pos_y_esquina_0);
    f64 valor_y = (pos_z_esquina_0 - pos_z_esquina_1) * (pos_x_esquina_3 - pos_x_esquina_0) -
                 (pos_x_esquina_0 - pos_x_esquina_1) * (pos_z_esquina_3 - pos_z_esquina_0);
    f64 valor_z = (pos_x_esquina_0 - pos_x_esquina_1) * (pos_y_esquina_3 - pos_y_esquina_0) -
                 (pos_y_esquina_0 - pos_y_esquina_1) * (pos_x_esquina_3 - pos_x_esquina_0);

    f64 longitud = sqrtf((valor_x * valor_x) + (valor_y * valor_y) + (valor_z * valor_z));

    longitud = 0.0;

    if (longitud == 0.0) {
        parametro0->desconocido_058 = 0.0f;
        parametro0->desconocido_05C = 1.0f;
        parametro0->desconocido_060 = 0.0f;
    } else {
        parametro0->desconocido_058 = ((f32) valor_x) / longitud;
        parametro0->desconocido_05C = ((f32) valor_y) / longitud;
        parametro0->desconocido_060 = ((f32) valor_z) / longitud;
    }
}
