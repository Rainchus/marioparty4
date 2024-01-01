#include "game/board/window.h"

extern s32 BoardPlayerIsAllCom(void);
extern Process* boardMainProc;

static s8 winChoice;
static s8 autoPickF;
static s8 winPortrait;
static s8 winPosIdx;
static u8 disablePlayer;
static s8 winPause;
static s8 winWait;
static s16 winPrio;
static s16 messSpeed;
static s16 defaultChoice;
static s32 winMess;
static s32 winAttr;
f32 lbl_801D3F70[2];
static void (*comKeyFunc)();
static Process* winProc;
static s32 choiceDisableTbl[0x10];
static u32 winInsertMesTbl[8];

static s32 PortraitTbl[] = {
    0,  4,  2,  3,
    7,  6,  0,  12,
    12, 
};
static s32 StarPortraitTbl[] = {
    13, 16, 14, 15,
    18, 6,  13, 12,
    12
};

static s16 windowID = -1;
const s8 lbl_801D5318[4] = {0, 1, 4, 0};

void BoardWinInit(void) {
    HuWinInit(1);
}

void fn_8006FDA0(f32* arg0) {
    if (arg0 != 0) {
        lbl_801D3F70[0] = arg0[0];
        lbl_801D3F70[1] = arg0[1];
        return;
    }
    lbl_801D3F70[0] = lbl_801D3F70[1] = 0.0f;
}

void BoardWinKillAll(void) {
    BoardWinKill();
    HuWinAllKill();
}

void BoardWinDestroy(void) {
    if (windowID >= 0) {
        if (winPortrait == -1) {
            HuWinExCleanup(windowID);
        } else {
            HuWinExCleanup(windowID);
            winPortrait = -1;
        }
        windowID = -1;
    }
    winMess = 0;
    winProc = 0;
}

void BoardWinProc(void) {
    f32 sp10[2];
    f32 sp8[2];
    s32 var_r31;
    f32* temp_r29;
    f32* temp_r30;
    WindowData *var_r28 = NULL;

    f32 var_50[7][2] = {
        {384.0f,  64.0f}, {432.0f, 192.0f},
        {504.0f,  96.0f}, {432.0f, 128.0f},
        {288.0f, 192.0f}, {432.0f,  96.0f},
        {432.0f,  96.0f},
    };
    f32 var_18[7][2] = {
        {96.0f, 328.0f},  {72.0f, 128.0f},
        {36.0f, 344.0f},  {128.0f, 312.0f},
        {144.0f, 144.0f}, {128.0f, 264.0f},
        {128.0f,  75.0f},
    };
    
    if (windowID < 0) {
        temp_r30 = var_50[winPosIdx];
        temp_r29 = var_18[winPosIdx];
        HuWinMesMaxSizeGet(1, sp10, winMess);
        if (sp10[0] <= temp_r30[0]) {
            sp10[0] = temp_r30[0];
            sp8[0] = temp_r29[0];
        } else {
            sp8[0] = -10000.0f;
        }
        if (sp10[1] <= temp_r30[1]) {
            sp10[1] = temp_r30[1];
        }
        sp8[1] = temp_r29[1];
        if ((winPosIdx == 5) || (winPosIdx == 6)) {
            windowID = HuWinExCreateStyled(sp8[0], sp8[1], sp10[0], sp10[1], -1, 1);
            HuWinMesPalSet(windowID, 7, 0, 0, 0);
        } else if (winPortrait == -1) {
            windowID = HuWinExCreate(sp8[0], sp8[1], sp10[0], sp10[1], -1);
        } else {
            windowID = HuWinExCreate(sp8[0], sp8[1], sp10[0], sp10[1], winPortrait);
        }
        if (windowID == -1) {
            HuPrcEnd();
        }
        if (_CheckFlag(0x1000B) != 0) {
            HuWinPriSet(windowID, 3);
        }
    }
    if (disablePlayer != 0) {
        HuWinDisablePlayerSet(windowID, disablePlayer);
    }
    if (winPrio != -1) {
        HuWinPriSet(windowID, winPrio);
    }
    if (winPortrait == -1) {
        HuWinExAnimIn(windowID);
    } else {
        HuWinExAnimIn(windowID);
    }
    HuWinMesSpeedSet(windowID, messSpeed);
    HuWinMesSet(windowID, winMess);
    
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        if (winInsertMesTbl[var_r31] != -1) {
            HuWinInsertMesSet(windowID, winInsertMesTbl[var_r31], var_r31);
        }
    }
    HuWinAttrSet(windowID, winAttr);
    
    for (var_r31 = 0; var_r31 < 0x10; var_r31++) {
        if (choiceDisableTbl[var_r31] != 0) {
            HuWinChoiceDisable(windowID, var_r31);
        }
    }
    if (autoPickF != 0) {
        BoardWinStartComKeySet();
        if (comKeyFunc != 0) {
            comKeyFunc();
        }
    } else if ((_CheckFlag(0x1000B) != 0) && ((winPosIdx == 5) || (winPosIdx == 6))) {
        var_r28 = &winData[windowID];
        var_r28->active_pad = 0xF;
        HuWinComKeyWait(-1, -1, -1, -1, 0);
    } else {
        BoardWinStartComKeySet();
    }
    HuWinMesWait(windowID);
    if (winWait != 0) {
        HuWinKeyWaitEntry(windowID);
        HuWinMesWait(windowID);
    }
    if (winPause != 0) {
        HuPrcSleep(-1);
    }
    if (defaultChoice != -1) {
        winChoice = HuWinChoiceGet(windowID, defaultChoice);
    }
    if (winPortrait != -1) {
        HuWinExAnimOut(windowID);
    }
    HuPrcEnd();
}

int BoardWinChoiceGet(void) {
    return winChoice;
}

void BoardWinPause(void) {
    winPause = 1;
}

void BoardWinCreateChoice(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_r31;
    SystemState* temp_r3;
    s32 var_r30;
    

    winPosIdx = arg0;
    winChoice = 0;
    defaultChoice = arg3;
    winPortrait = arg2;
    winAttr = 0;
    autoPickF = 1;
    winWait = 0;
    comKeyFunc = NULL;
    disablePlayer = 0;
    winPrio = -1;
    winPause = 0;
    HuWinComKeyReset();
    
    for (var_r31 = 0; var_r31 < 0x10; var_r31++) {
        choiceDisableTbl[var_r31] = 0;
    }
    
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        winInsertMesTbl[var_r31] = -1;
    }
    if (winProc == 0) {
        winProc = HuPrcChildCreate(&BoardWinProc, 0x2009, 0x4000, 0, boardMainProc);
        HuPrcDestructorSet2(winProc, &BoardWinDestroy);
    }
    winMess = arg1;
    if (GWSystem.mess_speed == 3) {
        GWSystem.mess_speed = 1;
    }
    var_r30 = GWSystem.mess_speed;
    BoardWinSpeedSet(var_r30);
    BoardWinPlayerSet(GWSystem.player_curr);
}

void BoardWinCreate(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_r30;
    s32 var_r31;
    void* temp_r3;

    winPosIdx = arg0;
    winChoice = 0;
    defaultChoice = -1;
    winPortrait = arg2;
    winAttr = 0;
    autoPickF = 1;
    winWait = 0;
    comKeyFunc = NULL;
    disablePlayer = 0;
    winPrio = -1;
    winPause = 0;
    HuWinComKeyReset();
    
    for (var_r31 = 0; var_r31 < 0x10; var_r31++) {
        choiceDisableTbl[var_r31] = 0;
    }
    
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        winInsertMesTbl[var_r31] = -1;
    }
    if (winProc == 0) {
        winProc = HuPrcChildCreate(&BoardWinProc, 0x2009U, 0x4000U, 0, boardMainProc);
        HuPrcDestructorSet2(winProc, &BoardWinDestroy);
    }
    winMess = arg1;
    if (GWSystem.mess_speed == 3) {
        GWSystem.mess_speed = 1;
    }
    var_r30 = GWSystem.mess_speed;
    BoardWinSpeedSet(var_r30);
    BoardWinPlayerSet(GWSystem.player_curr);
    autoPickF = 0;
}

void BoardWinInsertMesSet(s32 value, s32 index) {
    winInsertMesTbl[index] = value;
}

static inline BOOL BoardWinDone(void) {
    if(winProc != NULL) {
        return 0;
    } else {
        return 1;
    }
}

void BoardWinWait(void) {
    while(!BoardWinDone()) {
        HuPrcVSleep();
    }
}

