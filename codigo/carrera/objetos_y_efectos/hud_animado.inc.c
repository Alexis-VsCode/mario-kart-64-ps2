// Hud animado

void funcion_8005AB60(void) {
    switch (h_ud_jugador[JUGADOR_UNO].unk_78) {
        case 0:
            break;
        case 1:
            paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].velocimetro_x, 0x106, 0x10);
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].velocimetro_y, 182, 0x10) != 0) {
                h_ud_jugador[JUGADOR_UNO].unk_78++;
                h_ud_jugador[JUGADOR_UNO].desconocido_79 = 1;
            }
            break;
        case 2:
            paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].velocimetro_x, 0x116, 4);
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].velocimetro_y, 0xC6, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].unk_78++;
            }
            break;
        case 3:
            paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].velocimetro_x, 0x106, 4);
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].velocimetro_y, 182, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].unk_78++;
            }
            break;
        case 4:
            paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].velocimetro_x, 0x10E, 4);
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].velocimetro_y, 0xBE, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].unk_78++;
            }
            break;
        case 5:
            paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].velocimetro_x, 0x106, 4);
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].velocimetro_y, 182, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].unk_78++;
            }
            break;
        case 6:
            paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].velocimetro_x, 0x10A, 2);
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].velocimetro_y, 0xBA, 2) != 0) {
                h_ud_jugador[JUGADOR_UNO].unk_78++;
            }
            break;
        case 7:
            paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].velocimetro_x, 0x106, 2);
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].velocimetro_y, 182, 2) != 0) {
                h_ud_jugador[JUGADOR_UNO].unk_78++;
            }
            break;
        case 8:
            h_ud_jugador[JUGADOR_UNO].unk_78 = 0;
            break;
    }
    if ((h_ud_jugador[JUGADOR_UNO].desconocido_79 != 0) && (h_ud_jugador[JUGADOR_UNO].desconocido_79 == 1)) {
        if (++dato_801657E7 >= 0x10) {
            dato_801657E7 = 0;
            dato_8016579E = 0xDD00;
            h_ud_jugador[JUGADOR_UNO].desconocido_79 = 0U;
        } else {
            dato_8016579E = dato_800E55B0[dato_801657E7] + 0xDD00;
        }
    }
    switch (h_ud_jugador[JUGADOR_UNO].desconocido_80) {
        case 0:
            break;
        case 1:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].deslizamiento_caja_item_y, 0x40, 8) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_80++;
            }
            break;
        case 2:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].deslizamiento_caja_item_y, 0x38, 8) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_80++;
            }
            break;
        case 3:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].deslizamiento_caja_item_y, 0x40, 8) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_80++;
            }
            break;
        case 4:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].deslizamiento_caja_item_y, 0x38, 8) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_80++;
            }
            break;
        case 5:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].deslizamiento_caja_item_y, 0x40, 8) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_80++;
            }
            break;
        case 6:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].deslizamiento_caja_item_y, 0x38, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_80++;
            }
            break;
        case 7:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].deslizamiento_caja_item_y, 0x40, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_80++;
            }
            break;
        case 8:
            h_ud_jugador[JUGADOR_UNO].desconocido_80 = 0;
            break;
    }
    switch (h_ud_jugador[JUGADOR_UNO].desconocido_7A) {
        case 0:
            break;
        case 1:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].temporizador_x, 0xE4, 0x10) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7A++;
            }
            break;
        case 2:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].temporizador_x, 0xF4, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7A++;
            }
            break;
        case 3:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].temporizador_x, 0xE4, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7A++;
            }
            break;
        case 4:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].temporizador_x, 0xEC, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7A++;
            }
            break;
        case 5:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].temporizador_x, 0xE4, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7A++;
            }
            break;
        case 6:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].temporizador_x, 0xE8, 2) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7A++;
            }
            break;
        case 7:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].temporizador_x, 0xE4, 2) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7A++;
            }
            break;
        case 8:
            h_ud_jugador[JUGADOR_UNO].desconocido_7A = 0;
            break;
    }
    switch (h_ud_jugador[JUGADOR_UNO].desconocido_7D) {
        case 0:
            break;
        case 1:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_x, 0x53, 0x10) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7D++;
            }
            break;
        case 2:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_x, 0x43, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7D++;
            }
            break;
        case 3:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_x, 0x53, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7D++;
            }
            break;
        case 4:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_x, 0x4B, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7D++;
            }
            break;
        case 5:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_x, 0x53, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7D++;
            }
            break;
        case 6:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_x, 0x4F, 2) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7D++;
            }
            break;
        case 7:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_x, 0x53, 2) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7D++;
            }
            break;
        case 8:
            h_ud_jugador[JUGADOR_UNO].desconocido_7D = 0;
            break;
    }
    dato_8018CFEC = (f32) (h_ud_jugador[JUGADOR_UNO].velocimetro_x + 0x18);
    dato_8018CFF4 = (f32) (h_ud_jugador[JUGADOR_UNO].velocimetro_y + 6);
    switch (h_ud_jugador[JUGADOR_UNO].desconocido_7B) {
        case 0:
            break;
        case 1:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_1, 0xE4, 0x10) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7B++;
            }
            break;
        case 2:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_1, 0xF4, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7B++;
            }
            break;
        case 3:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_1, 0xE4, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7B++;
            }
            break;
        case 4:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_1, 0xEC, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7B++;
            }
            break;
        case 5:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_1, 0xE4, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7B++;
            }
            break;
        case 6:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_1, 0xE8, 2) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7B++;
            }
            break;
        case 7:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_1, 0xE4, 2) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7B++;
            }
            break;
        case 8:
            h_ud_jugador[JUGADOR_UNO].desconocido_7B = 0;
            break;
    }
    switch (h_ud_jugador[JUGADOR_UNO].desconocido_7E) {
        case 0:
            break;
        case 1:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_despues_imagen_1_x, 0x53, 0x10) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7E++;
            }
            break;
        case 2:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_despues_imagen_1_x, 0x43, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7E++;
            }
            break;
        case 3:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_despues_imagen_1_x, 0x53, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7E++;
            }
            break;
        case 4:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_despues_imagen_1_x, 0x4B, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7E++;
            }
            break;
        case 5:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_despues_imagen_1_x, 0x53, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7E++;
            }
            break;
        case 6:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_despues_imagen_1_x, 0x4F, 2) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7E++;
            }
            break;
        case 7:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_despues_imagen_1_x, 0x53, 2) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7E++;
            }
            break;
        case 8:
            h_ud_jugador[JUGADOR_UNO].desconocido_7E = 0;
            break;
    }
    switch (h_ud_jugador[JUGADOR_UNO].desconocido_7C) {
        case 0:
            break;
        case 1:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_2, 0xE4, 0x10) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7C++;
            }
            break;
        case 2:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_2, 0xF4, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7C++;
            }
            break;
        case 3:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_2, 0xE4, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7C++;
            }
            break;
        case 4:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_2, 0xEC, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7C++;
            }
            break;
        case 5:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_2, 0xE4, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7C++;
            }
            break;
        case 6:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_2, 0xE8, 2) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7C++;
            }
            break;
        case 7:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_2, 0xE4, 2) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7C++;
            }
            break;
        case 8:
            h_ud_jugador[JUGADOR_UNO].desconocido_7C = 0;
            break;
    }
    switch (h_ud_jugador[JUGADOR_UNO].desconocido_7F) {
        case 0:
            break;
        case 1:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_despues_imagen_2_x, 0x53, 0x10) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7F++;
            }
            break;
        case 2:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_despues_imagen_2_x, 0x43, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7F++;
            }
            break;
        case 3:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_despues_imagen_2_x, 0x53, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7F++;
            }
            break;
        case 4:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_despues_imagen_2_x, 0x4B, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7F++;
            }
            break;
        case 5:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_despues_imagen_2_x, 0x53, 4) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7F++;
            }
            break;
        case 6:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_despues_imagen_2_x, 0x4F, 2) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7F++;
            }
            break;
        case 7:
            if (paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].vuelta_despues_imagen_2_x, 0x53, 2) != 0) {
                h_ud_jugador[JUGADOR_UNO].desconocido_7F++;
            }
            break;
        case 8:
            h_ud_jugador[JUGADOR_UNO].desconocido_7F = 0;
            break;
    }
}

void funcion_8005B7A0(void) {
    f32 temporal_f0;
    f32* temporal_s2;
    f32* temporal_s3;
    f32* temporal_s4;
    SIN_USO f32* variable_s1;
    s32 variable_s0;

    paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_1, 0xE4, 0x10);
    paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_2, 0xE4, 0x10);
    paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_finalizacion_vuelta_3, 0xE4, 0x10);
    paso_s16_hacia(&h_ud_jugador[JUGADOR_UNO].tiempo_x_total, 0xE4, 0x10);
    for (variable_s0 = 0; variable_s0 < JUGADORES_NUM; variable_s0++) {
        temporal_s2 = &dato_8018D028[variable_s0];
        temporal_s3 = &dato_8018D0C8[variable_s0];
        temporal_s4 = &dato_8018D078[variable_s0];
        if (dato_8018D050[variable_s0] >= 0.0f) {
            paso_f32_hacia(temporal_s2, *temporal_s3, *temporal_s4);
            temporal_f0 = *temporal_s2;
            if (temporal_f0 == *temporal_s3) {
                *temporal_s4 = 0.0f;
            }
            if ((f64) temporal_f0 <= -32.0) {
                dato_8018D050[variable_s0] = -32.0f;
            }
        }
    }
}

void funcion_8005B914(void) {
    s32 i;
    SIN_USO s32 desconocido;

    switch (dato_8018D1CC) {
        case 0:
            break;
        case 0x1:
            funcion_8005AAF0();
            break;
        case 0x2:
            if (seleccion_modo == CONTRARRELOJ) {
                h_ud_jugador[JUGADOR_UNO].desconocido_80 = 1;
            }
            h_ud_jugador[JUGADOR_UNO].unk_78 = 1;
            h_ud_jugador[JUGADOR_UNO].desconocido_7A = 1;
            h_ud_jugador[JUGADOR_UNO].desconocido_7D = 1;
            funcion_8005AA4C();
            break;
        case 0x3:
            funcion_8005AA94(0);
            break;
        case 0x4:
            h_ud_jugador[JUGADOR_UNO].desconocido_7B = 1;
            h_ud_jugador[JUGADOR_UNO].desconocido_7E = 1;
            funcion_8005AA4C();
            break;
        case 0x5:
            funcion_8005AA94(0);
            break;
        case 0x6:
            h_ud_jugador[JUGADOR_UNO].desconocido_7C = 1;
            h_ud_jugador[JUGADOR_UNO].desconocido_7F = 1;
            funcion_8005AA4C();
            funcion_8005AA80();
            break;
        case 0x14:
            dato_8018D078[0] = 16.0f;
            funcion_8005AA4C();
            break;
        case 0x15:
            funcion_8005AA94(4);
            break;
        case 0x16:
            dato_8018D078[1] = 16.0f;
            funcion_8005AA4C();
            break;
        case 0x17:
            funcion_8005AA94(4);
            break;
        case 0x18:
            dato_8018D078[2] = 16.0f;
            funcion_8005AA4C();
            break;
        case 0x19:
            funcion_8005AA94(4);
            break;
        case 0x1A:
            dato_8018D078[3] = 16.0f;
            funcion_8005AA4C();
            break;
        case 0x1B:
            funcion_8005AA94(0xA);
            break;
        case 0x1C:
            funcion_8005AA80();
            break;
        case 0x64:
            funcion_8005AA4C();
            break;
        case 0x65:
            funcion_8005AA94(0x3A);
            break;
        case 0x66:
            dato_8018D078[0] = -8.0f;
            dato_8018D0C8[0] = -32.0f;
            funcion_8005AA4C();
            break;
        case 0x67:
            funcion_8005AA94(4);
            break;
        case 0x68:
            dato_8018D078[1] = -8.0f;
            dato_8018D0C8[1] = -32.0f;
            funcion_8005AA4C();
            break;
        case 0x69:
            funcion_8005AA94(4);
            break;
        case 0x6A:
            dato_8018D078[2] = -8.0f;
            dato_8018D0C8[2] = -32.0f;
            funcion_8005AA4C();
            break;
        case 0x6B:
            funcion_8005AA94(4);
            break;
        case 0x6C:
            dato_8018D078[3] = -8.0f;
            dato_8018D0C8[3] = -32.0f;
            funcion_8005AA4C();
            break;
        case 0x6D:
            funcion_8005AA94(0xA);
            break;
        case 0x6E:
            for (i = 0; i < JUGADORES_NUM; i += 4) {
                dato_8018D050[i] = -32.0f;
                dato_8018D050[i + 1] = -32.0f;
                dato_8018D050[i + 2] = -32.0f;
                dato_8018D050[i + 3] = -32.0f;
            }
            dato_8018D028[0] = 360.0f;
            dato_8018D050[0] = 110.0f;
            dato_8018D0C8[0] = 44.0f;
            dato_8018D078[0] = -16.0f;
            dato_801657E2 = 1;
            funcion_8005AA4C();
            break;
        case 0x6F:
            funcion_8005AA94(4);
            break;
        case 0x70:
            dato_8018D028[1] = 360.0f;
            dato_8018D050[1] = 110.0f;
            dato_8018D0C8[1] = 76.0f;
            dato_8018D078[1] = -16.0f;
            funcion_8005AA4C();
            break;
        case 0x71:
            funcion_8005AA94(4);
            break;
        case 0x72:
            dato_8018D028[2] = 360.0f;
            dato_8018D050[2] = 110.0f;
            dato_8018D0C8[2] = 108.0f;
            dato_8018D078[2] = -16.0f;
            funcion_8005AA4C();
            break;
        case 0x73:
            funcion_8005AA94(4);
            break;
        case 0x74:
            dato_8018D028[3] = 360.0f;
            dato_8018D050[3] = 110.0f;
            dato_8018D0C8[3] = 140.0f;
            dato_8018D078[3] = -16.0f;
            funcion_8005AA4C();
            break;
        case 0x75:
            funcion_8005AA94(4);
            break;
        case 0x76:
            dato_8018D028[4] = 360.0f;
            dato_8018D050[4] = 110.0f;
            dato_8018D0C8[4] = 180.0f;
            dato_8018D078[4] = -16.0f;
            funcion_8005AA4C();
            break;
        case 0x77:
            funcion_8005AA94(4);
            break;
        case 0x78:
            dato_8018D028[5] = 360.0f;
            dato_8018D050[5] = 110.0f;
            dato_8018D0C8[5] = 212.0f;
            dato_8018D078[5] = -16.0f;
            funcion_8005AA4C();
            break;
        case 0x79:
            funcion_8005AA94(4);
            break;
        case 0x7A:
            dato_8018D028[6] = 360.0f;
            dato_8018D050[6] = 110.0f;
            dato_8018D0C8[6] = 244.0f;
            dato_8018D078[6] = -16.0f;
            funcion_8005AA4C();
            break;
        case 0x7B:
            funcion_8005AA94(4);
            break;
        case 0x7C:
            dato_8018D028[7] = 360.0f;
            dato_8018D050[7] = 110.0f;
            dato_8018D0C8[7] = 276.0f;
            dato_8018D078[7] = -16.0f;
            funcion_8005AA4C();
            break;
        case 0x7D:
            funcion_8005AA94(0xA);
            break;
        case 0x7E:
            for (i = 0; i < JUGADORES_NUM; i++) {
                dato_8018D078[i] = 0.0f;
            }
            funcion_8005AA4C();
            break;
        case 0x7F:
            funcion_8005AA94(0x82);
            break;
        case 0x80:
            if (gp_actual_carrera_puesto_por_id_jugador[0] < 4) {
                funcion_8005AA6C(0x8C);
            } else {
                funcion_8005AA6C(0x82);
            }
            break;
        case 0x82:
            funcion_8005AA80();
            break;
        case 0x8C:
            dato_8018D078[0] = -16.0f;
            dato_8018D0C8[0] = -32.0f;
            funcion_8005AA4C();
            break;
        case 0x8D:
            funcion_8005AA94(4);
            break;
        case 0x8E:
            dato_8018D078[1] = -16.0f;
            dato_8018D0C8[1] = -32.0f;
            funcion_8005AA4C();
            break;
        case 0x8F:
            funcion_8005AA94(4);
            break;
        case 0x90:
            dato_8018D078[2] = -16.0f;
            dato_8018D0C8[2] = -32.0f;
            funcion_8005AA4C();
            break;
        case 0x91:
            funcion_8005AA94(4);
            break;
        case 0x92:
            dato_8018D078[3] = -16.0f;
            dato_8018D0C8[3] = -32.0f;
            funcion_8005AA4C();
            break;
        case 0x93:
            funcion_8005AA94(4);
            break;
        case 0x94:
            dato_8018D078[4] = -16.0f;
            dato_8018D0C8[4] = -32.0f;
            funcion_8005AA4C();
            break;
        case 0x95:
            funcion_8005AA94(4);
            break;
        case 0x96:
            dato_8018D078[5] = -16.0f;
            dato_8018D0C8[5] = -32.0f;
            funcion_8005AA4C();
            break;
        case 0x97:
            funcion_8005AA94(4);
            break;
        case 0x98:
            dato_8018D078[6] = -16.0f;
            dato_8018D0C8[6] = -32.0f;
            funcion_8005AA4C();
            break;
        case 0x99:
            funcion_8005AA94(4);
            break;
        case 0x9A:
            dato_8018D078[7] = -16.0f;
            dato_8018D0C8[7] = -32.0f;
            funcion_8005AA4C();
            break;
        case 0x9B:
            funcion_8005AA94(0x14);
            break;
        case 0x9C:
            funcion_8005AA80();
            break;
    }
    if (dato_8018D1CC < 0x64) {
        funcion_8005AB60();
    } else if (dato_8018D1CC < 0xC8) {
        funcion_8005B7A0();
    }
    if ((dato_8018D1CC != 0) && (dato_8018D1CC >= 0x14) && (dato_8018D1CC < 0x1E)) {
        for (i = 0; i < 4; i++) {
            paso_f32_hacia(&dato_8018D028[i], dato_8018D0C8[i], dato_8018D078[i]);
            if (dato_8018D028[i] == dato_8018D0C8[i]) {
                dato_8018D078[i] = 0.0f;
            }
        }
    }
}

