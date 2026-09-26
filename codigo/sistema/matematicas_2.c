#include <ultra64.h>
#include <juego/macros.h>
#include <juego/estructuras_comunes.h>
#include "sistema/matematicas_2.h"
#include "sistema/bucle_principal.h"
#include "sistema/matematicas.h"
#include "juego/objetos.h"

#include "memoria/memoria_carrera.h"
#include "carrera/colision.h"
#include "graficos/dibujar_jugador.h"
#include "carrera/objetos_y_efectos.h"
#include "juego/definiciones.h"
#include "carrera/camara.h"

#pragma intrinsic(sqrtf)

SIN_USO void operador_o(s32* parametro0, s32 parametro1) {
    *parametro0 = (s32) (*parametro0 | parametro1);
}

SIN_USO void operador_y_no(s32* parametro0, s32 parametro1) {
    *parametro0 = (s32) (*parametro0 & ~parametro1);
}

SIN_USO void xor_operador(s32* parametro0, s32 parametro1) {
    *parametro0 = (s32) (*parametro0 ^ parametro1);
}

SIN_USO bool funcion_80040E84(s32* parametro0, s32 parametro1) {
    bool phi_v1;

    phi_v1 = false;
    if ((*parametro0 & parametro1) != 0) {
        phi_v1 = true;
    }
    return phi_v1;
}

SIN_USO s32 funcion_80040EA4(s32* parametro0, s32 parametro1) {
    s32 phi_v1;

    phi_v1 = 0;
    if ((*parametro0 & parametro1) == 0) {
        phi_v1 = 1;
    }
    return phi_v1;
}

void copiar_vec3f(Vec3f dest, Vec3f parametro1) {
    dest[0] = parametro1[0];
    dest[1] = parametro1[1];
    dest[2] = parametro1[2];
}

s32 arriba_paso_f32_hacia(f32* value, f32 objetivo, f32 paso) {
    s32 objetivo_alcanzado = 0;

    if (*value < objetivo) {
        *value += paso;
        if (objetivo <= *value) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    }
    return objetivo_alcanzado;
}

s32 abajo_paso_f32_hacia(f32* value, f32 objetivo, f32 paso) {
    s32 objetivo_alcanzado = 0;

    if (objetivo < *value) {
        *value -= paso;
        if (*value <= objetivo) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    }
    return objetivo_alcanzado;
}

s32 arriba_paso_s32_hacia(s32* value, s32 objetivo, s32 paso) {
    s32 objetivo_alcanzado = 0;

    if (*value < objetivo) {
        *value = *value + paso;
        objetivo_alcanzado = 0;
        if (*value >= objetivo) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    }
    return objetivo_alcanzado;
}

s32 abajo_paso_s32_hacia(s32* value, s32 objetivo, s32 paso) {
    s32 objetivo_alcanzado = 0;

    if (objetivo < *value) {
        *value = *value - paso;
        ;
        if (objetivo >= *value) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    }
    return objetivo_alcanzado;
}

s32 arriba_paso_s16_hacia(s16* value, s16 objetivo, s16 paso) {
    s32 objetivo_alcanzado = 0;

    if (*value < objetivo) {
        *value = *value + paso;
        if (*value >= objetivo) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    }
    return objetivo_alcanzado;
}

s32 arriba_paso_u16_hacia(u16* value, u16 objetivo, u16 paso) {
    s32 objetivo_alcanzado = 0;

    if (*value < objetivo) {
        *value += paso;
        if (*value >= objetivo) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    }
    return objetivo_alcanzado;
}

s32 abajo_paso_s16_hacia(s16* value, s16 objetivo, s16 paso) {
    s32 objetivo_alcanzado = 0;

    if (objetivo < *value) {
        *value -= paso;
        if (objetivo >= *value) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    }
    return objetivo_alcanzado;
}

s32 abajo_paso_u16_hacia(u16* value, s32 objetivo, s32 paso) {
    s32 objetivo_alcanzado = 0;
    s32 temporal_ = *value;

    if (objetivo < temporal_) {
        temporal_ -= paso;
        if (objetivo >= temporal_) {
            temporal_ = objetivo;
            objetivo_alcanzado = 1;
        }
        *value = temporal_;
    }
    return objetivo_alcanzado;
}

SIN_USO s32 arriba_paso_f32_hacia_alternativo(f32* value, f32 objetivo, f32* paso) {
    s32 objetivo_alcanzado = 0;

    if (*value < objetivo) {
        *value += *paso;
        if (objetivo <= *value) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    }
    return objetivo_alcanzado;
}

SIN_USO s32 abajo_paso_f32_hacia_alternativo(f32* value, f32 objetivo, f32* paso) {
    s32 objetivo_alcanzado = 0;

    if (objetivo < *value) {
        *value -= *paso;
        if (*value <= objetivo) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    }
    return objetivo_alcanzado;
}

SIN_USO s32 arriba_paso_s32_hacia_alternativo(s32* value, s32 objetivo, s32* paso) {
    s32 objetivo_alcanzado = 0;

    if (*value < objetivo) {
        *value += *paso;
        if (*value >= objetivo) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    }
    return objetivo_alcanzado;
}

SIN_USO s32 abajo_paso_s32_hacia_alternativo(s32* value, s32 objetivo, s32* paso) {
    s32 objetivo_alcanzado = 0;

    if (objetivo < *value) {
        *value -= *paso;
        if (objetivo >= *value) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    }
    return objetivo_alcanzado;
}

SIN_USO s32 arriba_paso_s16_hacia_alternativo(s16* value, s16 objetivo, s16* paso) {
    s32 objetivo_alcanzado = 0;

    if (*value < objetivo) {
        *value += *paso;
        if (*value >= objetivo) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    }
    return objetivo_alcanzado;
}

SIN_USO s32 abajo_paso_s16_hacia_alternativo(s16* value, s16 objetivo, s16* paso) {
    s32 objetivo_alcanzado = 0;

    if (objetivo < *value) {
        *value -= *paso;
        if (objetivo >= *value) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    }
    return objetivo_alcanzado;
}

s32 paso_s16_hacia(s16* value, s16 objetivo, s16 paso) {
    s32 objetivo_alcanzado = 0;

    if (*value < objetivo) {
        if (paso >= 0) {
            *value += paso;
        } else {
            *value -= paso;
        }
        if (*value >= objetivo) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    } else if (objetivo < *value) {
        if (paso >= 0) {
            *value -= paso;
        } else {
            *value += paso;
        }
        if (objetivo >= *value) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    }
    return objetivo_alcanzado;
}

SIN_USO s32 paso_s32_hacia(s32* value, s32 objetivo, s32 paso) {
    s32 temporal_v0;
    s32 objetivo_alcanzado;

    temporal_v0 = *value;
    objetivo_alcanzado = 0;
    if (temporal_v0 < objetivo) {
        if (paso >= 0) {
            *value = (s32) (temporal_v0 + paso);
        } else {
            *value = (s32) (temporal_v0 - paso);
        }
        if (*value >= objetivo) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }

    } else if (objetivo < temporal_v0) {
        if (paso >= 0) {
            *value = (s32) (temporal_v0 - paso);
        } else {
            *value = (s32) (temporal_v0 + paso);
        }
        if (objetivo >= *value) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    }
    return objetivo_alcanzado;
}

s32 paso_f32_hacia(f32* value, f32 objetivo, f32 paso) {
    s32 objetivo_alcanzado = 0;

    if (*value < objetivo) {
        if (paso >= 0.0f) {
            *value += paso;
        } else {
            *value -= paso;
        }
        if (objetivo <= *value) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    } else if (objetivo < *value) {
        if (paso >= 0.0f) {
            *value -= paso;
        } else {
            *value += paso;
        }
        if (*value <= objetivo) {
            *value = objetivo;
            objetivo_alcanzado = 1;
        }
    }
    return objetivo_alcanzado;
}

void funcion_80041480(s16* parametro0, s16 parametro1, s16 parametro2, s16* parametro3) {
    *parametro0 += *parametro3;
    if (*parametro3 >= 0) {
        if (*parametro0 >= parametro2) {
            *parametro0 = parametro2;
            *parametro3 = -*parametro3;
        }
    } else if (parametro1 >= *parametro0) {
        *parametro0 = parametro1;
        *parametro3 = -*parametro3;
    }
}

Vec3f* fijar_xyz_vec3f(Vec3f parametro0, f32 parametro1, f32 parametro2, f32 parametro3) {
    parametro0[0] = parametro1;
    parametro0[1] = parametro2;
    parametro0[2] = parametro3;
    return (Vec3f*) &parametro0;
}

Vec3f* normalizar_vec3f(Vec3f dest) {
    f32 invsqrt = 1.0f / sqrtf(dest[0] * dest[0] + dest[1] * dest[1] + dest[2] * dest[2]);

    dest[0] = dest[0] * invsqrt;
    dest[1] = dest[1] * invsqrt;
    dest[2] = dest[2] * invsqrt;
    return (Vec3f*) &dest;
}

