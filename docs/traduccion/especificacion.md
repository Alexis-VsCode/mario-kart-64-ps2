# Especificación: Mario Kart 64 PS2 en español

- **Estado:** F0 en revisión.
- **Sincronizada con** las ramas publicadas el 2026-09-28: `idioma/infra` (`a3d0bae`), `idioma/fuente` (`641fe27`) e `idioma/texturas` (`236962b`). `idioma/cadenas`, `idioma/port` y el arte de `idioma/texturas` están en curso y sin publicar.

## 1. Objetivo

Todo texto que aparece en pantalla en el port debe estar en español correcto:

- menús, pausa, resultados, fantasmas, Memory Card, ceremonia y créditos;
- HUD, carteles de Lakitu y títulos de pista;
- pantallas propias del port.

Además, cada texto:

- usa tildes, Ñ, Ü, ¡, ¿ y ordinales «1.º» cuando corresponde;
- usa la terminología del [glosario](glosario.md);
- no se sale del espacio donde se dibuja;
- se puede comprobar con pruebas que corren en el PC.

## 2. Alcance

### 2.1 Incluido

| Área | Qué | Dónde |
|---|---|---|
| Fuente del menú | 11 caracteres nuevos (Á É Í Ó Ú Ñ Ü ¡ ¿ º ª), tabla de glifos completa y codificación | `codigo/menus/elementos_menu/`, `codigo/sistema/caracteres_es.c` |
| Cadenas | Unas 200 cadenas de menú y mensajes, los literales en línea `"results"`, `"round"` y `"driver's points"`, y los créditos | `textos_y_tablas.inc.c:264-647`, `info_pistas_y_tiempos.inc.c:421-504`, `codigo/ceremonia/creditos.c:70-81` |
| Créditos | `texto_creditos` tiene 126 entradas: se traducen las 63 en inglés y las 63 en japonés no cambian | `codigo/ceremonia/creditos.c` |
| Nombres de pista | Las 20 pistas | `recursos/pistas/metadatos/nombres_circuito.inc.c` |
| Texturas | Unas 55 texturas con texto: 13 de menú, 4 de número de jugadores, 4 copas, 20 títulos de pista, 2 carteles de MOO MOO FARM, 3 del HUD, 8 puestos y PULSA START. Además, los 48 cuadros de Lakitu (3 animaciones de 16) | `recursos/texturas/`, `recursos/comunes/texturas/` |
| Pantallas del port | Fuente 5x7 del panel, página de audio, pantalla de fallo, registro, nombres de fase y fuente de depuración N64 | `codigo/depuracion/`, `codigo/sistema/`, `codigo/graficos/sintetizador_gs.c` |
| Infraestructura | `make test` sin SDK, conversor EUC-JP, CI y tope de líneas | `Makefile`, `herramientas/`, `.github/workflows/compilacion.yml` |

### 2.2 Excluido

- **Voces del juego:** son muestras de audio.
- **Avisos nuevos.** No se agregan textos que hoy no existen en pantalla:
  - la falta de Memory Card al arrancar, que hoy solo va al registro (`codigo/sistema/memory_card.c:225`);
  - el cambio de 60 FPS con R3.

  Serían texto nuevo, no traducción.
- **Selección de idioma en tiempo de ejecución.**
- **Texto que se conserva tal cual.** Nombres de personaje (`nombre_*`), `copyright_1996`, `50cc`, `100cc`, `150cc`, `extra`, `modo_vs`, `tiempo_total_hud` (TOTAL), logotipos y carteles comerciales, onomatopeyas y `velocimetro` (km/h). Cada uno aparece en el manifiesto de texturas con su motivo (R-TEX-02).
- **Título de la partida en el navegador de la PS2.** «SMK64 PS2» / «Partida» (`memory_card.c:172`): `titulo_sjis` solo admite ASCII.
- **Nombres de nota del Controller Pak.** Son datos que se comparan con `memcmp` (`codigo/sistema/guardado_ps2.c:145`), no texto.
- **Contenido inalcanzable.** Queda documentado aquí. Sus cadenas se traducen porque cuesta poco; sus texturas no.

| Contenido | Por qué no se ve en el port | Tratamiento |
|---|---|---|
| Gestor del Controller Pak (START al arrancar) | `funcion_80091D74` sale con 0 porque `status` queda a 0 (`animaciones_personajes.inc.c:379`; `memset` en `codigo/entrada/mandos.c:234`) | Cadenas sí. Texturas ia16 (`codigo/datos/texturas_fuentes.s:56-127`) y fuentes diminutas, no |
| Menú de depuración N64 | `MODO_DEPURACION_ACTIVACION` vale 0 porque el build no define `GCC` ni `DEBUG` (`incluir/juego/definiciones.h:7-11`, `Makefile:46-47`) | Cadenas en ASCII (bloque B7) |
| `menu_con_item`, `menu_sin_item` | El menú principal no los agrega (`imprimir_texto.inc.c:656-674`) | No se traducen |
| `mando_sin_texto` | El bit del puerto 1 se activa siempre que `padPortOpen` funciona (`mandos.c:121`, `:235-236`) | Se traduce, pero no se puede capturar |

## 3. Convenciones

- **Formato de cada requisito:** enunciado observable, **Aceptación** (condición verificable) y **Prueba** (qué lo comprueba). Su estado y sus commits se siguen en [trazabilidad.md](trazabilidad.md).
- **Referencias `ruta:línea`:** se refieren a `main` (`0e7b7d5`) salvo que se indique otra rama. Las ramas de trabajo mueven líneas.
- **(nuevo):** el archivo no existe en `main`.
- **(hecho en `<hash>`):** el archivo o el cambio ya está en una rama publicada.
- **(en curso):** está en una rama de trabajo que todavía no se publicó.
- **Coordenadas:** están en el espacio de 320 × 240 del juego. `e` es la escala con la que se dibuja el texto.
- **Fuentes de verdad:**
  - términos: [glosario.md](glosario.md);
  - glifos: `codigo/menus/elementos_menu/lista_glifos.inc.c` (hecho en `1c9545d` y `5718601`);
  - tablas de texto, lugares de dibujo, lista negra y textos esperados: `herramientas/pruebas/prueba_textos_tablas.inc.c`, `prueba_textos_lugares.inc.c`, `prueba_textos_lista_negra.inc.c` y `prueba_textos_esperados.inc.c` (nuevos; en curso en `idioma/cadenas`);
  - texturas: `recursos/es/texturas.tsv` (hecho en `4345598`).
- **Cambios de requisito, límite, escala, paso o término:** se registran en [cambios.md](cambios.md) antes de tocar el código.

## 4. Términos base

Los fija el plan aprobado. El [glosario](glosario.md) los desarrolla y cita su fuente.

- **Modos:** GRAN PREMIO, CONTRARRELOJ, BATALLA.
- **Copas:** COPA CHAMPIÑÓN, COPA FLOR, COPA ESTRELLA, COPA ESPECIAL.
- **Resultados:** ¡VICTORIA!, ¡DERROTA!, HAS QUEDADO N.º, FIN, EQUIPO.
- **Tiempos:** RÉCORDS, MEJOR VUELTA, TIEMPOS DE VUELTA, ÚLTIMA VUELTA.
- **General:** PISTA, PILOTO, FANTASMA.
- **Verbos:** GRABAR (un fantasma) y GUARDAR (datos).
- **Memoria:** MEMORY CARD y RANURA 1 / RANURA 2.
- **Botones de PS2:** CRUZ, CUADRADO, SELECT y R1, según `codigo/entrada/mandos.c:57-63`.

## 5. Requisitos

### 5.1 R-FUE: fuente y codificación

**R-FUE-01. La tabla de glifos es completa y no depende del enlazador.**

`lut_textura_glifo` y `ancho_pantalla_glifo` salen de una única lista X-macro, `codigo/menus/elementos_menu/lista_glifos.inc.c`, con una línea `GLIFO(textura, ancho)` por glifo (hecho en `1c9545d`):

- los índices 0..235 (0x00..0xEB) son los 236 glifos de la N64, en su orden (hecho en `4e35120`);
- los índices 0xEC..0xF6 son los 11 glifos del español, en el orden de `CaracterEs` de `incluir/sistema/caracteres_es.h` (hecho en `5718601`);
- en total son 247.

Se eliminan los 7 arreglos de continuación (`textos_y_tablas.inc.c:871-906`, `animaciones_personajes.inc.c:3-6`). Un `ASSERT_ESTATICO(CANTIDAD_ARREGLO(lut_textura_glifo) == CANTIDAD_ARREGLO(ancho_pantalla_glifo), …)` en `textos_y_tablas.inc.c` impide que las dos tablas se desalineen. La macro recibe condición y mensaje (`incluir/juego/macros.h:35`).

- **Aceptación:**
  - las dos tablas tienen 247 entradas;
  - estos índices apuntan a su símbolo fijo:

    | Índice | Símbolo |
    |---|---|
    | 0 | `seg_2_textura_fuente_letra_a` |
    | 90 | `dato_020031AC` |
    | 91 | `dato_02003274` |
    | 212 | `dato_02004124` ('ー') |
    | 225 | `dato_020043A4` (sufijo ND) |
    | 228 | `dato_02004494` (sufijo ST) |
    | 234 | `seg_2_textura_fuente_coma` |
    | 235 | `dato_0200455C` |
    | 0xEC..0xF6 | `seg_2_textura_fuente_es_*`, en el orden de `CaracterEs` |

  - ninguna entrada de dos bytes da un índice ≥ 247.
- **Prueba:** `herramientas/pruebas/prueba_tablas_glifos.py` (cuenta e índices fijos; fija además los índices 134, 135, 164, 188, 190 y 216) y `herramientas/pruebas/prueba_glifos.c`, caso `probar_compatibilidad` (ningún índice fuera de la lista).

**R-FUE-02. Compatibilidad con la N64.**

Para toda entrada de dos bytes cuyo primer byte no sea 0x8F, el índice y el avance son los mismos que con el código de la N64.

- **Aceptación:** la huella FNV-1a de los pares (índice, avance) de todas esas entradas vale `0x770E34E9` (`HUELLA_N64`). La huella se calculó con el código anterior al cambio de la regla de avance, compilado con `-fsigned-char`.
- **Prueba:** `prueba_glifos.c`, caso `probar_compatibilidad` (hecho en `d87d14f`).

**R-FUE-03. Los 11 caracteres nuevos usan JIS X 0212 de 3 bytes.**

Las cadenas se escriben en UTF-8 legible (por ejemplo, «CAMPEÓN») y la compilación las pasa a EUC-JP. Cada carácter da su glifo propio y avanza 3 bytes. La minúscula da el mismo glifo que la mayúscula.

| Carácter | EUC-JP | Carácter | EUC-JP |
|---|---|---|---|
| Á / á | `8F AA A1` / `8F AB A1` | Ñ / ñ | `8F AA D0` / `8F AB D0` |
| É / é | `8F AA B1` / `8F AB B1` | Ü / ü | `8F AA E4` / `8F AB E4` |
| Í / í | `8F AA BF` / `8F AB BF` | ¡ | `8F A2 C2` |
| Ó / ó | `8F AA D1` / `8F AB D1` | ¿ | `8F A2 C4` |
| Ú / ú | `8F AA E2` / `8F AB E2` | º / ª | `8F A2 EB` / `8F A2 EC` |

- **Aceptación:**
  - el conversor del build produce esos bytes;
  - «CAMPEÓN», «¡GANADOR!», «¿SEGURO?», «AÑO 1.º», «PINGÜINO», «campeón» y «ーー», tal como quedan en EUC-JP, dan la secuencia de glifos esperada;
  - en «CAMPEÓN» y en «ーー», los bytes recorridos suman `strlen`;
  - `leer_caracter_es` reconoce cada carácter en EUC-JP (3 bytes) y en UTF-8 (2 bytes), con su letra base y su signo.
- **Prueba:** `prueba_convertir_eucjp.py` (bytes), `prueba_glifos.c` (caso `probar_espanol`, hecho en `641fe27`) y `prueba_caracteres_es.c` (caso `probar_lectura`, hecho en `9e6bec7`).

**R-FUE-04. `leer_glifo` es la única regla de avance.**

`s32 leer_glifo(char* car, s32* bytes)` (`glifos.inc.c`) es el único punto que decide el índice y el avance. Lo usan las cuatro impresoras de `imprimir_texto.inc.c` y `obtener_ancho_cadena`. En `main`, la regla «índice ≥ 0x30 → 2 bytes» estaba repetida en `imprimir_texto.inc.c:112, 152, 185, 234, 286`.

- **Aceptación:** `git grep -n 'indice_glifo >= 0x30' -- codigo/menus/` no devuelve nada, y la regla de dos bytes solo aparece dentro de `leer_glifo`.
- **Prueba:** la huella de R-FUE-02 y el `git grep` en la revisión (hecho en `d87d14f`).

**R-FUE-05. Las secuencias inválidas no rompen el recorrido.**

Una secuencia `8F` incompleta o desconocida devuelve -2 y avanza 1 byte. Nunca pasa del NUL.

- **Aceptación:** `"\x8F"`, `"\x8F\xAA"`, `"\x8F\xAA\xA2"` y `"\x8F\xA2\xC3"` dan -2 y 1 byte.
- **Prueba:** `prueba_glifos.c`, caso `probar_secuencias_rotas` (hecho en `641fe27`).
- **Pendiente:** en la compilación DEV, registrar una sola vez por puntero de cadena una secuencia inválida o un byte guía `C2`/`C3` (UTF-8 sin convertir). No está en `641fe27`.
- **Nota:** `imprimir_texto1` mide la cadena antes de dibujar y sale sin dibujar nada si encuentra un -2 (`imprimir_texto.inc.c:182-183`). Por eso R-TXT-03 exige que ninguna cadena dé -2.

**R-FUE-06. Anchos.**

- Una letra con diacrítico mide lo mismo que su letra base:

  | Á | É | Í | Ó | Ú | Ñ | Ü |
  |---|---|---|---|---|---|---|
  | 0x0C | 0x0A | 0x07 | 0x0C | 0x0C | 0x0D | 0x0C |

- ¡ mide lo mismo que ! (0x0A) y ¿ lo mismo que ? (0x0A). º y ª miden 0x0A.
- No cambian la línea base ni la alineación de `obtener_ancho_cadena`, `imprimir_texto0`, `imprimir_texto1` e `imprimir_texto2`. `imprimir_texto0` es la que usan `imprimir_modo_texto_1` e `imprimir_modo_texto_2` (`imprimir_texto.inc.c:131-168`).
- **Aceptación:**
  - ancho(«CAMPEÓN») = ancho(«CAMPEON»);
  - ancho(Á) = ancho(A);
  - ancho(¡) = ancho(!);
  - en la lista, cada glifo de 0xEC a 0xF4 tiene el ancho de su letra o signo base.
- **Prueba:** `prueba_glifos.c`, caso `probar_anchos_espanol`, y `prueba_tablas_glifos.py`.

**R-FUE-07. El diacrítico se dibuja con la matriz de la letra y el texto respeta el pool.**

- Una letra con diacrítico es una `TexturaMenu` de dos partes (`codigo/datos/texturas/fuente_es.inc.c`, hecho en `5718601`):
  - la letra base original, de 26 × 16;
  - el signo, de 26 × `ALTO_DIACRITICO` (8).
- `imprimir_letra` (`letras_y_fundidos.inc.c`) dibuja la segunda parte con `dibujar_diacritico_glifo` (`cargar_texturas_menu.inc.c`) y `vtx_glifo_diacritico` (`codigo/datos/segmento_datos_2.c`, de y = -24 a y = -16):
  - reutiliza la matriz que cargó la letra: no emite `gSPMatrix` ni incrementa `cantidad_efecto_matriz`;
  - escala con la letra;
  - es blanca, como la parte alta del degradado.
- **Tope del pool.** En `funcion_80095BD0`, bajo `AVOID_UB`, el tope pasa de 0x2F7 (759) a `MTX_EFECTO_POOL_TAMANIO`, que vale 660 (`incluir/sistema/bucle_principal.h:24`), el tamaño real de `efecto_mtx`. Si se alcanza, las letras que sobran no se dibujan, como en la N64 al pasar su tope (hecho en `dcc0914`, commit propio).
- **Alcance.** El cambio y su aceptación se limitan a `funcion_80095BD0` y al dibujo del diacrítico. Los demás sitios que escriben `efecto_mtx` sin tope quedan fuera (ver §8).
- **Aceptación:**
  - bajo `AVOID_UB`, `funcion_80095BD0` no escribe `efecto_mtx[i]` con i ≥ `MTX_EFECTO_POOL_TAMANIO`;
  - `dibujar_diacritico_glifo` no contiene `gSPMatrix` ni modifica `cantidad_efecto_matriz`, así que dibujar «CAMPEÓN» consume las mismas matrices que «CAMPEON»;
  - las partes de alto 8 solo aparecen como segunda parte, de 26 de ancho, de los glifos del español.
