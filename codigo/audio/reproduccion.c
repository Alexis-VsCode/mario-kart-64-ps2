#include <ultra64.h>
#include <juego/macros.h>

#include "audio/interno.h"
#include "audio/reproduccion.h"
#include "audio/carga.h"
#include "audio/monton.h"
#include "audio/externo.h"
#include "audio/efectos.h"
#include "audio/datos.h"
#include "audio/reproductor_secuencias.h"

#ifdef TARGET_PS2
extern u32 notas_robadas, sonidos_sin_nota, notas_tomadas_apagandose;
#define CANTIDAD_PS2(x) ((x)++)
#else
#define CANTIDAD_PS2(x)
#endif

void fijar_reverb_paneo_vel_nota(struct Nota* nota, f32 velocidad, u8 paneo, u8 reverb_vol) {
    struct EuSubNota* sub = &nota->eu_sub_nota;
    f32 derecha_vol, izquierda_vol;
    u8 derecha_fuerte;
    u8 izquierda_fuerte;
    s32 indice_paneo_chico;
    u16 mascara_desconocido = ~0x80;

    paneo &= mascara_desconocido;

    if (nota->eu_sub_nota.efectos_auriculares_estereo && audio_bib_sonido_modo == SONIDO_AURICULARES_MODO) {
        indice_paneo_chico = paneo >> 3;
        if (indice_paneo_chico >= CANTIDAD_ARREGLO(cuantizacion_paneo_auriculares)) {
            indice_paneo_chico = CANTIDAD_ARREGLO(cuantizacion_paneo_auriculares) - 1;
        }

        sub->izquierda_paneo_auriculares = cuantizacion_paneo_auriculares[indice_paneo_chico];
        sub->derecha_paneo_auriculares = cuantizacion_paneo_auriculares[CANTIDAD_ARREGLO(cuantizacion_paneo_auriculares) - 1 - indice_paneo_chico];
        sub->derecha_fuerte_estereo = false;
        sub->izquierda_fuerte_estereo = false;
        sub->usa_auriculares_paneo_efectos = true;

        izquierda_vol = volumen_paneo_auriculares[paneo];
        derecha_vol = volumen_paneo_auriculares[127 - paneo];
    } else if (sub->efectos_auriculares_estereo && audio_bib_sonido_modo == SONIDO_ESTEREO_MODO) {
        derecha_fuerte = false;
        izquierda_fuerte = false;
        sub->derecha_paneo_auriculares = 0;
        sub->izquierda_paneo_auriculares = 0;

        sub->usa_auriculares_paneo_efectos = false;

        izquierda_vol = volumen_paneo_estereo[paneo];
        derecha_vol = volumen_paneo_estereo[127 - paneo];
        if (paneo < 0x20) {
            izquierda_fuerte = true;
        } else if (paneo > 0x60) {
            derecha_fuerte = true;
        }

        sub->derecha_fuerte_estereo = derecha_fuerte;
        sub->izquierda_fuerte_estereo = izquierda_fuerte;

    } else if (audio_bib_sonido_modo == SONIDO_MONO_MODO) {
        izquierda_vol = 0.707f;
        derecha_vol = 0.707f;
    } else {
        izquierda_vol = volumen_paneo_predeterminado[paneo];
        derecha_vol = volumen_paneo_predeterminado[127 - paneo];
    }

    if (velocidad < 0.0f) {
        printf_vacio("Audio: setvol: volume minus %f\n", velocidad);
        velocidad = 0.0f;
    }
    if (velocidad > 1.0f) {
        printf_vacio("Audio: setvol: volume overflow %f\n", velocidad);
        velocidad = 1.0f;
    }

    sub->izquierda_vol_objetivo = ((s32) (velocidad * izquierda_vol * 4095.999f));
    sub->derecha_vol_objetivo = ((s32) (velocidad * derecha_vol * 4095.999f));

    if (sub->reverb_vol != reverb_vol) {
        sub->reverb_vol = reverb_vol;
        sub->amb_mezclador_necesita_inicializacion = true;
        return;
    }

    if (sub->inicializacion_necesita) {
        sub->amb_mezclador_necesita_inicializacion = true;
    } else {
        sub->amb_mezclador_necesita_inicializacion = false;
    }
}

