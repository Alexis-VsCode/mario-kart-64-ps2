#ifndef _OS_EEPROM_H_
#define _OS_EEPROM_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/ultratypes.h>
#include "os_message.h"

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

#endif

#define EEPROM_TYPE_4K 0x01
#define EEPROM_TYPE_16K 0x02

#define EEPROM_MAXBLOCKS 64
#define EEP16K_MAXBLOCKS 256
#define EEPROM_BLOCK_SIZE 8

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

extern s32 osEepromProbe(OSMesgQueue*);
extern s32 osEepromRead(OSMesgQueue*, u8, u8*);
extern s32 osEepromWrite(OSMesgQueue*, u8, u8*);
extern s32 osEepromLongRead(OSMesgQueue*, u8, u8*, int);
extern s32 osEepromLongWrite(OSMesgQueue*, u8, u8*, int);

#endif

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif
