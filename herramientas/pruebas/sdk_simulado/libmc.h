// libmc.h simulado: las órdenes de la Memory Card que usa memory_card.c, con
// los valores del SDK (sdk_simulado.c)
#ifndef SIM_LIBMC_H
#define SIM_LIBMC_H

#define sceMcTypePS2 2
#define sceMcFileAttrReadable 0x0001
#define sceMcFileAttrWriteable 0x0002
#define sceMcFileCreateFile 0x0200
#define MC_WAIT 0
#define MC_NOWAIT 1
#define MC_TYPE_MC 0
#define MC_TYPE_XMC 1

enum MCICON_TYPES {
    MCICON_TYPE_SAVED_DATA = 0
};

typedef int iconIVECTOR[4];
typedef float iconFVECTOR[4];

typedef struct {
    unsigned char head[4];
    unsigned short type;
    unsigned short nlOffset;
    unsigned unknown2;
    unsigned trans;
    iconIVECTOR bgCol[4];
    iconFVECTOR lightDir[3];
    iconFVECTOR lightCol[3];
    iconFVECTOR lightAmbient;
    unsigned short title[34];
    unsigned char view[64];
    unsigned char copy[64];
    unsigned char del[64];
    unsigned char unknown3[512];
} mcIcon;

int mcInit(int type);
int mcGetInfo(int port, int slot, int *type, int *free, int *format);
int mcOpen(int port, int slot, const char *name, int mode);
int mcClose(int fd);
int mcRead(int fd, void *buffer, int size);
int mcWrite(int fd, const void *buffer, int size);
int mcMkDir(int port, int slot, const char *name);
int mcDelete(int port, int slot, const char *name);
int mcSync(int mode, int *cmd, int *result);

#endif
