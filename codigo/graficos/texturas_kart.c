#include <ultra64.h>
#include <juego/macros.h>
#include "sistema/bucle_principal.h"
#include "memoria/buffers.h"
#include <juego/estructuras_comunes.h>
#include "graficos/texturas_kart.h"
#include "juego/definiciones.h"
#include <juego/decodificacion.h>

#ifdef TARGET_PS2
extern s32 estado_juego;
extern s32 seleccion_modo;
extern s16 id_circuito_actual;

#define CANTIDAD_ENC_KART (sizeof(textura_kart_codificado[0]) / sizeof(textura_kart_codificado[0][0][0]) * 2)
#define RANURAS_DEC_KART 32

static struct {
    uintptr_t rom;
    u32 size;
    u32 version; /* cambia con cada copia real */
} kart_enc[CANTIDAD_ENC_KART];
static struct {
    s32 enc;     /* buffer comprimido del que salio (-1: nada conocido) */
    u32 version;
    uintptr_t rom;
    u32 size;
} dec_kart[RANURAS_DEC_KART];
static u32 kart_version;
static s32 clave_memo_kart = -1;

/* Paletas (lista_paletas_jugador) */
#define CANTIDAD_PAL_KART (sizeof(lista_paletas_jugador) / 512)
#define KART_PAL_DMA 128
static u32 kart_pal_version[CANTIDAD_PAL_KART];
static struct {
    const void* dest;
    uintptr_t rom;
    u32 size;
} kart_pal_dma[KART_PAL_DMA];

static int memo_kart_ps2_en(void) {
    s32 clave = (estado_juego == CARRERA && seleccion_modo != CONTRARRELOJ) ? id_circuito_actual : -1;

    if (clave != clave_memo_kart) {
        s32 i;

        clave_memo_kart = clave;
        for (i = 0; i < (s32) CANTIDAD_ENC_KART; i++) {
            kart_enc[i].size = 0;
        }
        for (i = 0; i < RANURAS_DEC_KART; i++) {
            dec_kart[i].enc = -1;
        }
        for (i = 0; i < KART_PAL_DMA; i++) {
            kart_pal_dma[i].dest = NULL;
        }
        for (i = 0; i < (s32) CANTIDAD_PAL_KART; i++) {
            kart_pal_version[i] = ++kart_version;
        }
    }
    return clave >= 0;
}

static s32 ps2_kart_enc_indice(const void* p) {
    uintptr_t apagado = (uintptr_t) p - (uintptr_t) textura_kart_codificado;

    if ((uintptr_t) p < (uintptr_t) textura_kart_codificado || apagado % sizeof(struct_d_802DFB80) != 0 ||
        apagado / sizeof(struct_d_802DFB80) >= CANTIDAD_ENC_KART) {
        return -1;
    }
    return (s32) (apagado / sizeof(struct_d_802DFB80));
}

static s32 ps2_kart_dma(OSIoMesg* mb, s32 prio, s32 dir, uintptr_t rom, void* dest, size_t size, OSMesgQueue* mq) {
    s32 i = ps2_kart_enc_indice(dest);
    uintptr_t poff = (uintptr_t) dest - (uintptr_t) lista_paletas_jugador;

    if ((uintptr_t) dest >= (uintptr_t) lista_paletas_jugador && poff < sizeof(lista_paletas_jugador)) {
        u32 ranura = (u32) (((uintptr_t) dest >> 3) * 0x9E3779B1u) >> 25;
        int on = memo_kart_ps2_en();

        if (on && kart_pal_dma[ranura].dest == dest && kart_pal_dma[ranura].rom == rom && kart_pal_dma[ranura].size == size) {
            osSendMesg(mq, (OSMesg) mb, OS_MESG_NOBLOCK);
            return 0;
        }
        kart_pal_dma[ranura].dest = on ? dest : NULL;
        kart_pal_dma[ranura].rom = rom;
        kart_pal_dma[ranura].size = size;
        /* Todas las paletas que toca pasan a otra version. */
        {
            u32 p;

            for (p = poff / 512; p <= (poff + size - 1) / 512 && p < CANTIDAD_PAL_KART; p++) {
                kart_pal_version[p] = ++kart_version;
            }
        }
        return osPiStartDma(mb, prio, dir, rom, dest, size, mq);
    }

    if (i >= 0 && memo_kart_ps2_en()) {
        if (kart_enc[i].rom == rom && kart_enc[i].size == size) {
            osSendMesg(mq, (OSMesg) mb, OS_MESG_NOBLOCK);
            return 0;
        }
        kart_enc[i].rom = rom;
        kart_enc[i].size = size;
        kart_enc[i].version = ++kart_version;
    } else if (i >= 0) {
        kart_enc[i].size = 0;
    }
    return osPiStartDma(mb, prio, dir, rom, dest, size, mq);
}

void ps2_kart_mio0decode(u8* orig_, u8* dst) {
    s32 e = ps2_kart_enc_indice(orig_);
    uintptr_t apagado = (uintptr_t) dst - (uintptr_t) &dato_802BFB80;
    s32 d = (dst >= (u8*) &dato_802BFB80 && apagado % 0x1000 == 0 && apagado / 0x1000 < RANURAS_DEC_KART) ? (s32) (apagado / 0x1000)
                                                                                             : -1;

    if (e >= 0 && d >= 0 && memo_kart_ps2_en() && kart_enc[e].size != 0) {
        if (dec_kart[d].enc == e && dec_kart[d].version == kart_enc[e].version) {
            return; /* ya tiene exactamente esta imagen */
        }
        dec_kart[d].enc = -1; /* mientras se escribe */
        mio0decode(orig_, dst);
        dec_kart[d].enc = e;
        dec_kart[d].version = kart_enc[e].version;
        dec_kart[d].rom = kart_enc[e].rom;
        dec_kart[d].size = kart_enc[e].size;
        return;
    }
    if (d >= 0) {
        dec_kart[d].enc = -1;
    }
    mio0decode(orig_, dst);
}

/* Para la cache de texturas (memoria_texturas.c) */
int ps2_kart_sprite_clave(const void* p, u32 largo, u32* clave) {
    uintptr_t apagado = (uintptr_t) p - (uintptr_t) &dato_802BFB80;
    s32 d;

    if ((uintptr_t) p < (uintptr_t) &dato_802BFB80 || apagado >= RANURAS_DEC_KART * 0x1000u || clave_memo_kart < 0) {
        return 0;
    }
    d = (s32) (apagado / 0x1000);
    if (dec_kart[d].enc < 0 || (apagado % 0x1000) + largo > 0x1000) {
        return 0;
    }
    *clave = (u32) dec_kart[d].rom * 0x9E3779B1u ^ dec_kart[d].size * 0x85EBCA6Bu ^ (u32) (apagado % 0x1000) * 0xC2B2AE35u;
    return 1;
}

/* Paleta de kart */
int ps2_kart_paleta_clave(const void* p, u32 largo, u32* clave) {
    uintptr_t apagado = (uintptr_t) p - (uintptr_t) lista_paletas_jugador;

    if ((uintptr_t) p < (uintptr_t) lista_paletas_jugador || apagado + largo > sizeof(lista_paletas_jugador) || largo == 0 ||
        apagado / 512 != (apagado + largo - 1) / 512 || clave_memo_kart < 0) {
        return 0;
    }
    *clave = kart_pal_version[apagado / 512] * 0x9E3779B1u ^ (u32) apagado * 0x85EBCA6Bu ^ largo;
    return 1;
}

#define osPiStartDma ps2_kart_dma
#endif

u16 dato_800DDEB0[] = {
    0x06c0, 0x06e0, 0x06e0, 0x0680, 0x07c0, 0x0700, 0x0680, 0x0910,
};

