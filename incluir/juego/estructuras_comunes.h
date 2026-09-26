#ifndef JUEGO_ESTRUCTURAS_COMUNES_H
#define JUEGO_ESTRUCTURAS_COMUNES_H

#include <ultra64.h>

typedef f32 Vec3f[3];
typedef f32 Vec4f[4];

typedef s32 Vec3iu[3];

typedef s16 Vec3s[3];
typedef u16 Vec3su[3];
typedef s16 Vec4s[4];

typedef f32 Mat3[3][3];
typedef f32 Mat4[4][4];

typedef struct {
    f32 x, y, z;
} Vec3fs;

typedef enum { A = 0x80, B = 0x40, Z = 0x20, R = 0x10 } MandoFantasma;

typedef struct {
     s16 inicio_punto_camino;
     s16 fin_punto_camino;
     s32 type;
} ComportamientoCPU;

enum EstadoTareaSp {
    ESTADO_SPTASK_NO_EMPEZADO,
    EJECUTANDO_ESTADO_SPTASK,
    SPTASK_ESTADO_INTERRUMPIDO,
    SPTASK_ESTADO_TERMINADO,
    SPTASK_ESTADO_TERMINADO_DP
};

struct TareaSP {
     OSTask tarea;
     OSMesgQueue* msgqueue;
     OSMesg msg;
     enum EstadoTareaSp state;
};

struct ManejadorVblank {
    OSMesgQueue* queue;
    OSMesg msg;
};

struct dato_80150158 {
    s16 desconocido0;
    s32 desconocido4;
    s32 desconocido8;
    s32 desconocido_c;
};

struct Mando {
    s16 palanca_x_crudo;
    s16 palanca_y_crudo;
    u16 button;
    u16 boton_pulsado;
    u16 boton_apretado;
    u16 sentido_palanca;
    u16 palanca_pulsado;
    u16 palanca_apretado;
};

struct desconocido_struct_80287500 {
    Vec3f desconocido0;
    f32 desconocido_c;
    f32 unk10;
    f32 unk14;
    s32 unk18;
    s32 desconocido_1c;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 desconocido_2c;
    f32 desconocido30;
    f32 unk34;
    s32 unk38;
};

struct desconocido_struct_800DDB40 {
    u32 desconocido0;
    u32 desconocido4;
    u32 desconocido8;
    u32 desconocido_c;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 desconocido_1c;
    u32 unk20;
    u16 unk24;
    u16 desconocido26;
};

struct desconocido_struct_802B53C8 {
    f32 desconocido0;
    f32 desconocido4;
    f32 desconocido8;
    f32 desconocido_c;
};

struct desconocido_struct_800DDB68 {
    s32* dato_800ED600;
    s32* dato_800ED608;
    s32* dato_800ED610;
    s32* dato_800ED618;
    s32* dato_800ED620;
    s32* dato_800ED628;
    s32* dato_800ED630;
    s32* dato_800ED638;
};

typedef struct {
    u8 button;
    s8 duracion_frame;
    s8 palanca_y;
    s8 palanca_x;
} FantasmaPersonal;

typedef struct {
     u16 desconocido30;
     u16 desconocido32;
     u16 unk34;
     u16 indice_yx_malla;
     u16 indice_zy_malla;
     u16 indice_zx_malla;
     Vec3f distancia_superficie;
     Vec3f desconocido48;
     Vec3f desconocido54;
     Vec3f vector_orientacion;
     f32 desconocido_6c;
} Colision;

typedef struct {
     Vec3f pos;
     f32 scale;
     u16 desconocido_010;
     u16 type;
     f32 tipo_superficie;
     f32 desconocido_018;
     s16 vivo_es;
     s16 temporizador;
     s16 rotacion;
     s16 desconocido_022;
     f32 desconocido_024;
     f32 desconocido_028;
     s16 desconocido_02C;
     s16 desconocido_02E;
     s16 desconocido_030;
     s16 desconocido_032;
     s16 desconocido_034;
     s16 desconocido_036;
     s16 rojo;
     s16 verde;
     s16 azul;
     s16 alpha;
     s16 desconocido_040;
     s16 desconocido_042;
     s16 desconocido_044;
     s16 desconocido_046;
} Particula;

typedef struct {
    s16 ob[3];
    s16 tc[2];
    s8 ca[4];
} VtxCircuito;

