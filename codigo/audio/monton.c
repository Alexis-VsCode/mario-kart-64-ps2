#include <ultra64.h>
#include <juego/macros.h>

#include "audio/datos.h"
#include "audio/efectos.h"
#include "audio/monton.h"
#include "audio/carga.h"
#include "audio/sintesis.h"
#include "audio/reproduccion.h"
#include "audio/reproductor_secuencias.h"

s16 g_volumen;
s8 reverb_usar;
s8 reverbs_sintesis_num;
struct EuSubNota* eu_subs_nota;

struct SonidoPoolReserva pool_sesion_audio;
struct SonidoPoolReserva pool_inicializacion_audio;
struct SonidoPoolReserva notas_y_pool_buffers;
u8 relleno_monton_audio[0x20];
struct SonidoPoolReserva sec_y_pool_banco;
struct SonidoPoolReserva pool_comun_persistente;
struct SonidoPoolReserva pool_comun_provisorio;

struct SonidoMultiPool sec_pool_cargado;
struct SonidoMultiPool pool_cargado_banco;
struct SonidoMultiPool pool_cargado_sin_uso;

struct PoolDesconocido1 pool_desconocido_1;

struct DividirPool dividir_pool_sesion;
struct DividirPool2 sec_y_dividir_pool_banco;
struct DividirPool persistente_comun_pool_dividir;
struct DividirPool provisorio_comun_pool_dividir;

u8 situacion_carga_desconocido[0x40];
u8 situacion_carga_banco[0x40];
u8 sec_situacion_carga[0x100];

volatile u8 situacion_reinicio_audio;
u8 audio_reinicio_ajuste_id_a_carga;
s32 audio_reinicio_fundido_salida_frames_izquierda;

u8 buffer_sin_uso_audio[0x1000];

struct Nota* notas;

char cadena_audio_monton_00[] = "Warning:Kill Note  %x \n";
char cadena_audio_monton_01[] = "Kill Voice %d (ID %d) %d\n";
char cadena_audio_monton_02[] = "Warning: Running Sequence's data disappear!\n";
char cadena_audio_monton_03[] = "Audio:Memory:Heap OverFlow : Not Allocate %d!\n";
char cadena_audio_monton_04[] = "Audio:Memory:DataHeap Not Allocate \n";
char cadena_audio_monton_05[] = "StayHeap Not Allocate %d\n";
char cadena_audio_monton_06[] = "AutoHeap Not Allocate %d\n";
char cadena_audio_monton_07[] = "Status ID0 : %d  ID1 : %d\n";
char cadena_audio_monton_08[] = "id 0 is Stopping\n";
char cadena_audio_monton_09[] = "id 0 is Stop\n";
char cadena_audio_monton_10[] = "id 1 is Stopping\n";
char cadena_audio_monton_11[] = "id 1 is Stop\n";
char cadena_audio_monton_12[] = "WARNING: NO FREE AUTOSEQ AREA.\n";
char cadena_audio_monton_13[] = "WARNING: NO STOP AUTO AREA.\n";
char cadena_audio_monton_14[] = "         AND TRY FORCE TO STOP SIDE \n";
char cadena_audio_monton_15[] = "Check ID0  (seq ID %d) Useing ...\n";
char cadena_audio_monton_16[] = "Check ID1  (seq ID %d) Useing ...\n";
char cadena_audio_monton_17[] = "No Free Seq area.\n";
char cadena_audio_monton_18[] = "CH %d: ID %d\n";
char cadena_audio_monton_19[] = "TWO SIDES ARE LOADING... ALLOC CANCELED.\n";
char cadena_audio_monton_20[] = "WARNING: Before Area Overlaid After.";
char cadena_audio_monton_21[] = "WARNING: After Area Overlaid Before.";
char cadena_audio_monton_22[] = "MEMORY:SzHeapAlloc ERROR: sza->side %d\n";
char cadena_audio_monton_23[] = "Audio:MEMORY:SzHeap Overflow error. (%d bytes)\n";
char cadena_audio_monton_24[] = "Auto Heap Unhit for ID %d\n";
char cadena_audio_monton_25[] = "Heap Reconstruct Start %x\n";
char cadena_audio_monton_26[] = "AHPBASE %x\n";
char cadena_audio_monton_27[] = "AHPCUR  %x\n";
char cadena_audio_monton_28[] = "HeapTop %x\n";
char cadena_audio_monton_29[] = "SynoutRate %d / %d \n";
char cadena_audio_monton_30[] = "FXSIZE %d\n";
char cadena_audio_monton_31[] = "FXCOMP %d\n";
char cadena_audio_monton_32[] = "FXDOWN %d\n";
char cadena_audio_monton_33[] = "WaveCacheLen: %d\n";
char cadena_audio_monton_34[] = "SpecChange Finished\n";
char cadena_audio_monton_35[] = "Fbank Seq %x\n";
char cadena_audio_monton_36[] = "Already Load Type %d,ID %d\n";
char cadena_audio_monton_37[] = "Warning:Emem Over,not alloc %d\n";
char cadena_audio_monton_38[] = "Write %d\n";

extern u8 situacion_carga_desconocido[];

void cargar_situacion_banco_reinicio_y_sec(void) {
    s32 i;
    for (i = 0; i < 64; i++) {
        if (situacion_carga_banco[i] != 5) {
            situacion_carga_banco[i] = 0;
        }
    }

    for (i = 0; i < 64; i++) {
        if (situacion_carga_desconocido[i] != 5) {
            situacion_carga_desconocido[i] = 0;
        }
    }

    for (i = 0; i < 256; i++) {
        if (sec_situacion_carga[i] != 5) {
            sec_situacion_carga[i] = 0;
        }
    }
}

void descartar_banco(s32 id_banco) {
    s32 i;

    for (i = 0; i < notas_simultaneo_max; i++) {
        struct Nota* nota = &notas[i];

        if (nota->eu_sub_nota.id_banco == id_banco) {
            if (nota->priority >= MIN_PRIORIDAD_NOTA) {
                nota->capa_padre->activado = false;
                nota->capa_padre->terminado = true;
            }
            desactivar_nota(nota);
            quitar_lista_audio(&nota->item_lista);
            empujar_atras_lista_audio(&listas_libre_nota.desactivado, &nota->item_lista);
        }
    }
}

void descartar_secuencia(s32 sec_id) {
    s32 i;

    for (i = 0; i < JUGADORES_SECUENCIA; i++) {
        if (jugadores_secuencia[i].activado && jugadores_secuencia[i].sec_id == sec_id) {
            desactivar_jugador_secuencia(&jugadores_secuencia[i]);
        }
    }
}

void* sonido_reserva(struct SonidoPoolReserva* pool, u32 size) {
    u8* empezar;
    u8* pos;
    u32 tamanio_alineado = ALIGN16(size);

    empezar = pool->act;
    if (empezar + tamanio_alineado <= pool->start + pool->size) {
        pool->act += tamanio_alineado;
        for (pos = empezar; pos < pool->act; pos++) {
            *pos = 0;
        }
    } else {
        return NULL;
    }
    pool->entradas_reservado_num++;
    return empezar;
}

void sonido_inicializacion_pool_reserva(struct SonidoPoolReserva* pool, void* direccion_mem, u32 size) {
    pool->act = pool->start = (u8*) ALIGN16((uintptr_t) direccion_mem);
    pool->size = size;
    pool->entradas_reservado_num = 0;
}

void borrar_pool_persistente(struct PoolPersistente* persistente) {
    persistente->pool.entradas_reservado_num = 0;
    persistente->pool.act = persistente->pool.start;
    persistente->entradas_num = 0;
}

void borrar_pool_provisorio(struct PoolProvisorio* provisorio) {
    provisorio->pool.entradas_reservado_num = 0;
    provisorio->pool.act = provisorio->pool.start;
    provisorio->lado_siguiente = 0;
    provisorio->entradas[0].ptr = provisorio->pool.start;
    provisorio->entradas[1].ptr = provisorio->pool.start + provisorio->pool.size;
    provisorio->entradas[0].id = -1;
    provisorio->entradas[1].id = -1;
}

void funcion_800B90E0(struct SonidoPoolReserva* pool) {
    pool->entradas_reservado_num = 0;
    pool->act = pool->start;
}

void sonido_pools_principal_inicializacion(s32 parametro0) {
    sonido_inicializacion_pool_reserva(&pool_inicializacion_audio, &monton_audio, parametro0);
    sonido_inicializacion_pool_reserva(&pool_sesion_audio, monton_audio + parametro0, tamanio_monton_audio - parametro0);
}

void funcion_800B914C(struct DividirPool* parametro0) {
    pool_sesion_audio.act = pool_sesion_audio.start;
    sonido_inicializacion_pool_reserva(&notas_y_pool_buffers, sonido_reserva(&pool_sesion_audio, parametro0->sec_querer), parametro0->sec_querer);
    sonido_inicializacion_pool_reserva(&sec_y_pool_banco, sonido_reserva(&pool_sesion_audio, parametro0->personalizado_querer), parametro0->personalizado_querer);
}

