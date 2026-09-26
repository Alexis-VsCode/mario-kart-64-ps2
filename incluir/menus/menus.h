#ifndef MENUS_MENUS_H
#define MENUS_MENUS_H

#include <PR/os.h>
#include <juego/estructuras_comunes.h>
#include <juego/definiciones.h>

union PaqueteModoJuego {
    u8 modos[4];
    s32 word;
};

enum TiposFundidoMenu {
    MENU_FUNDIDO_TIPO_PRINCIPAL,
    MENU_FUNDIDO_TIPO_ATRAS,
    MENU_FUNDIDO_TIPO_DEMO,
    MENU_FUNDIDO_TIPO_DATOS,
    MENU_FUNDIDO_TIPO_OPCION,
    MENU_FUNDIDO_TIPO_MAX
};

enum SubMenuSeleccionTipo {
    NINGUNO_MENU_SUB,
    DATOS_MENU_SUB,
    SUB_MENU_MAPA_SELECCION_COPA = 0x01,
    SUB_MENU_MAPA_SELECCION_CIRCUITO,
    SUB_MENU_MAPA_SELECCION_OK,
    SUB_MENU_MAPA_SELECCION_BATALLA_CIRCUITO,
    SUB_MENU_DATOS_OPCIONES = 0x0B,
    SUB_MENU_DATOS_BORRAR_CONFIRMAR,
    SUB_MENU_DATOS_NO_PUEDE_BORRAR,
    SUB_MENU_OPCION_MIN = 0x15,
    SUB_MENU_OPCION_RETORNO_JUEGO_SELECCION = SUB_MENU_OPCION_MIN,
    SUB_MENU_OPCION_SONIDO_MODO,
    SUB_MENU_OPCION_COPIA_CONTROLLER_PAK,
    SUB_MENU_OPCION_BORRAR_TODOS_DATOS,
    SUB_MENU_OPCION_MAX = SUB_MENU_OPCION_BORRAR_TODOS_DATOS,
    SUB_MENU_BORRAR_MIN = 0x1E,
    SUB_MENU_BORRAR_ABANDONAR = SUB_MENU_BORRAR_MIN,
    SUB_MENU_BORRAR_BORRAR,
    SUB_MENU_BORRAR_MAX = SUB_MENU_BORRAR_BORRAR,
    SUB_MENU_GUARDADO_DATOS_BORRADO,
    SUB_MENU_COPIA_PAK_DESDE_MIN_FANTASMA = 0x28,
    SUB_MENU_COPIA_PAK_DESDE_GHOST1_1P = SUB_MENU_COPIA_PAK_DESDE_MIN_FANTASMA,
    SUB_MENU_COPIA_PAK_DESDE_GHOST2_1P,
    SUB_MENU_COPIA_PAK_DESDE_MAX_FANTASMA = SUB_MENU_COPIA_PAK_DESDE_GHOST2_1P,
    SUB_MENU_COPIA_PAK_ERROR_2J_MIN,
    SUB_MENU_COPIA_PAK_ERROR_SIN_FANTASMA_DATOS = SUB_MENU_COPIA_PAK_ERROR_2J_MIN,
    SUB_MENU_COPIA_PAK_ERROR_SIN_JUEGO_DATOS,
    SUB_MENU_COPIA_PAK_ERROR_SIN_PAK_2P,
    SUB_MENU_COPIA_PAK_ERROR_MALO_LECTURA_2P,
    SUB_MENU_COPIA_PAK_ERROR_2J_MAX = SUB_MENU_COPIA_PAK_ERROR_MALO_LECTURA_2P,
    SUB_MENU_COPIA_PAK_A_MIN_FANTASMA = 0x32,
    SUB_MENU_COPIA_PAK_A_GHOST1_2P = SUB_MENU_COPIA_PAK_A_MIN_FANTASMA,
    SUB_MENU_COPIA_PAK_A_GHOST2_2P,
    SUB_MENU_COPIA_PAK_A_MAX_FANTASMA = SUB_MENU_COPIA_PAK_A_GHOST2_2P,
    SUB_MENU_COPIA_PAK_ERROR_1J_MIN,
    SUB_MENU_COPIA_PAK_ERROR_SIN_PAK_1P = SUB_MENU_COPIA_PAK_ERROR_1J_MIN,
    SUB_MENU_COPIA_PAK_ERROR_MALO_LECTURA_1P,
    SUB_MENU_COPIA_PAK_ERROR_NO_PUEDE_CREAR_1P,
    SUB_MENU_COPIA_PAK_ERROR_SIN_PAGINAS_1P,
    SUB_MENU_COPIA_PAK_ERROR_1J_MAX,
    SUB_MENU_COPIA_PAK_AVISO_MIN = SUB_MENU_COPIA_PAK_ERROR_1J_MAX,
    SUB_MENU_COPIA_PAK_AVISO_ABANDONAR = SUB_MENU_COPIA_PAK_AVISO_MIN,
    SUB_MENU_COPIA_PAK_AVISO_COPIA,
    SUB_MENU_COPIA_PAK_AVISO_MAX = SUB_MENU_COPIA_PAK_AVISO_COPIA,
    SUB_MENU_COPIA_PAK_ACCION_MIN,
    SUB_MENU_COPIA_PAK_INICIO = SUB_MENU_COPIA_PAK_ACCION_MIN,
    SUB_MENU_COPIA_PAK_COPIANDO,
    SUB_MENU_COPIA_PAK_COMPLETADO,
    SUB_MENU_COPIA_PAK_ACCION_MAX = SUB_MENU_COPIA_PAK_COMPLETADO,
    SUB_MENU_COPIA_PAK_INCAPAZ_ERROR_MIN = 0x41,
    SUB_MENU_COPIA_PAK_INCAPAZ_COPIA_DESDE_1P = SUB_MENU_COPIA_PAK_INCAPAZ_ERROR_MIN,
    SUB_MENU_COPIA_PAK_INCAPAZ_LECTURA_DESDE_2P,
    SUB_MENU_COPIA_PAK_INCAPAZ_ERROR_MAX = SUB_MENU_COPIA_PAK_INCAPAZ_LECTURA_DESDE_2P,
    SUB_MENU_COPIA_PAK_CREAR_JUEGO_DATOS_INICIALIZACION = 0x46,
    SUB_MENU_COPIA_PAK_CREAR_JUEGO_DATOS_HECHO
};

enum MenuPrincipalTipoSeleccion {
    MENU_PRINCIPAL_NINGUNO,
    MENU_PRINCIPAL_OPCION,
    MENU_PRINCIPAL_DATOS,
    MENU_PRINCIPAL_SELECCION_JUGADOR,
    MENU_PRINCIPAL_SELECCION_MODO,
    MENU_PRINCIPAL_SELECCION_SUB_MODO,
    MENU_PRINCIPAL_SELECCION_OK,
    MENU_PRINCIPAL_OK_SELECCION_IR_ATRAS,
    MENU_PRINCIPAL_MODO_SUB_SELECCION_IR_ATRAS
};

enum JugadorSeleccionMenuSeleccionTipos {
    JUGADOR_SELECCION_MENU_NINGUNO,
    JUGADOR_SELECCION_MENU_PRINCIPAL,
    JUGADOR_SELECCION_MENU_OK,
    JUGADOR_SELECCION_MENU_OK_IR_ATRAS
};

enum DepuracionMenuSeleccionTipos {
    NINGUNO_MENU_DEPURACION,
    DEPURACION_MENU_DESACTIVADO,
    DEPURACION_MENU_DEPURACION_MODO,
    CIRCUITO_MENU_DEPURACION,
    DEPURACION_MENU_PANTALLA_MODO,
    JUGADOR_MENU_DEPURACION,
    DEPURACION_MENU_SONIDO_MODO,
    DEPURACION_MENU_DAR_TODOS_ORO_COPA,
    DEPURACION_MENU_OPCION_SELECCIONADO = 0x40
};

enum ControllerPakTiposSeleccionMenu {
    CONTROLLER_PAK_NINGUNO_MENU,
    CONTROLLER_PAK_REGISTRO_SELECCION_MENU,
    CONTROLLER_PAK_FIN_MENU,
    CONTROLLER_PAK_BORRAR_MENU,
    CONTROLLER_PAK_ABANDONAR_MENU,
    CONTROLLER_PAK_MENU_TABLA_JUEGO_DATOS,
    CONTROLLER_PAK_IR_MENU_A_BORRANDO,
    CONTROLLER_PAK_BORRANDO_MENU,
    CONTROLLER_PAK_ERROR_BORRAR_MENU_NO_BORRADO,
    CONTROLLER_PAK_MENU_BORRAR_ERROR_SIN_PAK,
    CONTROLLER_PAK_MENU_BORRAR_ERROR_PAK_CAMBIADO
};

enum CircuitoRegistrosMenuSeleccionTipos {
    CIRCUITO_REGISTROS_MENU_MIN,
    CIRCUITO_REGISTROS_MENU_RETORNO_MENU = CIRCUITO_REGISTROS_MENU_MIN,
    CIRCUITO_REGISTROS_MENU_BORRAR_REGISTROS,
    CIRCUITO_REGISTROS_MENU_BORRAR_FANTASMA,
    CIRCUITO_REGISTROS_MENU_MAX = CIRCUITO_REGISTROS_MENU_BORRAR_FANTASMA
};

enum CircuitoRegistrosSubMenuSeleccionTipos {
    CIRCUITO_REGISTROS_SUB_MENU_MIN,
    CIRCUITO_REGISTROS_SUB_MENU_ABANDONAR = CIRCUITO_REGISTROS_SUB_MENU_MIN,
    CIRCUITO_REGISTROS_SUB_MENU_BORRAR,
    CIRCUITO_REGISTROS_SUB_MENU_MAX = CIRCUITO_REGISTROS_SUB_MENU_BORRAR
};

enum DepuracionGotoEscenaTipos {
    CARRERA_GOTO_DEPURACION,
    FINAL_GOTO_DEPURACION,
    DEPURACION_GOTO_CREDITOS_SECUENCIA_PREDETERMINADO,
    DEPURACION_GOTO_CREDITOS_SECUENCIA_EXTRA
};

enum FundidoModoSeleccionTipos { NINGUNO_MODO_FUNDIDO, PRINCIPAL_MODO_FUNDIDO, LOGO_MODO_FUNDIDO };

enum ControllerPakTiposSentidoDesplazamiento {
    CONTROLLER_PAK_NINGUNO_DIR_DESPLAZAMIENTO,
    CONTROLLER_PAK_ABAJO_DIR_DESPLAZAMIENTO,
    CONTROLLER_PAK_ARRIBA_DIR_DESPLAZAMIENTO
};

void actualizar_menus(void);
void act_menu_opciones(struct Mando*, u16);
void act_menu_datos(struct Mando*, u16);
void circuito_datos_menu_act(struct Mando*, u16);
void logo_intro_menu_act(struct Mando*, u16);
void controller_pak_act_menu(struct Mando*, u16);
void act_menu_salpicadura(struct Mando*, u16);
void preparar_modo_juego_seleccionado(void);
void menu_principal_act(struct Mando*, u16);
bool liberar_punto_personaje_es(s32);
void seleccionar_act_menu_jugador(struct Mando*, u16);
void seleccionar_act_menu_circuito(struct Mando*, u16);
void cargar_estados_menu(s32);
void reiniciar_menu_destello_ciclo(void);
void fijar_modo_sonido(void);
bool es_pantalla_siendo_fundido(void);

extern s32 ojo_modelo_z_intro;
extern f32 escala_modelo_intro;
extern f32 rot_x_modelo_intro;
extern f32 rot_y_modelo_intro;
extern f32 rot_z_modelo_intro;
extern f32 pos_x_modelo_intro;
extern f32 pos_y_modelo_intro;
extern f32 pos_z_modelo_intro;

extern s32 tipo_fundido_menu;

extern s8 selecciones_cuadricula_personaje[4];
extern s8 personaje_cuadricula_es_seleccionado[4];
extern s8 seleccion_menu_sub;
extern s8 menu_principal_seleccion;
extern s8 jugador_seleccion_menu_seleccion;
extern s8 seleccion_menu_depuracion;
extern s8 controller_pak_seleccion_menu;
extern s8 pantalla_modo_lista_indice;
extern u8 sonido_modo;
extern s8 cantidad_jugador;
extern s8 versus_seleccion_cursor_resultado;
extern s8 contrarreloj_seleccion_cursor_resultado;
extern s8 batalla_resultado_cursor_seleccion;
extern s8 contrarreloj_indice_circuito_datos;
extern s8 circuito_registros_menu_seleccion;
extern s8 circuito_registros_sub_menu_seleccion;
extern s8 escena_goto_depuracion;
extern s8 inicializacion_jugador_fantasma;
extern s8 inicializacion_mapa_circuito;
extern s32 contador_tiempos_menu;
extern s32 temporizador_retardo_menu;
extern s8 mando_usar_demo;
extern s8 seleccion_copa;
extern s8 indice_circuito_en_copa;
extern s8 sin_ref_8018EE0C;

extern s32 seleccion_menu;
extern s32 seleccion_modo_fundido;
extern s8 selecciones_personaje[];

extern s8 juego_modo_menu_columna[];
extern s8 juego_modo_sub_menu_columna[4][3];
extern s8 id_demo_siguiente;
extern s8 controller_pak_renglon_tabla_seleccionado;
extern s8 controller_pak_renglones_tabla_visible[];
extern s8 controller_pak_sentido_desplazamiento;

extern const s8 seleccion_modo_jugador[];
extern const s32 juego_modo_jugador_seleccion[][3];
extern const s16 orden_circuito_copa[COPAS_NUM][CIRCUITOS_NUM_POR_COPA];

#endif
