# Manual de usuario

Cómo jugar a Mario Kart 64 para PlayStation 2, en español. Para compilar o modificar el port, ver el [manual técnico](tecnico.md).

## Qué es

Un port de Mario Kart 64 (versión estadounidense) a PlayStation 2, con todo el texto que ve el jugador en español. La ISO ya trae el juego completo: no hace falta la ROM original. Es un proyecto sin fines de lucro, educativo y de preservación, sin afiliación con Nintendo ni con Sony (ver [Aviso legal](#aviso-legal)).

## Requisitos

Una de estas opciones:

- **PCSX2**, con una BIOS de PS2;
- **Play!**;
- **una PS2** con OPL o uLaunchELF (sin probar en hardware; ver [Limitaciones conocidas](#limitaciones-conocidas)).

La imagen es NTSC 480i: entrelazada a 640×448 y a 60 Hz (`codigo/graficos/sintetizador_gs.c`). El antiparpadeo, la posición y el formato 4:3 o 16:9 se ajustan en el menú [CONFIGURACIÓN Y TRUCOS](#configuración-y-trucos); con una consola PAL, ver [Consolas PAL y NTSC](#consolas-pal-y-ntsc). Para guardar la partida hace falta una Memory Card de PS2 formateada en la ranura 1.

## Descarga y comprobación

Los enlaces de descarga están en la [Descarga del README](../../README.md#2-qué-incluye-y-descarga-verificable). La Release publica tres archivos:

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

## Configuración y trucos

**Cómo llegar:** en la pantalla de título, START; en el menú principal, OPCIONES; y en OPCIONES, la quinta fila, CONFIGURACIÓN Y TRUCOS. Las cuatro filas originales de OPCIONES no cambian.

**Controles** (`codigo/menus/menus/tablas_menus.inc.c`):

| Botón | Acción |
|---|---|
| Arriba / abajo | Cambia de fila; se para en la primera y en la última |
| Izquierda / derecha | Cambia el valor de la fila |
| Cruz | Avanza el valor; sobre VOLVER, sale |
| Cuadrado | Sale a OPCIONES |

Los cambios se aplican al momento, salvo DESBLOQUEAR TODO (ver más abajo). Al salir, si cambiaste algo, las opciones se guardan en la Memory Card (ver [Archivo de opciones](#archivo-de-opciones-smk64cfgdat)).

**Filas** (valores por defecto en `incluir/sistema/opciones_port.h`):

| Fila | Valores | Por defecto | Qué hace |
|---|---|---|---|
| ANTIPARPADEO | NO, SÍ | NO | Mezcla cada línea con la vecina para que los textos y el marcador no tiemblen en una TV de tubo. Suaviza la imagen; en un emulador o en una TV moderna suele verse mejor en NO |
| POSICIÓN X | −32 a 32 | 0 | Desplaza la imagen en horizontal, para una TV que corta un borde |
| POSICIÓN Y | −16 a 16 | 0 | Desplaza la imagen en vertical |
| FORMATO | NORMAL, CON BANDAS, PANORÁMICO | CON BANDAS si la PS2 está configurada en 16:9; si no, NORMAL | Ver [Formato y TV 16:9](#formato-y-tv-169) |
| DESBLOQUEAR TODO | NO, SÍ | NO | Truco: el modo EXTRA (espejo) y los fantasmas del staff, sin ganarlos |
| OBJETO | NORMAL o un objeto (plátano, caparazones, rayo, estrella, champiñones…) | NORMAL | Truco: las cajas dan siempre ese objeto a los jugadores humanos |
| 200CC | NO, SÍ | NO | Truco: más velocidad en 150cc |
| RIVALES SIN VENTAJA | NO, SÍ | NO | Truco: la CPU no acelera de más cuando va por detrás |
| VOLVER | — | — | Vuelve a OPCIONES |

Todos los trucos vienen apagados.

### Formato y TV 16:9

El juego lee en la configuración de la PS2 si la TV es 16:9 (`TV_SCREEN_169`; la opción «pantalla completa» cuenta como 4:3).

| FORMATO | Para qué TV | Resultado |
|---|---|---|
| NORMAL | 4:3 | La imagen ocupa toda la pantalla, como siempre |
| CON BANDAS | 16:9 | La imagen conserva la proporción 4:3, centrada, con bandas negras a los lados. El dibujo del juego no cambia |
| PANORÁMICO | 16:9 | La carrera, la pantalla dividida y la ceremonia muestran más campo a los lados (Hor+). Los menús no cambian. El marcador de la carrera se estrecha para que la TV no lo estire, y en los bordes algún objeto o tramo de pista puede aparecer tarde |

Una TV 16:9 estira a lo ancho cualquier imagen 4:3: con NORMAL en esa TV, los personajes se ven anchos.

### Advertencias de los trucos

- **Los récords se guardan aunque haya trucos activos.** Un tiempo, un fantasma o un trofeo conseguidos con trucos quedan en la partida igual que los demás, sin marca. Si quieres conservar solo récords limpios, apaga los trucos antes de correr.
- **200CC** solo actúa en Gran Premio y Versus a 150cc; no en contrarreloj (desincronizaría los fantasmas) ni en batalla. Los resultados puntúan como 150cc, la pausa dice 150cc, y un cambio en mitad de una carrera se aplica en la siguiente.
- **OBJETO** no actúa en contrarreloj. En batalla, si el objeto elegido no existe en ese modo, la caja da la ruleta normal. La CPU no recibe el objeto elegido.
- **DESBLOQUEAR TODO** se aplica al cambiar de pantalla (al volver al título o al entrar en otro menú), no en la pantalla actual. Nunca escribe el desbloqueo en la partida: al apagarlo, EXTRA vuelve a ocultarse si no lo habías ganado, y los trofeos EXTRA conseguidos con el truco quedan guardados pero ocultos.
- **RIVALES SIN VENTAJA** solo tiene efecto en Gran Premio.

### Archivo de opciones (SMK64CFG.DAT)

Las opciones se guardan aparte de la partida, en `SMK64CFG.DAT`, dentro de la misma carpeta de la Memory Card (ver [Memory Card](#memory-card)). Ocupa 32 bytes, con versión y CRC32. El juego lo escribe al salir del menú solo si algo cambió. Si falta, está dañado o es de otra versión, el juego usa los valores por defecto; un valor fuera de rango se lleva a su valor por defecto. Borrarlo desde el navegador de la consola devuelve todo a los valores de fábrica sin tocar la partida.

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
| `SMK64CFG.DAT` | Opciones de imagen y trucos (ver [Archivo de opciones](#archivo-de-opciones-smk64cfgdat)) |
| `icon.sys`, `SMK64.ICO` | Icono del navegador de la consola (`herramientas/crear_icono.py`) |

Al arrancar se carga la copia válida más reciente. Si la tarjeta no responde en 5 s, medidos con el reloj, el juego sigue sin la partida y no guarda.

Si arrancas sin tarjeta y la insertas después, o cambias la tarjeta con el juego en marcha, antes del primer guardado el juego lee las dos copias de la tarjeta nueva. Escribe la partida sobre la copia más vieja y con una generación mayor que la de la más nueva: así no pisa la copia más nueva de esa tarjeta, y en el siguiente arranque carga la partida recién guardada. Si deja de responder más tarde, el juego deja de usarla hasta el siguiente arranque, en lugar de tomarla por una tarjeta nueva (`codigo/sistema/memory_card.c`). Los archivos `SMK64.SAV` y `SMK64.TMP` de versiones anteriores los lee y los borra el juego en el primer guardado.

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
- **Menú del port:** CONFIGURACIÓN Y TRUCOS, con el estilo y la fuente de OPCIONES; desde la 1.2.1, los valores se ven en amarillo opaco, como las etiquetas. La fuente no tiene «:» ni «/», por eso no escribo «16:9».
- **Fuente del menú:** 11 glifos nuevos (Á É Í Ó Ú Ñ Ü ¡ ¿ º ª), dibujados a partir de los originales; escribo los ordinales «1.º».
- **Texturas con texto:** 55 texturas (títulos de menú, botones, copas, número de jugadores, los 20 títulos de pista, el cartel de la granja, TIEMPO y VUELTA en el HUD, puestos «1.º»…«8.º» y PULSA START) y los 48 cuadros de los carteles de Lakitu (¡ÚLTIMA!, VUELTA 2 y ¡REVÉS!). En la 1.2.0 reconstruí el «º» de los puestos, VUELTA, los botones y copas de dos líneas y el título de la Pista de la Jungla DK (en la 1.2.1, el punto de los puestos pasa a ir antes de la «º», «8.º»), y traduje los carteles de pista con texto: BIENVENIDOS, YA (el GO de la Pista Mario), PASO A NIVEL (la señal de cruce del Desierto Kalimari) y los emblemas 1J a 4J. Salen de PNG versionados en `recursos/es/`, compuestos con letras de las propias texturas del juego. Las 1229 texturas del juego están clasificadas en el manifiesto `recursos/es/texturas.tsv`: traducidas, sin texto, logotipo o cartel comercial, o no visibles en el port.
- **Pantallas del port:** panel de rendimiento y página de audio (con tildes), nombres de fase, registro y guiones de prueba. La pantalla de fallo escribe con tildes («PARADA DE DIAGNÓSTICO») mediante `scr_putchar` de ps2sdk y los glifos CP437 de su fuente, que la CI comprueba en cada compilación.

**Qué no traduje:** nombres de personaje, logotipos y carteles comerciales, 50cc/100cc/150cc, VS, onomatopeyas, las voces (son muestras de audio) y las texturas de la pantalla del Controller Pak, que el port no puede abrir. El detalle está en la [especificación](../traduccion/especificacion.md#22-excluido).

Cómo comprobé la localización está en el [manual técnico](tecnico.md#pruebas).

## Limitaciones conocidas

Al 2026-10-13, versión 1.3.0:

- **Sin probar en PS2 real ni en una TV.** Tampoco con OPL ni uLaunchELF en hardware, ni con un multitap real. Según el autor del port original, lo probó en PCSX2 (con BIOS) y en Play!. Desde la 1.2.0, la CI arranca el juego en Play! en cada cambio y compara capturas del título, del menú, del menú de configuración y de la carrera con referencias aprobadas.
- **Verificado solo por los valores de los registros de vídeo:** el antiparpadeo, las bandas y la posición. Las capturas del emulador leen la memoria de vídeo antes de la salida a la TV, así que no los muestran. Falta comprobar en una TV cómo se ven.
- **Sin verificar en una consola real:**
  - el tacto del stick con la zona muerta de 8;
  - el multitap;
  - el cambio de Memory Card con el juego en marcha;
  - el rendimiento en PANORÁMICO, que dibuja más objetos por cuadro;
  - la lectura de la región en `rom0:ROMVER`: solo lo comprobé en Play! por la ruta con reinicio del IOP y con un ROMVER sintético; lanzado desde OPL sin reinicio, o con una BIOS real, no. Si falla, el registro dice «región de la consola desconocida» y el juego sigue igual.
- **PANORÁMICO:** en los bordes algún objeto o tramo de pista puede aparecer tarde.
- **Los trucos no marcan los récords** (ver [Advertencias de los trucos](#advertencias-de-los-trucos)).
- **Copiar fantasmas no está disponible:** en PS2 no hay otra tarjeta desde la que copiar, y el menú lo avisa.
- **La pantalla del Controller Pak:** el port no la abre y no traduje sus texturas.
- **Con una consola PAL hace falta una TV que acepte 60 Hz** (ver [Consolas PAL y NTSC](#consolas-pal-y-ntsc)).

## Solución de problemas

| Síntoma | Causa y solución |
|---|---|
| En pantalla: «falta SMK64ROM.BIN: usa la ISO completa (o el ELF monolitico con uLaunchELF)» | El ELF no encontró `SMK64ROM.BIN` en `host:` ni en el disco, o el del disco es más pequeño de lo que espera el ELF (de otra compilación). La pantalla muestra el texto sin tildes; en el registro sale `ROM: no se encontró \SMK64ROM.BIN;1 en el disco ...` o `ROM: \SMK64ROM.BIN;1 mide X y debería medir Y`. Usa la ISO completa o, con uLaunchELF, el ELF monolítico de la Release (`SLUS_999.99.monolitico.elf`) |
| En pantalla: «no se pudo leer SMK64ROM.BIN del disco» | Falló una lectura durante la carga tras 4 intentos de unos 6 s cada uno: imagen o disco dañado. Por `host:` también aparece si el archivo es más corto de lo esperado. En el registro sale `ROM: no se pudo leer SMK64ROM.BIN (trozo N)`. Comprueba la ISO con `SHA256SUMS` (ver [Descarga y comprobación](#descarga-y-comprobación)) y vuelve a descargarla si no coincide |
| La partida no se guarda | Hace falta una Memory Card de PS2 formateada en la ranura 1. Si la tarjeta dejó de responder, el juego no vuelve a usarla hasta el siguiente arranque. Con `DEBUG=1` o `DEV=1`, el registro muestra los mensajes `memory card:` |
| Con una consola PAL, la imagen no se ve bien | La TV no acepta NTSC a 60 Hz. Usa una TV que lo acepte (ver [Consolas PAL y NTSC](#consolas-pal-y-ntsc)) |
| La imagen tiembla en una TV de tubo | Activa ANTIPARPADEO en [CONFIGURACIÓN Y TRUCOS](#configuración-y-trucos) |
| La TV corta un borde de la imagen | Ajusta POSICIÓN X o POSICIÓN Y en [CONFIGURACIÓN Y TRUCOS](#configuración-y-trucos) |
| En una TV 16:9 los personajes se ven anchos | Usa FORMATO CON BANDAS o PANORÁMICO (ver [Formato y TV 16:9](#formato-y-tv-169)) |
| Las opciones vuelven a los valores por defecto | No se pudo leer o escribir `SMK64CFG.DAT`: comprueba la Memory Card de la ranura 1 (ver [Archivo de opciones](#archivo-de-opciones-smk64cfgdat)) |
| La carrera vuelve a 30 FPS | Tras tres tirones en una carrera, el modo 60 FPS se queda a 30 FPS hasta la siguiente (ver [60 FPS](#60-fps)). También se puede haber desactivado con R3 |

`SLUS_999.99` y `SMK64ROM.BIN` deben salir de la misma compilación. El juego no detecta un `SMK64ROM.BIN` de otra compilación si es igual o más grande que el esperado.

Las últimas líneas del registro también aparecen en la pantalla de fallo, en cualquier compilación, junto con el `BUILD_ID` de la compilación. Si describes un problema, incluye la versión, el emulador o la consola y el cargador, el `BUILD_ID` y esas líneas.

## Aviso legal

- **Sin fines de lucro.** Es un proyecto educativo, de preservación y de apoyo a la comunidad. No vendo nada, no cobro por descargarlo y no lleva publicidad.
- **Sin afiliación.** No está afiliado a Nintendo ni a Sony, ni respaldado por ellas. Mario Kart 64, sus personajes y sus marcas son de Nintendo; PlayStation 2 es una marca de Sony Interactive Entertainment.
- **Qué publico.** Publico la ISO y el ELF igual que en el repositorio original del port, [anthoo582/mario-kart-64-ps2](https://github.com/anthoo582/mario-kart-64-ps2). El trabajo se apoya en el port de anthoo582 y en el [proyecto de descompilación de Mario Kart 64](https://github.com/n64decomp/mk64); los créditos completos están en [creditos.md](creditos.md).
- **Licencia.** El repositorio original no declara licencia. Publico con licencia MIT solo mis aportes a este fork ([LICENSE](../../LICENSE)); el juego, sus recursos, la descompilación y el código del repositorio original quedan fuera.

El aviso completo está en la [portada del repositorio](../../README.md#aviso-legal).