#define GRUPO_KART_DECLARAR(variable_) \
    u8* variable_##_grupo_0[] = { \
        variable_##_000, variable_##_001, variable_##_002, variable_##_003, variable_##_004, variable_##_005, variable_##_006, \
        variable_##_007, variable_##_008, variable_##_009, variable_##_010, variable_##_011, variable_##_012, variable_##_013, \
        variable_##_014, variable_##_015, variable_##_016, variable_##_017, variable_##_018, variable_##_019, variable_##_020, \
        variable_##_195, variable_##_196, variable_##_197, variable_##_198, variable_##_199, variable_##_200, variable_##_201, \
        variable_##_202, variable_##_203, variable_##_204, variable_##_205, variable_##_206, variable_##_207, variable_##_208, \
    }; \
    u8* variable_##_grupo_1[] = { \
        variable_##_021, variable_##_022, variable_##_023, variable_##_024, variable_##_025, variable_##_026, variable_##_027, \
        variable_##_028, variable_##_029, variable_##_030, variable_##_031, variable_##_032, variable_##_033, variable_##_034, \
        variable_##_035, variable_##_036, variable_##_037, variable_##_038, variable_##_039, variable_##_040, variable_##_041, \
        variable_##_195, variable_##_196, variable_##_197, variable_##_198, variable_##_199, variable_##_200, variable_##_201, \
        variable_##_202, variable_##_203, variable_##_204, variable_##_205, variable_##_206, variable_##_207, variable_##_208, \
    }; \
    u8* variable_##_grupo_2[] = { \
        variable_##_042, variable_##_043, variable_##_044, variable_##_045, variable_##_046, variable_##_047, variable_##_048, \
        variable_##_049, variable_##_050, variable_##_051, variable_##_052, variable_##_053, variable_##_054, variable_##_055, \
        variable_##_056, variable_##_057, variable_##_058, variable_##_059, variable_##_060, variable_##_061, variable_##_062, \
        variable_##_215, variable_##_216, variable_##_217, variable_##_218, variable_##_219, variable_##_220, variable_##_221, \
        variable_##_222, variable_##_223, variable_##_224, variable_##_225, variable_##_226, variable_##_227, variable_##_228, \
    }; \
    u8* variable_##_grupo_3[] = { \
        variable_##_063, variable_##_064, variable_##_065, variable_##_066, variable_##_067, variable_##_068, variable_##_069, \
        variable_##_070, variable_##_071, variable_##_072, variable_##_073, variable_##_074, variable_##_075, variable_##_076, \
        variable_##_077, variable_##_078, variable_##_079, variable_##_080, variable_##_081, variable_##_082, variable_##_083, \
        variable_##_235, variable_##_236, variable_##_237, variable_##_238, variable_##_239, variable_##_240, variable_##_241, \
        variable_##_242, variable_##_243, variable_##_244, variable_##_245, variable_##_246, variable_##_247, variable_##_248, \
    }; \
    u8* variable_##_grupo_4[] = { \
        variable_##_084, variable_##_085, variable_##_086, variable_##_087, variable_##_088, variable_##_089, variable_##_090, \
        variable_##_091, variable_##_092, variable_##_093, variable_##_094, variable_##_095, variable_##_096, variable_##_097, \
        variable_##_098, variable_##_099, variable_##_100, variable_##_101, variable_##_102, variable_##_103, variable_##_104, \
        variable_##_235, variable_##_236, variable_##_237, variable_##_238, variable_##_239, variable_##_240, variable_##_241, \
        variable_##_242, variable_##_243, variable_##_244, variable_##_245, variable_##_246, variable_##_247, variable_##_248, \
    }; \
    u8* variable_##_grupo_5[] = { \
        variable_##_105, variable_##_106, variable_##_107, variable_##_108, variable_##_109, variable_##_110, variable_##_111, \
        variable_##_112, variable_##_113, variable_##_114, variable_##_115, variable_##_116, variable_##_117, variable_##_118, \
        variable_##_119, variable_##_120, variable_##_121, variable_##_122, variable_##_123, variable_##_124, variable_##_125, \
        variable_##_235, variable_##_236, variable_##_237, variable_##_238, variable_##_239, variable_##_240, variable_##_241, \
        variable_##_242, variable_##_243, variable_##_244, variable_##_245, variable_##_246, variable_##_247, variable_##_248, \
    }; \
    u8* variable_##_grupo_6[] = { \
        variable_##_126, variable_##_127, variable_##_128, variable_##_129, variable_##_130, variable_##_131, variable_##_132, \
        variable_##_133, variable_##_134, variable_##_135, variable_##_136, variable_##_137, variable_##_138, variable_##_139, \
        variable_##_140, variable_##_141, variable_##_142, variable_##_143, variable_##_144, variable_##_145, variable_##_146, \
        variable_##_255, variable_##_256, variable_##_257, variable_##_258, variable_##_259, variable_##_260, variable_##_261, \
        variable_##_262, variable_##_263, variable_##_264, variable_##_265, variable_##_266, variable_##_267, variable_##_268, \
    }; \
    u8* variable_##_grupo_7[] = { \
        variable_##_147, variable_##_148, variable_##_149, variable_##_150, variable_##_151, variable_##_152, variable_##_153, \
        variable_##_154, variable_##_155, variable_##_156, variable_##_157, variable_##_158, variable_##_159, variable_##_160, \
        variable_##_161, variable_##_162, variable_##_163, variable_##_164, variable_##_165, variable_##_166, variable_##_167, \
        variable_##_275, variable_##_276, variable_##_277, variable_##_278, variable_##_279, variable_##_280, variable_##_281, \
        variable_##_282, variable_##_283, variable_##_284, variable_##_285, variable_##_286, variable_##_287, variable_##_288, \
    }; \
    u8* variable_##_grupo_8[] = { \
        variable_##_168, variable_##_169, variable_##_170, variable_##_171, variable_##_172, variable_##_173, variable_##_174, \
        variable_##_175, variable_##_176, variable_##_177, variable_##_178, variable_##_179, variable_##_180, variable_##_181, \
        variable_##_182, variable_##_183, variable_##_184, variable_##_185, variable_##_186, variable_##_187, variable_##_188, \
        variable_##_275, variable_##_276, variable_##_277, variable_##_278, variable_##_279, variable_##_280, variable_##_281, \
        variable_##_282, variable_##_283, variable_##_284, variable_##_285, variable_##_286, variable_##_287, variable_##_288, \
    }; \
    u8* variable_##_grupo_9[] = { \
        variable_##_189, variable_##_190, variable_##_191, variable_##_192, variable_##_193, variable_##_194, variable_##_195, \
        variable_##_196, variable_##_197, variable_##_198, variable_##_199, variable_##_200, variable_##_201, variable_##_202, \
        variable_##_203, variable_##_204, variable_##_205, variable_##_206, variable_##_207, variable_##_208, \
    }; \
    u8* variable_##_grupo_10[] = { \
        variable_##_189, variable_##_190, variable_##_191, variable_##_192, variable_##_193, variable_##_194, variable_##_195, \
        variable_##_196, variable_##_197, variable_##_198, variable_##_199, variable_##_200, variable_##_201, variable_##_202, \
        variable_##_203, variable_##_204, variable_##_205, variable_##_206, variable_##_207, variable_##_208, \
    }; \
    u8* variable_##_grupo_11[] = { \
        variable_##_209, variable_##_210, variable_##_211, variable_##_212, variable_##_213, variable_##_214, variable_##_215, \
        variable_##_216, variable_##_217, variable_##_218, variable_##_219, variable_##_220, variable_##_221, variable_##_222, \
        variable_##_223, variable_##_224, variable_##_225, variable_##_226, variable_##_227, variable_##_228, \
    }; \
    u8* variable_##_grupo_12[] = { \
        variable_##_229, variable_##_230, variable_##_231, variable_##_232, variable_##_233, variable_##_234, variable_##_235, \
        variable_##_236, variable_##_237, variable_##_238, variable_##_239, variable_##_240, variable_##_241, variable_##_242, \
        variable_##_243, variable_##_244, variable_##_245, variable_##_246, variable_##_247, variable_##_248, \
    }; \
    u8* variable_##_grupo_13[] = { \
        variable_##_229, variable_##_230, variable_##_231, variable_##_232, variable_##_233, variable_##_234, variable_##_235, \
        variable_##_236, variable_##_237, variable_##_238, variable_##_239, variable_##_240, variable_##_241, variable_##_242, \
        variable_##_243, variable_##_244, variable_##_245, variable_##_246, variable_##_247, variable_##_248, \
    }; \
    u8* variable_##_grupo_14[] = { \
        variable_##_229, variable_##_230, variable_##_231, variable_##_232, variable_##_233, variable_##_234, variable_##_235, \
        variable_##_236, variable_##_237, variable_##_238, variable_##_239, variable_##_240, variable_##_241, variable_##_242, \
        variable_##_243, variable_##_244, variable_##_245, variable_##_246, variable_##_247, variable_##_248, \
    }; \
    u8* variable_##_grupo_15[] = { \
        variable_##_249, variable_##_250, variable_##_251, variable_##_252, variable_##_253, variable_##_254, variable_##_255, \
        variable_##_256, variable_##_257, variable_##_258, variable_##_259, variable_##_260, variable_##_261, variable_##_262, \
        variable_##_263, variable_##_264, variable_##_265, variable_##_266, variable_##_267, variable_##_268, \
    }; \
    u8* variable_##_grupo_16[] = { \
        variable_##_269, variable_##_270, variable_##_271, variable_##_272, variable_##_273, variable_##_274, variable_##_275, \
        variable_##_276, variable_##_277, variable_##_278, variable_##_279, variable_##_280, variable_##_281, variable_##_282, \
        variable_##_283, variable_##_284, variable_##_285, variable_##_286, variable_##_287, variable_##_288, \
    }; \
    u8* variable_##_grupo_17[] = { \
        variable_##_269, variable_##_270, variable_##_271, variable_##_272, variable_##_273, variable_##_274, variable_##_275, \
        variable_##_276, variable_##_277, variable_##_278, variable_##_279, variable_##_280, variable_##_281, variable_##_282, \
        variable_##_283, variable_##_284, variable_##_285, variable_##_286, variable_##_287, variable_##_288, \
    };

