// Sesion audio

s8 dato_8018EF10;
StructDesconocido8018EF18 dato_8018EF18[16];
struct desconocido_8018EFD8 dato_8018EFD8[50];
u8 dato_8018FB90;
u8 dato_8018FB91;
Camara* camara_copia[4];
Vec3f camara_velocidad[4];
Vec3f pos_ultimo_camara[4];
u8 dato_8018FC08;
s16 dato_8018FC10[4][2];
struct Sonido sonido_pedidos[0x100];
struct SonidoCaracteristicas sonido_bancos[SONIDO_CANTIDAD_BANCO][20];
u8 sonido_banco_usado_lista_atras[SONIDO_CANTIDAD_BANCO];
u8 sonido_banco_libre_lista_frente[SONIDO_CANTIDAD_BANCO];
u8 sonidos_num_en_banco[SONIDO_CANTIDAD_BANCO];
u8 dato_80192AB8[SONIDO_CANTIDAD_BANCO][8][8];
u8 dato_80192C38;
ubool8 sonido_banco_desactivado[SONIDO_CANTIDAD_BANCO];
struct CanalVolumenEscalaFundido dato_80192C48[SONIDO_CANTIDAD_BANCO];
struct_d_80192CA8_entrada dato_80192CA8[3][5];
u8 dato_80192CC6[3];
u32 dato_80192CD0[256];
struct_d_801930D0_entrada dato_801930D0[3];

u8 dato_800E9DA0 = 0;
SIN_USO s32 dato_800E9DA4[] = { 0, 0, 0, 0 };
s32 dato_800E9DB4[] = { 0, 0, 0, 0 };
f32 dato_800E9DC4[] = { 1.0f, 1.0f, 1.0f, 1.0f };
f32 dato_800E9DD4[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 dato_800E9DE4[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 dato_800E9DF4[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
s32 dato_800E9E14[] = { 0, 0, 0, 0 };
s32 dato_800E9E24[] = { 0, 0, 0, 0 };
s32 dato_800E9E34[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
f32 dato_800E9E54[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 dato_800E9E64[] = { 0.0f, 0.0f, 0.0f, 0.0f };
s32 dato_800E9E74[] = { 0, 0, 0, 0 };
s32 dato_800E9E84[] = { 0, 0, 0, 0 };
u32 dato_800E9E94[] = { 0, 0, 0, 0 };
s32 dato_800E9EA4[] = { 0, 0, 0, 0 };
f32 dato_800E9EB4[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 dato_800E9EC4[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 dato_800E9ED4[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 dato_800E9EE4[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 dato_800E9EF4[] = { 1.0f, 1.0f, 1.0f, 1.0f };
f32 dato_800E9F04[] = { 1.0f, 1.0f, 1.0f, 1.0f };
f32 dato_800E9F14[] = { 1.0f, 1.0f, 1.0f, 1.0f };
u8 dato_800E9F24[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
u8 dato_800E9F2C[JUGADORES_NUM] = { 0, 0, 0, 0, 0, 0, 0, 0 };
f32 dato_800E9F34[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
f32 dato_800E9F54[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
u8 dato_800E9F74[] = { 0, 0, 0, 0 };
u8 dato_800E9F78[] = { 0, 0, 0, 0 };
struct desconocido_800E9F7C dato_800E9F7C[] = {
    { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, 3800.0f, 3.4f, 0.4f, -1.0f, 0.4f, 1100.0f, 630.0f, 3600.0f, 1.0f },
    { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, 3800.0f, 3.4f, 0.4f, -1.0f, 0.4f, 1100.0f, 630.0f, 3600.0f, 1.0f },
    { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, 3800.0f, 3.4f, 0.4f, -1.0f, 0.4f, 1100.0f, 630.0f, 3600.0f, 1.0f },
    { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, 3800.0f, 3.4f, 0.4f, -1.0f, 0.4f, 1100.0f, 630.0f, 3600.0f, 1.0f }
};
struct desconocido_800EA06C dato_800EA06C[] = { { { 0.0f, 1.0f, 1.0f }, 0 }, { { 0.0f, 1.0f, 1.0f }, 0 },
                                     { { 0.0f, 1.0f, 1.0f }, 0 }, { { 0.0f, 1.0f, 1.0f }, 0 },
                                     { { 0.0f, 1.0f, 1.0f }, 0 }, { { 0.0f, 1.0f, 1.0f }, 0 },
                                     { { 0.0f, 1.0f, 1.0f }, 0 }, { { 0.0f, 1.0f, 1.0f }, 0 } };
u8 dato_800EA0EC[] = { 0, 0, 0, 0 };
u8 dato_800EA0F0 = 0;
u8 dato_800EA0F4 = 0;
SIN_USO Vec3f dato_800EA0F8 = { 0.0f, 0.0f, 1.0f };
u8 dato_800EA104 = 0;
u8 dato_800EA108 = 0;
u8 dato_800EA10C[] = { 0, 0, 0, 0 };
f32 dato_800EA110[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 dato_800EA120[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 dato_800EA130[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
f32 dato_800EA150 = 1.4f;
u8 dato_800EA154[] = { 2, 2, 88, 90, 3, 48, 88, 48 };
u16 dato_800EA15C = 0;
u16 dato_800EA160 = 0;
u8 dato_800EA164 = 0;
s8 dato_800EA168 = 0;
s8 dato_800EA16C = 0;
u8 dato_800EA170[] = { 0, 0, 0, 0 };
u16 dato_800EA174 = 0;
f32 dato_800EA178 = 1.0f;
f32 dato_800EA17C = 0.85f;
u16 dato_800EA180 = 0;
u16 dato_800EA184 = 0;
u8 dato_800EA188[][6] = { { 4, 2, 2, 2, 2, 1 }, { 6, 2, 2, 2, 2, 1 }, { 8, 2, 2, 0, 1, 1 }, { 8, 2, 2, 0, 1, 1 } };
u8 dato_800EA1A0[][6] = { { 4, 1, 1, 2, 2, 1 }, { 3, 1, 1, 2, 2, 1 }, { 3, 1, 1, 0, 1, 1 }, { 3, 1, 1, 0, 1, 1 } };
u8 sonido_cantidad_pedido = 0;
u8 num_procesado_sonido_pedidos = 0;
u8 dato_800EA1C0 = 0;
u16 dato_800EA1C4 = 0;
Vec3f dato_800EA1C8 = { 0.0f, 0.0f, 0.0f };
f32 dato_800EA1D4 = 1.0f;
u32 externo_sin_uso_u32_0 = 0x00000000;
s8 dato_800EA1DC = 0;
u32 externo_sin_uso_u32_1 = 0x00000000;
u8 dato_800EA1E4 = 0;
u8 dato_800EA1E8 = 0;
u8 dato_800EA1EC = 0;
u8 dato_800EA1F0[] = { 0, 1, 2, 3 };
u8 dato_800EA1F4[] = { 0, 0, 0, 0 };

char cadena00_sin_uso_externo[] = "Error : Queue is not empty ( %x ) \n";
char cadena01_sin_uso_externo[] = "specchg error\n";
char cadena02_sin_uso_externo[] = "***** CAM MAX %d *****\n";
u8 dato_800EA244 = 0;
char cadena03_sin_uso_externo[] = "entryout !!! %d\n";
char cadena04_sin_uso_externo[] = "AFTER GOAL VOICE FLAME %d\n";
char cadena05_sin_uso_externo[] = "*** Pause On ***\n";
char cadena06_sin_uso_externo[] = "*** Pause Off ***\n";
char cadena07_sin_uso_externo[] = "CALLED!! Na_ChangeSoundMode player %d\n";
char cadena08_sin_uso_externo[] = "CALLED!! Na_ChangeSoundMode spec   %d\n";
char cadena09_sin_uso_externo[] = "Interfaced Spec Change player %d\n";
char cadena10_sin_uso_externo[] = "Interfaced Spec Change spec   %d\n";
SIN_USO u32 externo_sin_uso_u32s[] = { 0xff000000, 0xff000000, 0x00000000 };
char cadena11_sin_uso_externo[] = "FX MIX %d\n";
char cadena12_sin_uso_externo[] = "************** Seq Fadeout ***************\n";
char cadena13_sin_uso_externo[] = "SEQ FADE OUT TIME %d\n";
#ifdef VERSION_EU
char externo_sin_uso_cadena_eu_02[] = "************** SE Fadeout ***************\n";
char externo_sin_uso_cadena_eu_03[] = "SE FADE OUT TIME %d\n";
#endif

#ifdef VERSION_EU
#define RUEDA_IZQUIERDA_AUDIO IZQUIERDA_FRENTE
#define RUEDA_DERECHA_AUDIO DERECHA_FRENTE
#else
#define RUEDA_IZQUIERDA_AUDIO IZQUIERDA_ATRAS
#define RUEDA_DERECHA_AUDIO DERECHA_ATRAS
#endif

void funcion_800C13F0(void) {
}

void reiniciar_eu_sesion_audio(OSMesg id_ajuste) {
    OSMesg msj;
    osRecvMesg(dato_800EA3B4, &msj, 0);
    osSendMesg(dato_800EA3B0, id_ajuste, 0);
    osRecvMesg(dato_800EA3B4, &msj, 1);
    if (msj != id_ajuste) {
        osRecvMesg(dato_800EA3B4, &msj, 1);
    }
}

f32 funcion_800C1480(u8 banco, u8 sonido_id) {
    f32 temporal_f0;
    f32 variable_f2;
    s32 variable_v0;
    struct SonidoCaracteristicas* temporal_v0;

    temporal_v0 = &sonido_bancos[banco][sonido_id];
    if (temporal_v0->sonido_bits & 0x400000) {
        return 1.0f;
    }
    temporal_f0 = temporal_v0->distancia;
    if (temporal_f0 > 2000.0f) {
        variable_f2 = 0.0f;
    } else {
        switch (temporal_v0->sonido_bits & 0x30000) { /* irregular */
            case 0x10000:
                variable_v0 = 0x1F4;
                break;
            case 0x20000:
                variable_v0 = 0x29A;
                break;
            case 0x30000:
                variable_v0 = 0x3E8;
                break;
            default:
                variable_v0 = 0x190;
                break;
        }
        if (temporal_f0 < variable_v0) {
            variable_f2 = (((variable_v0 - temporal_f0) / variable_v0) * 0.5) + 0.5;
        } else {
            variable_f2 = (1.0 - ((temporal_f0 - variable_v0) / (2000.0f - variable_v0))) * 0.5;
        }
        variable_f2 *= variable_f2;
    }
    return variable_f2;
}

s8 funcion_800C15D0(u8 banco, u8 sonido_id, u8 canal) {
    s32 variable_a0;
    s8 variable_v0;
    s8 variable_v1;

    variable_v0 = 0;
    variable_v1 = 0;
    if (!(sonido_bancos[banco][sonido_id].sonido_bits & 0x200000)) {
        if (sonido_bancos[banco][sonido_id].distancia < 500.0f) {
            variable_v0 = (sonido_bancos[banco][sonido_id].distancia / 500.0f) * 10.0f;
        } else {
            variable_v0 = 0x0A;
        }
    }
    if (ES_SECUENCIA_CANAL_VALIDO(jugadores_secuencia[2].channels[canal])) {
        variable_v1 = jugadores_secuencia[2].channels[canal]->sonido_io_guion[6];
    }
    if (variable_v1 == -1) {
        variable_v1 = 0;
    }
    variable_a0 = *sonido_bancos[banco][sonido_id].unk18 + variable_v0 + variable_v1 + dato_8018EF10;
    if (variable_a0 >= 0x80) {
        variable_a0 = 0x7F;
    }
    return variable_a0;
}

s8 funcion_800C16E8(f32 parametro0, f32 parametro1, u8 id_camara) {
    f32 variable_f0;
    f32 variable_f14;
    f32 variable_nuevo;
    f32* variable2_nuevo;
    f32 variable_f16;
    f32 variable_f18;
    f32 variable_f20;
    f32 variable_f2;
    variable2_nuevo = &variable_f0;

    if (dato_800EA1C0 == 0) {
        if (dato_800EA0F4 != 0) {
            variable_f2 = 10.0f;
            variable_f14 = 20.0f;
            variable_f16 = 10.0f;
            variable_f18 = 2.5f;
        } else {
            variable_f0 = 100.0f;
            variable_f2 = *variable2_nuevo;
            variable_f14 = 200.0f;
            variable_f16 = 5.0f;
            variable_f18 = 3.3333333f;
        }
        variable_f20 = (parametro0 < 0.0f) ? -parametro0 : parametro0;

        if (variable_f2 < variable_f20) {
            variable_f20 = variable_f2;
        }

        variable_nuevo = parametro0;
        variable_f0 = (parametro1 < 0.0f) ? -parametro1 : parametro1;
        if (variable_f2 < (variable_f0 = *variable2_nuevo)) {
            variable_f0 = variable_f2;
        }
        if ((variable_nuevo == 0.0f) && (parametro1 == 0.0f)) {
            variable_f2 = 0.5f;
        } else if ((variable_nuevo >= 0.0f) && (variable_f0 <= variable_f20)) {
            variable_f2 = 1.0f - ((variable_f14 - variable_f20) / (variable_f16 * (variable_f14 - variable_f0)));
        } else if ((variable_nuevo < 0.0f) && (variable_f0 <= variable_f20)) {
            variable_f2 = (variable_f14 - variable_f20) / (variable_f16 * (variable_f14 - variable_f0));
        } else {
            variable_f2 = (parametro0 / (variable_f18 * variable_f0)) + 0.5f;
        }
        if (variable_f2 > 1.0f) {
            variable_f2 = 1.0f;
        }
        if (variable_f2 < 0.0f) {
            variable_f2 = 0.0f;
        }
        return (s8) (s32) ((variable_f2 * 127.0f) + 0.5f);
    }
    return (id_camara & 1) * 0x7F;
}

f32 funcion_800C1934(u8 banco, u8 sonido_id) {
    f32 phi_f2;

    phi_f2 = 1.0f;
    if (sonido_bancos[banco][sonido_id].sonido_bits & 0x800000) {
        phi_f2 -= ((aleatorio_audio & 0xF) / 192.0f);
    }
    return phi_f2;
}

void funcion_800C19D0(u8 parametro0, u8 parametro1, u8 parametro2) {
    f32 sp3_c;
    s8 sp3_b;
    f32 sp34;
    s8 sp33;
    StructDesconocido8018EF18* temporal_s0_2;
    struct SonidoCaracteristicas* temporal_s0;

    sp3_b = 0;
    sp33 = 0x40;
    sp3_c = 1.0f;
    sp34 = 1.0f;
    switch (parametro0) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            temporal_s0 = &sonido_bancos[parametro0][parametro1];
            temporal_s0->distancia = sqrtf(temporal_s0->distancia);
            sp3_c = (funcion_800C1480(parametro0, parametro1) * *temporal_s0->unk14) * dato_80192C48[parametro0].current;
            sp3_b = funcion_800C15D0(parametro0, parametro1, parametro2);
            sp34 = funcion_800C1934(parametro0, parametro1) * *temporal_s0->unk10;
            sp33 = funcion_800C16E8(*temporal_s0->unk00[0], *temporal_s0->desconocido08, temporal_s0->id_camara);
            break;
    }
    temporal_s0_2 = &dato_8018EF18[parametro2];
    if (sp3_c != temporal_s0_2->desconocido0) {
        funcion_800CBBE8(((parametro2 & 0xFF) << 8) | 0x06020000 | 3, (u8) (u32) (sp3_c * 127.0f));
        temporal_s0_2->desconocido0 = sp3_c;
    }
    if (sp3_b != (s8) temporal_s0_2->desconocido8) {
        funcion_800CBBE8(((parametro2 & 0xFF) << 8) | 0x05020000, sp3_b);
        temporal_s0_2->desconocido8 = (u8) sp3_b;
    }
    if (sp34 != temporal_s0_2->desconocido4) {
        funcion_800CBB88(((parametro2 & 0xFF) << 8) | 0x04020000, sp34);
        temporal_s0_2->desconocido4 = sp34;
    }
    if (sp33 != (s8) temporal_s0_2->desconocido9) {
        funcion_800CBBE8(((parametro2 & 0xFF) << 8) | 0x03020000, sp33);
        temporal_s0_2->desconocido9 = (u8) sp33;
    }
}

struct desconocido_8018EFD8* funcion_800C1C88(u8 parametro0, Vec3f posicion, f32* velocidad, f32* parametro3, u8 parametro4, u32 sonido_bits) {
    struct desconocido_8018EFD8* temporal_a1;
    SIN_USO struct desconocido_8018EFD8* temporal_v1;
    SIN_USO u8 temporal_t7;
    u8 por_que_1;

    if (dato_8018EFD8[dato_8018FB90].next != 0xFF) {
        por_que_1 = dato_8018FB90;
        dato_8018EFD8[por_que_1].prev = dato_8018FB91;
        temporal_a1 = &dato_8018EFD8[dato_8018FB90];
        dato_8018EFD8[dato_8018FB91].next = por_que_1;
        temporal_t7 = temporal_a1->next;
        dato_8018FB91 = por_que_1;
        dato_8018FB90 = dato_8018EFD8[dato_8018FB90].next;
        dato_8018EFD8[dato_8018FB90].prev = 0xFF;
        dato_8018EFD8[por_que_1].pos_x = &posicion[0];
        dato_8018EFD8[por_que_1].pos_y = &posicion[1];
        dato_8018EFD8[por_que_1].pos_z = &posicion[2];
        dato_8018EFD8[por_que_1].next = 0xFF;
        dato_8018EFD8[por_que_1].vel_x = &velocidad[0];
        dato_8018EFD8[por_que_1].vel_y = &velocidad[1];
        dato_8018EFD8[por_que_1].vel_z = &velocidad[2];
        dato_8018EFD8[por_que_1].unk18[1] = 0.0f;
        dato_8018EFD8[por_que_1].unk24 = parametro3;
        dato_8018EFD8[por_que_1].id_camara = parametro4;
        dato_8018EFD8[por_que_1].desconocido30 = parametro0;
        dato_8018EFD8[por_que_1].sonido_bits = sonido_bits;
        return &dato_8018EFD8[por_que_1];
    }
    return NULL;
}

void funcion_800C1DA4(Camara* parametro0, Vec3s rot, struct desconocido_8018EFD8* parametro2) {
    f32 x;
    f32 y;

    x = parametro0->pos[0] - *parametro2->pos_x;
    y = parametro0->pos[2] - *parametro2->pos_z;
    parametro2->unk18[0] = funcion_800416D8(x, y, rot[1]);
    parametro2->unk18[2] = funcion_80041724(x, y, rot[1]);
}

void funcion_800C1E2C(Camara* camara, Vec3f velocidad, struct desconocido_8018EFD8* parametro2) {
    f32 sp44;
    f32 temporal_f6;
    f32 x;
    f32 y;
    f32 dist0;
    f32 dist1;
    f32 cosa0;
    f32 cosa1;
    f32 temporal_f2;

    x = (*parametro2->pos_x) - camara->pos[0];
    y = (*parametro2->pos_z) - camara->pos[2];

    sp44 = (*parametro2->vel_x) - velocidad[0];
    temporal_f6 = (*parametro2->vel_z) - velocidad[2];

    cosa0 = x + sp44;
    cosa1 = y + temporal_f6;

    dist0 = sqrtf((x * x) + (y * y));
    dist1 = sqrtf((cosa0 * cosa0) + (cosa1 * cosa1));

    temporal_f2 = 1.0f / (1.0f - ((dist0 - dist1) / parametro2->unk34));

    if (temporal_f2 > 0.1f) {
        parametro2->desconocido_2c = temporal_f2;
    } else {
        parametro2->desconocido_2c = 0.1f;
    }

    if ((*parametro2->unk24) != 0.0f) {
        parametro2->desconocido_2c *= (((*parametro2->unk24) / dato_800EA06C[parametro2->desconocido30].unk00[1]) + dato_800EA06C[parametro2->desconocido30].unk00[0]) +
                       dato_800E9F34[parametro2->desconocido30];
    }
}

void funcion_800C1F8C(void) {
    u8 variable_s1;
    u8 variable_a1;
    u8 id_camara;
    Camara** camara;

    variable_a1 = dato_800EA1C0 + 1;
    for (variable_s1 = 0; variable_s1 < variable_a1; variable_s1++) {
        camara_velocidad[variable_s1][0] = camara_copia[variable_s1]->pos[0] - pos_ultimo_camara[variable_s1][0];
        camara_velocidad[variable_s1][2] = camara_copia[variable_s1]->pos[2] - pos_ultimo_camara[variable_s1][2];
        pos_ultimo_camara[variable_s1][0] = camara_copia[variable_s1]->pos[0];
        pos_ultimo_camara[variable_s1][2] = camara_copia[variable_s1]->pos[2];
    }

    variable_a1 = 0;
    variable_s1 = dato_8018EFD8[0].next;
    while (variable_s1 != 0xFF) {
        if (dato_8018EFD8[variable_s1].unk18[1] == 100000.0f) {
            if (dato_8018FB91 == variable_s1) {
                dato_8018FB91 = dato_8018EFD8[variable_s1].prev;
            } else {
                dato_8018EFD8[dato_8018EFD8[variable_s1].next].prev = dato_8018EFD8[variable_s1].prev;
            }
            dato_8018EFD8[dato_8018EFD8[variable_s1].prev].next = dato_8018EFD8[variable_s1].next;
            dato_8018EFD8[variable_s1].prev = 0xFF;
            dato_8018EFD8[variable_s1].next = dato_8018FB90;
            dato_8018EFD8[dato_8018FB90].prev = variable_s1;
            dato_8018FB90 = variable_s1;
        } else {
            id_camara = dato_8018EFD8[variable_s1].id_camara;
            camara = &camara_copia[id_camara];
            funcion_800C1DA4(*camara, (*camara)->rot, &dato_8018EFD8[variable_s1]);
            if (dato_800EA1C8 != dato_8018EFD8[variable_s1].vel_x) {
                funcion_800C1E2C(*camara, camara_velocidad[0], &dato_8018EFD8[variable_s1]);
            }
            variable_a1 = variable_s1;
        }
        variable_s1 = dato_8018EFD8[variable_a1].next;
        if ((variable_s1 != 0xFF) && (dato_800EA244 < variable_s1)) {
            dato_800EA244 = variable_s1;
        }
    }
}

Vec3f* funcion_800C21E8(Vec3f pos, u32 sonido_bits) {
    u8 it;
    Vec3f* devuelto;
    SIN_USO f32* cosa = pos;
    struct desconocido_8018EFD8* temporal_a1;

    devuelto = 0;
    it = dato_8018EFD8[0].next;
    while (it != 0xFF) {
        temporal_a1 = &dato_8018EFD8[it];
        it = dato_8018EFD8[0].next;
        if ((pos == temporal_a1->pos_x) && (sonido_bits == temporal_a1->sonido_bits)) {
            it = 0xFF;
            if (temporal_a1->unk18[1] != 100000.0f) {
                devuelto = &temporal_a1->unk18;
            } else {
                goto probar;
            }
        } else {
        probar:
            it = temporal_a1->next;
        }
    }
    return devuelto;
}

void funcion_800C2274(u8 jugador) {
    s16 sp46;
    s16 variable_s1;
    s16 sp42;
    u8 variable_s0;
    u8 temporal_s0;
    u8 por_que = 0xFF;
    s32 variable_a2;

    variable_a2 = 0xF;
    if (jugadores_secuencia[jugador].activado != 0) {
        switch (seleccion_modo_pantalla) { /* irregular */
            case 0:
                break;
            case 1:
                variable_a2 = 0xE;
                break;
            case 3:
                if (seleccion_cantidad_jugador_1 == 3) {
                    variable_a2 = 0xD;
                } else {
                    variable_a2 = 0xC;
                }
                break;
        }
        temporal_s0 = jugadores_secuencia[jugador].channels[variable_a2]->sonido_io_guion[0];
        if (temporal_s0 != por_que) {
            sp46 = jugadores_secuencia[jugador].channels[variable_a2]->sonido_io_guion[1] % 4u;
            variable_s1 = jugadores_secuencia[jugador].channels[variable_a2]->sonido_io_guion[2] % 16u;
            if (variable_s1 >= 0xA) {
                variable_s1 = 9;
            }
            sp42 = jugadores_secuencia[jugador].channels[variable_a2]->sonido_io_guion[3] % 8u;
            funcion_800CBBE8(((jugador & 0xFF) << 0x10) | 0x06000000 | ((variable_a2 & 0xFF) << 8), -1);
        }
        switch (temporal_s0) {
            case 1:
                dato_8018FC10[sp46][0] = variable_s1;
                dato_8018FC10[sp46][1] = sp42;
                for (variable_s0 = 0; variable_s0 < 4; variable_s0++) {
                    if (dato_8018FC10[variable_s0][0] != por_que) {
                        funcion_8001AAAC(variable_s0, dato_8018FC10[variable_s0][0], dato_8018FC10[variable_s0][1]);
                        dato_8018FC10[variable_s0][0] = por_que;
                    }
                }
                break;
            case 2:
                dato_8018FC10[sp46][0] = variable_s1;
                dato_8018FC10[sp46][1] = sp42;
                break;
        }
    }
}

void funcion_800C2474(void) {
    u8 variable_v0;

    dato_8018EF10 = 0;
    camara_copia[0] = camara1;
    camara_copia[1] = camara2;
    camara_copia[2] = camara3;
    camara_copia[3] = camara4;
    dato_8018FB91 = 0;
    dato_8018FB90 = 1;
    dato_800EA0F4 = 0;
    dato_8018FC08 = 0;
    dato_800EA104 = 0;
    dato_800EA108 = 0;
    dato_800EA0F0 = 0;
    dato_800EA16C = 0;
    funcion_800CBBB8(0xF2000000U, 0);
    dato_800EA16C = 0;
    dato_800EA15C = 0;
    dato_800EA160 = 0;
    dato_800EA164 = 0;
    dato_800EA178 = 1.0f;
    dato_800EA17C = 0.85f;
    dato_800EA180 = 0;
    dato_800EA184 = 0;
    for (variable_v0 = 0; variable_v0 < 4; variable_v0++) {
        dato_800E9DB4[variable_v0] = 0;
        dato_800E9DF4[variable_v0] = 0;
        camara_velocidad[variable_v0][0] = 0.0f;
        camara_velocidad[variable_v0][1] = 0.0f;
        camara_velocidad[variable_v0][2] = 0.0f;
        pos_ultimo_camara[variable_v0][0] = 0.0f;
        pos_ultimo_camara[variable_v0][1] = 0.0f;
        pos_ultimo_camara[variable_v0][2] = 0.0f;
        dato_800EA0EC[variable_v0] = 0;
        dato_800E9EA4[variable_v0] = 0;
        dato_800E9F7C[variable_v0].desconocido_14 = 0;
        dato_800E9E74[variable_v0] = 0;
        dato_800E9E84[variable_v0] = 0;
        dato_800E9E94[variable_v0] = 0;
        jugadores[variable_v0].ruedas[RUEDA_IZQUIERDA_AUDIO].tipo_superficie = 0;
        jugadores[variable_v0].ruedas[RUEDA_DERECHA_AUDIO].tipo_superficie = 0;
        jugadores[variable_v0].efectos = 0;
        jugadores[variable_v0].desconocido_20C = 0.0f;
        jugadores[variable_v0].desconocido_0C0 = 0;
        jugadores[variable_v0].desconocido_098 = 0.0f;
        jugadores[variable_v0].oob_props = 0;
        dato_8018FC10[variable_v0][0] = 0x00FF;
        dato_8018FC10[variable_v0][1] = 0;
        dato_800EA10C[variable_v0] = 0;
        dato_800E9F74[variable_v0] = 0;
        dato_800E9F78[variable_v0] = 0;
    }
    for (variable_v0 = 0; variable_v0 < JUGADORES_NUM; variable_v0++) {
        dato_800E9F24[variable_v0] = 0;
        dato_800E9F2C[variable_v0] = 0;
        dato_800E9F34[variable_v0] = 0.0f;
        dato_800E9F54[variable_v0] = 0.0f;
        dato_800EA130[variable_v0] = 0.0f;
        dato_800EA06C[variable_v0].desconocido_0c = 0;
        jugadores[variable_v0].efectos = 0;
    }
    for (variable_v0 = 0; variable_v0 < 16; variable_v0++) {
        dato_8018EF18[variable_v0].desconocido0 = 1.0f;
        dato_8018EF18[variable_v0].desconocido4 = 1.0f;
        dato_8018EF18[variable_v0].desconocido8 = 0;
        dato_8018EF18[variable_v0].desconocido9 = 0x40;
    }
    dato_8018EFD8[0].prev = 0xFF;
    dato_8018EFD8[0].next = 0xFF;
    for (variable_v0 = 1; variable_v0 < 49; variable_v0++) {
        dato_8018EFD8[variable_v0].prev = variable_v0 - 1;
        dato_8018EFD8[variable_v0].next = variable_v0 + 1;
    }
    dato_8018EFD8[variable_v0].prev = variable_v0 - 1;
    dato_8018EFD8[variable_v0].next = 0xFF;
}

void funcion_800C284C(u8 parametro0, u8 parametro1, u8 parametro2, u16 parametro3) {
    u8 variable_v1;
    SIN_USO s32 relleno;

    if ((dato_800EA1EC != 0) && (parametro0 != 2)) {
        return;
    }

    funcion_800CBBB8(0x82000000 | (((u32) parametro0 & 0xFF) << 0x10) | (((u32) parametro1 & 0xFF) << 8), parametro3);
    dato_801930D0[parametro0].desconocido_248 = parametro1 | (parametro2 << 8);
    if (dato_801930D0[parametro0].desconocido_000 != 1.0f) {
        funcion_800CBB88(0x41000000 | (((u32) parametro0 & 0xFF) << 0x10), dato_801930D0[parametro0].desconocido_000);
    }
    dato_801930D0[parametro0].desconocido_028 = 0;
    dato_801930D0[parametro0].desconocido_018 = 0;
    dato_801930D0[parametro0].desconocido_014 = 0;

    for (variable_v1 = 0; variable_v1 < 16; variable_v1++) {
        dato_801930D0[parametro0].desconocido_044[variable_v1].desconocido_00 = 1.0f;
        dato_801930D0[parametro0].desconocido_044[variable_v1].desconocido_0C = 0;
        dato_801930D0[parametro0].desconocido_044[variable_v1].desconocido_10 = 1.0f;
        dato_801930D0[parametro0].desconocido_044[variable_v1].desconocido_1C = 0;
    }

    dato_801930D0[parametro0].desconocido_244 = 0;
    dato_801930D0[parametro0].desconocido_246 = 0;
}

void funcion_800C29B4(u8 parametro0, u16 parametro1) {
    funcion_800CBBB8(((parametro0 & 0xFF) << 0x10) | 0x83000000, parametro1);
    dato_801930D0[parametro0].desconocido_248 = 0xFFFF;
}

void funcion_800C2A2C(u32 cmd) {
    f32 objetivo_escala_frec;
    u16 desactivar_mascara_canal;
    u16 val;
    u16 fundir_temporizador;
    u8 prioridad;
    u8 puerto_io;
    u8 i;
    u8 duracion;
    u8 indice_canal;
    u8 encontrado;
    u8 sec_id;
    u8 parametros_sub;
    u8 op;
    u8 sec_indice_jugador;

    op = cmd >> 28;
    sec_indice_jugador = (cmd & 0xF000000) >> 24;

    switch (op) {
        case 0:
            sec_id = cmd & 0xFF;
            parametros_sub = (cmd & 0xFF00) >> 8;
            fundir_temporizador = (cmd & 0xFF0000) >> 13;
            funcion_800C284C(sec_indice_jugador, sec_id, parametros_sub, fundir_temporizador);
            break;

        case 1:
            fundir_temporizador = (cmd & 0xFF0000) >> 13;
            funcion_800C29B4(sec_indice_jugador, fundir_temporizador);
            break;

        case 2:
            sec_id = cmd & 0xFF;
            parametros_sub = (cmd & 0xFF00) >> 8;
            fundir_temporizador = (cmd & 0xFF0000) >> 13;
            prioridad = parametros_sub;

            for (i = 0; i < dato_80192CC6[sec_indice_jugador]; i++) {
                if (dato_80192CA8[sec_indice_jugador][i].cosa0 == sec_id) {
                    if (i == 0) {
                        funcion_800C284C(sec_indice_jugador, sec_id, parametros_sub, fundir_temporizador);
                    }
                    return;
                }
            }

            encontrado = dato_80192CC6[sec_indice_jugador];
            for (i = 0; i < dato_80192CC6[sec_indice_jugador]; i++) {
                if (prioridad >= dato_80192CA8[sec_indice_jugador][i].cosa1) {
                    encontrado = i;
                    i = dato_80192CC6[sec_indice_jugador];
                }
            }

            if ((encontrado != dato_80192CC6[sec_indice_jugador]) || (encontrado == 0)) {
                if (dato_80192CC6[sec_indice_jugador] < 5) {
                    dato_80192CC6[sec_indice_jugador]++;
                }
                for (i = dato_80192CC6[sec_indice_jugador] - 1; i != encontrado; i--) {
                    dato_80192CA8[sec_indice_jugador][i].cosa1 = dato_80192CA8[sec_indice_jugador][i - 1].cosa1;
                    dato_80192CA8[sec_indice_jugador][i].cosa0 = dato_80192CA8[sec_indice_jugador][i - 1].cosa0;
                }

                dato_80192CA8[sec_indice_jugador][encontrado].cosa1 = parametros_sub;
                dato_80192CA8[sec_indice_jugador][encontrado].cosa0 = sec_id;
            }
            if (encontrado == 0) {
                funcion_800C284C(sec_indice_jugador, sec_id, parametros_sub, fundir_temporizador);
            }
            break;

        case 3:
            fundir_temporizador = (cmd & 0xFF0000) >> 13;

            encontrado = dato_80192CC6[sec_indice_jugador];
            for (i = 0; i < dato_80192CC6[sec_indice_jugador]; i++) {
                sec_id = cmd & 0xFF;
                if (dato_80192CA8[sec_indice_jugador][i].cosa0 == sec_id) {
                    encontrado = i;
                    i = dato_80192CC6[sec_indice_jugador];
                }
            }

            if (encontrado != dato_80192CC6[sec_indice_jugador]) {
                for (i = encontrado; i < (dato_80192CC6[sec_indice_jugador] - 1); i++) {
                    dato_80192CA8[sec_indice_jugador][i].cosa1 = dato_80192CA8[sec_indice_jugador][i + 1].cosa1;
                    dato_80192CA8[sec_indice_jugador][i].cosa0 = dato_80192CA8[sec_indice_jugador][i + 1].cosa0;
                }

                dato_80192CC6[sec_indice_jugador]--;
            }
            if (encontrado == 0) {
                funcion_800C29B4(sec_indice_jugador, fundir_temporizador);
                if (dato_80192CC6[sec_indice_jugador] != 0) {
                    funcion_800C284C(sec_indice_jugador, dato_80192CA8[sec_indice_jugador][0].cosa0,
                                  dato_80192CA8[sec_indice_jugador][0].cosa1, fundir_temporizador);
                }
            }
            break;

        case 4:
            duracion = (cmd & 0xFF0000) >> 15;
            val = cmd & 0xFF;

            if (duracion == 0) {
                duracion++;
            }

            dato_801930D0[sec_indice_jugador].desconocido_004 = val / 127.0f;
            if (dato_801930D0[sec_indice_jugador].desconocido_000 != dato_801930D0[sec_indice_jugador].desconocido_004) {
                dato_801930D0[sec_indice_jugador].desconocido_008 =
                    (dato_801930D0[sec_indice_jugador].desconocido_000 - dato_801930D0[sec_indice_jugador].desconocido_004) / duracion;
                dato_801930D0[sec_indice_jugador].desconocido_00C = duracion;
            }
            break;

        case 5:
            duracion = (cmd & 0xFF0000) >> 15;
            val = cmd & 0xFFFF;

            if (duracion == 0) {
                duracion++;
            }
            objetivo_escala_frec = (f32) val / 1000.0f;
            for (i = 0; i < 0x10; i++) {
                dato_801930D0[sec_indice_jugador].desconocido_044[i].desconocido_14 = objetivo_escala_frec;
                dato_801930D0[sec_indice_jugador].desconocido_044[i].desconocido_1C = duracion;
                dato_801930D0[sec_indice_jugador].desconocido_044[i].desconocido_18 =
                    (dato_801930D0[sec_indice_jugador].desconocido_044[i].desconocido_10 - objetivo_escala_frec) / duracion;
            }

            dato_801930D0[sec_indice_jugador].desconocido_244 = 0xFFFF;
            break;

        case 6:
            duracion = (cmd & 0xFF0000) >> 15;
            indice_canal = (cmd & 0xF00) >> 8;
            val = cmd & 0xFF;

            if (duracion == 0) {
                duracion++;
            }

            dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_04 = val / 127.0f;
            if (dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_00 !=
                dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_04) {
                dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_08 =
                    (dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_00 -
                     dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_04) /
                    duracion;
                dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_0C = duracion;
                dato_801930D0[sec_indice_jugador].desconocido_244 |= 1 << indice_canal;
            }
            break;

        case 7:
            puerto_io = (cmd & 0xFF0000) >> 16;
            val = cmd & 0xFF;
            funcion_800CBBE8((0x46000000 | ((sec_indice_jugador & 0xFF) << 0x10)) | ((puerto_io & 0xFF) << 8), val);
            break;

        case 8:
            indice_canal = (cmd & 0xF00) >> 8;
            puerto_io = (cmd & 0xFF0000) >> 16;
            val = cmd & 0xFF;
            if (!(dato_801930D0[sec_indice_jugador].desconocido_24A & (1 << indice_canal))) {
                funcion_800CBBE8(((0x06000000 | ((sec_indice_jugador & 0xFF) << 0x10)) | (((u32) indice_canal & 0xFF) << 8)) |
                                  (puerto_io & 0xFF),
                              val);
            }
            break;

        case 9:
            dato_801930D0[sec_indice_jugador].desconocido_24A = cmd & 0xFFFF;
            break;

        case 10:
            val = 1;
            desactivar_mascara_canal = cmd & 0xFFFF;
            for (i = 0; i < 0x10; i++) {
                funcion_800CBBE8(0x08000000 | ((sec_indice_jugador & 0xFF) << 0x10) | (((u32) i & 0xFF) << 8),
                              (desactivar_mascara_canal & val) ? 1 : 0);
                val <<= 1;
            }

            break;

        case 11:
            dato_801930D0[sec_indice_jugador].desconocido_014 = cmd;
            break;

        case 12:
            parametros_sub = (cmd & 0xF00000) >> 20;
            if (parametros_sub != 0xF) {
                encontrado = dato_801930D0[sec_indice_jugador].desconocido_041++;
                if (encontrado < 5) {
                    dato_801930D0[sec_indice_jugador].desconocido_02C[encontrado] = cmd;
                    dato_801930D0[sec_indice_jugador].desconocido_040 = 2;
                }
            } else {
                dato_801930D0[sec_indice_jugador].desconocido_041 = 0;
            }
            break;

        case 14:
            parametros_sub = (cmd & 0xF00) >> 8;
            val = cmd & 0xFF;
            switch (parametros_sub) {
                case 0:
                    funcion_800CBBB8(0xF0000000, dato_800EA1F0[val]);
                    break;

                case 1:
                    dato_800EA1EC = val & 1;
                    break;
            }

            break;

        case 15:
            sec_id = cmd & 0xFF;
            parametros_sub = (cmd & 0xFF00) >> 8;
            dato_800EA1C0 = parametros_sub;
            reiniciar_eu_sesion_audio((void*) sec_id);
            dato_800EA1F4[0] = sec_id;
            funcion_800CBBE8(0x46020000, parametros_sub);
            funcion_800C5C40();
            break;

        default:
            break;
    }
}

void funcion_800C3448(u32 parametro0) {
    dato_80192CD0[dato_800EA1E4] = parametro0;
    dato_800EA1E4 += 1;
}

void funcion_800C3478(void) {
    for (dato_800EA1E8; dato_800EA1E4 != dato_800EA1E8;) {
        funcion_800C2A2C(dato_80192CD0[dato_800EA1E8++]);
    }
}

u16 funcion_800C3508(u8 jugador) {
    if (!jugadores_secuencia[jugador].activado) {
        return -1;
    }
    return dato_801930D0[jugador].desconocido_248;
}
