// Tablas cpu

extern s32 dato_8018D168;

s16 cpu_para_mario[] = { LUIGI, YOSHI, TOAD, DK, WARIO, PEACH, BOWSER, 0 };

s16 cpu_para_luigi[] = { MARIO, YOSHI, TOAD, DK, WARIO, PEACH, BOWSER, 0 };

s16 cpu_para_yoshi[] = { MARIO, LUIGI, TOAD, DK, WARIO, PEACH, BOWSER, 0 };

s16 cpu_para_toad[] = { MARIO, LUIGI, YOSHI, DK, WARIO, PEACH, BOWSER, 0 };

s16 cpu_para_dk[] = { MARIO, LUIGI, YOSHI, TOAD, WARIO, PEACH, BOWSER, 0 };

s16 cpu_para_wario[] = { MARIO, LUIGI, YOSHI, TOAD, DK, PEACH, BOWSER, 0 };

s16 cpu_para_peach[] = { MARIO, LUIGI, YOSHI, TOAD, DK, WARIO, BOWSER, 0 };

s16 cpu_para_bowser[] = { MARIO, LUIGI, YOSHI, TOAD, DK, WARIO, PEACH, 0 };

s16* cpu_para_jugador[] = { cpu_para_mario, cpu_para_luigi, cpu_para_yoshi, cpu_para_toad,
                         cpu_para_dk,    cpu_para_wario, cpu_para_peach, cpu_para_bowser };

s16 cpu_para_mario_y_luigi[] = { YOSHI, TOAD, DK, WARIO, PEACH, BOWSER };

s16 cpu_para_mario_y_yoshi[] = { LUIGI, TOAD, DK, WARIO, PEACH, BOWSER };

s16 cpu_para_mario_y_toad[] = { LUIGI, YOSHI, DK, WARIO, PEACH, BOWSER };

s16 cpu_para_mario_y_dk[] = { LUIGI, YOSHI, TOAD, WARIO, PEACH, BOWSER };

s16 cpu_para_mario_y_wario[] = { LUIGI, YOSHI, TOAD, DK, PEACH, BOWSER };

s16 cpu_para_mario_y_peach[] = { LUIGI, YOSHI, TOAD, DK, WARIO, BOWSER };

s16 cpu_para_mario_y_bowser[] = { LUIGI, YOSHI, TOAD, DK, WARIO, PEACH };

s16 cpu_para_luigi_y_mario[] = { YOSHI, TOAD, DK, WARIO, PEACH, BOWSER };

s16 cpu_para_luigi_y_yoshi[] = { MARIO, TOAD, DK, WARIO, PEACH, BOWSER };

s16 cpu_para_luigi_y_toad[] = { MARIO, YOSHI, DK, WARIO, PEACH, BOWSER };

s16 cpu_para_luigi_y_dk[] = { MARIO, YOSHI, TOAD, WARIO, PEACH, BOWSER };

s16 cpu_para_luigi_y_wario[] = { MARIO, YOSHI, TOAD, DK, PEACH, BOWSER };

s16 cpu_para_luigi_y_peach[] = { MARIO, YOSHI, TOAD, DK, WARIO, BOWSER };

s16 cpu_para_luigi_y_bowser[] = { MARIO, YOSHI, TOAD, DK, WARIO, PEACH };

s16 cpu_para_yoshi_y_mario[] = { LUIGI, TOAD, DK, WARIO, PEACH, BOWSER };

s16 cpu_para_yoshi_y_luigi[] = { MARIO, TOAD, DK, WARIO, PEACH, BOWSER };

s16 cpu_para_yoshi_y_toad[] = { MARIO, LUIGI, DK, WARIO, PEACH, BOWSER };

s16 cpu_para_yoshi_y_dk[] = { MARIO, LUIGI, TOAD, WARIO, PEACH, BOWSER };

s16 cpu_para_yoshi_y_wario[] = { MARIO, LUIGI, TOAD, DK, PEACH, BOWSER };

s16 cpu_para_yoshi_y_peach[] = { MARIO, LUIGI, TOAD, DK, WARIO, BOWSER };

s16 cpu_para_yoshi_y_bowser[] = { MARIO, LUIGI, TOAD, DK, WARIO, PEACH };

s16 cpu_para_toad_y_mario[] = { LUIGI, YOSHI, DK, WARIO, PEACH, BOWSER };

s16 cpu_para_toad_y_luigi[] = { MARIO, YOSHI, DK, WARIO, PEACH, BOWSER };

s16 cpu_para_toad_y_yoshi[] = { MARIO, LUIGI, DK, WARIO, PEACH, BOWSER };

s16 cpu_para_toad_y_dk[] = { MARIO, LUIGI, YOSHI, WARIO, PEACH, BOWSER };

s16 cpu_para_toad_y_wario[] = { MARIO, LUIGI, YOSHI, DK, PEACH, BOWSER };

s16 cpu_para_toad_y_peach[] = { MARIO, LUIGI, YOSHI, DK, WARIO, BOWSER };

s16 cpu_para_toad_y_bowser[] = { MARIO, LUIGI, YOSHI, DK, WARIO, PEACH };

s16 cpu_para_dk_y_mario[] = { LUIGI, YOSHI, TOAD, WARIO, PEACH, BOWSER };

s16 cpu_para_dk_y_luigi[] = { MARIO, YOSHI, TOAD, WARIO, PEACH, BOWSER };

s16 cpu_para_dk_y_toad[] = { MARIO, LUIGI, TOAD, WARIO, PEACH, BOWSER };

s16 cpu_para_dk_y_yoshi[] = { MARIO, LUIGI, YOSHI, WARIO, PEACH, BOWSER };

