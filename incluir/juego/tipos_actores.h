#ifndef JUEGO_TIPOS_ACTORES_H
#define JUEGO_TIPOS_ACTORES_H

#include <ultra64.h>
#include <juego/macros.h>
#include <juego/estructuras_comunes.h>

enum TipoActor {
    actor_desconocido_0_x01 = 0x01,
    ARBOL_ACTOR_MARIO_RACEWAY,
    ARBOL_ACTOR_YOSHI_VALLEY,
    ARBOL_ACTOR_ROYAL_RACEWAY,
    ROCA_CAYENDO_ACTOR,
    ACTOR_BANANA,
    ACTOR_CAPARAZON_VERDE,
    ACTOR_CAPARAZON_ROJO,
    ACTOR_YOSHI_HUEVO,
    ACTOR_PLANTA_PIRANHA,
    actor_desconocido_0_x0_b,
    ACTOR_CAJA_ITEM,
    ACTOR_CAJA_ITEM_FALSA,
    GRUPO_BANANA_ACTOR,
    MOTOR_TREN_ACTOR,
    TENDER_TREN_ACTOR,
    ACTOR_TREN_PASAJERO_AUTOMOVIL,
    VACA_ACTOR,
    ARBOL_ACTOR_MOO_MOO_FARM,
    actor_desconocido_0_x14,
    TRIPLE_ACTOR_CAPARAZON_VERDE,
    TRIPLE_ACTOR_CAPARAZON_ROJO,
    ACTOR_MARIO_CARTEL,
    actor_desconocido_0_x18,
    ARBOL_PALMERA_ACTOR,
    actor_desconocido_0_x1_a,
    actor_desconocido_0_x1_b,
    ARBOL_ACTOR_BOWSERS_CASTLE,
    ARBOL_ACTOR_FRAPPE_SNOWLAND,
    CACTUS1_ACTOR_KALAMARI_DESERT,
    CACTUS2_ACTOR_KALAMARI_DESERT,
    CACTUS3_ACTOR_KALAMARI_DESERT,
    ARBUSTO_ACTOR_BOWSERS_CASTLE,
    actor_desconocido_0_x21,
    ACTOR_WARIO_CARTEL,
    actor_desconocido_0_x23,
    CAMION_CAJA_ACTOR,
    BARCO_PALETA_ACTOR,
    ACTOR_PASO_A_NIVEL,
    OMNIBUS_ESCUELA_ACTOR,
    CAMION_CISTERNA_ACTOR,
    AZUL_ACTOR_CAPARAZON_ESPINOSO,
    ACTOR_GLOBO_AEROSTATICO_CAJA_ITEM,
    AUTOMOVIL_ACTOR,
    ACTOR_KIWANO_FRUTA
};

#define TAMANIO_LISTA_ACTOR 100

#define ES_ACTOR_NO_VENCIDO 0xF

enum EstadoCaparazon {
    CAPARAZON_MANTENIDO,
    CAPARAZON_SOLTADO,
    CAPARAZON_MOVIENDO,
    CAPARAZON_ROJO_BLOQUEO_EN,
    TRIPLE_CAPARAZON_VERDE,
    CAPARAZON_VERDE_CORREDOR_GOLPE_A,
    TRIPLE_CAPARAZON_ROJO,
    CAPARAZON_DESTRUIDO,
    CAPARAZON_AZUL_BLOQUEO_EN,
    CAPARAZON_AZUL_OBJETIVO_ELIMINADO
};

enum EstadoBanana {
    BANANA_MANTENIDO,
    BANANA_SOLTADO,
    PRIMER_BANANA_GRUPO_BANANA,
    BANANA_GRUPO_BANANA,
    BANANA_EN_SUELO,
    BANANA_DESTRUIDO
};

#define MANTENIDO_CAJA_ITEM_FALSA 0
#define CAJA_ITEM_FALSA_EN_SUELO 1
#define DESTRUIDO_CAJA_ITEM_FALSA 2

struct Actor {
     s16 type;
     s16 flags;
     s16 desconocido_04;
     s16 state;
     f32 desconocido_08;
     f32 tamanio_caja_envolvente;
     Vec3s rot;
     s16 desconocido_16;
     Vec3f pos;
     Vec3f velocidad;
     Colision desconocido30;
};

extern struct Actor lista_actor[TAMANIO_LISTA_ACTOR];

struct AutomovilTren {
     s16 type;
     s16 flags;
     s16 desconocido_04;
     s16 rot_rueda;
     f32 desconocido_08;
     f32 desconocido_0C;
     Vec3s rot;
     s16 desconocido_16;
     Vec3f pos;
     Vec3f velocidad;
     Colision desconocido30;
};

struct PasoANivel {
     s16 type;
     s16 flags;
     s16 algun_temporizador;
     s16 id_cruce;
     f32 desconocido_08;
     f32 desconocido_0C;
     Vec3s rot;
     s16 desconocido_16;
     Vec3f pos;
     Vec3f velocidad;
     Colision desconocido30;
};

struct RocaCayendo {
     s16 type;
     s16 flags;
     s16 temporizador_reaparicion;
     s16 desconocido_06;
     f32 desconocido_08;
     f32 tamanio_caja_envolvente;
     Vec3s rot;
     s16 desconocido_16;
     Vec3f pos;
     Vec3f velocidad;
     Colision desconocido30;
};

struct DatosAparicionActor {
     Vec3s pos;
    union {
         u16 algun_id;
         s16 id_algun_con_signo;
    };
};

struct DesconocidoActorAparicionDatos {
     Vec3s pos;
     s16 algun_id;
     s16 desconocido8;
};

struct YoshiValleyHuevo {
     s16 type;
     s16 flags;
     s16 desconocido_04;
     s16 desconocido_06;
     f32 radio_camino;
     f32 tamanio_caja_envolvente;
     s16 rot_camino;
     s16 rot_huevo;
     s16 desconocido_14;
     s16 desconocido_16;
     Vec3f pos;
     Vec3f centro_camino;
     Colision desconocido30;
};

struct KiwanoFruta {
     s16 type;
     s16 flags;
     s16
        jugador_objetivo;
     s16 state;
     f32 temporizador_golpe;
     f32 tamanio_caja_envolvente;
     s16 anim_estado;
     s16 anim_temporizador;
     s16 desconocido_14;
     s16 desconocido_16;
     Vec3f pos;
     Vec3f velocidad;
     Colision desconocido30;
};

struct BarcoRuedaPaleta {
     s16 type;
     s16 flags;
     s16 desconocido_04;
     s16 rot_rueda;
     f32 desconocido_08;
     f32 desconocido_0C;
     Vec3s rot_barco;
     s16 desconocido_16;
     Vec3f pos;
     Vec3f velocidad;
     Colision desconocido30;
};

struct PlantaPiranha {
     s16 type;
     s16 flags;
     Vec4s estados_visibilidad;
     f32 tamanio_caja_envolvente;
     Vec4s unk10;
     Vec3f pos;
     Vec4s temporizadores;
     f32 desconocido_02C;
     Colision desconocido30;
};

struct ArbolPalmera {
     s16 type;
     s16 flags;
     s16 variante;
     s16 state;
     f32 desconocido_08;
     f32 tamanio_caja_envolvente;
     Vec3s rot;
     s16 desconocido_16;
     Vec3f pos;
     Vec3f velocidad;
     Colision desconocido30;
};

typedef struct {
     s16 type;
     s16 flags;
     s16 disponible_caparazones;
     s16 state;
     f32 desconocido_08;
     f32 desconocido_0C;
     s16 velocidad_rot;
     s16 angulo_rot;
     s16 id_jugador;
     s16 desconocido_16;
     Vec3f desconocido_18;
     Vec3f indices_caparazon;
     Colision desconocido30;
} TriplePadreCaparazon;

struct ActorCaparazon {
     s16 type;
     s16 flags;
    union {
         s16 indice_padre;
         s16 algun_temporizador;
         s16 jugador_objetivo;
    };
     s16 state;
     f32 id_caparazon;
     f32 tamanio_caja_envolvente;
     s16 velocidad_rot;
    union {
         s16 angulo_rot;
         u16 indice_camino;
    };
     s16 id_jugador;
     s16 desconocido_16;
     Vec3f pos;
     Vec3f velocidad;
     Colision desconocido30;
};

struct CajaItem {
     s16 type;
     s16 flags;
     s16 algun_temporizador;
     s16 state;
     f32 distancia_reinicio;
     f32 tamanio_caja_envolvente;
     Vec3s rot;
     s16 desconocido_16;
     Vec3f pos;
     f32 orig_y;
     f32 desconocido_028;
     f32 desconocido_02C;
     Colision desconocido30;
};

struct CajaItemFalsa {
     s16 type;
     s16 flags;
     s16 algun_temporizador;
     s16 state;
     f32 escalado_tamanio;
     f32 tamanio_caja_envolvente;
     Vec3s rot;
     s16 desconocido_16;
     Vec3f pos;
     f32 id_jugador;
     f32 objetivo_y;
     f32 desconocido_02C;
     Colision desconocido30;
};

struct PadreGrupoBanana {
     s16 type;
     s16 flags;
     s16 desconocido_04;
     s16 state;
     f32 desconocido_08;
     f32 desconocido_0C;
     s16 id_jugador;
     s16 banana_indices[5];
     s16 disponible_bananas;
     s16 desconocido_1E;
     f32 desconocido_20[4];
     Colision desconocido30;
};

struct BananaActor {
     s16 type;
     s16 flags;
     s16 desconocido_04;
     s16 state;
     s16 indice_padre;
     s16 banana_id;
     f32 tamanio_caja_envolvente;
    union {
         Vec3s rot;
        struct {
             s16 id_jugador;
             s16 indice_mayor;
             s16 indice_menor;
        };
    };
     s16 desconocido_16;
     Vec3f pos;
     Vec3f velocidad;
     Colision desconocido30;
};

#endif
