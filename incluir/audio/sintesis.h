#ifndef AUDIO_SINTESIS_H
#define AUDIO_SINTESIS_H

#include "audio/interno.h"
#include <PR/abi.h>

#define LARGO_PREDETERMINADO_1CH 0x180
#define LARGO_PREDETERMINADO_2CH 0x300

#define TEMPORAL_DIRECCION_DMEM 0x0
#define DMEM_DIRECCION_REMUESTREADO 0x20
#define RESAMPLED2_DIRECCION_DMEM 0x1A0
#define DMEM_DIRECCION_SIN_COMPRIMIR_NOTA 0x180
#define DMEM_DIRECCION_NOTA_PANEO_TEMPORAL 0x200
#define DMEM_DIRECCION_ESTEREO_FUERTE_TEMPORAL_SECO 0x200
#define DMEM_DIRECCION_ESTEREO_FUERTE_TEMPORAL_HUMEDO 0x340
#define DMEM_DIRECCION_COMPRIMIDO_ADPCM_DATOS 0x3f0
#define DMEM_DIRECCION_IZQUIERDA_CH 0x540
#define DMEM_DIRECCION_DERECHA_CH 0x6C0
#define DMEM_DIRECCION_HUMEDO_IZQUIERDA_CH 0x840
#define DMEM_DIRECCION_HUMEDO_DERECHA_CH 0x9C0

#define ACTUALIZACIONES_MAX_POR_FRAME 5

struct ReverbAnilloBufferItem {
     s16 muestras_num_despues_submuestreo;
     s16 largo_trozo; // never read
     s16* a_izquierda_submuestreo;
     s16* a_derecha_submuestreo;
     s32 pos_inicio;
     s16 longitud_a;
     s16 longitud_b;
};

struct ReverbSintesis {
     u8 banderas_remuestreo;
     u8 reverb_usar;
     u8 izquierda_frames_a_ignorar;
     u8 frame_act;
     u8 tasa_submuestreo;
     u16 tamanio_ventana;
     u16 ganancia_reverb;
     u16 tasa_remuestreo;
     s32 siguiente_anillo_buffer_pos;
     s32 desconocido_c; // never read
     s32 tamanio_buf_por_canal;
    struct {
         s16* izquierda;
         s16* derecha;
    } buffer_anillo;
     s16* izquierda_estado_remuestreo;
     s16* derecha_estado_remuestreo;
     s16* unk24; // never read
     s16* unk28; // never read
     struct ReverbAnilloBufferItem items[2][ACTUALIZACIONES_MAX_POR_FRAME];
     s16* desconocido_f8;
     s16* f_c_desconocido;
     s16* desconocido100;
     s16* desconocido104;
};

#define ALIGN(val, cant) (((val) + (1 << cant) - 1) & ~((1 << cant) - 1))

void preparar_buffer_anillo_reverb(s32 largo_trozo, u32 actualizar_indice, s32 indice_reverb);
Acmd* cargar_buffer_anillo_reverb_sintesis(Acmd*, u16, u16, s32, s32);
Acmd* guardar_buffer_anillo_reverb_sintesis(Acmd*, u16, u16, s32, s32);
void funcion_800B6FB4(s32 actualizar_inicio_indice, s32 indice_nota);
void cargar_eu_subs_nota_sintesis(s32 actualizar_indice);
Acmd* ejecutar_sintesis(Acmd*, s32*, s16*, s32);
Acmd* remuestreo_sintesis_y_reverb_mezcla(Acmd*, s32, s16, s16);
Acmd* guardar_muestras_reverb_sintesis(Acmd*, s16, s16);
Acmd* actualizar_audio_hacer_uno_sintesis(s16*, s32, Acmd*, s32);
Acmd* procesar_nota_sintesis(s32 indice_nota, struct EuSubNota* eu_sub_nota, struct EstadoSintesisNota* estado_sintesis,
                             s16* ai_buf, s32 en_buf, Acmd* cmd, s32 actualizar_indice);
Acmd* cargar_muestras_ola(Acmd* acmd, struct EuSubNota* eu_sub_nota, struct EstadoSintesisNota* estado_sintesis,
                        s32 muestras_na_carga);
Acmd* remuestreo_final(Acmd* acmd, struct EstadoSintesisNota* estado_sintesis, s32 cantidad, u16 tono, u16 dmem_en,
                     u32 banderas);
Acmd* funcion_800B86A0(Acmd* cmd, struct EuSubNota* nota, struct EstadoSintesisNota* estado_sintesis, s32 muestras_n,
                    u16 en_buf, s32 ajustes_paneo_auriculares, u32 banderas);
Acmd* aplicar_efectos_paneo_auriculares_nota(Acmd* acmd, struct EuSubNota* eu_sub_nota, struct EstadoSintesisNota* nota,
                                     s32 largo_buf, s32 banderas, s32 derecha_izquierda);

extern struct ReverbSintesis reverbs_sintesis[4];

#endif
