#include "game/object.h"
#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/hsfmotion.h"
#include "game/init.h"
#include "game/minigame_seq.h"
#include "game/chrman.h"
#include "game/sprite.h"
#include "game/window.h"

#include "REL/E3SetupDLL.h"

static struct {
	s16 playerCnt;
	s16 rumble;
	s16 mgF;
	s16 board;
	s16 port[4];
	s16 character[4];
} configE3;

E3Pad e3PadData[4];
s16 e3PadCtrl;
s16 e3ConfigPlayerCnt;
static s32 e3EvtNo;
s32 e3ExitEnableF;
s32 lbl_2_bss_B0;
OverlayID e3NextOvl;
s32 e3NextEvent;
u32 e3ExitMode;
static s32 needCharKill;
float e3CameraFov;
omObjData *e3MenuMainObj;
omObjData *e3ViewObj;
omObjData *e3OvlWatchObj;
static omObjData *cameraObj;
static omObjData *lbl_2_bss_84[2];
static omObjData *configModeObj[4];
omObjData *e3BGObj;
omObjData *lbl_2_bss_6C;
static s16 lightE3;
s16 lbl_2_bss_62[4];
s16 lbl_2_bss_60;
Vec lbl_2_bss_54;
Vec lbl_2_bss_48;
float lbl_2_bss_44;
s16 lbl_2_bss_40;
s32 lbl_2_bss_3C;
s16 lbl_2_bss_3A;
s16 lbl_2_bss_38;
s16 lbl_2_bss_36;
s16 lbl_2_bss_34;
s16 lbl_2_bss_2A[5];
static s16 repBtn;

static Vec shadowPos = {
	0, 12000, 0
};

static Vec shadowTarget = {
	0, 0, 0
};

static Vec shadowUp = {
	0, 0, -1
};

Vec lbl_2_data_274[] = {
	477.5, 500, -425,
	-477.5, 500, -425,
	477.5, 500, 425,
	-477.5, 500, 425,
	0.11, -1, -0.22,
	-0.11, -1, -0.22,
	0.11, -1, 0.22,
	-0.11, -1, 0.22,
};

static s16 playerCntTbl[] = {
	1, 2, 3, 4
};

static s16 charTbl[] = {
	0, 1, 2, 3,
	-1, -1, 6, 7
};

static s32 charSfxTbl[] = {
	295,
	359,
	423,
	487,
	551,
	615,
	679,
	743
};

void ModuleProlog(void)
{
	e3EvtNo = omovlevtno;
	HuAudSndGrpSetSet(0);
	e3ExitEnableF = 0;
	lbl_2_bss_B0 = 0;
	e3PadCtrl = 0;
	e3NextOvl = 0;
	e3NextEvent = 0;
	e3ExitMode = 0;
	switch(e3EvtNo) {
		default:
		case 0:
			repBtn = 0;
			needCharKill = 1;
			E3MainInit();
			break;
			
		case 1:
			repBtn = 1;
			needCharKill = 0;
			E3MGSelectInit();
			break;
	}
}

static void InitCamera(omObjData *object);
static void InitMenuControl(omObjData *object);
static void InitPlayerCnt(omObjData *object);
static void InitCharSel(omObjData *object);
static void InitVibrateCfg(omObjData *object);
static void InitGameModeSel(omObjData *object);

void E3MainInit(void)
{
	s32 idx = E3PadRead();
	s32 port;
	Process *objman;
	if(idx == 0) {
		OSReport("No pad detected\n");
		idx++;
	}
	e3ConfigPlayerCnt = idx;
	configE3.playerCnt = idx-1;
	port = (GWRumbleGet()) ? 1 : 0;
	configE3.rumble = port;
	configE3.mgF = 0;
	configE3.board = 0;
	for(port=0,idx=0; port<4; idx++, port++) {
		while(idx < 8) {
			if(charTbl[idx] >= 0) {
				break;
			}
			idx++;
		}
		configE3.character[port] = idx;
	}
	for(port=0,idx=0; port<4; port++) {
		if(!e3PadData[port].enable) {
			configE3.port[idx] = port;
			if(idx == 0) {
				e3PadCtrl = port;
			}
			idx++;
		}
	}
	for(port=0; port<4; port++) {
		if(e3PadData[port].enable) {
			configE3.port[idx] = port;
			idx++;
		}
	}
	HuSysVWaitSet(1);
	objman = omInitObjMan(80, 8192);
	
	HuWinInit(1);
	CRot.x = -4;
	CRot.y = 0;
	CRot.z = 0;
	Center.x = 0;
	Center.y = 160;
	Center.z = 0;
	CZoom = 1960;
	e3CameraFov = 40;
	Hu3DCameraCreate(1);
	Hu3DCameraPerspectiveSet(1, e3CameraFov, 100, 25000, 4.0f/3.0f);
	Hu3DShadowCreate(e3CameraFov*0.3f, 100, 25000);
	Hu3DShadowTPLvlSet(0.6f);
	Hu3DShadowPosSet(&shadowPos, &shadowUp, &shadowTarget);
	e3ViewObj = omAddObjEx(objman, 32730, 0, 0, -1, omOutView);
	cameraObj = omAddObjEx(objman, 199, 0, 0, -1, InitCamera);
	e3OvlWatchObj = omAddObjEx(objman, 200, 0, 0, -1, E3OvlWatchInit);
	e3MenuMainObj = omAddObjEx(objman, 10, 0, 0, -1, InitMenuControl);
	e3BGObj = omAddObjEx(objman, 20, 0, 0, -1, E3BGCreate);
	configModeObj[0] = omAddObjEx(objman, 30, 0, 0, -1, InitPlayerCnt);
	configModeObj[0]->work[0] = 1;
	configModeObj[1] = omAddObjEx(objman, 30, 0, 0, -1, InitCharSel);
	configModeObj[2] = omAddObjEx(objman, 30, 0, 0, -1, InitVibrateCfg);
	configModeObj[3] = omAddObjEx(objman, 30, 0, 0, -1, InitGameModeSel);
	E3LightInit();
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
}

void E3LightInit(void)
{
	s32 i;
	lightE3 = lbl_2_bss_60 = -1;
	for(i=0; i<4; i++) {
		lbl_2_bss_62[i] = -1;
	}
	lbl_2_bss_54.x = 0;
	lbl_2_bss_54.y = 1500;
	lbl_2_bss_54.z = 0;
	lbl_2_bss_48.x = 0;
	lbl_2_bss_48.y = -1;
	lbl_2_bss_48.z = 0;
	lbl_2_bss_44 = 26;
	lbl_2_bss_40 = 4;
	lightE3 = Hu3DGLightCreate(0, 1500, 0, 0, -1, 0, 255, 255, 255);
	Hu3DGLightStaticSet(lightE3, 1);
	Hu3DGLightInfinitytSet(lightE3);
}

static float GetStickX(s8 value)
{
	float new_value;
	if(value > 69) {
		value = 69;
	} else if(value < -69) {
		value = -69;
	}
	new_value = value;
	new_value /= 69;
	return new_value;
}

static s16 GetStickY(s8 value)
{
	float new_value;
	if(value > 69) {
		value = 69;
	} else if(value < -69) {
		value = -69;
	}
	new_value = value;
	new_value *= 255.0f/69;
	return new_value;
}

static u16 GetBtn(s16 player)
{
	u16 value;
	if(repBtn) {
		value = HuPadDStkRep[player];
		value |= HuPadBtnRep[player];
	} else {
		value = HuPadDStk[player];
		value |= HuPadBtn[player];
	}
	return value;
}

static u16 GetBtnDown(u16 button, u16 buttonLast)
{
	u16 down = PADButtonUp(button, buttonLast);
	return down;
}

u16 E3PadUpdate(s16 player, E3Pad *pad)
{
	pad->enable = HuPadStatGet(player);
	if(!pad->enable) {
		u16 btn = GetBtn(player);
		pad->btnDown = PADButtonUp(btn, pad->btn);
		pad->btn = btn;
	} else {
		pad->btnDown = pad->btn = 0;
	}
	return pad->btnDown;
}

s16 E3PadRead(void)
{
	s16 i;
	s16 players;
	for(i=0, players=0; i<4; i++) {
		E3PadUpdate(i, &e3PadData[i]);
		if(!e3PadData[i].enable) {
			players++;
		}
	}
	return players;
}

float MotionMaxTimeGet(s16 arg0)
{
    MotionData *temp_r31 = &Hu3DMotion[arg0];
    HsfMotion *temp_r30;
    s16 temp_r29;

    temp_r30 = temp_r31->unk_04->motion;
    temp_r29 = temp_r30->len;
    return temp_r29;
}


float MotionShiftTimeGet(s16 arg0)
{
    ModelData *temp_r31 = &Hu3DData[arg0];

    return temp_r31->unk_84;
}

static void UpdateMenuControl(omObjData *object);

static void InitMenuControl(omObjData *object)
{
	HuAudSeqPlay(43);
	lbl_2_bss_3C = 0;
	lbl_2_bss_3A = -1;
	lbl_2_bss_36 = 30;
	lbl_2_bss_34 = 0;
	object->func = UpdateMenuControl;
	worstVcount = 0;
	object->work[0] = 0;
	object->work[1] = 0;
	object->work[3] = 0;
}

static void UpdateMenuControl(omObjData *object)
{
	s32 pos;
	
	if(e3ExitEnableF) {
		return;
	}
	E3PadRead();
	pos = object->work[1];
	if(pos < 4) {
		omObjData *config = configModeObj[pos];
		if(config->work[0] == 0) {
			if(config->work[3]) {
				pos++;
			} else {
				pos--;
				if(pos < 0) {
					omOvlHisData *his;
					pos=0;
					his = omOvlHisGet(1);
					omOvlHisChg(1, his->overlay, 1, his->stat);
					e3ExitMode = 0;
					e3NextOvl = 0;
					e3NextEvent = 0;
					e3ExitEnableF = 1;
				}
			}
			
			if(pos < 4) {
				configModeObj[pos]->work[0] = 1;
			}
		}
		object->work[1] = pos;
	}
	if(pos >= 4) {
		s32 playerCnt;
		e3ExitMode = 2;
		if(configE3.mgF) {
			e3NextOvl = OVL_E3SETUP;
			e3NextEvent = 1;
		} else {
			if(configE3.board) {
				e3NextOvl = OVL_W02;
			} else {
				e3NextOvl = OVL_W01;
			}
		}
		GWRumbleSet(configE3.rumble);
		playerCnt = playerCntTbl[configE3.playerCnt];
		for(pos=0; pos<4; pos++) {
			s16 character;
			GWPlayerCfg[pos].pad_idx = configE3.port[pos];
			character = configE3.character[pos];
			GWPlayerCfg[pos].character = character;
			if(!configE3.mgF) {
				HuAudFXPlay(charSfxTbl[character]);
			}
			GWPlayerCfg[pos].group = pos;
			if(pos < playerCnt) {
				GWPlayerCfg[pos].iscom = 0;
			} else {
				GWPlayerCfg[pos].iscom = 1;
			}
		}
		e3ExitEnableF = 1;
	}
}

static void UpdateOvlWatch(omObjData *object)
{
	s32 i;
	if(WipeStatGet()) {
		return;
	}
	if(!MGSeqDoneCheck()) {
		return;
	}
	HuSysVWaitSet(1);
	if(needCharKill) {
		CharKill(-1);
		for(i=0; i<4; i++) {
			CharARAMOpen(GWPlayerCfg[i].character);
		}
	}
	if(e3ExitMode == 1) {
		omOvlGotoEx(e3NextOvl, 1, e3NextEvent, 0);
	} else if(e3ExitMode == 2) {
		omOvlCallEx(e3NextOvl, 1, e3NextEvent, 0);
	} else {
		omOvlReturnEx(e3NextOvl+1, 1);
	}
}

void E3OvlWatchInit(omObjData *object)
{
	if(e3ExitEnableF) {
		HuAudSeqAllFadeOut(2500);
		WipeColorSet(0, 0, 0);
		WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
		MGSeqKillAll();
		object->func = UpdateOvlWatch;
	}
}

typedef struct e3_player_cnt_work {
	AnimData *frame[3];
	AnimData *arrow;
	AnimData *arrow_hilite;
	float winSize[2]; //Should be struct
	s16 frameGroup;
	s16 arrowGroup;
	s16 arrowGroup2;
	s16 unk22[6];
	s16 winHeader;
	s16 winPlayer;
	s16 playerCnt;
	s16 playerCntOld;
} E3PlayerCntWork;

static s16 lbl_2_data_31E[] = {
	35, 38, 41, 44
};

static u32 playerCntMessTbl[] = {
	0x00220002,
	0x00220003,
	0x00220004,
	0x00220001
};

static void UpdatePlayerCnt(omObjData *object)
{
	E3PlayerCntWork *work = object->data;
	s32 i;
	u16 btnDown;
	u32 mess;
	if(object->work[1] != object->work[0]) {
		if(object->work[0] == 0) {
			object->work[2] = 4;
		} else {
			object->work[2] = 3;
		}
		object->work[1] = object->work[0];
	}
	btnDown = e3PadData[e3PadCtrl].btnDown;
	switch(object->work[2]) {
		case 0:
			break;
		case 1:
			if(btnDown & PAD_BUTTON_A) {
				HuAudFXPlay(1);
				configE3.playerCnt = work->playerCnt;
				object->work[0] = 0;
				object->work[3] = 1;
			} else if(btnDown & PAD_BUTTON_B) {
				HuAudFXPlay(3);
				work->playerCnt = configE3.playerCnt;
				object->work[0] = 0;
				object->work[3] = 0;
			} else {
				if(e3ConfigPlayerCnt) {
					if(btnDown & PAD_BUTTON_LEFT) {
						HuAudFXPlay(0);
						work->playerCnt--;
						if(work->playerCnt < 0) {
							work->playerCnt = e3ConfigPlayerCnt-1;
							if(work->playerCnt < 0) {
								work->playerCnt = 0;
							}
						}
					} else if(btnDown & PAD_BUTTON_RIGHT) {
						HuAudFXPlay(0);
						work->playerCnt++;
						if(work->playerCnt >= e3ConfigPlayerCnt) {
							work->playerCnt = 0;
						}
					}
				} else {
					work->playerCnt = 0;
				}
			}
			break;
			
		case 3:
			HuSprAttrSet(work->frameGroup, 2, HUSPR_ATTR_DISPOFF);
			if(e3ConfigPlayerCnt > 1) {
				for(i=0; i<2; i++) {
					HuSprAttrReset(work->arrowGroup, i, HUSPR_ATTR_DISPOFF);
					HuSprAttrReset(work->arrowGroup2, i, HUSPR_ATTR_DISPOFF);
				}
			}
			object->work[2] = 1;
			break;
			
		case 4:
			HuSprAttrReset(work->frameGroup, 2, HUSPR_ATTR_DISPOFF);
			for(i=0; i<2; i++) {
				HuSprAttrSet(work->arrowGroup, i, HUSPR_ATTR_DISPOFF);
				HuSprAttrSet(work->arrowGroup2, i, HUSPR_ATTR_DISPOFF);
			}
			object->work[2] = 0;
			break;
	}
	if(work->playerCntOld != work->playerCnt) {
		float size[2];
		mess = playerCntMessTbl[work->playerCnt];
		HuWinMesMaxSizeGet(1, size, mess);
		HuWinCenterPosSet(work->winPlayer, (work->winSize[0]-size[0])/-2.0f, (work->winSize[1]-size[1])/-2.0f);
		HuWinMesSet(work->winPlayer, mess);
		work->playerCntOld = work->playerCnt;
	}
}

static void InitPlayerCnt(omObjData *object)
{
	
}