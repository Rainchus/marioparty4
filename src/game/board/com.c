#include "game/board/com.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/board/com_path.h"
#include "game/board/main.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/tutorial.h"
#include "game/board/window.h"

#include "math.h"

s32 BoardBooComUseCheck(s32);

static void ExecComKeyLeft(void);
static void ExecComKeyRight(void);
static void ExecComKeyUp(void);
static void ExecComKeyDown(void);
static void ExecComKey(s32 arg0, s32 arg1, s32 arg2);
static s32 ChooseUseItem(s32 arg0);
static BOOL CheckMiniUse(s32 arg0, s32 arg1);
static BOOL CheckMegaUse(s32 arg0, s32 arg1);
static BOOL CheckSparkUse(s32 arg0, s32 arg1);
static BOOL CheckBoardChangeUse(s32 arg0, s32 arg1);
static BOOL CheckSwapUse(s32 arg0, s32 arg1);
static BOOL CheckBooUse(s32 arg0, s32 arg1);
static BOOL CheckLampUse(s32 arg0, s32 arg1);

static s8 itemUse = -1;

static s8 comItemWeightTbl[8][12] = {
    { 0x0C, 0x0B, 0x05, 0x03, 0x01, 0x02, 0x06, 0x04, 0x00, 0x07, 0x09, 0x0A },
    { 0x0C, 0x0B, 0x05, 0x0A, 0x03, 0x01, 0x02, 0x00, 0x06, 0x04, 0x07, 0x09 },
    { 0x0C, 0x0B, 0x05, 0x06, 0x03, 0x01, 0x02, 0x0A, 0x07, 0x09, 0x00, 0x04 },
    { 0x0C, 0x05, 0x0B, 0x09, 0x03, 0x01, 0x02, 0x06, 0x00, 0x04, 0x0A, 0x07 },
    { 0x0C, 0x0B, 0x04, 0x09, 0x0A, 0x03, 0x01, 0x05, 0x02, 0x06, 0x00, 0x07 },
    { 0x0C, 0x0B, 0x05, 0x03, 0x01, 0x0A, 0x06, 0x02, 0x00, 0x04, 0x09, 0x07 },
    { 0x0C, 0x05, 0x0B, 0x04, 0x07, 0x09, 0x03, 0x01, 0x0A, 0x06, 0x02, 0x00 },
    { 0x0C, 0x05, 0x07, 0x0B, 0x0A, 0x09, 0x04, 0x06, 0x03, 0x01, 0x02, 0x00 }
};

static BOOL (*comItemUseCheckFuncTbl[])(s32, s32) = {
    CheckMiniUse,
    CheckMegaUse,
    CheckMiniUse,
    CheckMegaUse,
    CheckBoardChangeUse,
    CheckBoardChangeUse,
    CheckSwapUse,
    CheckSparkUse,
    NULL,
    CheckBoardChangeUse,
    NULL,
    CheckBooUse,
    CheckLampUse,
    NULL
};

static Vec comJunctionDirTbl[] = {
    {   0.0f,   0.0f, -72.0f },
    {  90.0f,  72.0f,   0.0f },
    { 180.0f,   0.0f,  72.0f },
    { 270.0f, -72.0f,   0.0f }
};

static void ExecComKeyLeft(void) {
    ExecComKey(GWSystem.player_curr, 0, 1);
}

void BoardComKeySetLeft(void) {
    BoardWinComKeyFuncSet(ExecComKeyLeft);
}

static void ExecComKeyRight(void) {
    ExecComKey(GWSystem.player_curr, 1, 1);
}

void BoardComKeySetRight(void) {
    BoardWinComKeyFuncSet(ExecComKeyRight);
}

static void ExecComKeyUp(void) {
    ExecComKey(GWSystem.player_curr, 0, 0);
}

void BoardComKeySetUp(void) {
    BoardWinComKeyFuncSet(ExecComKeyUp);
}

static void ExecComKeyDown(void) {
    ExecComKey(GWSystem.player_curr, 1, 0);
}

void BoardComKeySetDown(void) {
    BoardWinComKeyFuncSet(ExecComKeyDown);
}

static void ExecComKey(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp14[4];
    s32 temp_r31;
    s16 temp_r30;
    s32 var_r29;

    sp14[0] = sp14[1] = sp14[2] = sp14[3] = 0;
    temp_r31 = GWPlayer[arg0].port;
    temp_r30 = GWMessDelayGet();
    if (arg2 == 0) {
        var_r29 = 4;
    } else {
        var_r29 = 2;
    }
    if (arg1 == 1) {
        sp14[temp_r31] = var_r29;
        HuWinComKeyWait(sp14[0], sp14[1], sp14[2], sp14[3], temp_r30);
    }
    sp14[temp_r31] = 0x100;
    HuWinComKeyWait(sp14[0], sp14[1], sp14[2], sp14[3], temp_r30);
}

