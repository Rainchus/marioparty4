#include "unsplit.h"
#include "game/audio.h"
#include "game/objsub.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/board/main.h"
#include "game/board/audio.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/ui.h"
#include "game/board/tutorial.h"

// structs
typedef struct structActiveMG {
    s16 unk_00;
    s8  unk_02;
    s8  unk_03;
    s32 unk_04;
} structActiveMG;

typedef struct unkSubstructR31 {
    s16 unk_00[4];
    char unk_08[0x14];
    Vec unk_1C[13][13];
} unkSubstructR31;

typedef struct bitcopy {
    struct {
        u8 field00_bit0 : 1;
        u8 field00_bit1 : 3;
        u8 field00_bit4 : 2;
        u8 field00_bit6 : 1;
        u8 field00_bit7 : 1;
    };
    struct {
        u8 field01_bit0 : 4;
    };
    u8 unk_02;
    s8 unk_03;
    s16 unk_04;
    u8 unk_06;
    s32 unk_08;
    unkSubstructR31* unk_0C;
} bitcopy;

// bss
static structActiveMG activeMG[4];
static s16 mgListAll[0x20];

// data
static s32 mgSetupSprTbl[13] = {
    0x0007004B, 0x0007004C, 0x0007004D, 0x0007004E,
    0x0007004F, 0x00070052, 0x00070050, 0x00070051,
    0x00070053, 0x00070054, 0x00070055, 0x00070068,
    0x00070056
};
static Vec statusLayout4P[4] = {
    { 170.0f, 244.0f, 0.0f }, 
    { 406.0f, 244.0f, 0.0f },
    { 170.0f, 364.0f, 0.0f },
    { 406.0f, 364.0f, 0.0f },
};
static Vec statusLayout1Vs3[4] = {
    { 170.0f, 304.0f, 0.0f }, 
    { 406.0f, 224.0f, 0.0f },
    { 406.0f, 304.0f, 0.0f },
    { 406.0f, 384.0f, 0.0f },
};
static Vec statusLayout2Vs2[4] = {
    { 170.0f, 260.0f, 0.0f }, 
    { 170.0f, 348.0f, 0.0f },
    { 406.0f, 260.0f, 0.0f },
    { 406.0f, 348.0f, 0.0f },
};
static s32 luckyMessTbl[9] = {
    0x00140000, 0x00140005, 0x0014000A, 0x0014000F,
    0x00140014, 0x00140019, 0x00140000, 0x00140000,
    0x00140000
};

// sbss
static u8 mgType;
static s32 luckyF;
static s16 mgNext;
static omObjData* mgSetupObj;
static Process* mgSetupProc;

// sdata

// sdata2

// determined functions
void BoardMGSetupExec(void);
static void DestroyMGSetup(void);
static void ExecMGSetup(void);
static void DetermineMGList(bitcopy*);
static void SetupStatusLayout(void);
static s32 GetMGType(void);
static s32 GetMGTypeTeam(void);
static void CreateMGSetup(void);
static void UpdateMGSetup(omObjData*);
static void CenterStatus(bitcopy*, omObjData*);
static void SeparateStatus(bitcopy*, omObjData*);
static void PopupVS(bitcopy*, omObjData*);
// ...
static void FallMGType(bitcopy*, omObjData*);
static void LuckyMGFall(bitcopy*, omObjData*);
static void UpdateLuckyValue(bitcopy*, omObjData*);
static void UpdateMGList(bitcopy*, omObjData*);
static void HideLuckyValue(void);
s32 BoardMGSetupPlayPush(s32, s16);
void BoardMGSetupPlayPop(s32, s16);

// FUNCTIONS //

void BoardMGSetupExec(void) {
    mgSetupProc = HuPrcChildCreate(&ExecMGSetup, 0x2006, 0x3800, 0, boardMainProc);
    HuPrcDestructorSet2(mgSetupProc, &DestroyMGSetup);
    while (mgSetupProc != 0) {
        HuPrcVSleep();
    }
}

static void DestroyMGSetup(void) {
    GWSystem.player_curr = 0;
    mgSetupProc = NULL;
}

static inline s32 setupObjGet(void) {
    bitcopy* work = (bitcopy*) mgSetupObj->work;
    return work->field00_bit1;
}

static void ExecMGSetup(void) {
    s32 sp60[9] = {
        0x750000, 0x760000, 0x770000,
        0x780000, 0x790000, 0x7A0000,
        0x7B0000, 0x7C0000, 0x7D0000
    };
    Vec sp54;
    u16 var_r24;
    s32 var_r22;
    s32 var_r23;
    s32 var_r31;
    u32 var_r30;
    bitcopy* temp_r29;
    bitcopy* temp_r28;
    bitcopy* temp_r27;
    bitcopy* temp_r26;
    bitcopy* temp_r25;

    luckyF = 0;
    mgNext = 0;
    GWSystem.player_curr = -1;
    GWSystem.unk_32 = 1;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        activeMG[var_r31].unk_00 = -1;
        activeMG[var_r31].unk_04 = 0;
    }
    BoardPlayerMoveAwayStartCurr(GWPlayer[GWSystem.player_curr].space_curr, 1);
    BoardCameraMoveSet(0);
    BoardCameraTargetSpaceSet(BoardSpaceStarGetCurr());
    sp54.x = 0.0f;
    sp54.y = 150.0f;
    sp54.z = 0.0f;
    BoardCameraMotionStartEx(-1, NULL, &sp54, 1300.0f, -1.0f, 0x15);
    BoardCameraMotionWait();
    WipeCreate(1, 0, 0x15);
    
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    BoardFilterFadeInit(0x1E, 0xA0U);
    CreateMGSetup();
    while (setupObjGet() != 7) {
        HuPrcVSleep();
    }
    if (BoardRandMod(0x64U) < 5U) {
        HuPrcSleep(0x1E);
        luckyF = 1;
        temp_r29 = (bitcopy*) mgSetupObj->work;
        temp_r29->field00_bit1 = 4;
        temp_r29->unk_02 = 0;
        temp_r29->unk_03 = 0;
        temp_r29->unk_04 = 0;
        HuAudFXPlay(0x35C);
        while (setupObjGet() != 7) {
            HuPrcVSleep();
        }
        temp_r28 = (bitcopy*) mgSetupObj->work;
        temp_r28->field00_bit1 = 1;
        temp_r28->unk_02 = 0;
        temp_r28->unk_03 = 0;
        temp_r28->unk_04 = 0;
        while (setupObjGet() != 7) {
            HuPrcVSleep();
        }
        var_r30 = luckyMessTbl[GWBoardGet()];
        BoardWinCreate(2, var_r30, BoardWinPortraitGetStar());
        BoardWinWait();
        BoardWinKill();
        temp_r27 = (bitcopy*) mgSetupObj->work;
        temp_r27->field00_bit1 = 5;
        temp_r27->unk_02 = 0;
        temp_r27->unk_03 = 0;
        temp_r27->unk_04 = 0;
        while (setupObjGet() != 7) {
            HuPrcVSleep();
        }
        switch (GWSystem.unk_32) {
            case 1:
                var_r30 = luckyMessTbl[GWBoardGet()] + 1;
                break;
            case 2:
                var_r30 = luckyMessTbl[GWBoardGet()] + 2;
                break;
            case 3:
                var_r30 = luckyMessTbl[GWBoardGet()] + 3;
                break;
        }
        BoardWinCreate(2, var_r30, BoardWinPortraitGetStar());
        BoardWinWait();
        var_r30 = luckyMessTbl[GWBoardGet()] + 4;
        BoardWinCreate(2, var_r30, BoardWinPortraitGetStar());
        BoardWinWait();
        BoardWinKill();
        HideLuckyValue();
    } else {
        temp_r26 = (bitcopy*) mgSetupObj->work;
        temp_r26->field00_bit1 = 1;
        temp_r26->unk_02 = 0;
        temp_r26->unk_03 = 0;
        temp_r26->unk_04 = 0;
        while (setupObjGet() != 7) {
            HuPrcVSleep();
        }
    }
    temp_r25 = (bitcopy*) mgSetupObj->work;
    temp_r25->field00_bit1 = 6;
    temp_r25->unk_02 = 0;
    temp_r25->unk_03 = 0;
    temp_r25->unk_04 = 0;
    while (setupObjGet() != 7) {
        HuPrcVSleep();
    }
    HuDataDirClose(0x70000);
    HuDataDirClose(0x20000);
    HuDataDirClose(sp60[GWBoardGet()]);
    HuPrcSleep(2);
    if (_CheckFlag(0xBU) != 0) {
        var_r23 = 0x140000;
    } else {
        var_r23 = mgInfoTbl[mgNext].data_dir;
    }
    var_r22 = BoardDataDirReadAsync(var_r23);
    BoardAudSeqFadeOut(0, 0x3E8U);
    _SetFlag(0x1000EU);
    WipeColorSet(0xFFU, 0xFFU, 0xFFU);
    WipeCreate(2, 0, -1);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFXAllStop();
    _SetFlag(0x1001CU);
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        BoardStatusItemHideSet(var_r31, 1);
    }
    ((bitcopy*) (mgSetupObj->work))->field00_bit0 = 1;
    BoardDataAsyncWait(var_r22);
    var_r24 = mgNext + 0x191;
    BoardMGSetupPlayPop(mgType, var_r24);
    GWSystem.mg_next_type = -1;
    GWMGAvailSet(var_r24);
    GWSystem.mg_next = var_r24 - 0x191;
    _SetFlag(0x10002U);
    if (GWSystem.turn == GWSystem.max_turn) {
        _SetFlag(0xAU);
    }
    BoardNextOvlSet(3);
    HuPrcEnd();
}

static void DetermineMGList(bitcopy* arg0) {
    MgInfo* var_r31;
    s32 temp_r23;
    s32 var_r30;
    s16* var_r28;
    s32 var_r22;
    s32 var_r21;
    s32 var_r24;
    s32 var_r27;
    u32 temp_r20;
    s32 var_r29;
    u32 var_r19;
    s32 temp_r18;
    u32* temp_r26;
    s16* temp_r25;

    var_r24 = 0;
    var_r31 = mgInfoTbl;
    
    for (var_r27 = 0; var_r31->ovl != 0xFFFF; var_r31++, var_r27++) {
        if ((var_r31->flag & 1) == 0) {
            mgListAll[var_r24] = (var_r31 - mgInfoTbl) + 0x191;
            var_r24++;
        }
    }
    mgListAll[var_r24] = -1;
    temp_r26 = HuMemDirectMallocNum(HEAP_SYSTEM, var_r27 * 4, 0x10000000U);
    temp_r25 = HuMemDirectMallocNum(HEAP_SYSTEM, var_r27 * 2, 0x10000000U);
    var_r31 = mgInfoTbl;
    
    for (var_r29 = var_r30 = 0; var_r30 < var_r27; var_r30++, var_r31++) {
        if ((mgType == var_r31->type) && (var_r31->ovl != 0x29)) {
            if ((GWMGListGet() != 2) || (GWMGCustomGet(var_r30 + 0x191) != 0)) {
                if (GWMGListGet() == 1) {
                    var_r21 = 0;
                    var_r28 = &mgListAll[0];
                    while (*var_r28 != -1) {
                        if (var_r30 + 0x191 == *var_r28) {
                            var_r21 = 1;
                            break;
                        }
                        var_r28++;
                    }
                    if (var_r21 != 0) continue;
                }
                temp_r26[var_r29] = var_r31->name_mess;
                temp_r25[var_r29] = var_r30;
                var_r29++;
            }
        }
    }

    var_r19 = var_r29;
    var_r30 = 0;
    while (var_r30 < arg0->field01_bit0) {
        var_r29 = BoardRandMod(var_r19);
        temp_r20 = temp_r26[var_r29];
        temp_r23 = temp_r25[var_r29];
        temp_r18 = temp_r23 + 0x191;

        if (GWMGListGet() == 2 || BoardMGSetupPlayPush(mgType, temp_r18) == 0) {
            var_r22 = 0;
            for (var_r29 = 0; var_r29 < var_r30; var_r29++) {
                if (temp_r20 == activeMG[var_r29].unk_04) {
                    var_r22 = 1;
                    break;
                }
            }
            if (var_r22 == 0) {
                if (GWMGAvailGet(temp_r23 + 0x191) == 0) {
                    activeMG[var_r30].unk_03 = 0;
                } else {
                    activeMG[var_r30].unk_03 = 1;
                }
                activeMG[var_r30].unk_04 = temp_r20;
                activeMG[var_r30].unk_02 = temp_r23;
                var_r30++;
            }
        }
    }
    HuMemDirectFree(temp_r26);
    HuMemDirectFree(temp_r25);
}

