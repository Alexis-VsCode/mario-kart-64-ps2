// Cargar texturas

void funcion_800431B0(Vec3f pos, Vec3su orientacion, f32 escalar, Vtx* vtx) {
    fijar_transformacion_matriz_rsp(pos, orientacion, escalar);
    gSPVertex(display_list_cabeza++, vtx, 4, 0);
    gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
}

void funcion_80043220(Vec3f pos, Vec3su orientacion, f32 escalar, Gfx* gfx) {
    fijar_transformacion_matriz_rsp(pos, orientacion, escalar);
    gSPDisplayList(display_list_cabeza++, dato_0D0077A0);
    gSPDisplayList(display_list_cabeza++, gfx);
}

SIN_USO void funcion_80043288(Vec3f pos, Vec3su orientacion, f32 parametro2, Gfx* gfx) {
    fijar_transformacion_matriz_rsp(pos, orientacion, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D0077A0);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BOTH);
    gSPDisplayList(display_list_cabeza++, gfx);
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
}

void funcion_80043328(Vec3f parametro0, Vec3su parametro1, f32 parametro2, Gfx* gfx) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D0077D0);
    gSPDisplayList(display_list_cabeza++, gfx);
}

SIN_USO void funcion_80043390(Vec3f parametro0, Vec3su parametro1, f32 parametro2, Gfx* gfx) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D0077F8);
    gSPDisplayList(display_list_cabeza++, gfx);
}

SIN_USO void funcion_800433F8(Vec3f parametro0, Vec3su parametro1, f32 parametro2, Gfx* gfx) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007828);
    gSPDisplayList(display_list_cabeza++, gfx);
}

SIN_USO void funcion_80043460(Vec3f parametro0, Vec3su parametro1, f32 parametro2, Gfx* gfx) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007828);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BOTH);
    gSPDisplayList(display_list_cabeza++, gfx);
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
}

void funcion_80043500(Vec3f parametro0, Vec3su parametro1, f32 parametro2, Gfx* gfx) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007850);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BOTH);
    gSPDisplayList(display_list_cabeza++, gfx);
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
}

void funcion_800435A0(Vec3f parametro0, Vec3su parametro1, f32 parametro2, Gfx* gfx, s32 parametro4) {
    fijar_matriz_transformacion_invertido_x_y_orientacion_rsp(parametro0, parametro1, parametro2);

    gSPDisplayList(display_list_cabeza++, dato_0D007878);
    gDPSetPrimColor(display_list_cabeza++, 0, 0, 0xFF, 0xFF, 0xFF, parametro4);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BOTH);
    gSPDisplayList(display_list_cabeza++, gfx);
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
}

SIN_USO void funcion_80043668(Vec3f parametro0, Vec3su parametro1, f32 parametro2, Gfx* gfx) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D0078A0);
    gSPDisplayList(display_list_cabeza++, gfx);
}

SIN_USO void funcion_800436D0(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, Vtx* vtx) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D0078A0);
    gSPVertex(display_list_cabeza++, vtx, 3, 0);
    gSPDisplayList(display_list_cabeza++, dato_0D006930);
}

SIN_USO void funcion_80043764(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, Vtx* vtx) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D0078A0);
    gSPVertex(display_list_cabeza++, vtx, 4, 0);
    gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
}

SIN_USO void funcion_800437F8(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, Vtx* vtx, s32 parametro5) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D0078A0);

    gDPSetRenderMode(display_list_cabeza++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
    vtx[0].v.cn[3] = parametro5;
    vtx[1].v.cn[3] = parametro5;
    vtx[2].v.cn[3] = parametro5;
    vtx[3].v.cn[3] = parametro5;
    gSPVertex(display_list_cabeza++, vtx, 4, 0);
    gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
}

SIN_USO void funcion_800438C4(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, Vtx* vtx, s32 parametro5) {
    vtx[1].v.ob[0] = parametro5;
    vtx[2].v.ob[0] = parametro5;
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D0078A0);
    gDPSetRenderMode(display_list_cabeza++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
    gSPVertex(display_list_cabeza++, vtx, 4, 0);
    gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
}

SIN_USO void funcion_8004398C(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, Vtx* vtx, s32 parametro5) {
    vtx[0].v.ob[0] = parametro5;
    vtx[3].v.ob[0] = parametro5;
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D0078A0);
    gDPSetRenderMode(display_list_cabeza++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
    gSPVertex(display_list_cabeza++, vtx, 4, 0);
    gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
}

s32 funcion_80043A54(s32 parametro0) {
    s32 temporal_a1;
    s32 phi_v0;
    s32 phi_v1 = 0;

    phi_v0 = parametro0;
    do {
        phi_v1++;
        temporal_a1 = phi_v0 / 2;
        phi_v0 = temporal_a1;
    } while (temporal_a1 != 1);
    return phi_v1;
}