void fijar_tasa_remuestreo_nota(struct Nota* nota, f32 entrada_tasa_remuestreo) {
    f32 tasa_remuestreo = 0.0f;
    struct EuSubNota* sub_temporal = &nota->eu_sub_nota;

    if (entrada_tasa_remuestreo < 0.0f) {
        printf_vacio("Audio: setpitch: pitch minus %f\n", entrada_tasa_remuestreo);
        entrada_tasa_remuestreo = 0.0f;
    }
    if (entrada_tasa_remuestreo < 2.0f) {
        sub_temporal->partes_adpcm_tiene_dos = 0;

        if (1.9999599f < entrada_tasa_remuestreo) {
            tasa_remuestreo = 1.9999599f;
        } else {
            tasa_remuestreo = entrada_tasa_remuestreo;
        }

    } else {
        sub_temporal->partes_adpcm_tiene_dos = 1;
        if (2 * 1.9999599f < entrada_tasa_remuestreo) {
            tasa_remuestreo = 1.9999599f;
        } else {
            tasa_remuestreo = entrada_tasa_remuestreo * 0.5f;
        }
    }
    nota->eu_sub_nota.remuestreo_tasa_fijo_punto = (s32) (tasa_remuestreo * 32768.0f);
}

struct SonidoBancoAudio* obtener_sonido_banco_audio_instrumento(struct Instrumento* instrumento, s32 semitono) {
    struct SonidoBancoAudio* sonido;
    if (semitono < instrumento->rango_lo_normal) {
        sonido = &instrumento->sonido_notas_bajo;
    } else if (semitono <= instrumento->rango_hi_normal) {
        sonido = &instrumento->sonido_notas_normal;
    } else {
        sonido = &instrumento->sonido_notas_alto;
    }
    return sonido;
}

struct Instrumento* obtener_interior_instrumento(s32 id_banco, s32 inst_id) {
    struct Instrumento* inst;

    if (ES_BANCO_CARGA_COMPLETO(id_banco) == false) {
        printf_vacio("Audio: voiceman: No bank error %d\n", id_banco);
        banderas_error_audio = id_banco + 0x10000000;
        return NULL;
    }

    if (inst_id >= entradas_ctl[id_banco].instrumentos_num) {
        printf_vacio("Audio: voiceman: progNo. overflow %d,%d\n", inst_id, entradas_ctl[id_banco].instrumentos_num);
        banderas_error_audio = ((id_banco << 8) + inst_id) + 0x3000000;
        return NULL;
    }

    inst = entradas_ctl[id_banco].instrumentos[inst_id];
    if (inst == NULL) {
        printf_vacio("Audio: voiceman: progNo. undefined %d,%d\n", id_banco, inst_id);
        banderas_error_audio = ((id_banco << 8) + inst_id) + 0x1000000;
        return inst;
    }
    return inst;
}

struct Tambor* obtener_tambor(s32 id_banco, s32 id_tambor) {
    struct Tambor* tambor;

    if (ES_BANCO_CARGA_COMPLETO(id_banco) == false) {
        printf_vacio("Audio: voiceman: No bank error %d\n", id_banco);
        banderas_error_audio = id_banco + 0x10000000;
        return NULL;
    }

    if (id_tambor >= entradas_ctl[id_banco].tambores_num) {
        printf_vacio("Audio: voiceman: Percussion Overflow %d,%d\n", id_tambor, entradas_ctl[id_banco].tambores_num);
        banderas_error_audio = ((id_banco << 8) + id_tambor) + 0x4000000;
        return NULL;
    }

#ifdef TARGET_PS2
    /* Aun sin reubicar, el campo es un desplazamiento pequeno */
    if ((uintptr_t) entradas_ctl[id_banco].tambores < 0x00100000U) {
#else
    if ((uintptr_t) entradas_ctl[id_banco].tambores < 0x80000000U) {
#endif
        printf_vacio("Audio: voiceman: Percussion table pointer (bank %d) is irregular.\n");
        return NULL;
    }

    tambor = entradas_ctl[id_banco].tambores[id_tambor];
    if (tambor == NULL) {
        printf_vacio("Audio: voiceman: Percpointer NULL %d,%d\n", id_banco, id_tambor);
        banderas_error_audio = ((id_banco << 8) + id_tambor) + 0x5000000;
    }
    printf_vacio("--4 %x\n", banderas_error_audio);
    printf_vacio("Stoped Voice\n");
    return tambor;
}

void inicializar_nota(struct Nota* nota) {
    if (nota->capa_padre->adsr.tasa_suelta == 0) {
        inicializar_adsr(&nota->adsr, nota->capa_padre->sec_canal->adsr.envelope, &nota->escala_vol_adsr);
    } else {
        inicializar_adsr(&nota->adsr, nota->capa_padre->adsr.envelope, &nota->escala_vol_adsr);
    }
    nota->adsr.state = INICIAL_ESTADO_ADSR;
    nota->eu_sub_nota = sub_nota_predeterminado;
}

void desactivar_nota(struct Nota* nota) {
    if (nota->eu_sub_nota.inicializacion_necesita == true) {
        nota->eu_sub_nota.inicializacion_necesita = false;
    } else {
        fijar_reverb_paneo_vel_nota(nota, 0, 0x40, 0);
    }
    nota->priority = NOTA_PRIORIDAD_DESACTIVADO;
    nota->capa_padre = SIN_CAPA;
    nota->capa_padre_ant = SIN_CAPA;
    nota->eu_sub_nota.activado = false;
    nota->eu_sub_nota.terminado = false;
}

void procesar_notas(void) {
    f32 escalar;
    f32 frecuencia;
    f32 velocidad;
    struct Nota* nota;
    struct EstadoReproduccionNota* estado_reproduccion;
    struct EuSubNota* eu_sub_nota;
    SIN_USO u8 relleno[12];
    u8 reverb_vol;
    SIN_USO u8 relleno3;
    u8 paneo;
    u8 desplazamiento_libro;
    struct AtributosNota* atributos;
    s32 i;

    for (i = 0; i < notas_simultaneo_max; i++) {
        nota = &notas[i];
        estado_reproduccion = (struct EstadoReproduccionNota*) &nota->priority;
        if (nota->capa_padre != SIN_CAPA) {
#ifndef NO_SEGMENTED_MEMORY
#ifdef TARGET_PS2
            /* En el N64 una capa valida esta en KSEG0 (0x80000000+) */
            if ((uintptr_t) estado_reproduccion->capa_padre < 0x00100000U) {
#else
            if ((uintptr_t) estado_reproduccion->capa_padre < 0x7fffffffU) {
#endif
                continue;
            }
#endif

#ifdef VERSION_EU_V10
            printf_vacio("----------------------Double-Error CH: %x %f\n", &nota, nota->capa_padre->sec_canal);
            printf_vacio("----------------------Double-Error NT: %x\n", &nota);
            if (nota != estado_reproduccion->capa_padre->nota && estado_reproduccion->priority != 1) {
                estado_reproduccion->adsr.accion |= SUELTA_ACCION_ADSR;
                estado_reproduccion->adsr.vel_salida_fundido = parametros_buffer_audio.actualizaciones_por_inv_frame;
                estado_reproduccion->priority = 1;
                goto d;
            }
#endif
            if (!estado_reproduccion->capa_padre->activado && estado_reproduccion->priority >= MIN_PRIORIDAD_NOTA) {
                goto c;
            } else if (estado_reproduccion->capa_padre->sec_canal->sec_jugador == NULL) {
                printf_vacio_eu_0("CAUTION:SUB IS SEPARATED FROM GROUP");
                desactivar_canal_secuencia(estado_reproduccion->capa_padre->sec_canal);
                estado_reproduccion->priority = DETENIENDO_PRIORIDAD_NOTA;
                continue;
            } else if (estado_reproduccion->capa_padre->sec_canal->sec_jugador->silenciado) {
                if ((estado_reproduccion->capa_padre->sec_canal->comportamiento_silencio &
                     (SILENCIO_COMPORTAMIENTO_PARADA_GUION | SILENCIO_COMPORTAMIENTO_PARADA_NOTAS))) {
                    goto c;
                }
            }
            goto d;
        c:
            sec_canal_capa_nota_suelta(estado_reproduccion->capa_padre);
            quitar_lista_audio(&nota->item_lista);
            empujar_frente_lista_audio(&nota->item_lista.pool->decayendo, &nota->item_lista);
            estado_reproduccion->priority = DETENIENDO_PRIORIDAD_NOTA;
        } else if (estado_reproduccion->priority >= MIN_PRIORIDAD_NOTA) {
            continue;
        }
    d:
        if (estado_reproduccion->priority != NOTA_PRIORIDAD_DESACTIVADO) {
            eu_sub_nota = &nota->eu_sub_nota;
            if (estado_reproduccion->priority == DETENIENDO_PRIORIDAD_NOTA || eu_sub_nota->terminado) {
                if (estado_reproduccion->adsr.state == ADSR_ESTADO_DESACTIVADO || eu_sub_nota->terminado) {
                    if (estado_reproduccion && estado_reproduccion) {}
                    if (estado_reproduccion->capa_padre_buscado != SIN_CAPA) {
                        desactivar_nota(nota);
                        if (estado_reproduccion->capa_padre_buscado->sec_canal != NULL) {
                            inicializar_para_capa_nota(nota, estado_reproduccion->capa_padre_buscado);
                            inicializar_vibrato_nota(nota);
                            quitar_lista_audio(&nota->item_lista);
                            empujar_atras_lista_audio(&nota->item_lista.pool->active, &nota->item_lista);
                            estado_reproduccion->capa_padre_buscado = SIN_CAPA;
                        } else {
                            printf_vacio_eu_0("Error:Wait Track disappear\n");
                            desactivar_nota(nota);
                            quitar_lista_audio(&nota->item_lista);
                            empujar_atras_lista_audio(&nota->item_lista.pool->desactivado, &nota->item_lista);
                            estado_reproduccion->capa_padre_buscado = SIN_CAPA;
                            goto saltear;
                        }
                    } else {
                        desactivar_nota(nota);
                        quitar_lista_audio(&nota->item_lista);
                        empujar_atras_lista_audio(&nota->item_lista.pool->desactivado, &nota->item_lista);
                        goto saltear;
                    }
                }
            } else if (estado_reproduccion->adsr.state == ADSR_ESTADO_DESACTIVADO) {
                desactivar_nota(nota);
                quitar_lista_audio(&nota->item_lista);
                empujar_atras_lista_audio(&nota->item_lista.pool->desactivado, &nota->item_lista);
                goto saltear;
            }

            escalar = actualizar_adsr(&estado_reproduccion->adsr);
            actualizar_vibrato_nota(nota);
            atributos = &estado_reproduccion->atributos;
            if (estado_reproduccion->priority == DETENIENDO_PRIORIDAD_NOTA) {
                frecuencia = atributos->escala_frec;
                velocidad = atributos->velocidad;
                paneo = atributos->paneo;
                reverb_vol = atributos->reverb_vol;
                if (1) {}
                desplazamiento_libro = eu_sub_nota->desplazamiento_libro;
            } else {
                frecuencia = estado_reproduccion->capa_padre->escala_frec_nota;
                velocidad = estado_reproduccion->capa_padre->velocidad_nota;
                paneo = estado_reproduccion->capa_padre->paneo_nota;
                reverb_vol = estado_reproduccion->capa_padre->sec_canal->reverb_vol;
                desplazamiento_libro = estado_reproduccion->capa_padre->sec_canal->desplazamiento_libro & 0x7;
            }

            frecuencia *= estado_reproduccion->escala_frec_vibrato * estado_reproduccion->escala_frec_portamento;
            velocidad = velocidad * escalar;
            fijar_tasa_remuestreo_nota(nota, frecuencia);
            fijar_reverb_paneo_vel_nota(nota, velocidad, paneo, reverb_vol);
            eu_sub_nota->desplazamiento_libro = desplazamiento_libro;
        saltear:;
        }
    }
}

void sec_canal_capa_decaer_suelta_interno(struct CapaCanalSecuencia* sec_capa, s32 objetivo) {
    struct Nota* nota;
    struct AtributosNota* atributos;

    if ((sec_capa == SIN_CAPA) || (sec_capa->nota == NULL)) {
        return;
    }

    nota = sec_capa->nota;
    atributos = &nota->atributos;

    if (nota->capa_padre_buscado == sec_capa) {
        nota->capa_padre_buscado = SIN_CAPA;
    }

    if (nota->capa_padre != sec_capa) {
        if (nota->capa_padre == SIN_CAPA && nota->capa_padre_buscado == SIN_CAPA && nota->capa_padre_ant == sec_capa &&
            objetivo != DECAER_ESTADO_ADSR) {
            printf_vacio_eu_0("Slow Release Batting\n");
            nota->adsr.vel_salida_fundido = parametros_buffer_audio.actualizaciones_por_inv_frame;
            nota->adsr.accion |= SUELTA_ACCION_ADSR;
        }
    } else {
        sec_capa->status = SONIDO_SITUACION_CARGA_NO_CARGADO;
        if (nota->adsr.state != DECAER_ESTADO_ADSR) {
            atributos->escala_frec = sec_capa->escala_frec_nota;
            atributos->velocidad = sec_capa->velocidad_nota;
            atributos->paneo = sec_capa->paneo_nota;
            if (sec_capa->sec_canal != NULL) {
                atributos->reverb_vol = sec_capa->sec_canal->reverb_vol;
            }
            nota->priority = DETENIENDO_PRIORIDAD_NOTA;
            nota->capa_padre_ant = nota->capa_padre;
            nota->capa_padre = SIN_CAPA;
            if (objetivo == SUELTA_ESTADO_ADSR) {
                nota->adsr.vel_salida_fundido = parametros_buffer_audio.actualizaciones_por_inv_frame;
                nota->adsr.accion |= SUELTA_ACCION_ADSR;
            } else {
                nota->adsr.accion |= DECAER_ACCION_ADSR;
                if (sec_capa->adsr.tasa_suelta == 0) {
                    nota->adsr.vel_salida_fundido =
                        sec_capa->sec_canal->adsr.tasa_suelta * parametros_buffer_audio.actualizaciones_desconocido_por_frame_escalado;
                } else {
                    nota->adsr.vel_salida_fundido =
                        sec_capa->adsr.tasa_suelta * parametros_buffer_audio.actualizaciones_desconocido_por_frame_escalado;
                }
                nota->adsr.sostenido = (CONVERSION_FLOTANTE(sec_capa->sec_canal->adsr.sostenido) * nota->adsr.current) / 256.0f;
            }
        }

        if (objetivo == DECAER_ESTADO_ADSR) {
            quitar_lista_audio(&nota->item_lista);
            empujar_frente_lista_audio(&nota->item_lista.pool->decayendo, &nota->item_lista);
        }
    }
}

void sec_canal_capa_nota_decaer(struct CapaCanalSecuencia* sec_capa) {
    sec_canal_capa_decaer_suelta_interno(sec_capa, DECAER_ESTADO_ADSR);
}

void sec_canal_capa_nota_suelta(struct CapaCanalSecuencia* sec_capa) {
    sec_canal_capa_decaer_suelta_interno(sec_capa, SUELTA_ESTADO_ADSR);
}

const u8 dato_800E98F4[4] = { 0x40, 0x20, 0x10, 0x08 };

s32 construir_ola_sintetico(struct Nota* nota, struct CapaCanalSecuencia* sec_capa, s32 id_ola) {
    f32 escala_frec;
    f32 proporcion;
    u8 indice_cantidad_muestra;

    if (id_ola < 128) {
        printf_vacio("Audio:Wavemem: Bad voiceno (%d)\n", id_ola);
        id_ola = 128;
    }

    escala_frec = sec_capa->escala_frec;
    if (sec_capa->portamento.mode != 0 && 0.0f < sec_capa->portamento.extension) {
        escala_frec *= (sec_capa->portamento.extension + 1.0f);
    }
    if (escala_frec < 1.0f) {
        indice_cantidad_muestra = 0;
        proporcion = 1.0465f;
    } else if (escala_frec < 2.0f) {
        indice_cantidad_muestra = 1;
        proporcion = 0.52325f;
    } else if (escala_frec < 4.0f) {
        indice_cantidad_muestra = 2;
        proporcion = 0.26263f;
    } else {
        indice_cantidad_muestra = 3;
        proporcion = 0.13081f;
    }
    sec_capa->escala_frec *= proporcion;
    nota->id_ola = id_ola;
    nota->indice_cantidad_muestra = indice_cantidad_muestra;

    nota->eu_sub_nota.sonido.muestras = &muestras_ola[id_ola - 128][indice_cantidad_muestra * 64];

    return indice_cantidad_muestra;
}

void inicializar_ola_sintetico(struct Nota* nota, struct CapaCanalSecuencia* sec_capa) {
    s32 indice_cantidad_muestra;
    s32 ola_muestra_cantidad_indice;
    s32 id_ola = sec_capa->inst_o_ola;
    if (id_ola == 0xff) {
        id_ola = sec_capa->sec_canal->inst_o_ola;
    }
    indice_cantidad_muestra = nota->indice_cantidad_muestra;
    ola_muestra_cantidad_indice = construir_ola_sintetico(nota, sec_capa, id_ola);
    nota->estado_sintesis.int_pos_muestra =
        nota->estado_sintesis.int_pos_muestra * dato_800E98F4[ola_muestra_cantidad_indice] / dato_800E98F4[indice_cantidad_muestra];
}

void inicializar_lista_nota(struct ItemListaAudio* lista) {
    lista->prev = lista;
    lista->next = lista;
    lista->u.count = 0;
}

void inicializar_listas_nota(struct PoolNota* pool) {
    inicializar_lista_nota(&pool->desactivado);
    inicializar_lista_nota(&pool->decayendo);
    inicializar_lista_nota(&pool->soltando);
    inicializar_lista_nota(&pool->active);
    pool->desactivado.pool = pool;
    pool->decayendo.pool = pool;
    pool->soltando.pool = pool;
    pool->active.pool = pool;
}

void liberar_lista_nota_inicializacion(void) {
    s32 i;

    inicializar_listas_nota(&listas_libre_nota);
    for (i = 0; i < notas_simultaneo_max; i++) {
        notas[i].item_lista.u.value = &notas[i];
        notas[i].item_lista.prev = NULL;
        empujar_atras_lista_audio(&listas_libre_nota.desactivado, &notas[i].item_lista);
    }
}

void borrar_pool_nota(struct PoolNota* pool) {
    s32 i;
    struct ItemListaAudio* origen;
    struct ItemListaAudio* act;
    struct ItemListaAudio* dest;
    SIN_USO s32 j;

    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                origen = &pool->desactivado;
                dest = &listas_libre_nota.desactivado;
                break;

            case 1:
                origen = &pool->decayendo;
                dest = &listas_libre_nota.decayendo;
                break;

            case 2:
                origen = &pool->soltando;
                dest = &listas_libre_nota.soltando;
                break;

            case 3:
                origen = &pool->active;
                dest = &listas_libre_nota.active;
                break;
        }

        for (;;) {
            act = origen->next;
            if (act == origen) {
                break;
            }
            if (act == NULL) {
                printf_vacio_eu_0("Audio: C-Alloc : Dealloc voice is NULL\n");
                break;
            }
            quitar_lista_audio(act);
            empujar_atras_lista_audio(dest, act);
        }
    }
}

