// Ejecutar tareas

static int salida_remuestreo_sin_uso(const u32 *cmd, u32 izquierda, u32 salida, u32 largo)
{
    EstadoAudioSimulado sim;
    u32 lo = salida & 0xFFF, hi = lo + largo;
    u32 j;

    sim.in = Rsp.in;
    sim.out = Rsp.out;
    sim.nbytes = Rsp.nbytes;
    sim.vol[0] = Rsp.vol[0];
    sim.vol[1] = Rsp.vol[1];
    sim.tasa[0] = Rsp.tasa[0];
    sim.tasa[1] = Rsp.tasa[1];
    sim.humedo_vol = Rsp.humedo_vol;
    sim.humedo_tasa = Rsp.humedo_tasa;
    for (j = 0; j < izquierda && j < MAX_COMANDOS_ADELANTE; j++, cmd += 2) {
        u32 w0 = cmd[0], w1 = cmd[1];

        switch (w0 >> 24) {
            case A_SPNOOP:
            case A_SEGMENT:
            case A_LOADADPCM:
            case A_SETLOOP:
                break;
            case A_SETBUFF:
                sim.in = w0 & 0xFFFF;
                sim.out = w1 >> 16;
                sim.nbytes = w1 & 0xFFFF;
                break;
            case A_ENVSETUP1:
                sim.humedo_vol = (u16) (((w0 >> 16) & 0xFF) << 8);
                sim.humedo_tasa = 0;
                sim.tasa[0] = (s16) (w1 >> 16);
                sim.tasa[1] = (s16) (w1 & 0xFFFF);
                break;
            case A_ENVSETUP2:
                sim.vol[0] = w1 >> 16;
                sim.vol[1] = w1 & 0xFFFF;
                break;
            case A_ENVMIXER: {
                u32 n = ARRIBA_RONDA_8((w0 >> 8) & 0xFF);
                u32 bytes = (n > 0 ? n : 8) * 2;
                int silenciado = sim.vol[0] == 0 && sim.vol[1] == 0 && sim.tasa[0] == 0 && sim.tasa[1] == 0 &&
                            sim.humedo_tasa == 0;

                if ((!silenciado && se_superponen(((w0 >> 16) & 0xFF) << 4, bytes, lo, hi)) ||
                    se_superponen(((w1 >> 24) & 0xFF) << 4, bytes, lo, hi) ||
                    se_superponen(((w1 >> 16) & 0xFF) << 4, bytes, lo, hi) ||
                    se_superponen(((w1 >> 8) & 0xFF) << 4, bytes, lo, hi) || se_superponen((w1 & 0xFF) << 4, bytes, lo, hi)) {
                    return 0;
                }
                break;
            }
            case A_MIXER: {
                u32 bytes = ARRIBA_RONDA_32(ABAJO_RONDA_16(((w0 >> 16) & 0xFF) << 4));

                if (se_superponen((w1 >> 16) & 0xFFF, bytes, lo, hi) || se_superponen(w1 & 0xFFF, bytes, lo, hi)) {
                    return 0;
                }
                break;
            }
            case A_INTERLEAVE: {
                u32 bytes = ARRIBA_RONDA_16(sim.nbytes);

                if (se_superponen((w1 >> 16) & 0xFFF, bytes, lo, hi) || se_superponen(w1 & 0xFFF, bytes, lo, hi)) {
                    return 0;
                }
                tapar_zona(sim.out & 0xFFF, bytes * 2, &lo, &hi);
                break;
            }
            case A_LOADBUFF:
                tapar_zona(w0 & 0xFFF, ABAJO_RONDA_16(((w0 >> 16) & 0xFF) << 4), &lo, &hi);
                break;
            case A_SAVEBUFF:
                if (se_superponen(w0 & 0xFFF, ABAJO_RONDA_16(((w0 >> 16) & 0xFF) << 4), lo, hi)) {
                    return 0;
                }
                break;
            case A_CLEARBUFF:
                tapar_zona(w0 & 0xFFF, ARRIBA_RONDA_16(w1 & 0xFFFF), &lo, &hi);
                break;
            case A_DMEMMOVE:
                if (se_superponen(w0 & 0xFFF, ARRIBA_RONDA_16(w1 & 0xFFFF), lo, hi)) {
                    return 0;
                }
                tapar_zona((w1 >> 16) & 0xFFF, ARRIBA_RONDA_16(w1 & 0xFFFF), &lo, &hi);
                break;
            case A_DMEMMOVE2:
                if (se_superponen(w0 & 0xFFF, w1 & 0xFFFF, lo, hi)) {
                    return 0;
                }
                tapar_zona((w1 >> 16) & 0xFFF, ((w0 >> 16) & 0xFF) * (w1 & 0xFFFF), &lo, &hi);
                break;
            case A_DOWNSAMPLE_HALF: {
                u32 ns = (w0 & 0xFFFF) ? ARRIBA_RONDA_8(w0 & 0xFFFF) : 8;

                if (se_superponen((w1 >> 16) & 0xFFF, ns * 4, lo, hi)) {
                    return 0;
                }
                tapar_zona(w1 & 0xFFF, ns * 2, &lo, &hi);
                break;
            }
            case A_ADPCM: {
                u32 bytes = ARRIBA_RONDA_32(sim.nbytes);

                /* Lee datos comprimidos (menos que bytes) desde in. */
                if (se_superponen(sim.in & 0xFFF, bytes, lo, hi)) {
                    return 0;
                }
                tapar_zona(sim.out & 0xFFF, 32 + bytes, &lo, &hi);
                break;
            }
            case A_RESAMPLE: {
                u32 vueltas = ARRIBA_RONDA_16(sim.nbytes) > 16 ? ARRIBA_RONDA_16(sim.nbytes) / 16 : 1;
                u32 direccion_entrada = sim.in & 0xFFF;

                if (se_superponen(direccion_entrada > 64 ? direccion_entrada - 64 : 0, 128 + vueltas * 64, lo, hi)) {
                    return 0;
                }
                tapar_zona(sim.out & 0xFFF, vueltas * 16, &lo, &hi);
                break;
            }
            default:
                return 0;
        }
        if (lo >= hi) {
            return 1;
        }
    }
    return 0;
}

#ifdef SMK64_DEV
static u32 cantidad_tarea, cmd_hist[32], salida_pico;
static char traza[65536];
static int largo_traza, hecho_traza, este_volcado, volcado;
#define TRAZA(...) (largo_traza += snprintf(traza + largo_traza, sizeof(traza) - largo_traza, __VA_ARGS__), \
                    largo_traza += snprintf(traza + largo_traza, sizeof(traza) - largo_traza, "\n"))

static void trazar_vaciar(void)
{
    FILE *f;

    if (hecho_traza) {
        return;
    }
    hecho_traza = 1;
    bloquear_host();
    f = fopen("host:audio_tasks.txt", "wb");
    if (f != NULL) {
        fwrite(traza, 1, largo_traza, f);
        fclose(f);
    }
    desbloquear_host();
}
#endif

static void ejecutar_lista_audio(u64 *lista_cmd, u32 bytes_tamanio);
static void ejecutar_ordenes(const u32 *cmd, u32 n);

#ifdef SMK64_AUDIO_CHECK
#define ZONAS_COMPROBACION 256
#define MEMORIA_COMPROBACION (96 * 1024)

static struct {
    u8 *addr;
    u32 size;
    u32 offset;
} zonas_comprobacion[ZONAS_COMPROBACION];
static u8 zonas_antes[MEMORIA_COMPROBACION], zonas_referencia[MEMORIA_COMPROBACION];
static u8 s_dmem_antes[4096], dmem_referencia[4096];
static u32 diferencias_audio, tareas_comprobadas;

