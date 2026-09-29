# Trazabilidad

Relaciona cada requisito de la [especificación](especificacion.md) con su prueba, sus commits y su evidencia. Estado a 2026-09-28, sobre las ramas publicadas `origin/idioma/infra` (`a3d0bae`), `origin/idioma/fuente` (`641fe27`) y `origin/idioma/texturas` (`236962b`).

## Cómo se completa

- **Commits:** hashes cortos de lo publicado. Si prueba y cambio van en commits separados, se anotan los dos (rojo → verde).
- **Rojo:** cómo se demostró que la prueba falla sin el cambio:
  - **comprobado:** la prueba del commit, ejecutada sobre el árbol del commit padre, falla (se indica cuántos fallos);
  - **módulo nuevo:** la prueba cubre un archivo que no existía, así que sin el cambio no puede pasar;
  - **no aplica:** refactor, cuya prueba es de equivalencia (R-GOB-02).
- **Mutación restaurada (R-GOB-03):** no quedó registrada en el repositorio para ningún commit publicado. Se adjunta al PR de integración.
- **Estados:** `hecho` (publicado y con su prueba en verde), `parcial` (hecho en parte; se indica qué falta), `en curso` (rama sin publicar), `pendiente` (sin empezar).
- **Requisito cerrado:** cuando está `hecho`, tiene la evidencia y REVISIÓN lo aprueba. Ninguno está cerrado todavía: la revisión de F5 no empezó.
- **Cambios de especificación:** se anotan en [cambios.md](cambios.md) y se enlazan aquí.

## Evidencia común

- **`make test` sin SDK.** `env -u PS2SDK make test` termina con 0 en `a3d0bae`, `641fe27` y `236962b`, y `env -u PS2SDK make` falla con el mensaje de `PS2SDK`. Comprobado el 2026-09-28 sobre una copia de cada rama.
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

- **Gobernanza de las ramas publicadas** (comprobado el 2026-09-28): el comando de R-GOB-01 sale vacío; ningún commit toca `build/` ni `compilaciones/` (R-GOB-05); ningún archivo de `codigo/`, `incluir/` o `herramientas/` lleva identificadores de requisito (R-GOB-07).

## Commits publicados

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

## Requisitos

| Requisito | Prueba | Commits | Estado | Evidencia |
|---|---|---|---|---|
| R-FUE-01 Tabla de glifos completa | `prueba_tablas_glifos.py`; `prueba_glifos.c` (`probar_compatibilidad`) | `4e35120`, `1c9545d`, `5718601` | hecho | CI n.º 7 y n.º 8; rojo comprobado |
| R-FUE-02 Compatibilidad N64 | `prueba_glifos.c` (`probar_compatibilidad`) | `d87d14f` | hecho | CI n.º 6 |
| R-FUE-03 JIS X 0212 de 3 bytes | `prueba_convertir_eucjp.py`; `prueba_glifos.c` (`probar_espanol`); `prueba_caracteres_es.c` | `727c7ed`, `9e6bec7`, `641fe27` | hecho | CI n.º 8; rojo comprobado en `641fe27` |
| R-FUE-04 `leer_glifo` única regla de avance | huella de R-FUE-02; `git grep` en la revisión | `d87d14f` | hecho | `git grep -n 'indice_glifo >= 0x30'` vacío en `641fe27` |
| R-FUE-05 Robustez ante -2 | `prueba_glifos.c` (`probar_secuencias_rotas`) | `641fe27` | parcial: falta el registro DEV | CI n.º 8 |
| R-FUE-06 Anchos | `prueba_glifos.c` (`probar_anchos_espanol`); `prueba_tablas_glifos.py` | `5718601`, `641fe27` | hecho | CI n.º 8 |
| R-FUE-07 Diacrítico con la matriz de la letra y tope del pool | `prueba_tablas_glifos.py` (`probar_partes_de_signo`); CI; revisión técnica; recorrido F6 | `dcc0914`, `5718601` | parcial: falta el recorrido F6 | CI n.º 7 |
| R-FUE-08 Arte reproducible | `prueba_glifos_es.py` | `9abb8d7`, `5718601` | hecho | CI n.º 7 |
| R-TXT-01 Español según el glosario | `prueba_textos.c` (lista negra) | — | en curso | — |
| R-TXT-02 Número y orden de entradas | `prueba_textos.c` (`prueba_textos_tablas.inc.c`) | — | en curso | — |
| R-TXT-03 Glifo para todo carácter | `prueba_textos.c` | — | en curso | — |
| R-TXT-04 Ancho por tinta y zona segura | `prueba_textos.c` (`prueba_textos_lugares.inc.c`, `prueba_textos_tinta.py`) | — | en curso | — |
| R-TXT-05 Interlineado | `prueba_textos.c` | — | en curso | — |
| R-TXT-06 Textos esperados byte a byte | `prueba_textos.c` (`prueba_textos_esperados.inc.c`) | — | en curso | — |
| R-TXT-07 Ordinales «1.º» | `prueba_textos.c`; `prueba_texturas_es.py`; captura F6 | — | en curso | — |
| R-TXT-08 Botones y puertos de PS2 en cadenas | `prueba_textos.c` | — | pendiente | — |
| R-MC-01 MEMORY CARD, sin Controller Pak | `prueba_textos.c` | — | pendiente | — |
| R-MC-02 Ranura 1/2 | `prueba_textos.c` | — | pendiente | — |
| R-MC-03 Opción copiar honesta | `prueba_textos.c`; `git diff` de `tablas_menus.inc.c`; captura F6 | — | pendiente | — |
| R-TEX-01 Despacho por firma | `prueba_textura_menu.c`; `prueba_tkmk00.py` | `9f9beac`, `2ff6bf0` | hecho | CI n.º 9 |
| R-TEX-02 Manifiesto completo | `prueba_texturas_es.py` | `4345598` | parcial: cubre las 63 TKMK00; falta el resto de carpetas | CI n.º 9 |
| R-TEX-03 Tamaños desde el manifiesto; PULSA START crudo | `prueba_texturas_es.py` | — | en curso (bloque B) | — |
| R-TEX-04 PNG fuente y reproducibilidad | `prueba_png_simple.py`; `prueba_formatos_textura.py`; `prueba_texturas_es.py` | `1ee6041`, `a7e918e`, `4345598` | parcial: herramientas hechas; faltan los PNG y las reglas del compositor | CI n.º 9 |
| R-TEX-05 HUD sin solapamiento | `prueba_texturas_es.py`; hoja del HUD; capturas F6 | — | pendiente | — |
| R-TEX-06 Lakitu: 16 cuadros y paleta | `prueba_texturas_es.py`; tira de 16 cuadros | — | pendiente | — |
| R-TEX-07 Botones de PS2 | `prueba_texturas_es.py` | — | en curso (bloque C) | — |
| R-TEX-08 Superposición sin mezcla | `prueba_invertir_texturas.py`; `prueba_texturas_es.py` | `fdd6a54` | parcial: falta conectarla al build y el sello de las `.i4` | CI n.º 9; rojo comprobado |
| R-PORT-01 Fuente 5x7 | `prueba_fuente_5x7.c` | — | en curso | — |
| R-PORT-02 Panel, audio y fases en español | `prueba_fuente_5x7.c`; `prueba_textos_port.py`; capturas F6 | — | en curso | — |
| R-PORT-03 Pantalla de fallo | `prueba_caracteres_es.c` (`probar_quitar_diacriticos`); `prueba_fuente_5x7.c`; paso G-FALLO; captura | `9e6bec7` (`quitar_diacriticos`) | en curso | CI n.º 6 |
| R-PORT-04 Marcas del registro | `prueba_textos_port.py`; revisión lingüística | — | en curso ([CC-05](cambios.md)) | — |
| R-PORT-05 Fuente de depuración N64 | `prueba_textos.c` | `9e6bec7` (`caracter_es_base`) | pendiente | — |
| R-INF-01 Objetivos del PC sin SDK | job `pruebas-pc` | `f8f9a39` | parcial: faltan `es` y `hoja-es` (A0) | Todas las ejecuciones de CI de la tabla; `make test` sin SDK comprobado |
| R-INF-02 Conversor EUC-JP | `prueba_convertir_eucjp.py` | `727c7ed` | hecho | CI n.º 1 |
| R-INF-03 Metadatos convertidos | `prueba_metadatos_eucjp.py` | `ecbfd5c` | hecho | CI n.º 1; rojo comprobado |
| R-INF-04 `-fsigned-char` y dependencias de `test` | `make -n test`; huella de R-FUE-02 | `ecbfd5c`, `8fdea7c` | hecho | CI n.º 6 |
| R-INF-05 CI | ejecuciones de la CI | `7387d01`, `6dd12e7`, `a3d0bae` | parcial: falta el paso G-FALLO (P4) | Todas las ejecuciones de CI de la tabla |
| R-INF-06 Tope de líneas | `comprobar_lineas.py` en `make test` | `f1f3d3d` | hecho | `comprobar_lineas.py`: 0 archivos por encima del tope en las tres ramas |
| R-GOB-01 Formato de commits | comando de R-GOB-01 | todas | hecho en lo publicado | Salida vacía en las tres ramas |
| R-GOB-02 Refactor separado | `comparar_preprocesado.py`; job `mismo-binario`; caracterización | `418ea18`, `1c9545d`, `d87d14f` | hecho | Ver «Commits publicados» y CI n.º 5 |
| R-GOB-03 Rojo demostrado y mutación restaurada | salidas en el PR; `git diff --quiet` | todas | parcial: rojo comprobado en 5 commits; mutaciones sin registrar; `dcc0914` sin rojo | Tabla «Commits publicados» |
| R-GOB-04 Revisión por rol distinto | registro de revisión | — | pendiente (F5) | — |
| R-GOB-05 Árbol limpio | `git status --short`; `git log -- build compilaciones` | todas | hecho en lo publicado | Salida vacía en las tres ramas |
| R-GOB-06 Stage por ruta | `git diff --stat` en la revisión | — | pendiente (F5) | — |
| R-GOB-07 Sin identificadores en el código | `grep` de identificadores de requisito | todas | hecho en lo publicado | Salida vacía en las tres ramas |
| R-GOB-08 Documentación sincronizada | revisión del PR | — | en curso (esta sincronización) | — |
