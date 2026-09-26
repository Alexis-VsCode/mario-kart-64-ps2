// Dibujar objetos y nieve

#define HACER_RGB(r, g, b) (((r) << 0x10) | ((g) << 0x08) | (b << 0x00))

s32 dato_80165590;
s32 dato_80165594;
s32 dato_80165598;
s32 dato_8016559C;
SIN_USO s32 dato_801655A0;
s32 dato_801655A4;
SIN_USO s32 dato_801655A8;
s32 dato_801655AC;
SIN_USO s32 dato_801655B0;
s32 dato_801655B4;
SIN_USO s32 dato_801655B8;
s32 dato_801655BC;
s32 dato_801655C0;
s32 dato_801655C4;
s32 dato_801655C8;
s32 dato_801655CC;
SIN_USO s32 dato_801655D0[2];
s32 dato_801655D8;
SIN_USO s32 dato_801655DC[2];
s32 dato_801655E8;
SIN_USO s32 dato_801655EC;
s32 dato_801655F0;
SIN_USO s32 dato_801655F4;
s32 dato_801655F8;
SIN_USO s32 dato_80165600[2];
s32 dato_80165608;
SIN_USO s32 dato_80165610[2];
s32 dato_80165618;
SIN_USO s32 dato_80165620[2];
s32 dato_80165628;
SIN_USO s32 dato_80165630[2];
u32 dato_80165638;
SIN_USO s32 dato_80165640[2];
u32 dato_80165648;
SIN_USO u32 dato_80165650[2];
u32 dato_80165658[8];
s32 dato_80165678;
SIN_USO s32 dato_80165680[12];
u16 dato_801656B0;
SIN_USO s32 dato_801656B8[2];
u16 dato_801656C0;
SIN_USO s32 dato_801656C8[2];
u16 dato_801656D0;
SIN_USO s32 dato_801656D8[2];
u16 dato_801656E0;
SIN_USO s32 dato_801656E8[2];
s16 dato_801656F0;
SIN_USO s32 dato_801656F8[4];
s16 dato_80165708;
SIN_USO s32 dato_8016570C;
s16 dato_80165710;
SIN_USO s32 dato_80165714;
s16 dato_80165718;
SIN_USO s32 dato_8016571C;
s16 dato_80165720;
SIN_USO s32 dato_80165724;
s16 dato_80165728;
SIN_USO s32 dato_8016572C;
s16 dato_80165730;
SIN_USO s32 dato_80165734;
s16 dato_80165738;
SIN_USO s32 dato_8016573C;
s16 dato_80165740;
SIN_USO s32 dato_80165744;
s16 dato_80165748;
SIN_USO s32 dato_8016574C;

s16 thwomps_activo_num;
s32 dato_80165754;
ThwompAparicion* lista_aparicion_thowmp;

