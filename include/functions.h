#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "types.h"
#include "common_structs.h"
#include "common_enums.h"
#include "dolphin/mtx.h"
#include "dolphin/gx/GXStruct.h"

void Hu3D2Dto3D(Vec3f*, s32, Vec3f*);
void Hu3DModelLightInfoSet(s32, s32);
void Hu3DBGColorSet(u8, u8, u8);
void Hu3DCameraCreate(s16);
void Hu3DCameraPerspectiveSet(s16, f32, f32, f32, f32);
void Hu3DCameraViewportSet(s16, f32, f32, f32, f32, f32, f32);
void fn_80044920(s16);
void fn_80045F74(s16, s32);
s32 fn_800578E4(void);
void HuAudFadeOut(int arg0);
void fn_80035A0C(void);

void HuDecodeData(void *src, void *dst, u32 size, int decode_type);

void HuMemInitAll(void);
void *HuMemInit(void *ptr, s32 size);
void HuMemDCFlushAll();
void HuMemDCFlush(HeapID heap);
void *HuMemDirectMalloc(HeapID heap, s32 size);
void *HuMemDirectMallocNum(HeapID heap, s32 size, u32 num);
void HuMemDirectFree(void *ptr);
void HuMemDirectFreeNum(HeapID heap, u32 num);
s32 HuMemUsedMallocSizeGet(HeapID heap);
s32 HuMemUsedMallocBlockGet(HeapID heap);
u32 HuMemHeapSizeGet(HeapID heap);
void *HuMemHeapPtrGet(HeapID heap);

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
void HuPrcEnd(void);
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

void omMasterInit(int prio, FileListEntry *ovl_list, int ovl_count, OverlayID start_ovl);
void omOvlCallEx(OverlayID overlay, s16 arg2, int event, int stat);
void omOvlGotoEx(OverlayID overlay, s16 arg2, int event, int stat);
void omOvlReturnEx(s16 level, s16 arg2);
void omOvlKill(s16 arg);
void omOvlHisChg(s32 level, OverlayID overlay, int event, int stat);
omOvlHisData *omOvlHisGet(s32 level);
Process *omInitObjMan(s16 max_objs, int prio);
void omDestroyObjMan(void);
omObjData *omAddObjEx(Process *objman_process, s16 prio, u16 mdlcnt, u16 mtncnt, s16 group, void (*func)(omObjData *));
void omAddMember(Process *objman_process, u16 group, omObjData *object);
void omDelObjEx(Process *objman_process, omObjData *object);
void omDelMember(Process *objman_process, omObjData *object);
void omMakeGroupEx(Process *objman_process, u16 group, u16 max_objs);
omObjData **omGetGroupMemberListEx(Process *objman_process, s16 group);
void omSetStatBit(omObjData *obj, u16 stat);
void omResetStatBit(omObjData *obj, u16 stat);
void omSetTra(omObjData *obj, float x, float y, float z);
void omSetRot(omObjData *obj, float x, float y, float z);
void omSetSca(omObjData *obj, float x, float y, float z);
void omMain(void);
void omAllPause(BOOL pause);
char omPauseChk(void);
OverlayID omCurrentOvlGet(void);


void omDLLDBGOut(void);
void omDLLInit(FileListEntry *ovl_list);
int omDLLStart(s16 ovl, s16 dll);
void omDLLNumEnd(s16 ovl, s16 arg2);

void omSysPauseEnable(BOOL flag);


void WipeCreate(char dir, char type, short duration);
u8 WipeStatGet(void);

void pfInit(void);
void pfClsScr(void);
s16 print8(s16 x, s16 y, float scale, char *str, ...);
s16 printWin(s16 x, s16 y, s16 w, s16 h, GXColor *color);
void pfDrawFonts(void);

