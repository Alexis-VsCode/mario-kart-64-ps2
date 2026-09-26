#include <PR/ultratypes.h>
#include "juego/desplazamientos_pista.h"
#include "datos_pista.h"

extern u8 textura_cartel_disparo_caparazon_0[];
extern u8 textura_cartel_disparo_caparazon_1[];
extern u8 textura_azul_amarillo_tablero[];
extern u8 textura_64619C[];
extern u8 textura_verde_azul_tablero[];
extern u8 textura_pasto_3[];
extern u8 textura_bandera_rojo[];
extern u8 textura_65100C[];
extern u8 textura_65112C[];
extern u8 textura_653608[];
extern u8 textura_pasto_11[];
extern u8 textura_cartel_luigi_cara_0[];
extern u8 textura_cartel_luigi_cara_1[];
extern u8 textura_66C7A8[];
extern u8 textura_670AC8[];
extern u8 textura_671A88[];
extern u8 textura_6735DC[];
extern u8 textura_673C68[];
extern u8 textura_6747C4[];
extern u8 textura_ruta_1[];
extern u8 textura_ruta_2[];
extern u8 textura_meta_ruta_1[];
extern u8 textura_67BBD8[];
extern u8 textura_68272C[];
extern u8 textura_682928[];
extern u8 textura_682B24[];
extern u8 textura_682D20[];
extern u8 textura_682F1C[];
extern u8 textura_683118[];
extern u8 textura_cartel_azul_64[];
extern u8 textura_cartel_koopa_aire_0[];
extern u8 textura_cartel_koopa_aire_1[];
extern u8 textura_cartel_luigis_0[];
extern u8 textura_cartel_luigis_1[];
extern u8 textura_cartel_mario_estrella_0[];
extern u8 textura_cartel_mario_estrella_1[];
extern u8 textura_cartel_nintendo_rojo_0[];
extern u8 textura_cartel_nintendo_rojo_1[];
extern u8 textura_cartel_yoshi[];
extern u8 textura_gris_azul_tablero[];

const textura_circuito luigi_raceway_texturas[] = {
    { textura_cartel_disparo_caparazon_0, 0x038C, 0x1000, 0x0 },
    { textura_cartel_disparo_caparazon_1, 0x0247, 0x1000, 0x0 },
    { textura_azul_amarillo_tablero, 0x013A, 0x0800, 0x0 },
    { textura_64619C, 0x0124, 0x0800, 0x0 },
    { textura_verde_azul_tablero, 0x0139, 0x0800, 0x0 },
    { textura_pasto_3, 0x0372, 0x0800, 0x0 },
    { textura_bandera_rojo, 0x019E, 0x0800, 0x0 },
    { textura_65100C, 0x0120, 0x0800, 0x0 },
    { textura_65112C, 0x0150, 0x0800, 0x0 },
    { textura_653608, 0x07A7, 0x0800, 0x0 },
    { textura_pasto_11, 0x01F8, 0x0800, 0x0 },
    { textura_cartel_luigi_cara_0, 0x05C9, 0x1000, 0x0 },
    { textura_cartel_luigi_cara_1, 0x065F, 0x1000, 0x0 },
    { textura_66C7A8, 0x0149, 0x0800, 0x0 },
    { textura_670AC8, 0x0FBF, 0x1000, 0x0 },
    { textura_671A88, 0x012D, 0x0800, 0x0 },
    { textura_6735DC, 0x03B1, 0x0800, 0x0 },
    { textura_673C68, 0x038D, 0x0800, 0x0 },
    { textura_6747C4, 0x0145, 0x0800, 0x0 },
    { textura_ruta_1, 0x02D2, 0x1000, 0x0 },
    { textura_ruta_2, 0x02AE, 0x1000, 0x0 },
    { textura_meta_ruta_1, 0x026B, 0x1000, 0x0 },
    { textura_67BBD8, 0x0310, 0x0800, 0x0 },
    { textura_68272C, 0x01F9, 0x1000, 0x0 },
    { textura_682928, 0x01F9, 0x1000, 0x0 },
    { textura_682B24, 0x01F9, 0x1000, 0x0 },
    { textura_682D20, 0x01F9, 0x1000, 0x0 },
    { textura_682F1C, 0x01F9, 0x1000, 0x0 },
    { textura_683118, 0x01F9, 0x1000, 0x0 },
    { textura_cartel_azul_64, 0x0567, 0x1000, 0x0 },
    { textura_cartel_koopa_aire_0, 0x0360, 0x1000, 0x0 },
    { textura_cartel_koopa_aire_1, 0x0304, 0x1000, 0x0 },
    { textura_cartel_luigis_0, 0x0287, 0x1000, 0x0 },
    { textura_cartel_luigis_1, 0x02AF, 0x1000, 0x0 },
    { textura_cartel_mario_estrella_0, 0x02D2, 0x1000, 0x0 },
    { textura_cartel_mario_estrella_1, 0x02B1, 0x1000, 0x0 },
    { textura_cartel_nintendo_rojo_0, 0x02A6, 0x1000, 0x0 },
    { textura_cartel_nintendo_rojo_1, 0x02F7, 0x1000, 0x0 },
    { textura_cartel_yoshi, 0x04DF, 0x1000, 0x0 },
    { textura_gris_azul_tablero, 0x04A1, 0x1000, 0x0 },
    { 0x00000000, 0x0000, 0x0000, 0x0 },
};

