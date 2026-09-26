// Pools y segmentos

#ifdef TARGET_PS2
void ps2_tmem_estatico_rango(const void* empezar, u32 size);
void ps2_tmem_estatico_bloque(const void* empezar, u32 size, int permanente);
#endif
#include "sistema/bucle_principal.h"
#include "carrera/preparacion_carrera.h"
#include "sistema/matematicas.h"
#include "datos/tabla_pistas.h"
#include "juego/definiciones.h"

s32 gfx_posicion_buscar;
s32 posicion_buscar_empaquetado;

uintptr_t espacio_libre_pool;
struct BloquePoolPrincipal* cabeza_l_lista_pool;
struct BloquePoolPrincipal* cabeza_r_lista_pool;

struct EstadoPoolPrincipal* estado_pool_principal = NULL;

struct desconocido_struct_802B8CD4 dato_802B8CD4[] = { 0 };
s32 dato_802B8CE4 = 0;
s32 margen_memoria[2];

enum OpEmpaquetado {
    LUCES_PG_0               = 0x00, /* 0..0x14 mappés sur desempaquetar_luces */
    /* Presets de combine renommés pour refléter les macros G_CC_* */
    PG_SETCOMBINE_CC_MODULATERGBA      = 0x15,
    PG_SETCOMBINE_CC_MODULATERGBDECALA = 0x16,
    PG_SETCOMBINE_CC_SOMBREADO             = 0x17,
    PG_RMODE_OPA             = 0x18,
    PG_RMODE_TEXEDGE         = 0x19,
    PG_TILECFG_A             = 0x1A,
    PG_TILECFG_B             = 0x1B,
    PG_TILECFG_C             = 0x1C,
    PG_TILECFG_D             = 0x1D,
    PG_TILECFG_E             = 0x1E,
    PG_TILECFG_F             = 0x1F,
    CARGAR_BLOQUE_TIMG_PG_0      = 0x20,
    CARGAR_BLOQUE_TIMG_PG_1      = 0x21,
    CARGAR_BLOQUE_TIMG_PG_2      = 0x22,
    CARGAR_BLOQUE_TIMG_PG_3      = 0x23,
    CARGAR_BLOQUE_TIMG_PG_4      = 0x24,
    CARGAR_BLOQUE_TIMG_PG_5      = 0x25,
    TEXTURA_PG_EN            = 0x26,
    APAGADO_TEXTURA_PG           = 0x27,
    PG_VTX1                  = 0x28,
    PG_TRI1                  = 0x29,
    PG_ENDDL                 = 0x2A,
    PG_DL                    = 0x2B,
    PG_TILECFG_G             = 0x2C,
    PG_CULLDL                = 0x2D,
    PG_SETCOMBINE_ALT        = 0x2E,
    PG_RMODE_XLU             = 0x2F,
    PG_SPLINE3D              = 0x30,
    PG_VTX_BASE              = 0x32,
    PG_SETCOMBINE_CC_DECALRGBA  = 0x53,
    PG_RMODE_OPA_DECAL       = 0x54,
    PG_RMODE_XLU_DECAL       = 0x55,
    PG_SETGEOMETRYMODE       = 0x56,
    PG_CLEARGEOMETRYMODE     = 0x57,
    PG_TRI2                  = 0x58,
    FIN_ARCHIVO_PG                   = 0xFF,
};

void* obtener_siguiente_disponible_memoria_direccion(uintptr_t size) {
    uintptr_t liberar_espacio = (uintptr_t) siguiente_libre_memoria_direccion;
    size = ALIGN16(size);
    siguiente_libre_memoria_direccion += size;
#if defined(TARGET_PS2) && defined(SMK64_DEV)
    if (size >= 0x2000) {
        void registrar(const char* fmt, ...);
        registrar("heap: +%x en %x (fin %x, techo %x) desde %p", (unsigned) size, (unsigned) liberar_espacio,
                (unsigned) siguiente_libre_memoria_direccion, (unsigned) ptr_fin_monton, __builtin_return_address(0));
    }
#endif
    return (void*) liberar_espacio;
}

uintptr_t fijar_direccion_base_segmento(s32 segmento, void* direccion) {
    tabla_segmento[segmento] = (uintptr_t) direccion & 0x1FFFFFFF;
#if defined(TARGET_PS2) && defined(SMK64_DEV)
    if (segmento == 2) {
        void registrar(const char* fmt, ...);
        void fijar_vigilancia(void* direccion);
        registrar("segmento 2 = %p (desde %p)", direccion, __builtin_return_address(0));
        fijar_vigilancia(&tabla_segmento[2]);
    }
#endif
    return tabla_segmento[segmento];
}

void* obtener_direccion_base_segmento(s32 segmento) {
    return (void*) FISICO_A_VIRTUAL(tabla_segmento[segmento]);
}

void* segmentado_a_virtual(const void* direccion) {
    size_t segmento = (uintptr_t) direccion >> 24;
    size_t desplazamiento = (uintptr_t) direccion & 0x00FFFFFF;

    return (void*) FISICO_A_VIRTUAL(tabla_segmento[segmento] + desplazamiento);
}

void mover_tabla_segmento_a_dmem(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        gSPSegment(display_list_cabeza++, i, tabla_segmento[i]);
    }
}

