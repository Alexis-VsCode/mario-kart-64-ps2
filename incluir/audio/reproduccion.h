#ifndef AUDIO_REPRODUCCION_H
#define AUDIO_REPRODUCCION_H

#include <PR/ultratypes.h>

#include "interno.h"

#define CAPA_RESERVA_NOTA 1
#define CANAL_RESERVA_NOTA 2
#define SEC_RESERVA_NOTA 4
#define NOTA_RESERVA_GLOBAL_LISTA_LIBRES 8

void fijar_reverb_paneo_vel_nota(struct Nota* nota, f32 velocidad, u8 paneo, u8 reverb_vol);
void fijar_tasa_remuestreo_nota(struct Nota* nota, f32 entrada_tasa_remuestreo);
s32 construir_ola_sintetico(struct Nota* nota, struct CapaCanalSecuencia* sec_capa, s32 id_ola);
void inicializar_ola_sintetico(struct Nota* nota, struct CapaCanalSecuencia* sec_capa);
void inicializar_lista_nota(struct ItemListaAudio* lista);
void inicializar_listas_nota(struct PoolNota* pool);
void liberar_lista_nota_inicializacion(void);
void borrar_pool_nota(struct PoolNota* pool);
void relleno_pool_nota(struct PoolNota* pool, s32 cantidad);
void empujar_frente_lista_audio(struct ItemListaAudio* lista, struct ItemListaAudio* item);
void quitar_lista_audio(struct ItemListaAudio* item);
struct Nota* sacar_nodo_con_prio_inferior(struct ItemListaAudio* lista, s32 limite);
void inicializar_para_capa_nota(struct Nota* nota, struct CapaCanalSecuencia* sec_capa);
void desactivar_nota(struct Nota* nota);
void procesar_notas(void);
struct SonidoBancoAudio* obtener_sonido_banco_audio_instrumento(struct Instrumento* instrumento, s32 semitono);
struct Instrumento* obtener_interior_instrumento(s32 id_banco, s32 inst_id);
struct Tambor* obtener_tambor(s32 id_banco, s32 id_tambor);
void inicializar_nota(struct Nota* nota);
void sec_canal_capa_decaer_suelta_interno(struct CapaCanalSecuencia* sec_capa, s32 objetivo);
void sec_canal_capa_nota_decaer(struct CapaCanalSecuencia* sec_capa);
void sec_canal_capa_nota_suelta(struct CapaCanalSecuencia* sec_capa);
void funcion_800BD8F4(struct Nota* nota, struct CapaCanalSecuencia* sec_capa);
void suelta_nota_y_propiedad_tomar(struct Nota* nota, struct CapaCanalSecuencia* sec_capa);
struct Nota* reservar_nota_desde_desactivado(struct PoolNota* pool, struct CapaCanalSecuencia* sec_capa);
struct Nota* reservar_nota_desde_decayendo(struct PoolNota* pool, struct CapaCanalSecuencia* sec_capa);
struct Nota* reservar_nota_desde_activo(struct PoolNota* pool, struct CapaCanalSecuencia* sec_capa);
struct Nota* reservar_nota(struct CapaCanalSecuencia* sec_capa);
void inicializar_all_nota(void);

#endif