- **Prueba:** `prueba_tablas_glifos.py` (caso `probar_partes_de_signo`), compilación de PS2 en la CI, revisión técnica y recorrido de F6 por las pantallas con más tildes (créditos, Memory Card).

**R-FUE-08. El arte de los glifos es reproducible.**

- Los 11 `.i4` nuevos los escribe `herramientas/generar_glifos_es.py` (solo biblioteca estándar; hecho en `9abb8d7`) en `$(BUILD)/glifos_es/`, a partir de los `.i4` originales de `recursos/texturas/sin_comprimir/`. Nada en `recursos/` cambia.
- `texturas_fuentes_es.s` los enlaza al final de `textures_0a` (`herramientas/generar_rom_ld.py`; hecho en `5718601`).
- Con `--ver`, la herramienta imprime los glifos en texto para revisarlos.
- Reglas del arte:
  - los diacríticos (`diacritico_*`, 26 × 8) llevan la tinta en las filas 2-5 y se centran sobre la parte alta de la letra, que es cursiva;
  - ¡ y ¿ (`abre_*`) son el giro exacto de 180° de ! y ?, con la misma caja de tinta;
  - los ordinales (`ordinal_o`, `ordinal_a`) son la O y la A a media altura, arriba y subrayadas, con tinta hasta la fila 10;
  - ningún glifo de 26 × 16 tiene tinta en la fila 15 ni en la columna 25, que el quad no muestra.
- **Aceptación:**
  - los diacríticos ocupan 104 B y ¡ ¿ º ª ocupan 208 B;
  - las filas con tinta y los giros son exactos;
  - dos ejecuciones dan bytes idénticos;
  - `GLIFOS_ES_NOMBRES` del `Makefile` coincide con la lista de la herramienta.
- **Prueba:** `herramientas/pruebas/prueba_glifos_es.py` (hecho en `9abb8d7`).

### 5.2 R-TXT: cadenas

Las pruebas de este apartado están en `herramientas/pruebas/prueba_textos.c` (nuevo; en curso en `idioma/cadenas`). Recorre las tablas reales, en la copia EUC-JP que compila el build, con el decodificador del juego (`glifos.inc.c`). Sus datos:

| Archivo | Contenido |
|---|---|
| `prueba_textos_tablas.inc.c` | Tablas revisadas, número de entradas originales y estado (`ES` o `PENDIENTE`). Una tabla `PENDIENTE` es un fallo esperado, y `TABLAS_PENDIENTES` solo puede bajar |
| `prueba_textos_lugares.inc.c` | Dónde se dibuja cada tabla, con qué impresora, escala y paso, y sus límites |
| `prueba_textos_lista_negra.inc.c` | Palabras en inglés y palabras sin su tilde |
| `prueba_textos_esperados.inc.c` | Texto esperado de cada entrada traducida, en UTF-8 |
| `prueba_textos_tinta.py` | Tinta izquierda y derecha de cada glifo, sacada de los `.i4` |

**R-TXT-01. Todo el texto visible está en español según el glosario.**

- Esto cubre menús, pausa, resultados, fantasmas, Memory Card, ceremonia, créditos, intro de batalla, avisos y banner.
- Los literales en línea `"results"`, `"round"` y `"driver's points"` (`info_pistas_y_tiempos.inc.c:421, 423, 502, 504`) pasan a tablas con nombre.
- Se conservan los nombres propios, las siglas (CPU, VS, OK, PS2…) y «MEMORY CARD».
- **Aceptación:**
  - Ninguna tabla en estado `ES` contiene palabras de la lista negra: palabras en inglés y palabras que exigen tilde, como MENU, CLASIFICACION, REPETICION, ESTEREO, CHAMPINON o MONTANA.
  - Ningún argumento de texto de las impresoras de la fuente del menú es un literal. Las únicas excepciones son `'`, `"`, 'ー' y los búferes numéricos.
  - Quedan fuera de esa regla las impresoras de la fuente de depuración (`imprimir_cad2_depuracion` y similares, `imprimir_texto.inc.c:751-794`). Sus literales van en ASCII según R-PORT-05.
- **Prueba:** `prueba_textos.c`, con `prueba_textos_lista_negra.inc.c`.

**R-TXT-02. Cada tabla conserva el número y el orden de sus entradas.**

Hay índices que se calculan con paso fijo, así que no puede cambiar ni la cantidad ni el orden.

| Tabla | Entradas |
|---|---|
| `boton_pausa_texto` | 7 |
| `texto_lugar` | 9 |
| `nombres_copa` | 9 |
| `menu_opcion_texto` | 4 |
| `dato_800E7744` | 6 |
| `dato_800E7890` | 16 |
| `dato_800E78D0` | 12 |
| `dato_800E7900` | 6 |
| `dato_800E7940` | 16 |
| `dato_800E798C` | 42 |
| `texto_creditos` | 126 |
| `creditos_texto_render_info` | 63 |

- **Aceptación:** cada cuenta coincide con la de `prueba_textos_tablas.inc.c`.
- **Prueba:** `prueba_textos.c`.

**R-TXT-03. Todo carácter tiene glifo.**

Tras la conversión, cada carácter de una tabla `ES` da, con `leer_glifo`, un índice ≥ 0 y menor que 247. Ninguna cadena:

- da -2;
- cae en el glifo de reserva 'B' (byte alto que no se reconoce, `animaciones_personajes.inc.c:732, 741-754`);
- cae en el glifo de reserva 'C' (secuencia A1/A3/AB que no se reconoce, `imprimir_texto.inc.c:8, 94-95`).

Esta comprobación, hecha con el decodificador real, es la que valida los caracteres. El conversor no lleva lista blanca (R-INF-02). Ejemplos:

| Carácter | EUC-JP | Resultado |
|---|---|---|
| ’ | `A1 C7` | Glifo 0xD1 (`fuente_apostrofo`) |
| ” | `A1 C9` | Glifo 0xD2 |
| … | `A1 C4` | Reserva 'C': se rechaza |
| “ | `A1 C8` | Reserva 'C': se rechaza |

En la fuente del menú no se usan `( ) : ; / %`, porque '(' se dibuja como «cc» y los demás no tienen glifo.

- **Aceptación:** cero cadenas con -2 o con reserva.
- **Prueba:** `prueba_textos.c`.

**R-TXT-04. El texto cabe en la zona segura, medido por tinta.**

Para cada tabla y cada lugar donde se dibuja (registrado en `prueba_textos_lugares.inc.c`):

- el borde izquierdo es `x + tinta_izq(primero)·e`;
- el borde derecho es `x + (Σ avance(0..n−2) + tinta_der(último) + 1)·e`;
- los dos se ajustan según la alineación (izquierda, centrada o derecha).

Los dos bordes quedan dentro de x ∈ [16, 296] y dentro del límite propio del lugar. El límite de cada lugar tiene uno de estos orígenes:

- **S:** zona segura del televisor, [16, 296];
- **G:** geometría del código (caja, vecino o salto de línea);
- **I:** máximo del inglés en ese lugar, solo donde la posición depende de otro elemento que no se puede acotar mejor;
- **C:** captura aprobada en [cambios.md](cambios.md).

`tinta_izq` y `tinta_der` salen de los `.i4` de la fuente, los originales y los del español (`prueba_textos_tinta.py`).

- **Aceptación:** ninguna cadena queda fuera de su límite ni de la zona segura.
- **Prueba:** `prueba_textos.c`.
- **Motivo:**
  - El inglés nunca pasa de x ≈ 293.
  - La tinta de un glifo sobrepasa su avance entre 3 y 8 px.
  - PCSX2 no muestra el sobrebarrido de la TV.

**R-TXT-05. El interlineado deja sitio para las tildes.**

En todo bucle que dibuja varias líneas con paso `p` y escala `e`, si alguna línea a partir de la segunda contiene una letra con diacrítico, se cumple `p ≥ ceil(20,6·e)`. 20,6 px es la altura de la tinta del diacrítico sobre la línea base a escala 1. Las excepciones solo se admiten mediante [cambios.md](cambios.md) (CC-02).

- **Aceptación:** ningún bucle registrado en `prueba_textos_lugares.inc.c` incumple la regla.
- **Prueba:** `prueba_textos.c`.

**R-TXT-06. Los textos esperados coinciden byte a byte.**

- `prueba_textos_esperados.inc.c` guarda, por tabla e índice, el texto en español en UTF-8.
- El `Makefile` lo pasa a EUC-JP con el mismo conversor que el build, y cada entrada compilada coincide byte a byte con el esperado.
- Un cambio de texto actualiza el esperado en el mismo commit. Si toca un término, actualiza también el glosario.
- **Aceptación:** cero diferencias.
- **Prueba:** `prueba_textos.c`.

**R-TXT-07. Los ordinales se escriben «1.º».**

Todo ordinal visible se escribe con número, punto y º: «1.º» … «8.º». El femenino es «2.ª» (Lakitu). No quedan ST/ND/RD/TH ni un espacio entre el número y el ordinal.

Afecta a:

- `texto_lugar` (hoy `"    st"`…);
- `dato_800E7744` (hoy `"1 ｓ"`, `"2 ｎ"`…);
- las texturas `hud_1ro`…`hud_8vo`.

- **Aceptación:** los esperados de texto coinciden y las texturas de puesto no tienen sufijo inglés.
- **Prueba:** `prueba_textos.c`, `prueba_texturas_es.py` y captura en F6 del ranking de récords y del puesto final.

**R-TXT-08. Las cadenas nombran los botones y los puertos de la PS2.**

Toda cadena que nombra un botón o un puerto de la N64 usa el botón de PS2 de la tabla de R-TEX-07 y la terminología de la PS2. Casos conocidos:

- `datos_menu_texto`: «a BUTTON*SEE DATA  B BUTTON*EXIT» (`textos_y_tablas.inc.c:395`), que pasa a CRUZ y CUADRADO;
- `mando_sin_texto`: «CONNECT A CONTROLLER TO SOCKET 1,» (`textos_y_tablas.inc.c:387`).

- **Aceptación:** la lista negra incluye BUTTON y SOCKET, y los esperados nombran CRUZ y CUADRADO.
- **Prueba:** `prueba_textos.c` (lista negra y esperados).

### 5.3 R-MC: Memory Card

**R-MC-01. Se habla de la Memory Card, no del Controller Pak.**

Ninguna cadena visible menciona «N64», «CONTROLLER PAK» ni «CONTROLLER 1/2». Se escribe «MEMORY CARD». Tampoco se mencionan las páginas de la N64 («PLEASE FREE 121 PAGES», `textos_y_tablas.inc.c:525`).

- **Aceptación:** la lista negra incluye N64, CONTROLLER, PAK y PAGES, y ninguna tabla `ES` los contiene.
- **Prueba:** `prueba_textos.c` (lista negra y esperados).

**R-MC-02. Cada mensaje nombra la ranura correcta.**

Todo mensaje que en el original nombra «CONTROLLER 1» nombra «RANURA 1», y todo mensaje que nombra «CONTROLLER 2» nombra «RANURA 2». Afecta a `dato_800E7890`, `dato_800E78D0`, `dato_800E7900`, `dato_800E7940`, `dato_800E798C` y `dato_800E7918`.

- **Aceptación:** para cada entrada cuyo original contiene «CONTROLLER n», el texto en español contiene «RANURA n».
- **Prueba:** `prueba_textos.c`, sobre `prueba_textos_esperados.inc.c`.

**R-MC-03. La opción de copiar fantasmas es honesta.**

- `menu_opcion_texto[2]` («COPY N64 CONTROLLER PAK») pasa a «COPIAR FANTASMAS».
- El mensaje al que esa opción lleva siempre es el grupo 2 de `dato_800E78D0` (entradas 6-8). Pasa a:
  - «COPIAR FANTASMAS DESDE»
  - «OTRA MEMORY CARD NO»
  - «ESTÁ DISPONIBLE EN PS2»
- No cambian la navegación ni los estados `SUB_MENU_*`.
- **Por qué siempre falla:** `osPfsInit` con canal ≠ 0 devuelve `PFS_ERR_NOPACK` (`codigo/sistema/guardado_ps2.c:119-121`), así que la copia siempre termina en `SUB_MENU_COPIA_PAK_ERROR_SIN_PAK_2P` (`codigo/menus/menus/tablas_menus.inc.c:315-317`).
- **Aceptación:**
  - los esperados coinciden;
  - `git diff <base> -- codigo/menus/menus/tablas_menus.inc.c` sale vacío en el bloque B4.
- **Prueba:** `prueba_textos.c` y captura en F6 de la opción y del mensaje.

### 5.4 R-TEX: texturas

**R-TEX-01. El cargador elige el formato por la firma.**

- `codigo/sistema/descompresion_textura_menu.c` y su cabecera (hechos en `2ff6bf0`; puros y compilables en el PC) leen la firma de la textura del segmento 0x0B:
  - «TKMK00» → decodificador TKMK00;
  - «MIO0» → descompresor MIO0, con RGBA16 big-endian y el alfa ya horneado;
  - otra firma → `tamanio_textura_menu` devuelve 0 y `decodificar_textura_menu` devuelve `TEXTURA_MENU_FIRMA_DESCONOCIDA` sin escribir la salida.
- `tkmk00decode` (`codigo/sistema/descompresion.c`) queda como adaptador: marca la RAM de texturas como antes y, ante una firma desconocida, corta con `detener_por_error`.
- **Aceptación:**
  - las 63 TKMK00 de `recursos/texturas/menus/tkmk00/` dan la SHA-1 de `herramientas/pruebas/referencias_tkmk00.txt`. Esas sumas se sacaron una vez con el decodificador original y con el alfa que indica el `type` de su `TexturaMenu`: 0xBE para el tipo 1 y 0x01 para el tipo 0;
  - la misma salida, guardada como MIO0, vuelve igual y con el mismo tamaño, con alfa 0x01 y 0xBE;
  - una firma desconocida devuelve el error y deja la salida intacta.
- **Prueba:** `herramientas/pruebas/prueba_textura_menu.c` (hecho en `2ff6bf0`) y `herramientas/pruebas/prueba_tkmk00.py`, que comprueba el alfa de cada textura contra las tablas del juego y la salida de la herramienta `tkmk00` del PC contra las sumas (hecho en `9f9beac`).

**R-TEX-02. El manifiesto cubre todas las texturas.**

`recursos/es/texturas.tsv` (hecho en `4345598`) tiene las columnas `id`, `origen`, `formato`, `alfa` (`opaco` o `clave_00BE`), `texto_es`, `retocado` y `motivo_no`. Hoy tiene una fila por cada una de las 63 texturas TKMK00: 40 para traducir y 23 con motivo (8 «nombre propio», 7 «sin texto», 3 «unidad», 2 «se escribe igual», 2 «no se muestra» y 1 «nombre del modo», ver [CC-04](cambios.md)).

Tiene que cubrir también:

- `recursos/comunes/texturas/`;
- `recursos/texturas/{sin_comprimir,generales,efectos,lakitu,pistas,objetos,karts,seleccion_personaje}/`;
- `recursos/texturas/fuente_pantalla_fallo.ia1.inc.c`;
- los `.incbin` de `codigo/datos/*.s`.

Cada textura tiene una fila, o su carpeta entera tiene una fila de exclusión con motivo. `objetos/cartel_meta` se revisa textura a textura, porque lleva el logotipo. PULSA START se registra como RGBA16 crudo (R-TEX-03).

- **Aceptación:**
  - ninguna textura queda sin fila ni sin exclusión de carpeta;
  - ninguna fila tiene `texto_es` y `motivo_no` a la vez;
  - el alfa de cada fila TKMK00 coincide con el de `referencias_tkmk00.txt`.
- **Prueba:** `herramientas/pruebas/prueba_texturas_es.py`. Hoy comprueba las 63 filas TKMK00; la cobertura del resto está pendiente.

**R-TEX-03. Los tamaños de las texturas traducidas salen del manifiesto.**

- Las texturas de menú traducidas se guardan en MIO0 (RGBA16 big-endian con el alfa horneado), en el mismo lugar del segmento 0x0B. Toda entrada `TexturaMenu` que apunta a una de ellas usa `TAMANIO_ES_<id>`. Ese valor se calcula a partir del manifiesto y de los `.mio0`, en una cabecera bajo `$(BUILD)/es/`. Las entradas de texturas no traducidas no cambian.
- **Excepción: PULSA START.** `empezar_boton_empuje` no es TKMK00 ni MIO0:
  - es un RGBA16 crudo de 159 × 16 (5088 B), `recursos/texturas/sin_comprimir/empezar_boton_empuje.rgba16`, enlazado con `.incbin` en `codigo/datos/texturas_seleccion.s:796-797`;
  - su `TexturaMenu` es `{1, empezar_boton_empuje, 159, 16, 81, 179, 0x0, 0}` (`codigo/datos/texturas/fuentes_y_menus.inc.c:533`);
  - `cargar_img_menu` la copia tal cual, `alto·ancho·2` bytes (`cargar_texturas_menu.inc.c:830-832`).

  La versión en español conserva ese formato: RGBA16 crudo de 159 × 16 y 5088 B, sin MIO0 ni `TAMANIO_ES`. Solo cambia la ruta del `.incbin`.
- **Aceptación:**
  - ningún MIO0 tiene `size` 0: con 0 se copian solo 0x1000 bytes (`imagenes_menu.inc.c:67-71`);
  - `TAMANIO_ES_<id>` es ≥ el tamaño del `.mio0`;
  - la textura cabe en `buffer_comprimido_menu`: 0xCE00 en los menús y 0x2800 en carrera y ceremonia (`animaciones_personajes.inc.c:338, 434`);
  - la cabecera MIO0 declara `ancho·alto·2` bytes;
  - hay `.balign 16` antes de cada `glabel` en `codigo/datos/texturas_tkmk00.s`;
  - la ROM crece menos de 256 KB en total;
  - el cartel MOO MOO FARM usa el mismo mecanismo de tamaño en `recursos/pistas/moo_moo_farm/desplazamientos.c:57-58`;
  - PULSA START en español mide 5088 B y su entrada `TexturaMenu` no cambia.
- **Prueba:** `prueba_texturas_es.py`.

**R-TEX-04. Los PNG fuente están versionados y el resultado es reproducible.**

- Cada textura traducida tiene su PNG versionado en `recursos/es/`.
- El binario sale solo de herramientas del repositorio, que usan la biblioteca estándar y zlib:
  - `herramientas/png_simple.py` (hecho en `1ee6041`): lee gris, RGB, indexado con PLTE y tRNS, gris con alfa y RGBA de 8 bits. Escribe siempre con el filtro 0 y sin tIME. Rechaza 16 bits, menos de 8 bits y entrelazado;
  - `herramientas/formatos_textura.py` (hecho en `a7e918e`): convierte sin pérdida rgba16, ia16, ia8, i4, i8 y ci8 con su tlut. Rechaza un valor que el formato no puede guardar;
  - `herramientas/texturas_es.py` (hecho en `4345598`): `exportar`, `importar`, `comprobar` y `hoja`.
- **Aceptación:**
  - exportar e importar cada textura del manifiesto da los bytes originales decodificados (hecho);
  - la misma imagen da siempre los mismos bytes de PNG (hecho);
  - en el tipo 1, los píxeles transparentes valen 0x00BE; el tipo 0 es opaco;
  - fuera de la caja de texto, la textura es idéntica a la original;
  - un PNG sin la marca `retocado` es idéntico a lo que produce el compositor;
  - al recomponer el texto en inglés, el compositor reproduce al menos el 95 % de los píxeles de la caja.
- **Prueba:** `prueba_png_simple.py`, `prueba_formatos_textura.py` y `prueba_texturas_es.py`.

**R-TEX-05. El HUD usa palabras completas y no se solapa.**

- TIEMPO y VUELTA van completas, con texturas más anchas y desplazamientos ajustados ([CC-03](cambios.md)).
- Ningún píxel con tinta de la palabra se superpone con lo que el código dibuja al lado. Llamadas afectadas en `codigo/graficos/dibujar_objetos/ventana_item_y_minimapa.inc.c`:

  | Líneas | Qué dibuja |
  |---|---|
  | 481-482 | `comun_textura_hud_vuelta` (LAP) en `vuelta_x` |
  | 483-484 | Dígitos de vuelta en `vuelta_x + 0x1C` |
  | 532-533, 537-538 | `comun_textura_hud_tiempo` (TIME) de los tiempos de vuelta, en `tiempo_x_finalizacion_vuelta_{1,2} − 0x13`, con 32 px de ancho |
  | 542-543, 548-549 | LAP en `vuelta_despues_imagen_{1,2}_x` |
  | 544, 550 | Dígitos de vuelta en `vuelta_despues_imagen_{1,2}_x + 0x1C` |
  | 789-790 | TIME en `temporizador_x − 0x13`, con `dibujar_textura_32x_hud_2d_16` |
  | 793-794 | `comun_textura_hud_vuelta_tiempo` en `temporizador_x − 0x13`, con `dibujar_textura_32x_hud_2d_16` |

  En pantalla dividida, los dígitos de vuelta van en `vuelta_x + 0xC` (`codigo/carrera/objetos_y_efectos/hud_pantalla_dividida.inc.c:51`).
- Solo se abrevia en pantalla dividida si la palabra no cabe, y se registra en [cambios.md](cambios.md).
- `hud_1ro`…`hud_8vo` pasan a «1.º»…«8.º».
- **Aceptación:** la prueba de no solapamiento pasa para 1, 2, 3 y 4 jugadores en todas las llamadas de la tabla.
- **Prueba:** `prueba_texturas_es.py`, hoja de contacto del HUD y capturas en F6.

**R-TEX-06. Lakitu mantiene sus 16 cuadros y su paleta.**

- `vuelta_final` pasa a «¡ÚLTIMA!», `segunda_vuelta` a «2.ª VUELTA» y `marcha_atras` a «¡AL REVÉS!».
- Cada animación sigue con 16 cuadros contiguos, porque solo se pasa el primero (`nubes_estrellas_y_lakitu.inc.c:675`).
- Los cuadros se cuantizan a la paleta existente: las `tlut_lakitu_*` no cambian.
- **Aceptación:**
  - fuera de la máscara del cartel, cada cuadro es idéntico al original;
  - en el cuadro más plano, los glifos miden al menos 8 px de alto;
  - si el texto principal no cumple, la prueba de ajuste elige el texto de reserva que indica el manifiesto.
- **Prueba:** `prueba_texturas_es.py` y hoja en tira de 16 cuadros.

**R-TEX-07. Las texturas nombran los botones de PS2.**

Toda textura que nombra un botón usa el botón de PS2 que asigna `codigo/entrada/mandos.c:57-63`:

| Botón de N64 | Botón de PS2 |
|---|---|
| L | SELECT |
| R | R1/R2 |
| Z | L1/L2 |
| A | CRUZ |
| B | CUADRADO |

Así, `opcion_l` pasa a «SELECT OPCIONES» y `datos_r` a «R1 DATOS». Las cadenas siguen la misma tabla (R-TXT-08).

- **Aceptación:**
  - el texto de cada textura traducida en el manifiesto nombra el botón de la tabla;
  - ninguna textura traducida conserva «L» o «R» sueltas, ni iconos Ⓐ o Ⓑ.
- **Prueba:** `prueba_texturas_es.py`.

**R-TEX-08. La superposición no mezcla idiomas.**

- Las texturas `.inc.c` del HUD se sustituyen con la opción `--superponer <carpeta>` de `herramientas/invertir_texturas.py` (hecho en `fdd6a54`): si existe `<carpeta>/<ruta del .inc.c>`, se invierte esa versión. En ese modo se compara el resultado con la salida en lugar de fiarse de la fecha, así que al quitar una sustitución vuelve la versión del repositorio.
- Pendiente:
  - conectar la opción al build, con la carpeta bajo `$(BUILD)/es`;
  - cubrir con un sello propio las `.i4` de los puestos, que no pasan por esa herramienta (`TEXTURE_NAME_RE`, `invertir_texturas.py:16`).
- **Aceptación:**
  - si se quita una sustitución, el siguiente build incremental vuelve a la textura original;
  - una sustitución que no es un arreglo de datos falla;
  - ningún build mezcla idiomas.
- **Prueba:** `herramientas/pruebas/prueba_invertir_texturas.py` (hecho en `fdd6a54`) y `prueba_texturas_es.py`, caso de build incremental (pendiente).

#### Textos esperados en texturas

| Textura | Original | Español |
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
| `batalla_modo` | BATTLE | BATALLA |
| `modo_contrarreloj` | T.TRIALS | CONTRARRELOJ |
| `modo_mario_gp` | MARIO GP | GRAN PREMIO. Si no pasa la prueba de ajuste, se queda «MARIO GP» y se documenta ([CC-04](cambios.md)) |
| `ok` | OK? | ¿OK? |
| `juego_menu_1j`…`4j` | 1P GAME… | 1 JUG. … 4 JUG. |
| `menu_copa_hongo`, `_flor`, `_estrella`, `_especial` | … CUP | COPA / nombre, en 2 líneas |
| `titulo_*` (20) y cartel MOO MOO FARM | nombres de pista | nombres oficiales según el glosario |
| `tiempo_hud`, `tiempo_vuelta_hud`, `vuelta_hud` | TIME, LAP | TIEMPO, VUELTA |
| `hud_1ro`…`hud_8vo` | 1st…8th | 1.º…8.º |
| `empezar_boton_empuje` | PUSH START BUTTON | PULSA START |
| Lakitu `vuelta_final`, `segunda_vuelta`, `marcha_atras` | FINAL LAP, 2nd LAP, REVERSE | ¡ÚLTIMA!, 2.ª VUELTA, ¡AL REVÉS! |

### 5.5 R-PORT: pantallas del port

Las pruebas de este apartado son `herramientas/pruebas/prueba_fuente_5x7.c` y `herramientas/pruebas/prueba_textos_port.py` (nuevas; en curso en `idioma/port`). `prueba_textos_port.py` es una lista negra sobre los literales que el port manda a sus pantallas y a su registro.

**R-PORT-01. La fuente 5x7 tiene los 11 caracteres.**

- `codigo/depuracion/fuente_5x7.c` (nuevo, puro) usa celdas de 8 filas: la fila 0 es para el diacrítico y las filas 1-7 para la letra.
- Dibuja Á É Í Ó Ú Ñ Ü ¡ ¿ º ª, tanto en UTF-8 como en EUC-JP. La minúscula da la mayúscula.
- El ASCII no cambia. Hoy la fuente cubre de ' ' a 'Z' (`codigo/depuracion/texto_pantalla.c:8-9`).
- `texto_pantalla.c` cuenta columnas por carácter, no por byte.
- **Aceptación:**
  - 'A' sigue siendo `0E 11 11 11 1F 11 11`;
  - las filas 1-7 de Á son iguales a las de A, y la fila 0 no está vacía;
  - ¡ y ¿ son la rotación de ! y ?;
  - «AÑO» ocupa 3 columnas;
  - un `"\xC3"` al final consume 1 byte.
- **Prueba:** `prueba_fuente_5x7.c`.

**R-PORT-02. El panel, la página de audio y los nombres de fase están en español.**

- **Panel** (`codigo/depuracion/medidor_rendimiento.c:263-339`): FRAME pasa a CUADRO, POOL a RESERVA y VTX a VÉRT.
- **Página de audio** (`codigo/depuracion/monitor_audio.c:128-135`): MUSICA pasa a MÚSICA, y «SEQ» (`:134`) se traduce.
- **Nombres de fase:**
  - `codigo/sistema/arranque_ps2.c:62-88`;
  - `codigo/sistema/bucle_principal/hilos_video_y_audio.inc.c`;
  - `codigo/carrera/preparacion_carrera.c:203-209` (hoy `"func_802969F8"`, `"init_hud"`…);
  - `codigo/memoria/memoria_carrera/descomprimir_pista.inc.c:437-453` («pista: offsets», «pista: display lists», «pista: vertices (copia)»…);
  - `codigo/graficos/dibujar_pistas/pistas_toads_a_big_donut.inc.c:392-394` («colision: malla», «colision: cuadricula»);
  - las partes `.inc.c` de los fuentes de `JP_SRC` del Makefile que marcan fases.
- Dentro de los archivos que se convierten a EUC-JP (`JP_SRC` y sus partes), estos textos van solo en ASCII, porque el panel y el registro leen UTF-8.
- **Aceptación:** los textos coinciden con los esperados y ninguna línea del panel pasa de su ancho.
- **Prueba:** `prueba_fuente_5x7.c` (ancho de las líneas), `prueba_textos_port.py` (lista negra y ASCII dentro de los archivos convertidos) y capturas en F6 con `make DEBUG=1` y `make DEBUG=1 DEBUG_AUDIO=1`.

**R-PORT-03. La pantalla de fallo no muestra basura.**

- Todo texto que llega a `scr_printf` pasa antes por `quitar_diacriticos` (hecho en `9e6bec7`): Á → A, Ñ → N, º → o, y ¡ ¿ se omiten. Los puntos de entrada son `linea_pantalla` (`codigo/depuracion/depuracion.c:286-297`) y `detener_arranque` (`codigo/sistema/arranque_ps2.c:26-27`).
- **Puerta G-FALLO:** es un paso de la CI que inspecciona la fuente de libdebug. Si confirma que tiene glifos CP437, se transcodifican las letras disponibles (á é í ó ú ñ Ñ ü Ü É ¿ ¡ º ª) y el resto se translitera.
- Textos fijos en español:
  - «PARADA DE DIAGNÓSTICO»;
  - estados de hilo: RUN/READY/WAIT/SUSP/WSUSP pasan a EJEC/LISTO/ESPERA/SUSP/ESUSP (`depuracion.c:261-262`);
  - causas del fallo.
- **Aceptación:**
  - `quitar_diacriticos("después, ¿cuántos? ÑANDÚ")` da `"despues, cuantos? NANDU"`, también cuando el destino corta la cadena (hecho en `9e6bec7`);
  - la pantalla no muestra bytes ≥ 0x80 sin mapear.
- **Prueba:** `prueba_caracteres_es.c` (caso `probar_quitar_diacriticos`), `prueba_fuente_5x7.c`, paso G-FALLO en la CI y captura con `make DEBUG=1 EXTRA_DEFINES=-DSMK64_BOOT_STOP=<etapa>`.

**R-PORT-04. Cada marca del registro tiene una sola definición.**

- `incluir/depuracion/marcas_registro.h` (nuevo) define `MARCA_PANICO`, `MARCA_CUELGUE` y `MARCA_GIF`.
- El consumidor (`strstr` en `depuracion.c:99-100`) y todos los productores usan la misma macro:
  - `registrar` en `depuracion.c:220` (cuelgue), `:401` (pánico) y `:481` (cuelgue);
  - `estado_gif`, que se arma con `snprintf` en `depuracion.c:253` y se registra en `:388` y `:483`;
  - `detener_por_gif_trabado("GIF DMA sin terminar…")` en `codigo/graficos/sintetizador_gs.c:121`, que llega al registro por `depuracion.c:387`.
- Cambiar el valor de una marca es un cambio de especificación ([CC-05](cambios.md)).
- Los unos 103 formatos de `registrar()` llevan las tildes correctas: «no se guardará», «no se encontró», «debería».
- **Aceptación:** fuera de la cabecera no queda ningún literal de marca en `codigo/`.
- **Prueba:** `prueba_textos_port.py` y revisión lingüística.

**R-PORT-05. La fuente de depuración N64 no lee fuera de su tabla.**

- `codigo/graficos/dibujar_objetos/kart_bomba_y_depuracion.inc.c:181-182` indexa `dato_800E5628` con `(u8)`.
- Para los 11 caracteres dibuja la letra base (`caracter_es_base`, hecho en `9e6bec7`).
- Las cadenas que usan esta fuente:
  - son ASCII con celda en `dato_800E5628`, así que no llevan `$ & \ { | }`;
  - caben antes del salto de línea en x ≥ 296 (`:171`).
- **Aceptación:** ninguna cadena de depuración queda fuera de estas reglas.
- **Prueba:** `prueba_textos.c`, tablas con fuente de depuración.

### 5.6 R-INF: infraestructura

**R-INF-01. Los objetivos del PC corren sin el SDK.**