void inicializar_pool_memoria(uintptr_t inicio_pool, uintptr_t fin_pool) {

    inicio_pool = ALIGN16(inicio_pool);
    fin_pool &= ~0xF;

    tamanio_memoria_libre = (fin_pool - inicio_pool) - 0x10;
    siguiente_libre_memoria_direccion = inicio_pool;
}

void* reservar_memoria(size_t size) {
    uintptr_t liberar_espacio;

    size = ALIGN16(size);
    tamanio_memoria_libre -= size;
    liberar_espacio = siguiente_libre_memoria_direccion;
    siguiente_libre_memoria_direccion += size;

    return (void*) liberar_espacio;
}

SIN_USO void funcion_802A7D54(s32 parametro0, s32 parametro1) {
    g_d_80150158[parametro0].desconocido0 = parametro0;
    g_d_80150158[parametro0].desconocido8 = parametro1;
}

void* cargar_datos(uintptr_t empezar_direccion, uintptr_t direccion_fin) {
    void* reservado;
    uintptr_t size = direccion_fin - empezar_direccion;

    reservado = reservar_memoria(size);
    if (reservado != 0) {
        copiar_dma((u8*) reservado, (u8*) empezar_direccion, size);
    }
    return (void*) reservado;
}

SIN_USO void inicializar_pool_principal(uintptr_t empezar, uintptr_t end) {
    empezar = ALIGN16(empezar);
    end = ALIGN16(end - 15);

    espacio_libre_pool = (end - empezar) - 16;

    cabeza_l_lista_pool = (struct BloquePoolPrincipal*) empezar;
    cabeza_r_lista_pool = (struct BloquePoolPrincipal*) end;
    cabeza_l_lista_pool->prev = NULL;
    cabeza_l_lista_pool->next = NULL;
    cabeza_r_lista_pool->prev = NULL;
    cabeza_r_lista_pool->next = NULL;
}

SIN_USO void* reservar_pool_principal(uintptr_t size, uintptr_t lado) {
    struct BloquePoolPrincipal* cabeza_lista_nuevo;
    void* direccion = NULL;

    size = ALIGN16(size) + 8;
    if (espacio_libre_pool >= size) {
        espacio_libre_pool -= size;
        if (lado == IZQUIERDA_POOL_MEMORIA) {
            cabeza_lista_nuevo = (struct BloquePoolPrincipal*) ((u8*) cabeza_l_lista_pool + size);
            cabeza_l_lista_pool->next = cabeza_lista_nuevo;
            cabeza_lista_nuevo->prev = cabeza_l_lista_pool;
            direccion = (u8*) cabeza_l_lista_pool + 8;
            cabeza_l_lista_pool = cabeza_lista_nuevo;
        } else {
            cabeza_lista_nuevo = (struct BloquePoolPrincipal*) ((u8*) cabeza_r_lista_pool - size);
            cabeza_r_lista_pool->prev = cabeza_lista_nuevo;
            cabeza_lista_nuevo->next = cabeza_r_lista_pool;
            cabeza_r_lista_pool = cabeza_lista_nuevo;
            direccion = (u8*) cabeza_r_lista_pool + 8;
        }
    }
    return direccion;
}
SIN_USO uintptr_t liberar_pool_principal(void* direccion) {
    struct BloquePoolPrincipal* bloque_3 = (struct BloquePoolPrincipal*) ((u8*) direccion - 8);
    struct BloquePoolPrincipal* cabeza_lista_viejo = (struct BloquePoolPrincipal*) ((u8*) direccion - 8);

    if (cabeza_lista_viejo < cabeza_l_lista_pool) {
        while (cabeza_lista_viejo->next != NULL) {
            cabeza_lista_viejo = cabeza_lista_viejo->next;
        }
        cabeza_l_lista_pool = bloque_3;
        cabeza_l_lista_pool->next = NULL;
        espacio_libre_pool += (uintptr_t) cabeza_lista_viejo - (uintptr_t) cabeza_l_lista_pool;
    } else {
        while (cabeza_lista_viejo->prev != NULL) {
            cabeza_lista_viejo = cabeza_lista_viejo->prev;
        }
        cabeza_r_lista_pool = bloque_3->next;
        cabeza_r_lista_pool->prev = NULL;
        espacio_libre_pool += (uintptr_t) cabeza_r_lista_pool - (uintptr_t) cabeza_lista_viejo;
    }
    return espacio_libre_pool;
}
SIN_USO void* rehacer_reserva_pool_principal(void* direccion, uintptr_t size) {
    void* direccion_nuevo = NULL;
    struct BloquePoolPrincipal* bloque_3 = (struct BloquePoolPrincipal*) ((u8*) direccion - 8);

    if (bloque_3->next == cabeza_l_lista_pool) {
        liberar_pool_principal(direccion);
        direccion_nuevo = reservar_pool_principal(size, IZQUIERDA_POOL_MEMORIA);
    }
    return direccion_nuevo;
}

SIN_USO uintptr_t disponible_pool_principal(void) {
    return espacio_libre_pool - 8;
}

