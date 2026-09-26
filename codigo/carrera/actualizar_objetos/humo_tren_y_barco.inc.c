// Humo tren y barco

s32 funcion_80073B34(s32 parametro0, s16* parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6) {
    if (parametro3 < *parametro1) {
        return funcion_80073A10(parametro0, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6);
    }
}

bool funcion_80073B78(s32 parametro0, s32 indice_objeto, s16* parametro2, s32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6, s32 parametro7) {
    s32 phi_t0;

    phi_t0 = false;
    if (lista_objeto[indice_objeto].desconocido_0CF == 0) {
        lista_objeto[indice_objeto].desconocido_0AC = parametro6;
        if (parametro0 != 0) {
            *parametro2 = parametro3;
        }
        lista_objeto[indice_objeto].desconocido_0D0 = parametro7;
        funcion_80073800(indice_objeto, 1);
    } else {
        lista_objeto[indice_objeto].desconocido_0AC--;
        if (lista_objeto[indice_objeto].desconocido_0AC < 0) {
            lista_objeto[indice_objeto].desconocido_0AC = parametro6;
            if (lista_objeto[indice_objeto].desconocido_0CF == 1) {
                *parametro2 += parametro5;
                if (*parametro2 >= parametro4) {
                    *parametro2 = parametro4;
                    lista_objeto[indice_objeto].desconocido_0CF++;
                }
            } else {
                *parametro2 -= parametro5;
                if (parametro3 >= *parametro2) {
                    *parametro2 = parametro3;
                    if (lista_objeto[indice_objeto].desconocido_0D0 > 0) {
                        lista_objeto[indice_objeto].desconocido_0D0--;
                    }
                    if (lista_objeto[indice_objeto].desconocido_0D0 == 0) {
                        funcion_80073800(indice_objeto, 0);
                        funcion_8007381C(indice_objeto);
                        phi_t0 = true;
                    } else {
                        lista_objeto[indice_objeto].desconocido_0CF = 1;
                    }
                }
            }
        }
    }

    return phi_t0;
}

bool funcion_80073CB0(s32 indice_objeto, s16* parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6) {
    return funcion_80073B78(1, indice_objeto, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6);
}

bool funcion_80073D0C(s32 indice_objeto, s16* parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6) {
    return funcion_80073B78(0, indice_objeto, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6);
}

SIN_USO void funcion_80073D68(s32 indice_objeto, s16* parametro1, s16 parametro2, s32 parametro3) {
    *parametro1 = *parametro1 + parametro3;
    if (*parametro1 >= parametro2) {
        *parametro1 = parametro2;
        funcion_80073800(indice_objeto, 0);
        funcion_8007381C(indice_objeto);
    }
}

void funcion_80073DC0(s32 indice_objeto, s16* parametro1, s16 parametro2, s32 parametro3) {
    *parametro1 = *parametro1 - parametro3;
    if (parametro2 >= *parametro1) {
        *parametro1 = parametro2;
        funcion_80073800(indice_objeto, 0);
        funcion_8007381C(indice_objeto);
    }
}

bool funcion_80073E18(s32 indice_objeto, u16* parametro1, u16 parametro2, s32 parametro3) {
    bool phi_t0;
    s32 temporal_v1;

    phi_t0 = false;
    if (lista_objeto[indice_objeto].desconocido_0CF == 0) {
        funcion_80073800(indice_objeto, 1);
        lista_objeto[indice_objeto].desconocido_048 = parametro3;
    }

    temporal_v1 = lista_objeto[indice_objeto].desconocido_048 - parametro2;
    if (temporal_v1 <= 0) {
        *parametro1 += lista_objeto[indice_objeto].desconocido_048;
        funcion_80073800(indice_objeto, 0);
        phi_t0 = true;
    } else {
        *parametro1 += parametro2;
        lista_objeto[indice_objeto].desconocido_048 = temporal_v1;
    }

    return phi_t0;
}

SIN_USO bool funcion_80073ED4(s32 indice_objeto, u16* parametro1, u16 parametro2, s32 parametro3) {
    bool phi_t0;
    s32 temporal_v1;

    phi_t0 = false;
    if (lista_objeto[indice_objeto].desconocido_0CF == 0) {
        funcion_80073800(indice_objeto, 1);
        lista_objeto[indice_objeto].desconocido_048 = parametro3;
    }

    temporal_v1 = lista_objeto[indice_objeto].desconocido_048 - parametro2;
    if (temporal_v1 <= 0) {
        *parametro1 += lista_objeto[indice_objeto].desconocido_048;
        funcion_80073800(indice_objeto, 0);
        phi_t0 = true;
    } else {
        *parametro1 -= parametro2;
        lista_objeto[indice_objeto].desconocido_048 = temporal_v1;
    }
    return phi_t0;
}

void funcion_80073F90(s32 indice_objeto, s32 parametro1) {
    lista_objeto[indice_objeto].desconocido_0CD = parametro1;
}

void funcion_80073FAC(s32 indice_objeto) {
    lista_objeto[indice_objeto].desconocido_0DB++;
}

void funcion_80073FD4(s32 indice_objeto) {
    funcion_80073F90(indice_objeto, 0);
    lista_objeto[indice_objeto].desconocido_0DB = 1;
}

SIN_USO void funcion_80074014(void) {
}

bool funcion_8007401C(s32 indice_objeto, f32* parametro1, f32 parametro2, f32 parametro3, f32 parametro4, s32 parametro5, s32 parametro6) {
    bool phi_a3;

    phi_a3 = false;
    if (lista_objeto[indice_objeto].desconocido_0CD == 0) {
        *parametro1 = parametro2;
        lista_objeto[indice_objeto].desconocido_0AA = parametro5;
        lista_objeto[indice_objeto].desconocido_0CE = parametro6;
        funcion_80073F90(indice_objeto, 1);
    } else {
        lista_objeto[indice_objeto].desconocido_0AA--;
        if ((s32) lista_objeto[indice_objeto].desconocido_0AA < 0) {
            lista_objeto[indice_objeto].desconocido_0AA = parametro5;
            *parametro1 += parametro4;
            if (parametro3 < *parametro1) {
                if ((s32) lista_objeto[indice_objeto].desconocido_0CE > 0) {
                    lista_objeto[indice_objeto].desconocido_0CE--;
                }
                if (lista_objeto[indice_objeto].desconocido_0CE == 0) {
                    *parametro1 = parametro3;
                    funcion_80073F90(indice_objeto, 0);
                    funcion_80073FAC(indice_objeto);
                    phi_a3 = true;
                } else {
                    *parametro1 = parametro2;
                }
            }
        }
    }

    return phi_a3;
}

s32 funcion_80074118(s32 indice_objeto, f32* parametro1, f32 parametro2, f32 parametro3, f32 parametro4, s32 parametro5, s32 parametro6) {
    return funcion_8007401C(indice_objeto, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6);
}

s32 funcion_8007415C(s32 indice_objeto, f32* parametro1, f32 parametro2, f32 parametro3, f32 parametro4, s32 parametro5, s32 parametro6) {
    if (*parametro1 < parametro3) {
        return funcion_8007401C(indice_objeto, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6);
    }
}

s32 funcion_800741B4(s32 indice_objeto, f32* parametro1, f32 parametro2, f32 parametro3, f32 parametro4, s32 parametro5, s32 parametro6) {
    if (lista_objeto[indice_objeto].desconocido_0CD == 0) {
        *parametro1 = parametro2;
        lista_objeto[indice_objeto].desconocido_0AA = parametro5;
        lista_objeto[indice_objeto].desconocido_0CE = parametro6;
        funcion_80073F90(indice_objeto, 1);
    } else {
        lista_objeto[indice_objeto].desconocido_0AA += -1;
        if (lista_objeto[indice_objeto].desconocido_0AA < 0) {
            lista_objeto[indice_objeto].desconocido_0AA = parametro5;
            *parametro1 -= parametro4;
            if (*parametro1 < parametro3) {
                if (lista_objeto[indice_objeto].desconocido_0CE > 0) {
                    lista_objeto[indice_objeto].desconocido_0CE--;
                }
                if (lista_objeto[indice_objeto].desconocido_0CE == 0) {
                    *parametro1 = parametro3;
                    funcion_80073F90(indice_objeto, 0);
                    funcion_80073FAC(indice_objeto);
                } else {
                    *parametro1 = parametro2;
                }
            }
        }
    }

    return 0;
}

SIN_USO void funcion_800742A8(s32 indice_objeto, f32* parametro1, f32 parametro2, f32 parametro3, f32 parametro4, s32 parametro5, s32 parametro6) {
    funcion_800741B4(indice_objeto, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6);
}

SIN_USO void funcion_800742EC(s32 indice_objeto, f32* parametro1, f32 parametro2, f32 parametro3, f32 parametro4, s32 parametro5, s32 parametro6) {
    if (parametro3 < *parametro1) {
        funcion_800741B4(indice_objeto, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6);
    }
}

