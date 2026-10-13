# Estilo de la documentación

Cómo escribo la documentación de este proyecto y cómo ordeno el informe. La [prueba de voz](../../herramientas/pruebas/prueba_voz_docs.py) vigila lo primero y la [prueba de enlaces](../../herramientas/pruebas/prueba_enlaces_docs.py), lo segundo ([CC-36 y CC-37](../traduccion/cambios.md)).

## La voz

- **Yo** para lo que hice, decidí o comprobé: «traduje», «decidí», «comprobé con 44 pruebas». No escribo «Alexis», «el autor», «el responsable» ni «la persona que», y evito el «se» de acción propia («se hizo», «se comprobó»).
- **Tú** para ti, que lees: «descarga», «comprueba», «ábrelo». Nunca usted.
- **Tercera persona solo para terceros reales:** anthoo582 y el autor del port original, la descompilación comunitaria, Nintendo y Sony.
- **La revisión independiente** se nombra como tal («la revisión independiente encontró…»), porque la hizo otra parte y no puedo presentarla como mía. Lo mío en primera persona es lo que hice con sus hallazgos: «corregí», «acepté».
- **Firma, créditos y licencia** pueden llevar el nombre completo, Alexis Barrera.
- No menciono a mi empleador ni a ninguna institución.
- No cambio hechos, cifras, hashes ni identificadores CC al reescribir: solo la redacción.

## Referencias en el texto

No uso notas al pie. La evidencia va en un enlace dentro de la misma frase: a un commit, a una ejecución de la CI o a un acta de revisión. Un dato vive en un solo lugar y los demás documentos lo enlazan.

## La estructura del informe

El [README](../../README.md) sigue este orden, y la página del proyecto lo replica en versión corta:

1. Resumen y propósito.
2. Qué incluye y descarga verificable, con tamaño y SHA-256.
3. Cómo jugar.
4. Qué comprobé y cómo: una tabla de afirmación, método y evidencia, y los límites declarados.
5. Patrones y prácticas que apliqué: una tabla de patrón y dónde se ve en el repositorio.
6. Mi trayectoria en este proyecto, en primera persona.
7. Créditos, aviso legal y licencia.

## Qué vigila la prueba

`prueba_voz_docs.py narrativa` revisa la portada, el registro de cambios, CONTRIBUTING, la página, el caso de estudio, las notas de versión, los créditos y el manual de usuario. `prueba_voz_docs.py proceso` revisa `docs/traduccion/`, las actas y el manual técnico. Sin argumento revisa ambos alcances. Ignora los bloques de código, las URL y los nombres de terceros. Los patrones prohibidos y los falsos positivos que revisé a mano están en el propio archivo.
