#include <ultra64.h>
#include <juego/macros.h>

#include "audio/carga.h"
#include "audio/datos.h"
#include "audio/monton.h"
#include "audio/interno.h"
#include "audio/reproduccion.h"
#include "audio/sintesis.h"
#include "audio/reproductor_secuencias.h"
#include "audio/puerto_eu.h"
#include "memoria/buffer_salida_graficos.h"

#define ALIGN16(val) (((val) + 0xF) & ~0xF)

struct JugadorSecuencia jugadores_secuencia[JUGADORES_SECUENCIA];
struct CanalSecuencia canales_secuencia[CANALES_SECUENCIA];
struct CapaCanalSecuencia capas_secuencia[CAPAS_SECUENCIA];
struct CanalSecuencia ninguno_canal_secuencia;
struct ItemListaAudio lista_libre_capa;
struct PoolNota listas_libre_nota;
OSMesgQueue act_audio_frame_dma_cola;
OSMesg act_audio_frame_dma_msj_bufs[AUDIO_FRAME_DMA_COLA_TAMANIO];
OSIoMesg act_audio_frame_dma_io_msj_bufs[AUDIO_FRAME_DMA_COLA_TAMANIO];
OSMesgQueue dato_803B6720;
OSMesg dato_803B6738;

OSIoMesg dato_803B6740;
struct DmaCompartido dmas_muestra[0x70];
u32 muestra_dma_num_lista_items;
u32 muestra_dma_lista_tamanio_1;
s32 dato_803B6E60;
s32 cargar_relleno_bss;

u8 muestra_dma_reutilizar_cola_1[256];
u8 muestra_dma_reutilizar_cola_2[256];
u8 muestra_dma_reutilizar_cola_cola_1;
u8 muestra_dma_reutilizar_cola_cola_2;
u8 muestra_dma_reutilizar_cola_cabeza_1;
u8 muestra_dma_reutilizar_cola_cabeza_2;

ALSeqFile* sec_cabecera_archivo;
ALSeqFile* cabecera_ctl_al;
ALSeqFile* tabla_al;
u8* conjuntos_banco_al;
u16 cantidad_secuencia;
struct EntradaCtl* entradas_ctl;
struct AudioBufferParametrosEU parametros_buffer_audio;
u32 dato_803B70A8;
s32 ordenes_audio_max;
s32 notas_simultaneo_max;
s16 interno_tempo_a_externo;
s8 audio_bib_sonido_modo;
volatile s32 cantidad_frame_audio;
s32 act_audio_frame_dma_cantidad;

char cargar_cadena_audio_00[] = "Romcopy %x -> %x ,size %x\n";
char cargar_cadena_audio_01[] = "Romcopyend\n";
char cargar_cadena_audio_02[] = "CAUTION:WAVE CACHE FULL %d";
char cargar_cadena_audio_03[] = "LOAD  Rom :%x -> Ram :%x  Len:%x\n";
char cargar_cadena_audio_04[] = "BASE %x %x\n";
char cargar_cadena_audio_05[] = "LOAD %x %x %x\n";
char cargar_cadena_audio_06[] = "INSTTOP    %x\n";
char cargar_cadena_audio_07[] = "INSTMAP[0] %x\n";
char cargar_cadena_audio_08[] = "already flags %d\n";
char cargar_cadena_audio_09[] = "already flags %d\n";
char cargar_cadena_audio_10[] = "ERR:SLOW BANK DMA BUSY\n";
char cargar_cadena_audio_11[] = "ERR:SLOW DMA BUSY\n";
char cargar_cadena_audio_12[] = "Check %d  bank %d\n";
char cargar_cadena_audio_13[] = "Cache Check\n";
char cargar_cadena_audio_14[] = "NO BANK ERROR\n";
char cargar_cadena_audio_15[] = "BANK %d LOADING START\n";
char cargar_cadena_audio_16[] = "BANK %d LOAD MISS (NO MEMORY)!\n";
char cargar_cadena_audio_17[] = "BANK %d ALREADY CACHED\n";
char cargar_cadena_audio_18[] = "BANK LOAD MISS! FOR %d\n";
char cargar_cadena_audio_19[] = "Seq %d Loading Start\n";
char cargar_cadena_audio_20[] = "Heap Overflow Error\n";
char cargar_cadena_audio_21[] = "SEQ  %d ALREADY CACHED\n";
char cargar_cadena_audio_22[] = "Ok,one bank slow load Start \n";
char cargar_cadena_audio_23[] = "Sorry,too many %d bank is none.fast load Start \n";
char cargar_cadena_audio_24[] = "Seq %d:Default Load Id is %d\n";
char cargar_cadena_audio_25[] = "Seq Loading Start\n";
char cargar_cadena_audio_26[] = "Error:Before Sequence-SlowDma remain.\n";
char cargar_cadena_audio_27[] = "      Cancel Seq Start.\n";
char cargar_cadena_audio_28[] = "SEQ  %d ALREADY CACHED\n";
char cargar_cadena_audio_29[] = "Clear Workarea %x -%x size %x \n";
char cargar_cadena_audio_30[] = "AudioHeap is %x\n";
char cargar_cadena_audio_31[] = "Heap reset.Synth Change %x \n";
char cargar_cadena_audio_32[] = "Heap %x %x %x\n";
char cargar_cadena_audio_33[] = "Main Heap Initialize.\n";
char cargar_cadena_audio_34[] = "---------- Init Completed. ------------\n";
char cargar_cadena_audio_35[] = " Syndrv    :[%6d]\n";
char cargar_cadena_audio_36[] = " Seqdrv    :[%6d]\n";
char cargar_cadena_audio_37[] = " audiodata :[%6d]\n";
char cargar_cadena_audio_38[] = "---------------------------------------\n";

void copiar_inmediato_dma_audio(u8* direccion_dev, void* direccion_v, size_t nbytes) {
    osInvalDCache(direccion_v, nbytes);
    osPiStartDma(&dato_803B6740, OS_MESG_PRI_HIGH, OS_READ, (uintptr_t) direccion_dev, direccion_v, nbytes, &dato_803B6720);
    osRecvMesg(&dato_803B6720, NULL, OS_MESG_BLOCK);
}

void copiar_asincrono_dma_audio(uintptr_t direccion_dev, void* direccion_v, size_t nbytes, OSMesgQueue* cola, OSIoMesg* msj) {
    osInvalDCache(direccion_v, nbytes);
    osPiStartDma(msj, OS_MESG_PRI_NORMAL, OS_READ, direccion_dev, direccion_v, nbytes, cola);
}

void copiar_asincrono_parcial_dma_audio(uintptr_t* direccion_dev, u8** direccion_v, ssize_t* restante, OSMesgQueue* cola,
                                  OSIoMesg* msj) {
    ssize_t transferencia = (*restante >= 0x1000 ? 0x1000 : *restante);
    *restante -= transferencia;
    osInvalDCache(*direccion_v, transferencia);
    osPiStartDma(msj, OS_MESG_PRI_NORMAL, OS_READ, *direccion_dev, *direccion_v, transferencia, cola);
    *direccion_dev += transferencia;
    *direccion_v += transferencia;
}

void disminuir_ttls_dma_muestra() {
    u32 i;

    for (i = 0; i < muestra_dma_lista_tamanio_1; i++) {
        struct DmaCompartido* temporal_ = &dmas_muestra[i];
        if (temporal_->ttl != 0) {
            temporal_->ttl--;
            if (temporal_->ttl == 0) {
                temporal_->indice_reutilizar = muestra_dma_reutilizar_cola_cabeza_1;
                muestra_dma_reutilizar_cola_1[muestra_dma_reutilizar_cola_cabeza_1++] = (u8) i;
            }
        }
    }

    for (i = muestra_dma_lista_tamanio_1; i < muestra_dma_num_lista_items; i++) {
        struct DmaCompartido* temporal_ = &dmas_muestra[i];
        if (temporal_->ttl != 0) {
            temporal_->ttl--;
            if (temporal_->ttl == 0) {
                temporal_->indice_reutilizar = muestra_dma_reutilizar_cola_cabeza_2;
                muestra_dma_reutilizar_cola_2[muestra_dma_reutilizar_cola_cabeza_2++] = (u8) i;
            }
        }
    }

    dato_803B6E60 = 0;
}

void* datos_muestra_dma(uintptr_t direccion_dev, u32 size, s32 parametro2, u8* ref_indice_dma) {
    s32 tiene_dma = false;
    struct DmaCompartido* dma;
    uintptr_t direccion_dev_dma;
    u32 transferencia;
    u32 i;
    u32 indice_dma;
    ssize_t buffer_pos;
    SIN_USO u32 relleno;

    if (parametro2 != 0 || *ref_indice_dma >= muestra_dma_lista_tamanio_1) {
        for (i = muestra_dma_lista_tamanio_1; i < muestra_dma_num_lista_items; i++) {
            dma = &dmas_muestra[i];
            buffer_pos = direccion_dev - dma->source;
            if (0 <= buffer_pos && (size_t) buffer_pos <= dma->tamanio_buf - size) {
                if (dma->ttl == 0 && muestra_dma_reutilizar_cola_cola_2 != muestra_dma_reutilizar_cola_cabeza_2) {
                    if (dma->indice_reutilizar != muestra_dma_reutilizar_cola_cola_2) {
                        muestra_dma_reutilizar_cola_2[dma->indice_reutilizar] = muestra_dma_reutilizar_cola_2[muestra_dma_reutilizar_cola_cola_2];
                        dmas_muestra[muestra_dma_reutilizar_cola_2[muestra_dma_reutilizar_cola_cola_2]].indice_reutilizar = dma->indice_reutilizar;
                    }
                    muestra_dma_reutilizar_cola_cola_2++;
                }
                dma->ttl = 60;
                *ref_indice_dma = (u8) i;
                return &dma->buffer[(direccion_dev - dma->source)];
            }
        }

        if ((muestra_dma_reutilizar_cola_cola_2 != muestra_dma_reutilizar_cola_cabeza_2) && (parametro2 != 0)) {
            indice_dma = muestra_dma_reutilizar_cola_2[muestra_dma_reutilizar_cola_cola_2++];
            dma = &dmas_muestra[indice_dma];
            tiene_dma = true;
        }
    } else {
        dma = &dmas_muestra[*ref_indice_dma];
        for (i = 0; i < muestra_dma_lista_tamanio_1; dma = &dmas_muestra[i++]) {
            buffer_pos = direccion_dev - dma->source;
            if (0 <= buffer_pos && (size_t) buffer_pos <= dma->tamanio_buf - size) {
                if (dma->ttl == 0) {
                    if (dma->indice_reutilizar != muestra_dma_reutilizar_cola_cola_1) {
                        if (1) {}
                        muestra_dma_reutilizar_cola_1[dma->indice_reutilizar] = muestra_dma_reutilizar_cola_1[muestra_dma_reutilizar_cola_cola_1];
                        dmas_muestra[muestra_dma_reutilizar_cola_1[muestra_dma_reutilizar_cola_cola_1]].indice_reutilizar = dma->indice_reutilizar;
                    }
                    muestra_dma_reutilizar_cola_cola_1++;
                }
                dma->ttl = 2;
                return dma->buffer + (direccion_dev - dma->source);
            }
        }
    }

    if (!tiene_dma) {
        indice_dma = muestra_dma_reutilizar_cola_1[muestra_dma_reutilizar_cola_cola_1++];
        dma = &dmas_muestra[indice_dma];
        tiene_dma = true;
    }

    transferencia = dma->tamanio_buf;
    direccion_dev_dma = direccion_dev & ~0xF;
    dma->ttl = 2;
    dma->source = direccion_dev_dma;
    dma->tamanio_sin_uso = transferencia;
    osPiStartDma(&act_audio_frame_dma_io_msj_bufs[act_audio_frame_dma_cantidad++], OS_MESG_PRI_NORMAL, OS_READ, direccion_dev_dma,
                 dma->buffer, transferencia, &act_audio_frame_dma_cola);
    *ref_indice_dma = indice_dma;
    return (direccion_dev - direccion_dev_dma) + dma->buffer;
}

void funcion_800BB030(SIN_USO s32 parametro0) {
    s32 i;
#define j i

    dato_803B70A8 = 0x5A0;

    for (i = 0; i < notas_simultaneo_max * 3 * parametros_buffer_audio.desconocido_ajuste_4; i++) {
        dmas_muestra[muestra_dma_num_lista_items].buffer = sonido_reserva(&notas_y_pool_buffers, dato_803B70A8);
        if (dmas_muestra[muestra_dma_num_lista_items].buffer == NULL) {
            break;
        }
        dmas_muestra[muestra_dma_num_lista_items].tamanio_buf = dato_803B70A8;
        dmas_muestra[muestra_dma_num_lista_items].source = 0;
        dmas_muestra[muestra_dma_num_lista_items].tamanio_sin_uso = 0;
        dmas_muestra[muestra_dma_num_lista_items].unused2 = 0;
        dmas_muestra[muestra_dma_num_lista_items].ttl = 0;
        muestra_dma_num_lista_items++;
    }

    for (i = 0; (u32) i < muestra_dma_num_lista_items; i++) {
        muestra_dma_reutilizar_cola_1[i] = (u8) i;
        dmas_muestra[i].indice_reutilizar = (u8) i;
    }

    for (j = muestra_dma_num_lista_items; j < 0x100; j++) {
        muestra_dma_reutilizar_cola_1[j] = 0;
    }

    muestra_dma_reutilizar_cola_cola_1 = 0;
    muestra_dma_reutilizar_cola_cabeza_1 = (u8) muestra_dma_num_lista_items;
    muestra_dma_lista_tamanio_1 = muestra_dma_num_lista_items;

    dato_803B70A8 = 0x180;
    for (i = 0; i < notas_simultaneo_max; i++) {
        dmas_muestra[muestra_dma_num_lista_items].buffer = sonido_reserva(&notas_y_pool_buffers, dato_803B70A8);
        if (dmas_muestra[muestra_dma_num_lista_items].buffer == NULL) {
            break;
        }
        dmas_muestra[muestra_dma_num_lista_items].tamanio_buf = dato_803B70A8;
        dmas_muestra[muestra_dma_num_lista_items].source = 0;
        dmas_muestra[muestra_dma_num_lista_items].tamanio_sin_uso = 0;
        dmas_muestra[muestra_dma_num_lista_items].unused2 = 0;
        dmas_muestra[muestra_dma_num_lista_items].ttl = 0;
        muestra_dma_num_lista_items++;
    }

    for (i = muestra_dma_lista_tamanio_1; (u32) i < muestra_dma_num_lista_items; i++) {
        muestra_dma_reutilizar_cola_2[i - muestra_dma_lista_tamanio_1] = (u8) i;
        dmas_muestra[i].indice_reutilizar = (u8) (i - muestra_dma_lista_tamanio_1);
    }

    for (j = muestra_dma_num_lista_items; j < 0x100; j++) {
        muestra_dma_reutilizar_cola_2[j] = muestra_dma_lista_tamanio_1;
    }

    muestra_dma_reutilizar_cola_cola_2 = 0;
    muestra_dma_reutilizar_cola_cabeza_2 = muestra_dma_num_lista_items - muestra_dma_lista_tamanio_1;
#undef j
}

