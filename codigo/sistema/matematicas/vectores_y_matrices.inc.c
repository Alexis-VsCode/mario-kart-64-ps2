// Vectores y matrices

#pragma intrinsic(sqrtf, fabs)

SIN_USO s32 dato_802B91C0[2] = { 13, 13 };
Vec3f dato_802B91C8 = { 0.0f, 0.0f, 0.0f };

SIN_USO s32 funcion_802B4F60(SIN_USO s32 parametro0, Vec3f parametro1, SIN_USO s32 parametro2, SIN_USO f32 parametro3, SIN_USO f32 parametro4) {
    Mat4 sp30;
    f32 sp2_c;
    f32 sp28;
    Vec3f sp1_c;
    copiar_retorno_vec3f(sp1_c, parametro1);
    sp28 = sp1_c[0];
    sp2_c = sp1_c[1];
    if (sp2_c && sp2_c) {};
    sp2_c = ((sp30[0][3] * sp28) + (sp30[1][3] * sp2_c) + (sp30[2][3] * sp1_c[2])) + sp30[3][3];
    if (sp28 && sp28) {};
    transformar_mat4_vec3f_mtxf(sp1_c, sp30);
    if (0.0f >= sp2_c) {
        return 0;
    } else {
        return 1;
    }
}

SIN_USO void funcion_802B4FF0() {
}

s32 fijar_posicion_render(Mat4 mtx, s32 mode) {
    if (cantidad_objeto_matriz >= MTX_OBJETO_POOL_TAMANIO) {
        return 0;
    }
    mtxf_a_mtx(&gfx_pool->objeto_mtx[cantidad_objeto_matriz], mtx);
    switch (mode) { /* irregular */
        case 0:
            gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->objeto_mtx[cantidad_objeto_matriz++]),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            break;
        case 1:
            gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->objeto_mtx[cantidad_objeto_matriz++]),
                      G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            break;
        case 3:
            gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->objeto_mtx[cantidad_objeto_matriz++]),
                      G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            break;
        case 2:
            gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->objeto_mtx[cantidad_objeto_matriz++]),
                      G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            break;
    }
    return 1;
}

f32 dist_al_cuadrado_con_error(Vec3f from, Vec3f to) {
    f32 delta_y;
    f32 delta_z;
    f32 delta_x;

    delta_x = to[0] - from[0];
    delta_y = to[1] - from[1];
    delta_z = to[2] - from[2];
    return (delta_x * delta_x) + (delta_y * delta_y) + delta_z + delta_z;
}

s32 obtener_angulo_xz_entre_puntos(Vec3f punto_desde, Vec3f punto_a) {
    f32 delta_x;
    f32 delta_z;
    delta_x = punto_a[0] - punto_desde[0];
    delta_z = punto_a[2] - punto_desde[2];

    return atan2s(delta_x, delta_z);
}

SIN_USO u32 funcion_802B5258(Vec3f parametro0, Vec3s parametro1) {
    f32 temporal_v1;
    f32 temporal_v2;
    temporal_v1 = parametro1[0] - parametro0[0];
    temporal_v2 = parametro1[2] - parametro0[2];

    return atan2s(temporal_v1, temporal_v2);
}

void fijar_vec3f(Vec3f dest, f32 coord_x, f32 coord_y, f32 coord_z) {
    dest[0] = coord_x;
    dest[1] = coord_y;
    dest[2] = coord_z;
}

void fijar_vec3s(Vec3s dest, s16 coord_x, s16 coord_y, s16 coord_z) {
    dest[0] = coord_x;
    dest[1] = coord_y;
    dest[2] = coord_z;
}

#pragma GCC diagnostic push

#ifdef __GNUC__
#if defined(__clang__)
#pragma GCC diagnostic ignored "-Wreturn-stack-address"
#else
#pragma GCC diagnostic ignored "-Wreturn-local-addr"
#endif
#endif

void* copiar_retorno_vec3f(Vec3f dest, Vec3f orig_) {
    dest[0] = orig_[0];
    dest[1] = orig_[1];
    dest[2] = orig_[2];
    return &dest;
}

void copiar_vec3s(Vec3s dest, Vec3s orig_) {
    dest[0] = orig_[0];
    dest[1] = orig_[1];
    dest[2] = orig_[2];
}

SIN_USO void* fijar_retorno_vec3f(Vec3f dest, f32 x, f32 y, f32 z) {
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
    return &dest;
}

void copiar_mtxf(Mat4 orig_, Mat4 dest) {
    s32 renglon;
    s32 columna;

    for (renglon = 0; renglon < 4; renglon++) {
        for (columna = 0; columna < 4; columna++) {
            dest[renglon][columna] = orig_[renglon][columna];
        }
    }
}

void copiar_elemento_n_mtxf(s32* dest, s32* orig_, s32 n) {
    while (n-- > 0) {
        *dest++ = *orig_++;
    }
}

void identidad_mtxf(Mat4 mtx) {
    register s32 renglon;
    register s32 col;

    for (renglon = 0; renglon < 4; renglon++) {
        for (col = 0; col < 4; col++) {
            mtx[renglon][col] = (renglon == col) ? 1.0f : 0.0f;
        }
    }
}

void trasladar_vec3f_mat4_agregar(Mat4 orig_, Mat4 dest, Vec3f trasladar) {
    dest[3][0] = orig_[3][0] + trasladar[0];
    dest[3][1] = orig_[3][1] + trasladar[1];
    dest[3][2] = orig_[3][2] + trasladar[2];
    dest[3][3] = orig_[3][3];
    dest[0][0] = orig_[0][0];
    dest[0][1] = orig_[0][1];
    dest[0][2] = orig_[0][2];
    dest[0][3] = orig_[0][3];
    dest[1][0] = orig_[1][0];
    dest[1][1] = orig_[1][1];
    dest[1][2] = orig_[1][2];
    dest[1][3] = orig_[1][3];
    dest[2][0] = orig_[2][0];
    dest[2][1] = orig_[2][1];
    dest[2][2] = orig_[2][2];
    dest[2][3] = orig_[2][3];

}

SIN_USO void trasladar_ligero_vec3f_mat4_agregar(Mat4 mat, Mat4 dest, Vec3f pos) {
    dest[3][0] = mat[3][0] + pos[0];
    dest[3][1] = mat[3][1] + pos[1];
    dest[3][2] = mat[3][2] + pos[2];
}

void trasladar_mtxf(Mat4 dest, Vec3f trasladar) {
    identidad_mtxf(dest);
    dest[3][0] = trasladar[0];
    dest[3][1] = trasladar[1];
    dest[3][2] = trasladar[2];
}
void proyeccion_mtxf(Mat4 mtx_proy, u16* parametro1, f32 vert_fov, f32 proporcion_aspecto, f32 cerca, f32 lejos, f32 escala_homogeneo) {
    f32 medio_cot;
    s32 idx_renglon, col_idx;
    identidad_mtxf(mtx_proy);
    vert_fov *= 0.017453292222222222;
    medio_cot = cosf(vert_fov / 2) / sinf(vert_fov / 2);
    mtx_proy[0][0] = medio_cot / proporcion_aspecto;
    mtx_proy[1][1] = medio_cot;
    mtx_proy[2][2] = (cerca + lejos) / (cerca - lejos);
    mtx_proy[2][3] = -1.0f;
    mtx_proy[3][2] = (2 * cerca * lejos) / (cerca - lejos);
    mtx_proy[3][3] = 0.0f;

    for (idx_renglon = 0; idx_renglon < 4; idx_renglon++) {
        for (col_idx = 0; col_idx < 4; col_idx++) {
            mtx_proy[idx_renglon][col_idx] *= escala_homogeneo;
        }
    }

    if (parametro1 != 0) {
        if ((cerca + lejos) <= 2.0) {
            *parametro1 = 0xFFFF;
        } else {
            *parametro1 = 131072.0 / (cerca + lejos);
            if (*parametro1 <= 0) {
                *parametro1 = 1;
            }
        }
    }
}

void mirada_mtxf(Mat4 mtx, Vec3f from, Vec3f to) {
    register f32 longitud_inv;

    f32 arriba_x;
    f32 arriba_y;
    f32 arriba_z;
    f32 adelante_x;
    f32 adelante_y;
    f32 adelante_z;
    f32 derecha_x;
    f32 derecha_y;
    f32 derecha_z;

    arriba_x = 0.0f;
    arriba_y = 1.0f;
    arriba_z = 0.0f;

    adelante_x = to[0] - from[0];
    adelante_y = to[1] - from[1];
    adelante_z = to[2] - from[2];

    longitud_inv = -1.0 / sqrtf(adelante_x * adelante_x + adelante_y * adelante_y + adelante_z * adelante_z);
    adelante_x *= longitud_inv;
    adelante_y *= longitud_inv;
    adelante_z *= longitud_inv;

    derecha_x = arriba_y * adelante_z - arriba_z * adelante_y;
    derecha_y = arriba_z * adelante_x - arriba_x * adelante_z;
    derecha_z = arriba_x * adelante_y - arriba_y * adelante_x;

    longitud_inv = 1.0 / sqrtf(derecha_x * derecha_x + derecha_y * derecha_y + derecha_z * derecha_z);

    derecha_x *= longitud_inv;
    derecha_y *= longitud_inv;
    derecha_z *= longitud_inv;

    arriba_x = adelante_y * derecha_z - adelante_z * derecha_y;
    arriba_y = adelante_z * derecha_x - adelante_x * derecha_z;
    arriba_z = adelante_x * derecha_y - adelante_y * derecha_x;

    longitud_inv = 1.0 / sqrtf(arriba_x * arriba_x + arriba_y * arriba_y + arriba_z * arriba_z);
    arriba_x *= longitud_inv;
    arriba_y *= longitud_inv;
    arriba_z *= longitud_inv;

    mtx[0][0] = derecha_x;
    mtx[1][0] = derecha_y;
    mtx[2][0] = derecha_z;
    mtx[3][0] = -(from[0] * derecha_x + from[1] * derecha_y + from[2] * derecha_z);

    mtx[0][1] = arriba_x;
    mtx[1][1] = arriba_y;
    mtx[2][1] = arriba_z;
    mtx[3][1] = -(from[0] * arriba_x + from[1] * arriba_y + from[2] * arriba_z);

    mtx[0][2] = adelante_x;
    mtx[1][2] = adelante_y;
    mtx[2][2] = adelante_z;
    mtx[3][2] = -(from[0] * adelante_x + from[1] * adelante_y + from[2] * adelante_z);

    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.0f;
    mtx[3][3] = 1.0f;
}

void rotar_x_mtxf(Mat4 mtx, s16 angulo) {
    f32 angulo_sen = senos(angulo);
    f32 angulo_cos = coss(angulo);

    identidad_mtxf(mtx);
    mtx[1][1] = angulo_cos;
    mtx[1][2] = angulo_sen;
    mtx[2][1] = -angulo_sen;
    mtx[2][2] = angulo_cos;

}

void rotar_y_mtxf(Mat4 mtx, s16 angulo) {
    f32 angulo_sen = senos(angulo);
    f32 angulo_cos = coss(angulo);

    identidad_mtxf(mtx);
    mtx[0][0] = angulo_cos;
    mtx[0][2] = -angulo_sen;
    mtx[2][0] = angulo_sen;
    mtx[2][2] = angulo_cos;

}

void rotar_z_mtxf_s16(Mat4 mtx, s16 angulo) {
    f32 angulo_sen = senos(angulo);
    f32 angulo_cos = coss(angulo);

    identidad_mtxf(mtx);
    mtx[0][0] = angulo_cos;
    mtx[0][1] = angulo_sen;
    mtx[1][0] = -angulo_sen;
    mtx[1][1] = angulo_cos;

}

SIN_USO void funcion_802B5B14(Vec3f b, Vec3s rotar) {
    Mat4 mtx;
    Vec3f copiar;

    f32 sx = senos(rotar[0]);
    f32 cx = coss(rotar[0]);

    f32 sy = senos(rotar[1]);
    f32 cy = coss(rotar[1]);

    f32 sz = senos(rotar[2]);
    f32 cz = coss(rotar[2]);

    copiar[0] = b[0];
    copiar[1] = b[1];

    mtx[0][0] = cy * cz + sx * sy * sz;
    mtx[1][0] = -cy * sz + sx * sy * cz;
    mtx[2][0] = cx * sy;

    mtx[0][1] = cx * sz;
    mtx[1][1] = cx * cz;
    mtx[2][1] = -sx;

    mtx[0][2] = -sy * cz + sx * cy * sz;
    mtx[1][2] = sy * sz + sx * cy * cz;
    mtx[2][2] = cx * cy;

    b[0] = copiar[0] * mtx[0][0] + copiar[1] * mtx[0][1] + copiar[1] * mtx[0][2];
    b[1] = copiar[0] * mtx[1][0] + copiar[1] * mtx[1][1] + copiar[1] * mtx[1][2];
    b[2] = copiar[0] * mtx[2][0] + copiar[1] * mtx[2][1] + copiar[1] * mtx[2][2];
}

void vec_unidad_z_rot_x_rot_y(s16 rot_y, s16 rot_x, Vec3f parametro2) {
    f32 sen_x = senos(rot_x);
    f32 cos_x = coss(rot_x);
    f32 sen_y = senos(rot_y);
    f32 cos_y = coss(rot_y);

    parametro2[0] = cos_x * sen_y;
    parametro2[1] = sen_x;
    parametro2[2] = -(cos_x * cos_y);
}

SIN_USO void funcion_802B5D30(s16 parametro0, s16 parametro1, s32 parametro2) {
    fijar_iluminacion_circuito((Lights1*) 0x9000000, parametro0, parametro1, parametro2);
}

void fijar_iluminacion_circuito(Lights1* direccion_luz, s16 rotar_angulo_y, s16 rotar_angulo_x, s32 cantidad_luz) {
    u32 segmento = SEGMENT_NUMBER2(direccion_luz);
    u32 desplazamiento = SEGMENT_OFFSET(direccion_luz);
    SIN_USO s32 relleno;
    f32 angulo_x_sen;
    f32 angulo_x_cos;
    f32 angulo_y_sen;
    SIN_USO s32 relleno2[2];
    f32 angulo_y_cos;
    s32 idx_luz;
    s8 angulo_luz[3];
    Lights1* luces;

    luces = (Lights1*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    angulo_x_sen = senos(rotar_angulo_x);
    angulo_x_cos = coss(rotar_angulo_x);
    angulo_y_sen = senos(rotar_angulo_y);
    angulo_y_cos = coss(rotar_angulo_y);
    angulo_luz[0] = angulo_x_cos * angulo_y_sen * 120.0f;
    angulo_luz[1] = 120.0f * angulo_x_sen;
    angulo_luz[2] = angulo_x_cos * angulo_y_cos * -120.0f;
    for (idx_luz = 0; idx_luz < cantidad_luz; idx_luz++, luces++) {
        luces->l[0].l.dir[0] = angulo_luz[0];
        luces->l[0].l.dir[1] = angulo_luz[1];
        luces->l[0].l.dir[2] = angulo_luz[2];
    }
}

void escalar_mtxf(Mat4 mtx, f32 coef) {
    mtx[0][0] *= coef;
    mtx[1][0] *= coef;
    mtx[2][0] *= coef;
    mtx[0][1] *= coef;
    mtx[1][1] *= coef;
    mtx[2][1] *= coef;
    mtx[0][2] *= coef;
    mtx[1][2] *= coef;
    mtx[2][2] *= coef;
}

void rotar_traslacion_zxy_mtxf(Mat4 dest, Vec3f trasladar, Vec3s orientacion) {
    f32 sen_x;
    f32 cos_x;
    f32 sen_y;
    f32 cos_y;
    f32 sen_z;
    f32 cos_z;

    sen_x = senos(orientacion[0]);
    cos_x = coss(orientacion[0]);
    sen_y = senos(orientacion[1]);
    cos_y = coss(orientacion[1]);
    sen_z = senos(orientacion[2]);
    cos_z = coss(orientacion[2]);
    dest[0][0] = (cos_y * cos_z) + ((sen_x * sen_y) * sen_z);
    dest[1][0] = (-cos_y * sen_z) + ((sen_x * sen_y) * cos_z);
    dest[2][0] = cos_x * sen_y;
    dest[3][0] = trasladar[0];
    dest[0][1] = cos_x * sen_z;
    dest[1][1] = cos_x * cos_z;
    dest[2][1] = -sen_x;
    dest[3][1] = trasladar[1];
    dest[0][2] = (-sen_y * cos_z) + ((sen_x * cos_y) * sen_z);
    dest[1][2] = (sen_y * sen_z) + ((sen_x * cos_y) * cos_z);
    dest[2][2] = cos_x * cos_y;
    dest[3][2] = trasladar[2];
    dest[0][3] = 0.0f;
    dest[1][3] = 0.0f;
    dest[2][3] = 0.0f;
    dest[3][3] = 1.0f;
}
SIN_USO void funcion_802B60B4(Mat4 parametro0, Vec3s parametro1, Vec3s parametro2) {
    f32 seno1;
    f32 coseno1;
    f32 seno2;
    f32 coseno2;
    f32 seno3;
    f32 coseno3;

    seno1 = senos(parametro2[0]);
    coseno1 = coss(parametro2[0]);
    seno2 = senos(parametro2[1]);
    coseno2 = coss(parametro2[1]);
    seno3 = senos(parametro2[2]);
    coseno3 = coss(parametro2[2]);
    parametro0[0][0] = (coseno2 * coseno3) + ((seno1 * seno2) * seno3);
    parametro0[0][1] = (-coseno2 * seno3) + ((seno1 * seno2) * coseno3);
    parametro0[0][2] = coseno1 * seno2;
    parametro0[0][3] = (f32) parametro1[0];
    parametro0[1][0] = (f32) (coseno1 * seno3);
    parametro0[1][1] = (f32) (coseno1 * coseno3);
    parametro0[1][2] = (f32) -seno1;
    parametro0[1][3] = (f32) parametro1[1];
    parametro0[2][0] = (f32) ((-seno2 * coseno3) + ((seno1 * coseno2) * seno3));
    parametro0[2][1] = (f32) ((seno2 * seno3) + ((seno1 * coseno2) * coseno3));
    parametro0[2][2] = (f32) (coseno1 * coseno2);
    parametro0[2][3] = (f32) parametro1[2];
    parametro0[3][0] = 0.0f;
    parametro0[3][1] = 0.0f;
    parametro0[3][2] = 0.0f;
    parametro0[3][3] = 1.0f;
}

SIN_USO void funcion_802B6214(Mat4 parametro0, Vec3s parametro1, Vec3s parametro2) {
    f32 seno1;
    f32 coseno1;
    f32 seno2;
    f32 coseno2;
    f32 seno3;
    f32 coseno3;

    seno1 = senos(parametro2[0]);
    coseno1 = coss(parametro2[0]);
    seno2 = senos(parametro2[1]);
    coseno2 = coss(parametro2[1]);
    seno3 = senos(parametro2[2]);
    coseno3 = coss(parametro2[2]);
    parametro0[0][0] = (coseno2 * coseno3) + ((seno1 * seno2) * seno3);
    parametro0[1][0] = (-coseno2 * seno3) + ((seno1 * seno2) * coseno3);
    parametro0[2][0] = coseno1 * seno2;
    parametro0[3][0] = parametro1[0];
    parametro0[0][1] = coseno1 * seno3;
    parametro0[1][1] = coseno1 * coseno3;
    parametro0[2][1] = -seno1;
    parametro0[3][1] = parametro1[1];
    parametro0[0][2] = (-seno2 * coseno3) + ((seno1 * coseno2) * seno3);
    parametro0[1][2] = (seno2 * seno3) + ((seno1 * coseno2) * coseno3);
    parametro0[2][2] = coseno1 * coseno2;
    parametro0[3][2] = parametro1[2];
    parametro0[0][3] = 0.0f;
    parametro0[1][3] = 0.0f;
    parametro0[2][3] = 0.0f;
    parametro0[3][3] = 1.0f;
}

SIN_USO void funcion_802B6374(Vec3f parametro0) {
    f32 temporal_f0;
    temporal_f0 = sqrtf((parametro0[0] * parametro0[0]) + (parametro0[1] * parametro0[1]) + (parametro0[2] * parametro0[2]));
    parametro0[0] /= temporal_f0;
    parametro0[1] /= temporal_f0;
    parametro0[2] /= temporal_f0;
}

void transformar_mat3_vec3f_mtxf(Vec3f vec, Mat3 mtx) {
    f32 nuevo_x;
    f32 nuevo_y;
    f32 nuevo_z;

    nuevo_x = (mtx[0][0] * vec[0]) + (mtx[0][1] * vec[1]) + (mtx[0][2] * vec[2]);
    nuevo_y = (mtx[1][0] * vec[0]) + (mtx[1][1] * vec[1]) + (mtx[1][2] * vec[2]);
    nuevo_z = (mtx[2][0] * vec[0]) + (mtx[2][1] * vec[1]) + (mtx[2][2] * vec[2]);

    vec[0] = nuevo_x;
    vec[1] = nuevo_y;
    vec[2] = nuevo_z;
}

void transformar_mat4_vec3f_mtxf(Vec3f vec, Mat4 mat) {
    f32 nuevo_x;
    f32 nuevo_y;
    f32 nuevo_z;

    nuevo_x = (mat[0][0] * vec[0]) + (mat[0][1] * vec[1]) + (mat[0][2] * vec[2]);
    nuevo_y = (mat[1][0] * vec[0]) + (mat[1][1] * vec[1]) + (mat[1][2] * vec[2]);
    nuevo_z = (mat[2][0] * vec[0]) + (mat[2][1] * vec[1]) + (mat[2][2] * vec[2]);

    vec[0] = nuevo_x;
    vec[1] = nuevo_y;
    vec[2] = nuevo_z;
}

SIN_USO void funcion_802B64B0(SIN_USO s32 parametro0, SIN_USO s32 parametro1, SIN_USO s32 parametro2, SIN_USO s32 parametro3) {
}

void vec3f_rotar_eje_y(Vec3f vec, s16 angulo_y_rot) {
    f32 angulo_y_sen = senos(angulo_y_rot);
    f32 angulo_y_cos = coss(angulo_y_rot);

    f32 vec_x = vec[0];
    f32 vec_y = vec[1];
    f32 vec_z = vec[2];

    vec[0] = angulo_y_cos * vec_x - (angulo_y_sen * vec_z);
    vec[1] = vec_y;
    vec[2] = angulo_y_sen * vec_x + (angulo_y_cos * vec_z);
}
// Standard Y-axis rotation matrix multiplication

void calcular_matriz_orientacion(Mat3 dest, f32 eje_z, f32 eje_y_cos, f32 eje_x, s16 angulo_rotacion) {
    Mat3 mtx_rot_y;
    Mat3 mtx_rot_xz;
    s32 renglon, col;
    f32 a;
    f32 eje_normalizado_x;
    SIN_USO f32 c;
    f32 eje_normalizado_z;
    SIN_USO s32 relleno[3];
    f32 valor_sen;
    f32 valor_cos;

    valor_sen = senos(angulo_rotacion);
    valor_cos = coss(angulo_rotacion);
    mtx_rot_y[0][0] = valor_cos;
    mtx_rot_y[2][1] = 0;
    mtx_rot_y[1][2] = 0;

    mtx_rot_y[1][1] = 1;
    mtx_rot_y[2][0] = valor_sen;
    mtx_rot_y[0][2] = -valor_sen;

    mtx_rot_y[2][2] = valor_cos;
    mtx_rot_y[1][0] = 0;
    mtx_rot_y[0][1] = 0;

    if (eje_y_cos == 1) {

        for (renglon = 0; renglon < 3; renglon++) {
            for (col = 0; col < 3; col++) {
                mtx_rot_xz[renglon][col] = (renglon == col) ? 1.0f : 0.0f;
            }
        }

    } else if (eje_y_cos == -1) {

        for (renglon = 0; renglon < 3; renglon++) {
            for (col = 0; col < 3; col++) {
                mtx_rot_xz[renglon][col] = (renglon == col) ? 1.0f : 0.0f;
            }
        }

        mtx_rot_xz[1][1] = -1;

    } else {
        a = (f32) - (360.0 - ((f64) (acos1f(eje_y_cos) * 180.0f) / M_PI));
        eje_normalizado_x = -eje_x / sqrtf((eje_z * eje_z) + (eje_x * eje_x));
        eje_normalizado_z = eje_z / sqrtf((eje_z * eje_z) + (eje_x * eje_x));
        calcular_matriz_rotacion(mtx_rot_xz, a, eje_normalizado_x, 0,
                                  eje_normalizado_z);
    }
    dest[0][0] = (mtx_rot_y[0][0] * mtx_rot_xz[0][0]) + (mtx_rot_y[0][1] * mtx_rot_xz[1][0]) + (mtx_rot_y[0][2] * mtx_rot_xz[2][0]);
    dest[1][0] = (mtx_rot_y[1][0] * mtx_rot_xz[0][0]) + (mtx_rot_y[1][1] * mtx_rot_xz[1][0]) + (mtx_rot_y[1][2] * mtx_rot_xz[2][0]);
    dest[2][0] = (mtx_rot_y[2][0] * mtx_rot_xz[0][0]) + (mtx_rot_y[2][1] * mtx_rot_xz[1][0]) + (mtx_rot_y[2][2] * mtx_rot_xz[2][0]);

    dest[0][1] = (mtx_rot_y[0][0] * mtx_rot_xz[0][1]) + (mtx_rot_y[0][1] * mtx_rot_xz[1][1]) + (mtx_rot_y[0][2] * mtx_rot_xz[2][1]);
    dest[1][1] = (mtx_rot_y[1][0] * mtx_rot_xz[0][1]) + (mtx_rot_y[1][1] * mtx_rot_xz[1][1]) + (mtx_rot_y[1][2] * mtx_rot_xz[2][1]);
    dest[2][1] = (mtx_rot_y[2][0] * mtx_rot_xz[0][1]) + (mtx_rot_y[2][1] * mtx_rot_xz[1][1]) + (mtx_rot_y[2][2] * mtx_rot_xz[2][1]);

    dest[0][2] = (mtx_rot_y[0][0] * mtx_rot_xz[0][2]) + (mtx_rot_y[0][1] * mtx_rot_xz[1][2]) + (mtx_rot_y[0][2] * mtx_rot_xz[2][2]);
    dest[1][2] = (mtx_rot_y[1][0] * mtx_rot_xz[0][2]) + (mtx_rot_y[1][1] * mtx_rot_xz[1][2]) + (mtx_rot_y[1][2] * mtx_rot_xz[2][2]);
    dest[2][2] = (mtx_rot_y[2][0] * mtx_rot_xz[0][2]) + (mtx_rot_y[2][1] * mtx_rot_xz[1][2]) + (mtx_rot_y[2][2] * mtx_rot_xz[2][2]);
}

SIN_USO void funcion_802B68F8(Mat3 matriz, f32 parametro1, f32 parametro2, f32 parametro3) {
    s32 i, j;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    SIN_USO f32 relleno;

    if (parametro2 == 1) {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                matriz[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }
    } else if (parametro2 == -1) {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                matriz[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }
        matriz[1][1] = -1.0f;
    } else {
        a = (f32) - (360.0 - ((f64) (acos1f(parametro2) * 180.0f) / M_PI));
        b = -parametro3 / sqrtf((parametro1 * parametro1) + (parametro3 * parametro3));
        c = 0;
        d = parametro1 / sqrtf((parametro1 * parametro1) + (parametro3 * parametro3));
        calcular_matriz_rotacion(matriz, a, b, c, d);
    }
}

void calcular_matriz_rotacion(Mat3 matriz_dest, s16 angulo_rotacion, f32 eje_x, f32 eje_y, f32 eje_z) {
    f32 valor_sen;
    f32 valor_cos;
    f32 temporal_;
    f32 valor_zx;
    f32 valor_yz;
    f32 valor_xy;
    SIN_USO s32 relleno[2];

    valor_sen = senos((u16) angulo_rotacion);
    valor_cos = coss((u16) angulo_rotacion);

    temporal_ = 1.0f - valor_cos;

    valor_zx = (eje_z * eje_x) * temporal_;
    valor_yz = (eje_y * eje_z) * temporal_;
    valor_xy = (eje_x * eje_y) * temporal_;

    temporal_ = eje_x * eje_x;
    matriz_dest[0][0] = ((1.0f - temporal_) * valor_cos) + temporal_;
    matriz_dest[2][1] = valor_yz - (eje_x * valor_sen);
    matriz_dest[1][2] = valor_yz + (eje_x * valor_sen);

    temporal_ = eje_y * eje_y;
    matriz_dest[1][1] = (((1.0f - temporal_) * valor_cos) + temporal_);
    matriz_dest[2][0] = valor_zx + (eje_y * valor_sen);
    matriz_dest[0][2] = valor_zx - (eje_y * valor_sen);

    temporal_ = eje_z * eje_z;
    matriz_dest[2][2] = (((1.0f - temporal_) * valor_cos) + temporal_);
    matriz_dest[1][0] = valor_xy - (eje_z * valor_sen);
    matriz_dest[0][1] = valor_xy + (eje_z * valor_sen);
}

SIN_USO void funcion_802B6BC0(Mat4 parametro0, s16 parametro1, f32 parametro2, f32 parametro3, f32 parametro4) {
    f32 seno;
    f32 coseno;
    f32 temporal_f0;
    f32 temporal_f12;

    seno = senos(parametro1);
    coseno = coss(parametro1);
    temporal_f0 = sqrtf((parametro2 * parametro2) + (parametro4 * parametro4));
    if (temporal_f0 != 0.0f) {
        temporal_f12 = 1.0f / temporal_f0;
        parametro0[0][0] = ((-parametro4 * coseno) - ((seno * parametro3) * parametro2)) * temporal_f12;
        parametro0[0][3] = ((parametro4 * seno) - ((coseno * parametro3) * parametro2)) * temporal_f12;
        parametro0[1][2] = -parametro2;
        parametro0[0][1] = seno * temporal_f0;
        parametro0[1][0] = coseno * temporal_f0;
        parametro0[1][3] = -parametro3;
        parametro0[0][2] = ((coseno * parametro2) - ((seno * parametro3) * parametro4)) * temporal_f12;
        parametro0[1][1] = ((-seno * parametro2) - ((coseno * parametro3) * parametro4)) * temporal_f12;
        parametro0[2][0] = -parametro4;
        parametro0[0][3] = 0.0f;
        parametro0[1][2] = 0.0f;
        parametro0[2][1] = 0.0f;
    } else {
        parametro0[0][1] = 0.0f;
        parametro0[1][3] = 0.0f;
        parametro0[0][2] = 0.0f;
        parametro0[1][1] = 0.0f;
        parametro0[0][3] = 0.0f;
        parametro0[1][2] = 0.0f;
        parametro0[2][1] = 0.0f;
        parametro0[0][0] = 1.0f;
        parametro0[1][0] = 1.0f;
        parametro0[2][0] = 1.0f;
    }
}

SIN_USO void funcion_802B6D58(Mat4 parametro0, Vec3f parametro1, Vec3f parametro2) {
    f32 seno1;
    f32 coseno1;
    f32 seno2;
    f32 coseno2;
    f32 seno3;
    f32 coseno3;

    seno1 = senos(parametro2[0]);
    coseno1 = coss(parametro2[0]);
    seno2 = senos(parametro2[1]);
    coseno2 = coss(parametro2[1]);
    seno3 = senos(parametro2[2]);
    coseno3 = coss(parametro2[2]);
    parametro0[0][0] = (coseno2 * coseno3) + ((seno1 * seno2) * seno3);
    parametro0[1][0] = (-coseno2 * seno3) + (seno1 * seno2) * coseno3;
    parametro0[2][0] = coseno1 * seno2;
    parametro0[3][0] = parametro1[0];
    parametro0[0][1] = coseno1 * seno3;
    parametro0[1][1] = coseno1 * coseno3;
    parametro0[2][1] = -seno1;
    parametro0[3][1] = parametro1[1];
    parametro0[0][2] = (-seno2 * coseno3) + ((seno1 * coseno2) * seno3);
    parametro0[1][2] = (seno2 * seno3) + ((seno1 * coseno2) * coseno3);
    parametro0[2][2] = coseno1 * coseno2;
    parametro0[3][2] = parametro1[2];
    parametro0[0][3] = 0.0f;
    parametro0[1][3] = 0.0f;
    parametro0[2][3] = 0.0f;
    parametro0[3][3] = 1.0f;
}

void multiplicacion_mtxf(Mat4 dest, Mat4 izquierda_mtx, Mat4 derecha_mtx) {
    Mat4 producto;
    producto[0][0] = (izquierda_mtx[0][0] * derecha_mtx[0][0]) + (izquierda_mtx[0][1] * derecha_mtx[1][0]) +
                    (izquierda_mtx[0][2] * derecha_mtx[2][0]) + (izquierda_mtx[0][3] * derecha_mtx[3][0]);
    producto[0][1] = (izquierda_mtx[0][0] * derecha_mtx[0][1]) + (izquierda_mtx[0][1] * derecha_mtx[1][1]) +
                    (izquierda_mtx[0][2] * derecha_mtx[2][1]) + (izquierda_mtx[0][3] * derecha_mtx[3][1]);
    producto[0][2] = (izquierda_mtx[0][0] * derecha_mtx[0][2]) + (izquierda_mtx[0][1] * derecha_mtx[1][2]) +
                    (izquierda_mtx[0][2] * derecha_mtx[2][2]) + (izquierda_mtx[0][3] * derecha_mtx[3][2]);
    producto[0][3] = (izquierda_mtx[0][0] * derecha_mtx[0][3]) + (izquierda_mtx[0][1] * derecha_mtx[1][3]) +
                    (izquierda_mtx[0][2] * derecha_mtx[2][3]) + (izquierda_mtx[0][3] * derecha_mtx[3][3]);
    producto[1][0] = (izquierda_mtx[1][0] * derecha_mtx[0][0]) + (izquierda_mtx[1][1] * derecha_mtx[1][0]) +
                    (izquierda_mtx[1][2] * derecha_mtx[2][0]) + (izquierda_mtx[1][3] * derecha_mtx[3][0]);
    producto[1][1] = (izquierda_mtx[1][0] * derecha_mtx[0][1]) + (izquierda_mtx[1][1] * derecha_mtx[1][1]) +
                    (izquierda_mtx[1][2] * derecha_mtx[2][1]) + (izquierda_mtx[1][3] * derecha_mtx[3][1]);
    producto[1][2] = (izquierda_mtx[1][0] * derecha_mtx[0][2]) + (izquierda_mtx[1][1] * derecha_mtx[1][2]) +
                    (izquierda_mtx[1][2] * derecha_mtx[2][2]) + (izquierda_mtx[1][3] * derecha_mtx[3][2]);
    producto[1][3] = (izquierda_mtx[1][0] * derecha_mtx[0][3]) + (izquierda_mtx[1][1] * derecha_mtx[1][3]) +
                    (izquierda_mtx[1][2] * derecha_mtx[2][3]) + (izquierda_mtx[1][3] * derecha_mtx[3][3]);
    producto[2][0] = (izquierda_mtx[2][0] * derecha_mtx[0][0]) + (izquierda_mtx[2][1] * derecha_mtx[1][0]) +
                    (izquierda_mtx[2][2] * derecha_mtx[2][0]) + (izquierda_mtx[2][3] * derecha_mtx[3][0]);
    producto[2][1] = (izquierda_mtx[2][0] * derecha_mtx[0][1]) + (izquierda_mtx[2][1] * derecha_mtx[1][1]) +
                    (izquierda_mtx[2][2] * derecha_mtx[2][1]) + (izquierda_mtx[2][3] * derecha_mtx[3][1]);
    producto[2][2] = (izquierda_mtx[2][0] * derecha_mtx[0][2]) + (izquierda_mtx[2][1] * derecha_mtx[1][2]) +
                    (izquierda_mtx[2][2] * derecha_mtx[2][2]) + (izquierda_mtx[2][3] * derecha_mtx[3][2]);
    producto[2][3] = (izquierda_mtx[2][0] * derecha_mtx[0][3]) + (izquierda_mtx[2][1] * derecha_mtx[1][3]) +
                    (izquierda_mtx[2][2] * derecha_mtx[2][3]) + (izquierda_mtx[2][3] * derecha_mtx[3][3]);
    producto[3][0] = (izquierda_mtx[3][0] * derecha_mtx[0][0]) + (izquierda_mtx[3][1] * derecha_mtx[1][0]) +
                    (izquierda_mtx[3][2] * derecha_mtx[2][0]) + (izquierda_mtx[3][3] * derecha_mtx[3][0]);
    producto[3][1] = (izquierda_mtx[3][0] * derecha_mtx[0][1]) + (izquierda_mtx[3][1] * derecha_mtx[1][1]) +
                    (izquierda_mtx[3][2] * derecha_mtx[2][1]) + (izquierda_mtx[3][3] * derecha_mtx[3][1]);
    producto[3][2] = (izquierda_mtx[3][0] * derecha_mtx[0][2]) + (izquierda_mtx[3][1] * derecha_mtx[1][2]) +
                    (izquierda_mtx[3][2] * derecha_mtx[2][2]) + (izquierda_mtx[3][3] * derecha_mtx[3][2]);
    producto[3][3] = (izquierda_mtx[3][0] * derecha_mtx[0][3]) + (izquierda_mtx[3][1] * derecha_mtx[1][3]) +
                    (izquierda_mtx[3][2] * derecha_mtx[2][3]) + (izquierda_mtx[3][3] * derecha_mtx[3][3]);
    copiar_elemento_n_mtxf((s32*) dest, (s32*) producto, 16);
}

void mtxf_a_mtx(Mtx* dest, Mat4 orig_) {
#ifdef AVOID_UB
    guMtxF2L(orig_, dest);
#else
    s32 como_punto_fijo;
    register s32 i;
    register s16* a3 = (s16*) dest;
    register s16* t0 = (s16*) dest + 16;
    register f32* t1 = (f32*) orig_;

    for (i = 0; i < 16; i++) {
        como_punto_fijo = *t1++ * (1 << 16);
        *a3++ = ALTO_S16_OBTENER_DE_32(como_punto_fijo); // integer part
        *t0++ = BAJO_S16_OBTENER_DE_32(como_punto_fijo);
    }
#endif
}

u16 busqueda_atan2(f32 y, f32 x) {
    u16 devuelto;

    if (x == 0) {
        devuelto = tabla_arctan[0];
    } else {
        if (1000000.0f < y / x) {
            if (y > 0.0f) {
                devuelto = 0x4000;
            } else {
                devuelto = 0xC000;
            }
        } else {
            devuelto = tabla_arctan[(s32) (y / x * 1024 + 0.5f)];
        }
    }
    return devuelto;
}

u16 atan2s(f32 y, f32 x) {
    u16 devuelto;
    if (y >= 0) {
        if (x >= 0) {
            if (x >= y) {
                devuelto = busqueda_atan2(y, x);
            } else {
                devuelto = 0x4000 - busqueda_atan2(x, y);
            }
        } else {
            x = -x;
            if (x < y) {
                devuelto = 0x4000 + busqueda_atan2(x, y);
            } else {
                devuelto = 0x8000 - busqueda_atan2(y, x);
            }
        }
    } else {
        y = -y;
        if (x < 0) {
            x = -x;
            if (x >= y) {
                devuelto = 0x8000 + busqueda_atan2(y, x);
            } else {
                devuelto = 0xC000 - busqueda_atan2(x, y);
            }
        } else {
            if (x < y) {
                devuelto = 0xC000 + busqueda_atan2(x, y);
            } else {
                devuelto = -busqueda_atan2(y, x);
            }
        }
    }
    return devuelto;
}

f32 atan2f(f32 y, f32 x) {
    return atan2s(y, x);
}