void funcion_8005C360(f32 parametro0) {
    if (!h_ud_jugador[JUGADOR_UNO].desconocido_79) {
        u16 v;
        if (parametro0 < 10.0) {
            v = (u16) (128.0f * parametro0) + 0xDD00;
        } else if (parametro0 < 20.0) {
            v = (u16) ((parametro0 - 10.0) * 256.0) + 0xE200;
        } else {
            v = (u16) ((parametro0 - 20.0) * 268.8) + 0xEC00;
        }
        if (parametro0 == dato_8018CFE4) {
            if (parametro0 > 5.0f) {
                if (++dato_801657E7 == 8) {
                    dato_801657E7 = 0;
                }
            } else {
                dato_801657E7 = 0;
            }
        }
        dato_8016579E = v + dato_800E55A0[dato_801657E7];
        dato_8018CFE4 = parametro0;
    }
}

void funcion_8005C64C(SIN_USO s32* parametro0) {
}

void funcion_8005C654(s32* parametro0) {
    *parametro0 = 0;
}

void funcion_8005C65C(s32 parametro0) {
    dato_8018D2C8[parametro0] = 1;
}

void funcion_8005C674(s8 index, s16* x, s16* y, s16* z) {
    s16* orig_ = &dato_800E4730[index * 3];
    *x = *orig_++;
    *y = *orig_++;
    *z = *orig_++;
}

