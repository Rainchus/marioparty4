#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/audio.h"
#include "game/board/window.h"
#include "game/board/ui.h"
#include "game/board/space.h"
#include "game/board/star.h"
#include "game/audio.h"
#include "game/objsub.h"
#include "game/pad.h"

#include "game/data.h"
#include "game/wipe.h"

static s16 stopWin = -1;
static s16 wheelMdl = -1;
s16 lbl_801D3854 = -1;
static s16 focusMdl = -1;
static s32 messBase = -1;

static s32 hostMotTbl[][8] = {
	{ 
		DATA_MAKE_NUM(DATADIR_BLAST5, 23),
		DATA_MAKE_NUM(DATADIR_BLAST5, 24),
		DATA_MAKE_NUM(DATADIR_BLAST5, 25),
		DATA_MAKE_NUM(DATADIR_BLAST5, 26),
		DATA_MAKE_NUM(DATADIR_BLAST5, 27),
		DATA_MAKE_NUM(DATADIR_BLAST5, 28),
		DATA_MAKE_NUM(DATADIR_BLAST5, 29),
		DATA_MAKE_NUM(DATADIR_BLAST5, 30)
	},
	{ 
		DATA_MAKE_NUM(DATADIR_BLAST5, 31),
		DATA_MAKE_NUM(DATADIR_BLAST5, 32),
		DATA_MAKE_NUM(DATADIR_BLAST5, 33),
		DATA_MAKE_NUM(DATADIR_BLAST5, 34),
		DATA_MAKE_NUM(DATADIR_BLAST5, 35),
		DATA_MAKE_NUM(DATADIR_BLAST5, 36),
		DATA_MAKE_NUM(DATADIR_BLAST5, 37),
		DATA_MAKE_NUM(DATADIR_BLAST5, 38)
	},
	{ 
		DATA_MAKE_NUM(DATADIR_BLAST5, 39),
		DATA_MAKE_NUM(DATADIR_BLAST5, 40),
		DATA_MAKE_NUM(DATADIR_BLAST5, 41),
		DATA_MAKE_NUM(DATADIR_BLAST5, 42),
		DATA_MAKE_NUM(DATADIR_BLAST5, 43),
		DATA_MAKE_NUM(DATADIR_BLAST5, 44),
		DATA_MAKE_NUM(DATADIR_BLAST5, 45),
		DATA_MAKE_NUM(DATADIR_BLAST5, 46)
	},
	{ 
		DATA_MAKE_NUM(DATADIR_BLAST5, 47),
		DATA_MAKE_NUM(DATADIR_BLAST5, 48),
		DATA_MAKE_NUM(DATADIR_BLAST5, 49),
		DATA_MAKE_NUM(DATADIR_BLAST5, 50),
		DATA_MAKE_NUM(DATADIR_BLAST5, 51),
		DATA_MAKE_NUM(DATADIR_BLAST5, 52),
		DATA_MAKE_NUM(DATADIR_BLAST5, 53),
		DATA_MAKE_NUM(DATADIR_BLAST5, 54)
	},
	{ 
		DATA_MAKE_NUM(DATADIR_BLAST5, 55),
		DATA_MAKE_NUM(DATADIR_BLAST5, 56),
		DATA_MAKE_NUM(DATADIR_BLAST5, 57),
		DATA_MAKE_NUM(DATADIR_BLAST5, 58),
		DATA_MAKE_NUM(DATADIR_BLAST5, 59),
		DATA_MAKE_NUM(DATADIR_BLAST5, 60),
		DATA_MAKE_NUM(DATADIR_BLAST5, 61),
		DATA_MAKE_NUM(DATADIR_BLAST5, 62)
	},
	{ 
		DATA_MAKE_NUM(DATADIR_BLAST5, 63),
		DATA_MAKE_NUM(DATADIR_BLAST5, 64),
		DATA_MAKE_NUM(DATADIR_BLAST5, 65),
		DATA_MAKE_NUM(DATADIR_BLAST5, 66),
		DATA_MAKE_NUM(DATADIR_BLAST5, 67),
		DATA_MAKE_NUM(DATADIR_BLAST5, 68),
		DATA_MAKE_NUM(DATADIR_BLAST5, 69),
		DATA_MAKE_NUM(DATADIR_BLAST5, 70)
	},
	{ 
		-1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
	},
	{ 
		-1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
	},
	{ 
		-1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
	},
};

