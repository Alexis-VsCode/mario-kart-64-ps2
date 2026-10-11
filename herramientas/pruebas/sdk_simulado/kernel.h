// kernel.h simulado: lo que memory_card.c usa del kernel del EE (sdk_simulado.c)
#ifndef SIM_KERNEL_H
#define SIM_KERNEL_H

#include <stdint.h>

typedef struct {
    int count;
    int max_count;
    int init_count;
    int wait_threads;
    uint32_t attr;
    uint32_t option;
} ee_sema_t;

typedef struct {
    int status;
    void *func;
    void *stack;
    int stack_size;
    void *gp_reg;
    int initial_priority;
    int current_priority;
    uint32_t attr;
    uint32_t option;
} ee_thread_t;

int DI(void);
int EI(void);
int32_t CreateSema(ee_sema_t *sema);
int32_t SignalSema(int32_t id);
int32_t iSignalSema(int32_t id);
int32_t WaitSema(int32_t id);
int32_t PollSema(int32_t id);
int32_t CreateThread(ee_thread_t *th);
int32_t StartThread(int32_t id, void *args);
int32_t ChangeThreadPriority(int32_t id, int32_t prio);
int32_t GetThreadId(void);
int32_t SetAlarm(uint16_t time, void (*handler)(int32_t, uint16_t, void *), void *arg);
void ExitHandler(void);

#endif
