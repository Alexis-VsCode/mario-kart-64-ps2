// Procesar secuencias

void procesar_guion_canal_secuencia(struct CanalSecuencia* sec_canal) {
    struct EstadoGuionM64* estado;
    struct JugadorSecuencia* sec_jugador;
    u8 cmd;
    s8 temporal_;
    u8 lo_bits;
    u16 sp5_a;
    s32 sp38;
    s8 value;
    s32 i;
    u8* sec_datos;

    if (!sec_canal->activado) {
        return;
    }
    if (sec_canal->guion_parada) {
        for (i = 0; i < MAX_CAPAS; i++) {
            if (sec_canal->capas[i] != NULL) {
                sec_canal_capa_proceso_guion(sec_canal->capas[i]);
            }
        }
        return;
    }
    sec_jugador = sec_canal->sec_jugador;
    if (sec_jugador->silenciado && ((sec_canal->comportamiento_silencio & 0x80) != 0)) {
        return;
    }
    if (sec_canal->delay != 0) {
        sec_canal->delay--;
    }
    estado = &sec_canal->estado_guion;
    if (sec_canal->delay == 0) {
        for (;;) {
            cmd = leer_m64_u8(estado);
            if (cmd > 0xc0) {
                switch (cmd) {
                    case 0xFF:
                        if (estado->profundidad) {};
                        if (1) {};
                        if (1) {};
                        if (1) {};
                        if (estado->profundidad == 0) {
                            desactivar_canal_secuencia(sec_canal);
                            goto salida;
                        } else {
                            estado->pc = estado->stack[--estado->profundidad];
                        }
                        break;

                    case 0xFE:
                        goto salida;

                    case 0xFD:
                        sec_canal->delay = leer_comprimido_m64_u16(estado);
                        goto salida;

                    case 0xEA:
                        sec_canal->guion_parada = 1;
                        goto salida;

                    case 0xFC:
                        sp5_a = leer_m64_s16(estado);
                        estado->stack[estado->profundidad++] = estado->pc;
                        estado->pc = sec_jugador->sec_datos + sp5_a;
                        break;

                    case 0xF8:
                        estado->iters_bucle_resto[estado->profundidad] = leer_m64_u8(estado);
                        estado->stack[estado->profundidad] = estado->pc;
                        estado->profundidad += 1;
                        break;

                    case 0xF7:
                        estado->iters_bucle_resto[estado->profundidad - 1]--;
                        if (estado->iters_bucle_resto[estado->profundidad - 1] != 0) {
                            estado->pc = estado->stack[estado->profundidad - 1];
                        } else {
                            estado->profundidad--;
                        }
                        break;

                    case 0xF6:
                        estado->profundidad -= 1;
                        break;

                    case 0xF5:
                    case 0xF9:
                    case 0xFA:
                    case 0xFB:
                        sp5_a = leer_m64_s16(estado);
                        if ((cmd == 0xFA) && (value != 0)) {
                            break;
                        }
                        if ((cmd == 0xF9) && (value >= 0)) {
                            break;
                        }
                        if ((cmd == 0xF5) && (value < 0)) {
                            break;
                        }
                        estado->pc = sec_jugador->sec_datos + sp5_a;
                        break;

                    case 0xF2:
                    case 0xF3:
                    case 0xF4:
                        temporal_ = leer_m64_u8(estado);
                        if ((cmd == 0xF3) && (value != 0)) {
                            break;
                        }
                        if ((cmd == 0xF2) && (value >= 0)) {
                            break;
                        }
                        estado->pc += temporal_;
                        break;

                    case 0xF1:
                        borrar_pool_nota(&sec_canal->pool_nota);
                        relleno_pool_nota(&sec_canal->pool_nota, leer_m64_u8(estado));
                        break;

                    case 0xF0:
                        borrar_pool_nota(&sec_canal->pool_nota);
                        break;

                    case 0xC2:
                        sp5_a = leer_m64_s16(estado);
                        sec_canal->tabla_din = (void*) (sec_jugador->sec_datos + sp5_a);
                        break;

                    case 0xC5:
                        if (value != (-1)) {
                            sec_datos = (*sec_canal->tabla_din)[value];
                            sp38 = (u16) ((sec_datos[0] << 8) + sec_datos[1]);
                            sec_canal->tabla_din = (void*) (sec_jugador->sec_datos + sp38);
                        }
                        break;

                    case 0xEB:
                        cmd = leer_m64_u8(estado);
                        sp38 = ((u16*) conjuntos_banco_al)[sec_jugador->sec_id];
                        lo_bits = *(sp38 + conjuntos_banco_al);
                        cmd = conjuntos_banco_al[(((s32) sp38) + lo_bits) - cmd];
                        if (obtener_banco_o_sec(1, 2, cmd) != NULL) {
                            sec_canal->id_banco = cmd;
                        }

                    case 0xC1:
                        fijar_instrumento(sec_canal, leer_m64_u8(estado));
                        break;

                    case 0xC3:
                        sec_canal->notas_grande = 0;
                        break;

                    case 0xC4:
                        sec_canal->notas_grande = 1;
                        break;

                    case 0xDF:
                        fijar_volumen_canal_secuencia(sec_canal, leer_m64_u8(estado));
                        sec_canal->cambios.como_bitfields.volumen = 1;
                        break;

                    case 0xE0:
                        sec_canal->escala_volumen = ((f32) ((s32) leer_m64_u8(estado))) / 128.0f;
                        sec_canal->cambios.como_bitfields.volumen = 1;
                        break;

                    case 0xDE:
                        sp5_a = leer_m64_s16(estado);
                        sec_canal->escala_frec = ((f32) ((s32) sp5_a)) / 32768.0f;
                        sec_canal->cambios.como_bitfields.escala_frec = 1;
                        break;

                    case 0xD3:
                        cmd = leer_m64_u8(estado) + 127;
                        sec_canal->escala_frec = tono_curva_frecuencia_escala[cmd];
                        sec_canal->cambios.como_bitfields.escala_frec = 1;
                        break;

                    case 0xDD:
                        sec_canal->paneo_nuevo = leer_m64_u8(estado);
                        sec_canal->cambios.como_bitfields.paneo = 1;
                        break;

                    case 0xDC:
                        sec_canal->peso_canal_paneo = leer_m64_u8(estado);
                        sec_canal->cambios.como_bitfields.paneo = 1;
                        break;

                    case 0xDB:
                        temporal_ = *(estado->pc++);
                        sec_canal->trasposicion = temporal_;
                        break;

                    case 0xDA:
                        sp5_a = leer_m64_s16(estado);
                        sec_canal->adsr.envelope = (struct EnvolventeAdsr*) (sec_jugador->sec_datos + sp5_a);
                        break;

                    case 0xD9:
                        sec_canal->adsr.tasa_suelta = leer_m64_u8(estado);
                        break;

                    case 0xD8:
                        sec_canal->objetivo_extension_vibrato = leer_m64_u8(estado) * 8;
                        sec_canal->inicio_extension_vibrato = 0;
                        sec_canal->vibrato_extension_cambio_retardo = 0;
                        break;

                    case 0xD7:
                        sec_canal->inicio_tasa_vibrato = sec_canal->objetivo_tasa_vibrato = leer_m64_u8(estado) * 32;
                        sec_canal->vibrato_tasa_cambio_retardo = 0;
                        break;

                    case 0xE2:
                        sec_canal->inicio_extension_vibrato = leer_m64_u8(estado) * 8;
                        sec_canal->objetivo_extension_vibrato = leer_m64_u8(estado) * 8;
                        sec_canal->vibrato_extension_cambio_retardo = leer_m64_u8(estado) * 0x10;
                        break;

                    case 0xE1:
                        sec_canal->inicio_tasa_vibrato = leer_m64_u8(estado) << 5;
                        sec_canal->objetivo_tasa_vibrato = leer_m64_u8(estado) << 5;
                        sec_canal->vibrato_tasa_cambio_retardo = leer_m64_u8(estado) * 0x10;
                        break;

                    case 0xE3:
                        sec_canal->retardo_vibrato = leer_m64_u8(estado) * 0x10;
                        break;

                    case 0xD4:
                        sec_canal->reverb_vol = leer_m64_u8(estado);
                        break;

                    case 0xC6:
                        cmd = leer_m64_u8(estado);
                        sp5_a = ((u16*) conjuntos_banco_al)[sec_jugador->sec_id];
                        lo_bits = *(sp5_a + conjuntos_banco_al);
                        cmd = conjuntos_banco_al[(sp5_a + lo_bits) - cmd];
                        if (obtener_banco_o_sec(1, 2, cmd) != NULL) {
                            sec_canal->id_banco = cmd;
                        }
                        break;

                    case 0xC7:
                        cmd = leer_m64_u8(estado);
                        sp5_a = leer_m64_s16(estado);
                        sec_datos = sec_jugador->sec_datos + sp5_a;
                        *sec_datos = ((u8) value) + cmd;
                        break;

                    case 0xC8:
                    case 0xC9:
                    case 0xCC:
                        temporal_ = leer_m64_u8(estado);
                        if (cmd == 0xC8) {
                            value -= temporal_;
                        } else if (cmd == 0xCC) {
                            value = temporal_;
                        } else {
                            value &= temporal_;
                        }
                        break;

                    case 0xCA:
                        sec_canal->comportamiento_silencio = leer_m64_u8(estado);
                        break;

                    case 0xCB:
                        sp38 = ((u16) leer_m64_s16(estado)) + value;
                        value = sec_jugador->sec_datos[sp38];
                        break;

                    case 0xD0:
                        sec_canal->efectos_auriculares_estereo = leer_m64_u8(estado);
                        break;

                    case 0xD1:
                        sec_canal->politica_reserva_nota = leer_m64_u8(estado);
                        break;

                    case 0xD2:
                        sec_canal->adsr.sostenido = leer_m64_u8(estado);
                        break;

                    case 0xE5:
                        sec_canal->indice_reverb = leer_m64_u8(estado);
                        break;

                    case 0xE4:
                        if (value != (-1)) {
                            if (estado->profundidad) {};
                            sec_datos = (*sec_canal->tabla_din)[value];
                            estado->stack[estado->profundidad++] = estado->pc;
                            sp38 = (u16) ((sec_datos[0] << 8) + sec_datos[1]);
                            estado->pc = sec_jugador->sec_datos + sp38;
                        }
                        break;

                    case 0xE6:
                        sec_canal->desplazamiento_libro = leer_m64_u8(estado);
                        break;

                    case 0xE7:
                        sp5_a = leer_m64_s16(estado);
                        sec_datos = sec_jugador->sec_datos + sp5_a;
                        sec_canal->comportamiento_silencio = *(sec_datos++);
                        sec_canal->politica_reserva_nota = *(sec_datos++);
                        sec_canal->prioridad_nota = *(sec_datos++);
                        sec_canal->trasposicion = (s8) (*(sec_datos++));
                        sec_canal->paneo_nuevo = *(sec_datos++);
                        sec_canal->peso_canal_paneo = *(sec_datos++);
                        sec_canal->reverb_vol = *(sec_datos++);
                        sec_canal->indice_reverb = *(sec_datos++);
                        sec_canal->cambios.como_bitfields.paneo = 1;
                        break;

                    case 0xE8:
                        sec_canal->comportamiento_silencio = leer_m64_u8(estado);
                        sec_canal->politica_reserva_nota = leer_m64_u8(estado);
                        sec_canal->prioridad_nota = leer_m64_u8(estado);
                        sec_canal->trasposicion = (s8) leer_m64_u8(estado);
                        sec_canal->paneo_nuevo = leer_m64_u8(estado);
                        sec_canal->peso_canal_paneo = leer_m64_u8(estado);
                        sec_canal->reverb_vol = leer_m64_u8(estado);
                        sec_canal->indice_reverb = leer_m64_u8(estado);
                        sec_canal->cambios.como_bitfields.paneo = 1;
                        break;

                    case 0xEC:
                        sec_canal->objetivo_extension_vibrato = 0;
                        sec_canal->inicio_extension_vibrato = 0;
                        sec_canal->vibrato_extension_cambio_retardo = 0;
                        sec_canal->objetivo_tasa_vibrato = 0;
                        sec_canal->inicio_tasa_vibrato = 0;
                        sec_canal->vibrato_tasa_cambio_retardo = 0;
                        sec_canal->escala_frec = 1.0f;
                        break;

                    case 0xE9:
                        sec_canal->prioridad_nota = leer_m64_u8(estado);
                        break;

                    case 0xEF:
                        leer_m64_s16(estado);
                        leer_m64_u8(estado);
                        break;
                }
            } else {
                lo_bits = cmd & 0xf;
                switch (cmd & 0xF0) {
                    case 0x0:
                        if (sec_canal->capas[lo_bits] != NULL) {
                            value = sec_canal->capas[lo_bits]->terminado;
                        } else {
                            value = -1;
                        }
                        break;

                    case 0x70:
                        sec_canal->sonido_io_guion[lo_bits] = value;
                        break;

                    case 0x80:
                        value = sec_canal->sonido_io_guion[lo_bits];
                        if (lo_bits < 4) {
                            sec_canal->sonido_io_guion[lo_bits] = -1;
                        }
                        break;

                    case 0x50:
                        value -= sec_canal->sonido_io_guion[lo_bits];
                        break;

                    case 0x60:
                        sec_canal->delay = lo_bits;
                        goto salida;

                    case 0x90:
                        sp5_a = leer_m64_s16(estado);
                        if (sec_capa_conjunto_canal(sec_canal, lo_bits) == 0) {
                            sec_canal->capas[lo_bits]->estado_guion.pc = sec_jugador->sec_datos + sp5_a;
                        }
                        break;

                    case 0xA0:
                        sec_libre_capa_canal(sec_canal, lo_bits);
                        break;

                    case 0xB0:
                        if ((value != (-1)) && (sec_capa_conjunto_canal(sec_canal, lo_bits) != (-1))) {
                            sec_datos = (*sec_canal->tabla_din)[value];
                            sp5_a = (sec_datos[0] << 8) + sec_datos[1];
                            sec_canal->capas[lo_bits]->estado_guion.pc = sec_jugador->sec_datos + sp5_a;
                        }
                        break;

                    case 0x10:
                        sp5_a = leer_m64_s16(estado);
                        activar_canal_secuencia(sec_jugador, lo_bits, sec_jugador->sec_datos + sp5_a);
                        break;

                    case 0x20:
                        desactivar_canal_secuencia(sec_jugador->channels[lo_bits]);
                        break;

                    case 0x30:
                        cmd = leer_m64_u8(estado);
                        sec_jugador->channels[lo_bits]->sonido_io_guion[cmd] = value;
                        break;

                    case 0x40:
                        cmd = leer_m64_u8(estado);
                        value = sec_jugador->channels[lo_bits]->sonido_io_guion[cmd];
                        break;
                }
            }
        }
    }
salida:
    for (i = 0; i < MAX_CAPAS; i++) {
        if (sec_canal->capas[i] != 0) {
            sec_canal_capa_proceso_guion(sec_canal->capas[i]);
        }
    }
}

