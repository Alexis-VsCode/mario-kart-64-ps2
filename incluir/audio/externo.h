#ifndef AUDIO_EXTERNO_H
#define AUDIO_EXTERNO_H

#include <juego/estructuras_comunes.h>
#include "carrera/camara.h"

#define ADSR_ESTADO_DESACTIVADO 0
#define INICIAL_ESTADO_ADSR 1
#define ADSR_ESTADO_INICIO_BUCLE 2
#define BUCLE_ESTADO_ADSR 3
#define FUNDIDO_ESTADO_ADSR 4
#define CUELGUE_ESTADO_ADSR 5
#define DECAER_ESTADO_ADSR 6
#define SUELTA_ESTADO_ADSR 7
#define SOSTENIDO_ESTADO_ADSR 8

#define SUELTA_ACCION_ADSR 0x10
#define DECAER_ACCION_ADSR 0x20
#define CUELGUE_ACCION_ADSR 0x40

#define DESACTIVAR_ADSR 0
#define CUELGUE_ADSR -1
#define ADSR_GOTO -2
#define REINICIO_ADSR -3

#define PARAMETROS_SECUENCIA(prioridad, sec_id) ((prioridad << 8) | sec_id)

#define SONIDO_ESTEREO_MODO 0
#define SONIDO_MONO_MODO 3
#define SONIDO_AURICULARES_MODO 1

#define SEC_NIVEL_JUGADOR 0
#define SEC_AMB_JUGADOR 1
#define SEC_SFX_JUGADOR 2

#define SONIDO_UNK0_BANCO 0
#define SONIDO_UNK1_BANCO 1
#define SONIDO_UNK2_BANCO 2
#define SONIDO_UNK3_BANCO 3
#define SONIDO_UNK4_BANCO 4
#define SONIDO_UNK5_BANCO 5
#define SONIDO_CANTIDAD_BANCO 6

struct Sonido {
     u32 sonido_bits;
     Vec3f* position;
     u8 id_camara;
     f32* desconocido_0c;
     f32* unk10;
     s8* unk14;
};

struct desconocido_800E9F7C {
     Vec3f pos;
     f32 desconocido_0C;
     f32 desconocido_10;
     s8 desconocido_14;
     f32 desconocido_18;
     f32 desconocido_1C;
     f32 desconocido_20;
     f32 desconocido_24;
     f32 desconocido_28;
     f32 desconocido_2C;
     f32 desconocido_30;
     f32 desconocido_34;
     f32 desconocido_38;
};

struct desconocido_8018EFD8 {
     f32* pos_x;
     f32* pos_y;
     f32* pos_z;
     f32* vel_x;
     f32* vel_y;
     f32* vel_z;
     Vec3f unk18;
     f32* unk24;
     u8 id_camara;
     u8 prev;
     u8 next;
     f32 desconocido_2c;
     u8 desconocido30;
     f32 unk34;
     u32 sonido_bits;
};

struct SonidoCaracteristicas {
     Vec3f* unk00;
     f32* desconocido04;
     f32* desconocido08;
     u8 id_camara;
     f32* unk10;
     f32* unk14;
     s8* unk18;
     f32 distancia;
     u32 priority;
     u32 sonido_bits;
     u8 sonido_situacion;
     u8 frescura;
     u8 prev;
     u8 next;
     u8 desconocido_2c;
};

struct desconocido_800EA06C {
     Vec3f unk00;
     u8 desconocido_0c;
};

typedef struct {
     f32 desconocido_00;
     f32 desconocido_04;
     f32 desconocido_08;
     u16 desconocido_0C;
     f32 desconocido_10;
     f32 desconocido_14;
     f32 desconocido_18;
     u16 desconocido_1C;
} struct_d_801930D0_interior;

typedef struct {
     f32 desconocido_000;
     f32 desconocido_004;
     f32 desconocido_008;
     u16 desconocido_00C;
     u8 desconocido_00E[3];
     u8 desconocido_011;
     u8 desconocido_012;
     u8 desconocido_013;
     u32 desconocido_014;
     u16 desconocido_018;
     u16 desconocido_01A;
     f32 desconocido_01C;
     f32 desconocido_020;
     f32 desconocido_024;
     u16 desconocido_028;
     u16 desconocido_02A;
     u32 desconocido_02C[5];
     u8 desconocido_040;
     u8 desconocido_041;
     u8 desconocido_042;
     u8 desconocido_043;
     struct_d_801930D0_interior desconocido_044[16];
     u16 desconocido_244;
     u16 desconocido_246;
     u16 desconocido_248;
     u16 desconocido_24A;
} struct_d_801930D0_entrada;

struct CanalVolumenEscalaFundido {
     f32 current;
     f32 target;
     f32 velocidad;
     u16 frames_restante;
};

typedef struct {
    f32 desconocido0;
    f32 desconocido4;
    u8 desconocido8;
    u8 desconocido9;
} StructDesconocido8018EF18;

