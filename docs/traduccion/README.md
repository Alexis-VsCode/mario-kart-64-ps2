# Traducción al español

Esta carpeta documenta el trabajo para que todo lo que ve el jugador en el port de Mario Kart 64 a PS2 salga en español:

- cadenas de menú y mensajes;
- créditos;
- texturas con texto: menús, títulos de pista, HUD y carteles de Lakitu;
- pantallas propias del port: panel de rendimiento, página de audio, pantalla de fallo y registro.

Los nombres de carpetas, funciones, variables y comentarios del código ya están en español. Aquí solo se trata el texto que sale en pantalla.

## Estado (2026-09-28)

| Fase | Contenido | Rama | Estado |
|---|---|---|---|
| F0 | Esta documentación y el README principal | `docs/readme-y-especificacion` | En revisión |
| F1 | `make test` sin SDK, conversor EUC-JP, metadatos convertidos, `-fsigned-char`, tope de líneas y CI | `idioma/infra` | Hecha: 8 commits, de `f8f9a39` a `a3d0bae`. CI en verde |
| F2 | Refactor de la fuente del menú sin cambio de comportamiento | `idioma/fuente` | Hecha: `418ea18`, `1c9545d` y `d87d14f` |
| F3 | Tabla de glifos completa, caracteres del español, glifos nuevos y tope del pool de matrices | `idioma/fuente` | Base hecha, de `4e35120` a `641fe27`. CI en verde. Falta el registro DEV de R-FUE-05 y el recorrido en PCSX2 |
| F4 | Cadenas, texturas y pantallas del port | `idioma/cadenas`, `idioma/texturas`, `idioma/port` | TEXTURAS: herramientas, cargador por firma y manifiesto hechos (de `1ee6041` a `4345598`); el arte está en curso. CADENAS y PORT: en curso, sin publicar |
| F5–F7 | Revisión, recorrido en PCSX2 e integración | `feature/idioma-espanol` | Pendientes |

El detalle por requisito y por commit está en [trazabilidad.md](trazabilidad.md).

## Punto de partida (verificado en `main`, `0e7b7d5`)

- **Fuente del menú.** No tiene Ñ, tildes, Ü, ¡, ¿, º ni ª (`car_a_indice_glifo` en `codigo/menus/elementos_menu/animaciones_personajes.inc.c`).
- **Tabla de glifos incompleta.** `lut_textura_glifo` tiene 91 entradas y `ancho_pantalla_glifo` tiene 236 (`codigo/menus/elementos_menu/textos_y_tablas.inc.c:777` y `:244`). En la N64, el resto de la tabla eran arreglos que el enlazador colocaba a continuación. En PS2, los índices a partir del 91 leen fuera de la tabla.
- **Texturas de menú.** Las texturas con texto son TKMK00 (`recursos/texturas/menus/tkmk00/`, 63 archivos). El repositorio solo trae el decodificador.
- **Mensajes de guardado.** Hablan del «N64 CONTROLLER PAK» (`textos_y_tablas.inc.c:428-561`).
- **Compilación.** `make test` exige `PS2SDK` (`Makefile:11-13`) y la conversión a EUC-JP depende de `iconv` (`Makefile:255-261`). Las dos cosas cambian en `idioma/infra`.

## Documentos

| Documento | Contenido |
|---|---|
| [especificacion.md](especificacion.md) | Qué hay que cumplir: alcance, exclusiones, requisitos numerados con criterio de aceptación y prueba, decisiones cerradas y riesgos |
| [plan.md](plan.md) | Cómo se hace: fases F0–F7 con su estado, roles y archivos, ramas, puertas de calidad, ciclo por bloque, definición de terminado y verificación |
| [glosario.md](glosario.md) | Términos aprobados y su fuente |
| [trazabilidad.md](trazabilidad.md) | Relación entre requisito, prueba, commits y evidencia, con los hashes de lo ya publicado |
| [cambios.md](cambios.md) | Registro de cambios de la especificación: límites, escalas, interlineado, términos y diferencias con el plan aprobado |

## Cómo se trabaja

1. **Primero la especificación.** Cada cambio del código responde a un requisito (`R-FUE`, `R-TXT`, `R-MC`, `R-TEX`, `R-PORT`, `R-INF`, `R-GOB`). Si cambia un requisito, un límite, una escala o un término, primero se registra en [cambios.md](cambios.md) y se aprueba. Después se toca el código.
2. **Primero la prueba.**
   - La prueba nueva falla antes del cambio (rojo). Va en un commit propio o en el mismo commit que el cambio. En los dos casos, la salida del rojo se adjunta al PR.
   - El cambio la hace pasar (verde).
   - Una mutación de la implementación la vuelve a poner en rojo y después se restaura.
   - Se revisa y se integra.
3. **Roles.** FUENTE, CADENAS, TEXTURAS, PORT, PRUEBAS, REVISIÓN e INTEGRACIÓN. Nadie revisa un bloque que escribió.
4. **Ramas.** Ver el esquema de abajo y [plan.md §3](plan.md#3-ramas).
5. **Trazabilidad.** Los identificadores de requisito aparecen en los commits y en esta carpeta, nunca en el código.

## Ramas

```
origin/main (0e7b7d5)
 ├─ docs/readme-y-especificacion    F0: esta carpeta y el README principal
 └─ idioma/infra                     F1
     ├─ idioma/fuente                F2 y F3
     │   ├─ idioma/cadenas           F4 (CADENAS)
     │   └─ idioma/port              F4 (PORT)
     └─ idioma/texturas              F4 (TEXTURAS); incorpora el resto de infra con el merge 236962b
```

La integración se hace en `feature/idioma-espanol`, con `git merge --no-ff`, en este orden: `idioma/infra` → `idioma/fuente` → `idioma/texturas` → `idioma/cadenas` → `idioma/port`.

## Comandos de referencia

| Comando | Uso |
|---|---|
| `. herramientas/entorno.sh` | Carga el entorno del SDK de PS2 |
| `make` | Compila el ELF (`build/ps2/SLUS_999.99`) y `build/ps2/SMK64ROM.BIN` |
| `make test` | Pruebas en el PC. Desde `idioma/infra` no necesita el SDK |
| `make herramientas` | Herramientas del PC: `mio0`, `empaquetador_listas` y, desde `idioma/texturas`, `tkmk00`. Desde `idioma/infra` no necesita el SDK |
| `make DEBUG=1` | Panel de rendimiento (L3 + R3) y registro |
| `make DEBUG=1 DEBUG_AUDIO=1` | Página de audio en el panel |
| `make DEV=1` | Guiones de prueba por `host:` (emuladores) |
| `make iso` | ISO en `compilaciones/` |
| `python3 herramientas/comparar_preprocesado.py <antes> <después> <fuente.c>…` | Comprueba en el PC, sin SDK, que un refactor no cambia lo que ve el compilador (desde `idioma/fuente`) |
| `sh herramientas/comparar_binario.sh <base> [DEBUG=1]` | Compara el ELF y la ROM con los de una base. Necesita el SDK (desde `idioma/infra`; en la CI, job `mismo-binario`) |
| `git status --short` | Tiene que salir vacío al cerrar cada bloque |

## Reglas generales

Se aplican las reglas de la sección «Contribuir» del [README principal](../../README.md):

- nombres en español y `snake_case`;
- archivos de código de 1000 líneas como máximo;
- `make clean && make` y `make test` antes de enviar un cambio.
