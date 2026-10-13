# Trazabilidad

Relaciona cada requisito de la [especificación](especificacion.md) con su prueba, sus commits y su evidencia. Estado a 2026-10-11: la localización de F0 a F7 (cerrada en `dda9a5f`), la sincronización con el original de F8 (cerrada en `main`, `af3bfa05`), la versión 1.1.0 de F9 (publicada en `45bbe10a`), la versión 1.2.0 de F10 (en `feature/version-1.2.0`, `fd6a4bb7`) y la versión 1.2.1 de F11 (en `feature/capturas-1.2.1`, `863cbc45`).

## Cómo se completa

- **Commits:** hashes cortos, integrados en `feature/idioma-espanol` (F0 a F7), en `feature/sincronizacion-upstream` (F8), en `feature/version-1.1.0` (F9), en `feature/version-1.2.0` (F10) o en `feature/capturas-1.2.1` (F11). Si prueba y cambio van en commits separados, se anotan los dos (rojo → verde).
- **Rojo:** cómo se demostró que la prueba falla sin el cambio:
  - **comprobado:** la prueba del commit, ejecutada sobre el árbol del commit padre, falla (se indica cuántos fallos);
  - **módulo nuevo:** la prueba cubre un archivo que no existía, así que sin el cambio no puede pasar;
  - **no aplica:** refactor, cuya prueba es de equivalencia (R-GOB-02).
