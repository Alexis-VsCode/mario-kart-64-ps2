#include <ultra64.h>
#include <juego/macros.h>
#include <PR/ucode.h>

#include "audio/sintesis.h"
#include "audio/reproductor_secuencias.h"
#include "audio/puerto_eu.h"
#include "audio/carga.h"
#include "audio/monton.h"
#include "audio/datos.h"

OSMesgQueue dato_801937C0;
OSMesgQueue dato_801937D8;
OSMesgQueue dato_801937F0;
OSMesgQueue dato_80193808;

struct EuAudioCmd s_audio_cmd[0x100];

OSMesg dato_80194020[2];
OSMesg dato_80194028[4];
OSMesg dato_80194038[1];
OSMesg dato_8019403C[1];

u8 dato_800EA3A0[] = { 0, 0, 0, 0 };

u8 dato_800EA3A4[] = { 0, 0, 0, 0 };

OSMesgQueue* dato_800EA3A8 = &dato_801937C0;
OSMesgQueue* dato_800EA3AC = &dato_801937D8;
OSMesgQueue* dato_800EA3B0 = &dato_801937F0;
OSMesgQueue* dato_800EA3B4 = &dato_80193808;

char puerto_eu_sin_uso_cadena0[] = "DAC:Lost 1 Frame.\n";
char puerto_eu_sin_uso_cadena1[] = "DMA: Request queue over.( %d )\n";
char puerto_eu_sin_uso_cadena2[] = "DMA [ %d lines] TIMEOUT\n";
char puerto_eu_sin_uso_cadena3[] = "Warning: WaveDmaQ contains %d msgs.\n";
char puerto_eu_sin_uso_cadena4[] = "Audio:now-max tasklen is %d / %d\n";
char puerto_eu_sin_uso_cadena5[] = "Audio:Warning:ABI Tasklist length over (%d)\n";

s32 dato_800EA484 = 128;

char puerto_eu_sin_uso_cadena6[] = "AudioSend: %d -> %d (%d)\n";

s32 dato_800EA4A4 = 0;

char puerto_eu_sin_uso_cadena7[] = "Undefined Port Command %d\n";

struct TareaSP* crear_siguiente_audio_frame_tarea(void) {
    u32 restante_muestras_en_ai;
    s32 ordenes_escrito;
    s32 index;
    OSTask_t* tarea;
    s32 variable_s0;
    s16* buffer_ai_act;
    s32 cantidad_dma_viejo;
    OSMesg sp58;
    OSMesg sp54;
    s32 copia_ordenes_escrito;

    cantidad_frame_audio++;
    if ((cantidad_frame_audio % parametros_buffer_audio.desconocido_ajuste_4) != 0) {
        return NULL;
    }
    osSendMesg(dato_800EA3A8, (OSMesg) cantidad_frame_audio, OS_MESG_NOBLOCK);

    indice_tarea_audio ^= 1;
    act_ai_buffer_indice++;
    act_ai_buffer_indice %= NUMAIBUFFERS;
    index = (act_ai_buffer_indice + 1) % NUMAIBUFFERS;
    restante_muestras_en_ai = osAiGetLength() / 4;

    if (longitudes_buffer_ai[index] != 0) {
        osAiSetNextBuffer(ai_buffers[index], longitudes_buffer_ai[index] * 4);
    }
    cantidad_dma_viejo = act_audio_frame_dma_cantidad;
    for (variable_s0 = 0; variable_s0 < act_audio_frame_dma_cantidad; variable_s0++) {
        if (osRecvMesg(&act_audio_frame_dma_cola, NULL, 0) == 0) {
            cantidad_dma_viejo -= 1;
        }
    }
    if (cantidad_dma_viejo != 0) {
        for (variable_s0 = 0; variable_s0 < cantidad_dma_viejo; variable_s0++) {
            osRecvMesg(&act_audio_frame_dma_cola, NULL, 1);
        }
    }
    cantidad_dma_viejo = act_audio_frame_dma_cola.validCount;
    if (cantidad_dma_viejo != 0) {
        for (variable_s0 = 0; variable_s0 < cantidad_dma_viejo; variable_s0++) {
            osRecvMesg(&act_audio_frame_dma_cola, NULL, 0);
        }
    }
    act_audio_frame_dma_cantidad = 0;
    disminuir_ttls_dma_muestra();
    if (osRecvMesg(dato_800EA3B0, &sp58, 0) != -1) {
        audio_reinicio_ajuste_id_a_carga = (u8) (u32) sp58;
        situacion_reinicio_audio = 5;
    }
    if (situacion_reinicio_audio != 0) {
        if (reiniciar_paso_abajo_cerrar_audio_y() == 0) {
            if (situacion_reinicio_audio == 0) {
                osSendMesg(dato_800EA3B4, (OSMesg) (u32) audio_reinicio_ajuste_id_a_carga, OS_MESG_NOBLOCK);
            }
            return NULL;
        }
    }

