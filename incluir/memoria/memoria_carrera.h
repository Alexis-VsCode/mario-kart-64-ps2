#ifndef MEMORIA_MEMORIA_CARRERA_H
#define MEMORIA_MEMORIA_CARRERA_H

struct BloquePoolPrincipal {
    struct BloquePoolPrincipal* prev;
    struct BloquePoolPrincipal* next;
};

struct EstadoPoolPrincipal {
    uintptr_t freeSpace;
    struct BloquePoolPrincipal* cabeza_l_lista;
    struct BloquePoolPrincipal* cabeza_r_lista;
    struct EstadoPoolPrincipal* prev;
};

struct StructDesconocido802AF7B4 {
    s32 desconocido0;
    s32 desconocido4;
};

struct desconocido_struct_802B8CD4 {
    s16 desconocido0;
    s16 desconocido2;
    s32 desconocido4;
    s32 desconocido8;
    s32 fill;
};

struct PoolSoloReserva {
    s32 espacio_total;
    s32 espacio_usado;
    u8* ptr_inicio;
    u8* ptr_libre;
};

#define IZQUIERDA_POOL_MEMORIA 0
#define DERECHA_POOL_MEMORIA 1

#define ALIGN4(val) (((val) + 0x3) & ~0x3)

extern f32 vtx_estirar_y;

void* obtener_siguiente_disponible_memoria_direccion(uintptr_t);
uintptr_t fijar_direccion_base_segmento(s32, void*);
void* obtener_direccion_base_segmento(s32);
void* segmentado_a_virtual(const void*);
void mover_tabla_segmento_a_dmem(void);
void inicializar_pool_memoria(uintptr_t, uintptr_t);
void* descomprimir_segmentos(u8*, u8*);
void* reservar_memoria(size_t);
void* cargar_datos(uintptr_t, uintptr_t);
void funcion_802A7D54(s32, s32);

void inicializar_pool_principal(uintptr_t, uintptr_t);
void* reservar_pool_principal(uintptr_t, uintptr_t);
uintptr_t liberar_pool_principal(void*);
void* rehacer_reserva_pool_principal(void*, uintptr_t);
uintptr_t disponible_pool_principal(void);
uintptr_t empujar_estado_pool_principal(void);
uintptr_t sacar_estado_pool_principal(void);
void* funcion_802A80B0(u8*, u8*, u8*);
void funcion_802A81EC(void);
struct PoolSoloReserva* inicializar_pool_solo_reserva(uintptr_t, uintptr_t);
uintptr_t funcion_802A82AC(s32);
uintptr_t funcion_802A8348(s32, s32, s32);
u8* texturas_dma(u8*, u32, u32);
uintptr_t MIO0_0F(u8*, uintptr_t, uintptr_t);
void funcion_802A8844(void);
void desempaquetar_luces(Gfx*, u8*, s8);
void desempaquetar_displaylist(Gfx*, u8*, s8);
void desempaquetar_displaylist_fin(Gfx*, u8*, s8);
void fijar_modo_geometria_desempaquetar(Gfx*, u8*, s8);
void borrar_modo_geometria_desempaquetar(Gfx*, u8*, s8);
void desempaquetar_displaylist_descarte(Gfx*, u8*, s8);
void desempaquetar_modo1_combinacion(Gfx*, u8*, uintptr_t);
void desempaquetar_modo2_combinacion(Gfx*, u8*, uintptr_t);
void desempaquetar_sombreado_modo_combinacion(Gfx*, u8*, uintptr_t);
void desempaquetar_modo4_combinacion(Gfx*, u8*, uintptr_t);
void desempaquetar_modo5_combinacion(Gfx*, u8*, uintptr_t);
void renderizar_opaco_modo_desempaquetar(Gfx*, u8*, uintptr_t);
void renderizar_borde_tex_modo_desempaquetar(Gfx*, u8*, uintptr_t);
void renderizar_translucido_modo_desempaquetar(Gfx*, u8*, uintptr_t);
void renderizar_decal_opaco_modo_desempaquetar(Gfx*, u8*, uintptr_t);
void renderizar_decal_translucido_modo_desempaquetar(Gfx*, u8*, uintptr_t);
void desempaquetar_sincronizacion_tile(Gfx*, u8*, s8);
void cargar_sincronizacion_tile_desempaquetar(Gfx*, u8*, s8);
void desempaquetar_textura_en(Gfx*, u8*, s8);
void desempaquetar_apagado_textura(Gfx*, u8*, s8);
u8* cargar_circuito(s32);

extern u8 _other_texturesSegmentRomStart[];

#endif
