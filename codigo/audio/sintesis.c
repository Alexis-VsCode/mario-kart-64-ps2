#include <ultra64.h>
#include <juego/macros.h>
#include "audio/sintesis.h"
#include "audio/monton.h"
#include "audio/datos.h"
#include "audio/carga.h"
#include "audio/reproductor_secuencias.h"
#include "audio/interno.h"
#include "PR/abi.h"

#define a_conjunto_carga_buffer_par(pkt, c, apagado)                                               \
    aSetBuffer(pkt, 0, c + DMEM_DIRECCION_HUMEDO_IZQUIERDA_CH, 0, LARGO_PREDETERMINADO_1CH - c);            \
    aLoadBuffer(pkt, VIRTUAL_A_PHYSICAL2(reverb_sintesis.buffer_anillo.izquierda + (apagado))); \
    aSetBuffer(pkt, 0, c + DMEM_DIRECCION_HUMEDO_DERECHA_CH, 0, LARGO_PREDETERMINADO_1CH - c);           \
    aLoadBuffer(pkt, VIRTUAL_A_PHYSICAL2(reverb_sintesis.buffer_anillo.derecha + (apagado)))

#define a_conjunto_guardado_buffer_par(pkt, c, d, apagado)                                            \
    aSetBuffer(pkt, 0, 0, c + DMEM_DIRECCION_HUMEDO_IZQUIERDA_CH, d);                              \
    aSaveBuffer(pkt, VIRTUAL_A_PHYSICAL2(reverb_sintesis.buffer_anillo.izquierda + (apagado))); \
    aSetBuffer(pkt, 0, 0, c + DMEM_DIRECCION_HUMEDO_DERECHA_CH, d);                             \
    aSaveBuffer(pkt, VIRTUAL_A_PHYSICAL2(reverb_sintesis.buffer_anillo.derecha + (apagado)));

struct CambioVolumen {
    u16 izquierda_origen;
    u16 derecha_origen;
    u16 izquierda_objetivo;
    u16 derecha_objetivo;
};

u64* procesar_envolvente(u64* cmd, struct EuSubNota* eu_sub_nota, struct EstadoSintesisNota* estado_sintesis, s32 muestras_n,
                      u16 en_buf, s32 ajustes_paneo_auriculares, u32 banderas);

struct ReverbSintesis reverbs_sintesis[4];
u8 relleno_sintesis_audio[0x10];

char cadena_audio_sintesis_0[] = "Terminate-Canceled Channel %d,Phase %d\n";
char cadena_audio_sintesis_1[] = "Copy %d\n";
char cadena_audio_sintesis_2[] = "%d->%d\n";
char cadena_audio_sintesis_3[] = "pitch %x: delaybytes %d : olddelay %d\n";
char cadena_audio_sintesis_4[] = "cont %x: delaybytes %d : olddelay %d\n";

void preparar_buffer_anillo_reverb(s32 largo_trozo, u32 actualizar_indice, s32 indice_reverb) {
    struct ReverbAnilloBufferItem* item;
    struct ReverbSintesis* reverb = &reverbs_sintesis[indice_reverb];
    s32 pos_orig;
    s32 dst_pos;
    s32 muestras_n;
    s32 muestras_excesivo;
    s32 SIN_USO relleno[3];
    if (reverb->tasa_submuestreo != 1) {
        if (reverb->izquierda_frames_a_ignorar == 0) {
            item = &reverb->items[reverb->frame_act][actualizar_indice];

            osInvalDCache(item->a_izquierda_submuestreo, 0x300);

            for (pos_orig = 0, dst_pos = 0; dst_pos < item->longitud_a / 2; pos_orig += reverb->tasa_submuestreo, dst_pos++) {
                reverb->buffer_anillo.izquierda[item->pos_inicio + dst_pos] = item->a_izquierda_submuestreo[pos_orig];
                reverb->buffer_anillo.derecha[item->pos_inicio + dst_pos] = item->a_derecha_submuestreo[pos_orig];
            }
            for (dst_pos = 0; dst_pos < item->longitud_b / 2; pos_orig += reverb->tasa_submuestreo, dst_pos++) {
                reverb->buffer_anillo.izquierda[dst_pos] = item->a_izquierda_submuestreo[pos_orig];
                reverb->buffer_anillo.derecha[dst_pos] = item->a_derecha_submuestreo[pos_orig];
            }
        }
    }

    item = &reverb->items[reverb->frame_act][actualizar_indice];
    muestras_n = largo_trozo / reverb->tasa_submuestreo;
    muestras_excesivo = (muestras_n + reverb->siguiente_anillo_buffer_pos) - reverb->tamanio_buf_por_canal;
    if (muestras_excesivo < 0) {
        item->longitud_a = muestras_n * 2;
        item->longitud_b = 0;
        item->pos_inicio = (s32) reverb->siguiente_anillo_buffer_pos;
        reverb->siguiente_anillo_buffer_pos += muestras_n;
    } else {
        item->longitud_a = (muestras_n - muestras_excesivo) * 2;
        item->longitud_b = muestras_excesivo * 2;
        item->pos_inicio = reverb->siguiente_anillo_buffer_pos;
        reverb->siguiente_anillo_buffer_pos = muestras_excesivo;
    }
    item->muestras_num_despues_submuestreo = muestras_n;
    item->largo_trozo = largo_trozo;
}

Acmd* cargar_buffer_anillo_reverb_sintesis(Acmd* acmd, u16 direccion, u16 desplazamiento_orig, s32 largo, s32 indice_reverb) {
    aLoadBuffer(acmd++, VIRTUAL_A_PHYSICAL2(&reverbs_sintesis[indice_reverb].buffer_anillo.izquierda[desplazamiento_orig]), direccion, largo);
    aLoadBuffer(acmd++, VIRTUAL_A_PHYSICAL2(&reverbs_sintesis[indice_reverb].buffer_anillo.derecha[desplazamiento_orig]), direccion + 0x180,
                largo);
    return acmd;
}

Acmd* guardar_buffer_anillo_reverb_sintesis(Acmd* acmd, u16 direccion, u16 desplazamiento_dest, s32 largo, s32 indice_reverb) {
    aSaveBuffer(acmd++, direccion, VIRTUAL_A_PHYSICAL2(&reverbs_sintesis[indice_reverb].buffer_anillo.izquierda[desplazamiento_dest]), largo);
    aSaveBuffer(acmd++, direccion + 0x180,
                VIRTUAL_A_PHYSICAL2(&reverbs_sintesis[indice_reverb].buffer_anillo.derecha[desplazamiento_dest]), largo);
    return acmd;
}

void funcion_800B6FB4(s32 actualizar_inicio_indice, s32 indice_nota) {
    s32 i;

    for (i = actualizar_inicio_indice + 1; i < parametros_buffer_audio.actualizaciones_por_frame; i++) {
        if (!eu_subs_nota[notas_simultaneo_max * i + indice_nota].inicializacion_necesita) {
            eu_subs_nota[notas_simultaneo_max * i + indice_nota].activado = false;
        } else {
            break;
        }
    }
}

void cargar_eu_subs_nota_sintesis(s32 actualizar_indice) {
    struct EuSubNota* orig_;
    struct EuSubNota* dest;
    s32 i;

    for (i = 0; i < notas_simultaneo_max; i++) {
        orig_ = &notas[i].eu_sub_nota;
        dest = &eu_subs_nota[notas_simultaneo_max * actualizar_indice + i];
        if (orig_->activado) {
            *dest = *orig_;
            orig_->inicializacion_necesita = false;
        } else {
            dest->activado = false;
        }
    }
}

Acmd* ejecutar_sintesis(Acmd* acmd, s32* ordenes_escrito, s16* ai_buf, s32 largo_buf) {
    s32 i, j;
    u32* ai_buf_ptr;
    Acmd* cmd = acmd;
    s32 largo_trozo;

    for (i = parametros_buffer_audio.actualizaciones_por_frame; i > 0; i--) {
        procesar_secuencias(i - 1);
        cargar_eu_subs_nota_sintesis(parametros_buffer_audio.actualizaciones_por_frame - i);
    }
    aSegment(cmd++, 0, 0);
    ai_buf_ptr = (u32*) ai_buf;
    for (i = parametros_buffer_audio.actualizaciones_por_frame; i > 0; i--) {
        if (i == 1) {
            largo_trozo = largo_buf;
        } else {
            if (largo_buf / i >= parametros_buffer_audio.muestras_por_max_actualizacion) {
                largo_trozo = parametros_buffer_audio.muestras_por_max_actualizacion;
            } else if (largo_buf / i <= parametros_buffer_audio.muestras_por_min_actualizacion) {
                largo_trozo = parametros_buffer_audio.muestras_por_min_actualizacion;
            } else {
                largo_trozo = parametros_buffer_audio.muestras_por_actualizacion;
            }
        }
        for (j = 0; j < reverbs_sintesis_num; j++) {
            if (reverbs_sintesis[j].reverb_usar != 0) {
                preparar_buffer_anillo_reverb(largo_trozo, parametros_buffer_audio.actualizaciones_por_frame - i, j);
            }
        }
        cmd = actualizar_audio_hacer_uno_sintesis((s16*) ai_buf_ptr, largo_trozo, cmd, parametros_buffer_audio.actualizaciones_por_frame - i);
        largo_buf -= largo_trozo;
        ai_buf_ptr += largo_trozo;
    }

    for (j = 0; j < reverbs_sintesis_num; j++) {
        if (reverbs_sintesis[j].izquierda_frames_a_ignorar != 0) {
            reverbs_sintesis[j].izquierda_frames_a_ignorar--;
        }
        reverbs_sintesis[j].frame_act ^= 1;
    }
    *ordenes_escrito = cmd - acmd;
    return cmd;
}