void sec_y_inicializacion_pool_banco(struct DividirPool2* a) {
    sec_y_pool_banco.act = sec_y_pool_banco.start;
    sonido_inicializacion_pool_reserva(&pool_comun_persistente, sonido_reserva(&sec_y_pool_banco, a->persistente_querer), a->persistente_querer);
    sonido_inicializacion_pool_reserva(&pool_comun_provisorio, sonido_reserva(&sec_y_pool_banco, a->provisorio_querer), a->provisorio_querer);
}

void inicializar_pools_persistente(struct DividirPool* a) {
    pool_comun_persistente.act = pool_comun_persistente.start;
    sonido_inicializacion_pool_reserva(&sec_pool_cargado.persistente.pool, sonido_reserva(&pool_comun_persistente, a->sec_querer), a->sec_querer);
    sonido_inicializacion_pool_reserva(&pool_cargado_banco.persistente.pool, sonido_reserva(&pool_comun_persistente, a->banco_querer),
                          a->banco_querer);
    sonido_inicializacion_pool_reserva(&pool_cargado_sin_uso.persistente.pool, sonido_reserva(&pool_comun_persistente, a->querer_sin_uso),
                          a->querer_sin_uso);
    borrar_pool_persistente(&sec_pool_cargado.persistente);
    borrar_pool_persistente(&pool_cargado_banco.persistente);
    borrar_pool_persistente(&pool_cargado_sin_uso.persistente);
}

void inicializar_pools_provisorio(struct DividirPool* a) {
    pool_comun_provisorio.act = pool_comun_provisorio.start;
    sonido_inicializacion_pool_reserva(&sec_pool_cargado.provisorio.pool, sonido_reserva(&pool_comun_provisorio, a->sec_querer), a->sec_querer);
    sonido_inicializacion_pool_reserva(&pool_cargado_banco.provisorio.pool, sonido_reserva(&pool_comun_provisorio, a->banco_querer), a->banco_querer);
    sonido_inicializacion_pool_reserva(&pool_cargado_sin_uso.provisorio.pool, sonido_reserva(&pool_comun_provisorio, a->querer_sin_uso),
                          a->querer_sin_uso);
    borrar_pool_provisorio(&sec_pool_cargado.provisorio);
    borrar_pool_provisorio(&pool_cargado_banco.provisorio);
    borrar_pool_provisorio(&pool_cargado_sin_uso.provisorio);
}

