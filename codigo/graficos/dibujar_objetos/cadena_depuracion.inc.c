// Cadenas de la fuente de depuracion. La fuente solo tiene ASCII: los
// caracteres del espanol (UTF-8 o EUC-JP) se dibujan con su letra base.

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
        int bytes;
        int car = leer_caracter_es(parametro2, &bytes, NULL);
        // Sin signo: la tabla tiene una entrada por cada byte
        u8 letra = (car != CAR_ES_NINGUNO) ? (u8) caracter_es_base(car) : (u8) *parametro2;

        if (dato_800E5628[letra] >= 0) {
            funcion_800573E4(*x, *y, dato_800E5628[letra]);
        }
        texto_envoltura_depuracion(x, y);
        parametro2 += bytes;
    }
}