s32 funcion_800BB304(struct MuestraBancoAudio* muestra) {
    SIN_USO u8* mem;

    if (muestra == (void*) NULL) {
        return -1;
    }

    if (muestra->cargado == 1) {
        mem = sonido_reserva(&notas_y_pool_buffers, muestra->tamanio_muestra);
        if (mem == (void*) NULL) {
            return -1;
        }
        copiar_inmediato_dma_audio(muestra->direccion_muestra, mem, muestra->tamanio_muestra);
        muestra->cargado = 0x81;
        muestra->direccion_muestra = mem;
    }
}

s32 funcion_800BB388(s32 id_banco, s32 inst_id, s32 parametro2) {
    struct Instrumento* instr;
    struct Tambor* tambor;

    if (inst_id < 0x7F) {
        instr = obtener_interior_instrumento(id_banco, inst_id);
        if (instr == NULL) {
            return -1;
        }
        if (instr->rango_lo_normal != 0) {
            funcion_800BB304(instr->sonido_notas_bajo.muestra);
        }
        funcion_800BB304(instr->sonido_notas_normal.muestra);
        if (instr->rango_hi_normal != 0x7F) {
            funcion_800BB304(instr->sonido_notas_alto.muestra);
        }
    } else if (inst_id == 0x7F) {
        tambor = obtener_tambor(id_banco, parametro2);
        if (tambor == NULL) {
            return -1;
        }
        funcion_800BB304(tambor->sonido.muestra);
        return 0;
    }
#ifdef AVOID_UB
    return 0;
#endif
}

void funcion_800BB43C(ALSeqFile* f, u8* base) {
#define PARCHE(ORIG, BASE, TIPO) ORIG = (TIPO) ((uintptr_t) ORIG + (uintptr_t) BASE)
    int i;
    u8* wut = base;
    for (i = 0; i < f->seqCount; i++) {
        if (f->seqArray[i].len != 0) {
            PARCHE(f->seqArray[i].offset, wut, u8*);
        }
    }
#undef PARCHE
}

void parchear_sonido(struct SonidoBancoAudio* sonido, u8* mem_base, u8* base_desplazamiento) {
    struct MuestraBancoAudio* muestra;
    void* parcheado;
    u8* mem;

#define PARCHE(x, base) (parcheado = (void*) ((uintptr_t) (x) + (uintptr_t) base))

    if (sonido->muestra != NULL) {
        muestra = sonido->muestra = (struct MuestraBancoAudio*) PARCHE(sonido->muestra, mem_base);
        if (muestra->cargado == 0) {
            muestra->direccion_muestra = (u8*) PARCHE(muestra->direccion_muestra, base_desplazamiento);
            muestra->loop = (struct BucleAdpcm*) PARCHE(muestra->loop, mem_base);
            muestra->libro = (struct LibroAdpcm*) PARCHE(muestra->libro, mem_base);
            muestra->cargado = 1;
        } else if (muestra->cargado == 0x80) {
            PARCHE(muestra->direccion_muestra, base_desplazamiento);
            mem = sonido_reserva(&notas_y_pool_buffers, muestra->tamanio_muestra);
            if (mem == NULL) {
                muestra->direccion_muestra = (u8*) parcheado;
                muestra->cargado = 1;
            } else {
                copiar_inmediato_dma_audio((u8*) parcheado, mem, muestra->tamanio_muestra);
                muestra->cargado = 0x81;
                muestra->direccion_muestra = mem;
            }
            muestra->loop = (struct BucleAdpcm*) PARCHE(muestra->loop, mem_base);
            muestra->libro = (struct LibroAdpcm*) PARCHE(muestra->libro, mem_base);
        }
    }

#undef PARCHE
}

void funcion_800BB584(s32 id_banco) {
    u8* variable_a1;

    if (tabla_al->seqArray[id_banco].len == 0) {
        variable_a1 = tabla_al->seqArray[(s32) tabla_al->seqArray[id_banco].offset].offset;
    } else {
        variable_a1 = tabla_al->seqArray[id_banco].offset;
    }
    parchear_banco_audio((struct BancoAudio*) (entradas_ctl[id_banco].instrumentos - 1), variable_a1,
                     entradas_ctl[id_banco].instrumentos_num, entradas_ctl[id_banco].tambores_num);
    entradas_ctl[id_banco].tambores = (struct Tambor**) *(entradas_ctl[id_banco].instrumentos - 1);
}

