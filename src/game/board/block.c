#include "game/process.h"
#include "game/board/main.h"
#include "game/board/player.h"
#include "math.h"

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 3;
        u8 unk00_field2 : 1;
        u8 unk00_field3 : 1;
        u8 unk00_field4 : 1;
        u8 unk00_field5 : 1;
    };
    
    u8 unk01;
    s16 unk02;
    s16 unk04;
} BlockWork;

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 3;
        u8 unk00_field2 : 1;
        u8 unk00_field3 : 1;
        u8 unk00_field4 : 1;
        u8 unk00_field5 : 1;
    };
    
    u8 unk01;
    s8 unk02;
    s16 unk04;
} CoinWork;

static void BlockProc(void);
static void DestroyBlock(void);
static void ExecBlockObj(omObjData* arg0);
static void CreateBlockObj(s32 arg0);
static void DestroyBlockObj(BlockWork* unused0, omObjData* unused1);
static void SpawnBlock(BlockWork* arg0, omObjData* arg1);
static void HitBlock(BlockWork* arg0, omObjData* arg1);
static void OpenBlock(BlockWork* arg0, omObjData* arg1);
static void SetBlockOpen(void);
static void SetBlockStop(void);
static void WaitBlockHit(void);
static void CreateCoinMdl(void);
static void KillCoinMdl(void);
static void PopupCoin(void);
static void PopupCoinExec(omObjData* arg0);

extern s8 boardTutorialBlockF;
extern s8 boardTutorialBlockItem;

static s16 jumpMot = -1;
static s16 starMdl = -1;

static f32 rotMax;
static f32 scaleAngle;
static f32 rotY;

static omObjData* blockObj;
static Process* blockProc;

static s16 coinMdl[10] = {
    -1, -1, -1, -1, 0, 0, 0, 0, 0, 0
};

static s32 coinF[10];

s32 BoardBlockExec(s32 arg0) {
    if (BoardPlayerSizeGet(arg0) == 2) {
        return 0;
    }
    
    blockProc = HuPrcChildCreate(BlockProc, 0x2003, 0x3800U, 0, boardMainProc);
    HuPrcDestructorSet2(blockProc, DestroyBlock);
    
    while (blockProc != NULL) {
        HuPrcVSleep();
    }
    
    return 0;
}

static void BlockProc(void) {
    s32 sp14[8] = {0x005F0060, 0x001A0060, 0x006D0060, 0x008A0060, 0x00850060, 0x00110060, 0x000D0060, 0x00810060};
    Point3d sp8;
    s32 var_r28;
    s32 var_r29;
    s32 temp_r31;
    BlockWork* temp_r30;
    s32* temp_r4;
    s32 var_r27;
    
    temp_r31 = GWSystem.player_curr;

    var_r27 = GWPlayer[temp_r31].character;
    jumpMot = BoardPlayerMotionCreate(temp_r31, sp14[var_r27]);
    BoardRotateDiceNumbers(temp_r31);
    BoardPlayerMotBlendSet(temp_r31, 0, 0xF);
    omVibrate((s16) temp_r31, 0xC, 0xC, 0);
    CreateBlockObj(temp_r31);
    
    temp_r30 = OM_GET_WORK_PTR(blockObj, BlockWork);
    while (temp_r30->unk00_field1 != 2) {
        HuPrcVSleep();
    }
    
    BoardCameraViewSet(3);
    BoardCameraMotionWait();
    BoardWinCreate(0, 0x10000, -1);
    BoardWinWait();
    BoardWinKill();
    BoardPlayerMotionShiftSet(temp_r31, 0xB, 0, 8.0, 0.0);
    HuPrcSleep(9);
    while (BoardPlayerMotionTimeGet(temp_r31) < 30.0f) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x30C);
    SetBlockOpen();
    while (BoardPlayerMotionEndCheck(temp_r31) == 0) {
        HuPrcVSleep();
    }
    BoardRotateDiceNumbers((s32) temp_r31);
    if (temp_r30->unk00_field3 != 0) {
        SetBlockStop();
        BoardModelPosGet(starMdl, &sp8);
        if (_CheckFlag(0x1000BU) == 0) {
            BoardAudSeqPause(0, 1, 0x3E8);
        }
        BoardStarGive(temp_r31, &sp8);
        if (_CheckFlag(0x1000BU) == 0) {
            BoardAudSeqPause(0, 0, 0x3E8);
        }
    } else {
        var_r29 = 0;
        while (var_r29 < 0x14) {
            WaitBlockHit();
            BoardPlayerMotionStart(temp_r31, (s32) jumpMot, 0);
            BoardPlayerMotionSpeedSet(temp_r31, 2);
            while (BoardPlayerMotionTimeGet(temp_r31) < 4) {
                HuPrcVSleep();
            }
            SetBlockOpen();
            PopupCoin();
            while (BoardPlayerMotionEndCheck(temp_r31) == 0) {
                HuPrcVSleep();
            }
            BoardPlayerMotionStart(temp_r31, 1, 0);
            BoardPlayerCoinsAdd(temp_r31, 1);
            HuAudFXPlay(7);
            HuPrcVSleep();
            var_r29 += 1;
        }
        SetBlockStop();
    }
    if (temp_r30->unk00_field3 != 0) {
        var_r28 = 0x10001;
    } else {
        var_r28 = 0x10002;
    }
    BoardWinCreate(0, var_r28, -1);
    BoardWinWait();
    BoardWinKill();
    KillCoinMdl();
    temp_r30->unk00_field0 = 1;
    BoardRotateDiceNumbers((s32) temp_r31);
    HuPrcVSleep();
    if ((_CheckFlag(0x1000BU) != 0) && temp_r30->unk00_field3 == 0) {
        BoardTutorialHookExec(0x16, 0);
    }
    BoardCameraViewSet(2);
    BoardCameraMotionWait();
    HuPrcEnd();
}

