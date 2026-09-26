// Tareas y mandos

void funcion_80091B78(void);
void inicializar_audio(void);
#ifdef TARGET_PS2
s32 ps2_ritmo_pasos(s32 original);
void ps2_ritmo_imagen(u32 periodo);
#endif
void crear_hilo_depuracion(void);
void empezar_hilo_depuracion(void);
struct TareaSP* crear_siguiente_audio_frame_tarea(void);

struct ManejadorVblank* manejador_vblank_1 = NULL;
struct ManejadorVblank* manejador_vblank_2 = NULL;

struct TareaSP* tarea_sp_activo = NULL;
struct TareaSP* actual_audio_sp_tarea = NULL;
struct TareaSP* actual_pantalla_sp_tarea = NULL;
struct TareaSP* siguiente_audio_sp_tarea = NULL;
struct TareaSP* siguiente_pantalla_sp_tarea = NULL;

struct Mando mandos[JUGADORES_NUM];
struct Mando* mando_uno = &mandos[0];
struct Mando* mando_dos = &mandos[1];
struct Mando* mando_tres = &mandos[2];
struct Mando* mando_cuatro = &mandos[3];
struct Mando* mando_cinco = &mandos[4];
struct Mando* mando_seis = &mandos[5];
struct Mando* mando_siete = &mandos[6];
struct Mando* mando_ocho = &mandos[7];

Jugador jugadores[JUGADORES_NUM];
Jugador* jugador_uno = &jugadores[0];
Jugador* jugador_dos = &jugadores[1];
Jugador* jugador_tres = &jugadores[2];
Jugador* jugador_cuatro = &jugadores[3];
Jugador* jugador_cinco = &jugadores[4];
Jugador* jugador_seis = &jugadores[5];
Jugador* jugador_siete = &jugadores[6];
Jugador* jugador_ocho = &jugadores[7];

Jugador* copia_jugador_uno = &jugadores[0];
Jugador* copia_jugador_dos = &jugadores[1];
SIN_USO Jugador* copia_jugador_tres = &jugadores[2];
SIN_USO Jugador* copia_jugador_cuatro = &jugadores[3];

SIN_USO s32 dato_800FD850[3];
struct GfxPool gfx_pools[2];
struct GfxPool* gfx_pool;

SIN_USO s32 gfx_pool_margen;
struct ManejadorVblank manejador_vblank_juego;
struct ManejadorVblank sonido_manejador_vblank;
OSMesgQueue cola_msj_dma, cola_vblank_juego, gfx_cola_vblank, sin_uso_g_mens_cola, cola_msj_intr, sp_tarea_msj_cola;
OSMesgQueue sonido_cola_msj;
OSMesg sonido_buf_msj[1];
OSMesg buf_msj_dma[1], buf_msj_juego;
OSMesg gfx_buf_msj[1];
SIN_USO OSMesg dato_8014F010, dato_8014F014;
OSMesg buf_msj_intr[16], sp_tarea_msj_buf[16];
OSMesg msj_recibido_principal;
OSIoMesg msj_io_dma;
OSMesgQueue si_evento_msj_cola;
OSMesg si_evento_msj_buf[3];

OSContStatus situaciones_mando[4];
OSContPad rellenos_mando[4];
u8 bits_mando;
CuadriculaColision cuadricula_colision[1024];
u16 actores_num;
u16 cantidad_objeto_matriz;
s32 pasos_por_frame;
f32 dato_80150118;

u16 reinicio_suave_was;
u16 dato_8015011E;

s32 dato_80150120;
s32 modo_goto;
SIN_USO s32 dato_80150128;
SIN_USO s32 dato_8015012C;
f32 acercar_camara[4];
SIN_USO s32 dato_80150140;
SIN_USO s32 dato_80150144;
f32 aspecto_pantalla;
f32 persp_lejos_circuito;
f32 circuito_cerca_persp;
SIN_USO f32 dato_80150154;

struct dato_80150158 g_d_80150158[16];
uintptr_t tabla_segmento[16];
Gfx* display_list_cabeza;

struct TareaSP* gfx_tarea_sp;
s32 dato_801502A0;
s32 dato_801502A4;
u16* framebuffers_fisico[3];
uintptr_t fisico_zbuffer;
SIN_USO u32 dato_801502B8;
SIN_USO u32 dato_801502BC;
Mat4 dato_801502C0;

s32 margen[2048];

u16 dato_80152300[4];
u16 dato_80152308;

SIN_USO OSThread hilo_margen;
OSThread hilo_inactivo;
ALIGNED8 u8 pila_hilo_inactivo[TAMANIO_PILA];
OSThread hilo_video;
ALIGNED8 u8 pila_hilo_video[TAMANIO_PILA];
SIN_USO OSThread dato_80156820;
SIN_USO ALIGNED8 u8 d_8015680_pila[TAMANIO_PILA];
OSThread hilo_bucle_juego;
ALIGNED8 u8 juego_bucle_hilo_pila[TAMANIO_PILA];
OSThread hilo_audio;
ALIGNED8 u8 pila_hilo_audio[TAMANIO_PILA];
SIN_USO OSThread dato_8015CD30;
SIN_USO ALIGNED8 u8 d_8015CD30_pila[TAMANIO_PILA / 2];

ALIGNED8 u8 gfx_sp_tarea_cesion_buffer[4352];
ALIGNED8 u32 gfx_pila_tarea_sp[256];
OSMesg buf_msj_pi[32];
OSMesgQueue cola_msj_pi;

s32 estado_juego = 0xFFFF;
u16 estado_carrera = NINGUNO_CARRERA;
u16 dato_800DC514 = 0;
u16 modo_render_creditos = 0;
u16 modo_demo = INACTIVO_MODO_DEMO;
u16 modo_depuracion_activacion = MODO_DEPURACION_ACTIVACION;
s32 siguiente_estado_juego = 7;
SIN_USO s32 dato_800DC528 = 1;
s32 modo_pantalla_activo = MODO_PANTALLA_1P;
s32 seleccion_modo_pantalla = MODO_PANTALLA_1P;
SIN_USO s32 dato_800DC534 = 0;
s32 seleccion_cantidad_jugador_1 = 2;

s32 seleccion_modo = GRAN_PREMIO;
s32 dato_800DC540 = 0;
s32 dato_800DC544 = 0;
s32 seleccion_cc = CC_50;
s32 temporizador_global = 0;
SIN_USO s32 dato_800DC550 = 0;
SIN_USO s32 dato_800DC554 = 0;
SIN_USO s32 dato_800DC558 = 0;
u16 s_framebuffer_renderizado = 0;
u16 framebuffer_renderizado = 0;
SIN_USO u16 dato_800DC564 = 0;
s32 dato_800DC568 = 0;
s32 dato_800DC56C[8] = { 0 };
s16 num_vblanks = 0;
SIN_USO s16 dato_800DC590 = 0;
f32 temporizador_vblank = 0.0f;
f32 temporizador_circuito = 0.0f;

void crear_hilo(OSThread* hilo_2, OSId id, void (*entry)(void*), void* parametro, void* sp, OSPri prio) {
    hilo_2->next = NULL;
    hilo_2->queue = NULL;
    osCreateThread(hilo_2, id, entry, parametro, sp, prio);
}
void es_inicializacion_printf(void);
void funcion_principal(void) {
#ifdef VERSION_EU
    osTvType = TV_TYPE_PAL;
#endif
    osInitialize();
#ifdef DEBUG
    es_inicializacion_printf();
#endif
    crear_hilo(&hilo_inactivo, 1, &hilo1_inactivo, NULL, pila_hilo_inactivo + CANTIDAD_ARREGLO(pila_hilo_inactivo), 100);
    osStartThread(&hilo_inactivo);
}

void hilo1_inactivo(void* parametro) {
    MARCAR_PUNTO_CONTROL("thread1_idle");
    osCreateViManager(OS_PRIORITY_VIMGR);
#ifdef VERSION_EU
    osViSetMode(&osViModeTable[OS_VI_PAL_LAN1]);
#else
    if (osTvType == TV_TYPE_NTSC) {
        osViSetMode(&osViModeTable[OS_VI_NTSC_LAN1]);
    } else {
        osViSetMode(&osViModeTable[OS_VI_MPAL_LAN1]);
    }
#endif
    osViBlack(true);
    osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
    osCreatePiManager(OS_PRIORITY_PIMGR, &cola_msj_pi, buf_msj_pi, CANTIDAD_ARREGLO(buf_msj_pi));
    reinicio_suave_was = (s16) osResetType;
    crear_hilo_depuracion();
    empezar_hilo_depuracion();
    crear_hilo(&hilo_video, 3, &hilo3_video, parametro, pila_hilo_video + CANTIDAD_ARREGLO(pila_hilo_video), 100);
    osStartThread(&hilo_video);
    osSetThreadPri(NULL, 0);

#if defined(TARGET_PS2) && defined(SMK64_MEDIDOR)
    {
        void medidor_bucle_inactivo(void);
        medidor_bucle_inactivo();
    }
#elif defined(TARGET_PS2)
    {
        void registrar_bucle_inactivo(u32 empezar, u32 largo);
        registrar_bucle_inactivo(0, 0);
    }
#endif
    while (true) {
        ;
    }
}

void preparar_colas_msj(void) {
    osCreateMesgQueue(&cola_msj_dma, buf_msj_dma, CANTIDAD_ARREGLO(buf_msj_dma));
    osCreateMesgQueue(&sp_tarea_msj_cola, sp_tarea_msj_buf, CANTIDAD_ARREGLO(sp_tarea_msj_buf));
    osCreateMesgQueue(&cola_msj_intr, buf_msj_intr, CANTIDAD_ARREGLO(buf_msj_intr));
    osViSetEvent(&cola_msj_intr, (OSMesg) VBLANK_VI_MSJ, 1);
    osSetEventMesg(OS_EVENT_SP, &cola_msj_intr, (OSMesg) COMPLETO_SP_MSJ);
    osSetEventMesg(OS_EVENT_DP, &cola_msj_intr, (OSMesg) COMPLETO_DP_MSJ);
}

void empezar_sptask(s32 tipo_tarea) {
    if (tipo_tarea == M_AUDTASK) {
        tarea_sp_activo = actual_audio_sp_tarea;
    } else {
        tarea_sp_activo = actual_pantalla_sp_tarea;
    }
    osSpTaskLoad(&tarea_sp_activo->tarea);
    osSpTaskStartGo(&tarea_sp_activo->tarea);
    tarea_sp_activo->state = EJECUTANDO_ESTADO_SPTASK;
}

void crear_estructura_tarea_gfx(void) {
    gfx_tarea_sp->msgqueue = &gfx_cola_vblank;
    gfx_tarea_sp->msg = (OSMesg) 2;
    gfx_tarea_sp->tarea.t.type = M_GFXTASK;
    gfx_tarea_sp->tarea.t.flags = OS_TASK_DP_WAIT;
    gfx_tarea_sp->tarea.t.ucode_boot = rspF3DBootStart;
    gfx_tarea_sp->tarea.t.ucode_boot_size = ((u8*) rspF3DBootEnd - (u8*) rspF3DBootStart);
    if (estado_juego != CARRERA || seleccion_cantidad_jugador_1 == 1) {
        gfx_tarea_sp->tarea.t.ucode = gspF3DEXTextStart;
        gfx_tarea_sp->tarea.t.ucode_data = gspF3DEXDataStart;
    } else {
        gfx_tarea_sp->tarea.t.ucode = gspF3DLXTextStart;
        gfx_tarea_sp->tarea.t.ucode_data = gspF3DLXDataStart;
    }
    gfx_tarea_sp->tarea.t.flags = 0;
    gfx_tarea_sp->tarea.t.flags = OS_TASK_DP_WAIT;
    gfx_tarea_sp->tarea.t.ucode_size = SP_UCODE_SIZE;
    gfx_tarea_sp->tarea.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    gfx_tarea_sp->tarea.t.dram_stack = (u64*) &gfx_pila_tarea_sp;
    gfx_tarea_sp->tarea.t.dram_stack_size = SP_DRAM_STACK_SIZE8;
    gfx_tarea_sp->tarea.t.output_buff = (u64*) &gfx_sp_tarea_salida_buffer;
    gfx_tarea_sp->tarea.t.output_buff_size = (u64*) ((u8*) gfx_sp_tarea_salida_buffer + sizeof(gfx_sp_tarea_salida_buffer));
    gfx_tarea_sp->tarea.t.data_ptr = (u64*) gfx_pool->gfx_pool;
    gfx_tarea_sp->tarea.t.data_size = (display_list_cabeza - gfx_pool->gfx_pool) * sizeof(Gfx);
    funcion_8008C214();
    gfx_tarea_sp->tarea.t.yield_data_ptr = (u64*) &gfx_sp_tarea_cesion_buffer;
    gfx_tarea_sp->tarea.t.yield_data_size = OS_YIELD_DATA_SIZE;
}

void inicializar_mandos(void) {
    osCreateMesgQueue(&si_evento_msj_cola, &si_evento_msj_buf[0], CANTIDAD_ARREGLO(si_evento_msj_buf));
    osSetEventMesg(OS_EVENT_SI, &si_evento_msj_cola, (OSMesg) 0x33333333);
    osContInit(&si_evento_msj_cola, &bits_mando, situaciones_mando);
    if ((bits_mando & 1) == 0) {
        es_mando_1_desconectado = true;
    } else {
        es_mando_1_desconectado = false;
    }
}

void actualizar_mando(s32 index) {
    struct Mando* mando = &mandos[index];
    u16 palanca;

    if (es_mando_1_desconectado) {
        return;
    }

    mando->palanca_x_crudo = rellenos_mando[index].stick_x;
    mando->palanca_y_crudo = rellenos_mando[index].stick_y;

    if ((rellenos_mando[index].button & D_CBUTTONS) != 0) {
        rellenos_mando[index].button |= Z_TRIG;
    }
    mando->boton_pulsado = rellenos_mando[index].button & (rellenos_mando[index].button ^ mando->button);
    mando->boton_apretado = mando->button & (rellenos_mando[index].button ^ mando->button);
    mando->button = rellenos_mando[index].button;

    palanca = 0;
    if (mando->palanca_x_crudo < -50) {
        palanca |= L_JPAD;
    }
    if (mando->palanca_x_crudo > 50) {
        palanca |= R_JPAD;
    }
    if (mando->palanca_y_crudo < -50) {
        palanca |= D_JPAD;
    }
    if (mando->palanca_y_crudo > 50) {
        palanca |= U_JPAD;
    }
    mando->palanca_pulsado = palanca & (palanca ^ mando->sentido_palanca);
    mando->palanca_apretado = mando->sentido_palanca & (palanca ^ mando->sentido_palanca);
    mando->sentido_palanca = palanca;
}

