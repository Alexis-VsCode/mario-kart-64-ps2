#ifndef JUEGO_OBJETOS_H
#define JUEGO_OBJETOS_H

#include "curvas.h"
#include <juego/estructuras_comunes.h>

#define TAMANIO_LISTA_OBJETO 0x226
#define ALGUN_OBJETO_INDICE_LISTA_TAMANIO 32

typedef struct {
     f32 escalado_tamanio;
     Vec3f pos;
     Vec3f pos_origen;
     Vec3f desconocido_01C;
     Vec3f offset;
     f32 desconocido_034;
     Vec3f velocidad;
     f32 altura_superficie;
     s32 desconocido_048;
     s32 desconocido_04C;
     s32 temporizador;
     s32 status;
     s32 desconocido_058;
     s32 desconocido_05C;
     u8* t_lut_activo;
     u8* textura_activo;
     u8* tlut_lista;
     u8* textura_lista;
     Gfx* model;
     Vtx* vertice;
     s8 desconocido_078[0x04];
     PuntoControlSpline* puntos_control;
     DatosSpline* spline;
     s16 desconocido_084[0xA];
     u16 temporizador_animacion;
     u16 desconocido_09A;
     s16 desconocido_09C;
     s16 desconocido_09E;
     s16 prim_alpha;
     s16 desconocido_0A2;
     s16 type;
     s16 state;
     s16 desconocido_0A8;
     s16 desconocido_0AA;
     s16 desconocido_0AC;
     s16 desconocido_0AE;
     s16 desconocido_0B0;
     Vec3su orientacion;
     Vec3su desconocido_0B8;
     Vec3su angulo_sentido;
     u16 desconocido_0C4;
     u16 desconocido_0C6;
     u16 tamanio_caja_envolvente;
     s8 desconocido_0CA;
     bool8 activo_temporizador_es;
     s8 desconocido_0CC;
     s8 desconocido_0CD;
     s8 desconocido_0CE;
     s8 desconocido_0CF;
     s8 desconocido_0D0;
     s8 desconocido_0D1;
     s8 textura_indice_lista;
     s8 desconocido_0D3;
     s8 desconocido_0D4;
     u8 desconocido_0D5;
     u8 desconocido_0D6;
     u8 desconocido_0D7;
     u8 desconocido_0D8;
     u8 textura_ancho;
     u8 textura_altura;
     u8 desconocido_0DB;
     u8 desconocido_0DC;
     u8 desconocido_0DD;
     s8 desconocido_0DE;
     u8 desconocido_0DF;
} Objeto;

extern Objeto lista_objeto[];

typedef struct {
     f32 escalado_tamanio;
     Vec3f pos;
     Vec3f pos_origen;
     Vec3f desconocido_01C;
     Vec3f offset;
     f32 desconocido_034;
     Vec3f velocidad;
     f32 desconocido_044;
     s32 desconocido_048;
     s32 desconocido_04C;
     s32 temporizador;
     s32 status;
     s32 desconocido_058;
     s32 desconocido_05C;
     u8* t_lut_activo;
     u8* textura_activo;
     u8* tlut_lista;
     u8* textura_lista;
     Gfx* model;
     Vtx* vertice;
     s8 desconocido_078[0x04];
     Vec4s* desconocido_07C;
     Vec4s* desconocido_080;
     s16 desconocido_084[0xA];
     u16 hongo_dorado_temporizador;
     u16 desconocido_09A;
     s16 desconocido_09C;
     s16 desconocido_09E;
     s16 prim_alpha;
     s16 desconocido_0A2;
     s16 item_actual;
     s16 estado_pantalla_item;
     s16 desconocido_0A8;
     s16 desconocido_0AA;
     s16 desconocido_0AC;
     s16 desconocido_0AE;
     s16 desconocido_0B0;
     Vec3su orientacion;
     Vec3su desconocido_0B8;
     Vec3su angulo_sentido;
     u16 desconocido_0C4;
     u16 desconocido_0C6;
     u16 desconocido_0C8;
     s8 desconocido_0CA;
     s8 activo_temporizador_es;
     s8 desconocido_0CC;
     s8 desconocido_0CD;
     s8 desconocido_0CE;
     s8 desconocido_0CF;
     s8 desconocido_0D0;
     s8 desconocido_0D1;
     s8 textura_indice_lista;
     s8 desconocido_0D3;
     s8 desconocido_0D4;
     u8 desconocido_0D5;
     u8 desconocido_0D6;
     u8 desconocido_0D7;
     u8 desconocido_0D8;
     u8 textura_ancho;
     u8 textura_altura;
     u8 desconocido_0DB;
     u8 desconocido_0DC;
     u8 desconocido_0DD;
     s8 desconocido_0DE;
     u8 desconocido_0DF;
} VentanaItemObjetos;

#define VISIBLE 0x00040000

extern s32 dato_80183DA0;

