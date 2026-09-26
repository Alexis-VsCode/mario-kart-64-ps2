#include <ultra64.h>
#include <juego/macros.h>
#include <juego/definiciones.h>
#include <juego/tipos_actores.h>
#include "carrera/preparacion_carrera.h"
#include "sistema/matematicas.h"
#include "memoria/memoria_carrera.h"
#include "juego/camino.h"
#include "carrera/ia_vehiculos_y_camara.h"
#include "menus/elementos_menu.h"
#include "carrera/colision.h"
#include "carrera/actores.h"
#include "carrera/actores_extendidos.h"
#include "audio/externo.h"
#include "carrera/actualizar_objetos.h"
#include "carrera/efectos.h"
#include "juego/sonidos.h"

void copiar_colision(Colision* orig_, Colision* dest) {
    dest->desconocido30 = orig_->desconocido30;
    dest->desconocido32 = orig_->desconocido32;
    dest->unk34 = orig_->unk34;
    dest->indice_yx_malla = orig_->indice_yx_malla;
    dest->indice_zy_malla = orig_->indice_zy_malla;
    dest->indice_zx_malla = orig_->indice_zx_malla;
    dest->distancia_superficie[0] = orig_->distancia_superficie[0];
    dest->distancia_superficie[1] = orig_->distancia_superficie[1];
    dest->distancia_superficie[2] = orig_->distancia_superficie[2];

    copiar_retorno_vec3f(dest->desconocido48, orig_->desconocido48);
    copiar_retorno_vec3f(dest->desconocido54, orig_->desconocido54);
    copiar_retorno_vec3f(dest->vector_orientacion, orig_->vector_orientacion);
}

void chocar_con_jugador_triple_actor_caparazon(struct ActorCaparazon* caparazon, s32 tipo_caparazon) {
    TriplePadreCaparazon* padre = (TriplePadreCaparazon*) &lista_actor[caparazon->indice_padre];

    padre->disponible_caparazones--;

    switch ((s16) caparazon->id_caparazon) {
        case 0:
            padre->indices_caparazon[0] = -1.0f;
            break;
        case 1:
            padre->indices_caparazon[1] = -1.0f;
            break;
        case 2:
            padre->indices_caparazon[2] = -1.0f;
            break;
    }

    caparazon->flags = 0x8000;
    caparazon->angulo_rot = 0;
    caparazon->velocidad[1] = 3.0f;
    caparazon->algun_temporizador = 60;

    switch (tipo_caparazon) {
        case ACTOR_CAPARAZON_VERDE:
            caparazon->state = CAPARAZON_VERDE_CORREDOR_GOLPE_A;
            break;
        case ACTOR_CAPARAZON_ROJO:
            caparazon->state = CAPARAZON_DESTRUIDO;
            break;
    }
}

void funcion_802B039C(struct BananaActor* banana) {
    banana->state = BANANA_SOLTADO;
    banana->desconocido_04 = 0x00B4;
    banana->velocidad[0] = ((f32) (int_aleatorio(0x00C8) - 0x64) * 0.015);
    banana->velocidad[1] = ((f32) int_aleatorio(0x00C8)) * 0.015;
    banana->velocidad[2] = ((f32) (int_aleatorio(0x00C8) - 0x64) * 0.015);
}

void funcion_802B0464(s16 indice_banana) {
    struct BananaActor* banana;

    if (indice_banana != -1) {
        banana = (struct BananaActor*) &lista_actor[indice_banana];
        funcion_802B039C(banana);
        funcion_802B0464(banana->indice_menor);
    }
}

void funcion_802B04E8(SIN_USO struct BananaActor* parametro0, s16 indice_banana) {
    struct BananaActor* banana;

    if (indice_banana != -1) {
        banana = (struct BananaActor*) &lista_actor[indice_banana];
        funcion_802B039C(banana);
        funcion_802B04E8(banana, banana->indice_mayor);
    }
}

void destruir_banana_en_grupo_banana(struct BananaActor* banana) {
    struct PadreGrupoBanana* temporal_v0_2;

    funcion_802B0464(banana->indice_menor);
    funcion_802B04E8(banana, banana->indice_mayor);
    if ((jugadores[banana->id_jugador].type & HUMANO_JUGADOR) != 0) {
        funcion_800C9060(banana->id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x90, 0x53));
    }
    banana->flags = -0x8000;
    banana->desconocido_04 = 0x003C;
    banana->state = BANANA_DESTRUIDO;
    banana->velocidad[1] = 3.0f;
    temporal_v0_2 = (struct PadreGrupoBanana*) &lista_actor[banana->indice_padre];
    temporal_v0_2->banana_indices[0] = -1;
    temporal_v0_2->banana_indices[1] = -1;
    temporal_v0_2->banana_indices[2] = -1;
    temporal_v0_2->banana_indices[3] = -1;
    temporal_v0_2->banana_indices[4] = -1;
}

void soltar_banana_en_grupo_banana(struct PadreGrupoBanana* grupo_banana) {
    s16 indice_mayor;
    struct BananaActor* banana;

    grupo_banana->disponible_bananas -= 1;
    if (grupo_banana->banana_indices[4] != -1) {
        banana = (struct BananaActor*) &lista_actor[grupo_banana->banana_indices[4]];
        grupo_banana->banana_indices[4] = -1;
    } else if (grupo_banana->banana_indices[3] != -1) {
        banana = (struct BananaActor*) &lista_actor[grupo_banana->banana_indices[3]];
        grupo_banana->banana_indices[3] = -1;
    } else if (grupo_banana->banana_indices[2] != -1) {
        banana = (struct BananaActor*) &lista_actor[grupo_banana->banana_indices[2]];
        grupo_banana->banana_indices[2] = -1;
    } else if (grupo_banana->banana_indices[1] != -1) {
        banana = (struct BananaActor*) &lista_actor[grupo_banana->banana_indices[1]];
        grupo_banana->banana_indices[1] = -1;
    } else if (grupo_banana->banana_indices[0] != -1) {
        banana = (struct BananaActor*) &lista_actor[grupo_banana->banana_indices[0]];
        grupo_banana->banana_indices[0] = -1;
    } else {
        return;
    }

    banana->state = BANANA_SOLTADO;
    banana->desconocido_04 = 0x00B4;
    banana->velocidad[0] = 0.0f;
    banana->velocidad[1] = 1.5f;
    banana->velocidad[2] = 0.0f;
    indice_mayor = banana->indice_mayor;
    if (indice_mayor != -1) {
        ((struct BananaActor*) &lista_actor[indice_mayor])->indice_menor = -1;
    }
}

void funcion_802B0788(s16 palanca_y_crudo, struct PadreGrupoBanana* grupo_banana, Jugador* jugador) {
    Vec3f velocidad;
    struct BananaActor* banana;
    struct BananaActor* banana_mayor;
    f32 variable_f0;
    f32 variable_f12;

    grupo_banana->disponible_bananas -= 1;
    if (grupo_banana->banana_indices[4] != -1) {
        banana = (struct BananaActor*) &lista_actor[grupo_banana->banana_indices[4]];
        grupo_banana->banana_indices[4] = -1;
    } else if (grupo_banana->banana_indices[3] != -1) {
        banana = (struct BananaActor*) &lista_actor[grupo_banana->banana_indices[3]];
        grupo_banana->banana_indices[3] = -1;
    } else if (grupo_banana->banana_indices[2] != -1) {
        banana = (struct BananaActor*) &lista_actor[grupo_banana->banana_indices[2]];
        grupo_banana->banana_indices[2] = -1;
    } else if (grupo_banana->banana_indices[1] != -1) {
        banana = (struct BananaActor*) &lista_actor[grupo_banana->banana_indices[1]];
        grupo_banana->banana_indices[1] = -1;
    } else if (grupo_banana->banana_indices[0] != -1) {
        banana = (struct BananaActor*) &lista_actor[grupo_banana->banana_indices[0]];
        grupo_banana->banana_indices[0] = -1;
    } else {
        return;
    }

    banana->state = BANANA_SOLTADO;
    banana->desconocido_04 = 0x001E;
    if (banana->indice_mayor != -1) {
        banana_mayor = (struct BananaActor*) &lista_actor[banana->indice_mayor];
        banana_mayor->indice_menor = -1;
    }
    if (jugador->speed < 2.0f) {
        variable_f0 = ((palanca_y_crudo - 30.0f) / 20.0f) + 1.5f;
        variable_f12 = 4.0f;
    } else {
        variable_f0 = ((palanca_y_crudo - 30.0f) / 20.0f) + 1.5f;
        variable_f12 = (jugador->speed * 0.75f) + 4.5f + variable_f0;
    }
    fijar_vec3f(velocidad, 0.0f, variable_f0, variable_f12);
    vec3f_rotar_eje_y(velocidad, jugador->rotacion[1] + jugador->desconocido_0C0);
    banana->velocidad[0] = velocidad[0];
    banana->velocidad[1] = velocidad[1];
    banana->velocidad[2] = velocidad[2];
}

s32 funcion_802B09C0(s16 banana_id) {
    struct BananaActor* banana;
    if (banana_id == -1) {
        return 0;
    }
    banana = (struct BananaActor*) &lista_actor[banana_id];
    if (banana->state == PRIMER_BANANA_GRUPO_BANANA) {
        return 1;
    }
    if (banana->state == BANANA_GRUPO_BANANA) {
        return 1;
    }
    return 0;
}

