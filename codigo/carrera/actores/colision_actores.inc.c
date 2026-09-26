// Colision actores

bool consultar_actor_colision_vs_actor(struct Actor* parametro0, struct Actor* parametro1) {
    f32 temporal_f0;
    f32 dist;
    f32 dist_y;
    f32 dist_z;
    f32 dist_x;

    temporal_f0 = parametro0->tamanio_caja_envolvente + parametro1->tamanio_caja_envolvente;
    dist_x = parametro0->pos[0] - parametro1->pos[0];
    if (temporal_f0 < dist_x) {
        return SIN_COLISION;
    }
    if (dist_x < -temporal_f0) {
        return SIN_COLISION;
    }
    dist_y = parametro0->pos[1] - parametro1->pos[1];
    if (temporal_f0 < dist_y) {
        return SIN_COLISION;
    }
    if (dist_y < -temporal_f0) {
        return SIN_COLISION;
    }
    dist_z = parametro0->pos[2] - parametro1->pos[2];
    if (temporal_f0 < dist_z) {
        return SIN_COLISION;
    }
    if (dist_z < -temporal_f0) {
        return SIN_COLISION;
    }
    dist = (dist_x * dist_x) + (dist_y * dist_y) + (dist_z * dist_z);
    if (dist < 0.1f) {
        return SIN_COLISION;
    }
    if ((temporal_f0 * temporal_f0) < dist) {
        return SIN_COLISION;
    }
    return COLISION;
}

void destruir_actor_destructible(struct Actor* actor) {
    struct ActorCaparazon* caparazon;
    struct BananaActor* banana;
    struct CajaItemFalsa* caja_item_falsa_2;
    Jugador* jugador;

    switch (actor->type) {
        case ACTOR_BANANA:
            banana = (struct BananaActor*) actor;
            switch (banana->state) {
                case PRIMER_BANANA_GRUPO_BANANA:
                case BANANA_GRUPO_BANANA:
                    destruir_banana_en_grupo_banana(banana);
                    break;
                case BANANA_MANTENIDO:
                    jugador = &jugadores[banana->id_jugador];
                    jugador->disparadores &= ~EFECTO_ITEM_ARRASTRE;
                case BANANA_EN_SUELO:
                    banana->flags = -0x8000;
                    banana->desconocido_04 = 0x003C;
                    banana->state = BANANA_DESTRUIDO;
                    banana->velocidad[1] = 3.0f;
                    break;
                case BANANA_SOLTADO:
                case BANANA_DESTRUIDO:
                default:
                    break;
            }
            break;
        case ACTOR_CAPARAZON_VERDE:
            caparazon = (struct ActorCaparazon*) actor;
            if (caparazon->state != CAPARAZON_VERDE_CORREDOR_GOLPE_A) {
                switch (caparazon->state) {
                    case CAPARAZON_MOVIENDO:
                        eliminar_actor_en_lista_actor_vigente(actor - lista_actor);
                    case CAPARAZON_MANTENIDO:
                    case CAPARAZON_SOLTADO:
                        caparazon->flags = -0x8000;
                        caparazon->angulo_rot = 0;
                        caparazon->algun_temporizador = 0x003C;
                        caparazon->state = CAPARAZON_VERDE_CORREDOR_GOLPE_A;
                        caparazon->velocidad[1] = 3.0f;
                        break;
                    case TRIPLE_CAPARAZON_VERDE:
                        chocar_con_jugador_triple_actor_caparazon(caparazon, ACTOR_CAPARAZON_VERDE);
                        break;
                    default:
                        break;
                }
            }
            break;
        case AZUL_ACTOR_CAPARAZON_ESPINOSO:
            caparazon = (struct ActorCaparazon*) actor;
            if (caparazon->state != CAPARAZON_DESTRUIDO) {
                switch (caparazon->state) {
                    case CAPARAZON_MOVIENDO:
                    case CAPARAZON_ROJO_BLOQUEO_EN:
                    case TRIPLE_CAPARAZON_VERDE:
                    case CAPARAZON_VERDE_CORREDOR_GOLPE_A:
                    case CAPARAZON_AZUL_BLOQUEO_EN:
                    case CAPARAZON_AZUL_OBJETIVO_ELIMINADO:
                        funcion_800C9EF4(caparazon->pos, SONIDO_CARGA_PARAMETRO(0x51, 0x01, 0x80, 0x08));
                        eliminar_actor_en_lista_actor_vigente(actor - lista_actor);
                    case CAPARAZON_MANTENIDO:
                    case CAPARAZON_SOLTADO:
                        caparazon->flags = -0x8000;
                        caparazon->angulo_rot = 0;
                        caparazon->algun_temporizador = 0x003C;
                        caparazon->state = CAPARAZON_DESTRUIDO;
                        caparazon->velocidad[1] = 3.0f;
                        break;
                    default:
                        break;
                }
            }
            break;
        case ACTOR_CAPARAZON_ROJO:
            caparazon = (struct ActorCaparazon*) actor;
            if (caparazon->state != CAPARAZON_DESTRUIDO) {
                switch (caparazon->state) {
                    case CAPARAZON_MOVIENDO:
                    case CAPARAZON_ROJO_BLOQUEO_EN:
                    case TRIPLE_CAPARAZON_VERDE:
                    case CAPARAZON_VERDE_CORREDOR_GOLPE_A:
                    case CAPARAZON_AZUL_BLOQUEO_EN:
                    case CAPARAZON_AZUL_OBJETIVO_ELIMINADO:
                        eliminar_actor_en_lista_actor_vigente(actor - lista_actor);
                    case CAPARAZON_MANTENIDO:
                    case CAPARAZON_SOLTADO:
                        caparazon->flags = -0x8000;
                        caparazon->angulo_rot = 0;
                        caparazon->algun_temporizador = 0x003C;
                        caparazon->state = CAPARAZON_DESTRUIDO;
                        caparazon->velocidad[1] = 3.0f;
                        break;
                    case TRIPLE_CAPARAZON_ROJO:
                        chocar_con_jugador_triple_actor_caparazon(caparazon, ACTOR_CAPARAZON_ROJO);
                        break;
                    default:
                        break;
                }
            }
            break;
        case ACTOR_CAJA_ITEM_FALSA:
            caja_item_falsa_2 = (struct CajaItemFalsa*) actor;
            jugador = &jugadores[(s16) caja_item_falsa_2->id_jugador];
            if (caja_item_falsa_2->state == MANTENIDO_CAJA_ITEM_FALSA) {
                jugador->disparadores &= ~EFECTO_ITEM_ARRASTRE;
            }
            caja_item_falsa_2->state = DESTRUIDO_CAJA_ITEM_FALSA;
            caja_item_falsa_2->flags = -0x8000;
            caja_item_falsa_2->algun_temporizador = 0;
            break;
    }
}