extern s32 indice_lakitu_lista[];

#define ID_OBJETO_ELIMINADO -1
#define ID_OBJETO_NULO -1

extern s32 ventana_item_objeto_por_id_jugador[];

extern s16 dato_80165750;

extern s32 dato_8018D1C8;
extern s32 dato_8018D1D0;
extern s32 dato_8018D1D8;

extern s32 dato_8018D3C0;

extern Colision dato_8018C0B0[];

#define NUM_YV_BANDERA_POSTES 4

// pos, rot
extern s16 dato_800E5DF4[];

#define CANGREJOS_NUM 0xA

typedef struct {
     s16 inicio_x;
     s16 patrulla_x;
     s16 inicio_z;
     s16 patrulla_z;
} AparicionCangrejo;

extern AparicionCangrejo apariciones_cangrejo[];

#define NUM_THWOMPS_50CC 8
#define NUM_THWOMPS_100CC_EXTRA 11
#define NUM_THWOMPS_150CC 12

// pos x,y,z
extern float dato_800E6734[];

typedef struct {
     s16 inicio_x;
     s16 inicio_z;
     s16 desconocido_4;
     s16 desconocido_6;
} ThwompAparicion;

extern ThwompAparicion apariciones_thomwp_50CC[];
extern ThwompAparicion thwomp_extra_apariciones_100CC[];
extern ThwompAparicion apariciones_thomwp_150CC[];
extern ThwompAparicion* lista_aparicion_thowmp;

extern s16 thwomps_activo_num;

#define CARTELES_NEON_NUM 10
#define CHOMPS_CADENA_NUM 3

#define PINGUINOS_NUM 15

extern s32 lista_objeto_indice_1[];

#define GAVIOTAS_NUM 10
#define MUNIECOS_NIEVE_NUM 19
#define ERIZOS_NUM 15

typedef struct {
     Vec3s pos;
     s16 desconocido_6;
} AparicionMuniecoNieve;

extern AparicionMuniecoNieve apariciones_munieco_nieve[];

typedef struct {
     Vec3s pos;
     s16 desconocido_06;
} AparicionErizo;

extern AparicionErizo apariciones_erizo[];
extern Vec3s puntos_patrulla_erizo[];

extern s32 lista_objeto_indice_2[];

#define NUM_BOOS 0xA
#define RESPIROS_FUEGO_NUM 4

extern Vec3s apariciones_respiros_fuego[];

extern s16 dato_800E5740[];
extern s16 dato_800E579C[];
extern s16 dato_800E57F8[];

extern s32 lista_objeto_indice_3[];

extern s32 lista_objeto_indice_4[];

#define objeto_particula_1_tamanio 128
#define TOPOS_GROUP1_NUM 8
#define TOPOS_GROUP2_NUM 11
#define TOPOS_GROUP3_NUM 12
#define TOPOS_TOTAL_NUM (TOPOS_GROUP1_NUM + TOPOS_GROUP2_NUM + TOPOS_GROUP3_NUM)
#define COPOS_NUM 0x32

typedef union {
    Vec3s como_lista_vec_3_s[TOPOS_TOTAL_NUM];
    s16 como_lista_plano[TOPOS_TOTAL_NUM * 3];
} UnionAparicionTopo;
extern UnionAparicionTopo apariciones_topo;

extern s8 dato_8018D198[];
extern s8 dato_8018D1A8[];
extern s8 dato_8018D1B8[];

extern s32 dato_8018CF10;

extern s32 particula_objeto_1[];

extern s32 siguiente_libre_objeto_particula_1;

extern s16 dato_8018D174;

#define objeto_particula_2_tamanio 128

extern s32 particula_objeto_2[];

extern s32 siguiente_libre_objeto_particula_2;

extern s32 dato_8018D3BC;

#define objeto_particula_3_tamanio 128
extern s32 particula_objeto_3[];
extern s32 siguiente_libre_objeto_particula_3;
extern s16 dato_80165730;

extern s16 dato_80165738;

#define objeto_particula_4_tamanio 0x40

#define ANTORCHAS_NUM 8

extern s16 apariciones_antorcha[];

extern s32 particula_objeto_4[];

extern s32 siguiente_libre_objeto_particula_4;

#define hoja_particula_tamanio 0x40
#define hoja_particula_aparicion_tamanio 0x14

extern s32 particula_hoja[];

extern s32 siguiente_libre_hoja_particula;

typedef struct {
     u16 rot_y;
     u16 pos_y;
     u16 porciento_escala;
     u16 tipo_sub;
} DatosEstrella, DatosNube;

#define TAMANIO_D_8018CC80 0x64

extern s32 dato_8018CC80[];

extern s32 dato_8018D1F0;

extern s32 dato_8018D1F8;

extern s16 dato_8018D17C;

extern s8 dato_8018D230;

extern s32 dato_8018D3C4;

#endif
