// Paredes y triangulos

s32 es_chocando_con_pared_z(Colision* parametro, f32 tamanio_caja_envolvente, f32 x1, f32 y1, f32 z1, u16 indice_superficie, f32 pos_x,
                             f32 pos_y, f32 pos_z) {
    TrianguloColision* triangulo = &malla_colision[indice_superficie];
    SIN_USO s32 relleno[6];
    f32 x4;
    f32 y4;
    f32 x3;
    f32 y3;
    f32 x2;
    f32 y2;
    SIN_USO s32 relleno2[3];
    f32 distancia_a_superficie;
    f32 distancia_a_superficie_2;
    SIN_USO s32 relleno3[2];
    f32 area;
    f32 area2;
    f32 area3;
    s32 b = true;
    if (triangulo->min_x > x1) {
        return SIN_COLISION;
    }
    if (triangulo->max_x < x1) {
        return SIN_COLISION;
    }
    if (triangulo->max_y < y1) {
        return SIN_COLISION;
    }
    if (triangulo->min_y > y1) {
        return SIN_COLISION;
    }
    if ((triangulo->min_z - tamanio_caja_envolvente * 3.0f) > z1) {
        return SIN_COLISION;
    }
    if ((triangulo->max_z + tamanio_caja_envolvente * 3.0f) < z1) {
        return SIN_COLISION;
    }

    x2 = (f32) triangulo->vtx1->v.ob[0];
    y2 = (f32) triangulo->vtx1->v.ob[1];

    x3 = (f32) triangulo->vtx2->v.ob[0];
    y3 = (f32) triangulo->vtx2->v.ob[1];

    x4 = (f32) triangulo->vtx3->v.ob[0];
    y4 = (f32) triangulo->vtx3->v.ob[1];

    area = (y2 - y1) * (x3 - x1) - (x2 - x1) * (y3 - y1);

    if (area == 0) {
        area2 = (y3 - y1) * (x4 - x1) - (x3 - x1) * (y4 - y1);
        area3 = (y4 - y1) * (x2 - x1) - (x4 - x1) * (y2 - y1);

        if (area2 * area3 < 0.0f) {
            b = false;
        }
    } else {

        area2 = (y3 - y1) * (x4 - x1) - (x3 - x1) * (y4 - y1);

        if (area2 == 0) {
            area3 = (y4 - y1) * (x2 - x1) - (x4 - x1) * (y2 - y1);

            if ((area * area3) < 0.0f) {
                b = false;
            }
        } else {
            if ((area * area2) < 0.0f) {
                b = false;
            } else {
                area3 = (y4 - y1) * (x2 - x1) - (x4 - x1) * (y2 - y1);

                if (area3 != 0) {
                    if ((area2 * area3) < 0.0f) {
                        b = false;
                    }
                }
            }
        }
    }

    if (!b) {
        return SIN_COLISION;
    }

    distancia_a_superficie =
        ((triangulo->normal_x * x1) + (triangulo->normal_y * y1) + (triangulo->normal_z * z1)) + triangulo->distancia;
    if (triangulo->flags & 0x200) {
        distancia_a_superficie_2 =
            ((triangulo->normal_x * pos_x) + (triangulo->normal_y * pos_y) + (triangulo->normal_z * pos_z)) + triangulo->distancia;
        if ((distancia_a_superficie > 0.0f) && (distancia_a_superficie_2 > 0.0f)) {
            if (distancia_a_superficie < tamanio_caja_envolvente) {
                parametro->desconocido30 = 1;
                parametro->indice_yx_malla = indice_superficie;
                parametro->distancia_superficie[0] = distancia_a_superficie - tamanio_caja_envolvente;
                parametro->desconocido48[0] = triangulo->normal_x;
                parametro->desconocido48[1] = triangulo->normal_y;
                parametro->desconocido48[2] = triangulo->normal_z;
                return COLISION;
            }
            return SIN_COLISION;
        }

        if ((distancia_a_superficie < 0.0f) && (distancia_a_superficie_2 < 0.0f)) {
            distancia_a_superficie *= -1.0f;
            if (distancia_a_superficie < tamanio_caja_envolvente) {
                parametro->desconocido30 = 1;
                parametro->indice_yx_malla = indice_superficie;
                parametro->distancia_superficie[0] = distancia_a_superficie - tamanio_caja_envolvente;
                parametro->desconocido48[0] = -triangulo->normal_x;
                parametro->desconocido48[1] = -triangulo->normal_y;
                parametro->desconocido48[2] = -triangulo->normal_z;
                return 1;
            }
            return SIN_COLISION;
        }
        if ((distancia_a_superficie > 0.0f) && (distancia_a_superficie_2 < 0.0f)) {
            parametro->desconocido30 = 1;
            parametro->indice_yx_malla = indice_superficie;
            parametro->distancia_superficie[0] = -(distancia_a_superficie + tamanio_caja_envolvente);
            parametro->desconocido48[0] = -triangulo->normal_x;
            parametro->desconocido48[1] = -triangulo->normal_y;
            parametro->desconocido48[2] = -triangulo->normal_z;
            return COLISION;
        }
        if ((distancia_a_superficie < 0.0f) && (distancia_a_superficie_2 > 0.0f)) {
            parametro->desconocido30 = 1;
            parametro->indice_yx_malla = indice_superficie;
            parametro->distancia_superficie[0] = distancia_a_superficie + tamanio_caja_envolvente;
            parametro->desconocido48[0] = triangulo->normal_x;
            parametro->desconocido48[1] = triangulo->normal_y;
            parametro->desconocido48[2] = triangulo->normal_z;
            return COLISION;
        }
        if (distancia_a_superficie == 0.0f) {
            if (distancia_a_superficie_2 >= 0.0f) {
                parametro->desconocido30 = 1;
                parametro->indice_yx_malla = indice_superficie;
                parametro->distancia_superficie[0] = distancia_a_superficie_2 + tamanio_caja_envolvente;
                parametro->desconocido48[0] = triangulo->normal_x;
                parametro->desconocido48[1] = triangulo->normal_y;
                parametro->desconocido48[2] = triangulo->normal_z;
                return COLISION;
            }
            parametro->desconocido30 = 1;
            parametro->indice_yx_malla = indice_superficie;
            parametro->distancia_superficie[0] = -(distancia_a_superficie_2 + tamanio_caja_envolvente);
            parametro->desconocido48[0] = triangulo->normal_x;
            parametro->desconocido48[1] = triangulo->normal_y;
            parametro->desconocido48[2] = triangulo->normal_z;
            return COLISION;
        }
        return SIN_COLISION;
    }
    if (distancia_a_superficie > tamanio_caja_envolvente) {
        if (distancia_a_superficie < parametro->distancia_superficie[0]) {
            parametro->desconocido30 = 1;
            parametro->indice_yx_malla = indice_superficie;
            parametro->distancia_superficie[0] = distancia_a_superficie - tamanio_caja_envolvente;
            parametro->desconocido48[0] = triangulo->normal_x;
            parametro->desconocido48[1] = triangulo->normal_y;
            parametro->desconocido48[2] = triangulo->normal_z;
        }
        return SIN_COLISION;
    }

    distancia_a_superficie_2 =
        (triangulo->normal_x * pos_x) + (triangulo->normal_y * pos_y) + (triangulo->normal_z * pos_z) + triangulo->distancia;
    if (distancia_a_superficie_2 < 0.0f) {
        return SIN_COLISION;
    }
    parametro->desconocido30 = 1;
    parametro->indice_yx_malla = indice_superficie;
    parametro->distancia_superficie[0] = distancia_a_superficie - tamanio_caja_envolvente;
    parametro->desconocido48[0] = triangulo->normal_x;
    parametro->desconocido48[1] = triangulo->normal_y;
    parametro->desconocido48[2] = triangulo->normal_z;
    return COLISION;
}