static void comprobar_tarea_audio(u64 *lista_cmd, u32 bytes_tamanio)
{
    const u32 *cmd = (const u32 *) lista_cmd;
    u32 n = bytes_tamanio / 8, i, nr = 0, used = 0;
    typeof(Rsp) rsp_antes, rsp_referencia;

    for (i = 0; i < n; i++) {
        u32 w0 = cmd[i * 2], w1 = cmd[i * 2 + 1], size = 0;

        switch (w0 >> 24) {
            case A_ADPCM:
            case A_RESAMPLE:
                size = 32;
                break;
            case A_SAVEBUFF:
                size = ABAJO_RONDA_16(((w0 >> 16) & 0xFF) << 4);
                break;
        }
        if (size != 0) {
            if (nr == ZONAS_COMPROBACION || used + size > MEMORIA_COMPROBACION) {
                ejecutar_lista_audio(lista_cmd, bytes_tamanio); /* no entra: sin comprobar */
                return;
            }
            zonas_comprobacion[nr].addr = (u8 *) ptr(w1);
            zonas_comprobacion[nr].size = size;
            zonas_comprobacion[nr].offset = used;
            memcpy(&zonas_antes[used], zonas_comprobacion[nr].addr, size);
            used += size;
            nr++;
        }
    }
    memcpy(s_dmem_antes, s_dmem.u8, sizeof(s_dmem_antes));
    rsp_antes = Rsp;

    /* Referencia: el C tal cual, sin atajos ni MMI. */
    atajos_audio = 0;
#ifdef ASPMAIN_MMI
    mmi_usar = 0;
#endif
    ejecutar_ordenes(cmd, n);
    for (i = 0; i < nr; i++) {
        memcpy(&zonas_referencia[zonas_comprobacion[i].offset], zonas_comprobacion[i].addr, zonas_comprobacion[i].size);
    }
    memcpy(dmem_referencia, s_dmem.u8, sizeof(dmem_referencia));
    rsp_referencia = Rsp;

    /* Deshacer en orden inverso */
    for (i = nr; i-- > 0;) {
        memcpy(zonas_comprobacion[i].addr, &zonas_antes[zonas_comprobacion[i].offset], zonas_comprobacion[i].size);
    }
    memcpy(s_dmem.u8, s_dmem_antes, sizeof(s_dmem_antes));
    Rsp = rsp_antes;

    atajos_audio = 1;
#ifdef ASPMAIN_MMI
    mmi_usar = 1;
#endif
    ejecutar_lista_audio(lista_cmd, bytes_tamanio);
    tareas_comprobadas++;
    if (memcmp(s_dmem.u8, dmem_referencia, sizeof(dmem_referencia)) != 0 && diferencias_audio++ < 20) {
        registrar("AUDIO_CHECK: la DMEM difiere (tarea %u)", (unsigned) tareas_comprobadas);
    }
    if (memcmp(&Rsp, &rsp_referencia, sizeof(Rsp)) != 0 && diferencias_audio++ < 20) {
        registrar("AUDIO_CHECK: el estado del RSP difiere (tarea %u)", (unsigned) tareas_comprobadas);
    }
    for (i = 0; i < nr; i++) {
        if (memcmp(zonas_comprobacion[i].addr, &zonas_referencia[zonas_comprobacion[i].offset], zonas_comprobacion[i].size) != 0 && diferencias_audio++ < 20) {
            registrar("AUDIO_CHECK: la RAM en %p (%u bytes) difiere (tarea %u)", zonas_comprobacion[i].addr, (unsigned) zonas_comprobacion[i].size,
                    (unsigned) tareas_comprobadas);
        }
    }
    if ((tareas_comprobadas % 600) == 0) {
        registrar("AUDIO_CHECK: %u tareas comprobadas, %u diferencias", (unsigned) tareas_comprobadas, (unsigned) diferencias_audio);
    }
}
#endif

