#ifndef _PRINTF_H_
#define _PRINTF_H_
#include <stdarg.h>

typedef struct {
    union {
         s64 s64;
        u64 u64;
        f64 f64;
        u32 u32;
        u16 u16;
    } value;
     char* buff;
     s32 part1_len;
     s32 num_leading_zeros;
     s32 part2_len;
     s32 num_mid_zeros;
     s32 part3_len;
     s32 num_trailing_zeros;
     s32 precision;
     s32 width;
     u32 size;
     u32 flags;
     u8 length;
} printf_struct;

#define FLAGS_SPACE 1
#define FLAGS_PLUS 2
#define FLAGS_MINUS 4
#define FLAGS_HASH 8
#define FLAGS_ZERO 16
s32 _Printf(char* (*prout)(char*, const char*, size_t), char* dst, const char* fmt, va_list args);
void _Litob(printf_struct* args, u8 type);
void func_800D8890(printf_struct* args, u8 type);
void _Ldtob(printf_struct* args, u8 type);
#endif