s8 BoardComPreferItemGet(s32 arg0, s8 *arg1, s8 arg2) {
    s32 temp_r26;
    s32 var_r28;
    s32 temp_r29;
    s32 var_r27;
    s32 i;
    s32 j;

    temp_r26 = GWPlayer[arg0].character;
    var_r27 = -1;
    var_r28 = 0x64;
    for (i = 0; i < arg2; i++) {
        temp_r29 = arg1[i];
        for (j = 0; j < 0xC; j++) {
            if (temp_r29 == comItemWeightTbl[temp_r26][j]) {
                if (j < var_r28 && (BoardPlayerItemFind(arg0, temp_r29) == -1 || temp_r29 == 0xC || temp_r29 == 0xB)) {
                    var_r28 = j;
                    var_r27 = i;
                }
                break;
            }
        }
    }
    if (var_r28 == 0x64) {
        return -1;
    }
    return var_r27;
}

s8 BoardComPreferItemCheck(s32 arg0, s8 arg1, s8 arg2, s8 arg3) {
    s8 spB[3];
    s8 temp_r25;

    spB[0] = arg1;
    spB[1] = arg2;
    spB[2] = arg3;
    temp_r25 = BoardComPreferItemGet(arg0, spB, 3);
    return temp_r25;
}

s32 BoardComItemWeightGet(s32 arg0, s32 arg1) {
    s32 var_r30;
    s32 i;

    for (i = 0; i < 0xC; i++) {
        if (arg1 == comItemWeightTbl[GWPlayer[arg0].character][i]) {
            break;
        }
    }
    var_r30 = 0xB - i;
    return var_r30;
}

s32 BoardComTutorialItemGet(s32 arg0) {
    s32 var_r30;
    s32 var_r31;

    if (!GWPlayer[arg0].com) {
        return -1;
    }
    if (itemUse != -1) {
        var_r31 = itemUse;
    }
    if (boardTutorialUseItem >= 0 && boardTutorialUseItem <= 0xD) {
        var_r31 = boardTutorialUseItem;
        boardTutorialUseItem = -1;
    }
    if (var_r31 != -1) {
        var_r30 = BoardPlayerItemFind(arg0, var_r31);
    } else {
        var_r30 = -1;
    }
    return var_r30;
}

s32 BoardComUseItemSet(s32 arg0, s32 arg1) {
    if (arg1 == -1) {
        itemUse = -1;
        return 1;
    }
    if (BoardPlayerItemFind(arg0, arg1) != -1) {
        itemUse = arg1;
        return 1;
    }
    return 0;
}

BOOL BoardComUseItemCheck(s32 arg0) {
    s32 var_r31;

    var_r31 = BoardPlayerItemCount(arg0);
    if (var_r31 <= 0) {
        return FALSE;
    }
    if (ChooseUseItem(arg0) != -1) {
        return TRUE;
    }
    return FALSE;
}

static s32 ChooseUseItem(s32 arg0) {
    s32 i;
    s32 j;
    s32 temp_r29;
    s32 var_r28;
    s32 temp_r27;
    s32 temp_r25;
    BOOL (*temp_r24)(s32, s32);
    s8 temp_r23;

    temp_r29 = -1;
    temp_r25 = GWPlayer[arg0].character;
    var_r28 = 0x64;
    for (i = 0; i < 3; i++) {
        temp_r27 = GWPlayer[arg0].items[i];
        if (temp_r27 == -1) {
            continue;
        }
        temp_r24 = comItemUseCheckFuncTbl[temp_r27];
        if (!temp_r24) {
            continue;
        }
        temp_r23 = temp_r24(arg0, temp_r27);
        if (temp_r23) {
            for (j = 0; j < 0xC; j++) {
                if (temp_r27 == comItemWeightTbl[temp_r25][j]) {
                    if (j < var_r28) {
                        var_r28 = j;
                    }
                    break;
                }
            }
        }
    }
    if (var_r28 == 0x64) {
        return -1;
    }
    temp_r29 = comItemWeightTbl[temp_r25][var_r28];
    if (temp_r29 == -1) {
        itemUse = -1;
    } else if (BoardPlayerItemFind(arg0, temp_r29) != -1) {
        itemUse = temp_r29;
    }
    return temp_r29;
}

static BOOL CheckMiniUse(s32 arg0, s32 arg1) {
    s32 temp_r29;
    s32 var_r26;
    s32 var_r25;
    s32 temp_r28;
    s32 temp_r23;
    s32 var_r24;
    s32 var_r31;
    s32 var_r30;

    var_r24 = 0;
    temp_r29 = GWPlayer[arg0].space_curr;
    temp_r28 = GWPlayer[arg0].diff;
    temp_r23 = GWPlayer[arg0].character;
    switch (temp_r28) {
        case 0:
            var_r30 = 0x32;
            break;
        case 1:
            var_r30 = 0x19;
            break;
        case 2:
            var_r30 = 5;
            break;
        case 3:
            var_r30 = 0;
            break;
    }
    if ((temp_r28 == 0 || temp_r28 == 1) && temp_r23 == 1) {
        var_r30 = 7;
    }
    if (GWBoardGet() != 7 && GWBoardGet() != 8) {
        var_r26 = BoardComPathReachCheck(temp_r29, 8, 0);
        var_r25 = BoardComPathReachCheck(temp_r29, 8, 1);
    } else {
        var_r26 = 0x3E7;
        var_r25 = BoardComPathW20BestGet(temp_r29, 0x10000000, 0xA);
        if ((GWBoardGet() == 8 || GWBoardGet() == 7) && BoardRandMod(0x64) < 0x3C) {
            var_r24 = 1;
        }
    }
    switch (GWPlayer[arg0].diff) {
        case 0:
            var_r31 = 5;
            break;
        case 1:
            var_r31 = 7;
            break;
        case 2:
            var_r31 = 9;
            break;
        case 3:
            var_r31 = 0xA;
            break;
    }
    if ((var_r25 < var_r31 || var_r26 < var_r31 || var_r24 != 0) && BoardRandMod(0x64) >= var_r30) {
        return TRUE;
    }
    return FALSE;
}

static BOOL CheckMegaUse(s32 arg0, s32 arg1) {
    s32 temp_r27;
    s32 temp_r26;
    s32 temp_r24;
    s32 temp_r29;
    s16 temp_r25;
    s16 var_r28;
    s16 temp_r23;
    s16 temp_r22;
    s16 i;

    temp_r29 = GWPlayer[arg0].diff;
    temp_r26 = GWPlayer[arg0].character;
    switch (temp_r29) {
        case 0:
            var_r28 = 5;
            break;
        case 1:
            var_r28 = 7;
            break;
        case 2:
            var_r28 = 9;
            break;
        case 3:
            var_r28 = 0xA;
            break;
    }
    if (((temp_r29 == 0 || temp_r29 == 1) && temp_r26 == 0) || ((temp_r29 == 0 || temp_r29 == 1) && temp_r26 == 5)) {
        var_r28 = 8;
    }
    if (GWBoardGet() != 7 || BoardRandMod(0x64) >= 0x3C) {
        temp_r24 = GWPlayer[arg0].space_curr;
        temp_r27 = BoardComPathReachCheck(temp_r24, 8, 0);
        temp_r23 = GWPlayer[arg0].space_curr;
        for (i = 0; i < 4; i++) {
            if (i != arg0) {
                temp_r22 = GWPlayer[i].space_curr;
                temp_r25 = BoardComPathLenGet(temp_r23, temp_r22);
                if (temp_r25 < var_r28 + 0x14 && temp_r25 > 0 && GWTeamGet() && i == BoardPlayerSameTeamFind(arg0)) {
                    return FALSE;
                }
            }
        }
        if (GWBoardGet() != 7 && GWBoardGet() != 8 && temp_r27 < 0xA && temp_r27 > 0) {
            return FALSE;
        }
    }
    if (BoardPlayerItemFind(arg0, arg1) != -1) {
        return TRUE;
    }
    return FALSE;
}

