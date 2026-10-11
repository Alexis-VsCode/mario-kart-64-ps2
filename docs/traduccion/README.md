# Traducción al español

Esta carpeta documenta el trabajo con el que todo lo que ve el jugador en el port de Mario Kart 64 a PS2 sale en español:

- cadenas de menú y mensajes;
- créditos;
- texturas con texto: menús, títulos de pista, HUD y carteles de Lakitu;
- pantallas propias del port: panel de rendimiento, página de audio, pantalla de fallo y registro.

Los nombres de carpetas, funciones, variables y comentarios del código ya están en español. Aquí solo se trata el texto que sale en pantalla.

## Estado de F10 (2026-10-11)

La localización (F0 a F7), la sincronización con el original (F8, versión 1.0.0) y la versión 1.1.0 (F9, publicada en `45bbe10a`) están cerradas y en `main`. F10, la versión 1.2.0, está integrada en `feature/version-1.2.0` (`fd6a4bb7`), con el PR en borrador [#5](https://github.com/Alexis-VsCode/mario-kart-64-ps2/pull/5). `BUILD_ID` sigue en 2026-10-11, la fecha de la versión.

Hecho en F10:

- **Opciones del port** ([CC-18](cambios.md)): `SMK64CFG.DAT`, un archivo aparte en la Memory Card, guarda las opciones de imagen y los trucos sin tocar la partida.
- **Menú CONFIGURACIÓN Y TRUCOS** ([CC-19](cambios.md)): quinta entrada de OPCIONES, con el estilo de los menús del juego. Filas: ANTIPARPADEO, POSICIÓN X, POSICIÓN Y, FORMATO (NORMAL, CON BANDAS o PANORÁMICO), DESBLOQUEAR TODO, OBJETO, 200CC, RIVALES SIN VENTAJA y VOLVER.
- **Imagen** ([CC-20](cambios.md) y [CC-21](cambios.md)): antiparpadeo opcional, apagado por defecto; posición de la imagen; CON BANDAS por defecto si la PS2 está en 16:9, y vista PANORÁMICA.
- **Trucos** ([CC-22](cambios.md) a [CC-25](cambios.md)): los récords se guardan aunque haya trucos activos, y el manual lo advierte. 200CC solo aplica en GP y VS a 150cc y puntúa como 150cc. Un objeto que no vale en batalla da la ruleta normal. DESBLOQUEAR TODO se aplica al cambiar de pantalla.
- **Emulador en la CI** ([CC-26](cambios.md)): el job «Guion en el emulador (Play!)» arranca dos veces el ELF de DEV en Play! 0.72 sin BIOS. Comprueba el registro (región PAL con un ROMVER sintético y «vídeo: PMODE 8046») y compara las capturas de título, menú y carrera con sus referencias y entre sí.
- **Deuda** ([CC-27](cambios.md)): saldadas D-03 a D-08, D-16 a D-22 y D-24. Queda D-23, y D-25 apareció al documentar ([deuda.md](deuda.md)).
- **Texturas** ([CC-28](cambios.md) y [CC-29](cambios.md)): reconstruidas (el «º» de los puestos, VUELTA, botones y copas, el título de la Jungla DK) y traducidas (BIENVENIDOS, YA, 1J a 4J y PASO A NIVEL). El manifiesto clasifica 1229 texturas.
- **Pruebas:** `make test` suma las pruebas de opciones, Memory Card, registros de vídeo, vista panorámica, menú, trucos, reserva de matrices y herramientas de la CI. CI en verde: [38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616).
- **Revisión** técnica y lingüística de cada rama, registrada en el [acta de F10](revisiones/2026-10-11-version-1.2.0.md).
- **Portafolio** ([CC-30](cambios.md), aprobado): aviso legal reforzado, autoría, caso de estudio, página web y licencia MIT de los aportes.

Lo que no se puede comprobar sin hardware real ni TV está en los [límites declarados](especificacion.md#9-límites-declarados): el tacto; el antiparpadeo, las bandas y la posición, comprobados solo por valores de registro; el multitap; el cambio de tarjeta en caliente; el rendimiento en PANORÁMICO, y la lectura de ROMVER fuera de la ruta con reinicio del IOP. En PANORÁMICO, los objetos o la pista pueden aparecer tarde en los bordes, y el marcador sale estirado.

| Fase | Contenido | Estado |
|---|---|---|
| F0–F5, F7 | Documentación, infraestructura, fuente, cadenas, texturas, pantallas del port, revisión e integración de la localización | Cerradas (histórico), en `main`. Detalle en [plan.md §4](plan.md#4-fases) |
| F6 | Recorrido en PCSX2 y captura en TV | Retirada por CC-12 |
| F8 | Sincronización con el original, CI, correcciones y documentación | Cerrada: versión 1.0.0, en `main` (`af3bfa05`). [Acta](revisiones/2026-10-11-sincronizacion.md) |
| F9 | Versión 1.1.0: CC-13 a CC-17 y deudas chicas | Cerrada: publicada en `45bbe10a`, en `main`. [Acta](revisiones/2026-10-11-version-1.1.0.md) |
| F10 | Versión 1.2.0: CC-18 a CC-30, deuda técnica, menú de configuración y trucos, emulador en la CI | Integrada en `fd6a4bb7`. Falta lo de [Pendiente](#pendiente). [Acta](revisiones/2026-10-11-version-1.2.0.md) |

El detalle por requisito y por commit está en [trazabilidad.md](trazabilidad.md); la deuda técnica, en [deuda.md](deuda.md).

## Pendiente

1. **Documentación de F10:** integrar `v120/doc-traduccion` y las demás ramas de documentación, entre ellas las de CC-30.
2. **Publicación:** job `publicar` sobre `feature/version-1.2.0`; commit, tamaño y SHA-256 de la ISO: <<PUBLICACION>>.
3. **Fusión a `main`** de `feature/version-1.2.0`, con el PR #5 como registro.
4. **Release v1.2.0:** job `release` sobre `main`, con la ISO versionada, el ELF monolítico y las notas de la versión, que llevan el SHA-256 de la ISO ([CC-16](cambios.md)).
5. **Limpieza de ramas:** job `limpiar-ramas` sobre `main` ([CC-09](cambios.md)).

## Próximo paso

Integrar la documentación de F10 y lanzar `publicar`, y después fusionar a `main` y lanzar `release` y `limpiar-ramas`, en ese orden (ver el [manual técnico](../manual/tecnico.md)).

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
| [plan.md](plan.md) | Cómo se hizo: fases F0–F10 con su estado, roles y archivos, ramas, puertas de calidad, ciclo por bloque y verificación |
| [glosario.md](glosario.md) | Términos aprobados y su fuente |
| [trazabilidad.md](trazabilidad.md) | Relación entre requisito, prueba, commits y evidencia, con el estado de cada requisito y los commits de F8, F9 y F10 |
| [cambios.md](cambios.md) | Registro de cambios de la especificación (CC-01 a CC-30): límites, escalas, términos, decisiones y diferencias con el plan aprobado |
| [revisiones/](revisiones/) | Actas de revisión: la de F8, [2026-10-11-sincronizacion.md](revisiones/2026-10-11-sincronizacion.md), con las propuestas para el repositorio original, la de F9, [2026-10-11-version-1.1.0.md](revisiones/2026-10-11-version-1.1.0.md), y la de F10, [2026-10-11-version-1.2.0.md](revisiones/2026-10-11-version-1.2.0.md) |
| [deuda.md](deuda.md) | Deuda técnica: lo que se sabe que falta, por qué no se hizo y dónde se haría. Lo que no se puede comprobar sin hardware está en los [límites declarados](especificacion.md#9-límites-declarados) |

## Cómo se trabaja

Las reglas del proyecto (Definition of Done, autoría, commits, ramas, revisión y acta) están en [CONTRIBUTING.md](../../CONTRIBUTING.md), y cómo compilar, probar y publicar, en el [manual técnico](../manual/tecnico.md). En esta carpeta se añaden dos cosas propias de la localización:

1. **Primero la especificación.** Cada cambio del código responde a un requisito (`R-FUE`, `R-TXT`, `R-MC`, `R-TEX`, `R-PORT`, `R-INF`, `R-GOB`, `R-VID`, `R-TRU`). Si cambia un requisito, un límite, una escala o un término, primero se registra en [cambios.md](cambios.md) y se aprueba. Después se toca el código.
2. **Trazabilidad.** Los identificadores de requisito aparecen en los commits y en esta carpeta, nunca en el código ([trazabilidad.md](trazabilidad.md)).

## Ramas

F10 se trabaja en `feature/version-1.2.0`, que nace de `main` (`fc17498f`), con una rama `v120/*` por frente integrada con `git merge --no-ff`. El esquema de las ramas, de dónde sale cada una y su merge están en [plan.md §3.4](plan.md#34-f10).

F9 se trabajó en `feature/version-1.1.0`, que nace de `main` (`af3bfa05`), con una rama `v110/*` por frente; ya está en `main` y su esquema está en [plan.md §3.3](plan.md#33-f9).

F8 se trabajó en `feature/sincronizacion-upstream`, que nace de `main` (`3f43c005`), con una subrama por bloque; ya está en `main` y su esquema está en [plan.md §3.2](plan.md#32-f8).

Las ramas de F0 a F7 (`docs/readme-y-especificacion`, `idioma/infra`, `idioma/fuente`, `idioma/texturas`, `idioma/cadenas`, `idioma/port` y `feature/idioma-espanol`) ya están en `main`; su esquema está en [plan.md §3.1](plan.md#31-f0-a-f7-histórico).

## Comandos propios de la localización

El resto de objetivos y variables de `make` están en el [manual técnico](../manual/tecnico.md).

| Comando | Uso |
|---|---|
| `make es` / `make hoja-es` | Texturas en español en `build/ps2/es/` / hojas de contacto en `build/ps2/es/hojas/`, sin el SDK |
| `python3 herramientas/comparar_preprocesado.py <antes> <después> <fuente.c>…` | Comprueba en el PC, sin SDK, que un refactor no cambia lo que ve el compilador |
| `sh herramientas/comparar_binario.sh <base> [DEBUG=1]` | Compara el ELF y la ROM con los de una base. Necesita el SDK (en la CI, job `mismo-binario`) |

## Verificación de F10

Comprobado el 2026-10-11 sobre `feature/version-1.2.0` en `fd6a4bb7`.

- **Especificación → trazabilidad.** `especificacion.md` define 58 requisitos (`R-FUE` 9, `R-TXT` 8, `R-MC` 4, `R-TEX` 8, `R-PORT` 5, `R-INF` 7, `R-GOB` 8, `R-VID` 5, `R-TRU` 4). Los 58 tienen fila en [trazabilidad.md](trazabilidad.md) y la lista coincide con el comando de la [verificación de F8](#verificación-de-f8). Estado: 51 hechos y 7 parciales (R-GOB-01, R-GOB-02, R-GOB-03, R-GOB-04, R-GOB-06, R-GOB-07 y R-GOB-08). R-TEX-02 y R-PORT-03 pasan a hechos; R-GOB-07 pasa a parcial por D-25, y R-GOB-08 sigue parcial hasta integrar la documentación, como en F8 y F9.
- **Pruebas.** `PS2SDK= make test` termina con 0: las 44 pruebas que imprimen su resumen dan 0 fallos y el tope de líneas, 0 archivos por encima.
- **Gobernanza.** Sobre `main..feature/version-1.2.0`: 113 commits (99 más 14 merges), todos de Alexis Barrera; el comando de R-GOB-01 sale vacío; ningún commit toca `build/` ni `compilaciones/`; no hay trailers; el grep de R-GOB-07 encuentra 8 líneas en 4 archivos de `herramientas/` (D-25).
- **CI de F10:** [38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616), en verde. La publicación: <<PUBLICACION>>.

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
