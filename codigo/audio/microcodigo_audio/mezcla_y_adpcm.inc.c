// Mezcla y adpcm

#ifndef ASPMAIN_PTR
#define ASPMAIN_PTR(direccion) ((void *) (uintptr_t) (direccion))
#endif

#if defined(_EE) && !defined(ASPMAIN_NO_MMI)
#define ASPMAIN_MMI 1
#endif

/* Alineada: la version MMI lee cada fila (8 bytes) con un ld. */
static s16 tabla_remuestreo[64][4] __attribute__((aligned(16)));

void inicializar_aspmain(const u8 *asp_principal_datos_be)
{
    int i;

    /* Tabla de remuestreo */
    for (i = 0; i < 64 * 4; i++) {
        const u8 *p = asp_principal_datos_be + 0x100 + i * 2;

        tabla_remuestreo[i / 4][i % 4] = (s16) ((p[0] << 8) | p[1]);
    }
}

static union {
    s16 s16[2048];
    u8 u8[4096];
} s_dmem __attribute__((aligned(16)));

#define DMEM_U8(a)  (&s_dmem.u8[(a) & 0xFFF])
#define DMEM_S16(a) (&s_dmem.s16[((a) & 0xFFF) / 2])
#define ARRIBA_RONDA_16(v)   (((v) + 15) & ~15)
#define ARRIBA_RONDA_8(v)    (((v) + 7) & ~7)
#define ARRIBA_RONDA_32(v)   (((v) + 31) & ~31)
#define ABAJO_RONDA_16(v) ((v) & ~15)

static struct {
    u16 in, out, nbytes;
    u16 vol[2];
    s16 tasa[2];
    u16 humedo_vol;
    s16 humedo_tasa;
    s16 *estado_bucle;
} Rsp;

#define LIBRO_DMEM 0xF80

static int atajos_audio = 1;
#ifdef SMK64_DEV
static u32 remuestreos_totales, remuestreos_sin_salida;
#endif

static inline s16 limitar16(s32 v)
{
    return v < -0x8000 ? -0x8000 : (v > 0x7FFF ? 0x7FFF : (s16) v);
}

#define ADPCM_NIB(n, desplaz) ((s32) (s16) ((((s32) (n)) << 28) >> 28 << (desplaz)))

#ifdef ASPMAIN_MMI
static int mmi_usar = 1;
#ifdef SMK64_DEV
/* Comandos que fueron por el C (registro) */
static u32 mmi_c[5];
#define MMI_C(i) (mmi_c[i]++)
#else
#define MMI_C(i) ((void) 0)
#endif

typedef s16 Vec8[8] __attribute__((aligned(16)));

/* Palabras de 32 bits */
static const u32 s_k_4000[4] __attribute__((aligned(16))) = { 0x4000, 0x4000, 0x4000, 0x4000 };
static const u32 k7_ff_fw[4] __attribute__((aligned(16))) = { 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF };
static const u32 k7_ff_fh[4] __attribute__((aligned(16))) = { 0x7FFF7FFF, 0x7FFF7FFF, 0x7FFF7FFF, 0x7FFF7FFF };

#define MMI_BCAST(d, r) "pcpyld " d ", " r ", " r "\n\t" "pcpyh  " d ", " d "\n\t"

#define MMI_MULHI_U(d, x, v, t1, t2)             \
    "pmulth " d ", " x ", " v "\n\t"             \
    "psraw  " t1 ", " x ", 16\n\t"               \
    "pmulth " t1 ", " t1 ", " v "\n\t"           \
    "psrah  " t2 ", " v ", 15\n\t"               \
    "psraw  " d ", " d ", 16\n\t"                \
    "psraw  " t1 ", " t1 ", 16\n\t"              \
    "pand   " t2 ", " x ", " t2 "\n\t"           \
    "pinteh " d ", " t1 ", " d "\n\t"            \
    "paddh  " d ", " d ", " t2 "\n\t"

static inline int dmem_en(u32 direccion, u32 largo)
{
    return direccion + largo <= 0x1000;
}

static inline int superponer_ranges(u32 a, u32 alen, u32 b, u32 blen)
{
    return a < b + blen && b < a + alen;
}

static Vec8 amb_k[3];

