# Créditos

Quién hizo cada parte de este repositorio. El historial de git registra el autor de cada commit; aquí se resume por áreas, sin contar commits: el primer commit del port original trae el port entero.

## Port a PlayStation 2: anthoo582

El port es de anthoo582 ([anthoo582/mario-kart-64-ps2](https://github.com/anthoo582/mario-kart-64-ps2)), del que este repositorio es un fork. Incluye la capa que sustituye el hardware de la Nintendo 64 por el de la PS2:

- el intérprete de listas de dibujo F3DEX, el combinador de color y la TMEM, con salida al GS;
- el microcódigo de audio reescrito en C y la salida por `audsrv`;
- hilos, colas de mensajes, retrazo y temporizadores sobre el kernel del EE;
- la lectura de la ROM del disco en segundo plano;
- el guardado en la Memory Card;
- la pantalla de fallo, el registro, el panel de rendimiento y los guiones de prueba.

En `c2ed147` y `ae93f71` añadió, entre otras cosas, el multitap, el arranque desde OPL sin reiniciar el IOP, tiempos límite en el IOP, el CD y la Memory Card, 60 FPS más estables, la caché de texturas por columnas y arreglos de color y de vértices.

## Base: la descompilación de Mario Kart 64

El código del juego sale de la descompilación comunitaria de Mario Kart 64 (versión estadounidense), sobre la que se construyó el port.

## Localización, sincronización y mejoras: Alexis Barrera

Alexis Barrera (GitHub: [Alexis-VsCode](https://github.com/Alexis-VsCode)) mantiene este fork.

**Localización completa al español:**

- fuente del menú con 11 glifos nuevos (Á É Í Ó Ú Ñ Ü ¡ ¿ º ª) y la tabla de glifos completa, de 247 entradas;
- textos de menús, mensajes, Memory Card, intro de la batalla, ceremonia y créditos;
- los 20 nombres oficiales de pista en español;
- 55 texturas con texto y los 48 cuadros de los carteles de Lakitu;
- pantallas propias del port (panel de rendimiento, página de audio y registro) con tildes.

**Mejoras del port:**

- `make test` en el PC, sin el SDK de PS2;
- conversión a EUC-JP sin `iconv` (`herramientas/convertir_eucjp.py`);
- CI con la imagen de ps2dev fijada por digest, comparación de binario y publicación de los binarios y de la Release;
- la tabla de texturas de glifos cubre los 236 glifos originales, que en PS2 se leían fuera de la tabla (`4e35120`);
- el texto del menú no escribe más matrices de las que tiene su reserva (`dcc0914`).

**Sincronización con el original** hasta `ae93f71`: fusión `9f4d0215` y textos nuevos del original en español (`748db117` y `36fc9e40`). Después de la sincronización, las correcciones de [CC-11](../traduccion/cambios.md) (E3, E4, E5, G5, L2 y L3) están en la rama de integración `feature/sincronizacion-upstream` hasta su fusión a `main`.

## Herramientas de terceros

- [ps2dev](https://github.com/ps2dev/ps2dev): toolchain de PS2, ps2sdk y gsKit.
- PCSX2 y Play!: emuladores en los que el autor del port lo probó.
- OPL y uLaunchELF: cargadores para PS2.

## Licencia y marcas

Ni el repositorio original ni este fork declaran una licencia, y este repositorio no añade ninguna. Mario Kart 64, Nintendo 64, PlayStation 2, DualShock y el resto de marcas citadas pertenecen a sus respectivos dueños. Proyecto de preservación sin afiliación con Nintendo ni con Sony.