#define TABLE0_KART_DECLARAR(variable_) \
    u8** variable_##_tabla_0[] = { \
        variable_##_grupo_8, variable_##_grupo_7, variable_##_grupo_6, variable_##_grupo_5, variable_##_grupo_4, \
        variable_##_grupo_3, variable_##_grupo_2, variable_##_grupo_1, variable_##_grupo_0, \
    };

#define TABLE1_KART_DECLARAR(variable_) \
    u8** variable_##_tabla_1[] = { \
        variable_##_grupo_17, variable_##_grupo_16, variable_##_grupo_15, variable_##_grupo_14, variable_##_grupo_13, \
        variable_##_grupo_12, variable_##_grupo_11, variable_##_grupo_10, variable_##_grupo_9, \
    };

#define DECLARAR_KART_VUELCO_TABLA(variable_) \
    u8* variable_##_vuelco[] = { \
        variable_##_289, variable_##_290, variable_##_291, variable_##_292, variable_##_293, variable_##_294, variable_##_295, \
        variable_##_296, variable_##_297, variable_##_298, variable_##_299, variable_##_300, variable_##_301, variable_##_302, \
        variable_##_303, variable_##_304, variable_##_305, variable_##_306, variable_##_307, variable_##_308, variable_##_309, \
        variable_##_310, variable_##_311, variable_##_312, variable_##_313, variable_##_314, variable_##_315, variable_##_316, \
        variable_##_317, variable_##_318, variable_##_319, variable_##_320 \
    };