typedef struct {
     u16 flags;
     u16 tipo_superficie;

     s16 min_x;
    s16 min_y;             // Minimum y coordinate
    s16 min_z;
    s16 max_x;
    s16 max_y;             // Maximum y coordinate
     s16 max_z;
     Vtx* vtx1;
    Vtx* vtx2;
    Vtx* vtx3;
     f32 normal_x;
     f32 normal_y;
     f32 normal_z;
     f32 distancia;
} TrianguloColision;

typedef struct {
     Vec3f pos;
     u8 tipo_superficie;
     u8 banderas_superficie;
     u16 indice_malla_colision;
     f32 altura_base;
     s32 desconocido_14;
} RuedaKart;

#define IZQUIERDA_FRENTE 0
#define DERECHA_FRENTE 1
#define IZQUIERDA_ATRAS 2
#define DERECHA_ATRAS 3

struct InteriorJugadorDesconocido {
     s16 desconocido0;
     s16 desconocido2;
     f32 desconocido4;
     f32 desconocido8;
     f32 desconocido_c;
     f32 unk10;
     f32 unk14;
     s16 unk18;
     s16 desconocido_1a;
     s16 desconocido_1c;
     s16 desconocido_1e;
     s16 unk20;
};

typedef struct {
     u16 type;
     u16 desconocido_002;
     s16 puesto_actual;
     u16 desconocido_006;
     s16 cantidad_vuelta;
     char desconocido_00A[0x2];
     s32 disparadores;
     s16 copia_item_actual;
     s16 desconocido_012;
     Vec3f pos;
     Vec3f pos_viejo;
     Vec3s rotacion;
     char desconocido_032[0x2];
     Vec3f velocidad;
     s16 desconocido_040;
     s16 desconocido_042;
     s16 kart_props;
     u16 desconocido_046;
     Vec4s desconocido_048;
     Vec4s desconocido_050;
     f32 desconocido_058;
     f32 desconocido_05C;
     f32 desconocido_060;
     Vec3f desconocido_064;
     f32 tamanio_caja_envolvente;
     f32 desconocido_074;
     s16 desconocido_078;
     s16 desconocido_07A;
     s32 posicion_giro;
     f32 potencia_impulso;
     f32 desconocido_084;
     f32 desconocido_088;
     f32 desconocido_08C;
     f32 desconocido_090;
     f32 speed;
     f32 desconocido_098;
     f32 actual_rapidez;
     f32 desconocido_0A0;
     f32 desconocido_0A4;
     s16 desconocido_0A8;
     s16 desconocido_0AA;
     s16 sentido_esquivar;
     s16 desconocido_0AE;
     s16 desconocido_0B0;
     s16 desconocido_0B2;
     u16 temporizador_esquivar;
     u16 graficos_kart;
     f32 inicializacion_acel_esquivar;
     u32 efectos;
     s16 desconocido_0C0;
     s16 desconocido_0C2;
     s16 acel_pendiente;
     s16 alpha;
     s16 desconocido_0C8;
     s16 lakitu_props;
     Vec4s desconocido_0CC;
     Vec4s desconocido_0D4;
     s16 temporizador_impulso;
     u16 oob_props;
     s16 desconocido_0E0;
     s16 desconocido_0E2;
     f32 desconocido_0E4;
     f32 desconocido_0E8;
     f32 velocidad_salto_kart;
     f32 tiron_salto_kart;
     f32 aceleracion_salto_kart;
     u16 tipo_superficie;
     s16 delta_posicion_giro;
     f32 friccion_kart;
     f32 gravedad_kart;
     f32 desconocido_104;
     f32 desconocido_108;
     s16 desconocido_10C;
     char desconocido_10E[0x2];
     Colision colision;
     Mat3 desconocido_150;
     Mat3 matriz_orientacion;
     RuedaKart ruedas[4];
     f32 desconocido_1F8;
     f32 desconocido_1FC;
     u32 incrementar_cambio_giro;
     s16 duracion_derrape;
     s16 desconocido_206;
     f32 desconocido_208;
     f32 desconocido_20C;
     f32 desconocido_210;
     f32 arriba_rapidez;
     f32 desconocido_218;
     f32 desconocido_21C;
     s16 mas_cercano_camino_punto_id;
     s16 desconocido_222;
     f32 size;
     s16 contador_estado_derrape;
     s16 estado_derrape;
     f32 anterior_rapidez;
     f32 desconocido_230;
     s16 desconocido_234;
     s16 desconocido_236;
     s16 desconocido_238;
     s16 desconocido_23A;
     f32 desconocido_23C;
     s32 rueda_rapidez;
     u16 anim_frame_selector[4];
     u16 anim_selector_grupo[4];
     u16 id_personaje;
     u16 desconocido_256;
     Particula pool_particula_0[10];
     Particula pool_particula_1[10];
     Particula pool_particula_2[10];
     Particula pool_particula_3[10];
     s16 desconocido_D98;
     s16 desconocido_D9A;
     f32 desconocido_D9C;
     f32 desconocido_DA0;
     s16 desconocido_DA4;
     s16 desconocido_DA6;
     f32 desconocido_DA8;
     f32 desconocido_dac;
     f32 desconocido_DB0;
     struct InteriorJugadorDesconocido desconocido_DB4;
} Jugador;