void parchear_banco_audio(struct BancoAudio* mem, u8* desplazamiento, u32 instrumentos_num, u32 tambores_num) {
    struct Instrumento* instrumento;
    struct Instrumento** it_instrs;
    struct Instrumento** end;
    struct BancoAudio* temporal_;
    u32 i;
    void* parcheado;
    struct Tambor* tambor;
    struct Tambor** tambores;
    u32 tambores_num_2;

#define REAL_DESPLAZAMIENTO_BASE(x, base) (void*) ((uintptr_t) (x) + (uintptr_t) base)
#define PARCHE(x, base) (parcheado = REAL_DESPLAZAMIENTO_BASE(x, base))
#define MEM_PARCHE(x) x = PARCHE(x, mem)

#define DESPLAZAMIENTO_BASE(x, base) REAL_DESPLAZAMIENTO_BASE(base, x)

    tambores = mem->tambores;
    tambores_num_2 = tambores_num;
    if (tambores != NULL && tambores_num_2 > 0) {
        mem->tambores = PARCHE(tambores, mem);
        for (i = 0; i < tambores_num_2; i++) {
            parcheado = mem->tambores[i];
            if (parcheado != NULL) {
                tambor = PARCHE(parcheado, mem);
                mem->tambores[i] = tambor;
                if (tambor->cargado == 0) {
                    parchear_sonido(&tambor->sonido, (u8*) mem, desplazamiento);
                    parcheado = tambor->envelope;
                    tambor->envelope = DESPLAZAMIENTO_BASE(mem, parcheado);
                    tambor->cargado = 1;
                }
            }
        }
    }

    temporal_ = &*mem;
    if (instrumentos_num > 0) {
        struct Instrumento** inst_temporal;
        it_instrs = temporal_->instrumentos;
        inst_temporal = temporal_->instrumentos;
        end = instrumentos_num + inst_temporal;

        do {
            if (*it_instrs != NULL) {
                *it_instrs = DESPLAZAMIENTO_BASE(*it_instrs, mem);
                instrumento = *it_instrs;

                if (instrumento->cargado == 0) {
                    parchear_sonido(&instrumento->sonido_notas_bajo, (u8*) mem, desplazamiento);
                    parchear_sonido(&instrumento->sonido_notas_normal, (u8*) mem, desplazamiento);
                    parchear_sonido(&instrumento->sonido_notas_alto, (u8*) mem, desplazamiento);
                    parcheado = instrumento->envelope;
                    instrumento->envelope = DESPLAZAMIENTO_BASE(mem, parcheado);
                    instrumento->cargado = 1;
                }
            }
            it_instrs++;
        } while (end != it_instrs);
    }
#undef MEM_PARCHE
#undef PARCHE
#undef REAL_DESPLAZAMIENTO_BASE
#undef DESPLAZAMIENTO_BASE
}

struct BancoAudio* cargar_inmediato_banco(s32 id_banco, s32 parametro1) {
    s32 reservar;
    SIN_USO s32 margen_pila_0[9];
    struct BancoAudio* devuelto;
    u8* datos_ctl;

    reservar = cabecera_ctl_al->seqArray[id_banco].len + 0xf;
    reservar = ALIGN16(reservar);
    reservar -= 0x10;
    datos_ctl = cabecera_ctl_al->seqArray[id_banco].offset;
    devuelto = reservar_banco_o_sec(&pool_cargado_banco, 1, reservar, parametro1, id_banco);
    if (devuelto == NULL) {
        return NULL;
    }
    copiar_inmediato_dma_audio(datos_ctl + 0x10, devuelto, (u32) reservar);
    entradas_ctl[id_banco].instrumentos = devuelto->instrumentos;
    funcion_800BB584(id_banco);
    if (situacion_carga_banco[id_banco] != 5) {
        situacion_carga_banco[id_banco] = 2;
    }
    return devuelto;
}

struct BancoAudio* cargar_asincrono_banco(s32 id_banco, s32 parametro1, struct JugadorSecuencia* sec_jugador) {
    size_t reservar;
    SIN_USO s32 margen_pila_0[9];
    struct BancoAudio* devuelto;
    u8* datos_ctl;
    SIN_USO s32 margen_pila_1[2];