GRUPO_KART_DECLARAR(kart_mario)
GRUPO_KART_DECLARAR(kart_toad)
GRUPO_KART_DECLARAR(kart_luigi)
GRUPO_KART_DECLARAR(kart_yoshi)
GRUPO_KART_DECLARAR(kart_dk)
GRUPO_KART_DECLARAR(kart_bowser)
GRUPO_KART_DECLARAR(kart_peach)
GRUPO_KART_DECLARAR(kart_wario)

TABLE0_KART_DECLARAR(kart_mario)
TABLE0_KART_DECLARAR(kart_luigi)
TABLE0_KART_DECLARAR(kart_yoshi)
TABLE0_KART_DECLARAR(kart_toad)
TABLE0_KART_DECLARAR(kart_dk)
TABLE0_KART_DECLARAR(kart_wario)
TABLE0_KART_DECLARAR(kart_peach)
TABLE0_KART_DECLARAR(kart_bowser)

TABLE1_KART_DECLARAR(kart_mario)
TABLE1_KART_DECLARAR(kart_luigi)
TABLE1_KART_DECLARAR(kart_yoshi)
TABLE1_KART_DECLARAR(kart_toad)
TABLE1_KART_DECLARAR(kart_dk)
TABLE1_KART_DECLARAR(kart_wario)
TABLE1_KART_DECLARAR(kart_peach)
TABLE1_KART_DECLARAR(kart_bowser)