void cargar_textura_bloque_rgba32_nomirror(u8* textura, s32 ancho, s32 altura) {
    gDPLoadTextureBlock(display_list_cabeza++, textura, G_IM_FMT_RGBA, G_IM_SIZ_32b, ancho, altura, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
}

void cargar_textura_tile_rgba32_nomirror(u8* textura, s32 ancho, s32 altura) {
    gDPLoadTextureTile(display_list_cabeza++, textura, G_IM_FMT_RGBA, G_IM_SIZ_32b, ancho, altura, 0, 0, ancho - 1,
                       altura - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                       G_TX_NOLOD, G_TX_NOLOD);
}

void cargar_textura_bloque_rgba16_espejo(u8* textura, s32 ancho, s32 altura) {
    gDPLoadTextureBlock(display_list_cabeza++, textura, G_IM_FMT_RGBA, G_IM_SIZ_16b, ancho, altura, 0,
                        G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
}

void cargar_textura_bloque_rgba16_nomirror(u8* textura, s32 ancho, s32 altura, s32 algun_mascara) {
    gDPLoadTextureBlock(display_list_cabeza++, textura, G_IM_FMT_RGBA, G_IM_SIZ_16b, ancho, altura, 0,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_CLAMP, algun_mascara, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
}

void cargar_textura_tile_rgba16_nomirror(u8* textura, s32 ancho, s32 altura) {
    gDPLoadTextureTile(display_list_cabeza++, textura, G_IM_FMT_RGBA, G_IM_SIZ_16b, ancho, altura, 0, 0, ancho - 1,
                       altura - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                       G_TX_NOLOD, G_TX_NOLOD);
}

void cargar_nomirror_bloque_ia16_textura(u8* textura, s32 ancho, s32 altura) {
    gDPLoadTextureBlock(display_list_cabeza++, textura, G_IM_FMT_IA, G_IM_SIZ_16b, ancho, altura, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
}

void cargar_nomirror_tile_ia16_textura(u8* textura, s32 ancho, s32 altura) {
    gDPLoadTextureTile(display_list_cabeza++, textura, G_IM_FMT_IA, G_IM_SIZ_16b, ancho, altura, 0, 0, ancho - 1,
                       altura - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                       G_TX_NOLOD, G_TX_NOLOD);
}

void cargar_nomirror_bloque_ia8_textura(u8* textura, s32 ancho, s32 altura) {
    gDPLoadTextureBlock(display_list_cabeza++, textura, G_IM_FMT_IA, G_IM_SIZ_8b, ancho, altura, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
}

void cargar_nomirror_tile_ia8_textura(u8* textura, s32 ancho, s32 altura) {
    gDPLoadTextureTile(display_list_cabeza++, textura, G_IM_FMT_IA, G_IM_SIZ_8b, ancho, altura, 0, 0, ancho - 1,
                       altura - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                       G_TX_NOLOD, G_TX_NOLOD);
}

void cargar_nomirror_bloque_i8_textura(u8* textura, s32 ancho, s32 altura) {
    gDPLoadTextureBlock(display_list_cabeza++, textura, G_IM_FMT_I, G_IM_SIZ_8b, ancho, altura, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
}

void funcion_80044924(u8* textura, s32 ancho, s32 altura) {

    gDPSetTextureImage(display_list_cabeza++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, textura);
    gDPSetTile(display_list_cabeza++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, G_TX_RENDERTILE, G_TX_LOADTILE, 0,
               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
               G_TX_NOLOD);
    gDPLoadSync(display_list_cabeza++);
    gDPLoadBlock(display_list_cabeza++, G_TX_LOADTILE, 0, 0, (((ancho * altura) + 3) >> 2) - 1,
                 ((ancho / 16) + 2047) / (ancho / 16));
    gDPPipeSync(display_list_cabeza++);
    gDPSetTile(display_list_cabeza++, G_IM_FMT_IA, G_IM_SIZ_4b, (((ancho >> 1) + 7) >> 3), G_TX_RENDERTILE,
               G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP,
               G_TX_NOMASK, G_TX_NOLOD);
    gDPSetTileSize(display_list_cabeza++, G_TX_RENDERTILE, 0, 0, (ancho - 1) << G_TEXTURE_IMAGE_FRAC,
                   (altura - 1) << G_TEXTURE_IMAGE_FRAC);
}

SIN_USO void funcion_80044AB8(u8* textura, s32 ancho, s32 altura) {
    gDPLoadTextureTile_4b(display_list_cabeza++, textura, G_IM_FMT_IA, ancho, altura, 0, 0, ancho - 1, altura - 1, 0,
                          G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                          G_TX_NOLOD);
}

void funcion_80044BF8(u8* textura, s32 ancho, s32 altura) {
    gDPLoadTextureBlock(display_list_cabeza++, textura, G_IM_FMT_I, G_IM_SIZ_8b, ancho, altura, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
}

void funcion_80044DA0(u8* image, s32 ancho, s32 altura) {

    gDPSetTextureImage(display_list_cabeza++, G_IM_FMT_I, G_IM_SIZ_16b, 1, image);
    gDPSetTile(display_list_cabeza++, G_IM_FMT_I, G_IM_SIZ_16b, 0, G_TX_RENDERTILE, G_TX_LOADTILE, 0,
               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
               G_TX_NOLOD);
    gDPLoadSync(display_list_cabeza++);
    gDPLoadBlock(display_list_cabeza++, G_TX_LOADTILE, 0, 0, (((ancho * altura) + 3) >> 2) - 1,
                 ((ancho / 16) + 2047) / (ancho / 16));
    gDPPipeSync(display_list_cabeza++);
    gDPSetTile(display_list_cabeza++, G_IM_FMT_I, G_IM_SIZ_4b, (((ancho >> 1) + 7) >> 3), G_TX_RENDERTILE, G_TX_RENDERTILE,
               0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
               G_TX_NOLOD);
    gDPSetTileSize(display_list_cabeza++, G_TX_RENDERTILE, 0, 0, (ancho - 1) << G_TEXTURE_IMAGE_FRAC,
                   (altura - 1) << G_TEXTURE_IMAGE_FRAC);
}

void funcion_80044F34(u8* image, s32 ancho, s32 altura) {

    gDPSetTextureImage(display_list_cabeza++, G_IM_FMT_I, G_IM_SIZ_16b, 1, image);
    gDPSetTile(display_list_cabeza++, G_IM_FMT_I, G_IM_SIZ_16b, 0, G_TX_RENDERTILE, G_TX_LOADTILE, 0,
               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
               G_TX_NOLOD);
    gDPLoadSync(display_list_cabeza++);
    gDPLoadBlock(display_list_cabeza++, G_TX_LOADTILE, 0, 0, (((ancho * altura) + 3) >> 2) - 1,
                 ((ancho / 16) + 2047) / (ancho / 16));
    gDPPipeSync(display_list_cabeza++);
    gDPSetTile(display_list_cabeza++, G_IM_FMT_I, G_IM_SIZ_4b, (((ancho >> 1) + 7) >> 3), G_TX_RENDERTILE, G_TX_RENDERTILE,
               0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
               G_TX_NOLOD);
    gDPSetTileSize(display_list_cabeza++, G_TX_RENDERTILE, 0, 0, (ancho - 1) << G_TEXTURE_IMAGE_FRAC,
                   (altura - 1) << G_TEXTURE_IMAGE_FRAC);
}

void funcion_800450C8(u8* image, s32 ancho, s32 altura) {
    s32 mascaras = funcion_80043A54(ancho);

    gDPSetTextureImage(display_list_cabeza++, G_IM_FMT_I, G_IM_SIZ_16b, 1, image);
    gDPSetTile(display_list_cabeza++, G_IM_FMT_I, G_IM_SIZ_16b, 0, G_TX_RENDERTILE, G_TX_LOADTILE, 0,
               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, mascaras, G_TX_NOLOD);
    gDPLoadSync(display_list_cabeza++);
    gDPLoadBlock(display_list_cabeza++, G_TX_LOADTILE, 0, 0, (((ancho * altura) + 3) >> 2) - 1,
                 ((ancho / 16) + 2047) / (ancho / 16));
    gDPPipeSync(display_list_cabeza++);
    gDPSetTile(display_list_cabeza++, G_IM_FMT_I, G_IM_SIZ_4b, (((ancho >> 1) + 7) >> 3), G_TX_RENDERTILE, G_TX_RENDERTILE,
               0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, mascaras, G_TX_NOLOD);
    gDPSetTileSize(display_list_cabeza++, G_TX_RENDERTILE, 0, 0, (ancho - 1) << G_TEXTURE_IMAGE_FRAC,
                   (altura - 1) << G_TEXTURE_IMAGE_FRAC);
}

void cargar_textura_rsp(u8* textura, s32 ancho, s32 altura) {
    gDPLoadTextureBlock(display_list_cabeza++, textura, G_IM_FMT_CI, G_IM_SIZ_8b, ancho, altura, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
}

void cargar_mascara_textura_rsp(u8* textura, s32 ancho, s32 altura, s32 algun_mascara) {
    gDPLoadTextureBlock(display_list_cabeza++, textura, G_IM_FMT_CI, G_IM_SIZ_8b, ancho, altura, 0,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_CLAMP, algun_mascara, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
}

SIN_USO void funcion_80045614(u8* textura, s32 ancho, s32 altura) {
    gDPLoadTextureTile(display_list_cabeza++, textura, G_IM_FMT_CI, G_IM_SIZ_8b, ancho, altura, 0, 0, ancho - 1,
                       altura - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                       G_TX_NOLOD, G_TX_NOLOD);
}

SIN_USO void funcion_80045738(u8* imagen1, u8* imagen2, s32 ancho, s32 altura) {
    gDPSetCombineLERP(display_list_cabeza++, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

    gDPLoadMultiBlock(display_list_cabeza++, imagen2, 0x100, G_TX_RENDERTILE, G_IM_FMT_I, G_IM_SIZ_8b, ancho, altura, 0,
                      G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                      G_TX_NOLOD);
    gDPLoadTextureBlock(display_list_cabeza++, imagen1, G_IM_FMT_RGBA, G_IM_SIZ_16b, ancho, altura, 0,
                        G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    gDPSetTile(display_list_cabeza++, G_IM_FMT_I, G_IM_SIZ_8b, (ancho + 7) >> 3, 0x0100, 1, 0, G_TX_NOMIRROR | G_TX_WRAP,
               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
    ;
    gDPSetTileSize(display_list_cabeza++, 1, 0, 0, (ancho - 1) << G_TEXTURE_IMAGE_FRAC,
                   (altura - 1) << G_TEXTURE_IMAGE_FRAC);
}

void funcion_80045B2C(Vtx* parametro0) {
    gSPVertex(display_list_cabeza++, parametro0, 4, 0);
    gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
}

void funcion_80045B74(Vtx* parametro0) {
    gSPVertex(display_list_cabeza++, parametro0, 3, 0);
    gSPDisplayList(display_list_cabeza++, dato_0D006930);
}

SIN_USO void funcion_80045BBC(Vec3f parametro0, Vec3su parametro1, f32 parametro2, Vtx* parametro3) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D0078A0);
    gSPVertex(display_list_cabeza++, parametro3, 4, 0);
    gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
}

SIN_USO void funcion_80045C48(Vec3f parametro0, Vec3su parametro1, f32 parametro2, Vtx* parametro3) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D0078D0);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BOTH);
    gSPVertex(display_list_cabeza++, parametro3, 4, 0);
    gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
}

void funcion_80045D0C(u8* textura, Vtx* parametro1, s32 ancho, s32 parametro3, s32 altura) {
    s32 indice_altura;
    s32 indice_vertice = 0;
    u8* img = textura;

    for (indice_altura = 0; indice_altura < parametro3 / altura; indice_altura++) {
        cargar_textura_bloque_rgba16_espejo(img, ancho, altura);
        funcion_80045B2C(&parametro1[indice_vertice]);
        img += ancho * altura * 2;
        indice_vertice += 4;
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_80045E10(u8* textura, Vtx* parametro1, s32 ancho, s32 parametro3, s32 altura) {
    s32 indice_altura;
    s32 indice_vertice = 0;
    u8* img = textura;

    for (indice_altura = 0; indice_altura < parametro3 / altura; indice_altura++) {
        cargar_textura_bloque_rgba16_espejo(img, ancho, altura);
        funcion_80045B2C(&parametro1[indice_vertice]);
        img += ancho * (altura - 1) * 2;
        indice_vertice += 4;
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_80045F18(u8* textura, Vtx* parametro1, s32 ancho, s32 parametro3, s32 altura, s32 algun_mascara) {
    s32 indice_altura;
    s32 indice_vertice = 0;
    u8* img = textura;

    for (indice_altura = 0; indice_altura < parametro3 / altura; indice_altura++) {
        cargar_textura_bloque_rgba16_nomirror(img, ancho, altura, algun_mascara);
        funcion_80045B2C(&parametro1[indice_vertice]);
        img += ancho * (altura - 1) * 2;
        indice_vertice += 4;
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

SIN_USO void funcion_80046030(u8* tlut, u8* textura, Vtx* parametro2, s32 ancho, s32 parametro4, s32 altura) {
    s32 variable_s0 = 0;
    u8* img1 = tlut;
    u8* img2 = textura;
    s32 temporal_lo_2;
    s32 variable_;
    s32 i;

    gSPDisplayList(display_list_cabeza++, dato_0D008138);

    for (i = 0; i < parametro4 / altura; i++) {
        funcion_80045738(img1, img2, ancho, altura);
        funcion_80045B2C(&parametro2[variable_s0]);
        variable_ = altura - 1;
        temporal_lo_2 = (ancho * variable_);
        img1 += temporal_lo_2 * 2;
        img2 += temporal_lo_2;
        variable_s0 += 4;
    }
    gSPTexture(display_list_cabeza++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
    gSPDisplayList(display_list_cabeza++, dato_0D008120);
}

void funcion_800461A4(u8* textura, Vtx* parametro1, s32 ancho, s32 parametro3, s32 altura) {
    s32 indice_altura;
    s32 indice_vertice = 0;
    u8* img = textura;

    for (indice_altura = 0; indice_altura < parametro3 / altura; indice_altura++) {
        cargar_textura_bloque_rgba32_nomirror(img, ancho, altura);
        funcion_80045B2C(&parametro1[indice_vertice]);
        img += ancho * altura * 4;
        indice_vertice += 4;
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_800462A8(u8* textura, Vtx* parametro1, s32 ancho, s32 parametro3, s32 altura) {
    s32 indice_altura;
    s32 indice_vertice = 0;
    u8* img = textura;

    for (indice_altura = 0; indice_altura < parametro3 / altura; indice_altura++) {
        cargar_textura_bloque_rgba32_nomirror(img, ancho, altura);
        funcion_80045B2C(&parametro1[indice_vertice]);
        img += ancho * (altura - 1) * 4;
        indice_vertice += 4;
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_800463B0(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7, SIN_USO s32 parametro8,
                   s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007928);
    funcion_80045D0C(textura, parametro5, parametro6, parametro7, parametro9);
}

void funcion_80046424(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7, SIN_USO s32 parametro8,
                   s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007968);
    funcion_8004B614(dato_801656C0, dato_801656D0, dato_801656E0, 128, 128, 128, 255);
    funcion_80045D0C(textura, parametro5, parametro6, parametro7, parametro9);
}

SIN_USO void funcion_800464D0(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7,
                          SIN_USO s32 parametro8, s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007948);
    funcion_80045E10(textura, parametro5, parametro6, parametro7, parametro9);
}

SIN_USO void funcion_80046544(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7,
                          SIN_USO s32 parametro8, s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D0079A8);
    funcion_80045E10(textura, parametro5, parametro6, parametro7, parametro9);
}

void funcion_800465B8(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, s32 parametro4, u8* textura, Vtx* parametro6, s32 parametro7, s32 parametro8,
                   SIN_USO s32 parametro9, s32 parametro_a) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D0079E8);

    fijar_transparencia(parametro4);
    funcion_80045E10(textura, parametro6, parametro7, parametro8, parametro_a);
}

SIN_USO void funcion_80046634(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6, s32 parametro7, s32 parametro8,
                          SIN_USO s32 parametro9, s32 parametro_a) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007948);
    funcion_80046030(tlut, textura, parametro6, parametro7, parametro8, parametro_a);
}

void funcion_800466B0(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007948);
    cargar_textura_bloque_rgba16_espejo(textura, parametro6, parametro7);
    funcion_80045B74(parametro5);
}

SIN_USO void funcion_80046720(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7,
                          SIN_USO s32 parametro8, s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007928);
    funcion_800461A4(textura, parametro5, parametro6, parametro7, parametro9);
}

SIN_USO void funcion_80046794(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7,
                          SIN_USO s32 parametro8, s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007948);
    funcion_800462A8(textura, parametro5, parametro6, parametro7, parametro9);
}

void funcion_80046808(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* textura, Vtx* parametro4, s32 parametro5, s32 parametro6, SIN_USO s32 parametro7,
                   s32 parametro8) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007948);
    funcion_80045E10(textura, parametro4, parametro5, parametro6, parametro8);
}

SIN_USO void funcion_80046874(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* textura, Vtx* parametro4, s32 parametro5, s32 parametro6,
                          SIN_USO s32 parametro7, s32 parametro8) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D0079C8);
    funcion_80045E10(textura, parametro4, parametro5, parametro6, parametro8);
}

void funcion_800468E0(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* textura, Vtx* parametro4, s32 parametro5, s32 parametro6, SIN_USO s32 parametro7,
                   s32 parametro8, s32 parametro9) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D0079C8);
    funcion_80045F18(textura, parametro4, parametro5, parametro6, parametro8, parametro9);
}

SIN_USO void funcion_80046954(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* textura, Vtx* parametro4, s32 parametro5, s32 parametro6,
                          SIN_USO s32 parametro7, s32 parametro8) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D0079C8);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BOTH);
    funcion_80045E10(textura, parametro4, parametro5, parametro6, parametro8);
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
}

