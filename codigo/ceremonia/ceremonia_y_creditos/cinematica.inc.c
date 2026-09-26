// Cinematica

void funcion_80284308(CamaraCinematica* camara) {
    Jugador** sp30[4] = { &jugador_uno, &jugador_dos, &jugador_tres, &jugador_cuatro };
    Jugador* ply;
    f32 x;
    f32 y;
    f32 z;

    evento_cinematica(reproducir_felicitacion_sonido, camara, 140, 140);
    mover_camara_cinematica_junto_spline(camara, (struct struct_80286A04*) dato_802858E0,
                                       (struct struct_80286A04*) dato_802858F8, 0);

    ply = *(sp30[0] + dato_802874D8.desconocido_1d);

    x = ply->pos[0] - jugador_uno->pos[0];
    y = ply->pos[1] - jugador_uno->pos[1];
    z = ply->pos[2] - jugador_uno->pos[2];

    camara->mirar_a[0] += x;
    camara->mirar_a[2] += z;
    camara->pos[0] += x;
    camara->pos[2] += z;
    camara->mirar_a[1] += y;
    camara->pos[1] += y;
}

struct struct_80282C40 dato_80285A10[] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF33D, 0x002F, 0xFE5A } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF36B, 0x0028, 0xFE76 } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3A6, 0x0027, 0xFE6F } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3C8, 0x002A, 0xFE4D } },
    { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3CF, 0x002F, 0xFE33 } },
};

struct struct_80282C40 dato_80285A4C[] = {
    { 0x00, 0x00, 0x00, 45, 0x00, 0x00, { 0xF4AC, 0xFFC1, 0xFD1A } },
    { 0x00, 0x00, 0x00, 45, 0x00, 0x00, { 0xF3D1, 0xFFF2, 0xFC8F } },
    { 0x00, 0x00, 0x00, 45, 0x00, 0x00, { 0xF2BA, 0xFFF2, 0xFCBA } },
    { 0x00, 0x00, 0x00, 45, 0x00, 0x00, { 0xF219, 0xFFF7, 0xFD56 } },
    { 0xFF, 0x00, 0x00, 45, 0x00, 0x00, { 0xF1E8, 0xFFED, 0xFDD9 } },
};

struct struct_80282C40 dato_80285A88[] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3D8, 0x0012, 0xFE0E } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3D8, 0x0012, 0xFE0E } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3D6, 0x001A, 0xFE0F } },
    { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3D7, 0x001D, 0xFE0F } },
};

struct struct_80282C40 dato_80285AB8[] = {
    { 0x00, 0x00, 0x00, 75, 0x00, 0x00, { 0xF1FB, 0x006C, 0xFE85 } },
    { 0x00, 0x00, 0x00, 45, 0x00, 0x00, { 0xF1FB, 0x006C, 0xFE85 } },
    { 0x00, 0x00, 0x00, 45, 0x00, 0x00, { 0xF225, 0x00FB, 0xFE7A } },
    { 0xFF, 0x00, 0x00, 45, 0x00, 0x00, { 0xF21C, 0x00EB, 0xFE7C } },
};

struct struct_80282C40 dato_80285AE8[] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3A3, 0x004C, 0xFE22 } },
    { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF3A3, 0x004C, 0xFE22 } },
};

struct struct_80282C40 dato_80285B00[] = {
    { 0x00, 0x00, 0x00, 30, 0x00, 0x00, { 0xF1BA, 0x0092, 0xFE22 } },
    { 0xFF, 0x00, 0x00, 30, 0x00, 0x00, { 0xF1BA, 0x0092, 0xFE22 } },
};

struct struct_80282C40 dato_80285B18[] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF496, 0x0029, 0xFF27 } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF496, 0x0029, 0xFF27 } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF4D5, 0xFFE3, 0xFF70 } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF54D, 0xFFE8, 0xFF9B } },
    { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF54D, 0xFFE8, 0xFF9B } },
};

struct struct_80282C40 dato_80285B54[] = {
    { 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, { 0xF307, 0x012F, 0xFE96 } },
    { 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, { 0xF307, 0x012F, 0xFE96 } },
    { 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, { 0xF326, 0x00CE, 0xFF12 } },
    { 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, { 0xF35A, 0x0000, 0xFF9E } },
    { 0xFF, 0x00, 0x00, 0x41, 0x00, 0x00, { 0xF35A, 0x0000, 0xFF9E } },
};

struct struct_80282C40 dato_80285B90[] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF5BB, 0x0008, 0xFE7E } },
    { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF5BB, 0x0008, 0xFE7E } },
};

struct struct_80282C40 dato_80285BA8[] = {
    { 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, { 0xF7A6, 0x0044, 0xFECC } },
    { 0xFF, 0x00, 0x00, 0x05, 0x00, 0x00, { 0xF7A6, 0x0044, 0xFECC } },

    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF690, 0x0018, 0xFE9E } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF690, 0x0018, 0xFE9E } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF690, 0x0018, 0xFE9E } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF6B9, 0x0021, 0xFEA5 } },
    { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF6CD, 0x001B, 0xFEA9 } },

    { 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, { 0xF4A5, 0xFFF0, 0xFE49 } },
    { 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, { 0xF4A5, 0xFFF0, 0xFE49 } },
    { 0x00, 0x00, 0x00, 0x47, 0x00, 0x00, { 0xF4A5, 0xFFF0, 0xFE49 } },
    { 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, { 0xF4CE, 0x0046, 0xFE4D } },
    { 0xFF, 0x00, 0x00, 0x1E, 0x00, 0x00, { 0xF4EB, 0x0084, 0xFE5C } },
};

struct struct_80282C40 dato_80285C38[] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF4ED, 0xFFEB, 0xFF66 } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF4ED, 0xFFEB, 0xFF66 } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF408, 0x0028, 0xFE82 } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF32B, 0x0062, 0xFDD6 } },
    { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF2A4, 0x006A, 0xFDA5 } },
};