s32 es_chocando_con_pared_x(Colision* parametro, f32 tamanio_caja_envolvente, f32 x1, f32 y1, f32 z1, u16 indice_superficie, f32 pos_x,
                             f32 pos_y, f32 pos_z) {
    TrianguloColision* triangulo = &malla_colision[indice_superficie];
    s32 b = 1;
    SIN_USO s32 relleno[7];
    f32 y4;
    f32 z4;
    f32 y3;
    f32 z3;
    f32 y2;
    f32 z2;
    SIN_USO s32 relleno3[2];
    f32 distancia_a_superficie;
    f32 distancia_a_superficie_2;
    SIN_USO s32 relleno4[2];
    f32 area;
    f32 area2;
    f32 area3;

    if (triangulo->min_z > z1) {
        return SIN_COLISION;
    }
    if (triangulo->max_z < z1) {
        return SIN_COLISION;
    }
    if (triangulo->max_y < y1) {
        return SIN_COLISION;
    }
    if (triangulo->min_y > y1) {
        return SIN_COLISION;
    }
    if ((triangulo->min_x - tamanio_caja_envolvente * 3.0f) > x1) {
        return SIN_COLISION;
    }
    if ((triangulo->max_x + tamanio_caja_envolvente * 3.0f) < x1) {
        return SIN_COLISION;
    }

    z2 = (f32) triangulo->vtx1->v.ob[2];
    y2 = (f32) triangulo->vtx1->v.ob[1];

    z3 = (f32) triangulo->vtx2->v.ob[2];
    y3 = (f32) triangulo->vtx2->v.ob[1];

    z4 = (f32) triangulo->vtx3->v.ob[2];
    y4 = (f32) triangulo->vtx3->v.ob[1];

    area = (y2 - y1) * (z3 - z1) - (z2 - z1) * (y3 - y1);

    if (area == 0) {
        area2 = (y3 - y1) * (z4 - z1) - (z3 - z1) * (y4 - y1);
        area3 = (y4 - y1) * (z2 - z1) - (z4 - z1) * (y2 - y1);

        if (area2 * area3 < 0.0f) {
            b = 0;
        }
    } else {

        area2 = (y3 - y1) * (z4 - z1) - (z3 - z1) * (y4 - y1);

        if (area2 == 0) {
            area3 = (y4 - y1) * (z2 - z1) - (z4 - z1) * (y2 - y1);

            if ((area * area3) < 0.0f) {
                b = 0;
            }
        } else {
            if ((area * area2) < 0.0f) {
                b = 0;
            } else {
                area3 = (y4 - y1) * (z2 - z1) - (z4 - z1) * (y2 - y1);

                if (area3 != 0) {
                    if ((area2 * area3) < 0.0f) {
                        b = 0;
                    }
                }
            }
        }
    }
    if (b == 0) {
        return SIN_COLISION;
    }

    distancia_a_superficie =
        ((triangulo->normal_x * x1) + (triangulo->normal_y * y1) + (triangulo->normal_z * z1)) + triangulo->distancia;
    if (triangulo->flags & 0x200) {
        distancia_a_superficie_2 =
            ((triangulo->normal_x * pos_x) + (triangulo->normal_y * pos_y) + (triangulo->normal_z * pos_z)) + triangulo->distancia;
        if ((distancia_a_superficie > 0.0f) && (distancia_a_superficie_2 > 0.0f)) {
            if (distancia_a_superficie < tamanio_caja_envolvente) {
                parametro->desconocido32 = 1;
                parametro->indice_zy_malla = indice_superficie;
                parametro->distancia_superficie[1] = distancia_a_superficie - tamanio_caja_envolvente;
                parametro->desconocido54[0] = triangulo->normal_x;
                parametro->desconocido54[1] = triangulo->normal_y;
                parametro->desconocido54[2] = triangulo->normal_z;
                return COLISION;
            }
            return SIN_COLISION;
        }

        if ((distancia_a_superficie < 0.0f) && (distancia_a_superficie_2 < 0.0f)) {
            distancia_a_superficie *= -1.0f;
            if (distancia_a_superficie < tamanio_caja_envolvente) {
                parametro->desconocido32 = 1;
                parametro->indice_zy_malla = indice_superficie;
                parametro->distancia_superficie[1] = distancia_a_superficie - tamanio_caja_envolvente;
                parametro->desconocido54[0] = -triangulo->normal_x;
                parametro->desconocido54[1] = -triangulo->normal_y;
                parametro->desconocido54[2] = -triangulo->normal_z;
                return 1;
            }
            return SIN_COLISION;
        }
        if ((distancia_a_superficie > 0.0f) && (distancia_a_superficie_2 < 0.0f)) {
            parametro->desconocido32 = 1;
            parametro->indice_zy_malla = indice_superficie;
            parametro->distancia_superficie[1] = -(distancia_a_superficie + tamanio_caja_envolvente);
            parametro->desconocido54[0] = -triangulo->normal_x;
            parametro->desconocido54[1] = -triangulo->normal_y;
            parametro->desconocido54[2] = -triangulo->normal_z;
            return COLISION;
        }
        if ((distancia_a_superficie < 0.0f) && (distancia_a_superficie_2 > 0.0f)) {
            parametro->desconocido32 = 1;
            parametro->indice_zy_malla = indice_superficie;
            parametro->distancia_superficie[1] = distancia_a_superficie + tamanio_caja_envolvente;
            parametro->desconocido54[0] = triangulo->normal_x;
            parametro->desconocido54[1] = triangulo->normal_y;
            parametro->desconocido54[2] = triangulo->normal_z;
            return COLISION;
        }
        if (distancia_a_superficie == 0.0f) {
            if (distancia_a_superficie_2 >= 0.0f) {
                parametro->desconocido32 = 1;
                parametro->indice_zy_malla = indice_superficie;
                parametro->distancia_superficie[1] = distancia_a_superficie_2 + tamanio_caja_envolvente;
                parametro->desconocido54[0] = triangulo->normal_x;
                parametro->desconocido54[1] = triangulo->normal_y;
                parametro->desconocido54[2] = triangulo->normal_z;
                return COLISION;
            }
            parametro->desconocido32 = 1;
            parametro->indice_zy_malla = indice_superficie;
            parametro->distancia_superficie[1] = -(distancia_a_superficie_2 + tamanio_caja_envolvente);
            parametro->desconocido54[0] = triangulo->normal_x;
            parametro->desconocido54[1] = triangulo->normal_y;
            parametro->desconocido54[2] = triangulo->normal_z;
            return COLISION;
        }
        return SIN_COLISION;
    }
    if (distancia_a_superficie > tamanio_caja_envolvente) {
        if (parametro->distancia_superficie[1] > distancia_a_superficie) {
            parametro->desconocido32 = 1;
            parametro->indice_zy_malla = indice_superficie;
            parametro->distancia_superficie[1] = distancia_a_superficie - tamanio_caja_envolvente;
            parametro->desconocido54[0] = triangulo->normal_x;
            parametro->desconocido54[1] = triangulo->normal_y;
            parametro->desconocido54[2] = triangulo->normal_z;
        }
        return SIN_COLISION;
    }

    distancia_a_superficie_2 =
        (triangulo->normal_x * pos_x) + (triangulo->normal_y * pos_y) + (triangulo->normal_z * pos_z) + triangulo->distancia;
    if (distancia_a_superficie_2 < 0.0f) {
        return SIN_COLISION;
    }
    parametro->desconocido32 = 1;
    parametro->indice_zy_malla = indice_superficie;
    parametro->distancia_superficie[1] = distancia_a_superficie - tamanio_caja_envolvente;
    parametro->desconocido54[0] = triangulo->normal_x;
    parametro->desconocido54[1] = triangulo->normal_y;
    parametro->desconocido54[2] = triangulo->normal_z;
    return COLISION;
}

