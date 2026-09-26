#ifndef AUDIO_PUERTO_EU_H
#define AUDIO_PUERTO_EU_H

#include "audio/interno.h"

#define MUESTRAS_A_SOBREPRODUCCION 0x10
#define EXTRA_EN_BUFFER_AI_MUESTRAS_OBJETIVO 0x40

void procesar_cmd_audio_eu(struct EuAudioCmd*);
void sec_fundido_jugador_a_volumen_cero(s32 parametro0, s32 fundir_tiempo_salida);
void funcion_800CBA64(s32 indice_jugador, s32 fundir_en_tiempo);
void inicializar_colas_eu_puerto(void);
void funcion_800CBB48(s32, s32*);
void funcion_800CBB88(u32, f32);
void funcion_800CBBB8(u32, u32);
void funcion_800CBBE8(u32, s8);
void funcion_800CBC24(void);
void funcion_800CBCB0(u32 parametro0);
void inicializar_eu_puerto(void);

extern OSMesgQueue dato_801937C0;
extern OSMesgQueue dato_801937D8;
extern OSMesgQueue dato_801937F0;
extern OSMesgQueue dato_80193808;

extern struct EuAudioCmd s_audio_cmd[0x100];

extern OSMesg dato_80194020[];
extern OSMesg dato_80194028[];
extern OSMesg dato_80194038[];
extern OSMesg dato_8019403C[];

extern OSMesgQueue* dato_800EA3A8;
extern OSMesgQueue* dato_800EA3AC;
extern OSMesgQueue* dato_800EA3B0;
extern OSMesgQueue* dato_800EA3B4;
extern s32 dato_800EA484;
extern s32 dato_800EA4A4;

#endif