Vec4s dato_80165760;
SIN_USO s16 dato_80165768;
s8 dato_8016576A;
Vec4s dato_80165770;
SIN_USO s32 dato_80165778;
Vec4s dato_80165780;
SIN_USO s32 dato_80165788;
s16 dato_8016578C;
SIN_USO s16 dato_8016578E;
s16 dato_80165790;
SIN_USO s16 dato_80165792;
s16 dato_80165794;
SIN_USO s32 dato_80165798;
s8 dato_8016579C;
u16 dato_8016579E;
SIN_USO s16 dato_801657A0;
u16 dato_801657A2;
SIN_USO s32 dato_801657A4;
SIN_USO s16 dato_801657A8[3];
s8 dato_801657AE;
SIN_USO s8 dato_801657AF;
s8 desactivar_hud;
SIN_USO s8 dato_801657B1;
s8 dato_801657B2;
SIN_USO s8 dato_801657B3;
s8 dato_801657B4;
s8 dato_801657B8[16];
s8 dato_801657C8;
s8 dato_801657D0[8];
s8 dato_801657D8;
SIN_USO s16 dato_801657DA[2];
SIN_USO s8 dato_801657E0;
s8 dato_801657E1;
s8 dato_801657E2;
s8 dato_801657E3;
s8 dato_801657E4;
s8 dato_801657E5;
bool8 dato_801657E6;
u8 dato_801657E7;
bool8 dato_801657E8;
SIN_USO s32 dato_801657EC;
bool8 dato_801657F0;
SIN_USO s32 dato_801657F4;
bool8 dato_801657F8;
s32 dato_801657FC;
s8 dato_80165800[2];
s32 dato_80165804;
s8 dato_80165808;
s32 dato_8016580C;
bool8 dato_80165810;
s32 dato_80165814;
bool8 dato_80165818;
s32 dato_8016581C;
s8 dato_80165820;
SIN_USO s32 dato_80165824;
s8 dato_80165828;
Vec3su dato_8016582C;
s8 dato_80165832[2];
Vec3su dato_80165834;
SIN_USO s32 dato_8016583A;
s8 dato_80165840[3];
SIN_USO s32 dato_80165848[6];
s32 dato_80165860;
SIN_USO s32 dato_80165864;
SIN_USO s32 dato_80165868;
s32 dato_8016586C;
SIN_USO s32 dato_80165870[2];
s32 dato_80165878;
s32 dato_8016587C;
u8* dato_80165880;
SIN_USO s32 dato_80165884;
s8 dato_80165888;
SIN_USO s32 dato_8016588C;
s8 dato_80165890;
SIN_USO s32 dato_80165894;
s8 dato_80165898;
s32 dato_8016589C;
SIN_USO s32 dato_801658A0[2];
s8 dato_801658A8;
SIN_USO s32 dato_801658B0[3];
s8 dato_801658BC;
SIN_USO s32 dato_801658C0;
SIN_USO s16 dato_801658C4;
s8 dato_801658C6;
SIN_USO s32 dato_801658C8;
SIN_USO s16 dato_801658CC;
s8 dato_801658CE;
SIN_USO s32 dato_801658D0;
SIN_USO s16 dato_801658D4;
s8 dato_801658D6;
SIN_USO s32 dato_801658D8;
s8 dato_801658DC;
SIN_USO s32 dato_801658E0;
s8 dato_801658E4;
SIN_USO s32 dato_801658E8;
s8 dato_801658EC;
SIN_USO s32 dato_801658F0;
s8 dato_801658F4;
SIN_USO s32 dato_801658F8;
SIN_USO s8 dato_801658FC;
u8 indice_item_aleatorio;
s8 dato_801658FE;
u8 aleatorio_mando;
s16 dato_80165900;
SIN_USO s32 dato_80165904;
s8 dato_80165908;
SIN_USO s32 dato_80165910[96];
s8 dato_80165A90;
SIN_USO s32 dato_80165AA0[95];
SIN_USO s32 dato_80165C14;
Objeto lista_objeto[TAMANIO_LISTA_OBJETO];
SIN_USO s32 dato_80183D58;
s32 tamanio_lista_objeto;
Mtx dato_80183D60;
s32 dato_80183DA0;
f32 dato_80183DA8[4];
s32 indice_lakitu_lista[4];
f32 dato_80183DC8[4];
s32 objeto_indice_kart_bomba[NUM_KARTS_BOMBA_MAX];
SIN_USO s32 dato_80183DF8[16];
s32 siguiente_libre_objeto_particula_1;
Vec3f dato_80183E40;
s32 siguiente_libre_objeto_particula_2;
Vec3f dato_80183E50;
s32 siguiente_libre_objeto_particula_3;
SIN_USO s32 dato_80183E60[3];
s32 siguiente_libre_objeto_particula_4;
Vec3f dato_80183E70;
s32 siguiente_libre_hoja_particula;
Vec3su dato_80183E80;
s32 ventana_item_objeto_por_id_jugador[4];
Vec3su dato_80183E98;
s32 lista_objeto_indice_1[32];
SIN_USO s32 dato_80183F20[2];
s32 lista_objeto_indice_2[32];
u8 dato_80183FA8[4][0x2000];
s32 lista_objeto_indice_3[32];
u8* lakitu_ptr_textura;
s32 lista_objeto_indice_4[32];
Colision dato_8018C0B0[4];
s32 particula_objeto_1[objeto_particula_2_tamanio];
Colision dato_8018C3B0;
s32 particula_objeto_2[objeto_particula_2_tamanio];
SIN_USO Colision dato_8018C5F0;
s32 particula_objeto_3[objeto_particula_3_tamanio];
Colision dato_8018C830;
s32 particula_objeto_4[objeto_particula_4_tamanio];
s32 particula_hoja[hoja_particula_tamanio];
jugador_hud h_ud_jugador[4];
s32 dato_8018CC80[TAMANIO_D_8018CC80];
struct_d_8018CE10 dato_8018CE10[8];
s32 dato_8018CF10;
Camara* dato_8018CF14;
s16 dato_8018CF18;
Jugador* dato_8018CF1C;
s16 dato_8018CF20;
SIN_USO s32 dato_8018CF24;
Jugador* dato_8018CF28[8];
s16 dato_8018CF48;
s16 dato_8018CF50[8];
s16 dato_8018CF60;
s16 dato_8018CF68[8];
s16 dato_8018CF78;
s16 gp_actual_carrera_personaje_id_por_puesto[8];
s16 dato_8018CF90;
s16 dato_8018CF98[8];
s16 dato_8018CFA8;
u8 dato_8018CFAC[4];
s16 dato_8018CFB0;
u8 dato_8018CFB4[4];
s16 dato_8018CFB8;
u8 dato_8018CFBC[4];
s16 dato_8018CFC0;
u8 dato_8018CFC4[4];
s16 dato_8018CFC8;
f32 dato_8018CFCC;
s16 dato_8018CFD0;
f32 dato_8018CFD4;
s16 dato_8018CFD8;

