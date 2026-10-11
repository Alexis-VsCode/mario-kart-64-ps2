# Deuda técnica

Lo que se sabe que falta o que se hizo con una salvedad, separado de lo pendiente del plan ([README.md § Pendiente](README.md#pendiente)). Cada entrada dice qué hay que hacer, por qué no se hizo y dónde se haría. Las que vienen de la revisión de F8 enlazan al [acta](revisiones/2026-10-11-sincronizacion.md).

Saldar una entrada sigue el proceso normal: si cambia un requisito o un contrato, primero un CC en [cambios.md](cambios.md); después la prueba en rojo, el cambio y la revisión. Al saldarla, la fila se borra aquí y el commit se anota en [trazabilidad.md](trazabilidad.md).

## Verificación

| Id | Qué | Medida | Por qué no ahora | Dónde se saldaría |
|---|---|---|---|---|
| D-01 | G5 (CC-11) no tiene prueba en el PC. La corrección de `G_AC_DITHER` (`ce98830c`) se verificó con evidencia de código en su mensaje, no con `prueba_combinador` como pedía CC-11 | Probar el alfa del tramado con casos fijos: -64 da 0, 64 da 32 y 128 da 128, con rojo y mutación demostrados. Necesita D-02 | `combinar_color` está en `combinador_y_recorte.inc.c`, que solo compila con el SDK de PS2. Mover código a `combinador_color.c` quedaba fuera de los archivos del bloque de F8 | Un CC que amplíe el bloque de gráficos. Hasta entonces, la confirmación del responsable del proyecto de que G5 se acepta con evidencia de código |
| D-02 | Las pruebas del combinador exigen mover código a `combinador_color.c` | Pasar a funciones puras de `codigo/graficos/combinador_color.c` e `incluir/graficos/combinador_color.h` el promedio del alfa con tramado (por ejemplo, `combinador_alfa_tramado`) y, si G4 vuelve, la lectura de SHADE (`combinador_lee_shade`), y añadir sus casos a `herramientas/pruebas/prueba_combinador.c` | Es un cambio de estructura del intérprete; en F8 solo entraban correcciones mínimas (CC-11) | El mismo CC que D-01 |
| D-03 | R-TEX-03: el crecimiento de la ROM se midió a mano (`rom.bin` + 6 144 B frente a `main`) | Un paso de la CI que compare el tamaño de `build/ps2/rom.bin` con el de la base y falle si crece 256 KB o más | `rom.bin` solo existe con el SDK, y `make test` corre sin él | Job `compilar-ps2` o `mismo-binario` de la CI |
| D-04 | R-TEX-08: la prueba revisa las reglas del sello `ES_SELLO` en el `Makefile`, no un build incremental real | Compilar, quitar una sustitución de `build/ps2/es`, volver a compilar sin `make clean` y comprobar que vuelve la textura original | Necesita el SDK y una segunda compilación | Job `compilar-ps2` de la CI |
| D-05 | R-TEX-02: ninguna prueba exige fila o exclusión de carpeta para las texturas fuera de las 63 TKMK00 y las 15 del Controller Pak | Recorrer las carpetas y `.incbin` que enumera R-TEX-02 y exigir a cada textura una fila o una exclusión con motivo | El manifiesto no tiene tipo de fila de carpeta, y ninguna decisión escrita nombra una carpeta concreta para excluir | Un CC con el formato de la fila de carpeta y cambios en `herramientas/texturas_es.py` y `prueba_texturas_es.py` |
| D-06 | Sin verificación visual: nadie del proyecto ha visto la versión en PCSX2, en Play!, en una TV ni en una PS2 real. Las medidas de texto, texturas y HUD las comprueban las pruebas del PC; la imagen final, no | Ninguna dentro del proyecto: CC-12 retiró los recorridos y las capturas | Decisión del responsable del proyecto (CC-12): la versión se verifica con las pruebas y la CI. Se declara como limitación en el manual de usuario y en las notas de versión | Si alguien aporta capturas o un defecto visual, se registra en un CC y se corrige con su prueba |

## Código

| Id | Qué | Medida | Por qué no ahora | Dónde se saldaría |
|---|---|---|---|---|
| D-07 | Puerta G-FALLO: la pantalla de fallo translitera siempre (sin tildes); el registro las conserva (R-PORT-03) | Un paso de la CI que inspeccione la fuente de libdebug y, si tiene glifos CP437, transcodifique las letras disponibles | La transliteración es legible y está probada (`prueba_caracteres_es.c`); la inspección depende del SDK | Un CC sobre R-PORT-03 y un paso de la CI |
| D-08 | Otros sitios escriben `efecto_mtx` sin tope (especificación §8): `imprimir_texto.inc.c`, `menus_pausa.inc.c`, `particulas_derrape.inc.c`, `globos_batalla.inc.c`, `dibujar_kart_y_sombra.inc.c` y `actores_podio.c` | Tope de la reserva en cada sitio, como en `funcion_80095BD0` | Fuera del alcance de R-FUE-07 y sin un caso medido | Un requisito propio en [cambios.md](cambios.md) |
| D-09 | `probar_tope_reserva` acepta `>= MTX_EFECTO_POOL_TAMANIO + 1` ([acta §4](revisiones/2026-10-11-sincronizacion.md#4-sincpendientes-r-fue-05-r-fue-07-y-l2-cc-08-y-cc-11)) | Anclar la expresión de `prueba_tablas_glifos.py:168` al cierre de la condición y registrar esa mutación | Hallazgo Baja; las regresiones probables sí se detectan | `herramientas/pruebas/prueba_tablas_glifos.py` |
| D-10 | El contrato «al menos un grupo por cada `GRUPO_`» depende de un 4 escrito a mano ([acta §3](revisiones/2026-10-11-sincronizacion.md#3-sincsistema-arranque-cronómetro-rom-y-memory-card-cc-08-y-cc-11-e3-e5)) | Contar en `prueba_cronometro_fases.c` los `#define GRUPO_` de `marcas_registro.h` y exigir `GRUPOS_MAX` mayor que ese número | Hallazgo Baja; hoy hay 4 grupos y caben 6 | `herramientas/pruebas/prueba_cronometro_fases.c` |
| D-11 | `leer_archivo_mc()` devuelve -1 cuando la lectura terminó y solo vence `mcClose` (`memory_card.c:137`) | Devolver `n` después del cierre, o escribir la decisión | Hallazgo Baja; E5 no lo pedía | `codigo/sistema/memory_card.c`, con un CC si cambia la conducta |
| D-12 | El borrado de los archivos viejos espera dos veces aunque la tarjeta no conteste (`memory_card.c:326-329`) | Poner el segundo `mcDelete` bajo `if (mc_ok)` | Hallazgo Baja; pasa una vez y con archivos de compilaciones anteriores | `codigo/sistema/memory_card.c` |
| D-13 | Si `mcGetInfo` vuelve después del tiempo límite, libmc escribe en `type`/`free`/`format`, en la pila ya liberada de `listo_tarjeta_mc()` (`memory_card.c:89`) | Hacer `static` esas tres variables | Viene de antes de F8 y CC-11 solo aprobó inicializarlas | Un CC propio |

## Textos

| Id | Qué | Medida | Por qué no ahora | Dónde se saldaría |
|---|---|---|---|---|
| D-14 | El registro del multitap dice «multitap en el puerto 1: no» cuando el puerto está abierto y no hay multitap (`multitap.c:49-50`) | «no conectado» o «sin multitap» | Hallazgo Baja de la revisión lingüística; no se ve en pantalla | `codigo/entrada/multitap.c` |
| D-15 | El registro de la CI dice «tiene commits que no estan en main» (`compilacion.yml:162`) | «están» | Quedó fuera de `b69f1548` | `.github/workflows/compilacion.yml` |
