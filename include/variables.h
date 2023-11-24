#ifndef _VARIABLES_H
#define _VARIABLES_H

#include "types.h"
#include "common_structs.h"
#include "dolphin/os.h"
#include "dolphin/gx/GXStruct.h"

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

extern PlayerConfig gPlayerConfig[4];

extern FileListEntry _ovltbl[];

extern u32 DirDataSize;

#endif
