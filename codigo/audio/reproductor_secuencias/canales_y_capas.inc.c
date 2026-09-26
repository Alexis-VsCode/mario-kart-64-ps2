// Canales y capas

char cadena00_sin_uso_reproductor_sec[] = "Audio:Track:Warning: No Free Notetrack\n";
char cadena01_sin_uso_reproductor_sec[] = "SUBTRACK DIM\n";
char cadena02_sin_uso_reproductor_sec[] = "Audio:Track: Warning :SUBTRACK had been stolen by other Group.\n";
char cadena03_sin_uso_reproductor_sec[] = "SEQID %d,BANKID %d\n";
char cadena04_sin_uso_reproductor_sec[] = "ERR:SUBTRACK %d NOT ALLOCATED\n";
char cadena05_sin_uso_reproductor_sec[] = "Error:Same List Add\n";
#ifdef VERSION_EU_V10
char reproductor_sec_sin_uso_cadena_eu_01[] = "Wait Time out!\n";
#endif
char cadena06_sin_uso_reproductor_sec[] = "Macro Level Over Error!\n";
char cadena07_sin_uso_reproductor_sec[] = "Macro Level Over Error!\n";
char cadena08_sin_uso_reproductor_sec[] = "WARNING: NPRG: cannot change %d\n";
char cadena09_sin_uso_reproductor_sec[] = "Audio:Track:NOTE:UNDEFINED NOTE COM. %x\n";
char cadena10_sin_uso_reproductor_sec[] = "Audio: Note:Velocity Error %d\n";
char cadena11_sin_uso_reproductor_sec[] = "Error: Subtrack no prg.\n";
char cadena12_sin_uso_reproductor_sec[] = "ERR %x\n";
char cadena13_sin_uso_reproductor_sec[] = "Error: Your assignchannel is stolen.\n";
char cadena14_sin_uso_reproductor_sec[] = "Audio:Track :Call Macro Level Over Error!\n";
char cadena15_sin_uso_reproductor_sec[] = "Audio:Track :Loops Macro Level Over Error!\n";
char cadena16_sin_uso_reproductor_sec[] = "SUB:ERR:BANK %d NOT CACHED.\n";
char cadena17_sin_uso_reproductor_sec[] = "SUB:ERR:BANK %d NOT CACHED.\n";
char cadena18_sin_uso_reproductor_sec[] = "Audio:Track: CTBLCALL Macro Level Over Error!\n";
char cadena19_sin_uso_reproductor_sec[] = "[%2x] \n";
char cadena20_sin_uso_reproductor_sec[] = "Err :Sub %x ,address %x:Undefined SubTrack Function %x";
char cadena21_sin_uso_reproductor_sec[] = "Disappear Sequence or Bank %d\n";
char cadena22_sin_uso_reproductor_sec[] = "Macro Level Over Error!\n";
char cadena23_sin_uso_reproductor_sec[] = "Macro Level Over Error!\n";
char cadena24_sin_uso_reproductor_sec[] = "Group:Undefine upper C0h command (%x)\n";
char cadena25_sin_uso_reproductor_sec[] = "Group:Undefined Command\n";

void inicializar_canal_secuencia(struct CanalSecuencia* sec_canal) {
    s32 i;

    sec_canal->activado = false;
    sec_canal->terminado = false;
    sec_canal->guion_parada = false;
    sec_canal->algo_parada_2 = false;
    sec_canal->instrumento_tiene = false;
    sec_canal->efectos_auriculares_estereo = false;
    sec_canal->trasposicion = 0;
    sec_canal->notas_grande = false;
    sec_canal->desplazamiento_libro = 0;
    sec_canal->cambios.as_u8 = 0xff;
    sec_canal->estado_guion.profundidad = 0;
    sec_canal->paneo_nuevo = 0x40;
    sec_canal->peso_canal_paneo = 0x80;
    sec_canal->nota_sin_uso = NULL;
    sec_canal->indice_reverb = 0;
    sec_canal->reverb_vol = 0;
    sec_canal->prioridad_nota = PREDETERMINADO_PRIORIDAD_NOTA;
    sec_canal->delay = 0;
    sec_canal->adsr.envelope = envolvente_predeterminado;
    sec_canal->adsr.tasa_suelta = 0x20;
    sec_canal->adsr.sostenido = 0;
    sec_canal->objetivo_tasa_vibrato = 0x800;
    sec_canal->inicio_tasa_vibrato = 0x800;
    sec_canal->objetivo_extension_vibrato = 0;
    sec_canal->inicio_extension_vibrato = 0;
    sec_canal->vibrato_tasa_cambio_retardo = 0;
    sec_canal->vibrato_extension_cambio_retardo = 0;
    sec_canal->retardo_vibrato = 0;
    sec_canal->volumen = 1.0f;
    sec_canal->escala_volumen = 1.0f;
    sec_canal->escala_frec = 1.0f;
    for (i = 0; i < 8; i++) {
        sec_canal->sonido_io_guion[i] = -1;
    }
    sec_canal->unused = false;
    inicializar_listas_nota(&sec_canal->pool_nota);
}

