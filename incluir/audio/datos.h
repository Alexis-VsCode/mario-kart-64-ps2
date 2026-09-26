#ifndef AUDIO_DATOS_H
#define AUDIO_DATOS_H

#include "interno.h"

#define AUDIO_BLOQUEO_SIN_INICIALIZAR 0
#define BLOQUEO_AUDIO_NO_CARGANDO 0x76557364
#define CARGANDO_BLOQUEO_AUDIO 0x19710515

#define NUMAIBUFFERS 3
#ifdef VERSION_EU
#define LARGO_AIBUFFER (0xaa * 16)
#else
#define LARGO_AIBUFFER (0xa0 * 16)
#endif

extern s32 act_audio_frame_dma_cantidad;

extern s16 olas_diente_sierra[256];
extern s16 olas_triangulo[256];
extern s16 olas_seno[256];
extern s16 olas_cuadrado[256];
extern s16 ola_desconocido_6[256];
extern s16 ola_desconocido_7[256];
extern s16* muestras_ola[6];
extern u32 rellenar[2];
extern f32 tono_curva_frecuencia_escala[256];
extern f32 frecuencias_nota[128];
extern u8 predeterminado_corto_nota_velocidad_tabla[16];
extern u8 predeterminado_corto_nota_duracion_tabla[16];
extern struct EnvolventeAdsr envolvente_predeterminado[];
extern u32 rellenar2;
extern struct EuSubNota sub_nota_cero;
extern struct EuSubNota sub_nota_predeterminado;
extern u16 cuantizacion_paneo_auriculares[0x10];
extern s16 desconocido_datos_800F6290[];
extern f32 volumen_paneo_auriculares[128];
extern f32 volumen_paneo_estereo[128];
extern f32 volumen_paneo_predeterminado[128];
extern u32 aleatorio_audio;

extern s16 tatums_por_pulso;
extern volatile s32 bloqueo_carga_audio;

extern s32 indice_tarea_audio;
extern s32 act_ai_buffer_indice;
extern Acmd* audio_cmd_buffers[2];
extern Acmd* audio_cmd;
extern struct TareaSP* tarea_audio;
extern struct TareaSP tareas_audio[2];
extern f32 dato_803B7178;
extern s32 tasa_refrescar;
extern s16* ai_buffers[];
extern s16 longitudes_buffer_ai[]; // osAiSetNextBuffer nbytes
extern u16 dato_803B7192;
extern u32 aleatorio_audio;
extern s32 banderas_error_audio;
extern u64 audio_globales_fin_marcador;
extern u8 monton_audio[];

extern struct EUAjustesReverb ajustes_reverb[];
extern struct AudioSesionAjustesEU ajustes_sesion_audio[];
extern s8 cantidad_sin_uso_800EA5C8;
extern s16 tatums_por_pulso;
extern s32 tamanio_monton_audio;
extern s32 audio_inicializacion_pool_tamanio;
extern s32 dato_800EA5D8;
extern volatile s32 bloqueo_carga_audio;

#endif