Acmd* remuestreo_sintesis_y_reverb_mezcla(Acmd* acmd, s32 largo_buf, s16 indice_reverb, s16 actualizar_indice) {
    struct ReverbAnilloBufferItem* item;
    s16 empezar_relleno;
    s16 longitud_a_rellenado;

    item = &reverbs_sintesis[indice_reverb].items[reverbs_sintesis[indice_reverb].frame_act][actualizar_indice];
    aClearBuffer(acmd++, 0x840, 0x300);
    if (reverbs_sintesis[indice_reverb].tasa_submuestreo == 1) {

        acmd = cargar_buffer_anillo_reverb_sintesis(acmd, 0x840, item->pos_inicio, item->longitud_a, indice_reverb);
        if (item->longitud_b != 0) {
            acmd = cargar_buffer_anillo_reverb_sintesis(acmd, item->longitud_a + 0x840, 0U, item->longitud_b, indice_reverb);
        }

        aMix(acmd++, 0x7fff, 0x840, 0x540, 0x300);
        aMix(acmd++, 0x8000 + reverbs_sintesis[indice_reverb].ganancia_reverb, 0x840, 0x840, 0x300);
    } else {
        empezar_relleno = (item->pos_inicio % 8U) * 2;
        longitud_a_rellenado = ALIGN(empezar_relleno + item->longitud_a, 4);

        acmd =
            cargar_buffer_anillo_reverb_sintesis(acmd, 0x0020, item->pos_inicio - (empezar_relleno / 2), 0x00000180, indice_reverb);
        if (item->longitud_b != 0) {
            acmd = cargar_buffer_anillo_reverb_sintesis(acmd, longitud_a_rellenado + 0x20, 0, 0x180 - longitud_a_rellenado, indice_reverb);
        }

        aSetBuffer(acmd++, 0, 0x20 + empezar_relleno, 0x840, largo_buf * 2);
        aResample(acmd++, reverbs_sintesis[indice_reverb].banderas_remuestreo, reverbs_sintesis[indice_reverb].tasa_remuestreo,
                  VIRTUAL_A_PHYSICAL2(reverbs_sintesis[indice_reverb].izquierda_estado_remuestreo));
        aSetBuffer(acmd++, 0, 0x1A0 + empezar_relleno, 0x9C0, largo_buf * 2);
        aResample(acmd++, reverbs_sintesis[indice_reverb].banderas_remuestreo, reverbs_sintesis[indice_reverb].tasa_remuestreo,
                  VIRTUAL_A_PHYSICAL2(reverbs_sintesis[indice_reverb].derecha_estado_remuestreo));
        aMix(acmd++, 0x7fff, 0x840, 0x540, 0x300);
        aMix(acmd++, 0x8000 + reverbs_sintesis[indice_reverb].ganancia_reverb, 0x840, 0x840, 0x300);
    }
    return acmd;
}

Acmd* guardar_muestras_reverb_sintesis(Acmd* acmd, s16 indice_reverb, s16 actualizar_indice) {
    struct ReverbAnilloBufferItem* item;

    item = &reverbs_sintesis[indice_reverb].items[reverbs_sintesis[indice_reverb].frame_act][actualizar_indice];
    if (reverbs_sintesis[indice_reverb].reverb_usar != 0) {
        switch (reverbs_sintesis[indice_reverb].tasa_submuestreo) {
            case 1:
                acmd = guardar_buffer_anillo_reverb_sintesis(acmd, 0x840, item->pos_inicio, item->longitud_a, indice_reverb);
                if (item->longitud_b != 0) {
                    acmd =
                        guardar_buffer_anillo_reverb_sintesis(acmd, 0x840 + item->longitud_a, 0, item->longitud_b, indice_reverb);
                }
                break;
            default:
                aSaveBuffer(acmd++, 0x840,
                            VIRTUAL_A_PHYSICAL2(reverbs_sintesis[indice_reverb]
                                                     .items[reverbs_sintesis[indice_reverb].frame_act][actualizar_indice]
                                                     .a_izquierda_submuestreo),
                            0x300);
                reverbs_sintesis[indice_reverb].banderas_remuestreo = 0;
                break;
        }
    }
    return acmd;
}