void funcion_80046A00(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* textura, Vtx* parametro4, s32 parametro5, s32 parametro6) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007948);
    cargar_textura_bloque_rgba16_espejo(textura, parametro5, parametro6);
    funcion_80045B74(parametro4);
}

SIN_USO void funcion_80046A68(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* textura, Vtx* parametro4, s32 parametro5, s32 parametro6,
                          SIN_USO s32 parametro7, s32 parametro8) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D0079C8);
    funcion_800462A8(textura, parametro4, parametro5, parametro6, parametro8);
}

SIN_USO void funcion_80046AD4(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura) {
    funcion_800464D0(parametro0, parametro1, parametro2, parametro3, textura, comun_vtx_jugador_minimapa_icono, 8, 8, 8, 8);
}

SIN_USO void funcion_80046B38(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura) {
    funcion_800464D0(parametro0, parametro1, parametro2, parametro3, textura, rectangulo_vtx_comun, 16, 16, 16, 16);
}

SIN_USO void funcion_80046B9C(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* textura) {
    funcion_80046808(parametro0, parametro1, parametro2, textura, rectangulo_vtx_comun, 16, 16, 16, 16);
}

SIN_USO void funcion_80046BEC(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5) {
    funcion_800466B0(parametro0, parametro1, parametro2, parametro3, textura, parametro5, 16, 16);
}

