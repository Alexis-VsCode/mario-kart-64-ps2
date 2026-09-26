// Efectos jugador

void funcion_8002C17C(Jugador* jugador, s8 id_jugador) {
    switch (id_circuito_actual) { /* irregular */
        case CIRCUITO_YOSHI_VALLEY:
            if ((jugador->colision.distancia_superficie[2] >= 600.0f) && (dato_80165330[id_jugador] == 0)) {
                dato_80165330[id_jugador] = 1;
                copia_mas_cercano_camino_punto_por_id_jugador[id_jugador] = punto_camino_mas_cercano_por_id_jugador[id_jugador];
                indice_camino_copia_por_id_jugador[id_jugador] = indice_camino_por_id_jugador[id_jugador];
            } else if (dato_80165330[id_jugador] == 0) {
                copia_mas_cercano_camino_punto_por_id_jugador[id_jugador] = punto_camino_mas_cercano_por_id_jugador[id_jugador];
                indice_camino_copia_por_id_jugador[id_jugador] = indice_camino_por_id_jugador[id_jugador];
            } else if (!(jugador->efectos & EFECTO_EN_EL_AIRE)) {
                if (funcion_802ABDF4(jugador->colision.indice_zx_malla) == 0) {
                    dato_80165330[id_jugador] = 0;
                }
            }
            break;
        case CIRCUITO_FRAPPE_SNOWLAND:
            if ((jugador->tipo_superficie == FUERA_PISTA_NIEVE) && (dato_80165330[id_jugador] == 0)) {
                dato_80165330[id_jugador] = 1;
                copia_mas_cercano_camino_punto_por_id_jugador[id_jugador] = punto_camino_mas_cercano_por_id_jugador[id_jugador];
                indice_camino_copia_por_id_jugador[id_jugador] = indice_camino_por_id_jugador[id_jugador];
            } else if (jugador->tipo_superficie != FUERA_PISTA_NIEVE) {
                dato_80165330[id_jugador] = 0;
                copia_mas_cercano_camino_punto_por_id_jugador[id_jugador] = punto_camino_mas_cercano_por_id_jugador[id_jugador];
                indice_camino_copia_por_id_jugador[id_jugador] = indice_camino_por_id_jugador[id_jugador];
            }
            break;
        case CIRCUITO_ROYAL_RACEWAY:
            if (((jugador->efectos & IMPULSO_RAMPA_ASFALTO_EFECTO) != 0) && (dato_80165330[id_jugador] == 0)) {
                dato_80165330[id_jugador] = 1;
                copia_mas_cercano_camino_punto_por_id_jugador[id_jugador] = punto_camino_mas_cercano_por_id_jugador[id_jugador];
                indice_camino_copia_por_id_jugador[id_jugador] = indice_camino_por_id_jugador[id_jugador];
            } else if (((jugador->efectos & IMPULSO_RAMPA_ASFALTO_EFECTO) == 0) && !(jugador->efectos & EFECTO_EN_EL_AIRE)) {
                dato_80165330[id_jugador] = 0;
                copia_mas_cercano_camino_punto_por_id_jugador[id_jugador] = punto_camino_mas_cercano_por_id_jugador[id_jugador];
                indice_camino_copia_por_id_jugador[id_jugador] = indice_camino_por_id_jugador[id_jugador];
            }
            break;
        case CIRCUITO_RAINBOW_ROAD:
            if ((jugador->colision.distancia_superficie[2] >= 600.0f) && (dato_80165330[id_jugador] == 0)) {
                dato_80165330[id_jugador] = 1;
                copia_mas_cercano_camino_punto_por_id_jugador[id_jugador] = punto_camino_mas_cercano_por_id_jugador[id_jugador];
                indice_camino_copia_por_id_jugador[id_jugador] = indice_camino_por_id_jugador[id_jugador];
            } else if (dato_80165330[id_jugador] == 0) {
                copia_mas_cercano_camino_punto_por_id_jugador[id_jugador] = punto_camino_mas_cercano_por_id_jugador[id_jugador];
                indice_camino_copia_por_id_jugador[id_jugador] = indice_camino_por_id_jugador[id_jugador];
            } else if (!((jugador->efectos & EFECTO_EN_EL_AIRE) || (jugador->lakitu_props & LAKITU_RECUPERACION))) {
                dato_80165330[id_jugador] = 0;
            }
            break;
        default:
            dato_80165330[id_jugador] = 0;
            if (1) {}
            break;
    }
}