static BOOL CheckSparkUse(s32 arg0, s32 arg1) {
    s32 temp_r27;
    s32 temp_r28;
    s32 temp_r26;
    s32 temp_r25;
    s32 temp_r24;
    s32 i;
    s32 var_r30;

    temp_r25 = GWPlayer[arg0].space_curr;
    temp_r28 = GWPlayer[arg0].diff;
    temp_r24 = GWPlayer[arg0].character;
    switch (temp_r28) {
        case 0:
            var_r30 = 0x32;
            break;
        case 1:
            var_r30 = 0x19;
            break;
        case 2:
            var_r30 = 5;
            break;
        case 3:
            var_r30 = 0;
            break;
    }
    if ((temp_r28 == 0 || temp_r28 == 1) && temp_r24 == 7) {
        var_r30 = 7;
    }
    for (i = 0; i < 4; i++) {
        if (i != arg0) {
            temp_r26 = GWPlayer[i].space_curr;
            temp_r27 = BoardComPathLenGet(temp_r26, temp_r25);
            if (temp_r27 > 0 && temp_r27 <= 0xF && BoardPlayerItemFind(arg0, arg1) != -1 && BoardRandMod(0x64) >= var_r30) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

static BOOL CheckBoardChangeUse(s32 arg0, s32 arg1) {
    s32 temp_r25;
    s32 temp_r24;
    s32 temp_r23;
    s32 temp_r22;
    s32 temp_r21;
    s32 temp_r26;
    s32 var_r30;
    s32 var_r29;
    s32 var_r27;
    s32 i;

    temp_r25 = GWPlayer[arg0].diff;
    temp_r24 = GWPlayer[arg0].character;
    switch (temp_r25) {
        case 0:
            var_r27 = 0x32;
            break;
        case 1:
            var_r27 = 0x19;
            break;
        case 2:
            var_r27 = 5;
            break;
        case 3:
            var_r27 = 0;
            break;
    }
    if (((arg1 == 4 && temp_r24 == 4) || (arg1 == 5 && (temp_r24 == 6 || temp_r24 == 3))) && (temp_r25 == 0 || temp_r25 == 1)) {
        var_r27 = 7;
    }
    var_r30 = 0x3E7;
    for (i = 0; i < 4; i++) {
        if (arg0 == i) {
            continue;
        }
        temp_r21 = GWPlayer[i].space_curr;
        if (!GWTeamGet() || i != BoardPlayerSameTeamFind(arg0)) {
            temp_r26 = GWPlayer[i].space_curr;
            if (GWBoardGet() == 7) {
                if (BoardComPathW20BestGet(temp_r21, 0x10000000, 0xA) != -1) {
                    var_r29 = 0xA;
                } else {
                    var_r29 = 0;
                }
            } else if (GWBoardGet() == 8) {
                if (BoardComPathW20BestGet(temp_r21, 0x200000, 0xA) != -1 || BoardComPathW20BestGet(temp_r21, 0x400000, 0xA) != -1) {
                    var_r29 = 0xA;
                } else {
                    var_r29 = 0;
                }
            } else {
                var_r29 = BoardComPathReachCheck(temp_r26, 8, 0);
            }
            if (var_r29 != 0 && var_r29 < var_r30) {
                var_r30 = var_r29;
            }
        }
    }
    if ((var_r30 > 0xF && var_r30 != 0x3E7) || (GWTeamGet() && i == BoardPlayerSameTeamFind(arg0))) {
        return FALSE;
    }
    temp_r26 = GWPlayer[arg0].space_curr;
    temp_r23 = BoardComPathReachCheck(temp_r26, 8, 0);
    temp_r22 = BoardComPathReachCheck(temp_r26, 8, 1);
    if (BoardPlayerItemFind(arg0, arg1) != -1 && BoardRandMod(0x64) >= var_r27) {
        if ((temp_r23 == 0 || temp_r22 == 0) && var_r30 == 0x3E7) {
            return TRUE;
        }
        if (temp_r23 > var_r30 || temp_r22 > var_r30) {
            return TRUE;
        }
        if (temp_r23 > 0xA || temp_r22 > 0xA) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL CheckSwapUse(s32 arg0, s32 arg1) {
    s32 temp_r27;
    s32 temp_r26;
    s32 temp_r25;
    s32 var_r30;
    s32 var_r29;
    s32 i;

    temp_r27 = GWPlayer[arg0].diff;
    temp_r25 = GWPlayer[arg0].character;
    switch (temp_r27) {
        case 0:
            var_r29 = 0x32;
            break;
        case 1:
            var_r29 = 0x19;
            break;
        case 2:
            var_r29 = 5;
            break;
        case 3:
            var_r29 = 0;
            break;
    }
    if ((temp_r27 == 0 || temp_r27 == 1) && temp_r25 == 2) {
        var_r29 = 7;
    }
    for (var_r30 = i = 0; i < 4; i++) {
        if (i != arg0) {
            var_r30 += BoardPlayerItemCount(i);
        }
    }
    if (var_r30 == 0) {
        return FALSE;
    }
    if (GWTeamGet()) {
        temp_r26 = BoardPlayerSameTeamFind(arg0);
        for (var_r30 = i = 0; i < 4; i++) {
            if (temp_r26 != i && i != arg0) {
                var_r30 += BoardPlayerItemCount(i);
            }
        }
        if (var_r30 == 0) {
            return FALSE;
        }
    }
    if (BoardPlayerItemFind(arg0, arg1) != -1 && BoardRandMod(0x64) >= var_r29) {
        return TRUE;
    }
    return FALSE;
}

static BOOL CheckBooUse(s32 arg0, s32 arg1) {
    if (BoardPlayerCoinsGet(arg0) < 5) {
        return FALSE;
    }
    if (BoardBooComUseCheck(arg0) == 0) {
        return FALSE;
    }
    if (BoardPlayerItemFind(arg0, arg1) == -1) {
        return FALSE;
    }
    return TRUE;
}

static BOOL CheckLampUse(s32 arg0, s32 arg1) {
    if ((BoardPlayerCoinsGet(arg0) >= 0x14 || GWSystem.last5_effect == 4) && BoardPlayerItemFind(arg0, arg1) != -1) {
        return TRUE;
    }
    return FALSE;
}

s32 BoardComJunctionInputGet(s32 arg0, Vec *arg1, s32 arg2, float *arg3) {
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    float var_f30;
    float var_f29;
    float var_f31;
    s32 var_r29;
    s32 var_r27;
    s32 temp_r26;
    s32 var_r24;
    s32 var_r23;
    s32 var_r21;
    s32 i;
    s16 var_r28;
    s16 temp_r25;
    s16 spC;

    temp_r26 = GWBoardGet();
    var_r24 = 0;
    temp_r25 = GWPlayer[arg0].space_curr;
    var_r28 = -1;
    spC = GWPlayer[arg0].roll;
    switch (GWPlayer[arg0].diff) {
        case 3:
            var_r29 = 0;
            break;
        case 2:
            var_r29 = 0;
            break;
        case 1:
            var_r29 = 0xA;
            break;
        default:
        case 0:
            var_r29 = 0x1E;
            break;
    }
    if (BoardRandMod(0x64) >= var_r29) {
        var_r23 = 1;
    } else {
        var_r23 = 0;
    }
    if (var_r23 != 0) {
        if (temp_r26 >= 0 && temp_r26 <= 5) {
            var_r28 = BoardComPathBestGet(temp_r25);
        } else if (temp_r26 == 7) {
            var_r28 = BoardComPathW20BestGet(temp_r25, 0x10000000, 0xA);
        }
        if (var_r28 == -1) {
            var_r24 = 1;
        } else {
            BoardSpacePosGet(0, temp_r25, &sp1C);
            BoardSpacePosGet(0, var_r28, &sp28);
            PSVECSubtract(&sp28, &sp1C, &sp10);
            var_f31 = BoardDAngleCalc(90.0 - 180.0 * (atan2(sp10.z, sp10.x) / M_PI));
            if (var_f31 < 0.0f) {
                var_f31 += 360.0f;
            }
            if (var_f31 > 360.0f) {
                var_f31 -= 360.0f;
            }
        }
    }
    if (var_r24 != 0) {
        var_r21 = BoardRandMod(arg2);
        var_f31 = arg3[var_r21];
    }
    var_f30 = 999.0f;
    for (var_r27 = i = 0; i < 4; i++) {
        var_f29 = (comJunctionDirTbl[i].x - var_f31 < 0.0f)
            ? -(comJunctionDirTbl[i].x - var_f31)
            : (comJunctionDirTbl[i].x - var_f31);
        if (var_f29 < var_f30) {
            var_r27 = i;
            var_f30 = var_f29;
        }
    }
    arg1->x = comJunctionDirTbl[var_r27].y;
    arg1->z = comJunctionDirTbl[var_r27].z;
    arg1->y = 0.0f;
    return 0;
}

s32 BoardComBestPlayerFind(void) {
    s32 temp_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 i;

    if (_CheckFlag(0x1000B) != 0) {
        return -1;
    }
    var_r28 = -1;
    var_r29 = -1;
    for (i = 0; i < 4; i++) {
        var_r27 = GWPlayer[i].space_curr;
        temp_r30 = BoardComPathReachCheck(var_r27, 8, 0);
        if (temp_r30 > 0 && temp_r30 > var_r29) {
            var_r29 = temp_r30;
            var_r28 = i;
        }
    }
    return var_r28;
}
