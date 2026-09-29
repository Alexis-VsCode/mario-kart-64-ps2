#include <iopcontrol.h>
#include <kernel.h>
#include <loadfile.h>
#include <sbv_patches.h>
#include <sifrpc.h>
#include <stdio.h>

#include <ultra64.h>

#include "sistema/sistema_ps2.h"
#include "graficos/interprete_f3dex.h"
#include "audio/salida_audio.h"
#include "sistema/guardado_ps2.h"
#include "sistema/cronometro_fases.h"
#include "depuracion/marcas_registro.h"
#include "sistema/caracteres_es.h"

extern void funcion_principal(void);

/* Prioridad del hilo principal */
#define PRIORIDAD_HILO_PRINCIPAL 126

#ifdef SMK64_BOOT_STOP
#include <depuracion/depuracion_juego.h>
static void detener_arranque(int etapa)
{
    if (etapa == SMK64_BOOT_STOP) {
        char texto[64], ascii[64];

        /* scr_printf solo tiene ASCII */
        snprintf(texto, sizeof(texto), "\n  SMK64 PS2: parada de diagnóstico en la etapa %d\n", etapa);
        quitar_diacriticos(ascii, sizeof(ascii), texto);
        init_scr();
        scr_printf("%s", ascii);
        for (;;) {
            SleepThread();
        }
    }
}
#define ETAPA(n) detener_arranque(n)
#else
#define ETAPA(n) do { } while (0)
#endif

/* Deja el IOP en un estado conocido */
static void reiniciar_iop(void)
{
    SifInitRpc(0);
    while (!SifIopReset("", 0)) {
    }
    while (!SifIopSync()) {
    }
    SifInitRpc(0);
    SifLoadFileInit();
    sbv_patch_enable_lmb();
    sbv_patch_disable_prefix_check();
}

int main(int argc, char *argv[])
{

    ETAPA(0);
    empezar_tiempos_ps2(GRUPO_ARRANQUE);
#ifndef SMK64_NO_IOP_RESET
    reiniciar_iop();
#else
    SifInitRpc(0);
#endif
    marcar_tiempos_ps2("reinicio del IOP");
    ChangeThreadPriority(GetThreadId(), PRIORIDAD_HILO_PRINCIPAL);
    ETAPA(1);

    inicializar_depuracion();
    ETAPA(2);
    registrar("arranque: ROM %u KB en %p", (unsigned) ((__rom_end - __rom_start) / 1024), __rom_start);
    if (!inicializar_rom_ps2(argc > 0 ? argv[0] : NULL)) {
        detener_por_error("falta SMK64ROM.BIN: usa la ISO completa (o el ELF monolítico con uLaunchELF)");
    }
    marcar_tiempos_ps2("disco: empieza la carga");

    inicializar_hilos();
    inicializar_hardware_libultra();
    guardar_segmentos_iniciales();
    marcar_tiempos_ps2("depuración, hilos, segmentos");
    ETAPA(3);
    inicializar_renderizador();
    marcar_tiempos_ps2("GS y texturas");
    ETAPA(4);
    inicializar_mandos_ps2();
    marcar_tiempos_ps2("mandos (SIO2MAN, PADMAN)");
    inicializar_memory_card();  /* necesita SIO2MAN, que carga inicializar_mandos_ps2 */
    /* la lectura de la memory card sigue en segundo plano */
    marcar_tiempos_ps2("memory card (MCMAN/MCSERV)");
    ETAPA(5);
    inicializar_ps2_audio();
    marcar_tiempos_ps2("audio (LIBSD, AUDSRV)");
    inicializar_retrazo();
    ETAPA(6);

    registrar("entrando en el bucle principal del juego");
    funcion_principal();

    for (;;) {
        SleepThread();
    }
    return 0;
}
