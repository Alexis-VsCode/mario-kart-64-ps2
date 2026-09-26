#ifndef CARRERA_PESOS_CAMINO_H
#define CARRERA_PESOS_CAMINO_H

typedef unsigned long long pw_u64;
typedef unsigned int pw_u32;

static inline int pw_msb64(pw_u64 x)
{
    int n = 0;

    if (x >> 32) { x >>= 32; n += 32; }
    if (x >> 16) { x >>= 16; n += 16; }
    if (x >> 8) { x >>= 8; n += 8; }
    if (x >> 4) { x >>= 4; n += 4; }
    if (x >> 2) { x >>= 2; n += 2; }
    if (x >> 1) { n += 1; }
    return n;
}

static inline pw_u64 pw_rne128(pw_u64 hi, pw_u64 lo, int s)
{
    pw_u64 q, resto, mitad;
    int above;

    if (s >= 64) {
        int t = s - 64;

        q = (t == 0) ? hi : (hi >> t);
        if (t == 0) {
            resto = lo;
            mitad = 1ULL << 63;
            above = resto > mitad;
            if (resto > mitad || (resto == mitad && (q & 1))) {
                q++;
            }
            (void) above;
            return q;
        }
        /* resto: (hi mod 2^t) : lo, mitad 2^(t-1) : 0 */
        resto = hi & ((1ULL << t) - 1);
        mitad = 1ULL << (t - 1);
        if (resto > mitad || (resto == mitad && (lo != 0 || (q & 1)))) {
            q++;
        }
        return q;
    }
    q = (lo >> s) | (hi << (64 - s));
    resto = lo & ((1ULL << s) - 1);
    mitad = 1ULL << (s - 1);
    if (resto > mitad || (resto == mitad && (q & 1))) {
        q++;
    }
    return q;
}

static inline int flotante_hacer_pw(pw_u64 m, int k, pw_u32 *salida)
{
    int e;

    if (m == (1ULL << 24)) {
        m >>= 1;
        k++;
    }
    /* m en [2^23, 2^24): valor en [2^(23+k), 2^(24+k)) */
    e = 23 + k + 127;
    if (e <= 0 || e >= 255) {
        return 0;
    }
    *salida = ((pw_u32) e << 23) | ((pw_u32) m & 0x7FFFFF);
    return 1;
}

static inline int pw_doble_then_flotante(pw_u64 hi, pw_u64 lo, int k, pw_u32 *salida)
{
    int msb = hi ? 64 + pw_msb64(hi) : pw_msb64(lo);
    pw_u64 d;
    int kd;

    if (msb > 52) {
        /* redondeo a double: se quitan msb - 52 bits */
        d = pw_rne128(hi, lo, msb - 52);
        kd = k + (msb - 52);
        if (d == (1ULL << 53)) {
            d >>= 1;
            kd++;
        }
    } else {
        d = lo; /* cabe en double: exacto */
        kd = k;
    }
    msb = pw_msb64(d);
    if (msb > 23) {
        pw_u64 f = pw_rne128(0, d, msb - 23);

        return flotante_hacer_pw(f, kd + (msb - 23), salida);
    }
    /* menos de 24 bits: exacto, se normaliza */
    return flotante_hacer_pw(d << (23 - msb), kd - (23 - msb), salida);
}

static inline int pesos_camino_ps2(pw_u32 jb, pw_u32 *w1, pw_u32 *w2, pw_u32 *w3)
{
    int e = (int) ((jb >> 23) & 0xFF) - 127;
    pw_u64 mj, a, cuad_hi, cuad_lo, a_l, a_h, cruce, t;
    int s;

    if ((jb >> 31) || e >= 0 || e < -17) {
        return 0;
    }
    mj = (jb & 0x7FFFFF) | 0x800000;
    s = 23 - e;
    a = (1ULL << s) - mj;

    {
        pw_u64 p = mj * mj;

        if (!pw_doble_then_flotante(0, p, -2 * s - 1, w3)) {
            return 0;
        }
    }
    a_l = a & 0xFFFFFFFFULL;
    a_h = a >> 32;
    cruce = 2 * ((pw_u64) (pw_u32) a_h * (pw_u32) a_l);
    cuad_lo = (pw_u64) (pw_u32) a_l * (pw_u32) a_l;
    t = cuad_lo + (cruce << 32);
    cuad_hi = (pw_u64) (pw_u32) a_h * (pw_u32) a_h + (cruce >> 32) + (t < cuad_lo);
    cuad_lo = t;
    if (!pw_doble_then_flotante(cuad_hi, cuad_lo, -2 * s - 1, w1)) {
        return 0;
    }
    {
        pw_u64 q = a * mj;
        int msb = pw_msb64(q);
        pw_u64 d;
        int kd = -2 * s, sh;
        pw_u64 r;

        if (msb > 52) {
            d = pw_rne128(0, q, msb - 52);
            kd += msb - 52;
        } else {
            d = q;
        }
        sh = -(kd + 53);
        if (sh > 0) {
            r = (sh >= 64) ? 0 : pw_rne128(0, d, sh);
        } else {
            r = d << (-sh);
        }
        r += 1ULL << 52;
        if (!pw_doble_then_flotante(0, r, -53, w2)) {
            return 0;
        }
    }
    return 1;
}

#endif