struct struct_80282C40 dato_80285C74[] = {
    { 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, { 0xF616, 0xFFD8, 0x00F7 } },
    { 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, { 0xF616, 0xFFD8, 0x00F7 } },
    { 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, { 0xF558, 0xFFBB, 0xFFE4 } },
    { 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, { 0xF481, 0xFFF0, 0xFF30 } },
    { 0xFF, 0x00, 0x00, 0x28, 0x00, 0x00, { 0xF414, 0xFFED, 0xFEE1 } },
};

struct struct_80282C40 dato_80285CB0[] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF551, 0xFFE7, 0xFFA5 } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF551, 0xFFE7, 0xFFA5 } },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF54E, 0xFFE7, 0xFF82 } },
    { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, { 0xF544, 0xFFFA, 0xFF74 } },
};

struct struct_80282C40 dato_80285CE0[] = {
    { 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, { 0xF362, 0xFFF3, 0xFF62 } },
    { 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, { 0xF362, 0xFFF3, 0xFF62 } },
    { 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, { 0xF392, 0xFFF3, 0x0068 } },
    { 0xFF, 0x00, 0x00, 0x19, 0x00, 0x00, { 0xF3E1, 0xFF47, 0x00A2 } },
};

struct Cinematica escena_corte[] = {
    { funcion_80283D2C, 330 }, { funcion_802840C8, 270 }, { funcion_802842D8, 247 },
    { funcion_80284418, 200 }, { funcion_80284494, 170 }, { funcion_802844FC, 108 },
    { funcion_8028422C, 140 }, { funcion_802842A8, 270 }, { funcion_80284308, 0x7FFF },
};

void funcion_80284418(CamaraCinematica* camara) {
    evento_cinematica(reproducir_podio_sonido, camara, 0x52, 0x52);
    evento_cinematica(reproducir_podio_sonido, camara, 0x48, 0x48);
    evento_cinematica(reproducir_podio_sonido, camara, 0x3D, 0x3D);
    mover_camara_cinematica_junto_spline(camara, (struct struct_80286A04*) dato_80285A10,
                                       (struct struct_80286A04*) dato_80285A4C, 0);
}

void funcion_80284494(CamaraCinematica* camara) {
    evento_cinematica(reproducir_pez_sonido_2, camara, 0x1E, 0x1E);
    evento_cinematica(envoltura_func_8028100C, camara, 0, 0);
    mover_camara_cinematica_junto_spline(camara, (struct struct_80286A04*) dato_80285A88,
                                       (struct struct_80286A04*) dato_80285AB8, 0);
}

void funcion_802844FC(CamaraCinematica* camara) {
    evento_cinematica(reproducir_pez_sonido, camara, 0x3B, 0x3B);
    mover_camara_cinematica_junto_spline(camara, (struct struct_80286A04*) dato_80285AE8,
                                       (struct struct_80286A04*) dato_80285B00, 0);
}

void funcion_8028454C(CamaraCinematica* camara) {
    evento_cinematica(funcion_80283CA8, camara, 0, 0);
    evento_cinematica(envoltura_func_800CA0CC, camara, 1, 1);
    evento_cinematica(envoltura_func_800CB134, camara, 0, 0);
    evento_cinematica(envoltura_func_80280FFC, camara, 0x3C, 0x3C);
    mover_camara_cinematica_junto_spline(camara, (struct struct_80286A04*) dato_80285B18,
                                       (struct struct_80286A04*) dato_80285B54, 0);
}

void funcion_802845EC(CamaraCinematica* camara) {
    mover_camara_cinematica_junto_spline(camara, (struct struct_80286A04*) dato_80285B90,
                                       (struct struct_80286A04*) dato_80285BA8, 0);
}

void funcion_8028461C(CamaraCinematica* camara) {
    funcion_80283240(1);
    funcion_80283B6C(camara);
}

void funcion_80284648(CamaraCinematica* camara) {
    evento_cinematica(funcion_802845EC, camara, 0, 0);
    evento_cinematica(funcion_8028461C, camara, 0x110, 0x110);
    evento_cinematica(funcion_80283BA4, camara, 0x115, 0x115);
}

SIN_USO void funcion_802846AC(void) {
}

void funcion_802846B4(CamaraCinematica* camara) {
    mover_camara_cinematica_junto_spline(camara, (struct struct_80286A04*) dato_80285C38,
                                       (struct struct_80286A04*) dato_80285C74, 0);
}

void funcion_802846E4(CamaraCinematica* camara) {

    mover_camara_cinematica_junto_spline(camara, (struct struct_80286A04*) dato_80285CB0,
                                       (struct struct_80286A04*) dato_80285CE0, 0);
    camara->mirar_a[0] += (jugador_cuatro->pos[0] - -2796.0f);
    camara->mirar_a[1] += (jugador_cuatro->pos[1] - -29.0f);
    camara->mirar_a[2] += (jugador_cuatro->pos[2] - -97.0f);
    camara->pos[0] += (jugador_cuatro->pos[0] - -2796.0f);
    camara->pos[1] += (jugador_cuatro->pos[1] - -29.0f);
    camara->pos[2] += (jugador_cuatro->pos[2] - -97.0f);
}

struct Cinematica dato_80285D58[] = {
    { funcion_8028454C, 300 }, { funcion_80284154, 175 },    { funcion_802846B4, 200 },
    { funcion_802846E4, 184 }, { funcion_80284648, 0x7FFF },
};

struct struct_80285D80 dato_80285D80[] = {
    { { 0, 0, 0, 0, 0, 0 }, { 0xffc6, 0x0000, 0xfc02 } },    { { 0, 0, 0, 0, 4, 0 }, { 0xffb9, 0x0005, 0xff53 } },
    { { 0, 0, 0, 0, 10, 0 }, { 0xfec3, 0x0036, 0x009e } },   { { -1, 0, 0, 0, 0, 0 }, { 0xfc1a, 0xffdd, 0x0298 } },

    { { 0, 0, 0, 60, 0, 0 }, { 0xfeb1, 0xff45, 0xfd76 } },   { { 0, 0, 0, 60, 4, 0 }, { 0xfea7, 0xff73, 0x00da } },
    { { 0, 0, 0, 60, 10, 0 }, { 0xfd94, 0xff9b, 0x020b } },  { { -1, 0, 0, 60, 0, 0 }, { 0xfa7b, 0x003c, 0x039c } },

    { { 0, 0, 0, 0, 0, 0 }, { 0x04a7, 0x004f, 0x060b } },    { { 0, 0, 0, 0, 0, 0 }, { 0x04a7, 0x004f, 0x060b } },
    { { 0, 0, 0, 0, 0, 0 }, { 0x048a, 0x0068, 0x059a } },    { { 0, 0, 0, 0, 0, 0 }, { 0x0501, 0x0070, 0x04b7 } },
    { { -1, 0, 0, 0, 0, 0 }, { 0x0569, 0x0042, 0x0410 } },   { { 0, 0, 0, 18, 0, 0 }, { 0x051c, 0x00b9, 0x07e5 } },
    { { 0, 0, 0, 40, 0, 0 }, { 0x051c, 0x00b9, 0x07e5 } },   { { 0, 0, 0, 50, 0, 0 }, { 0x04f6, 0x0032, 0x077f } },
    { { 0, 0, 0, 50, 0, 0 }, { 0x040d, 0x0023, 0x0664 } },   { { -1, 0, 0, 50, 0, 0 }, { 0x044d, 0x000c, 0x05a8 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0x00d1, 0x0070, 0xf5ab } },    { { 0, 0, 0, 0, 0, 0 }, { 0x00d1, 0x0070, 0xf5ab } },
    { { 0, 0, 0, 0, 0, 0 }, { 0x0145, 0x0043, 0xf624 } },    { { -1, 0, 0, 0, 0, 0 }, { 0x01bb, 0x001b, 0xf6a9 } },
    { { 0, 0, 0, 20, 0, 0 }, { 0x01be, 0xff8b, 0xf723 } },   { { 0, 0, 0, 30, 0, 0 }, { 0x01be, 0xff8b, 0xf721 } },
    { { 0, 0, 0, 60, 0, 0 }, { 0x023d, 0xff7a, 0xf7a5 } },   { { -1, 0, 0, 60, 0, 0 }, { 0x02bb, 0x0047, 0xf854 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfd1a, 0x001f, 0x0aaa } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfd1a, 0x0016, 0x0890 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfd1b, 0x0017, 0x05ee } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfd24, 0x0013, 0x0325 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfcab, 0x0010, 0x01af } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfb52, 0x0013, 0x0094 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfa51, 0x001a, 0x0055 } },    { { -1, 0, 0, 0, 0, 0 }, { 0xf8f5, 0x001b, 0x0053 } },
    { { 0, 0, 0, 50, 0, 0 }, { 0xfd1f, 0xfeb7, 0x094f } },   { { 0, 0, 0, 50, 0, 0 }, { 0xfd21, 0xffdf, 0x069f } },
    { { 0, 0, 0, 50, 0, 0 }, { 0xfd35, 0x0012, 0x03fa } },   { { 0, 0, 0, 30, 0, 0 }, { 0xfd32, 0xffe5, 0x0133 } },
    { { 0, 0, 0, 30, 0, 0 }, { 0xfb92, 0x000e, 0x0011 } },   { { 0, 0, 0, 30, 0, 0 }, { 0xf993, 0x001c, 0xffb7 } },
    { { 0, 0, 0, 40, 0, 0 }, { 0xf866, 0x0009, 0xfffb } },   { { -1, 0, 0, 30, 0, 0 }, { 0xf712, 0xffe7, 0x00c8 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0x079c, 0x00de, 0xf99e } },    { { 0, 0, 0, 0, 0, 0 }, { 0x079c, 0x00de, 0xf99e } },
    { { 0, 0, 0, 0, 0, 0 }, { 0x077f, 0x0099, 0xf9a6 } },    { { 0, 0, 0, 0, 0, 0 }, { 0x0784, 0x005b, 0xf9a2 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0x0784, 0x005b, 0xf9a2 } },    { { -1, 0, 0, 0, 0, 0 }, { 0x0784, 0x005b, 0xf9a2 } },
    { { 0, 0, 0, 55, 0, 0 }, { 0x0886, 0xffaa, 0xf863 } },   { { 0, 0, 0, 55, 0, 0 }, { 0x0887, 0xffaa, 0xf864 } },
    { { 0, 0, 0, 55, 0, 0 }, { 0x0960, 0x0010, 0xf9ad } },   { { 0, 0, 0, 66, 0, 0 }, { 0x092b, 0x009e, 0xfaa4 } },
    { { 0, 0, 0, 50, 0, 0 }, { 0x0930, 0x00a9, 0xfa98 } },   { { 0, 0, 0, 50, 0, 0 }, { 0x0932, 0x00a9, 0xfa95 } },
    { { -1, 0, 0, 50, 0, 0 }, { 0x092f, 0x00a1, 0xfa9c } },  { { 0, 0, 0, 0, 0, 0 }, { 0xff37, 0x002d, 0xf9ab } },
    { { 0, 0, 0, 0, 0, 0 }, { 0x007b, 0x0035, 0xfaef } },    { { 0, 0, 0, 0, 0, 0 }, { 0x01a6, 0x002d, 0xfc8e } },
    { { -1, 0, 0, 0, 0, 0 }, { 0x0228, 0x0035, 0xfdad } },   { { 0, 0, 0, 60, 0, 0 }, { 0xfdc7, 0xffe6, 0xfaf6 } },
    { { 0, 0, 0, 60, 0, 0 }, { 0xfed8, 0xffee, 0xfbf4 } },   { { 0, 0, 0, 60, 0, 0 }, { 0xffdc, 0xffe6, 0xfd46 } },
    { { -1, 0, 0, 60, 0, 0 }, { 0x004b, 0xffe7, 0xfe2d } },  { { 0, 0, 0, 0, 0, 0 }, { 0xfc11, 0xffcd, 0x0096 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfc11, 0xffcd, 0x0096 } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfc16, 0x0096, 0x007c } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfc1e, 0x01e9, 0x0049 } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfc2c, 0x0419, 0xfff4 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfc4e, 0x0615, 0xffc1 } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfc31, 0x077f, 0xfff1 } },
    { { -1, 0, 0, 0, 0, 0 }, { 0xfc31, 0x077f, 0xfff1 } },   { { 0, 0, 0, 50, 0, 0 }, { 0xfc60, 0xff8e, 0xfead } },
    { { 0, 0, 0, 26, 0, 0 }, { 0xfc61, 0xff85, 0xfeae } },   { { 0, 0, 0, 45, 0, 0 }, { 0xfc64, 0x0015, 0xfe9f } },
    { { 0, 0, 0, 40, 0, 0 }, { 0xfc66, 0x0104, 0xfe93 } },   { { 0, 0, 0, 40, 0, 0 }, { 0xfcf6, 0x02c5, 0xfec2 } },
    { { 0, 0, 0, 33, 0, 0 }, { 0xfcd2, 0x0446, 0xff38 } },   { { 0, 0, 0, 30, 0, 0 }, { 0xfc82, 0x05b0, 0xff46 } },
    { { -1, 0, 0, 37, 0, 0 }, { 0xfc7d, 0x05ac, 0xff4d } },  { { 0, 0, 0, 0, 235, 0 }, { 0xfffb, 0x0047, 0xfe2b } },
    { { 0, 0, 0, 0, 225, 0 }, { 0xfff5, 0x0015, 0xfb8a } },  { { 0, 0, 0, 0, 245, 0 }, { 0x0143, 0x001f, 0xfab2 } },
    { { 0, 0, 0, 0, 39, 0 }, { 0x0230, 0x001d, 0xfaee } },   { { 0, 0, 0, 0, 25, 0 }, { 0x0294, 0x0012, 0xfb89 } },
    { { 0, 0, 0, 0, 228, 0 }, { 0x04b4, 0x001c, 0xfb7b } },  { { 0, 0, 0, 0, 226, 0 }, { 0x0545, 0x0011, 0xfc7c } },
    { { 0, 0, 0, 0, 244, 0 }, { 0x04aa, 0x001b, 0xfd89 } },  { { 0, 0, 0, 0, 0, 0 }, { 0x02f5, 0x000c, 0xfde2 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0x00cd, 0xffd6, 0xfde5 } },    { { 0, 0, 0, 0, 13, 0 }, { 0xfefa, 0xffdd, 0xfdcf } },
    { { 0, 0, 0, 0, 16, 0 }, { 0xfdd8, 0xfff9, 0xfe2b } },   { { -1, 0, 0, 0, 0, 0 }, { 0xfd15, 0x0006, 0xff68 } },
    { { 0, 0, 0, 30, 235, 0 }, { 0x0002, 0xffcd, 0xfc47 } }, { { 0, 0, 0, 30, 225, 0 }, { 0x00f6, 0xffc1, 0xf9e6 } },
    { { 0, 0, 0, 30, 245, 0 }, { 0x032d, 0xffbe, 0xfaad } }, { { 0, 0, 0, 20, 39, 0 }, { 0x02c7, 0xffff, 0xfcca } },
    { { 0, 0, 0, 30, 25, 0 }, { 0x047b, 0xffb4, 0xfb52 } },  { { 0, 0, 0, 20, 228, 0 }, { 0x05eb, 0xffed, 0xfcff } },
    { { 0, 0, 0, 30, 226, 0 }, { 0x053d, 0xffbc, 0xfe69 } }, { { 0, 0, 0, 30, 244, 0 }, { 0x02c8, 0xffb7, 0xfde1 } },
    { { 0, 0, 0, 30, 0, 0 }, { 0x0104, 0xffd6, 0xfe02 } },   { { 0, 0, 0, 30, 0, 0 }, { 0xfedf, 0xff8c, 0xfdef } },
    { { 0, 0, 0, 30, 13, 0 }, { 0xfd19, 0xff9e, 0xfe46 } },  { { 0, 0, 0, 30, 16, 0 }, { 0xfcc0, 0xffcd, 0xffc7 } },
    { { -1, 0, 0, 30, 0, 0 }, { 0xfc30, 0x0060, 0x011a } },  { { 0, 0, 0, 0, 0, 0 }, { 0xf4cf, 0x0217, 0x07f0 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xf575, 0x018b, 0x0622 } },    { { 0, 0, 0, 0, 0, 0 }, { 0xf5e3, 0x0123, 0x04ee } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xf6a2, 0x01a8, 0x02dc } },    { { 0, 0, 0, 0, 0, 0 }, { 0xf68b, 0x0262, 0x0050 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xf7b5, 0x0189, 0xfcdb } },    { { -1, 0, 0, 0, 0, 0 }, { 0xf8a8, 0x012d, 0xf7e1 } },
    { { 0, 0, 0, 30, 0, 0 }, { 0xf558, 0x00f2, 0x0673 } },   { { 0, 0, 0, 30, 0, 0 }, { 0xf5fe, 0x0065, 0x04a5 } },
    { { 0, 0, 0, 30, 0, 0 }, { 0xf665, 0xffe3, 0x0385 } },   { { 0, 0, 0, 30, 0, 0 }, { 0xf771, 0x011d, 0x012a } },
    { { 0, 0, 0, 30, 0, 0 }, { 0xf7f7, 0x0186, 0xff48 } },   { { 0, 0, 0, 30, 0, 0 }, { 0xf873, 0x0116, 0xfe9c } },
    { { -1, 0, 0, 42, 0, 0 }, { 0xf86d, 0x00e0, 0xf9cc } },  { { 0, 0, 0, 0, 0, 0 }, { 0x06d4, 0x00a6, 0xfae3 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0x06d4, 0x00a6, 0xfae3 } },    { { 0, 0, 0, 0, 0, 0 }, { 0x06fe, 0x0066, 0xf9cf } },
    { { 0, 0, 0, 0, 0, 0 }, { 0x04f6, 0x0046, 0xf966 } },    { { 0, 0, 0, 0, 0, 0 }, { 0x017c, 0x0053, 0xfa6c } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfec9, 0x003a, 0xfc36 } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfc6f, 0xffde, 0xfdc0 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfb17, 0xffbe, 0xfec7 } },    { { -1, 0, 0, 0, 0, 0 }, { 0xf96a, 0x00ab, 0x011b } },
    { { 0, 0, 0, 9, 0, 0 }, { 0x06db, 0xffd3, 0xfca8 } },    { { 0, 0, 0, 30, 0, 0 }, { 0x06dc, 0xffdc, 0xfcac } },
    { { 0, 0, 0, 25, 0, 0 }, { 0x077f, 0xffbe, 0xfb94 } },   { { 0, 0, 0, 25, 0, 0 }, { 0x06b5, 0xffbd, 0xfa16 } },
    { { 0, 0, 0, 25, 0, 0 }, { 0x0359, 0xffd6, 0xfa1e } },   { { 0, 0, 0, 25, 0, 0 }, { 0x005b, 0xffb1, 0xfb2f } },
    { { 0, 0, 0, 25, 0, 0 }, { 0xfdee, 0xff57, 0xfc9c } },   { { 0, 0, 0, 25, 0, 0 }, { 0xfc95, 0xff34, 0xfda4 } },
    { { -1, 0, 0, 25, 0, 0 }, { 0xfa96, 0xfff6, 0xffb7 } },  { { 0, 0, 0, 0, 0, 0 }, { 0xfaef, 0xff6e, 0xfdaa } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfaef, 0xff6e, 0xfdaa } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfb54, 0xff68, 0xfdbf } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfbb5, 0xff64, 0xfde0 } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfc0d, 0xff64, 0xfdfa } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfc9f, 0xff64, 0xfe2b } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfd80, 0xff61, 0xfe99 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfdca, 0xff66, 0xfeab } },    { { -1, 0, 0, 0, 0, 0 }, { 0xfe06, 0xff6d, 0xfebf } },
    { { 0, 0, 0, 30, 0, 0 }, { 0xf911, 0xff0f, 0xfe1a } },   { { 0, 0, 0, 30, 0, 0 }, { 0xf911, 0xff0f, 0xfe1a } },
    { { 0, 0, 0, 35, 0, 0 }, { 0xf9dd, 0xfe99, 0xfec0 } },   { { 0, 0, 0, 35, 0, 0 }, { 0xfb37, 0xfe86, 0xff8e } },
    { { 0, 0, 0, 35, 0, 0 }, { 0xfcc7, 0xfe7a, 0xff8b } },   { { 0, 0, 0, 35, 0, 0 }, { 0xfe21, 0xff1d, 0xff62 } },
    { { 0, 0, 0, 38, 0, 0 }, { 0xff5c, 0xff8e, 0xff2e } },   { { 0, 0, 0, 30, 0, 0 }, { 0xffa1, 0xff56, 0xff54 } },
    { { -1, 0, 0, 30, 0, 0 }, { 0xffdf, 0xff4e, 0xff5d } },  { { 0, 0, 0, 0, 0, 0 }, { 0x0326, 0x0016, 0xfbe5 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0x0326, 0x0016, 0xfbe5 } },    { { 0, 0, 0, 0, 0, 0 }, { 0x0279, 0x001c, 0xfbdc } },
    { { 0, 0, 0, 0, 0, 0 }, { 0x00e2, 0x0014, 0xfc78 } },    { { 0, 0, 0, 0, 0, 0 }, { 0x0010, 0x0015, 0xfdcf } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xffa5, 0x006f, 0xfead } },    { { -1, 0, 0, 0, 0, 0 }, { 0xffb3, 0x008e, 0xff63 } },
    { { 0, 0, 0, 30, 0, 0 }, { 0x0381, 0xffa1, 0xfdc3 } },   { { 0, 0, 0, 30, 0, 0 }, { 0x0381, 0xffa1, 0xfdc3 } },
    { { 0, 0, 0, 35, 0, 0 }, { 0x0237, 0xff21, 0xfd88 } },   { { 0, 0, 0, 35, 0, 0 }, { 0x005d, 0xff63, 0xfe39 } },
    { { 0, 0, 0, 35, 0, 0 }, { 0xfef8, 0x007d, 0xff60 } },   { { 0, 0, 0, 30, 0, 0 }, { 0xfe07, 0x00c8, 0xffb7 } },
    { { -1, 0, 0, 30, 0, 0 }, { 0xfdc3, 0x00d1, 0xff6a } },  { { 0, 0, 0, 0, 0, 0 }, { 0xfff9, 0x004d, 0xfd4b } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xff2a, 0x009e, 0xfcf8 } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfe1b, 0x0174, 0xfd03 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfc2c, 0x0163, 0xfbea } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfbc2, 0x003c, 0xfaa3 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfbf4, 0x0012, 0xf87d } },    { { -1, 0, 0, 0, 0, 0 }, { 0xfbf4, 0x0012, 0xf87d } },
    { { 0, 0, 0, 37, 0, 0 }, { 0xfedb, 0xff54, 0xfc06 } },   { { 0, 0, 0, 37, 0, 0 }, { 0xfeb0, 0xff91, 0xfb66 } },
    { { 0, 0, 0, 37, 0, 0 }, { 0xfe79, 0x0070, 0xfb62 } },   { { 0, 0, 0, 37, 0, 0 }, { 0xfde5, 0x00ac, 0xfb55 } },
    { { 0, 0, 0, 37, 0, 0 }, { 0xfd9b, 0x0079, 0xfb3c } },   { { 0, 0, 0, 48, 0, 0 }, { 0xfd0d, 0x0037, 0xfa1a } },
    { { -1, 0, 0, 30, 0, 0 }, { 0xfd20, 0x001d, 0xfa0d } },  { { 0, 0, 0, 0, 0, 0 }, { 0x0032, 0x0017, 0xfb25 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0x0032, 0x0011, 0xf7f3 } },    { { 0, 0, 0, 0, 0, 0 }, { 0xffef, 0x000a, 0xf6b4 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xff34, 0x0008, 0xf54e } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfe63, 0x0009, 0xf494 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfdd3, 0x0005, 0xf436 } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfcc0, 0x0005, 0xf3ec } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfba1, 0x0004, 0xf3e5 } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfa43, 0x0002, 0xf3d4 } },
    { { -1, 0, 0, 0, 0, 0 }, { 0xf96d, 0x0003, 0xf3f1 } },   { { 0, 0, 0, 30, 0, 0 }, { 0x0032, 0xff86, 0xf947 } },
    { { 0, 0, 0, 30, 0, 0 }, { 0x0042, 0xff4f, 0xf627 } },   { { 0, 0, 0, 30, 0, 0 }, { 0x0181, 0xff13, 0xf612 } },
    { { 0, 0, 0, 30, 0, 0 }, { 0x00eb, 0xff7e, 0xf60e } },   { { 0, 0, 0, 30, 0, 0 }, { 0x002b, 0xffc5, 0xf554 } },
    { { 0, 0, 0, 30, 0, 0 }, { 0xff90, 0xffb2, 0xf508 } },   { { 0, 0, 0, 30, 0, 0 }, { 0xfeb4, 0x0011, 0xf3e0 } },
    { { 0, 0, 0, 30, 0, 0 }, { 0xfd8c, 0x001a, 0xf386 } },   { { 0, 0, 0, 30, 0, 0 }, { 0xfc2b, 0x0067, 0xf3ae } },
    { { -1, 0, 0, 30, 0, 0 }, { 0xfb56, 0x0051, 0xf3ac } },  { { 0, 0, 0, 0, 0, 0 }, { 0xf49d, 0x001e, 0x003a } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xf4c9, 0x003c, 0x0039 } },    { { 0, 0, 0, 0, 0, 0 }, { 0xf4f7, 0x005a, 0x0038 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xf4f7, 0x005a, 0x0038 } },    { { 0, 0, 0, 0, 0, 0 }, { 0xf535, 0x0057, 0x0036 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xf6ae, 0x0036, 0x001d } },    { { 0, 0, 0, 0, 0, 0 }, { 0xf6ce, 0x0031, 0x001c } },
    { { -1, 0, 0, 0, 0, 0 }, { 0xf6ce, 0x0031, 0x001c } },   { { 0, 0, 0, 80, 0, 0 }, { 0xf669, 0xff5a, 0x004d } },
    { { 0, 0, 0, 80, 0, 0 }, { 0xf69d, 0xff8d, 0x004b } },   { { 0, 0, 0, 80, 0, 0 }, { 0xf6d6, 0xffc8, 0x003b } },
    { { 0, 0, 0, 5, 0, 0 }, { 0xf6d9, 0xffd3, 0x0040 } },    { { 0, 0, 0, 3, 0, 0 }, { 0xf717, 0xffd0, 0x0045 } },
    { { 0, 0, 0, 4, 0, 0 }, { 0xf894, 0xffc5, 0x000f } },    { { 0, 0, 0, 4, 0, 0 }, { 0xf8b8, 0xffcc, 0x001a } },
    { { -1, 0, 0, 4, 0, 0 }, { 0xf8b8, 0xffcc, 0x0014 } },   { { 0, 0, 0, 0, 0, 0 }, { 0xff61, 0x03ce, 0xf2bf } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfd33, 0x038d, 0xf40f } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfc59, 0x0366, 0xf4df } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfbe7, 0x0321, 0xf5d5 } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfb9a, 0x02a9, 0xf704 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfb58, 0x0220, 0xf8b1 } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfabf, 0x01f3, 0xfa36 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xf9f2, 0x01ef, 0xfb8d } },    { { 0, 0, 0, 0, 0, 0 }, { 0xf943, 0x01fe, 0xfd31 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xf950, 0x0200, 0xfea3 } },    { { 0, 0, 0, 0, 0, 0 }, { 0xf9cd, 0x0214, 0xff83 } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xface, 0x022d, 0x000d } },    { { -1, 0, 0, 0, 0, 0 }, { 0xfbd8, 0x0231, 0x000d } },
    { { 0, 0, 0, 20, 0, 0 }, { 0xfea7, 0x033c, 0xf478 } },   { { 0, 0, 0, 20, 0, 0 }, { 0xfcb7, 0x0306, 0xf5e1 } },
    { { 0, 0, 0, 20, 0, 0 }, { 0xfbf7, 0x02d4, 0xf6b4 } },   { { 0, 0, 0, 20, 0, 0 }, { 0xfb96, 0x0278, 0xf7a5 } },
    { { 0, 0, 0, 20, 0, 0 }, { 0xfb66, 0x0217, 0xf8e0 } },   { { 0, 0, 0, 20, 0, 0 }, { 0xfb26, 0x01c5, 0xfa9b } },
    { { 0, 0, 0, 20, 0, 0 }, { 0xfadd, 0x01eb, 0xfc29 } },   { { 0, 0, 0, 28, 0, 0 }, { 0xfa89, 0x0208, 0xfd69 } },
    { { 0, 0, 0, 29, 0, 0 }, { 0xfaf3, 0x020a, 0xfe2d } },   { { 0, 0, 0, 28, 0, 0 }, { 0xfb2b, 0x0226, 0xfe09 } },
    { { 0, 0, 0, 28, 0, 0 }, { 0xfb39, 0x0216, 0xfe2c } },   { { 0, 0, 0, 28, 0, 0 }, { 0xfb08, 0x0202, 0xfe1f } },
    { { -1, 0, 0, 28, 0, 0 }, { 0xfb31, 0x023f, 0xfe38 } },  { { 0, 0, 0, 0, 0, 0 }, { 0xfe5d, 0x01f9, 0xf67a } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfd7a, 0x0136, 0xf7ab } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfb8b, 0x0066, 0xfa4f } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xf9c4, 0x0032, 0xfc9f } },    { { 0, 0, 0, 0, 0, 0 }, { 0xf7b6, 0x0022, 0xfdda } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xf771, 0x0054, 0xfdec } },    { { -1, 0, 0, 0, 0, 0 }, { 0xf7df, 0x00a6, 0xfed5 } },
    { { 0, 0, 0, 30, 0, 0 }, { 0xfd5a, 0x0107, 0xf7db } },   { { 0, 0, 0, 30, 0, 0 }, { 0xfc6f, 0x0063, 0xf918 } },
    { { 0, 0, 0, 30, 0, 0 }, { 0xfa65, 0x002e, 0xfbe0 } },   { { 0, 0, 0, 30, 0, 0 }, { 0xf843, 0x0010, 0xfddc } },
    { { 0, 0, 0, 30, 0, 0 }, { 0xf5d2, 0x000c, 0xfe55 } },   { { 0, 0, 0, 30, 0, 0 }, { 0xf57e, 0x006c, 0xfde9 } },
    { { -1, 0, 0, 30, 0, 0 }, { 0xf5f2, 0x00a8, 0xfe82 } },  { { 0, 0, 0, 0, 0, 0 }, { 0xf8e5, 0x0181, 0x054b } },
    { { 0, 0, 0, 0, 0, 0 }, { 0xfae4, 0x00b9, 0x0556 } },    { { 0, 0, 0, 0, 0, 0 }, { 0xfccc, 0x0010, 0x0556 } },
    { { -1, 0, 0, 0, 0, 0 }, { 0xfd42, 0x0047, 0x056d } },   { { 0, 0, 0, 70, 0, 0 }, { 0xf88a, 0x00e8, 0x0378 } },
    { { 0, 0, 0, 70, 0, 0 }, { 0xfc3e, 0x001d, 0x0410 } },   { { 0, 0, 0, 70, 0, 0 }, { 0xfea3, 0x0041, 0x05f7 } },
    { { -1, 0, 0, 70, 0, 0 }, { 0xfeda, 0x0109, 0x0642 } },
};

