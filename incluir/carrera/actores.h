#ifndef CARRERA_ACTORES_H
#define CARRERA_ACTORES_H

#include "juego/tipos_actores.h"
#include "carrera/preparacion_carrera.h"
#include "carrera/camara.h"

#define FIN_DE_DATOS_APARICION -0x8000

void limpiar_rojo_y_caparazones_verdes(struct ActorCaparazon*);
void inicializar_actor(struct Actor*, Vec3f, Vec3s, Vec3f, s16);
void actor_no_renderizado(Camara*, struct Actor*);
void actor_renderizado(Camara*, struct Actor*);
void funcion_80297340(Camara*);
void funcion_802976D8(Vec3s);
void funcion_802976EC(Colision*, Vec3s);
void funcion_80297760(struct Actor*, Vec3f);
void funcion_802977B0(Jugador*);
void funcion_802977E4(Jugador*);
void inicializar_caparazon_rojo_textura(void);
void funcion_8029794C(Vec3f, Vec3s, f32);
void funcion_802979F8(struct Actor*, f32);
void renderizar_vaca_actor(Camara*, Mat4, struct Actor*);
void actualizar_actor_yoshi_huevo(struct YoshiValleyHuevo*);
void actualizar_planta_estatico_actor(struct Actor*);
void actualizar_actor_kiwano_fruta(struct KiwanoFruta*);
void actualizar_barco_paleta_actor(struct BarcoRuedaPaleta*);
void actualizar_motor_tren_actor(struct AutomovilTren*);
void actualizar_tender_tren_actor(struct AutomovilTren*);
void actualizar_actor_tren_pasajero_automovil(struct AutomovilTren*);
void actualizar_actor_planta_piranha(struct PlantaPiranha*);
void renderizar_actor_planta_piranha(Camara*, Mat4, struct PlantaPiranha*);
void renderizar_vacas(Camara*, Mat4, struct Actor*);
void evaluar_colision_jugador_palmera_arboles(Jugador*);
void evaluar_colision_jugadores_palmera_arboles(void);
void funcion_80298D10(void);
void renderizar_arboles_palmera(Camara*, Mat4, struct Actor*);
void renderizar_arbol_actor_mario_raceway(Camara*, Mat4, struct Actor*);
void renderizar_arbol_actor_yoshi_valley(Camara*, Mat4, struct Actor*);
void renderizar_arbol_actor_royal_raceway(Camara*, Mat4, struct Actor*);
void renderizar_arbol_actor_moo_moo_farm(Camara*, Mat4, struct Actor*);
void funcion_80299864(Camara*, Mat4, struct Actor*);
void renderizar_arbol_actor_bowser_castle(Camara*, Mat4, struct Actor*);
void renderizar_arbusto_actor_bowser_castle(Camara*, Mat4, struct Actor*);
void renderizar_arbol_actor_frappe_snowland(Camara*, Mat4, struct Actor*);
void renderizar_cactus1_arbol_actor_kalimari_desert(Camara*, Mat4, struct Actor*);
void renderizar_cactus2_arbol_actor_kalimari_desert(Camara*, Mat4, struct Actor*);
void renderizar_cactus3_arbol_actor_kalimari_desert(Camara*, Mat4, struct Actor*);
void renderizar_actor_kiwano_fruta(Camara*, Mat4, struct Actor*);
void renderizar_caparazon_actor(Camara*, Mat4, struct ActorCaparazon*);
void renderizar_actor_caparazon_verde(Camara*, Mat4, struct ActorCaparazon*);
void renderizar_actor_caparazon_rojo(Camara*, Mat4, struct ActorCaparazon*);
void renderizar_actor_caparazon_azul(Camara*, Mat4, struct ActorCaparazon*);
void renderizar_banana_actor(Camara*, Mat4, struct BananaActor*);
void actualizar_actor_wario_cartel(struct Actor*);
void actualizar_actor_paso_a_nivel(struct PasoANivel*);
void actualizar_actor_mario_cartel(struct Actor*);
void funcion_8029AC18(Camara*, Mat4, struct Actor*);
void renderizar_barco_paleta_actor(Camara*, struct BarcoRuedaPaleta*, Mat4, u16);
void renderizar_camion_caja_actor(Camara*, struct Actor*);
void renderizar_omnibus_escuela_actor(Camara*, struct Actor*);
void renderizar_automovil_actor(Camara*, struct Actor*);
void renderizar_camion_cisterna_actor(Camara*, struct Actor*);
void renderizar_motor_tren_actor(Camara*, struct AutomovilTren*);
void renderizar_tender_tren_actor(Camara*, struct AutomovilTren*);
void renderizar_actor_tren_pasajero_automovil(Camara*, struct AutomovilTren*);
void renderizar_roca_cayendo_actor(Camara*, struct RocaCayendo*);
void aparecer_plantas_piranha(struct DatosAparicionActor*);
void aparecer_arboles_palmera(struct DatosAparicionActor*);
void funcion_8029CF0C(struct DatosAparicionActor*, struct RocaCayendo*);
void aparecer_rocas_cayendo(struct DatosAparicionActor*);
void actualizar_rocas_cayendo_actor(struct RocaCayendo*);
void aparecer_follaje(struct DatosAparicionActor*);
void aparecer_todos_cajas_item(struct DatosAparicionActor*);
void inicializar_kiwano_fruta(void);
void destruir_todos_actores(void);
void aparecer_actores_circuito(void);
void cargar_texturas_actores_inicializacion_y(void);
void quitar_sonido_juego_antes(struct Actor*);
void destruir_actor(struct Actor*);
s16 quitar_item_destructible_intentar(Vec3f, Vec3s, Vec3f, s16);
s16 agregar_actor_a_ranura_vacio(Vec3f, Vec3s, Vec3f, s16);
s16 aparecer_actor_en_pos(Vec3f, s16);
bool consultar_y_resolver_colision_jugador_actor(Jugador*, Vec3f, f32, f32, f32);
bool colision_mario_cartel(Jugador*, struct Actor*);
bool colision_planta_piranha(Jugador*, struct PlantaPiranha*);
bool colision_yoshi_huevo(Jugador*, struct YoshiValleyHuevo*);
bool arbol_colision(Jugador*, struct Actor*);
bool consultar_jugador_colision_vs_item_actor(Jugador*, struct Actor*);
bool consultar_actor_colision_vs_actor(struct Actor*, struct Actor*);
void destruir_actor_destructible(struct Actor*);
void reproducir_sonido_en_colision_actor_destructible(struct Actor*, struct Actor*);
void evaluar_colision_actor_entre_dos_actores_destructible(struct Actor*, struct Actor*);
void evaluar_colision_entre_actor_jugador(Jugador*, struct Actor*);
void evaluar_colision_para_jugadores_y_actores(void);
void evaluar_colision_para_actores_destructible(void);
void funcion_802A1064(struct CajaItemFalsa*);
void actualizar_actor_caja_item_falsa(struct CajaItemFalsa*);
void inicializar_actor_globo_aerostatico_caja_item(f32, f32, f32);
void actualizar_actor_caja_item_globo_aerostatico(struct CajaItem*);
void actualizar_actor_caja_item(struct CajaItem*);
void renderizar_actor_caja_item_falsa(Camara*, struct CajaItemFalsa*);
void renderizar_actor_caja_item(Camara*, struct CajaItem*);
void renderizar_actor_wario_cartel(Camara*, struct Actor*);
void renderizar_actor_yoshi_huevo(Camara*, Mat4, struct YoshiValleyHuevo*, u16);
void renderizar_actor_mario_cartel(Camara*, Mat4, struct Actor*);
void renderizar_actor_paso_a_nivel(Camara*, struct PasoANivel*);
void renderizar_arbol_palmera_actor(Camara*, Mat4, struct ArbolPalmera*);
void renderizar_cajas_item(struct desconocido_struct_800DC5EC*);
void renderizar_actores_circuito(struct desconocido_struct_800DC5EC*);
void actualizar_actores_circuito(void);

extern void funcion_800C98B8(Vec3f, Vec3f, u32);
extern void funcion_800C99E0(Vec3f, s32);

extern u8* dato_802BA050;
extern u8* dato_802BA054;
extern u8* dato_802BA058;
extern struct Actor* actor_globo_aerostatico_caja_item;
extern s8 tlut_caparazon_rojo[];
extern u16 dato_802BA260;

extern u16 es_cruce_disparado_por_indice[];
extern Lights1 dato_800DC610[];

extern Gfx dato_0D005338[];
extern Gfx dato_0D005368[];
extern Gfx dato_0D007B20[];

extern Gfx toads_turnpike_dl_0[];
extern Gfx toads_turnpike_dl_1[];
extern Gfx toads_turnpike_dl_2[];
extern Gfx toads_turnpike_dl_3[];
extern Gfx toads_turnpike_dl_4[];
extern Gfx toads_turnpike_dl_5[];
extern Gfx toads_turnpike_dl_6[];
extern Gfx toads_turnpike_dl_7[];
extern Gfx toads_turnpike_dl_8[];
extern Gfx toads_turnpike_dl_9[];
extern Gfx toads_turnpike_dl_10[];
extern Gfx toads_turnpike_dl_11[];

extern s32 publicar_contrarreloj_guardado_no_puede_repeticion;

extern Gfx dato_0D001750[];
extern Gfx dato_0D001780[];
extern Gfx dato_0D001798[];
extern Gfx dato_0D0017B0[];
extern Gfx dato_0D0017C8[];
extern Gfx dato_0D0017E0[];
extern Gfx dato_0D0017F8[];
extern Gfx dato_0D001810[];
extern Gfx dato_0D001828[];
extern Gfx dato_0D001B90[];
extern Gfx dato_0D001BD8[];
extern Gfx dato_0D001C20[];
extern Gfx dato_0D001C88[];
extern Gfx dato_0D002EE8[];
extern Gfx comun_modelo_falso_caja_item[];
extern Gfx caja_item_signo_pregunta_modelo[];
extern Gfx dato_0D003090[];
extern Gfx dato_0D0030F8[];
extern Gfx dato_0D003128[];
extern Gfx dato_0D003158[];
extern Gfx dato_0D003188[];
extern Gfx dato_0D0031B8[];
extern Gfx dato_0D0031E8[];
extern Gfx banana_modelo_comun[];
extern Gfx comun_modelo_plano_banana[];

extern s8 dato_800DC628[];
extern s8 dato_800DC630[];
extern s8 dato_802B8864[];

#endif
