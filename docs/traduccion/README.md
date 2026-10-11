# Traducción al español

Esta carpeta documenta el trabajo con el que todo lo que ve el jugador en el port de Mario Kart 64 a PS2 sale en español:

- cadenas de menú y mensajes;
- créditos;
- texturas con texto: menús, títulos de pista, HUD y carteles de Lakitu;
- pantallas propias del port: panel de rendimiento, página de audio, pantalla de fallo y registro.

Los nombres de carpetas, funciones, variables y comentarios del código ya están en español. Aquí solo se trata el texto que sale en pantalla.

## Estado de F8 (2026-10-11)

La localización (F0 a F7) está cerrada y en `main` (`3f43c005`). F8, la sincronización con el repositorio original, está integrada en `feature/sincronizacion-upstream` hasta `d5f95cc5`. La versión que sale de ella es la 1.0.0, con `BUILD_ID` 2026-10-11.

Hecho en F8:

- **Sincronización** con `anthoo582/mario-kart-64-ps2` hasta `ae93f71` (fusión `9f4d0215`, [CC-08](cambios.md)): multitap, arranque desde OPL sin reiniciar el IOP, tiempos límite en el IOP, el CD y la Memory Card, 60 FPS más estables y caché de texturas por columnas. Los textos nuevos del original están en español (`748db117` y `36fc9e40`).
- **CI** ([CC-09](cambios.md)): `compilar-ps2` compila también `make DEV=1`; el commit de publicación pasa a tipo `build`; jobs a pedido `release` y `limpiar-ramas`.
- **Correcciones con evidencia** ([CC-11](cambios.md)): E3, E4, E5, G5, L2 y L3. G2 y G4 se retiraron y quedan como propuesta para el original. G5 se integró sin prueba en el PC y L3 usa 128 KB de VRAM en lugar de 112 KB; las dos diferencias están registradas en CC-11.
- **Pendientes técnicos de F3 y F4:** registro DEV de R-FUE-05 en las tres impresoras, prueba del tope de R-FUE-07, prueba de los botones de R-TEX-07 y prueba de la tabla de glifos frente a la forma del original (G1).
- **Revisión** técnica y lingüística de cada rama, registrada en el [acta de F8](revisiones/2026-10-11-sincronizacion.md).
- **Decisiones del responsable del proyecto:** CC-10 (recorrido con capturas) rechazado y [CC-12](cambios.md): la versión se verifica con las pruebas del PC y la CI, sin pasos manuales; F6 queda retirada.

