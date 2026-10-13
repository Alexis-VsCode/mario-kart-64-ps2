# Manual técnico

Cómo está hecho el port, cómo compilo, pruebo y publico, y cómo traigo las actualizaciones del repositorio original. Para jugar, ver el [manual de usuario](usuario.md). El proceso de trabajo (Definition of Done, ramas, commits y revisión) está en [CONTRIBUTING.md](../../CONTRIBUTING.md).

## Arquitectura

```
+----------------------------------------------------------------+
|  Juego descompilado                                            |
|  carrera, menús, ceremonia, motor de sonido, dibujo, bucle     |
|  principal (codigo/)                                           |
+-------------------------------+--------------------------------+
                                |  API de libultra (incluir/libultra/)
+-------------------------------v--------------------------------+
|  Capa de compatibilidad N64 -> PS2                             |
|                                                                |
|  Gráficos  listas F3DEX -> combinador de color -> TMEM         |
|            -> paquetes para el GS (gsKit, DMA del GIF)         |
|  Audio     microcódigo de audio en C -> audsrv a 48 kHz        |
|  Sistema   hilos y colas de mensajes, retrazo y temporizadores,|
|            DMA de la ROM, EEPROM/Controller Pak -> Memory Card,|
|            mandos                                              |
+-------------------------------+--------------------------------+
                                |
+-------------------------------v--------------------------------+
|  Hardware PS2: EE, GS e IOP (audio, mandos, Memory Card, DVD)  |
+----------------------------------------------------------------+
```

| Pieza de la N64 | Sustituto en PS2 | Archivo |
|---|---|---|
| RSP gráfico (F3DEX) y RDP | Intérprete de listas de dibujo | `codigo/graficos/interprete_f3dex.c` y `interprete_f3dex/` |
| Combinador de color | Evaluación del combinador; el alfa con tramado es la función pura `combinador_alfa_tramado()` | `codigo/graficos/combinador_color.c`, `incluir/graficos/combinador_color.h` |
| TMEM | Carga y caché de texturas | `codigo/graficos/memoria_texturas.c` y `memoria_texturas/` |
| Salida de vídeo | Paquetes y framebuffers del GS; los registros del PCRTC (PMODE, DISPFB2, DISPLAY) salen de una función pura según las opciones | `codigo/graficos/sintetizador_gs.c`, `incluir/graficos/registros_video.h`, `incluir/graficos/vista_panoramica.h` |
| RSP de audio | Microcódigo en C | `codigo/audio/microcodigo_audio.c` y `microcodigo_audio/` |
| Salida de audio | `audsrv` (IRX embebidos en `codigo/datos/datos_embebidos.s`) | `codigo/audio/salida_audio.c` |
| Tareas del RSP | Reparto entre gráficos y audio | `codigo/sistema/tareas_rsp.c` |
| Hilos y mensajes | Hilos del kernel del EE | `codigo/sistema/hilos.c` |
| VI, retrazo y temporizadores | Interrupción de VBlank | `codigo/sistema/retrazo_vertical.c` |
| DMA del cartucho (PI) | Copia desde la ROM en RAM | `codigo/sistema/hardware.c`, `codigo/sistema/carga_rom.c` |
| EEPROM y Controller Pak | Imagen guardada en la Memory Card; la copia que se pisa en una tarjeta nueva la elige una función pura | `codigo/sistema/guardado_ps2.c`, `codigo/sistema/memory_card.c`, `incluir/sistema/eleccion_guardado.h` |
| Mandos | `libpad`; la conversión del eje del stick y el reposo de la cruceta son funciones puras | `codigo/entrada/mandos.c`, `incluir/entrada/eje_palanca.h` |
| Sin equivalente: opciones del port | Ajustes de imagen y trucos en `SMK64CFG.DAT`, con su formato y saneado en funciones puras | `incluir/sistema/opciones_port.h`, `codigo/sistema/memory_card.c`, `incluir/menus/menu_configuracion.h` |
| Sin equivalente: región de la consola | Lectura de `rom0:ROMVER` al arrancar, solo para el registro: el vídeo sale siempre en NTSC a 60 Hz | `codigo/sistema/arranque_ps2.c`, `incluir/sistema/region_ps2.h` |

