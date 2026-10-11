# Registro de cambios

Cambios de cada versión de este repositorio. Sigue el formato de [Keep a Changelog](https://keepachangelog.com/es-ES/1.1.0/), con las secciones Añadido, Cambiado, Corregido, Sincronizado con el original y Conocido. Las versiones se numeran `X.Y.Z` ([CONTRIBUTING.md](CONTRIBUTING.md#publicación-y-versión)).

El detalle de cada cambio está en el commit que se cita y en [docs/traduccion/](docs/traduccion/README.md): los requisitos en la [especificación](docs/traduccion/especificacion.md), los cambios de especificación (`CC-NN`) en [cambios.md](docs/traduccion/cambios.md) y la relación con los commits en la [trazabilidad](docs/traduccion/trazabilidad.md).

## [Sin publicar]

Nada todavía.

## [1.2.0] - 2026-10-11

Versión con el menú de configuración y trucos, las opciones de imagen, la verificación en un emulador dentro de la CI y el cierre de la deuda técnica, con los cambios de especificación CC-18 a CC-30 de [cambios.md](docs/traduccion/cambios.md). Notas de la Release: [docs/versiones/v1.2.0.md](docs/versiones/v1.2.0.md). Commit de publicación: <<PUBLICACION>>.

### Añadido

- Archivo de opciones del port, `SMK64CFG.DAT`, en la Memory Card, leído y guardado en el hilo de guardado (`93cb4d04`, `8c022b34`; CC-18).
- Menú **CONFIGURACIÓN Y TRUCOS** en OPCIONES, con ANTIPARPADEO, POSICIÓN X/Y, FORMATO, DESBLOQUEAR TODO, OBJETO, 200CC, RIVALES SIN VENTAJA y VOLVER (`7c5439e4`, `146b23af`; CC-19).
- Opciones de imagen en 480i: antiparpadeo, desactivado por defecto, y posición de la imagen (`fa835b62`, `9173dde8`; CC-20).
- FORMATO NORMAL, CON BANDAS o PANORÁMICO; CON BANDAS por defecto si la PS2 está configurada en 16:9. PANORÁMICO ensancha el aspecto de cada vista, de la ceremonia y el cono de visibilidad de los objetos (`92c1f1f3`, `fd4286e3`, `c52e2f8d`, `761d735d`; CC-21).
- Trucos (CC-22 a CC-25):
  - DESBLOQUEAR TODO, que se aplica al reconstruir cada pantalla de menú (`be355571`, `91c7254e`);
  - OBJETO: un objeto fijo; en batalla, uno no válido deja la ruleta normal (`5a19ff97`);
  - 200CC: solo en Gran Premio y VS a 150cc, y puntúa como 150cc (`c80fe61e`);
  - RIVALES SIN VENTAJA (`f46bc633`).
  - Los récords se guardan aunque haya trucos activos, con una advertencia en el menú.
- Job «Guion en el emulador (Play!)» en la CI: arranca dos veces el ELF de `DEV=1` en Play! 0.72 sin BIOS, revisa el registro (región PAL con un ROMVER sintético y `vídeo: PMODE 8046`) y compara las capturas del título, del menú y de la carrera con sus referencias y entre sí (`2c3a8b29`, `98a042b7`, `570a0a12`, `979fcf14`; CC-26). Ejecución en verde: [38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616).
- Pasos nuevos en el job `compilar-ps2`: tope de crecimiento de la ROM (`a27fd80f`, D-03), compilación incremental real (`04adf1f6`, D-04) e inspección de la fuente de libdebug (`68bc6dce`, D-07).
- Pruebas nuevas en `make test` (`3cf36394`): opciones del port, menú de configuración, registros de vídeo, vista panorámica, los cuatro trucos, el arnés de `memory_card.c` con libmc simulada (`36796171`, D-16), las herramientas del emulador y de la CI, y la reserva de matrices.

### Cambiado

- Todas las texturas quedan clasificadas en el manifiesto `recursos/es/texturas.tsv`, con filas de archivo y de carpeta y exclusiones con motivo (`22fbc484`, `9032ab75`, `4216877e`, `431c3186`; CC-29, D-05).
- La pantalla de fallo escribe con tildes mediante `scr_putchar` y `a_cp437` (`8e311363`, `ab75b9aa`; D-07).
- La elección entre la cruceta y el stick pasa a la función pura `cruceta_manda_stick` (`bd70c399`, `3d67d29d`; D-18).
- Texturas reconstruidas (CC-28): el «º» de los puestos (`2175d03b`), VUELTA (`d7b3feb9`), los botones y las copas (`9d9ac85e`) y el título de la Jungla DK (`bace922a`).
- Texturas traducidas (CC-29): BIENVENIDOS (`cb32c871`), YA (`3505ff26`), los emblemas 1J a 4J (`caf7756f`) y PASO A NIVEL (`625105f4`). No queda ninguna textura pendiente (D-24).

### Corregido

- **Memory Card:** la cabecera B y las demás órdenes a libmc no se envían tras vencer una lectura (`2c83c0f8`, D-21); el registro da la generación que se escribe (`c69d9ef4`, D-20); las opciones quedan escritas antes de subir su versión (`3bbac652`).
- **Reserva `efecto_mtx`:** los menús, los globos, las partículas, el kart y los fuegos artificiales no escriben fuera de ella con la reserva llena (`93231a07`, `64805e8c`, `a989c0f5`, `d2ce4c18`; D-08).
- Las bandas no desbordan MAGH (`d5ee5381`); 200CC no escribe un empuje sin efecto (`a6397211`); RIVALES SIN VENTAJA respeta al rival designado (`4c0323bf`).
- D-19: la prueba de la región separa la guarda de largo (`0c962092`). D-22: erratas y «1 fallo» en singular (`9a92bc41`).
- D-23: con la reserva de matrices llena, la partícula se deja de dibujar en lugar de salir con la matriz anterior (`483cc7de`).
- D-25: el código y las herramientas ya no citan identificadores de requisito, y `prueba_textos_port.py` lo vigila (`259a000d`, `667b37bf`).

### Conocido

- **Sin hardware real ni TV:** el tacto del stick, el multitap, el cambio de Memory Card en caliente y el rendimiento en PANORÁMICO. El antiparpadeo, las bandas y la posición solo se comprueban por los valores de los registros, porque las capturas leen la VRAM antes del PCRTC.
- ROMVER solo se verificó por la ruta con reinicio del IOP y con un ROMVER sintético.
- D-06 (verificación visual en una TV o una PS2) y D-17 (ROMVER en consola real y bajo OPL) pasan a los [límites declarados](docs/traduccion/especificacion.md#9-límites-declarados) en lo que la CI no puede ver; el job del emulador cubre el resto (CC-26).
- En PANORÁMICO, los objetos y la pista pueden aparecer tarde en los bordes, y el marcador sale estirado.

## [1.1.0] - 2026-10-11

Versión de mantenimiento de la fase F9, con los cambios de especificación CC-13 a CC-17 de [cambios.md](docs/traduccion/cambios.md) y parte de la [deuda técnica](docs/traduccion/deuda.md) de la 1.0.0. `BUILD_ID` sigue en `2026-10-11`, la fecha de la versión. Notas de la Release: [docs/versiones/v1.1.0.md](docs/versiones/v1.1.0.md).

### Añadido

- La Release publica también el ELF monolítico, `SLUS_999.99.monolitico.elf`, para jugar desde USB con uLaunchELF sin compilar y sin `SMK64ROM.BIN`. `SHA256SUMS` lleva una línea por la ISO y otra por el ELF (`4bdd41a8`, CC-16).
- Al arrancar, el juego lee la región de la consola en `rom0:ROMVER`. En una consola PAL, el registro avisa de que la imagen es NTSC a 60 Hz y de que hace falta una TV que lo acepte. El modo de vídeo no cambia (`807d2c45`, `3b11daa5`, `ac1a1090`; CC-15).
- Pruebas nuevas en `make test`, que pasa a 31 pruebas (`a29bd920`):
  - `prueba_eleccion_guardado.c`: la copia que se pisa y la generación mínima al guardar en una tarjeta nueva (`2e578b4b`);
  - `prueba_eje_palanca.c`: la conversión del eje del stick y el reposo de la cruceta (`4a48ff6a`, `ddbdc023`);
  - `prueba_region_ps2.c`: la región PAL, NTSC o desconocida a partir de ROMVER (`807d2c45`);
  - los casos del alfa con tramado en `prueba_combinador.c` (`d41996f7`, CC-17).
- La sección [Consolas PAL y NTSC](docs/manual/usuario.md#consolas-pal-y-ntsc) del manual de usuario.

### Cambiado

- La zona muerta del stick izquierdo baja de 24 a 8: el kart empieza a girar con 28 de 127 (un 22 % del recorrido), en lugar de 41 (un 32 %). La cruceta sigue haciendo de stick mientras el izquierdo está a 25 o menos del centro, con su propio umbral `ZONA_REPOSO_CRUCETA` (`1fc4c437`, `dcbe656e`, `34ab306d`, `2b37f61f`; CC-14).
- El alfa con tramado de `G_AC_DITHER` pasa a la función pura `combinador_alfa_tramado()` de `incluir/graficos/combinador_color.h`, sin cambio de conducta (`ff313bc5`, CC-17). Salda D-01 y D-02.
- El job `release` corre en el contenedor de ps2dev, se detiene si el SHA-256 de la ISO no está en las notas de la versión y compila el ELF monolítico (`4bdd41a8`, CC-16).
- El registro del ritmo de física dice «ritmo de física» en lugar de «ritmo 3-4P», porque también actúa con 2 jugadores (`7e9edfaa`).
- La comprobación de lo descargado pasa a `sha256sum -c --ignore-missing SHA256SUMS`, porque `SHA256SUMS` tiene dos líneas y basta con descargar uno de los dos archivos ([manual de usuario](docs/manual/usuario.md#descarga-y-comprobación)).

### Corregido

- **Memory Card** (CC-13):
  - al insertar una tarjeta después de arrancar o cambiarla en caliente, el guardado escribía en la tarjeta nueva sin leer sus copias y podía pisar la partida más nueva; ahora pisa la más vieja y escribe con una generación mayor (`b989feca`, `e4937a28`, `8c69e253`);
  - la espera de la partida al arrancar se mide con el reloj y no en vueltas del bucle (`41441ae5`);
  - el segundo borrado de los archivos de versiones anteriores solo se hace si la tarjeta sigue contestando (`3e62e63e`, D-12);
  - los resultados de `mcGetInfo` ya no se escriben en la pila si la tarjeta contesta tarde (`abe7c205`, D-13);
  - D-11 se mantiene, con la decisión escrita en CC-13.
- El job `publicar` ya no oculta un fallo del commit: solo omite el commit si no hay nada preparado (`4bdd41a8`, CC-16).
- Deuda técnica:
  - D-09: la prueba del tope de la reserva de matrices mira la condición entera (`bb8d41bd`, `b780d986`);
  - D-10: `GRUPOS_MAX` tiene que ser mayor que el número de grupos de `marcas_registro.h` (`3e2067a4`);
  - D-14: el registro del multitap dice «sin multitap» en lugar de «no» (`1d8f5670`);
  - D-15: los textos de `compilacion.yml` llevan tildes (`c641d19b`).

### Conocido

- **Sin verificar en una consola real lo nuevo de esta versión:** el tacto del stick, la lectura de ROMVER con el IOP reiniciado y bajo OPL sin reinicio, y el cambio de Memory Card en caliente (D-06).
- **Sin probar en una PS2 real**, ni con OPL o uLaunchELF en hardware, ni con un multitap real. Según el autor del port original, se probó en PCSX2 (con BIOS) y en Play!.
- **Sin verificación visual registrada** de la versión en español (CC-12).
- Con una consola PAL hace falta una TV que acepte NTSC a 60 Hz.
- La deuda técnica abierta, con su motivo, está en [deuda.md](docs/traduccion/deuda.md).

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

- La CI compila también `make DEV=1`, y suma los jobs a pedido `release` (Release con la ISO y `SHA256SUMS`) y `limpiar-ramas` (borra las ramas ya contenidas en `main`). Las entradas `publicar` y `limpiar_ramas` aceptan «si» y «sí» (`24ed39a0`, `b69f1548`, CC-09).
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

[Sin publicar]: https://github.com/Alexis-VsCode/mario-kart-64-ps2/compare/v1.1.0...main
[1.1.0]: https://github.com/Alexis-VsCode/mario-kart-64-ps2/releases/tag/v1.1.0
[1.0.0]: https://github.com/Alexis-VsCode/mario-kart-64-ps2/releases/tag/v1.0.0
