# Manual técnico

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
| Combinador de color | Evaluación del combinador | `codigo/graficos/combinador_color.c` |
| TMEM | Carga y caché de texturas | `codigo/graficos/memoria_texturas.c` y `memoria_texturas/` |
| Salida de video | Paquetes y framebuffers del GS | `codigo/graficos/sintetizador_gs.c` |
| RSP de audio | Microcódigo en C | `codigo/audio/microcodigo_audio.c` y `microcodigo_audio/` |
| Salida de audio | `audsrv` (IRX embebidos en `codigo/datos/datos_embebidos.s`) | `codigo/audio/salida_audio.c` |
| Tareas del RSP | Reparto entre gráficos y audio | `codigo/sistema/tareas_rsp.c` |
| Hilos y mensajes | Hilos del kernel del EE | `codigo/sistema/hilos.c` |
| VI, retrazo y temporizadores | Interrupción de VBlank | `codigo/sistema/retrazo_vertical.c` |
| DMA del cartucho (PI) | Copia desde la ROM en RAM | `codigo/sistema/hardware.c`, `codigo/sistema/carga_rom.c` |
| EEPROM y Controller Pak | Imagen guardada en la Memory Card | `codigo/sistema/guardado_ps2.c`, `codigo/sistema/memory_card.c` |
| Mandos | `libpad` | `codigo/entrada/mandos.c` |

### La ROM

El código se enlaza en un ELF del EE (`compilacion/ps2.ld`). La «ROM» se construye por separado:

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
| `herramientas/pruebas/` | Pruebas de `make test` |
| `herramientas/guiones/` | Guion de recorrido para `make DEV=1` (`recorrido_textos.txt`) |
| `docs/traduccion/` | Localización al español: especificación, plan, glosario, trazabilidad y registro de cambios |
| `build/` | Salida de la compilación (versionada) |
| `compilaciones/` | ISO y contenido del disco (versionados) |

Los módulos grandes se reparten en partes `.inc.c` dentro de una carpeta con el mismo nombre (por ejemplo, `codigo/graficos/interprete_f3dex/`).

## Requisitos

| Herramienta | Versión | Uso |
|---|---|---|
| Toolchain de PS2 de [ps2dev](https://github.com/ps2dev/ps2dev): `mips64r5900el-ps2-elf-gcc`, ps2sdk y gsKit | La compilación incluida se hizo con EE GCC 15.2.0 | ELF para el EE |
| GNU make | 4.3 o posterior; se recomienda 4.4 | Todo el proceso |
| `gcc` del PC | C99 (probado con 13.3) | Herramientas del PC (`build/herramientas/`) y `make test` |
| Python | 3.8 o posterior, solo biblioteca estándar | Scripts de `herramientas/` (entre ellos la conversión a EUC-JP y las texturas en español), `crear_iso.sh` y `make test` |
| `genisoimage` (cdrkit) | Cualquiera | Solo para `make iso` |
| `git` | Cualquiera | Opcional: fecha de la ISO |
| GNU coreutils o BusyBox | — | `stat -c`, `md5sum`, `sha256sum`, `touch -d @N` |

Cómo se comprueban estas versiones:

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

En cada terminal donde vayas a compilar, desde la raíz del repositorio. El script se ejecuta con `.`, no como programa:

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

- Fija la imagen por su digest (`ps2dev/ps2dev@sha256:…`) para que la compilación no cambie cuando se publique una imagen nueva.
- `SOURCE_DATE_EPOCH` lleva la fecha del último commit, porque la imagen no tiene `git`. Sin ella, la ISO toma la fecha 0 (1970).
- El contenedor se ejecuta como root. El `chown` final devuelve los archivos a tu usuario.

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
| `MONOLITICO=1` | Un solo ELF con toda la ROM dentro, sin `SMK64ROM.BIN`. Añade `monolitico/` a la carpeta |
| `MEDIDOR=0/1` | Quita o incluye el panel de rendimiento. Por defecto vale 1 con `DEBUG=1` y 0 en el resto, también con `DEV=1` |
| `ROM_STREAM=0/1` | ROM dentro del ELF (0) o en `SMK64ROM.BIN` (1). Por defecto vale 0 con `DEV=1` o `MONOLITICO=1` y 1 en el resto |
| `V=1` | Muestra los comandos completos |
| `OPT` | Optimización del código del juego (por defecto `-O2`) |
| `BUILD_ID` | Identificador que aparece en la pantalla de fallo (por defecto `2026-09-25`) |
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

No incluye el ELF monolítico ni la herramienta `tkmk00`, que `make test` compila al vuelo. La compilación versionada, en español, es la del commit `dda9a5f` («chore(build): binarios e ISO en espanol»).

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
git add build compilaciones
```

La CI puede hacer ese commit: el job `publicar` de `.github/workflows/compilacion.yml` se lanza a mano (`workflow_dispatch`) con la entrada `publicar=si`. Compila desde cero, en la imagen de ps2dev fijada por digest, las variantes normal, `DEBUG=1` y `DEV=1`, corre `make test`, crea la ISO, exige GNU make 4.4 o posterior y commitea `build/ps2` y `compilaciones` en la misma rama. Así se generó `dda9a5f`.

`build/` está versionado y `make test` escribe ahí sus copias y sus binarios.
Después de las pruebas, para no subirlos por error:

```bash
git clean -fdq -- build && git checkout -- build
```

## Pruebas

```bash
make test
git clean -fdq -- build && git checkout -- build
```

`make test` no necesita el SDK de PS2 ni el entorno cargado. Las pruebas en C se compilan con el `gcc` del PC y `-fsigned-char` (el `char` del R5900 lleva signo); las demás son scripts de Python. Cualquier comprobación que no se cumple hace fallar `make test` con código de salida distinto de 0. Deja sus copias y ejecutables en `build/`, que está versionado: por eso la limpieza del final.

Son 26 pruebas (8 en C y 18 en Python) más el comprobador del tope de líneas, todas en `herramientas/pruebas/`:

| Área | Pruebas | Qué comprueban |
|---|---|---|
| Juego y port | `prueba_combinador.c`, `prueba_caminos_vehiculos.c` | Combinador de color en seis casos; tabla precalculada de caminos del tren y del barco contra el algoritmo original, en modo normal y espejo |
| Codificación | `prueba_convertir_eucjp.py`, `prueba_metadatos_eucjp.py`, `prueba_caracteres_es.c` | Conversión a EUC-JP (errores con `ruta:línea:columna`), metadatos de pista convertidos, lectura de Á É Í Ó Ú Ñ Ü ¡ ¿ º ª en EUC-JP y UTF-8 y `quitar_diacriticos` |
| Fuente del menú | `prueba_glifos.c`, `prueba_tablas_glifos.py`, `prueba_glifos_es.py` | Compatibilidad con la N64 (huella de índices y avances), tabla de 247 glifos, anchos y arte reproducible de los 11 glifos nuevos |
| Textos | `prueba_textos.c` (con sus tablas `prueba_textos_*.inc.c` y `prueba_textos_tinta.py`) | Todas las tablas en español: glosario y lista negra, número de entradas, glifo para cada carácter, textos esperados byte a byte, zona segura medida por tinta, interlineado y signos de apertura |
| Pantallas del port | `prueba_fuente_5x7.c`, `prueba_textos_port.py`, `prueba_ancho_panel.py`, `prueba_cadena_depuracion.c` | Fuente del panel con tildes, textos del panel, del registro y de la pantalla de fallo, ancho de las líneas del panel y fuente de depuración N64 |
| Texturas | `prueba_png_simple.py`, `prueba_formatos_textura.py`, `prueba_tkmk00.py`, `prueba_textura_menu.c`, `prueba_invertir_texturas.py`, `prueba_texturas_es.py`, `prueba_cableado_es.py`, `prueba_composicion_es.py`, `prueba_hud_es.py`, `prueba_lakitu_es.py`, `prueba_titulos_es.py`, `prueba_cartel_es.py`, `prueba_hojas_es.py` | Herramientas de PNG y formatos, despacho TKMK00/MIO0, manifiesto, cableado en la ROM y tamaños, composición del arte, HUD sin solapes de 1 a 4 jugadores, 16 cuadros y paleta de Lakitu, títulos de pista, cartel de la granja y hojas de contacto |
| Calidad | `herramientas/comprobar_lineas.py` | Ningún archivo de código pasa de 1000 líneas |

## Depuración

### Compilaciones

- **`make DEBUG=1`**: el registro sale por `printf` con el prefijo `smk64:` (consola del EE en el emulador) e incluye el panel de rendimiento.
- **`make DEV=1`**: además del registro por `printf`, activa:
  - el registro en `host:smk64_log.txt` (cuando se llena el búfer, se vuelca a `host:smk64_log_NN.txt`);
  - los guiones de prueba;
  - con `EXTRA_DEFINES=-DSMK64_DEV_FRAMEDUMP`, volcados de pantalla `host:frameNNNNN.tga` en cuadros fijos.

  No incluye el panel salvo con `MEDIDOR=1`.
- **Todas las compilaciones** muestran la pantalla de fallo ante una excepción del EE, un error fatal o un cuelgue. Se considera cuelgue pasar 6 s sin cuadros, o 30 s durante una fase de carga o mientras se espera la ROM del disco. La pantalla muestra:
  - el `BUILD_ID` y el motivo;
  - la fase activa (arranque o carga de pista) y su último paso;
  - la tabla de hilos: prioridad, estado, espera, función de entrada y último punto de control;
  - las últimas líneas del registro.

### Panel de rendimiento (L3 + R3)

Muestra FPS (actual, mínimo, máximo y promedio), milisegundos por cuadro, reparto de CPU, esperas del GS y del DMA, triángulos, subidas de texturas, memoria libre, cortes de audio, porcentaje de la ROM ya cargado y los tiempos de arranque y de carga de pista.

Aparece completo al arrancar. Cada vez que se presiona L3 + R3 pasa a una línea, después a oculto y vuelve a completo. Con `DEBUG_AUDIO=1`, entre oculto y completo aparece la página de audio.

### Guiones de prueba (`DEV=1`)

Si existe `host:smk64_input.txt`, el guion sustituye a los mandos, el juego ve 4 mandos conectados y el resultado se escribe en `host:smk64_test.txt`. El guion lleva una orden por línea, y `#` inicia un comentario.

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
| `captura NOMBRE` | Escribe `host:captura.req` para una herramienta externa que el repositorio no incluye. Si nadie la atiende en 900 cuadros, registra un aviso y sigue |
| `camaras`, `volcado` | Vuelca las cámaras al registro / pide un volcado de la lista de dibujo |
| `audio NOMBRE S`, `tareas_audio NOMBRE N` | Graba S segundos de audio / vuelca N tareas de audio en `host:` |
| `perfil inicio`, `perfil fin NOMBRE` | Perfilado por muestreo (requiere `EXTRA_DEFINES=-DSMK64_PROF`) |
| `fallo [div]` | Provoca una excepción para probar la pantalla de fallo |
| `fin` | Termina el guion |

- **Botones:** `A B Z R L START CU CD CL CR ARRIBA ABAJO IZQ DER NADA`, combinables con `+` (por ejemplo, `A+R`).
- **Comparadores:** `== != < <= > >=`.
- **Variables:** `estado menu pista modo carrera pausa vuelta puesto jugadores copa cc demo frame submenu seleccion menupausa resultados columna subcolumna menufinal`.

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

## Solución de problemas

| Síntoma | Causa y solución |
|---|---|
| `PS2SDK no definido: ejecuta '. herramientas/entorno.sh'` | El entorno no está cargado en esta terminal. Pasa con cualquier objetivo salvo `test`, `herramientas`, `es`, `hoja-es` y `clean`. Ejecuta `. herramientas/entorno.sh` (con `.`, no como programa) y repite |
| `entorno.sh: no hay toolchain de PS2 en ...` | No existe `$PS2DEV/ee/bin/mips64r5900el-ps2-elf-gcc`. Instala ps2dev o exporta `PS2DEV` con la ruta correcta |
| `git status` muestra cambios en `build/` o `compilaciones/` | Es lo esperado después de compilar o probar: están versionados. Restaura con `git checkout -- build compilaciones` |
| Al terminar `make` aparece una línea `rm ...` y faltan archivos en `build/ps2/recursos/` | GNU make 4.3 borra los intermedios de la ROM. La compilación es válida. Restaura con `git checkout -- build` o usa make 4.4 |
| `error: <ruta>:<línea>:<columna>: '…' (U+XXXX) no existe en EUC-JP` | Un texto de los fuentes que se convierten (`JP_SRC` y `JP_PARTES` del Makefile) lleva un carácter que EUC-JP no tiene. La conversión la hace `herramientas/convertir_eucjp.py`, no `iconv`, y corta la compilación en ese punto. Cambia el carácter; si además no tiene glifo en la fuente del menú, `make test` lo señala en la prueba de textos |
| `make_iso: falta genisoimage (apt install genisoimage)` | Instala `genisoimage` (en Alpine, el paquete `cdrkit`) |
| `DEBUG_AUDIO=1 necesita DEBUG=1 o DEV=1` | Combina `DEBUG_AUDIO=1` con `DEBUG=1` o `DEV=1` |