void leer_mandos(void) {
    OSMesg mens;

    osContStartReadData(&si_evento_msj_cola);
    osRecvMesg(&si_evento_msj_cola, &mens, OS_MESG_BLOCK);
    osContGetReadData(rellenos_mando);
    actualizar_mando(0);
    actualizar_mando(1);
    actualizar_mando(2);
    actualizar_mando(3);
    mando_cinco->button = (s16) (((mando_uno->button | mando_dos->button) | mando_tres->button) |
                                     mando_cuatro->button);
    mando_cinco->boton_pulsado =
        (s16) (((mando_uno->boton_pulsado | mando_dos->boton_pulsado) | mando_tres->boton_pulsado) |
               mando_cuatro->boton_pulsado);
    mando_cinco->boton_apretado = (s16) (((mando_uno->boton_apretado | mando_dos->boton_apretado) |
                                               mando_tres->boton_apretado) |
                                              mando_cuatro->boton_apretado);
    mando_cinco->sentido_palanca =
        (s16) (((mando_uno->sentido_palanca | mando_dos->sentido_palanca) | mando_tres->sentido_palanca) |
               mando_cuatro->sentido_palanca);
    mando_cinco->palanca_pulsado =
        (s16) (((mando_uno->palanca_pulsado | mando_dos->palanca_pulsado) | mando_tres->palanca_pulsado) |
               mando_cuatro->palanca_pulsado);
    mando_cinco->palanca_apretado =
        (s16) (((mando_uno->palanca_apretado | mando_dos->palanca_apretado) | mando_tres->palanca_apretado) |
               mando_cuatro->palanca_apretado);
}

void funcion_80000BEC(void) {
    fisico_zbuffer = VIRTUAL_A_FISICO(&g_zbuffer);
}

void despachar_sptask_audio(struct TareaSP* tarea_sp) {
#ifdef TARGET_PS2
    void ejecutar_tarea_audio_rsp_ps2(OSTask * tarea);

    ejecutar_tarea_audio_rsp_ps2(&tarea_sp->tarea);
    tarea_sp->state = SPTASK_ESTADO_TERMINADO;
#else
    osWritebackDCacheAll();
    osSendMesg(&sp_tarea_msj_cola, tarea_sp, OS_MESG_NOBLOCK);
#endif
}

void ejecutar_display_list(struct TareaSP* tarea_sp) {
    osWritebackDCacheAll();
    tarea_sp->state = ESTADO_SPTASK_NO_EMPEZADO;
    if (actual_pantalla_sp_tarea == NULL) {
        actual_pantalla_sp_tarea = tarea_sp;
        siguiente_pantalla_sp_tarea = NULL;
        osSendMesg(&cola_msj_intr, (OSMesg) MSJ_INICIO_GFX_SPTASK, OS_MESG_NOBLOCK);
    } else {
        siguiente_pantalla_sp_tarea = tarea_sp;
    }
}

void inicializar_rcp(void) {
    mover_tabla_segmento_a_dmem();
    inicializar_rdp();
    fijar_viewport();
    seleccionar_framebuffer();
    inicializar_zbuffer();
}

void maestro_fin_display_list(void) {
    gDPFullSync(display_list_cabeza++);
    gSPEndDisplayList(display_list_cabeza++);
    crear_estructura_tarea_gfx();
}

void* borrar_framebuffer(s32 color) {
    gDPPipeSync(display_list_cabeza++);

    gDPSetRenderMode(display_list_cabeza++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCycleType(display_list_cabeza++, G_CYC_FILL);

    gDPSetFillColor(display_list_cabeza++, color);
    gDPFillRectangle(display_list_cabeza++, 0, 0, ANCHO_PANTALLA - 1, ALTURA_PANTALLA - 1);

    gDPPipeSync(display_list_cabeza++);

    gDPSetCycleType(display_list_cabeza++, G_CYC_1CYCLE);
}

void inicializar_renderizado(void) {
    gfx_pool = &gfx_pools[0];
    fijar_direccion_base_segmento(1, gfx_pool);
    gfx_tarea_sp = &gfx_pool->tarea_sp;
    display_list_cabeza = gfx_pool->gfx_pool;
    inicializar_rcp();
    borrar_framebuffer(0);
    maestro_fin_display_list();
    PS2_TIEMPOS_ESPERADO_FRAME(gfx_pool->gfx_pool);
    ejecutar_display_list(&gfx_pool->tarea_sp);
    framebuffer_renderizado++;
    temporizador_global++;
}

void config_gfx_pool(void) {
    gfx_pool = &gfx_pools[temporizador_global & 1];
    fijar_direccion_base_segmento(1, gfx_pool);
    display_list_cabeza = gfx_pool->gfx_pool;
    gfx_tarea_sp = &gfx_pool->tarea_sp;
}

void mostrar_y_esperar_retrazo(void) {
    perfilador_registro_hilo5_tiempo(ANTES_DISPLAY_LISTS);
    osRecvMesg(&gfx_cola_vblank, &msj_recibido_principal, OS_MESG_BLOCK);
    ejecutar_display_list(&gfx_pool->tarea_sp);
    perfilador_registro_hilo5_tiempo(DESPUES_DISPLAY_LISTS);
    osRecvMesg(&cola_vblank_juego, &msj_recibido_principal, OS_MESG_BLOCK);
    osViSwapBuffer((void*) FISICO_A_VIRTUAL(framebuffers_fisico[s_framebuffer_renderizado]));
    perfilador_registro_hilo5_tiempo(FIN_THREAD5);
    osRecvMesg(&cola_vblank_juego, &msj_recibido_principal, OS_MESG_BLOCK);
#ifdef TARGET_PS2
    {
        static u32 ultimo_vblank_frame;
        u32 contador_vblank(void);

        if (estado_juego == CARRERA && pasos_por_frame > 2) {
            while (contador_vblank() - ultimo_vblank_frame < (u32) pasos_por_frame) {
                osRecvMesg(&cola_vblank_juego, &msj_recibido_principal, OS_MESG_BLOCK);
            }
        }
        if (estado_juego == CARRERA && modo_pantalla_activo != MODO_PANTALLA_1P) {
            ps2_ritmo_imagen(contador_vblank() - ultimo_vblank_frame);
        }
        ultimo_vblank_frame = contador_vblank();
    }
#endif
    fijar_framebuffer_pantalla_error(framebuffers_fisico[s_framebuffer_renderizado]);

    if (++s_framebuffer_renderizado == 3) {
        s_framebuffer_renderizado = 0;
    }
    if (++framebuffer_renderizado == 3) {
        framebuffer_renderizado = 0;
    }
    temporizador_global++;
}

#ifdef TARGET_PS2
/* En PS2 el codigo de estos segmentos no se recarga */
void reiniciar_segmento_final(void);
void reiniciar_segmento_carreras(void);

void inicializar_secuencias_final_segmento(void) {
    reiniciar_segmento_final();
}

void inicializar_carrera_segmento(void) {
    reiniciar_segmento_carreras();
}
#else
void inicializar_secuencias_final_segmento(void) {
    bzero((void*) FINAL_SEG, TAMANIO_FINAL_SEG);
    osWritebackDCacheAll();
    copiar_dma((u8*) FINAL_SEG, (u8*) SEG_FINAL_ROM_INICIO, SEG_FINAL_ROM_TAMANIO);
    osInvalICache((void*) FINAL_SEG, TAMANIO_FINAL_SEG);
    osInvalDCache((void*) FINAL_SEG, TAMANIO_FINAL_SEG);
}

void inicializar_carrera_segmento(void) {
    bzero((void*) CARRERA_SEG, TAMANIO_CARRERA_SEG);
    osWritebackDCacheAll();
    copiar_dma((u8*) CARRERA_SEG, (u8*) SEG_CARRERA_ROM_INICIO, SEG_CARRERA_ROM_TAMANIO);
    osInvalICache((void*) CARRERA_SEG, TAMANIO_CARRERA_SEG);
    osInvalDCache((void*) CARRERA_SEG, TAMANIO_CARRERA_SEG);
}
#endif

void copiar_dma(u8* dest, u8* direccion_rom, size_t size) {

    osInvalDCache(dest, size);
    while (size > 0x100) {
        osPiStartDma(&msj_io_dma, 0, 0, (uintptr_t) direccion_rom, dest, 0x100, &cola_msj_dma);
        osRecvMesg(&cola_msj_dma, &msj_recibido_principal, 1);
        size -= 0x100;
        direccion_rom += 0x100;
        dest += 0x100;
    }
    if (size != 0) {
        osPiStartDma(&msj_io_dma, 0, 0, (uintptr_t) direccion_rom, dest, size, &cola_msj_dma);
        osRecvMesg(&cola_msj_dma, &msj_recibido_principal, 1);
    }
}

void preparar_memoria_juego(void) {
    SIN_USO u32 relleno[2];
    ptrdiff_t comun_circuito_datos_tamanio;
    uintptr_t textura_tamanio_seg;
    ptrdiff_t textura_inicio_seg;
    uintptr_t memoria_reservado;
    SIN_USO s32 margen_desconocido;

    MARCAR_PUNTO_CONTROL("sgm: init_segment_racing");
    inicializar_carrera_segmento();
    ptr_fin_monton = CARRERA_SEG;
    fijar_direccion_base_segmento(0, (void*) INICIO_SEG);

    inicializar_pool_memoria(INICIO_POOL_MEMORIA, FIN_POOL_MEMORIA);

    funcion_80000BEC();

    osInvalDCache((void*) TABLAS_TRIG, TAMANIO_TABLAS_TRIG);
    osPiStartDma(&msj_io_dma, 0, 0, TRIG_TABLAS_ROM_INICIO, (void*) TABLAS_TRIG, TAMANIO_TABLAS_TRIG, &cola_msj_dma);
    osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);

    MARCAR_PUNTO_CONTROL("sgm: load_data seg2");
    fijar_direccion_base_segmento(2, (void*) cargar_datos(INICIO_DATOS_SEG, FIN_DATOS_SEG));

    comun_circuito_datos_tamanio = TAMANIO_TEXTURAS_COMUN;
    comun_circuito_datos_tamanio = ALIGN16(comun_circuito_datos_tamanio);

#ifdef AVOID_UB
    textura_inicio_seg = (ptrdiff_t) CARRERA_SEG - comun_circuito_datos_tamanio;
#else
    textura_inicio_seg = CARRERA_SEG - comun_circuito_datos_tamanio;
#endif
    osPiStartDma(&msj_io_dma, 0, 0, COMUN_TEXTURAS_ROM_INICIO, (void*) textura_inicio_seg, comun_circuito_datos_tamanio,
                 &cola_msj_dma);
    osRecvMesg(&cola_msj_dma, &msj_recibido_principal, OS_MESG_BLOCK);

    textura_tamanio_seg = TAMANIO_SIN_COMPRIMIR_MIO0(textura_inicio_seg);
    textura_tamanio_seg = ALIGN16(textura_tamanio_seg);
    memoria_reservado = siguiente_libre_memoria_direccion;
    MARCAR_PUNTO_CONTROL("sgm: mio0 texturas comunes");
    mio0decode((u8*) textura_inicio_seg, (u8*) memoria_reservado);
    fijar_direccion_base_segmento(0xD, (void*) memoria_reservado);
#ifdef TARGET_PS2
    {
        void ps2_tmem_estatico_bloque(const void* empezar, u32 size, int permanente);

        ps2_tmem_estatico_bloque((void*) memoria_reservado, textura_tamanio_seg, 1);
    }
#endif

    siguiente_libre_memoria_direccion += textura_tamanio_seg;

    libre_memoria_reinicio_ancla = siguiente_libre_memoria_direccion;
}

