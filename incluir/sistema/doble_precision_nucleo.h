#ifndef SISTEMA_DOBLE_PRECISION_NUCLEO_H
#define SISTEMA_DOBLE_PRECISION_NUCLEO_H

typedef unsigned long long sd_u64;
typedef unsigned int sd_u32;

#define CARTEL_SD    0x8000000000000000ULL
#define SD_FRAC    0x000FFFFFFFFFFFFFULL
#define SD_HIDDEN  0x0010000000000000ULL
#define SD_EXP(x)  ((sd_u32) ((x) >> 52) & 0x7FF)

static inline sd_u64 grs_ronda_sd(sd_u64 m)
{
    sd_u32 grs = (sd_u32) m & 7;

    m >>= 3;
    if (grs > 4 || (grs == 4 && (m & 1))) {
        m++;
    }
    return m;
}

static inline int mul_sd(sd_u64 a, sd_u64 b, sd_u64 *r)
{
    sd_u32 ea = SD_EXP(a), eb = SD_EXP(b);
    sd_u64 sign = (a ^ b) & CARTEL_SD;
    sd_u64 ma, mb, a_l, a_h, b_l, b_h, ll, lh, hl, hh, medio, lo, hi, m, resto, mitad;
    int e;

    if (ea == 0 || ea == 0x7FF || eb == 0 || eb == 0x7FF) {
        return 0;
    }
    ma = (a & SD_FRAC) | SD_HIDDEN;
    mb = (b & SD_FRAC) | SD_HIDDEN;
    /* Producto exacto de 106 bits con multiplicaciones de 32x32. */
    a_l = ma & 0xFFFFFFFFULL;
    a_h = ma >> 32;
    b_l = mb & 0xFFFFFFFFULL;
    b_h = mb >> 32;
    ll = (sd_u64) (sd_u32) a_l * (sd_u32) b_l;
    lh = (sd_u64) (sd_u32) a_l * (sd_u32) b_h;
    hl = (sd_u64) (sd_u32) a_h * (sd_u32) b_l;
    hh = (sd_u64) (sd_u32) a_h * (sd_u32) b_h;
    medio = lh + hl; /* < 2^54: sin desborde */
    lo = ll + (medio << 32);
    hi = hh + (medio >> 32) + (lo < ll);
    e = (int) ea + (int) eb - 1023;
    /* El producto esta en [2^104, 2^106): hi tiene 41 o 42 bits. */
    if (hi & (1ULL << 41)) {
        m = (hi << 11) | (lo >> 53);
        resto = lo & ((1ULL << 53) - 1);
        mitad = 1ULL << 52;
        e++;
    } else {
        m = (hi << 12) | (lo >> 52);
        resto = lo & ((1ULL << 52) - 1);
        mitad = 1ULL << 51;
    }
    if (resto > mitad || (resto == mitad && (m & 1))) {
        m++;
        if (m == (SD_HIDDEN << 1)) {
            m >>= 1;
            e++;
        }
    }
    if (e <= 0 || e >= 0x7FF) {
        return 0; /* desnormal o infinito: libgcc */
    }
    *r = sign | ((sd_u64) e << 52) | (m & SD_FRAC);
    return 1;
}

/* a + b (para a - b, se cambia el signo de b) */
static inline int agregar_sd(sd_u64 a, sd_u64 b, sd_u64 *r)
{
    sd_u32 ea = SD_EXP(a), eb = SD_EXP(b);
    sd_u64 ma, mb, m, sign;
    int e;
    sd_u32 d;

    if (ea == 0x7FF || eb == 0x7FF) {
        return 0;
    }
    if (ea == 0 || eb == 0) {
        if (ea == 0 && (a << 1) == 0 && eb != 0) {
            *r = b;
            return 1;
        }
        if (eb == 0 && (b << 1) == 0 && ea != 0) {
            *r = a;
            return 1;
        }
        return 0;
    }
    if ((a << 1) < (b << 1)) {
        sd_u64 t = a;

        a = b;
        b = t;
        ea = SD_EXP(a);
        eb = SD_EXP(b);
    }
    sign = a & CARTEL_SD;
    ma = ((a & SD_FRAC) | SD_HIDDEN) << 3;
    mb = ((b & SD_FRAC) | SD_HIDDEN) << 3;
    d = ea - eb;
    if (d != 0) {
        if (d >= 60) {
            mb = 1; /* solo el bit pegajoso */
        } else {
            sd_u64 perdido = mb & ((1ULL << d) - 1);

            mb = (mb >> d) | (perdido != 0);
        }
    }
    e = (int) ea;
    if (((a ^ b) & CARTEL_SD) == 0) {
        m = ma + mb;
        if (m & (1ULL << 56)) {
            m = (m >> 1) | (m & 1);
            e++;
        }
    } else {
        m = ma - mb;
        if (m == 0) {
            *r = 0; /* x - x = +0 al redondear al mas cercano */
            return 1;
        }
        while (!(m & (1ULL << 55))) {
            m <<= 1;
            e--;
        }
    }
    m = grs_ronda_sd(m);
    if (m == (SD_HIDDEN << 1)) {
        m >>= 1;
        e++;
    }
    if (e <= 0 || e >= 0x7FF) {
        return 0;
    }
    *r = sign | ((sd_u64) e << 52) | (m & SD_FRAC);
    return 1;
}

