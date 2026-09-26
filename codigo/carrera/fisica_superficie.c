#include <ultra64.h>
#include <juego/macros.h>
#include <juego/mk64.h>
#include <juego/pista.h>

#include "sistema/matematicas.h"
#include <juego/estructuras_comunes.h>
#include "carrera/control_jugador.h"
#include "carrera/efectos.h"
#include "carrera/fisica_superficie.h"
#include "juego/definiciones.h"

void funcion_8003DC40(Jugador* jugador) {
    jugador->desconocido_dac = 1.0f;
}

SIN_USO void funcion_8003DC50(Jugador* jugador, Vec3f parametro1) {
    s32 cosa1 = 0;
    s32 cosa2 = 0;
    if (jugador) {};
    if (jugador->desconocido_230 <= jugador->desconocido_23C) {
        if (jugador->colision.desconocido48[1] >= 0.1736) {
            parametro1[0] = (jugador->desconocido_206 / GRADOS(1)) * 0x78;
            parametro1[2] = -(jugador->acel_pendiente / GRADOS(1)) * 0x78;
        } else {
            parametro1[0] = cosa1;
            parametro1[2] = cosa2;
        }
    } else if (jugador->colision.desconocido48[1] >= 0.1736) {
        parametro1[0] = (jugador->desconocido_206 / GRADOS(1)) * 0x78;
        parametro1[2] = -(jugador->acel_pendiente / GRADOS(1)) * 0x78;
    } else {
        parametro1[0] = cosa1;
        parametro1[2] = cosa2;
    }
    parametro1[1] = 0.0f;
    transformar_mat3_vec3f_mtxf(parametro1, jugador->matriz_orientacion);
}

SIN_USO void funcion_8003DE4C(Jugador* jugador, Vec3f parametro1) {
    s32 cosa1 = 0;
    s32 cosa2 = 0;
    if (jugador) {};
    if (jugador->desconocido_230 <= jugador->desconocido_23C) {
        if (jugador->colision.desconocido54[1] >= 0.1736) {
            parametro1[0] = (jugador->desconocido_206 / GRADOS(1)) * 0x78;
            parametro1[2] = -(jugador->acel_pendiente / GRADOS(1)) * 0x78;
        } else {
            parametro1[0] = cosa1;
            parametro1[2] = cosa2;
        }
    } else if (jugador->colision.desconocido54[1] >= 0.1736) {
        parametro1[0] = (jugador->desconocido_206 / GRADOS(1)) * 0x78;
        parametro1[2] = -(jugador->acel_pendiente / GRADOS(1)) * 0x78;
    } else {
        parametro1[0] = cosa1;
        parametro1[2] = cosa2;
    }
    parametro1[1] = 0.0f;
    transformar_mat3_vec3f_mtxf(parametro1, jugador->matriz_orientacion);
}

void funcion_8003E048(Jugador* jugador, Vec3f parametro1, Vec3f parametro2, Vec3f parametro3, f32* parametro4, f32* parametro5, f32* parametro6, f32* parametro7) {
    *parametro5 += parametro1[0] * jugador->colision.distancia_superficie[2] * 1;
    *parametro6 += parametro1[1] * jugador->colision.distancia_superficie[2] * 0.1;
    *parametro7 += parametro1[2] * jugador->colision.distancia_superficie[2] * 1;
    funcion_8002A5F4(parametro1, *parametro4, parametro2, 1, 2);
    if (jugador->colision.vector_orientacion[1] <= 0.8829f) {
        parametro3[0] = ((jugador->desconocido_206 / GRADOS(1)) * 0xB4);
        parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0xB4);
        alternativo_desacelerar_jugador(jugador, 4.0f);
        jugador->desconocido_dac = 0.5f;
        if ((jugador->efectos & EFECTO_HONGO) != 0) {
            quitar_efecto_hongo(jugador);
            jugador->actual_rapidez /= 2;
            jugador->desconocido_08C /= 2;
        }
    } else if ((((jugador->speed / 18.0f) * 216.0f) > 20.0f) ||
               ((jugador->efectos & EFECTO_VUELCO_TERRENO) == EFECTO_VUELCO_TERRENO)) {
        parametro3[0] = ((jugador->desconocido_206 / GRADOS(1)) * 0x32);
        parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0x3C);
    } else {
        parametro3[0] = 0.0f;
        parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0x32);
    }
    parametro3[1] = 0.0f;
    transformar_mat3_vec3f_mtxf(parametro3, jugador->matriz_orientacion);
}

void funcion_8003E37C(Jugador* jugador, Vec3f parametro1, Vec3f parametro2, Vec3f parametro3, f32* parametro4, f32* parametro5, f32* parametro6, f32* parametro7) {
    *parametro5 += parametro1[0] * jugador->colision.distancia_superficie[2] * 1;
    *parametro6 += parametro1[1] * jugador->colision.distancia_superficie[2] * 0.2;
    *parametro7 += parametro1[2] * jugador->colision.distancia_superficie[2] * 1;
    funcion_8002A5F4(parametro1, *parametro4, parametro2, 0.5f, 2);
    if ((jugador->colision.vector_orientacion[1] <= 0.7318f) || (jugador->tipo_superficie == ACANTILADO)) {
        parametro3[0] = ((jugador->desconocido_206 / GRADOS(1)) * 0xB4);
        parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0xB4);
        if (((jugador->speed / 18.0f) * 216.0f) >= 8.0f) {
            alternativo_desacelerar_jugador(jugador, 5.0f);
        }
        jugador->desconocido_dac = 0.5f;
        if ((jugador->efectos & EFECTO_HONGO) != 0) {
            quitar_efecto_hongo(jugador);
            jugador->actual_rapidez /= 2;
            jugador->desconocido_08C /= 2;
        }
    } else if ((((jugador->speed / 18.0f) * 216.0f) > 20.0f) ||
               ((jugador->efectos & EFECTO_VUELCO_TERRENO) == EFECTO_VUELCO_TERRENO)) {
        parametro3[0] = ((jugador->desconocido_206 / GRADOS(1)) * 0x32);
        parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0x32);
    } else {
        parametro3[0] = 0.0f;
        parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0x32);
    }
    parametro3[1] = 0.0f;
    transformar_mat3_vec3f_mtxf(parametro3, jugador->matriz_orientacion);
}

void funcion_8003E6EC(Jugador* jugador, Vec3f parametro1, Vec3f parametro2, Vec3f parametro3, f32* parametro4, f32* parametro5, f32* parametro6, f32* parametro7) {
    *parametro5 += parametro1[0] * jugador->colision.distancia_superficie[2] * 1;
    *parametro6 += parametro1[1] * jugador->colision.distancia_superficie[2] * 0.1;
    *parametro7 += parametro1[2] * jugador->colision.distancia_superficie[2] * 1;
    funcion_8002A5F4(parametro1, *parametro4, parametro2, 0.5f, 2);
    if (jugador->colision.vector_orientacion[1] <= 0.8829f) {
        parametro3[0] = ((jugador->desconocido_206 / GRADOS(1)) * 0xB4);
        parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0xB4);
        alternativo_desacelerar_jugador(jugador, 4.0f);
        funcion_8003DC40(jugador);
    } else if ((((jugador->speed / 18.0f) * 216.0f) > 20.0f) ||
               ((jugador->efectos & EFECTO_VUELCO_TERRENO) == EFECTO_VUELCO_TERRENO)) {
        parametro3[0] = ((jugador->desconocido_206 / GRADOS(1)) * 0x32);
        parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0x3C);
    } else {
        parametro3[0] = 0.0f;
        parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0x32);
    }
    parametro3[1] = 0.0f;
    transformar_mat3_vec3f_mtxf(parametro3, jugador->matriz_orientacion);
}

void funcion_8003E9EC(Jugador* jugador, Vec3f parametro1, Vec3f parametro2, Vec3f parametro3, f32* parametro4, f32* parametro5, f32* parametro6, f32* parametro7) {
    *parametro5 += parametro1[0] * jugador->colision.distancia_superficie[2] * 1;
    *parametro6 += parametro1[1] * jugador->colision.distancia_superficie[2] * 0.1;
    *parametro7 += parametro1[2] * jugador->colision.distancia_superficie[2] * 1;
    funcion_8002A5F4(parametro1, *parametro4, parametro2, 1.2f, 2);
    if (jugador->colision.vector_orientacion[1] <= 0.8357f) {
        parametro3[0] = ((jugador->desconocido_206 / GRADOS(1)) * 0x78);
        parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0xB4);
        alternativo_desacelerar_jugador(jugador, 4.0f);
        funcion_8003DC40(jugador);
    } else {
        if ((((jugador->speed / 18.0f) * 216.0f) > 20.0f) ||
            ((jugador->efectos & EFECTO_VUELCO_TERRENO) == EFECTO_VUELCO_TERRENO)) {
            if ((jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie == ASFALTO) ||
                (jugador->ruedas[DERECHA_ATRAS].tipo_superficie == ASFALTO) ||
                (jugador->ruedas[DERECHA_FRENTE].tipo_superficie == ASFALTO) ||
                (jugador->ruedas[IZQUIERDA_FRENTE].tipo_superficie == ASFALTO)) {
                parametro3[0] = ((jugador->desconocido_206 / GRADOS(1)) * 5);
            } else {
                parametro3[0] = ((jugador->desconocido_206 / GRADOS(1)) * 0x28);
            }
            parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0x28);
        } else {
            parametro3[0] = 0.0f;
            parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0x32);
        }
        if ((jugador->efectos & EFECTO_VUELCO_TERRENO) != 0) {
            parametro3[0] = ((jugador->desconocido_206 / GRADOS(1)) * 0x78);
            parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0xB4);
        }
    }
    parametro3[1] = 0.0f;
    transformar_mat3_vec3f_mtxf(parametro3, jugador->matriz_orientacion);
}

void funcion_8003EE2C(Jugador* jugador, Vec3f parametro1, Vec3f parametro2, Vec3f parametro3, f32* parametro4, f32* parametro5, f32* parametro6, f32* parametro7) {
    *parametro5 += parametro1[0] * jugador->colision.distancia_superficie[2] * 1;
    *parametro6 += parametro1[1] * jugador->colision.distancia_superficie[2] * 0.1;
    *parametro7 += parametro1[2] * jugador->colision.distancia_superficie[2] * 1;
    funcion_8002A5F4(parametro1, *parametro4, parametro2, 0.5f, 2);
    if (jugador->colision.vector_orientacion[1] <= 0.8357f) {
        parametro3[0] = ((jugador->desconocido_206 / GRADOS(1)) * 0x78);
        parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0xB4);
        alternativo_desacelerar_jugador(jugador, 4.0f);
        funcion_8003DC40(jugador);
    } else if ((((jugador->speed / 18.0f) * 216.0f) > 20.0f) ||
               ((jugador->efectos & EFECTO_VUELCO_TERRENO) == EFECTO_VUELCO_TERRENO)) {
        parametro3[0] = ((jugador->desconocido_206 / GRADOS(1)) * 0x32);
        parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0x3C);
    } else {
        parametro3[0] = 0.0f;
        parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0x32);
    }
    parametro3[1] = 0.0f;
    transformar_mat3_vec3f_mtxf(parametro3, jugador->matriz_orientacion);
}

void funcion_8003F138(Jugador* jugador, Vec3f parametro1, Vec3f parametro2, Vec3f parametro3, f32* parametro4, f32* parametro5, f32* parametro6, f32* parametro7) {
    *parametro5 += parametro1[0] * jugador->colision.distancia_superficie[2] * 1;
    *parametro6 += parametro1[1] * jugador->colision.distancia_superficie[2] * 0.1;
    *parametro7 += parametro1[2] * jugador->colision.distancia_superficie[2] * 1;
    funcion_8002A5F4(parametro1, *parametro4, parametro2, 0.5f, 2);
    if (jugador->tipo_superficie == PASTO) {
        jugador->kart_props &= ~ARRIBA_ATRAS;
    }
    if (jugador->colision.vector_orientacion[1] <= 0.8357f) {
        parametro3[0] = ((jugador->desconocido_206 / GRADOS(1)) * 0xC8);
        parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0xC8);
        alternativo_desacelerar_jugador(jugador, 4.0f);
        jugador->desconocido_dac = 0.5f;
        parametro3[0] = 0;
    } else if ((((jugador->speed / 18.0f) * 216.0f) > 20.0f) ||
               ((jugador->efectos & EFECTO_VUELCO_TERRENO) == EFECTO_VUELCO_TERRENO)) {
        parametro3[0] = ((jugador->desconocido_206 / GRADOS(1)) * 0x78);
        parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0x78);
        parametro3[0] = 0;
    } else {
        parametro3[0] = 0.0f;
        parametro3[2] = (-(jugador->acel_pendiente / GRADOS(1)) * 0x32);
    }
    parametro3[1] = 0.0f;
    parametro3[2] = 0.0f;
    transformar_mat3_vec3f_mtxf(parametro3, jugador->matriz_orientacion);
}

void funcion_8003F46C(Jugador* jugador, Vec3f parametro1, Vec3f parametro2, Vec3f parametro3, f32* parametro4, f32* parametro5, f32* parametro6, f32* parametro7) {
    parametro1[0] = -jugador->colision.vector_orientacion[0];
    parametro1[1] = -jugador->colision.vector_orientacion[1];
    parametro1[2] = -jugador->colision.vector_orientacion[2];
    if ((jugador->colision.vector_orientacion[1] < 0.0f) && ((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == 0)) {
        *parametro5 += parametro1[0] * jugador->colision.distancia_superficie[2] * 1;
        *parametro6 += parametro1[1] * jugador->colision.distancia_superficie[2] * 1;
        *parametro7 += parametro1[2] * jugador->colision.distancia_superficie[2] * 1;
        funcion_8002A5F4(parametro1, *parametro4, parametro2, 1.2f, 0.0f);
        jugador->tiron_salto_kart = 0.0f;
        jugador->aceleracion_salto_kart = 0.0f;
        jugador->velocidad_salto_kart = 0.0f;
        return;
    } else {
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
        switch (id_circuito_actual) {
            case CIRCUITO_MARIO_RACEWAY:
                funcion_8003E048(jugador, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6, parametro7);
                break;
            case CIRCUITO_CHOCO_MOUNTAIN:
            case CIRCUITO_KOOPA_BEACH:
                funcion_8003E37C(jugador, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6, parametro7);
                break;
            case CIRCUITO_BOWSER_CASTLE:
                funcion_8003E6EC(jugador, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6, parametro7);
                break;
            case CIRCUITO_LUIGI_RACEWAY:
                funcion_8003E9EC(jugador, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6, parametro7);
                break;
            case CIRCUITO_WARIO_STADIUM:
                funcion_8003EE2C(jugador, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6, parametro7);
                break;
            case CIRCUITO_DK_JUNGLE:
                funcion_8003F138(jugador, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6, parametro7);
                break;
            default:
                funcion_8003E048(jugador, parametro1, parametro2, parametro3, parametro4, parametro5, parametro6, parametro7);
                break;
        }
#else

#endif
        if (jugador->efectos & EFECTO_VUELCO_TERRENO) {
            jugador->desconocido_dac = 0.5f;
        }
    }
}

void funcion_8003F734(Jugador* jugador, Vec3f parametro1, Vec3f parametro2, f32* parametro3, f32* parametro4, f32* parametro5, f32* parametro6) {
    f32 temporal_f12;
    f32 temporal_f14;
    f32 temporal_f0_2;

    parametro1[0] = -jugador->colision.desconocido48[0];
    parametro1[1] = -jugador->colision.desconocido48[1];
    parametro1[2] = -jugador->colision.desconocido48[2];
    if (jugador->colision.desconocido48[1] == 0) {
        *parametro4 += parametro1[0] * jugador->colision.distancia_superficie[0] * 1;
        *parametro5 += parametro1[1] * jugador->colision.distancia_superficie[0] * 0.1;
        *parametro6 += parametro1[2] * jugador->colision.distancia_superficie[0] * 1;
        if ((jugador->acel_pendiente < 0) && (((jugador->speed / 18.0f) * 216.0f) < 10.0f)) {
            funcion_8002A5F4(parametro1, *parametro3, parametro2, 2.5f, 0);
        } else {
            funcion_8002A5F4(parametro1, *parametro3, parametro2, 0.5f, 0);
        }
    } else if (jugador->colision.desconocido48[1] <= 0.5) {
        *parametro4 += parametro1[0] * jugador->colision.distancia_superficie[0] * 1;
        *parametro5 += parametro1[1] * jugador->colision.distancia_superficie[0] * 0.1;
        *parametro6 += parametro1[2] * jugador->colision.distancia_superficie[0] * 1;
        funcion_8002A5F4(parametro1, *parametro3, parametro2, 1, 0);
        if ((!(jugador->efectos & EFECTO_VUELCO_TERRENO)) && ((jugador->efectos & EFECTO_EN_EL_AIRE) == 0)) {
            parametro2[1] *= -1e-05;
        }
    } else {
        *parametro4 += parametro1[0] * jugador->colision.distancia_superficie[0] * 1;
        temporal_f0_2 = jugador->colision.distancia_superficie[0] * parametro1[1];
        if (temporal_f0_2 < 0) {
            *parametro5 += temporal_f0_2 * 0.1;
        } else {
            *parametro5 += temporal_f0_2 * 0;
        }
        *parametro6 += parametro1[2] * jugador->colision.distancia_superficie[0] * 1;
        funcion_8002A5F4(parametro1, *parametro3, parametro2, 1.2f, 0);
        if ((!(jugador->efectos & EFECTO_VUELCO_TERRENO)) && ((jugador->efectos & EFECTO_EN_EL_AIRE) == 0)) {
            parametro2[1] *= -1e-05;
        }
    }
    jugador->efectos &= ~EFECTO_DERRAPANDO;
    temporal_f12 = jugador->colision.distancia_superficie[0] * parametro1[0];
    temporal_f14 = jugador->colision.distancia_superficie[0] * parametro1[2];
    if (((temporal_f12 >= 0) && (temporal_f14 >= 0)) || ((temporal_f12 < 0) && (temporal_f14 >= 0))) {
        temporal_f0_2 = jugador->tamanio_caja_envolvente / 2;
        jugador->desconocido_218 = *parametro4 - temporal_f12 - temporal_f0_2;
        jugador->desconocido_21C = *parametro6 - temporal_f14 - temporal_f0_2;
    }
    if (((temporal_f12 < 0) && (temporal_f14 < 0)) || ((temporal_f12 >= 0) && (temporal_f14 < 0))) {
        temporal_f0_2 = jugador->tamanio_caja_envolvente / 2;
        jugador->desconocido_218 = *parametro4 + temporal_f12 + temporal_f0_2;
        jugador->desconocido_21C = *parametro6 + temporal_f14 + temporal_f0_2;
    }
}

void funcion_8003FBAC(Jugador* jugador, Vec3f parametro1, Vec3f parametro2, f32* parametro3, f32* parametro4, f32* parametro5, f32* parametro6) {
    f32 temporal_f0_2;
    f32 temporal_f12;
    f32 temporal_f14;

    parametro1[0] = -jugador->colision.desconocido54[0];
    parametro1[1] = -jugador->colision.desconocido54[1];
    parametro1[2] = -jugador->colision.desconocido54[2];
    if (jugador->colision.desconocido54[1] == 0) {
        *parametro4 += parametro1[0] * jugador->colision.distancia_superficie[1] * 1;
        *parametro5 += parametro1[1] * jugador->colision.distancia_superficie[1] * 0.1;
        *parametro6 += parametro1[2] * jugador->colision.distancia_superficie[1] * 1;
        if ((jugador->acel_pendiente < 0) && (((jugador->speed / 18.0f) * 216.0f) < 10.0f)) {
            funcion_8002A5F4(parametro1, *parametro3, parametro2, 1.5f, 0);
        } else {
            funcion_8002A5F4(parametro1, *parametro3, parametro2, 0.5f, 0);
        }
    } else if (jugador->colision.desconocido54[1] <= 0.5) {
        *parametro4 += parametro1[0] * jugador->colision.distancia_superficie[1] * 1;
        *parametro5 += parametro1[1] * jugador->colision.distancia_superficie[1] * 0.1;
        *parametro6 += parametro1[2] * jugador->colision.distancia_superficie[1] * 1;
        funcion_8002A5F4(parametro1, *parametro3, parametro2, 1, 0);
        if ((!(jugador->efectos & EFECTO_VUELCO_TERRENO)) && ((jugador->efectos & EFECTO_EN_EL_AIRE) == 0)) {
            parametro2[1] *= -1e-05;
        }
    } else {
        *parametro4 += parametro1[0] * jugador->colision.distancia_superficie[1] * 1;
        temporal_f0_2 = jugador->colision.distancia_superficie[1] * parametro1[1];
        if (temporal_f0_2 < 0) {
            *parametro5 += temporal_f0_2 * 0.1;
        } else {
            *parametro5 += temporal_f0_2 * 0;
        }
        *parametro6 += parametro1[2] * jugador->colision.distancia_superficie[1] * 1;
        funcion_8002A5F4(parametro1, *parametro3, parametro2, 1.2f, 0);
        if ((!(jugador->efectos & EFECTO_VUELCO_TERRENO)) && ((jugador->efectos & EFECTO_EN_EL_AIRE) == 0)) {
            parametro2[1] *= -1e-05;
        }
    }
    jugador->efectos &= ~EFECTO_DERRAPANDO;
    temporal_f12 = jugador->colision.distancia_superficie[1] * parametro1[0];
    temporal_f14 = jugador->colision.distancia_superficie[1] * parametro1[2];
    if (((temporal_f12 >= 0) && (temporal_f14 >= 0)) || ((temporal_f12 >= 0) && (temporal_f14 < 0))) {
        temporal_f0_2 = jugador->tamanio_caja_envolvente / 2;
        jugador->desconocido_218 = *parametro4 - temporal_f12 - temporal_f0_2;
        jugador->desconocido_21C = *parametro6 - temporal_f14 - temporal_f0_2;
    }
    if (((temporal_f12 < 0) && (temporal_f14 >= 0)) || ((temporal_f12 < 0) && (temporal_f14 < 0))) {
        temporal_f0_2 = jugador->tamanio_caja_envolvente / 2;
        jugador->desconocido_218 = *parametro4 + temporal_f12 + temporal_f0_2;
        jugador->desconocido_21C = *parametro6 + temporal_f14 + temporal_f0_2;
    }
}