void *HuDvdDataRead(char *path);
void **HuDvdDataReadMulti(char **paths);
void *HuDvdDataReadDirect(char *path, HeapID heap);
void *HuDvdDataFastRead(s32 entrynum);
void *HuDvdDataFastReadNum(s32 entrynum, s32 num);
void *HuDvdDataFastReadAsync(s32 entrynum, DataReadStat *stat);
void HuDvdDataClose(void *ptr);
void HuDvdErrorWatch();

void HuDataInit(void);
int HuDataReadChk(s32 data_num);
DataReadStat *HuDataGetStatus(void *dir_ptr);
void *HuDataGetDirPtr(s32 data_num);
DataReadStat *HuDataDirRead(s32 data_num);
DataReadStat *HuDataDirReadNum(s32 data_num, s32 num);
DataReadStat *HuDataDirSet(void *dir_ptr, s32 data_num);
void HuDataDirReadAsyncCallBack(s32 result, DVDFileInfo* fileInfo);
s32 HuDataDirReadAsync(s32 data_num);
s32 HuDataDirReadNumAsync(s32 data_num, s32 num);
BOOL HuDataGetAsyncStat(s32 status);
void *HuDataRead(s32 data_num);
void *HuDataReadNum(s32 data_num, s32 num);
void *HuDataSelHeapRead(s32 data_num, HeapID heap);
void *HuDataSelHeapReadNum(s32 data_num, s32 num, HeapID heap);
void **HuDataReadMulti(s32 *data_ids);
s32 HuDataGetSize(s32 data_num);
void HuDataClose(void *ptr);
void HuDataCloseMulti(void **ptrs);
void HuDataDirClose(s32 data_id);
void HuDataDirCloseNum(s32 num);
void *HuDataReadNumHeapShortForce(s32 data_id, s32 num, HeapID heap);

void *HuARDirCheck(s32 dir);
void HuAR_ARAMtoMRAM(void *dst);
void HuAR_ARAMtoMRAMNum(void *dst, s32 num);
BOOL HuARDMACheck();

void Hu3DModelPosSet(s16 index, float x, float y, float z);
void Hu3DModelRotSet(s16 index, float x, float y, float z);
void Hu3DModelScaleSet(s16 index, float x, float y, float z);

void espInit(void);
void espScaleSet(s16, f32, f32);
s16 espEntry(s32, s32, s32);
void espDispOff(s16);
void espKill(s16);
void espDispOn(s16);
void espPosSet(s16, f32, f32);

void HuSprInit(void);
void HuSprClose(void);
void HuSprExec(short draw_no);
void HuSprBegin(void);
SpriteData *HuSprCall(void);
void HuSprFinish(void);
void HuSprPauseSet(BOOL value);
AnimData *HuSprAnimRead(void *data);
void HuSprAnimLock(AnimData *anim);
short HuSprCreate(AnimData *anim, short prio, short bank);
short HuSprFuncCreate(void (*func)(SpriteData *sprite), short prio);
short HuSprGrpCreate(short capacity);
short HuSprGrpCopy(short group);
void HuSprGrpMemberSet(short group, short member, short sprite);
void HuSprGrpMemberKill(short group, short member);
void HuSprGrpKill(short group);
void HuSprKill(short sprite);
void HuSprAnimKill(AnimData *anim);
void HuSprAttrSet(short group, short member, int attr);
void HuSprAttrReset(short group, short member, int attr);
void HuSprPosSet(short group, short member, float x, float y);
void HuSprZRotSet(short group, short member, float z_rot);
void HuSprScaleSet(short group, short member, float x, float y);
void HuSprTPLvlSet(short group, short member, float tp_lvl);
void HuSprColorSet(short group, short member, u8 r, u8 g, u8 b);
void HuSprSpeedSet(short group, short member, float speed);
void HuSprBankSet(short group, short member, short bank);
void HuSprGrpPosSet(short group, float x, float y);
void HuSprGrpCenterSet(short group, float x, float y);
void HuSprGrpZRotSet(short group, float z_rot);
void HuSprGrpScaleSet(short group, float x, float y);
void HuSprGrpTPLvlSet(short group, float tp_lvl);
void HuSprGrpDrawNoSet(short group, int draw_no);
void HuSprDrawNoSet(short group, short member, int draw_no);
void HuSprPriSet(short group, short member, short prio);
void HuSprGrpScissorSet(short group, short x, short y, short w, short h);
void HuSprScissorSet(short group, short member, short x, short y, short w, short h);
AnimData *HuSprAnimMake(short sizeX, short sizeY, short dataFmt);
void HuSprBGSet(short group, short member,  AnimData *bg, short bg_bank);
void HuSprSprBGSet(short sprite, AnimData *bg, short bg_bank);
void AnimDebug(AnimData *anim);