void* reservar_banco_o_sec(struct SonidoMultiPool* parametro0, s32 parametro1, s32 size, s32 parametro3, s32 id) {
    struct PoolProvisorio* tp;
    struct SonidoPoolReserva* pool;
    void* devuelto;
    u16 SIN_USO _primer_val;
    u16 SIN_USO _segundo_val;
    u16 primer_val;
    u16 segundo_val;
    s32 variable_v1_2;
    u8* tabla;
    u8 es_sonido;

    if (parametro3 == 0) {
        tp = &parametro0->provisorio;
        if (parametro0 == &sec_pool_cargado) {
            tabla = sec_situacion_carga; es_sonido = 0;
        } else {
            primer_val += 0;
            if (parametro0 == &pool_cargado_banco) {
                es_sonido = 1; tabla = situacion_carga_banco;
            } else if (parametro0 == &pool_cargado_sin_uso) {
                tabla = situacion_carga_desconocido; es_sonido = 2;
            }
        }
        if (tp->entradas[0].id == -1) {
            primer_val = 0;
        } else {
            primer_val = tabla[tp->entradas[0].id];
        }
        if (tp->entradas[1].id == -1) {
            segundo_val = 0;
        } else {
            segundo_val = tabla[tp->entradas[1].id];
        }
        if (es_sonido == 1) {
            if (primer_val == 4) {
                for (variable_v1_2 = 0; variable_v1_2 < notas_simultaneo_max; variable_v1_2++) {
                    if (notas[variable_v1_2].eu_sub_nota.id_banco == tp->entradas[0].id && notas[variable_v1_2].eu_sub_nota.activado) {
                        break;
                    }
                }
                if (variable_v1_2 == notas_simultaneo_max) {
                    if (situacion_carga_banco[tp->entradas[0].id] != SONIDO_SITUACION_CARGA_5) {
                        situacion_carga_banco[tp->entradas[0].id] = SONIDO_DESCARTABLE_SITUACION_CARGA;
                    }
                    primer_val = SONIDO_DESCARTABLE_SITUACION_CARGA;
                }
            }
            if (segundo_val == 4) {
                for (variable_v1_2 = 0; variable_v1_2 < notas_simultaneo_max; variable_v1_2++) {
                    if (notas[variable_v1_2].eu_sub_nota.id_banco == tp->entradas[1].id && notas[variable_v1_2].eu_sub_nota.activado) {
                        break;
                    }
                }
                if (variable_v1_2 == notas_simultaneo_max) {
                    if (situacion_carga_banco[tp->entradas[1].id] != SONIDO_SITUACION_CARGA_5) {
                        situacion_carga_banco[tp->entradas[1].id] = SONIDO_DESCARTABLE_SITUACION_CARGA;
                    }
                    segundo_val = SONIDO_DESCARTABLE_SITUACION_CARGA;
                }
            }
        }
        if (primer_val == 0) {
            tp->lado_siguiente = 0;
        } else if (segundo_val == 0) {
            tp->lado_siguiente = 1;
        } else {
            if ((primer_val == 3) && (segundo_val == 3)) {
            } else if (primer_val == 3) {
                tp->lado_siguiente = 0;
            } else if (segundo_val == 3) {
                tp->lado_siguiente = 1;
            } else {
                if (es_sonido == 0) {
                    if (primer_val == SONIDO_COMPLETO_SITUACION_CARGA) {
                        for (variable_v1_2 = 0; variable_v1_2 < JUGADORES_SECUENCIA; variable_v1_2++) {
                            if (jugadores_secuencia[variable_v1_2].activado &&
                                jugadores_secuencia[variable_v1_2].sec_id == tp->entradas[0].id) {
                                break;
                            }
                        }
                        if (variable_v1_2 == JUGADORES_SECUENCIA) {
                            tp->lado_siguiente = 0;
                            goto salida;
                        }
                    }
                    if (segundo_val == SONIDO_COMPLETO_SITUACION_CARGA) {
                        for (variable_v1_2 = 0; variable_v1_2 < JUGADORES_SECUENCIA; variable_v1_2++) {
                            if (jugadores_secuencia[variable_v1_2].activado &&
                                jugadores_secuencia[variable_v1_2].sec_id == tp->entradas[1].id) {
                                break;
                            }
                        }
                        if (variable_v1_2 == JUGADORES_SECUENCIA) {
                            tp->lado_siguiente = 1;
                            goto salida;
                        }
                    }
                } else if (es_sonido == 1) {
                    if (primer_val == SONIDO_COMPLETO_SITUACION_CARGA) {
                        for (variable_v1_2 = 0; variable_v1_2 < notas_simultaneo_max; variable_v1_2++) {
                            if (notas[variable_v1_2].eu_sub_nota.id_banco == tp->entradas[0].id &&
                                notas[variable_v1_2].eu_sub_nota.activado) {
                                break;
                            }
                        }
                        if (variable_v1_2 == notas_simultaneo_max) {
                            tp->lado_siguiente = 0;
                            goto salida;
                        }
                    }
                    if (segundo_val == SONIDO_COMPLETO_SITUACION_CARGA) {
                        for (variable_v1_2 = 0; variable_v1_2 < notas_simultaneo_max; variable_v1_2++) {
                            if (notas[variable_v1_2].eu_sub_nota.id_banco == tp->entradas[1].id &&
                                notas[variable_v1_2].eu_sub_nota.activado) {
                                break;
                            }
                        }
                        if (variable_v1_2 == notas_simultaneo_max) {
                            tp->lado_siguiente = 1;
                            goto salida;
                        }
                    }
                }
                if (tp->lado_siguiente == 0) {
                    if (primer_val == SONIDO_SITUACION_CARGA_EN_PROGRESO) {
                        if (segundo_val != SONIDO_SITUACION_CARGA_EN_PROGRESO) {
                            tp->lado_siguiente = 1;
                            goto salida;
                        }
                    } else {
                        goto salida;
                    }
                } else {
                    if (segundo_val == SONIDO_SITUACION_CARGA_EN_PROGRESO) {
                        if (primer_val != SONIDO_SITUACION_CARGA_EN_PROGRESO) {
                            tp->lado_siguiente = 0;
                            goto salida;
                        }
                    } else {
                        goto salida;
                    }
                }
                return NULL;
            salida:;
            }
        }

        pool = &parametro0->provisorio.pool;
        if (tp->entradas[tp->lado_siguiente].id != (s8) -1) {
            tabla[tp->entradas[tp->lado_siguiente].id] = SONIDO_SITUACION_CARGA_NO_CARGADO;
            if (es_sonido == true) {
                descartar_banco(tp->entradas[tp->lado_siguiente].id);
            }
        }
        switch (tp->lado_siguiente) {
            case 0:
                tp->entradas[0].ptr = pool->start;
                tp->entradas[0].id = (s16) id;
                tp->entradas[0].size = (u32) size;
                pool->act = pool->start + size;
                if (tp->entradas[1].ptr < pool->act) {
                    tabla[tp->entradas[1].id] = 0;
                    switch (es_sonido) { /* irregular */
                        case 0:
                            descartar_secuencia((s32) tp->entradas[1].id);
                            break;
                        case 1:
                            descartar_banco((s32) tp->entradas[1].id);
                            break;
                    }
                    tp->entradas[1].id = -1;
                    tp->entradas[1].ptr = pool->start + pool->size;
                }
                devuelto = tp->entradas[0].ptr;
                break;
            case 1:
                tp->entradas[1].ptr = pool->start + pool->size - size - 0x10;
                tp->entradas[1].id = (s16) id;
                tp->entradas[1].size = (u32) size;
                if ((u32) tp->entradas[1].ptr < (u32) pool->act) {
                    tabla[tp->entradas[0].id] = 0;
                    switch (es_sonido) {
                        case 0:
                            descartar_secuencia((s32) tp->entradas[0].id);
                            break;
                        case 1:
                            descartar_banco((s32) tp->entradas[0].id);
                            break;
                    }
                    tp->entradas[0].id = -1;
                    pool->act = pool->start;
                }
                devuelto = tp->entradas[1].ptr;
                break;
            default:
                return NULL;
        }
        tp->lado_siguiente ^= 1;
        return devuelto;
    }
    devuelto = sonido_reserva(&parametro0->persistente.pool, parametro1 * size);
    parametro0->persistente.entradas[parametro0->persistente.entradas_num].ptr = devuelto;
    if (devuelto == NULL) {
        switch (parametro3) {
            case 2:
                return reservar_banco_o_sec(parametro0, parametro1, size, 0, id);
            case 1:
            case 0:
                return NULL;
        }
    }
    parametro0->persistente.entradas[parametro0->persistente.entradas_num].id = (s16) id;
    parametro0->persistente.entradas[parametro0->persistente.entradas_num].size = (u32) size;
    return parametro0->persistente.entradas[parametro0->persistente.entradas_num++].ptr;
}

void* obtener_banco_o_sec(s32 pool_idx, s32 parametro1, s32 id) {
    void* devuelto;

    devuelto = busqueda_pool1_desconocido(pool_idx, id);
    if (devuelto != NULL) {
        return devuelto;
    }
    return obtener_banco_o_interior_sec(pool_idx, parametro1, id);
}

void* obtener_banco_o_interior_sec(s32 pool_idx, s32 parametro1, s32 id_banco) {
    u32 i;
    struct SonidoMultiPool* pool_cargado;
    struct PoolProvisorio* provisorio;
    struct PoolPersistente* persistente;

    switch (pool_idx) {
        case 0:
            pool_cargado = &sec_pool_cargado;
            break;
        case 1:
            pool_cargado = &pool_cargado_banco;
            break;
        case 2:
            pool_cargado = &pool_cargado_sin_uso;
            break;
    }

    provisorio = &pool_cargado->provisorio;
    if (parametro1 == 0) {
        if (provisorio->entradas[0].id == id_banco) {
            provisorio->lado_siguiente = 1;
            return provisorio->entradas[0].ptr;
        } else if (provisorio->entradas[1].id == id_banco) {
            provisorio->lado_siguiente = 0;
            return provisorio->entradas[1].ptr;
        } else {
            return NULL;
        }
    }

    persistente = &pool_cargado->persistente;
    for (i = 0; i < persistente->entradas_num; i++) {
        if (persistente->entradas[i].id == id_banco) {
            return persistente->entradas[i].ptr;
        }
    }

    if (parametro1 == 2) {
        return obtener_banco_o_sec(pool_idx, 0, id_banco);
    }
    return NULL;
}

void funcion_800B9BE4(f32 parametro0, f32 parametro1, u16* parametro2) {
    s32 i;
    f32 tmp[16];

    tmp[0] = parametro1 * 262159.0f;
    tmp[8] = parametro0 * 262159.0f;
    tmp[1] = (parametro1 * parametro0) * 262159.0f;
    tmp[9] = ((parametro0 * parametro0) + parametro1) * 262159.0f;

    for (i = 2; i < 8; i++) {
        parametro2[i] = parametro1 * tmp[i - 2] + parametro0 * tmp[i - 1];
        parametro2[8 + i] = parametro1 * tmp[6 + i] + parametro0 * tmp[7 + i];
    }

    for (i = 0; i < 16; i++) {
        parametro2[i] = tmp[i];
    }
}

void disminuir_ganancia_reverb(void) {
    s32 i;
    for (i = 0; i < reverbs_sintesis_num; i++) {
        reverbs_sintesis[i].ganancia_reverb -= reverbs_sintesis[i].ganancia_reverb / 4;
    }
}

s32 reiniciar_paso_abajo_cerrar_audio_y(void) {
    s32 i;
    s32 j;

    switch (situacion_reinicio_audio) {
        case 5:
            for (i = 0; i < JUGADORES_SECUENCIA; i++) {
                desactivar_jugador_secuencia(&jugadores_secuencia[i]);
            }
            audio_reinicio_fundido_salida_frames_izquierda = 4;
            situacion_reinicio_audio--;
            break;
        case 4:
            if (audio_reinicio_fundido_salida_frames_izquierda != 0) {
                audio_reinicio_fundido_salida_frames_izquierda--;
                disminuir_ganancia_reverb();
            } else {
                for (i = 0; i < notas_simultaneo_max; i++) {
                    if (notas[i].eu_sub_nota.activado && notas[i].adsr.state != ADSR_ESTADO_DESACTIVADO) {
                        notas[i].adsr.vel_salida_fundido = parametros_buffer_audio.actualizaciones_por_inv_frame;
                        notas[i].adsr.accion |= SUELTA_ACCION_ADSR;
                    }
                }
                audio_reinicio_fundido_salida_frames_izquierda = 0x00000010;
                situacion_reinicio_audio--;
            }
            break;
        case 3:
            if (audio_reinicio_fundido_salida_frames_izquierda != 0) {
                audio_reinicio_fundido_salida_frames_izquierda--;
                disminuir_ganancia_reverb();
            } else {
                for (i = 0; i < NUMAIBUFFERS; i++) {
                    for (j = 0; j < (s32) (LARGO_AIBUFFER / sizeof(s16)); j++) {
                        ai_buffers[i][j] = 0;
                    }
                }
                audio_reinicio_fundido_salida_frames_izquierda = 4;
                situacion_reinicio_audio--;
            }
            break;
        case 2:
            if (audio_reinicio_fundido_salida_frames_izquierda != 0) {
                audio_reinicio_fundido_salida_frames_izquierda--;
            } else {
                situacion_reinicio_audio--;
            }
            break;
        case 1:
            reiniciar_sesion_audio();
            situacion_reinicio_audio = 0;
            break;
    }
    if (situacion_reinicio_audio < 3) {
        return 0;
    }
    return 1;
}