s16 dato_800E4730[] = { 0x00ff, 0x0000, 0x0000, 0x00ff, 0x00ff, 0x0000, 0x0000, 0x00ff, 0x0000, 0x0032, 0x00ff, 0x00ff,
                     0x0000, 0x0000, 0x00ff, 0x00ff, 0x0032, 0x00ff, 0x00ff, 0x0028, 0x0028, 0x0032, 0x00ff, 0x0064,
                     0x0082, 0x000f, 0x00ff, 0x0000, 0x0000, 0x0000,
                     0x0000 };

u8** dato_800E4770[] = {
    &dato_8018D420, &dato_8018D424, &dato_8018D428, &dato_8018D428, &dato_8018D42C, &dato_8018D42C,
    &dato_8018D430, &dato_8018D430, &dato_8018D434, &dato_8018D434, &dato_8018D434, &dato_8018D434,
};

u8** dato_800E47A0[] = {
    &dato_8018D438, &dato_8018D43C, &dato_8018D440, &dato_8018D444, &dato_8018D448, &dato_8018D44C, &dato_8018D450, &dato_8018D454,
    &dato_8018D458, &dato_8018D45C, &dato_8018D460, &dato_8018D464, &dato_8018D468, &dato_8018D46C, &dato_8018D470,
};

s32 dato_800E47DC[] = {
    HACER_RGB(0xFB, 0xFF, 0xFB), HACER_RGB(0xA0, 0x60, 0x11), HACER_RGB(0xE0, 0xC0, 0x90), HACER_RGB(0xD0, 0xB0, 0x80),
    HACER_RGB(0x90, 0x70, 0x40), HACER_RGB(0xC0, 0x70, 0x10), HACER_RGB(0xD0, 0xF0, 0xFF), HACER_RGB(0xE0, 0x90, 0x30),
    HACER_RGB(0xC0, 0x90, 0x30), HACER_RGB(0x60, 0x40, 0x20), HACER_RGB(0xF0, 0xD0, 0xB0), HACER_RGB(0xA0, 0x80, 0x30),
};

