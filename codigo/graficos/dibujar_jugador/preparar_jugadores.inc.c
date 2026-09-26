// Preparar jugadores

#ifdef TARGET_PS2
/* Los sprites de los karts */
void ps2_kart_mio0decode(u8* orig_, u8* dst);
#define mio0decode ps2_kart_mio0decode
#endif
#include "carrera/aparicion_jugadores.h"

s8 framebuffer_renderizado_por_jugador[] = { 0x00, 0x02, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02 };

s32 jugadores_a_cantidad_render = 0;

SIN_USO void* dato_800DDB5C[3] = { framebuffer_0, framebuffer_1, framebuffer_2 };

s16 jugadores_a_id_jugador_render[8];
s16 jugadores_a_id_pantalla_render[8];
Jugador* jugadores_a_jugador_render[8];
s16 cantidad_efecto_matriz;
s32 dato_80164AF4[3];
struct_d_802F1F80* paleta_jugador;
u8* textura_superior_kart;
u8* textura_inferior_kart;
u16 efecto_rojo_jugador[8];
u16 efecto_verde_jugador[8];
u16 efecto_azul_jugador[8];
u16 efecto_cian_jugador[8];
u16 efecto_magenta_jugador[8];
u16 efecto_amarillo_jugador[8];
SIN_USO u16 efecto_blanco_jugador[8];
s32 dato_80164B80[296];
s16 dato_80165020[40];
Vec3f velocidad_ultimo_jugador[8];
s16 ultimo_selector_frame_anim[4][8];
s16 ultimo_selector_grupo_anim[4][8];
s16 dato_80165150[4][8];
s16 dato_80165190[4][8];
s16 dato_801651D0[4][8];

void funcion_8001F980(s32* parametro0, s32* parametro1) {
    if ((modo_demo == 1) || (dato_80164A28 != 0) || (dato_8015F894 != 0)) {
        *parametro0 = 0xAA;
    } else {
        *parametro0 = 0;
    }
    if (dato_80164A28 != 0) {
        *parametro1 = 0xAA;
        return;
    }
    *parametro1 = 0;
}

void funcion_8001F9E4(Jugador* jugador, Camara* camara, s8 id_pantalla) {
    SIN_USO s32 relleno;
    s32 sp30;
    s32 sp2_c;
    SIN_USO s32 relleno2;

    obtener_indice_jugador_para_jugador(jugador);
    funcion_8001F980(&sp30, &sp2_c);

    jugador->desconocido_002 &= ~(desconocido_002_desconocido_0_x2 << (id_pantalla * 4));
    jugador->desconocido_002 &= ~(LADO_DE_KART << (id_pantalla * 4));

    if (comprobar_colision_camara_jugador(jugador, camara, (f32) (dato_80165578 + sp30), (f32) (dato_8016557A + sp2_c)) == 1) {
        jugador->desconocido_002 |= desconocido_002_desconocido_0_x2 << (id_pantalla * 4);
    }
    if (comprobar_colision_camara_jugador(jugador, camara, (f32) dato_80165580, (f32) dato_80165582) == 1) {
        jugador->desconocido_002 |= LADO_DE_KART << (id_pantalla * 4);
    }
}

u16 comprobar_colision_camara_jugador(Jugador* jugador, Camara* camara, f32 parametro2, f32 parametro3) {
    SIN_USO f32 relleno[6];
    f32 sp64;
    f32 sp60;
    f32 sp5_c;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4_c;
    f32 sp48;
    f32 sp44;
    s16 variable_v0;
    u16 devuelto;

    devuelto = false;
    switch (modo_pantalla_activo) { /* irregular */
        case MODO_PANTALLA_1P:
            variable_v0 = 0x293C;
            break;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            variable_v0 = 0x3058;
            break;
        case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
            variable_v0 = 0x1FFE;
            break;
        default:
            if (1) {}
            variable_v0 = 0x1FFE;
            break;
    }
    sp4_c = (parametro2 * coss((camara->rot[1] - variable_v0))) + camara->pos[2];
    sp58 = (parametro2 * senos((camara->rot[1] - variable_v0))) + camara->pos[0];
    sp48 = (parametro2 * coss((camara->rot[1] + variable_v0))) + camara->pos[2];
    sp54 = (parametro2 * senos((camara->rot[1] + variable_v0))) + camara->pos[0];
    sp44 = (parametro3 * coss((camara->rot[1] + (135 * GRADOS(1))))) + camara->pos[2];
    sp50 = (parametro3 * senos((camara->rot[1] + (135 * GRADOS(1))))) + camara->pos[0];

    sp64 = ((sp4_c - jugador->pos[2]) * (sp54 - jugador->pos[0])) - ((sp48 - jugador->pos[2]) * (sp58 - jugador->pos[0]));
    sp60 = ((sp48 - jugador->pos[2]) * (sp50 - jugador->pos[0])) - ((sp44 - jugador->pos[2]) * (sp54 - jugador->pos[0]));
    sp5_c = ((sp44 - jugador->pos[2]) * (sp58 - jugador->pos[0])) - ((sp4_c - jugador->pos[2]) * (sp50 - jugador->pos[0]));

    if (((sp64 >= 0) && (sp60 >= 0) && (sp5_c >= 0)) || (((sp64) <= 0) && (sp60 <= 0) && (sp5_c <= 0))) {
        devuelto = true;
    }
    return devuelto;
}

u16 funcion_8001FD78(Jugador* jugador, f32 pos_x, SIN_USO f32 parametro2, f32 pos_z) {
    f32 sp64;
    f32 sp60;
    f32 sp5c;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 temporal_f14;
    f32 cosa0;
    f32 cosa1;
    u16 devuelto;

    devuelto = false;

    sp58 = (70.0f * coss(((jugador->desconocido_0C0 - jugador->rotacion[1]) - (10 * GRADOS(1))))) + jugador->pos[2];
    sp64 = (70.0f * senos(((jugador->desconocido_0C0 - jugador->rotacion[1]) - (10 * GRADOS(1))))) + jugador->pos[0];
    sp54 = (70.0f * coss(((jugador->desconocido_0C0 - jugador->rotacion[1]) + (10 * GRADOS(1))))) + jugador->pos[2];
    sp60 = (70.0f * senos(((jugador->desconocido_0C0 - jugador->rotacion[1]) + (10 * GRADOS(1))))) + jugador->pos[0];
    sp50 = (10.0f * coss(((jugador->desconocido_0C0 - jugador->rotacion[1]) + (40 * GRADOS(1))))) + jugador->pos[2];
    sp5c = (10.0f * senos(((jugador->desconocido_0C0 - jugador->rotacion[1]) + (40 * GRADOS(1))))) + jugador->pos[0];

    temporal_f14 = ((sp58 - pos_z) * (sp60 - pos_x)) - ((sp54 - pos_z) * (sp64 - pos_x));
    cosa0 = ((sp54 - pos_z) * (sp5c - pos_x)) - ((sp50 - pos_z) * (sp60 - pos_x));
    cosa1 = ((sp50 - pos_z) * (sp64 - pos_x)) - ((sp58 - pos_z) * (sp5c - pos_x));
    if (((temporal_f14 >= 0) && (cosa0 >= 0) && (cosa1 >= 0)) || ((temporal_f14 <= 0) && (cosa0 <= 0) && (cosa1 <= 0))) {
        devuelto = true;
    }
    return devuelto;
}

void renderizar_jugador_inicializacion(Jugador* jugador, Camara* camara, s8 id_jugador, s8 id_pantalla) {
    SIN_USO s32 relleno[4];
    s32 sp4_c;
    s32 sp48;
    SIN_USO s32 relleno2;
    s32 temporal_v0;
    s32 temporal_v0_2;

    if ((jugador->type & EXISTE_JUGADOR) == EXISTE_JUGADOR) {
        funcion_8001F9E4(jugador, camara, id_pantalla);
        temporal_v0 = desconocido_002_desconocido_0_x2 << (id_pantalla << 2);
        if (temporal_v0 == (jugador->desconocido_002 & temporal_v0)) {
            if (!(jugador->type & SECUENCIA_INICIO_JUGADOR)) {
                funcion_8002934C(jugador, camara, id_pantalla, id_jugador);
            } else {
                funcion_8002934C(jugador, camara, id_pantalla, id_jugador);
                jugador->acel_pendiente = 0;
                jugador->desconocido_206 = 0;
                jugador->desconocido_050[id_pantalla] = 0;
            }
        }
        funcion_8001F980(&sp4_c, &sp48);
        temporal_v0_2 = ANIMACION_CAMBIANDO << (id_pantalla << 2);
        if ((temporal_v0 == (jugador->desconocido_002 & temporal_v0)) && (temporal_v0_2 == (jugador->desconocido_002 & temporal_v0_2))) {
            if ((comprobar_colision_camara_jugador(jugador, camara, dato_80165570 + sp4_c, dato_80165572 + sp48) == 1) & 0xFFFF) {
                jugadores_a_id_jugador_render[jugadores_a_cantidad_render] = (s16) id_jugador;
                jugadores_a_id_pantalla_render[jugadores_a_cantidad_render] = (s16) id_pantalla;
                jugadores_a_jugador_render[jugadores_a_cantidad_render] = jugador;
                jugadores_a_cantidad_render += 1;
                dato_80165190[id_pantalla][id_jugador] = 0;
                ultimo_selector_frame_anim[id_pantalla][id_jugador] = jugador->anim_frame_selector[id_pantalla];
                ultimo_selector_grupo_anim[id_pantalla][id_jugador] = jugador->anim_selector_grupo[id_pantalla];
                dato_80165150[id_pantalla][id_jugador] = jugador->desconocido_0A8;
                dato_801651D0[id_pantalla][id_jugador] += 1;
                if (dato_801651D0[id_pantalla][id_jugador] == 2) {
                    dato_801651D0[id_pantalla][id_jugador] = 0;
                }
            } else {
                if ((comprobar_colision_camara_jugador(jugador, camara, dato_80165574 + sp4_c, dato_80165576) == 1) & 0xFFFF) {
                    if ((framebuffer_renderizado == framebuffer_renderizado_por_jugador[id_jugador]) ||
                        ((ultimo_selector_frame_anim[id_pantalla][id_jugador] - jugador->anim_frame_selector[id_pantalla]) > 0x13) ||
                        ((ultimo_selector_frame_anim[id_pantalla][id_jugador] - jugador->anim_frame_selector[id_pantalla]) < -0x13) ||
                        (dato_80165190[id_pantalla][id_jugador] == (s16) 1U)) {
                        jugadores_a_id_jugador_render[jugadores_a_cantidad_render] = (s16) id_jugador;
                        jugadores_a_id_pantalla_render[jugadores_a_cantidad_render] = (s16) id_pantalla;
                        jugadores_a_jugador_render[jugadores_a_cantidad_render] = jugador;
                        jugadores_a_cantidad_render += 1;
                        ultimo_selector_frame_anim[id_pantalla][id_jugador] = jugador->anim_frame_selector[id_pantalla];
                        ultimo_selector_grupo_anim[id_pantalla][id_jugador] = jugador->anim_selector_grupo[id_pantalla];
                        dato_80165150[id_pantalla][id_jugador] = jugador->desconocido_0A8;
                        dato_80165190[id_pantalla][id_jugador] = 0;
                        dato_801651D0[id_pantalla][id_jugador] += 1;
                        if (dato_801651D0[id_pantalla][id_jugador] == 2) {
                            dato_801651D0[id_pantalla][id_jugador] = 0;
                        }
                    }
                } else {
                    if (((ultimo_selector_frame_anim[id_pantalla][id_jugador] - jugador->anim_frame_selector[id_pantalla]) > 0x13) ||
                        ((ultimo_selector_frame_anim[id_pantalla][id_jugador] - jugador->anim_frame_selector[id_pantalla]) < -0x13) ||
                        (dato_80165190[id_pantalla][id_jugador] == (s16) 1U)) {
                        jugadores_a_id_jugador_render[jugadores_a_cantidad_render] = (s16) id_jugador;
                        jugadores_a_id_pantalla_render[jugadores_a_cantidad_render] = (s16) id_pantalla;
                        jugadores_a_jugador_render[jugadores_a_cantidad_render] = jugador;
                        jugadores_a_cantidad_render += 1;
                        ultimo_selector_frame_anim[id_pantalla][id_jugador] = (s16) jugador->anim_frame_selector[id_pantalla];
                        ultimo_selector_grupo_anim[id_pantalla][id_jugador] = jugador->anim_selector_grupo[id_pantalla];
                        dato_80165150[id_pantalla][id_jugador] = jugador->desconocido_0A8;
                        dato_80165190[id_pantalla][id_jugador] = 0;
                        dato_801651D0[id_pantalla][id_jugador] += 1;
                        if (dato_801651D0[id_pantalla][id_jugador] == 2) {
                            dato_801651D0[id_pantalla][id_jugador] = 0;
                        }
                    }
                }
            }
        }
    }
}

void renderizar_particula_kart_en_pantalla_uno_textura_kart_carga_y(void) {
    s16 i;

    cargar_kart_textura_no_bloqueante(jugadores_a_jugador_render[0], jugadores_a_id_jugador_render[0], jugadores_a_id_pantalla_render[0],
                                   jugadores_a_id_pantalla_render[0],
                                   dato_801651D0[jugadores_a_id_pantalla_render[0]][jugadores_a_id_jugador_render[0]]);
    renderizar_particula_kart_en_pantalla_uno(copia_jugador_uno, JUGADOR_UNO, JUGADOR_UNO);
    renderizar_particula_kart_en_pantalla_uno(jugador_dos, JUGADOR_DOS, JUGADOR_UNO);
    renderizar_particula_kart_en_pantalla_uno(jugador_tres, JUGADOR_TRES, JUGADOR_UNO);
    renderizar_particula_kart_en_pantalla_uno(jugador_cuatro, JUGADOR_CUATRO, JUGADOR_UNO);
    if (modo_pantalla_activo != PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
        renderizar_particula_kart_en_pantalla_uno(jugador_cinco, JUGADOR_CINCO, JUGADOR_UNO);
        renderizar_particula_kart_en_pantalla_uno(jugador_seis, JUGADOR_SEIS, JUGADOR_UNO);
        renderizar_particula_kart_en_pantalla_uno(jugador_siete, JUGADOR_SIETE, JUGADOR_UNO);
        renderizar_particula_kart_en_pantalla_uno(jugador_ocho, JUGADOR_OCHO, JUGADOR_UNO);
    }
    osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);

    for (i = 1; i < jugadores_a_cantidad_render; i++) {

        cargar_kart_textura_no_bloqueante(jugadores_a_jugador_render[i], jugadores_a_id_jugador_render[i],
                                       jugadores_a_id_pantalla_render[i], jugadores_a_id_pantalla_render[i],
                                       dato_801651D0[jugadores_a_id_pantalla_render[i]][jugadores_a_id_jugador_render[i]]);

        mio0decode(
            (u8*) textura_kart_codificado[dato_801651D0[jugadores_a_id_pantalla_render[i - 1]][jugadores_a_id_jugador_render[i - 1]]]
                                     [jugadores_a_id_pantalla_render[i - 1]][jugadores_a_id_jugador_render[i - 1]]
                                         .desconocido_00,
            dato_802BFB80
                .tamanio_arreglo_8[dato_801651D0[jugadores_a_id_pantalla_render[i - 1]][jugadores_a_id_jugador_render[i - 1]]]
                           [jugadores_a_id_pantalla_render[i - 1]][jugadores_a_id_jugador_render[i - 1]]
                .arreglo_indice_pixel);
        osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
    }

    mio0decode((u8*) textura_kart_codificado[dato_801651D0[jugadores_a_id_pantalla_render[jugadores_a_cantidad_render - 1]]
                                                   [jugadores_a_id_jugador_render[jugadores_a_cantidad_render - 1]]]
                                        [jugadores_a_id_pantalla_render[jugadores_a_cantidad_render - 1]]
                                        [jugadores_a_id_jugador_render[jugadores_a_cantidad_render - 1]]
                                            .desconocido_00,
               dato_802BFB80
                   .tamanio_arreglo_8[dato_801651D0[jugadores_a_id_pantalla_render[jugadores_a_cantidad_render - 1]]
                                         [jugadores_a_id_jugador_render[jugadores_a_cantidad_render - 1]]]
                              [jugadores_a_id_pantalla_render[jugadores_a_cantidad_render - 1]]
                              [jugadores_a_id_jugador_render[jugadores_a_cantidad_render - 1]]
                   .arreglo_indice_pixel);
}

