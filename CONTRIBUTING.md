# Cómo contribuir

Reglas de trabajo del repositorio: qué se lee antes de empezar, cómo se nombran las ramas y los commits, cómo se prueba, cómo se revisa y cuándo un cambio está terminado. Para jugar, ver el [manual de usuario](docs/manual/usuario.md); para compilar, probar y publicar, el [manual técnico](docs/manual/tecnico.md).

Este archivo es la única fuente de la [Definition of Done](#definition-of-done) ([CC-12](docs/traduccion/cambios.md)). Los demás documentos la enlazan y no la repiten.

## Lo que no se negocia

1. **Autoría real.** Cada commit lleva como autor a la persona que hizo el trabajo, con su identidad de git. Los créditos del proyecto están en [docs/manual/creditos.md](docs/manual/creditos.md) y no se cuentan commits por autor.
2. **Sin trailers.** Ningún mensaje de commit termina con líneas `Clave: valor` (`Co-Authored-By:`, `Signed-off-by:` ni otras). El cuerpo explica el cambio en prosa.
3. **Sin menciones a herramientas.** Los mensajes de commit, el código y los documentos hablan del cambio, no de las herramientas con las que se escribió.
4. **Commits con formato:** `tipo(dominio): descripción`, en español (ver [Commits](#commits)).
5. **Stage por ruta explícita:** `git add -- <ruta>…`. Nunca `git add -A`, `git add .` ni `git commit -a` (R-GOB-06).
6. **`build/` y `compilaciones/` solo cambian en el commit de publicación**, que hace el job `publicar` de la CI. Ningún commit de trabajo los toca (R-GOB-05).
7. **La historia publicada no se reescribe:** nada de `rebase`, `amend` ni `push --force` sobre commits ya subidos. Un error en un commit publicado se corrige con otro commit o se registra en [cambios.md](docs/traduccion/cambios.md), como se hizo en CC-06.
8. **No se moderniza de paso el código descompilado.** Un cambio no renombra, reordena ni reescribe código de la descompilación que no necesita para cumplir su requisito. Lo que se quiera mejorar va en su propio cambio, con su requisito.
9. **Integración a `main` solo con el visto bueno del responsable del proyecto.**

## Lectura previa

Antes de tocar nada:

1. `git status --short` (tiene que salir vacío) y `git log --oneline -10` de la rama de partida.
2. El [README](README.md) y este archivo.
3. El [manual técnico](docs/manual/tecnico.md): estructura, compilación, pruebas, archivos sensibles y errores a evitar.
4. En [`docs/traduccion/`](docs/traduccion/README.md): el estado y lo pendiente, los cambios abiertos de [cambios.md](docs/traduccion/cambios.md) y la [deuda técnica](docs/traduccion/deuda.md).
5. Si el cambio toca textos o texturas en pantalla, la [especificación](docs/traduccion/especificacion.md) y el [glosario](docs/traduccion/glosario.md).

## Orden de autoridad

Cuando dos fuentes no coinciden, manda la primera de esta lista:

1. **El código y las pruebas, medidos:** lo que hace el código y lo que comprueban `make test` y la CI, ejecutados, no recordados.
2. **La especificación aprobada:** [especificacion.md](docs/traduccion/especificacion.md) y los cambios aprobados de [cambios.md](docs/traduccion/cambios.md).
3. **Los demás documentos:** README, manuales, plan y trazabilidad.

Si un documento contradice el código, se corrige el documento. Si el código contradice la especificación aprobada, es un defecto, o un cambio que primero se registra y se aprueba en [cambios.md](docs/traduccion/cambios.md). Ante una duda de alcance, decide el responsable del proyecto.

## Ramas

- **Rama de integración:** `feature/<tema>`, creada desde el último `origin/main`. Por ejemplo, `feature/idioma-espanol` (F0–F7) y `feature/sincronizacion-upstream` (F8).
- **Subramas:** `<tema>/<parte>`, creadas desde la rama de integración, una por autor y por parte. `<tema>` es un prefijo corto y común a todas las subramas (en F8: `sinc/ci`, `sinc/sistema`, `sinc/panel`…). Cada una trabaja en su propio worktree (`git worktree add`) y solo toca sus archivos.
- Nombres en minúsculas, con guiones y sin tildes.
- Si una subrama necesita lo nuevo de su rama de integración, lo trae con un merge, no con un rebase.
- Solo INTEGRACIÓN integra, con `git merge --no-ff`, y solo después de la [revisión](#revisión).
- Las ramas ya contenidas en `main` se borran con el job `limpiar-ramas` ([manual técnico](docs/manual/tecnico.md#ci-y-publicación)).

Al crear una rama se comprueba de dónde nace; `merge-base` no sirve como prueba:

```sh
git reflog show <rama> | tail -1              # «branch: Created from <origen>»
git rev-list --count <origen>..<rama>         # 0: todavía sin commits propios
git rev-list --count <rama>..<origen>         # 0: no le falta nada del origen
git log --merges <origen>..<rama>             # vacío: sin merges inesperados
git log --format='%ae' origin/main..<rama> | sort -u   # solo los autores esperados
```

## Commits

- **Asunto:** `tipo(dominio): descripción`, en español con tildes. Tipos: `feat`, `fix`, `refactor`, `test`, `build`, `ci` y `docs`. El dominio es el área que se toca (`menus`, `sistema`, `fuente`, `make`, `manual`…). Los cambios de la CI pueden ir sin dominio (`ci: descripción`) y se aceptan los mensajes de merge por defecto (`Merge branch '…' into …`). `chore` no está admitido (R-GOB-01).
- **Una sola cosa por commit.** Un refactor no cambia el comportamiento y va solo (R-GOB-02), demostrado con el preprocesado idéntico (`herramientas/comparar_preprocesado.py`), el binario idéntico (job `mismo-binario`) o una prueba de caracterización.
- **Trasladar texto o código es un commit propio**, sin cambiar lo trasladado. Las correcciones van en commits aparte.
- **Cuerpo:** por qué se hace el cambio y su evidencia: la salida del rojo, la mutación y su restauración o, si no hay prueba posible en el PC, la evidencia de código (ver [Ciclo de un cambio](#ciclo-de-un-cambio)). Los identificadores de requisito (`R-…`) y de cambio (`CC-NN`) van en el mensaje, nunca en el código (R-GOB-07).
- **Comprobación**, que tiene que salir vacía:

  ```sh
  git log --format=%s origin/main..HEAD ^upstream/main \
    | grep -vE "^((feat|fix|refactor|test|build|ci|docs)\([a-z0-9_-]+\)|ci): |^Merge branch '"
  ```

  `upstream/main` es la rama principal del repositorio original, con el remoto configurado como explica el [manual técnico](docs/manual/tecnico.md#traer-actualizaciones-del-repositorio-original). Los commits del original que trae una fusión con él conservan su mensaje y no siguen este formato; `^upstream/main` los deja fuera (en F8, `c2ed147` y `ae93f71`, aceptados en CC-08).

## Reglas de código

- Nombres en español y en `snake_case`. Los tipos van en `PascalCase` y las constantes en `MAYUSCULAS`.
- La API de libultra, el SDK de PS2 y los símbolos del enlazador conservan sus nombres originales.
- Las funciones y los datos sin identificar se llaman `funcion_<dirección>` y `dato_<dirección>`, con la dirección original de la N64.
- Los comentarios explican un contrato o una invariante, son cortos y no cuentan la historia del arreglo, que va en el commit (R-GOB-07).
- Máximo 1000 líneas por archivo de código en `codigo/`, `incluir/` y `herramientas/` (lo comprueba `herramientas/comprobar_lineas.py` dentro de `make test`, que lista las pocas excepciones: tablas de datos y la API original de libultra). Si una parte crece, va a un archivo propio.
- El código descompilado se toca lo justo (ver [Lo que no se negocia](#lo-que-no-se-negocia), punto 8).

## Ciclo de un cambio

1. **Especificación.** El cambio responde a un requisito de la [especificación](docs/traduccion/especificacion.md). Si cambia un requisito, un límite, una escala, un término o un contrato, primero se registra en [cambios.md](docs/traduccion/cambios.md) y se aprueba; después se toca el código.
2. **Prueba en rojo.** La prueba nueva va en `herramientas/pruebas/`, entra en el objetivo `test` del `Makefile` y falla antes del cambio por el motivo esperado. **Cada prueba nueva cubre al menos un caso válido y uno de error**, para que no pase en vacío.
3. **Verde.** El cambio hace pasar la prueba sin romper ninguna otra.
4. **Mutación restaurada.** Se rompe a mano la implementación, la prueba vuelve a fallar y se restaura. Si el comportamiento ya existía y solo se añade la prueba, la mutación es el rojo.
5. **Sin arnés en el PC.** Si el código solo compila con el SDK de PS2 y no hay forma de probarlo en el PC dentro del cambio, el mensaje del commit lleva la evidencia de código (archivo y línea, escenario concreto, resultado antes y después) y la prueba que falta se anota en [deuda.md](docs/traduccion/deuda.md). No se escriben pruebas que no prueban nada.
6. **Árbol limpio.** `git status --short` vacío.

Prueba y cambio pueden ir en dos commits o en uno; en los dos casos el rojo queda demostrado (R-GOB-03):

```sh
# Dos commits: el de la prueba queda en rojo
rm -rf build/ps2/jp                 # evita probar copias convertidas viejas
make test                           # falla en el caso nuevo
git add -- herramientas/pruebas/<prueba> Makefile
git commit -m "test(<dominio>): <qué comprueba>"
make test                           # pasa después del cambio
git add -- <rutas del cambio>
git commit -m "fix(<dominio>): <qué cambia>"

# Un commit: la prueba se ejecuta sobre el árbol del padre y falla
git worktree add --detach ../rojo HEAD~1
git show HEAD:herramientas/pruebas/<prueba> > ../rojo/herramientas/pruebas/<prueba>
(cd ../rojo && <orden de la prueba>)
git worktree remove --force ../rojo

# Mutación restaurada
make test                           # con la mutación: falla
git checkout -- <ruta>
git diff --quiet -- <ruta> && echo restaurado

# Árbol limpio
git clean -fdq -- build && git checkout -- build compilaciones
git status --short                  # vacío
```

## Revisión

- Revisa un rol distinto del autor; el autor nunca revisa lo suyo (R-GOB-04). Cada rama tiene una revisión técnica y, si toca textos que se ven o se leen, una lingüística. Qué mira cada una está en [plan.md §7](docs/traduccion/plan.md#7-revisión).
- El revisor trabaja sobre el diff de tres puntos (`git diff <integración>...<rama>`), que solo muestra lo que aporta la rama aunque la rama de integración haya avanzado.
- **Veredicto** de cada revisión: «aprobada», «aprobada con observaciones» o «cambios requeridos».
- **No se integra con hallazgos Alta o Media abiertos.** La única excepción es una decisión del responsable del proyecto, registrada en el acta y en [cambios.md](docs/traduccion/cambios.md).
- Si la rama se rehace después de la revisión (por ejemplo, para corregir un mensaje), el acta anota la correspondencia entre los hashes revisados y los integrados.

### Acta de revisión

Cada integración deja un acta en `docs/traduccion/revisiones/AAAA-MM-DD-<tema>.md`, enlazada desde el [índice de docs/traduccion](docs/traduccion/README.md). La de F8 es [2026-10-11-sincronizacion.md](docs/traduccion/revisiones/2026-10-11-sincronizacion.md).

````markdown
# Acta de revisión: <tema> (<fase>)

- **Fecha:** AAAA-MM-DD
- **Rama de integración:** `feature/<tema>`, de dónde nace y qué trae.
- **Cambios que cubre:** CC-NN a CC-NN.
- **Roles:** quién escribió y quién revisó cada rama.

## Resumen

| Rama | Revisión técnica | Revisión lingüística | Decisión |
|---|---|---|---|
| `<tema>/<parte>` | Veredicto | Veredicto | Integrada (`<merge>`) / No se integra: motivo |

## N. `<tema>/<parte>`: título

**Commits:** `<hash>` (`<asunto>`)…

**Comprobaciones de REVISIÓN técnica:** qué se ejecutó y qué salió.

**Hallazgos técnicos:**

**[Alta|Media|Baja] Título**
- Archivo: ruta:línea
- Riesgo: qué falla y en qué caso
- Recomendación: qué cambiar
- Estado: resuelto en `<commit>` / aceptado: motivo / abierto: entrada en deuda.md

**Hallazgos lingüísticos:** con el mismo formato.

**Decisión:** se integra con `<merge>` / no se integra: motivo.
````

## Publicación y versión

- **Versión:** `X.Y.Z`, con la etiqueta `vX.Y.Z`. La primera es la 1.0.0. `BUILD_ID` del `Makefile` es la fecha de la versión (`AAAA-MM-DD`) y cambia en un commit `build(make)` propio.
- **Antes de publicar**, en la rama de integración:
  - [CHANGELOG.md](CHANGELOG.md): lo de «Sin publicar» pasa a la sección de la versión, con su fecha;
  - `docs/versiones/vX.Y.Z.md`: el cuerpo de la Release, enlazado desde el README. Sin él, el job `release` se detiene.
- **Orden:** `publicar` → merge a `main` → `release` → `limpiar-ramas`, cada paso con el anterior en verde. El detalle de cada job está en el [manual técnico](docs/manual/tecnico.md#ci-y-publicación).
- Los datos que solo existen después del commit de publicación (tamaño y SHA-256 de la ISO, commit de publicación y ejecución de la CI) se completan en un commit `docs` antes del merge a `main`.
- Lo que no se puede comprobar con las pruebas del PC ni con la CI se declara como limitación en el [manual de usuario](docs/manual/usuario.md#limitaciones-conocidas) y en las notas de la versión. No se piden recorridos ni capturas a nadie ([CC-12](docs/traduccion/cambios.md)).

## Documentación

- La documentación se actualiza en la misma rama que el cambio (R-GOB-08): especificación, trazabilidad, cambios, manuales y README, según lo que toque, y una línea en «Sin publicar» del [CHANGELOG](CHANGELOG.md) si el cambio se nota en la versión.
- Cada tema se explica en un solo documento; los demás lo enlazan.
- **Todo documento nuevo se enlaza desde un índice:** el [README](README.md), el [índice del manual](docs/manual/README.md) o el [de docs/traduccion](docs/traduccion/README.md).
- Español neutro, con tildes y signos de apertura. Los datos (commits, rutas, cifras) se comprueban en el código o en git antes de escribirlos.

## Definition of Done

Un cambio está terminado cuando se cumplen todos estos puntos:

1. **Respaldo:** responde a un requisito de la especificación o a un cambio aprobado en [cambios.md](docs/traduccion/cambios.md).
2. **Compila en la CI** con la imagen `ps2dev/ps2dev` fijada por digest: `make`, `make DEBUG=1`, `make DEV=1` y `make iso` (job `compilar-ps2`).
3. **`make test` pasa sin regresiones**, en el PC y en la CI (jobs `pruebas-pc` y `compilar-ps2`).
4. **Pruebas:** cada prueba nueva cubre un caso válido y uno de error, con el rojo y la mutación restaurada demostrados en el mensaje del commit. Si no hay arnés posible en el PC, el mensaje lleva la evidencia de código y la prueba que falta está en [deuda.md](docs/traduccion/deuda.md).
5. **Commits:** con formato, una sola cosa por commit, stage por ruta, sin trailers y sin `build/` ni `compilaciones/`. El comando de [Commits](#commits) sale vacío; los commits del repositorio original que trae una fusión con él quedan fuera (CC-08).
6. **Documentación sincronizada** en la misma rama, con cada documento nuevo enlazado desde un índice.
7. **Limitaciones declaradas:** lo que no comprueban las pruebas ni la CI está escrito como limitación, sin pasos manuales para nadie.
8. **Árbol limpio:** `git status --short` vacío, con `build/` y `compilaciones/` restaurados.
9. **Revisión** por un rol distinto del autor, registrada en el acta, sin hallazgos Alta o Media abiertos.
10. **Visto bueno del responsable del proyecto** para integrar en `main`.
