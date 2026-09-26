// Dibujar kart y sombra

void funcion_80022A98(Jugador* jugador, s8 indice_jugador) {
    if ((jugador->type & EXISTE_JUGADOR) == EXISTE_JUGADOR) {
        funcion_80026A48(jugador, indice_jugador);
        funcion_800235AC(jugador, indice_jugador);
        if (((jugador->efectos & EFECTO_APLASTAMIENTO) == EFECTO_APLASTAMIENTO) ||
            ((jugador->efectos & EFECTO_APLASTAMIENTO_PUBLICAR) == EFECTO_APLASTAMIENTO_PUBLICAR)) {
            if ((jugador->efectos & EFECTO_APLASTAMIENTO) == EFECTO_APLASTAMIENTO) {
                funcion_80022B50(jugador, indice_jugador);
            }
            if ((jugador->efectos & EFECTO_APLASTAMIENTO_PUBLICAR) == EFECTO_APLASTAMIENTO_PUBLICAR) {
                funcion_80022BC4(jugador, indice_jugador);
            }
        } else {
            funcion_80022DB4(jugador, indice_jugador);
        }
        funcion_80030A34(jugador);
    }
}

void funcion_80022B50(Jugador* jugador, SIN_USO s8 indice_jugador) {
    f32 temporal_f0;
    s16 variable_v0;

    variable_v0 = jugador->desconocido_DB4.desconocido2;
    temporal_f0 = jugador->desconocido_DB4.unk10;
    if (variable_v0 < 5) {
        variable_v0++;
    }

    jugador->desconocido_DA4 = (variable_v0 * temporal_f0) - (0.7 * (variable_v0 * variable_v0));
    jugador->desconocido_DB4.unk10 = temporal_f0;
    jugador->desconocido_DB4.desconocido2 = variable_v0;
}

void funcion_80022BC4(Jugador* jugador, SIN_USO s8 indice_jugador) {
    f32 temporal_f0 = jugador->desconocido_DB4.unk10;
    s16 temporal_v0 = jugador->desconocido_DB4.desconocido2;
    s16 temporal_f16;

    temporal_v0++;

    temporal_f16 = (temporal_v0 * temporal_f0) - (0.5 * (temporal_v0 * temporal_v0));

    if ((temporal_v0 != 0) && (temporal_f16 < 0)) {
        temporal_f0 *= 0.8;
        temporal_v0 = 0;
        if (temporal_f0 <= 0.1) {
            jugador->efectos &= ~EFECTO_APLASTAMIENTO_PUBLICAR;
            temporal_f0 = 0.0f;
        }
    }
    if (temporal_f16 <= 0) {
        temporal_f16 = 0;
    }
    jugador->desconocido_DA4 = temporal_f16;
    jugador->desconocido_DB4.unk10 = temporal_f0;
    jugador->desconocido_DB4.desconocido2 = temporal_v0;
}

void funcion_80022CA8(Jugador* jugador, s8 id_jugador, SIN_USO s8 id_pantalla, s8 voltear_desplazamiento) {
    s16 temporal_v0 = jugador->desconocido_DA4;

    vtx_jugador[id_jugador][voltear_desplazamiento + 0x0].v.ob[1] = 18 - (temporal_v0 * 2.3);
    vtx_jugador[id_jugador][voltear_desplazamiento + 0x1].v.ob[1] = 9 - temporal_v0;
    vtx_jugador[id_jugador][voltear_desplazamiento + 0x2].v.ob[1] = 9 - temporal_v0;
    vtx_jugador[id_jugador][voltear_desplazamiento + 0x3].v.ob[1] = 18 - (temporal_v0 * 2.3);
    vtx_jugador[id_jugador][voltear_desplazamiento + 0x4].v.ob[1] = 9 - temporal_v0;
    vtx_jugador[id_jugador][voltear_desplazamiento + 0x7].v.ob[1] = 9 - temporal_v0;
}

void funcion_80022D60(SIN_USO Jugador* jugador, s8 id_jugador, SIN_USO s8 id_pantalla, s8 voltear_desplazamiento) {
    vtx_jugador[id_jugador][voltear_desplazamiento].v.ob[1] = 21;
    vtx_jugador[id_jugador][voltear_desplazamiento + 0x3].v.ob[1] = 21;
}

void funcion_80022DB4(Jugador* jugador, SIN_USO s8 indice_jugador) {
    f32 temporal_f0 = jugador->desconocido_DB4.desconocido_c;
    s16 temporal_v0 = jugador->desconocido_DB4.unk18;
    s16 temporal_f16;

    temporal_v0++;

    temporal_f16 = (temporal_v0 * temporal_f0) - (0.7 * (temporal_v0 * temporal_v0));

    if ((temporal_v0 != 0) && (temporal_f16 < 0)) {
        temporal_f0 *= 0.8;
        temporal_v0 = 0;
        if (temporal_f0 <= 0.1) {
            temporal_f0 = 0.0f;
        }
    }
    if (temporal_f16 <= 0) {
        temporal_f16 = 0;
    }
    jugador->desconocido_DB4.desconocido_1e = temporal_f16;
    jugador->desconocido_DB4.desconocido_c = temporal_f0;
    jugador->desconocido_DB4.unk18 = temporal_v0;
}

void funcion_80022E84(Jugador* jugador, s8 id_jugador, SIN_USO s8 id_pantalla, s8 voltear_desplazamiento) {
    s16 temporal_v0 = jugador->desconocido_DB4.desconocido_1e;

    vtx_jugador[id_jugador][voltear_desplazamiento + 0x0].v.ob[1] = 18 - temporal_v0;
    vtx_jugador[id_jugador][voltear_desplazamiento + 0x1].v.ob[1] = 9 - temporal_v0;
    vtx_jugador[id_jugador][voltear_desplazamiento + 0x2].v.ob[1] = 9 - temporal_v0;
    vtx_jugador[id_jugador][voltear_desplazamiento + 0x3].v.ob[1] = 18 - temporal_v0;
    vtx_jugador[id_jugador][voltear_desplazamiento + 0x4].v.ob[1] = 9 - temporal_v0;
    vtx_jugador[id_jugador][voltear_desplazamiento + 0x7].v.ob[1] = 9 - temporal_v0;
}

void cambiar_efecto_rgb_color_jugador(SIN_USO Jugador* jugador, s8 indice_jugador, s32 parametro2, f32 alpha) {
    efecto_rojo_jugador[indice_jugador] =
        (s16) ((f32) efecto_rojo_jugador[indice_jugador] - ((efecto_rojo_jugador[indice_jugador] - ((parametro2 >> 16) & 0xFF)) * alpha));

    efecto_verde_jugador[indice_jugador] =
        (s16) ((f32) efecto_verde_jugador[indice_jugador] - ((efecto_verde_jugador[indice_jugador] - ((parametro2 >> 8) & 0xFF)) * alpha));

    efecto_azul_jugador[indice_jugador] =
        (s16) ((f32) efecto_azul_jugador[indice_jugador] - ((efecto_azul_jugador[indice_jugador] - (parametro2 & 0xFF)) * alpha));
}

void cambiar_jugador_color_efecto_cmy(SIN_USO Jugador* jugador, s8 indice_jugador, s32 parametro2, f32 parametro3) {
    mover_u16_hacia(&efecto_cian_jugador[indice_jugador], (parametro2 >> 16) & 0xFF, parametro3);
    mover_u16_hacia(&efecto_magenta_jugador[indice_jugador], (parametro2 >> 8) & 0xFF, parametro3);
    mover_u16_hacia(&efecto_amarillo_jugador[indice_jugador], parametro2 & 0xFF, parametro3);
}

bool es_jugador_bajo_luz_luigi_raceway(Jugador* jugador, s8 indice_jugador) {
    switch (id_circuito_actual) {
        case CIRCUITO_LUIGI_RACEWAY:
            if (((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x14F) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x158)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x15E) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x164)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x169) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x170)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x174) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x17A)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x17E) &&
                 (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x184))) {
                cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, LUZ_COLOR, 0.3f);
                cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0xE0, 0.3f);
                dato_80164B80[indice_jugador] = 0;
                return true;
            }
            return false;

        default:
            return false;
    }
}

void renderizar_ambiente_luz_en_jugador(Jugador* jugador, s8 indice_jugador) {
    switch (id_circuito_actual) {
        case CIRCUITO_BOWSER_CASTLE:
            if (((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x15) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x2A)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x14D) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x15C)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x1D1) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x1E4)) ||
                (jugador->colision.distancia_superficie[2] >= 500.0f)) { // over lava
                cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, COLOR_LAVA, 0.3f);
                cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0x004040, 0.3f);
                dato_80164B80[indice_jugador] = 0;
            } else if (((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0xF1) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0xF5)) ||
                       ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0xFB) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0xFF)) ||
                       ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x105) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x109)) ||
                       ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x10F) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x113)) ||
                       ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x145) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x14A)) ||
                       ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x15E) &&
                        (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x163))) {
                cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, LUZ_COLOR, 0.3f);
                cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0xE0, 0.3f);
                dato_80164B80[indice_jugador] = 0;
            } else {
                cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, NEGRO_COLOR, 0.3f);
                cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0, 0.3f);
                dato_80164B80[indice_jugador] = 0;
            }
            break;
        case CIRCUITO_BANSHEE_BOARDWALK:
            if (((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0xD) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x15)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x29) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x39)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x46) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x4E)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x5F) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x67)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x7B) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x86)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x9D) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0xA6)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0xB9) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0xC3)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0xB9) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0xC3)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0xD7) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0xE1)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x10E) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x119)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x154) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x15F)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x1EF) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x1F7)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x202) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x209)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x216) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x21D)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x230) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x23A)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x24C) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x256)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x288) && (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x269)) ||
                ((punto_camino_mas_cercano_por_id_jugador[indice_jugador] >= 0x274) &&
                 (punto_camino_mas_cercano_por_id_jugador[indice_jugador] < 0x27E))) {
                cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, LUZ_COLOR, 0.3f);
                cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0x0000E0, 0.3f);
                dato_80164B80[indice_jugador] = 0;
            } else {
                cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, NEGRO_COLOR, 0.3f);
                cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0, 0.3f);
                dato_80164B80[indice_jugador] = 0;
            }
            break;
        default:
            cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, NEGRO_COLOR, 0.3f);
            cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0, 0.3f);
            dato_80164B80[indice_jugador] = 0;
            break;
    }
}

