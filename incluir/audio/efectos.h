#ifndef AUDIO_EFECTOS_H
#define AUDIO_EFECTOS_H

#include "audio/interno.h"

#ifdef TARGET_N64
#define ENDIAN_GRANDE_ES 1
#endif

#define ADSR_ESTADO_DESACTIVADO 0
#define INICIAL_ESTADO_ADSR 1
#define ADSR_ESTADO_INICIO_BUCLE 2
#define BUCLE_ESTADO_ADSR 3
#define FUNDIDO_ESTADO_ADSR 4
#define CUELGUE_ESTADO_ADSR 5
#define DECAER_ESTADO_ADSR 6
#define SUELTA_ESTADO_ADSR 7
#define SOSTENIDO_ESTADO_ADSR 8

#define SUELTA_ACCION_ADSR 0x10
#define DECAER_ACCION_ADSR 0x20
#define CUELGUE_ACCION_ADSR 0x40

#define DESACTIVAR_ADSR 0
#define CUELGUE_ADSR -1
#define ADSR_GOTO -2
#define REINICIO_ADSR -3

#if ENDIAN_GRANDE_ES
#define BSWAP16(x) (x)
#else
#define BSWAP16(x) (((x) & 0xff) << 8 | (((x) >> 8) & 0xff))
#endif

void procesar_sonido_canal_secuencia(struct CanalSecuencia* sec_canal, s32 recalcular_volumen);
void procesar_sonido_jugador_secuencia(struct JugadorSecuencia* sec_jugador);
f32 escalar_frec_portamento_obtener(struct Portamento* p);
s16 obtener_cambio_tono_vibrato(struct EstadoVibrato* vib);
f32 escalar_frec_vibrato_obtener(struct EstadoVibrato* vib);
void actualizar_vibrato_nota(struct Nota* nota);
void inicializar_vibrato_nota(struct Nota* nota);
void inicializar_adsr(struct EstadoAdsr* adsr, struct EnvolventeAdsr* envolvente, s16* salida_vol);
f32 actualizar_adsr(struct EstadoAdsr* adsr);

#endif