void actualizar_grupo_banana_actor(struct PadreGrupoBanana* grupo_banana) {
    SIN_USO s32 relleno[2];
    Jugador* duenio;
    struct Mando* mando;
    s32 algun_cantidad;

    duenio = &jugadores[grupo_banana->id_jugador];
    switch (grupo_banana->state) {
        case 0:
            funcion_802B2914(grupo_banana, duenio, 0);
            grupo_banana->desconocido_04 = 4;
            grupo_banana->state = 1;
            grupo_banana->disponible_bananas = 1;
            break;
        case 1:
            grupo_banana->desconocido_04 -= 1;
            if (grupo_banana->desconocido_04 == 0) {
                funcion_802B2914(grupo_banana, duenio, 1);
                grupo_banana->desconocido_04 = 4;
                grupo_banana->state = 2;
                grupo_banana->disponible_bananas += 1;
            }
            break;
        case 2:
            grupo_banana->desconocido_04 -= 1;
            if (grupo_banana->desconocido_04 == 0) {
                funcion_802B2914(grupo_banana, duenio, 2);
                grupo_banana->desconocido_04 = 4;
                grupo_banana->state = 3;
                grupo_banana->disponible_bananas += 1;
            }
            break;
        case 3:
            grupo_banana->desconocido_04 -= 1;
            if (grupo_banana->desconocido_04 == 0) {
                funcion_802B2914(grupo_banana, duenio, 3);
                grupo_banana->desconocido_04 = 4;
                grupo_banana->state = 4;
                grupo_banana->disponible_bananas += 1;
            }
            break;
        case 4:
            grupo_banana->desconocido_04 -= 1;
            if (grupo_banana->desconocido_04 == 0) {
                funcion_802B2914(grupo_banana, duenio, 4);
                grupo_banana->desconocido_04 = 4;
                grupo_banana->state = 5;
                grupo_banana->disponible_bananas += 1;
            }
            break;
        case 5:
            grupo_banana->state = 6;
            ((struct BananaActor*) &lista_actor[grupo_banana->banana_indices[0]])->flags |= 0x5000;
            ((struct BananaActor*) &lista_actor[grupo_banana->banana_indices[1]])->flags |= 0x5000;
            ((struct BananaActor*) &lista_actor[grupo_banana->banana_indices[2]])->flags |= 0x5000;
            ((struct BananaActor*) &lista_actor[grupo_banana->banana_indices[3]])->flags |= 0x5000;
            ((struct BananaActor*) &lista_actor[grupo_banana->banana_indices[4]])->flags |= 0x5000;
            break;
        case 6:
            algun_cantidad = 0;
            if (funcion_802B09C0(grupo_banana->banana_indices[0]) == 1) {
                algun_cantidad = 1;
            }
            if (funcion_802B09C0(grupo_banana->banana_indices[1]) == 1) {
                algun_cantidad += 1;
            }
            if (funcion_802B09C0(grupo_banana->banana_indices[2]) == 1) {
                algun_cantidad += 1;
            }
            if (funcion_802B09C0(grupo_banana->banana_indices[3]) == 1) {
                algun_cantidad += 1;
            }
            if (funcion_802B09C0(grupo_banana->banana_indices[4]) == 1) {
                algun_cantidad += 1;
            }
            if (algun_cantidad == 0) {
                destruir_actor((struct Actor*) grupo_banana);
                duenio->disparadores &= ~EFECTO_ITEM_ARRASTRE;
            } else if ((duenio->type & HUMANO_JUGADOR) != 0) {
                mando = &mandos[grupo_banana->id_jugador];
                if ((mando->boton_pulsado & Z_TRIG) != 0) {
                    mando->boton_pulsado &= ~Z_TRIG;
                    funcion_800C9060(duenio - jugador_uno, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x12));
                    if ((mando->palanca_y_crudo >= 0x1F) &&
                        ((mando->palanca_x_crudo < 0x28) && (mando->palanca_x_crudo >= -0x27))) {
                        funcion_802B0788(mando->palanca_y_crudo, grupo_banana, duenio);
                    } else {
                        soltar_banana_en_grupo_banana(grupo_banana);
                    }
                }
            }
            break;
        default:
            break;
    }
}

bool es_existe_caparazon(s16 parametro0) {
    struct ActorCaparazon* actor;
    if (parametro0 < 0) {
        return false;
    }
    actor = (struct ActorCaparazon*) &lista_actor[parametro0];
    if (actor->type == ACTOR_CAPARAZON_VERDE) {
        if (actor->state == TRIPLE_CAPARAZON_VERDE) {
            return true;
        }
        return false;
    }
    if (actor->state == TRIPLE_CAPARAZON_ROJO) {
        return true;
    }
    return false;
}

void actualizar_caparazon_triple_actor(TriplePadreCaparazon* padre, s16 tipo_caparazon) {
    SIN_USO s32 relleno[2];
    s16 id_jugador;
    SIN_USO s32 relleno2;
    struct ActorCaparazon* caparazon;
    Vec3f algun_velocidad;
    SIN_USO s32 relleno3;
    s16 cantidad_caparazon;
    u16 algun_angulo_rot;
    Jugador* jugador;

    id_jugador = padre->id_jugador;
    jugador = &jugadores[id_jugador];
    padre->angulo_rot += padre->velocidad_rot;
    algun_angulo_rot = padre->angulo_rot;
    switch (padre->state) {
        case CAPARAZON_PRIMER_APARICION:
            if (inicializar_triple_caparazon(padre, &jugadores[id_jugador], tipo_caparazon, 0U) != -1) {
                funcion_800C9060(id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x12));
                padre->disponible_caparazones += 1;
            }
            padre->state = CAPARAZON_SEGUNDO_APARICION;
            break;
        case CAPARAZON_SEGUNDO_APARICION:
            if (padre->velocidad_rot > 0) {
                if (algun_angulo_rot > GRADOS(300)) {
                    if (inicializar_triple_caparazon(padre, &jugadores[id_jugador], tipo_caparazon, 1U) != -1) {
                        funcion_800C9060(id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x12));
                        padre->disponible_caparazones += 1;
                    }
                    padre->state = CAPARAZON_TERCER_APARICION;
                }
            } else {
                if (algun_angulo_rot < GRADOS(60)) {
                    if (inicializar_triple_caparazon(padre, &jugadores[id_jugador], tipo_caparazon, 1U) != -1) {
                        funcion_800C9060(id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x12));
                        padre->disponible_caparazones += 1;
                    }
                    padre->state = CAPARAZON_TERCER_APARICION;
                }
            }
            break;
        case CAPARAZON_TERCER_APARICION:
            if (padre->velocidad_rot > 0) {
                if ((algun_angulo_rot > GRADOS(60)) && (algun_angulo_rot < GRADOS(70))) {
                    if (inicializar_triple_caparazon(padre, &jugadores[id_jugador], tipo_caparazon, 2U) != -1) {
                        funcion_800C9060(id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x12));
                        padre->disponible_caparazones += 1;
                    }
                    padre->state = 3;
                }
            } else if ((algun_angulo_rot < GRADOS(300)) && (algun_angulo_rot > GRADOS(290))) {
                if (inicializar_triple_caparazon(padre, &jugadores[id_jugador], tipo_caparazon, 2U) != -1) {
                    funcion_800C9060(id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x12));
                    padre->disponible_caparazones += 1;
                }
                padre->state = 3;
            }
            break;
        case 3:
            padre->state = 4;
            caparazon = (struct ActorCaparazon*) &lista_actor[(s16) padre->indices_caparazon[0]];
            caparazon->flags |= 0x4000;
            caparazon = (struct ActorCaparazon*) &lista_actor[(s16) padre->indices_caparazon[1]];
            caparazon->flags |= 0x4000;
            caparazon = (struct ActorCaparazon*) &lista_actor[(s16) padre->indices_caparazon[2]];
            caparazon->flags |= 0x4000;
            break;
        case 4:
            cantidad_caparazon = 0;
            if (es_existe_caparazon(padre->indices_caparazon[0]) == 1) {
                cantidad_caparazon = 1;
            } else {
                padre->indices_caparazon[0] = -1.0f;
            }
            if (es_existe_caparazon(padre->indices_caparazon[1]) == 1) {
                cantidad_caparazon++;
            } else {
                padre->indices_caparazon[1] = -1.0f;
            }
            if (es_existe_caparazon(padre->indices_caparazon[2]) == 1) {
                cantidad_caparazon++;
            } else {
                padre->indices_caparazon[2] = -1.0f;
            }
            if (cantidad_caparazon == 0) {
                destruir_actor((struct Actor*) padre);
                break;
            }
            if ((mandos[padre->id_jugador].boton_pulsado & Z_TRIG) != 0) {
                padre->desconocido_08 += 1.0f;
                mandos[padre->id_jugador].boton_pulsado &= ~Z_TRIG;
            }
            if (padre->desconocido_08 > 0.0f) {
                if (padre->indices_caparazon[0] > 0.0f) {
                    caparazon = (struct ActorCaparazon*) &lista_actor[(s16) padre->indices_caparazon[0]];
                    if ((caparazon->angulo_rot < GRADOS(5)) || (caparazon->angulo_rot > -GRADOS(5))) {
                        algun_velocidad[0] = 0;
                        algun_velocidad[1] = 0;
                        algun_velocidad[2] = 8;
                        vec3f_rotar_eje_y(algun_velocidad, jugador->rotacion[1] + jugador->desconocido_0C0);
                        caparazon->velocidad[0] = algun_velocidad[0];
                        caparazon->velocidad[1] = algun_velocidad[1];
                        caparazon->velocidad[2] = algun_velocidad[2];
                        caparazon->state = CAPARAZON_MOVIENDO;
                        caparazon->algun_temporizador = 0x001E;
                        funcion_800C9060(padre->id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x04));
                        funcion_800C90F4(padre->id_jugador,
                                      (jugador->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x00));
                        if (padre->type == TRIPLE_ACTOR_CAPARAZON_ROJO) {
                            agregar_caparazon_rojo_en_lista_actor_vigente(padre->indices_caparazon[0]);
                        } else {
                            agregar_caparazon_verde_en_lista_actor_vigente(padre->indices_caparazon[0]);
                        }
                        padre->indices_caparazon[0] = -1.0f;
                        padre->disponible_caparazones -= 1;
                        padre->desconocido_08 -= 1.0f;
                        break;
                    }
                }
                if (padre->indices_caparazon[1] > 0.0f) {
                    caparazon = (struct ActorCaparazon*) &lista_actor[(s16) padre->indices_caparazon[1]];
                    if ((caparazon->angulo_rot < GRADOS(14.95)) || (caparazon->angulo_rot > GRADOS(5))) {
                        algun_velocidad[0] = 0;
                        algun_velocidad[1] = 0;
                        algun_velocidad[2] = 8;
                        vec3f_rotar_eje_y(algun_velocidad, jugador->rotacion[1] + jugador->desconocido_0C0);
                        caparazon->velocidad[0] = algun_velocidad[0];
                        caparazon->velocidad[1] = algun_velocidad[1];
                        caparazon->velocidad[2] = algun_velocidad[2];
                        caparazon->state = CAPARAZON_MOVIENDO;
                        caparazon->algun_temporizador = 0x001E;
                        funcion_800C90F4(padre->id_jugador,
                                      (jugador->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x00));
                        funcion_800C9060(padre->id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x04));
                        if (padre->type == TRIPLE_ACTOR_CAPARAZON_ROJO) {
                            agregar_caparazon_rojo_en_lista_actor_vigente(padre->indices_caparazon[1]);
                        } else {
                            agregar_caparazon_verde_en_lista_actor_vigente(padre->indices_caparazon[1]);
                        }
                        padre->indices_caparazon[1] = -1.0f;
                        padre->disponible_caparazones -= 1;
                        padre->desconocido_08 -= 1.0f;
                        break;
                    }
                }
                if (padre->indices_caparazon[2] > 0.0f) {
                    caparazon = (struct ActorCaparazon*) &lista_actor[(s16) padre->indices_caparazon[2]];
                    if ((caparazon->angulo_rot < -GRADOS(5)) || (caparazon->angulo_rot > -GRADOS(10))) {
                        algun_velocidad[0] = 0;
                        algun_velocidad[1] = 0;
                        algun_velocidad[2] = 8;
                        vec3f_rotar_eje_y(algun_velocidad, jugador->rotacion[1] + jugador->desconocido_0C0);
                        caparazon->velocidad[0] = algun_velocidad[0];
                        caparazon->velocidad[1] = algun_velocidad[1];
                        caparazon->velocidad[2] = algun_velocidad[2];
                        caparazon->state = CAPARAZON_MOVIENDO;
                        caparazon->algun_temporizador = 0x001E;
                        funcion_800C9060(padre->id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x04));
                        funcion_800C90F4(padre->id_jugador,
                                      (jugador->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x00));
                        if (padre->type == TRIPLE_ACTOR_CAPARAZON_ROJO) {
                            agregar_caparazon_rojo_en_lista_actor_vigente(padre->indices_caparazon[2]);
                        } else {
                            agregar_caparazon_verde_en_lista_actor_vigente(padre->indices_caparazon[2]);
                        }
                        padre->indices_caparazon[2] = -1.0f;
                        padre->disponible_caparazones -= 1;
                        padre->desconocido_08 -= 1.0f;
                        break;
                    }
                }
            }
            break;
        default:
            break;
    }
}