void renderizar_particula_kart_en_pantalla_dos_textura_kart_carga_y(void) {
    s16 variable_s0;

    cargar_kart_textura_no_bloqueante(jugadores_a_jugador_render[0], jugadores_a_id_jugador_render[0], jugadores_a_id_pantalla_render[0],
                                   jugadores_a_id_pantalla_render[0],
                                   dato_801651D0[jugadores_a_id_pantalla_render[0]][jugadores_a_id_jugador_render[0]]);
    renderizar_particula_kart_en_pantalla_dos(copia_jugador_uno, JUGADOR_UNO, JUGADOR_DOS);
    renderizar_particula_kart_en_pantalla_dos(jugador_dos, JUGADOR_DOS, JUGADOR_DOS);
    renderizar_particula_kart_en_pantalla_dos(jugador_tres, JUGADOR_TRES, JUGADOR_DOS);
    renderizar_particula_kart_en_pantalla_dos(jugador_cuatro, JUGADOR_CUATRO, JUGADOR_DOS);
    if (modo_pantalla_activo != PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
        renderizar_particula_kart_en_pantalla_dos(jugador_cinco, JUGADOR_CINCO, JUGADOR_DOS);
        renderizar_particula_kart_en_pantalla_dos(jugador_seis, JUGADOR_SEIS, JUGADOR_DOS);
        renderizar_particula_kart_en_pantalla_dos(jugador_siete, JUGADOR_SIETE, JUGADOR_DOS);
        renderizar_particula_kart_en_pantalla_dos(jugador_ocho, JUGADOR_OCHO, JUGADOR_DOS);
    }
    osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
    for (variable_s0 = 1; variable_s0 < jugadores_a_cantidad_render; variable_s0++) {
        cargar_kart_textura_no_bloqueante(jugadores_a_jugador_render[variable_s0], jugadores_a_id_jugador_render[variable_s0],
                                       jugadores_a_id_pantalla_render[variable_s0], jugadores_a_id_pantalla_render[variable_s0],
                                       dato_801651D0[jugadores_a_id_pantalla_render[variable_s0]][jugadores_a_id_jugador_render[variable_s0]]);
        mio0decode(
            (u8*) textura_kart_codificado[dato_801651D0[jugadores_a_id_pantalla_render[variable_s0 - 1]]
                                                [jugadores_a_id_jugador_render[variable_s0 - 1]]]
                                     [jugadores_a_id_pantalla_render[variable_s0 - 1]][jugadores_a_id_jugador_render[variable_s0 - 1]]
                                         .desconocido_00,
            dato_802BFB80
                .tamanio_arreglo_8[dato_801651D0[jugadores_a_id_pantalla_render[variable_s0 - 1]][jugadores_a_id_jugador_render[variable_s0 - 1]]]
                           [jugadores_a_id_pantalla_render[variable_s0 - 1]][jugadores_a_id_jugador_render[variable_s0 - 1]]
                .arreglo_indice_pixel);
        osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
    }
    mio0decode((u8*) textura_kart_codificado[dato_801651D0[jugadores_a_id_pantalla_render[jugadores_a_cantidad_render - 1]]
                                                   [jugadores_a_id_jugador_render[jugadores_a_cantidad_render - 1]]]
                                        [jugadores_a_id_pantalla_render[jugadores_a_cantidad_render - 1]]
                                        [jugadores_a_id_jugador_render[jugadores_a_cantidad_render - 1]]
                                            .desconocido_00,
               dato_802BFB80
                   .tamanio_arreglo_8[dato_801651D0[jugadores_a_id_pantalla_render[jugadores_a_cantidad_render - 1]]
                                         [jugadores_a_id_jugador_render[jugadores_a_cantidad_render - 1]]]
                              [jugadores_a_id_pantalla_render[jugadores_a_cantidad_render - 1]]
                              [jugadores_a_id_jugador_render[jugadores_a_cantidad_render - 1]]
                   .arreglo_indice_pixel);
}

void renderizar_particula_kart_en_pantalla_tres_textura_kart_carga_y(void) {
    s16 variable_s0;

    cargar_kart_textura_no_bloqueante(jugadores_a_jugador_render[0], jugadores_a_id_jugador_render[0] + 4,
                                   jugadores_a_id_pantalla_render[0], jugadores_a_id_pantalla_render[0] - 2,
                                   dato_801651D0[jugadores_a_id_pantalla_render[0]][jugadores_a_id_jugador_render[0]]);
    renderizar_particula_kart_en_pantalla_tres(copia_jugador_uno, JUGADOR_UNO, JUGADOR_TRES);
    renderizar_particula_kart_en_pantalla_tres(jugador_dos, JUGADOR_DOS, JUGADOR_TRES);
    renderizar_particula_kart_en_pantalla_tres(jugador_tres, JUGADOR_TRES, JUGADOR_TRES);
    renderizar_particula_kart_en_pantalla_tres(jugador_cuatro, JUGADOR_CUATRO, JUGADOR_TRES);
    osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
    for (variable_s0 = 1; variable_s0 < jugadores_a_cantidad_render; variable_s0++) {
        cargar_kart_textura_no_bloqueante(jugadores_a_jugador_render[variable_s0], jugadores_a_id_jugador_render[variable_s0] + 4,
                                       jugadores_a_id_pantalla_render[variable_s0], jugadores_a_id_pantalla_render[variable_s0] - 2,
                                       dato_801651D0[jugadores_a_id_pantalla_render[variable_s0]][jugadores_a_id_jugador_render[variable_s0]]);
        mio0decode(
            (u8*) textura_kart_codificado
                [dato_801651D0[jugadores_a_id_pantalla_render[variable_s0 - 1]][jugadores_a_id_jugador_render[variable_s0 - 1]]]
                [jugadores_a_id_pantalla_render[variable_s0 - 1] - 2][jugadores_a_id_jugador_render[variable_s0 - 1] + 4]
                    .desconocido_00,
            dato_802BFB80
                .tamanio_arreglo_8[dato_801651D0[jugadores_a_id_pantalla_render[variable_s0 - 1]][jugadores_a_id_jugador_render[variable_s0 - 1]]]
                           [jugadores_a_id_pantalla_render[variable_s0 - 1] - 2][jugadores_a_id_jugador_render[variable_s0 - 1] + 4]
                .arreglo_indice_pixel);
        osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
    }
    mio0decode((u8*) textura_kart_codificado[dato_801651D0[jugadores_a_id_pantalla_render[jugadores_a_cantidad_render - 1]]
                                                   [jugadores_a_id_jugador_render[jugadores_a_cantidad_render - 1]]]
                                        [jugadores_a_id_pantalla_render[jugadores_a_cantidad_render - 1] - 2]
                                        [jugadores_a_id_jugador_render[jugadores_a_cantidad_render - 1] + 4]
                                            .desconocido_00,
               dato_802BFB80
                   .tamanio_arreglo_8[dato_801651D0[jugadores_a_id_pantalla_render[jugadores_a_cantidad_render - 1]]
                                         [jugadores_a_id_jugador_render[jugadores_a_cantidad_render - 1]]]
                              [jugadores_a_id_pantalla_render[jugadores_a_cantidad_render - 1] - 2]
                              [jugadores_a_id_jugador_render[jugadores_a_cantidad_render - 1] + 4]
                   .arreglo_indice_pixel);
}

void renderizar_particula_kart_en_pantalla_cuatro_textura_kart_carga_y(void) {
    s16 variable_s0;

    cargar_kart_textura_no_bloqueante(jugadores_a_jugador_render[0], jugadores_a_id_jugador_render[0] + 4,
                                   jugadores_a_id_pantalla_render[0], jugadores_a_id_pantalla_render[0] - 2,
                                   dato_801651D0[jugadores_a_id_pantalla_render[0]][jugadores_a_id_jugador_render[0]]);
    renderizar_particula_kart_en_pantalla_cuatro(copia_jugador_uno, JUGADOR_UNO, JUGADOR_CUATRO);
    renderizar_particula_kart_en_pantalla_cuatro(jugador_dos, JUGADOR_DOS, JUGADOR_CUATRO);
    renderizar_particula_kart_en_pantalla_cuatro(jugador_tres, JUGADOR_TRES, JUGADOR_CUATRO);
    renderizar_particula_kart_en_pantalla_cuatro(jugador_cuatro, JUGADOR_CUATRO, JUGADOR_CUATRO);
    osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
    for (variable_s0 = 1; variable_s0 < jugadores_a_cantidad_render; variable_s0++) {
        cargar_kart_textura_no_bloqueante(jugadores_a_jugador_render[variable_s0], jugadores_a_id_jugador_render[variable_s0] + 4,
                                       jugadores_a_id_pantalla_render[variable_s0], jugadores_a_id_pantalla_render[variable_s0] - 2,
                                       dato_801651D0[jugadores_a_id_pantalla_render[variable_s0]][jugadores_a_id_jugador_render[variable_s0]]);
        mio0decode(
            (u8*) textura_kart_codificado
                [dato_801651D0[jugadores_a_id_pantalla_render[variable_s0 - 1]][jugadores_a_id_jugador_render[variable_s0 - 1]]]
                [jugadores_a_id_pantalla_render[variable_s0 - 1] - 2][jugadores_a_id_jugador_render[variable_s0 - 1] + 4]
                    .desconocido_00,
            dato_802BFB80
                .tamanio_arreglo_8[dato_801651D0[jugadores_a_id_pantalla_render[variable_s0 - 1]][jugadores_a_id_jugador_render[variable_s0 - 1]]]
                           [jugadores_a_id_pantalla_render[variable_s0 - 1] - 2][jugadores_a_id_jugador_render[variable_s0 - 1] + 4]
                .arreglo_indice_pixel);
        osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);
    }
    mio0decode((u8*) textura_kart_codificado[dato_801651D0[jugadores_a_id_pantalla_render[jugadores_a_cantidad_render - 1]]
                                                   [jugadores_a_id_jugador_render[jugadores_a_cantidad_render - 1]]]
                                        [jugadores_a_id_pantalla_render[jugadores_a_cantidad_render - 1] - 2]
                                        [jugadores_a_id_jugador_render[jugadores_a_cantidad_render - 1] + 4]
                                            .desconocido_00,
               dato_802BFB80
                   .tamanio_arreglo_8[dato_801651D0[jugadores_a_id_pantalla_render[jugadores_a_cantidad_render - 1]]
                                         [jugadores_a_id_jugador_render[jugadores_a_cantidad_render - 1]]]
                              [jugadores_a_id_pantalla_render[jugadores_a_cantidad_render - 1] - 2]
                              [jugadores_a_id_jugador_render[jugadores_a_cantidad_render - 1] + 4]
                   .arreglo_indice_pixel);
}

void intentar_jugador_renderizado(Jugador* jugador, s8 id_jugador, s8 parametro2) {

    if (((jugador->type & EXISTE_JUGADOR) == EXISTE_JUGADOR) && ((jugador->type & jugador_desconocido_0_x40) == 0)) {
        if ((jugador->desconocido_002 & desconocido_002_desconocido_0_x2 << (parametro2 * 4)) == desconocido_002_desconocido_0_x2 << (parametro2 * 4)) {
            renderizar_jugador(jugador, id_jugador, parametro2);
        }
    }
}

void renderizar_jugadores_en_pantalla_uno(void) {
    SIN_USO s32 relleno;
    SIN_USO char* sp3_c[8] = {
        "S_MARIO", "S_LUIZI", "S_YOSSY", "S_KINOP", "S_DONKY", "S_WARIO", "S_PEACH", "S_KUPPA",
    };
    SIN_USO char* sp1_c[8] = {
        "J_MARIO", "J_LUIZI", "J_YOSSY", "J_KINOP", "J_DONKY", "J_WARIO", "J_PEACH", "J_KUPPA",
    };

    jugadores_a_cantidad_render = 0;
    renderizar_jugador_inicializacion(copia_jugador_uno, camara1, JUGADOR_UNO, JUGADOR_UNO);
    renderizar_jugador_inicializacion(jugador_dos, camara1, JUGADOR_DOS, JUGADOR_UNO);
    renderizar_jugador_inicializacion(jugador_tres, camara1, JUGADOR_TRES, JUGADOR_UNO);
    renderizar_jugador_inicializacion(jugador_cuatro, camara1, JUGADOR_CUATRO, JUGADOR_UNO);
    if (modo_pantalla_activo != PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
        renderizar_jugador_inicializacion(jugador_cinco, camara1, JUGADOR_CINCO, JUGADOR_UNO);
        renderizar_jugador_inicializacion(jugador_seis, camara1, JUGADOR_SEIS, JUGADOR_UNO);
        renderizar_jugador_inicializacion(jugador_siete, camara1, JUGADOR_SIETE, JUGADOR_UNO);
        renderizar_jugador_inicializacion(jugador_ocho, camara1, JUGADOR_OCHO, JUGADOR_UNO);
    }
    intentar_jugador_renderizado(jugador_uno, JUGADOR_UNO, JUGADOR_UNO);
    intentar_jugador_renderizado(jugador_dos, JUGADOR_DOS, JUGADOR_UNO);
    intentar_jugador_renderizado(jugador_tres, JUGADOR_TRES, JUGADOR_UNO);
    intentar_jugador_renderizado(jugador_cuatro, JUGADOR_CUATRO, JUGADOR_UNO);
    if (modo_pantalla_activo != PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
        intentar_jugador_renderizado(jugador_cinco, JUGADOR_CINCO, JUGADOR_UNO);
        intentar_jugador_renderizado(jugador_seis, JUGADOR_SEIS, JUGADOR_UNO);
        intentar_jugador_renderizado(jugador_siete, JUGADOR_SIETE, JUGADOR_UNO);
        intentar_jugador_renderizado(jugador_ocho, JUGADOR_OCHO, JUGADOR_UNO);
    }
    if (jugadores_a_cantidad_render != 0) {
        renderizar_particula_kart_en_pantalla_uno_textura_kart_carga_y();
    } else {
        renderizar_particula_kart_en_pantalla_uno(copia_jugador_uno, JUGADOR_UNO, JUGADOR_UNO);
        renderizar_particula_kart_en_pantalla_uno(jugador_dos, JUGADOR_DOS, JUGADOR_UNO);
        renderizar_particula_kart_en_pantalla_uno(jugador_tres, JUGADOR_TRES, JUGADOR_UNO);
        renderizar_particula_kart_en_pantalla_uno(jugador_cuatro, JUGADOR_CUATRO, JUGADOR_UNO);
        if (modo_pantalla_activo != PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
            renderizar_particula_kart_en_pantalla_uno(jugador_cinco, JUGADOR_CINCO, JUGADOR_UNO);
            renderizar_particula_kart_en_pantalla_uno(jugador_seis, JUGADOR_SEIS, JUGADOR_UNO);
            renderizar_particula_kart_en_pantalla_uno(jugador_siete, JUGADOR_SIETE, JUGADOR_UNO);
            renderizar_particula_kart_en_pantalla_uno(jugador_ocho, JUGADOR_OCHO, JUGADOR_UNO);
        }
    }
    jugadores_a_cantidad_render = 0;
}

