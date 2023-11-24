#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "types.h"
#include "common_structs.h"
#include "dolphin/gx/GXStruct.h"

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
void fn_80032A58(int arg0);
void fn_80035A0C(void);

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

void HuPrcInit(void);
Process *HuPrcCreate(void (*func)(void), u16 prio, u32 stack_size, s32 extra_size);
void HuPrcChildLink(Process *parent, Process *child);
void HuPrcChildUnlink(Process *process);
Process *HuPrcChildCreate(void (*func)(void), u16 prio, u32 stack_size, s32 extra_size, Process *parent);
void HuPrcChildWatch();
Process *HuPrcCurrentGet();
int HuPrcKill(Process *process);
void HuPrcChildKill(Process *process);
void HuPrcSleep(s32 time);
void HuPrcVSleep(void);
void HuPrcWakeup(Process *process);
void HuPrcDestructorSet2(Process *process, void (*func)(void));
void HuPrcDestructorSet(void (*func)(void));
void HuPrcCall(int tick);
void *HuPrcMemAlloc(s32 size);
void HuPrcMemFree(void *ptr);
void HuPrcSetStat(Process *process, u16 value);
void HuPrcResetStat(Process *process, u16 value);
void HuPrcAllPause(int flag);
void HuPrcAllUPause(int flag);

void omOvlGotoEx(int id, s16 end_mode, int stat, int event);
void omOvlReturnEx(int level, s16 end_mode);
void WipeCreate(char dir, char type, short duration);

void pfInit(void);
void pfClsScr(void);
s16 print8(s16 x, s16 y, float scale, char *str, ...);
s16 printWin(s16 x, s16 y, s16 w, s16 h, GXColor *color);
void pfDrawFonts(void);

#endif
