# Deuda técnica

Lo que se sabe que falta o que se hizo con una salvedad, separado de lo pendiente del plan ([README.md § Pendiente](README.md#pendiente)). Cada entrada dice qué hay que hacer, por qué no se hizo y dónde se haría. Las que vienen de una revisión enlazan a su acta: la de F8 ([2026-10-11-sincronizacion.md](revisiones/2026-10-11-sincronizacion.md)), la de F9 ([2026-10-11-version-1.1.0.md](revisiones/2026-10-11-version-1.1.0.md)) o la de F10 ([2026-10-11-version-1.2.0.md](revisiones/2026-10-11-version-1.2.0.md)).

Las entradas saldadas están en [trazabilidad.md](trazabilidad.md): las de F9 (D-01, D-02, D-09 a D-15) en [§ Deuda saldada en F9](trazabilidad.md#deuda-saldada-en-f9), y las de F10 (D-03 a D-08, D-16 a D-22 y D-24) en [§ Deuda saldada en F10](trazabilidad.md#deuda-saldada-en-f10).

Lo que no se puede comprobar sin hardware real ni TV no es deuda: son los [límites declarados de la especificación (§9)](especificacion.md#9-límites-declarados). Ahí pasaron D-06 (sin verificación visual en una TV ni en una PS2) y D-17 (ROMVER en consola real y bajo OPL), en lo que la CI no puede ver ([CC-26](cambios.md)).

Saldar una entrada sigue el proceso normal: si cambia un requisito o un contrato, primero un CC en [cambios.md](cambios.md); después la prueba en rojo, el cambio y la revisión. Al saldarla, la fila se borra aquí y el commit se anota en [trazabilidad.md](trazabilidad.md).

## Código

| Id | Qué | Medida | Por qué no ahora | Dónde se saldaría |
|---|---|---|---|---|
| D-23 | Con la reserva `efecto_mtx` llena, `funcion_800652D4` (`particulas_derrape.inc.c:690`) vuelve sin cargar matriz y sus llamadores en `particulas_derrape.inc.c`, `particulas_y_onomatopeyas.inc.c` y `globos_batalla.inc.c` dibujan la partícula con la matriz anterior: no escribe fuera del arreglo (R-FUE-09), pero sale un artefacto visual ([acta de F10 §6](revisiones/2026-10-11-version-1.2.0.md#6-v120deudas-deuda-técnica-cc-27)) | Que la función devuelva si cargó la matriz y que cada llamador se salte el dibujo si no | Hallazgo Baja; solo ocurre con el cuadro saturado y toca archivos de otro dueño | `codigo/carrera/objetos_y_efectos/particulas_y_onomatopeyas.inc.c` y los demás llamadores |

## Gobernanza

| Id | Qué | Medida | Por qué no ahora | Dónde se saldaría |
|---|---|---|---|---|
| D-25 | R-GOB-07: comentarios y docstrings de F10 citan identificadores de requisito o de deuda: `herramientas/ci/comprobar_incremental.sh:2`, `herramientas/ci/tope_rom.py:2`, `herramientas/pruebas/prueba_tope_rom.py:2` y `:40`, y `herramientas/pruebas/prueba_texturas_es.py:14`, `:57`, `:292` y `:319` ([acta de F10 §12](revisiones/2026-10-11-version-1.2.0.md#12-integración)) | Describir lo que comprueban sin nombrar el requisito; el identificador va en el commit y en [trazabilidad.md](trazabilidad.md) | Lo encontró la documentación de F10 después de integrar; ninguna revisión de rama lo señaló y los archivos son de otro dueño | Esos cuatro archivos, en un commit sin cambio de conducta |
