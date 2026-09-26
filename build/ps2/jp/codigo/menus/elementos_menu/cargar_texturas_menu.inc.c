// Cargar texturas menu

#ifdef AVOID_UB
#define TIPO_MTX Mtx
#else
typedef struct {
    u16 i[4][4];
    u16 f[4][4];
} mtx_u;

typedef union {
    mtx_u u;
    Mtx_t m;
    long long int force_structure_alignment;
} Mtx2;

typedef union {
    s16 s[2];
    s32 w;
} ElUnionPorQue;

#define TIPO_MTX Mtx2
#endif

void funcion_80095AE0(TIPO_MTX* parametro0, f32 parametro1, f32 parametro2, f32 parametro3, f32 parametro4) {
#ifdef AVOID_UB
    Mat4 orig_;
    orig_[0][0] = parametro3;
    orig_[0][1] = 0.0f;
    orig_[0][2] = 0.0f;
    orig_[0][3] = 0.0f;
    orig_[1][0] = 0.0f;
    orig_[1][1] = parametro4;
    orig_[1][2] = 0.0f;
    orig_[1][3] = 0.0f;
    orig_[2][0] = 0.0f;
    orig_[2][1] = 0.0f;
    orig_[2][2] = 1.0f;
    orig_[2][3] = 0.0f;
    orig_[3][0] = parametro1;
    orig_[3][1] = parametro2;
    orig_[3][2] = 0.0f;
    orig_[3][3] = 1.0f;
    guMtxF2L(orig_, parametro0);
#else
    ElUnionPorQue sp14;
    ElUnionPorQue sp10;
    ElUnionPorQue sp_c;
    ElUnionPorQue sp8;
    s32 i;

    for(i = 0; i < 16; i++) { parametro0->m[0][i] = 0; }

    sp14.w = parametro3 * 65536.0f;
    sp10.w = parametro4 * 65536.0f;
    sp_c.w = parametro1 * 65536.0f;
    sp8.w = parametro2 * 65536.0f;
    parametro0->u.i[0][0] = sp14.s[0];
    parametro0->u.i[1][1] = sp10.s[0];
    parametro0->u.i[2][2] = 1;
    parametro0->u.i[3][0] = sp_c.s[0];
    parametro0->u.i[3][1] = sp8.s[0];
    parametro0->u.i[3][3] = 1;
    parametro0->u.f[0][0] = sp14.s[1];
    parametro0->u.f[1][1] = sp10.s[1];
    parametro0->u.f[3][0] = sp_c.s[1];
    parametro0->u.f[3][1] = sp8.s[1];
#endif
}

#undef TIPO_MTX