static int envmixer_mmi(u32 w0, u32 w1, int n)
{
    u32 en_a = ((w0 >> 16) & 0xFF) << 4;
    u32 d0 = ((w1 >> 24) & 0xFF) << 4, d1 = ((w1 >> 16) & 0xFF) << 4;
    u32 e0 = ((w1 >> 8) & 0xFF) << 4, e1 = (w1 & 0xFF) << 4;
    u32 largo = (u32) (n > 0 ? n : 8) * 2;
    u8 *in, *seco0, *seco1, *humedo0, *humedo1;
    u32 v0 = Rsp.vol[0], v1 = Rsp.vol[1];
    s32 r0 = Rsp.tasa[0], r1 = Rsp.tasa[1];
    int i;

    if (Rsp.humedo_tasa != 0 || !dmem_en(en_a, largo) || !dmem_en(d0, largo) || !dmem_en(d1, largo) || !dmem_en(e0, largo) ||
        !dmem_en(e1, largo)) {
        return 0;
    }
    in = DMEM_U8(en_a);
    seco0 = DMEM_U8(d0);
    seco1 = DMEM_U8(d1);
    humedo0 = DMEM_U8(e0);
    humedo1 = DMEM_U8(e1);
    for (i = 0; i < 8; i++) {
        amb_k[0][i] = (w0 & 2) ? -1 : 0;
        amb_k[1][i] = (w0 & 1) ? -1 : 0;
        amb_k[2][i] = (s16) Rsp.humedo_vol;
    }
    __asm__ __volatile__(
        "lq     $24, 0(%[k])\n\t"
        "lq     $25, 16(%[k])\n\t"
        "lq     $15, 32(%[k])\n\t"
        "1:\n\t"
        "lq     $8, 0(%[in])\n\t"
        MMI_BCAST("$9", "%[v0]")
        MMI_MULHI_U("$13", "$8", "$9", "$10", "$11")
        "pxor   $13, $13, $24\n\t"
        MMI_BCAST("$9", "%[v1]")
        MMI_MULHI_U("$14", "$8", "$9", "$10", "$11")
        "pxor   $14, $14, $25\n\t"
        MMI_MULHI_U("$12", "$13", "$15", "$10", "$11")
        "lq     $8, 0(%[d0])\n\t"
        "paddsh $8, $8, $13\n\t"
        "sq     $8, 0(%[d0])\n\t"
        "lq     $8, 0(%[w0])\n\t"
        "paddsh $8, $8, $12\n\t"
        "sq     $8, 0(%[w0])\n\t"
        MMI_MULHI_U("$12", "$14", "$15", "$10", "$11")
        "lq     $8, 0(%[d1])\n\t"
        "paddsh $8, $8, $14\n\t"
        "sq     $8, 0(%[d1])\n\t"
        "lq     $8, 0(%[w1])\n\t"
        "paddsh $8, $8, $12\n\t"
        "sq     $8, 0(%[w1])\n\t"
        "addu   %[v0], %[v0], %[r0]\n\t"
        "addu   %[v1], %[v1], %[r1]\n\t"
        "addiu  %[in], %[in], 16\n\t"
        "addiu  %[d0], %[d0], 16\n\t"
        "addiu  %[w0], %[w0], 16\n\t"
        "addiu  %[d1], %[d1], 16\n\t"
        "addiu  %[w1], %[w1], 16\n\t"
        "addiu  %[n], %[n], -8\n\t"
        "bgtz   %[n], 1b\n\t"
        : [in] "+r"(in), [d0] "+r"(seco0), [w0] "+r"(humedo0), [d1] "+r"(seco1), [w1] "+r"(humedo1), [v0] "+r"(v0),
          [v1] "+r"(v1), [n] "+r"(n)
        : [r0] "r"(r0), [r1] "r"(r1), [k] "r"(amb_k)
        : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "memory");
    return 1;
}

static int mezclar_mmi(u32 nbytes, s16 ganancia, u32 direccion_entrada, u32 direccion_salida)
{
    u8 *in = DMEM_U8(direccion_entrada), *salida = DMEM_U8(direccion_salida);
    s32 n = (s32) nbytes;
    s32 g = ganancia;

    if (((direccion_entrada | direccion_salida) & 15) != 0 || !dmem_en(direccion_entrada & 0xFFF, nbytes) || !dmem_en(direccion_salida & 0xFFF, nbytes)) {
        return 0;
    }
    if (n <= 0) {
        return 1;
    }
    __asm__ __volatile__(
        "lq     $12, 0(%[kh])\n\t"
        MMI_BCAST("$13", "%[g]")
        "lq     $14, 0(%[kr])\n\t"
        "lq     $15, 0(%[kw])\n\t"
        "pnor   $24, $15, $0\n\t"
        "lq     $8, 0(%[in])\n\t"
        "lq     $9, 16(%[in])\n\t"
        "1:\n\t"
        "lq     $10, 0(%[salida])\n\t"
        "lq     $11, 16(%[salida])\n\t"
        "pmtlo  $14\n\t"
        "pmthi  $14\n\t"
        "pmaddh $10, $10, $12\n\t"
        "pmaddh $10, $8, $13\n\t"
        "pmfhl.lw $10\n\t"
        "pmfhl.uw $25\n\t"
        "psraw  $10, $10, 15\n\t"
        "psraw  $25, $25, 15\n\t"
        "pmaxw  $10, $10, $24\n\t"
        "pminw  $10, $10, $15\n\t"
        "pmaxw  $25, $25, $24\n\t"
        "pminw  $25, $25, $15\n\t"
        "pinteh $10, $25, $10\n\t"
        "pmtlo  $14\n\t"
        "pmthi  $14\n\t"
        "pmaddh $11, $11, $12\n\t"
        "pmaddh $11, $9, $13\n\t"
        "pmfhl.lw $11\n\t"
        "pmfhl.uw $25\n\t"
        "psraw  $11, $11, 15\n\t"
        "psraw  $25, $25, 15\n\t"
        "pmaxw  $11, $11, $24\n\t"
        "pminw  $11, $11, $15\n\t"
        "pmaxw  $25, $25, $24\n\t"
        "pminw  $25, $25, $15\n\t"
        "pinteh $11, $25, $11\n\t"
        "sq     $10, 0(%[salida])\n\t"
        "addiu  %[in], %[in], 32\n\t"
        "addiu  %[n], %[n], -32\n\t"
        "blez   %[n], 2f\n\t"
        "lq     $8, 0(%[in])\n\t"
        "lq     $9, 16(%[in])\n\t"
        "2:\n\t"
        "sq     $11, 16(%[salida])\n\t"
        "addiu  %[salida], %[salida], 32\n\t"
        "bgtz   %[n], 1b\n\t"
        : [in] "+r"(in), [salida] "+r"(salida), [n] "+r"(n)
        : [g] "r"(g), [kh] "r"(k7_ff_fh), [kr] "r"(s_k_4000), [kw] "r"(k7_ff_fw)
        : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "memory");
    return 1;
}

/* A_RESAMPLE con salida */
#define RS_UNO(ri, rt)                                                                  \
    "ldl    " ri ", 7(%[in])\n\t"                                                     \
    "ldr    " ri ", 0(%[in])\n\t"                                                     \
    "srl    $2, %[acc], 7\n\t"                                                        \
    "andi   $2, $2, 0x1F8\n\t"                                                        \
    "addu   $2, $2, %[tab]\n\t"                                                       \
    "ld     " rt ", 0($2)\n\t"                                                        \
    "addu   %[acc], %[acc], %[p2]\n\t"                                                \
    "srl    $3, %[acc], 16\n\t"                                                       \
    "sll    $3, $3, 1\n\t"                                                            \
    "addu   %[in], %[in], $3\n\t"                                                     \
    "andi   %[acc], %[acc], 0xFFFF\n\t"
#define PAR_RS(s)                                                                      \
    RS_UNO("$8", "$10")                                                                 \
    RS_UNO("$9", "$11")                                                                 \
    "pextlw $8, $9, $8\n\t"                                                           \
    "pextlw $10, $11, $10\n\t"                                                        \
    "pmtlo  $24\n\t"                                                                  \
    "pmthi  $24\n\t"                                                                  \
    "pmaddh $8, $8, $10\n\t"                                                          \
    "pmfhl.lw $8\n\t"                                                                 \
    "pmfhl.uw $9\n\t"                                                                 \
    "psraw  $8, $8, 15\n\t"                                                           \
    "psraw  $9, $9, 15\n\t"                                                           \
    "paddw  " s ", $8, $9\n\t"

static void remuestrear_mmi(s16 **inp, s16 *salida, u32 *accp, u32 tono2, int nbytes)
{
    u8 *in = (u8 *) *inp;
    u32 acc = *accp;

    __asm__ __volatile__(
        "lq     $24, 0(%[kr])\n\t"
        "lq     $25, 0(%[kw])\n\t"
        "1:\n\t"
        PAR_RS("$12")
        PAR_RS("$13")
        "pcpyld $14, $13, $12\n\t"
        "pcpyud $15, $12, $13\n\t"
        "paddw  $14, $14, $15\n\t"
        PAR_RS("$12")
        PAR_RS("$13")
        "pcpyld $15, $13, $12\n\t"
        "pcpyud $12, $12, $13\n\t"
        "paddw  $15, $15, $12\n\t"
        "pnor   $13, $25, $0\n\t"
        "pmaxw  $14, $14, $13\n\t"
        "pminw  $14, $14, $25\n\t"
        "pmaxw  $15, $15, $13\n\t"
        "pminw  $15, $15, $25\n\t"
        "ppach  $14, $15, $14\n\t"
        "sq     $14, 0(%[salida])\n\t"
        "addiu  %[salida], %[salida], 16\n\t"
        "addiu  %[n], %[n], -16\n\t"
        "bgtz   %[n], 1b\n\t"
        : [in] "+r"(in), [salida] "+r"(salida), [acc] "+r"(acc), [n] "+r"(nbytes)
        : [p2] "r"(tono2), [tab] "r"(tabla_remuestreo), [kr] "r"(s_k_4000), [kw] "r"(k7_ff_fw)
        : "$2", "$3", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "memory");
    *inp = (s16 *) in;
    *accp = acc;
}

static Vec8 adpcm_cols[16][10];
/* Las columnas se guardan con las dos filas de las que salen */
static u64 clave_adpcm[16][4];
static u8 valido_clave_adpcm[16];

static void cols_construir_adpcm(u32 idx)
{
    const s16 *c0 = DMEM_S16(LIBRO_DMEM + idx * 32);
    const s16 *c1 = DMEM_S16(LIBRO_DMEM + idx * 32 + 16);
    const u64 *renglones = (const u64 *) c0;
    u64 *clave = clave_adpcm[idx];
    Vec8 *col = adpcm_cols[idx];
    int j, k;

    if (valido_clave_adpcm[idx] && clave[0] == renglones[0] && clave[1] == renglones[1] && clave[2] == renglones[2] && clave[3] == renglones[3]) {
        return;
    }
    clave[0] = renglones[0];
    clave[1] = renglones[1];
    clave[2] = renglones[2];
    clave[3] = renglones[3];
    valido_clave_adpcm[idx] = 1;
    for (k = 0; k < 8; k++) {
        col[0][k] = c0[k];
        col[1][k] = c1[k];
    }
    for (j = 0; j < 8; j++) {
        for (k = 0; k < 8; k++) {
            col[2 + j][k] = k < j ? 0 : (k == j ? 2048 : c1[k - j - 1]);
        }
    }
}

#define ADPCM_X(op, sl, apagado_col)                                                         \
    "sll    $3, $2, " #sl "\n\t"                                                      \
    "sra    $3, $3, 28\n\t"                                                           \
    "sllv   $3, $3, %[sh]\n\t"                                                        \
    MMI_BCAST("$9", "$3")                                                               \
    "lq     $8, " #apagado_col "(%[col])\n\t"                                              \
    op "  $10, $8, $9\n\t"
/* Las 8 salidas de una mitad */
#define MITAD_ADPCM(apagado_salida)                                                              \
    ADPCM_X("pmulth", 24, 32)                                                           \
    ADPCM_X("pmaddh", 28, 48)                                                           \
    ADPCM_X("pmaddh", 16, 64)                                                           \
    ADPCM_X("pmaddh", 20, 80)                                                           \
    ADPCM_X("pmaddh", 8, 96)                                                            \
    ADPCM_X("pmaddh", 12, 112)                                                          \
    ADPCM_X("pmaddh", 0, 128)                                                           \
    ADPCM_X("pmaddh", 4, 144)                                                           \
    "pcpyud $11, $24, $24\n\t"                                                        \
    "pexeh  $12, $11\n\t"                                                             \
    "pcpyh  $12, $12\n\t"                                                             \
    "prevh  $11, $11\n\t"                                                             \
    "pcpyh  $11, $11\n\t"                                                             \
    "lq     $8, 0(%[col])\n\t"                                                        \
    "pmaddh $10, $8, $12\n\t"                                                         \
    "lq     $8, 16(%[col])\n\t"                                                       \
    "pmaddh $10, $8, $11\n\t"                                                         \
    "pmfhl.lw $10\n\t"                                                                \
    "pmfhl.uw $11\n\t"                                                                \
    "psraw  $10, $10, 11\n\t"                                                         \
    "psraw  $11, $11, 11\n\t"                                                         \
    "pmaxw  $10, $10, $14\n\t"                                                        \
    "pminw  $10, $10, $15\n\t"                                                        \
    "pmaxw  $11, $11, $14\n\t"                                                        \
    "pminw  $11, $11, $15\n\t"                                                        \
    "pinteh $24, $11, $10\n\t"                                                        \
    "sq     $24, " #apagado_salida "(%[salida])\n\t"

/* Una trama */
static inline void adpcm_frame_mmi(const u8 *in, s16 *salida, const Vec8 *col, u32 desplaz)
{
    __asm__ __volatile__(
        "ldl    $2, 8(%[in])\n\t"
        "ldr    $2, 1(%[in])\n\t"
        "lq     $15, 0(%[kw])\n\t"
        "pnor   $14, $15, $0\n\t"
        "lq     $24, -16(%[salida])\n\t"
        MITAD_ADPCM(0)
        "dsrl32 $2, $2, 0\n\t"
        MITAD_ADPCM(16)
        :
        : [in] "r"(in), [salida] "r"(salida), [col] "r"(col), [sh] "r"(desplaz), [kw] "r"(k7_ff_fw)
        : "$2", "$3", "$8", "$9", "$10", "$11", "$12", "$14", "$15", "$24", "hi", "lo", "memory");
}

