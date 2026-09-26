// Actores basicos

u8* dato_802BA050;
u8* dato_802BA054;
u8* dato_802BA058;

struct Actor* actor_globo_aerostatico_caja_item;
s8 tlut_caparazon_rojo[512];
u16 dato_802BA260;

void limpiar_rojo_y_caparazones_verdes(struct ActorCaparazon* caparazon) {
    s32 indice_actor;
    struct ActorCaparazon* comparar;

    for (indice_actor = actores_permanente_num; indice_actor < TAMANIO_LISTA_ACTOR; indice_actor++) {
        comparar = (struct ActorCaparazon*) &lista_actor[indice_actor];
        if ((caparazon != comparar) && !(comparar->flags & ES_ACTOR_NO_VENCIDO) && (comparar->type == ACTOR_CAPARAZON_VERDE)) {
            if (comparar->state == CAPARAZON_MOVIENDO) {
                eliminar_actor_en_lista_actor_vigente(indice_actor);
            }
            caparazones_aparecido_num--;
            destruir_actor((struct Actor*) comparar);
            return;
        }
    }

    for (indice_actor = actores_permanente_num; indice_actor < TAMANIO_LISTA_ACTOR; indice_actor++) {
        comparar = (struct ActorCaparazon*) &lista_actor[indice_actor];
        if ((caparazon != comparar) && !(comparar->flags & ES_ACTOR_NO_VENCIDO) && (comparar->type == ACTOR_CAPARAZON_ROJO)) {
            switch (comparar->state) {
                case CAPARAZON_MOVIENDO:
                case CAPARAZON_ROJO_BLOQUEO_EN:
                case TRIPLE_CAPARAZON_VERDE:
                case CAPARAZON_VERDE_CORREDOR_GOLPE_A:
                case CAPARAZON_AZUL_BLOQUEO_EN:
                case CAPARAZON_AZUL_OBJETIVO_ELIMINADO:
                    eliminar_actor_en_lista_actor_vigente(indice_actor);
                case CAPARAZON_DESTRUIDO:
                    caparazones_aparecido_num -= 1;
                    destruir_actor((struct Actor*) comparar);
                    return;
                default:
                    break;
            }
        }
    }

    for (indice_actor = actores_permanente_num; indice_actor < TAMANIO_LISTA_ACTOR; indice_actor++) {
        comparar = (struct ActorCaparazon*) &lista_actor[indice_actor];
        if ((caparazon != comparar) && (comparar->type == ACTOR_CAPARAZON_VERDE)) {
            switch (comparar->state) {
                case CAPARAZON_MOVIENDO:
                    eliminar_actor_en_lista_actor_vigente(indice_actor);
                case CAPARAZON_DESTRUIDO:
                    caparazones_aparecido_num -= 1;
                    destruir_actor((struct Actor*) comparar);
                    return;
            }
        }
    }

    for (indice_actor = actores_permanente_num; indice_actor < TAMANIO_LISTA_ACTOR; indice_actor++) {
        comparar = (struct ActorCaparazon*) &lista_actor[indice_actor];
        if ((caparazon != comparar) && (comparar->type == ACTOR_CAPARAZON_ROJO)) {
            switch (comparar->state) {
                case CAPARAZON_MOVIENDO:
                case CAPARAZON_ROJO_BLOQUEO_EN:
                case TRIPLE_CAPARAZON_VERDE:
                case CAPARAZON_VERDE_CORREDOR_GOLPE_A:
                case CAPARAZON_AZUL_BLOQUEO_EN:
                case CAPARAZON_AZUL_OBJETIVO_ELIMINADO:
                    eliminar_actor_en_lista_actor_vigente(indice_actor);
                case CAPARAZON_DESTRUIDO:
                    caparazones_aparecido_num -= 1;
                    destruir_actor((struct Actor*) comparar);
                    return;
            }
        }
    }
}

void inicializar_actor(struct Actor* actor, Vec3f pos_inicial, Vec3s rot_inicial, Vec3f velocidad_inicial, s16 tipo_actor) {
    copiar_retorno_vec3f(actor->pos, pos_inicial);
    copiar_vec3s(actor->rot, rot_inicial);
    copiar_retorno_vec3f(actor->velocidad, velocidad_inicial);
    actor->type = tipo_actor;
    actor->flags = -0x8000;
    actor->desconocido_04 = 0;
    actor->state = 0;
    actor->desconocido_08 = 0.0f;
    actor->tamanio_caja_envolvente = 0.0f;
    funcion_802AAAAC(&actor->desconocido30);
    switch (tipo_actor) {
        case CAMION_CAJA_ACTOR:
            if ((s32) dato_802BA260 >= 3) {
                dato_802BA260 = 0;
            }
            actor->state = (s16) dato_802BA260;
            dato_802BA260 += 1;
            break;
        case ACTOR_YOSHI_HUEVO:
            actor->flags |= 0x4000;
            actor->desconocido_08 = 70.0f;
            actor->tamanio_caja_envolvente = 20.0f;
            actor->velocidad[0] = actor->pos[0];
            actor->velocidad[1] = actor->pos[1];
            actor->velocidad[2] = actor->pos[2] + 70.0f;
            break;
        case ACTOR_KIWANO_FRUTA:
            actor->state = 0;
            actor->rot[0] = 0;
            actor->rot[1] = 0;
            actor->rot[2] = 0;
            actor->tamanio_caja_envolvente = 2.0f;
            break;
        case ROCA_CAYENDO_ACTOR:
            actor->flags |= 0x4000;
            actor->tamanio_caja_envolvente = 10.0f;
            break;
        case MOTOR_TREN_ACTOR:
            actor->desconocido_08 = 10.0f;
            break;
        case ACTOR_BANANA:
            actor->flags = actor->flags | 0x4000 | 0x1000;
            actor->tamanio_caja_envolvente = 2.0f;
            break;
        case ACTOR_CAPARAZON_VERDE:
            caparazones_aparecido_num += 1;
            actor->desconocido_04 = 0;
            actor->tamanio_caja_envolvente = 4.0f;
            actor->flags = actor->flags | 0x4000 | 0x2000 | 0x1000;
            if ((s32) caparazones_aparecido_num >= 0x15) {
                limpiar_rojo_y_caparazones_verdes((struct ActorCaparazon*) actor);
            }
            break;
        case ACTOR_CAPARAZON_ROJO:
            caparazones_aparecido_num += 1;
            actor->desconocido_04 = 0;
            actor->tamanio_caja_envolvente = 4.0f;
            actor->flags = actor->flags | 0x4000 | 0x2000 | 0x1000;
            if ((s32) caparazones_aparecido_num >= 0x15) {
                limpiar_rojo_y_caparazones_verdes((struct ActorCaparazon*) actor);
            }
            break;
        case ARBOL_ACTOR_MARIO_RACEWAY:
            caparazones_aparecido_num += 1;
            actor->flags |= 0x4000;
            actor->state = 0x0043;
            actor->tamanio_caja_envolvente = 3.0f;
            actor->desconocido_08 = 20.0f;
            break;
        case ARBOL_ACTOR_YOSHI_VALLEY:
            actor->flags |= 0x4000;
            actor->state = 0x0043;
            actor->tamanio_caja_envolvente = 3.0f;
            actor->desconocido_08 = 23.0f;
            break;
        case ARBOL_ACTOR_ROYAL_RACEWAY:
            actor->flags |= 0x4000;
            actor->state = 0x0043;
            actor->tamanio_caja_envolvente = 3.0f;
            actor->desconocido_08 = 17.0f;
            break;
        case ARBOL_ACTOR_MOO_MOO_FARM:
            actor->state = 0x0043;
            actor->flags = -0x8000;
            actor->tamanio_caja_envolvente = 3.0f;
            actor->desconocido_08 = 17.0f;
            break;
        case 26:
            actor->flags |= 0x4000;
            actor->state = 0x0043;
            actor->tamanio_caja_envolvente = 3.0f;
            actor->desconocido_08 = 17.0f;
            break;
        case 28:
            actor->state = 0x0043;
            actor->flags = -0x8000;
            actor->tamanio_caja_envolvente = 3.0f;
            actor->desconocido_08 = 17.0f;
            break;
        case 33:
            actor->flags |= 0x4000;
            actor->state = 0x0043;
            actor->tamanio_caja_envolvente = 3.0f;
            actor->desconocido_08 = 17.0f;
            break;
        case 29:
            actor->flags |= 0x4000;
            actor->state = 0x0043;
            actor->tamanio_caja_envolvente = 3.0f;
            actor->desconocido_08 = 17.0f;
            break;
        case 30:
            actor->flags |= 0x4000;
            actor->state = 0x0019;
            actor->tamanio_caja_envolvente = 3.0f;
            actor->desconocido_08 = 7.0f;
            break;
        case 31:
            actor->flags |= 0x4000;
            actor->state = 0x0019;
            actor->tamanio_caja_envolvente = 3.0f;
            actor->desconocido_08 = 7.0f;
            break;
        case 32:
            actor->flags |= 0x4000;
            actor->state = 0x0019;
            actor->tamanio_caja_envolvente = 3.0f;
            actor->desconocido_08 = 7.0f;
            break;
        case ARBOL_PALMERA_ACTOR:
            actor->flags |= 0x4000;
            actor->state = 0x003C;
            actor->tamanio_caja_envolvente = 3.0f;
            actor->desconocido_08 = 13.0f;
            break;
        case ACTOR_CAJA_ITEM_FALSA:
            actor->flags = actor->flags | 0x4000 | 0x1000;
            actor->desconocido_08 = 0.35f;
            actor->tamanio_caja_envolvente = 1.925f;
            comprobar_colision_envolvente(&actor->desconocido30, 1.925f, actor->pos[0], actor->pos[1], actor->pos[2]);
            break;
        case ACTOR_GLOBO_AEROSTATICO_CAJA_ITEM:
            actor->flags |= 0x4000;
            actor->desconocido_04 = 0;
            actor->state = 5;
            actor->tamanio_caja_envolvente = 5.5f;
            break;
        case ACTOR_CAJA_ITEM:
            actor->flags |= 0x4000;
            actor->desconocido_04 = 0;
            actor->state = 0;
            actor->tamanio_caja_envolvente = 5.5f;
            break;
        case ACTOR_PLANTA_PIRANHA:
            actor->flags |= 0x4000;
            actor->state = 0x001E;
            actor->tamanio_caja_envolvente = 5.0f;
            break;
        default:
            break;
    }
}

