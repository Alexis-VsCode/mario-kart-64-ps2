# Deuda técnica

Lo que se sabe que falta o que se hizo con una salvedad, separado de lo pendiente del plan ([README.md § Pendiente](README.md#pendiente)). Cada entrada dice qué hay que hacer, por qué no se hizo y dónde se haría. Las que vienen de una revisión enlazan a su acta: la de F8 ([2026-10-11-sincronizacion.md](revisiones/2026-10-11-sincronizacion.md)), la de F9 ([2026-10-11-version-1.1.0.md](revisiones/2026-10-11-version-1.1.0.md)) o la de F10 ([2026-10-11-version-1.2.0.md](revisiones/2026-10-11-version-1.2.0.md)).

Las entradas saldadas están en [trazabilidad.md](trazabilidad.md): las de F9 (D-01, D-02, D-09 a D-15) en [§ Deuda saldada en F9](trazabilidad.md#deuda-saldada-en-f9), y las de F10 (D-03 a D-08 y D-16 a D-25) en [§ Deuda saldada en F10](trazabilidad.md#deuda-saldada-en-f10).

Lo que no se puede comprobar sin hardware real ni TV no es deuda: son los [límites declarados de la especificación (§9)](especificacion.md#9-límites-declarados). Ahí pasaron D-06 (sin verificación visual en una TV ni en una PS2) y D-17 (ROMVER en consola real y bajo OPL), en lo que la CI no puede ver ([CC-26](cambios.md)).

Saldar una entrada sigue el proceso normal: si cambia un requisito o un contrato, primero un CC en [cambios.md](cambios.md); después la prueba en rojo, el cambio y la revisión. Al saldarla, la fila se borra aquí y el commit se anota en [trazabilidad.md](trazabilidad.md).

## Abierta

Ninguna. Toda la deuda conocida está saldada o pasó a los límites declarados.