void funcion_80074344(s32 indice_objeto, f32* parametro1, f32 parametro2, f32 parametro3, f32 parametro4, s32 parametro5, s32 parametro6) {
    if (lista_objeto[indice_objeto].desconocido_0CD == 0) {
        *parametro1 = parametro2;
        lista_objeto[indice_objeto].desconocido_0AA = parametro5;
        lista_objeto[indice_objeto].desconocido_0CE = parametro6;
        funcion_80073F90(indice_objeto, 1);
        return;
    }

    lista_objeto[indice_objeto].desconocido_0AA--;
    if (lista_objeto[indice_objeto].desconocido_0AA < 0) {
        lista_objeto[indice_objeto].desconocido_0AA = parametro5;
        if (lista_objeto[indice_objeto].desconocido_0CD == 1) {
            *parametro1 += parametro4;
            if (parametro3 <= *parametro1) {
                *parametro1 = parametro3;
                lista_objeto[indice_objeto].desconocido_0CD++;
            }
        } else {
            *parametro1 -= parametro4;
            if (*parametro1 <= parametro2) {
                *parametro1 = parametro2;

                if (lista_objeto[indice_objeto].desconocido_0CE > 0) {
                    lista_objeto[indice_objeto].desconocido_0CE--;
                }
                if (lista_objeto[indice_objeto].desconocido_0CE == 0) {
                    funcion_80073F90(indice_objeto, 0);
                    funcion_80073FAC(indice_objeto);
                } else {
                    lista_objeto[indice_objeto].desconocido_0CD = 1;
                }
            }
        }
    }
}

void funcion_80074478(s32 indice_objeto) {
    lista_objeto[indice_objeto].status |= 1;
}

void funcion_800744A0(s32 indice_objeto) {
    lista_objeto[indice_objeto].status &= ~1;
}

void funcion_800744CC(void) {
    if (dato_8018D224 != 0) {
        osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
        dato_8018D224 = 0;
    }
}

void funcion_80074510(uintptr_t direccion_dev, void* vaddr, size_t nbytes) {
    funcion_800744CC();
    osPiStartDma(&msj_io_dma, OS_MESG_PRI_NORMAL, OS_READ, direccion_dev, vaddr, nbytes, &cola_msj_dma);
    dato_8018D224 = 1;
}

void funcion_80074574(u8* parametro0, void* parametro1, u16 parametro2, u16 parametro3) {
    funcion_80074510((uintptr_t) &_other_texturesSegmentRomStart[SEGMENT_OFFSET(parametro0)], parametro1, parametro2 * parametro3);
}

void funcion_800745C8(s32 indice_objeto, uintptr_t parametro1) {
    s32 phi_a1;

    if ((lista_objeto[indice_objeto].status & 1) != 0) {
        phi_a1 = 0;
        if (lista_objeto[indice_objeto].tlut_lista != lista_objeto[indice_objeto].t_lut_activo) {
            lista_objeto[indice_objeto].t_lut_activo = lista_objeto[indice_objeto].tlut_lista;
        }

        lista_objeto[indice_objeto].status ^= 2;
        if ((lista_objeto[indice_objeto].status & 2) != 0) {
            phi_a1 = 1;
        }

        lista_objeto[indice_objeto].textura_activo =
            (u8*) (lista_objeto[indice_objeto].textura_ancho * lista_objeto[indice_objeto].textura_altura * phi_a1) + parametro1;
        funcion_800744A0(indice_objeto);
    }
}

void funcion_8007466C(s32 indice_objeto, uintptr_t parametro1) {
    s32 phi_a1;

    if ((lista_objeto[indice_objeto].status & 1) != 0) {
        lista_objeto[indice_objeto].t_lut_activo =
            (u8*) ((u32*) lista_objeto[indice_objeto].tlut_lista + (lista_objeto[indice_objeto].desconocido_0D3 << 7));
        lista_objeto[indice_objeto].status ^= 2;
        phi_a1 = 0;
        if ((lista_objeto[indice_objeto].status & 2) != 0) {
            phi_a1 = 1;
        }
        lista_objeto[indice_objeto].textura_activo =
            (u8*) (lista_objeto[indice_objeto].textura_ancho * lista_objeto[indice_objeto].textura_altura * phi_a1) + parametro1;
        funcion_800744A0(indice_objeto);
    }
}