Gfx* funcion_80095BD0(Gfx* display_list_cabeza_2, u8* parametro1, f32 parametro2, f32 parametro3, u32 parametro4, u32 parametro5, f32 parametro6, f32 parametro7) {
    Vtx* variable_a1;
    Mtx* sp28;

    if (cantidad_efecto_matriz >= 0x2F7) {
        goto func_80095BD0_etiqueta_1;
    }
    sp28 = &gfx_pool->efecto_mtx[cantidad_efecto_matriz];
    if (cantidad_efecto_matriz < 0) {
        rmon_printf("effectcount < 0 !!!!!!(kawano)\n");
    }
    goto func_80095BD0_etiqueta_2;
func_80095BD0_etiqueta_1:
    rmon_printf("MAX effectcount(760) over!!!!(kawano)\n");
    return display_list_cabeza_2;
func_80095BD0_etiqueta_2:
    funcion_80095AE0((void*) sp28, parametro2, parametro3, parametro6, parametro7);
    gSPMatrix(display_list_cabeza_2++, VIRTUAL_A_FISICO(&gfx_pool->efecto_mtx[cantidad_efecto_matriz]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    cantidad_efecto_matriz += 1;
    gDPLoadTextureTile_4b(display_list_cabeza_2++, parametro1, G_IM_FMT_I, parametro4, 0, 0, 0, parametro4, parametro5, 0, G_TX_NOMIRROR | G_TX_WRAP,
                          G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    switch (parametro4) {
        default:
            variable_a1 = dato_02007CD8;
            break;
        case 16:
            variable_a1 = dato_02007CD8;
            break;
        case 26:
            variable_a1 = dato_02007BB8;
            break;
        case 30:
            variable_a1 = dato_02007DF8;
            break;
    }

    return funcion_800959F8(display_list_cabeza_2, variable_a1);
}

Gfx* funcion_80095E10(Gfx* display_list_cabeza_2, s8 parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9, u8* parametro_a, u32 parametro_b, u32 parametro_c) {
    u32 variable_a1_2 = parametro4;
    u32 variable_s3 = parametro5;
    s32 sp7_c;
    u32 variable_s2;
    u32 variable_s4;
    s32 variable_t0 = 1;
    s32 temporal_lo;
    s32 sp68 = 0;
    s32 sp64 = 0;
    s32 variable_v0_2;

    while ((u32) variable_t0 < parametro_b) {
        variable_t0 *= 2;
    }

    temporal_lo = 0x400 / variable_t0;

    while ((u32) (temporal_lo / 2) > parametro_c) {
        temporal_lo /= 2;
    }

    variable_v0_2 = variable_t0;
    while (variable_v0_2 > 1) {
        variable_v0_2 /= 2;
        sp68 += 1;
    }
    variable_v0_2 = temporal_lo;

    while (variable_v0_2 > 1) {
        variable_v0_2 /= 2;
        sp64 += 1;
    }

    if (parametro8 < 0) {
        parametro4 -= parametro8;
        parametro8 = 0;
    } else if (((parametro6 - parametro4) + parametro8) > ANCHO_PANTALLA) {
        parametro6 = (parametro4 - parametro8) + ANCHO_PANTALLA;
    }

    if (parametro9 < 0) {
        parametro5 -= parametro9;
        parametro9 = 0;
    } else if (((parametro7 - parametro5) + parametro9) > ALTURA_PANTALLA) {
        parametro7 = (parametro5 - parametro9) + ALTURA_PANTALLA;
    }

    if (parametro6 < parametro4) {
        return display_list_cabeza_2;
    }
    if (parametro7 < parametro5) {
        return display_list_cabeza_2;
    }
    sp7_c = parametro8;
    for (variable_s3 = parametro5; variable_s3 < (u32) parametro7; variable_s3 += temporal_lo) {

        if ((u32) parametro7 < temporal_lo + variable_s3) {
            variable_s4 = parametro7 - variable_s3;
            if (!variable_s4) {
                break;
            }
        } else {
            variable_s4 = temporal_lo;
        }

        for (variable_a1_2 = parametro4; variable_a1_2 < (u32) parametro6; variable_a1_2 += variable_t0) {

            if ((u32) parametro6 < variable_t0 + variable_a1_2) {
                variable_s2 = parametro6 - variable_a1_2;
                if (!variable_s2) {
                    break;
                }
            } else {
                variable_s2 = variable_t0;
            }
            gDPLoadTextureTile(display_list_cabeza_2++, parametro_a, parametro1, G_IM_SIZ_16b, parametro_b, 0, variable_a1_2, variable_s3,
                               variable_a1_2 + variable_s2, variable_s3 + variable_s4, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, sp68, sp64, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(display_list_cabeza_2++, parametro8 * 4, parametro9 * 4, (parametro8 + variable_s2) * 4, (parametro9 + variable_s4) * 4, 0,
                                (variable_a1_2 * 32) & 0xFFFF, (variable_s3 * 32) & 0xFFFF, parametro2, parametro3);

            parametro8 += variable_t0;
        }

        parametro8 = sp7_c;
        parametro9 += temporal_lo;
    }
    return display_list_cabeza_2;
}

Gfx* funcion_800963F0(Gfx* display_list_cabeza_2, s8 parametro1, s32 parametro2, s32 parametro3, f32 parametro4, f32 parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9, s32 parametro_a, s32 parametro_b, u8* parametro_c, u32 parametro_d, u32 parametro_e) {
    u32 variable_a1_2 = parametro6;
    u32 variable_s3 = parametro7;
    s32 sp7_c;
    u32 variable_s2;
    u32 variable_s4;
    u32 a;
    u32 b;
    s32 variable_t0 = 1;
    s32 temporal_lo;
    s32 sp68 = 0;
    s32 sp64 = 0;
    s32 variable_v0_2;

    while ((u32) variable_t0 < parametro_d) {
        variable_t0 *= 2;
    }

    temporal_lo = 0x400 / variable_t0;

    while ((u32) (temporal_lo / 2) > parametro_e) {
        temporal_lo /= 2;
    }

    variable_v0_2 = variable_t0;
    while (variable_v0_2 > 1) {
        variable_v0_2 /= 2;
        sp68 += 1;
    }
    variable_v0_2 = temporal_lo;

    while (variable_v0_2 > 1) {
        variable_v0_2 /= 2;
        sp64 += 1;
    }

    if (parametro_a < 0) {
        parametro6 -= parametro_a;
        parametro_a = 0;
    } else if ((parametro_a + (parametro8 - parametro6) * parametro4) > ANCHO_PANTALLA) {
        parametro8 -= parametro_a + (parametro8 - parametro6) * parametro4 - ANCHO_PANTALLA;
    }

    if (parametro_b < 0) {
        parametro7 -= parametro_b;
        parametro_b = 0;
    } else if ((parametro_b + (parametro9 - parametro7) * parametro5) > ALTURA_PANTALLA) {
        parametro9 -= parametro_b + (parametro9 - parametro7) * parametro5 - ALTURA_PANTALLA;
    }

    if (parametro8 < parametro6) {
        return display_list_cabeza_2;
    }
    if (parametro9 < parametro7) {
        return display_list_cabeza_2;
    }
    parametro2 /= parametro4;
    parametro3 /= parametro5;

    sp7_c = parametro_a;
    for (variable_s3 = parametro7; variable_s3 < (u32) parametro9; variable_s3 += temporal_lo) {

        if ((u32) parametro9 < temporal_lo + variable_s3) {
            variable_s4 = parametro9 - variable_s3;
            if (!variable_s4) {
                break;
            }
        } else {
            variable_s4 = temporal_lo;
        }
        b = variable_s4 * parametro5;
        for (variable_a1_2 = parametro6; variable_a1_2 < (u32) parametro8; variable_a1_2 += variable_t0) {

            if ((u32) parametro8 < (variable_t0 + variable_a1_2)) {
                variable_s2 = parametro8 - variable_a1_2;
                if (!variable_s2) {
                    break;
                }
            } else {
                variable_s2 = variable_t0;
            }
            a = variable_s2 * parametro4;

            gDPLoadTextureTile(display_list_cabeza_2++, parametro_c, parametro1, G_IM_SIZ_16b, parametro_d, parametro_e, variable_a1_2, variable_s3,
                               variable_a1_2 + variable_s2, variable_s3 + variable_s4, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, sp68, sp64, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(display_list_cabeza_2++, parametro_a * 4, parametro_b * 4, (parametro_a + a) * 4, (parametro_b + b) * 4, 0,
                                (variable_a1_2 * 32) & 0xFFFF, (variable_s3 * 32) & 0xFFFF, parametro2, parametro3);

            parametro_a += variable_t0 * parametro4;
        }

        parametro_a = sp7_c;
        parametro_b += temporal_lo * parametro5;
    }
    return display_list_cabeza_2;
}

extern u8 dato_0B002A00[];
#ifdef TARGET_PS2
extern u8 _ftext[];
#define TEXTURA_NOISE (_ftext + 0x2A00)
#else
#define TEXTURA_NOISE dato_0B002A00
#endif
Gfx* funcion_80096CD8(Gfx* display_list_cabeza_2, s32 x_pos, s32 y_pos, u32 ancho, u32 altura) {
    u32 x;
    u32 y;
    SIN_USO s32 relleno;
    u32 rect_xoffset;
    u32 rect_yoffset;
    s32 ancho_tile = 1;
    s32 altura_tile;
    s32 mascaras = 0;
    s32 maskt = 0;
    s32 rnd;

    while ((u32) ancho_tile < ancho) {
        ancho_tile *= 2;
    }

    altura_tile = 1024 / ancho_tile;
    while ((u32) (altura_tile / 2) > altura) {
        altura_tile /= 2;
    }

    rnd = ancho_tile;
    while (rnd > 1) {
        rnd /= 2;
        mascaras += 1;
    }
    rnd = altura_tile;
    while (rnd > 1) {
        rnd /= 2;
        maskt += 1;
    }

    if (x_pos < 0) {
        ancho -= x_pos;
        x_pos = 0;
    } else if ((x_pos + ancho) > ANCHO_PANTALLA) {
        ancho = ANCHO_PANTALLA - x_pos;
    }
    if (y_pos < 0) {
        altura -= y_pos;
        y_pos = 0;
    } else if ((y_pos + altura) > ALTURA_PANTALLA) {
        altura = ALTURA_PANTALLA - y_pos;
    }

    if (ancho == 0) {
        return display_list_cabeza_2;
    }
    if (altura == 0) {
        return display_list_cabeza_2;
    }

    rnd = int_aleatorio(100);
    display_list_cabeza_2 = dibujar_caja(display_list_cabeza_2, x_pos, y_pos, x_pos + ancho, y_pos + altura, 0, 0, 0, rnd);
    rnd += 150;

    gDPPipeSync(display_list_cabeza_2++);
    gDPSetRenderMode(display_list_cabeza_2++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(display_list_cabeza_2++, 0, 0, rnd, rnd, rnd, rnd);
    gDPSetCombineMode(display_list_cabeza_2++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    for (y = y_pos; y < (y_pos + altura); y += altura_tile) {
        if ((y + altura_tile) > (y_pos + altura)) {
            rect_yoffset = y_pos + altura - y;
            if (rect_yoffset == 0) {
                break;
            }
        } else {
            rect_yoffset = altura_tile;
        }
        for (x = x_pos; x < x_pos + ancho; x += ancho_tile) {
            if (x + ancho_tile > x_pos + ancho) {
                rect_xoffset = x_pos + ancho - x;
                if (rect_xoffset == 0) {
                    break;
                }
            } else
                rect_xoffset = ancho_tile;

            gDPLoadTextureTile(display_list_cabeza_2++, (TEXTURA_NOISE + int_aleatorio(128) * 2), G_IM_FMT_IA, G_IM_SIZ_16b, ancho,
                               altura, x, y, x + rect_xoffset, y + rect_yoffset, 0, G_TX_WRAP, G_TX_WRAP, mascaras, maskt,
                               G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(display_list_cabeza_2++, x << 2, y << 2, (x + rect_xoffset) << 2, (y + rect_yoffset) << 2,
                                G_TX_RENDERTILE, (x * 32) & 0xFFFF, (y * 32) & 0xFFFF, 1024, 1024);
        }
    }

    return display_list_cabeza_2;
}

Gfx* funcion_80097274(Gfx* display_list_cabeza_2, s8 parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9, SIN_USO u16* parametro_a, u32 parametro_b, u32 parametro_c, SIN_USO s32 parametro_d) {
    u32 variable_a1_2 = parametro4;
    u32 variable_s3 = parametro5;
    s32 sp7_c;
    u32 variable_s2;
    u32 variable_s4;
    s32 variable_t0 = 1;
    s32 temporal_lo;
    s32 sp68 = 0;
    s32 sp64 = 0;
    s32 variable_v0_2;
    gDPPipeSync(display_list_cabeza_2++);
    gDPSetCycleType(display_list_cabeza_2++, G_CYC_2CYCLE);
    gDPSetTextureLOD(display_list_cabeza_2++, G_TL_TILE);
    gDPSetPrimColor(display_list_cabeza_2++, 0, 0, 0, 0, 0, temporizador_global % 256);
    gDPSetCombineLERP(display_list_cabeza_2++, TEXEL1, TEXEL0, PRIMITIVE_ALPHA, TEXEL0, TEXEL1, TEXEL0, PRIMITIVE, TEXEL0, 0,
                      0, 0, COMBINED, 0, 0, 0, COMBINED);
    while ((u32) variable_t0 < parametro_b) {
        variable_t0 *= 2;
    }
    temporal_lo = 0x400 / variable_t0;
    while ((u32) (temporal_lo / 2) > parametro_c) {
        temporal_lo /= 2;
    }
    variable_v0_2 = variable_t0;
    while (variable_v0_2 > 1) {
        variable_v0_2 /= 2;
        sp68 += 1;
    }
    variable_v0_2 = temporal_lo;
    while (variable_v0_2 > 1) {
        variable_v0_2 /= 2;
        sp64 += 1;
    }
    if (parametro8 < 0) {
        parametro4 -= parametro8;
        parametro8 = 0;
    } else if (((parametro6 - parametro4) + parametro8) > 320) {
        parametro6 = (parametro4 - parametro8) + 320;
    }
    if (parametro9 < 0) {
        parametro5 -= parametro9;
        parametro9 = 0;
    } else if (((parametro7 - parametro5) + parametro9) > 240) {
        parametro7 = (parametro5 - parametro9) + 240;
    }
    if (parametro6 < parametro4) {
        return display_list_cabeza_2;
    }
    if (parametro7 < parametro5) {
        return display_list_cabeza_2;
    }
    sp7_c = parametro8;
    for (variable_s3 = parametro5; variable_s3 < (u32) parametro7; variable_s3 += temporal_lo) {
        if ((u32) parametro7 < temporal_lo + variable_s3) {
            variable_s4 = parametro7 - variable_s3;
            if (!variable_s4) {
                break;
            }
        } else {
            variable_s4 = temporal_lo;
        }
        for (variable_a1_2 = parametro4; variable_a1_2 < (u32) parametro6; variable_a1_2 += variable_t0) {
            if ((u32) parametro6 < variable_t0 + variable_a1_2) {
                variable_s2 = parametro6 - variable_a1_2;
                if (!variable_s2) {
                    break;
                }
            } else {
                variable_s2 = variable_t0;
            }
            gDPLoadMultiTile(display_list_cabeza_2++, parametro_a, 0, G_TX_RENDERTILE, parametro1, G_IM_SIZ_16b, parametro_b, parametro_c, variable_a1_2,
                             variable_s3, variable_a1_2 + variable_s2, variable_s3 + variable_s4, 0, G_TX_WRAP, G_TX_WRAP, sp68, sp64,
                             G_TX_NOLOD, G_TX_NOLOD);
            gDPLoadMultiTile(display_list_cabeza_2++, TEXTURA_NOISE + int_aleatorio(128) * 2, 256, G_TX_RENDERTILE + 1, parametro1,
                             G_IM_SIZ_16b, parametro_b, parametro_c, variable_a1_2, variable_s3, variable_a1_2 + variable_s2, variable_s3 + variable_s4, 0,
                             G_TX_WRAP, G_TX_WRAP, sp68, sp64, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(display_list_cabeza_2++, parametro8 * 4, parametro9 * 4, (parametro8 + variable_s2) * 4, (parametro9 + variable_s4) * 4, 0,
                                (variable_a1_2 * 32) & 0xFFFF, (variable_s3 * 32) & 0xFFFF, parametro2, parametro3);
            parametro8 += variable_t0;
        }
        parametro8 = sp7_c;
        parametro9 += temporal_lo;
    }
    gDPPipeSync(display_list_cabeza_2++);
    gDPSetCycleType(display_list_cabeza_2++, G_CYC_1CYCLE);
    return display_list_cabeza_2;
}

Gfx* funcion_80097A14(Gfx* display_list_cabeza_2, s8 parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6, s32 parametro7, u8* parametro8,
                   u32 parametro9, u32 parametro_a) {
    gDPPipeSync(display_list_cabeza_2++);
    gDPSetCycleType(display_list_cabeza_2++, G_CYC_COPY);
    display_list_cabeza_2 = funcion_80095E10(display_list_cabeza_2, parametro1, 0x00001000, 0x00000400, parametro2, parametro3, parametro4, parametro5, parametro6, parametro7,
                                    parametro8, parametro9, parametro_a);
    gDPPipeSync(display_list_cabeza_2++);
    gDPSetCycleType(display_list_cabeza_2++, G_CYC_1CYCLE);
    return display_list_cabeza_2;
}

Gfx* funcion_80097AE4(Gfx* display_list_cabeza_2, s8 fmt, s32 parametro2, s32 parametro3, u8* parametro4, s32 ancho) {
    s32 i;
    s32 temporal_;
    s32 copia_parametro_2;
    s32 dsdx;

    if (ancho >= 32) {
        return display_list_cabeza_2;
    }

    copia_parametro_2 = parametro2;

    for (i = 0; i < 64; i += 32) {
        temporal_ = 0;
        dsdx = 0x8000 / (32 - ancho);
        gDPLoadTextureTile(display_list_cabeza_2++, parametro4, fmt, G_IM_SIZ_16b, 64, 64, temporal_, i, temporal_ + 32, i + 32, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(display_list_cabeza_2++, (parametro2 + ancho) << 2, parametro3 << 2, (parametro2 + 32) << 2, (parametro3 + 32) << 2, 0, 0,
                            0, dsdx, 1024);

        parametro2 += 32;

        gDPLoadTextureTile(display_list_cabeza_2++, parametro4, fmt, G_IM_SIZ_16b, 64, 64, temporal_ + 32, i, temporal_ + 64, i + 32, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(display_list_cabeza_2++, parametro2 << 2, parametro3 << 2, ((parametro2 - ancho) + 32) << 2, (parametro3 + 32) << 2, 0, 0,
                            0, dsdx, 1024);

        parametro2 = copia_parametro_2;
        parametro3 += 32;
    }
    return display_list_cabeza_2;
}

Gfx* funcion_80097E58(Gfx* display_list_cabeza_2, s8 fmt, SIN_USO u32 parametro2, u32 parametro3, SIN_USO u32 parametro4, u32 parametro5, s32 parametro6,
                   s32 parametro7, u8* algun_textura, u32 parametro9, SIN_USO u32 parametro_a, s32 ancho) {
    u32 ult;
    u32 temporal_;
    s32 copia_parametro_6;
    s32 temporal_v1;
    s32 variable_s2;
    s32 lrs;
    s32 sp_dc;
    s32 temporal2 = 32;

    if (ancho >= 32) {
        return display_list_cabeza_2;
    }

    copia_parametro_6 = parametro6;

    lrs = parametro9 / 2;
    sp_dc = parametro9 - lrs;
    for (ult = parametro3; ult < parametro5; ult += 32) {
        temporal_ = 0;
        if ((ult + temporal2) > parametro5) {
            variable_s2 = parametro5 - ult;
            if (!variable_s2) {
                break;
            }
        } else {
            variable_s2 = temporal2;
        }
        temporal_v1 = ((32 * lrs) << 10) / (lrs * (32 - ancho));

        gDPLoadTextureTile(display_list_cabeza_2++, algun_textura, fmt, G_IM_SIZ_16b, parametro9, parametro_a, temporal_, ult, temporal_ + lrs,
                           ult + variable_s2, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD,
                           G_TX_NOLOD);
        gSPTextureRectangle(display_list_cabeza_2++, (parametro6 + lrs * ancho / 32) << 2, parametro7 << 2, (parametro6 + lrs) << 2,
                            (parametro7 + variable_s2) << 2, 0, 0, (ult << 5) & 0xFFFF, temporal_v1, 1024);
        parametro6 += lrs;
        temporal_v1 = ((32 * sp_dc) << 10) / (sp_dc * (32 - ancho));
        gDPLoadTextureTile(display_list_cabeza_2++, algun_textura, fmt, G_IM_SIZ_16b, parametro9, parametro_a, temporal_ + lrs, ult, temporal_ + parametro9,
                           ult + variable_s2, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD,
                           G_TX_NOLOD);
        gSPTextureRectangle(display_list_cabeza_2++, parametro6 << 2, parametro7 << 2, (parametro6 + sp_dc * (32 - ancho) / 32) << 2,
                            (parametro7 + variable_s2) << 2, 0, (lrs << 5) & 0xFFFF, (ult << 5) & 0xFFFF, temporal_v1, 1024);
        parametro6 = copia_parametro_6;
        parametro7 += temporal2;
    }
    return display_list_cabeza_2;
}

Gfx* funcion_80098558(Gfx* display_list_cabeza_2, u32 parametro1, u32 parametro2, u32 parametro3, u32 parametro4, u32 parametro5, u32 parametro6, SIN_USO s32 parametro7,
                   s32 parametro8) {
    u32 variable_a3;
    u32 variable_v0;
    s32 copia_parametro_5;

    copia_parametro_5 = parametro5;
    for (variable_v0 = parametro2; variable_v0 < parametro4; variable_v0 += 0x20) {
        for (variable_a3 = parametro1; variable_a3 < parametro3; variable_a3 += 0x20) {
            gDPLoadTextureTile(display_list_cabeza_2++, buffer_textura_menu, G_IM_FMT_RGBA, G_IM_SIZ_16b, parametro8, 0, variable_a3,
                               variable_v0, variable_a3 + 0x20, variable_v0 + 0x20, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(display_list_cabeza_2++, parametro5 << 2, parametro6 << 2, (parametro5 + 0x20) << 2, (parametro6 + 0x20) << 2, 0, 0,
                                0, 1024, 1024);
            parametro5 += 0x20;
        }
        parametro5 = copia_parametro_5;
        parametro6 += 0x20;
    }
    return display_list_cabeza_2;
}

Gfx* funcion_800987D0(Gfx* display_list_cabeza_2, u32 parametro1, u32 parametro2, u32 ancho, u32 altura, s32 columna, s32 renglon,
                   SIN_USO u8* parametro7, u32 textura_ancho, SIN_USO s32 textura_altura) {
    s32 variable_a2;
    s32 variable_v0_2;
    s32 copia_columna;
    s32 temporal_f4_2;
    SIN_USO s32 margen_pila_0;
    s32 temporal_f6;
    f32 temporal_f0;
    f32 temporal_f18;
    f32 temporal_f24;

    if (duracion_transicion[0] == 0) {
        duracion_transicion[0] = 1;
    }
    temporal_f24 = senos(((tiempo_transicion_actual[0] * 0x4E20) / duracion_transicion[0]) % 20000U);
    temporal_f0 = coss(((tiempo_transicion_actual[0] * 0x4E20) / duracion_transicion[0]) % 20000U);
    temporal_f18 = (((f32) tiempo_transicion_actual[0] * 0.5) / duracion_transicion[0]) + 1.0;
    copia_columna = columna;
    for (variable_v0_2 = parametro2; (u32) variable_v0_2 < altura; variable_v0_2 += 0x20) {
        for (variable_a2 = parametro1; (u32) variable_a2 < ancho; variable_a2 += 0x20) {
            gDPLoadTextureTile(display_list_cabeza_2++, buffer_textura_menu, G_IM_FMT_RGBA, G_IM_SIZ_16b, textura_ancho, 0,
                               variable_a2, variable_v0_2, variable_a2 + 0x20, variable_v0_2 + 0x20, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
            temporal_f6 = (temporal_f18 * ((temporal_f0 * (columna - 0xA0)) + (temporal_f24 * (renglon - 0x78)))) + 160.0f;
            temporal_f4_2 = (temporal_f18 * ((-temporal_f24 * (columna - 0xA0)) + (temporal_f0 * (renglon - 0x78)))) + 120.0f;
            gSPTextureRectangle(display_list_cabeza_2++, temporal_f6 * 4, temporal_f4_2 * 4, ((temporal_f6 + 0x20) ^ 0) * 4,
                                ((temporal_f4_2 + 0x20) ^ 0) * 4, 0, 0, 0, 1024, 1024);
            columna += 0x20;
        }
        columna = copia_columna;
        renglon += 0x20;
    }
    return display_list_cabeza_2;
}

Gfx* dibujar_relleno_caja(Gfx* display_list_cabeza_2, s32 ulx, s32 uly, s32 lrx, s32 lry, s32 rojo, s32 verde, s32 azul, s32 alpha) {
    rojo &= 0xFF;
    verde &= 0xFF;
    azul &= 0xFF;
    alpha &= 0xFF;
    if (lrx < ulx) {
        intercambiar_valores(&ulx, &lrx);
    }
    if (lry < uly) {
        intercambiar_valores(&uly, &lry);
    }
    if ((ulx >= 0x140) || (uly >= 0xF0)) {
        return display_list_cabeza_2;
    }
    if (ulx < 0) {
        ulx = 0;
    }
    if (uly < 0) {
        uly = 0;
    }
    if ((lrx < 0) || (lry < 0)) {
        return display_list_cabeza_2;
    }
    if (lrx >= 0x140) {
        lrx = 0x13F;
    }
    if (lry >= 0xF0) {
        lry = 0xEF;
    }
    gSPDisplayList(display_list_cabeza_2++, dato_02008030);
    gDPSetFillColor(display_list_cabeza_2++, (GPACK_RGBA5551(rojo, verde, (u32) azul, alpha) << 0x10 |
                                        GPACK_RGBA5551(rojo, verde, (u32) azul, alpha)));
    gDPFillRectangle(display_list_cabeza_2++, ulx, uly, lrx, lry);
    gSPDisplayList(display_list_cabeza_2++, dato_02008058);
    return display_list_cabeza_2;
}

Gfx* dibujar_caja(Gfx* display_list_cabeza_2, s32 ulx, s32 uly, s32 lrx, s32 lry, u32 rojo, u32 verde, u32 azul, u32 alpha) {
    rojo &= 0xFF;
    verde &= 0xFF;
    azul &= 0xFF;
    alpha &= 0xFF;
    if (lrx < ulx) {
        intercambiar_valores(&ulx, &lrx);
    }
    if (lry < uly) {
        intercambiar_valores(&uly, &lry);
    }
    if ((ulx >= 0x140) || (uly >= 0xF0)) {
        return display_list_cabeza_2;
    }
    if (ulx < 0) {
        ulx = 0;
    }
    if (uly < 0) {
        uly = 0;
    }
    if ((lrx < 0) || (lry < 0)) {
        return display_list_cabeza_2;
    }
    if (lrx >= 0x141) {
        lrx = 0x140;
    }
    if (lry >= 0xF1) {
        lry = 0xF0;
    }
    gSPDisplayList(display_list_cabeza_2++, dato_02008008);
    gDPSetPrimColor(display_list_cabeza_2++, 0, 0, rojo, verde, azul, alpha);
    gDPFillRectangle(display_list_cabeza_2++, ulx, uly, lrx, lry);
    gDPPipeSync(display_list_cabeza_2++);
    return display_list_cabeza_2;
}

Gfx* funcion_80098FC8(Gfx* display_list_cabeza_2, s32 ulx, s32 uly, s32 lrx, s32 lry) {
    return dibujar_relleno_caja(display_list_cabeza_2, ulx, uly, lrx, lry, 0, 0, 0, 0xFF);
}

void copiar_segmento_mio0_dma(u64* datos, size_t nbytes, void* vaddr) {
    OSIoMesg mb;
    OSMesg mens;

    osInvalDCache(vaddr, nbytes);
    osPiStartDma(&mb, OS_MESG_PRI_NORMAL, OS_READ, (uintptr_t) &_textures_0aSegmentRomStart[SEGMENT_OFFSET(datos)],
                 vaddr, nbytes, &cola_msj_dma);
    osRecvMesg(&cola_msj_dma, &mens, OS_MESG_BLOCK);
}

void texturas_tkmk00_dma(u64* datos, size_t nbytes, void* vaddr) {
    OSIoMesg mb;
    OSMesg mens;

    osInvalDCache(vaddr, nbytes);
    osPiStartDma(&mb, OS_MESG_PRI_NORMAL, OS_READ, (uintptr_t) &_textures_0bSegmentRomStart[SEGMENT_OFFSET(datos)],
                 vaddr, nbytes, &cola_msj_dma);
    osRecvMesg(&cola_msj_dma, &mens, OS_MESG_BLOCK);
}

void borrar_texturas_menu(void) {
    menu_textura_buffer_indice = 0;
    entradas_textura_menu = 0;
}

void* segmentado_a_duplicado_virtual(const void* direccion) {
    size_t segmento = (uintptr_t) direccion >> 24;
    size_t desplazamiento = (uintptr_t) direccion & 0x00FFFFFF;

    return (void*) FISICO_A_VIRTUAL(tabla_segmento[segmento] + desplazamiento);
}

void* segmentado_a_duplicado_virtual_2(const void* direccion) {
    size_t segmento = (uintptr_t) direccion >> 24;
    size_t desplazamiento = (uintptr_t) direccion & 0x00FFFFFF;

    return (void*) FISICO_A_VIRTUAL(tabla_segmento[segmento] + desplazamiento);
}

#if defined(TARGET_PS2) && defined(SMK64_DEV)
s32 menu_texturas_salteado;
#endif
#ifdef AVOID_UB
static u32 menu_textura_buffer_tamanio;

static void fijar_buffer_textura_menu(u16* buffer, u32 size) {
    buffer_textura_menu = buffer;
    menu_textura_buffer_tamanio = size;
}

static s32 cabe_textura_menu(TexturaMenu* direccion_tex) {
    u32 end = (menu_textura_buffer_indice + direccion_tex->width * direccion_tex->height) * sizeof(u16);

    if ((entradas_textura_menu < TEXTURA_MAX_MAPA) && ((menu_textura_buffer_tamanio == 0) || (end <= menu_textura_buffer_tamanio))) {
        return true;
    }
#if defined(TARGET_PS2) && defined(SMK64_DEV)
    menu_texturas_salteado++;
    {
        void registrar(const char* fmt, ...);
        registrar("MENU: textura %p %ux%u no cabe: entradas %d/%d, buffer %u/%u bytes (desde %p)", direccion_tex->textura_datos,
                direccion_tex->width, direccion_tex->height, (int) entradas_textura_menu, TEXTURA_MAX_MAPA, (unsigned) end,
                (unsigned) menu_textura_buffer_tamanio, __builtin_return_address(0));
    }
#endif
    return false;
}
#endif

void cargar_img_menu(TexturaMenu* direccion) {
    u16 size;
    s32 i;
    s32 img_cargado;
    TexturaMenu* direccion_tex;
    TexturaMapa* mapa_tex = &mapa_textura_menu[0];

    direccion_tex = segmentado_a_duplicado_virtual(direccion);
    while (direccion_tex->textura_datos != NULL) {
        img_cargado = false;
        for (i = 0; i < entradas_textura_menu; i++) {
            if (direccion_tex->textura_datos == (mapa_tex + i)->textura_datos) {
                img_cargado = true;
                break;
            }
        }
#if defined(TARGET_PS2) && defined(SMK64_DEV_TRACE)
        {
            void registrar(const char* fmt, ...);
            registrar("load_menu_img %p -> %p (desde %p): tipo %d datos %p %ux%u tam %u", direccion, direccion_tex, __builtin_return_address(0), direccion_tex->type,
                    direccion_tex->textura_datos, direccion_tex->width, direccion_tex->height, direccion_tex->size);
        }
#endif

        if (img_cargado == false) {
#ifdef AVOID_UB
            if (!cabe_textura_menu(direccion_tex)) {
                direccion_tex++;
                continue;
            }
#endif
            if (direccion_tex->type == 3) {
                if (direccion_tex->size != 0) {
                    size = direccion_tex->size;
                } else {
                    size = 0x1000;
                }
                if (size % 8) {
                    size = ((size / 8) * 8) + 8;
                }
                copiar_segmento_mio0_dma(direccion_tex->textura_datos, size, buffer_comprimido_menu);
                mio0decode((u8*) buffer_comprimido_menu, (u8*) &buffer_textura_menu[menu_textura_buffer_indice]);
            } else {
                copiar_segmento_mio0_dma(direccion_tex->textura_datos, (direccion_tex->height * direccion_tex->width) * 2,
                                      &buffer_textura_menu[menu_textura_buffer_indice]);
            }
            mapa_tex[entradas_textura_menu].textura_datos = direccion_tex->textura_datos;
            mapa_tex[entradas_textura_menu].offset = menu_textura_buffer_indice;
            menu_textura_buffer_indice += direccion_tex->height * direccion_tex->width;
            menu_textura_buffer_indice = ((menu_textura_buffer_indice / 8) * 8) + 8;
            entradas_textura_menu += 1;
        }
        direccion_tex++;
    }
}

void funcion_80099394(TexturaMenu* direccion) {
    s32 i;
    s32 img_cargado;
    TexturaMenu* direccion_tex;
    TexturaMapa* mapa_tex = &mapa_textura_menu[0];

    direccion_tex = segmentado_a_duplicado_virtual(direccion);
    while (direccion_tex->textura_datos != NULL) {
        img_cargado = false;
        for (i = 0; i < entradas_textura_menu; i++) {
            if (direccion_tex->textura_datos == (mapa_tex + i)->textura_datos) {
                img_cargado = true;
                break;
            }
        }

        if (img_cargado == false) {
#ifdef AVOID_UB
            if (!cabe_textura_menu(direccion_tex)) {
                direccion_tex++;
                continue;
            }
#endif
            if (direccion_tex->type == 5) {
                copiar_segmento_mio0_dma(direccion_tex->textura_datos, (u32) (((s32) (direccion_tex->height * direccion_tex->width)) / 2),
                                      &buffer_textura_menu[menu_textura_buffer_indice]);
            }
            mapa_tex[entradas_textura_menu].textura_datos = direccion_tex->textura_datos;
            mapa_tex[entradas_textura_menu].offset = menu_textura_buffer_indice;
            menu_textura_buffer_indice += direccion_tex->height * direccion_tex->width;
            menu_textura_buffer_indice = ((menu_textura_buffer_indice / 8) * 8) + 8;
            entradas_textura_menu += 1;
        }
        direccion_tex++;
    }
}
