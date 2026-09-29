# Trazabilidad

Relaciona cada requisito de la [especificación](especificacion.md) con su prueba, sus commits y su evidencia. Estado final, a 2026-09-29, sobre `feature/idioma-espanol` en `dda9a5f`, con las cinco ramas de trabajo ya fusionadas.

## Cómo se completa

- **Commits:** hashes cortos, todos integrados en `feature/idioma-espanol`. Si prueba y cambio van en commits separados, se anotan los dos (rojo → verde).
- **Rojo:** cómo se demostró que la prueba falla sin el cambio:
  - **comprobado:** la prueba del commit, ejecutada sobre el árbol del commit padre, falla (se indica cuántos fallos);
  - **módulo nuevo:** la prueba cubre un archivo que no existía, así que sin el cambio no puede pasar;
  - **no aplica:** refactor, cuya prueba es de equivalencia (R-GOB-02).
- **Mutación restaurada (R-GOB-03):** está registrada en los mensajes de `4bf57f3`, `d28f950` y `da631b0` (este último para `23055c5` y `29541a4`). Para el resto de commits no quedó registrada en el repositorio.
- **Estados:** `hecho` (integrado y con su prueba en verde), `parcial` (hecho en parte; se indica qué falta), `pendiente` (sin hacer).
- **Requisito cerrado:** cuando está `hecho`, tiene la evidencia y REVISIÓN lo aprueba. La aprobación de REVISIÓN no quedó registrada en el repositorio (R-GOB-04), así que la tabla indica el estado de implementación y prueba.
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

## Requisitos