Vec3f* producto_cruce_vec3f(Vec3f dest, Vec3f parametro1, Vec3f parametro2) {

    dest[0] = (parametro1[1] * parametro2[2]) - (parametro2[1] * parametro1[2]);
    dest[1] = (parametro1[2] * parametro2[0]) - (parametro2[2] * parametro1[0]);
    dest[2] = (parametro1[0] * parametro2[1]) - (parametro2[0] * parametro1[1]);

    return (Vec3f*) &dest;
}

SIN_USO s32 es_dentro_distancia_2d(f32 x1, f32 y1, f32 x2, f32 y2, f32 distancia) {
    f32 x;
    f32 y;
    s32 devuelto = 0;

    x = x2 - x1;
    y = y2 - y1;
    if (((x * x) + (y * y)) <= (distancia * distancia)) {
        devuelto = 1;
    }
    return devuelto;
}

s32 funcion_80041658(f32 parametro0, f32 parametro1) {
    return -atan2s(parametro0, parametro1) & 0xFFFF;
}

SIN_USO s32 funcion_80041680(f32 parametro0, f32 parametro1) {
    return atan2s(parametro1, parametro0);
}

SIN_USO s32 funcion_800416AC(f32 parametro0, f32 parametro1) {
    return atan2s(parametro1, parametro0);
}

f32 funcion_800416D8(f32 x, f32 z, u16 angulo) {
    f32 angulo_cos;

    angulo_cos = coss(angulo);
    return (angulo_cos * x) - (senos(angulo) * z);
}

f32 funcion_80041724(f32 x, f32 z, u16 angulo) {
    f32 angulo_sen;

    angulo_sen = senos(angulo);
    return (coss(angulo) * z) + (angulo_sen * x);
}

s32 obtener_angulo_entre_xy(f32 x1, f32 x2, f32 y1, f32 y2) {
    return atan2s(x2 - x1, y2 - y1);
}

u16 funcion_800417B4(u16 angulo1, u16 angulo2) {
    u16 angulo_salida;

    if ((angulo1 >> 8) != (angulo2 >> 8)) {
        angulo_salida = angulo2 - angulo1;
        if (angulo_salida < 0x400) {
            angulo_salida = angulo1 + 0x80;
        } else if (angulo_salida < 0x800) {
            angulo_salida = angulo1 + 0x200;
        } else if (angulo_salida < 0x4000) {
            angulo_salida = angulo1 + 0x400;
        } else if (angulo_salida < 0x8000) {
            angulo_salida = angulo1 + 0x700;
        } else if (angulo_salida < 0xC000) {
            angulo_salida = angulo1 - 0x700;
        } else if (angulo_salida < 0xF800) {
            angulo_salida = angulo1 - 0x400;
        } else if (angulo_salida < 0xFC00) {
            angulo_salida = angulo1 - 0x200;
        } else {
            angulo_salida = angulo1 - 0x80;
        }
    } else {
        angulo_salida = angulo2;
    }
    return angulo_salida;
}

s32 funcion_800418AC(f32 parametro0, f32 parametro1, Vec3f parametro2) {
    return atan2s(parametro0 - parametro2[0], parametro1 - parametro2[2]);
}

s32 funcion_800418E8(f32 parametro0, f32 parametro1, Vec3f parametro2) {
    return atan2s(parametro0 - parametro2[1], parametro1 - parametro2[2]);
}

s32 funcion_80041924(Colision* parametro0, Vec3f parametro1) {
    s32 devuelto = 0;

    comprobar_colision_envolvente(parametro0, 10.0f, parametro1[0], parametro1[1], parametro1[2]);
    if (parametro0->unk34 == 1) {
        devuelto = 1;
    }
    return devuelto;
}

bool es_particula_en_pantalla(Vec3f parametro0, Camara* parametro1, u16 parametro2) {
    u16 temporal_t9;
    s32 devuelto;

    devuelto = false;
    temporal_t9 = (obtener_angulo_entre_xy(parametro1->pos[0], parametro0[0], parametro1->pos[2], parametro0[2]) + (parametro2 / 2)) - parametro1->rot[1];
    if ((temporal_t9 >= 0) && (parametro2 >= temporal_t9)) {
        devuelto = true;
    }
    return devuelto;
}

void funcion_800419F8(void) {
    Vec3f pos;
    Vec3f vec;

    pos[0] = 0.0f;
    pos[1] = 0.0f;
    pos[2] = 120.0f;
    rotar_x_y_vec3f(vec, pos, (s16*) dato_80165834);
    dato_80165840[0] = vec[0];
    dato_80165840[1] = vec[1];
    dato_80165840[2] = vec[2];
}