static int adpcm_mmi(u32 banderas, s16 *estado)
{
    u32 o = Rsp.out & 0xFFF;
    int nbytes = ARRIBA_RONDA_32(Rsp.nbytes);
    u8 *in = DMEM_U8(Rsp.in);
    s16 *salida = DMEM_S16(o);
    u32 built = 0;

    if ((o & 15) != 0 || !dmem_en(o, 32 + nbytes) || superponer_ranges(o, 32 + nbytes, 0xF80, 0x80) ||
        superponer_ranges(o, 32 + nbytes, 0, 0x180)) {
        return 0;
    }
    if (banderas & A_INIT) {
        memset(salida, 0, 16 * sizeof(s16));
    } else if (banderas & A_LOOP) {
        memcpy(salida, Rsp.estado_bucle, 16 * sizeof(s16));
    } else {
        memcpy(salida, estado, 16 * sizeof(s16));
    }
    salida += 16;
    while (nbytes > 0) {
        u32 h = in[0], idx = h & 0xF, desplaz = (h >> 4) > 12 ? 12 : (h >> 4);

        if (!(built & (1u << idx))) {
            cols_construir_adpcm(idx);
            built |= 1u << idx;
        }
        adpcm_frame_mmi(in, salida, adpcm_cols[idx], desplaz);
        in += 9;
        salida += 16;
        nbytes -= 16 * sizeof(s16);
    }
    memcpy(estado, salida - 16, 16 * sizeof(s16));
    return 1;
}
#endif

static void a_adpcm(u32 banderas, s16 *estado)
{
    u8 *in = DMEM_U8(Rsp.in);
    s16 *salida = DMEM_S16(Rsp.out);
    int nbytes = ARRIBA_RONDA_32(Rsp.nbytes);

#ifdef ASPMAIN_MMI
    if (mmi_usar) {
        if (adpcm_mmi(banderas, estado)) {
            return;
        }
        MMI_C(0);
    }
#endif
    if (banderas & A_INIT) {
        memset(salida, 0, 16 * sizeof(s16));
    } else if (banderas & A_LOOP) {
        memcpy(salida, Rsp.estado_bucle, 16 * sizeof(s16));
    } else {
        memcpy(salida, estado, 16 * sizeof(s16));
    }
    salida += 16;

    while (nbytes > 0) {
        u8 frame[9];
        const u8 *d = frame + 1;
        /* Escalas 13-15 */
        int desplaz = (in[0] >> 4) > 12 ? 12 : (in[0] >> 4);
        s16 c0[8], c1[8];
        int i;

        memcpy(frame, in, sizeof(frame));
        memcpy(c0, DMEM_S16(LIBRO_DMEM + (frame[0] & 0xF) * 32), sizeof(c0));
        memcpy(c1, DMEM_S16(LIBRO_DMEM + (frame[0] & 0xF) * 32 + 16), sizeof(c1));
        in += sizeof(frame);
        for (i = 0; i < 2; i++) {
            /* Filtro de orden 2 del libro de codigos, desenrollado */
            s32 p1 = salida[-1], p2 = salida[-2];
            s32 x0 = ADPCM_NIB(d[0] >> 4, desplaz), x1 = ADPCM_NIB(d[0] & 0xF, desplaz);
            s32 x2 = ADPCM_NIB(d[1] >> 4, desplaz), x3 = ADPCM_NIB(d[1] & 0xF, desplaz);
            s32 x4 = ADPCM_NIB(d[2] >> 4, desplaz), x5 = ADPCM_NIB(d[2] & 0xF, desplaz);
            s32 x6 = ADPCM_NIB(d[3] >> 4, desplaz), x7 = ADPCM_NIB(d[3] & 0xF, desplaz);
            s32 k0 = c1[0], k1 = c1[1], k2 = c1[2], k3 = c1[3], k4 = c1[4], k5 = c1[5], k6 = c1[6];

            d += 4;
            salida[0] = limitar16((c0[0] * p2 + k0 * p1 + (x0 << 11)) >> 11);
            salida[1] = limitar16((c0[1] * p2 + k1 * p1 + (x1 << 11) + k0 * x0) >> 11);
            salida[2] = limitar16((c0[2] * p2 + k2 * p1 + (x2 << 11) + k1 * x0 + k0 * x1) >> 11);
            salida[3] = limitar16((c0[3] * p2 + k3 * p1 + (x3 << 11) + k2 * x0 + k1 * x1 + k0 * x2) >> 11);
            salida[4] = limitar16((c0[4] * p2 + k4 * p1 + (x4 << 11) + k3 * x0 + k2 * x1 + k1 * x2 + k0 * x3) >> 11);
            salida[5] = limitar16((c0[5] * p2 + k5 * p1 + (x5 << 11) + k4 * x0 + k3 * x1 + k2 * x2 + k1 * x3 + k0 * x4) >> 11);
            salida[6] = limitar16((c0[6] * p2 + k6 * p1 + (x6 << 11) + k5 * x0 + k4 * x1 + k3 * x2 + k2 * x3 + k1 * x4 +
                              k0 * x5) >>
                             11);
            salida[7] = limitar16((c0[7] * p2 + c1[7] * p1 + (x7 << 11) + k6 * x0 + k5 * x1 + k4 * x2 + k3 * x3 + k2 * x4 +
                              k1 * x5 + k0 * x6) >>
                             11);
            salida += 8;
        }
        nbytes -= 16 * sizeof(s16);
    }
    memcpy(estado, salida - 16, 16 * sizeof(s16));
}

