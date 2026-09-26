#include <carrera/actores.h>
#include <sistema/bucle_principal.h>
#include <juego/definiciones.h>
#include <juego/camino.h>

void actualizar_actor_kiwano_fruta(struct KiwanoFruta* fruta) {
    Jugador* jugador;
    f32 temporal_f2;
    f32 temporal_f16;
    f32 temporal_f14;
    f32 temporal_f12;
    s32 punto_camino_mas_cercano;

    jugador = &jugadores[fruta->jugador_objetivo];
    if (((jugador->type & CPU_JUGADOR) != 0) || (jugador->colision.unk34 == 0)) {
        fruta->state = 0;
        return;
    }
    switch (fruta->state) { /* irregular */
        case 0:
            if ((obtener_tipo_superficie(jugador->colision.indice_zx_malla) & 0xFF) != PASTO) {
                return;
            }
            fruta->state = 1;
            fruta->velocidad[0] = 80.0f;
        case 1:
            punto_camino_mas_cercano = punto_camino_mas_cercano_por_id_jugador[(u16) (jugador - jugador_uno)];
            temporal_f2 = jugador->pos[0] - camino_pista_actual[punto_camino_mas_cercano].pos_x;
            temporal_f16 = jugador->pos[1] - camino_pista_actual[punto_camino_mas_cercano].pos_y;
            temporal_f14 = jugador->pos[2] - camino_pista_actual[punto_camino_mas_cercano].pos_z;
            temporal_f12 = fruta->velocidad[0] / sqrtf((temporal_f2 * temporal_f2) + (temporal_f16 * temporal_f16) + (temporal_f14 * temporal_f14));
            temporal_f2 *= temporal_f12;
            temporal_f16 *= temporal_f12;
            temporal_f14 *= temporal_f12;
            fruta->pos[0] = jugador->pos[0] + temporal_f2;
            fruta->pos[1] = jugador->pos[1] + temporal_f16;
            fruta->pos[2] = jugador->pos[2] + temporal_f14;
            fruta->velocidad[0] -= 2.0f;
            if (fruta->velocidad[0] <= 0.0f) {
                fruta->state = 2;
                fruta->temporizador_golpe = 30.0f;
                fruta->velocidad[0] = 0.0f;
                fruta->velocidad[1] = 2.3f;
                fruta->velocidad[2] = 0.0f;
                if ((jugador->efectos & EFECTO_ESTRELLA) != 0) {
                    funcion_800C9060(jugador - jugador_uno, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0xA0, 0x52));
                } else {
                    jugador->efectos |= EFECTO_GOLPE_ENEMIGO;
                    jugador->pos[0] -= temporal_f2 * 4.0f;
                    jugador->pos[2] -= temporal_f14 * 4.0f;
                    jugador->velocidad[0] -= temporal_f2 * 0.7f;
                    jugador->velocidad[2] -= temporal_f14 * 0.7f;
                    funcion_800C9060(jugador - jugador_uno, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x70, 0x18));
                    if (seleccion_modo != GRAN_PREMIO) {
                        publicar_contrarreloj_guardado_no_puede_repeticion = 1;
                    }
                }
            }
            break;
        case 2:
            fruta->velocidad[1] -= 0.3f;
            fruta->pos[0] += fruta->velocidad[0];
            fruta->pos[1] += fruta->velocidad[1];
            fruta->pos[2] += fruta->velocidad[2];
            fruta->temporizador_golpe -= 1.0f;
            if (fruta->temporizador_golpe < 0.0f) {
                fruta->state = 0;
            }
            break;
        default:
            break;
    }
    if (fruta->state != 0) {
        fruta->anim_temporizador += 1;
        if (fruta->anim_temporizador == 8) {
            fruta->anim_temporizador = 0;
            fruta->anim_estado += 1;
            if (fruta->anim_estado == 3) {
                fruta->anim_estado = 0;
            }
        }
    }
}
