#ifndef AUDIO_REPRODUCTOR_SECUENCIAS_H
#define AUDIO_REPRODUCTOR_SECUENCIAS_H

#include <PR/ultratypes.h>

#include "audio/interno.h"

#define ESPECIAL_ES_PORTAMENTO(x) ((x).mode & 0x80)
#define MODO_PORTAMENTO(x) ((x).mode & ~0x80)
#define MODO_PORTAMENTO_1 1
#define MODO_PORTAMENTO_2 2
#define MODO_PORTAMENTO_3 3
#define MODO_PORTAMENTO_4 4
#define MODO_PORTAMENTO_5 5

void inicializar_canal_secuencia(struct CanalSecuencia* sec_canal);
s32 sec_capa_conjunto_canal(struct CanalSecuencia* sec_canal, s32 indice_capa);
void sec_desactivar_capa_canal(struct CapaCanalSecuencia* capa);
void sec_libre_capa_canal(struct CanalSecuencia* sec_canal, s32 indice_capa);
void desactivar_canal_secuencia(struct CanalSecuencia* sec_canal);
struct CanalSecuencia* reservar_canal_secuencia(void);
void inicializar_canales_jugador_secuencia(struct JugadorSecuencia* sec_jugador, u16 bits_canal);
void desactivar_canales_jugador_secuencia(struct JugadorSecuencia* sec_jugador, u16 bits_canal);
void activar_canal_secuencia(struct JugadorSecuencia* sec_jugador, u8 indice_canal, void* guion);
void desactivar_jugador_secuencia(struct JugadorSecuencia* sec_jugador);
void funcion_800BEF2C(struct JugadorSecuencia* sec_jugador);
void empujar_atras_lista_audio(struct ItemListaAudio* lista, struct ItemListaAudio* item);
void* sacar_atras_lista_audio(struct ItemListaAudio* lista);
void inicializar_lista_libres_capa(void);
u8 leer_m64_u8(struct EstadoGuionM64* estado);
s16 leer_m64_s16(struct EstadoGuionM64* estado);
u16 leer_comprimido_m64_u16(struct EstadoGuionM64* estado);
u8 obtener_instrumento(struct CanalSecuencia* sec_canal, u8 inst_id, struct Instrumento** salida_inst,
                  struct AjustesAdsr* adsr);
void procesar_secuencias(s32);
void fijar_instrumento(struct CanalSecuencia* sec_canal, u8 inst_id);
void fijar_volumen_canal_secuencia(struct CanalSecuencia* sec_canal, u8 volumen);
void sec_canal_capa_proceso_guion(struct CapaCanalSecuencia* capa);
void procesar_secuencia_jugador_secuencia(struct JugadorSecuencia*);
void procesar_guion_canal_secuencia(struct CanalSecuencia*);
void procesar_secuencias(s32);
void inicializar_jugador_secuencia(u32 jugador);
void inicializar_jugadores_secuencia(void);

#endif
