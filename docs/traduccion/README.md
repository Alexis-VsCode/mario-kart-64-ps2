# Traducción al español

Esta carpeta documenta el trabajo con el que todo lo que ve el jugador en el port de Mario Kart 64 a PS2 sale en español:

- cadenas de menú y mensajes;
- créditos;
- texturas con texto: menús, títulos de pista, HUD y carteles de Lakitu;
- pantallas propias del port: panel de rendimiento, página de audio, pantalla de fallo y registro.

Los nombres de carpetas, funciones, variables y comentarios del código ya están en español. Aquí solo se trata el texto que sale en pantalla.

## Estado de F9 (2026-10-11)

La localización (F0 a F7) y la sincronización con el original (F8) están cerradas y en `main` (`af3bfa05`): la versión 1.0.0, publicada en `900c9be3`. F9, la versión 1.1.0, está integrada en `feature/version-1.1.0` (`a29bd920`), que nace de `af3bfa05`. `BUILD_ID` sigue en 2026-10-11, la fecha de la versión.

Hecho en F9:

- **Memory Card** ([CC-13](cambios.md)): al insertar o cambiar la tarjeta ya no se pisa la copia más nueva; la espera de la partida al arrancar se mide con el reloj; el segundo borrado solo se hace con `mc_ok` (D-12); los resultados de `mcGetInfo` salen de la pila (D-13). D-11 se mantiene, con la decisión escrita en CC-13.
- **Stick** ([CC-14](cambios.md)): la zona muerta del port baja de 24 a 8 y el giro empieza a 28 de 127 (22 %, antes 32 %). La cruceta conserva su reposo hasta 25 del centro (`ZONA_REPOSO_CRUCETA` 26).
- **Región** ([CC-15](cambios.md)): el arranque lee `rom0:ROMVER` y, en una consola PAL, registra que la imagen sale en NTSC a 60 Hz y que hace falta una TV que lo acepte. El modo de vídeo no cambia.
- **Publicación** ([CC-16](cambios.md)): `publicar` ya no oculta un fallo del commit; `release` corre en el contenedor de ps2dev, comprueba que el SHA-256 de la ISO esté en las notas y adjunta `SLUS_999.99.monolitico.elf` con su línea en `SHA256SUMS`.
- **Alfa con tramado** ([CC-17](cambios.md)): pasa a una función pura con prueba; salda D-01 y D-02.
- **Deudas chicas:** D-09, D-10, D-14 y D-15, y el registro del ritmo de física dice «ritmo» en lugar de «3-4P».
- **Pruebas:** `make test` pasa a 31 pruebas, con `prueba_eleccion_guardado`, `prueba_eje_palanca` y `prueba_region_ps2`.
- **Revisión** técnica y lingüística de cada rama, registrada en el [acta de F9](revisiones/2026-10-11-version-1.1.0.md).

Sin verificar en consola real: el tacto del stick, la lectura de ROMVER por las dos rutas del IOP (reiniciado y bajo OPL) y el cambio de tarjeta en caliente ([deuda.md](deuda.md): D-06, D-16 y D-17).