u16 colision_terreno_actor(Colision* colision, f32 tamanio_caja_envolvente, f32 nuevo_x, f32 nuevo_y, f32 nuevo_z, f32 viejo_x, f32 viejo_y,
                            f32 viejo_z) {
    s32 longitud_x_circuito;
    s32 longitud_z_circuito;
    s16 indice_x_seccion;
    s16 indice_z_seccion;
    u16 triangulos_num;
    u16 indice_colision;
    s16 indice_cuadricula;

    u16 indice_seccion;

    u16 banderas = 0;
    s32 seccion_x;
    s32 seccion_z;

    u16 i;

    colision->desconocido30 = 0;
    colision->desconocido32 = 0;
    colision->unk34 = 0;
    colision->distancia_superficie[0] = 1000.0f;
    colision->distancia_superficie[1] = 1000.0f;
    colision->distancia_superficie[2] = 1000.0f;

    if ((s32) colision->indice_zx_malla < (s32) cantidad_malla_colision) {
        if (es_chocando_con_superficie_conducible(colision, tamanio_caja_envolvente, nuevo_x, nuevo_y, nuevo_z, colision->indice_zx_malla,
                                               viejo_x, viejo_y, viejo_z) == COLISION) {
            banderas |= EJE_MIRANDO_Y;
        }
    }

    if ((s32) colision->indice_yx_malla < (s32) cantidad_malla_colision) {
        if (es_chocando_con_pared_z(colision, tamanio_caja_envolvente, nuevo_x, nuevo_y, nuevo_z, colision->indice_yx_malla, viejo_x, viejo_y,
                                     viejo_z) == COLISION) {
            banderas |= EJE_MIRANDO_Z;
        }
    }

    if ((s32) colision->indice_zy_malla < (s32) cantidad_malla_colision) {
        if (es_chocando_con_pared_x(colision, tamanio_caja_envolvente, nuevo_x, nuevo_y, nuevo_z, colision->indice_zy_malla, viejo_x, viejo_y,
                                     viejo_z) == COLISION) {
            banderas |= EJE_MIRANDO_X;
        }
    }

    if (banderas == (EJE_MIRANDO_Y | EJE_MIRANDO_Z | EJE_MIRANDO_X)) {
        return banderas;
    }

    longitud_x_circuito = (s32) max_x_circuito - min_x_circuito;
    longitud_z_circuito = (s32) max_z_circuito - min_z_circuito;

    seccion_x = longitud_x_circuito / TAMANIO_CUADRICULA;
    seccion_z = longitud_z_circuito / TAMANIO_CUADRICULA;

    indice_x_seccion = (nuevo_x - min_x_circuito) / seccion_x;
    indice_z_seccion = (nuevo_z - min_z_circuito) / seccion_z;

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
        return banderas;
    }

    indice_seccion = cuadricula_colision[indice_cuadricula].triangulo;

    for (i = 0; i < triangulos_num; i++) {
        if (banderas == (EJE_MIRANDO_Y | EJE_MIRANDO_Z | EJE_MIRANDO_X)) {
            return banderas;
        }

        indice_colision = indices_colision[indice_seccion];

        if ((malla_colision[indice_colision].flags & EJE_MIRANDO_Y)) {
            if ((banderas & EJE_MIRANDO_Y) == 0) {
                if (indice_colision != colision->indice_zx_malla) {
                    if (es_chocando_con_superficie_conducible(colision, tamanio_caja_envolvente, nuevo_x, nuevo_y, nuevo_z, indice_colision,
                                                           viejo_x, viejo_y, viejo_z) == COLISION) {
                        banderas |= EJE_MIRANDO_Y;
                    }
                }
            }
        } else if ((malla_colision[indice_colision].flags & EJE_MIRANDO_X) != 0) {
            if ((banderas & EJE_MIRANDO_X) == 0) {
                if (indice_colision != colision->indice_zy_malla) {
                    if (es_chocando_con_pared_x(colision, tamanio_caja_envolvente, nuevo_x, nuevo_y, nuevo_z, indice_colision, viejo_x,
                                                 viejo_y, viejo_z) == COLISION) {
                        banderas |= EJE_MIRANDO_X;
                    }
                }
            }
        } else if ((banderas & EJE_MIRANDO_Z) == 0) {
            if (indice_colision != colision->indice_yx_malla) {
                if (es_chocando_con_pared_z(colision, tamanio_caja_envolvente, nuevo_x, nuevo_y, nuevo_z, indice_colision, viejo_x, viejo_y,
                                             viejo_z) == COLISION) {
                    banderas |= EJE_MIRANDO_Z;
                }
            }
        }
        indice_seccion++;
    }
    return banderas;
}

u16 comprobar_colision_envolvente(Colision* colision, f32 tamanio_caja_envolvente, f32 pos_x, f32 pos_y, f32 pos_z) {
    u16 triangulos_num;
    s32 longitud_x_circuito;
    s32 longitud_z_circuito;
    u16 indice_malla;
    s32 seccion_x;
    s32 seccion_z;
    s16 indice_x_seccion;
    s16 indice_z_seccion;
    s16 indice_cuadricula;
    u16 i;

    u16 indice_seccion;
    u16 banderas;

    colision->desconocido30 = 0;
    colision->desconocido32 = 0;
    colision->unk34 = 0;
    colision->distancia_superficie[0] = 1000.0f;
    colision->distancia_superficie[1] = 1000.0f;
    colision->distancia_superficie[2] = 1000.0f;
    banderas = 0;
    if (colision->indice_zx_malla < cantidad_malla_colision) {
        if (comprobar_colision_zx(colision, tamanio_caja_envolvente, pos_x, pos_y, pos_z, colision->indice_zx_malla) == 1) {
            banderas |= EJE_MIRANDO_Y;
        }
    }
    if (colision->indice_yx_malla < cantidad_malla_colision) {
        if (comprobar_colision_yx(colision, tamanio_caja_envolvente, pos_x, pos_y, pos_z, colision->indice_yx_malla) == 1) {
            banderas |= EJE_MIRANDO_Z;
        }
    }
    if (colision->indice_zy_malla < cantidad_malla_colision) {
        if (comprobar_colision_zy(colision, tamanio_caja_envolvente, pos_x, pos_y, pos_z, colision->indice_zy_malla) == 1) {
            banderas |= EJE_MIRANDO_X;
        }
    }
    if (banderas == (EJE_MIRANDO_Y | EJE_MIRANDO_Z | EJE_MIRANDO_X)) {
        return banderas;
    }

    longitud_x_circuito = (s32) max_x_circuito - min_x_circuito;
    longitud_z_circuito = (s32) max_z_circuito - min_z_circuito;

    seccion_x = longitud_x_circuito / TAMANIO_CUADRICULA;
    seccion_z = longitud_z_circuito / TAMANIO_CUADRICULA;

    indice_x_seccion = (pos_x - min_x_circuito) / seccion_x;
    indice_z_seccion = (pos_z - min_z_circuito) / seccion_z;

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

    indice_cuadricula = indice_x_seccion + indice_z_seccion * TAMANIO_CUADRICULA;
    triangulos_num = cuadricula_colision[indice_cuadricula].triangulos_num;
    if (triangulos_num == 0) {
        return banderas;
    }
    indice_seccion = cuadricula_colision[indice_cuadricula].triangulo;

    for (i = 0; i < triangulos_num; i++) {
        if (banderas == (EJE_MIRANDO_X | EJE_MIRANDO_Y | EJE_MIRANDO_Z)) {
            return banderas;
        }
        indice_malla = indices_colision[indice_seccion];
        if (malla_colision[indice_malla].flags & EJE_MIRANDO_Y) {
            if (!(banderas & EJE_MIRANDO_Y)) {
                if (indice_malla != colision->indice_zx_malla) {
                    if (comprobar_colision_zx(colision, tamanio_caja_envolvente, pos_x, pos_y, pos_z, indice_malla) == 1) {
                        banderas |= EJE_MIRANDO_Y;
                    }
                }
            }
        } else if (malla_colision[indice_malla].flags & EJE_MIRANDO_X) {
            if (!(banderas & EJE_MIRANDO_X)) {
                if (indice_malla != colision->indice_zy_malla) {
                    if (comprobar_colision_zy(colision, tamanio_caja_envolvente, pos_x, pos_y, pos_z, indice_malla) == 1) {
                        banderas |= EJE_MIRANDO_X;
                    }
                }
            }
        } else {
            if (!(banderas & EJE_MIRANDO_Z)) {
                if (indice_malla != colision->indice_yx_malla) {
                    if (comprobar_colision_yx(colision, tamanio_caja_envolvente, pos_x, pos_y, pos_z, indice_malla) == 1) {
                        banderas |= EJE_MIRANDO_Z;
                    }
                }
            }
        }
        indice_seccion++;
    }
    return banderas;
}

extern u8 D_8014F1110;

f32 obtener_altura_superficie(f32 pos_x, f32 pos_y, f32 pos_z) {
    f32 altura;
    s16 indice_x_seccion;
    s16 indice_z_seccion;
    s16 seccion_cuadricula;

    u16 index;
    u16 triangulos_num;
    u16 indice_seccion;
    f32 phi_f20 = -3000.0f;
    u16 i;

    s32 longitud_x_circuito;
    s32 longitud_z_circuito;
    s32 seccion_x;
    s32 seccion_z;

    longitud_x_circuito = (max_x_circuito - min_x_circuito);
    longitud_z_circuito = (max_z_circuito - min_z_circuito);
    seccion_x = longitud_x_circuito / TAMANIO_CUADRICULA;
    seccion_z = longitud_z_circuito / TAMANIO_CUADRICULA;

    indice_x_seccion = (s16) ((pos_x - min_x_circuito) / seccion_x);
    indice_z_seccion = (s16) ((pos_z - min_z_circuito) / seccion_z);
    seccion_cuadricula = indice_x_seccion + (indice_z_seccion * TAMANIO_CUADRICULA);
    triangulos_num = cuadricula_colision[seccion_cuadricula].triangulos_num;

    if (indice_x_seccion < 0) {
        return 3000.0f;
    }
    if (indice_z_seccion < 0) {
        return 3000.0f;
    }
    if (indice_x_seccion >= TAMANIO_CUADRICULA) {
        return 3000.0f;
    }
    if (indice_z_seccion >= TAMANIO_CUADRICULA) {
        return 3000.0f;
    }
    if (triangulos_num == 0) {
        return 3000.0f;
    }

    indice_seccion = cuadricula_colision[seccion_cuadricula].triangulo;

    for (i = 0; i < triangulos_num; i++) {

        index = indices_colision[indice_seccion];

        if ((malla_colision[index].flags & EJE_MIRANDO_Y) &&
            (comprobar_chocando_horizontalmente_con_triangulo(pos_x, pos_z, index) == 1)) {
            altura = calcular_altura_superficie(pos_x, pos_y, pos_z, index);
            if ((altura <= pos_y) && (phi_f20 < altura)) {
                phi_f20 = altura;
            }
        }
        indice_seccion++;
    }
    return phi_f20;
}

