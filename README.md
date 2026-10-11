# Mario Kart 64 para PlayStation 2

Port de Mario Kart 64 (versión estadounidense) a PlayStation 2. El repositorio incluye el juego descompilado, una capa de compatibilidad que sustituye el hardware de la Nintendo 64 por el de la PS2 y todos los recursos ya extraídos (texturas, pistas, karts, música y efectos). No hace falta la ROM original para compilar.

## Estado

- Probado en **PCSX2** (con BIOS real) y en **Play!**.
- **Sin probar en una PS2 real**, ni con OPL o uLaunchELF en hardware.
- Video NTSC entrelazado a 640×448 (`codigo/graficos/sintetizador_gs.c`).
- Multitap de PS2 (SCPH-10090 o SCPH-70110) para 3 y 4 jugadores, sin probar con un multitap real. Sin multitap se leen los puertos 1 y 2. Ver [Multitap](#multitap).
- **Juego en español**: menús, mensajes, Memory Card, créditos, títulos de pista, HUD, carteles de Lakitu y pantallas propias del port. Detalle y estado de la verificación en [Idioma](#idioma).

## Descarga

La ISO ya compilada, en español, está en el repositorio: [`compilaciones/SLUS_999.99.SuperMarioKart64.iso`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/raw/main/compilaciones/SLUS_999.99.SuperMarioKart64.iso) (13 373 440 bytes, unos 12,8 MiB).

- **PCSX2** (con BIOS) o **Play!**: abrir la ISO directamente.
- **OPL**: copiar la carpeta `compilaciones/disco/OPL/CD/`, que lleva la misma ISO con el nombre que espera OPL, a la raíz del USB o del recurso SMB (sin probar en hardware).

Para compilarla desde el código, ver [Compilar](#compilar).

## Características

- Las 20 pistas (16 de carrera y 4 de batalla), los 8 personajes y los modos Gran Premio, Contrarreloj, VS y Batalla, de 1 a 4 jugadores con multitap.
- Gráficos: un intérprete de listas de dibujo F3DEX, con el combinador de color y la TMEM de la N64, que produce paquetes para el GS.
- Audio original: las muestras de la ROM se mezclan con la misma aritmética que la N64 (microcódigo de audio reescrito en C) y salen a 48 kHz por `audsrv`.
- Modo 60 FPS, activo por defecto y conmutable con R3. Dibuja un cuadro intermedio solo durante la carrera, fuera de pausa, y solo si queda tiempo de CPU con margen. La lógica del juego sigue a 30 Hz, como en el original. Si el cuadro intermedio provoca un tirón, el juego pasa unos segundos a 30 FPS; desde el tercer tirón de una carrera sigue a 30 FPS estables hasta la siguiente (`codigo/graficos/interprete_f3dex/listas_dibujo.inc.c`).
- De 2 a 4 jugadores, si una imagen tarda más de lo previsto, la física da hasta 4 pasos por imagen para que la carrera no vaya en cámara lenta (`codigo/sistema/ritmo_fisica.c`).
- Partidas guardadas en la Memory Card de la ranura 1, en dos copias alternas con CRC32.
- Los datos de la ROM se leen del disco en segundo plano desde el arranque.
- En el bucle de créditos, START o A del mando 1 vuelven a la pantalla de título.
- Pantalla de fallo con el estado de cada hilo y el registro reciente. Aparece ante una excepción, un error fatal o un cuelgue.
- ISO con fechas fijas, tomadas de `SOURCE_DATE_EPOCH` o del último commit.

## Contribuir

### 1. Rama

Crea la rama desde el último `origin/main` y verifica de dónde nace:

```bash
git fetch origin
git switch -c fix/mi-cambio origin/main
git reflog show fix/mi-cambio | tail -1           # «branch: Created from origin/main»
git rev-list --count origin/main..fix/mi-cambio   # 0: todavía sin commits propios
git rev-list --count fix/mi-cambio..origin/main   # 0: no le falta nada de main
```

Nombre: `tipo/tema`, en minúsculas y con guiones (por ejemplo, `fix/tilde-en-la-pausa`). La rama se borra después de integrarla.

Un cambio que toca textos o texturas en pantalla sigue además la [especificación de la traducción](docs/traduccion/especificacion.md) y el [glosario](docs/traduccion/glosario.md): primero se actualizan los textos esperados de `herramientas/pruebas/` y, si cambia un límite, una escala o un término, se registra en [`cambios.md`](docs/traduccion/cambios.md).

### 2. Prueba en rojo

1. Escribe la prueba en `herramientas/pruebas/` y añádela al objetivo `test` del `Makefile`.
2. Ejecuta `make test` y comprueba que falla (rojo) por el motivo esperado.
3. Haz el cambio y comprueba que `make test` pasa (verde).

Si el comportamiento ya existe y solo añades la prueba, demuestra que detecta el fallo con una mutación temporal del código. Después restaura el archivo y comprueba con `git diff --quiet -- <ruta>` que no queda rastro.

### 3. Commits

- Formato `tipo(dominio): descripción`, en español. Tipos: `feat`, `fix`, `refactor`, `test`, `build`, `ci` y `docs`. El dominio es el área que se toca (`menus`, `sistema`, `make`, `readme`…); los cambios de integración continua van sin dominio (`ci: descripción`). Ejemplo: `docs(readme): describir el flujo de contribución`.
- Un tema por commit.
- Un refactor no cambia el comportamiento y va en su propio commit, nunca junto a un cambio funcional.
- Agrega los archivos por ruta (`git add <ruta>`), nunca con `git add -A` ni `git add .`. Revisa `git status --short` antes de cada commit.
- `build/` y `compilaciones/` no entran en los commits de trabajo (ver [Binarios versionados](#binarios-versionados)).

### 4. Antes de pedir revisión

```bash
. herramientas/entorno.sh
make clean && make -j"$(nproc)"
make test
git checkout -- build compilaciones
git status --short   # solo deben aparecer tus cambios
```

Si el cambio afecta a `DEBUG=1` o `DEV=1`, compila también esas variantes.

### 5. Revisión

Otra persona revisa cada cambio; el autor nunca revisa el suyo. Cada hallazgo sigue este formato:

```text
[Alta|Media|Baja] Título
Archivo: ruta:línea
Riesgo: qué puede fallar
Recomendación: cómo corregirlo
```

No se integra un cambio con hallazgos Alta o Media abiertos.

### 6. Integración

Con la revisión aprobada, la rama se integra con un commit de merge explícito:

```bash
git switch main
git pull --ff-only
git merge --no-ff fix/mi-cambio
```

### Definition of Done

Un cambio está terminado cuando:

1. Compila: `make clean && make` termina sin errores.
2. `make test` pasa, sin regresiones.
3. La documentación está sincronizada: README y `docs/` describen el cambio.
4. El árbol está limpio: `git status --short` vacío, con `build/` y `compilaciones/` restaurados.
5. El responsable del proyecto confirma el cierre.

### Reglas de código

- Nombres en español y en `snake_case`. Los tipos van en `PascalCase` y las constantes en `MAYUSCULAS`.
- La API de libultra, el SDK de PS2 y los símbolos del enlazador conservan sus nombres originales.
- Las funciones y los datos sin identificar se llaman `funcion_<dirección>` y `dato_<dirección>`, con la dirección original de la N64.
- Comentarios cortos.
- Máximo 1000 líneas por archivo de código en `codigo/`, `incluir/` y `herramientas/`; los datos de `recursos/` (pistas y texturas) no cuentan. Si una parte crece, va a un archivo propio. Solo lo superan las tablas de datos y la cabecera externa que ya lo hacían: `codigo/datos/karts/kart_*.s`, `codigo/datos/otras_texturas.s`, `codigo/datos/texturas_fuentes.s`, `codigo/memoria/tablas_trigonometricas.c` e `incluir/libultra/PR/gbi.h`.

## Aviso legal

Proyecto de preservación sin afiliación con Nintendo ni con Sony. Mario Kart 64, Nintendo 64, PlayStation 2, DualShock y el resto de marcas citadas pertenecen a sus respectivos dueños.
