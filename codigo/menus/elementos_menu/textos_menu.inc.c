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

char texto_menu_anuncio_fantasma[] = "NOW-MEET THE COURSE GHOST!!!";

char* mando_sin_texto[] = { "CONNECT A CONTROLLER TO SOCKET 1,", "THEN POWER ON AGAIN" };

char* introduccion_batalla_texto[] = {
    "BATTLE GAME",
    "POP OPPOSING PLAYER'S BALLOONS",
    "WHEN ALL 3 ARE GONE,THEY ARE OUT!",
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
    "CONTROLLER 1 DOES NOT HAVE ",
    "N64 CONTROLLER PAK",
    "",
    "",

    "UNABLE TO READ ",
    "N64 CONTROLLER PAK DATA ",
    "FROM CONTROLLER 1",
    "",

    "UNABLE TO CREATE GAME DATA ",
    "FROM CONTROLLER 1 ",
    "N64 CONTROLLER PAK",
    "",

    "UNABLE TO COPY GHOST ",
    "-- INSUFFICIENT FREE PAGES ",
    "IN CONTROLLER 1 ",
    "N64 CONTROLLER PAK",
};

char* dato_800E78D0[] = {
    "NO GHOST DATA ",         "IN CONTROLLER 2 ",         "N64 CONTROLLER PAK",

    "NO MARIO KART 64 DATA ", "PRESENT IN CONTROLLER 2 ", "N64 CONTROLLER PAK",

    "CONTROLLER 2 ",          "DOES NOT HAVE ",           "N64 CONTROLLER PAK SET",

    "UNABLE TO READ DATA ",   "FROM CONTROLLER 2 ",       "N64 CONTROLLER PAK",
};

char* dato_800E7900[] = {
    "UNABLE TO COPY DATA ", "FROM CONTROLLER 1 ", "N64 CONTROLLER PAK",

    "UNABLE TO READ DATA ", "FROM CONTROLLER 2 ", "N64 CONTROLLER PAK",
};

char* dato_800E7918[] = {
    "CONTROLLER 1",
    "CONTROLLER 2",
};

char* dato_800E7920[] = {
    "WHICH FILE DO YOU WANT TO MAKE A COPY OF?",
    "TO WHICH FILE DO YOU WANT TO COPY?",
};

char* dato_800E7928[] = {
    "CURRENT DATA WILL BE ERASED,",
    "IS THIS OK?",
};

char* dato_800E7930[] = {
    "QUIT",
    "COPY",
};

char* dato_800E7938[] = {
    "COPYING",
    "DATA COPY COMPLETED",
};

char* dato_800E7940[] = {
    "NO N64 CONTROLLER PAK DETECTED",
    "TO SAVE GHOST DATA, ",
    "INSERT N64 CONTROLLER PAK ",
    "INTO CONTROLLER 1",

    "UNABLE TO READ ",
    "N64 CONTROLLER PAK DATA",
    "",
    "",

    "",
    "",
    "",
    "",

    "INSUFFICIENT FREE PAGES AVAILABLE ",
    "IN N64 CONTROLLER PAK TO CREATE ",
    "GAME DATA, PLEASE FREE 121 PAGES.",
    "SEE INSTRUCTION BOOKLET FOR DETAILS.",
};

char* dato_800E7980[] = {
    "TO SAVE GHOST DATA, ",
    "INSERT N64 CONTROLLER PAK ",
    "INTO CONTROLLER 1",
};

char* dato_800E798C[] = {
    "N64 CONTROLLER PAK ",
    "NOT DETECTED. ",
    "IF YOU WANT TO SAVE ",
    "THE GHOST DATA, ",
    "PLEASE INSERT ",
    "N64 CONTROLLER PAK ",
    "INTO CONTROLLER 1",

    "",
    "UNABLE TO SAVE ",
    "     THE GHOST",
    "",
    "",
    "",
    "",

    "",
    "UNABLE TO SAVE ",
    "     THE GHOST",
    "",
    "",
    "",
    "",

    "INSUFFICIENT ",
    "FREE PAGES AVAILABLE ",
    "",
    "-- GHOST DATA ",
    "COULD NOT BE SAVED",
    "",
    "",

    "",
    "CANNOT CREATE ",
    "     GAME DATA",
    "",
    "",
    "",
    "",

    "",
    "THIS GHOST IS ",
    "     ALREADY SAVED",
    "",
    "",
    "",
    "",
};

char* dato_800E7A34[] = {
    "RACE DATA CANNOT ",
    "BE SAVED FOR GHOST",
};

char* dato_800E7A3C[] = {
    "SELECT THE FILE ",
    "YOU WANT TO SAVE",
};

char* dato_800E7A44 = "NO DATA";

char* dato_800E7A48[] = {
    "CREATING ",
    "MARIO KART 64 ",
    "GAME DATA",
};

char* dato_800E7A54[] = {
    "CANNOT CREATE GAME DATA",
    "",
    "",
};

char* dato_800E7A60[] = {
    "THE PREVIOUS DATA ",
    "WILL BE ERASED, ",
    "IS THIS OK?",
};

char* dato_800E7A6C[] = {
    "QUIT",
    "SAVE",
};

char* dato_800E7A74[] = {
    "SAVING GHOST DATA",
    "",
    "PLEASE WAIT",
};

char* dato_800E7A80[] = {
    "UNABLE TO SAVE ",
    "THE GHOST",
};

char* dato_800E7A88[] = {
    "YOU ARE AWARDED THE",
    "GOLD CUP",
    "SILVER CUP",
    "BRONZE CUP",
};

char* dato_800E7A98 = "MAYBE NEXT TIME!";

char* dato_800E7A9C[] = {
    "CONGRATULATIONS!",
    "WHAT A PITY!",
};

char* texto_lugar[] = {
    "YOU PLACED", "    st", "    nd", "    rd", "    th", "    th", "    th", "    th", "    th",
};