void HuWinAllKill(void);
void HuWinMesSet(s16, s32);
void HuWinKill(s16);
void HuWinPriSet(s16, s32);
void HuWinMesPalSet(s16, s32, s32, s32, s32);
void HuWinMesSpeedSet(s16, s32);
void HuWinMesMaxSizeGet(s32, f32*, ...);
s16 HuWinCreate(float x, float y, s16 w, s16 h, s16 frame);

void HuPadRumbleAllStop(void);
s16 HuPadStatGet(s16);

void HuAudFXListnerKill(void);
void HuAudDllSndGrpSet(u16 ovl);
void HuAudVoiceInit(s16 ovl);

void MGSeqKillAll(void);

void MGSeqPracticeStart(void);
void fn_8004D6F4(s16 arg);

s32 _CheckFlag(u32 flag);

void BoardMessCreate(s16, s32, s32);
void BoardMessKill(void);
void BoardMessWait(void);

s32 rand8(void);

void fn_8005D8E8(void); 
void fn_8005DB6C(s16, Vec3f*, s32, f32, f32, s32); 
void fn_8005E0C0(void);
void fn_80074210(s32, s32, Vec3f*);
void fn_8007A360(s32);
void fn_8007F894(void);
void fn_80083F84(void);
void fn_800884F4(s32);
void fn_800A4C88(void);
void fn_800A6B10(void);
void fn_8008853C(s32);
void fn_800B42B4(s32);
void fn_80082AAC(s32);
void fn_800B4264(s32, s32, s32);
void fn_8007500C(s32);
void fn_8006F0D4(s32, f32);
f32 fn_8006F128(s32);
f64 fmod(f32, f64);
void fn_8006F61C(s16, s32);
void fn_800B42BC(s16);
s32 fn_8006DBD4(s16);
void fn_8005B150(void*, void*);
void fn_8006F2E8(s32, Vec3f*);
void fn_8005D10C(void*, void*);
s16 fn_8006D9A4(s32, void*, s32);
void fn_8006DB90(s16);
void fn_8006DDE8(s16, f32);
void fn_8006E2B8(s16, s32, s32);
void fn_8006E878(s16, f32);
void fn_8006F158(s16, void*);
void fn_8006F1A8(s16, f32, f32, f32);
s32 fn_8006F220(s16 arg0, Vec3f* arg1);
void fn_8006F50C(s16, s32);
void fn_80073FF4(void*);
void fn_80073FFC(void*);
void fn_80074004(void*);
s32 fn_800745F0(s32, s32);
void fn_800772EC(s32);
void fn_80077A3C(void);
void fn_80077AAC(s16);
void fn_8007A83C(s16);
void fn_80083EDC(s16);
void fn_800A4F6C(s16);
void fn_800B3FD8(void*);
void fn_800B4274(s32, s32);
void fn_8005D5C0(Vec3f*);
void fn_8006F338(s16, f32, f32, f32);
s32 fn_8005B6A8(void);
void fn_8006EFBC(s16, Mtx);
void fn_8006F270(s16, f32, f32, f32);

#endif
