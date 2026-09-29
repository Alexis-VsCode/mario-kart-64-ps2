// Hilos video y audio

void recibir_tareas_nuevo(void) {
    SIN_USO s32 relleno;
    struct TareaSP* tarea_sp;

    while (osRecvMesg(&sp_tarea_msj_cola, (OSMesg*) &tarea_sp, OS_MESG_NOBLOCK) != -1) {
        tarea_sp->state = ESTADO_SPTASK_NO_EMPEZADO;
        switch (tarea_sp->tarea.t.type) {
            case 2:
                siguiente_audio_sp_tarea = tarea_sp;
                break;
            case 1:
                siguiente_pantalla_sp_tarea = tarea_sp;
                break;
        }
    }

    if (actual_audio_sp_tarea == NULL && siguiente_audio_sp_tarea != NULL) {
        actual_audio_sp_tarea = siguiente_audio_sp_tarea;
        siguiente_audio_sp_tarea = NULL;
    }
    if (actual_pantalla_sp_tarea == NULL && siguiente_pantalla_sp_tarea != NULL) {
        actual_pantalla_sp_tarea = siguiente_pantalla_sp_tarea;
        siguiente_pantalla_sp_tarea = NULL;
    }
}

void fijar_manejador_vblank(s32 index, struct ManejadorVblank* manejador, OSMesgQueue* cola, OSMesg* mens) {
    manejador->queue = cola;
    manejador->msg = mens;
    switch (index) {
        case 1:
            manejador_vblank_1 = manejador;
            break;
        case 2:
            manejador_vblank_2 = manejador;
            break;
    }
}

void empezar_sptask_gfx(void) {
    if (tarea_sp_activo == NULL && actual_pantalla_sp_tarea != NULL &&
        actual_pantalla_sp_tarea->state == ESTADO_SPTASK_NO_EMPEZADO) {
        perfilador_registro_gfx_tiempo(TAREAS_EN_COLA);
        empezar_sptask(M_GFXTASK);
    }
}

void manejar_vblank(void) {
    temporizador_vblank += v_bl_ank_temporizador_iter;
    num_vblanks++;

    recibir_tareas_nuevo();

    if (actual_audio_sp_tarea != NULL) {
        if (tarea_sp_activo != NULL) {
            interrumpir_sptask_gfx();
        } else {
            perfilador_registro_vblank_tiempo();
            empezar_sptask(M_AUDTASK);
        }
    } else {
        if (tarea_sp_activo == NULL && actual_pantalla_sp_tarea != NULL &&
            actual_pantalla_sp_tarea->state != SPTASK_ESTADO_TERMINADO) {
            perfilador_registro_gfx_tiempo(TAREAS_EN_COLA);
            empezar_sptask(M_GFXTASK);
        }
    }

#if ENABLE_RUMBLE
    actualizar_vi_hilo_vibracion();
#endif

    if (manejador_vblank_1 != NULL) {
        osSendMesg(manejador_vblank_1->queue, manejador_vblank_1->msg, OS_MESG_NOBLOCK);
    }
    if (manejador_vblank_2 != NULL) {
        osSendMesg(manejador_vblank_2->queue, manejador_vblank_2->msg, OS_MESG_NOBLOCK);
    }
}

void manejar_completo_dp(void) {
    if (actual_pantalla_sp_tarea->msgqueue != NULL) {
        osSendMesg(actual_pantalla_sp_tarea->msgqueue, actual_pantalla_sp_tarea->msg, OS_MESG_NOBLOCK);
    }
    perfilador_registro_gfx_tiempo(COMPLETO_RDP);
    actual_pantalla_sp_tarea->state = SPTASK_ESTADO_TERMINADO_DP;
    actual_pantalla_sp_tarea = NULL;
}

