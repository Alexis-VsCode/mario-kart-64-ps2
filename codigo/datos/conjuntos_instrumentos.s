.include "macros.inc"

.section .data

glabel conjuntos_instrumento
.hword fijar_instrumento_00 - conjuntos_instrumento
.hword fijar_instrumento_01 - conjuntos_instrumento
.hword fijar_instrumento_02 - conjuntos_instrumento
.hword fijar_instrumento_03 - conjuntos_instrumento
.hword fijar_instrumento_04 - conjuntos_instrumento
.hword fijar_instrumento_05 - conjuntos_instrumento
.hword fijar_instrumento_06 - conjuntos_instrumento
.hword fijar_instrumento_07 - conjuntos_instrumento
.hword fijar_instrumento_08 - conjuntos_instrumento
.hword fijar_instrumento_09 - conjuntos_instrumento
.hword instrumento_conjunto_0A - conjuntos_instrumento
.hword instrumento_conjunto_0B - conjuntos_instrumento
.hword instrumento_conjunto_0C - conjuntos_instrumento
.hword instrumento_conjunto_0D - conjuntos_instrumento
.hword instrumento_conjunto_0E - conjuntos_instrumento
.hword instrumento_conjunto_0F - conjuntos_instrumento
.hword fijar_instrumento_10 - conjuntos_instrumento
.hword fijar_instrumento_11 - conjuntos_instrumento
.hword fijar_instrumento_12 - conjuntos_instrumento
.hword fijar_instrumento_13 - conjuntos_instrumento
.hword fijar_instrumento_14 - conjuntos_instrumento
.hword fijar_instrumento_15 - conjuntos_instrumento
.hword fijar_instrumento_16 - conjuntos_instrumento
.hword fijar_instrumento_17 - conjuntos_instrumento
.hword fijar_instrumento_18 - conjuntos_instrumento
.hword fijar_instrumento_19 - conjuntos_instrumento
.hword instrumento_conjunto_1A - conjuntos_instrumento
.hword instrumento_conjunto_1B - conjuntos_instrumento
.hword instrumento_conjunto_1C - conjuntos_instrumento
.hword instrumento_conjunto_1D - conjuntos_instrumento

fijar_instrumento_00:
.byte 0x01, 0x00
fijar_instrumento_01:
.byte 0x01, 0x01
fijar_instrumento_02:
.byte 0x01, 0x02
fijar_instrumento_03:
.byte 0x01, 0x03
fijar_instrumento_04:
.byte 0x01, 0x04
fijar_instrumento_05:
.byte 0x01, 0x05
fijar_instrumento_06:
.byte 0x01, 0x06
fijar_instrumento_07:
.byte 0x01, 0x07
fijar_instrumento_08:
.byte 0x01, 0x08
fijar_instrumento_09:
.byte 0x01, 0x09
instrumento_conjunto_0A:
.byte 0x01, 0x0A
instrumento_conjunto_0B:
.byte 0x01, 0x0B
instrumento_conjunto_0C:
.byte 0x01, 0x0B
instrumento_conjunto_0D:
.byte 0x01, 0x0B
instrumento_conjunto_0E:
.byte 0x01, 0x0B
instrumento_conjunto_0F:
.byte 0x01, 0x0B
fijar_instrumento_10:
.byte 0x01, 0x0C
fijar_instrumento_11:
.byte 0x01, 0x0E
fijar_instrumento_12:
.byte 0x01, 0x0F
fijar_instrumento_13:
.byte 0x01, 0x10
fijar_instrumento_14:
.byte 0x01, 0x0B
fijar_instrumento_15:
.byte 0x01, 0x11
fijar_instrumento_16:
.byte 0x01, 0x0B
fijar_instrumento_17:
.byte 0x01, 0x0D
fijar_instrumento_18:
.byte 0x01, 0x0C
fijar_instrumento_19:
.byte 0x01, 0x12
instrumento_conjunto_1A:
.byte 0x01, 0x13
instrumento_conjunto_1B:
.byte 0x01, 0x13
instrumento_conjunto_1C:
.byte 0x01, 0x14
instrumento_conjunto_1D:
.byte 0x01, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
fin_conjuntos_instrumento:
