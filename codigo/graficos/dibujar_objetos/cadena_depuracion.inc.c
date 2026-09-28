// Cadenas de la fuente de depuracion

void texto_envoltura_depuracion(s32* x, s32* y) {
    *x += 8;
    if (*x >= 296) {
        *x = 20;
        *y += 8;
    }
}

void imprimir_cadena_depuracion(s32* x, s32* y, char* parametro2) {
    *x += 20;
    *y += 20;

    while (*parametro2 != '\0') {
        if (dato_800E5628[(s32) *parametro2] >= 0) {
            funcion_800573E4(*x, *y, dato_800E5628[(s32) *parametro2]);
        }
        texto_envoltura_depuracion(x, y);
        parametro2++;
    }
}