SIN_USO void funcion_80041A70(void) {
}

void traslacion_x_y_mtfx(Mat4 parametro0, s32 x, s32 y) {
    parametro0[0][0] = 1.0f;
    parametro0[1][1] = 1.0f;
    parametro0[2][2] = 1.0f;
    parametro0[1][0] = 0.0f;
    parametro0[2][0] = 0.0f;
    parametro0[0][1] = 0.0f;
    parametro0[3][0] = x;
    parametro0[2][1] = 0.0f;
    parametro0[0][2] = 0.0f;
    parametro0[1][2] = 0.0f;
    parametro0[3][2] = 0.0f;
    parametro0[3][1] = y;
    parametro0[0][3] = 0.0f;
    parametro0[1][3] = 0.0f;
    parametro0[2][3] = 0.0f;
    parametro0[3][3] = 1.0f;

}

void rotar_z_mtxf_u16(Mat4 dest, u16 angulo) {
    f32 theta_sen = senos(angulo);
    f32 cos_theta = coss(angulo);

    dest[0][0] = cos_theta;
    dest[1][0] = -theta_sen;
    dest[1][1] = cos_theta;
    dest[0][1] = theta_sen;
    dest[2][0] = 0.0f;
    dest[3][0] = 0.0f;
    dest[2][1] = 0.0f;
    dest[3][1] = 0.0f;
    dest[0][2] = 0.0f;
    dest[1][2] = 0.0f;
    dest[3][2] = 0.0f;
    dest[0][3] = 0.0f;
    dest[1][3] = 0.0f;
    dest[2][3] = 0.0f;
    dest[2][2] = 1.0f;
    dest[3][3] = 1.0f;
}

void escalar_x_y_mtxf(Mat4 dest, f32 escalar) {
    dest[1][0] = 0.0f;
    dest[2][0] = 0.0f;
    dest[3][0] = 0.0f;
    dest[0][1] = 0.0f;
    dest[2][1] = 0.0f;
    dest[3][1] = 0.0f;
    dest[0][2] = 0.0f;
    dest[1][2] = 0.0f;
    dest[3][2] = 0.0f;
    dest[0][3] = 0.0f;
    dest[1][3] = 0.0f;
    dest[2][3] = 0.0f;
    dest[2][2] = 1.0f;
    dest[3][3] = 1.0f;
    dest[0][0] = escalar;
    dest[1][1] = escalar;
}

SIN_USO void rotar_escala_x_y_z_mtxf(Mat4 dest, u16 angulo, f32 escalar) {
    f32 theta_sen = senos(angulo);
    f32 cos_theta = coss(angulo) * escalar;

    dest[2][0] = 0.0f;
    dest[0][0] = cos_theta;
    dest[1][1] = cos_theta;
    dest[2][1] = 0.0f;
    dest[1][0] = -theta_sen * escalar;
    dest[0][2] = 0.0f;
    dest[1][2] = 0.0f;
    dest[0][1] = theta_sen * escalar;
    dest[3][2] = 0.0f;
    dest[0][3] = 0.0f;
    dest[1][3] = 0.0f;
    dest[2][3] = 0.0f;
    dest[3][0] = 1.0f;
    dest[3][1] = 1.0f;
    dest[2][2] = 1.0f;
    dest[3][3] = 1.0f;
}

void rotar_escala_x_y_z_traslacion_x_y_mtxf(Mat4 dest, s32 x, s32 y, u16 angulo, f32 escalar) {
    f32 theta_sen = senos(angulo);
    f32 cos_theta = coss(angulo) * escalar;

    dest[2][0] = 0.0f;
    dest[0][0] = cos_theta;
    dest[1][0] = (-theta_sen) * escalar;
    dest[3][0] = (f32) x;
    dest[1][1] = cos_theta;
    dest[0][1] = theta_sen * escalar;
    dest[2][1] = 0.0f;
    dest[3][1] = (f32) y;
    dest[0][2] = 0.0f;
    dest[1][2] = 0.0f;
    dest[2][2] = 1.0f;
    dest[3][3] = 1.0f;
    dest[3][2] = 0.0f;
    dest[0][3] = 0.0f;
    dest[1][3] = 0.0f;
    dest[2][3] = 0.0f;
}

void funcion_80041D24(void) {
    dato_801658FE = 1;
}

void guOrtho(Mtx*, f32, f32, f32, f32, f32, f32, f32);
extern s8 dato_801658FE;

void funcion_80041D34(void) {
    guOrtho(&dato_80183D60, 0.0f, 320.0f, 240.0f, 0.0f, -1.0f, 1.0f, 1.0f);
    switch (modo_pantalla_activo) {
        case MODO_PANTALLA_1P:
            guOrtho(&gfx_pool->orto_mtx, 0.0f, 320.0f, 240.0f, 0.0f, -1.0f, 1.0f, 1.0f);
            break;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            guOrtho(&gfx_pool->orto_mtx, 0.0f, 160.0f, 120.0f, 0.0f, -1.0f, 1.0f, 1.0f);
            break;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
            if (dato_801658FE == 0) {
                guOrtho(&gfx_pool->orto_mtx, 0.0f, 320.0f, 120.0f, 0.0f, -1.0f, 1.0f, 1.0f);
            } else {
                guOrtho(&gfx_pool->orto_mtx, 0.0f, 320.0f, 240.0f, 0.0f, -1.0f, 1.0f, 1.0f);
            }
            break;
        case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
            guOrtho(&gfx_pool->orto_mtx, 0.0f, 320.0f, 240.0f, 0.0f, -1.0f, 1.0f, 1.0f);
            break;
    }
}

void fijar_pantalla_hud_matriz(void) {
    gDPSetTexturePersp(display_list_cabeza++, G_TP_PERSP);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->orto_mtx),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
}

SIN_USO void funcion_80041F54(s32 x, s32 y) {
    Mat4 matriz;

    traslacion_x_y_mtfx(matriz, x, y);
    convertir_a_matriz_punto_fijo(&gfx_pool->mtx_hud[cantidad_hud_matriz], matriz);

    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}

SIN_USO void funcion_80042000(u16 angulo_z) {
    Mat4 matriz;

    rotar_z_mtxf_u16(matriz, angulo_z);
    convertir_a_matriz_punto_fijo(&gfx_pool->mtx_hud[cantidad_hud_matriz], matriz);

    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}

SIN_USO void funcion_800420A8(f32 escalar) {
    Mat4 matriz;

    escalar_x_y_mtxf(matriz, escalar);
    convertir_a_matriz_punto_fijo(&gfx_pool->mtx_hud[cantidad_hud_matriz], matriz);

    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}

SIN_USO void funcion_8004214C(u16 angulo, f32 escalar) {
    Mat4 matriz;

    rotar_escala_x_y_z_mtxf(matriz, angulo, escalar);
    convertir_a_matriz_punto_fijo(&gfx_pool->mtx_hud[cantidad_hud_matriz], matriz);

    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}

SIN_USO void funcion_800421FC(s32 x, s32 y, f32 escalar) {
    Mat4 matriz;

    traslacion_x_y_mtfx(matriz, x, y);
    convertir_a_matriz_punto_fijo(&gfx_pool->mtx_hud[cantidad_hud_matriz], matriz);

    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    escalar_x_y_mtxf(matriz, escalar);
    convertir_a_matriz_punto_fijo(&gfx_pool->mtx_hud[cantidad_hud_matriz], matriz);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
              G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
}

void funcion_80042330(s32 x, s32 y, u16 angulo, f32 escalar) {
    Mat4 matriz;
    rotar_escala_x_y_z_traslacion_x_y_mtxf(matriz, x, y, angulo, escalar);
    convertir_a_matriz_punto_fijo(&gfx_pool->mtx_hud[cantidad_hud_matriz], matriz);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}

SIN_USO void funcion_800423F0(Mat4 parametro0, u16 parametro1, u16 parametro2, u16 parametro3) {
    f32 sp3_c;
    f32 temporal_f20;
    f32 sp34;
    f32 sp30;
    f32 sp2_c;
    f32 temporal_f0;

    sp3_c = senos(parametro1);
    temporal_f20 = coss(parametro1);
    sp34 = senos(parametro2);
    sp30 = coss(parametro2);
    sp2_c = senos(parametro3);
    temporal_f0 = coss(parametro3);

    parametro0[0][0] = (f32) (sp30 * temporal_f0 + (sp3_c * sp34 * sp2_c));
    parametro0[1][0] = (f32) ((-sp30 * sp2_c) + (sp3_c * sp34 * temporal_f0));
    parametro0[2][0] = (f32) (temporal_f20 * sp34);
    parametro0[3][0] = 0.0f;
    parametro0[0][1] = (f32) (temporal_f20 * sp2_c);
    parametro0[1][1] = (f32) (temporal_f20 * temporal_f0);
    parametro0[2][1] = (f32) -sp3_c;
    parametro0[3][1] = 0.0f;
    parametro0[0][2] = (f32) ((-sp34 * temporal_f0) + (sp3_c * sp30 * sp2_c));
    parametro0[1][2] = (f32) ((sp34 * sp2_c) + (sp3_c * sp30 * temporal_f0));
    parametro0[2][2] = (f32) (temporal_f20 * sp30);
    parametro0[3][2] = 0.0f;
    parametro0[0][3] = 0.0f;
    parametro0[1][3] = 0.0f;
    parametro0[2][3] = 0.0f;
    parametro0[3][3] = 1.0f;
}