void manejar_completo_sp(void) {
    struct TareaSP* tarea_sp_act = tarea_sp_activo;

    tarea_sp_activo = NULL;

    if (tarea_sp_act->state == SPTASK_ESTADO_INTERRUMPIDO) {
        if (osSpTaskYielded((OSTask*) tarea_sp_act) == 0) {
            tarea_sp_act->state = SPTASK_ESTADO_TERMINADO;
            perfilador_registro_gfx_tiempo(COMPLETO_RSP);
        }
        perfilador_registro_vblank_tiempo();
        empezar_sptask(M_AUDTASK);
    } else {
        tarea_sp_act->state = SPTASK_ESTADO_TERMINADO;
        if (tarea_sp_act->tarea.t.type == M_AUDTASK) {
            perfilador_registro_vblank_tiempo();
            if (actual_pantalla_sp_tarea != NULL) {
                if (actual_pantalla_sp_tarea->state != SPTASK_ESTADO_TERMINADO) {
                    if (actual_pantalla_sp_tarea->state != SPTASK_ESTADO_INTERRUMPIDO) {
                        perfilador_registro_gfx_tiempo(TAREAS_EN_COLA);
                    }
                    empezar_sptask(M_GFXTASK);
                }
            }
            actual_audio_sp_tarea = NULL;
            if (tarea_sp_act->msgqueue != NULL) {
                osSendMesg(tarea_sp_act->msgqueue, tarea_sp_act->msg, OS_MESG_NOBLOCK);
            }
        } else {
            perfilador_registro_gfx_tiempo(COMPLETO_RSP);
        }
    };
}

void hilo3_video(SIN_USO void* parametro0) {
    s32 i;
    u64* framebuffer1;
    OSMesg mens;
    SIN_USO s32 relleno[4];

    MARCAR_PUNTO_CONTROL("hilo 3: video");
    framebuffers_fisico[0] = (u16*) &framebuffer_0;
    framebuffers_fisico[1] = (u16*) &framebuffer_1;
    framebuffers_fisico[2] = (u16*) &framebuffer_2;

    // Clear framebuffer.
    framebuffer1 = (u64*) &framebuffer_1;
    for (i = 0; i < 19200; i++) {
        framebuffer1[i] = 0;
    }
    preparar_colas_msj();
    MARCAR_PUNTO_CONTROL("memoria del juego");
    MARCAR_TIEMPOS_PS2("principal: hilos");
    preparar_memoria_juego();
    MARCAR_TIEMPOS_PS2("memoria del juego");
    MARCAR_PUNTO_CONTROL("memoria del juego lista");

#ifdef TARGET_PS2
    crear_hilo(&hilo_audio, 4, &hilo4_audio, 0, pila_hilo_audio + CANTIDAD_ARREGLO(pila_hilo_audio), 110);
#else
    crear_hilo(&hilo_audio, 4, &hilo4_audio, 0, pila_hilo_audio + CANTIDAD_ARREGLO(pila_hilo_audio), 20);
#endif
    osStartThread(&hilo_audio);

    crear_hilo(&hilo_bucle_juego, 5, &hilo5_bucle_juego, 0, juego_bucle_hilo_pila + CANTIDAD_ARREGLO(juego_bucle_hilo_pila),
                  10);
    osStartThread(&hilo_bucle_juego);

    while (true) {
        osRecvMesg(&cola_msj_intr, &mens, OS_MESG_BLOCK);
        switch ((u32) mens) {
            case VBLANK_VI_MSJ:
                manejar_vblank();
                break;
            case COMPLETO_SP_MSJ:
                manejar_completo_sp();
                break;
            case COMPLETO_DP_MSJ:
                manejar_completo_dp();
                break;
            case MSJ_INICIO_GFX_SPTASK:
                empezar_sptask_gfx();
                break;
        }
    }
}

void funcion_800025D4(void) {
    funcion_80091B78();
    modo_pantalla_activo = MODO_PANTALLA_1P;
    fijar_perspectiva_y_proporcion_aspecto();
}

void funcion_80002600(void) {
    funcion_80091B78();
    modo_pantalla_activo = MODO_PANTALLA_1P;
    fijar_perspectiva_y_proporcion_aspecto();
}

void funcion_8000262C(void) {
    funcion_80091B78();
    modo_pantalla_activo = MODO_PANTALLA_1P;
    fijar_perspectiva_y_proporcion_aspecto();
}

void funcion_80002658(void) {
    funcion_80091B78();
    modo_pantalla_activo = MODO_PANTALLA_1P;
    fijar_perspectiva_y_proporcion_aspecto();
}