void funcion_800235AC(Jugador* jugador, s8 indice_jugador) {
    s32 tiempo_transcurrido;

    if (((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) == INVISIBLE_JUGADOR_O_BOMBA) && (jugador == jugador_tres)) {
        cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, LUZ_COLOR, 0.3f);
        cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0xE0, 0.3f);
        dato_80164B80[indice_jugador] = 0;
        return;
    }

    if (((jugador->lakitu_props & EFECTO_HELADO) == EFECTO_HELADO) &&
        ((jugador->lakitu_props & LAKITU_APAGAR) == LAKITU_APAGAR)) {
        cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, 0x646464, 0.5f);
        cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0xFF0000, 0.1f);
        return;
    }
    if ((jugador->lakitu_props & LAKITU_APAGAR) == LAKITU_APAGAR) {
        cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, NEGRO_COLOR, 1.0f);
        cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0, 1.0f);
        return;
    }
    if ((jugador->lakitu_props & EFECTO_HELADO) == EFECTO_HELADO) {
        cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, 0x646464, 0.5f);
        cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0xFF0000, 0.1f);
        return;
    }
    if ((jugador->lakitu_props & EFECTO_DESHIELO) == EFECTO_DESHIELO) {
        cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, NEGRO_COLOR, 0.1f);
        cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0, 0.1f);
        return;
    }

    if (((jugador->efectos & EFECTO_RAYO) == EFECTO_RAYO) && ((s32) jugador->desconocido_0B0 < 0x78)) {
        dato_80164B80[indice_jugador] += 5;
        if (dato_80164B80[indice_jugador] >= 0x1E) {
            dato_80164B80[indice_jugador] = 0;
        }
        if ((dato_80164B80[indice_jugador] >= 0) && (dato_80164B80[indice_jugador] < 0xB)) {
            cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, 0x808080, 0.8f);
            cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0, 0.8f);
        }
        if ((dato_80164B80[indice_jugador] >= 0xB) && (dato_80164B80[indice_jugador] < 0x15)) {
            cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, 0x70, 0.8f);
            cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0, 0.8f);
        }
        if ((dato_80164B80[indice_jugador] >= 0x15) && (dato_80164B80[indice_jugador] < 0x1F)) {
            cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, 0x8F8F00, 0.8f);
            cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0, 0.8f);
        }
        return;
    }
    if ((jugador->efectos & EFECTO_ESTRELLA) != 0) {
        tiempo_transcurrido = (s32) temporizador_circuito - jugador_estrella_efecto_inicio_tiempo[indice_jugador];
        if (tiempo_transcurrido <= 8) {

            if (tiempo_transcurrido >= 7) {
                dato_80164B80[indice_jugador] += 10;
            } else {
                dato_80164B80[indice_jugador] += 5;
            }
            if (dato_80164B80[indice_jugador] >= 40) {
                dato_80164B80[indice_jugador] = 0;
            }
            if ((dato_80164B80[indice_jugador] >= 0) && (dato_80164B80[indice_jugador] <= 10)) {
                cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, 0x70, 0.8f);
                cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0, 0.8f);
            }
            if ((dato_80164B80[indice_jugador] >= 0xB) && (dato_80164B80[indice_jugador] <= 20)) {
                cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, 0x707000, 0.8f);
                cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0, 0.8f);
            }
            if ((dato_80164B80[indice_jugador] >= 0x15) && (dato_80164B80[indice_jugador] <= 30)) {
                cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, 0x700000, 0.8f);
                cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0, 0.8f);
            }
            if (dato_80164B80[indice_jugador] >= 0x1F) {
                cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, 0x7000, 0.8f);
                cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0, 0.8f);
            }
            return;
        }
    }
    if (es_jugador_bajo_luz_luigi_raceway(jugador, indice_jugador) != true) {
        if (((jugador->ruedas[DERECHA_ATRAS].desconocido_14 & 1) == 1) || ((jugador->ruedas[DERECHA_ATRAS].desconocido_14 & 2) == 2) ||
            ((jugador->ruedas[IZQUIERDA_FRENTE].desconocido_14 & 3) == 3)) {
            cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, NEGRO_COLOR, 0.3f);
            cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0x6F6F6F, 0.3f);
            return;
        }
        renderizar_ambiente_luz_en_jugador(jugador, indice_jugador);
        if ((jugador->lakitu_props & LAKITU_LAVA) == LAKITU_LAVA) {
            cambiar_efecto_rgb_color_jugador(jugador, indice_jugador, NEGRO_COLOR, 0.3f);
            cambiar_jugador_color_efecto_cmy(jugador, indice_jugador, 0xF0F0F0, 0.3f);
        }
    }
}