SIN_USO void funcion_8004252C(Mat4 parametro0, u16 parametro1, u16 parametro2) {
    f32 sp2_c = senos(parametro1);
    f32 sp28 = coss(parametro1);
    f32 theta_y_sen = senos(parametro2);
    f32 cos_theta_y = coss(parametro2);

    parametro0[1][0] = sp2_c * theta_y_sen;
    parametro0[2][0] = sp28 * theta_y_sen;
    parametro0[0][1] = 0.0f;
    parametro0[0][0] = cos_theta_y;
    parametro0[2][1] = -sp2_c;
    parametro0[0][2] = -theta_y_sen;
    parametro0[1][1] = sp28;
    parametro0[1][2] = sp2_c * cos_theta_y;
    parametro0[2][2] = sp28 * cos_theta_y;
}

void fijar_transformacion_matriz_mtxf(Mat4 transformar_matriz, Vec3f vector_traslacion, Vec3su vector_rotacion,
                                    f32 factor_escalado) {
    f32 sen_x = senos(vector_rotacion[0]);
    f32 cos_x = coss(vector_rotacion[0]);
    f32 sen_y = senos(vector_rotacion[1]);
    f32 cos_y = coss(vector_rotacion[1]);
    f32 sen_z = senos(vector_rotacion[2]);
    f32 cos_z = coss(vector_rotacion[2]);

    transformar_matriz[0][0] = ((cos_y * cos_z) + (sen_x * sen_y * sen_z)) * factor_escalado;
    transformar_matriz[1][0] = ((-cos_y * sen_z) + (sen_x * sen_y * cos_z)) * factor_escalado;
    transformar_matriz[2][0] = (cos_x * sen_y) * factor_escalado;
    transformar_matriz[3][0] = vector_traslacion[0];
    transformar_matriz[0][1] = cos_x * sen_z * factor_escalado;
    transformar_matriz[1][1] = cos_x * cos_z * factor_escalado;
    transformar_matriz[2][1] = -sen_x * factor_escalado;
    transformar_matriz[3][1] = vector_traslacion[1];
    transformar_matriz[0][2] = ((-sen_y * cos_z) + (sen_x * cos_y * sen_z)) * factor_escalado;
    transformar_matriz[1][2] = ((sen_y * sen_z) + (sen_x * cos_y * cos_z)) * factor_escalado;
    transformar_matriz[2][2] = cos_x * cos_y * factor_escalado;
    transformar_matriz[3][2] = vector_traslacion[2];
    transformar_matriz[0][3] = 0.0f;
    transformar_matriz[1][3] = 0.0f;
    transformar_matriz[2][3] = 0.0f;
    transformar_matriz[3][3] = 1.0f;
}

void fijar_trasl_escala_matriz_mtxf(Mat4 transformar_matriz, Vec3f vec1, Vec3f vec2, f32 escalar) {
    transformar_matriz[0][0] = escalar;
    transformar_matriz[1][0] = 0.0f;
    transformar_matriz[2][0] = 0.0f;
    transformar_matriz[3][0] = vec1[0] - vec2[0];
    transformar_matriz[0][1] = 0.0f;
    transformar_matriz[1][1] = -escalar;
    transformar_matriz[2][1] = 0.0f;
    transformar_matriz[3][1] = vec1[1] - vec2[1];
    transformar_matriz[0][2] = 0.0f;
    transformar_matriz[1][2] = 0.0f;
    transformar_matriz[2][2] = -escalar;
    transformar_matriz[3][2] = vec1[2] - vec2[2];
    transformar_matriz[0][3] = 0.0f;
    transformar_matriz[1][3] = 0.0f;
    transformar_matriz[2][3] = 0.0f;
    transformar_matriz[3][3] = 1.0f;
}

