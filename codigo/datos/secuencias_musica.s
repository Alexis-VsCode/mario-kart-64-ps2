.include "macros.inc"

.section .data

glabel musica_secuencia_tabla_cabecera
.hword 3, ((musica_secuencia_tabla_fin - tabla_secuencia_musica) / 8) - 1
glabel tabla_secuencia_musica
.word (sec_00 - musica_secuencia_tabla_cabecera), (sec_00_fin - sec_00)
.word (sec_01 - musica_secuencia_tabla_cabecera), (sec_01_fin - sec_01)
.word (sec_02 - musica_secuencia_tabla_cabecera), (sec_02_fin - sec_02)
.word (sec_03 - musica_secuencia_tabla_cabecera), (sec_03_fin - sec_03)
.word (sec_04 - musica_secuencia_tabla_cabecera), (sec_04_fin - sec_04)
.word (sec_05 - musica_secuencia_tabla_cabecera), (sec_05_fin - sec_05)
.word (sec_06 - musica_secuencia_tabla_cabecera), (sec_06_fin - sec_06)
.word (sec_07 - musica_secuencia_tabla_cabecera), (sec_07_fin - sec_07)
.word (sec_08 - musica_secuencia_tabla_cabecera), (sec_08_fin - sec_08)
.word (sec_09 - musica_secuencia_tabla_cabecera), (sec_09_fin - sec_09)
.word (sec_0A - musica_secuencia_tabla_cabecera), (sec_0A_fin - sec_0A)
.word (sec_0B - musica_secuencia_tabla_cabecera), (sec_0B_fin - sec_0B)
.word (sec_0C - musica_secuencia_tabla_cabecera), (sec_0C_fin - sec_0C)
.word (sec_0D - musica_secuencia_tabla_cabecera), (sec_0D_fin - sec_0D)
.word (sec_0E - musica_secuencia_tabla_cabecera), (sec_0E_fin - sec_0E)
.word (sec_0F - musica_secuencia_tabla_cabecera), (sec_0F_fin - sec_0F)
.word (sec_10 - musica_secuencia_tabla_cabecera), (sec_10_fin - sec_10)
.word (sec_11 - musica_secuencia_tabla_cabecera), (sec_11_fin - sec_11)
.word (sec_12 - musica_secuencia_tabla_cabecera), (sec_12_fin - sec_12)
.word (sec_13 - musica_secuencia_tabla_cabecera), (sec_13_fin - sec_13)
.word (sec_14 - musica_secuencia_tabla_cabecera), (sec_14_fin - sec_14)
.word (sec_15 - musica_secuencia_tabla_cabecera), (sec_15_fin - sec_15)
.word (sec_16 - musica_secuencia_tabla_cabecera), (sec_16_fin - sec_16)
.word (sec_17 - musica_secuencia_tabla_cabecera), (sec_17_fin - sec_17)
.word (sec_18 - musica_secuencia_tabla_cabecera), (sec_18_fin - sec_18)
.word (sec_19 - musica_secuencia_tabla_cabecera), (sec_19_fin - sec_19)
.word (sec_1A - musica_secuencia_tabla_cabecera), (sec_1A_fin - sec_1A)
.word (sec_1B - musica_secuencia_tabla_cabecera), (sec_1B_fin - sec_1B)
.word (sec_1C - musica_secuencia_tabla_cabecera), (sec_1C_fin - sec_1C)
.word (sec_1D - musica_secuencia_tabla_cabecera), (sec_1D_fin - sec_1D)
glabel musica_secuencia_tabla_fin

.align 4, 0x00

glabel sec_00
.incbin "recursos/sonido/musica/00_efectos_sonido.m64"
glabel sec_00_fin

glabel sec_01
.incbin "recursos/sonido/musica/01_pantalla_titulo.m64"
glabel sec_01_fin

glabel sec_02
.incbin "recursos/sonido/musica/02_menu_principal.m64"
glabel sec_02_fin

glabel sec_03
.incbin "recursos/sonido/musica/03_pista_circuitos.m64"
glabel sec_03_fin

glabel sec_04
.incbin "recursos/sonido/musica/04_pista_granja.m64"
glabel sec_04_fin

glabel sec_05
.incbin "recursos/sonido/musica/05_pista_montana.m64"
glabel sec_05_fin

glabel sec_06
.incbin "recursos/sonido/musica/06_pista_playa.m64"
glabel sec_06_fin

glabel sec_07
.incbin "recursos/sonido/musica/07_pista_embrujada.m64"
glabel sec_07_fin

glabel sec_08
.incbin "recursos/sonido/musica/08_pista_nieve.m64"
glabel sec_08_fin

glabel sec_09
.incbin "recursos/sonido/musica/09_pista_castillo.m64"
glabel sec_09_fin

glabel sec_0A
.incbin "recursos/sonido/musica/10_pista_desierto.m64"
glabel sec_0A_fin

glabel sec_0B
.incbin "recursos/sonido/musica/11_largada.m64"
glabel sec_0B_fin

glabel sec_0C
.incbin "recursos/sonido/musica/12_ultima_vuelta.m64"
glabel sec_0C_fin

glabel sec_0D
.incbin "recursos/sonido/musica/13_llegada_primer_puesto.m64"
glabel sec_0D_fin

glabel sec_0E
.incbin "recursos/sonido/musica/14_llegada_puesto_medio.m64"
glabel sec_0E_fin

glabel sec_0F
.incbin "recursos/sonido/musica/15_llegada_perdiste.m64"
glabel sec_0F_fin

glabel sec_10
.incbin "recursos/sonido/musica/16_resultados_ganador.m64"
glabel sec_10_fin

glabel sec_11
.incbin "recursos/sonido/musica/17_estrella.m64"
glabel sec_11_fin

glabel sec_12
.incbin "recursos/sonido/musica/18_pista_rainbow_road.m64"
glabel sec_12_fin

glabel sec_13
.incbin "recursos/sonido/musica/19_pista_selva.m64"
glabel sec_13_fin

glabel sec_14
.incbin "recursos/sonido/musica/20_ceremonia_trofeo_perdiste.m64"
glabel sec_14_fin

glabel sec_15
.incbin "recursos/sonido/musica/21_pista_toads_turnpike.m64"
glabel sec_15_fin

glabel sec_16
.incbin "recursos/sonido/musica/22_largada_vs.m64"
glabel sec_16_fin

glabel sec_17
.incbin "recursos/sonido/musica/23_resultados_ganador_vs.m64"
glabel sec_17_fin

glabel sec_18
.incbin "recursos/sonido/musica/24_resultados_perdiste.m64"
glabel sec_18_fin

glabel sec_19
.incbin "recursos/sonido/musica/25_arena_batalla.m64"
glabel sec_19_fin

glabel sec_1A
.incbin "recursos/sonido/musica/26_ceremonia_presentacion.m64"
glabel sec_1A_fin

glabel sec_1B
.incbin "recursos/sonido/musica/27_ceremonia_ganador.m64"
glabel sec_1B_fin

glabel sec_1C
.incbin "recursos/sonido/musica/28_creditos.m64"
glabel sec_1C_fin

glabel sec_1D
.incbin "recursos/sonido/musica/29_ceremonia_perdiste.m64"
glabel sec_1D_fin