SIN_USO uintptr_t empujar_estado_pool_principal(void) {
    struct EstadoPoolPrincipal* estado_ant = estado_pool_principal;
    uintptr_t liberar_espacio = espacio_libre_pool;
    struct BloquePoolPrincipal* lhead = cabeza_l_lista_pool;
    struct BloquePoolPrincipal* rhead = cabeza_r_lista_pool;

    estado_pool_principal = reservar_pool_principal(sizeof(*estado_pool_principal), IZQUIERDA_POOL_MEMORIA);
    estado_pool_principal->freeSpace = liberar_espacio;
    estado_pool_principal->cabeza_l_lista = lhead;
    estado_pool_principal->cabeza_r_lista = rhead;
    estado_pool_principal->prev = estado_ant;
    return espacio_libre_pool;
}

SIN_USO uintptr_t sacar_estado_pool_principal(void) {
    espacio_libre_pool = estado_pool_principal->freeSpace;
    cabeza_l_lista_pool = estado_pool_principal->cabeza_l_lista;
    cabeza_r_lista_pool = estado_pool_principal->cabeza_r_lista;
    estado_pool_principal = estado_pool_principal->prev;
    return espacio_libre_pool;
}
SIN_USO void* funcion_802A80B0(u8* dest, u8* inicio_orig, u8* fin_orig) {
    void* direccion;
    uintptr_t size = inicio_orig - dest;
    direccion = reservar_pool_principal(size, (uintptr_t) fin_orig);

    if (direccion != 0) {

        osInvalDCache(direccion, size);
        osPiStartDma(&msj_io_dma, OS_MESG_PRI_NORMAL, OS_READ, (uintptr_t) dest, direccion, size, &cola_msj_dma);
        osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
    }
    return direccion;
}

SIN_USO void* cargar_segmento(s32 segmento, u8* inicio_orig, u8* fin_orig, u8* lado) {
    void* direccion = funcion_802A80B0(inicio_orig, fin_orig, lado);

    if (direccion != NULL) {
        fijar_direccion_base_segmento(segmento, direccion);
    }
    return direccion;
}

SIN_USO void* funcion_802A8190(s32 parametro0, u8* parametro1) {
    void* direccion;
    uintptr_t temporal_v0 = dato_802B8CD4[parametro0].desconocido4;
    uintptr_t temporal_v1 = dato_802B8CD4[parametro0].desconocido8;
    uintptr_t temporal_v2 = dato_802B8CD4[parametro0].desconocido2;
    direccion = funcion_802A80B0((u8*) temporal_v0, (u8*) temporal_v1, parametro1);

    if (direccion != 0) {
        fijar_direccion_base_segmento(temporal_v2, direccion);
    }
    return (void*) direccion;
}

SIN_USO void funcion_802A81EC(void) {
    s32 temporal_s0;
    s16* phi_s1;
    s32 phi_s0;

    phi_s1 = (s16*) &dato_802B8CD4;
    phi_s0 = 0;
    do {
        if ((*phi_s1 & 1) != 0) {
            funcion_802A8190(phi_s0, 0);
        }
        temporal_s0 = phi_s0 + 1;
        phi_s1 += 8;
        phi_s0 = temporal_s0;
    } while (phi_s0 != 3);
}

SIN_USO struct PoolSoloReserva* inicializar_pool_solo_reserva(uintptr_t size, uintptr_t lado) {
    void* direccion;
    struct PoolSoloReserva* sub_pool = NULL;

    size = ALIGN4(size);
    direccion = reservar_pool_principal(size + sizeof(struct PoolSoloReserva), lado);
    if (direccion != NULL) {
        sub_pool = (struct PoolSoloReserva*) direccion;
        sub_pool->espacio_total = size;
        sub_pool->espacio_usado = (s32) direccion + sizeof(struct PoolSoloReserva);
        sub_pool->ptr_inicio = 0;
        sub_pool->ptr_libre = (u8*) direccion + sizeof(struct PoolSoloReserva);
    }
    return sub_pool;
}

SIN_USO uintptr_t funcion_802A82AC(s32 parametro0) {
    uintptr_t temporal_v0;
    uintptr_t phi_v1;

    temporal_v0 = dato_801502A0 - parametro0;
    phi_v1 = 0;
    if (temporal_v0 >= (uintptr_t) display_list_cabeza) {
        dato_801502A0 = temporal_v0;
        phi_v1 = temporal_v0;
    }
    return phi_v1;
}

u8* vtx_comprimido_dma(u8* empezar, u8* end) {
    u8* liberar_espacio;
    uintptr_t size;

    size = ALIGN16(end - empezar);
    liberar_espacio = (u8*) siguiente_libre_memoria_direccion;
    copiar_dma(liberar_espacio, empezar, size);
    siguiente_libre_memoria_direccion += size;
    return liberar_espacio;
}

SIN_USO uintptr_t funcion_802A8348(s32 parametro0, s32 parametro1, s32 parametro2) {
    uintptr_t desplazamiento;
    SIN_USO void* relleno;
    uintptr_t direccion_viejo;
    void* direccion_nuevo;

    desplazamiento = ALIGN16(parametro1 * parametro2);
    direccion_viejo = siguiente_libre_memoria_direccion;
    direccion_nuevo = (void*) (direccion_viejo + desplazamiento);
    relleno = &direccion_nuevo;
    osInvalDCache(direccion_nuevo, desplazamiento);
    osPiStartDma(&msj_io_dma, 0, 0, (uintptr_t) &_other_texturesSegmentRomStart[SEGMENT_OFFSET(parametro0)], direccion_nuevo, desplazamiento,
                 &cola_msj_dma);
    osRecvMesg(&cola_msj_dma, &msj_recibido_principal, 1);

    funcion_80040030((u8*) direccion_nuevo, (u8*) direccion_viejo);
    siguiente_libre_memoria_direccion += desplazamiento;
    return direccion_viejo;
}