s32 usar_item_grupo_banana(Jugador* jugador) {
    Vec3f velocidad_inicial = { 0.0f, 0.0f, 0.0f };
    Vec3s rot_inicial = { 0, 0, 0 };
    Vec3f pos_inicial = { 0.0f, 0.0f, 0.0f };
    s16 indice_actor;
    struct PadreGrupoBanana* banana_grupo;

    indice_actor = agregar_actor_a_ranura_vacio(pos_inicial, rot_inicial, velocidad_inicial, GRUPO_BANANA_ACTOR);
    if (indice_actor < 0) {
        return indice_actor;
    }
    banana_grupo = (struct PadreGrupoBanana*) &lista_actor[indice_actor];
    banana_grupo->state = 0;
    banana_grupo->id_jugador = jugador - jugador_uno;
    jugador->disparadores |= EFECTO_ITEM_ARRASTRE;
    return indice_actor;
}

s32 usar_triple_item_caparazon(Jugador* jugador, s16 triple_tipo_caparazon) {
    Vec3f velocidad_inicial = { 0.0f, 0.0f, 0.0f };
    Vec3s rot_inicial = { 0, 0, 0 };
    Vec3f pos_inicial = { 0.0f, 0.0f, 0.0f };
    s16 indice_actor;
    TriplePadreCaparazon* padre;

    indice_actor = agregar_actor_a_ranura_vacio(pos_inicial, rot_inicial, velocidad_inicial, triple_tipo_caparazon);
    if (indice_actor < 0) {
        return indice_actor;
    }
    padre = (TriplePadreCaparazon*) &lista_actor[indice_actor];
    padre->state = 0;
    padre->velocidad_rot = GRADOS(8);
    padre->angulo_rot = - GRADOS(180);
    padre->id_jugador = jugador - jugador_uno;
    padre->disponible_caparazones = 0;
    padre->desconocido_08 = 0.0f;
    return indice_actor;
}

s32 inicializar_triple_caparazon(TriplePadreCaparazon* padre, Jugador* jugador, s16 tipo_caparazon, u16 id_caparazon) {
    Vec3f velocidad_inicial = { 0.0f, 0.0f, 0.0f };
    Vec3s rot_inicial = { 0, 0, 0 };
    Vec3f pos_inicial;
    s16 indice_actor;
    struct ActorCaparazon* caparazon;

    pos_inicial[0] = 0.0f;
    pos_inicial[1] = -jugador->tamanio_caja_envolvente;
    pos_inicial[2] = jugador->tamanio_caja_envolvente - 4.0f;
    transformar_mat3_vec3f_mtxf(pos_inicial, jugador->matriz_orientacion);
    pos_inicial[0] += jugador->pos[0];
    pos_inicial[1] += jugador->pos[1];
    pos_inicial[2] += jugador->pos[2];

    indice_actor = agregar_actor_a_ranura_vacio(pos_inicial, rot_inicial, velocidad_inicial, tipo_caparazon);
    if (indice_actor < 0) {
        padre->indices_caparazon[id_caparazon] = -1.0f;
        return -1;
    }

    caparazon = (struct ActorCaparazon*) &lista_actor[indice_actor];
    pos_inicial[0] = jugador->pos[0];
    pos_inicial[1] = jugador->pos[1];
    pos_inicial[2] = jugador->pos[2];
    colision_terreno_actor(&caparazon->desconocido30, caparazon->tamanio_caja_envolvente + 1.0f, caparazon->pos[0], caparazon->pos[1], caparazon->pos[2],
                            pos_inicial[0], pos_inicial[1], pos_inicial[2]);
    funcion_802B4E30((struct Actor*) caparazon);
    caparazon->flags = 0x9000;
    switch (tipo_caparazon) {
        case ACTOR_CAPARAZON_VERDE:
            caparazon->state = TRIPLE_CAPARAZON_VERDE;
            break;
        case ACTOR_CAPARAZON_ROJO:
            caparazon->state = TRIPLE_CAPARAZON_ROJO;
            break;
    }
    caparazon->velocidad_rot = 0;
    caparazon->angulo_rot = -GRADOS(180);
    caparazon->id_jugador = jugador - jugador_uno;
    caparazon->indice_padre = (struct Actor*) padre - lista_actor;
    caparazon->id_caparazon = id_caparazon;
    padre->indices_caparazon[id_caparazon] = (struct Actor*) caparazon - lista_actor;
    return 1;
}

