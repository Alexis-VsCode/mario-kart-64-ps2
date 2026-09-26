#include <ultra64.h>
#include <juego/macros.h>
#include <PR/gu.h>
#include <juego/mk64.h>
#include <depuracion/depuracion_juego.h>
#include <juego/estructuras_comunes.h>
#include "sistema/bucle_principal.h"
#include "memoria/memoria_carrera.h"
#include <recursos/datos_comunes.h>
#include "graficos/dibujar_jugador.h"
#include "graficos/dibujar_objetos.h"
#include "ceremonia/actores_podio.h"
#include "ceremonia/camara_ceremonia.h"
#include "carrera/control_jugador.h"
#include "carrera/objetos_y_efectos.h"
#include "carrera/ia_vehiculos_y_camara.h"
#include "ceremonia/dibujar_podio.h"
#include "sistema/matematicas.h"

s32 color_cono_fuego_artificial[] = {
    0x00FF4080,
    0x008040FF,
    0x0040FF40,
    0x00FFFF40
};

s32 color_fuego_artificial[] = {
    0x007F2040,
    0x0040207F,
    0x00207F20,
    0x007F7F20
};

u16 s_aleatorio_semilla_16 = 0;

ParamsInicializacionActor inicializar_globo_2 = {
    Globo, { 0xF3AF, 34, 0xFE2D }, 0, 0, 0, 0,
};

ParamsInicializacionActor inicializar_rafaga = {
    RafagaFuegoArtificial, { 0xF3AF, 34, 0xFE2D }, 0, 0, 0, 0,
};

ParamsInicializacionActor inicializar_cono = {
    ConoFuegoArtificial, { 0xF3AF, 34, 0xFE2D }, 0, 0, 0, 0,
};

ParamsInicializacionActor inicializar_ficticio = {
    Inicial, { 0xF2CC, 250, 0xFE11 }, 0, 0, 0, 0,
};

s16 dato_802874B0[17];

Gfx* dato_802874D4;

struct_d_802874D8 dato_802874D8;

// s32 sActorTimer

ActorCeremonia* lista_actor_podio;
s32 dato_802874FC;

void funcion_80280650(void) {
}

void fijar_posicion_inicial(ActorCeremonia* actor) {
    ParamsInicializacionActor* params = actor->params_inicializacion;

    actor->pos[0] = params->desconocido2[0];
    actor->pos[1] = params->desconocido2[1];
    actor->pos[2] = params->desconocido2[2];

    actor->desconocido_a = params->desconocido8 << 8;
    actor->desconocido_c = params->desconocido9 << 8;
    actor->desconocido_e = params->desconocido_a << 8;
    actor->type = params->type;
}

ActorCeremonia* buscar_entrada_disponible(void) {
    SIN_USO s32 relleno[2];
    ActorCeremonia* actor = lista_actor_podio;
    s32 i;

    for (i = 0; i < 200; i++) {

        if ((actor->activo_es & 1) == 0) {
            bzero(actor, sizeof(ActorCeremonia));
            actor->activo_es = 1;
            actor->unk24 = 1.0f;
            return actor;
        }

        actor++;
    }
    return NULL;
}

ActorCeremonia* actor_nuevo(ParamsInicializacionActor* parametro0) {
    ActorCeremonia* actor = buscar_entrada_disponible();

#ifdef AVOID_UB
    if (actor == NULL) {
        return (ActorCeremonia*) &lista_actor_podio[0];
    }
#endif

    actor->params_inicializacion = parametro0;
    fijar_posicion_inicial(actor);
    return actor;
}