| Fase | Contenido | Estado |
|---|---|---|
| F0–F5, F7 | Documentación, infraestructura, fuente, cadenas, texturas, pantallas del port, revisión e integración de la localización | Cerradas (histórico), en `main`. Detalle en [plan.md §4](plan.md#4-fases) |
| F6 | Recorrido en PCSX2 y captura en TV | Retirada por CC-12 |
| F8 | Sincronización con el original, CI, correcciones y documentación | Cerrada: versión 1.0.0, en `main` (`af3bfa05`). [Acta](revisiones/2026-10-11-sincronizacion.md) |
| F9 | Versión 1.1.0: CC-13 a CC-17 y deudas chicas | Integrada en `feature/version-1.1.0`. Falta lo de [Pendiente](#pendiente) |

El detalle por requisito y por commit está en [trazabilidad.md](trazabilidad.md); la deuda técnica, en [deuda.md](deuda.md).

## Pendiente

1. **Documentación de F9:** integrar `v110/doc-manual` (manual de usuario con el aviso de los 60 Hz y `sha256sum -c --ignore-missing`, notas de la versión y `CHANGELOG.md`) y `v110/doc-traduccion` en `feature/version-1.1.0`.
2. **Publicación:** job `publicar` sobre `feature/version-1.1.0`. El commit de publicación, la ejecución y las sumas quedan en [trazabilidad.md](trazabilidad.md#evidencia-común).
3. **Fusión a `main`** de `feature/version-1.1.0`.
4. **Release v1.1.0:** job `release` sobre `main`, con la ISO versionada, el ELF monolítico y las notas de `docs/versiones/v1.1.0.md`, que tienen que llevar el SHA-256 de la ISO o el job falla ([CC-16](cambios.md)).
5. **Limpieza de ramas:** job `limpiar-ramas` sobre `main`. Al final, `git ls-remote --heads origin` lista solo `main` ([CC-09](cambios.md)).

## Próximo paso

Integrar la documentación de F9 y lanzar `publicar`; después, fusionar a `main` y lanzar `release` y `limpiar-ramas`, en ese orden (ver el [manual técnico](../manual/tecnico.md)). El código de F9 ya está integrado y revisado, y `make test` termina con 0 en `a29bd920`.

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
| [plan.md](plan.md) | Cómo se hizo: fases F0–F9 con su estado, roles y archivos, ramas, puertas de calidad, ciclo por bloque y verificación |
| [glosario.md](glosario.md) | Términos aprobados y su fuente |
| [trazabilidad.md](trazabilidad.md) | Relación entre requisito, prueba, commits y evidencia, con el estado de cada requisito y los commits de F8 y F9 |
| [cambios.md](cambios.md) | Registro de cambios de la especificación (CC-01 a CC-17): límites, escalas, términos, decisiones y diferencias con el plan aprobado |
| [revisiones/](revisiones/) | Actas de revisión: la de F8, [2026-10-11-sincronizacion.md](revisiones/2026-10-11-sincronizacion.md), con las propuestas para el repositorio original, y la de F9, [2026-10-11-version-1.1.0.md](revisiones/2026-10-11-version-1.1.0.md) |
| [deuda.md](deuda.md) | Deuda técnica: lo que se sabe que falta, por qué no se hizo y dónde se haría |

## Cómo se trabaja

Las reglas del proyecto (Definition of Done, autoría, commits, ramas, revisión y acta) están en [CONTRIBUTING.md](../../CONTRIBUTING.md), y cómo compilar, probar y publicar, en el [manual técnico](../manual/tecnico.md). En esta carpeta se añaden dos cosas propias de la localización:

1. **Primero la especificación.** Cada cambio del código responde a un requisito (`R-FUE`, `R-TXT`, `R-MC`, `R-TEX`, `R-PORT`, `R-INF`, `R-GOB`). Si cambia un requisito, un límite, una escala o un término, primero se registra en [cambios.md](cambios.md) y se aprueba. Después se toca el código.
2. **Trazabilidad.** Los identificadores de requisito aparecen en los commits y en esta carpeta, nunca en el código ([trazabilidad.md](trazabilidad.md)).

## Ramas

F9 se trabaja en `feature/version-1.1.0`, que nace de `main` (`af3bfa05`), con una rama `v110/*` por frente integrada con `git merge --no-ff`. El esquema de las ramas, de dónde sale cada una y su merge están en [plan.md §3.3](plan.md#33-f9).

F8 se trabajó en `feature/sincronizacion-upstream`, que nace de `main` (`3f43c005`), con una subrama por bloque; ya está en `main` y su esquema está en [plan.md §3.2](plan.md#32-f8).

Las ramas de F0 a F7 (`docs/readme-y-especificacion`, `idioma/infra`, `idioma/fuente`, `idioma/texturas`, `idioma/cadenas`, `idioma/port` y `feature/idioma-espanol`) ya están en `main`; su esquema está en [plan.md §3.1](plan.md#31-f0-a-f7-histórico).

## Comandos propios de la localización

El resto de objetivos y variables de `make` están en el [manual técnico](../manual/tecnico.md).

| Comando | Uso |
|---|---|
| `make es` / `make hoja-es` | Texturas en español en `build/ps2/es/` / hojas de contacto en `build/ps2/es/hojas/`, sin el SDK |
| `python3 herramientas/comparar_preprocesado.py <antes> <después> <fuente.c>…` | Comprueba en el PC, sin SDK, que un refactor no cambia lo que ve el compilador |
| `sh herramientas/comparar_binario.sh <base> [DEBUG=1]` | Compara el ELF y la ROM con los de una base. Necesita el SDK (en la CI, job `mismo-binario`) |

## Verificación de F9

Comprobado el 2026-10-11 sobre `feature/version-1.1.0` en `a29bd920`.

- **Especificación → trazabilidad.** Los 46 requisitos siguen teniendo fila en [trazabilidad.md](trazabilidad.md) y la lista coincide con el comando de la [verificación de F8](#verificación-de-f8). Estado: 38 hechos y 8 parciales (R-TEX-02, R-PORT-03, R-GOB-01, R-GOB-02, R-GOB-03, R-GOB-04, R-GOB-06 y R-GOB-08). R-GOB-08 sigue parcial hasta integrar `v110/doc-manual` y `v110/doc-traduccion`, como en F8; R-GOB-01 suma `b780d986`, de tipo `style`.
- **Pruebas.** `env -u PS2SDK make test` termina con 0: 31 pruebas y el tope de líneas, 0 fallos.
- **Gobernanza.** Sobre `origin/main..feature/version-1.1.0`: 38 commits, todos de Alexis Barrera; el comando de R-GOB-01 solo devuelve `b780d986`; ningún commit toca `build/` ni `compilaciones/`; no hay trailers; el grep de R-GOB-07 sale vacío.
- **CI de F9:** ejecución, commit de publicación y sumas en [trazabilidad.md](trazabilidad.md#evidencia-común).

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
- **Definition of Done:** la de [CONTRIBUTING.md](../../CONTRIBUTING.md), que se cerró con la publicación (`900c9be3`) y la fusión a `main` (`af3bfa05`).