El `Makefile` (hecho en `f8f9a39`) declara `OBJETIVOS_PC := test clean herramientas`. Solo esos objetivos quedan fuera del `$(error)` que exige `PS2SDK`. Los objetivos `es` y `hoja-es` (bloque A0) se añaden a `OBJETIVOS_PC` cuando existan. Los demás objetivos siguen exigiendo `PS2SDK`.

- **Aceptación:**
  - `env -u PS2SDK make test` termina con 0;
  - `env -u PS2SDK make herramientas` y `env -u PS2SDK make clean` no piden el SDK;
  - cuando existan, `env -u PS2SDK make es` y `env -u PS2SDK make hoja-es` terminan con 0;
  - `env -u PS2SDK make` sigue fallando con «PS2SDK no definido: ejecuta '. herramientas/entorno.sh'».
- **Prueba:** job `pruebas-pc` de la CI, en ubuntu sin SDK.

**R-INF-02. El conversor EUC-JP da los mismos bytes que iconv y falla con posición.**

- `herramientas/convertir_eucjp.py` (hecho en `727c7ed`) sustituye a `iconv` en el `Makefile`.
- Para los archivos que se convierten (`JP_SRC` y `JP_PARTES`) produce los mismos bytes que `iconv -f UTF-8 -t EUC-JP` de glibc, sin depender del `iconv` del sistema.
- Si un carácter no existe en EUC-JP, falla con `ruta:línea:columna` y el código del carácter, y no deja salida a medias. Una entrada que no es UTF-8 también falla.
- **Sin lista blanca, a propósito.** El conversor no rechaza caracteres que sí existen en EUC-JP pero no tienen glifo. Esa validación la hace la prueba de textos con el decodificador real (R-TXT-03): ’ y ” tienen glifo; … y “ no.
- **Aceptación:**
  - cero diferencias con `iconv` en los archivos del build (si `iconv` no está instalado, la prueba lo avisa y omite esa comparación);
  - los bytes de R-FUE-03;
  - los finales de línea y el ASCII no cambian;
  - «HOLA» entre comillas angulares («») falla e indica la línea.
- **Prueba:** `herramientas/pruebas/prueba_convertir_eucjp.py` (hecho en `727c7ed`).

**R-INF-03. Los metadatos de pista se convierten.**

- Todos los `recursos/pistas/metadatos/*.inc.c` entran en `JP_PARTES` y se convierten a EUC-JP, entre ellos `nombres_circuito.inc.c`, `nombres_depuracion_circuito.inc.c` y `longitudes_circuito.inc.c`.
- El compilador toma las copias de `$(BUILD)/jp` gracias a `-iquote $(BUILD)/jp` (`JP_IQUOTE`).
- En `main` se incluyen desde `textos_y_tablas.inc.c:278, 282, 289, 294, 400` y llegan en UTF-8 por `-I.` (`Makefile:79`).
- **Aceptación:** con las opciones del build, el preprocesado de `elementos_menu.c` resuelve cada metadato de pista a su copia de `$(BUILD)/jp`.
- **Prueba:** `herramientas/pruebas/prueba_metadatos_eucjp.py` (hecho en `ecbfd5c`).

**R-INF-04. Las pruebas se comportan como el objetivo.**

- Toda compilación de prueba que incluye código del juego usa `-fsigned-char` (`CC_PRUEBAS := gcc -fsigned-char`, hecho en `8fdea7c`). El `char` del R5900 lleva signo, y `funcion_80092EE4` compara con etiquetas negativas (`imprimir_texto.inc.c:9-10`).
- `make test` depende de las copias `$(BUILD)/jp/*` que usa (hecho en `ecbfd5c`).
- **Aceptación:**
  - `make -n test` muestra `-fsigned-char` en cada `gcc` de prueba;
  - si se modifica un archivo de `JP_PARTES`, `make test` vuelve a convertir su copia.
- **Prueba:** inspección con `make -n test` y la huella de R-FUE-02.

**R-INF-05. Hay CI.**

`.github/workflows/compilacion.yml` (hecho en `7387d01`, `6dd12e7` y `a3d0bae`) se lanza en cada push y pull request, y a mano. Tiene tres jobs:

| Job | Qué hace |
|---|---|
| `pruebas-pc` | `make test` en `ubuntu-latest`, sin SDK |
| `compilar-ps2` | En el contenedor `ps2dev/ps2dev` fijado por digest: `make clean`, `make`, `make DEBUG=1`, `make test` y `make iso`. Guarda como artefactos `build/ps2/SLUS_999.99`, `build/ps2/SMK64ROM.BIN`, `build/ps2/smk64.map`, `build/ps2/debug/SLUS_999.99` y la ISO |
| `mismo-binario` | Solo a mano, con la entrada `base`. Corre `herramientas/comparar_binario.sh` contra la base, en release y con `DEBUG=1` |

El paso G-FALLO se añade en el bloque P4.

- **Aceptación:** la CI termina en verde en cada push y en el PR.
- **Prueba:** ejecuciones de la CI (ver [trazabilidad.md](trazabilidad.md)).

**R-INF-06. Ningún archivo de código pasa el tope de líneas.**

- `herramientas/comprobar_lineas.py` (hecho en `f1f3d3d`) se ejecuta dentro de `make test`.
- Ningún `.c`, `.h`, `.py` o `.sh` de `codigo/`, `incluir/` o `herramientas/` pasa de 1000 líneas.
- Excepciones: `incluir/libultra/*` y `codigo/memoria/tablas_trigonometricas.c`.
- Los `.s` de datos que ya superan el tope no crecen: `codigo/datos/karts/kart_*.s` (5915 líneas), `otras_texturas.s` (2139) y `texturas_fuentes.s` (1753). Lo nuevo va en archivos propios, como `codigo/datos/texturas_fuentes_es.s` (hecho en `5718601`).
- **Aceptación:** el comprobador termina con 0, y `wc -l` de esos `.s` no crece.
- **Prueba:** `make test` (el comprobador no revisa los `.s`) y revisión.

### 5.7 R-GOB: gobernanza

**R-GOB-01. Commits separados y con formato.**

- Cada commit hace una sola cosa.
- El asunto sigue `tipo(dominio): descripción` en español. Los tipos son `feat`, `fix`, `refactor`, `test`, `build`, `ci` y `docs`.
- También se aceptan:
  - `ci: descripción`, sin dominio, para los cambios de la CI;
  - los mensajes de merge por defecto, `Merge branch '…' into …`.
- Cada bloque de traducción (B1…B7) es un par de commits, prueba y cambio, o un solo commit con los dos. En los dos casos, el rojo se demuestra (R-GOB-03).
- **Aceptación:** este comando no devuelve nada:

  ```sh
  git log --format=%s origin/main..HEAD \
    | grep -vE "^((feat|fix|refactor|test|build|ci|docs)\([a-z0-9_-]+\)|ci): |^Merge branch '"
  ```

- **Prueba:** ese comando en la revisión del PR. Hoy sale vacío en `origin/idioma/infra`, `origin/idioma/fuente` y `origin/idioma/texturas`.

**R-GOB-02. El refactor no se mezcla con el cambio funcional.**

Un commit `refactor(...)` no cambia el comportamiento, y un commit funcional no mueve código entre archivos. El refactor lo demuestra con una de estas pruebas:

- **Preprocesado idéntico**, en el PC y sin SDK: `python3 herramientas/comparar_preprocesado.py <padre> <commit> <fuentes>` informa `igual` (hecho en `cb36bbc`).
- **Binario idéntico:** `sh herramientas/comparar_binario.sh <base>` y la misma orden con `DEBUG=1` informan `igual` para `SLUS_999.99` y `SMK64ROM.BIN` (job `mismo-binario`).
- **Prueba de caracterización**, cuando el refactor reorganiza la lógica y el binario cambia: una prueba fijada con el código anterior da el mismo resultado. Es el caso de `d87d14f`, cubierto por la huella de R-FUE-02.

- **Aceptación:** cada commit `refactor` de la rama tiene una de las tres pruebas registrada en [trazabilidad.md](trazabilidad.md).
- **Prueba:** revisión del PR.

**R-GOB-03. El rojo se demuestra y la mutación se restaura.**

- Antes del verde, la prueba nueva falla:
  - si prueba y cambio van en commits separados, el commit de la prueba está en rojo;
  - si van en el mismo commit, la prueba de ese commit se ejecuta sobre el árbol del commit padre y falla.
