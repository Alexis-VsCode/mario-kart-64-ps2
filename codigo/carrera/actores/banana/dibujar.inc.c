#include <carrera/actores.h>
#include <carrera/preparacion_carrera.h>
#include <PR/gbi.h>

void renderizar_banana_actor(Camara* camara, SIN_USO Mat4 parametro1, struct BananaActor* banana) {
    SIN_USO s32 relleno[2];
    s32 max_objetos_alcanzado;
    Vec3s sp7_c;
    Mat4 sp3_c;

    f32 temporal_ =
        distancia_si_visible(camara->pos, banana->pos, camara->rot[1], 0, acercar_camara[camara - camara1], 490000.0f);
    if (temporal_ < 0.0f) {
        actor_no_renderizado(camara, (struct Actor*) banana);
        return;
    }

    if ((banana->pos[1] > max_y_circuito + 800.0f)) {
        actor_no_renderizado(camara, (struct Actor*) banana);
        return;
    }
    if (banana->pos[1] < (min_y_circuito - 800.0f)) {
        actor_no_renderizado(camara, (struct Actor*) banana);
        return;
    }

    actor_renderizado(camara, (struct Actor*) banana);

    if (banana->state == 5) {
        rotar_traslacion_zxy_mtxf(sp3_c, banana->pos, banana->rot);
    } else {
        sp7_c[0] = 0;
        sp7_c[1] = 0;
        sp7_c[2] = 0;
        rotar_traslacion_zxy_mtxf(sp3_c, banana->pos, sp7_c);
    }

    max_objetos_alcanzado = fijar_posicion_render(sp3_c, 0) == 0;
    if (max_objetos_alcanzado) {
        return;
    }

    if (banana->state != 5) {
        gSPDisplayList(display_list_cabeza++, &banana_modelo_comun);
    } else {
        gSPDisplayList(display_list_cabeza++, &comun_modelo_plano_banana);
    }
}