void funcion_8005C6B4(s8 parametro0, s16* parametro1, s16* parametro2, s16* parametro3) {
    switch (parametro0) {
        case 0:
            *parametro1 = 0xFF;
            *parametro2 = 0x40;
            *parametro3 = 0x40;
            break;
        case 1:
            *parametro1 = 0xFF;
            *parametro2 = 0xFF;
            *parametro3 = 0x40;
            break;
        case 2:
            *parametro1 = 0x40;
            *parametro2 = 0x40;
            *parametro3 = 0xFF;
            break;
    }
}

void funcion_8005C728(void) {
    s16 x;
    s16 y;
    s16 z;
    s32 temporal_t7;

    temporal_t7 = ++dato_8018D400;
    dato_8018D40C = temporal_t7 & 0x3F;
    dato_8018D410 = temporal_t7 & 0x1F;
    dato_80165590 = temporal_t7 & 0xF;
    dato_80165594 = temporal_t7 & 7;
    dato_80165598 = temporal_t7 & 3;
    dato_8016559C = temporal_t7 & 1;
    if (dato_8018D40C == 0) {
        dato_801655A4 += 1;
        dato_801655D8 ^= 1;
    }
    if (dato_8018D410 == 0) {
        dato_801655AC += 1;
        dato_801655E8 ^= 1;
    }
    if (dato_80165590 == 0) {
        dato_801655B4 += 1;
        dato_801655F8 ^= 1;
    }
    if (dato_80165594 == 0) {
        dato_801655BC += 1;
        dato_80165608 ^= 1;
    }
    if (dato_80165598 == 0) {
        dato_801655C4 += 1;
        dato_80165618 ^= 1;
    }
    if (dato_8016559C == 0) {
        dato_801655CC += 1;
        dato_80165628 ^= 1;
    }
    if (--dato_8018D2AC < 0) {
        dato_8018D2AC = 0;
    }
    dato_801658A8 += 1;
    if (dato_801658A8 >= 7) {
        dato_801658A8 = 0;
    }
    funcion_8005C674(dato_801658A8, &x, &y, &z);
    dato_801656C0 = x / 2;
    dato_801656D0 = y / 2;
    dato_801656E0 = z / 2;
    funcion_8005C980();
}