s32 descarte[] = { 0, 0, 0 };

Vtx* vtx_jugador[] = { vtx_jugador_uno, vtx_jugador_dos, vtx_jugador_tres, vtx_jugador_cuatro, vtx_jugador_cinco, vtx_jugador_seis, vtx_jugador_siete, vtx_jugador_ocho };

f32 tamanio_personaje[] = { MARIO_TAMANIO, LUIGI_TAMANIO, YOSHI_TAMANIO, TOAD_TAMANIO, DK_TAMANIO, WARIO_TAMANIO, PEACH_TAMANIO, BOWSER_TAMANIO };

u8** kart_mario_ruedas_0[] = { kart_mario_168_rueda_0, kart_mario_147_rueda_0, kart_mario_126_rueda_0,
                             kart_mario_105_rueda_0, kart_mario_084_rueda_0, kart_mario_063_rueda_0,
                             kart_mario_042_rueda_0, kart_mario_021_rueda_0, kart_mario_000_rueda_0 };

u8** kart_mario_ruedas_1[] = { kart_mario_269_rueda_0, kart_mario_269_rueda_0, kart_mario_249_rueda_0,
                             kart_mario_229_rueda_0, kart_mario_229_rueda_0, kart_mario_229_rueda_0,
                             kart_mario_209_rueda_0, kart_mario_189_rueda_0, kart_mario_189_rueda_0 };

u8** kart_luigi_ruedas_0[] = { kart_luigi_168_rueda_0, kart_luigi_147_rueda_0, kart_luigi_126_rueda_0,
                             kart_luigi_105_rueda_0, kart_luigi_084_rueda_0, kart_luigi_063_rueda_0,
                             kart_luigi_042_rueda_0, kart_luigi_021_rueda_0, kart_luigi_000_rueda_0 };

u8** kart_luigi_ruedas_1[] = { kart_luigi_269_rueda_0, kart_luigi_269_rueda_0, kart_luigi_249_rueda_0,
                             kart_luigi_229_rueda_0, kart_luigi_229_rueda_0, kart_luigi_229_rueda_0,
                             kart_luigi_209_rueda_0, kart_luigi_189_rueda_0, kart_luigi_189_rueda_0 };

u8** kart_bowser_ruedas_0[] = { kart_bowser_168_rueda_0, kart_bowser_147_rueda_0, kart_bowser_126_rueda_0,
                              kart_bowser_105_rueda_0, kart_bowser_084_rueda_0, kart_bowser_063_rueda_0,
                              kart_bowser_042_rueda_0, kart_bowser_021_rueda_0, kart_bowser_000_rueda_0 };

u8** kart_bowser_ruedas_1[] = { kart_bowser_269_rueda_0, kart_bowser_269_rueda_0, kart_bowser_249_rueda_0,
                              kart_bowser_229_rueda_0, kart_bowser_229_rueda_0, kart_bowser_229_rueda_0,
                              kart_bowser_209_rueda_0, kart_bowser_189_rueda_0, kart_bowser_189_rueda_0 };

u8** kart_toad_ruedas_0[] = { kart_toad_168_rueda_0, kart_toad_147_rueda_0, kart_toad_126_rueda_0,
                            kart_toad_105_rueda_0, kart_toad_084_rueda_0, kart_toad_063_rueda_0,
                            kart_toad_042_rueda_0, kart_toad_021_rueda_0, kart_toad_000_rueda_0 };

u8** kart_toad_ruedas_1[] = { kart_toad_269_rueda_0, kart_toad_269_rueda_0, kart_toad_249_rueda_0,
                            kart_toad_229_rueda_0, kart_toad_229_rueda_0, kart_toad_229_rueda_0,
                            kart_toad_209_rueda_0, kart_toad_189_rueda_0, kart_toad_189_rueda_0 };

u8** kart_yoshi_ruedas_0[] = { kart_yoshi_168_rueda_0, kart_yoshi_147_rueda_0, kart_yoshi_126_rueda_0,
                             kart_yoshi_105_rueda_0, kart_yoshi_084_rueda_0, kart_yoshi_063_rueda_0,
                             kart_yoshi_042_rueda_0, kart_yoshi_021_rueda_0, kart_yoshi_000_rueda_0 };

u8** kart_yoshi_ruedas_1[] = { kart_yoshi_269_rueda_0, kart_yoshi_269_rueda_0, kart_yoshi_249_rueda_0,
                             kart_yoshi_229_rueda_0, kart_yoshi_229_rueda_0, kart_yoshi_229_rueda_0,
                             kart_yoshi_209_rueda_0, kart_yoshi_189_rueda_0, kart_yoshi_189_rueda_0 };

u8** kart_dk_ruedas_0[] = { kart_dk_168_rueda_0, kart_dk_147_rueda_0, kart_dk_126_rueda_0, kart_dk_105_rueda_0, kart_dk_084_rueda_0,
                          kart_dk_063_rueda_0, kart_dk_042_rueda_0, kart_dk_021_rueda_0, kart_dk_000_rueda_0 };

u8** kart_dk_ruedas_1[] = { kart_dk_269_rueda_0, kart_dk_269_rueda_0, kart_dk_249_rueda_0, kart_dk_229_rueda_0, kart_dk_229_rueda_0,
                          kart_dk_229_rueda_0, kart_dk_209_rueda_0, kart_dk_189_rueda_0, kart_dk_189_rueda_0 };

u8** kart_peach_ruedas_0[] = { kart_peach_168_rueda_0, kart_peach_147_rueda_0, kart_peach_126_rueda_0,
                             kart_peach_105_rueda_0, kart_peach_084_rueda_0, kart_peach_063_rueda_0,
                             kart_peach_042_rueda_0, kart_peach_021_rueda_0, kart_peach_000_rueda_0 };

u8** kart_peach_ruedas_1[] = { kart_peach_269_rueda_0, kart_peach_269_rueda_0, kart_peach_249_rueda_0,
                             kart_peach_229_rueda_0, kart_peach_229_rueda_0, kart_peach_229_rueda_0,
                             kart_peach_209_rueda_0, kart_peach_189_rueda_0, kart_peach_189_rueda_0 };