typedef struct {
    u8 cosa0;
    u8 cosa1;
} struct_d_80192CA8_entrada;

void funcion_800C94A4(u8);
void funcion_800CADD0(u8, f32);
void funcion_800C13F0(void);
void reiniciar_eu_sesion_audio(OSMesg);
f32 funcion_800C1480(u8, u8);
s8 funcion_800C15D0(u8, u8, u8);
s8 funcion_800C16E8(f32, f32, u8);
f32 funcion_800C1934(u8, u8);
void funcion_800C19D0(u8, u8, u8);
struct desconocido_8018EFD8* funcion_800C1C88(u8, Vec3f, Vec3f, f32*, u8, u32);
void funcion_800C1DA4(Camara*, Vec3s, struct desconocido_8018EFD8*);
void funcion_800C1E2C(Camara*, Vec3f, struct desconocido_8018EFD8*);
void funcion_800C1F8C(void);

Vec3f* funcion_800C21E8(Vec3f, u32);
void funcion_800C2274(u8);
void funcion_800C2474(void);
void funcion_800C284C(u8, u8, u8, u16);
void funcion_800C29B4(u8, u16);

void funcion_800C3724(void);
void funcion_800C2A2C(u32);
void funcion_800C3448(u32);
void funcion_800C3478(void);
u16 funcion_800C3508(u8);
void funcion_800C3608(u8, u8);
u8 funcion_800C357C(s32);
void funcion_800C35E8(u8);
void funcion_800C36C4(u8, u8, u8, u8);
void funcion_800C3F70(void);

void funcion_800C400C(void);
void funcion_800C4084(u16);
void funcion_800C40F0(u8);
void reproducir_sonido(u32, Vec3f*, u8, f32*, f32*, s8*);
void funcion_800C41CC(u8, struct SonidoCaracteristicas*);
void funcion_800C4398(void);
void eliminar_sonido_desde_banco(u8, u8);
void funcion_800C4888(u8);
void funcion_800C4FE4(u8);

void funcion_800C5278(u8);
void funcion_800C5384(u8, Vec3f*);
void funcion_800C54B8(u8, Vec3f*);
void funcion_800C550C(Vec3f*);
void funcion_800C5578(Vec3f*, u32);
void funcion_800C56F0(u32);
void funcion_800C5848(void);
void escalar_volumen_canal_fundido(u8, u8, u16);
void funcion_800C5968(u8);
void funcion_800C59C4(void);
void sonido_inicializacion(void);
void funcion_800C5BD0(void);
void funcion_800C5C40(void);
void funcion_800C5CB8(void);
void funcion_800C5D04(u8);
void funcion_800C5E38(u8);

void funcion_800C6108(u8);
void funcion_800C64A0(u8);
void funcion_800C6758(u8);
void funcion_800C683C(u8);

void funcion_800C70A8(u8);
void funcion_800C76C0(u8);

void funcion_800C847C(u8);
void funcion_800C86D8(u8);
void funcion_800C8770(u8);
void funcion_800C8920(void);
void funcion_800C89E4(void);
void funcion_800C8AE4(void);
void funcion_800C8C7C(u8);
void funcion_800C8CCC(void);
void reproducir_sonido2(s32);
void reproducir_secuencia(u16);
void reproducir_secuencia2(u16);
void funcion_800C8F44(u8);
void funcion_800C8F80(u8, u32);

void funcion_800C9018(u8, u32);
void funcion_800C9060(u8, u32);
void funcion_800C90F4(u8, u32);
void funcion_800C9250(u8);
void funcion_800C92CC(u8, u32);
void funcion_800C94A4(u8);
void funcion_800C97C4(u8);
void funcion_800C98B8(Vec3f, Vec3f, u32);
void funcion_800C99E0(Vec3f, s32);
void funcion_800C9A88(u8);
void funcion_800C9D0C(u8);
void funcion_800C9D80(Vec3f, Vec3f, u32);
void funcion_800C9EF4(Vec3f, u32);
void funcion_800C9F90(u8);

void funcion_800CA008(u8, u8);
void funcion_800CA0A0(void);
void funcion_800CA0B8(void);
void funcion_800CA0CC(void);
void funcion_800CA0E4(void);
void funcion_800CA118(u8);
void funcion_800CA24C(u8);
void funcion_800CA270(void);
void funcion_800CA288(u8, s8);
void funcion_800CA2B8(u8);
void funcion_800CA2E4(u8, s8);
void funcion_800CA30C(u8);
void funcion_800CA330(u8);
void funcion_800CA388(u8);
void reproducir_secuencias(u16, u16);
void funcion_800CA49C(u8);
void funcion_800CA59C(u8);
void funcion_800CA984(u8);
void funcion_800CAACC(u8);
void funcion_800CAB4C(u8);
void funcion_800CAC08(void);
void funcion_800CAC60(u8);
void funcion_800CAD40(s32);
void funcion_800CAEC4(u8, f32);
void funcion_800CAFC0(u8);

