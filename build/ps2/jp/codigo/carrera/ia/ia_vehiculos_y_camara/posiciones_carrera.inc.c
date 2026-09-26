// Posiciones carrera

s32 desconocido_cpu_vehiculos_camara_camino_relleno[24];
Colision dato_80162E70;
s16 dato_80162EB0;
s16 dato_80162EB2;

ComportamientoCPU* comportamiento_cpu_circuitos[CIRCUITOS_NUM - 1];

s32 dato_80162F08[2];

s16 dato_80162F10[30];
s16 dato_80162F50[30];

s32 dato_80162F90[4];

Vec3f posicion_desplazamiento;
Vec3f dato_80162FB0;
Vec3f dato_80162FC0;
s16 temporizador_humo_tren;
s16 algun_punto_camino_mas_cercano;
s16 dato_80162FD0;
f32 porciento_finalizacion_circuito_por_puesto[JUGADORES_NUM];
s16 dato_80162FF8[12];
s16 dato_80163010[12];
f32 cpu_objetivo_rapidez[10];
s16 direccion_angulo_anterior[12];
f32 factor_posicion_pista[10];
f32 dato_80163090[10];
bool es_jugador_en_curva[10];
u16 actual_mas_cercano_camino_punto;
s16 es_jugador_nuevo_camino_punto;
s16 dato_801630E8[10];
s16 temporizador_humo_ferry;
s32 dato_80163100[10];
s32 dato_80163128[10];
s32 dato_80163150[10];
f32 anterior_jugador_ai_desplazamiento_x[10];
f32 anterior_jugador_ai_desplazamiento_z[10];
s16 vehiculo_sonido_render_contador;
s32 dato_801631CC;
PuntoCaminoPista* actual_pista_izquierda_camino;
PuntoCaminoPista* actual_pista_derecha_camino;
s16* actual_pista_seccion_tipos_camino;
s16* actual_camino_punto_esperado_rotacion_camino;
u16 dato_801631E0[12];
u16 dato_801631F8[10];
f32 actual_cpu_objetivo_rapidez;
f32 anterior_cpu_objetivo_rapidez[10];
s32 dato_80163238;
u16 cruzado_linea_meta[12];
u16 contador_sentido_incorrecto[12];
u16 es_sentido_incorrecto_jugador[12];
s32 anterior_vuelta_progreso_puntaje[10];
ComportamientoCPU* comportamiento_cpu_actual;
u16 actual_cpu_comportamiento_id[12];
u16 anterior_cpu_comportamiento_id[12];
u16 cpu_comportamiento_estado[12];
s16 angulo_jugador[12];
u16 jugadores_pista_seccion_id[12];
u16 dato_80163330[10];
u16 dato_80163344[2];
u16 dato_80163348[2];
u16 dato_8016334C[2];
u16 comportamiento_cpu_rapidez[12];
s32 camino_tamanio[4];
s32 jugador_actualizacion_incrementar;
s32 dato_8016337C;
s16 actual_jugador_mirada_adelante[12];
s16 dato_80163398[12];
s16 dato_801633B0[12];
s16 temporizador_intercambio_posicion[12];
s16 dato_801633E0[12];
s16 dato_801633F8[12];
s16 dato_80163410[4];
f32 dato_80163418[4];
f32 dato_80163428[4];
f32 dato_80163438[4];
s32 indice_camino_jugador;
f32 inicio_z_camino;
f32 g_jugador_z_anterior[10];
s16 mejor_clasificado_humano_jugador;
s16 es_en_extra;
s16 dato_8016347C;
s16 dato_8016347E;
s32 dato_80163480;
s32 dato_80163484;
s32 dato_80163488;
s16 dato_8016348C;
s16 cpu_entrando_camino_interseccion[12];
s16 cpu_saliendo_camino_interseccion[12];
s16 dato_801634C0[12];
s16 b_parada_ai_cruce[10];
s16 dato_801634EC;
s32 dato_801634F0;
s32 dato_801634F4;
PistaPosicionFactorInstruccion jugador_pista_posicion_factor_instruccion[10];
Camino2D* punto_camino_vehiculo_2d;
s32 longitud_camino_vehiculo_2d;
CosasTren lista_tren[TRENES_NUM];
u16 es_cruce_disparado_por_indice[CRUCES_NUM];
u16 temporizador_activo_cruce[CRUCES_NUM];
CosasBarcoPaleta barcos_paleta[BARCOS_PALETA_NUM];
CosasVehiculo lista_camion_caja[NUM_CARRERA_CAJA_CAMIONES];
CosasVehiculo lista_omnibus_escuela[NUM_CARRERA_ESCUELA_OMNIBUS];
CosasVehiculo lista_camion_cisterna[NUM_CARRERA_CISTERNA_CAMIONES];
CosasVehiculo lista_automovil[AUTOMOVILES_CARRERA_NUM];
s32 dato_80163DD8[4];
KartBomba karts_bomba[NUM_KARTS_BOMBA_MAX];
Colision dato_80164038[NUM_KARTS_BOMBA_MAX];
struct actores_vigente lista_actores_vigente[8];
CpuItemEstrategiaDatos cpu_item_estrategia[JUGADORES_NUM];
s16 dato_80164358;
s16 dato_8016435A;
s16 dato_8016435C;
s16 gp_actual_carrera_jugador_id_por_puesto[12];
s16 id_jugador_ant_por_puesto[12];
s32 cantidad_vuelta_por_id_jugador[10];
s32 gp_actual_carrera_puesto_por_id_jugador[10];
s32 anterior_gp_actual_carrera_puesto_por_id_jugador[10];
s32 gp_actual_carrera_puesto_por_duplicar_id_jugador[10];
u16 cantidad_camino_seleccionado;
u16 punto_camino_mas_cercano_por_id_jugador[12];
s32 num_camino_puntos_recorrido[10];
s16 jugador_obtener_por_id_personaje[10];
s32 dato_8016448C;
PuntoCaminoPista* camino_pista_actual;
f32 dato_80164498[4];
f32 porciento_finalizacion_vuelta_por_id_jugador[10];
f32 porciento_finalizacion_circuito_por_id_jugador[10];
s16 b_en_multi_seccion_camino[12];
f32 camino_y_jugador[10];
s16 dato_80164538[12];
PuntoCaminoPista* caminos_pista[4];
PuntoCaminoPista* caminos_izquierda_pista[4];
PuntoCaminoPista* caminos_derecha_pista[4];
s16* tipos_seccion_pista[4];
s16* rotacion_esperado_camino[4];
s16* pista_consecutivo_curva_cantidades[4];
u16 indice_camino_por_id_jugador[12];
u16 cantidad_camino_por_indice_camino[4];
s32 dato_801645D0[4];
s16* actual_pista_consecutivo_curva_cantidades_camino;
s32 dato_801645E8[4];
f32 dato_801645F8[4];
s32 dato_80164608[4];
f32 dato_80164618[4];
s32 dato_80164628[4];
f32 dato_80164638[4];
f32 dato_80164648[4];
f32 dato_80164658[4];
s16 punto_camino_mas_cercano_por_id_camara[4];
s16 dato_80164670[4];
s16 dato_80164678[4];
s16 dato_80164680[4];
f32 dato_80164688[4];
f32 dato_80164698;
f32 dato_8016469C;
f32 dato_801646A0;
s32 dato_801646A4;
s32 dato_801646A8;
s32 dato_801646AC;
s32 dato_801646B0;
s32 dato_801646B4;
s32 dato_801646B8;
s32 dato_801646BC;
s16 dato_801646C0[4];
u32 dato_801646C8;
u16 dato_801646CC;
desconocido_struct_46D0 dato_801646D0[4];

char* dato_800EB710 = "ゴール直後の強制ソート\n";
char* dato_800EB728 = "2PGPで片方がゴール直後の強制ソート\n";
char* dato_800EB74C = "順位計算エラー！！ (num %d) (rank %d) (e_rank %d)\n";
char* dato_800EB780 = "バイパス切り替え エラー!!!(num %d  org_bipas %d  bipas %d)\n";
char* dato_800EB7BC = "(%d) rap %3d  rate_count_F %10.2f  rap_count_F %10.2f  area %5d \n";
char* dato_800EB800 = "迷路に突入！ enemy %d (%d --> %d)\n";
char* dato_800EB824 = "迷路から出た！ enemy %d (%d --> %d)\n";
char* dato_800EB84C = "enemy voice set (%d  slip_flag %x  weapon %x)\n";
char* dato_800EB87C = "スピンヴォイス！！(%d , name %d)\n";
char* dato_800EB8A0 = "ダメージヴォイス！！(%d, name %d)\n";
char* dato_800EB8C4 = "===== ENEMY DRIVE SUB (%d) =====\n";
char* dato_800EB8E8 = "ENEMY END(手抜き)\n\n";
char* dato_800EB8FC = "ENEMY END(手抜き)\n\n";
char* dato_800EB910 = "(1)enemy stick angle over!! (%d)\n";
char* dato_800EB934 = "ENEMY END\n\n";
char* dato_800EB940 = "(2)enemy stick angle over!! (%d)\n";
char* dato_800EB964 = "ENEMY END\n\n";
char* dato_800EB970 = "AREA ERR!!! (現在のセンターライン %d に未登録のグループです) %d\n";
char* dato_800EB9B4 = "AREA ERR!!! (未登録のグループです) %d\n";
char* dato_800EB9DC = "get_oga_area_sub_BP() ... エリアが見つからないッス！ (b_num = %d)\n";
char* dato_800EBA20 = "  状況: (%d, %d, %d) \n";
char* dato_800EBA38 = "<%d> (%d, %d, %d) [%d] lng %f\n";
// Wario Stadium Jump failed! ! ! (area %d, y %7.2f)
char* dato_800EBA58 = "ワリオスタジアム  ジャンプ失敗！！！ (area %d, y %7.2f)\n";
char* dato_800EBA94 = "水に落ちた！！  センターラインに強制移動しました (num %d: area %d ) (%d,%d,%d)\n";
char* dato_800EBAE4 = "こーすあうと！！（手抜き中:バンプ有り）  センターラインに強制移動しました (num %d: area %d ==>%d) "
                   "(group %d) (%d,%d,%d)\n";
char* dato_800EBB60 = "こーすあうと！！（手抜き中:バンプ無し）  センターラインに強制移動しました (num %d: area %d ==>%d) "
                   "(group %d) (%d,%d,%d)\n";
char* dato_800EBBDC = "こーすあうと！！！    エリアを再計算しました (num %d: area %d ==>%d)\n";
char* dato_800EBC24 = "直接指定のBOM(%d) (%7.2f, %7.2f, %7.2f) \n";
char* dato_800EBC50 = "BOM HIT CHECK\n";
char* dato_800EBC60 = "BOM HIT !!!!! (%d)\n";
char* dato_800EBC74 = "BOM待機\n";
char* dato_800EBC80 = "RESULT BOM area(%d)\n";
char* dato_800EBC98 = "BOM が 落ちました。\n";
char* dato_800EBCB0 = "カメ用火柱 SET 失敗 (TABLE IS FULL)\n";
char* dato_800EBCD8 = "赤ガメ火柱セットエラー！ (category %d)\n";
char* dato_800EBD00 = "青ガメ火柱セットエラー！ (category %d)\n";
char* dato_800EBD28 = "トゲガメ火柱セットエラー！ (category %d)\n";
char* dato_800EBD54 = "カメ火柱初期化！！\n";
// Center line initialization
char* dato_800EBD68 = "センターライン初期化\n";
char* dato_800EBD80 = "MAP NUMBER %d\n";
char* dato_800EBD90 = "center_EX ptr      = %x %x (%x)\n";
char* dato_800EBDB4 = "\n";
char* dato_800EBDB8 = "center_BP[%d] ptr         = %x %x (%x)\n";
char* dato_800EBDE0 = "side_point_L_BP[%d] ptr   = %x %x (%x)\n";
char* dato_800EBE08 = "side_point_R_BP[%d] ptr   = %x %x (%x)\n";
char* dato_800EBE30 = "curve_BP[%d] ptr          = %x %x (%x)\n";
char* dato_800EBE58 = "angle_BP[%d] ptr          = %x %x (%x)\n";
char* dato_800EBE80 = "short_cut_data_BP[%d] ptr = %x %x (%x)\n";
char* dato_800EBEA8 = "\n";
char* dato_800EBEAC = "小川の使用メモリー合計 = %d\n";
char* dato_800EBECC = "敵初期化\n";
char* dato_800EBED8 = "敵初期化終了\n";
char* dato_800EBEE8 = "バイパス CENTER LINE 分割開始\n";
char* dato_800EBF08 = "センターラインをROMから読みます (map:%d)\n";
char* dato_800EBF34 = "ROM center (BP%d) line adr. = %x (%x)\n";
char* dato_800EBF5C = "センターラインを計算します (map:%d)\n";
char* dato_800EBF84 = "center (BP%d) line adr. = %x (%x)\n";
char* dato_800EBFA8 = "BP center_point_number : %d\n";
char* dato_800EBFC8 = "センターライン データ エラー！！\n";
char* dato_800EBFEC = "バイパス CENTER LINE 分割終了 (%d -> %d 個)\n";
// No center line. (map: %d)
char* dato_800EC01C = "センターラインが ありません。(map:%d)\n";
char* dato_800EC044 = "サイドポイント計算 (バイパス %d)\n";
char* dato_800EC068 = "カーブデータ計算 (バイパス %d)\n";
// No center line. (map: %d)
char* dato_800EC088 = "センターラインが ありません。(map:%d)\n";
char* dato_800EC0B0 = "アングルデータ計算 (バイパス %d) \n";
// No center line. (map: %d)
char* dato_800EC0D4 = "センターラインが ありません。(map:%d)\n";
char* dato_800EC0FC = "ショートカットデータ計算 (バイパス %d)\n";
char* dato_800EC124 = "extern POINT rom_center_KT%d_BP%d[] = {\n";
char* dato_800EC150 = "\t{%d,%d,%d,%d},\n";
char* dato_800EC164 = "\t0x8000,0x8000,0x8000,0\n};\n\n";
char* dato_800EC184 = "area read from ROM (%d)\n";
char* dato_800EC1A0 = "ノーマルジャンプ！！！(%d)\n";
char* dato_800EC1BC = "ターボオン！！！(%d)\n";
// No cutting corners! ! ! (%d)
char* dato_800EC1D4 = "手抜き禁止！！！(%d)\n";
char* dato_800EC1EC = "アクション開始データエラー！(num %d, act %d)\n";
char* dato_800EC21C = "アクション終了データエラー！(num %d,  act %d,  old_act_num %d)\n";
char* dato_800EC25C = "SL : center_point_number : %d\n";
char* dato_800EC27C = "SL: CENTER LINE 分割開始\n";
char* dato_800EC298 = "SL: CENTER LINE 分割終了 (%d -> %d 個)\n";
char* dato_800EC2C0 = "SHIP : center_point_number : %d\n";
char* dato_800EC2E4 = "SHIP: CENTER LINE 分割開始\n";
char* dato_800EC300 = "SHIP: CENTER LINE 分割終了 (%d -> %d 個)\n";
char* dato_800EC32C = "汎用OBJキャラ初期化\n";
char* dato_800EC344 = "SL OBJ設定\n";
char* dato_800EC350 = "SHIP OBJ設定\n";
char* dato_800EC360 = "トラックOBJ設定\n";
char* dato_800EC374 = "バスOBJ設定\n";
char* dato_800EC384 = "タンクOBJ設定\n";
char* dato_800EC394 = "RV OBJ設定\n";
char* dato_800EC3A0 = "汎用OBJキャラ初期化終了\n";
char* dato_800EC3BC = "クラクション (num %d, permit %d, %d)\n";
char* dato_800EC3E4 = "OGA CAMERA INIT (%d)\n";
char* dato_800EC3FC = "OGA CAMERA INIT END\n";
char* dato_800EC414 = "高速カメラ ERR !!! (ncx = %f)\n";
char* dato_800EC434 = "高速カメラ ERR !!! (ncz = %f)\n";
char* dato_800EC454 = "高速カメラ ERR !!! (ecx = %f)\n";
char* dato_800EC474 = "高速カメラ ERR !!! (ecz = %f)\n";
char* dato_800EC494 = "OGA DRIVERS POINT CAMERA MODE \n";
char* dato_800EC4B4 = "OGA WINNER CAMERA MODE \n";
char* dato_800EC4D0 = "OGA TIMEATTACK QUICK CAMERA INIT \n";
char* dato_800EC4F4 = "OGA BATTLE CAMERA INIT win(%d)\n";
char* dato_800EC514 = "GOAL! <<rank 1>> camera %d  rank %d\n";
char* dato_800EC53C = "GOAL! <<rank 2,3,4>> camera %d  rank %d\n";
char* dato_800EC568 = "GOAL! <<rank 5,6,7,8>> camera %d  rank %d\n";
char* dato_800EC594 = "カメラとカートが衝突しました！！！  (%d)\n";
char* dato_800EC5C0 = "<<< ITEM OBJ NUMBER ERR !! >>> item %d  obj_num %d \n";
char* dato_800EC5F8 = "<<< BANANA SET 失敗 >>> obj_num %d   zure %f \n";
char* dato_800EC628 = "BANANA 所有者チェックに引っ掛かりました。(num %d)\n";
char* dato_800EC65C = "理由: EXISTOBJ \n";
char* dato_800EC670 = "理由: category \n";
char* dato_800EC684 = "理由: sparam \n";
char* dato_800EC694 = "理由: num \n";
char* dato_800EC6A0 = "BANANA HOLD (num %d  time %d   hold_time %d)\n";
char* dato_800EC6D0 = "設置 BANANA 所有者チェックに引っ掛かりました。(num %d)\n";
char* dato_800EC708 = "理由: EXISTOBJ \n";
char* dato_800EC71C = "理由: category \n";
char* dato_800EC730 = "理由: sparam \n";
char* dato_800EC740 = "理由: num \n";
char* dato_800EC74C = "BANANA 置きました。 (num %d)\n";
char* dato_800EC76C = "<<< BANANA NAGE SET 失敗 >>> obj_num %d \n";
char* dato_800EC798 = "BANANA NAGE MOVE 所有者チェックに引っ掛かりました。(num %d)\n";
char* dato_800EC7D8 = "理由: EXISTOBJ \n";
char* dato_800EC7EC = "理由: category \n";
char* dato_800EC800 = "理由: sparam \n";
char* dato_800EC810 = "理由: num \n";
char* dato_800EC81C = "BANANA NAGE END 所有者チェックに引っ掛かりました。(num %d)\n";
char* dato_800EC858 = "理由: EXISTOBJ \n";
char* dato_800EC86C = "理由: category \n";
char* dato_800EC880 = "理由: sparam \n";
char* dato_800EC890 = "理由: num \n";
char* dato_800EC89C = "G_SHELL HOLD (num %d  time %d   hold_time %d)\n";
char* dato_800EC8CC = "<<< G_SHELL SET 失敗 >>> obj_num %d \n";
char* dato_800EC8F4 = "<<< G_SHELL SET 失敗 >>> object_count %d \n";
char* dato_800EC920 = "G_SHELL 所有者チェックに引っ掛かりました。(num %d)\n";
char* dato_800EC954 = "理由: EXISTOBJ \n";
char* dato_800EC968 = "理由: category \n";
char* dato_800EC97C = "理由: sparam \n";
char* dato_800EC98C = "理由: num \n";
char* dato_800EC998 = "発射直前 G_SHELL 所有者チェックに引っ掛かりました。(num %d)\n";
char* dato_800EC9D8 = "理由: EXISTOBJ \n";
char* dato_800EC9EC = "理由: category \n";
char* dato_800ECA00 = "理由: sparam \n";
char* dato_800ECA10 = "理由: num \n";
char* dato_800ECA1C = "G_SHELL 発射 (num %d)\n";
char* dato_800ECA34 = "R_SHELL HOLD (num %d  time %d   hold_time %d  obj_num %d)\n";
char* dato_800ECA70 = "<<< R_SHELL SET 失敗 >>> obj_num %d \n";
char* dato_800ECA98 = "<<< R_SHELL SET 失敗 >>> object_count %d \n";
char* dato_800ECAC4 = "R_SHELL 所有者チェックに引っ掛かりました。(num %d)\n";
char* dato_800ECAF8 = "理由: EXISTOBJ \n";
char* dato_800ECB0C = "理由: category \n";
char* dato_800ECB20 = "理由: sparam \n";
char* dato_800ECB30 = "理由: num \n";
char* dato_800ECB3C = "R_SHELL SHOOT (num %d  time %d   hold_time %d  obj_num %d)\n";
char* dato_800ECB78 = "発射直前 R_SHELL 所有者チェックに引っ掛かりました。(num %d)\n";
char* dato_800ECBB8 = "理由: EXISTOBJ \n";
char* dato_800ECBCC = "理由: category \n";
char* dato_800ECBE0 = "理由: sparam \n";
char* dato_800ECBF0 = "理由: num \n";
char* dato_800ECBFC = "R_SHELL 発射 (num %d)\n";
char* dato_800ECC14 = "S_BANANA HOLD (num %d  time %d   hold_time %d)\n";
char* dato_800ECC44 = "<<< SUPER_BANANA SET 失敗 >>> obj_num %d \n";
char* dato_800ECC70 = "<<< SUPER_BANANA SET 失敗 >>> object_count %d \n";
char* dato_800ECCA0 = "S_BANANA 所有者チェックに引っ掛かりました。(num %d)\n";
char* dato_800ECCD8 = "理由: category \n";
char* dato_800ECCEC = "理由: sparam \n";
char* dato_800ECCFC = "理由: sb_ok \n";
char* dato_800ECD0C = "S_BANANA RELEASE (num %d  time %d )\n";
char* dato_800ECD34 = "<<< FAKE IBOX SET 失敗 >>> obj_num %d \n";
char* dato_800ECD5C = "IBOX 所有者チェックに引っ掛かりました。(num %d)\n";
char* dato_800ECD90 = "理由: EXISTOBJ \n";
char* dato_800ECDA4 = "理由: category \n";
char* dato_800ECDB8 = "理由: sparam \n";
char* dato_800ECDC8 = "理由: num \n";
char* dato_800ECDD4 = "FBOX HOLD (num %d  time %d   hold_time %d)\n";
char* dato_800ECE00 = "設置 IBOX 所有者チェックに引っ掛かりました。(num %d)\n";
char* dato_800ECE38 = "理由: EXISTOBJ \n";
char* dato_800ECE4C = "理由: category \n";
char* dato_800ECE60 = "理由: sparam \n";
char* dato_800ECE70 = "理由: num \n";
char* dato_800ECE7C = "雷START (%d)\n";
char* dato_800ECE8C = "雷END (%d)\n";
char* dato_800ECE98 = "---------- 表彰台初期化\n";
char* dato_800ECEB4 = "map_number = %d - > 20 書き換え中。\n";
char* dato_800ECEDC = "OGA 表彰 move 開始\n";
char* dato_800ECEF0 = "４位の人の表示をコールしました。\n";
char* dato_800ECF14 = "表彰台に到着\n";
// Everyone gather!
char* dato_800ECF24 = "全員集合！\n";
char* dato_800ECF30 = "道路に到着\n";
char* dato_800ECF3C = "４位の人終了\n";
char* dato_800ECF4C = "OGA 表彰 move 終了\n";
char* dato_800ECF60 = "OGAWA DEBUG DRAW\n";

s16 obtener_angulo_entre_camino(Vec3f parametro0, Vec3f parametro1) {
    s16 devuelto_temporal;
    s16 phi_v1;

    devuelto_temporal = obtener_angulo_xz_entre_puntos(parametro0, parametro1);
    phi_v1 = devuelto_temporal;
    if (es_modo_espejo != 0) {
        phi_v1 = -devuelto_temporal;
    }
    return phi_v1;
}

bool chocar_con_vehiculo_es(f32 vehiculo_x, f32 vehiculo_z, f32 velocidad_x_vehiculo, f32 velocidad_z_vehiculo, f32 distancia_x,
                             f32 distancia_y, f32 jugador_x, f32 jugador_z) {
    f32 velocidad;
    f32 temporal_f18;

    velocidad = sqrtf((velocidad_x_vehiculo * velocidad_x_vehiculo) + (velocidad_z_vehiculo * velocidad_z_vehiculo));
    if (velocidad < 0.01f) {
        return false;
    }
    temporal_f18 =
        ((velocidad_x_vehiculo / velocidad) * (jugador_x - vehiculo_x)) + ((velocidad_z_vehiculo / velocidad) * (jugador_z - vehiculo_z));
    if ((-distancia_x < temporal_f18) && (temporal_f18 < distancia_x)) {
        temporal_f18 = ((velocidad_z_vehiculo / velocidad) * (jugador_x - vehiculo_x)) +
                   (-(velocidad_x_vehiculo / velocidad) * (jugador_z - vehiculo_z));
        if ((-distancia_y < temporal_f18) && (temporal_f18 < distancia_y)) {
            return true;
        }
    }
    return false;
}

void ajustar_posicion_por_angulo(Vec3f pos_nuevo, Vec3f pos_viejo, s16 orientacion_y) {
    f32 x_dist;
    f32 z_dist;
    f32 temporal1;
    f32 temporal2;
    f32 seno;
    f32 coseno;

    if (es_modo_espejo != 0) {
        orientacion_y = -orientacion_y;
    }
    x_dist = pos_nuevo[0] - pos_viejo[0];
    z_dist = pos_nuevo[2] - pos_viejo[2];
    seno = senos(orientacion_y);
    coseno = coss(orientacion_y);
    temporal1 = ((x_dist * coseno) + (z_dist * seno));
    temporal2 = ((z_dist * coseno) - (x_dist * seno));
    pos_nuevo[0] = pos_viejo[0] + temporal1;
    pos_nuevo[2] = pos_viejo[2] + temporal2;
}

s32 renderizar_banderas_distancia_vehiculo_conjunto(Vec3f pos_vehiculo, f32 renderizar_distancia, s32 banderas) {
    Camara* camara;
    Jugador* jugador;
    f32 x;
    f32 z;
    f32 jugador_x;
    f32 jugador_z;
    s32 i;
    s32 bandera;
    s8 pantallas_num;

    x = pos_vehiculo[0];
    z = pos_vehiculo[2];
    switch (modo_pantalla_activo) {
        case MODO_PANTALLA_1P:
            pantallas_num = 1;
            break;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            pantallas_num = 2;
            break;
        case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
            pantallas_num = cantidad_jugador;
            break;
        default:
            pantallas_num = 1;
            break;
    }
    bandera = banderas;
    if (!modo_demo) {
        jugador = jugador_uno;
        for (i = 0; i < cantidad_jugador; i++, jugador++) {
            if (((jugador->type & HUMANO_JUGADOR) != 0) && ((jugador->type & CPU_JUGADOR) == 0)) {
                jugador_x = jugador->pos[0];
                jugador_z = jugador->pos[2];

                if (((jugador_x - renderizar_distancia) < x) && ((jugador_x + renderizar_distancia) > x) &&
                    ((jugador_z - renderizar_distancia) < z) && ((jugador_z + renderizar_distancia) > z)) {
                    bandera |= (VEHICULO_RENDER << i);
                } else {
                    bandera &= ~(VEHICULO_RENDER << i);
                }
            }
        }
    } else {
        camara = camara1;
        for (i = 0; i < pantallas_num; i++, camara++) {
            jugador_x = camara->pos[0];
            jugador_z = camara->pos[2];
            if (((jugador_x - renderizar_distancia) < x) && (x < (jugador_x + renderizar_distancia)) &&
                ((jugador_z - renderizar_distancia) < z) && (z < (jugador_z + renderizar_distancia))) {
                bandera |= (VEHICULO_RENDER << i);
            } else {
                bandera &= ~(VEHICULO_RENDER << i);
            }
        }
    }
    return bandera;
}

void detectar_sentido_jugador_incorrecto(s32 id_jugador, Jugador* jugador) {
    s16 jugador_angulo;
    s16 difference_rotacion;
    s16 angulo_punto_camino;
    s16 indice_camino;
    u32 punto_camino;

    indice_camino = (s16) indice_camino_por_id_jugador[id_jugador];
    punto_camino = punto_camino_mas_cercano_por_id_jugador[id_jugador];

    jugador_angulo = (s16) ((s16) jugador->rotacion[1] / GRADOS(1));
    angulo_punto_camino = (s16) ((s16) rotacion_esperado_camino[indice_camino][punto_camino] / GRADOS(1));

    difference_rotacion = jugador_angulo - angulo_punto_camino;

    if (difference_rotacion < 0) {
        difference_rotacion = -difference_rotacion;
    }

    if ((num_camino_puntos_recorrido[id_jugador] < anterior_vuelta_progreso_puntaje[id_jugador]) &&
        (difference_rotacion >= SEVERO_INCORRECTO_SENTIDO_MIN) && (difference_rotacion < SEVERO_INCORRECTO_SENTIDO_MAX)) {
        contador_sentido_incorrecto[id_jugador]++;
        if ((contador_sentido_incorrecto[id_jugador]) >= INCORRECTO_SENTIDO_FRAMES_LIMITE) {
            es_sentido_incorrecto_jugador[id_jugador] = 1;
            contador_sentido_incorrecto[id_jugador] = INCORRECTO_SENTIDO_FRAMES_LIMITE;
            jugadores[id_jugador].efectos |= EFECTO_REVERSA;
        }
    } else if ((difference_rotacion < SEVERO_CORRECTO_SENTIDO_MIN) ||
               (difference_rotacion >= SEVERO_CORRECTO_SENTIDO_MAX)) {
        es_sentido_incorrecto_jugador[id_jugador] = 0;
        contador_sentido_incorrecto[id_jugador] = 0;
        jugadores[id_jugador].efectos &= ~EFECTO_REVERSA;
    }
    anterior_vuelta_progreso_puntaje[id_jugador] = num_camino_puntos_recorrido[id_jugador];
}

void fijar_puestos(void) {
    s32 id_jugador_a_intercambio;
    f32 finalizacion_circuito_a_intercambio;
    s32 id_jugador_por_puesto[8];
    s32 id_jugador_ant;
    SIN_USO s32 relleno;
    s32 jugador_num;
    s32 puesto;
    s32 id_jugador;
    s32 alto_puesto;

    switch (seleccion_modo) {
        case BATALLA:
        default:
            return;
        case GRAN_PREMIO:
        case CONTRARRELOJ:
            jugador_num = JUGADORES_NUM;
            break;
        case VERSUS:
            jugador_num = cantidad_jugador;
            break;
    }

    if (dato_8016348C == 0) {
        for (puesto = 0; puesto < jugador_num; puesto++) {
            id_jugador = gp_actual_carrera_jugador_id_por_puesto[puesto];
            id_jugador_por_puesto[puesto] = id_jugador;
            porciento_finalizacion_circuito_por_puesto[puesto] = porciento_finalizacion_circuito_por_id_jugador[id_jugador];
        }
    } else {
        for (puesto = 0; puesto < jugador_num; puesto++) {
            id_jugador = gp_actual_carrera_jugador_id_por_puesto[puesto];
            id_jugador_por_puesto[puesto] = id_jugador;
            porciento_finalizacion_circuito_por_puesto[puesto] = -tiempo_jugador_ultimo_tocado_linea_meta[id_jugador];
        }
    }

    for (puesto = 0; puesto < jugador_num - 1; puesto++) {
        if ((jugadores[gp_actual_carrera_jugador_id_por_puesto[puesto]].type & MODO_CINEMATICA_JUGADOR)) {
            continue;
        }

        for (alto_puesto = puesto + 1; alto_puesto < jugador_num; alto_puesto++) {
            if (porciento_finalizacion_circuito_por_puesto[puesto] < porciento_finalizacion_circuito_por_puesto[alto_puesto]) {
                if (!(jugadores[gp_actual_carrera_jugador_id_por_puesto[alto_puesto]].type & MODO_CINEMATICA_JUGADOR)) {
                    id_jugador_a_intercambio = id_jugador_por_puesto[puesto];
                    id_jugador_por_puesto[puesto] = id_jugador_por_puesto[alto_puesto];
                    id_jugador_por_puesto[alto_puesto] = id_jugador_a_intercambio;
                    finalizacion_circuito_a_intercambio = porciento_finalizacion_circuito_por_puesto[puesto];
                    porciento_finalizacion_circuito_por_puesto[puesto] = porciento_finalizacion_circuito_por_puesto[alto_puesto];
                    porciento_finalizacion_circuito_por_puesto[alto_puesto] = finalizacion_circuito_a_intercambio;
                }
            }
        }
    }

    for (puesto = 0; puesto < JUGADORES_NUM; puesto++) {
        anterior_gp_actual_carrera_puesto_por_id_jugador[puesto] = gp_actual_carrera_puesto_por_id_jugador[puesto];
    }

    for (puesto = 0; puesto < jugador_num; puesto++) {
        gp_actual_carrera_jugador_id_por_puesto[puesto] = id_jugador_por_puesto[puesto];
        gp_actual_carrera_puesto_por_id_jugador[id_jugador_por_puesto[puesto]] = puesto;
    }
    for (puesto = 0; puesto < jugador_num; puesto++) {
        id_jugador_ant = id_jugador_ant_por_puesto[puesto];
        id_jugador_por_puesto[puesto] = id_jugador_ant;
        porciento_finalizacion_circuito_por_puesto[puesto] = porciento_finalizacion_circuito_por_id_jugador[id_jugador_ant];
    }

    for (puesto = 0; puesto < jugador_num - 1; puesto++) {
        for (alto_puesto = puesto + 1; alto_puesto < jugador_num; alto_puesto++) {
            if (porciento_finalizacion_circuito_por_puesto[puesto] < porciento_finalizacion_circuito_por_puesto[alto_puesto]) {
                id_jugador_a_intercambio = id_jugador_por_puesto[puesto];
                id_jugador_por_puesto[puesto] = id_jugador_por_puesto[alto_puesto];
                id_jugador_por_puesto[alto_puesto] = id_jugador_a_intercambio;
                finalizacion_circuito_a_intercambio = porciento_finalizacion_circuito_por_puesto[puesto];
                porciento_finalizacion_circuito_por_puesto[puesto] = porciento_finalizacion_circuito_por_puesto[alto_puesto];
                porciento_finalizacion_circuito_por_puesto[alto_puesto] = finalizacion_circuito_a_intercambio;
            }
        }
    }

    for (puesto = 0; puesto < jugador_num; puesto++) {
        gp_actual_carrera_puesto_por_duplicar_id_jugador[id_jugador_por_puesto[puesto]] = puesto;
        id_jugador_ant_por_puesto[puesto] = id_jugador_por_puesto[puesto];
    }
}

void actualizar_clasificacion_jugador(void) {
    f32 temporal_f0;
    SIN_USO s32 relleno;
    s32 ids_jugador[8];
    s32 temporal_a0;
    s32 temporal_t2_2;
    s32 comparar_indice;
    s32 i;
    s32 num_racers;

    switch (seleccion_modo) {
        case BATALLA:
        default:
            return;
        case GRAN_PREMIO:
        case CONTRARRELOJ:
            num_racers = 8;
            break;
        case VERSUS:
            num_racers = cantidad_jugador;
            break;
    }

    for (i = 0; i < num_racers; i++) {
        temporal_a0 = gp_actual_carrera_jugador_id_por_puesto[i];
        ids_jugador[i] = temporal_a0;
        porciento_finalizacion_circuito_por_puesto[i] = -tiempo_jugador_ultimo_tocado_linea_meta[temporal_a0];
    }

    for (i = 0; i < (num_racers - 1); i++) {
        for (comparar_indice = i + 1; comparar_indice < num_racers; comparar_indice++) {
            if (porciento_finalizacion_circuito_por_puesto[i] < porciento_finalizacion_circuito_por_puesto[comparar_indice]) {
                temporal_t2_2 = ids_jugador[i];
                ids_jugador[i] = ids_jugador[comparar_indice];
                ids_jugador[comparar_indice] = temporal_t2_2;
                temporal_f0 = porciento_finalizacion_circuito_por_puesto[i];
                porciento_finalizacion_circuito_por_puesto[i] = porciento_finalizacion_circuito_por_puesto[comparar_indice];
                porciento_finalizacion_circuito_por_puesto[comparar_indice] = temporal_f0;
            }
        }
    }

    for (i = 0; i < JUGADORES_NUM; i++) {
        anterior_gp_actual_carrera_puesto_por_id_jugador[i] = gp_actual_carrera_puesto_por_id_jugador[i];
    }

    for (i = 0; i < num_racers; i++) {
        gp_actual_carrera_puesto_por_id_jugador[ids_jugador[i]] = i;
        gp_actual_carrera_jugador_id_por_puesto[i] = ids_jugador[i];
    }
}

void fijar_circuito_fin_puestos_con_tiempo(void) {
    f32 temporal_a0;
    s32 temporal_;
    s32 sp68[8];
    SIN_USO s32 relleno;
    s32 temporal_t1;
    s32 i;
    s32 j;
    s32 es_brough_a_you_por_el_numero_este_bound_superior_loops = 8;

    for (i = 0; i < es_brough_a_you_por_el_numero_este_bound_superior_loops;) {
        porciento_finalizacion_circuito_por_puesto[i++] = 0.0f;
    }

    for (j = 0, i = 0; i < es_brough_a_you_por_el_numero_este_bound_superior_loops; i++) {
        if (jugadores[i].type & MODO_CINEMATICA_JUGADOR) {
            sp68[j] = i;
            porciento_finalizacion_circuito_por_puesto[j] = -tiempo_jugador_ultimo_tocado_linea_meta[i];
            j++;
        }
    }

    temporal_t1 = j;
    for (i = 0; i < es_brough_a_you_por_el_numero_este_bound_superior_loops; i++) {
        if (!(jugadores[i].type & MODO_CINEMATICA_JUGADOR)) {
            sp68[j] = i;
            porciento_finalizacion_circuito_por_puesto[j] = porciento_finalizacion_circuito_por_id_jugador[i];
            j++;
        }
    }

    for (i = 0; i < (temporal_t1 - 1); i++) {
        for (j = i + 1; j < temporal_t1; j++) {
            if (porciento_finalizacion_circuito_por_puesto[i] < porciento_finalizacion_circuito_por_puesto[j]) {
                temporal_ = sp68[i];
                sp68[i] = sp68[j];
                sp68[j] = temporal_;
                temporal_a0 = porciento_finalizacion_circuito_por_puesto[i];
                porciento_finalizacion_circuito_por_puesto[i] = porciento_finalizacion_circuito_por_puesto[j];
                porciento_finalizacion_circuito_por_puesto[j] = temporal_a0;
            }
        }
    }

    for (i = temporal_t1; i < (es_brough_a_you_por_el_numero_este_bound_superior_loops - 1); i++) {
        for (j = i + 1; j < es_brough_a_you_por_el_numero_este_bound_superior_loops; j++) {
            if (porciento_finalizacion_circuito_por_puesto[i] < porciento_finalizacion_circuito_por_puesto[j]) {
                temporal_ = sp68[i];
                sp68[i] = sp68[j];
                sp68[j] = temporal_;
                temporal_a0 = porciento_finalizacion_circuito_por_puesto[i];
                porciento_finalizacion_circuito_por_puesto[i] = porciento_finalizacion_circuito_por_puesto[j];
                porciento_finalizacion_circuito_por_puesto[j] = temporal_a0;
            }
        }
    }

    for (i = 0; i < JUGADORES_NUM; i++) {
        anterior_gp_actual_carrera_puesto_por_id_jugador[i] = gp_actual_carrera_puesto_por_id_jugador[i];
    }

    for (i = 0; i < es_brough_a_you_por_el_numero_este_bound_superior_loops; i++) {
        gp_actual_carrera_puesto_por_id_jugador[sp68[i]] = i;
        gp_actual_carrera_jugador_id_por_puesto[i] = sp68[i];
    }
}

s32 es_punto_camino_en_rango(u16 punto_camino, u16 punto_camino_actual, u16 rango_backward, u16 rango_adelante,
                           u16 puntos_camino_total) {
    s32 variable_v1;

    variable_v1 = 0;
    if ((punto_camino_actual >= rango_backward) && (punto_camino_actual < (puntos_camino_total - rango_adelante))) {
        if ((punto_camino >= (punto_camino_actual - rango_backward)) && ((punto_camino_actual + rango_adelante) >= punto_camino)) {
            variable_v1 = 1;
        }
    } else if ((((punto_camino_actual + rango_adelante) % puntos_camino_total) < punto_camino) &&
               ((((punto_camino_actual + puntos_camino_total) - rango_backward) % puntos_camino_total) >= punto_camino)) {
        variable_v1 = -1;
    } else {
        variable_v1 = 2;
    }
    return variable_v1;
}

#include "control_velocidad_cpu.inc.c"

bool funcion_800088D8(s32 id_jugador, s16 parametro1, s16 parametro2) {
    Jugador* jugador;
    s16* temporal_a3;
    s32 progreso;
    f32 temporal_f0;
    s16 variable_t1;
    u16* variable_a0_3;
    s16 temporal_;
    s16 temporal2;
    s32 i;
    s32 variable_a0;
    s16 variable_v0;
    s16 variable_a0_4;
    s32* variable_v1;
    s16 STEMP_V1;
    s16 STEMP_V0;
    s16 puesto;

    dato_80163128[id_jugador] = -1;
    dato_80163150[id_jugador] = -1;
    if (seleccion_modo == CONTRARRELOJ) {
        return 1;
    }
    if (parametro1 < 0) {
        return 1;
    }
    if (parametro1 >= 4) {
        parametro1 = 3;
    }
    if (dato_80163330[id_jugador] == 1) {
        return 1;
    }
    jugador = &jugadores[id_jugador];
    if (jugador->type & HUMANO_JUGADOR) {
        return 1;
    }

    temporal_a3 = &CIRCUITO_OBTENER_800DCBB4(parametro1 * 8);
    if (parametro2 == 0) {
        if (modo_demo == 1) {
            STEMP_V0 = num_camino_puntos_recorrido[id_jugador];
            STEMP_V1 = num_camino_puntos_recorrido[id_jugador_ant_por_puesto[7]];
            progreso = STEMP_V0 - STEMP_V1;
            if (progreso < 0) {
                progreso = -progreso;
            }
            if (parametro1 < 3) {
                STEMP_V0 = temporal_a3[0];
                STEMP_V1 = temporal_a3[8];
                temporal_f0 = porciento_finalizacion_vuelta_por_id_jugador[id_jugador];
                variable_a0 = (STEMP_V1 * temporal_f0) + (STEMP_V0 * (1.0f - temporal_f0));
            } else {
                variable_a0 = temporal_a3[0];
            }
            dato_80163150[id_jugador] = variable_a0;
            if ((dato_80163150[id_jugador] < progreso) && (((jugador->speed / 18.0f) * 216.0f) >= 20.0f)) {
                return 0;
            }
            return 1;
        }

        STEMP_V0 = num_camino_puntos_recorrido[id_jugador];
        STEMP_V1 = num_camino_puntos_recorrido[mejor_clasificado_humano_jugador];
        progreso = STEMP_V0 - STEMP_V1;
        puesto = gp_actual_carrera_puesto_por_id_jugador[mejor_clasificado_humano_jugador];
        if (((((cantidad_camino_por_indice_camino[0] * 2) / 3)) < progreso) && ((puesto) >= 6)) {
            STEMP_V0 = num_camino_puntos_recorrido[id_jugador];
            STEMP_V1 = temporal_ = num_camino_puntos_recorrido[id_jugador_ant_por_puesto[puesto - 1]];
            progreso = STEMP_V0 - STEMP_V1;
        }
        if (progreso < 0) {
            progreso = -progreso;
        }
        if (parametro1 < 3) {
            STEMP_V0 = temporal_a3[0];
            STEMP_V1 = temporal_a3[8];
            temporal_f0 = porciento_finalizacion_vuelta_por_id_jugador[id_jugador];
            variable_a0 = (STEMP_V1 * temporal_f0) + (STEMP_V0 * (1.0f - temporal_f0));
        } else {
            variable_a0 = temporal_a3[0];
        }
        dato_80163150[id_jugador] = variable_a0 = (seleccion_cc + 1) * variable_a0;
        if ((variable_a0 < progreso) && (((jugador->speed / 18.0f) * 216.0f) >= 20.0f)) {
            return 0;
        }
        return 1;
    }

    temporal2 = dato_80163344[0];
    STEMP_V0 = num_camino_puntos_recorrido[id_jugador];
    STEMP_V1 = num_camino_puntos_recorrido[temporal2];
    progreso = STEMP_V1 - STEMP_V0;
    if (progreso < 0) {
        progreso = -progreso;
    }

    variable_v0 = 0;
    for (i = 0; i < 2; i++) {
        if (gp_actual_carrera_puesto_por_id_jugador[dato_80163344[i] & 0xFFFF] < parametro2) {
            variable_v0++;
        }
    }

    variable_a0_4 = 0;
    for (i = 0; i < cantidad_jugador; i++) {
        if (gp_actual_carrera_puesto_por_id_jugador[i] < parametro2) {
            variable_a0_4++;
        }
    }

    variable_t1 = (parametro2 - (variable_v0 & 0xFFFF)) - variable_a0_4;
    parametro2 -= variable_v0;

    if ((variable_v0 > 0) || (variable_a0_4 > 0)) {
        variable_t1++;
    }
    dato_80164538[id_jugador] = variable_t1;
    if ((variable_t1 < 0) || (variable_t1 >= 8)) {
        return 0;
    }
    if (parametro1 < 3) {
        STEMP_V0 = temporal_a3[variable_t1 + 0];
        STEMP_V1 = temporal_a3[variable_t1 + 8];
        temporal_f0 = porciento_finalizacion_vuelta_por_id_jugador[id_jugador];
        variable_a0 = (STEMP_V1 * temporal_f0) + (STEMP_V0 * (1.0f - temporal_f0));
    } else {
        variable_a0 = temporal_a3[variable_t1];
    }
    dato_80163128[id_jugador] = progreso;
    dato_80163150[id_jugador] = variable_a0;
    if (variable_a0 < progreso) {
        return 1;
    }
    return 0;
}

void fijar_camino_actual(s32 indice_camino) {
    camino_pista_actual = caminos_pista[indice_camino];
    actual_pista_izquierda_camino = caminos_izquierda_pista[indice_camino];
    actual_pista_derecha_camino = caminos_derecha_pista[indice_camino];
    actual_pista_seccion_tipos_camino = tipos_seccion_pista[indice_camino];
    actual_camino_punto_esperado_rotacion_camino = rotacion_esperado_camino[indice_camino];
    actual_pista_consecutivo_curva_cantidades_camino = pista_consecutivo_curva_cantidades[indice_camino];
    cantidad_camino_seleccionado = cantidad_camino_por_indice_camino[indice_camino];
}