void reproducir_sonido_en_colision_actor_destructible(struct Actor* parametro0, struct Actor* parametro1) {
    switch (parametro0->type) {
        case ACTOR_CAPARAZON_VERDE:
            if ((parametro0->state == CAPARAZON_MANTENIDO) || (parametro0->state == TRIPLE_CAPARAZON_VERDE)) {
                parametro0->flags |= 0x200;
                funcion_800C98B8(parametro0->pos, parametro0->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x90, 0x53));
                return;
            }
            break;
        case ACTOR_CAPARAZON_ROJO:
            if ((parametro0->state == CAPARAZON_MANTENIDO) || (parametro0->state == TRIPLE_CAPARAZON_ROJO)) {
                parametro0->flags |= 0x200;
                funcion_800C98B8(parametro0->pos, parametro0->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x90, 0x53));
                return;
            }
            break;
        case AZUL_ACTOR_CAPARAZON_ESPINOSO:
            if (parametro0->state == CAPARAZON_MANTENIDO) {
                parametro0->flags |= 0x200;
                funcion_800C98B8(parametro0->pos, parametro0->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x90, 0x53));
                return;
            }
            break;
        case ACTOR_CAJA_ITEM_FALSA:
            if (parametro0->state == MANTENIDO_CAJA_ITEM_FALSA) {
                parametro0->flags |= 0x200;
                funcion_800C98B8(parametro0->pos, parametro0->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x90, 0x53));
                return;
            }
            break;
    }

    switch (parametro1->type) {
        case ACTOR_CAPARAZON_VERDE:
            if ((parametro1->state == CAPARAZON_MANTENIDO) || (parametro1->state == TRIPLE_CAPARAZON_VERDE)) {
                parametro1->flags |= 0x200;
                funcion_800C98B8(parametro1->pos, parametro1->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x90, 0x53));
                return;
            }
            break;
        case ACTOR_CAPARAZON_ROJO:
            if ((parametro1->state == CAPARAZON_MANTENIDO) || (parametro1->state == TRIPLE_CAPARAZON_ROJO)) {
                parametro1->flags |= 0x200;
                funcion_800C98B8(parametro1->pos, parametro1->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x90, 0x53));
                return;
            }
            break;
        case AZUL_ACTOR_CAPARAZON_ESPINOSO:
            if (parametro1->state == CAPARAZON_MANTENIDO) {
                parametro1->flags |= 0x200;
                funcion_800C98B8(parametro1->pos, parametro1->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x90, 0x53));
                return;
            }
            break;
        case ACTOR_CAJA_ITEM_FALSA:
            if (parametro1->state == MANTENIDO_CAJA_ITEM_FALSA) {
                parametro1->flags |= 0x200;
                funcion_800C98B8(parametro1->pos, parametro1->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x90, 0x53));
                return;
            }
            break;
    }

    parametro0->flags |= 0x100;
    funcion_800C98B8(parametro0->pos, parametro0->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x10));
}