static void SetupStatusLayout(void) {
    s32 var_r27;
    s32 var_r26;
    s32 var_r28;
    s32 var_r30;
    s32 var_r29;
    s32 var_r31;

    if (mgType != 0) {
        if (mgType == 1) {
            for (var_r28 = var_r31 = 0; var_r31 < 4; var_r31++) {
                if (GWPlayer[var_r31].color == 2) {
                    var_r27 = var_r31;
                    GWPlayer[var_r31].field08_bit11 = GWPlayerTeamGet(var_r31);
                    GWPlayerCfg[var_r31].group = 0;
                    var_r28++;
                } else {
                    GWPlayer[var_r31].field08_bit11 = GWPlayerTeamGet(var_r31);
                    GWPlayerCfg[var_r31].group = 1;
                    var_r26 = var_r31;
                }
            }
            if (var_r28 == 1) {
                BoardStatusTargetPosSet(var_r27, statusLayout1Vs3);
                var_r30 = 1;
                
                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    if (var_r31 != var_r27) {
                        BoardStatusTargetPosSet(var_r31, &statusLayout1Vs3[var_r30++]);
                    }
                }
                return;
            }
            BoardStatusTargetPosSet(var_r26, statusLayout1Vs3);
            var_r29 = 1;
            
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                if (var_r31 == var_r26) {
                    GWPlayer[var_r31].field08_bit11 = GWPlayerTeamGet(var_r31);
                    GWPlayerCfg[var_r31].group = 0;
                } else {
                    BoardStatusTargetPosSet(var_r31, &statusLayout1Vs3[var_r29++]);
                    GWPlayer[var_r31].field08_bit11 = GWPlayerTeamGet(var_r31);
                    GWPlayerCfg[var_r31].group = 1;
                }
            }
            return;
        }
        var_r30 = 2;
        for (var_r29 = var_r31 = 0; var_r31 < 4; var_r31++) {
            if (GWPlayer[var_r31].color == 2) {
                BoardStatusTargetPosSet(var_r31, &statusLayout2Vs2[var_r29++]);
                GWPlayer[var_r31].field08_bit11 = GWPlayerTeamGet(var_r31);
                GWPlayerCfg[var_r31].group = 0;
            } else {
                BoardStatusTargetPosSet(var_r31, &statusLayout2Vs2[var_r30++]);
                GWPlayer[var_r31].field08_bit11 = GWPlayerTeamGet(var_r31);
                GWPlayerCfg[var_r31].group = 1;
            }
        }
    }
}

static s32 GetMGType(void) {
    s32 var_r27;
    s32 var_r28;
    s32 var_r30;
    s32 var_r31;
    s32 var_r25;
    s32 var_r26;
    s8 var_r29;

    for (var_r28 = var_r30 = var_r27 = var_r31 = 0; var_r31 < 4; var_r31++) {
        if (GWPlayer[var_r31].color == 2) {
            var_r30++;
        } else if (GWPlayer[var_r31].color == 1) {
            var_r28++;
        } else {
            var_r27++;
        }
    }
    if ((var_r30 != 2) || (var_r28 != 2)) {
        if (var_r27 == 4) {
            var_r31 = BoardRandMod(4);
            GWPlayer[var_r31].color = 1;
            var_r27 = 3;
            var_r28 = 1;
            var_r30 = 0;
        }
        var_r26 = var_r25 = -1;
        if (var_r30 == 3) {
            var_r26 = 2;
            var_r25 = 1;
        } else if (var_r28 == 3) {
            var_r26 = 1;
            var_r25 = 2;
        }
        if (((var_r27 >= 3) || ((var_r27 == 2) && (var_r28 == 1) && (var_r30 == 1))) && (BoardRandMod(0x64U) > 0x28U)) {
            if (var_r30 == 1) {
                var_r29 = 2;
            } else {
                var_r29 = 1;
            }
            do {
                var_r31 = BoardRandMod(4);
            } while (GWPlayer[var_r31].color != 3);
            GWPlayer[var_r31].color = var_r29;
            if (var_r29 == 1) {
                var_r29 = 2;
            } else {
                var_r29 = 1;
            }
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                if (GWPlayer[var_r31].color == 3) {
                    GWPlayer[var_r31].color = var_r29;
                }
            }
        } else {
            
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                if ((GWPlayer[var_r31].color == 3) || (GWPlayer[var_r31].color == 0)) {
                    if (var_r26 == -1) {
                        if (BoardRandMod(0x64) < 0x32) {
                            var_r29 = 2;
                        } else {
                            var_r29 = 1;
                        }
                    } else if (BoardRandMod(0x64) < 0x5A) {
                        var_r29 = var_r26;
                    } else {
                        var_r29 = var_r25;
                    }
                    GWPlayer[var_r31].color = var_r29;
                }
            }
        }
    }
    
    
    for (var_r30 = var_r28 = var_r31 = 0; var_r31 < 4; var_r31++) {
        if (GWPlayer[var_r31].color == 2) {
            var_r30++;
        } else if (GWPlayer[var_r31].color == 1) {
            var_r28++;
        }
    }

    if (var_r30 == 1 || var_r30 == 3) {
        return 1;
    } else if (var_r30 == 2) {
        return 2;
    } else {
        return 0;
    }
}

static s32 GetMGTypeTeam(void) {
    s8 sp12[4];
    s8 spE[4];
    s8 spA[4];
    s8 sp8[2] = { 2, 1 };
    s32 var_r30;
    s32 var_r31;
    s32 temp_r25;
    s8 var_r27;
    s8 var_r26;
    s8 var_r28;
    s8* var_r29; 

    spA[0] = spA[1] = spA[2] = spA[3] = -1;
    spE[0] = spE[1] = spE[2] = spE[3] = -1;
    sp12[0] = sp12[1] = sp12[2] = sp12[3] = -1;
    
    for (var_r28 = var_r27 = var_r26 = var_r31 = 0; var_r31 < 4; var_r31++) {
        switch (GWPlayer[var_r31].color) {
        case 2:
            sp12[var_r28] = var_r31;
            var_r28++;
            break;
        case 1:
            spE[var_r26] = var_r31;
            var_r26++;
            break;
        default:
            spA[var_r27] = var_r31;
            var_r27++;
            break;
        }
    }
    if (var_r27 != 0) {
        
        for (var_r31 = 0; var_r31 < var_r27; var_r31++) {
            GWPlayer[spA[var_r31]].color = sp8[BoardRandMod(2)];
        }
        return GetMGTypeTeam();
    }
    if ((var_r28 == 4) || (var_r26 == 4)) {
        return 0;
    }
    if ((var_r28 == 1) || (var_r26 == 1)) {
        if (var_r28 == 1) {
            var_r29 = sp12;
        } else {
            var_r29 = spE;
        }
        if (BoardRandMod(0x64U) < 0x46U) {
            var_r30 = BoardPlayerSameTeamFind(*var_r29);
            GWPlayer[*var_r29].color = GWPlayer[var_r30].color;
            return 0;
        }
        var_r30 = BoardPlayerSameTeamFind(*var_r29);
        GWPlayer[var_r30].color = GWPlayer[*var_r29].color;
        return 2;
    }
    var_r30 = BoardPlayerSameTeamFind(sp12[0]);
    if (GWPlayer[sp12[0]].color != GWPlayer[var_r30].color) {
        temp_r25 = GWPlayer[var_r30].color;
        GWPlayer[var_r30].color = GWPlayer[sp12[0]].color;

        
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if ((var_r31 != sp12[0]) && (var_r31 != var_r30)) {
                break;
            }
        }
        GWPlayer[var_r31].color = temp_r25;
        var_r30 = BoardPlayerSameTeamFind(var_r31);
        GWPlayer[var_r30].color = temp_r25;
    }
    return 2;
}

