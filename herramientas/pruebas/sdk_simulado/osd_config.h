// osd_config.h simulado: el tipo de tele de la configuración de la BIOS (sdk_simulado.c)
#ifndef SIM_OSD_CONFIG_H
#define SIM_OSD_CONFIG_H

enum TV_SCREEN_TYPES {
    TV_SCREEN_43 = 0,
    TV_SCREEN_FULL,
    TV_SCREEN_169
};

int configGetTvScreenType(void);

#endif
