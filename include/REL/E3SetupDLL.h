#ifndef E3SETUPDLL_H
#define E3SETUPDLL_H

#include "game/animdata.h"
#include "game/object.h"
#include "game/pad.h"

typedef struct e3pad {
	u16 btn;
	u16 btnDown;
	u16 enable;
	u16 unk6;
} E3Pad;

typedef struct mgInterface {
	/* 0x00 */ AnimData *unk00[2];
	/* 0x08 */ s32 pad;
	/* 0x0C	*/ s32 pad2;
	/* 0x10 */ s32 pad3;
	/* 0x14 */ s32 pad4;
	/* 0x18 */ s32 pad5;
	/* 0x1C */ s16 group;
	/* 0x1E */ s16 group2;
	/* 0x20 */ s32 pad6;
	/* 0x24 */ s32 pad7;
	/* 0x28 */ s32 pad8;
	/* 0x2C */ s16 unk2C;
	/* 0x2E */ s32 pad9;
	/* the struct is 0x34 big */
} mgInterface;

typedef struct mgPic {
	/* 0x00 */ AnimData *unk00[2];
	/* 0x08 */ s32 pad;
	/* 0x0C	*/ s32 pad2;
	/* 0x10 */ s32 pad3;
	/* 0x14 */ s32 pad4;
	/* 0x18 */ s32 pad5;
	/* 0x1C */ s16 pad6;
	/* 0x1E */ s16 pad7;
	/* 0x20 */ s32 pad8;
	/* 0x24 */ s32 pad9;
	/* 0x28 */ s32 pad10;
	/* 0x2C */ s16 unk2C;
	/* 0x2E */ s32 pad11;
	/* 0x32 */ s32 pad12;
	/* 0x36 */ s32 pad13;
	/* 0x3A */ s32 pad14;
	/* 0x40 */ s16 unk40;
	/* 0x44 */ s32 pad15;
	/* 0x48	*/ s32 pad16;
	/* 0x4C */ s32 unk4C;
	/* 0x50 */ s32 pad18;
	/* the struct is 0x54 big */
} mgPic;

typedef struct mgSelect {
	/* 0x00 */ AnimData *unk00[4];
	/* 0x10 */ s32 pad3;
	/* 0x14 */ s32 pad4;
	/* 0x18 */ s32 pad5;
	/* 0x1C */ s16 unk1C;
	/* 0x1E */ s16 unk1E;
	/* 0x20 */ s16 unk20;
	/* 0x22 */ s16 pad20;
	/* 0x24 */ s32 pad9;
	/* 0x28 */ s32 pad10;
	/* 0x2C */ s16 unk2C;
	/* 0x2E */ s16 unk2E[4];
	/* 0x36 */ s16 pad13;
	/* 0x38 */ s16 unk38[4];
	/* 0x40 */ s16 pad15;
	/* 0x42 */ s16 unk42;
	/* 0x44 */ s16 unk44;
	/* 0x46 */ s16 unk46;
	/* 0x48	*/ s32 pad17;
	/* 0x4C */ s32 pad18;
	/* 0x50 */ s32 pad19;
	/* the struct is 0x54 big */
} mgSelect;

extern E3Pad e3PadData[4];
extern s16 e3PadCtrl;
extern s16 e3ConfigPlayerCnt;
extern s16 e3ConfigPlayerF;
extern s32 e3ExitEnableF;
extern OverlayID e3NextOvl;
extern s32 e3NextEvent;
extern u32 e3ExitMode;
extern float e3CameraFov;
extern omObjData *e3MenuMainObj;
extern omObjData *e3ViewObj;
extern omObjData *e3OvlWatchObj;
extern omObjData *e3BGObj;

void E3MainInit(void);
void E3MGSelectInit(void);
s16 E3PadRead(void);
u16 E3PadUpdate(s16 player, E3Pad *pad);
void E3OvlWatchInit(omObjData *object);
void E3BGCreate(omObjData *object);
void E3LightInit(void);

#endif