void funcion_80023BF0(Jugador* jugador, s8 id_jugador, s8 id_pantalla, s8 parametro3) {
    if (((jugador->efectos & EFECTO_APLASTAMIENTO) == EFECTO_APLASTAMIENTO) ||
        ((jugador->efectos & EFECTO_APLASTAMIENTO_PUBLICAR) == EFECTO_APLASTAMIENTO_PUBLICAR)) {
        funcion_80022CA8(jugador, id_jugador, id_pantalla, parametro3);
    } else {
        funcion_80022E84(jugador, id_jugador, id_pantalla, parametro3);
    }
    if ((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == MANTENIDO_POR_LAKITU) {
        funcion_80022D60(jugador, id_jugador, id_pantalla, parametro3);
    }
}

void renderizar_sombra_jugador(Jugador* jugador, s8 id_jugador, s8 id_pantalla) {
    Mat4 sp118;
    SIN_USO Mat4 relleno;
    Vec3f sp_cc;
    Vec3s sp_c4;
    s16 temporal_t9;
    s16 sp_c0;
    Vec3f sp_b4;
    f32 sp_b0;
    f32 sp_ac;
    SIN_USO Vec3f relleno2;
    f32 variable_f2;

    temporal_t9 = (u16) (jugador->desconocido_048[id_pantalla] + jugador->rotacion[1] + jugador->desconocido_0C0) / 128;
    sp_c0 = -jugador->rotacion[1] - jugador->desconocido_0C0;

    sp_b0 = -coss(temporal_t9 << 7) * 2;
    sp_ac = -senos(temporal_t9 << 7) * 2;

    if (((jugador->efectos & EFECTO_ERROR_EXPLOSION) == EFECTO_ERROR_EXPLOSION) ||
        ((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) == GOLPE_POR_CAPARAZON_VERDE_EFECTO) ||
        ((jugador->efectos & desconocido_efecto_0_x_80000) == desconocido_efecto_0_x_80000) ||
        ((jugador->efectos & desconocido_efecto_0_x_800000) == desconocido_efecto_0_x_800000) ||
        ((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) == GOLPE_POR_CAPARAZON_VERDE_EFECTO) ||
        ((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == MANTENIDO_POR_LAKITU) ||
        ((jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA) == GOLPE_POR_EFECTO_ESTRELLA) ||
        ((jugador->efectos & EFECTO_VUELCO_TERRENO) == EFECTO_VUELCO_TERRENO) ||
        ((jugador->efectos & EFECTO_EN_EL_AIRE) == EFECTO_EN_EL_AIRE)) {

        variable_f2 = (f32) (1.0 - ((f64) jugador->colision.distancia_superficie[2] * 0.02));
        if (variable_f2 < 0.0f) {
            variable_f2 = 0.0f;
        }
        if (variable_f2 > 1.0f) {
            variable_f2 = 1.0f;
        }
        sp_b4[0] = jugador->colision.vector_orientacion[0];
        sp_b4[2] = jugador->colision.vector_orientacion[2];
        sp_b4[1] = jugador->colision.vector_orientacion[1];

        sp_cc[0] = jugador->pos[0] + ((sp_b0 * senos(sp_c0)) + (sp_ac * coss(sp_c0)));
        sp_cc[1] = jugador->desconocido_074 + 1.0f;
        sp_cc[2] = jugador->pos[2] + ((sp_b0 * coss(sp_c0)) - (sp_ac * senos(sp_c0)));
        transformar_matriz_conjunto(sp118, sp_b4, sp_cc, (sp_c0 + jugador->desconocido_042),
                             tamanio_personaje[jugador->id_personaje] * jugador->size * variable_f2);
    } else {
        sp_c4[0] = jugador->acel_pendiente;
        sp_c4[1] = sp_c0;
        sp_c4[2] = jugador->desconocido_206 * 2;

        sp_cc[0] = jugador->pos[0] + ((sp_b0 * senos(sp_c0)) + (sp_ac * coss(sp_c0)));
        sp_cc[1] = jugador->desconocido_074 + 1.0f;
        sp_cc[2] = jugador->pos[2] + ((sp_b0 * coss(sp_c0)) - (sp_ac * senos(sp_c0)));
        trasladar_rotacion_mtxf(sp118, sp_cc, sp_c4);
        escala2_mtxf(sp118, tamanio_personaje[jugador->id_personaje] * jugador->size);
    }
    convertir_a_matriz_punto_fijo(&gfx_pool->sombra_mtx[id_jugador + (id_pantalla * 8)], sp118);

    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->sombra_mtx[id_jugador + (id_pantalla * 8)]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(display_list_cabeza++, dato_0D008D58);
    gDPSetTextureLUT(display_list_cabeza++, G_TT_NONE);
    gDPLoadTextureBlock(display_list_cabeza++, cargado_textura_kart_sombra, G_IM_FMT_I, G_IM_SIZ_8b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    funcion_8004B414(0, 0, 0, 0xFF);
    gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
    gSPVertex(display_list_cabeza++, &dato_800E51D0[0], 4, 0);

    gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
    gDPLoadTextureBlock(display_list_cabeza++, (cargado_textura_kart_sombra + ALGUN_MATEMATICA_PUNTERO_TEXTURA), G_IM_FMT_I,
                        G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                        G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    funcion_8004B414(0, 0, 0, 0xFF);
    gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
    gSPVertex(display_list_cabeza++, &dato_800E5210[0], 4, 0);

    gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void renderizar_creditos_sombra_jugador(Jugador* jugador, s8 id_jugador, s8 parametro2) {
    Mat4 sp118;
    SIN_USO Mat4 relleno;
    Vec3f sp_cc;
    Vec3s sp_c4;
    s16 temporal_t9;
    s16 sp_c0;
    SIN_USO Vec3f relleno2;
    f32 sp_b0;
    f32 sp_ac;
    SIN_USO Vec3f relleno3;
    Vec3f sp94 = { 9.0f, 7.0f, 5.0f };

    temporal_t9 = (u16) (jugador->desconocido_048[parametro2] + jugador->rotacion[1] + jugador->desconocido_0C0) / 128;
    sp_c0 = -jugador->rotacion[1] - jugador->desconocido_0C0;

    sp_b0 = -coss(temporal_t9 << 7) * 3;
    sp_ac = -senos(temporal_t9 << 7) * 3;

    sp_c4[0] = 0;
    sp_c4[1] = sp_c0;
    sp_c4[2] = 0;

    sp_cc[0] = jugador->pos[0] + ((sp_b0 * senos(sp_c0)) + (sp_ac * coss(sp_c0)));
    sp_cc[2] = jugador->pos[2] + ((sp_b0 * coss(sp_c0)) - (sp_ac * senos(sp_c0)));
    sp_cc[1] = lista_objeto[lista_objeto_indice_1[id_jugador]].pos[1] + sp94[id_jugador];

    trasladar_rotacion_mtxf(sp118, sp_cc, sp_c4);
    escala2_mtxf(sp118, tamanio_personaje[jugador->id_personaje] * jugador->size);
    convertir_a_matriz_punto_fijo(&gfx_pool->sombra_mtx[id_jugador + (parametro2 * 8)], sp118);

    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->sombra_mtx[id_jugador + (parametro2 * 8)]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(display_list_cabeza++, dato_0D008D58);
    gDPSetTextureLUT(display_list_cabeza++, G_TT_NONE);
    gDPLoadTextureBlock(display_list_cabeza++, cargado_textura_kart_sombra, G_IM_FMT_I, G_IM_SIZ_8b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    funcion_8004B414(0, 0, 0, 0x000000D0);
    gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
    gSPVertex(display_list_cabeza++, &dato_800E51D0[0], 4, 0);

    gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
    gDPLoadTextureBlock(display_list_cabeza++, (cargado_textura_kart_sombra + ALGUN_MATEMATICA_PUNTERO_TEXTURA), G_IM_FMT_I,
                        G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                        G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    funcion_8004B414(0, 0, 0, 0x000000D0);
    gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
    gSPVertex(display_list_cabeza++, &dato_800E5210[0], 4, 0);

    gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void renderizar_kart(Jugador* jugador, s8 id_jugador, s8 parametro2, s8 voltear_desplazamiento) {
    SIN_USO s32 relleno;
    Mat4 sp1_a4;
    SIN_USO s32 relleno2[17];
    Vec3f sp154;
    Vec3s sp14_c;
    f32 sp148;
    f32 sp144;
    f32 sp140;
    s16 temporal_v1;
    s16 cosa;

    if (jugador->kart_props & sin_uso_0_x_2000) {
        sp14_c[0] = 0;
        sp14_c[1] = jugador->desconocido_048[parametro2];
        sp14_c[2] = 0;
        funcion_80062B18(&sp148, &sp144, &sp140, 0.0f, 1.5f, 0.0f, -jugador->desconocido_048[parametro2], jugador->desconocido_050[parametro2]);
        sp154[1] = (jugador->pos[1] - jugador->tamanio_caja_envolvente) + (sp144 - 2.0);
        sp154[0] = jugador->pos[0] + sp148;
        sp154[2] = jugador->pos[2] + sp140;
    } else {
        cosa = (u16) (jugador->desconocido_048[parametro2] + jugador->rotacion[1] + jugador->desconocido_0C0);
        temporal_v1 = jugador->desconocido_0CC[parametro2] * senos(cosa);
        if ((jugador->efectos & EFECTO_EN_EL_AIRE) == EFECTO_EN_EL_AIRE) {
            sp14_c[0] = camaras[parametro2].rot[0] - GRADOS(90);
        } else {
            sp14_c[0] = -temporal_v1 * 0.8;
        }
        sp14_c[1] = jugador->desconocido_048[parametro2];
        sp14_c[2] = jugador->desconocido_050[parametro2];
        if (((s32) jugador->efectos & EFECTO_APLASTAMIENTO) == EFECTO_APLASTAMIENTO) {
            funcion_80062B18(&sp148, &sp144, &sp140, 0.0f, 8.0f, 0.0f, -jugador->desconocido_048[parametro2], jugador->desconocido_050[parametro2]);
            sp154[1] = (jugador->pos[1] - jugador->tamanio_caja_envolvente) + jugador->desconocido_108;
            sp154[0] = jugador->pos[0] + sp148;
            sp154[2] = jugador->pos[2] + sp140;
        } else {
            funcion_80062B18(&sp148, &sp144, &sp140, 0.0f, 1.5f, 0.0f, -jugador->desconocido_048[parametro2], jugador->desconocido_050[parametro2]);
            sp154[1] = (jugador->pos[1] - jugador->tamanio_caja_envolvente) + jugador->desconocido_108 + (sp144 - 2.0);
            sp154[0] = jugador->pos[0] + sp148;
            sp154[2] = jugador->pos[2] + sp140;
        }
    }
#ifdef AVOID_UB
    paleta_jugador = &lista_paletas_jugador[dato_801651D0[parametro2][id_jugador]][parametro2][id_jugador];
#else
    paleta_jugador = (struct_d_802F1F80*) &lista_paletas_jugador[dato_801651D0[parametro2][id_jugador]][parametro2][id_jugador * 0x100];
#endif
    if ((parametro2 == 0) || (parametro2 == 1)) {
        textura_superior_kart = &dato_802BFB80.tamanio_arreglo_8[dato_801651D0[parametro2][id_jugador]][parametro2][id_jugador].arreglo_indice_pixel[0];
        textura_inferior_kart = &dato_802BFB80.tamanio_arreglo_8[dato_801651D0[parametro2][id_jugador]][parametro2][id_jugador].arreglo_indice_pixel[0x7C0];
    } else {
        textura_superior_kart =
            &dato_802BFB80.tamanio_arreglo_8[dato_801651D0[parametro2][id_jugador]][parametro2 - 1][id_jugador - 4].arreglo_indice_pixel[0];
        textura_inferior_kart =
            &dato_802BFB80.tamanio_arreglo_8[dato_801651D0[parametro2][id_jugador]][parametro2 - 1][id_jugador - 4].arreglo_indice_pixel[0x7C0];
    }
    trasladar_rotacion_mtxf(sp1_a4, sp154, sp14_c);
    escala2_mtxf(sp1_a4, tamanio_personaje[jugador->id_personaje] * jugador->size);
    convertir_a_matriz_punto_fijo(&gfx_pool->mtx_kart[id_jugador + (parametro2 * 8)], sp1_a4);

    if ((jugador->efectos & BOO_EFECTO) == BOO_EFECTO) {
        if (parametro2 == id_jugador) {
            gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_kart[id_jugador + (parametro2 * 8)]),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(display_list_cabeza++, renderizar_personaje_ajuste_comun);
            gDPLoadTLUT_pal256(display_list_cabeza++, paleta_jugador);
            gDPSetTextureLUT(display_list_cabeza++, G_TT_RGBA16);
            funcion_8004B614(efecto_rojo_jugador[id_jugador], efecto_verde_jugador[id_jugador], efecto_azul_jugador[id_jugador],
                          efecto_cian_jugador[id_jugador], efecto_magenta_jugador[id_jugador], efecto_amarillo_jugador[id_jugador],
                          (s32) jugador->alpha);
            gDPSetRenderMode(display_list_cabeza++,
                             AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL |
                                 GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA),
                             AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL |
                                 GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));
        } else {
            gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_kart[id_jugador + (parametro2 * 8)]),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(display_list_cabeza++, renderizar_personaje_ajuste_comun);
            gDPLoadTLUT_pal256(display_list_cabeza++, paleta_jugador);
            gDPSetTextureLUT(display_list_cabeza++, G_TT_RGBA16);
            funcion_8004B614(efecto_rojo_jugador[id_jugador], efecto_verde_jugador[id_jugador], efecto_azul_jugador[id_jugador],
                          efecto_cian_jugador[id_jugador], efecto_magenta_jugador[id_jugador], efecto_amarillo_jugador[id_jugador],
                          jugador_otro_pantallas_alpha[id_jugador]);
            gDPSetRenderMode(display_list_cabeza++,
                             AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL |
                                 GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA),
                             AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL |
                                 GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));
        }
    } else if (((jugador->lakitu_props & LAKITU_APAGAR) == LAKITU_APAGAR) || (jugador->disparadores & EFECTO_BOMBA_VOLVERSE) ||
               (jugador->disparadores & EFECTO_BATALLA_PERDER)) {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_kart[id_jugador + (parametro2 * 8)]),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(display_list_cabeza++, renderizar_personaje_ajuste_comun);
        gDPLoadTLUT_pal256(display_list_cabeza++, paleta_jugador);
        gDPSetTextureLUT(display_list_cabeza++, G_TT_RGBA16);
        funcion_8004B614(efecto_rojo_jugador[id_jugador], efecto_verde_jugador[id_jugador], efecto_azul_jugador[id_jugador],
                      efecto_cian_jugador[id_jugador], efecto_magenta_jugador[id_jugador], efecto_amarillo_jugador[id_jugador],
                      (s32) jugador->alpha);
        gDPSetAlphaCompare(display_list_cabeza++, G_AC_DITHER);
        gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2);
    } else {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_kart[id_jugador + (parametro2 * 8)]),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(display_list_cabeza++, renderizar_personaje_ajuste_comun);
        gDPLoadTLUT_pal256(display_list_cabeza++, paleta_jugador);
        gDPSetTextureLUT(display_list_cabeza++, G_TT_RGBA16);
        funcion_8004B614(efecto_rojo_jugador[id_jugador], efecto_verde_jugador[id_jugador], efecto_azul_jugador[id_jugador],
                      efecto_cian_jugador[id_jugador], efecto_magenta_jugador[id_jugador], efecto_amarillo_jugador[id_jugador],
                      (s32) jugador->alpha);
        gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    }

    gDPLoadTextureBlock(display_list_cabeza++, textura_superior_kart, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPVertex(display_list_cabeza++, &vtx_jugador[id_jugador][voltear_desplazamiento], 4, 0);
    gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);

    gDPLoadTextureBlock(display_list_cabeza++, textura_inferior_kart, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPVertex(display_list_cabeza++, &vtx_jugador[id_jugador][voltear_desplazamiento + 4], 4, 0);
    gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
    gDPSetAlphaCompare(display_list_cabeza++, G_AC_NONE);
}

void renderizar_fantasma(Jugador* jugador, s8 id_jugador, s8 id_pantalla, s8 voltear_desplazamiento) {
    SIN_USO s32 relleno;
    Mat4 sp12_c;
    SIN_USO s32 relleno2[17];
    Vec3f sp_dc;
    Vec3s sp_d4;
    f32 sp_d0;
    f32 sp_cc;
    f32 sp_c8;
    SIN_USO s32 relleno3;
    s16 sp_c2;
    s16 cosa;

    if (id_pantalla) {}
    if (dato_8015F890 == 1) {
        sp_c2 = 0x00FF;
    } else {
        sp_c2 = 0x0070;
    }
    cosa = (u16) (jugador->desconocido_048[id_pantalla] - jugador->rotacion[1]);
    sp_d4[0] = (-(s16) (senos(cosa) * (0.0f * 0.0f)) * 0.8);
    sp_d4[1] = jugador->desconocido_048[id_pantalla];
    sp_d4[2] = jugador->desconocido_050[id_pantalla];
    funcion_80062B18(&sp_d0, &sp_cc, &sp_c8, 0, 1.5f, 0, -jugador->desconocido_048[id_pantalla], jugador->desconocido_050[id_pantalla]);
    sp_dc[1] = (jugador->pos[1] - jugador->tamanio_caja_envolvente) + (sp_cc - 2.0);
    sp_dc[0] = jugador->pos[0] + sp_d0;
    sp_dc[2] = jugador->pos[2] + sp_c8;
#ifdef AVOID_UB
    paleta_jugador = &lista_paletas_jugador[dato_801651D0[id_pantalla][id_jugador]][id_pantalla][id_jugador];
#else
    paleta_jugador =
        (struct_d_802F1F80*) &lista_paletas_jugador[dato_801651D0[id_pantalla][id_jugador]][id_pantalla][id_jugador * 0x100];
#endif
    if ((id_pantalla == 0) || (id_pantalla == 1)) {
        textura_superior_kart =
            &dato_802BFB80.tamanio_arreglo_8[dato_801651D0[id_pantalla][id_jugador]][id_pantalla][id_jugador].arreglo_indice_pixel[0];
        textura_inferior_kart =
            &dato_802BFB80.tamanio_arreglo_8[dato_801651D0[id_pantalla][id_jugador]][id_pantalla][id_jugador].arreglo_indice_pixel[0x7C0];
    } else {
        textura_superior_kart =
            &dato_802BFB80.tamanio_arreglo_8[dato_801651D0[id_pantalla][id_jugador]][id_pantalla - 1][id_jugador - 4].arreglo_indice_pixel[0];
        textura_inferior_kart =
            &dato_802BFB80.tamanio_arreglo_8[dato_801651D0[id_pantalla][id_jugador]][id_pantalla - 1][id_jugador - 4].arreglo_indice_pixel[0x7C0];
    }

    trasladar_rotacion_mtxf(sp12_c, sp_dc, sp_d4);
    escala2_mtxf(sp12_c, tamanio_personaje[jugador->id_personaje] * jugador->size);
    convertir_a_matriz_punto_fijo(&gfx_pool->mtx_kart[id_jugador + (id_pantalla * 8)], sp12_c);

    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_kart[id_jugador + (id_pantalla * 8)]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(display_list_cabeza++, renderizar_personaje_ajuste_comun);
    gDPLoadTLUT_pal256(display_list_cabeza++, paleta_jugador);
    gDPSetTextureLUT(display_list_cabeza++, G_TT_RGBA16);
    funcion_8004B614(efecto_rojo_jugador[id_jugador], efecto_verde_jugador[id_jugador], efecto_azul_jugador[id_jugador],
                  efecto_cian_jugador[id_jugador], efecto_magenta_jugador[id_jugador], efecto_amarillo_jugador[id_jugador], sp_c2);
    gDPSetRenderMode(display_list_cabeza++,
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL |
                         GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA),
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL |
                         GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));

    gDPLoadTextureBlock(display_list_cabeza++, textura_superior_kart, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPVertex(display_list_cabeza++, &vtx_jugador[id_jugador][voltear_desplazamiento], 4, 0);
    gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);

    gDPLoadTextureBlock(display_list_cabeza++, textura_inferior_kart, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPVertex(display_list_cabeza++, &vtx_jugador[id_jugador][voltear_desplazamiento + 4], 4, 0);
    gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
    gDPSetAlphaCompare(display_list_cabeza++, G_AC_NONE);
}

void funcion_80025DE8(Jugador* jugador, s8 id_jugador, s8 id_pantalla, s8 voltear_desplazamiento) {
    Mat4 sp_a8;
    Vec3f sp9_c;
    Vec3s sp94;

    sp9_c[0] = jugador->pos[0] + (senos(-jugador->rotacion[1]) * -1.5);
    sp9_c[1] = ((jugador->pos[1] - jugador->tamanio_caja_envolvente) + jugador->desconocido_108) + 0.1;
    sp9_c[2] = jugador->pos[2] + (coss(-jugador->rotacion[1]) * -1.5);
    sp94[0] = -GRADOS(1);
    sp94[1] = jugador->desconocido_048[id_pantalla];
    sp94[2] = jugador->desconocido_050[id_pantalla];

    trasladar_rotacion_mtxf(sp_a8, sp9_c, sp94);
    escala2_mtxf(sp_a8, tamanio_personaje[jugador->id_personaje] * jugador->size);
    convertir_a_matriz_punto_fijo(&gfx_pool->efecto_mtx[cantidad_efecto_matriz], sp_a8);

    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->efecto_mtx[cantidad_efecto_matriz]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(display_list_cabeza++, dato_0D008D10);
    gDPSetTextureLUT(display_list_cabeza++, G_TT_RGBA16);
    funcion_8004B614(efecto_rojo_jugador[id_jugador], efecto_verde_jugador[id_jugador], efecto_azul_jugador[id_jugador],
                  efecto_cian_jugador[id_jugador], efecto_magenta_jugador[id_jugador], efecto_amarillo_jugador[id_jugador],
                  0x00000040);
    gDPSetRenderMode(display_list_cabeza++,
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL |
                         GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA),
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL |
                         GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));

    gDPLoadTextureBlock(display_list_cabeza++, textura_superior_kart, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPVertex(display_list_cabeza++, &vtx_jugador[id_jugador][voltear_desplazamiento], 4, 0);
    gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);

    gDPLoadTextureBlock(display_list_cabeza++, textura_inferior_kart, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPVertex(display_list_cabeza++, &vtx_jugador[id_jugador][voltear_desplazamiento + 4], 4, 0);
    gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
    cantidad_efecto_matriz += 1;
}

