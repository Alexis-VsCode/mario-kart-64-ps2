#include <ultra64.h>
#include <juego/macros.h>

#include "audio/reproductor_secuencias.h"
#include "audio/efectos.h"
#include "audio/interno.h"
#include "audio/carga.h"
#include "audio/datos.h"

void procesar_sonido_canal_secuencia(struct CanalSecuencia* sec_canal, s32 recalcular_volumen) {
    f32 volumen_canal;
    s32 i;

    if (sec_canal->cambios.como_bitfields.volumen || recalcular_volumen) {
        volumen_canal = sec_canal->volumen * sec_canal->escala_volumen * sec_canal->sec_jugador->volumen_fundido_aplicado;
        if (sec_canal->sec_jugador->silenciado && (sec_canal->comportamiento_silencio & SUAVIZAR_COMPORTAMIENTO_SILENCIO) != 0) {
            volumen_canal = sec_canal->sec_jugador->escala_volumen_silencio * volumen_canal;
        }
        sec_canal->volumen_aplicado = volumen_canal * volumen_canal;
    }

    if (sec_canal->cambios.como_bitfields.paneo) {
        sec_canal->paneo = sec_canal->paneo_nuevo * sec_canal->peso_canal_paneo;
    }

    for (i = 0; i < 4; ++i) {
        struct CapaCanalSecuencia* capa = sec_canal->capas[i];
        if (capa != NULL && capa->activado && capa->nota != NULL) {
            if (capa->nota_propiedades_necesitar_inicializacion) {
                capa->escala_frec_nota = capa->escala_frec * sec_canal->escala_frec;
                capa->velocidad_nota = capa->cuadrado_velocidad * sec_canal->volumen_aplicado;
                capa->paneo_nota = (sec_canal->paneo + capa->paneo * (0x80 - sec_canal->peso_canal_paneo)) >> 7;
                capa->nota_propiedades_necesitar_inicializacion = false;
            } else {
                if (sec_canal->cambios.como_bitfields.escala_frec) {
                    capa->escala_frec_nota = capa->escala_frec * sec_canal->escala_frec;
                }
                if (sec_canal->cambios.como_bitfields.volumen || recalcular_volumen) {
                    capa->velocidad_nota = capa->cuadrado_velocidad * sec_canal->volumen_aplicado;
                }
                if (sec_canal->cambios.como_bitfields.paneo) {
                    capa->paneo_nota = (sec_canal->paneo + capa->paneo * (0x80 - sec_canal->peso_canal_paneo)) >> 7;
                }
            }
        }
    }
    sec_canal->cambios.as_u8 = 0;
}

void procesar_sonido_jugador_secuencia(struct JugadorSecuencia* sec_jugador) {
    s32 i;

    if (sec_jugador->frames_restante_fundido != 0) {
        sec_jugador->volumen_fundido += sec_jugador->velocidad_fundido;
        sec_jugador->volumen_recalcular = true;

        if (sec_jugador->volumen_fundido > US_FLOAT2(1)) {
            sec_jugador->volumen_fundido = US_FLOAT2(1);
        }
        if (sec_jugador->volumen_fundido < 0) {
            sec_jugador->volumen_fundido = 0;
        }

        if (--sec_jugador->frames_restante_fundido == 0) {
            if (sec_jugador->state == 2) {
                desactivar_jugador_secuencia(sec_jugador);
                return;
            }
        }
    }

    if (sec_jugador->volumen_recalcular) {
        sec_jugador->volumen_fundido_aplicado = sec_jugador->volumen_fundido * sec_jugador->escala_volumen_fundido;
    }

    for (i = 0; i < MAX_CANALES; i++) {
        if (ES_SECUENCIA_CANAL_VALIDO(sec_jugador->channels[i]) == true && sec_jugador->channels[i]->activado == true) {
            procesar_sonido_canal_secuencia(sec_jugador->channels[i], sec_jugador->volumen_recalcular);
        }
    }

    sec_jugador->volumen_recalcular = false;
}

f32 escalar_frec_portamento_obtener(struct Portamento* p) {
    u32 v0;
    f32 result;

    p->act += p->speed;
    v0 = (u32) p->act;

    if (v0 > 127) {
        v0 = 127;
    }

    result = FLOTANTE_US(1.0) + p->extension * (tono_curva_frecuencia_escala[v0 + 128] - FLOTANTE_US(1.0));
    return result;
}

s16 obtener_cambio_tono_vibrato(struct EstadoVibrato* vib) {
    s32 index;
    vib->time += (s32) vib->tasa;
    index = (vib->time >> 10) & 0x3F;
    return vib->curva[index] >> 8;
}

f32 escalar_frec_vibrato_obtener(struct EstadoVibrato* vib) {
    s32 cambio_tono;
    f32 extension_;
    f32 result;

    if (vib->delay != 0) {
        vib->delay--;
        return 1;
    }

    if (vib->temporizador_cambio_extension) {
        if (vib->temporizador_cambio_extension == 1) {
            vib->extension = (s32) vib->sec_canal->objetivo_extension_vibrato;
        } else {
            vib->extension += ((s32) vib->sec_canal->objetivo_extension_vibrato - vib->extension) / (s32) vib->temporizador_cambio_extension;
        }

        vib->temporizador_cambio_extension--;
    } else if (vib->sec_canal->objetivo_extension_vibrato != (s32) vib->extension) {
        if ((vib->temporizador_cambio_extension = vib->sec_canal->vibrato_extension_cambio_retardo) == 0) {
            vib->extension = (s32) vib->sec_canal->objetivo_extension_vibrato;
        }
    }

    if (vib->temporizador_cambio_tasa) {
        if (vib->temporizador_cambio_tasa == 1) {
            vib->tasa = (s32) vib->sec_canal->objetivo_tasa_vibrato;
        } else {
            vib->tasa += ((s32) vib->sec_canal->objetivo_tasa_vibrato - vib->tasa) / (s32) vib->temporizador_cambio_tasa;
        }

        vib->temporizador_cambio_tasa--;
    } else if (vib->sec_canal->objetivo_tasa_vibrato != (s32) vib->tasa) {
        if ((vib->temporizador_cambio_tasa = vib->sec_canal->vibrato_tasa_cambio_retardo) == 0) {
            vib->tasa = (s32) vib->sec_canal->objetivo_tasa_vibrato;
        }
    }

    if (vib->extension == 0) {
        return 1.0f;
    }

    cambio_tono = obtener_cambio_tono_vibrato(vib);
    extension_ = (f32) vib->extension / FLOTANTE_US(4096.0);

    result = FLOTANTE_US(1.0) + extension_ * (tono_curva_frecuencia_escala[cambio_tono + 128] - FLOTANTE_US(1.0));
    return result;
}

void actualizar_vibrato_nota(struct Nota* nota) {
    if (nota->portamento.mode != 0) {
        nota->escala_frec_portamento = escalar_frec_portamento_obtener(&nota->portamento);
    }
    if (nota->estado_vibrato.active && nota->capa_padre != SIN_CAPA) {
        nota->escala_frec_vibrato = escalar_frec_vibrato_obtener(&nota->estado_vibrato);
    }
}

void inicializar_vibrato_nota(struct Nota* nota) {
    struct EstadoVibrato* vib;
    SIN_USO struct CanalSecuencia* sec_canal;
    struct EstadoReproduccionNota* sec_estado_jugador = (struct EstadoReproduccionNota*) &nota->priority;

    nota->escala_frec_vibrato = 1.0f;
    nota->escala_frec_portamento = 1.0f;

    vib = &nota->estado_vibrato;

    vib->active = true;
    vib->time = 0;

    vib->curva = muestras_ola[2];
    vib->sec_canal = nota->capa_padre->sec_canal;
    if ((vib->temporizador_cambio_extension = vib->sec_canal->vibrato_extension_cambio_retardo) == 0) {
        vib->extension = CONVERSION_FLOTANTE(vib->sec_canal->objetivo_extension_vibrato);
    } else {
        vib->extension = CONVERSION_FLOTANTE(vib->sec_canal->inicio_extension_vibrato);
    }

    if ((vib->temporizador_cambio_tasa = vib->sec_canal->vibrato_tasa_cambio_retardo) == 0) {
        vib->tasa = CONVERSION_FLOTANTE(vib->sec_canal->objetivo_tasa_vibrato);
    } else {
        vib->tasa = CONVERSION_FLOTANTE(vib->sec_canal->inicio_tasa_vibrato);
    }
    vib->delay = vib->sec_canal->retardo_vibrato;

    sec_estado_jugador->portamento = sec_estado_jugador->capa_padre->portamento;
}

void inicializar_adsr(struct EstadoAdsr* adsr, struct EnvolventeAdsr* envolvente, SIN_USO s16* salida_vol) {
    adsr->accion = 0;
    adsr->state = ADSR_ESTADO_DESACTIVADO;
    adsr->delay = 0;
    adsr->envelope = envolvente;
    adsr->sostenido = 0.0f;
    adsr->current = 0.0f;
}

f32 actualizar_adsr(struct EstadoAdsr* adsr) {
    u8 accion = adsr->accion;
    u8 estado = adsr->state;
    switch (estado) {
        case ADSR_ESTADO_DESACTIVADO:
            return 0;

        case INICIAL_ESTADO_ADSR: {
            if (accion & CUELGUE_ACCION_ADSR) {
                adsr->state = CUELGUE_ESTADO_ADSR;
                break;
            }
        }

        case ADSR_ESTADO_INICIO_BUCLE:
            adsr->indice_amb = 0;
            adsr->state = BUCLE_ESTADO_ADSR;

        reiniciar:
        case BUCLE_ESTADO_ADSR:
            adsr->delay = BSWAP16(adsr->envelope[adsr->indice_amb].delay);
            switch (adsr->delay) {
                case DESACTIVAR_ADSR:
                    adsr->state = ADSR_ESTADO_DESACTIVADO;
                    break;
                case CUELGUE_ADSR:
                    adsr->state = CUELGUE_ESTADO_ADSR;
                    break;
                case ADSR_GOTO:
                    adsr->indice_amb = BSWAP16(adsr->envelope[adsr->indice_amb].arg);
                    goto reiniciar;
                case REINICIO_ADSR:
                    adsr->state = INICIAL_ESTADO_ADSR;
                    break;

                default:
                    if (adsr->delay >= 4) {
                        adsr->delay = adsr->delay * parametros_buffer_audio.actualizaciones_por_frame /
                                      parametros_buffer_audio.desconocido_ajuste_4 / 4;
                    }
                    if (adsr->delay == 0) {
                        adsr->delay = 1;
                    }
                    adsr->target = (f32) BSWAP16(adsr->envelope[adsr->indice_amb].arg) / 32767.0f;
                    adsr->target = adsr->target * adsr->target;
                    adsr->velocidad = (adsr->target - adsr->current) / adsr->delay;
                    adsr->state = FUNDIDO_ESTADO_ADSR;
                    adsr->indice_amb++;
                    break;
            }
            if (adsr->state != FUNDIDO_ESTADO_ADSR) {
                break;
            }

        case FUNDIDO_ESTADO_ADSR:
            adsr->current += adsr->velocidad;
            if (--adsr->delay <= 0) {
                adsr->state = BUCLE_ESTADO_ADSR;
            }

        case CUELGUE_ESTADO_ADSR:
            break;

        case DECAER_ESTADO_ADSR:
        case SUELTA_ESTADO_ADSR: {
            adsr->current -= adsr->vel_salida_fundido;
            if (adsr->sostenido != 0.0f && estado == DECAER_ESTADO_ADSR) {
                if (adsr->current < adsr->sostenido) {
                    adsr->current = adsr->sostenido;
                    adsr->delay = 128;
                    adsr->state = SOSTENIDO_ESTADO_ADSR;
                }
                break;
            }

            if (adsr->current < 0.00001f) {
                adsr->current = 0.0f;
                adsr->state = ADSR_ESTADO_DESACTIVADO;
            }
            break;
        }

        case SOSTENIDO_ESTADO_ADSR:
            adsr->delay -= 1;
            if (adsr->delay == 0) {
                adsr->state = SUELTA_ESTADO_ADSR;
            }
            break;
    }

    if ((accion & DECAER_ACCION_ADSR)) {
        adsr->state = DECAER_ESTADO_ADSR;
        adsr->accion = accion & ~DECAER_ACCION_ADSR;
    }

    if ((accion & SUELTA_ACCION_ADSR)) {
        adsr->state = SUELTA_ESTADO_ADSR;
        adsr->accion = accion & ~SUELTA_ACCION_ADSR;
    }

    if (adsr->current < 0.0f) {
        printf_vacio_eu_0("Env-Clear 0\n");
        return 0.0f;
    }
    if (adsr->current > 1.0f) {
        printf_vacio_eu_1("Audio:Envp: overflow  %f\n", adsr->current);
        return 1.0f;
    }
    return adsr->current;
}