s32 sec_capa_conjunto_canal(struct CanalSecuencia* sec_canal, s32 indice_capa) {
    struct CapaCanalSecuencia* capa;

    if (sec_canal->capas[indice_capa] == NULL) {
        struct CapaCanalSecuencia* capa;
        capa = sacar_atras_lista_audio(&lista_libre_capa);
        sec_canal->capas[indice_capa] = capa;
        if (capa == NULL) {
            sec_canal->capas[indice_capa] = NULL;
            return -1;
        }
    } else {
        sec_canal_capa_nota_decaer(sec_canal->capas[indice_capa]);
    }

    capa = sec_canal->capas[indice_capa];
    capa->sec_canal = sec_canal;
    capa->adsr = sec_canal->adsr;
    capa->adsr.tasa_suelta = 0;
    capa->activado = true;
    capa->algo_parada = false;
    capa->notas_continuo = false;
    capa->terminado = false;
    capa->paneo_tambor_ignorar = false;
    capa->portamento.mode = 0;
    capa->estado_guion.profundidad = 0;
    capa->status = SONIDO_SITUACION_CARGA_NO_CARGADO;
    capa->duracion_nota = 0x80;
    capa->paneo = 0x40;
    capa->trasposicion = 0;
    capa->delay = 0;
    capa->duration = 0;
    capa->retardo_sin_uso = 0;
    capa->nota = NULL;
    capa->instrumento = NULL;
    capa->escala_frec = 1.0f;
    capa->cuadrado_velocidad = 0.0f;
    capa->inst_o_ola = 0xff;
    return 0;
}

void sec_desactivar_capa_canal(struct CapaCanalSecuencia* capa) {
    if (capa != NULL) {
        sec_canal_capa_nota_decaer(capa);
        capa->activado = false;
        capa->terminado = true;
    }
}

void sec_libre_capa_canal(struct CanalSecuencia* sec_canal, s32 indice_capa) {
    struct CapaCanalSecuencia* capa = sec_canal->capas[indice_capa];

    if (capa != NULL) {
        empujar_atras_lista_audio(&lista_libre_capa, &capa->item_lista);
        sec_desactivar_capa_canal(capa);
        sec_canal->capas[indice_capa] = NULL;
    }
}

void desactivar_canal_secuencia(struct CanalSecuencia* sec_canal) {
    s32 i;
    for (i = 0; i < MAX_CAPAS; i++) {
        sec_libre_capa_canal(sec_canal, i);
    }

    borrar_pool_nota(&sec_canal->pool_nota);
    sec_canal->activado = false;
    sec_canal->terminado = true;
}

struct CanalSecuencia* reservar_canal_secuencia(void) {
    s32 i;
    for (i = 0; i < CANALES_SECUENCIA; i++) {
        if (canales_secuencia[i].sec_jugador == NULL) {
            return &canales_secuencia[i];
        }
    }
    return &ninguno_canal_secuencia;
}

void inicializar_canales_jugador_secuencia(struct JugadorSecuencia* sec_jugador, u16 bits_canal) {
    struct CanalSecuencia* sec_canal;
    s32 i;

    for (i = 0; i < MAX_CANALES; i++) {
        if (bits_canal & 1) {
            sec_canal = sec_jugador->channels[i];
            if (ES_SECUENCIA_CANAL_VALIDO(sec_canal) == true && sec_canal->sec_jugador == sec_jugador) {
                desactivar_canal_secuencia(sec_canal);
                sec_canal->sec_jugador = NULL;
            }
            sec_canal = reservar_canal_secuencia();
            if (ES_SECUENCIA_CANAL_VALIDO(sec_canal) == false) {
                banderas_error_audio = i + 0x10000;
                sec_jugador->channels[i] = sec_canal;
            } else {
                inicializar_canal_secuencia(sec_canal);
                sec_jugador->channels[i] = sec_canal;
                sec_canal->sec_jugador = sec_jugador;
                sec_canal->id_banco = sec_jugador->banco_predeterminado[0];
                sec_canal->comportamiento_silencio = sec_jugador->comportamiento_silencio;
                sec_canal->politica_reserva_nota = sec_jugador->politica_reserva_nota;
            }
        }
        bits_canal = bits_canal >> 1;
    }
}

void desactivar_canales_jugador_secuencia(struct JugadorSecuencia* sec_jugador, u16 bits_canal) {
    struct CanalSecuencia* sec_canal;
    s32 i;

    for (i = 0; i < MAX_CANALES; i++) {
        if (bits_canal & 1) {
            sec_canal = sec_jugador->channels[i];
            if (ES_SECUENCIA_CANAL_VALIDO(sec_canal) == true) {
                if (sec_canal->sec_jugador == sec_jugador) {
                    desactivar_canal_secuencia(sec_canal);
                    sec_canal->sec_jugador = NULL;
                } else {
                }
                sec_jugador->channels[i] = &ninguno_canal_secuencia;
            }
        }
        bits_canal = bits_canal >> 1;
    }
}

void activar_canal_secuencia(struct JugadorSecuencia* sec_jugador, u8 indice_canal, void* guion) {
    struct CanalSecuencia* sec_canal = sec_jugador->channels[indice_canal];
    s32 i;
    if (ES_SECUENCIA_CANAL_VALIDO(sec_canal) == false) {
    } else {
        sec_canal->activado = true;
        sec_canal->terminado = false;
        sec_canal->estado_guion.profundidad = 0;
        sec_canal->estado_guion.pc = guion;
        sec_canal->delay = 0;
        for (i = 0; i < MAX_CAPAS; i++) {
            if (sec_canal->capas[i] != NULL) {
                sec_libre_capa_canal(sec_canal, i);
            }
        }
    }
}

void desactivar_jugador_secuencia(struct JugadorSecuencia* sec_jugador) {
    desactivar_canales_jugador_secuencia(sec_jugador, 0xffff);
    borrar_pool_nota(&sec_jugador->pool_nota);
    sec_jugador->terminado = true;
    sec_jugador->activado = false;

    if (ES_SEC_CARGA_COMPLETO(sec_jugador->sec_id) && sec_situacion_carga[sec_jugador->sec_id] != 5) {
        sec_situacion_carga[sec_jugador->sec_id] = SONIDO_DESCARTABLE_SITUACION_CARGA;
    }

    if (ES_BANCO_CARGA_COMPLETO(sec_jugador->banco_predeterminado[0]) && situacion_carga_banco[sec_jugador->banco_predeterminado[0]] != 5) {
        situacion_carga_banco[sec_jugador->banco_predeterminado[0]] = 4;
    }

    if (sec_jugador->banco_predeterminado[0] == pool_cargado_banco.provisorio.entradas[0].id) {
        pool_cargado_banco.provisorio.lado_siguiente = 1;
    } else if (sec_jugador->banco_predeterminado[0] == pool_cargado_banco.provisorio.entradas[1].id) {
        pool_cargado_banco.provisorio.lado_siguiente = 0;
    }
}

void empujar_atras_lista_audio(struct ItemListaAudio* lista, struct ItemListaAudio* item) {
    if (item->prev != NULL) {
    } else {
        lista->prev->next = item;
        item->prev = lista->prev;
        item->next = lista;
        lista->prev = item;
        lista->u.count++;
        item->pool = lista->pool;
    }
}