static void ejecutar_lista_audio(u64 *lista_cmd, u32 bytes_tamanio)
{
    const u32 *cmd = (const u32 *) lista_cmd;
    u32 n = bytes_tamanio / 8;
    u32 i;

#ifdef SMK64_DEV
    cantidad_tarea++;
    este_volcado = 0;
    if (cantidad_tarea > 600 && volcado < 3) {
        for (i = 0; i < n; i++) {
            if ((cmd[i * 2] >> 24) == A_ENVSETUP2 && (cmd[i * 2 + 1] >> 16) > 0x2000) {
                este_volcado = 1;
                volcado++;
                TRAZA("== tarea %u", (unsigned) cantidad_tarea);
                break;
            }
        }
    }
    for (i = 0; i < n; i++) {
        cmd_hist[(cmd[i * 2] >> 24) & 31]++;
    }
    if (volcado == 3 && !este_volcado) {
        trazar_vaciar();
    }
    if ((cantidad_tarea % 300) == 1) {
        registrar("audio: tarea %u, %u cmds; hist ADPCM %u RES %u ENVMIX %u MIX %u LOADBUF %u SAVEBUF %u INTERL %u; pico %u",
                (unsigned) cantidad_tarea, (unsigned) n, (unsigned) cmd_hist[A_ADPCM], (unsigned) cmd_hist[A_RESAMPLE],
                (unsigned) cmd_hist[A_ENVMIXER], (unsigned) cmd_hist[A_MIXER], (unsigned) cmd_hist[A_LOADBUFF],
                (unsigned) cmd_hist[A_SAVEBUFF], (unsigned) cmd_hist[A_INTERLEAVE], (unsigned) salida_pico);
        registrar("audio: envmixer %u (%u muestras): mudos %u, sin reverb %u; remuestreos %u, sin salida %u",
                (unsigned) envolventes_totales, (unsigned) muestras_envolventes, (unsigned) envolventes_mudas, (unsigned) envolventes_sin_reverb,
                (unsigned) remuestreos_totales, (unsigned) remuestreos_sin_salida);
#ifdef ASPMAIN_MMI
        registrar("audio: por C en vez de MMI: ADPCM %u, remuestreo %u sin alinear %u solapado, envolvente %u, mezcla %u",
                (unsigned) mmi_c[0], (unsigned) mmi_c[1], (unsigned) mmi_c[2], (unsigned) mmi_c[3],
                (unsigned) mmi_c[4]);
        memset(mmi_c, 0, sizeof(mmi_c));
#endif
        envolventes_totales = muestras_envolventes = envolventes_mudas = envolventes_sin_reverb = 0;
        remuestreos_totales = remuestreos_sin_salida = 0;
        memset(cmd_hist, 0, sizeof(cmd_hist));
        salida_pico = 0;
        {
            void registrar_reproductores_secuencias(void);

            registrar_reproductores_secuencias();
        }
    }
#endif
    ejecutar_ordenes(cmd, n);
}

