#include "game/board/player.h"

//// #include "game/board/ui.h"
extern void BoardStatusHammerShowSet(s32, s32);
extern void BoardYourTurnExec(s32);
extern s32 BoardItemUseExec(s32);
//// #include "game/board/main.h"
extern f32 BoardDAngleCalc(f32);
//// #include "game/board/model.h"
extern s16 BoardModelCreateCharacter(s32, s32, s32*, s32);
extern void BoardModelExistCheck(s16, s32);
extern void BoardModelExistDupe(s16, s32);
extern void BoardModelCameraSet(s16, u16);
extern void BoardItemStatusKill(s32);
extern void BoardModelAmbSet(s16, f32, f32, f32);
extern void BoardModelPosSetV(s16, Vec*);
extern void BoardModelPosSet(s16, f32, f32, f32);
extern s32 BoardModelPosGet(s16, Vec*);
extern void BoardModelRotSetV(s16, Vec*);
extern void BoardModelRotSet(s16, f32, f32, f32);
extern s32 BoardModelRotGet(s16, Vec*);
extern void BoardModelRotYSet(s16, f32);
extern f32 BoardModelRotYGet(s16);
extern void BoardModelScaleSetV(s16, Vec*);
extern void BoardModelScaleSet(s16, f32, f32, f32);
extern void BoardModelScaleGet(s16, s32*);
extern void BoardModelVoiceEnableSet(s16, s32, s32);
extern s32 BoardModelMotionCreate(s16, s32);
extern void BoardModelMotionKill(s16, s32);
extern s32 BoardModelMotionEndCheck(s16);
extern s32 BoardModelMotionStart(s16, s32, s32);
extern s32 BoardModelMotionShiftSet(s16, s32, f32, f32, u32);
extern void BoardModelMotionSpeedSet(s16, f32);
extern void BoardModelMotionTimeSet(s16, f32);
extern f32 BoardModelMotionTimeGet(s16);
extern f32 BoardModelMotionMaxTimeGet(s16);
extern void BoardModelMotionTimeRangeSet(s16, s32, s32);
extern void BoardModelAttrSet(s16, s32);
extern void BoardModelAttrReset(s16, s32);
//// #include "game/board/tutorial.h"
extern BoardTutorialHookExec(s16, s32);
//// #include "game/board/com.h"
extern void BoardComUseItemSet(s32, s32);
//// #include "game/board/overhead.h"
extern void BoardViewOverheadExec(s32);
extern void BoardViewMapExec(s32);
//// #include "game/board/roll.h"
extern s32 fn_80085CC8(s32);
extern void fn_80085EB4(void);
//// #include "game/chrman.h"
extern void CharModelDataClose(s16);
extern void CharModelStepTypeSet(s16, s32);
//// #include "game/board/pad.h"
extern s8 HuPadStkX[4];
extern s8 HuPadStkY[4];
extern u16 HuPadBtnDown[4];
extern u8 HuPadDStk[4];
//// #include "game/board/view.h"
void BoardViewMapExec(s32);
////

static void UpdateJunctionGfx(omObjData*);
static void StopJunctionPlayer(s32);
static void RestoreJunction(f32, s32);
static s32 GetDefaultDirection(f32, f32*, s32);
//...
s32 BoardPlayerAutoSizeGet(s32);
void BoardPlayerAutoSizeSet(s32, s32);
void BoardPlayerCopyMat(s32);
void BoardBowserSuitKill(s32);
void SetRollPlayerSize(s32);
void BoardDiceDigit2DUpdateEnable(s32);
void BoardPlayerMoveTo(s32, s16);
void BoardPlayerZoomRestore(s32);
void BoardRotateDiceNumbers(s32);
void BoardBowserSuitMotionSetWait(void);
void BoardBowserSuitPlayerModelKill(void);
void BoardDiceDigit2DShowSet(s32);
s32 DoDebugMove(s32, s16*);
s32 DoSparkSpace(s32, s16*);
s32 ExecJunction(s32, s16*);
s32 MegaPlayerPassFunc(s32, s16);
s32 BoardPlayerMotBlendCheck(s32);

typedef struct bitcopy {
    struct {
        u8 field00_bit0 : 1;
        u8 field00_bit1 : 2;
        u8 field00_bit3 : 2;
        u8 field00_bit5 : 2;
        u8 field00_bit7 : 1;
    };
    u8 unk_01;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06[6];
} bitcopy;

static HsfMaterial *playerMatCopy[4];
static s32 (*postTurnHook[4])();
static s32 (*preTurnHook[4])();

s16 boardPlayerMdl[4];
static s16 playerMot[4];
static s16 junctionArrowRot[4];
static s8 rollType;
static omObjData* junctionObj;
static s32 junctionMask;
static s32 rollResized;

static s16 suitMdl = -1;
static s16 suitPlayerMdl = -1;
static s16 suitCurrMot = -1;

static s32 diceJumpObj[4] = {0, 0, 0, 0};
static s32 motDoneF[4] = {0, 0, 0, 0};
static s16 bowserSuitMot[5] = {-1, -1, -1, -1, -1};
char* lbl_8013993C[] = {
    "eye1",
    "eye2",
    "eye1",
    "eye2",
    "mat14",
    "mat16",
    "eye1",
    "eye2",
    "Clswario_eye_l1_AUTO14",
    "Clswario_eye_l1_AUTO15",
    "m_donkey_eye4",
    "m_donkey_eye5",
    "mat65",
    "mat66",
    "Clswaluigi_eye_l1_AUTO1",
    "Clswaluigi_eye_l1_AUTO2",
};

s32 lbl_8013997C[] = {
    0x10D,
    0x14D,
    0x18D,
    0x1CD,
    0x20D,
    0x24D,
    0x28D,
    0x2CD,
};

static s32 boardMotTbl[] = {
    0x5F0035, 0x1A0035, 0x6D0035, 0x8A0035,
    0x850035, 0x110035, 0x0D0035, 0x810035,
};

static s32 boardMotRevTbl[] = {
    0x5F0036, 0x1A0036, 0x6D0036, 0x8A0036,
    0x850036, 0x110036, 0x0D0036, 0x810036,
};

static s32 bowserSuitCharMdlTbl[] = {
    0x40000, 0x40003, 0x40006, 0x40009,
    0x4000C, 0x4000F, 0x40012, 0x40015,
};

static s32 bowserSuitMotTbl[] = {
    0x40019, 0x4001A, 0x4001B, 0x4001E,
    0x4001F, 0x70095, 0x70096, 0x70097,
    0x70098, 0x70099, 0x7009A, 0x7009B,
    0x7009C,
};

static s32 boardSparkSfxTbl[] = {
    0x128, 0x168, 0x1A8, 0x1E8,
    0x228, 0x268, 0x2A8, 0x2E8,
};

static s32 boardSparkSfxTblAlt[] = {
    0x123, 0x163, 0x1A3, 0x1E3,
    0x223, 0x263, 0x2A3, 0x2E3,
};

static s32 megaSquishObj[] = {
    0, 0, 0, 0,
};

static s32 megaSquishSfxTbl[] = {
    0x128, 0x168, 0x1A8, 0x1E8,
    0x228, 0x268, 0x2A8, 0x2E8,
};

inline PlayerState* GetPlayer(s32 index) {
    return &GWPlayer[index];
}

inline s16 GetBoardPlayer(s32 index) {
    PlayerState *player = GetPlayer(index);
    return boardPlayerMdl[player->player_idx];
}

s32 BoardRollTypeGet(void) {
    return rollType;
}

void BoardRollTypeSet(s32 type) {
    rollType = type;
}

s32 BoardPlayerGetCharMess(s32 player) {
    s32 charMess[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    
    return charMess[GWPlayer[player].character];
}

char* BoardPlayerGetCharName(s32 player) {
    char* charNames[8] = {"Mario", "Luigi", "Peach", "Yoshi", "Wario", "Donky", "Daisy", "Waluigi"};
    return charNames[GWPlayer[player].character];
}

s32 BoardPlayerIsAllCom(void) {
    if ((GWPlayer[0].com != 0) && (GWPlayer[1].com != 0) && (GWPlayer[2].com != 0) && (GWPlayer[3].com != 0)) {
        return 1;
    }
    return 0;
}

void BoardPlayerInit(void) {
    s32 temp_r30;
    s32 var_r31;

    if (BoardIsStarted() == 0) {
        GWSystem.player_curr = 0;
        temp_r30 = BoardSpaceFlagPosGet(0, 0x80000000, 0);
        
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            GWPlayer[var_r31].space_curr = temp_r30;
            BoardPlayerCornerPosSet(var_r31);
            BoardPlayerSizeSet(var_r31, 0);
            GWPlayer[var_r31].color = 0;
            GWPlayer[var_r31].bowser_suit = 0;
            GWPlayer[var_r31].field00_bit9 = 0;
            GWPlayer[var_r31].field08_bit3 = 0;
        }
        return;
    }
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        BoardPlayerCornerPosSet(var_r31);
        if (BoardPlayerAutoSizeGet(var_r31) != 0) {
            BoardPlayerAutoSizeSet(var_r31, BoardPlayerAutoSizeGet(var_r31));
            BoardStatusHammerShowSet(var_r31, 0);
        }
    }
}

void BoardPlayerModelInit(void) {
    s32 sp64[14];
    s32 var_r31;
    s32 var_r30;
    s32 temp_r29;
    s32 temp_r25;
    s32 temp_r24;
    s16 temp_r3;
    s32 temp_r4;
    PlayerState* temp_r22;
    PlayerState* temp_r27;

    s32 ro0[8] =  { 0x5E0000, 0x190000, 0x6C0000, 0x890000, 0x840000, 0x100000, 0xC0000, 0x800000 };
    s32 ro1[8] =  { 0x5F0000, 0x1A0000, 0x6D0000, 0x8A0000, 0x850000, 0x110000, 0xD0000, 0x810000 };
    u16 ro2[13] = { 0, 2, 3, 5, 6, 22, 23, 24, 27, 31, 47, 72, 73 };
    
    memset(&boardPlayerMdl, 0, 8);
    suitMdl = -1;
    suitPlayerMdl = -1;
    if ((_CheckFlag(0x10005U) != 0) || ((_CheckFlag(0x10006U) != 0) && (temp_r4 = GWSystem.board, temp_r4 == 5))) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            temp_r25 = GWPlayer[var_r31].field08_bit11;
            GWPlayer[var_r31].team = temp_r25;
            GWPlayerCfg[var_r31].group = temp_r25;
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        preTurnHook[var_r31] = 0;
        postTurnHook[var_r31] = 0;
        motDoneF[var_r31] = 0;
        diceJumpObj[var_r31] = 0;
        temp_r22 = &GWPlayer[var_r31];
        temp_r27 = temp_r22;
        temp_r29 = GWPlayerCfg[var_r31].character;
        temp_r27->player_idx = var_r31;
        GWPlayer[var_r31].character = temp_r29;
        GWPlayerCfg[var_r31].character = temp_r29;
        
        for (var_r30 = 0; var_r30 < 0xD; var_r30++) {
            sp64[var_r30] = ro1[temp_r29] | ro2[var_r30];
        }
        sp64[var_r30] = -1;
        temp_r3 = BoardModelCreateCharacter(temp_r29, ro0[temp_r29], sp64, 0);
        boardPlayerMdl[var_r31] = temp_r3;
        BoardPlayerCopyMat(var_r31);
        playerMot[var_r31] = 1;
        BoardModelMotionStart(temp_r3, playerMot[var_r31], 0x40000001);
        if (BoardIsStarted() == 0) {
            
            for (var_r30 = 0; var_r30 < 3; var_r30++) {
                temp_r27->items[var_r30] = -1;
            }
            temp_r24 = GWPlayerCfg[var_r31].group;
            GWPlayer[var_r31].team = temp_r24;
            GWPlayerCfg[var_r31].group = temp_r24;
        }
        GWPlayer[var_r31].show_next = 1;
        GWPlayer[var_r31].bowser_suit = 0;
        BoardModelExistDupe(temp_r3, 1);
        BoardModelExistCheck(temp_r3, 1);
        fn_8006DDE8(temp_r3, -1.0f);
        GWPlayer[var_r31].com = GWPlayerCfg[var_r31].iscom;
        GWPlayerCfg[var_r31].iscom = GWPlayerCfg[var_r31].iscom;
        GWPlayer[var_r31].port = GWPlayerCfg[var_r31].pad_idx;
        GWPlayerCfg[var_r31].pad_idx = GWPlayerCfg[var_r31].pad_idx;
        GWPlayer[var_r31].diff = GWPlayerCfg[var_r31].diff;
        GWPlayerCfg[var_r31].diff = GWPlayerCfg[var_r31].diff;
        temp_r27->space_prev = -1;
        CharModelDataClose(GWPlayer[var_r31].character);
    }
    CharModelLayerSetAll(2);
}

void BoardPlayerModelKill(void) {
    s32 var_r31;
    PlayerState* temp_r30;
    PlayerState* temp_r29;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        temp_r30 = BoardPlayerGet(var_r31);
        if (boardPlayerMdl[temp_r30->player_idx] != -1) {
            BoardModelKill(boardPlayerMdl[temp_r30->player_idx]);
            boardPlayerMdl[temp_r30->player_idx] = -1;
        }
        if (playerMatCopy[var_r31] != 0) {
            HuMemDirectFree(playerMatCopy[var_r31]);
            playerMatCopy[var_r31] = 0;
        }
        BoardBowserSuitKill(var_r31);
    }
}

void BoardPlayerLayerSet(s32 arg0, s32 arg1) {
    BoardModelLayerSet(BoardPlayerModelGet(arg0), arg1);
}

void BoardPlayerCameraSet(s32 arg0, u16 arg1) {
    BoardModelCameraSet(BoardPlayerModelGet(arg0), arg1);
}

void fn_80062A40(s32 arg0, f32 arg8) {
    fn_8006DDE8(BoardPlayerModelGet(arg0), arg8);
}

void BoardPlayerExistCheck(s32 arg0, s32 arg1) {
    if (arg1 == 0) {
        BoardModelExistCheck(BoardPlayerModelGet(arg0), 0);
    } else {
        BoardModelExistCheck(BoardPlayerModelGet(arg0), 1);
    }
}

s32 BoardPlayerItemAdd(s32 arg0, s32 arg1) {
    PlayerState* var_r30;
    s32 var_r29;
    s32 var_r31;

    var_r29 = -1;
    var_r30 = BoardPlayerGet(arg0);
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        if (GWPlayer[arg0].items[var_r31] == -1) {
            HuAudFXPlay(0x360);
            var_r30->items[var_r31] = arg1;
            BoardItemStatusKill(arg0);
            var_r29 = var_r31;
            break;
        }
    }
    return var_r29;
}

s32 BoardPlayerItemRemove(s32 arg0, s32 arg1) {
    s32 temp_r29;
    PlayerState* temp_r28;

    temp_r28 = BoardPlayerGet(arg0);
    temp_r29 = temp_r28->items[arg1];
    if (temp_r28->items[arg1] == -1) {
        return temp_r29;
    }
    if (arg1 == 0) {
        temp_r28->items[0] = temp_r28->items[1];
    }
    if ((arg1 == 1) || (arg1 == 0)) {
        temp_r28->items[1] = temp_r28->items[2];
    }
    temp_r28->items[2] = -1;
    HuAudFXPlay(0x363);
    BoardItemStatusKill(arg0);
    return temp_r29;
}

s32 BoardPlayerItemFind(s32 arg0, s32 arg1) {
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        if (arg1 == GWPlayer[arg0].items[var_r31]) {
            return var_r31;
        }
    }
    
    return -1;
}

s32 BoardPlayerItemCount(s32 arg0) {
    s32 var_r30;
    s32 var_r31;

    for (var_r31 = 0, var_r30 = var_r31; var_r31 < 3; var_r31++) {
        if (GWPlayer[arg0].items[var_r31] != -1) {
            var_r30++;
        }
    }
    
    return var_r30;
}

void BoardPlayerCornerPosSet(s32 arg0) {
    Vec sp8;

    BoardPlayerCornerPosGet(arg0, &sp8);
    BoardPlayerPosSetV(arg0, &sp8);
}

void BoardPlayerCornerPosGet(s32 arg0, Point3d* arg1) {
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 temp_r28;

    if (arg1 != 0) {
        temp_r28 = GWPlayer[arg0].space_curr;
        var_r31 = GWSystem.player_curr;
        if (var_r31 == -1) {
            var_r31 = 0;
        }
        for (var_r30 = 0, var_r29 = var_r30; var_r30 < 4; var_r31 = (var_r31 + 1) & 3, var_r30++) {
            if (var_r31 == arg0) break;
            if (temp_r28 == GWPlayer[var_r31].space_curr) {
                var_r29 += 1;
            }
        }
        BoardSpaceCornerPosGet(temp_r28, var_r29, arg1);
    }
}

void BoardPlayerAmbSet(s32 arg0, f32 arg8, f32 arg9, f32 argA) {
    BoardModelAmbSet(BoardPlayerModelGet(arg0), arg8, arg9, argA);
}

void BoardPlayerMtxSet(s32 arg0, Mtx *arg1) {
    BoardModelMtxSet(BoardPlayerModelGet(arg0), arg1);
}

void BoardPlayerPosSetV(s32 arg0, Vec* arg1) {
    BoardModelPosSetV(BoardPlayerModelGet(arg0), arg1);

    if (GWPlayer[arg0].bowser_suit != 0) {
        BoardModelPosSetV(suitMdl, arg1);
    }
}

void BoardPlayerPosSet(s32 arg0, f32 arg8, f32 arg9, f32 argA) {
    BoardModelPosSet(BoardPlayerModelGet(arg0), arg8, arg9, argA);
    
    if (GWPlayer[arg0].bowser_suit != 0) {
        BoardModelPosSet(suitMdl, arg8, arg9, argA);
    }
}

void BoardPlayerPosGet(s32 arg0, Vec* arg1) {
    BoardModelPosGet(BoardPlayerModelGet(arg0), arg1);
}

void BoardPlayerRotSetV(s32 arg0, Vec* arg1) {
    BoardModelRotSetV(BoardPlayerModelGet(arg0), arg1);

    if (GWPlayer[arg0].bowser_suit != 0) {
        BoardModelRotSetV(suitMdl, arg1);
    }
}

void BoardPlayerRotSet(s32 arg0, f32 arg8, f32 arg9, f32 argA) {
    BoardModelRotSet(BoardPlayerModelGet(arg0), arg8, arg9, argA);
    
    if (GWPlayer[arg0].bowser_suit != 0) {
        BoardModelRotSet(suitMdl, arg8, arg9, argA);
    }
}

void BoardPlayerRotGet(s32 arg0, Vec* arg1) {
    BoardModelRotGet(BoardPlayerModelGet(arg0), arg1);
}

void BoardPlayerRotYSet(s32 arg0, f32 arg8) {
    if (arg8 < 0.0f) {
        arg8 += 360.0f;
    }
    if (arg8 > 360.0f) {
        arg8 -= 360.0f;
    }
    BoardModelRotYSet(BoardPlayerModelGet(arg0), arg8);
    if (GWPlayer[arg0].bowser_suit != 0) {
        BoardModelRotYSet(suitMdl, arg8);
    }
}

f32 BoardPlayerRotYGet(s32 arg0) {
    f32 var_f31;

    if (GWPlayer[arg0].bowser_suit != 0) {
        var_f31 = BoardModelRotYGet(suitMdl);
    } else {
        var_f31 = BoardModelRotYGet(BoardPlayerModelGet(arg0));
    }
    return var_f31;
}

void BoardPlayerScaleSetV(s32 arg0, Vec* arg1) {
    BoardModelScaleSetV(BoardPlayerModelGet(arg0), arg1);
}

void BoardPlayerScaleSet(s32 arg0, f32 arg8, f32 arg9, f32 argA) {
    BoardModelScaleSet(BoardPlayerModelGet(arg0), arg8, arg9, argA);
}

void BoardPlayerScaleGet(s32 arg0, s32 *arg1) {
    BoardModelScaleGet(BoardPlayerModelGet(arg0), arg1);
}

s16 BoardPlayerCurrMotionGet(s32 arg0) {
    PlayerState* player = BoardPlayerGet(arg0);
    
    return playerMot[player->player_idx];
}

void BoardPlayerVoiceEnableSet(s32 arg0, s32 arg1, s32 arg2) {
    BoardModelVoiceEnableSet(BoardPlayerModelGet(arg0), arg1, arg2);
}

s32 BoardPlayerMotionCreate(s32 arg0, s32 arg1) {
    return BoardModelMotionCreate(BoardPlayerModelGet(arg0), arg1);
}

void BoardPlayerMotionKill(s32 arg0, s32 arg1) {
    BoardModelMotionKill(BoardPlayerModelGet(arg0), arg1);
}

s32 BoardPlayerMotionEndCheck(s32 arg0) {
    return BoardModelMotionEndCheck(BoardPlayerModelGet(arg0));
}

void BoardPlayerMotionEndWait(s32 arg0) {
    while (BoardModelMotionEndCheck(BoardPlayerModelGet(arg0)) == 0) {
        HuPrcVSleep();
    }
}

void BoardPlayerMotionStart(s32 arg0, s32 arg1, s32 arg2) {
    PlayerState* player;
    s32 temp_r29;
    
    player = BoardPlayerGet(arg0);
    if (arg1 == 0) {
    }
    if (arg1 != playerMot[player->player_idx]) {
        temp_r29 = BoardModelMotionStart(BoardPlayerModelGet(arg0), arg1, arg2);
        if (temp_r29 == 0) {
            playerMot[player->player_idx] = arg1;
        }
    }
}

void BoardPlayerMotionShiftSet(s32 arg0, s32 arg1, f32 arg8, f32 arg9, u32 arg2) {
    PlayerState* player;
    s32 temp_r29;
    
    player = BoardPlayerGet(arg0);
    if (arg1 == 0) {
    }
    if (arg1 != playerMot[player->player_idx]) {
        temp_r29 = BoardModelMotionShiftSet(BoardPlayerModelGet(arg0), arg1, arg8, arg9, arg2);
        if (temp_r29 == 0) {
            playerMot[player->player_idx] = arg1;
        }
    }
}

void BoardPlayerMotionSpeedSet(s32 arg0, f32 arg8) {
    BoardModelMotionSpeedSet(BoardPlayerModelGet(arg0), arg8);
}

void BoardPlayerMotionTimeSet(s32 arg0, f32 arg8) {
    BoardModelMotionTimeSet(BoardPlayerModelGet(arg0), arg8);
}

f32 BoardPlayerMotionTimeGet(s32 arg0) {
    BoardModelMotionTimeGet(BoardPlayerModelGet(arg0));
}

f32 BoardPlayerMotionMaxTimeGet(s32 arg0) {
    BoardModelMotionMaxTimeGet(BoardPlayerModelGet(arg0));
}

void BoardPlayerMotionTimeRangeSet(s32 arg0, f32 arg8, f32 arg9) {
    BoardModelMotionTimeRangeSet(BoardPlayerModelGet(arg0), arg8, arg9);
}

void BoardPlayerModelAttrSet(s32 arg0, s32 arg1) {
    BoardModelAttrSet(BoardPlayerModelGet(arg0), arg1);
}

void BoardPlayerModelAttrReset(s32 arg0, s32 arg1) {
    BoardModelAttrReset(BoardPlayerModelGet(arg0), arg1);
}

void BoardPlayerCoinsSet(s32 arg0, s32 arg1) {
    GWCoinsSet(arg0, arg1);
}

s32 BoardPlayerCoinsGet(s32 arg0) {
    return GWCoinsGet(arg0);
}

void BoardPlayerCoinsAdd(s32 arg0, s32 arg1) {
    PlayerState* player;
    s16 coins;

    player = BoardPlayerGet(arg0);
    if ((arg1 > 0) && (player->coins_total < 0x3E7)) {
        player->coins_total += arg1;
        if (player->coins_total > 0x3E7) {
            player->coins_total = 0x3E7;
        }
    }
    BoardPlayerCoinsSet(arg0, arg1 + BoardPlayerCoinsGet(arg0));
}

void BoardPlayerStarsAdd(s32 arg0, s32 arg1) {
    GWStarsSet(arg0, (arg1 + GWStarsGet(arg0)));
}

void BoardPlayerSizeSet(s32 arg0, s32 arg1) {
    PlayerState* temp_r27;
    Vec temp_r4[3] = { { 1, 1, 1 }, { 0.3, 0.3, 0.3 }, { 2.5, 2.5, 2.5 } };

    temp_r27 = BoardPlayerGet(arg0);
    temp_r27->size = arg1;
    if (arg1 == 2) {
        CharModelStepTypeSet(GWPlayer[arg0].character, 4);
    } else if (arg1 == 1) {
        CharModelStepTypeSet(GWPlayer[arg0].character, 5);
    } else {
        CharModelStepTypeSet(GWPlayer[arg0].character, 0);
    }
    BoardModelScaleSetV(BoardPlayerModelGet(arg0), &temp_r4[arg1]);
}

s32 BoardPlayerSizeGet(s32 idx) {
    PlayerState* player;

    player = BoardPlayerGet(idx);
    if(!player) {
        return;
    }
    return player->size;
}

s32 BoardPlayerSameTeamFind(s32 arg0) {
    s32 var_r31;
    s32 team2;
    s32 team;
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (var_r31 == arg0) continue;
        team2 = GWPlayer[var_r31].team;
        team = GWPlayer[arg0].team;
        if (team == team2) break;
    }
    return var_r31;
}

s32 BoardPlayerTeamFind(s32 arg0) {
    s32 var_r31;
    s32 team2;
    s32 team;
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (var_r31 == arg0) continue;
        team2 = GWPlayer[var_r31].team;
        team = GWPlayer[arg0].team;
        if (team != team2) break;
    }
    return var_r31;
}

s32 BoardPlayerRankCalc(s32 player) {
    s32 coins;
    s32 rank;
    s32 i;
    s32 score[4];

    for (i = 0; i < 4; i++) {
        coins = GWCoinsGet(i);
        score[i] = coins | (GWStarsGet(i) << 0xA);
    }
    for (rank = 0, i = 0; i < 4; i++) {
        if ((i != player) && (score[player] < score[i])) {
            rank++;
        }
    }
    return rank;
}

void BoardPlayerPreTurnHookSet(s32 arg0, s32 (*arg1)()) {
    preTurnHook[arg0] = arg1;
}

void BoardPlayerPostTurnHookSet(s32 arg0, s32 (*arg1)()) {
    postTurnHook[arg0] = arg1;
}

void BoardPlayerTurnExec(s32 arg0) {
    BoardPauseEnableSet(1);
    BoardComUseItemSet(arg0, -1);
    GWSystem.field31_bit4 = 0xF;
    _ClearFlag(0x10016);
    _ClearFlag(0x1000E);
    BoardCameraMoveSet(1);
    if (_CheckFlag(0x10006U) == 0) {
        BoardCameraViewSet(2);
        omVibrate((s16) arg0, 0xC, 4, 2);
        rollType = -1;
        BoardYourTurnExec(arg0);
        rollResized = 0;
        SetRollPlayerSize(arg0);
        if (preTurnHook[arg0] != 0U) {
            if (preTurnHook[arg0]() != 0) {
                preTurnHook[arg0] = 0;
            }
        }
        if (_CheckFlag(0x1000BU) != 0) {
            BoardTutorialHookExec(5, 0);
        }
        BoardPlayerTurnRollExec(arg0);
    } else {
        BoardCameraViewSet(1);
        BoardCameraMotionWait();
    }
    BoardPlayerTurnMoveExec(arg0);
}

static inline s32 PlayerItemUseExec(s32 arg0) {
    return BoardItemUseExec(arg0);
}

void BoardPlayerTurnRollExec(s32 arg0) {
    s32 temp_r28;
    s32 temp_r30;

    GWPlayer[arg0].roll = 0;
    GWPlayer[arg0].field08_bit7 = 1;
    BoardPauseEnableSet(0);
    do {
        temp_r30 = fn_80085CC8(arg0);
        switch (temp_r30) {
        case -2:
            BoardPauseEnableSet(1);
            fn_80085EB4();
            BoardCameraTargetPlayerSet(arg0);
            BoardCameraMotionWait();
            rollType = PlayerItemUseExec(arg0);
            if (BoardRollTypeGet() == 0xC) {
                _SetFlag(0x10016);
                BoardSpaceLandExec(arg0, GWPlayer[arg0].space_curr);
                BoardCameraMoveSet(1);
                BoardCameraViewSet(2);
                _ClearFlag(0x10016);
            }
            BoardPauseEnableSet(0);
            break;
        case -3:
            fn_80085EB4();
            BoardViewMapExec(arg0);
            break;
        case -4:
            fn_80085EB4();
            BoardViewOverheadExec(arg0);
            break;
        }
    } while (temp_r30 <= 0);
}

void BoardPlayerTurnMoveExec(s32 arg0) {
    s16 sp8;
    u32 temp_r27;
    s32 temp_r30;
    s32 var_r29;
    s32 var_r28;
    s32 temp_r0;
    s32 temp_r1;

    BoardPauseEnableSet(1);
    var_r28 = 0;
    if (_CheckFlag(0x10006U) == 0) {
        BoardCameraMoveSet(1);
        var_r29 = 1;
        BoardCameraViewSet(1);
        BoardCameraMotionWait();
        sp8 = -1;
        GWPlayer[arg0].space_next = -1;
        if (GWPlayer[arg0].bowser_suit != 0) {
            BoardCameraTargetModelSet(suitMdl);
            BoardCameraOffsetSet(0.0f, 100.0f, 0.0f);
        }
    } else {
        var_r29 = 0;
        var_r28 = 1;
        _ClearFlag(0x10006);
        _ClearFlag(0x10007);
        sp8 = GWPlayer[arg0].space_next;
        goto block_14;
    }
    do {
        BoardPauseEnableSet(1);
        GWPlayer[arg0].space_prev = GWPlayer[arg0].space_curr;
        if (_CheckFlag(0x20001U) == 0) {
            if (ExecJunction(arg0, &sp8) != 0) {
                break;
            }
        } else if (DoDebugMove(arg0, &sp8) != 0) {
            break;
        }
        
        GWPlayer[arg0].space_next = sp8;
        StopJunctionPlayer(0);
        if (MegaPlayerPassFunc(arg0, sp8) == 0) {
            BoardPauseEnableSet(0);
            BoardPlayerMoveTo(arg0, sp8);
            BoardPauseEnableSet(1);
        }
        GWPlayer[arg0].space_prev = GWPlayer[arg0].space_curr;
        GWPlayer[arg0].space_curr = sp8;
        if (var_r29 != 0) {
            BoardPlayerCurrMoveAwayStart(GWPlayer[arg0].space_prev, 0);
            var_r29 = 0;
        }
        DoSparkSpace(arg0, 0);
        if (BoardSpaceWalkEventExec() != 0) {
            continue;
        }
        if (BoardSpaceWalkExec(arg0, sp8) != 0) {
            continue;
        }
block_14:
        temp_r30 = BoardSpaceTypeGet(0, sp8);
        temp_r27 = BoardSpaceFlagGet(0, sp8);
        if ((temp_r30 == 0 || temp_r30 == 8 || temp_r30 == 10) && ((temp_r27 & 0x20000000) == 0) || var_r28 != 0) {
            var_r28 = 0;
            continue;
        }
        HuAudFXPlay(0x301);
        
        if (--GWPlayer[arg0].roll == 0) break;
    } while (1);
    BoardPauseEnableSet(1);
    BoardDiceDigit2DUpdateEnable(arg0);
    BoardRotateDiceNumbers(arg0);
    if (GWPlayer[arg0].bowser_suit != 0) {
        BoardCameraTargetPlayerSet(arg0);
    }
    if (_CheckFlag(0x1000BU) != 0) {
        BoardTutorialHookExec(7, 0);
    }
    if (BoardRollTypeGet() != -1) {
        fn_8008EEB8(arg0, BoardRollTypeGet());
        while (fn_8008EE9C() == 0) {
            HuPrcVSleep();
        }
        rollType = -1;
    }
    BoardPlayerSizeRestore(arg0);
    rollResized = 0;
    if (_CheckFlag(0x1000BU) != 0) {
        BoardTutorialHookExec(8, 0);
    }
    BoardSpaceHiddenBlockExec(arg0, sp8);
    BoardSpaceLandExec(arg0, sp8);
    _SetFlag(0x1000E);
    if (GWSystem.field31_bit4 != 1) {
        BoardCameraViewSet(2);
        BoardCameraMotionWait();
    } else {
        GWSystem.field31_bit4 = 0xF;
    }
    BoardPlayerZoomRestore(arg0);
    return;
}