void actor_no_renderizado(Camara* parametro0, struct Actor* parametro1) {
    switch (parametro0 - camara1) {
        case JUGADOR_UNO:
            parametro1->flags &= ~(1 << JUGADOR_UNO);
            break;
        case JUGADOR_DOS:
            parametro1->flags &= ~(1 << JUGADOR_DOS);
            break;
        case JUGADOR_TRES:
            parametro1->flags &= ~(1 << JUGADOR_TRES);
            break;
        case JUGADOR_CUATRO:
            parametro1->flags &= ~(1 << JUGADOR_CUATRO);
            break;
    }
}

void actor_renderizado(Camara* parametro0, struct Actor* parametro1) {
    switch (parametro0 - camara1) {
        case JUGADOR_UNO:
            parametro1->flags |= 1 << JUGADOR_UNO;
            break;
        case JUGADOR_DOS:
            parametro1->flags |= 1 << JUGADOR_DOS;
            break;
        case JUGADOR_TRES:
            parametro1->flags |= 1 << JUGADOR_TRES;
            break;
        case JUGADOR_CUATRO:
            parametro1->flags |= 1 << JUGADOR_CUATRO;
            break;
    }
}

void funcion_80297340(Camara* parametro0) {
    Mat4 sp38;
    s16 temporal_ = dato_8015F8D0[2];
    s32 max_objetos_alcanzado;

    if (estado_juego == SECUENCIA_CREDITOS) {
        return;
    }

    trasladar_mtxf(sp38, dato_8015F8D0);

    max_objetos_alcanzado = fijar_posicion_render(sp38, 0) == 0;
    if (max_objetos_alcanzado) {
        return;
    }

    if (temporal_ < parametro0->pos[2]) {
        if (dato_800DC5BC != 0) {

            gDPSetFogColor(display_list_cabeza++, dato_801625EC, dato_801625F4, dato_801625F0, 0xFF);
            gSPDisplayList(display_list_cabeza++, &dato_0D001C20);
        } else {
            gSPDisplayList(display_list_cabeza++, &dato_0D001B90);
        }
    } else if (dato_800DC5BC != 0) {

        gDPSetFogColor(display_list_cabeza++, dato_801625EC, dato_801625F4, dato_801625F0, 0xFF);
        gSPDisplayList(display_list_cabeza++, &dato_0D001C88);
    } else {
        gSPDisplayList(display_list_cabeza++, &dato_0D001BD8);
    }
}

