#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "types.h"
#include "common_structs.h"

void OSReport(const char * format, ...);
void* OSAllocFromHeap(int heap, u32 size);
s32 OSCheckHeap(int heap);
void DCFlushRangeNoSync(void *addr, u32 size);
void* HuPrcCreate(void (*), s32, s32, s32);
void Hu3DBGColorSet(u8, u8, u8);
void Hu3DCameraCreate(s16);
void Hu3DCameraPerspectiveSet(s16, f32, f32, f32, f32);
void Hu3DCameraViewportSet(s16, f32, f32, f32, f32, f32, f32);
void omOvlHisChg(s32, s32, s32, s32);
UnkOvl* omOvlHisGet(s32);
void* omInitObjMan(s32, s32);
void fn_80044920(s16);
void fn_80045F74(s16, s32);
s32 fn_800578E4(void);
void fn_1_26C(void);


void HuMemInitAll(void);
void *HuMemInit(void *ptr, u32 size);
void HuMemDCFlush(int heap);

void *HuMemHeapInit(void *ptr, u32 size);
void *HuMemMemoryAlloc(void *heap_ptr, u32 size, void *retaddr);
void *HuMemMemoryAllocNum(void *heap_ptr, u32 size, u32 num, void *retaddr);
void HuMemMemoryFree(void *ptr, void *retaddr);
void HuMemMemoryFreeNum(void *heap_ptr, u32 num, void *retaddr);
u32 HuMemUsedMemorySizeGet(void *heap_ptr);
u32 HuMemUsedMemoryBlockGet(void *heap_ptr);


#endif