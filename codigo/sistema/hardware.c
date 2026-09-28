#include <kernel.h>
#include <string.h>
#include <timer.h>

#include <ultra64.h>
#include <PR/os.h>

#include "graficos/memoria_texturas.h"
#include "sistema/sistema_ps2.h"

u32 osTvType = OS_TV_NTSC;
s32 osRomType = 0;
u32 osRomBase = 0;
u32 osResetType = 0;
s32 osCicId = 6102;
s32 osVersion = 0;
u32 osMemSize = 0x800000; /* 8 MB con el Expansion Pak (lo que espera MK64) */
s32 osAppNmiBuffer[16];
u64 osClockRate = 62500000;

u64 tiempo_actual(void)
{
    u64 omnibus = GetTimerSystemTime();

    return (omnibus / 147456) * 46875 + ((omnibus % 147456) * 46875) / 147456;
}

static u64 desplazamiento_tiempo;

OSTime osGetTime(void)
{
    return tiempo_actual() - desplazamiento_tiempo;
}

void osSetTime(OSTime time)
{
    desplazamiento_tiempo = tiempo_actual() - time;
}

u32 osGetCount(void)
{
    return (u32) tiempo_actual();
}

void osInvalDCache(void *vaddr, size_t nbytes)
{
    (void) vaddr;
    (void) nbytes;
}

void osInvalICache(void *vaddr, size_t nbytes)
{
    (void) vaddr;
    (void) nbytes;
}

void osWritebackDCache(void *vaddr, size_t nbytes)
{
    (void) vaddr;
    (void) nbytes;
}

void osWritebackDCacheAll(void)
{
}

u32 osVirtualToPhysical(void *direccion)
{
    return (u32) (uintptr_t) direccion & 0x1FFFFFFF;
}

void *osPhysicalToVirtual(u32 direccion)
{
    return (void *) (uintptr_t) direccion;
}

void osInitialize(void)
{
}

void inicializar_hardware_libultra(void)
{
    desplazamiento_tiempo = tiempo_actual();
}

static OSMesgQueue *cola_cmd_pi;

void osCreatePiManager(OSPri prio, OSMesgQueue *cmd_q, OSMesg *cmd_buf, s32 cnt_mens_cmd)
{
    (void) prio;
    osCreateMesgQueue(cmd_q, cmd_buf, cnt_mens_cmd);
    cola_cmd_pi = cmd_q;
}

OSMesgQueue *osPiGetCmdQueue(void)
{
    return cola_cmd_pi;
}

static void comprobar_rango_rom(uintptr_t direccion_dev, size_t size, void *llamador)
{
    uintptr_t lo = (uintptr_t) __rom_start;
    uintptr_t hi = (uintptr_t) __rom_end;

    if (direccion_dev >= lo && direccion_dev + size <= hi + 0x10000) {
        return;
    }
    if (direccion_dev >= 0x00100000 && direccion_dev + size <= (uintptr_t) __rom_start) {
        return;
    }
    registrar("PI DMA fuera de la ROM: %08x +%x (llamado desde %p)", (unsigned) direccion_dev, (unsigned) size, llamador);
    detener_por_error("osPiStartDma: dirección de cartucho inválida");
}

s32 osPiStartDma(OSIoMesg *mb, s32 prioridad, s32 sentido, uintptr_t direccion_dev, void *direccion_v, size_t nbytes,
                 OSMesgQueue *mq)
{
    (void) prioridad;

    if (sentido == OS_READ) {
#ifdef SMK64_DEV
        {
            void rango_vigilancia_ps2(const void *dst, u32 size, void *llamador);

            rango_vigilancia_ps2(direccion_v, nbytes, __builtin_return_address(0));
        }
#endif
        comprobar_rango_rom(direccion_dev, nbytes, __builtin_return_address(0));
        esperar_rom_ps2((const void *) direccion_dev, nbytes);
        if ((void *) direccion_dev != direccion_v) {
            escribir_ram_tmem_ps2(direccion_v, nbytes); /* antes y despues: memoria_texturas.h */
            memmove(direccion_v, (const void *) direccion_dev, nbytes);
            escribir_ram_tmem_ps2(direccion_v, nbytes);
        }
    }

    if (mb != NULL) {
        mb->hdr.retQueue = mq;
        mb->dramAddr = direccion_v;
        mb->devAddr = direccion_dev;
        mb->size = nbytes;
    }
    if (mq != NULL) {
        osSendMesg(mq, (OSMesg) mb, OS_MESG_NOBLOCK);
    }
    return 0;
}

s32 osEPiStartDma(OSPiHandle *manejar, OSIoMesg *mb, s32 sentido)
{
    (void) manejar;
    return osPiStartDma(mb, mb->hdr.pri, sentido, mb->devAddr, mb->dramAddr, mb->size, mb->hdr.retQueue);
}

OSPiHandle *osCartRomInit(void)
{
    static OSPiHandle manejador;

    return &manejador;
}

static int negro_vi = 1;

int pantalla_en_negro(void)
{
    return negro_vi;
}

void osCreateViManager(OSPri prio)
{
    (void) prio;
}

void osViSetMode(OSViMode *mode)
{
    (void) mode; /* El modo del GS lo fija ps2_video.c */
}

void osViSetSpecialFeatures(u32 func)
{
    (void) func;
}

void osViBlack(u8 activo_2)
{
    negro_vi = activo_2;
}

void osViSetXScale(f32 value)
{
    (void) value;
}

void osViSetYScale(f32 value)
{
    (void) value;
}

static void *fb_actual_vi;
static void *fb_siguiente_vi;

void osViSwapBuffer(void *frame_buf_ptr)
{
    fb_actual_vi = fb_siguiente_vi;
    fb_siguiente_vi = frame_buf_ptr;
}

void *osViGetCurrentFramebuffer(void)
{
    return fb_actual_vi;
}

void *osViGetNextFramebuffer(void)
{
    return fb_siguiente_vi;
}

OSThread *__osGetCurrFaultedThread(void)
{
    return NULL;
}

void osSyncPrintf(const char *fmt, ...)
{
    (void) fmt;
}
