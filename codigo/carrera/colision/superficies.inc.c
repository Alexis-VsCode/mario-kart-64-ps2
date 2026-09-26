// Superficies

#pragma intrinsic(sqrtf)

void anular_displaylist(uintptr_t direccion) {
    s32 segmento = SEGMENT_NUMBER2(direccion);
    s32 desplazamiento = SEGMENT_OFFSET(direccion);

    Gfx* macro;

    macro = (Gfx*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    macro->words.w0 = (G_ENDDL << 24);
    macro->words.w1 = 0;
}

void funcion_802AAAAC(Colision* colision) {
    colision->indice_yx_malla = 5000;
    colision->indice_zy_malla = 5000;
    colision->indice_zx_malla = 5000;
    colision->desconocido30 = 0;
    colision->desconocido32 = 0;
    colision->unk34 = 0;
    colision->distancia_superficie[0] = 0;
    colision->distancia_superficie[1] = 0;
    colision->distancia_superficie[2] = 0;
    fijar_vec3f(colision->desconocido48, 0.0f, 0.0f, 1.0f);
    fijar_vec3f(colision->desconocido54, 1.0f, 0.0f, 0.0f);
    fijar_vec3f(colision->vector_orientacion, 0.0f, 1.0f, 0.0f);
}

f32 funcion_802AAB4C(Jugador* jugador) {
    f32 jugador_x;
    f32 jugador_z;
    s32 temporal_v1;

    jugador_x = jugador->pos[0];
    jugador_z = jugador->pos[2];
    switch (id_circuito_actual) {
        case CIRCUITO_BOWSER_CASTLE:
            if (jugador_x > 1859.0f) {
                return dato_8015F8E4;
            }
            if (jugador_x < 1549.0f) {
                return dato_8015F8E4;
            }
            if (jugador_z > -1102.0f) {
                return dato_8015F8E4;
            }
            if (jugador_z < -1402.0f) {
                return dato_8015F8E4;
            }
            return 20.0f;
        case CIRCUITO_KOOPA_BEACH:
            if (jugador_x > 239.0f) {
                return dato_8015F8E4;
            }
            if (jugador_x < 67.0f) {
                return dato_8015F8E4;
            }
            if (jugador_z > 2405.0f) {
                return dato_8015F8E4;
            }
            if (jugador_z < 2233.0f) {
                return dato_8015F8E4;
            }
            return 0.8f;
        case CIRCUITO_SHERBET_LAND:
            if ((obtener_tipo_superficie(jugador->colision.indice_zx_malla) & 0xFF) == NIEVE) {
                return (f32) (min_y_circuito - 0xA);
            }
            return dato_8015F8E4;
        case CIRCUITO_DK_JUNGLE:
            temporal_v1 = obtener_id_seccion_pista(jugador->colision.indice_zx_malla) & 0xFF;
            if (temporal_v1 == 0xFF) {
                if ((obtener_tipo_superficie(jugador->colision.indice_zx_malla) & 0xFF) == CUEVA) {
                    return -475.0f;
                }
                if (jugador_x > -478.0f) {
                    return -33.9f;
                }
                if (jugador_x < -838.0f) {
                    return -475.0f;
                }
                if (jugador_z > -436.0f) {
                    return -475.0f;
                }
                if (jugador_z < -993.0f) {
                    return -33.9f;
                }
                if (jugador_z < jugador_x) {
                    return -475.0f;
                }
                return -33.9f;
            }
            if (temporal_v1 >= 0x14) {
                return -475.0f;
            }
            return -33.9f;
        default:
            return dato_8015F8E4;
    }
}

s32 comprobar_colision_zx(Colision* colision, f32 tamanio_caja_envolvente, f32 pos_x, f32 pos_y, f32 pos_z, u16 index) {
    TrianguloColision* triangulo = &malla_colision[index];
    SIN_USO f32 relleno;
    f32 x3;
    SIN_USO f32 relleno2;
    f32 z3;
    SIN_USO f32 relleno3[4];
    f32 x2;
    f32 z2;
    f32 x1;
    f32 z1;
    f32 distancia_a_superficie;
    f32 cruce_producto_zx_1;
    f32 cruce_producto_zx_2;
    f32 cruce_producto_zx_3;
    s32 b = true;

    if (triangulo->normal_y < -0.9f) {
        return 0;
    }
    if (triangulo->min_x > pos_x) {
        return 0;
    }
    if (triangulo->min_z > pos_z) {
        return 0;
    }
    if (triangulo->max_x < pos_x) {
        return 0;
    }
    if (triangulo->max_z < pos_z) {
        return 0;
    }
    if ((triangulo->min_y - tamanio_caja_envolvente * 3.0f) > pos_y) {
        return 0;
    }

    x1 = triangulo->vtx1->v.ob[0];
    z1 = triangulo->vtx1->v.ob[2];

    x2 = triangulo->vtx2->v.ob[0];
    z2 = triangulo->vtx2->v.ob[2];

    x3 = triangulo->vtx3->v.ob[0];
    z3 = triangulo->vtx3->v.ob[2];

    cruce_producto_zx_1 = (z1 - pos_z) * (x2 - pos_x) - (x1 - pos_x) * (z2 - pos_z);

    if (!cruce_producto_zx_1) {

        cruce_producto_zx_2 = (z2 - pos_z) * (x3 - pos_x) - (x2 - pos_x) * (z3 - pos_z);

        cruce_producto_zx_3 = (z3 - pos_z) * (x1 - pos_x) - (x3 - pos_x) * (z1 - pos_z);

        if ((cruce_producto_zx_2 * cruce_producto_zx_3) < 0.0f) {
            b = false;
        }
    } else {

        cruce_producto_zx_2 = (z2 - pos_z) * (x3 - pos_x) - (x2 - pos_x) * (z3 - pos_z);

        if (!cruce_producto_zx_2) {
            cruce_producto_zx_3 = (z3 - pos_z) * (x1 - pos_x) - (x3 - pos_x) * (z1 - pos_z);

            if ((cruce_producto_zx_1 * cruce_producto_zx_3) < 0.0f) {
                b = false;
            }
        } else {
            if ((cruce_producto_zx_1 * cruce_producto_zx_2) < 0.0f) {
                b = false;
            } else {
                cruce_producto_zx_3 = (z3 - pos_z) * (x1 - pos_x) - (x3 - pos_x) * (z1 - pos_z);
                if (cruce_producto_zx_3 != 0) {
                    if ((cruce_producto_zx_2 * cruce_producto_zx_3) < 0.0f) {
                        b = false;
                    }
                }
            }
        }
    }
    if (!b) {
        return 0;
    }
    distancia_a_superficie =
        ((triangulo->normal_x * pos_x) + (triangulo->normal_y * pos_y) + (triangulo->normal_z * pos_z) + triangulo->distancia) -
        tamanio_caja_envolvente;
    if (distancia_a_superficie > 0.0f) {
        if (colision->distancia_superficie[2] > distancia_a_superficie) {
            colision->unk34 = 1;
            colision->indice_zx_malla = index;
            colision->distancia_superficie[2] = distancia_a_superficie;
            colision->vector_orientacion[0] = triangulo->normal_x;
            colision->vector_orientacion[1] = triangulo->normal_y;
            colision->vector_orientacion[2] = triangulo->normal_z;
        }
        return 0;
    }

    if (distancia_a_superficie > -16.0f) {
        colision->unk34 = 1;
        colision->indice_zx_malla = index;
        colision->distancia_superficie[2] = distancia_a_superficie;
        colision->vector_orientacion[0] = triangulo->normal_x;
        colision->vector_orientacion[1] = triangulo->normal_y;
        colision->vector_orientacion[2] = triangulo->normal_z;
        return 1;
    }
    return 0;
}

s32 comprobar_colision_yx(Colision* colision, f32 tamanio_caja_envolvente, f32 pos_x, f32 pos_y, f32 pos_z, u16 index) {
    TrianguloColision* triangulo = &malla_colision[index];
    SIN_USO f32 relleno[6];
    f32 x3;
    f32 y3;
    SIN_USO f32 relleno2[1];

    SIN_USO f32 relleno3[5];
    f32 x2;
    f32 y2;
    f32 x1;
    f32 y1;
    f32 distancia_a_superficie;
    f32 cruce_producto_yx_1;
    f32 cruce_producto_yx_2;
    f32 cruce_producto_yx_3;
    s32 b = true;

    if (triangulo->min_x > pos_x) {
        return 0;
    }
    if (triangulo->max_x < pos_x) {
        return 0;
    }
    if (triangulo->max_y < pos_y) {
        return 0;
    }
    if (triangulo->min_y > pos_y) {
        return 0;
    }

    if ((triangulo->min_z - tamanio_caja_envolvente * 3.0f) > pos_z) {
        return 0;
    }
    if ((triangulo->max_z + tamanio_caja_envolvente * 3.0f) < pos_z) {
        return 0;
    }

    x1 = triangulo->vtx1->v.ob[0];
    y1 = triangulo->vtx1->v.ob[1];

    x2 = triangulo->vtx2->v.ob[0];
    y2 = triangulo->vtx2->v.ob[1];

    x3 = triangulo->vtx3->v.ob[0];
    y3 = triangulo->vtx3->v.ob[1];

    cruce_producto_yx_1 = (y1 - pos_y) * (x2 - pos_x) - (x1 - pos_x) * (y2 - pos_y);

    if (!cruce_producto_yx_1) {

        cruce_producto_yx_2 = (y2 - pos_y) * (x3 - pos_x) - (x2 - pos_x) * (y3 - pos_y);

        cruce_producto_yx_3 = (y3 - pos_y) * (x1 - pos_x) - (x3 - pos_x) * (y1 - pos_y);

        if ((cruce_producto_yx_2 * cruce_producto_yx_3) < 0.0f) {
            b = false;
        }
    } else {
        cruce_producto_yx_2 = (y2 - pos_y) * (x3 - pos_x) - (x2 - pos_x) * (y3 - pos_y);
        if (!cruce_producto_yx_2) {
            cruce_producto_yx_3 = (y3 - pos_y) * (x1 - pos_x) - (x3 - pos_x) * (y1 - pos_y);
            if (cruce_producto_yx_1 * cruce_producto_yx_3 < 0.0f) {
                b = false;
            }
        } else {
            if ((cruce_producto_yx_1 * cruce_producto_yx_2) < 0.0f) {
                b = false;
            } else {
                cruce_producto_yx_3 = ((y3 - pos_y) * (x1 - pos_x)) - ((x3 - pos_x) * (y1 - pos_y));
                if (cruce_producto_yx_3 != 0) {
                    if ((cruce_producto_yx_2 * cruce_producto_yx_3) < 0.0f) {
                        b = false;
                    }
                }
            }
        }
    }
    if (!b) {
        return 0;
    }
    distancia_a_superficie =
        ((triangulo->normal_x * pos_x) + (triangulo->normal_y * pos_y) + (triangulo->normal_z * pos_z) + triangulo->distancia) -
        tamanio_caja_envolvente;
    if (distancia_a_superficie > 0.0f) {
        if (distancia_a_superficie < colision->distancia_superficie[0]) {
            colision->desconocido30 = 1;
            colision->indice_yx_malla = index;
            colision->distancia_superficie[0] = distancia_a_superficie;
            colision->desconocido48[0] = triangulo->normal_x;
            colision->desconocido48[1] = triangulo->normal_y;
            colision->desconocido48[2] = triangulo->normal_z;
        }
        return 0;
    }

    if (distancia_a_superficie > -16.0f) {
        colision->desconocido30 = 1;
        colision->indice_yx_malla = index;
        colision->distancia_superficie[0] = distancia_a_superficie;
        colision->desconocido48[0] = triangulo->normal_x;
        colision->desconocido48[1] = triangulo->normal_y;
        colision->desconocido48[2] = triangulo->normal_z;
        return 1;
    }
    return 0;
}

s32 comprobar_colision_zy(Colision* colision, f32 tamanio_caja_envolvente, f32 pos_x, f32 pos_y, f32 pos_z, u16 index) {
    TrianguloColision* triangulo = &malla_colision[index];
    s32 b = true;
    SIN_USO f32 relleno[7];
    f32 y3;
    f32 z3;
    SIN_USO f32 relleno2[5];
    f32 y2;
    f32 z2;
    f32 y1;
    f32 z1;
    f32 distancia_a_superficie;
    f32 cruce_producto_yz_1;
    f32 cruce_producto_yz_2;
    f32 cruce_producto_yz_3;
    if (triangulo->min_z > pos_z) {
        return 0;
    }
    if (triangulo->max_z < pos_z) {
        return 0;
    }
    if (triangulo->max_y < pos_y) {
        return 0;
    }
    if (triangulo->min_y > pos_y) {
        return 0;
    }
    if ((triangulo->min_x - (tamanio_caja_envolvente * 3.0f)) > pos_x) {
        return 0;
    }
    if ((triangulo->max_x + (tamanio_caja_envolvente * 3.0f)) < pos_x) {
        return 0;
    }

    z1 = triangulo->vtx1->v.ob[2];
    y1 = triangulo->vtx1->v.ob[1];

    z2 = triangulo->vtx2->v.ob[2];
    y2 = triangulo->vtx2->v.ob[1];

    z3 = triangulo->vtx3->v.ob[2];
    y3 = triangulo->vtx3->v.ob[1];

    cruce_producto_yz_1 = (y1 - pos_y) * (z2 - pos_z) - (z1 - pos_z) * (y2 - pos_y);

    if (!cruce_producto_yz_1) {

        cruce_producto_yz_2 = ((y2 - pos_y) * (z3 - pos_z)) - ((z2 - pos_z) * (y3 - pos_y));

        cruce_producto_yz_3 = ((y3 - pos_y) * (z1 - pos_z)) - ((z3 - pos_z) * (y1 - pos_y));

        if ((cruce_producto_yz_2 * cruce_producto_yz_3) < 0.0f) {
            b = false;
        }
    } else {

        cruce_producto_yz_2 = ((y2 - pos_y) * (z3 - pos_z)) - ((z2 - pos_z) * (y3 - pos_y));

        if (cruce_producto_yz_2 == 0) {
            cruce_producto_yz_3 = ((y3 - pos_y) * (z1 - pos_z)) - ((z3 - pos_z) * (y1 - pos_y));

            if ((cruce_producto_yz_1 * cruce_producto_yz_3) < 0.0f) {
                b = false;
            }
        } else {

            if ((cruce_producto_yz_1 * cruce_producto_yz_2) < 0.0f) {
                b = false;
            } else {
                cruce_producto_yz_3 = ((y3 - pos_y) * (z1 - pos_z)) - ((z3 - pos_z) * (y1 - pos_y));
                if (cruce_producto_yz_3 != 0) {
                    if ((cruce_producto_yz_2 * cruce_producto_yz_3) < 0.0f) {
                        b = false;
                    }
                }
            }
        }
    }
    if (!b) {
        return 0;
    }

    distancia_a_superficie = ((((triangulo->normal_x * pos_x) + (triangulo->normal_y * pos_y)) + (triangulo->normal_z * pos_z)) +
                         triangulo->distancia) -
                        tamanio_caja_envolvente;

    if (distancia_a_superficie > 0.0f) {
        if (distancia_a_superficie < colision->distancia_superficie[1]) {
            colision->desconocido32 = 1;
            colision->indice_zy_malla = index;
            colision->distancia_superficie[1] = distancia_a_superficie;
            colision->desconocido54[0] = triangulo->normal_x;
            colision->desconocido54[1] = triangulo->normal_y;
            colision->desconocido54[2] = triangulo->normal_z;
        }
        return 0;
    }
    if (distancia_a_superficie > (-16.0f)) {
        colision->desconocido32 = 1;
        colision->indice_zy_malla = index;
        colision->distancia_superficie[1] = distancia_a_superficie;
        colision->desconocido54[0] = triangulo->normal_x;
        colision->desconocido54[1] = triangulo->normal_y;
        colision->desconocido54[2] = triangulo->normal_z;
        return 1;
    }
    return 0;
}

s32 comprobar_chocando_horizontalmente_con_triangulo(f32 pos_x, f32 pos_z, u16 index) {
    TrianguloColision* triangulo = &malla_colision[index];
    SIN_USO f32 relleno;
    f32 x3;
    SIN_USO f32 relleno2;
    f32 z3;
    f32 x2;
    SIN_USO f32 relleno3;
    f32 z2;
    f32 x1;
    f32 z1;
    SIN_USO f32 relleno4[4];
    f32 cruce_producto_zx_1;
    f32 cruce_producto_zx_3;
    f32 cruce_producto_zx_2;
    s32 b = true;

    x1 = triangulo->vtx1->v.ob[0];
    z1 = triangulo->vtx1->v.ob[2];

    x2 = triangulo->vtx2->v.ob[0];
    z2 = triangulo->vtx2->v.ob[2];

    x3 = triangulo->vtx3->v.ob[0];
    z3 = triangulo->vtx3->v.ob[2];

    cruce_producto_zx_1 = (z1 - pos_z) * (x2 - pos_x) - (x1 - pos_x) * (z2 - pos_z);

    if (!cruce_producto_zx_1) {

        cruce_producto_zx_2 = (z2 - pos_z) * (x3 - pos_x) - (x2 - pos_x) * (z3 - pos_z);

        cruce_producto_zx_3 = (z3 - pos_z) * (x1 - pos_x) - (x3 - pos_x) * (z1 - pos_z);

        if ((cruce_producto_zx_2 * cruce_producto_zx_3) < 0.0f) {
            b = false;
        }
    } else {
        cruce_producto_zx_2 = (z2 - pos_z) * (x3 - pos_x) - (x2 - pos_x) * (z3 - pos_z);
        if (!cruce_producto_zx_2) {
            cruce_producto_zx_3 = (z3 - pos_z) * (x1 - pos_x) - (x3 - pos_x) * (z1 - pos_z);
            if (cruce_producto_zx_1 * cruce_producto_zx_3 < 0.0f) {
                b = false;
            }
        } else {
            if ((cruce_producto_zx_1 * cruce_producto_zx_2) < 0.0f) {
                b = false;
            } else {
                cruce_producto_zx_3 = ((z3 - pos_z) * (x1 - pos_x)) - ((x3 - pos_x) * (z1 - pos_z));
                if (cruce_producto_zx_3 != 0) {
                    if ((cruce_producto_zx_2 * cruce_producto_zx_3) < 0.0f) {
                        b = false;
                    }
                }
            }
        }
    }
    return b;
}

s8 obtener_tipo_superficie(u16 index) {
    TrianguloColision* triangulo = &malla_colision[index];
    return triangulo->tipo_superficie;
}

s16 obtener_id_seccion_pista(u16 index) {
    TrianguloColision* triangulo = &malla_colision[index];
    return triangulo->flags & 0xFF;
}

s16 funcion_802ABD7C(u16 index) {
    TrianguloColision* triangulo = &malla_colision[index];
    return triangulo->flags & 0x1000;
}

s16 funcion_802ABDB8(u16 index) {
    TrianguloColision* triangulo = &malla_colision[index];
    return triangulo->flags & 0x400;
}

s16 funcion_802ABDF4(u16 index) {
    TrianguloColision* triangulo = &malla_colision[index];
    return triangulo->flags & 0x800;
}

f32 calcular_altura_superficie(f32 x, f32 y, f32 z, u16 index) {
    TrianguloColision* triangulo = &malla_colision[index];
    if (triangulo->normal_y == 0.0f) {
        return y;
    }
    return ((triangulo->normal_x * x) + (triangulo->normal_z * z) + triangulo->distancia) / -triangulo->normal_y;
}

f32 funcion_802ABEAC(Colision* colision, Vec3f pos) {
    if (colision->unk34 == 1) {
        return calcular_altura_superficie(pos[0], pos[1], pos[2], colision->indice_zx_malla);
    }
    if (colision->desconocido30 == 1) {
        return calcular_altura_superficie(pos[0], pos[1], pos[2], colision->indice_yx_malla);
    }
    if (colision->desconocido32 == 1) {
        return calcular_altura_superficie(pos[0], pos[1], pos[2], colision->indice_zy_malla);
    }
    return pos[1];
}

void procesar_colision_caparazon(Vec3f pos, SIN_USO f32 tamanio_caja_envolvente, Vec3f velocidad, SIN_USO f32 desconocido) {
    f32 magnitud;
    f32 producto_punto;
    f32 x;
    f32 escalar_x;
    f32 escalar_y;
    f32 escalar_z;
    f32 y;
    f32 z;
    SIN_USO f32 x2;
    SIN_USO f32 y2;
    f32 magnitud_velocidad;
    SIN_USO f32 z2;
    f32 escalar_factor;

    x = velocidad[0];
    y = velocidad[1];
    z = velocidad[2];
    magnitud_velocidad = sqrtf((x * x) + (y * y) + (z * z));

    if ((magnitud_velocidad > 4.5) || (magnitud_velocidad < 3.5)) {
        magnitud_velocidad = 4.0f;
    }

    x2 = pos[0];
    y2 = pos[1];
    z2 = pos[2];

    producto_punto = (pos[0] * x) + (pos[1] * y) + (pos[2] * z);
    escalar_x = x - producto_punto * pos[0];
    escalar_y = y - producto_punto * pos[1];
    escalar_z = z - producto_punto * pos[2];

    x = escalar_x - producto_punto * pos[0];
    y = escalar_y - producto_punto * pos[1];
    z = escalar_z - producto_punto * pos[2];

    magnitud = sqrtf((x * x) + (y * y) + (z * z));

    escalar_factor = 1.0f / magnitud * magnitud_velocidad;

    velocidad[0] = x * escalar_factor;
    velocidad[1] = y * escalar_factor;
    velocidad[2] = z * escalar_factor;
}

void colision_caparazon(Colision* colision, Vec3f velocidad) {
    if (colision->distancia_superficie[0] < 0.0f) {
        procesar_colision_caparazon(colision->desconocido48, colision->distancia_superficie[0], velocidad, 2.0f);
    }

    if (colision->distancia_superficie[1] < 0.0f) {
        procesar_colision_caparazon(colision->desconocido54, colision->distancia_superficie[1], velocidad, 2.0f);
    }
}

void ajustar_ortogonalmente_pos(Vec3f pos1, f32 tamanio_caja_envolvente, Vec3f pos2, SIN_USO f32 desconocido) {
    f32 x1;
    f32 y1;
    f32 z1;
    f32 x2;
    f32 y2;
    f32 z2;
    f32 producto_punto;
    f32 orto_x;
    f32 orto_y;
    f32 orto_z;

    x2 = pos2[0];
    y2 = pos2[1];
    z2 = pos2[2];
    x1 = -pos1[0];
    y1 = -pos1[1];
    z1 = -pos1[2];

    producto_punto = (x1 * x2) + (y1 * y2) + (z1 * z2);

    orto_x = x2 - (producto_punto * x1);
    orto_y = y2 - (producto_punto * y1);
    orto_z = z2 - (producto_punto * z1);

    if (tamanio_caja_envolvente < -3.5) {
        pos2[0] = orto_x - (producto_punto * x1 * 0.5f);
        pos2[1] = orto_y - (producto_punto * y1 * 0.5f);
        pos2[2] = orto_z - (producto_punto * z1 * 0.5f);
    } else {
        pos2[0] = orto_x;
        pos2[1] = orto_y;
        pos2[2] = orto_z;
    }
}

SIN_USO s32 detectar_colision_rueda(RuedaKart* rueda) {
    Colision colision;
    SIN_USO s32 relleno[12];
    s32 longitud_x_circuito;
    s32 longitud_z_circuito;
    f32 rueda_x;
    f32 rueda_y;
    f32 rueda_z;
    s16 indice_x_seccion;
    s16 indice_z_seccion;
    u16 i;
    u16 triangulos_num;
    u16 indice_malla;
    s16 indice_cuadricula;
    u16 indice_seccion;

    colision.desconocido30 = 0;
    colision.desconocido32 = 0;
    colision.unk34 = 0;
    colision.distancia_superficie[0] = 1000.0f;
    colision.distancia_superficie[1] = 1000.0f;
    colision.distancia_superficie[2] = 1000.0f;
    rueda_x = rueda->pos[0];
    rueda_y = rueda->pos[1];
    rueda_z = rueda->pos[2];
    switch (rueda->banderas_superficie) { /* irregular */
        case 0x80:
            if (comprobar_colision_zy(&colision, 5.0f, rueda_x, rueda_y, rueda_z, (u16) (s32) rueda->indice_malla_colision) == 1) {
                rueda->altura_base = calcular_altura_superficie(rueda_x, rueda_y, rueda_z, rueda->indice_malla_colision);
                return 1;
            }
            break;
        case 0x40:
            if (comprobar_colision_zx(&colision, 5.0f, rueda_x, rueda_y, rueda_z, (u16) (s32) rueda->indice_malla_colision) == 1) {
                rueda->altura_base = calcular_altura_superficie(rueda_x, rueda_y, rueda_z, rueda->indice_malla_colision);
                return 1;
            }
            break;
        case 0x20:
            if (comprobar_colision_yx(&colision, 5.0f, rueda_x, rueda_y, rueda_z, (u16) (s32) rueda->indice_malla_colision) == 1) {
                rueda->altura_base = calcular_altura_superficie(rueda_x, rueda_y, rueda_z, rueda->indice_malla_colision);
                return 1;
            }
            break;
        default:
            break;
    }
    longitud_x_circuito = max_x_circuito - min_x_circuito;
    longitud_z_circuito = max_z_circuito - min_z_circuito;
    indice_x_seccion = (rueda_x - min_x_circuito) / (longitud_x_circuito / TAMANIO_CUADRICULA);
    indice_z_seccion = (rueda_z - min_z_circuito) / (longitud_z_circuito / TAMANIO_CUADRICULA);
    if (indice_x_seccion < 0) {
        return 0;
    }
    if (indice_z_seccion < 0) {
        return 0;
    }
    if (indice_x_seccion >= TAMANIO_CUADRICULA) {
        return 0;
    }
    if (indice_z_seccion >= TAMANIO_CUADRICULA) {
        return 0;
    }

    indice_cuadricula = (indice_x_seccion + indice_z_seccion * TAMANIO_CUADRICULA);
    triangulos_num = cuadricula_colision[indice_cuadricula].triangulos_num;
    if (triangulos_num == 0) {
        return 0;
    }
    indice_seccion = cuadricula_colision[indice_cuadricula].triangulo;
    for (i = 0; i < triangulos_num; i++) {
        indice_malla = indices_colision[indice_seccion];
        if (malla_colision[indice_malla].flags & EJE_MIRANDO_Y) {
            if (indice_malla != rueda->indice_malla_colision) {
                if (comprobar_colision_zx(&colision, 5.0f, rueda_x, rueda_y, rueda_z, indice_malla) == 1) {
                    rueda->altura_base = calcular_altura_superficie(rueda_x, rueda_y, rueda_z, indice_malla);
                    rueda->tipo_superficie = malla_colision[indice_malla].tipo_superficie;
                    rueda->banderas_superficie = 0x40;
                    rueda->indice_malla_colision = indice_malla;
                    if (malla_colision[indice_malla].flags & 0x1000) {
                        rueda->desconocido_14 = 1;
                    } else {
                        rueda->desconocido_14 = 0;
                    }
                    return 1;
                }
            }
        } else if (malla_colision[indice_malla].flags & EJE_MIRANDO_X) {
            if ((malla_colision[indice_malla].normal_x != 1.0f) && (indice_malla != rueda->indice_malla_colision)) {
                if (comprobar_colision_zy(&colision, 5.0f, rueda_x, rueda_y, rueda_z, indice_malla) == 1) {
                    rueda->altura_base = calcular_altura_superficie(rueda_x, rueda_y, rueda_z, indice_malla);
                    rueda->tipo_superficie = malla_colision[indice_malla].tipo_superficie;
                    rueda->banderas_superficie = 0x80;
                    rueda->indice_malla_colision = indice_malla;
                    return 1;
                }
            }
        } else if ((malla_colision[indice_malla].normal_z != 1.0f) && (indice_malla != rueda->indice_malla_colision)) {
            if (comprobar_colision_yx(&colision, 5.0f, rueda_x, rueda_y, rueda_z, indice_malla) == 1) {
                rueda->altura_base = calcular_altura_superficie(rueda_x, rueda_y, rueda_z, indice_malla);
                rueda->tipo_superficie = malla_colision[indice_malla].tipo_superficie;
                rueda->banderas_superficie = 0x20;
                rueda->indice_malla_colision = indice_malla;
                return 1;
            }
        }
        indice_seccion++;
    }
    rueda->altura_base = rueda_y;
    rueda->tipo_superficie = 0;
}

s32 es_chocando_con_superficie_conducible(Colision* colision, f32 tamanio_caja_envolvente, f32 nuevo_x, f32 nuevo_y, f32 nuevo_z,
                                       u16 index, f32 viejo_x, f32 viejo_y, f32 viejo_z) {
    TrianguloColision* triangulo = &malla_colision[index];
    SIN_USO s32 relleno;
    f32 x4;
    SIN_USO f32 y4;
    f32 z4;
    f32 x3;
    SIN_USO f32 y3;
    f32 z3;
    f32 x2;
    SIN_USO f32 y2;
    f32 z2;
    f32 distancia_superficie;
    f32 temporal_;
    SIN_USO s32 relleno2[2];
    f32 area;
    f32 area2;
    f32 area3;
    s32 b = 1;

    if (triangulo->min_x > nuevo_x) {
        return 0;
    }
    if (triangulo->min_z > nuevo_z) {
        return 0;
    }
    if (triangulo->max_x < nuevo_x) {
        return 0;
    }
    if (triangulo->max_z < nuevo_z) {
        return 0;
    }
    if ((triangulo->min_y - tamanio_caja_envolvente * 3.0f) > nuevo_y) {
        return 0;
    }

    x2 = (f32) triangulo->vtx1->v.ob[0];
    z2 = (f32) triangulo->vtx1->v.ob[2];

    x3 = (f32) triangulo->vtx2->v.ob[0];
    z3 = (f32) triangulo->vtx2->v.ob[2];

    x4 = (f32) triangulo->vtx3->v.ob[0];
    z4 = (f32) triangulo->vtx3->v.ob[2];

    area = (z2 - nuevo_z) * (x3 - nuevo_x) - (x2 - nuevo_x) * (z3 - nuevo_z);

    if (area == 0) {
        area2 = (z3 - nuevo_z) * (x4 - nuevo_x) - (x3 - nuevo_x) * (z4 - nuevo_z);
        area3 = (z4 - nuevo_z) * (x2 - nuevo_x) - (x4 - nuevo_x) * (z2 - nuevo_z);
        if (area2 * area3 < 0.0f) {
            b = 0;
        }
    } else {

        area2 = (z3 - nuevo_z) * (x4 - nuevo_x) - (x3 - nuevo_x) * (z4 - nuevo_z);

        if (area2 == 0) {

            area3 = (z4 - nuevo_z) * (x2 - nuevo_x) - (x4 - nuevo_x) * (z2 - nuevo_z);

            if (area * area3 < 0.0f) {
                b = 0;
            }
        } else {
            if ((area * area2) < 0.0f) {
                b = 0;
            } else {
                area3 = (z4 - nuevo_z) * (x2 - nuevo_x) - (x4 - nuevo_x) * (z2 - nuevo_z);
                if (area3 != 0) {
                    if (area2 * area3 < 0.0f) {
                        b = 0;
                    }
                }
            }
        }
    }
    if (b == 0) {
        return 0;
    }

    distancia_superficie =
        (triangulo->normal_x * nuevo_x) + (triangulo->normal_y * nuevo_y) + (triangulo->normal_z * nuevo_z) + triangulo->distancia;

    if (distancia_superficie > tamanio_caja_envolvente) {
        if (colision->distancia_superficie[2] > distancia_superficie) {
            colision->unk34 = 1;
            colision->indice_zx_malla = index;
            colision->distancia_superficie[2] = distancia_superficie - tamanio_caja_envolvente;
            colision->vector_orientacion[0] = triangulo->normal_x;
            colision->vector_orientacion[1] = triangulo->normal_y;
            colision->vector_orientacion[2] = triangulo->normal_z;
        }
        return 0;
    }

    temporal_ = (triangulo->normal_x * viejo_x) + (triangulo->normal_y * viejo_y) + (triangulo->normal_z * viejo_z) + triangulo->distancia;

    if (temporal_ < 0.0f) {
        return 0;
    }

    colision->unk34 = 1;
    colision->indice_zx_malla = index;
    colision->distancia_superficie[2] = distancia_superficie - tamanio_caja_envolvente;
    colision->vector_orientacion[0] = triangulo->normal_x;
    colision->vector_orientacion[1] = triangulo->normal_y;
    colision->vector_orientacion[2] = triangulo->normal_z;
    return 1;
}
