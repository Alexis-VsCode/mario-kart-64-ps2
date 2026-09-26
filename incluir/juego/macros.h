#ifndef JUEGO_MACROS_H
#define JUEGO_MACROS_H

#ifndef __sgi
#define GLOBAL_ASM(...)
#endif

#if !defined(__sgi) && (!defined(NON_MATCHING) || !defined(AVOID_UB))
#endif

#define CANTIDAD_ARREGLO(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

#define GLUE(a, b) a##b
#define GLUE2(a, b) GLUE(a, b)

#ifdef __GNUC__
#define SIN_USO __attribute__((unused))
#else
#define SIN_USO
#endif

#ifdef __GNUC__
#define NORETURN __attribute__((noreturn))
#else
#define NORETURN
#endif

#ifdef __GNUC__
#define SIN_REORDENAR __attribute__((sin_reordenar))
#else
#define SIN_REORDENAR
#endif

#ifdef __GNUC__
#define ASSERT_ESTATICO(cond, mens) _Static_assert(cond, mens)
#else
#define ASSERT_ESTATICO(cond, mens) typedef char GLUE2(estatico_asercion_fallido, __LINE__)[(cond) ? 1 : -1]
#endif

#ifdef __GNUC__
#define ALIGNED8 __attribute__((aligned(8)))
#else
#define ALIGNED8
#endif

#ifdef __GNUC__
#define ALIGNED16 __attribute__((aligned(16)))
#else
#define ALIGNED16
#endif

// Fixed point macros
#define FTOFIX(f) ((s32) ((f) * 65536.0))
#define ITOFIX(i) ((s32) ((i) << 16))
#define FIXTOF(x) ((double) ((x) / 65536.0))
#define FIXTOI(x) ((s32) ((x) >> 16))

#define a_int_fijo(f) (FTOFIX(f) >> 16)
#define a_frac(f) (FTOFIX(f) & 0xFFFF)

#define a_matriz_punto_fijo(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16)                    \
    {                                                                                                                \
        { ((a_int_fijo(x1)) << 16) | a_int_fijo(x2), ((a_int_fijo(x3)) << 16) | a_int_fijo(x4),                      \
          (a_int_fijo(x5) << 16) | a_int_fijo(x6), (a_int_fijo(x7) << 16) | a_int_fijo(x8) },                        \
            { ((a_int_fijo(x9)) << 16) | a_int_fijo(x10), ((a_int_fijo(x11)) << 16) | a_int_fijo(x12),               \
              (a_int_fijo(x13) << 16) | a_int_fijo(x14), (a_int_fijo(x15) << 16) | a_int_fijo(x16) },                \
            { ((a_frac(x1)) << 16) | a_frac(x2), ((a_frac(x3)) << 16) | a_frac(x4), (a_frac(x5) << 16) | a_frac(x6), \
              (a_frac(x7) << 16) | a_frac(x8) },                                                                     \
        {                                                                                                            \
            ((a_frac(x9)) << 16) | a_frac(x10), ((a_frac(x11)) << 16) | a_frac(x12),                                 \
                (a_frac(x13) << 16) | a_frac(x14), (a_frac(x15) << 16) | a_frac(x16)                                 \
        }                                                                                                            \
    }

#ifdef TARGET_PS2
#define VIRTUAL_A_FISICO(direccion) ((uintptr_t) (direccion) & 0x1FFFFFFF)
#define FISICO_A_VIRTUAL(direccion) ((uintptr_t) (direccion) & 0x1FFFFFFF)
#define VIRTUAL_A_PHYSICAL2(direccion) ((u8*) (direccion))
#else
#define VIRTUAL_A_FISICO(direccion) ((uintptr_t) (direccion) & 0x1FFFFFFF)

#define FISICO_A_VIRTUAL(direccion) ((uintptr_t) (direccion) | 0x80000000)

#define VIRTUAL_A_PHYSICAL2(direccion) ((u8*) (direccion) - 0x80000000U)
#endif

#ifdef TARGET_PS2
void marcar_punto_control(const char* where);
#define MARCAR_PUNTO_CONTROL(s) marcar_punto_control(s)
#else
#define MARCAR_PUNTO_CONTROL(s)
#endif

/* Cronometro de fases del port de PS2 (src/os/cronometro_fases.c) */
#ifdef TARGET_PS2
void empezar_tiempos_ps2(const char* group);
void marcar_tiempos_ps2(const char* paso);
void fin_tiempos_ps2(void);
void ps2_tiempos_esperado_frame(const void* dl);
#define EMPEZAR_TIEMPOS_PS2(g) empezar_tiempos_ps2(g)
#define MARCAR_TIEMPOS_PS2(s) marcar_tiempos_ps2(s)
#define FIN_TIEMPOS_PS2() fin_tiempos_ps2()
#define PS2_TIEMPOS_ESPERADO_FRAME(dl) ps2_tiempos_esperado_frame(dl)
#else
#define EMPEZAR_TIEMPOS_PS2(g)
#define MARCAR_TIEMPOS_PS2(s)
#define FIN_TIEMPOS_PS2()
#define PS2_TIEMPOS_ESPERADO_FRAME(dl)
#endif

#ifdef TARGET_PS2
#define TAMANIO_SIN_COMPRIMIR_MIO0(p)                                                                       \
    (((u32) ((u8*) (p))[4] << 24) | ((u32) ((u8*) (p))[5] << 16) | ((u32) ((u8*) (p))[6] << 8) | \
     (u32) ((u8*) (p))[7])
#else
#define TAMANIO_SIN_COMPRIMIR_MIO0(p) (*(u32*) ((u8*) (p) + 4))
#endif

/* Un texel de 16 bits (RGBA5551) leido o escrito por la CPU */
#ifdef TARGET_PS2
#define TEXEL16(x) ((u16) __builtin_bswap16((u16) (x)))
#else
#define TEXEL16(x) (x)
#endif

#define ALIGN16(val) (((val) + 0xF) & ~0xF)

#define FIN_EMPAQUETADO_OBTENER(dl) (((u8*) dl) + sizeof(dl) - sizeof(dl[0]) - 0x07000000)

#define CUAD(x) ((x) * (x))

#endif