s32 dato_800E480C[] = {
    HACER_RGB(0xB0, 0xB0, 0xB0), HACER_RGB(0x80, 0x40, 0x11), HACER_RGB(0xB0, 0x80, 0x50), HACER_RGB(0xA0, 0x70, 0x40),
    HACER_RGB(0x60, 0x30, 0x11), HACER_RGB(0x80, 0x40, 0x10), HACER_RGB(0x70, 0x90, 0xA0), HACER_RGB(0xA0, 0x60, 0x30),
    HACER_RGB(0xA0, 0x70, 0x10), HACER_RGB(0x30, 0x10, 0x11), HACER_RGB(0xB0, 0xA0, 0x80), HACER_RGB(0x80, 0x60, 0x10),
};

void funcion_80057C60(void) {
    gSPViewport(display_list_cabeza++, VIRTUAL_A_FISICO(dato_802B8880));
    gDPSetScissor(display_list_cabeza++, G_SC_NON_INTERLACE, 0, 0, ANCHO_PANTALLA, ALTURA_PANTALLA);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&dato_80183D60), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
}

void funcion_80057CE4(void) {
    switch (dato_8018D21C) {
        case 0:
            funcion_802A3730(dato_800DC5EC);
            break;
        case 1:
            funcion_802A3730(dato_800DC5EC);
            break;
        case 2:
            funcion_802A3730(dato_800DC5F0);
            break;
        case 3:
            funcion_802A3730(dato_800DC5EC);
            break;
        case 4:
            funcion_802A3730(dato_800DC5F0);
            break;
        case 8:
            funcion_802A3730(dato_800DC5EC);
            break;
        case 9:
            funcion_802A3730(dato_800DC5F0);
            break;
        case 10:
            funcion_802A3730(dato_800DC5F4);
            break;
        case 11:
            funcion_802A3730(dato_800DC5F8);
            break;
    }
}

void funcion_80057DD0(void) {
    if (dato_801657B2 != 0) {
        funcion_8004C024(0xF, 0xB, 0x122, 0, 0xFF, 0, 0xFF);
        funcion_8004C148(0x131, 0xB, 0xDA, 0, 0xFF, 0, 0xFF);
        funcion_8004C024(0xF, 0xE5, 0x122, 0, 0xFF, 0, 0xFF);
        funcion_8004C148(0xF, 0xB, 0xDA, 0, 0xFF, 0, 0xFF);
        funcion_8004C024(0x16, 0x10, 0x114, 0xFF, 0, 0, 0xFF);
        funcion_8004C148(0x12A, 0x10, 0xD0, 0xFF, 0, 0, 0xFF);
        funcion_8004C024(0x16, 0xE0, 0x114, 0xFF, 0, 0, 0xFF);
        funcion_8004C148(0x16, 0x10, 0xD0, 0xFF, 0, 0, 0xFF);
        funcion_8004C024(0x18, 0x15, 0x110, 0, 0, 0xFF, 0xFF);
        funcion_8004C148(0x128, 0x15, 0xC4, 0, 0, 0xFF, 0xFF);
        funcion_8004C024(0x18, 0xDB, 0x110, 0, 0, 0xFF, 0xFF);
        funcion_8004C148(0x18, 0x15, 0xC4, 0, 0, 0xFF, 0xFF);
    }
}

void funcion_80057FC4(u32 parametro0) {
    SIN_USO Gfx* temporal_v1;

    if ((desactivar_hud != 0)) {
        return;
    }
    gSPDisplayList(display_list_cabeza++, &dato_0D0076F8);
    fijar_pantalla_hud_matriz();

    if ((dato_801657C8 != 0)) {
        return;
    }

    switch (parametro0) {
        case 0:
            funcion_80051EBC();
            break;
        case 1:
            funcion_80051EF8();
            break;
        case 2:
            funcion_80051F9C();
            break;
        case 3:
            funcion_80052044();
            break;
        case 4:
            funcion_80052080();
            break;
    }
}

void renderizar_objeto(u32 parametro0) {
    SIN_USO Gfx* temporal_v1;

    if (desactivar_hud != 0) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, &dato_0D0076F8);

    if (dato_8018D22C != 0) {
        return;
    }

    switch (parametro0) {
        case RENDER_PANTALLA_MODO_1J_JUGADOR_UNO:
            renderizar_objeto_p1();
            break;
        case RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_UNO:
            renderizar_objeto_p1();
            break;
        case RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_DOS:
            renderizar_objeto_p2();
            break;
        case RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_UNO:
            renderizar_objeto_p1();
            break;
        case RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_DOS:
            renderizar_objeto_p2();
            break;
        case 5:
            renderizar_objeto_p1();
            break;
        case 6:
            renderizar_objeto_p2();
            break;
        case 7:
            renderizar_objeto_p3();
            break;
        case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_UNO:
            renderizar_objeto_p1();
            break;
        case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_DOS:
            renderizar_objeto_p2();
            break;
        case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_TRES:
            renderizar_objeto_p3();
            break;
        case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_CUATRO:
            renderizar_objeto_p4();
            break;
    }
}

void renderizar_objeto_p1(void) {

    gDPSetTexturePersp(display_list_cabeza++, G_TP_PERSP);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[0]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[0]),
              G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    renderizar_karts_bomba_envoltura(JUGADOR_UNO);
    if (estado_juego == FINAL) {
        funcion_80055F48(JUGADOR_UNO);
        funcion_80056160(JUGADOR_UNO);
        funcion_8005217C(JUGADOR_UNO);
        funcion_80054BE8(JUGADOR_UNO);
        return;
    }
    if (!modo_demo) {
        renderizar_lakitu(JUGADOR_UNO);
    }
    renderizar_objeto_para_jugador(JUGADOR_UNO);
}

void renderizar_objeto_p2(void) {

    gDPSetTexturePersp(display_list_cabeza++, G_TP_PERSP);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[1]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[1]),
              G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    renderizar_karts_bomba_envoltura(JUGADOR_DOS);
    if (!modo_demo) {
        renderizar_lakitu(JUGADOR_DOS);
    }
    renderizar_objeto_para_jugador(JUGADOR_DOS);
}

void renderizar_objeto_p3(void) {
    gDPSetTexturePersp(display_list_cabeza++, G_TP_PERSP);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[2]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[2]),
              G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    renderizar_karts_bomba_envoltura(JUGADOR_TRES);
    if (!modo_demo) {
        renderizar_lakitu(JUGADOR_TRES);
    }
    renderizar_objeto_para_jugador(JUGADOR_TRES);
}

void renderizar_objeto_p4(void) {

    gDPSetTexturePersp(display_list_cabeza++, G_TP_PERSP);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[3]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[3]),
              G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    renderizar_karts_bomba_envoltura(JUGADOR_CUATRO);
    if ((!modo_demo) && (seleccion_cantidad_jugador_1 == 4)) {
        renderizar_lakitu(JUGADOR_CUATRO);
    }
    renderizar_objeto_para_jugador(JUGADOR_CUATRO);
}

