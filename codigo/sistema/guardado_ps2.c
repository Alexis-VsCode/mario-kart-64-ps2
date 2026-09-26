#include <string.h>

#include <ultra64.h>
#include <PR/os.h>

#include "sistema/sistema_ps2.h"
#include "sistema/guardado_ps2.h"

ImagenGuardadoPs2 guardado_ps2;
static int sucio;

void marcar_partida_modificada(void)
{
    sucio = 1;
    guardado_ps2.generacion++;
    pedir_guardado();
}

void marcar_partida_modificada_sin_aviso(void)
{
    sucio = 1;
}

int tomar_partida_modificada(void)
{
    int d = sucio;

    sucio = 0;
    return d;
}

s32 osEepromProbe(OSMesgQueue *mq)
{
    esperar_cargado_memcard_ps2();
    (void) mq;
    return EEPROM_TYPE_4K;
}

s32 osEepromRead(OSMesgQueue *mq, u8 direccion_2, u8 *buffer)
{
    esperar_cargado_memcard_ps2();
    (void) mq;
    if (direccion_2 >= EEPROM_MAXBLOCKS) {
        return -1;
    }
    memcpy(buffer, &guardado_ps2.eeprom[direccion_2 * EEPROM_BLOCK_SIZE], EEPROM_BLOCK_SIZE);
    return 0;
}

s32 osEepromWrite(OSMesgQueue *mq, u8 direccion_2, u8 *buffer)
{
    esperar_cargado_memcard_ps2();
    (void) mq;
    if (direccion_2 >= EEPROM_MAXBLOCKS) {
        return -1;
    }
    memcpy(&guardado_ps2.eeprom[direccion_2 * EEPROM_BLOCK_SIZE], buffer, EEPROM_BLOCK_SIZE);
    marcar_partida_modificada();
    return 0;
}

s32 osEepromLongRead(OSMesgQueue *mq, u8 direccion_2, u8 *buffer, int nbytes)
{
    esperar_cargado_memcard_ps2();
    (void) mq;
    if (direccion_2 >= EEPROM_MAXBLOCKS || direccion_2 * EEPROM_BLOCK_SIZE + nbytes > TAMANIO_EEPROM_PS2) {
        return -1;
    }
    memcpy(buffer, &guardado_ps2.eeprom[direccion_2 * EEPROM_BLOCK_SIZE], nbytes);
    return 0;
}

s32 osEepromLongWrite(OSMesgQueue *mq, u8 direccion_2, u8 *buffer, int nbytes)
{
    esperar_cargado_memcard_ps2();
    (void) mq;
    if (direccion_2 >= EEPROM_MAXBLOCKS || direccion_2 * EEPROM_BLOCK_SIZE + nbytes > TAMANIO_EEPROM_PS2) {
        return -1;
    }
    memcpy(&guardado_ps2.eeprom[direccion_2 * EEPROM_BLOCK_SIZE], buffer, nbytes);
    marcar_partida_modificada();
    return 0;
}

#define TAMANIO_PAGINA_PAK 256

static int pak_ok(OSPfs *pfs)
{
    return pfs != NULL && pfs->channel == 0 && (pfs->status & PFS_INITIALIZED);
}

static int paginas_usado(void)
{
    int i;
    int used = 0;

    for (i = 0; i < NOTAS_PAK_PS2; i++) {
        if (guardado_ps2.pak.notas[i].used) {
            used += guardado_ps2.pak.notas[i].paginas;
        }
    }
    return used;
}

s32 osPfsIsPlug(OSMesgQueue *mq, u8 *pattern)
{
    esperar_cargado_memcard_ps2();
    (void) mq;
    *pattern = 1; /* un pak en el mando 1 */
    return 0;
}

s32 osPfsInit(OSMesgQueue *mq, OSPfs *pfs, int canal)
{
    esperar_cargado_memcard_ps2();
    memset(pfs, 0, sizeof(OSPfs));
    pfs->queue = mq;
    pfs->channel = canal;
    if (canal != 0) {
        return PFS_ERR_NOPACK;
    }
    pfs->status = PFS_INITIALIZED;
    pfs->banks = 1;
    return 0;
}

s32 osPfsInitPak(OSMesgQueue *mq, OSPfs *pfs, int canal)
{
    return osPfsInit(mq, pfs, canal);
}

s32 osPfsChecker(OSPfs *pfs)
{
    return pak_ok(pfs) ? 0 : PFS_ERR_NOPACK;
}

s32 osPfsRepairId(OSPfs *pfs)
{
    return osPfsChecker(pfs);
}

static int coincidencia_nombres(const NotaPakPs2 *n, u16 empresa, u32 juego, const u8 *nombre, const u8 *ext)
{
    return n->used && n->empresa == empresa && n->juego == juego &&
           memcmp(n->name, nombre, PFS_FILE_NAME_LEN) == 0 && memcmp(n->ext, ext, PFS_FILE_EXT_LEN) == 0;
}

s32 osPfsFindFile(OSPfs *pfs, u16 empresa, u32 juego, u8 *nombre, u8 *ext, s32 *no_archivo)
{
    int i;

    if (!pak_ok(pfs)) {
        return PFS_ERR_NOPACK;
    }
    for (i = 0; i < NOTAS_PAK_PS2; i++) {
        if (coincidencia_nombres(&guardado_ps2.pak.notas[i], empresa, juego, nombre, ext)) {
            *no_archivo = i;
            return 0;
        }
    }
    return PFS_ERR_INVALID;
}

s32 osPfsAllocateFile(OSPfs *pfs, u16 empresa, u32 juego, u8 *nombre, u8 *ext, int nbytes, s32 *no_archivo)
{
    int i;
    int paginas = (nbytes + TAMANIO_PAGINA_PAK - 1) / TAMANIO_PAGINA_PAK;
    int desplazamiento = 0;

    if (!pak_ok(pfs)) {
        return PFS_ERR_NOPACK;
    }
    if (osPfsFindFile(pfs, empresa, juego, nombre, ext, no_archivo) == 0) {
        return PFS_ERR_EXIST;
    }
    if (paginas_usado() + paginas > PAGINAS_PAK_PS2) {
        return PFS_DATA_FULL;
    }
    /* Asignacion compacta: los datos de cada nota van seguidos. */
    for (i = 0; i < NOTAS_PAK_PS2; i++) {
        if (guardado_ps2.pak.notas[i].used) {
            int end = guardado_ps2.pak.notas[i].primer_pagina + guardado_ps2.pak.notas[i].paginas;

            if (end > desplazamiento) {
                desplazamiento = end;
            }
        }
    }
    if (desplazamiento + paginas > PAGINAS_PAK_PS2) {
        return PFS_DATA_FULL; /* fragmentado: el juego solo usa una nota */
    }
    for (i = 0; i < NOTAS_PAK_PS2; i++) {
        NotaPakPs2 *n = &guardado_ps2.pak.notas[i];

        if (!n->used) {
            memset(n, 0, sizeof(*n));
            n->used = 1;
            n->empresa = empresa;
            n->juego = juego;
            memcpy(n->name, nombre, PFS_FILE_NAME_LEN);
            memcpy(n->ext, ext, PFS_FILE_EXT_LEN);
            n->primer_pagina = desplazamiento;
            n->paginas = paginas;
            memset(&guardado_ps2.pak.data[desplazamiento * TAMANIO_PAGINA_PAK], 0, paginas * TAMANIO_PAGINA_PAK);
            *no_archivo = i;
            marcar_partida_modificada();
            return 0;
        }
    }
    return PFS_DIR_FULL;
}

s32 osPfsDeleteFile(OSPfs *pfs, u16 empresa, u32 juego, u8 *nombre, u8 *ext)
{
    s32 no_archivo;

    if (!pak_ok(pfs)) {
        return PFS_ERR_NOPACK;
    }
    if (osPfsFindFile(pfs, empresa, juego, nombre, ext, &no_archivo) != 0) {
        return PFS_ERR_INVALID;
    }
    guardado_ps2.pak.notas[no_archivo].used = 0;
    marcar_partida_modificada();
    return 0;
}

s32 osPfsReadWriteFile(OSPfs *pfs, s32 no_archivo, u8 bandera, int desplazamiento, int nbytes, u8 *buffer)
{
    NotaPakPs2 *n;
    u8 *datos;

    if (!pak_ok(pfs)) {
        return PFS_ERR_NOPACK;
    }
    if (no_archivo < 0 || no_archivo >= NOTAS_PAK_PS2 || !guardado_ps2.pak.notas[no_archivo].used) {
        return PFS_ERR_INVALID;
    }
    n = &guardado_ps2.pak.notas[no_archivo];
    if (desplazamiento < 0 || nbytes < 0 || desplazamiento + nbytes > n->paginas * TAMANIO_PAGINA_PAK) {
        return PFS_ERR_INVALID;
    }
    datos = &guardado_ps2.pak.data[n->primer_pagina * TAMANIO_PAGINA_PAK + desplazamiento];
    if (bandera == PFS_READ) {
        memcpy(buffer, datos, nbytes);
    } else {
        memcpy(datos, buffer, nbytes);
        marcar_partida_modificada();
    }
    return 0;
}

s32 osPfsFileState(OSPfs *pfs, s32 no_archivo, OSPfsState *estado)
{
    NotaPakPs2 *n;

    if (!pak_ok(pfs)) {
        return PFS_ERR_NOPACK;
    }
    if (no_archivo < 0 || no_archivo >= NOTAS_PAK_PS2 || !guardado_ps2.pak.notas[no_archivo].used) {
        return PFS_ERR_INVALID;
    }
    n = &guardado_ps2.pak.notas[no_archivo];
    memset(estado, 0, sizeof(*estado));
    estado->file_size = n->paginas * TAMANIO_PAGINA_PAK;
    estado->company_code = n->empresa;
    estado->game_code = n->juego;
    memcpy(estado->game_name, n->name, PFS_FILE_NAME_LEN);
    memcpy(estado->ext_name, n->ext, PFS_FILE_EXT_LEN);
    return 0;
}

s32 osPfsFreeBlocks(OSPfs *pfs, s32 *bytes_no_usado)
{
    if (!pak_ok(pfs)) {
        return PFS_ERR_NOPACK;
    }
    *bytes_no_usado = (PAGINAS_PAK_PS2 - paginas_usado()) * TAMANIO_PAGINA_PAK;
    return 0;
}

s32 osPfsNumFiles(OSPfs *pfs, s32 *archivos_max, s32 *archivos_usado)
{
    int i;
    int used = 0;

    if (!pak_ok(pfs)) {
        return PFS_ERR_NOPACK;
    }
    for (i = 0; i < NOTAS_PAK_PS2; i++) {
        used += guardado_ps2.pak.notas[i].used ? 1 : 0;
    }
    *archivos_max = NOTAS_PAK_PS2;
    *archivos_usado = used;
    return 0;
}