u16 creditos_aleatorio_u16(void) {
    u16 temporal1, temporal2;

    if (s_aleatorio_semilla_16 == 22026) {
        s_aleatorio_semilla_16 = 0;
    }

    temporal1 = (s_aleatorio_semilla_16 & 0x00FF) << 8;
    temporal1 = temporal1 ^ s_aleatorio_semilla_16;

    s_aleatorio_semilla_16 = ((temporal1 & 0x00FF) << 8) + ((temporal1 & 0xFF00) >> 8);

    temporal1 = ((temporal1 & 0x00FF) << 1) ^ s_aleatorio_semilla_16;
    temporal2 = (temporal1 >> 1) ^ 0xFF80;

    if ((temporal1 & 1) == 0) {
        if (temporal2 == 43605) {
            s_aleatorio_semilla_16 = 0;
        } else {
            s_aleatorio_semilla_16 = temporal2 ^ 0x1FF4;
        }
    } else {
        s_aleatorio_semilla_16 = temporal2 ^ 0x8180;
    }

    return s_aleatorio_semilla_16;
}

f32 flotante_aleatorio_entre_0_y_1(void) {
    return creditos_aleatorio_u16() / 65536.0f;
}

f32 sabe_quien_aleatorio(f32 parametro0) {
    return (flotante_aleatorio_entre_0_y_1() * parametro0) - (parametro0 * 0.5f);
}

void funcion_80280884(void) {
}

void actualizar_globo(ActorCeremonia* actor) {
    renderizar_globo(actor->pos, 1.0f, actor->desconocido_2e, actor->desconocido_2c);
    actor->pos[1] += 0.8f;
    actor->desconocido_2e = senos(actor->desconocido30) * actor->unk34;
    actor->desconocido30 += actor->desconocido32;
    actor->temporizador++;

    if (actor->temporizador > 800) {
        actor->activo_es = 0;
    }
    if (dato_802874B0[13] == 1) {
        actor->activo_es = 0;
    }
}

void actualizar_y_rafaga_aparicion_cono_fuego_artificial(FuegoArtificial* cono) {
    if (cono->desconocido44 < 30) {
        cono->pos[1] += 2.5f;
        cono->pos[0] += sabe_quien_aleatorio(0.2f);
        cono->pos[2] += sabe_quien_aleatorio(0.2f);
    } else if (cono->desconocido_2c == 4) {
        FuegoArtificial* rafaga = (FuegoArtificial*) actor_nuevo(&inicializar_cono);
        rafaga->pos[0] = cono->pos[0];
        rafaga->pos[1] = cono->pos[1];
        rafaga->pos[2] = cono->pos[2];
        rafaga->desconocido30 = color_cono_fuego_artificial[cono->desconocido48];
        rafaga->desconocido_3c = 0xFF;
        rafaga->desconocido40 = -0x11;
        rafaga->desconocido44 = 0x64;
        rafaga->unk34 = 1.8700001f;
        rafaga->unk38 = 1.8700001f;
    }
}

Mat4 dato_80287500;

void funcion_80280A28(Vec3f parametro0, Vec3s parametro1, f32 parametro2) {
    Mat4 mtx;

    trasladar_rotacion_mtxf(mtx, parametro0, parametro1);
    mtx[0][0] = dato_80287500[0][0] * parametro2;
    mtx[0][1] = dato_80287500[1][0] * parametro2;
    mtx[0][2] = dato_80287500[2][0] * parametro2;
    mtx[1][0] = dato_80287500[0][1] * parametro2;
    mtx[1][1] = dato_80287500[1][1] * parametro2;
    mtx[1][2] = dato_80287500[2][1] * parametro2;
    mtx[2][0] = dato_80287500[0][2] * parametro2;
    mtx[2][1] = dato_80287500[1][2] * parametro2;
    mtx[2][2] = dato_80287500[2][2] * parametro2;
    convertir_a_matriz_punto_fijo(&gfx_pool->efecto_mtx[cantidad_efecto_matriz], mtx);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->efecto_mtx[cantidad_efecto_matriz]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}

