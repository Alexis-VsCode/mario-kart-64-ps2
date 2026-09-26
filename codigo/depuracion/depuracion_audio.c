#ifdef SMK64_DEV
#include <ultra64.h>
#include "audio/interno.h"
#include "audio/carga.h"

void registrar(const char *fmt, ...);

void registrar_reproductores_secuencias(void)
{
    int i;

    for (i = 0; i < JUGADORES_SECUENCIA; i++) {
        struct JugadorSecuencia *p = &jugadores_secuencia[i];

        registrar("  seqplayer %d: on %d estado %d seq %d banco %d tempo %u delay %u vol %d/100 pc %p", i, p->activado,
                p->state, p->sec_id, p->banco_predeterminado[0], p->tempo, p->delay, (int) (p->volumen_fundido * 100),
                p->estado_guion.pc);
    }
}
#else
void registrar_reproductores_secuencias(void)
{
}
#endif