void BoardPlayerPostTurnHookExec(s32 arg0) {
    if (postTurnHook[arg0] != 0U) {
        if (postTurnHook[arg0]() != 0) {
            postTurnHook[arg0] = 0;
        }
    }
}

void BoardPlayerSizeRestore(s32 arg0) {
    PlayerState* temp_r24;
    PlayerState* temp_r23;
    s32 var_r28;
    s32 var_r27;

    temp_r24 = BoardPlayerGet(arg0);
    if (temp_r24 != 0) {
        var_r28 = temp_r24->size;
    }
    if (var_r28 != 0) {
        temp_r23 = BoardPlayerGet(arg0);
        if (temp_r23 != 0) {
            var_r27 = temp_r23->size;
        }
        if (var_r27 == 1) {
            HuAudFXPlay(0x313);
        } else {
            HuAudFXPlay(0x311);
        }
        BoardPlayerResizeAnimExec(arg0, 0);
        BoardPlayerSizeSet(arg0, 0);

        while (fn_8008EE9C() == 0) {
            HuPrcVSleep();
        }
    }
}

void BoardPlayerZoomRestore(s32 arg0) {
    PlayerState* sp8;
    s32 var_r31;
    s32 var_r29;
    s32 var_r28;
    s32 temp_r27;
    Vec sp18;
    Vec spC;

    sp8 = BoardPlayerGet(arg0);
    BoardModelPosGet(BoardPlayerModelGet(arg0), &spC);
    temp_r27 = GWPlayer[arg0].space_curr;
    var_r31 = GWSystem.player_curr;
    if (var_r31 == -1) {
        var_r31 = 0;
    }
    for (var_r28 = 0, var_r29 = var_r28; var_r28 < 4; var_r28++) {
        if (var_r31 == arg0) break;
        if (temp_r27 == GWPlayer[var_r31].space_curr) {
            var_r29++;
        }
        var_r31 = (var_r31 + 1) & 3;
        (void)var_r29; // hack
    }
    BoardSpaceCornerPosGet(temp_r27, var_r29, &sp18);
    BoardPlayerMotBlendSet(arg0, 0, 0xF);
    
    while (BoardPlayerMotBlendCheck(arg0) == 0) {
        HuPrcVSleep();
    }
    BoardRotateDiceNumbers(arg0);
}

void BoardJunctionMaskSet(s32 arg0) {
    junctionMask |= arg0;
}

void BoardJunctionMaskReset(s32 arg0) {
    junctionMask &= ~arg0;
}

void BoardJunctionMaskZero(void) {
    junctionMask = 0;
}

static inline u32 BoardJunctionMaskGet(void) {
    return junctionMask;
}

static inline GetLinkCount(s32 playerIdx, s32 boardIdx) {
    s32 i;
    s32 linkCount;
    BoardSpace* boardSpaceLink;
    BoardSpace* boardSpaceFlag;
    PlayerState* player;
    s32 color;
    s32 temp;

    linkCount = 0;
    boardSpaceLink = BoardSpaceGet(0, boardIdx);
    
    if (boardSpaceLink->link_cnt <= 1) {
        return 0;
    }
    linkCount = boardSpaceLink->link_cnt;
    for (i = 0; i < boardSpaceLink->link_cnt; i++) {
        boardSpaceFlag = BoardSpaceGet(0, boardSpaceLink->link[i]);
        if (((boardSpaceFlag->flag & 0x20000000) != 0 && (BoardPlayerSizeGet(playerIdx) != 1))
            || ((boardSpaceFlag->flag & 0x02000000) != 0)
            || ((boardSpaceFlag->flag & 0x04000000) != 0)
            || ((boardSpaceFlag->flag & BoardJunctionMaskGet()) != 0)) {
            
            linkCount -= 1;
        }
    }
    return linkCount;
}

void InitJunction(s32 arg0, s32 arg1, f32 arg8) {
    Point3d sp68;
    Point3d sp5C;
    Point3d sp50;
    Point3d sp44;
    f32 sp40;
    f32 sp3C;
    s32 sp38;
    s16 sp20;
    s16 spE;
    BoardSpace* temp_r26;
    BoardSpace* temp_r25;
    f32 var_f27;
    f32 var_f28;
    f32 var_f29;
    omObjData* var_r28;
    s32 var_r20;
    bitcopy* temp_r29;
    s32 var_r27;
    s32 var_r22;
    f32 angle;

    if (junctionObj == 0) {
        for (var_r20 = 0; var_r20 < 4; var_r20++) {
            junctionArrowRot[var_r20] = -1;
        }
        
        sp38 = GetLinkCount(arg0, arg1);
        if (sp38 > 1) {
            var_r28 = omAddObjEx(boardObjMan, 0x100, 0, 0, -1, UpdateJunctionGfx);
            junctionObj = var_r28;
            temp_r29 = (bitcopy*) var_r28->work;
            temp_r29->field00_bit0 = 0;
            temp_r29->field00_bit7 = 0;
            temp_r29->field00_bit1 = arg0;
            temp_r29->unk_02 = 0;
            temp_r29->field00_bit5 = 0;
            temp_r29->unk_01 = 0;
            var_r28->scale.x = var_r28->scale.y = var_r28->scale.z = 3.0f;
            HuWinMesMaxSizeGet(1, &sp3C, 0x90003);
            var_f27 = 304.0f;
            var_f28 = -10000.0f;
            temp_r29->unk_04 = HuWinCreate(var_f27, var_f28, sp3C, sp40, 0);
            HuWinBGTPLvlSet(temp_r29->unk_04, 0.0f);
            HuWinMesSpeedSet(temp_r29->unk_04, 0);
            HuWinMesSet(temp_r29->unk_04, 0x90003);
            if (_CheckFlag(0x1000BU) != 0) {
                HuWinDispOff(temp_r29->unk_04);
            }
            temp_r26 = BoardSpaceGet(0, arg1);
            BoardSpacePosGet(0, arg1, &sp68);
            spE = BoardPlayerSizeGet(arg0);
            
            for (var_r27 = 0, var_r22 = var_r27; var_r22 < temp_r26->link_cnt; var_r22++) {
                if (temp_r26->link[var_r22] != 0) {
                    temp_r25 = BoardSpaceGet(0, temp_r26->link[var_r22]);
                    if (((((temp_r25->flag & 0x20000000) == 0) != 0) || (spE == 1)) && ((temp_r25->flag & 0x02000000) == 0) && ((temp_r25->flag & 0x04000000) == 0)) {
                        if ((temp_r25->flag & BoardJunctionMaskGet()) == 0) {
                            BoardSpacePosGet(0, temp_r26->link[var_r22], &sp50);
                            PSVECSubtract(&sp50, &sp68, &sp44);
                            PSVECNormalize(&sp44, &sp44);
                            
                            angle = (180.0 * (atan2(sp44.x, sp44.z) / M_PI));
                            if (angle < 0.0f) {
                                angle += 360.0f;
                            }
                            if (angle > 360.0f) {
                                angle -= 360.0f;
                            }
                            
                            OSf32tos16(&angle, &sp20);
                            sp20 = ((sp20 + 0x16) / 45) * 0x2D;;
                            junctionArrowRot[var_r27] = sp20;
                            var_f29 = 0.0f;
                            if (sp20 == 0) {
                                var_f29 = 100.0f;
                            } else if ((sp20 == 0xB4) && ((spE == 2) || (GWPlayer[arg0].bowser_suit != 0))) {
                                var_f29 = -100.0f;
                            }
                            temp_r29->unk_06[var_r27] = BoardModelCreate(0x70000, NULL, 1);
                            BoardModelRotSet(temp_r29->unk_06[var_r27], 0.0f, angle, 0.0f);
                            BoardModelLayerSet(temp_r29->unk_06[var_r27], 6);
                            sp5C.x = sp68.x + (100.0 * sin((M_PI * angle) / 180.0));
                            sp5C.y = 300.0f + sp68.y;
                            sp5C.z = (var_f29 + (sp68.z + (100.0 * cos((M_PI * angle) / 180.0))));
                            BoardModelPosSetV(temp_r29->unk_06[var_r27], &sp5C);
                            BoardModelScaleSet(temp_r29->unk_06[var_r27], var_r28->scale.x, var_r28->scale.y, var_r28->scale.z);
                            var_r27++;
                        }
                    }
                }
            }
            temp_r29->field00_bit3 = var_r27;
            if (-1.0f != arg8) {
                RestoreJunction(arg8, 0);
            }
        }
    }
    return;
}

static void UpdateJunctionGfx(omObjData* arg0) {
    s32 var_r28;
    bitcopy* temp_r30;

    temp_r30 = (bitcopy*)arg0->work;
    if ((temp_r30->field00_bit0 != 0) || (BoardIsKill() != 0)) {
        for (var_r28 = 0; var_r28 < temp_r30->field00_bit3; var_r28++) {
            BoardModelKill(temp_r30->unk_06[var_r28]);
        }
        HuWinKill(temp_r30->unk_04);
        junctionObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r30->unk_01 != 0) {
        temp_r30->unk_01--;
    } else if (temp_r30->field00_bit7 != 0) {
        temp_r30->field00_bit0 = 1;
    }
    temp_r30->unk_02 += 8;
    if (temp_r30->unk_02 > 0xB4) {
        temp_r30->unk_02 -= 0xB4;
    }
    OSs16tof32(&temp_r30->unk_02, &arg0->scale.x);
    arg0->scale.x = 3.0 + sin((M_PI * arg0->scale.x) / 180.0);
    arg0->scale.y = arg0->scale.x;
    arg0->scale.z = arg0->scale.x;
    BoardModelScaleSet(temp_r30->unk_06[temp_r30->field00_bit5], arg0->scale.x, arg0->scale.y, arg0->scale.z);
}

static void StopJunctionPlayer(s32 arg0) {
    bitcopy* temp_r31;

    if (junctionObj != 0) {
        temp_r31 = (bitcopy*)junctionObj->work;
        temp_r31->field00_bit7 = 1;
        temp_r31->unk_01 = 0;
        if (arg0 != 0) {
            HuAudFXPlay(2);
        }
        HuPrcSleep(0xA);
    }
}

static void RestoreJunction(f32 arg8, s32 arg0) {
    Point3d sp1C;
    f32 spC[4];
    s16 var_r30;
    s16 temp_r29;
    bitcopy* temp_r31;

    if (junctionObj != 0) {
        temp_r31 = (bitcopy*) junctionObj->work;
        if (temp_r31->unk_01 == 0) {
            arg8 = 90.0f * (((90.0f + arg8) - 1.0f) / 90.0f);
            
            for (var_r30 = 0; var_r30 < temp_r31->field00_bit3; var_r30++) {
                BoardModelRotGet(temp_r31->unk_06[var_r30], &sp1C);
                spC[var_r30] = 90.0f * (((90.0f + sp1C.y) - 1.0f) / 90.0f);
            }
            
            for (;var_r30 < 4; var_r30++) {
                spC[var_r30] = -999.0f;
            }
            
            temp_r29 = GetDefaultDirection(arg8, spC, temp_r31->field00_bit3);
            if ((temp_r29 != -1) && (temp_r31->field00_bit5 != temp_r29)) {
                temp_r31->field00_bit5 = temp_r29;
                if (arg0 != 0) {
                    HuAudFXPlay(0);
                }
                temp_r31->unk_01 = 0x14;
            }
        }
    }
}

static s32 GetDefaultDirection(f32 arg0, f32* arg1, s32 arg2) {
    f32 var_f27;
    f32 var_f28;
    f32 temp_f1;
    f32 temp_f30;
    s32 var_r30;
    s32 var_r31;

    temp_f30 = BoardDAngleCalc(arg0);
    var_f28 = 999.0f;
    
    for (var_r31 = 0, var_r30 = var_r31; var_r31 < arg2; var_r31++) {
        temp_f1 = BoardDAngleCalc(arg1[var_r31]);
        var_f27 = BOARD_FABS(BoardDAngleCalc(temp_f1 - temp_f30));
        
        if (var_f27 < var_f28) {
            var_f28 = var_f27;
            var_r30 = var_r31;
        }
    }
    return var_r30;
}

static inline s32 BoardPlayerMotGet(s32 player)
{
	PlayerState *player_ptr = BoardPlayerGet(player);
	return playerMot[player_ptr->player_idx];
}

static s32 DoDebugMove(s32 arg0, s16* arg1) {
    s16 spC0[10];
    s16 spAC[10];
    Vec spA0;
    Vec sp94;
    Vec sp88;
    Vec sp7C;
    BoardSpace* sp5C;
    s32 sp58;
    s32 sp54;
    BoardCameraData* sp50;
    f32 var_f30;
    s32 var_r29;
    s16 var_r26;
    PlayerState* sp28;
    BoardSpace* var_r23;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;
    s32 var_r18;
    bitcopy* var_r17;

    var_r18 = -1;
    
    memset(spC0, 0, 0x14);
    memset(spAC, 0, 0x14);
    while (1) {loop_1:
        sp28 = BoardPlayerGet(arg0);
        var_r23 = BoardSpaceGet(0, sp28->space_curr);
        sp58 = BoardSpaceCountGet(0);
        BoardPlayerPosGet(arg0, &sp88);
        var_r20 = GWPlayer[arg0].port;
        
        for (var_r22 = 0, var_r29 = var_r22; var_r29 < var_r23->link_cnt; var_r29++) {
            if ((BoardSpaceFlagGet(0, var_r23->link[var_r29]) & 0x06000000) == 0) {
                if ((BoardSpaceFlagGet(0, var_r23->link[var_r29]) & 0x20000000) == 0 || (BoardPlayerSizeGet(arg0) == 1)) {
                    spAC[var_r22++] = var_r23->link[var_r29];
                }
            }
        }
        var_r22 += BoardSpaceLinkTargetListGet(0, sp28->space_curr, &spAC[var_r22]);
        
        for (var_r29 = 0; var_r29 < var_r22; var_r29++) {
            sp5C = BoardSpaceGet(0, spAC[var_r29]);
            if (sp5C == 0) {
                spAC[var_r29] = 0;
            } else {
                PSVECSubtract(&sp5C->pos, &sp88, &sp94);
                var_f30 = 90.0 - (180.0 * (atan2(sp94.z, sp94.x) / M_PI));
                OSf32tos16(&var_f30, &var_r26);
                if (var_r26 < 0) {
                    var_r26 += 0x168;
                }
                if (var_r26 > 0x168) {
                    var_r26 -= 0x168;
                }
                
                spC0[var_r29] = var_r26 = var_r26 = (((var_r26 + 0x16) / 45) * 0x2D);
            }
        }
        sp54 = GWPlayer[arg0].space_curr;
        InitJunction(arg0, sp28->space_curr, -1.0f);
        do {loop_21:
            if (sp54 != GWPlayer[arg0].space_curr) {
                sp54 = GWPlayer[arg0].space_curr;
                goto loop_1;
            }
            spA0.x = HuPadStkX[var_r20];
            spA0.y = 0.0f;
            spA0.z = HuPadStkY[var_r20];
            if (HuPadBtnDown[var_r20] == 0x400) {
                StopJunctionPlayer(0);
                var_r18 = 1;
                goto end;
            } else {
                if (HuPadBtnDown[var_r20] == 0x10) {
                    BoardDiceDigit2DShowSet(0);
                    BoardRotateDiceNumbers(arg0);
                    StopJunctionPlayer(0);
                    BoardViewMapExec(arg0);
                    InitJunction(arg0, sp28->space_curr, -1.0f);
                    BoardDiceDigit2DShowSet(1);
                    goto loop_21;
                }
                if ((0.0f != spA0.x) || (0.0f != spA0.z)) {
                    var_f30 = (90.0 + (180.0 * (atan2(spA0.z, spA0.x) / M_PI)));
                    if (var_f30 < 0.0f) {
                        var_f30 += 360.0f;
                    }
                    if (var_f30 > 360.0f) {
                        var_f30 -= 360.0f;
                    }
                    RestoreJunction(var_f30, 1);
                    sp50 = &boardCamera;
                    PSVECSubtract(&sp50->target, &sp50->pos, &sp7C);
                    var_f30 = (var_f30 + (90.0 - (180.0 * (atan2(-sp7C.z, -sp7C.x) / M_PI))));
                    if (var_f30 < 0.0f) {
                        var_f30 += 360.0f;
                    }
                    if (var_f30 > 360.0f) {
                        var_f30 -= 360.0f;
                    }
                    var_r21 = var_f30;
                    
                    for (var_r29 = 0; var_r29 < var_r22; var_r29++) {
                        if ((spC0[var_r29] + 0x2D > var_r21) && (spC0[var_r29] - 0x2D < var_r21)) {
                            *arg1 = spAC[var_r29];
                            var_r18 = 0;
                            goto end;
                        } else if ((var_r21 <= 0x168) && (var_r21 >= 0x13B) && ((s32) ((&spC0[0])[var_r29] + 0x195) > var_r21) && ((s32) ((&spC0[0])[var_r29] + 0x13B) < var_r21)) {
                            *arg1 = spAC[var_r29];
                            var_r18 = 0;
                            goto end;
                        }
                    }
                } else {
                    if (BoardPlayerMotGet(arg0) != 1) {
                        BoardRotateDiceNumbers(arg0);
                    }
                    if (GWPlayer[arg0].bowser_suit != 0) {
                        BoardBowserSuitMotionSetWait();
                        BoardBowserSuitPlayerModelKill();
                    }
                }
                HuPrcVSleep();
                goto loop_21;  
            }
        } while (1);
    }
    end:
    return var_r18;
}

// ...

void BoardPlayerCopyMat(s32 arg0) {
    s16 modelID;
    ModelData *model;
    void* temp_r3;
    HsfData* temp_r31;

    modelID = BoardModelIDGet(GetBoardPlayer(arg0));
    model = &Hu3DData[modelID];
    temp_r31 = model->hsfData;
    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, temp_r31->materialCnt * 0x3C, 0x10000000U);
    memcpy(temp_r3, temp_r31->material, temp_r31->materialCnt * 0x3C);
    playerMatCopy[arg0] = temp_r3;
}
