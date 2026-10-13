# Mario Kart 64 para PlayStation 2, en español

Alexis Barrera ([Alexis-VsCode](https://github.com/Alexis-VsCode)) · fork del port a PS2 de [anthoo582](https://github.com/anthoo582/mario-kart-64-ps2) · versión 1.2.1, 2026-10-11

[![Compilación y pruebas](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/workflows/compilacion.yml/badge.svg)](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/workflows/compilacion.yml)

**Resumen.** Llevé Mario Kart 64 a mi PlayStation 2 con todo el texto que ve el jugador en español, sobre la descompilación comunitaria del juego y el port de anthoo582.
Es un proyecto personal, sin ánimo de lucro: publico la ISO y el ELF para que la comunidad pueda probarlos, y quien juegue debe tener el juego original.
Cada cambio parte de una especificación que apruebo antes de tocar el código, lo pruebo en el PC y en un emulador desde la CI, y queda registrado con su revisión.
Lo que no pude comprobar, como una PS2 real o una TV, lo declaro aparte.

## Contenido

1. [Resumen y propósito](#1-resumen-y-propósito)
2. [Qué incluye y descarga verificable](#2-qué-incluye-y-descarga-verificable)
3. [Cómo jugar](#3-cómo-jugar)
4. [Qué comprobé y cómo](#4-qué-comprobé-y-cómo)
5. [Patrones y prácticas que apliqué](#5-patrones-y-prácticas-que-apliqué)
6. [Mi trayectoria en este proyecto](#6-mi-trayectoria-en-este-proyecto)
7. [Créditos, aviso legal y licencia](#7-créditos-aviso-legal-y-licencia)

## 1. Resumen y propósito

Mario Kart 64 es el juego de mi infancia. Quise mejorarlo, traducirlo por completo y jugarlo en mi PS2, y para eso me apoyé en la descompilación del juego y en el port de anthoo582.

- **Sin ánimo de lucro.** No cobro nada y no hay donaciones, publicidad ni patrocinio.
- **Para la comunidad.** Publico la ISO y el ELF, como hace el repositorio original, para que cualquiera pueda probarlos.
- **Con el juego original.** Para jugar debes poseer una copia original de Mario Kart 64.
- **Sin afiliación.** No tengo relación con Nintendo ni con Sony. Si el titular de los derechos me pide retirar el proyecto, lo retiro.
- **Mejoras del port.** Bajé la zona muerta del stick de 24 a 8 ([`dcbe656e`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/dcbe656e)), la región de la consola sale de `rom0:ROMVER` ([`3b11daa5`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/3b11daa5)) y las opciones se guardan en `SMK64CFG.DAT` ([`8c022b34`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/8c022b34)).
- **Pieza de portafolio.** También es una muestra de mi trabajo como desarrollador e ingeniero de observabilidad: cómo especifico, pruebo, mido y documento un cambio en un código que nadie diseñó para leerse. El [caso de estudio](docs/caso-de-estudio.md) lo cuenta, y [CC-30](docs/traduccion/cambios.md) y [CC-32](docs/traduccion/cambios.md) registran las decisiones de portafolio y de propósito sin lucro.

## 2. Qué incluye y descarga verificable

El repositorio trae el juego descompilado, una capa de compatibilidad que sustituye el hardware de la Nintendo 64 por el de la PS2 y los recursos ya extraídos (texturas, pistas, karts, música y efectos).

- Las 20 pistas (16 de carrera y 4 de batalla), los 8 personajes y los modos Gran Premio, Contrarreloj, VS y Batalla, de 1 a 4 jugadores con multitap.
- Textos, nombres de pista oficiales, texturas con texto, HUD y carteles en español, incluidos BIENVENIDOS, YA, los emblemas 1J a 4J y PASO A NIVEL. Clasifiqué 1229 texturas en el manifiesto `recursos/es/texturas.tsv` ([CC-29](docs/traduccion/cambios.md), commits [`a6fa679e`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/a6fa679e) y [`4216877e`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/4216877e)). La fuente con 11 glifos nuevos está en [creditos.md](docs/manual/creditos.md).
- **Menú CONFIGURACIÓN Y TRUCOS**, en OPCIONES, guardado en `SMK64CFG.DAT` de la Memory Card (versión 1.2.0, [CC-18 a CC-25](docs/traduccion/cambios.md); [acta de la 1.2.0](docs/traduccion/revisiones/2026-10-11-version-1.2.0.md)):
  - ANTIPARPADEO (desactivado por defecto) y POSICIÓN X/Y de la imagen;
  - FORMATO NORMAL, CON BANDAS o PANORÁMICO; CON BANDAS es el valor por defecto si la PS2 está configurada en 16:9;
  - trucos DESBLOQUEAR TODO, OBJETO, 200CC (solo Gran Premio y VS en 150cc, y puntúa como 150cc) y RIVALES SIN VENTAJA. Los récords se guardan aunque haya trucos activos; el menú lo advierte.
- Gráficos: un intérprete de listas de dibujo F3DEX, con el combinador de color y la TMEM de la N64, que produce paquetes para el GS. Vídeo NTSC entrelazado a 640×448 y 60 Hz, también en consolas PAL, que necesitan una TV que acepte 60 Hz ([detalle](docs/manual/usuario.md#consolas-pal-y-ntsc)).
- Audio original: las muestras de la ROM se mezclan con la misma aritmética que la N64 y salen a 48 kHz por `audsrv`.
- Modo 60 FPS durante la carrera, activo por defecto y conmutable con R3; la lógica del juego sigue a 30 Hz.
- Partidas guardadas en la Memory Card de la ranura 1, en dos copias alternas con CRC32, sin pisar la partida más nueva de una tarjeta cambiada en caliente (versión 1.1.0, [CC-13](docs/traduccion/cambios.md), commits [`b989feca`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/b989feca) y [`e4937a28`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/e4937a28); [acta de la 1.1.0](docs/traduccion/revisiones/2026-10-11-version-1.1.0.md)).
- Arranque desde OPL sin reiniciar el IOP.
- Pantalla de fallo con el estado de cada hilo, el registro reciente y tildes.

### Descarga y verificación

Como en el repositorio original, publico la ISO y el ELF.

- **Versión 1.2.1:** [Releases](https://github.com/Alexis-VsCode/mario-kart-64-ps2/releases/tag/v1.2.1), con la ISO, el ELF monolítico, `SHA256SUMS` y las [notas de la versión](docs/versiones/v1.2.1.md).
- **ISO directa:** [`SLUS_999.99.SuperMarioKart64.iso`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/releases/download/v1.2.1/SLUS_999.99.SuperMarioKart64.iso).
- **ELF monolítico, para uLaunchELF desde USB:** [`SLUS_999.99.monolitico.elf`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/releases/download/v1.2.1/SLUS_999.99.monolitico.elf). Lleva la ROM dentro: no necesita `SMK64ROM.BIN`.
- **Alternativa:** la ISO versionada en `main`, [`compilaciones/SLUS_999.99.SuperMarioKart64.iso`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/raw/main/compilaciones/SLUS_999.99.SuperMarioKart64.iso).

| Archivo | Tamaño | SHA-256 |
|---|---|---|
| `SLUS_999.99.SuperMarioKart64.iso` | 13 387 776 bytes | `3b4321ce86050f1a3bceb5a381ca354cecca1853a784069e56111a232df5eceb` |
| `SLUS_999.99.monolitico.elf` | En la lista de archivos de la Release | Su línea de `SHA256SUMS` en la Release |

*Tabla 1. Archivos de la versión 1.2.1, publicados con el commit [`d3c27566`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/d3c27566) y la ejecución de la CI [38181807319](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38181807319).*

Con el archivo y `SHA256SUMS` en la misma carpeta:

```sh
sha256sum -c --ignore-missing SHA256SUMS
```

La salida esperada es `SLUS_999.99.SuperMarioKart64.iso: OK` (o `SLUS_999.99.monolitico.elf: OK`). En Windows, con PowerShell: `Get-FileHash <archivo> -Algorithm SHA256`. Si la suma no coincide, la descarga está dañada: vuelve a descargarla. El job que publica la Release compila el ELF, por eso su suma solo está en `SHA256SUMS`.

### Estructura del repositorio

| Ruta | Contenido |
|---|---|
| `codigo/` | Código del juego y del port, por dominio: audio, carrera, ceremonia, datos, depuración, entrada, gráficos, memoria, menús y sistema |
| `incluir/` | Cabeceras, incluida la capa `libultra` |
| `recursos/` | Texturas, pistas, sonido y los recursos en español (`recursos/es/`) |
| `herramientas/` | Conversores, compositor de texturas, pruebas, CI y [guion del emulador](herramientas/emulador/) |
| `compilacion/` | Scripts del enlazador |
| `build/` y `compilaciones/` | Binarios versionados y la ISO; solo cambian en el commit de publicación |
| `docs/` | [Manual](docs/manual/README.md), [traducción](docs/traduccion/README.md), [notas de versión](docs/versiones/) y [caso de estudio](docs/caso-de-estudio.md) |

*Tabla 2. Carpetas principales.*

## 3. Cómo jugar

| Dónde | Cómo |
|---|---|
| PCSX2 (con BIOS de PS2) | Abrir la ISO directamente |
| Play! | Abrir la ISO directamente |
| OPL | Copiar la ISO, con el mismo nombre, en la carpeta `CD/` del USB o del recurso SMB |
| uLaunchELF | Copiar `SLUS_999.99.monolitico.elf` a un USB y abrirlo desde el navegador de archivos |

*Tabla 3. Formas de ejecutar el juego. No probé OPL ni uLaunchELF en hardware (sección 4).*

Para guardar la partida y las opciones hace falta una Memory Card de PS2 formateada en la ranura 1. Controles, multitap, 60 FPS, consolas PAL y solución de problemas están en el [manual de usuario](docs/manual/usuario.md); el índice completo, en [docs/manual/](docs/manual/README.md). Qué cambia respecto a la 1.2.0: [CHANGELOG.md](CHANGELOG.md#121---2026-10-11).

### Si quieres compilarlo

Con el toolchain de ps2dev instalado ([requisitos e instalación](docs/manual/tecnico.md#requisitos)):

```bash
. herramientas/entorno.sh
make -j"$(nproc)"
make iso                      # compilaciones/SLUS_999.99.SuperMarioKart64.iso
make test                     # pruebas en el PC; no necesita el SDK
git checkout -- build compilaciones && git clean -fdq -- build compilaciones
```

`build/` y `compilaciones/` están versionados: compilar y probar los modifica, y los restauro como en la última línea. Objetivos, variables y salida: [manual técnico](docs/manual/tecnico.md#compilar).

## 4. Qué comprobé y cómo

Cada afirmación lleva el método con el que la comprobé y el enlace a la evidencia. El estado es el de la versión 1.2.1, del 2026-10-11; el avance y lo pendiente están en [docs/traduccion/README.md](docs/traduccion/README.md).

| Afirmación | Método | Evidencia |
|---|---|---|
| Textos, glifos, texturas, Memory Card, stick, región, registros de vídeo, vista panorámica, menú y trucos pasan sus pruebas | `PS2SDK= make test` en el PC, sin el SDK de PS2, más el comprobador del tope de líneas. En la 1.2.0 dio 0 fallos en las 44 pruebas que imprimen su resumen y 0 archivos por encima del tope | [Trazabilidad, F10](docs/traduccion/trazabilidad.md) y [manual técnico](docs/manual/tecnico.md#pruebas) |
| Compila para PS2 (release, `DEBUG=1`, `DEV=1`), respeta el tope de la ROM y compila de forma incremental | CI de GitHub, en el job `compilar-ps2` | Ejecuciones [38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616) (1.2.0) y [38181807319](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38181807319) (publicación de la 1.2.1) |
| El juego arranca, detecta la región PAL con un ROMVER sintético, escribe `vídeo: PMODE 8046` y muestra el título, el menú, la configuración y la carrera | Job «Guion en el emulador (Play!)», con Play! 0.72 sin BIOS y un margen del 0,1 % ([CC-26](docs/traduccion/cambios.md), [CC-31](docs/traduccion/cambios.md)) | Commit [`2c3a8b29`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/2c3a8b29), capturas de [referencia](herramientas/emulador/referencias/) y la ejecución [38181807319](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38181807319) |
| La comparación de capturas detecta un bloque de 32×16 cambiado | Prueba en rojo, mutación y restauración, con tolerancia por defecto de 0,001 | Commits [`1bac15d9`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/1bac15d9) y [`632050ac`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/632050ac); [acta de la 1.2.1](docs/traduccion/revisiones/2026-10-11-version-1.2.1.md) |
| Ninguna partida más nueva se pisa al cambiar la tarjeta | Arnés del PC para `memory_card.c` con libmc simulada | Commits [`b989feca`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/b989feca) y [`36796171`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/36796171); [acta de la 1.1.0](docs/traduccion/revisiones/2026-10-11-version-1.1.0.md) |
| Cada fase la revisó una parte distinta de la que escribió el cambio | Acta de revisión por versión, con hallazgos y su estado | [Actas](docs/traduccion/revisiones/) y [deuda técnica](docs/traduccion/deuda.md) |

*Tabla 4. Qué comprobé y cómo.*

Esto es lo que no pude comprobar, o comprobé solo en parte:

| Qué | Por qué | Estado |
|---|---|---|
| Tacto del stick, multitap, cambio de Memory Card en marcha y rendimiento en PANORÁMICO | Necesitan hardware real y una TV | Sin verificar |
| Antiparpadeo, bandas y posición de la imagen | Las capturas leen la VRAM antes del PCRTC; solo comprobé los valores de los registros | Parcial |
| Lectura de ROMVER bajo OPL sin reinicio del IOP | Solo comprobé la ruta con reinicio y un ROMVER sintético | Parcial |
| OPL y uLaunchELF | Necesitan hardware real | Sin verificar |

*Tabla 5. Límites declarados.*

El port original declara pruebas en **PCSX2** (con BIOS) y en **Play!**. Las limitaciones conocidas están en el [manual de usuario](docs/manual/usuario.md#limitaciones-conocidas) y los límites declarados, en la [especificación](docs/traduccion/especificacion.md#9-límites-declarados).

## 5. Patrones y prácticas que apliqué

| Patrón | Dónde se ve en el repositorio |
|---|---|
| Especificación antes del código (SDD) | Cada cambio de comportamiento empieza como un cambio de especificación (CC) que apruebo antes de tocar el código, con requisitos verificables: [cambios.md](docs/traduccion/cambios.md) y [especificación](docs/traduccion/especificacion.md) |
| Pruebas en rojo con mutación (TDD) | La prueba se ve en rojo antes del cambio y detecta una mutación del código, que luego restauro. Ejemplo: [`1bac15d9`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/1bac15d9) exige que un bloque de 32×16 cambiado falle con la tolerancia por defecto y [`632050ac`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/632050ac) la baja a 0,001. El ciclo está en [CONTRIBUTING.md](CONTRIBUTING.md#ciclo-de-un-cambio) |
| Funciones puras en cabeceras de `incluir/` | `cruceta_manda_stick` en [`incluir/entrada/eje_palanca.h`](incluir/entrada/eje_palanca.h) ([`bd70c399`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/bd70c399)) y la lógica del menú de configuración en [`incluir/menus/menu_configuracion.h`](incluir/menus/menu_configuracion.h) ([`7c5439e4`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/7c5439e4)), probadas en el PC sin el SDK |
| Autor distinto del revisor | Cada fase la revisa otra parte por separado y deja un [acta](docs/traduccion/revisiones/); lo que la revisión independiente encuentra y no corrijo pasa a la [deuda técnica](docs/traduccion/deuda.md) con un identificador |
| CI con emulador | El job «Guion en el emulador (Play!)» arranca el ELF y compara capturas con referencias ([`2c3a8b29`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/2c3a8b29), [herramientas del emulador](herramientas/emulador/)) |
| Publicación reproducible con SHA-256 | La CI compila la ISO con una imagen de ps2dev fijada por digest, la versiono en un commit de publicación aparte ([`d3c27566`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/d3c27566)) y publica `SHA256SUMS` junto a ella |
| Trazabilidad CC → commit → prueba | Cada requisito enlaza con su prueba y sus commits en la [trazabilidad](docs/traduccion/trazabilidad.md). Reglas, ramas y Definition of Done: [CONTRIBUTING.md](CONTRIBUTING.md) |

*Tabla 6. Patrones y dónde se ven.*

## 6. Mi trayectoria en este proyecto

Soy desarrollador e ingeniero de observabilidad, y este proyecto me dejó aplicar mi oficio a un código ajeno que no estaba pensado para leerse. Lo que hago en mi trabajo, ver qué hace un sistema por lo que escribe y por lo que mide, lo llevé al juego:

- **Registros del juego.** Trabajo con el registro que trae el port y lo amplié: el registro dice qué generación de la Memory Card escribe el juego ([`c69d9ef4`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/c69d9ef4)) y la pantalla de fallo usa los glifos CP437 con tildes ([`8e311363`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/8e311363)). Cómo leerlo: [manual técnico](docs/manual/tecnico.md#depuración).
- **Arranque y audio en la CI.** El job del emulador lee el registro del arranque y comprueba la región y el vídeo. Después de la 1.2.1 hice que el comprobador exija también el audio listo y rechace los avisos de audsrv e IOP ([`e3855654`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/e3855654), [`325d2b44`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/325d2b44)).
- **Medidor de rendimiento.** Con `DEBUG=1`, L3 y R3 abren el panel del port con los FPS, los milisegundos por cuadro, el reparto de CPU y los cortes de audio. Lo traduje con tildes. Medir con él el rendimiento en PANORÁMICO en una consola real sigue entre mis límites declarados ([panel de rendimiento](docs/manual/tecnico.md#panel-de-rendimiento-l3--r3)).
- **Capturas comparadas con tolerancia.** Comparo las capturas del emulador con referencias y entre sí. Bajé la tolerancia de 0,02 a 0,001 ([`632050ac`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/632050ac)) y la comparación más estricta encontró dos defectos visibles: los valores tenues del menú de configuración y el ordinal «8º.» ([notas de la 1.2.1](docs/versiones/v1.2.1.md)).

El [caso de estudio](docs/caso-de-estudio.md) cuenta el resto: la motivación, los retos y las decisiones.

## 7. Créditos, aviso legal y licencia

### Créditos

- **Port a PS2:** anthoo582 ([anthoo582/mario-kart-64-ps2](https://github.com/anthoo582/mario-kart-64-ps2)), del que este repositorio es un fork. Su port trae el intérprete gráfico, el audio, los hilos y el guardado en la Memory Card ([detalle](docs/manual/creditos.md)).
- **Descompilación:** el proyecto comunitario de Mario Kart 64 ([n64decomp/mk64](https://github.com/n64decomp/mk64)), sobre el que anthoo582 construyó el port.
- **Localización, mejoras y verificación de este fork:** Alexis Barrera.
- **Toolchain:** [ps2dev](https://github.com/ps2dev/ps2dev) (ps2sdk y gsKit).
- **Emulador de la CI:** [Play!](https://github.com/jpd002/Play-).

El detalle por áreas está en [docs/manual/creditos.md](docs/manual/creditos.md).

### Aviso legal

- Proyecto **sin fines de lucro**, educativo, de preservación y de apoyo a la comunidad. No vendo nada ni cobro por nada de lo que contiene; no hay donaciones, publicidad ni patrocinio.
- **Sin afiliación** con Nintendo ni con Sony, que no lo patrocinan ni lo respaldan. Mario Kart 64, Nintendo 64, PlayStation 2, DualShock y el resto de marcas citadas pertenecen a sus respectivos dueños.
- Para jugar, debes poseer una copia original de Mario Kart 64.
- Si eres titular de derechos y quieres que retire algún contenido, abre un [issue](https://github.com/Alexis-VsCode/mario-kart-64-ps2/issues) y lo retiraré.

### Licencia

Publico mis aportes a este fork bajo la licencia MIT, a nombre de Alexis Barrera ([LICENSE](LICENSE), commit [`abc844ff`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/abc844ff)). La licencia no cubre el juego ni sus recursos, la descompilación ni el código del repositorio original, que no declaran licencia.

## Documentación

| Documento | Contenido |
|---|---|
| [docs/manual/](docs/manual/README.md) | Índice del manual |
| [Manual de usuario](docs/manual/usuario.md) | Requisitos, descarga, PCSX2, Play!, OPL, uLaunchELF, controles, multitap, 60 FPS, Memory Card, idioma, limitaciones y solución de problemas |
| [Manual técnico](docs/manual/tecnico.md) | Arquitectura, compilación, pruebas, depuración, CI y publicación, y cómo traer las actualizaciones del original |
| [Créditos](docs/manual/creditos.md) | Autoría por áreas |
| [Estilo](docs/manual/estilo.md) | La voz de la documentación y la estructura del informe |
| [LICENSE](LICENSE) | Licencia MIT de los aportes del fork y lo que excluye |
| [CONTRIBUTING.md](CONTRIBUTING.md) | Definition of Done, reglas, ramas, commits y revisión |
| [CHANGELOG.md](CHANGELOG.md) | Cambios por versión |
| [Notas de la versión 1.2.1](docs/versiones/v1.2.1.md) | Cuerpo de la Release actual; las anteriores: [v1.2.0.md](docs/versiones/v1.2.0.md), [v1.1.0.md](docs/versiones/v1.1.0.md) y [v1.0.0.md](docs/versiones/v1.0.0.md) |
| [Caso de estudio](docs/caso-de-estudio.md) | Motivación, retos, decisiones y proceso |
| [docs/traduccion/](docs/traduccion/README.md) | Localización: estado, especificación, plan, glosario, trazabilidad, cambios, actas de revisión y deuda técnica |