u8** kart_wario_ruedas_0[] = { kart_wario_168_rueda_0, kart_wario_147_rueda_0, kart_wario_126_rueda_0,
                             kart_wario_105_rueda_0, kart_wario_084_rueda_0, kart_wario_063_rueda_0,
                             kart_wario_042_rueda_0, kart_wario_021_rueda_0, kart_wario_000_rueda_0 };

u8** kart_wario_ruedas_1[] = { kart_wario_269_rueda_0, kart_wario_269_rueda_0, kart_wario_249_rueda_0,
                             kart_wario_229_rueda_0, kart_wario_229_rueda_0, kart_wario_229_rueda_0,
                             kart_wario_209_rueda_0, kart_wario_189_rueda_0, kart_wario_189_rueda_0 };

u16** ruedas_kart_0[] = { (u16**) kart_mario_ruedas_0, (u16**) kart_luigi_ruedas_0, (u16**) kart_yoshi_ruedas_0,
                         (u16**) kart_toad_ruedas_0,  (u16**) kart_dk_ruedas_0,    (u16**) kart_wario_ruedas_0,
                         (u16**) kart_peach_ruedas_0, (u16**) kart_bowser_ruedas_0 };

u16** ruedas_kart_1[] = { (u16**) kart_mario_ruedas_1, (u16**) kart_luigi_ruedas_1, (u16**) kart_yoshi_ruedas_1,
                         (u16**) kart_toad_ruedas_1,  (u16**) kart_dk_ruedas_1,    (u16**) kart_wario_ruedas_1,
                         (u16**) kart_peach_ruedas_1, (u16**) kart_bowser_ruedas_1 };

s32 dato_800DDE74[] = { 96, 128, 192, 256, 288, 384, 512, 544, 576 };

s32 margen_compilador_quizas = 0;

void renderizar_jugadores_en_pantalla_dos(void) {
    jugadores_a_cantidad_render = 0;
    renderizar_jugador_inicializacion(copia_jugador_uno, camara2, JUGADOR_UNO, JUGADOR_DOS);
    renderizar_jugador_inicializacion(jugador_dos, camara2, JUGADOR_DOS, JUGADOR_DOS);
    renderizar_jugador_inicializacion(jugador_tres, camara2, JUGADOR_TRES, JUGADOR_DOS);
    renderizar_jugador_inicializacion(jugador_cuatro, camara2, JUGADOR_CUATRO, JUGADOR_DOS);
    if (modo_pantalla_activo != PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
        renderizar_jugador_inicializacion(jugador_cinco, camara2, JUGADOR_CINCO, JUGADOR_DOS);
        renderizar_jugador_inicializacion(jugador_seis, camara2, JUGADOR_SEIS, JUGADOR_DOS);
        renderizar_jugador_inicializacion(jugador_siete, camara2, JUGADOR_SIETE, JUGADOR_DOS);
        renderizar_jugador_inicializacion(jugador_ocho, camara2, JUGADOR_OCHO, JUGADOR_DOS);
    }
    intentar_jugador_renderizado(jugador_uno, JUGADOR_UNO, JUGADOR_DOS);
    intentar_jugador_renderizado(jugador_dos, JUGADOR_DOS, JUGADOR_DOS);
    intentar_jugador_renderizado(jugador_tres, JUGADOR_TRES, JUGADOR_DOS);
    intentar_jugador_renderizado(jugador_cuatro, JUGADOR_CUATRO, JUGADOR_DOS);
    if (modo_pantalla_activo != PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
        intentar_jugador_renderizado(jugador_cinco, JUGADOR_CINCO, JUGADOR_DOS);
        intentar_jugador_renderizado(jugador_seis, JUGADOR_SEIS, JUGADOR_DOS);
        intentar_jugador_renderizado(jugador_siete, JUGADOR_SIETE, JUGADOR_DOS);
        intentar_jugador_renderizado(jugador_ocho, JUGADOR_OCHO, JUGADOR_DOS);
    }
    if (jugadores_a_cantidad_render != 0) {
        renderizar_particula_kart_en_pantalla_dos_textura_kart_carga_y();
    } else {
        renderizar_particula_kart_en_pantalla_dos(copia_jugador_uno, JUGADOR_UNO, JUGADOR_DOS);
        renderizar_particula_kart_en_pantalla_dos(jugador_dos, JUGADOR_DOS, JUGADOR_DOS);
        renderizar_particula_kart_en_pantalla_dos(jugador_tres, JUGADOR_TRES, JUGADOR_DOS);
        renderizar_particula_kart_en_pantalla_dos(jugador_cuatro, JUGADOR_CUATRO, JUGADOR_DOS);
        if (modo_pantalla_activo != PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
            renderizar_particula_kart_en_pantalla_dos(jugador_cinco, JUGADOR_CINCO, JUGADOR_DOS);
            renderizar_particula_kart_en_pantalla_dos(jugador_seis, JUGADOR_SEIS, JUGADOR_DOS);
            renderizar_particula_kart_en_pantalla_dos(jugador_siete, JUGADOR_SIETE, JUGADOR_DOS);
            renderizar_particula_kart_en_pantalla_dos(jugador_ocho, JUGADOR_OCHO, JUGADOR_DOS);
        }
    }
    jugadores_a_cantidad_render = 0;
}

void renderizar_jugadores_en_pantalla_tres(void) {
    jugadores_a_cantidad_render = 0;
    renderizar_jugador_inicializacion(copia_jugador_uno, camara3, JUGADOR_UNO, JUGADOR_TRES);
    renderizar_jugador_inicializacion(jugador_dos, camara3, JUGADOR_DOS, JUGADOR_TRES);
    renderizar_jugador_inicializacion(jugador_tres, camara3, JUGADOR_TRES, JUGADOR_TRES);
    renderizar_jugador_inicializacion(jugador_cuatro, camara3, JUGADOR_CUATRO, JUGADOR_TRES);
    intentar_jugador_renderizado(jugador_uno, JUGADOR_UNO, JUGADOR_TRES);
    intentar_jugador_renderizado(jugador_dos, JUGADOR_DOS, JUGADOR_TRES);
    intentar_jugador_renderizado(jugador_tres, JUGADOR_TRES, JUGADOR_TRES);
    intentar_jugador_renderizado(jugador_cuatro, JUGADOR_CUATRO, JUGADOR_TRES);
    if (jugadores_a_cantidad_render != 0) {
        renderizar_particula_kart_en_pantalla_tres_textura_kart_carga_y();
    } else {
        renderizar_particula_kart_en_pantalla_tres(copia_jugador_uno, JUGADOR_UNO, JUGADOR_TRES);
        renderizar_particula_kart_en_pantalla_tres(jugador_dos, JUGADOR_DOS, JUGADOR_TRES);
        renderizar_particula_kart_en_pantalla_tres(jugador_tres, JUGADOR_TRES, JUGADOR_TRES);
        renderizar_particula_kart_en_pantalla_tres(jugador_cuatro, JUGADOR_CUATRO, JUGADOR_TRES);
    }
    jugadores_a_cantidad_render = 0;
}

void renderizar_jugadores_en_pantalla_cuatro(void) {
    jugadores_a_cantidad_render = 0;
    renderizar_jugador_inicializacion(copia_jugador_uno, camara4, JUGADOR_UNO, JUGADOR_CUATRO);
    renderizar_jugador_inicializacion(jugador_dos, camara4, JUGADOR_DOS, JUGADOR_CUATRO);
    renderizar_jugador_inicializacion(jugador_tres, camara4, JUGADOR_TRES, JUGADOR_CUATRO);
    renderizar_jugador_inicializacion(jugador_cuatro, camara4, JUGADOR_CUATRO, JUGADOR_CUATRO);
    intentar_jugador_renderizado(jugador_uno, JUGADOR_UNO, JUGADOR_CUATRO);
    intentar_jugador_renderizado(jugador_dos, JUGADOR_DOS, JUGADOR_CUATRO);
    intentar_jugador_renderizado(jugador_tres, JUGADOR_TRES, JUGADOR_CUATRO);
    intentar_jugador_renderizado(jugador_cuatro, JUGADOR_CUATRO, JUGADOR_CUATRO);
    if (jugadores_a_cantidad_render != 0) {
        renderizar_particula_kart_en_pantalla_cuatro_textura_kart_carga_y();
    } else {
        renderizar_particula_kart_en_pantalla_cuatro(copia_jugador_uno, JUGADOR_UNO, JUGADOR_CUATRO);
        renderizar_particula_kart_en_pantalla_cuatro(jugador_dos, JUGADOR_DOS, JUGADOR_CUATRO);
        renderizar_particula_kart_en_pantalla_cuatro(jugador_tres, JUGADOR_TRES, JUGADOR_CUATRO);
        renderizar_particula_kart_en_pantalla_cuatro(jugador_cuatro, JUGADOR_CUATRO, JUGADOR_CUATRO);
    }
    jugadores_a_cantidad_render = 0;
}

void funcion_80021B0C(void) {
    funcion_8006E7CC(copia_jugador_uno, 0, 0);
    funcion_8006E7CC(jugador_dos, 1, 0);
    funcion_8006E7CC(jugador_tres, 2, 0);
    funcion_8006E7CC(jugador_cuatro, 3, 0);
    if (modo_pantalla_activo != PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
        funcion_8006E7CC(jugador_cinco, 4, 0);
        funcion_8006E7CC(jugador_seis, 5, 0);
        funcion_8006E7CC(jugador_siete, 6, 0);
        funcion_8006E7CC(jugador_ocho, 7, 0);
    }
    if (estado_juego == FINAL) {
        if (jugador_uno->kart_props & sin_uso_0_x_2000) {
            renderizar_creditos_sombra_jugador(jugador_uno, 0, 0);
        }
        if (jugador_dos->kart_props & sin_uso_0_x_2000) {
            renderizar_creditos_sombra_jugador(jugador_dos, 1, 0);
        }
        if (jugador_tres->kart_props & sin_uso_0_x_2000) {
            renderizar_creditos_sombra_jugador(jugador_tres, 2, 0);
        }
        if (jugador_cuatro->kart_props & sin_uso_0_x_2000) {
            renderizar_creditos_sombra_jugador(jugador_cuatro, 3, 0);
        }
    }
}

void funcion_80021C78(void) {
    funcion_8006E848(copia_jugador_uno, 0, 1);
    funcion_8006E848(jugador_dos, 1, 1);
    funcion_8006E848(jugador_tres, 2, 1);
    funcion_8006E848(jugador_cuatro, 3, 1);
    if (modo_pantalla_activo != PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
        funcion_8006E848(jugador_cinco, 4, 1);
        funcion_8006E848(jugador_seis, 5, 1);
        funcion_8006E848(jugador_siete, 6, 1);
        funcion_8006E848(jugador_ocho, 7, 1);
    }
}

void funcion_80021D40(void) {
    funcion_8006E8C4(copia_jugador_uno, 0, 2);
    funcion_8006E8C4(jugador_dos, 1, 2);
    funcion_8006E8C4(jugador_tres, 2, 2);
    funcion_8006E8C4(jugador_cuatro, 3, 2);
}

void funcion_80021DA8(void) {
    funcion_8006E940(copia_jugador_uno, 0, 3);
    funcion_8006E940(jugador_dos, 1, 3);
    funcion_8006E940(jugador_tres, 2, 3);
    funcion_8006E940(jugador_cuatro, 3, 3);
}

void trasladar_rotacion_mtxf(Mat4 dest, Vec3f pos, Vec3s orientacion) {
    SIN_USO f32 relleno[3];
    f32 sen_x = senos(orientacion[0]);
    f32 cos_x = coss(orientacion[0]);
    f32 sen_y = senos(orientacion[1]);
    f32 cos_y = coss(orientacion[1]);
    f32 sen_z = senos(orientacion[2]);
    f32 cos_z = coss(orientacion[2]);

    dest[0][0] = (cos_y * cos_z) + ((sen_x * sen_y) * sen_z);
    dest[1][0] = (-cos_y * sen_z) + ((sen_x * sen_y) * cos_z);
    dest[2][0] = cos_x * sen_y;
    dest[3][0] = pos[0];
    dest[0][1] = cos_x * sen_z;
    dest[1][1] = cos_x * cos_z;
    dest[2][1] = -sen_x;
    dest[3][1] = pos[1];
    dest[0][2] = (-sen_y * cos_z) + ((sen_x * cos_y) * sen_z);
    dest[1][2] = (sen_y * sen_z) + ((sen_x * cos_y) * cos_z);
    dest[2][2] = cos_x * cos_y;
    dest[3][2] = pos[2];
    dest[0][3] = 0.0f;
    dest[1][3] = 0.0f;
    dest[2][3] = 0.0f;
    dest[3][3] = 1.0f;
}

SIN_USO void funcion_80021F50(Mat4 parametro0, Vec3f parametro1) {
    parametro0[3][0] += parametro1[0];
    parametro0[3][1] += parametro1[1];
    parametro0[3][2] += parametro1[2];
}

void escala2_mtxf(Mat4 parametro0, f32 escalar) {
    parametro0[0][0] *= escalar;
    parametro0[1][0] *= escalar;
    parametro0[2][0] *= escalar;
    parametro0[0][1] *= escalar;
    parametro0[1][1] *= escalar;
    parametro0[2][1] *= escalar;
    parametro0[0][2] *= escalar;
    parametro0[1][2] *= escalar;
    parametro0[2][2] *= escalar;
}

SIN_USO void fallido_fijo_punto_matriz_conversion(Mtx* dest, Mat4 orig_) {
    f32 a_fijo = 65536.0f;
    dest->m[0][0] = orig_[0][0] * a_fijo;
    dest->m[0][1] = orig_[0][1] * a_fijo;
    dest->m[0][2] = orig_[0][2] * a_fijo;
    dest->m[0][3] = orig_[0][3] * a_fijo;
    dest->m[1][0] = orig_[1][0] * a_fijo;
    dest->m[1][1] = orig_[1][1] * a_fijo;
    dest->m[1][2] = orig_[1][2] * a_fijo;
    dest->m[1][3] = orig_[1][3] * a_fijo;
    dest->m[2][0] = orig_[2][0] * a_fijo;
    dest->m[2][1] = orig_[2][1] * a_fijo;
    dest->m[2][2] = orig_[2][2] * a_fijo;
    dest->m[2][3] = orig_[2][3] * a_fijo;
    dest->m[3][0] = orig_[3][0] * a_fijo;
    dest->m[3][1] = orig_[3][1] * a_fijo;
    dest->m[3][2] = orig_[3][2] * a_fijo;
    dest->m[3][3] = orig_[3][3] * a_fijo;
}