void reiniciar_sesion_audio(void) {
    s32 variable_s1;
    s32 variable_s5;
    s32 temporal_;
    u32 total_mem;
    u32 mem_provisorio;
    u32 mem_persistente;
    s16* mem;
    struct ReverbSintesis* reverb;
    struct EUAjustesReverb* reverb_ajustes;
    struct AudioSesionAjustesEU* temporal_s6 = &ajustes_sesion_audio[audio_reinicio_ajuste_id_a_carga];

    muestra_dma_num_lista_items = 0;
    parametros_buffer_audio.frecuencia = temporal_s6->frecuencia;
    parametros_buffer_audio.frecuencia_ai = osAiSetFrequency(parametros_buffer_audio.frecuencia);
    parametros_buffer_audio.muestras_por_objetivo_frame = ALIGN16(parametros_buffer_audio.frecuencia / tasa_refrescar);
    parametros_buffer_audio.min_ai_buffer_longitud = parametros_buffer_audio.muestras_por_objetivo_frame - 0x10;
    parametros_buffer_audio.max_ai_buffer_longitud = parametros_buffer_audio.muestras_por_objetivo_frame + 0x10;
    parametros_buffer_audio.actualizaciones_por_frame = ((parametros_buffer_audio.muestras_por_objetivo_frame + 0x10) / 192) + 1;
    parametros_buffer_audio.muestras_por_actualizacion =
        (parametros_buffer_audio.muestras_por_objetivo_frame / parametros_buffer_audio.actualizaciones_por_frame) & ~0x0007;
    parametros_buffer_audio.muestras_por_max_actualizacion = parametros_buffer_audio.muestras_por_actualizacion + 8;
    parametros_buffer_audio.muestras_por_min_actualizacion = parametros_buffer_audio.muestras_por_actualizacion - 8;
    parametros_buffer_audio.tasa_remuestreo = 32000.0f / ((f32) (s32) parametros_buffer_audio.frecuencia);
    parametros_buffer_audio.actualizaciones_desconocido_por_frame_escalado = 0.001171875f / parametros_buffer_audio.actualizaciones_por_frame;
    parametros_buffer_audio.actualizaciones_por_inv_frame = 1.0f / parametros_buffer_audio.actualizaciones_por_frame;
    notas_simultaneo_max = temporal_s6->notas_simultaneo_max;
    g_volumen = temporal_s6->volumen;
    interno_tempo_a_externo =
        (u32) (((parametros_buffer_audio.actualizaciones_por_frame * 2880000.0f) / tatums_por_pulso) / dato_803B7178);
    parametros_buffer_audio.desconocido_ajuste_4 = temporal_s6->desconocido1;
    parametros_buffer_audio.muestras_por_objetivo_frame *= parametros_buffer_audio.desconocido_ajuste_4;
    parametros_buffer_audio.max_ai_buffer_longitud *= parametros_buffer_audio.desconocido_ajuste_4;
    parametros_buffer_audio.min_ai_buffer_longitud *= parametros_buffer_audio.desconocido_ajuste_4;
    parametros_buffer_audio.actualizaciones_por_frame *= parametros_buffer_audio.desconocido_ajuste_4;
    ordenes_audio_max =
        (notas_simultaneo_max * 0x14 * parametros_buffer_audio.actualizaciones_por_frame) + (temporal_s6->num_reverbs * 0x20) + 0x1E0;
    mem_persistente = temporal_s6->mem_sec_persistente + temporal_s6->mem_banco_persistente + temporal_s6->desconocido_18;
    mem_provisorio = temporal_s6->mem_sec_provisorio + temporal_s6->mem_banco_provisorio + temporal_s6->desconocido_24;
    total_mem = mem_persistente + mem_provisorio;
    temporal_ = (pool_sesion_audio.size - total_mem) - 0x100;
    dividir_pool_sesion.sec_querer = temporal_;
    dividir_pool_sesion.personalizado_querer = total_mem;
    funcion_800B914C(&dividir_pool_sesion);
    sec_y_dividir_pool_banco.persistente_querer = mem_persistente;
    sec_y_dividir_pool_banco.provisorio_querer = mem_provisorio;
    sec_y_inicializacion_pool_banco(&sec_y_dividir_pool_banco);
    persistente_comun_pool_dividir.sec_querer = temporal_s6->mem_sec_persistente;
    persistente_comun_pool_dividir.banco_querer = temporal_s6->mem_banco_persistente;
    persistente_comun_pool_dividir.querer_sin_uso = temporal_s6->desconocido_18;
    inicializar_pools_persistente(&persistente_comun_pool_dividir);
    provisorio_comun_pool_dividir.sec_querer = temporal_s6->mem_sec_provisorio;
    provisorio_comun_pool_dividir.banco_querer = temporal_s6->mem_banco_provisorio;
    provisorio_comun_pool_dividir.querer_sin_uso = temporal_s6->desconocido_24;
    inicializar_pools_provisorio(&provisorio_comun_pool_dividir);
    cargar_situacion_banco_reinicio_y_sec();
    notas = sonido_reserva(&notas_y_pool_buffers, notas_simultaneo_max * sizeof(struct Nota));
    inicializar_all_nota();
    liberar_lista_nota_inicializacion();
    eu_subs_nota =
        sonido_reserva(&notas_y_pool_buffers, parametros_buffer_audio.actualizaciones_por_frame * notas_simultaneo_max * 0x10);
    for (variable_s5 = 0; variable_s5 != 2; variable_s5++) {
        audio_cmd_buffers[variable_s5] = sonido_reserva(&notas_y_pool_buffers, ordenes_audio_max * sizeof(u64));
    }
    for (variable_s5 = 0; variable_s5 < 4; variable_s5++) {
        reverbs_sintesis[variable_s5].reverb_usar = 0;
    }
    reverbs_sintesis_num = temporal_s6->num_reverbs;
    for (variable_s5 = 0; variable_s5 < reverbs_sintesis_num; variable_s5++) {
        reverb = &reverbs_sintesis[variable_s5];
        reverb_ajustes = &temporal_s6->ajustes_reverb[variable_s5];
        reverb->tamanio_ventana = reverb_ajustes->tamanio_ventana * 64;
        reverb->tasa_submuestreo = reverb_ajustes->tasa_submuestreo;
        reverb->ganancia_reverb = reverb_ajustes->gain;
        reverb->reverb_usar = 8;
        reverb->buffer_anillo.izquierda = sonido_reserva(&notas_y_pool_buffers, reverb->tamanio_ventana * 2);
        reverb->buffer_anillo.derecha = sonido_reserva(&notas_y_pool_buffers, reverb->tamanio_ventana * 2);
        reverb->siguiente_anillo_buffer_pos = 0;
        reverb->desconocido_c = 0;
        reverb->frame_act = 0;
        reverb->tamanio_buf_por_canal = reverb->tamanio_ventana;
        reverb->izquierda_frames_a_ignorar = 2;
        if (reverb->tasa_submuestreo != 1) {
            reverb->banderas_remuestreo = 1;
            reverb->tasa_remuestreo = 0x8000 / reverb->tasa_submuestreo;
            reverb->izquierda_estado_remuestreo = sonido_reserva(&notas_y_pool_buffers, 0x00000020U);
            reverb->derecha_estado_remuestreo = sonido_reserva(&notas_y_pool_buffers, 0x00000020U);
            reverb->unk24 = sonido_reserva(&notas_y_pool_buffers, 0x00000020U);
            reverb->unk28 = sonido_reserva(&notas_y_pool_buffers, 0x00000020U);
            for (variable_s1 = 0; variable_s1 < parametros_buffer_audio.actualizaciones_por_frame; variable_s1++) {
                mem = sonido_reserva(&notas_y_pool_buffers, 0x00000300U);
                reverb->items[0][variable_s1].a_izquierda_submuestreo = mem;
                reverb->items[0][variable_s1].a_derecha_submuestreo = mem + (LARGO_PREDETERMINADO_1CH / sizeof(s16));
                mem = sonido_reserva(&notas_y_pool_buffers, 0x00000300U);
                reverb->items[1][variable_s1].a_izquierda_submuestreo = mem;
                reverb->items[1][variable_s1].a_derecha_submuestreo = mem + (LARGO_PREDETERMINADO_1CH / sizeof(s16));
            }
        }
    }
    funcion_800BB030(notas_simultaneo_max);
    osWritebackDCacheAll();
}

