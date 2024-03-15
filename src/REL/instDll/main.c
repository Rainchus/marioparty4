#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"

#include "game/wipe.h"
#include "game/flag.h"
#include "game/minigame_seq.h"
#include "game/data.h"
#include "game/audio.h"
#include "game/window.h"
#include "game/sprite.h"
#include "math.h"

#include "rel_sqrt_consts.h"

void HuSprGrpDrawNoSet(s16 group, s32 draw_no);
static s16 lbl_1_data_0 = 1;

static omObjData *lbl_1_bss_60;
static omObjData *lbl_1_bss_5C;
static Process *lbl_1_bss_58;
static Vec lbl_1_bss_40[2];
static Vec lbl_1_bss_28[2];
static float lbl_1_bss_20[2];
static s32 lbl_1_bss_1C;
static AnimData *lbl_1_bss_18;
static u16 lbl_1_bss_14;
static u16 lbl_1_bss_12;
static u16 lbl_1_bss_10;
static float lbl_1_bss_C;
static u8 lbl_1_bss_8;
static u16 lbl_1_bss_6;
static u16 lbl_1_bss_4;
static s32 lbl_1_bss_0;

static void fn_1_994(void);
static void fn_1_17E4(void);
static void fn_1_220C(void);
static void fn_1_2804(void);
static void fn_1_2FA0(void);
static void fn_1_4174(omObjData *object);
static void fn_1_4528(omObjData *object);

void ModuleProlog(void)
{
	s32 i;
	omOvlHisData *his;
	s32 light;
	OSReport("******* INST ObjectSetup *********\n");
	lbl_1_bss_58 = omInitObjMan(50, 8192);
	omGameSysInit(lbl_1_bss_58);
	lbl_1_bss_8 = GWLanguageGet();
	lbl_1_bss_14 = GWSystem.mg_next;
	lbl_1_bss_10 = 0;
	lbl_1_bss_4 = 0;
	_ClearFlag(0x1000C);
	for(i=0; HuSndGrpTbl[i].ovl != OVL_INVALID; i++) {
		if(HuSndGrpTbl[i].ovl == mgInfoTbl[lbl_1_bss_14].ovl) {
			break;
		}
	}
	if(HuSndGrpTbl[i].ovl != OVL_INVALID) {
		HuAudSndGrpSetSet(HuSndGrpTbl[i].grpset);
	}
	if(mgInfoTbl[lbl_1_bss_14].ovl == OVL_M411) {
		if(GWMGTypeGet() == -1) {
			GWMGTypeSet(frandmod(3)); 
		}
	} else {
		GWMGTypeSet(-1);
	}
	HuDataDirClose(mgInfoTbl[lbl_1_bss_14].data_dir);
	his = omOvlHisGet(0);
	omOvlHisChg(0, OVL_RESULT, his->event, his->stat);
	if(omovlevtno == 0 && mgInfoTbl[lbl_1_bss_14].ovl == OVL_M430) {
		s32 team_cnt[2];
		s32 team_players[2][2];
		team_cnt[0] = team_cnt[1] = 0;
		for(i=0; i<4; i++) {
			team_players[GWPlayerCfg[i].group][team_cnt[GWPlayerCfg[i].group]++] = i;
		}
		if(frand() & 1) {
			GWPlayerCfg[team_players[0][0]].group = 0;
			GWPlayerCfg[team_players[0][1]].group = 1;
		} else {
			GWPlayerCfg[team_players[0][0]].group = 1;
			GWPlayerCfg[team_players[0][1]].group = 0;
		}
		if(frand() & 1) {
			GWPlayerCfg[team_players[1][0]].group = 2;
			GWPlayerCfg[team_players[1][1]].group = 3;
		} else {
			GWPlayerCfg[team_players[1][0]].group = 3;
			GWPlayerCfg[team_players[1][1]].group = 2;
		}
	}
	if(mgInfoTbl[lbl_1_bss_14].type == 3
		|| mgInfoTbl[lbl_1_bss_14].type == 5
		|| mgInfoTbl[lbl_1_bss_14].type == 6
		|| mgInfoTbl[lbl_1_bss_14].type == 8
		|| !_CheckFlag(0xB)) {
			HuDataDirClose(DATADIR_INST);
			omSysPauseEnable(1);
			omOvlCallEx(mgInfoTbl[lbl_1_bss_14].ovl, 1, 0, 0);
			return;
		}
	lbl_1_bss_40[0].x = -67.0f;
	lbl_1_bss_40[0].y = 40.0f;
	lbl_1_bss_40[0].z = 0.0f;
	lbl_1_bss_28[0].x = 260.0f;
	lbl_1_bss_28[0].y = -103.0f;
	lbl_1_bss_28[0].z = -18.0f;
	lbl_1_bss_20[0] = 2885.0f;
	lbl_1_bss_C = 20.0f;
	lbl_1_bss_12 = GWSystem.board;
	if(mgBoardHostEnableF) {
		lbl_1_bss_12 = 1;
	}
	lbl_1_bss_40[1].x = lbl_1_bss_40[1].y = lbl_1_bss_40[1].z = 0.0f;
	lbl_1_bss_28[1].x = lbl_1_bss_28[1].y = lbl_1_bss_28[1].z = 0.0f;
	lbl_1_bss_20[1] = 1000.0f;
	omSysPauseEnable(0);
	Hu3DCameraCreate(3);
	Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 15000.0f, 1.2f);
	Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
	Hu3DCameraPerspectiveSet(2, 30.0f, 20.0f, 15000.0f, 1.2f);
	Hu3DCameraViewportSet(2, 0, 0, 640, 480, 0, 1);
	light = Hu3DGLightCreate(0, 100, 1000, 0, -0.5, -1, 255, 255, 255);
	Hu3DGLightInfinitytSet(light);
	HuPrcChildCreate(fn_1_994, 100, 12288, 0, lbl_1_bss_58);
	HuPrcChildCreate(fn_1_17E4, 100, 12288, 0, lbl_1_bss_58);
	HuPrcChildCreate(fn_1_220C, 100, 12288, 0, lbl_1_bss_58);
	HuPrcChildCreate(fn_1_2804, 100, 12288, 0, lbl_1_bss_58);
	HuPrcChildCreate(fn_1_2FA0, 100, 12288, 0, lbl_1_bss_58);
	lbl_1_bss_5C = omAddObjEx(lbl_1_bss_58, 32730, 0, 0, -1, fn_1_4174);
	omAddObjEx(lbl_1_bss_58, 0, 32, 32, -1, fn_1_4528);
	HuAudSeqPlay(59);
	Hu3DBGColorSet(0, 0, 0);
	HuWinInit(1);
}

static s8 lbl_1_data_26[][4] = {
	{ 3, 2, 1, 0 },
	{ 1, 1, 1, 0 },
	{ 1, 1, 0, 0 },
	{ 0, 1, 2, 3 },
	{ 3, 2, 1, 0 },
	{ 0, -1, -1, -1 },
	{ 0, -1, -1, -1 },
	{ 3, 2, 1, 0 },
};

static s8 lbl_1_data_46[] = {
	4,
	4,
	4,
	4,
	4,
	1,
	1,
	4
};

static s32 lbl_1_data_50[] = {
	DATA_MAKE_NUM(DATADIR_INST, 0),
	DATA_MAKE_NUM(DATADIR_INST, 1),
	DATA_MAKE_NUM(DATADIR_INST, 2),
	DATA_MAKE_NUM(DATADIR_INST, 3),
	DATA_MAKE_NUM(DATADIR_INST, 4),
	DATA_MAKE_NUM(DATADIR_INST, 0),
	DATA_MAKE_NUM(DATADIR_INST, 5),
	DATA_MAKE_NUM(DATADIR_INST, 0),
};

static s32 lbl_1_data_70[] = {
	DATA_MAKE_NUM(DATADIR_INST, 9),
	DATA_MAKE_NUM(DATADIR_INST, 10),
	DATA_MAKE_NUM(DATADIR_INST, 11),
	DATA_MAKE_NUM(DATADIR_INST, 12),
	DATA_MAKE_NUM(DATADIR_INST, 13),
	DATA_MAKE_NUM(DATADIR_INST, 14),
	DATA_MAKE_NUM(DATADIR_INST, 14),
	DATA_MAKE_NUM(DATADIR_INST, 9),
};

static void fn_1_50B0(ModelData *model, Mtx mtx);
static void fn_1_5B64(ModelData *model, Mtx mtx);

static void fn_1_994(void)
{
	
	Vec pos;
	Vec target;
	Vec up;
	
	Vec spC;
	Process *process;
	
	s16 i;
	s16 model;
	s16 num_coms;
	s16 j;
	s16 btns;
	s32 status;
	s32 done;
	s16 group;
	s32 pic;
	omOvlHisData *his;
	s16 sprite;
		AnimData *anim;
	float pos_z;
	float time;
	float fov_vel;
	float rot_x;
	
	
	process = HuPrcCurrentGet();
	status = -1;
	group = HuSprGrpCreate(1);
	anim = HuSprAnimRead(HuDataReadNum(lbl_1_data_70[mgInfoTbl[lbl_1_bss_14].type], MEMORY_DEFAULT_NUM));
	sprite = HuSprCreate(anim, 0, 0);
	HuSprGrpMemberSet(group, 0, sprite);
	HuSprGrpDrawNoSet(group, 127);
	HuSprPosSet(group, 0, 288, 240);
	if(GWMGTypeGet() == -1) {
		pic = mgInfoTbl[lbl_1_bss_14].inst_pic[0];
	} else {
		pic = mgInfoTbl[lbl_1_bss_14].inst_pic[GWMGTypeGet()];
	}
	lbl_1_bss_18 = HuSprAnimRead(HuDataReadNumHeapShortForce(pic, MEMORY_DEFAULT_NUM, HEAP_DATA));
	Hu3DShadowCreate(20, 500, 8000);
	Hu3DShadowTPLvlSet(0);
	Hu3DShadowSizeSet(192);
	target.x = target.y = target.z  = 0;
	pos.x = pos.z = 100.0f;
	pos.y = 7000.0f;
	up.x = up.y = 0.0f;
	up.z = 1.0f;
	Hu3DShadowPosSet(&pos, &up, &target);
	model = Hu3DModelCreateFile(lbl_1_data_50[mgInfoTbl[lbl_1_bss_14].type]);
	lbl_1_bss_1C = model;
	Hu3DModelPosSet(model, 0, 2000, 0);
	Hu3DModelAttrSet(model, 0x40000002);
	Hu3DModelCameraSet(model, 1);
	Hu3DModelShadowSet(model);
	i = Hu3DHookFuncCreate(fn_1_5B64);
	Hu3DModelPosSet(i, 0, -200, 0);
	Hu3DModelCameraSet(i, 1);
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	pos_z = -500.0f;
	for(i=0; i<=50; i++) {
		Hu3DModelPosSet(model, 0.0f, 2500.0*cos(M_PI*(i*1.8f)/180.0)-200.0, pos_z);
		Hu3DModelRotSet(model, 0, 0, 45.0f*(1.0f-(i/50.0f)));
		pos_z += 50.0/7.0;
		Hu3DShadowTPLvlSet(0.5*(i/50.0f));
		HuPrcVSleep();
	}
	HuAudFXPlay(1211);
	Hu3DModelAttrReset(model, 0x40000002);
	for(i=1; i<=20; i++) {
		Hu3DModelPosSet(model, 0.0f, (200.0*(sin(M_PI*(i*2.25f)/180.0)*(1.0/sin(M_PI/4))))-200.0, pos_z);
		rot_x = (20-i)*cos(M_PI*(i*13.5f)/180.0);
		Hu3DModelRotSet(model, rot_x, 0.0f, 0.0f);
		pos_z += 50.0/7.0;
		HuPrcVSleep();
	}
	Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
	Hu3DModelAttrSet(model, 0x40000002);
	HuPrcSleep(10);
	HuAudFXPlay(1212);
	Hu3DModelAttrReset(model, 0x40000002);
	i = Hu3DHookFuncCreate(fn_1_50B0);
	
	Hu3DModelCameraSet(i, 1);
	Hu3DModelPosSet(i, 0, 415, 0);
	lbl_1_data_0 = 0;
	while(Hu3DMotionTimeGet(model) < 80.0f) {
		if(Hu3DMotionTimeGet(model) > 30.0f) {
			lbl_1_data_0 = 2;
		}
		HuPrcVSleep();
	}
	Hu3DModelAttrSet(model, 0x40000002);
	HuDataDirClose(DATADIR_INST);
	status = HuDataDirReadAsync(mgInfoTbl[lbl_1_bss_14].data_dir);
	while(lbl_1_data_0 != 1) {
		HuPrcVSleep();
	}
	done = 0;
	for(i=num_coms=0; i<4; i++) {
		if(GWPlayerCfg[i].iscom) {
			num_coms++;
		}
	}
	i=0;
	while(1) {
		if(!done) {
			for(btns=j=0; j<4; j++) {
				if(!GWPlayerCfg[j].iscom) {
					btns |= HuPadBtnDown[GWPlayerCfg[j].pad_idx];
				}
			}
			if((btns == PAD_BUTTON_START) || omSysExitReq || (num_coms == 4 && i > 60)) {
				HuAudFXPlay(2);
				done = 1;
			}
			if(btns == PAD_TRIGGER_Z) {
				HuAudFXPlay(1);
				done = 1;
				his = omOvlHisGet(0);
				omOvlHisChg(0, OVL_INST, 1, his->stat);
				_SetFlag(0x1000C);
			}
			if(mgInstExitEnableF &&  (btns & PAD_BUTTON_B)) {
				HuAudFXPlay(3);
				if(status != -1) {
					while(!HuDataGetAsyncStat(status)) {
						HuPrcVSleep();
					}
				}
				WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
				HuAudSeqAllFadeOut(500);
				while(WipeStatGet()) {
					HuPrcVSleep();
				}
				HuDataDirClose(mgInfoTbl[lbl_1_bss_14].data_dir);
				if(mgInfoTbl[lbl_1_bss_14].ovl == OVL_M430) {
					for(num_coms=0; num_coms<4; num_coms++) {
						GWPlayerCfg[num_coms].group = GWPlayerCfg[num_coms].group/2;
					}
				}
				omOvlReturnEx(1, 1);
				HuPrcEnd();
				while(1) {
					HuPrcVSleep();
				}
			}
		}
		if(!lbl_1_bss_4 || !done) {
			HuPrcVSleep();
			i++;
			continue;
		} else {
			break;
		}
	}
	if(status != -1) {
		while(!HuDataGetAsyncStat(status)) {
			HuPrcVSleep();
		}
	}
	spC = lbl_1_bss_40[0];
	pos = lbl_1_bss_28[0];
	pos_z = lbl_1_bss_20[0];
	WipeColorSet(255, 255, 255);
	lbl_1_data_0 = 3;
	HuPrcSleep(20);
	lbl_1_data_0 = 4;
	HuPrcSleep(10);
	
	Hu3DModelAttrReset(model, 0x40000002);
	HuPrcSleep(10);
	fov_vel = 0;
	for(i=0; i<=60; i++) {
		time = i/60.0f;
		lbl_1_bss_40[0].x = spC.x+((-65.0f-spC.x)*time);
		lbl_1_bss_40[0].y = spC.y+((8.0f-spC.y)*time);
		lbl_1_bss_40[0].z = spC.z+(-spC.z)*time;
		lbl_1_bss_28[0].x = pos.x+((17.0f-pos.x)*time);
		lbl_1_bss_28[0].y = pos.y+((5.0f-pos.y)*time);
		lbl_1_bss_28[0].z = pos.z+((-188.0f-pos.z)*time);
		lbl_1_bss_20[0] = pos_z+((1173.0f-pos_z)*time);
		if(i == 30) {
			HuAudFXPlay(1210);
			WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
			HuAudSeqAllFadeOut(1000);
		}
		if(i == 40) {
			Hu3DModelAttrSet(model, 0x40000002);
		}
		if(i > 20) {
			lbl_1_bss_C += fov_vel;
			fov_vel += 0.04;
		}
		HuPrcVSleep();
	}
	while(WipeStatGet()) {
		lbl_1_bss_C += fov_vel;
		fov_vel += 0.04;
		HuPrcVSleep();
	}
	lbl_1_data_0 = 6;
	HuPrcVSleep();
	omSysPauseEnable(1);
	if(omSysExitReq) {
		HuDataDirClose(mgInfoTbl[lbl_1_bss_14].data_dir);
		omOvlReturnEx(1, 1);
	} else {
		omOvlCallEx(mgInfoTbl[lbl_1_bss_14].ovl, 1, 0, 0);
	}
	HuPrcEnd();
	while(1) {
		HuPrcVSleep();
	}
}