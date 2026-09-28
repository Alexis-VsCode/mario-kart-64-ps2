// Descomprimir pista

void desempaquetar_spline_3D(Gfx* gfx, u8* parametro1, SIN_USO s8 parametro2) {
    uintptr_t temporal_v0;
    uintptr_t phi_a0;
    uintptr_t phi_t0;
    uintptr_t phi_a3;
    uintptr_t phi_a2;

    temporal_v0 = parametro1[posicion_buscar_empaquetado++];

    if (es_modo_espejo != 0) {
        phi_a0 = temporal_v0 & 0x1F;
        phi_a2 = ((temporal_v0 >> 5) & 7);
        temporal_v0 = parametro1[posicion_buscar_empaquetado++];
        phi_a2 |= ((temporal_v0 & 3) * 8);
        phi_a3 = (temporal_v0 >> 2) & 0x1F;
        phi_t0 = ((temporal_v0 >> 7) & 1);
        temporal_v0 = parametro1[posicion_buscar_empaquetado++];
        phi_t0 |= (temporal_v0 & 0xF) * 2;
    } else {
        phi_t0 = temporal_v0 & 0x1F;
        phi_a3 = ((temporal_v0 >> 5) & 7);
        temporal_v0 = parametro1[posicion_buscar_empaquetado++];
        phi_a3 |= ((temporal_v0 & 3) * 8);
        phi_a2 = (temporal_v0 >> 2) & 0x1F;
        phi_a0 = ((temporal_v0 >> 7) & 1);
        temporal_v0 = parametro1[posicion_buscar_empaquetado++];
        phi_a0 |= (temporal_v0 & 0xF) * 2;
    }
    gfx[gfx_posicion_buscar].words.w0 = ((uintptr_t) (uint8_t) G_QUAD << 24);
    gfx[gfx_posicion_buscar].words.w1 = ((phi_a0 * 2) << 24) | ((phi_t0 * 2) << 16) | ((phi_a3 * 2) << 8) | (phi_a2 * 2);
    gfx_posicion_buscar++;
}

SIN_USO void funcion_802A9AEC(void) {
}

