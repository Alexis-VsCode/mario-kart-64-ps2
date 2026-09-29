# Traducción al español

Esta carpeta documenta el trabajo con el que todo lo que ve el jugador en el port de Mario Kart 64 a PS2 sale en español:

- cadenas de menú y mensajes;
- créditos;
- texturas con texto: menús, títulos de pista, HUD y carteles de Lakitu;
- pantallas propias del port: panel de rendimiento, página de audio, pantalla de fallo y registro.

Los nombres de carpetas, funciones, variables y comentarios del código ya están en español. Aquí solo se trata el texto que sale en pantalla.

## Estado (2026-09-29)

La localización está hecha e integrada en `feature/idioma-espanol`. Cada fase se hizo en su rama, ya fusionada; las ramas de trabajo se borran tras la fusión a `main`.

| Fase | Contenido | Rama (ya fusionada) | Estado |
|---|---|---|---|
| F0 | Esta documentación y el README principal | `docs/readme-y-especificacion` | Hecha: `c86f72c`…`cbc10e8`. Es la base de `feature/idioma-espanol` |
| F1 | `make test` sin SDK, conversor EUC-JP, metadatos convertidos, `-fsigned-char`, tope de líneas y CI | `idioma/infra` | Hecha: 9 commits, de `f8f9a39` a `476dd52`. Integrada en `3d482a8` |
| F2 | Refactor de la fuente del menú sin cambio de comportamiento | `idioma/fuente` | Hecha: `418ea18`, `1c9545d` y `d87d14f`. Integrada en `6a050d1` |
| F3 | Tabla de glifos completa, caracteres del español, glifos nuevos y tope del pool de matrices | `idioma/fuente` | Hecha: de `4e35120` a `641fe27`. Falta el registro DEV de R-FUE-05 |
| F4 | Texturas (manifiesto, cableado y arte) | `idioma/texturas` | Hecha: de `1ee6041` a `44cc3fb`. Integrada en `d3663fd` |
| F4 | Cadenas, créditos y nombres de pista | `idioma/cadenas` | Hecha: de `15136d3` a `a54c0d4`. Integrada en `b043668` |
| F4 | Pantallas del port y registro | `idioma/port` | Hecha: de `3db4b80` a `ba66cf9`. Integrada en `2ae3d3a` |
| F5 | Revisión técnica y lingüística | — | Sin registro en el repositorio (ver [Pendiente](#pendiente)) |
| F6 | Recorrido en PCSX2 y captura en TV | — | Pendiente. El guion está hecho: `herramientas/guiones/recorrido_textos.txt` (`466e73f`) |
| F7 | Integración y publicación | `feature/idioma-espanol` | Hecha: merges, `0ff568e`, job `publicar` (`c461c5b`) y compilación versionada `dda9a5f`, generada por la CI [36518116212](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/36518116212). Queda la fusión a `main` |

El detalle por requisito y por commit está en [trazabilidad.md](trazabilidad.md).

## Pendiente

Lo que sigue sin hacer en `dda9a5f`, con su motivo:

1. **Recorrido en PCSX2 (F6).** Lo hace el usuario: `make DEV=1` (o el ELF versionado `build/ps2/dev/SLUS_999.99`), copiar `herramientas/guiones/recorrido_textos.txt` como `smk64_input.txt` en la carpeta `host:` y sacar a mano las capturas en cada `nota`. El guion no cubre datos y récords, contrarreloj, VS y batalla (VTA. con 3 y 4 jugadores), el cartel ¡REVÉS!, Memory Card, ceremonia ni créditos; tampoco el panel (`make DEBUG=1`), la página de audio (`make DEBUG=1 DEBUG_AUDIO=1`) ni la parada de diagnóstico. Pasos en [plan.md §9.4](plan.md#94-en-pcsx2). De él dependen R-FUE-07, R-TXT-07, R-MC-03, R-TEX-05, R-PORT-02 y R-PORT-03.
2. **Captura en TV** o en hardware real, para el sobrebarrido ([plan.md §9.5](plan.md#95-en-tv)). El port no se ha probado en una PS2 real.
3. **Registro DEV de R-FUE-05.** No está en el código: el único registro DEV de `imprimir_texto1` avisa de un índice fuera de la tabla, no de una secuencia inválida (-2) ni de un byte `C2`/`C3`.
4. **Cobertura de pruebas que falta:**
   - R-TEX-02: fuera de las 63 texturas TKMK00 y las 15 del Controller Pak, ninguna prueba exige que cada textura con texto tenga fila o exclusión de carpeta en el manifiesto;
   - R-TEX-07: que las texturas nombren los botones de PS2 se revisó en el manifiesto, sin comprobación automática;
   - R-TEX-03: el crecimiento de la ROM (6 144 B) se midió a mano;
   - R-TEX-08: la prueba revisa las reglas del sello en el `Makefile`, no un build incremental real;
   - R-FUE-07: el tope del pool de matrices (`dcc0914`) no tiene prueba en el PC ni rojo demostrado.
5. **Puerta G-FALLO.** No se hizo: la pantalla de fallo translitera siempre (sin tildes); el registro las conserva.
6. **Registro de la revisión (F5).** No hay en el repositorio registro de la revisión por un rol distinto del autor (R-GOB-04, R-GOB-06) ni de la aprobación de CC-01 a CC-07; las mutaciones restauradas solo están registradas en parte (R-GOB-03).
7. **Confirmación del cierre** por el responsable del proyecto (punto 5 de la definición de terminado) y fusión a `main`.

Desviación registrada que no se corrige: cuatro commits de tipo `chore` (R-GOB-01, [CC-06](cambios.md)).

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
| [plan.md](plan.md) | Cómo se hizo: fases F0–F7 con su estado final, roles y archivos, ramas, puertas de calidad, ciclo por bloque, definición de terminado y verificación |
| [glosario.md](glosario.md) | Términos aprobados y su fuente |
| [trazabilidad.md](trazabilidad.md) | Relación entre requisito, prueba, commits y evidencia, con el estado final de cada requisito |
| [cambios.md](cambios.md) | Registro de cambios de la especificación: límites, escalas, interlineado, términos y diferencias con el plan aprobado |

## Cómo se trabaja

1. **Primero la especificación.** Cada cambio del código responde a un requisito (`R-FUE`, `R-TXT`, `R-MC`, `R-TEX`, `R-PORT`, `R-INF`, `R-GOB`). Si cambia un requisito, un límite, una escala o un término, primero se registra en [cambios.md](cambios.md) y se aprueba. Después se toca el código.
2. **Primero la prueba.**
   - La prueba nueva falla antes del cambio (rojo). Va en un commit propio o en el mismo commit que el cambio. En los dos casos, la salida del rojo se adjunta al PR.
   - El cambio la hace pasar (verde).
   - Una mutación de la implementación la vuelve a poner en rojo y después se restaura.
   - Se revisa y se integra.
3. **Roles.** FUENTE, CADENAS, TEXTURAS, PORT, PRUEBAS, REVISIÓN e INTEGRACIÓN. Nadie revisa un bloque que escribió.
4. **Ramas.** Una rama por cambio, que se borra después de integrarla. La historia de las ramas de la traducción está en el esquema de abajo y en [plan.md §3](plan.md#3-ramas).
5. **Trazabilidad.** Los identificadores de requisito aparecen en los commits y en esta carpeta, nunca en el código.

## Ramas

Así se trabajó; todas estas ramas ya están fusionadas.

```
origin/main (0e7b7d5)
 ├─ docs/readme-y-especificacion    F0: esta carpeta y el README principal
 │   └─ feature/idioma-espanol       integración
 └─ idioma/infra                     F1
     ├─ idioma/fuente                F2 y F3
     │   ├─ idioma/cadenas           F4 (CADENAS)
     │   └─ idioma/port              F4 (PORT)
     └─ idioma/texturas              F4 (TEXTURAS); incorpora el resto de infra con el merge 236962b
```

La integración se hizo en `feature/idioma-espanol`, con `git merge --no-ff`, en este orden: `idioma/infra` (`3d482a8`) → `idioma/fuente` (`6a050d1`) → `idioma/texturas` (`d3663fd`) → `idioma/cadenas` (`b043668`) → `idioma/port` (`2ae3d3a`).

## Comandos de referencia

| Comando | Uso |
|---|---|
| `. herramientas/entorno.sh` | Carga el entorno del SDK de PS2 |
| `make` | Compila el ELF (`build/ps2/SLUS_999.99`) y `build/ps2/SMK64ROM.BIN` |
| `make test` | Pruebas en el PC, sin el SDK. Después: `git clean -fdq -- build && git checkout -- build` |
| `make herramientas` | Herramientas del PC: `mio0`, `empaquetador_listas` y `tkmk00`, sin el SDK |
| `make es` / `make hoja-es` | Texturas en español en `build/ps2/es/` / hojas de contacto en `build/ps2/es/hojas/`, sin el SDK |
| `make DEBUG=1` | Panel de rendimiento (L3 + R3) y registro |
| `make DEBUG=1 DEBUG_AUDIO=1` | Página de audio en el panel |
| `make DEV=1` | Guiones de prueba por `host:` (emuladores); el de recorrido es `herramientas/guiones/recorrido_textos.txt` |
| `make iso` | ISO en `compilaciones/` |
| `python3 herramientas/comparar_preprocesado.py <antes> <después> <fuente.c>…` | Comprueba en el PC, sin SDK, que un refactor no cambia lo que ve el compilador |
| `sh herramientas/comparar_binario.sh <base> [DEBUG=1]` | Compara el ELF y la ROM con los de una base. Necesita el SDK (en la CI, job `mismo-binario`) |
| `git status --short` | Tiene que salir vacío al cerrar cada bloque |

## Reglas generales

Se aplican las reglas de la sección «Contribuir» del [README principal](../../README.md):

- nombres en español y `snake_case`;
- archivos de código de 1000 líneas como máximo;
- `make clean && make` y `make test` antes de enviar un cambio.

## Verificación de cierre

Comprobado el 2026-09-29 sobre `feature/idioma-espanol` (código de `dda9a5f`).

- **Especificación → trazabilidad.** `especificacion.md` define 46 requisitos (`R-FUE` 8, `R-TXT` 8, `R-MC` 3, `R-TEX` 8, `R-PORT` 5, `R-INF` 6, `R-GOB` 8). Los 46 tienen fila en [trazabilidad.md](trazabilidad.md), la lista coincide sin sobrantes ni faltantes y todos tienen prueba asignada. Estado: 33 hechos (5 con una salvedad anotada), 11 parciales y 2 pendientes (R-GOB-04 y R-GOB-06, por falta de registro de revisión). Comprobación:

  ```sh
  diff <(grep -oE '^\*\*R-[A-Z]+-[0-9]+' especificacion.md | tr -d '*' | sort) \
       <(grep -oE '^\| R-[A-Z]+-[0-9]+' trazabilidad.md | tr -d '| ' | sort)
  ```

- **Pruebas.** `env -u PS2SDK make test` termina con 0: 26 pruebas (8 en C y 18 en Python) y el comprobador del tope de líneas, 0 fallos; `prueba_textos` informa 0 tablas pendientes. Con `PYTHON=python3.8`, las copias de `build/ps2/jp` y `build/ps2/es` y la tabla de caminos salen idénticas a las versionadas.
- **CI.** La ejecución [36518116212](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/36518116212) del workflow `compilacion`, sobre `c461c5b`, terminó en verde: `pruebas-pc`; `compilar-ps2` (release, `DEBUG=1`, `make test` e ISO); y `publicar` (release, `DEBUG=1`, `DEV=1`, `make test` e ISO), que generó `dda9a5f`. `mismo-binario` no corrió porque no se pidió una base.
- **Definición de terminado** (README principal):
  1. Compila: `make clean && make` en la CI (jobs `compilar-ps2` y `publicar`). No se compiló para PS2 en esta máquina, que no tiene el SDK.
  2. `make test` pasa, sin regresiones: sí, en el PC y en la CI.
  3. Documentación sincronizada: README y `docs/traduccion/` describen el estado de `dda9a5f`.
  4. Árbol limpio: `git status --short` vacío después de `git clean -fdq -- build && git checkout -- build`.
  5. Confirmación del responsable del proyecto: pendiente.
- **Pendientes del usuario:** el recorrido en PCSX2 con `herramientas/guiones/recorrido_textos.txt` y las pantallas que el guion no cubre, la captura en TV y la confirmación del cierre (puntos 1, 2 y 7 de [Pendiente](#pendiente)).
