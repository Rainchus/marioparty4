#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/audio.h"
#include "game/board/window.h"

#include "game/objsub.h"
#include "game/sprite.h"
#include "game/audio.h"
#include "game/wipe.h"
#include "game/gamework.h"

static s16 bowserSpr[11];
static Vec playerPosTemp[4];

static s32 scareFxTbl[] = {
	0x128,
	0x168,
	0x1A8,
	0x1E8,
	0x228,
	0x268,
	0x2A8,
	0x2E8
};


static s8 eventPlayer;
static s8 eventType;
static s16 eventSpace;
static s16 playerMot[4];
static s16 fireParMan;
static AnimData *fireAnim;
static char coinStealStrAll[8];
static char coinStealStr[8];
static omObjData *suitGiveObj;
static omObjData *miniBowserBalloonObj;
static omObjData *bowserEventObj;
static omObjData *miniBowserObj;
static omObjData *bowserObj;
static Process *bowserProc;

static s16 jumpMot = -1;
static s16 scareMot = -1;
static s16 suitItemMdl = -1;
static s16 bowserMdl = -1;

static void ExecBowser(void);
static void ExecBowserMain(void);
static void ExecMGReturn(void);
static void DestroyBowser(void);

static void SquishPlayers(void);
static void ExecBowserSpecial(void);
static void ExecBowserGame(void);
static void DoMGReturnEffect(void);
static void ExecBowserShuffle(void);
static void ExecBowserRevo(void);
static void ExecBowserSuit(void);

static void CreateBowserObj(void);

static void SetBowserState(s32 state);
static s32 CheckBowserIdle(void);

static void CreateBowserEvent(void);
static s32 CheckBowserEvent(void);
static void StopBowserEvent(void);

static void ConfigBowserEvent(void);

static void CreateMiniBowser(void);
static s32 CheckMiniBowser(void);


static void CreatePlayerMot(void);
static void KillPlayerMot(void);

static void InitBowserFire(void);
static void KillBowserFire(void);

static s32 ExecMiniBowserEvent(void);

s32 BoardBowserExec(s32 player, s32 space)
{
	if(_CheckFlag(0x1000B)) {
		HuAudFXPlay(841);
		BoardCameraViewSet(2);
		BoardPlayerMotBlendSet(player, 0, 15);
		while(!BoardPlayerMotBlendCheck(player)) {
			HuPrcVSleep();
		}
		BoardCameraMotionWait();
		BoardTutorialHookExec(12, 0);
		GWPlayer[player].color = 2;
	} else {
		eventPlayer = player;
		eventSpace = space;
		playerMot[0] = playerMot[1] = playerMot[2] = playerMot[3] = -1;
		bowserProc = HuPrcChildCreate(ExecBowser, 8196, 14336, 0, boardMainProc);
		HuPrcDestructorSet2(bowserProc, DestroyBowser);
		while(bowserProc) {
			HuPrcVSleep();
		}
		GWPlayer[player].color = 2;
	}
}

typedef struct bowser_work {
	u8 kill : 1;
} BowserWork;

typedef struct mini_bowser_work {
	u8 kill : 1;
} MiniBowserWork;

typedef struct bowser_event_work {
	u8 kill : 1;
} BowserEventWork;

static void ExecBowser(void)
{
	s32 i;
	s32 status;
	if(!_CheckFlag(0x10003)) {
		HuAudFXPlay(841);
		omVibrate(eventPlayer, 12, 4, 2);
		if(GWBoardGet() == 5 && boardBowserHook) {
			boardBowserHook(1);
		}
		BoardAudSeqPause(0, 1, 1000);
		if(BoardRandMod(100) < 20) {
			eventType = 0;
		} else {
			eventType = 1;
		}
	} else {
		BoardMusStart(1, 6, 127, 0);
	}
	status = BoardDataDirReadAsync(DATADIR_BKOOPA);
	BoardDataAsyncWait(status);
	CreatePlayerMot();
	if(!_CheckFlag(0x10003)) {
		ExecBowserMain();
	} else {
		ExecMGReturn();
	}
	for(i=0; i<4; i++) {
		if(eventSpace == GWPlayer[i].space_curr) {
			BoardPlayerMotionSpeedSet(i, 1.0f);
		}
	}
	BoardAudSeqPause(0, 0, 1000);
	if(bowserObj) {
		OM_GET_WORK_PTR(bowserObj, BowserWork)->kill = 1;
	}
	if(miniBowserObj) {
		OM_GET_WORK_PTR(miniBowserObj, MiniBowserWork)->kill = 1;
	}
	if(bowserEventObj) {
		OM_GET_WORK_PTR(bowserEventObj, BowserEventWork)->kill = 1;
	}
	GWPlayer[eventPlayer].show_next = 1;
	BoardCameraMotionStartEx(-1, NULL, NULL, 2100.0f, -1.0f, 21);
	HuPrcSleep(30);
	for(i=0; i<4; i++) {
		BoardPlayerIdleSet(i);
	}
	BoardCameraMotionWait();
	if(GWBoardGet() == 5 && boardBowserHook) {
		boardBowserHook(0);
	} else {
		HuPrcSleep(30);
	}
	HuPrcEnd();
}

static void ExecBowserMain(void)
{
	s32 result = 0;
	BoardPlayerMotBlendSet(eventPlayer, 0, 15);
	while(!BoardPlayerMotBlendCheck(eventPlayer)) {
		HuPrcVSleep();
	}
	BoardMusStart(1, 5, 127, 0);
	BoardCameraViewSet(3);
	BoardFilterFadeInit(30, 160);
	BoardCameraMotionWait();
	BoardPlayerMotionShiftSet(eventPlayer, jumpMot, 0.0f, 10.0f, 0x40000001);
	BoardPlayerMotionSpeedSet(eventPlayer, 2.0f);
	HuPrcSleep(120);
	ConfigBowserEvent();
	HuAudFXPlay(scareFxTbl[GWPlayer[eventPlayer].character]);
	BoardPlayerMotionShiftSet(eventPlayer, scareMot, 0.0f, 10.0f, 0);
	CreateMiniBowser();
	while(!CheckMiniBowser()) {
		HuPrcVSleep();
	}
	BoardPlayerIdleSet(eventPlayer);
	if(eventType) {
		result = ExecMiniBowserEvent();
		if(!result) {
			return;
		}
		BoardAudSeqFadeOut(1, 1000);
		BoardFilterFadeInit(30, 160);
		HuPrcSleep(30);
	}
	ExecBowserSpecial();
	BoardModelMotionShiftSet(bowserMdl, 3, 0.0f, 8.0f, 0);
	HuPrcSleep(8);
	HuAudFXPlay(58);
	BoardWinCreate(2, 0x3000B, 5);
	BoardWinWait();
	BoardWinKill();
	BoardAudSeqFadeOut(1, 1000);
	while(!BoardModelMotionEndCheck(bowserMdl)) {
		HuPrcVSleep();
	}
	SetBowserState(6);
	while(!CheckBowserIdle()) {
		HuPrcVSleep();
	}
	BoardFilterFadeOut(30);
}

static void ExecMGReturn(void)
{
	s32 i;
	s32 player;
	BoardStatusItemSet(1);
	for(i=0; i<4; i++) {
		BoardPlayerPosSetV(i, &playerPosTemp[i]);
	}
	BoardCameraMoveSet(0);
	BoardCameraTargetPlayerSet(eventPlayer);
	BoardCameraViewSet(2);
	BoardCameraMotionWait();
	CreateBowserObj();
	SquishPlayers();
	BoardPlayerMotBlendSet(eventPlayer, 0, 15);
	BoardCameraViewSet(3);
	BoardFilterFadeInit(30, 160);
	BoardStatusItemSet(0);
	BoardCameraMotionWait();
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 21);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	_ClearFlag(0x1001C);
	BoardCameraMoveSet(1);
	player = GWSystem.player_curr;
	GWSystem.player_curr = -1;
	DoMGReturnEffect();
	GWSystem.player_curr = player;
	BoardStatusShowSetAll(1);
	BoardModelMotionShiftSet(bowserMdl, 3, 0.0f, 8.0f, 0);
	HuPrcSleep(8);
	HuAudFXPlay(58);
	BoardWinCreate(2, 0x3000B, 5);
	BoardWinWait();
	BoardWinKill();
	while(!BoardStatusStopCheck(0)) {
		HuPrcVSleep();
	}
	BoardAudSeqFadeOut(1, 1000);
	while(!BoardModelMotionEndCheck(bowserMdl)) {
		HuPrcVSleep();
	}
	SetBowserState(6);
	while(!CheckBowserIdle()) {
		HuPrcVSleep();
	}
	BoardFilterFadeOut(30);
	BoardMusStartBoard();
}

static void DestroyBowser(void)
{
	KillPlayerMot();
	HuDataDirClose(DATADIR_BKOOPA);
	bowserProc = NULL;
}

static void SquishPlayers(void)
{
	Vec pos;
	Vec pos_space;
	s32 i;
	BoardPlayerPosGet(eventPlayer, &pos);
	if(!_CheckFlag(0x10003)) {
		HuAudFXPlay(798);
	}
	pos.y += 6.0f;
	BoardPlayerPosSetV(eventPlayer, &pos);
	GWPlayer[eventPlayer].show_next = 0;
	BoardPlayerMotionSpeedSet(eventPlayer, 0.0f);
	for(i=0; i<4; i++) {
		if(eventSpace == GWPlayer[i].space_curr) {
			BoardPlayerPosGet(i, &pos);
			BoardSpacePosGet(0, eventSpace, &pos_space);
			pos.y = pos_space.y+2.5f;
			BoardPlayerPosSetV(i, &pos);
			BoardPlayerMotionStart(i, playerMot[i], 0);
			BoardPlayerMotionTimeSet(i, 50.0f);
			BoardPlayerMotionSpeedSet(i, 0.0f);
		}
	}
}

static void ExecBowserSpecial(void)
{
	s32 i;
	CreateBowserObj();
	while(!CheckBowserIdle()) {
		HuPrcVSleep();
	}
	SetBowserState(2);
	HuAudFXPlay(58);
	BoardMusStart(1, 6, 127, 0);
	HuPrcSleep(120);
	BoardWinCreate(2, 0x30007, 5);
	BoardWinWait();
	BoardWinKill();
	HuAudFXPlay(857);
	BoardModelMotionShiftSet(bowserMdl, 4, 0.0f, 10.0f, 0);
	for(i=0; i<4; i++) {
		omVibrate(i, 12, 12, 0);
	}
	HuPrcSleep(11);
	while(!BoardModelMotionEndCheck(bowserMdl)) {
		HuPrcVSleep();
	}
	CreateBowserEvent();
	HuAudFXPlay(831);
	HuAudFXPlay(60);
	while(!CheckBowserEvent()) {
		HuPrcVSleep();
	}
	HuPrcSleep(60);
	BoardModelAttrSet(bowserMdl, 0x40000004);
	while(!BoardModelMotionEndCheck(bowserMdl)) {
		HuPrcVSleep();
	}
	BoardModelMotionShiftSet(bowserMdl, 1, 0.0f, 10.0f, 0);
	StopBowserEvent();
	switch(GWSystem.bowser_event) {
		case 0:
			ExecBowserGame();
			break;
			
		case 2:
			ExecBowserRevo();
			break;
			
		case 1:
			ExecBowserShuffle();
			break;
			
		case 3:
			ExecBowserSuit();
			break;
	}
}

