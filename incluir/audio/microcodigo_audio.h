#ifndef AUDIO_MICROCODIGO_AUDIO_H
#define AUDIO_MICROCODIGO_AUDIO_H

#include <ultra64.h>

/* Datos del microcodigo (big-endian, rspAspMainDataStart) */
void inicializar_aspmain(const u8 *asp_principal_datos_be);
/* Ejecuta una tarea de audio: bytes_tamanio / 8 comandos Acmd. */
void ejecutar_tarea_aspmain(u64 *lista_cmd, u32 bytes_tamanio);
/* 1 (por defecto) */
void fijar_shortcuts_aspmain(int activar);

#ifdef SMK64_DEV
void volcar_pedido_aspmain(const char *nombre, int tareas);
/* Compara la version MMI con el C en 'iters' comandos al azar */
int autoprueba_aspmain(int vueltas);
#endif

#endif
