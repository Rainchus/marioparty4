#include "common.h"
#include "game/process.h"
#include "game/data.h"
#include "game/sprite.h"
#include "game/object.h"
#include "game/audio.h"
#include "game/memory.h"
#include "game/hsfman.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/window.h"
#include "game/thpmain.h"
#include "math.h"

#define HU_PAD_BTN_ALL (HuPadBtn[0] | HuPadBtn[1] | HuPadBtn[2] | HuPadBtn[3])
#define HU_PAD_BTNDOWN_ALL (HuPadBtnDown[0] | HuPadBtnDown[1] | HuPadBtnDown[2] | HuPadBtnDown[3])
#define HU_PAD_DSTK_ALL (HuPadDStkRep[0] | HuPadDStkRep[1] | HuPadDStkRep[2] | HuPadDStkRep[3])

extern int lbl_801D3A00;

Process *lbl_1_bss_54;
Vec lbl_1_bss_3C[2];
Vec lbl_1_bss_24[2];
float lbl_1_bss_1C[2];

s16 lbl_1_bss_E[7];

s16 lbl_1_bss_8[3];
s16 lbl_1_bss_6;

s16 lbl_1_bss_4;
s32 lbl_1_bss_0;

void fn_1_26C(void);
void fn_1_9F8(void);
void fn_1_AC0(void);
void fn_1_2100(void);
BOOL fn_1_2474(void);

void *logoReadNintendo(void);

void ModuleProlog(void)
{
	omOvlHisData *history;
	OSReport("******* Boot ObjectSetup *********\n");
	lbl_1_bss_54 = omInitObjMan(50, 8192);
	lbl_1_bss_3C[0].x = -67;
	lbl_1_bss_3C[0].y = 40;
	lbl_1_bss_3C[0].z = 0;
	lbl_1_bss_24[0].x = 260;
	lbl_1_bss_24[0].y = -103;
	lbl_1_bss_24[0].z = -18;
	lbl_1_bss_1C[0] = 2885;
	Hu3DCameraCreate(1);
	Hu3DCameraPerspectiveSet(1, 30, 20, 15000, 1.2);
	Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
	HuPrcCreate(fn_1_26C, 100, 12288, 0);
	Hu3DBGColorSet(0, 0, 0);
	history = omOvlHisGet(0);
	omOvlHisChg(0, history->overlay, 1, history->stat);
}

void fn_1_26C(void)
{
	AnimData *data;
	s16 group;
	s16 sprite_nintendo;
	s16 sprite_hudson;
	s16 i;
	OSTick tick_prev;
	Process *curr = HuPrcCurrentGet();
	if(omovlevtno == 0) {
		fn_1_AC0();
	}
	group = HuSprGrpCreate(2);
	data = HuSprAnimRead(logoReadNintendo());
	sprite_nintendo = HuSprCreate(data, 0, 0);
	HuSprGrpMemberSet(group, 0, sprite_nintendo);
	HuSprPosSet(group, 0, 288, 240);
	HuSprAttrSet(group, 0, SPRITE_ATTR_HIDDEN);
	if(omovlevtno != 0) {
		HuAudSndGrpSetSet(0);
		data = HuSprAnimReadFile(MAKE_DATA_NUM(DATADIR_TITLE, 1));
		sprite_hudson = HuSprCreate(data, 0, 0);
		HuSprGrpMemberSet(group, 1, sprite_hudson);
		HuSprPosSet(group, 1, 288, 240);
		HuSprAttrSet(group, 1, SPRITE_ATTR_HIDDEN);
		HuWinInit(1);
		fn_1_2100();
		lbl_801D3A00 = 1;
	} else {
		s16 group_thp;
		BOOL skip_wait;
		float win_size[2];
		s16 sprite_thp;
		for(i=0; i<4; i++) {
			GWPlayerCfg[i].pad_idx = i;
		}
		repeat:
		HuSprAttrReset(group, 0, SPRITE_ATTR_HIDDEN);
		WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
		while(WipeStatGet()) {
			HuPrcVSleep();
		}
		WipeColorSet(255, 255, 255);
		if(!lbl_801D3A00) {
			tick_prev = OSGetTick();
			fn_800498F0();
			HuWindowInit();
			MGSeqInit();
			HuWinInit(1);
			fn_1_2100();
			data = HuSprAnimReadFile(MAKE_DATA_NUM(DATADIR_TITLE, 1));
			sprite_hudson = HuSprCreate(data, 0, 0);
			HuSprGrpMemberSet(group, 1, sprite_hudson);
			HuSprPosSet(group, 1, 288, 240);
			HuSprAttrSet(group, 1, SPRITE_ATTR_HIDDEN);
			while(OSTicksToMilliseconds(OSGetTick()-tick_prev) < 3000) {
				HuPrcVSleep();
			}
		} else {
			for(i=0; i<180; i++) {
				if(HuPadBtnDown[0] & (PAD_BUTTON_START|PAD_BUTTON_A)) {
					break;
				}
				HuPrcVSleep();
			}
		}
		WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
		while(WipeStatGet()) {
			HuPrcVSleep();
		}
		HuSprAttrSet(group, 0, SPRITE_ATTR_HIDDEN);
		HuSprAttrReset(group, 1, SPRITE_ATTR_HIDDEN);
		HuPrcSleep(60);
		WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
		while(WipeStatGet()) {
			HuPrcVSleep();
		}
		if(!lbl_801D3A00) {
			void *group_samp;
			tick_prev = OSGetTick();
			group_samp = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(0));
			msmSysLoadGroup(0, group_samp, 0);
			HuMemDirectFree(group_samp);
			while(OSTicksToMilliseconds(OSGetTick()-tick_prev) < 3000) {
				HuPrcVSleep();
			}
		} else {
			for(i=0; i<180; i++) {
				if(HuPadBtnDown[0] & (PAD_BUTTON_START|PAD_BUTTON_A)) {
					break;
				}
				HuPrcVSleep();
			}
		}
		WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
		while(WipeStatGet()) {
			HuPrcVSleep();
		}
		tick_prev = OSGetTick();
		if(!lbl_801D3A00) {
			HuAudSndGrpSetSet(0);
			lbl_801D3A00 = 1;
		}
		while(OSTicksToMilliseconds(OSGetTick()-tick_prev) < 1000) {
			HuPrcVSleep();
		}
		HuSprAttrSet(group, 0, SPRITE_ATTR_HIDDEN);
		HuSprAttrSet(group, 1, SPRITE_ATTR_HIDDEN);
		group_thp = HuSprGrpCreate(1);
		sprite_thp = HuTHPSprCreateVol("movie/opmov_a00.thp", 0, 100, 122);
		HuSprGrpMemberSet(group_thp, 0, sprite_thp);
		HuSprPosSet(group_thp, 0, 288, 240);
		HuWinMesMaxSizeBetGet(win_size, MAKE_MESSID(54, 0), MAKE_MESSID(54, 4));
		lbl_1_bss_E[0] = HuWinCreate(-10000, 448-win_size[1], win_size[0], win_size[1], 0);
		HuWinMesSpeedSet(lbl_1_bss_E[0], 0);
		HuWinBGTPLvlSet(lbl_1_bss_E[0], 0);
		HuWinPriSet(lbl_1_bss_E[0], 10);
		HuWinAttrSet(lbl_1_bss_E[0], 0x800);
		HuPrcSleep(5);
		WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);
		while(WipeStatGet()) {
			HuPrcVSleep();
		}
		skip_wait = FALSE;
		while(!HuTHPEndCheck()) {
			fn_1_9F8();
			if(HuPadBtnDown[0] & (PAD_BUTTON_START|PAD_BUTTON_A)) {
				skip_wait = TRUE;
				break;
			}
			HuPrcVSleep();
		}
		WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
		while(WipeStatGet()) {
			HuPrcVSleep();
		}
		HuWinKill(lbl_1_bss_E[0]);
		HuTHPClose();
		HuPrcVSleep();
		HuSprGrpKill(group_thp);
		if(!skip_wait) {
			HuPrcSleep(60);
		}
		skip_wait = FALSE;
	}
	if(!fn_1_2474()) {
		HuPrcSleep(60);
		goto repeat;
	}
	WipeColorSet(255, 255, 255);
	HuAudSStreamAllFadeOut(500);
	WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	HuPrcVSleep();
	if(omSysExitReq) {
		omOvlReturnEx(1, 1);
	} else {
		omOvlCallEx(OVL_MODESEL, 1, 0, 0);
	}
	for(i=0; i<4; i++) {
		GWPlayerCfg[i].character = -1;
	}
	HuPrcEnd();
	do {
		HuPrcVSleep();
	} while(1);
}

s16 lbl_1_data_38[] = {
	1686, 1785,
	1850, 1936,
	1993, 2097,
	2135, 2245,
	2258, 2320,
	-1, -1,
};

void fn_1_9F8(void)
{
	int frame = HuTHPFrameGet();
	int i;
	for(i=0; lbl_1_data_38[i*2] != -1; i++) {
		if(frame == lbl_1_data_38[i*2]) {
			HuWinMesSet(lbl_1_bss_E[0], MAKE_MESSID(54, i));
		}
		if(frame == lbl_1_data_38[(i*2)+1]) {
			HuWinHomeClear(lbl_1_bss_E[0]);
		}
	}
}

u16 lbl_1_data_50[] = {
	236, 313,
	353, 313
};

void fn_1_AC0(void)
{
	s16 i;
	s16 option;
	s16 group;
	s16 sprite;
	AnimData *data;
	option = 0;
	if(OSGetResetCode() != OS_RESET_RESTART) {
		return;
	}
	if(VIGetDTVStatus() != VI_NON_INTERLACE) {
		OSSetProgressiveMode(OS_PROGRESSIVE_MODE_OFF);
		return;
	}
	if(OSGetProgressiveMode() == OS_PROGRESSIVE_MODE_OFF && !(HU_PAD_BTN_ALL & PAD_BUTTON_B)) {
		return;
	}
	if(OSGetProgressiveMode() == OS_PROGRESSIVE_MODE_ON) {
		VIConfigure(&GXNtsc480IntDf);
		VIFlush();
	}
	group = HuSprGrpCreate(3);
	data = HuSprAnimReadFile(MAKE_DATA_NUM(DATADIR_TITLE, 3));
	sprite = HuSprCreate(data, 0, 0);
	HuSprGrpMemberSet(group, 0, sprite);
	HuSprPosSet(group, 0, 288, 240);
	data = HuSprAnimReadFile(MAKE_DATA_NUM(DATADIR_TITLE, 6));
	sprite = HuSprCreate(data, 0, 0);
	HuSprGrpMemberSet(group, 1, sprite);
	HuSprPosSet(group, 1, lbl_1_data_50[option*2], lbl_1_data_50[(option*2)+1]);
	data = HuSprAnimReadFile(MAKE_DATA_NUM(DATADIR_TITLE, 7));
	sprite = HuSprCreate(data, 0, 0);
	HuSprGrpMemberSet(group, 2, sprite);
	HuSprPosSet(group, 2, lbl_1_data_50[option*2], lbl_1_data_50[(option*2)+1]);
	HuSprAttrSet(group, 2, SPRITE_ATTR_HIDDEN);
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	for(i=0; i<600; i++) {
		if(HU_PAD_DSTK_ALL & (PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT)) {
			option ^= 1;
			HuSprPosSet(group, 1, lbl_1_data_50[option*2], lbl_1_data_50[(option*2)+1]);
			i=0;
		}
		if(HU_PAD_BTNDOWN_ALL & PAD_BUTTON_A) {
			HuSprAttrSet(group, 1, SPRITE_ATTR_HIDDEN);
			HuSprPosSet(group, 2, lbl_1_data_50[option*2], lbl_1_data_50[(option*2)+1]);
			HuSprAttrReset(group, 2, SPRITE_ATTR_HIDDEN);
			break;
		}
		HuPrcVSleep();
	}
	WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	if(!option) {
		OSSetProgressiveMode(OS_PROGRESSIVE_MODE_ON);
		VIConfigure(&GXNtsc480Prog);
		VIFlush();
		HuPrcSleep(100);
	} else {
		OSSetProgressiveMode(OS_PROGRESSIVE_MODE_OFF);
	}
	HuSprGrpKill(group);
	group = HuSprGrpCreate(1);
	if(!option) {
		data = HuSprAnimReadFile(MAKE_DATA_NUM(DATADIR_TITLE, 4));
	} else {
		data = HuSprAnimReadFile(MAKE_DATA_NUM(DATADIR_TITLE, 5));
	}
	sprite = HuSprCreate(data, 0, 0);
	HuSprGrpMemberSet(group, 0, sprite);
	HuSprPosSet(group, 0, 288, 240);
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	HuPrcSleep(60);
	for(i=0; i<180; i++) {
		if(HU_PAD_BTNDOWN_ALL & PAD_BUTTON_A) {
			break;
		}
		HuPrcVSleep();
	}
	WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	HuSprGrpKill(group);
	HuPrcSleep(30);
}

u16 lbl_1_data_58[] = {
	1, 2
};

void fn_1_1178(void)
{
	
	s16 i;
	for(i=0; i<1; i++) {
		Vec pos, target, up;
		float x, y, z;
		
		x = lbl_1_bss_3C[i].x;
		y = lbl_1_bss_3C[i].y;
		z = lbl_1_bss_3C[i].z;
		
		pos.x = (((sin((M_PI*y)/180.0)*cos((M_PI*x)/180.0))*lbl_1_bss_1C[i])+lbl_1_bss_24[i].x);
		pos.y = (-sin((M_PI*x)/180.0)*lbl_1_bss_1C[i])+lbl_1_bss_24[i].y;
		pos.z = ((cos((M_PI*y)/180.0)*cos((M_PI*x)/180.0))*lbl_1_bss_1C[i])+lbl_1_bss_24[i].z;
		target.x = lbl_1_bss_24[i].x;
		target.y = lbl_1_bss_24[i].y;
		target.z = lbl_1_bss_24[i].z;
		up.x = sin((M_PI*y)/180.0)*sin((M_PI*x)/180.0);
		up.y = cos((M_PI*x)/180.0);
		up.z = cos((M_PI*y)/180.0)*sin((M_PI*x)/180.0);
		Hu3DCameraPosSet(lbl_1_data_58[i], pos.x, pos.y, pos.z, up.x, up.y, up.z, target.x, target.y, target.z);
	}
}

void fn_1_152C(void)
{
	
}

void fn_1_2100(void)
{
	s16 model;
	s16 sprite;
	AnimData *sprite_data;
	lbl_1_bss_8[0] = model = Hu3DModelCreateFile(MAKE_DATA_NUM(DATADIR_TITLE, 11));
	Hu3DModelAttrSet(model, 1);
	Hu3DModelAttrSet(model, 0x40000001);
	lbl_1_bss_8[1] = model = Hu3DModelCreateFile(MAKE_DATA_NUM(DATADIR_TITLE, 12));
	Hu3DModelAttrSet(model, 1);
	Hu3DModelAttrSet(model, 0x40000001);
	lbl_1_bss_8[2] = model = Hu3DModelCreateFile(MAKE_DATA_NUM(DATADIR_TITLE, 13));
	Hu3DModelAttrSet(model, 1);
	Hu3DModelAttrSet(model, 0x40000001);
	Hu3DModelCameraInfoSet(model, 1);
	Hu3DModelLightInfoSet(model, 1);
	lbl_1_bss_6 = HuSprGrpCreate(4);
	sprite_data = HuSprAnimReadFile(MAKE_DATA_NUM(DATADIR_TITLE, 8));
	sprite = HuSprCreate(sprite_data, 0, 0);
	HuSprGrpMemberSet(lbl_1_bss_6, 0, sprite);
	HuSprAttrSet(lbl_1_bss_6, 0, SPRITE_ATTR_HIDDEN);
	HuSprDrawNoSet(lbl_1_bss_6, 0, 127);
	HuSprPosSet(lbl_1_bss_6, 0, 288, 240);
	sprite_data = HuSprAnimReadFile(MAKE_DATA_NUM(DATADIR_TITLE, 10));
	sprite = HuSprCreate(sprite_data, 1, 0);
	HuSprGrpMemberSet(lbl_1_bss_6, 1, sprite);
	HuSprAttrSet(lbl_1_bss_6, 1, SPRITE_ATTR_HIDDEN);
	HuSprPosSet(lbl_1_bss_6, 1, 288, 420);
	sprite_data = HuSprAnimReadFile(MAKE_DATA_NUM(DATADIR_TITLE, 2));
	sprite = HuSprCreate(sprite_data, 2, 0);
	HuSprGrpMemberSet(lbl_1_bss_6, 2, sprite);
	HuSprAttrSet(lbl_1_bss_6, 2, SPRITE_ATTR_HIDDEN|SPIRTE_ATTR_BILINEAR);
	HuSprPosSet(lbl_1_bss_6, 2, 288, 380);
	sprite_data = HuSprAnimReadFile(MAKE_DATA_NUM(DATADIR_TITLE, 9));
	sprite = HuSprCreate(sprite_data, 0, 0);
	HuSprGrpMemberSet(lbl_1_bss_6, 3, sprite);
	HuSprAttrSet(lbl_1_bss_6, 3, SPRITE_ATTR_HIDDEN|SPIRTE_ATTR_BILINEAR);
	HuSprPosSet(lbl_1_bss_6, 3, 288, 200);
}

BOOL fn_1_2474(void)
{
	
}