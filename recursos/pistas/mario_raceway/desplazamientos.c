#include <PR/ultratypes.h>
#include "juego/desplazamientos_pista.h"
#include "datos_pista.h"

extern u8 textura_rosa_amarillo_tablero[];
extern u8 textura_64619C[];
extern u8 textura_pasto_1[];
extern u8 textura_64BB60[];
extern u8 textura_pasto_7[];
extern u8 textura_pasto_5[];
extern u8 textura_bandera_rojo[];
extern u8 textura_663F90[];
extern u8 textura_6642A4[];
extern u8 textura_6640B4[];
extern u8 textura_pasto_10[];
extern u8 textura_6684F8[];
extern u8 textura_cartel_luigis_0[];
extern u8 textura_cartel_luigis_1[];
extern u8 textura_cartel_mario_estrella_0[];
extern u8 textura_cartel_mario_estrella_1[];
extern u8 textura_66C8F4[];
extern u8 textura_cartel_nintendo_rojo_0[];
extern u8 textura_cartel_nintendo_rojo_1[];
extern u8 textura_670AC8[];
extern u8 textura_674354[];
extern u8 textura_ruta_0[];
extern u8 textura_meta_ruta_0[];
extern u8 textura_67B9B0[];
extern u8 textura_cartel_yoshi[];
extern u8 textura_gris_azul_tablero[];
extern u8 textura_cartel_disparo_caparazon_0[];
extern u8 textura_cartel_disparo_caparazon_1[];
extern u8 textura_cartel_koopa_aire_0[];
extern u8 textura_cartel_koopa_aire_1[];

const textura_circuito mario_raceway_texturas[] = {
    { textura_rosa_amarillo_tablero, 0x0149, 0x0800, 0x0 },
    { textura_64619C, 0x0124, 0x0800, 0x0 },
    { textura_pasto_1, 0x0125, 0x0800, 0x0 },
    { textura_64BB60, 0x0169, 0x0800, 0x0 },
    { textura_pasto_7, 0x05DE, 0x0800, 0x0 },
    { textura_pasto_5, 0x023F, 0x0800, 0x0 },
    { textura_bandera_rojo, 0x019E, 0x0800, 0x0 },
    { textura_663F90, 0x0122, 0x0800, 0x0 },
    { textura_6642A4, 0x0162, 0x0800, 0x0 },
    { textura_6640B4, 0x01EF, 0x0800, 0x0 },
    { textura_pasto_10, 0x01F8, 0x0800, 0x0 },
    { textura_6684F8, 0x010D, 0x0800, 0x0 },
    { textura_cartel_luigis_0, 0x0287, 0x1000, 0x0 },
    { textura_cartel_luigis_1, 0x02AF, 0x1000, 0x0 },
    { textura_cartel_mario_estrella_0, 0x02D2, 0x1000, 0x0 },
    { textura_cartel_mario_estrella_1, 0x02B1, 0x1000, 0x0 },
    { textura_66C8F4, 0x01A1, 0x0800, 0x0 },
    { textura_cartel_nintendo_rojo_0, 0x02A6, 0x1000, 0x0 },
    { textura_cartel_nintendo_rojo_1, 0x02F7, 0x1000, 0x0 },
    { textura_670AC8, 0x0FBF, 0x1000, 0x0 },
    { textura_674354, 0x046F, 0x0800, 0x0 },
    { textura_ruta_0, 0x0300, 0x1000, 0x0 },
    { textura_meta_ruta_0, 0x0338, 0x1000, 0x0 },
    { textura_67B9B0, 0x0225, 0x0800, 0x0 },
    { textura_cartel_yoshi, 0x04DF, 0x1000, 0x0 },
    { textura_gris_azul_tablero, 0x04A1, 0x1000, 0x0 },
    { textura_cartel_disparo_caparazon_0, 0x038C, 0x1000, 0x0 },
    { textura_cartel_disparo_caparazon_1, 0x0247, 0x1000, 0x0 },
    { textura_cartel_koopa_aire_0, 0x0360, 0x1000, 0x0 },
    { textura_cartel_koopa_aire_1, 0x0304, 0x1000, 0x0 },
    { 0x00000000, 0x0000, 0x0000, 0x0 },
};