static void DestroyBlock(void) {
    if (jumpMot != -1) {
        BoardPlayerMotionKill(GWSystem.player_curr, (s32) jumpMot);
        jumpMot = -1;
    }
    KillCoinMdl();
    blockProc = 0;
}


static void CreateBlockObj(s32 arg0) {
    Point3d spC;
    BlockWork* temp_r31;
    s8 var_r30;
    
    BoardPlayerPosGet(arg0, &spC);
    starMdl = BoardModelCreate(0x70004, NULL, 0);
    BoardModelVisibilitySet(starMdl, 0);
    BoardModelMotionSpeedSet(starMdl, 0);
    BoardModelLayerSet(starMdl, 2U);
    
    blockObj = omAddObjEx(boardObjMan, 0x101, 0U, 0U, -1, ExecBlockObj);
    
    temp_r31 = OM_GET_WORK_PTR(blockObj, BlockWork);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk00_field2 = 0;
    temp_r31->unk00_field4 = 0;
    temp_r31->unk00_field5 = 0;
    temp_r31->unk00_field1 = 0;
    
    blockObj->trans.x = spC.x;
    blockObj->trans.y = 270 + spC.y;
    blockObj->trans.z = spC.z;
    
    blockObj->scale.x = blockObj->scale.y = blockObj->scale.z = 0.01;
    blockObj->rot.x = blockObj->rot.y = blockObj->rot.z = 0.0;
    
    scaleAngle = 0;
    rotY = 0;
    rotMax = 30;
    
    BoardModelVisibilitySet(starMdl, 1);
    
    if (BoardRandFloat() > 0.5f) {
        var_r30 = 0;
    } else {
        var_r30 = 1;
    }
    
    temp_r31->unk00_field3 = var_r30;
    
    if (boardTutorialBlockF != 0) {
        temp_r31->unk00_field3 = boardTutorialBlockItem;
        boardTutorialBlockF = 0;
    }
    
    HuAudFXPlay(0x302);
    
    if (temp_r31->unk00_field3 == 0) {
        CreateCoinMdl();
    }
}

