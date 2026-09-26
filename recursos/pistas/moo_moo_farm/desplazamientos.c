#include <PR/ultratypes.h>
#include "juego/desplazamientos_pista.h"
#include "datos_pista.h"

extern u8 textura_puerta_madera_0[];
extern u8 textura_pasto_2[];
extern u8 textura_64AF50[];
extern u8 textura_64B090[];
extern u8 textura_64B54C[];
extern u8 textura_64B3F8[];
extern u8 textura_cartel_nintendo_0[];
extern u8 textura_cartel_nintendo_1[];
extern u8 textura_6684F8[];
extern u8 textura_cartel_luigis_0[];
extern u8 textura_cartel_luigis_1[];
extern u8 textura_cartel_mario_estrella_0[];
extern u8 textura_cartel_mario_estrella_1[];
extern u8 textura_674D58[];
extern u8 textura_675064[];
extern u8 textura_675220[];
extern u8 textura_6775EC[];
extern u8 textura_683314[];
extern u8 textura_68CDA0[];
extern u8 textura_6442D4[];
extern u8 textura_64440C[];
extern u8 textura_6446AC[];
extern u8 textura_moo_moo_farm_izquierda_cartel[];
extern u8 textura_moo_moo_farm_derecha_cartel[];
extern u8 textura_64ACAC[];
extern u8 textura_66D698[];
extern u8 textura_66EBF0[];
extern u8 textura_rueda_vapor_motor_real[];

const textura_circuito moo_moo_farm_texturas[] = {
    { textura_puerta_madera_0, 0x0294, 0x1000, 0x0 },
    { textura_pasto_2, 0x0415, 0x0800, 0x0 },
    { textura_64AF50, 0x0140, 0x0800, 0x0 },
    { textura_64B090, 0x0365, 0x0800, 0x0 },
    { textura_64B54C, 0x038C, 0x0800, 0x0 },
    { textura_64B3F8, 0x0153, 0x0800, 0x0 },
    { textura_cartel_nintendo_0, 0x0541, 0x1000, 0x0 },
    { textura_cartel_nintendo_1, 0x0512, 0x1000, 0x0 },
    { textura_6684F8, 0x010D, 0x0800, 0x0 },
    { textura_cartel_luigis_0, 0x0287, 0x1000, 0x0 },
    { textura_cartel_luigis_1, 0x02AF, 0x1000, 0x0 },
    { textura_cartel_mario_estrella_0, 0x02D2, 0x1000, 0x0 },
    { textura_cartel_mario_estrella_1, 0x02B1, 0x1000, 0x0 },
    { textura_674D58, 0x030C, 0x1000, 0x0 },
    { textura_675064, 0x01BB, 0x0800, 0x0 },
    { textura_675220, 0x0212, 0x0800, 0x0 },
    { textura_6775EC, 0x0233, 0x1000, 0x0 },
    { textura_683314, 0x02DC, 0x1000, 0x0 },
    { textura_68CDA0, 0x0110, 0x0800, 0x0 },
    { textura_6442D4, 0x0138, 0x0800, 0x0 },
    { textura_64440C, 0x029D, 0x1000, 0x0 },
    { textura_6446AC, 0x0116, 0x0800, 0x0 },
    { textura_moo_moo_farm_izquierda_cartel, 0x0A66, 0x1000, 0x0 },
    { textura_moo_moo_farm_derecha_cartel, 0x0A64, 0x1000, 0x0 },
    { textura_64ACAC, 0x02A3, 0x0800, 0x0 },
    { textura_66D698, 0x0370, 0x0800, 0x0 },
    { textura_66EBF0, 0x0146, 0x0800, 0x0 },
    { textura_rueda_vapor_motor_real, 0x022F, 0x1000, 0x0 },
    { 0x00000000, 0x0000, 0x0000, 0x0 },
};

const Gfx* moo_moo_farm_dls[] = {
    d_circuito_moo_moo_farm_dl_88,   d_circuito_moo_moo_farm_dl_598,  d_circuito_moo_moo_farm_dl_338,
    d_circuito_moo_moo_farm_dl_8A0,  d_circuito_moo_moo_farm_dl_B00,  d_circuito_moo_moo_farm_dl_FE0,
    d_circuito_moo_moo_farm_dl_D70,  d_circuito_moo_moo_farm_dl_12B8, d_circuito_moo_moo_farm_dl_1530,
    d_circuito_moo_moo_farm_dl_1A20, d_circuito_moo_moo_farm_dl_1790, d_circuito_moo_moo_farm_dl_1D00,
    d_circuito_moo_moo_farm_dl_1F58, d_circuito_moo_moo_farm_dl_2470, d_circuito_moo_moo_farm_dl_2190,
    d_circuito_moo_moo_farm_dl_27A8, d_circuito_moo_moo_farm_dl_2A10, d_circuito_moo_moo_farm_dl_2F20,
    d_circuito_moo_moo_farm_dl_2C38, d_circuito_moo_moo_farm_dl_3238, d_circuito_moo_moo_farm_dl_34A0,
    d_circuito_moo_moo_farm_dl_39F8, d_circuito_moo_moo_farm_dl_36B8, d_circuito_moo_moo_farm_dl_3CB0,
    d_circuito_moo_moo_farm_dl_3EB8, d_circuito_moo_moo_farm_dl_4428, d_circuito_moo_moo_farm_dl_4098,
    d_circuito_moo_moo_farm_dl_46D8, d_circuito_moo_moo_farm_dl_4910, d_circuito_moo_moo_farm_dl_4E00,
    d_circuito_moo_moo_farm_dl_4AD0, d_circuito_moo_moo_farm_dl_5040, d_circuito_moo_moo_farm_dl_5290,
    d_circuito_moo_moo_farm_dl_5758, d_circuito_moo_moo_farm_dl_5458, d_circuito_moo_moo_farm_dl_5990,
    d_circuito_moo_moo_farm_dl_5BF8, d_circuito_moo_moo_farm_dl_60A8, d_circuito_moo_moo_farm_dl_5DF0,
    d_circuito_moo_moo_farm_dl_62D0, d_circuito_moo_moo_farm_dl_6548, d_circuito_moo_moo_farm_dl_6A70,
    d_circuito_moo_moo_farm_dl_6778, d_circuito_moo_moo_farm_dl_6CB8, d_circuito_moo_moo_farm_dl_6FF0,
    d_circuito_moo_moo_farm_dl_74C8, d_circuito_moo_moo_farm_dl_7218, d_circuito_moo_moo_farm_dl_7718,
    d_circuito_moo_moo_farm_dl_7A80, d_circuito_moo_moo_farm_dl_7F78, d_circuito_moo_moo_farm_dl_7CD8,
    d_circuito_moo_moo_farm_dl_81E8, d_circuito_moo_moo_farm_dl_84D0, d_circuito_moo_moo_farm_dl_89A0,
    d_circuito_moo_moo_farm_dl_8728, d_circuito_moo_moo_farm_dl_8C00, d_circuito_moo_moo_farm_dl_8F18,
    d_circuito_moo_moo_farm_dl_93D0, d_circuito_moo_moo_farm_dl_9178, d_circuito_moo_moo_farm_dl_9640,
    d_circuito_moo_moo_farm_dl_9938, d_circuito_moo_moo_farm_dl_9DF8, d_circuito_moo_moo_farm_dl_9BB0,
    d_circuito_moo_moo_farm_dl_A010, d_circuito_moo_moo_farm_dl_A2C0, d_circuito_moo_moo_farm_dl_A7B0,
    d_circuito_moo_moo_farm_dl_A568, d_circuito_moo_moo_farm_dl_A9C8, d_circuito_moo_moo_farm_dl_ACB0,
    d_circuito_moo_moo_farm_dl_B230, d_circuito_moo_moo_farm_dl_B020, d_circuito_moo_moo_farm_dl_B478,
    d_circuito_moo_moo_farm_dl_B798, d_circuito_moo_moo_farm_dl_BCE8, d_circuito_moo_moo_farm_dl_BB00,
    d_circuito_moo_moo_farm_dl_BF10, d_circuito_moo_moo_farm_dl_C180, d_circuito_moo_moo_farm_dl_C6D8,
    d_circuito_moo_moo_farm_dl_C4F8, d_circuito_moo_moo_farm_dl_C950, d_circuito_moo_moo_farm_dl_CBC8,
    d_circuito_moo_moo_farm_dl_D140, d_circuito_moo_moo_farm_dl_CF58, d_circuito_moo_moo_farm_dl_D408,
    d_circuito_moo_moo_farm_dl_D6B0, d_circuito_moo_moo_farm_dl_DC70, d_circuito_moo_moo_farm_dl_DA50,
    d_circuito_moo_moo_farm_dl_DF60, d_circuito_moo_moo_farm_dl_E1D8, d_circuito_moo_moo_farm_dl_E708,
    d_circuito_moo_moo_farm_dl_E4B0, d_circuito_moo_moo_farm_dl_EA18,
};
