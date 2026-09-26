// Imagenes menu

void funcion_8009952C(TexturaMenu* direccion) {
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
            copiar_segmento_mio0_dma(direccion_tex->textura_datos, 0x00008000U, buffer_comprimido_menu);
            mio0decode((u8*) buffer_comprimido_menu, (u8*) &buffer_textura_menu[menu_textura_buffer_indice]);
            mapa_tex[entradas_textura_menu].textura_datos = direccion_tex->textura_datos;
            mapa_tex[entradas_textura_menu].offset = menu_textura_buffer_indice;
            menu_textura_buffer_indice += direccion_tex->height * direccion_tex->width;
            menu_textura_buffer_indice = ((menu_textura_buffer_indice / 8) * 8) + 8;
            entradas_textura_menu += 1;
        }
        direccion_tex++;
    }
}

void cargar_menu_img_mio0_forzado(TexturaMenu* direccion) {
    cargar_menu_img_comp_tipo(direccion, CARGA_MENU_IMG_MIO0_FORZAR);
}

void cargar_menu_img_comp_tipo(TexturaMenu* direccion, s32 tipo_comp) {
    u16 size;
    s32 i;
    s32 img_cargado;
    u8 borrar_bit;
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

        if ((img_cargado == false) || (tipo_comp > CARGA_MENU_IMG_FORZAR)) {
#ifdef AVOID_UB
            if (!cabe_textura_menu(direccion_tex)) {
                direccion_tex++;
                continue;
            }
#endif
            if (direccion_tex->size != 0) {
                size = direccion_tex->size;
            } else {
                size = 0x1000;
            }
            if (size % 8) {
                size = ((size / 8) * 8) + 8;
            }
            switch (tipo_comp) {
                case CARGA_MENU_IMG_MIO0_UNA_VEZ:
                case CARGA_MENU_IMG_MIO0_FORZAR:
                    copiar_segmento_mio0_dma(direccion_tex->textura_datos, size, buffer_comprimido_menu);
                    break;
                case CARGA_MENU_IMG_TKMK00_UNA_VEZ:
                case CARGA_MENU_IMG_TKMK00_FORZAR:
                    texturas_tkmk00_dma(direccion_tex->textura_datos, size, buffer_comprimido_menu);
                    break;
            }

            switch (tipo_comp) {
                case CARGA_MENU_IMG_MIO0_UNA_VEZ:
                case CARGA_MENU_IMG_MIO0_FORZAR:
                    mio0decode((u8*) buffer_comprimido_menu, (u8*) &buffer_textura_menu[menu_textura_buffer_indice]);
                    break;
                case CARGA_MENU_IMG_TKMK00_UNA_VEZ:
                case CARGA_MENU_IMG_TKMK00_FORZAR:
                    if (direccion_tex->type == 1) {
                        borrar_bit = 0xBE;
                    } else {
                        borrar_bit = 1;
                    }
                    if (1) {}
                    tkmk00decode(buffer_comprimido_menu, tkmk_00_bajo_res_buffer,
                                 &buffer_textura_menu[menu_textura_buffer_indice], borrar_bit);
                    break;
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

void funcion_80099958(TexturaMenu* direccion, s32 parametro1, s32 parametro2) {
    u16 size;
    TexturaMenu* direccion_tex;

    direccion_tex = segmentado_a_duplicado_virtual(direccion);
    while (direccion_tex->textura_datos != NULL) {
        if (direccion_tex->size != 0) {
            size = direccion_tex->size;
        } else {
            size = 0x1400;
        }
        if (size % 8) {
            size = ((size / 8) * 8) + 8;
        }
        copiar_segmento_mio0_dma(direccion_tex->textura_datos, size, buffer_comprimido_menu);
        mio0decode((u8*) buffer_comprimido_menu,
                   (u8*) dato_802BFB80.tamanio_arreglo_4[parametro2][parametro1 / 2][(parametro1 % 2) + 2].arreglo_indice_pixel);
        direccion_tex++;
    }
}

void funcion_80099A70(void) {
    s32 i;
    dato_8018E060[0].texture = NULL;
    for (i = 0; i < TAMANIO_D_8018E060; i++) {}
}

void funcion_80099A94(TexturaMenu* parametro0, s32 parametro1) {
    struct_8018E060_entrada* variable_v1;

    variable_v1 = &dato_8018E060[0];
    while (variable_v1->texture != NULL) {
        variable_v1++;
    }
    variable_v1->texture = segmentado_a_duplicado_virtual(parametro0);
    variable_v1->tex_num = parametro1;
}

void funcion_80099AEC(void) {
    s32 algun_variable;
    s8 fin_tex;
    struct_8018E060_entrada* variable_s1;
    TexturaMapa* entry;
    TexturaMenu* tex_ptr;
    OSIoMesg mb;
    OSMesg sp64;
    s32 tamanio_cache;
    s32 tamanio_buf;

    if (estado_juego == CARRERA) {
        tamanio_buf = 0x500;
    } else {
        tamanio_buf = 0x1000;
    }

    fin_tex = 0;
    entry = &mapa_textura_menu[0];
    variable_s1 = &dato_8018E060[0];
    tex_ptr = variable_s1->texture;

    if (tex_ptr == NULL) {
        return;
    }

    if (tex_ptr->size) {
        tamanio_cache = tex_ptr->size;
    } else {
        tamanio_cache = 0x1400;
    }
    if (tamanio_cache % 8) {
        tamanio_cache = ((tamanio_cache / 8) * 8) + 8;
    }

    osInvalDCache(buffer_comprimido_menu, tamanio_cache);
    osPiStartDma(&mb, 0, 0, (uintptr_t) _textures_0aSegmentRomStart + SEGMENT_OFFSET(tex_ptr->textura_datos),
                 buffer_comprimido_menu, tamanio_cache, &cola_msj_dma);
    osRecvMesg(&cola_msj_dma, &sp64, 1);

    while (1) {
        if ((variable_s1 + 1)->texture == NULL) {
            fin_tex += 1;
        } else {
            tex_ptr = (variable_s1 + 1)->texture;
            if (tex_ptr->size) {
                tamanio_cache = tex_ptr->size;
            } else {
                tamanio_cache = 0x1400;
            }
            if (tamanio_cache % 8) {
                tamanio_cache = ((tamanio_cache / 8) * 8) + 8;
            }
            osInvalDCache(&buffer_comprimido_menu[tamanio_buf], tamanio_cache);
            osPiStartDma(&mb, 0, 0, (uintptr_t) _textures_0aSegmentRomStart + SEGMENT_OFFSET(tex_ptr->textura_datos),
                         &buffer_comprimido_menu[tamanio_buf], tamanio_cache, &cola_msj_dma);
        }

        algun_variable = (entry + variable_s1->tex_num)->offset;

        mio0decode((u8*) buffer_comprimido_menu, (u8*) &buffer_textura_menu[algun_variable]);

        variable_s1->texture = NULL;
        variable_s1++;
        if (fin_tex) {
            break;
        }

        osRecvMesg(&cola_msj_dma, &sp64, 1);

        if ((variable_s1 + 1)->texture == NULL) {
            fin_tex += 1;
        } else {
            tex_ptr = (variable_s1 + 1)->texture;
            if (tex_ptr->size) {
                tamanio_cache = tex_ptr->size;
            } else {
                tamanio_cache = 0x1400;
            }
            if (tamanio_cache % 8) {
                tamanio_cache = ((tamanio_cache / 8) * 8) + 8;
            }
            osInvalDCache(buffer_comprimido_menu, tamanio_cache);
            osPiStartDma(&mb, 0, 0, (uintptr_t) _textures_0aSegmentRomStart + SEGMENT_OFFSET(tex_ptr->textura_datos),
                         buffer_comprimido_menu, tamanio_cache, &cola_msj_dma);
        }

        algun_variable = (entry + variable_s1->tex_num)->offset;
        mio0decode((u8*) &buffer_comprimido_menu[tamanio_buf], (u8*) &buffer_textura_menu[algun_variable]);
        variable_s1->texture = NULL;
        variable_s1++;
        if (fin_tex) {
            break;
        }
        osRecvMesg(&cola_msj_dma, &sp64, 1);
    }
}

void funcion_80099E54(void) {
    dato_8018E0E8[0].textura_mk64 = NULL;
}

void funcion_80099E60(TexturaMenu* parametro0, s32 parametro1, s32 parametro2) {
    struct_8018E0E8_entrada* variable_v1;

    variable_v1 = dato_8018E0E8;
    while (variable_v1->textura_mk64 != NULL) {
        variable_v1++;
    }
    variable_v1->textura_mk64 = segmentado_a_duplicado_virtual(parametro0);
    variable_v1->desconocido4 = parametro1;
    variable_v1->desconocido6 = parametro2;
}

void funcion_80099EC4(void) {
    s8 variable_s4;
    s32 variable_s0;
    SIN_USO s32 relleno[2];
    OSIoMesg sp68;
    OSMesg sp64;
    s32 huh;
    TexturaMenu* temporal_s2;
    struct_8018E0E8_entrada* variable_s1;

    variable_s4 = 0;
    variable_s1 = dato_8018E0E8;
    temporal_s2 = variable_s1->textura_mk64;

    if (temporal_s2 == NULL)
        return;

    huh = temporal_s2->size;
    if (huh != 0) {
        variable_s0 = huh;
    } else {
        variable_s0 = 0x1400;
    }
    if (variable_s0 % 8) {
        variable_s0 = ((variable_s0 / 8) * 8) + 8;
    }
    osInvalDCache((void*) buffer_comprimido_menu, variable_s0);
    osPiStartDma(&sp68, 0, 0, (u32) _textures_0aSegmentRomStart + SEGMENT_OFFSET(temporal_s2->textura_datos),
                 buffer_comprimido_menu, variable_s0, &cola_msj_dma);
    if ((variable_s0 && variable_s0) && variable_s0) {}
    osRecvMesg(&cola_msj_dma, &sp64, 1);
    while (1) {
        if ((variable_s1 + 1)->textura_mk64 == NULL) {
            variable_s4 += 1;
        } else {
            temporal_s2 = (variable_s1 + 1)->textura_mk64;
            huh = (variable_s1 + 1)->textura_mk64->size;
            if (huh != 0) {
                variable_s0 = huh;
            } else {
                variable_s0 = 0x1400;
            }
            if (variable_s0 % 8) {
                variable_s0 = ((variable_s0 / 8) * 8) + 8;
            }
            osInvalDCache(buffer_comprimido_menu + 0x500, variable_s0);
            osPiStartDma(&sp68, 0, 0, (u32) _textures_0aSegmentRomStart + SEGMENT_OFFSET(temporal_s2->textura_datos),
                         buffer_comprimido_menu + 0x500, variable_s0, &cola_msj_dma);
        }
        mio0decode((u8*) buffer_comprimido_menu,
                   dato_802BFB80.tamanio_arreglo_4[variable_s1->desconocido6][variable_s1->desconocido4 / 2][(variable_s1->desconocido4 % 2) + 2].arreglo_indice_pixel);
        variable_s1->textura_mk64 = NULL;
        variable_s1++;
        if (variable_s4 != 0)
            break;
        osRecvMesg(&cola_msj_dma, &sp64, 1);
        if ((variable_s1 + 1)->textura_mk64 == NULL) {
            variable_s4 += 1;
        } else {
            temporal_s2 = (variable_s1 + 1)->textura_mk64;
            huh = (variable_s1 + 1)->textura_mk64->size;
            if (huh != 0) {
                variable_s0 = huh;
            } else {
                variable_s0 = 0x1400;
            }
            if (variable_s0 % 8) {
                variable_s0 = ((variable_s0 / 8) * 8) + 8;
            }
            osInvalDCache(buffer_comprimido_menu, variable_s0);
            osPiStartDma(&sp68, 0, 0, (u32) _textures_0aSegmentRomStart + SEGMENT_OFFSET(temporal_s2->textura_datos),
                         buffer_comprimido_menu, variable_s0, &cola_msj_dma);
        }
        mio0decode((u8*) (buffer_comprimido_menu + 0x500),
                   dato_802BFB80.tamanio_arreglo_4[variable_s1->desconocido6][variable_s1->desconocido4 / 2][(variable_s1->desconocido4 % 2) + 2].arreglo_indice_pixel);
        variable_s1->textura_mk64 = NULL;
        variable_s1++;
        if (variable_s4 != 0)
            break;
        osRecvMesg(&cola_msj_dma, &sp64, 1);
    }
}

void funcion_8009A238(TexturaMenu* parametro0, s32 parametro1) {
    s32 variable_a3;
    s32 temporal_v1;
    u64* sp24;
    SIN_USO TexturaMapa* temporal_v0;

    temporal_v1 = mapa_textura_menu[parametro1].offset;
    sp24 = parametro0->textura_datos;
    variable_a3 = parametro0->size;
    if (variable_a3 % 8) {
        variable_a3 = ((variable_a3 / 8) * 8) + 8;
    }
    texturas_tkmk00_dma(sp24, variable_a3, buffer_comprimido_menu);
    tkmk00decode(buffer_comprimido_menu, tkmk_00_bajo_res_buffer, &buffer_textura_menu[temporal_v1], 1);
    mapa_textura_menu[parametro1].textura_datos = sp24;
}

void funcion_8009A2F0(struct_8018E0E8_entrada* parametro0) {
    TexturaMenu* variable_a0;
    struct_8018E0E8_entrada* temporal_v0;

    temporal_v0 = segmentado_a_duplicado_virtual_2(parametro0);
    variable_a0 = temporal_v0->textura_mk64;
    while (variable_a0 != NULL) {
        if (variable_a0 == NULL) {
            break;
        }
        cargar_menu_img_comp_tipo(variable_a0, CARGA_MENU_IMG_TKMK00_UNA_VEZ);
        if (1) {}
        temporal_v0++;
        variable_a0 = temporal_v0->textura_mk64;
    }
}

void funcion_8009A344(void) {
    s32 index;
    for (index = 0; index < TAMANIO_D_8018DEE0; index++) {
        dato_8018DEE0[index].visible = 0;
    }
}

s32 seleccionar_menu_personaje_animar(AnimacionMk* anim) {
    s32 i;
    struct_8018DEE0_entrada* entry;

    anim = segmentado_a_duplicado_virtual_2(anim);
    i = 0;
    while (dato_8018DEE0[i].visible) {
        i++;
        if (i >= 0x10) {
            // No more space.
            while (1) {
                ;
            }
        }
    }

    entry = &dato_8018DEE0[i];
    entry->textura_secuencia = anim;
    entry->indice_secuencia = -1;
    entry->abajo_cantidad_frame = 0;
    entry->visible = 0x80000000;
    entry->indice_textura_menu = entradas_textura_menu;

    if (anim[0].textura_mk64) {
        cargar_menu_img_mio0_forzado(anim[0].textura_mk64);
    }
    if (anim[1].textura_mk64) {
        cargar_menu_img_mio0_forzado(anim[1].textura_mk64);
    } else {
        cargar_menu_img_mio0_forzado(anim[0].textura_mk64);
    }

    entry->unk14 = 0;
    return i;
}

s32 funcion_8009A478(AnimacionMk* anim, s32 parametro1) {
    s32 i;
    struct_8018DEE0_entrada* entry;

    anim = segmentado_a_duplicado_virtual_2(anim);
    i = 0;
    while (dato_8018DEE0[i].visible) {
        i++;
        if (i >= 0x10) {
            // No more space.
            while (1) {
                ;
            }
        }
    }

    entry = &dato_8018DEE0[i];
    entry->textura_secuencia = anim;
    entry->indice_secuencia = -1;
    entry->abajo_cantidad_frame = 0;
    entry->visible = 0x80000000;
    entry->indice_textura_menu = entradas_textura_menu;
    if (anim[0].textura_mk64) {
        funcion_80099958(anim[0].textura_mk64, parametro1, 0);
    }
    if (anim[1].textura_mk64) {
        funcion_80099958(anim[1].textura_mk64, parametro1, 1);
    } else {
        funcion_80099958(anim[0].textura_mk64, parametro1, 1);
    }
    entry->unk14 = 0;
    return i;
}

void funcion_8009A594(s32 parametro0, s32 parametro1, AnimacionMk* parametro2) {
    AnimacionMk* temporal_v0;
    TexturaMenu* temporal_a0;

    temporal_v0 = segmentado_a_duplicado_virtual_2(parametro2);
    dato_8018DEE0[parametro0].textura_secuencia = temporal_v0;
    dato_8018DEE0[parametro0].indice_secuencia = parametro1;
    dato_8018DEE0[parametro0].abajo_cantidad_frame = (temporal_v0 + parametro1)->longitud_frame;
    temporal_a0 = segmentado_a_duplicado_virtual(temporal_v0[parametro1].textura_mk64);
    if (dato_8018DEE0[parametro0].unk14 != 0) {
        funcion_80099A94(temporal_a0, dato_8018DEE0[parametro0].indice_textura_menu);
        dato_8018DEE0[parametro0].unk14 = 0;
    } else {
        funcion_80099A94(temporal_a0, dato_8018DEE0[parametro0].indice_textura_menu + 1);
        dato_8018DEE0[parametro0].unk14 = 1;
    }
}

void funcion_8009A640(s32 parametro0, s32 parametro1, s32 parametro2, AnimacionMk* parametro3) {
    AnimacionMk* temporal_v0;
    TexturaMenu* temporal_a0;

    temporal_v0 = segmentado_a_duplicado_virtual_2(parametro3);
    dato_8018DEE0[parametro0].textura_secuencia = temporal_v0;
    dato_8018DEE0[parametro0].indice_secuencia = parametro1;
    dato_8018DEE0[parametro0].abajo_cantidad_frame = (temporal_v0 + parametro1)->longitud_frame;
    temporal_a0 = segmentado_a_duplicado_virtual(temporal_v0[parametro1].textura_mk64);
    dato_8018DEE0[parametro0].unk14 ^= 1;
    funcion_80099E60(temporal_a0, parametro2, dato_8018DEE0[parametro0].unk14);
}

SIN_USO void funcion_8009A6D4(void) {
    s32 index;
    for (index = 0; index < TAMANIO_D_8018DEE0; index++) {
        if ((dato_8018DEE0[index].visible & 0x80000000) != 0) {
            funcion_8009A878(&dato_8018DEE0[index]);
            display_list_cabeza = funcion_8009C434(display_list_cabeza, &dato_8018DEE0[index], 0, 0, 0);
        }
    }
    funcion_80099AEC();
}

void funcion_8009A76C(s32 parametro0, s32 parametro1, s32 parametro2, s32 parametro3) {
    struct_8018DEE0_entrada* temporal_ = &dato_8018DEE0[parametro0];
    if (temporal_->visible & 0x80000000) {
        funcion_8009A878(temporal_);
        display_list_cabeza = funcion_8009C434(display_list_cabeza, temporal_, parametro1, parametro2, parametro3);
    }
}

void funcion_8009A7EC(s32 parametro0, s32 parametro1, s32 parametro2, s32 parametro3, s32 parametro4) {
    struct_8018DEE0_entrada* temporal_ = &dato_8018DEE0[parametro0];
    if (temporal_->visible & 0x80000000) {
        funcion_8009A944(temporal_, parametro3);
        display_list_cabeza = funcion_8009C708(display_list_cabeza, temporal_, parametro1, parametro2, parametro3, parametro4);
    }
}

TexturaMenu* funcion_8009A878(struct_8018DEE0_entrada* parametro0) {
    AnimacionMk* temporal_v1;
    AnimacionMk* variable_v0;
    AnimacionMk* probar;
    TexturaMenu* temporal_a0;

    temporal_v1 = parametro0->textura_secuencia;
    if (parametro0->indice_secuencia < 0) {
        parametro0->indice_secuencia = 0;
        parametro0->abajo_cantidad_frame = 0;
    }
    parametro0->abajo_cantidad_frame--;
    if (parametro0->abajo_cantidad_frame <= 0) {
        parametro0->indice_secuencia++;
        variable_v0 = ((probar = temporal_v1) + parametro0->indice_secuencia);
        if (variable_v0->textura_mk64 == NULL) {
            parametro0->indice_secuencia = 0;
        }
        variable_v0 = (probar + parametro0->indice_secuencia);
        parametro0->abajo_cantidad_frame = variable_v0->longitud_frame;
        temporal_a0 = segmentado_a_duplicado_virtual(variable_v0->textura_mk64);
        if (parametro0->unk14 != 0) {
            funcion_80099A94(temporal_a0, parametro0->indice_textura_menu);
            parametro0->unk14 = 0;
        } else {
            funcion_80099A94(temporal_a0, parametro0->indice_textura_menu + 1);
            parametro0->unk14 = 1;
        }
    }
    return parametro0->textura_secuencia[parametro0->indice_secuencia].textura_mk64;
}

TexturaMenu* funcion_8009A944(struct_8018DEE0_entrada* parametro0, s32 parametro1) {
    AnimacionMk* temporal_v1;
    AnimacionMk* variable_v0;
    AnimacionMk* probar;
    TexturaMenu* temporal_a0;

    temporal_v1 = parametro0->textura_secuencia;
    if (parametro0->indice_secuencia < 0) {
        parametro0->indice_secuencia = 0;
        parametro0->abajo_cantidad_frame = 0;
    }
    parametro0->abajo_cantidad_frame--;
    if (parametro0->abajo_cantidad_frame <= 0) {
        parametro0->indice_secuencia++;
        variable_v0 = ((probar = temporal_v1) + parametro0->indice_secuencia);
        if (variable_v0->textura_mk64 == NULL) {
            parametro0->indice_secuencia = 0;
        }
        variable_v0 = (probar + parametro0->indice_secuencia);
        parametro0->abajo_cantidad_frame = variable_v0->longitud_frame;
        temporal_a0 = segmentado_a_duplicado_virtual(variable_v0->textura_mk64);
        parametro0->unk14 ^= 1;
        funcion_80099E60(temporal_a0, parametro1, parametro0->unk14);
    }
    return parametro0->textura_secuencia[parametro0->indice_secuencia].textura_mk64;
}

void funcion_8009A9FC(s32 parametro0, s32 parametro1, u32 parametro2, s32 parametro3) {
    s32 rojo;
    s32 verde;
    s32 azul;
    s32 newred;
    s32 newgreen;
    s32 newblue;
    s32 alpha;
    s32 temporal_t9;
    u16 temporal_a0;
    s32 variable_t1;
    u16* color0;
    u16* color1;

    color0 = &buffer_textura_menu[mapa_textura_menu[parametro0].offset];
    color1 = &buffer_textura_menu[mapa_textura_menu[parametro1].offset];
    for (variable_t1 = 0; (u32) variable_t1 < parametro2; variable_t1++) {
        temporal_a0 = TEXEL16(*color0);
        color0++;
        rojo = (temporal_a0 & 0xF800) >> 0xB;
        verde = (temporal_a0 & 0x7C0) >> 6;
        azul = (temporal_a0 & 0x3E) >> 1;
        alpha = temporal_a0 & 0x1;
        if (alpha) {}
        temporal_t9 = ((rojo * 0x4D) + (verde * 0x96) + (azul * 0x1D)) >> 8;
        newred = (((((temporal_t9 - rojo) * parametro3) >> 8) + rojo) << 0xB);
        newgreen = (((((((temporal_t9 * 7) / 8) - verde) * parametro3) >> 8) + verde) << 6);
        newblue = (((((((temporal_t9 * 6) / 8) - azul) * parametro3) >> 8) + azul) << 1);
        *color1++ = TEXEL16(newblue + newgreen + newred + alpha);
    }
}

void funcion_8009AB7C(s32 parametro0) {
    s32 rojo;
    s32 verde;
    s32 azul;
    s32 alpha;
    s32 newred;
    s32 newgreen;
    s32 newblue;
    u32 temporal_t9;
    s32 variable_v1;
    u16* color;

    color = &buffer_textura_menu[mapa_textura_menu[parametro0].offset];
    for (variable_v1 = 0; variable_v1 < 0x4B000; variable_v1++) {
        rojo = ((TEXEL16(*color) & 0xF800) >> 0xB) * 0x4D;
        verde = ((TEXEL16(*color) & 0x7C0) >> 6) * 0x96;
        azul = ((TEXEL16(*color) & 0x3E) >> 1) * 0x1D;
        alpha = TEXEL16(*color) & 0x1;
        temporal_t9 = rojo + verde + azul;
        temporal_t9 >>= 8;
        newred = temporal_t9 << 0xB;
        newgreen = temporal_t9 << 6;
        newblue = temporal_t9 << 1;
        *color++ = TEXEL16(newblue + newgreen + newred + alpha);
    }
}

void funcion_8009AD78(s32 parametro0, s32 parametro1) {
    s32 rojo;
    s32 verde;
    s32 azul;
    s32 alpha;
    SIN_USO s32 newred;
    SIN_USO s32 newgreen;
    SIN_USO s32 newblue;
    u32 temporal_t9;
    s32 variable_v1;
    s32 size;
    SIN_USO u16 temporal_a0;
    u16* color;

    color = &buffer_textura_menu[mapa_textura_menu[parametro0].offset];
    size = mapa_textura_menu[parametro0 + 1].offset - mapa_textura_menu[parametro0].offset;
    for (variable_v1 = 0; variable_v1 != size; variable_v1++) {
        rojo = ((TEXEL16(*color) & 0xF800) >> 0xB) * 0x4D;
        verde = ((TEXEL16(*color) & 0x7C0) >> 6) * 0x96;
        azul = ((TEXEL16(*color) & 0x3E) >> 1) * 0x1D;
        alpha = TEXEL16(*color) & 0x1;
        temporal_t9 = rojo + verde + azul;
        temporal_t9 = temporal_t9 >> 8;
        temporal_t9 += ((0x20 - temporal_t9) * parametro1) >> 8;
        *color++ = TEXEL16((temporal_t9 << 1) + (temporal_t9 << 6) + (temporal_t9 << 0xB) + alpha);
    }
}

void convertir_img_a_escala_grises(s32 parametro0, u32 parametro1) {
    u32 i;
    s32 rojo;
    s32 verde;
    s32 azul;
    s32 alpha;
    u32 temporal_t9;
    s32 size;
    u16* color;
    f32 sp48[32];

    for (i = 0; i < 32; i++) {
        sp48[i] = pot_menu(i / 32.0, (parametro1 * 1.5 / 256.0) + 0.25);
    }
    color = &buffer_textura_menu[mapa_textura_menu[parametro0].offset];
    size = mapa_textura_menu[parametro0 + 1].offset - mapa_textura_menu[parametro0].offset;
    for (i = 0; i < (u32) size; i++) {
        rojo = ((TEXEL16(*color) & 0xF800) >> 0xB) * 0x55;
        verde = ((TEXEL16(*color) & 0x7C0) >> 6) * 0x4B;
        azul = ((TEXEL16(*color) & 0x3E) >> 1) * 0x5F;
        alpha = TEXEL16(*color) & 0x1;
        temporal_t9 = rojo + verde + azul;
        temporal_t9 /= 256;
        temporal_t9 = sp48[temporal_t9] * 32.0f;
        if (temporal_t9 >= 32) {
            temporal_t9 = 31;
        }
        *color++ = TEXEL16((temporal_t9 << 1) + (temporal_t9 << 6) + (temporal_t9 << 0xB) + alpha);
    }
}

void ajustar_color_img(s32 parametro0, s32 parametro1, s32 parametro2, s32 parametro3, s32 parametro4) {
    s32 rojo;
    s32 verde;
    s32 azul;
    s32 alpha;
    s32 newred;
    s32 newgreen;
    s32 newblue;
    u32 temporal_t9;
    s32 variable_v1;
    u16* color;

    color = &buffer_textura_menu[mapa_textura_menu[parametro0].offset];
    for (variable_v1 = 0; variable_v1 != parametro1; variable_v1++) {
        rojo = ((TEXEL16(*color) & 0xF800) >> 0xB) * 0x4D;
        verde = ((TEXEL16(*color) & 0x7C0) >> 6) * 0x96;
        azul = ((TEXEL16(*color) & 0x3E) >> 1) * 0x1D;
        alpha = TEXEL16(*color) & 0x1;
        temporal_t9 = rojo + verde + azul;
        temporal_t9 = temporal_t9 / 256;
        newred = ((temporal_t9 * parametro2) / 256) << 0xB;
        newgreen = ((temporal_t9 * parametro3) / 256) << 6;
        newblue = ((temporal_t9 * parametro4) / 256) << 1;
        *color++ = TEXEL16(newred + newgreen + newblue + alpha);
    }
}

u16* funcion_8009B8C4(u64* parametro0) {
    SIN_USO s32 relleno[2];
    s32 desplazamiento;
    s32 encontrado;
    s32 algun_indice;

    encontrado = 0;
    for (algun_indice = 0; algun_indice < entradas_textura_menu; algun_indice++) {
        if (parametro0 == mapa_textura_menu[algun_indice].textura_datos) {
            encontrado = 1;
            desplazamiento = mapa_textura_menu[algun_indice].offset;
            break;
        }
    }

    if (encontrado != 0) {
        return &buffer_textura_menu[desplazamiento];
    }
    return NULL;
}

void funcion_8009B938(void) {
    gfx_ptr = (Gfx*) algun_buffer_dl;
    num_d_8018E768_entradas = 0;
}

void funcion_8009B954(TexturaMenu* parametro0) {
    dato_8018E768[num_d_8018E768_entradas].texturas = segmentado_a_duplicado_virtual(parametro0);
    dato_8018E768[num_d_8018E768_entradas].display_list = gfx_ptr;
}

void funcion_8009B998(void) {
    gSPEndDisplayList(gfx_ptr++);
    num_d_8018E768_entradas += 1;
}

Gfx* funcion_8009B9D0(Gfx* display_list_cabeza_2, TexturaMenu* texturas) {
    Gfx* display_list;
    SIN_USO s32 relleno;
    bool encontrado;
    s32 index;

    encontrado = false;
    for (index = 0; index < TAMANIO_D_8018E768; index++) {
        if (dato_8018E768[index].texturas == segmentado_a_duplicado_virtual(texturas)) {
            display_list = dato_8018E768[index].display_list;
            encontrado = true;
            break;
        }
    }
    if (encontrado) {
        gSPDisplayList(display_list_cabeza_2++, display_list);
        return display_list_cabeza_2;
    }
#ifdef AVOID_UB
    return display_list_cabeza_2;
#endif
}

Gfx* renderizar_texturas_menu(Gfx* parametro0, TexturaMenu* parametro1, s32 columna, s32 renglon) {
    TexturaMenu* temporal_v0;
    u8* temporal_v0_3;
    s8 variable_s4;

    temporal_v0 = segmentado_a_duplicado_virtual(parametro1);
    while (temporal_v0->textura_datos != NULL) {
        variable_s4 = 0;
        switch (temporal_v0->type) {
            case 0:
                gSPDisplayList(parametro0++, dato_02007708);
                break;
            case 1:
                gSPDisplayList(parametro0++, dato_02007728);
                break;
            case 2:
                gSPDisplayList(parametro0++, dato_02007748);
                break;
            case 3:
                gSPDisplayList(parametro0++, dato_02007768);
                variable_s4 = 3;
                break;
            case 4:
                gSPDisplayList(parametro0++, dato_02007788);
                break;
            default:
                gSPDisplayList(parametro0++, dato_02007728);
                break;
        }
        temporal_v0_3 = (u8*) funcion_8009B8C4(temporal_v0->textura_datos);
        if (temporal_v0_3 != 0) {
            if (tipo_transicion[4] != 4) {
                parametro0 =
                    funcion_80095E10(parametro0, variable_s4, 0x00000400, 0x00000400, 0, 0, temporal_v0->width, temporal_v0->height,
                                  temporal_v0->d_x + columna, temporal_v0->d_y + renglon, temporal_v0_3, temporal_v0->width, temporal_v0->height);
            } else {
                parametro0 = funcion_800987D0(parametro0, 0U, 0U, temporal_v0->width, temporal_v0->height, temporal_v0->d_x + columna,
                                     temporal_v0->d_y + renglon, temporal_v0_3, temporal_v0->width, temporal_v0->height);
            }
        }
        temporal_v0++;
    }
    return parametro0;
}

Gfx* funcion_8009BC9C(Gfx* parametro0, TexturaMenu* parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5) {
    TexturaMenu* variable_s0;
    u8* temporal_v0_3;

    variable_s0 = segmentado_a_duplicado_virtual(parametro1);
    while (variable_s0->textura_datos != NULL) {
        switch (variable_s0->type) { /* irregular */
            case 0:
                gSPDisplayList(parametro0++, dato_02007708);
                break;
            case 1:
                gSPDisplayList(parametro0++, dato_02007728);
                break;
        }
        temporal_v0_3 = (u8*) funcion_8009B8C4(variable_s0->textura_datos);
        if (temporal_v0_3 != 0) {
            switch (parametro4) {
                case 1:
                    parametro0 = funcion_80097AE4(parametro0, 0, variable_s0->d_x + parametro2, variable_s0->d_y + parametro3, temporal_v0_3, parametro5);
                    break;
                case 2:
                    parametro0 = funcion_80097E58(parametro0, 0, 0, 0U, variable_s0->width, variable_s0->height, variable_s0->d_x + parametro2,
                                         variable_s0->d_y + parametro3, temporal_v0_3, variable_s0->width, variable_s0->height, parametro5);
                    break;
                case 3:
                    parametro0 = funcion_80097A14(parametro0, 0, 0, 0, variable_s0->width, variable_s0->height, variable_s0->d_x + parametro2,
                                         variable_s0->d_y + parametro3, temporal_v0_3, variable_s0->width, variable_s0->height);
                    break;
                case 4:
                    parametro0 = funcion_80097274(parametro0, 0, 0x00000400, 0x00000400, 0, 0, variable_s0->width, variable_s0->height,
                                         variable_s0->d_x + parametro2, variable_s0->d_y + parametro3, (u16*) temporal_v0_3, variable_s0->width,
                                         variable_s0->height, parametro5);
                    break;
            }
        }
        variable_s0++;
    }
    return parametro0;
}