SIN_USO void funcion_80046C3C(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* textura, Vtx* parametro4) {
    funcion_80046A00(parametro0, parametro1, parametro2, textura, parametro4, 16, 16);
}

SIN_USO void funcion_80046C78(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura) {
    funcion_800464D0(parametro0, parametro1, parametro2, parametro3, textura, dato_0D005AE0, 32, 32, 32, 32);
}

SIN_USO void funcion_80046CDC(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura) {
    funcion_800464D0(parametro0, parametro1, parametro2, parametro3, textura, dato_0D005FB0, 64, 32, 64, 32);
}

SIN_USO void funcion_80046D40(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* textura) {
    funcion_80046808(parametro0, parametro1, parametro2, textura, dato_0D005FB0, 64, 32, 64, 32);
}

SIN_USO void funcion_80046D90(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura) {
    funcion_800464D0(parametro0, parametro1, parametro2, parametro3, textura, erizo_vtx_comun, 64, 64, 64, 32);
}

SIN_USO void funcion_80046DF4(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, s32 parametro4, u8* textura) {
    funcion_800465B8(parametro0, parametro1, parametro2, parametro3, parametro4, textura, erizo_vtx_comun, 64, 64, 64, 32);
}

void cargar_textura_y_tlut(u8* tlut, u8* textura, s32 ancho, s32 altura) {
    gSPDisplayList(display_list_cabeza++, dato_0D007D78);
    gDPLoadTLUT_pal256(display_list_cabeza++, tlut);
    cargar_textura_rsp(textura, ancho, altura);
}

