#include <carrera/actores.h>
#include <carrera/preparacion_carrera.h>
#include <juego/definiciones.h>
#include <sistema/bucle_principal.h>

void actualizar_banana_actor(struct BananaActor* banana) {
    SIN_USO f32 relleno;
    Jugador* jugador;
    struct BananaActor* banana_mayor;
    struct Mando* mando;
    Vec3f algun_otro_velocidad;
    Vec3f algun_velocidad;
    f32 temporal_f0;
    SIN_USO f32 variable_f8;
    SIN_USO f32 relleno2;
    SIN_USO f32 relleno3;
    SIN_USO f32 relleno4[2];
    f32 temporal_f12;
    f32 temporal_f2;
    f32 temporal_f14;
    f32 temporal_f16;
    f32 desconocido_x;
    f32 desconocido_y;
    f32 desconocido_z;

    jugador = &jugadores[banana->rot[0]];
    switch (banana->state) {
        case BANANA_MANTENIDO:
            temporal_f2 = jugador->pos[0] - banana->pos[0];
            temporal_f14 = jugador->pos[1] - banana->pos[1];
            temporal_f16 = jugador->pos[2] - banana->pos[2];
            temporal_f12 = sqrtf((temporal_f2 * temporal_f2) + (temporal_f14 * temporal_f14) + (temporal_f16 * temporal_f16)) / 10.0f;
            if (temporal_f12 == 0.0f) {
                banana->pos[0] = jugador->pos[0] + 0.2f;
                banana->pos[1] = jugador->pos[1] + 0.2f;
                banana->pos[2] = jugador->pos[2] + 0.2f;
            } else {
                temporal_f2 /= temporal_f12;
                temporal_f14 /= temporal_f12;
                temporal_f16 /= temporal_f12;
                banana->pos[0] = jugador->pos[0] - temporal_f2;
                banana->pos[1] = jugador->pos[1] - temporal_f14 - 2.0f;
                banana->pos[2] = jugador->pos[2] - temporal_f16;
            }
            comprobar_colision_envolvente(&banana->desconocido30, banana->tamanio_caja_envolvente + 1.0f, banana->pos[0], banana->pos[1],
                                     banana->pos[2]);
            funcion_802B4E30((struct Actor*) banana);
            if ((jugador->type & HUMANO_JUGADOR) != 0) {
                if (modo_demo) {
                    mando = mando_uno;
                } else {
                    mando = &mandos[banana->rot[0]];
                }
                if ((mando->boton_apretado & Z_TRIG) != 0) {
                    mando->boton_apretado &= ~Z_TRIG;
                    banana->state = BANANA_SOLTADO;
                    banana->desconocido_04 = 0x00B4;
                    jugador->disparadores &= ~EFECTO_ITEM_ARRASTRE;
                    funcion_800C9060(jugador - jugador_uno, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x12));
                    relleno3 = mando->palanca_y_crudo;
                    if ((relleno3 > 30.0f) && (mando->palanca_x_crudo < 10) && (mando->palanca_x_crudo >= -9)) {
                        relleno3 = relleno3 - ((f32) 30);
                        relleno3 = (relleno3 / 20.0f) + 0.5f;
                        if (jugador->speed < 2.0f) {
                            temporal_f0 = 4.0f;
                        } else {
                            temporal_f0 = (jugador->speed * 0.75f) + 3.5f + relleno3;
                        }
                        fijar_vec3f(algun_velocidad, 0, relleno3, temporal_f0);
                        vec3f_rotar_eje_y(algun_velocidad, jugador->rotacion[1] + jugador->desconocido_0C0);
                        banana->velocidad[0] = algun_velocidad[0];
                        banana->velocidad[1] = algun_velocidad[1];
                        banana->velocidad[2] = algun_velocidad[2];
                    } else {
                        banana->velocidad[0] = 0;
                        banana->velocidad[1] = 1.5f;
                        banana->velocidad[2] = 0;
                    }
                }
            }
            break;
        case BANANA_SOLTADO:
            if (banana->desconocido_04 != 0) {
                banana->desconocido_04 -= 1;
                if (banana->desconocido_04 == 0) {
                    banana->flags &= ~0x1000;
                }
            }
            banana->pos[0] += banana->velocidad[0];
            banana->pos[2] += banana->velocidad[2];
            if (banana->velocidad[1] > -1.0f) {
                banana->velocidad[1] -= 0.15f;
            }
            banana->pos[1] += banana->velocidad[1];
            if ((banana->pos[2] < (f32) min_z_circuito) || ((f32) max_z_circuito < banana->pos[2]) ||
                (banana->pos[0] < (f32) min_x_circuito) || ((f32) max_x_circuito < banana->pos[0]) ||
                (banana->pos[1] < (f32) min_y_circuito)) {
                destruir_actor_destructible((struct Actor*) banana);
            } else {
                comprobar_colision_envolvente(&banana->desconocido30, banana->tamanio_caja_envolvente + 1.0f, banana->pos[0], banana->pos[1],
                                         banana->pos[2]);
                banana->desconocido30.unk34 = 1;
                if ((banana->desconocido30.unk34 != 0) && (banana->desconocido30.distancia_superficie[2] < 0.0f)) {
                    algun_otro_velocidad[0] = -banana->desconocido30.vector_orientacion[0];
                    algun_otro_velocidad[1] = -banana->desconocido30.vector_orientacion[1];
                    algun_otro_velocidad[2] = -banana->desconocido30.vector_orientacion[2];
                    banana->pos[0] += algun_otro_velocidad[0] * banana->desconocido30.distancia_superficie[2];
                    banana->pos[1] += algun_otro_velocidad[1] * banana->desconocido30.distancia_superficie[2];
                    banana->pos[2] += algun_otro_velocidad[2] * banana->desconocido30.distancia_superficie[2];
                    banana->flags &= ~0x1000;
                    banana->state = 4;
                }
            }
            break;
        case PRIMER_BANANA_GRUPO_BANANA:
            algun_velocidad[0] = 0.0f;
            algun_velocidad[1] = 0.0f;
            algun_velocidad[2] = -5.0f;
            vec3f_rotar_eje_y(algun_velocidad, jugador->rotacion[1] + jugador->desconocido_0C0);
            desconocido_x = jugador->pos[0] + algun_velocidad[0];
            desconocido_y = jugador->pos[1] + algun_velocidad[1];
            desconocido_z = jugador->pos[2] + algun_velocidad[2];
            temporal_f2 = desconocido_x - banana->pos[0];
            temporal_f14 = desconocido_y - banana->pos[1];
            temporal_f16 = desconocido_z - banana->pos[2];
            temporal_f0 = sqrtf((temporal_f2 * temporal_f2) + (temporal_f14 * temporal_f14) + (temporal_f16 * temporal_f16));
            if (temporal_f0 == 0.0f) {
                banana->pos[0] = jugador->pos[0] + 0.2f;
                banana->pos[1] = jugador->pos[1] + 0.2f;
                banana->pos[2] = jugador->pos[2] + 0.2f;
            } else {
                temporal_f2 /= temporal_f0;
                temporal_f14 /= temporal_f0;
                temporal_f16 /= temporal_f0;
                banana->pos[0] = algun_velocidad[0] + (desconocido_x - temporal_f2);
                banana->pos[1] = desconocido_y - temporal_f14 - 2.0f;
                banana->pos[2] = desconocido_z - temporal_f16;
            }
            comprobar_colision_envolvente(&banana->desconocido30, banana->tamanio_caja_envolvente + 1.0f, banana->pos[0], banana->pos[1],
                                     banana->pos[2]);
            funcion_802B4E30((struct Actor*) banana);
            break;
        case BANANA_GRUPO_BANANA:
            banana_mayor = (struct BananaActor*) &lista_actor[banana->indice_mayor];
            temporal_f2 = banana_mayor->pos[0] - banana->pos[0];
            temporal_f14 = banana_mayor->pos[1] - banana->pos[1];
            temporal_f16 = banana_mayor->pos[2] - banana->pos[2];
            temporal_f12 = sqrtf((temporal_f2 * temporal_f2) + (temporal_f14 * temporal_f14) + (temporal_f16 * temporal_f16)) / 5.0f;
            if (temporal_f12 == 0.0f) {
                banana->pos[0] = banana_mayor->pos[0] + 0.2f;
                banana->pos[1] = banana_mayor->pos[1] + 0.2f;
                banana->pos[2] = banana_mayor->pos[2] + 0.2f;
            } else {
                temporal_f2 /= temporal_f12;
                temporal_f14 /= temporal_f12;
                temporal_f16 /= temporal_f12;
                banana->pos[0] = banana_mayor->pos[0] - temporal_f2;
                banana->pos[1] = banana_mayor->pos[1] - temporal_f14 - 2.0f;
                banana->pos[2] = banana_mayor->pos[2] - temporal_f16;
            }
            variable_f8 = banana->pos[2];
            comprobar_colision_envolvente(&banana->desconocido30, banana->tamanio_caja_envolvente + 1.0f, banana->pos[0], banana->pos[1],
                                     banana->pos[2]);
            funcion_802B4E30((struct Actor*) banana);
            break;
        case BANANA_DESTRUIDO:
            banana->velocidad[1] -= 0.3f;
            if (banana->velocidad[1] < -5.0f) {
                banana->velocidad[1] = -5.0f;
            }
            banana->pos[1] += banana->velocidad[1];
            banana->rot[0] += GRADOS(2);
            banana->rot[1] -= GRADOS(8);
            banana->rot[2] += GRADOS(5);
            banana->desconocido_04 -= 1;
            if (banana->desconocido_04 == 0) {
                destruir_actor((struct Actor*) banana);
            }
            break;
        case BANANA_EN_SUELO:
            banana->flags |= 0xC000;
            banana->flags &= ~0x1000;
            break;
        default:
            break;
    }
}
