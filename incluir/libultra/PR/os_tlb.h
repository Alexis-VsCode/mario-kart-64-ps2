#ifndef _OS_TLB_H_
#define _OS_TLB_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/ultratypes.h>

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

typedef u32 OSPageMask;

#endif

#define OS_PM_4K 0x0000000
#define OS_PM_16K 0x0006000
#define OS_PM_64K 0x001e000
#define OS_PM_256K 0x007e000
#define OS_PM_1M 0x01fe000
#define OS_PM_4M 0x07fe000
#define OS_PM_16M 0x1ffe000

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

extern void osMapTLB(s32, OSPageMask, void*, u32, u32, s32);
extern void osMapTLBRdb(void);
extern void osUnmapTLB(s32);
extern void osUnmapTLBAll(void);
extern void osSetTLBASID(s32);

#endif

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif
