#include <stdio.h>
#include <string.h>

#include <ultra64.h>
#include "audio/interno.h"
#include "audio/carga.h"
#include "audio/monton.h"

#include "sistema/sistema_ps2.h"
#include "audio/salida_audio.h"
#include "depuracion/monitor_audio.h"

extern u8 dato_800EA188[][6];
extern u8 dato_800EA1C0;
extern u32 notas_robadas, sonidos_sin_nota;

int ps2_audio_monitor_canal_banco(int indice_canal)
{
    /* externo.c reparte los canales banco por banco (dato_80192C38) */
    const u8 *per = dato_800EA188[dato_800EA1C0 < 4 ? dato_800EA1C0 : 0];
    int b, primer = 0;

    for (b = 0; b < PS2_AUDIO_SONIDO_BANCOS; b++) {
        if (indice_canal < primer + per[b]) {
            return b;
        }
        primer += per[b];
    }
    return -1;
}

static int canal_indice(const struct JugadorSecuencia *p, const struct CanalSecuencia *c)
{
    int i;

    for (i = 0; i < MAX_CANALES; i++) {
        if (p->channels[i] == c) {
            return i;
        }
    }
    return -1;
}

void ps2_audio_monitor_copia(CopiaAudioPs2 *s)
{
    const struct JugadorSecuencia *sfx = &jugadores_secuencia[PS2_AUDIO_SFX_JUGADOR];
    int i;

    memset(s, 0, sizeof(*s));
    s->max_notas = (u16) notas_simultaneo_max;
    if (notas != NULL) {
        for (i = 0; i < notas_simultaneo_max; i++) {
            const struct Nota *n = &notas[i];
            const struct EstadoReproduccionNota *ps = (const struct EstadoReproduccionNota *) &n->priority;
            const struct CapaCanalSecuencia *l = ps->capa_padre;

            if (!n->eu_sub_nota.activado || l == NULL || (uintptr_t) l >= 0x7FFFFFFFU || l->sec_canal == NULL) {
                continue;
            }
            s->activo_notas++;
            {
                int pl = (int) (l->sec_canal->sec_jugador - jugadores_secuencia);

                if (pl >= 0 && pl < 4) {
                    s->notas_por_jugador[pl]++;
                }
            }
            if (l->sec_canal->sec_jugador == sfx) {
                int b = ps2_audio_monitor_canal_banco(canal_indice(sfx, l->sec_canal));

                s->sfx_notas++;
                if (b >= 0) {
                    s->sfx_por_banco[b]++;
                    if (b == PS2_AUDIO_VOZ_BANCO) {
                        s->voz_notas++;
                    }
                }
            } else {
                s->musica_notas++;
            }
        }
    }
    for (i = 0; i < 4 && i < JUGADORES_SECUENCIA; i++) {
        s->sec[i] = jugadores_secuencia[i].activado ? jugadores_secuencia[i].sec_id : 0xFF;
    }
    for (; i < 4; i++) {
        s->sec[i] = 0xFF;
    }
    {
        EstadisticasAudioPs2 a;

        obtener_estadisticas_audio_ps2(&a);
        s->vaciados = a.vaciados;
        s->ms_cola = a.ms_cola;
        s->max_us_tarea = a.max_us_tarea;
        s->blocks = a.blocks;
        s->pico = a.pico;
    }
    s->steals_nota = notas_robadas;
    s->drops_nota = sonidos_sin_nota;
}

static void sec_texto(char *salida, int size, u8 id)
{
    if (id == 0xFF) {
        snprintf(salida, size, "-");
    } else {
        snprintf(salida, size, "%u", (unsigned) id);
    }
}

int ps2_audio_monitor_lineas(char (*lineas_2)[64], int lineas_max)
{
    CopiaAudioPs2 s;
    char m0[8], m1[8];
    int n = 0;

    ps2_audio_monitor_copia(&s);
    sec_texto(m0, sizeof(m0), s.sec[0]);
    sec_texto(m1, sizeof(m1), s.sec[1]);
#define LINEA(...)                                  \
    do {                                           \
        if (n < lineas_max) {                        \
            snprintf(lineas_2[n], 64, __VA_ARGS__);   \
            n++;                                   \
        }                                          \
    } while (0)
    LINEA("AUDIO N64 COLA %u MS CORTES %u TAREA MÁX %u US", (unsigned) s.ms_cola, (unsigned) s.vaciados,
         (unsigned) s.max_us_tarea);
    LINEA("NOTAS %u/%u MÚSICA %u EFECTOS %u VOCES %u", (unsigned) s.activo_notas, (unsigned) s.max_notas,
         (unsigned) s.musica_notas, (unsigned) (s.sfx_notas - s.voz_notas), (unsigned) s.voz_notas);
    LINEA("EFECTOS POR BANCO %u %u %u %u %u %u", s.sfx_por_banco[0], s.sfx_por_banco[1], s.sfx_por_banco[2], s.sfx_por_banco[3],
         s.sfx_por_banco[4], s.sfx_por_banco[5]);
    LINEA("MÚSICA SEC %s + %s  EFECTOS SEC %s", m0, m1, s.sec[2] == 0xFF ? "-" : "0");
    LINEA("PICO %d ROBOS %u DESCARTES %u BLOQUES %u", (int) s.pico, (unsigned) s.steals_nota,
         (unsigned) s.drops_nota, (unsigned) s.blocks);
#undef LINEA
    return n;
}

void ps2_audio_monitor_frame(void)
{
#if defined(SMK64_DEBUG_AUDIO)
    static u32 s_frames;
    char lineas_2[8][64];
    int i, n;

    /* cada 2 s al registro (printf en DEBUG */
    if ((++s_frames % 120) != 0) {
        return;
    }
    n = ps2_audio_monitor_lineas(lineas_2, 8);
    for (i = 0; i < n; i++) {
        rend_registro_ps2("debug_audio: %s", lineas_2[i]);
    }
#endif
}
