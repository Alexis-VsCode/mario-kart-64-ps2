# Registro de cambios de la especificación

Aquí se registra todo cambio de requisito, límite, escala, paso de interlineado, término o texto de reserva, y toda diferencia entre lo ejecutado y el plan aprobado. El registro se hace **antes** de tocar el código. Las diferencias ya ejecutadas se registran en cuanto se detectan.

## Reglas

- Cada cambio tiene un identificador `CC-NN` que no se reutiliza.
- **Estados:** `propuesto`, `aprobado`, `rechazado` o `aplicado`.
- **Aprobación:**
  - la dan INTEGRACIÓN y REVISIÓN;
  - si el cambio toca una decisión cerrada de la especificación o el plan aprobado, también el responsable del proyecto.
- **Evidencia:** un cambio de maquetación se justifica con medidas y con una captura antes/después (PCSX2 y, si afecta a los bordes, TV).
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

- **Estado:** propuesto
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
- **Evidencia requerida:** captura antes/después de la selección de pista en contrarreloj.
- **Aprobación:** INTEGRACIÓN — / REVISIÓN —
- **Commit:** —

### CC-02: interlineado de los mensajes de varias líneas

- **Estado:** propuesto
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
- **Aprobación:** INTEGRACIÓN — / REVISIÓN —
- **Commit:** —

### CC-03: ampliación del HUD

- **Estado:** propuesto
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
- **Aprobación:** INTEGRACIÓN — / REVISIÓN — / responsable del proyecto —
- **Commit:** —

### CC-04: `modo_mario_gp` sin traducir en el manifiesto

- **Estado:** propuesto
- **Fecha:** 2026-09-28
- **Requisitos afectados:** R-TEX-02, R-TEX-04
- **Motivo:** el plan aprobado traduce `modo_mario_gp` a GRAN PREMIO y solo admite conservar «MARIO GP» si no pasa la prueba de ajuste. El manifiesto de `4345598` ya lo marca con `motivo_no` «nombre del modo», sin prueba de ajuste registrada.
- **Cambio propuesto:** hacer la prueba de ajuste de «GRAN PREMIO» en la textura de 64 × 18. Si pasa, la fila pierde el motivo y lleva `texto_es`. Si no pasa, se conserva «MARIO GP» con la medida como evidencia.
- **Archivos y líneas:** `recursos/es/texturas.tsv`, fila `modo_mario_gp`.
- **Alternativas descartadas:** abreviar a «G. PREMIO» sin registrar la medida.
- **Evidencia requerida:** medida del texto compuesto y hoja antes/después.
- **Aprobación:** INTEGRACIÓN — / REVISIÓN — / responsable del proyecto —
- **Commit:** —

### CC-05: valor de la marca de pánico del registro

- **Estado:** propuesto
- **Fecha:** 2026-09-28
- **Requisitos afectados:** R-PORT-04
- **Motivo:** el registro vuelca al PC en el momento las líneas que contienen «PANIC» (`codigo/depuracion/depuracion.c:99`). El trabajo en curso de PORT define `MARCA_PANICO` como «PANICO», así que la línea de pánico se escribe en español. Cambiar el valor de una marca es un cambio de especificación.
- **Cambio propuesto:** `MARCA_PANICO` vale «PANICO». Productor y consumidor usan la macro, así que el volcado no cambia de comportamiento.
- **Archivos y líneas:** `incluir/depuracion/marcas_registro.h` (nuevo) y `codigo/depuracion/depuracion.c:99-100, 401`.
- **Alternativas descartadas:** conservar «PANIC», porque deja una palabra en inglés en el registro.
- **Evidencia requerida:** `prueba_textos_port.py` en verde y una línea de pánico en el registro de `make DEBUG=1`.
- **Aprobación:** INTEGRACIÓN — / REVISIÓN —
- **Commit:** —

### CC-06: diferencias entre lo ejecutado y el plan aprobado

- **Estado:** aplicado; falta la ratificación en la aprobación de F0
- **Fecha:** 2026-09-28
- **Requisitos afectados:** R-INF-01, R-INF-02, R-INF-05, R-FUE-01, R-FUE-07, R-FUE-08, R-TEX-03, R-GOB-01, R-GOB-02, R-GOB-03
- **Motivo:** lo publicado en F1–F4 se apartó del plan en estos puntos. La especificación ya describe lo ejecutado.

| Plan aprobado | Lo ejecutado | Commit |
|---|---|---|
| Las subramas nacen de `feature/idioma-espanol` | `idioma/infra` nace de `main`; `idioma/fuente` e `idioma/texturas`, de `idioma/infra`; `idioma/cadenas` e `idioma/port`, de `idioma/fuente`. Se integran en `feature/idioma-espanol` en el orden infra → fuente → texturas → cadenas → port | — |
| Solo `test`, `clean` y `es` sin SDK | `OBJETIVOS_PC := test clean herramientas`; `es` y `hoja-es` se añaden cuando existan | `f8f9a39` |
| El conversor lleva una lista blanca de caracteres sacada de la lista de glifos | Sin lista blanca: la prueba de textos valida los caracteres con el decodificador real. ’ y ” tienen glifo; … y “ no | `727c7ed` |
| CI en `.github/workflows/ps2.yml` | CI en `.github/workflows/compilacion.yml`, con el job `mismo-binario` añadido | `7387d01`, `a3d0bae` |
| Puerta de F2: `nm -n -S` idéntico | `comparar_preprocesado.py` en el PC, `mismo-binario` en la CI y, para `d87d14f`, prueba de caracterización | `cb36bbc`, `a3d0bae` |
| `textos_menu.inc.c` en F2, dentro de FUENTE | Lo hace CADENAS al empezar F4 | En curso |
| F3 empieza por el tope del pool | Orden real: LUT, lista X-macro, caracteres, regla de avance, glifos, pool, glifos en la ROM y cadenas con tildes | `4e35120`…`641fe27` |
| `ASSERT_ESTATICO(… == GLIFOS_TOTAL)` | El `ASSERT_ESTATICO` compara la cuenta de las dos tablas; `prueba_tablas_glifos.py` fija el total de 247 | `4e35120`, `1c9545d` |
| Diacrítico con `case 26` de alto 8 en `cargar_texturas_menu.inc.c` | `imprimir_letra` dibuja la segunda parte con `dibujar_diacritico_glifo` y `vtx_glifo_diacritico` | `5718601` |
| Glifos con vista previa PNG (`--vista-previa`) | Los glifos se escriben en `$(BUILD)/glifos_es/`, no se versionan, y `--ver` los muestra en texto | `9abb8d7` |
| Todas las texturas traducidas en MIO0 con `TAMANIO_ES_*` | PULSA START es RGBA16 crudo de 159 × 16 y sigue así | — |
| Un commit por bloque de traducción | Par de commits (prueba y cambio) o uno solo con los dos, con el rojo demostrado | — |
| Formato `tipo(dominio): descripción` sin excepciones | Se aceptan también `ci: descripción` y los mensajes de merge `Merge branch '…'` | `7387d01`, `6dd12e7`, `a3d0bae`, `236962b` |
| Quitar `iconv` de los requisitos del README | `iconv` ya no hace falta para compilar. Solo lo usa, si está instalado, `prueba_convertir_eucjp.py` para comparar. Los requisitos del README se actualizan en F7, al integrar | Pendiente (F7) |

- **Alternativas descartadas:** rehacer las ramas según el plan. Se descarta porque lo publicado tiene CI en verde y la topología real respeta las dependencias entre roles.
- **Evidencia requerida:** la de [trazabilidad.md](trazabilidad.md).
- **Aprobación:** INTEGRACIÓN — / REVISIÓN — / responsable del proyecto —
- **Commit:** los de la tabla.