static s32 messBaseTbl[] = {
	0xE0000,
	0xE0018,
	0xE0030,
	0xE0048,
	0xE0060,
	0xE0078,
	0,
	0,
	0,
};

static float playerOfsTbl[][2] = {
	{ -94, 0 },
	{ 0, 0 },
	{ 94, 0 }
};

static char *plateObjNameTbl[] = {
	"plate",
	"plate1",
	"plate2",
	"plate3"
};

static char *hiliteObjNameTbl[] = {
	"lite",
	"lite1",
	"lite2",
	"lite3",
	"kao",
	"kao1",
	"kao2",
	"kao3",
};

static s32 resultRankFX12Tbl[] = {
	0x122,
	0x162,
	0x1A2,
	0x1E2,
	0x222,
	0x262,
	0x2A2,
	0x2E2
};

static s32 resultRankFX3Tbl[] = {
	0x12A,
	0x16A,
	0x1AA,
	0x1EA,
	0x22A,
	0x26A,
	0x2AA,
	0x2EA
};

static s32 resultRankFX4Tbl[] = {
	0x12E,
	0x16E,
	0x1AE,
	0x1EE,
	0x22E,
	0x26E,
	0x2AE,
	0x2EE
};

static s32 impactFXTbl[] = {
	0x119,
	0x159,
	0x199,
	0x1D9,
	0x219,
	0x259,
	0x299,
	0x2D9
};

static s32 lotteryWheelMdlTbl[] = {
	DATA_MAKE_NUM(DATADIR_BLAST5, 13),
	DATA_MAKE_NUM(DATADIR_BLAST5, 14),
	DATA_MAKE_NUM(DATADIR_BLAST5, 15),
	DATA_MAKE_NUM(DATADIR_BLAST5, 16),
	DATA_MAKE_NUM(DATADIR_BLAST5, 17),
	DATA_MAKE_NUM(DATADIR_BLAST5, 18),
	DATA_MAKE_NUM(DATADIR_BLAST5, 19),
	DATA_MAKE_NUM(DATADIR_BLAST5, 20),
};

static s16 lotterySprPrioTbl[] = {
	1520,
	1510,
	1500,
	1500,
	1500,
	1500,
	1500,
	1500,
	1500,
	1500,
	1500,
	1490,
	1490,
	1500,
	1500
};

static s32 lotterySprTbl[] = {
	DATA_MAKE_NUM(DATADIR_BOARD, 39),
	DATA_MAKE_NUM(DATADIR_BOARD, 38),
	DATA_MAKE_NUM(DATADIR_BOARD, 41),
	DATA_MAKE_NUM(DATADIR_BOARD, 40),
	DATA_MAKE_NUM(DATADIR_BOARD, 40),
	DATA_MAKE_NUM(DATADIR_BOARD, 40),
	DATA_MAKE_NUM(DATADIR_BOARD, 45),
	DATA_MAKE_NUM(DATADIR_BOARD, 40),
	DATA_MAKE_NUM(DATADIR_BOARD, 40),
	DATA_MAKE_NUM(DATADIR_BOARD, 40),
	DATA_MAKE_NUM(DATADIR_BOARD, 44),
	DATA_MAKE_NUM(DATADIR_BOARD, 42),
	DATA_MAKE_NUM(DATADIR_BOARD, 42),
};

static float lotterySprPosTbl[][2] = {
	{ 0, -35 },
	{ 0, 0 },
	{ -68, -38 },
	{ 80, -22 },
	{ 64, -22 },
	{ 48, -22 },
	{ 26, -22 },
	{ 80, -48 },
	{ 64, -48 },
	{ 48, -48 },
	{ 26, -48 },
	{ -18, -40 },
	{ -18, 32 },
	{ -16, -72 },
	{ -16, 0 }
};

static s32 teamCharSprTbl[] = {
	DATA_MAKE_NUM(DATADIR_BOARD, 46),
	DATA_MAKE_NUM(DATADIR_BOARD, 47),
	DATA_MAKE_NUM(DATADIR_BOARD, 48),
	DATA_MAKE_NUM(DATADIR_BOARD, 49),
	DATA_MAKE_NUM(DATADIR_BOARD, 50),
	DATA_MAKE_NUM(DATADIR_BOARD, 51),
	DATA_MAKE_NUM(DATADIR_BOARD, 52),
	DATA_MAKE_NUM(DATADIR_BOARD, 53),
};