static inline s16 be_rd16(u32 a)
{
    return (s16) ((s_dmem.u8[(a & 0xFFF) ^ 1] << 8) | s_dmem.u8[((a + 1) & 0xFFF) ^ 1]);
}

static inline void be_wr16(u32 a, s16 v)
{
    s_dmem.u8[(a & 0xFFF) ^ 1] = (u8) ((u16) v >> 8);
    s_dmem.u8[((a + 1) & 0xFFF) ^ 1] = (u8) v;
}

/* Entrada en direccion impar (el juego la pide a veces) */
static void odd_remuestreo_a(u32 banderas, u16 tono, s16 *estado)
{
    u32 en_inicial = Rsp.in & 0xFFF, in = en_inicial, rel, blk;
    s16 *salida = DMEM_S16(Rsp.out);
    int nbytes = ARRIBA_RONDA_16(Rsp.nbytes);
    s16 tmp[16];
    u32 acc;
    int i, j;

    if (banderas & A_INIT) {
        memset(tmp, 0, 5 * sizeof(s16));
    } else {
        memcpy(tmp, estado, 16 * sizeof(s16));
    }
    if (banderas & 2) {
        for (i = 0; i < 8; i++) {
            be_wr16(in - 16 + i * 2, tmp[8 + i]);
        }
        in -= tmp[5] & ~1;
    }
    in -= 8;
    acc = (u16) tmp[4];
    for (i = 0; i < 4; i++) {
        be_wr16(in + i * 2, tmp[i]);
    }
    do {
        for (i = 0; i < 8; i++) {
            const s16 *t = tabla_remuestreo[(acc * 64) >> 16];
            s32 sum = 0;

            for (j = 0; j < 4; j++) {
                sum += (be_rd16(in + j * 2) * t[j] + 0x4000) >> 15;
            }
            *salida++ = limitar16(sum);
            acc += (u32) tono << 1;
            in += (acc >> 16) * 2;
            acc &= 0xFFFF;
        }
        nbytes -= 8 * sizeof(s16);
    } while (nbytes > 0);

    for (i = 0; i < 4; i++) {
        estado[i] = be_rd16(in + i * 2);
    }
    estado[4] = (s16) acc;
    rel = (in + 8 - en_inicial) & 0xFFF;
    estado[5] = (s16) ((0u - rel) & 0xF);
    estado[6] = 0;
    estado[7] = 0;
    blk = en_inicial + (rel & ~0xFu);
    for (i = 0; i < 8; i++) {
        estado[8 + i] = be_rd16(blk + i * 2);
    }
}

