#include "os/libultra_internal.h"
#include <PR/gu.h>

void guMtxXFMF(Mtx*, float, float, float, float*, float*, float*);
void guMtxCatF(float mf[4][4], float nf[4][4], float res[4][4]);

void guMtxCatL(Mtx* m, Mtx* n, Mtx* res) {
    float mf[4][4], nf[4][4], resf[4][4];

    guMtxL2F(mf, m);
    guMtxL2F(nf, n);

    guMtxCatF(mf, nf, resf);

    guMtxF2L(resf, res);
}

void guMtxXFML(Mtx* m, float x, float y, float z, float* ox, float* oy, float* oz) {
    float mf[4][4];

    guMtxL2F(mf, m);

    guMtxXFMF((Mtx*) mf, x, y, z, ox, oy, oz);
}