void actualizar_estado_juego(void) {
    switch (estado_juego) {
        case MENU_INICIO_DESDE_ABANDONAR:
            funcion_80002658();
            ahora_cargado_circuito_id = NULO_CIRCUITO;
            break;
        case MENU_PRINCIPAL_DESDE_ABANDONAR:
            funcion_800025D4();
            ahora_cargado_circuito_id = NULO_CIRCUITO;
            break;
        case MENU_SELECCION_JUGADOR_DESDE_ABANDONAR:
            funcion_80002600();
            ahora_cargado_circuito_id = NULO_CIRCUITO;
            break;
        case MENU_SELECCION_CIRCUITO_DESDE_ABANDONAR:
            funcion_8000262C();
            ahora_cargado_circuito_id = NULO_CIRCUITO;
            break;
        case CARRERA:
            EMPEZAR_TIEMPOS_PS2(GRUPO_CARGA_PISTA);
            inicializar_carrera_segmento();
            MARCAR_TIEMPOS_PS2("segmento de carrera");
            preparar_carrera();
            MARCAR_TIEMPOS_PS2("resto de la preparación");
            break;
        case FINAL:
            ahora_cargado_circuito_id = NULO_CIRCUITO;
            inicializar_secuencias_final_segmento();
            cargar_cinematica_ceremonia();
            break;
        case SECUENCIA_CREDITOS:
            ahora_cargado_circuito_id = NULO_CIRCUITO;
            inicializar_carrera_segmento();
            inicializar_secuencias_final_segmento();
            cargar_creditos();
            break;
    }
}

void hilo5_bucle_juego(SIN_USO void* parametro) {
    MARCAR_PUNTO_CONTROL("hilo 5: juego");
    osCreateMesgQueue(&gfx_cola_vblank, gfx_buf_msj, 1);
    osCreateMesgQueue(&cola_vblank_juego, &buf_msj_juego, 1);
    inicializar_mandos();
    if (!reinicio_suave_was) {
        borrar_buffer_nmi();
    }

    fijar_manejador_vblank(2, &manejador_vblank_juego, &cola_vblank_juego, (OSMesg) OS_EVENT_SW2);
    nmi_g_versus_resultados_2_p = &p_app_nmi_buffer[0];
    nmi_g_versus_resultados_3_p =
        &p_app_nmi_buffer[2];
    nmi_g_versus_resultados_4_p = &p_app_nmi_buffer[11];
    desconocido_nmi_4 = &p_app_nmi_buffer[23];
    desconocido_nmi_5 = &p_app_nmi_buffer[25];
    desconocido_nmi_6 = &p_app_nmi_buffer[28];
    MARCAR_PUNTO_CONTROL("inicio del dibujo");
    inicializar_renderizado();
    leer_mandos();
    MARCAR_PUNTO_CONTROL("inicio del sonido");
    funcion_800C5CB8();
    MARCAR_PUNTO_CONTROL("bucle de juego");

    while (true) {
        funcion_800CB2C4();

        if (siguiente_estado_juego != estado_juego) {
            estado_juego = siguiente_estado_juego;
            actualizar_estado_juego();
        }
        MARCAR_PUNTO_CONTROL("cuadro: inicio");
        perfilador_registro_hilo5_tiempo(INICIO_THREAD5);
        {
            EMPEZAR_PROF(JUEGO_PROF);
            config_gfx_pool();
            leer_mandos();
            MARCAR_PUNTO_CONTROL("cuadro: estado del juego");
            manejador_estado_juego();
            MARCAR_PUNTO_CONTROL("cuadro: listas de dibujo");
            maestro_fin_display_list();
            FIN_PROF(JUEGO_PROF);
        }
        PS2_TIEMPOS_ESPERADO_FRAME(gfx_pool->gfx_pool);
        mostrar_y_esperar_retrazo();
    }
}

void hilo4_audio(SIN_USO void* parametro) {
    SIN_USO u32 unused[3];
    MARCAR_PUNTO_CONTROL("hilo 4: audio");
    inicializar_audio();
    MARCAR_PUNTO_CONTROL("audio iniciado");
    osCreateMesgQueue(&sonido_cola_msj, sonido_buf_msj, CANTIDAD_ARREGLO(sonido_buf_msj));
#ifdef TARGET_PS2
    {
        void fijar_evento_audio_vi_os_ps2(OSMesgQueue * mq, OSMesg mens);

        fijar_evento_audio_vi_os_ps2(&sonido_cola_msj, (OSMesg) 512);
    }
#else
    fijar_manejador_vblank(1, &sonido_manejador_vblank, &sonido_cola_msj, (OSMesg) 512);
#endif

    while (true) {
        OSMesg mens;
        struct TareaSP* tarea_sp;

        osRecvMesg(&sonido_cola_msj, &mens, OS_MESG_BLOCK);

        perfilador_registro_hilo4_tiempo();

        {
            EMPEZAR_PROF(PROF_AUDIOGAME);
            tarea_sp = crear_siguiente_audio_frame_tarea();
            FIN_PROF(PROF_AUDIOGAME);
        }
        if (tarea_sp != NULL) {
            despachar_sptask_audio(tarea_sp);
        }
        perfilador_registro_hilo4_tiempo();
    }
}
