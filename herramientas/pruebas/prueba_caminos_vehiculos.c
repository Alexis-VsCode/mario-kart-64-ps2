#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef short s16;
typedef int s32;
typedef float f32;

typedef struct {
    s16 pos_x, pos_y, pos_z;
    unsigned short id_seccion_pista;
} PuntoCaminoPista;

typedef struct {
    s16 x;
    s16 z;
} Camino2D;

/* Por camino */
static const s16 tabla[] = {
#include TABLA
};

static s16 es_modo_espejo;

/* Copia literal del original (sin el camino rapido de la PS2). */
static s32 generar_2d_camino(Camino2D *dest_camino, PuntoCaminoPista *orig_camino, s32 puntos_camino_num)
{
    f32 temporal_f14_3;
    f32 temporal_f16_2;
    f32 x1, z1, x2, z2, x3, z3;
    f32 temporal_f24;
    f32 sp_a8;
    f32 temporal_f26;
    f32 sp_a0;
    f32 temporal_f2_3;
    PuntoCaminoPista *punto1;
    f32 j;
    PuntoCaminoPista *punto2;
    PuntoCaminoPista *punto3;
    s32 i;
    f32 temporal_f6 = 0.0f;
    s32 elemento_nb;
    f32 sp7_c;

    sp_a8 = orig_camino[0].pos_x;
    sp_a0 = orig_camino[0].pos_z;
    elemento_nb = 0;

    for (i = 0; i < puntos_camino_num; i++) {
        punto1 = &orig_camino[((i % puntos_camino_num))];
        punto2 = &orig_camino[(((i + 1) % puntos_camino_num))];
        punto3 = &orig_camino[(((i + 2) % puntos_camino_num))];
        x1 = punto1->pos_x;
        z1 = punto1->pos_z;
        x2 = punto2->pos_x;
        z2 = punto2->pos_z;
        x3 = punto3->pos_x;
        z3 = punto3->pos_z;

        sp7_c = 0.05 / (sqrtf(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1))) +
                       sqrtf(((x3 - x2) * (x3 - x2)) + ((z3 - z2) * (z3 - z2))));

        for (j = 0.0f; j <= 1.0; j += sp7_c) {
            temporal_f2_3 = (1.0 - j) * 0.5 * (1.0 - j);
            temporal_f14_3 = ((1.0 - j) * j) + 0.5;
            temporal_f16_2 = j * 0.5 * j;

            temporal_f24 = (temporal_f2_3 * x1) + (temporal_f14_3 * x2) + (temporal_f16_2 * x3);
            temporal_f26 = (temporal_f2_3 * z1) + (temporal_f14_3 * z2) + (temporal_f16_2 * z3);
            temporal_f6 += sqrtf(((temporal_f24 - sp_a8) * (temporal_f24 - sp_a8)) + ((temporal_f26 - sp_a0) * (temporal_f26 - sp_a0)));
            sp_a8 = temporal_f24;
            sp_a0 = temporal_f26;
            if ((temporal_f6 > 20.0f) || ((i == 0) && (j == 0.0))) {
                if (es_modo_espejo) {
                    dest_camino->x = (s16) -sp_a8;
                } else {
                    dest_camino->x = (s16) sp_a8;
                }
                dest_camino->z = sp_a0;
                elemento_nb += 1;
                dest_camino++;
                temporal_f6 = 0.0f;
            }
        }
    }
    return elemento_nb;
}

int main(void)
{
    static PuntoCaminoPista orig_[4096];
    static Camino2D salida[65536];
    const s16 *p = tabla;
    int malo = 0, t = 0;

    for (; p[0] != 0; t++) {
        s32 puntos_camino_num = p[0], cantidad = p[1], k, n;
        const s16 *orig = p + 2, *tabla = orig + 2 * puntos_camino_num;

        for (k = 0; k < puntos_camino_num; k++) {
            orig_[k].pos_x = orig[2 * k];
            orig_[k].pos_y = 0;
            orig_[k].pos_z = orig[2 * k + 1];
        }
        for (es_modo_espejo = 0; es_modo_espejo < 2; es_modo_espejo++) {
            int dif_ = 0;

            n = generar_2d_camino(salida, orig_, puntos_camino_num);
            if (n != cantidad) {
                printf("camino %d espejo %d: %d puntos, la tabla tiene %d\n", t, es_modo_espejo, n, cantidad);
                malo++;
                continue;
            }
            for (k = 0; k < n; k++) {
                s16 x = es_modo_espejo ? (s16) -tabla[2 * k] : tabla[2 * k];

                dif_ += salida[k].x != x || salida[k].z != tabla[2 * k + 1];
            }
            printf("camino %d espejo %d: %d puntos, %d distintos\n", t, es_modo_espejo, n, dif_);
            malo += dif_ != 0;
        }
        p = tabla + 2 * cantidad;
    }
    if (t == 0) {
        printf("tabla vacia\n");
        malo = 1;
    }
    return malo != 0;
}