    tarea_audio = &tareas_audio[indice_tarea_audio];
    audio_cmd = audio_cmd_buffers[indice_tarea_audio];
    index = act_ai_buffer_indice;
    buffer_ai_act = ai_buffers[index];
    longitudes_buffer_ai[index] =
        ((parametros_buffer_audio.muestras_por_objetivo_frame - restante_muestras_en_ai + EXTRA_EN_BUFFER_AI_MUESTRAS_OBJETIVO) &
         ~0xF) +
        MUESTRAS_A_SOBREPRODUCCION;
    if (longitudes_buffer_ai[index] < parametros_buffer_audio.min_ai_buffer_longitud) {
        longitudes_buffer_ai[index] = parametros_buffer_audio.min_ai_buffer_longitud;
    }
    if (longitudes_buffer_ai[index] > parametros_buffer_audio.max_ai_buffer_longitud) {
        longitudes_buffer_ai[index] = parametros_buffer_audio.max_ai_buffer_longitud;
    }
    if (osRecvMesg(dato_800EA3AC, &sp54, 0) != -1) {
        funcion_800CBCB0((u32) sp54);
    }
    audio_cmd = ejecutar_sintesis((Acmd*) audio_cmd, &ordenes_escrito, buffer_ai_act, longitudes_buffer_ai[index]);
    aleatorio_audio = osGetCount() * (aleatorio_audio + cantidad_frame_audio);
    aleatorio_audio = aleatorio_audio + ai_buffers[index][cantidad_frame_audio & 0xFF];

    index = indice_tarea_audio;
    tarea_audio->msgqueue = NULL;
    copia_ordenes_escrito += 0;
    tarea_audio->msg = NULL;

    tarea = &tarea_audio->tarea.t;
    tarea->type = M_AUDTASK;
    tarea->flags = 0;
    tarea->ucode_boot = rspF3DBootStart;
    tarea->ucode_boot_size = (u8*) rspF3DBootEnd - (u8*) rspF3DBootStart;
    tarea->ucode = rspAspMainStart;
    tarea->ucode_data = rspAspMainDataStart;
    tarea->ucode_size = 0x1000;
    tarea->ucode_data_size = (rspAspMainDataEnd - rspAspMainDataStart) * sizeof(u64);
    tarea->dram_stack = NULL;
    tarea->dram_stack_size = 0;
    tarea->output_buff = NULL;
    tarea->output_buff_size = NULL;
    tarea->data_ptr = (u64*) audio_cmd_buffers[index];
    tarea->data_size = ordenes_escrito * sizeof(u64);
    tarea->yield_data_ptr = NULL;
    tarea->yield_data_size = 0;
    copia_ordenes_escrito = ordenes_escrito;
    if (dato_800EA484 < ordenes_escrito) {
        dato_800EA484 = copia_ordenes_escrito;
    }
    return tarea_audio;
}

void procesar_cmd_audio_eu(struct EuAudioCmd* cmd) {
    s32 i;

    switch (cmd->u.s.op) {
        case 0x81:
            precargar_secuencia(cmd->u.s.arg2, 3);
            break;

        case 0x82:
        case 0x88:
            cargar_secuencia(cmd->u.s.id_banco, cmd->u.s.arg2, cmd->u.s.parametro3);
            funcion_800CBA64(cmd->u.s.id_banco, cmd->u2.as_s32);
            break;

        case 0x83:
            if (jugadores_secuencia[cmd->u.s.id_banco].activado != false) {
                if (cmd->u2.as_s32 == 0) {
                    desactivar_jugador_secuencia(&jugadores_secuencia[cmd->u.s.id_banco]);
                } else {
                    sec_fundido_jugador_a_volumen_cero(cmd->u.s.id_banco, cmd->u2.as_s32);
                }
            }
            break;

        case 0xf0:
            audio_bib_sonido_modo = cmd->u2.as_s32;
            break;

        case 0xf1:
            for (i = 0; i < 4; i++) {
                jugadores_secuencia[i].silenciado = true;
                jugadores_secuencia[i].volumen_recalcular = true;
            }
            break;

        case 0xf2:
            for (i = 0; i < 4; i++) {
                jugadores_secuencia[i].silenciado = false;
                jugadores_secuencia[i].volumen_recalcular = true;
            }
            break;
        case 0xF3:
            funcion_800BB388(cmd->u.s.id_banco, cmd->u.s.arg2, cmd->u.s.parametro3);
            break;
    }
}

void sec_fundido_jugador_a_volumen_cero(s32 parametro0, s32 fundir_tiempo_salida) {
    struct JugadorSecuencia* jugador;

    if (fundir_tiempo_salida == 0) {
        fundir_tiempo_salida = 1;
    }
    jugador = &jugadores_secuencia[parametro0];
    jugador->state = 2;
    jugador->frames_restante_fundido = fundir_tiempo_salida;
    jugador->velocidad_fundido = -(jugador->volumen_fundido / fundir_tiempo_salida);
}

void funcion_800CBA64(s32 indice_jugador, s32 fundir_en_tiempo) {
    struct JugadorSecuencia* jugador;

    if (fundir_en_tiempo != 0) {
        jugador = &jugadores_secuencia[indice_jugador];
        jugador->state = 1;
        jugador->fundido_temporizador_desconocido_eu = fundir_en_tiempo;
        jugador->frames_restante_fundido = fundir_en_tiempo;
        jugador->volumen_fundido = 0.0f;
        jugador->velocidad_fundido = 0.0f;
    }
}

