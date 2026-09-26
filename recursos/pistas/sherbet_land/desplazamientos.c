#include <PR/ultratypes.h>
#include "juego/desplazamientos_pista.h"
#include "datos_pista.h"

extern u8 textura_643B3C[];
extern u8 textura_66D024[];
extern u8 textura_678118[];
extern u8 textura_cartel_flecha_rojo_madera[];
extern u8 textura_678CC8[];
extern u8 textura_67842C[];
extern u8 textura_67893C[];
extern u8 textura_651984[];
extern u8 textura_651428[];
extern u8 textura_662924[];

const textura_circuito sherbet_land_texturas[] = {
    { textura_643B3C, 0x0798, 0x0800, 0x0 }, { textura_66D024, 0x04EA, 0x0800, 0x0 },
    { textura_678118, 0x0314, 0x0800, 0x0 }, { textura_cartel_flecha_rojo_madera, 0x04E1, 0x1000, 0x0 },
    { textura_678CC8, 0x058E, 0x0800, 0x0 }, { textura_67842C, 0x050E, 0x0800, 0x0 },
    { textura_67893C, 0x038B, 0x0800, 0x0 }, { textura_651984, 0x019C, 0x0800, 0x0 },
    { textura_651428, 0x055B, 0x0800, 0x0 }, { textura_662924, 0x0110, 0x0800, 0x0 },
    { 0x00000000, 0x0000, 0x0000, 0x0 },
};

const Gfx* sherbet_land_dls[] = {
    d_circuito_sherbet_land_dl_0,    d_circuito_sherbet_land_dl_158,  d_circuito_sherbet_tierra_dl_C0,
    d_circuito_sherbet_tierra_dl_1A8,  d_circuito_sherbet_land_dl_280,  d_circuito_sherbet_tierra_dl_3B8,
    d_circuito_sherbet_land_dl_310,  d_circuito_sherbet_land_dl_400,  d_circuito_sherbet_tierra_dl_4E8,
    d_circuito_sherbet_land_dl_638,  d_circuito_sherbet_land_dl_560,  d_circuito_sherbet_tierra_dl_6A0,
    d_circuito_sherbet_land_dl_768,  d_circuito_sherbet_land_dl_880,  d_circuito_sherbet_tierra_dl_7A0,
    d_circuito_sherbet_tierra_dl_8E8,  d_circuito_sherbet_tierra_dl_9A0,  d_circuito_sherbet_tierra_dl_B08,
    d_circuito_sherbet_tierra_dl_A28,  d_circuito_sherbet_tierra_dl_BC0,  d_circuito_sherbet_tierra_dl_C88,
    d_circuito_sherbet_tierra_dl_DF0,  d_circuito_sherbet_tierra_dl_D10,  d_circuito_sherbet_tierra_dl_EC8,
    d_circuito_sherbet_tierra_dl_F68,  d_circuito_sherbet_tierra_dl_10D8, d_circuito_sherbet_land_dl_1028,
    d_circuito_sherbet_tierra_dl_11C8, d_circuito_sherbet_land_dl_1238, d_circuito_sherbet_land_dl_1368,
    d_circuito_sherbet_tierra_dl_12F0, d_circuito_sherbet_land_dl_1440, d_circuito_sherbet_land_dl_1480,
    d_circuito_sherbet_land_dl_1508, d_circuito_sherbet_tierra_dl_14C0, d_circuito_sherbet_land_dl_1570,
    d_circuito_sherbet_land_dl_1598, d_circuito_sherbet_land_dl_1638, d_circuito_sherbet_tierra_dl_15F0,
    d_circuito_sherbet_land_dl_1698, d_circuito_sherbet_tierra_dl_16C0, d_circuito_sherbet_land_dl_1778,
    d_circuito_sherbet_land_dl_1730, d_circuito_sherbet_tierra_dl_17D8, d_circuito_sherbet_land_dl_1828,
    d_circuito_sherbet_tierra_dl_18E8, d_circuito_sherbet_tierra_dl_18A0, d_circuito_sherbet_land_dl_1920,
    d_circuito_sherbet_tierra_dl_19A0, d_circuito_sherbet_tierra_dl_1A58, d_circuito_sherbet_tierra_dl_19F0,
    d_circuito_sherbet_tierra_dl_1A90, d_circuito_sherbet_tierra_dl_1AF8, d_circuito_sherbet_tierra_dl_1BA8,
    d_circuito_sherbet_tierra_dl_1B50, d_circuito_sherbet_tierra_dl_1C20, d_circuito_sherbet_tierra_dl_1C48,
    d_circuito_sherbet_tierra_dl_1D60, d_circuito_sherbet_tierra_dl_1D08, d_circuito_sherbet_tierra_dl_1E10,
    d_circuito_sherbet_tierra_dl_1E88, d_circuito_sherbet_land_dl_2010, d_circuito_sherbet_tierra_dl_1F70,
    d_circuito_sherbet_tierra_dl_20D0, d_circuito_sherbet_land_dl_2190, d_circuito_sherbet_tierra_dl_22F8,
    d_circuito_sherbet_land_dl_2288, d_circuito_sherbet_land_dl_2370, d_circuito_sherbet_land_dl_2438,
    d_circuito_sherbet_tierra_dl_25A0, d_circuito_sherbet_land_dl_2530, d_circuito_sherbet_tierra_dl_25F8,
};