SIN_USO u8* funcion_802A841C(u8* parametro0, s32 parametro1, s32 parametro2) {
    u8* temporal_v0;
    void* temporal_a0;
    temporal_v0 = (u8*) siguiente_libre_memoria_direccion;
    temporal_a0 = temporal_v0 + parametro2;
    parametro1 = ALIGN16(parametro1);
    parametro2 = ALIGN16(parametro2);

    osInvalDCache(temporal_a0, parametro1);
    osPiStartDma(&msj_io_dma, 0, 0, (uintptr_t) &_other_texturesSegmentRomStart[SEGMENT_OFFSET(parametro0)], temporal_a0, parametro1,
                 &cola_msj_dma);
    osRecvMesg(&cola_msj_dma, &msj_recibido_principal, 1);
    funcion_80040030((u8*) temporal_a0, temporal_v0);
    siguiente_libre_memoria_direccion += parametro2;
    return temporal_v0;
}

u8* texturas_dma(u8 textura[], size_t parametro1, size_t parametro2) {
    u8* temporal_v0;
    void* temporal_a0;

    temporal_v0 = (u8*) siguiente_libre_memoria_direccion;
    temporal_a0 = temporal_v0 + parametro2;
    parametro1 = ALIGN16(parametro1);
    parametro2 = ALIGN16(parametro2);
    osInvalDCache((void*) temporal_a0, parametro1);
    osPiStartDma(&msj_io_dma, 0, 0, (uintptr_t) &_other_texturesSegmentRomStart[SEGMENT_OFFSET(textura)],
                 (void*) temporal_a0, parametro1, &cola_msj_dma);
    osRecvMesg(&cola_msj_dma, &msj_recibido_principal, (int) 1);
    mio0decode((u8*) temporal_a0, temporal_v0);
#ifdef TARGET_PS2
    ps2_tmem_estatico_bloque(temporal_v0, parametro2, 0);
#endif
    siguiente_libre_memoria_direccion += parametro2;
    return temporal_v0;
}

uintptr_t MIO0_0F(u8* parametro0, uintptr_t parametro1, uintptr_t parametro2) {
    uintptr_t viejo_monton_fin_ptr;
    void* temporal_v0;

    parametro1 = ALIGN16(parametro1);
    parametro2 = ALIGN16(parametro2);
    viejo_monton_fin_ptr = ptr_fin_monton;
    temporal_v0 = (void*) siguiente_libre_memoria_direccion;

    osInvalDCache(temporal_v0, parametro1);
    osPiStartDma(&msj_io_dma, 0, 0, (uintptr_t) &_other_texturesSegmentRomStart[SEGMENT_OFFSET(parametro0)], temporal_v0, parametro1,
                 &cola_msj_dma);
    osRecvMesg(&cola_msj_dma, &msj_recibido_principal, 1);
    mio0decode((u8*) temporal_v0, (u8*) viejo_monton_fin_ptr);
    ptr_fin_monton += parametro2;
    return viejo_monton_fin_ptr;
}

void funcion_802A86A8(VtxCircuito* datos, u32 parametro1) {
    VtxCircuito* vtx_circuito = datos;
    Vtx* vtx;
    s32 tmp = ALIGN16(parametro1 * 0x10);
#ifdef AVOID_UB
    u32 i;
#else
    s32 i;
#endif
    s8 temporal_a0;
    s8 temporal_a3;
    s8 banderas;

    ptr_fin_monton -= tmp;
    vtx = (Vtx*) ptr_fin_monton;

    for (i = 0; i < parametro1; i++) {
        if (es_modo_espejo) {
            vtx->v.ob[0] = -vtx_circuito->ob[0];
        } else {
            vtx->v.ob[0] = vtx_circuito->ob[0];
        }

        vtx->v.ob[1] = (vtx_circuito->ob[1] * vtx_estirar_y);
        temporal_a0 = vtx_circuito->ca[0];
        temporal_a3 = vtx_circuito->ca[1];

        banderas = temporal_a0 & 3;
        banderas |= (temporal_a3 << 2) & 0xC;

        vtx->v.ob[2] = vtx_circuito->ob[2];
        vtx->v.tc[0] = vtx_circuito->tc[0];
        vtx->v.tc[1] = vtx_circuito->tc[1];
        vtx->v.cn[0] = (temporal_a0 & 0xFC);
        vtx->v.cn[1] = (temporal_a3 & 0xFC);
        vtx->v.cn[2] = vtx_circuito->ca[2];
        vtx->v.flag = banderas;
        vtx->v.cn[3] = 0xFF;
        vtx++;
        vtx_circuito++;
    }
}

void descomprimir_vtx(VtxCircuito* parametro0, u32 cantidad_vertice) {
    s32 size = ALIGN16(cantidad_vertice * 0x18);
    u32 segmento = SEGMENT_NUMBER2(parametro0);
    u32 desplazamiento = SEGMENT_OFFSET(parametro0);
    void* liberar_espacio;
    u8* vtx_comprimido = VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    SIN_USO s32 relleno;

    liberar_espacio = (void*) siguiente_libre_memoria_direccion;
    siguiente_libre_memoria_direccion += size;

    mio0decode(vtx_comprimido, (u8*) liberar_espacio);
    funcion_802A86A8((VtxCircuito*) liberar_espacio, cantidad_vertice);
    fijar_direccion_base_segmento(4, (void*) ptr_fin_monton);
}

SIN_USO void funcion_802A8844(void) {
}

void desempaquetar_luces(Gfx* parametro0, SIN_USO u8* parametro1, s8 parametro2) {
    SIN_USO s32 relleno;
    s32 a = (parametro2 * 0x18) + 0x9000008;
    s32 b = (parametro2 * 0x18) + 0x9000000;
    Gfx macro[] = { gsSPNumLights(NUMLIGHTS_1) };

    parametro0[gfx_posicion_buscar].words.w0 = macro->words.w0;
    parametro0[gfx_posicion_buscar].words.w1 = macro->words.w1;

    gfx_posicion_buscar++;
    parametro0[gfx_posicion_buscar].words.w0 = 0x3860010;

    parametro0[gfx_posicion_buscar].words.w1 = a;

    gfx_posicion_buscar++;
    parametro0[gfx_posicion_buscar].words.w0 = 0x3880010;
    parametro0[gfx_posicion_buscar].words.w1 = b;
    gfx_posicion_buscar++;
}

void desempaquetar_displaylist(Gfx* parametro0, u8* parametros, SIN_USO s8 opcode) {
    uintptr_t temporal_v0 = parametros[posicion_buscar_empaquetado++];
    uintptr_t temporal_t7 = ((parametros[posicion_buscar_empaquetado++]) << 8 | temporal_v0) * 8;
    parametro0[gfx_posicion_buscar].words.w0 = 0x06000000;
    parametro0[gfx_posicion_buscar].words.w1 = 0x07000000 + temporal_t7;
    gfx_posicion_buscar++;
}

void desempaquetar_displaylist_fin(Gfx* parametro0, SIN_USO u8* parametro1, SIN_USO s8 parametro2) {
    parametro0[gfx_posicion_buscar].words.w0 = (uintptr_t) (uint8_t) G_ENDDL << 24;
    parametro0[gfx_posicion_buscar].words.w1 = 0;
    gfx_posicion_buscar++;
}

void fijar_modo_geometria_desempaquetar(Gfx* parametro0, SIN_USO u8* parametro1, SIN_USO s8 parametro2) {
    Gfx macro[] = { gsSPSetGeometryMode(G_CULL_BACK) };
    parametro0[gfx_posicion_buscar].words.w0 = macro->words.w0;
    parametro0[gfx_posicion_buscar].words.w1 = macro->words.w1;
    gfx_posicion_buscar++;
}

void borrar_modo_geometria_desempaquetar(Gfx* parametro0, SIN_USO u8* parametro1, SIN_USO s8 parametro2) {
    Gfx macro[] = { gsSPClearGeometryMode(G_CULL_BACK) };
    parametro0[gfx_posicion_buscar].words.w0 = macro->words.w0;
    parametro0[gfx_posicion_buscar].words.w1 = macro->words.w1;
    gfx_posicion_buscar++;
}

void desempaquetar_displaylist_descarte(Gfx* parametro0, SIN_USO u8* parametro1, SIN_USO s8 parametro2) {
    Gfx macro[] = { gsSPCullDisplayList(0, 7) };
    parametro0[gfx_posicion_buscar].words.w0 = macro->words.w0;
    parametro0[gfx_posicion_buscar].words.w1 = macro->words.w1;
    gfx_posicion_buscar++;
}

void desempaquetar_modo1_combinacion(Gfx* parametro0, SIN_USO u8* parametro1, SIN_USO uintptr_t parametro2) {
    Gfx macro[] = { gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA) };
    parametro0[gfx_posicion_buscar].words.w0 = macro->words.w0;
    parametro0[gfx_posicion_buscar].words.w1 = macro->words.w1;
    gfx_posicion_buscar++;
}

void desempaquetar_modo2_combinacion(Gfx* parametro0, SIN_USO u8* parametro1, SIN_USO uintptr_t parametro2) {
    Gfx macro[] = { gsDPSetCombineMode(G_CC_MODULATERGBDECALA, G_CC_MODULATERGBDECALA) };
    parametro0[gfx_posicion_buscar].words.w0 = macro->words.w0;
    parametro0[gfx_posicion_buscar].words.w1 = macro->words.w1;
    gfx_posicion_buscar++;
}

void desempaquetar_sombreado_modo_combinacion(Gfx* parametro0, SIN_USO u8* parametro1, SIN_USO uintptr_t parametro2) {
    Gfx macro[] = { gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE) };
    parametro0[gfx_posicion_buscar].words.w0 = macro->words.w0;
    parametro0[gfx_posicion_buscar].words.w1 = macro->words.w1;
    gfx_posicion_buscar++;
}

void desempaquetar_modo4_combinacion(Gfx* parametro0, SIN_USO u8* parametro1, SIN_USO uintptr_t parametro2) {
    Gfx macro[] = { gsDPSetCombineMode(G_CC_MODULATERGBDECALA, G_CC_MODULATERGBDECALA) };
    parametro0[gfx_posicion_buscar].words.w0 = macro->words.w0;
    parametro0[gfx_posicion_buscar].words.w1 = macro->words.w1;
    gfx_posicion_buscar++;
}

void desempaquetar_modo5_combinacion(Gfx* parametro0, SIN_USO u8* parametro1, SIN_USO uintptr_t parametro2) {
    Gfx macro[] = { gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA) };
    parametro0[gfx_posicion_buscar].words.w0 = macro->words.w0;
    parametro0[gfx_posicion_buscar].words.w1 = macro->words.w1;
    gfx_posicion_buscar++;
}

void renderizar_opaco_modo_desempaquetar(Gfx* parametro0, SIN_USO u8* parametro1, SIN_USO uintptr_t parametro2) {
    Gfx macro[] = { gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2) };
    parametro0[gfx_posicion_buscar].words.w0 = macro->words.w0;
    parametro0[gfx_posicion_buscar].words.w1 = macro->words.w1;
    gfx_posicion_buscar++;
}

void renderizar_borde_tex_modo_desempaquetar(Gfx* parametro0, SIN_USO u8* parametro1, SIN_USO uintptr_t parametro2) {
    Gfx macro[] = { gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2) };
    parametro0[gfx_posicion_buscar].words.w0 = macro->words.w0;
    parametro0[gfx_posicion_buscar].words.w1 = macro->words.w1;
    gfx_posicion_buscar++;
}

void renderizar_translucido_modo_desempaquetar(Gfx* parametro0, SIN_USO u8* parametro1, SIN_USO uintptr_t parametro2) {
    Gfx macro[] = { gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2) };
    parametro0[gfx_posicion_buscar].words.w0 = macro->words.w0;
    parametro0[gfx_posicion_buscar].words.w1 = macro->words.w1;
    gfx_posicion_buscar++;
}

void renderizar_decal_opaco_modo_desempaquetar(Gfx* parametro0, SIN_USO u8* parametro1, SIN_USO uintptr_t parametro2) {
    Gfx macro[] = { gsDPSetRenderMode(G_RM_AA_ZB_OPA_DECAL, G_RM_AA_ZB_OPA_DECAL) };
    parametro0[gfx_posicion_buscar].words.w0 = macro->words.w0;
    parametro0[gfx_posicion_buscar].words.w1 = macro->words.w1;
    gfx_posicion_buscar++;
}

void renderizar_decal_translucido_modo_desempaquetar(Gfx* parametro0, SIN_USO u8* parametro1, SIN_USO uintptr_t parametro2) {
    Gfx macro[] = { gsDPSetRenderMode(G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL) };
    parametro0[gfx_posicion_buscar].words.w0 = macro->words.w0;
    parametro0[gfx_posicion_buscar].words.w1 = macro->words.w1;
    gfx_posicion_buscar++;
}

void desempaquetar_sincronizacion_tile(Gfx* gfx, u8* parametros, s8 opcode) {
    Gfx sincronizacion_tile[] = { gsDPTileSync() };
    uintptr_t temporal_a0;
    uintptr_t lo;
    uintptr_t hi;

    s32 ancho;
    s32 altura;
    s32 fmt;
    s32 siz;
    s32 line;
    s32 tmem;
    s32 cms;
    s32 mascaras;
    s32 cmt;
    s32 maskt;
    s32 lrs;
    s32 lrt;
    SIN_USO s32 relleno[4];

    tmem = 0;
    switch (opcode) {
        case PG_TILECFG_A:
            ancho = 32;
            altura = 32;
            fmt = 0;
            break;
        case PG_TILECFG_G:
            ancho = 32;
            altura = 32;
            fmt = 0;
            tmem = 256;
            break;
        case PG_TILECFG_B:
            ancho = 64;
            altura = 32;
            fmt = 0;
            break;
        case PG_TILECFG_C:
            ancho = 32;
            altura = 64;
            fmt = 0;
            break;
        case PG_TILECFG_D:
            ancho = 32;
            altura = 32;
            fmt = 3;
            break;
        case PG_TILECFG_E:
            ancho = 64;
            altura = 32;
            fmt = 3;
            break;
        case PG_TILECFG_F:
            ancho = 32;
            altura = 64;
            fmt = 3;
            break;
    }

    siz = G_IM_SIZ_16b_BYTES;
    line = ((((ancho * 2) + 7) >> 3));

    temporal_a0 = parametros[posicion_buscar_empaquetado++];
    cms = temporal_a0 & 0xF;
    mascaras = (temporal_a0 & 0xF0) >> 4;

    temporal_a0 = parametros[posicion_buscar_empaquetado++];
    cmt = temporal_a0 & 0xF;
    maskt = (temporal_a0 & 0xF0) >> 4;

    gfx[gfx_posicion_buscar].words.w0 = sincronizacion_tile->words.w0;
    gfx[gfx_posicion_buscar].words.w1 = sincronizacion_tile->words.w1;
    gfx_posicion_buscar++;

    lo = ((uintptr_t) (uint8_t) G_SETTILE << 24) | (fmt << 21) | (siz << 19) | (line << 9) | tmem;
    hi = ((cmt) << 18) | ((maskt) << 14) | ((cms) << 8) | ((mascaras) << 4);

    gfx[gfx_posicion_buscar].words.w0 = lo;
    gfx[gfx_posicion_buscar].words.w1 = hi;
    gfx_posicion_buscar++;

    lrs = (ancho - 1) << 2;
    lrt = (altura - 1) << 2;

    lo = ((uintptr_t) (uint8_t) G_SETTILESIZE << 24);
    hi = (lrs << 12) | lrt;

    gfx[gfx_posicion_buscar].words.w0 = lo;
    gfx[gfx_posicion_buscar].words.w1 = hi;
    gfx_posicion_buscar++;
}

void cargar_sincronizacion_tile_desempaquetar(Gfx* gfx, u8* parametros, s8 opcode) {
    SIN_USO uintptr_t variable_;
    Gfx sincronizacion_tile[] = { gsDPTileSync() };
    Gfx cargar_sincronizacion[] = { gsDPLoadSync() };

    uintptr_t parametro;
    uintptr_t lo;
    uintptr_t hi;
    uintptr_t direccion;
    uintptr_t ancho;
    uintptr_t altura;
    uintptr_t fmt;
    uintptr_t siz;
    uintptr_t tmem;
    uintptr_t tile;

    switch (opcode) {
        case CARGAR_BLOQUE_TIMG_PG_0:
            ancho = 32;
            altura = 32;
            fmt = 0;
            break;
        case CARGAR_BLOQUE_TIMG_PG_1:
            ancho = 64;
            altura = 32;
            fmt = 0;
            break;
        case CARGAR_BLOQUE_TIMG_PG_2:
            ancho = 32;
            altura = 64;
            fmt = 0;
            break;
        case CARGAR_BLOQUE_TIMG_PG_3:
            ancho = 32;
            altura = 32;
            fmt = 3;
            break;
        case CARGAR_BLOQUE_TIMG_PG_4:
            ancho = 64;
            altura = 32;
            fmt = 3;
            break;
        case CARGAR_BLOQUE_TIMG_PG_5:
            ancho = 32;
            altura = 64;
            fmt = 3;
            break;
    }

    variable_ = parametros[posicion_buscar_empaquetado];
    direccion = SEGMENT_ADDR(0x05, parametros[posicion_buscar_empaquetado++] << 11);
    posicion_buscar_empaquetado++;
    parametro = parametros[posicion_buscar_empaquetado++];
    siz = G_IM_SIZ_16b;
    tmem = (parametro & 0xF);
    tile = (parametro & 0xF0) >> 4;

    lo = ((uintptr_t) (uint8_t) G_SETTIMG << 24) | (fmt << 21) | (siz << 19);
    gfx[gfx_posicion_buscar].words.w0 = lo;
    gfx[gfx_posicion_buscar].words.w1 = direccion;
    gfx_posicion_buscar++;

    gfx[gfx_posicion_buscar].words.w0 = sincronizacion_tile->words.w0;
    gfx[gfx_posicion_buscar].words.w1 = sincronizacion_tile->words.w1;
    gfx_posicion_buscar++;

    lo = ((uintptr_t) (uint8_t) G_SETTILE << 24) | (fmt << 21) | (siz << 19) | tmem;
    hi = tile << 24;

    gfx[gfx_posicion_buscar].words.w0 = lo;
    gfx[gfx_posicion_buscar].words.w1 = hi;
    gfx_posicion_buscar++;

    gfx[gfx_posicion_buscar].words.w0 = cargar_sincronizacion->words.w0;
    gfx[gfx_posicion_buscar].words.w1 = cargar_sincronizacion->words.w1;
    gfx_posicion_buscar++;

    lo = (uintptr_t) (uint8_t) G_LOADBLOCK << 24;
    hi = (tile << 24) | (MIN((ancho * altura) - 1, 0x7FF) << 12) | CALC_DXT(ancho, G_IM_SIZ_16b_BYTES);

    gfx[gfx_posicion_buscar].words.w0 = lo;
    gfx[gfx_posicion_buscar].words.w1 = hi;
    gfx_posicion_buscar++;
}

void desempaquetar_textura_en(Gfx* parametro0, SIN_USO u8* parametros, SIN_USO s8 parametro2) {
    Gfx macro[] = { gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON) };

    parametro0[gfx_posicion_buscar].words.w0 = macro->words.w0;
    parametro0[gfx_posicion_buscar].words.w1 = macro->words.w1;
    gfx_posicion_buscar++;
}

void desempaquetar_apagado_textura(Gfx* parametro0, SIN_USO u8* parametros, SIN_USO s8 parametro2) {
    Gfx macro[] = { gsSPTexture(0x1, 0x1, 0, G_TX_RENDERTILE, G_OFF) };

    parametro0[gfx_posicion_buscar].words.w0 = macro->words.w0;
    parametro0[gfx_posicion_buscar].words.w1 = macro->words.w1;
    gfx_posicion_buscar++;
}

void desempaquetar_vtx1(Gfx* gfx, u8* parametros, SIN_USO s8 parametro2) {
    uintptr_t temporal_t7;
    uintptr_t temporal_t7_2;

    uintptr_t temporal_ = parametros[posicion_buscar_empaquetado++];
    uintptr_t temporal2 = ((parametros[posicion_buscar_empaquetado++] << 8) | temporal_) * 0x10;

    temporal_ = parametros[posicion_buscar_empaquetado++];
    temporal_t7 = temporal_ & 0x3F;
    temporal_ = parametros[posicion_buscar_empaquetado++];
    temporal_t7_2 = temporal_ & 0x3F;

    gfx[gfx_posicion_buscar].words.w0 =
        ((uintptr_t) (uint8_t) G_VTX << 24) | (temporal_t7_2 * 2 << 16) | (((temporal_t7 << 10) + ((0x10 * temporal_t7) - 1)));
    gfx[gfx_posicion_buscar].words.w1 = 0x04000000 + temporal2;
    gfx_posicion_buscar++;
}

void desempaquetar_vtx2(Gfx* gfx, u8* parametros, s8 parametro2) {
    uintptr_t temporal_t9;
    uintptr_t temporal_v1;
    uintptr_t temporal_v2;

    temporal_v1 = parametros[posicion_buscar_empaquetado++];
    temporal_v2 = ((parametros[posicion_buscar_empaquetado++] << 8) | temporal_v1) * 0x10;

    temporal_t9 = parametro2 - PG_VTX_BASE;

    gfx[gfx_posicion_buscar].words.w0 = ((uintptr_t) (uint8_t) G_VTX << 24) | ((temporal_t9 << 10) + (((temporal_t9) * 0x10) - 1));
    gfx[gfx_posicion_buscar].words.w1 = 0x4000000 + temporal_v2;
    gfx_posicion_buscar++;
}

void desempaquetar_triangulo(Gfx* gfx, u8* parametros, SIN_USO s8 parametro2) {
    uintptr_t temporal_v0;
    uintptr_t phi_a0;
    uintptr_t phi_a2;
    uintptr_t phi_a3;

    temporal_v0 = parametros[posicion_buscar_empaquetado++];

    if (es_modo_espejo) {
        phi_a3 = temporal_v0 & 0x1F;
        phi_a2 = (temporal_v0 >> 5) & 7;
        temporal_v0 = parametros[posicion_buscar_empaquetado++];
        phi_a2 |= (temporal_v0 & 3) * 8;
        phi_a0 = (temporal_v0 >> 2) & 0x1F;
    } else {
        phi_a0 = temporal_v0 & 0x1F;
        phi_a2 = (temporal_v0 >> 5) & 7;
        temporal_v0 = parametros[posicion_buscar_empaquetado++];
        phi_a2 |= (temporal_v0 & 3) * 8;
        phi_a3 = (temporal_v0 >> 2) & 0x1F;
    }
    gfx[gfx_posicion_buscar].words.w0 = ((uintptr_t) (uint8_t) G_TRI1 << 24);
    gfx[gfx_posicion_buscar].words.w1 = ((phi_a0 * 2) << 16) | ((phi_a2 * 2) << 8) | (phi_a3 * 2);
    gfx_posicion_buscar++;
}

void desempaquetar_cuadrangulo(Gfx* gfx, u8* parametros, SIN_USO s8 parametro2) {
    uintptr_t temporal_v0;
    uintptr_t phi_t0;
    uintptr_t phi_a3;
    uintptr_t phi_a0;
    uintptr_t phi_t2;
    uintptr_t phi_t1;
    uintptr_t phi_a2;

    temporal_v0 = parametros[posicion_buscar_empaquetado++];

    if (es_modo_espejo) {
        phi_t0 = temporal_v0 & 0x1F;
        phi_a3 = (temporal_v0 >> 5) & 7;
        temporal_v0 = parametros[posicion_buscar_empaquetado++];
        phi_a3 |= (temporal_v0 & 3) * 8;
        phi_a0 = (temporal_v0 >> 2) & 0x1F;
    } else {
        phi_a0 = temporal_v0 & 0x1F;
        phi_a3 = (temporal_v0 >> 5) & 7;
        temporal_v0 = parametros[posicion_buscar_empaquetado++];
        phi_a3 |= (temporal_v0 & 3) * 8;
        phi_t0 = (temporal_v0 >> 2) & 0x1F;
    }

    temporal_v0 = parametros[posicion_buscar_empaquetado++];

    if (es_modo_espejo) {
        phi_a2 = temporal_v0 & 0x1F;
        phi_t1 = (temporal_v0 >> 5) & 7;
        temporal_v0 = parametros[posicion_buscar_empaquetado++];
        phi_t1 |= (temporal_v0 & 3) * 8;
        phi_t2 = (temporal_v0 >> 2) & 0x1F;
    } else {
        phi_t2 = temporal_v0 & 0x1F;
        phi_t1 = (temporal_v0 >> 5) & 7;
        temporal_v0 = parametros[posicion_buscar_empaquetado++];
        phi_t1 |= (temporal_v0 & 3) * 8;
        phi_a2 = (temporal_v0 >> 2) & 0x1F;
    }
    gfx[gfx_posicion_buscar].words.w0 =
        ((uintptr_t) (uint8_t) G_TRI2 << 24) | ((phi_a0 * 2) << 16) | ((phi_a3 * 2) << 8) | (phi_t0 * 2);
    gfx[gfx_posicion_buscar].words.w1 = ((phi_t2 * 2) << 16) | ((phi_t1 * 2) << 8) | (phi_a2 * 2);
    gfx_posicion_buscar++;
}