void convertir_a_matriz_punto_fijo(Mtx* dest, Mat4 orig_) {
#ifdef AVOID_UB
    guMtxF2L(orig_, dest);
#else
    f32 a_fijo = 65536.0f;
    dest->m[0][0] = ((s32) (orig_[0][0] * a_fijo) & 0xFFFF0000) | (((s32) (orig_[0][1] * a_fijo) >> 0x10) & 0xFFFF);
    dest->m[0][1] = ((s32) (orig_[0][2] * a_fijo) & 0xFFFF0000) | (((s32) (orig_[0][3] * a_fijo) >> 0x10) & 0xFFFF);
    dest->m[0][2] = ((s32) (orig_[1][0] * a_fijo) & 0xFFFF0000) | (((s32) (orig_[1][1] * a_fijo) >> 0x10) & 0xFFFF);
    dest->m[0][3] = ((s32) (orig_[1][2] * a_fijo) & 0xFFFF0000) | (((s32) (orig_[1][3] * a_fijo) >> 0x10) & 0xFFFF);
    dest->m[1][0] = ((s32) (orig_[2][0] * a_fijo) & 0xFFFF0000) | (((s32) (orig_[2][1] * a_fijo) >> 0x10) & 0xFFFF);
    dest->m[1][1] = ((s32) (orig_[2][2] * a_fijo) & 0xFFFF0000) | (((s32) (orig_[2][3] * a_fijo) >> 0x10) & 0xFFFF);
    dest->m[1][2] = ((s32) (orig_[3][0] * a_fijo) & 0xFFFF0000) | (((s32) (orig_[3][1] * a_fijo) >> 0x10) & 0xFFFF);
    dest->m[1][3] = ((s32) (orig_[3][2] * a_fijo) & 0xFFFF0000) | (((s32) (orig_[3][3] * a_fijo) >> 0x10) & 0xFFFF);
    dest->m[2][0] = ((s32) (orig_[0][0] * a_fijo) << 0x10) | ((s32) (orig_[0][1] * a_fijo) & 0xFFFF);
    dest->m[2][1] = ((s32) (orig_[0][2] * a_fijo) << 0x10) | ((s32) (orig_[0][3] * a_fijo) & 0xFFFF);
    dest->m[2][2] = ((s32) (orig_[1][0] * a_fijo) << 0x10) | ((s32) (orig_[1][1] * a_fijo) & 0xFFFF);
    dest->m[2][3] = ((s32) (orig_[1][2] * a_fijo) << 0x10) | ((s32) (orig_[1][3] * a_fijo) & 0xFFFF);
    dest->m[3][0] = ((s32) (orig_[2][0] * a_fijo) << 0x10) | ((s32) (orig_[2][1] * a_fijo) & 0xFFFF);
    dest->m[3][1] = ((s32) (orig_[2][2] * a_fijo) << 0x10) | ((s32) (orig_[2][3] * a_fijo) & 0xFFFF);
    dest->m[3][2] = ((s32) (orig_[3][0] * a_fijo) << 0x10) | ((s32) (orig_[3][1] * a_fijo) & 0xFFFF);
    dest->m[3][3] = ((s32) (orig_[3][2] * a_fijo) << 0x10) | ((s32) (orig_[3][3] * a_fijo) & 0xFFFF);
#endif
}

bool ajustar_angulo(s16* angulo, s16 angulo_objetivo, s16 paso) {
    s16 temporal_v0;

    temporal_v0 = angulo_objetivo - *angulo;
    if (paso < 0) {
        paso *= -1;
    }

    if (temporal_v0 > 0) {
        temporal_v0 -= paso;
        if (temporal_v0 >= 0) {
            *angulo = angulo_objetivo - temporal_v0;
        } else {
            *angulo = angulo_objetivo;
        }
    } else {
        temporal_v0 += paso;
        if (temporal_v0 <= 0) {
            *angulo = angulo_objetivo - temporal_v0;
        } else {
            *angulo = angulo_objetivo;
        }
    }
    if (angulo_objetivo == *angulo) {
        return false;
    }
    return true;
}

void mover_s32_hacia(s32* valor_inicial, s32 valor_objetivo, f32 algun_porciento) {
    *valor_inicial -= ((*valor_inicial - valor_objetivo) * algun_porciento);
}

void mover_f32_hacia(f32* valor_inicial, f32 valor_objetivo, f32 algun_porciento) {
    *valor_inicial -= ((*valor_inicial - valor_objetivo) * algun_porciento);
#ifdef TARGET_PS2
    if ((*valor_inicial < 0.001f) && (-0.001f < *valor_inicial)) {
#else
    if ((*valor_inicial < 0.001) && (-0.001 < *valor_inicial)) {
#endif
        *valor_inicial = 0.0f;
    }
}

void mover_s16_hacia(s16* valor_inicial, s16 valor_objetivo, f32 algun_porciento) {
    *valor_inicial -= ((*valor_inicial - valor_objetivo) * algun_porciento);
}

void mover_u16_hacia(u16* valor_inicial, s16 valor_objetivo, f32 algun_porciento) {
    *valor_inicial -= ((*valor_inicial - valor_objetivo) * algun_porciento);
}

void funcion_80022744(void) {
    funcion_8006E058();
    funcion_8002276C();
}

void funcion_8002276C(void) {
    switch (modo_pantalla_activo) { /* irregular */
        case MODO_PANTALLA_1P:
            switch (seleccion_modo) {
                case GRAN_PREMIO:
                    funcion_80022A98(jugador_uno, 0);
                    funcion_80022A98(jugador_dos, 1);
                    funcion_80022A98(jugador_tres, 2);
                    funcion_80022A98(jugador_cuatro, 3);
                    funcion_80022A98(jugador_cinco, 4);
                    funcion_80022A98(jugador_seis, 5);
                    funcion_80022A98(jugador_siete, 6);
                    funcion_80022A98(jugador_ocho, 7);
                    break;
                case CONTRARRELOJ:
                    funcion_80022A98(jugador_uno, 0);
                    if ((jugador_dos->type & INVISIBLE_JUGADOR_O_BOMBA) == INVISIBLE_JUGADOR_O_BOMBA) {
                        funcion_80022A98(jugador_dos, 1);
                    }
                    if ((jugador_tres->type & INVISIBLE_JUGADOR_O_BOMBA) == INVISIBLE_JUGADOR_O_BOMBA) {
                        funcion_80022A98(jugador_tres, 2);
                    }
                    break;
                case VERSUS:
                case BATALLA:
                    funcion_80022A98(jugador_uno, 0);
                    funcion_80022A98(jugador_dos, 1);
                    if (seleccion_cantidad_jugador_1 >= 3) {
                        funcion_80022A98(jugador_tres, 2);
                    }
                    if (seleccion_cantidad_jugador_1 == 4) {
                        funcion_80022A98(jugador_cuatro, 3);
                    }
                    break;
            }
            break;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            switch (seleccion_modo) {
                case GRAN_PREMIO:
                    funcion_80022A98(jugador_uno, 0);
                    funcion_80022A98(jugador_dos, 1);
                    funcion_80022A98(jugador_tres, 2);
                    funcion_80022A98(jugador_cuatro, 3);
                    funcion_80022A98(jugador_cinco, 4);
                    funcion_80022A98(jugador_seis, 5);
                    funcion_80022A98(jugador_siete, 6);
                    funcion_80022A98(jugador_ocho, 7);
                    break;
                case VERSUS:
                case BATALLA:
                    funcion_80022A98(jugador_uno, 0);
                    funcion_80022A98(jugador_dos, 1);
                    break;
                case CONTRARRELOJ:
                    funcion_80022A98(jugador_uno, 0);
                    break;
            }
            break;
        case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
            if ((VERSUS == seleccion_modo) || (BATALLA == seleccion_modo)) {
                funcion_80022A98(jugador_uno, 0);
                funcion_80022A98(jugador_dos, 1);
                funcion_80022A98(jugador_tres, 2);
                if (seleccion_cantidad_jugador_1 == 4) {
                    funcion_80022A98(jugador_cuatro, 3);
                }
            }
            break;
    }
}
