#include "common.h"
#include "math.h"
#include "game/object.h"
#include "game/flag.h"
#include "game/data.h"
#include "game/wipe.h"

typedef void (*VoidFunc)(void);

omObjData *boardMainObj;
u32 boardRandSeed;
static omObjData *last5GfxObj;
static omObjData *confettiObj;
static omObjData *filterObj;
void *boardTurnStartFunc;
u32 lbl_801D3F00;
u32 lbl_801D3EFC;
u32 lbl_801D3EF8;
VoidFunc boardTurnFunc;
void *boardLightSetHook;
void *boardLightResetHook;
static VoidFunc destroyFunc;
static VoidFunc createFunc;
static BOOL cameraUseBackup;
static omObjData *tauntObj;
static omObjData *cameraObj;
Process *boardObjMan;
Process *boardMainProc;

static OverlayID nextOvl = OVL_INVALID;

extern void BoardPlayerCoinsSet(s32 player, s32 value);
extern void BoardPlayerAutoSizeSet(s32 player, s32 value);
extern void fn_800A4A7C(void);
extern void fn_800A6EE4(void);

extern s8 boardTutorialF;

void BoardKill(void);

static void InitBoardFunc(omObjData *object);
static void ExecBoardFunc(omObjData *object);
static void KillBoardFunc(omObjData *object);

static void MainFunc(void);
static void DestroyMainFunc(void);

static void CreateBoard(void);
static void DestroyBoard(void);

static inline s32 BoardCurrGet()
{
	return GWSystem.board;
}

static inline s32 BoardPartyFlagGet()
{
	s32 value = GWSystem.party;
	return value;
}

static inline s16 BoardHandicapGet(s32 player)
{
	return GWPlayer[player].handicap;
}

void BoardCommonInit(VoidFunc create, VoidFunc destroy)
{
	omSysPauseEnable(FALSE);
	if(!_CheckFlag(FLAG_ID_MAKE(1, 0))) {
		_SetFlag(FLAG_ID_MAKE(1, 0));
		_ClearFlag(FLAG_ID_MAKE(2, 1));
		_ClearFlag(FLAG_ID_MAKE(2, 3));
		_ClearFlag(FLAG_ID_MAKE(2, 0));
		_ClearFlag(FLAG_ID_MAKE(2, 2));
		_ClearFlag(FLAG_ID_MAKE(2, 4));
		_ClearFlag(FLAG_ID_MAKE(2, 5));
		_ClearFlag(FLAG_ID_MAKE(1, 6));
		_ClearFlag(FLAG_ID_MAKE(1, 9));
		_ClearFlag(FLAG_ID_MAKE(0, 8));
		_ClearFlag(FLAG_ID_MAKE(0, 10));
		fn_800A4A7C();
	}
	
	nextOvl = OVL_INVALID;
	_SetFlag(FLAG_ID_MAKE(1, 28));
	_SetFlag(FLAG_ID_MAKE(1, 14));
	_ClearFlag(FLAG_ID_MAKE(1, 16));
	_ClearFlag(FLAG_ID_MAKE(1, 17));
	_ClearFlag(FLAG_ID_MAKE(1, 18));
	_ClearFlag(FLAG_ID_MAKE(1, 19));
	_ClearFlag(FLAG_ID_MAKE(1, 20));
	_ClearFlag(FLAG_ID_MAKE(1, 21));
	_ClearFlag(FLAG_ID_MAKE(1, 23));
	_ClearFlag(FLAG_ID_MAKE(1, 24));
	_ClearFlag(FLAG_ID_MAKE(1, 25));
	_ClearFlag(FLAG_ID_MAKE(1, 27));
	createFunc = create;
	destroyFunc = destroy;
	boardTurnFunc = NULL;
	lbl_801D3EFC = 0;
	lbl_801D3F00 = 0;
	lbl_801D3EF8 = 0;
	boardTurnStartFunc = NULL;
	boardObjMan = omInitObjMan(64, 8192);
	omSystemKeyCheckSetup(boardObjMan);
	boardMainObj = omAddObjEx(boardObjMan, 0, 0, 0, -1, InitBoardFunc);
	switch(omcurovl) {
		case OVL_W01:
			GWSystem.board = 0;
			break;
			
		case OVL_W02:
			GWSystem.board = 1;
			break;
			
		case OVL_W03:
			GWSystem.board = 2;
			break;
			
		case OVL_W04:
			GWSystem.board = 3;
			break;
			
		case OVL_W05:
			GWSystem.board = 4;
			break;
			
		case OVL_W06:
			GWSystem.board = 5;
			break;
			
		case OVL_W10:
			GWSystem.board = 6;
			break;
			
		case OVL_W20:
			GWSystem.board = 7;
			break;
			
		case OVL_W21:
			GWSystem.board = 8;
			break;
	}
}

static void InitBoardFunc(omObjData *object)
{
	boardMainProc = HuPrcChildCreate(MainFunc, 8194, 0x6000, 0, boardObjMan);
	HuPrcDestructorSet2(boardMainProc, DestroyMainFunc);
	object->func = ExecBoardFunc;
}

static void ExecBoardFunc(omObjData *object)
{
	if(!_CheckFlag(FLAG_ID_MAKE(1, 16))) {
		return;
	}
	if(!_CheckFlag(FLAG_ID_MAKE(1, 17))) {
		if(omSysExitReq) {
			BoardKill();
		} else {
			if(BoardPauseReqCheck()) {
				BoardPauseStart();
			} else {
				return;
			}
		}
	} else {
		if(boardMainProc) {
			HuPrcKill(boardMainProc);
		}
		object->func = KillBoardFunc;
	}
}

static void KillBoardFunc(omObjData *object)
{
	if(boardMainProc) {
		return;
	}
	if(WipeStatGet()) {
		return;
		return_alt:
		return;
	} else {
		if(HuARDMACheck()) {
			goto return_alt;
		}
		if(nextOvl != OVL_INVALID) {
			omOvlCallEx(nextOvl, 1, 0, 0);
		} else {
			if(_CheckFlag(FLAG_ID_MAKE(1, 11))) {
				BoardTutorialKill();
				BoardTutorialWorkRestore();
			}
			_ClearFlag(FLAG_ID_MAKE(1, 0));
			HuARDirFree(MAKE_DIR_NUM(DATADIR_BOARD));
			if(_CheckFlag(FLAG_ID_MAKE(1, 27))) {
				omOvlReturnEx(2, 1);
			} else {
				omOvlReturnEx(1, 1);
			}
		}
	}
}

void BoardKill(void)
{
	_SetFlag(FLAG_ID_MAKE(1, 28));
	_SetFlag(FLAG_ID_MAKE(1, 14));
	if(_CheckFlag(FLAG_ID_MAKE(1, 11))) {
		BoardTutorialHookExec(29, 0);
	}
	HuAudFXAllStop();
	if(!BoardIsStarted()) {
		WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
		boardTutorialF = 1;
		while(WipeStatGet()) {
			HuPrcVSleep();
		}
	}
	_SetFlag(FLAG_ID_MAKE(1, 17));
	HuPrcKill(boardMainProc);
	DestroyBoard();
}

s32 BoardIsKill(void)
{
	return (_CheckFlag(FLAG_ID_MAKE(1, 17))) ? 1 : 0;
}

void BoardPauseEnableSet(s32 value)
{
	if(_CheckFlag(FLAG_ID_MAKE(1, 11))) {
		_SetFlag(FLAG_ID_MAKE(1, 25));
		omSysPauseEnable(FALSE);
	} else {
		if(value) {
			_SetFlag(FLAG_ID_MAKE(1, 25));
		} else {
			_ClearFlag(FLAG_ID_MAKE(1, 25));
		}
	}
}

s32 BoardPauseEnableGet()
{
	return (_CheckFlag(FLAG_ID_MAKE(1, 25))) ? 1 : 0;
}

void BoardSaveInit(s32 board)
{
	int i;
	GWSystem.board = board;
	_ClearFlag(FLAG_ID_MAKE(1, 0));
	_ClearFlag(FLAG_ID_MAKE(1, 1));
	_ClearFlag(FLAG_ID_MAKE(1, 5));
	_ClearFlag(FLAG_ID_MAKE(1, 4));
	_ClearFlag(FLAG_ID_MAKE(1, 6));
	_ClearFlag(FLAG_ID_MAKE(1, 2));
	_ClearFlag(FLAG_ID_MAKE(1, 9));
	_ClearFlag(FLAG_ID_MAKE(1, 7));
	_ClearFlag(FLAG_ID_MAKE(1, 8));
	_ClearFlag(FLAG_ID_MAKE(0, 8));
	_ClearFlag(FLAG_ID_MAKE(1, 12));
	_ClearFlag(FLAG_ID_MAKE(1, 3));
	GWSystem.turn = 1;
	GWSystem.star_flag = 0;
	GWSystem.star_pos = 0;
	GWSystem.star_total = 1;
	GWSystem.last5_effect = 0;
	GWSystem.player_curr = -1;
	GWSystem.field31_bit0 = 0;
	GWSystem.field31_bit4 = 0;
	GWSystem.unk_32 = 1;
	GWSystem.mg_next = 0;
	GWSystem.mg_next_extra = 0;
	GWSystem.unk_38 = 0;
	GWSystem.block_pos = 0;
	memset(GWSystem.board_data, 0, 32);
	for(i=0; i<4; i++) {
		BoardPlayerAutoSizeSet(i, 0);
		GWPlayer[i].field00_bit9 = 0;
		GWPlayer[i].color = 0;
		GWPlayer[i].bowser_suit = 0;
		GWPlayer[i].field08_bit3 = 0;
		GWPlayer[i].space_shock = 0;
		GWPlayer[i].field02_bit1 = 0;
		GWPlayer[i].show_next = 1;
		BoardPlayerCoinsSet(i, 0);
		if(_CheckFlag(FLAG_ID_MAKE(1, 11))) {
			GWSystem.team = 0;
		}
		GWPlayer[i].blue_count = 0;
		GWPlayer[i].red_count = 0;
		GWPlayer[i].question_count = 0;
		GWPlayer[i].fortune_count = 0;
		GWPlayer[i].bowser_count = 0;
		GWPlayer[i].battle_count = 0;
		GWPlayer[i].mushroom_count = 0;
		GWPlayer[i].warp_count = 0;
		GWPlayer[i].coins_mg = 0;
		GWPlayer[i].coins_total = 0;
		GWPlayer[i].coins_max = 0;
		GWPlayer[i].stars_max = 0;
		GWPlayer[i].coins_battle = 0;
		GWPlayer[i].unk_26 = 0;
		GWPlayer[i].coins_mg_gain = 0;
		GWPlayer[i].items[0] = -1;
		GWPlayer[i].items[1] = -1;
		GWPlayer[i].items[2] = -1;
		if(!BoardPartyFlagGet() || _CheckFlag(FLAG_ID_MAKE(1, 11))) {
			GWStarsSet(i, 0);
		} else {
			GWStarsSet(i, BoardHandicapGet(i));
		}
	}
}

void BoardStoryConfigSet(s32 mg_type, s32 diff_story)
{
	GWSystem.party = 0;
	GWSystem.team = 0;
	GWSystem.diff_story = diff_story;
	GWSystem.bonus_star = 0;
	GWSystem.mg_type = mg_type;
	GWPlayer[0].handicap = 0;
	GWPlayer[1].handicap = 0;
	GWPlayer[2].handicap = 0;
	GWPlayer[3].handicap = 0;
	GWSystem.max_turn = 15;
	memset(GWPlayer, 0, 4*sizeof(PlayerState));
	_ClearFlag(FLAG_ID_MAKE(0, 2));
	_ClearFlag(FLAG_ID_MAKE(0, 3));
	_ClearFlag(FLAG_ID_MAKE(0, 4));
	_ClearFlag(FLAG_ID_MAKE(0, 5));
	_ClearFlag(FLAG_ID_MAKE(0, 6));
	_ClearFlag(FLAG_ID_MAKE(0, 7));
	_ClearFlag(FLAG_ID_MAKE(1, 11));
	_SetFlag(FLAG_ID_MAKE(0, 11));
	_SetFlag(FLAG_ID_MAKE(1, 10));
}

void BoardPartyConfigSet(s32 team, s32 bonus_star, s32 mg_type, s32 max_turn, s32 p1_handicap, s32 p2_handicap, s32 p3_handicap, s32 p4_handicap)
{
	GWSystem.party = 1;
	GWSystem.team = team;
	GWSystem.diff_story = 0;
	GWSystem.bonus_star = bonus_star;
	GWSystem.mg_type = mg_type;
	GWSystem.max_turn = max_turn;
	memset(GWPlayer, 0, 4*sizeof(PlayerState));
	GWPlayer[0].handicap = p1_handicap;
	GWPlayer[1].handicap = p2_handicap;
	GWPlayer[2].handicap = p3_handicap;
	GWPlayer[3].handicap = p4_handicap;
	_ClearFlag(FLAG_ID_MAKE(1, 11));
	_SetFlag(FLAG_ID_MAKE(0, 11));
	_SetFlag(FLAG_ID_MAKE(1, 10));
}

static void DestroyMainFunc(void)
{
	boardMainProc = NULL;
}

static void MainFunc(void)
{
	s32 i;
	s32 fade_enable, turn_cont, fade_type;
	fade_enable = 0;
	turn_cont = 0;
	BoardPauseEnableSet(1);
	if(_CheckFlag(FLAG_ID_MAKE(0, 10))) {
		_ClearFlag(FLAG_ID_MAKE(0, 10));
		_SetFlag(FLAG_ID_MAKE(1, 16));
		BoardKill();
		HuPrcSleep(-1);
	}
	_ClearFlag(FLAG_ID_MAKE(0, 10));
	BoardTutorialInit();
	if(_CheckFlag(FLAG_ID_MAKE(1, 11))) {
		BoardTutorialWorkSave();
		BoardTutorialPlayerInit();
		GWSystem.mess_speed = 1;
		GWSystem.mess_delay = 32;
	}
	CreateBoard();
	if(!_CheckFlag(FLAG_ID_MAKE(1, 1))) {
		GWSystem.player_curr = -1;
		fn_800A6EE4();
		GWSystem.player_curr = 0;
		fade_enable = 1;
		_SetFlag(FLAG_ID_MAKE(1, 1));
	} else {
		fade_enable = 0;
	}
	if(BoardIsTurnCont()) {
		turn_cont = 1;
	}
	if((int)(GWSystem.max_turn-GWSystem.turn) < 5 && GWSystem.player_curr == 0 && !turn_cont) {
		if(!_CheckFlag(FLAG_ID_MAKE(0, 8))) {
			fn_800A9708();
			_SetFlag(FLAG_ID_MAKE(0, 8));
		} else {
			BoardLast5GfxInit();
		}
	}
	if(!turn_cont) {
		fade_type = 1;
	} else {
		fade_type = 0;
	}
	_ClearFlag(FLAG_ID_MAKE(1, 28));
	do {
		BoardStatusShowSetAll(1);
		if(BoardCurrGet() == 5 && GWSystem.player_curr == 0 && !turn_cont && boardTurnFunc) {
			GWSystem.player_curr = -1;
			boardTurnFunc();
			GWSystem.player_curr = 0;
		}
		fn_80070D84();
		for(i=GWSystem.player_curr; i<4; i++) {
			if(BoardCurrGet() == 7 || BoardCurrGet() == 8) {
				if((int)(GWSystem.max_turn-GWSystem.turn) < 5 && i == 0 && !turn_cont) {
					BoardLast5GfxInit();
					_SetFlag(FLAG_ID_MAKE(0, 8));
				}
			}
			if(_CheckFlag(FLAG_ID_MAKE(1, 6))) {
				BoardPlayerTurnExec(i);
			} else {
				if(!turn_cont) {
					BoardCameraVisibleSet(0);
					GWSystem.player_curr = i;
					BoardCameraTargetModelSet(i);
					BoardCameraMotionWait();
					{
						Vec pos;
						BoardSpacePosGet(0, GWPlayer[i].space_curr, &pos);
						BoardPlayerPosSetV(i, &pos);
					}
					while(WipeStatGet()) {
						HuPrcVSleep();
					}
					if(!fade_enable) {
						if(!fade_type) {
							WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSS, 30);
							while(WipeStatGet()) {
								HuPrcVSleep();
							}
						} else {
							fade_type = 0;
							WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 21);
							while(WipeStatGet()) {
								HuPrcVSleep();
							}
						}
					} else {
						fade_enable = 0;
					}
					BoardPlayerTurnExec(i);
				}
			}
			turn_cont = 0;
			if(_CheckFlag(FLAG_ID_MAKE(1, 11))) {
				BoardTutorialHookExec(9, 0);
			}
			if(i != 3 || _CheckFlag(FLAG_ID_MAKE(1, 11))) {
				WipeColorSet(255, 255, 255);
				WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSS, 1);
				while(WipeStatGet()) {
					HuPrcVSleep();
				}
				BoardPlayerCurrMoveAwayStart(GWPlayer[i].space_curr, 1);
				fade_type = 0;
			} else {
				if(BoardCurrGet() == 7 || BoardCurrGet() == 8) {
					if(GWSystem.turn != GWSystem.max_turn) {
						WipeColorSet(255, 255, 255);
						WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSS, 1);
						while(WipeStatGet()) {
							HuPrcVSleep();
						}
						BoardPlayerCurrMoveAwayStart(GWPlayer[i].space_curr, 1);
						fade_type = 0;
					}
				} else {
					WipeColorSet(0, 0, 0);
					WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 21);
					while(WipeStatGet()) {
						HuPrcVSleep();
					}
				}
			}
			BoardPlayerPostTurnHookExec(i);
		}
		if(BoardCurrGet() == 7 || BoardCurrGet() == 8) {
			GWSystem.player_curr = 0;
			if(BoardTurnNext()) {
				fn_80070EE8(0, 500);
				BoardKill();
				HuPrcEnd();
				HuPrcSleep(-1);
			}
		} else {
			_SetFlag(FLAG_ID_MAKE(1, 28));
			_SetFlag(FLAG_ID_MAKE(1, 14));
			BoardPauseEnableSet(1);
			_CheckFlag(FLAG_ID_MAKE(1, 9));
			if(_CheckFlag(FLAG_ID_MAKE(2, 0)) || _CheckFlag(FLAG_ID_MAKE(1, 11)) ) {
				for(i=0; i<4; i++) {
					GWPlayer[i].color = 0;
				}
				GWSystem.player_curr = (GWSystem.player_curr+1)&3;
			} else {
				fn_800A1A34();
				HuPrcSleep(-1);
			}
		}
	} while(1);
}

