# Plan de trabajo: Mario Kart 64 PS2 en español

Este documento dice cómo se cumplió la [especificación](especificacion.md) y el estado de cada fase. El trabajo se repartió en roles que avanzaron en paralelo, cada uno en su propia rama y su propio worktree (`git worktree add`). Solo INTEGRACIÓN integró.

- **F0 a F7** (localización, hasta 2026-09-29) están cerradas y se conservan como histórico: sus ramas se fusionaron en `feature/idioma-espanol`, que se fusionó a `main` (`3f43c005`). F6 se retiró por [CC-12](cambios.md).
- **F8** (sincronización con el original, 2026-10-11) está cerrada: se integró en `feature/sincronizacion-upstream`, se publicó en `900c9be3` y está en `main` (`af3bfa05`), la versión 1.0.0.
- **F9** (versión 1.1.0, 2026-10-11) está cerrada: se integró en `feature/version-1.1.0`, se publicó en `45bbe10a` y está en `main`.
- **F10** (versión 1.2.0, 2026-10-11) está integrada en `feature/version-1.2.0` (`fd6a4bb7`). Lo que queda por hacer está en [README.md § Pendiente](README.md#pendiente).
- **F11** (versión 1.2.1, 2026-10-11, [CC-31](cambios.md)) está en `feature/capturas-1.2.1` (`863cbc45`) y se publicará como `v1.2.1`.

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
| PORT | Pantallas propias del port y textos del registro | `codigo/depuracion/fuente_5x7.c` e `incluir/depuracion/fuente_5x7.h`; `codigo/depuracion/texto_pantalla.c` y su cabecera; `medidor_rendimiento.c`; `monitor_audio.c`; `depuracion.c`; `incluir/depuracion/marcas_registro.h`; la llamada a `detener_por_gif_trabado` de `codigo/graficos/sintetizador_gs.c`; nombres de fase de `arranque_ps2.c`, `hilos_video_y_audio.inc.c`, `preparacion_carrera.c`, `descomprimir_pista.inc.c`, `pistas_toads_a_big_donut.inc.c` y de las partes de los fuentes de `JP_SRC`; `kart_bomba_y_depuracion.inc.c` | `idioma/port` |
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

### 3.1 F0 a F7 (histórico)

Topología con la que se trabajó, comprobada con `git reflog` el 2026-09-28. Todas las ramas de trabajo se fusionaron en `feature/idioma-espanol`, y esta en `main` (`3f43c005`).

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

### 3.2 F8

Las subramas de F8 salieron de `36fc9e40`, el commit que deja en español los textos nuevos del original, y se integraron en `feature/sincronizacion-upstream` con `git merge --no-ff`. El detalle de cada una está en [F8](#f8-sincronización-con-el-original).

```
main (3f43c005)
 └─ feature/sincronizacion-upstream       integración de F8
     ├─ (36fc9e40)
     │   ├─ sinc/ci                         CC-09                 → 1ac5c96f
     │   ├─ sinc/graficos                   CC-11 G2, G4 y G5     no se integra
     │   ├─ sinc/graficos-g5                CC-11 G5              → 368a5416
     │   ├─ sinc/sistema                    CC-08, CC-11 E3-E5    → bbb11eb6
     │   ├─ sinc/pendientes                 R-FUE-05, R-FUE-07, L2 → cf956b42
     │   ├─ sinc/panel                      L3, R-TEX-07          → 240358fd
     │   └─ sinc/recorrido                  CC-10 (rechazado)     no se integra
     └─ (d5f95cc5)
         ├─ sinc/manual                     documentación (CC-12)
         ├─ sinc/proceso                    documentación (CC-12)
         └─ sinc/doc-traduccion             docs/traduccion (CC-12)
```

### 3.3 F9

`feature/version-1.1.0` nace de `main` en `af3bfa05` y empieza con el registro de CC-13 a CC-17. Las cinco ramas de código salieron de `5b1caac8`, el último registro, y se integraron con `git merge --no-ff`; las dos de documentación salen de `a29bd920`, con el código ya integrado. El detalle de cada una está en [F9](#f9-versión-110).

```
main (af3bfa05)
 └─ feature/version-1.1.0                 integración de F9
     ├─ (5b1caac8)                         registro de CC-13 a CC-17
     │   ├─ v110/graficos                   CC-17, D-01, D-02          → 9289608a
     │   ├─ v110/memoria                    CC-13, D-11, D-12, D-13    → 4465f614
     │   ├─ v110/region                     CC-15                      → d105a89b
     │   ├─ v110/ci-textos                  CC-16, D-09, D-10, D-14, D-15 → 12579275
     │   └─ v110/entrada                    CC-14 y reposo de la cruceta → 4563d816
     └─ (a29bd920)                         las tres pruebas nuevas en make test
         ├─ v110/doc-manual                 manual, notas de la versión y CHANGELOG
         └─ v110/doc-traduccion             docs/traduccion y acta de F9
```

### 3.4 F10

`feature/version-1.2.0` nace de `main` en `fc17498f` y empieza con el registro de CC-18 a CC-27 (`edad2078`). `v120/contrato` fija las opciones del port y las ramas que las usan salen de su último commit, `93cb4d04`. CC-28 y CC-29 se registraron antes de sus ramas. Todas se integraron con `git merge --no-ff`. El detalle de cada una está en [F10](#f10-versión-120).

```
main (fc17498f)
 └─ feature/version-1.2.0                 integración de F10
     ├─ (edad2078)                         registro de CC-18 a CC-27
     │   └─ v120/contrato                   CC-18, contrato de las opciones   → 226a3ce3
     │       └─ (93cb4d04)
     │           ├─ v120/memoria            CC-18, D-16, D-20, D-21, D-22     → 48e951fc
     │           ├─ v120/imagen             CC-20, CC-21                      → 9b206935
     │           ├─ v120/menu               CC-19                             → 8a62d5a1
     │           ├─ v120/trucos             CC-22 a CC-25                     → 159c4396
     │           ├─ v120/deudas             D-07, D-08, D-18, D-19, D-22      → 6e6a2108
     │           ├─ v120/manifiesto         D-05                              → c3e1d30e
     │           └─ v120/ci-emulador        CC-26, D-03, D-04, D-07 (CI)      → 10f290a3
     ├─ (0081dca5)                         registro de CC-28
     │   └─ v120/texturas                   CC-28                             → b7b03ee3
     ├─ 91c7254e, 3bbac652, 3cf36394, 979fcf14   correcciones de INTEGRACIÓN
     ├─ (0f15c448)                         registro de CC-29
     │   └─ v120/texturas-pistas            CC-29, clasificación              → 616213c8
     │       └─ (df9aea49)
     │           ├─ v120/tx-bienvenida      BIENVENIDOS                       → 3017fe10
     │           ├─ v120/tx-ya              YA                                → a087fc2a
     │           ├─ v120/tx-emblemas        1J a 4J                           → 56401560
     │           └─ v120/tx-cruce           PASO A NIVEL                      → fd6a4bb7
     └─ (fd6a4bb7)
         └─ v120/doc-traduccion             docs/traduccion y acta de F10
```

### 3.5 F11

`feature/capturas-1.2.1` nace de `main` con el registro de CC-31 (`8d94ba8d`). De ahí salen `v121/capturas` (comparación estricta, captura nueva, regeneración en la CI y valores del menú de configuración) y `v121/ordinal` (punto del ordinal). El detalle está en [F11](#f11-versión-121).

```
main
 └─ feature/capturas-1.2.1                integración de F11
     └─ (8d94ba8d)                         registro de CC-31
         ├─ v121/capturas                   tolerancia, captura, referencias, valores   → 1bac15d9…863cbc45
         └─ v121/ordinal                    8.º en lugar de 8º.                          → 73aff9e2
```

### 3.6 Verificación al crear una rama

Para una rama nueva se ejecuta todo esto y se adjunta la salida al PR. `merge-base` no sirve como prueba.

```sh
git reflog show <rama> | tail -1                  # punto de creación
git rev-list --count <origen>..<rama>             # commits propios
git log --merges <origen>..<rama>                 # merges inesperados
git log --format='%ae' origin/main..<rama> | sort -u
```

## 4. Fases

| Fase | Roles | Contenido | Rama | Puerta | Estado |
|---|---|---|---|---|---|
| F0 | INTEGRACIÓN | README profesional y `docs/traduccion/`: especificación, glosario, plan, trazabilidad y cambios | `docs/readme-y-especificacion` | El responsable del proyecto aprueba la especificación | Cerrada (histórico): `c86f72c`…`cbc10e8`, base de `feature/idioma-espanol` |
| F1 | INTEGRACIÓN + PRUEBAS | `make test` sin SDK, conversor EUC-JP, metadatos convertidos, `-fsigned-char`, tope de líneas y CI | `idioma/infra` | CI verde | Cerrada (histórico): `f8f9a39`…`476dd52`, integrada en `3d482a8` |
| F2 | FUENTE | Refactor sin cambio de comportamiento: `glifos.inc.c`, `lista_glifos.inc.c` y regla única de avance | `idioma/fuente` | Preprocesado o binario idéntico, o prueba de caracterización (R-GOB-02) | Cerrada (histórico), integrada en `6a050d1` |
| F3 | FUENTE | LUT de 236 entradas, caracteres del español, glifos nuevos, tope del pool y cadenas con tildes | `idioma/fuente` | `prueba_tablas_glifos.py`, `prueba_glifos.c`, `prueba_glifos_es.py` y `prueba_caracteres_es.c` en verde | Cerrada (histórico): `418ea18`…`641fe27`. El registro DEV de R-FUE-05 que faltaba se hizo en F8 |
| F4 | CADENAS ∥ TEXTURAS ∥ PORT | Bloques B1–B7, A0–A6 → B → C y P1–P5 | `idioma/{cadenas,texturas,port}` | Por bloque: rojo → verde → revisión | Cerrada (histórico), integrada en `d3663fd`, `b043668` y `2ae3d3a`. Sin paso G-FALLO (ver P4 y [deuda.md](deuda.md)) |
| F5 | REVISIÓN ×2 | Revisión adversarial de cada bloque y verificación de las mutaciones restauradas | — | Sin hallazgos Alta o Media abiertos | Cerrada (histórico) sin registro en el repositorio (ver [trazabilidad.md](trazabilidad.md), R-GOB-03 y R-GOB-04). Desde F8 la revisión queda en [revisiones/](revisiones/) |
| F6 | Responsable del proyecto | Recorrido en PCSX2 con el guion DEV y al menos una captura en TV | — | Capturas aprobadas | **Retirada por [CC-12](cambios.md)**: la versión se verifica con las pruebas del PC y la CI. La falta de verificación visual es una limitación declarada ([deuda.md](deuda.md), D-06) |
| F7 | INTEGRACIÓN | Integración, regeneración de `build/` y `compilaciones/`, sección «Idioma» del README y requisitos del README sin `iconv` obligatorio | `feature/idioma-espanol` | Definición de terminado de entonces (§8) | Cerrada (histórico): merges, `dda9a5f` (job `publicar`, CI 36518116212) y fusión a `main` (`3f43c005`) |
| F8 | INTEGRACIÓN, autores por rama y REVISIÓN ×2 | Sincronización con el original hasta `ae93f71` (CC-08), CI con Release y limpieza de ramas (CC-09), correcciones con evidencia (CC-11), pendientes técnicos de F3 y F4 y documentación (CC-12) | `feature/sincronizacion-upstream` y `sinc/*` | [Definition of Done](../../CONTRIBUTING.md) y [acta de revisión](revisiones/2026-10-11-sincronizacion.md) sin hallazgos Alta o Media abiertos, salvo el de G5 | Cerrada: publicación `900c9be3` y fusión a `main` (`af3bfa05`), versión 1.0.0. El hallazgo de G5 se resolvió en F9 (CC-17) |
| F9 | INTEGRACIÓN, autores por rama y REVISIÓN ×2 | Versión 1.1.0: Memory Card (CC-13), zona muerta del stick (CC-14), región de la consola (CC-15), publicación comprobada y ELF monolítico (CC-16), prueba del alfa con tramado (CC-17) y deudas D-01, D-02 y D-09 a D-15 | `feature/version-1.1.0` y `v110/*` | [Definition of Done](../../CONTRIBUTING.md) y [acta de revisión](revisiones/2026-10-11-version-1.1.0.md) sin hallazgos Alta o Media abiertos | Cerrada: publicada en `45bbe10a` y en `main` |
| F10 | INTEGRACIÓN, autores por rama y REVISIÓN ×2 | Versión 1.2.0: opciones del port (CC-18), menú CONFIGURACIÓN Y TRUCOS (CC-19), imagen (CC-20, CC-21), trucos (CC-22 a CC-25), emulador en la CI (CC-26), deuda técnica (CC-27), texturas (CC-28, CC-29) y portafolio (CC-30) | `feature/version-1.2.0` y `v120/*` | [Definition of Done](../../CONTRIBUTING.md) y [acta de revisión](revisiones/2026-10-11-version-1.2.0.md) sin hallazgos Alta o Media abiertos | Integrada en `fd6a4bb7`, CI [38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616). Publicada en `9ab41422` y cerrada con la Release `v1.2.0`, la fusión a `main` y la limpieza de ramas ([README.md § Pendiente](README.md#pendiente)) |
| F11 | INTEGRACIÓN, autores por rama y REVISIÓN | Versión 1.2.1: comparación estricta de capturas, captura del menú de configuración y regeneración de las referencias en la CI (CC-31), con los dos defectos visibles que encontró | `feature/capturas-1.2.1` y `v121/*` | [Definition of Done](../../CONTRIBUTING.md) y [acta de revisión](revisiones/2026-10-11-version-1.2.1.md) sin hallazgos Alta o Media abiertos | En `feature/capturas-1.2.1` (`863cbc45`), referencias regeneradas en [38179540046](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38179540046) y [38180265814](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38180265814). Se publicará como `v1.2.1` |

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
- Lo que quedó de F3:
  - el registro DEV de R-FUE-05, hecho en F8 (`a5e97ddf`, `f38d6de6` y `94cdfea5`);
  - la comprobación en PCSX2 del ranking de récords y de «ーーーー», retirada con F6 (CC-12). Los índices de esos glifos los fija `prueba_tablas_glifos.py`.

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

### F8: sincronización con el original

El responsable del proyecto aprobó el plan de F8 el 2026-10-11. Los cambios se registraron antes de tocar el código (`df07cfa9`, `55cbf083`, `73bb9a8f` y `132d4bf5`: CC-08 a CC-11). Después, en `feature/sincronizacion-upstream`:

1. **Fusión** del original hasta `ae93f71` (`9f4d0215`), con `git -c merge.directoryRenames=false merge --no-ff` (CC-08).
2. **Textos nuevos del original en español:** `748db117` (lista negra de `prueba_textos_port.py`, en rojo) y `36fc9e40` (traducción, en verde).
3. **README** con lo nuevo del original (`409a72b9`).
4. **Subramas**, una por frente, desde `36fc9e40`, cada una con su revisión técnica y lingüística ([acta](revisiones/2026-10-11-sincronizacion.md)).
5. **Decisiones del responsable del proyecto:** CC-10 rechazado y G2 y G4 retirados de CC-11 (`b4b37c13`); verificación sin pasos manuales y manual del proyecto (CC-12, `d5f95cc5`).
6. **Integración** con `--no-ff`, en este orden: `sinc/ci` (`1ac5c96f`) → `sinc/graficos-g5` (`368a5416`) → `sinc/sistema` (`bbb11eb6`) → `sinc/pendientes` (`cf956b42`) → `sinc/panel` (`240358fd`).
7. **Documentación** de CC-12 en `sinc/manual`, `sinc/proceso` y `sinc/doc-traduccion`, que salen de `d5f95cc5`.

| Subrama | Contenido | Commits | Integración |
|---|---|---|---|
| `sinc/ci` | `compilar-ps2` con `make DEV=1`, publicación con tipo `build`, jobs `release` y `limpiar-ramas` (CC-09) y `BUILD_ID` 2026-10-11 | `24ed39a0`, `6251a4a6`, `b69f1548` | `1ac5c96f` |
| `sinc/graficos-g5` | G5: el alfa negativo con `G_AC_DITHER` se limita a 0 (CC-11) | `ce98830c` | `368a5416` |
| `sinc/sistema` | Prueba de arranque (CC-08), E3, E4 y E5 (CC-11) y tildes de las pruebas | `664d9013`, `176651ed`, `a86960cf`, `61a88a74`, `372f10ed` | `bbb11eb6` |
| `sinc/pendientes` | Tabla de glifos sin alias del original (G1), tope de `funcion_80095BD0` (R-FUE-07), L2 (CC-11), registro DEV de R-FUE-05 en las tres impresoras y tildes de las pruebas | `e600bd6e`, `697f3af6`, `9adc3192`, `a5e97ddf`, `f38d6de6`, `94cdfea5`, `27199b8f` | `cf956b42` |
| `sinc/panel` | L3 (CC-11), botones de PS2 en el manifiesto (R-TEX-07) y tildes de la prueba | `4612a508`, `ac4fcdae`, `5d901a47`, `4e4cc6f8` | `240358fd` |
| `sinc/graficos` | G5, G2 y G4 con sus correcciones de revisión | `fb6a81c0`, `ae92ebc4`, `d9c9e2ee`, `27091745`, `30dc154e`, `adf45533` | No se integra: solo G5, como `sinc/graficos-g5` |
| `sinc/recorrido` | Cinco guiones de PCSX2 con capturas y hoja de capturas (CC-10) | `bb920d50`…`93cae6c0` (8 commits) | No se integra: CC-10 rechazado |

`sinc/sistema` se integró con los mensajes reescritos para quitar los trailers que encontró REVISIÓN; los árboles son los revisados. La correspondencia de hashes está en el [acta](revisiones/2026-10-11-sincronizacion.md#resumen).

### F9: versión 1.1.0

El responsable del proyecto aprobó el plan de F9 el 2026-10-11. Los cambios se registraron antes de tocar el código (`0c39b416`, `111eb2c7`, `33cbcbb3`, `2857317b` y `5b1caac8`: CC-13 a CC-17). Después, en `feature/version-1.1.0`:

1. **Ramas de código**, una por frente, desde `5b1caac8`, cada una con su revisión técnica y lingüística ([acta](revisiones/2026-10-11-version-1.1.0.md)).
2. **Integración** con `--no-ff`, en este orden: `v110/graficos` (`9289608a`) → `v110/memoria` (`4465f614`) → `v110/region` (`d105a89b`) → `v110/ci-textos` (`12579275`) → `v110/entrada` (`4563d816`). `v110/entrada` esperó al arreglo de la cruceta, el hallazgo Media de su revisión.
3. **Registro ajustado a la revisión:** `f09697ca` (CC-13, CC-14 y CC-17) y `6519d73e` (CC-14 con el reposo de la cruceta).
4. **`make test`** con las tres pruebas nuevas (`a29bd920`): 31 pruebas y el tope de líneas.
5. **Documentación** en `v110/doc-manual` y `v110/doc-traduccion`, que salen de `a29bd920`.

| Rama | Contenido | Commits | Integración |
|---|---|---|---|
| `v110/graficos` | Alfa con tramado en una función pura, con prueba (CC-17; salda D-01 y D-02) | `ff313bc5`, `d41996f7` | `9289608a` |
| `v110/memoria` | Tarjeta nueva sin pisar la copia más nueva, espera con el reloj, segundo borrado con `mc_ok` y `mcGetInfo` fuera de la pila (CC-13; salda D-11 a D-13) | `2e578b4b`, `b989feca`, `e4937a28`, `41441ae5`, `3e62e63e`, `abe7c205`, `8c69e253` | `4465f614` |
| `v110/region` | Región de la consola a partir de `rom0:ROMVER` y registro al arrancar (CC-15) | `807d2c45`, `3b11daa5`, `ac1a1090` | `d105a89b` |
| `v110/ci-textos` | Publicación comprobada y ELF monolítico en la Release (CC-16); D-09, D-10, D-14 y D-15; registro «ritmo» en lugar de «3-4P» | `bb8d41bd`, `3e2067a4`, `1d8f5670`, `7e9edfaa`, `c641d19b`, `4bdd41a8`, `b780d986` | `12579275` |
| `v110/entrada` | Zona muerta del stick de 24 a 8 y reposo propio de la cruceta (CC-14) | `1fc4c437`, `4a48ff6a`, `dcbe656e`, `ddbdc023`, `34ab306d`, `2b37f61f` | `4563d816` |

El arreglo de la cruceta se revisó con otros hashes y el mismo parche; la correspondencia está en el [acta](revisiones/2026-10-11-version-1.1.0.md#resumen).

### F10: versión 1.2.0

El responsable del proyecto aprobó el plan de F10 el 2026-10-11, con la maqueta del menú. Los cambios se registraron antes de tocar el código: CC-18 a CC-27 en `edad2078`, CC-28 en `0081dca5` y CC-29 en `0f15c448`. CC-30 (portafolio) se registró con la documentación. Después, en `feature/version-1.2.0`:

1. **Contrato** de las opciones del port en `v120/contrato` (`93cb4d04`), del que salen las ramas que lo usan.
2. **Ramas de código**, una por frente, cada una con su revisión técnica y lingüística ([acta](revisiones/2026-10-11-version-1.2.0.md)).
3. **Integración** con `--no-ff`, en el orden de la tabla. Los hallazgos que pedían tocar zonas compartidas se resolvieron en INTEGRACIÓN: `91c7254e` (DESBLOQUEAR TODO al reconstruir el menú), `3bbac652` (opciones escritas antes de subir su versión), `3cf36394` (pruebas nuevas en `make test`) y `979fcf14` (el emulador exige «vídeo: PMODE 8046»).
4. **Texturas sin revisar** (CC-29): clasificación en `v120/texturas-pistas` y traducción de las 15 pendientes en cuatro ramas paralelas.
5. **CI** en verde: [38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616), con el job del emulador.
6. **Documentación** en `v120/doc-traduccion` y las demás ramas de documentación, que salen de `fd6a4bb7`.

| Rama | Contenido | Commits | Integración |
|---|---|---|---|
| `v120/contrato` | `OpcionesPort` y formato de `SMK64CFG.DAT` (CC-18) | `d6bf7381`, `a760841b`, `93cb4d04` | `226a3ce3` |
| `v120/memoria` | `SMK64CFG.DAT` en el hilo de guardado y arnés de libmc (CC-18; D-16, D-20, D-21, D-22) | `36796171`, `289e9c78`, `2c83c0f8`, `c94152e0`, `c69d9ef4`, `b38d42c4`, `2275f2c8`, `098af916`, `8c022b34`, `1727504e`, `d7e296f9` | `48e951fc` |
| `v120/imagen` | Antiparpadeo, posición, CON BANDAS y PANORÁMICO (CC-20, CC-21) | `deeba019`, `fa835b62`, `9173dde8`, `064830d8`, `92c1f1f3`, `fd4286e3`, `c52e2f8d`, `761d735d`, `2093202d`, `d8ebb3ac`, `d5ee5381` | `9b206935` |
| `v120/menu` | Menú CONFIGURACIÓN Y TRUCOS (CC-19) | `7abb1f92`, `7c5439e4`, `b8954cee`, `146b23af`, `be1248ff` | `8a62d5a1` |
| `v120/trucos` | DESBLOQUEAR TODO, OBJETO, 200CC y RIVALES SIN VENTAJA (CC-22 a CC-25) | `9d310c2c`, `be355571`, `4efcf0be`, `5a19ff97`, `038c39c0`, `c80fe61e`, `0e75a425`, `f46bc633`, `a6397211`, `4c0323bf` | `159c4396` |
| `v120/deudas` | D-07, D-08, D-18, D-19 y D-22 (CC-27) | `0c962092`, `00b25b9d`, `9a92bc41`, `e0f76493`, `bd70c399`, `3d67d29d`, `e16f26d8`, `93231a07`, `64805e8c`, `a989c0f5`, `d2ce4c18`, `b06d4cbe`, `8e311363`, `278f45a5`, `ab75b9aa`, `0f75b754`, `dc6d4730`, `3a30f145` | `6e6a2108` |
| `v120/manifiesto` | Filas de carpeta del manifiesto (D-05) | `fee9830b`, `22fbc484`, `9032ab75`, `7638072f`, `de397d10`, `742d480c`, `d57a6bef` | `c3e1d30e` |
| `v120/texturas` | Reconstrucción del HUD y de los menús (CC-28) | `3b5e4aef`, `d7b3feb9`, `2175d03b`, `9d9ac85e`, `bace922a` | `b7b03ee3` |
| `v120/ci-emulador` | Job del emulador, tope de la ROM, build incremental y fuente de libdebug (CC-26; D-03, D-04, D-07) | `7491fd24`, `98a042b7`, `a7bae5d4`, `570a0a12`, `99fa9b5c`, `a27fd80f`, `2c3a8b29`, `04adf1f6`, `f48b7a41`, `68bc6dce` | `10f290a3` |
| `v120/texturas-pistas` | Clasificación de las texturas sin revisar (CC-29) | `a6fa679e`, `4216877e`, `431c3186`, `df9aea49` | `616213c8` |
| `v120/tx-bienvenida` | BIENVENIDOS (D-24) | `fe010d2a`, `cb32c871` | `3017fe10` |
| `v120/tx-ya` | YA (D-24) | `bb31482f`, `3505ff26` | `a087fc2a` |
| `v120/tx-emblemas` | 1J a 4J (D-24) | `bc4516de`, `caf7756f` | `56401560` |
| `v120/tx-cruce` | PASO A NIVEL (D-24) | `f7866dd3`, `625105f4` | `fd6a4bb7` |

### F11: versión 1.2.1

El responsable del proyecto aprobó CC-31 el 2026-10-11 y se registró antes de tocar el código (`8d94ba8d`). Después, en `feature/capturas-1.2.1`:

1. **Comparación estricta:** la prueba del bloque de 32×16 en rojo (`1bac15d9`) y la tolerancia de 0,001 (`632050ac`).
2. **Captura nueva** del menú CONFIGURACIÓN Y TRUCOS (`a7ab8019`) y referencias revisadas a ojo (`3a022b42`, `f4b86834`).
3. **Defectos visibles** que la revisión de las capturas encontró: los valores tenues del menú de configuración (`a5464408`, `39bb214b`, `42a13caf`) y el ordinal «8º.» (`v121/ordinal`, `73aff9e2`).
4. **Regeneración en la CI** con `regenerar_referencias=sí` (`17901393`), usada en las ejecuciones [38179540046](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38179540046) (`6933dd08`) y [38180265814](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38180265814) (`863cbc45`).
5. **Documentación** en `v121/docs`.

| Rama | Contenido | Commits | Integración |
|---|---|---|---|
| `v121/capturas` | Tolerancia, captura `configuracion`, referencias, regeneración en la CI y valores del menú de configuración (CC-31) | `1bac15d9`, `632050ac`, `a7ab8019`, `3a022b42`, `f4b86834`, `a5464408`, `17901393`, `6933dd08`, `39bb214b`, `42a13caf`, `863cbc45` | En `feature/capturas-1.2.1` |
| `v121/ordinal` | Punto del ordinal antes de la «º» volada (CC-31) | `9ec3b950`, `33979fbf` | `73aff9e2` |

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
| F3 | Pruebas de fuente en verde | `make test` y compilación de PS2 en la CI | Cumplida en `641fe27`; el registro DEV de R-FUE-05 se cumplió en F8 |
| F4 | Cada bloque en rojo → verde → revisión | Evidencia en el PR y [trazabilidad.md](trazabilidad.md) | Verde en `make test` y en la CI 36518116212. Rojo y mutación registrados solo en parte (R-GOB-03) |
| G-FALLO | Glifos de libdebug inspeccionados antes de P4 | Paso de CI añadido en P4 | No se hizo: la pantalla de fallo translitera siempre (R-PORT-03; [deuda.md](deuda.md), D-07) |
| F5 | Sin hallazgos Alta o Media abiertos | Registro de revisión | Sin registro en el repositorio |
| F6 | Capturas aprobadas | Capturas adjuntas al PR | Retirada por CC-12 |
| F7 | Definición de terminado de entonces | Lista de §8 | Cumplida: `dda9a5f` y fusión a `main` (`3f43c005`) |
| F8 | Sin hallazgos Alta o Media abiertos | [Acta de revisión](revisiones/2026-10-11-sincronizacion.md) | Cumplida salvo G5, integrado sin la prueba que pedía CC-11 y a la espera de la confirmación del responsable del proyecto |

## 7. Revisión

- **Formato de cada hallazgo:** el del acta de revisión de [CONTRIBUTING.md](../../CONTRIBUTING.md#acta-de-revisión).
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
- **Registro:** desde F8, la revisión de cada integración queda en un acta en [revisiones/](revisiones/), con el formato de [CONTRIBUTING.md](../../CONTRIBUTING.md). La de F8 es [2026-10-11-sincronizacion.md](revisiones/2026-10-11-sincronizacion.md); la de F9, [2026-10-11-version-1.1.0.md](revisiones/2026-10-11-version-1.1.0.md), la de F10, [2026-10-11-version-1.2.0.md](revisiones/2026-10-11-version-1.2.0.md), y la de F11, [2026-10-11-version-1.2.1.md](revisiones/2026-10-11-version-1.2.1.md).

## 8. Definición de terminado

Desde CC-12, la única Definition of Done es la de [CONTRIBUTING.md](../../CONTRIBUTING.md).

F0 a F7 se cerraron con la lista de entonces: compila en la CI con la imagen `ps2dev/ps2dev` (`make`, `make DEBUG=1` y `make iso`); `make test` pasa sin regresiones; el Markdown está sincronizado; el árbol queda limpio; y el responsable del proyecto confirma el cierre.

## 9. Verificación

### 9.1 En el PC

```sh
make test                  # pruebas y comprobadores; sin SDK
git clean -fdq -- build && git checkout -- build
git status --short         # vacío
```

### 9.2 En la CI

`.github/workflows/compilacion.yml` corre en cada push y pull request, y a mano (`workflow_dispatch`). Tiene siete jobs; el detalle de cada uno está en R-INF-05 de la [especificación](especificacion.md) y el procedimiento de publicación, en el [manual técnico](../manual/tecnico.md).

1. `pruebas-pc`: `make test` sin SDK.
2. `compilar-ps2`: `make clean`, `make`, el tope de crecimiento de la ROM y el build incremental (desde F10), `make DEBUG=1`, `make DEV=1` (desde F8), `make test`, la inspección de la fuente de libdebug (desde F10) y `make iso` en el contenedor `ps2dev/ps2dev`.
3. `emulador` (desde F10, CC-26): arranca dos veces el ELF de DEV en Play! 0.72 sin BIOS, revisa el registro y compara las capturas de título, menú, configuración (desde F11) y carrera con `herramientas/emulador/referencias/` y entre sí, con una tolerancia del 0,1 % desde F11 (CC-31). Con `regenerar_referencias=sí`, escribe y commitea las referencias nuevas, que se revisan a ojo antes de integrar.
4. `mismo-binario`, a mano con una `base`.
5. `publicar`, a mano con `publicar=si` o `sí`: commit de publicación `build(compilaciones): binarios e ISO en español`. Así se generó `dda9a5f` en F7 (entonces con tipo `chore`). Desde F9 solo omite el commit si no hay nada preparado (`git diff --cached --quiet`); cualquier otro fallo detiene el job (CC-16).
6. `release`, a mano con `release=<etiqueta>`, en el contenedor `ps2dev/ps2dev`: comprueba que el SHA-256 de la ISO versionada está en `docs/versiones/<etiqueta>.md`, compila `make MONOLITICO=1` y publica la ISO, `SLUS_999.99.monolitico.elf` y un `SHA256SUMS` con las dos líneas, con esas notas (CC-16). Se lanza en otra ejecución, sobre `main`, después de fusionar el commit de publicación; el orden completo está en el [manual técnico](../manual/tecnico.md#ci-y-publicación).
7. `limpiar-ramas`, a mano con `limpiar_ramas=si` o `sí`: borra las ramas remotas cuya punta ya está en `main`.

### 9.3 Evidencia visual

- Hojas antes/después: `python3 herramientas/texturas_es.py hoja <original.png> <nuevo.png> <salida.png>` (hecho en `4345598`) arma original, nuevo y máscara de diferencias. `make hoja-es` (`a0da3a1`) saca en `build/ps2/es/hojas/` las hojas de cada familia y la de cada cartel de Lakitu, en tira de 16 cuadros.
- Glifos: `python3 herramientas/generar_glifos_es.py <carpeta> --ver` los muestra en texto.
- Son herramientas de apoyo para quien cambie el arte. Desde CC-12 ninguna verificación depende de mirar sus salidas: las medidas las comprueban las pruebas (`prueba_composicion_es.py`, `prueba_hojas_es.py` y las demás de R-TEX).

### 9.4 En PCSX2 y en TV (retirado)

El recorrido en PCSX2 con `herramientas/guiones/recorrido_textos.txt` y la captura en TV eran la fase F6. [CC-12](cambios.md) la retiró: la versión se verifica con las pruebas del PC y la CI, y nadie corre recorridos ni manda capturas. Desde F10 la CI arranca el juego en Play! (CC-26); lo que eso deja sin comprobar está en los [límites declarados](especificacion.md#9-límites-declarados). Cómo jugar en PCSX2, en Play! o en una PS2 está en el [manual de usuario](../manual/usuario.md).
