# Mario Kart 64 para PlayStation 2

Port de Mario Kart 64 (versión estadounidense) a PlayStation 2. El repositorio incluye el juego descompilado, una capa de compatibilidad que sustituye el hardware de la Nintendo 64 por el de la PS2 y todos los recursos ya extraídos (texturas, pistas, karts, música y efectos). No hace falta la ROM original para compilar.

## Estado

- Probado en **PCSX2** (con BIOS real) y en **Play!**.
- **Sin probar en una PS2 real**, ni con OPL o uLaunchELF en hardware.
- Video NTSC entrelazado a 640×448 (`codigo/graficos/sintetizador_gs.c`).
- Limitación conocida: solo se leen los puertos de mando 1 y 2 de la consola, sin multitap (`PUERTOS_PS2` en `codigo/entrada/mandos.c`). En VS y Batalla de 3 o 4 jugadores, los jugadores 3 y 4 no tienen mando.
- **Juego en español**: menús, mensajes, Memory Card, créditos, títulos de pista, HUD, carteles de Lakitu y pantallas propias del port. Detalle y estado de la verificación en [Idioma](#idioma).

## Descarga

La ISO ya compilada, en español, está en el repositorio: [`compilaciones/SLUS_999.99.SuperMarioKart64.iso`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/raw/main/compilaciones/SLUS_999.99.SuperMarioKart64.iso) (13 373 440 bytes, unos 12,8 MiB).

- **PCSX2** (con BIOS) o **Play!**: abrir la ISO directamente.
- **OPL**: copiar la carpeta `compilaciones/disco/OPL/CD/`, que lleva la misma ISO con el nombre que espera OPL, a la raíz del USB o del recurso SMB (sin probar en hardware).

Para compilarla desde el código, ver [Compilar](#compilar).

## Características

- Las 20 pistas (16 de carrera y 4 de batalla), los 8 personajes y los modos Gran Premio, Contrarreloj, VS y Batalla.
- Gráficos: un intérprete de listas de dibujo F3DEX, con el combinador de color y la TMEM de la N64, que produce paquetes para el GS.
- Audio original: las muestras de la ROM se mezclan con la misma aritmética que la N64 (microcódigo de audio reescrito en C) y salen a 48 kHz por `audsrv`.
- Modo 60 FPS, activo por defecto y conmutable con R3. Dibuja un cuadro intermedio solo durante la carrera, fuera de pausa, y solo si queda tiempo de CPU. La lógica del juego sigue a 30 Hz, como en el original.
- Partidas guardadas en la Memory Card de la ranura 1, en dos copias alternas con CRC32.
- Los datos de la ROM se leen del disco en segundo plano desde el arranque.
- En el bucle de créditos, START o A del mando 1 vuelven a la pantalla de título.
- Pantalla de fallo con el estado de cada hilo y el registro reciente. Aparece ante una excepción, un error fatal o un cuelgue.
- ISO con fechas fijas, tomadas de `SOURCE_DATE_EPOCH` o del último commit.

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
| `EXTRA_DEFINES` | Defines adicionales, por ejemplo `-DSMK64_PROF` (perfilador por muestreo) o `-DSMK64_DEV_FRAMEDUMP` (volcados de pantalla, con `DEV=1`) |

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

## Ejecutar

- **PCSX2** (con BIOS) y **Play!**: abrir la ISO de `compilaciones/`.
- **OPL** (sin probar en hardware): copiar la carpeta `compilaciones/disco/OPL/CD/` a la raíz del USB o del recurso SMB.
- **uLaunchELF** (sin probar en hardware): usar el ELF de `make MONOLITICO=1` (`build/ps2/monolitico/SLUS_999.99`), que hay que compilar. El `SLUS_999.99` normal busca `SMK64ROM.BIN` solo en `host:` y en el disco, no junto al ELF (`codigo/sistema/carga_rom.c`). Según el código, lanzado desde un USB sin disco debería detenerse con el error «falta SMK64ROM.BIN».
- **ELF suelto en un emulador con `host:`**: `SMK64ROM.BIN` tiene que estar en la carpeta que el emulador expone como `host:`.

`SLUS_999.99` y `SMK64ROM.BIN` deben salir de la misma compilación. El juego no detecta un `SMK64ROM.BIN` de otra compilación si es igual o más grande que el esperado (ver [Solución de problemas](#solución-de-problemas)).

## Controles

Asignación de `codigo/entrada/mandos.c`. Al conectar un mando, el port lo fija en modo DualShock (analógico).

| N64 | DualShock 2 |
|---|---|
| A | Cruz |
| B | Cuadrado |
| Z | L1 o L2 |
| R | R1 o R2 |
| L | Select |
| Start | Start |
| Stick | Stick izquierdo |
| Cruceta | Cruceta (también hace de stick si el stick izquierdo está en reposo) |
| C arriba | Triángulo o stick derecho hacia arriba |
| C abajo | Círculo o stick derecho hacia abajo |
| C izquierda / C derecha | Stick derecho hacia la izquierda / derecha |

Funciones propias del port (solo en el mando 1):

| Botón | Acción |
|---|---|
| R3 (sin L3) | Activa o desactiva los 60 FPS |
| L3 + R3 | Cambia la vista del panel de rendimiento (solo en compilaciones con panel) |
| START o A en el bucle de créditos | Vuelve a la pantalla de título |

El stick izquierdo tiene una zona muerta de 24 y se escala al recorrido de un stick de N64 (máximo 80). El stick derecho activa los botones C cuando se aleja más de 64 del centro.

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

### Guardado

La partida se guarda en la Memory Card de la ranura 1, en `/BASLUS-99999SMK64/`:

| Archivo | Contenido |
|---|---|
| `SMK64A.SAV`, `SMK64B.SAV` | Dos copias alternas: EEPROM y Controller Pak emulados, con número de generación y CRC32 |
| `icon.sys`, `SMK64.ICO` | Icono del navegador de la consola (`herramientas/crear_icono.py`) |

Al arrancar se carga la copia válida más reciente. Si la tarjeta no responde en 5 s, el juego sigue sin la partida y no guarda. Los archivos `SMK64.SAV` y `SMK64.TMP` de versiones anteriores se leen y se borran en el primer guardado.

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

## Idioma

El juego está en español, sin selección de idioma. La especificación, el plan, el glosario y la trazabilidad están en [`docs/traduccion/`](docs/traduccion/).

**Qué está en español:**

- **Textos:** menús, opciones, pausa, tiempos y resultados, fantasmas, mensajes de la Memory Card («RANURA 1», «COPIAR FANTASMAS» con un aviso honesto porque en PS2 no hay otra tarjeta desde la que copiar), intro de la batalla, ceremonia y créditos (la mitad japonesa de los créditos se conserva). Los botones se nombran como en el DualShock 2: CRUZ, CUADRADO, SELECT y R1.
- **Nombres de pista:** los oficiales de Nintendo en español (Pista Mario, Senda Arco Iris, Granja Mu-Mu…), con su fuente en el [glosario](docs/traduccion/glosario.md).
- **Fuente del menú:** 11 glifos nuevos (Á É Í Ó Ú Ñ Ü ¡ ¿ º ª), dibujados a partir de los originales; los ordinales se escriben «1.º».
- **Texturas con texto:** 55 texturas (títulos de menú, botones, copas, número de jugadores, los 20 títulos de pista, el cartel de la granja, TIEMPO y VUELTA en el HUD, puestos «1.º»…«8.º» y PULSA START) y los 48 cuadros de los carteles de Lakitu (¡ÚLTIMA!, VUELTA 2 y ¡REVÉS!). Salen de PNG versionados en `recursos/es/`, compuestos con letras de las propias texturas del juego.
- **Pantallas del port:** panel de rendimiento y página de audio (con tildes), nombres de fase, registro y guiones de prueba. La pantalla de fallo usa `scr_printf` de ps2sdk, que solo tiene ASCII: muestra el texto sin tildes («PARADA DE DIAGNOSTICO»), mientras el registro lo conserva completo.

**Qué no se traduce:** nombres de personaje, logotipos y carteles comerciales, 50cc/100cc/150cc, VS, onomatopeyas, las voces (son muestras de audio) y las texturas de la pantalla del Controller Pak, que el port no puede abrir. El detalle está en la [especificación](docs/traduccion/especificacion.md#22-excluido).

**Cómo se comprobó:**

- `make test`, sin el SDK de PS2: 26 pruebas y el tope de líneas en verde (ver [Pruebas](#pruebas)). La prueba de textos recorre todas las tablas con el decodificador del juego y mide cada texto por tinta contra la zona segura del televisor.
- CI en verde en la ejecución [36518116212](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/36518116212): pruebas en el PC, compilación para PS2 (release, `DEBUG=1`, `make test` e ISO) y el job `publicar` (release, `DEBUG=1`, `DEV=1`, pruebas e ISO), que generó la compilación versionada `dda9a5f`.

**Queda para el usuario:** el recorrido en PCSX2 con el guion `herramientas/guiones/recorrido_textos.txt` (`make DEV=1`, copiarlo como `smk64_input.txt` en la carpeta `host:` y sacar las capturas a mano en cada `nota`), las pantallas que el guion no recorre y una captura en TV para el sobrebarrido. La lista completa está en [`docs/traduccion/README.md`](docs/traduccion/README.md#pendiente).

El trabajo se repartió en estos roles:

| Rol | Alcance |
|---|---|
| INFRA | Compilación y pruebas: `make test` sin el SDK de PS2, conversión a EUC-JP sin `iconv`, tope de líneas y CI |
| FUENTE | Fuente del menú: tildes, ñ, ü, ¡ y ¿ |
| CADENAS | Textos de menús, mensajes y créditos |
| TEXTURAS | Texturas con texto: menús, títulos de pista, HUD y carteles de Lakitu |
| PORT | Pantallas propias del port: panel de rendimiento, pantalla de fallo y registro |
| PRUEBAS | Prueba en rojo antes de cada cambio |
| REVISIÓN | Revisión técnica y lingüística de cada bloque |
| INTEGRACIÓN | Integración y commit de publicación de los binarios |

## Contribuir

### 1. Rama

Crea la rama desde el último `origin/main` y verifica de dónde nace:

```bash
git fetch origin
git switch -c fix/mi-cambio origin/main
git reflog show fix/mi-cambio | tail -1           # «branch: Created from origin/main»
git rev-list --count origin/main..fix/mi-cambio   # 0: todavía sin commits propios
git rev-list --count fix/mi-cambio..origin/main   # 0: no le falta nada de main
```

Nombre: `tipo/tema`, en minúsculas y con guiones (por ejemplo, `fix/tilde-en-la-pausa`). La rama se borra después de integrarla.

Un cambio que toca textos o texturas en pantalla sigue además la [especificación de la traducción](docs/traduccion/especificacion.md) y el [glosario](docs/traduccion/glosario.md): primero se actualizan los textos esperados de `herramientas/pruebas/` y, si cambia un límite, una escala o un término, se registra en [`cambios.md`](docs/traduccion/cambios.md).

### 2. Prueba en rojo

1. Escribe la prueba en `herramientas/pruebas/` y añádela al objetivo `test` del `Makefile`.
2. Ejecuta `make test` y comprueba que falla (rojo) por el motivo esperado.
3. Haz el cambio y comprueba que `make test` pasa (verde).

Si el comportamiento ya existe y solo añades la prueba, demuestra que detecta el fallo con una mutación temporal del código. Después restaura el archivo y comprueba con `git diff --quiet -- <ruta>` que no queda rastro.

### 3. Commits

- Formato `tipo(dominio): descripción`, en español. Tipos: `feat`, `fix`, `refactor`, `test`, `build`, `ci` y `docs`. El dominio es el área que se toca (`menus`, `sistema`, `make`, `readme`…); los cambios de integración continua van sin dominio (`ci: descripción`). Ejemplo: `docs(readme): describir el flujo de contribución`.
- Un tema por commit.
- Un refactor no cambia el comportamiento y va en su propio commit, nunca junto a un cambio funcional.
- Agrega los archivos por ruta (`git add <ruta>`), nunca con `git add -A` ni `git add .`. Revisa `git status --short` antes de cada commit.
- `build/` y `compilaciones/` no entran en los commits de trabajo (ver [Binarios versionados](#binarios-versionados)).

### 4. Antes de pedir revisión

```bash
. herramientas/entorno.sh
make clean && make -j"$(nproc)"
make test
git checkout -- build compilaciones
git status --short   # solo deben aparecer tus cambios
```

Si el cambio afecta a `DEBUG=1` o `DEV=1`, compila también esas variantes.

### 5. Revisión

Otra persona revisa cada cambio; el autor nunca revisa el suyo. Cada hallazgo sigue este formato:

```text
[Alta|Media|Baja] Título
Archivo: ruta:línea
Riesgo: qué puede fallar
Recomendación: cómo corregirlo
```

No se integra un cambio con hallazgos Alta o Media abiertos.

### 6. Integración

Con la revisión aprobada, la rama se integra con un commit de merge explícito:

```bash
git switch main
git pull --ff-only
git merge --no-ff fix/mi-cambio
```

### Definition of Done

Un cambio está terminado cuando:

1. Compila: `make clean && make` termina sin errores.
2. `make test` pasa, sin regresiones.
3. La documentación está sincronizada: README y `docs/` describen el cambio.
4. El árbol está limpio: `git status --short` vacío, con `build/` y `compilaciones/` restaurados.
5. El responsable del proyecto confirma el cierre.

### Reglas de código

- Nombres en español y en `snake_case`. Los tipos van en `PascalCase` y las constantes en `MAYUSCULAS`.
- La API de libultra, el SDK de PS2 y los símbolos del enlazador conservan sus nombres originales.
- Las funciones y los datos sin identificar se llaman `funcion_<dirección>` y `dato_<dirección>`, con la dirección original de la N64.
- Comentarios cortos.
- Máximo 1000 líneas por archivo de código en `codigo/`, `incluir/` y `herramientas/`; los datos de `recursos/` (pistas y texturas) no cuentan. Si una parte crece, va a un archivo propio. Solo lo superan las tablas de datos y la cabecera externa que ya lo hacían: `codigo/datos/karts/kart_*.s`, `codigo/datos/otras_texturas.s`, `codigo/datos/texturas_fuentes.s`, `codigo/memoria/tablas_trigonometricas.c` e `incluir/libultra/PR/gbi.h`.

## Solución de problemas

| Síntoma | Causa y solución |
|---|---|
| `PS2SDK no definido: ejecuta '. herramientas/entorno.sh'` | El entorno no está cargado en esta terminal. Pasa con cualquier objetivo salvo `test`, `herramientas`, `es`, `hoja-es` y `clean`. Ejecuta `. herramientas/entorno.sh` (con `.`, no como programa) y repite |
| `entorno.sh: no hay toolchain de PS2 en ...` | No existe `$PS2DEV/ee/bin/mips64r5900el-ps2-elf-gcc`. Instala ps2dev o exporta `PS2DEV` con la ruta correcta |
| `git status` muestra cambios en `build/` o `compilaciones/` | Es lo esperado después de compilar o probar: están versionados. Restaura con `git checkout -- build compilaciones` |
| Al terminar `make` aparece una línea `rm ...` y faltan archivos en `build/ps2/recursos/` | GNU make 4.3 borra los intermedios de la ROM. La compilación es válida. Restaura con `git checkout -- build` o usa make 4.4 |
| En pantalla: «falta SMK64ROM.BIN: usa la ISO completa (o el ELF monolitico con uLaunchELF)» | El ELF no encontró `SMK64ROM.BIN` en `host:` ni en el disco, o el del disco es más pequeño de lo que espera el ELF (de otra compilación). La pantalla muestra el texto sin tildes; en el registro sale `ROM: no se encontró \SMK64ROM.BIN;1 en el disco ...` o `ROM: \SMK64ROM.BIN;1 mide X y debería medir Y`. Usa la ISO de `make iso` o el ELF de `make MONOLITICO=1` |
| En pantalla: «no se pudo leer SMK64ROM.BIN del disco» | Falló una lectura durante la carga, tras 8 reintentos: imagen o disco dañado. Por `host:` también aparece si el archivo es más corto de lo esperado. En el registro sale `ROM: no se pudo leer SMK64ROM.BIN (trozo N)`. Vuelve a crear la ISO con `make iso` |
| `error: <ruta>:<línea>:<columna>: '…' (U+XXXX) no existe en EUC-JP` | Un texto de los fuentes que se convierten (`JP_SRC` y `JP_PARTES` del Makefile) lleva un carácter que EUC-JP no tiene. La conversión la hace `herramientas/convertir_eucjp.py`, no `iconv`, y corta la compilación en ese punto. Cambia el carácter; si además no tiene glifo en la fuente del menú, `make test` lo señala en la prueba de textos |
| `make_iso: falta genisoimage (apt install genisoimage)` | Instala `genisoimage` (en Alpine, el paquete `cdrkit`) |
| `DEBUG_AUDIO=1 necesita DEBUG=1 o DEV=1` | Combina `DEBUG_AUDIO=1` con `DEBUG=1` o `DEV=1` |
| La partida no se guarda | Hace falta una Memory Card de PS2 formateada en la ranura 1. Con `DEBUG=1` o `DEV=1`, el registro muestra los mensajes `memory card:` |

Las últimas líneas del registro también aparecen en la pantalla de fallo, en cualquier compilación.

## Aviso legal

Proyecto de preservación sin afiliación con Nintendo ni con Sony. Mario Kart 64, Nintendo 64, PlayStation 2, DualShock y el resto de marcas citadas pertenecen a sus respectivos dueños.