enum TIPOS_PARTICULA_POOL_1 {
    SIN_PARTICULA,
    PARTICULA_DERRAPE,
    PARTICULA_SUELO,
    PARTICULA_PASTO,
    TIPO_PARTICULA_POOL_1_4,
    TIPO_PARTICULA_POOL_1_5,
    TIPO_PARTICULA_POOL_1_6,
    TIPO_PARTICULA_POOL_1_7,
    TIPO_PARTICULA_POOL_1_8,
    TIPO_PARTICULA_POOL_1_9
};

typedef struct {
     s32 desconocido_00;
     u8 fantasma_datos_guardado;
     s8 indice_circuito;
     u8 id_personaje;
     u8 desconocido_07[0x3C];
     u8 relleno_43[0x7F - 0x43];
     u8 checksum;
} struct_8018EE10_entrada;

typedef struct {
     u16 rojo;
     u16 verde;
     u16 azul;
     u16 alpha;
} RGBA16;

typedef struct {
     f32 escalado_desconocido;
     f32 escalado_puesto;
     u32 algun_temporizador;
     u32 algun_temporizador_1;
     u32 tiempo_ultimo_tocado_linea_meta;
    union {
        struct {
             u32 tiempo_finalizacion_vuelta_1;
             u32 tiempo_finalizacion_vuelta_2;
             u32 tiempo_finalizacion_vuelta_3;
        };
        u32 veces_finalizacion_vuelta[3];
    };
    union {
        struct {
             u32 duracion_vuelta_1;
             u32 duracion_vuelta_2;
             u32 duracion_vuelta_3;
        };
        u32 duraciones_vuelta[3];
    };
     s32 pos_x_int;
     s32 pos_y_int;
     s32 pos_z_int;
     s32 desconocido_38;
     s16 temporizador_parpadear;
     s16 velocimetro_x;
     s16 velocimetro_y;
     s16 caja_item_x;
     s16 caja_item_y;
     s16 deslizamiento_caja_item_x;
     s16 deslizamiento_caja_item_y;
     s16 desconocido_4A;
     s16 desconocido_4C;
     s16 temporizador_x;
    union {
        struct {
             s16 tiempo_x_finalizacion_vuelta_1;
             s16 tiempo_x_finalizacion_vuelta_2;
             s16 tiempo_x_finalizacion_vuelta_3;
        };
         s16 vuelta_finalizacion_tiempo_xs[3];
    };
     s16 tiempo_x_total;
     s16 temporizador_y;
     s16 vuelta_x;
     s16 vuelta_despues_imagen_1_x;
     s16 vuelta_despues_imagen_2_x;
     s16 vuelta_y;
     s16 puesto_x;
     s16 puesto_y;
     s16
        puesto_x_deslizamiento;
     s16
        puesto_y_deslizamiento;
     s16 posicion_preparacion;
     s16 desconocido_6C;
     s16 desconocido_6E;
     s8 bool_completo_carrera;
     s8 cantidad_vuelta;
     s8 cantidad_vuelta_tambien;
     s8 estado_parpadear;
     s8 desconocido_74;
     s8 desconocido_75;
     u8 sobrescribir_item;
     s8 desconocido_77;
     u8 unk_78;
     u8 desconocido_79;
     u8 desconocido_7A;
     u8 desconocido_7B;
     u8 desconocido_7C;
     u8 desconocido_7D;
     u8 desconocido_7E;
     u8 desconocido_7F;
     u8 desconocido_80;
     u8 desconocido_81;
     s8 desconocido_82;
     s8 desconocido_83;
} jugador_hud;

#define TAMANIO_JUGADORES_HUD 4

#endif