Acmd* actualizar_audio_hacer_uno_sintesis(s16* ai_buf, s32 largo_buf, Acmd* acmd, s32 actualizar_indice) {
    struct EuSubNota* eu_sub_nota;
    u8 indices_nota[56];
    s32 temporal_;
    s32 i;
    s16 j;
    s16 pos_nota = 0;

    if (reverbs_sintesis_num == 0) {
        for (i = 0; i < notas_simultaneo_max; i++) {
            if (eu_subs_nota[notas_simultaneo_max * actualizar_indice + i].activado) {
                indices_nota[pos_nota++] = i;
            }
        }
    } else {
        for (j = 0; j < reverbs_sintesis_num; j++) {
            for (i = 0; i < notas_simultaneo_max; i++) {
                eu_sub_nota = &eu_subs_nota[notas_simultaneo_max * actualizar_indice + i];
                if (eu_sub_nota->activado && j == eu_sub_nota->indice_reverb) {
                    indices_nota[pos_nota++] = i;
                }
            }
        }

        for (i = 0; i < notas_simultaneo_max; i++) {
            eu_sub_nota = &eu_subs_nota[notas_simultaneo_max * actualizar_indice + i];
            if (eu_sub_nota->activado && eu_sub_nota->indice_reverb >= reverbs_sintesis_num) {
                indices_nota[pos_nota++] = i;
            }
        }
    }
    aClearBuffer(acmd++, DMEM_DIRECCION_IZQUIERDA_CH, LARGO_PREDETERMINADO_2CH);
    i = 0;
    for (j = 0; j < reverbs_sintesis_num; j++) {
        reverb_usar = reverbs_sintesis[j].reverb_usar;
        if (reverb_usar != 0) {
            acmd = remuestreo_sintesis_y_reverb_mezcla(acmd, largo_buf, j, actualizar_indice);
        }
        for (; i < pos_nota; i++) {
            temporal_ = actualizar_indice * notas_simultaneo_max;
            if (j == eu_subs_nota[temporal_ + indices_nota[i]].indice_reverb) {
                acmd = procesar_nota_sintesis(indices_nota[i], &eu_subs_nota[temporal_ + indices_nota[i]],
                                              &notas[indices_nota[i]].estado_sintesis, ai_buf, largo_buf, acmd, actualizar_indice);
                continue;
            } else {
                break;
            }
        }
        if (reverbs_sintesis[j].reverb_usar != 0) {
            acmd = guardar_muestras_reverb_sintesis(acmd, j, actualizar_indice);
        }
    }
    for (; i < pos_nota; i++) {
        temporal_ = actualizar_indice * notas_simultaneo_max;
        if (ES_BANCO_CARGA_COMPLETO(eu_subs_nota[temporal_ + indices_nota[i]].id_banco) == true) {
            acmd = procesar_nota_sintesis(indices_nota[i], &eu_subs_nota[temporal_ + indices_nota[i]],
                                          &notas[indices_nota[i]].estado_sintesis, ai_buf, largo_buf, acmd, actualizar_indice);
        } else {
            banderas_error_audio = (eu_subs_nota[temporal_ + indices_nota[i]].id_banco + (i << 8)) + 0x10000000;
        }
    }

    temporal_ = largo_buf * 2;
    aSetBuffer(acmd++, 0, 0, TEMPORAL_DIRECCION_DMEM, temporal_);
    aInterleave(acmd++, DMEM_DIRECCION_IZQUIERDA_CH, DMEM_DIRECCION_DERECHA_CH);
    aSaveBuffer(acmd++, TEMPORAL_DIRECCION_DMEM, VIRTUAL_A_PHYSICAL2(ai_buf), temporal_ * 2);
    return acmd;
}