struct struct_80286A10 {
    u16 desconocido0[4];
    struct struct_80285D80* desconocido8;
    struct struct_80285D80* desconocido_c;
};

#ifdef VERSION_EU
struct struct_80286A04 dato_80286A04[] = {

    { 0x01, 0x00, &dato_80285D80[162], &dato_80285D80[162], 0x0087 },
    { 0x00, 0x08, &dato_80285D80[0], &dato_80285D80[4], 0x00D1 },
    { 0x00, 0x09, &dato_80285D80[8], &dato_80285D80[13], 0x00D1 },
    { 0x00, 0x0B, &dato_80285D80[26], &dato_80285D80[34], 0x00D1 },
    { 0x00, 0x05, &dato_80285D80[18], &dato_80285D80[22], 0x00D1 },
    { 0x00, 0x02, &dato_80285D80[42], &dato_80285D80[48], 0x00D1 },
    { 0x00, 0x0E, &dato_80285D80[259], &dato_80285D80[263], 0x00D1 },
    { 0x00, 0x0C, &dato_80285D80[55], &dato_80285D80[59], 0x00D1 },
    { 0x00, 0x07, &dato_80285D80[63], &dato_80285D80[71], 0x00D1 },
    { 0x00, 0x01, &dato_80285D80[79], &dato_80285D80[92], 0x00D1 },
    { 0x00, 0x04, &dato_80285D80[105], &dato_80285D80[112], 0x00D2 },
    { 0x00, 0x12, &dato_80285D80[119], &dato_80285D80[128], 0x00D2 },
    { 0x00, 0x00, &dato_80285D80[155], &dato_80285D80[162], 0x00D2 },
    { 0x00, 0x06, &dato_80285D80[169], &dato_80285D80[176], 0x00D2 },
    { 0x00, 0x0A, &dato_80285D80[183], &dato_80285D80[193], 0x00D2 },
    { 0x00, 0x03, &dato_80285D80[203], &dato_80285D80[211], 0x00D2 },
    { 0x00, 0x0D, &dato_80285D80[219], &dato_80285D80[232], 0x00D2 },
    { 0x01, 0x00, &dato_80285D80[162], &dato_80285D80[162], 0x00D2 },
    { 0x02, 0x07, &dato_80285D80[245], &dato_80285D80[252], 0x00D2 },
};

