#include "sistema/doble_precision_nucleo.h"

typedef union {
    double d;
    sd_u64 u;
} DU;

typedef union {
    float f;
    sd_u32 u;
} FU;

double __real___adddf3(double a, double b);
double __real___subdf3(double a, double b);
double __real___muldf3(double a, double b);
double __real___extendsfdf2(float a);
float __real___truncdfsf2(double a);
double __real___floatsidf(int a);
int __real___fixdfsi(double a);
int __real___ltdf2(double a, double b);
int __real___gtdf2(double a, double b);
int __real___ledf2(double a, double b);
int __real___gedf2(double a, double b);
int __real___eqdf2(double a, double b);
int __real___nedf2(double a, double b);

#ifdef SMK64_PROF
#define RAPIDO(nombre) rapido_##nombre
#else
#define RAPIDO(nombre) __wrap_##nombre
#endif

double RAPIDO(__adddf3)(double a, double b)
{
    DU x = { a }, y = { b }, z;

    if (agregar_sd(x.u, y.u, &z.u)) {
        return z.d;
    }
    return __real___adddf3(a, b);
}

double RAPIDO(__subdf3)(double a, double b)
{
    DU x = { a }, y = { b }, z;

    if (agregar_sd(x.u, y.u ^ CARTEL_SD, &z.u)) {
        return z.d;
    }
    return __real___subdf3(a, b);
}

double RAPIDO(__muldf3)(double a, double b)
{
    DU x = { a }, y = { b }, z;

    if (mul_sd(x.u, y.u, &z.u)) {
        return z.d;
    }
    return __real___muldf3(a, b);
}

double RAPIDO(__extendsfdf2)(float a)
{
    FU x = { a };
    DU z;

    if (sd_extend(x.u, &z.u)) {
        return z.d;
    }
    return __real___extendsfdf2(a);
}

float RAPIDO(__truncdfsf2)(double a)
{
    DU x = { a };
    FU z;

    if (sd_trunc(x.u, &z.u)) {
        return z.f;
    }
    return __real___truncdfsf2(a);
}

double RAPIDO(__floatsidf)(int a)
{
    DU z;

    z.u = sd_desde_int(a);
    return z.d;
}

int RAPIDO(__fixdfsi)(double a)
{
    DU x = { a };
    int r;

    if (sd_a_int(x.u, &r)) {
        return r;
    }
    return __real___fixdfsi(a);
}

#define ENVOLTURA_CMP(nombre)                              \
    int RAPIDO(nombre)(double a, double b)              \
    {                                               \
        DU x = { a }, y = { b };                    \
        int c = sd_cmp(x.u, y.u);                   \
                                                    \
        return (c == 2) ? __real_##nombre(a, b) : c;  \
    }

ENVOLTURA_CMP(__ltdf2)
ENVOLTURA_CMP(__gtdf2)
ENVOLTURA_CMP(__ledf2)
ENVOLTURA_CMP(__gedf2)
#undef RAPIDO
#define RAPIDO(nombre) __wrap_##nombre
ENVOLTURA_CMP(__eqdf2)
ENVOLTURA_CMP(__nedf2)