#define MAX3(a, b, c, salida) \
    if (a >= b) {          \
        if (a >= c) {      \
            salida = a;       \
        } else             \
            salida = c;       \
                           \
    } else if (b >= c) {   \
        salida = b;           \
    } else                 \
        salida = c;

#define MIN3(a, b, c, salida) \
    if (a <= b) {          \
        if (a <= c) {      \
            salida = a;       \
        } else             \
            salida = c;       \
                           \
    } else if (b <= c) {   \
        salida = b;           \
    } else                 \
        salida = c;

void agregar_triangulo_colision(Vtx* vtx1, Vtx* vtx2, Vtx* vtx3, s8 tipo_superficie, u16 id_seccion) {
    TrianguloColision* triangulo = &malla_colision[cantidad_malla_colision];
    s16 x2;
    s16 z2;
    u16 vtx_1_bandera;
    s16 x3;
    s16 x1;
    s16 y1;
    s16 z1;
    u16 vtx_2_bandera;
    s16 y2;
    u16 vtx_3_bandera;
    u16 banderas;
    s16 y3;
    s16 z3;

    SIN_USO s32 relleno2[7];

    f64 producto_x_cruce;
    f64 producto_y_cruce;
    f64 producto_z_cruce;
    f64 magnitud;

    SIN_USO s32 relleno3[3];

    f32 normal_x;
    f32 normal_y;
    f32 normal_z;
    f32 distancia;

    s16 max_x;
    s16 max_z;
    s16 min_y;
    s16 min_x;
    s16 max_y;
    s16 min_z;

    triangulo->vtx1 = vtx1;
    triangulo->vtx2 = vtx2;
    triangulo->vtx3 = vtx3;
    if ((triangulo->vtx1->v.flag == 4) && (triangulo->vtx2->v.flag == 4) && (triangulo->vtx3->v.flag == 4)) {

        return;
    }

    x1 = triangulo->vtx1->v.ob[0];
    y1 = triangulo->vtx1->v.ob[1];
    z1 = triangulo->vtx1->v.ob[2];
    x2 = triangulo->vtx2->v.ob[0];
    y2 = triangulo->vtx2->v.ob[1];
    z2 = triangulo->vtx2->v.ob[2];
    x3 = triangulo->vtx3->v.ob[0];
    y3 = triangulo->vtx3->v.ob[1];
    z3 = triangulo->vtx3->v.ob[2];
    if ((x1 == x2) && (z1 == z2)) {
        triangulo->vtx1 = vtx1;
        triangulo->vtx3 = vtx2;
        triangulo->vtx2 = vtx3;
        x1 = triangulo->vtx1->v.ob[0];
        y1 = triangulo->vtx1->v.ob[1];
        z1 = triangulo->vtx1->v.ob[2];
        x2 = triangulo->vtx3->v.ob[0];
        y2 = triangulo->vtx3->v.ob[1];
        z2 = triangulo->vtx3->v.ob[2];
        x3 = triangulo->vtx2->v.ob[0];
        y3 = triangulo->vtx2->v.ob[1];
        z3 = triangulo->vtx2->v.ob[2];
    }
    MAX3(x1, x2, x3, max_x)

    MAX3(z1, z2, z3, max_z)

    MAX3(y1, y2, y3, max_y)

    MIN3(x1, x2, x3, min_x)

    MIN3(y1, y2, y3, min_y)

    MIN3(z1, z2, z3, min_z)

    producto_x_cruce = (((y2 - y1) * (z3 - z2)) - ((z2 - z1) * (y3 - y2)));
    producto_y_cruce = (((z2 - z1) * (x3 - x2)) - ((x2 - x1) * (z3 - z2)));
    producto_z_cruce = (((x2 - x1) * (y3 - y2)) - ((y2 - y1) * (x3 - x2)));

    magnitud =
        sqrtf((producto_x_cruce * producto_x_cruce) + (producto_y_cruce * producto_y_cruce) + (producto_z_cruce * producto_z_cruce));

    if (!magnitud) {
        return;
    }

    normal_x = (f32) producto_x_cruce / magnitud;
    normal_y = (f32) producto_y_cruce / magnitud;
    normal_z = (f32) producto_z_cruce / magnitud;

    distancia = -((normal_x * x1) + (normal_y * y1) + (normal_z * z1));

    if (dato_8015F59C) {
        if (normal_y < -0.9f) {
            return;
        } else if (normal_y > 0.9f) {
            return;
        }
    }

    if (dato_8015F5A0) {
        if ((normal_y < 0.1f) && (normal_y > -0.1f)) {
            return;
        }
    }

    triangulo->max_x = max_x;
    triangulo->max_z = max_z;
    triangulo->min_x = min_x;
    triangulo->min_z = min_z;
    triangulo->min_y = min_y;
    triangulo->max_y = max_y;

    if (min_x < min_x_circuito) {
        min_x_circuito = min_x;
    }
    if (min_y < min_y_circuito) {
        min_y_circuito = min_y;
    }
    if (min_z < min_z_circuito) {
        min_z_circuito = min_z;
    }
    if (max_x > max_x_circuito) {
        max_x_circuito = max_x;
    }
    if (max_y > max_y_circuito) {
        max_y_circuito = max_y;
    }
    if (max_z > max_z_circuito) {
        max_z_circuito = max_z;
    }

    triangulo->normal_x = normal_x;
    triangulo->normal_y = normal_y;
    triangulo->normal_z = normal_z;
    triangulo->distancia = distancia;

    triangulo->tipo_superficie = (u16) tipo_superficie;

    producto_x_cruce = producto_x_cruce * producto_x_cruce;
    producto_y_cruce = producto_y_cruce * producto_y_cruce;
    producto_z_cruce = producto_z_cruce * producto_z_cruce;

    dato_8015F6FA = 0;
    dato_8015F6FC = 0;

    vtx_1_bandera = triangulo->vtx1->v.flag;
    vtx_2_bandera = triangulo->vtx2->v.flag;
    vtx_3_bandera = triangulo->vtx3->v.flag;

    banderas = id_seccion;

    if ((vtx_1_bandera == 1) && (vtx_2_bandera == 1) && (vtx_3_bandera == 1)) {
        banderas |= 0x400;
    } else if ((vtx_1_bandera == 2) && (vtx_2_bandera == 2) && (vtx_3_bandera == 2)) {
        banderas |= 0x800;
    } else if ((vtx_1_bandera == 3) && (vtx_2_bandera == 3) && (vtx_3_bandera == 3)) {
        banderas |= 0x1000;
    } else if (dato_8015F5A4 != 0) {
        banderas |= 0x200;
    }

    triangulo->flags = banderas;

    if ((producto_x_cruce <= producto_y_cruce) && (producto_y_cruce >= producto_z_cruce)) {
        triangulo->flags |= EJE_MIRANDO_Y;
    } else if ((producto_x_cruce > producto_y_cruce) && (producto_x_cruce >= producto_z_cruce)) {
        triangulo->flags |= EJE_MIRANDO_X;
    } else {
        triangulo->flags |= EJE_MIRANDO_Z;
    }
    cantidad_malla_colision++;
}

void fijar_vtx_desde_triangulo(u32 triangulo, s8 tipo_superficie, u16 id_seccion) {
    u32 vert1 = ((triangulo & 0x00FF0000) >> 16) / 2;
    u32 vert2 = ((triangulo & 0x0000FF00) >> 8) / 2;
    u32 vert3 = (triangulo & 0x000000FF) / 2;

    Vtx* vtx1 = vtx_buffer[vert1];
    Vtx* vtx2 = vtx_buffer[vert2];
    Vtx* vtx3 = vtx_buffer[vert3];

    agregar_triangulo_colision(vtx1, vtx2, vtx3, tipo_superficie, id_seccion);
}

void fijar_vtx_desde_tri2(u32 triangulo1, u32 triangulo2, s8 tipo_superficie, u16 id_seccion) {
    SIN_USO s32 relleno[2];
    u32 vert1 = ((triangulo1 & 0x00FF0000) >> 16) / 2;
    u32 vert2 = ((triangulo1 & 0x0000FF00) >> 8) / 2;
    u32 vert3 = (triangulo1 & 0x000000FF) / 2;

    u32 vert4 = ((triangulo2 & 0x00FF0000) >> 16) / 2;
    u32 vert5 = ((triangulo2 & 0x0000FF00) >> 8) / 2;
    u32 vert6 = (triangulo2 & 0x000000FF) / 2;

    Vtx* vtx1 = vtx_buffer[vert1];
    Vtx* vtx2 = vtx_buffer[vert2];
    Vtx* vtx3 = vtx_buffer[vert3];

    Vtx* vtx4 = vtx_buffer[vert4];
    Vtx* vtx5 = vtx_buffer[vert5];
    Vtx* vtx6 = vtx_buffer[vert6];

    agregar_triangulo_colision(vtx1, vtx2, vtx3, tipo_superficie, id_seccion);
    agregar_triangulo_colision(vtx4, vtx5, vtx6, tipo_superficie, id_seccion);
}
