#ifndef _VARIABLES_H
#define _VARIABLES_H

#include "types.h"
#include "common_structs.h"
#include "dolphin/os.h"
#include "dolphin/gx/GXStruct.h"

#define M_PI 3.141592653589793

extern u16 HuPadBtnDown[4];
extern u8 HuPadDStk[4];

extern OSHeapHandle currentHeapHandle;
extern GXRenderModeObj *RenderMode;

extern BOOL saftyFrameF;
extern u16 strlinecnt;
extern u16 empstrline;
extern int fontcolor;
extern u32 procfunc;

extern WipeState wipeData;

extern PlayerConfig GWPlayerCfg[4];

extern FileListEntry _ovltbl[];

extern u32 DirDataSize;

extern u32 totalPolyCnted;
extern char fadeStat;

extern omObjData *omDBGSysKeyObj;
extern Process *omwatchproc;
extern OverlayID omnextovl;
extern OverlayID omcurovl;
extern int omcurdll;
extern int omovlhisidx;
extern int omovlevtno;
extern int omnextovlevtno;
extern int omovlstat;
extern char omUPauseFlag;
extern s16 omSysExitReq;
extern s16 omdispinfo;
extern char omSysPauseEnableFlag;
extern OverlayID omprevovl;
extern PlayerState GWPlayer[4];
extern SystemState GWSystem;

extern u32 minimumVcount;

#endif
