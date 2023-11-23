#ifndef _VARIABLES_H
#define _VARIABLES_H

#include "types.h"
#include "common_structs.h"
#include "dolphin/os.h"

extern u16 HuPadBtnDown[4];
extern u8 HuPadDStk[4];

extern OSHeapHandle currentHeapHandle;

extern BOOL saftyFrameF;
extern u16 strlinecnt;
extern u16 empstrline;
extern int fontcolor;
extern u32 procfunc;

extern WipeState wipeData;

extern PlayerConfig gPlayerConfig[4];

#endif