void renderizar_efecto_nieve_jugador(u32 parametro0) {
    SIN_USO Gfx* temporal_v1;

    if (desactivar_hud != 0) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, &dato_0D0076F8);

    if (dato_8018D22C != 0) {
        return;
    }
    switch (parametro0) {
        case RENDER_PANTALLA_MODO_1J_JUGADOR_UNO:
            renderizar_efecto_uno_nieve_jugador();
            break;
        case RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_UNO:
            renderizar_efecto_uno_nieve_jugador();
            break;
        case RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_DOS:
            renderizar_efecto_dos_nieve_jugador();
            break;
        case RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_UNO:
            renderizar_efecto_uno_nieve_jugador();
            break;
        case RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_DOS:
            renderizar_efecto_dos_nieve_jugador();
            break;
        case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_UNO:
            renderizar_efecto_uno_nieve_jugador();
            break;
        case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_DOS:
            renderizar_efecto_dos_nieve_jugador();
            break;
        case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_TRES:
            renderizar_efecto_tres_nieve_jugador();
            break;
        case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_CUATRO:
            renderizar_efecto_cuatro_nieve_jugador();
            break;
    }
}

void renderizar_efecto_uno_nieve_jugador(void) {
    gDPSetTexturePersp(display_list_cabeza++, G_TP_PERSP);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[0]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[0]),
              G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    if (estado_juego != FINAL) {
        renderizar_efecto_nevando(JUGADOR_UNO);
    }
}

void renderizar_efecto_dos_nieve_jugador(void) {
    gDPSetTexturePersp(display_list_cabeza++, G_TP_PERSP);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[1]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[1]),
              G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    renderizar_efecto_nevando(JUGADOR_DOS);
}

void renderizar_efecto_tres_nieve_jugador(void) {
    gDPSetTexturePersp(display_list_cabeza++, G_TP_PERSP);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[2]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[2]),
              G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    renderizar_efecto_nevando(JUGADOR_TRES);
}

void renderizar_efecto_cuatro_nieve_jugador(void) {
    gDPSetTexturePersp(display_list_cabeza++, G_TP_PERSP);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[3]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[3]),
              G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    renderizar_efecto_nevando(JUGADOR_CUATRO);
}

void renderizar_objeto_para_jugador(s32 id_camara) {
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_MARIO_RACEWAY:
            break;
        case CIRCUITO_CHOCO_MOUNTAIN:
            break;
        case CIRCUITO_BOWSER_CASTLE:
            renderizar_thwomps_objeto(id_camara);
            renderizar_objeto_bowser_llama(id_camara);
            break;
        case CIRCUITO_BANSHEE_BOARDWALK:
            if (estado_juego != SECUENCIA_CREDITOS) {
                renderizar_bin_basura_objeto(id_camara);
                renderizar_murcielago_objeto(id_camara);
                funcion_8005217C(id_camara);
                renderizar_boos_objeto(id_camara);
            }
            break;
        case CIRCUITO_YOSHI_VALLEY:
            funcion_80055228(id_camara);
            if (estado_juego != SECUENCIA_CREDITOS) {
                renderizar_erizos_objeto(id_camara);
            }
            break;
        case CIRCUITO_FRAPPE_SNOWLAND:
            if (estado_juego != SECUENCIA_CREDITOS) {
                renderizar_muniecos_nieve_objeto(id_camara);
            }
            break;
        case CIRCUITO_KOOPA_BEACH:
            if (estado_juego != SECUENCIA_CREDITOS) {
                renderizar_cangrejos_objeto(id_camara);
            }
            if (estado_juego != SECUENCIA_CREDITOS) {

                if ((cantidad_jugador == 1) || (cantidad_jugador == 2)) {
                    renderizar_gaviotas_objeto(id_camara);
                }
            } else {
                renderizar_gaviotas_objeto(id_camara);
            }
            break;
        case CIRCUITO_ROYAL_RACEWAY:
            break;
        case CIRCUITO_LUIGI_RACEWAY:
            if (dato_80165898 != 0) {
                renderizar_objeto_globo_aerostatico(id_camara);
            }
            break;
        case CIRCUITO_MOO_MOO_FARM:
            if (estado_juego != SECUENCIA_CREDITOS) {
                renderizar_topos_objeto(id_camara);
            }
            break;
        case CIRCUITO_TOADS_TURNPIKE:
            break;
        case CIRCUITO_KALAMARI_DESERT:
            renderizar_objeto_trenes_humo_particulas(id_camara);
            break;
        case CIRCUITO_SHERBET_LAND:
            if (estado_juego != SECUENCIA_CREDITOS) {
                funcion_80052E30(id_camara);
            }
            renderizar_pinguinos_tren_objeto(id_camara);
            break;
        case CIRCUITO_RAINBOW_ROAD:
            if (estado_juego != SECUENCIA_CREDITOS) {
                renderizar_neon_objeto(id_camara);
                renderizar_chomps_cadena_objeto(id_camara);
            }
            break;
        case CIRCUITO_WARIO_STADIUM:
            break;
        case CIRCUITO_BLOCK_FORT:
            break;
        case CIRCUITO_SKYSCRAPER:
            break;
        case CIRCUITO_DOUBLE_DECK:
            break;
        case CIRCUITO_DK_JUNGLE:
            if (estado_juego != SECUENCIA_CREDITOS) {
                renderizar_objeto_paleta_barco_humo_particulas(id_camara);
            }
            break;
    }
