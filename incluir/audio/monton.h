#ifndef MONTON_H_AUDIO
#define MONTON_H_AUDIO

#include <PR/ultratypes.h>

#include "interno.h"

#define SONIDO_SITUACION_CARGA_NO_CARGADO 0
#define SONIDO_SITUACION_CARGA_EN_PROGRESO 1
#define SONIDO_COMPLETO_SITUACION_CARGA 2
#define SONIDO_DESCARTABLE_SITUACION_CARGA 3
#define SONIDO_SITUACION_CARGA_4 4
#define SONIDO_SITUACION_CARGA_5 5

#define ES_BANCO_CARGA_COMPLETO(id_banco) (situacion_carga_banco[id_banco] >= SONIDO_COMPLETO_SITUACION_CARGA)
#define ES_SEC_CARGA_COMPLETO(sec_id) (sec_situacion_carga[sec_id] >= SONIDO_COMPLETO_SITUACION_CARGA)

struct SonidoPoolReserva {
    u8* start;
    u8* act;
    u32 size;
    s32 entradas_reservado_num;
};

struct SecOEntradaBanco {
    u8* ptr;
    u32 size;
    s16 indice_pool;
    s16 id;
};

struct PoolPersistente {
     u32 entradas_num;
     struct SonidoPoolReserva pool;
     struct SecOEntradaBanco entradas[32];
};

struct PoolProvisorio {
     u32 lado_siguiente;
     struct SonidoPoolReserva pool;
     struct SecOEntradaBanco entradas[2];
};

struct SonidoMultiPool {
     struct PoolPersistente persistente;
     struct PoolProvisorio provisorio;
     u32 pad2[4];
};

struct PoolDesconocido1 {
    struct SonidoPoolReserva pool;
    struct SecOEntradaBanco entradas[32];
};

struct EntradaDesconocido {
    s8 used;
    s8 medio;
    s8 id_banco;
    u32 pad;
    u8* direccion_orig;
    u8* direccion_dst;
    u32 size;
};

struct PoolDesconocido {
     struct SonidoPoolReserva pool;
     struct EntradaDesconocido entradas[64];
     s32 entradas_num;
     u32 desconocido514;
};

struct DividirPool {
    u32 sec_querer;
    u32 banco_querer;
    u32 querer_sin_uso;
    u32 personalizado_querer;
};

struct DividirPool2 {
    u32 persistente_querer;
    u32 provisorio_querer;
};

void cargar_situacion_banco_reinicio_y_sec(void);
void descartar_banco(s32 id_banco);
void descartar_secuencia(s32 sec_id);
void* sonido_reserva(struct SonidoPoolReserva* pool, u32 size);
void sonido_inicializacion_pool_reserva(struct SonidoPoolReserva* pool, void* direccion_mem, u32 size);
void borrar_pool_persistente(struct PoolPersistente* persistente);
void borrar_pool_provisorio(struct PoolProvisorio* provisorio);
void funcion_800B90E0(struct SonidoPoolReserva* pool);
void sonido_pools_principal_inicializacion(s32);
void funcion_800B914C(struct DividirPool*);
void sec_y_inicializacion_pool_banco(struct DividirPool2* a);
void inicializar_pools_persistente(struct DividirPool* a);
void inicializar_pools_provisorio(struct DividirPool* a);
void* reservar_banco_o_sec(struct SonidoMultiPool*, s32, s32, s32, s32);
void* obtener_banco_o_sec(s32 pool_idx, s32 parametro1, s32 id);
void* obtener_banco_o_interior_sec(s32 pool_idx, s32 parametro1, s32 id_banco);
void funcion_800B9BE4(f32, f32, u16*);
void disminuir_ganancia_reverb(void);
s32 reiniciar_paso_abajo_cerrar_audio_y(void);
void reiniciar_sesion_audio(void);
void* busqueda_pool1_desconocido(s32 pool_idx, s32 id);
void funcion_800BA8B0(s32, s32);

extern s32 dato_800EA5D0;

extern s32 ordenes_audio_max;
extern s16 interno_tempo_a_externo;
extern f32 dato_803B7178;
extern s32 tasa_refrescar;
extern u32 muestra_dma_num_lista_items;
extern struct AudioSesionAjustesEU ajustes_sesion_audio[];

extern s16 g_volumen;
extern s8 reverb_usar;
extern s8 reverbs_sintesis_num;
extern struct EuSubNota* eu_subs_nota;
extern struct SonidoPoolReserva pool_sesion_audio;
extern struct SonidoPoolReserva pool_inicializacion_audio;
extern struct SonidoPoolReserva notas_y_pool_buffers;
extern struct SonidoPoolReserva pool_comun_persistente;
extern struct SonidoPoolReserva pool_comun_provisorio;
extern struct SonidoMultiPool sec_pool_cargado;
extern struct SonidoMultiPool pool_cargado_banco;
extern struct SonidoMultiPool pool_cargado_sin_uso;
extern struct PoolDesconocido1 pool_desconocido_1;
extern struct DividirPool dividir_pool_sesion;
extern struct DividirPool2 sec_y_dividir_pool_banco;
extern struct DividirPool persistente_comun_pool_dividir;
extern struct DividirPool provisorio_comun_pool_dividir;
extern struct SonidoMultiPool pool_cargado_sin_uso;
extern struct SonidoPoolReserva sec_y_pool_banco;
extern u8 situacion_carga_banco[64];
extern u8 situacion_carga_desconocido[64];
extern u8 sec_situacion_carga[256];
extern volatile u8 situacion_reinicio_audio;
extern u8 audio_reinicio_ajuste_id_a_carga;
extern s32 audio_reinicio_fundido_salida_frames_izquierda;
extern struct Nota* notas;

#endif
