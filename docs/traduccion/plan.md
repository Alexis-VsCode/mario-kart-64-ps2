# Plan de trabajo: Mario Kart 64 PS2 en español

Este documento dice cómo se cumplió la [especificación](especificacion.md) y el estado final de cada fase (2026-09-29). El trabajo se repartió en roles que avanzaron en paralelo, cada uno en su propia rama y su propio worktree (`git worktree add`). Solo INTEGRACIÓN integró. Las ramas de trabajo ya están fusionadas en `feature/idioma-espanol`; lo que queda por hacer está en [README.md § Pendiente](README.md#pendiente).

## 1. Principios

- **Lectura inicial.** Antes de tocar nada se leen el `README.md`, `docs/traduccion/` y la salida de `git status --short`.
- **Núcleo puro y adaptadores PS2 finos.** Decodificadores, anchos y conversión de formatos compilan en el PC y se prueban con `make test`. Lo que toca el GS, `scr_printf` o el DMA queda en adaptadores finos. Ejemplos ya hechos: `caracteres_es.c` y `descompresion_textura_menu.c` son puros; `tkmk00decode` es el adaptador.
- **Una sola fuente de verdad:**
  - `lista_glifos.inc.c` (X-macro) da a la vez la LUT y los anchos;
  - `recursos/es/texturas.tsv` gobierna las texturas y sus tamaños.
- **Despacho por firma.** El cargador de texturas elige TKMK00 o MIO0 leyendo la cabecera.
- **Herramientas deterministas.** Glifos, texturas y cabeceras salen de herramientas del repositorio. No se editan binarios a mano.
- **Pruebas guiadas por tablas.** Cuentas, límites y textos esperados están versionados.
- **Sin sobreingeniería.** No se escribe un codificador TKMK00: las traducidas van en MIO0.
- **Otros principios:**
  - reutilizar antes de crear;
  - medir antes de optimizar;
  - ante una duda de alcance, se pregunta al responsable del proyecto.

## 2. Roles

| Rol | Responsabilidad | Archivos propios | Rama (ya fusionada) |
|---|---|---|---|
| INTEGRACIÓN | Infraestructura, documentación, integración y publicación. Es el único rol que integra en `feature/idioma-espanol` | Reglas generales del `Makefile`, `.github/workflows/compilacion.yml`, `herramientas/convertir_eucjp.py`, `herramientas/comprobar_lineas.py`, `herramientas/comparar_binario.sh`, `herramientas/comparar_preprocesado.py`, `docs/traduccion/*`, `README.md` | `docs/readme-y-especificacion`, `idioma/infra`, `feature/idioma-espanol` |
| PRUEBAS | Escribe las pruebas y demuestra el rojo y la mutación restaurada | `herramientas/pruebas/*` | La rama del bloque |
| FUENTE | Tabla de glifos, codificación, glifos nuevos y tope del pool de matrices | `codigo/menus/elementos_menu/{glifos,lista_glifos}.inc.c`; las llamadas a `leer_glifo` de `imprimir_texto.inc.c`; `funcion_80095BD0` y `dibujar_diacritico_glifo` de `cargar_texturas_menu.inc.c`; `imprimir_letra` de `letras_y_fundidos.inc.c`; `codigo/datos/segmento_datos_2.c` e `incluir/datos/segmento_datos_2.h`; `codigo/datos/texturas.c` e `incluir/datos/texturas.h` (solo la inclusión de la fuente del español); `codigo/datos/texturas/fuente_es.inc.c` e `incluir/datos/texturas/fuente_es.h`; `codigo/datos/texturas_fuentes_es.s`; `incluir/sistema/caracteres_es.h` y `codigo/sistema/caracteres_es.c`; `herramientas/generar_glifos_es.py`; `herramientas/generar_rom_ld.py` | `idioma/fuente` |
| CADENAS | Traslado de las cadenas a `textos_menu.inc.c`, traducción de tablas y créditos, y maquetación registrada en `cambios.md` | `codigo/menus/elementos_menu/textos_menu.inc.c`; cadenas de `codigo/ceremonia/creditos.c`; `recursos/pistas/metadatos/nombres_circuito.inc.c` y `nombres_depuracion_circuito.inc.c`; literales, escalas y pasos de `info_pistas_y_tiempos.inc.c`, `menus_pausa.inc.c` y `dibujar_menus.inc.c` | `idioma/cadenas` |
| TEXTURAS | Cargador por firma, herramientas de texturas, manifiesto y arte | `codigo/sistema/descompresion_textura_menu.c` e `incluir/sistema/descompresion_textura_menu.h`; `codigo/sistema/descompresion.c`; `herramientas/{png_simple,formatos_textura,texturas_es}.py`; `herramientas/archivos_host.c`; `herramientas/invertir_texturas.py`; `recursos/es/**`; las rutas `.incbin` de `codigo/datos/*.s`; los tamaños de `codigo/datos/texturas/{fuentes_y_menus,vistas_previas_pistas}.inc.c`; `recursos/pistas/moo_moo_farm/desplazamientos.c`; los desplazamientos del HUD en `ventana_item_y_minimapa.inc.c` y `hud_pantalla_dividida.inc.c` | `idioma/texturas` |
| PORT | Pantallas propias del port y textos del registro | `codigo/depuracion/fuente_5x7.c` e `incluir/depuracion/fuente_5x7.h`; `codigo/depuracion/texto_pantalla.c` y su cabecera; `medidor_rendimiento.c`; `monitor_audio.c`; `depuracion.c`; `incluir/depuracion/marcas_registro.h`; la llamada de `codigo/graficos/sintetizador_gs.c:121`; nombres de fase de `arranque_ps2.c`, `hilos_video_y_audio.inc.c`, `preparacion_carrera.c`, `descomprimir_pista.inc.c`, `pistas_toads_a_big_donut.inc.c` y de las partes de los fuentes de `JP_SRC`; `kart_bomba_y_depuracion.inc.c` | `idioma/port` |
| REVISIÓN | Dos revisores independientes: uno técnico y uno lingüístico. No revisa bloques propios | Ninguno | — |

**Archivos compartidos.** Cada uno tiene zonas con dueño. INTEGRACIÓN resuelve los conflictos al integrar.

| Archivo | Zonas |
|---|---|
| `Makefile` | INTEGRACIÓN: reglas generales, `OBJETIVOS_PC`, conversión y CI. Cada rol añade sus pruebas a la receta de `test` y sus reglas y variables en bloques propios |
| `codigo/menus/elementos_menu/textos_y_tablas.inc.c` | FUENTE: tablas de glifos (inclusión de `lista_glifos.inc.c` y `ASSERT_ESTATICO`). CADENAS: el bloque de cadenas de `main` `:264-647`, que se traslada a `textos_menu.inc.c` |
| `incluir/menus/elementos_menu.h` | FUENTE: declaraciones de glifos (`leer_glifo`, los 7 `extern` de los arreglos de continuación que se eliminaron en `4e35120`). CADENAS: los `extern` de las tablas nuevas |
| `codigo/menus/elementos_menu/imprimir_texto.inc.c` | FUENTE: la regla de avance. CADENAS: los literales |
| `codigo/menus/elementos_menu/cargar_texturas_menu.inc.c` | FUENTE: `funcion_80095BD0` y `dibujar_diacritico_glifo`. TEXTURAS: `cargar_img_menu` |
| Formatos de `registrar()` en cualquier archivo de `codigo/` | PORT cambia solo el literal; el resto del archivo es de su dueño |

Regla general: ningún rol toca la zona de otro sin registrarlo en el PR y avisar a INTEGRACIÓN.

## 3. Ramas

Topología con la que se trabajó, comprobada con `git reflog` el 2026-09-28. Todas las ramas de trabajo están fusionadas en `feature/idioma-espanol`, que se fusiona a `main`; después se borran.

```
origin/main (0e7b7d5)
 ├─ docs/readme-y-especificacion    F0 (README y docs/traduccion)
 │   └─ feature/idioma-espanol       integración (nace de cbc10e8)
 └─ idioma/infra                     F1        reflog: «Created from origin/main»
     ├─ idioma/fuente                F2, F3    reflog: «Created from origin/idioma/infra»
     │   ├─ idioma/cadenas           F4        reflog: «Created from origin/idioma/fuente»
     │   └─ idioma/port              F4        reflog: «Created from origin/idioma/fuente»
     └─ idioma/texturas              F4        reflog: «Created from origin/idioma/infra»
```

- Cada subrama nació de la rama de la que dependía su trabajo: F2/F3 y TEXTURAS necesitaban la infraestructura; CADENAS y PORT, la fuente.
- Una subrama trajo lo nuevo de su rama de origen con un merge: `236962b` llevó a `idioma/texturas` los commits `6dd12e7` y `a3d0bae` de `idioma/infra`, y `2095326` llevó `476dd52` a `idioma/cadenas`.
- `feature/idioma-espanol` nació de `docs/readme-y-especificacion` (`cbc10e8`). INTEGRACIÓN integró cada subrama con `git merge --no-ff`, en este orden:
  1. `idioma/infra` (`3d482a8`)
  2. `idioma/fuente` (`6a050d1`)
  3. `idioma/texturas` (`d3663fd`)
  4. `idioma/cadenas` (`b043668`)
  5. `idioma/port` (`2ae3d3a`)
- Después de integrar: `0ff568e` (una tilde que detectó la prueba del port), `466e73f` (guion de recorrido), `c461c5b` (job `publicar`) y `dda9a5f` (commit de publicación).

**Verificación al crear una rama.** Para una rama nueva se ejecuta todo esto y se adjunta la salida al PR. `merge-base` no sirve como prueba.

```sh
git reflog show <rama> | tail -1                  # punto de creación
git rev-list --count <origen>..<rama>             # commits propios
git log --merges <origen>..<rama>                 # merges inesperados
git log --format='%ae' origin/main..<rama> | sort -u
```

## 4. Fases

| Fase | Roles | Contenido | Rama | Puerta | Estado |
|---|---|---|---|---|---|
| F0 | INTEGRACIÓN | README profesional y `docs/traduccion/`: especificación, glosario, plan, trazabilidad y cambios | `docs/readme-y-especificacion` | El responsable del proyecto aprueba la especificación | Hecha: `c86f72c`…`cbc10e8`, base de `feature/idioma-espanol` |
| F1 | INTEGRACIÓN + PRUEBAS | `make test` sin SDK, conversor EUC-JP, metadatos convertidos, `-fsigned-char`, tope de líneas y CI | `idioma/infra` | CI verde | Hecha: `f8f9a39`…`476dd52`, integrada en `3d482a8` |
| F2 | FUENTE | Refactor sin cambio de comportamiento: `glifos.inc.c`, `lista_glifos.inc.c` y regla única de avance | `idioma/fuente` | Preprocesado o binario idéntico, o prueba de caracterización (R-GOB-02) | Hecha, integrada en `6a050d1` |
| F3 | FUENTE | LUT de 236 entradas, caracteres del español, glifos nuevos, tope del pool y cadenas con tildes | `idioma/fuente` | `prueba_tablas_glifos.py`, `prueba_glifos.c`, `prueba_glifos_es.py` y `prueba_caracteres_es.c` en verde | Hecha (`418ea18`…`641fe27`); pendiente el registro DEV de R-FUE-05 |
| F4 | CADENAS ∥ TEXTURAS ∥ PORT | Bloques B1–B7, A0–A6 → B → C y P1–P5 | `idioma/{cadenas,texturas,port}` | Por bloque: rojo → verde → revisión | Hecha, integrada en `d3663fd`, `b043668` y `2ae3d3a`. Sin paso G-FALLO (ver P4) |
| F5 | REVISIÓN ×2 | Revisión adversarial de cada bloque y verificación de las mutaciones restauradas | — | Sin hallazgos Alta o Media abiertos | Sin registro en el repositorio (ver [trazabilidad.md](trazabilidad.md), R-GOB-03 y R-GOB-04) |
| F6 | Responsable del proyecto | Recorrido en PCSX2 con el guion DEV y al menos una captura en TV | — | Capturas aprobadas | Pendiente. El guion está hecho: `herramientas/guiones/recorrido_textos.txt` (`466e73f`) |
| F7 | INTEGRACIÓN | Integración, regeneración de `build/` y `compilaciones/`, sección «Idioma» del README y requisitos del README sin `iconv` obligatorio | `feature/idioma-espanol` | Definición de terminado | Hecha: merges, `dda9a5f` (job `publicar`, CI 36518116212) y esta documentación. Queda la fusión a `main` |

### F1: infraestructura (hecha en `idioma/infra`, ya fusionada)

| Commit | Qué hace | Requisito |
|---|---|---|
| `f8f9a39` | `OBJETIVOS_PC := test clean herramientas`: solo los demás objetivos exigen `PS2SDK` | R-INF-01 |
| `727c7ed` | `convertir_eucjp.py` sustituye a `iconv`, con `prueba_convertir_eucjp.py` | R-INF-02 |
| `ecbfd5c` | Los metadatos de pista entran en la conversión y se buscan primero en `build/ps2/jp` (`-iquote`); `make test` depende de las copias convertidas | R-INF-03, R-INF-04 |
| `8fdea7c` | Las pruebas se compilan con `-fsigned-char` | R-INF-04 |
| `f1f3d3d` | `comprobar_lineas.py` dentro de `make test` | R-INF-06 |
| `7387d01` | CI: jobs `pruebas-pc` y `compilar-ps2` | R-INF-05 |
| `6dd12e7` | CI: el job de PS2 empieza con `make clean` | R-INF-05, R-GOB-05 |
| `a3d0bae` | `comparar_binario.sh` y job `mismo-binario` | R-INF-05, R-GOB-02 |
| `476dd52` | La prueba del conversor no compara con un `iconv` sin JIS X 0212 (el de musl) | R-INF-02 |

Los esqueletos de prueba con fallos esperados que pedía el plan se hicieron dentro de cada bloque. Por ejemplo, `prueba_textos_tablas.inc.c` (`ae9dc3c`) marcaba las tablas `PENDIENTE` como fallo esperado; su número solo podía bajar y terminó en 0.

### F2 y F3: fuente (hechas en `idioma/fuente`, ya fusionada, en este orden)

| Orden | Commit | Tipo | Qué hace | Requisito |
|---|---|---|---|---|
| 1 | `418ea18` | refactor | Las funciones de glifos pasan a `glifos.inc.c` | R-GOB-02 |
| 2 | `4e35120` | fix | La LUT pasa a 236 entradas en orden N64, desaparecen los 7 arreglos y se añade el `ASSERT_ESTATICO` | R-FUE-01 |
| 3 | `1c9545d` | refactor | `lista_glifos.inc.c` (X-macro) da la LUT y los anchos | R-FUE-01, R-GOB-02 |
| 4 | `cb36bbc` | build | `comparar_preprocesado.py` para comprobar un refactor sin SDK | R-GOB-02 |
| 5 | `9e6bec7` | feat | `caracteres_es.c`: lectura en EUC-JP y UTF-8, letra base, signo y `quitar_diacriticos` | R-FUE-03, R-PORT-03 |
| 6 | `d87d14f` | refactor | `leer_glifo`, regla única de avance en las cinco impresoras | R-FUE-02, R-FUE-04 |
| 7 | `9abb8d7` | feat | `generar_glifos_es.py` escribe los 11 glifos en el build | R-FUE-08 |
| 8 | `dcc0914` | fix | Tope real del pool de matrices en `funcion_80095BD0` | R-FUE-07 |
| 9 | `5718601` | feat | Glifos en la ROM (`texturas_fuentes_es.s`) y en la lista (0xEC..0xF6); diacrítico con la matriz de la letra | R-FUE-01, R-FUE-06, R-FUE-07 |
| 10 | `641fe27` | feat | `leer_glifo` reconoce las secuencias `8F xx xx`; las cadenas del menú pueden llevar tildes | R-FUE-03, R-FUE-05, R-FUE-06 |

- El traslado de `textos_y_tablas.inc.c:264-647` a `textos_menu.inc.c`, que el plan ponía en F2, lo hizo CADENAS al empezar F4 (`15136d3`), porque ese archivo es suyo.
- Pendiente de F3:
  - el registro DEV de R-FUE-05 (no está en el código);
  - comprobar en PCSX2 que se ven bien el ranking de récords (ordinales) y «ーーーー», los glifos que leían fuera de la tabla antes de `4e35120` (parte del recorrido de F6).

### F4: trabajo en paralelo

**CADENAS** (hecho en `idioma/cadenas`, ya fusionada). Primero trasladó las cadenas a `textos_menu.inc.c` en un commit `refactor` propio (`15136d3`) y añadió `prueba_textos.c` con sus tablas (`ae9dc3c`). Después, un bloque por tema. El rojo de los bloques que cambiaron prueba y texto en un solo commit está registrado en `da631b0`:

| Bloque | Contenido | Requisitos | Commits |
|---|---|---|---|
| B1 | Opciones y datos | R-TXT-01…06 | `330e2d9`, `ecd39f1` |
| B2 | Copas y nombres de pista | R-TXT-01…06 | `5b21e3e`, `5bddeef`, `23055c5`, `a16b42c`, `a54c0d4` |
| B3 | Pausa y resultados. Los literales `"results"`, `"round"` y `"driver's points"` pasan a tablas | R-TXT-01…07 | `4da5ab9`, `b061832`, `39059d8`, `f8bf7b5`, `d28f950` |
| B4 | Fantasmas y Memory Card | R-MC-01…03, R-TXT-08 | `88e159b` |
| B5 | Ceremonia y créditos (`creditos.c:70-81`) | R-TXT-01…07 | `321091a` |
| B6 | Intro de batalla, avisos y banner | R-TXT-01…06, R-TXT-08 | `25311d4` |
| B7 | Depuración, solo ASCII | R-PORT-05 | `47a7371`, `ab920e9`, `26a0bbc`, `32c2a6f` |

**TEXTURAS** (hecho en `idioma/texturas`, ya fusionada).

| Bloque | Contenido | Requisitos | Estado |
|---|---|---|---|
| A0 | Objetivos `es` y `hoja-es`, que corren sin SDK y entran en `OBJETIVOS_PC` | R-INF-01 | Hecho en `37633d3` y `a0da3a1` |
| A1 | `png_simple.py` | R-TEX-04 | Hecho en `1ee6041` |
| A2 | `formatos_textura.py` | R-TEX-04 | Hecho en `a7e918e` |
| A3 | Herramienta `tkmk00` del PC (`archivos_host.c`) y sumas de referencia | R-TEX-01 | Hecho en `9f9beac` |
| A4 | Despacho por firma (`descompresion_textura_menu.c`) | R-TEX-01 | Hecho en `2ff6bf0` |
| A5 | Superposición (`--superponer`), conectada al build con su sello | R-TEX-08 | Hecho en `fdd6a54`; conexión en `7e0d345` y `a4676b3` |
| A6 | Manifiesto y `texturas_es.py`: `exportar`, `importar`, `comprobar` y `hoja` | R-TEX-02, R-TEX-04 | Hecho en `4345598` |
| B | Cableado idéntico: PNG iguales a los originales, MIO0 y `TAMANIO_ES_*`. El juego debe verse igual, salvo la diferencia aceptada de la disolución | R-TEX-02, R-TEX-03 | Hecho en `37633d3` y `31eaf62` |
| C | Arte, una familia por commit (orden debajo) | R-TEX-04…07 | Hecho; correcciones en `e28eea2` y `44cc3fb` |

`236962b` trae a `idioma/texturas` el final de `idioma/infra`.

Familias del bloque C, en el orden en que se integraron:

1. Títulos grandes (`03e5967`)
2. Botones, tarjetas de modo y jugadores, y copas (`788a957`)
3. PULSA START, RGBA16 crudo de 159 × 16, ver R-TEX-03 (`78b7177`)
4. HUD: TIEMPO y VUELTA (`7e0d345`) y puestos (`a4676b3`)
5. Lakitu (`74cbaf6`)
6. Títulos de pista (`b4f294b`) y cartel MOO MOO FARM (`c86be95`)

**PORT** (hecho en `idioma/port`, ya fusionada).

| Bloque | Contenido | Requisitos | Commits |
|---|---|---|---|
| P1 | Fuente 5x7 y columnas por carácter | R-PORT-01 | `3db4b80`, `82858b4` |
| P2 | Panel y página de audio | R-PORT-02 | `0af8ebe`, `1bc10ba` |
| P3 | Marcas del registro | R-PORT-04 | `9d2b711`, `91b2a89`, `823a0c8` |
| P4 | Pantalla de fallo y fuente de depuración N64. La puerta G-FALLO no se hizo: la pantalla translitera siempre | R-PORT-03, R-PORT-05 | `0c05c15`, `ba66cf9`, `40ed241`, `37cf760` |
| P5 | Formatos de `registrar()` y nombres de fase | R-PORT-02, R-PORT-04 | `ead3e9d`, `ac10246`, `7ec08ed`, `ae0cf90`, `d9dbbbc`, `9a74ca2`, `f21bcae`, `3d4e5d8`, `7b88a69`, `cde92e0`, `b7e7fb7`, `7653639` |

Los cambios de escala o de paso que pidió la maquetación están en [cambios.md](cambios.md) (CC-01, CC-02, CC-03 y CC-07).

R-GOB-01 no se cumplió del todo: `31eaf62` (texturas), `da631b0` y `6794945` (cadenas) y el de publicación `dda9a5f` son de tipo `chore`, que no está entre los admitidos. No se reescribió la historia; está registrado en [CC-06](cambios.md).

## 5. Ciclo por bloque

1. **Rojo (PRUEBAS).** La prueba nueva falla, y su salida se adjunta al PR.
2. **Verde (rol autor).** La implementación hace pasar la prueba.
3. **Mutación restaurada (PRUEBAS).** Se rompe a mano la implementación, la prueba vuelve a fallar y se restaura.
4. **Comprobaciones:** `make test` y los comprobadores.
5. **Árbol limpio:** `git status --short` vacío.
6. **Revisión (REVISIÓN).**
7. **Integración (INTEGRACIÓN)** con `merge --no-ff`.

Prueba y cambio pueden ir en dos commits o en uno. Las dos formas son válidas si el rojo queda demostrado:

```sh
# Forma A: dos commits
rm -rf build/ps2/jp                # build/ está versionado: evita probar copias viejas
make test                          # falla en el caso nuevo
git add -- herramientas/pruebas/<prueba>
git commit -m "test(<dominio>): <qué comprueba>"
make test                          # pasa después del cambio
git add -- <rutas del bloque>
git commit -m "feat(<dominio>): <qué cambia>"

# Forma B: un commit con prueba y cambio; el rojo se ejecuta sobre el padre
git worktree add --detach ../rojo HEAD~1
git show HEAD:herramientas/pruebas/<prueba> > ../rojo/herramientas/pruebas/<prueba>
(cd ../rojo && <orden de la prueba>)      # tiene que fallar
git worktree remove --force ../rojo

# Mutación restaurada
#    (se rompe a mano una línea de la implementación)
make test                          # vuelve a fallar
git checkout -- <ruta>
git diff --quiet -- <ruta> && echo restaurado

# Árbol limpio
git checkout -- build/ compilaciones/
git clean -n -- build/             # listar lo nuevo sin versionar; después: git clean -f -- build/
git status --short                 # vacío

# Integración (solo INTEGRACIÓN, después de la revisión)
git switch feature/idioma-espanol
git merge --no-ff idioma/<rama>
```

Hay una razón para borrar `build/ps2/jp` antes de probar: al restaurar `build/` con `git checkout`, las copias de `build/ps2/jp` quedan con fecha más nueva que su fuente, y `make` no las volvería a convertir.

## 6. Puertas de calidad

| Puerta | Condición | Cómo se comprueba | Estado |
|---|---|---|---|
| F0 | Especificación aprobada | Aprobación del responsable del proyecto en el PR del frente A | Integrada como base de `feature/idioma-espanol`; la aprobación no quedó registrada en el repositorio |
| F1 | CI verde | Jobs `pruebas-pc` y `compilar-ps2` | Cumplida en `a3d0bae` |
| F2 | Refactor sin cambio de comportamiento | `comparar_preprocesado.py` en el PC; job `mismo-binario` en la CI; prueba de caracterización si el binario cambia | Cumplida (ver [trazabilidad.md](trazabilidad.md)) |
| F3 | Pruebas de fuente en verde | `make test` y compilación de PS2 en la CI | Cumplida en `641fe27`, salvo el registro DEV de R-FUE-05 |
| F4 | Cada bloque en rojo → verde → revisión | Evidencia en el PR y [trazabilidad.md](trazabilidad.md) | Verde en `make test` y en la CI 36518116212. Rojo y mutación registrados solo en parte (R-GOB-03) |
| G-FALLO | Glifos de libdebug inspeccionados antes de P4 | Paso de CI añadido en P4 | No se hizo: la pantalla de fallo translitera siempre (R-PORT-03) |
| F5 | Sin hallazgos Alta o Media abiertos | Registro de revisión | Sin registro en el repositorio |
| F6 | Capturas aprobadas | Capturas adjuntas al PR | Pendiente |
| F7 | Definición de terminado | Lista de §8 | Puntos 1–4 cumplidos en `dda9a5f` y esta documentación; el 5, la confirmación del responsable, queda con la fusión a `main` |

## 7. Revisión

- **Formato de cada hallazgo:**

  ```
  [Alta|Media|Baja] Título
  Archivo: ruta:línea
  Riesgo: qué falla y en qué caso
  Recomendación: qué cambiar
  ```

- **Revisión técnica:**
  - requisitos y pruebas del bloque;
  - que el refactor no se mezcle con cambios funcionales;
  - rojo demostrado y mutaciones restauradas;
  - límites y tope de líneas;
  - archivos fuera del dominio o de la zona del bloque;
  - formato de los commits (R-GOB-01).
- **Revisión lingüística:**
  - glosario;
  - tildes y signos de apertura;
  - tuteo;
  - ordinales;
  - nombres de botón de PS2;
  - naturalidad dentro del espacio disponible.
- **Regla general:** el autor nunca revisa su propio bloque.

## 8. Definición de terminado

1. Compila en la CI con la imagen `ps2dev/ps2dev`: `make`, `make DEBUG=1` y `make iso`.
2. `make test` pasa sin regresiones.
3. El Markdown está sincronizado: especificación, trazabilidad, cambios, glosario y README.
4. El árbol queda limpio: `git status --short` vacío y los archivos de `build/` tocados por las pruebas, restaurados.
5. El responsable del proyecto confirma el cierre.

## 9. Verificación

### 9.1 En el PC

```sh
make test                  # pruebas y comprobadores; sin SDK
git clean -fdq -- build && git checkout -- build
git status --short         # vacío
```

### 9.2 En la CI

`.github/workflows/compilacion.yml` corre en cada push y pull request:

1. Job `pruebas-pc`: `make test` en `ubuntu-latest`, sin SDK.
2. Job `compilar-ps2`, en el contenedor `ps2dev/ps2dev` fijado por digest:
   1. `make clean`;
   2. `make`;
   3. `make DEBUG=1`;
   4. `make test`;
   5. `make iso`;
   6. artefactos: el ELF de release y el de `DEBUG=1`, `SMK64ROM.BIN`, `smk64.map` y la ISO.
3. Job `mismo-binario`, solo a mano con una `base`: `comparar_binario.sh` en release y con `DEBUG=1`.
4. Job `publicar`, solo a mano con `publicar=si`: compila desde cero release, `DEBUG=1` y `DEV=1`, corre `make test`, crea la ISO y commitea `build/ps2` y `compilaciones` (commit de publicación; así se generó `dda9a5f`).

### 9.3 Evidencia visual

- Hojas antes/después: `python3 herramientas/texturas_es.py hoja <original.png> <nuevo.png> <salida.png>` (hecho en `4345598`) arma original, nuevo y máscara de diferencias. `make hoja-es` (`a0da3a1`) saca en `build/ps2/es/hojas/` las hojas de cada familia y la de cada cartel de Lakitu, en tira de 16 cuadros.
- Glifos: `python3 herramientas/generar_glifos_es.py <carpeta> --ver` los muestra en texto.
- Las dos salidas se adjuntan al PR.

### 9.4 En PCSX2

1. Compilar la versión DEV:

   ```sh
   . herramientas/entorno.sh
   make DEV=1                 # build/ps2/dev/SLUS_999.99, con la ROM dentro (ROM_STREAM=0)
   ```

2. Copiar el guion de recorrido, `herramientas/guiones/recorrido_textos.txt`, a `host:smk64_input.txt`, la ruta que lee el juego (`codigo/depuracion/guiones_prueba.c:433`). En PCSX2 tiene que estar activado el acceso `host:`. El guion recorre título, menú principal, opciones, selección de piloto y de pista con las cuatro copas, carrera con HUD, pausa, carteles de Lakitu VUELTA 2 y ¡ÚLTIMA! y resultados.
3. Recorrer, a mano o ampliando el guion, lo que el guion no cubre:
   - datos y récords (ordinales «1.º» y «ーーーー»);
   - contrarreloj, VS y batalla, con 3 y 4 jugadores para ver «VTA.» en el HUD;
   - el cartel de Lakitu ¡REVÉS! (ir en sentido contrario);
   - Memory Card: sin tarjeta, con tarjeta y la opción de copiar fantasmas;
   - ceremonia y créditos.
4. Hacer las capturas a mano en las pausas `nota`. La orden `captura` espera a un proceso externo que no está en el repositorio (`guiones_prueba.c:665-679`).
5. Capturar las pantallas que no salen en la versión DEV:
   - Panel: `make DEBUG=1`, activado con L3 + R3. Con `DEV=1` el panel no se compila, porque `MEDIDOR` vale 0.
   - Página de audio: `make DEBUG=1 DEBUG_AUDIO=1`.
   - Parada de diagnóstico: `make DEBUG=1 EXTRA_DEFINES=-DSMK64_BOOT_STOP=<etapa>` (`codigo/sistema/arranque_ps2.c:21-35`).
6. Comprobar que la ISO arranca en PCSX2 y en Play!: `make iso` la deja en `compilaciones/SLUS_999.99.SuperMarioKart64.iso`, y la de `dda9a5f` ya está versionada ahí. El ELF DEV versionado es `build/ps2/dev/SLUS_999.99`.

### 9.5 En TV

- Hace falta al menos una captura en TV o en hardware real para comprobar el sobrebarrido.
- Se usa la ISO por OPL: `make iso` deja una copia en `compilaciones/disco/OPL/CD/`.
- Se elige una pantalla con texto cerca de los bordes, por ejemplo la pausa o un mensaje de Memory Card.
- Al terminar se restaura `compilaciones/` (R-GOB-05), salvo en F7.