- La salida del rojo se adjunta al PR.
- Después del verde, una mutación manual de la implementación vuelve a poner la prueba en rojo, y la mutación se restaura.
- Cuando la prueba cubre un módulo nuevo, el rojo es la ausencia del módulo; basta con registrarlo.
- **Aceptación:** `git diff --quiet -- <ruta>` termina con 0 después de restaurar.
- **Prueba:** evidencia en el PR con las salidas de rojo, verde, mutación y restauración.

**R-GOB-04. Revisa un rol distinto del autor.**

- Todo bloque lo revisa REVISIÓN, nunca el rol que lo escribió.
- Cada hallazgo sigue este formato:
  - `[Alta|Media|Baja] Título`
  - `Archivo: ruta:línea`
  - `Riesgo`
  - `Recomendación`
- **Aceptación:** no se integra con hallazgos Alta o Media abiertos.
- **Prueba:** registro de la revisión en el PR.

**R-GOB-05. El árbol queda limpio.**

- Al cerrar cada bloque y cada fase, `git status --short` sale vacío.
- Los archivos de `build/` y `compilaciones/` que tocan las pruebas se restauran.
- `build/` y `compilaciones/` solo cambian en el commit final de publicación (F7).
- **Aceptación:** `git status --short` vacío, y ningún commit anterior a F7 toca `build/` ni `compilaciones/`.
- **Prueba:** `git log --name-only origin/main..HEAD -- build compilaciones` vacío hasta F7. Hoy sale vacío en las tres ramas publicadas.

**R-GOB-06. El stage se hace por ruta explícita.**

Se usa `git add -- <ruta>…`. Nunca `git add -A`, `git add .` ni `git commit -a`.

- **Aceptación:** `git diff --stat <base>..HEAD` solo muestra archivos del dominio del bloque o de las zonas que [plan.md §2](plan.md#2-roles) le asigna en los archivos compartidos.
- **Prueba:** revisión del PR.

**R-GOB-07. El código no lleva historia ni identificadores de requisito.**

Los comentarios explican un contrato o una invariante. Las funciones de varios pasos usan `/* Paso N: … */` o `// Paso N: …`, según el estilo del archivo. El código no lleva identificadores de requisito ni la historia del arreglo: eso va en el commit y en [trazabilidad.md](trazabilidad.md).

- **Aceptación:** este comando sale vacío:

  ```sh
  grep -rnE 'R-(FUE|TXT|MC|TEX|PORT|INF|GOB)-[0-9]' codigo incluir herramientas
  ```

- **Prueba:** ese comando en la revisión. Hoy sale vacío en las tres ramas publicadas.

**R-GOB-08. La documentación se actualiza en la misma iteración.**

Si un bloque cambia una estructura o un contrato, el mismo PR actualiza la especificación, la trazabilidad, los cambios y, si corresponde, el README.

- **Aceptación:** la revisión no encuentra documentos desfasados.
- **Prueba:** revisión del PR.

## 6. Decisiones cerradas

| Tema | Decisión |
|---|---|
| Pistas | Nombres oficiales de Nintendo en español, con la fuente citada en el glosario. Incluye las texturas `titulo_*` y el cartel MOO MOO FARM |
| HUD | Palabras completas (TIEMPO, VUELTA). Se amplían las texturas y se ajustan los desplazamientos. Solo se abrevia en pantalla dividida si no cabe |
| Binarios | `build/` y `compilaciones/` siguen versionados. Solo se regeneran en un commit final de publicación; nunca se agregan durante el trabajo |
| Variante | Español neutro con tuteo y terminología de Nintendo España. Botones de PS2 (CRUZ, CUADRADO, SELECT, R1) según `codigo/entrada/mandos.c:57-63` |
| Memory Card | Se escribe «MEMORY CARD» y «RANURA n», el término oficial de Sony. La opción «copiar fantasmas», que en el port siempre falla, pasa a un mensaje honesto: no disponible en PS2 |
| Contenido inalcanzable | Gestor del Controller Pak y menú de depuración N64: sus cadenas se traducen (cuesta poco) y sus texturas no. Queda documentado en §2.2 |

Las diferencias entre lo ejecutado y el plan aprobado están registradas en [CC-06](cambios.md).

## 7. Diferencias aceptadas

- **Transición de disolución.** El decodificador TKMK00 pone a cero su búfer temporal (`descompresion_tkmk00.c:61`). Ese búfer es `tkmk_00_bajo_res_buffer` (`imagenes_menu.inc.c:98-99`), el mismo que usa la transición de disolución (`letras_y_fundidos.inc.c:760-790`). Una textura MIO0 no lo toca, así que el patrón de disolución ya no se reinicia si se carga una textura traducida a mitad de la transición. Se acepta como diferencia, no como regresión.
- **Alineación del registro.** `%-26s` alinea por bytes (`codigo/sistema/cronometro_fases.c:165`). Una tilde descuadra una columna en el registro. No afecta a la pantalla.

## 8. Riesgos y mitigación

| Riesgo | Mitigación |
|---|---|
| El `iconv` de musl de la imagen de CI no tiene JIS X 0212 y rompería las tildes sin avisar | Conversor en Python (R-INF-02), hecho en `727c7ed` |
| Un carácter sin glifo da -2 y `imprimir_texto1` borra la cadena entera | R-TXT-03: la prueba de textos valida cada carácter con el decodificador real |
| Se cuela UTF-8 sin convertir (metadatos) | R-INF-03, hecho en `ecbfd5c`, y registro DEV de `C2`/`C3` (R-FUE-05, pendiente) |
| Las tildes chocan con la línea anterior | R-TXT-05 y [CC-02](cambios.md) |
| El sobrebarrido de la TV no se ve en PCSX2 | Zona segura x ∈ [16, 296] (R-TXT-04) y captura en TV en F6 |
| El texto del menú desborda el pool de matrices (tope 0x2F7 > 660) | R-FUE-07: tope real en `funcion_80095BD0` (`dcc0914`) y diacrítico sin matriz propia (`5718601`) |
| Otros sitios escriben `efecto_mtx` sin tope: `imprimir_texto.inc.c:386-387, 437-438, 458-459`; `menus_pausa.inc.c:255-256, 552, 578`; `particulas_derrape.inc.c:695`; `globos_batalla.inc.c:62, 181`; `dibujar_kart_y_sombra.inc.c:680, 729`; `actores_podio.c:200` | Fuera del alcance de R-FUE-07. El recorrido de F6 vigila las pantallas con más texto. Si hace falta, se abre un requisito propio en [cambios.md](cambios.md) |
| Una pantalla supera `TEXTURA_MAX_MAPA` (200, `incluir/menus/elementos_menu.h:620`) | Contador DEV `menu_texturas_salteado` (`cargar_texturas_menu.inc.c:776`), revisado en el recorrido de F6 |
| Una `TexturaMenu` con `size` 0 se copia truncada | R-TEX-03 |
| Un build incremental mezcla idiomas | R-TEX-08 |
| El arte compuesto automáticamente no queda bien | Marca `retocado` en el manifiesto, hojas antes/después y revisión visual |
| `build/` versionado ensucia el árbol y deja copias viejas en `build/ps2/jp` | R-GOB-05, `make clean` al empezar el job `compilar-ps2` (`6dd12e7`) y borrar `build/ps2/jp` antes de probar cambios de texto ([plan.md §5](plan.md#5-ciclo-por-bloque)) |
| La orden `captura` de los guiones espera un proceso externo que no está en el repositorio (`guiones_prueba.c:665-679`) | Capturas manuales en las pausas `nota` |
| Falta el permiso `workflow` para publicar la CI | No ocurrió: la CI corre en las tres ramas publicadas. Si faltara, el build de PS2 se verificaría en la máquina del responsable del proyecto y se informaría así |
| Un nombre de pista no tiene fuente oficial confirmada | El glosario cita la fuente; los nombres pendientes se marcan hasta cerrarlos |
| Conflictos de fusión en archivos compartidos (`Makefile`, `textos_y_tablas.inc.c`, `incluir/menus/elementos_menu.h`) | Dueño por zona ([plan.md §2](plan.md#2-roles)), integración en el orden fijado y resolución por INTEGRACIÓN |
| El texto de Lakitu es ilegible en los cuadros de canto | Solo se exige no tocar nada fuera de la máscara y una altura ≥ 8 px en el cuadro plano (R-TEX-06) |