static void ExecBlockObj(omObjData* arg0) {
    BlockWork* temp_r30;

    temp_r30 = OM_GET_WORK_PTR(arg0, BlockWork);
    
    if (temp_r30->unk00_field0 != 0 || BoardIsKill() != 0) {
        DestroyBlockObj(temp_r30, arg0);
        blockObj = 0;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    
    switch (temp_r30->unk00_field1) {
        case 0:
            SpawnBlock(temp_r30, arg0);
            break;
        case 2:
            HitBlock(temp_r30, arg0);
            break;
        case 3:
            OpenBlock(temp_r30, arg0);
            break;
    }
    
    if (temp_r30->unk00_field5 != 0) {
        BoardModelVisibilitySet(starMdl, 0);
    }
    
    BoardModelPosSet(starMdl, arg0->trans.x, arg0->trans.y, arg0->trans.z);
    BoardModelRotSet(starMdl, arg0->rot.x, arg0->rot.y, arg0->rot.z);
    BoardModelScaleSet(starMdl, arg0->scale.x, arg0->scale.y, arg0->scale.z);
}

static void DestroyBlockObj(BlockWork* unused0, omObjData* unused1) {
    if (starMdl != -1) {
        BoardModelKill(starMdl);
        starMdl = -1;
    }
}

static void SpawnBlock(BlockWork* arg0, omObjData* arg1) {
    f32 temp_f0;

    if (scaleAngle < 90.0f) {
        scaleAngle += 3.75f;
        if (scaleAngle > 90.0f) {
            scaleAngle = 90.0f;
        }
    } else {
        rotMax *= 0.5f;
        if (rotMax < 0.8f) {
            rotY = 0.0f;
            rotMax = 0.0f;
            arg0->unk02 = 0;
            arg0->unk00_field1 = 2;
        }
    }
    
    if (rotY < 360.0f) {
        rotY += rotMax;
        if (rotY > 360.0f) {
            rotY = 360.0f;
        }
    }
    
    arg1->rot.y = rotY;
    arg1->scale.x = arg1->scale.y = arg1->scale.z = sin(M_PI * scaleAngle / 180.0);
}

static void HitBlock(BlockWork* arg0, omObjData* arg1) {
    float var_f30;

    arg0->unk02 += 3;
    if (arg0->unk02 > 0x168) {
        arg0->unk02 -= 0x168;
    }
    OSs16tof32(&arg0->unk02, &var_f30);
    arg1->trans.y = arg1->trans.y + 0.2f * sin((M_PI * var_f30) / 180.0);
}

static void OpenBlock(BlockWork* arg0, omObjData* arg1) {
    s16 sp8;
    f32 temp_f30;

    if (arg0->unk00_field4 == 0) {
        arg0->unk00_field4 = 1;
        HuAudFXPlay(0x33B);
        BoardModelMotionStart(starMdl, 0, 0);
    }
    
    if (arg0->unk00_field2 == 0) {
        OSf32tos16(&arg1->trans.y, &arg0->unk04);
        arg1->trans.y += 80.0f;
        arg0->unk00_field2 = 1;
    } else {
        OSs16tof32(&arg0->unk04, &temp_f30);
        arg1->trans.y += -8.0f;
        
        if (arg1->trans.y < temp_f30) {
            arg1->trans.y = temp_f30;
            arg0->unk00_field1 = 2;
        }
    }
}

static void SetBlockOpen(void) {
    BlockWork* temp_r31;

    temp_r31 = OM_GET_WORK_PTR(blockObj, BlockWork);
    temp_r31->unk00_field1 = 3;
}

static void SetBlockStop(void) {
    BlockWork* temp_r31;

    temp_r31 = OM_GET_WORK_PTR(blockObj, BlockWork);
    temp_r31->unk00_field5 = 1;
}

static void WaitBlockHit(void) {
    BlockWork* temp_r31;

    temp_r31 = OM_GET_WORK_PTR(blockObj, BlockWork);
    
    while (temp_r31->unk00_field1 != 2) {
        HuPrcVSleep();
    }
}

static void CreateCoinMdl(void) {
    s32 i;
    
    for (i = 0; i < 10; i += 1) {
        coinMdl[i] = BoardModelCreate(0x7000A, NULL, 1);
        BoardModelVisibilitySet(coinMdl[i], 0);
        coinF[i] = 0;
    }
}

static void KillCoinMdl(void) {
    s32 i;
    
    for (i = 0; i < 0xA; i += 1) {
        if (coinMdl[i] != -1) {
            BoardModelKill(coinMdl[i]);
            coinMdl[i] = -1;
        }
        coinF[i] = 0;
    }
}

static inline s32 UnkFunc(s16 *var_r26) {
    s32 i;
    
    for (i = 0; i < 10; i++) {
        if (coinF[i] == 0) {
            *var_r26 = coinMdl[i];
            return i;
        }
    }
    
    return -1;
}

static void PopupCoin(void) {
    Point3d sp8;
    omObjData* temp_r3;
    s32 var_r28;
    s16 var_r26;
    CoinWork* temp_r31;
    
    do {
        HuPrcVSleep();
        var_r28 = UnkFunc(&var_r26);
    } while (var_r28 == -1);
    
    temp_r3 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, PopupCoinExec);
    temp_r31 = OM_GET_WORK_PTR(temp_r3, CoinWork);
    
    temp_r31->unk00_field0 = 0;
    temp_r31->unk01 = 0xA;
    temp_r31->unk04 = var_r26;
    temp_r31->unk02 = var_r28;
    
    temp_r3->trans.x = 15.0f;
    temp_r3->trans.y = 40.0f;
    
    BoardModelPosGet(starMdl, &sp8);
    BoardModelPosSetV(temp_r31->unk04, &sp8);
    BoardModelVisibilitySet(temp_r31->unk04, 1);
}

static void PopupCoinExec(omObjData* arg0) {
    Point3d sp14;
    Point3d sp8;
    CoinWork* temp_r31;

    temp_r31 = OM_GET_WORK_PTR(arg0, CoinWork);
    
    if (temp_r31->unk00_field0 != 0 || BoardIsKill() != 0) {
        BoardModelVisibilitySet(temp_r31->unk04, 0);
        coinF[temp_r31->unk02] = 0;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    
    if (temp_r31->unk01 != 0) {
        temp_r31->unk01 -= 1;
    } else {
        temp_r31->unk00_field0 = 1;
        return;
    }
    
    BoardModelPosGet(temp_r31->unk04, &sp14);
    sp14.y += arg0->trans.y;
    BoardModelPosSetV(temp_r31->unk04, &sp14);
    BoardModelRotGet(temp_r31->unk04, &sp8);
    sp8.y += arg0->trans.x;
    
    if (sp8.y > 360.0f) {
        sp8.y -= 360.0f;
    }
    
    BoardModelRotSetV(temp_r31->unk04, &sp8);
}
