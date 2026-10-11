#!/usr/bin/env python3
"""main() de arranque_ps2.c pone en marcha la depuración antes de tocar el IOP.

inicializar_depuracion() arranca el perro guardián y la pantalla de fallo.
Si el reinicio del IOP (reiniciar_iop, o preparar_iop_sin_reinicio bajo
OPL) se cuelga antes, queda en pantalla la última imagen del cargador. La
llamada va en main() una sola vez y antes de ese bloque; quitarla o
moverla no da ningún error de compilación.

El cronómetro se abre en main() con empezar_tiempos_ps2(GRUPO_ARRANQUE)
antes del primer paso: sin grupo abierto, marcar_tiempos_ps2 no anota nada.
"""
import os
import sys

sys.path.insert(0, os.path.dirname(__file__))
from prueba_textos_port import RAIZ, fichas  # noqa: E402

ARRANQUE = "codigo/sistema/arranque_ps2.c"
REINICIO_IOP = ("reiniciar_iop", "preparar_iop_sin_reinicio")

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def cuerpo_de(lista, nombre):
    """Fichas del cuerpo de la funcion 'nombre', sin sus llaves."""
    for i in range(len(lista) - 1):
        if lista[i][:2] != ("id", nombre) or lista[i + 1][:2] != ("sig", "("):
            continue
        # Parametros: nombre( ... ) y despues '{' (si no, es una llamada o una declaracion)
        j, nivel = i + 1, 0
        while j < len(lista):
            if lista[j][:2] == ("sig", "("):
                nivel += 1
            elif lista[j][:2] == ("sig", ")"):
                nivel -= 1
                if nivel == 0:
                    break
            j += 1
        j += 1
        if j >= len(lista) or lista[j][:2] != ("sig", "{"):
            continue
        nivel = 0
        for k in range(j, len(lista)):
            if lista[k][:2] == ("sig", "{"):
                nivel += 1
            elif lista[k][:2] == ("sig", "}"):
                nivel -= 1
                if nivel == 0:
                    return lista[j + 1:k]
    return []


def llamadas(cuerpo, nombre):
    """(posición, línea) de cada llamada a 'nombre'."""
    return [(i, cuerpo[i][2]) for i in range(len(cuerpo) - 1)
            if cuerpo[i][:2] == ("id", nombre) and cuerpo[i + 1][:2] == ("sig", "(")]


def main():
    with open(os.path.join(RAIZ, ARRANQUE), encoding="utf-8") as f:
        cuerpo = cuerpo_de(list(fichas(f.read())), "main")
    comprobar(cuerpo, "%s: no se encontró main()" % ARRANQUE)

    depuracion = llamadas(cuerpo, "inicializar_depuracion")
    comprobar(len(depuracion) == 1, "%s: inicializar_depuracion() aparece %d veces en main(); va una"
              % (ARRANQUE, len(depuracion)))
    reinicio = sorted(p for nombre in REINICIO_IOP for p in llamadas(cuerpo, nombre))
    comprobar(reinicio, "%s: main() no llama a %s" % (ARRANQUE, " ni a ".join(REINICIO_IOP)))
    if depuracion and reinicio:
        comprobar(depuracion[0][0] < reinicio[0][0],
                  "%s:%d: inicializar_depuracion() va antes del reinicio del IOP (línea %d)"
                  % (ARRANQUE, depuracion[0][1], reinicio[0][1]))

    grupo = [p for p in llamadas(cuerpo, "empezar_tiempos_ps2")
             if [f[:2] for f in cuerpo[p[0] + 2:p[0] + 4]] == [("id", "GRUPO_ARRANQUE"), ("sig", ")")]]
    comprobar(grupo, "%s: main() no abre el cronómetro con empezar_tiempos_ps2(GRUPO_ARRANQUE)" % ARRANQUE)
    pasos = llamadas(cuerpo, "marcar_tiempos_ps2")
    comprobar(pasos, "%s: main() no marca ningún paso del cronómetro" % ARRANQUE)
    if grupo and pasos:
        comprobar(grupo[0][0] < pasos[0][0],
                  "%s:%d: empezar_tiempos_ps2(GRUPO_ARRANQUE) va antes del primer paso (línea %d)"
                  % (ARRANQUE, grupo[0][1], pasos[0][1]))
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
