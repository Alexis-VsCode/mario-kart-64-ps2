#ifndef _OS_CACHE_H_
#define _OS_CACHE_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/ultratypes.h>

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

#endif

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

#define OS_DCACHE_ROUNDUP_ADDR(x) (void*) (((((u32) (x) + 0xf) / 0x10) * 0x10))
#define OS_DCACHE_ROUNDUP_SIZE(x) (u32)(((((u32) (x) + 0xf) / 0x10) * 0x10))

extern void osInvalDCache(void*, size_t);
extern void osInvalICache(void*, size_t);
extern void osWritebackDCache(void*, size_t);
extern void osWritebackDCacheAll(void);

#endif

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif
