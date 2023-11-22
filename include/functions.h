#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "types.h"
#include "common_structs.h"

void OSReport(const char * format, ...);
void* OSAllocFromHeap(int heap, u32 size);
s32 OSCheckHeap(int heap);
void DCFlushRangeNoSync(void *addr, u32 size);
void DCFlushRange(void *addr, u32 size);
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

void HuDecodeData(void *src, void *dst, u32 size, int decode_type);

void HuMemInitAll(void);
void *HuMemInit(void *ptr, s32 size);
void HuMemDCFlushAll();
void HuMemDCFlush(int heap);
void *HuMemDirectMalloc(int heap, s32 size);
void *HuMemDirectMallocNum(int heap, s32 size, u32 num);
void HuMemDirectFree(void *ptr);
void HuMemDirectFreeNum(int heap, u32 num);
s32 HuMemUsedMallocSizeGet(int heap);
s32 HuMemUsedMallocBlockGet(int heap);
u32 HuMemHeapSizeGet(int heap);
void *HuMemHeapPtrGet(int heap);

void *HuMemHeapInit(void *ptr, s32 size);
void *HuMemMemoryAlloc(void *heap_ptr, s32 size, u32 retaddr);
void *HuMemMemoryAllocNum(void *heap_ptr, s32 size, u32 num, u32 retaddr);
void HuMemMemoryFree(void *ptr, u32 retaddr);
void HuMemMemoryFreeNum(void *heap_ptr, u32 num, u32 retaddr);
s32 HuMemUsedMemorySizeGet(void *heap_ptr);
s32 HuMemUsedMemoryBlockGet(void *heap_ptr);
s32 HuMemMemoryAllocSizeGet(s32 size);
void HuMemHeapDump(void *heap_ptr, s16 status);



#endif