# Manual de usuario

Cómo jugar a Mario Kart 64 para PlayStation 2, en español. Para compilar o modificar el port, ver el [manual técnico](tecnico.md).

## Qué es

Un port de Mario Kart 64 (versión estadounidense) a PlayStation 2, con todo el texto que ve el jugador en español. La ISO ya trae el juego completo: no hace falta la ROM original. Es un proyecto de preservación sin afiliación con Nintendo ni con Sony.

## Requisitos

Una de estas opciones:

- **PCSX2**, con una BIOS de PS2;
- **Play!**;
- **una PS2** con OPL o uLaunchELF (sin probar en hardware; ver [Limitaciones conocidas](#limitaciones-conocidas)).

La imagen es NTSC, entrelazada a 640×448 y a 60 Hz (`codigo/graficos/sintetizador_gs.c`); con una consola PAL, ver [Consolas PAL y NTSC](#consolas-pal-y-ntsc). Para guardar la partida hace falta una Memory Card de PS2 formateada en la ranura 1.

## Descarga y comprobación

Los enlaces de descarga están en la [Descarga del README](../../README.md#descarga). La Release publica tres archivos:

- la ISO, `SLUS_999.99.SuperMarioKart64.iso`, para PCSX2, Play! y OPL;
- el ELF monolítico, `SLUS_999.99.monolitico.elf`, para uLaunchELF desde USB;
- `SHA256SUMS`, con una línea por cada uno de los dos anteriores.

Basta con descargar el archivo que vayas a usar. Con él y `SHA256SUMS` en la misma carpeta:

```bash
sha256sum -c --ignore-missing SHA256SUMS
# SLUS_999.99.SuperMarioKart64.iso: OK      (o SLUS_999.99.monolitico.elf: OK)
```

`--ignore-missing` omite la línea del archivo que no descargaste; sin esa opción, `sha256sum` la da por fallida. En Windows, con PowerShell: `Get-FileHash <archivo> -Algorithm SHA256`, y comparar el resultado con su línea de `SHA256SUMS`. Si no coincide o no sale `OK`, la descarga está dañada: vuelve a descargarla.

## Ejecutar

- **PCSX2** (con BIOS) y **Play!**: abrir la ISO directamente.
- **OPL** (sin probar en hardware): copiar la ISO, con el mismo nombre, en la carpeta `CD/` de la raíz del USB o del recurso SMB. Lanzado desde OPL, el juego no reinicia el IOP (lo detecta por la firma del núcleo de OPL y por arrancar desde `cdrom`), así que OPL no tiene que volver a montar el USB, el HDD o la red. A cambio no hay VMC, PADEMU ni IGR de OPL: la partida se guarda en la Memory Card física.
- **uLaunchELF** (sin probar en hardware): usa el ELF monolítico de la Release, `SLUS_999.99.monolitico.elf`. Lleva la ROM entera dentro, así que no hay que compilar nada ni copiar `SMK64ROM.BIN`. Cópialo a un USB y ábrelo desde el navegador de archivos de uLaunchELF (`mass:/`). No sirve el `SLUS_999.99` de la ISO: busca `SMK64ROM.BIN` solo en `host:` y en el disco, no junto al ELF (`codigo/sistema/carga_rom.c`), y lanzado desde un USB sin disco se detiene con el error «falta SMK64ROM.BIN».

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
| L3 + R3 | Cambia la vista del panel de rendimiento (solo en compilaciones con panel; la ISO publicada no lo trae) |
| START o A en el bucle de créditos | Vuelve a la pantalla de título |

El stick izquierdo tiene una zona muerta de 8 (24 hasta la versión 1.0.0) y se escala al recorrido de un stick de N64 (máximo 80). Junto con la zona muerta que aplica el propio juego, el kart empieza a girar con el stick a 28 de 127 del centro, un 22 % del recorrido; antes hacía falta un 32 %. La cruceta hace de stick mientras el stick izquierdo está en reposo, es decir, a 25 o menos del centro en los dos ejes, igual que antes: la deriva de un stick gastado no la anula. Los valores están en `incluir/entrada/eje_palanca.h`. El stick derecho activa los botones C cuando se aleja más de 64 del centro.

## Multitap: de 1 a 4 jugadores

El juego admite el multitap de PS2 (SCPH-10090 o SCPH-70110) para 3 y 4 jugadores. Sin multitap se leen los puertos 1 y 2. Cada jugador queda fijo a su conector, aunque otro mando se desconecte (`conector_jugador_ps2` en `codigo/entrada/multitap.c`):

| Multitap | Jugador 1 | Jugador 2 | Jugador 3 | Jugador 4 |
|---|---|---|---|---|
| En el puerto 1 | 1-A | 1-B | 1-C | 1-D |
| Solo en el puerto 2 | Puerto 1 | 2-A | 2-B | 2-C |
| Sin multitap | Puerto 1 | Puerto 2 | — | — |

El multitap se detecta al arrancar y se vuelve a comprobar una vez por segundo. Usa los módulos XSIO2MAN, XPADMAN y XMTAPMAN de la BIOS, y XMCMAN y XMCSERV para la Memory Card. Si la BIOS no los trae, el juego carga SIO2MAN y PADMAN y funciona con dos mandos.

## 60 FPS

El modo 60 FPS está activo por defecto y se conmuta con R3. Dibuja un cuadro intermedio solo durante la carrera, fuera de pausa, y solo si queda tiempo de CPU con margen. La lógica del juego sigue a 30 Hz, como en el original. Si el cuadro intermedio provoca un tirón, el juego pasa unos segundos a 30 FPS; desde el tercer tirón de una carrera sigue a 30 FPS estables hasta la siguiente (`codigo/graficos/interprete_f3dex/listas_dibujo.inc.c`).

De 2 a 4 jugadores, si las imágenes tardan más de lo previsto, la física da un paso más por imagen que el original, como mucho 4, para que la carrera no vaya en cámara lenta (`codigo/sistema/ritmo_fisica.c`). Con `DEBUG=1` o `DEV=1`, el registro lo indica con líneas `ritmo de física:`.

## Memory Card

La partida se guarda en la Memory Card de la ranura 1, en `/BASLUS-99999SMK64/`:

| Archivo | Contenido |
|---|---|
| `SMK64A.SAV`, `SMK64B.SAV` | Dos copias alternas: EEPROM y Controller Pak emulados, con número de generación y CRC32 |
| `icon.sys`, `SMK64.ICO` | Icono del navegador de la consola (`herramientas/crear_icono.py`) |

Al arrancar se carga la copia válida más reciente. Si la tarjeta no responde en 5 s, medidos con el reloj, el juego sigue sin la partida y no guarda.

Si arrancas sin tarjeta y la insertas después, o cambias la tarjeta con el juego en marcha, antes del primer guardado se leen las dos copias de la tarjeta nueva. La partida se escribe sobre la copia más vieja y con una generación mayor que la de la más nueva: así la copia más nueva de esa tarjeta no se pisa, y en el siguiente arranque se carga la partida recién guardada. Si deja de responder más tarde, el juego deja de usarla hasta el siguiente arranque, en lugar de tomarla por una tarjeta nueva (`codigo/sistema/memory_card.c`). Los archivos `SMK64.SAV` y `SMK64.TMP` de versiones anteriores se leen y se borran en el primer guardado.

## Consolas PAL y NTSC

La imagen sale siempre en NTSC a 60 Hz, también en una consola PAL, la europea (`codigo/graficos/sintetizador_gs.c`). El juego avanza al ritmo del retrazo vertical, así que a 60 Hz va a la velocidad del original. Con una consola PAL hace falta una TV que acepte una señal NTSC de 60 Hz; una TV que solo acepte 50 Hz no mostrará bien la imagen. El port no cambia el modo de vídeo según la consola: un modo PAL a 50 Hz haría el juego un 17 % más lento ([CC-15](../traduccion/cambios.md)).

Al arrancar, el juego lee la región de la consola en la BIOS (`rom0:ROMVER`). Con `DEBUG=1` o `DEV=1`, el registro muestra una de estas líneas:

| Línea del registro | Significado |
|---|---|
| `consola PAL: la imagen sale en NTSC a 60 Hz; hace falta una TV que acepte 60 Hz` | Consola europea |
| `consola NTSC` | Consola de Japón, América, Asia o China |
| `región de la consola desconocida` | No se pudo leer la región; el juego sigue igual |

## Idioma

El juego está en español, sin selección de idioma. La especificación, el plan, el glosario y la trazabilidad están en [`docs/traduccion/`](../traduccion/README.md).

**Qué está en español:**

- **Textos:** menús, opciones, pausa, tiempos y resultados, fantasmas, mensajes de la Memory Card («RANURA 1», «COPIAR FANTASMAS» con un aviso honesto porque en PS2 no hay otra tarjeta desde la que copiar), intro de la batalla, ceremonia y créditos (la mitad japonesa de los créditos se conserva). Los botones se nombran como en el DualShock 2: CRUZ, CUADRADO, SELECT y R1.
- **Nombres de pista:** los oficiales de Nintendo en español (Pista Mario, Senda Arco Iris, Granja Mu-Mu…), con su fuente en el [glosario](../traduccion/glosario.md).
- **Fuente del menú:** 11 glifos nuevos (Á É Í Ó Ú Ñ Ü ¡ ¿ º ª), dibujados a partir de los originales; los ordinales se escriben «1.º».
- **Texturas con texto:** 55 texturas (títulos de menú, botones, copas, número de jugadores, los 20 títulos de pista, el cartel de la granja, TIEMPO y VUELTA en el HUD, puestos «1.º»…«8.º» y PULSA START) y los 48 cuadros de los carteles de Lakitu (¡ÚLTIMA!, VUELTA 2 y ¡REVÉS!). Salen de PNG versionados en `recursos/es/`, compuestos con letras de las propias texturas del juego.
- **Pantallas del port:** panel de rendimiento y página de audio (con tildes), nombres de fase, registro y guiones de prueba. La pantalla de fallo usa `scr_printf` de ps2sdk, que solo tiene ASCII: muestra el texto sin tildes («PARADA DE DIAGNOSTICO»), mientras el registro lo conserva completo.

**Qué no se traduce:** nombres de personaje, logotipos y carteles comerciales, 50cc/100cc/150cc, VS, onomatopeyas, las voces (son muestras de audio) y las texturas de la pantalla del Controller Pak, que el port no puede abrir. El detalle está en la [especificación](../traduccion/especificacion.md#22-excluido).

Cómo se comprobó la localización está en el [manual técnico](tecnico.md#pruebas).

## Limitaciones conocidas

Al 2026-10-11, versión 1.1.0:

- **Sin probar en PS2 real.** Tampoco con OPL ni uLaunchELF en hardware, ni con un multitap real. Según el autor del port original, se probó en PCSX2 (con BIOS) y en Play!.
- **Sin verificar en una consola real lo nuevo de la 1.1.0:**
  - el tacto del stick con la zona muerta de 8;
  - la lectura de la región en `rom0:ROMVER`, tanto con el IOP reiniciado como lanzado desde OPL sin reinicio; si falla, el registro dice «región de la consola desconocida» y el juego sigue igual;
  - el cambio de Memory Card con el juego en marcha.

  Las pruebas del PC comprueban la conversión del stick, la lectura de ROMVER y la elección de la copia que se pisa, pero no el hardware.
- **Sin verificación visual registrada.** Las pruebas del PC comprueban los textos byte a byte, los glifos, los anchos medidos por tinta contra la zona segura del televisor y las texturas generadas, pero no hay capturas registradas de la versión en español en un emulador ni en un televisor ([CC-12](../traduccion/cambios.md)).
- **La pantalla de fallo sale sin tildes**, porque la fuente de ps2sdk solo tiene ASCII. El registro conserva las tildes.
- **Copiar fantasmas no está disponible:** en PS2 no hay otra tarjeta desde la que copiar, y el menú lo avisa.
- **La pantalla del Controller Pak** no se abre en el port y sus texturas no se traducen.
- **Con una consola PAL hace falta una TV que acepte 60 Hz** (ver [Consolas PAL y NTSC](#consolas-pal-y-ntsc)).

## Solución de problemas

| Síntoma | Causa y solución |
|---|---|
| En pantalla: «falta SMK64ROM.BIN: usa la ISO completa (o el ELF monolitico con uLaunchELF)» | El ELF no encontró `SMK64ROM.BIN` en `host:` ni en el disco, o el del disco es más pequeño de lo que espera el ELF (de otra compilación). La pantalla muestra el texto sin tildes; en el registro sale `ROM: no se encontró \SMK64ROM.BIN;1 en el disco ...` o `ROM: \SMK64ROM.BIN;1 mide X y debería medir Y`. Usa la ISO completa o, con uLaunchELF, el ELF monolítico de la Release (`SLUS_999.99.monolitico.elf`) |
| En pantalla: «no se pudo leer SMK64ROM.BIN del disco» | Falló una lectura durante la carga tras 4 intentos de unos 6 s cada uno: imagen o disco dañado. Por `host:` también aparece si el archivo es más corto de lo esperado. En el registro sale `ROM: no se pudo leer SMK64ROM.BIN (trozo N)`. Comprueba la ISO con `SHA256SUMS` (ver [Descarga y comprobación](#descarga-y-comprobación)) y vuelve a descargarla si no coincide |
| La partida no se guarda | Hace falta una Memory Card de PS2 formateada en la ranura 1. Si la tarjeta dejó de responder, el juego no vuelve a usarla hasta el siguiente arranque. Con `DEBUG=1` o `DEV=1`, el registro muestra los mensajes `memory card:` |
| Con una consola PAL, la imagen no se ve bien | La TV no acepta NTSC a 60 Hz. Usa una TV que lo acepte (ver [Consolas PAL y NTSC](#consolas-pal-y-ntsc)) |
| La carrera vuelve a 30 FPS | Tras tres tirones en una carrera, el modo 60 FPS se queda a 30 FPS hasta la siguiente (ver [60 FPS](#60-fps)). También se puede haber desactivado con R3 |

`SLUS_999.99` y `SMK64ROM.BIN` deben salir de la misma compilación. El juego no detecta un `SMK64ROM.BIN` de otra compilación si es igual o más grande que el esperado.

Las últimas líneas del registro también aparecen en la pantalla de fallo, en cualquier compilación, junto con el `BUILD_ID` de la compilación. Si describes un problema, incluye la versión, el emulador o la consola y el cargador, el `BUILD_ID` y esas líneas.