| Requisito | Prueba | Commits | Estado | Evidencia |
|---|---|---|---|---|
| R-FUE-01 Tabla de glifos completa | `prueba_tablas_glifos.py`; `prueba_glifos.c` (`probar_compatibilidad`) | `4e35120`, `1c9545d`, `5718601` | hecho | CI n.º 7 y n.º 8; rojo comprobado |
| R-FUE-02 Compatibilidad N64 | `prueba_glifos.c` (`probar_compatibilidad`) | `d87d14f` | hecho | CI n.º 6 |
| R-FUE-03 JIS X 0212 de 3 bytes | `prueba_convertir_eucjp.py`; `prueba_glifos.c` (`probar_espanol`); `prueba_caracteres_es.c` | `727c7ed`, `9e6bec7`, `641fe27` | hecho | CI n.º 8; rojo comprobado en `641fe27` |
| R-FUE-04 `leer_glifo` única regla de avance | huella de R-FUE-02; `git grep` en la revisión | `d87d14f` | hecho | `git grep -n 'indice_glifo >= 0x30' -- codigo/menus/` vacío en `dda9a5f` |
| R-FUE-05 Robustez ante -2 | `prueba_glifos.c` (`probar_secuencias_rotas`) | `641fe27` | parcial: falta el registro DEV | CI n.º 8. El registro DEV de `C2`/`C3` no está en el código |
| R-FUE-06 Anchos | `prueba_glifos.c` (`probar_anchos_espanol`); `prueba_tablas_glifos.py` | `5718601`, `641fe27` | hecho | CI n.º 8 |
| R-FUE-07 Diacrítico con la matriz de la letra y tope del pool | `prueba_tablas_glifos.py` (`probar_partes_de_signo`); CI; revisión técnica; recorrido F6 | `dcc0914`, `5718601` | parcial: falta el recorrido F6 | CI n.º 7 y 36518116212 |
| R-FUE-08 Arte reproducible | `prueba_glifos_es.py` | `9abb8d7`, `5718601` | hecho | CI n.º 7 |
| R-TXT-01 Español según el glosario | `prueba_textos.c` (lista negra) | B1–B7 (ver «Commits de F4») | hecho | `TABLAS_PENDIENTES` = 0; rojo en `da631b0` |
| R-TXT-02 Número y orden de entradas | `prueba_textos.c` (`prueba_textos_tablas.inc.c`) | `ae9dc3c` y B1–B7 | hecho | `make test` en `dda9a5f` |
| R-TXT-03 Glifo para todo carácter | `prueba_textos.c` | `ae9dc3c` y B1–B7 | hecho | `make test` en `dda9a5f` |
| R-TXT-04 Ancho por tinta y zona segura | `prueba_textos.c` (`prueba_textos_lugares.inc.c`, `prueba_textos_tinta.py`) | `330e2d9`, `5b21e3e`, `b061832`, `23055c5` | hecho; falta la captura en TV (F6) | Mutación de `23055c5` en `da631b0`; [CC-01](cambios.md) |
| R-TXT-05 Interlineado | `prueba_textos.c` (`probar_interlineado`) | `ae9dc3c` | hecho | [CC-02](cambios.md) |
| R-TXT-06 Textos esperados byte a byte | `prueba_textos.c` (`prueba_textos_esperados.inc.c`) | B1–B7 | hecho | Rojo en `da631b0` |
| R-TXT-07 Ordinales «1.º» | `prueba_textos.c`; `prueba_hud_es.py`; captura F6 | `f8bf7b5`, `d28f950`, `a4676b3` | parcial: falta la captura F6 | Rojo de `f8bf7b5` en `da631b0`; rojo y mutación de `d28f950` en su mensaje |
| R-TXT-08 Botones y puertos de PS2 en cadenas | `prueba_textos.c` | `88e159b` | hecho | «CRUZ*VER DATOS  CUADRADO*SALIR» en `textos_menu.inc.c` |
| R-MC-01 MEMORY CARD, sin Controller Pak | `prueba_textos.c` | `88e159b` | hecho | Rojo en `da631b0`: 331 fallos |
| R-MC-02 Ranura 1/2 | `prueba_textos.c` | `88e159b` | hecho | Esperados de `dato_800E78*` |
| R-MC-03 Opción copiar honesta | `prueba_textos.c`; `git diff` de `tablas_menus.inc.c`; captura F6 | `88e159b` | parcial: falta la captura F6 | Esperados «COPIAR FANTASMAS DESDE / OTRA MEMORY CARD NO / ESTÁ DISPONIBLE EN PS2» |
| R-TEX-01 Despacho por firma | `prueba_textura_menu.c`; `prueba_tkmk00.py` | `9f9beac`, `2ff6bf0` | hecho | CI n.º 9 |
| R-TEX-02 Manifiesto completo | `prueba_texturas_es.py` | `4345598`, `37633d3`, `31eaf62` | parcial: ninguna prueba exige fila o exclusión para las carpetas fuera de TKMK00 | 97 filas en `recursos/es/texturas.tsv` y 3 en `lakitu.tsv` |
| R-TEX-03 Tamaños desde el manifiesto; PULSA START crudo | `prueba_cableado_es.py`; `prueba_cartel_es.py` | `37633d3`, `78b7177`, `c86be95` | hecho; el crecimiento de la ROM se midió a mano | `rom.bin` + 6 144 B en `dda9a5f` |
| R-TEX-04 PNG fuente y reproducibilidad | `prueba_png_simple.py`; `prueba_formatos_textura.py`; `prueba_texturas_es.py`; `prueba_composicion_es.py` | `1ee6041`, `a7e918e`, `4345598`, `03e5967` y el arte | hecho | `make test` en `dda9a5f` |
| R-TEX-05 HUD sin solapamiento | `prueba_hud_es.py`; hoja del HUD; capturas F6 | `7e0d345`, `a4676b3` | parcial: faltan las capturas F6 | [CC-03](cambios.md), [CC-07](cambios.md) |
| R-TEX-06 Lakitu: 16 cuadros y paleta | `prueba_lakitu_es.py`; tira de 16 cuadros | `74cbaf6`, `44cc3fb` | hecho | Textos de reserva de `lakitu.tsv` |
| R-TEX-07 Botones de PS2 | `prueba_composicion_es.py` (PNG = texto del manifiesto) | `788a957` | hecho; sin comprobación automática del nombre del botón | `SELECT|OPCIONES` y `R1|DATOS` en el manifiesto |
| R-TEX-08 Superposición sin mezcla | `prueba_invertir_texturas.py`; `prueba_hud_es.py` | `fdd6a54`, `7e0d345`, `a4676b3` | hecho; la prueba revisa las reglas del sello, no un build incremental real | CI n.º 9; rojo comprobado en `fdd6a54` |
| R-PORT-01 Fuente 5x7 | `prueba_fuente_5x7.c` | `3db4b80`, `82858b4` | hecho | `make test` en `dda9a5f` |
| R-PORT-02 Panel, audio y fases en español | `prueba_fuente_5x7.c`; `prueba_textos_port.py`; `prueba_ancho_panel.py`; capturas F6 | `0af8ebe`, `ead3e9d`, `ac10246`, `1bc10ba`, `7653639` | parcial: faltan las capturas F6 | CUADRO, RESERVA, VÉRT y MÚSICA en el código |
| R-PORT-03 Pantalla de fallo | `prueba_caracteres_es.c` (`probar_quitar_diacriticos`); `prueba_textos_port.py`; captura | `9e6bec7`, `0c05c15`, `ba66cf9` | parcial: sin paso G-FALLO (se translitera siempre) y sin captura | «PARADA DE DIAGNÓSTICO» y EJEC/LISTO/ESPERA en `depuracion.c` |
| R-PORT-04 Marcas del registro | `prueba_textos_port.py`; revisión lingüística | `9d2b711`, `91b2a89`, `823a0c8` y los formatos de `registrar()` | hecho | [CC-05](cambios.md) |
| R-PORT-05 Fuente de depuración N64 | `prueba_textos.c`; `prueba_cadena_depuracion.c` | `9e6bec7`, `40ed241`, `37cf760`, `ab920e9`, `26a0bbc`, `32c2a6f` | hecho | Rojo de `ab920e9` en `da631b0`; mutación de `29541a4` en `da631b0` |
| R-INF-01 Objetivos del PC sin SDK | job `pruebas-pc` | `f8f9a39`, `37633d3`, `a0da3a1` | hecho | `env -u PS2SDK make es` y `make hoja-es` con 0 en `dda9a5f` |
| R-INF-02 Conversor EUC-JP | `prueba_convertir_eucjp.py` | `727c7ed`, `476dd52` | hecho | CI n.º 1 |
| R-INF-03 Metadatos convertidos | `prueba_metadatos_eucjp.py` | `ecbfd5c` | hecho | CI n.º 1; rojo comprobado |
| R-INF-04 `-fsigned-char` y dependencias de `test` | `make -n test`; huella de R-FUE-02 | `ecbfd5c`, `8fdea7c` | hecho | `make -n test`: `-fsigned-char` en los 8 `gcc` de prueba |
| R-INF-05 CI | ejecuciones de la CI | `7387d01`, `6dd12e7`, `a3d0bae`, `c461c5b` | hecho; el paso G-FALLO no se añadió | CI 36518116212 |
| R-INF-06 Tope de líneas | `comprobar_lineas.py` en `make test` | `f1f3d3d` | hecho | 0 archivos por encima del tope en `dda9a5f` |
| R-GOB-01 Formato de commits | comando de R-GOB-01 | todas | parcial: 4 commits `chore` | [CC-06](cambios.md) |
| R-GOB-02 Refactor separado | `comparar_preprocesado.py`; job `mismo-binario`; caracterización | `418ea18`, `1c9545d`, `d87d14f`, `15136d3`, `3db4b80`, `9d2b711`, `40ed241`, `26a0bbc`, `4da5ab9`, `47a7371` | parcial: falta la prueba registrada de `15136d3` | F2: ver «Commits de F1–F3» y CI n.º 5. `9d2b711`, `40ed241` y `26a0bbc`: `comparar_preprocesado.py` da `igual` (en su mensaje). `3db4b80`: caracterización con la huella de la fuente ASCII. `4da5ab9` y `47a7371`: verificación en `6794945` ([CC-06](cambios.md)) |
| R-GOB-03 Rojo demostrado y mutación restaurada | salidas en el PR; `git diff --quiet` | todas | parcial: rojo registrado en F1–F3 (5 commits) y en `da631b0` (8 bloques de CADENAS); mutaciones solo en `4bf57f3`, `d28f950` y `da631b0`; `dcc0914` sin rojo | Tablas de commits de este documento |
| R-GOB-04 Revisión por rol distinto | registro de revisión | — | pendiente: sin registro en el repositorio | — |
| R-GOB-05 Árbol limpio | `git status --short`; `git log -- build compilaciones` | todas | hecho | Solo `dda9a5f` toca `build/` y `compilaciones/` |
| R-GOB-06 Stage por ruta | `git diff --stat` en la revisión | — | pendiente: sin registro de revisión | — |
| R-GOB-07 Sin identificadores en el código | `grep` de identificadores de requisito | todas | hecho | Salida vacía en `dda9a5f` |
| R-GOB-08 Documentación sincronizada | revisión del PR | — | hecho | Esta sincronización final de README y `docs/traduccion/` |