void relleno_pool_nota(struct PoolNota* pool, s32 cantidad) {
    s32 i;
    s32 j;
    struct Nota* nota;
    struct ItemListaAudio* origen;
    struct ItemListaAudio* dest;

    borrar_pool_nota(pool);

    for (i = 0, j = 0; j < cantidad; i++) {
        if (i == 4) {
            printf_vacio_eu_1("Alloc Error:Dim voice-Alloc %d", cantidad);
            return;
        }

        switch (i) {
            case 0:
                origen = &listas_libre_nota.desactivado;
                dest = &pool->desactivado;
                break;

            case 1:
                origen = &listas_libre_nota.decayendo;
                dest = &pool->decayendo;
                break;

            case 2:
                origen = &listas_libre_nota.soltando;
                dest = &pool->soltando;
                break;

            case 3:
                origen = &listas_libre_nota.active;
                dest = &pool->active;
                break;
        }

        while (j < cantidad) {
            nota = sacar_atras_lista_audio(origen);
            if (nota == NULL) {
                break;
            }
            empujar_atras_lista_audio(dest, &nota->item_lista);
            j++;
        }
    }
}

void empujar_frente_lista_audio(struct ItemListaAudio* lista, struct ItemListaAudio* item) {
    if (item->prev != NULL) {
        printf_vacio_eu_0("Error:Same List Add\n");
    } else {
        item->prev = lista;
        item->next = lista->next;
        lista->next->prev = item;
        lista->next = item;
        lista->u.count++;
        item->pool = lista->pool;
    }
}

