#include <PR/ultratypes.h>
#include "juego/desplazamientos_pista.h"
#include "datos_pista.h"

extern u8 textura_67F15C[];
extern u8 textura_67F450[];
extern u8 textura_cartel_wario_cara[];
extern u8 textura_670AC8[];
extern u8 textura_blanco_negro_tablero[];
extern u8 textura_64C11C[];
extern u8 textura_64C7B4[];
extern u8 textura_668228[];
extern u8 textura_668358[];
extern u8 textura_66AEB8[];
extern u8 textura_677A40[];
extern u8 textura_67E428[];
extern u8 textura_643A34[];
extern u8 textura_66EBF0[];
extern u8 textura_68272C[];
extern u8 textura_682928[];
extern u8 textura_682B24[];
extern u8 textura_682D20[];
extern u8 textura_682F1C[];
extern u8 textura_683118[];

const textura_circuito wario_stadium_texturas[] = {
    { textura_67F15C, 0x02F1, 0x0800, 0x0 },
    { textura_67F450, 0x0194, 0x0800, 0x0 },
    { textura_cartel_wario_cara, 0x0825, 0x1000, 0x0 },
    { textura_670AC8, 0x0FBF, 0x1000, 0x0 },
    { textura_blanco_negro_tablero, 0x0107, 0x0800, 0x0 },
    { textura_64C11C, 0x0695, 0x0800, 0x0 },
    { textura_64C7B4, 0x046C, 0x0800, 0x0 },
    { textura_668228, 0x0130, 0x0800, 0x0 },
    { textura_668358, 0x01A0, 0x0800, 0x0 },
    { textura_66AEB8, 0x0201, 0x0800, 0x0 },
    { textura_677A40, 0x0275, 0x0800, 0x0 },
    { textura_67E428, 0x0A81, 0x1000, 0x0 },
    { textura_643A34, 0x0106, 0x0800, 0x0 },
    { textura_66EBF0, 0x0146, 0x0800, 0x0 },
    { textura_68272C, 0x01F9, 0x1000, 0x0 },
    { textura_682928, 0x01F9, 0x1000, 0x0 },
    { textura_682B24, 0x01F9, 0x1000, 0x0 },
    { textura_682D20, 0x01F9, 0x1000, 0x0 },
    { textura_682F1C, 0x01F9, 0x1000, 0x0 },
    { textura_683118, 0x01F9, 0x1000, 0x0 },
    { 0x00000000, 0x0000, 0x0000, 0x0 },
};

