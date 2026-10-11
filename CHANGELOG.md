# Registro de cambios

Cambios de cada versión de este repositorio. Sigue el formato de [Keep a Changelog](https://keepachangelog.com/es-ES/1.1.0/), con las secciones Añadido, Cambiado, Corregido, Sincronizado con el original y Conocido. Las versiones se numeran `X.Y.Z` ([CONTRIBUTING.md](CONTRIBUTING.md#publicación-y-versión)).

El detalle de cada cambio está en el commit que se cita y en [docs/traduccion/](docs/traduccion/README.md): los requisitos en la [especificación](docs/traduccion/especificacion.md), los cambios de especificación (`CC-NN`) en [cambios.md](docs/traduccion/cambios.md) y la relación con los commits en la [trazabilidad](docs/traduccion/trazabilidad.md).

## [Sin publicar]

Nada todavía.

## [1.0.0] - 2026-10-11

Primera versión publicada: el port a PS2 de anthoo582, localizado por completo al español (fases F0 a F7) y sincronizado con el repositorio original hasta `ae93f71` (fase F8). Notas de la Release: [docs/versiones/v1.0.0.md](docs/versiones/v1.0.0.md).

### Añadido

**Localización al español (F0–F7):**

- Textos de menús, opciones, pausa, tiempos y resultados, fantasmas, Memory Card, intro de la batalla, ceremonia y créditos. Los botones se nombran como en el DualShock 2: CRUZ, CUADRADO, SELECT y R1.
- Los 20 nombres de pista oficiales de Nintendo en español, con su fuente en el [glosario](docs/traduccion/glosario.md).
- Fuente del menú con 11 glifos nuevos (Á É Í Ó Ú Ñ Ü ¡ ¿ º ª) y lectura de las cadenas con tildes (`5718601`, `641fe27`).
- 55 texturas con texto y los 48 cuadros de los carteles de Lakitu en español, generados desde PNG versionados en `recursos/es/` con el manifiesto `recursos/es/texturas.tsv` y `herramientas/texturas_es.py` (`4345598`).
- Pantallas propias del port (panel de rendimiento, página de audio, nombres de fase y registro) con tildes. La pantalla de fallo translitera, porque su fuente solo tiene ASCII.
- `make test` en el PC sin el SDK de PS2 (`f8f9a39`), conversión a EUC-JP sin `iconv` (`727c7ed`), tope de 1000 líneas por archivo de código (`f1f3d3d`) y comprobación de refactores por preprocesado (`cb36bbc`).
- CI en GitHub Actions: pruebas en el PC, compilación para PS2 con la imagen de ps2dev fijada por digest (`7387d01`), comparación de binario con una base (`a3d0bae`) y job `publicar` para el commit de los binarios (`c461c5b`).
- Documentación de la localización en `docs/traduccion/`: especificación, plan, glosario, trazabilidad y registro de cambios.

**Fase F8:**

- La CI compila también `make DEV=1`, y suma los jobs a pedido `release` (Release con la ISO y `SHA256SUMS`) y `limpiar-ramas` (borra las ramas ya contenidas en `main`) (`24ed39a0`, CC-09).
- Registro DEV de las cadenas del menú que la fuente no dibuja: secuencias inválidas o bytes de UTF-8 sin convertir, una vez por cadena, en las tres impresoras de texto (`a5e97ddf`, `f38d6de6`, `94cdfea5`; R-FUE-05).
- Pruebas nuevas en `make test`:
  - `lut_textura_glifo` se define una sola vez y sin los alias de la N64 (`e600bd6e`);
  - el tope de la reserva de matrices del texto del menú es el tamaño real de `efecto_mtx` (`697f3af6`; R-FUE-07);
  - ningún texto del manifiesto de texturas nombra botones de la N64 (`5d901a47`; R-TEX-07);
  - `inicializar_depuracion()` va antes del reinicio del IOP (`prueba_arranque.py`, `664d9013`);
  - el cronómetro de fases, compilado en el PC (`prueba_cronometro_fases.c`, `176651ed`);
  - una fila libre entre las líneas del panel 5x7 (`4612a508`).
- Manual de usuario, manual técnico y créditos en `docs/manual/`; este registro de cambios, [CONTRIBUTING.md](CONTRIBUTING.md), las notas de versión, el acta de revisión de F8 y el registro de deuda técnica (CC-12).

### Cambiado

- Los textos nuevos que trajo el original van en español y con tildes; los grupos del cronómetro de la ceremonia y de los créditos pasan a `GRUPO_CARGA_CEREMONIA` y `GRUPO_CARGA_CREDITOS` (`748db117`, `36fc9e40`).
- El commit de publicación pasa a `build(compilaciones): binarios e ISO en español`, con el commit de origen y la ejecución de la CI en el cuerpo (`24ed39a0`, CC-09).
- `BUILD_ID` es la fecha de la versión: `2026-10-11` (`6251a4a6`).
- La versión se verifica con las pruebas del PC y la CI. Se retira el recorrido manual en PCSX2 y la captura en TV (F6), y se rechaza el recorrido con capturas automáticas (CC-10, CC-12).

### Corregido

**F0–F7:**

- La tabla de texturas de glifos cubre los 236 glifos originales: en PS2, los índices a partir del 91 se leían fuera de la tabla (`4e35120`).
- El texto del menú no escribe más matrices de las que tiene su reserva (`dcc0914`).

**Fase F8** (CC-11):

- El cronómetro de fases admite 6 grupos: con los grupos nuevos, un quinto pisaba en silencio el informe de otro (`176651ed`, E3).
- La lectura de la ROM se rinde hacia los 24 s, antes que el perro guardián de 30 s, y muestra «no se pudo leer SMK64ROM.BIN del disco» en lugar de un cuelgue (`a86960cf`, E4).
- Una Memory Card que no contesta ya no se toma por una tarjeta nueva formateada: queda sin usar hasta el siguiente arranque (`61a88a74`, E5).
- `G_AC_DITHER` limita a 0 el alfa negativo antes de elevarlo al cuadrado, para que ese píxel quede oculto (`ce98830c`, G5).
- Sin matriz libre, la letra no se dibuja y su tilde tampoco; antes la tilde caía sobre la letra anterior (`9adc3192`, L2).
- El panel 5x7 deja una fila libre entre líneas para que las tildes no toquen la línea de arriba; reserva 128 KB de VRAM en lugar de los 112 KB que anotaba CC-11, porque la textura ocupa 16 páginas del GS (`ac4fcdae`, L3).

### Sincronizado con el original

Fusión `9f4d0215` de `c2ed147` y `ae93f71` de [anthoo582/mario-kart-64-ps2](https://github.com/anthoo582/mario-kart-64-ps2), con `merge.directoryRenames=false` (CC-08):

- Multitap de PS2 para 3 y 4 jugadores, con cada jugador fijo a su conector; sin multitap, dos mandos.
- Arranque desde OPL sin reiniciar el IOP; a cambio, sin VMC, PADEMU ni IGR de OPL.
- Tiempos límite en el reinicio del IOP, en la lectura del CD y en la Memory Card.
- 60 FPS más estables: tras tres tirones en una carrera, 30 FPS estables hasta la siguiente; la física da hasta 4 pasos por imagen de 2 a 4 jugadores.
- Caché de texturas por columnas de 256 px, tramado de color por primitiva, `FILTRADO_TEXTURAS` y el diagnóstico del combinador `SMK64_DIAG_CC`.
- Arreglos de color y de los vértices de `0x800E8700` (onomatopeyas, rayo, globo y partículas).
- Órdenes nuevas en los guiones de prueba: `graba`, `disparador` y `memoria`.

Se conservó la tabla de glifos de este repositorio, que tiene las 236 entradas del original en el mismo orden más las 11 del español.

### Conocido

- **Sin probar en una PS2 real**, ni con OPL o uLaunchELF en hardware. Según el autor del port original, se probó en PCSX2 (con BIOS) y en Play!.
- **Sin verificación visual registrada** de la versión en español: las pruebas miden textos, glifos y texturas, pero nadie del proyecto ha revisado la imagen en un emulador ni en un televisor (CC-12).
- **Multitap sin probar en hardware.**
- La pantalla de fallo sale sin tildes; el registro las conserva.
- La deuda técnica abierta, con su motivo, está en [deuda.md](docs/traduccion/deuda.md).

[Sin publicar]: https://github.com/Alexis-VsCode/mario-kart-64-ps2/compare/v1.0.0...main
[1.0.0]: https://github.com/Alexis-VsCode/mario-kart-64-ps2/releases/tag/v1.0.0