| Fase | Contenido | Estado |
|---|---|---|
| F0–F5, F7 | Documentación, infraestructura, fuente, cadenas, texturas, pantallas del port, revisión e integración de la localización | Cerradas (histórico), en `main` (`3f43c005`). Detalle en [plan.md §4](plan.md#4-fases) |
| F6 | Recorrido en PCSX2 y captura en TV | Retirada por CC-12 |
| F8 | Sincronización con el original, CI, correcciones y documentación | Integrada en `feature/sincronizacion-upstream`. Falta lo de [Pendiente](#pendiente) |

El detalle por requisito y por commit está en [trazabilidad.md](trazabilidad.md); la deuda técnica, en [deuda.md](deuda.md).

## Pendiente

1. **Integrar la documentación de F8** (`sinc/manual`, `sinc/proceso` y esta rama) en `feature/sincronizacion-upstream`, con su revisión.
2. **Confirmación de G5.** CC-11 pedía `prueba_combinador` y G5 se integró con evidencia de código: falta que el responsable del proyecto lo confirme ([CC-11](cambios.md), [deuda.md](deuda.md) D-01).
3. **Publicación:** job `publicar` sobre `feature/sincronizacion-upstream`, que regenera `build/` y `compilaciones/` desde cero. La ejecución de la CI y el commit de publicación se anotan en [trazabilidad.md](trazabilidad.md#evidencia-común).
4. **Fusión a `main`** de `feature/sincronizacion-upstream`.
5. **Release v1.0.0:** job `release` sobre `main`, después de fusionar el commit de publicación, con la ISO versionada y las notas de [docs/versiones/v1.0.0.md](../versiones/v1.0.0.md). El tamaño y el SHA-256 de la ISO están en esas notas.
6. **Limpieza de ramas:** job `limpiar-ramas` sobre `main`. Al final, `git ls-remote --heads origin` lista solo `main` ([CC-09](cambios.md)). Se comprueba después de la fusión a `main`.

## Próximo paso

Revisar e integrar las tres ramas de documentación de F8 y, con la Definition of Done de [CONTRIBUTING.md](../../CONTRIBUTING.md) cumplida, lanzar `publicar` sobre `feature/sincronizacion-upstream`. El orden completo de la publicación (publicar, fusión a `main`, `release` y `limpiar-ramas`) está en el [manual técnico](../manual/tecnico.md).

## Punto de partida (verificado en `main`, `0e7b7d5`)

- **Fuente del menú.** No tenía Ñ, tildes, Ü, ¡, ¿, º ni ª (`car_a_indice_glifo` en `codigo/menus/elementos_menu/animaciones_personajes.inc.c`).
- **Tabla de glifos incompleta.** `lut_textura_glifo` tenía 91 entradas y `ancho_pantalla_glifo` tenía 236 (`codigo/menus/elementos_menu/textos_y_tablas.inc.c:777` y `:244`). En la N64, el resto de la tabla eran arreglos que el enlazador colocaba a continuación. En PS2, los índices a partir del 91 leían fuera de la tabla.
- **Texturas de menú.** Las texturas con texto son TKMK00 (`recursos/texturas/menus/tkmk00/`, 63 archivos). El repositorio solo traía el decodificador; las traducidas van en MIO0.
- **Mensajes de guardado.** Hablaban del «N64 CONTROLLER PAK» (`textos_y_tablas.inc.c:428-561`).
- **Compilación.** `make test` exigía `PS2SDK` (`Makefile:11-13`) y la conversión a EUC-JP dependía de `iconv` (`Makefile:255-261`). Las dos cosas cambiaron en F1.

## Documentos

| Documento | Contenido |
|---|---|
| [especificacion.md](especificacion.md) | Qué hay que cumplir: alcance, exclusiones, requisitos numerados con criterio de aceptación y prueba, decisiones cerradas y riesgos |
| [plan.md](plan.md) | Cómo se hizo: fases F0–F8 con su estado, roles y archivos, ramas, puertas de calidad, ciclo por bloque y verificación |
| [glosario.md](glosario.md) | Términos aprobados y su fuente |
| [trazabilidad.md](trazabilidad.md) | Relación entre requisito, prueba, commits y evidencia, con el estado de cada requisito y los commits de F8 |
| [cambios.md](cambios.md) | Registro de cambios de la especificación (CC-01 a CC-12): límites, escalas, términos, decisiones y diferencias con el plan aprobado |
| [revisiones/](revisiones/) | Actas de revisión. La de F8 es [2026-10-11-sincronizacion.md](revisiones/2026-10-11-sincronizacion.md), con las propuestas para el repositorio original |
| [deuda.md](deuda.md) | Deuda técnica: lo que se sabe que falta, por qué no se hizo y dónde se haría |

## Cómo se trabaja

Las reglas del proyecto (Definition of Done, autoría, commits, ramas, revisión y acta) están en [CONTRIBUTING.md](../../CONTRIBUTING.md), y cómo compilar, probar y publicar, en el [manual técnico](../manual/tecnico.md). En esta carpeta se añaden dos cosas propias de la localización:

1. **Primero la especificación.** Cada cambio del código responde a un requisito (`R-FUE`, `R-TXT`, `R-MC`, `R-TEX`, `R-PORT`, `R-INF`, `R-GOB`). Si cambia un requisito, un límite, una escala o un término, primero se registra en [cambios.md](cambios.md) y se aprueba. Después se toca el código.
2. **Trazabilidad.** Los identificadores de requisito aparecen en los commits y en esta carpeta, nunca en el código ([trazabilidad.md](trazabilidad.md)).

## Ramas

F8 se trabajó en `feature/sincronizacion-upstream`, que nace de `main` (`3f43c005`), con una subrama por bloque integrada con `git merge --no-ff`. El esquema de las subramas, de dónde sale cada una y su merge están en [plan.md §3.2](plan.md#32-f8).

Las ramas de F0 a F7 (`docs/readme-y-especificacion`, `idioma/infra`, `idioma/fuente`, `idioma/texturas`, `idioma/cadenas`, `idioma/port` y `feature/idioma-espanol`) ya están en `main`; su esquema está en [plan.md §3.1](plan.md#31-f0-a-f7-histórico).

## Comandos propios de la localización

El resto de objetivos y variables de `make` están en el [manual técnico](../manual/tecnico.md).

| Comando | Uso |
|---|---|
| `make es` / `make hoja-es` | Texturas en español en `build/ps2/es/` / hojas de contacto en `build/ps2/es/hojas/`, sin el SDK |
| `python3 herramientas/comparar_preprocesado.py <antes> <después> <fuente.c>…` | Comprueba en el PC, sin SDK, que un refactor no cambia lo que ve el compilador |
| `sh herramientas/comparar_binario.sh <base> [DEBUG=1]` | Compara el ELF y la ROM con los de una base. Necesita el SDK (en la CI, job `mismo-binario`) |

## Verificación de F8

Comprobado el 2026-10-11 sobre `feature/sincronizacion-upstream` en `d5f95cc5`.

- **Especificación → trazabilidad.** `especificacion.md` define 46 requisitos (`R-FUE` 8, `R-TXT` 8, `R-MC` 3, `R-TEX` 8, `R-PORT` 5, `R-INF` 6, `R-GOB` 8). Los 46 tienen fila en [trazabilidad.md](trazabilidad.md) y la lista coincide. Estado: 38 hechos (6 aceptados por CC-12 sin captura y 3 con una salvedad registrada en [deuda.md](deuda.md)) y 8 parciales (R-TEX-02, R-PORT-03, R-GOB-01, R-GOB-02, R-GOB-03, R-GOB-04, R-GOB-06 y R-GOB-08). Comprobación:

  ```sh
  diff <(grep -oE '^\*\*R-[A-Z]+-[0-9]+' especificacion.md | tr -d '*' | sort) \
       <(grep -oE '^\| R-[A-Z]+-[0-9]+' trazabilidad.md | tr -d '| ' | sort)
  ```

- **Pruebas.** `make test` terminó con 0 fallos en el worktree de revisión de cada rama integrada ([acta](revisiones/2026-10-11-sincronizacion.md)).
- **Gobernanza.** Sobre `origin/main..feature/sincronizacion-upstream`: el comando de R-GOB-01 solo devuelve `c2ed147` y `ae93f71`, del original; ningún commit toca `build/` ni `compilaciones/`; no hay trailers; el grep de R-GOB-07 sale vacío.
- **CI de F8:** ejecución y commit de publicación en [trazabilidad.md](trazabilidad.md#evidencia-común).
- **Definition of Done:** la de [CONTRIBUTING.md](../../CONTRIBUTING.md), que se cierra con la publicación y la fusión a `main` ([Pendiente](#pendiente)).