void* busqueda_pool1_desconocido(s32 pool_idx, s32 id) {
    s32 i;

    for (i = 0; i < pool_desconocido_1.pool.entradas_reservado_num; i++) {
        if (pool_desconocido_1.entradas[i].indice_pool == pool_idx && pool_desconocido_1.entradas[i].id == id) {
            return pool_desconocido_1.entradas[i].ptr;
        }
    }
    return NULL;
}

void funcion_800BA8B0(s32 pool_idx, s32 id) {
    ALSeqFile* sp3_c;
    s32 temporal_a2;
    u32 temporal_a1;
    u8* variable_a3;
    SIN_USO u8* temporal_v0;
    SIN_USO s32 relleno;

    switch (pool_idx) { /* irregular */
        case 0:
            sp3_c = sec_cabecera_archivo;
            break;
        case 1:
            sp3_c = cabecera_ctl_al;
            break;
        case 2:
            sp3_c = tabla_al;
            break;
    }
    if (sp3_c->seqArray[id].len == 0) {
        id = (s32) sp3_c->seqArray[id].offset;
    }
    if (busqueda_pool1_desconocido(pool_idx, id) == NULL) {
        temporal_a2 = pool_desconocido_1.pool.entradas_reservado_num;
        temporal_a1 = sp3_c->seqArray[id].len;
        variable_a3 = sp3_c->seqArray[id].offset;
        if (pool_idx == 1) {
            variable_a3 += 0x10;
        }
        pool_desconocido_1.entradas[temporal_a2].ptr = sonido_reserva(&pool_desconocido_1.pool, temporal_a1);
        if (pool_desconocido_1.entradas[temporal_a2].ptr != NULL) {
            copiar_inmediato_dma_audio(variable_a3, pool_desconocido_1.entradas[temporal_a2].ptr, temporal_a1);
            pool_desconocido_1.entradas[temporal_a2].indice_pool = pool_idx;
            pool_desconocido_1.entradas[temporal_a2].id = id;
            pool_desconocido_1.entradas[temporal_a2].size = temporal_a1;
            switch (pool_idx) {
                case 0:
                    if (sec_situacion_carga[id] != 5) {
                        sec_situacion_carga[id] = 5;
                    }
                    break;
                case 1:
                    entradas_ctl[id].instrumentos = (struct Instrumento**) (pool_desconocido_1.entradas[temporal_a2].ptr + 4);
                    funcion_800BB584(id);
                    if (situacion_carga_banco[id] != 5) {
                        situacion_carga_banco[id] = 5;
                    }
                    break;
                case 2:
                    break;
            }
        }
    }
}