void funcion_8002C4F8(Jugador* jugador, s8 indice_jugador) {
    dato_801652A0[indice_jugador] = funcion_802AAB4C(jugador);
    if (jugador->pos[1] <= dato_801652A0[indice_jugador]) {
        jugador->oob_props |= OOB_PASADA_O_NIVEL_FLUIDO;
    } else {
        jugador->oob_props &= ~OOB_PASADA_O_NIVEL_FLUIDO;
    }
    if (jugador->tamanio_caja_envolvente < (dato_801652A0[indice_jugador] - jugador->pos[1])) {
        jugador->oob_props |= BAJO_OOB_O_NIVEL_FLUIDO;
        jugador->oob_props &= ~OOB_PASADA_O_NIVEL_FLUIDO;
    } else {
        jugador->oob_props &= ~BAJO_OOB_O_NIVEL_FLUIDO;
    }
    if (jugador->tamanio_caja_envolvente < (dato_801652A0[indice_jugador] - jugador->pos[1])) {
        if ((jugador->oob_props & BAJO_NIVEL_FLUIDO) != BAJO_NIVEL_FLUIDO) {
            jugador->oob_props |= BAJO_NIVEL_OOB;
            jugador->oob_props |= BAJO_NIVEL_FLUIDO;
            if ((id_circuito_actual != CIRCUITO_KOOPA_BEACH) && (id_circuito_actual != CIRCUITO_SKYSCRAPER) &&
                (id_circuito_actual != CIRCUITO_RAINBOW_ROAD) && ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR)) {
                if ((id_circuito_actual == CIRCUITO_BOWSER_CASTLE) || (id_circuito_actual == CIRCUITO_BIG_DONUT)) {
                    funcion_800C9060((u8) indice_jugador, 0x1900801CU);
                } else {
                    funcion_800C9060((u8) indice_jugador, 0x19008008U);
                }
            }
        }
    }
    if ((id_circuito_actual == CIRCUITO_KOOPA_BEACH) || (id_circuito_actual == CIRCUITO_SKYSCRAPER) ||
        (id_circuito_actual == CIRCUITO_RAINBOW_ROAD)) {
        jugador->oob_props &= ~(BAJO_NIVEL_OOB | BAJO_NIVEL_FLUIDO);
    }
    if ((jugador->tamanio_caja_envolvente < (dato_801652A0[indice_jugador] - jugador->pos[1])) &&
        (jugador->colision.distancia_superficie[2] >= 600.0f)) {
        jugador->lakitu_props |= LAKITU_RECUPERACION;
    }
    if (jugador->colision.distancia_superficie[2] >= 600.0f) {
        jugador->lakitu_props |= WENT_SOBRE_OOB;
    } else if ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) {
        jugador->lakitu_props &= ~WENT_SOBRE_OOB;
    }
    if ((jugador->type & CPU_JUGADOR) &&
        ((funcion_802ABDF4(jugador->colision.indice_zx_malla) != 0) || (jugador->lakitu_props & LAKITU_RECUPERACION))) {
        if (!(jugador->lakitu_props & MANTENIDO_POR_LAKITU) && !(jugador->lakitu_props & LAKITU_ESCENA) &&
            !(jugador->efectos & EFECTO_CARRERA_PERDIDO)) {
            funcion_80090778(jugador);
            funcion_80090868(jugador);
        }
    }
    if ((jugador->type & CPU_JUGADOR) && (jugador->tipo_superficie == SALIDA_DE_LIMITES) && !(jugador->efectos & EFECTO_EN_EL_AIRE)) {
        funcion_80090778(jugador);
        funcion_80090868(jugador);
    }
    funcion_8002C17C(jugador, indice_jugador);
}

void funcion_8002C7E4(Jugador* jugador, s8 indice_jugador, s8 parametro2) {
    if ((jugador->desconocido_046 & 1) != 1) {
        if ((jugador->efectos & EFECTO_GOLPE_ENEMIGO) == EFECTO_GOLPE_ENEMIGO) {
            if ((jugador->efectos & EFECTO_HONGO) != EFECTO_HONGO) {
                funcion_8002B9CC(jugador, indice_jugador, parametro2);
            }
            jugador->kart_props &= ~ARRIBA_ATRAS;
            jugador->desconocido_046 |= 1;
            jugador->desconocido_046 |= 8;
            if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
                funcion_8001CA24(jugador, 2.8f);
            }
            if ((jugador->desconocido_046 & TOCAR_BICHO) == TOCAR_BICHO) {
                if ((jugador->desconocido_046 & PORTON_TOCAR_BICHO) != PORTON_TOCAR_BICHO) {
                    jugador->desconocido_046 |= PORTON_TOCAR_BICHO;
                    jugador->desconocido_046 |= TROMPO_INSTANTE;
                    if (jugador->efectos & EFECTO_HONGO) {
                        quitar_efecto_hongo(jugador);
                    }
                }
            }
        }
    }
    if ((jugador->efectos & EFECTO_GOLPE_ENEMIGO) == EFECTO_GOLPE_ENEMIGO) {
        jugador->efectos &= ~EFECTO_GOLPE_ENEMIGO;
        jugador->desconocido_10C = 1;
        jugador->kart_props &= ~ARRIBA_ATRAS;
        return;
    }
    jugador->desconocido_046 &= ~0x0001;
    jugador->efectos &= ~EFECTO_GOLPE_ENEMIGO;
    if (jugador->desconocido_10C > 0) {
        jugador->desconocido_10C += 1;
    }
    if (jugador->desconocido_10C >= 0xA) {
        jugador->desconocido_10C = 0;
    }
}

void funcion_8002C954(Jugador* jugador, s8 id_jugador, Vec3f velocidad) {
    f32 temporal_f0;
    f32 variable_f14;
    f32 xdist;
    f32 ydist;
    f32 zdist;

    temporal_f0 = jugador->pos[1] - jugador->desconocido_074;

    if (((((jugador->efectos & EFECTO_VUELCO_TERRENO) != EFECTO_VUELCO_TERRENO) &&
          ((jugador->efectos & IMPULSO_RAMPA_ASFALTO_EFECTO) == IMPULSO_RAMPA_ASFALTO_EFECTO)) ||
         ((((temporal_f0 >= 20.0f) || (temporal_f0 < (-1.0f))) && ((jugador->efectos & EFECTO_VUELCO_TERRENO) == 0)) &&
          (jugador->efectos & EFECTO_EN_EL_AIRE)) ||
         ((jugador->colision.unk34 == 0) && ((jugador->efectos & EFECTO_VUELCO_TERRENO) == 0))) &&
        (((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == 0) || (!(jugador->lakitu_props & LAKITU_ESCENA)))) {
        funcion_8008F494(jugador, id_jugador);
    }
    if ((jugador->desconocido_046 & 0x20) != 0x20) {
        if ((jugador->colision.distancia_superficie[0] < (-1.0f)) || (jugador->colision.distancia_superficie[1] < (-1.0f))) {
            jugador->desconocido_256 = 1;
        }
        jugador->desconocido_046 |= 0x20;
    }
    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) && (((jugador->speed / 18.0f) * 216.0f) > 30.0f)) {
        funcion_8001CA24(jugador, 3.0f);
    }
    jugador->desconocido_046 |= 0x10;
    jugador->desconocido_256++;
    if (jugador->desconocido_256 >= 0xA) {
        jugador->desconocido_256 = 0;
    }
    if ((jugador->acel_pendiente >= 0) && (((jugador->speed / 18.0f) * 216.0f) > 5.0f)) {
        alternativo_desacelerar_jugador(jugador, 18.0f);
    }
    if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
        xdist = velocidad_ultimo_jugador[id_jugador][0] - velocidad[0];
        variable_f14 = velocidad_ultimo_jugador[id_jugador][1] - velocidad[1];
        ydist = variable_f14;
        zdist = velocidad_ultimo_jugador[id_jugador][2] - velocidad[2];
        variable_f14 = sqrtf((xdist * xdist) + (ydist * ydist) + (zdist * zdist)) / 3;
        if (variable_f14 >= 1.0) {
            variable_f14 = 1.0f;
        }
        if ((variable_f14 <= 0.6) && (((jugador->speed / 18.0f) * 216.0f) >= 40.0f) &&
            (!(jugador->type & INVISIBLE_JUGADOR_O_BOMBA))) {
            funcion_800CAEC4(id_jugador, 0.6F);
        } else if (!(jugador->type & INVISIBLE_JUGADOR_O_BOMBA)) {
            if ((variable_f14 <= 0.6) && (((jugador->speed / 18.0f) * 216.0f) < 40.0f) &&
                (((jugador->speed / 18.0f) * 216.0f) >= 10.0f)) {
                funcion_800CAEC4(id_jugador, 0.3F);
            } else {
                funcion_800CAEC4(id_jugador, variable_f14);
            }
        }
    }
    if (jugador->efectos & EFECTO_HONGO) {
        quitar_efecto_hongo(jugador);
        jugador->desconocido_08C /= 2;
    }
}

