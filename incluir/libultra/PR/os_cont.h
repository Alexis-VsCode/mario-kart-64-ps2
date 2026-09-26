#ifndef _OS_CONT_H_
#define _OS_CONT_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/ultratypes.h>
#include "os_message.h"

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

typedef struct {
    u16 type;  /* Controller Type */
    u8 status; /* Controller status */
    u8 errnum;
} OSContStatus;

typedef struct {
    u16 button;
    s8 stick_x;
    s8 stick_y;
    u8 errno;
} OSContPad;

typedef struct {
    void* address;
    u8 databuffer[32];
    u8 addressCrc;
    u8 dataCrc;
    u8 errno;
} OSContRamIo;

#endif

/* Controllers  number */

#ifndef _HW_VERSION_1
#define MAXCONTROLLERS 4
#else
#define MAXCONTROLLERS 6
#endif

/* controller errors */
#define CONT_NO_RESPONSE_ERROR 0x8
#define CONT_OVERRUN_ERROR 0x4
#ifdef _HW_VERSION_1
#define CONT_FRAME_ERROR 0x2
#define CONT_COLLISION_ERROR 0x1
#endif

/* Controller type */

#define CONT_ABSOLUTE 0x0001
#define CONT_RELATIVE 0x0002
#define CONT_JOYPORT 0x0004
#define CONT_EEPROM 0x8000
#define CONT_EEP16K 0x4000
#define CONT_TYPE_MASK 0x1f07
#define CONT_TYPE_NORMAL 0x0005
#define CONT_TYPE_MOUSE 0x0002
#define CONT_TYPE_VOICE 0x0100

/* Controller status */

#define CONT_CARD_ON 0x01
#define CONT_CARD_PULL 0x02
#define CONT_ADDR_CRC_ER 0x04
#define CONT_EEPROM_BUSY 0x80

#define CONT_A 0x8000
#define CONT_B 0x4000
#define CONT_G 0x2000
#define CONT_START 0x1000
#define CONT_UP 0x0800
#define CONT_DOWN 0x0400
#define CONT_LEFT 0x0200
#define CONT_RIGHT 0x0100
#define CONT_L 0x0020
#define CONT_R 0x0010
#define CONT_E 0x0008
#define CONT_D 0x0004
#define CONT_C 0x0002
#define CONT_F 0x0001

#define A_BUTTON CONT_A
#define B_BUTTON CONT_B
#define L_TRIG CONT_L
#define R_TRIG CONT_R
#define Z_TRIG CONT_G
#define START_BUTTON CONT_START
#define U_JPAD CONT_UP
#define L_JPAD CONT_LEFT
#define R_JPAD CONT_RIGHT
#define D_JPAD CONT_DOWN
#define U_CBUTTONS CONT_E
#define L_CBUTTONS CONT_C
#define R_CBUTTONS CONT_F
#define D_CBUTTONS CONT_D

/* Controller error number */

#define CONT_ERR_NO_CONTROLLER PFS_ERR_NOPACK
#define CONT_ERR_CONTRFAIL CONT_OVERRUN_ERROR
#define CONT_ERR_INVALID PFS_ERR_INVALID
#define CONT_ERR_DEVICE PFS_ERR_DEVICE
#define CONT_ERR_NOT_READY 12
#define CONT_ERR_VOICE_MEMORY 13
#define CONT_ERR_VOICE_WORD 14
#define CONT_ERR_VOICE_NO_RESPONSE 15

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

/* Controller interface */

extern s32 osContInit(OSMesgQueue*, u8*, OSContStatus*);
extern s32 osContReset(OSMesgQueue*, OSContStatus*);
extern s32 osContStartQuery(OSMesgQueue*);
extern s32 osContStartReadData(OSMesgQueue*);
#ifndef _HW_VERSION_1
extern s32 osContSetCh(u8);
#endif
extern void osContGetQuery(OSContStatus*);
extern void osContGetReadData(OSContPad*);

#endif

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif
