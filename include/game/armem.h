#ifndef _GAME_ARMEM_H
#define _GAME_ARMEM_H

#include "common.h"
#include "game/memory.h"

void HuARInit(void);
void *HuARMalloc(u32 arg0);
void HuARFree(void *arg0);
void HuAMemDump(void);
void *HuAR_DVDtoARAM(u32 arg0);
void HuAR_MRAMtoARAM(s32 arg0);
void *HuAR_MRAMtoARAM2(void *arg0);
void HuAR_ARAMtoMRAM(void *dst);
void *HuAR_ARAMtoMRAMNum(void *dst, s32 num);
BOOL HuARDMACheck(void);
void *HuARDirCheck(u32 dir);
void HuARDirFree(u32 arg0);
void *HuAR_ARAMtoMRAMFileRead(u32 arg0, u32 arg1, HeapID arg2);

#endif
