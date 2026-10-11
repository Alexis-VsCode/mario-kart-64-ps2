# Manual de usuario

## Ejecutar

- **PCSX2** (con BIOS) y **Play!**: abrir la ISO de `compilaciones/`.
- **OPL** (sin probar en hardware): copiar la carpeta `compilaciones/disco/OPL/CD/` a la raíz del USB o del recurso SMB. Lanzado desde OPL, el juego no reinicia el IOP (lo detecta por la firma del núcleo de OPL y por arrancar desde `cdrom`), así que OPL no tiene que volver a montar el USB, el HDD o la red. A cambio no hay VMC, PADEMU ni IGR de OPL: la partida se guarda en la Memory Card física.
- **uLaunchELF** (sin probar en hardware): usar el ELF de `make MONOLITICO=1` (`build/ps2/monolitico/SLUS_999.99`), que hay que compilar. El `SLUS_999.99` normal busca `SMK64ROM.BIN` solo en `host:` y en el disco, no junto al ELF (`codigo/sistema/carga_rom.c`). Según el código, lanzado desde un USB sin disco debería detenerse con el error «falta SMK64ROM.BIN».
- **ELF suelto en un emulador con `host:`**: `SMK64ROM.BIN` tiene que estar en la carpeta que el emulador expone como `host:`.

`SLUS_999.99` y `SMK64ROM.BIN` deben salir de la misma compilación. El juego no detecta un `SMK64ROM.BIN` de otra compilación si es igual o más grande que el esperado (ver [Solución de problemas](#solución-de-problemas)).

## Controles

Asignación de `codigo/entrada/mandos.c`. Al conectar un mando, el port lo fija en modo DualShock (analógico).

| N64 | DualShock 2 |
|---|---|
| A | Cruz |
| B | Cuadrado |
| Z | L1 o L2 |
| R | R1 o R2 |
| L | Select |
| Start | Start |
| Stick | Stick izquierdo |
| Cruceta | Cruceta (también hace de stick si el stick izquierdo está en reposo) |
| C arriba | Triángulo o stick derecho hacia arriba |
| C abajo | Círculo o stick derecho hacia abajo |
| C izquierda / C derecha | Stick derecho hacia la izquierda / derecha |

Funciones propias del port (solo en el mando 1):

| Botón | Acción |
|---|---|
| R3 (sin L3) | Activa o desactiva los 60 FPS |
| L3 + R3 | Cambia la vista del panel de rendimiento (solo en compilaciones con panel) |
| START o A en el bucle de créditos | Vuelve a la pantalla de título |

El stick izquierdo tiene una zona muerta de 24 y se escala al recorrido de un stick de N64 (máximo 80). El stick derecho activa los botones C cuando se aleja más de 64 del centro.

### Multitap

Cada jugador queda fijo a su conector, aunque otro mando se desconecte (`conector_jugador_ps2` en `codigo/entrada/multitap.c`):

| Multitap | Jugador 1 | Jugador 2 | Jugador 3 | Jugador 4 |
|---|---|---|---|---|
| En el puerto 1 | 1-A | 1-B | 1-C | 1-D |
| Solo en el puerto 2 | Puerto 1 | 2-A | 2-B | 2-C |
| Sin multitap | Puerto 1 | Puerto 2 | — | — |

El multitap se detecta al arrancar y se vuelve a comprobar una vez por segundo. Usa los módulos XSIO2MAN, XPADMAN y XMTAPMAN de la BIOS, y XMCMAN y XMCSERV para la Memory Card. Si la BIOS no los trae, el juego carga SIO2MAN y PADMAN y funciona con dos mandos.

### Guardado

La partida se guarda en la Memory Card de la ranura 1, en `/BASLUS-99999SMK64/`:

| Archivo | Contenido |
|---|---|
| `SMK64A.SAV`, `SMK64B.SAV` | Dos copias alternas: EEPROM y Controller Pak emulados, con número de generación y CRC32 |
| `icon.sys`, `SMK64.ICO` | Icono del navegador de la consola (`herramientas/crear_icono.py`) |

Al arrancar se carga la copia válida más reciente. Si la tarjeta no responde en 5 s, el juego sigue sin la partida y no guarda. Los archivos `SMK64.SAV` y `SMK64.TMP` de versiones anteriores se leen y se borran en el primer guardado.

## Idioma

El juego está en español, sin selección de idioma. La especificación, el plan, el glosario y la trazabilidad están en [`docs/traduccion/`](docs/traduccion/).

**Qué está en español:**

- **Textos:** menús, opciones, pausa, tiempos y resultados, fantasmas, mensajes de la Memory Card («RANURA 1», «COPIAR FANTASMAS» con un aviso honesto porque en PS2 no hay otra tarjeta desde la que copiar), intro de la batalla, ceremonia y créditos (la mitad japonesa de los créditos se conserva). Los botones se nombran como en el DualShock 2: CRUZ, CUADRADO, SELECT y R1.
- **Nombres de pista:** los oficiales de Nintendo en español (Pista Mario, Senda Arco Iris, Granja Mu-Mu…), con su fuente en el [glosario](docs/traduccion/glosario.md).
- **Fuente del menú:** 11 glifos nuevos (Á É Í Ó Ú Ñ Ü ¡ ¿ º ª), dibujados a partir de los originales; los ordinales se escriben «1.º».
- **Texturas con texto:** 55 texturas (títulos de menú, botones, copas, número de jugadores, los 20 títulos de pista, el cartel de la granja, TIEMPO y VUELTA en el HUD, puestos «1.º»…«8.º» y PULSA START) y los 48 cuadros de los carteles de Lakitu (¡ÚLTIMA!, VUELTA 2 y ¡REVÉS!). Salen de PNG versionados en `recursos/es/`, compuestos con letras de las propias texturas del juego.
- **Pantallas del port:** panel de rendimiento y página de audio (con tildes), nombres de fase, registro y guiones de prueba. La pantalla de fallo usa `scr_printf` de ps2sdk, que solo tiene ASCII: muestra el texto sin tildes («PARADA DE DIAGNOSTICO»), mientras el registro lo conserva completo.

**Qué no se traduce:** nombres de personaje, logotipos y carteles comerciales, 50cc/100cc/150cc, VS, onomatopeyas, las voces (son muestras de audio) y las texturas de la pantalla del Controller Pak, que el port no puede abrir. El detalle está en la [especificación](docs/traduccion/especificacion.md#22-excluido).

**Cómo se comprobó:**

- `make test`, sin el SDK de PS2: 26 pruebas y el tope de líneas en verde (ver [Pruebas](#pruebas)). La prueba de textos recorre todas las tablas con el decodificador del juego y mide cada texto por tinta contra la zona segura del televisor.
- CI en verde en la ejecución [36518116212](https://github.com/Alexis-VsCode/mario-kart-64-ps2/actions/runs/36518116212): pruebas en el PC, compilación para PS2 (release, `DEBUG=1`, `make test` e ISO) y el job `publicar` (release, `DEBUG=1`, `DEV=1`, pruebas e ISO), que generó la compilación versionada `dda9a5f`.

**Queda para el usuario:** el recorrido en PCSX2 con el guion `herramientas/guiones/recorrido_textos.txt` (`make DEV=1`, copiarlo como `smk64_input.txt` en la carpeta `host:` y sacar las capturas a mano en cada `nota`), las pantallas que el guion no recorre y una captura en TV para el sobrebarrido. La lista completa está en [`docs/traduccion/README.md`](docs/traduccion/README.md#pendiente).

El trabajo se repartió en estos roles:

| Rol | Alcance |
|---|---|
| INFRA | Compilación y pruebas: `make test` sin el SDK de PS2, conversión a EUC-JP sin `iconv`, tope de líneas y CI |
| FUENTE | Fuente del menú: tildes, ñ, ü, ¡ y ¿ |
| CADENAS | Textos de menús, mensajes y créditos |
| TEXTURAS | Texturas con texto: menús, títulos de pista, HUD y carteles de Lakitu |
| PORT | Pantallas propias del port: panel de rendimiento, pantalla de fallo y registro |
| PRUEBAS | Prueba en rojo antes de cada cambio |
| REVISIÓN | Revisión técnica y lingüística de cada bloque |
| INTEGRACIÓN | Integración y commit de publicación de los binarios |

## Solución de problemas

| Síntoma | Causa y solución |
|---|---|
| En pantalla: «falta SMK64ROM.BIN: usa la ISO completa (o el ELF monolitico con uLaunchELF)» | El ELF no encontró `SMK64ROM.BIN` en `host:` ni en el disco, o el del disco es más pequeño de lo que espera el ELF (de otra compilación). La pantalla muestra el texto sin tildes; en el registro sale `ROM: no se encontró \SMK64ROM.BIN;1 en el disco ...` o `ROM: \SMK64ROM.BIN;1 mide X y debería medir Y`. Usa la ISO de `make iso` o el ELF de `make MONOLITICO=1` |
| En pantalla: «no se pudo leer SMK64ROM.BIN del disco» | Falló una lectura durante la carga, tras 8 reintentos: imagen o disco dañado. Por `host:` también aparece si el archivo es más corto de lo esperado. En el registro sale `ROM: no se pudo leer SMK64ROM.BIN (trozo N)`. Vuelve a crear la ISO con `make iso` |
| La partida no se guarda | Hace falta una Memory Card de PS2 formateada en la ranura 1. Con `DEBUG=1` o `DEV=1`, el registro muestra los mensajes `memory card:` |

Las últimas líneas del registro también aparecen en la pantalla de fallo, en cualquier compilación.
