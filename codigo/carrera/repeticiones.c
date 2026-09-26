#include <ultra64.h>
#include <juego/macros.h>
#include <juego/estructuras_comunes.h>
#include <juego/definiciones.h>
#include <juego/decodificacion.h>
#include <juego/mk64.h>
#include <juego/pista.h>

#include "sistema/bucle_principal.h"
#include "carrera/preparacion_carrera.h"
#include "memoria/buffers.h"
#include "sistema/guardado.h"
#include "carrera/repeticiones.h"
#include "carrera/inicio_hud_y_objetos.h"
#include "menus/elementos_menu.h"
#include "carrera/objetos_y_efectos.h"
#include "graficos/texturas_kart.h"

extern s32 mio0encode(s32 entrada, s32, s32);
extern s32 funcion_80040174(void*, s32, s32);

u8* buffer_fantasma_repeticion;
s16 repeticion_fantasma_buffer_tamanio;
s16 dato_80162D86;

static u16 jugador_fantasma_botones_ant;
static u32 jugador_fantasma_frames_restante;
static s16 jugador_fantasma_repeticion_idx;
static u32* repeticion_fantasma_jugador;

static u16 botones_ant_circuito_fantasma;
static u32 circuito_fantasma_frames_restante;
static s16 circuito_fantasma_repeticion_idx;
static u32* repeticion_fantasma_circuito;

static u16 publicar_tt_botones_ant;
static s32 publicar_tt_frames_restante;
static s16 publicar_tt_repeticion_idx;
static u32* repeticion_tt_publicar;

static s16 idx_entrada_jugador;
static u32* entradas_jugador;

static u16 id_circuito_ant;
u32 dato_80162DC4;
s32 dato_80162DC8;
s32 dato_80162DCC;
s32 dato_80162DD0;
u16 b_jugador_fantasma_desactivado;
u16 b_circuito_fantasma_desactivado;
u16 dato_80162DD8;
s32 dato_80162DDC;
s32 dato_80162DE0;
s32 dato_80162DE4;
s32 dato_80162DE8;
SIN_USO static s32 contador_repeticion_sin_uso;
s32 pausa_disparado;
SIN_USO static s32 b_sin_uso_circuito_fantasma_desactivado;
s32 publicar_contrarreloj_guardado_no_puede_repeticion;
s32 dato_80162DFC;

s32 dato_80162E00;

u32* repeticion_fantasma_codificado = (u32*) &dato_802BFB80.tamanio_arreglo_8[0][2][3];
u32* repeticion_fantasma_comprimido = (u32*) &dato_802BFB80.tamanio_arreglo_8[1][1][3];

extern s32 cantidad_vuelta_por_id_jugador[];

extern FantasmaPersonal* d_mario_raceway_fantasma_personal;
extern FantasmaPersonal* d_royal_raceway_fantasma_personal;
extern FantasmaPersonal* d_luigi_raceway_fantasma_personal;

void cargar_fantasma_circuito(void) {
    repeticion_fantasma_circuito = (u32*) &dato_802BFB80.tamanio_arreglo_8[0][2][3];
    osInvalDCache(&repeticion_fantasma_circuito[0], 0x4000);
    osPiStartDma(&msj_io_dma, 0, 0, (uintptr_t) &_kart_texturesSegmentRomStart[SEGMENT_OFFSET(dato_80162DC4)],
                 repeticion_fantasma_circuito, 0x4000, &cola_msj_dma);
    osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
    circuito_fantasma_frames_restante = (*repeticion_fantasma_circuito & CONTADOR_FRAME_REPETICION);
    circuito_fantasma_repeticion_idx = 0;
}

void publicar_contrarreloj_repeticion_carga(void) {
    repeticion_tt_publicar = (u32*) &dato_802BFB80.tamanio_arreglo_8[0][dato_80162DD0][3];
    publicar_tt_frames_restante = *repeticion_tt_publicar & CONTADOR_FRAME_REPETICION;
    publicar_tt_repeticion_idx = 0;
}