static s8 currTicket;
static s8 numTickets;
static s8 last5Player;
static s16 last5Space;
static s16 hostMdl;
static omObjData *last5RouletteObj;
static Process *last5Proc;
static omObjData *teamResultObj;
static omObjData *hostMoveObj;
static omObjData *lotteryDrawObj;
static omObjData *lotteryDrawWheelObj;

static Vec spacePos;
static Vec focusPos;
static Vec hostPos;
static s16 hostMot[8];
static omObjData *lotteryTicketObj[4];

static void DestroyLast5(void);

static void ExecLast5(void);
static void CreateLast5(void);
static void KillLast5(void);

static void InitHost(void);
static void KillHost(void);

static void Last5Main(void);

static s32 CheckJump(s32 player);

static void CreateBlock(Vec *pos);

static void CreateLotteryDrawWheel(void);

static void SetLotteryDrawState(s32 state);
static s32 GetLotteryDrawState();

static void KillLotteryDrawWheel(void);

static void ExecLotteryDraw(void);

static void InitLotteryTicket(void);
static void KillLotteryTicket(void);

static void StartHostMove(Vec *from, Vec *to, s32 time);
static s32 CheckHostMove(void);


static void CreateStopWin(void);
static void CreateLast5Roulette(void);
static void SetLast5RouletteFade(s32 flag);
static void SetLast5RouletteState(s32 state);
static s32 GetLast5RouletteState();
static s32 GetLast5RouletteResult();

static void CreateTeamResult(void);
static void GetTeamResultTaget(s32 team, Vec *pos);
static void SetTeamResultTaget(s32 team, Vec *pos);
static void KillTeamResult(void);

void BoardLast5Exec()
{
	GWSystem.player_curr = -1;
	last5Proc = HuPrcChildCreate(ExecLast5, 8200, 14336, 0, boardMainProc);
	HuPrcDestructorSet2(last5Proc, DestroyLast5);
	while(last5Proc != NULL) {
		HuPrcVSleep();
	}
	GWSystem.player_curr = 0;
}

static void DestroyLast5(void)
{
	KillLast5();
	HuDataDirClose(DATADIR_BLAST5);
	last5Proc = NULL;
}

static void ExecLast5(void)
{
	s32 i;
	messBase = messBaseTbl[GWBoardGet()];
	CreateLast5();
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	_ClearFlag(0x1001C);
	BoardLast5GfxInit();
	BoardAudSeqFadeOut(0, 1000);
	BoardMusStart(1, 8, 127, 0);
	BoardWinCreate(2, messBase, BoardWinPortraitGetStar());
	BoardWinWait();
	BoardWinKill();
	ExecLotteryDraw();
	Last5Main();
	BoardAudSeqFadeOut(1, 1000);
	_SetFlag(0x1001C);
	_SetFlag(0x1000E);
	WipeColorSet(255, 255, 255);
	WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	BoardModelMotionStart(hostMdl, 1, 0x40000001);
	BoardCameraMoveSet(0);
	BoardCameraViewSet(2);
	BoardCameraMotionWait();
	BoardCameraMoveSet(1);
	for(i=0; i<4; i++) {
		BoardModelVisibilitySet(BoardPlayerModelGet(i), 1);
		BoardPlayerCornerPosSet(i);
		BoardPlayerRotYSet(i, 0.0f);
	}
	BoardStatusItemSet(0);
	HuPrcSleep(60);
	HuPrcEnd();
}

static void CreateLast5(void)
{
	Vec rot;
	s32 i;
	last5Space = BoardSpaceFlagPosGet(0, 0x80000000, &spacePos);
	for(i=0; i<4; i++) {
		BoardModelVisibilitySet(BoardPlayerModelGet(i), 0);
	}
	BoardStatusItemSet(0);
	focusPos.x = 150.0f+spacePos.x;
	focusPos.y = 100.0f+spacePos.y;
	focusPos.z = -150.0f+spacePos.z;
	focusMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 10), NULL, 0);
	BoardModelVisibilitySet(focusMdl, 0);
	BoardModelPosSetV(focusMdl, &focusPos);
	rot.x = -10.0f;
	rot.y = 0.0f;
	rot.z = 0.0f;
	BoardCameraMoveSet(0);
	BoardCameraMotionStartEx(focusMdl, &rot, NULL, 1480.0f, 25.0f, 1);
	BoardCameraMotionWait();
	BoardCameraMoveSet(1);
	InitHost();
	CreateLotteryDrawWheel();
	InitLotteryTicket();
}

static void KillLast5(void)
{
	if(stopWin != -1) {
		HuWinKill(stopWin);
		stopWin = -1;
	}
	BoardConfettiKill();
	KillHost();
	KillLotteryDrawWheel();
	KillLotteryTicket();
}

static void InitHost(void)
{
	Vec pos;
	s32 i;
	s32 board = GWBoardGet();
	hostMdl = BoardStarHostMdlGet();
	BoardModelPosGet(hostMdl, &hostPos);
	for(i=0; i<8; i++) {
		hostMot[i] = BoardModelMotionCreate(hostMdl, hostMotTbl[board][i]);
	}
	BoardModelMotionStart(hostMdl, 1, 0x40000001);
	pos.x = 150.0f+spacePos.x;
	pos.y = spacePos.y;
	pos.z = (150.0f+spacePos.z)-50.0f;
	BoardModelPosSetV(hostMdl, &pos);
}

static void KillHost(void)
{
	s32 i;
	for(i=0; i<8; i++) {
		if(hostMot[i] != -1) {
			BoardModelMotionKill(hostMdl, hostMot[i]);
			hostMot[i] = -1;
		}
	}
	BoardModelRotYSet(hostMdl, 0.0f);
	BoardModelPosSetV(hostMdl, &hostPos);
}

static void Last5Main(void)
{
	float temp_f31;
	s32 temp_r31;
	s32 temp_r30;
	s32 temp_r29;
	s32 temp_r27;
	s32 temp_r26;
	s32 temp_r25;
	s32 temp_r24;
	s32 temp_r23;
	s32 temp_r22;
	s32 temp_r21;
	s32 temp_r20;
	s32 temp_r19;
	s32 temp_r18;
	Vec sp6C[4];
	Vec sp60;
	Vec sp54;
	Vec sp48;
	Vec sp3C;
	float sp2C[4];
	s8 sp28[4];
	s8 sp24[4];
	s8 sp20[4];
	
	
	
	temp_r18 = -1;
	for(temp_r26=temp_r27=0; temp_r27<=3; temp_r27++) {
		for(temp_r25=temp_r31=0; temp_r31<4; temp_r31++) {
			if(GWPlayer[temp_r31].rank == temp_r27) {
				sp28[temp_r26] = temp_r31;
				sp24[temp_r26] = temp_r27;
				temp_r26++;
				if(temp_r27 > temp_r18) {
					sp20[temp_r25] = temp_r31;
					temp_r25++;
				}
			}
		}
		if(temp_r25 != 0) {
			temp_r21 = temp_r25;
		}
	}
	BoardWinCreate(2, messBase+10, BoardWinPortraitGetStar());
	BoardWinWait();
	BoardModelMotionShiftSet(hostMdl, hostMot[5], 0.0f, 4.0f, 0);
	HuPrcVSleep(8);
	BoardModelMotionShiftSet(hostMdl, hostMot[6], 0.0f, 8.0f, 0x40000001);
	for(temp_r31=0; temp_r31<4; temp_r31++) {
		temp_r30 = sp28[temp_r31];
		temp_r27 = sp24[temp_r31];
		temp_r23 = GWPlayer[temp_r30].character;
		sp6C[temp_r31].x = -122.0f;
		sp6C[temp_r31].y = (temp_r31*74)+80;
		sp6C[temp_r31].z = 0.0f;
		BoardStatusPosSet(temp_r30, &sp6C[temp_r31]);
		HuPrcVSleep();
		BoardStatusShowSet(temp_r30, 1);
		sp2C[temp_r31] = (122.0f-sp6C[temp_r31].x)/15.0f;
		for(temp_r29=0; temp_r29<15; temp_r29++) {
			sp6C[temp_r31].x += sp2C[temp_r31];
			BoardStatusPosSet(temp_r30, &sp6C[temp_r31]);
			HuPrcVSleep();
		}
		switch(temp_r27) {
			case 0:
			case 1:
				temp_r22 = resultRankFX12Tbl[temp_r23];
				break;
				
			case 2:
				temp_r22 = resultRankFX3Tbl[temp_r23];
				break;
				
			case 3:
				temp_r22 = resultRankFX4Tbl[temp_r23];
				break;
		}
		HuAudFXPlay(temp_r22);
		temp_r24 = 11+messBase+temp_r27;
		BoardWinCreate(2, temp_r24, BoardWinPortraitGetStar());
		BoardWinInsertMesSet(BoardPlayerGetCharMess(temp_r30), temp_r27);
		BoardWinWait();
	}
	if((s32)GWSystem.team != 0) {
		CreateTeamResult();
		for(temp_r31=0; temp_r31<4; temp_r31++) {
			sp2C[temp_r31] = (-122.0f-sp6C[temp_r31].x)/15.0f;
		}
		for(temp_r29=0; temp_r29<15; temp_r29++) {
			for(temp_r31=0; temp_r31<4; temp_r31++) {
				temp_r30 = sp28[temp_r31];
				sp6C[temp_r31].x += sp2C[temp_r31];
				BoardStatusPosSet(temp_r30, &sp6C[temp_r31]);
			}
			HuPrcVSleep();
		}
		BoardStatusItemSet(0);
		temp_r24 = 0xE0090+GWBoardGet();
		BoardWinCreate(2, temp_r24, BoardWinPortraitGetStar());
		BoardWinWait();
		for(temp_r31=0; temp_r31<2; temp_r31++) {
			GetTeamResultTaget(temp_r31, &sp6C[temp_r31]);
			sp2C[temp_r31] = (122.0f-sp6C[temp_r31].x)/15.0f;
			for(temp_r29=0; temp_r29<15; temp_r29++) {
				sp6C[temp_r31].x += sp2C[temp_r31];
				SetTeamResultTaget(temp_r31, &sp6C[temp_r31]);
				HuPrcVSleep();
			}
		}
	}
	BoardModelMotionStart(hostMdl, hostMot[5], 0x40000004);
	HuPrcVSleep(8);
	BoardModelMotionShiftSet(hostMdl, 1, 0.0f, 8.0f, 0x40000001);
	BoardWinCreate(2, messBase+15, BoardWinPortraitGetStar());
	BoardWinWait();
	if((s32)GWSystem.team != 0) {
		for(temp_r31=0; temp_r31<2; temp_r31++) {
			sp2C[temp_r31] = (-122.0f-sp6C[temp_r31].x)/15.0f;
		}
		for(temp_r29=0; temp_r29<15; temp_r29++) {
			for(temp_r31=0; temp_r31<2; temp_r31++) {
				GetTeamResultTaget(temp_r31, &sp6C[temp_r31]);
				sp6C[temp_r31].x += sp2C[temp_r31];
				SetTeamResultTaget(temp_r31, &sp6C[temp_r31]);
			}
			HuPrcVSleep();
		}
		KillTeamResult();
	} else {
		for(temp_r31=0; temp_r31<4; temp_r31++) {
			sp2C[temp_r31] = (-122.0f-sp6C[temp_r31].x)/15.0f;
		}
		for(temp_r29=0; temp_r29<15; temp_r29++) {
			for(temp_r31=0; temp_r31<4; temp_r31++) {
				temp_r30 = sp28[temp_r31];
				sp6C[temp_r31].x += sp2C[temp_r31];
				BoardStatusPosSet(temp_r30, &sp6C[temp_r31]);
			}
			HuPrcVSleep();
		}
		BoardStatusItemSet(0);
	}
	BoardModelPosGet(hostMdl, &sp60);
	sp54.x = sp60.x+100.0f;
	sp54.y = sp60.y;
	sp54.z = sp60.z;
	StartHostMove(&sp60, &sp54, 25);
	while(!CheckHostMove()) {
		HuPrcVSleep();
	}
	BoardModelMotionShiftSet(hostMdl, 1, 0.0f, 8.0f, 0x40000001);
	HuPrcSleep(8);
	if((s32)GWSystem.team != 0) {
		temp_r30 = last5Player;
	} else {
		if(temp_r21 == 1) {
			temp_r30 = sp20[0];
		} else {
			temp_r30 = sp20[BoardRandMod(temp_r21)];
		}
	}
	sp48.x = sp60.x-100.0f;
	sp48.y = sp60.y;
	sp48.z = sp60.z;
	sp48.y += 700.0f;
	BoardPlayerPosSetV(temp_r30, &sp48);
	BoardPlayerMotionStart(temp_r30, 6, 0x40000001);
	BoardPlayerVoiceEnableSet(temp_r30, 6, 0);
	BoardPlayerRotYSet(temp_r30, 0);
	BoardModelVisibilitySet(BoardPlayerModelGet(temp_r30), 1);
	BoardWinCreate(2, messBase+16, BoardWinPortraitGetStar());
	BoardWinInsertMesSet(BoardPlayerGetCharMess(temp_r30), 3);
	BoardWinWait();
	BoardModelMotionShiftSet(hostMdl, hostMot[5], 0.0f, 4.0f, 0);
	HuPrcVSleep(8);
	BoardModelMotionShiftSet(hostMdl, hostMot[6], 0.0f, 8.0f, 0x40000001);
	temp_r19 = 0;
	temp_r29 = 3;
	for(temp_f31=0; temp_r29>0; temp_f31++) {
		sp48.y += (float)(5.0+((9.8/120)*temp_f31*temp_f31));
		if(sp60.y > sp48.y) {
			omVibrate(temp_r30, 12, 6, 6);
			if(!temp_r19) {
				HuAudFXPlay(impactFXTbl[GWPlayer[temp_r30].character]);
				temp_r19 = 1;
			}
			sp48.y = sp60.y;
			sp48.y += temp_r29*10;
			temp_r29--;
			temp_f31 = 0.0f;
		}
		BoardPlayerPosSetV(temp_r30, &sp48);
		HuPrcVSleep();
	}
	HuPrcSleep(20);
	BoardPlayerIdleSet(temp_r30);
	sp3C = sp48;
	BoardModelMotionStart(hostMdl, hostMot[5], 0x40000004);
	HuPrcVSleep(8);
	BoardModelMotionShiftSet(hostMdl, 1, 0.0f, 8.0f, 0x40000001);
	CreateLast5Roulette();
	SetLast5RouletteFade(1);
	SetLast5RouletteState(2);
	CreateStopWin();
	sp48.x = sp60.x-100.0f;
	sp48.y = sp60.y;
	sp48.z = sp60.z;
	CreateBlock(&sp48);
	SetLotteryDrawState(2);
	while(GetLotteryDrawState() != 0) {
		HuPrcVSleep();
	}
	while(!CheckJump(temp_r30)) {
		HuPrcVSleep();
	}
	BoardPlayerDiceJumpStart(temp_r30);
	while(!BoardPlayerDiceJumpCheck(temp_r30)) {
		HuPrcVSleep();
	}
	SetLotteryDrawState(1);
	SetLast5RouletteState(3);
	while(GWPlayer[temp_r30].field08_bit3) {
		HuPrcVSleep();
	}
	while(GetLast5RouletteState() != 0) {
		HuPrcVSleep();
	}
	HuWinDispOff(stopWin);
	SetLotteryDrawState(3);
	temp_r20 = GetLast5RouletteResult();
	GWSystem.last5_effect = temp_r20;
	if(GWSystem.last5_effect == 2) {
		BoardSpaceTypeForce(2, 3);
	}
	if(GWSystem.last5_effect == 3) {
		BoardSpaceTypeForce(2, 7);
	}
	temp_r24 = 18+messBase+temp_r20;
	BoardWinCreate(2, temp_r24, BoardWinPortraitGetStar());
	BoardWinWait();
	StartHostMove(&sp54, &sp60, 25);
	BoardPlayerPosGet(temp_r30, &sp48);
	sp48 = sp3C;
	sp3C.x = sp48.x-300.0f;
	sp3C.y = sp48.y;
	sp3C.z = sp48.z;
	BoardPlayerPosLerpStart(temp_r30, &sp48, &sp3C, 25);
	while(GWPlayer[temp_r30].moving) {
		HuPrcVSleep();
	}
	BoardPlayerIdleSet(temp_r30);
	BoardModelVisibilitySet(BoardPlayerModelGet(temp_r30), 0);
	SetLast5RouletteFade(0);
	BoardModelMotionShiftSet(hostMdl, 1, 0.0f, 8.0f, 0x40000001);
	BoardWinCreate(2, messBase+23, BoardWinPortraitGetStar());
	BoardWinWait();
	BoardModelMotionShiftSet(hostMdl, hostMot[4], 0.0f, 8.0f, 0);
	HuPrcSleep(8);
	while(!BoardModelMotionEndCheck(hostMdl)) {
		HuPrcVSleep();
	}
	BoardModelMotionShiftSet(hostMdl, hostMot[2], 0.0f, 8.0f, 0x40000001);
	SetLotteryDrawState(4);
}

static s32 CheckJump(s32 player)
{
	s32 sp8 = 0;
	if(GWPlayer[player].com) {
		if(BoardRandMod(100) >= 90) {
			return 1;
		} else {
			goto return0;
		}
	}
	if(HuPadBtnDown[GWPlayer[player].port] == PAD_BUTTON_A) {
		return 1;
	} else {
		return0:
		return 0;
	}
}