static void remuestreo_a(u32 banderas, u16 tono, s16 *estado, int calcular_salida)
{
    s16 tmp[16];
    s16 *en_inicial = DMEM_S16(Rsp.in);
    s16 *in = en_inicial;
    s16 *salida = DMEM_S16(Rsp.out);
    int nbytes = ARRIBA_RONDA_16(Rsp.nbytes);
    u32 acc, rel;
    int i;

    if (Rsp.in & 1) {
        odd_remuestreo_a(banderas, tono, estado);
        return;
    }
    if (banderas & A_INIT) {
        memset(tmp, 0, 5 * sizeof(s16));
    } else {
        memcpy(tmp, estado, 16 * sizeof(s16));
    }
    if (banderas & 2) {
        memcpy(in - 8, tmp + 8, 8 * sizeof(s16));
        in -= tmp[5] / (s32) sizeof(s16);
    }
    in -= 4;
    acc = (u16) tmp[4];
    memcpy(in, tmp, 4 * sizeof(s16));

    if (!calcular_salida) {
        u32 muestras = 8 * (u32) (nbytes > 16 ? nbytes / 16 : 1);
        u32 total = acc + muestras * ((u32) tono << 1);

        in += total >> 16;
        acc = total & 0xFFFF;
        goto salida_estado;
    }
#ifdef ASPMAIN_MMI
    if (mmi_usar) {
        u32 muestras = 8 * (u32) (nbytes > 16 ? nbytes / 16 : 1);
        u32 total = acc + muestras * ((u32) tono << 1);
        u32 en_apagado = (u32) ((u8 *) in - s_dmem.u8), en_largo = ((total >> 16) + 4) * sizeof(s16);
        u32 apagado_salida = (u32) ((u8 *) salida - s_dmem.u8), largo_salida = muestras * sizeof(s16);

        if ((apagado_salida & 15) == 0 && en_apagado < 0x1000 && dmem_en(en_apagado, en_largo) && dmem_en(apagado_salida, largo_salida) &&
            !superponer_ranges(en_apagado, en_largo, apagado_salida, largo_salida)) {
            remuestrear_mmi(&in, salida, &acc, (u32) tono << 1, nbytes);
            goto salida_estado;
        }
        MMI_C((apagado_salida & 15) != 0 ? 1 : 2);
    }
#endif
    do {
        for (i = 0; i < 8; i++) {
            const s16 *t = tabla_remuestreo[(acc * 64) >> 16];
            s32 s = ((in[0] * t[0] + 0x4000) >> 15) + ((in[1] * t[1] + 0x4000) >> 15) +
                    ((in[2] * t[2] + 0x4000) >> 15) + ((in[3] * t[3] + 0x4000) >> 15);

            *salida++ = limitar16(s);
            acc += (u32) tono << 1;
            in += acc >> 16;
            acc &= 0xFFFF;
        }
        nbytes -= 8 * sizeof(s16);
    } while (nbytes > 0);

salida_estado:
    estado[4] = (s16) acc;
    memcpy(estado, in, 4 * sizeof(s16));
    rel = (u32) ((in + 4) - en_inicial) * sizeof(s16) & 0xFFF;
    estado[5] = (s16) ((0u - rel) & 0xF);
    estado[6] = 0;
    estado[7] = 0;
    memcpy(estado + 8, DMEM_U8(Rsp.in + (rel & ~0xFu)), 8 * sizeof(s16));
}

#ifdef SMK64_DEV
static u32 envolventes_mudas, envolventes_sin_reverb, envolventes_totales, muestras_envolventes;
#endif

static void a_envmixer(u32 w0, u32 w1)
{
    s16 *in = DMEM_S16(((w0 >> 16) & 0xFF) << 4);
    /* Muestras de 8 en 8, como el original (el juego manda p */
    int n = ARRIBA_RONDA_8((w0 >> 8) & 0xFF);
    int intercambiar = 0;
    s32 neg0 = (w0 & 2) ? -1 : 0, neg1 = (w0 & 1) ? -1 : 0;
    s16 *seco0 = DMEM_S16(((w1 >> 24) & 0xFF) << 4), *seco1 = DMEM_S16(((w1 >> 16) & 0xFF) << 4);
    s16 *humedo0 = DMEM_S16(((w1 >> 8) & 0xFF) << 4), *humedo1 = DMEM_S16((w1 & 0xFF) << 4);
    u16 vol0 = Rsp.vol[0], vol1 = Rsp.vol[1], humedo_vol = Rsp.humedo_vol;
    int i;

#ifdef SMK64_DEV
    envolventes_totales++;
    muestras_envolventes += n;
    if (vol0 == 0 && vol1 == 0 && Rsp.tasa[0] == 0 && Rsp.tasa[1] == 0) {
        envolventes_mudas++;
    }
    if (humedo_vol == 0 && Rsp.humedo_tasa == 0) {
        envolventes_sin_reverb++;
    }
#endif

    /* Nota muda (volumen 0 sin rampa) */
    if (vol0 == 0 && vol1 == 0 && Rsp.tasa[0] == 0 && Rsp.tasa[1] == 0 && Rsp.humedo_tasa == 0) {
        s32 a = (s16) neg0, b = (s16) neg1;
        s32 wa = intercambiar ? b : a, wb = intercambiar ? a : b;
        s32 c[4];
        s16 *dst[4];
        int cantidad = (n > 0) ? n : 8; /* el bucle general hace al menos 8 */
        int k;

        c[0] = a;
        c[1] = (s16) ((wa * (s32) humedo_vol) >> 16);
        c[2] = b;
        c[3] = (s16) ((wb * (s32) humedo_vol) >> 16);
        dst[0] = seco0;
        dst[1] = humedo0;
        dst[2] = seco1;
        dst[3] = humedo1;
        for (k = 0; k < 4; k++) {
            if (c[k] != 0) {
                s16 *d = dst[k];

                for (i = 0; i < cantidad; i++) {
                    d[i] = limitar16(d[i] + c[k]);
                }
            }
        }
        return;
    }

#ifdef ASPMAIN_MMI
    if (mmi_usar) {
        if (envmixer_mmi(w0, w1, n)) {
            return;
        }
        MMI_C(3);
    }
#endif
    do {
        s32 v0 = vol0, v1 = vol1, vw = humedo_vol;

        for (i = 0; i < 8; i++) {
            s32 x = *in++;
            s32 a = (s16) ((s16) ((x * v0) >> 16) ^ neg0);
            s32 b = (s16) ((s16) ((x * v1) >> 16) ^ neg1);
            s32 wa = intercambiar ? b : a, wb = intercambiar ? a : b;

            *seco0 = limitar16(*seco0 + a);
            seco0++;
            *humedo0 = limitar16(*humedo0 + (s16) ((wa * vw) >> 16));
            humedo0++;
            *seco1 = limitar16(*seco1 + b);
            seco1++;
            *humedo1 = limitar16(*humedo1 + (s16) ((wb * vw) >> 16));
            humedo1++;
        }
        vol0 += Rsp.tasa[0];
        vol1 += Rsp.tasa[1];
        humedo_vol += Rsp.humedo_tasa;
        n -= 8;
    } while (n > 0);
}

