// Textos y tablas

void guMtxCatL(Mtx* m, Mtx* n, Mtx* res);

u16* buffer_textura_menu;
u32* buffer_comprimido_menu;
u8* tkmk_00_bajo_res_buffer;
u8* copia_puntos_gp;
void* algun_buffer_dl;
s8 puntos_gp_por_id_personaje[8];
s8 id_personaje_por_puesto_total_gp[8];
s8 dato_8018D9D8;
s8 dato_8018D9D9;
MenuItem menu_items[MENU_ITEMS_MAX];
struct_8018DEE0_entrada dato_8018DEE0[TAMANIO_D_8018DEE0];
struct_8018E060_entrada dato_8018E060[TAMANIO_D_8018E060];
SIN_USO u8 menu_item_bss_margen0[8];
struct_8018E0E8_entrada dato_8018E0E8[TAMANIO_D_8018E0E8];
s32 menu_textura_buffer_indice;
TexturaMapa mapa_textura_menu[TEXTURA_MAX_MAPA];
#ifdef AVOID_UB
static void fijar_buffer_textura_menu(u16* buffer, u32 size);
#endif
s32 entradas_textura_menu;
Gfx* gfx_ptr;
s32 num_d_8018E768_entradas;
struct_8018E768_entrada dato_8018E768[TAMANIO_D_8018E768];
s32 menu_destello_ciclo;
s8 tipo_transicion[5];
u32 duracion_transicion[5];
u32 tiempo_transicion_actual[4];
s32 dato_8018E7E0;
struct desconocido_struct_8018E7E8 dato_8018E7E8[TAMANIO_D_8018E7E8];
struct desconocido_struct_8018E7E8 dato_8018E810[TAMANIO_D_8018E810];
s8 dato_8018E838[4];
s32 dato_8018E83C;

s32 dato_8018E840[4];
s32 dato_8018E850[2];
s32 dato_8018E858[2];
s8 g_color_texto;
s32 d_8018E864_relleno;
OSPfs controller_pak_manejador_1_archivo;
OSPfs controller_pak_manejador_2_archivo;
OSPfsState estado_pfs[16];
s32 pfs_error[16];
s32 controller_pak_1_num_archivos_usado;
s32 controller_pak_archivos_escribible_1_max;

s32 controller_pak_libre_paginas_1_num;
s32 controller_pak_nota_1_archivo;
s32 controller_pak_nota_2_archivo;
s32 menu_item_bss_relleno2;
ALIGNED8 DatosGuardado datos_guardado;

u8 dato_8018ED90;
u8 dato_8018ED91;
s32 temporizador_modelo_intro;