- **Mutación restaurada (R-GOB-03):** en F1–F7 está registrada en los mensajes de `4bf57f3`, `d28f950` y `da631b0` (este último para `23055c5` y `29541a4`); para el resto de commits de entonces no quedó registrada. En F8, F9 y F10, cada commit con prueba la registra en su mensaje, y REVISIÓN la reprodujo (actas de [F8](revisiones/2026-10-11-sincronizacion.md), [F9](revisiones/2026-10-11-version-1.1.0.md) y [F10](revisiones/2026-10-11-version-1.2.0.md)).
- **Estados:** `hecho` (integrado y con su prueba en verde), `parcial` (hecho en parte; se indica qué falta), `pendiente` (sin hacer).
- **Requisito cerrado:** cuando está `hecho`, tiene la evidencia y REVISIÓN lo aprueba. La aprobación de REVISIÓN de F1–F7 no quedó registrada en el repositorio; las de F8, F9 y F10 están en sus actas ([F8](revisiones/2026-10-11-sincronizacion.md), [F9](revisiones/2026-10-11-version-1.1.0.md), [F10](revisiones/2026-10-11-version-1.2.0.md)). La tabla indica el estado de implementación y prueba.
- **Criterios de F6:** desde [CC-12](cambios.md), lo que dependía del recorrido en PCSX2 o de una captura en TV se acepta con lo que comprueban las pruebas del PC y la CI. Lo que eso deja sin ver estuvo en la deuda D-06 y desde F10 está en los [límites declarados](especificacion.md#9-límites-declarados); el job `emulador` de la CI arranca el juego (CC-26).
- **Cambios de especificación:** se anotan en [cambios.md](cambios.md) y se enlazan aquí.

## Evidencia común

- **`make test` sin SDK.** En `dda9a5f`, `env -u PS2SDK make test` termina con 0: 26 pruebas y el tope de líneas, 0 fallos. `env -u PS2SDK make es`, `make hoja-es`, `make herramientas` y `make clean` tampoco piden el SDK, y `env -u PS2SDK make` falla con el mensaje de `PS2SDK`. Comprobado el 2026-09-29.
- **Python 3.8.** Con `make test PYTHON=python3.8`, partiendo sin `build/ps2/jp`, `build/ps2/es` ni la tabla de caminos, las copias regeneradas coinciden byte a byte con las versionadas en `dda9a5f`.
- **CI** (`.github/workflows/compilacion.yml`, todas en verde):

  | Ejecución | Commit | Rama | Qué cubre |
  |---|---|---|---|
  | [n.º 1](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/36459563109) | `7387d01` | `idioma/infra` | `pruebas-pc` y `compilar-ps2` |
  | [n.º 3](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/36459868320) | `a3d0bae` | `idioma/infra` | Final de F1 |
  | [n.º 4](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/36460503442) | `cb36bbc` | `idioma/fuente` | Refactor de glifos y LUT de 236 |
  | [n.º 5](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/36460518925) | `cb36bbc` | `idioma/fuente` | Lanzada a mano con base `4e35120`: `mismo-binario` informa `igual` para `SLUS_999.99` y `SMK64ROM.BIN`, en release y con `DEBUG=1` |
  | [n.º 6](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/36460978286) | `d87d14f` | `idioma/fuente` | Regla única de avance |
  | [n.º 7](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/36461774598) | `5718601` | `idioma/fuente` | Incluye `9abb8d7` y `dcc0914` |
  | [n.º 8](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/36461938399) | `641fe27` | `idioma/fuente` | Final publicado de F3 |
  | [n.º 9](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/36462490896) | `236962b` | `idioma/texturas` | A1–A6 y el merge de `idioma/infra` |
  | [36518116212](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/36518116212) | `c461c5b` | `feature/idioma-espanol` | Final: las cinco ramas integradas. `pruebas-pc`, `compilar-ps2` (release, `DEBUG=1`, `make test`, ISO) y `publicar` (release, `DEBUG=1`, `DEV=1`, `make test`, ISO y commit `dda9a5f`) en verde; `mismo-binario` omitido (sin `base`) |

- **Gobernanza** (comprobado el 2026-09-29 sobre `origin/main..dda9a5f`): el comando de R-GOB-01 devuelve los 4 commits `chore` registrados en [CC-06](cambios.md); solo `dda9a5f`, el de publicación, toca `build/` y `compilaciones/` (R-GOB-05); ningún archivo de `codigo/`, `incluir/` o `herramientas/` lleva identificadores de requisito (R-GOB-07).
- **F8** (comprobado el 2026-10-11 sobre `origin/main..feature/sincronizacion-upstream`, en `d5f95cc5`):
  - el comando de R-GOB-01 devuelve solo `c2ed147` y `ae93f71`, los commits del original que trae la fusión ([CC-08](cambios.md));
  - `git log --name-only … -- build compilaciones` sale vacío: `build/` y `compilaciones/` esperan al commit de publicación (R-GOB-05);
  - `git log --format='%(trailers)'` sale vacío en todos los commits; el grep de R-GOB-07 sale vacío;
  - `make test` terminó con 0 fallos en el worktree de revisión de cada rama integrada ([acta](revisiones/2026-10-11-sincronizacion.md));
  - CI de F8 (`pruebas-pc`, `compilar-ps2` con `make DEV=1` y `publicar`): ejecución [38123501282](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38123501282), commit de publicación `900c9be3`.
- **F9** (comprobado el 2026-10-11 sobre `origin/main..feature/version-1.1.0`, en `a29bd920`):
  - `env -u PS2SDK make test` termina con 0: 31 pruebas (28 de F8 más `prueba_eleccion_guardado`, `prueba_eje_palanca` y `prueba_region_ps2`) y el tope de líneas, 0 fallos;
  - el comando de R-GOB-01 devuelve solo `b780d986`, de tipo `style` ([acta de F9 §7](revisiones/2026-10-11-version-1.1.0.md#7-integración));
  - `git log --name-only … -- build compilaciones` sale vacío, `git log --format='%(trailers)'` también, y el grep de R-GOB-07 sale vacío;
  - los 38 commits son míos;
  - CI, publicación y Release `v1.1.0` de F9 (commit de publicación, ejecución, tamaño y SHA-256 de la ISO y del ELF monolítico): commit de publicación `45bbe10a`, ejecución [38149880694](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38149880694), ISO de 13 381 632 bytes (unos 12,8 MiB) con SHA-256 `e2f3abfea88cc7e61f16b2254934697ace926de77d74428647c07c9e1985afea`; el ELF monolítico, con su suma en el `SHA256SUMS` de la Release `v1.1.0`

- **F10** (comprobado el 2026-10-11 sobre `main..feature/version-1.2.0`, en `fd6a4bb7`):
  - `PS2SDK= make test` termina con 0: las 44 pruebas que imprimen su resumen dan 0 fallos y el tope de líneas, 0 archivos por encima;
  - 113 commits (99 más 14 merges), todos míos; el comando de R-GOB-01 sale vacío;
  - `git log --name-only … -- build compilaciones` sale vacío y `git log --format='%(trailers)'` también;
  - el grep de R-GOB-07, con `VID` y `TRU`, encuentra 8 líneas en 4 archivos de `herramientas/` ([deuda.md](deuda.md), D-25);
  - CI en verde: ejecución [38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616) (`pruebas-pc`, `compilar-ps2` con release, `DEBUG=1`, `DEV=1`, tope de la ROM, build incremental y fuente de libdebug, y `emulador`);
  - publicación: commit `9ab41422`, ejecución [38167051526](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38167051526), ISO de 13 387 776 bytes, SHA-256 `186d45b2feaa66078820005eb43370701a17ea45bdd15ad9e3eb420c8ffb0f21`.

## Commits de F1–F3

Los commits de `idioma/infra` e `idioma/fuente`, uno por uno. `476dd52` (infra) llegó después: la prueba del conversor omite la comparación con un `iconv` sin JIS X 0212.

| Commit | Rama | Tipo | Qué hace | Prueba | Rojo |
|---|---|---|---|---|---|
| `f8f9a39` | infra | build | `make test`, `clean` y `herramientas` sin SDK | `env -u PS2SDK make test`; job `pruebas-pc` | Antes del cambio, `make test` sin SDK se corta con el `$(error)` |
| `727c7ed` | infra | build | Conversor EUC-JP propio | `prueba_convertir_eucjp.py` | Módulo nuevo |
| `ecbfd5c` | infra | fix | Metadatos de pista en EUC-JP, `-iquote $(BUILD)/jp` y dependencias de `test` | `prueba_metadatos_eucjp.py` | Comprobado sobre `727c7ed`: 5 fallos (metadatos incluidos sin convertir) |
| `8fdea7c` | infra | build | Pruebas con `-fsigned-char` | `make -n test` | No aplica (opción de compilación) |
| `f1f3d3d` | infra | build | Tope de 1000 líneas en `make test` | `comprobar_lineas.py` | Módulo nuevo |
| `7387d01` | infra | ci | Jobs `pruebas-pc` y `compilar-ps2` | CI n.º 1 | No aplica |
| `6dd12e7` | infra | ci | `make clean` antes de compilar para PS2 | CI n.º 3 | No aplica |
| `a3d0bae` | infra | ci | `comparar_binario.sh` y job `mismo-binario` | CI n.º 3 y n.º 5 | No aplica |
| `418ea18` | fuente | refactor | Funciones de glifos a `glifos.inc.c` | `comparar_preprocesado.py 418ea18^ 418ea18 codigo/menus/elementos_menu.c`: `igual` (200 531 tokens) | No aplica |
| `4e35120` | fuente | fix | LUT de 236 entradas, sin los 7 arreglos, con `ASSERT_ESTATICO` | `prueba_tablas_glifos.py` | Comprobado sobre `418ea18`: 13 fallos |
| `1c9545d` | fuente | refactor | `lista_glifos.inc.c` (X-macro) | `comparar_preprocesado.py 1c9545d^ 1c9545d …`: `igual` (200 461 tokens); CI n.º 5: `cb36bbc` da el mismo binario que `4e35120` | No aplica |
| `cb36bbc` | fuente | build | `comparar_preprocesado.py` | Uso en `418ea18` y `1c9545d` | No aplica (herramienta) |
| `9e6bec7` | fuente | feat | `caracteres_es.c` y `caracteres_es.h` | `prueba_caracteres_es.c` | Módulo nuevo |
| `d87d14f` | fuente | refactor | `leer_glifo`, regla única de avance | `prueba_glifos.c`, `probar_compatibilidad` (huella `0x770E34E9`). El preprocesado cambia, como corresponde a un cambio de lógica; la equivalencia la da la huella | No aplica (caracterización) |
| `9abb8d7` | fuente | feat | `generar_glifos_es.py` | `prueba_glifos_es.py` | Módulo nuevo |
| `dcc0914` | fuente | fix | Tope del pool de matrices bajo `AVOID_UB` | Compilación de PS2 en la CI (n.º 7) y revisión técnica. Sin prueba en el PC: la función arma listas de dibujo | No demostrado |
| `5718601` | fuente | feat | Glifos del español en la ROM y en la lista; diacrítico con la matriz de la letra | `prueba_tablas_glifos.py` | Comprobado sobre `dcc0914`: 13 fallos |
| `641fe27` | fuente | feat | Secuencias `8F xx xx` en `leer_glifo` | `prueba_glifos.c` | Comprobado sobre `5718601`: 13 fallos |
| `1ee6041` | texturas | feat | `png_simple.py` | `prueba_png_simple.py` | Módulo nuevo |
| `a7e918e` | texturas | feat | `formatos_textura.py` | `prueba_formatos_textura.py` | Módulo nuevo |
| `9f9beac` | texturas | build | `archivos_host.c`, herramienta `tkmk00` y `referencias_tkmk00.txt` | `prueba_tkmk00.py` | Módulo nuevo |
| `2ff6bf0` | texturas | feat | Despacho por firma TKMK00/MIO0 | `prueba_textura_menu.c` | Módulo nuevo |
| `fdd6a54` | texturas | feat | `invertir_texturas.py --superponer` | `prueba_invertir_texturas.py` | Comprobado sobre `2ff6bf0`: 3 fallos |
| `4345598` | texturas | feat | Manifiesto `recursos/es/texturas.tsv` y `texturas_es.py` | `prueba_texturas_es.py` | Módulo nuevo |
| `236962b` | texturas | merge | Trae `6dd12e7` y `a3d0bae` de `idioma/infra` | CI n.º 9 | No aplica |

## Commits de F4 y del cierre

Por bloque; el detalle de cada commit está en su mensaje.

| Rama | Commits | Qué hace | Pruebas | Rojo y mutación |
|---|---|---|---|---|
| texturas | `37633d3` | Bloque B: las 40 TKMK00 a traducir salen de PNG, en MIO0 con `TAMANIO_ES_*` (`make es`) | `prueba_cableado_es.py` | Módulo nuevo |
| texturas | `31eaf62` | Controller Pak en el manifiesto con «no se muestra» | `prueba_texturas_es.py` | No registrado |
| texturas | `03e5967`, `788a957`, `78b7177`, `7e0d345`, `a4676b3`, `74cbaf6`, `b4f294b`, `c86be95` | Arte: títulos de menú, botones, PULSA START, TIEMPO/VUELTA, puestos, Lakitu, títulos de pista y cartel de la granja | `prueba_composicion_es.py`, `prueba_hud_es.py`, `prueba_lakitu_es.py`, `prueba_titulos_es.py`, `prueba_cartel_es.py` | Módulo nuevo en cada prueba nueva; mutaciones no registradas |
| texturas | `a0da3a1`, `e28eea2`, `44cc3fb` | `make hoja-es`; G y C de los títulos; cuadros del giro de Lakitu | `prueba_hojas_es.py`, `prueba_composicion_es.py`, `prueba_lakitu_es.py` | No registrado |
| cadenas | `15136d3`, `ae9dc3c` | Traslado a `textos_menu.inc.c` y prueba de textos | `prueba_textos.c` | Refactor sin prueba de equivalencia registrada; la prueba nace con las tablas `PENDIENTE` |
| cadenas | `ecd39f1`, `5bddeef`, `39059d8`, `f8bf7b5`, `88e159b`, `321091a`, `25311d4`, `ab920e9` | Bloques B1–B7 | `prueba_textos.c` | Comprobado en `da631b0`: 110, 36, 56, 14, 331, 88, 32 y 82 fallos sin el cambio |
| cadenas | `330e2d9`, `5b21e3e`, `b061832`, `d28f950` | Maquetación en la zona segura (CC-01) y hueco del puesto | `prueba_textos.c` | `d28f950`: rojo y mutación en su mensaje |
| cadenas | `4da5ab9`, `47a7371` | Literales a tablas | Verificación en `6794945` | No aplica (ver CC-06) |
| cadenas | `f53a3b4`, `3b58fd2`, `14c3b63`, `23055c5`, `29541a4`, `4bf57f3`, `2688be9`, `26a0bbc`, `32c2a6f`, `a16b42c`, `a54c0d4` | Ajustes de la prueba de textos, fuente de depuración y nombres de pista | `prueba_textos.c` | Mutaciones de `23055c5` y `29541a4` en `da631b0`; `4bf57f3` en su mensaje; `a16b42c` → `a54c0d4` en dos commits |
| port | `3db4b80`, `82858b4` | Fuente 5x7 en un módulo puro, con tildes | `prueba_fuente_5x7.c` | Refactor con huella ASCII; módulo nuevo |
| port | `0af8ebe`, `ead3e9d`, `ac10246`, `7ec08ed`, `1bc10ba`, `7653639` | Panel, página de audio, nombres de fase y puntos de control | `prueba_textos_port.py`, `prueba_ancho_panel.py` | Módulo nuevo; mutaciones no registradas |
| port | `9d2b711`, `91b2a89`, `823a0c8` | Marcas del registro (CC-05) | `prueba_textos_port.py` | `9d2b711`: preprocesado `igual`; el resto no registrado |
| port | `0c05c15`, `ba66cf9` | Pantalla de fallo y avisos de arranque | `prueba_textos_port.py`, `prueba_caracteres_es.c` | No registrado |
| port | `40ed241`, `37cf760` | Fuente de depuración N64 sin lecturas fuera de la tabla | `prueba_cadena_depuracion.c` | `40ed241`: preprocesado `igual`; `37cf760` no registrado |
| port | `ae0cf90`, `d9dbbbc`, `9a74ca2`, `f21bcae`, `3d4e5d8`, `7b88a69`, `cde92e0`, `b7e7fb7` | Formatos de `registrar()` y registro de los guiones | `prueba_textos_port.py` | No registrado |
| feature | `3d482a8`, `6a050d1`, `d3663fd`, `b043668`, `2ae3d3a` | Integración de infra, fuente, texturas, cadenas y port con `--no-ff` | `make test` y CI | No aplica |
| feature | `0ff568e`, `466e73f`, `c461c5b`, `dda9a5f` | Tilde de un aviso de texturas, guion de recorrido, job `publicar` y commit de publicación | `prueba_textos_port.py`; CI 36518116212 | No aplica |

## Commits de F8

Los commits de `feature/sincronizacion-upstream` sobre `main`, por orden. Las subramas salen de `36fc9e40`; su revisión está en el [acta](revisiones/2026-10-11-sincronizacion.md).

| Commit | Rama | Tipo | Qué hace | Requisito o CC | Prueba | Rojo y mutación |
|---|---|---|---|---|---|---|
| `df07cfa9`, `55cbf083`, `73bb9a8f`, `132d4bf5` | feature | docs | Registro de CC-08 a CC-11 antes del código | CC-08…CC-11 | — | No aplica |
| `9f4d0215` | feature | merge | Fusión del original hasta `ae93f71` con `merge.directoryRenames=false` | CC-08 | `git diff 9f4d0215^1 9f4d0215 -- build compilaciones` y de los 3 archivos de glifos, vacíos | En rojo solo en `prueba_textos_port.py`, como prevé CC-08 |
| `748db117` | feature | test | Palabras de los textos nuevos del original en la lista negra | CC-08, R-PORT-04 | `prueba_textos_port.py` | Comprobado: de 7 a 16 fallos con la fusión |
| `36fc9e40` | feature | fix | Textos nuevos del original en español; grupos `GRUPO_CARGA_CEREMONIA` y `GRUPO_CARGA_CREDITOS` | CC-08, R-PORT-02, R-PORT-04 | `prueba_textos_port.py` | 16 → 0 fallos; mutación «contesto» en `memory_card.c:78`: 1 fallo |
| `409a72b9` | feature | docs | README con multitap, OPL sin reinicio del IOP y 60 FPS del original | CC-08 | — | No aplica |
| `b4b37c13` | feature | docs | CC-10 rechazado; G2 y G4 quedan como propuesta | CC-10, CC-11 | — | No aplica |
| `24ed39a0` | ci | ci | `make DEV=1` en `compilar-ps2`, publicación con tipo `build`, jobs `release` y `limpiar-ramas` | CC-09, R-INF-05, R-GOB-01 | `yaml.safe_load`, `bash -n` y simulación de `limpiar-ramas` en la revisión | No aplica (configuración de la CI) |
| `6251a4a6` | ci | build | `BUILD_ID` 2026-10-11 | CC-09 | — | No aplica |
| `b69f1548` | ci | ci | Tildes en las entradas a pedido y `sí` con tilde | CC-09 | Revisión lingüística | No aplica |
| `1ac5c96f` | feature | merge | Integra `sinc/ci` | — | — | No aplica |
| `ce98830c` | graficos-g5 | fix | G5: el alfa negativo con `G_AC_DITHER` se limita a 0 | CC-11 (G5) | Evidencia de código en el mensaje; sin prueba en el PC ([deuda.md](deuda.md), D-01) | No demostrado |
| `368a5416` | feature | merge | Integra `sinc/graficos-g5` | — | — | No aplica |
| `664d9013` | sistema | test | `inicializar_depuracion()` antes del reinicio del IOP | CC-08, R-PORT-02 | `prueba_arranque.py` | El código ya cumplía: 5 mutaciones de `arranque_ps2.c` en FALLO |
| `176651ed` | sistema | fix | `GRUPOS_MAX` de 4 a 6 | CC-11 (E3), R-PORT-02 | `prueba_cronometro_fases.c` | Comprobado: 5 fallos con 4; mutación a 5: 3 fallos |
| `a86960cf` | sistema | fix | Lectura de la ROM por debajo del perro guardián | CC-11 (E4), R-PORT-01 | Evidencia de código en el mensaje | No aplica (sin arnés de PC) |
| `61a88a74` | sistema | fix | Memory Card que no contesta | CC-11 (E5), R-PORT-01 | Evidencia de código en el mensaje | No aplica (sin arnés de PC) |
| `372f10ed` | sistema | test | Tildes en las salidas de las dos pruebas | — | `prueba_arranque.py`, `prueba_cronometro_fases.c` | Mutaciones con la salida nueva en FALLO |
| `bbb11eb6` | feature | merge | Integra `sinc/sistema` | — | — | No aplica |
| `e600bd6e` | pendientes | test | `lut_textura_glifo` se define una vez, fuera de todo `#if` y sin los alias del original (G1) | CC-08, R-FUE-01 | `prueba_tablas_glifos.py` | El código ya cumplía: mutaciones en FALLO (bloque del original: 11 fallos) |
| `697f3af6` | pendientes | test | El tope de `funcion_80095BD0` es el tamaño de `efecto_mtx` | R-FUE-07 | `prueba_tablas_glifos.py` (`probar_tope_reserva`) | El código ya cumplía: mutación 0x2F7, 1 fallo |
| `9adc3192` | pendientes | fix | Sin matriz libre, la letra no lleva tilde; registro DEV | CC-11 (L2), R-FUE-07 | Evidencia de código en el mensaje | No aplica (sin arnés de PC) |
| `a5e97ddf` | pendientes | test | Detector del primer byte que la fuente no dibuja | R-FUE-05 | `prueba_glifos.c` (`probar_primer_byte_invalido`) | Comprobado: no enlaza; con un sustituto, 11 fallos |
| `f38d6de6` | pendientes | feat | Registro DEV de las cadenas del menú que la fuente no dibuja | R-FUE-05 | `prueba_glifos.c` | Mutaciones: sin C2/C3, 4 fallos; avance de 1, 2; sin guarda del NUL, ASan |
| `94cdfea5` | pendientes | fix | El registro DEV también en `imprimir_texto0` e `imprimir_texto2` | R-FUE-05 | `prueba_tablas_glifos.py` (`probar_registro_texto_invalido`) | Comprobado: 2 fallos; mutación: 1 |
| `27199b8f` | pendientes | test | Tildes en los mensajes nuevos de las pruebas de glifos | — | `prueba_glifos.c`, `prueba_tablas_glifos.py` | Mutaciones con la salida nueva en FALLO |
| `cf956b42` | feature | merge | Integra `sinc/pendientes` | — | — | No aplica |
| `4612a508` | panel | test | Una fila libre entre las líneas del panel 5x7 | CC-11 (L3), R-PORT-02 | `prueba_ancho_panel.py` | Comprobado: 1 fallo |
| `ac4fcdae` | panel | fix | `TEXTO_ALTO_LINEA` 9, textura de 108 filas y 128 KB de VRAM | CC-11 (L3), R-PORT-02 | `prueba_ancho_panel.py` | Mutaciones: alto de línea, VRAM de 112 KB y textura de 104, en FALLO |
| `5d901a47` | panel | test | Ningún `texto_es` del manifiesto nombra botones de la N64 | R-TEX-07 | `prueba_texturas_es.py` (paso 5) | El manifiesto ya cumplía: 4 mutaciones en FALLO |
| `4e4cc6f8` | panel | fix | Tildes en los mensajes de la prueba del panel | — | `prueba_ancho_panel.py` | Mutaciones con la salida nueva en FALLO |
| `240358fd` | feature | merge | Integra `sinc/panel` | — | — | No aplica |
| `d5f95cc5` | feature | docs | CC-12: verificación sin pasos manuales y manual del proyecto | CC-12 | — | No aplica |

No se integraron `sinc/graficos` (salvo G5) ni `sinc/recorrido` (CC-10 rechazado).

## Commits de F9

Los commits de `feature/version-1.1.0` sobre `main` (`af3bfa05`), por orden de integración. Las cinco ramas salen de `5b1caac8`; su revisión está en el [acta de F9](revisiones/2026-10-11-version-1.1.0.md).

| Commit | Rama | Tipo | Qué hace | Requisito o CC | Prueba | Rojo y mutación |
|---|---|---|---|---|---|---|
| `0c39b416`, `111eb2c7`, `33cbcbb3`, `2857317b`, `5b1caac8` | feature | docs | Registro de CC-13 a CC-17 antes del código | CC-13…CC-17 | — | No aplica |
| `ff313bc5` | graficos | refactor | Alfa con tramado en `combinador_alfa_tramado()`, `static inline` en `combinador_color.h` | CC-17 | Arnés de equivalencia fuera del repositorio: 0 diferencias en 614 401 valores | No aplica (refactor) |
| `d41996f7` | graficos | test | Casos del alfa con tramado en `prueba_combinador.c` | CC-17 (D-01, D-02) | `prueba_combinador.c` | Mutación sin el límite a 0: 1 fallo |
| `9289608a` | feature | merge | Integra `v110/graficos` | — | — | No aplica |
| `2e578b4b` | memoria | test | Elección de la copia que se pisa en una tarjeta nueva | CC-13, R-MC-01, R-MC-02 | `prueba_eleccion_guardado.c` | No compila sin la cabecera; con cuerpos vacíos, 14 fallos de 20 |
| `b989feca` | memoria | feat | `eleccion_guardado.h`: copia a pisar y generación mínima | CC-13 | `prueba_eleccion_guardado.c` | Mutaciones: comparación invertida, 6 fallos; sin el +1, 10 |
| `e4937a28` | memoria | fix | Leer la tarjeta nueva antes de guardar en ella | CC-13 | Evidencia de código en el mensaje ([deuda.md](deuda.md), D-16) | No aplica (sin arnés de PC) |
| `41441ae5` | memoria | fix | La espera de la partida al arrancar se mide con `ciclos_ps2()` | CC-13 | Evidencia de código en el mensaje | No aplica (sin arnés de PC) |
| `3e62e63e` | memoria | fix | Segundo borrado solo con `mc_ok` | CC-13 (D-12) | Evidencia de código en el mensaje | No aplica (sin arnés de PC) |
| `abe7c205` | memoria | fix | `type`, `free` y `format` de `mcGetInfo` pasan a `static` | CC-13 (D-13) | Evidencia de código en el mensaje | No aplica (sin arnés de PC) |
| `8c69e253` | memoria | fix | La cabecera B solo se lee si la tarjeta sigue contestando | CC-13 | Evidencia de código en el mensaje | No aplica (sin arnés de PC) |
| `4465f614` | feature | merge | Integra `v110/memoria` | — | — | No aplica |
| `807d2c45` | region | test | Región leída de `rom0:ROMVER` | CC-15, R-PORT-02 | `prueba_region_ps2.c` | No compila sin la cabecera |
| `3b11daa5` | region | feat | `region_ps2.h`: región a partir de ROMVER | CC-15 | `prueba_region_ps2.c` | Mutación de la «A» a PAL: 1 fallo de 16 |
| `ac1a1090` | region | feat | El arranque registra la región de la consola | CC-15, R-PORT-02 | Evidencia de código en el mensaje ([deuda.md](deuda.md), D-17) | No aplica (sin arnés de PC) |
| `d105a89b` | feature | merge | Integra `v110/region` | — | — | No aplica |
| `bb8d41bd` | ci-textos | test | El tope de la reserva de matrices es la condición entera | R-FUE-07 (D-09) | `prueba_tablas_glifos.py` (`probar_tope_reserva`) | Mutación «+ 1»: la prueba anterior pasaba, la nueva da 1 fallo |
| `3e2067a4` | ci-textos | test | `GRUPOS_MAX` deja hueco para los grupos de `marcas_registro.h` | D-10 | `prueba_cronometro_fases.c` | Reproducido por REVISIÓN: con 6 grupos, la anterior da 0 fallos y la nueva 1 |
| `1d8f5670` | ci-textos | fix | El registro del multitap dice «sin multitap» | R-PORT-04 (D-14) | Evidencia de código en el mensaje | No aplica (sin arnés de PC) |
| `7e9edfaa` | ci-textos | fix | El registro del ritmo de física dice «ritmo» en lugar de «3-4P» | R-PORT-04 | Evidencia de código en el mensaje | No aplica (sin arnés de PC) |
| `c641d19b` | ci-textos | ci | Tildes en los textos de `compilacion.yml` | R-INF-05 (D-15) | Revisión lingüística | No aplica |
| `4bdd41a8` | ci-textos | ci | `publicar` no oculta fallos del commit; `release` en el contenedor de ps2dev, con la suma de la ISO comprobada y el ELF monolítico | CC-16, R-INF-05 | Bloques `run:` ejecutados con `sh -e` en el PC | Publicar con un commit que falla: antes salía con 0, ahora con 1 |
| `b780d986` | ci-textos | style | Tildes en el comentario del tope de la reserva | — | `prueba_tablas_glifos.py` | No aplica. Tipo no admitido por R-GOB-01 |
| `12579275` | feature | merge | Integra `v110/ci-textos` | — | — | No aplica |
| `f09697ca` | feature | docs | CC-13, CC-14 y CC-17 ajustados a la revisión | CC-13, CC-14, CC-17 | — | No aplica |
| `1fc4c437` | entrada | refactor | `convertir_eje` pasa a `incluir/entrada/eje_palanca.h` | CC-14 | Caracterización: 0 diferencias en los 256 valores | No aplica (refactor) |
| `4a48ff6a` | entrada | test | Conversión del eje del stick | CC-14 | `prueba_eje_palanca.c` | Con la zona muerta en 24: el giro empieza a 41, 1 fallo |
| `dcbe656e` | entrada | fix | Zona muerta del stick de 24 a 8 | CC-14 | `prueba_eje_palanca.c` | Mutaciones: zona muerta 24, 1 fallo; divisor 128, 1 fallo |
| `ddbdc023` | entrada | test | La cruceta usa su propio umbral de reposo del stick | CC-14 | `prueba_eje_palanca.c` | «'ZONA_REPOSO_CRUCETA' undeclared» |
| `34ab306d` | entrada | fix | La cruceta hace de stick con el stick izquierdo en reposo | CC-14 | `prueba_eje_palanca.c`; `convertir()` revisada a mano ([deuda.md](deuda.md), D-18) | Mutación con `ZONA_MUERTA_PALANCA` en `eje_en_reposo`: 16 fallos |
| `2b37f61f` | entrada | fix | Reposo de la cruceta hasta 25 del centro (`ZONA_REPOSO_CRUCETA` 26) | CC-14 | `prueba_eje_palanca.c` | No registrado aparte; la prueba sigue a la constante |
| `4563d816` | feature | merge | Integra `v110/entrada` | — | — | No aplica |
| `6519d73e` | feature | docs | CC-14 con el reposo de la cruceta hasta 25 del centro | CC-14 | — | No aplica |
| `a29bd920` | feature | build | Las tres pruebas nuevas en `make test` | CC-13, CC-14, CC-15 | `make test` | No aplica |

`ddbdc023`, `34ab306d`, `2b37f61f` y `a29bd920` se revisaron con otros hashes y el mismo parche ([acta de F9](revisiones/2026-10-11-version-1.1.0.md#resumen)).

### Deuda saldada en F9

| Deuda | Commits | Cómo |
|---|---|---|
| D-01, D-02 | `ff313bc5`, `d41996f7` | G5 tiene prueba en el PC: la función pura del alfa con tramado y sus casos en `prueba_combinador.c` (CC-17) |
| D-09 | `bb8d41bd`, `b780d986` | `probar_tope_reserva` exige la condición entera |
| D-10 | `3e2067a4` | `prueba_cronometro_fases.c` cuenta los `#define GRUPO_` |
| D-11 | — | Decisión escrita en [CC-13](cambios.md): se mantiene; si solo vence `mcClose`, la tarjeta queda desactivada y la partida de la sesión sigue en la memoria |
| D-12 | `3e62e63e` | Segundo `mcDelete` solo con `mc_ok` |
| D-13 | `abe7c205` | `type`, `free` y `format` son `static` |
| D-14 | `1d8f5670` | «sin multitap» |
| D-15 | `c641d19b` | «están» y las demás tildes del workflow |

## Commits de F10

Los commits de `feature/version-1.2.0` sobre `main`, por orden de integración. `v120/contrato` sale de `edad2078`; las ramas que usan las opciones del port, de `93cb4d04`, el contrato; `v120/texturas`, de `0081dca5` (CC-28); `v120/texturas-pistas`, de `0f15c448` (CC-29), y las cuatro de texturas traducidas, de `df9aea49`. Su revisión está en el [acta de F10](revisiones/2026-10-11-version-1.2.0.md).

| Commit | Rama | Tipo | Qué hace | Requisito o CC | Prueba | Rojo y mutación |
|---|---|---|---|---|---|---|
| `edad2078` | feature | docs | CC-18 a CC-27 de la versión 1.2.0 | CC-18…CC-27 | — | No aplica |
| `0081dca5` | feature | docs | CC-28, reconstrucción de texturas del HUD y de los menús | CC-28 | — | No aplica |
| `d6bf7381` | contrato | refactor | Mover el CRC32 a una cabecera compartida | CC-18 | `prueba_opciones_port.c` (CRC32 de «123456789») | No aplica (refactor) |
| `a760841b` | contrato | test | Prueba del archivo de opciones del port | CC-18, R-MC-04 | `prueba_opciones_port.c` | No compilaba sin la cabecera |
| `93cb4d04` | contrato | feat | Contrato de las opciones del port y su archivo SMK64CFG.DAT | CC-18, R-MC-04 | `prueba_opciones_port.c` | Mutaciones en el mensaje |
| `226a3ce3` | feature | merge | Integra `v120/contrato` | — | — | No aplica |
| `36796171` | memoria | test | Arnés del PC para memory_card.c con libmc simulada | D-16 | `prueba_memory_card.c` | Mutación sin la guarda `mc_ok`: falla |
| `289e9c78` | memoria | test | Ninguna orden a libmc tras vencer una lectura de la carga | D-21 | `prueba_memory_card.c` | 4 fallos de 62 |
| `2c83c0f8` | memoria | fix | No pedir lecturas ni escrituras con una orden vencida | D-21, R-MC-04 | `prueba_memory_card.c` | Mutación sin la guarda de `leer_archivo_mc`: falla |
| `c94152e0` | memoria | test | El registro del guardado da la generación escrita | D-20 | `prueba_memory_card.c` | 1 fallo de 64 (el registro decía 3) |
| `c69d9ef4` | memoria | fix | Registrar la generación que se escribe en la tarjeta | D-20 | `prueba_memory_card.c` | — |
| `b38d42c4` | memoria | docs | Corregir «más que lo pedido» en un comentario | D-22 | Revisión lingüística | No aplica |
| `2275f2c8` | memoria | refactor | Sacar la creación de la carpeta a preparar_carpeta() | CC-18 | `prueba_memory_card.c` | No aplica (refactor) |
| `098af916` | memoria | test | Archivo de opciones del port en el hilo de guardado | CC-18, R-MC-04 | `prueba_memory_card.c` | No compilaba sin `ARCHIVO_OPCIONES` |
| `8c022b34` | memoria | feat | Leer y guardar SMK64CFG.DAT en el hilo de guardado | CC-18, R-MC-04 | `prueba_memory_card.c`: 83 comprobaciones | Mutación en el mensaje |
| `1727504e` | memoria | docs | Anotar que D-21 corta toda orden a una tarjeta que no contesta | D-21 | — | No aplica |
| `d7e296f9` | memoria | docs | Explicar la guarda de cargar_opciones y la pérdida del pedido de opciones | CC-18 | — | No aplica |
| `48e951fc` | feature | merge | Integra `v120/memoria` | — | — | No aplica |
| `deeba019` | imagen | test | Prueba de los registros del PCRTC según las opciones de imagen | CC-20, CC-21, R-VID-01…R-VID-03 | `prueba_registros_video.c` | No compilaba sin la cabecera |
| `fa835b62` | imagen | feat | Cálculo puro de PMODE, DISPFB2 y DISPLAY según las opciones de imagen | CC-20, CC-21, R-VID-01…R-VID-03 | `prueba_registros_video.c` | Mutaciones en el mensaje |
| `9173dde8` | imagen | feat | El GS aplica el antiparpadeo, la posición y las bandas | CC-20, CC-21 | Job `emulador` (registro de vídeo) | No aplica (solo compila con el SDK; evidencia de código en el mensaje) |
| `064830d8` | imagen | test | Prueba del aspecto y del cono de la vista panorámica | CC-21, R-VID-04 | `prueba_vista_panoramica.c` | No compilaba sin la cabecera |
| `92c1f1f3` | imagen | feat | Aspecto y cono de visibilidad de la vista panorámica | CC-21, R-VID-04 | `prueba_vista_panoramica.c` | Mutaciones en el mensaje |
| `fd4286e3` | imagen | feat | La vista de cada pantalla usa el aspecto panorámico | CC-21, R-VID-04 | Job `emulador` | No aplica (solo compila con el SDK; evidencia de código en el mensaje) |
| `c52e2f8d` | imagen | feat | Aspecto panorámico al cambiar de pantalla y cono de objetos más ancho | CC-21, R-VID-04 | Job `emulador` | No aplica (solo compila con el SDK; evidencia de código en el mensaje) |
| `761d735d` | imagen | feat | La cámara de la ceremonia usa el aspecto panorámico | CC-21, R-VID-04 | Job `emulador` | No aplica (solo compila con el SDK; evidencia de código en el mensaje) |
| `2093202d` | imagen | fix | El registro de vídeo nombra el área visible en español | CC-20 | Revisión lingüística | No aplica |
| `d8ebb3ac` | imagen | test | Comprobar las bandas con bases de MAGH 0 y 1 | CC-21, R-VID-03 | `prueba_registros_video.c` | 4 fallos de 66 |
| `d5ee5381` | imagen | fix | No desbordar MAGH al calcular las bandas | CC-21, R-VID-03 | `prueba_registros_video.c` | Sin la protección frente a cero: falla |
| `9b206935` | feature | merge | Integra `v120/imagen` | — | — | No aplica |
| `7abb1f92` | menu | test | Prueba de la navegación del menú de configuración y trucos | CC-19, R-VID-05 | `prueba_menu_configuracion.c` | No compilaba sin la cabecera |
| `7c5439e4` | menu | feat | Lógica pura del menú de configuración y trucos | CC-19, R-VID-05 | `prueba_menu_configuracion.c`: 55 comprobaciones | Mutaciones en el mensaje; salto del 13: 5 fallos |
| `b8954cee` | menu | test | Textos y lugares del menú de configuración y trucos | CC-19, R-TXT-03, R-TXT-04 | Pruebas de textos y de lugares | Los textos nuevos no existían |
| `146b23af` | menu | feat | Menú CONFIGURACIÓN Y TRUCOS en OPCIONES | CC-19, R-VID-05 | Pruebas de textos; job `emulador` (captura del menú) | — |
| `be1248ff` | menu | docs | Anota en CC-19 la alineación del valor que se aparta de la maqueta | CC-19 | — | No aplica |
| `8a62d5a1` | feature | merge | Integra `v120/menu` | — | — | No aplica |
| `9d310c2c` | trucos | test | Prueba del truco DESBLOQUEAR TODO | CC-22, R-TRU-01 | `prueba_trucos.c` | No compilaba sin la cabecera |
| `be355571` | trucos | feat | Truco DESBLOQUEAR TODO | CC-22, R-TRU-01 | `prueba_trucos.c` | Mutaciones en el mensaje |
| `4efcf0be` | trucos | test | Prueba del truco OBJETO | CC-23, R-TRU-02 | `prueba_truco_objeto.c` | No compilaba sin la cabecera |
| `5a19ff97` | trucos | feat | Truco OBJETO | CC-23, R-TRU-02 | `prueba_truco_objeto.c` | Mutaciones en el mensaje |
| `038c39c0` | trucos | test | Prueba del truco 200CC | CC-24, R-TRU-03 | `prueba_cilindrada_200cc.c` | No compilaba sin la cabecera |
| `c80fe61e` | trucos | feat | Truco 200CC | CC-24, R-TRU-03 | `prueba_cilindrada_200cc.c` | Mutación 37/32: falla |
| `0e75a425` | trucos | test | Prueba del truco RIVALES SIN VENTAJA | CC-25, R-TRU-04 | `prueba_rivales_sin_ventaja.c` | No compilaba sin la cabecera |
| `f46bc633` | trucos | feat | Truco RIVALES SIN VENTAJA | CC-25, R-TRU-04 | `prueba_rivales_sin_ventaja.c` | Mutaciones en el mensaje |
| `a6397211` | trucos | fix | Quitar la escritura sin efecto del empuje en el truco 200CC | CC-24 | `prueba_cilindrada_200cc.c` | No aplica (solo compila con el SDK; evidencia de código en el mensaje) |
| `4c0323bf` | trucos | fix | Respetar al rival designado con RIVALES SIN VENTAJA | CC-25 | `prueba_rivales_sin_ventaja.c` | No aplica (solo compila con el SDK; evidencia de código en el mensaje) |
| `159c4396` | feature | merge | Integra `v120/trucos` | — | — | No aplica |
| `0c962092` | deudas | test | ROMVER válido leído con 13 bytes da región desconocida | D-19 | `prueba_region_ps2.c` | Mutación `largo < 5`: falla |
| `00b25b9d` | deudas | docs | Corrige «así que» en el comentario del combinador | D-22 | Revisión lingüística | No aplica |
| `9a92bc41` | deudas | test | El resumen final dice «1 fallo» en singular | D-22 | Las pruebas en C | — |
| `e0f76493` | deudas | test | Casos de quién manda, la cruceta o el stick | D-18 | `prueba_eje_palanca.c` | No enlazaba sin `cruceta_manda_stick` |
| `bd70c399` | deudas | feat | Cruceta_manda_stick decide si la cruceta hace de stick | D-18 | `prueba_eje_palanca.c` | Mutación que solo mira el eje x: falla |
| `3d67d29d` | deudas | refactor | Convertir() usa cruceta_manda_stick | D-18 | `prueba_eje_palanca.c` | No aplica (refactor) |
| `e16f26d8` | deudas | test | Prueba estática del tope de efecto_mtx | D-08, R-FUE-09 | `prueba_reserva_matrices.py` | Falla en los seis sitios sin tope |
| `93231a07` | deudas | fix | Los menús no escriben efecto_mtx con la reserva llena | D-08, R-FUE-09 | `prueba_reserva_matrices.py` | — |
| `64805e8c` | deudas | fix | Globos y partículas no escriben efecto_mtx con la reserva llena | D-08, R-FUE-09 | `prueba_reserva_matrices.py` | — |
| `a989c0f5` | deudas | fix | El kart no escribe efecto_mtx con la reserva llena | D-08, R-FUE-09 | `prueba_reserva_matrices.py` | — |
| `d2ce4c18` | deudas | fix | Los fuegos artificiales no escriben efecto_mtx con la reserva llena | D-08, R-FUE-09 | `prueba_reserva_matrices.py` | Mutación sin el tope de `funcion_80280A28`: 1 fallo |
| `b06d4cbe` | deudas | test | A_cp437 pasa el español a los glifos CP437 de libdebug | D-07, R-PORT-03 | `prueba_caracteres_es.c` | No compilaba sin `a_cp437` |
| `8e311363` | deudas | feat | A_cp437 da el código CP437 de las letras con glifo | D-07, R-PORT-03 | `prueba_caracteres_es.c` | Mutación que cruza ñ y Ñ: 3 fallos |
| `278f45a5` | deudas | test | Scr_putchar en la pantalla de fallo exige a_cp437 antes | D-07, R-PORT-03 | `prueba_textos_port.py` | Falla sin `a_cp437` antes de `scr_putchar` |
| `ab75b9aa` | deudas | feat | La pantalla de fallo escribe con tildes mediante scr_putchar | D-07, R-PORT-03 | `prueba_textos_port.py`; paso «Fuente de libdebug» | Mutación en el mensaje |
| `0f75b754` | deudas | test | Make test ejecuta la prueba de la reserva de matrices | D-08, R-FUE-09 | `make test` | No aplica |
| `dc6d4730` | deudas | test | La prueba de la reserva exige que el tope sume las matrices de más | D-08, R-FUE-09 | `prueba_reserva_matrices.py`: 20 comprobaciones | Sin el + 1 la prueba anterior pasaba; la nueva falla |
| `3a30f145` | deudas | docs | Deuda de la partícula dibujada con la matriz anterior | D-23 | — | No aplica |
| `6e6a2108` | feature | merge | Integra `v120/deudas` | — | — | No aplica |
| `fee9830b` | manifiesto | test | Filas de carpeta y cobertura de R-TEX-02 en el manifiesto | D-05, R-TEX-02 | `prueba_texturas_es.py` | `AttributeError`: faltaba `leer_carpetas` |
| `22fbc484` | manifiesto | feat | Filas de carpeta en el manifiesto de texturas | D-05, R-TEX-02 | `prueba_texturas_es.py` | — |
| `9032ab75` | manifiesto | feat | Exclusiones de carpeta sin texto en el manifiesto | D-05, R-TEX-02 | `prueba_texturas_es.py` | — |
| `7638072f` | manifiesto | test | Carpetas con texto aún sin cubrir en R-TEX-02 | D-05, R-TEX-02 | `prueba_texturas_es.py` | — |
| `de397d10` | manifiesto | fix | Motivo coherente para la carpeta de Toad's Turnpike | D-05 | `prueba_texturas_es.py` | No aplica |
| `742d480c` | manifiesto | refactor | Leer el manifiesto una sola vez al validar las carpetas | D-05 | `prueba_texturas_es.py` | No aplica (refactor) |
| `d57a6bef` | manifiesto | docs | Alcance recursivo de las filas de carpeta en el docstring | D-05 | — | No aplica |
| `c3e1d30e` | feature | merge | Integra `v120/manifiesto` | — | — | No aplica |
| `3b5e4aef` | texturas | test | El borde de las palabras del HUD solo lleva contorno | CC-28, R-TEX-05 | `prueba_hud_es.py` | Rojo con VUELTA |
| `d7b3feb9` | texturas | fix | VUELTA termina con contorno en el borde derecho | CC-28, R-TEX-05 | `prueba_hud_es.py` | PNG anterior de VUELTA: falla |
| `2175d03b` | texturas | fix | El «º» de los puestos volado, relleno e inclinado como las cifras | CC-28, R-TXT-07 | `prueba_composicion_es.py` | — |
| `9d9ac85e` | texturas | fix | Letra pequeña con contorno oscuro y sin placa en los botones de dos líneas | CC-28, R-TEX-04 | `prueba_composicion_es.py` | — |
| `bace922a` | texturas | fix | El título de la Jungla DK cabe sin montar las letras | CC-28, R-TEX-04 | `prueba_composicion_es.py` | — |
| `b7b03ee3` | feature | merge | Integra `v120/texturas` | — | — | No aplica |
| `7491fd24` | ci-emulador | test | Prueba de la comparación de capturas del emulador | CC-26, R-INF-07 | `prueba_comparar_capturas.py` | `ModuleNotFoundError` |
| `98a042b7` | ci-emulador | feat | Comparación de las capturas del emulador con sus referencias | CC-26, R-INF-07 | `prueba_comparar_capturas.py` | Mutación del umbral: 2 fallos |
| `a7bae5d4` | ci-emulador | test | Prueba de la revisión del registro del emulador | CC-26, R-INF-07 | `prueba_comprobar_registro.py` | `ModuleNotFoundError` |
| `570a0a12` | ci-emulador | feat | Revisión del registro y del guion del emulador | CC-26, R-INF-07 | `prueba_comprobar_registro.py` | Mutación sin mirar el cuelgue: falla |
| `99fa9b5c` | ci-emulador | test | Prueba del tope de crecimiento de la ROM | D-03, R-TEX-03 | `prueba_tope_rom.py` | `ModuleNotFoundError` |
| `a27fd80f` | ci-emulador | feat | Tope de crecimiento de la ROM en compilar-ps2 | D-03, R-TEX-03, R-INF-05 | `prueba_tope_rom.py` | Mutación que admite el límite exacto: falla |
| `2c3a8b29` | ci-emulador | ci | Job que arranca el ELF de DEV en Play! con un guion | CC-26, R-INF-05, R-INF-07 | Ejecución de la CI | No aplica |
| `04adf1f6` | ci-emulador | ci | Build incremental real sin una sustitución del HUD | D-04, R-TEX-08, R-INF-05 | Ejecución de la CI | No aplica |
| `f48b7a41` | ci-emulador | test | Prueba de la inspección de la fuente de libdebug | D-07, R-PORT-03 | `prueba_fuente_libdebug.py` | `ModuleNotFoundError` |
| `68bc6dce` | ci-emulador | feat | Inspección de la fuente de libdebug en compilar-ps2 | D-07, R-PORT-03, R-INF-05 | `prueba_fuente_libdebug.py` | Un bit cambiado en la ñ: falla |
| `10f290a3` | feature | merge | Integra `v120/ci-emulador` | — | — | No aplica |
| `91c7254e` | feature | feat | Aplicar DESBLOQUEAR TODO al reconstruir cada pantalla de menú | CC-22, R-TRU-01 | `prueba_trucos.c`; job `emulador` | No aplica (solo compila con el SDK; evidencia de código en el mensaje) |
| `3bbac652` | feature | fix | Las opciones quedan escritas antes de subir su versión | CC-18 | Revisión del código | No aplica (solo compila con el SDK; evidencia de código en el mensaje) |
| `3cf36394` | feature | test | Las pruebas de la versión 1.2.0 en make test | CC-18…CC-27 | `make test` | No aplica |
| `979fcf14` | feature | ci | Exigir en el registro los valores de vídeo por defecto | CC-20, CC-26, R-VID-01, R-INF-07 | Ejecución de la CI | No aplica |
| `0f15c448` | feature | docs | CC-29, clasificación de las texturas sin revisar | CC-29 | — | No aplica |
| `a6fa679e` | texturas-pistas | test | Vaciar PENDIENTES y aceptar filas de archivo suelto (CC-29) | CC-29, R-TEX-02 | `prueba_texturas_es.py` | Falla con `PENDIENTES` sin clasificar |
| `4216877e` | texturas-pistas | feat | Clasificar las texturas sin revisar de R-TEX-02 en el manifiesto (CC-29) | CC-29, R-TEX-02 | `prueba_texturas_es.py` | — |
| `431c3186` | texturas-pistas | feat | Separar las filas de archivo (archivo:) de las de carpeta (CC-29) | CC-29, R-TEX-02 | `prueba_texturas_es.py` | — |
| `df9aea49` | texturas-pistas | test | Contar las texturas pendientes y registrarlas como deuda D-24 (CC-29) | CC-29, R-TEX-02 (D-24) | `prueba_texturas_es.py` | — |
| `616213c8` | feature | merge | Integra `v120/texturas-pistas` | — | — | No aplica |
| `fe010d2a` | tx-bienvenida | test | Exigir el cartel de bienvenida en español (BIENVE / NIDOS) | CC-29, R-TEX-02 (D-24) | `prueba_texturas_es.py`; `prueba_composicion_es.py` | Falla con el cartel en inglés |
| `cb32c871` | tx-bienvenida | feat | Cartel de bienvenida en español (BIENVE / NIDOS) | CC-29 (D-24) | `prueba_texturas_es.py` | Mutación del PNG: falla |
| `3017fe10` | feature | merge | Integra `v120/tx-bienvenida` | — | — | No aplica |
| `bb31482f` | tx-ya | test | Bajar a 14 las texturas pendientes por el cartel YA de Mario Raceway | CC-29, R-TEX-02 (D-24) | `prueba_texturas_es.py` | `TEXTURAS_PENDIENTES` a 15: falla dentro de `make test` |
| `3505ff26` | tx-ya | feat | Traducir a YA el cartel GO de Mario Raceway con la Y y la A dibujadas en su fuente | CC-29 (D-24) | `prueba_texturas_es.py` | — |
| `a087fc2a` | feature | merge | Integra `v120/tx-ya` | — | — | No aplica |
| `bc4516de` | tx-emblemas | test | Exigir ci8 con su paleta y bajar las pendientes a 11 por los emblemas 1J a 4J (CC-29) | CC-29, R-TEX-02 (D-24) | `prueba_texturas_es.py` | — |
| `caf7756f` | tx-emblemas | feat | Traducir los emblemas 1P a 4P a 1J a 4J con ci8 y su paleta (CC-29) | CC-29 (D-24) | `prueba_texturas_es.py` | PNG de 1J sobre el de 2J: falla |
| `56401560` | feature | merge | Integra `v120/tx-emblemas` | — | — | No aplica |
| `f7866dd3` | tx-cruce | test | Exigir PASO / A NIVEL en diagonal en las señales de cruce y bajar a 7 las texturas pendientes | CC-29, R-TEX-02 (D-24) | `prueba_texturas_es.py` | — |
| `625105f4` | tx-cruce | feat | Traducir a PASO / A NIVEL la cruz de San Andrés de Kalimari Desert | CC-29 (D-24) | `prueba_texturas_es.py` | — |
| `fd6a4bb7` | feature | merge | Integra `v120/tx-cruce` | — | — | No aplica |

`91c7254e`, `3bbac652`, `3cf36394` y `979fcf14` son de INTEGRACIÓN: resuelven hallazgos de la revisión que pedían tocar zonas compartidas ([acta de F10 §12](revisiones/2026-10-11-version-1.2.0.md#12-integración)).

### Deuda saldada en F10

| Deuda | Commits | Cómo |
|---|---|---|
| D-03 | `99fa9b5c`, `a27fd80f` | Paso «Tope de crecimiento de la ROM» en `compilar-ps2`: falla si `rom.bin` crece 256 KiB o más sobre `main` |
| D-04 | `04adf1f6` | Paso «Build incremental sin una sustitución» en `compilar-ps2` |
| D-05 | `fee9830b`, `22fbc484`, `9032ab75`, `7638072f`, `de397d10`, `742d480c`, `d57a6bef`; CC-29: `a6fa679e`, `4216877e`, `431c3186` | Filas `carpeta:` y `archivo:`; `PENDIENTES` vacía y 1229 texturas clasificadas |
| D-06 | `2c3a8b29`, `570a0a12`, `98a042b7`, `979fcf14` | El job `emulador` arranca el juego y compara capturas; lo que no ve pasa a los [límites declarados](especificacion.md#9-límites-declarados) |
| D-07 | `b06d4cbe`, `8e311363`, `278f45a5`, `ab75b9aa`, `f48b7a41`, `68bc6dce` | Pantalla de fallo con tildes mediante `scr_putchar` y `a_cp437`; la CI inspecciona la fuente de libdebug |
| D-08 | `e16f26d8`, `93231a07`, `64805e8c`, `a989c0f5`, `d2ce4c18`, `0f75b754`, `dc6d4730` | Tope de `efecto_mtx` en los seis sitios (R-FUE-09) |
| D-16 | `36796171` | Arnés del PC con libmc simulada (`prueba_memory_card.c`) |
| D-17 | `570a0a12` | El job `emulador` exige la línea de región con un ROMVER sintético, por la ruta con reinicio del IOP; el resto pasa a los [límites declarados](especificacion.md#9-límites-declarados) |
| D-18 | `e0f76493`, `bd70c399`, `3d67d29d` | `cruceta_manda_stick()`, función pura con prueba |
| D-19 | `0c962092` | Caso de largo 13 en `prueba_region_ps2.c` |
| D-20 | `c94152e0`, `c69d9ef4` | El registro da la generación escrita |
| D-21 | `289e9c78`, `2c83c0f8`, `1727504e` | Ninguna orden a libmc después de una vencida |
| D-22 | `00b25b9d`, `b38d42c4`, `9a92bc41` | «así que», «más de lo pedido», «como sale de fread()» y «1 fallo» en singular |
| D-24 | `bb31482f`, `3505ff26`, `fe010d2a`, `cb32c871`, `bc4516de`, `caf7756f`, `f7866dd3`, `625105f4` | YA, BIENVENIDOS, 1J a 4J y PASO A NIVEL; `TEXTURAS_PENDIENTES` en 0 |
| D-23 | `076e7cc2`, `041eb862` | `funcion_800652D4` devuelve si cargó la matriz y sus 30 llamadores se saltan el dibujo si no; `prueba_reserva_matrices.py` lo exige |
| D-25 | `e1a3d746`, `ecc00c42` | `prueba_textos_port.py` vigila que código, cabeceras y herramientas no citen identificadores de requisito ni de deuda; se limpiaron 24 líneas |

## Commits de F11

Los commits de `feature/capturas-1.2.1` sobre `main`, en orden. `v121/capturas` y `v121/ordinal` salen de `8d94ba8d` (registro de CC-31); `v121/ordinal` se integra con un merge `--no-ff`. Su revisión está en el [acta de la 1.2.1](revisiones/2026-10-11-version-1.2.1.md).

| Commit | Rama | Tipo | Qué hace | Requisito o CC | Prueba | Rojo y mutación |
|---|---|---|---|---|---|---|
| `8d94ba8d` | feature | docs | CC-31, capturas de referencia al día y comparación estricta | CC-31 | — | No aplica |
| `1bac15d9` | capturas | test | Un bloque de 32×16 cambiado debe fallar con la tolerancia por defecto | CC-31, R-INF-07 | `prueba_comparar_capturas.py` | Falla con la tolerancia de 0,02 |
| `632050ac` | capturas | fix | Tolerancia por defecto de 0,001 en la comparación de capturas | CC-31, R-INF-07 | `prueba_comparar_capturas.py` | Rojo con 0,02 en `1bac15d9`; la revisión repitió la mutación |
| `a7ab8019` | capturas | feat | Captura del menú CONFIGURACIÓN Y TRUCOS en el guion de la CI | CC-31, R-INF-07 | Ejecución de la CI | No aplica |
| `3a022b42` | capturas | test | Referencias regeneradas con Play! 0.72 y el ELF de DEV actual | CC-31, R-INF-07 | Ejecución de la CI y revisión a ojo | No aplica |
| `f4b86834` | capturas | docs | Capturas al día y figura del menú de configuración en la página | CC-31 | — | No aplica |
| `a5464408` | capturas | fix | Valores de CONFIGURACIÓN Y TRUCOS en amarillo opaco | CC-31, CC-19 | `prueba_menu_configuracion.c` | La prueba fija `CONFIG_COLOR_VALOR` a `AMARILLO_TEXTO` |
| `9ec3b950` | ordinal | test | Exige el punto del ordinal antes de la o volada | CC-31, R-TEX-04 | `prueba_hud_es.py` | Falla con «8º.» |
| `33979fbf` | ordinal | fix | Punto del ordinal antes de la o volada (8.º) | CC-31, R-TEX-04 | `prueba_hud_es.py` | — |
| `73aff9e2` | feature | merge | Integra `v121/ordinal` | — | — | No aplica |
| `17901393` | capturas | ci | Opción para regenerar las referencias en la propia CI | CC-31, R-INF-05, R-INF-07 | Ejecución de la CI | No aplica |
| `6933dd08` | capturas | test | Referencias regeneradas en la CI ([38179540046](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38179540046)) | CC-31, R-INF-07 | Segunda ejecución contra ellas | No aplica |
| `39bb214b` | capturas | test | Los valores de CONFIGURACIÓN Y TRUCOS se alinean a la derecha a mano | CC-31, CC-19 | `prueba_menu_configuracion.c` | No compila sin `config_columna_valor` |
| `42a13caf` | capturas | fix | Valores de CONFIGURACIÓN Y TRUCOS en el modo opaco de las etiquetas | CC-31, CC-19 | `prueba_menu_configuracion.c` | Suma en lugar de resta: 1 fallo |
| `863cbc45` | capturas | test | Referencias regeneradas en la CI ([38180265814](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38180265814)) | CC-31, R-INF-07 | Segunda ejecución contra ellas | No aplica |

## Requisitos

| Requisito | Prueba | Commits | Estado | Evidencia |
|---|---|---|---|---|
| R-FUE-01 Tabla de glifos completa | `prueba_tablas_glifos.py`; `prueba_glifos.c` (`probar_compatibilidad`) | `4e35120`, `1c9545d`, `5718601`; F8: `e600bd6e` | hecho | CI n.º 7 y n.º 8; rojo comprobado. Desde `e600bd6e`, la tabla no puede volver a la forma del original (CC-08) |
| R-FUE-02 Compatibilidad N64 | `prueba_glifos.c` (`probar_compatibilidad`) | `d87d14f` | hecho | CI n.º 6 |
| R-FUE-03 JIS X 0212 de 3 bytes | `prueba_convertir_eucjp.py`; `prueba_glifos.c` (`probar_espanol`); `prueba_caracteres_es.c` | `727c7ed`, `9e6bec7`, `641fe27` | hecho | CI n.º 8; rojo comprobado en `641fe27` |
| R-FUE-04 `leer_glifo` única regla de avance | huella de R-FUE-02; `git grep` en la revisión | `d87d14f` | hecho | `git grep -n 'indice_glifo >= 0x30' -- codigo/menus/` vacío en `dda9a5f` |
| R-FUE-05 Robustez ante -2 | `prueba_glifos.c` (`probar_secuencias_rotas`, `probar_primer_byte_invalido`); `prueba_tablas_glifos.py` (`probar_registro_texto_invalido`) | `641fe27`; F8: `a5e97ddf`, `f38d6de6`, `94cdfea5` | hecho | Registro DEV en las tres impresoras; rojo y mutaciones en los mensajes de F8 |
| R-FUE-06 Anchos | `prueba_glifos.c` (`probar_anchos_espanol`); `prueba_tablas_glifos.py` | `5718601`, `641fe27` | hecho | CI n.º 8 |
| R-FUE-07 Diacrítico con la matriz de la letra y tope del pool | `prueba_tablas_glifos.py` (`probar_partes_de_signo`, `probar_tope_reserva`); CI | `dcc0914`, `5718601`; F8: `697f3af6`, `9adc3192`; F9: `bb8d41bd` (D-09) | hecho (CC-12: sin recorrido F6) | CI n.º 7 y 36518116212. L2 ([CC-11](cambios.md)) con evidencia de código en `9adc3192` |
| R-FUE-08 Arte reproducible | `prueba_glifos_es.py` | `9abb8d7`, `5718601` | hecho | CI n.º 7 |
| R-FUE-09 Tope de `efecto_mtx` en todos los sitios | `prueba_reserva_matrices.py` | `e16f26d8`, `93231a07`, `64805e8c`, `a989c0f5`, `d2ce4c18`, `0f75b754`, `dc6d4730` | hecho; la partícula con la matriz anterior queda en [deuda.md](deuda.md) (D-23) | 20 comprobaciones; mutación sin el + 1 detectada ([CC-27](cambios.md)) |
| R-TXT-01 Español según el glosario | `prueba_textos.c` (lista negra) | B1–B7 (ver «Commits de F4») | hecho | `TABLAS_PENDIENTES` = 0; rojo en `da631b0` |
| R-TXT-02 Número y orden de entradas | `prueba_textos.c` (`prueba_textos_tablas.inc.c`) | `ae9dc3c` y B1–B7 | hecho | `make test` en `dda9a5f` |
| R-TXT-03 Glifo para todo carácter | `prueba_textos.c` | `ae9dc3c` y B1–B7 | hecho | `make test` en `dda9a5f` |
| R-TXT-04 Ancho por tinta y zona segura | `prueba_textos.c` (`prueba_textos_lugares.inc.c`, `prueba_textos_tinta.py`) | `330e2d9`, `5b21e3e`, `b061832`, `23055c5` | hecho (CC-12: sin captura en TV, D-06) | Mutación de `23055c5` en `da631b0`; [CC-01](cambios.md) |
| R-TXT-05 Interlineado | `prueba_textos.c` (`probar_interlineado`) | `ae9dc3c` | hecho | [CC-02](cambios.md) |
| R-TXT-06 Textos esperados byte a byte | `prueba_textos.c` (`prueba_textos_esperados.inc.c`) | B1–B7 | hecho | Rojo en `da631b0` |
| R-TXT-07 Ordinales «1.º» | `prueba_textos.c`; `prueba_texturas_es.py`; `prueba_hud_es.py` | `f8bf7b5`, `d28f950`, `a4676b3` | hecho (CC-12: sin captura F6) | Rojo de `f8bf7b5` en `da631b0`; rojo y mutación de `d28f950` en su mensaje |
| R-TXT-08 Botones y puertos de PS2 en cadenas | `prueba_textos.c` | `88e159b` | hecho | «CRUZ*VER DATOS  CUADRADO*SALIR» en `textos_menu.inc.c` |
| R-MC-01 MEMORY CARD, sin Controller Pak | `prueba_textos.c`; F9: `prueba_eleccion_guardado.c`; F10: `prueba_memory_card.c` | `88e159b`; F9: `2e578b4b`…`8c69e253` ([CC-13](cambios.md)); F10: `36796171`, `289e9c78`, `2c83c0f8` | hecho | Rojo en `da631b0`: 331 fallos. F9: una tarjeta nueva no pisa la copia más nueva. F10: arnés del PC con libmc simulada (D-16, D-21) |
| R-MC-02 Ranura 1/2 | `prueba_textos.c`; F9: `prueba_eleccion_guardado.c` | `88e159b`; F9: `2e578b4b`, `b989feca`, `e4937a28` ([CC-13](cambios.md)) | hecho | Esperados de `dato_800E78*`. F9: rojo y mutaciones de la elección de copia en los mensajes |
| R-MC-03 Opción copiar honesta | `prueba_textos.c`; `git diff` de `tablas_menus.inc.c` | `88e159b` | hecho (CC-12: sin captura F6) | Esperados «COPIAR FANTASMAS DESDE / OTRA MEMORY CARD NO / ESTÁ DISPONIBLE EN PS2» |
| R-MC-04 Archivo de opciones del port | `prueba_opciones_port.c`; `prueba_memory_card.c` | `d6bf7381`, `a760841b`, `93cb4d04`, `098af916`, `8c022b34`, `3bbac652` | hecho; el cambio de tarjeta en caliente es un límite declarado | 83 comprobaciones en `prueba_memory_card.c` ([CC-18](cambios.md)) |
| R-TEX-01 Despacho por firma | `prueba_textura_menu.c`; `prueba_tkmk00.py` | `9f9beac`, `2ff6bf0` | hecho | CI n.º 9 |
| R-TEX-02 Manifiesto completo | `prueba_texturas_es.py` | `4345598`, `37633d3`, `31eaf62`; F10: `fee9830b`, `22fbc484`, `9032ab75`, `7638072f`, `a6fa679e`, `4216877e`, `431c3186`, `df9aea49` y las traducciones de D-24 | hecho | 1229 texturas clasificadas; `PENDIENTES` vacía y `TEXTURAS_PENDIENTES` en 0 ([CC-27](cambios.md), [CC-29](cambios.md)) |
| R-TEX-03 Tamaños desde el manifiesto; PULSA START crudo | `prueba_cableado_es.py`; `prueba_cartel_es.py`; F10: `prueba_tope_rom.py` y el paso de `compilar-ps2` | `37633d3`, `78b7177`, `c86be95`; F10: `99fa9b5c`, `a27fd80f` | hecho | `rom.bin` + 6 144 B en `dda9a5f`; tope comprobado en la CI de F10 |
| R-TEX-04 PNG fuente y reproducibilidad | `prueba_png_simple.py`; `prueba_formatos_textura.py`; `prueba_texturas_es.py`; `prueba_composicion_es.py` | `1ee6041`, `a7e918e`, `4345598`, `03e5967` y el arte | hecho | `make test` en `dda9a5f` |
| R-TEX-05 HUD sin solapamiento | `prueba_hud_es.py`; hoja del HUD | `7e0d345`, `a4676b3` | hecho (CC-12: sin capturas F6) | [CC-03](cambios.md), [CC-07](cambios.md) |
| R-TEX-06 Lakitu: 16 cuadros y paleta | `prueba_lakitu_es.py`; tira de 16 cuadros | `74cbaf6`, `44cc3fb` | hecho | Textos de reserva de `lakitu.tsv` |
| R-TEX-07 Botones de PS2 | `prueba_texturas_es.py` (paso 5); `prueba_composicion_es.py` (PNG = texto del manifiesto) | `788a957`; F8: `5d901a47` | hecho | `SELECT|OPCIONES` y `R1|DATOS` en el manifiesto; 4 mutaciones en FALLO en `5d901a47` |
| R-TEX-08 Superposición sin mezcla | `prueba_invertir_texturas.py`; `prueba_hud_es.py`; F10: paso «Build incremental sin una sustitución» | `fdd6a54`, `7e0d345`, `a4676b3`, F10: `04adf1f6` | hecho | Build incremental real en la CI de F10 (D-04) |
| R-PORT-01 Fuente 5x7 | `prueba_fuente_5x7.c` | `3db4b80`, `82858b4` | hecho | `make test` en `dda9a5f` |
| R-PORT-02 Panel, audio y fases en español | `prueba_fuente_5x7.c`; `prueba_textos_port.py`; `prueba_ancho_panel.py`; F9: `prueba_region_ps2.c` | `0af8ebe`, `ead3e9d`, `ac10246`, `1bc10ba`, `7653639`; F8: `36fc9e40`, `4612a508`, `ac4fcdae`; F9: `807d2c45`, `3b11daa5`, `ac1a1090` | hecho (CC-12: sin capturas F6) | CUADRO, RESERVA, VÉRT y MÚSICA en el código; fila libre entre líneas del panel (L3, [CC-11](cambios.md)); registro de la región de la consola ([CC-15](cambios.md)), sin verificar en consola real ([deuda.md](deuda.md), D-17) |
| R-PORT-03 Pantalla de fallo | `prueba_caracteres_es.c`; `prueba_textos_port.py`; `prueba_fuente_libdebug.py` | `9e6bec7`, `0c05c15`, `ba66cf9`; F10: `b06d4cbe`, `8e311363`, `278f45a5`, `ab75b9aa`, `f48b7a41`, `68bc6dce` | hecho | Puerta G-FALLO en la CI de F10 (D-07). La captura se retiró (CC-12) |
| R-PORT-04 Marcas del registro | `prueba_textos_port.py`; revisión lingüística | `9d2b711`, `91b2a89`, `823a0c8` y los formatos de `registrar()`; F8: `748db117`, `36fc9e40`; F9: `1d8f5670`, `7e9edfaa` | hecho | [CC-05](cambios.md); los textos nuevos del original, en español ([CC-08](cambios.md)); F9: «sin multitap» y «ritmo» en lugar de «3-4P» |
| R-PORT-05 Fuente de depuración N64 | `prueba_textos.c`; `prueba_cadena_depuracion.c` | `9e6bec7`, `40ed241`, `37cf760`, `ab920e9`, `26a0bbc`, `32c2a6f` | hecho | Rojo de `ab920e9` en `da631b0`; mutación de `29541a4` en `da631b0` |
| R-INF-01 Objetivos del PC sin SDK | job `pruebas-pc` | `f8f9a39`, `37633d3`, `a0da3a1` | hecho | `env -u PS2SDK make es` y `make hoja-es` con 0 en `dda9a5f` |
| R-INF-02 Conversor EUC-JP | `prueba_convertir_eucjp.py` | `727c7ed`, `476dd52` | hecho | CI n.º 1 |
| R-INF-03 Metadatos convertidos | `prueba_metadatos_eucjp.py` | `ecbfd5c` | hecho | CI n.º 1; rojo comprobado |
| R-INF-04 `-fsigned-char` y dependencias de `test` | `make -n test`; huella de R-FUE-02 | `ecbfd5c`, `8fdea7c` | hecho | `make -n test`: `-fsigned-char` en los 8 `gcc` de prueba |
| R-INF-05 CI | ejecuciones de la CI | `7387d01`, `6dd12e7`, `a3d0bae`, `c461c5b`; F8: `24ed39a0`, `6251a4a6`, `b69f1548`; F9: `c641d19b`, `4bdd41a8`; F10: `a27fd80f`, `04adf1f6`, `68bc6dce`, `2c3a8b29`, `979fcf14` | hecho | CI 36518116212; F10: [38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616); F8 y F9 en [Evidencia común](#evidencia-común) ([CC-09](cambios.md), [CC-16](cambios.md), [CC-26](cambios.md)) |
| R-INF-06 Tope de líneas | `comprobar_lineas.py` en `make test` | `f1f3d3d` | hecho | 0 archivos por encima del tope en `dda9a5f` |
| R-INF-07 Emulador en la CI | `prueba_comprobar_registro.py`; `prueba_comparar_capturas.py`; job `emulador` | `7491fd24`, `98a042b7`, `a7bae5d4`, `570a0a12`, `2c3a8b29`, `979fcf14`; F11: `1bac15d9`, `632050ac`, `a7ab8019`, `3a022b42`, `17901393`, `6933dd08`, `863cbc45` | hecho | [38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616): dos arranques en Play! 0.72, región PAL, «vídeo: PMODE 8046» y capturas dentro de la tolerancia ([CC-26](cambios.md)). F11: tolerancia del 0,1 %, captura `configuracion` y referencias regeneradas en [38179540046](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38179540046) y [38180265814](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38180265814) ([CC-31](cambios.md)) |
| R-VID-01 Antiparpadeo opcional | `prueba_registros_video.c`; job `emulador` | `deeba019`, `fa835b62`, `9173dde8`, `979fcf14` | hecho; sin verificar en TV (límite declarado) | 0x8046 por defecto y 0x8027 con DBY ([CC-20](cambios.md)) |
| R-VID-02 Posición con límites | `prueba_registros_video.c` | `deeba019`, `fa835b62`, `9173dde8` | hecho; sin verificar en TV (límite declarado) | DY par y límites ([CC-20](cambios.md)) |
| R-VID-03 CON BANDAS | `prueba_registros_video.c` | `fa835b62`, `9173dde8`, `d8ebb3ac`, `d5ee5381` | hecho; sin verificar en TV (límite declarado) | Rojo de `d8ebb3ac`: 4 fallos de 66 ([CC-21](cambios.md)) |
| R-VID-04 PANORÁMICO | `prueba_vista_panoramica.c` | `064830d8`, `92c1f1f3`, `fd4286e3`, `c52e2f8d`, `761d735d` | hecho; bordes, marcador y rendimiento como límites declarados | Aspecto y cono ([CC-21](cambios.md)) |
| R-VID-05 Menú CONFIGURACIÓN Y TRUCOS | `prueba_menu_configuracion.c`; pruebas de textos y de lugares; captura del menú en el job `emulador` | `7abb1f92`, `7c5439e4`, `b8954cee`, `146b23af`, `be1248ff` | hecho | 55 comprobaciones; mutación del salto del 13: 5 fallos ([CC-19](cambios.md)) |
| R-TRU-01 DESBLOQUEAR TODO | `prueba_trucos.c` | `9d310c2c`, `be355571`, `91c7254e` | hecho | Se aplica al reconstruir cada pantalla de menú ([CC-22](cambios.md)) |
| R-TRU-02 OBJETO | `prueba_truco_objeto.c` | `4efcf0be`, `5a19ff97` | hecho | Casos de GP, Versus, batalla, contrarreloj e inválidos ([CC-23](cambios.md)) |
| R-TRU-03 200CC | `prueba_cilindrada_200cc.c` | `038c39c0`, `c80fe61e`, `a6397211` | hecho | Peor caso < 8,8; mutación 37/32 detectada ([CC-24](cambios.md)) |
| R-TRU-04 RIVALES SIN VENTAJA | `prueba_rivales_sin_ventaja.c` | `0e75a425`, `f46bc633`, `4c0323bf` | hecho | Efecto en el juego no medible: la CPU no es determinista ([CC-25](cambios.md)) |
| R-GOB-01 Formato de commits | comando de R-GOB-01 | todas | parcial: 4 commits `chore` en F1–F7 y 1 `style` en F9 (`b780d986`) | [CC-06](cambios.md). En F8 el comando solo devuelve `c2ed147` y `ae93f71`, del original ([CC-08](cambios.md)); la publicación pasa a tipo `build` ([CC-09](cambios.md)). En F9 devuelve solo `b780d986` ([acta de F9 §7](revisiones/2026-10-11-version-1.1.0.md#7-integración)). En F10 sale vacío |
| R-GOB-02 Refactor separado | `comparar_preprocesado.py`; job `mismo-binario`; caracterización | `418ea18`, `1c9545d`, `d87d14f`, `15136d3`, `3db4b80`, `9d2b711`, `40ed241`, `26a0bbc`, `4da5ab9`, `47a7371` | parcial: falta la prueba registrada de `15136d3` | F2: ver «Commits de F1–F3» y CI n.º 5. `9d2b711`, `40ed241` y `26a0bbc`: `comparar_preprocesado.py` da `igual` (en su mensaje). `3db4b80`: caracterización con la huella de la fuente ASCII. `4da5ab9` y `47a7371`: verificación en `6794945` ([CC-06](cambios.md)) |
| R-GOB-03 Rojo demostrado y mutación restaurada | salidas en el PR; `git diff --quiet` | todas | parcial: rojo registrado en F1–F3 (5 commits) y en `da631b0` (8 bloques de CADENAS); mutaciones solo en `4bf57f3`, `d28f950` y `da631b0`. En F8 y F9, rojo y mutación en cada commit con prueba; E4, E5 y L2 (F8) y la parte de libmc de CC-13, el registro de la región, D-14 y la condición de la cruceta (F9) sin arnés de PC, con evidencia de código. G5 tiene prueba desde F9 (`d41996f7`) | Tablas de commits de este documento; actas de [F8](revisiones/2026-10-11-sincronizacion.md) y [F9](revisiones/2026-10-11-version-1.1.0.md) |
| R-GOB-04 Revisión por rol distinto | registro de revisión | — | parcial: F1–F7 sin registro. F8, cerrada en `main` (`af3bfa05`) con su acta; su hallazgo Media de G5 se resolvió en F9 con la prueba de CC-17. F9 con acta, sin hallazgos Alta abiertos; los dos Media que piden texto en el manual de usuario (60 Hz en una consola PAL y `sha256sum -c --ignore-missing`) se cierran al integrar `v110/doc-manual`. F10 con [acta](revisiones/2026-10-11-version-1.2.0.md), sin hallazgos Alta ni Media abiertos | Actas de [F8](revisiones/2026-10-11-sincronizacion.md) y [F9](revisiones/2026-10-11-version-1.1.0.md) |
| R-GOB-05 Árbol limpio | `git status --short`; `git log -- build compilaciones` | todas | hecho | Solo los commits de publicación tocan `build/` y `compilaciones/`: `dda9a5f` en F7 y `900c9be3` en F8. En F9 (`a29bd920`), `git log --name-only origin/main..HEAD -- build compilaciones` sale vacío. En F10 (`fd6a4bb7`) sale vacío; la publicación es `9ab41422` |
| R-GOB-06 Stage por ruta | `git diff --stat` en la revisión | — | parcial: F1–F7 sin registro; en F8 y F9, REVISIÓN comprobó con el diff de tres puntos que cada rama solo toca sus archivos | Actas de [F8](revisiones/2026-10-11-sincronizacion.md) y [F9](revisiones/2026-10-11-version-1.1.0.md) |
| R-GOB-07 Sin identificadores en el código | `grep` de identificadores de requisito | todas | parcial: en F10 quedan 8 líneas en 4 archivos de `herramientas/` ([deuda.md](deuda.md), D-25) | Salida vacía en `dda9a5f`, `d5f95cc5` y `a29bd920`. En `fd6a4bb7`: `herramientas/ci/comprobar_incremental.sh`, `herramientas/ci/tope_rom.py`, `herramientas/pruebas/prueba_tope_rom.py` y `herramientas/pruebas/prueba_texturas_es.py` |
| R-GOB-08 Documentación sincronizada | revisión del PR | — | parcial: en F8, `sinc/manual`, `sinc/proceso` y `sinc/doc-traduccion` se integraron y están en `main` (`af3bfa05`). En F9 falta integrar `v110/doc-manual` y `v110/doc-traduccion` en `feature/version-1.1.0`; pasa a hecho con esa integración, antes de publicar, como en F8. En F10 pasa a hecho cuando se integren las ramas de documentación (`v120/doc-traduccion` y las demás), antes de publicar | Sincronización de F7; en F8, la documentación de [CC-12](cambios.md); en F9, CC-13 a CC-17 con commit y aprobación, el [acta](revisiones/2026-10-11-version-1.1.0.md) y [deuda.md](deuda.md); en F10, CC-18 a CC-29 con commit y aprobación, CC-30, el [acta](revisiones/2026-10-11-version-1.2.0.md) y los [límites declarados](especificacion.md#9-límites-declarados) |