#else

#endif

    renderizar_particulas_humo_objeto(id_camara);
    renderizar_particula_hoja_objeto(id_camara);

    if (dato_80165730 != 0) {
        renderizar_objeto_gran_premio_globos(id_camara);
    }
    if (seleccion_modo == BATALLA) {
        renderizar_objeto_kart_bomba(id_camara);
    }
}

void renderizar_efecto_nevando(s32 parametro0) {
    switch (id_circuito_actual) {
        case CIRCUITO_FRAPPE_SNOWLAND:
            if (estado_juego != 9) {
                if ((dato_8015F894 == 0) && (seleccion_cantidad_jugador_1 == 1)) {
                    renderizar_particulas_copos_objeto();
                }
            } else {
                renderizar_particulas_copos_objeto();
            }
            break;
        case CIRCUITO_SHERBET_LAND:
            renderizar_bloque_hielo(parametro0);
            break;
    }
}

void funcion_80058BF4(void) {
    gSPDisplayList(display_list_cabeza++, &dato_0D0076F8);
}

void funcion_80058C20(u32 parametro0) {

    dato_8018D21C = parametro0;
    gSPDisplayList(display_list_cabeza++, &dato_0D0076F8);

    if (dato_8018D22C == 0) {
        switch (parametro0) {
            case RENDER_PANTALLA_MODO_1J_JUGADOR_UNO:
                funcion_80058F48();
                break;
            case RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_UNO:
                if (!modo_demo) {
                    funcion_80059358();
                    break;
                }

                break;
            case RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_DOS:
                if (!modo_demo) {
                    funcion_800593F0();
                    break;
                }

                break;
            case RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_UNO:
                if (!modo_demo) {
                    funcion_800594F0();
                    break;
                }

                break;
            case RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_DOS:
                if (!modo_demo) {
                    funcion_80059528();
                    break;
                }

                break;
            case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_UNO:
                if (!modo_demo) {
                    funcion_800596A8();
                    break;
                }

                break;
            case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_DOS:
                if (!modo_demo) {
                    funcion_80059710();
                    break;
                }

                break;
            case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_TRES:
                if (!modo_demo) {
                    funcion_80059750();
                    break;
                }

                break;
            case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_CUATRO:
                if ((!modo_demo) && (seleccion_cantidad_jugador_1 == 4)) {
                    funcion_800597B8();
                }
                break;
        }
    }
}