desconocido_d_800E70A0 dato_800E70A0[] = {
    { 0x3d, 0x11, 0x00, 0x00 }, { 0x15, 0x3e, 0x00, 0x00 }, { 0x5c, 0x3e, 0x00, 0x00 },
    { 0xa3, 0x3e, 0x00, 0x00 }, { 0xea, 0x3e, 0x00, 0x00 }, { 0x10a, 0xc8, 0x00, 0x00 },
    { 0x15, 0xc8, 0x00, 0x00 }, { 0x55, 0xc8, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E70E8[] = {
    { 0x40, 0x41, 0x00, 0x00 },
    { 0x40, 0x53, 0x00, 0x00 },
    { 0x40, 0x65, 0x00, 0x00 },
    { 0x40, 0x77, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E7108[][4] = {
    {
        { 0x18, 0x3f, 0x00, 0x00 },
        { 0x5d, 0x3f, 0x00, 0x00 },
        { 0xa2, 0x3f, 0x00, 0x00 },
        { 0xe7, 0x3f, 0x00, 0x00 },
    },
    {
        { 0x18, 0x91, 0x00, 0x00 },
        { 0x5d, 0x91, 0x00, 0x00 },
        { 0xa2, 0x91, 0x00, 0x00 },
        { 0xe7, 0x91, 0x00, 0x00 },
    },
};

desconocido_d_800E70A0 dato_800E7148[] = {
    { 0x17, 0x3b, 0x00, 0x00 },
    { 0x5d, 0x3b, 0x00, 0x00 },
    { 0xa2, 0x3b, 0x00, 0x00 },
    { 0xe8, 0x3b, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E7168[] = {
    { 0x17, 0x70, 0x00, 0x00 },
    { 0x57, 0x70, 0x00, 0x00 },
    { 0x17, 0x97, 0x00, 0x00 },
    { 0x57, 0x97, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E7188[] = {
    { 0x80, 0x58, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 },

    { 0x80, 0x3f, 0x00, 0x00 }, { 0x80, 0x91, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 },

    { 0x5a, 0x58, 0x00, 0x00 }, { 0xa6, 0x58, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 },

    { 0x5a, 0x3f, 0x00, 0x00 }, { 0xa6, 0x3f, 0x00, 0x00 }, { 0x5a, 0x91, 0x00, 0x00 }, { 0xa6, 0x91, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E7208[][2] = {
    {
        { 0x9d, 0x70, 0x00, 0x00 },
        { 0x128, 0x81, 0x00, 0x00 },
    },
    {
        { 0x9d, 0x88, 0x00, 0x00 },
        { 0x128, 0x99, 0x00, 0x00 },
    },
    {
        { 0x9d, 0xa0, 0x00, 0x00 },
        { 0x128, 0xb1, 0x00, 0x00 },
    },
    {
        { 0x9d, 0xb8, 0x00, 0x00 },
        { 0x128, 0xc9, 0x00, 0x00 },
    },
};

desconocido_d_800E70A0 dato_800E7248[] = {
    { 0xff6a, 0x3b, 0x00, 0x00 },
    { 0x172, 0x3b, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E7258[] = {
    { 0x17, 0x3b, 0x00, 0x00 },
    { 0xc5, 0x3b, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E7268[] = {
    { 0x28, 0x73, 0x00, 0x00 },
    { 0x28, 0x3c, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E7278[] = {
    { 0x3e, 0x43, 0x00, 0x00 },     { 0xa1, 0x43, 0x00, 0x00 },
    { 0x3e, 0xc5, 0x00, 0x00 },     { 0xa1, 0xc5, 0x00, 0x00 },

    { 0xffc0, 0xf0, 0x00, 0x00 },   { 0x140, 0xf0, 0x00, 0x00 },
    { 0xffc0, 0xffc0, 0x00, 0x00 }, { 0xffc0, 0xffc0, 0x00, 0x00 },

    { 0xffc0, 0xffc0, 0x00, 0x00 }, { 0x140, 0xffc0, 0x00, 0x00 },
    { 0xffc0, 0xf0, 0x00, 0x00 },   { 0xffc0, 0xffc0, 0x00, 0x00 },

    { 0xffc0, 0xffc0, 0x00, 0x00 }, { 0x140, 0xffc0, 0x00, 0x00 },
    { 0xffc0, 0xf0, 0x00, 0x00 },   { 0x140, 0xf0, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E72F8 = { 0x140, 0x23, 0x00, 0x00 };

desconocido_d_800E70A0 dato_800E7300[] = {
    { 0x50, 0x23, 0x00, 0x00 }, { 0xb0, 0x23, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 },

    { 0x32, 0x23, 0x00, 0x00 }, { 0x80, 0x23, 0x00, 0x00 }, { 0xce, 0x23, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 },

    { 0x18, 0x23, 0x00, 0x00 }, { 0x5d, 0x23, 0x00, 0x00 }, { 0xa2, 0x23, 0x00, 0x00 }, { 0xe7, 0x23, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E7360[] = {
    { 0x61, 0xa7, 0x00, 0x00 },
    { 0x61, 0xb6, 0x00, 0x00 },
    { 0x61, 0xc5, 0x00, 0x00 },
    { 0x61, 0xd4, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E7380[] = {
    { 0x30, 0x4b, 0x00, 0x00 },
    { 0x109, 0x4b, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E7390[] = {
    { 0xad, 0x8d, 0x00, 0x00 }, { 0xad, 0x9a, 0x00, 0x00 }, { 0xad, 0xa7, 0x00, 0x00 },
    { 0xad, 0xb4, 0x00, 0x00 }, { 0xad, 0xc1, 0x00, 0x00 }, { 0xad, 0xce, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E73C0[] = {
    { 0xac, 0xa5, 0x00, 0x00 },
    { 0xac, 0xc3, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E73D0[] = {
    { 0xc0, 0xb3, 0x00, 0x00 },
    { 0xc0, 0xc2, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E73E0[] = {
    { 0x61, 0x94, 0x00, 0x00 }, { 0x61, 0xa1, 0x00, 0x00 }, { 0x61, 0xae, 0x00, 0x00 },
    { 0x61, 0xbb, 0x00, 0x00 }, { 0x61, 0xc8, 0x00, 0x00 }, { 0x61, 0xd5, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E7410[] = {
    { 0x52, 0x90, 0x00, 0x00 },
    { 0x52, 0xa4, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E7420[] = {
    { 0x76, 0x95, 0x00, 0x00 },
    { 0x76, 0xa4, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E7430[] = {
    { 0x17, 0xa, 0x00, 0x00 }, { 0x5d, 0xa, 0x00, 0x00 }, { 0xa2, 0xa, 0x00, 0x00 },
    { 0xe8, 0xa, 0x00, 0x00 }, { 0x17, 0xa, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E7458[] = {
    { 0x14a, 0x32, 0x00, 0x00 },  { 0xff60, 0xd4, 0x00, 0x00 }, { 0xa0, 0x10e, 0x00, 0x00 },
    { 0xff60, 0xbe, 0x00, 0x00 }, { 0x143, 0x5a, 0x00, 0x00 },
};

desconocido_d_800E70A0 dato_800E7480[] = {
    { 0xa0, 0x32, 0x00, 0x00 }, { 0x9b, 0xd4, 0x00, 0x00 }, { 0xa0, 0x50, 0x00, 0x00 },
    { 0x9b, 0xbe, 0x00, 0x00 }, { 0x80, 0x5a, 0x00, 0x00 },
};

RGBA16 dato_800E74A8[] = {
    { 0x00, 0xf3, 0xf3, 0xff }, { 0xff, 0xa8, 0xc3, 0xff }, { 0xff, 0xfe, 0x7a, 0xff },
    { 0x7b, 0xfc, 0x7b, 0xff }, { 0xff, 0xff, 0x00, 0xff },
};

RGBA16 dato_800E74D0[] = {
    { 0x00, 0xf3, 0xf3, 0xff },
    { 0xff, 0xa8, 0xc3, 0xff },
    { 0xff, 0xff, 0x00, 0xff },
};

RGBA16 color_fondo[] = {
    { 0xff, 0xaf, 0xaf, 0xff },
    { 0xaf, 0xff, 0xaf, 0xff },
    { 0xaf, 0xaf, 0xff, 0xff },
};

const s16 ancho_pantalla_glifo[] = {
#define GLIFO(textura, ancho) ancho,
#include "lista_glifos.inc.c"
#undef GLIFO
};

#include "textos_menu.inc.c"

const s8 premios_punto_gp[] = { 9, 6, 3, 1 };
const s8 dato_800F0B1C[] = {
    0, 0, 1, 0, 1, 0, 1, 2, 0, 1, 2, 3,
};
const s8 dato_800F0B28[] = {
    0, 1, 2, 1, 2, 1, 2, 1, 2, 0, 0, 1, 2, 2, 1, 2, 2, 1, 2, 2,
    1, 2, 2, 1, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
};

const s8 dato_800F0B50[] = { 0x1f, 0x0b, 0x15, 0x29 };
const s8 dato_800F0B54[] = { 0x20, 0x0f, 0x18, 0x2c };

RGBA16 dato_800E7AC8[] = {
    { 0x00, 0x00, 0x00, 0x00 },
    { 0xff, 0xff, 0xff, 0xff },
    { 0x00, 0x00, 0x50, 0xff },
    { 0xff, 0xff, 0xff, 0xff },
};

RGBA16 dato_800E7AE8[] = {
    { 0x00, 0x00, 0x00, 0xff },
    { 0xff, 0xff, 0xff, 0xff },
};

TexturaMenu* dato_800E7AF8[] = {
    dato_02000000, dato_02000028, dato_02000050, dato_02000078, dato_020000A0, dato_020000C8, dato_020000F0, dato_02000118, dato_02000140,
    dato_02000168, dato_02000190, dato_020001B8, dato_020001E0, dato_02000208, dato_02000230, dato_02000258, dato_02000280, dato_020002A8,
    dato_020002D0, dato_020002F8, dato_02000320, dato_02000348, dato_02000370, dato_02000398, dato_020003C0, dato_020003E8, dato_02000410,
    dato_02000438, dato_02000460, dato_02000488, dato_020004B0, dato_020004D8, dato_02000500, dato_02000528, dato_02000550, dato_02000578,
    dato_020005A0, dato_020005C8, dato_020005F0, dato_02000618, dato_02000640, dato_02000668, dato_02000690, dato_020006B8, dato_020006E0,
    dato_02000708, dato_02000730, dato_02000758, dato_02000780, dato_020007A8, dato_020007D0, dato_020007F8, dato_02000820, dato_02000848,
    dato_02000870, dato_02000898, dato_020008C0, dato_020008E8, dato_02000910, dato_02000938, dato_02000960, dato_02000988, dato_020009B0,
    dato_020009D8, dato_02000A00, dato_02000A28, dato_02000A50, dato_02000A78, dato_02000AA0, dato_02000AC8, dato_02000AF0, dato_02000B18,
    dato_02000B40, dato_02000B68, dato_02000B90, dato_02000BB8, dato_02000BE0, dato_02000C08, dato_02000C30, dato_02000C58, dato_02000C80,
    dato_02000CA8, dato_02000CD0, dato_02000CF8, dato_02000D20, dato_02000D48, dato_02000D70, dato_02000D98, dato_02000DC0, dato_02000DE8,
    dato_02000E10, dato_02000E38, dato_02000E60, dato_02000E88, dato_02000EB0, dato_02000ED8, dato_02000F00, dato_02000F28, dato_02000F50,
    dato_02000F78, dato_02000FA0, dato_02000FC8, dato_02000FF0, dato_02001018, dato_02001040, dato_02001068, dato_02001090, dato_020010B8,
    dato_020010E0, dato_02001108, dato_02001130, dato_02001158, dato_02001180, dato_020011A8, dato_020011D0, dato_020011F8, dato_02001220,
    dato_02001248, dato_02001270, dato_02001298, dato_020012C0, dato_020012E8, dato_02001310, dato_02001338, dato_02001360, dato_02001388,
    dato_020013B0, dato_020013D8, dato_02001400, dato_02001428, dato_02001450, dato_02001478, dato_020014A0,
};

TexturaMenu* dato_800E7D0C[] = {
    dato_020016BC, dato_020016E4, dato_0200170C, dato_02001734, dato_0200175C,
    dato_02001784, dato_020017AC, dato_020017D4, dato_020017FC, dato_02001824,
};

AnimacionMk* dato_800E7D34[] = {
    dato_0200198C, dato_0200199C, dato_020019AC, dato_020019BC, dato_020019CC, dato_020019DC,
};

TexturaMenu* fondo_texturas_menu[] = {
    seg2_azul_cielo_fondo_textura,
    seg2_atardecer_fondo_textura,
};

TexturaMenu* dato_800E7D54[] = {
    dato_02001A8C, dato_02001A64, dato_02001AB4, dato_02001A14, dato_02001B04, dato_020019EC, dato_02001ADC, dato_02001A3C,
};

TexturaMenu* dato_800E7D74[] = {
    seg2_mario_raceway_textura_vista_previa,
    dato_02001B54,
    dato_02001B7C,
    dato_02001BA4,
    dato_02001BCC,
    dato_02001BF4,
    dato_02001C1C,
    dato_02001C44,
    dato_02001C6C,
    dato_02001C94,
    dato_02001CBC,
    dato_02001CE4,
    dato_02001D0C,
    dato_02001D34,
    dato_02001D5C,
    dato_02001D84,
    dato_02001DAC,
    dato_02001DD4,
    dato_02001DFC,
    dato_02001E24,
};

TexturaMenu* dato_800E7DC4[] = {
    seg2_mario_raceway_textura_titulo,
    seg2_choco_mountain_textura_titulo,
    dato_02004EF8,
    dato_02004F20,
    dato_02004F48,
    dato_02004F70,
    dato_02004F98,
    dato_02004FC0,
    dato_02004FE8,
    dato_02005010,
    dato_02005038,
    dato_02005060,
    dato_02005088,
    dato_020050B0,
    dato_020050D8,
    dato_02005100,
    dato_02005128,
    dato_02005150,
    dato_02005178,
    dato_020051A0,
};

#ifdef AVOID_UB
AnimacionMk* dato_800E7E14[] = {
    dato_020020BC, dato_020020CC, dato_020020DC, dato_020020DC, dato_020020EC, dato_020020FC, dato_0200210C, dato_0200210C,
};
#else
AnimacionMk* dato_800E7E14[] = {
    dato_020020BC,
    dato_020020CC,
    dato_020020DC,
};

AnimacionMk* dato_800E7E20[] = {
    dato_020020DC, dato_020020EC, dato_020020FC, dato_0200210C, dato_0200210C,
};
#endif

AnimacionMk* dato_800E7E34[] = {
    dato_02001E64, dato_02001E74, dato_02001E84, dato_02001E94, dato_02001EA4, dato_02001EB4, dato_02001EC4,
    dato_02001ED4, dato_02001EE4, dato_02001EF4, dato_02001F04, dato_02001F14, dato_02001F24, dato_02001F34,
    dato_02001F44, dato_02001F54, dato_02001F64, dato_02001F74, dato_02001F84, dato_02001F94,
};

TexturaMenu* lut_textura_glifo[] = {
#define GLIFO(textura, ancho) textura,
#include "lista_glifos.inc.c"
#undef GLIFO
};

ASSERT_ESTATICO(CANTIDAD_ARREGLO(lut_textura_glifo) == CANTIDAD_ARREGLO(ancho_pantalla_glifo),
                "cada glifo necesita su textura");