void evaluar_colision_actor_entre_dos_actores_destructible(struct Actor* actor1, struct Actor* actor2) {
    if (consultar_actor_colision_vs_actor(actor1, actor2) == COLISION) {
        if ((actor1->type == AZUL_ACTOR_CAPARAZON_ESPINOSO) && (actor2->type == AZUL_ACTOR_CAPARAZON_ESPINOSO)) {
            destruir_actor_destructible(actor1);
            destruir_actor_destructible(actor2);
            actor1->flags |= 0x100;
            funcion_800C98B8(actor1->pos, actor1->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x10));
            return;
        }
        if (actor1->type == AZUL_ACTOR_CAPARAZON_ESPINOSO) {
            if (actor1->state == CAPARAZON_MANTENIDO) {
                destruir_actor_destructible(actor1);
            }
        } else {
            destruir_actor_destructible(actor1);
        }
        if (actor2->type == AZUL_ACTOR_CAPARAZON_ESPINOSO) {
            if (actor2->state == CAPARAZON_MANTENIDO) {
                destruir_actor_destructible(actor2);
            }
        } else {
            destruir_actor_destructible(actor2);
        }
        reproducir_sonido_en_colision_actor_destructible(actor1, actor2);
    }
}

void evaluar_colision_entre_actor_jugador(Jugador* jugador, struct Actor* actor) {
    SIN_USO s32 relleno;
    s16 temporal_lo;
    SIN_USO s32 relleno2[2];
    s16 temporal_v1;
    Jugador* duenio;
    f32 temporal_f0;
    f32 temporal_f2;

    temporal_lo = jugador - jugador_uno;
    switch (actor->type) {
        case ACTOR_YOSHI_HUEVO:
            if (!(jugador->efectos & BOO_EFECTO) && !(jugador->type & INVISIBLE_JUGADOR_O_BOMBA)) {
                colision_yoshi_huevo(jugador, (struct YoshiValleyHuevo*) actor);
            }
            break;
        case ACTOR_BANANA:
            if (jugador->efectos &
                (BOO_EFECTO | BANANA_CERCA_EFECTO_TROMPO | EFECTO_TROMPO_BANANA | EFECTO_TROMPO_CONDUCIENDO)) {
                break;
            }
            if (jugador->disparadores & DISPARADOR_BANANA_GOLPE) {
                break;
            }
            temporal_v1 = actor->rot[0];
            if (((temporal_lo == temporal_v1) && (actor->flags & 0x1000)) ||
                (consultar_jugador_colision_vs_item_actor(jugador, actor) != COLISION)) {
                break;
            }
            jugador->disparadores |= DISPARADOR_BANANA_GOLPE;
            duenio = &jugadores[temporal_v1];
            if (duenio->type & HUMANO_JUGADOR) {
                if (actor->flags & 0xF) {
                    if (temporal_lo != temporal_v1) {
                        funcion_800C90F4(temporal_v1, (duenio->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x06));
                    }
                } else {
                    temporal_f0 = actor->pos[0] - duenio->pos[0];
                    temporal_f2 = actor->pos[2] - duenio->pos[2];
                    if ((((temporal_f0 * temporal_f0) + (temporal_f2 * temporal_f2)) < 360000.0f) && (temporal_lo != temporal_v1)) {
                        funcion_800C90F4(temporal_v1, (duenio->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x06));
                    }
                }
            }
            destruir_actor_destructible(actor);
            break;
        case ACTOR_CAPARAZON_VERDE:
            if (jugador->efectos & (BOO_EFECTO | GOLPE_POR_CAPARAZON_VERDE_EFECTO)) {
                break;
            }
            if (jugador->disparadores & DISPARADOR_VUELCO_BAJO) {
                break;
            }
            temporal_v1 = actor->rot[2];
            if (((temporal_lo == temporal_v1) && (actor->flags & 0x1000)) ||
                (consultar_jugador_colision_vs_item_actor(jugador, actor) != COLISION)) {
                break;
            }
            jugador->disparadores |= DISPARADOR_VUELCO_BAJO;
            funcion_800C98B8(jugador->pos, jugador->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x10));
            duenio = &jugadores[temporal_v1];
            if ((duenio->type & HUMANO_JUGADOR) && (temporal_lo != temporal_v1)) {
                funcion_800C90F4(temporal_v1, (duenio->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x06));
            }
            destruir_actor_destructible(actor);
            break;
        case AZUL_ACTOR_CAPARAZON_ESPINOSO:
            if (jugador->disparadores & DISPARADOR_VUELCO_ALTO) {
                break;
            }
            temporal_v1 = actor->rot[2];
            if (((temporal_lo == temporal_v1) && (actor->flags & 0x1000)) ||
                (consultar_jugador_colision_vs_item_actor(jugador, actor) != COLISION)) {
                break;
            }
            if (!(jugador->efectos & BOO_EFECTO)) {
                jugador->disparadores |= DISPARADOR_VUELCO_ALTO;
                funcion_800C98B8(jugador->pos, jugador->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x10));
            }
            duenio = &jugadores[temporal_v1];
            if ((duenio->type & HUMANO_JUGADOR) && (temporal_lo != temporal_v1)) {
                funcion_800C90F4(temporal_v1, (duenio->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x06));
            }
            if (temporal_lo == actor->desconocido_04) {
                destruir_actor_destructible(actor);
            }
            break;
        case ACTOR_CAPARAZON_ROJO:
            temporal_v1 = actor->rot[2];
            if (jugador->efectos & EFECTO_ERROR_EXPLOSION) {
                break;
            }
            if (jugador->disparadores & DISPARADOR_VUELCO_ALTO) {
                break;
            }
            temporal_v1 = actor->rot[2];
            if (((temporal_lo == temporal_v1) && (actor->flags & 0x1000)) ||
                (consultar_jugador_colision_vs_item_actor(jugador, actor) != COLISION)) {
                break;
            }
            if (!(jugador->efectos & BOO_EFECTO)) {
                jugador->disparadores |= DISPARADOR_VUELCO_ALTO;
                funcion_800C98B8(jugador->pos, jugador->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x10));
            }
            duenio = &jugadores[temporal_v1];
            if ((duenio->type & HUMANO_JUGADOR) && (temporal_lo != temporal_v1)) {
                funcion_800C90F4(temporal_v1, (duenio->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x06));
            }
            destruir_actor_destructible(actor);
            break;
        case ACTOR_PLANTA_PIRANHA:
            if (!(jugador->efectos & BOO_EFECTO)) {
                colision_planta_piranha(jugador, (struct PlantaPiranha*) actor);
            }
            break;
        case ACTOR_MARIO_CARTEL:
            if (!(jugador->efectos & BOO_EFECTO)) {
                colision_mario_cartel(jugador, actor);
            }
            break;
        case ARBOL_ACTOR_MARIO_RACEWAY:
        case ARBOL_ACTOR_YOSHI_VALLEY:
        case ARBOL_ACTOR_ROYAL_RACEWAY:
        case ARBOL_ACTOR_MOO_MOO_FARM:
        case ARBOL_PALMERA_ACTOR:
        case 26:
        case ARBOL_ACTOR_BOWSERS_CASTLE:
        case ARBOL_ACTOR_FRAPPE_SNOWLAND:
        case CACTUS1_ACTOR_KALAMARI_DESERT:
        case CACTUS2_ACTOR_KALAMARI_DESERT:
        case CACTUS3_ACTOR_KALAMARI_DESERT:
        case ARBUSTO_ACTOR_BOWSERS_CASTLE:
            if (!(jugador->efectos & BOO_EFECTO)) {
                arbol_colision(jugador, actor);
            }
            break;
        case ROCA_CAYENDO_ACTOR:
            if (!(jugador->efectos & BOO_EFECTO) && !(jugador->type & INVISIBLE_JUGADOR_O_BOMBA)) {
                if (consultar_jugador_colision_vs_item_actor(jugador, actor) == COLISION) {
                    funcion_800C98B8(actor->pos, actor->velocidad, SONIDO_EXPLOSION_ACCION);
                    if ((seleccion_modo == CONTRARRELOJ) && !(jugador->type & CPU_JUGADOR)) {
                        publicar_contrarreloj_guardado_no_puede_repeticion = 1;
                    }
                    if (jugador->efectos & EFECTO_ESTRELLA) {
                        actor->velocidad[1] = 10.0f;
                    } else {
                        aplastamiento_disparador(jugador, jugador - jugador_uno);
                    }
                }
            }
            break;
        case ACTOR_CAJA_ITEM_FALSA:
            temporal_v1 = actor->velocidad[0];
            if (jugador->efectos & BOO_EFECTO) {
                break;
            }
            temporal_v1 = actor->velocidad[0];
            if (((temporal_lo == temporal_v1) && (actor->flags & 0x1000)) ||
                (consultar_jugador_colision_vs_item_actor(jugador, actor) != COLISION)) {
                break;
            }
            jugador->disparadores |= DISPARADOR_VUELCO_VERTICAL;
            duenio = &jugadores[temporal_v1];
            if (duenio->type & HUMANO_JUGADOR) {
                if (actor->flags & 0xF) {
                    if (temporal_lo != temporal_v1) {
                        funcion_800C90F4(temporal_v1, (duenio->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x06));
                    }
                } else {
                    temporal_f0 = actor->pos[0] - duenio->pos[0];
                    temporal_f2 = actor->pos[2] - duenio->pos[2];
                    if ((((temporal_f0 * temporal_f0) + (temporal_f2 * temporal_f2)) < 360000.0f) && (temporal_lo != temporal_v1)) {
                        funcion_800C90F4(temporal_v1, (duenio->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x06));
                    }
                }
                if (actor->state == 0) {
                    duenio->disparadores &= ~EFECTO_ITEM_ARRASTRE;
                }
            }
            actor->state = 2;
            actor->flags = -0x8000;
            actor->desconocido_04 = 0;
            break;
        case ACTOR_GLOBO_AEROSTATICO_CAJA_ITEM:
            if (consultar_jugador_colision_vs_item_actor(jugador, actor) == COLISION) {
                actor->state = 3;
                actor->flags = -0x8000;
                actor->desconocido_04 = 0;
                if (jugador->type & HUMANO_JUGADOR) {
                    funcion_8007ABFC(jugador - jugador_uno, 7);
                }
            } else if (actor->state == 0) {
                actor->state = 1;
                actor->flags = -0x8000;
            }
            break;
        case ACTOR_CAJA_ITEM:
            if (consultar_jugador_colision_vs_item_actor(jugador, actor) == COLISION) {
                actor->state = 3;
                actor->flags = -0x8000;
                actor->desconocido_04 = 0;
                if (jugador->type & HUMANO_JUGADOR) {
                    funcion_8007ABFC(jugador - jugador_uno, 0);
                }
            } else if (actor->state == 0) {
                actor->state = 1;
                actor->flags = -0x8000;
            }
            break;
        default:
            break;
    }
}

void evaluar_colision_para_jugadores_y_actores(void) {
    struct Actor* temporal_a1;
    s32 i, j;
    Jugador* phi_s1;

    for (i = 0; i < JUGADORES_NUM; i++) {
        phi_s1 = &jugadores[i];

        if (((phi_s1->type & EXISTE_JUGADOR) != 0) && ((phi_s1->efectos & EFECTO_APLASTAMIENTO) == 0)) {
            funcion_802977E4(phi_s1);
            for (j = 0; j < TAMANIO_LISTA_ACTOR; j++) {
                temporal_a1 = &lista_actor[j];

                if ((phi_s1->efectos & EFECTO_APLASTAMIENTO) == 0) {
                    if (((temporal_a1->flags & 0x8000) != 0) && ((temporal_a1->flags & 0x4000) != 0)) {
                        evaluar_colision_entre_actor_jugador(phi_s1, temporal_a1);
                    }
                }
            }
        }
    }
}

void evaluar_colision_para_actores_destructible(void) {
    struct Actor* actor1;
    struct Actor* actor2;
    s32 i, j;
    SIN_USO s32 relleno;

    for (i = actores_permanente_num; i < (TAMANIO_LISTA_ACTOR - 1); i++) {
        actor1 = &lista_actor[i];

        if ((actor1->flags & 0x8000) == 0) {
            continue;
        }
        if ((actor1->flags & 0x4000) == 0) {
            continue;
        }

        switch (actor1->type) {
            case ACTOR_BANANA:
            case ACTOR_CAPARAZON_VERDE:
            case ACTOR_CAPARAZON_ROJO:
            case AZUL_ACTOR_CAPARAZON_ESPINOSO:
            case ACTOR_CAJA_ITEM_FALSA:

                for (j = i + 1; j < TAMANIO_LISTA_ACTOR; j++) {
                    actor2 = &lista_actor[j];

                    if ((actor1->flags & 0x8000) == 0) {
                        continue;
                    }
                    if ((actor1->flags & 0x4000) == 0) {
                        continue;
                    }

                    if ((actor2->flags & 0x8000) == 0) {
                        continue;
                    }
                    if ((actor2->flags & 0x4000) == 0) {
                        continue;
                    }

                    switch (actor2->type) {
                        case ACTOR_BANANA:
                            if (actor1->type == ACTOR_BANANA) {
                                continue;
                            }
                            evaluar_colision_actor_entre_dos_actores_destructible(actor1, actor2);
                            break;
                        case ACTOR_CAPARAZON_VERDE:
                            if (actor1->type == ACTOR_CAPARAZON_VERDE) {
                                if (actor1->rot[2] == actor2->rot[2]) {
                                    continue;
                                }
                            }
                            evaluar_colision_actor_entre_dos_actores_destructible(actor1, actor2);
                            break;
                        case ACTOR_CAPARAZON_ROJO:
                            if (actor1->type == ACTOR_CAPARAZON_ROJO) {
                                if (actor1->rot[2] == actor2->rot[2]) {
                                    continue;
                                }
                            }
                            evaluar_colision_actor_entre_dos_actores_destructible(actor1, actor2);
                            break;
                        case AZUL_ACTOR_CAPARAZON_ESPINOSO:
                        case ACTOR_CAJA_ITEM_FALSA:
                            evaluar_colision_actor_entre_dos_actores_destructible(actor1, actor2);
                            break;
                    }
                }

                break;
        }
    }
}

void funcion_802A1064(struct CajaItemFalsa* caja_item_falsa) {
    if ((u32) (caja_item_falsa - (struct CajaItemFalsa*) lista_actor) <= (u32) TAMANIO_LISTA_ACTOR) {
        if (((caja_item_falsa->flags & 0x8000) != 0) && (caja_item_falsa->type == ACTOR_CAJA_ITEM_FALSA)) {
            caja_item_falsa->state = CAJA_ITEM_FALSA_EN_SUELO;
            caja_item_falsa->objetivo_y = funcion_802ABEAC(&caja_item_falsa->desconocido30, caja_item_falsa->pos) + 8.66f;
            caja_item_falsa->algun_temporizador = 100;
        }
    }
}

#include "carrera/actores/caja_item_falsa/actualizar.inc.c"

void inicializar_actor_globo_aerostatico_caja_item(f32 x, f32 y, f32 z) {
    Vec3f pos;
    Vec3f velocidad;
    Vec3s rot;
    s16 id;

    if (seleccion_modo == CONTRARRELOJ) {
        return;
    }

    fijar_vec3s(rot, 0, 0, 0);
    fijar_vec3f(velocidad, 0, 0, 0);
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    id = agregar_actor_a_ranura_vacio(pos, rot, velocidad, ACTOR_GLOBO_AEROSTATICO_CAJA_ITEM);
    actor_globo_aerostatico_caja_item = &lista_actor[id];
}