void BoardWinKill(void) {
    if (winProc != 0) {
        HuPrcKill(winProc);
        winProc = NULL;
    }
}

void BoardWinSetAttr(s32 arg0) {
    winAttr |= arg0;
    if (windowID >= 0) {
        HuWinAttrSet(windowID, winAttr);
    }
}

void BoardWinResetAttr(s32 arg0) {
    winAttr &= ~arg0;
    if (windowID >= 0) {
        HuWinAttrSet(windowID, winAttr);
    }
}

void BoardWinChoiceDisable(s32 index) {
    choiceDisableTbl[index] = 1;
}

void BoardWinKeyWait(void) {
    winWait = 1;
}

int BoardWinSpeedGet(void) {
    s32 temp_r31;

    if (GWSystem.mess_speed == 3) {
        GWSystem.mess_speed = 1;
    }
    temp_r31 = GWSystem.mess_speed;
    return lbl_801D5318[temp_r31];
}

void BoardWinSpeedSet(s32 arg0) {
    messSpeed = lbl_801D5318[arg0];
    if (windowID != -1) {
        HuWinMesSpeedSet(windowID, messSpeed);
    }
}

s16 BoardWinChoiceNowGet(void) {
    if (windowID == -1) {
        return -1;
    }
    return HuWinChoiceNowGet(windowID);
}

void BoardWinPriSet(s16 arg0) {
    winPrio = arg0;
    if (windowID != -1) {
        HuWinPriSet(windowID, arg0);
    }
}

s16 BoardWinChoiceNowGet2(void) {
    if (windowID == -1) {
        return -1;
    }
    return HuWinChoiceNowGet(windowID);
}

s32 BoardWinPortraitGet(void) {
    s32 temp = GWSystem.board;
    return PortraitTbl[temp];
}

s32 BoardWinPortraitGetStar(void) {
    s32 temp = GWSystem.board;
    return StarPortraitTbl[temp];
}

void BoardWinPlayerSet(s32 arg0) {
    s32 temp_r0;
    s32 i;

    if (arg0 == -1) {
        temp_r0 = GWSystem.story;
        if (temp_r0 != 1) {
            for (i = 0, disablePlayer = i; i < 4; i++) {
                if (GWPlayer[i].com != 0) {
                    disablePlayer |= 1 << GWPlayer[i].port;
                }
            }
        } else {
            disablePlayer = 0;
        }
    } else if (GWPlayer[arg0].com != 0) {
        disablePlayer = 0xF;
    } else {
        disablePlayer = ~(1 << GWPlayer[arg0].port);
    }
    if (_CheckFlag(0x1000BU) != 0) {
        disablePlayer = 0;
    }
    if (windowID != -1) {
        HuWinDisablePlayerSet(windowID, disablePlayer);
    }
}

void BoardWinStartComKeySet(void) {
    s32 sp8[4];
    s16 temp_r28;
    s32 temp_r30;
    s32 var_r31;
    s32 temp_r29;

    if (BoardPlayerIsAllCom() != 0) {
        sp8[0] = sp8[1] = sp8[2] = sp8[3] = 0x100;
        goto block_20;
    }
    if (GWSystem.player_curr == -1) {
        if ((GWPlayer[0].com == 0) || (GWPlayer[1].com == 0) || (GWPlayer[2].com == 0) || (GWPlayer[3].com == 0)) {
            return;
        }
        goto block_9;
    }
    if (GWPlayer[GWSystem.player_curr].com != 0) {
block_9:
        if (GWSystem.player_curr != -1) {
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                temp_r29 = GWPlayer[var_r31].port;
                if (GWSystem.player_curr == var_r31) {
                    sp8[temp_r29] = 0x100;
                } else {
                    sp8[temp_r29] = 0;
                }
            }
        } else {
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                sp8[var_r31] = 0x100;
            }
        }
block_20:
        temp_r28 = GWMessSpeedGet();
        temp_r30 = HuWinKeyWaitNumGet(winMess);
        if (temp_r30 != 0) {
            HuWinComKeyReset();
            for (var_r31 = 0; var_r31 < temp_r30; var_r31++) {
                HuWinComKeyWait(sp8[0], sp8[1], sp8[2], sp8[3], (s32)temp_r28);
            }
        }
    }
}

void BoardWinComKeyFuncSet(void (*func)()) {
    comKeyFunc = func;
}