const Gfx* wario_stadium_dls[] = {
    d_circuito_wario_stadium_dl_0,    d_circuito_wario_stadium_dl_158,  d_circuito_wario_stadium_dl_B8,
    d_circuito_wario_stadium_dl_1B8,  d_circuito_wario_stadium_dl_2A0,  d_circuito_wario_stadium_dl_440,
    d_circuito_wario_stadium_dl_350,  d_circuito_wario_stadium_dl_4C0,  d_circuito_wario_stadium_dl_5E8,
    d_circuito_wario_stadium_dl_798,  d_circuito_wario_stadium_dl_668,  d_circuito_wario_stadium_dl_830,
    d_circuito_wario_stadium_dl_940,  d_circuito_wario_stadium_dl_AB0,  d_circuito_wario_stadium_dl_990,
    d_circuito_wario_stadium_dl_B60,  d_circuito_wario_stadium_dl_C08,  d_circuito_wario_stadium_dl_D60,
    d_circuito_wario_stadium_dl_C70,  d_circuito_wario_stadium_dl_E30,  d_circuito_wario_stadium_dl_ED0,
    d_circuito_wario_stadium_dl_1068, d_circuito_wario_stadium_dl_F70,  d_circuito_wario_stadium_dl_1158,
    d_circuito_wario_stadium_dl_11F8, d_circuito_wario_stadium_dl_13C0, d_circuito_wario_stadium_dl_12E0,
    d_circuito_wario_stadium_dl_14A0, d_circuito_wario_stadium_dl_1590, d_circuito_wario_stadium_dl_1708,
    d_circuito_wario_stadium_dl_1630, d_circuito_wario_stadium_dl_17A8, d_circuito_wario_stadium_dl_1868,
    d_circuito_wario_stadium_dl_19E0, d_circuito_wario_stadium_dl_1908, d_circuito_wario_stadium_dl_1AB8,
    d_circuito_wario_stadium_dl_1B48, d_circuito_wario_stadium_dl_1CA8, d_circuito_wario_stadium_dl_1BB0,
    d_circuito_wario_stadium_dl_1D68, d_circuito_wario_stadium_dl_1DF8, d_circuito_wario_stadium_dl_1FD8,
    d_circuito_wario_stadium_dl_1E70, d_circuito_wario_stadium_dl_20A8, d_circuito_wario_stadium_dl_21A8,
    d_circuito_wario_stadium_dl_2308, d_circuito_wario_stadium_dl_2218, d_circuito_wario_stadium_dl_23B0,
    d_circuito_wario_stadium_dl_2490, d_circuito_wario_stadium_dl_2610, d_circuito_wario_stadium_dl_2530,
    d_circuito_wario_stadium_dl_2698, d_circuito_wario_stadium_dl_2798, d_circuito_wario_stadium_dl_2928,
    d_circuito_wario_stadium_dl_2870, d_circuito_wario_stadium_dl_29D0, d_circuito_wario_stadium_dl_2AB0,
    d_circuito_wario_stadium_dl_2C30, d_circuito_wario_stadium_dl_2B60, d_circuito_wario_stadium_dl_2CE0,
    d_circuito_wario_stadium_dl_2DC0, d_circuito_wario_stadium_dl_2FB8, d_circuito_wario_stadium_dl_2E70,
    d_circuito_wario_stadium_dl_3098, d_circuito_wario_stadium_dl_31B0, d_circuito_wario_stadium_dl_3368,
    d_circuito_wario_stadium_dl_3260, d_circuito_wario_stadium_dl_3450, d_circuito_wario_stadium_dl_3550,
    d_circuito_wario_stadium_dl_36D8, d_circuito_wario_stadium_dl_3600, d_circuito_wario_stadium_dl_37A8,
    d_circuito_wario_stadium_dl_3890, d_circuito_wario_stadium_dl_3A10, d_circuito_wario_stadium_dl_3980,
    d_circuito_wario_stadium_dl_3AD0, d_circuito_wario_stadium_dl_3BB0, d_circuito_wario_stadium_dl_3D90,
    d_circuito_wario_stadium_dl_3CF8, d_circuito_wario_stadium_dl_3E80, d_circuito_wario_stadium_dl_3F78,
    d_circuito_wario_stadium_dl_40F0, d_circuito_wario_stadium_dl_4060, d_circuito_wario_stadium_dl_41D0,
    d_circuito_wario_stadium_dl_4270, d_circuito_wario_stadium_dl_43E0, d_circuito_wario_stadium_dl_4340,
    d_circuito_wario_stadium_dl_44B0, d_circuito_wario_stadium_dl_4550, d_circuito_wario_stadium_dl_47F0,
    d_circuito_wario_stadium_dl_46E0, d_circuito_wario_stadium_dl_4948, d_circuito_wario_stadium_dl_4A78,
    d_circuito_wario_stadium_dl_4BE8, d_circuito_wario_stadium_dl_4B30, d_circuito_wario_stadium_dl_4C60,
    d_circuito_wario_stadium_dl_4D40, d_circuito_wario_stadium_dl_4EF0, d_circuito_wario_stadium_dl_4E30,
    d_circuito_wario_stadium_dl_4F80, d_circuito_wario_stadium_dl_5090, d_circuito_wario_stadium_dl_51E8,
    d_circuito_wario_stadium_dl_5168, d_circuito_wario_stadium_dl_5270, d_circuito_wario_stadium_dl_5338,
    d_circuito_wario_stadium_dl_54E8, d_circuito_wario_stadium_dl_5460, d_circuito_wario_stadium_dl_5588,
};