static void mezcla_a(u32 cantidad16, s16 ganancia, u16 direccion_entrada, u16 direccion_salida)
{
    int nbytes = ARRIBA_RONDA_32(ABAJO_RONDA_16(cantidad16 << 4));
    s16 *in = DMEM_S16(direccion_entrada);
    s16 *salida = DMEM_S16(direccion_salida);
    s16 a[16], b[16], r[16];
    int i;

#ifdef ASPMAIN_MMI
    if (mmi_usar) {
        if (mezclar_mmi(nbytes, ganancia, direccion_entrada, direccion_salida)) {
            return;
        }
        MMI_C(4);
    }
#endif
    /* De 16 en 16 muestras y con el orden del microcodigo */
    memcpy(a, in, sizeof(a));
    while (nbytes > 0) {
        memcpy(b, salida, sizeof(b));
        for (i = 0; i < 16; i++) {
            r[i] = limitar16((b[i] * 0x7FFF + a[i] * ganancia + 0x4000) >> 15);
        }
        memcpy(salida, r, 8 * sizeof(s16));
        in += 16;
        if (nbytes > 32) {
            memcpy(a, in, sizeof(a));
        }
        memcpy(salida + 8, r + 8, 8 * sizeof(s16));
        salida += 16;
        nbytes -= 32;
    }
}

static void entrelazado_a(u16 izquierda, u16 derecha)
{
    int cantidad = ARRIBA_RONDA_16(Rsp.nbytes) / (int) sizeof(s16) / 8;
    s16 *l = DMEM_S16(izquierda);
    s16 *r = DMEM_S16(derecha);
    s16 *d = DMEM_S16(Rsp.out);
    int i;

    /* De 8 en 8 */
    while (cantidad-- > 0) {
        s16 a[8], b[8];

        memcpy(a, l, sizeof(a));
        memcpy(b, r, sizeof(b));
        for (i = 0; i < 8; i++) {
            *d++ = a[i];
            *d++ = b[i];
        }
        l += 8;
        r += 8;
    }
}

static inline void *ptr(u32 direccion)
{
    return ASPMAIN_PTR(direccion);
}

#ifndef TROZO_MOVIMIENTO
#define TROZO_MOVIMIENTO 16
#endif
#ifndef TROZO_MOVE2
#define TROZO_MOVE2 32
#endif

/* Copia hacia adelante de a chunk bytes */
static void copiar_fwd_dmem(u32 dst, u32 orig_, u32 n, u32 trozo)
{
    u8 tmp[32];

    while (n > 0) {
        memcpy(tmp, DMEM_U8(orig_), trozo);
        memcpy(DMEM_U8(dst), tmp, trozo);
        orig_ += trozo;
        dst += trozo;
        n = n > trozo ? n - trozo : 0;
    }
}

/* Salida de un A_RESAMPLE que nadie lee */
typedef struct {
    u16 in, out, nbytes;
    u16 vol[2];
    s16 tasa[2];
    u16 humedo_vol;
    s16 humedo_tasa;
} EstadoAudioSimulado;

#define MAX_COMANDOS_ADELANTE 64

static inline int se_superponen(u32 a, u32 alen, u32 lo, u32 hi)
{
    return alen != 0 && a < hi && lo < a + alen;
}

static inline void tapar_zona(u32 a, u32 alen, u32 *lo, u32 *hi)
{
    if (a <= *lo && *lo < a + alen) {
        *lo = a + alen;
    }
    if (a < *hi && *hi <= a + alen) {
        *hi = a;
    }
}