void* sacar_atras_lista_audio(struct ItemListaAudio* lista) {
    struct ItemListaAudio* item = lista->prev;
    if (item == lista) {
        return NULL;
    }
    item->prev->next = lista;
    lista->prev = item->prev;
    item->prev = NULL;
    lista->u.count--;
    return item->u.value;
}

void inicializar_lista_libres_capa(void) {
    s32 i;

    lista_libre_capa.prev = &lista_libre_capa;
    lista_libre_capa.next = &lista_libre_capa;
    lista_libre_capa.u.count = 0;
    lista_libre_capa.pool = NULL;

    for (i = 0; i < CANTIDAD_ARREGLO(capas_secuencia); i++) {
        capas_secuencia[i].item_lista.u.value = &capas_secuencia[i];
        capas_secuencia[i].item_lista.prev = NULL;
        empujar_atras_lista_audio(&lista_libre_capa, &capas_secuencia[i].item_lista);
    }
}

u8 leer_m64_u8(struct EstadoGuionM64* estado) {
    return *(estado->pc++);
}

s16 leer_m64_s16(struct EstadoGuionM64* estado) {
    s16 devuelto = *(estado->pc++) << 8;
    devuelto = *(estado->pc++) | devuelto;
    return devuelto;
}

u16 leer_comprimido_m64_u16(struct EstadoGuionM64* estado) {
    u16 devuelto = *(estado->pc++);
    if (devuelto & 0x80) {
        devuelto = (devuelto << 8) & 0x7f00;
        devuelto = *(estado->pc++) | devuelto;
    }
    return devuelto;
}

