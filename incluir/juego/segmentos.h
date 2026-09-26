#ifndef JUEGO_SEGMENTOS_H
#define JUEGO_SEGMENTOS_H

#include <ultra64.h>
#include <juego/macros.h>

extern u8 _memoryPoolSegmentNoloadStart[];
extern u8 _memoryPoolSegmentNoloadEnd[];

extern u8 _endingSegmentStart[];
extern u8 _endingSegmentRomStart[];
extern u8 _endingSegmentRomEnd[];
extern u8 _endingSegmentNoloadEnd[];

extern u8 _racingSegmentStart[];
extern u8 _racingSegmentNoloadEnd[];
extern u8 _racingSegmentRomStart[];
extern u8 _racingSegmentRomEnd[];

extern u8 _trigTablesSegmentStart[];
extern u8 _trigTablesSegmentSize[];
extern u8 _trigTablesSegmentRomStart[];

extern u8 _data_segment2SegmentRomStart[];
extern u8 _data_segment2SegmentRomEnd[];

extern u8 _common_texturesSegmentRomStart[];
extern u8 _common_texturesSegmentRomEnd[];

extern u8 _ceremonyDataSegmentRomStart[];
extern u8 _ceremonyDataSegmentRomEnd[];

extern u8 _startupLogoSegmentRomStart[];
extern u8 _startupLogoSegmentRomEnd[];

#define INICIO_SEG 0x80000000

#ifdef AVOID_UB

#define INICIO_POOL_MEMORIA (uintptr_t) &_memoryPoolSegmentNoloadStart[0]
#define FIN_POOL_MEMORIA (uintptr_t) &_memoryPoolSegmentNoloadEnd[0]

#define FINAL_SEG (uintptr_t) &_endingSegmentStart[0]
#define SEG_FINAL_ROM_INICIO (uintptr_t) &_endingSegmentRomStart[0]
#define TAMANIO_FINAL_SEG (size_t) ALIGN16((ptrdiff_t) (&_endingSegmentNoloadEnd[0] - &_endingSegmentStart[0]))
#define SEG_FINAL_ROM_TAMANIO (size_t) ALIGN16((ptrdiff_t) (&_endingSegmentRomEnd[0] - &_endingSegmentRomStart[0]))

#define CARRERA_SEG (uintptr_t) &_racingSegmentStart[0]
#define SEG_CARRERA_ROM_INICIO (uintptr_t) &_racingSegmentRomStart[0]
#define TAMANIO_CARRERA_SEG (size_t) ALIGN16((ptrdiff_t) (&_racingSegmentNoloadEnd[0] - &_racingSegmentStart[0]))
#define SEG_CARRERA_ROM_TAMANIO (size_t) ALIGN16((ptrdiff_t) (&_racingSegmentRomEnd[0] - &_racingSegmentRomStart[0]))

#define TABLAS_TRIG (uintptr_t) &_trigTablesSegmentStart[0]
#define TRIG_TABLAS_ROM_INICIO (uintptr_t) &_trigTablesSegmentRomStart[0]
#define TAMANIO_TABLAS_TRIG (size_t) _trigTablesSegmentSize

#define INICIO_DATOS_SEG (uintptr_t) &_data_segment2SegmentRomStart[0]
#define FIN_DATOS_SEG (uintptr_t) &_data_segment2SegmentRomEnd[0]

#define COMUN_TEXTURAS_ROM_INICIO (uintptr_t) &_common_texturesSegmentRomStart[0]
#define TAMANIO_TEXTURAS_COMUN (ptrdiff_t) (&_common_texturesSegmentRomEnd[0] - &_common_texturesSegmentRomStart[0])

#define CEREMONIA_DATOS_ROM_INICIO &_ceremonyDataSegmentRomStart[0]
#define CEREMONIA_DATOS_ROM_FIN &_ceremonyDataSegmentRomEnd[0]

#define INICIO_LOGO_ROM_INICIO &_startupLogoSegmentRomStart[0]
#define INICIO_LOGO_ROM_FIN &_startupLogoSegmentRomEnd[0]

#else

#define INICIO_POOL_MEMORIA (uintptr_t) &_memoryPoolSegmentNoloadStart
#define FIN_POOL_MEMORIA (uintptr_t) 0x80242F00

#define FINAL_SEG (uintptr_t) 0x80280000
#define SEG_FINAL_ROM_INICIO (u8*) &_endingSegmentRomStart[0]

#define TAMANIO_FINAL_SEG (size_t) 0xDF00
#define SEG_FINAL_ROM_TAMANIO (size_t) ALIGN16((ptrdiff_t) (&_endingSegmentRomEnd[0] - &_endingSegmentRomStart[0]))

#define CARRERA_SEG (uintptr_t) 0x8028DF00
#define SEG_CARRERA_ROM_INICIO (u8*) &_racingSegmentRomStart[0]
#define TAMANIO_CARRERA_SEG (size_t) 0x2C470

#define SEG_CARRERA_ROM_TAMANIO (size_t) ALIGN16((ptrdiff_t) (&_racingSegmentRomEnd[0] - &_racingSegmentRomStart[0]))

#define TABLAS_TRIG (uintptr_t) 0x802BA370
#define TRIG_TABLAS_ROM_INICIO (uintptr_t) &_trigTablesSegmentRomStart[0]
#define TAMANIO_TABLAS_TRIG (size_t) 0x5810

#define INICIO_DATOS_SEG (uintptr_t) &_data_segment2SegmentRomStart[0]
#define FIN_DATOS_SEG (uintptr_t) &_data_segment2SegmentRomEnd[0]

#define COMUN_TEXTURAS_ROM_INICIO (uintptr_t) &_common_texturesSegmentRomStart[0]
#define TAMANIO_TEXTURAS_COMUN \
    (ptrdiff_t) ((uintptr_t) &_common_texturesSegmentRomEnd - (uintptr_t) &_common_texturesSegmentRomStart)

#define CEREMONIA_DATOS_ROM_INICIO &_ceremonyDataSegmentRomStart[0]
#define CEREMONIA_DATOS_ROM_FIN &_ceremonyDataSegmentRomEnd[0]

#define INICIO_LOGO_ROM_INICIO &_startupLogoSegmentRomStart[0]
#define INICIO_LOGO_ROM_FIN &_startupLogoSegmentRomEnd[0]

#endif

#endif
