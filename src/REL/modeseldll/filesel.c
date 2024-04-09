#include "game/gamework_data.h"
#include "game/process.h"
#include "game/window.h"
#include "game/wipe.h"
#include "game/audio.h"
#include "game/gamework.h"
#include "game/saveload.h"
#include "game/card.h"
#include "game/hsfman.h"
#include "game/pad.h"

#include "math.h"

#include "REL/modeseldll.h"


s16 lbl_1_data_100 = -1;
float lbl_1_data_104[] = {
	-55, 0, 0, 0, 60, -57, 806, -71,
	0, 0, 0, 100, -131, 900, -87, 0,
	0, 0, 46, -117, 566, -87, 0, 0,
	0, 46, -117, 566, -90, 0, 0, -22,
	39, -153, 432, -40, 0, 0, 0, 130,
	-186, 6530, -23, 0, 0, -9, 1,
	-70, 1318, -25, 0, 0, 0, 242, 90,
	343, -30, 0, 0, 0, 223, -60, 505,
	-23, 0, 0, 0, 65, -97, 1318
};

s32 lbl_1_data_21C[] = {
	0x63000D,
	0x63000E,
	0x63000F,
	0x630010,
	0x630011,
	0x630012,
	0x630013,
	0x630014,
	0x630015,
	0x630016,
	0x630017,
	0x630018,
	0x630019,
	0x63001A,
	0x63001B,
	0x63001C,
	0x63001D,
	0x63001E,
};


char *lbl_1_data_26C[] = {
	"\x0E\x16",
	"\x0E\x17"
};

char *lbl_1_data_278[] = {
	"A",
	"B"
};

char *lbl_1_data_288[] = {
	"1",
	"2",
	"3"
};

s32 lbl_1_bss_14C;
s16 lbl_1_bss_148;
s16 lbl_1_bss_146;
s16 lbl_1_bss_140[3];
s16 lbl_1_bss_13A[3];
s16 lbl_1_bss_134[3];
s32 lbl_1_bss_12C[2];
s32 lbl_1_bss_120[3];
s16 lbl_1_bss_11C;
s16 lbl_1_bss_116[3];
s16 lbl_1_bss_110[3];
float lbl_1_bss_108[2];
float lbl_1_bss_100[2];
AnimData *lbl_1_bss_FC;
AnimData *lbl_1_bss_F8;
AnimData *lbl_1_bss_F4;
s16 lbl_1_bss_EE[3];
s16 lbl_1_bss_E8[3];
OSTime lbl_1_bss_D0[3];
s32 lbl_1_bss_C4[3];
s32 lbl_1_bss_B8[3];
s32 lbl_1_bss_AC[3];
s16 lbl_1_bss_A4[3];
s16 lbl_1_bss_9E[3];
s16 lbl_1_bss_98[3];
s16 lbl_1_bss_92[3];
s16 lbl_1_bss_90;
float lbl_1_bss_8C;
s16 lbl_1_bss_88;

s32 fn_1_3AAC(void);
void fn_1_5D30(void);
s32 fn_1_61B4(void);
void fn_1_AAB8(void);

s32 fn_1_37DC(void)
{
	s16 i;
	s16 result;
	WindowData *window;
	s16 fxstat;
	Process *process = HuPrcCurrentGet();
	Process *child;
	float winSize[2];
	for(i=0; i<3; i++) {
		lbl_1_bss_13A[i] = lbl_1_bss_134[i] = -1;
		lbl_1_bss_116[i] = -1;
		lbl_1_bss_110[i] = -1;
	}
	lbl_1_bss_FC = lbl_1_bss_F8 = lbl_1_bss_F4 = NULL;
	curSlotNo = 0;
	fn_1_1EC0(0);
	fn_1_5D30();
	child = HuPrcChildCreate(fn_1_AAB8, 10, 8192, 0, process);
	winSize[0] = 457;
	winSize[1] = 94;
	lbl_1_bss_148 = HuWinExCreateStyled(-10000, 448-winSize[1], winSize[0], winSize[1], -1, 0);
	window = &winData[lbl_1_bss_148];
	window->active_pad = 1;
	HuWinPushKeySet(lbl_1_bss_148, 0x300);
	HuWinMesSpeedSet(lbl_1_bss_148, 0);
	HuWinDispOn(lbl_1_bss_148);
	fxstat = HuAudFXPlay(2098);
	lbl_1_data_100 = fxstat;
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	HuAudSeqPlay(43);
	while(1) {
		result = fn_1_3AAC();
		if(!result) {
			break;
		}
		if(!SLSaveFlagGet()) {
			GWGameStatReset();
			GWGameStat.sound_mode = msmSysGetOutputMode();
			result = 1;
			break;
		} else {
			if(fn_1_61B4()) {
				break;
			}
		}
	}
	if(result == 0) {
		HuAudFXStop(fxstat);
	}
	HuWinExAnimOut(lbl_1_bss_148);
	HuWinExCleanup(lbl_1_bss_148);
	HuPrcKill(child);
	HuCardUnMount(0);
	HuCardUnMount(1);
	return result;
}

#define GET_ZEROSIGN(x) (((x) == 0) ? (-1) : (1))

s32 fn_1_562C(void);
void fn_1_57C8(s16 arg0);
void fn_1_5BAC(s16 arg0, s32 arg1);
s32 fn_1_5C38(void);
void fn_1_B8CC(u32 arg0);
void fn_1_BA20(void);

