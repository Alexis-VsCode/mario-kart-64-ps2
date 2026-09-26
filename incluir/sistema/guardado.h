#ifndef SISTEMA_GUARDADO_H
#define SISTEMA_GUARDADO_H

#include <PR/os.h>
#include <juego/estructuras_comunes.h>

#define MANDO_1 0
#define MANDO_2 1
#define MANDO_3 2
#define MANDO_4 3

#define ERROR_SIN_PFS 0
#define PFS_SIN_PAK_INSERTADO 1
#define PFS_PAK_MALO_LECTURA 2
#define PFS_PAK_CORRUPTO 3
#define DESBORDE_ARCHIVO_PFS 4
#define DATOS_INVALIDO_PFS -1
#define PFS_NUM_ARCHIVOS_ERROR -2
#define PFS_LIBRE_BLOQUES_ERROR -3
#define PFS_PAK_ESTADO_OK -4

#define SIN_PAK 0
#define PAK 1
#define PAK_NO_INSERTADO -1

void funcion_800B45E0(s32);
void guardar_datos_gran_premio_puntos_y_modo_sonido_escritura(void);
void funcion_800B46D0(void);
void funcion_800B4728(s32);
void guardar_datos_gran_premio_puntos_y_modo_sonido_reinicio(void);
u8 suma_control_contrarreloj_registros(s32);
s32 funcion_800B6348(s32);
s32 funcion_800B639C(s32);
s32 funcion_800B63F0(s32);
u8 guardar_suma_control_datos_calcular_1(void);
u8 guardar_suma_control_datos_calcular_2(void);
void guardar_datos_carga(void);
void funcion_800B4A9C(s32);
void guardar_datos_validar(void);
void poblar_contrarreloj_registro(u8* contrarreloj_registro, u32 time, s32 id_personaje);
u32 funcion_800B4DF4(u8*);
s32 funcion_800B4E24(s32);
u32 funcion_800B4EB4(s32, s32);
s32 funcion_800B4F2C(void);
s32 funcion_800B4FB0(s32);
s32 funcion_800B5020(u32, s32);
s32 funcion_800B5218(void);
void funcion_800B536C(s32);
void funcion_800B5404(s32, s32);
u8 funcion_800B54C0(s32, s32);
u8 funcion_800B54EC(s32, s32);
u8 funcion_800B5508(s32, s32, s32);
s32 es_completo_modo_cc(s32);
s32 tiene_modo_extra_desbloqueado(void);
s32 tiene_modo_extra_completado(void);
void funcion_800B559C(s32);
u8 funcion_800B578C(s32);
s32 funcion_800B5888(s32);
s32 funcion_800B58C4(s32);
void guardar_respaldo_datos_actualizacion(void);
u8 guardar_respaldo_suma_control_datos_calcular_1(void);
u8 guardar_respaldo_suma_control_datos_calcular_2(void);
s32 guardar_respaldo_suma_control_datos_validar(void);
s32 comprobar_para_controller_pak(s32);
s32 funcion_800B5B2C(s32);
s32 controller_pak_1_situacion(void);
s32 controller_pak_2_situacion(void);
s32 funcion_800B5F30(void);
s32 funcion_800B6014(void);
s32 funcion_800B6088(s32);
u8 funcion_800B60E8(s32);
s32 funcion_800B6178(s32);
s32 funcion_800B64EC(s32);
s32 funcion_800B65F4(s32, s32);
void funcion_800B6708(void);
void funcion_800B6798(void);
u8 funcion_800B6828(s32);
u8 funcion_800B68F4(s32);
s32 funcion_800B69BC(s32);
s32 funcion_800B6A68(void);

extern u32* repeticion_fantasma_comprimido;
extern struct_8018EE10_entrada dato_8018EE10[];

extern u16 codigo_empresa;
extern u32 codigo_juego;
extern s8 controller_pak_1_estado;

extern s8 controller_pak_2_estado;
extern const u8 dato_800F2E60[];
extern const u8 nombre_juego[];
extern const u8 codigo_ext[];
extern u16 dato_80162DD6;
extern s32 dato_80162DE0;
extern s32 dato_80162DFC;
extern OSPfs controller_pak_manejador_1_archivo;
extern OSPfs controller_pak_manejador_2_archivo;
extern OSPfsState estado_pfs[16];
extern s32 pfs_error[16];
extern s32 controller_pak_1_num_archivos_usado;
extern s32 controller_pak_archivos_escribible_1_max;
extern s8 dato_8018EDE5;
extern s8 dato_8018EDE6;
extern s8 dato_8018EDE7;

#endif