void funcion_80074704(s32 indice_objeto, uintptr_t parametro1) {
    s32 phi_a1;

    if ((lista_objeto[indice_objeto].status & 1) != 0) {
        lista_objeto[indice_objeto].t_lut_activo = lista_objeto[indice_objeto].tlut_lista;
        lista_objeto[indice_objeto].status ^= 2;
        phi_a1 = 0;
        if ((lista_objeto[indice_objeto].status & 2) != 0) {
            phi_a1 = 1;
        }
        lista_objeto[indice_objeto].textura_activo =
            (u8*) (lista_objeto[indice_objeto].textura_ancho * lista_objeto[indice_objeto].textura_altura * phi_a1) + parametro1;
        funcion_800744A0(indice_objeto);
    }
}

u8* funcion_80074790(s32 indice_objeto, u8* parametro1) {
    s32 phi_a2;

    lista_objeto[indice_objeto].status ^= 4;
    phi_a2 = 0;
    if ((lista_objeto[indice_objeto].status & 4) != 0) {
        phi_a2 = 1;
    }
    return (lista_objeto[indice_objeto].textura_ancho * lista_objeto[indice_objeto].textura_altura * phi_a2) + parametro1;
}

void funcion_800747F0(s32 indice_objeto, u8* parametro1) {
    u8* sp24;
    if (lista_objeto[indice_objeto].textura_indice_lista != lista_objeto[indice_objeto].desconocido_0D3) {
        sp24 = lista_objeto[indice_objeto].textura_lista +
               (lista_objeto[indice_objeto].textura_ancho * lista_objeto[indice_objeto].textura_altura *
                lista_objeto[indice_objeto].textura_indice_lista);
        funcion_80074574(sp24, (void*) funcion_80074790(indice_objeto, parametro1), lista_objeto[indice_objeto].textura_ancho,
                      lista_objeto[indice_objeto].textura_altura);
        lista_objeto[indice_objeto].desconocido_0D3 = lista_objeto[indice_objeto].textura_indice_lista;
        funcion_80074478(indice_objeto);
    }
}

void funcion_80074894(s32 indice_objeto, u8* parametro1) {
    funcion_800747F0(indice_objeto, parametro1);
    funcion_800745C8(indice_objeto, (uintptr_t) parametro1);
}

void funcion_800748C4(s32 indice_objeto, u8* parametro1) {
    funcion_800747F0(indice_objeto, parametro1);
    funcion_8007466C(indice_objeto, (uintptr_t) parametro1);
}

void funcion_800748F4(s32 indice_objeto, u8* parametro1) {
    funcion_800747F0(indice_objeto, parametro1);
    funcion_80074704(indice_objeto, (uintptr_t) parametro1);
}

void funcion_80074924(s32 indice_objeto) {
    s32 sp2_c;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s16 temporal_v0;
    s32 temporal_a0;
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->escalado_tamanio = 0.15f;
    temporal_v0 = id_circuito_actual;
    switch (temporal_v0) { /* irregular */
        case CIRCUITO_MARIO_RACEWAY:
            sp2_c = int_aleatorio(0x00C8U);
            sp28 = int_aleatorio(dato_80165748);
            sp24 = int_aleatorio(0x0096U);
            sp20 = int_aleatorio(0x2000U);
            objeto->pos_origen[0] = (f32) ((((f64) dato_80165718 + 100.0) - (f64) sp2_c) * (f64) orientacion_x);
            objeto->pos_origen[1] = (f32) (dato_80165720 + sp28);
            objeto->pos_origen[2] = (f32) (((f64) dato_80165728 + 200.0) - (f64) sp24);
            break;
        case CIRCUITO_ROYAL_RACEWAY:
            sp2_c = int_aleatorio(0x0168U);
            sp28 = int_aleatorio(dato_80165748);
            sp24 = int_aleatorio(0x00B4U);
            sp20 = int_aleatorio(0x2000U);
            objeto->pos_origen[0] = (f32) ((((f64) dato_80165718 + 180.0) - (f64) sp2_c) * (f64) orientacion_x);
            objeto->pos_origen[1] = (f32) (dato_80165720 + sp28);
            objeto->pos_origen[2] = (f32) (((f64) dato_80165728 + 200.0) - (f64) sp24);
            break;
        case CIRCUITO_LUIGI_RACEWAY:
            sp2_c = int_aleatorio(0x012CU);
            sp28 = int_aleatorio(dato_80165748);
            sp24 = int_aleatorio(0x0096U);
            sp20 = int_aleatorio(0x2000U);
            objeto->pos_origen[0] = (f32) ((((f64) dato_80165718 + 150.0) - (f64) sp2_c) * (f64) orientacion_x);
            objeto->pos_origen[1] = (f32) (dato_80165720 + sp28);
            objeto->pos_origen[2] = (f32) (((f64) dato_80165728 + 200.0) - (f64) sp24);
            break;
    }
    fijar_desplazamiento_origen_obj(indice_objeto, 0, 0, 0);
    if (cantidad_jugador == 1) {
        objeto->velocidad[1] = (f32) (((f64) (f32) (sp2_c % 4) * 0.25) + 0.8);
    } else {
        objeto->velocidad[1] = (f32) (((f64) (f32) (sp2_c % 3) * 0.2) + 0.4);
    }
    temporal_a0 = sp2_c % 8;
    objeto->desconocido_084[0] = dato_800E6F30[temporal_a0][0];
    objeto->desconocido_084[1] = dato_800E6F30[temporal_a0][1];
    objeto->desconocido_084[2] = dato_800E6F30[temporal_a0][2];
    objeto->desconocido_084[3] = dato_800E6F48[temporal_a0][0];
    objeto->desconocido_084[4] = dato_800E6F48[temporal_a0][1];
    objeto->desconocido_084[5] = dato_800E6F48[temporal_a0][2];
    objeto->desconocido_084[6] = sp20 - 0x1000;
    if (sp2_c & 1) {
        objeto->desconocido_084[7] = (sp20 / 32) + 0x100;
    } else {
        objeto->desconocido_084[7] = -0x100 - (sp20 / 32);
    }
    objeto->prim_alpha = 0x00E6;
    estado_siguiente_objeto(indice_objeto);
}