void procesar_secuencia_jugador_secuencia(struct JugadorSecuencia* sec_jugador) {
    u8 cmd;
    u8 lo_bits;
    u8 temporal_;
    s32 value;
    s32 i;
    u16 u16v;
    u8* sec_datos;
    struct EstadoGuionM64* estado;
    s32 temporal32;

    if (sec_jugador->activado == false) {
        return;
    }

    if (sec_jugador->dma_banco_en_progreso == true) {
        if (osRecvMesg(&sec_jugador->banco_dma_msj_cola, NULL, 0) == -1) {
            return;
        }
        if (sec_jugador->restante_dma_banco == 0) {
            sec_jugador->dma_banco_en_progreso = false;
            funcion_800BB584(sec_jugador->id_banco_cargando);
            if (situacion_carga_banco[sec_jugador->id_banco_cargando] != 5) {
                situacion_carga_banco[sec_jugador->id_banco_cargando] = 2;
            }
        } else {
            copiar_asincrono_parcial_dma_audio(&sec_jugador->banco_dma_act_dev_direccion, &sec_jugador->banco_dma_act_mem_direccion,
                                         &sec_jugador->restante_dma_banco, &sec_jugador->banco_dma_msj_cola,
                                         &sec_jugador->banco_dma_io_msj);
        }
        return;
    }

    if (sec_jugador->sec_dma_en_progreso == true) {
        if (osRecvMesg(&sec_jugador->sec_cola_msj_dma, NULL, 0) == -1) {
            return;
        }
        sec_jugador->sec_dma_en_progreso = false;
        if (sec_situacion_carga[sec_jugador->sec_id] != 5) {
            sec_situacion_carga[sec_jugador->sec_id] = 2;
        }
    }

    temporal32 = 2;
    if (ES_SEC_CARGA_COMPLETO(sec_jugador->sec_id) == false ||
        (ES_BANCO_CARGA_COMPLETO(sec_jugador->banco_predeterminado[0]) == false)) {
        desactivar_jugador_secuencia(sec_jugador);
        return;
    }

    if (sec_situacion_carga[sec_jugador->sec_id] != 5) {
        sec_situacion_carga[sec_jugador->sec_id] = temporal32;
    }

    if (situacion_carga_banco[sec_jugador->banco_predeterminado[0]] != 5) {
        situacion_carga_banco[sec_jugador->banco_predeterminado[0]] = temporal32;
    }

    if (sec_jugador->silenciado && (sec_jugador->comportamiento_silencio & SILENCIO_COMPORTAMIENTO_PARADA_GUION) != 0) {
        return;
    }

    sec_jugador->tempo_acc += sec_jugador->tempo;
    if (sec_jugador->tempo_acc < interno_tempo_a_externo) {
        return;
    }
    sec_jugador->tempo_acc -= (u16) interno_tempo_a_externo;

    estado = &sec_jugador->estado_guion;
    if (sec_jugador->delay > 1) {
        sec_jugador->delay--;
    } else {
        sec_jugador->volumen_recalcular = 1;
        for (;;) {
            cmd = leer_m64_u8(estado);
            if (cmd == 0xff) {
                if (estado->profundidad == 0) {
                    desactivar_jugador_secuencia(sec_jugador);
                    break;
                }
                estado->pc = estado->stack[--estado->profundidad];
            }

            if (cmd == 0xfd) {
                sec_jugador->delay = leer_comprimido_m64_u16(estado);
                break;
            }

            if (cmd == 0xfe) {
                sec_jugador->delay = 1;
                break;
            }

            if (cmd >= 0xc0) {
                switch (cmd) {
                    case 0xff:
                        break;

                    case 0xfc:
                        u16v = leer_m64_s16(estado);
                        if (0 && estado->profundidad >= 4) {}
                        estado->stack[estado->profundidad++] = estado->pc;
                        estado->pc = sec_jugador->sec_datos + u16v;
                        break;

                    case 0xf8:
                        if (0 && estado->profundidad >= 4) {}
                        estado->iters_bucle_resto[estado->profundidad] = leer_m64_u8(estado);
                        estado->stack[estado->profundidad++] = estado->pc;
                        break;

                    case 0xf7:
                        estado->iters_bucle_resto[estado->profundidad - 1]--;
                        if (estado->iters_bucle_resto[estado->profundidad - 1] != 0) {
                            estado->pc = estado->stack[estado->profundidad - 1];
                        } else {
                            estado->profundidad--;
                        }
                        break;

                    case 0xfb:
                    case 0xfa:
                    case 0xf9:
                    case 0xf5:
                        u16v = leer_m64_s16(estado);
                        if (cmd == 0xfa && value != 0) {
                            break;
                        }
                        if (cmd == 0xf9 && value >= 0) {
                            break;
                        }
                        if (cmd == 0xf5 && value < 0) {
                            break;
                        }
                        estado->pc = sec_jugador->sec_datos + u16v;
                        break;

                    case 0xf4:
                    case 0xf3:
                    case 0xf2:
                        temporal_ = leer_m64_u8(estado);
                        if (cmd == 0xf3 && value != 0) {
                            break;
                        }
                        if (cmd == 0xf2 && value >= 0) {
                            break;
                        }
                        estado->pc += (s8) temporal_;
                        break;

                    case 0xf1:
                        borrar_pool_nota(&sec_jugador->pool_nota);
                        relleno_pool_nota(&sec_jugador->pool_nota, leer_m64_u8(estado));
                        break;

                    case 0xf0:
                        borrar_pool_nota(&sec_jugador->pool_nota);
                        break;

                    case 0xdf:
                        sec_jugador->trasposicion = 0;

                    case 0xde:
                        sec_jugador->trasposicion += (s8) leer_m64_u8(estado);
                        break;

                    case 0xdc:
                    case 0xdd:
                        temporal_ = leer_m64_u8(estado);
                        if (cmd == 0xdd) {
                            sec_jugador->tempo = temporal_ * ESCALA_TEMPO;
                        } else {
                            sec_jugador->tempo += (s8) temporal_ * ESCALA_TEMPO;
                        }

                        if (sec_jugador->tempo > interno_tempo_a_externo) {
                            sec_jugador->tempo = interno_tempo_a_externo;
                        }

                        if ((s16) sec_jugador->tempo <= 0) {
                            sec_jugador->tempo = 1;
                        }
                        break;

                    case 0xda:
                        cmd = leer_m64_u8(estado);
                        u16v = leer_m64_s16(estado);
                        switch (cmd) {
                            case ESTADO_JUGADOR_SECUENCIA_0:
                            case SECUENCIA_JUGADOR_ESTADO_FUNDIDO_SALIDA:
                                if (sec_jugador->state != ESTADO_JUGADOR_SECUENCIA_2) {
                                    sec_jugador->fundido_temporizador_desconocido_eu = u16v;
                                    sec_jugador->state = cmd;
                                }
                                break;
                            case ESTADO_JUGADOR_SECUENCIA_2:
                                sec_jugador->frames_restante_fundido = u16v;
                                sec_jugador->state = cmd;
                                sec_jugador->velocidad_fundido = (0.0f - sec_jugador->volumen_fundido) / (s32) (u16v & 0xFFFFu);
                                break;
                        }
                        break;

                    case 0xdb:
                        temporal32 = leer_m64_u8(estado);
                        switch (sec_jugador->state) {
                            case ESTADO_JUGADOR_SECUENCIA_2:
                                break;
                            case SECUENCIA_JUGADOR_ESTADO_FUNDIDO_SALIDA:
                                sec_jugador->state = ESTADO_JUGADOR_SECUENCIA_0;
                                sec_jugador->volumen_fundido = 0.0f;
                            case ESTADO_JUGADOR_SECUENCIA_0:
                                sec_jugador->frames_restante_fundido = sec_jugador->fundido_temporizador_desconocido_eu;
                                if (sec_jugador->fundido_temporizador_desconocido_eu != 0) {
                                    sec_jugador->velocidad_fundido = (temporal32 / 127.0f - sec_jugador->volumen_fundido) /
                                                              CONVERSION_FLOTANTE(sec_jugador->frames_restante_fundido);
                                } else {
                                    sec_jugador->volumen_fundido = temporal32 / 127.0f;
                                }
                        }
                        break;

                    case 0xd9:
                        temporal_ = leer_m64_u8(estado);
                        sec_jugador->escala_volumen_fundido = (s8) temporal_ / 127.0f;
                        break;

                    case 0xd7:
                        u16v = leer_m64_s16(estado);
                        inicializar_canales_jugador_secuencia(sec_jugador, u16v);
                        break;

                    case 0xd6:
                        u16v = leer_m64_s16(estado);
                        desactivar_canales_jugador_secuencia(sec_jugador, u16v);
                        break;

                    case 0xd5:
                        temporal_ = leer_m64_u8(estado);
                        sec_jugador->escala_volumen_silencio = (f32) (s8) temporal_ / FLOTANTE_US(127.0);
                        break;

                    case 0xd4:
                        sec_jugador->silenciado = true;
                        break;

                    case 0xd3:
                        sec_jugador->comportamiento_silencio = leer_m64_u8(estado);
                        break;

                    case 0xd2:
                    case 0xd1:
                        u16v = leer_m64_s16(estado);
                        sec_datos = sec_jugador->sec_datos + u16v;
                        if (cmd == 0xd2) {
                            sec_jugador->corto_nota_velocidad_tabla = sec_datos;
                        } else {
                            sec_jugador->corto_nota_duracion_tabla = sec_datos;
                        }
                        break;

                    case 0xd0:
                        sec_jugador->politica_reserva_nota = leer_m64_u8(estado);
                        break;

                    case 0xcc:
                        value = leer_m64_u8(estado);
                        break;

                    case 0xc9:
                        value &= leer_m64_u8(estado);
                        break;

                    case 0xc8:
                        value = value - leer_m64_u8(estado);
                        break;

                    default:
                        break;
                }
            } else {
                lo_bits = cmd & 0xf;
                switch (cmd & 0xf0) {
                    case 0x00:
                        value = sec_jugador->channels[lo_bits]->terminado;
                        break;
                    case 0x10:
                        break;
                    case 0x20:
                        break;
                    case 0x40:
                        break;
                    case 0x50:
                        value -= sec_jugador->sec_eu_variacion[0];
                        break;
                    case 0x60:
                        break;
                    case 0x70:
                        sec_jugador->sec_eu_variacion[0] = value;
                        break;
                    case 0x80:
                        value = sec_jugador->sec_eu_variacion[0];
                        break;
                    case 0x90:
                        u16v = leer_m64_s16(estado);
                        activar_canal_secuencia(sec_jugador, lo_bits, sec_jugador->sec_datos + u16v);
                        break;
                    case 0xa0:
                        break;

                    default:
                        break;
                }
            }
        }
    }

    for (i = 0; i < MAX_CANALES; i++) {
        if (ES_SECUENCIA_CANAL_VALIDO(sec_jugador->channels[i]) == true) {
            procesar_guion_canal_secuencia(sec_jugador->channels[i]);
        }
    }
}

