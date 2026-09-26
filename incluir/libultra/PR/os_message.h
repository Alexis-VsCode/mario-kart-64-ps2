#ifndef _OS_MESSAGE_H_
#define _OS_MESSAGE_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/ultratypes.h>
#include <PR/os_thread.h>

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

typedef u32 OSEvent;

typedef void* OSMesg;

typedef struct OSMesgQueue_s {
    OSThread* mtqueue;
    OSThread* fullqueue;
    s32 validCount;
    s32 first;
    s32 msgCount;
    OSMesg* msg;
} OSMesgQueue;

#endif

#ifdef _FINALROM
#define OS_NUM_EVENTS 15
#else
#define OS_NUM_EVENTS 23
#endif

#define OS_EVENT_SW1 0
#define OS_EVENT_SW2 1
#define OS_EVENT_CART 2
#define OS_EVENT_COUNTER 3
#define OS_EVENT_SP 4
#define OS_EVENT_SI 5            /* SI (controller) interrupt */
#define OS_EVENT_AI 6
#define OS_EVENT_VI 7
#define OS_EVENT_PI 8
#define OS_EVENT_DP 9
#define OS_EVENT_CPU_BREAK 10
#define OS_EVENT_SP_BREAK 11
#define OS_EVENT_FAULT 12
#define OS_EVENT_THREADSTATUS 13
#define OS_EVENT_PRENMI 14
#ifndef _FINALROM
#define OS_EVENT_RDB_READ_DONE 15
#define OS_EVENT_RDB_LOG_DONE 16
#define OS_EVENT_RDB_DATA_DONE 17
#define OS_EVENT_RDB_REQ_RAMROM 18
#define OS_EVENT_RDB_FREE_RAMROM 19
#define OS_EVENT_RDB_DBG_DONE 20
#define OS_EVENT_RDB_FLUSH_PROF 21
#define OS_EVENT_RDB_ACK_PROF 22
#endif

#define OS_MESG_NOBLOCK 0
#define OS_MESG_BLOCK 1

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

#define MQ_GET_COUNT(mq) ((mq)->validCount)

#define MQ_IS_EMPTY(mq) (MQ_GET_COUNT(mq) == 0)
#define MQ_IS_FULL(mq) (MQ_GET_COUNT(mq) >= (mq)->msgCount)

extern void osCreateMesgQueue(OSMesgQueue*, OSMesg*, s32);
extern s32 osSendMesg(OSMesgQueue*, OSMesg, s32);
extern s32 osJamMesg(OSMesgQueue*, OSMesg, s32);
extern s32 osRecvMesg(OSMesgQueue*, OSMesg*, s32);

extern void osSetEventMesg(OSEvent, OSMesgQueue*, OSMesg);

#endif

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif
