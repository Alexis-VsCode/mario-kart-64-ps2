#include <carrera/actores.h>
#include <PR/gbi.h>

void renderizar_actor_caparazon_rojo(Camara* camara, Mat4 matriz, struct ActorCaparazon* caparazon) {
    gDPLoadTLUT_pal256(display_list_cabeza++, &tlut_caparazon_rojo);
    renderizar_caparazon_actor(camara, matriz, caparazon);
}

void renderizar_actor_caparazon_azul(Camara* camara, Mat4 matriz, struct ActorCaparazon* caparazon) {
    gDPLoadTLUT_pal256(display_list_cabeza++, tlut_comun_caparazon_azul);
    renderizar_caparazon_actor(camara, matriz, caparazon);
}