BOOL BoardTurnNext(void)
{
	s32 i;
	for(i=0; i<4; i++) {
		GWPlayer[i].color = 0;
	}
	GWSystem.turn++;
	if(GWSystem.turn > GWSystem.max_turn) {
		return 1;
	} else {
		return 0;
	}
}

void BoardNextOvlSet(OverlayID overlay)
{
	nextOvl = overlay;
	fn_80070EE8(0, 1000);
	BoardKill();
}

BOOL BoardIsStarted(void)
{
	if(_CheckFlag(FLAG_ID_MAKE(1, 2)) || _CheckFlag(FLAG_ID_MAKE(1, 3)) || _CheckFlag(FLAG_ID_MAKE(1, 4)) || _CheckFlag(FLAG_ID_MAKE(1, 5)) || _CheckFlag(FLAG_ID_MAKE(1, 6))) {
		return 1;
	} else {
		return 0;
	}
}

static void CreateBoard(void)
{
	
}

static void DestroyBoard(void)
{
	
}

u32 BoardRand(void)
{
	boardRandSeed = (boardRandSeed*0x19660D)+(0x3C6EF35F);
	return boardRandSeed;
}

u32 BoardRandMod(u32 value)
{
	return (BoardRand() & 0x7FFFFFFF)%value;
}

float BoardRandFloat(void)
{
	float value;
	*((u32 *)&value) = (BoardRand() & 0x7FFFFF)|0x3F800000;
	return value-1.0f;
}

float BoardVecDistXZCalc(Vec *vec1, Vec *vec2)
{
	float x = vec1->x-vec2->x;
	float z = vec1->z-vec2->z;
	return sqrtf((x*x)+(z*z));
}

s32 BoardVecMaxDistXZCheck(Vec *vec1, Vec *vec2, float max_dist)
{
	float z = vec1->z-vec2->z;
	float x = vec1->x-vec2->x;
	float dist = sqrtf((x*x)+(z*z));
	if(dist <= max_dist) {
		return 1;
	} else {
		return 0;
	}
}

s32 BoardVecMinDistCheck(Vec *vec1, Vec *vec2, float min_dist)
{
	Vec temp;
	Mtx temp_mtx;
	VECSubtract(vec1, vec2, &temp);
	if(VECSquareMag(&temp) >= (min_dist*min_dist)) {
		return 0;
	} else {
		return 1;
	}
}

s32 BoardDataDirReadAsync(s32 data_num)
{
	s32 status = HuDataDirReadAsync(data_num);
	return status;
}

void BoardDataAsyncWait(s32 status)
{
	if(status == -1) {
		return;
	}
	while(!HuDataGetAsyncStat(status)) {
		HuPrcVSleep();
	}
}