static void CreateMGSetup(void) {
    s32 var_r30;
    unkSubstructR31* temp_r31;
    bitcopy* temp_r28;
    bitcopy* temp_r29;

    mgSetupObj = omAddObjEx(boardObjMan, 0x200, 0U, 0U, -1, UpdateMGSetup);
    temp_r28 = (bitcopy*) mgSetupObj->work;
    temp_r28->field00_bit0 = 0;
    temp_r29 = (bitcopy*) mgSetupObj->work;
    temp_r29->field00_bit1 = 0;
    temp_r29->unk_02 = 0;
    temp_r29->unk_03 = 0;
    temp_r29->unk_04 = 0;
    temp_r28->unk_0C = HuMemDirectMallocNum(HEAP_SYSTEM, 0x154, 0x10000000U);
    temp_r31 = temp_r28->unk_0C;
    temp_r31->unk_00[0] = HuSprGrpCreate(0xD);
    
    for (var_r30 = 0; var_r30 < 13; var_r30++) {
        BoardSpriteCreate(mgSetupSprTbl[var_r30], 0x5DC, NULL, &temp_r31->unk_00[var_r30] + 1);
        HuSprGrpMemberSet(*temp_r31->unk_00, var_r30, *(&temp_r31->unk_00[var_r30] + 1));
        HuSprAttrSet(*temp_r31->unk_00, var_r30, 4);
        temp_r31->unk_1C[0][var_r30].x = temp_r31->unk_1C[0][var_r30].y = temp_r31->unk_1C[0][var_r30].z = 0.0f;
        temp_r31->unk_1C[1][var_r30].x = temp_r31->unk_1C[1][var_r30].y = temp_r31->unk_1C[1][var_r30].z = 0.0f;
    }
    HuSprGrpPosSet(temp_r31->unk_00[0], 288.0f, 240.0f);
}

void UpdateMGSetup(omObjData* arg0) {
    bitcopy* var_r31;
    s32 var_r29;

    var_r31 = (bitcopy*) arg0->work;
    if (var_r31->field00_bit0 != 0 || BoardIsKill() != 0) {
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            if (activeMG[var_r29].unk_00 != -1) {
                HuWinKill(activeMG[var_r29].unk_00);
                activeMG[var_r29].unk_00 = -1;
            }
        }
        HuSprGrpKill(var_r31->unk_0C->unk_00[0]);
        HuMemDirectFree(var_r31->unk_0C);
        mgSetupObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
    } else if (var_r31->unk_06 != 0) {
        var_r31->unk_06--;
    } else {
        switch (var_r31->field00_bit1) {
            case 1:
                CenterStatus(var_r31, arg0);
                break;
            case 2:
                SeparateStatus(var_r31, arg0);
                break;
            case 3:
                PopupVS(var_r31, arg0);
                break;
            case 4:
                FallMGType(var_r31, arg0);
                break;
            case 5:
                LuckyMGFall(var_r31, arg0);
                break;
            case 6:
                UpdateLuckyValue(var_r31, arg0);
                break;
            case 7:
                UpdateMGList(var_r31, arg0);
                break;
        }
    }
}

void CenterStatus(bitcopy* arg0, omObjData* arg1) {
    s32 var_r31;
    bitcopy* temp_r30;

    if (arg0->unk_02 == 0) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            BoardStatusItemHideSet(var_r31, 0);
            BoardStatusTargetPosSet(var_r31, &statusLayout4P[var_r31]);
        }
        arg0->unk_02 = 1;
        HuAudFXPlay(0x354);
        return;
    }
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (!BoardStatusStopCheck(var_r31)) {
            return;
        }
    }
    if ((s32) GWSystem.team != 0) {
        mgType = GetMGTypeTeam();
    } else {
        mgType = GetMGType();
    }
    if (mgType == 0) {
        arg0->field01_bit0 = 4;
    } else {
        arg0->field01_bit0 = 3;
    }
    SetupStatusLayout();
    DetermineMGList(arg0);
    if (_CheckFlag(0x1000BU) != 0) {
        BoardTutorialHookExec(0x1A, 0);
    }
    temp_r30 = (bitcopy*) mgSetupObj->work;
    temp_r30->field00_bit1 = 2;
    temp_r30->unk_02 = 0;
    temp_r30->unk_03 = 0;
    temp_r30->unk_04 = 0;
}