void funcion_800CB134(void);
void empezar_secuencia_ceremonia_perdiendo(void);
void funcion_800CB2C4(void);
void funcion_800CBC24(void);

extern s8 dato_801657E5;

extern s32 banderas_error_audio;

extern s8 dato_8018EF10;
extern StructDesconocido8018EF18 dato_8018EF18[16];
extern struct desconocido_8018EFD8 dato_8018EFD8[];
extern u8 dato_8018FB90;
extern u8 dato_8018FB91;
extern Camara* camara_copia[4];
extern Vec3f camara_velocidad[4];
extern Vec3f pos_ultimo_camara[4];
extern u8 dato_8018FC08;
extern s16 dato_8018FC10[4][2];

extern struct SonidoCaracteristicas sonido_bancos[SONIDO_CANTIDAD_BANCO][20];
extern u8 sonido_banco_usado_lista_atras[SONIDO_CANTIDAD_BANCO];
extern u8 sonido_banco_libre_lista_frente[SONIDO_CANTIDAD_BANCO];
extern u8 sonidos_num_en_banco[SONIDO_CANTIDAD_BANCO];
extern u8 dato_80192AB8[SONIDO_CANTIDAD_BANCO][8][8];
extern u8 dato_80192C38;
extern u8 sonido_banco_desactivado[SONIDO_CANTIDAD_BANCO];
extern struct CanalVolumenEscalaFundido dato_80192C48[SONIDO_CANTIDAD_BANCO];
extern struct_d_80192CA8_entrada dato_80192CA8[3][5];
extern u8 dato_80192CC6[3];
extern u32 dato_80192CD0[256];
extern struct_d_801930D0_entrada dato_801930D0[3];
extern u8 num_procesado_sonido_pedidos;
extern u8 sonido_cantidad_pedido;
extern struct Sonido sonido_pedidos[0x100];

extern u8 dato_800E9DA0;
extern s32 dato_800E9DB4[];
extern f32 dato_800E9DC4[4];
extern f32 dato_800E9DD4[4];
extern f32 dato_800E9DE4[4];
extern f32 dato_800E9DF4[8];
extern s32 dato_800E9E14[4];
extern s32 dato_800E9E24[4];
extern s32 dato_800E9E34[8];
extern f32 dato_800E9E54[4];
extern f32 dato_800E9E64[4];
extern s32 dato_800E9E74[4];
extern s32 dato_800E9E84[4];
extern u32 dato_800E9E94[4];
extern s32 dato_800E9EA4[4];
extern f32 dato_800E9EB4[4];
extern f32 dato_800E9EC4[4];
extern f32 dato_800E9ED4[4];
extern f32 dato_800E9EE4[4];
extern f32 dato_800E9EF4[4];
extern f32 dato_800E9F04[4];
extern f32 dato_800E9F14[4];
extern u8 dato_800E9F24[8];
extern u8 dato_800E9F2C[8];
extern f32 dato_800E9F34[8];
extern f32 dato_800E9F54[8];
extern u8 dato_800E9F74[4];
extern u8 dato_800E9F78[4];
extern struct desconocido_800E9F7C dato_800E9F7C[4];
extern u8 dato_800E9F90[];
extern struct desconocido_800EA06C dato_800EA06C[8];
extern u8 dato_800EA0EC[];
extern u8 dato_800EA0F0;
extern u8 dato_800EA0F4;
extern u8 dato_800EA104;
extern u8 dato_800EA108;
extern u8 dato_800EA10C[];
extern f32 dato_800EA110[4];
extern f32 dato_800EA120[4];
extern f32 dato_800EA130[8];
extern f32 dato_800EA150;
extern u8 dato_800EA154[];
extern u16 dato_800EA15C;
extern u16 dato_800EA160;
extern u8 dato_800EA164;
extern s8 dato_800EA168;
extern u8 dato_800EA170[];
extern u16 dato_800EA174;
extern f32 dato_800EA178;
extern f32 dato_800EA17C;
extern u16 dato_800EA180;
extern u16 dato_800EA184;
extern u8 dato_800EA188[][6];
extern u8 dato_800EA1A0[][6];
extern u8 dato_800EA1C0;
extern u16 dato_800EA1C4;
extern Vec3f dato_800EA1C8;
extern f32 dato_800EA1D4;
extern s8 dato_800EA1DC;
extern u8 dato_800EA1E4;
extern u8 dato_800EA1E8;
extern u8 dato_800EA1EC;
extern u8 dato_800EA1F0[];
extern u8 dato_800EA1F4[];
extern u8 dato_800EA244;

extern s8 dato_800EA16C;

extern OSMesgQueue* dato_800EA3B0;
extern OSMesgQueue* dato_800EA3B4;

#endif