static void ExecBowserGame(void)
{
	s32 i;
	s16 mgTbl[3] = {
		435,
		436,
		437
	};
	s32 messLoss[3] = {
		0x30009,
		0x3000C,
		0x3000E
	};
	s32 mg;
	s32 mess;
	s32 fx_stat;
	for(i=0; i<4; i++) {
		BoardPlayerPosGet(i, &playerPosTemp[i]);
	}
	BoardWinCreate(2, 0x30008, 5);
	BoardWinWait();
	mess = messLoss[GWSystem.bowser_loss];
	BoardWinCreate(2, mess, 5);
	BoardWinWait();
	BoardWinKill();
	BoardModelMotionShiftSet(bowserMdl, 5, 0.0f, 8.0f, 0);
	HuPrcSleep(8);
	while(BoardModelMotionTimeGet(bowserMdl) < 80.0f) {
		HuPrcVSleep();
	}
	fx_stat = HuAudFXPlay(846);
	InitBowserFire();
	while(BoardModelMotionTimeGet(bowserMdl) < 200.0f) {
		HuPrcVSleep();
	}
	BoardAudSeqFadeOut(1, 1000);
	BoardMusVolPanSet(0, 0, 1);
	BoardAudSeqPause(0, 0, 1);
	_SetFlag(0x1000E);
	HuAudFXFadeOut(fx_stat, 500);
	WipeColorSet(255, 255, 255);
	WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	HuAudFXAllStop();
	_SetFlag(0x1001C);
	KillBowserFire();
	HuPrcSleep(60);
	BoardModelMotionStart(bowserMdl, 1, 0);
	mg = (s16)mgTbl[BoardRandMod(3)];
	GWMGAvailSet(mg);
	GWSystem.mg_next = mg-401;
	_SetFlag(0x10003);
	BoardNextOvlSet(OVL_INST);
	BoardFilterFadeOut(30);
	HuPrcEnd();
}

static void DoMGReturnEffect(void)
{
	s32 messTbl[3] = {
		0x3000A,
		0x3000D,
		0x3000F
	};
	s32 player;
	s32 coin;
	s32 item;
	s32 delay;
	s32 item_cnt;
	s32 mess;
	s32 mess_char;
	for(player=0; player<4; player++) {
		s16 gain = GWPlayer[player].coin_gain;
		if(gain == 1) { 
			break;
		}
	}
	mess = messTbl[GWSystem.bowser_loss];
	mess_char = BoardPlayerGetCharMess(player);
	BoardStatusShowSetForce(player);
	BoardStatusShowSet(player, 1);
	BoardWinCreate(2, mess, 5);
	BoardWinInsertMesSet(mess_char, 1);
	BoardWinWait();
	while(!BoardStatusStopCheck(player)) {
		HuPrcVSleep();
	}
	omVibrate(player, 12, 4, 2);
	if(GWSystem.bowser_loss == 2) {
		item_cnt = BoardPlayerItemCount(player);
		for(item=0; item<item_cnt; item++) {
			BoardPlayerItemRemove(player, 0);
			HuPrcSleep(30);
		}
	} else {
		coin = BoardPlayerCoinsGet(player);
		if(GWSystem.bowser_loss == 1) {
			coin = BoardPlayerCoinsGet(player)-(coin >> 1);
		}
		if(coin >= 50 ) {
			delay = 1;
		} else if(coin >= 20) {
			delay = 3;
		} else {
			delay = 6;
		}
		while(coin != 0 && BoardPlayerCoinsGet(player) != 0) {
			BoardPlayerCoinsAdd(player, -1);
			HuAudFXPlay(14);
			HuPrcSleep(delay);
			coin--;
		}
		HuAudFXPlay(15);
	}
	BoardStatusShowSet(player, 0);
	while(!BoardStatusStopCheck(player)) {
		HuPrcVSleep();
	}
}