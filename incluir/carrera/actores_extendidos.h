#ifndef CARRERA_ACTORES_EXTENDIDOS_H
#define CARRERA_ACTORES_EXTENDIDOS_H

#include <juego/estructuras_comunes.h>
#include "juego/tipos_actores.h"

void copiar_colision(Colision*, Colision*);
void chocar_con_jugador_triple_actor_caparazon(struct ActorCaparazon*, s32);
void funcion_802B039C(struct BananaActor*);
void funcion_802B0464(s16);
void funcion_802B04E8(struct BananaActor*, s16);
void destruir_banana_en_grupo_banana(struct BananaActor*);
void soltar_banana_en_grupo_banana(struct PadreGrupoBanana*);
void funcion_802B0788(s16, struct PadreGrupoBanana*, Jugador*);
s32 funcion_802B09C0(s16);
void actualizar_grupo_banana_actor(struct PadreGrupoBanana*);
bool es_existe_caparazon(s16);
void actualizar_caparazon_triple_actor(TriplePadreCaparazon*, s16);
s32 usar_item_grupo_banana(Jugador*);
s32 usar_triple_item_caparazon(Jugador*, s16);
s32 inicializar_triple_caparazon(TriplePadreCaparazon*, Jugador*, s16, u16);
s32 usar_caparazon_verde_item(Jugador*);
s32 usar_caparazon_rojo_item(Jugador*);
void usar_caparazon_azul_item(Jugador*);
void actualizar_banana_actor(struct BananaActor*);
void funcion_802B2914(struct PadreGrupoBanana*, Jugador*, s16);
s32 usar_item_caja_item_falso(Jugador*);
s32 usar_item_banana(Jugador*);
void usar_item_trueno(Jugador*);
void item_usar_jugador(Jugador*);
void comprobar_item_usar_jugador(void);
void actualizar_actor_caparazon_verde(struct ActorCaparazon*);
void funcion_802B3B44(struct ActorCaparazon*);
void funcion_802B3E7C(struct ActorCaparazon*, Jugador*);
s16 funcion_802B3FD0(Jugador*, struct ActorCaparazon*);
void funcion_802B4104(struct ActorCaparazon*);
void actualizar_actor_rojo_caparazon_azul(struct ActorCaparazon*);
void funcion_802B4E30(struct Actor*);

extern void funcion_800CAB4C(u8);

extern f32 dato_802B9F68;

extern s16 cantidad_globo_jugador[];

#endif