void inicializar_colas_eu_puerto(void) {
    dato_800EA3A0[0] = 0;
    dato_800EA3A4[0] = 0;
    osCreateMesgQueue(dato_800EA3A8, dato_80194020, 1);
    osCreateMesgQueue(dato_800EA3AC, dato_80194028, 4);
    osCreateMesgQueue(dato_800EA3B0, dato_80194038, 1);
    osCreateMesgQueue(dato_800EA3B4, dato_8019403C, 1);
}

void funcion_800CBB48(s32 parametro0, s32* parametro1) {
    struct EuAudioCmd* cmd = &s_audio_cmd[dato_800EA3A0[0] & 0xff];
    cmd->u.first = parametro0;
    cmd->u2.as_u32 = *parametro1;
    dato_800EA3A0[0]++;
}

void funcion_800CBB88(u32 parametro0, f32 parametro1) {
    funcion_800CBB48(parametro0, (s32*) &parametro1);
}

void funcion_800CBBB8(u32 parametro0, u32 parametro1) {
    funcion_800CBB48(parametro0, (s32*) &parametro1);
}

void funcion_800CBBE8(u32 parametro0, s8 parametro1) {
    s32 sp34 = parametro1 << 24;
    funcion_800CBB48(parametro0, &sp34);
}

void funcion_800CBC24(void) {
    s32 temporal_t6;
    s32 probar;
    OSMesg cosa;
    temporal_t6 = dato_800EA3A0[0] - dato_800EA3A4[0];
    probar = (u8) temporal_t6;
    probar = (probar + 0x100) & 0xFF;
    do {
    } while (0);
    if (dato_800EA4A4 < probar) {
        dato_800EA4A4 = probar;
    }
    cosa = (OSMesg) ((dato_800EA3A0[0] & 0xFF) | ((dato_800EA3A4[0] & 0xFF) << 8));
    osSendMesg(dato_800EA3AC, cosa, 0);
    dato_800EA3A4[0] = dato_800EA3A0[0];
}

void funcion_800CBCB0(u32 parametro0) {
    struct EuAudioCmd* cmd;
    struct JugadorSecuencia* sec_jugador;
    struct CanalSecuencia* chan;
    u8 end = parametro0 & 0xff;
    u8 i = (parametro0 >> 8) & 0xff;

    for (;;) {
        if (i == end) {
            break;
        }
        cmd = &s_audio_cmd[i++ & 0xff];

        if ((cmd->u.s.op & 0xf0) == 0xf0) {
            procesar_cmd_audio_eu(cmd);
            goto por_que;
        }

        if (cmd->u.s.id_banco < JUGADORES_SECUENCIA) {
            sec_jugador = &jugadores_secuencia[cmd->u.s.id_banco];
            if ((cmd->u.s.op & 0x80) != 0) {
                procesar_cmd_audio_eu(cmd);
            } else if ((cmd->u.s.op & 0x40) != 0) {
                switch (cmd->u.s.op) {
                    case 0x41:
                        sec_jugador->escala_volumen_fundido = cmd->u2.as_f32;
                        sec_jugador->volumen_recalcular = true;
                        break;

                    case 0x47:
                        sec_jugador->tempo = cmd->u2.as_s32 * TATUMS_POR_PULSO;
                        break;

                    case 0x48:
                        sec_jugador->trasposicion = cmd->u2.as_s8;
                        break;

                    case 0x46:
                        sec_jugador->sec_eu_variacion[cmd->u.s.parametro3] = cmd->u2.as_s8;
                        break;
                }
            } else if (sec_jugador->activado != false && cmd->u.s.arg2 < 0x10) {
                chan = sec_jugador->channels[cmd->u.s.arg2];
                if (ES_SECUENCIA_CANAL_VALIDO(chan)) {
                    switch (cmd->u.s.op) {
                        case 1:
                            chan->escala_volumen = cmd->u2.as_f32;
                            chan->cambios.como_bitfields.volumen = true;
                            break;
                        case 2:
                            chan->volumen = cmd->u2.as_f32;
                            chan->cambios.como_bitfields.volumen = true;
                            break;
                        case 3:
                            chan->paneo_nuevo = cmd->u2.as_s8;
                            chan->cambios.como_bitfields.paneo = true;
                            break;
                        case 4:
                            chan->escala_frec = cmd->u2.as_f32;
                            chan->cambios.como_bitfields.escala_frec = true;
                            break;
                        case 5:
                            chan->reverb_vol = cmd->u2.as_s8;
                            break;
                        case 6:
                            if (cmd->u.s.parametro3 < 8) {
                                chan->sonido_io_guion[cmd->u.s.parametro3] = cmd->u2.as_s8;
                            }
                            break;
                        case 8:
                            chan->algo_parada_2 = cmd->u2.as_s8;
                    }
                }
            }
        }

    por_que:
        cmd->u.s.op = 0;
    }
}

void inicializar_eu_puerto() {
    inicializar_colas_eu_puerto();
}
