#ifndef _ULTRA64_OS_MISC_H_
#define _ULTRA64_OS_MISC_H_
#include <PR/ultratypes.h>

void osInitialize(void);
u32 osGetCount(void);

uintptr_t osVirtualToPhysical(void*);

#endif