void mtxf_conjunto_matriz_g_objeto_lista(s32 indice_objeto, Mat4 transformar_matriz) {
    f32 sen_x;
    Objeto* objeto = &lista_objeto[indice_objeto];
    f32 sen_y;
    f32 cos_y;
    f32 sen_z;
    f32 cos_z;
    f32 cos_x;

    sen_x = senos(objeto->orientacion[0]);
    cos_x = coss(objeto->orientacion[0]);
    sen_y = senos(objeto->orientacion[1]);
    cos_y = coss(objeto->orientacion[1]);
    sen_z = senos(objeto->orientacion[2]);
    cos_z = coss(objeto->orientacion[2]);

    transformar_matriz[0][0] = objeto->escalado_tamanio * ((cos_y * cos_z) + (sen_x * sen_y * sen_z));
    transformar_matriz[1][0] = objeto->escalado_tamanio * ((-cos_y * sen_z) + sen_x * sen_y * cos_z);
    transformar_matriz[2][0] = objeto->escalado_tamanio * (cos_x * sen_y);
    transformar_matriz[3][0] = objeto->pos[0];
    transformar_matriz[0][1] = objeto->escalado_tamanio * (cos_x * sen_z);
    transformar_matriz[1][1] = objeto->escalado_tamanio * (cos_x * cos_z);
    transformar_matriz[2][1] = objeto->escalado_tamanio * -sen_x;
    transformar_matriz[3][1] = objeto->pos[1];
    transformar_matriz[0][2] = objeto->escalado_tamanio * ((-sen_y * cos_z) + (sen_x * cos_y * sen_z));
    transformar_matriz[1][2] = objeto->escalado_tamanio * ((sen_y * sen_z) + (sen_x * cos_y * cos_z));
    transformar_matriz[2][2] = objeto->escalado_tamanio * (cos_x * cos_y);
    transformar_matriz[3][2] = objeto->pos[2];
    transformar_matriz[0][3] = 0.0f;
    transformar_matriz[1][3] = 0.0f;
    transformar_matriz[2][3] = 0.0f;
    transformar_matriz[3][3] = 1.0f;
}

SIN_USO void mtxf_multiplicar_primer_columna(Mat4 parametro0, f32 parametro1) {
    parametro0[0][0] *= parametro1;
    parametro0[1][0] *= parametro1;
    parametro0[2][0] *= parametro1;
}

SIN_USO void mtxf_multiplicar_segundo_columna(Mat4 parametro0, f32 parametro1) {
    parametro0[0][1] *= parametro1;
    parametro0[1][1] *= parametro1;
    parametro0[2][1] *= parametro1;
}

SIN_USO void mtxf_multiplicar_tercer_columna(Mat4 parametro0, f32 parametro1) {
    parametro0[0][2] *= parametro1;
    parametro0[1][2] *= parametro1;
    parametro0[2][2] *= parametro1;
}

void transformar_matriz_conjunto(Mat4 dest, Vec3f vector_orientacion, Vec3f vector_posicion, u16 angulo_rotacion,
                          f32 escalar_factor) {
    Vec3f sp44;
    Vec3f sp38;
    Vec3f sp2_c;

    fijar_xyz_vec3f(sp44, senos(angulo_rotacion), 0.0f, coss(angulo_rotacion));
    normalizar_vec3f(vector_orientacion);
    producto_cruce_vec3f(sp38, vector_orientacion, sp44);
    normalizar_vec3f(sp38);
    producto_cruce_vec3f(sp2_c, sp38, vector_orientacion);
    normalizar_vec3f(sp2_c);
    dest[0][0] = sp38[0] * escalar_factor;
    dest[0][1] = sp38[1] * escalar_factor;
    dest[0][2] = sp38[2] * escalar_factor;
    dest[3][0] = vector_posicion[0];
    dest[1][0] = vector_orientacion[0] * escalar_factor;
    dest[1][1] = vector_orientacion[1] * escalar_factor;
    dest[1][2] = vector_orientacion[2] * escalar_factor;
    dest[3][1] = vector_posicion[1];
    dest[2][0] = sp2_c[0] * escalar_factor;
    dest[2][1] = sp2_c[1] * escalar_factor;
    dest[2][2] = sp2_c[2] * escalar_factor;
    dest[3][2] = vector_posicion[2];
    dest[0][3] = 0.0f;
    dest[1][3] = 0.0f;
    dest[2][3] = 0.0f;
    dest[3][3] = 1.0f;
}

SIN_USO void rotar_vec3f(Vec3f dest, Vec3f pos, Vec3s rot) {
    f32 sp74;
    f32 sp70;
    f32 sp6_c;
    f32 temporal_f4;
    f32 sp64;
    f32 sp60;
    f32 temporal_f8;
    f32 sp58;
    f32 sp54;
    f32 seno1;
    f32 coseno1;
    f32 seno2;
    f32 coseno2;
    f32 seno3;
    f32 coseno3;

    seno1 = senos(rot[0]);
    coseno1 = coss(rot[0]);
    seno2 = senos(rot[1]);
    coseno2 = coss(rot[1]);
    seno3 = senos(rot[2]);
    coseno3 = coss(rot[2]);
    sp74 = pos[0] * ((coseno2 * coseno3) + ((seno1 * seno2) * seno3));
    temporal_f4 = pos[1] * ((-coseno2 * seno3) + ((seno1 * seno2) * coseno3));
    temporal_f8 = pos[2] * (coseno1 * seno2);
    sp70 = pos[0] * (coseno1 * seno3);
    sp64 = pos[1] * (coseno1 * coseno3);
    sp58 = pos[2] * -seno1;
    sp6_c = pos[0] * ((-seno2 * coseno3) + ((seno1 * coseno2) * seno3));
    sp60 = pos[1] * ((seno2 * seno3) + ((seno1 * coseno2) * coseno3));
    sp54 = pos[2] * (coseno1 * coseno2);
    dest[0] = sp74 + temporal_f4 + temporal_f8;
    dest[1] = sp70 + sp64 + sp58;
    dest[2] = sp6_c + sp60 + sp54;
}

void rotar_x_y_vec3f(Vec3f dest, Vec3f pos, Vec3s rot) {
    f32 sp2_c;
    f32 sp28;
    f32 sp24;
    f32 seno1;
    f32 coseno1;
    f32 seno2;
    f32 coseno2;

    sp2_c = pos[0];
    sp28 = pos[1];
    sp24 = pos[2];
    seno1 = senos(rot[0]);
    coseno1 = coss(rot[0]);
    seno2 = senos(rot[1]);
    coseno2 = coss(rot[1]);
    dest[0] = (sp2_c * coseno2) - (sp24 * seno2);
    dest[1] = (sp2_c * seno1 * seno2) + (sp28 * coseno1) + (sp24 * seno1 * coseno2);
    dest[2] = ((sp2_c * coseno1 * seno2) - (sp28 * seno1)) + (sp24 * coseno1 * coseno2);
}

void fijar_transformacion_matriz_rsp(Vec3f trasladar, Vec3su orientacion, f32 escalar) {
    Mat4 matriz;

    fijar_transformacion_matriz_mtxf(matriz, trasladar, orientacion, escalar);
    convertir_a_matriz_punto_fijo(&gfx_pool->mtx_hud[cantidad_hud_matriz], matriz);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}

SIN_USO void fijar_matriz_dif_traslacion_escala_rsp(Vec3f pos1, Vec3f pos2, f32 escalar) {
    Mat4 matriz;

    fijar_trasl_escala_matriz_mtxf(matriz, pos1, pos2, escalar);
    convertir_a_matriz_punto_fijo(&gfx_pool->mtx_hud[cantidad_hud_matriz], matriz);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}

void fijar_matriz_transformacion_invertido_x_y_orientacion_rsp(Vec3f parametro0, Vec3su parametro1, f32 parametro2) {
    Mat4 matriz;
    Vec3su orientacion;

    orientacion[0] = parametro1[0] + 0x8000;
    orientacion[1] = parametro1[1] + 0x8000;
    orientacion[2] = parametro1[2];
    fijar_transformacion_matriz_mtxf(matriz, parametro0, orientacion, parametro2);
    convertir_a_matriz_punto_fijo(&gfx_pool->mtx_hud[cantidad_hud_matriz], matriz);

    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}

void fijar_matriz_trasl_rot_escala_rsp(Vec3f parametro0, Vec3f parametro1, f32 parametro2) {
    Mat4 matriz;

    transformar_matriz_conjunto(matriz, parametro1, parametro0, 0, parametro2);
    convertir_a_matriz_punto_fijo(&gfx_pool->mtx_hud[cantidad_hud_matriz], matriz);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}

void rsp_conjunto_matriz_g_objeto_lista(s32 transformar_indice) {
    Mat4 matriz;

    mtxf_conjunto_matriz_g_objeto_lista(transformar_indice, matriz);
    convertir_a_matriz_punto_fijo(&gfx_pool->mtx_hud[cantidad_hud_matriz], matriz);

    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}