s32 usar_caparazon_verde_item(Jugador* jugador) {
    Vec3f velocidad_inicial = { 0.0f, 0.0f, 0.0f };
    Vec3s rot_inicial = { 0, 0, 0 };
    Vec3f pos_inicial;
    s16 indice_actor;
    struct ActorCaparazon* caparazon;

    pos_inicial[0] = 0.0f;
    pos_inicial[1] = -jugador->tamanio_caja_envolvente;
    pos_inicial[2] = jugador->tamanio_caja_envolvente - 4.0f;

    transformar_mat3_vec3f_mtxf(pos_inicial, jugador->matriz_orientacion);

    pos_inicial[0] += jugador->pos[0];
    pos_inicial[1] += jugador->pos[1];
    pos_inicial[2] += jugador->pos[2];

    indice_actor = agregar_actor_a_ranura_vacio(pos_inicial, rot_inicial, velocidad_inicial, ACTOR_CAPARAZON_VERDE);
    if (indice_actor < 0) {
        return indice_actor;
    }

    caparazon = (struct ActorCaparazon*) &lista_actor[indice_actor];
    pos_inicial[0] = jugador->pos[0];
    pos_inicial[1] = jugador->pos[1];
    pos_inicial[2] = jugador->pos[2];
    colision_terreno_actor(&caparazon->desconocido30, caparazon->tamanio_caja_envolvente + 1.0f, caparazon->pos[0], caparazon->pos[1], caparazon->pos[2],
                            pos_inicial[0], pos_inicial[1], pos_inicial[2]);
    funcion_802B4E30((struct Actor*) caparazon);
    caparazon->state = CAPARAZON_MANTENIDO;
    caparazon->velocidad_rot = 0;
    caparazon->angulo_rot = -GRADOS(180);
    caparazon->id_jugador = jugador - jugador_uno;
    return indice_actor;
}

s32 usar_caparazon_rojo_item(Jugador* jugador) {
    Vec3f velocidad_inicial = { 0.0f, 0.0f, 0.0f };
    Vec3s rot_inicial = { 0, 0, 0 };
    Vec3f pos_inicial;
    s16 indice_actor;
    struct ActorCaparazon* caparazon;

    pos_inicial[0] = 0.0f;
    pos_inicial[1] = -jugador->tamanio_caja_envolvente;
    pos_inicial[2] = jugador->tamanio_caja_envolvente - 4.0f;

    transformar_mat3_vec3f_mtxf(pos_inicial, jugador->matriz_orientacion);

    pos_inicial[0] += jugador->pos[0];
    pos_inicial[1] += jugador->pos[1];
    pos_inicial[2] += jugador->pos[2];

    indice_actor = agregar_actor_a_ranura_vacio(pos_inicial, rot_inicial, velocidad_inicial, ACTOR_CAPARAZON_ROJO);
    if (indice_actor < 0) {
        return indice_actor;
    }

    caparazon = (struct ActorCaparazon*) &lista_actor[indice_actor];
    pos_inicial[0] = jugador->pos[0];
    pos_inicial[1] = jugador->pos[1];
    pos_inicial[2] = jugador->pos[2];
    colision_terreno_actor(&caparazon->desconocido30, caparazon->tamanio_caja_envolvente + 1.0f, caparazon->pos[0], caparazon->pos[1], caparazon->pos[2],
                            pos_inicial[0], pos_inicial[1], pos_inicial[2]);
    funcion_802B4E30((struct Actor*) caparazon);
    caparazon->state = CAPARAZON_MANTENIDO;
    caparazon->velocidad_rot = 0;
    caparazon->angulo_rot = jugador->rotacion[1] - GRADOS(180);
    caparazon->id_jugador = jugador - jugador_uno;
    return indice_actor;
}

void usar_caparazon_azul_item(Jugador* jugador) {
    lista_actor[usar_caparazon_rojo_item(jugador)].type = AZUL_ACTOR_CAPARAZON_ESPINOSO;
}

#include "carrera/actores/banana/actualizar.inc.c"