void sec_canal_capa_proceso_guion(struct CapaCanalSecuencia* capa) {
    struct JugadorSecuencia* sec_jugador;
    struct CanalSecuencia* sec_canal;
    SIN_USO u32 relleno0;
    struct EstadoGuionM64* estado;
    struct Portamento* portamento;
    struct SonidoBancoAudio* sonido;
    struct Instrumento* instrumento;
    struct Tambor* tambor;
    s32 temporal_a0_5;
    u16 sp3_a;
    s32 sonido_mismo;
    SIN_USO u32 relleno1;
    u8 cmd;
    SIN_USO u8 semitono_cmd;
    f32 ajuste;
    s32 vel;
    SIN_USO s32 semitono_usado;
    f32 escala_frec;
    f32 temporal_f12;
    f32 temporal_f2;

    sonido_mismo = true;
    if (capa->activado == false) {
        return;
    }

    if (capa->delay > 1) {
        capa->delay--;
        if (!capa->algo_parada && capa->delay <= capa->duration) {
            sec_canal_capa_nota_decaer(capa);
            capa->algo_parada = true;
        }
        return;
    }

    if (!capa->notas_continuo) {
        sec_canal_capa_nota_decaer(capa);
    }
#ifdef VERSION_EU_V10
    else {
        if ((capa->nota != 0) && (capa == capa->nota->capa_padre_buscado)) {
            sec_canal_capa_nota_decaer(capa);
        }
    }
#endif

    if (MODO_PORTAMENTO(capa->portamento) == MODO_PORTAMENTO_1 ||
        MODO_PORTAMENTO(capa->portamento) == MODO_PORTAMENTO_2) {
        capa->portamento.mode = 0;
    }

    sec_canal = capa->sec_canal;
    sec_jugador = sec_canal->sec_jugador;
    capa->nota_propiedades_necesitar_inicializacion = true;

    for (;;) {
        estado = &capa->estado_guion;
        cmd = leer_m64_u8(estado);

        if (cmd <= 0xc0) {
            break;
        }

        switch (cmd) {
            case 0xff:
                if (estado->profundidad == 0) {
                    sec_desactivar_capa_canal(capa);
                    return;
                }
                estado->pc = estado->stack[--estado->profundidad];
                break;

            case 0xfc:
                if (0 && estado->profundidad >= 4) {}
                sp3_a = leer_m64_s16(estado);
                estado->stack[estado->profundidad++] = estado->pc;
                estado->pc = sec_jugador->sec_datos + sp3_a;
                break;

            case 0xf8:
                if (0 && estado->profundidad >= 4) {}
                estado->iters_bucle_resto[estado->profundidad] = leer_m64_u8(estado);
                estado->stack[estado->profundidad++] = estado->pc;
                break;

            case 0xf7:
                if (--estado->iters_bucle_resto[estado->profundidad - 1] != 0) {
                    estado->pc = estado->stack[estado->profundidad - 1];
                } else {
                    estado->profundidad--;
                }
                break;

            case 0xfb:
                sp3_a = leer_m64_s16(estado);
                estado->pc = sec_jugador->sec_datos + sp3_a;
                break;

            case 0xf4:
                estado->pc += (s8) leer_m64_u8(estado);
                break;

            case 0xc1:
            case 0xca:
                temporal_a0_5 = *(estado->pc++);
                if (cmd == 0xc1) {
                    capa->cuadrado_velocidad = (f32) (temporal_a0_5 * temporal_a0_5) / 16129.0f;
                } else {
                    capa->paneo = temporal_a0_5;
                }
                break;

            case 0xc2:
            case 0xc9:
                temporal_a0_5 = *(estado->pc++);
                if (cmd == 0xc9) {
                    capa->duracion_nota = temporal_a0_5;
                } else {
                    capa->trasposicion = temporal_a0_5;
                }
                break;

            case 0xc4:
            case 0xc5:
                if (cmd == 0xc4) {
                    capa->notas_continuo = true;
                } else {
                    capa->notas_continuo = false;
                }
                sec_canal_capa_nota_decaer(capa);
                break;

            case 0xc3:
                sp3_a = leer_comprimido_m64_u16(estado);
                capa->corto_nota_predeterminado_juego_porcentaje = sp3_a;
                break;

            case 0xc6:
                cmd = leer_m64_u8(estado);
                if (cmd >= 0x7f) {
                    if (cmd == 0x7f) {
                        capa->inst_o_ola = 0;
                    } else {
                        capa->inst_o_ola = cmd;
                        capa->instrumento = NULL;
                    }

                    if (1) {}

                    if (cmd == 0xff) {
                        capa->adsr.tasa_suelta = 0;
                    }
                    break;
                }

                if ((capa->inst_o_ola = obtener_instrumento(sec_canal, cmd, &capa->instrumento, &capa->adsr)) == 0) {
                    capa->inst_o_ola = 0xff;
                }
                break;

            case 0xc7:
                capa->portamento.mode = leer_m64_u8(estado);

                cmd = leer_m64_u8(estado) + sec_canal->trasposicion + capa->trasposicion + sec_jugador->trasposicion;

                if (cmd >= 0x80) {
                    cmd = 0;
                }

                capa->nota_objetivo_portamento = cmd;

                if (ESPECIAL_ES_PORTAMENTO(capa->portamento)) {
                    capa->tiempo_portamento = *((estado)->pc++);
                    break;
                }

                sp3_a = leer_comprimido_m64_u16(estado);
                capa->tiempo_portamento = sp3_a;
                break;

            case 0xc8:
                capa->portamento.mode = 0;
                break;

            case 0xcb:
                sp3_a = leer_m64_s16(estado);
                capa->adsr.envelope = (struct EnvolventeAdsr*) (sec_jugador->sec_datos + sp3_a);
                capa->adsr.tasa_suelta = leer_m64_u8(estado);
                break;

            case 0xcc:
                capa->paneo_tambor_ignorar = true;
                break;

            default:
                switch (cmd & 0xf0) {
                    case 0xd0:
                        sp3_a = sec_jugador->corto_nota_velocidad_tabla[cmd & 0xf];
                        capa->cuadrado_velocidad = (f32) (sp3_a * sp3_a) / 16129.0f;
                        break;
                    case 0xe0:
                        capa->duracion_nota = sec_jugador->corto_nota_duracion_tabla[cmd & 0xf];
                        break;
                    default:
                        break;
                }
        }
    }

    if (cmd == 0xc0) {
        capa->delay = leer_comprimido_m64_u16(estado);
        capa->algo_parada = true;
    } else {
        capa->algo_parada = false;

        if (sec_canal->notas_grande == true) {
            switch (cmd & 0xc0) {
                case 0x00:
                    sp3_a = leer_comprimido_m64_u16(estado);
                    vel = *(estado->pc++);
                    capa->duracion_nota = *(estado->pc++);
                    capa->porcentaje_juego = sp3_a;
                    break;

                case 0x40:
                    sp3_a = leer_comprimido_m64_u16(estado);
                    vel = *(estado->pc++);
                    capa->duracion_nota = 0;
                    capa->porcentaje_juego = sp3_a;
                    break;

                case 0x80:
                    sp3_a = capa->porcentaje_juego;
                    vel = *(estado->pc++);
                    capa->duracion_nota = *(estado->pc++);
                    break;
            }
            if ((vel >= 0x80) || (vel < 0)) {
                vel = 0x0000007F;
            }
            cmd -= (cmd & 0xc0);
            capa->cuadrado_velocidad = ((f32) (vel) * (f32) vel) / 16129.0f;
        } else {
            switch (cmd & 0xc0) {
                case 0x00:
                    sp3_a = leer_comprimido_m64_u16(estado);
                    capa->porcentaje_juego = sp3_a;
                    break;

                case 0x40:
                    sp3_a = capa->corto_nota_predeterminado_juego_porcentaje;
                    break;

                case 0x80:
                    sp3_a = capa->porcentaje_juego;
                    break;
            }

            cmd -= cmd & 0xc0;
        }

        capa->delay = sp3_a;
        capa->duration = capa->duracion_nota * sp3_a >> 8;
        if ((sec_jugador->silenciado && (sec_canal->comportamiento_silencio & SILENCIO_COMPORTAMIENTO_PARADA_NOTAS) != 0) ||
            sec_canal->algo_parada_2) {
            capa->algo_parada = true;

        } else {
            s32 temporal_ = capa->inst_o_ola;
            if (temporal_ == 0xff) {
                if (!sec_canal->instrumento_tiene) {
                    return;
                }
                temporal_ = sec_canal->inst_o_ola;
            }
            if (temporal_ == 0) {
                cmd += sec_canal->trasposicion + capa->trasposicion;

                tambor = obtener_tambor(sec_canal->id_banco, cmd);
                if (tambor == NULL) {
                    capa->algo_parada = true;
                    capa->retardo_sin_uso = capa->delay;
                    return;
                } else {
                    capa->adsr.envelope = tambor->envelope;
                    capa->adsr.tasa_suelta = tambor->tasa_suelta;
                    if (!capa->paneo_tambor_ignorar) {
                        capa->paneo = tambor->paneo;
                    }
                    capa->sonido = &tambor->sonido;
                    capa->escala_frec = capa->sonido->ajuste;
                }
            } else {
                cmd += sec_jugador->trasposicion + sec_canal->trasposicion + capa->trasposicion;

                if (cmd >= 0x80) {
                    capa->algo_parada = true;
                } else {
                    if (capa->inst_o_ola == 0xffu) {
                        instrumento = sec_canal->instrumento;
                    } else {
                        instrumento = capa->instrumento;
                    }

                    if (capa->portamento.mode != 0) {
                        if (capa->nota_objetivo_portamento < cmd) {
                            vel = cmd;
                        } else {
                            vel = capa->nota_objetivo_portamento;
                        }

                        if (instrumento != NULL) {
                            sonido = obtener_sonido_banco_audio_instrumento(instrumento, vel);
                            sonido_mismo = (sonido == capa->sonido);
                            capa->sonido = sonido;
                            ajuste = sonido->ajuste;
                        } else {
                            capa->sonido = NULL;
                            ajuste = 1.0f;
                        }

                        temporal_f2 = frecuencias_nota[cmd] * ajuste;
                        temporal_f12 = frecuencias_nota[capa->nota_objetivo_portamento] * ajuste;

                        portamento = &capa->portamento;
                        switch (MODO_PORTAMENTO(capa->portamento)) {
                            case MODO_PORTAMENTO_1:
                            case MODO_PORTAMENTO_3:
                            case MODO_PORTAMENTO_5:
                                escala_frec = temporal_f12;
                                break;

                            case MODO_PORTAMENTO_2:
                            case MODO_PORTAMENTO_4:
                            default:
                                escala_frec = temporal_f2;
                                break;
                        }

                        portamento->extension = temporal_f2 / escala_frec - 1.0f;

                        if (ESPECIAL_ES_PORTAMENTO(capa->portamento)) {
                            portamento->speed = FLOTANTE_US(32512.0) * CONVERSION_FLOTANTE(sec_jugador->tempo) /
                                                ((f32) capa->delay * (f32) interno_tempo_a_externo *
                                                 CONVERSION_FLOTANTE(capa->tiempo_portamento));
                        } else {
                            portamento->speed = FLOTANTE_US(127.0) / CONVERSION_FLOTANTE(capa->tiempo_portamento);
                        }
                        portamento->act = 0.0f;
                        capa->escala_frec = escala_frec;
                        if (MODO_PORTAMENTO(capa->portamento) == MODO_PORTAMENTO_5) {
                            capa->nota_objetivo_portamento = cmd;
                        }
                    } else if (instrumento != NULL) {
                        sonido = obtener_sonido_banco_audio_instrumento(instrumento, cmd);
                        sonido_mismo = (sonido == capa->sonido);
                        capa->sonido = sonido;
                        capa->escala_frec = frecuencias_nota[cmd] * sonido->ajuste;
                    } else {
                        capa->sonido = NULL;
                        capa->escala_frec = frecuencias_nota[cmd];
                    }
                }
            }
            capa->retardo_sin_uso = capa->delay;
        }
    }

    if (capa->algo_parada == true) {
        if (capa->nota != NULL || capa->notas_continuo) {
            sec_canal_capa_nota_decaer(capa);
        }
        return;
    }

    cmd = false;
    if (!capa->notas_continuo) {
        cmd = true;
    } else if (capa->nota == NULL || capa->status == SONIDO_SITUACION_CARGA_NO_CARGADO) {
        cmd = true;
    } else if (sonido_mismo == false) {
        sec_canal_capa_nota_decaer(capa);
        cmd = true;
    } else if (capa != capa->nota->capa_padre) {
        cmd = true;
    } else if (capa->sonido == NULL) {
        inicializar_ola_sintetico(capa->nota, capa);
    }

    if (cmd != false) {
        capa->nota = reservar_nota(capa);
    }

    if (capa->nota != NULL && capa->nota->capa_padre == capa) {
        inicializar_vibrato_nota(capa->nota);
    }
    if (sec_canal) {}
}