void aplicar_efecto(Jugador* jugador, s8 indice_jugador, s8 parametro2) {
    if (((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == MANTENIDO_POR_LAKITU) ||
        ((jugador->lakitu_props & LAKITU_ESCENA) == LAKITU_ESCENA)) {
        funcion_80090970(jugador, indice_jugador, parametro2);
    }
    if ((jugador->efectos & BANANA_CERCA_EFECTO_TROMPO) == BANANA_CERCA_EFECTO_TROMPO) {
        aplicar_banana_cerca_efecto_trompo(jugador, indice_jugador);
    }
    if (jugador->kart_props & CONDUCIENDO_CERCA_TROMPO) {
        aplicar_conduciendo_cerca_efecto_trompo(jugador, indice_jugador);
    }
    if ((jugador->efectos & EFECTO_HONGO) == EFECTO_HONGO) {
        aplicar_efecto_hongo(jugador);
    }
    if ((jugador->efectos & IMPULSO_RAMPA_ASFALTO_EFECTO) == IMPULSO_RAMPA_ASFALTO_EFECTO) {
        aplicar_impulso_rampa_asfalto_efecto(jugador);
    }
    if ((jugador->efectos & IMPULSO_RAMPA_MADERA_EFECTO) == IMPULSO_RAMPA_MADERA_EFECTO) {
        aplicar_impulso_rampa_madera_efecto(jugador);
    }
    if ((s32) (jugador->efectos & EFECTO_APLASTAMIENTO) == EFECTO_APLASTAMIENTO) {
        aplicar_efecto_golpe(jugador, indice_jugador);
    }
    if ((jugador->efectos & EFECTO_RAYO) == EFECTO_RAYO) {
        aplicar_efecto_rayo(jugador, indice_jugador);
    }
    if ((jugador->efectos & EFECTO_VUELCO_TERRENO) == EFECTO_VUELCO_TERRENO) {
        funcion_8008F3F4(jugador, indice_jugador);
    }
    if ((jugador->efectos & EFECTO_ESTRELLA) == EFECTO_ESTRELLA) {
        aplicar_efecto_estrella(jugador, indice_jugador);
    }
    if ((jugador->efectos & BOO_EFECTO) == BOO_EFECTO) {
        aplicar_boo_efecto(jugador, indice_jugador);
    }
    if (((jugador->efectos & EFECTO_FUERA_DERRAPE) == EFECTO_FUERA_DERRAPE) && (jugador->contador_estado_derrape >= 100)) {
        alternativo_desacelerar_jugador(jugador, 4.0f);
    }
    if (((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
        ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO)) {
        funcion_8008C9EC(jugador, indice_jugador);
    }
    if ((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) == GOLPE_POR_CAPARAZON_VERDE_EFECTO) {
        funcion_8008C62C(jugador, indice_jugador);
    }
    if ((jugador->efectos & EFECTO_ERROR_EXPLOSION) == EFECTO_ERROR_EXPLOSION) {
        funcion_8008E4A4(jugador, indice_jugador);
    }
    if ((jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA) == GOLPE_POR_EFECTO_ESTRELLA) {
        aplicar_golpe_por_efecto_estrella(jugador, indice_jugador);
    }
    if ((jugador->efectos & TEMPRANO_INICIO_TROMPO_EFECTO) == TEMPRANO_INICIO_TROMPO_EFECTO) {
        funcion_8008F1B8(jugador, indice_jugador);
    }
    if ((jugador->efectos & desconocido_efecto_0_x_80000) == desconocido_efecto_0_x_80000) {
        funcion_8008D698(jugador, indice_jugador);
    }
    if ((jugador->efectos & desconocido_efecto_0_x_800000) == desconocido_efecto_0_x_800000) {
        funcion_8008D8B4(jugador, indice_jugador);
        alternativo_desacelerar_jugador(jugador, 10.0f);
    }
    if (estado_carrera != HECHO_CARRERA) {
        if (jugador->disparadores & EFECTO_BATALLA_PERDER) {
            funcion_8008FC64(jugador, indice_jugador);
        }
        if (jugador->disparadores & EFECTO_BOMBA_VOLVERSE) {
            funcion_8008FCDC(jugador, indice_jugador);
        }
    }
    if (jugador->kart_props & sin_uso_0_x_800) { // never true
        funcion_80091298(jugador, indice_jugador);
    }
}

void funcion_8002D028(Jugador* jugador, s8 indice_jugador) {
    Vec3f sp4_c;
    f32 temporal_f18;
    s16 temporal_t1;
    s16 temporal_;
    s16 temporal2;
    f32 cosa0;
    SIN_USO s32 relleno;

    sp4_c[0] = dato_80165210[dato_80165270[indice_jugador]];
    sp4_c[1] = 0;
    sp4_c[2] = dato_80165230[dato_80165270[indice_jugador]];

    temporal_ = -(s16) obtener_angulo_xz_entre_puntos(jugador->pos, sp4_c);
    temporal2 = jugador->rotacion[1];
    temporal_ = (temporal_ - temporal2);

    cosa0 = 8;

    if (temporal_ > ((s16) (cosa0 * GRADOS(1)))) {
        temporal_ = (cosa0 * GRADOS(1));
    }
    if (temporal_ < ((s16) (-cosa0 * GRADOS(1)))) {
        temporal_ = (-cosa0 * GRADOS(1));
    }

    temporal_t1 = (dato_80165020[indice_jugador] + ((s16) ((temporal_ * 0x35) / (cosa0 * GRADOS(1))))) / 2;
    aplicar_giro_cpu(jugador, (s16) temporal_t1);
    dato_80165020[indice_jugador] = (s16) temporal_t1;

    temporal_f18 = sqrtf((sp4_c[0] - jugador->pos[0]) * (sp4_c[0] - jugador->pos[0]) +
                     (sp4_c[2] - jugador->pos[2]) * (sp4_c[2] - jugador->pos[2]));
    if (temporal_f18 <= 8.0f) {
        ajustar_angulo(&jugador->rotacion[1], -GRADOS(180), GRADOS(2));
        if ((jugador->rotacion[1] <= (-179 * GRADOS(1))) || (jugador->rotacion[1] >= (179 * GRADOS(1)))) {
            jugador->type &= ~PREPARACION_JUGADOR;
        }
        jugador->desconocido_08C = 0;
        jugador->speed = 0;
        jugador->desconocido_104 = 0;
        jugador->rueda_rapidez = 0;
        jugador->posicion_giro = 0;
        jugador->velocidad[0] = 0;
        jugador->velocidad[1] = 0;
        jugador->velocidad[2] = 0;
        jugador->desconocido_0C0 = 0;
        jugador->desconocido_078 = 0;
    } else {
        jugador->desconocido_08C = 1200;
    }
}

void funcion_8002D268(Jugador* jugador, SIN_USO Camara* camara, s8 id_pantalla, s8 id_jugador) {
    Vec3f sp184 = { 0.0, 0.0, 1.0 };
    Vec3f sp178 = { 0.0, 0.0, 0.0 };
    Vec3f sp16_c = { 0.0, 0.0, 0.0 };
    Vec3f sp160 = { 0.0, 0.0, 0.0 };
    f32 sp104[] = { 0.825, 0.8, 0.725, 0.625, 0.425, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,
                    0.3,   0.3, 0.3,   0.3,   0.3,   0.3, 0.3, 0.3, 0.3, 0.3, 0.3 };
    f32 temporal_;
    f32 siguiente_x;
    f32 siguiente_y;
    f32 siguiente_z;
    f32 pos_x;
    f32 pos_y;
    f32 pos_z;
    f32 temporal2;
    s32 temporal_v0_3;
    s32 temporal3;
    f32 temporal_f2_2;
    SIN_USO s32 relleno[8];
    f32 gravedad_x;
    f32 gravedad_y;
    f32 gravedad_z;
    f32 distancia_superficie;
    SIN_USO s32 relleno2;
    Vec3f velocidad_nuevo;
    Vec3f sp8_c;
    SIN_USO s32 relleno3[3];
    s32 sp7_c = 0;
    SIN_USO s32 relleno4[6];

    funcion_80027EDC(jugador, id_jugador);
    actualizar_duracion_derrape_jugador(jugador);
    if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
        funcion_8002A79C(jugador, id_jugador);
    }
    funcion_8002B830(jugador, id_jugador, id_pantalla);
    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
        funcion_8002BF4C(jugador, id_jugador);
    }
    aplicar_efecto(jugador, id_jugador, id_pantalla);
    if (((jugador->efectos & EFECTO_FUERA_DERRAPE) == EFECTO_FUERA_DERRAPE) && (jugador->contador_estado_derrape >= 100)) {
        sp7_c = 2;
    }
    funcion_80037BB4(jugador, sp160);
    funcion_8002AB70(jugador);
    funcion_8002FCA8(jugador, id_jugador);
    if (jugador->kart_props & ARRIBA_ATRAS) {
        jugador->desconocido_064[0] *= -1.0f;
        jugador->desconocido_064[2] *= -1.0f;
    }
    if ((jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie == ASFALTO) && (jugador->ruedas[DERECHA_ATRAS].tipo_superficie == ASFALTO)) {
        gravedad_x = (-1 * (jugador->desconocido_064[0] + sp16_c[0])) +
               ((-jugador->colision.vector_orientacion[0] * jugador->gravedad_kart) * 0.925);
        gravedad_y = (-jugador->colision.vector_orientacion[1] * jugador->gravedad_kart);
        gravedad_z = (-1 * (jugador->desconocido_064[2] + sp16_c[2])) +
               ((-jugador->colision.vector_orientacion[2] * jugador->gravedad_kart) * 0.925);
    } else {
        temporal3 = (((jugador->speed / 18.0f) * 216.0f) / 10.0f);
        if (temporal3 >= 10) {
            temporal3 = 10;
        }
        gravedad_x = -1 * (jugador->desconocido_064[0] + sp16_c[0]) +
                   ((-jugador->colision.vector_orientacion[0] * jugador->gravedad_kart) * sp104[temporal3]);
        gravedad_y = (-jugador->colision.vector_orientacion[1] * jugador->gravedad_kart);
        gravedad_z = -1 * (jugador->desconocido_064[2] + sp16_c[2]) +
                   ((-jugador->colision.vector_orientacion[2] * jugador->gravedad_kart) * sp104[temporal3]);
    }
    if (((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) &&
        ((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB)) {
        gravedad_x = 0 * (jugador->desconocido_064[0] + sp16_c[0]);
        gravedad_y = -1 * jugador->gravedad_kart / 4;
        gravedad_z = 0 * (jugador->desconocido_064[2] + sp16_c[2]);
    }
    if ((jugador->efectos & EFECTO_EN_EL_AIRE) == EFECTO_EN_EL_AIRE) {
        gravedad_x = 0 * (jugador->desconocido_064[0] + sp16_c[0]);
        gravedad_y = -1 * jugador->gravedad_kart;
        gravedad_z = 0 * (jugador->desconocido_064[2] + sp16_c[2]);
    }
    temporal_f2_2 = ((jugador->pos_viejo[2] - jugador->pos[2]) * coss(jugador->rotacion[1] + jugador->desconocido_0C0)) +
                (-(jugador->pos_viejo[0] - jugador->pos[0]) * senos(jugador->rotacion[1] + jugador->desconocido_0C0));
    if (temporal_f2_2 > 0.1) {
        jugador->kart_props |= HACIA_ATRAS_MOVIMIENTO;
    } else {
        jugador->kart_props &= ~HACIA_ATRAS_MOVIMIENTO;
    }
    if (((jugador->desconocido_08C <= 0.0f) &&
         ((temporal_v0_3 = jugador->efectos, (temporal_v0_3 & EFECTO_FRENADO) == EFECTO_FRENADO))) &&
        ((temporal_v0_3 & EFECTO_GIRO_AB) != EFECTO_GIRO_AB)) {
        sp178[2] = temporal_f2_2 * 4500.0f;
    } else {
        sp178[2] = 0.0f;
    }
    sp178[1] = 0.0f;
    transformar_mat3_vec3f_mtxf(sp178, jugador->matriz_orientacion);
    gravedad_x += sp178[0];
    gravedad_z += sp178[2];
    funcion_8002C7E4(jugador, id_jugador, id_pantalla);
    sp184[2] = funcion_80030150(jugador, id_jugador);
    transformar_mat3_vec3f_mtxf(sp184, jugador->matriz_orientacion);
    velocidad_nuevo[0] = jugador->velocidad[0];
    velocidad_nuevo[1] = jugador->velocidad[1];
    velocidad_nuevo[2] = jugador->velocidad[2];
    if (((jugador->desconocido_10C < 3) && (((s32) jugador->desconocido_256) < 3)) ||
        ((jugador->efectos & EFECTO_HONGO) == EFECTO_HONGO)) {

        if (((jugador->posicion_giro >> 16) >= 40) || ((jugador->posicion_giro >> 16) <= -40)) {

            velocidad_nuevo[0] += (((((f64) ((sp184[0] + gravedad_x) + sp160[0])) -
                                 (velocidad_nuevo[0] * (0.12 * ((f64) jugador->friccion_kart)))) /
                                6000.0) /
                               (((((f64) jugador->desconocido_20C) * 0.6) + 1.0) + sp7_c));
            velocidad_nuevo[2] += (((((f64) ((sp184[2] + gravedad_z) + sp160[2])) -
                                 (velocidad_nuevo[2] * (0.12 * ((f64) jugador->friccion_kart)))) /
                                6000.0) /
                               (((((f64) jugador->desconocido_20C) * 0.6) + 1.0) + sp7_c));
        } else {
            velocidad_nuevo[0] += (((((f64) ((sp184[0] + gravedad_x) + sp160[0])) -
                                 (velocidad_nuevo[0] * (0.12 * ((f64) jugador->friccion_kart)))) /
                                6000.0) /
                               (sp7_c + 1));
            velocidad_nuevo[2] += (((((f64) ((sp184[2] + gravedad_z) + sp160[2])) -
                                 (velocidad_nuevo[2] * (0.12 * ((f64) jugador->friccion_kart)))) /
                                6000.0) /
                               (sp7_c + 1));
        }
    } else {
        velocidad_nuevo[0] +=
            (((((f64) ((sp184[0] + gravedad_x) + sp160[0])) - (velocidad_nuevo[0] * (0.12 * ((f64) jugador->friccion_kart)))) /
              6000.0) /
             30.0);
        velocidad_nuevo[2] +=
            (((((f64) ((sp184[2] + gravedad_z) + sp160[2])) - (velocidad_nuevo[2] * (0.12 * ((f64) jugador->friccion_kart)))) /
              6000.0) /
             30.0);
    }
    velocidad_nuevo[1] +=
        (((((f64) ((sp184[1] + gravedad_y) + sp160[1])) - (velocidad_nuevo[1] * (0.12 * ((f64) jugador->friccion_kart)))) /
          6000.0) /
         ((f64) jugador->desconocido_dac));
    if (((((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == MANTENIDO_POR_LAKITU) ||
          ((jugador->lakitu_props & LAKITU_ESCENA) == LAKITU_ESCENA)) ||
         ((jugador->efectos & EFECTO_APLASTAMIENTO) == EFECTO_APLASTAMIENTO)) ||
        (jugador->lakitu_props & LAKITU_RECUPERACION)) {
        velocidad_nuevo[0] = 0.0f;
        velocidad_nuevo[1] = 0.0f;
        velocidad_nuevo[2] = 0.0f;
    }
    if ((jugador->kart_props & CARRERA_GP_PERDER) == CARRERA_GP_PERDER) {
        jugador->kart_props &= ~CARRERA_GP_PERDER;
    }

    pos_x = jugador->pos[0];
    pos_y = jugador->pos[1];
    pos_z = jugador->pos[2];

    jugador->pos_viejo[0] = jugador->pos[0];
    jugador->pos_viejo[2] = jugador->pos[2];
    jugador->pos_viejo[1] = jugador->pos[1];
    siguiente_x = pos_x + jugador->velocidad[0] + dato_8018CE10[id_jugador].desconocido_04[0];
    siguiente_y = pos_y + jugador->velocidad[1];
    siguiente_z = pos_z + jugador->velocidad[2] + dato_8018CE10[id_jugador].desconocido_04[2];

    if (((((jugador->lakitu_props & MANTENIDO_POR_LAKITU) != MANTENIDO_POR_LAKITU) &&
          ((jugador->lakitu_props & LAKITU_ESCENA) != LAKITU_ESCENA)) &&
         ((jugador->efectos & EFECTO_APLASTAMIENTO) != EFECTO_APLASTAMIENTO)) &&
        (!(jugador->lakitu_props & LAKITU_RECUPERACION))) {
        funcion_8002AAC0(jugador);
        siguiente_y += jugador->velocidad_salto_kart;
        siguiente_y -= 0.02;
    }
    colision_terreno_actor(&jugador->colision, jugador->tamanio_caja_envolvente, siguiente_x, siguiente_y, siguiente_z, jugador->pos_viejo[0],
                            jugador->pos_viejo[1], jugador->pos_viejo[2]);
    jugador->desconocido_058 = 0.0f;
    jugador->desconocido_060 = 0.0f;
    jugador->desconocido_05C = 1.0f;
    if ((jugador->kart_props & ARRIBA_ATRAS) != ARRIBA_ATRAS) {
        calcular_matriz_orientacion(jugador->matriz_orientacion, jugador->desconocido_058, jugador->desconocido_05C, jugador->desconocido_060,
                                     jugador->rotacion[1]);
    } else {
        calcular_matriz_orientacion(jugador->matriz_orientacion, jugador->desconocido_058, jugador->desconocido_05C, jugador->desconocido_060,
                                     jugador->rotacion[1] + GRADOS(180));
    }
    jugador->efectos |= EFECTO_EN_EL_AIRE;
    jugador->desconocido_0C2 += 1;
    distancia_superficie = jugador->colision.distancia_superficie[2];
    if (distancia_superficie <= 0.0f) {
        jugador->efectos = jugador->efectos & (~EFECTO_SALTO);
        jugador->efectos = jugador->efectos & (~EFECTO_EN_EL_AIRE);
        if (jugador->desconocido_0C2 >= 35) {
            if (jugador->desconocido_0C2 >= 0x32) {
                jugador->desconocido_0C2 = 0x32;
            }
            jugador->desconocido_DB4.desconocido_c = 3.0f;
            jugador->desconocido_DB4.unk18 = 0;
            jugador->graficos_kart |= POOMP;
            if ((((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
                 ((jugador->efectos & IMPULSO_RAMPA_ASFALTO_EFECTO) == IMPULSO_RAMPA_ASFALTO_EFECTO)) &&
                ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {

                funcion_800C9060(id_jugador, 0x1900A60AU);
            } else if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
                       ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
                funcion_800CADD0((u8) id_jugador, ((f32) jugador->desconocido_0C2) / 35.0f);
            }
            if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
                jugador->kart_props |= ACELERADOR_VUELCO_PUBLICAR;
            }
        }
        if (((jugador->desconocido_0C2 < 0x23) && (jugador->desconocido_0C2 >= 0x1C)) && (((jugador->speed / 18.0f) * 216.0f) >= 20.0f)) {
            jugador->desconocido_DB4.desconocido_c = 2.8f;
            jugador->desconocido_DB4.unk18 = 0;
            if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
                ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
                funcion_800CADD0((u8) id_jugador, ((f32) jugador->desconocido_0C2) / 35.0f);
            }
            if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
                jugador->kart_props |= ACELERADOR_VUELCO_PUBLICAR;
            }
        }
        if (((jugador->desconocido_0C2 < 0x1C) && (jugador->desconocido_0C2 >= 4)) && (((jugador->speed / 18.0f) * 216.0f) >= 20.0f)) {
            jugador->desconocido_DB4.unk18 = 0;
            jugador->desconocido_DB4.desconocido_c = 1.5f;
            if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
                ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
                if (((jugador->desconocido_0C2 < 0xB) && (jugador->desconocido_0C2 >= 4)) && (id_circuito_actual == CIRCUITO_BOWSER_CASTLE)) {
                    funcion_800CADD0((u8) id_jugador, jugador->desconocido_0C2 / 14.0f);
                } else {
                    funcion_800CADD0((u8) id_jugador, jugador->desconocido_0C2 / 25.0f);
                }
            }
        }
        jugador->desconocido_0C2 = 0;
        jugador->velocidad_salto_kart = jugador->desconocido_0C2;
    }
    distancia_superficie = jugador->colision.distancia_superficie[2];
    if (distancia_superficie <= 0.0f) {
        funcion_8003F46C(jugador, sp8_c, velocidad_nuevo, sp178, &distancia_superficie, &siguiente_x, &siguiente_y, &siguiente_z);
    }
    distancia_superficie = jugador->colision.distancia_superficie[0];
    if (distancia_superficie < 0.0f) {
        funcion_8003F734(jugador, sp8_c, velocidad_nuevo, &distancia_superficie, &siguiente_x, &siguiente_y, &siguiente_z);
        funcion_8002C954(jugador, id_jugador, velocidad_nuevo);
    }
    distancia_superficie = jugador->colision.distancia_superficie[1];
    if (distancia_superficie < 0.0f) {
        funcion_8003FBAC(jugador, sp8_c, velocidad_nuevo, &distancia_superficie, &siguiente_x, &siguiente_y, &siguiente_z);
        funcion_8002C954(jugador, id_jugador, velocidad_nuevo);
    }
    distancia_superficie = jugador->colision.distancia_superficie[0];
    if (distancia_superficie >= 0.0f) {
        distancia_superficie = jugador->colision.distancia_superficie[1];
        if (distancia_superficie >= 0.0f) {
            jugador->desconocido_046 &= 0xFFDF;
            if (jugador->desconocido_256 != 0) {
                jugador->desconocido_256++;
                if (jugador->desconocido_256 >= 10) {
                    jugador->desconocido_256 = 0;
                }
            }
        }
    }
    if (((!(jugador->efectos & EFECTO_EN_EL_AIRE)) && (funcion_802ABDB8(jugador->colision.indice_zx_malla) != 0)) &&
        ((jugador->efectos & EFECTO_VUELCO_TERRENO) != EFECTO_VUELCO_TERRENO)) {
        if ((!(jugador->lakitu_props & MANTENIDO_POR_LAKITU)) || (!(jugador->lakitu_props & LAKITU_ESCENA))) {
            funcion_8008F494(jugador, id_jugador);
        }
    } else if (((!(jugador->efectos & EFECTO_EN_EL_AIRE)) && (funcion_802ABDB8(jugador->colision.indice_zx_malla) == 0)) &&
               (jugador->efectos & EFECTO_VUELCO_TERRENO)) {
        funcion_8008F5A4(jugador, id_jugador);
    }
    jugador->desconocido_074 = calcular_altura_superficie(siguiente_x, siguiente_y, siguiente_z, jugador->colision.indice_zx_malla);
    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        (((modo_pantalla_activo == MODO_PANTALLA_1P) || (modo_pantalla_activo == PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL)) ||
         (modo_pantalla_activo == PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL))) {
        funcion_80029B4C(jugador, siguiente_x, siguiente_y, siguiente_z);
    } else {
        funcion_8002A194(jugador, siguiente_x, siguiente_y, siguiente_z);
    }
    funcion_8002AE38(jugador, id_jugador, pos_x, pos_z, siguiente_x, siguiente_z);

    temporal2 = (velocidad_nuevo[0] * velocidad_nuevo[0]) + (velocidad_nuevo[2] * velocidad_nuevo[2]);
    jugador->anterior_rapidez = jugador->speed;
    jugador->speed = sqrtf(temporal2);

    if ((jugador->desconocido_08C <= 0.0f) && (jugador->speed <= 0.08) && (dato_8018CE10[id_jugador].desconocido_04[0] == 0.0f) &&
        (dato_8018CE10[id_jugador].desconocido_04[2] == 0.0f)) {
        velocidad_nuevo[0] = velocidad_nuevo[0] + (-1 * velocidad_nuevo[0]);
        velocidad_nuevo[2] = velocidad_nuevo[2] + (-1 * velocidad_nuevo[2]);
    } else {
        jugador->pos[0] = siguiente_x;
        jugador->pos[2] = siguiente_z;
    }
    jugador->pos[1] = siguiente_y;
    if ((jugador->type & HUMANO_JUGADOR) && (!(jugador->type & CPU_JUGADOR))) {
        funcion_8002BB9C(jugador, &siguiente_x, &siguiente_z, id_pantalla, id_jugador, velocidad_nuevo);
    }
    jugador->desconocido_064[0] = sp178[0];
    jugador->desconocido_064[2] = sp178[2];
    jugador->velocidad[0] = velocidad_nuevo[0];
    jugador->velocidad[1] = velocidad_nuevo[1];
    jugador->velocidad[2] = velocidad_nuevo[2];
    velocidad_ultimo_jugador[id_jugador][0] = velocidad_nuevo[0];
    velocidad_ultimo_jugador[id_jugador][1] = velocidad_nuevo[1];
    velocidad_ultimo_jugador[id_jugador][2] = velocidad_nuevo[2];
    if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
        if (kart_arriba_rapidez_tabla[jugador->id_personaje] < jugador->speed) {
            temporal_ = kart_arriba_rapidez_tabla[jugador->id_personaje] / jugador->speed;
            jugador->velocidad[0] *= temporal_;
            jugador->velocidad[1] *= temporal_;
            jugador->velocidad[2] *= temporal_;
            jugador->speed = kart_arriba_rapidez_tabla[jugador->id_personaje];
        }
    }
    if ((jugador->kart_props & ARRIBA_ATRAS) == ARRIBA_ATRAS) {
        if (jugador->speed > 1) {
            temporal_ = 1 / jugador->speed;
            jugador->velocidad[0] *= temporal_;
            jugador->velocidad[1] *= temporal_;
            jugador->velocidad[2] *= temporal_;
            jugador->speed = 1;
        }
    }
    if (jugador->colision.distancia_superficie[2] >= 500.0f) {
        jugador->desconocido_078 = (s16) (((s16) jugador->desconocido_078) / 2);
    }
    funcion_8002C4F8(jugador, id_jugador);
}

void funcion_8002E4C4(Jugador* jugador) {
    s32 jugador_indice;

    jugador_indice = obtener_indice_jugador_para_jugador(jugador);
    jugador->tiron_salto_kart = 0.0f;
    jugador->aceleracion_salto_kart = 0.0f;
    jugador->velocidad_salto_kart = 0.0f;
    jugador->pos[1] = obtener_altura_superficie(jugador->pos[0], camino_y_jugador[jugador_indice] + 10.0f, jugador->pos[2]) +
                     jugador->tamanio_caja_envolvente;
    if (((jugador->pos[1] - camino_y_jugador[jugador_indice]) > 1200.0f) ||
        ((jugador->pos[1] - camino_y_jugador[jugador_indice]) < -1200.0f)) {
        jugador->pos[1] = jugador->pos_viejo[1];
    }
    jugador->velocidad[1] = 0.0f;
}