void funcion_8005C980(void) {
    s32 variable_v0;
    s32 sp0;
    s32 temporal_v1;
    for (variable_v0 = 0; variable_v0 < JUGADORES_NUM; variable_v0++) {
        temporal_v1 = gp_actual_carrera_puesto_por_id_jugador[variable_v0];
        if (dato_80165590 == 0) {
            dato_8018CF98[variable_v0] = temporal_v1;
        }
        dato_8018CF28[temporal_v1] = &jugador_uno[sp0];
        if (sp0 == 0) {
            dato_80165794 = temporal_v1;
        }
    }

    for (variable_v0 = 0; variable_v0 < JUGADORES_NUM; variable_v0++) {
        sp0 = gp_actual_carrera_jugador_id_por_puesto[variable_v0];
        dato_8018CF50[variable_v0] = sp0;
        if (dato_80165590 == 0) {
            gp_actual_carrera_personaje_id_por_puesto[variable_v0] = (jugador_uno + sp0)->id_personaje;
        }
    }

    if (--dato_8018D314 <= 0) {
        dato_8018D314 = dato_8018D3F4;
        dato_8018D3E4 = dato_800E55D0[dato_8018D3F8][0];
        dato_8018D3E8 = dato_800E55D0[dato_8018D3F8][1];
        dato_8018D3EC = dato_800E55D0[dato_8018D3F8][2];
        if (++dato_8018D3F8 == 6) {
            dato_8018D3F8 = 0;
        }
    }
}
