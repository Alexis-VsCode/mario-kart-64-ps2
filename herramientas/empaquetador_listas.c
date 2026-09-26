#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "PR/gbi.h"

#define LONGITUD_CADENA_MAX 256
#define SALIDA_CADENA_MAX 10000

#define OML_AA_ZCMP_ZUPD_IMRD_ALPHA_CVG_SEL (AA_EN | Z_CMP | Z_UPD | IM_RD | ALPHA_CVG_SEL)
#define OML_AA_ZCMP_ZUPD_IMRD_CVG_X_ALPHA_ALPHA_CVG_SEL (AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_X_ALPHA | ALPHA_CVG_SEL)

#define PARAM_TEX_EN  0x0001
#define APAGADO_PARAM_TEX 0xFFFF

#define COMB_CC_MODULATERGBA        0xFFFF
#define COMB_CC_MODULATERGBDECALA   0xF3F9
#define SOMBREADO_CC_COMB               0x793C
#define COMB_CC_DECALRGBA           0xFFFD
#define ALT1_AJUSTE_COMB            0xF9FC

#define SEG_BASE_4 0x04000000ULL
#define SEG_BASE_5 0x05000000ULL

#define G_OP_D0 0xD0

void empaquetar(FILE *archivo_entrada, FILE *archivo_salida);

static int entrada_endian_little = 0;

int main(int argc, char *argv[]) {
    if (argc == 4 && strcmp(argv[1], "-le") == 0) {
        entrada_endian_little = 1;
        argv++;
        argc--;
    }
    if (argc != 3) {
        printf("Usage: ./dl_unpack [-le] input.bin output.bin\n");
        exit(1);
    }

    FILE *archivo_entrada = fopen(argv[1], "rb");
    if (archivo_entrada == NULL) {
        printf("Failed to open input file: %s\n", argv[1]);
        exit(1);
    }

    FILE *archivo_salida = fopen(argv[2], "wb");
    if (archivo_salida == NULL) {
        printf("Failed to create output file: %s\n", argv[2]);
        exit(1);
    }

    empaquetar(archivo_entrada, archivo_salida);
    return 0;
}

uint64_t intercambiar_endian(uint64_t value) {
    uint64_t result = 0;
    if (entrada_endian_little) {
        return (value << 32) | (value >> 32);
    }
    int i;
    for (i = 0; i < 8; i++) {
        result = (result << 8) | ((value >> (i * 8)) & 0xFF);
    }
    return result;
}

uint32_t comprimir_b1(uint8_t a, uint8_t b, uint8_t c) {
    return (a / 2) | ((b / 2) << 5) | ((c / 2) << 10);
}

#define ARG1(val) ((val) >> 48)
#define ARG1WORD(val) ((val) >> 32)
#define ARG2(val) ((val) >> 40)
#define ARG2WORD(val) ((val) >> 32)
#define OPCODE(val) (uint8_t)((val) >> 56)

enum op_empaquetado {
    /* Set combine presets (renommés en fonction des macros G_CC_*) */
    PG_SETCOMBINE_CC_MODULATERGBA      = 0x15,
    PG_SETCOMBINE_CC_MODULATERGBDECALA = 0x16,
    PG_SETCOMBINE_CC_SOMBREADO             = 0x17,

    PG_RMODE_OPA     = 0x18,
    PG_RMODE_TEXEDGE = 0x19,

    PG_TILECFG_A = 0x1A,
    PG_TILECFG_B = 0x1B,
    PG_TILECFG_C = 0x1C,
    PG_TILECFG_D = 0x1D,
    PG_TILECFG_E = 0x1E,
    PG_TILECFG_F = 0x1F,

    CARGAR_BLOQUE_TIMG_PG_0 = 0x20,
    CARGAR_BLOQUE_TIMG_PG_1 = 0x21,
    CARGAR_BLOQUE_TIMG_PG_2 = 0x22,
    CARGAR_BLOQUE_TIMG_PG_3 = 0x23,
    CARGAR_BLOQUE_TIMG_PG_4 = 0x24,
    CARGAR_BLOQUE_TIMG_PG_5 = 0x25,

    APAGADO_TEXTURA_PG = 0x26,
    TEXTURA_PG_EN  = 0x27,

    PG_VTX1  = 0x28,

    PG_TRI1  = 0x29,
    PG_ENDDL = 0x2A,
    PG_DL    = 0x2B,
    PG_TILECFG_G = 0x2C,
    PG_CULLDL = 0x2D,

    PG_SETCOMBINE_ALT = 0x2E,

    PG_RMODE_XLU = 0x2F,

    PG_SPLINE3D = 0x30,

    PG_VTX_BASE = 0x32,

    PG_SETCOMBINE_CC_DECALRGBA = 0x53,

    PG_RMODE_OPA_DECAL = 0x54,
    PG_RMODE_XLU_DECAL = 0x55,

    PG_SETGEOMETRYMODE   = 0x56,
    PG_CLEARGEOMETRYMODE = 0x57,

    /* Triangle pair */
    PG_TRI2 = 0x58,

    PG_D0_REMAP = 0xDD,

    DESCONOCIDO_PG = 0xEE,
    FIN_ARCHIVO_PG     = 0xFF,
};

void empaquetar(FILE *archivo_entrada, FILE *archivo_salida) {

    uint8_t p1;
    uint8_t p2;
    uint8_t p3;
    uint16_t p7;

    uint64_t cmd;
    uint8_t codigo_op;
    uint32_t desplazamiento = 0;
    uint32_t cantidad = 0;
    uint8_t datos[50000];
    int depuracion = getenv("DLPACKER_DEBUG") != NULL;
    int lb_bias = 0;
    while (fread(&cmd, sizeof(uint64_t), 1, archivo_entrada) == 1) {
        cmd = intercambiar_endian(cmd);
        codigo_op = OPCODE(cmd);
        switch (codigo_op) {
            case (uint8_t)G_SETOTHERMODE_L:
                p7 = (uint16_t) cmd;
                if (p7 == OML_AA_ZCMP_ZUPD_IMRD_ALPHA_CVG_SEL) {
                    datos[cantidad++] = PG_RMODE_OPA;
                    if (depuracion) fprintf(stderr, "@%u PG_RMODE_OPA\n", cantidad-1);
                } else if (p7 == OML_AA_ZCMP_ZUPD_IMRD_CVG_X_ALPHA_ALPHA_CVG_SEL) {
                    datos[cantidad++] = PG_RMODE_TEXEDGE;
                    if (depuracion) fprintf(stderr, "@%u PG_RMODE_TEXEDGE\n", cantidad-1);
                } else if ((p7 & ZMODE_XLU) == ZMODE_XLU) {
                    if ((p7 & ALPHA_CVG_SEL) == ALPHA_CVG_SEL) {
                        datos[cantidad++] = PG_RMODE_XLU_DECAL;
                        if (depuracion) fprintf(stderr, "@%u PG_RMODE_XLU_DECAL (ZMODE_XLU|ALPHA_CVG_SEL)\n", cantidad-1);
                    } else {
                        datos[cantidad++] = PG_RMODE_XLU;
                        if (depuracion) fprintf(stderr, "@%u PG_RMODE_XLU (ZMODE_XLU)\n", cantidad-1);
                    }
                } else if ((p7 & ALPHA_CVG_SEL) == ALPHA_CVG_SEL) {
                    datos[cantidad++] = PG_RMODE_OPA_DECAL;
                    if (depuracion) fprintf(stderr, "@%u PG_RMODE_OPA_DECAL (ALPHA_CVG_SEL)\n", cantidad-1);
                }
                break;
            case (uint8_t)G_TRI1:
                datos[cantidad++] = PG_TRI1;
                if (depuracion) fprintf(stderr, "@%u PG_TRI1\n", cantidad-1);
                p1 = (uint8_t) (cmd >> 16) / 2;
                p2 = (uint8_t) (cmd >> 8) / 2;
                p3 = (uint8_t) (cmd) / 2;

                *(uint16_t*) (datos + cantidad) = (uint16_t) (p1 | (p2 << 5) | (p3 << 10));
                cantidad++; cantidad++;
                break;
            case G_DL:
                datos[cantidad++] = PG_DL;
                if (depuracion) fprintf(stderr, "@%u PG_DL\n", cantidad-1);
                *(uint16_t*) (datos + cantidad) = (uint16_t)(((uint32_t)cmd) / 8);
                cantidad++; cantidad++;
                break;
            case (uint8_t)G_QUAD: {
                datos[cantidad++] = PG_SPLINE3D;
                if (depuracion) fprintf(stderr, "@%u PG_SPLINE3D\n", cantidad-1);
                uint32_t w1 = (uint32_t)cmd;
                uint8_t a0 = (uint8_t)(w1 >> 24) / 2;
                uint8_t t0 = (uint8_t)(w1 >> 16) / 2;
                uint8_t a3 = (uint8_t)(w1 >> 8)  / 2;
                uint8_t a2 = (uint8_t)(w1)       / 2;
                uint8_t P0 = ((a3 & 0x7) << 5) | (t0 & 0x1F);
                uint8_t P1 = ((a0 & 0x1) << 7) | ((a2 & 0x1F) << 2) | ((a3 >> 3) & 0x3);
                uint8_t P2 = (a0 >> 1) & 0x0F;
                datos[cantidad++] = P0;
                datos[cantidad++] = P1;
                datos[cantidad++] = P2;
                if (depuracion) fprintf(stderr, "    quad a0=%u t0=%u a3=%u a2=%u -> P0=%02X P1=%02X P2=%02X\n", a0, t0, a3, a2, P0, P1, P2);
                break;
            }
            case (uint8_t)G_TRI2:
                datos[cantidad++] = PG_TRI2;
                if (depuracion) fprintf(stderr, "@%u PG_TRI2\n", cantidad-1);
                *(uint16_t*) (datos + cantidad) = comprimir_b1(ARG1(cmd), ARG2(cmd), cmd >> 32);
                cantidad++; cantidad++;
                *(uint16_t*) (datos + cantidad) = comprimir_b1(cmd >> 16, cmd >> 8, cmd);
                cantidad++; cantidad++;
                break;
            case G_VTX:
                datos[cantidad++] = (uint8_t)(((((uint16_t)ARG1WORD(cmd)) + 1) / 0x410) + PG_VTX_BASE);
                if (depuracion) fprintf(stderr, "@%u PG_VTX_%u\n", cantidad-1, datos[cantidad-1]-PG_VTX_BASE);
                *(uint16_t*) (datos + cantidad) = (uint16_t)(((uint32_t)cmd - (uint32_t)SEG_BASE_4) / 16);
                cantidad++; cantidad++;
                break;
            case G_SETTIMG: {
                p1 = (uint32_t)(cmd - SEG_BASE_5) >> 11;
                p2 = 0x00;
                p3 = 0x70;

                {
                    uint64_t siguiente;
                    int encontrado = 0;
                    for (int i = 0; i < 12; i++) {
                        if (fread(&siguiente, sizeof(uint64_t), 1, archivo_entrada) != 1) {
                            printf("Error: Unexpected EOF scanning after G_SETTIMG\n");
                            break;
                        }
                        siguiente = intercambiar_endian(siguiente);
                        uint8_t nop = OPCODE(siguiente);
                        if (nop == (uint8_t)G_LOADBLOCK) {
                            cmd = siguiente;
                            encontrado = 1;
                            break;
                        }
                        if (nop == (uint8_t)G_SETTILE || nop == (uint8_t)G_RDPLOADSYNC || nop == (uint8_t)G_RDPPIPESYNC) {
                            continue;
                        }
                    }
                    if (!encontrado) {
                        printf("Error: Did not find G_LOADBLOCK after G_SETTIMG\n");
                        datos[cantidad++] = CARGAR_BLOQUE_TIMG_PG_0;
                        datos[cantidad++] = p1;
                        datos[cantidad++] = p2;
                        datos[cantidad++] = p3;
                        break;
                    }
                }

                {
                    uint32_t lb_w0 = (uint32_t)(cmd >> 32);
                    uint32_t lb_w1 = (uint32_t)(cmd);
                    uint16_t uls = (lb_w0 >> 12) & 0xFFF;
                    uint16_t ult = (lb_w0 >> 0) & 0xFFF;
                    uint8_t  tile = (lb_w1 >> 24) & 0x7;
                    uint16_t lrs = (lb_w1 >> 12) & 0xFFF;
                    uint16_t dxt = (lb_w1 >> 0) & 0xFFF;
                    int base = -1;
                    if (tile == G_TX_LOADTILE && uls == 0 && (ult == 0 || ult == 3)) {
                        if (lrs == 0x3FF && dxt == 0x0100) base = 0;
                        else if (lrs == 0x7FF && dxt == 0x0080) base = 1;
                        else if (lrs == 0x7FF && dxt == 0x0100) base = 2;
                    }
                    if (base < 0) {
                        printf("Error: Unrecognized/Unexpected G_LOADBLOCK (tile=%u uls=%u ult=%u lrs=%03X dxt=%03X)\n", tile, uls, ult, lrs, dxt);
                        base = 0;
                    }
                    uint8_t variante = (uint8_t)(CARGAR_BLOQUE_TIMG_PG_0 + base + lb_bias);
                    datos[cantidad++] = variante;
                    if (depuracion) fprintf(stderr, "@%u PG_TIMG_LOADBLOCK_%d (base=%d,bias=%d) cmd=%016llX\n", cantidad-1, (int)(variante-CARGAR_BLOQUE_TIMG_PG_0), base, lb_bias, (unsigned long long)cmd);
                }

                datos[cantidad++] = p1;
                datos[cantidad++] = p2;
                datos[cantidad++] = p3;
                break;
            }
            case G_RDPTILESYNC: {
                if (fread(&cmd, sizeof(uint64_t), 1, archivo_entrada) != 1) {
                    printf("Error: Unexpected EOF after G_RDPTILESYNC (SETTILE)\n");
                    break;
                }
                cmd = intercambiar_endian(cmd);
                if ((uint8_t)OPCODE(cmd) != (uint8_t)G_SETTILE) {
                    printf("Error: Expected G_SETTILE after G_RDPTILESYNC, got 0x%02X\n", OPCODE(cmd));
                    break;
                }

                uint32_t st_w0 = (uint32_t)(cmd >> 32);
                uint32_t st_w1 = (uint32_t)cmd;
                uint8_t fmt   = (st_w0 >> 21) & 0x7;
                uint8_t siz   = (st_w0 >> 19) & 0x3;
                uint16_t line = (st_w0 >> 9) & 0x1FF;
                uint16_t tmem = (st_w0 >> 0) & 0x1FF;
                uint8_t tile  = (st_w1 >> 24) & 0x7;
                uint8_t pal   = (st_w1 >> 20) & 0xF;
                uint8_t cmt   = (st_w1 >> 18) & 0x3;
                uint8_t maskt = (st_w1 >> 14) & 0xF;
                uint8_t shiftt= (st_w1 >> 10) & 0xF;
                uint8_t cms   = (st_w1 >> 8)  & 0x3;
                uint8_t mascaras = (st_w1 >> 4)  & 0xF;
                uint8_t shifts= (st_w1 >> 0)  & 0xF;

                p1 = (((cmd >> 14) & 0xF) << 4) | ((cmd >> 18) & 0xF);
                p2 = (((cmd >> 4) & 0xF) << 4) | ((cmd >> 8) & 0xF);

                {
                    int encontrado = 0;
                    for (int i = 0; i < 6; i++) {
                        if (fread(&cmd, sizeof(uint64_t), 1, archivo_entrada) != 1) {
                            printf("Error: Unexpected EOF after G_SETTILE (SETTILESIZE)\n");
                            break;
                        }
                        cmd = intercambiar_endian(cmd);
                        uint8_t op2 = OPCODE(cmd);
                        if (op2 == (uint8_t)G_SETTILESIZE) { encontrado = 1; break; }
                        if (op2 == (uint8_t)G_RDPLOADSYNC || op2 == (uint8_t)G_RDPPIPESYNC) {
                            continue;
                        }
                        break;
                    }
                    if (!encontrado) {
                        printf("Error: Expected G_SETTILESIZE after G_SETTILE, got 0x%02X\n", OPCODE(cmd));
                        break;
                    }
                }

                uint32_t ss_w0 = (uint32_t)(cmd >> 32);
                uint32_t ss_w1 = (uint32_t)cmd;
                uint16_t uls = (ss_w0 >> 12) & 0xFFF;
                uint16_t ult = (ss_w0 >> 0)  & 0xFFF;
                uint16_t lrs = (ss_w1 >> 12) & 0xFFF;
                uint16_t lrt = (ss_w1 >> 0)  & 0xFFF;

                if (fmt == G_IM_FMT_RGBA && lrs == 0x07C && lrt == 0x07C) {
                    uint8_t w0_b1 = (uint8_t)((st_w0 >> 8) & 0xFF);
                    if (depuracion) fprintf(stderr, "#TILE RGBA7C7C st_w0=%08X ss_w1=%08X p2=%02X p1=%02X w0_b1=%02X\n", st_w0, ss_w1, p2, p1, w0_b1);
                    if (w0_b1 == 0x11) {
                        datos[cantidad++] = PG_TILECFG_G;
                        if (depuracion) fprintf(stderr, "@%u PG_TILECFG_G p2=%02X p1=%02X\n", cantidad-1, p2, p1);
                    } else {
                        datos[cantidad++] = PG_TILECFG_A;
                        if (depuracion) fprintf(stderr, "@%u PG_TILECFG_A p2=%02X p1=%02X\n", cantidad-1, p2, p1);
                    }
                    lb_bias = 0;
                } else if (fmt == G_IM_FMT_RGBA && lrs == 0x0FC && lrt == 0x07C) {
                    datos[cantidad++] = PG_TILECFG_B;
                    if (depuracion) fprintf(stderr, "@%u PG_TILECFG_B p2=%02X p1=%02X\n", cantidad-1, p2, p1);
                    lb_bias = 0;
                } else if (fmt == G_IM_FMT_RGBA && lrs == 0x07C && lrt == 0x0FC) {
                    datos[cantidad++] = PG_TILECFG_C;
                    if (depuracion) fprintf(stderr, "@%u PG_TILECFG_C p2=%02X p1=%02X\n", cantidad-1, p2, p1);
                    lb_bias = 0;
                } else if (fmt == G_IM_FMT_IA && lrs == 0x07C && lrt == 0x07C) {
                    datos[cantidad++] = PG_TILECFG_D;
                    if (depuracion) fprintf(stderr, "@%u PG_TILECFG_D p2=%02X p1=%02X\n", cantidad-1, p2, p1);
                    lb_bias = 3;
                } else if (fmt == G_IM_FMT_IA && lrs == 0x0FC && lrt == 0x07C) {
                    datos[cantidad++] = PG_TILECFG_E;
                    if (depuracion) fprintf(stderr, "@%u PG_TILECFG_E p2=%02X p1=%02X\n", cantidad-1, p2, p1);
                    lb_bias = 3;
                } else if (fmt == G_IM_FMT_IA && lrs == 0x07C && lrt == 0x0FC) {
                    datos[cantidad++] = PG_TILECFG_F;
                    if (depuracion) fprintf(stderr, "@%u PG_TILECFG_F p2=%02X p1=%02X\n", cantidad-1, p2, p1);
                    lb_bias = 3;
                } else {
                    if (depuracion) fprintf(stderr, "@%u PG_TILECFG_A (default) fmt=%u siz=%u line=%u tmem=%u tile=%u pal=%u cmt=%u cms=%u uls=%03X ult=%03X lrs=%03X lrt=%03X maskt=%u masks=%u shiftt=%u shifts=%u\n",
                        cantidad, fmt, siz, line, tmem, tile, pal, cmt, cms, uls, ult, lrs, lrt, maskt, mascaras, shiftt, shifts);
                    datos[cantidad++] = PG_TILECFG_A; lb_bias = 0;
                }

                datos[cantidad++] = p2;
                datos[cantidad++] = p1;
                break;
            }
            case (uint8_t)G_TEXTURE: {
                uint16_t t = (uint16_t)cmd;
                if (t == 0x0001) {
                    datos[cantidad++] = TEXTURA_PG_EN;
                    if (depuracion) fprintf(stderr, "@%u PG_TEXTURE_ON (t==0001)\n", cantidad-1);
                    break;
                }
                if (t == 0xFFFF) {
                    datos[cantidad++] = APAGADO_TEXTURA_PG;
                    if (depuracion) fprintf(stderr, "@%u PG_TEXTURE_OFF (t==FFFF)\n", cantidad-1);
                    break;
                }
                uint32_t w0 = (uint32_t)(cmd >> 32);
                uint8_t on8 = (uint8_t)(w0 & 0xFF);
                uint8_t on7 = (uint8_t)((w0 >> 1) & 0x7F);
                datos[cantidad++] = ((on8 != 0) || (on7 != 0)) ? TEXTURA_PG_EN : APAGADO_TEXTURA_PG;
                if (depuracion) fprintf(stderr, "@%u PG_TEXTURE_%s (decoded) on8=%u on7=%u\n", cantidad-1, (((on8!=0)||(on7!=0))?"ON":"OFF"), on8, on7);
                break;
            }
            case (uint8_t)G_ENDDL:
                datos[cantidad++] = PG_ENDDL;
                if (depuracion) fprintf(stderr, "@%u PG_ENDDL\n", cantidad-1);
                break;
            case (uint8_t)G_RDPLOADSYNC:
            case (uint8_t)G_RDPPIPESYNC:
                break;
            case (uint8_t)G_LOADBLOCK:
                break;
            case (uint8_t)G_CULLDL:
                datos[cantidad++] = PG_CULLDL;
                if (depuracion) fprintf(stderr, "@%u PG_CULLDL\n", cantidad-1);
                break;
            case G_OP_D0:
                datos[cantidad++] = PG_D0_REMAP;
                if (depuracion) fprintf(stderr, "@%u PG_D0_REMAP\n", cantidad-1);
                break;
            case G_SETCOMBINE:
                p7 = (uint16_t)cmd;
                if (p7 == COMB_CC_MODULATERGBDECALA) {
                    datos[cantidad++] = PG_SETCOMBINE_CC_MODULATERGBDECALA;
                    if (depuracion) fprintf(stderr, "@%u PG_SETCOMBINE_PRESET_F3F9\n", cantidad-1);
                } else if (p7 == COMB_CC_MODULATERGBA) {
                    datos[cantidad++] = PG_SETCOMBINE_CC_MODULATERGBA;
                    if (depuracion) fprintf(stderr, "@%u PG_SETCOMBINE_PRESET_FFFF\n", cantidad-1);
                } else if (p7 == SOMBREADO_CC_COMB) {
                    datos[cantidad++] = PG_SETCOMBINE_CC_SOMBREADO;
                    if (depuracion) fprintf(stderr, "@%u PG_SETCOMBINE_PRESET_793C\n", cantidad-1);
                } else if (p7 == COMB_CC_DECALRGBA) {
                    datos[cantidad++] = PG_SETCOMBINE_CC_DECALRGBA;
                    if (depuracion) fprintf(stderr, "@%u PG_SETCOMBINE_DECALRGBA\n", cantidad-1);
                } else if (p7 == ALT1_AJUSTE_COMB) {
                    datos[cantidad++] = PG_SETCOMBINE_ALT;
                    if (depuracion) fprintf(stderr, "@%u PG_SETCOMBINE_ALT\n", cantidad-1);
                }
                break;
            case (uint8_t)G_SETGEOMETRYMODE:
                datos[cantidad++] = PG_SETGEOMETRYMODE;
                if (depuracion) fprintf(stderr, "@%u PG_SETGEOMETRYMODE\n", cantidad-1);
                break;
            case (uint8_t)G_CLEARGEOMETRYMODE:
                datos[cantidad++] = PG_CLEARGEOMETRYMODE;
                if (depuracion) fprintf(stderr, "@%u PG_CLEARGEOMETRYMODE\n", cantidad-1);
                break;
            default:
                printf("Error: Unknown Opcode: 0x%X\n", codigo_op);
                printf("Opcode written to file as 0xEE\n");
                datos[cantidad++] = DESCONOCIDO_PG;
                break;
        }

        desplazamiento += 4;
    }
    // eos
    datos[cantidad++] = FIN_ARCHIVO_PG;
    size_t escrito_elements_num = fwrite(datos, sizeof(uint8_t), cantidad, archivo_salida);
    if (escrito_elements_num != cantidad) {
        printf("Failed to write data to file.\n");
        exit(1);
    }

    fclose(archivo_entrada);
    fclose(archivo_salida);
}