void procesar_secuencias(SIN_USO s32 restante_iteraciones) {
    s32 i;
    for (i = 0; i < JUGADORES_SECUENCIA; i++) {
        if (jugadores_secuencia[i].activado == true) {
            procesar_secuencia_jugador_secuencia(&jugadores_secuencia[i]);
            procesar_sonido_jugador_secuencia(&jugadores_secuencia[i]);
        }
    }
    procesar_notas();
}

void inicializar_jugador_secuencia(u32 jugador) {
    struct JugadorSecuencia* sec_jugador = &jugadores_secuencia[jugador];
    desactivar_jugador_secuencia(sec_jugador);
    sec_jugador->delay = 0;
    sec_jugador->state = 1;
    sec_jugador->frames_restante_fundido = 0;
    sec_jugador->fundido_temporizador_desconocido_eu = 0;
    sec_jugador->tempo_acc = 0;
    sec_jugador->tempo = 120 * ESCALA_TEMPO;
    sec_jugador->trasposicion = 0;
    sec_jugador->politica_reserva_nota = 0;
    sec_jugador->corto_nota_velocidad_tabla = predeterminado_corto_nota_velocidad_tabla;
    sec_jugador->corto_nota_duracion_tabla = predeterminado_corto_nota_duracion_tabla;
    sec_jugador->volumen_fundido = 1.0f;
    sec_jugador->escala_volumen_fundido = 1.0f;
    sec_jugador->velocidad_fundido = 0.0f;
    sec_jugador->volumen = 0.0f;
    sec_jugador->escala_volumen_silencio = 0.5f;
}