u8*** tabla_textura_kart_0[] = {
    kart_mario_tabla_0, kart_luigi_tabla_0, kart_yoshi_tabla_0, kart_toad_tabla_0,
    kart_dk_tabla_0,    kart_wario_tabla_0, kart_peach_tabla_0, kart_bowser_tabla_0,
};

u8*** tabla_textura_kart_1[] = {
    kart_mario_tabla_1, kart_luigi_tabla_1, kart_yoshi_tabla_1, kart_toad_tabla_1,
    kart_dk_tabla_1,    kart_wario_tabla_1, kart_peach_tabla_1, kart_bowser_tabla_1,
};

DECLARAR_KART_VUELCO_TABLA(kart_mario)
DECLARAR_KART_VUELCO_TABLA(kart_luigi)
DECLARAR_KART_VUELCO_TABLA(kart_bowser)
DECLARAR_KART_VUELCO_TABLA(kart_toad)
DECLARAR_KART_VUELCO_TABLA(kart_yoshi)
DECLARAR_KART_VUELCO_TABLA(kart_dk)
DECLARAR_KART_VUELCO_TABLA(kart_peach)
DECLARAR_KART_VUELCO_TABLA(kart_wario)

u8** tumbles_textura_kart[] = {
    kart_mario_vuelco, kart_luigi_vuelco, kart_yoshi_vuelco, kart_toad_vuelco,
    kart_dk_vuelco,    kart_wario_vuelco, kart_peach_vuelco, kart_bowser_vuelco,
};

u8* paletas_kart[] = {
    kart_mario_paleta, kart_luigi_paleta, kart_yoshi_paleta, kart_toad_paleta,
    kart_dk_paleta,    kart_wario_paleta, kart_peach_paleta, kart_bowser_paleta,
};

void cargar_textura_kart(Jugador* jugador, s8 id_jugador, s8 id_pantalla, s8 id_pantalla_2, s8 index) {
    s32 temporal_ = jugador->efectos;
    if (((temporal_ & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
        ((temporal_ & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO) ||
        ((temporal_ & desconocido_efecto_0_x_80000) == desconocido_efecto_0_x_80000) ||
        ((temporal_ & desconocido_efecto_0_x_800000) == desconocido_efecto_0_x_800000) ||
        ((temporal_ & EFECTO_GOLPE_RAYO) == EFECTO_GOLPE_RAYO) || ((jugador->kart_props & sin_uso_0_x_800) != 0)) {
        if (jugador->anim_frame_selector[id_pantalla] != 0) {
            osInvalDCache(&textura_kart_codificado[index][id_pantalla_2][id_jugador], dato_800DDEB0[jugador->id_personaje]);

            osPiStartDma(&msj_io_dma, OS_MESG_PRI_NORMAL, OS_READ,
                         (uintptr_t) &_kart_texturesSegmentRomStart[SEGMENT_OFFSET(
                             tabla_textura_kart_1[jugador->id_personaje][jugador->anim_selector_grupo[id_pantalla]]
                                               [jugador->anim_frame_selector[id_pantalla]])],
                         &textura_kart_codificado[index][id_pantalla_2][id_jugador], dato_800DDEB0[jugador->id_personaje],
                         &cola_msj_dma);

            osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
        } else {
            osInvalDCache(&textura_kart_codificado[index][id_pantalla_2][id_jugador], dato_800DDEB0[jugador->id_personaje]);

            osPiStartDma(&msj_io_dma, OS_MESG_PRI_NORMAL, OS_READ,
                         (uintptr_t) &_kart_texturesSegmentRomStart[SEGMENT_OFFSET(
                             tabla_textura_kart_0[jugador->id_personaje][jugador->anim_selector_grupo[id_pantalla]]
                                               [jugador->anim_frame_selector[id_pantalla]])],
                         &textura_kart_codificado[index][id_pantalla_2][id_jugador], dato_800DDEB0[jugador->id_personaje],
                         &cola_msj_dma);

            osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
        }
    } else if (((temporal_ & GOLPE_POR_CAPARAZON_VERDE_EFECTO) == GOLPE_POR_CAPARAZON_VERDE_EFECTO) ||
               ((temporal_ & EFECTO_ERROR_EXPLOSION) == EFECTO_ERROR_EXPLOSION) ||
               ((temporal_ & GOLPE_POR_EFECTO_ESTRELLA) == GOLPE_POR_EFECTO_ESTRELLA) ||
               ((temporal_ & EFECTO_VUELCO_TERRENO) == EFECTO_VUELCO_TERRENO)) {
        osInvalDCache(&textura_kart_codificado[index][id_pantalla_2][id_jugador], 0x780U);
        osPiStartDma(&msj_io_dma, OS_MESG_PRI_NORMAL, OS_READ,
                     (uintptr_t) &_kart_texturesSegmentRomStart[SEGMENT_OFFSET(
                         tumbles_textura_kart[jugador->id_personaje][jugador->desconocido_0A8 >> 8])],
                     &textura_kart_codificado[index][id_pantalla_2][id_jugador], 0x900, &cola_msj_dma);

        osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
    } else {
        osInvalDCache(&textura_kart_codificado[index][id_pantalla_2][id_jugador], dato_800DDEB0[jugador->id_personaje]);

        osPiStartDma(&msj_io_dma, OS_MESG_PRI_NORMAL, OS_READ,
                     (uintptr_t) &_kart_texturesSegmentRomStart[SEGMENT_OFFSET(
                         tabla_textura_kart_0[jugador->id_personaje][jugador->anim_selector_grupo[id_pantalla]]
                                           [jugador->anim_frame_selector[id_pantalla]])],
                     &textura_kart_codificado[index][id_pantalla_2][id_jugador], dato_800DDEB0[jugador->id_personaje], &cola_msj_dma);

        osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
    }
}

void cargar_kart_textura_no_bloqueante(Jugador* jugador, s8 parametro1, s8 parametro2, s8 parametro3, s8 parametro4) {
    s32 temporal_ = jugador->efectos;

    if (((temporal_ & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
        ((temporal_ & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO) ||
        ((temporal_ & desconocido_efecto_0_x_80000) == desconocido_efecto_0_x_80000) ||
        ((temporal_ & desconocido_efecto_0_x_800000) == desconocido_efecto_0_x_800000) ||
        ((temporal_ & EFECTO_GOLPE_RAYO) == EFECTO_GOLPE_RAYO) || ((jugador->kart_props & sin_uso_0_x_800) != 0)) {
        if (jugador->anim_frame_selector[parametro2] != 0) {
            osInvalDCache(&textura_kart_codificado[parametro4][parametro3][parametro1], dato_800DDEB0[jugador->id_personaje]);

            osPiStartDma(&msj_io_dma, OS_MESG_PRI_NORMAL, OS_READ,
                         (uintptr_t) &_kart_texturesSegmentRomStart[SEGMENT_OFFSET(
                             tabla_textura_kart_1[jugador->id_personaje][jugador->anim_selector_grupo[parametro2]]
                                               [jugador->anim_frame_selector[parametro2]])],
                         &textura_kart_codificado[parametro4][parametro3][parametro1], dato_800DDEB0[jugador->id_personaje], &cola_msj_dma);
        } else {
            osInvalDCache(&textura_kart_codificado[parametro4][parametro3][parametro1], dato_800DDEB0[jugador->id_personaje]);

            osPiStartDma(&msj_io_dma, OS_MESG_PRI_NORMAL, OS_READ,
                         (uintptr_t) &_kart_texturesSegmentRomStart[SEGMENT_OFFSET(
                             tabla_textura_kart_0[jugador->id_personaje][jugador->anim_selector_grupo[parametro2]]
                                               [jugador->anim_frame_selector[parametro2]])],
                         &textura_kart_codificado[parametro4][parametro3][parametro1], dato_800DDEB0[jugador->id_personaje], &cola_msj_dma);
        }
    } else if (((temporal_ & GOLPE_POR_CAPARAZON_VERDE_EFECTO) == GOLPE_POR_CAPARAZON_VERDE_EFECTO) ||
               ((temporal_ & EFECTO_ERROR_EXPLOSION) == EFECTO_ERROR_EXPLOSION) ||
               ((temporal_ & GOLPE_POR_EFECTO_ESTRELLA) == GOLPE_POR_EFECTO_ESTRELLA) ||
               ((temporal_ & EFECTO_VUELCO_TERRENO) == EFECTO_VUELCO_TERRENO)) {
        osInvalDCache(&textura_kart_codificado[parametro4][parametro3][parametro1], 0x780);
        osPiStartDma(&msj_io_dma, OS_MESG_PRI_NORMAL, OS_READ,
                     (uintptr_t) &_kart_texturesSegmentRomStart[SEGMENT_OFFSET(
                         tumbles_textura_kart[jugador->id_personaje][jugador->desconocido_0A8 >> 8])],
                     &textura_kart_codificado[parametro4][parametro3][parametro1], 0x900, &cola_msj_dma);
    } else {
        osInvalDCache(&textura_kart_codificado[parametro4][parametro3][parametro1], dato_800DDEB0[jugador->id_personaje]);

        osPiStartDma(&msj_io_dma, OS_MESG_PRI_NORMAL, OS_READ,
                     (uintptr_t) &_kart_texturesSegmentRomStart[SEGMENT_OFFSET(
                         tabla_textura_kart_0[jugador->id_personaje][jugador->anim_selector_grupo[parametro2]]
                                           [jugador->anim_frame_selector[parametro2]])],
                     &textura_kart_codificado[parametro4][parametro3][parametro1], dato_800DDEB0[jugador->id_personaje], &cola_msj_dma);
    }
}

void cargar_paleta_kart(Jugador* jugador, s8 id_jugador, s8 id_pantalla, s8 index) {
#ifdef AVOID_UB
    struct_d_802F1F80* temporal_s0 = &lista_paletas_jugador[index][id_pantalla][id_jugador];
#else
    struct_d_802F1F80* temporal_s0 = (struct_d_802F1F80*) &lista_paletas_jugador[index][id_pantalla][id_jugador * 0x100];
#endif
    switch (modo_pantalla_activo) {
        case MODO_PANTALLA_1P:
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            osInvalDCache(temporal_s0, sizeof(struct_d_802F1F80));

            osPiStartDma(&msj_io_dma, OS_MESG_PRI_NORMAL, OS_READ,
                         (uintptr_t) &_kart_texturesSegmentRomStart[SEGMENT_OFFSET(paletas_kart[jugador->id_personaje])],
                         temporal_s0, sizeof(struct_d_802F1F80), &cola_msj_dma);

            osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
            break;
        case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
            osInvalDCache(temporal_s0, sizeof(struct_d_802F1F80));

            osPiStartDma(&msj_io_dma, OS_MESG_PRI_NORMAL, OS_READ,
                         (uintptr_t) &_kart_texturesSegmentRomStart[SEGMENT_OFFSET(paletas_kart[jugador->id_personaje])],
                         temporal_s0, sizeof(struct_d_802F1F80), &cola_msj_dma);

            osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
            break;
    }
}

void cargar_datos_jugador(SIN_USO Jugador* jugador, s32 parametro1, void* direccion_v, u16 size) {
    osInvalDCache(direccion_v, size);

    osPiStartDma(&msj_io_dma, OS_MESG_PRI_NORMAL, OS_READ,
                 (uintptr_t) &_kart_texturesSegmentRomStart[SEGMENT_OFFSET(parametro1)], direccion_v, size, &cola_msj_dma);

    osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
}

void cargar_jugador_datos_no_bloqueante(SIN_USO Jugador* jugador, s32 parametro1, void* direccion_v, u16 size) {
    osInvalDCache(direccion_v, size);

    osPiStartDma(&msj_io_dma, OS_MESG_PRI_NORMAL, OS_READ,
                 (uintptr_t) &_kart_texturesSegmentRomStart[SEGMENT_OFFSET(parametro1)], direccion_v, size, &cola_msj_dma);
}