const Gfx* luigi_raceway_dls[] = {
    d_circuito_luigi_raceway_dl_0,    d_circuito_luigi_raceway_dl_328,  d_circuito_luigi_raceway_dl_1A8,
    d_circuito_luigi_raceway_dl_480,  d_circuito_luigi_raceway_dl_6E0,  d_circuito_luigi_raceway_dl_9F8,
    d_circuito_luigi_raceway_dl_868,  d_circuito_luigi_raceway_dl_B48,  d_circuito_luigi_raceway_dl_D80,
    d_circuito_luigi_raceway_dl_1058, d_circuito_luigi_raceway_dl_EE8,  d_circuito_luigi_raceway_dl_1198,
    d_circuito_luigi_raceway_dl_1398, d_circuito_luigi_raceway_dl_16D8, d_circuito_luigi_raceway_dl_1538,
    d_circuito_luigi_raceway_dl_1888, d_circuito_luigi_raceway_dl_1B00, d_circuito_luigi_raceway_dl_1E30,
    d_circuito_luigi_raceway_dl_1C78, d_circuito_luigi_raceway_dl_1FD0, d_circuito_luigi_raceway_dl_2240,
    d_circuito_luigi_raceway_dl_2518, d_circuito_luigi_raceway_dl_2348, d_circuito_luigi_raceway_dl_2658,
    d_circuito_luigi_raceway_dl_2860, d_circuito_luigi_raceway_dl_2BC0, d_circuito_luigi_raceway_dl_2978,
    d_circuito_luigi_raceway_dl_2D00, d_circuito_luigi_raceway_dl_2F08, d_circuito_luigi_raceway_dl_32C0,
    d_circuito_luigi_raceway_dl_2FF8, d_circuito_luigi_raceway_dl_3408, d_circuito_luigi_raceway_dl_3610,
    d_circuito_luigi_raceway_dl_3928, d_circuito_luigi_raceway_dl_36A8, d_circuito_luigi_raceway_dl_3AB0,
    d_circuito_luigi_raceway_dl_3C18, d_circuito_luigi_raceway_dl_3EB0, d_circuito_luigi_raceway_dl_3CA0,
    d_circuito_luigi_raceway_dl_4058, d_circuito_luigi_raceway_dl_4198, d_circuito_luigi_raceway_dl_4440,
    d_circuito_luigi_raceway_dl_4240, d_circuito_luigi_raceway_dl_4638, d_circuito_luigi_raceway_dl_4720,
    d_circuito_luigi_raceway_dl_4A18, d_circuito_luigi_raceway_dl_4828, d_circuito_luigi_raceway_dl_4C60,
    d_circuito_luigi_raceway_dl_4CF8, d_circuito_luigi_raceway_dl_4FD8, d_circuito_luigi_raceway_dl_4E38,
    d_circuito_luigi_raceway_dl_5220, d_circuito_luigi_raceway_dl_52D0, d_circuito_luigi_raceway_dl_5558,
    d_circuito_luigi_raceway_dl_5420, d_circuito_luigi_raceway_dl_5728, d_circuito_luigi_raceway_dl_57F8,
    d_circuito_luigi_raceway_dl_5A60, d_circuito_luigi_raceway_dl_5940, d_circuito_luigi_raceway_dl_5BA0,
    d_circuito_luigi_raceway_dl_5CB8, d_circuito_luigi_raceway_dl_5F08, d_circuito_luigi_raceway_dl_5E10,
    d_circuito_luigi_raceway_dl_6018, d_circuito_luigi_raceway_dl_6150, d_circuito_luigi_raceway_dl_6350,
    d_circuito_luigi_raceway_dl_6288, d_circuito_luigi_raceway_dl_6400, d_circuito_luigi_raceway_dl_6558,
    d_circuito_luigi_raceway_dl_6608, d_circuito_luigi_raceway_dl_65B0, d_circuito_luigi_raceway_dl_6658,
    d_circuito_luigi_raceway_dl_66B8, d_circuito_luigi_raceway_dl_67A0, d_circuito_luigi_raceway_dl_6708,
    d_circuito_luigi_raceway_dl_6810, d_circuito_luigi_raceway_dl_68C0, d_circuito_luigi_raceway_dl_6A00,
    d_circuito_luigi_raceway_dl_6930, d_circuito_luigi_raceway_dl_6A90, d_circuito_luigi_raceway_dl_6B58,
    d_circuito_luigi_raceway_dl_6DA0, d_circuito_luigi_raceway_dl_6C40, d_circuito_luigi_raceway_dl_6EB0,
    d_circuito_luigi_raceway_dl_6FF0, d_circuito_luigi_raceway_dl_7248, d_circuito_luigi_raceway_dl_7110,
    d_circuito_luigi_raceway_dl_7388, d_circuito_luigi_raceway_dl_74B0, d_circuito_luigi_raceway_dl_7750,
    d_circuito_luigi_raceway_dl_75F0, d_circuito_luigi_raceway_dl_7928, d_circuito_luigi_raceway_dl_7A18,
    d_circuito_luigi_raceway_dl_7CD0, d_circuito_luigi_raceway_dl_7BB0, d_circuito_luigi_raceway_dl_7EE8,
    d_circuito_luigi_raceway_dl_7FA0, d_circuito_luigi_raceway_dl_8260, d_circuito_luigi_raceway_dl_8158,
    d_circuito_luigi_raceway_dl_8450, d_circuito_luigi_raceway_dl_8508, d_circuito_luigi_raceway_dl_8790,
    d_circuito_luigi_raceway_dl_86F8, d_circuito_luigi_raceway_dl_8958, d_circuito_luigi_raceway_dl_8A70,
    d_circuito_luigi_raceway_dl_8D68, d_circuito_luigi_raceway_dl_8CC8, d_circuito_luigi_raceway_dl_8F00,
    d_circuito_luigi_raceway_dl_9058, d_circuito_luigi_raceway_dl_9408, d_circuito_luigi_raceway_dl_9310,
    d_circuito_luigi_raceway_dl_95A0, d_circuito_luigi_raceway_dl_97B0, d_circuito_luigi_raceway_dl_9AD0,
    d_circuito_luigi_raceway_dl_99C0, d_circuito_luigi_raceway_dl_9C50, d_circuito_luigi_raceway_dl_9E58,
    d_circuito_luigi_raceway_dl_A178, d_circuito_luigi_raceway_dl_A028, d_circuito_luigi_raceway_dl_A320,
};