SIN_USO void funcion_80297524(uintptr_t direccion, s32 ancho, s32 altura) {
    gDPLoadTextureBlock(display_list_cabeza++, VIRTUAL_A_FISICO(direccion), G_IM_FMT_RGBA, G_IM_SIZ_16b, ancho, altura, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
}

void funcion_802976D8(Vec3s parametro0) {
    parametro0[0] = 0x4000;
    parametro0[1] = 0;
    parametro0[2] = 0;
}

void funcion_802976EC(Colision* parametro0, Vec3s parametro1) {
    f32 x, y, z;

    if (parametro0->unk34 == 0) {
        funcion_802976D8(parametro1);
        return;
    }

    x = parametro0->vector_orientacion[0];
    y = parametro0->vector_orientacion[1];
    z = parametro0->vector_orientacion[2];

    parametro1[0] = atan2s(z, y) + 0x4000;
    parametro1[1] = 0;
    parametro1[2] = atan2s(x, y);
}

void funcion_80297760(struct Actor* parametro0, Vec3f parametro1) {
    parametro1[0] = parametro0->pos[0];
    parametro1[1] = parametro0->pos[1];
    parametro1[2] = parametro0->pos[2];
    parametro1[1] = calcular_altura_superficie(parametro1[0], parametro1[1], parametro1[2], parametro0->desconocido30.indice_zx_malla);
}

void funcion_802977B0(Jugador* parametro0) {
    parametro0->ruedas[DERECHA_FRENTE].desconocido_14 |= 2;
    parametro0->ruedas[IZQUIERDA_FRENTE].desconocido_14 |= 2;
    parametro0->ruedas[DERECHA_ATRAS].desconocido_14 |= 2;
    parametro0->ruedas[IZQUIERDA_ATRAS].desconocido_14 |= 2;
}

void funcion_802977E4(Jugador* parametro0) {
    parametro0->ruedas[DERECHA_FRENTE].desconocido_14 &= ~2 & 0xFFFF;
    parametro0->ruedas[IZQUIERDA_FRENTE].desconocido_14 &= ~2 & 0xFFFF;
    parametro0->ruedas[DERECHA_ATRAS].desconocido_14 &= ~2 & 0xFFFF;
    parametro0->ruedas[IZQUIERDA_ATRAS].desconocido_14 &= ~2 & 0xFFFF;
}

void inicializar_caparazon_rojo_textura(void) {
    s16* caparazon_rojo_textura = (s16*) &tlut_caparazon_rojo[0];
    s16* caparazon_verde_textura = (s16*) VIRTUAL_A_PHYSICAL2(tabla_segmento[SEGMENT_NUMBER2(tlut_comun_caparazon_verde)] +
                                                           SEGMENT_OFFSET(tlut_comun_caparazon_verde));
    s16 color_pixel, color_rojo, color_verde, color_azul, alpha_color;
    s32 i;
    for (i = 0; i < 256; i++) {
        color_pixel = TEXEL16(*caparazon_verde_textura);
        color_rojo = color_pixel & 0xF800;
        color_verde = color_pixel & 0x7C0;
        color_azul = color_pixel & 0x3E;
        alpha_color = color_pixel & 0x1;

        *caparazon_rojo_textura =
            TEXEL16((color_rojo >> 5) | (color_verde << 5) | color_azul | alpha_color);
        caparazon_verde_textura++;
        caparazon_rojo_textura++;
    }
}

SIN_USO void funcion_80297944(void) {};

void funcion_8029794C(Vec3f pos, Vec3s rot, f32 escalar) {
    Mat4 sp20;
    pos[1] += 2.0f;

    rotar_traslacion_zxy_mtxf(sp20, pos, rot);
    escalar_mtxf(sp20, escalar);
    if (fijar_posicion_render(sp20, 0) != 0) {
        gSPDisplayList(display_list_cabeza++, dato_0D007B20);
        pos[1] -= 2.0f;
    }
}

void funcion_802979F8(struct Actor* parametro0, SIN_USO f32 parametro1) {
    Vec3f pos;
    Vec3s rot;

    if (parametro0->desconocido30.unk34 != 0) {

        funcion_802976EC(&parametro0->desconocido30, rot);
        funcion_80297760(parametro0, pos);
        funcion_8029794C(pos, rot, 0.45f);
    }
}

#include "carrera/actores/vaca/dibujar.inc.c"

#include "carrera/actores/huevo_yoshi/actualizar.inc.c"

void actualizar_planta_estatico_actor(struct Actor* parametro0) {
    if (((parametro0->flags & 0x800) == 0) && ((parametro0->flags & 0x400) != 0)) {
        parametro0->pos[1] = parametro0->pos[1] + 4.0f;
        if (parametro0->pos[1] > 800.0f) {
            parametro0->flags |= 0x800;
        }
    }
}

#include "carrera/actores/fruta_kiwano/actualizar.inc.c"

#include "carrera/actores/barco_paletas/actualizar.inc.c"

#include "carrera/actores/tren/actualizar.inc.c"

#include "carrera/actores/planta_piranha/actualizar.inc.c"

#include "carrera/actores/planta_piranha/dibujar.inc.c"

void renderizar_vacas(Camara* camara, Mat4 parametro1, SIN_USO struct Actor* actor) {
    u16 temporal_s1;
    f32 temporal_f0;
    struct DatosAparicionActor* variable_t1;
    struct DatosAparicionActor* variable_s1;
    struct DatosAparicionActor* variable_s5;
    Vec3f sp88;
    u32 sonido_cosa = SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x90, 0x4D);
    s32 segmento = SEGMENT_NUMBER2(d_circuito_moo_moo_farm_aparicion_vaca);
    s32 desplazamiento = SEGMENT_OFFSET(d_circuito_moo_moo_farm_aparicion_vaca);

    variable_t1 = (struct DatosAparicionActor*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    dato_8015F704 = 6.4e7f;
    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    variable_s5 = NULL;
    variable_s1 = variable_t1;
    while (variable_s1->pos[0] != FIN_DE_DATOS_APARICION) {
        sp88[0] = variable_s1->pos[0] * sentido_circuito;
        sp88[1] = variable_s1->pos[1];
        sp88[2] = variable_s1->pos[2];
        temporal_f0 =
            distancia_si_visible(camara->pos, sp88, camara->rot[1], 0.0f, acercar_camara[camara - camara1], 4000000.0f);
        if (temporal_f0 > 0.0f) {
            if (temporal_f0 < dato_8015F704) {
                dato_8015F704 = temporal_f0;
                variable_s5 = variable_s1;
            }
            parametro1[3][0] = sp88[0];
            parametro1[3][1] = sp88[1];
            parametro1[3][2] = sp88[2];
            if ((cantidad_objeto_matriz < MTX_OBJETO_POOL_TAMANIO) && (fijar_posicion_render(parametro1, 0) != 0)) {
                switch (variable_s1->algun_id) {
                    case 0:
                        gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_vaca1_dl);
                        break;
                    case 1:
                        gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_vaca2_dl);
                        break;
                    case 2:
                        gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_vaca3_dl);
                        break;
                    case 3:
                        gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_vaca4_dl);
                        break;
                    case 4:
                        gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_vaca5_dl);
                        break;
                }
            } else {
                return;
            }
        }
        variable_s1++;
    }

    if ((camara == camara1) && (variable_s5 != NULL)) {
        if (dato_8015F700 == 0) {
            temporal_s1 = variable_s5 - variable_t1;
            if ((temporal_s1 != dato_8015F702) && (dato_8015F704 < 160000.0f)) {
                funcion_800C99E0(dato_8015F708, sonido_cosa);
                dato_8015F708[0] = variable_s5->pos[0] * sentido_circuito;
                dato_8015F708[1] = variable_s5->pos[1];
                dato_8015F708[2] = variable_s5->pos[2];
                dato_8015F702 = temporal_s1;
                funcion_800C98B8(dato_8015F708, dato_802B91C8, sonido_cosa);
                dato_8015F700 = 0x00F0;
            }
        } else {
            dato_8015F700 -= 1;
        }
    }
}

void evaluar_colision_jugador_palmera_arboles(Jugador* jugador) {
    Vec3f pos;
    s32 segmento = SEGMENT_NUMBER2(d_circuito_dks_jungle_parkway_aparicion_arbol);
    s32 desplazamiento = SEGMENT_OFFSET(d_circuito_dks_jungle_parkway_aparicion_arbol);
    struct DesconocidoActorAparicionDatos* datos = (struct DesconocidoActorAparicionDatos*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);

    while (datos->pos[0] != FIN_DE_DATOS_APARICION) {
        pos[0] = datos->pos[0] * sentido_circuito;
        pos[1] = datos->pos[1];
        pos[2] = datos->pos[2];
        if (consultar_y_resolver_colision_jugador_actor(jugador, pos, 5.0f, 40.0f, 0.8f) == COLISION) {
            if ((jugador->efectos & EFECTO_ESTRELLA) != 0) {
                funcion_800C98B8(jugador->pos, jugador->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x10));
                funcion_800C90F4((u8) (jugador - jugador_uno),
                              (jugador->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x0D));
                datos->algun_id |= 0x400;
            }
            if ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) == 0) {
                funcion_800C9060((u8) (jugador - jugador_uno), SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x70, 0x18));
            }
            break;
        }
        datos++;
    }
}

