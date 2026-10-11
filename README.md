# Mario Kart 64 para PlayStation 2, en español

Port de Mario Kart 64 (versión estadounidense) a PlayStation 2, con todo el texto que ve el jugador en español. El repositorio incluye el juego descompilado, una capa de compatibilidad que sustituye el hardware de la Nintendo 64 por el de la PS2 y todos los recursos ya extraídos (texturas, pistas, karts, música y efectos). No hace falta la ROM original para compilar ni para jugar.

Es el port a PS2 de anthoo582, con la localización completa al español, la sincronización con el repositorio original y las mejoras de Alexis Barrera. Cada cambio sigue una especificación aprobada y, cuando se puede probar en el PC, una prueba que falla antes del cambio (ver [CONTRIBUTING.md](CONTRIBUTING.md)).

## Estado

Versión 1.0.0, del 2026-10-11. El avance y lo pendiente de la fase en curso están en [docs/traduccion/README.md](docs/traduccion/README.md).

**Verificado en este repositorio, con pruebas y CI:**

- `make test` en el PC, sin el SDK de PS2: 28 pruebas y el comprobador del tope de líneas, 0 fallos. Comprueban, entre otras cosas, cada texto en español byte a byte y por tinta contra la zona segura del televisor, la tabla de glifos, las texturas en español y la compatibilidad de la fuente con la N64 ([detalle](docs/manual/tecnico.md#pruebas)).
- CI en verde: pruebas en el PC y compilación para PS2 de las variantes release, `DEBUG=1` y `DEV=1` con la ISO. Ejecución de la versión 1.0.0: <<PUBLICACION>>.

**Según el port original:** probado en **PCSX2** (con BIOS) y en **Play!**.

**Sin verificar:**

- en una **PS2 real**;
- con **OPL** y **uLaunchELF** en hardware;
- con un **multitap real**;
- la **imagen en pantalla** de la versión en español: no hay revisión visual registrada.

Las limitaciones conocidas están en el [manual de usuario](docs/manual/usuario.md#limitaciones-conocidas).

## Autoría y créditos

- **Port a PS2:** anthoo582 ([anthoo582/mario-kart-64-ps2](https://github.com/anthoo582/mario-kart-64-ps2)), del que este repositorio es un fork.
- **Base:** la descompilación comunitaria de Mario Kart 64.
- **Localización al español, sincronización con el original y mejoras de este repositorio:** Alexis Barrera (GitHub: [Alexis-VsCode](https://github.com/Alexis-VsCode)), que mantiene el fork.
- **Toolchain:** [ps2dev](https://github.com/ps2dev/ps2dev) (ps2sdk y gsKit).

El detalle por áreas está en [docs/manual/creditos.md](docs/manual/creditos.md).

## Descarga

- **Última versión:** [Releases](https://github.com/Alexis-VsCode/mario-kart-64-ps2/releases/latest), con la ISO, `SHA256SUMS` y las [notas de la versión](docs/versiones/v1.0.0.md).
- **ISO directa:** [`SLUS_999.99.SuperMarioKart64.iso`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/releases/latest/download/SLUS_999.99.SuperMarioKart64.iso).
- **Alternativa:** la ISO versionada en `main`, [`compilaciones/SLUS_999.99.SuperMarioKart64.iso`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/raw/main/compilaciones/SLUS_999.99.SuperMarioKart64.iso).

| Archivo | Tamaño | SHA-256 |
|---|---|---|
| `SLUS_999.99.SuperMarioKart64.iso` | <<PUBLICACION>> | <<PUBLICACION>> |

Cómo comprobarla y ejecutarla en PCSX2, Play!, OPL o uLaunchELF: [manual de usuario](docs/manual/usuario.md).

## Características

- Las 20 pistas (16 de carrera y 4 de batalla), los 8 personajes y los modos Gran Premio, Contrarreloj, VS y Batalla, de 1 a 4 jugadores con multitap.
- Textos, nombres de pista oficiales, texturas con texto, HUD y carteles de Lakitu en español, con 11 glifos nuevos en la fuente del menú.
- Gráficos: un intérprete de listas de dibujo F3DEX, con el combinador de color y la TMEM de la N64, que produce paquetes para el GS. Video NTSC entrelazado a 640×448.
- Audio original: las muestras de la ROM se mezclan con la misma aritmética que la N64 (microcódigo de audio reescrito en C) y salen a 48 kHz por `audsrv`.
- Modo 60 FPS durante la carrera, activo por defecto y conmutable con R3; la lógica del juego sigue a 30 Hz.
- Partidas guardadas en la Memory Card de la ranura 1, en dos copias alternas con CRC32.
- Arranque desde OPL sin reiniciar el IOP.
- Pantalla de fallo con el estado de cada hilo y el registro reciente.

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
| [CONTRIBUTING.md](CONTRIBUTING.md) | Definition of Done, reglas, ramas, commits y revisión |
| [CHANGELOG.md](CHANGELOG.md) | Cambios por versión |
| [Notas de la versión 1.0.0](docs/versiones/v1.0.0.md) | Cuerpo de la Release |
| [docs/traduccion/](docs/traduccion/README.md) | Localización: estado, especificación, plan, glosario, trazabilidad, cambios, actas de revisión y deuda técnica |

## Aviso legal

Proyecto de preservación sin afiliación con Nintendo ni con Sony. Mario Kart 64, Nintendo 64, PlayStation 2, DualShock y el resto de marcas citadas pertenecen a sus respectivos dueños.

Ni el repositorio original ni este fork declaran una licencia, y este repositorio no añade ninguna.