static inline int sd_extend(sd_u32 f, sd_u64 *r)
{
    sd_u32 e = (f >> 23) & 0xFF;
    sd_u64 sign = (sd_u64) (f >> 31) << 63;

    if (e == 0) {
        if ((f << 1) == 0) {
            *r = sign;
            return 1;
        }
        return 0;
    }
    if (e == 0xFF) {
        return 0;
    }
    *r = sign | ((sd_u64) (e - 127 + 1023) << 52) | ((sd_u64) (f & 0x7FFFFF) << 29);
    return 1;
}

static inline int sd_trunc(sd_u64 d, sd_u32 *r)
{
    sd_u32 ed = SD_EXP(d);
    sd_u32 sign = (sd_u32) (d >> 63) << 31;
    sd_u64 frac = d & SD_FRAC, m, resto;
    int e;

    if (ed == 0) {
        if ((d << 1) == 0) {
            *r = sign;
            return 1;
        }
        return 0;
    }
    if (ed == 0x7FF) {
        return 0;
    }
    e = (int) ed - 1023 + 127;
    if (e <= 0 || e >= 0xFF) {
        return 0;
    }
    m = (frac | SD_HIDDEN) >> 29;
    resto = frac & ((1ULL << 29) - 1);
    if (resto > (1ULL << 28) || (resto == (1ULL << 28) && (m & 1))) {
        m++;
        if (m == (1ULL << 24)) {
            m >>= 1;
            e++;
            if (e >= 0xFF) {
                return 0;
            }
        }
    }
    *r = sign | ((sd_u32) e << 23) | ((sd_u32) m & 0x7FFFFF);
    return 1;
}

static inline sd_u64 sd_desde_int(int i)
{
    sd_u64 sign = 0, m;
    int e = 1023 + 52;

    if (i == 0) {
        return 0;
    }
    if (i < 0) {
        sign = CARTEL_SD;
        m = (sd_u64) (-(long long) i);
    } else {
        m = (sd_u64) i;
    }
    while (!(m & SD_HIDDEN)) {
        m <<= 1;
        e--;
    }
    return sign | ((sd_u64) e << 52) | (m & SD_FRAC);
}

static inline int sd_a_int(sd_u64 d, int *r)
{
    sd_u32 ed = SD_EXP(d);
    sd_u64 m;
    int desplaz;

    if (ed < 1023) {
        if (ed == 0x7FF) {
            return 0;
        }
        *r = 0; /* |d| < 1 (ceros y desnormales incluidos) */
        return 1;
    }
    if (ed >= 1023 + 31) {
        return 0;
    }
    m = (d & SD_FRAC) | SD_HIDDEN;
    desplaz = 52 - ((int) ed - 1023);
    m >>= desplaz;
    *r = (d & CARTEL_SD) ? -(int) m : (int) m;
    return 1;
}

/* Comparacion: -1, 0, 1, o 2 si alguno es NaN. */
static inline int sd_cmp(sd_u64 a, sd_u64 b)
{
    long long ka, kb;

    if ((SD_EXP(a) == 0x7FF && (a & SD_FRAC)) || (SD_EXP(b) == 0x7FF && (b & SD_FRAC))) {
        return 2;
    }
    if (((a | b) << 1) == 0) {
        return 0;
    }
    /* Orden total de los finitos e infinitos */
    ka = (a & CARTEL_SD) ? -(long long) (a & ~CARTEL_SD) : (long long) a;
    kb = (b & CARTEL_SD) ? -(long long) (b & ~CARTEL_SD) : (long long) b;
    return (ka < kb) ? -1 : (ka > kb);
}

#endif