s16 cpu_para_dk_y_wario[] = { MARIO, LUIGI, YOSHI, TOAD, PEACH, BOWSER };

s16 cpu_para_dk_y_peach[] = { MARIO, LUIGI, YOSHI, TOAD, WARIO, BOWSER };

s16 cpu_para_dk_y_bowser[] = { MARIO, LUIGI, YOSHI, TOAD, WARIO, PEACH };

s16 cpu_para_wario_y_mario[] = { LUIGI, YOSHI, TOAD, DK, PEACH, BOWSER };

s16 cpu_para_wario_y_luigi[] = { MARIO, YOSHI, TOAD, DK, PEACH, BOWSER };

s16 cpu_para_wario_y_yoshi[] = { MARIO, LUIGI, TOAD, DK, PEACH, BOWSER };

s16 cpu_para_wario_y_dk[] = { MARIO, LUIGI, YOSHI, TOAD, PEACH, BOWSER };

s16 cpu_para_wario_y_toad[] = { MARIO, LUIGI, YOSHI, DK, PEACH, BOWSER };

s16 cpu_para_wario_y_peach[] = { MARIO, LUIGI, YOSHI, TOAD, DK, BOWSER };

s16 cpu_para_wario_y_bowser[] = { MARIO, LUIGI, YOSHI, TOAD, DK, PEACH };

s16 cpu_para_peach_y_mario[] = { LUIGI, YOSHI, TOAD, DK, WARIO, BOWSER };

s16 cpu_para_peach_y_luigi[] = { MARIO, YOSHI, TOAD, DK, WARIO, BOWSER };

s16 cpu_para_peach_y_yoshi[] = { MARIO, LUIGI, TOAD, DK, WARIO, BOWSER };

s16 cpu_para_peach_y_dk[] = { MARIO, LUIGI, YOSHI, TOAD, WARIO, BOWSER };

s16 cpu_para_peach_y_wario[] = { MARIO, LUIGI, YOSHI, TOAD, DK, BOWSER };

s16 cpu_para_peach_y_toad[] = { MARIO, LUIGI, YOSHI, DK, WARIO, BOWSER };

s16 cpu_para_peach_y_bowser[] = { MARIO, LUIGI, YOSHI, TOAD, DK, WARIO };

s16 cpu_para_bowser_y_mario[] = { LUIGI, YOSHI, TOAD, DK, WARIO, PEACH };

s16 cpu_para_bowser_y_luigi[] = { MARIO, YOSHI, TOAD, DK, WARIO, PEACH };

s16 cpu_para_bowser_y_yoshi[] = { MARIO, LUIGI, TOAD, DK, WARIO, PEACH };

s16 cpu_para_bowser_y_dk[] = { MARIO, LUIGI, YOSHI, TOAD, WARIO, PEACH };

s16 cpu_para_bowser_y_wario[] = { MARIO, LUIGI, YOSHI, TOAD, DK, PEACH };

s16 cpu_para_bowser_y_toad[] = { MARIO, LUIGI, YOSHI, DK, WARIO, PEACH };

s16 cpu_para_bowser_y_peach[] = { MARIO, LUIGI, YOSHI, TOAD, DK, WARIO };

s16* ufor_cp_lista_mario[] = { cpu_para_mario_y_luigi, cpu_para_mario_y_luigi, cpu_para_mario_y_yoshi, cpu_para_mario_y_toad,
                            cpu_para_mario_y_dk,    cpu_para_mario_y_wario, cpu_para_mario_y_peach, cpu_para_mario_y_bowser };

s16* ufor_cp_lista_luigi[] = { cpu_para_luigi_y_mario, cpu_para_luigi_y_mario, cpu_para_luigi_y_yoshi, cpu_para_luigi_y_toad,
                            cpu_para_luigi_y_dk,    cpu_para_luigi_y_wario, cpu_para_luigi_y_peach, cpu_para_luigi_y_bowser };

s16* ufor_cp_lista_yoshi[] = { cpu_para_yoshi_y_mario, cpu_para_yoshi_y_luigi, cpu_para_yoshi_y_luigi, cpu_para_yoshi_y_toad,
                            cpu_para_yoshi_y_dk,    cpu_para_yoshi_y_wario, cpu_para_yoshi_y_peach, cpu_para_yoshi_y_bowser };

s16* ufor_cp_lista_toad[] = { cpu_para_toad_y_mario, cpu_para_toad_y_luigi, cpu_para_toad_y_yoshi, cpu_para_toad_y_yoshi,
                           cpu_para_toad_y_dk,    cpu_para_toad_y_wario, cpu_para_toad_y_peach, cpu_para_toad_y_bowser };

s16* ufor_cp_lista_dk[] = { cpu_para_dk_y_mario, cpu_para_dk_y_luigi, cpu_para_dk_y_toad,  cpu_para_dk_y_yoshi,
                         cpu_para_dk_y_yoshi, cpu_para_dk_y_wario, cpu_para_dk_y_peach, cpu_para_dk_y_bowser };

s16* ufor_cp_lista_wario[] = { cpu_para_wario_y_mario, cpu_para_wario_y_luigi, cpu_para_wario_y_yoshi, cpu_para_wario_y_toad,
                            cpu_para_wario_y_dk,    cpu_para_wario_y_dk,    cpu_para_wario_y_peach, cpu_para_wario_y_bowser };

s16* ufor_cp_lista_peach[] = { cpu_para_peach_y_mario, cpu_para_peach_y_luigi, cpu_para_peach_y_yoshi, cpu_para_peach_y_toad,
                            cpu_para_peach_y_dk,    cpu_para_peach_y_wario, cpu_para_peach_y_dk,    cpu_para_peach_y_bowser };

s16* ufor_cp_lista_bowser[] = {
    cpu_para_bowser_y_mario, cpu_para_bowser_y_luigi, cpu_para_bowser_y_yoshi, cpu_para_bowser_y_toad,
    cpu_para_bowser_y_dk,    cpu_para_bowser_y_wario, cpu_para_bowser_y_peach, cpu_para_bowser_y_peach
};

s16** cpu_para_dos_jugador[] = { ufor_cp_lista_mario, ufor_cp_lista_luigi, ufor_cp_lista_yoshi, ufor_cp_lista_toad,
                             ufor_cp_lista_dk,    ufor_cp_lista_wario, ufor_cp_lista_peach, ufor_cp_lista_bowser };

s32 obtener_indice_jugador_para_jugador(Jugador* jugador) {
    s32 index;

    if (jugador == jugador_uno) {
        index = 0;
    }
    if (jugador == jugador_dos) {
        index = 1;
    }
    if (jugador == jugador_tres) {
        index = 2;
    }
    if (jugador == jugador_cuatro) {
        index = 3;
    }
    if (jugador == jugador_cinco) {
        index = 4;
    }
    if (jugador == jugador_seis) {
        index = 5;
    }
    if (jugador == jugador_siete) {
        index = 6;
    }
    if (jugador == jugador_ocho) {
        index = 7;
    }
    return index;
}

void funcion_80027DA8(Jugador* jugador, s8 id_jugador) {
    if (dato_8015F890 != 1) {
        if ((jugador->type & jugador_desconocido_0_x10) != jugador_desconocido_0_x10) {
            if (((dato_8018D168 == 1) && ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR)) &&
                ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
                funcion_800C94A4(id_jugador);
                jugador->type |= jugador_desconocido_0_x10;
            } else if ((jugador->type & SECUENCIA_INICIO_JUGADOR) == 0) {
                funcion_800C9A88(id_jugador);
                jugador->type |= jugador_desconocido_0_x10;
            }
        }
    } else if ((jugador->type & jugador_desconocido_0_x10) != jugador_desconocido_0_x10) {
        if ((dato_8018D168 == 1) && (jugador == jugador_uno)) {
            funcion_800C94A4(id_jugador);
            jugador->type |= jugador_desconocido_0_x10;
        } else if ((jugador->type & SECUENCIA_INICIO_JUGADOR) == 0) {
            funcion_800C9A88(id_jugador);
            jugador->type |= jugador_desconocido_0_x10;
        }
    }
}