u16 dato_80286B34[] = {
    0x0087, 0x00D5, 0x00D5, 0x00D5, 0x00D5, 0x00D5, 0x00D5, 0x00D5, 0x00D5, 0x00D5,
    0x00D5, 0x00D5, 0x00D5, 0x00D5, 0x00D4, 0x00D4, 0x00D4, 0x00DB, 0x00D2, 0x0000,
};

#else

struct struct_80286A04 dato_80286A04[] = {

    { 0x01, 0x00, &dato_80285D80[162], &dato_80285D80[162], 0x0096 },
    { 0x00, 0x08, &dato_80285D80[0], &dato_80285D80[4], 0x00F1 },
    { 0x00, 0x09, &dato_80285D80[8], &dato_80285D80[13], 0x00F1 },
    { 0x00, 0x0B, &dato_80285D80[26], &dato_80285D80[34], 0x00F1 },
    { 0x00, 0x05, &dato_80285D80[18], &dato_80285D80[22], 0x00F1 },
    { 0x00, 0x02, &dato_80285D80[42], &dato_80285D80[48], 0x00F1 },
    { 0x00, 0x0E, &dato_80285D80[259], &dato_80285D80[263], 0x00F1 },
    { 0x00, 0x0C, &dato_80285D80[55], &dato_80285D80[59], 0x00F1 },
    { 0x00, 0x07, &dato_80285D80[63], &dato_80285D80[71], 0x00F1 },
    { 0x00, 0x01, &dato_80285D80[79], &dato_80285D80[92], 0x00F1 },
    { 0x00, 0x04, &dato_80285D80[105], &dato_80285D80[112], 0x00F1 },
    { 0x00, 0x12, &dato_80285D80[119], &dato_80285D80[128], 0x00F0 },
    { 0x00, 0x00, &dato_80285D80[155], &dato_80285D80[162], 0x00F0 },
    { 0x00, 0x06, &dato_80285D80[169], &dato_80285D80[176], 0x00F0 },
    { 0x00, 0x0A, &dato_80285D80[183], &dato_80285D80[193], 0x00F0 },
    { 0x00, 0x03, &dato_80285D80[203], &dato_80285D80[211], 0x00F0 },
    { 0x00, 0x0D, &dato_80285D80[219], &dato_80285D80[232], 0x00F0 },
    { 0x01, 0x00, &dato_80285D80[162], &dato_80285D80[162], 0x00F2 },
    { 0x02, 0x07, &dato_80285D80[245], &dato_80285D80[252], 0x00F0 },
};

