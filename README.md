# Mario Kart 64 para PlayStation 2, en español

Alexis Barrera ([Alexis-VsCode](https://github.com/Alexis-VsCode)) · fork del port a PS2 de [anthoo582](https://github.com/anthoo582/mario-kart-64-ps2) · versión 1.2.1, 2026-10-11

[![Compilación y pruebas](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/workflows/compilacion.yml/badge.svg)](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/workflows/compilacion.yml)

**Resumen.** Port de Mario Kart 64 a PlayStation 2 con todo el texto que ve el jugador en español, hecho sobre la descompilación comunitaria del juego.
Es un proyecto personal, sin ánimo de lucro: la ISO y el ELF se publican para que la comunidad pueda probarlos, y quien juegue debe tener el juego original.
Cada cambio parte de una especificación aprobada, se prueba en el PC y en un emulador desde la CI, y queda registrado con su revisión.
Lo que no se pudo comprobar, como una PS2 real o una TV, se declara aparte.

## Contenido

1. [Propósito](#1-propósito)
2. [Qué incluye](#2-qué-incluye)
3. [Descarga y verificación](#3-descarga-y-verificación)
4. [Cómo jugar](#4-cómo-jugar)
5. [Estado y verificación](#5-estado-y-verificación)
6. [Estructura del repositorio](#6-estructura-del-repositorio)
7. [Proceso y calidad](#7-proceso-y-calidad)
8. [Autoría](#8-autoría)
9. [Créditos](#9-créditos)
10. [Aviso legal](#10-aviso-legal)
11. [Licencia](#11-licencia)

## 1. Propósito

Mario Kart 64 es el juego de la infancia de Alexis Barrera. Quiso mejorarlo, traducirlo por completo y jugarlo en su PS2, aprovechando la descompilación del juego y el port de anthoo582.

- **Sin ánimo de lucro.** No se cobra por nada, y no hay donaciones, publicidad ni patrocinio.
- **Para la comunidad.** Se publican la ISO y el ELF, como hace el repositorio original, para que cualquiera pueda probarlos.
- **Con el juego original.** Quien juegue debe poseer una copia original de Mario Kart 64.
- **Sin afiliación.** No hay relación con Nintendo ni con Sony. Si el titular de los derechos pide retirar el proyecto, se retira.
- **Pieza de portafolio.** Es también una muestra del trabajo de su autor como desarrollador e ingeniero de observabilidad: cómo se especifica, se prueba, se mide y se documenta un cambio en un código que nadie diseñó para leerse. El [caso de estudio](docs/caso-de-estudio.md) lo cuenta.[^1]

## 2. Qué incluye

El repositorio trae el juego descompilado, una capa de compatibilidad que sustituye el hardware de la Nintendo 64 por el de la PS2 y los recursos ya extraídos (texturas, pistas, karts, música y efectos).

- Las 20 pistas (16 de carrera y 4 de batalla), los 8 personajes y los modos Gran Premio, Contrarreloj, VS y Batalla, de 1 a 4 jugadores con multitap.
- Textos, nombres de pista oficiales, texturas con texto, HUD y carteles en español, incluidos BIENVENIDOS, YA, los emblemas 1J a 4J y PASO A NIVEL. El manifiesto clasifica 1229 texturas.[^2]
- **Menú CONFIGURACIÓN Y TRUCOS**, en OPCIONES, guardado en `SMK64CFG.DAT` de la Memory Card:
  - ANTIPARPADEO (desactivado por defecto) y POSICIÓN X/Y de la imagen;
  - FORMATO NORMAL, CON BANDAS o PANORÁMICO; CON BANDAS es el valor por defecto si la PS2 está configurada en 16:9;
  - trucos DESBLOQUEAR TODO, OBJETO, 200CC (solo Gran Premio y VS en 150cc, y puntúa como 150cc) y RIVALES SIN VENTAJA. Los récords se guardan aunque haya trucos activos; el menú lo advierte.[^3]
- Gráficos: un intérprete de listas de dibujo F3DEX, con el combinador de color y la TMEM de la N64, que produce paquetes para el GS. Vídeo NTSC entrelazado a 640×448 y 60 Hz, también en consolas PAL, que necesitan una TV que acepte 60 Hz ([detalle](docs/manual/usuario.md#consolas-pal-y-ntsc)).
- Audio original: las muestras de la ROM se mezclan con la misma aritmética que la N64 y salen a 48 kHz por `audsrv`.
- Modo 60 FPS durante la carrera, activo por defecto y conmutable con R3; la lógica del juego sigue a 30 Hz.
- Partidas guardadas en la Memory Card de la ranura 1, en dos copias alternas con CRC32, sin pisar la partida más nueva de una tarjeta cambiada en caliente.[^4]
- Arranque desde OPL sin reiniciar el IOP.
- Pantalla de fallo con el estado de cada hilo, el registro reciente y tildes.

## 3. Descarga y verificación

Como en el repositorio original, se publican la ISO y el ELF.

- **Última versión:** [Releases](https://github.com/Alexis-VsCode/mario-kart-64-ps2/releases/latest), con la ISO, el ELF monolítico, `SHA256SUMS` y las [notas de la versión](docs/versiones/v1.2.1.md).
- **ISO directa:** [`SLUS_999.99.SuperMarioKart64.iso`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/releases/latest/download/SLUS_999.99.SuperMarioKart64.iso).
- **ELF monolítico, para uLaunchELF desde USB:** [`SLUS_999.99.monolitico.elf`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/releases/latest/download/SLUS_999.99.monolitico.elf). Lleva la ROM dentro: no necesita `SMK64ROM.BIN`.
- **Alternativa:** la ISO versionada en `main`, [`compilaciones/SLUS_999.99.SuperMarioKart64.iso`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/raw/main/compilaciones/SLUS_999.99.SuperMarioKart64.iso).

| Archivo | Tamaño | SHA-256 |
|---|---|---|
| `SLUS_999.99.SuperMarioKart64.iso` | 13 387 776 bytes | `3b4321ce86050f1a3bceb5a381ca354cecca1853a784069e56111a232df5eceb` |
| `SLUS_999.99.monolitico.elf` | En la lista de archivos de la Release | Su línea de `SHA256SUMS` en la Release |

*Tabla 1. Archivos de la versión 1.2.1.*[^5]

Con el archivo y `SHA256SUMS` en la misma carpeta:

```sh
sha256sum -c --ignore-missing SHA256SUMS
```

La salida esperada es `SLUS_999.99.SuperMarioKart64.iso: OK` (o `SLUS_999.99.monolitico.elf: OK`). En Windows, con PowerShell: `Get-FileHash <archivo> -Algorithm SHA256`. Si la suma no coincide, la descarga está dañada: vuelve a descargarla. El ELF se compila en el mismo job que publica la Release, por eso su suma solo está en `SHA256SUMS`.

## 4. Cómo jugar

| Dónde | Cómo |
|---|---|
| PCSX2 (con BIOS de PS2) | Abrir la ISO directamente |
| Play! | Abrir la ISO directamente |
| OPL | Copiar la ISO, con el mismo nombre, en la carpeta `CD/` del USB o del recurso SMB |
| uLaunchELF | Copiar `SLUS_999.99.monolitico.elf` a un USB y abrirlo desde el navegador de archivos |

*Tabla 2. Formas de ejecutar el juego. OPL y uLaunchELF no se han probado en hardware (sección 5).*

Para guardar la partida y las opciones hace falta una Memory Card de PS2 formateada en la ranura 1. Controles, multitap, 60 FPS, consolas PAL y solución de problemas están en el [manual de usuario](docs/manual/usuario.md); el índice completo, en [docs/manual/](docs/manual/README.md).

## 5. Estado y verificación

Versión 1.2.1, del 2026-10-11. Qué cambia respecto a la 1.2.0: [CHANGELOG.md](CHANGELOG.md#121---2026-10-11). El avance y lo pendiente están en [docs/traduccion/README.md](docs/traduccion/README.md).

| Qué | Cómo se verificó | Estado |
|---|---|---|
| Textos, glifos, texturas, Memory Card, stick, región, registros de vídeo, vista panorámica, menú y trucos | `make test` en el PC, sin el SDK de PS2, más el comprobador del tope de líneas | 0 fallos[^6] |
| Compilación para PS2 (release, `DEBUG=1`, `DEV=1`), tope de la ROM, compilación incremental | CI de GitHub | En verde[^7] |
| Arranque, región PAL con ROMVER sintético, `vídeo: PMODE 8046` y capturas del título, el menú, la configuración y la carrera | Job «Guion en el emulador (Play!)», con Play! 0.72 sin BIOS y margen del 0,1 % | En verde[^8] |
| Tacto del stick, multitap, cambio de Memory Card en marcha, rendimiento en PANORÁMICO | Hardware real y TV | Sin verificar |
| Antiparpadeo, bandas y posición de la imagen | Solo por valores de registro: las capturas leen la VRAM antes del PCRTC | Parcial |
| Lectura de ROMVER bajo OPL sin reinicio del IOP | Solo la ruta con reinicio y un ROMVER sintético | Parcial |
| OPL y uLaunchELF | Hardware real | Sin verificar |

*Tabla 3. Qué se verificó y qué no.*

El port original declara pruebas en **PCSX2** (con BIOS) y en **Play!**. Las limitaciones conocidas están en el [manual de usuario](docs/manual/usuario.md#limitaciones-conocidas) y los límites declarados, en la [especificación](docs/traduccion/especificacion.md#9-límites-declarados).

## 6. Estructura del repositorio

| Ruta | Contenido |
|---|---|
| `codigo/` | Código del juego y del port, por dominio: audio, carrera, ceremonia, datos, depuración, entrada, gráficos, memoria, menús y sistema |
| `incluir/` | Cabeceras, incluida la capa `libultra` |
| `recursos/` | Texturas, pistas, sonido y los recursos en español (`recursos/es/`) |
| `herramientas/` | Conversores, compositor de texturas, pruebas, CI y [guion del emulador](herramientas/emulador/) |
| `compilacion/` | Scripts del enlazador |
| `build/` y `compilaciones/` | Binarios versionados y la ISO; solo cambian en el commit de publicación |
| `docs/` | [Manual](docs/manual/README.md), [traducción](docs/traduccion/README.md), [notas de versión](docs/versiones/) y [caso de estudio](docs/caso-de-estudio.md) |

*Tabla 4. Carpetas principales.*

Con el toolchain de ps2dev instalado ([requisitos e instalación](docs/manual/tecnico.md#requisitos)):

```bash
. herramientas/entorno.sh
make -j"$(nproc)"
make iso                      # compilaciones/SLUS_999.99.SuperMarioKart64.iso
make test                     # pruebas en el PC; no necesita el SDK
git checkout -- build compilaciones && git clean -fdq -- build compilaciones
```

`build/` y `compilaciones/` están versionados: compilar y probar los modifica, y se restauran como en la última línea. Objetivos, variables y salida: [manual técnico](docs/manual/tecnico.md#compilar).

## 7. Proceso y calidad

- **Especificación primero.** Cada cambio de comportamiento empieza como un cambio de especificación (CC) aprobado, con requisitos verificables, en [cambios.md](docs/traduccion/cambios.md).
- **Pruebas con mutaciones.** Cuando se puede probar en el PC, la prueba se ve en rojo antes del cambio y se demuestra que detecta una mutación del código, que luego se restaura. Ejemplo: `1bac15d9` exige que un bloque de 32×16 cambiado falle con la tolerancia por defecto y `632050ac` la baja a 0,001.[^9]
- **Autor distinto del revisor.** Cada fase se revisa por separado y deja un [acta](docs/traduccion/revisiones/); lo que la revisión encuentra y no se arregla pasa a la [deuda técnica](docs/traduccion/deuda.md) con un identificador.
- **Trazabilidad.** Cada requisito se enlaza con su prueba y sus commits en la [trazabilidad](docs/traduccion/trazabilidad.md). Reglas, ramas y Definition of Done: [CONTRIBUTING.md](CONTRIBUTING.md).
- **Publicación reproducible.** La ISO se compila en la CI con una imagen de ps2dev fijada y se versiona en un commit de publicación aparte.[^5]

## 8. Autoría

Soy Alexis Barrera, desarrollador e ingeniero de observabilidad, y mantengo este fork. Mi trabajo en este repositorio, con la evidencia de cada punto:

- **Localización completa al español:** textos, 20 nombres de pista, glifos nuevos en la fuente (Á É Í Ó Ú Ñ Ü ¡ ¿ º ª), texturas reconstruidas y traducidas, y el manifiesto de texturas.[^2] [Créditos por áreas](docs/manual/creditos.md).
- **Mejoras del port:** Memory Card sin pérdida de partidas (CC-13), zona muerta del stick de 24 a 8 (`dcbe656e`), región de la consola desde ROMVER (`3b11daa5`), menú CONFIGURACIÓN Y TRUCOS (`7c5439e4`) y opciones en `SMK64CFG.DAT` (`8c022b34`).[^3]
- **Verificación:** las pruebas del PC, la CI y el arranque automático en Play!, descritos en la sección 5.
- **Proceso:** cada cambio parte de un cambio de especificación aprobado, una prueba en rojo y una revisión con acta (sección 7).

Evidencia: [cambios de especificación](docs/traduccion/cambios.md) y su [trazabilidad](docs/traduccion/trazabilidad.md); [actas de revisión](docs/traduccion/revisiones/); [deuda técnica](docs/traduccion/deuda.md); [ejecuciones de la CI](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions) y [herramientas del emulador](herramientas/emulador/); [Releases](https://github.com/Alexis-VsCode/mario-kart-64-ps2/releases) con sus notas en [docs/versiones/](docs/versiones/).

## 9. Créditos

- **Port a PS2:** anthoo582 ([anthoo582/mario-kart-64-ps2](https://github.com/anthoo582/mario-kart-64-ps2)), del que este repositorio es un fork. Su port trae el intérprete gráfico, el audio, los hilos y el guardado en la Memory Card.[^10]
- **Descompilación:** el proyecto comunitario de Mario Kart 64 ([n64decomp/mk64](https://github.com/n64decomp/mk64)), sobre el que se construyó el port.
- **Localización, mejoras y verificación de este fork:** Alexis Barrera.
- **Toolchain:** [ps2dev](https://github.com/ps2dev/ps2dev) (ps2sdk y gsKit).
- **Emulador de la CI:** [Play!](https://github.com/jpd002/Play-).

El detalle por áreas está en [docs/manual/creditos.md](docs/manual/creditos.md).

## 10. Aviso legal

- Proyecto **sin fines de lucro**, educativo, de preservación y de apoyo a la comunidad. No se vende ni se cobra por nada de lo que contiene; no hay donaciones, publicidad ni patrocinio.
- **Sin afiliación** con Nintendo ni con Sony, que no lo patrocinan ni lo respaldan. Mario Kart 64, Nintendo 64, PlayStation 2, DualShock y el resto de marcas citadas pertenecen a sus respectivos dueños.
- Para jugar, debes poseer una copia original de Mario Kart 64.
- Si eres titular de derechos y quieres que se retire algún contenido, abre un [issue](https://github.com/Alexis-VsCode/mario-kart-64-ps2/issues) y se retirará.

## 11. Licencia

Los aportes propios de este fork se publican bajo la licencia MIT, a nombre de Alexis Barrera ([LICENSE](LICENSE)). La licencia no cubre el juego ni sus recursos, la descompilación ni el código del repositorio original, que no declaran licencia.[^11]

## Documentación

| Documento | Contenido |
|---|---|
| [docs/manual/](docs/manual/README.md) | Índice del manual |
| [Manual de usuario](docs/manual/usuario.md) | Requisitos, descarga, PCSX2, Play!, OPL, uLaunchELF, controles, multitap, 60 FPS, Memory Card, idioma, limitaciones y solución de problemas |
| [Manual técnico](docs/manual/tecnico.md) | Arquitectura, compilación, pruebas, depuración, CI y publicación, y cómo traer las actualizaciones del original |
| [Créditos](docs/manual/creditos.md) | Autoría por áreas |
| [LICENSE](LICENSE) | Licencia MIT de los aportes del fork y lo que excluye |
| [CONTRIBUTING.md](CONTRIBUTING.md) | Definition of Done, reglas, ramas, commits y revisión |
| [CHANGELOG.md](CHANGELOG.md) | Cambios por versión |
| [Notas de la versión 1.2.1](docs/versiones/v1.2.1.md) | Cuerpo de la Release actual; las anteriores: [v1.2.0.md](docs/versiones/v1.2.0.md), [v1.1.0.md](docs/versiones/v1.1.0.md) y [v1.0.0.md](docs/versiones/v1.0.0.md) |
| [Caso de estudio](docs/caso-de-estudio.md) | Motivación, retos, decisiones y proceso |
| [docs/traduccion/](docs/traduccion/README.md) | Localización: estado, especificación, plan, glosario, trazabilidad, cambios, actas de revisión y deuda técnica |

## Notas

[^1]: [CC-30](docs/traduccion/cambios.md) (portafolio, aprobado el 2026-10-11) y [CC-32](docs/traduccion/cambios.md) (propósito sin lucro en README, página y notas de versión); [caso de estudio](docs/caso-de-estudio.md), sección «Motivación».
[^2]: [CC-29](docs/traduccion/cambios.md): el manifiesto `recursos/es/texturas.tsv` clasifica 1229 texturas (`a6fa679e`, `4216877e`). La fuente con 11 glifos nuevos está en [creditos.md](docs/manual/creditos.md).
[^3]: [CC-18 a CC-25](docs/traduccion/cambios.md), integrados en la versión 1.2.0 (merge `fd6a4bb7`); [acta de la 1.2.0](docs/traduccion/revisiones/2026-10-11-version-1.2.0.md).
[^4]: [CC-13](docs/traduccion/cambios.md), commit `0c39b416`; [acta de la 1.1.0](docs/traduccion/revisiones/2026-10-11-version-1.1.0.md).
[^5]: Publicación de la 1.2.1: commit `d3c27566`, ejecución de la CI [38181807319](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38181807319); [acta de la 1.2.1](docs/traduccion/revisiones/2026-10-11-version-1.2.1.md) y [notas de la versión](docs/versiones/v1.2.1.md).
[^6]: En la 1.2.0, `PS2SDK= make test` terminó con 0 fallos en las 44 pruebas que imprimen su resumen y 0 archivos por encima del tope de líneas ([trazabilidad, F10](docs/traduccion/trazabilidad.md)); detalle en el [manual técnico](docs/manual/tecnico.md#pruebas).
[^7]: Ejecución [38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616) de la 1.2.0 ([trazabilidad, F10](docs/traduccion/trazabilidad.md)) y la de publicación de la 1.2.1, [38181807319](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38181807319).
[^8]: [CC-26](docs/traduccion/cambios.md) (emulador en la CI) y [CC-31](docs/traduccion/cambios.md) (comparación estricta, referencias en [herramientas/emulador/referencias/](herramientas/emulador/referencias/)).
[^9]: [CC-31](docs/traduccion/cambios.md); las mutaciones reproducidas por la revisión están en las [actas](docs/traduccion/revisiones/).
[^10]: [Créditos](docs/manual/creditos.md), sección «Port a PlayStation 2».
[^11]: [LICENSE](LICENSE), commit `abc844ff`.