void renderizar_fuegos_artificiales(Vec3f parametro0, f32 parametro1, s32 rgb, s16 alpha) {
    Vec3f sp4_c;
    Vec3s sp44;
    s16 rojo;
    s16 verde;
    s16 azul;

    sp4_c[0] = parametro0[0];
    sp4_c[1] = parametro0[1];
    sp4_c[2] = parametro0[2];
    sp44[0] = 0;
    sp44[1] = camara1->rot[1];
    sp44[2] = 0;
    funcion_80280A28(sp4_c, sp44, parametro1);
    gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
    gDPLoadTextureBlock(display_list_cabeza++, dato_8018D48C, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    rojo = ((rgb >> 0x10) & 0xFF) & 0xFF;
    verde = ((rgb >> 0x08) & 0xFF) & 0xFF;
    azul = ((rgb >> 0x00) & 0xFF) & 0xFF;
    funcion_8004B35C(rojo, verde, azul, alpha);
    gSPDisplayList(display_list_cabeza++, dato_0D008E48);
    cantidad_efecto_matriz += 1;
}

void actualizar_fuego_artificial(FuegoArtificial* actor) {
    s32 i;
    Vec3f pos;
    if (actor->desconocido44 < 30) {
        for (i = 0; i < 10; i++) {
            pos[0] = actor->pos[0];
            pos[1] = actor->pos[1] - i * 2;
            pos[2] = actor->pos[2];
            renderizar_fuegos_artificiales(pos, ((10 - i) / 10.0f) * 2, color_fuego_artificial[actor->desconocido48],
                             (((((30 - actor->desconocido44) * 100)) / 30.0f)));
        }

    } else {
        if (actor->desconocido_2c < 5) {
            actor->desconocido_3c += actor->desconocido40 * 2;
            actor->unk34 += actor->unk38 * 2;
        } else {
            actor->desconocido_3c += actor->desconocido40 / (1.0f + (((actor->desconocido_2c * 7) - 0x23) / 10.0f));
            actor->unk34 += actor->unk38 / (1.0f + (((actor->desconocido_2c * 7) - 0x23) / 10.0f));
            if (actor->desconocido_3c < 0) {
                actor->desconocido_3c = 0;
            }
        }
        actor->desconocido_2c += 1;
        if (((actor->desconocido_3c > 0) && ((actor->unk34 > 0.0f))) || (actor->desconocido_2c < 30)) {
            renderizar_fuegos_artificiales(actor->pos, actor->unk34, actor->desconocido30, (s16) actor->desconocido_3c);
        } else {
            actor->activo_es = 0;
        }
    }
    actor->desconocido44 += 1;
}

void sin_uso_80280FA0(SIN_USO ActorCeremonia* actor) {
}

void sin_uso_80280FA8(SIN_USO ActorCeremonia* actor) {
}

void inicializar_globos_y_fuegos_artificiales(void) {
    dato_802874D8.temporizador_actor = 0;
    lista_actor_podio = (ActorCeremonia*) obtener_siguiente_disponible_memoria_direccion(sizeof(ActorCeremonia) * 200);
    bzero(lista_actor_podio, (sizeof(ActorCeremonia) * 200));
    actor_nuevo(&inicializar_ficticio);
}

void funcion_80280FFC(void) {
    dato_802874D8.desconocido_1c = 1;
}

void funcion_8028100C(SIN_USO s32 parametro0, SIN_USO s32 parametro1, SIN_USO s32 parametro2) {
}

void aparecer_globos(s32 parametro0, s32 parametro1, s32 parametro2) {
    s32 i;

    for (i = 0; i < 100; i++) {
        ActorCeremonia* globo;
        globo = actor_nuevo(&inicializar_globo_2);
        globo->pos[0] = sabe_quien_aleatorio(200.0f) + parametro0;
        globo->pos[1] = sabe_quien_aleatorio(380.0f) + parametro1;
        globo->pos[2] = sabe_quien_aleatorio(600.0f) + parametro2;
        globo->desconocido_2c = (s16) (s32) (flotante_aleatorio_entre_0_y_1() * 7.0f);
        globo->desconocido30 = creditos_aleatorio_u16();
        globo->desconocido32 = (s16) (s32) (sabe_quien_aleatorio(400.0f) + 900.0f);
        globo->unk34 = (s16) (s32) (sabe_quien_aleatorio(2000.0f) + 3000.0f);
    }
}

extern s32 color_fuego_artificial[];

void aparecer_cono_fuego_artificial(s32 parametro0, s32 parametro1, s32 parametro2) {
    f32 num;
    static u32 dato_80287540;

    if (((f32) flotante_aleatorio_entre_0_y_1() * (dato_802874B0[7] + 0xD)) < 1.0f) {
        FuegoArtificial* cono;
        cono = (FuegoArtificial*) actor_nuevo(&inicializar_rafaga);
        cono->pos[0] = sabe_quien_aleatorio(0.0f) + parametro0;
        cono->pos[1] = sabe_quien_aleatorio((f32) (dato_802874B0[11] + 100)) + (f32) parametro1;
        cono->pos[2] = sabe_quien_aleatorio((f32) (dato_802874B0[12] + 700)) + (f32) parametro2;

        num = 1.1f;

        cono->desconocido48 = dato_80287540 % 4U;
        cono->desconocido30 = color_fuego_artificial[dato_80287540 % 4U];
        cono->unk34 = num;
        cono->unk38 = num;
        dato_80287540 += 1;
        cono->desconocido_3c = 0xFF;
        cono->desconocido40 = -0x11;
    }
}

extern Mat4 dato_80287500;

void aparecer_temporizador(void) {
    Camara* camara = &camaras[0];
    f32 mirar_ay;

    guLookAtF(dato_80287500, camara->pos[0], camara->pos[1], camara->pos[2], camara->mirar_a[0], camara->mirar_a[1],
              camara->mirar_a[2], camara->arriba[0], camara->arriba[1], camara->arriba[2]);
    if (dato_802874D8.desconocido_1d < 3) {
        if (dato_802874D8.temporizador_actor < 300) {
            mirar_ay = camara->mirar_a[1];
            aparecer_cono_fuego_artificial(-0xE0E, (s32) (((mirar_ay - camara->pos[1]) * 1.5f) + mirar_ay), -0x258);
        }
        if (dato_802874D8.temporizador_actor == 120) {
            aparecer_globos(-0xC6C, (s32) ((f32) dato_802874B0[10] + 210.0f), -0x1EF);
        }
    } else if (dato_802874D8.temporizador_actor == 2) {
        aparecer_globos(-0xC6C, (s32) ((f32) dato_802874B0[10] + 210.0f), -0x1EF);
    }

    dato_802874D8.temporizador_actor += 1;
}

void* actualizacion[][3] = {
    { sin_uso_80280FA8, sin_uso_80280FA0, 0 },
    { sin_uso_80280FA8, actualizar_globo, 0 },
    { sin_uso_80280FA8, actualizar_fuego_artificial, 0 },
    { actualizar_y_rafaga_aparicion_cono_fuego_artificial, 0, actualizar_fuego_artificial },
};

void actualizar_bucle_actores(void) {
    void (*func)(void*);
    s32 i;
    s32 j;
    aparecer_temporizador();
    dato_802874B0[16] = 0;

    for (i = 0; i < 3; i++) {
        ActorCeremonia* actor = lista_actor_podio;
        for (j = 0; j < 200; j++) {
            if (actor->activo_es & 1) {

                func = actualizacion[actor->type][i];

                if (func != 0) {
                    func(actor);
                }
            }
            actor++;
        }
    }
}

void funcion_8028150C(void) {
    dato_802874D4 = display_list_cabeza;
}

void funcion_80281520(void) {
}

void funcion_80281528(void) {
}

void funcion_80281530(void) {
}

void funcion_80281538(void) {
}

void funcion_80281540(void) {
}

void bucle_ceremonia_podio(void) {
    cantidad_objeto_matriz = 0;
    dato_802874FC = 0;
    actualizar_ceremonia_podio_camara();
    funcion_80028F70();
    funcion_80022744();
    funcion_80059AC8();
    funcion_80059AC8();
    funcion_8005A070();
    if (dato_802874D8.desconocido_1c != 0) {
        funcion_8001C14C();
        actualizar_vehiculos();
    }
    renderizar_ceremonia_podio();
    funcion_80281540();
#if DVDL
    mostrar_dvdl();
#endif
    gDPFullSync(display_list_cabeza++);
    gSPEndDisplayList(display_list_cabeza++);
}