void SeparateStatus(bitcopy* arg0, omObjData* arg1) {
    Vec sp8;
    f32 temp_f30;
    f32 temp_f29;
    s32 var_r28;
    bitcopy* temp_r29;
    unkSubstructR31* temp_r27;

    temp_r27 = arg0->unk_0C;
    switch (arg0->unk_02) {
        case 0:
            for (var_r28 = 0; var_r28 < 4; var_r28++) {
                BoardStatusPosGet(var_r28, &sp8.x);
                if (sp8.x < 288.0f) {
                    sp8.x = -98.0f;
                } else {
                    sp8.x = 674.0f;
                }
                BoardStatusTargetPosSet(var_r28, &sp8);
            }
            arg0->unk_02 = 1;
            arg0->unk_03 = 0;
            return;
    case 1:
        if ((s8) arg0->unk_03 >= 0x5A) {
            arg0->unk_03 = 0;
            temp_r29 = (bitcopy*) mgSetupObj->work;
            temp_r29->field00_bit1 = 7;
            temp_r29->unk_02 = 0;
            temp_r29->unk_03 = 0;
            temp_r29->unk_04 = 0;
            return;
        }
        OSu8tof32((u8*)&arg0->unk_03, &temp_f29);
        temp_f30 = sin((temp_f29 * M_PI) / 180.0) * 4.0 + 1.0;
        arg0->unk_03 += 6;
        if (arg0->unk_03 > 0x5A) {
            arg0->unk_03 = 0x5A;
        }
        HuSprScaleSet(temp_r27->unk_00[0], 0, temp_f30, temp_f30);
        if (arg0->unk_03 > 0x3C) {
            HuSprTPLvlSet(temp_r27->unk_00[0], 0, (90.0f - arg0->unk_03) / 30.0f);
        }
    }
}

void PopupVS(bitcopy* arg0, omObjData* arg1) {
    f32 var_f30;
    f32 temp_f31;
    bitcopy* temp_r28;
    unkSubstructR31* temp_r29;

    temp_r29 = arg0->unk_0C;
    if (arg0->unk_02 == 0) {
        HuSprAttrReset(temp_r29->unk_00[0], 0, 4);
        HuSprAttrSet(temp_r29->unk_00[0], 0, 8);
        HuSprScaleSet(temp_r29->unk_00[0], 0, 0.001f, 0.001f);
        HuSprPosSet(temp_r29->unk_00[0], 0, 0.0f, 64.0f);
        arg0->unk_02 = 1;
        HuAudFXPlay(0x355);
        return;
    }
    OSs16tof32(&arg0->unk_04, &temp_f31);
    if (arg0->unk_04 < 0x5A) {
        var_f30 = 2.0 * sin((M_PI * temp_f31) / 180.0);
    } else {
        var_f30 = 1.0 + sin((M_PI * temp_f31) / 180.0);
        if (arg0->unk_04 >= 0xB4) {
            var_f30 = 1.0f;
            temp_r28 = (bitcopy*) mgSetupObj->work;
            temp_r28->field00_bit1 = 3;
            temp_r28->unk_02 = 0;
            temp_r28->unk_03 = 0;
            temp_r28->unk_04 = 0;
            arg0->unk_06 = 0x3C;
        }
    }
    HuSprScaleSet(temp_r29->unk_00[0], 0, var_f30, var_f30);
    arg0->unk_04 += 9;
    if ((_CheckFlag(0x1000BU) != 0) && arg0->field00_bit1 == 3) {
        BoardTutorialHookExec(0x1B, 0);
        if (*boardTutorialData == 1) {
            arg0->field00_bit1 = 0;
        }
    }
}
