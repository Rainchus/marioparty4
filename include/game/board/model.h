#ifndef _BOARD_WARP_H
#define _BOARD_WARP_H

#include "game/hsfman.h"
#include "game/data.h"

typedef struct board_model_param {
	s32 data_num;
	struct {
		u8 field04_bit0 : 2;
		u8 visible : 1;
		u8 link : 1;
		u8 start_mot : 1;
		u8 pause : 1;
	};
	s16 unk6;
} BoardModelParam;

void BoardModelInit(void);
void BoardModelKillAll(void);
void BoardModelDummyUpdate(void);
void BoardModelVisibilityUpdate(void);
void BoardModelHideSetAll(s32 flag);
void BoardModelAmbSetAll(float r, float g, float b);
void BoardModelCameraSetAll(u16 camera);
s16 BoardModelCreate(s32 data_num, s32 *mot_list, s32 link);
s16 BoardModelCreateCharacter(s32 character, s32 data_num, s32 *mot_list, s32 link);
s16 BoardModelCreateParam(BoardModelParam *param, Vec *pos, Vec *rot);
void BoardModelKill(s16 model);
s16 BoardModelIDGet(s16 model);
s32 fn_8006DC1C(s16 model, s32 arg1);
s32 BoardModelPassSet(s16 model, s32 pass);
s32 BoardModelAmbSet(s16 model, float r, float g, float b);
s32 BoardModelExistCheck(s16 model, s32 arg1);
s32 BoardModelExistDupe(s16 model, s32 arg1);
s32 fn_8006DDE8(s16 model, float arg1);
s32 BoardModelMotionStart(s16 model, s32 slot, u32 attr);
s32 BoardModelMotionSpeedSet(s16 model, float speed);
void BoardModelPosSet(s16 model, float x, float y, float z);
void BoardModelPosSetV(s16 model, Vec *pos);
void BoardModelRotSet(s16 model, float x, float y, float z);
void BoardModelRotSetV(s16 model, Vec *rot);
void BoardModelScaleSet(s16 model, float x, float y, float z);
void BoardModelScaleSetV(s16 model, Vec *scale);
void BoardModelVisibilitySet(s16 model, s32 flag);


#endif