static void ejecutar_ordenes(const u32 *cmd, u32 n)
{
    u32 i;

    for (i = 0; i < n; i++, cmd += 2) {
        u32 w0 = cmd[0], w1 = cmd[1];

#ifdef SMK64_DEV
        if (este_volcado) {
            TRAZA("%08x %08x", (unsigned) w0, (unsigned) w1);
        }
#endif

        switch (w0 >> 24) {
            case A_SPNOOP:
            case A_SEGMENT:
                break;
            case A_ADPCM:
                a_adpcm((w0 >> 16) & 0xFF, (s16 *) ptr(w1));
                break;
            case A_CLEARBUFF:
                memset(DMEM_U8(w0 & 0xFFFF), 0, ARRIBA_RONDA_16(w1 & 0xFFFF));
                break;
            case A_RESAMPLE: {
                u32 vueltas = ARRIBA_RONDA_16(Rsp.nbytes) > 16 ? ARRIBA_RONDA_16(Rsp.nbytes) / 16 : 1;
                u32 direccion_entrada = Rsp.in & 0xFFF;
                int lee_propia_salida = se_superponen(direccion_entrada > 64 ? direccion_entrada - 64 : 0, 128 + vueltas * 64, Rsp.out & 0xFFF,
                                        (Rsp.out & 0xFFF) + vueltas * 16);
                int querer = !atajos_audio || lee_propia_salida || !salida_remuestreo_sin_uso(cmd + 2, n - i - 1, Rsp.out, vueltas * 16);

#ifdef SMK64_DEV
                remuestreos_totales++;
                remuestreos_sin_salida += !querer;
#endif
                remuestreo_a((w0 >> 16) & 0xFF, w0 & 0xFFFF, (s16 *) ptr(w1), querer);
                break;
            }
            case A_SETBUFF:
                Rsp.in = w0 & 0xFFFF;
                Rsp.out = w1 >> 16;
                Rsp.nbytes = w1 & 0xFFFF;
                break;
            case A_DMEMMOVE:
                copiar_fwd_dmem(w1 >> 16, w0 & 0xFFFF, ARRIBA_RONDA_16(w1 & 0xFFFF), TROZO_MOVIMIENTO);
                break;
            case A_LOADADPCM: {
                /* DMA de 8 en 8 bytes a 0x3D0 real */
                u32 c = ARRIBA_RONDA_8(w0 & 0xFFFF) & 0xFFF, primer = c < 0x1000 - LIBRO_DMEM ? c : 0x1000 - LIBRO_DMEM;

                memcpy(DMEM_U8(LIBRO_DMEM), ptr(w1), primer);
                memcpy(DMEM_U8(0), (const u8 *) ptr(w1) + primer, c - primer);
                break;
            }
            case A_MIXER:
                mezcla_a((w0 >> 16) & 0xFF, (s16) (w0 & 0xFFFF), w1 >> 16, w1 & 0xFFFF);
                break;
            case A_INTERLEAVE:
                entrelazado_a(w1 >> 16, w1 & 0xFFFF);
#ifdef SMK64_DEV
                {
                    int k;
                    s16 *d = DMEM_S16(Rsp.out);

                    for (k = 0; k < Rsp.nbytes; k++) {
                        u32 a = d[k] < 0 ? -d[k] : d[k];

                        if (a > salida_pico) {
                            salida_pico = a;
                        }
                    }
                }
#endif
                break;
            case A_SETLOOP:
                Rsp.estado_bucle = (s16 *) ptr(w1);
                break;
            case A_DMEMMOVE2:
                copiar_fwd_dmem(w1 >> 16, w0 & 0xFFFF, ((w0 >> 16) & 0xFF) * (w1 & 0xFFFF), TROZO_MOVE2);
                break;
            case A_DOWNSAMPLE_HALF: {
                /* De 8 en 8 y al menos 8, como el original */
                u32 k, ns = (w0 & 0xFFFF) ? ARRIBA_RONDA_8(w0 & 0xFFFF) : 8;
                s16 *in = DMEM_S16(w1 >> 16);
                s16 *salida = DMEM_S16(w1 & 0xFFFF);

                for (; ns > 0; ns -= 8, in += 16, salida += 8) {
                    s16 t[16];

                    memcpy(t, in, sizeof(t));
                    for (k = 0; k < 8; k++) {
                        salida[k] = t[k * 2];
                    }
                }
                break;
            }
            case A_ENVSETUP1:
                Rsp.humedo_vol = (u16) (((w0 >> 16) & 0xFF) << 8);
                /* El microcodigo de MK64 no usa rampa de reverberacion */
                Rsp.humedo_tasa = 0;
                Rsp.tasa[0] = (s16) (w1 >> 16);
                Rsp.tasa[1] = (s16) (w1 & 0xFFFF);
                break;
            case A_ENVSETUP2:
                Rsp.vol[0] = w1 >> 16;
                Rsp.vol[1] = w1 & 0xFFFF;
                break;
            case A_ENVMIXER:
                a_envmixer(w0, w1);
                break;
            case A_LOADBUFF:
                memcpy(DMEM_U8(w0 & 0xFFFF), ptr(w1), ABAJO_RONDA_16(((w0 >> 16) & 0xFF) << 4));
                break;
            case A_SAVEBUFF:
                memcpy(ptr(w1), DMEM_U8(w0 & 0xFFFF), ABAJO_RONDA_16(((w0 >> 16) & 0xFF) << 4));
                break;
            default:
                break;
        }
    }
}

