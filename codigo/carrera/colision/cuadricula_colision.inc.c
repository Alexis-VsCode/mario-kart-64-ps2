// Cuadricula colision

void fijar_vtx_desde_cuadrangulo(u32 line, s8 tipo_superficie, u16 id_seccion) {
    SIN_USO s32 relleno[6];
    Vtx* vtx1;
    Vtx* vtx2;
    Vtx* vtx3;
    Vtx* vtx4;

    u32 vert1 = ((line & 0x00FF0000) >> 16) / 2;
    u32 vert2 = ((line & 0x0000FF00) >> 8) / 2;
    u32 vert3 = (line & 0x000000FF) / 2;
    u32 vert4 = ((line & 0xFF000000) >> 24) / 2;

    vtx1 = vtx_buffer[vert1];
    vtx2 = vtx_buffer[vert2];
    vtx3 = vtx_buffer[vert3];
    vtx4 = vtx_buffer[vert4];

    agregar_triangulo_colision(vtx1, vtx2, vtx3, tipo_superficie, id_seccion);
    agregar_triangulo_colision(vtx1, vtx3, vtx4, tipo_superficie, id_seccion);
}

void fijar_buffer_vtx(uintptr_t direccion, u32 num_vertices, u32 indice_buffer) {
    u32 i;
    u32 segmento = SEGMENT_NUMBER2(direccion);
    u32 desplazamiento = SEGMENT_OFFSET(direccion);
    Vtx* vtx = (Vtx*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    for (i = 0; i < num_vertices; i++) {
        vtx_buffer[indice_buffer] = vtx;
        vtx++;
        indice_buffer++;
    }
}
s32 es_rectangulo_intersecando_linea(s16 min_x, s16 max_x, s16 min_z, s16 max_z, s16 x1, s16 z1, s16 x2, s16 z2) {
    f32 desplazamiento_x;
    f32 punto_proyectado;
    f32 desplazamiento_z;

    desplazamiento_x = x2 - x1;
    desplazamiento_z = z2 - z1;
    if (desplazamiento_x == 0.0f) {
        if (x1 < min_x) {
            return 0;
        }
        if (max_x < x1) {
            return 0;
        }
        if (desplazamiento_z > 0.0f) {
            if ((z1 < min_z) && (max_z < z2)) {
                return 1;
            }
        } else if ((z2 < min_z) && (max_z < z1)) {
            return 1;
        }
    } else {
        if (desplazamiento_z == 0.0f) {
            if (z1 < min_z) {
                return 0;
            }
            if (max_z < z1) {
                return 0;
            }
            if (desplazamiento_x > 0.0f) {
                if ((x1 < min_x) && (max_x < x2)) {
                    return 1;
                }
            } else if ((x2 < min_x) && (max_x < x1)) {
                return 1;
            }
        } else {
            punto_proyectado = ((desplazamiento_x / desplazamiento_z) * (min_z - z1)) + x1;
            if ((min_x <= punto_proyectado) && (punto_proyectado <= max_x)) {
                return 1;
            }
            punto_proyectado = ((desplazamiento_x / desplazamiento_z) * (max_z - z1)) + x1;
            if ((min_x <= punto_proyectado) && (punto_proyectado <= max_x)) {
                return 1;
            }
            punto_proyectado = ((desplazamiento_z / desplazamiento_x) * (min_x - x1)) + z1;
            if ((min_z <= punto_proyectado) && (punto_proyectado <= max_z)) {
                return 1;
            }
            punto_proyectado = ((desplazamiento_z / desplazamiento_x) * (max_x - x1)) + z1;
            if ((min_z <= punto_proyectado) && (punto_proyectado <= max_z)) {
                return 1;
            }
        }
    }
    return 0;
}

s32 es_triangulo_intersecando_envolvente_caja(s16 min_x, s16 max_x, s16 min_z, s16 max_z, u16 index) {
    TrianguloColision* triangulo = &malla_colision[index];
    s16 x1;
    s16 z1;
    s16 x2;
    s16 z2;
    s16 x3;
    s16 z3;

    x1 = triangulo->vtx1->v.ob[0];
    z1 = triangulo->vtx1->v.ob[2];
    x2 = triangulo->vtx2->v.ob[0];
    z2 = triangulo->vtx2->v.ob[2];
    x3 = triangulo->vtx3->v.ob[0];
    z3 = triangulo->vtx3->v.ob[2];
    if ((x1 >= min_x) && (max_x >= x1) && (z1 >= min_z) && (max_z >= z1)) {
        return 1;
    }
    if ((x2 >= min_x) && (max_x >= x2) && (z2 >= min_z) && (max_z >= z2)) {
        return 1;
    }
    if ((x3 >= min_x) && (max_x >= x3) && (z3 >= min_z) && (max_z >= z3)) {
        return 1;
    }
    if (es_rectangulo_intersecando_linea(min_x, max_x, min_z, max_z, x1, z1, x2, z2) == 1) {
        return 1;
    }
    if (es_rectangulo_intersecando_linea(min_x, max_x, min_z, max_z, x2, z2, x3, z3) == 1) {
        return 1;
    }
    if (es_rectangulo_intersecando_linea(min_x, max_x, min_z, max_z, x3, z3, x1, z1) == 1) {
        return 1;
    }
    return 0;
}

#ifdef TARGET_PS2
static void generar_original_cuadricula_colision(void);

static void generar_rapido_cuadricula_colision(void) {
    static u16 cantidad_celda[TAMANIO_CUADRICULA * TAMANIO_CUADRICULA];
    static u16 pos_celda[TAMANIO_CUADRICULA * TAMANIO_CUADRICULA];
    static u8 superponer_x[TAMANIO_CUADRICULA], superponer_z[TAMANIO_CUADRICULA];
    s16 min_x_celda[TAMANIO_CUADRICULA], max_x_celda[TAMANIO_CUADRICULA];
    s16 min_z_celda[TAMANIO_CUADRICULA], max_z_celda[TAMANIO_CUADRICULA];
    TrianguloColision* triangulo;
    s32 i, j, k, pasada;
    s32 seccion_z, seccion_x, longitud_x_circuito, longitud_z_circuito;
    u32 total;

    longitud_x_circuito = (s32) max_x_circuito - min_x_circuito;
    longitud_z_circuito = (s32) max_z_circuito - min_z_circuito;
    seccion_x = longitud_x_circuito / TAMANIO_CUADRICULA;
    seccion_z = longitud_z_circuito / TAMANIO_CUADRICULA;

    for (i = 0; i < TAMANIO_CUADRICULA; i++) {
        s16 min_x = (min_x_circuito + (seccion_x * i)) - 20;
        s16 min_z = (min_z_circuito + (seccion_z * i)) - 20;

        min_x_celda[i] = min_x;
        max_x_celda[i] = min_x + seccion_x + 40;
        min_z_celda[i] = min_z;
        max_z_celda[i] = min_z + seccion_z + 40;
    }
    for (i = 0; i < TAMANIO_CUADRICULA * TAMANIO_CUADRICULA; i++) {
        cantidad_celda[i] = 0;
    }

    total = 0;
    for (pasada = 0; pasada < 2; pasada++) {
        if (pasada == 1) {
            total = 0;
            for (i = 0; i < TAMANIO_CUADRICULA * TAMANIO_CUADRICULA; i++) {
                pos_celda[i] = (u16) total;
                total += cantidad_celda[i];
            }
            if (total > 0xFFFF) {
                generar_original_cuadricula_colision();
                return;
            }
            for (i = 0; i < 1024; i++) {
                cuadricula_colision[i].triangulos_num = cantidad_celda[i];
                if (cantidad_celda[i] != 0) {
                    cuadricula_colision[i].triangulo = pos_celda[i];
                }
            }
            triangulos_colision_num = (u16) total;
            indices_colision = (u16*) siguiente_libre_memoria_direccion;
        }
        for (i = 0; i < cantidad_malla_colision; i++) {
            triangulo = malla_colision + i;
            for (k = 0; k < TAMANIO_CUADRICULA; k++) {
                superponer_x[k] = !(triangulo->max_x < min_x_celda[k]) && !(triangulo->min_x > max_x_celda[k]);
            }
            for (j = 0; j < TAMANIO_CUADRICULA; j++) {
                superponer_z[j] = !(triangulo->max_z < min_z_celda[j]) && !(triangulo->min_z > max_z_celda[j]);
            }
            for (j = 0; j < TAMANIO_CUADRICULA; j++) {
                if (!superponer_z[j]) {
                    continue;
                }
                for (k = 0; k < TAMANIO_CUADRICULA; k++) {
                    if (!superponer_x[k] ||
                        es_triangulo_intersecando_envolvente_caja(min_x_celda[k], max_x_celda[k], min_z_celda[j], max_z_celda[j],
                                                              (u16) i) != 1) {
                        continue;
                    }
                    if (pasada == 0) {
                        cantidad_celda[k + j * TAMANIO_CUADRICULA]++;
                    } else {
                        indices_colision[pos_celda[k + j * TAMANIO_CUADRICULA]++] = (u16) i;
                    }
                }
            }
        }
    }
}

void generar_cuadricula_colision(void) {
#ifdef SMK64_GRID_CHECK
    /* Comprobacion */
    static CuadriculaColision cuadricula_ref[TAMANIO_CUADRICULA * TAMANIO_CUADRICULA];
    static u16 ref_indices[0x10000];
    void registrar(const char* fmt, ...);
    u16 cantidad_ref;
    s32 cuadricula_dif = 0, idx_dif = 0, n;

    generar_original_cuadricula_colision();
    bcopy(cuadricula_colision, cuadricula_ref, sizeof(cuadricula_ref));
    bcopy(indices_colision, ref_indices, triangulos_colision_num * sizeof(u16));
    cantidad_ref = triangulos_colision_num;
    generar_rapido_cuadricula_colision();
    for (n = 0; n < TAMANIO_CUADRICULA * TAMANIO_CUADRICULA; n++) {
        cuadricula_dif += cuadricula_ref[n].triangulos_num != cuadricula_colision[n].triangulos_num ||
                    cuadricula_ref[n].triangulo != cuadricula_colision[n].triangulo;
    }
    for (n = 0; n < cantidad_ref && n < triangulos_colision_num; n++) {
        idx_dif += ref_indices[n] != indices_colision[n];
    }
    registrar("GRID_CHECK pista %d: %u triangulos, %u indices (original %u): celdas distintas %d, indices distintos %d",
            (int) id_circuito_actual, (unsigned) cantidad_malla_colision, (unsigned) triangulos_colision_num,
            (unsigned) cantidad_ref, (int) cuadricula_dif, (int) idx_dif);
#else
    generar_rapido_cuadricula_colision();
#endif
}

static void generar_original_cuadricula_colision(void) {
#else
void generar_cuadricula_colision(void) {
#endif
    TrianguloColision* triangulo;
    s32 i, j, k;
    SIN_USO s32 relleno[5];
    s16 max_x;
    s16 max_z;
    s16 min_x;
    s16 min_z;
    s32 seccion_z;
    s32 seccion_x;
    s32 longitud_x_circuito;
    s32 longitud_z_circuito;
    s32 index;

    longitud_x_circuito = (s32) max_x_circuito - min_x_circuito;
    longitud_z_circuito = (s32) max_z_circuito - min_z_circuito;

    seccion_x = longitud_x_circuito / TAMANIO_CUADRICULA;
    seccion_z = longitud_z_circuito / TAMANIO_CUADRICULA;

    for (i = 0; i < 1024; i++) {
        cuadricula_colision[i].triangulos_num = 0;
    }

    triangulos_colision_num = 0;
    indices_colision = (u16*) siguiente_libre_memoria_direccion;

    for (j = 0; j < TAMANIO_CUADRICULA; j++) {
        for (k = 0; k < TAMANIO_CUADRICULA; k++) {
            index = k + j * TAMANIO_CUADRICULA;

            min_x = (min_x_circuito + (seccion_x * k)) - 20;
            min_z = (min_z_circuito + (seccion_z * j)) - 20;

            max_x = min_x + seccion_x + 40;
            max_z = min_z + seccion_z + 40;

            for (i = 0; i < cantidad_malla_colision; i++) {
                triangulo = malla_colision + i;
                if (triangulo->max_z < min_z) {
                    continue;
                }
                if (triangulo->min_z > max_z) {
                    continue;
                }
                if (triangulo->max_x < min_x) {
                    continue;
                }
                if (triangulo->min_x > max_x) {
                    continue;
                }

                if (es_triangulo_intersecando_envolvente_caja(min_x, max_x, min_z, max_z, (u16) i) == 1) {
                    if (cuadricula_colision[index].triangulos_num == 0) {
                        cuadricula_colision[index].triangulo = triangulos_colision_num;
                    }
                    cuadricula_colision[index].triangulos_num++;
                    indices_colision[triangulos_colision_num] = (u16) i;
                    triangulos_colision_num++;
                }
            }
        }
    }
}

void generar_malla_colision_con_predeterminados(Gfx* gfx) {
    generar_malla_colision(gfx, PREDETERMINADO_SUPERFICIE, 0xFF);
}

void generar_malla_colision_con_id_seccion_predeterminado(Gfx* gfx, s8 tipo_superficie) {
    generar_malla_colision(gfx, tipo_superficie, 0xFF);
}

extern u32 dato_8015F58C;

void generar_malla_colision(Gfx* direccion, s8 tipo_superficie, u16 id_seccion) {
    s32 opcode;
    uintptr_t lo;
    uintptr_t hi;
    s32 i;

    s32 segmento = SEGMENT_NUMBER2(direccion);
    s32 desplazamiento = SEGMENT_OFFSET(direccion);
    Gfx* gfx = (Gfx*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    dato_8015F6FA = 0;
    dato_8015F6FC = 0;

    for (i = 0; i < 0x1FFF; i++) {
        lo = gfx->words.w0;
        hi = gfx->words.w1;
        opcode = GFX_OPCODE_OBTENER(lo);

        if (opcode == (G_DL << 24)) {
            generar_malla_colision((Gfx*) hi, tipo_superficie, id_seccion);

        } else if (opcode == (G_VTX << 24)) {
            fijar_buffer_vtx(hi, (lo >> 10) & 0x3F, ((lo >> 16) & 0xFF) >> 1);

        } else if (opcode == (G_TRI1 << 24)) {
            dato_8015F58C += 1;
            fijar_vtx_desde_triangulo(hi, tipo_superficie, id_seccion);

        } else if (opcode == (G_TRI2 << 24)) {
            dato_8015F58C += 2;
            fijar_vtx_desde_tri2(lo, hi, tipo_superficie, id_seccion);

        } else if (opcode == (G_QUAD << 24)) {
            dato_8015F58C += 2;
            fijar_vtx_desde_cuadrangulo(hi, tipo_superficie, id_seccion);

        } else if (opcode == (G_ENDDL << 24)) {
            break;
        }

        gfx++;
    }
}

void fijar_tamanio_tile_buscar_y(uintptr_t direccion, s32 uls, s32 ult) {
    u32 segmento = SEGMENT_NUMBER2(direccion);
    u32 desplazamiento = SEGMENT_OFFSET(direccion);
    Gfx* gfx = (Gfx*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    u32 opcode;

    uls = (uls << 12) & 0xFFF000;
    ult &= 0xFFF;

    while (true) {

        opcode = GFX_OPCODE_OBTENER(gfx->words.w0);

        if (opcode == (u32) G_ENDDL << 24) {
            break;
        } else if (opcode == (u32) (G_SETTILESIZE << 24)) {
            gfx->words.w0 = (G_SETTILESIZE << 24) | uls | ult;

            break;
        }
        gfx++;
    }
}

void fijar_colores_vertice(uintptr_t direccion, u32 cantidad_vertice, SIN_USO s32 vert3, s8 alpha, u8 rojo, u8 verde, u8 azul) {
    s32 segmento = SEGMENT_NUMBER2(direccion);
    s32 desplazamiento = SEGMENT_OFFSET(direccion);
    s32 i;
    Vtx* vtx = (Vtx*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);

    for (i = 0; (u32) i < cantidad_vertice; i++) {
        if (rojo) {
            vtx->v.cn[0] = rojo;
            vtx->v.cn[1] = verde;
            vtx->v.cn[2] = azul;
        }
        vtx->v.cn[3] = alpha;
        vtx++;
    }
}

void fijar_colores_vtx_buscar_y(uintptr_t display_list, s8 alpha, u8 rojo, u8 verde, u8 azul) {
    s32 segmento = SEGMENT_NUMBER2(display_list);
    s32 desplazamiento = SEGMENT_OFFSET(display_list);
    Gfx* gfx = (Gfx*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    uintptr_t lo;
    uintptr_t hi;
    s32 opcode;

    while (true) {
        lo = gfx->words.w0;
        hi = gfx->words.w1;
        opcode = GFX_OPCODE_OBTENER(lo);
        if (opcode == (G_ENDDL << 24)) {
            break;
        } else if (opcode == (G_DL << 24)) {
            fijar_colores_vtx_buscar_y(hi, alpha, rojo, verde, azul);
        } else if (opcode == (G_VTX << 24)) {
            fijar_colores_vertice(hi, (lo >> 10) & 0x3F, ((lo >> 16) & 0xFF) >> 1, alpha, rojo, verde, azul);
        }
        gfx++;
    }
}

void restar_vector_escalado(Vec3f pos1, f32 tamanio_caja_envolvente, Vec3f pos2) {
    pos2[0] -= pos1[0] * tamanio_caja_envolvente;
    pos2[1] -= pos1[1] * tamanio_caja_envolvente;
    pos2[2] -= pos1[2] * tamanio_caja_envolvente;
}

u16 colision_terreno_jugador(Jugador* jugador, RuedaKart* rueda, f32 rueda_2_x, f32 rueda_2_y, f32 rueda_2_z) {
    Colision wtf;
    Colision* colision = &wtf;
    SIN_USO s32 relleno;
    u16 i;
    u16 indice_malla;
    u16 triangulos_num;
    u16 indice_seccion;
    f32 rueda_x;
    f32 rueda_y;
    f32 rueda_z;
    f32 tamanio_caja_envolvente;
    f32 altura;

    s32 longitud_x_circuito;
    s32 longitud_z_circuito;

    s16 indice_x_seccion;
    s16 indice_z_seccion;
    s16 indice_cuadricula;

    s32 seccion_x;
    s32 seccion_z;
    SIN_USO s32 relleno2[9];

    colision->distancia_superficie[0] = 1000.0f;
    colision->distancia_superficie[1] = 1000.0f;
    colision->distancia_superficie[2] = 1000.0f;
    tamanio_caja_envolvente = jugador->tamanio_caja_envolvente;
    colision->indice_yx_malla = 5000;
    colision->indice_zy_malla = 5000;
    colision->indice_zx_malla = 5000;
    colision->desconocido30 = 0;
    colision->desconocido32 = 0;
    colision->unk34 = 0;
    rueda_x = rueda->pos[0];
    rueda_y = rueda->pos[1];
    rueda_z = rueda->pos[2];
    switch (rueda->banderas_superficie) {
        case 0x80:
            if (es_chocando_con_pared_x(colision, tamanio_caja_envolvente, rueda_x, rueda_y, rueda_z, rueda->indice_malla_colision,
                                         rueda_2_x, rueda_2_y, rueda_2_z) == 1) {
                altura = calcular_altura_superficie(rueda_x, rueda_y, rueda_z, rueda->indice_malla_colision);
                if ((!(altura > jugador->pos[1])) && !((jugador->pos[1] - altura) > (2 * tamanio_caja_envolvente))) {
                    rueda->altura_base = altura;
                    restar_vector_escalado(colision->desconocido54, colision->distancia_superficie[1], rueda->pos);
                    return 1;
                }
            }
            break;
        case 0x40:
            if (es_chocando_con_superficie_conducible(colision, tamanio_caja_envolvente, rueda_x, rueda_y, rueda_z,
                                                   rueda->indice_malla_colision, rueda_2_x, rueda_2_y, rueda_2_z) == 1) {
                altura = calcular_altura_superficie(rueda_x, rueda_y, rueda_z, rueda->indice_malla_colision);
                if (!(jugador->pos[1] < altura) && !((2 * tamanio_caja_envolvente) < (jugador->pos[1] - altura))) {
                    rueda->altura_base = altura;
                    restar_vector_escalado(colision->vector_orientacion, colision->distancia_superficie[2], rueda->pos);
                    return 1;
                }
            }
            break;
        case 0x20:
            if (es_chocando_con_pared_z(colision, tamanio_caja_envolvente, rueda_x, rueda_y, rueda_z, rueda->indice_malla_colision,
                                         rueda_2_x, rueda_2_y, rueda_2_z) == 1) {
                altura = calcular_altura_superficie(rueda_x, rueda_y, rueda_z, rueda->indice_malla_colision);
                if (!(jugador->pos[1] < altura) && !((2 * tamanio_caja_envolvente) < (jugador->pos[1] - altura))) {
                    rueda->altura_base = altura;
                    restar_vector_escalado(colision->desconocido48, colision->distancia_superficie[0], rueda->pos);
                    return 1;
                }
            }
            break;
        case 0:
            break;
    }

    longitud_x_circuito = (s32) max_x_circuito - min_x_circuito;
    longitud_z_circuito = (s32) max_z_circuito - min_z_circuito;

    seccion_x = longitud_x_circuito / TAMANIO_CUADRICULA;
    seccion_z = longitud_z_circuito / TAMANIO_CUADRICULA;

    indice_x_seccion = (rueda_x - min_x_circuito) / seccion_x;
    indice_z_seccion = (rueda_z - min_z_circuito) / seccion_z;

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
        return 0;
    }

    indice_seccion = cuadricula_colision[indice_cuadricula].triangulo;

    for (i = 0; i < triangulos_num; i++) {
        indice_malla = indices_colision[indice_seccion];
        if (malla_colision[indice_malla].flags & EJE_MIRANDO_Y) {
            if (indice_malla != rueda->indice_malla_colision) {
                if (es_chocando_con_superficie_conducible(colision, tamanio_caja_envolvente, rueda_x, rueda_y, rueda_z, indice_malla,
                                                       rueda_2_x, rueda_2_y, rueda_2_z) == 1) {
                    altura = calcular_altura_superficie(rueda_x, rueda_y, rueda_z, indice_malla);

                    if (!(jugador->pos[1] < altura) && !((2 * tamanio_caja_envolvente) < (jugador->pos[1] - altura))) {
                        restar_vector_escalado(colision->vector_orientacion, colision->distancia_superficie[2], rueda->pos);
                        rueda->altura_base = altura;
                        rueda->tipo_superficie = (u8) malla_colision[indice_malla].tipo_superficie;
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
            }
        } else if (malla_colision[indice_malla].flags & EJE_MIRANDO_X) {
            if (malla_colision[indice_malla].normal_y != 0.0f) {
                if (indice_malla != rueda->indice_malla_colision) {
                    if (es_chocando_con_pared_x(colision, tamanio_caja_envolvente, rueda_x, rueda_y, rueda_z, indice_malla, rueda_2_x,
                                                 rueda_2_y, rueda_2_z) == 1) {
                        altura = calcular_altura_superficie(rueda_x, rueda_y, rueda_z, indice_malla);
                        if (!(jugador->pos[1] < altura) && !((2 * tamanio_caja_envolvente) < (jugador->pos[1] - altura))) {
                            rueda->altura_base = altura;
                            restar_vector_escalado(colision->desconocido54, colision->distancia_superficie[1], rueda->pos);
                            rueda->altura_base = calcular_altura_superficie(rueda_x, rueda_y, rueda_z, indice_malla);
                            rueda->tipo_superficie = (u8) malla_colision[indice_malla].tipo_superficie;
                            rueda->banderas_superficie = 0x80;
                            rueda->indice_malla_colision = indice_malla;
                            return 1;
                        }
                    }
                }
            }
        } else {
            if (malla_colision[indice_malla].normal_y != 0.0f) {
                if (indice_malla != rueda->indice_malla_colision) {
                    if (es_chocando_con_pared_z(colision, tamanio_caja_envolvente, rueda_x, rueda_y, rueda_z, indice_malla, rueda_2_x,
                                                 rueda_2_y, rueda_2_z) == 1) {
                        altura = calcular_altura_superficie(rueda_x, rueda_y, rueda_z, indice_malla);
                        if (!(jugador->pos[1] < altura) && !((2 * tamanio_caja_envolvente) < (jugador->pos[1] - altura))) {
                            rueda->altura_base = altura;
                            restar_vector_escalado(colision->desconocido48, colision->distancia_superficie[0], rueda->pos);
                            rueda->tipo_superficie = (u8) malla_colision[indice_malla].tipo_superficie;
                            rueda->banderas_superficie = 0x20;
                            rueda->indice_malla_colision = indice_malla;
                            return 1;
                        }
                    }
                }
            }
        }
        indice_seccion++;
    }
    rueda->altura_base = rueda_y;
    rueda->tipo_superficie = 0;
    return 0;
}