void funcion_80074D94(s32 indice_objeto) {
    if (lista_objeto[indice_objeto].desconocido_0AE == 1) {
        if ((dato_80165740 <= lista_objeto[indice_objeto].offset[1]) &&
            (abajo_paso_s16_hacia(&lista_objeto[indice_objeto].prim_alpha, 0, 8) != 0)) {
            funcion_80086F60(indice_objeto);
        }
        agregar_desplazamiento_y_velocidad_objeto(indice_objeto);
    }
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void funcion_80074E28(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) {
        case 1:
            funcion_80074924(indice_objeto);
            break;
        case 2:
            if (ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 1) != false) {
                funcion_80086E70(indice_objeto);
                break;
            }
        case 0:
            break;
        case 3:
            funcion_80041480(&lista_objeto[indice_objeto].desconocido_084[6], -0x1000, 0x1000, &lista_objeto[indice_objeto].desconocido_084[7]);
            if (lista_objeto[indice_objeto].desconocido_0AE == 0) {
                funcion_80072428(indice_objeto);
            }
            break;
    }
}

void funcion_80074EE8(void) {
    s32 algun_indice;
    s32 indice_objeto;
    s32 algun_cantidad;
    Objeto* objeto;

    algun_cantidad = 0;
    for (algun_indice = 0; algun_indice < dato_80165738; algun_indice++) {
        indice_objeto = particula_objeto_3[algun_indice];
        if (indice_objeto != ID_OBJETO_ELIMINADO) {
            objeto = &lista_objeto[indice_objeto];
            if (objeto->state != 0) {
                funcion_80074E28(indice_objeto);
                funcion_80074D94(indice_objeto);
                if (objeto->state == 0) {
                    eliminar_envoltorio_objeto(&particula_objeto_3[algun_indice]);
                }
                algun_cantidad += 1;
            }
        }
    }
    if (algun_cantidad == 0) {
        dato_80165730 = 0;
    }
}

void funcion_80074FD8(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) { /* irregular */
        case 0:
            break;
        case 1:
            if (funcion_80087E08(indice_objeto, lista_objeto[indice_objeto].velocidad[1], 0.12f,
                              lista_objeto[indice_objeto].desconocido_034, lista_objeto[indice_objeto].angulo_sentido[1],
                              0x00000064) != 0) {
                estado_siguiente_objeto(indice_objeto);
            }
            calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
            lista_objeto[indice_objeto].orientacion[0] += dato_8016582C[0];
            lista_objeto[indice_objeto].orientacion[1] += dato_8016582C[1];
            lista_objeto[indice_objeto].orientacion[2] += dato_8016582C[2];
            break;
        case 2:
            funcion_80086F60(indice_objeto);
            funcion_80072428(indice_objeto);
            break;
    }
}

void funcion_800750D8(s32 indice_objeto, s32 parametro1, Vec3f parametro2, s32 parametro3, s32 parametro4) {
    s32 sp24;
    s32 temporal_v0;
    Objeto* objeto;

    inicializar_objeto(indice_objeto, 0);
    sp24 = int_aleatorio(0x01F4U);
    temporal_v0 = int_aleatorio(0x0032U);
    objeto = &lista_objeto[indice_objeto];
    objeto->desconocido_0D5 = parametro3;
    objeto->escalado_tamanio = ((f64) (f32) sp24 * 0.0005) + 0.05;
    objeto->velocidad[1] = ((f64) (f32) temporal_v0 * (0.05 * 1.0)) + 2.0;
    objeto->desconocido_034 = ((f64) (f32) (temporal_v0 % 5) * 0.1) + 1.0;
    objeto->angulo_sentido[1] = (parametro1 << 0x10) / parametro4;
    objeto->pos_origen[0] = (parametro2[0] + (temporal_v0 / 2)) - 12.0f;
    objeto->pos_origen[1] = (parametro2[1] - 10.0) + int_aleatorio(0x000AU);
    objeto->pos_origen[2] = (parametro2[2] + (temporal_v0 / 2)) - 12.0f;
    objeto->orientacion[0] = sp24 << 7;
    objeto->orientacion[1] = temporal_v0 * 0x50;
    objeto->orientacion[2] = temporal_v0 * 0x50;
}

void funcion_80075304(Vec3f parametro0, s32 parametro1, s32 parametro2, s32 parametro3) {
    s32 variable_s1;
    s32 indice_objeto;

    for (variable_s1 = 0; variable_s1 < parametro3; variable_s1++) {
        switch (parametro1) { /* irregular */
            case 1:
                indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_1, &siguiente_libre_objeto_particula_1, objeto_particula_1_tamanio);
                break;
            case 2:
                indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_2, &siguiente_libre_objeto_particula_2, objeto_particula_2_tamanio);
                break;
            case 3:
                indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_3, &siguiente_libre_objeto_particula_3, objeto_particula_3_tamanio);
                break;
        }
        if (indice_objeto == ID_OBJETO_NULO) {
            break;
        }
        funcion_800750D8(indice_objeto, variable_s1, parametro0, parametro2, parametro3);
    }
}

void funcion_8007542C(s32 parametro0) {
    s32 indice_objeto;
    s32 variable_s2;
    s32* variable_s3;
    Objeto* objeto;

    dato_8016582C[0] += 0x2000;
    dato_8016582C[1] += 0x1000;
    dato_8016582C[2] += 0x1800;
    for (variable_s2 = 0; variable_s2 < 0x80; variable_s2++) {
        switch (parametro0) { /* irregular */
            case 1:
                variable_s3 = particula_objeto_1;
                break;
            case 2:
                variable_s3 = particula_objeto_2;
                break;
            case 3:
                variable_s3 = particula_objeto_3;
                break;
        }
        indice_objeto = variable_s3[variable_s2];
        if (indice_objeto != ID_OBJETO_ELIMINADO) {
            objeto = &lista_objeto[indice_objeto];
            if (objeto->state != 0) {
                funcion_80074FD8(indice_objeto);
                if (objeto->state == 0) {
                    eliminar_envoltorio_objeto(&variable_s3[variable_s2]);
                }
            }
        }
    }
}

void inicializar_humo_tren(s32 indice_objeto, Vec3f pos, f32 velocidad) {
    Objeto* objeto;
    SIN_USO s32 relleno[2];

    inicializar_objeto(indice_objeto, 0);
    objeto = &lista_objeto[indice_objeto];
    objeto->pos_origen[0] = pos[0];
    objeto->pos_origen[1] = pos[1];
    objeto->pos_origen[2] = pos[2];
    objeto->velocidad[1] = velocidad;
    objeto->type = int_aleatorio(0x0064U) + 0x1E;
}

s32 aparecer_humo_tren(s32 indice_tren, Vec3f pos, f32 velocidad) {
    s32 indice_objeto;

    if (indice_tren == 0) {
        indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_2, &siguiente_libre_objeto_particula_2, objeto_particula_2_tamanio);
        if (indice_objeto != ID_OBJETO_NULO) {
            inicializar_humo_tren(indice_objeto, pos, velocidad);
        }
    } else {
        indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_3, &siguiente_libre_objeto_particula_3, objeto_particula_3_tamanio);
        if (indice_objeto != ID_OBJETO_NULO) {
            inicializar_humo_tren(indice_objeto, pos, velocidad);
        }
    }
    return indice_objeto;
}

void funcion_80075698(s32 indice_objeto) {
    lista_objeto[indice_objeto].desconocido_0D5 = 1;
    lista_objeto[indice_objeto].textura_activo = dato_8018D490;
    lista_objeto[indice_objeto].textura_lista = dato_8018D490;
    lista_objeto[indice_objeto].prim_alpha = 0xFF;
    lista_objeto[indice_objeto].angulo_sentido[1] = 0;
    lista_objeto[indice_objeto].orientacion[0] = 0;
    lista_objeto[indice_objeto].orientacion[2] = 0;
    lista_objeto[indice_objeto].offset[0] = 0.0f;
    lista_objeto[indice_objeto].offset[1] = 0.0f;
    lista_objeto[indice_objeto].offset[2] = 0.0f;
    lista_objeto[indice_objeto].escalado_tamanio = 0.5f;
    estado_siguiente_objeto(indice_objeto);
}

void funcion_80075714(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) {
        case 1:
            funcion_80075698(indice_objeto);
            break;
        case 2:
            lista_objeto[indice_objeto].velocidad[1] -= 0.03;
            arriba_paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], 100.0f, lista_objeto[indice_objeto].velocidad[1]);
            funcion_8007415C(indice_objeto, &lista_objeto[indice_objeto].escalado_tamanio, 0.55f, 1.0f, 0.1f, 1, 0);
            if (funcion_80073B00(indice_objeto, &lista_objeto[indice_objeto].prim_alpha, 0xFF, 0x1E, 7, 0, 0) != 0) {
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 3:
            funcion_80072428(indice_objeto);
            break;
        case 0:
            break;
    }

    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void actualizar_humo_tren(void) {
    SIN_USO s32 relleno[2];
    s32 cantidad;
    s32 i;
    s32 temporal_a0;
    Objeto* objeto;
    if (dato_8016578C != 0) {
        dato_8016578C -= 1;
    }
    if (dato_80165790 != 0) {
        dato_80165790 -= 1;
    }
    if ((lista_tren[0].algun_banderas != 0) || (dato_8016578C != 0)) {
        cantidad = 0;
        for (i = 0; i < 128; i++) {
            temporal_a0 = particula_objeto_2[i];
            if (temporal_a0 != -1) {
                objeto = &lista_objeto[temporal_a0];
                if (objeto->state != 0) {
                    funcion_80075714(temporal_a0);
                    if (objeto->state == 0) {
                        eliminar_envoltorio_objeto(&particula_objeto_2[i]);
                    }
                    cantidad += 1;
                }
            }
        }
        if (cantidad != 0) {
            dato_8016578C = 100;
        }
    }
    if ((lista_tren[1].algun_banderas != 0) || (dato_80165790 != 0)) {
        cantidad = 0;
        for (i = 0; i < 128; i++) {
            temporal_a0 = particula_objeto_3[i];
            if (temporal_a0 != -1) {
                objeto = &lista_objeto[temporal_a0];
                if (objeto->state != 0) {
                    funcion_80075714(temporal_a0);
                    if (objeto->state == 0) {
                        eliminar_envoltorio_objeto(&particula_objeto_3[i]);
                    }
                    cantidad += 1;
                }
            }
        }
        if (cantidad != 0) {
            dato_80165790 = 100;
        }
    }
}

void inicializar_humo_ferry(s32 indice_objeto, Vec3f pos, f32 velocidad) {
    Objeto* objeto;

    inicializar_objeto(indice_objeto, 0);
    objeto = &lista_objeto[indice_objeto];
    objeto->pos_origen[0] = pos[0];
    objeto->pos_origen[1] = pos[1];
    objeto->pos_origen[2] = pos[2];
    objeto->velocidad[1] = velocidad;
    objeto->type = 0x00FF;
    objeto->desconocido_0A2 = 0x0096;
}

s32 aparecer_humo_ferry(s32 indice_ferry, Vec3f pos, f32 velocidad) {
    s32 indice_objeto;

    if (indice_ferry == 0) {
        indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_2, &siguiente_libre_objeto_particula_2, objeto_particula_2_tamanio);
        if (indice_objeto != ID_OBJETO_NULO) {
            inicializar_humo_ferry(indice_objeto, pos, velocidad);
        }
    } else {
        indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_3, &siguiente_libre_objeto_particula_3, objeto_particula_3_tamanio);
        if (indice_objeto != ID_OBJETO_NULO) {
            inicializar_humo_ferry(indice_objeto, pos, velocidad);
        }
    }

    return indice_objeto;
}