void funcion_80027EDC(Jugador* jugador, s8 id_jugador) {
    SIN_USO s32 relleno;
    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {

#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
        switch (id_circuito_actual) {
            case CIRCUITO_MARIO_RACEWAY:
                if (((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0x19B) &&
                    ((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0x1B9)) {
                    if (dato_80165300[id_jugador] != 1) {
                        funcion_800CA288(id_jugador, 0x55);
                    }
                    dato_80165300[id_jugador] = 1;
                } else {
                    if (dato_80165300[id_jugador] != 0) {
                        funcion_800CA2B8(id_jugador);
                        dato_80165300[id_jugador] = 0;
                    }
                }
                break;
            case CIRCUITO_CHOCO_MOUNTAIN:
                if (((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0xA0) &&
                    ((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0xB4)) {
                    if (dato_80165300[id_jugador] != 1) {
                        funcion_800CA288(id_jugador, 0x55);
                    }
                    dato_80165300[id_jugador] = 1;
                } else {
                    if (dato_80165300[id_jugador] != 0) {
                        funcion_800CA2B8(id_jugador);
                        dato_80165300[id_jugador] = 0;
                    }
                }
                break;
            case CIRCUITO_BOWSER_CASTLE:
                if (((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0x29) &&
                    ((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0x1D2)) {
                    if (dato_80165300[id_jugador] != 1) {
                        funcion_800CA288(id_jugador, 0x41);
                    }
                    dato_80165300[id_jugador] = 1;
                } else {
                    if (dato_80165300[id_jugador] != 0) {
                        funcion_800CA2B8(id_jugador);
                        dato_80165300[id_jugador] = 0;
                    }
                }
                break;
            case CIRCUITO_BANSHEE_BOARDWALK:
                if (((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0x180) &&
                    ((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0x1E1)) {
                    if (dato_80165300[id_jugador] != 1) {
                        funcion_800CA288(id_jugador, 0x41);
                    }
                    dato_80165300[id_jugador] = 1;
                } else {
                    if (dato_80165300[id_jugador] != 0) {
                        funcion_800CA2B8(id_jugador);
                        dato_80165300[id_jugador] = 0;
                    }
                }
                break;
            case CIRCUITO_LUIGI_RACEWAY:
                if (((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0x145) &&
                    ((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0x18B)) {
                    if (dato_80165300[id_jugador] != 1) {
                        funcion_800CA288(id_jugador, 0x55);
                    }
                    dato_80165300[id_jugador] = 1;
                } else {
                    if (dato_80165300[id_jugador] != 0) {
                        funcion_800CA2B8(id_jugador);
                        dato_80165300[id_jugador] = 0;
                    }
                }
                break;
            case CIRCUITO_TOADS_TURNPIKE:
                if ((jugador->type & MODO_CINEMATICA_JUGADOR) != MODO_CINEMATICA_JUGADOR) {
                    if (dato_80165300[id_jugador] != 1) {
                        funcion_800CA288(id_jugador, 0x1e);
                    }
                    dato_80165300[id_jugador] = 1;
                } else {
                    if (dato_80165300[id_jugador] != 0) {
                        funcion_800CA2B8(id_jugador);
                        dato_80165300[id_jugador] = 0;
                    }
                }
                break;
            case CIRCUITO_SHERBET_LAND:
                if (((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0x11C) &&
                    ((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0x209)) {
                    if (dato_80165300[id_jugador] != 1) {
                        funcion_800CA288(id_jugador, 0x55);
                    }
                    dato_80165300[id_jugador] = 1;
                } else {
                    if (dato_80165300[id_jugador] != 0) {
                        funcion_800CA2B8(id_jugador);
                        dato_80165300[id_jugador] = 0;
                    }
                }
                break;
            case CIRCUITO_DK_JUNGLE:
                if ((((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0) &&
                     ((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0x65)) ||
                    (((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0x14A) &&
                     ((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0x21F))) {
                    if (dato_80165300[id_jugador] != 2) {
                        funcion_800C8F80(id_jugador, 0x0170802D);
                    }
                    dato_80165300[id_jugador] = 2;
                } else {
                    if (((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0x288) &&
                        ((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0x305)) {
                        if (dato_80165300[id_jugador] != 1) {
                            funcion_800CA288(id_jugador, 0x55);
                        }
                        dato_80165300[id_jugador] = 1;
                    } else {
                        if (dato_80165300[id_jugador] != 0) {
                            if (dato_80165300[id_jugador] == 1) {
                                funcion_800CA2B8(id_jugador);
                            }
                            if (dato_80165300[id_jugador] == 2) {
                                funcion_800C9018(id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x70, 0x80, 0x2D));
                            }
                            dato_80165300[id_jugador] = 0;
                        }
                    }
                }
                break;
            default:
                break;
        }
#else

#endif
    } else {
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
        switch (id_circuito_actual) {
            case CIRCUITO_MARIO_RACEWAY:
                if (((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0x19B) &&
                    ((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0x1B9)) {
                    if (dato_80165300[id_jugador] != 1) {
                        funcion_800CA2E4(id_jugador, 0x55);
                    }
                    dato_80165300[id_jugador] = 1;
                } else {
                    if (dato_80165300[id_jugador] != 0) {
                        funcion_800CA30C(id_jugador);
                        dato_80165300[id_jugador] = 0;
                    }
                }
                break;
            case CIRCUITO_CHOCO_MOUNTAIN:
                if (((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0xA0) &&
                    ((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0xB4)) {
                    if (dato_80165300[id_jugador] != 1) {
                        funcion_800CA2E4(id_jugador, 0x55);
                    }
                    dato_80165300[id_jugador] = 1;
                } else {
                    if (dato_80165300[id_jugador] != 0) {
                        funcion_800CA30C(id_jugador);
                        dato_80165300[id_jugador] = 0;
                    }
                }
                break;
            case CIRCUITO_BOWSER_CASTLE:
                if (((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0x29) &&
                    ((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0x1D2)) {
                    if (dato_80165300[id_jugador] != 1) {
                        funcion_800CA2E4(id_jugador, 0x41);
                    }
                    dato_80165300[id_jugador] = 1;
                } else {
                    if (dato_80165300[id_jugador] != 0) {
                        funcion_800CA30C(id_jugador);
                        dato_80165300[id_jugador] = 0;
                    }
                }
                break;
            case CIRCUITO_BANSHEE_BOARDWALK:
                if (((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0x180) &&
                    ((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0x1E1)) {
                    if (dato_80165300[id_jugador] != 1) {
                        funcion_800CA2E4(id_jugador, 0x41);
                    }
                    dato_80165300[id_jugador] = 1;
                } else {
                    if (dato_80165300[id_jugador] != 0) {
                        funcion_800CA30C(id_jugador);
                        dato_80165300[id_jugador] = 0;
                    }
                }
                break;
            case CIRCUITO_LUIGI_RACEWAY:
                if (((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0x145) &&
                    ((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0x18B)) {
                    if (dato_80165300[id_jugador] != 1) {
                        funcion_800CA2E4(id_jugador, 0x55);
                    }
                    dato_80165300[id_jugador] = 1;
                } else {
                    if (dato_80165300[id_jugador] != 0) {
                        funcion_800CA30C(id_jugador);
                        dato_80165300[id_jugador] = 0;
                    }
                }
                break;
            case CIRCUITO_TOADS_TURNPIKE:
                if ((jugador->type & MODO_CINEMATICA_JUGADOR) != MODO_CINEMATICA_JUGADOR) {
                    if (dato_80165300[id_jugador] != 1) {
                        funcion_800CA2E4(id_jugador, 0x1E);
                    }
                    dato_80165300[id_jugador] = 1;
                } else {
                    if (dato_80165300[id_jugador] != 0) {
                        funcion_800CA30C(id_jugador);
                        dato_80165300[id_jugador] = 0;
                    }
                }
                break;
            case CIRCUITO_SHERBET_LAND:
                if (((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0x11C) &&
                    ((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0x209)) {
                    if (dato_80165300[id_jugador] != 1) {
                        funcion_800CA2E4(id_jugador, 0x55);
                    }
                    dato_80165300[id_jugador] = 1;
                } else {
                    if (dato_80165300[id_jugador] != 0) {
                        funcion_800CA30C(id_jugador);
                        dato_80165300[id_jugador] = 0;
                    }
                }
                break;
            case CIRCUITO_DK_JUNGLE:
                if (((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0x288) &&
                    ((s16) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0x305)) {
                    if (dato_80165300[id_jugador] != 1) {
                        funcion_800CA2E4(id_jugador, 0x55);
                    }
                    dato_80165300[id_jugador] = 1;
                } else {
                    if (dato_80165300[id_jugador] != 0) {
                        funcion_800CA30C(id_jugador);
                        dato_80165300[id_jugador] = 0;
                    }
                }
                break;
            default:
                break;
        }
#else

#endif
    }
}

void funcion_80028864(Jugador* jugador, Camara* camara, s8 id_jugador, s8 id_pantalla) {
    u16 es_visible;

    if (!(jugador->type & SECUENCIA_INICIO_JUGADOR)) {
        switch (modo_pantalla_activo) {
            case MODO_PANTALLA_1P:
                es_visible = comprobar_colision_camara_jugador(jugador, camara1, (f32) dato_8016557C, 0.0f);
                break;
            case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
            case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
                es_visible = comprobar_colision_camara_jugador(jugador, camara1, (f32) dato_8016557C, 0.0f);
                if (es_visible == true) {
                    break;
                }
                es_visible = comprobar_colision_camara_jugador(jugador, camara2, (f32) dato_8016557C, 0.0f);
                break;
            case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
                es_visible = comprobar_colision_camara_jugador(jugador, camara1, (f32) dato_8016557C, 0.0f);
                if (es_visible == true) {
                    break;
                }
                es_visible = comprobar_colision_camara_jugador(jugador, camara2, (f32) dato_8016557C, 0.0f);
                if (es_visible == true) {
                    break;
                }
                es_visible = comprobar_colision_camara_jugador(jugador, camara3, (f32) dato_8016557C, 0.0f);
                if (es_visible == true) {
                    break;
                }
                es_visible = comprobar_colision_camara_jugador(jugador, camara4, (f32) dato_8016557C, 0.0f);
                break;
        }
        if ((es_visible == 1) || ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) == INVISIBLE_JUGADOR_O_BOMBA) ||
            (seleccion_modo == BATALLA) || ((jugador->lakitu_props & MANTENIDO_POR_LAKITU) != 0) ||
            (jugador->lakitu_props & LAKITU_ESCENA) ||
            ((*(dato_801633F8 + (id_jugador))) == ((s16) 1U))) {
            jugador->efectos &= ~EFECTO_CARRERA_PERDIDO;
            if (((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
                ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO) ||
                ((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) == GOLPE_POR_CAPARAZON_VERDE_EFECTO) ||
                ((jugador->efectos & TEMPRANO_INICIO_TROMPO_EFECTO) == TEMPRANO_INICIO_TROMPO_EFECTO) ||
                ((jugador->efectos & desconocido_efecto_0_x_80000) == desconocido_efecto_0_x_80000) ||
                ((jugador->efectos & desconocido_efecto_0_x_800000) == desconocido_efecto_0_x_800000) ||
                ((jugador->efectos & EFECTO_ERROR_EXPLOSION) == EFECTO_ERROR_EXPLOSION) ||
                ((jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA) == GOLPE_POR_EFECTO_ESTRELLA) ||
                ((jugador->efectos & EFECTO_GOLPE_RAYO) == EFECTO_GOLPE_RAYO) ||
                (jugador->kart_props & sin_uso_0_x_800)) {
                funcion_8002E594(jugador, camara, id_pantalla, id_jugador);
            } else {
                funcion_8002D268(jugador, camara, id_pantalla, id_jugador);
            }
        } else {
            movimiento_cpu_control(jugador, camara, id_pantalla, id_jugador);
        }
    } else if ((jugador->type & PREPARACION_JUGADOR) == PREPARACION_JUGADOR) {
        funcion_8002D028(jugador, id_jugador);
        funcion_8002F730(jugador, camara, id_pantalla, id_jugador);
    } else if (jugador->type & jugador_desconocido_0_x80) {
        funcion_8002D268(jugador, camara, id_pantalla, id_jugador);
    } else {
        if ((jugador->type & HUMANO_JUGADOR) != HUMANO_JUGADOR) {
            jugador->actual_rapidez = 50.0f;
        }
        jugador->efectos &= ~EFECTO_EN_EL_AIRE;
    }
}

void funcion_80028C44(Jugador* jugador, Camara* camara, s8 id_jugador, s8 id_pantalla) {
    if ((jugador->type & SECUENCIA_INICIO_JUGADOR) == 0) {
        jugador->efectos &= ~EFECTO_CARRERA_PERDIDO;
        if (((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
            ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO) ||
            ((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) == GOLPE_POR_CAPARAZON_VERDE_EFECTO) ||
            ((jugador->efectos & TEMPRANO_INICIO_TROMPO_EFECTO) == TEMPRANO_INICIO_TROMPO_EFECTO) ||
            ((jugador->efectos & desconocido_efecto_0_x_80000) == desconocido_efecto_0_x_80000) ||
            ((jugador->efectos & desconocido_efecto_0_x_800000) == desconocido_efecto_0_x_800000) ||
            ((jugador->efectos & EFECTO_ERROR_EXPLOSION) == EFECTO_ERROR_EXPLOSION) ||
            ((jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA) == GOLPE_POR_EFECTO_ESTRELLA) ||
            ((jugador->efectos & EFECTO_GOLPE_RAYO) == EFECTO_GOLPE_RAYO) ||
            ((jugador->kart_props & sin_uso_0_x_800) != 0)) {
            funcion_8002E594(jugador, camara, id_pantalla, id_jugador);
        } else {
            funcion_8002D268(jugador, camara, id_pantalla, id_jugador);
        }
    } else {
        jugador->efectos &= ~EFECTO_EN_EL_AIRE;
    }
}

void funcion_80028D3C(Jugador* jugador, Camara* camara, s8 id_jugador, s8 id_pantalla) {
    if ((((jugador->type & SECUENCIA_INICIO_JUGADOR) == 0) && (estado_carrera != HECHO_CARRERA)) || (jugador->lakitu_props & 2) != 0 ||
        (jugador->lakitu_props & LAKITU_ESCENA) != 0 ||
        (jugador->efectos & (EFECTO_RAYO | EFECTO_ERROR_EXPLOSION | GOLPE_POR_EFECTO_ESTRELLA | EFECTO_APLASTAMIENTO |
                            EFECTO_APLASTAMIENTO_PUBLICAR | EFECTO_VUELCO_TERRENO | 0xC00 | 0xC0)) != 0) {
        jugador->efectos &= ~EFECTO_CARRERA_PERDIDO;
        if (((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
            ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO) ||
            ((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) == GOLPE_POR_CAPARAZON_VERDE_EFECTO) ||
            ((jugador->efectos & TEMPRANO_INICIO_TROMPO_EFECTO) == TEMPRANO_INICIO_TROMPO_EFECTO) ||
            ((jugador->efectos & desconocido_efecto_0_x_80000) == desconocido_efecto_0_x_80000) ||
            ((jugador->efectos & desconocido_efecto_0_x_800000) == desconocido_efecto_0_x_800000) ||
            ((jugador->efectos & EFECTO_ERROR_EXPLOSION) == EFECTO_ERROR_EXPLOSION) ||
            ((jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA) == GOLPE_POR_EFECTO_ESTRELLA) ||
            ((jugador->efectos & EFECTO_GOLPE_RAYO) == EFECTO_GOLPE_RAYO) ||
            ((jugador->kart_props & sin_uso_0_x_800) != 0)) {
            funcion_8002E594(jugador, camara, id_pantalla, id_jugador);
        } else {
            funcion_8002D268(jugador, camara, id_pantalla, id_jugador);
        }
    } else {
        jugador->efectos = jugador->efectos & ~EFECTO_EN_EL_AIRE;
    }
}

void funcion_80028E70(Jugador* jugador, Camara* camara, s8 id_jugador, s8 id_pantalla) {
    if ((jugador->type & EXISTE_JUGADOR) == EXISTE_JUGADOR) {
        switch (estado_juego) {
            case FINAL:
                if (!(jugador->type & SECUENCIA_INICIO_JUGADOR)) {
                    funcion_80038C6C(jugador, camara, id_pantalla, id_jugador);
                } else {
                    jugador->efectos &= ~EFECTO_EN_EL_AIRE;
                }
                break;
            default:
                funcion_80027DA8(jugador, id_jugador);
                switch (seleccion_modo) {
                    case CONTRARRELOJ:
                    case VERSUS:
                        funcion_80028C44(jugador, camara, id_jugador, id_pantalla);
                        break;
                    case BATALLA:
                        funcion_80028D3C(jugador, camara, id_jugador, id_pantalla);
                        break;
                    default:
                        funcion_80028864(jugador, camara, id_jugador, id_pantalla);
                        break;
                }
                break;
        }
    }
}

SIN_USO void funcion_80028F5C(SIN_USO s32 parametro0, SIN_USO s32 parametro1, SIN_USO s32 parametro2, SIN_USO s32 parametro3) {
}

void funcion_80028F70(void) {
    cantidad_efecto_matriz = 0;
    funcion_80028E70(copia_jugador_uno, camara1, 0, 0);
    funcion_80028E70(jugador_dos, camara1, 1, 0);
    funcion_80028E70(jugador_tres, camara1, 2, 0);
    funcion_80028E70(jugador_cuatro, camara1, 3, 0);
    funcion_80028E70(jugador_cinco, camara1, 4, 0);
    funcion_80028E70(jugador_seis, camara1, 5, 0);
    funcion_80028E70(jugador_siete, camara1, 6, 0);
    funcion_80028E70(jugador_ocho, camara1, 7, 0);
}

void funcion_80029060(void) {
    cantidad_efecto_matriz = 0;
    funcion_80028E70(copia_jugador_uno, camara1, 0, 0);
    funcion_80028E70(jugador_dos, camara1, 1, 0);
    funcion_80028E70(jugador_tres, camara1, 2, 0);
    funcion_80028E70(jugador_cuatro, camara1, 3, 0);
    funcion_80028E70(jugador_cinco, camara1, 4, 0);
    funcion_80028E70(jugador_seis, camara1, 5, 0);
    funcion_80028E70(jugador_siete, camara1, 6, 0);
    funcion_80028E70(jugador_ocho, camara1, 7, 0);
}

void funcion_80029150(void) {
}

void funcion_80029158(void) {
    cantidad_efecto_matriz = 0;
    funcion_80028E70(copia_jugador_uno, camara1, 0, 0);
    funcion_80028E70(jugador_dos, camara1, 1, 0);
    funcion_80028E70(jugador_tres, camara1, 2, 0);
    funcion_80028E70(jugador_cuatro, camara1, 3, 0);
}

void funcion_800291E8(void) {
}

void funcion_800291F0(void) {
}

void funcion_800291F8(void) {
}

void funcion_80029200(Jugador* jugador, s8 id_pantalla) {
    if ((s32) jugador->acel_pendiente < -0x71B) {
        jugador->anim_selector_grupo[id_pantalla] = 0;
    }
    if (((s32) jugador->acel_pendiente < -0x4F9) && ((s32) jugador->acel_pendiente > -GRADOS(10))) {
        jugador->anim_selector_grupo[id_pantalla] = 1;
    }
    if ((jugador->acel_pendiente <= -GRADOS(3)) && (jugador->acel_pendiente > -GRADOS(7))) {
        jugador->anim_selector_grupo[id_pantalla] = 2;
    }
    if ((jugador->acel_pendiente <= -GRADOS(2)) && (jugador->acel_pendiente > -GRADOS(3))) {
        jugador->anim_selector_grupo[id_pantalla] = 3;
    }
    if ((jugador->acel_pendiente < GRADOS(2)) && (jugador->acel_pendiente > -GRADOS(2))) {
        jugador->anim_selector_grupo[id_pantalla] = 4;
    }
    if ((jugador->acel_pendiente >= GRADOS(2)) && (jugador->acel_pendiente < GRADOS(3))) {
        jugador->anim_selector_grupo[id_pantalla] = 5;
    }
    if ((jugador->acel_pendiente >= GRADOS(3)) && (jugador->acel_pendiente < GRADOS(7))) {
        jugador->anim_selector_grupo[id_pantalla] = 6;
    }
    if ((jugador->acel_pendiente >= GRADOS(7)) && (jugador->acel_pendiente < GRADOS(10))) {
        jugador->anim_selector_grupo[id_pantalla] = 7;
    }
    if (jugador->acel_pendiente >= GRADOS(10)) {
        jugador->anim_selector_grupo[id_pantalla] = 8;
    }
}

void funcion_8002934C(Jugador* jugador, Camara* camara, s8 id_pantalla, s8 id_jugador) {
    SIN_USO s32 relleno[2];
    f32 temporal_f0;
    f32 temporal_f2;
    SIN_USO s32 relleno2[3];
    f32 variable_f0;
    s16 temporal_a0;
    s32 temporal_a0_2;
    s32 variable_a1;
    s32 variable_t0;
    u16 variable_a0;

    jugador->desconocido_048[id_pantalla] = atan2s(jugador->pos[0] - camara->pos[0], jugador->pos[2] - camara->pos[2]);
    jugador->anim_frame_selector[id_pantalla] =
        (u16) ((((jugador->desconocido_048[id_pantalla]) + jugador->rotacion[1] + jugador->desconocido_0C0))) / 128;

    temporal_f2 = (tamanio_personaje[jugador->id_personaje] * 18.0f) * jugador->size;
    temporal_f0 = jugador->desconocido_230 - jugador->desconocido_23C;
    if ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) {
        if ((jugador->efectos & EFECTO_RAYO) == EFECTO_RAYO) {
            jugador->desconocido_0CC[id_pantalla] = (s16) ((s32) (((f64) atan1s(temporal_f0 / temporal_f2)) * 1.6));
        } else {
            jugador->desconocido_0CC[id_pantalla] = atan1s(temporal_f0 / temporal_f2) * 2;
        }
    }
    if ((jugador->efectos & EFECTO_APLASTAMIENTO) == EFECTO_APLASTAMIENTO) {
        jugador->desconocido_0CC[id_pantalla] = (s16) ((s32) jugador->desconocido_D9C);
    }
    if ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) {
        temporal_f0 = jugador->desconocido_1F8 - jugador->desconocido_1FC;
        jugador->desconocido_0D4[id_pantalla] = (((atan1s(temporal_f0 / temporal_f2)) * 0.9));
    } else {
        if (((jugador->anim_frame_selector[id_pantalla]) >= 0) && ((jugador->anim_frame_selector[id_pantalla]) < 0x101)) {
            variable_f0 = jugador->pos_viejo[1] - jugador->pos[1];
        } else {
            variable_f0 = jugador->pos[1] - jugador->pos_viejo[1];
        }
        jugador->desconocido_0D4[id_pantalla] = (s16) ((s32) (((f64) atan1s(variable_f0 / temporal_f2)) * 0.5));
    }
    if ((jugador->efectos & EFECTO_APLASTAMIENTO) == EFECTO_APLASTAMIENTO) {
        jugador->desconocido_0D4[id_pantalla] = (s16) ((s32) jugador->desconocido_D9C);
    }
    funcion_80029200(jugador, id_pantalla);
    temporal_a0 = ((jugador->desconocido_048[id_pantalla] + jugador->rotacion[1]) + jugador->desconocido_0C0);
    temporal_a0 = (s16) jugador->desconocido_0D4[id_pantalla] * senos((u16) temporal_a0) + jugador->desconocido_0CC[id_pantalla] * coss((u16) temporal_a0);
    mover_s16_hacia(&jugador->desconocido_050[id_pantalla], temporal_a0, 0.5f);
    variable_a0 = jugador->anim_frame_selector[id_pantalla];
    jugador->desconocido_002 = jugador->desconocido_002 & (~(desconocido_002_desconocido_0_x4 << (id_pantalla * 4)));
    if (variable_a0 >= 0x101) {
        variable_a0 = 0x201 - variable_a0;
        jugador->desconocido_002 |= (desconocido_002_desconocido_0_x4 << (id_pantalla * 4));
    }
    if (((jugador->efectos & EFECTO_TROMPO_BANANA) != EFECTO_TROMPO_BANANA) &&
        ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) != EFECTO_TROMPO_CONDUCIENDO) &&
        ((jugador->efectos & desconocido_efecto_0_x_80000) != desconocido_efecto_0_x_80000) &&
        ((jugador->efectos & desconocido_efecto_0_x_800000) != desconocido_efecto_0_x_800000) &&
        ((jugador->efectos & EFECTO_GOLPE_RAYO) != EFECTO_GOLPE_RAYO) &&
        (!(jugador->kart_props & sin_uso_0_x_800))) {
        if (variable_a0 < 0x51) {
            variable_a1 = 0x208;
            variable_t0 = 0;
        } else {
            variable_a1 = GRADOS(9);
            variable_t0 = 0xF;
        }
    } else {
        variable_a1 = GRADOS(9);
        variable_t0 = 0;
    }
    if (((jugador->efectos & desconocido_efecto_0_x_80000) == desconocido_efecto_0_x_80000) ||
        ((jugador->efectos & desconocido_efecto_0_x_800000) == desconocido_efecto_0_x_800000) ||
        (jugador->kart_props & sin_uso_0_x_800)) {
        jugador->desconocido_050[id_pantalla] = 0;
    }
    if (((jugador->efectos & EFECTO_EN_EL_AIRE) == EFECTO_EN_EL_AIRE) &&
        ((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == MANTENIDO_POR_LAKITU)) {
        jugador->desconocido_050[id_pantalla] = 0;
    }
    variable_a0 = (jugador->desconocido_048[id_pantalla] + jugador->rotacion[1] + jugador->desconocido_0C0);
    if (((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
        ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO) ||
        ((jugador->efectos & desconocido_efecto_0_x_80000) == desconocido_efecto_0_x_80000) ||
        ((jugador->efectos & desconocido_efecto_0_x_800000) == desconocido_efecto_0_x_800000) ||
        ((jugador->efectos & EFECTO_GOLPE_RAYO) == EFECTO_GOLPE_RAYO) ||
        (jugador->kart_props & sin_uso_0_x_800)) {
        if (variable_a0 >= 0x7FF9) {
            variable_a0 = -variable_a0;
            variable_a0 /= variable_a1;
            if (variable_a0 == 0) {
                variable_a0 = 1;
            }
        } else {
            variable_a0 /= variable_a1;
        }
    } else {
        if (variable_a0 >= 0x7FF9) {
            variable_a0 = (-variable_a0);
        }
        variable_a0 /= variable_a1;
    }
    jugador->anim_frame_selector[id_pantalla] = variable_a0 + variable_t0;
    if ((jugador->anim_frame_selector[id_pantalla]) >= 0x23) {
        jugador->anim_frame_selector[id_pantalla] = 0x22;
    }
    if ((jugador->efectos & EFECTO_TROMPO_BANANA) || (jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) ||
        (jugador->efectos & desconocido_efecto_0_x_80000) || (jugador->efectos & desconocido_efecto_0_x_800000) ||
        (jugador->efectos & EFECTO_GOLPE_RAYO) || (jugador->kart_props & sin_uso_0_x_800)) {

        if ((jugador->anim_frame_selector[id_pantalla]) >= 0x14) {
            jugador->anim_frame_selector[id_pantalla] = 0;
        }
    }
    if ((jugador->anim_selector_grupo[id_pantalla]) >= 9) {
        jugador->anim_selector_grupo[id_pantalla] = 4;
    }
    if (((jugador->efectos & desconocido_efecto_0_x_80000) == desconocido_efecto_0_x_80000) ||
        ((jugador->efectos & desconocido_efecto_0_x_800000) == desconocido_efecto_0_x_800000) ||
        (jugador->kart_props & sin_uso_0_x_800)) {

        jugador->anim_selector_grupo[id_pantalla] = 4;
    }
    if (((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) == GOLPE_POR_CAPARAZON_VERDE_EFECTO) ||
        ((jugador->efectos & EFECTO_ERROR_EXPLOSION) == EFECTO_ERROR_EXPLOSION) ||
        ((jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA) == GOLPE_POR_EFECTO_ESTRELLA) || (jugador->efectos & EFECTO_VUELCO_TERRENO) ||
        (jugador->efectos & EFECTO_TROMPO_BANANA) || (jugador->efectos & EFECTO_TROMPO_CONDUCIENDO)) {

        jugador->desconocido_002 |= ANIMACION_CAMBIANDO << (id_pantalla * 4);
        dato_80165190[id_pantalla][id_jugador] = 1;

        if ((jugador->efectos & EFECTO_TROMPO_BANANA) || (jugador->efectos & EFECTO_TROMPO_CONDUCIENDO)) {
            if ((jugador->anim_frame_selector[id_pantalla] == ultimo_selector_frame_anim[id_pantalla][id_jugador]) &&
                (jugador->anim_selector_grupo[id_pantalla] == ultimo_selector_grupo_anim[id_pantalla][id_jugador])) {
                jugador->desconocido_002 &= ~(ANIMACION_CAMBIANDO << (id_pantalla * 4));
                dato_80165190[id_pantalla][id_jugador] = 1;
            }
        } else if (((jugador->desconocido_0A8) >> 8) == dato_80165150[id_pantalla][id_jugador] >> 8) {
            jugador->desconocido_002 &= ~(ANIMACION_CAMBIANDO << (id_pantalla * 4));
        }
    } else {
        jugador->desconocido_002 |= ANIMACION_CAMBIANDO << (id_pantalla * 4);
        if (((jugador->anim_frame_selector[id_pantalla] == ultimo_selector_frame_anim[id_pantalla][id_jugador]) &&
             (jugador->anim_selector_grupo[id_pantalla] == ultimo_selector_grupo_anim[id_pantalla][id_jugador])) &&
            ((dato_80165190[id_pantalla][id_jugador]) == 0)) {
            jugador->desconocido_002 &= ~(ANIMACION_CAMBIANDO << (id_pantalla * 4));
        }
    }
    temporal_a0_2 = ultimo_selector_frame_anim[id_pantalla][id_jugador] - jugador->anim_frame_selector[id_pantalla];
    if ((temporal_a0_2 >= 0x14) || (temporal_a0_2 < (-0x13))) {
        jugador->desconocido_002 |= ANIMACION_CAMBIANDO << (id_pantalla * 4);
    }
}