Las funciones puras de esas cabeceras son `static inline` y no dependen del SDK de PS2: el código del port las usa y `make test` las prueba en el PC (ver [Pruebas](#pruebas)). La lógica que las rodea, con libmc, libpad o la BIOS, solo compila con el SDK.

## La ROM

Enlazo el código en un ELF del EE (`compilacion/ps2.ld`). Construyo la «ROM» por separado:

```
recursos/ y codigo/datos/
  |  cada bloque se compila y se enlaza en su dirección segmentada
  |  (compilacion/segmento_datos.ld)
  v
bloques .bin --(build/herramientas/mio0)--> bloques .mio0
  |  herramientas/generar_rom_ld.py
  v
build/ps2/rom.elf -> build/ps2/rom.bin
  |  herramientas/partir_rom.py
  +--> rom_cabecera.bin   (va dentro del ELF)
  +--> SMK64ROM.BIN       (se lee del disco en segundo plano)
```

- Los bloques que el juego espera comprimidos se comprimen con MIO0: datos comunes, ceremonia, logo, y datos y vértices de cada pista. Las listas de dibujo de las pistas se empaquetan con `empaquetador_listas`.
- Con `ROM_STREAM=0` (por defecto con `MONOLITICO=1` o `DEV=1`), la ROM entera va dentro del ELF.
- Un hilo lee `SMK64ROM.BIN` en trozos de 64 KB desde el arranque. Si el juego pide por DMA un trozo que todavía no se ha leído, ese trozo pasa primero y el juego espera solo por él.
- Preparación previa:
  - las texturas de 16 bits se copian con los bytes invertidos (`herramientas/invertir_texturas.py` → `build/ps2/be/`);
  - los bancos de audio pasan a little-endian (`herramientas/invertir_audio.py`);
  - los caminos del tren y del barco se precalculan (`herramientas/generar_caminos_vehiculos.py`);
  - los fuentes de `JP_SRC` y los de `JP_PARTES` (sus partes `.inc.c` y los metadatos de pista), que en el repositorio están en UTF-8, pasan a EUC-JP con `herramientas/convertir_eucjp.py` (`build/ps2/jp/`);
  - las texturas en español salen de los PNG de `recursos/es/` (`make es` → `build/ps2/es/`): las de menú se guardan en MIO0 y el cargador elige TKMK00 o MIO0 por la firma.

## Vídeo

El modo no cambia desde la 1.0.0: NTSC 480i a 60 Hz, 640×448, iniciado por gsKit. La 1.2.0 añade la presentación en el PCRTC y la vista panorámica ([CC-20](../traduccion/cambios.md) y CC-21). Ninguno de los dos cambia lo que dibuja el GS, salvo el campo de visión en PANORÁMICO.

**Registros del PCRTC.** `calcular_registros_video()` (`incluir/graficos/registros_video.h`) es una función pura: recibe el `DISPLAY` que deja `gsKit_init_screen` (`BaseVideo`) y las opciones, y devuelve tres valores:

| Registro | Por defecto | Con las opciones |
|---|---|---|
| `PMODE` (0x12000000) | `0x8046` (`PMODE_GSKIT`): solo el circuito 2, como gsKit | ANTIPARPADEO: `0x8027` (`PMODE_ANTIPARPADEO`), los dos circuitos con CRTMD=1, MMOD=1 y ALP=0x80, mezcla al 50 % |
| `DISPFB2` (0x12000090) | Sin cambios | ANTIPARPADEO: suma DBY=1 (bit 43), el circuito 2 una línea más abajo |
| `DISPLAY1` y `DISPLAY2` (0x12000080, 0x120000A0) | Los de gsKit | POSICIÓN X: `DX` + 8 VCK por paso (±32). POSICIÓN Y: `DY` + 2 líneas por paso (±16), siempre par. CON BANDAS: MAGH a 3/4 de los VCK por píxel, `DW` a 3/4 y `DX` centrado; el negro de fuera del área hace de bandas |

Con los valores por defecto, los registros son los de la 1.1.0; `prueba_registros_video.c` lo fija. `sintetizador_gs.c` vuelve a calcular y escribe los registros en el retrazo cuando cambia `version_opciones_port`, y no los toca en pánico. Al arrancar registra la línea `vídeo: PMODE <pmode> área visible <display>`, que el job `emulador` exige (`vídeo: PMODE 8046`).

**Vista panorámica.** `incluir/graficos/vista_panoramica.h`:

- `aspecto_panoramico()` multiplica `aspecto_pantalla` por 4/3 en las asignaciones de la carrera, la vista dividida y la ceremonia (Hor+). No se aplica en `guPerspectiveF`, para que los menús no cambien.
- `cono_visibilidad()` ensancha 4/3 el cono horizontal de `es_visible_objeto_en_camara`, con tope en una vuelta. El ensanche lineal cubre siempre el campo real, porque atan(4/3·tan a) ≤ 4/3·a entre 0 y 90 grados.
- Límites declarados: el juego elige los tramos de pista por cuadrante de cámara, y en los bordes algún objeto o tramo puede aparecer tarde; el marcador sale estirado.

**Configuración de la PS2.** `memory_card.c` lee `configGetTvScreenType()` antes de cargar las opciones: solo `TV_SCREEN_169` cuenta como 16:9 (`pantalla_osd_169`), y entonces FORMATO vale CON BANDAS por defecto.

## Opciones del port y trucos

**`opciones_port`** (`incluir/sistema/opciones_port.h`, [CC-18](../traduccion/cambios.md)) guarda los 8 ajustes del menú CONFIGURACIÓN Y TRUCOS. El flujo:

1. El menú escribe `opciones_port` y llama a `opciones_cambiadas()`, que sube `version_opciones_port` tras una barrera de compilador, para que el retrazo no vea la versión nueva antes que los campos.
2. Al salir del menú, si algo cambió, `pedir_guardado_opciones()` encola la escritura en el hilo de guardado.
3. El GS relee las opciones en el retrazo; los trucos las leen directamente.

`SMK64CFG.DAT` mide 32 bytes, en little endian: `MKCF`, versión (u16, hoy 1), tamaño (u16), los 8 campos en el orden del struct, 12 bytes a 0 y el CRC32 de los bytes 0 a 27. `opciones_deserializar()` rechaza firma, versión, tamaño o CRC distintos (una versión mayor también: no se sabe qué significan sus campos) y deja los valores por defecto; `opciones_sanear()` lleva cada campo a su rango. El hilo de guardado no reescribe el archivo si no cambió.

**Menú.** La navegación y el ciclo de valores son funciones puras de `incluir/menus/menu_configuracion.h` (`config_mover_fila`, `config_cambiar`); el dibujo está en `info_pistas_y_tiempos.inc.c` y la entrada en `tablas_menus.inc.c` ([CC-19](../traduccion/cambios.md)).

**Trucos** (apagados por defecto; CC-22 a CC-25):

| Truco | Función pura | Dónde actúa |
|---|---|---|
| DESBLOQUEAR TODO | `incluir/juego/trucos.h` | `tiene_modo_extra_desbloqueado` (`guardado.c`) y los fantasmas del staff (`repeticiones.c`). Nunca escribe el desbloqueo en la partida; se aplica al reconstruir cada pantalla de menú (`91c7254e`) y el cursor se recorta si EXTRA deja de existir |
| OBJETO | `incluir/carrera/truco_objeto.h` | Tras la ruleta de `funcion_8007AFB0`, solo para humanos. El generador aleatorio avanza igual. En batalla solo valen los objetos de batalla; en contrarreloj o con un valor inválido sale el objeto normal |
| 200CC | `incluir/carrera/cilindrada_200cc.h` | Modificador de 150cc, factor 35/32 en la rapidez máxima, el empuje al aparecer y el objetivo de la CPU. Solo Gran Premio y Versus; `seleccion_cc` sigue en 150cc, así que puntúa como 150cc |
| RIVALES SIN VENTAJA | `incluir/carrera/rivales_sin_ventaja.h` | Quita el impulso de la CPU por detrás del jugador (`control_velocidad_cpu.inc.c`) y la velocidad fija de recuperación (`caminos_y_vehiculos.inc.c`); respeta al rival designado (`4c0323bf`). Solo en Gran Premio |

Los récords, fantasmas y trofeos conseguidos con trucos se guardan sin marca; el manual de usuario lo advierte.

## Estructura

| Carpeta | Contenido |
|---|---|
| `codigo/sistema/` | Arranque, bucle principal, hilos, retrazo, carga de la ROM, guardado y descompresión MIO0 y TKMK00. `pantalla_fallo.c` es la pantalla de fallo original de la N64 |
| `codigo/sistema/libultra/` | Parte portable de libultra (conserva sus nombres originales) |
| `codigo/graficos/` | Intérprete F3DEX, memoria de texturas, combinador de color, salida al GS y dibujo de jugadores, objetos y pistas |
| `codigo/audio/` | Motor de sonido del juego, microcódigo de audio en C y salida por `audsrv` |
| `codigo/carrera/` | Lógica de carrera, física, colisiones, cámara, objetos, actores y conducción de los rivales de la CPU |
| `codigo/menus/`, `codigo/ceremonia/` | Menús; podio y créditos |
| `codigo/entrada/` | Mandos |
| `codigo/memoria/` | Pools, buffers y tablas |
| `codigo/depuracion/` | Registro, pantalla de fallo del port y vigilancia de cuelgues, guiones de prueba, panel de rendimiento y muestreo de CPU |
| `codigo/datos/` | Tablas del juego, listas de recursos binarios (`.s`) y datos embebidos |
| `incluir/` | Cabeceras por área. `incluir/libultra/` es la API de la N64, sin traducir |
| `recursos/pistas/` | Las 20 pistas: datos de pista, listas de dibujo, vértices y metadatos (`metadatos/`) |
| `recursos/texturas/` | Karts, personajes, Lakitu, objetos, menús, HUD y texturas de pistas |
| `recursos/sonido/` | Bancos de instrumentos, muestras y música (`musica/`) |
| `recursos/comunes/`, `recursos/ceremonia/`, `recursos/logo_inicio/` | Bloques de datos que la ROM guarda comprimidos |
| `compilacion/` | Scripts del enlazador (`ps2.ld`, `segmento_datos.ld`) |
| `recursos/es/` | PNG y manifiestos de las texturas en español, y letras de cada familia para componerlas |
| `herramientas/` | Entorno, ISO, ROM, texturas (también las del español), audio, icono, caminos del tren y del barco, empaquetador de listas y conversión a EUC-JP |
| `herramientas/pruebas/` | Pruebas de `make test`; `sdk_simulado/` tiene las cabeceras y la libmc simulada del arnés de Memory Card |
| `herramientas/ci/` | Pasos de la CI que necesitan el SDK: tope de la ROM, build incremental e inspección de la fuente de libdebug |
| `herramientas/emulador/` | Job `emulador`: lanzador de Play!, guion, revisión del registro, comparación de capturas y referencias aprobadas |
| `herramientas/guiones/` | Guion de ejemplo para `make DEV=1` (`recorrido_textos.txt`) |
| `docs/manual/` | Este manual, el de usuario y los créditos |
| `docs/traduccion/` | Localización al español: especificación, plan, glosario, trazabilidad, registro de cambios y actas de revisión |
| `.github/workflows/compilacion.yml` | CI y publicación (ver [CI y publicación](#ci-y-publicación)) |
| `build/` | Salida de la compilación (versionada) |
| `compilaciones/` | ISO y contenido del disco (versionados) |

Los módulos grandes se reparten en partes `.inc.c` dentro de una carpeta con el mismo nombre (por ejemplo, `codigo/graficos/interprete_f3dex/`).

## Requisitos

| Herramienta | Versión | Uso |
|---|---|---|
| Toolchain de PS2 de [ps2dev](https://github.com/ps2dev/ps2dev): `mips64r5900el-ps2-elf-gcc`, ps2sdk y gsKit | Compilé la versión incluida con EE GCC 15.2.0 | ELF para el EE |
| GNU make | 4.3 o posterior; se recomienda 4.4 | Todo el proceso |
| `gcc` del PC | C99 (probado con 13.3) | Herramientas del PC (`build/herramientas/`) y `make test` |
| Python | 3.8 o posterior, solo biblioteca estándar | Scripts de `herramientas/` (entre ellos la conversión a EUC-JP y las texturas en español), `crear_iso.sh` y `make test` |
| `genisoimage` (cdrkit) | Cualquiera | Solo para `make iso` |
| `git` | Cualquiera | Opcional: fecha de la ISO |
| GNU coreutils o BusyBox | — | `stat -c`, `md5sum`, `sha256sum`, `touch -d @N` |

Cómo compruebo estas versiones:

- **EE GCC:** `strings build/ps2/smk64.elf | grep 'GCC:'` muestra la versión usada en la compilación incluida.
- **GNU make:** el Makefile usa objetivos agrupados (`&:`), que existen desde la 4.3. Con la 4.4 o posterior, `.NOTINTERMEDIATE` conserva los archivos intermedios de la ROM; con la 4.3, make los borra al terminar.
- **Python:** con Python 3.8, las salidas de todos los scripts de `herramientas/` coinciden byte a byte con las versionadas en `build/ps2/`.
- **Conversión a EUC-JP:** la hace `herramientas/convertir_eucjp.py`, sin `iconv`. Si hay un `iconv` instalado con JIS X 0212, `make test` compara su salida con la del conversor; si no, omite esa comparación.

## Instalación del entorno

### 1. Toolchain de PS2

Resumen de la [guía de ps2dev](https://github.com/ps2dev/ps2dev#requirements). La ruta de `PS2DEV` debe ser absoluta, sin espacios ni caracteres especiales.

```bash
export PS2DEV=/usr/local/ps2dev
sudo mkdir -p "$PS2DEV"
sudo chown -R "$USER": "$PS2DEV"
```

**Opción A, binarios precompilados** (Linux x86-64):

```bash
curl -LO https://github.com/ps2dev/ps2dev/releases/download/latest/ps2dev-ubuntu-latest.tar.gz
tar -xf ps2dev-ubuntu-latest.tar.gz --strip-components 1 -C "$PS2DEV"
```

**Opción B, compilar desde el código** (dependencias para Ubuntu; para otros sistemas, ver la guía):

```bash
sudo apt -y install gcc g++ make cmake patch git texinfo flex bison gettext libgsl-dev libgmp3-dev libmpfr-dev libmpc-dev zlib1g-dev autopoint
git clone https://github.com/ps2dev/ps2dev.git
cd ps2dev
./build-all.sh
```

### 2. Herramientas del PC

En Ubuntu o Debian:

```bash
sudo apt install make gcc python3 genisoimage git
```

### 3. Cargar el entorno

En cada terminal donde vayas a compilar, desde la raíz del repositorio. Ejecuta el script con `.`, no como programa:

```bash
export PS2DEV=/ruta/a/ps2dev   # solo si no está en /usr/local/ps2dev
. herramientas/entorno.sh
```

`herramientas/entorno.sh` comprueba que exista `$PS2DEV/ee/bin/mips64r5900el-ps2-elf-gcc`. Después exporta `PS2DEV`, `PS2SDK` (`$PS2DEV/ps2sdk`) y `GSKIT` (`$PS2DEV/gsKit`) y añade al `PATH` los binarios del toolchain.

### Alternativa: Docker

La imagen `ps2dev/ps2dev` está basada en Alpine. Trae el toolchain en `/usr/local/ps2dev` con las variables ya definidas, pero no las herramientas del PC ni `git`.

```bash
docker pull ps2dev/ps2dev
docker inspect --format '{{index .RepoDigests 0}}' ps2dev/ps2dev   # ps2dev/ps2dev@sha256:…
docker run --rm -it -v "$PWD":/src -w /src \
    -e SOURCE_DATE_EPOCH="$(git log -1 --format=%ct)" \
    -e PROPIETARIO="$(id -u):$(id -g)" \
    ps2dev/ps2dev@sha256:<digest> sh
```

Dentro del contenedor:

```sh
apk add --no-cache make gcc musl-dev python3 cdrkit   # cdrkit trae genisoimage
. herramientas/entorno.sh
make -j"$(nproc)" && make iso
chown -R "$PROPIETARIO" build compilaciones
```

- Fija la imagen por su digest (`ps2dev/ps2dev@sha256:…`) para que la compilación no cambie cuando se publique una imagen nueva. La CI usa el digest que figura en [CI y publicación](#ci-y-publicación).
- `SOURCE_DATE_EPOCH` lleva la fecha del último commit, porque la imagen no tiene `git`. Sin ella, la ISO toma la fecha 0 (1970).
- El contenedor corre como root. El `chown` final devuelve los archivos a tu usuario.

## Compilar

```bash
. herramientas/entorno.sh
make -j"$(nproc)"
make iso
```

`make iso` compila lo que falte antes de crear la imagen. Las variables se combinan con cualquier objetivo, por ejemplo `make DEBUG=1 iso`.

> `build/` y `compilaciones/` están versionados, y compilar los modifica. Ver [Binarios versionados](#binarios-versionados).

### Objetivos

| Comando | Qué hace |
|---|---|
| `make` / `make elf` | ELF final y `SMK64ROM.BIN` |
| `make iso` | Imagen ISO para PCSX2, Play! y OPL (`herramientas/crear_iso.sh`) |
| `make test` | Pruebas en el PC (ver [Pruebas](#pruebas)) |
| `make herramientas` | Herramientas del PC: `build/herramientas/mio0`, `build/herramientas/empaquetador_listas` y `build/herramientas/tkmk00` |
| `make es` | Texturas en español a partir de los PNG de `recursos/es/`, en `build/ps2/es/` (la compilación normal ya lo hace) |
| `make hoja-es` | Hojas de contacto original / español / máscara de diferencias en `build/ps2/es/hojas/`, para revisar el arte a ojo |
| `make clean` | Borra `build/ps2/` y `build/herramientas/`, que están versionados (no toca `compilaciones/`) |
| `make print-VARIABLE` | Muestra el valor de una variable del Makefile |

`make test`, `make herramientas`, `make es`, `make hoja-es` y `make clean` corren en el PC sin el SDK de PS2. Los demás objetivos, también `make print-VARIABLE`, se detienen si `PS2SDK` no está definido: carga antes el entorno.

### Variables

| Variable | Efecto |
|---|---|
| `DEBUG=1` | Panel de rendimiento en pantalla (L3 + R3) y registro por `printf`. Carpeta `build/ps2/debug/` |
| `DEV=1` | Lo mismo que `DEBUG=1` salvo el panel, más registro y guiones de prueba por `host:`. ROM dentro del ELF por defecto. Carpeta `build/ps2/dev/` |
| `DEBUG_AUDIO=1` | Estado del audio en el registro cada 2 s (`página de audio:`) y página de audio en el panel. Exige `DEBUG=1` o `DEV=1`; con `DEV=1`, la página necesita `MEDIDOR=1`. Añade `debug_audio/` a la carpeta |
| `MONOLITICO=1` | Un solo ELF con toda la ROM dentro, sin `SMK64ROM.BIN`, para uLaunchELF. Añade `monolitico/` a la carpeta. El job `release` lo compila y lo publica como `SLUS_999.99.monolitico.elf` |
| `MEDIDOR=0/1` | Quita o incluye el panel de rendimiento. Por defecto vale 1 con `DEBUG=1` y 0 en el resto, también con `DEV=1` |
| `ROM_STREAM=0/1` | ROM dentro del ELF (0) o en `SMK64ROM.BIN` (1). Por defecto vale 0 con `DEV=1` o `MONOLITICO=1` y 1 en el resto |
| `V=1` | Muestra los comandos completos |
| `OPT` | Optimización del código del juego (por defecto `-O2`) |
| `BUILD_ID` | Identificador que aparece en la pantalla de fallo (por defecto `2026-10-11`, la fecha de las versiones 1.0.0 y 1.1.0; `DEBUG=1` y `DEV=1` le añaden `-debug` y `-dev`) |
| `EXTRA_DEFINES` | Defines adicionales, por ejemplo `-DSMK64_PROF` (perfilador por muestreo), `-DSMK64_DEV_FRAMEDUMP` (volcados de pantalla, con `DEV=1`), `-DFILTRADO_TEXTURAS=0` (texturas sin suavizado, vecino más cercano) o `-DSMK64_DIAG_CC` (con `DEV=1`, registra los colores que el GS no reproduce igual que el RDP) |

`DEBUG`, `DEV`, `MONOLITICO` y `DEBUG_AUDIO` compilan en su propia carpeta. Si cambian otras opciones (`OPT`, `ROM_STREAM`, `MEDIDOR`, `BUILD_ID` o `EXTRA_DEFINES`), se recompila todo el código de esa carpeta. Los datos de la ROM y los fuentes preparados (`build/ps2/be/`, `build/ps2/jp/` y las texturas en español de `build/ps2/es/`) están en `build/ps2/` y son comunes a todas las variantes.

## Salida

| Compilación | Carpeta | Archivos |
|---|---|---|
| `make` | `build/ps2/` | `SLUS_999.99` (ELF sin símbolos), `smk64.elf` (con símbolos), `smk64.map`, `SMK64ROM.BIN` |
| `make DEBUG=1` | `build/ps2/debug/` | Los mismos |
| `make DEV=1` | `build/ps2/dev/` | `SLUS_999.99`, `smk64.elf`, `smk64.map` (ROM dentro del ELF) |
| `MONOLITICO=1` | `<carpeta>/monolitico/` | ELF con la ROM completa, sin `SMK64ROM.BIN` |
| `make iso` | `compilaciones/` | `SLUS_999.99.SuperMarioKart64.iso` (`..._DEBUG.iso` con `DEBUG=1` o `DEV=1`) |
| | `compilaciones/disco/contenido/` | Contenido del disco: `SYSTEM.CNF`, `SLUS_999.99` y, si la ROM va aparte, `SMK64ROM.BIN` (`contenido_debug/` con `DEBUG=1` o `DEV=1`) |
| | `compilaciones/disco/OPL/CD/` | Copia de la ISO con el nombre que espera OPL |

La ISO lleva el volumen `SMK64_PS2` y arranca `cdrom0:\SLUS_999.99;1` en modo NTSC. Al terminar, `crear_iso.sh` muestra su SHA-256. `MONOLITICO=1` no cambia el nombre de la ISO: `make MONOLITICO=1 iso` sobrescribe la normal.

### Binarios versionados

El repositorio incluye una compilación hecha:

- `build/`: las variantes normal, `DEBUG=1` y `DEV=1`, los datos de la ROM (con las texturas en español), los ejecutables de las pruebas y las herramientas `mio0` y `empaquetador_listas`.
- `compilaciones/`: la ISO normal y el contenido del disco.

No incluye el ELF monolítico, que compila y publica el job `release`, ni la herramienta `tkmk00`, que `make test` compila al vuelo. La compilación versionada es la del último commit de publicación, `build(compilaciones): binarios e ISO en español`; la de la versión 1.0.0 es `900c9be` y la de la 1.1.0, `45bbe10a`.

`make`, `make iso`, `make test` y `make clean` modifican o borran esos archivos. **No se commitean durante el trabajo.** Después de compilar y probar, restáuralos:

```bash
git checkout -- build compilaciones
git status --short build compilaciones   # si quedan archivos nuevos (??):
git clean -fd -- build compilaciones
```

Solo se regeneran en un commit de publicación, dedicado y sin otros cambios. Hace falta GNU make 4.4 o posterior: con la 4.3, make borra los intermedios de la ROM y `git add` registraría su borrado.

```bash
make clean
make -j"$(nproc)" && make DEBUG=1 -j"$(nproc)" && make DEV=1 -j"$(nproc)"
make test && make iso
git add -A build/ps2 compilaciones
```

El bloque reproduce lo que hace la CI: el commit de publicación lo hace el job `publicar` (ver [CI y publicación](#ci-y-publicación)).

## Pruebas

```bash
make test
git clean -fdq -- build && git checkout -- build
```

`make test` no necesita el SDK de PS2 ni el entorno cargado. Compilo las pruebas en C con el `gcc` del PC y `-fsigned-char` (el `char` del R5900 lleva signo); las demás son scripts de Python. Cualquier comprobación que no se cumple hace fallar `make test` con código de salida distinto de 0. Deja sus copias y ejecutables en `build/`, que está versionado: por eso la limpieza del final.

El objetivo `test` del `Makefile` corre 46 pruebas de `herramientas/pruebas/` (21 en C y 25 en Python) y después el comprobador del tope de líneas, `herramientas/comprobar_lineas.py`. Cada prueba termina con una línea `N comprobaciones, M fallos`, salvo `prueba_caminos_vehiculos`, que informa por camino:

| Área | Pruebas | Qué comprueban |
|---|---|---|
| Juego y port | `prueba_combinador.c`, `prueba_caminos_vehiculos.c` | Combinador de color en seis casos y el alfa con tramado (-64 da 0, 64 da 32 y 128 da 128); tabla precalculada de caminos del tren y del barco contra el algoritmo original, en modo normal y espejo |
| Mandos, Memory Card y región | `prueba_eje_palanca.c`, `prueba_eleccion_guardado.c`, `prueba_region_ps2.c` | Conversión del eje del stick (centro, extremos ±80, simetría, monotonía y giro a 28 o menos del centro) y reposo de la cruceta por debajo de `ZONA_REPOSO_CRUCETA`; copia que se pisa y generación mínima al guardar en una tarjeta nueva; región PAL, NTSC o desconocida a partir de `rom0:ROMVER` |
| Codificación | `prueba_convertir_eucjp.py`, `prueba_metadatos_eucjp.py`, `prueba_caracteres_es.c` | Conversión a EUC-JP (errores con `ruta:línea:columna`), metadatos de pista convertidos, lectura de Á É Í Ó Ú Ñ Ü ¡ ¿ º ª en EUC-JP y UTF-8 y `quitar_diacriticos` |
| Pantallas del port | `prueba_fuente_5x7.c`, `prueba_textos_port.py`, `prueba_ancho_panel.py`, `prueba_cadena_depuracion.c` | Fuente del panel con tildes; textos del panel, del registro y de la pantalla de fallo, con la lista negra ampliada a los textos nuevos del original; ancho de las líneas del panel y la fila libre entre líneas; fuente de depuración N64 |
| Vídeo | `prueba_registros_video.c`, `prueba_vista_panoramica.c` | PMODE, DBY y DISPLAY por defecto iguales a los de gsKit; antiparpadeo `0x8027` con DBY en el bit 43; DY siempre par; bandas con bases de MAGH 0 y 1 sin desbordar; aspecto ×4/3 solo en PANORÁMICO y cono de visibilidad con tope |
| Opciones, menú y trucos | `prueba_opciones_port.c`, `prueba_menu_configuracion.c`, `prueba_trucos.c`, `prueba_truco_objeto.c`, `prueba_cilindrada_200cc.c`, `prueba_rivales_sin_ventaja.c` | Formato de `SMK64CFG.DAT` (firma, versión, tamaño, CRC32 y saneado), valores por defecto según 16:9; navegación y ciclo de valores del menú; DESBLOQUEAR TODO; OBJETO en GP, batalla, contrarreloj y con valores inválidos; fórmula de 200CC contra las tablas originales con el peor caso por debajo de 8,8 por paso; RIVALES SIN VENTAJA |
| Memory Card (arnés) | `prueba_memory_card.c` | `memory_card.c` compilado en el PC con la libmc simulada de `sdk_simulado/`: carga, guardado, tarjeta nueva, tarjeta que deja de contestar (sin más órdenes en la sesión), espera al arrancar con un reloj simulado y archivo de opciones |
| CI y emulador | `prueba_tope_rom.py`, `prueba_fuente_libdebug.py`, `prueba_comprobar_registro.py`, `prueba_comparar_capturas.py` | Los scripts de `herramientas/ci/` y `herramientas/emulador/` con datos sintéticos: tope de 256 KiB, glifos CP437 de libdebug, registro (región, pánico, guion) y capturas (tolerancia, tamaño, imagen uniforme) |
| Arranque y cronómetro | `prueba_arranque.py`, `prueba_cronometro_fases.c` | `inicializar_depuracion()` va en `main()` antes del reinicio del IOP y el cronómetro arranca antes del primer paso; el cronómetro de fases admite los 6 grupos, y `GRUPOS_MAX` es mayor que el número de `GRUPO_` de `marcas_registro.h` |
| Fuente del menú | `prueba_glifos.c`, `prueba_glifos_es.py`, `prueba_tablas_glifos.py`, `prueba_reserva_matrices.py` | Compatibilidad con la N64 (huella de índices y avances) y detector del primer byte que la fuente no dibuja; anchos y arte reproducible de los 11 glifos nuevos; tabla de 247 glifos definida una sola vez, tope de la reserva de matrices (la condición entera) y registro DEV en las tres impresoras de cadenas; `prueba_reserva_matrices.py` exige el tope antes de cada escritura en `efecto_mtx` |
| Textos | `prueba_textos.c` (con sus tablas `prueba_textos_*.inc.c` y `prueba_textos_tinta.py`) | Todas las tablas en español: glosario y lista negra, número de entradas, glifo para cada carácter, textos esperados byte a byte, zona segura medida por tinta, interlineado y signos de apertura |
| Texturas | `prueba_png_simple.py`, `prueba_formatos_textura.py`, `prueba_tkmk00.py`, `prueba_invertir_texturas.py`, `prueba_texturas_es.py`, `prueba_cableado_es.py`, `prueba_composicion_es.py`, `prueba_hud_es.py`, `prueba_lakitu_es.py`, `prueba_titulos_es.py`, `prueba_cartel_es.py`, `prueba_hojas_es.py`, `prueba_textura_menu.c` | Herramientas de PNG y formatos, despacho TKMK00/MIO0, manifiesto (sin botones de la N64 en los textos), cableado en la ROM y tamaños, composición del arte, HUD sin solapes de 1 a 4 jugadores, 16 cuadros y paleta de Lakitu, títulos de pista, cartel de la granja y hojas de contacto. El manifiesto clasifica las 1229 texturas con filas de textura, de carpeta (`carpeta:`) y de archivo (`archivo:`), y `TEXTURAS_PENDIENTES` vale 0 |
| Calidad | `herramientas/comprobar_lineas.py` | Ningún archivo de código pasa de 1000 líneas |

Medido el 2026-10-11 en `fd6a4bb7` (base de la documentación de la versión 1.2.0) con `PS2SDK= make test`: código de salida 0, las 46 pruebas con 0 fallos (`prueba_textos`: 237 426 comprobaciones y 0 tablas pendientes; `prueba_eje_palanca`: 438; `prueba_memory_card`: 83; `prueba_registros_video`: 66; `prueba_menu_configuracion`: 55; `prueba_opciones_port`: 38; `prueba_truco_objeto`: 29; `prueba_cilindrada_200cc`: 19; `prueba_region_ps2`: 17; `prueba_vista_panoramica`: 16; `prueba_trucos`: 13; `prueba_rivales_sin_ventaja`: 5) y 0 archivos por encima del tope de líneas.

**Qué no comprueba `make test`.** Ninguna prueba del PC mira la imagen: eso lo hace el job `emulador` de la CI, con capturas del título, del menú, del menú de configuración y de la carrera en Play! (ver [CI y publicación](#ci-y-publicación)). Esas capturas leen la VRAM antes del PCRTC, así que el antiparpadeo, las bandas y la posición solo los compruebo por los valores de registro. Sin hardware real ni TV quedan sin verificar el tacto del stick, el multitap, el cambio de tarjeta en caliente, el rendimiento en PANORÁMICO y la lectura de `rom0:ROMVER` con una BIOS real o lanzado desde OPL sin reinicio del IOP (en la CI solo se lee un ROMVER sintético por la ruta con reinicio). No queda deuda abierta ([deuda.md](../traduccion/deuda.md)); lo que solo se ve en hardware real son los límites declarados.

## Depuración

### Compilaciones

- **`make DEBUG=1`**: el registro sale por `printf` con el prefijo `smk64:` (consola del EE en el emulador) e incluye el panel de rendimiento.
- **`make DEV=1`**: además del registro por `printf`, activa:
  - el registro en `host:smk64_log.txt` (cuando se llena el búfer, se vuelca a `host:smk64_log_NN.txt`);
  - los guiones de prueba;
  - con `EXTRA_DEFINES=-DSMK64_DEV_FRAMEDUMP`, volcados de pantalla `host:frameNNNNN.tga` en cuadros fijos;
  - con `EXTRA_DEFINES=-DSMK64_NO_IOP_RESET`, compilación de depuración para OPL: el arranque solo hace `SifInitRpc` y nunca reinicia el IOP. Así conserva los módulos que OPL ya cargó. Sin la definición, el IOP se reinicia salvo que OPL lance el juego;
  - avisos en el registro, una vez cada uno, de lo que en pantalla falla en silencio: una cadena del menú con un byte que la fuente no dibuja (`texto del menú con un byte inválido`, en las tres impresoras de `imprimir_texto.inc.c`) y la reserva de matrices del texto agotada (`menu: reserva de matrices agotada`).

  No incluye el panel salvo con `MEDIDOR=1`.
- **Todas las compilaciones** muestran la pantalla de fallo ante una excepción del EE, un error fatal o un cuelgue. Se considera cuelgue pasar 6 s sin cuadros, o 30 s durante una fase de carga o mientras se espera la ROM del disco. La pantalla muestra:
  - el `BUILD_ID` y el motivo;
  - la fase activa (arranque o carga de pista) y su último paso;
  - la tabla de hilos: prioridad, estado, espera, función de entrada y último punto de control;
  - las últimas líneas del registro.

### Panel de rendimiento (L3 + R3)

Muestra FPS (actual, mínimo, máximo y promedio), milisegundos por cuadro, reparto de CPU, esperas del GS y del DMA, triángulos, subidas de texturas, memoria libre, cortes de audio, porcentaje de la ROM ya cargado y los tiempos de arranque y de carga de pista.

Aparece completo al arrancar. Cada vez que se presiona L3 + R3 pasa a una línea, después a oculto y vuelve a completo. Con `DEBUG_AUDIO=1`, entre oculto y completo aparece la página de audio.

Las líneas del panel dejan una fila libre entre ellas para que las tildes no toquen la línea de arriba (`TEXTO_ALTO_LINEA` en `incluir/depuracion/texto_pantalla.h`). Por eso el panel reserva 128 KB de VRAM (`MEDIDOR_VRAM_BYTES` en `incluir/depuracion/medidor_rendimiento.h`).

### Guiones de prueba (`DEV=1`)

Si existe `host:smk64_input.txt`, el guion sustituye a los mandos, el juego ve 4 mandos conectados y el juego escribe el resultado en `host:smk64_test.txt`. El guion lleva una orden por línea, y `#` inicia un comentario.

| Orden | Efecto |
|---|---|
| `espera N` | N cuadros sin presionar nada |
| `pulsa BOTONES [N]` | Presiona durante N cuadros (2 por defecto) y suelta |
| `mantiene BOTONES N` | Mantiene presionado durante N cuadros |
| `stick X Y N [BOTONES]` | Stick en (X, Y) durante N cuadros |
| `hasta VAR CMP VALOR [MAX]` | Espera a que se cumpla la condición (3000 cuadros por defecto). Si no se cumple, registra `FALLO` y aborta |
| `pulsa_hasta BOTONES VAR CMP VALOR [MAX]` | Presiona cada 12 cuadros hasta que se cumpla la condición |
| `comprueba VAR CMP VALOR` | Registra `ok` o `FALLO` sin abortar |
| `si VAR CMP VALOR N` | Salta las N órdenes siguientes si no se cumple la condición |
| `mando N` | Las órdenes siguientes van al mando N (1 a 4) |
| `fija BOTONES` | Deja botones presionados de forma permanente en el mando actual |
| `autopiloto si\|no` | La CPU conduce a los jugadores humanos |
| `intermedio si\|no` | Activa o desactiva los 60 FPS |
| `objeto N [J]` | Da el objeto N (1 a 15) al jugador J |
| `nota TEXTO` | Escribe una nota en el resultado |
| `muestra VAR` | Escribe el valor de la variable en el resultado |
| `siguiente_estado N` | Pasa el juego al estado N, como el atajo de depuración del original |
| `disparador BITS [J]` | Pone esos bits de disparador en el jugador J (1 a 8; por defecto, el del mando actual) |
| `memoria` | Escribe el montón libre, la reserva del juego, el audio y la caché de texturas |
| `captura NOMBRE` | Guarda la pantalla en `host:NOMBRE.tga`. Si no se ha guardado en 900 cuadros, registra un aviso y sigue |
| `graba PREFIJO C N`, `graba no` | Guarda N capturas `host:PREFIJO_NNN.tga`, una cada C cuadros, sin parar el guion / las corta |
| `camaras`, `volcado` | Vuelca las cámaras al registro / pide un volcado de la lista de dibujo |
| `audio NOMBRE S`, `tareas_audio NOMBRE N` | Graba S segundos de audio / vuelca N tareas de audio en `host:` |
| `perfil inicio`, `perfil fin NOMBRE` | Perfilado por muestreo (requiere `EXTRA_DEFINES=-DSMK64_PROF`) |
| `fallo [div]` | Provoca una excepción para probar la pantalla de fallo |
| `fin` | Termina el guion |

- **Botones:** `A B Z R L START CU CD CL CR ARRIBA ABAJO IZQ DER NADA`, combinables con `+` (por ejemplo, `A+R`).
- **Comparadores:** `== != < <= > >=`.
- **Variables:** `estado menu pista modo carrera pausa vuelta puesto jugadores copa cc demo frame submenu seleccion menupausa resultados columna subcolumna menufinal efectos disparadores rapidez`.

Las órdenes `captura` y `graba` vienen del original. Una captura pedida mientras otra sigue pendiente puede perderse, y el `.tga` puede salir con el alfa del último vértice del cuadro. Ningún flujo del proyecto las usa, y queda como propuesta para el original (G2 en [CC-11](../traduccion/cambios.md)).

Ejemplo:

```text
# host:smk64_input.txt
espera 120                       # 120 cuadros sin tocar nada
pulsa_hasta A estado == 4 3600   # presiona A hasta que estado valga 4 (carrera)
autopiloto si
espera 600
comprueba pausa == 0
fin
```

## CI y publicación

El workflow `compilacion` (`.github/workflows/compilacion.yml`) corre en cada push y pull request, y también a pedido (`workflow_dispatch`). Los jobs de compilación y `release` usan la imagen `ps2dev/ps2dev@sha256:7327334ab94e273b1723761fcd4a3591a31b78bbc28e4c281ad0fa42b3c8264d`, fijada por digest.

| Job | Cuándo corre | Qué hace |
|---|---|---|
| `pruebas-pc` | Siempre | `make test` en `ubuntu-latest`, sin el SDK |
| `compilar-ps2` | Siempre | `make clean`; `make` (release); tope de crecimiento de la ROM; build incremental sin una sustitución; `make DEBUG=1` y `make DEV=1`; `make test`; inspección de la fuente de libdebug; `make iso`. Guarda como artefacto `smk64-ps2` el ELF release, `SMK64ROM.BIN`, el mapa, los ELF de `DEBUG=1` y `DEV=1` y la ISO |
| `emulador` | Siempre, tras `compilar-ps2` | Arranca dos veces el ELF de `DEV=1` en Play! sin BIOS, con un guion, y comprueba el registro y las capturas (ver [Job del emulador](#job-del-emulador)) |
| `mismo-binario` | A pedido, con `base` no vacía | `herramientas/comparar_binario.sh <base>` para release y para `DEBUG=1`: compila la base y el árbol actual desde cero y compara el ELF sin símbolos y `SMK64ROM.BIN`. Un refactor tiene que dar los mismos bytes |
| `publicar` | A pedido, con `publicar` = `si` o `sí` | Exige GNU make 4.4 o posterior; `make clean`, las variantes release, `DEBUG=1` y `DEV=1`, `make test` y `make iso`. Prepara `build/ps2` y `compilaciones`; si no hay nada preparado (`git diff --cached --quiet`), termina en verde sin commit. Si hay cambios, commitea con el mensaje `build(compilaciones): binarios e ISO en español`, con el commit de origen y la ejecución en el cuerpo, y hace push a la misma rama. Un fallo del commit o del push detiene el job en rojo |
| `release` | A pedido, con `release` = etiqueta | Corre en el contenedor de ps2dev. Exige `compilaciones/SLUS_999.99.SuperMarioKart64.iso` y `docs/versiones/<etiqueta>.md`, y se detiene si el SHA-256 de la ISO no aparece en esas notas. Después, `make clean` y `make MONOLITICO=1`, que deja el ELF monolítico como `SLUS_999.99.monolitico.elf`. Escribe `SHA256SUMS` con dos líneas, la ISO y el ELF monolítico, y crea la Release `<etiqueta>` sobre el commit lanzado, con el título «Mario Kart 64 PS2 en español <etiqueta>», los tres archivos y esas notas como cuerpo |
| `limpiar-ramas` | A pedido, con `limpiar_ramas` = `si` o `sí` | Borra cada rama remota cuya punta ya está en `main` (`git merge-base --is-ancestor`). Conserva `main` y las ramas con commits propios |

Pasos de `compilar-ps2` que necesitan el SDK (`herramientas/ci/`):

| Paso | Script | Qué exige |
|---|---|---|
| Tope de crecimiento de la ROM | `tope_rom.py` | `build/ps2/rom.bin` crece menos de 256 KiB sobre la base medida de `main` (R-TEX-03, D-03) |
| Build incremental sin una sustitución | `comprobar_incremental.sh` | Al quitar un PNG del HUD y compilar sin `make clean`, desaparece su `.inc.c` de `build/ps2/es`, vuelve la textura original y cambia el ELF; al reponerlo vuelve el ELF del principio (R-TEX-08, D-04) |
| Fuente de libdebug | `inspeccionar_fuente_libdebug.py` | Los glifos de `msx[]` en `libdebug.a` son los CP437 de las letras del español, para que la pantalla de fallo escriba con tildes con `scr_putchar` (D-07) |

### Job del emulador

`emulador` ([CC-26](../traduccion/cambios.md)) corre en `ubuntu-24.04` con un límite de 40 minutos:

1. Descarga Play! 0.72 (AppImage) y comprueba su SHA-256, fijado en el workflow. Corre bajo Xvfb con Vulkan por software (lavapipe): con OpenGL, las capturas leen la RAM del GS vacía.
2. `herramientas/emulador/ejecutar_play.sh` monta `host:`, `mc0:` y `rom0:` como carpetas, escribe un `rom0:ROMVER` sintético europeo (`0160EC20010704`), copia `guion_ci.txt` como `host:smk64_input.txt` y arranca el ELF con `--elf`. Se detiene al terminar el guion o a los 900 s.
3. El guion pasa por el título, el menú principal, el menú CONFIGURACIÓN Y TRUCOS (desde la 1.2.1) y una carrera de Gran Premio, con una `captura` en cuadros fijos de cada pantalla. La navegación es determinista: dos ejecuciones dan un 0,0000 % de diferencia.
4. `comprobar_registro.py` exige que el registro llegue al bucle principal sin pánico ni cuelgue, la línea de región PAL, la línea `vídeo: PMODE 8046` y que el guion termine con `fin`, 0 fallos y ninguna captura perdida.
5. `comparar_capturas.py` compara las capturas con `herramientas/emulador/referencias/` (`titulo`, `menu`, `configuracion`, `carrera`) y las de la segunda ejecución con las de la primera; falla si falta una captura, si cambia de tamaño, si es de un solo color o si difiere en más del 0,1 % de los píxeles. Esa tolerancia por defecto (0,001) bajó de 0,02 en la 1.2.1 ([CC-31](../traduccion/cambios.md)): un bloque de 32×16 cambiado (0,18 %) ya no pasa.
6. El job falla si dura 30 minutos o más, y guarda como artefacto `emulador` los registros y las capturas.

**Regenerar las referencias.** Si un cambio visible es intencionado, lanza el workflow a mano sobre la rama con `regenerar_referencias` = `si` o `sí`. El job escribe las capturas de la primera ejecución como referencias, comprueba la segunda contra ellas, copia `menu`, `carrera` y `configuracion` a `docs/img/` y commitea en la rama con el asunto `test(emulador): referencias regeneradas en la CI con el ELF de DEV actual` y la ejecución en el cuerpo. Si nada cambia, termina sin commit. Antes de integrar, revisa a ojo las referencias nuevas: así aparecieron en la 1.2.1 los valores tenues del menú de configuración y el ordinal «8º.».

Límites: las capturas leen la VRAM antes del PCRTC, así que no muestran el antiparpadeo, las bandas ni la posición; ROMVER solo se lee por la ruta con reinicio del IOP. Ejecución en verde de la 1.2.0: [38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616); referencias de la 1.2.1 regeneradas en [38179540046](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38179540046) y [38180265814](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38180265814).

Entradas a pedido (Actions → `compilacion` → Run workflow, o `POST /repos/{dueño}/{repo}/actions/workflows/compilacion.yml/dispatches` con `ref` e `inputs`):

| Entrada | Por defecto | Uso |
|---|---|---|
| `base` | vacía | Referencia para comparar el binario; vacía, no se compara |
| `publicar` | `no` | `sí` regenera `build/` y `compilaciones/` y los commitea en la rama |
| `release` | vacía | Etiqueta de la Release, por ejemplo `v1.0.0`; vacía, no hay publicación |
| `limpiar_ramas` | `no` | `sí` borra las ramas remotas que ya están contenidas en `main` |

Publico una versión en este orden, cada paso con el anterior terminado en verde:

1. **`publicar`**, lanzado sobre la rama de integración: deja en ella el commit de publicación con los binarios y la ISO regenerados desde cero.
2. **Merge a `main`** de la rama de integración, con la revisión aprobada (ver [CONTRIBUTING.md](../../CONTRIBUTING.md)).
3. **`release`**, lanzado sobre `main` con la etiqueta de la versión: publica la ISO que quedó versionada en `compilaciones/` y el ELF monolítico que compila en ese momento. Las notas (`docs/versiones/<etiqueta>.md`) tienen que estar ya en `main`, con el SHA-256 de la ISO versionada.
4. **`limpiar-ramas`**, lanzado sobre `main`: solo borra lo que ya está fusionado.

El job `release` comprueba que el SHA-256 de la ISO versionada (`sha256sum compilaciones/SLUS_999.99.SuperMarioKart64.iso`) esté en las notas. No versiono el ELF monolítico: su suma se conoce cuando termina `release` y queda en el `SHA256SUMS` de la Release. Para la versión 1.0.0: ejecución de CI [38123501282](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38123501282), commit de publicación `900c9be`. Para la 1.1.0: ejecución [38149880694](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38149880694), commit de publicación `45bbe10a`. Para la 1.2.0: ejecución [38167051526](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38167051526), commit de publicación `9ab41422`.

## Traer actualizaciones del repositorio original

El repositorio original es [anthoo582/mario-kart-64-ps2](https://github.com/anthoo582/mario-kart-64-ps2). Así se sincronizó en F8 hasta `ae93f71` ([CC-08](../traduccion/cambios.md)):

1. **Traer y medir.**

   ```bash
   git remote add upstream https://github.com/anthoo582/mario-kart-64-ps2.git
   git fetch upstream
   git log --oneline origin/main..upstream/main               # commits nuevos del original
   git merge-tree --write-tree --name-only origin/main upstream/main
   ```

   `git merge-tree` (git 2.38 o posterior) lista los archivos en conflicto sin tocar el árbol. En F8 dio 9 archivos de código (12 trozos) y 95 de `build/` y `compilaciones/`.
2. **Registrar un CC antes de fusionar** en [cambios.md](../traduccion/cambios.md), con cómo se resuelve cada conflicto y la evidencia que se pedirá, y esperar su aprobación.
3. **Abrir la rama** `feature/sincronizacion-<tema>` desde `main` (en F8, `feature/sincronizacion-upstream`). Las correcciones posteriores van en subramas `sinc/<tema>` que se fusionan en ella.
4. **Fusionar sin seguir renombres de carpetas:**

   ```bash
   git -c merge.directoryRenames=false merge --no-ff upstream/main
   ```

   Sin esa opción, git toma `build/ps2/debug/`, que el original dejó de versionar, por renombrada a `build/ps2/dev/` y mueve allí archivos de este repositorio.
5. **Resolver como fusión pura**, sin traducir ni corregir nada en el commit de fusión:
   - `build/` y `compilaciones/` quedan como en `main` hasta el commit de publicación;
   - la tabla de glifos (`codigo/menus/elementos_menu/textos_y_tablas.inc.c`, `animaciones_personajes.inc.c` e `incluir/menus/elementos_menu.h`) queda como en `main`: tiene las 236 entradas del original en el mismo orden más las 11 del español;
   - en los archivos del port se toma el código del original y se conservan los textos en español;
   - `README.md` queda como en `main`; lo nuevo del original lo documento en un commit `docs` aparte.
6. **Comprobar la fusión** `M`: estos diffs tienen que salir vacíos.

   ```bash
   git diff M^1 M -- build compilaciones
   git diff M^1 M -- codigo/menus/elementos_menu/textos_y_tablas.inc.c \
       codigo/menus/elementos_menu/animaciones_personajes.inc.c incluir/menus/elementos_menu.h
   ```

7. **Traducir los textos nuevos del original** en commits propios: primero amplío la lista negra de `prueba_textos_port.py` (rojo) y después traduzco (verde). En F8: fusión `9f4d0215`, rojo `748db117`, verde `36fc9e40`. La fusión queda en rojo solo en esa prueba y nunca se sube sola.
8. **Cerrar** con `make test` en verde y la CI en verde, incluida la compilación para PS2.

Para leer un archivo de otra rama sin fusionarla: `git show origin/<rama>:<ruta>`. Lo que quiera proponer al original (por ejemplo G2 y G4 de [CC-11](../traduccion/cambios.md)) lo documento con el caso concreto y no lo aplico aquí.

## Archivos sensibles

Cambiar cualquiera de estos archivos o ajustes exige un CC aprobado en [cambios.md](../traduccion/cambios.md).

| Archivo o ajuste | Por qué está así |
|---|---|
| Digest de `ps2dev/ps2dev` en `.github/workflows/compilacion.yml` (4 apariciones: `compilar-ps2`, `mismo-binario`, `publicar` y `release`) | Fija el compilador para que el binario sea reproducible. Las cuatro tienen que cambiar juntas, y compruebo el cambio con `mismo-binario`. El ELF monolítico de la Release sale del mismo toolchain que la ISO |
| `herramientas/entorno.sh` | Lo cargan todas las compilaciones, locales y de la CI. Define `PS2DEV`, `PS2SDK`, `GSKIT` y el `PATH` del toolchain |
| `Makefile`: objetivo `test` | Define qué corre `make test` y en qué orden. Una prueba que sale de la lista deja de comprobarse sin aviso |
| `Makefile`: `BUILD_ID`, `JP_SRC` y `JP_PARTES` | `BUILD_ID` identifica la compilación en la pantalla de fallo. `JP_SRC` y `JP_PARTES` deciden qué fuentes pasan a EUC-JP |
| `build/` y `compilaciones/` | Están versionados. Solo cambian en el commit de publicación, que hace el job `publicar` |
| Tabla de glifos: `lista_glifos.inc.c`, `textos_y_tablas.inc.c` y `animaciones_personajes.inc.c` (en `codigo/menus/elementos_menu/`) | Los índices de los 236 glifos originales tienen que coincidir con los de la N64 (`prueba_glifos.c`); los 11 del español van detrás |
| `incluir/entrada/eje_palanca.h`: `ZONA_MUERTA_PALANCA` y `ZONA_REPOSO_CRUCETA` | Fijan dónde empieza el giro (28 de 127 junto con la zona muerta del juego) y hasta dónde la cruceta hace de stick (25 del centro). `prueba_eje_palanca.c` falla si el giro empieza más allá de 28; el reposo lo comprueba con la propia constante, así que cambiar `ZONA_REPOSO_CRUCETA` no la pone en rojo ([CC-14](../traduccion/cambios.md)) |
| `incluir/sistema/eleccion_guardado.h` | Decide qué copia se pisa en una tarjeta nueva y con qué generación. Un error pisa la partida más nueva o hace cargar la vieja ([CC-13](../traduccion/cambios.md)) |
| `GS_MODE_NTSC` en `codigo/graficos/sintetizador_gs.c` | El juego avanza al ritmo del retrazo: a 50 Hz iría un 17 % más lento. Las consolas PAL salen también en NTSC a 60 Hz ([CC-15](../traduccion/cambios.md)) |
| `recursos/es/texturas.tsv` | Manifiesto de las texturas en español: qué traduzco, qué excluyo y con qué texto |
| `merge.directoryRenames=false` al fusionar el original | Sin él, git mueve archivos de `build/ps2/debug/` a `build/ps2/dev/` |

## Errores a evitar

| Error | Por qué | Cómo se detecta |
|---|---|---|
| Fiarse de una copia vieja de `build/ps2/jp/` | `build/` está versionado y un checkout puede dejar la copia convertida más nueva que su fuente. Por eso `make test` vuelve a convertir en cada pasada lo que lee `prueba_textos` | `make test` falla en `prueba_textos` con textos que no coinciden |
| Buscar texto con `grep` en `build/ps2/jp/` | Esos archivos están en EUC-JP: un `grep` con tildes en UTF-8 no encuentra nada | Buscar en el fuente, que está en UTF-8 |
| Commitear `build/` o `compilaciones/` en un commit de trabajo | Mezcla binarios con cambios de código | `git status --short` antes de cada commit; restaurar con `git checkout -- build compilaciones` |
| Fusionar el original sin `merge.directoryRenames=false` | Mueve archivos versionados a otra carpeta | `git diff M^1 M -- build compilaciones` no sale vacío |
| Traducir o corregir dentro del commit de fusión | Mezcla la fusión con un cambio funcional y no se puede revisar ni revertir por separado | El commit de fusión toca más archivos de los que tenían conflicto |
| Un refactor sin comparar el resultado | Puede cambiar el binario sin que ninguna prueba lo note | `python3 herramientas/comparar_preprocesado.py` en el PC o el job `mismo-binario` en la CI |
| Usar el tipo `chore` en un commit | Las reglas de commits no lo admiten | Revisar el asunto antes de commitear (ver [CONTRIBUTING.md](../../CONTRIBUTING.md)) |
| Hacer cherry-pick sin comprobar de qué depende el commit | El commit puede necesitar otros que no están en la rama | `git diff --stat` del commit y compilar y correr `make test` después |
| Dar por verificado lo que solo se vería en pantalla | Ninguna prueba mira la imagen ([CC-12](../traduccion/cambios.md)) | Declararlo como limitación, como hace el [manual de usuario](usuario.md#limitaciones-conocidas) |

## Solución de problemas de compilación

| Síntoma | Causa y solución |
|---|---|
| `PS2SDK no definido: ejecuta '. herramientas/entorno.sh'` | El entorno no está cargado en esta terminal. Pasa con cualquier objetivo salvo `test`, `herramientas`, `es`, `hoja-es` y `clean`. Ejecuta `. herramientas/entorno.sh` (con `.`, no como programa) y repite |
| `entorno.sh: no hay toolchain de PS2 en ...` | No existe `$PS2DEV/ee/bin/mips64r5900el-ps2-elf-gcc`. Instala ps2dev o exporta `PS2DEV` con la ruta correcta |
| `git status` muestra cambios en `build/` o `compilaciones/` | Es lo esperado después de compilar o probar: están versionados. Restaura con `git checkout -- build compilaciones` |
| Al terminar `make` aparece una línea `rm ...` y faltan archivos en `build/ps2/recursos/` | GNU make 4.3 borra los intermedios de la ROM. La compilación es válida. Restaura con `git checkout -- build` o usa make 4.4 |
| `error: <ruta>:<línea>:<columna>: '…' (U+XXXX) no existe en EUC-JP` | Un texto de los fuentes que se convierten (`JP_SRC` y `JP_PARTES` del Makefile) lleva un carácter que EUC-JP no tiene. La conversión la hace `herramientas/convertir_eucjp.py`, no `iconv`, y corta la compilación en ese punto. Cambia el carácter; si además no tiene glifo en la fuente del menú, `make test` lo señala en la prueba de textos |
| `make_iso: falta genisoimage (apt install genisoimage)` | Instala `genisoimage` (en Alpine, el paquete `cdrkit`) |
| `DEBUG_AUDIO=1 necesita DEBUG=1 o DEV=1` | Combina `DEBUG_AUDIO=1` con `DEBUG=1` o `DEV=1` |
