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

- **Estado:** aplicado
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-MC-01, R-MC-02
- **Motivo:**
  - Si se arranca sin tarjeta o se cambia en caliente, `guardar_ahora` escribe en `ranura_siguiente` con la generación de la sesión sin leer la tarjeta. Pisa la copia más nueva y en el siguiente arranque se carga la vieja (`memory_card.c:241-243` y `:302-323`).
  - Hay tres defectos más:
    - la espera de la partida al arrancar cuenta 5000 vueltas y no tiempo, contra un perro guardián de 6 s (`:281-283`);
    - el segundo borrado espera aunque la tarjeta no conteste (D-12);
    - `mcGetInfo` puede escribir `type`/`free`/`format` en una pila ya liberada si contesta tarde (D-13).
- **Cambio:**
  - **Tarjeta nueva:** cuando `mcGetInfo` devuelve -1, se leen las dos cabeceras antes de escribir. Se pisa la copia más vieja y la generación pasa a ser la mayor de la tarjeta más uno. Lo decide una función pura en `incluir/sistema/eleccion_guardado.h`, probada en el PC. No se toca `guardado_ps2.generacion`: el hilo de guardado la usa para espaciar los guardados.
  - **Espera al arrancar:** se mide con `ciclos_ps2()`, no en vueltas del bucle.
  - **Segundo borrado** (D-12): solo con `mc_ok`.
  - **Variables de `mcGetInfo`** (D-13): `type`, `free` y `format` pasan a `static`.
  - **D-11, decisión escrita:** se mantiene. Si solo vence `mcClose`, la tarjeta queda desactivada y descartar la lectura es coherente: la partida de la sesión sigue en la memoria.
- **Alternativas descartadas:** no escribir nunca en una tarjeta distinta de la del arranque, porque perdería el guardado al insertar una tarjeta vacía.
- **Evidencia requerida:**
  - `prueba_eleccion_guardado.c` (rojo y mutaciones);
  - para el resto, evidencia de código y compilación en la CI.
- **Lo aplicado:**
  - `prueba_eleccion_guardado.c`: rojo sin la cabecera (no compila) y, con cuerpos vacíos, 14 fallos de 20; mutaciones de la comparación (6 fallos) y del +1 de la generación mínima (10 fallos), restauradas.
  - El resto de `memory_card.c` solo compila con el SDK: evidencia de código en los mensajes y `gcc -fsyntax-only` con cabeceras simuladas; lo que queda sin arnés de PC está en [deuda.md](deuda.md) (D-16).
  - Hallazgo Media de la revisión: `releer_tarjeta_nueva` lee la cabecera B solo si la tarjeta sigue contestando (`8c69e253`).
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica de `v110/memoria`, aprobada con observaciones y aprobada en la 2.ª pasada; lingüística, aprobada con observaciones ([acta de F9](revisiones/2026-10-11-version-1.1.0.md#2-v110memoria-memory-card-cc-13));
  - INTEGRACIÓN: merge `4465f614` (2026-10-11).
- **Commit:** `2e578b4b` (prueba), `b989feca` (función pura), `e4937a28` (tarjeta nueva), `41441ae5` (espera con el reloj), `3e62e63e` (D-12), `abe7c205` (D-13), `8c69e253` (cabecera B) y el merge `4465f614`. Texto del registro ajustado a la revisión en `f09697ca`.

### CC-14: zona muerta del stick de 24 a 8

- **Estado:** aplicado
- **Fecha:** 2026-10-11
- **Requisitos afectados:** ninguno de la traducción; cambia el control del port (`codigo/entrada/mandos.c`).
- **Motivo:** el port descarta 24 de 127 unidades del stick y estira el resto a ±80 (`mandos.c:31-48`). El juego aplica después su propia zona muerta de 12 (`mandos_carrera.inc.c:76-95`). Juntas, el kart empieza a girar con 41 de 127 (un 32 % del recorrido); en la N64 era alrededor del 15 %.
- **Cambio:**
  - `ZONA_MUERTA_PALANCA` pasa a 8 y el giro empieza con 28 de 127 (22 %).
  - El juego conserva su zona muerta, que absorbe la deriva de un stick gastado.
  - `convertir_eje` pasa a una función pura en `incluir/entrada/eje_palanca.h`, probada en el PC.
  - La cruceta hace de stick mientras el izquierdo está en reposo. El reposo usa su propio umbral, `ZONA_REPOSO_CRUCETA` (26: hasta 25 del centro, donde antes la salida del stick era 0), para que una deriva de 10 a 25 unidades no la anule (hallazgo de la revisión, `eje_en_reposo`).
- **Alternativas descartadas:**
  - quitar la zona muerta del port, porque dejaría solo la del juego frente a la deriva de los mandos de PS2;
  - hacerla configurable, por sobreingeniería.
- **Evidencia requerida:**
  - `prueba_eje_palanca.c`: el giro empieza a ≤ 28, centro 0, extremos ±80, simetría y monotonía, con rojo y mutaciones;
  - el tacto en una consola real no se verifica (D-06).
- **Lo aplicado:**
  - `prueba_eje_palanca.c`: rojo con la zona muerta en 24 («el giro empieza a 41 del centro, se esperaba como mucho 28»); mutaciones de la zona muerta y del divisor (127 → 128), restauradas.
  - Reposo de la cruceta: rojo «'ZONA_REPOSO_CRUCETA' undeclared» (`ddbdc023`); mutación con `ZONA_MUERTA_PALANCA` en `eje_en_reposo`, 16 fallos (`34ab306d`); umbral de 24 a 26 (`2b37f61f`). Verde: «prueba_eje_palanca: 417 comprobaciones, 0 fallos» en `make test` sobre `a29bd920` (el mensaje de `2b37f61f` dice 415: con el umbral en 26 el bucle de reposo suma dos comprobaciones).
  - La condición de `convertir()` en `mandos.c:64` solo compila con el SDK: revisada a mano y sin prueba ([deuda.md](deuda.md), D-18).
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica de `v110/entrada`, aprobada con observaciones en las dos pasadas; el efecto sobre la cruceta se resolvió con su propio umbral y el arreglo se revisó aparte, aprobado con observaciones; lingüística, aprobada con observaciones ([acta de F9](revisiones/2026-10-11-version-1.1.0.md#5-v110entrada-zona-muerta-del-stick-y-reposo-de-la-cruceta-cc-14));
  - INTEGRACIÓN: merge `4563d816` (2026-10-11).
- **Commit:** `1fc4c437` (refactor), `4a48ff6a` (prueba), `dcbe656e` (zona muerta), `ddbdc023`, `34ab306d` y `2b37f61f` (reposo de la cruceta) y el merge `4563d816`. Registro ajustado en `f09697ca` y `6519d73e`.

### CC-15: región PAL/NTSC detectada y documentada

- **Estado:** aplicado
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-PORT-02
- **Motivo:**
  - El GS se fuerza a NTSC a 60 Hz también en consolas PAL (`sintetizador_gs.c:248`). Por eso el juego, que avanza una vez por retrazo, va a la velocidad correcta.
  - Un jugador con una consola PAL no tiene cómo saber que necesita una TV que acepte 60 Hz.
- **Cambio:**
  - Una función pura en `incluir/sistema/region_ps2.h` interpreta la región de `rom0:ROMVER`.
  - Al arrancar se registra la región. En una consola PAL avisa de que la imagen es NTSC a 60 Hz.
  - El manual de usuario lo explica. El modo de vídeo no cambia.
- **Alternativas descartadas:**
  - un modo PAL a 50 Hz, con el juego un 17 % más lento y cortes de audio;
  - la salida 480p, que cambia la imagen y no se puede verificar.
- **Evidencia requerida:** `prueba_region_ps2.c` con los valores de ROMVER y uno inválido, con rojo y mutación.
- **Lo aplicado:**
  - `region_de_romver()` es `static inline` en `incluir/sistema/region_ps2.h`; solo la «E» da PAL.
  - `registrar_region_consola()` (`arranque_ps2.c`) lee `rom0:ROMVER` justo después del reinicio o la preparación del IOP y registra «consola PAL: la imagen sale en NTSC a 60 Hz; hace falta una TV que acepte 60 Hz», «consola NTSC» o «región de la consola desconocida».
  - `prueba_region_ps2.c`: rojo sin la cabecera (no compila) y mutación de la «A» a PAL, 1 fallo de 16, restaurada.
  - La lectura en consola real, por las dos rutas del IOP, no se ha verificado ([deuda.md](deuda.md), D-17). La explicación para el jugador va en el manual de usuario, con la documentación de F9.
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica de `v110/region`, aprobada con observaciones en las dos pasadas; lingüística, aprobada con observaciones ([acta de F9](revisiones/2026-10-11-version-1.1.0.md#3-v110region-región-de-la-consola-cc-15));
  - INTEGRACIÓN: merge `d105a89b` (2026-10-11); la prueba entra en `make test` con `a29bd920`.
- **Commit:** `807d2c45` (prueba), `3b11daa5` (función pura), `ac1a1090` (registro al arrancar) y el merge `d105a89b`.

### CC-16: publicación comprobada y ELF monolítico en la Release

- **Estado:** aplicado en la CI; la evidencia llega con la Release `v1.1.0`. Amplía CC-09.
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-INF-05
- **Motivo:**
  - `publicar` oculta un fallo real del commit con `|| echo "sin cambios"`.
  - `release` no comprueba que el SHA-256 de la ISO coincida con el de las notas.
  - Para jugar desde USB con uLaunchELF hace falta el ELF de `make MONOLITICO=1`, y nadie lo publica.
- **Cambio:**
  - **`publicar`:** solo omite el commit si `git diff --cached --quiet`.
  - **`release`:** corre en el contenedor de ps2dev y falla si el SHA-256 de la ISO no está en las notas. Compila `make MONOLITICO=1` en la referencia publicada y adjunta ese ELF con su suma. El ELF no se versiona en `compilaciones/`.
- **Alternativas descartadas:** versionar el ELF monolítico en el repositorio, que agrega un archivo grande en cada versión.
- **Evidencia requerida:** la Release `v1.1.0` con la ISO, el ELF monolítico y `SHA256SUMS`, todo comprobado.
- **Lo aplicado:**
  - `publicar` omite el commit solo si `git diff --cached --quiet`; cualquier otro fallo detiene el job.
  - `release` corre en el mismo contenedor de ps2dev que `compilar-ps2`, falla si el SHA-256 de la ISO no está en `docs/versiones/<etiqueta>.md`, compila `make clean` y `make MONOLITICO=1` y publica la ISO, `SLUS_999.99.monolitico.elf` y un `SHA256SUMS` con las dos líneas.
  - Comprobado en el PC con los bloques `run:` del workflow: `publicar` sale con 1 ante un commit que falla (antes, con 0); `release` sale con 1 con unas notas sin la suma. `make MONOLITICO=1` y `gh release create` solo se ejecutan en la CI.
  - Release `v1.1.0`: ejecución, tamaño y SHA-256 de la ISO y del ELF monolítico en [trazabilidad.md](trazabilidad.md#evidencia-común).
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica de `v110/ci-textos`, aprobada con observaciones en las dos pasadas; lingüística, con cambios requeridos, resuelto en `b780d986` ([acta de F9](revisiones/2026-10-11-version-1.1.0.md#4-v110ci-textos-publicación-y-deudas-chicas-cc-16));
  - INTEGRACIÓN: merge `12579275` (2026-10-11).
- **Commit:** `c641d19b` (tildes del workflow), `4bdd41a8` (publicación comprobada y ELF monolítico) y el merge `12579275`.

### CC-17: prueba del alfa con tramado en el combinador

- **Estado:** aplicado. Salda D-01 y D-02.
- **Fecha:** 2026-10-11
- **Requisitos afectados:** ninguno de la traducción; amplía el bloque de gráficos de CC-11 (G5).
- **Motivo:** G5 (`ce98830c`) se integró con evidencia de código, porque el cálculo está en `combinador_y_recorte.inc.c`, que solo compila con el SDK.
- **Cambio:**
  - Commit `refactor`, sin cambio de conducta: el alfa con tramado pasa a la función pura `combinador_alfa_tramado()`, `static inline` en `combinador_color.h`, y la usan las dos ramas de `combinar_color`.
  - Commit `test`: casos en `prueba_combinador.c`.
- **Evidencia requerida:** -64 da 0, 64 da 32 y 128 da 128, con rojo por mutación (quitar el límite) y restauración.
- **Lo aplicado:**
  - `refactor`: arnés de equivalencia fuera del repositorio entre la expresión anterior y `combinador_alfa_tramado()`, de -300 a 300 en pasos de 2^-10: 0 diferencias en 614 401 valores. `combinador_color.c` no cambia.
  - `test`: 4 casos nuevos en `prueba_combinador.c` (-64 → 0, 0 → 0, 64 → 32 y 128 → 128); 22 comprobaciones, 0 fallos. Mutación sin el límite a 0: «tramado(-64)=32.000000», 1 fallo, restaurada.
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica y lingüística de `v110/graficos`, aprobadas con observaciones ([acta de F9](revisiones/2026-10-11-version-1.1.0.md#1-v110graficos-alfa-con-tramado-cc-17));
  - INTEGRACIÓN: merge `9289608a` (2026-10-11).
- **Commit:** `ff313bc5` (refactor), `d41996f7` (prueba) y el merge `9289608a`.

### CC-18: archivo de opciones del port en la Memory Card

- **Estado:** aplicado
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-MC-04 (nuevo)
- **Motivo:** los ajustes de imagen y los trucos de CC-19 a CC-25 tienen que sobrevivir al apagado sin tocar la partida guardada. La imagen de guardado (`guardado_ps2.h`) no tiene espacio libre y exige la versión exacta: cambiarla invalidaría las partidas existentes.
- **Cambio:**
  - Archivo aparte `SMK64CFG.DAT` en `/BASLUS-99999SMK64/`: 32 bytes con la magia `MKCF`, versión, tamaño, los campos, bytes reservados y CRC32.
  - La lógica pura (valores por defecto, serializar, validar y sanear) va en una cabecera `static inline` con su prueba. El CRC32 se comparte con `memory_card.c`.
  - Se lee y se escribe solo desde el hilo de guardado, porque libmc no admite varios hilos. Se escribe al salir del menú de CC-19 y solo si algo cambió.
  - Si falta el archivo o está dañado, se usan los valores por defecto y el juego sigue.
- **Alternativas descartadas:** ampliar la imagen de guardado, porque obliga a migrar las partidas.
- **Evidencia requerida:** prueba del PC con ida y vuelta, magia, versión y CRC erróneos, valores fuera de rango, el CRC32 de «123456789» igual a 0xCBF43926 y mutaciones restauradas.
- **Lo aplicado:**
  - `d6bf7381` (refactor) lleva el CRC32 a una cabecera compartida con `memory_card.c`.
  - `a760841b` (prueba) y `93cb4d04` (contrato): `incluir/sistema/opciones_port.h` define `OpcionesPort`, los valores por defecto según la configuración de la PS2, el saneado y el formato de 32 bytes. Rojo: no compilaba sin la cabecera.
  - `098af916` (prueba) y `8c022b34`: el hilo de guardado lee y escribe `SMK64CFG.DAT`; `prueba_memory_card.c`, con la libmc simulada de D-16, da 83 comprobaciones y 0 fallos. Rojo: no compilaba sin `ARCHIVO_OPCIONES`.
  - `3bbac652` (integración): los campos quedan escritos antes de que el retrazo vea la versión nueva de las opciones (hallazgo Baja de `v120/imagen`).
  - Sin Memory Card, las opciones duran hasta apagar la consola. El cambio de tarjeta en caliente no se ha probado en hardware ([especificación §9](especificacion.md#9-límites-declarados)).
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: el contrato se revisó con `v120/memoria`; técnica, aprobada con observaciones; lingüística, aprobada ([acta de F10](revisiones/2026-10-11-version-1.2.0.md#2-v120memoria-archivo-de-opciones-y-memory-card-cc-18-cc-27));
  - INTEGRACIÓN: merges `226a3ce3` (`v120/contrato`) y `48e951fc` (`v120/memoria`) (2026-10-11).
- **Commit:** `d6bf7381`, `a760841b`, `93cb4d04`, `098af916`, `8c022b34`, `3bbac652` y los merges `226a3ce3` y `48e951fc`.

### CC-19: menú «CONFIGURACIÓN Y TRUCOS»

- **Estado:** aplicado
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-VID-05 (nuevo), R-TXT-04, R-TXT-05
- **Motivo:** el jugador necesita cambiar los ajustes de imagen y los trucos sin combinaciones de botones ocultas. El responsable del proyecto eligió una entrada de menú con el mismo estilo que los menús del juego y aprobó la maqueta.
- **Cambio:**
  - Quinta entrada «CONFIGURACIÓN Y TRUCOS» al final de OPCIONES. Se añade al final para no cambiar la numeración que usan los guiones. El paso entre filas baja para que la quinta quede dentro de la zona segura.
  - Subpantalla con 9 filas:
    - ANTIPARPADEO, POSICIÓN X, POSICIÓN Y, FORMATO;
    - DESBLOQUEAR TODO, OBJETO, 200CC, RIVALES SIN VENTAJA;
    - VOLVER.
  - Estilo del juego:
    - fuente del texto del menú, caja negra translúcida y cursor giratorio;
    - arcoíris en la fila elegida y el valor en verde;
    - el valor va alineado a la derecha en x=0x11C, no detrás del nombre como en la maqueta, para que los valores largos no pisen la caja; las 9 filas van de y=0x58 a y=0xD8;
    - los sonidos de OPCIONES.
  - Controles:
    - arriba/abajo mueven la fila y se paran en los extremos;
    - izquierda/derecha cambian el valor, y X lo avanza;
    - Círculo o VOLVER salen.
  - La fuente no tiene «:» ni «/», así que no se escribe «16:9».
  - La navegación y el ciclo de valores van en una función pura con su prueba. Los textos nuevos entran en las pruebas de textos y de lugares.
- **Alternativas descartadas:** combinaciones de botones con L3, porque son ocultas, y texturas nuevas, porque el estilo ya existe en el juego.
- **Evidencia requerida:** pruebas de navegación y de textos (rojo, mutación, verde), compilación de PS2 en la CI y la pasada del emulador de CC-26 por el menú.
- **Lo aplicado:**
  - `7abb1f92` (prueba) y `7c5439e4`: `incluir/menus/menu_configuracion.h` con la navegación, el ciclo de valores y el objeto de 0 a 15 sin el 13; `prueba_menu_configuracion.c`, 55 comprobaciones y 0 fallos. Rojo: no compilaba sin la cabecera. Mutación del salto del 13, repetida en la corrección: 5 fallos, restaurada.
  - `b8954cee` (prueba) y `146b23af`: quinta fila de OPCIONES y subpantalla, con sus textos en las pruebas de textos y de lugares (glifos, texto esperado, zona segura y sin solape entre etiqueta y valor).
  - `91c7254e` (integración): DESBLOQUEAR TODO se aplica al reconstruir cada pantalla de menú (CC-22).
  - La CI recorre el menú en el emulador y compara su captura con la referencia (CC-26).
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11), con la maqueta;
  - REVISIÓN: técnica de `v120/menu`, aprobada con observaciones; lingüística, aprobada ([acta de F10](revisiones/2026-10-11-version-1.2.0.md#4-v120menu-menú-configuración-y-trucos-cc-19));
  - INTEGRACIÓN: merge `8a62d5a1` (2026-10-11).
- **Commit:** `7abb1f92`, `7c5439e4`, `b8954cee`, `146b23af`, `be1248ff` (alineación del valor), `91c7254e` y el merge `8a62d5a1`.

### CC-20: antiparpadeo y posición de la imagen en 480i

- **Estado:** aplicado
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-VID-01, R-VID-02 (nuevos), R-PORT-02
- **Motivo:**
  - En 480i las líneas finas (textos, marcador) tiemblan en una TV de tubo.
  - Algunas TV cortan los bordes de la imagen.
  - El port nunca escribe PMODE ni DISPLAY: se quedan los valores de gsKit.
- **Cambio:**
  - **Solo la presentación:** CC-15 y la decisión de no usar 480p se mantienen; el modo sigue siendo NTSC 480i a 60 Hz.
  - **Antiparpadeo:**
    - PMODE con los dos circuitos de lectura, CRTMD=1, MMOD=1 y ALP=0x80 (0x8027);
    - DISPFB2 con DBY=1 (bit 43);
    - mezcla al 50 % dos líneas vecinas.
  - **Posición:** DX en VCK (MAGH+1 por píxel) y DY siempre par, en DISPLAY1 y DISPLAY2 por igual, con límites.
  - Los registros se calculan con una función pura y se escriben en el retrazo cuando cambian las opciones; en pánico no se tocan.
  - Con los valores por defecto (antiparpadeo NO, posición 0,0) los registros son los de la 1.1.0. La prueba lo fija.
- **Alternativas descartadas:**
  - antiparpadeo activado por defecto, porque ablanda la imagen en emuladores y TV modernas y no hay verificación en hardware;
  - 480p, por la misma razón que en CC-15.
- **Evidencia requerida:** prueba de los valores de registro (por defecto 0x8046 y el DISPLAY de gsKit; antiparpadeo 0x8027 y DBY en el bit 43; DY par) con mutaciones, y el registro del arranque en el emulador.
- **Lo aplicado:**
  - `deeba019` (prueba) y `fa835b62`: `incluir/graficos/registros_video.h` calcula PMODE, DISPFB2 y DISPLAY. Por defecto, 0x8046 y el DISPLAY de gsKit; con antiparpadeo, 0x8027 y DBY en el bit 43; DY siempre par. Rojo: no compilaba sin la cabecera.
  - `9173dde8`: `sintetizador_gs.c` escribe los registros en el retrazo cuando cambian las opciones; `2093202d` ajusta el texto del registro de vídeo.
  - `979fcf14` (integración): el job del emulador exige en el registro «vídeo: PMODE 8046», el valor por defecto.
  - El efecto en una TV no se ha visto: las capturas leen la VRAM antes del PCRTC ([especificación §9](especificacion.md#9-límites-declarados)).
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica de `v120/imagen`, aprobada con observaciones; lingüística, aprobada ([acta de F10](revisiones/2026-10-11-version-1.2.0.md#3-v120imagen-antiparpadeo-posición-y-formato-cc-20-cc-21));
  - INTEGRACIÓN: merge `9b206935` (2026-10-11).
- **Commit:** `deeba019`, `fa835b62`, `9173dde8`, `2093202d`, `979fcf14` y el merge `9b206935`.

### CC-21: formato 4:3, con bandas o panorámico según la configuración de la PS2

- **Estado:** aplicado
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-VID-03, R-VID-04 (nuevos)
- **Motivo:**
  - Con la PS2 configurada en 16:9, la TV estira la imagen 4:3.
  - El responsable del proyecto pidió dos modos: proporción correcta, que es el de fábrica en 16:9, y vista ancha opcional.
- **Cambio:**
  - **Configuración de la PS2:** se lee con `configGetTvScreenType()`. Solo `TV_SCREEN_169` es 16:9; `TV_SCREEN_FULL` sigue siendo 4:3.
  - **FORMATO:** NORMAL, CON BANDAS o PANORÁMICO. Si no hay archivo de opciones, vale CON BANDAS con la PS2 en 16:9 y NORMAL en otro caso.
  - **CON BANDAS:** se hace en el PCRTC, con MAGH=2, DW=1920 y DX desplazado. La imagen ocupa 3/4 del ancho y el fondo negro rellena los lados. El dibujo del juego no cambia ni pierde resolución.
  - **PANORÁMICO (Hor+):**
    - `aspecto_pantalla` ×4/3 en las asignaciones de la carrera, la vista dividida y la ceremonia, no en `guPerspectiveF`, para que los menús no cambien;
    - el cono de `es_visible_objeto_en_camara` se ensancha en la misma proporción;
    - el marcador sale estirado.
- **Alternativas descartadas:**
  - escalar las X en el intérprete F3DEX, que toca vértices, rectángulos y recorte;
  - aplicar el aspecto dentro de `guPerspectiveF`, que también ensancha los menús.
- **Riesgo:** los tramos de pista se eligen por cuadrante de cámara, así que puede faltar pista en los bordes en PANORÁMICO. Se comprueba con el emulador; si aparece, el valor PANORÁMICO se retira antes de publicar.
- **Evidencia requerida:** pruebas puras del aspecto (1,333 → 1,778; 0,667 → 0,889; 2,667 → 3,556), del cono con tope y de los registros con bandas, con mutaciones, más las capturas del emulador.
- **Lo aplicado:**
  - CON BANDAS sale de `registros_video.h` (MAGH=2, DW=1920, DX centrado). La revisión encontró que con bases de MAGH 0 o 1 el cálculo pasaba por debajo de cero: rojo en `d8ebb3ac` (4 fallos de 66), arreglado en `d5ee5381`.
  - `064830d8` (prueba) y `92c1f1f3`: `incluir/graficos/vista_panoramica.h` con el aspecto (1,333 → 1,778; 0,667 → 0,889; 2,667 → 3,556) y el cono ensanchado 4/3 con tope. Rojo: no compilaba sin la cabecera.
  - `fd4286e3`, `c52e2f8d` y `761d735d` aplican el aspecto en la vista de cada pantalla, al cambiar de pantalla en la carrera y en la ceremonia.
  - El valor PANORÁMICO se mantiene. En los bordes pueden aparecer tarde objetos o tramos de pista, el marcador sale estirado y el rendimiento no se ha medido en hardware ([especificación §9](especificacion.md#9-límites-declarados)).
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica de `v120/imagen`, aprobada con observaciones; lingüística, aprobada ([acta de F10](revisiones/2026-10-11-version-1.2.0.md#3-v120imagen-antiparpadeo-posición-y-formato-cc-20-cc-21));
  - INTEGRACIÓN: merge `9b206935` (2026-10-11).
- **Commit:** `d8ebb3ac`, `d5ee5381`, `064830d8`, `92c1f1f3`, `fd4286e3`, `c52e2f8d`, `761d735d` y el merge `9b206935`.

### CC-22: truco DESBLOQUEAR TODO

- **Estado:** aplicado
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-TRU-01 (nuevo)
- **Motivo:** el responsable del proyecto pidió los trucos de CC-22 a CC-25, apagados de fábrica.
- **Cambio:**
  - La consulta del modo EXTRA (`tiene_modo_extra_desbloqueado`, `guardado.c`) y la de los fantasmas del staff (`repeticiones.c`) aceptan el truco mediante funciones puras.
  - Nunca se escribe el desbloqueo en la partida.
  - El valor del truco se aplica al volver al título o al reconstruir el menú, no en caliente.
  - El cursor se recorta si EXTRA deja de existir.
- **Límite declarado:** los trofeos EXTRA ganados con el truco se guardan y quedan ocultos si se apaga.
- **Evidencia requerida:** prueba pura con rojo y mutaciones (`&&` en lugar de `||`, `<` en lugar de `<=`).
- **Lo aplicado:**
  - `9d310c2c` (prueba) y `be355571`: `incluir/juego/trucos.h`. La consulta del modo EXTRA y la de los fantasmas del staff leen una copia que solo cambia en `truco_desbloquear_aplicar()`, que también recorta el cursor de cilindrada. Rojo: no compilaba sin la cabecera.
  - La revisión vio que nadie llamaba a `truco_desbloquear_aplicar()` (Media). Se resolvió en la integración con `91c7254e`: se llama al reconstruir cada pantalla de menú, así que el truco se aplica al cambiar de pantalla.
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica de `v120/trucos`, aprobada con observaciones; lingüística, aprobada ([acta de F10](revisiones/2026-10-11-version-1.2.0.md#5-v120trucos-los-cuatro-trucos-cc-22-a-cc-25));
  - INTEGRACIÓN: merge `159c4396` (2026-10-11).
- **Commit:** `9d310c2c`, `be355571`, `91c7254e` y el merge `159c4396`.

### CC-23: truco OBJETO

- **Estado:** aplicado
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-TRU-02 (nuevo)
- **Motivo:** como CC-22.
- **Cambio:**
  - **Dónde:** en el sorteo de la caja para jugadores humanos (`funcion_8007AFB0`), después de la ruleta, el resultado se sustituye por el objeto elegido.
  - **Qué no cambia:** el generador aleatorio avanza igual, y la CPU y el Boo no cambian.
  - **Cuándo no se sustituye:** en batalla solo se usan los objetos válidos en batalla. En contrarreloj, en otros modos o con un valor inválido, sale el objeto normal.
- **Evidencia requerida:** prueba pura con los casos de GP, batalla, contrarreloj e inválidos, y mutaciones.
- **Lo aplicado:**
  - `4efcf0be` (prueba) y `5a19ff97`: `incluir/carrera/truco_objeto.h` y el enganche en `funcion_8007AFB0`, con casos de Gran Premio, Versus, batalla, contrarreloj e inválidos. Rojo: no compilaba sin la cabecera.
  - Un objeto que no vale en batalla da la ruleta normal, sin aviso; el menú no filtra por modo.
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica de `v120/trucos`, aprobada con observaciones; lingüística, aprobada ([acta de F10](revisiones/2026-10-11-version-1.2.0.md#5-v120trucos-los-cuatro-trucos-cc-22-a-cc-25));
  - INTEGRACIÓN: merge `159c4396` (2026-10-11).
- **Commit:** `4efcf0be`, `5a19ff97` y el merge `159c4396`.

### CC-24: truco 200CC

- **Estado:** aplicado
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-TRU-03 (nuevo)
- **Motivo:** como CC-22.
- **Cambio:**
  - **Modificador de 150cc,** no una cilindrada nueva: un valor 4 chocaría con `BATALLA_CC` y leería fuera de las tablas de la CPU.
  - **Factor ×35/32** en la rapidez máxima y en el empuje de humanos y CPU al aparecer, y en el objetivo de velocidad de la CPU.
  - **Dónde aplica:** solo en Gran Premio y Versus a 150cc. No aplica en contrarreloj ni en batalla, porque los fantasmas se desincronizarían.
- **Límites declarados:**
  - puntúa en la casilla de 150cc;
  - la pausa dice 150cc;
  - un cambio en mitad de la carrera se aplica en la siguiente.
- **Evidencia requerida:**
  - prueba pura que valide la fórmula contra las tablas originales;
  - peor caso de velocidad por paso por debajo de 8,8, con margen para las pendientes;
  - la mutación 37/32 tiene que fallar.
- **Riesgo:** curvas más difíciles y la CPU fuera de su camino. Se comprueba con el emulador.
- **Lo aplicado:**
  - `038c39c0` (prueba) y `c80fe61e`: `incluir/carrera/cilindrada_200cc.h`, con la fórmula del empuje contra las tablas originales, el factor 35/32, el peor caso por debajo de 8,8 y los modos en que aplica. Rojo: no compilaba sin la cabecera.
  - `a6397211` (revisión, Baja) quita la escritura del empuje que `aparecer_jugador()` pisaba después.
  - Solo aplica en Gran Premio y Versus a 150cc, y puntúa como 150cc.
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica de `v120/trucos`, aprobada con observaciones; lingüística, aprobada ([acta de F10](revisiones/2026-10-11-version-1.2.0.md#5-v120trucos-los-cuatro-trucos-cc-22-a-cc-25));
  - INTEGRACIÓN: merge `159c4396` (2026-10-11).
- **Commit:** `038c39c0`, `c80fe61e`, `a6397211` y el merge `159c4396`.

### CC-25: truco RIVALES SIN VENTAJA

- **Estado:** aplicado
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-TRU-04 (nuevo)
- **Motivo:** como CC-22.
- **Cambio:**
  - **El impulso que se anula:** en el control de velocidad de la CPU (`control_velocidad_cpu.inc.c`) desaparece el que la CPU recibe al ir por detrás del jugador. Con el truco, la CPU acelera solo hasta el objetivo de su tabla.
  - **La velocidad fija sustituida:** la velocidad fija de recuperación de `caminos_y_vehiculos.inc.c` se reemplaza por ese mismo objetivo base.
  - **Lo que no cambia:** las órdenes de velocidad de cada pista quedan intactas.
- **Límite declarado:** solo tiene efecto en el Gran Premio.
- **Evidencia requerida:** prueba pura con rojo y mutaciones.
- **Lo aplicado:**
  - `0e75a425` (prueba) y `f46bc633`: `incluir/carrera/rivales_sin_ventaja.h` y los dos enganches del control de velocidad. Rojo: no compilaba sin la cabecera.
  - `4c0323bf` (revisión, Baja): el rival designado conserva su control de velocidad, como dice el cambio.
  - El efecto en el juego no se puede medir con una prueba, porque la CPU no es determinista.
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica de `v120/trucos`, aprobada con observaciones; lingüística, aprobada ([acta de F10](revisiones/2026-10-11-version-1.2.0.md#5-v120trucos-los-cuatro-trucos-cc-22-a-cc-25));
  - INTEGRACIÓN: merge `159c4396` (2026-10-11).
- **Commit:** `0e75a425`, `f46bc633`, `4c0323bf` y el merge `159c4396`.

### CC-26: verificación en un emulador dentro de la CI

- **Estado:** aplicado. Matiza CC-12: sigue sin pedirse nada al usuario; la CI arranca el juego sola.
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-INF-05, R-INF-07 (nuevo)
- **Motivo:** D-06 y D-17 no se podían saldar sin ver el juego arrancar. Play! arranca un ELF sin BIOS (`--elf`) y monta `host:`, `rom0:` y la Memory Card como carpetas.
- **Cambio:**
  - **Job `emulador`:**
    - Play! con versión y SHA-256 fijados, bajo Xvfb y renderizado por software;
    - arranca el ELF de DEV con un guion de `host:`;
    - lo detiene al terminar el guion o al vencer el tiempo.
  - **Qué comprueba:**
    - el registro de arranque y la línea de región con un ROMVER sintético;
    - los valores de los registros de vídeo;
    - las capturas del menú y de la carrera comparadas con referencias aprobadas, con tolerancia.
  - **Criterios para continuar** (todos):
    - hay registro y no hay pánico;
    - el guion termina sin fallos;
    - las capturas no son uniformes;
    - dos ejecuciones dan capturas dentro de la tolerancia;
    - el job dura menos de 30 minutos.
  - **Si algún criterio falla:** CC-26 pasa a rechazado con la URL de la ejecución. D-06 y D-17 pasan a límites declarados.
- **Límite:** las capturas leen la VRAM antes del PCRTC, así que el antiparpadeo, las bandas y la posición se comprueban por los valores de registro.
- **Evidencia requerida:** la ejecución del job en verde, o su rechazo documentado.
- **Lo aplicado:**
  - `7491fd24` (prueba) y `98a042b7`: comparación de las capturas TGA con sus referencias y entre ejecuciones, con rechazo de la imagen uniforme.
  - `a7bae5d4` (prueba) y `570a0a12`: revisión del registro (sin pánico ni cuelgue, con la línea de región del ROMVER sintético) y del fin del guion.
  - `2c3a8b29`: job «Guion en el emulador (Play!)», que arranca dos veces el ELF de DEV en Play! 0.72 sin BIOS. `979fcf14` exige además «vídeo: PMODE 8046». Las referencias de título, menú y carrera están en `herramientas/emulador/referencias/`.
  - Ejecución en verde: [38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616), con todos los criterios para continuar cumplidos.
  - D-06 y D-17 se saldan en lo que la CI comprueba. El tacto, la imagen en una TV y la lectura de ROMVER sin reiniciar el IOP quedan como límites declarados ([especificación §9](especificacion.md#9-límites-declarados)).
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica de `v120/ci-emulador`, aprobada con observaciones; el hallazgo Media de la ejecución pendiente se cierra con [38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616); lingüística, aprobada ([acta de F10](revisiones/2026-10-11-version-1.2.0.md#9-v120ci-emulador-emulador-y-ci-cc-26-cc-27));
  - INTEGRACIÓN: merge `10f290a3` (2026-10-11).
- **Commit:** `7491fd24`, `98a042b7`, `a7bae5d4`, `570a0a12`, `2c3a8b29`, `979fcf14` y el merge `10f290a3`.

### CC-27: cierre de la deuda técnica

- **Estado:** aplicado. Queda D-23 en [deuda.md](deuda.md); lo que no se puede comprobar sin hardware pasa a límites declarados.
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-TEX-02, R-TEX-03, R-TEX-08, R-PORT-03, R-FUE-09 (nuevo), R-MC-01, R-MC-02
- **Motivo:** el responsable del proyecto pidió no dejar deuda. Lo que no se puede saldar sin hardware pasa a límite declarado.
- **Cambio:**

  | Deuda | Cómo se cierra |
  |---|---|
  | D-03 | Tope de crecimiento de la ROM en la CI |
  | D-04 | Compilación incremental real en la CI |
  | D-05 | Filas de carpeta en el manifiesto de texturas |
  | D-07 | Pantalla de fallo con tildes mediante `scr_putchar`, si la inspección de la fuente de libdebug lo confirma |
  | D-08 | Tope de `efecto_mtx` en los seis sitios |
  | D-16 | Arnés del PC con libmc simulada |
  | D-18 | Función pura de la cruceta |
  | D-19 | Caso de largo 13 |
  | D-20 | El registro da la generación escrita |
  | D-21 | La cabecera B se lee solo con `mc_ok`; además, `leer_archivo_mc` y `escribir_archivo_mc` no envían ninguna orden con `mc_ok` a 0, de modo que una tarjeta que no contesta no recibe más órdenes en toda la sesión |
  | D-22 | Erratas y «1 fallo» en singular |
  | D-06 y D-17 | Mediante CC-26 |

- **Evidencia requerida:** cada cierre con su prueba en rojo y la mutación restaurada, o con la ejecución de la CI. `deuda.md` queda sin filas, o solo con límites declarados.
- **Lo aplicado:** cada deuda con sus commits está en [trazabilidad.md § Deuda saldada en F10](trazabilidad.md#deuda-saldada-en-f10). En resumen:
  - **CI** (`v120/ci-emulador`): tope de la ROM (`99fa9b5c`, `a27fd80f`; D-03), build incremental real (`04adf1f6`; D-04) e inspección de la fuente de libdebug (`f48b7a41`, `68bc6dce`; D-07).
  - **Código** (`v120/deudas`): pantalla de fallo con tildes mediante `scr_putchar` (`b06d4cbe`, `8e311363`, `278f45a5`, `ab75b9aa`; D-07), tope de `efecto_mtx` en los seis sitios (`e16f26d8`, `93231a07`, `64805e8c`, `a989c0f5`, `d2ce4c18`, `0f75b754`, `dc6d4730`; D-08), cruceta en una función pura (`e0f76493`, `bd70c399`, `3d67d29d`; D-18), largo 13 (`0c962092`; D-19) y erratas (`00b25b9d`, `9a92bc41`; D-22).
  - **Memory Card** (`v120/memoria`): arnés con libmc simulada (`36796171`; D-16), generación escrita en el registro (`c94152e0`, `c69d9ef4`; D-20), ninguna orden después de una vencida (`289e9c78`, `2c83c0f8`; D-21) y errata (`b38d42c4`; D-22).
  - **Manifiesto** (`v120/manifiesto`): filas de carpeta (`fee9830b`, `22fbc484`, `9032ab75`, `7638072f`; D-05), completado con CC-29.
  - La revisión de `v120/deudas` dejó D-23, la partícula dibujada con la matriz anterior (`3a30f145`).
  - `3cf36394` (integración) pone en `make test` las pruebas nuevas de la versión.
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica de `v120/deudas`, con cambios requeridos (Alta: la prueba de la reserva no estaba en `make test`), resuelto en `0f75b754` y `dc6d4730`, y aprobada con observaciones; técnica de `v120/memoria`, `v120/manifiesto` y `v120/ci-emulador`, aprobadas con observaciones; lingüística, aprobada o aprobada con observaciones ([acta de F10](revisiones/2026-10-11-version-1.2.0.md#6-v120deudas-deuda-técnica-cc-27));
  - INTEGRACIÓN: merges `48e951fc`, `6e6a2108`, `c3e1d30e` y `10f290a3` (2026-10-11).
- **Commit:** los de [trazabilidad.md § Deuda saldada en F10](trazabilidad.md#deuda-saldada-en-f10), `3cf36394` y los merges `48e951fc`, `6e6a2108`, `c3e1d30e` y `10f290a3`.

### CC-28: reconstrucción de texturas del HUD y de los menús

- **Estado:** aplicado
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-TEX-04, R-TEX-05
- **Motivo:** la auditoría de las 58 texturas en español encontró estos defectos (todas se generan con `compositor_es.py`):
  - **Puestos 1.º…8.º:** el «º» parece un signo de grados. Es un anillo hueco a media altura y no está inclinado como las cifras.
  - **VUELTA:** toca la última columna sin contorno, así que la A se ve cortada.
  - **Botones de menú y de modo a dos líneas, y nombres de copa:** usan la letra pequeña sin contorno sobre una placa, distinta del estilo del juego.
  - **Título de la Jungla DK:** más apretado que el resto de los títulos.
- **Cambio:**
  - **Puestos:** el «º» pasa a ser volado, relleno e inclinado, a la altura de la cifra.
  - **VUELTA:** margen de contorno en el borde derecho.
  - **Letra pequeña:** contorno oscuro de 1 px y separación entre las líneas, de forma igual en todos los botones de dos líneas.
  - **Título de la Jungla DK:** el título se ajusta sin juntar letras.
  - Todo se regenera con el compositor; nada se retoca a mano.
- **Alternativas descartadas:**
  - un texto más natural en Lakitu, porque pide una fuente nueva;
  - acortar nombres sin necesidad.
- **Evidencia requerida:**
  - una prueba nueva del contorno en el borde de las texturas del HUD (en rojo con VUELTA);
  - `prueba_composicion_es.py` igual al compositor;
  - las pruebas de textura en verde;
  - la hoja de contacto, revisada por un revisor distinto del autor.
- **Lo aplicado:**
  - `3b5e4aef` (prueba): el borde de las palabras del HUD solo lleva contorno, en rojo con VUELTA; `d7b3feb9` lo corrige.
  - `2175d03b` («º» de los puestos), `9d9ac85e` (letra pequeña con contorno y sin placa) y `bace922a` (título de la Jungla DK), todo regenerado con `compositor_es.py`. En la revisión, `prueba_composicion_es.py` da 856 comprobaciones y 0 fallos.
  - Mutación de la revisión: con el PNG anterior de VUELTA, `prueba_hud_es.py` falla.
  - Los binarios de `build/ps2/es` se regeneran en el commit de publicación (`9ab41422`), como fija R-GOB-05.
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica de `v120/texturas`, aprobada con observaciones, con la hoja de contacto revisada por un revisor distinto del autor ([acta de F10](revisiones/2026-10-11-version-1.2.0.md#8-v120texturas-reconstrucción-del-hud-y-de-los-menús-cc-28));
  - INTEGRACIÓN: merge `b7b03ee3` (2026-10-11).
- **Commit:** `3b5e4aef`, `d7b3feb9`, `2175d03b`, `9d9ac85e`, `bace922a` y el merge `b7b03ee3`.

### CC-29: clasificación de las texturas sin revisar

- **Estado:** aplicado
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-TEX-02
- **Motivo:** tras las filas de carpeta de D-05 quedan unas 1200 texturas sin clasificar en 10 rutas (`PENDIENTES` en `prueba_texturas_es.py`). Entre ellas hay carteles de pista con texto en inglés.
- **Cambio:**
  - Se mira cada textura y se le da una de estas salidas:
    - **sin texto:** fila de carpeta o de textura;
    - **logotipo o cartel comercial** (marcas, patrocinadores, nombres propios): se conserva por §2.2 y su fila lleva el motivo;
    - **no se muestra en el port:** fila con su evidencia;
    - **texto general visible:** se traduce con el compositor.
  - Una textura suelta que las órdenes no leen (rgba32, ia1, ci8) se excluye con una fila de archivo, `archivo:<ruta>`, distinta de la fila de carpeta de D-05. `prueba_texturas_es.py` exige que `carpeta:` apunte a una carpeta y `archivo:` a un archivo (R-TEX-02).
  - Cada clasificación con texto la revisa un refutador.
  - Al terminar, `PENDIENTES` queda vacía.
  - «pendiente:» no es un motivo para conservar texto. Las 15 texturas con texto general visible que aún no se pueden traducir (WELCOME, GO, RAILROAD CROSSING y 1P a 4P) llevan `motivo_no` «pendiente: …», cuentan en `TEXTURAS_PENDIENTES` de `prueba_texturas_es.py`, que solo puede bajar, y quedan como deuda ([D-24](deuda.md)). CC-29 no se cierra hasta que se traduzcan o un CC decida conservarlas. En F10 se tradujeron las 15.
- **Evidencia requerida:**
  - `prueba_texturas_es.py` en verde con `PENDIENTES` vacía y `TEXTURAS_PENDIENTES` a 0;
  - las traducciones con su prueba y su hoja de contacto;
  - la revisión de un agente distinto del autor.
- **Lo aplicado:**
  - `a6fa679e` (prueba) y `4216877e`: las texturas sin revisar quedan clasificadas en `recursos/es/texturas.tsv` y `PENDIENTES` queda vacía. En total, el manifiesto clasifica 1229 texturas.
  - `431c3186` separa las filas `archivo:` de las `carpeta:` (hallazgo Media) y `df9aea49` cuenta las pendientes en `TEXTURAS_PENDIENTES` y registra D-24 (hallazgo Alta).
  - Traducidas con el compositor y con su prueba: YA en Mario Raceway (`bb31482f`, `3505ff26`), BIENVENIDOS en dos mitades (`fe010d2a`, `cb32c871`), los emblemas 1J a 4J en ci8 con su paleta (`bc4516de`, `caf7756f`) y PASO A NIVEL en diagonal en las 8 señales de cruce (`f7866dd3`, `625105f4`).
  - `TEXTURAS_PENDIENTES` queda en 0 y D-24 se salda.
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica de `v120/texturas-pistas`, con cambios requeridos, resuelto en `431c3186` y `df9aea49`; las cuatro ramas de texturas traducidas, aprobadas con observaciones después de repetir las mutaciones ([acta de F10](revisiones/2026-10-11-version-1.2.0.md#10-v120texturas-pistas-clasificación-de-las-texturas-sin-revisar-cc-29) y [§11](revisiones/2026-10-11-version-1.2.0.md#11-texturas-traducidas-v120tx-bienvenida-v120tx-ya-v120tx-emblemas-y-v120tx-cruce-cc-29));
  - INTEGRACIÓN: merges `616213c8`, `3017fe10`, `a087fc2a`, `56401560` y `fd6a4bb7` (2026-10-11).
- **Commit:** `0f15c448` (registro), `a6fa679e`, `4216877e`, `431c3186`, `df9aea49`, `bb31482f`, `3505ff26`, `fe010d2a`, `cb32c871`, `bc4516de`, `caf7756f`, `f7866dd3`, `625105f4` y los merges `616213c8`, `3017fe10`, `a087fc2a`, `56401560` y `fd6a4bb7`.

### CC-30: portafolio: aviso legal reforzado, autoría, caso de estudio, página web y licencia MIT de los aportes

- **Estado:** aprobado
- **Fecha:** 2026-10-11
- **Requisitos afectados:** ninguno de la traducción; toca la documentación pública del proyecto (R-GOB-08).
- **Motivo:** el proyecto se publica sin fines de lucro, con fines educativos, de preservación y de apoyo a la comunidad, y distribuye la ISO y el ELF como el repositorio original (`anthoo582/mario-kart-64-ps2`). Hace falta dejar claro quién hizo qué, con qué fin y en qué condiciones, con el crédito a anthoo582 y al proyecto de descompilación de mk64.
- **Cambio:**
  - **Aviso legal reforzado:** los derechos del juego son de Nintendo; el proyecto no tiene fines de lucro y no está afiliado a Nintendo.
  - **Autoría:** Alexis Barrera, desarrollador e ingeniero de observabilidad, autor de la localización, la sincronización y las versiones 1.1.0 y 1.2.0, con los créditos al port y a la descompilación.
  - **Caso de estudio:** el motivo (Mario Kart 64 es el juego de su infancia y quería mejorarlo, traducirlo y jugarlo en su PS2 aprovechando la descompilación), cómo se trabajó y qué se aprendió.
  - **Página web** del proyecto con ese contenido.
  - **Licencia MIT** solo para los aportes propios; no cambia las condiciones del código de origen ni cubre los recursos del juego.
- **Alternativas descartadas:** una licencia para todo el repositorio, porque el código de origen y los recursos del juego tienen sus propias condiciones.
- **Evidencia requerida:** revisión técnica y lingüística de la documentación, y comprobar que ninguna página nombra un empleador ni una institución.
- **Aprobación:** responsable del proyecto: aprobado (2026-10-11).
- **Commit:** —

### CC-31: capturas de referencia al día y comparación estricta

- **Estado:** aplicado
- **Fecha:** 2026-10-11
- **Requisitos afectados:** R-INF-07
- **Motivo:**
  - Las referencias del emulador son anteriores a CC-28: el menú muestra la placa negra vieja.
  - `comparar_capturas.py` admite hasta un 2 % de píxeles distintos, así que un cambio de textura pequeño pasa sin aviso.
  - Las dos ejecuciones de la CI dan un 0 % de diferencia entre sí.
- **Cambio:**
  - La tolerancia por defecto pasa de 0,02 a 0,001.
  - Las referencias se regeneran con el ELF de DEV actual y se revisan a ojo.
  - El guion captura también el menú CONFIGURACIÓN Y TRUCOS, si la navegación es determinista.
  - Las imágenes de la página del proyecto (`docs/img/`) se actualizan.
- **Evidencia requerida:**
  - una prueba en rojo con un bloque de 32×16 cambiado (0,18 %) frente a la tolerancia vieja;
  - el job del emulador en verde con la tolerancia nueva;
  - la revisión visual de las referencias.
- **Lo aplicado:**
  - `1bac15d9` (prueba): un bloque de 32×16 cambiado en 640×448 (0,18 %) debe fallar con la tolerancia por defecto; en rojo con 0,02. `632050ac` baja la tolerancia por defecto de `comparar_capturas.py` a 0,001 (0,1 %).
  - `a7ab8019`: `guion_ci.txt` captura también `configuracion`, el menú CONFIGURACIÓN Y TRUCOS. Dos ejecuciones dan un 0,0000 % de diferencia entre sí.
  - `3a022b42`: referencias regeneradas con Play! 0.72 y el ELF de DEV actual, revisadas a ojo; `f4b86834` pone al día `docs/img/` con la figura del menú de configuración.
  - `17901393`: entrada `regenerar_referencias` del workflow. Con `sí`, el job `emulador` escribe las capturas de la primera ejecución como referencias, comprueba la segunda contra ellas, copia `menu`, `carrera` y `configuracion` a `docs/img/` y commitea en la rama. Las referencias se revisan a ojo antes de integrar. Regeneradas así en las ejecuciones [38179540046](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38179540046) (`6933dd08`) y [38180265814](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38180265814) (`863cbc45`).
  - Mirar las capturas con la comparación estricta encontró dos defectos visibles del juego:
    - los valores de CONFIGURACIÓN Y TRUCOS se dibujaban tenues: primero en verde semitransparente (`a5464408` los pasa a `CONFIG_COLOR_VALOR`, amarillo) y después en el modo de texto alineado a la derecha, que también es tenue (`39bb214b` en rojo, `42a13caf` los dibuja en el modo opaco de las etiquetas con `config_columna_valor()`);
    - el ordinal de los puestos se leía «8º.»: `9ec3b950` (prueba en `prueba_hud_es.py`) y `33979fbf` ponen el punto en la base antes de la «º» volada, «8.º».
- **Aprobación:**
  - responsable del proyecto: aprobado (2026-10-11);
  - REVISIÓN: técnica de `v121/capturas` y de `v121/ordinal`, aprobadas con observaciones después de corregir los hallazgos ([acta de la 1.2.1](revisiones/2026-10-11-version-1.2.1.md));
  - INTEGRACIÓN: merge `73aff9e2` (`v121/ordinal`) en `feature/capturas-1.2.1` (2026-10-11).
- **Commit:** `8d94ba8d` (registro), `1bac15d9`, `632050ac`, `a7ab8019`, `3a022b42`, `f4b86834`, `a5464408`, `9ec3b950`, `33979fbf`, `17901393`, `6933dd08`, `39bb214b`, `42a13caf`, `863cbc45` y el merge `73aff9e2`.

### CC-32: portada pública del proyecto: página, README y propósito sin lucro

- **Estado:** aprobado
- **Fecha:** 2026-10-13
- **Requisitos afectados:** R-DOC-01 (nuevo)
- **Motivo:**
  - La página `docs/index.html` enlaza `caso-de-estudio.html` y `manual/usuario.html`, que son archivos `.md` sin cabecera YAML: Jekyll, el valor por defecto de GitHub Pages, no los convierte y darían 404.
  - El README y la página no dicen con claridad que es un aporte sin ánimo de lucro, con motivación personal, publicado para la comunidad.
- **Cambio:**
  - Estilo de artículo técnico en página y README: resumen, secciones numeradas, tablas con reglas, figuras con pie y notas al pie. La página lleva además un resumen en inglés.
  - Paleta C elegida por el responsable: azul tinta con una línea fina roja bajo el título; modo claro y oscuro.
  - Enlaces del caso de estudio y del manual absolutos a GitHub.
  - Propósito sin lucro, aviso legal y autoría con las mismas palabras en README, página y notas de versión.
  - Prueba del PC que exige que todo enlace relativo de la página y del README apunte a un archivo que existe y que ningún enlace de la página termine en `.md` sin pasar por GitHub.
- **Alternativas descartadas:** un workflow de despliegue de Pages (basta la rama `main` y la carpeta `/docs`) y un archivo `.nojekyll`.
- **Evidencia requerida:** la prueba en rojo con los enlaces actuales, en verde tras el cambio, y una mutación que la rompe; la URL pública de Pages respondiendo.
- **Aprobación:** responsable del proyecto: aprobado, con la paleta C (2026-10-13).
- **Commit:** —

### CC-33: el audio se comprueba en la CI y el tono con 200cc en el PC

- **Estado:** aprobado
- **Fecha:** 2026-10-13
- **Requisitos afectados:** R-INF-07
- **Motivo:** el job del emulador no mira el audio: si `audsrv` dejara de iniciar, el job pasaría con el juego mudo. Además, nadie ha comprobado que el tono del motor siga en rango con el truco 200cc.
- **Cambio:**
  - `comprobar_registro.py` exige `audio: audsrv listo` y rechaza los avisos de módulos del IOP, de `audsrv_init` y de `audsrv_set_format`.
  - Prueba del PC del tono del motor con 150cc y 200cc; el código del juego solo se toca si da fuera de rango.
  - `SMK64_NO_IOP_RESET` documentado en el manual técnico.
- **Evidencia requerida:** prueba en rojo con un registro sin la línea de audio; el job del emulador en verde con el registro real.
- **Aprobación:** responsable del proyecto: aprobado (2026-10-13).
- **Commit:** —

### CC-34: marcador de la carrera en PANORÁMICO sin estirar

- **Estado:** aprobado
- **Fecha:** 2026-10-13
- **Requisitos afectados:** R-VID-04
- **Motivo:** en el formato PANORÁMICO el 3D se amplía con Hor+ pero la TV estira el marcador. Es el defecto visible más grande que queda declarado (especificación §9).
- **Cambio:**
  - El HUD de la carrera se estrecha a 3/4 en X alrededor del centro de su cuadrante, solo con el formato PANORÁMICO.
  - Los menús, los fundidos a pantalla completa y los demás formatos no cambian.
  - La transformación es una función pura `static inline` con su prueba.
- **Alternativas descartadas:** estrechar también los menús y los fundidos.
- **Evidencia requerida:** prueba pura con mutación y captura del emulador, revisada a ojo, con el marcador sin estirar.
- **Aprobación:** responsable del proyecto: aprobado (2026-10-13). Si la revisión visual falla, se descarta sin publicar.
- **Commit:** —

### CC-35: matriz de tramado propia y medición del medio texel

- **Estado:** aprobado
- **Fecha:** 2026-10-13
- **Requisitos afectados:** R-VID-06 (nuevo)
- **Motivo:**
  - La matriz de tramado se toma de los valores por defecto de gsKit, que según una lectura de su código pueden dejar una de las 16 celdas en 0 en lugar de −2. El repositorio nunca escribe `DIMX`.
  - El desplazamiento de medio texel del filtrado no tiene prueba.
- **Cambio:**
  - Se escribe `DIMX` propio en el arranque de cada paquete de dibujo, calculado por una función pura con su prueba. Antes se confirma con el gsKit real de la imagen fijada.
  - Guion DEV con un tablero de texels que mide el desplazamiento; si es correcto queda como prueba, y si no, se corrige la constante.
- **Evidencia requerida:** prueba pura de `DIMX` con mutación y la medición del tablero en el emulador.
- **Aprobación:** responsable del proyecto: aprobado (2026-10-13).
- **Commit:** —