void inicializar_framebuffer_limpieza_juego(void) {
    siguiente_estado_juego = 0;
    borrar_framebuffer(0);
}

void bucle_logica_carrera(void) {
    s16 i;
    u16 rot_y;

    cantidad_objeto_matriz = 0;
    cantidad_efecto_matriz = 0;
    if (juego_en_pausa != 0) {
        funcion_80290B14();
    }
    if (es_en_abandonar_a_transicion_menu != 0) {
        funcion_802A38B4();
        return;
    }

    if (num_vblanks >= 6) {
        num_vblanks = 5;
    }
    if (num_vblanks < 0) {
        num_vblanks = 1;
    }
    funcion_802A4EF4();

    switch (modo_pantalla_activo) {
        case MODO_PANTALLA_1P:
            pasos_por_frame = 2;
            bucle_repeticiones();
            if (juego_en_pausa == 0) {
                for (i = 0; i < pasos_por_frame; i++) {
                    if (dato_8015011E) {
                        temporizador_circuito += ITER_TEMPORIZADOR_CIRCUITO;
                    }
                    funcion_802909F0();
                    evaluar_colision_para_jugadores_y_actores();
                    manejar_pulsacion_a_para_todos_jugadores_durante_carrera();
                    funcion_8001EE98(copia_jugador_uno, camara1, 0);
                    funcion_80028F70();
                    funcion_8028F474();
                    funcion_80059AC8();
                    actualizar_actores_circuito();
                    actualizar_agua_circuito();
                    funcion_8028FCBC();
                }
                funcion_80022744();
            }
            funcion_8005A070();
            num_vblanks = 0;
            perfilador_registro_hilo5_tiempo(EJECUTAR_GUION_NIVEL);
            dato_8015F788 = 0;
            renderizar_pantalla_jugador_uno_1j();
            if (!modo_depuracion_activacion) {
                dato_800DC514 = false;
            } else {
                if (dato_800DC514) {

                    if ((mando_uno->boton_pulsado & R_TRIG) && (mando_uno->button & A_BUTTON) &&
                        (mando_uno->button & B_BUTTON)) {
                        dato_800DC514 = false;
                    }

                    rot_y = camara1->rot[1];
                    cantidad_camino_depuracion = dato_800DC5EC->contador_camino;
                    if (rot_y < GRADOS(45)) {
                        funcion_80057A50(40, 100, "SOUTH  ", cantidad_camino_depuracion);
                    } else if (rot_y < GRADOS(135)) {
                        funcion_80057A50(40, 100, "EAST   ", cantidad_camino_depuracion);
                    } else if (rot_y < GRADOS(225)) {
                        funcion_80057A50(40, 100, "NORTH  ", cantidad_camino_depuracion);
                    } else if (rot_y < GRADOS(315)) {
                        funcion_80057A50(40, 100, "WEST   ", cantidad_camino_depuracion);
                    } else {
                        funcion_80057A50(40, 100, "SOUTH  ", cantidad_camino_depuracion);
                    }

                } else {
                    if ((mando_uno->boton_pulsado & L_TRIG) && (mando_uno->button & A_BUTTON) &&
                        (mando_uno->button & B_BUTTON)) {
                        dato_800DC514 = true;
                    }
                }
            }
            break;

        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            if (id_circuito_actual == CIRCUITO_DK_JUNGLE) {
                pasos_por_frame = 3;
            } else {
                pasos_por_frame = 2;
            }
#ifdef TARGET_PS2
            pasos_por_frame = ps2_ritmo_pasos(pasos_por_frame);
#endif
            if (juego_en_pausa == 0) {
                for (i = 0; i < pasos_por_frame; i++) {
                    if (dato_8015011E != 0) {
                        temporizador_circuito += ITER_TEMPORIZADOR_CIRCUITO;
                    }
                    funcion_802909F0();
                    evaluar_colision_para_jugadores_y_actores();
                    manejar_pulsacion_a_para_todos_jugadores_durante_carrera();
                    funcion_8001EE98(copia_jugador_uno, camara1, 0);
                    funcion_80029060();
                    funcion_8001EE98(copia_jugador_dos, camara2, 1);
                    funcion_80029150();
                    funcion_8028F474();
                    funcion_80059AC8();
                    actualizar_actores_circuito();
                    actualizar_agua_circuito();
                    funcion_8028FCBC();
                }
                funcion_80022744();
            }
            funcion_8005A070();
            perfilador_registro_hilo5_tiempo(EJECUTAR_GUION_NIVEL);
            num_vblanks = 0;
            mover_tabla_segmento_a_dmem();
            inicializar_rdp();
            if (dato_800DC5B0 != 0) {
                seleccionar_framebuffer();
            }
            dato_8015F788 = 0;
            if (indice_ganador_jugador == 0) {
                renderizar_vertical_pantalla_jugador_dos_2j();
                renderizar_vertical_pantalla_jugador_uno_2j();
            } else {
                renderizar_vertical_pantalla_jugador_uno_2j();
                renderizar_vertical_pantalla_jugador_dos_2j();
            }
            break;

        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:

            if (id_circuito_actual == CIRCUITO_DK_JUNGLE) {
                pasos_por_frame = 3;
            } else {
                pasos_por_frame = 2;
            }
#ifdef TARGET_PS2
            pasos_por_frame = ps2_ritmo_pasos(pasos_por_frame);
#endif

            if (juego_en_pausa == 0) {
                for (i = 0; i < pasos_por_frame; i++) {
                    if (dato_8015011E != 0) {
                        temporizador_circuito += ITER_TEMPORIZADOR_CIRCUITO;
                    }
                    funcion_802909F0();
                    evaluar_colision_para_jugadores_y_actores();
                    manejar_pulsacion_a_para_todos_jugadores_durante_carrera();
                    funcion_8001EE98(copia_jugador_uno, camara1, 0);
                    funcion_80029060();
                    funcion_8001EE98(copia_jugador_dos, camara2, 1);
                    funcion_80029150();
                    funcion_8028F474();
                    funcion_80059AC8();
                    actualizar_actores_circuito();
                    actualizar_agua_circuito();
                    funcion_8028FCBC();
                }
                funcion_80022744();
            }
            perfilador_registro_hilo5_tiempo(EJECUTAR_GUION_NIVEL);
            num_vblanks = (u16) 0;
            funcion_8005A070();
            mover_tabla_segmento_a_dmem();
            inicializar_rdp();
            if (dato_800DC5B0 != 0) {
                seleccionar_framebuffer();
            }
            dato_8015F788 = 0;
            if (indice_ganador_jugador == 0) {
                renderizar_horizontal_pantalla_jugador_dos_2j();
                renderizar_horizontal_pantalla_jugador_uno_2j();
            } else {
                renderizar_horizontal_pantalla_jugador_uno_2j();
                renderizar_horizontal_pantalla_jugador_dos_2j();
            }

            break;

        case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
            if (seleccion_cantidad_jugador_1 == 3) {
                switch (id_circuito_actual) {
                    case CIRCUITO_BOWSER_CASTLE:
                    case CIRCUITO_MOO_MOO_FARM:
                    case CIRCUITO_SKYSCRAPER:
                    case CIRCUITO_DK_JUNGLE:
                        pasos_por_frame = 3;
                        break;
                    default:
                        pasos_por_frame = 2;
                        break;
                }
            } else {
                switch (id_circuito_actual) {
                    case CIRCUITO_BLOCK_FORT:
                    case CIRCUITO_DOUBLE_DECK:
                    case CIRCUITO_BIG_DONUT:
                        pasos_por_frame = 2;
                        break;
                    case CIRCUITO_DK_JUNGLE:
                        pasos_por_frame = 4;
                        break;
                    default:
                        pasos_por_frame = 3;
                        break;
                }
            }
#ifdef TARGET_PS2
            pasos_por_frame = ps2_ritmo_pasos(pasos_por_frame);
#endif
            if (juego_en_pausa == 0) {
                for (i = 0; i < pasos_por_frame; i++) {
                    if (dato_8015011E != 0) {
                        temporizador_circuito += ITER_TEMPORIZADOR_CIRCUITO;
                    }
                    funcion_802909F0();
                    evaluar_colision_para_jugadores_y_actores();
                    manejar_pulsacion_a_para_todos_jugadores_durante_carrera();
                    funcion_8001EE98(copia_jugador_uno, camara1, 0);
                    funcion_80029158();
                    funcion_8001EE98(jugador_dos, camara2, 1);
                    funcion_800291E8();
                    funcion_8001EE98(jugador_tres, camara3, 2);
                    funcion_800291F0();
                    funcion_8001EE98(jugador_cuatro, camara4, 3);
                    funcion_800291F8();
                    funcion_8028F474();
                    funcion_80059AC8();
                    actualizar_actores_circuito();
                    actualizar_agua_circuito();
                    funcion_8028FCBC();
                }
                funcion_80022744();
            }
            funcion_8005A070();
            num_vblanks = 0;
            perfilador_registro_hilo5_tiempo(EJECUTAR_GUION_NIVEL);
            mover_tabla_segmento_a_dmem();
            inicializar_rdp();
            if (dato_800DC5B0 != 0) {
                seleccionar_framebuffer();
            }
            dato_8015F788 = 0;
            if (indice_ganador_jugador == 0) {
                renderizar_pantalla_jugador_dos_3j_4j();
                renderizar_pantalla_jugador_tres_3j_4j();
                renderizar_pantalla_jugador_cuatro_3j_4j();
                renderizar_pantalla_jugador_uno_3j_4j();
            } else if (indice_ganador_jugador == 1) {
                renderizar_pantalla_jugador_uno_3j_4j();
                renderizar_pantalla_jugador_tres_3j_4j();
                renderizar_pantalla_jugador_cuatro_3j_4j();
                renderizar_pantalla_jugador_dos_3j_4j();
            } else if (indice_ganador_jugador == 2) {
                renderizar_pantalla_jugador_uno_3j_4j();
                renderizar_pantalla_jugador_dos_3j_4j();
                renderizar_pantalla_jugador_cuatro_3j_4j();
                renderizar_pantalla_jugador_tres_3j_4j();
            } else {
                renderizar_pantalla_jugador_uno_3j_4j();
                renderizar_pantalla_jugador_dos_3j_4j();
                renderizar_pantalla_jugador_tres_3j_4j();
                renderizar_pantalla_jugador_cuatro_3j_4j();
            }
            break;
    }

    if (!modo_depuracion_activacion) {
        metros_recurso_activacion = 0;
    } else {
        if (metros_recurso_activacion) {
            pantalla_recurso();
            if ((!(mando_uno->button & L_TRIG)) && (mando_uno->button & R_TRIG) &&
                (mando_uno->boton_pulsado & B_BUTTON)) {
                metros_recurso_activacion = 0;
            }
        } else {
            if ((!(mando_uno->button & L_TRIG)) && (mando_uno->button & R_TRIG) &&
                (mando_uno->boton_pulsado & B_BUTTON)) {
                metros_recurso_activacion = 1;
            }
        }
    }
    funcion_802A4300();
    funcion_800591B4();
    funcion_80093E20();
#if DVDL
    mostrar_dvdl();
#endif
    gDPFullSync(display_list_cabeza++);
    gSPEndDisplayList(display_list_cabeza++);
}

