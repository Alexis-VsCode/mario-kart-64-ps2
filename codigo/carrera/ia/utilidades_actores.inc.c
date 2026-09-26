s32 agregar_actor_en_lista_actor_vigente(s32 indice_actor, s16 parametro1) {
    s32 i;
    s32 a2 = 0;

    for (i = 0; i < JUGADORES_NUM; i++) {

        if (lista_actores_vigente[i].desconocido_c == 0) {
            lista_actores_vigente[i].desconocido_c = 1;
            lista_actores_vigente[i].indice_actor = indice_actor;
            lista_actores_vigente[i].unk10 = parametro1;
            lista_actores_vigente[i].unk14 = 0;
            a2 = 1;
            break;
        }
    }
    if (a2 == 0) {
        return -2;
    }
    return 0;
}

s32 agregar_caparazon_rojo_en_lista_actor_vigente(s32 indice_actor) {
    struct Actor* actor = &lista_actor[indice_actor];
    if (actor->type != ACTOR_CAPARAZON_ROJO) {
        return -1;
    }
    return agregar_actor_en_lista_actor_vigente(indice_actor, 0);
}

s32 agregar_caparazon_verde_en_lista_actor_vigente(s32 indice_actor) {
    struct Actor* actor = &lista_actor[indice_actor];
    if (actor->type != ACTOR_CAPARAZON_VERDE) {
        return -1;
    }
    return agregar_actor_en_lista_actor_vigente(indice_actor, 1);
}

s32 agregar_caparazon_azul_en_lista_actor_vigente(s32 parametro0) {
    struct Actor* actor = &lista_actor[parametro0];
    if (actor->type != AZUL_ACTOR_CAPARAZON_ESPINOSO) {
        return -1;
    }
    return agregar_actor_en_lista_actor_vigente(parametro0, 2);
}

void eliminar_actor_en_lista_actor_vigente(s32 indice_actor) {
    struct actores_vigente* phi;
    s32 i;

    for (i = 0; i < JUGADORES_NUM; i++) {
        phi = &lista_actores_vigente[i];
        if (indice_actor == phi->indice_actor) {
            phi->desconocido_c = 0;
            phi->indice_actor = 1000;
        }
    }
}

void funcion_8000EEDC(void) {
    struct actores_vigente* phi;
    s32 i;

    for (i = 0; i < JUGADORES_NUM; i++) {
        phi = &lista_actores_vigente[i];
        phi->desconocido_c = 0;
        phi->indice_actor = 1000;
    }
}

void generar_humo_jugador(void) {
    s32 algun_indice;
    f32 variable_f20;
    struct Actor* temporal_s1;
    struct actores_vigente* variable_s0;

    for (algun_indice = 0; algun_indice < JUGADORES_NUM; algun_indice++) {
        variable_s0 = &lista_actores_vigente[algun_indice];
        if (variable_s0->desconocido_c == 1) {
            temporal_s1 = &lista_actor[variable_s0->indice_actor];
            variable_s0->unk14++;
            switch (variable_s0->unk10) {
                case 0:
                    if (variable_s0->unk14 < 0xA) {
                        variable_f20 = 0.3f;
                    } else {
                        variable_f20 = 0.9f;
                    }
                    break;
                case 1:
                    if (variable_s0->unk14 < 0xA) {
                        variable_f20 = 0.15f;
                    } else {
                        variable_f20 = 0.45f;
                    }
                    break;
                case 2:
                    if (variable_s0->unk14 < 0xA) {
                        variable_f20 = 0.15f;
                    } else {
                        variable_f20 = 0.45f;
                    }
                    break;
                default:
                    variable_f20 = 1.0f;
                    break;
            }
            if (!(variable_s0->unk14 & 1)) {
                inicializar_particula_humo(temporal_s1->pos, ((int_aleatorio(30) + 20) * variable_f20) / 50.0f, variable_s0->unk10);
            }
        }
    }
}