void cargar_fantasma_jugador(void) {
    repeticion_fantasma_jugador = (u32*) &dato_802BFB80.tamanio_arreglo_8[0][dato_80162DC8][3];
    jugador_fantasma_frames_restante = (s32) *repeticion_fantasma_jugador & CONTADOR_FRAME_REPETICION;
    jugador_fantasma_repeticion_idx = 0;
}
#ifdef VERSION_EU
#define DESBLOQUEAR_FANTASMA_MARIO 10700
#define ROYAL_DESBLOQUEAR_FANTASMA 19300
#define DESBLOQUEAR_FANTASMA_LUIGI 13300
#else
#define DESBLOQUEAR_FANTASMA_MARIO 9000
#define ROYAL_DESBLOQUEAR_FANTASMA 16000
#define DESBLOQUEAR_FANTASMA_LUIGI 11200

#endif

void fijar_fantasma_personal(void) {
    u32 tiempo_mejor;
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_MARIO_RACEWAY:
            tiempo_mejor = funcion_800B4E24(0) & 0xfffff;
            if (tiempo_mejor <= DESBLOQUEAR_FANTASMA_MARIO) {
                b_circuito_fantasma_desactivado = 0;
                b_sin_uso_circuito_fantasma_desactivado = 0;
            } else {
                b_circuito_fantasma_desactivado = 1;
                b_sin_uso_circuito_fantasma_desactivado = 1;
            }
            dato_80162DC4 = (u32) &d_mario_raceway_fantasma_personal;
            dato_80162DE4 = 0;
            break;
        case CIRCUITO_ROYAL_RACEWAY:
            tiempo_mejor = funcion_800B4E24(0) & 0xfffff;
            if (tiempo_mejor <= ROYAL_DESBLOQUEAR_FANTASMA) {
                b_circuito_fantasma_desactivado = 0;
                b_sin_uso_circuito_fantasma_desactivado = 0;
            } else {
                b_circuito_fantasma_desactivado = 1;
                b_sin_uso_circuito_fantasma_desactivado = 1;
            }
            dato_80162DC4 = (u32) &d_royal_raceway_fantasma_personal;
            dato_80162DE4 = 6;
            break;
        case CIRCUITO_LUIGI_RACEWAY:
            tiempo_mejor = funcion_800B4E24(0) & 0xfffff;
            if (tiempo_mejor <= DESBLOQUEAR_FANTASMA_LUIGI) {
                b_circuito_fantasma_desactivado = 0;
                b_sin_uso_circuito_fantasma_desactivado = 0;
            } else {
                b_circuito_fantasma_desactivado = 1;
                b_sin_uso_circuito_fantasma_desactivado = 1;
            }
            dato_80162DC4 = (u32) &d_luigi_raceway_fantasma_personal;
            dato_80162DE4 = 1;
            break;
        default:
            b_circuito_fantasma_desactivado = 1;
            b_sin_uso_circuito_fantasma_desactivado = 1;
    }
#else

#endif
}

s32 funcion_800051C4(void) {
    s32 phi_v0;

    if (repeticion_fantasma_buffer_tamanio != 0) {
        funcion_80040174((void*) buffer_fantasma_repeticion, (repeticion_fantasma_buffer_tamanio * 4) + 0x20, (s32) repeticion_fantasma_codificado);
        phi_v0 =
            mio0encode((s32) repeticion_fantasma_codificado, (repeticion_fantasma_buffer_tamanio * 4) + 0x20, (s32) repeticion_fantasma_comprimido);
        return phi_v0 + 0x1e;
    }
#ifdef AVOID_UB
    return 0;
#endif
}

void funcion_8000522C(void) {
    repeticion_fantasma_jugador = (u32*) &dato_802BFB80.tamanio_arreglo_8[0][dato_80162DC8][3];
    mio0decode((u8*) repeticion_fantasma_comprimido, (u8*) repeticion_fantasma_jugador);
    jugador_fantasma_frames_restante = (s32) (*repeticion_fantasma_jugador & CONTADOR_FRAME_REPETICION);
    jugador_fantasma_repeticion_idx = 0;
    dato_80162E00 = 1;
}

void funcion_800052A4(void) {
    s16 temporal_v0;

    if (dato_80162DC8 == 1) {
        dato_80162DC8 = 0;
        dato_80162DCC = 1;
    } else {
        dato_80162DC8 = 1;
        dato_80162DCC = 0;
    }
    temporal_v0 = idx_entrada_jugador;
    buffer_fantasma_repeticion = (void*) &dato_802BFB80.tamanio_arreglo_8[0][dato_80162DC8][3];
    repeticion_fantasma_buffer_tamanio = temporal_v0;
    dato_80162D86 = temporal_v0;
}

void funcion_80005310(void) {

    if (seleccion_modo == CONTRARRELOJ) {

        fijar_fantasma_personal();

        if (id_circuito_ant != id_circuito_actual) {
            b_jugador_fantasma_desactivado = 1;
        }

        id_circuito_ant = (u16) id_circuito_actual;
        pausa_disparado = 0;
        contador_repeticion_sin_uso = 0;
        publicar_contrarreloj_guardado_no_puede_repeticion = 0;

        if (seleccion_modo == CONTRARRELOJ && modo_pantalla_activo == MODO_PANTALLA_1P) {

            if (dato_8015F890 == 1) {
                publicar_contrarreloj_repeticion_carga();
                if (dato_80162DD8 == 0) {
                    cargar_fantasma_jugador();
                }
                if (b_circuito_fantasma_desactivado == 0) {
                    cargar_fantasma_circuito();
                }
            } else {

                dato_80162DD8 = 1U;
                entradas_jugador = (u32*) &dato_802BFB80.tamanio_arreglo_8[0][dato_80162DCC][3];
                entradas_jugador[0] = -1;
                idx_entrada_jugador = 0;
                dato_80162DDC = 0;
                funcion_80091EE4();
                if (b_jugador_fantasma_desactivado == 0) {
                    cargar_fantasma_jugador();
                }
                if (b_circuito_fantasma_desactivado == 0) {
                    cargar_fantasma_circuito();
                }
            }
        }
    }
}

#define MASCARA_REPETICION (TODOS_BOTONES ^ (A_BUTTON | B_BUTTON | Z_TRIG | R_TRIG | L_TRIG))

void publicar_contrarreloj_repeticion_proceso(void) {
    u32 entradas;
    u32 bytes_palanca;
    SIN_USO u16 desconocido;
    u16 temporal_botones;
    s16 val_palanca;
    s16 botones = 0;

    if (publicar_tt_repeticion_idx >= 0x1000) {
        jugador_uno->type = MODO_CINEMATICA_JUGADOR | SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR;
        return;
    }

    entradas = repeticion_tt_publicar[publicar_tt_repeticion_idx];
    bytes_palanca = entradas & PALANCA_X_REPETICION;

    if (bytes_palanca < 0x80U) {
        val_palanca = (s16) (bytes_palanca & 0xFF);
    } else {
        val_palanca = (s16) (bytes_palanca | (~0xFF));
    }

    bytes_palanca = (u32) (entradas & PALANCA_Y_REPETICION) >> 8;
    mando_ocho->palanca_x_crudo = val_palanca;

    if (bytes_palanca < 0x80U) {
        val_palanca = (s16) (bytes_palanca & 0xFF);
    } else {
        val_palanca = (s16) (bytes_palanca | (~0xFF));
    }
    mando_ocho->palanca_y_crudo = val_palanca;
    if (entradas & BOTON_REPETICION_A) {
        botones |= A_BUTTON;
    }
    if (entradas & BOTON_REPETICION_B) {
        botones |= B_BUTTON;
    }
    if (entradas & TRIG_REPETICION_Z) {
        botones |= Z_TRIG;
    }
    if (entradas & TRIG_REPETICION_R) {
        botones |= R_TRIG;
    }
    temporal_botones = mando_ocho->boton_pulsado & MASCARA_REPETICION;
    mando_ocho->boton_pulsado = (botones & (botones ^ publicar_tt_botones_ant)) | temporal_botones;
    temporal_botones = mando_ocho->boton_apretado & MASCARA_REPETICION;
    mando_ocho->boton_apretado = (publicar_tt_botones_ant & (botones ^ publicar_tt_botones_ant)) | temporal_botones;
    publicar_tt_botones_ant = botones;
    mando_ocho->button = botones;

    if (publicar_tt_frames_restante == 0) {
        publicar_tt_repeticion_idx++;
        publicar_tt_frames_restante = (s32) (repeticion_tt_publicar[publicar_tt_repeticion_idx] & CONTADOR_FRAME_REPETICION);
    } else {
        publicar_tt_frames_restante -= INCREMENTAR_FRAME_REPETICION;
    }
}

void procesar_repeticion_fantasma_circuito(void) {
    u32 entradas;
    u32 bytes_palanca;
    SIN_USO u16 desconocido;
    u16 botones_temporal;
    s16 val_palanca;
    s16 botones = 0;
    if (circuito_fantasma_repeticion_idx >= 0x1000) {
        funcion_80005AE8(jugador_tres);
        return;
    }

    entradas = repeticion_fantasma_circuito[circuito_fantasma_repeticion_idx];
    bytes_palanca = entradas & PALANCA_X_REPETICION;
    if (bytes_palanca < 0x80U) {
        val_palanca = (s16) (bytes_palanca & 0xFF);
    } else {
        val_palanca = (s16) (bytes_palanca | (~0xFF));
    }
    bytes_palanca = (u32) (entradas & PALANCA_Y_REPETICION) >> 8;
    mando_siete->palanca_x_crudo = val_palanca;

    if (bytes_palanca < 0x80U) {
        val_palanca = (s16) (bytes_palanca & 0xFF);
    } else {
        val_palanca = (s16) (bytes_palanca | (~0xFF));
    }
    mando_siete->palanca_y_crudo = val_palanca;

    if (entradas & BOTON_REPETICION_A) {
        botones = A_BUTTON;
    }
    if (entradas & BOTON_REPETICION_B) {
        botones |= B_BUTTON;
    }
    if (entradas & TRIG_REPETICION_Z) {
        botones |= Z_TRIG;
    }
    if (entradas & TRIG_REPETICION_R) {
        botones |= R_TRIG;
    }
    botones_temporal = mando_siete->boton_pulsado & MASCARA_REPETICION;
    mando_siete->boton_pulsado = (botones & (botones ^ botones_ant_circuito_fantasma)) | botones_temporal;
    botones_temporal = mando_siete->boton_apretado & MASCARA_REPETICION;
    mando_siete->boton_apretado = (botones_ant_circuito_fantasma & (botones ^ botones_ant_circuito_fantasma)) | botones_temporal;
    botones_ant_circuito_fantasma = botones;
    mando_siete->button = botones;
    if (circuito_fantasma_frames_restante == 0) {
        circuito_fantasma_repeticion_idx++;
        circuito_fantasma_frames_restante = (s32) (repeticion_fantasma_circuito[circuito_fantasma_repeticion_idx] & CONTADOR_FRAME_REPETICION);
    } else {
        circuito_fantasma_frames_restante -= (s32) INCREMENTAR_FRAME_REPETICION;
    }
}

void procesar_repeticion_fantasma_jugador(void) {
    u32 entradas;
    u32 bytes_palanca;
    SIN_USO u16 desconocido;
    u16 temporal_botones;
    s16 val_palanca;
    s16 botones = 0;

    if (jugador_fantasma_repeticion_idx >= 0x1000) {
        funcion_80005AE8(jugador_dos);
        return;
    }
    entradas = repeticion_fantasma_jugador[jugador_fantasma_repeticion_idx];
    bytes_palanca = entradas & PALANCA_X_REPETICION;
    if (bytes_palanca < 0x80U) {
        val_palanca = (s16) (bytes_palanca & 0xFF);
    } else {
        val_palanca = (s16) (bytes_palanca | ~0xFF);
    }

    bytes_palanca = (u32) (entradas & PALANCA_Y_REPETICION) >> 8;

    mando_seis->palanca_x_crudo = val_palanca;

    if (bytes_palanca < 0x80U) {
        val_palanca = (s16) (bytes_palanca & 0xFF);
    } else {
        val_palanca = (s16) (bytes_palanca | (~0xFF));
    }

    mando_seis->palanca_y_crudo = val_palanca;

    if (entradas & BOTON_REPETICION_A) {
        botones = A_BUTTON;
    }
    if (entradas & BOTON_REPETICION_B) {
        botones |= B_BUTTON;
    }
    if (entradas & TRIG_REPETICION_Z) {
        botones |= Z_TRIG;
    }
    if (entradas & TRIG_REPETICION_R) {
        botones |= R_TRIG;
    }
    temporal_botones = mando_seis->boton_pulsado & MASCARA_REPETICION;
    mando_seis->boton_pulsado = (botones & (botones ^ jugador_fantasma_botones_ant)) | temporal_botones;

    temporal_botones = mando_seis->boton_apretado & MASCARA_REPETICION;
    mando_seis->boton_apretado = (jugador_fantasma_botones_ant & (botones ^ jugador_fantasma_botones_ant)) | temporal_botones;
    jugador_fantasma_botones_ant = botones;
    mando_seis->button = botones;

    if (jugador_fantasma_frames_restante == 0) {
        jugador_fantasma_repeticion_idx++;
        jugador_fantasma_frames_restante = (s32) (repeticion_fantasma_jugador[jugador_fantasma_repeticion_idx] & CONTADOR_FRAME_REPETICION);
    } else {
        jugador_fantasma_frames_restante -= (s32) INCREMENTAR_FRAME_REPETICION;
    }
}

void guardar_repeticion_jugador(void) {
    s16 botones;
    u32 entradas;
    u32 palanca_x;
    u32 palanca_y;
    u32 contador_entrada;
    u32 contador_entradas_w_ant;
    u32 entradas_ant;
    if (((idx_entrada_jugador >= 0x1000) || ((jugador_uno->lakitu_props & MANTENIDO_POR_LAKITU) != 0)) ||
        ((jugador_uno->lakitu_props & LAKITU_ESCENA) != 0)) {
        publicar_contrarreloj_guardado_no_puede_repeticion = 1;
        return;
    }

    palanca_x = mando_uno->palanca_x_crudo;
    palanca_x &= 0xFF;
    palanca_y = mando_uno->palanca_y_crudo;
    palanca_y = (palanca_y & 0xFF) << 8;
    botones = mando_uno->button;
    entradas = 0;
    if (botones & A_BUTTON) {
        entradas |= BOTON_REPETICION_A;
    }
    if (botones & B_BUTTON) {
        entradas |= BOTON_REPETICION_B;
    }
    if (botones & Z_TRIG) {
        entradas |= TRIG_REPETICION_Z;
    }
    if (botones & R_TRIG) {
        entradas |= TRIG_REPETICION_R;
    }
    entradas |= palanca_x;
    entradas |= palanca_y;
    contador_entradas_w_ant = entradas_jugador[idx_entrada_jugador];
    entradas_ant = contador_entradas_w_ant & REPETICION_LIMPIEZA_FRAME_CONTADOR;
    if ((*entradas_jugador) == -1) {

        entradas_jugador[idx_entrada_jugador] = entradas;

    } else if (entradas_ant == entradas) {

        contador_entrada = contador_entradas_w_ant & CONTADOR_FRAME_REPETICION;

        if (contador_entrada == CONTADOR_FRAME_REPETICION) {

            idx_entrada_jugador++;
            entradas_jugador[idx_entrada_jugador] = entradas;

        } else {
            contador_entradas_w_ant += INCREMENTAR_FRAME_REPETICION;
            entradas_jugador[idx_entrada_jugador] = contador_entradas_w_ant;
        }
    } else {
        idx_entrada_jugador++;
        entradas_jugador[idx_entrada_jugador] = entradas;
    }
}

void funcion_80005AE8(Jugador* ply) {
    if (((ply->type & INVISIBLE_JUGADOR_O_BOMBA) != 0) && (ply != jugador_uno)) {
        ply->type = MODO_CINEMATICA_JUGADOR | SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR;
    }
}

void funcion_80005B18(void) {
    if (seleccion_modo == CONTRARRELOJ) {
        if ((cantidad_vuelta_por_id_jugador[0] == 3) && (dato_80162DDC == 0) && (publicar_contrarreloj_guardado_no_puede_repeticion != 1)) {
            if (b_jugador_fantasma_desactivado == 1) {
                dato_80162DD0 = dato_80162DCC;
                funcion_800052A4();
                b_jugador_fantasma_desactivado = 0;
                dato_80162DDC = 1;
                dato_80162DE0 = jugador_uno->id_personaje;
                dato_80162DE8 = jugador_uno->id_personaje;
                dato_80162E00 = 0;
                dato_80162DFC = h_ud_jugador[JUGADOR_UNO].algun_temporizador;
                funcion_80005AE8(jugador_dos);
                funcion_80005AE8(jugador_tres);
            } else if (cantidad_vuelta_por_id_jugador[1] != 3) {
                dato_80162DD0 = dato_80162DCC;
                funcion_800052A4();
                dato_80162DDC = 1;
                dato_80162DE0 = jugador_uno->id_personaje;
                dato_80162DFC = h_ud_jugador[JUGADOR_UNO].algun_temporizador;
                dato_80162E00 = 0;
                dato_80162DE8 = jugador_uno->id_personaje;
                funcion_80005AE8(jugador_dos);
                funcion_80005AE8(jugador_tres);
            } else {
                buffer_fantasma_repeticion = dato_802BFB80.tamanio_arreglo_8[0][dato_80162DC8][3].arreglo_indice_pixel;
                repeticion_fantasma_buffer_tamanio = dato_80162D86;
                dato_80162DD0 = dato_80162DCC;
                dato_80162DE8 = jugador_uno->id_personaje;
                dato_80162DD8 = 0;
                b_jugador_fantasma_desactivado = 0;
                dato_80162DDC = 1;
                funcion_80005AE8(jugador_dos);
                funcion_80005AE8(jugador_tres);
            }
        } else {
            if ((cantidad_vuelta_por_id_jugador[0] == 3) && (dato_80162DDC == 0) && (publicar_contrarreloj_guardado_no_puede_repeticion == 1)) {
                buffer_fantasma_repeticion = dato_802BFB80.tamanio_arreglo_8[0][dato_80162DC8][3].arreglo_indice_pixel;
                repeticion_fantasma_buffer_tamanio = dato_80162D86;
                dato_80162DDC = 1;
            }
            if ((jugador_uno->type & MODO_CINEMATICA_JUGADOR) == MODO_CINEMATICA_JUGADOR) {
                funcion_80005AE8(jugador_dos);
                funcion_80005AE8(jugador_tres);
            } else {
                contador_repeticion_sin_uso += 1;
                if (contador_repeticion_sin_uso > 100) {
                    contador_repeticion_sin_uso = 100;
                }
                if ((seleccion_modo == CONTRARRELOJ) && (modo_pantalla_activo == MODO_PANTALLA_1P)) {
                    if ((b_jugador_fantasma_desactivado == 0) && (cantidad_vuelta_por_id_jugador[1] != 3)) {
                        procesar_repeticion_fantasma_jugador();
                    }
                    if ((b_circuito_fantasma_desactivado == 0) && (cantidad_vuelta_por_id_jugador[2] != 3)) {
                        procesar_repeticion_fantasma_circuito();
                    }
                    if (!(jugador_uno->type & MODO_CINEMATICA_JUGADOR)) {
                        guardar_repeticion_jugador();
                    }
                }
            }
        }
    }
}

void funcion_80005E6C(void) {
    if ((seleccion_modo == CONTRARRELOJ) && (seleccion_modo == CONTRARRELOJ) && (modo_pantalla_activo == MODO_PANTALLA_1P)) {
        if ((dato_80162DD8 == 0) && (cantidad_vuelta_por_id_jugador[1] != 3)) {
            procesar_repeticion_fantasma_jugador();
        }
        if ((b_circuito_fantasma_desactivado == 0) && (cantidad_vuelta_por_id_jugador[2] != 3)) {
            procesar_repeticion_fantasma_circuito();
        }
        if ((jugador_uno->type & MODO_CINEMATICA_JUGADOR) != MODO_CINEMATICA_JUGADOR) {
            publicar_contrarreloj_repeticion_proceso();
            return;
        }
        funcion_80005AE8(jugador_dos);
        funcion_80005AE8(jugador_tres);
    }
}

void bucle_repeticiones(void) {
    if (dato_8015F890 == 1) {
        funcion_80005E6C();
        return;
    }
    if (!pausa_disparado) {
        funcion_80005B18();
        return;
    }
    publicar_contrarreloj_guardado_no_puede_repeticion = 1;
}