//Various temporary register errors
//Scratch: https://decomp.me/scratch/BDhfa
s32 fn_1_3AAC(void)
{
	s16 temp_r31;
	s16 temp_r30;
	s32 temp_r29;
	s32 temp_r28;
	s16 temp_r27;
	s16 temp_r26;
	s16 temp_r25;
	s16 temp_r24;
	WindowData *temp_r23;
	float temp_f31;
	CARDFileInfo sp34;
	Vec sp28;
	Vec sp1C;
	Vec sp10;
	float sp8[2];
	
	fn_1_1EC0(0);
	temp_r23 = &winData[lbl_1_bss_148];
	HuWinMesMaxSizeGet(1, sp8, 0x10000C);
	lbl_1_bss_146 = HuWinExCreateStyled(-10000.0f, 316.0f, sp8[0], sp8[1], -1, 0);
	HuWinBGTPLvlSet(lbl_1_bss_146, 0);
	HuWinMesSpeedSet(lbl_1_bss_146, 0);
    while (1) {
    	repeat:
    	sp28.x = 188;
    	sp28.y = 250;
    	sp28.z = 600;
    	Hu3D2Dto3D(&sp28, 1, &sp1C);
    	Hu3DModelPosSetV(lbl_1_bss_19A[2], &sp1C);
    	Hu3DModelPosSetV(lbl_1_bss_19A[4], &sp1C);
    	Hu3DModelPosSetV(lbl_1_bss_19A[0], &sp1C);
    	sp28.x = 388;
    	Hu3D2Dto3D(&sp28, 1, &sp1C);
    	Hu3DModelPosSetV(lbl_1_bss_19A[3], &sp1C);
    	Hu3DModelPosSetV(lbl_1_bss_19A[5], &sp1C);
    	Hu3DModelPosSetV(lbl_1_bss_19A[1], &sp1C);
    	Hu3DModelAttrReset(lbl_1_bss_19A[2], 1);
    	Hu3DModelAttrSet(lbl_1_bss_19A[4], 1);
    	Hu3DModelAttrReset(lbl_1_bss_19A[3], 1);
    	Hu3DModelAttrSet(lbl_1_bss_19A[5], 1);
    	Hu3DModelRotSet(lbl_1_bss_19A[2], 0, 0, 0);
    	Hu3DModelRotSet(lbl_1_bss_19A[3], 0, 0, 0);
    	fn_1_57C8(lbl_1_bss_19A[4]);
    	fn_1_57C8(lbl_1_bss_19A[5]);
    	lbl_1_bss_12C[0] = lbl_1_bss_12C[1] = 1;
    	lbl_1_bss_108[0] = lbl_1_bss_108[1] = lbl_1_bss_100[0] = lbl_1_bss_100[1] = 1.0f;
    	lbl_1_bss_11C = -1;
    	fn_1_5C38();
    	for(temp_r30=0; temp_r30<=20; temp_r30++) {
    		temp_f31 = temp_r30/20.0;
    		temp_f31 = sin(M_PI*(90.0f*temp_f31)/180.0);
    		Hu3DModelScaleSet(lbl_1_bss_19A[0], temp_f31, temp_f31, temp_f31);
    		Hu3DModelScaleSet(lbl_1_bss_19A[1], temp_f31, temp_f31, temp_f31);
    		Hu3DModelScaleSet(lbl_1_bss_19A[2], temp_f31, temp_f31, temp_f31);
    		Hu3DModelScaleSet(lbl_1_bss_19A[3], temp_f31, temp_f31, temp_f31);
    		Hu3DModelScaleSet(lbl_1_bss_19A[4], temp_f31, temp_f31, temp_f31);
    		Hu3DModelScaleSet(lbl_1_bss_19A[5], temp_f31, temp_f31, temp_f31);
    		HuPrcVSleep();
    	}
    	while(1) {
    		repeat_loop:
    		HuWinDispOff(lbl_1_bss_146);
    		temp_r28 = fn_1_562C();
    		if(temp_r28 == 0 && fn_1_5C38() == 0) {
    			if(fn_1_5C38() == 0) {
    				HuWinMesSet(lbl_1_bss_148, 0x100002);
    				HuWinMesWait(lbl_1_bss_148);
    			}
    			HuWinMesSet(lbl_1_bss_148, 0x10004F);
    			HuWinAttrSet(lbl_1_bss_148, 0x10);
    			HuWinMesWait(lbl_1_bss_148);
    			temp_r27 = HuWinChoiceGet(lbl_1_bss_148, 1);
    			if(temp_r27 == 0) {
    				SLSaveFlagSet(0);
    				temp_r29 = 1;
    				goto cleanup;
    			}
    			HuWinInsertMesSet(lbl_1_bss_148, 0x100052, 0);
    			HuWinMesSet(lbl_1_bss_148, 0x10004C);
    			HuWinMesWait(lbl_1_bss_148);
    			while(!(HuPadBtnDown[0] & PAD_BUTTON_A)) {
    				HuPrcVSleep();
    			}
    		}
    		while(!fn_1_5C38()) {
    			temp_r28 = fn_1_562C();
    			HuWinMesSet(lbl_1_bss_148, 0x100002);
    			HuWinMesWait(lbl_1_bss_148);
    			if(temp_r23->key_down & PAD_BUTTON_B) {
    				HuAudFXPlay(3);
    				return 0;
    			}
    			if(fn_1_5C38()) {
    				break;
    			}
    			HuWinMesSet(lbl_1_bss_148, 0x10004B);
    			HuWinAttrSet(lbl_1_bss_148, 0x10);
    			HuWinMesWait(lbl_1_bss_148);
    			temp_r27 = HuWinChoiceGet(lbl_1_bss_148, 1);
    			if(temp_r27 == 0) {
    				SLSaveFlagSet(0);
    				temp_r29 = 1;
    				goto cleanup;
    			}
    			HuWinInsertMesSet(lbl_1_bss_148, 0x100052, 0);
    			HuWinMesSet(lbl_1_bss_148, 0x10004C);
    			HuWinMesWait(lbl_1_bss_148);
    			while(!(HuPadBtnDown[0] & PAD_BUTTON_A)) {
    				HuPrcVSleep();
    			}
    		}
    		SLSaveFlagSet(1);
    		HuWinMesSet(lbl_1_bss_148, 0x100001);
    		HuWinMesWait(lbl_1_bss_148);
    		HuWinMesSet(lbl_1_bss_146, 0x10000C);
    		HuWinDispOn(lbl_1_bss_146);
    		if(curSlotNo == 0) {
    			if(lbl_1_bss_14C & 0x1) {
    				temp_r31 = 0;
    			} else {
    				temp_r31 = 1;
    			}
    		} else {
    			if(lbl_1_bss_14C & 0x2) {
    				temp_r31 = 1;
    			} else {
    				temp_r31 = 0;
    			}
    		}
    		fn_1_5BAC(temp_r31, 1);
    		HuPrcSleep(10);
    		temp_r24 = temp_r31;
    		while(1) {
    			if(!fn_1_5C38()) {
    				fn_1_5BAC(temp_r31, 0);
    				HuPrcSleep(10);
    				goto repeat_loop;
    			} else {
    				if((HuPadDStkRep[0] & 0x1) && (lbl_1_bss_14C & 0x1)) {
    					temp_r31 = 0;
    				} else if((HuPadDStkRep[0] & 0x2) && (lbl_1_bss_14C & 0x2)) {
    					temp_r31 = 1;
    				} else if(!(lbl_1_bss_14C & (1 << temp_r31))) {
    					if(!(lbl_1_bss_14C & (1 << ((temp_r31+1) & 0x1)))) {
    						fn_1_5BAC(temp_r31, 0);
    						HuPrcSleep(10);
    						goto repeat_loop;
    					} else {
    						temp_r31 = (temp_r31+1) & 0x1;
    					}
    				}
    				if(temp_r24 != temp_r31) {
    					HuAudFXPlay(0);
    					fn_1_5BAC(temp_r31, 1);
    					fn_1_5BAC((temp_r31+1) & 0x1, 0);
    					HuPrcSleep(10);
    					temp_r24 = temp_r31;
    				}
    				if(HuPadBtnDown[0] & PAD_BUTTON_A) {
    					HuAudFXPlay(2096);
    					goto loop_exit;
    				} else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
    					HuAudFXPlay(3);
    					return 0;
    				}
    			}
    			HuPrcVSleep();
    		}
    	}
    	loop_exit:
    	HuWinHomeClear(lbl_1_bss_148);
    	temp_r26 = (temp_r31+1)&0x1;
    	Hu3DMotionSet(lbl_1_bss_19A[temp_r31+4], lbl_1_bss_16A[7]);
    	Hu3DMotionSpeedSet(lbl_1_bss_19A[temp_r31+4], 2.0f);
    	lbl_1_bss_12C[0] = lbl_1_bss_12C[1] = 0;
    	lbl_1_bss_11C = temp_r31;
    	SLCurSlotNoSet(temp_r31);
    	temp_r28 = HuCardMount(temp_r31);
    	if(temp_r28 == 0) {
    		SLSerialNoGet();
    		temp_r28 = HuCardOpen(temp_r31, SaveFileNameTbl[0], &sp34);
    		if(temp_r28 != 0 && temp_r28 != -4) {
    			temp_r29 = 1;
    		} else {
    			temp_r29 = 0;
    		}
    		HuCardClose(&sp34);
            break;
    	} else {
    		if(temp_r28 != -3) {
    			temp_r29 = 1;
                break;
    		}
    	}
    }
	temp_r27 = HuCardSectorSizeGet(curSlotNo);
	if(temp_r27 > 0 && temp_r27 != 8192) {
		HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
		HuWinMesSet(lbl_1_bss_148, 0x100039);
		HuWinMesWait(lbl_1_bss_148);
		temp_r29 = 1;
		goto skip_check;
	} else {
		if(temp_r27 == -128) {
			HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
			HuWinMesSet(lbl_1_bss_148, 0x100053);
			HuWinMesWait(lbl_1_bss_148);
			temp_r29 = 1;
			goto skip_check;
		} else {
			lbl_1_bss_8C += 720.0f;
			for(temp_r30=0; temp_r30 <= 40; temp_r30++) {
				if(temp_r30 <= 30) {
					temp_f31 = temp_r30/30.0f;
					sp28.x = 288.0+(GET_ZEROSIGN(temp_r26)*(100.0+(250.0*sin(M_PI*(90.0f*temp_f31)/180.0))));
					sp28.y = 250.0-(100.0*sin(M_PI*(180.0f*temp_f31)/180.0));
					sp28.z = (temp_r30*100)+600;
					Hu3D2Dto3D(&sp28, 1, &sp1C);
					Hu3DModelPosSetV(lbl_1_bss_19A[temp_r26+2], &sp1C);
					Hu3DModelPosSetV(lbl_1_bss_19A[temp_r26], &sp1C);
					Hu3DModelRotSet(lbl_1_bss_19A[temp_r26+2], temp_r30*20, temp_r30*10, 0);
				}
				
				if(temp_r30 > 20) {
					temp_f31 = (temp_r30-20)/20.0f;
					if(temp_r29) {
						sp28.x = 288.0f+((1.0-temp_f31)*(100*GET_ZEROSIGN(temp_r31)));
						sp28.y = 250.0-(100.0*sin(M_PI*(180.0f*temp_f31)/180.0));
						sp28.z = 600.0f;
						Hu3D2Dto3D(&sp28, 1, &sp1C);
						Hu3DModelPosSetV(lbl_1_bss_19A[temp_r31], &sp1C);
						temp_f31 = (0.5*sin(M_PI*(90.0f*temp_f31)/180.0))+1.0;
						Hu3DModelScaleSet(lbl_1_bss_19A[temp_r31], temp_f31, temp_f31, temp_f31);
					} else {
						sp28.x = 288.0f+(100*GET_ZEROSIGN(temp_r31));
						sp28.y = 250;
						sp28.z = 600;
						Hu3D2Dto3D(&sp28, 1, &sp1C);
						sp28.x = 60;
						sp28.y = 90;
						sp28.z = 600;
						Hu3D2Dto3D(&sp28, 1, &sp10);
						VECSubtract(&sp10, &sp1C, &sp28);
						sp28.x *= sin(M_PI*(90.0f*temp_f31)/180.0);
						sp28.y *= 1.0-cos(M_PI*(90.0f*temp_f31)/180.0);
						sp28.z = 0;
						VECAdd(&sp28, &sp1C, &sp1C);
						Hu3DModelPosSetV(lbl_1_bss_19A[temp_r31], &sp1C);
						lbl_1_bss_108[temp_r31] *= cos(M_PI*(90.0f*temp_f31)/180.0);
						lbl_1_bss_100[temp_r31] = 1.0-temp_f31;
						temp_f31 = 1.0+(0.3*sin(M_PI*(180.0f*temp_f31)/180.0));
						Hu3DModelScaleSet(lbl_1_bss_19A[temp_r31], temp_f31, temp_f31, temp_f31);
					}
				}
				HuPrcVSleep();
			}
			if(temp_r29 == 0) {
				HuWinKill(lbl_1_bss_146);
				return 1;
			}
			HuWinDispOff(lbl_1_bss_146);
			temp_r29 = 0;
			if(temp_r28 == -2) {
				HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[temp_r31]), 0);
				HuWinMesSet(lbl_1_bss_148, 0x100037);
				HuWinMesWait(lbl_1_bss_148);
				temp_r29 = 1;
			} else if(temp_r28 == -128) {
				HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[temp_r31]), 0);
				HuWinMesSet(lbl_1_bss_148, 0x100053);
				HuWinMesWait(lbl_1_bss_148);
				temp_r29 = 1;
			} else if(temp_r28 == -3) {
				HuWinMesSet(lbl_1_bss_148, 0x100002);
				HuWinMesWait(lbl_1_bss_148);
				temp_r29 = 1;
			} else if(temp_r28 == -6) {
				UnMountCnt = 0;
				HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[temp_r31]), 0);
				HuWinAttrSet(lbl_1_bss_148, 0x10);
				HuWinMesSet(lbl_1_bss_148, 0x100004);
				HuWinMesWait(lbl_1_bss_148);
				temp_r25 = HuWinChoiceGet(lbl_1_bss_148, 1);
				if(temp_r25 == 0) {
					HuWinMesSet(lbl_1_bss_148, 0x10004E);
					HuWinMesWait(lbl_1_bss_148);
					temp_r25 = HuWinChoiceGet(lbl_1_bss_148, 1);
					if(temp_r25 == 0) {
						fn_1_B8CC(0x100038);
						HuWinMesSet(lbl_1_bss_148, 0x10000B);
						HuWinMesWait(lbl_1_bss_148);
						HuPrcSleep(60);
						if(UnMountCnt & (1 << temp_r31)) {
							fn_1_BA20();
							HuWinMesSet(lbl_1_bss_148, 0x100050);
							HuWinMesWait(lbl_1_bss_148);
							temp_r29 = 1;
							goto cleanup;
						} else {
							_SetFlag(0x30000);
							temp_r28 = HuCardFormat(temp_r31);
							_ClearFlag(0x30000);
							if(temp_r28 == 0) {
								SLSerialNoGet();
							}
							fn_1_BA20();
							if(temp_r28 == -128) {
								HuWinMesSet(lbl_1_bss_148, 0x100036);
								HuWinMesWait(lbl_1_bss_148);
								HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
								HuWinMesSet(lbl_1_bss_148, 0x100053);
								HuWinMesWait(lbl_1_bss_148);
								temp_r29 = 1;
							} else if(temp_r28 == -3) {
								HuWinMesSet(lbl_1_bss_148, 0x100002);
								HuWinMesWait(lbl_1_bss_148);
								temp_r29 = 1;
							}
						}
					} else {
						temp_r29 = 1;
					}
				} else {
					temp_r29 = 1;
				}
			}
		}
	}
	if(temp_r29 == 0) {
		goto cleanup;
	}
	skip_check:
	HuWinMesSet(lbl_1_bss_148, 0x10004F);
	HuWinAttrSet(lbl_1_bss_148, 0x10);
	HuWinMesWait(lbl_1_bss_148);
	temp_r27 = HuWinChoiceGet(lbl_1_bss_148, 1);
	if(temp_r27 == 0) {
		SLSaveFlagSet(0);
		goto cleanup;
	} else {
		HuWinInsertMesSet(lbl_1_bss_148, 0x100052, 0);
		HuWinMesSet(lbl_1_bss_148, 0x10004C);
		HuWinMesWait(lbl_1_bss_148);
		while(!(HuPadBtnDown[0] & PAD_BUTTON_A)) {
			HuPrcVSleep();
		}
	}
	cleanup:
	HuWinDispOff(lbl_1_bss_146);
	lbl_1_bss_8C += 720.0f;
	for(temp_r30=0; temp_r30<=20; temp_r30++) {
		temp_f31 = temp_r30/20.0f;
		if(temp_r29) {
			temp_f31 = 1.5*cos(M_PI*(90.0f*temp_f31)/180.0);
			Hu3DModelScaleSet(lbl_1_bss_19A[0], temp_f31, temp_f31, temp_f31);
			Hu3DModelScaleSet(lbl_1_bss_19A[1], temp_f31, temp_f31, temp_f31);
			Hu3DModelScaleSet(lbl_1_bss_19A[2], 0.7*temp_f31, 0.7*temp_f31, 0.7*temp_f31);
			Hu3DModelScaleSet(lbl_1_bss_19A[3], 0.7*temp_f31, 0.7*temp_f31, 0.7*temp_f31);
			if(!SLSaveFlagGet()) {
				espScaleSet(lbl_1_bss_152[1], temp_f31, temp_f31);
			}
		} else {
			sp28.x = 288;
			sp28.y = 250;
			sp28.z = 600;
			Hu3D2Dto3D(&sp28, 1, &sp1C);
			sp28.x = 60;
			sp28.y = 90;
			sp28.z = 600;
			Hu3D2Dto3D(&sp28, 1, &sp10);
			VECSubtract(&sp10, &sp1C, &sp28);
			sp28.x *= sin(M_PI*(90.0f*temp_f31)/180.0);
			sp28.y *= 1.0-cos(M_PI*(90.0f*temp_f31)/180.0);
			sp28.z = 0.0f;
			VECAdd(&sp28, &sp1C, &sp1C);
			Hu3DModelPosSetV(lbl_1_bss_19A[temp_r31], &sp1C);
			lbl_1_bss_108[temp_r31] *= cos(M_PI*(90.0f*temp_f31)/180.0);
			lbl_1_bss_100[temp_r31] = 1.0-temp_f31;
			temp_f31 = 1.0+(0.3*cos(M_PI*(180.0f*temp_f31)/180.0));
			Hu3DModelScaleSet(lbl_1_bss_19A[temp_r31], temp_f31, temp_f31, temp_f31);
		}
		HuPrcVSleep();
	}
	if(temp_r29 && SLSaveFlagGet()) {
		goto repeat;
	}
	HuWinKill(lbl_1_bss_146);
	return 1;
}

s32 fn_1_562C(void)
{
	s16 i;
	s16 result;
	s16 ret;
	ret = 1;
	for(i=0; i<2; i++) {
		result = HuCardSlotCheck((s32)i);
		if(result == -2) {
			HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[i]), 0);
			HuWinMesSet(lbl_1_bss_148, 0x100037);
			HuWinMesWait(lbl_1_bss_148);
			ret = 0;
		} else if(result > 0 && result != 8192) {
			HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[i]), 0);
			HuWinMesSet(lbl_1_bss_148, 0x100039);
			HuWinMesWait(lbl_1_bss_148);
			ret = 0;
		} else if(result == -128) {
			HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[i]), 0);
			HuWinMesSet(lbl_1_bss_148, 0x100053);
			HuWinMesWait(lbl_1_bss_148);
			ret = 0;
		}
	}
	return ret;
}

void fn_1_57C8(s16 arg0)
{
	ModelData *model = &Hu3DData[arg0];
	HsfData *hsf = model->hsfData;
	HsfMaterial *mat = hsf->material;
	s16 i;
	for(i=0; i<hsf->materialCnt; i++, mat++) {
		mat->invAlpha = 0.0f;
		mat->pass &= 0xF0;
	}
}

typedef struct work_filesel {
	s16 slot;
	s32 param;
} WorkFilesel;

void fn_1_5850(void)
{
	s16 slot;
	WorkFilesel *work;
	s16 i;
	s32 param;
	Process *curr;
	curr = HuPrcCurrentGet();
	work = curr->user_data;
	slot = work->slot;
	param = work->param;
	Hu3DModelAttrSet(lbl_1_bss_19A[slot+2], 1);
	Hu3DModelAttrReset(lbl_1_bss_19A[slot+4], 1);
	Hu3DMotionSet(lbl_1_bss_19A[slot+4], lbl_1_bss_16A[6]);
	Hu3DMotionSpeedSet(lbl_1_bss_19A[slot+4], 2.0f);
	if(param) {
		Hu3DModelAttrReset(lbl_1_bss_19A[slot+4], 0x40000004);
	} else {
		Hu3DModelAttrSet(lbl_1_bss_19A[slot+4], 0x40000004);
		Hu3DMotionTimeSet(lbl_1_bss_19A[slot+4], Hu3DMotionMaxTimeGet(lbl_1_bss_19A[6]));
	}
	for(i=0; i<10; i++) {
		float scale;
		float time = i/10.0;
		if(param) {
			scale = 1.0+(0.3*sin(M_PI*(90.0f*time)/180.0));
		} else {
			scale = 1.0+(0.3*cos(M_PI*(90.0f*time)/180.0));
		}
		Hu3DModelScaleSet(lbl_1_bss_19A[slot+2], scale, scale, scale);
		Hu3DModelScaleSet(lbl_1_bss_19A[slot+4], scale, scale, scale);
		Hu3DModelScaleSet(lbl_1_bss_19A[slot], scale, scale, scale);
		HuPrcVSleep();
	}
	if(!param) {
		Hu3DModelAttrReset(lbl_1_bss_19A[slot+2], 1);
		Hu3DModelAttrSet(lbl_1_bss_19A[slot+4], 1);
	}
	HuMemDirectFree(work);
	HuPrcEnd();
	
	while(1) {
		HuPrcVSleep();
	}
}

void fn_1_5BAC(s16 arg0, s32 arg1)
{
	WorkFilesel *work;
	Process *child;
	Process *parent;
	parent = HuPrcCurrentGet();
	child = HuPrcChildCreate(fn_1_5850, 50, 8192, 0, parent);
	work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WorkFilesel), MEMORY_DEFAULT_NUM);
	child->user_data = work;
	work->slot = arg0;
	work->param = arg1;
}

s32 fn_1_5C38(void)
{
	s32 result;
	lbl_1_bss_14C = 0;
	result = HuCardSlotCheck(0);
	if(result == 8192) {
		Hu3DModelAttrReset(lbl_1_bss_19A[0], 1);
		lbl_1_bss_14C |= 1;
	} else {
		Hu3DModelAttrSet(lbl_1_bss_19A[0], 1);
	}
	result = HuCardSlotCheck(1);
	if(result == 8192) {
		Hu3DModelAttrReset(lbl_1_bss_19A[1], 1);
		lbl_1_bss_14C |= 2;
	} else {
		Hu3DModelAttrSet(lbl_1_bss_19A[1], 1);
	}
	return lbl_1_bss_14C;
}

void fn_1_5D30(void)
{
	ModelData *model;
	Vec pos_2d;
	Vec pos_3d;
	Mtx scale;
	espAttrReset(lbl_1_bss_152[0], 4);
	espDrawNoSet(lbl_1_bss_152[0], 127);
	espAttrReset(lbl_1_bss_152[1], 4);
	Hu3DModelAttrReset(lbl_1_bss_19A[2], 1);
	pos_2d.x = 188;
	pos_2d.y = 250;
	pos_2d.z = 600;
	Hu3D2Dto3D(&pos_2d, 1, &pos_3d);
	Hu3DModelPosSetV(lbl_1_bss_19A[2], &pos_3d);
	Hu3DModelPosSetV(lbl_1_bss_19A[4], &pos_3d);
	Hu3DModelPosSetV(lbl_1_bss_19A[0], &pos_3d);
	MTXScale(scale, 0.5f, 0.5f, 0.5f);
	model = &Hu3DData[lbl_1_bss_19A[2]];
	MTXCopy(scale, model->unk_F0);
	model = &Hu3DData[lbl_1_bss_19A[4]];
	MTXCopy(scale, model->unk_F0);
	model = &Hu3DData[lbl_1_bss_19A[0]];
	MTXCopy(scale, model->unk_F0);
	Hu3DModelAttrReset(lbl_1_bss_19A[3], 1);
	pos_2d.x = 388;
	Hu3D2Dto3D(&pos_2d, 1, &pos_3d);
	Hu3DModelPosSetV(lbl_1_bss_19A[3], &pos_3d);
	Hu3DModelPosSetV(lbl_1_bss_19A[5], &pos_3d);
	Hu3DModelPosSetV(lbl_1_bss_19A[1], &pos_3d);
	model = &Hu3DData[lbl_1_bss_19A[3]];
	MTXCopy(scale, model->unk_F0);
	model = &Hu3DData[lbl_1_bss_19A[5]];
	MTXCopy(scale, model->unk_F0);
	model = &Hu3DData[lbl_1_bss_19A[1]];
	MTXCopy(scale, model->unk_F0);
	Hu3DModelScaleSet(lbl_1_bss_19A[0], 0, 0, 0);
	Hu3DModelScaleSet(lbl_1_bss_19A[1], 0, 0, 0);
	Hu3DModelScaleSet(lbl_1_bss_19A[2], 0, 0, 0);
	Hu3DModelScaleSet(lbl_1_bss_19A[3], 0, 0, 0);
	Hu3DModelScaleSet(lbl_1_bss_19A[4], 0, 0, 0);
	Hu3DModelScaleSet(lbl_1_bss_19A[5], 0, 0, 0);
	fn_1_5C38();
}

void fn_1_7628(s16 boxno, s32 flag);

s32 fn_1_76B4(char *name, s16 slotno);
s32 fn_1_7B74(s16 boxno);
s32 fn_1_83B4(void);
s32 fn_1_8540(s16 boxno);
s32 fn_1_8C30(s16 boxno);
s32 fn_1_9E14(void);
s32 fn_1_9E4C(void);

void fn_1_A8C0(s16 boxno);
void fn_1_BA80(s16 boxno);

s32 fn_1_61B4(void)
{
	float temp_f31;
	s16 temp_r31;
	s16 temp_r30;
	s16 temp_r29;
	s16 temp_r28;
	s32 temp_r27;
	s16 temp_r26;
	float sp10[2];
	OSTime sp8;
	HuWinMesMaxSizeGet(1, sp10, 0x10003D);
	lbl_1_bss_146 = HuWinExCreateStyled(-10000, 316, sp10[0], sp10[1], -1, 0);
	HuWinAttrSet(lbl_1_bss_146, 0x800);
	HuWinBGTPLvlSet(lbl_1_bss_146, 0);
	HuWinMesSpeedSet(lbl_1_bss_146, 0);
	temp_r30 = -1;
	for(temp_r29=lbl_1_bss_88=0; temp_r29<3; temp_r29++) {
		lbl_1_bss_EE[temp_r29] = -1;
		lbl_1_bss_E8[temp_r29] = -1;
		lbl_1_bss_140[temp_r29] = 0;
		temp_r27 = fn_1_76B4(SaveFileNameTbl[temp_r29], curSlotNo);
		if(temp_r27 == 0) {
			temp_r27 = fn_1_83B4();
			if(temp_r27 == 0) {
				lbl_1_bss_140[temp_r29] = 1;
				if(lbl_1_bss_88 == 0) {
					temp_r30 = temp_r29;
				}
				lbl_1_bss_88++;
				if(SLCheckSumCheck()) {
					fn_1_A8C0(temp_r29);
				}
			}
			fn_1_9E14();
		}
		if(temp_r27 != 0 && temp_r27 != -4) {
			HuWinKill(lbl_1_bss_146);
			return 0;
		}
	}
	fn_1_9E4C();
	if(temp_r30 == -1) {
		temp_r30 = 0;
	}
	lbl_1_bss_120[0] = lbl_1_bss_120[1] = lbl_1_bss_120[2] = 1;
	UnMountCnt = 0;
	for(temp_r29=0; temp_r29<=20; temp_r29++) {
		temp_f31 = sin(M_PI*(90.0f*(temp_r29/20.0f))/180.0);
		for(temp_r28=0; temp_r28<3; temp_r28++) {
			Hu3DModelScaleSet(lbl_1_bss_19A[temp_r28+8], temp_f31, temp_f31, temp_f31);
			Hu3DModelScaleSet(lbl_1_bss_19A[temp_r28+11], temp_f31, temp_f31, temp_f31);
		}
		HuPrcVSleep();
	}
	HuWinMesSet(lbl_1_bss_148, 0x100007);
	HuWinMesWait(lbl_1_bss_148);
	fn_1_7628(temp_r30, 1);
	if(lbl_1_bss_88 == 0) {
		HuWinMesSet(lbl_1_bss_146, 0x100040);
	} else {
		if(lbl_1_bss_88 == 3) {
			HuWinMesSet(lbl_1_bss_146, 0x10003F);
		} else {
			HuWinMesSet(lbl_1_bss_146, 0x10003D);
		}
	}
	HuWinDispOn(lbl_1_bss_146);
	fn_1_BA80(temp_r30);
	if(UnMountCnt & (1 << curSlotNo)) {
		HuWinMesSet(lbl_1_bss_148, 0x100050);
		HuWinMesWait(lbl_1_bss_148);
		temp_r31 = 0;
	} else {
		UnMountCnt = 0;
		while(1) {
			HuPrcVSleep();
			if(UnMountCnt & (1 << curSlotNo)) {
				HuWinMesSet(lbl_1_bss_148, 0x100050);
				HuWinMesWait(lbl_1_bss_148);
				temp_r31 = 0;
				break;
			}
			temp_r26 = 0;
			if(HuPadDStkRep[0] & 0x1) {
				temp_r26 = -1;
			} else if(HuPadDStkRep[0] & 0x2) {
				temp_r26 = 1;
			}
			if(temp_r26) {
				fn_1_7628(temp_r30, 0);
				temp_r30 += temp_r26;
				if(temp_r30 < 0) {
					temp_r30 = 2;
				} else if(temp_r30 >= 3) {
					temp_r30 = 0;
				}
				HuAudFXPlay(0);
				fn_1_7628(temp_r30, 1);
				fn_1_BA80(temp_r30);
				HuPrcSleep(10);
			}
			if((HuPadBtnDown[0] & PAD_BUTTON_X) && lbl_1_bss_140[temp_r30]) {
				UnMountCnt = 0;
				temp_r31 = fn_1_76B4(SaveFileNameTbl[temp_r30], curSlotNo);
				if(temp_r31 < 0) {
					temp_r31 = 0;
					break;
				}
				if(!lbl_1_bss_140[temp_r30]) {
					continue;
				}
				HuWinDispOff(lbl_1_bss_146);
				HuAudFXPlay(2);
				HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_288[temp_r30]), 1);
				HuWinAttrSet(lbl_1_bss_148, 0x10);
				HuWinMesSet(lbl_1_bss_148, 0x100008);
				HuWinMesWait(lbl_1_bss_148);
				temp_r31 = HuWinChoiceGet(lbl_1_bss_148, 1);
				if(temp_r31 == 0) {
					temp_r31 = fn_1_8540(temp_r30);
					if(temp_r31 == 0) {
						break;
					}
				}
				if(UnMountCnt & (1 << curSlotNo)) {
					continue;
				}
				HuWinMesSet(lbl_1_bss_148, 0x100007);
				HuWinMesWait(lbl_1_bss_148);
				if(lbl_1_bss_88 == 0) {
					HuWinMesSet(lbl_1_bss_146, 0x100040);
				} else if(lbl_1_bss_88 == 3) {
					HuWinMesSet(lbl_1_bss_146, 0x10003F);
				} else {
					HuWinMesSet(lbl_1_bss_146, 0x10003D);
				}
				HuWinDispOn(lbl_1_bss_146);
				fn_1_BA80(temp_r30);
				continue;
			} else if(HuPadBtnDown[0] & PAD_BUTTON_Y) {
				UnMountCnt = 0;
				if(HuCardSlotCheck(curSlotNo) < 0) {
					HuWinMesSet(lbl_1_bss_148, 0x100002);
					HuWinMesWait(lbl_1_bss_148);
					temp_r31 = 0;
					break;
				}
				if(!lbl_1_bss_140[temp_r30]) {
					continue;
				}
				for(temp_r29=0; temp_r29<3; temp_r29++) {
					if(!lbl_1_bss_140[temp_r29]) {
						break;
					}
				}
				if(temp_r29 == 3) {
					continue;
				}
				HuWinDispOff(lbl_1_bss_146);
				HuAudFXPlay(2);
				if(fn_1_8C30(temp_r30) == 0) {
					temp_r31 = 0;
					break;
				}
				if(UnMountCnt & (1 << curSlotNo)) {
					continue;
				}
				HuWinMesSet(lbl_1_bss_148, 0x100007);
				HuWinMesWait(lbl_1_bss_148);
				if(lbl_1_bss_88 == 0) {
					HuWinMesSet(lbl_1_bss_146, 0x100040);
				} else if(lbl_1_bss_88 == 3) {
					HuWinMesSet(lbl_1_bss_146, 0x10003F);
				} else {
					HuWinMesSet(lbl_1_bss_146, 0x10003D);
				}
				HuWinDispOn(lbl_1_bss_146);
				fn_1_BA80(temp_r30);
				continue;
			} else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
				UnMountCnt = 0;
				HuWinDispOff(lbl_1_bss_146);
				HuCardMount(curSlotNo);
				if(HuCardSlotCheck(curSlotNo) < 0) {
					HuAudFXPlay(4);
					HuWinMesSet(lbl_1_bss_148, 0x100002);
					HuWinMesWait(lbl_1_bss_148);
					temp_r31 = 0;
					break;
				}
				if(SLSerialNoCheck() == 0) {
					HuAudFXPlay(4);
					HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
					HuWinMesSet(lbl_1_bss_148, 0x100045);
					HuWinMesWait(lbl_1_bss_148);
					temp_r31 = 0;
					break;
				}
				HuAudFXPlay(2097);
				SLCurBoxNoSet(temp_r30);
				if(!lbl_1_bss_140[temp_r30]) {
					HuWinMesSet(lbl_1_bss_148, 0x10000B);
					HuWinMesWait(lbl_1_bss_148);
					sp8 = OSGetTime();
					SLSaveDataMake(1, &sp8);
					GWGameStatReset();
					GWGameStat.sound_mode = msmSysGetOutputMode();
					SLCommonSet();
					fn_1_B8CC(0x10003C);
					HuPrcSleep(20);
					if(UnMountCnt & (1 << curSlotNo)) {
						fn_1_BA20();
						HuWinMesSet(lbl_1_bss_148, 0x100050);
						HuWinMesWait(lbl_1_bss_148);
						temp_r31 = 0;
						break;
					}
					temp_r27 = fn_1_7B74(temp_r30);
					fn_1_BA20();
					if(temp_r27 != 0) {
						temp_r31 = 1;
						break;
					}
					HuWinMesSet(lbl_1_bss_148, 0x10004F);
					HuWinAttrSet(lbl_1_bss_148, 0x10);
					HuWinMesWait(lbl_1_bss_148);
					temp_r31 = HuWinChoiceGet(lbl_1_bss_148, 1);
					if(temp_r31 == 0) {
						SLSaveFlagSet(0);
						temp_r31 = 1;
						break;
					}
					HuWinInsertMesSet(lbl_1_bss_148, 0x100052, 0);
					HuWinMesSet(lbl_1_bss_148, 0x10004C);
					HuWinMesWait(lbl_1_bss_148);
					while(!(HuPadBtnDown[0] & PAD_BUTTON_A)) {
						HuPrcVSleep();
					}
					temp_r31 = 0;
					break;
				} else {
					if(!fn_1_76B4(SaveFileNameTbl[temp_r30], curSlotNo)) {
						if(!fn_1_83B4()) {
							if(SLCheckSumCheck()) {
								fn_1_9E14();
								SLLoadGameStat();
								temp_r31 = 1;
								break;
							}
							HuWinHomeClear(lbl_1_bss_148);
							HuPrcSleep(60);
							if(UnMountCnt & (1 << curSlotNo)) {
								HuWinMesSet(lbl_1_bss_148, 0x100050);
								HuWinMesWait(lbl_1_bss_148);
								temp_r31 = 0;
								break;
							}
							HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_288[temp_r30]), 0);
							HuWinAttrSet(lbl_1_bss_148, 0x10);
							HuWinMesSet(lbl_1_bss_148, 0x10003A);
							HuWinMesWait(lbl_1_bss_148);
							temp_r31 = HuWinChoiceGet(lbl_1_bss_148, 1);
							if(!temp_r31) {
								temp_r31 = fn_1_8540(temp_r30);
								if(temp_r31 == 0) {
									break;
								}
								if(HuCardMount(curSlotNo) < 0) {
									temp_r31 = 0;
									break;
								}
							}
						} else {
							temp_r31 = 0;
						}
					} else {
						temp_r31 = 0;
					}
					if(temp_r31 == 0) {
						break;
					}
					if(UnMountCnt & (1 << curSlotNo)) {
						continue;
					}
					HuWinMesSet(lbl_1_bss_148, 0x100007);
					HuWinMesWait(lbl_1_bss_148);
					if(lbl_1_bss_88 == 0) {
						HuWinMesSet(lbl_1_bss_146, 0x100040);
					} else if(lbl_1_bss_88 == 3) {
						HuWinMesSet(lbl_1_bss_146, 0x10003F);
					} else {
						HuWinMesSet(lbl_1_bss_146, 0x10003D);
					}
					HuWinDispOn(lbl_1_bss_146);
					fn_1_BA80(temp_r30);
					continue;
				}
			}  else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
				HuAudFXPlay(3);
				temp_r31 = 0;
				break;
			}
		}
	}
	HuWinDispOff(lbl_1_bss_146);
	for(temp_r29=0; temp_r29<=20; temp_r29++) {
		temp_f31 = cos(M_PI*(90.0*(temp_r29/20.0))/180.0);
		Hu3DModelScaleSet(lbl_1_bss_19A[curSlotNo], temp_f31, temp_f31, temp_f31);
		for(temp_r28=0; temp_r28<3; temp_r28++) {
			Hu3DModelScaleSet(lbl_1_bss_19A[temp_r28+8], temp_f31, temp_f31, temp_f31);
			Hu3DModelScaleSet(lbl_1_bss_19A[temp_r28+11], temp_f31, temp_f31, temp_f31);
		}
		if(temp_r31) {
			espScaleSet(lbl_1_bss_152[1], temp_f31, temp_f31);
		}
		HuPrcVSleep();
	}
	HuWinKill(lbl_1_bss_146);
	return temp_r31;
}