#include "carrera/actores/caja_item/actualizar.inc.c"

#include "carrera/actores/caja_item_falsa/dibujar.inc.c"

#include "carrera/actores/caja_item/dibujar.inc.c"

#include "carrera/actores/cartel_wario/dibujar.inc.c"

#include "carrera/actores/huevo_yoshi/dibujar.inc.c"

#include "carrera/actores/cartel_mario/dibujar.inc.c"

#include "carrera/actores/paso_a_nivel/dibujar.inc.c"

#include "carrera/actores/palmera/dibujar.inc.c"

void renderizar_cajas_item(struct desconocido_struct_800DC5EC* parametro0) {
    Camara* camara = parametro0->camara;
    struct Actor* actor;
    s32 i;
    dato_8015F8DC = 0;

    for (i = 0; i < TAMANIO_LISTA_ACTOR; i++) {
        actor = &lista_actor[i];

        if (actor->flags == 0) {
            continue;
        }

        switch (actor->type) {
            case ACTOR_CAJA_ITEM_FALSA:
                renderizar_actor_caja_item_falsa(camara, (struct CajaItemFalsa*) actor);
                break;
            case ACTOR_CAJA_ITEM:
                renderizar_actor_caja_item(camara, (struct CajaItem*) actor);
                break;
            case ACTOR_GLOBO_AEROSTATICO_CAJA_ITEM:
                renderizar_actor_caja_item(camara, (struct CajaItem*) actor);
                break;
        }
    }
}

