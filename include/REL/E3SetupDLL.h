#ifndef E3SETUPDLL_H
#define E3SETUPDLL_H

#include "game/object.h"
#include "game/pad.h"

typedef struct e3pad {
	u16 btn;
	u16 btnDown;
	u16 enable;
	u16 unk6;
} E3Pad;

extern E3Pad e3PadData[4];
extern s16 e3PadCtrl;
extern s16 e3ConfigPlayerF;
extern s32 e3ExitEnableF;
extern OverlayID e3NextOvl;
extern s32 e3NextEvent;
extern u32 e3ExitMode;

void E3MainInit(void);
void E3MGSelectInit(void);
s16 E3PadRead(void);
u16 E3PadUpdate(s16 player, E3Pad *pad);
void E3OvlWatchInit(omObjData *object);
void E3BGCreate(omObjData *object);
void E3LightInit(void);

#endif