const Gfx* sherbet_land_dls_2[] = {
    d_circuito_sherbet_tierra_dl_26D0, d_circuito_sherbet_tierra_dl_28A0, d_circuito_sherbet_tierra_dl_27F0,
    d_circuito_sherbet_land_dl_2918, d_circuito_sherbet_tierra_dl_2A38, d_circuito_sherbet_tierra_dl_2BE0,
    d_circuito_sherbet_tierra_dl_2B08, d_circuito_sherbet_tierra_dl_2C58, d_circuito_sherbet_tierra_dl_2D78,
    d_circuito_sherbet_tierra_dl_2F48, d_circuito_sherbet_tierra_dl_2E28, d_circuito_sherbet_tierra_dl_2FE8,
    d_circuito_sherbet_tierra_dl_30E0, d_circuito_sherbet_land_dl_3260, d_circuito_sherbet_land_dl_3150,
    d_circuito_sherbet_land_dl_3320, d_circuito_sherbet_tierra_dl_33E0, d_circuito_sherbet_tierra_dl_35A8,
    d_circuito_sherbet_land_dl_3490, d_circuito_sherbet_tierra_dl_36A8, d_circuito_sherbet_land_dl_3770,
    d_circuito_sherbet_land_dl_3940, d_circuito_sherbet_land_dl_3840, d_circuito_sherbet_tierra_dl_3A50,
    d_circuito_sherbet_tierra_dl_3AE0, d_circuito_sherbet_tierra_dl_3C48, d_circuito_sherbet_tierra_dl_3BA8,
    d_circuito_sherbet_tierra_dl_3D40, d_circuito_sherbet_tierra_dl_3D98, d_circuito_sherbet_tierra_dl_3EB8,
    d_circuito_sherbet_tierra_dl_3E58, d_circuito_sherbet_tierra_dl_3FA0, d_circuito_sherbet_tierra_dl_3FC0,
    d_circuito_sherbet_tierra_dl_3FE8, d_circuito_sherbet_tierra_dl_3FD8, d_circuito_sherbet_land_dl_4000,
    d_circuito_sherbet_land_dl_4010, d_circuito_sherbet_land_dl_4020, d_circuito_sherbet_land_dl_4018,
    d_circuito_sherbet_land_dl_4028, d_circuito_sherbet_land_dl_4030, d_circuito_sherbet_land_dl_4040,
    d_circuito_sherbet_land_dl_4038, d_circuito_sherbet_land_dl_4048, d_circuito_sherbet_land_dl_4050,
    d_circuito_sherbet_land_dl_4060, d_circuito_sherbet_land_dl_4058, d_circuito_sherbet_land_dl_4068,
    d_circuito_sherbet_land_dl_4070, d_circuito_sherbet_land_dl_4080, d_circuito_sherbet_land_dl_4078,
    d_circuito_sherbet_land_dl_4088, d_circuito_sherbet_land_dl_4090, d_circuito_sherbet_tierra_dl_40A0,
    d_circuito_sherbet_land_dl_4098, d_circuito_sherbet_tierra_dl_40A8, d_circuito_sherbet_tierra_dl_40B0,
    d_circuito_sherbet_tierra_dl_41B8, d_circuito_sherbet_land_dl_4180, d_circuito_sherbet_land_dl_4280,
    d_circuito_sherbet_tierra_dl_42E0, d_circuito_sherbet_land_dl_4470, d_circuito_sherbet_tierra_dl_43C8,
    d_circuito_sherbet_land_dl_4570, d_circuito_sherbet_land_dl_4618, d_circuito_sherbet_land_dl_4798,
    d_circuito_sherbet_land_dl_4710, d_circuito_sherbet_land_dl_4868, d_circuito_sherbet_land_dl_4930,
    d_circuito_sherbet_tierra_dl_4A98, d_circuito_sherbet_tierra_dl_4A20, d_circuito_sherbet_tierra_dl_4B20,
};
