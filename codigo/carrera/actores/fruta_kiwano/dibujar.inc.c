#include <carrera/actores.h>
#include <PR/gbi.h>
#include <sistema/bucle_principal.h>
#include "recursos/pistas/dks_jungle_parkway/datos_pista.h"

void renderizar_actor_kiwano_fruta(SIN_USO Camara* camara, Mat4 parametro1, struct Actor* actor) {
    uintptr_t direccion;
    s32 max_objetos_alcanzado;

    if (actor->state == 0) {
        return;
    }

    parametro1[3][0] = actor->pos[0];
    parametro1[3][1] = actor->pos[1];
    parametro1[3][2] = actor->pos[2];

    max_objetos_alcanzado = fijar_posicion_render(parametro1, 0) == 0;
    if (max_objetos_alcanzado) {
        return;
    }

    direccion = (actor->rot[0] << 0xA) + 0x03009000;
    gDPLoadTextureBlock(display_list_cabeza++, VIRTUAL_A_FISICO(direccion), G_IM_FMT_CI, G_IM_SIZ_8b, 32, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPDisplayList(display_list_cabeza++, d_circuito_dks_jungle_parkway_dl_kiwano_fruta);
}