void funcion_80075B08(s32 indice_objeto) {
    lista_objeto[indice_objeto].desconocido_0D5 = 6;
    lista_objeto[indice_objeto].textura_activo = dato_8018D490;
    lista_objeto[indice_objeto].textura_lista = dato_8018D490;
    lista_objeto[indice_objeto].prim_alpha = 0xFF;
    lista_objeto[indice_objeto].angulo_sentido[1] = 0;
    lista_objeto[indice_objeto].orientacion[0] = 0;
    lista_objeto[indice_objeto].orientacion[2] = 0;
    lista_objeto[indice_objeto].offset[0] = 0.0f;
    lista_objeto[indice_objeto].offset[1] = 0.0f;
    lista_objeto[indice_objeto].offset[2] = 0.0f;
    lista_objeto[indice_objeto].escalado_tamanio = 0.5f;
    estado_siguiente_objeto(indice_objeto);
}

void funcion_80075B84(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) {
        case 1:
            funcion_80075B08(indice_objeto);
            break;
        case 2:
            lista_objeto[indice_objeto].velocidad[1] -= 0.03;
            arriba_paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], 100.0f, lista_objeto[indice_objeto].velocidad[1]);
            funcion_8007415C(indice_objeto, &lista_objeto[indice_objeto].escalado_tamanio, 0.55f, 1.0f, 0.1f, 1, 0);
            if (funcion_80073B00(indice_objeto, &lista_objeto[indice_objeto].prim_alpha, 0xFF, 0x1E, 7, 0, 0) != 0) {
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 3:
            funcion_80072428(indice_objeto);
            break;
        case 0:
            break;
    }

    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void actualizar_particula_humo_ferris(void) {
    SIN_USO s32 relleno[2];
    s32 cantidad;
    s32 i;
    s32 temporal_a0;
    Objeto* objeto;
    if (dato_8016578C != 0) {
        dato_8016578C -= 1;
    }
    if (dato_80165790 != 0) {
        dato_80165790 -= 1;
    }
    if ((barcos_paleta[0].algun_banderas != 0) || (dato_8016578C != 0)) {
        cantidad = 0;
        for (i = 0; i < 128; i++) {
            temporal_a0 = particula_objeto_2[i];
            if (temporal_a0 != -1) {
                objeto = &lista_objeto[temporal_a0];
                if (objeto->state != 0) {
                    funcion_80075B84(temporal_a0);
                    if (objeto->state == 0) {
                        eliminar_envoltorio_objeto(&particula_objeto_2[i]);
                    }
                    cantidad += 1;
                }
            }
        }
        if (cantidad != 0) {
            dato_8016578C = 100;
        }
    }
    if ((barcos_paleta[1].algun_banderas != 0) || (dato_80165790 != 0)) {
        cantidad = 0;
        for (i = 0; i < 128; i++) {
            temporal_a0 = particula_objeto_3[i];
            if (temporal_a0 != -1) {
                objeto = &lista_objeto[temporal_a0];
                if (objeto->state != 0) {
                    funcion_80075B84(temporal_a0);
                    if (objeto->state == 0) {
                        eliminar_envoltorio_objeto(&particula_objeto_3[i]);
                    }
                    cantidad += 1;
                }
            }
        }
        if (cantidad != 0) {
            dato_80165790 = 100;
        }
    }
}

void funcion_80075E5C(s32 indice_objeto, Vec3f parametro1, u16 parametro2, f32 parametro3, s32 parametro4) {
    Objeto* objeto;

    inicializar_objeto(indice_objeto, 0);
    objeto = &lista_objeto[indice_objeto];
    objeto->escalado_tamanio = 0.5f;
    objeto->desconocido_0D5 = 5;
    objeto->pos_origen[0] = parametro1[0];
    objeto->pos_origen[1] = parametro1[1];
    objeto->pos_origen[2] = parametro1[2];
    objeto->angulo_sentido[0] = 0x0C00;
    objeto->angulo_sentido[2] = 0;
    objeto->desconocido_034 = parametro3 * 4.0;
    objeto->angulo_sentido[1] = parametro2;
    objeto->type = 0x00FF;
    objeto->desconocido_0A2 = 0x00FF;
    objeto->desconocido_048 = parametro4 * 2;
}

s32 funcion_80075F28(Vec3f parametro0, u16 parametro1, f32 parametro2, s32 parametro3) {
    s32 indice_objeto;

    indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_1, &siguiente_libre_objeto_particula_1, objeto_particula_1_tamanio);
    if (indice_objeto != ID_OBJETO_NULO) {
        funcion_80075E5C(indice_objeto, parametro0, parametro1, parametro2, parametro3);
    }
    return indice_objeto;
}

void funcion_80075F98(Vec3f parametro0, u16 parametro1, f32 parametro2) {
    s32 algun_indice;

    for (algun_indice = 0; algun_indice < 10; algun_indice++) {
        if (funcion_80075F28(parametro0, parametro1, parametro2, algun_indice) == -1) {
            break;
        }
    }
}