void renderizar_reflejo_hielo_jugador(Jugador* jugador, s8 id_jugador, s8 id_pantalla, s8 voltear_desplazamiento) {
    Mat4 sp_a8;
    Vec3f sp9_c;
    Vec3s sp94;

    sp94[0] = 0;
    sp94[1] = jugador->desconocido_048[id_pantalla];
    sp94[2] = jugador->desconocido_050[id_pantalla] + 0x8000; // invert Y
    sp9_c[0] = jugador->pos[0];
    sp9_c[1] = jugador->desconocido_074 + (4.0f * jugador->size);
    sp9_c[2] = jugador->pos[2];
    if (!(jugador->desconocido_002 & (desconocido_002_desconocido_0_x4 << (id_pantalla * 4)))) {
        voltear_desplazamiento = 8;
    } else {
        voltear_desplazamiento = 0;
    }

    trasladar_rotacion_mtxf(sp_a8, sp9_c, sp94);
    escala2_mtxf(sp_a8, tamanio_personaje[jugador->id_personaje] * jugador->size);
    convertir_a_matriz_punto_fijo(&gfx_pool->efecto_mtx[cantidad_efecto_matriz], sp_a8);

    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->efecto_mtx[cantidad_efecto_matriz]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(display_list_cabeza++, renderizar_personaje_ajuste_comun);
    gDPSetTextureLUT(display_list_cabeza++, G_TT_RGBA16);
    funcion_8004B614(efecto_rojo_jugador[id_jugador], efecto_verde_jugador[id_jugador], efecto_azul_jugador[id_jugador],
                  efecto_cian_jugador[id_jugador], efecto_magenta_jugador[id_jugador], efecto_amarillo_jugador[id_jugador],
                  (s16) jugador->alpha / 2);
    gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2);
    gDPLoadTextureBlock(display_list_cabeza++, textura_superior_kart, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPVertex(display_list_cabeza++, &vtx_jugador[id_jugador][voltear_desplazamiento], 4, 0);
    gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
    gDPLoadTextureBlock(display_list_cabeza++, textura_inferior_kart, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPVertex(display_list_cabeza++, &vtx_jugador[id_jugador][voltear_desplazamiento + 4], 4, 0);
    gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
    cantidad_efecto_matriz += 1;
}

void renderizar_jugador(Jugador* jugador, s8 id_jugador, s8 id_pantalla) {
    SIN_USO s32 relleno[2];
    s32 temporal_t1;
    s32 voltear_desplazamiento;
    OSMesg* sp34;

    actualizar_paleta_rueda(jugador, id_jugador, id_pantalla, dato_801651D0[id_pantalla][id_jugador]);
    if (!(jugador->desconocido_002 & (desconocido_002_desconocido_0_x4 << (id_pantalla * 4)))) {
        voltear_desplazamiento = 0;
    } else {
        voltear_desplazamiento = 8;
    }
    funcion_80023BF0(jugador, id_jugador, id_pantalla, voltear_desplazamiento);
    temporal_t1 = LADO_DE_KART << (id_pantalla * 4);
    if ((temporal_t1 == (jugador->desconocido_002 & temporal_t1)) && (jugador->colision.distancia_superficie[2] <= 50.0f) &&
        (jugador->tipo_superficie != HIELO)) {
        if ((jugador->efectos & BOO_EFECTO) == BOO_EFECTO) {
            if (id_jugador == id_pantalla) {
                renderizar_sombra_jugador(jugador, id_jugador, id_pantalla);
            }
        } else {
            renderizar_sombra_jugador(jugador, id_jugador, id_pantalla);
        }
    }
    if ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA) {
        renderizar_kart(jugador, id_jugador, id_pantalla, voltear_desplazamiento);
    } else {
        renderizar_fantasma(jugador, id_jugador, id_pantalla, voltear_desplazamiento);
    }
    osRecvMesg(&cola_msj_dma, (OSMesg*) &sp34, OS_MESG_BLOCK);
    if ((temporal_t1 == (jugador->desconocido_002 & temporal_t1)) && (jugador->tipo_superficie == HIELO) &&
        ((jugador->lakitu_props & LAKITU_RECUPERACION) != LAKITU_RECUPERACION) &&
        (jugador->colision.distancia_superficie[2] <= 30.0f)) {
        renderizar_reflejo_hielo_jugador(jugador, id_jugador, id_pantalla, voltear_desplazamiento);
    }
    if (jugador->potencia_impulso >= 2.0f) {
        funcion_80025DE8(jugador, id_jugador, id_pantalla, voltear_desplazamiento);
    }
}

void funcion_80026A48(Jugador* jugador, s8 indice_jugador) {
    f32 temporal_f0;

    if (((jugador->efectos & TEMPRANO_INICIO_TROMPO_EFECTO) == TEMPRANO_INICIO_TROMPO_EFECTO) &&
        ((jugador->type & SECUENCIA_INICIO_JUGADOR) == 0)) {
        jugador->rueda_rapidez += dato_800DDE74[8];
        if (jugador->rueda_rapidez >= 0x400) {
            jugador->rueda_rapidez = 0;
        }
        return;
    }

    temporal_f0 = ((jugador->speed * (1.0f + jugador->desconocido_104)) / 18.0f) * 216.0f;
    if ((temporal_f0 <= 1.0f) || (es_jugador_triple_b_boton_combo[indice_jugador] == true)) {
        jugador->rueda_rapidez = 0;
    } else {
        jugador->rueda_rapidez += dato_800DDE74[(s32) (temporal_f0 / 12.0f)];
    }
    if (jugador->rueda_rapidez >= 0x400) {
        jugador->rueda_rapidez = 0;
    }
}

