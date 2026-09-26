#include <math.h>
#include <stdio.h>

#include <ultra64.h>
#include <PR/gbi.h>

#include "graficos/combinador_color.h"

static int s_fails, s_checks;

#define COMPROBACION(cond, ...)                                                                                               \
    do {                                                                                                               \
        s_checks++;                                                                                                     \
        if (!(cond)) {                                                                                                 \
            s_fails++;                                                                                                  \
            printf("FALLO %s:%d: ", __FILE__, __LINE__);                                                               \
            printf(__VA_ARGS__);                                                                                       \
            printf("\n");                                                                                              \
        }                                                                                                              \
    } while (0)

static int cerca(float a, float b)
{
    return fabsf(a - b) < 0.01f;
}

static void decodificar(Combinador *cc, Gfx g, int dos_ciclo)
{
    combinador_decodificar(cc, g.words.w0 & 0x00FFFFFF, g.words.w1, dos_ciclo ? G_CYC_2CYCLE : G_CYC_1CYCLE);
}

int main(void)
{
    Combinador cc;
    ColoresCombinador col = { { 0, 0, 0, 255 }, { 0, 0, 0, 255 }, 0 };
    const u8 blanco[4] = { 255, 255, 255, 255 };
    Simbolo s[4];

    {
        Gfx g = gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0);
        const u8 mitad[4] = { 128, 64, 255, 255 };

        decodificar(&cc, g, 0);
        combinador_combinar(&cc, &col, mitad, s);
        COMPROBACION(cerca(s[0].m, 128 / 255.0f) && cerca(s[0].a, 0), "modulate R m=%f a=%f", s[0].m, s[0].a);
        COMPROBACION(cerca(s[1].m, 64 / 255.0f), "modulate G m=%f", s[1].m);
        COMPROBACION(combinador_lee_rgb_texel(&cc) && combinador_lee_alfa_texel(&cc), "modulate lee el texel");
    }

    {
        Gfx g = gsDPSetCombineLERP(1, ENVIRONMENT, TEXEL0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 1, ENVIRONMENT, TEXEL0,
                                   PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0);
        ColoresCombinador mario = { { 0xC8, 0x01, 0x00, 0xD8 }, { 0xDC, 0x00, 0x00, 0xFF }, 0 };

        decodificar(&cc, g, 0);
        combinador_combinar(&cc, &mario, blanco, s);
        COMPROBACION(cerca(s[0].m, 1 - 0xDC / 255.0f) && cerca(s[0].a, 0xC8 / 255.0f), "globo R m=%f a=%f", s[0].m, s[0].a);
        COMPROBACION(cerca(s[1].m, 1) && cerca(s[1].a, 1 / 255.0f), "globo G m=%f a=%f", s[1].m, s[1].a);
        COMPROBACION(cerca(s[2].m, 1) && cerca(s[2].a, 0), "globo B m=%f a=%f", s[2].m, s[2].a);
        COMPROBACION(s[0].a > 0.5f, "globo: termino aditivo del rojo presente");
        COMPROBACION(combinador_texel_afecta_rgb(&cc, &mario), "globo: el texel influye en el RGB");
        COMPROBACION(cerca(s[3].m, 0xD8 / 255.0f), "globo alfa m=%f", s[3].m);
    }

    {
        Gfx g = gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

        decodificar(&cc, g, 1);
        COMPROBACION(cc.dos_ciclo, "niebla: 2 ciclos");
        COMPROBACION(combinador_lee_alfa_texel(&cc), "niebla: el alfa lee el texel a traves de COMBINED");
        COMPROBACION(combinador_lee_rgb_texel(&cc), "niebla: el RGB lee el texel");
        combinador_combinar(&cc, &col, blanco, s);
        COMPROBACION(cerca(s[0].m, 1) && cerca(s[3].m, 1), "niebla m rgb=%f alfa=%f", s[0].m, s[3].m);
    }

    {
        Gfx g = gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
        ColoresCombinador rojo = { { 255, 0, 0, 255 }, { 0, 0, 0, 0 }, 0 };

        decodificar(&cc, g, 1);
        COMPROBACION(!combinador_texel_afecta_rgb(&cc, &rojo), "plano: el RGB no depende del texel");
        COMPROBACION(combinador_lee_alfa_texel(&cc), "plano: el alfa si (2 ciclos)");
    }

    /* 5. Sin textura: SHADE en 1 ciclo. */
    {
        Gfx g = gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE);

        decodificar(&cc, g, 0);
        COMPROBACION(!combinador_lee_rgb_texel(&cc) && !combinador_lee_alfa_texel(&cc), "shade: no lee el texel");
    }

    /* 6. COMBINED_ALPHA en el C del segundo ciclo. */
    {
        Gfx g = gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, COMBINED, 0, COMBINED_ALPHA, 0, 0, 0, 0,
                                   COMBINED);
        ColoresCombinador p = { { 200, 100, 50, 255 }, { 0, 0, 0, 0 }, 0 };

        decodificar(&cc, g, 1);
        combinador_combinar(&cc, &p, blanco, s);
        COMPROBACION(cerca(s[0].m, 200 / 255.0f) && cerca(s[0].a, 0), "combined_alpha R m=%f a=%f", s[0].m, s[0].a);
        COMPROBACION(combinador_lee_rgb_texel(&cc), "combined_alpha: el RGB depende del texel via el alfa");
    }

    printf("%d comprobaciones, %d fallos\n", s_checks, s_fails);
    return s_fails != 0;
}