void inicializar_jugadores_secuencia(void) {
    s32 i, j;

    for (i = 0; i < CANTIDAD_ARREGLO(canales_secuencia); i++) {
        canales_secuencia[i].sec_jugador = NULL;
        canales_secuencia[i].activado = false;
#ifdef AVOID_UB
#define TAMANIO_CAPAS MAX_CAPAS
#else
#define TAMANIO_CAPAS CANTIDAD_ARREGLO(capas_secuencia)
#endif
        for (j = 0; j < TAMANIO_CAPAS; j++) {
            canales_secuencia[i].capas[j] = NULL;
        }
    }

    inicializar_lista_libres_capa();

    for (i = 0; i < CANTIDAD_ARREGLO(capas_secuencia); i++) {
        capas_secuencia[i].sec_canal = NULL;
        capas_secuencia[i].activado = false;
    }

    for (i = 0; i < JUGADORES_SECUENCIA; i++) {
        for (j = 0; j < MAX_CANALES; j++) {
            jugadores_secuencia[i].channels[j] = &ninguno_canal_secuencia;
        }

        jugadores_secuencia[i].sec_eu_variacion[0] = -1;
        jugadores_secuencia[i].comportamiento_silencio = SILENCIO_COMPORTAMIENTO_PARADA_GUION | SILENCIO_COMPORTAMIENTO_PARADA_NOTAS | SUAVIZAR_COMPORTAMIENTO_SILENCIO;
        jugadores_secuencia[i].activado = false;
        jugadores_secuencia[i].silenciado = false;
        jugadores_secuencia[i].dma_banco_en_progreso = false;
        jugadores_secuencia[i].sec_dma_en_progreso = false;
        inicializar_listas_nota(&jugadores_secuencia[i].pool_nota);
        inicializar_jugador_secuencia(i);
    }
}
