#ifndef _ULTRA64_PI_H_
#define _ULTRA64_PI_H_

typedef struct {
    void* dramAddr;
    void* C2Addr;
    u32 sectorSize;
    u32 C1ErrNum;
    u32 C1ErrSector[4];
} __OSBlockInfo;

typedef struct {
    u32 cmdType;
    u16 transferMode;
    u16 blockNum;
    s32 sectorNum;
    uintptr_t devAddr;
    u32 errStatus;
    u32 bmCtlShadow;
    u32 seqCtlShadow;
    __OSBlockInfo block[2];
} __OSTranxInfo;

typedef struct OSPiHandle_s {
    struct OSPiHandle_s* next;
    u8 type;
    u8 latency;
    u8 pageSize;
    u8 relDuration;
    u8 pulse;
    u8 domain;
    u32 baseAddress;
    u32 speed;
    __OSTranxInfo transferInfo;
} OSPiHandle;

typedef struct {
    u8 type;
    uintptr_t address;
} OSPiInfo;

typedef struct {
    u16 type;
    u8 pri;
    u8 status;
    OSMesgQueue* retQueue;
} OSIoMesgHdr;

typedef struct {
     OSIoMesgHdr hdr;
     void* dramAddr;
     uintptr_t devAddr;
     size_t size;
    OSPiHandle* piHandle;
} OSIoMesg;

#define OS_READ 0
#define OS_WRITE 1

#define OS_MESG_PRI_NORMAL 0
#define OS_MESG_PRI_HIGH 1

s32 osPiStartDma(OSIoMesg* mb, s32 priority, s32 direction, uintptr_t devAddr, void* vAddr, size_t nbytes,
                 OSMesgQueue* mq);
void osCreatePiManager(OSPri pri, OSMesgQueue* cmdQ, OSMesg* cmdBuf, s32 cmdMsgCnt);
OSMesgQueue* osPiGetCmdQueue(void);
s32 osPiWriteIo(uintptr_t devAddr, u32 data);
s32 osPiReadIo(uintptr_t devAddr, u32* data);

s32 osPiRawStartDma(s32 dir, u32 cart_addr, void* dram_addr, size_t size);
s32 osEPiRawStartDma(OSPiHandle* piHandle, s32 dir, u32 cart_addr, void* dram_addr, size_t size);
#endif
