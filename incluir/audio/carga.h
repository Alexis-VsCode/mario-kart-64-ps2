#ifndef AUDIO_CARGA_H
#define AUDIO_CARGA_H

#include <PR/ultratypes.h>
#include "audio/interno.h"

#define AUDIO_FRAME_DMA_COLA_TAMANIO 0x40

#define BANCOS_PRECARGAR 2
#define SECUENCIA_PRECARGAR 1

#define ES_SECUENCIA_CANAL_VALIDO(ptr) ((uintptr_t) (ptr) != (uintptr_t) &ninguno_canal_secuencia)

struct DmaCompartido {
     u8* buffer;
     uintptr_t source;
     u16 tamanio_sin_uso;
     u16 tamanio_buf;
     u8 unused2;
     u8 indice_reutilizar;
     u8 ttl;
};

void copiar_inmediato_dma_audio(u8* direccion_dev, void* direccion_v, size_t nbytes);
void copiar_asincrono_dma_audio(uintptr_t, void*, size_t, OSMesgQueue*, OSIoMesg*);
void copiar_asincrono_parcial_dma_audio(uintptr_t*, u8**, ssize_t*, OSMesgQueue*, OSIoMesg*);
void disminuir_ttls_dma_muestra(void);
void* datos_muestra_dma(uintptr_t, u32, s32, u8*);
void funcion_800BB030(s32);
s32 funcion_800BB304(struct MuestraBancoAudio*);
s32 funcion_800BB388(s32 id_banco, s32 inst_id, s32 parametro2);
void funcion_800BB43C(ALSeqFile*, u8*);
void parchear_sonido(struct SonidoBancoAudio* sonido, u8* mem_base, u8* base_desplazamiento);
void funcion_800BB584(s32);
void parchear_banco_audio(struct BancoAudio* mem, u8* desplazamiento, u32 instrumentos_num, u32 tambores_num);
struct BancoAudio* cargar_inmediato_banco(s32, s32);
struct BancoAudio* cargar_asincrono_banco(s32, s32, struct JugadorSecuencia*);
void* inmediato_dma_secuencia(s32, s32);
void* asincrono_dma_secuencia(s32, s32, struct JugadorSecuencia*);
u8 obtener_banco_faltante(u32 sec_id, s32* no_cantidad_nulo, s32* cantidad_nulo);
struct BancoAudio* cargar_inmediato_bancos(s32, u8*);
void precargar_secuencia(u32, u8);
void cargar_secuencia(u32, u32, s32);
void cargar_interno_secuencia(u32, u32, s32);

extern struct JugadorSecuencia jugadores_secuencia[JUGADORES_SECUENCIA];
extern struct CanalSecuencia canales_secuencia[CANALES_SECUENCIA];
extern struct CapaCanalSecuencia capas_secuencia[CAPAS_SECUENCIA];
extern struct CanalSecuencia ninguno_canal_secuencia;
extern struct ItemListaAudio lista_libre_capa;
extern struct PoolNota listas_libre_nota;
extern OSMesgQueue act_audio_frame_dma_cola;
extern OSMesg act_audio_frame_dma_msj_bufs[AUDIO_FRAME_DMA_COLA_TAMANIO];
extern OSIoMesg act_audio_frame_dma_io_msj_bufs[AUDIO_FRAME_DMA_COLA_TAMANIO];
extern OSMesgQueue dato_803B6720;
extern OSMesg dato_803B6738;

extern OSIoMesg dato_803B6740;
extern struct DmaCompartido dmas_muestra[0x70];
extern u32 muestra_dma_num_lista_items;
extern u32 muestra_dma_lista_tamanio_1;
extern s32 dato_803B6E60;
extern s32 cargar_relleno_bss;

extern u8 muestra_dma_reutilizar_cola_1[256];
extern u8 muestra_dma_reutilizar_cola_2[256];
extern u8 muestra_dma_reutilizar_cola_cola_1;
extern u8 muestra_dma_reutilizar_cola_cola_2;
extern u8 muestra_dma_reutilizar_cola_cabeza_1;
extern u8 muestra_dma_reutilizar_cola_cabeza_2;

extern ALSeqFile* sec_cabecera_archivo;
extern ALSeqFile* cabecera_ctl_al;
extern ALSeqFile* tabla_al;
extern u8* conjuntos_banco_al;
extern u16 cantidad_secuencia;
extern struct EntradaCtl* entradas_ctl;
extern struct AudioBufferParametrosEU parametros_buffer_audio;
extern u32 dato_803B70A8;
extern s32 ordenes_audio_max;
extern s32 notas_simultaneo_max;
extern s16 interno_tempo_a_externo;
extern s8 audio_bib_sonido_modo;
extern volatile s32 cantidad_frame_audio;
extern s32 act_audio_frame_dma_cantidad;

#endif