void manejador_estado_juego(void) {
#if DVDL
    if ((mando_uno->button & L_TRIG) && (mando_uno->button & R_TRIG) && (mando_uno->button & Z_TRIG) &&
        (mando_uno->button & A_BUTTON)) {
        siguiente_estado_juego = SECUENCIA_CREDITOS;
    } else if ((mando_uno->button & L_TRIG) && (mando_uno->button & R_TRIG) &&
               (mando_uno->button & Z_TRIG) && (mando_uno->button & B_BUTTON)) {
        siguiente_estado_juego = FINAL;
    }
#endif

    switch (estado_juego) {
        case 7:
            inicializar_framebuffer_limpieza_juego();
            break;
        case MENU_INICIO_DESDE_ABANDONAR:
        case MENU_PRINCIPAL_DESDE_ABANDONAR:
        case MENU_SELECCION_JUGADOR_DESDE_ABANDONAR:
        case MENU_SELECCION_CIRCUITO_DESDE_ABANDONAR:
            osViBlack(0);
            actualizar_menus();
            inicializar_rcp();
            funcion_80094A64(gfx_pool);
#if DVDL
            mostrar_dvdl();
#endif
            break;
        case CARRERA:
            bucle_logica_carrera();
            break;
        case FINAL:
            bucle_ceremonia_podio();
            break;
        case SECUENCIA_CREDITOS:
            bucle_creditos();
            break;
    }
}

void interrumpir_sptask_gfx(void) {
    if (tarea_sp_activo->tarea.t.type == M_GFXTASK) {
        tarea_sp_activo->state = SPTASK_ESTADO_INTERRUMPIDO;
        osSpTaskYield();
    }
}