void funcion_80046F60(u8* tlut, u8* parametro1, s32 parametro2, s32 parametro3, s32 parametro4) {
    gSPDisplayList(display_list_cabeza++, dato_0D007D78);
    gDPLoadTLUT_pal256(display_list_cabeza++, tlut);
    cargar_mascara_textura_rsp(parametro1, parametro2, parametro3, parametro4);
}

void funcion_80047068(u8* tlut, u8* textura, Vtx* parametro2, SIN_USO s32 parametro3, s32 parametro4, s32 ancho, s32 altura) {
    s32 indice_altura;
    s32 indice_vertice = 0;
    u8* img = textura;

    gDPLoadTLUT_pal256(display_list_cabeza++, tlut);
    for (indice_altura = 0; indice_altura < parametro4 / altura; indice_altura++) {
        cargar_textura_rsp(img, ancho, altura);
        gSPVertex(display_list_cabeza++, &parametro2[indice_vertice], 4, 0);
        gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
        img += ancho * altura;
        indice_vertice += 4;
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void dibujar_superponer_textura_rectangulo(u8* tlut, u8* textura, Vtx* parametro2, SIN_USO s32 parametro3, s32 parametro4, s32 ancho,
                                    s32 altura) {
    s32 indice_altura;
    s32 indice_vertice = 0;
    u8* img = textura;

    gDPLoadTLUT_pal256(display_list_cabeza++, tlut);
    for (indice_altura = 0; indice_altura < parametro4 / altura; indice_altura++) {
        cargar_textura_rsp(img, ancho, altura);
        gSPVertex(display_list_cabeza++, &parametro2[indice_vertice], 4, 0);
        gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
        img += ancho * (altura - 1);
        indice_vertice += 4;
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_8004747C(u8* tlut, u8* textura, Vtx* parametro2, SIN_USO s32 parametro3, s32 parametro4, s32 ancho, s32 altura, s32 algun_mascara) {
    s32 indice_altura;
    s32 indice_vertice = 0;
    u8* img = textura;

    gDPLoadTLUT_pal256(display_list_cabeza++, tlut);
    for (indice_altura = 0; indice_altura < parametro4 / altura; indice_altura++) {
        cargar_mascara_textura_rsp(img, ancho, altura, algun_mascara);
        gSPVertex(display_list_cabeza++, &parametro2[indice_vertice], 4, 0);
        gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
        img += ancho * (altura - 1);
        indice_vertice += 4;
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_8004768C(u8* tlut, u8* textura, Vtx* parametro2, s32 parametro3, s32 ancho, s32 altura) {
    s32 indice_altura;
    s32 indice_vertice = 0;
    u8* img = textura;

    gDPLoadTLUT_pal256(display_list_cabeza++, tlut);
    for (indice_altura = 0; indice_altura < parametro3 / altura; indice_altura++) {
        cargar_textura_rsp(img, altura, ancho);
        gSPVertex(display_list_cabeza++, &parametro2[indice_vertice], 4, 0);
        gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
        img += altura * ancho;
        indice_vertice += 4;
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_8004788C(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9, s32 parametro_a) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007CB8);
    funcion_80047068(tlut, textura, parametro6, parametro7, parametro8, parametro9, parametro_a);
}

void funcion_80047910(s32 x, s32 y, u16 angulo, f32 size, u8* tlut, u8* textura, Vtx* parametro6, s32 parametro7, s32 parametro8, s32 parametro9,
                   s32 parametro_a) {
    funcion_80042330(x, y, angulo, size);
    gSPDisplayList(display_list_cabeza++, dato_0D007CD8);
    dibujar_superponer_textura_rectangulo(tlut, textura, parametro6, parametro7, parametro8, parametro9, parametro_a);
}

void funcion_80047994(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9, s32 parametro_a) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007CF8);
    dibujar_superponer_textura_rectangulo(tlut, textura, parametro6, parametro7, parametro8, parametro9, parametro_a);
}

void funcion_80047A18(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9, s32 parametro_a) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007D18);
    funcion_80047068(tlut, textura, parametro6, parametro7, parametro8, parametro9, parametro_a);
}

void funcion_80047A9C(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9, s32 parametro_a) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007D38);
    dibujar_superponer_textura_rectangulo(tlut, textura, parametro6, parametro7, parametro8, parametro9, parametro_a);
}

SIN_USO void funcion_80047B20(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6, s32 parametro7, s32 parametro8,
                          s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007D38);
    funcion_8004768C(tlut, textura, parametro6, parametro7, parametro8, parametro9);
}

void funcion_80047B9C(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, s32 parametro4, u8* tlut, u8* textura, Vtx* parametro7, s32 parametro8,
                   s32 parametro9, s32 parametro_a, s32 parametro_b) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007DB8);
    fijar_transparencia(parametro4);
    funcion_80047068(tlut, textura, parametro7, parametro8, parametro9, parametro_a, parametro_b);
}

SIN_USO void funcion_80047C28(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, s32 parametro4, u8* tlut, u8* textura, Vtx* parametro7, s32 parametro8,
                          s32 parametro9, s32 parametro_a, s32 parametro_b) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007DD8);
    fijar_transparencia(parametro4);
    dibujar_superponer_textura_rectangulo(tlut, textura, parametro7, parametro8, parametro9, parametro_a, parametro_b);
}

void funcion_80047CB4(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, s32 parametro4, u8* tlut, u8* textura, Vtx* parametro7, s32 parametro8,
                   s32 parametro9, s32 parametro_a, s32 parametro_b) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007E38);
    fijar_transparencia(parametro4);
    funcion_80047068(tlut, textura, parametro7, parametro8, parametro9, parametro_a, parametro_b);
}

SIN_USO void funcion_80047D40(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, s32 parametro4, u8* tlut, u8* textura, Vtx* parametro7, s32 parametro8,
                          s32 parametro9, s32 parametro_a, s32 parametro_b) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007E58);
    fijar_transparencia(parametro4);
    dibujar_superponer_textura_rectangulo(tlut, textura, parametro7, parametro8, parametro9, parametro_a, parametro_b);
}

SIN_USO void funcion_80047DCC(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* tlut, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7,
                          s32 parametro8, s32 parametro9) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007CB8);
    funcion_80047068(tlut, textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

void funcion_80047E48(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* tlut, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007CD8);
    dibujar_superponer_textura_rectangulo(tlut, textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

SIN_USO void funcion_80047EC4(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* tlut, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7,
                          s32 parametro8, s32 parametro9) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007D18);
    funcion_80047068(tlut, textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

void funcion_80047F40(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* tlut, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007D38);
    dibujar_superponer_textura_rectangulo(tlut, textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

SIN_USO void funcion_80047FBC(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* tlut, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7,
                          s32 parametro8, s32 parametro9) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007D58);
    dibujar_superponer_textura_rectangulo(tlut, textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

SIN_USO void funcion_80048038(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* tlut, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7,
                          s32 parametro8, s32 parametro9) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007D98);
    funcion_80047068(tlut, textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

void dibujar_2d_textura_en(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* tlut, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7,
                        s32 parametro8, s32 parametro9) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007D78);
    dibujar_superponer_textura_rectangulo(tlut, textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

void funcion_80048130(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* tlut, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9, s32 parametro_a) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007D78);
    funcion_8004747C(tlut, textura, parametro5, parametro6, parametro7, parametro8, parametro9, parametro_a);
}

SIN_USO void funcion_800481B4(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* tlut, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7,
                          s32 parametro8) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007D78);
    funcion_8004768C(tlut, textura, parametro5, parametro6, parametro7, parametro8);
}

SIN_USO void funcion_80048228(Vec3f parametro0, Vec3su parametro1, f32 parametro2, s32 parametro3, u8* tlut, u8* textura, Vtx* parametro6, s32 parametro7,
                          s32 parametro8, s32 parametro9, s32 parametro_a) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007DB8);
    fijar_transparencia(parametro3);
    funcion_80047068(tlut, textura, parametro6, parametro7, parametro8, parametro9, parametro_a);
}

void funcion_800482AC(Vec3f parametro0, Vec3su parametro1, f32 parametro2, s32 parametro3, u8* tlut, u8* textura, Vtx* parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9, s32 parametro_a) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007DD8);
    fijar_transparencia(parametro3);
    dibujar_superponer_textura_rectangulo(tlut, textura, parametro6, parametro7, parametro8, parametro9, parametro_a);
}

SIN_USO void funcion_80048330(Vec3f parametro0, Vec3su parametro1, f32 parametro2, s32 parametro3, u8* tlut, u8* textura, Vtx* parametro6, s32 parametro7,
                          s32 parametro8, s32 parametro9, s32 parametro_a) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007E38);
    fijar_transparencia(parametro3);
    funcion_80047068(tlut, textura, parametro6, parametro7, parametro8, parametro9, parametro_a);
}

void funcion_800483B4(Vec3f parametro0, Vec3su parametro1, f32 parametro2, s32 parametro3, u8* tlut, u8* textura, Vtx* parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9, s32 parametro_a) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007E58);
    fijar_transparencia(parametro3);
    dibujar_superponer_textura_rectangulo(tlut, textura, parametro6, parametro7, parametro8, parametro9, parametro_a);
}

void funcion_80048438(Vec3f parametro0, Vec3su parametro1, f32 parametro2, s32 parametro3, u8* tlut, u8* textura, Vtx* parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9, s32 parametro_a) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007DF8);
    fijar_transparencia(parametro3);
    funcion_80047068(tlut, textura, parametro6, parametro7, parametro8, parametro9, parametro_a);
}

void funcion_800484BC(Vec3f parametro0, Vec3su parametro1, f32 parametro2, s32 parametro3, u8* tlut, u8* textura, Vtx* parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9, s32 parametro_a) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007E18);
    fijar_transparencia(parametro3);
    dibujar_superponer_textura_rectangulo(tlut, textura, parametro6, parametro7, parametro8, parametro9, parametro_a);
}

void funcion_80048540(Vec3f parametro0, Vec3su parametro1, f32 parametro2, s32 parametro3, u8* tlut, u8* textura, Vtx* parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9, s32 parametro_a) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007E98);
    fijar_transparencia(parametro3);
    dibujar_superponer_textura_rectangulo(tlut, textura, parametro6, parametro7, parametro8, parametro9, parametro_a);
}

void funcion_800485C4(Vec3f parametro0, Vec3su parametro1, f32 parametro2, s32 parametro3, u8* tlut, u8* textura, Vtx* parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9, s32 parametro_a) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007E98);
    gDPSetAlphaCompare(display_list_cabeza++, G_AC_DITHER);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);

    fijar_transparencia(parametro3);
    dibujar_superponer_textura_rectangulo(tlut, textura, parametro6, parametro7, parametro8, parametro9, parametro_a);

    gDPSetAlphaCompare(display_list_cabeza++, G_AC_NONE);
}

SIN_USO void funcion_800486B0(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_8004788C(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 24, 48, 24, 48);
}

SIN_USO void funcion_80048718(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_8004788C(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 32, 32, 32, 32);
}

SIN_USO void funcion_80048780(Vec3f parametro0, Vec3su parametro1, f32 parametro2, s32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_80048540(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 48, 48, 48, 40);
}

SIN_USO void funcion_800487DC(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_8004788C(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 48, 48, 48, 48);
}

SIN_USO void funcion_80048844(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_8004788C(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 64, 32, 64, 32);
}

SIN_USO void funcion_800488AC(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_8004788C(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 64, 64, 64, 32);
}

SIN_USO void funcion_80048914(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_80047910(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 64, 64, 64, 32);
}

SIN_USO void funcion_8004897C(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_80047994(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 64, 64, 64, 32);
}

SIN_USO void funcion_800489E4(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_80047A18(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 64, 64, 64, 32);
}

SIN_USO void funcion_80048A4C(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_80047A9C(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 64, 64, 64, 32);
}
