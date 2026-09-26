#ifndef SISTEMA_GUARDADO_PS2_H
#define SISTEMA_GUARDADO_PS2_H

#include <ultra64.h>

#define MAGICO_GUARDADO_PS2   0x344B4D53
#define VERSION_GUARDADO_PS2 1
#define TAMANIO_EEPROM_PS2  512
#define NOTAS_PAK_PS2    16
#define PAGINAS_PAK_PS2    123

typedef struct {
    u8 used;
    u8 pad;
    u16 empresa;
    u32 juego;
    u8 name[16];
    u8 ext[4];
    u16 primer_pagina;
    u16 paginas;
} NotaPakPs2;

typedef struct {
    NotaPakPs2 notas[NOTAS_PAK_PS2];
    u8 data[PAGINAS_PAK_PS2 * 256];
} Ps2Pak;

typedef struct {
    u32 magic;
    u32 version;
    u32 generacion;
    u32 checksum;
    u8 eeprom[TAMANIO_EEPROM_PS2];
    Ps2Pak pak;
} ImagenGuardadoPs2;

extern ImagenGuardadoPs2 guardado_ps2;

void marcar_partida_modificada(void);
void marcar_partida_modificada_sin_aviso(void);
int tomar_partida_modificada(void);

void inicializar_memory_card(void);
void cargar_partida(void);
void esperar_cargado_memcard_ps2(void);
int cargando_memcard_ps2(void);
void pedir_guardado(void);

#endif