void funcion_802B2914(struct PadreGrupoBanana* grupo_banana, Jugador* jugador, s16 banana_id) {
    s16 indice_actor;
    Vec3f velocidad_inicial;
    Vec3s rot_inicial;
    Vec3f pos_inicial;
    SIN_USO s32 relleno;
    SIN_USO s32 relleno2;
    struct BananaActor* banana_nuevo;
    struct BananaActor* banana_temporal;

    pos_inicial[0] = 0.0f;
    pos_inicial[1] = -jugador->tamanio_caja_envolvente;
    pos_inicial[2] = -(jugador->tamanio_caja_envolvente + 4.0f);
    transformar_mat3_vec3f_mtxf(pos_inicial, jugador->matriz_orientacion);
    pos_inicial[0] += jugador->pos[0];
    pos_inicial[1] += jugador->pos[1];
    pos_inicial[2] += jugador->pos[2];
    velocidad_inicial[0] = jugador->velocidad[0];
    velocidad_inicial[1] = jugador->velocidad[1];
    velocidad_inicial[2] = jugador->velocidad[2];
    rot_inicial[0] = 0;
    rot_inicial[1] = 0;
    rot_inicial[2] = 0;
    indice_actor = agregar_actor_a_ranura_vacio(pos_inicial, rot_inicial, velocidad_inicial, ACTOR_BANANA);
    if (indice_actor >= 0) {
        banana_nuevo = (struct BananaActor*) &lista_actor[indice_actor];
        pos_inicial[0] = jugador->pos[0];
        pos_inicial[1] = jugador->pos[1];
        pos_inicial[2] = jugador->pos[2];
        colision_terreno_actor(&banana_nuevo->desconocido30, banana_nuevo->tamanio_caja_envolvente + 1.0f, banana_nuevo->pos[0],
                                banana_nuevo->pos[1], banana_nuevo->pos[2], pos_inicial[0], pos_inicial[1], pos_inicial[2]);
        funcion_802B4E30((struct Actor*) banana_nuevo);
        banana_nuevo->flags = 0x9000;
        banana_nuevo->id_jugador = jugador - jugador_uno;
        banana_nuevo->indice_padre = (struct Actor*) grupo_banana - lista_actor;
        banana_nuevo->indice_menor = -1;
        banana_nuevo->desconocido_04 = 0x0014;
        banana_nuevo->banana_id = banana_id;
        switch (banana_id) {
            case 0:
                banana_nuevo->state = 2;
                grupo_banana->banana_indices[0] = indice_actor;
                banana_nuevo->indice_mayor = -1;
                break;
            case 1:
                banana_nuevo->state = 3;
                grupo_banana->banana_indices[1] = indice_actor;
                banana_nuevo->indice_mayor = grupo_banana->banana_indices[0];
                banana_temporal = (struct BananaActor*) &lista_actor[grupo_banana->banana_indices[0]];
                banana_temporal->indice_menor = indice_actor;
                break;
            case 2:
                banana_nuevo->state = 3;
                grupo_banana->banana_indices[2] = indice_actor;
                banana_nuevo->indice_mayor = grupo_banana->banana_indices[1];
                banana_temporal = (struct BananaActor*) &lista_actor[grupo_banana->banana_indices[1]];
                banana_temporal->indice_menor = indice_actor;
                break;
            case 3:
                banana_nuevo->state = 3;
                grupo_banana->banana_indices[3] = indice_actor;
                banana_nuevo->indice_mayor = grupo_banana->banana_indices[2];
                banana_temporal = (struct BananaActor*) &lista_actor[grupo_banana->banana_indices[2]];
                banana_temporal->indice_menor = indice_actor;
                break;
            case 4:
                banana_nuevo->state = 3;
                grupo_banana->banana_indices[4] = indice_actor;
                banana_nuevo->indice_mayor = grupo_banana->banana_indices[3];
                banana_temporal = (struct BananaActor*) &lista_actor[grupo_banana->banana_indices[3]];
                banana_temporal->indice_menor = indice_actor;
                break;
        }
        if ((jugador->type & HUMANO_JUGADOR) != 0) {
            funcion_800C9060(jugador - jugador_uno, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x12));
        }
    }
}

s32 usar_item_caja_item_falso(Jugador* jugador) {
    struct CajaItemFalsa* caja_item;
    SIN_USO s32 relleno[5];
    s16 indice_actor;
    Vec3f velocidad_inicial;
    Vec3s rot_inicial;
    Vec3f pos_inicial;

    pos_inicial[0] = 0.0f;
    pos_inicial[1] = -jugador->tamanio_caja_envolvente;
    pos_inicial[2] = -(jugador->tamanio_caja_envolvente + 4.0f);

    transformar_mat3_vec3f_mtxf(pos_inicial, jugador->matriz_orientacion);

    pos_inicial[0] += jugador->pos[0];
    pos_inicial[1] += jugador->pos[1];
    pos_inicial[2] += jugador->pos[2];

    velocidad_inicial[0] = jugador->velocidad[0];
    velocidad_inicial[1] = jugador->velocidad[1];
    velocidad_inicial[2] = jugador->velocidad[2];

    rot_inicial[0] = 0;
    rot_inicial[1] = 0;
    rot_inicial[2] = 0;

    indice_actor = agregar_actor_a_ranura_vacio(pos_inicial, rot_inicial, velocidad_inicial, ACTOR_CAJA_ITEM_FALSA);
    if (indice_actor < 0) {
        return indice_actor;
    }
    caja_item = (struct CajaItemFalsa*) &lista_actor[indice_actor];
    caja_item->id_jugador = (jugador - jugador_uno);
    caja_item->state = MANTENIDO_CAJA_ITEM_FALSA;
    jugador->disparadores |= EFECTO_ITEM_ARRASTRE;
    return indice_actor;
}

s32 usar_item_banana(Jugador* jugador) {
    SIN_USO s32 relleno[6];
    u16 id_jugador;
    s16 indice_actor;
    struct BananaActor* banana;
    Vec3f velocidad_inicial;
    Vec3s rot_inicial;
    Vec3f pos_inicial;

    id_jugador = jugador - jugador_uno;
    if (id_jugador >= 8) {
        return -1;
    }
    pos_inicial[0, 0] = 0.0f;
    pos_inicial[1] = -jugador->tamanio_caja_envolvente;
    pos_inicial[2] = -(jugador->tamanio_caja_envolvente + 4.0f);

    transformar_mat3_vec3f_mtxf(pos_inicial, jugador->matriz_orientacion);

    pos_inicial[0] += jugador->pos[0];
    pos_inicial[1] += jugador->pos[1];
    pos_inicial[2] += jugador->pos[2];

    velocidad_inicial[0] = jugador->velocidad[0];
    velocidad_inicial[1] = jugador->velocidad[1];
    velocidad_inicial[2] = jugador->velocidad[2];
    rot_inicial[0] = 0;
    rot_inicial[1] = 0;
    rot_inicial[2] = 0;

    indice_actor = agregar_actor_a_ranura_vacio(pos_inicial, rot_inicial, velocidad_inicial, ACTOR_BANANA);
    if (indice_actor < 0) {
        return indice_actor;
    }
    banana = (struct BananaActor*) &lista_actor[indice_actor];
    banana->id_jugador = id_jugador;
    banana->state = BANANA_MANTENIDO;
    banana->desconocido_04 = 0x0014;
    jugador->disparadores |= EFECTO_ITEM_ARRASTRE;
    return indice_actor;
}

void usar_item_trueno(Jugador* jugador) {
    s32 index;
    Jugador* otro_jugador;

    funcion_8009E5BC();
    if ((jugador->type & HUMANO_JUGADOR) != 0) {
        funcion_800CAB4C(jugador - jugador_uno);
    }

    for (index = 0; index < JUGADORES_NUM; index++) {
        otro_jugador = &jugadores[index];
        if (jugador != otro_jugador) {
            otro_jugador->disparadores |= DISPARADOR_GOLPE_RAYO;
        }
    }
}

void item_usar_jugador(Jugador* jugador) {
    s32 id_jugador = jugador - jugador_uno;

    switch (jugador->copia_item_actual) {
        case ITEM_CAPARAZON_VERDE:
            usar_caparazon_verde_item(jugador);
            break;
        case ITEM_CAPARAZON_ROJO:
            usar_caparazon_rojo_item(jugador);
            break;
        case AZUL_ITEM_CAPARAZON_ESPINOSO:
            usar_caparazon_azul_item(jugador);
            break;
        case ITEM_BANANA:
            usar_item_banana(jugador);
            break;
        case GRUPO_BANANA_ITEM:
            usar_item_grupo_banana(jugador);
            break;
        case HONGO_ITEM:
            jugador->disparadores |= DISPARADOR_HONGO;
            break;
        case HONGO_DOBLE_ITEM:
            jugador->disparadores |= DISPARADOR_HONGO;
            break;
        case ITEM_TRIPLE_HONGO:
            jugador->disparadores |= DISPARADOR_HONGO;
            break;
        case ITEM_SUPER_HONGO:
            jugador->disparadores |= DISPARADOR_HONGO;
            break;
        case ITEM_BOO:
            jugador->disparadores |= BOO_DISPARADOR;
            break;
        case ESTRELLA_ITEM:
            jugador->disparadores |= DISPARADOR_ESTRELLA;
            break;
        case RAYO_ITEM:
            usar_item_trueno(jugador);
            break;
        case ITEM_CAJA_ITEM_FALSA:
            usar_item_caja_item_falso(jugador);
            break;
        case TRIPLE_ITEM_CAPARAZON_VERDE:
            usar_triple_item_caparazon(jugador, TRIPLE_ACTOR_CAPARAZON_VERDE);
            break;
        case TRIPLE_ITEM_CAPARAZON_ROJO:
            usar_triple_item_caparazon(jugador, TRIPLE_ACTOR_CAPARAZON_ROJO);
            break;
    }
    consumir_item(id_jugador);
}

void comprobar_item_usar_jugador(void) {
    Jugador* jugador;
    struct Mando* objetivo;
    struct Mando* mando;
    struct Mando* mando_bucle;

    for (jugador = &jugadores[0], mando_bucle = &mandos[0], objetivo = &mandos[4]; mando_bucle != objetivo;
         jugador++, mando_bucle++) {
        mando = mando_bucle;
        if (evitar_usar_item(jugador) == false) {
            if ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != 0) {
                if ((jugador - jugador_dos) == 0) {
                    mando = mando_seis;
                } else if ((jugador - jugador_tres) == 0) {
                    mando = mando_siete;
                } else {
                    if ((jugador - jugador_uno) == 0) {
                        mando = mando_ocho;
                    }
                }
            }

            if (((jugador->type & HUMANO_JUGADOR) != 0) && (jugador->copia_item_actual != NINGUNO_ITEM) &&
                ((jugador->type & SECUENCIA_INICIO_JUGADOR) == 0)) {
                if ((mando->boton_pulsado & Z_TRIG) != 0) {
                    mando->boton_pulsado &= ~Z_TRIG;
                    item_usar_jugador(jugador);
                }
            }
        }
    }
}

#include "carrera/actores/caparazon_verde/actualizar.inc.c"

#include "carrera/actores/caparazones_azul_y_rojo/actualizar.inc.c"

void funcion_802B4E30(struct Actor* parametro0) {
    if ((parametro0->desconocido30.distancia_superficie[2] < 0.0f) && (parametro0->desconocido30.unk34 == 1)) {
        parametro0->pos[0] -= (parametro0->desconocido30.vector_orientacion[0] * parametro0->desconocido30.distancia_superficie[2]);
        parametro0->pos[1] -= (parametro0->desconocido30.vector_orientacion[1] * parametro0->desconocido30.distancia_superficie[2]);
        parametro0->pos[2] -= (parametro0->desconocido30.vector_orientacion[2] * parametro0->desconocido30.distancia_superficie[2]);
    }
    if ((parametro0->desconocido30.distancia_superficie[0] < 0.0f) && (parametro0->desconocido30.desconocido30 == 1)) {
        parametro0->pos[0] -= (parametro0->desconocido30.desconocido48[0] * parametro0->desconocido30.distancia_superficie[0]);
        parametro0->pos[1] -= (parametro0->desconocido30.desconocido48[1] * parametro0->desconocido30.distancia_superficie[0]);
        parametro0->pos[2] -= (parametro0->desconocido30.desconocido48[2] * parametro0->desconocido30.distancia_superficie[0]);
    }
    if ((parametro0->desconocido30.distancia_superficie[1] < 0.0f) && (parametro0->desconocido30.desconocido32 == 1)) {
        parametro0->pos[0] -= (parametro0->desconocido30.desconocido54[0] * parametro0->desconocido30.distancia_superficie[1]);
        parametro0->pos[1] -= (parametro0->desconocido30.desconocido54[1] * parametro0->desconocido30.distancia_superficie[1]);
        parametro0->pos[2] -= (parametro0->desconocido30.desconocido54[2] * parametro0->desconocido30.distancia_superficie[1]);
    }
}