    reservar = cabecera_ctl_al->seqArray[id_banco].len + 0xF;
    reservar = ALIGN16(reservar);
    reservar -= 0x10;
    datos_ctl = cabecera_ctl_al->seqArray[id_banco].offset;
    devuelto = reservar_banco_o_sec(&pool_cargado_banco, 1, reservar, parametro1, id_banco);
    if (devuelto == NULL) {
        return NULL;
    }
    sec_jugador->id_banco_cargando = id_banco;
    entradas_ctl[id_banco].instrumentos = devuelto->instrumentos;
    entradas_ctl[id_banco].tambores = NULL;
    sec_jugador->banco_dma_act_mem_direccion = (u8*) devuelto;
    sec_jugador->banco_dma_act_dev_direccion = (uintptr_t) (datos_ctl + 0x10);
    sec_jugador->restante_dma_banco = reservar;
    if (1) {}
    osCreateMesgQueue(&sec_jugador->banco_dma_msj_cola, &sec_jugador->msj_dma_banco, 1);
    sec_jugador->dma_banco_en_progreso = true;
    copiar_asincrono_parcial_dma_audio(&sec_jugador->banco_dma_act_dev_direccion, &sec_jugador->banco_dma_act_mem_direccion,
                                 &sec_jugador->restante_dma_banco, &sec_jugador->banco_dma_msj_cola, &sec_jugador->banco_dma_io_msj);
    if (situacion_carga_banco[id_banco] != 5) {
        situacion_carga_banco[id_banco] = 1;
    }
    return devuelto;
}

void* inmediato_dma_secuencia(s32 sec_id, s32 parametro1) {
    s32 sec_longitud;
    void* ptr;
    u8* sec_datos;

    sec_longitud = sec_cabecera_archivo->seqArray[sec_id].len;
    sec_longitud = ALIGN16(sec_longitud);
    sec_datos = sec_cabecera_archivo->seqArray[sec_id].offset;
    ptr = reservar_banco_o_sec(&sec_pool_cargado, 1, sec_longitud, parametro1, sec_id);
    if (ptr == NULL) {
        return NULL;
    }

    copiar_inmediato_dma_audio(sec_datos, ptr, sec_longitud);
    if (sec_situacion_carga[sec_id] != 5) {
        sec_situacion_carga[sec_id] = 2;
    }
    return ptr;
}

void* asincrono_dma_secuencia(s32 sec_id, s32 parametro1, struct JugadorSecuencia* sec_jugador) {
    s32 sec_longitud;
    void* ptr;
    u8* sec_datos;
    OSMesgQueue* cola_msj;

    sec_longitud = sec_cabecera_archivo->seqArray[sec_id].len;
    sec_longitud = ALIGN16(sec_longitud);
    sec_datos = sec_cabecera_archivo->seqArray[sec_id].offset;
    ptr = reservar_banco_o_sec(&sec_pool_cargado, 1, sec_longitud, parametro1, sec_id);
    if (ptr == NULL) {
        return NULL;
    }
    if (sec_longitud < 0x41) {
        copiar_inmediato_dma_audio(sec_datos, ptr, (u32) sec_longitud);
        if (1) {}
        if (sec_situacion_carga[sec_id] != 5) {
            sec_situacion_carga[sec_id] = 2;
        }
    } else {
        copiar_inmediato_dma_audio(sec_datos, ptr, 0x00000040U);
        cola_msj = &sec_jugador->sec_cola_msj_dma;
        osCreateMesgQueue(cola_msj, &sec_jugador->sec_msj_dma, 1);
        sec_jugador->sec_dma_en_progreso = true;
        copiar_asincrono_dma_audio((uintptr_t) (sec_datos + 0x40), (u8*) ptr + 0x40, sec_longitud - 0x40, cola_msj,
                             &sec_jugador->sec_msj_io_dma);
        if (sec_situacion_carga[sec_id] != 5) {
            sec_situacion_carga[sec_id] = 1;
        }
    }
    return ptr;
}

u8 obtener_banco_faltante(u32 sec_id, s32* no_cantidad_nulo, s32* cantidad_nulo) {
    void* temporal_;
    u32 id_banco;
    u16 desplazamiento;
    u8 i;
    u8 devuelto;

    *cantidad_nulo = 0;
    *no_cantidad_nulo = 0;
    desplazamiento = ((u16*) conjuntos_banco_al)[sec_id];
    for (i = conjuntos_banco_al[desplazamiento++], devuelto = 0; i != 0; i--) {
        id_banco = conjuntos_banco_al[desplazamiento++];

        if (ES_BANCO_CARGA_COMPLETO(id_banco) == true) {
            temporal_ = obtener_banco_o_sec(1, 2, id_banco);
        } else {
            temporal_ = NULL;
        }

        if (temporal_ == NULL) {
            (*cantidad_nulo)++;
            devuelto = id_banco;
        } else {
            (*no_cantidad_nulo)++;
        }
    }

    return devuelto;
}

struct BancoAudio* cargar_inmediato_bancos(s32 sec_id, u8* banco_predeterminado_salida) {
    void* devuelto;
    u32 id_banco;
    u16 desplazamiento;
    u8 i;

    desplazamiento = ((u16*) conjuntos_banco_al)[sec_id];
    for (i = conjuntos_banco_al[desplazamiento++]; i != 0; i--) {
        id_banco = conjuntos_banco_al[desplazamiento++];

        if (ES_BANCO_CARGA_COMPLETO(id_banco) == true) {
            devuelto = obtener_banco_o_sec(1, 2, id_banco);
        } else {
            devuelto = NULL;
        }

        if (devuelto == NULL) {
            devuelto = cargar_inmediato_banco(id_banco, 2);
        }
    }
    *banco_predeterminado_salida = id_banco;
    return devuelto;
}

void precargar_secuencia(u32 sec_id, u8 precargar_mascara) {
    void* datos_secuencia;
    u8 temporal_;

    if (sec_id >= cantidad_secuencia) {
        return;
    }

    if (sec_cabecera_archivo->seqArray[sec_id].len == 0) {
        sec_id = (u32) sec_cabecera_archivo->seqArray[sec_id].offset;
    }

    bloqueo_carga_audio = CARGANDO_BLOQUEO_AUDIO;
    if (precargar_mascara & BANCOS_PRECARGAR) {
        cargar_inmediato_bancos(sec_id, &temporal_);
    }

    if (precargar_mascara & SECUENCIA_PRECARGAR) {
        if (ES_BANCO_CARGA_COMPLETO(sec_id) == true) {
            datos_secuencia = obtener_banco_o_sec(0, 2, sec_id);
        } else {
            datos_secuencia = NULL;
        }
        if (datos_secuencia == NULL && inmediato_dma_secuencia(sec_id, 2) == NULL) {
            bloqueo_carga_audio = BLOQUEO_AUDIO_NO_CARGANDO;
            return;
        }
    }

    bloqueo_carga_audio = BLOQUEO_AUDIO_NO_CARGANDO;
}

void cargar_secuencia(u32 jugador, u32 sec_id, s32 cargar_asincrono) {
    if (!cargar_asincrono) {
        bloqueo_carga_audio = CARGANDO_BLOQUEO_AUDIO;
    }
    cargar_interno_secuencia(jugador, sec_id, cargar_asincrono);
    if (!cargar_asincrono) {
        bloqueo_carga_audio = BLOQUEO_AUDIO_NO_CARGANDO;
    }
}

void cargar_interno_secuencia(u32 jugador, u32 sec_id, s32 cargar_asincrono) {
    void* datos_secuencia;
    struct JugadorSecuencia* sec_jugador = &jugadores_secuencia[jugador];
    SIN_USO u32 margen[2];

    if (sec_id >= cantidad_secuencia) {
        return;
    }

    if (sec_cabecera_archivo->seqArray[sec_id].len == 0) {
        sec_id = (u32) sec_cabecera_archivo->seqArray[sec_id].offset;
    }

    desactivar_jugador_secuencia(sec_jugador);
    if (cargar_asincrono) {
        s32 bancos_faltante_num = 0;
        s32 ficticio = 0;
        s32 id_banco = obtener_banco_faltante(sec_id, &ficticio, &bancos_faltante_num);
        if (bancos_faltante_num == 1) {
            if (cargar_asincrono_banco(id_banco, 2, sec_jugador) == NULL) {
                return;
            }
            sec_jugador->banco_predeterminado[0] = id_banco;
        } else {
            if (cargar_inmediato_bancos(sec_id, &sec_jugador->banco_predeterminado[0]) == NULL) {
                return;
            }
        }
    } else if (cargar_inmediato_bancos(sec_id, &sec_jugador->banco_predeterminado[0]) == NULL) {
        return;
    }

    sec_jugador->sec_id = sec_id;
    datos_secuencia = obtener_banco_o_sec(0, 2, sec_id);
    if (datos_secuencia == NULL) {
        if (sec_jugador->sec_dma_en_progreso) {
            return;
        }
        if (cargar_asincrono) {
            datos_secuencia = asincrono_dma_secuencia(sec_id, 2, sec_jugador);
        } else {
            datos_secuencia = inmediato_dma_secuencia(sec_id, 2);
        }

        if (datos_secuencia == NULL) {
            return;
        }
    }

    inicializar_jugador_secuencia(jugador);
    sec_jugador->estado_guion.profundidad = 0;
    sec_jugador->delay = 0;
    sec_jugador->activado = true;
    sec_jugador->sec_datos = datos_secuencia;
    sec_jugador->estado_guion.pc = datos_secuencia;
}

extern u8 _audio_banksSegmentRomStart;
extern u8 _audio_tablesSegmentRomStart;
extern u8 _instrument_setsSegmentRomStart;
extern u8 _sequencesSegmentRomStart;
void inicializar_audio(void) {
    s32 i;
    SIN_USO s32 relleno[6];
    s32 j, k;
    s32 cantidad_sec_ctl;
    u32 buf[2];
    SIN_USO s32 lim2, lim3;
    s32 size;
    u64* ptr64;
    SIN_USO s32 relleno2;
    SIN_USO s32 one = 1;
    void* datos;

    bloqueo_carga_audio = 0;

    for (i = 0; i < tamanio_monton_audio / 8; i++) {
        ((u64*) monton_audio)[i] = 0;
    }

#ifdef TARGET_N64
    ptr64 = (u64*) ((u8*) gfx_sp_tarea_salida_buffer + sizeof(gfx_sp_tarea_salida_buffer));
    for (k = ((uintptr_t) &audio_globales_fin_marcador - (uintptr_t) ((u64 *)((u8 *) gfx_sp_tarea_salida_buffer + sizeof(gfx_sp_tarea_salida_buffer))) ) / 8; k >= 0; k--) {
        *ptr64++ = 0;
    }
#endif

#ifdef VERSION_EU
    dato_803B7178 = 20.03042f;
    tasa_refrescar = 50;
#else
    switch (osTvType) {
        case TV_TYPE_PAL:
            dato_803B7178 = 20.03042f;
            tasa_refrescar = 50;
            break;
        case TV_TYPE_MPAL:
            dato_803B7178 = 16.546f;
            tasa_refrescar = 60;
            break;
        case TV_TYPE_NTSC:
        default:
            dato_803B7178 = 16.713f;
            tasa_refrescar = 60;
            break;
    }
#endif
    inicializar_eu_puerto();
    if (k) {}
    for (i = 0; i < NUMAIBUFFERS; i++) {
        longitudes_buffer_ai[i] = 0xa0;
    }

    indice_tarea_audio = cantidad_frame_audio = 0;
    act_ai_buffer_indice = 0;
    audio_bib_sonido_modo = 0;
    tarea_audio = NULL;
    tareas_audio[0].tarea.t.data_size = 0;
    tareas_audio[1].tarea.t.data_size = 0;
    osCreateMesgQueue(&dato_803B6720, &dato_803B6738, 1);
    osCreateMesgQueue(&act_audio_frame_dma_cola, act_audio_frame_dma_msj_bufs, CANTIDAD_ARREGLO(act_audio_frame_dma_msj_bufs));
    act_audio_frame_dma_cantidad = 0;
    muestra_dma_num_lista_items = 0;

    sonido_pools_principal_inicializacion(audio_inicializacion_pool_tamanio);

    for (i = 0; i < NUMAIBUFFERS; i++) {
        ai_buffers[i] = sonido_reserva(&pool_inicializacion_audio, LARGO_AIBUFFER);

        for (j = 0; j < (s32) (LARGO_AIBUFFER / sizeof(s16)); j++) {
            ai_buffers[i][j] = 0;
        }
    }

    audio_reinicio_ajuste_id_a_carga = 0;
    situacion_reinicio_audio = one;
    reiniciar_paso_abajo_cerrar_audio_y();

    sec_cabecera_archivo = (ALSeqFile*) buf;
    datos = &_sequencesSegmentRomStart;
    copiar_inmediato_dma_audio(datos, sec_cabecera_archivo, 0x10);
    cantidad_secuencia = sec_cabecera_archivo->seqCount;
    size = cantidad_secuencia * sizeof(ALSeqData) + 4;
    size = ALIGN16(size);
    sec_cabecera_archivo = sonido_reserva(&pool_inicializacion_audio, size);
    copiar_inmediato_dma_audio(datos, sec_cabecera_archivo, size);
    funcion_800BB43C(sec_cabecera_archivo, datos);

    cabecera_ctl_al = (ALSeqFile*) buf;
    datos = &_audio_banksSegmentRomStart;
    copiar_inmediato_dma_audio(datos, cabecera_ctl_al, 0x10);
    cantidad_sec_ctl = cabecera_ctl_al->seqCount;
    size = ALIGN16(cantidad_sec_ctl * sizeof(ALSeqData) + 4);
    cabecera_ctl_al = sonido_reserva(&pool_inicializacion_audio, size);
    copiar_inmediato_dma_audio(datos, cabecera_ctl_al, size);
    funcion_800BB43C(cabecera_ctl_al, datos);
    entradas_ctl = sonido_reserva(&pool_inicializacion_audio, cantidad_sec_ctl * sizeof(struct EntradaCtl));
    for (i = 0; i < cantidad_sec_ctl; i++) {
        copiar_inmediato_dma_audio(cabecera_ctl_al->seqArray[i].offset, buf, 0x10);
        entradas_ctl[i].instrumentos_num = buf[0];
        entradas_ctl[i].tambores_num = buf[1];
    }

    tabla_al = (ALSeqFile*) buf;
    datos = &_audio_tablesSegmentRomStart;
    copiar_inmediato_dma_audio(datos, tabla_al, 0x10);
    size = tabla_al->seqCount * sizeof(ALSeqData) + 4;
    size = ALIGN16(size);
    tabla_al = sonido_reserva(&pool_inicializacion_audio, size);
    copiar_inmediato_dma_audio(datos, tabla_al, size);
    funcion_800BB43C(tabla_al, datos);

    conjuntos_banco_al = sonido_reserva(&pool_inicializacion_audio, 0x100);
    copiar_inmediato_dma_audio((u8 *) &_instrument_setsSegmentRomStart, conjuntos_banco_al, 0x100);

    sonido_inicializacion_pool_reserva(&pool_desconocido_1.pool, sonido_reserva(&pool_inicializacion_audio, (u32) dato_800EA5D8), (u32) dato_800EA5D8);
    inicializar_jugadores_secuencia();
    bloqueo_carga_audio = 0x76557364;
}