void quitar_lista_audio(struct ItemListaAudio* item) {
    if (item->prev == NULL) {
        printf_vacio_eu_0("Already Cut\n");
    } else {
        item->prev->next = item->next;
        item->next->prev = item->prev;
        item->prev = NULL;
    }
}

struct Nota* sacar_nodo_con_prio_inferior(struct ItemListaAudio* lista, s32 limite) {
    struct ItemListaAudio* act = lista->next;
    struct ItemListaAudio* mejor;

    if (act == lista) {
        return NULL;
    }

    for (mejor = act; act != lista; act = act->next) {
        if (((struct Nota*) mejor->u.value)->priority >= ((struct Nota*) act->u.value)->priority) {
            mejor = act;
        }
    }

    if (mejor == NULL) {
        return NULL;
    }

    if (limite <= ((struct Nota*) mejor->u.value)->priority) {
        return NULL;
    }

    quitar_lista_audio(mejor);
    return mejor->u.value;
}

void inicializar_para_capa_nota(struct Nota* nota, struct CapaCanalSecuencia* sec_capa) {
    SIN_USO s32 relleno[4];
    s16 inst_id;
    struct EuSubNota* sub = &nota->eu_sub_nota;

    nota->capa_padre_ant = SIN_CAPA;
    nota->capa_padre = sec_capa;
    nota->priority = sec_capa->sec_canal->prioridad_nota;
    sec_capa->nota_propiedades_necesitar_inicializacion = true;
    sec_capa->status = SONIDO_DESCARTABLE_SITUACION_CARGA;
    sec_capa->nota = nota;
    sec_capa->sec_canal->nota_sin_uso = nota;
    sec_capa->sec_canal->capa_sin_uso = sec_capa;
    sec_capa->velocidad_nota = 0.0f;
    inicializar_nota(nota);
    inst_id = sec_capa->inst_o_ola;
    if (inst_id == 0xff) {
        inst_id = sec_capa->sec_canal->inst_o_ola;
    }
    sub->sonido.sonido_banco_audio = sec_capa->sonido;

    if (inst_id >= 0x80) {
        sub->ola_sintetico_es = true;
    } else {
        sub->ola_sintetico_es = false;
    }

    if (sub->ola_sintetico_es) {
        construir_ola_sintetico(nota, sec_capa, inst_id);
    }
    sub->id_banco = sec_capa->sec_canal->id_banco;
    sub->efectos_auriculares_estereo = sec_capa->sec_canal->efectos_auriculares_estereo;
    sub->indice_reverb = sec_capa->sec_canal->indice_reverb & 3;
}

void funcion_800BD8F4(struct Nota* nota, struct CapaCanalSecuencia* sec_capa) {
    sec_canal_capa_nota_suelta(nota->capa_padre);
    nota->capa_padre_buscado = sec_capa;
}

void suelta_nota_y_propiedad_tomar(struct Nota* nota, struct CapaCanalSecuencia* sec_capa) {
    nota->capa_padre_buscado = sec_capa;
    nota->priority = DETENIENDO_PRIORIDAD_NOTA;
    nota->adsr.vel_salida_fundido = parametros_buffer_audio.actualizaciones_por_inv_frame;
    nota->adsr.accion |= SUELTA_ACCION_ADSR;
}

struct Nota* reservar_nota_desde_desactivado(struct PoolNota* pool, struct CapaCanalSecuencia* sec_capa) {
    struct Nota* nota = sacar_atras_lista_audio(&pool->desactivado);
    if (nota != NULL) {
        inicializar_para_capa_nota(nota, sec_capa);
        empujar_frente_lista_audio(&pool->active, &nota->item_lista);
    }
    return nota;
}

struct Nota* reservar_nota_desde_decayendo(struct PoolNota* pool, struct CapaCanalSecuencia* sec_capa) {
    struct Nota* nota = sacar_atras_lista_audio(&pool->decayendo);
    if (nota != NULL) {
        CANTIDAD_PS2(notas_tomadas_apagandose);
        suelta_nota_y_propiedad_tomar(nota, sec_capa);
        empujar_atras_lista_audio(&pool->soltando, &nota->item_lista);
    }
    return nota;
}

struct Nota* reservar_nota_desde_activo(struct PoolNota* pool, struct CapaCanalSecuencia* sec_capa) {
    struct Nota* nota_a;

    nota_a = sacar_nodo_con_prio_inferior(&pool->active, sec_capa->sec_canal->prioridad_nota);

    if (nota_a == NULL) {
        printf_vacio_eu_0("Audio: C-Alloc : lowerPrio is NULL\n");
    } else {
        CANTIDAD_PS2(notas_robadas);
        funcion_800BD8F4(nota_a, sec_capa);
        empujar_atras_lista_audio(&pool->soltando, &nota_a->item_lista);
    }

    return nota_a;
}

struct Nota* reservar_nota(struct CapaCanalSecuencia* sec_capa) {
    struct Nota* devuelto;
    u32 politica = sec_capa->sec_canal->politica_reserva_nota;

    if (politica & CAPA_RESERVA_NOTA) {
        devuelto = sec_capa->nota;
        if (devuelto != NULL && devuelto->capa_padre_ant == sec_capa && devuelto->capa_padre_buscado == SIN_CAPA) {
            suelta_nota_y_propiedad_tomar(devuelto, sec_capa);
            quitar_lista_audio(&devuelto->item_lista);
            empujar_atras_lista_audio(&devuelto->item_lista.pool->soltando, &devuelto->item_lista);
            return devuelto;
        }
    }

    if (politica & CANAL_RESERVA_NOTA) {
        if (!(devuelto = reservar_nota_desde_desactivado(&sec_capa->sec_canal->pool_nota, sec_capa)) &&
            !(devuelto = reservar_nota_desde_decayendo(&sec_capa->sec_canal->pool_nota, sec_capa)) &&
            !(devuelto = reservar_nota_desde_activo(&sec_capa->sec_canal->pool_nota, sec_capa))) {
            printf_vacio_eu_0("Sub Limited Warning: Drop Voice");
            sec_capa->status = SONIDO_SITUACION_CARGA_NO_CARGADO;
            CANTIDAD_PS2(sonidos_sin_nota);
            return NULL;
        }
        return devuelto;
    }

    if (politica & SEC_RESERVA_NOTA) {
        if (!(devuelto = reservar_nota_desde_desactivado(&sec_capa->sec_canal->pool_nota, sec_capa)) &&
            !(devuelto = reservar_nota_desde_desactivado(&sec_capa->sec_canal->sec_jugador->pool_nota, sec_capa)) &&
            !(devuelto = reservar_nota_desde_decayendo(&sec_capa->sec_canal->pool_nota, sec_capa)) &&
            !(devuelto = reservar_nota_desde_decayendo(&sec_capa->sec_canal->sec_jugador->pool_nota, sec_capa)) &&
            !(devuelto = reservar_nota_desde_activo(&sec_capa->sec_canal->pool_nota, sec_capa)) &&
            !(devuelto = reservar_nota_desde_activo(&sec_capa->sec_canal->sec_jugador->pool_nota, sec_capa))) {
            printf_vacio_eu_0("Warning: Drop Voice");
            sec_capa->status = SONIDO_SITUACION_CARGA_NO_CARGADO;
            CANTIDAD_PS2(sonidos_sin_nota);
            return NULL;
        }
        return devuelto;
    }

    if (politica & NOTA_RESERVA_GLOBAL_LISTA_LIBRES) {
        if (!(devuelto = reservar_nota_desde_desactivado(&listas_libre_nota, sec_capa)) &&
            !(devuelto = reservar_nota_desde_decayendo(&listas_libre_nota, sec_capa)) &&
            !(devuelto = reservar_nota_desde_activo(&listas_libre_nota, sec_capa))) {
            printf_vacio_eu_0("Warning: Drop Voice");
            sec_capa->status = SONIDO_SITUACION_CARGA_NO_CARGADO;
            CANTIDAD_PS2(sonidos_sin_nota);
            return NULL;
        }
        return devuelto;
    }

    if (!(devuelto = reservar_nota_desde_desactivado(&sec_capa->sec_canal->pool_nota, sec_capa)) &&
        !(devuelto = reservar_nota_desde_desactivado(&sec_capa->sec_canal->sec_jugador->pool_nota, sec_capa)) &&
        !(devuelto = reservar_nota_desde_desactivado(&listas_libre_nota, sec_capa)) &&
        !(devuelto = reservar_nota_desde_decayendo(&sec_capa->sec_canal->pool_nota, sec_capa)) &&
        !(devuelto = reservar_nota_desde_decayendo(&sec_capa->sec_canal->sec_jugador->pool_nota, sec_capa)) &&
        !(devuelto = reservar_nota_desde_decayendo(&listas_libre_nota, sec_capa)) &&
        !(devuelto = reservar_nota_desde_activo(&sec_capa->sec_canal->pool_nota, sec_capa)) &&
        !(devuelto = reservar_nota_desde_activo(&sec_capa->sec_canal->sec_jugador->pool_nota, sec_capa)) &&
        !(devuelto = reservar_nota_desde_activo(&listas_libre_nota, sec_capa))) {
        printf_vacio_eu_0("Warning: Drop Voice");
        sec_capa->status = SONIDO_SITUACION_CARGA_NO_CARGADO;
        CANTIDAD_PS2(sonidos_sin_nota);
        return NULL;
    }
    return devuelto;
}

void inicializar_all_nota(void) {
    struct Nota* nota;
    s32 i;

    for (i = 0; i < notas_simultaneo_max; i++) {
        nota = &notas[i];
        nota->eu_sub_nota = sub_nota_cero;
        nota->priority = NOTA_PRIORIDAD_DESACTIVADO;
        nota->capa_padre = SIN_CAPA;
        nota->capa_padre_buscado = SIN_CAPA;
        nota->capa_padre_ant = SIN_CAPA;
        nota->id_ola = 0;
        nota->atributos.velocidad = 0.0f;
        nota->escala_vol_adsr = 0;
        nota->adsr.state = ADSR_ESTADO_DESACTIVADO;
        nota->adsr.accion = 0;
        nota->estado_vibrato.active = false;
        nota->portamento.act = 0.0f;
        nota->portamento.speed = 0.0f;
        nota->estado_sintesis.buffers_sintesis = sonido_reserva(&notas_y_pool_buffers, sizeof(struct BuffersSintesisNota));
    }
}
