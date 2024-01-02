#include "common.h"

//// #include "game/board/main.h"
extern s32 BoardIsStarted(void);
//// #include "game/board/space.h"
extern s32 BoardSpaceFlagPosGet(s32, s32, u32);
//// #include "game/board/ui.h"
extern void BoardStatusHammerShowSet(s32, s32);
//// #include "game/board/model.h"
extern s16 BoardModelCreateCharacter(s32, s32, s32*, s32);
extern void BoardModelExistCheck(s16, s32);
extern void BoardModelExistDupe(s16, s32);
extern void BoardModelCameraSet(s16, u16);
//// #include "game/chrman.h"
extern void CharModelKillIndex(s16);
////

s32 BoardRollTypeGet(void);
void BoardRollTypeSet(s32 type);
s32 BoardPlayerGetCharMess(s32 player);
char* BoardPlayerGetCharName(s32 player);
s32 BoardPlayerIsAllCom(void);
void BoardPlayerInit(void);
void BoardPlayerModelInit(void);
void BoardPlayerModelKill(void);
void BoardPlayerLayerSet(s32, s32);
//...
s32 BoardPlayerAutoSizeGet(s32);
void BoardPlayerAutoSizeSet(s32, s32); 
void BoardPlayerSizeSet(s32, s32);
void fn_80062D90(s32);
void BoardPlayerCopyMat(s32);
void BoardBowserSuitKill(s32);

static void (*playerMatCopy[4])();
static void (*postTurnHook[4])();
static void (*preTurnHook[4])();

static s32 diceJumpObj[4] = {0, 0, 0, 0};
static s32 animDoneF[4] = {0, 0, 0, 0};
static s16 bowserSuitMot[5] = {-1, -1, -1, -1, -1};

s16 boardPlayerMdl[4];
static s16 playerMot[4];
static s8 rollType;

static s16 suitMdl = -1;
static s16 suitPlayerMdl = -1;
static s16 suitCurrMot = -1;

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
            fn_80062D90(var_r31);
            BoardPlayerSizeSet(var_r31, 0);
            GWPlayer[var_r31].color = 0;
            GWPlayer[var_r31].rank = 0;
            GWPlayer[var_r31].field01_bit9 = 0;
            GWPlayer[var_r31].field08_bit3 = 0;
        }
        return;
    }
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        fn_80062D90(var_r31);
        if (BoardPlayerAutoSizeGet(var_r31) != 0) {
            BoardPlayerAutoSizeSet(var_r31, BoardPlayerAutoSizeGet(var_r31));
            BoardStatusHammerShowSet(var_r31, 0);
        }
    }
}

void BoardPlayerModelInit(void) {
    s32 sp64[0x10];
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
            temp_r25 = GWPlayer[var_r31].bowser_suit;
            GWPlayer[var_r31].team = temp_r25;
            GWPlayerCfg[var_r31].group = temp_r25;
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        preTurnHook[var_r31] = 0;
        postTurnHook[var_r31] = 0;
        animDoneF[var_r31] = 0;
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
        GWPlayer[var_r31].rank = 0;
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
        CharModelKillIndex(GWPlayer[var_r31].character);
    }
    CharModelLayerSetAll(2);
}

void BoardPlayerModelKill(void) {
    s32 var_r31;
    PlayerState* temp_r30;
    PlayerState* temp_r29;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        temp_r29 = &GWPlayer[var_r31];
        temp_r30 = temp_r29;
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
    PlayerState* playerCopy;
    PlayerState* player;
    s16 boardPlayerModel;
    s16 boardPlayerModelCopy;
    
    player = &GWPlayer[arg0];
    playerCopy = player;
    boardPlayerModel = boardPlayerMdl[playerCopy->player_idx];
    boardPlayerModelCopy = boardPlayerModel;
    BoardModelLayerSet(boardPlayerModelCopy, arg1);
}

void BoardPlayerCameraSet(s32 arg0, u16 arg1) {
    PlayerState* playerCopy;
    PlayerState* player;
    s16 boardPlayerModel;
    s16 boardPlayerModelCopy;
    
    player = &GWPlayer[arg0];
    playerCopy = player;
    boardPlayerModel = boardPlayerMdl[playerCopy->player_idx];
    boardPlayerModelCopy = boardPlayerModel;
    BoardModelCameraSet(boardPlayerModelCopy, arg1);
}

void fn_80062A40(s32 arg0, f32 arg8) {
    PlayerState* playerCopy;
    PlayerState* player;
    s16 boardPlayerModel;
    s16 boardPlayerModelCopy;
    
    player = &GWPlayer[arg0];
    playerCopy = player;
    boardPlayerModel = boardPlayerMdl[playerCopy->player_idx];
    boardPlayerModelCopy = boardPlayerModel;
    fn_8006DDE8(boardPlayerModelCopy, arg8);
}