#ifndef _OS_AI_H_
#define _OS_AI_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/ultratypes.h>

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

#endif

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

extern u32 osAiGetStatus(void);
extern u32 osAiGetLength(void);
extern s32 osAiSetFrequency(u32);
extern s32 osAiSetNextBuffer(void*, u32);

#endif

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif
