#include <ultra64.h>
#include <juego/macros.h>
#include <juego/mk64.h>
#include "sistema/matematicas.h"
#include "carrera/animacion.h"
#include "memoria/memoria_carrera.h"
#include <sistema/bucle_principal.h>
#include <PR/gbi.h>
#include "carrera/objetos_y_efectos.h"

Vec3s animacion_pos_original;
s16 es_no_el_primer;
s16 debe_matriz_no_sacar;
s16 tamanio_pila_matriz;

void convertir_a_fijo_punto_matriz_animacion(Mtx* dest, Mat4 orig_) {
#ifdef AVOID_UB
    guMtxF2L(orig_, dest);
#else
    s32 como_punto_fijo;
    register s32 i;
    register s16* a3 = (s16*) dest;
    register s16* t0 = (s16*) dest + 16;
    register f32* t1 = (f32*) orig_;

    for (i = 0; i < 16; i++) {
        como_punto_fijo = *t1++ * (1 << 16);
        *a3++ = ALTO_S16_OBTENER_DE_32(como_punto_fijo); // integer part
        *t0++ = BAJO_S16_OBTENER_DE_32(como_punto_fijo);
    }
#endif
}

void trasladar_rotacion2_mtxf(Mat4 dest, Vec3f pos, Vec3s angulo) {
    register f32 sx = senos(angulo[0]);
    register f32 cx = coss(angulo[0]);

    register f32 sy = senos(angulo[1]);
    register f32 cy = coss(angulo[1]);

    register f32 sz = senos(angulo[2]);
    register f32 cz = coss(angulo[2]);

    dest[0][0] = cy * cz;
    dest[0][1] = cy * sz;
    dest[0][2] = -sy;
    dest[0][3] = 0.0f;

    dest[1][0] = sx * sy * cz - cx * sz;
    dest[1][1] = sx * sy * sz + cx * cz;
    dest[1][2] = sx * cy;
    dest[1][3] = 0.0f;

    dest[2][0] = cx * sy * cz + sx * sz;
    dest[2][1] = cx * sy * sz - sx * cz;
    dest[2][2] = cx * cy;
    dest[2][3] = 0.0f;

    dest[3][0] = pos[0];
    dest[3][1] = pos[1];
    dest[3][2] = pos[2];
    dest[3][3] = 1.0f;
}

void agregar_mtx_miembro_render_o(Armadura* parametro0, s16* parametro1, VectorMiembroAnimacion parametro2, s32 ciclo_tiempo) {
    Vec3f pos;
    Vec3s angulo;
    Mat4 matriz_modelo;
    s32 i;
    s32 algun_desplazamiento;
    Gfx* modelo;
    Gfx* modelo_virtual;
    modelo_virtual = parametro0->model;
    if (es_no_el_primer == 0) {
        for (i = 0; i < 3; i++) {
            pos[i] = animacion_pos_original[i] + parametro0->pos[i];
        }
        es_no_el_primer += 1;
    } else {
        for (i = 0; i < 3; i++) {
            pos[i] = parametro0->pos[i];
        }
    }
    for (i = 0; i < 3; i++) {
        if (ciclo_tiempo < parametro2[i].longitud_animacion) {
            algun_desplazamiento = ciclo_tiempo;
        } else {
            algun_desplazamiento = 0;
        }
        angulo[i] = parametro1[parametro2[i].ciclo_indice + algun_desplazamiento];
    }

    trasladar_rotacion2_mtxf(matriz_modelo, pos, angulo);
    convertir_a_fijo_punto_matriz_animacion(&gfx_pool->mtx_hud[cantidad_hud_matriz], matriz_modelo);
    tamanio_pila_matriz += 1;
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_PHYSICAL2(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
              G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    if (modelo_virtual != NULL) {
        modelo = segmentado_a_virtual(modelo_virtual);
        gSPDisplayList(display_list_cabeza++, modelo);
    }
}

void renderizar_armadura(Armadura* animacion, Animacion* parametro1, s16 ciclo_tiempo) {
    SIN_USO u32* temporal_;
    s16* arreglo_angulo;
    s32 algun_desplazamiento;
    VectorMiembroAnimacion* lista_ciclo_animacion;
    s32 tipo_animacion;
    s32 algun_indice;

    arreglo_angulo = segmentado_a_virtual(parametro1->arreglo_angulo);
    lista_ciclo_animacion = segmentado_a_virtual(parametro1->animacion_ciclo_espec_vector);
    tamanio_pila_matriz = 0;
    es_no_el_primer = 0;
    for (algun_indice = 0; algun_indice < 3; algun_indice++) {
        if (ciclo_tiempo < (*lista_ciclo_animacion)[algun_indice].longitud_animacion) {
            algun_desplazamiento = ciclo_tiempo;
        } else {
            algun_desplazamiento = 0;
        }
        animacion_pos_original[algun_indice] = arreglo_angulo[(*lista_ciclo_animacion)[algun_indice].ciclo_indice + algun_desplazamiento];
    }
    lista_ciclo_animacion++;
    debe_matriz_no_sacar = 0;
    do {
        tipo_animacion = animacion->type;
        switch (tipo_animacion) { /* irregular */
            case ANIMACION_PARADA:
                break;
            case DESACTIVAR_AUTOMATICO_SACAR_MATRIZ:
                debe_matriz_no_sacar = 1;
                break;
            case MATRIZ_SACAR:
                gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);
                tamanio_pila_matriz -= 1;
                break;
            case MODELO_RENDER_O_POS_AGREGAR:
                if (debe_matriz_no_sacar == 0) {
                    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);
                    tamanio_pila_matriz -= 1;
                }
                agregar_mtx_miembro_render_o(animacion, arreglo_angulo, *lista_ciclo_animacion, (s32) ciclo_tiempo);
                debe_matriz_no_sacar = 0;
                lista_ciclo_animacion++;
                break;
        }
        animacion = (Armadura*) ((u32*) animacion + animacion->size);
    } while (tipo_animacion != ANIMACION_PARADA);
}

s16 renderizar_modelo_animado(Armadura* armadura_virtual, Animacion** animacion_lista_virtual, s16 indice_animacion,
                          s16 ciclo_tiempo) {
    Armadura* armadura;
    Animacion* animacion;
    Animacion** animacion_lista;

    armadura = segmentado_a_virtual(armadura_virtual);
    animacion_lista = segmentado_a_virtual(animacion_lista_virtual);
    animacion = segmentado_a_virtual(animacion_lista[indice_animacion]);
    if (ciclo_tiempo >= animacion->longitud_animacion) {
        ciclo_tiempo = 0;
    }
    renderizar_armadura(armadura, animacion, ciclo_tiempo);
    ciclo_tiempo++;
    if (ciclo_tiempo >= animacion->longitud_animacion) {
        ciclo_tiempo = 0;
    }
    return ciclo_tiempo;
}

s16 obtener_longitud_animacion(Animacion** direccion, s16 desplazamiento) {
    Animacion** item = segmentado_a_virtual(direccion);
    Animacion* temporal_ = (Animacion*) segmentado_a_virtual((void*) item[desplazamiento]);

    return temporal_->longitud_animacion - 1;
}