Acmd* procesar_nota_sintesis(s32 indice_nota, struct EuSubNota* eu_sub_nota, struct EstadoSintesisNota* estado_sintesis,
                             SIN_USO s16* ai_buf, s32 en_buf, Acmd* cmd, s32 actualizar_indice) {
    s32 relleno[3];
    struct MuestraBancoAudio *muestra_libro_audio;
    struct BucleAdpcm *info_bucle;
    s16 *libro_cargado_act;
    s32 relleno4;
    s32 muestras_na_carga;
    s32 nota_terminado;
    s32 reiniciar;
    s32 banderas;
    u16 remuestreo_tasa_fijo_punto;
    s32 relleno2[1];
    u16 derecha_paneo_auriculares;
    s32 bucle_info_2;
    s32 a1;
#ifdef TARGET_PS2
    // Una nota con tono 0 no carga muestras
    static s32 sp_fc;
#else
    s32 sp_fc;
#endif
    s32 relleno3;
    s32 n_adpcm_muestras_procesado;
    s32 s4;
    u8 *direccion_muestra;
    s32 s3;
    s32 muestras_largo_ajustado;
    s32 derecha_izquierda;
    s32 pos_fin;
    s32 muestras_na_proceso;
    u32 muestras_largo_fijo_punto;
    s32 variable_s6;
    s32 muestras_n_en_este_iteracion;
    u32 variable_t2;
    u8 *variable_a0_2;
    s32 s_5_alineado;
    s32 temporal_t6;
    s32 aligned;
    struct MuestraBancoAudio *muestra_banco;
    s32 partes_n;
    s32 parte_act;
    s32 relleno5;
    s16 direccion;
    s32 largo_temporal_remuestreado;
    u16 nota_muestras_dmem_direccion_antes_remuestreo;
    s32 restante_muestras;
    s32 s1;
    u32 entradas_n;
    struct Nota *nota;

    libro_cargado_act = NULL;
    nota = &notas[indice_nota];
    banderas = 0;
    if (eu_sub_nota->inicializacion_necesita == true) {
        banderas = A_INIT;
        estado_sintesis->reinicio = 0;
        estado_sintesis->int_pos_muestra = 0;
        estado_sintesis->frac_pos_muestra = 0;
        estado_sintesis->izquierda_vol_act = 0;
        estado_sintesis->derecha_vol_act = 0;
        estado_sintesis->ant_auriculares_paneo_derecha = 0;
        estado_sintesis->ant_auriculares_paneo_izquierda = 0;
    }
    remuestreo_tasa_fijo_punto = eu_sub_nota->remuestreo_tasa_fijo_punto;

    partes_n = eu_sub_nota->partes_adpcm_tiene_dos + 1;
    muestras_largo_fijo_punto = ((remuestreo_tasa_fijo_punto * en_buf) * 2) + estado_sintesis->frac_pos_muestra;
    muestras_na_carga = muestras_largo_fijo_punto >> 0x10;
    estado_sintesis->frac_pos_muestra = muestras_largo_fijo_punto & 0xFFFF;

    if (eu_sub_nota->ola_sintetico_es) {
        cmd = cargar_muestras_ola(cmd, eu_sub_nota, estado_sintesis, muestras_na_carga);

        nota_muestras_dmem_direccion_antes_remuestreo = (estado_sintesis->int_pos_muestra * 2) + 0x1A0;
        estado_sintesis->int_pos_muestra += muestras_na_carga;
    } else {
        muestra_libro_audio = eu_sub_nota->sonido.sonido_banco_audio->muestra;
        info_bucle = muestra_libro_audio->loop;
        pos_fin = info_bucle->end;
        direccion_muestra = muestra_libro_audio->direccion_muestra;
        largo_temporal_remuestreado = 0;

        for (parte_act = 0; parte_act < partes_n; parte_act++) {
            muestra_banco = muestra_libro_audio;
            n_adpcm_muestras_procesado = 0;
            s4 = 0;

            if (partes_n == 1) {
                muestras_largo_ajustado = muestras_na_carga;
            } else if (muestras_na_carga & 1) {
                muestras_largo_ajustado = (muestras_na_carga & (~1)) + (parte_act * 2);
            } else {
                muestras_largo_ajustado = muestras_na_carga;
            }
            if (libro_cargado_act != (*muestra_banco->libro).libro) {
                libro_cargado_act = muestra_banco->libro->libro;
                entradas_n = (16 * muestra_banco->libro->orden) * muestra_banco->libro->npredictors;
                aLoadADPCM(cmd++, entradas_n, VIRTUAL_A_PHYSICAL2(eu_sub_nota->desplazamiento_libro+libro_cargado_act));
            }
            if (eu_sub_nota->desplazamiento_libro != 0) {
                libro_cargado_act = &desconocido_datos_800F6290[0];
            }
            while (n_adpcm_muestras_procesado != muestras_largo_ajustado) {
                nota_terminado = false;
                reiniciar = false;

                s3 = estado_sintesis->int_pos_muestra & 0xF;
                restante_muestras = pos_fin - estado_sintesis->int_pos_muestra;
                muestras_na_proceso = muestras_largo_ajustado - n_adpcm_muestras_procesado;
                if ((s3 == 0) && (estado_sintesis->reinicio == false)) {
                    s3 = 16;
                }

                a1 = 16 - s3;

                if (muestras_na_proceso < restante_muestras) {
                    bucle_info_2 = ((muestras_na_proceso - a1) + 0xF) / 16;
                    s1 = bucle_info_2 * 16;
                    variable_s6 = (a1 + s1) - muestras_na_proceso;
                } else {
                    s1 = restante_muestras - a1;
                    variable_s6 = 0;
                    if (s1 <= 0) {
                        s1 = 0;
                        a1 = restante_muestras;
                    }
                    bucle_info_2 = (s1 + 0xF) / 16;
                    if (info_bucle->count != 0) {
                        reiniciar = 1;
                    } else {
                        nota_terminado = 1;
                    }
                }

                if (bucle_info_2 != 0) {
                    temporal_t6 = ((estado_sintesis->int_pos_muestra - s3) + 16) / 16;
                    if (muestra_banco->cargado == 0x81) {
                        variable_a0_2 = (temporal_t6 * 9) + direccion_muestra;
                    } else {
                        variable_a0_2 =
                            datos_muestra_dma((uintptr_t) ((temporal_t6 * 9) + direccion_muestra), ALIGN(((bucle_info_2 * 9) + 16), 4),
                                            banderas, &estado_sintesis->indice_dma_muestra);
                    }

                    variable_t2 = ((uintptr_t) variable_a0_2) & 0xF;
                    aligned = ALIGN(((bucle_info_2 * 9) + 16), 4);
                    direccion = (0x540 - aligned);
                    aLoadBuffer(cmd++, VIRTUAL_A_PHYSICAL2(variable_a0_2 - variable_t2), direccion, aligned);
                } else {
                    s1 = 0;
                    variable_t2 = 0;
                }

                if (estado_sintesis->reinicio != false) {
                    aSetLoop(cmd++, VIRTUAL_A_PHYSICAL2(muestra_banco->loop->state));

                    banderas = A_LOOP;
                    estado_sintesis->reinicio = false;
                }
                muestras_n_en_este_iteracion = (s1 + a1) - variable_s6;
                s_5_alineado = ALIGN(s4 + 16, 4);
                if (n_adpcm_muestras_procesado == 0) {

                    aligned = ALIGN(((bucle_info_2 * 9) + 16), 4);
                    direccion = (0x540 - aligned);
                    aSetBuffer(cmd++, 0, direccion + variable_t2, 0x1A0, s1 * 2);
                    aADPCMdec(cmd++, banderas, VIRTUAL_A_PHYSICAL2(estado_sintesis->buffers_sintesis->estado_adpcmdec));
                    sp_fc = s3 * 2;
                } else {
                    aligned = ALIGN(((bucle_info_2 * 9) + 16), 4);
                    direccion = (0x540 - aligned);
                    aSetBuffer(cmd++, 0, direccion + variable_t2, 0x1A0 + s_5_alineado, s1 * 2);
                    aADPCMdec(cmd++, banderas, VIRTUAL_A_PHYSICAL2(estado_sintesis->buffers_sintesis->estado_adpcmdec));
                    aDMEMMove(cmd++, 0x1A0 + s_5_alineado + (s3 * 2), 0x1A0 + s4, muestras_n_en_este_iteracion * 2);
                }

                n_adpcm_muestras_procesado += muestras_n_en_este_iteracion;
                switch (banderas) {
                    case 1:
                        sp_fc = 0x20;
                        s4 = (s1 * 2) + 0x20;
                        break;
                    case 2:
                        s4 = (muestras_n_en_este_iteracion * 2) + s4;
                        break;
                    default:
                        if (s4 != 0) {
                            s4 = (muestras_n_en_este_iteracion * 2) + s4;
                        } else {
                            s4 = (s3 + muestras_n_en_este_iteracion) * 2;
                        }
                        break;
                }

                banderas = 0;
                if (nota_terminado) {
                    aClearBuffer(cmd++, 0x1A0 + s4, (muestras_largo_ajustado - n_adpcm_muestras_procesado) * 2);
                    eu_sub_nota->terminado = 1;
                    nota->eu_sub_nota.terminado = 1;
                    nota->eu_sub_nota.activado = 0;
                    funcion_800B6FB4(actualizar_indice, indice_nota);
                    break;
                }

                if (reiniciar) {
                    estado_sintesis->reinicio = true;
                    estado_sintesis->int_pos_muestra = info_bucle->start;
                } else {
                    estado_sintesis->int_pos_muestra += muestras_na_proceso;
                }
            }

            switch (partes_n) {
                case 1:
                    nota_muestras_dmem_direccion_antes_remuestreo = 0x1A0 + sp_fc;
                    break;
                case 2:
                    switch (parte_act) {
                        case 0:
                            aDownsampleHalf(cmd++, ALIGN(muestras_largo_ajustado / 2, 3), 0x1A0 + sp_fc, DMEM_DIRECCION_REMUESTREADO);
                            largo_temporal_remuestreado = muestras_largo_ajustado;
                            nota_muestras_dmem_direccion_antes_remuestreo = DMEM_DIRECCION_REMUESTREADO;
                            if (eu_sub_nota->terminado != false) {
                                aClearBuffer(cmd++, nota_muestras_dmem_direccion_antes_remuestreo + largo_temporal_remuestreado,
                                             muestras_largo_ajustado + 0x10);
                            }
                            break;
                        case 1:
                            aDownsampleHalf(cmd++, ALIGN(muestras_largo_ajustado / 2, 3), RESAMPLED2_DIRECCION_DMEM + sp_fc,
                                            largo_temporal_remuestreado + DMEM_DIRECCION_REMUESTREADO);
                            break;
                    }
            }
            if (eu_sub_nota->terminado != false) {
                break;
            }
        }
    }
    banderas = 0;
    if (eu_sub_nota->inicializacion_necesita == true) {
        banderas = A_INIT;
        eu_sub_nota->inicializacion_necesita = false;
    }

    cmd = remuestreo_final(cmd, estado_sintesis, en_buf * 2, remuestreo_tasa_fijo_punto, nota_muestras_dmem_direccion_antes_remuestreo, banderas);
    derecha_paneo_auriculares = eu_sub_nota->derecha_paneo_auriculares;
    if ((derecha_paneo_auriculares & 0xFFFF) || estado_sintesis->ant_auriculares_paneo_derecha) {
        derecha_izquierda = 1;
    } else if (eu_sub_nota->izquierda_paneo_auriculares || estado_sintesis->ant_auriculares_paneo_izquierda) {
        derecha_izquierda = 2;
    } else {
        derecha_izquierda = 0;
    }
    cmd = funcion_800B86A0(cmd, eu_sub_nota, estado_sintesis, en_buf, 0, derecha_izquierda, banderas);
    if (eu_sub_nota->usa_auriculares_paneo_efectos) {
        cmd = aplicar_efectos_paneo_auriculares_nota(cmd, eu_sub_nota, estado_sintesis, en_buf * 2, banderas, derecha_izquierda);
    }
    return cmd;
}

Acmd* cargar_muestras_ola(Acmd* acmd, struct EuSubNota* eu_sub_nota, struct EstadoSintesisNota* estado_sintesis,
                        s32 muestras_na_carga) {
    s32 a3;
    s32 repeticiones;
    aLoadBuffer(acmd++, VIRTUAL_A_PHYSICAL2(eu_sub_nota->sonido.muestras), 0x1A0, 128);

    estado_sintesis->int_pos_muestra &= 0x3f;
    a3 = 64 - estado_sintesis->int_pos_muestra;
    if (a3 < muestras_na_carga) {
        repeticiones = (muestras_na_carga - a3 + 63) / 64;
        if (repeticiones != 0) {
            aDMEMMove2(acmd++, repeticiones, 0x1A0, 0x1A0 + 128, 128);
        }
    }
    return acmd;
}

Acmd* remuestreo_final(Acmd* acmd, struct EstadoSintesisNota* estado_sintesis, s32 cantidad, u16 tono, u16 dmem_en,
                     u32 banderas) {
    aSetBuffer(acmd++,  0, dmem_en,  0, cantidad);
    aResample(acmd++, banderas, tono, VIRTUAL_A_PHYSICAL2(estado_sintesis->buffers_sintesis->estado_remuestreo_final));
    return acmd;
}

Acmd* funcion_800B86A0(Acmd* cmd, struct EuSubNota* nota, struct EstadoSintesisNota* estado_sintesis, s32 muestras_n,
                    u16 en_buf, s32 ajustes_paneo_auriculares, SIN_USO u32 banderas) {
    SIN_USO s32 relleno[2];
    u16 derecha_origen;
    u16 izquierda_origen;
    u16 izquierda_objetivo;
    u16 derecha_objetivo;
    s16 izquierda_rampa;
    s16 derecha_rampa;

    izquierda_origen = estado_sintesis->izquierda_vol_act;
    derecha_origen = estado_sintesis->derecha_vol_act;

    izquierda_objetivo = (nota->izquierda_vol_objetivo) << 4;
    derecha_objetivo = (nota->derecha_vol_objetivo) << 4;

    izquierda_rampa  = ((izquierda_objetivo  - izquierda_origen)  / (muestras_n >> 3));
    derecha_rampa = ((derecha_objetivo - derecha_origen) / (muestras_n >> 3));
    izquierda_objetivo  = izquierda_origen  + izquierda_rampa  * (muestras_n >> 3);
    derecha_objetivo = derecha_origen + derecha_rampa * (muestras_n >> 3);

    estado_sintesis->izquierda_vol_act = izquierda_objetivo;
    estado_sintesis->derecha_vol_act = derecha_objetivo;

    if (nota->usa_auriculares_paneo_efectos) {
        aClearBuffer(cmd++, DMEM_DIRECCION_NOTA_PANEO_TEMPORAL, LARGO_PREDETERMINADO_1CH);
        aEnvSetup1Alt(cmd++, nota->reverb_vol, izquierda_origen, derecha_origen, (u32)izquierda_rampa, (u32)derecha_rampa);
        aEnvSetup2(cmd++, izquierda_origen, derecha_origen);

        switch (ajustes_paneo_auriculares) {;
            case 1:
                aEnvMixer(cmd++,
                    en_buf, muestras_n,
                    0,
                    nota->derecha_fuerte_estereo, nota->izquierda_fuerte_estereo,
                    DMEM_DIRECCION_NOTA_PANEO_TEMPORAL,
                    DMEM_DIRECCION_DERECHA_CH,
                    DMEM_DIRECCION_HUMEDO_IZQUIERDA_CH,
                    DMEM_DIRECCION_HUMEDO_DERECHA_CH);
                break;
            case 2:
                aEnvMixer(cmd++,
                    en_buf, muestras_n,
                    0,
                    nota->derecha_fuerte_estereo, nota->izquierda_fuerte_estereo,
                    DMEM_DIRECCION_IZQUIERDA_CH,
                    DMEM_DIRECCION_NOTA_PANEO_TEMPORAL,
                    DMEM_DIRECCION_HUMEDO_IZQUIERDA_CH,
                    DMEM_DIRECCION_HUMEDO_DERECHA_CH);
                break;
            default:
                aEnvMixer(cmd++,
                    en_buf, muestras_n,
                    0,
                    nota->derecha_fuerte_estereo, nota->izquierda_fuerte_estereo,
                    DMEM_DIRECCION_IZQUIERDA_CH,
                    DMEM_DIRECCION_DERECHA_CH,
                    DMEM_DIRECCION_HUMEDO_IZQUIERDA_CH,
                    DMEM_DIRECCION_HUMEDO_DERECHA_CH);
                break;
        }
    } else {
        aEnvSetup1Alt(cmd++, nota->reverb_vol, izquierda_origen, derecha_origen, (u32)izquierda_rampa, (u32)derecha_rampa);
        aEnvSetup2(cmd++, izquierda_origen, derecha_origen);
        aEnvMixer(cmd++,
                en_buf, muestras_n,
                0,
                nota->derecha_fuerte_estereo, nota->izquierda_fuerte_estereo,
                DMEM_DIRECCION_IZQUIERDA_CH,
                DMEM_DIRECCION_DERECHA_CH,
                DMEM_DIRECCION_HUMEDO_IZQUIERDA_CH,
                DMEM_DIRECCION_HUMEDO_DERECHA_CH);
    }
    return cmd;
}

Acmd* aplicar_efectos_paneo_auriculares_nota(Acmd* acmd, struct EuSubNota* eu_sub_nota, struct EstadoSintesisNota* nota,
                                     s32 largo_buf, s32 banderas, s32 derecha_izquierda) {
    u16 dest;
    u16 tono;
    u8 desplaz_paneo_ant;
    u8 desplaz_paneo;
    SIN_USO u8 depuracion_desconocido;

    switch (derecha_izquierda) {
        case 1:
            dest = 0x540;
            desplaz_paneo = eu_sub_nota->derecha_paneo_auriculares;
            nota->ant_auriculares_paneo_izquierda = 0;
            desplaz_paneo_ant = nota->ant_auriculares_paneo_derecha;
            nota->ant_auriculares_paneo_derecha = desplaz_paneo;
            break;
        case 2:
            dest = 0x6C0;
            desplaz_paneo = eu_sub_nota->izquierda_paneo_auriculares;
            nota->ant_auriculares_paneo_derecha = 0;

            desplaz_paneo_ant = nota->ant_auriculares_paneo_izquierda;
            nota->ant_auriculares_paneo_izquierda = desplaz_paneo;
            break;
        default:
            return acmd;
    }

    if (banderas != 1) {
        if (desplaz_paneo_ant == 0) {
            aDMEMMove(acmd++, 0x0200, 0x0000, 8);
            aClearBuffer(acmd++, 8, 8);
            aDMEMMove(acmd++, 0x0200, 0x0000 + 0x10,
                      0x10);

            aSaveBuffer(acmd++, 0x0000, VIRTUAL_A_PHYSICAL2(nota->buffers_sintesis->estado_remuestreo_paneo),
                        sizeof(nota->buffers_sintesis->estado_remuestreo_paneo));

            tono = (largo_buf << 0xf) / (largo_buf + desplaz_paneo - desplaz_paneo_ant + 8);
            if (tono) {}
            aSetBuffer(acmd++, 0, 0x0200 + 8, 0x0000, desplaz_paneo + largo_buf - desplaz_paneo_ant);
            aResample(acmd++, 0, tono, VIRTUAL_A_PHYSICAL2(nota->buffers_sintesis->estado_remuestreo_paneo));
        } else {
            if (desplaz_paneo == 0) {
                tono = (largo_buf << 0xf) / (largo_buf - desplaz_paneo_ant - 4);
            } else {
                tono = (largo_buf << 0xf) / (largo_buf + desplaz_paneo - desplaz_paneo_ant);
            }

            if (1) {}

            aSetBuffer(acmd++, 0, 0x0200, 0x0000, largo_buf + desplaz_paneo - desplaz_paneo_ant);
            aResample(acmd++, 0, tono, VIRTUAL_A_PHYSICAL2(nota->buffers_sintesis->estado_remuestreo_paneo));
        }

        if (desplaz_paneo_ant != 0) {
            aLoadBuffer(acmd++, VIRTUAL_A_PHYSICAL2(nota->buffers_sintesis->buffer_muestras_paneo), 0x0200, desplaz_paneo_ant);
            aDMEMMove(acmd++, 0x0000, 0x0200 + desplaz_paneo_ant, desplaz_paneo + largo_buf - desplaz_paneo_ant);
        } else {
            aDMEMMove(acmd++, 0x0000, 0x0200, desplaz_paneo + largo_buf - desplaz_paneo_ant);
        }
    } else {
        aDMEMMove(acmd++, 0x0200, 0x0000, largo_buf);
        aDMEMMove(acmd++, 0x0000, 0x0200 + desplaz_paneo, largo_buf);
        aClearBuffer(acmd++, 0x0200, desplaz_paneo);
    }

    if (desplaz_paneo) {
        aSaveBuffer(acmd++, 0x0200 + largo_buf, VIRTUAL_A_PHYSICAL2(nota->buffers_sintesis->buffer_muestras_paneo), desplaz_paneo);
    }

    aMix(acmd++,  0x7FFF,  0x0200,  dest, ALIGN(largo_buf, 5));

    return acmd;
}
