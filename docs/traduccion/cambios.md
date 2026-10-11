# Registro de cambios de la especificación

Aquí se registra todo cambio de requisito, límite, escala, paso de interlineado, término o texto de reserva, y toda diferencia entre lo ejecutado y el plan aprobado. El registro se hace **antes** de tocar el código. Las diferencias ya ejecutadas se registran en cuanto se detectan.

## Reglas

- Cada cambio tiene un identificador `CC-NN` que no se reutiliza.
- **Estados:** `propuesto`, `aprobado`, `rechazado` o `aplicado`.
- **Aprobación:**
  - la dan INTEGRACIÓN y REVISIÓN;
  - si el cambio toca una decisión cerrada de la especificación o el plan aprobado, también el responsable del proyecto.
- **Evidencia:** un cambio de maquetación se justifica con medidas y con la prueba del PC que las comprueba. Desde CC-12 no se piden capturas; hasta entonces se pedía una captura antes/después (PCSX2 y, si afectaba a los bordes, TV).
- **Al aplicarlo:**
  - se anota el commit;
  - se actualizan `prueba_textos_lugares.inc.c` o `prueba_textos_esperados.inc.c` si corresponde;
  - se enlaza desde [trazabilidad.md](trazabilidad.md).

## Plantilla

```markdown
### CC-NN: título breve

- Estado: propuesto
- Fecha: AAAA-MM-DD
- Requisitos afectados: R-…
- Motivo (con medidas):
- Cambio propuesto:
- Archivos y líneas:
- Alternativas descartadas:
- Evidencia requerida:
- Aprobación: INTEGRACIÓN — / REVISIÓN — / responsable del proyecto (si aplica) —
- Commit: —
```

## Entradas

### CC-01: escala de la caja de récords

- **Estado:** aplicado
- **Fecha:** 2026-09-28
- **Requisitos afectados:** R-TXT-04
- **Motivo:**
  - La caja de récords de la selección de pista mide 0x64 = 100 px (`codigo/menus/elementos_menu/manejar_menus.inc.c:516-519`).
  - El texto empieza en `column + 8` (`dibujar_menus.inc.c:320`), así que quedan 92 px.
  - El tipo `TIPO_ITEM_MENU_065` («BEST RECORDS») se dibuja con escala horizontal 0,6, y el `TIPO_ITEM_MENU_066` («BEST LAP») con 0,8 (`dibujar_menus.inc.c:313-321`).
  - «MEJOR VUELTA» mide 138 unidades de avance. A 0,8 ocupa 110,4 px y no cabe en los 92 px.
- **Cambio propuesto:**
  - La escala horizontal del tipo 066 pasa de 0,8 a 0,6, igual que la del 065: 138 × 0,6 = 82,8 px.
  - La escala vertical sigue en 0,8.
- **Archivos y líneas:** `codigo/menus/elementos_menu/dibujar_menus.inc.c:313-321`.
- **Alternativas descartadas:** abreviar a «MEJOR VTA», porque contradice el glosario.
- **Evidencia requerida:** captura antes/después de la selección de pista en contrarreloj. La medida la comprueba `prueba_textos.c` con el límite de la caja en `prueba_textos_lugares.inc.c`; la captura se retiró con F6 (CC-12).
- **Aprobación:** no quedó registrada aparte; el cambio se integró con su rama en `feature/idioma-espanol`.
- **Commit:** `b061832` (escala horizontal de la caja de la mejor vuelta de 0,8 a 0,6, «MEJOR VUELTA» llegaba a x = 319 con la caja en 297).

### CC-02: interlineado de los mensajes de varias líneas

- **Estado:** aplicado, con otra solución
- **Fecha:** 2026-09-28
- **Requisitos afectados:** R-TXT-05
- **Motivo.** En estos bucles, el paso es menor que `ceil(20,6·e)`. Si una línea a partir de la segunda lleva una mayúscula con diacrítico, la tilde toca la línea anterior. La lista definitiva la calcula `prueba_textos.c`. Los sitios conocidos son:

| Sitio | Paso | Escala | Paso mínimo |
|---|---|---|---|
| `menus_pausa.inc.c:352` | 0xD (13) | 0,75 | 16 |
| `menus_pausa.inc.c:365, 373, 392, 399, 409, 415` | 0xD (13) | 0,8 | 17 |
| `menus_pausa.inc.c:403, 540` | 0xF (15) | 0,8 | 17 |
| `info_pistas_y_tiempos.inc.c:91, 103` | 0xD (13) | 0,65 | 14 |
| `info_pistas_y_tiempos.inc.c:159, 173, 210` | 0x14 (20) | 1,0 | 21 |
| `info_pistas_y_tiempos.inc.c:719-723, 786` | 0xD (13) | 0,75 | 16 |
| `info_pistas_y_tiempos.inc.c:743` | 0xD (13) | 0,7 | 15 |
| `info_pistas_y_tiempos.inc.c:762` | 0xD (13) | 0,8 | 17 |
| `info_pistas_y_tiempos.inc.c:770, 780` | 0xD (13) | 0,67 | 14 |
| `info_pistas_y_tiempos.inc.c:774` | 0xF (15) | 0,75 | 16 |
| `dibujar_menus.inc.c:733` | 0xD (13) | 0,65 | 14 |

- **Cambio propuesto.** En cada sitio se elige una de dos opciones, la que no saque el bloque de su cuadro:
  - bajar la escala hasta `e ≤ p / 20,6`: con paso 13, e ≤ 0,63; con paso 15, e ≤ 0,72; con paso 20, e ≤ 0,97;
  - subir el paso hasta `ceil(20,6·e)`.
- **Si no se puede:** queda la alternativa de redactar el texto sin mayúsculas acentuadas a partir de la segunda línea. Se registra como excepción, con su texto.
- **Archivos y líneas:** los de la tabla.
- **Alternativas descartadas:** comprimir la mayúscula acentuada dentro de 16 filas. La letra quedaría más baja que las demás.
- **Evidencia requerida:** capturas antes/después de cada pantalla afectada, comprobando que la última línea no se sale del cuadro. Por ejemplo, en `menus_pausa.inc.c:365` las líneas van en `y = 0x6E + p·i`: subir el paso a 0x11 (17, el mínimo con e = 0,8) mueve la séptima línea de y = 188 a y = 212.
- **Lo aplicado:** no se cambió ningún paso ni ninguna escala vertical. `prueba_textos.c` (`probar_interlineado`) mide la regla con más precisión: con un paso menor que `ceil(20,6·e)`, una letra con signo en la segunda línea o siguientes no puede quedar bajo la tinta de la línea anterior. Con los textos traducidos, ningún lugar registrado en `prueba_textos_lugares.inc.c` incumple esa condición, así que no hizo falta mover líneas ni registrar excepciones.
- **Aprobación:** no quedó registrada aparte; el cambio se integró con su rama en `feature/idioma-espanol`.
- **Commit:** `ae9dc3c` (prueba) y los bloques de traducción que la mantienen en verde.

### CC-03: ampliación del HUD

- **Estado:** aplicado
- **Fecha:** 2026-09-28
- **Requisitos afectados:** R-TEX-05
- **Motivo:**
  - En `tiempo_hud` (32 × 16), «TIME» ocupa las columnas 0-30. En `vuelta_hud` (32 × 8), «LAP» ocupa las columnas 0-24.
  - Con los glifos del HUD, TIEMPO mide unos 46 px y VUELTA unos 48-50 px.
  - El código deja menos sitio que la propia textura y dibuja las tres texturas con 32 px de ancho:
    - los dígitos de vuelta van en `vuelta_x + 0x1C` y en `vuelta_despues_imagen_{1,2}_x + 0x1C` (`ventana_item_y_minimapa.inc.c:483, 544, 550`), así que quedan unos 28 px útiles;
    - en pantalla dividida, los dígitos van en `vuelta_x + 0xC` (`hud_pantalla_dividida.inc.c:51`);
    - TIME se dibuja en `temporizador_x − 0x13` (`ventana_item_y_minimapa.inc.c:789-790`) y en `tiempo_x_finalizacion_vuelta_{1,2} − 0x13` para los tiempos de vuelta (`:532-533`, `:537-538`);
    - `comun_textura_hud_vuelta_tiempo` se dibuja en `temporizador_x − 0x13` con `dibujar_textura_32x_hud_2d_16` (`:793-794`).
- **Cambio propuesto:**
  - Las texturas `tiempo_hud`, `tiempo_vuelta_hud` y `vuelta_hud` pasan a ser más anchas. El ancho final se fija en el manifiesto.
  - Todas las llamadas que las dibujan con 32 px de ancho pasan a la variante del ancho nuevo.
  - Se ajustan los desplazamientos para que no haya solapamiento en 1, 2, 3 y 4 jugadores.
  - Solo se abrevia en pantalla dividida si la palabra no cabe, y eso se registra como un CC aparte.
- **Archivos y líneas:**
  - `codigo/graficos/dibujar_objetos/ventana_item_y_minimapa.inc.c:481-484, 532-533, 537-538, 542-551, 789-790, 793-794`;
  - `codigo/carrera/objetos_y_efectos/hud_pantalla_dividida.inc.c:48-51, 66, 103`;
  - las texturas del HUD en `recursos/es/`.
- **Alternativas descartadas:**
  - abreviar siempre (VTA., TPO.), porque contradice la decisión cerrada del HUD;
  - una familia de glifos del HUD más estrecha, porque rompe la coherencia visual con el resto del HUD.
- **Evidencia requerida:** prueba de no solapamiento en `prueba_texturas_es.py` sobre todas las llamadas, hoja del HUD y capturas en carrera con 1, 2 y 4 jugadores, incluida la pantalla de tiempos de vuelta.
- **Lo aplicado:** las tres texturas pasan a 64 de ancho y se dibujan alineadas por la derecha donde terminaban las de 32 (`PALABRA_HUD_X`), así el borde que da a los dígitos no se mueve. La prueba de no solapamiento está en `prueba_hud_es.py`, de 1 a 4 jugadores. Con 3 y 4 jugadores VUELTA no cabe y se abrevia: ver CC-07. Las capturas en carrera se retiraron con F6 (CC-12).
- **Aprobación:** no quedó registrada aparte; el cambio se integró con su rama en `feature/idioma-espanol`.
- **Commit:** `7e0d345`.

### CC-04: `modo_mario_gp` sin traducir en el manifiesto

- **Estado:** aplicado
- **Fecha:** 2026-09-28
- **Requisitos afectados:** R-TEX-02, R-TEX-04
- **Motivo:** el plan aprobado traduce `modo_mario_gp` a GRAN PREMIO y solo admite conservar «MARIO GP» si no pasa la prueba de ajuste. El manifiesto de `4345598` ya lo marca con `motivo_no` «nombre del modo», sin prueba de ajuste registrada.
- **Cambio propuesto:** hacer la prueba de ajuste de «GRAN PREMIO» en la textura de 64 × 18. Si pasa, la fila pierde el motivo y lleva `texto_es`. Si no pasa, se conserva «MARIO GP» con la medida como evidencia.
- **Archivos y líneas:** `recursos/es/texturas.tsv`, fila `modo_mario_gp`.
- **Alternativas descartadas:** abreviar a «G. PREMIO» sin registrar la medida.
- **Evidencia requerida:** medida del texto compuesto y hoja antes/después.
- **Lo aplicado:** «GRAN PREMIO» pasa la prueba de ajuste en dos líneas, «GRAN» / «PREMIO», con las letras diminutas del juego. La fila lleva `texto_es` y ya no tiene motivo. La medida la comprueba `prueba_composicion_es.py` y la hoja sale con `make hoja-es`.
- **Aprobación:** no quedó registrada aparte; el cambio se integró con su rama en `feature/idioma-espanol`.
- **Commit:** `788a957`.

### CC-05: valor de la marca de pánico del registro

- **Estado:** aplicado
- **Fecha:** 2026-09-28
- **Requisitos afectados:** R-PORT-04
- **Motivo:** el registro vuelca al PC en el momento las líneas que contienen «PANIC» (`codigo/depuracion/depuracion.c:99`). PORT define `MARCA_PANICO` en español, así que la línea de pánico se escribe en español. Cambiar el valor de una marca es un cambio de especificación.
- **Cambio propuesto:** `MARCA_PANICO` vale «PANICO». Productor y consumidor usan la macro, así que el volcado no cambia de comportamiento.
- **Archivos y líneas:** `incluir/depuracion/marcas_registro.h` (nuevo) y `codigo/depuracion/depuracion.c:99-100, 401`.
- **Alternativas descartadas:** conservar «PANIC», porque deja una palabra en inglés en el registro.
- **Evidencia requerida:** `prueba_textos_port.py` en verde y una línea de pánico en el registro de `make DEBUG=1`.
- **Lo aplicado:** primero «PANICO» (`91b2a89`) y después «PÁNICO», con tilde como el resto de mayúsculas del port (`823a0c8`). `strstr` compara bytes, así que el consumidor encuentra la marca en UTF-8, y la pantalla de fallo la muestra sin tilde por `quitar_diacriticos`. `prueba_textos_port.py` pide «pánico» con tilde. La línea de pánico en el registro de `make DEBUG=1` no se ha capturado.
- **Aprobación:** no quedó registrada aparte; el cambio se integró con su rama en `feature/idioma-espanol`.
- **Commit:** `9d2b711` (macros), `91b2a89` y `823a0c8`.

### CC-06: diferencias entre lo ejecutado y el plan aprobado

- **Estado:** aplicado
- **Fecha:** 2026-09-28
- **Requisitos afectados:** R-INF-01, R-INF-02, R-INF-05, R-FUE-01, R-FUE-07, R-FUE-08, R-TEX-03, R-GOB-01, R-GOB-02, R-GOB-03
- **Motivo:** lo ejecutado en F1–F7 se apartó del plan en estos puntos. La especificación describe lo ejecutado.

| Plan aprobado | Lo ejecutado | Commit |
|---|---|---|
| Las subramas nacen de `feature/idioma-espanol` | `idioma/infra` nace de `main`; `idioma/fuente` e `idioma/texturas`, de `idioma/infra`; `idioma/cadenas` e `idioma/port`, de `idioma/fuente`. Se integran en `feature/idioma-espanol` en el orden infra → fuente → texturas → cadenas → port | — |
| Solo `test`, `clean` y `es` sin SDK | `OBJETIVOS_PC := test clean herramientas es hoja-es` | `f8f9a39`, `37633d3`, `a0da3a1` |
| El conversor lleva una lista blanca de caracteres sacada de la lista de glifos | Sin lista blanca: la prueba de textos valida los caracteres con el decodificador real. ’ y ” tienen glifo; … y “ no | `727c7ed` |
| CI en `.github/workflows/ps2.yml` | CI en `.github/workflows/compilacion.yml`, con el job `mismo-binario` añadido | `7387d01`, `a3d0bae` |
| Puerta de F2: `nm -n -S` idéntico | `comparar_preprocesado.py` en el PC, `mismo-binario` en la CI y, para `d87d14f`, prueba de caracterización | `cb36bbc`, `a3d0bae` |
| `textos_menu.inc.c` en F2, dentro de FUENTE | Lo hizo CADENAS al empezar F4 | `15136d3` |
| F3 empieza por el tope del pool | Orden real: LUT, lista X-macro, caracteres, regla de avance, glifos, pool, glifos en la ROM y cadenas con tildes | `4e35120`…`641fe27` |
| `ASSERT_ESTATICO(… == GLIFOS_TOTAL)` | El `ASSERT_ESTATICO` compara la cuenta de las dos tablas; `prueba_tablas_glifos.py` fija el total de 247 | `4e35120`, `1c9545d` |
| Diacrítico con `case 26` de alto 8 en `cargar_texturas_menu.inc.c` | `imprimir_letra` dibuja la segunda parte con `dibujar_diacritico_glifo` y `vtx_glifo_diacritico` | `5718601` |
| Glifos con vista previa PNG (`--vista-previa`) | Los glifos se escriben en `$(BUILD)/glifos_es/`, no se versionan, y `--ver` los muestra en texto | `9abb8d7` |
| Todas las texturas traducidas en MIO0 con `TAMANIO_ES_*` | PULSA START es RGBA16 crudo de 159 × 16 y sigue así; los puestos y las palabras del HUD son `.inc.c` que se superponen desde `build/ps2/es` | `78b7177`, `7e0d345`, `a4676b3` |
| Un commit por bloque de traducción | Par de commits (prueba y cambio) o uno solo con los dos. En los bloques de CADENAS que cambiaron prueba y texto en un solo commit, el rojo y las mutaciones se registraron después en el mensaje de `da631b0` | `da631b0` |
| Formato `tipo(dominio): descripción` sin excepciones | Se aceptan también `ci: descripción` y los mensajes de merge `Merge branch '…'` | `7387d01`, `6dd12e7`, `a3d0bae`, `236962b` |
| Quitar `iconv` de los requisitos del README | `iconv` ya no hace falta para compilar. Solo lo usa, si está instalado y tiene JIS X 0212, `prueba_convertir_eucjp.py` para comparar. Los requisitos del README ya no lo piden | `476dd52`; README en la sincronización final |
| Refactor con preprocesado o binario idéntico | `4da5ab9` y `47a7371` sacan literales a variables: el binario cambia (punteros y símbolos nuevos), el texto dibujado no. La verificación, deshacer el refactor a mano y obtener el árbol del padre, está en el mensaje de `6794945` | `4da5ab9`, `47a7371`, `6794945` |
| Solo los tipos `feat`, `fix`, `refactor`, `test`, `build`, `ci` y `docs` | Cuatro commits usan `chore`: `31eaf62`, `da631b0`, `6794945` y el de publicación `dda9a5f`. No se reescribió la historia ya integrada | `31eaf62`, `da631b0`, `6794945`, `dda9a5f` |
| `feature/idioma-espanol` sale en un PR en borrador hacia `main` | `feature/idioma-espanol` nace de `docs/readme-y-especificacion` (`cbc10e8`) e integra las cinco ramas con `--no-ff` en el orden fijado; se fusiona a `main` y las ramas de trabajo se borran | `3d482a8`, `6a050d1`, `d3663fd`, `b043668`, `2ae3d3a` |

- **Alternativas descartadas:** rehacer las ramas según el plan. Se descarta porque lo publicado tiene CI en verde y la topología real respeta las dependencias entre roles.
- **Evidencia requerida:** la de [trazabilidad.md](trazabilidad.md).
- **Aprobación:** no quedó registrada aparte.
- **Commit:** los de la tabla.

### CC-07: VTA. en el HUD con 3 y 4 jugadores

- **Estado:** aplicado
- **Fecha:** 2026-09-29 (registrado después de aplicarlo)
- **Requisitos afectados:** R-TEX-05
- **Motivo:** con 3 y 4 jugadores, VUELTA no cabe junto a los dígitos de vuelta dentro de la parte de pantalla de cada jugador. La decisión cerrada del HUD admite abreviar solo en ese caso y exige registrarlo.
- **Cambio:** la textura chica de VUELTA (`vuelta_hud`, manifiesto `VUELTA|VTA.`) lleva «VTA.» en las filas 8 a 15, y el código la usa con 3 y 4 jugadores.
- **Archivos:** `recursos/es/inc/recursos/comunes/texturas/`, `codigo/carrera/objetos_y_efectos/hud_pantalla_dividida.inc.c` y `ventana_item_y_minimapa.inc.c`.
- **Alternativas descartadas:** abreviar también con 1 y 2 jugadores.
- **Evidencia:** `prueba_hud_es.py` (ninguna palabra pisa dígitos ni la parte de otro jugador, de 1 a 4 jugadores). Las capturas con 3 y 4 jugadores se retiraron con F6 (CC-12).
- **Aprobación:** no quedó registrada aparte; se registra aquí porque el cambio ya está integrado.
- **Commit:** `7e0d345`.

### CC-08: sincronización con el repositorio original hasta `ae93f71`

- **Estado:** aplicado
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-FUE-01, R-PORT-02, R-PORT-04, R-INF-05, R-GOB-01, R-GOB-05
- **Motivo:** `anthoo582/mario-kart-64-ps2` agregó `c2ed147` y `ae93f71` sobre la base común `0e7b7d5`. Traen el multitap, tiempos límite en el IOP, el CD y la Memory Card, el arranque desde OPL sin reiniciar el IOP, la caché de texturas por columnas, el tramado por primitiva, 60 FPS más estables y la orden `captura` de los guiones. `git merge-tree` da 9 archivos de código en conflicto (12 trozos) y 95 de `build/` y `compilaciones/`.
- **Cambio:**
  - **Fusión:** `git -c merge.directoryRenames=false merge --no-ff`. Sin esa opción, git trata `build/ps2/debug/`, que el original dejó de versionar, como renombrada a `build/ps2/dev/` y mueve allí archivos nuestros.
  - **Tabla de glifos:** `textos_y_tablas.inc.c`, `animaciones_personajes.inc.c` y `elementos_menu.h` quedan enteros como en `main`. El original arregló el mismo fallo con 236 entradas bajo `AVOID_UB` y alias `dato_800E7FF0` y siguientes. La tabla de `main` tiene esas 236 en el mismo orden más las 11 del español. Mezclar los dos lados deja un `#else` sin cerrar o hace que Á…ª lean fuera de la tabla.
  - **Archivos del port** (`mandos.c`, `listas_dibujo.inc.c`, `tarea_graficos.inc.c`, `arranque_ps2.c`, `memory_card.c`): el código del original con los textos en español. En `arranque_ps2.c` se conserva `inicializar_depuracion()` antes del reinicio del IOP; la llamada vieja ya se borra sin conflicto y la nueva solo está dentro del trozo en conflicto.
  - **`README.md`:** queda el de `main`. Lo nuevo del original (multitap, OPL, `FILTRADO_TEXTURAS`, `SMK64_DIAG_CC`, 60 FPS) se integra en un commit de documentación aparte.
  - **`build/` y `compilaciones/`:** quedan como en `main` hasta el commit de publicación, que los regenera desde cero.
  - **Textos nuevos del original** fuera de los conflictos: van en español con tildes en commits propios después de la fusión. Primero se amplía la lista negra de `prueba_textos_port.py` (rojo) y después se traducen (verde). Los grupos del cronómetro nuevos pasan a `GRUPO_CARGA_CEREMONIA` y `GRUPO_CARGA_CREDITOS` en `marcas_registro.h`.
  - El commit de fusión queda en rojo solo en `prueba_textos_port.py` y nunca se sube solo.
- **Archivos:** los 9 en conflicto, más `marcas_registro.h`, `hilos_video_y_audio.inc.c`, `guiones_prueba.c` y `prueba_textos_port.py`.
- **Alternativas descartadas:**
  - Rebase de los 115 commits: reescribe la historia publicada de `main`.
  - Tomar la tabla de 236 del original: pierde los 11 glifos del español.
  - Traducir los textos nuevos dentro del commit de fusión: mezcla la fusión con un cambio funcional.
- **Evidencia requerida:**
  - `git diff M^1 M -- build compilaciones` y el de los 3 archivos de glifos, vacíos;
  - `make test` verde después de la traducción;
  - CI de PS2 verde con `-lmtap`.
- **Lo aplicado:**
  - `git diff 9f4d0215^1 9f4d0215 -- build compilaciones` y el de `textos_y_tablas.inc.c`, `animaciones_personajes.inc.c` y `elementos_menu.h` salen vacíos.
  - La lista negra de `prueba_textos_port.py` se amplió primero (`748db117`, rojo) y los textos se tradujeron después (`36fc9e40`, verde).
  - Dos pruebas nuevas protegen lo que la fusión podía perder sin error de compilación: `prueba_arranque.py` (`inicializar_depuracion()` antes del reinicio del IOP, `664d9013`) y `prueba_tablas_glifos.py` (`lut_textura_glifo` se define una vez, fuera de todo `#if` y sin los alias del original, `e600bd6e`).
  - El comando de R-GOB-01 sobre `origin/main..feature/sincronizacion-upstream` devuelve los dos commits del original que trae la fusión, `c2ed147` y `ae93f71`. Son historia del repositorio original y no se reescriben.
  - CI de PS2 con `-lmtap`: la ejecución de F8 anotada en [trazabilidad.md](trazabilidad.md#evidencia-común).
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: lingüística de `feature/sincronizacion-upstream` aprobada con observaciones; `664d9013` y `e600bd6e` se revisaron con `sinc/sistema` y `sinc/pendientes` ([acta de F8](revisiones/2026-10-11-sincronizacion.md));
  - INTEGRACIÓN: fusión e integración en `feature/sincronizacion-upstream` (2026-10-11).
- **Commit:** `9f4d0215` (fusión), `748db117` (prueba), `36fc9e40` (textos), `409a72b9` (README), `664d9013` (merge `bbb11eb6`) y `e600bd6e` (merge `cf956b42`).

### CC-09: publicación con tipo `build`, Release de GitHub y limpieza de ramas por CI

- **Estado:** aplicado en la CI; la evidencia llega con la publicación
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-GOB-01, R-INF-05
- **Motivo:**
  - El job `publicar` commitea con `chore(build)`, un tipo que R-GOB-01 no admite (4 commits ya registrados en CC-06).
  - El modo DEV no se compila en la CI: los guiones de prueba y los registros DEV solo se descubrían rotos en la publicación.
  - El usuario pide una Release con la ISO y que queden solo las ramas necesarias.
  - Desde la sesión de trabajo, la API de GitHub no permite crear Releases ni borrar ramas (403).
- **Cambio:**
  - El commit de publicación pasa a `build(compilaciones): binarios e ISO en español`, con el commit de origen y la ejecución en el cuerpo.
  - `compilar-ps2` compila también `make DEV=1`.
  - **Job a pedido `release`** (entrada `release=<etiqueta>`): sobre la referencia lanzada, publica la ISO de `compilaciones/` y un `SHA256SUMS` con las notas de `docs/versiones/<etiqueta>.md`, con `GITHUB_TOKEN`.
  - **Job a pedido `limpiar_ramas`** (entrada `limpiar_ramas=si`): borra las ramas remotas que ya están contenidas en `main` (`git merge-base --is-ancestor`). No toca `main` ni ninguna rama con commits propios.
  - `BUILD_ID` pasa a la fecha de la versión.
- **Archivos:** `.github/workflows/compilacion.yml`, `Makefile` (línea de `BUILD_ID`) y `docs/versiones/v1.0.0.md`.
- **Alternativas descartadas:**
  - Crear la Release con la API desde la sesión: 403.
  - Reescribir los 4 commits `chore` ya integrados: la historia es pública.
- **Evidencia requerida:**
  - el commit de publicación con el tipo nuevo;
  - la Release con un SHA-256 igual al de la ISO versionada;
  - `git ls-remote --heads origin` con solo `main` al final.
- **Lo aplicado:**
  - el workflow tiene seis jobs: `pruebas-pc`, `compilar-ps2` (ahora también con `make DEV=1`), `mismo-binario`, `publicar`, `release` y `limpiar-ramas`;
  - `BUILD_ID ?= 2026-10-11` en el `Makefile`;
  - las entradas a pedido aceptan `si` y `sí` (`b69f1548`, de la revisión lingüística);
  - `release` no depende de `publicar`: se lanza en una segunda ejecución, sobre `main`, después de fusionar el commit de publicación, para que suba la ISO nueva (hallazgo Baja del [acta de F8](revisiones/2026-10-11-sincronizacion.md));
  - commit de publicación: en [trazabilidad.md](trazabilidad.md#evidencia-común); Release y SHA-256 de la ISO: en las [notas de la v1.0.0](../versiones/v1.0.0.md); ramas remotas: se comprueban después de la fusión a `main`, con `limpiar-ramas`.
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica y lingüística de `sinc/ci` aprobadas con observaciones;
  - INTEGRACIÓN: integrado con el merge `1ac5c96f`.
- **Commit:** `24ed39a0` (CI), `6251a4a6` (`BUILD_ID`), `b69f1548` (tildes de las entradas) y el merge `1ac5c96f`. Las notas `docs/versiones/v1.0.0.md` llegan con la documentación de F8.

### CC-10: recorrido de PCSX2 con capturas automáticas

- **Estado:** rechazado (responsable del proyecto, 2026-10-11). El proyecto no depende de capturas ni de pasos manuales de nadie: se verifica con las pruebas del PC y la CI. No se integra nada de este cambio y `herramientas/guiones/recorrido_textos.txt` queda como estaba.
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-FUE-07, R-TXT-07, R-MC-03, R-TEX-05, R-PORT-02, R-PORT-03 (los que dependen del recorrido de F6)
- **Motivo:** el recorrido de F6 se hacía a mano: `recorrido_textos.txt` paraba en cada `nota` para sacar la captura con F8. Además no cubría datos y récords, contrarreloj, VS, batalla, ¡REVÉS!, Memory Card, ceremonia ni créditos. Desde `ae93f71`, la orden `captura <nombre>` guarda `host:<nombre>.tga` en las compilaciones DEV.
- **Cambio:**
  - **Guiones:** 5 guiones en `herramientas/guiones/` (menús, gran premio, modos, Memory Card, ceremonia y créditos). Cada uno empieza en el arranque y termina en `fin`. Esperan cada pantalla con `pulsa_hasta`, `comprueba` y `siguiente_estado` en lugar de esperas a ciegas, y sacan una `captura` por pantalla.
  - **`prueba_guiones.py`:** valida los guiones contra las órdenes, variables y botones que lee de `guiones_prueba.c`.
  - **`hoja_capturas.py`:** arma una hoja PNG con las capturas en el orden del guion, marca las que faltan y deja un índice con los `FALLO` del registro.
- **Archivos:** `herramientas/guiones/`, `herramientas/hoja_capturas.py`, `herramientas/hojas_es.py` (refactor sin cambio de conducta), `herramientas/pruebas/` y `Makefile` (líneas de prueba).
- **Alternativas descartadas:** seguir con capturas a mano.
- **Evidencia requerida:**
  - `prueba_guiones.py` y `prueba_hoja_capturas.py` en verde, cada una con una mutación demostrada;
  - el recorrido real lo corre el usuario en PCSX2.
- **Aprobación:** responsable del proyecto: aprobado el 2026-10-11 y rechazado el mismo día (`b4b37c13`). REVISIÓN técnica y lingüística de `sinc/recorrido`: aprobadas con observaciones. INTEGRACIÓN: no se integra.
- **Commit:** ninguno integrado. La rama `sinc/recorrido` (`bb920d50`…`93cae6c0`) queda fuera de `feature/sincronizacion-upstream`; su revisión consta en el [acta de F8](revisiones/2026-10-11-sincronizacion.md).

### CC-11: correcciones con evidencia después de la sincronización

- **Estado:** aplicado, con las dos diferencias que se registran debajo (G5 y L3)
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-FUE-07, R-PORT-01, R-PORT-02, R-INF-05
- **Motivo:** revisión de solo lectura del árbol combinado, en tres frentes: gráficos, audio y estabilidad, y legibilidad del español. Solo entran las correcciones con un caso concreto y una corrección mínima. Lo que no tiene caso visible o no se puede verificar queda documentado.
- **Cambio:**

  | Id | Corrección | Archivos | Verificación |
  |---|---|---|---|
  | E3 | `GRUPOS_MAX` de 4 a 6: con los grupos nuevos de ceremonia y créditos la tabla quedaba llena, y un quinto grupo pisaba el cuarto en silencio | `cronometro_fases.c` | prueba en el PC si el cronómetro compila sin el SDK; si no, evidencia de código |
  | E4 | Lectura de la ROM: 4 intentos de 5 s más 1 s de cancelación (unos 24 s), por debajo de los 30 s del perro guardián, para que se vea «no se pudo leer SMK64ROM.BIN» y no «cuelgue» | `carga_rom.c` | evidencia de código |
  | E5 | Memory Card: con el tiempo vencido, el -1 se tomaba por «tarjeta nueva formateada». Ahora `type`/`format` se inicializan, se exige `mc_ok` y se deja de reintentar con la tarjeta desactivada | `memory_card.c` | evidencia de código |
  | G5 | `G_AC_DITHER`: el alfa negativo se limita a 0 antes de elevarlo al cuadrado | `combinador_y_recorte.inc.c` | `prueba_combinador` |
  | L2 | Si la reserva de matrices está agotada, la letra no se dibuja y su tilde tampoco (antes caía sobre la letra anterior). Registro DEV una vez cuando se agota | `letras_y_fundidos.inc.c`, `cargar_texturas_menu.inc.c` | evidencia de código y registro DEV |
  | L3 | Panel 5x7: una fila libre entre líneas para que las tildes no toquen la línea de arriba (`TEXTO_ALTO_LINEA` 9, textura de 108 filas, 112 KB de VRAM) | `texto_pantalla.h`, `texto_pantalla.c`, `medidor_rendimiento.h` | `prueba_fuente_5x7.c` |

- **No se tocan (documentado):**
  - **G2:** la captura de los guiones (`captura` y `graba`, solo DEV) puede perder un pedido y deja el alfa del `.tga` del último vértice. Ningún flujo del proyecto usa capturas (CC-10 rechazado), así que queda como propuesta para el repositorio original.
  - **G4:** el tramado por primitiva también alcanza a las letras del menú y a los puestos del HUD, que son triángulos y no rectángulos como dice el comentario del original. Corregirlo cambia la imagen y no hay forma de verificarlo sin capturas, así que queda como propuesta para el repositorio original.
  - **G3:** la segunda pasada `m·TEXEL + PRIM` no desplaza el modo REGION_REPEAT. Hoy ningún dibujo lo usa, así que no hay caso visible.
  - **Marcar el atlas una vez por pasada:** es una optimización sin medición.
  - **Audio, multitap, reinicio del IOP, 60 FPS, física y atlas:** sin defecto.
- **Alternativas descartadas:** apagar el tramado en todos los triángulos 2D, porque cambia el degradado de las letras.
- **Evidencia requerida:** la de la tabla. Cada corrección va en su commit `fix`, con la prueba en rojo o la evidencia en el mensaje.
- **Lo aplicado:**

  | Id | Commits | Verificación real |
  |---|---|---|
  | E3 | `176651ed` | `prueba_cronometro_fases.c`: rojo con `GRUPOS_MAX` 4 (5 fallos) y mutación a 5 (3 fallos) |
  | E4 | `a86960cf` | Evidencia de código en el mensaje. Peor caso de unos 24 s, por debajo de los 30 s del perro guardián |
  | E5 | `61a88a74` | Evidencia de código en el mensaje |
  | G5 | `ce98830c` | **Sin prueba en el PC.** La evidencia de código va en el mensaje del commit (alfa de vértice 0x40, PRIM 0xC0 y LOD 0xFF: antes -64 daba 32, ahora 0) |
  | L2 | `9adc3192` | Evidencia de código en el mensaje y registro DEV «menu: reserva de matrices agotada»; la tabla de glifos y el tope quedan cubiertos por `prueba_tablas_glifos.py` (`697f3af6`) |
  | L3 | `4612a508` (prueba), `ac4fcdae` (cambio), `4e4cc6f8` (tildes de la prueba) | `prueba_ancho_panel.py`, no `prueba_fuente_5x7.c`: `texto_pantalla.h` incluye `tamtypes.h` del SDK y no compila en el PC |

- **Diferencia en G5.** La tabla pedía `prueba_combinador`, pero `combinar_color` está en `combinador_y_recorte.inc.c`, que solo compila con el SDK, y el arnés compila solo `combinador_color.c`. Para probarlo hay que mover el promedio a `combinador_color.c`/`.h`, fuera de los archivos del bloque. INTEGRACIÓN integró solo G5, en la rama `sinc/graficos-g5`, con la evidencia del mensaje de `ce98830c`; la prueba queda como deuda ([deuda.md](deuda.md)). Como cambia la verificación aprobada, falta la confirmación del responsable del proyecto.
- **Diferencia en L3.** `MEDIDOR_VRAM_BYTES` queda en 128 KB y no en los 112 KB de la tabla. Motivo, del mensaje de `ac4fcdae`:
  - el GS guarda CT32 en páginas de 64 × 32 píxeles (8 KB); con TBW 4, la textura de 256 × 108 ocupa 16 páginas (las filas 96..107 caen en la cuarta fila de páginas);
  - con 112 KB (14 páginas), las páginas 14 y 15 del panel serían las 0 y 1 del atlas, que empieza justo detrás (`gs_vram_inicio_texturas`);
  - 128 KB son las 16 páginas enteras.

  El mensaje del commit cuantifica el solape con cifras que la revisión corrigió: la subida del panel pisaría las filas 0..11 del atlas en x 0..127 (no las 0..15), y el atlas taparía desde x 128 la línea 11 del panel y las dos últimas filas de letra de la línea 10 (filas 96 y 97). La conclusión no cambia. Solo afecta a las compilaciones con panel (`MEDIDOR=1`).
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11); G2 y G4 retirados de la tabla el mismo día (`b4b37c13`);
  - REVISIÓN: `sinc/pendientes` y `sinc/panel`, aprobadas con observaciones después de las correcciones; `sinc/sistema`, con cambios requeridos por los trailers de cuatro mensajes, que se reescribieron antes de integrar; `sinc/graficos`, con cambios requeridos por G5 (ver el [acta de F8](revisiones/2026-10-11-sincronizacion.md));
  - INTEGRACIÓN: merges `368a5416` (G5), `bbb11eb6` (E3, E4 y E5), `cf956b42` (L2) y `240358fd` (L3). Pendiente: la confirmación del responsable para G5.
- **Commit:** los de «Lo aplicado».

### CC-12: verificación sin pasos manuales y manual del proyecto

- **Estado:** aplicado en la documentación de F8
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-FUE-07, R-TXT-07, R-MC-03, R-TEX-05, R-PORT-02, R-PORT-03, R-GOB-04, R-GOB-08
- **Motivo:**
  - El responsable del proyecto decide que nadie corre recorridos ni manda capturas: la versión se publica para la comunidad con lo que verifican las pruebas del PC y la CI.
  - Los documentos repartían el uso, la parte técnica y el proceso entre el README y `docs/traduccion/`. No había créditos ni autoría, ni notas de versión, ni acta de revisión, ni una única Definition of Done.
- **Cambio:**
  - **Se retira F6** (recorrido en PCSX2 y captura en TV). Los requisitos que dependían de él se aceptan con lo que comprueban `make test` y la CI.
  - **«Sin verificación visual registrada»** se declara como limitación en el manual de usuario y en las notas de versión, en lugar de darlo por cubierto.
  - **Documentación en dos niveles:** el README es la portada y resume y enlaza. `docs/manual/` tiene el manual de usuario, el técnico y los créditos.
  - **Créditos y autoría:**
    - el port a PS2 es de anthoo582;
    - la base es la descompilación de Mario Kart 64;
    - la localización al español, la sincronización con el original y las mejoras de este repositorio son de Alexis Barrera.
  - **Proceso:**
    - `CONTRIBUTING.md` es la única fuente de la Definition of Done, las reglas que no se negocian, la lectura previa y el orden de autoridad (código y pruebas medidos, después la especificación aprobada, después los documentos);
    - `CHANGELOG.md` registra los cambios por versión y `docs/versiones/v1.0.0.md` es el cuerpo de la Release;
    - `docs/traduccion/revisiones/` guarda el acta de revisión de cada PR;
    - `docs/traduccion/deuda.md` separa la deuda técnica de lo pendiente del plan.
- **Archivos:** `README.md`, `CONTRIBUTING.md`, `CHANGELOG.md`, `docs/manual/`, `docs/versiones/`, `docs/traduccion/` (README, plan, especificacion, trazabilidad, revisiones/ y deuda).
- **Alternativas descartadas:**
  - una cabecera repetida en cada documento;
  - un comprobador automático de la documentación;
  - una línea base de avisos de la compilación de PS2;
  - proteger `main` (el job `publicar` hace push a la rama donde corre);
  - contar commits por autor en los créditos (el primer commit del port original trae el port entero).
- **Evidencia requerida:**
  - ningún documento pide pasos manuales al usuario;
  - los créditos están en el README;
  - `docs/versiones/v1.0.0.md` existe antes de lanzar el job `release`.
- **Aprobación:** responsable del proyecto: aprobado (2026-10-11). REVISIÓN e INTEGRACIÓN: con la revisión de las ramas de documentación de F8.
- **Commit:** `b4b37c13` (CC-10 rechazado y G2 y G4 retirados) y `d5f95cc5` (este registro). La aplicación va en las ramas de documentación de F8: `sinc/manual`, `sinc/proceso` y `sinc/doc-traduccion`.

### CC-13: Memory Card sin pérdida de partidas al cambiar la tarjeta

- **Estado:** aprobado (responsable del proyecto, 2026-10-11, plan F9)
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-MC-01, R-MC-02
- **Motivo:**
  - Si se arranca sin tarjeta o se cambia en caliente, `guardar_ahora` escribe en `ranura_siguiente` con la generación de la sesión sin leer la tarjeta. Pisa la copia más nueva y en el siguiente arranque se carga la vieja (`memory_card.c:241-243` y `:302-323`).
  - Hay tres defectos más:
    - la espera de la partida al arrancar cuenta 5000 vueltas y no tiempo, contra un perro guardián de 6 s (`:281-283`);
    - el segundo borrado espera aunque la tarjeta no conteste (D-12);
    - `mcGetInfo` puede escribir `type`/`free`/`format` en una pila ya liberada si contesta tarde (D-13).
- **Cambio:**
  - **Tarjeta nueva:** cuando `mcGetInfo` devuelve -1, se leen las dos cabeceras antes de escribir. Se pisa la copia más vieja y la generación pasa a ser la mayor de la tarjeta más uno. Lo decide una función pura en `incluir/sistema/eleccion_guardado.h`, probada en el PC. No se toca `guardado_ps2.generacion`: el hilo de juego la usa para espaciar los guardados.
  - **Espera al arrancar:** se mide con `ciclos_ps2()`, no en vueltas del bucle.
  - **Segundo borrado** (D-12): solo con `mc_ok`.
  - **Variables de `mcGetInfo`** (D-13): `type`, `free` y `format` pasan a `static`.
  - **D-11, decisión escrita:** se mantiene. Si solo vence `mcClose`, la tarjeta queda desactivada y descartar la lectura es coherente: la partida de la sesión sigue en la memoria.
- **Alternativas descartadas:** no escribir nunca en una tarjeta distinta de la del arranque, porque perdería el guardado al insertar una tarjeta vacía.
- **Evidencia requerida:**
  - `prueba_eleccion_guardado.c` (rojo y mutaciones);
  - para el resto, evidencia de código y compilación en la CI.
- **Aprobación:** responsable del proyecto: aprobado (2026-10-11). INTEGRACIÓN —. REVISIÓN —.
- **Commit:** —