void evaluar_colision_jugadores_palmera_arboles(void) {
    s32 index;

    for (index = 0; index < 4; index++) {
        if (((jugadores[index].type & 0xC000) != 0) &&
            ((s8) (u8) obtener_tipo_superficie(jugadores[index].colision.indice_zx_malla) == PASTO)) {
            evaluar_colision_jugador_palmera_arboles(&jugadores[index]);
        }
    }
}

void funcion_80298D10(void) {
    s32 segmento = SEGMENT_NUMBER2(d_circuito_dks_jungle_parkway_aparicion_arbol);
    s32 desplazamiento = SEGMENT_OFFSET(d_circuito_dks_jungle_parkway_aparicion_arbol);
    struct DesconocidoActorAparicionDatos* temporal_v1 =
        (struct DesconocidoActorAparicionDatos*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);

    while (temporal_v1->pos[0] != FIN_DE_DATOS_APARICION) {
        temporal_v1->pos[1] = temporal_v1->desconocido8;
        temporal_v1->algun_id &= 0xF;
        temporal_v1++;
    }
}

void renderizar_arboles_palmera(Camara* camara, Mat4 parametro1, SIN_USO struct Actor* actor) {
    s32 segmento = SEGMENT_NUMBER2(d_circuito_dks_jungle_parkway_aparicion_arbol);
    s32 desplazamiento = SEGMENT_OFFSET(d_circuito_dks_jungle_parkway_aparicion_arbol);
    struct DesconocidoActorAparicionDatos* variable_s1 =
        (struct DesconocidoActorAparicionDatos*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    SIN_USO s32 relleno;
    Vec3f sp_d4;
    f32 variable_f22;
    Mat4 sp90;
    Vec3s sp88 = { 0, 0, 0 };
    s32 probar;

    if (estado_juego == SECUENCIA_CREDITOS) {
        variable_f22 = 9000000.0f;
    } else {
        variable_f22 = 1000000.0f;
    }

    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);

    while (variable_s1->pos[0] != FIN_DE_DATOS_APARICION) {
        probar = variable_s1->algun_id;
        if (probar & 0x0800) {
            variable_s1++;
            continue;
        }

        if ((probar & 0x0400) && ((juego_en_pausa == 0) || (camara == camara1))) {
            variable_s1->pos[1] += 0xA;
            if (variable_s1->pos[1] >= 0x321) {
                variable_s1->algun_id |= 0x0800;
            }
        }
        sp_d4[0] = variable_s1->pos[0] * sentido_circuito;
        sp_d4[1] = variable_s1->pos[1];
        sp_d4[2] = variable_s1->pos[2];

        if (distancia_si_visible(camara->pos, sp_d4, camara->rot[1], 0.0f, acercar_camara[camara - camara1], variable_f22) <
            0.0f) {
            variable_s1++;
            continue;
        }

        probar &= 0xF;
        probar = (s16) probar;
        if (probar == 6) {
            rotar_traslacion_zxy_mtxf(sp90, sp_d4, sp88);
            if (!(cantidad_objeto_matriz < MTX_OBJETO_POOL_TAMANIO)) {
                break;
            }
            fijar_posicion_render(sp90, 0);
            goto etiqueta_ficticia;
        } else {
            parametro1[3][0] = sp_d4[0];
            parametro1[3][1] = sp_d4[1];
            parametro1[3][2] = sp_d4[2];
            if (cantidad_objeto_matriz < MTX_OBJETO_POOL_TAMANIO) {
                fijar_posicion_render(parametro1, 0);
            etiqueta_ficticia:
                gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
                switch (probar) {
                    case 0:
                        gSPDisplayList(display_list_cabeza++, d_circuito_dks_jungle_parkway_arbol1_dl);
                        break;
                    case 4:
                        gSPDisplayList(display_list_cabeza++, d_circuito_dks_jungle_parkway_arbol2_dl);
                        break;
                    case 5:
                        gSPDisplayList(display_list_cabeza++, d_circuito_dks_jungle_parkway_arbol3_dl);
                        break;
                    case 6:
                        gSPDisplayList(display_list_cabeza++, d_circuito_dks_jungle_parkway_arbol_palmera_dl);
                        break;
                }
            } else {
                break;
            }
            variable_s1++;
        }
    }
}

#include "carrera/actores/arboles/dibujar.inc.c"

