#include "os/libultra_internal.h"
#include <string.h>

#ifdef TARGET_PS2
typedef unsigned int Ps2Qword __attribute__((mode(TI), may_alias));
typedef u64 Ps2Dword __attribute__((may_alias));
typedef struct {
    u64 v;
} __attribute__((packed, may_alias)) Ps2DwordUnaligned;

__attribute__((optimize("no-tree-loop-distribute-patterns"))) void* memcpy(void* dst, const void* src, size_t size) {
    u8* d = dst;
    const u8* s = src;

    if (size >= 32) {
        u32 diff = (u32) d ^ (u32) s;

        if ((diff & 15) == 0) {
            while ((u32) d & 15) {
                *d++ = *s++;
                size--;
            }
            for (; size >= 64; size -= 64, d += 64, s += 64) {
                Ps2Qword a = ((const Ps2Qword*) s)[0];
                Ps2Qword b = ((const Ps2Qword*) s)[1];
                Ps2Qword c = ((const Ps2Qword*) s)[2];
                Ps2Qword e = ((const Ps2Qword*) s)[3];

                ((Ps2Qword*) d)[0] = a;
                ((Ps2Qword*) d)[1] = b;
                ((Ps2Qword*) d)[2] = c;
                ((Ps2Qword*) d)[3] = e;
            }
            for (; size >= 16; size -= 16, d += 16, s += 16) {
                *(Ps2Qword*) d = *(const Ps2Qword*) s;
            }
        } else {
            while ((u32) d & 7) {
                *d++ = *s++;
                size--;
            }
            if ((diff & 7) == 0) {
                for (; size >= 32; size -= 32, d += 32, s += 32) {
                    Ps2Dword a = ((const Ps2Dword*) s)[0];
                    Ps2Dword b = ((const Ps2Dword*) s)[1];
                    Ps2Dword c = ((const Ps2Dword*) s)[2];
                    Ps2Dword e = ((const Ps2Dword*) s)[3];

                    ((Ps2Dword*) d)[0] = a;
                    ((Ps2Dword*) d)[1] = b;
                    ((Ps2Dword*) d)[2] = c;
                    ((Ps2Dword*) d)[3] = e;
                }
            } else {
                for (; size >= 16; size -= 16, d += 16, s += 16) {
                    Ps2Dword a = ((const Ps2DwordUnaligned*) s)[0].v;
                    Ps2Dword b = ((const Ps2DwordUnaligned*) s)[1].v;

                    ((Ps2Dword*) d)[0] = a;
                    ((Ps2Dword*) d)[1] = b;
                }
            }
            for (; size >= 8; size -= 8, d += 8, s += 8) {
                *(Ps2Dword*) d = ((const Ps2DwordUnaligned*) s)->v;
            }
        }
    }
    while (size > 0) {
        *d++ = *s++;
        size--;
    }
    return dst;
}
#else
void* memcpy(void* dst, const void* src, size_t size) {
    u8* _dst = dst;
    const u8* _src = src;
    while (size > 0) {
        *_dst++ = *_src++;
        size--;
    }
    return dst;
}
#endif

size_t strlen(const char* str) {
    const u8* ptr = (const u8*) str;
    while (*ptr) {
        ptr++;
    }
    return (const char*) ptr - str;
}

char* strchr(const char* str, s32 ch) {
    u8 c = ch;
    while (*(u8*) str != c) {
        if (*(u8*) str == 0) {
            return NULL;
        }
        str++;
    }
    return (char*) str;
}
