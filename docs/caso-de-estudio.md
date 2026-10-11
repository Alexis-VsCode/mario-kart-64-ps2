# Caso de estudio: Mario Kart 64 para PlayStation 2 en español

Autor: Alexis Barrera, desarrollador e ingeniero de observabilidad ([Alexis-VsCode](https://github.com/Alexis-VsCode)). Versión de referencia: 1.2.0 (rama `feature/version-1.2.0`, [PR #5](https://github.com/Alexis-VsCode/mario-kart-64-ps2/pull/5)).

## Motivación

Mario Kart 64 es el juego de mi infancia. Quería volver a jugarlo en mi PlayStation 2, en español y con algunas mejoras que el original nunca tuvo. La descompilación comunitaria de Mario Kart 64 y el port de [anthoo582](https://github.com/anthoo582/mario-kart-64-ps2) lo hicieron posible: este repositorio es un fork de ese port.

Es un proyecto sin fines de lucro, educativo, de preservación y de apoyo a la comunidad. Se publican la ISO y el ELF, como en el repositorio original, con los créditos a anthoo582 y al proyecto de descompilación de mk64 ([créditos](manual/creditos.md)). No tiene afiliación con Nintendo ni con Sony.

## El reto

- **Un port de código descompilado.** El juego corre en la PS2 traduciendo la lista de comandos de la N64 al GS. Cualquier cambio toca código que nadie diseñó para leerse, y un error no da un mensaje: da una pantalla negra.
- **Una traducción completa con Ñ y tildes.** El texto del juego se codifica en EUC-JP; las letras acentuadas y la Ñ no existen en la fuente original y se añadieron como glifos nuevos en el rango JIS X 0212, con su tabla de conversión y sus pruebas.
- **Texto dentro de texturas.** Buena parte del texto visible (VUELTA, BIENVENIDOS, YA, 1J-4J, PASO A NIVEL, los puestos con «º») está dibujado en texturas comprimidas. Hubo que exportarlas, recomponerlas sin pérdida y volver a importarlas al formato original.
- **La PS2 como destino.** Memoria limitada, Memory Card, consolas PAL y NTSC, televisores 4:3 y 16:9, y la ROM empaquetada en el ELF con un tope de tamaño.

## Decisiones técnicas clave

- **La especificación va primero.** Cada cambio de comportamiento empieza como un contrato de cambio (CC) en [cambios.md](traduccion/cambios.md), con requisitos verificables, antes de escribir código.
- **Pruebas en el PC, sin el SDK de la PS2.** `PS2SDK= make test` compila y ejecuta las pruebas de C y de Python en cualquier máquina, de modo que el ciclo rojo-verde dura segundos.
- **Manifiestos en lugar de listas en la cabeza.** `recursos/es/texturas.tsv` dice qué hace el proyecto con cada textura: traducirla o por qué no (unidad, nombre propio, onomatopeya, no se muestra, decorado sin texto). Una prueba falla si aparece una textura sin clasificar.
- **Opciones del jugador en un archivo propio.** El menú CONFIGURACIÓN Y TRUCOS guarda en `SMK64CFG.DAT`, separado de la partida, para no arriesgar los récords (`8c022b34`).
- **Comportamientos por defecto prudentes.** Antiparpadeo desactivado; CON BANDAS si la PS2 está configurada en 16:9; los récords se guardan aunque haya trucos, con una advertencia; 200CC solo en GP y VS a 150cc, y puntúa como 150cc.

## Proceso

1. **Especificación primero.** CC-01 a CC-29 en [cambios.md](traduccion/cambios.md), cada uno con sus requisitos, su prueba y su commit en la [trazabilidad](traduccion/trazabilidad.md).
2. **TDD con mutaciones.** Cada prueba se ve en rojo antes del cambio y se demuestra que detecta una mutación del código: por ejemplo, `176651ed` registra el rojo de `prueba_cronometro_fases.c` con `GRUPOS_MAX` 4 y la mutación a 5.
3. **Autor distinto del revisor.** Cada fase se revisa por separado y deja un acta en [revisiones](traduccion/revisiones/). Lo que la revisión encuentra y no se arregla en el momento pasa a la [deuda](traduccion/deuda.md) con un identificador.
4. **Ramas en paralelo.** La 1.2.0 se desarrolló en 14 ramas `v120/*` (contrato, memoria, imagen, menú, trucos, deudas, manifiesto, texturas, ci-emulador, texturas-pistas y cuatro de texturas traducidas), cada una con un alcance cerrado.
5. **Integración con `merge --no-ff`.** Cada rama entra con su propio commit de merge, de `226a3ce3` (contrato) a `85010a1f` (tx-cruce), y la historia conserva qué cambió en cada bloque.

## Observabilidad

El proyecto se trató como un sistema en producción: si no se puede medir, no se da por bueno.

- **Registro de arranque y fases.** Las compilaciones `DEBUG=1` y `DEV=1` escriben un registro con la región de la consola, el modo de vídeo (`vídeo: PMODE 8046`) y la duración de cada fase de arranque.
- **Medidor de rendimiento** en pantalla (`codigo/depuracion/medidor_rendimiento.c`).
- **Pantalla de fallo** (`codigo/sistema/pantalla_fallo.c`), en lugar de una pantalla negra.
- **CI con emulador.** El job «Guion en el emulador (Play!)» arranca el ELF `DEV` dos veces en Play! 0.72 sin BIOS, lee el registro con `herramientas/emulador/comprobar_registro.py` (región PAL con ROMVER sintético y los valores de vídeo por defecto, `979fcf14`) y compara las capturas del título, el menú y la carrera con las de referencia y entre las dos ejecuciones ([ejecución 38159323616](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/38159323616)).
- **Tope de ROM y build incremental** comprobados en cada ejecución de la CI, junto con la compilación release, `DEBUG` y `DEV`, y la fuente de `libdebug`.
- **Integridad de la publicación.** La Release solo se publica si el SHA-256 de la ISO coincide con el de las notas de la versión.
- **Trazabilidad requisito → prueba → commit** en [trazabilidad.md](traduccion/trazabilidad.md).

## Métricas

Calculadas del repositorio en la rama `feature/version-1.2.0`:

| Métrica | Valor |
|---|---|
| Contratos de cambio (CC) | 29 (CC-01 a CC-29); CC-30 se registra con los documentos de traducción de la 1.2.0 |
| Programas de prueba en `make test` | 44, con 294 531 comprobaciones y 0 fallos |
| Commits del autor | 352 de 357 en la rama |
| Ramas integradas en la 1.2.0 | 14 |
| Filas del manifiesto de texturas | 223, de ellas 66 con texto en español |
| Texturas clasificadas | unas 1200 (CC-29) |
| Versiones publicadas | v1.0.0 (`af3bfa05`), v1.1.0 (`fc17498f`) y v1.2.0 (<<PUBLICACION>>) |
| ISO de la 1.2.0 | <<PUBLICACION>> |

## Resultados

- Juego completo en español, con Ñ y tildes en el texto y en las texturas.
- Menú CONFIGURACIÓN Y TRUCOS: ANTIPARPADEO, POSICIÓN X/Y, FORMATO NORMAL/CON BANDAS/PANORÁMICO, DESBLOQUEAR TODO, OBJETO, 200CC y RIVALES SIN VENTAJA.
- Deuda técnica reducida en la 1.2.0; el estado de cada entrada está en [deuda.md](traduccion/deuda.md). Sigue abierta D-23 (partícula de derrape dibujada con la matriz anterior cuando la reserva está llena).
- CI en verde con el juego arrancado de verdad en un emulador.

### Límites declarados

- Sin hardware real ni TV: el tacto del mando, el antiparpadeo, las bandas y la posición se verificaron por valores de registro, porque las capturas leen la VRAM antes del PCRTC. Tampoco se probaron el multitap, el cambio de tarjeta en caliente ni el rendimiento en PANORÁMICO.
- ROMVER solo se comprobó por la ruta con reinicio del IOP y con un ROMVER sintético.
- En PANORÁMICO, los objetos y la pista pueden aparecer tarde en los bordes, y el marcador sale estirado.

## Lecciones

- **Escribir el contrato antes que el código** evita discusiones al revisar: la pregunta es si se cumple el requisito, no si gusta el cambio.
- **Una prueba que no ha fallado nunca no demuestra nada.** Ver la prueba en rojo y demostrar que detecta una mutación es lo que le da valor.
- **Declarar los límites es parte del resultado.** Separar lo verificado en emulador de lo que necesita una TV real evita prometer de más.
- **Observar el arranque desde la CI** convierte «en mi máquina funciona» en una comprobación repetible en cada commit.