void renderizar_hud(u32 parametro0) {

    dato_8018D21C = parametro0;
    gSPDisplayList(display_list_cabeza++, &dato_0D0076F8);
    if (dato_8018D22C == 0) {
        switch (parametro0) {
            case RENDER_PANTALLA_MODO_1J_JUGADOR_UNO:
                funcion_80058F78();
                break;
            case RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_UNO:
                if (!modo_demo) {
                    renderizar_hud_2j_horizontal_jugador_dos_horizontal_jugador_uno();
                    break;
                }

                break;
            case RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_DOS:
                if (!modo_demo) {
                    renderizar_jugador_dos_horizontal_hud_2j();
                    break;
                }

                break;
            case RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_UNO:
                if (!modo_demo) {
                    renderizar_jugador_uno_vertical_hud_2j();
                    break;
                }

                break;
            case RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_DOS:
                if (!modo_demo) {
                    renderizar_jugador_dos_vertical_hud_2j();
                    break;
                }

                break;
            case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_UNO:
                if (!modo_demo) {
                    renderizar_multi_hud_1j();
                    break;
                }

                break;
            case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_DOS:
                if (!modo_demo) {
                    renderizar_multi_hud_2j();
                    break;
                }

                break;
            case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_TRES:
                if (!modo_demo) {
                    renderizar_multi_hud_3j();
                    break;
                }

                break;
            case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_CUATRO:
                if ((!modo_demo) && (seleccion_cantidad_jugador_1 == 4)) {
                    renderizar_multi_hud_4j();
                }
                break;
        }
    }
}

void funcion_80058F48(void) {
    if (desactivar_hud == 0) {
        fijar_pantalla_hud_matriz();
    }
}

void funcion_80058F78(void) {
    if (desactivar_hud == 0) {
        fijar_pantalla_hud_matriz();
        if ((!modo_demo) && (es_visible_hud != 0) && (dato_801657D8 == 0)) {
            dibujar_ventana_item(JUGADOR_UNO);
            if (dato_801657E4 != 2) {
                renderizar_temporizador_hud(JUGADOR_UNO);
                dibujar_cantidad_vuelta_simplificado(JUGADOR_UNO);
                funcion_8004EB38(0);
                if (dato_801657E6 != false) {
                    funcion_8004ED40(0);
                }
            }
        }
    }
}

void funcion_80059024(void) {
}

void funcion_8005902C(void) {

    if (dato_8018D2AC != 0) {
        switch (seleccion_cantidad_jugador_1) {
            case 2:
                funcion_8004EB30(JUGADOR_UNO);
                funcion_8004EB30(JUGADOR_DOS);
                break;
            case 3:
                funcion_8004EB30(JUGADOR_UNO);
                funcion_8004EB30(JUGADOR_DOS);
                funcion_8004EB30(JUGADOR_TRES);
                break;
            case 4:
                funcion_8004EB30(JUGADOR_UNO);
                funcion_8004EB30(JUGADOR_DOS);
                funcion_8004EB30(JUGADOR_TRES);
                funcion_8004EB30(JUGADOR_CUATRO);
                break;
        }
    }
}

void funcion_800590D4(void) {
    if (dato_8018D2A4 != 0) {
        if (seleccion_modo != BATALLA) {
            switch (seleccion_cantidad_jugador_1) {
                case 1:
                    if (seleccion_modo != CONTRARRELOJ) {
                        funcion_8004E800(JUGADOR_UNO);
                        break;
                    }
                    break;
                case 2:
                    funcion_8004E800(JUGADOR_UNO);
                    funcion_8004E800(JUGADOR_DOS);
                    break;
                case 3:
                    funcion_8004E998(JUGADOR_UNO);
                    funcion_8004E998(JUGADOR_DOS);
                    funcion_8004E998(JUGADOR_TRES);
                    break;
                case 4:
                    funcion_8004E998(JUGADOR_UNO);
                    funcion_8004E998(JUGADOR_DOS);
                    funcion_8004E998(JUGADOR_TRES);
                    funcion_8004E998(JUGADOR_CUATRO);
                    break;
            }
        }
    }
}
