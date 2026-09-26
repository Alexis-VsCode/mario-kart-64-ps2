// Desplazamiento nuevo

void calcular_desplazamiento_pos_nuevo_objeto(s32 indice_objeto) {
    lista_objeto[indice_objeto].pos[0] = lista_objeto[indice_objeto].pos_origen[0] + lista_objeto[indice_objeto].offset[0];
    lista_objeto[indice_objeto].pos[1] = lista_objeto[indice_objeto].pos_origen[1] + lista_objeto[indice_objeto].offset[1];
    lista_objeto[indice_objeto].pos[2] = lista_objeto[indice_objeto].pos_origen[2] + lista_objeto[indice_objeto].offset[2];
}

void funcion_8008BF64(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    dato_80183E40[0] = objeto->pos[0];
    dato_80183E40[1] = objeto->pos[1];
    dato_80183E40[2] = objeto->pos[2];
    dato_80183E80[0] = objeto->angulo_sentido[0];
    dato_80183E80[1] = objeto->angulo_sentido[1];
    dato_80183E80[2] = objeto->angulo_sentido[2];
}

void funcion_8008BFC0(s32 indice_objeto) {
    lista_objeto[indice_objeto].desconocido_09C = lista_objeto[indice_objeto].pos[0];
    lista_objeto[indice_objeto].desconocido_09E = lista_objeto[indice_objeto].pos[1];
}

void funcion_8008BFFC(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    switch (objeto->desconocido_0DE) {
        case 1:
            if (objeto->desconocido_0AE == 1) {
                funcion_8008B620(indice_objeto);
            }
            break;
        case 2:
            switch (objeto->desconocido_0AE) {
                case 0:
                    break;
                case 1:
                    funcion_8008B6A4(indice_objeto);
                    break;
            }
            break;
        case 3:
            switch (objeto->desconocido_0AE) {
                case 0:
                    break;
                case 1:
                    funcion_8008B620(indice_objeto);
                    break;
            }
            break;
        case 4:
            switch (objeto->desconocido_0AE) {
                case 0:
                    break;
                case 1:
                    funcion_8008B620(indice_objeto);
                    break;
                case 2:
                    funcion_80086F60(indice_objeto);
                    break;
            }
            break;
        case 5:
            switch (objeto->desconocido_0AE) {
                case 0:
                    break;
                case 1:
                    funcion_8008B620(indice_objeto);
                    break;
                case 2:
                    funcion_80086F60(indice_objeto);
                    break;
            }
            break;
        case 6:
            switch (objeto->desconocido_0AE) {
                case 0:
                    break;
                case 1:
                    funcion_8008B620(indice_objeto);
                    break;
            }
            break;
        case 7:
            switch (objeto->desconocido_0AE) {
                case 0:
                    break;
                case 1:
                    funcion_80088228(indice_objeto);
                    break;
                case 2:
                    funcion_80088364(indice_objeto);
                    break;
            }
            break;
        case 0:
        default:
            break;
    }
}

SIN_USO void funcion_8008C1B8(SIN_USO s32 parametro0) {
}

SIN_USO void funcion_8008C1C0(SIN_USO s32 parametro0) {
}