u8 obtener_instrumento(struct CanalSecuencia* sec_canal, u8 inst_id, struct Instrumento** salida_inst,
                  struct AjustesAdsr* adsr) {
    struct Instrumento* inst;
    inst = obtener_interior_instrumento(sec_canal->id_banco, inst_id);
    if (inst == NULL) {
        *salida_inst = NULL;
        return 0;
    }
    adsr->envelope = inst->envelope;
    adsr->tasa_suelta = inst->tasa_suelta;
    *salida_inst = inst;
    inst_id++;
    return inst_id;
}

void fijar_instrumento(struct CanalSecuencia* sec_canal, u8 inst_id) {
    if (inst_id >= 0x80) {
        sec_canal->inst_o_ola = inst_id;
        sec_canal->instrumento = NULL;
    } else if (inst_id == 0x7f) {
        sec_canal->inst_o_ola = 0;
        sec_canal->instrumento = (struct Instrumento*) 1;
    } else {
        if ((sec_canal->inst_o_ola = obtener_instrumento(sec_canal, inst_id, &sec_canal->instrumento, &sec_canal->adsr)) ==
            0) {
            sec_canal->instrumento_tiene = false;
            return;
        }
    }
    sec_canal->instrumento_tiene = true;
}

void fijar_volumen_canal_secuencia(struct CanalSecuencia* sec_canal, u8 volumen) {
    sec_canal->volumen = CONVERSION_FLOTANTE(volumen) / FLOTANTE_US(127.0);
}
