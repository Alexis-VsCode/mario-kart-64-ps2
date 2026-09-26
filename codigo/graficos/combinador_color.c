#include <string.h>

#include <ultra64.h>
#include <PR/gbi.h>

#include "graficos/combinador_color.h"

void combinador_decodificar(Combinador *cc, u32 combinar0, u32 combinar1, u32 om_h)
{
    u32 w0 = combinar0, w1 = combinar1;

    cc->rgb_a[0] = (w0 >> 20) & 0xF;
    cc->rgb_c[0] = (w0 >> 15) & 0x1F;
    cc->a_a[0] = (w0 >> 12) & 0x7;
    cc->a_c[0] = (w0 >> 9) & 0x7;
    cc->rgb_a[1] = (w0 >> 5) & 0xF;
    cc->rgb_c[1] = w0 & 0x1F;
    cc->rgb_b[0] = (w1 >> 28) & 0xF;
    cc->rgb_b[1] = (w1 >> 24) & 0xF;
    cc->a_a[1] = (w1 >> 21) & 0x7;
    cc->a_c[1] = (w1 >> 18) & 0x7;
    cc->rgb_d[0] = (w1 >> 15) & 0x7;
    cc->a_b[0] = (w1 >> 12) & 0x7;
    cc->a_d[0] = (w1 >> 9) & 0x7;
    cc->rgb_d[1] = (w1 >> 6) & 0x7;
    cc->a_b[1] = (w1 >> 3) & 0x7;
    cc->a_d[1] = w1 & 0x7;
    cc->dos_ciclo = ((om_h >> G_MDSFT_CYCLETYPE) & 3) == 1;
}

/* Entrada de color (componente c */
static Simbolo entrada_cc_rgb(const ColoresCombinador *col, int sel, int cual, int c, const u8 *v, Simbolo comb, Simbolo comb_alpha)
{
    Simbolo s = { 0.0f, 0.0f };

    if (cual == 2) {
        switch (sel) {
            case 0: return comb;
            case 1: case 2: s.m = 1.0f; return s;
            case 3: s.a = col->prim[c] / 255.0f; return s;
            case 4: s.a = v[c] / 255.0f; return s;
            case 5: s.a = col->amb[c] / 255.0f; return s;
            case 6: s.a = 1.0f; return s;               /* SCALE: sin uso en MK64 */
            case 7: return comb_alpha;
            case 8: case 9: s.a = 1.0f; return s;
            case 10: s.a = col->prim[3] / 255.0f; return s;
            case 11: s.a = v[3] / 255.0f; return s;
            case 12: s.a = col->amb[3] / 255.0f; return s;
            case 13: s.a = 1.0f; return s;
            case 14: s.a = col->prim_lod_frac / 255.0f; return s;
            default: return s;
        }
    }
    switch (sel) {
        case 0: return comb;
        case 1: case 2: s.m = 1.0f; return s;
        case 3: s.a = col->prim[c] / 255.0f; return s;
        case 4: s.a = v[c] / 255.0f; return s;
        case 5: s.a = col->amb[c] / 255.0f; return s;
        case 6: if (cual != 1) s.a = 1.0f; return s;
        case 7: return s;
        default: return s;
    }
}

static Simbolo entrada_alpha_cc(const ColoresCombinador *col, int sel, int cual, const u8 *v, Simbolo comb)
{
    Simbolo s = { 0.0f, 0.0f };

    if (cual == 2) {
        switch (sel) {
            case 0: s.a = 1.0f; return s;
            case 1: case 2: s.m = 1.0f; return s;
            case 3: s.a = col->prim[3] / 255.0f; return s;
            case 4: s.a = v[3] / 255.0f; return s;
            case 5: s.a = col->amb[3] / 255.0f; return s;
            case 6: s.a = col->prim_lod_frac / 255.0f; return s;
            default: return s;
        }
    }
    switch (sel) {
        case 0: return comb;
        case 1: case 2: s.m = 1.0f; return s;
        case 3: s.a = col->prim[3] / 255.0f; return s;
        case 4: s.a = v[3] / 255.0f; return s;
        case 5: s.a = col->amb[3] / 255.0f; return s;
        case 6: s.a = 1.0f; return s;
        default: return s;
    }
}

static Simbolo eval_cc(Simbolo A, Simbolo B, Simbolo C, Simbolo D)
{
    Simbolo x, r;

    x.m = A.m - B.m;
    x.a = A.a - B.a;
    r.m = x.m * C.a + x.a * C.m + x.m * C.m + D.m;
    r.a = x.a * C.a + D.a;
    return r;
}

void combinador_combinar(const Combinador *cc, const ColoresCombinador *col, const u8 v[4], Simbolo salida[4])
{
    int c, cyc;
    int leer_contador_ciclos = cc->dos_ciclo ? 2 : 1;
    Simbolo comb[4] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };

    for (cyc = 0; cyc < leer_contador_ciclos; cyc++) {
        Simbolo siguiente[4];

        for (c = 0; c < 3; c++) {
            siguiente[c] = eval_cc(entrada_cc_rgb(col, cc->rgb_a[cyc], 0, c, v, comb[c], comb[3]),
                              entrada_cc_rgb(col, cc->rgb_b[cyc], 1, c, v, comb[c], comb[3]),
                              entrada_cc_rgb(col, cc->rgb_c[cyc], 2, c, v, comb[c], comb[3]),
                              entrada_cc_rgb(col, cc->rgb_d[cyc], 3, c, v, comb[c], comb[3]));
        }
        siguiente[3] = eval_cc(entrada_alpha_cc(col, cc->a_a[cyc], 0, v, comb[3]), entrada_alpha_cc(col, cc->a_b[cyc], 1, v, comb[3]),
                          entrada_alpha_cc(col, cc->a_c[cyc], 2, v, comb[3]), entrada_alpha_cc(col, cc->a_d[cyc], 3, v, comb[3]));
        memcpy(comb, siguiente, sizeof(comb));
    }
    memcpy(salida, comb, sizeof(comb));
}

int combinador_texel_afecta_rgb(const Combinador *cc, const ColoresCombinador *col)
{
    static const u8 probes[2][4] = { { 0, 0, 0, 0 }, { 255, 255, 255, 255 } };
    int i, c;

    for (i = 0; i < 2; i++) {
        Simbolo s[4];

        combinador_combinar(cc, col, probes[i], s);
        for (c = 0; c < 3; c++) {
            if (s[c].m > 0.002f || s[c].m < -0.002f) {
                return 1;
            }
        }
    }
    return 0;
}

/* Alfa de un ciclo */
static int cc_lecturas_texel_alpha_ciclo(const Combinador *cc, int cyc, int ant)
{
    int sel[4] = { cc->a_a[cyc], cc->a_b[cyc], cc->a_c[cyc], cc->a_d[cyc] };
    int i;

    for (i = 0; i < 4; i++) {
        if (sel[i] == 1 || sel[i] == 2) {
            return 1;
        }
        if (cyc == 1 && ant && sel[i] == 0 && i != 2) {
            return 1;
        }
    }
    return 0;
}

/* Selectores que leen el texel */
static int rgb_sel_texel(int sel, int es_c)
{
    return sel == 1 || sel == 2 || (es_c && (sel == 8 || sel == 9));
}

int combinador_lee_rgb_texel(const Combinador *cc)
{
    int cyc, usa = 0, ant_rgb = 0, ant_a = 0;

    for (cyc = 0; cyc < (cc->dos_ciclo ? 2 : 1); cyc++) {
        int rgb = rgb_sel_texel(cc->rgb_a[cyc], 0) || rgb_sel_texel(cc->rgb_b[cyc], 0) ||
                  rgb_sel_texel(cc->rgb_c[cyc], 1) || rgb_sel_texel(cc->rgb_d[cyc], 0);

        if (cyc == 1) {
            rgb |= ant_rgb && (cc->rgb_a[1] == 0 || cc->rgb_b[1] == 0 || cc->rgb_c[1] == 0 || cc->rgb_d[1] == 0);
            rgb |= ant_a && cc->rgb_c[1] == 7;
        }
        ant_rgb = rgb;
        ant_a = cc_lecturas_texel_alpha_ciclo(cc, cyc, ant_a);
        usa |= rgb;
    }
    return usa;
}

int combinador_lee_alfa_texel(const Combinador *cc)
{
    int cyc, a = 0;

    for (cyc = 0; cyc < (cc->dos_ciclo ? 2 : 1); cyc++) {
        a = cc_lecturas_texel_alpha_ciclo(cc, cyc, a);
    }
    return a;
}
