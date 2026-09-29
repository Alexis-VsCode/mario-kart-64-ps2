# Glosario de la traducción al español

Términos aprobados para el texto que ve el jugador y fuente de cada nombre oficial. Un término que no está aquí no está aprobado: quien lo necesite lo propone en [cambios.md](cambios.md), lo aprueba REVISIÓN y se añade a este glosario antes de que INTEGRACIÓN integre el bloque que lo usa.

- Qué hay que cumplir: [especificacion.md](especificacion.md).
- Cómo se trabaja: [plan.md](plan.md).
- Fuentes externas consultadas el 28-09-2026.

El texto del juego se cita por símbolo, no por número de línea. En `main`, las tablas de texto del menú están en `codigo/menus/elementos_menu/textos_y_tablas.inc.c`. Tras el refactor del bloque CADENAS (rama `idioma/cadenas`) pasan a `codigo/menus/elementos_menu/textos_menu.inc.c`, con los mismos nombres.

## 1. Criterios

### 1.1 Variante y tratamiento

- **Variante:** español neutro con tuteo, con la terminología oficial de Nintendo España.
- **Excepción decidida:** GRAN PREMIO en lugar de «Grand Prix» (ver 2.1).
- **Tuteo:** los imperativos van en segunda persona del singular: ELIGE, PULSA.
- **Botones:** se nombran los de PS2, según la función `convertir` de `codigo/entrada/mandos.c`:

  | Botón de N64 | Botón de PS2 |
  |---|---|
  | A | CRUZ |
  | B | CUADRADO |
  | L | SELECT |
  | R | R1 (R2 hace lo mismo) |
  | START | START |

### 1.2 Ortografía

- **Mayúsculas con tilde.** La fuente del menú dibuja minúsculas y mayúsculas con el mismo glifo (`car_a_indice_glifo`), así que todo sale en mayúsculas. Las tildes, la Ñ y la Ü son obligatorias: CLASIFICACIÓN, CHAMPIÑÓN, ESTÉREO.
- **¡ y ¿ obligatorios:** ¡VICTORIA!, ¿OK?
- **Ordinales:** número, punto y letra volada, sin espacio.
  - Masculino: 1.º … 8.º.
  - Femenino: 2.ª (2.ª VUELTA).
  - No quedan ST, ND, RD ni TH. Detalle en R-TXT-07 de [especificacion.md](especificacion.md).
- **Signos que no existen en la fuente del menú:** `)`, `:`, `;`, `/` y `%` no tienen glifo, y `(` se dibuja como «cc» (`car_a_indice_glifo`). No se usan. Se escribe «RANURA 1», no «RANURA: 1».
  - Signos disponibles: `! ? - ' " . , * + $`, las cifras y las letras.
- **Se escriben igual:** VS, OK, TOTAL, EXTRA, START, SELECT, R1 y MEMORY CARD.

### 1.3 Caracteres especiales

Los caracteres Á É Í Ó Ú Ñ Ü ¡ ¿ º ª los resuelve `incluir/sistema/caracteres_es.h`, junto con `codigo/sistema/caracteres_es.c` (rama `idioma/fuente`, desde el commit 9e6bec7).

- Las cadenas se escriben en UTF-8 legible.
- El conversor del build (`herramientas/convertir_eucjp.py`) las pasa a EUC-JP.
- En EUC-JP, estos caracteres son de JIS X 0212 y ocupan 3 bytes (`8F xx xx`):
  - fila `AA`: mayúsculas;
  - fila `AB`: minúsculas;
  - fila `A2`: ¡ ¿ º ª.
- `leer_caracter_es` acepta mayúsculas y minúsculas. Por eso los nombres de pista pueden seguir en minúsculas en su archivo.

### 1.4 Longitud

- **Long.:** número de caracteres, con espacios y signos. Una letra con tilde o una Ñ cuenta como 1. Es una cifra orientativa.
- **Bytes:** cada carácter especial ocupa 3 bytes. «Copa Champiñón» tiene 14 caracteres y 18 bytes.
- **Límite real en cadenas:** el ancho en pantalla medido por tinta (`ancho_pantalla_glifo`, `obtener_ancho_cadena` y la prueba de R-TXT-04).
- **Límite real en texturas:** el tamaño en píxeles de cada textura.

### 1.5 Niveles de confianza (sección 3)

| Nivel | Criterio |
|---|---|
| **Alta** | Una página oficial de Nintendo en español nombra esa pista (la de N64 o una reedición suya) o ese término. |
| **Media** | Super Mario Wiki (SMW) da el nombre con referencia a capturas del juego, o SMW coincide con al menos una fuente secundaria independiente: una guía, Wikipedia en español o una publicación que transcribe el nombre del juego. |
| **Baja** | Hay una sola fuente sin referencia, o no existe nombre oficial y la entrada es una propuesta. |

## 2. Términos del juego

**Cómo leer las tablas:**

- **CADENAS:** tablas de texto del código, citadas por símbolo.
- **TEXTURAS:** imágenes con el texto dibujado. Las de menú se citan por su identificador en el manifiesto `recursos/es/texturas.tsv` (rama `idioma/texturas`). Las del HUD y las demás, por el nombre de su archivo.
- **Rutas de las texturas:**
  - texturas de menú: `recursos/texturas/menus/tkmk00/<id>.rgba16.tkmk00`;
  - texturas del HUD: `recursos/comunes/texturas/<id>.<formato>.inc.c`.

Todos los términos de esta sección los decidió el responsable del proyecto.

### 2.1 Modos y copas

| Inglés | Español | Dónde aparece | Nota |
|---|---|---|---|
| MARIO GP | GRAN PREMIO | TEXTURAS: `modo_mario_gp` (64×18 px) | Ver la nota GRAN PREMIO debajo de la tabla. |
| T.TRIALS | CONTRARRELOJ | TEXTURAS: `modo_contrarreloj` | Igual que Nintendo ES ([MK World][mkw-es], [MK8 Deluxe][mk8dx]) y el [manual de MK7][mk7-manual]. |
| VS | VS | TEXTURAS: `modo_vs`, que no cambia. CADENAS: `dato_800E7778[0]` | Nintendo ES escribe «Carrera VS.» ([MK World][mkw-es], [MK8 Wii U][mk8-wiiu]). En la textura y en los rótulos cortos queda VS. |
| BATTLE | BATALLA | TEXTURAS: `batalla_modo`. CADENAS: `nombres_copa[4]`, `dato_800E7778[1]`, `introduccion_batalla_texto[0]` | Nintendo ES ([MK8 Deluxe][mk8dx]). |
| MUSHROOM / FLOWER / STAR / SPECIAL CUP | COPA CHAMPIÑÓN / COPA FLOR / COPA ESTRELLA / COPA ESPECIAL | CADENAS: `nombres_copa[0..3]` y `nombres_copa[5..8]`. TEXTURAS: `menu_copa_hongo`, `menu_copa_flor`, `menu_copa_estrella`, `menu_copa_especial` (65×40 px, «COPA» y el nombre en dos líneas) | Nintendo ES ([MK8 Deluxe][mk8dx]). |

**Nota sobre GRAN PREMIO:**

- Nintendo usa «Grand Prix» en España y en Latinoamérica ([MK World ES][mkw-es], [MK World MX][mkw-mx], [manual de MK7][mk7-manual]). Se eligió la forma española.
- Si «GRAN PREMIO» no cabe en la textura, queda «MARIO GP» y se registra en [cambios.md](cambios.md).
- **Pendiente:** el manifiesto de la rama `idioma/texturas` todavía marca `modo_mario_gp` como no traducida, con el motivo «nombre del modo». Hay que alinearlo con esta decisión.

### 2.2 Carrera, tiempos y HUD

| Inglés | Español | Dónde aparece | Nota |
|---|---|---|---|
| LAP | VUELTA | CADENAS: `texto_tiempo_prefijo[0..2]` («LAP 1» pasa a «VUELTA 1»). TEXTURAS del HUD: `vuelta_hud` y `tiempo_vuelta_hud` | En el HUD, palabra completa. Solo se abrevia en pantalla dividida si no cabe, y se registra en [cambios.md](cambios.md). |
| TIME | TIEMPO | TEXTURAS del HUD: `tiempo_hud` | Palabra completa. |
| BEST RECORDS | RÉCORDS | CADENAS: `texto_tiempo_mejor[0]` | Nintendo ES: «Bate tus propios récords» ([MK World][mkw-es]). |
| BEST LAP | MEJOR VUELTA | CADENAS: `texto_tiempo_mejor[1]` | |
| LAP TIME | TIEMPOS DE VUELTA | CADENAS: `texto_tiempo_vuelta` | |
| FINAL LAP | ÚLTIMA VUELTA. En el cartel de Lakitu: ¡ÚLTIMA! | TEXTURAS: Lakitu `vuelta_final` | Ninguna cadena contiene FINAL LAP. |
| 2nd LAP | 2.ª VUELTA | TEXTURAS: Lakitu `segunda_vuelta` | |
| REVERSE | ¡AL REVÉS! | TEXTURAS: Lakitu `marcha_atras` | |
| 1st … 8th (sufijos st, nd, rd, th) | 1.º … 8.º | CADENAS: `texto_lugar[1..8]`, `dato_800E7744[0..4]` («1 ｓ» … «5 ｔ») y los literales «1 ｓ ー», «2 ｎ ー» y «3 ｒ ー» de `funcion_800A6E94` (`codigo/menus/elementos_menu/menus_pausa.inc.c`). TEXTURAS del HUD: `hud_1ro` … `hud_8vo` (`comun_textura_hud_lugar`) | `primer_lugar` … `cuarto_lugar` (`dato_0D015258`) solo tienen la cifra y no cambian. |
| YOU PLACED | HAS QUEDADO | CADENAS: `texto_lugar[0]` | En pantalla: HAS QUEDADO 1.º. |

**Carteles de Lakitu:**

- Los textos ¡ÚLTIMA!, 2.ª VUELTA y ¡AL REVÉS! son los del plan; el detalle está en R-TEX-06 de [especificacion.md](especificacion.md).
- No hay texto oficial equivalente. Desde *Double Dash!!* el aviso de sentido contrario es una flecha. Desde *Mario Kart 7*, el cartel de vuelta muestra la vuelta actual sobre el total ([SMW – Lakitu][smw-lakitu]).
- Si se quiere proponer otro texto, se registra como discrepancia para REVISIÓN.

### 2.3 Pistas, pilotos y fantasmas

| Inglés | Español | Dónde aparece | Nota |
|---|---|---|---|
| COURSE, MAP | PISTA | CADENAS: `boton_pausa_texto[2]`, `texto_menu_anuncio_fantasma`, `opcion_menu_texto[1..2]`, `borrar_mejor_fantasma_texto`. TEXTURAS: `seleccion_mapa` | El [manual de MK7][mk7-manual] usa «pistas». Los nombres de cada pista, en la sección 3. |
| DRIVER, PLAYER | PILOTO | CADENAS: `boton_pausa_texto[3]` y el literal «driver's points» de `funcion_800A34A8` (`info_pistas_y_tiempos.inc.c`). TEXTURAS: `seleccion_jugador` | Nintendo ES: «24 pilotos» ([MK World][mkw-es]). |
| GHOST | FANTASMA | CADENAS: `boton_pausa_texto[6]`, `texto_menu_anuncio_fantasma`, `opcion_menu_texto[2]` y los mensajes de fantasma (`dato_800E798C`, `dato_800E7A74`, `dato_800E7A80`). TEXTURAS: `fantasma_menu` | Nintendo ES: «corredores fantasma» ([MK World][mkw-es]). [Manual de MK7][mk7-manual]: «corredor fantasma». |
| SAVE (un fantasma) | GRABAR | CADENAS: `boton_pausa_texto[6]` («SAVE GHOST»), `dato_800E7A74` («SAVING GHOST DATA»), `dato_800E7A80` («UNABLE TO SAVE THE GHOST») | Se usa cuando lo que se guarda es un fantasma. |
| SAVE (datos) | GUARDAR | CADENAS: `dato_800E7878` y `dato_800E7884` («ALL SAVED DATA…») | Se usa cuando lo que se guarda son los datos de la partida. |

### 2.4 Pausa, resultados y opciones

| Inglés | Español | Dónde aparece | Nota |
|---|---|---|---|
| CONTINUE GAME | CONTINUAR | CADENAS: `boton_pausa_texto[0]` | |
| RETRY | REINTENTAR | CADENAS: `boton_pausa_texto[1]` | |
| COURSE CHANGE | CAMBIAR PISTA | CADENAS: `boton_pausa_texto[2]` | |
| DRIVER CHANGE | CAMBIAR PILOTO | CADENAS: `boton_pausa_texto[3]` | |
| QUIT, EXIT | SALIR | CADENAS: `boton_pausa_texto[4]`, `dato_800E7840[0]`, `dato_800E7930[0]`, `dato_800E7A6C[0]`, `datos_menu_texto` («B BUTTON*EXIT») | |
| REPLAY | REPETICIÓN | CADENAS: `boton_pausa_texto[5]` | |
| RANKING | CLASIFICACIÓN | CADENAS: `dato_800E7778` («VS MATCH RANKING», «BATTLE RANKING») | El [manual de MK7][mk7-manual] usa «clasificación». |
| results | RESULTADOS | CADENAS: literal de `funcion_800A2EB8` (`info_pistas_y_tiempos.inc.c`) | Pasa a una tabla con nombre en el bloque B3. |
| round | RONDA | CADENAS: literales de `funcion_800A2EB8` y `funcion_800A34A8` | Pasa a una tabla con nombre en el bloque B3. |
| WINNER! / LOSER! | ¡VICTORIA! / ¡DERROTA! | CADENAS: `texto_perder_victoria` | |
| SOUND MODE | SONIDO | CADENAS: `menu_opcion_texto[1]` | |
| STEREO / HEADPHONE / MONO | ESTÉREO / AURICULARES / MONO | CADENAS: `sonido_nombres_modo` | `depuracion_sonido_modo_nombres` pertenece al menú de depuración de la N64: se traduce solo en ASCII (bloque B7), sin tilde. |
| the end | FIN | CADENAS: `texto_creditos` (`codigo/ceremonia/creditos.c`) | |
| staff («mariokart64 staff») | EQUIPO | CADENAS: `texto_creditos` | |

### 2.5 Memory Card y botones

| Inglés | Español | Dónde aparece | Nota |
|---|---|---|---|
| N64 CONTROLLER PAK | MEMORY CARD | CADENAS: `menu_opcion_texto[2]`, `dato_800E7890`, `dato_800E78D0`, `dato_800E7900`, `dato_800E7940`, `dato_800E7980`, `dato_800E798C` | Nombre del periférico de Sony. Se deja en inglés. |
| CONTROLLER 1 / CONTROLLER 2 (en los mensajes de guardado) | RANURA 1 / RANURA 2 | CADENAS: `dato_800E7890`, `dato_800E78D0`, `dato_800E7900`, `dato_800E7918`, `dato_800E7940`, `dato_800E7980`, `dato_800E798C` | |
| a BUTTON, B BUTTON | CRUZ, CUADRADO | CADENAS: `datos_menu_texto` | Según `convertir` (`codigo/entrada/mandos.c`). |
| L, R (en las texturas) | SELECT, R1 | TEXTURAS: `opcion_l`, `datos_r` | Según `convertir` (`codigo/entrada/mandos.c`). |

### 2.6 Texturas de menú

| Textura | Inglés | Español |
|---|---|---|
| `seleccion_juego` | GAME SELECT | ELIGE MODO |
| `seleccion_jugador` | PLAYER SELECT | ELIGE PILOTO |
| `seleccion_mapa` | MAP SELECT | ELIGE PISTA |
| `opcion` | OPTION | OPCIONES |
| `opcion_l` | L OPTION | SELECT OPCIONES |
| `datos_r` | R DATA | R1 DATOS |
| `empezar` | BEGIN | EMPEZAR |
| `datos` | DATA | DATOS |
| `fantasma_menu` | GHOST | FANTASMA |
| `ok` | OK? | ¿OK? |
| `juego_menu_1j` … `juego_menu_4j` | 1P GAME … 4P GAME | 1 JUG. … 4 JUG. |
| `empezar_boton_empuje` (`recursos/texturas/sin_comprimir/`, 159×16 px) | PUSH START BUTTON | PULSA START |

## 3. Nombres oficiales de pistas, arenas y copas

Estos nombres son la decisión del proyecto. El plan pide los nombres oficiales de Nintendo en español con su fuente citada.

- **Variante latinoamericana:** donde hay una documentada, va en «Nota».
- **Prefijo:** se quita «N64» de los nombres de las pistas retro.
- **Long. EN:** longitud de la cadena inglesa actual. Para pistas y arenas, en `recursos/pistas/metadatos/nombres_circuito.inc.c`; para copas, en `nombres_copa[]`.
- **Índice:** posición, empezando en 0, en `nombres_circuito.inc.c`.

### 3.1 Pistas de carrera

| Índice | Inglés | Español | Long. ES / EN | Fuente | Confianza | Nota |
|---|---|---|---|---|---|---|
| 0 | Mario Raceway | Pista Mario | 11 / 13 | [SMW][smw-mario]; [guía MK Wii, Copa Caparazón][guia-caparazon]; [Wikipedia ES – MK Wii][wp-mkwii] | Media | LatAm: igual que ES. Solo en MK Wii LatAm aparece «Pista de Mario». |
| 1 | Choco Mountain | Monte Chocolate | 15 / 14 | [Nintendo ES – MK8 Deluxe][mk8dx] (Copa Turbo Dorada); [SMW][smw-choco] | Alta | |
| 2 | Bowser's Castle | Castillo de Bowser | 18 / 15 | [SMW][smw-bowser]; [guía MK Wii, Copa Centella][guia-centella]; [Wikipedia ES – MK Wii][wp-mkwii] | Media | |
| 3 | Banshee Boardwalk | Muelle Embrujado | 16 / 17 | [SMW][smw-banshee]; [Sopla el Cartucho, retro de MK DS][blog-mkds] | Media | |
| 4 | Yoshi Valley | Valle de Yoshi | 14 / 12 | [Nintendo ES – MK8 Deluxe][mk8dx] («N64 Valle de Yoshi»); [SMW][smw-yoshi] | Alta | |
| 5 | Frappe Snowland | Circuito Nevado | 15 / 15 | [SMW][smw-frappe]; [Sopla el Cartucho, retro de MK DS][blog-mkds] | Media | |
| 6 | Koopa Troopa Beach | Playa Koopa | 11 / 18 | [SMW][smw-koopa]; [Wikipedia ES – MK7][wp-mk7] | Media | |
| 7 | Royal Raceway | Pista Real | 10 / 13 | [Nintendo ES – MK8 Deluxe][mk8dx] («N64 Pista Real»); [SMW][smw-royal] | Alta | |
| 8 | Luigi Raceway | Pista Luigi | 11 / 13 | [SMW][smw-luigi]; [Wikipedia ES – MK7][wp-mk7] | Media | |
| 9 | Moo Moo Farm | Granja Mu-Mu | 12 / 12 | [SMW][smw-moo]; [Sopla el Cartucho, retro de MK DS][blog-mkds] | Media | |
| 10 | Toad's Turnpike | Autopista Toad | 14 / 15 | [Nintendo ES – MK8 Deluxe][mk8dx] («N64 Autopista Toad»); [SMW][smw-toad] | Alta | |
| 11 | Kalimari Desert | Desierto Kalimari | 17 / 15 | [Nintendo ES – MK8 Deluxe][mk8dx] (Copa Nabo); [SMW][smw-kalimari] | Alta | |
| 12 | Sherbet Land | Tierra Sorbete | 14 / 12 | [SMW][smw-sherbet]; [guía MK Wii, Copa Plátano][guia-platano]; [Wikipedia ES – MK Wii][wp-mkwii] | Media | Nintendo ES usa el mismo nombre para la Sherbet Land de GameCube ([MK8 Deluxe][mk8dx]). |
| 13 | Rainbow Road | Senda Arco Iris | 15 / 12 | [Nintendo ES – MK8 Deluxe][mk8dx] («N64 Senda Arco Iris»); [SMW][smw-rainbow] | Alta | |
| 14 | Wario Stadium | Estadio Wario | 13 / 13 | [SMW][smw-wario], con referencias a capturas de *Mario Kart World* en español de España y de Latinoamérica | Media | LatAm: igual que ES. |
| 18 | D.K.'s Jungle Parkway | Pista de la Jungla DK | 21 / 21 | [SMW][smw-dk]; [guía MK Wii, Copa Hoja][guia-hoja] | Media | LatAm (SMW, sin referencia): «Jungla de DK». |

### 3.2 Arenas de batalla

| Índice | Inglés | Español | Long. ES / EN | Fuente | Confianza | Nota |
|---|---|---|---|---|---|---|
| 15 | Block Fort | Ciudad Bloque | 13 / 10 | [SMW][smw-block], sin referencia | Baja | SMW indica que comparte nombre con Block City (GameCube). |
| 16 | Skyscraper | Rascacielos | 11 / 10 | [SMW][smw-sky]; [Wikipedia ES – MK Wii][wp-mkwii] («N64 Rascacielos») | Media | |
| 17 | Double Deck | Doble Piso | 10 / 11 | [SMW][smw-double] no da nombre en español | Baja (propuesta) | Según SMW, es la única pista de MK64 que no ha vuelto en ningún juego posterior. No tiene nombre oficial. |
| 19 | Big Donut | Gran Donut | 10 / 9 | [SMW][smw-donut], con referencia a capturas de *Mario Kart World* en español de España | Media | LatAm: «Rosca Enorme» (SMW, con referencia). |

### 3.3 Copas

| Posición en `nombres_copa[]` | Inglés | Español | Long. ES / EN | Fuente | Confianza |
|---|---|---|---|---|---|
| 0 y 5 | mushroom cup | Copa Champiñón | 14 / 12 (18 bytes) | [Nintendo ES – MK8 Deluxe][mk8dx]; [Nintendo ES – MK World][mkw-es] | Alta |
| 1 y 6 | flower cup | Copa Flor | 9 / 10 | [Nintendo ES – MK8 Deluxe][mk8dx]; [Nintendo ES – MK World][mkw-es] | Alta |
| 2 y 7 | star cup | Copa Estrella | 13 / 8 | [Nintendo ES – MK8 Deluxe][mk8dx]; [Nintendo ES – MK World][mkw-es] | Alta |
| 3 y 8 | special cup | Copa Especial | 13 / 11 | [Nintendo ES – MK8 Deluxe][mk8dx] | Alta |
| 4 | battle | Batalla | 7 / 6 | [Nintendo ES – MK8 Deluxe][mk8dx] | Alta |

### 3.4 Recuento de longitudes

Doce nombres oficiales son más largos que la cadena inglesa a la que sustituyen:

| Grupo | Nombre | Caracteres de más |
|---|---|---|
| Pistas y arenas (9) | Desierto Kalimari | +2 |
| | Monte Chocolate | +1 |
| | Tierra Sorbete | +2 |
| | Castillo de Bowser | +3 |
| | Valle de Yoshi | +2 |
| | Senda Arco Iris | +3 |
| | Gran Donut | +1 |
| | Ciudad Bloque | +3 |
| | Rascacielos | +1 |
| Copas en `nombres_copa[]` (3) | Copa Champiñón | +2 |
| | Copa Estrella | +5 |
| | Copa Especial | +2 |

Además:

- «Batalla» (`nombres_copa[4]`) tiene un carácter más que «battle».
- Ningún nombre de pista pasa de 21 caracteres, que es el máximo actual («d.k.'s jungle parkway»).
- Ningún nombre de pista o arena lleva caracteres especiales. Entre las copas, solo «Copa Champiñón».

### 3.5 Discrepancias entre fuentes

- **Rainbow Road:** Nintendo escribe «Senda Arco Iris», en dos palabras. No se usa «Arcoíris».
- **D.K.'s Jungle Parkway:** [Wikipedia ES – MK Wii][wp-mkwii] escribe «Pista de la Jungla de DK». Se usa «Pista de la Jungla DK», la forma de la [guía de MK Wii][guia-hoja] y de SMW.
- **Kalimari Desert:** [Wikipedia ES – MK7][wp-mk7] escribe «Kalamari». Es una errata: Nintendo ES escribe «Kalimari».
- **Moo Moo Farm:** el guion de «Mu-Mu» sigue el de «Pradera Mu-Mu», que aparece en la página oficial de [MK8 Deluxe][mk8dx].
- **Wikipedia ES – Mario Kart 64:** en su texto usa formas no oficiales: «Granja Moo Moo», «Autopista de Toad», «Circuito Real» y «Desierto de Kalimari» ([artículo][wp-mk64]). Se descartan porque Nintendo ES o las guías usan otras.
- **MARIO GP:** ver la nota de GRAN PREMIO en 2.1.

### 3.6 Dónde se usan los nombres

| Qué | Tipo | Ubicación | Límite |
|---|---|---|---|
| Nombres de pista y arena | CADENAS | `recursos/pistas/metadatos/nombres_circuito.inc.c`: 20 entradas en minúsculas, en el orden del índice. Se incluye en `nombres_circuito[]`, `duplicar_nombres_circuito[]` y `duplicar_nombres_circuito_2[]`. En `idioma/infra` (commit ecbfd5c), este archivo pasa por la conversión a EUC-JP como el resto del texto. | Ancho por tinta (R-TXT-04). Se conservan el número y el orden de las entradas. |
| Nombres de copa | CADENAS | `nombres_copa[]`: 9 entradas. Las copas están en 0-3 y se repiten en 5-8; «battle» está en 4. | Igual que la fila anterior. |
| Títulos de pista | TEXTURAS | Los 20 `recursos/texturas/menus/tkmk00/titulo_*.rgba16.tkmk00` | 140×18 px cada uno. |
| Cartel de la granja (MOO MOO FARM → GRANJA MU-MU) | TEXTURAS | `recursos/texturas/pistas/moo_moo_farm/izquierda_cartel.mio0` y `derecha_cartel.mio0`, que se incluyen como `textura_moo_moo_farm_izquierda_cartel` y `textura_moo_moo_farm_derecha_cartel` en `codigo/datos/otras_texturas.s`. Sus tamaños comprimido (`file_size`) y descomprimido (`data_size`) están en `moo_moo_farm_texturas[]` (`recursos/pistas/moo_moo_farm/desplazamientos.c`). | Dos mitades de 64×32 px. |
| Copas | TEXTURAS | `menu_copa_hongo`, `menu_copa_flor`, `menu_copa_estrella`, `menu_copa_especial` | 65×40 px, en dos líneas. |
| Modos | TEXTURAS | `modo_mario_gp`, `modo_contrarreloj`, `batalla_modo`. `modo_vs` no cambia. | 64×18 px. |
| Carteles de Lakitu | TEXTURAS | El texto está en los píxeles de `recursos/texturas/lakitu/vuelta_final/`, `segunda_vuelta/` y `marcha_atras/`: 16 cuadros `.bin` por cartel, que se incluyen con `.incbin` en `codigo/datos/otras_texturas.s`. Símbolos: `textura_lakitu_vuelta_final_01..16`, `textura_lakitu_segundo_vuelta_01..16` y `textura_lakitu_reversa_01..16` (`incluir/datos/otras_texturas.h`). Las paletas `tlut_lakitu_*` no cambian. | Los 16 cuadros y la paleta existente (R-TEX-06). |
| Ordinales | CADENAS | `texto_lugar[1..8]`, `dato_800E7744[0..4]` y los literales de `funcion_800A6E94` | Ancho por tinta. |
| Ordinales | TEXTURAS | `hud_1ro` … `hud_8vo` | Tamaño de cada textura. |
| Vuelta y tiempo | CADENAS | `texto_tiempo_prefijo[0..2]`, `texto_tiempo_mejor`, `texto_tiempo_vuelta` | Ancho por tinta. |
| Vuelta y tiempo | TEXTURAS | `vuelta_hud`, `tiempo_vuelta_hud`, `tiempo_hud` | Se amplían sin solaparse con lo que se dibuja al lado (R-TEX-05). |

## 4. Lo que no se traduce

| Qué | Dónde | Por qué |
|---|---|---|
| Nombres de personaje | TEXTURAS: `nombre_*` (8). CADENAS: `dato_800E76A8` (MARIO … BOWSER, D.K.) y `nombres_personaje_depuracion` | Son nombres propios. Nintendo ES usa los mismos nombres para estos ocho personajes ([MK8 Deluxe][mk8dx]). |
| Marcas y logotipos | «MARIO KART 64» en los mensajes (por ejemplo, `dato_800E7A48`) y carteles de marca de las pistas (por ejemplo, `cartel_nintendo_*` en `recursos/texturas/generales/`). También MEMORY CARD, START y SELECT. | Son marcas o nombres de producto. |
| © | `recursos/texturas/sin_comprimir/copyright_1996.rgba16` («© 1996 Nintendo») | Es el aviso legal. |
| cc | TEXTURAS: `50cc`, `100cc`, `150cc`. CADENAS: `dato_800E76CC` y `dato_800E76DC` («50(», «100(», «150(»; el `(` se dibuja como «cc») | Es una unidad. «extra» se escribe igual. |
| Onomatopeyas | `recursos/texturas/efectos/onomatopeyas/` | Son efectos de sonido dibujados. |
| Pantalla del Controller Pak | Texturas ia16 de `recursos/texturas/generales/`. Todavía no están en el manifiesto de la rama `idioma/texturas`; el plan pide registrarlas allí con su motivo. | En el port no se puede abrir: `funcion_80091D74` devuelve 0 porque `situaciones_mando[0].status` vale 0, ya que `codigo/entrada/mandos.c` lo pone a cero con `memset`. Sus cadenas sí se traducen, porque cuesta poco; sus texturas no. |
| Otros textos que se escriben igual o no se ven | `modo_vs` (VS); TOTAL (`texto_tiempo_prefijo[3]`, `tiempo_total_hud`); «Km/h» (`velocimetro`); `vuelta_1_hud_en_3` … `vuelta_3_hud_en_3`, que solo muestran «1/3» … «3/3»; `menu_con_item` y `menu_sin_item`, que nunca se muestran | Iguales en español, unidades, cifras sin texto o texto inalcanzable. |
| Créditos en japonés | La mitad japonesa de `texto_creditos` (63 entradas) | Se conservan tal cual. |

## Fuentes

- Nintendo España – Mario Kart 8 Deluxe: <https://www.nintendo.com/es-es/Juegos/Juegos-de-Nintendo-Switch/Mario-Kart-8-Deluxe-1173281.html>
- Nintendo España – Mario Kart World: <https://www.nintendo.com/es-es/Juegos/Juegos-de-Nintendo-Switch-2/Mario-Kart-World-2790000.html>
- Nintendo España – Mario Kart 8 (Wii U): <https://www.nintendo.com/es-es/Juegos/Juegos-de-Wii-U/Mario-Kart-8-765384.html>
- Nintendo México – Mario Kart World: <https://www.nintendo.com/es-mx/store/products/mario-kart-world-switch-2/>
- Manual electrónico de Mario Kart 7 (ES): <https://www.nintendo.com/eu/media/downloads/games_8/emanuals/nintendo_3ds_2/mario_kart_7/ElectronicManual_Nintendo3DS_MarioKart7_ES.pdf>
- Guías Nintendo – Mario Kart Wii: copas [Caparazón][guia-caparazon], [Plátano][guia-platano], [Hoja][guia-hoja] y [Centella][guia-centella].
- Wikipedia en español: [Mario Kart 7][wp-mk7], [Mario Kart Wii][wp-mkwii] y [Mario Kart 64][wp-mk64].
- Sopla el Cartucho, «Circuitos retro en Mario Kart DS» (2008): <http://soplaelcartucho.blogspot.com/2008/03/circuitos-retro-en-mario-kart-ds.html>
- Super Mario Wiki: apartado «Names in other languages» de cada pista, enlazado en las tablas, y [Lakitu (Mario Kart referee)][smw-lakitu].

[mk8dx]: https://www.nintendo.com/es-es/Juegos/Juegos-de-Nintendo-Switch/Mario-Kart-8-Deluxe-1173281.html
[mkw-es]: https://www.nintendo.com/es-es/Juegos/Juegos-de-Nintendo-Switch-2/Mario-Kart-World-2790000.html
[mk8-wiiu]: https://www.nintendo.com/es-es/Juegos/Juegos-de-Wii-U/Mario-Kart-8-765384.html
[mkw-mx]: https://www.nintendo.com/es-mx/store/products/mario-kart-world-switch-2/
[mk7-manual]: https://www.nintendo.com/eu/media/downloads/games_8/emanuals/nintendo_3ds_2/mario_kart_7/ElectronicManual_Nintendo3DS_MarioKart7_ES.pdf
[wp-mk7]: https://es.wikipedia.org/wiki/Mario_Kart_7
[wp-mkwii]: https://es.wikipedia.org/wiki/Mario_Kart_Wii
[wp-mk64]: https://es.wikipedia.org/wiki/Mario_Kart_64
[guia-caparazon]: https://www.guiasnintendo.com/2a_WII/mario_kart_wii/mario_kart_wii_sp/copacaparazon.html
[guia-platano]: https://www.guiasnintendo.com/2a_WII/mario_kart_wii/mario_kart_wii_sp/copaplatano.html
[guia-hoja]: https://www.guiasnintendo.com/2a_WII/mario_kart_wii/mario_kart_wii_sp/copahoja.html
[guia-centella]: https://www.guiasnintendo.com/2a_WII/mario_kart_wii/mario_kart_wii_sp/copacentella.html
[blog-mkds]: http://soplaelcartucho.blogspot.com/2008/03/circuitos-retro-en-mario-kart-ds.html
[smw-lakitu]: https://www.mariowiki.com/Lakitu_(Mario_Kart_referee)
[smw-mario]: https://www.mariowiki.com/Mario_Raceway
[smw-choco]: https://www.mariowiki.com/Choco_Mountain
[smw-bowser]: https://www.mariowiki.com/Bowser%27s_Castle_(Mario_Kart_64)
[smw-banshee]: https://www.mariowiki.com/Banshee_Boardwalk
[smw-yoshi]: https://www.mariowiki.com/Yoshi_Valley
[smw-frappe]: https://www.mariowiki.com/Frappe_Snowland
[smw-koopa]: https://www.mariowiki.com/Koopa_Troopa_Beach_(Mario_Kart_64)
[smw-royal]: https://www.mariowiki.com/Royal_Raceway
[smw-luigi]: https://www.mariowiki.com/Luigi_Raceway
[smw-moo]: https://www.mariowiki.com/Moo_Moo_Farm
[smw-toad]: https://www.mariowiki.com/Toad%27s_Turnpike
[smw-kalimari]: https://www.mariowiki.com/Kalimari_Desert
[smw-sherbet]: https://www.mariowiki.com/Sherbet_Land_(Mario_Kart_64)
[smw-rainbow]: https://www.mariowiki.com/Rainbow_Road_(Mario_Kart_64)
[smw-wario]: https://www.mariowiki.com/Wario_Stadium_(Mario_Kart_64)
[smw-dk]: https://www.mariowiki.com/DK%27s_Jungle_Parkway
[smw-block]: https://www.mariowiki.com/Block_Fort
[smw-sky]: https://www.mariowiki.com/Skyscraper
[smw-double]: https://www.mariowiki.com/Double_Deck
[smw-donut]: https://www.mariowiki.com/Big_Donut
