# Caso de estudio: Mario Kart 64 para PlayStation 2 en español

Soy Alexis Barrera, desarrollador e ingeniero de observabilidad ([Alexis-VsCode](https://github.com/Alexis-VsCode)), y este es el caso de estudio de mi proyecto. Versión de referencia: 1.2.0 (rama `feature/version-1.2.0`, [PR #5](https://github.com/Alexis-VsCode/mario-kart-64-ps2/pull/5)).

## Motivación

Mario Kart 64 es el juego de mi infancia. Quería volver a jugarlo en mi PlayStation 2, en español y con algunas mejoras que el original nunca tuvo. La descompilación comunitaria de Mario Kart 64 y el port de [anthoo582](https://github.com/anthoo582/mario-kart-64-ps2) lo hicieron posible: mi repositorio es un fork de ese port.

Es un proyecto sin fines de lucro, educativo, de preservación y de apoyo a la comunidad. Publico la ISO y el ELF, como el repositorio original, con los créditos a anthoo582 y al proyecto de descompilación de mk64 ([créditos](manual/creditos.md)). No tengo afiliación con Nintendo ni con Sony.

## El reto

- **Un port de código descompilado.** El juego corre en la PS2 traduciendo la lista de comandos de la N64 al GS. Cualquier cambio toca código que nadie diseñó para leerse, y un error no da un mensaje: da una pantalla negra.
- **Una traducción completa con Ñ y tildes.** El texto del juego se codifica en EUC-JP; las letras acentuadas y la Ñ no existen en la fuente original y las añadí como glifos nuevos en el rango JIS X 0212, con su tabla de conversión y sus pruebas.
- **Texto dentro de texturas.** Buena parte del texto visible (VUELTA, BIENVENIDOS, YA, 1J-4J, PASO A NIVEL, los puestos con «º») está dibujado en texturas comprimidas. Tuve que exportarlas, recomponerlas sin pérdida y volver a importarlas al formato original.
- **La PS2 como destino.** Memoria limitada, Memory Card, consolas PAL y NTSC, televisores 4:3 y 16:9, y la ROM empaquetada en el ELF con un tope de tamaño.

## Decisiones técnicas clave

- **La especificación va primero.** Cada cambio de comportamiento empieza como un contrato de cambio (CC) en [cambios.md](traduccion/cambios.md), con requisitos verificables, antes de escribir código.
- **Pruebas en el PC, sin el SDK de la PS2.** `PS2SDK= make test` compila y ejecuta las pruebas de C y de Python en cualquier máquina, de modo que el ciclo rojo-verde dura segundos.
- **Manifiestos en lugar de listas en la cabeza.** `recursos/es/texturas.tsv` dice qué hago con cada textura: traducirla o por qué no (unidad, nombre propio, onomatopeya, no se muestra, decorado sin texto). Una prueba falla si aparece una textura sin clasificar.
- **Opciones del jugador en un archivo propio.** El menú CONFIGURACIÓN Y TRUCOS guarda en `SMK64CFG.DAT`, separado de la partida, para no arriesgar los récords ([`8c022b34`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/8c022b34)).
- **Comportamientos por defecto prudentes.** Antiparpadeo desactivado; CON BANDAS si la PS2 está configurada en 16:9; los récords se guardan aunque haya trucos, con una advertencia; 200CC solo en GP y VS a 150cc, y puntúa como 150cc.

## Proceso

1. **Especificación primero.** Escribí CC-01 a CC-29 en [cambios.md](traduccion/cambios.md), cada uno con sus requisitos, su prueba y su commit en la [trazabilidad](traduccion/trazabilidad.md).
2. **TDD con mutaciones.** Veo cada prueba en rojo antes del cambio y compruebo que detecta una mutación del código: por ejemplo, [`176651ed`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/176651ed) registra el rojo de `prueba_cronometro_fases.c` con `GRUPOS_MAX` 4 y la mutación a 5.
3. **Revisión separada de la escritura.** Cada fase pasa por una revisión aparte de la escritura y deja un acta en [revisiones](traduccion/revisiones/). Lo que la revisión independiente encuentra y no corrijo en el momento pasa a la [deuda](traduccion/deuda.md) con un identificador.
4. **Ramas en paralelo.** Desarrollé la 1.2.0 en 14 ramas `v120/*` (contrato, memoria, imagen, menú, trucos, deudas, manifiesto, texturas, ci-emulador, texturas-pistas y cuatro de texturas traducidas), cada una con un alcance cerrado.
5. **Integración con `merge --no-ff`.** Cada rama entra con su propio commit de merge, de [`226a3ce3`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/226a3ce3) (contrato) a [`fd6a4bb7`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/fd6a4bb7) (tx-cruce), y la historia conserva qué cambió en cada bloque.

## Observabilidad

Traté el proyecto como un sistema en producción: si no se puede medir, no se da por bueno.

- **Registro de arranque y fases.** Las compilaciones `DEBUG=1` y `DEV=1` escriben un registro con la región de la consola, el modo de vídeo (`vídeo: PMODE 8046`) y la duración de cada fase de arranque.
- **Medidor de rendimiento** en pantalla (`codigo/depuracion/medidor_rendimiento.c`).
- **Pantalla de fallo** (`codigo/sistema/pantalla_fallo.c`), en lugar de una pantalla negra.
- **CI con emulador.** El job «Guion en el emulador (Play!)» arranca el ELF `DEV` dos veces en Play! 0.72 sin BIOS, lee el registro con `herramientas/emulador/comprobar_registro.py` (región PAL con ROMVER sintético y los valores de vídeo por defecto, [`979fcf14`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/979fcf14)) y compara las capturas del título, el menú y la carrera con las de referencia y entre las dos ejecuciones ([ejecución 38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616)).
- **Tope de ROM y build incremental** comprobados en cada ejecución de la CI, junto con la compilación release, `DEBUG` y `DEV`, y la fuente de `libdebug`.
- **Integridad de la publicación.** La Release solo sale si el SHA-256 de la ISO coincide con el de las notas de la versión.
- **Trazabilidad requisito → prueba → commit** en [trazabilidad.md](traduccion/trazabilidad.md).

## Métricas

Calculé estas cifras del repositorio en la rama `feature/version-1.2.0`:

| Métrica | Valor |
|---|---|
| Contratos de cambio (CC) | 29 (CC-01 a CC-29); registré CC-30 con los documentos de traducción de la 1.2.0 |
| Programas de prueba en `make test` | 44, con 294 531 comprobaciones y 0 fallos |
| Mis commits | 352 de 357 en la rama |
| Ramas integradas en la 1.2.0 | 14 |
| Filas del manifiesto de texturas | 223, de ellas 66 con texto en español |
| Texturas clasificadas | unas 1200 (CC-29) |
| Versiones publicadas | v1.0.0 (`af3bfa05`), v1.1.0 (`fc17498f`), v1.2.0 (`9ab41422`) y v1.2.1 (`d3c27566`) |
| ISO de la 1.2.0 | 13 387 776 bytes, SHA-256 `186d45b2feaa66078820005eb43370701a17ea45bdd15ad9e3eb420c8ffb0f21` |

## Resultados

- Juego completo en español, con Ñ y tildes en el texto y en las texturas.
- Menú CONFIGURACIÓN Y TRUCOS: ANTIPARPADEO, POSICIÓN X/Y, FORMATO NORMAL/CON BANDAS/PANORÁMICO, DESBLOQUEAR TODO, OBJETO, 200CC y RIVALES SIN VENTAJA.
- Dejé la deuda técnica en cero en la 1.2.0: todas las entradas de [deuda.md](traduccion/deuda.md) están saldadas o pasaron a límites declarados (lo que solo se ve en hardware real).
- CI en verde con el juego arrancado de verdad en un emulador.
- En la 1.2.1, al bajar la tolerancia de las capturas del 2 % al 0,1 % ([`632050ac`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/632050ac)) encontré dos defectos visuales reales que la comparación laxa dejaba pasar: los valores tenues del menú CONFIGURACIÓN Y TRUCOS y el ordinal «8º.» de los puestos, que ya corregí.

### Límites declarados

- Sin hardware real ni TV: el tacto del mando, el antiparpadeo, las bandas y la posición los comprobé por valores de registro, porque las capturas leen la VRAM antes del PCRTC. Tampoco probé el multitap, el cambio de tarjeta en caliente ni el rendimiento en PANORÁMICO.
- Solo comprobé ROMVER por la ruta con reinicio del IOP y con un ROMVER sintético.
- En PANORÁMICO, los objetos y la pista pueden aparecer tarde en los bordes, y el marcador sale estirado.

## Lecciones

- **Escribir el contrato antes que el código** evita discusiones al revisar: la pregunta es si cumple el requisito, no si gusta el cambio.
- **Una prueba que no ha fallado nunca no demuestra nada.** Verla en rojo y comprobar que detecta una mutación es lo que le da valor.
- **Declarar los límites es parte del resultado.** Separar lo que comprobé en el emulador de lo que necesita una TV real evita prometer de más.
- **Observar el arranque desde la CI** convierte «en mi máquina funciona» en una comprobación que se repite en cada commit.

## Qué comprobé y cómo

| Afirmación | Cómo lo comprobé | Evidencia |
|---|---|---|
| Las pruebas pasan sin el SDK de PS2 | `PS2SDK= make test` en el PC: 44 pruebas con resumen, 0 fallos en la 1.2.0 | [ejecución 38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616) |
| El juego compila y arranca en un emulador | Compilación release, `DEBUG` y `DEV`, tope de ROM y arranque en Play! sin BIOS | [ejecución 38181807319](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38181807319) |
| Las capturas no se desvían | Comparación con tolerancia del 0,1 % | [`632050ac`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/632050ac) y el [acta de la 1.2.1](traduccion/revisiones/2026-10-11-version-1.2.1.md) |
| Hardware real y TV | Sin comprobar | [Límites declarados](traduccion/especificacion.md) |

## Patrones y prácticas que apliqué

| Patrón | Dónde se ve |
|---|---|
| Especificación antes del código | [cambios.md](traduccion/cambios.md) |
| Pruebas en rojo con mutación | [`176651ed`](https://github.com/Alexis-VsCode/mario-kart-64-ps2/commit/176651ed) |
| Funciones puras en cabeceras `static inline` | Las pruebas compilan en el PC la lógica de la PS2 |
| Revisión separada de la escritura | [revisiones](traduccion/revisiones/) |
| CI con emulador | [ejecución 38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616) |
| Publicación reproducible con SHA-256 | [notas de la v1.2.1](versiones/v1.2.1.md) |
| Trazabilidad CC, commit y prueba | [trazabilidad.md](traduccion/trazabilidad.md) |

## Mi trayectoria en este proyecto

Trabajo como desarrollador e ingeniero de observabilidad y quise comprobar en un proyecto de ocio lo que defiendo en el trabajo: medir antes de dar algo por bueno. Aquí lo apliqué a un juego: un registro de arranque, un medidor de rendimiento, una pantalla de fallo y capturas comparadas con tolerancia en cada commit. Lo que me llevo es el hábito de escribir el contrato antes, ver cada prueba fallar y declarar los límites de lo que no pude verificar.