#ifdef AVOID_UB
#define RUEDA_D_802F1F80(a, b, c) &lista_paletas_jugador[a][b][c].paleta_rueda
#else
#define RUEDA_D_802F1F80(a, b, c) &lista_paletas_jugador[a][b][(c * 0x100) + 0xC0]
#endif

void actualizar_paleta_rueda(Jugador* jugador, s8 id_jugador, s8 id_pantalla, s8 parametro3) {
    s16 frame_id = ultimo_selector_frame_anim[id_pantalla][id_jugador];
    s16 id_grupo = ultimo_selector_grupo_anim[id_pantalla][id_jugador];
    s16 temporal_t2 = jugador->rueda_rapidez;
    s16 num_temporal = 0x40;

    if (((jugador->efectos & TEMPRANO_INICIO_TROMPO_EFECTO) == TEMPRANO_INICIO_TROMPO_EFECTO) &&
        ((jugador->type & SECUENCIA_INICIO_JUGADOR) == 0)) {
        if (((jugador->efectos & EFECTO_TROMPO_BANANA) != EFECTO_TROMPO_BANANA) &&
            ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) != EFECTO_TROMPO_CONDUCIENDO) &&
            ((jugador->efectos & EFECTO_GOLPE_RAYO) != EFECTO_GOLPE_RAYO) &&
            ((jugador->efectos & desconocido_efecto_0_x_80000) != desconocido_efecto_0_x_80000) &&
            ((jugador->efectos & desconocido_efecto_0_x_800000) != desconocido_efecto_0_x_800000) &&
            ((jugador->kart_props & sin_uso_0_x_800) == 0)) {

            if (frame_id <= 20) {
                cargar_jugador_datos_no_bloqueante(jugador,
                                              (s32) (ruedas_kart_0[jugador->id_personaje][id_grupo] +
                                                     (frame_id * num_temporal * 4) + ((temporal_t2 >> 8) * 0x40)),
                                              RUEDA_D_802F1F80(parametro3, id_pantalla, id_jugador), 0x80);
            } else {
                cargar_jugador_datos_no_bloqueante(jugador,
                                              (s32) (ruedas_kart_1[jugador->id_personaje][id_grupo] +
                                                     (frame_id - 21) * (num_temporal * 4) + ((temporal_t2 >> 8) * 0x40) + 0x600),
                                              RUEDA_D_802F1F80(parametro3, id_pantalla, id_jugador), 0x80);
            }
        } else {
            if (frame_id == 0) {
                cargar_jugador_datos_no_bloqueante(jugador,
                                              (s32) (ruedas_kart_0[jugador->id_personaje][id_grupo] +
                                                     (frame_id * num_temporal * 4) + ((temporal_t2 >> 8) * 0x40)),
                                              RUEDA_D_802F1F80(parametro3, id_pantalla, id_jugador), 0x80);
            } else {
                cargar_jugador_datos_no_bloqueante(jugador,
                                              (s32) (ruedas_kart_1[jugador->id_personaje][id_grupo] +
                                                     (frame_id * num_temporal * 4) + ((temporal_t2 >> 8) * 0x40)),
                                              RUEDA_D_802F1F80(parametro3, id_pantalla, id_jugador), 0x80);
            }
        }
    } else {
        if (((jugador->efectos & EFECTO_TROMPO_BANANA) != EFECTO_TROMPO_BANANA) &&
            ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) != EFECTO_TROMPO_CONDUCIENDO) &&
            ((jugador->efectos & desconocido_efecto_0_x_80000) != desconocido_efecto_0_x_80000) &&
            ((jugador->efectos & desconocido_efecto_0_x_800000) != desconocido_efecto_0_x_800000) &&
            ((jugador->efectos & EFECTO_GOLPE_RAYO) != EFECTO_GOLPE_RAYO) &&
            ((jugador->kart_props & sin_uso_0_x_800) == 0)) {

            if (frame_id <= 20) {
                cargar_jugador_datos_no_bloqueante(jugador,
                                              (s32) (ruedas_kart_0[jugador->id_personaje][id_grupo] +
                                                     (frame_id * num_temporal * 4) + ((temporal_t2 >> 8) * 0x40)),
                                              RUEDA_D_802F1F80(parametro3, id_pantalla, id_jugador), 0x80);
            } else {
                cargar_jugador_datos_no_bloqueante(jugador,
                                              (s32) (ruedas_kart_1[jugador->id_personaje][id_grupo] +
                                                     (frame_id - 21) * (num_temporal * 4) + ((temporal_t2 >> 8) * 0x40) + 0x600),
                                              RUEDA_D_802F1F80(parametro3, id_pantalla, id_jugador), 0x80);
            }
        } else {
            if (frame_id == 0) {
                cargar_jugador_datos_no_bloqueante(jugador,
                                              (s32) (ruedas_kart_0[jugador->id_personaje][id_grupo] +
                                                     (frame_id * num_temporal * 4) + ((temporal_t2 >> 8) * 0x40)),
                                              RUEDA_D_802F1F80(parametro3, id_pantalla, id_jugador), 0x80);
            } else {
                cargar_jugador_datos_no_bloqueante(jugador,
                                              (s32) (ruedas_kart_1[jugador->id_personaje][id_grupo] +
                                                     (frame_id * num_temporal * 4) + ((temporal_t2 >> 8) * 0x40)),
                                              RUEDA_D_802F1F80(parametro3, id_pantalla, id_jugador), 0x80);
            }
        }
    }
}

#undef RUEDA_D_802F1F80

SIN_USO void funcion_8002701C(void) {
}

SIN_USO void funcion_80027024(SIN_USO s32 parametro0, SIN_USO s32 parametro1, SIN_USO s32 parametro2) {
}
