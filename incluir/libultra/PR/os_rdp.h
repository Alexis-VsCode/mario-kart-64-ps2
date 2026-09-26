#ifndef _OS_RDP_H_
#define _OS_RDP_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/ultratypes.h>

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

#endif

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

extern u32 osDpGetStatus(void);
extern void osDpSetStatus(u32);
extern void osDpGetCounters(u32*);
extern s32 osDpSetNextBuffer(void*, u64);

#endif

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif
