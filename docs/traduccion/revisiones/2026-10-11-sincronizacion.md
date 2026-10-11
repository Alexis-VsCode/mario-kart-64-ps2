# Acta de revisión: sincronización con el original (F8)

- **Fecha:** 2026-10-11
- **Rama de integración:** `feature/sincronizacion-upstream`, que nace de `main` (`3f43c005`) y trae el original hasta `ae93f71` con la fusión `9f4d0215`.
- **Cambios que cubre:** [CC-08 a CC-12](../cambios.md).
- **Roles:** cada rama la escribió un autor y la revisaron REVISIÓN técnica y REVISIÓN lingüística, nunca el autor. Solo INTEGRACIÓN integró, con `git merge --no-ff`.
- **Formato de los hallazgos:** el de [plan.md §7](../plan.md#7-revisión). Cada hallazgo indica además cómo quedó: resuelto (con su commit), aceptado (con su motivo) o abierto (con su entrada en [deuda.md](../deuda.md)).

## Resumen

Todas las subramas salieron de `36fc9e40`, el commit que deja en español los textos nuevos del original.

| Rama | Revisión técnica | Revisión lingüística | Decisión |
|---|---|---|---|
| `sinc/ci` | Aprobada con observaciones | Aprobada con observaciones | Integrada (`1ac5c96f`) |
| `sinc/graficos` | Cambios requeridos (1.ª y 2.ª pasada) | Aprobada con observaciones | Solo G5, como `sinc/graficos-g5` (`368a5416`) |
| `sinc/sistema` | Cambios requeridos (1.ª y 2.ª pasada) | Aprobada con observaciones | Integrada (`bbb11eb6`) después de reescribir los mensajes |
| `sinc/pendientes` | Cambios requeridos; aprobada con observaciones en la 2.ª pasada | Aprobada con observaciones | Integrada (`cf956b42`) |
| `sinc/panel` | Aprobada con observaciones (dos pasadas) | Aprobada con observaciones | Integrada (`240358fd`) |
| `sinc/recorrido` | Aprobada con observaciones | Aprobada con observaciones | No se integra: CC-10 rechazado |

En todas las ramas, el diff de dos puntos contra `feature/sincronizacion-upstream` mostraba también `README.md`. No era un cambio de las ramas: la base avanzó con `409a72b9` después de que salieran. El alcance se comprobó con el diff de tres puntos.

**Hashes revisados e integrados.** Dos ramas se integraron con hashes distintos de los que vio REVISIÓN:

- `sinc/sistema` se rehízo para quitar los trailers de cuatro mensajes, con los mismos árboles: `feafb878` → `664d9013`, `98a33c68` → `176651ed`, `21005b69` → `a86960cf`, `63c6ab06` → `61a88a74` y `ab9c784b` → `372f10ed`.
- `sinc/graficos-g5` lleva solo `ce98830c`, que tiene el mismo parche que `fb6a81c0` (`git patch-id` igual).

## 1. `sinc/ci`: CI, Release y limpieza de ramas (CC-09)

**Commits:** `24ed39a0` (`ci: compilar DEV, publicar con tipo build, Release y limpieza de ramas`), `6251a4a6` (`build(make): BUILD_ID con la fecha de la versión 1.0.0`) y, de la revisión lingüística, `b69f1548` (`ci: tildes en las entradas a pedido y aceptar «sí» con tilde`).

**Comprobaciones de REVISIÓN técnica:**

- Autor y committer Alexis Barrera, sin firma ni trailers ni menciones a herramientas; el comando de R-GOB-01 sale vacío.
- El diff de tres puntos solo toca `.github/workflows/compilacion.yml` y la línea de `BUILD_ID` del `Makefile`; nada de `build/` ni `compilaciones/`.
- `yaml.safe_load` acepta el workflow: 4 entradas a pedido (`base`, `publicar`, `release` y `limpiar_ramas`) y 6 jobs. `bash -n` pasa en cada `run`.
- La etiqueta de `release` llega por variable de entorno, sin inyección en el script. La ISO coincide con `ISO_NAME` del `Makefile` y la falta de `docs/versiones/<etiqueta>.md` corta con un mensaje.
- `limpiar-ramas`, simulado con repositorios locales: borra solo las ramas contenidas en `main` y conserva las que tienen commits propios.
- `make test` en un worktree limpio: 0 fallos y ningún archivo por encima del tope de líneas.

**Hallazgos técnicos:**

**[Baja] El commit `ci:` agrupa cuatro cambios independientes**
- Archivo: `.github/workflows/compilacion.yml:17-164` (`24ed39a0`)
- Riesgo: compilar DEV, el tipo del commit de publicación, el job `release` y el job `limpiar-ramas` van juntos. No se podría revertir uno sin los demás.
- Recomendación: dividirlo si se aplica R-GOB-01 al pie de la letra; si se acepta la agrupación de CC-09, nada.
- Estado: aceptado. CC-09 aprobó los cuatro cambios como uno solo.

**[Baja] Documentación desfasada por este bloque, fuera de sus archivos**
- Archivo: `README.md`, `docs/traduccion/especificacion.md` (R-INF-05) y `docs/traduccion/plan.md` §9
- Riesgo: el valor de `BUILD_ID`, el número de jobs y el paso DEV quedaban desfasados (R-GOB-08).
- Recomendación: actualizarlos en la documentación de F8.
- Estado: resuelto en la documentación de F8 (R-INF-05 y plan.md §9.2).

**[Baja] `release` y `publicar` en el mismo lanzamiento publican la ISO anterior**
- Archivo: `.github/workflows/compilacion.yml:124`
- Riesgo: `release` no depende de `publicar`. Lanzados a la vez, `release` etiqueta el commit anterior a la publicación y sube la ISO vieja.
- Recomendación: lanzar `release` en una segunda ejecución, sobre el commit de publicación, o añadir `&& inputs.publicar != 'si'` a su condición.
- Estado: aceptado como procedimiento: primero `publicar` y después `release`, en otra ejecución, sobre el commit de publicación ([plan.md §9.2](../plan.md#92-en-la-ci)).

**Hallazgos lingüísticos:**

**[Media] Descripciones de entradas y salida de la CI sin tildes**
- Archivo: `.github/workflows/compilacion.yml`
- Riesgo: la pantalla de GitHub Actions mostraba «vacio» y «estan».
- Recomendación: «vacío» y «están».
- Estado: resuelto en `b69f1548`, que además acepta `sí` con tilde. Queda sin tilde el `echo` de `limpiar-ramas` («tiene commits que no estan en main», línea 162), que sale en el registro de la CI ([deuda.md](../deuda.md)).

**[Baja] Comentario sin tildes**
- Archivo: `.github/workflows/compilacion.yml`
- Riesgo: «esta» y «ningun» en un comentario.
- Recomendación: «está» y «ningún».
- Estado: resuelto en `b69f1548`.

**Decisión:** se integra con `1ac5c96f`.

## 2. `sinc/graficos`: correcciones de gráficos (CC-11, G5; G2 y G4 retirados)

**Commits revisados:** `fb6a81c0` (G5), `ae92ebc4` (G2), `d9c9e2ee` (G4) y, tras la primera pasada, `27091745` (alfa 0xFF del `.tga`), `30dc154e` (pedido de captura sin volcar) y `adf45533` (deshace G4).

**Commit integrado:** `ce98830c` (`fix(graficos): G_AC_DITHER limita a 0 el alfa negativo antes de elevarlo`), en la rama `sinc/graficos-g5`.

**Comprobaciones de REVISIÓN técnica:**

- Diff de tres puntos dentro de los archivos del bloque; nada de `build/` ni `compilaciones/`; `git diff --check` sin errores.
- Commits con autor correcto, sin firma ni trailers; las referencias «antes» de los mensajes coinciden con la base.
- `gcc -fsyntax-only` con cabeceras simuladas del SDK sobre `guiones_prueba.c` e `interprete_f3dex.c` (release, DEBUG y DEV): ningún diagnóstico en las líneas cambiadas. Errores puestos a propósito en copias se detectan.
- `cc_lee_shade`, extraída con `sed` y compilada con `combinador_color.c` en el PC, sobre los combinadores reales. El programa no se versiona.
- `ps2_screenshot_file` del ps2sdk copia el byte de alfa del CT32 sin cambiarlo.
- `make test` en un worktree limpio: 0 fallos.
- Segunda pasada: `27091745` fija `RGBAQ` a `0xFF808080`; en `30dc154e` la espera previa y la propia comparten el tope de 900 cuadros; `git diff d9c9e2ee~1 HEAD -- matrices_y_vertices.inc.c` sale vacío.

**Hallazgos técnicos:**

**[Alta] G2: `RGBAQ` con alfa 0x80 no hace opaco el `.tga`**
- Archivo: `codigo/graficos/sintetizador_gs.c:863` (en la rama)
- Riesgo: con TCC=0 y DECAL, el alfa del píxel es el de `RGBAQ`; 0x80 es 1,0 para el GS pero 128/255 en el archivo.
- Recomendación: fijar el alfa a 0xFF solo en el volcado de captura.
- Estado: resuelto en `27091745`, no integrado (G2 retirado de CC-11).

**[Media] G2: un pedido sin volcar bloquea para siempre la siguiente «captura»**
- Archivo: `codigo/depuracion/guiones_prueba.c:729` (en la rama)
- Riesgo: la espera por un «graba» pendiente no tenía tope; el guion no llegaba a `fin`.
- Recomendación: liberar el propio pedido al vencer el tope y limitar la espera previa.
- Estado: resuelto en `30dc154e`, no integrado (G2 retirado de CC-11).

**[Media] G5 sin la verificación que exige CC-11 (`prueba_combinador`)**
- Archivo: `codigo/graficos/interprete_f3dex/combinador_y_recorte.inc.c:35`
- Riesgo: la lógica es correcta (-64 daba 32 y ahora 0; de 0 a 128 no cambia), pero una regresión futura pasaría sin detectarse.
- Recomendación: (a) mover el promedio a una función pura de `combinador_color.c` y probarla en `prueba_combinador` (-64 → 0, 64 → 32, 128 → 128), o (b) aprobar por escrito la evidencia de código.
- Estado: abierto en las dos pasadas. INTEGRACIÓN integró G5 con la evidencia del mensaje de `ce98830c` (opción b); falta la confirmación del responsable del proyecto. La prueba queda como deuda ([deuda.md](../deuda.md)).

**[Media] G4 depende de una captura antes/después que no existe**
- Archivo: `codigo/graficos/interprete_f3dex/matrices_y_vertices.inc.c:932` (en la rama)
- Riesgo: el cambio del tramado alcanza también a objetos 3D y al humo PRIM/ENV, sin la captura que CC-11 exigía.
- Recomendación: no integrar `d9c9e2ee`.
- Estado: resuelto con `adf45533` (deshace G4). G4 se retiró de CC-11 (`b4b37c13`) y queda como propuesta para el original.

**[Baja] El mensaje de `27091745` da por observado un dato que solo se dedujo del código**
- Archivo: `codigo/graficos/sintetizador_gs.c:863` (en la rama)
- Riesgo: dice que el `.tga` «tenía alfa 0x80 en todos los píxeles», pero no se midió.
- Recomendación: anotarlo como deducido del código.
- Estado: aceptado; el commit no se integra.

**Hallazgo lingüístico:**

**[Baja] Comentarios nuevos sin tildes**
- Archivo: `matrices_y_vertices.inc.c`, `tarea_graficos.inc.c` y `sintetizador_gs.c`
- Riesgo: «Algun», «vertice», «triangulos», «menu». No se ve en pantalla; dos de esos archivos están enteros en ASCII.
- Recomendación: opcional.
- Estado: aceptado. `ce98830c` no añade comentarios a esos archivos.

**Decisión:** se integra solo G5, como `sinc/graficos-g5` (`368a5416`). G2 y G4 salen de CC-11 por decisión del responsable del proyecto (`b4b37c13`): G2 no tiene uso sin capturas y G4 cambia la imagen sin forma de verificarlo. Los dos van a [Propuestas para el repositorio original](#8-propuestas-para-el-repositorio-original).

## 3. `sinc/sistema`: arranque, cronómetro, ROM y Memory Card (CC-08 y CC-11, E3-E5)

**Commits integrados:** `664d9013` (prueba de arranque), `176651ed` (E3), `a86960cf` (E4), `61a88a74` (E5) y `372f10ed` (tildes de las salidas de prueba). Son los revisados, con los mensajes reescritos (ver el [resumen](#resumen)).

**Comprobaciones de REVISIÓN técnica:**

- El diff de tres puntos toca 6 archivos del bloque; el `Makefile` solo añade las 2 pruebas detrás de `prueba_textos_port.py`. `git merge-tree` limpio contra la base y contra las ramas hermanas que tocan el `Makefile`.
- `make test` en un worktree limpio: 0 fallos, con `prueba_arranque.py` y `prueba_cronometro_fases`. Las tres pruebas, en verde en cada commit.
- Rojo y mutaciones reproducidos: `GRUPOS_MAX` 4 da 5 fallos, 5 da 3 y 6 da 0; las cinco mutaciones de `arranque_ps2.c` dan los FALLO que citan los mensajes.
- `carga_rom.c`, `memory_card.c` y `cronometro_fases.c` pasan `gcc -fsyntax-only -Wall -Wextra` contra cabeceras falsas del SDK, en release, DEBUG y DEV.
- Contraste con `libmc.c` y `delaythread.c` del ps2sdk: el peor caso de E4 queda en unos 24-25 s, por debajo de los 30 s del perro guardián.

**Hallazgos técnicos:**

**[Media] Los 4 mensajes de commit terminaban en un trailer de git («Requisitos: …»)**
- Archivo: mensajes de `feafb878`, `98a33c68`, `21005b69` y `63c6ab06`
- Riesgo: incumple la regla «sin trailers»; una comprobación automática rechazaría la rama.
- Recomendación: reescribir solo los mensajes, con la trazabilidad como frase («Cubre …»), y comprobar que los árboles no cambian.
- Estado: resuelto antes de integrar. Los mensajes dicen «Cubre …» y `git log --format='%(trailers)' origin/main..feature/sincronizacion-upstream` sale vacío en todos los commits.

**[Baja] `leer_archivo_mc()` descarta una lectura completa cuando solo vence `mcClose`**
- Archivo: `codigo/sistema/memory_card.c:137`
- Riesgo: si la tarjeta contesta a la lectura y no al cierre, la partida no se carga.
- Recomendación: devolver `n` tras el cierre, o dejarlo escrito como decisión.
- Estado: abierto ([deuda.md](../deuda.md)).

**[Baja] El borrado de los archivos viejos no mira `mc_ok` entre sus dos esperas**
- Archivo: `codigo/sistema/memory_card.c:326-329`
- Riesgo: si vence el primer `mcDelete`, el segundo espera otros 5 s y repite el aviso. Pasa una vez y con archivos de compilaciones anteriores.
- Recomendación: poner el segundo `mcDelete` bajo `if (mc_ok)`.
- Estado: abierto ([deuda.md](../deuda.md)).

**[Baja] La escritura tardía de libmc en `type`/`free`/`format` de la pila no queda registrada**
- Archivo: `codigo/sistema/memory_card.c:89`
- Riesgo: viene de antes y la rama no lo empeora. Si `mcGetInfo` vuelve después del tiempo límite, libmc escribe en la pila ya liberada de `listo_tarjeta_mc()`.
- Recomendación: registrarlo, o hacer `static` esas 3 variables con un CC propio.
- Estado: registrado en [deuda.md](../deuda.md).

**[Baja] El contrato «uno por cada `GRUPO_`» depende de un 4 escrito a mano**
- Archivo: `codigo/sistema/cronometro_fases.c:9` y `herramientas/pruebas/prueba_cronometro_fases.c:36-38`
- Riesgo: con un séptimo grupo, la prueba seguiría en verde y el fallo de E3 volvería.
- Recomendación: contar los `#define GRUPO_` de `marcas_registro.h` en la prueba, o quitar el «(4)» del comentario.
- Estado: abierto ([deuda.md](../deuda.md)).

**[Baja] Los mensajes de `664d9013` y `176651ed` citan las salidas de prueba sin tildes**
- Archivo: mensajes de esos dos commits
- Riesgo: las salidas ya llevan tildes (`372f10ed`); las citas de los mensajes, no.
- Recomendación: corregirlas si se reescriben los mensajes.
- Estado: aceptado. Los mensajes se reescribieron solo para quitar los trailers.

**Hallazgos lingüísticos:**

**[Media] Mensajes de prueba nuevos sin tildes**
- Archivo: `herramientas/pruebas/prueba_arranque.py` y `prueba_cronometro_fases.c`
- Riesgo: `make test` imprimía «encontro», «linea», «cronometro», «ningun» y «lineas».
- Recomendación: poner las tildes.
- Estado: resuelto en `372f10ed`.

**[Baja] Comentarios y docstrings sin tildes**
- Archivo: `carga_rom.c`, `cronometro_fases.c`, `memory_card.c` y las dos pruebas
- Riesgo: no se ve en pantalla.
- Recomendación: opcional.
- Estado: corregido en las dos pruebas (`372f10ed`); aceptado en el código, que sigue el estilo ASCII de esos archivos.

El literal nuevo del registro, «memory card: no se pudo guardar (%d); la tarjeta no contesta y no se reintentará», es correcto y sigue el prefijo de los demás registros del archivo.

**Decisión:** se integra con `bbb11eb6`, después de reescribir los mensajes.

## 4. `sinc/pendientes`: R-FUE-05, R-FUE-07 y L2 (CC-08 y CC-11)

**Commits integrados:** `e600bd6e` y `697f3af6` (pruebas de la tabla de glifos y del tope), `9adc3192` (L2), `a5e97ddf` (prueba del detector, en rojo), `f38d6de6` (registro DEV), y de la primera pasada `94cdfea5` (registro en las tres impresoras) y `27199b8f` (tildes de las pruebas).

**Comprobaciones de REVISIÓN técnica:**

- merge-base `36fc9e40`; `git merge-tree` limpio; diff de tres puntos con 9 archivos del bloque; nada de `build/` ni `compilaciones/`; el grep de R-GOB-07 sale vacío.
- `make test`: `prueba_glifos` 38/0, `prueba_tablas_glifos` 695/0 (699/0 en la segunda pasada), `prueba_caracteres_es` 89/0 y `prueba_textos_port` 8596/0. `prueba_glifos` también con `-fsanitize=address,undefined`.
- Rojo de `a5e97ddf` reproducido: el enlace falla sin `primer_byte_invalido` y, con un sustituto que devuelve -1, da 11 fallos.
- Mutaciones de `primer_byte_invalido` (sin C2/C3: 4 fallos; avance de 1 byte: 2; sin la guarda del 0: ASan) y de la tabla de glifos (tope 0x2F7, tope con `>`, tabla dentro de `#ifdef AVOID_UB`, alias del original, bloque de `ae93f71`): todas en FALLO salvo la del hallazgo de abajo.
- `gcc -fsyntax-only` de `elementos_menu.c` y `depuracion.c`, con y sin `-DSMK64_DEV=1`: nada en las líneas nuevas; errores puestos a propósito se detectan.
- L2: las líneas que cita el mensaje coinciden; con matriz libre la conducta no cambia.

**Hallazgos técnicos:**

**[Media] El registro DEV de cadenas que la fuente no dibuja solo se llamaba desde `imprimir_texto1`**
- Archivo: `codigo/menus/elementos_menu/imprimir_texto.inc.c` (`imprimir_texto0` e `imprimir_texto2`)
- Riesgo: una cadena UTF-8 sin convertir impresa con `imprimir_modo_texto_1` o `dibujar_texto` no se registraba.
- Recomendación: el mismo enganche al principio de las otras dos impresoras.
- Estado: resuelto en `94cdfea5`, con la comprobación `probar_registro_texto_invalido` (rojo: 2 fallos; mutación: 1).

**[Baja] `probar_tope_reserva` acepta un tope con suma**
- Archivo: `herramientas/pruebas/prueba_tablas_glifos.py:168`
- Riesgo: `>= MTX_EFECTO_POOL_TAMANIO + 1` pasa la prueba y escribiría fuera de la reserva. Las regresiones más probables (0x2F7, `_MAX`, `>`) sí se detectan.
- Recomendación: anclar la expresión al cierre de la condición.
- Estado: abierto ([deuda.md](../deuda.md)).

**[Baja] La rama no estaba sobre la base actual**
- Archivo: `README.md` (solo en el diff de dos puntos)
- Riesgo: integrar aplicando el diff de dos puntos revertiría el README de la base.
- Recomendación: integrar con merge.
- Estado: resuelto; se integró con merge (`cf956b42`).

**[Baja] La docstring nueva de `prueba_tablas_glifos.py` sigue sin tildes** (segunda pasada)
- Archivo: `herramientas/pruebas/prueba_tablas_glifos.py:18-20` y `:177`
- Riesgo: «compilacion», «invalido», «funcion»; el resto del archivo ya estaba en ASCII.
- Recomendación: opcional.
- Estado: aceptado.

**Hallazgos lingüísticos:**

**[Media] Mensajes de prueba nuevos sin tildes**
- Archivo: `herramientas/pruebas/prueba_glifos.c` y `prueba_tablas_glifos.py`
- Riesgo: «byte invalido» y «ninguna declaracion».
- Recomendación: «inválido» y «declaración».
- Estado: resuelto en `27199b8f`.

**[Baja] Comentarios nuevos sin tildes**
- Archivo: `depuracion.c`, `caracteres_es.h`, `sistema_ps2.h` y `prueba_tablas_glifos.py`
- Riesgo: no se ve en pantalla.
- Recomendación: opcional.
- Estado: aceptado.

El registro nuevo de `cargar_texturas_menu.inc.c` va en ASCII («menu: reserva de matrices agotada…») porque ese archivo se convierte a EUC-JP (R-PORT-02); el de `depuracion.c`, que no se convierte, lleva sus tildes.

**Decisión:** se integra con `cf956b42`.

## 5. `sinc/panel`: interlineado del panel y botones de las texturas (CC-11, L3; R-TEX-07)

**Commits integrados:** `4612a508` (prueba, en rojo), `ac4fcdae` (L3), `5d901a47` (R-TEX-07) y `4e4cc6f8` (tildes de la prueba).

**Comprobaciones de REVISIÓN técnica:**

- Diff de tres puntos con 4 archivos del bloque; `git merge-tree` limpio con la base y con las ramas hermanas; ninguna otra rama toca el reparto de VRAM.
- Commits sin firma ni trailers; prueba y cambio en dos commits (forma A del plan).
- La cuenta de L3: 12 líneas de 9 filas = 108 filas, dentro de las 128 que lee el GS; 128 KB son las 16 páginas CT32 de la textura. El atlas en DEBUG conserva sus 12 filas de páginas antes y después (supone dos framebuffers CT16S de 640 × 448 y Z de 24 bits; no hay registro real de PS2 que lo confirme).
- Cabeceras compiladas en el PC con un `tamtypes.h` de prueba y `_Static_assert`.
- Rojo de `4612a508` reproducido (87 comprobaciones, 1 fallo); mutaciones del autor y de REVISIÓN (alto de textura 136, VRAM de 120 KB, alto de línea + 2) en FALLO. R-TEX-07: 671 comprobaciones; dan FALLO `R|DATOS`, `L|OPCIONES`, «Ⓐ OK» y `CONTROLLER|PAK`.
- `make test` en un worktree limpio: 0 fallos.

**Hallazgos técnicos:**

**[Media] La rama se aparta de CC-11 L3 (128 KB en vez de 112 KB y otra prueba) y la diferencia no estaba registrada**
- Archivo: `docs/traduccion/cambios.md` (CC-11, fila L3); cambio en `incluir/depuracion/medidor_rendimiento.h:10`
- Riesgo: la especificación y el código quedaban contradictorios. El cambio técnico es correcto.
- Recomendación: registrar en CC-11 los 128 KB con su motivo, la verificación en `prueba_ancho_panel.py` y los commits.
- Estado: resuelto en la documentación de F8 ([CC-11](../cambios.md), «Diferencia en L3»).

**[Baja] La prueba de R-TEX-07 exige más que la aceptación escrita**
- Archivo: `herramientas/pruebas/prueba_texturas_es.py:45`
- Riesgo: prohíbe también Z, A, B, N64 y CONTROLLER PAK. Una preposición «A» en un `texto_es` futuro daría FALLO.
- Recomendación: escribir en R-TEX-07 la lista exacta, con ese aviso.
- Estado: resuelto en la especificación (R-TEX-07).

**[Baja] El mensaje de `ac4fcdae` no describe del todo bien qué se pisaría con 112 KB**
- Archivo: mensaje de `ac4fcdae`
- Riesgo: dice filas 0..15 del atlas; son las 0..11. En la otra dirección, el atlas taparía desde x 128 la línea 11 y las filas 96-97 de la línea 10.
- Recomendación: usar estas cifras al registrar la diferencia.
- Estado: resuelto en CC-11.

**[Baja] `make test` deja modificados binarios versionados en `build/`** (segunda pasada)
- Archivo: `build/herramientas/mio0`, `build/ps2/pruebas/*`
- Riesgo: no lo introduce la rama; se puede colar en un commit con `git add -A`.
- Recomendación: restaurar `build/` antes de cada commit.
- Estado: aceptado. Es la regla de [CONTRIBUTING.md](../../../CONTRIBUTING.md): `build/` solo cambia en el commit de publicación.

**Hallazgos lingüísticos:**

**[Media] Mensajes de prueba nuevos sin tildes**
- Archivo: `herramientas/pruebas/prueba_ancho_panel.py`
- Riesgo: «linea», «lineas» y «paginas» justo en la prueba de las tildes del panel.
- Recomendación: poner las tildes.
- Estado: resuelto en `4e4cc6f8`.

**[Baja] Docstrings y comentarios sin tildes**
- Archivo: `prueba_ancho_panel.py`, `prueba_texturas_es.py`, `medidor_rendimiento.h` y `texto_pantalla.h`
- Riesgo: no se ve en pantalla.
- Recomendación: opcional.
- Estado: corregido en `prueba_ancho_panel.py` (`4e4cc6f8`); aceptado en el resto.

**Decisión:** se integra con `240358fd`.

## 6. `sinc/recorrido`: guiones de PCSX2 con capturas (CC-10, rechazado)

**Commits revisados:** `bb920d50`, `32747840`, `229b9656`, `8c8b3e5e`, `443358b0`, `9c024f89`, `2ed664cc` y `93cae6c0`. Ninguno se integra.

**Comprobaciones de REVISIÓN técnica:**

- Diff de tres puntos con los archivos del bloque (`Makefile`, `herramientas/guiones/`, `hoja_capturas.py`, `hojas_es.py` y dos pruebas nuevas).
- Rojo de `prueba_guiones.py` (6 fallos) y de `prueba_hoja_capturas.py` (1 fallo) reproducidos; mutaciones («pulsa_hast», «pulsa A 0x2», bit de origen del TGA) en FALLO; refactor de `hojas_es.py` con las 15 hojas idénticas.
- `make test`: 0 fallos.
- La conducta en el emulador no se pudo verificar.

**Hallazgos técnicos:**

- **[Baja]** La orden de la hoja del encabezado de `01_menus.txt:10` falla sin `python3` («Permission denied»).
- **[Baja]** El mensaje de `2ed664cc` cita `estados_menu.inc.c:80` (es la `:78`) y exagera el «solo».
- **[Baja]** `capturas_guion` (`hoja_capturas.py:78`) lista «graba no N M» como una serie de capturas.
- **[Baja]** La documentación apuntaba al guion `recorrido_textos.txt`, que la rama borraba.

**Hallazgos lingüísticos:**

- **[Baja]** «nota vs de 3 jugadores» en minúsculas en `03_modos.txt`; el glosario fija VS.
- **[Baja]** «1 JUG..4 JUG» sin el punto de la abreviatura en `01_menus.txt`.

Todos quedan sin efecto con la rama.

**Decisión:** no se integra. El responsable del proyecto rechazó CC-10 (`b4b37c13`): el proyecto se verifica con las pruebas del PC y la CI, sin capturas ni pasos manuales (CC-12). `herramientas/guiones/recorrido_textos.txt` queda como estaba.

## 7. Revisión lingüística de la fusión y de los textos nuevos del original

**Commits:** `9f4d0215` (fusión), `748db117`, `36fc9e40` y `409a72b9`.

**Comprobaciones:**

- Cuerpos de los commits en español correcto; el asunto del merge es el de git por defecto, que R-GOB-01 admite.
- De las 49 líneas con literales de `git diff 0e7b7d51 upstream/main -- codigo incluir`, todas las que tenían faltas están corregidas: «falló», «leído», «aceptó», «terminó», «quedó», «contestó», «memory card:», «cuadros», «montón», «reserva del juego», «imágenes», «4 o más», «tirón», «próxima». Los grupos del cronómetro pasaron a `GRUPO_CARGA_CEREMONIA` y `GRUPO_CARGA_CREDITOS`.
- Ninguno de esos archivos está en `JP_SRC` ni en `JP_PARTES`. `prueba_textos_port.py` da 8577 comprobaciones y 0 fallos, y `prueba_ancho_panel.py`, 84 y 0.

**Hallazgos:**

**[Baja] Valor de registro «no» poco claro en el estado del multitap**
- Archivo: `codigo/entrada/multitap.c:49-50`
- Riesgo: «multitap en el puerto 1: no» se lee mal junto a «conectado», «sin servicio» y «quitado».
- Recomendación: «no conectado» o «sin multitap».
- Estado: abierto ([deuda.md](../deuda.md)).

**[Baja] Comentarios del original sin tildes**
- Archivo: los archivos que trajo la fusión (`multitap.c`, `mandos.c`, `interprete_f3dex/*.inc.c`, `arranque_ps2.c`, `ritmo_fisica.c` y otros)
- Riesgo: no se ve en pantalla; también hay anglicismos («frame», «buffer», «driver»).
- Recomendación: opcional, en un commit aparte solo de comentarios, comprobado con `comparar_preprocesado.py`.
- Estado: aceptado; es opcional y no se ve en pantalla.

**[Baja] Nombre de grupo con tilde en un informe alineado por bytes**
- Archivo: `incluir/depuracion/marcas_registro.h`
- Riesgo: «carga de créditos» descuadra una columna del informe (`%-26s`). Ya está en la especificación (§7, «Alineación del registro»).
- Recomendación: ninguna.
- Estado: aceptado.

## 8. Propuestas para el repositorio original

Defectos del código que trae el original que este repositorio no corrige, para proponerlos a `anthoo582/mario-kart-64-ps2`. Ninguno tiene un caso visible que se pueda verificar sin capturas.

| Propuesta | Dónde | Qué pasa | Corrección propuesta |
|---|---|---|---|
| G2: la captura de los guiones | `codigo/depuracion/guiones_prueba.c` (orden `captura`, solo DEV), `tarea_graficos.inc.c` y `sintetizador_gs.c` (`gs_pantalla_a_ct32`) | La tarea de gráficos y el guion comparten el pedido sin protección: un «graba» en curso pisa una «captura» y el `.tga` no se vuelca. El volcado toma el alfa de `RGBAQ`, que queda del último vértice, y el `.tga` sale transparente | Leer el pedido una sola vez y borrarlo solo si sigue siendo el mismo (con `DI()`/`EI()`), poner un tope a toda espera y fijar el alfa a 0xFF en el volcado. Hecho y revisado en `sinc/graficos` (`ae92ebc4`, `27091745` y `30dc154e`) |
| G3: la segunda pasada `m·TEXEL + PRIM` | Intérprete F3DEX | No desplaza el modo REGION_REPEAT. Hoy ningún dibujo lo usa | Aplicar el desplazamiento también en la segunda pasada cuando haya un caso que lo use |
| G4: el tramado por primitiva | `codigo/graficos/interprete_f3dex/matrices_y_vertices.inc.c` | El tramado alcanza a las letras del menú y a los puestos del HUD | Tramar solo cuando el combinador lee SHADE o SHADE_ALPHA, o hay niebla. Hecho en `d9c9e2ee` y deshecho en `adf45533`, a falta de una captura antes/después |
| Comentario incorrecto del tramado | `matrices_y_vertices.inc.c:914` | Dice que «el HUD, los menús y el texto son rectángulos», pero `pantalla_rectangulo_comun` son dos triángulos (`gsSP2Triangles`, `recursos/comunes/datos_comunes.c:1102`) | Corregir el comentario junto con G4 |