u16 dato_80286B34[] = {
    0x0096, 0x00F3, 0x00F3, 0x00F3, 0x00F3, 0x00F3, 0x00F3, 0x00F3, 0x00F3, 0x00F3,
    0x00F3, 0x00F3, 0x00F3, 0x00F3, 0x00F2, 0x00F2, 0x00F2, 0x00F9, 0x00F0, 0x0000,
};
#endif

void funcion_802847CC(CamaraCinematica* camara) {
    u16 sp2_e;
    u16 sp2_c;
    sp2_e = dato_80286A04[dato_800DC5E4].desconocido_c - (10 - (-(((u16) (u32) dato_802856B4))));
    sp2_c = dato_80286A04[dato_800DC5E4].desconocido_c;

    evento_cinematica(funcion_80283CD0, camara, 0, 0);
    evento_cinematica(reproducir_bienvenida_sonido, camara, 8, 8);
#ifdef VERSION_EU
    evento_cinematica(reproducir_ganador_ceremonia_creditos_secuencia, camara, 134, 134);
#else
    evento_cinematica(reproducir_ganador_ceremonia_creditos_secuencia, camara, 149, 149);
#endif
    evento_cinematica(reiniciar_envoltura_spline, camara, 0, 0);
    switch (dato_80286A04[dato_800DC5E4].desconocido0) {
        case 1:
            evento_cinematica(animacion_desaparece_deslizando_bordes, camara, 0, -1);
            evento_cinematica(envoltura_func_80092C80, camara, sp2_e - 0x14, sp2_e - 0x14);
            break;

        case 2:
            evento_cinematica(animacion_aparece_deslizando_bordes, camara, 0, 0);
            evento_cinematica(reproducir_despedida_sonido, camara, 247, 247);
            mover_camara_cinematica_junto_spline(camara, (struct struct_80286A04*) dato_80286A04[dato_800DC5E4].desconocido4,
                                               (struct struct_80286A04*) dato_80286A04[dato_800DC5E4].desconocido8, 0);
            break;
        default:
            evento_cinematica(animacion_aparece_deslizando_bordes, camara, 0, 0);
            evento_cinematica(animacion_desaparece_deslizando_bordes, camara, sp2_e, sp2_e);
            evento_cinematica(envoltura_func_80092C80, camara, sp2_e - 0x14, sp2_e - 0x14);
            mover_camara_cinematica_junto_spline(camara, (struct struct_80286A04*) dato_80286A04[dato_800DC5E4].desconocido4,
                                               (struct struct_80286A04*) dato_80286A04[dato_800DC5E4].desconocido8, 0);
            break;
    }

#ifndef VERSION_EU
    if (seleccion_cc == CC_EXTRA) {
        sp2_c = dato_80286B34[dato_800DC5E4];
    }
#endif

    if (temporizador_disparo_cinematica == sp2_c) {
        if (dato_80286A04[dato_800DC5E4].desconocido0 != 2) {
            funcion_80280268(dato_80286A04[dato_800DC5E4 + 1].desconocido1);
        }
    }
}

