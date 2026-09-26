#ifndef DEPURACION_MEDIDOR_RENDIMIENTO_H
#define DEPURACION_MEDIDOR_RENDIMIENTO_H

#include <tamtypes.h>

#define MEDIDOR_CICLOS_POR_MS 294912u

/* VRAM que reserva el panel (textura CT32 de 256x96 */
#define MEDIDOR_VRAM_BYTES (96 * 1024)

static inline u32 medidor_leer_ciclos(void)
{
    u32 ciclos;

    __asm__ __volatile__("mfc0 %0, $9" : "=r"(ciclos));
    return ciclos;
}

void medidor_inicio_frame(void);
void medidor_dibujar(void);
void medidor_fin_frame(void);
/* Un frame intermedio (60 FPS) mostrado ademas del de la tarea */
void medidor_frame_intermedio(void);

/* Capa baja del GS (sintetizador_gs.c). */
void medidor_sumar_espera_gs(u32 ciclos);
void medidor_sumar_espera_dma(u32 ciclos);
void medidor_contar_envio_dma(void);

void medidor_sumar_audio(u32 ciclos);
void medidor_cola_audio(u32 bytes_encolados);

void medidor_entrada_mando(u32 pulsados);

/* Hilo inactivo del juego (hilo1_inactivo en src/bucle_principal.c) */
void medidor_bucle_inactivo(void) __attribute__((noreturn));

#endif
