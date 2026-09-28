// Textos del menu: nombres, mensajes y avisos que se dibujan con la fuente del menu

char* nombres_copa[] = {
    "COPA CHAMPIÑÓN",
    "COPA FLOR",
    "COPA ESTRELLA",
    "COPA ESPECIAL",
    "BATALLA",
    "COPA CHAMPIÑÓN",
    "COPA FLOR",
    "COPA ESTRELLA",
    "COPA ESPECIAL",
};

#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
char* nombres_circuito[] = {
#include "recursos/pistas/metadatos/nombres_circuito.inc.c"
};

char* duplicar_nombres_circuito[] = {
#include "recursos/pistas/metadatos/nombres_circuito.inc.c"
};
#else

#endif

char* duplicar_nombres_circuito_2[] = {
#include "recursos/pistas/metadatos/nombres_circuito.inc.c"
};

#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
char* nombres_circuito_depuracion[] = {
#include "recursos/pistas/metadatos/nombres_depuracion_circuito.inc.c"
};
#else

#endif

const s8 por_indice_copa_por_id_circuito[] = {
#include "recursos/pistas/metadatos/por_indice_copa_por_id_circuito.inc.c"
};

const s8 dato_800EFD64[] = { 0, 1, 4, 3, 5, 6, 2, 7 };

s8 seleccion_copa_por_id_circuito[] = {
#include "recursos/pistas/metadatos/seleccion_copa_por_id_circuito.inc.c"
};

char* texto_copa[] = {
    "NINGUNA",
    "BRONCE",
    "PLATA",
    "ORO",
};

char* nombres_personaje_depuracion[] = {
    "MARIO", "LUIGI", "YOSHI", "KINOPIO", "D.KONG", "WARIO", "PEACH", "KOOPA",
};

char* dato_800E76A8[] = {
    "MARIO",    "LUIGI", "YOSHI", "TOAD", "D.K.", "WARIO", "PEACH", "BOWSER",
    "ーーーー",
};

char* dato_800E76CC[] = {
    "50(",
    "100(",
    "150(",
    "EXTRA",
};

char* dato_800E76DC[] = {
    "50(",
    "100(",
    "150(",
    "EXTRA",
};

char* depuracion_pantalla_modo_nombres[] = {
    "1p", "2players UD", "2players LR", "3players", "4players",
};

char* depuracion_sonido_modo_nombres[] = {
    "stereo",
    "head phone",
    "xxx",
    "monaural",
};

char* sonido_nombres_modo[MODOS_SONIDO_NUM] = { "ESTÉREO", "AURICULARES", "", "MONO" };

char* texto_perder_victoria[] = {
    "¡VICTORIA!",
    "¡DERROTA!",
};

char* texto_tiempo_mejor[] = {
    "RÉCORDS",
    "MEJOR VUELTA",
};

char* texto_tiempo_vuelta = "TIEMPOS DE VUELTA";

char* texto_tiempo_prefijo[] = {
    "VUELTA 1",
    "VUELTA 2",
    "VUELTA 3",
    "TOTAL",
};

char* dato_800E7744[] = {
    "1.º", "2.º", "3.º", "4.º", "5.º", " ",
};

char* boton_pausa_texto[] = {
    "CONTINUAR", "REINTENTAR", "CAMBIAR PISTA", "CAMBIAR PILOTO", "SALIR", "REPETICIÓN", "GRABAR FANTASMA",
};

char* dato_800E7778[] = {
    "CLASIFICACIÓN VS",
    "CLASIFICACIÓN BATALLA",
};

// Titulos de los paneles de resultados del gran premio
char* texto_resultados = "RESULTADOS";
char* texto_ronda = "RONDA";
char* texto_puntos_piloto = "CLASIFICACIÓN";

// Puestos del resumen de versus (1.o, 2.o y 3.o) antes de las veces que se consiguieron
char* texto_puesto_versus[] = { "1.º ー", "2.º ー", "3.º ー" };

char texto_menu_anuncio_fantasma[] = "¡YA PUEDES RETAR AL FANTASMA!";

char* mando_sin_texto[] = { "CONECTA UN MANDO AL PUERTO 1", "Y VUELVE A ENCENDER LA CONSOLA." };

char* introduccion_batalla_texto[] = {
    "MODO BATALLA",
    "¡REVIENTA LOS GLOBOS RIVALES!",
    "SI PIERDES LOS 3, ¡QUEDAS FUERA!",
};

char datos_menu_texto[] = "CRUZ*VER DATOS  CUADRADO*SALIR";

char distancia_texto[] = "LONGITUD";

char* longitudes_circuito[] = {
#include "recursos/pistas/metadatos/longitudes_circuito.inc.c"
};

char* opcion_menu_texto[] = {
    "VOLVER AL MENÚ",
    "BORRAR RÉCORDS DE LA PISTA",
    "BORRAR FANTASMA DE LA PISTA",
};

char* dato_800E7840[] = {
    "SALIR",
    "BORRAR",
};

char* borrar_mejor_fantasma_texto[] = {
    "SE BORRARÁN LOS RÉCORDS", "Y LA MEJOR VUELTA DE", "ESTA PISTA. ¿DE ACUERDO?",

    "SE BORRARÁ EL FANTASMA",  "DE ESTA PISTA.",       "¿DE ACUERDO?",
};

char* dato_800E7860[] = {
    "NO SE PUEDE BORRAR",
    "EL FANTASMA",
};

char* menu_opcion_texto[] = {
    "VOLVER AL MENÚ PRINCIPAL",
    "SONIDO",
    "COPIAR FANTASMAS",
    "BORRAR TODOS LOS DATOS",
};

char* dato_800E7878[] = {
    "SE BORRARÁN TODOS LOS",
    "DATOS PARA SIEMPRE.",
    "¿QUIERES CONTINUAR?",
};

char* dato_800E7884[] = {
    "",
    "SE HAN BORRADO",
    "TODOS LOS DATOS.",
};

char* dato_800E7890[] = {
    "NO HAY MEMORY CARD",
    "EN LA RANURA 1.",
    "",
    "",

    "NO SE PUEDEN LEER",
    "LOS DATOS DE LA",
    "MEMORY CARD DE LA RANURA 1.",
    "",

    "NO SE PUEDEN CREAR LOS DATOS",
    "DEL JUEGO EN LA",
    "MEMORY CARD DE LA RANURA 1.",
    "",

    "NO SE PUDO COPIAR EL FANTASMA",
    "-- NO HAY ESPACIO LIBRE",
    "EN LA MEMORY CARD",
    "DE LA RANURA 1.",
};

char* dato_800E78D0[] = {
    "NO HAY FANTASMAS",
    "EN LA MEMORY CARD",
    "DE LA RANURA 2.",

    "LA MEMORY CARD DE LA",
    "RANURA 2 NO TIENE",
    "DATOS DE MARIO KART 64.",

    "COPIAR FANTASMAS DESDE",
    "OTRA MEMORY CARD NO",
    "ESTÁ DISPONIBLE EN PS2.",

    "NO SE PUEDEN LEER LOS",
    "DATOS DE LA MEMORY CARD",
    "DE LA RANURA 2.",
};

char* dato_800E7900[] = {
    "NO SE PUEDEN COPIAR",
    "LOS DATOS DE LA",
    "RANURA 1.",

    "NO SE PUEDEN LEER",
    "LOS DATOS DE LA",
    "RANURA 2.",
};

char* dato_800E7918[] = {
    "RANURA 1",
    "RANURA 2",
};

char* dato_800E7920[] = {
    "¿QUÉ FANTASMA QUIERES COPIAR?",
    "¿DÓNDE QUIERES COPIARLO?",
};

char* dato_800E7928[] = {
    "SE BORRARÁN LOS DATOS ACTUALES.",
    "¿DE ACUERDO?",
};

char* dato_800E7930[] = {
    "SALIR",
    "COPIAR",
};

char* dato_800E7938[] = {
    "COPIANDO",
    "COPIA TERMINADA",
};

char* dato_800E7940[] = {
    "NO SE DETECTA LA MEMORY CARD",
    "PARA GRABAR FANTASMAS,",
    "INSERTA UNA MEMORY CARD",
    "EN LA RANURA 1.",

    "NO SE PUEDEN LEER LOS",
    "DATOS DE LA MEMORY CARD.",
    "",
    "",

    "",
    "",
    "",
    "",

    "NO HAY ESPACIO SUFICIENTE",
    "EN LA MEMORY CARD PARA",
    "CREAR LOS DATOS DEL JUEGO.",
    "LIBERA ESPACIO Y PRUEBA DE NUEVO.",
};

char* dato_800E7980[] = {
    "PARA GRABAR FANTASMAS,",
    "INSERTA UNA MEMORY CARD",
    "EN LA RANURA 1.",
};

char* dato_800E798C[] = {
    "NO SE DETECTA",
    "LA MEMORY CARD.",
    "SI QUIERES GRABAR",
    "EL FANTASMA,",
    "INSERTA UNA",
    "MEMORY CARD",
    "EN LA RANURA 1.",

    "",
    "NO SE PUEDE GRABAR",
    "     EL FANTASMA.",
    "",
    "",
    "",
    "",

    "",
    "NO SE PUEDE GRABAR",
    "     EL FANTASMA.",
    "",
    "",
    "",
    "",

    "NO HAY ESPACIO",
    "LIBRE SUFICIENTE.",
    "",
    "-- NO SE PUDO",
    "GRABAR EL FANTASMA.",
    "",
    "",

    "",
    "NO SE PUEDEN CREAR",
    "     LOS DATOS.",
    "",
    "",
    "",
    "",

    "",
    "ESTE FANTASMA",
    "     YA SE HA GRABADO.",
    "",
    "",
    "",
    "",
};

char* dato_800E7A34[] = {
    "NO SE PUEDE GRABAR",
    "COMO FANTASMA.",
};

char* dato_800E7A3C[] = {
    "ELIGE EL ARCHIVO",
    "PARA GRABAR.",
};

char* dato_800E7A44 = "SIN DATOS";

char* dato_800E7A48[] = {
    "CREANDO LOS",
    "DATOS DE",
    "MARIO KART 64",
};

char* dato_800E7A54[] = {
    "NO SE PUEDEN CREAR LOS DATOS",
    "",
    "",
};

char* dato_800E7A60[] = {
    "SE BORRARÁN LOS",
    "DATOS ANTERIORES.",
    "¿DE ACUERDO?",
};

char* dato_800E7A6C[] = {
    "SALIR",
    "GRABAR",
};

char* dato_800E7A74[] = {
    "GRABANDO",
    "EL FANTASMA.",
    "ESPERA, POR FAVOR",
};

char* dato_800E7A80[] = {
    "NO SE GRABÓ",
    "EL FANTASMA.",
};

char* dato_800E7A88[] = {
    "HAS GANADO LA",
    "COPA DE ORO",
    "COPA DE PLATA",
    "COPA DE BRONCE",
};

char* dato_800E7A98 = "¡SUERTE LA PRÓXIMA VEZ!";

char* dato_800E7A9C[] = {
    "¡FELICIDADES!",
    "¡QUÉ PENA!",
};

char* texto_lugar[] = {
    "HAS QUEDADO", "   .º", "   .º", "   .º", "   .º", "   .º", "   .º", "   .º", "   .º",
};