#ifdef SMK64_DEV
/* Volcado de tareas completas para tools/audio/rsp_check */
static FILE *archivo_volcado;
static int izquierda_volcado;
static char nombre_volcado[64];
static volatile int pedido_volcado;

void volcar_pedido_aspmain(const char *nombre, int tareas)
{
    snprintf(nombre_volcado, sizeof(nombre_volcado), "host:%s", nombre);
    izquierda_volcado = tareas;
    pedido_volcado = 1;
}

static void volcar_tarea(const u32 *cmd, u32 n)
{
    static u32 direccion_reg[512], tamanio_reg[512];
    u32 i, nr = 0, hdr[3];

    if (pedido_volcado) {
        pedido_volcado = 0;
        bloquear_host();
        if (archivo_volcado != NULL) {
            fclose(archivo_volcado);
        }
        archivo_volcado = fopen(nombre_volcado, "wb");
        desbloquear_host();
    }
    if (archivo_volcado == NULL || izquierda_volcado <= 0) {
        return;
    }
    for (i = 0; i < n && nr < 512; i++) {
        u32 w0 = cmd[i * 2], w1 = cmd[i * 2 + 1], size = 0;

        switch (w0 >> 24) {
            case A_ADPCM:
            case A_RESAMPLE:
            case A_SETLOOP:
                size = 32;
                break;
            case A_LOADADPCM:
                size = w0 & 0xFFFF;
                break;
            case A_LOADBUFF:
            case A_SAVEBUFF:
                size = ((w0 >> 16) & 0xFF) << 4;
                break;
        }
        if (size != 0) {
            u32 a = (w1 & ~15u) - 64, e = ((w1 + size + 15) & ~15u) + 64;

            if (a >= 0x100000 && e <= 0x2000000) {
                direccion_reg[nr] = a;
                tamanio_reg[nr] = e - a;
                nr++;
            }
        }
    }
    bloquear_host();
    hdr[0] = 0x444D4341;
    hdr[1] = n;
    hdr[2] = nr;
    fwrite(hdr, 4, 3, archivo_volcado);
    fwrite(cmd, 8, n, archivo_volcado);
    for (i = 0; i < nr; i++) {
        fwrite(&direccion_reg[i], 4, 1, archivo_volcado);
        fwrite(&tamanio_reg[i], 4, 1, archivo_volcado);
        fwrite((void *) (uintptr_t) direccion_reg[i], 1, tamanio_reg[i], archivo_volcado);
    }
    if (--izquierda_volcado == 0) {
        fclose(archivo_volcado);
        archivo_volcado = NULL;
    }
    desbloquear_host();
    if (archivo_volcado == NULL) {
        registrar("audio: tareas volcadas en %s", nombre_volcado);
    }
}
#endif

#if defined(ASPMAIN_MMI) && defined(SMK64_DEV)
/* Autoprueba de la version MMI */
static u32 s_rnd = 0x12345678;

static u32 rnd(void)
{
    s_rnd ^= s_rnd << 13;
    s_rnd ^= s_rnd >> 17;
    s_rnd ^= s_rnd << 5;
    return s_rnd;
}

/* Valores de 16 bits con extremos frecuentes. */
static u32 rnd16(void)
{
    static const u16 borde_k[] = { 0, 1, 0x7FFF, 0x8000, 0x8001, 0xFFFF, 0x4000, 0xC000 };

    return (rnd() & 3) == 0 ? borde_k[rnd() & 7] : (rnd() & 0xFFFF);
}

static u8 ram_prueba[3][32] __attribute__((aligned(16)));

int autoprueba_aspmain(int vueltas)
{
    static u8 dmem_antes[4096], dmem_ref[4096];
    static u8 ram_antes[sizeof(ram_prueba)], ram_ref[sizeof(ram_prueba)];
    typeof(Rsp) rsp_antes, rsp_referencia;
    u32 cmd[8 * 2];
    int it, errores = 0, cantidades[4] = { 0 };
    int saltear_guardado = atajos_audio;

    atajos_audio = 0;
    for (it = 0; it < vueltas; it++) {
        int tipo = it & 3, nc = 0;
        u32 i;

        for (i = 0; i < 4096; i += 4) {
            u32 r = rnd();

            /* A veces valores extremos, para saturar. */
            if ((r & 0x70) == 0) {
                r |= 0x7FFF7FFF;
            }
            *(u32 *) &s_dmem.u8[i] = r;
        }
        for (i = 0; i < sizeof(ram_prueba); i++) {
            ((u8 *) ram_prueba)[i] = (u8) rnd();
        }
        Rsp.vol[0] = rnd16();
        Rsp.vol[1] = rnd16();
        Rsp.tasa[0] = (rnd() & 1) ? (s16) rnd16() : (s16) ((s32) (rnd() & 0x3FF) - 0x200);
        Rsp.tasa[1] = (rnd() & 1) ? (s16) rnd16() : (s16) ((s32) (rnd() & 0x3FF) - 0x200);
        Rsp.humedo_vol = (u16) ((rnd() & 0xFF) << 8);
        Rsp.humedo_tasa = 0;
        Rsp.estado_bucle = (s16 *) ram_prueba[2];

        switch (tipo) {
            case 0: {
                u32 cantidad = rnd() & 0xFF, b[5], k;

                for (k = 0; k < 5; k++) {
                    b[k] = (k > 0 && (rnd() & 3) == 0) ? b[rnd() % k] : rnd() % 225;
                }
                cmd[nc++] = (A_ENVMIXER << 24) | (b[0] << 16) | (cantidad << 8) | (rnd() & 3);
                cmd[nc++] = (b[1] << 24) | (b[2] << 16) | (b[3] << 8) | b[4];
                break;
            }
            case 1: {
                u32 c16 = rnd() % 65, in = (rnd() % 0xB0) << 4, salida = (rnd() % 0xB0) << 4;

                if ((rnd() & 7) == 0) {
                    in += 8; /* sin alinear: va por el C */
                }
                if ((rnd() & 3) == 0 && in >= 0x40) {
                    salida = in + (((rnd() & 7) - 3) << 4); /* solapadas */
                }
                cmd[nc++] = (A_MIXER << 24) | (c16 << 16) | rnd16();
                cmd[nc++] = (in << 16) | (salida & 0xFFF);
                break;
            }
            case 2: {
                u32 in = 0x100 + ((rnd() % 0x380) & ~1u), salida = 0x800 + ((rnd() % 0x300) << 1);
                u32 nbytes = rnd() % 0x101, banderas = (rnd() & 1) ? 1 : (rnd() & 2);
                s16 *st = (s16 *) ram_prueba[0];

                if ((rnd() & 3) != 0) {
                    salida &= ~15u;
                }
                if ((rnd() & 7) == 0) {
                    salida = in + ((rnd() & 0x3F) << 4) - 0x100; /* solapadas */
                    salida &= ~15u;
                }
                if ((rnd() & 15) == 0) {
                    in |= 1;
                }
                st[5] = (s16) ((rnd() & 7) * 2);
                cmd[nc++] = (A_SETBUFF << 24) | in;
                cmd[nc++] = (salida << 16) | nbytes;
                cmd[nc++] = (A_RESAMPLE << 24) | (banderas << 16) | rnd16();
                cmd[nc++] = (u32) (uintptr_t) ram_prueba[0];
                break;
            }
            default: {
                u32 in = 0x180 + rnd() % 0xC00, salida = 0x180 + ((rnd() % 0xB0) << 4);
                u32 nbytes = rnd() % 0x201, banderas = rnd() & 3;
                static s16 libro[8 * 16] __attribute__((aligned(16)));

                for (i = 0; i < 8 * 16; i++) {
                    libro[i] = (rnd() & 1) ? (s16) ((s32) (rnd() & 0x1FFF) - 0x1000) : (s16) rnd16();
                }
                if ((rnd() & 7) == 0) {
                    salida = (in & ~15u) + (((rnd() & 7) - 2) << 4); /* solapadas */
                }
                if ((rnd() & 7) == 0) {
                    salida += 8;
                }
                if (salida + 32 + ARRIBA_RONDA_32(nbytes) > 0xF80) {
                    salida = 0x200;
                }
                cmd[nc++] = (A_LOADADPCM << 24) | ((rnd() & 7) + 1) * 32;
                cmd[nc++] = (u32) (uintptr_t) libro;
                cmd[nc++] = (A_SETBUFF << 24) | in;
                cmd[nc++] = (salida << 16) | nbytes;
                cmd[nc++] = (A_ADPCM << 24) | (banderas << 16);
                cmd[nc++] = (u32) (uintptr_t) ram_prueba[1];
                break;
            }
        }
        cantidades[tipo]++;

        memcpy(dmem_antes, s_dmem.u8, sizeof(dmem_antes));
        memcpy(ram_antes, ram_prueba, sizeof(ram_antes));
        rsp_antes = Rsp;
        mmi_usar = 0;
        ejecutar_ordenes(cmd, nc / 2);
        memcpy(dmem_ref, s_dmem.u8, sizeof(dmem_ref));
        memcpy(ram_ref, ram_prueba, sizeof(ram_ref));
        rsp_referencia = Rsp;

        memcpy(s_dmem.u8, dmem_antes, sizeof(dmem_antes));
        memcpy(ram_prueba, ram_antes, sizeof(ram_antes));
        Rsp = rsp_antes;
        mmi_usar = 1;
        ejecutar_ordenes(cmd, nc / 2);
        if (memcmp(s_dmem.u8, dmem_ref, sizeof(dmem_ref)) != 0 || memcmp(ram_prueba, ram_ref, sizeof(ram_ref)) != 0 ||
            memcmp(&Rsp, &rsp_referencia, sizeof(Rsp)) != 0) {
            if (errores++ < 12) {
                u32 primer = 0;

                while (primer < 4096 && s_dmem.u8[primer] == dmem_ref[primer]) {
                    primer++;
                }
                registrar("aspmain MMI: difiere la prueba %d (tipo %d: %08x %08x %08x %08x), primer byte DMEM 0x%x",
                        it, tipo, (unsigned) cmd[0], (unsigned) cmd[1], (unsigned) cmd[nc - 2],
                        (unsigned) cmd[nc - 1], (unsigned) primer);
            }
        }
    }
    atajos_audio = saltear_guardado;
    memset(s_dmem.u8, 0, sizeof(s_dmem.u8));
    memset(&Rsp, 0, sizeof(Rsp));
    registrar("aspmain MMI: autoprueba %d comandos (envmixer %d, mixer %d, resample %d, adpcm %d): %d diferencias", vueltas,
            cantidades[0], cantidades[1], cantidades[2], cantidades[3], errores);
    return errores;
}
#endif

void ejecutar_tarea_aspmain(u64 *lista_cmd, u32 bytes_tamanio)
{
#ifdef SMK64_DEV
    volcar_tarea((const u32 *) lista_cmd, bytes_tamanio / 8);
#endif
#ifdef SMK64_AUDIO_CHECK
    comprobar_tarea_audio(lista_cmd, bytes_tamanio);
#else
    ejecutar_lista_audio(lista_cmd, bytes_tamanio);
#endif
}

void fijar_shortcuts_aspmain(int activar)
{
    atajos_audio = activar;
}
