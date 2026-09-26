#include <carrera/actores.h>
#include <sistema/bucle_principal.h>

void actualizar_actor_caja_item_falsa(struct CajaItemFalsa* caja_item_falsa) {
    u32 temporal_v1 = caja_item_falsa->id_jugador;
    Jugador* temporal_v0_4 = &jugadores[temporal_v1];
    struct Mando* temporal_v1_3;

    SIN_USO s32 relleno[7];
    f32 temporal_f2_2;
    f32 temporal_f14;
    f32 temporal_f16;
    f32 temporal_f18;
    SIN_USO s32 relleno2[3];

    switch (caja_item_falsa->state) {
        case 0:
            caja_item_falsa->tamanio_caja_envolvente = caja_item_falsa->escalado_tamanio * 5.5f;
            caja_item_falsa->rot[0] -= GRADOS(1);
            caja_item_falsa->rot[1] += GRADOS(2);
            caja_item_falsa->rot[2] -= GRADOS(1);

            temporal_f14 = temporal_v0_4->pos[0] - caja_item_falsa->pos[0];
            temporal_f16 = temporal_v0_4->pos[1] - caja_item_falsa->pos[1];
            temporal_f18 = temporal_v0_4->pos[2] - caja_item_falsa->pos[2];

            temporal_f2_2 = sqrtf((temporal_f14 * temporal_f14) + (temporal_f16 * temporal_f16) + (temporal_f18 * temporal_f18)) / 10.0f;
            temporal_f14 /= temporal_f2_2;
            temporal_f16 /= temporal_f2_2;
            temporal_f18 /= temporal_f2_2;
            caja_item_falsa->pos[0] = temporal_v0_4->pos[0] - temporal_f14;
            caja_item_falsa->pos[1] = (temporal_v0_4->pos[1] - temporal_f16) - 1.0f;
            caja_item_falsa->pos[2] = temporal_v0_4->pos[2] - temporal_f18;
            comprobar_colision_envolvente(&caja_item_falsa->desconocido30, caja_item_falsa->tamanio_caja_envolvente, caja_item_falsa->pos[0],
                                     caja_item_falsa->pos[1], caja_item_falsa->pos[2]);
            funcion_802B4E30((struct Actor*) caja_item_falsa);
            temporal_v1_3 = &mandos[temporal_v1];
            if ((temporal_v0_4->type & HUMANO_JUGADOR) != 0) {

                if ((temporal_v1_3->boton_apretado & Z_TRIG) != 0) {
                    temporal_v1_3->boton_apretado &= ~Z_TRIG;
                    funcion_802A1064(caja_item_falsa);
                    temporal_v0_4->disparadores &= ~EFECTO_ITEM_ARRASTRE;
                    funcion_800C9060((u8) (temporal_v0_4 - jugador_uno), SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x12));
                }
            }
            break;
        case 1:
            if (caja_item_falsa->escalado_tamanio < 1.0f) {
                caja_item_falsa->escalado_tamanio += 0.05f;
            } else if (caja_item_falsa->escalado_tamanio >= 1.0f) {
                caja_item_falsa->escalado_tamanio = 1.0f;
            }

            caja_item_falsa->tamanio_caja_envolvente = caja_item_falsa->escalado_tamanio * 5.5f;
            if (caja_item_falsa->objetivo_y <= caja_item_falsa->pos[1]) {
                caja_item_falsa->pos[1] = caja_item_falsa->objetivo_y;
            } else {
                caja_item_falsa->pos[1] += 0.2f;
            }
            if ((caja_item_falsa->flags & 0x1000) != 0) {
                if ((caja_item_falsa->algun_temporizador <= 0) || (caja_item_falsa->algun_temporizador >= 0x12D)) {
                    caja_item_falsa->flags &= 0xEFFF;
                    caja_item_falsa->algun_temporizador = 0;
                } else {
                    caja_item_falsa->algun_temporizador--;
                }
            }
            caja_item_falsa->rot[0] -= GRADOS(1);
            caja_item_falsa->rot[1] += GRADOS(2);
            caja_item_falsa->rot[2] -= GRADOS(1);
            break;

        case 2:
            if ((caja_item_falsa->algun_temporizador >= 0x14) || (caja_item_falsa->algun_temporizador < 0)) {
                destruir_actor((struct Actor*) caja_item_falsa);
            } else {
                caja_item_falsa->algun_temporizador++;
                caja_item_falsa->rot[0] += GRADOS(6);
                caja_item_falsa->rot[1] -= GRADOS(4);
                caja_item_falsa->rot[2] += GRADOS(2);
            }
            break;
        default:
            destruir_actor((struct Actor*) caja_item_falsa);
            break;
    }
}
