#ifndef RESULTDLL_H
#define RESULTDLL_H

#include "game/data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"

#include "game/sprite.h"

typedef struct datalist_model {
	s32 datanum;
	u32 attr;
	s16 type;
	s16 link;
	s16 mot_link;
	Vec pos;
	Vec rot;
	Vec scale;
} DataListModel;

typedef struct datalist_sprite {
	u32 datanum;
	s16 attr;
	s16 prio;
	float x;
	float y;
	GXColor color;
} DataListSprite;

void fn_1_6490(void);

void fn_1_8FF8(DataListModel *model_list);
void fn_1_927C(DataListSprite *sprite_list);
void fn_1_93B4(void);

extern s16 lbl_1_bss_1A9C[32];
extern s16 lbl_1_bss_1A5C[32];
extern s16 lbl_1_bss_1A1A[33];
extern s16 lbl_1_bss_1A18;

#endif