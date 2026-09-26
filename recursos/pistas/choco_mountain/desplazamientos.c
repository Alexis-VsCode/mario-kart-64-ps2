#include <PR/ultratypes.h>
#include "juego/desplazamientos_pista.h"
#include "datos_pista.h"

extern u8 textura_64619C[];
extern u8 textura_64647C[];
extern u8 textura_647F4C[];
extern u8 textura_64FBF4[];
extern u8 textura_653DB0[];
extern u8 textura_652B54[];
extern u8 textura_65315C[];
extern u8 textura_6684F8[];
extern u8 textura_cartel_luigis_0[];
extern u8 textura_cartel_luigis_1[];
extern u8 textura_cartel_nintendo_rojo_0[];
extern u8 textura_cartel_nintendo_rojo_1[];
extern u8 textura_6774D8[];
extern u8 textura_cartel_rocas_cayendo[];
extern u8 textura_cartel_trasera[];
extern u8 textura_679C04[];
extern u8 textura_67B864[];
extern u8 textura_67DC20[];
extern u8 textura_cartel_yoshi[];
extern u8 textura_gris_azul_tablero[];

const textura_circuito choco_mountain_texturas[] = {
    { textura_64619C, 0x0124, 0x0800, 0x0 },
    { textura_64647C, 0x0829, 0x1000, 0x0 },
    { textura_647F4C, 0x05BC, 0x1000, 0x0 },
    { textura_64FBF4, 0x0274, 0x0800, 0x0 },
    { textura_653DB0, 0x06AE, 0x0800, 0x0 },
    { textura_652B54, 0x0606, 0x0800, 0x0 },
    { textura_65315C, 0x04A9, 0x0800, 0x0 },
    { textura_6684F8, 0x010D, 0x0800, 0x0 },
    { textura_cartel_luigis_0, 0x0287, 0x1000, 0x0 },
    { textura_cartel_luigis_1, 0x02AF, 0x1000, 0x0 },
    { textura_cartel_nintendo_rojo_0, 0x02A6, 0x1000, 0x0 },
    { textura_cartel_nintendo_rojo_1, 0x02F7, 0x1000, 0x0 },
    { textura_6774D8, 0x0113, 0x0800, 0x0 },
    { textura_cartel_rocas_cayendo, 0x012C, 0x0800, 0x0 },
    { textura_cartel_trasera, 0x011E, 0x0800, 0x0 },
    { textura_679C04, 0x012F, 0x0800, 0x0 },
    { textura_67B864, 0x014C, 0x0800, 0x0 },
    { textura_67DC20, 0x03EF, 0x0800, 0x0 },
    { textura_cartel_yoshi, 0x04DF, 0x1000, 0x0 },
    { textura_gris_azul_tablero, 0x04A1, 0x1000, 0x0 },
    { 0x00000000, 0x0000, 0x0000, 0x0 },
};

const Gfx* choco_mountain_dls[] = {
    d_circuito_choco_mountain_dl_0,    d_circuito_choco_mountain_dl_150,  d_circuito_choco_montania_dl_B0,
    d_circuito_choco_mountain_dl_208,  d_circuito_choco_montania_dl_2A8,  d_circuito_choco_mountain_dl_410,
    d_circuito_choco_mountain_dl_330,  d_circuito_choco_montania_dl_4D8,  d_circuito_choco_mountain_dl_588,
    d_circuito_choco_montania_dl_6C0,  d_circuito_choco_mountain_dl_618,  d_circuito_choco_mountain_dl_750,
    d_circuito_choco_montania_dl_7E8,  d_circuito_choco_mountain_dl_908,  d_circuito_choco_mountain_dl_878,
    d_circuito_choco_mountain_dl_990,  d_circuito_choco_montania_dl_A28,  d_circuito_choco_montania_dl_BB8,
    d_circuito_choco_montania_dl_B10,  d_circuito_choco_montania_dl_C40,  d_circuito_choco_montania_dl_D30,
    d_circuito_choco_montania_dl_EA0,  d_circuito_choco_montania_dl_DF8,  d_circuito_choco_montania_dl_F38,
    d_circuito_choco_mountain_dl_1000, d_circuito_choco_mountain_dl_1150, d_circuito_choco_montania_dl_10A8,
    d_circuito_choco_montania_dl_11D8, d_circuito_choco_mountain_dl_1280, d_circuito_choco_montania_dl_13E0,
    d_circuito_choco_mountain_dl_1330, d_circuito_choco_mountain_dl_1488, d_circuito_choco_mountain_dl_1528,
    d_circuito_choco_montania_dl_16B8, d_circuito_choco_montania_dl_15E8, d_circuito_choco_mountain_dl_1788,
    d_circuito_choco_mountain_dl_1810, d_circuito_choco_mountain_dl_1970, d_circuito_choco_montania_dl_18B8,
    d_circuito_choco_montania_dl_1A40, d_circuito_choco_montania_dl_1AC8, d_circuito_choco_montania_dl_1C18,
    d_circuito_choco_montania_dl_1B70, d_circuito_choco_montania_dl_1CC8, d_circuito_choco_montania_dl_1D50,
    d_circuito_choco_montania_dl_1E98, d_circuito_choco_montania_dl_1E08, d_circuito_choco_montania_dl_1F40,
    d_circuito_choco_montania_dl_1FE0, d_circuito_choco_mountain_dl_2168, d_circuito_choco_montania_dl_20C8,
    d_circuito_choco_mountain_dl_2228, d_circuito_choco_montania_dl_22D8, d_circuito_choco_mountain_dl_2468,
    d_circuito_choco_montania_dl_23C8, d_circuito_choco_mountain_dl_2538, d_circuito_choco_mountain_dl_2600,
    d_circuito_choco_mountain_dl_2780, d_circuito_choco_montania_dl_26D8, d_circuito_choco_mountain_dl_2840,
    d_circuito_choco_mountain_dl_2908, d_circuito_choco_montania_dl_2A88, d_circuito_choco_montania_dl_29B8,
    d_circuito_choco_montania_dl_2B38, d_circuito_choco_montania_dl_2C08, d_circuito_choco_montania_dl_2D50,
    d_circuito_choco_montania_dl_2C98, d_circuito_choco_montania_dl_2DE8, d_circuito_choco_montania_dl_2EA0,
    d_circuito_choco_montania_dl_2FD0, d_circuito_choco_montania_dl_2F28, d_circuito_choco_mountain_dl_3070,
    d_circuito_choco_mountain_dl_3120, d_circuito_choco_montania_dl_32B0, d_circuito_choco_montania_dl_31D8,
    d_circuito_choco_mountain_dl_3368, d_circuito_choco_mountain_dl_3438, d_circuito_choco_mountain_dl_3618,
    d_circuito_choco_mountain_dl_3550, d_circuito_choco_montania_dl_36F0, d_circuito_choco_montania_dl_37D0,
    d_circuito_choco_montania_dl_39A8, d_circuito_choco_montania_dl_38E8, d_circuito_choco_montania_dl_3A80,
    d_circuito_choco_montania_dl_3B60, d_circuito_choco_montania_dl_3CB8, d_circuito_choco_montania_dl_3C18,
    d_circuito_choco_montania_dl_3D70, d_circuito_choco_montania_dl_3E18, d_circuito_choco_montania_dl_3FA8,
    d_circuito_choco_montania_dl_3EE0, d_circuito_choco_mountain_dl_4090, d_circuito_choco_mountain_dl_4138,
    d_circuito_choco_montania_dl_42C8, d_circuito_choco_montania_dl_41F8, d_circuito_choco_montania_dl_43C8,
};
