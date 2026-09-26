#ifndef _ABI_H_
#define _ABI_H_

#define A_SPNOOP 0
#define A_ADPCM 1
#define A_CLEARBUFF 2
#define A_RESAMPLE 5
#define A_SETBUFF 8
#define A_DMEMMOVE 10
#define A_LOADADPCM 11
#define A_MIXER 12
#define A_INTERLEAVE 13
#define A_SETLOOP 15

#if !(defined(VERSION_SH) || defined(VERSION_US) || defined(VERSION_EU))

#define A_ENVMIXER 3
#define A_LOADBUFF 4
#define A_RESAMPLE 5
#define A_SAVEBUFF 6
#define A_SEGMENT 7
#define A_SETVOL 9
#define A_POLEF 14

#else

#define A_ADDMIXER 4
#define A_RESAMPLE_ZOH 6
#define A_SEGMENT 7
#define A_DMEMMOVE2 16
#define A_DOWNSAMPLE_HALF 17
#define A_ENVSETUP1 18
#define A_ENVMIXER 19
#define A_LOADBUFF 20
#define A_SAVEBUFF 21
#define A_ENVSETUP2 22
#define A_S8DEC 23
#define A_HILOGAIN 24
#define A_UNK_25 25
#define A_DUPLICATE 26
#define A_FILTER 27

#endif

#define ACMD_SIZE 32

#define A_INIT 0x01
#define A_CONTINUE 0x00
#define A_LOOP 0x02
#define A_OUT 0x02
#define A_LEFT 0x02
#define A_RIGHT 0x00
#define A_VOL 0x04
#define A_RATE 0x00
#define A_AUX 0x08
#define A_NOAUX 0x00
#define A_MAIN 0x00
#define A_MIX 0x10

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

typedef struct {
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int gain : 16;
    unsigned int addr;
} Aadpcm;

typedef struct {
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int gain : 16;
    unsigned int addr;
} Apolef;

typedef struct {
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int pad1 : 16;
    unsigned int addr;
} Aenvelope;

typedef struct {
    unsigned int cmd : 8;
    unsigned int pad1 : 8;
    unsigned int dmem : 16;
    unsigned int pad2 : 16;
    unsigned int count : 16;
} Aclearbuff;

typedef struct {
    unsigned int cmd : 8;
    unsigned int pad1 : 8;
    unsigned int pad2 : 16;
    unsigned int inL : 16;
    unsigned int inR : 16;
} Ainterleave;

typedef struct {
    unsigned int cmd : 8;
    unsigned int pad1 : 24;
    unsigned int addr;
} Aloadbuff;

typedef struct {
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int pad1 : 16;
    unsigned int addr;
} Aenvmixer;

typedef struct {
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int gain : 16;
    unsigned int dmemi : 16;
    unsigned int dmemo : 16;
} Amixer;

typedef struct {
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int dmem2 : 16;
    unsigned int addr;
} Apan;

typedef struct {
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int pitch : 16;
    unsigned int addr;
} Aresample;

typedef struct {
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int pad1 : 16;
    unsigned int addr;
} Areverb;

typedef struct {
    unsigned int cmd : 8;
    unsigned int pad1 : 24;
    unsigned int addr;
} Asavebuff;

typedef struct {
    unsigned int cmd : 8;
    unsigned int pad1 : 24;
    unsigned int pad2 : 2;
    unsigned int number : 4;
    unsigned int base : 24;
} Asegment;

typedef struct {
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int dmemin : 16;
    unsigned int dmemout : 16;
    unsigned int count : 16;
} Asetbuff;

typedef struct {
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int vol : 16;
    unsigned int voltgt : 16;
    unsigned int volrate : 16;
} Asetvol;

typedef struct {
    unsigned int cmd : 8;
    unsigned int pad1 : 8;
    unsigned int dmemin : 16;
    unsigned int dmemout : 16;
    unsigned int count : 16;
} Admemmove;

typedef struct {
    unsigned int cmd : 8;
    unsigned int pad1 : 8;
    unsigned int count : 16;
    unsigned int addr;
} Aloadadpcm;

typedef struct {
    unsigned int cmd : 8;
    unsigned int pad1 : 8;
    unsigned int pad2 : 16;
    unsigned int addr;
} Asetloop;

typedef struct {
    uintptr_t w0;
    uintptr_t w1;
} Awords;

typedef union {
    Awords words;
#if ENDIAN_GRANDE_ES && !IS_64_BIT
    Aadpcm adpcm;
    Apolef polef;
    Aclearbuff clearbuff;
    Aenvelope envelope;
    Ainterleave interleave;
    Aloadbuff loadbuff;
    Aenvmixer envmixer;
    Aresample resample;
    Areverb reverb;
    Asavebuff savebuff;
    Asegment segment;
    Asetbuff setbuff;
    Asetvol setvol;
    Admemmove dmemmove;
    Aloadadpcm loadadpcm;
    Amixer mixer;
    Asetloop setloop;
#endif
    long long int force_union_align;
} Acmd;

typedef short ADPCM_STATE[16];

/* Pole filter state */
typedef short POLEF_STATE[4];

/* Resampler state */
typedef short RESAMPLE_STATE[16];

/* Resampler constants */
#define UNITY_PITCH 0x8000
#define MAX_RATIO 1.99996

/* Enveloper/Mixer state */
typedef short ENVMIX_STATE[40];

#define aADPCMdec(pkt, f, s)                                        \
    {                                                               \
        Acmd* _a = (Acmd*) pkt;                                     \
                                                                    \
        _a->words.w0 = _SHIFTL(A_ADPCM, 24, 8) | _SHIFTL(f, 16, 8); \
        _a->words.w1 = (uintptr_t) (s);                             \
    }

#define aPoleFilter(pkt, f, g, s)                                                         \
    {                                                                                     \
        Acmd* _a = (Acmd*) pkt;                                                           \
                                                                                          \
        _a->words.w0 = (_SHIFTL(A_POLEF, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(g, 0, 16)); \
        _a->words.w1 = (uintptr_t) (s);                                                   \
    }

#define aClearBuffer(pkt, d, c)                                         \
    {                                                                   \
        Acmd* _a = (Acmd*) pkt;                                         \
                                                                        \
        _a->words.w0 = _SHIFTL(A_CLEARBUFF, 24, 8) | _SHIFTL(d, 0, 24); \
        _a->words.w1 = (uintptr_t) (c);                                 \
    }

#define aEnvMixer(pkt, f, s)                                           \
    {                                                                  \
        Acmd* _a = (Acmd*) pkt;                                        \
                                                                       \
        _a->words.w0 = _SHIFTL(A_ENVMIXER, 24, 8) | _SHIFTL(f, 16, 8); \
        _a->words.w1 = (uintptr_t) (s);                                \
    }

#define aInterleave(pkt, l, r)                                 \
    {                                                          \
        Acmd* _a = (Acmd*) pkt;                                \
                                                               \
        _a->words.w0 = _SHIFTL(A_INTERLEAVE, 24, 8);           \
        _a->words.w1 = _SHIFTL(l, 16, 16) | _SHIFTL(r, 0, 16); \
    }

#define aLoadBuffer(pkt, s)                        \
    {                                              \
        Acmd* _a = (Acmd*) pkt;                    \
                                                   \
        _a->words.w0 = _SHIFTL(A_LOADBUFF, 24, 8); \
        _a->words.w1 = (uintptr_t) (s);            \
    }

#define aMix(pkt, f, g, i, o)                                                             \
    {                                                                                     \
        Acmd* _a = (Acmd*) pkt;                                                           \
                                                                                          \
        _a->words.w0 = (_SHIFTL(A_MIXER, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(g, 0, 16)); \
        _a->words.w1 = _SHIFTL(i, 16, 16) | _SHIFTL(o, 0, 16);                            \
    }

#define aPan(pkt, f, d, s)                                                              \
    {                                                                                   \
        Acmd* _a = (Acmd*) pkt;                                                         \
                                                                                        \
        _a->words.w0 = (_SHIFTL(A_PAN, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(d, 0, 16)); \
        _a->words.w1 = (uintptr_t) (s);                                                 \
    }

#define aResample(pkt, f, p, s)                                                              \
    {                                                                                        \
        Acmd* _a = (Acmd*) pkt;                                                              \
                                                                                             \
        _a->words.w0 = (_SHIFTL(A_RESAMPLE, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(p, 0, 16)); \
        _a->words.w1 = (uintptr_t) (s);                                                      \
    }

#define aSaveBuffer(pkt, s)                        \
    {                                              \
        Acmd* _a = (Acmd*) pkt;                    \
                                                   \
        _a->words.w0 = _SHIFTL(A_SAVEBUFF, 24, 8); \
        _a->words.w1 = (uintptr_t) (s);            \
    }

#define aSegment(pkt, s, b)                                   \
    {                                                         \
        Acmd* _a = (Acmd*) pkt;                               \
                                                              \
        _a->words.w0 = _SHIFTL(A_SEGMENT, 24, 8);             \
        _a->words.w1 = _SHIFTL(s, 24, 8) | _SHIFTL(b, 0, 24); \
    }

#define aSetBuffer(pkt, f, i, o, c)                                                         \
    {                                                                                       \
        Acmd* _a = (Acmd*) pkt;                                                             \
                                                                                            \
        _a->words.w0 = (_SHIFTL(A_SETBUFF, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(i, 0, 16)); \
        _a->words.w1 = _SHIFTL(o, 16, 16) | _SHIFTL(c, 0, 16);                              \
    }

#define aSetVolume(pkt, f, v, t, r)                                                         \
    {                                                                                       \
        Acmd* _a = (Acmd*) pkt;                                                             \
                                                                                            \
        _a->words.w0 = (_SHIFTL(A_SETVOL, 24, 8) | _SHIFTL(f, 16, 16) | _SHIFTL(v, 0, 16)); \
        _a->words.w1 = _SHIFTL(t, 16, 16) | _SHIFTL(r, 0, 16);                              \
    }

#define aSetLoop(pkt, a)                          \
    {                                             \
        Acmd* _a = (Acmd*) pkt;                   \
        _a->words.w0 = _SHIFTL(A_SETLOOP, 24, 8); \
        _a->words.w1 = (uintptr_t) (a);           \
    }

#define aDMEMMove(pkt, i, o, c)                                        \
    {                                                                  \
        Acmd* _a = (Acmd*) pkt;                                        \
                                                                       \
        _a->words.w0 = _SHIFTL(A_DMEMMOVE, 24, 8) | _SHIFTL(i, 0, 24); \
        _a->words.w1 = _SHIFTL(o, 16, 16) | _SHIFTL(c, 0, 16);         \
    }

#define aLoadADPCM(pkt, c, d)                                           \
    {                                                                   \
        Acmd* _a = (Acmd*) pkt;                                         \
                                                                        \
        _a->words.w0 = _SHIFTL(A_LOADADPCM, 24, 8) | _SHIFTL(c, 0, 24); \
        _a->words.w1 = (uintptr_t) (d);                                 \
    }

#define aSetVolume32(pkt, f, v, tr)                                                         \
    {                                                                                       \
        Acmd* _a = (Acmd*) pkt;                                                             \
                                                                                            \
        _a->words.w0 = (_SHIFTL(A_SETVOL, 24, 8) | _SHIFTL(f, 16, 16) | _SHIFTL(v, 0, 16)); \
        _a->words.w1 = (uintptr_t) (tr);                                                    \
    }

#if defined(VERSION_SH) || defined(VERSION_US) || defined(VERSION_EU)
#undef aLoadBuffer
#undef aSaveBuffer
#undef aMix
#undef aEnvMixer

#define aS8Dec(pkt, f, s)                                           \
    {                                                               \
        Acmd* _a = (Acmd*) pkt;                                     \
                                                                    \
        _a->words.w0 = _SHIFTL(A_S8DEC, 24, 8) | _SHIFTL(f, 16, 8); \
        _a->words.w1 = (uintptr_t) (s);                             \
    }

#define aAddMixer(pkt, s, d, c)                                                                          \
    {                                                                                                    \
        Acmd* _a = (Acmd*) pkt;                                                                          \
                                                                                                         \
        _a->words.w0 = (_SHIFTL(A_ADDMIXER, 24, 8) | _SHIFTL((c) >> 4, 16, 8) | _SHIFTL(0x7fff, 0, 16)); \
        _a->words.w1 = (_SHIFTL(s, 16, 16) | _SHIFTL(d, 0, 16));                                         \
    }

#define aLoadBuffer(pkt, s, d, c)                                                                 \
    {                                                                                             \
        Acmd* _a = (Acmd*) pkt;                                                                   \
                                                                                                  \
        _a->words.w0 = _SHIFTL(A_LOADBUFF, 24, 8) | _SHIFTL((c) >> 4, 16, 8) | _SHIFTL(d, 0, 16); \
        _a->words.w1 = (uintptr_t) (s);                                                           \
    }

#define aSaveBuffer(pkt, s, d, c)                                                                 \
    {                                                                                             \
        Acmd* _a = (Acmd*) pkt;                                                                   \
                                                                                                  \
        _a->words.w0 = _SHIFTL(A_SAVEBUFF, 24, 8) | _SHIFTL((c) >> 4, 16, 8) | _SHIFTL(s, 0, 16); \
        _a->words.w1 = (uintptr_t) (d);                                                           \
    }

#define aDuplicate(pkt, s, d, c)                                                              \
    {                                                                                         \
        Acmd* _a = (Acmd*) pkt;                                                               \
                                                                                              \
        _a->words.w0 = (_SHIFTL(A_DUPLICATE, 24, 8) | _SHIFTL(c, 16, 8) | _SHIFTL(s, 0, 16)); \
        _a->words.w1 = (_SHIFTL(d, 16, 16) | _SHIFTL(0x80, 0, 16));                           \
    }

#define aDMEMMove2(pkt, t, i, o, c)                                                         \
    {                                                                                       \
        Acmd* _a = (Acmd*) pkt;                                                             \
                                                                                            \
        _a->words.w0 = _SHIFTL(A_DMEMMOVE2, 24, 8) | _SHIFTL(t, 16, 8) | _SHIFTL(i, 0, 16); \
        _a->words.w1 = _SHIFTL(o, 16, 16) | _SHIFTL(c, 0, 16);                              \
    }

#define aResampleZoh(pkt, pitch, startFract)                                     \
    {                                                                            \
        Acmd* _a = (Acmd*) pkt;                                                  \
                                                                                 \
        _a->words.w0 = (_SHIFTL(A_RESAMPLE_ZOH, 24, 8) | _SHIFTL(pitch, 0, 16)); \
        _a->words.w1 = _SHIFTL(startFract, 0, 16);                               \
    }

#define aDownsampleHalf(pkt, nSamples, i, o)                                           \
    {                                                                                  \
        Acmd* _a = (Acmd*) pkt;                                                        \
                                                                                       \
        _a->words.w0 = (_SHIFTL(A_DOWNSAMPLE_HALF, 24, 8) | _SHIFTL(nSamples, 0, 16)); \
        _a->words.w1 = _SHIFTL(i, 16, 16) | _SHIFTL(o, 0, 16);                         \
    }

#define aMix(pkt, g, i, o, c)                                                                    \
    {                                                                                            \
        Acmd* _a = (Acmd*) pkt;                                                                  \
                                                                                                 \
        _a->words.w0 = (_SHIFTL(A_MIXER, 24, 8) | _SHIFTL((c) >> 4, 16, 8) | _SHIFTL(g, 0, 16)); \
        _a->words.w1 = _SHIFTL(i, 16, 16) | _SHIFTL(o, 0, 16);                                   \
    }

#define aEnvSetup1Alt(pkt,initialVolReverb,rampReverbL,rampReverbR,rampLeft,rampRight) { Acmd *_a = (Acmd *)pkt; _a->words.w0 = (_SHIFTL(A_ENVSETUP1, 24, 8) | _SHIFTL(initialVolReverb, 16, 8) | (_SHIFTL(rampReverbL, 8, 8)) | _SHIFTL(rampReverbR, 0, 8)); _a->words.w1 = _SHIFTL(rampLeft, 16, 16) | _SHIFTL(rampRight, 0, 16); }

#define aEnvSetup1(pkt, initialVolReverb, rampReverb, rampLeft, rampRight)                                            \
    {                                                                                                                 \
        Acmd* _a = (Acmd*) pkt;                                                                                       \
                                                                                                                      \
        _a->words.w0 = (_SHIFTL(A_ENVSETUP1, 24, 8) | _SHIFTL(initialVolReverb, 16, 8) | _SHIFTL(rampReverb, 0, 16)); \
        _a->words.w1 = _SHIFTL(rampLeft, 16, 16) | _SHIFTL(rampRight, 0, 16);                                         \
    }

#define aEnvSetup2(pkt, initialVolLeft, initialVolRight)                                  \
    {                                                                                     \
        Acmd* _a = (Acmd*) pkt;                                                           \
                                                                                          \
        _a->words.w0 = _SHIFTL(A_ENVSETUP2, 24, 8);                                       \
        _a->words.w1 = _SHIFTL(initialVolLeft, 16, 16) | _SHIFTL(initialVolRight, 0, 16); \
    }

#define aEnvMixer(pkt, inBuf, nSamples, swapReverb, negLeft, negRight, dryLeft, dryRight, wetLeft, wetRight)   \
    {                                                                                                          \
        Acmd* _a = (Acmd*) pkt;                                                                                \
                                                                                                               \
        _a->words.w0 = (_SHIFTL(A_ENVMIXER, 24, 8) | _SHIFTL((inBuf) >> 4, 16, 8) | _SHIFTL(nSamples, 8, 8)) | \
                       _SHIFTL(swapReverb, 2, 1) | _SHIFTL(negLeft, 1, 1) | _SHIFTL(negRight, 0, 1);           \
        _a->words.w1 = _SHIFTL((dryLeft) >> 4, 24, 8) | _SHIFTL((dryRight) >> 4, 16, 8) |                      \
                       _SHIFTL((wetLeft) >> 4, 8, 8) | _SHIFTL((wetRight) >> 4, 0, 8);                         \
    }

#define aFilter(pkt, f, countOrBuf, addr)                                                             \
    {                                                                                                 \
        Acmd* _a = (Acmd*) pkt;                                                                       \
                                                                                                      \
        _a->words.w0 = _SHIFTL(A_FILTER, 24, 8) | _SHIFTL((f), 16, 8) | _SHIFTL((countOrBuf), 0, 16); \
        _a->words.w1 = (uintptr_t) (addr);                                                            \
    }

#define aHiLoGain(pkt, g, buflen, i)                                                                \
    {                                                                                               \
        Acmd* _a = (Acmd*) pkt;                                                                     \
                                                                                                    \
        _a->words.w0 = _SHIFTL(A_HILOGAIN, 24, 8) | _SHIFTL((g), 16, 8) | _SHIFTL((buflen), 0, 16); \
        _a->words.w1 = _SHIFTL((i), 16, 16);                                                        \
    }

#define aUnknown25(pkt, f, c, o, i)                                                            \
    {                                                                                          \
        Acmd* _a = (Acmd*) pkt;                                                                \
                                                                                               \
        _a->words.w0 = (_SHIFTL(A_UNK_25, 24, 8) | _SHIFTL((f), 16, 8) | _SHIFTL((c), 0, 16)); \
        _a->words.w1 = _SHIFTL((o), 16, 16) | _SHIFTL((i), 0, 16);                             \
    }

#endif

#endif

#endif