void displaylist_desempaquetar(uintptr_t* datos, uintptr_t desplazamiento_displaylist_final, u32 parametro2) {
    uintptr_t segmento = SEGMENT_NUMBER2(datos);
    uintptr_t desplazamiento = SEGMENT_OFFSET(datos);
    u8* dl_empaquetado = VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);

    Gfx* gfx;
    u32 direccion;

    u8 opcode;

    desplazamiento_displaylist_final = ALIGN16(desplazamiento_displaylist_final) + 8;
    ptr_fin_monton -= desplazamiento_displaylist_final;
    direccion = ptr_fin_monton;
    gfx = (Gfx*) ptr_fin_monton;
    gfx_posicion_buscar = 0;
    posicion_buscar_empaquetado = 0;

    while (true) {

        opcode = dl_empaquetado[posicion_buscar_empaquetado++];

        if (opcode == 0xFF) {
            break;
        }

        switch (opcode) {
            case LUCES_PG_0 + 0x0:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0x1:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0x2:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0x3:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0x4:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0x5:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0x6:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0x7:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0x8:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0x9:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0xA:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0xB:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0xC:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0xD:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0xE:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0xF:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0x10:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0x11:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0x12:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0x13:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case LUCES_PG_0 + 0x14:
                desempaquetar_luces(gfx, dl_empaquetado, opcode);
                break;
            case PG_SETCOMBINE_CC_MODULATERGBA:
                desempaquetar_modo1_combinacion(gfx, dl_empaquetado, parametro2);
                break;
            case PG_SETCOMBINE_CC_MODULATERGBDECALA:
                desempaquetar_modo2_combinacion(gfx, dl_empaquetado, parametro2);
                break;
            case PG_SETCOMBINE_CC_SOMBREADO:
                desempaquetar_sombreado_modo_combinacion(gfx, dl_empaquetado, parametro2);
                break;
            case 0x2E:
                desempaquetar_modo4_combinacion(gfx, dl_empaquetado, parametro2);
                break;
            case PG_SETCOMBINE_CC_DECALRGBA:
                desempaquetar_modo5_combinacion(gfx, dl_empaquetado, parametro2);
                break;
            case PG_RMODE_OPA:
                renderizar_opaco_modo_desempaquetar(gfx, dl_empaquetado, parametro2);
                break;
            case PG_RMODE_TEXEDGE:
                renderizar_borde_tex_modo_desempaquetar(gfx, dl_empaquetado, parametro2);
                break;
            case PG_RMODE_XLU:
                renderizar_translucido_modo_desempaquetar(gfx, dl_empaquetado, parametro2);
                break;
            case PG_RMODE_OPA_DECAL:
                renderizar_decal_opaco_modo_desempaquetar(gfx, dl_empaquetado, parametro2);
                break;
            case PG_RMODE_XLU_DECAL:
                renderizar_decal_translucido_modo_desempaquetar(gfx, dl_empaquetado, parametro2);
                break;
            case PG_TILECFG_A:
                desempaquetar_sincronizacion_tile(gfx, dl_empaquetado, opcode);
                break;
            case PG_TILECFG_G:
                desempaquetar_sincronizacion_tile(gfx, dl_empaquetado, opcode);
                break;
            case PG_TILECFG_B:
                desempaquetar_sincronizacion_tile(gfx, dl_empaquetado, opcode);
                break;
            case PG_TILECFG_C:
                desempaquetar_sincronizacion_tile(gfx, dl_empaquetado, opcode);
                break;
            case PG_TILECFG_D:
                desempaquetar_sincronizacion_tile(gfx, dl_empaquetado, opcode);
                break;
            case PG_TILECFG_E:
                desempaquetar_sincronizacion_tile(gfx, dl_empaquetado, opcode);
                break;
            case PG_TILECFG_F:
                desempaquetar_sincronizacion_tile(gfx, dl_empaquetado, opcode);
                break;
            case CARGAR_BLOQUE_TIMG_PG_0:
                cargar_sincronizacion_tile_desempaquetar(gfx, dl_empaquetado, opcode);
                break;
            case CARGAR_BLOQUE_TIMG_PG_1:
                cargar_sincronizacion_tile_desempaquetar(gfx, dl_empaquetado, opcode);
                break;
            case CARGAR_BLOQUE_TIMG_PG_2:
                cargar_sincronizacion_tile_desempaquetar(gfx, dl_empaquetado, opcode);
                break;
            case CARGAR_BLOQUE_TIMG_PG_3:
                cargar_sincronizacion_tile_desempaquetar(gfx, dl_empaquetado, opcode);
                break;
            case CARGAR_BLOQUE_TIMG_PG_4:
                cargar_sincronizacion_tile_desempaquetar(gfx, dl_empaquetado, opcode);
                break;
            case CARGAR_BLOQUE_TIMG_PG_5:
                cargar_sincronizacion_tile_desempaquetar(gfx, dl_empaquetado, opcode);
                break;
            case TEXTURA_PG_EN:
                desempaquetar_textura_en(gfx, dl_empaquetado, opcode);
                break;
            case APAGADO_TEXTURA_PG:
                desempaquetar_apagado_textura(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX1:
                desempaquetar_vtx1(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x01:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x02:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x03:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x04:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x05:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x06:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x07:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x08:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x09:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x0A:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x0B:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x0C:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x0D:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x0E:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x0F:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x10:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x11:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x12:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x13:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x14:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x15:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x16:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x17:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x18:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x19:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x1A:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x1B:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x1C:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x1D:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x1E:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x1F:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_VTX_BASE + 0x20:
                desempaquetar_vtx2(gfx, dl_empaquetado, opcode);
                break;
            case PG_TRI1:
                desempaquetar_triangulo(gfx, dl_empaquetado, opcode);
                break;
            case PG_TRI2:
                desempaquetar_cuadrangulo(gfx, dl_empaquetado, opcode);
                break;
            case PG_SPLINE3D:
                desempaquetar_spline_3D(gfx, dl_empaquetado, opcode);
                break;
            case PG_CULLDL:
                desempaquetar_displaylist_descarte(gfx, dl_empaquetado, opcode);
                break;
            case PG_ENDDL:
                desempaquetar_displaylist_fin(gfx, dl_empaquetado, opcode);
                break;
            case PG_SETGEOMETRYMODE:
                fijar_modo_geometria_desempaquetar(gfx, dl_empaquetado, opcode);
                break;
            case PG_CLEARGEOMETRYMODE:
                borrar_modo_geometria_desempaquetar(gfx, dl_empaquetado, opcode);
                break;
            case PG_DL:
                desempaquetar_displaylist(gfx, dl_empaquetado, opcode);
                break;
            default:
                break;
        }
    }
    fijar_direccion_base_segmento(0x7, (void*) direccion);
}

struct desconocido_cad_802AA7C8 {
    u8* desconocido0;
    uintptr_t desconocido4;
    uintptr_t desconocido8;
    uintptr_t desconocido_c;
};

void descomprimir_texturas(u32* parametro0) {
    u32 segmento = SEGMENT_NUMBER2(parametro0);
    u32 desplazamiento = SEGMENT_OFFSET(parametro0);
    struct desconocido_cad_802AA7C8* phi_s0 = (struct desconocido_cad_802AA7C8*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    struct desconocido_cad_802AA7C8* temporal_s0;
    uintptr_t temporal_t2;
    u8* temporal_a0;
    uintptr_t phi_v0;
    uintptr_t sp20;

    phi_v0 = 0;
    temporal_s0 = phi_s0;
    while (true) {
        temporal_a0 = phi_s0->desconocido0;
        if ((temporal_a0) == 0) {
            break;
        }
        phi_v0 += phi_s0->desconocido8;
        phi_s0++;
    }
    phi_s0 = temporal_s0;
    ptr_fin_monton -= phi_v0;
    sp20 = ptr_fin_monton;

    while (true) {
        temporal_a0 = phi_s0->desconocido0;
        if ((temporal_a0) == 0) {
            break;
        }
        MIO0_0F(temporal_a0, phi_s0->desconocido4, phi_s0->desconocido8);
        phi_s0++;
    }
    ptr_fin_monton = sp20;
    temporal_t2 = ptr_fin_monton;
    fijar_direccion_base_segmento(0x5, (void*) temporal_t2);
#ifdef TARGET_PS2
    ps2_tmem_estatico_rango((void*) temporal_t2, phi_v0);
#endif
}

void* descomprimir_segmentos(u8* empezar, u8* end) {
    SIN_USO u32 relleno;
    u32 sp28;
    u32 size = ALIGN16(end - empezar);
    u8* fin_monton;
    u32* liberar_espacio;

    fin_monton = (u8*) ptr_fin_monton - size;
    copiar_dma(fin_monton, empezar, size);
    sp28 = TAMANIO_SIN_COMPRIMIR_MIO0(fin_monton);
    sp28 = ALIGN16(sp28);
    liberar_espacio = (u32*) siguiente_libre_memoria_direccion;
    mio0decode(fin_monton, (u8*) liberar_espacio);
    siguiente_libre_memoria_direccion += sp28;
    return (void*) liberar_espacio;
}

u8* cargar_circuito(s32 id_circuito) {
    SIN_USO s32 relleno[4];
    u8* vtx_comprimido;
    u8* circuito_datos_rom_inicio;
    u8* circuito_datos_rom_fin;
    u8* inicio_rom_vertice;
    u8* fin_rom_vertice;
    SIN_USO s32 relleno2[2];
    u32* texturas;
    VtxCircuito* inicio_vertice;
    u8* inicio_empaquetado;
    u32 cantidad_vertice;
    u8* desplazamiento_displaylist_final;
    u32 desconocido1;
    s32 ant_cargado_direccion_guardado;
    u8* inicio_rom_desplazamiento;
    u8* fin_rom_desplazamiento;

    circuito_datos_rom_inicio = tabla_circuito[id_circuito].dl_inicio_rom;
    circuito_datos_rom_fin = tabla_circuito[id_circuito].dl_fin_rom;
    inicio_rom_desplazamiento = tabla_circuito[id_circuito].inicio_rom_desplazamiento;
    fin_rom_desplazamiento = tabla_circuito[id_circuito].fin_rom_desplazamiento;
    inicio_rom_vertice = tabla_circuito[id_circuito].inicio_rom_vertice;
    fin_rom_vertice = tabla_circuito[id_circuito].fin_rom_vertice;
    texturas = tabla_circuito[id_circuito].texturas;
    inicio_vertice = tabla_circuito[id_circuito].inicio_vertice;
    inicio_empaquetado = tabla_circuito[id_circuito].inicio_empaquetado;
    cantidad_vertice = tabla_circuito[id_circuito].cantidad_vertice;
    desplazamiento_displaylist_final = tabla_circuito[id_circuito].desplazamiento_displaylist_final;
    desconocido1 = tabla_circuito[id_circuito].unknown1;

#ifdef TARGET_PS2
    ps2_tmem_estatico_rango(NULL, 0);
#endif
    if ((estado_juego == FINAL) || (estado_juego == SECUENCIA_CREDITOS)) {
        ptr_fin_monton = FINAL_SEG;
    } else {
        ptr_fin_monton = CARRERA_SEG;
    }
    fijar_direccion_base_segmento(9, cargar_datos((uintptr_t) inicio_rom_desplazamiento, (uintptr_t) fin_rom_desplazamiento));
    MARCAR_TIEMPOS_PS2("pista: desplazamientos");

    if (estado_juego != FINAL) {
        fijar_direccion_base_segmento(6, descomprimir_segmentos(circuito_datos_rom_inicio, circuito_datos_rom_fin));
        MARCAR_TIEMPOS_PS2("pista: datos (mio0)");
    }
    ant_cargado_direccion_guardado = siguiente_libre_memoria_direccion;
    vtx_comprimido = vtx_comprimido_dma(inicio_rom_vertice, fin_rom_vertice);
    MARCAR_TIEMPOS_PS2("pista: vértices (copia)");

    fijar_direccion_base_segmento(0xF, (void*) vtx_comprimido);
    descomprimir_vtx(inicio_vertice, cantidad_vertice);
    MARCAR_TIEMPOS_PS2("pista: vértices (mio0)");
    displaylist_desempaquetar((uintptr_t*) inicio_empaquetado, (uintptr_t) desplazamiento_displaylist_final, desconocido1);
    MARCAR_TIEMPOS_PS2("pista: listas de dibujo");
    descomprimir_texturas(texturas);
    MARCAR_TIEMPOS_PS2("pista: texturas (mio0)");
    siguiente_libre_memoria_direccion = ant_cargado_direccion_guardado;
    return vtx_comprimido;
}