#include "carrera/actores/fruta_kiwano/dibujar.inc.c"

void renderizar_caparazon_actor(Camara* camara, Mat4 matriz, struct ActorCaparazon* caparazon) {
    SIN_USO s16 relleno;
    u16 temporal_t8;
    SIN_USO s32 relleno2;
    s16 sp58[15] =
        { 0x0000, 0x0400, 0x0800, 0x0c00, 0x1000, 0x1400, 0x1800, 0x1c00,
          0x1c00, 0x1800, 0x1400, 0x1000, 0x0c00, 0x0800, 0x0400 };
    uintptr_t phi_t3;

    f32 temporal_f0 =
        distancia_si_visible(camara->pos, caparazon->pos, camara->rot[1], 0, acercar_camara[camara - camara1], 490000.0f);
    s32 max_objetos_alcanzado;
    if (temporal_f0 < 0.0f) {
        actor_no_renderizado(camara, (struct Actor*) caparazon);
        return;
    }

    actor_renderizado(camara, (struct Actor*) caparazon);
    if (temporal_f0 < 40000.0f) {
        funcion_802979F8((struct Actor*) caparazon, 3.4f);
    }
    if (caparazon->type == AZUL_ACTOR_CAPARAZON_ESPINOSO) {
        phi_t3 = (uintptr_t) dato_802BA054;
    } else {
        phi_t3 = (uintptr_t) dato_802BA050;
    }
    temporal_t8 = (u16) caparazon->velocidad_rot / GRADOS(24);
    phi_t3 += sp58[temporal_t8];

    matriz[3][0] = caparazon->pos[0];
    matriz[3][1] = (caparazon->pos[1] - caparazon->tamanio_caja_envolvente) + 1.0f;
    matriz[3][2] = caparazon->pos[2];

    max_objetos_alcanzado = fijar_posicion_render(matriz, 0) == 0;
    if (max_objetos_alcanzado) {
        return;
    }

    gDPLoadTextureBlock(display_list_cabeza++, VIRTUAL_A_FISICO(phi_t3), G_IM_FMT_CI, G_IM_SIZ_8b, 32, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    if (temporal_t8 < 8) {
        gSPDisplayList(display_list_cabeza++, dato_0D005338);
    } else {
        gSPDisplayList(display_list_cabeza++, dato_0D005368);
    }
}

SIN_USO s16 dato_802B8808[] = { 0x0014, 0x0028, 0x0000, 0x0000 };

SIN_USO s16 dato_802B8810[] = { 0x0fc0, 0x0000, 0xffff, 0xffff, 0x0014, 0x0000, 0x0000, 0x0000, 0x0fc0, 0x0fc0,
                            0xffff, 0xffff, 0xffec, 0x0000, 0x0000, 0x0000, 0x0000, 0x0fc0, 0xffff, 0xffff,
                            0xffec, 0x0028, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff };

#include "carrera/actores/caparazon_verde/dibujar.inc.c"

#include "carrera/actores/caparazones_azul_y_rojo/dibujar.inc.c"

#include "carrera/actores/banana/dibujar.inc.c"

#include "carrera/actores/cartel_wario/actualizar.inc.c"

#include "carrera/actores/paso_a_nivel/actualizar.inc.c"

#include "carrera/actores/cartel_mario/actualizar.inc.c"

SIN_USO void funcion_8029ABD4(f32* pos, s16 estado) {
    actores_num = 0;
    lista_actor[aparecer_actor_en_pos(pos, actor_desconocido_0_x14)].state = estado;
}

void funcion_8029AC18(Camara* camara, Mat4 parametro1, struct Actor* parametro2) {
    if (distancia_si_visible(camara->pos, parametro2->pos, camara->rot[1], 0, acercar_camara[camara - camara1], 4000000.0f) <
        0) {
        return;
    }

    parametro1[3][0] = parametro2->pos[0];
    parametro1[3][1] = parametro2->pos[1] - parametro2->tamanio_caja_envolvente;
    parametro1[3][2] = parametro2->pos[2];

    if (fijar_posicion_render(parametro1, 0) != 0) {
        gSPDisplayList(display_list_cabeza++, &dato_0D001750);

        switch (parametro2->state) {
            case 0:
                gSPDisplayList(display_list_cabeza++, &dato_0D001780);
                break;
            case 1:
                gSPDisplayList(display_list_cabeza++, &dato_0D001798);
                break;
            case 2:
                gSPDisplayList(display_list_cabeza++, &dato_0D0017B0);
                break;
            case 3:
                gSPDisplayList(display_list_cabeza++, &dato_0D0017C8);
                break;
            case 4:
                gSPDisplayList(display_list_cabeza++, &dato_0D0017E0);
                break;
            case 5:
                gSPDisplayList(display_list_cabeza++, &dato_0D0017F8);
                break;
            case 6:
                gSPDisplayList(display_list_cabeza++, &dato_0D001810);
                break;
            case 7:
                gSPDisplayList(display_list_cabeza++, &dato_0D001828);
                break;
        }
    }
}

SIN_USO void funcion_8029AE14() {
}

#include "carrera/actores/barco_paletas/dibujar.inc.c"

#include "carrera/actores/camion_caja/dibujar.inc.c"

#include "carrera/actores/omnibus_escolar/dibujar.inc.c"

#include "carrera/actores/auto/dibujar.inc.c"

#include "carrera/actores/camion_cisterna/dibujar.inc.c"

#include "carrera/actores/tren/dibujar.inc.c"

#include "carrera/actores/roca_que_cae/dibujar.inc.c"

void aparecer_plantas_piranha(struct DatosAparicionActor* aparecer_datos) {
    s32 segmento = SEGMENT_NUMBER2(aparecer_datos);
    s32 desplazamiento = SEGMENT_OFFSET(aparecer_datos);
    struct DatosAparicionActor* temporal_s0 = (struct DatosAparicionActor*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    struct PlantaPiranha* temporal_v1;
    SIN_USO s32 relleno;
    Vec3f pos_inicial;
    Vec3f velocidad_inicial;
    Vec3s rot_inicial;
    s32 temporal_;

    fijar_vec3f(velocidad_inicial, 0, 0, 0);
    fijar_vec3s(rot_inicial, 0, 0, 0);

    while (temporal_s0->pos[0] != FIN_DE_DATOS_APARICION) {
        pos_inicial[0] = temporal_s0->pos[0] * sentido_circuito;
        pos_inicial[1] = temporal_s0->pos[1];
        pos_inicial[2] = temporal_s0->pos[2];
        temporal_ = agregar_actor_a_ranura_vacio(pos_inicial, rot_inicial, velocidad_inicial, ACTOR_PLANTA_PIRANHA);
        temporal_v1 = (struct PlantaPiranha*) &lista_actor[temporal_];
        temporal_v1->estados_visibilidad[0] = 0;
        temporal_v1->estados_visibilidad[1] = 0;
        temporal_v1->estados_visibilidad[2] = 0;
        temporal_v1->estados_visibilidad[3] = 0;
        temporal_v1->temporizadores[0] = 0;
        temporal_v1->temporizadores[1] = 0;
        temporal_v1->temporizadores[2] = 0;
        temporal_v1->temporizadores[3] = 0;
        temporal_s0++;
    }
}

void aparecer_arboles_palmera(struct DatosAparicionActor* aparecer_datos) {
    s32 segmento = SEGMENT_NUMBER2(aparecer_datos);
    s32 desplazamiento = SEGMENT_OFFSET(aparecer_datos);
    struct DatosAparicionActor* temporal_s0 = (struct DatosAparicionActor*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    struct ArbolPalmera* temporal_v1;
    Vec3f pos_inicial;
    Vec3f velocidad_inicial;
    Vec3s rot_inicial;
    s32 temporal_;

    fijar_vec3f(velocidad_inicial, 0, 0, 0);
    fijar_vec3s(rot_inicial, 0, 0, 0);

    while (temporal_s0->pos[0] != FIN_DE_DATOS_APARICION) {
        pos_inicial[0] = temporal_s0->pos[0] * sentido_circuito;
        pos_inicial[1] = temporal_s0->pos[1];
        pos_inicial[2] = temporal_s0->pos[2];
        temporal_ = agregar_actor_a_ranura_vacio(pos_inicial, rot_inicial, velocidad_inicial, ARBOL_PALMERA_ACTOR);
        temporal_v1 = (struct ArbolPalmera*) &lista_actor[temporal_];

        temporal_v1->variante = temporal_s0->algun_id;
        comprobar_colision_envolvente((Colision*) &temporal_v1->desconocido30, 5.0f, temporal_v1->pos[0], temporal_v1->pos[1], temporal_v1->pos[2]);
        funcion_802976EC((Colision*) &temporal_v1->desconocido30, temporal_v1->rot);
        temporal_s0++;
    }
}