void renderizar_actores_circuito(struct desconocido_struct_800DC5EC* parametro0) {
    Camara* camara = parametro0->camara;
    u16 contador_camino = parametro0->contador_camino;
    SIN_USO s32 relleno[12];
    s32 i;

    struct Actor* actor;
    SIN_USO Vec3f sp4_c = { 0.0f, 5.0f, 10.0f };
    f32 sp48 = senos(camara->rot[1] - GRADOS(180));
    f32 temporal_f0 = coss(camara->rot[1] - GRADOS(180));

    dato_801502C0[0][0] = temporal_f0;
    dato_801502C0[0][2] = -sp48;
    dato_801502C0[2][2] = temporal_f0;
    dato_801502C0[1][0] = 0.0f;
    dato_801502C0[0][1] = 0.0f;
    dato_801502C0[2][1] = 0.0f;
    dato_801502C0[1][2] = 0.0f;
    dato_801502C0[0][3] = 0.0f;
    dato_801502C0[1][3] = 0.0f;
    dato_801502C0[2][3] = 0.0f;
    dato_801502C0[2][0] = sp48;
    dato_801502C0[1][1] = 1.0f;
    dato_801502C0[3][3] = 1.0f;

    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gSPSetLights1(display_list_cabeza++, dato_800DC610[1]);
    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

    if (seleccion_modo != BATALLA) {
        funcion_80297340(camara);
    }
    dato_8015F8E0 = 0;

    for (i = 0; i < TAMANIO_LISTA_ACTOR; i++) {
        actor = &lista_actor[i];

        if (actor->flags == 0) {
            continue;
        }
        switch (actor->type) {
            case ARBOL_ACTOR_MARIO_RACEWAY:
                renderizar_arbol_actor_mario_raceway(camara, dato_801502C0, actor);
                break;
            case ARBOL_ACTOR_YOSHI_VALLEY:
                renderizar_arbol_actor_yoshi_valley(camara, dato_801502C0, actor);
                break;
            case ARBOL_ACTOR_ROYAL_RACEWAY:
                renderizar_arbol_actor_royal_raceway(camara, dato_801502C0, actor);
                break;
            case ARBOL_ACTOR_MOO_MOO_FARM:
                renderizar_arbol_actor_moo_moo_farm(camara, dato_801502C0, actor);
                break;
            case actor_desconocido_0_x1_a:
                funcion_80299864(camara, dato_801502C0, actor);
                break;
            case ARBOL_ACTOR_BOWSERS_CASTLE:
                renderizar_arbol_actor_bowser_castle(camara, dato_801502C0, actor);
                break;
            case ARBUSTO_ACTOR_BOWSERS_CASTLE:
                renderizar_arbusto_actor_bowser_castle(camara, dato_801502C0, actor);
                break;
            case ARBOL_ACTOR_FRAPPE_SNOWLAND:
                renderizar_arbol_actor_frappe_snowland(camara, dato_801502C0, actor);
                break;
            case CACTUS1_ACTOR_KALAMARI_DESERT:
                renderizar_cactus1_arbol_actor_kalimari_desert(camara, dato_801502C0, actor);
                break;
            case CACTUS2_ACTOR_KALAMARI_DESERT:
                renderizar_cactus2_arbol_actor_kalimari_desert(camara, dato_801502C0, actor);
                break;
            case CACTUS3_ACTOR_KALAMARI_DESERT:
                renderizar_cactus3_arbol_actor_kalimari_desert(camara, dato_801502C0, actor);
                break;
            case ROCA_CAYENDO_ACTOR:
                renderizar_roca_cayendo_actor(camara, (struct RocaCayendo*) actor);
                break;
            case ACTOR_KIWANO_FRUTA:
                renderizar_actor_kiwano_fruta(camara, dato_801502C0, actor);
                break;
            case ACTOR_BANANA:
                renderizar_banana_actor(camara, dato_801502C0, (struct BananaActor*) actor);
                break;
            case ACTOR_CAPARAZON_VERDE:
                renderizar_actor_caparazon_verde(camara, dato_801502C0, (struct ActorCaparazon*) actor);
                break;
            case ACTOR_CAPARAZON_ROJO:
                renderizar_actor_caparazon_rojo(camara, dato_801502C0, (struct ActorCaparazon*) actor);
                break;
            case AZUL_ACTOR_CAPARAZON_ESPINOSO:
                renderizar_actor_caparazon_azul(camara, dato_801502C0, (struct ActorCaparazon*) actor);
                break;
            case ACTOR_PLANTA_PIRANHA:
                renderizar_actor_planta_piranha(camara, dato_801502C0, (struct PlantaPiranha*) actor);
                break;
            case MOTOR_TREN_ACTOR:
                renderizar_motor_tren_actor(camara, (struct AutomovilTren*) actor);
                break;
            case TENDER_TREN_ACTOR:
                renderizar_tender_tren_actor(camara, (struct AutomovilTren*) actor);
                break;
            case ACTOR_TREN_PASAJERO_AUTOMOVIL:
                renderizar_actor_tren_pasajero_automovil(camara, (struct AutomovilTren*) actor);
                break;
            case VACA_ACTOR:
                renderizar_vaca_actor(camara, dato_801502C0, actor);
                break;
            case actor_desconocido_0_x14:
                funcion_8029AC18(camara, dato_801502C0, actor);
                break;
            case ACTOR_MARIO_CARTEL:
                renderizar_actor_mario_cartel(camara, dato_801502C0, actor);
                break;
            case ACTOR_WARIO_CARTEL:
                renderizar_actor_wario_cartel(camara, actor);
                break;
            case ARBOL_PALMERA_ACTOR:
                renderizar_arbol_palmera_actor(camara, dato_801502C0, (struct ArbolPalmera*) actor);
                break;
            case BARCO_PALETA_ACTOR:
                renderizar_barco_paleta_actor(camara, (struct BarcoRuedaPaleta*) actor, dato_801502C0, contador_camino);
                break;
            case CAMION_CAJA_ACTOR:
                renderizar_camion_caja_actor(camara, actor);
                break;
            case OMNIBUS_ESCUELA_ACTOR:
                renderizar_omnibus_escuela_actor(camara, actor);
                break;
            case CAMION_CISTERNA_ACTOR:
                renderizar_camion_cisterna_actor(camara, actor);
                break;
            case AUTOMOVIL_ACTOR:
                renderizar_automovil_actor(camara, actor);
                break;
            case ACTOR_PASO_A_NIVEL:
                renderizar_actor_paso_a_nivel(camara, (struct PasoANivel*) actor);
                break;
            case ACTOR_YOSHI_HUEVO:
                renderizar_actor_yoshi_huevo(camara, dato_801502C0, (struct YoshiValleyHuevo*) actor, contador_camino);
                break;
        }
    }
    switch (id_circuito_actual) {
        case CIRCUITO_MOO_MOO_FARM:
            renderizar_vacas(camara, dato_801502C0, actor);
            break;
        case CIRCUITO_DK_JUNGLE:
            renderizar_arboles_palmera(camara, dato_801502C0, actor);
            break;
    }
}

void actualizar_actores_circuito(void) {
    struct Actor* actor;
    s32 i;
    for (i = 0; i < TAMANIO_LISTA_ACTOR; i++) {

        actor = &lista_actor[i];
        if (actor->flags == 0) {
            continue;
        }

        switch (actor->type) {
            case ROCA_CAYENDO_ACTOR:
                actualizar_rocas_cayendo_actor((struct RocaCayendo*) actor);
                break;
            case ACTOR_CAPARAZON_VERDE:
                actualizar_actor_caparazon_verde((struct ActorCaparazon*) actor);
                break;
            case ACTOR_CAPARAZON_ROJO:
                actualizar_actor_rojo_caparazon_azul((struct ActorCaparazon*) actor);
                break;
            case AZUL_ACTOR_CAPARAZON_ESPINOSO:
                actualizar_actor_rojo_caparazon_azul((struct ActorCaparazon*) actor);
                break;
            case ACTOR_KIWANO_FRUTA:
                actualizar_actor_kiwano_fruta((struct KiwanoFruta*) actor);
                break;
            case ACTOR_BANANA:
                actualizar_banana_actor((struct BananaActor*) actor);
                break;
            case BARCO_PALETA_ACTOR:
                actualizar_barco_paleta_actor((struct BarcoRuedaPaleta*) actor);
                break;
            case MOTOR_TREN_ACTOR:
                actualizar_motor_tren_actor((struct AutomovilTren*) actor);
                break;
            case TENDER_TREN_ACTOR:
                actualizar_tender_tren_actor((struct AutomovilTren*) actor);
                break;
            case ACTOR_TREN_PASAJERO_AUTOMOVIL:
                actualizar_actor_tren_pasajero_automovil((struct AutomovilTren*) actor);
                break;
            case ACTOR_CAJA_ITEM:
                actualizar_actor_caja_item((struct CajaItem*) actor);
                break;
            case ACTOR_GLOBO_AEROSTATICO_CAJA_ITEM:
                actualizar_actor_caja_item_globo_aerostatico((struct CajaItem*) actor);
                break;
            case ACTOR_CAJA_ITEM_FALSA:
                actualizar_actor_caja_item_falsa((struct CajaItemFalsa*) actor);
                break;
            case ACTOR_PLANTA_PIRANHA:
                actualizar_actor_planta_piranha((struct PlantaPiranha*) actor);
                break;
            case GRUPO_BANANA_ACTOR:
                actualizar_grupo_banana_actor((struct PadreGrupoBanana*) actor);
                break;
            case TRIPLE_ACTOR_CAPARAZON_VERDE:
                actualizar_caparazon_triple_actor((TriplePadreCaparazon*) actor, ACTOR_CAPARAZON_VERDE);
                break;
            case TRIPLE_ACTOR_CAPARAZON_ROJO:
                actualizar_caparazon_triple_actor((TriplePadreCaparazon*) actor, ACTOR_CAPARAZON_ROJO);
                break;
            case ACTOR_MARIO_CARTEL:
                actualizar_actor_mario_cartel(actor);
                break;
            case ACTOR_WARIO_CARTEL:
                actualizar_actor_wario_cartel(actor);
                break;
            case ACTOR_PASO_A_NIVEL:
                actualizar_actor_paso_a_nivel((struct PasoANivel*) actor);
                break;
            case ARBOL_ACTOR_MARIO_RACEWAY:
            case ARBOL_ACTOR_YOSHI_VALLEY:
            case ARBOL_ACTOR_ROYAL_RACEWAY:
            case ARBOL_ACTOR_MOO_MOO_FARM:
            case ARBOL_PALMERA_ACTOR:
            case actor_desconocido_0_x1_a:
            case actor_desconocido_0_x1_b:
            case ARBOL_ACTOR_BOWSERS_CASTLE:
            case ARBOL_ACTOR_FRAPPE_SNOWLAND:
            case CACTUS1_ACTOR_KALAMARI_DESERT:
            case CACTUS2_ACTOR_KALAMARI_DESERT:
            case CACTUS3_ACTOR_KALAMARI_DESERT:
            case ARBUSTO_ACTOR_BOWSERS_CASTLE:
                actualizar_planta_estatico_actor(actor);
                break;
            case ACTOR_YOSHI_HUEVO:
                actualizar_actor_yoshi_huevo((struct YoshiValleyHuevo*) actor);
                break;
        }
    }
    evaluar_colision_para_actores_destructible();
    comprobar_item_usar_jugador();
}