struct Cinematica dato_80286B5C[] = {
    { funcion_802847CC, 0x7FFF },
};

struct struct_80284AE8 {
    u8 desconocido0[0x1C];
    u8 desconocido_1c;
};

void reproducir_cinematica(CamaraCinematica* camara) {
    SIN_USO s32 relleno[3];
    s16 duracion_cinematica;

#define CINEMATICA(id, cinematica)                               \
    case id:                                                 \
        duracion_cinematica = cinematica[disparo_cinematica].duration; \
        cinematica[disparo_cinematica].disparo(camara);

    if (!camara->cinematica) {
        return;
    }
    switch (camara->cinematica) {
        CINEMATICA(2, escena_corte)
        break;
        CINEMATICA(3, escena_corte)
        break;
        CINEMATICA(4, escena_corte)
        break;
        CINEMATICA(5, dato_80285D58)
        reproducir_secuencia_ceremonia_perdiendo(camara);
        break;
        CINEMATICA(6, dato_80286B5C)
        break;
    }

#undef CINEMATICA

    if ((duracion_cinematica != 0) && ((temporizador_disparo_cinematica & 0xC000) == 0)) {

        if (temporizador_disparo_cinematica < 16383) {
            temporizador_disparo_cinematica++;
        }
        if (temporizador_disparo_cinematica == duracion_cinematica) {
            disparo_cinematica++;
            temporizador_disparo_cinematica = 0;
            reiniciar_spline();
        }
    } else {
        if (temporizador_disparo_cinematica & 0x4000) {
            temporizador_disparo_cinematica = 0;
            reiniciar_spline();
        } else {
            dato_802876D8 = 0;
            disparo_cinematica = 0;
            temporizador_disparo_cinematica = 0;
            reiniciar_spline();
        }
    }
}

void ceremonia_transicion_deslizando_bordes(void) {
    f32 temporal_f0;
    f32 temporal_f14;

    temporal_f14 = dato_802856B0 - bordes_deslizando_tamanio;
    if (temporal_f14 < 0.0f) {
        temporal_f14 = 0.0f;
    }
    temporal_f0 = dato_802856B0 + bordes_deslizando_tamanio;
    do {if (temporal_f0 > 240.0f) { temporal_f0 = 239.0f; } } while (0);

    gDPPipeSync(display_list_cabeza++);
    gDPSetRenderMode(display_list_cabeza++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCycleType(display_list_cabeza++, G_CYC_FILL);
    gDPSetFillColor(display_list_cabeza++, (GPACK_RGBA5551(0, 0, 0, 1) << 16 | GPACK_RGBA5551(0, 0, 0, 1)));
    gDPFillRectangle(display_list_cabeza++, 0, 0, 319, (s32) temporal_f14);
    gDPFillRectangle(display_list_cabeza++, 0, (s32) temporal_f0, 319, 239);
    gDPSetCycleType(display_list_cabeza++, G_CYC_1CYCLE);
    ajustar_transicion_valor_f32(&bordes_deslizando_tamanio, ordenado_tamanio_deslizando_bordes, dato_802856BC / dato_802856B4);
}
