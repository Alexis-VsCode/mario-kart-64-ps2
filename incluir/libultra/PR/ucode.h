#ifndef _ULTRA64_UCODE_H_
#define _ULTRA64_UCODE_H_

#define SP_DRAM_STACK_SIZE8 0x400
#define SP_UCODE_SIZE 0x1000
#define SP_UCODE_DATA_SIZE 0x800

extern u64 rspF3DBootStart[], rspF3DBootEnd[];

extern u64 gspF3DEXTextStart[], gspF3DEXTextEnd[];

extern u64 gspF3DLXTextStart[], gspF3DLXTextEnd[];

extern u64 gspF3DEXDataStart[], gspF3DEXDataEnd[];

extern u64 gspF3DLXDataStart[], gspF3DLXDataEnd[];

extern u64 rspAspMainStart[], rspAspMainEnd[];

extern u64 rspAspMainDataStart[], rspAspMainDataEnd[];

#endif
