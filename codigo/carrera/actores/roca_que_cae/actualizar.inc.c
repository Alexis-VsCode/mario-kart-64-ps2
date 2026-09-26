#include <carrera/actores.h>
#include <carrera/preparacion_carrera.h>
#include <sistema/bucle_principal.h>
#include "recursos/pistas/choco_mountain/datos_pista.h"

void funcion_8029CF0C(struct DatosAparicionActor* aparecer_datos, struct RocaCayendo* roca) {
    s32 segmento = SEGMENT_NUMBER2(aparecer_datos);
    s32 desplazamiento = SEGMENT_OFFSET(aparecer_datos);
    struct DatosAparicionActor* temporal_v0 = (struct DatosAparicionActor*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    Vec3s sp24 = { 60, 120, 180 };
    temporal_v0 += roca->desconocido_06;
    roca->temporizador_reaparicion = sp24[roca->desconocido_06];
    roca->pos[0] = (f32) temporal_v0->pos[0] * sentido_circuito;
    roca->pos[1] = (f32) temporal_v0->pos[1] + 10.0f;
    roca->pos[2] = (f32) temporal_v0->pos[2];
    fijar_vec3f(roca->velocidad, 0, 0, 0);
    fijar_vec3s(roca->rot, 0, 0, 0);
}

void aparecer_rocas_cayendo(struct DatosAparicionActor* aparecer_datos) {
    s32 direccion = SEGMENT_NUMBER2(aparecer_datos);
    s32 desplazamiento = SEGMENT_OFFSET(aparecer_datos);
    struct DatosAparicionActor* temporal_s0 = (struct DatosAparicionActor*) VIRTUAL_A_PHYSICAL2(tabla_segmento[direccion] + desplazamiento);
    struct RocaCayendo* temporal_v1;
    Vec3f pos_inicial;
    Vec3f velocidad_inicial;
    Vec3s rot_inicial;
    s16 temporal_;

    while (temporal_s0->pos[0] != -0x8000) {
        pos_inicial[0] = temporal_s0->pos[0] * sentido_circuito;
        pos_inicial[1] = temporal_s0->pos[1] + 10.0f;
        pos_inicial[2] = temporal_s0->pos[2];
        fijar_vec3f(velocidad_inicial, 0, 0, 0);
        fijar_vec3s(rot_inicial, 0, 0, 0);
        temporal_ = agregar_actor_a_ranura_vacio(pos_inicial, rot_inicial, velocidad_inicial, ROCA_CAYENDO_ACTOR);
        temporal_v1 = (struct RocaCayendo*) &lista_actor[temporal_];

        temporal_v1->desconocido_06 = temporal_s0->algun_id;
        funcion_802AAAAC((Colision*) &temporal_v1->desconocido30);
        temporal_s0++;
    }
}

void actualizar_rocas_cayendo_actor(struct RocaCayendo* roca) {
    Vec3f vec_desconocido;
    f32 relleno0;
    f32 relleno1;

    if (roca->temporizador_reaparicion != 0) {
        roca->temporizador_reaparicion -= 1;
        return;
    }
    if (roca->pos[1] < dato_8015F8E4) {
        funcion_8029CF0C(d_circuito_choco_mountain_apariciones_roca_cayendo, roca);
    }
    roca->rot[0] += (s16) ((roca->velocidad[2] * 5461.0f) / 20.0f);
    roca->rot[2] += (s16) ((roca->velocidad[0] * 5461.0f) / 20.0f);
    roca->velocidad[1] -= 0.1;
    if (roca->velocidad[1] < (-2.0f)) {
        roca->velocidad[1] = -2.0f;
    }
    roca->pos[0] += roca->velocidad[0];
    roca->pos[1] += roca->velocidad[1];
    roca->pos[2] += roca->velocidad[2];
    relleno1 = roca->velocidad[1];
    comprobar_colision_envolvente(&roca->desconocido30, 10.0f, roca->pos[0], roca->pos[1], roca->pos[2]);
    relleno0 = roca->desconocido30.distancia_superficie[2];
    if (relleno0 < 0.0f) {
        vec_desconocido[0] = -roca->desconocido30.vector_orientacion[0];
        vec_desconocido[1] = -roca->desconocido30.vector_orientacion[1];
        vec_desconocido[2] = -roca->desconocido30.vector_orientacion[2];
        roca->pos[0] += vec_desconocido[0] * roca->desconocido30.distancia_superficie[2];
        roca->pos[1] += vec_desconocido[1] * roca->desconocido30.distancia_superficie[2];
        roca->pos[2] += vec_desconocido[2] * roca->desconocido30.distancia_superficie[2];
        ajustar_ortogonalmente_pos(vec_desconocido, relleno0, roca->velocidad, 2.0f);
        roca->velocidad[1] = -1.2f * relleno1;
        funcion_800C98B8(roca->pos, roca->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x0F));
    }
    relleno0 = roca->desconocido30.distancia_superficie[0];
    if (relleno0 < 0.0f) {
        vec_desconocido[1] = -roca->desconocido30.desconocido48[1];
        if (vec_desconocido[1] == 0.0f) {
            roca->velocidad[1] *= -1.2f;
            return;
        } else {
            vec_desconocido[0] = -roca->desconocido30.desconocido48[0];
            vec_desconocido[2] = -roca->desconocido30.desconocido48[2];
            roca->pos[0] += vec_desconocido[0] * roca->desconocido30.distancia_superficie[0];
            roca->pos[1] += vec_desconocido[1] * roca->desconocido30.distancia_superficie[0];
            roca->pos[2] += vec_desconocido[2] * roca->desconocido30.distancia_superficie[0];
            ajustar_ortogonalmente_pos(vec_desconocido, relleno0, roca->velocidad, 2.0f);
            roca->velocidad[1] = -1.2f * relleno1;
            funcion_800C98B8(roca->pos, roca->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x0F));
        }
    }
    relleno0 = roca->desconocido30.distancia_superficie[1];
    if (relleno0 < 0.0f) {
        vec_desconocido[1] = -roca->desconocido30.desconocido54[1];
        if (vec_desconocido[1] == 0.0f) {
            roca->velocidad[1] *= -1.2f;
        } else {
            vec_desconocido[0] = -roca->desconocido30.desconocido54[0];
            vec_desconocido[2] = -roca->desconocido30.desconocido54[2];
            roca->pos[0] += vec_desconocido[0] * roca->desconocido30.distancia_superficie[1];
            roca->pos[1] += vec_desconocido[1] * roca->desconocido30.distancia_superficie[1];
            roca->pos[2] += vec_desconocido[2] * roca->desconocido30.distancia_superficie[1];
            relleno1 = roca->velocidad[1];
            ajustar_ortogonalmente_pos(vec_desconocido, relleno0, roca->velocidad, 2.0f);
            roca->velocidad[1] = -1.2f * relleno1;
            funcion_800C98B8(roca->pos, roca->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x0F));
        }
    }
}