const Gfx* mario_raceway_dls[] = {
    d_circuito_mario_raceway_dl_0,    d_circuito_mario_raceway_dl_1D0,  d_circuito_mario_raceway_dl_E8,
    d_circuito_mario_raceway_dl_2C8,  d_circuito_mario_raceway_dl_3A8,  d_circuito_mario_raceway_dl_568,
    d_circuito_mario_raceway_dl_478,  d_circuito_mario_raceway_dl_668,  d_circuito_mario_raceway_dl_750,
    d_circuito_mario_raceway_dl_928,  d_circuito_mario_raceway_dl_828,  d_circuito_mario_raceway_dl_A00,
    d_circuito_mario_raceway_dl_B08,  d_circuito_mario_raceway_dl_DC8,  d_circuito_mario_raceway_dl_C20,
    d_circuito_mario_raceway_dl_F60,  d_circuito_mario_raceway_dl_10A8, d_circuito_mario_raceway_dl_1408,
    d_circuito_mario_raceway_dl_1210, d_circuito_mario_raceway_dl_15C8, d_circuito_mario_raceway_dl_1740,
    d_circuito_mario_raceway_dl_1A30, d_circuito_mario_raceway_dl_1850, d_circuito_mario_raceway_dl_1B70,
    d_circuito_mario_raceway_dl_1CF8, d_circuito_mario_raceway_dl_1F68, d_circuito_mario_raceway_dl_1DE0,
    d_circuito_mario_raceway_dl_20A0, d_circuito_mario_raceway_dl_21E8, d_circuito_mario_raceway_dl_2418,
    d_circuito_mario_raceway_dl_22E0, d_circuito_mario_raceway_dl_2558, d_circuito_mario_raceway_dl_2680,
    d_circuito_mario_raceway_dl_28B0, d_circuito_mario_raceway_dl_2790, d_circuito_mario_raceway_dl_2A10,
    d_circuito_mario_raceway_dl_2B40, d_circuito_mario_raceway_dl_2DC0, d_circuito_mario_raceway_dl_2C98,
    d_circuito_mario_raceway_dl_2EF8, d_circuito_mario_raceway_dl_3038, d_circuito_mario_raceway_dl_32D8,
    d_circuito_mario_raceway_dl_31F0, d_circuito_mario_raceway_dl_3458, d_circuito_mario_raceway_dl_35D0,
    d_circuito_mario_raceway_dl_3830, d_circuito_mario_raceway_dl_3748, d_circuito_mario_raceway_dl_3960,
    d_circuito_mario_raceway_dl_3AA0, d_circuito_mario_raceway_dl_3D68, d_circuito_mario_raceway_dl_3C08,
    d_circuito_mario_raceway_dl_3EB8, d_circuito_mario_raceway_dl_4038, d_circuito_mario_raceway_dl_42A0,
    d_circuito_mario_raceway_dl_4150, d_circuito_mario_raceway_dl_43D8, d_circuito_mario_raceway_dl_44F8,
    d_circuito_mario_raceway_dl_4738, d_circuito_mario_raceway_dl_4610, d_circuito_mario_raceway_dl_4840,
    d_circuito_mario_raceway_dl_4910, d_circuito_mario_raceway_dl_4B78, d_circuito_mario_raceway_dl_4A60,
    d_circuito_mario_raceway_dl_4CD8, d_circuito_mario_raceway_dl_4DC8, d_circuito_mario_raceway_dl_4FF0,
    d_circuito_mario_raceway_dl_4ED0, d_circuito_mario_raceway_dl_5150,
};
