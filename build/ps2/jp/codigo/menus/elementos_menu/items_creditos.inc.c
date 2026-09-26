// Items creditos

void funcion_800AF270(MenuItem* parametro0) {
    s32 temporal_v1;
    s32 sp30;
    s32 temporal_v0;
    desconocido_d_800E70A0* cosa;

    temporal_v1 = parametro0->type - 0x12C;
    sp30 = dato_802874D8.desconocido_1e;
    temporal_v0 = dato_800EFD64[sp30];
    switch (parametro0->state) {
        case 0:
            cosa = &dato_800E7458[temporal_v1];
            parametro0->column = cosa->column;
            parametro0->row = cosa->row;
            parametro0->state = 1;
            break;
        case 1:
            cosa = &dato_800E7480[temporal_v1];
            funcion_800A91D8(parametro0, cosa->column, cosa->row);
            if ((parametro0->column == cosa->column) && (parametro0->row == cosa->row)) {
                parametro0->state = 2;
                parametro0->param2 = 0;
            }
            break;
        case 2:
            parametro0->param2++;
            if (parametro0->param2 >= 0x1F) {
                if (dato_802874D8.desconocido_1d >= 3) {
                    parametro0->state = 4;
                    funcion_800CA0B8();
                    funcion_800C90F4(0U, (sp30 * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x03));
                    funcion_800CA0A0();
                } else {
                    parametro0->state = 3;
                    funcion_8009A640(parametro0->d_8018DEE0_indice, 0, sp30,
                                  segmentado_a_duplicado_virtual_2(animacion_celebracion_personaje[temporal_v0]));
                    funcion_800CA0B8();
                    funcion_800C90F4(0U, (sp30 * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x07));
                    funcion_800CA0A0();
                }
            }
            break;
        case 3:
            if (dato_8018DEE0[parametro0->d_8018DEE0_indice].indice_secuencia >= dato_800E8440[temporal_v0]) {
                funcion_8009A640(parametro0->d_8018DEE0_indice, 0, sp30, segmentado_a_duplicado_virtual_2(dato_800E83A0[temporal_v0]));
                parametro0->state = 4;
            }
            break;
        case 4:
            break;
    }
}

void funcion_800AF480(MenuItem* parametro0) {
    s32 idx = parametro0->type - 0x190;

    if ((creditos_texto_render_info[idx].sentido_deslizamiento == 0) || (creditos_texto_render_info[idx].sentido_deslizamiento != 1)) {
        funcion_800AF4DC(parametro0);
    } else {
        funcion_800AF740(parametro0);
    }
}

void funcion_800AF4DC(MenuItem* parametro0) {
    SIN_USO s32 relleno;
    s32 temporal_v0;
    InfoRenderCreditos* temporal_v1;

    temporal_v0 = parametro0->type - 0x190;
    temporal_v1 = &creditos_texto_render_info[temporal_v0];
    parametro0->row = temporal_v1->row;
    switch (parametro0->state) {
        case 0:
            parametro0->column = temporal_v1->columna_inicial;
            parametro0->state = 1;
            parametro0->param2 = temporal_v1->extra_columna + (obtener_ancho_cadena(texto_creditos[temporal_v0]) * temporal_v1->escalado_texto / 2);
        case 1:
            funcion_800A9208(parametro0, parametro0->param2);
            parametro0->param1 = (s32) (parametro0->param2 - parametro0->column) / 4;
            if (parametro0->param1 >= 9) {
                parametro0->param1 = 8;
            }
            parametro0->paramf = (parametro0->param1 * 0.05) + 1.0;
            if (parametro0->column >= (parametro0->param2 - 0x14)) {
                parametro0->state = 2;
                parametro0->d_8018DEE0_indice = 0;
            }
            break;
        case 2:
            funcion_800A9208(parametro0, parametro0->param2);
            parametro0->param1 = (parametro0->param2 - parametro0->column) / 4;
            parametro0->d_8018DEE0_indice += 1;
            parametro0->paramf = ((parametro0->d_8018DEE0_indice - 0xA) * 0.0085 * (parametro0->d_8018DEE0_indice - 0xA)) + 0.4;
            if ((parametro0->d_8018DEE0_indice >= 9) && ((f64) parametro0->paramf > 1)) {
                parametro0->paramf = 1.0f;
                parametro0->state = 3;
            }
            break;
        case 3:
            if ((u8) dato_8018ED91 != 0) {
                parametro0->state = 4;
            }
            break;
        case 4:
            funcion_800A94C8(parametro0, parametro0->param2, 1);
            if (parametro0->row > 480.0) {
                parametro0->type = 0;
            }
            break;
        default:
            break;
    }
}

void funcion_800AF740(MenuItem* parametro0) {
    SIN_USO s32 relleno;
    s32 temporal_v0;
    InfoRenderCreditos* temporal_v1;

    temporal_v0 = parametro0->type - 0x190;
    temporal_v1 = &creditos_texto_render_info[temporal_v0];
    parametro0->row = temporal_v1->row;
    switch (parametro0->state) {
        case 0:
            parametro0->column = temporal_v1->columna_inicial;
            parametro0->state = 1;
            parametro0->param2 = temporal_v1->extra_columna - (obtener_ancho_cadena(texto_creditos[temporal_v0]) * temporal_v1->escalado_texto / 2);
        case 1:
            funcion_800A9208(parametro0, parametro0->param2);
            parametro0->param1 = (s32) (parametro0->column - parametro0->param2) / 4;
            if (parametro0->param1 >= 9) {
                parametro0->param1 = 8;
            }
            parametro0->paramf = (parametro0->param1 * 0.05) + 1.0;
            if ((parametro0->param2 + 0x14) >= parametro0->column) {
                parametro0->state = 2;
                parametro0->d_8018DEE0_indice = 0;
            }
            break;
        case 2:
            funcion_800A9208(parametro0, parametro0->param2);
            parametro0->param1 = (parametro0->column - parametro0->param2) / 4;
            parametro0->d_8018DEE0_indice += 1;
            parametro0->paramf = ((parametro0->d_8018DEE0_indice - 0xA) * 0.0085 * (parametro0->d_8018DEE0_indice - 0xA)) + 0.4;
            if ((parametro0->d_8018DEE0_indice >= 9) && ((f64) parametro0->paramf > 1)) {
                parametro0->paramf = 1.0f;
                parametro0->state = 3;
            }
            break;
        case 3:
            if ((u8) dato_8018ED91 != 0) {
                parametro0->state = 4;
            }
            break;
        case 4:
            funcion_800A94C8(parametro0, parametro0->param2, -1);
            if (parametro0->row > 480.0) {
                parametro0->type = 0;
            }
            break;
        default:
            break;
    }
}
