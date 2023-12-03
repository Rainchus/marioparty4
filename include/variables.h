#ifndef _VARIABLES_H
#define _VARIABLES_H

#include "types.h"
#include "common_structs.h"
#include "dolphin/os.h"
#include "dolphin/gx/GXStruct.h"

#define M_PI 3.141592653589793

extern u16 HuPadBtnDown[4];
extern u8 HuPadDStk[4];

extern WipeState wipeData;

extern PlayerConfig GWPlayerCfg[4];


extern u32 DirDataSize;

extern u32 totalPolyCnted;
extern char fadeStat;

extern PlayerState GWPlayer[4];
extern SystemState GWSystem;


#endif
