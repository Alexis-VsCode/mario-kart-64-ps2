# Mario Kart 64 para PlayStation 2, en español

Port de Mario Kart 64 (versión estadounidense) a PlayStation 2, con todo el texto que ve el jugador en español. El repositorio incluye el juego descompilado, una capa de compatibilidad que sustituye el hardware de la Nintendo 64 por el de la PS2 y todos los recursos ya extraídos (texturas, pistas, karts, música y efectos). No hace falta la ROM original para compilar ni para jugar.

Es el port a PS2 de anthoo582, con la localización completa al español, la sincronización con el repositorio original y las mejoras de Alexis Barrera. Cada cambio sigue una especificación aprobada y, cuando se puede probar en el PC, una prueba que falla antes del cambio (ver [CONTRIBUTING.md](CONTRIBUTING.md)).

## Estado

Versión 1.2.1, del 2026-10-11. Qué cambia respecto a la 1.2.0: [CHANGELOG.md](CHANGELOG.md#121---2026-10-11). El avance y lo pendiente están en [docs/traduccion/README.md](docs/traduccion/README.md).

**Verificado en este repositorio, con pruebas y CI:**

- `make test` en el PC, sin el SDK de PS2: pruebas de textos, glifos, texturas, Memory Card (con libmc simulada), stick, región, registros de vídeo, vista panorámica, menú de configuración y trucos, más el comprobador del tope de líneas, 0 fallos ([detalle](docs/manual/tecnico.md#pruebas)).
- CI en verde en la ejecución [38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616): pruebas del PC; compilación para PS2 de las variantes release, `DEBUG=1` y `DEV=1`; tope de crecimiento de la ROM; compilación incremental real; inspección de la fuente de libdebug, y el job «Guion en el emulador (Play!)».
- **En un emulador:** ese job arranca dos veces el ELF de `DEV=1` en Play! 0.72 sin BIOS, comprueba en el registro la línea de región PAL con un ROMVER sintético y `vídeo: PMODE 8046`, y compara las capturas del título, del menú y de la carrera con las [referencias aprobadas](herramientas/emulador/referencias/) y entre las dos ejecuciones (CC-26).

**Según el port original:** probado en **PCSX2** (con BIOS) y en **Play!**.

**Sin verificar:**

- en una **PS2 real** y en una **TV**: el tacto del stick, el multitap, el cambio de Memory Card con el juego en marcha y el rendimiento en PANORÁMICO;
- el **antiparpadeo, las bandas y la posición de la imagen**, que solo se comprueban por los valores de los registros, porque las capturas del emulador leen la VRAM antes del PCRTC;
- la lectura de **ROMVER** bajo OPL sin reinicio del IOP: solo se verificó la ruta con reinicio y un ROMVER sintético;
- con **OPL** y **uLaunchELF** en hardware.

Las limitaciones conocidas están en el [manual de usuario](docs/manual/usuario.md#limitaciones-conocidas).

## Autoría

Soy Alexis Barrera ([Alexis-VsCode](https://github.com/Alexis-VsCode)), desarrollador e ingeniero de observabilidad, y mantengo este fork. Mario Kart 64 es el juego de mi infancia, y la descompilación me permitió mejorarlo, traducirlo y jugarlo en mi PS2.

Mi trabajo en este repositorio:

- **Localización completa al español:** textos, nombres de pista, glifos nuevos en la fuente, texturas reconstruidas y traducidas, y un manifiesto que clasifica todas las texturas, con filas de archivo y de carpeta.
- **Mejoras del port:** Memory Card sin pérdida de partidas, stick más fino, lectura de la región, menú CONFIGURACIÓN Y TRUCOS, opciones de imagen y trucos.
- **Verificación:** las pruebas del PC, la CI y el arranque automático en Play!.
- **Proceso:** cada cambio parte de un cambio de especificación aprobado, una prueba en rojo y una revisión con acta.

Evidencia:

- [Cambios de especificación](docs/traduccion/cambios.md) (CC-01 en adelante) y su [trazabilidad](docs/traduccion/trazabilidad.md) con los commits;
- [actas de revisión](docs/traduccion/revisiones/) y [deuda técnica](docs/traduccion/deuda.md);
- [ejecuciones de la CI](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions) y las [herramientas del emulador](herramientas/emulador/);
- [Releases](https://github.com/Alexis-VsCode/mario-kart-64-ps2/releases) con sus notas en [docs/versiones/](docs/versiones/).

## Créditos

- **Port a PS2:** anthoo582 ([anthoo582/mario-kart-64-ps2](https://github.com/anthoo582/mario-kart-64-ps2)), del que este repositorio es un fork.
- **Base:** el proyecto de descompilación de Mario Kart 64 ([n64decomp/mk64](https://github.com/n64decomp/mk64)).
- **Localización, mejoras y verificación de este fork:** Alexis Barrera.
- **Toolchain:** [ps2dev](https://github.com/ps2dev/ps2dev) (ps2sdk y gsKit).
- **Emulador de la CI:** [Play!](https://github.com/jpd002/Play-).

El detalle por áreas está en [docs/manual/creditos.md](docs/manual/creditos.md).

## Descarga

Como en el repositorio original, se publican la ISO y el ELF.

- **Última versión:** [Releases](https://github.com/Alexis-VsCode/mario-kart-64-ps2/releases/latest), con la ISO, el ELF monolítico, `SHA256SUMS` y las [notas de la versión](docs/versiones/v1.2.1.md).
- **ISO directa:** [`SLUS_999.99.SuperMarioKart64.iso`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/releases/latest/download/SLUS_999.99.SuperMarioKart64.iso).
- **ELF monolítico, para uLaunchELF desde USB:** [`SLUS_999.99.monolitico.elf`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/releases/latest/download/SLUS_999.99.monolitico.elf). Lleva la ROM dentro: no necesita `SMK64ROM.BIN`.
- **Alternativa:** la ISO versionada en `main`, [`compilaciones/SLUS_999.99.SuperMarioKart64.iso`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/raw/main/compilaciones/SLUS_999.99.SuperMarioKart64.iso).

| Archivo | Tamaño | SHA-256 |
|---|---|---|
| `SLUS_999.99.SuperMarioKart64.iso` | 13 387 776 bytes | `186d45b2feaa66078820005eb43370701a17ea45bdd15ad9e3eb420c8ffb0f21` |
| `SLUS_999.99.monolitico.elf` | En la lista de archivos de la Release | Su línea de `SHA256SUMS` en la Release |

Cómo comprobar los archivos y ejecutarlos en PCSX2, Play!, OPL o uLaunchELF: [manual de usuario](docs/manual/usuario.md).

## Características

- Las 20 pistas (16 de carrera y 4 de batalla), los 8 personajes y los modos Gran Premio, Contrarreloj, VS y Batalla, de 1 a 4 jugadores con multitap.
- Textos, nombres de pista oficiales, texturas con texto, HUD y carteles en español, incluidos BIENVENIDOS, YA, los emblemas 1J a 4J y PASO A NIVEL.
- **Menú CONFIGURACIÓN Y TRUCOS**, en OPCIONES, con lo elegido guardado en `SMK64CFG.DAT` de la Memory Card:
  - **ANTIPARPADEO** (desactivado por defecto) y **POSICIÓN X/Y** de la imagen;
  - **FORMATO** NORMAL, CON BANDAS o PANORÁMICO; CON BANDAS es el valor por defecto si la PS2 está configurada en 16:9;
  - trucos **DESBLOQUEAR TODO** (se aplica al cambiar de pantalla), **OBJETO** (objeto fijo; en batalla, uno no válido deja la ruleta normal), **200CC** (solo Gran Premio y VS en 150cc, y puntúa como 150cc) y **RIVALES SIN VENTAJA**.
  - Los récords se guardan aunque haya trucos activos; el menú lo advierte.
- Gráficos: un intérprete de listas de dibujo F3DEX, con el combinador de color y la TMEM de la N64, que produce paquetes para el GS. Vídeo NTSC entrelazado a 640×448 y 60 Hz, también en consolas PAL, que necesitan una TV que acepte 60 Hz ([detalle](docs/manual/usuario.md#consolas-pal-y-ntsc)).
- Audio original: las muestras de la ROM se mezclan con la misma aritmética que la N64 y salen a 48 kHz por `audsrv`.
- Modo 60 FPS durante la carrera, activo por defecto y conmutable con R3; la lógica del juego sigue a 30 Hz.
- Partidas guardadas en la Memory Card de la ranura 1, en dos copias alternas con CRC32, sin pisar la partida más nueva de una tarjeta cambiada en caliente.
- Arranque desde OPL sin reiniciar el IOP.
- Pantalla de fallo con el estado de cada hilo, el registro reciente y tildes.

## Inicio rápido

Con el toolchain de ps2dev instalado ([requisitos e instalación](docs/manual/tecnico.md#requisitos)):

```bash
. herramientas/entorno.sh
make -j"$(nproc)"
make iso                      # compilaciones/SLUS_999.99.SuperMarioKart64.iso
make test                     # pruebas en el PC; no necesita el SDK
git checkout -- build compilaciones && git clean -fdq -- build compilaciones
```

`build/` y `compilaciones/` están versionados: compilar y probar los modifica, y se restauran como en la última línea. Objetivos, variables y salida: [manual técnico](docs/manual/tecnico.md#compilar).

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
| [Notas de la versión 1.2.1](docs/versiones/v1.2.1.md) | Cuerpo de la Release de la versión actual; las anteriores: [v1.2.0.md](docs/versiones/v1.2.0.md), [v1.1.0.md](docs/versiones/v1.1.0.md) y [v1.0.0.md](docs/versiones/v1.0.0.md) |
| [docs/traduccion/](docs/traduccion/README.md) | Localización: estado, especificación, plan, glosario, trazabilidad, cambios, actas de revisión y deuda técnica |

## Aviso legal

- Proyecto **sin fines de lucro**, con fines **educativos**, de **preservación** y de apoyo a la comunidad. No se vende ni se cobra por nada de lo que contiene.
- **Sin afiliación** con Nintendo ni con Sony, que no lo patrocinan ni lo respaldan. Mario Kart 64, Nintendo 64, PlayStation 2, DualShock y el resto de marcas citadas pertenecen a sus respectivos dueños.
- Para jugar, debes poseer una copia original de Mario Kart 64.
- Si eres titular de derechos y quieres que se retire algún contenido, abre un [issue](https://github.com/Alexis-VsCode/mario-kart-64-ps2/issues) y se retirará.

Licencia: los aportes propios de este fork se publican bajo la licencia MIT, a nombre de Alexis Barrera ([LICENSE](LICENSE)). La licencia no cubre el juego ni sus recursos, la descompilación ni el código del repositorio original, que no declaran licencia.
