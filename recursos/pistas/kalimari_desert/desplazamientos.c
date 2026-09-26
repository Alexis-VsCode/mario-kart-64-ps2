#include <PR/ultratypes.h>
#include "juego/desplazamientos_pista.h"
#include "datos_pista.h"

extern u8 textura_6684F8[];
extern u8 textura_cartel_luigis_0[];
extern u8 textura_cartel_luigis_1[];
extern u8 textura_cartel_mario_estrella_0[];
extern u8 textura_cartel_mario_estrella_1[];
extern u8 textura_cartel_nintendo_rojo_0[];
extern u8 textura_cartel_nintendo_rojo_1[];
extern u8 textura_67490C[];
extern u8 textura_cartel_yoshi[];
extern u8 textura_gris_azul_tablero[];
extern u8 textura_646CA8[];
extern u8 textura_6473E4[];
extern u8 textura_647994[];
extern u8 textura_668920[];
extern u8 textura_pista_ferrocarril[];
extern u8 textura_paso_a_nivel_pista[];
extern u8 textura_67291C[];
extern u8 textura_alambre_de_puas_cerca[];
extern u8 textura_67D304[];
extern u8 textura_67E010[];
extern u8 textura_67EEAC[];
extern u8 textura_cartel_disparo_caparazon_0[];
extern u8 textura_cartel_disparo_caparazon_1[];
extern u8 textura_cartel_koopa_aire_0[];
extern u8 textura_cartel_koopa_aire_1[];

const textura_circuito kalimari_desert_texturas[] = {
    { textura_6684F8, 0x010D, 0x0800, 0x0 },           { textura_cartel_luigis_0, 0x0287, 0x1000, 0x0 },
    { textura_cartel_luigis_1, 0x02AF, 0x1000, 0x0 },      { textura_cartel_mario_estrella_0, 0x02D2, 0x1000, 0x0 },
    { textura_cartel_mario_estrella_1, 0x02B1, 0x1000, 0x0 },   { textura_cartel_nintendo_rojo_0, 0x02A6, 0x1000, 0x0 },
    { textura_cartel_nintendo_rojo_1, 0x02F7, 0x1000, 0x0 }, { textura_67490C, 0x021C, 0x0800, 0x0 },
    { textura_cartel_yoshi, 0x04DF, 0x1000, 0x0 },        { textura_gris_azul_tablero, 0x04A1, 0x1000, 0x0 },
    { textura_646CA8, 0x073A, 0x1000, 0x0 },           { textura_6473E4, 0x05AD, 0x1000, 0x0 },
    { textura_647994, 0x05B5, 0x1000, 0x0 },           { textura_668920, 0x03D9, 0x0800, 0x0 },
    { textura_pista_ferrocarril, 0x0B5B, 0x1000, 0x0 },    { textura_paso_a_nivel_pista, 0x0208, 0x1000, 0x0 },
    { textura_67291C, 0x059C, 0x0800, 0x0 },           { textura_alambre_de_puas_cerca, 0x021E, 0x1000, 0x0 },
    { textura_67D304, 0x091C, 0x1000, 0x0 },           { textura_67E010, 0x0415, 0x0800, 0x0 },
    { textura_67EEAC, 0x0140, 0x0800, 0x0 },           { textura_cartel_disparo_caparazon_0, 0x038C, 0x1000, 0x0 },
    { textura_cartel_disparo_caparazon_1, 0x0247, 0x1000, 0x0 },   { textura_cartel_koopa_aire_0, 0x0360, 0x1000, 0x0 },
    { textura_cartel_koopa_aire_1, 0x0304, 0x1000, 0x0 },    { 0x00000000, 0x0000, 0x0000, 0x0 },
};

const Gfx* kalimari_desert_dls[] = {
    d_circuito_kalimari_desert_dl_0,    d_circuito_kalimari_desert_dl_258,  d_circuito_kalimari_desert_dl_100,
    d_circuito_kalimari_desert_dl_310,  d_circuito_kalimari_desierto_dl_4A0,  d_circuito_kalimari_desert_dl_778,
    d_circuito_kalimari_desierto_dl_5C0,  d_circuito_kalimari_desert_dl_858,  d_circuito_kalimari_desierto_dl_A58,
    d_circuito_kalimari_desierto_dl_CD0,  d_circuito_kalimari_desierto_dl_B38,  d_circuito_kalimari_desierto_dl_DD0,
    d_circuito_kalimari_desierto_dl_F68,  d_circuito_kalimari_desert_dl_1258, d_circuito_kalimari_desert_dl_1030,
    d_circuito_kalimari_desert_dl_1350, d_circuito_kalimari_desierto_dl_14C0, d_circuito_kalimari_desierto_dl_17C8,
    d_circuito_kalimari_desert_dl_1588, d_circuito_kalimari_desierto_dl_18C8, d_circuito_kalimari_desierto_dl_1A58,
    d_circuito_kalimari_desierto_dl_1D48, d_circuito_kalimari_desierto_dl_1B38, d_circuito_kalimari_desierto_dl_1E80,
    d_circuito_kalimari_desert_dl_2000, d_circuito_kalimari_desierto_dl_22D8, d_circuito_kalimari_desierto_dl_20E0,
    d_circuito_kalimari_desert_dl_2458, d_circuito_kalimari_desierto_dl_25D0, d_circuito_kalimari_desert_dl_2868,
    d_circuito_kalimari_desierto_dl_26E8, d_circuito_kalimari_desierto_dl_29C0, d_circuito_kalimari_desierto_dl_2B40,
    d_circuito_kalimari_desierto_dl_2DE8, d_circuito_kalimari_desierto_dl_2C88, d_circuito_kalimari_desierto_dl_2F30,
    d_circuito_kalimari_desert_dl_3068, d_circuito_kalimari_desierto_dl_32F8, d_circuito_kalimari_desierto_dl_31C0,
    d_circuito_kalimari_desert_dl_3460, d_circuito_kalimari_desert_dl_3590, d_circuito_kalimari_desert_dl_3818,
    d_circuito_kalimari_desert_dl_3718, d_circuito_kalimari_desert_dl_3998, d_circuito_kalimari_desierto_dl_3AC0,
    d_circuito_kalimari_desierto_dl_3DB8, d_circuito_kalimari_desierto_dl_3CA0, d_circuito_kalimari_desierto_dl_3FB0,
    d_circuito_kalimari_desierto_dl_40A8, d_circuito_kalimari_desert_dl_4358, d_circuito_kalimari_desert_dl_4280,
    d_circuito_kalimari_desert_dl_4538, d_circuito_kalimari_desert_dl_4630, d_circuito_kalimari_desierto_dl_49E0,
    d_circuito_kalimari_desert_dl_4908, d_circuito_kalimari_desierto_dl_4BA0, d_circuito_kalimari_desierto_dl_4CF0,
    d_circuito_kalimari_desierto_dl_4FB0, d_circuito_kalimari_desierto_dl_4EF8, d_circuito_kalimari_desert_dl_5100,
    d_circuito_kalimari_desert_dl_5208, d_circuito_kalimari_desert_dl_5470, d_circuito_kalimari_desierto_dl_53A0,
    d_circuito_kalimari_desierto_dl_55C8, d_circuito_kalimari_desert_dl_5730, d_circuito_kalimari_desert_dl_5978,
    d_circuito_kalimari_desert_dl_5898, d_circuito_kalimari_desierto_dl_5AD0, d_circuito_kalimari_desierto_dl_5BE8,
    d_circuito_kalimari_desierto_dl_5DF8, d_circuito_kalimari_desierto_dl_5D20, d_circuito_kalimari_desierto_dl_5F20,
    d_circuito_kalimari_desert_dl_6028, d_circuito_kalimari_desierto_dl_62F8, d_circuito_kalimari_desierto_dl_61B0,
    d_circuito_kalimari_desierto_dl_63E0, d_circuito_kalimari_desierto_dl_65B0, d_circuito_kalimari_desert_dl_6838,
    d_circuito_kalimari_desierto_dl_66F0, d_circuito_kalimari_desert_dl_6940,
};
