#include "game/process.h"
#include "game/gamework_data.h"
#include "game/board/item.h"
#include "game/object.h"

void KillMushroom();
void MushroomMain();
extern Process* boardMainProc;
extern Process* mushroomProc;

void BoardMushroomExec(s32 arg0) {
    omVibrate(arg0, 0xC, 6, 6);
    mushroomProc = HuPrcChildCreate(MushroomMain, 0x2003U, 0x3800U, 0, boardMainProc);
    HuPrcDestructorSet2(mushroomProc, KillMushroom);
    
    while (mushroomProc != NULL) {
        HuPrcVSleep();
    }
    
    GWPlayer[arg0].color = 3;
}

extern s32 boardTutorialData[4];

void MushroomMain(void) {
    Point3d sp14[2];
    Point3d sp8;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 var_r30;
    s32 curPlayer;
    s32 var_r29;
    boxObjWork* box;
    s32 var_r27;
    s32 var_r26;
    s32 i;

    var_r29 = -1;
    curPlayer = GWSystem.player_curr;
    BoardCameraViewSet(3);
    HuAudFXPlay(0x34A);
    BoardPlayerMotBlendSet(curPlayer, 0, 15);
    
    while (BoardPlayerMotBlendCheck(curPlayer) == 0) {
        HuPrcVSleep();
    }
    
    BoardCameraMotionWait();
    BoardPlayerIdleSet(curPlayer);
    
    if (_CheckFlag(0x1000B) != 0) {
        BoardTutorialHookExec(13, 0);
        boardTutorialData[0] = 0;
    }
    
    if ((GWSystem.max_turn - GWSystem.turn) == 0) {
        BoardWinCreate(0, 0x50003U, -1);
        BoardWinWait();
        BoardWinKill();
    } else if (BoardPlayerItemCount(curPlayer) == 3) {
        BoardWinCreate(0, 0x50000U, -1);
        BoardWinWait();
        BoardWinKill();
    } else {
        while (1) {
            InitBox(curPlayer);
            
            while (CheckBox() == 0) {
                HuPrcVSleep();
            }
    
            for (i = 0; i < 2; i++) {
                box = OM_GET_WORK_PTR(boxObj[i], boxObjWork);
                BoardModelPosGet(box->unk_02, &sp8);
                Hu3D3Dto2D(&sp8, 1, &sp14[i]);
                sp14[i].y += 32.0f;
                sp14[i].z = 0.0f;
            }
            
            if (GWPlayer[curPlayer].com != 0) {
                BoardRand();
                var_r26 = 0; //inline?
                var_r29 = (s8)var_r26;
                if (_CheckFlag(0x1000BU) != 0) {
                    var_r29 = 0;
                }
            }
            
            BoardPickerCreate(curPlayer, 2, &sp14[0], var_r29);
            BoardPickerBackFlagSet(0);
            
            while (BoardPickerDoneCheck() == 0) {
                HuPrcVSleep();
            }
            
            pickerChoice = BoardPickerChoiceGet();
            SetBoxShow(pickerChoice);
            SetBoxHide(pickerChoice ^ 1);
            WaitBoxCenter(pickerChoice);
            BoardPlayerMotionStart(curPlayer, 11, 0);
            
            while (BoardPlayerMotionTimeGet(curPlayer) < 27.0f) {
                HuPrcVSleep();
            }
            
            HuAudFXPlay(0x30C);
            StartItemGive(curPlayer);
            WaitBoxOpen(pickerChoice);
            ShowItemMdl();
            SetBoxCenter(pickerChoice);
            
            while (BoardPlayerMotionEndCheck(curPlayer) == 0) {
                HuPrcVSleep();
            }
            
            WaitItemGive();
            
            if (itemResult != 0) {
                var_r27 = 0x50001;
            } else {
                var_r27 = 0x50002;
            }
            
            BoardPlayerMotionShiftSet(curPlayer, 0xC, lbl_801D581C, 4.0f, 0);
            HuPrcSleep(4);
            BoardWinCreate(0, var_r27, -1);
            BoardWinWait();
            BoardWinKill();
            MarkKillBox();
            BoardPlayerMotionEndWait(curPlayer);
            BoardPlayerIdleSet(curPlayer);
            if (_CheckFlag(0x1000BU) != 0) {
                BoardPlayerIdleSet(curPlayer);
                BoardTutorialHookExec(14, 0);
                if (++boardTutorialData[0] < 2) {
                    KillItemMdl();
                    continue;
                }
            }
            break;
        }
    }
    HuPrcEnd();
}

void KillItemMdl(void);
void MarkKillBox(void);
extern omObjData* itemGiveObj;
extern s32 mushroomProc;

void KillMushroom(void) {
    ItemGiveWork2* temp_r31;

    MarkKillBox();
    
    if (itemGiveObj) {
        temp_r31 = OM_GET_WORK_PTR(itemGiveObj, ItemGiveWork2);
        temp_r31->unk00_field0 = 1;
    }
    
    KillItemMdl();
    mushroomProc = 0;
}

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 1;
        u8 unk00_field2 : 3;
        u8 unk00_field5 : 2;
        u8 unk00_field7 : 1;
    };
    char unk01[1];
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    f32 unk_08;
} ItemGiveWork2;

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 1;
        u8 unk00_field2 : 3;
        u8 unk00_field5 : 2;
        u8 unk00_field7 : 1;
    };
    char unk01[1];
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    f32 unk_08;
} boxObjWork;

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 2;
        u8 unk00_field2 : 5;
    };
    char unk01[1];
    s16 unk_02;
    f32 unk_04;
    f32 unk_08;
} itemObjWork;

void BoardModelPosSet(s16, f32, f32, f32);
void BoardModelRotSet(s16, f32, f32, f32);
void CenterBox(ItemGiveWork2*, omObjData*);
void ExitBox(ItemGiveWork2* arg0, omObjData* arg1);
void HideBox(ItemGiveWork2*, omObjData*);
void ShowBox(ItemGiveWork2*, omObjData*);
omObjData* boxObj[2];

void BoxMain(omObjData* arg0) {
    s32 temp_r0;
    ItemGiveWork2* temp_r30;

    temp_r30 = OM_GET_WORK_PTR(arg0, ItemGiveWork2);

    if ((temp_r30->unk00_field0) || (BoardIsKill() != 0)) {
        BoardModelKill(temp_r30->unk_02);
        boxObj[temp_r30->unk00_field1] = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    switch (temp_r30->unk00_field2) {
    case 0:
        ShowBox(temp_r30, arg0);
        break;
    case 2:
        CenterBox(temp_r30, arg0);
        break;
    case 3:
        ExitBox(temp_r30, arg0);
        break;
    case 4:
        HideBox(temp_r30, arg0);
        break;
    }
    BoardModelPosSet(temp_r30->unk_02, arg0->trans.x, arg0->trans.y, arg0->trans.z);
    BoardModelRotSet(temp_r30->unk_02, arg0->rot.x, arg0->rot.y, arg0->rot.z);
}

extern f32 lbl_801D5828;
extern f32 lbl_801D582C;
extern f64 lbl_801D5830;
extern f64 lbl_801D5838;
extern f64 lbl_801D5840;
extern f32 lbl_801D5848;

void ShowBox(ItemGiveWork2* arg0, omObjData* arg1) {
    Point3d sp8;

    BoardPlayerPosGet(arg0->unk00_field5, &sp8);
    sp8.y += lbl_801D5828;
    
    if (arg0->unk_08 >= lbl_801D582C) {
        arg0->unk_08 = lbl_801D582C;
        arg0->unk00_field7 = 1;
        arg0->unk00_field2 = 1;
    }
    
    OSs16tof32(&arg0->unk_06, &arg1->rot.y);
    arg1->trans.y = (sp8.y + (lbl_801D5830 * cos((lbl_801D5838 * (f64) arg0->unk_08) / lbl_801D5840)));
    arg0->unk_08 += lbl_801D5848;
    arg0->unk_06 += 30;
}

extern f32 lbl_801D581C;

void ExitBox(ItemGiveWork2* arg0, omObjData* arg1) {
    Point3d spC;
    s16 sp8;
    f32 temp;

    sp8 = (arg0->unk_06 % 360);
    OSs16tof32(&sp8, &temp);
    BoardPlayerPosGet(arg0->unk00_field5, &spC);
    spC.y += lbl_801D5828;

    if (arg0->unk_08 <= lbl_801D581C) {
        arg0->unk_08 = lbl_801D581C;
        arg0->unk00_field2 = 1;
    }

    arg1->trans.y = spC.y + (lbl_801D5830 * cos((lbl_801D5838 * arg0->unk_08) / lbl_801D5840));
    arg1->rot.y = sin((lbl_801D5838 * temp) / lbl_801D5840);
    arg0->unk_08 -= lbl_801D5848;
    arg0->unk_06 -= 30;
}

void HideBox(ItemGiveWork2* arg0, omObjData* arg1) {
    arg0->unk_04 -= 4;

    if (arg0->unk_04 < 0) {
        arg0->unk00_field2 = 1;
        arg0->unk_04 = 0;
    }

    BoardModelAlphaSet(arg0->unk_02, arg0->unk_04);
}

extern f32 lbl_801D584C;
extern f32 lbl_801D5850;

void CenterBox(ItemGiveWork2* arg0, omObjData* arg1) {
    Point3d sp20;
    Point3d sp14;
    Point3d sp8;

    sp14.x = arg1->trans.x;
    sp14.y = arg1->trans.y;
    sp14.z = arg1->trans.z;
    BoardPlayerPosGet(arg0->unk00_field5, &sp20);
    PSVECSubtract(&sp20, &sp14, &sp8);
    PSVECScale(&sp8, &sp8, lbl_801D584C);
    PSVECAdd(&sp8, &sp14, &sp14);

    if (BoardVecMaxDistXZCheck(&sp20, &sp14, lbl_801D5850) != 0) {
        arg1->trans.x = sp20.x;
        arg1->trans.z = sp20.z;
        arg0->unk00_field2 = 1;
    }
    
    arg1->trans.x = sp14.x;
    arg1->trans.z = sp14.z;
}

void InitBox(s32 arg0) {
    Point3d sp10;
    s32 sp8[2] = {0x0007006D, 0x0007006E};
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 i;
    boxObjWork* temp_r31;

    BoardPlayerPosGet(arg0, &sp10);

    for (i = 0; i < 2; i++) {
        boxObj[i] = omAddObjEx(boardObjMan, 0x101, 0U, 0U, -1, BoxMain);
        temp_r31 = OM_GET_WORK_PTR(boxObj[i], boxObjWork);
        temp_r31->unk00_field0 = 0;
        temp_r31->unk00_field7 = 0;
        temp_r31->unk00_field5 = arg0;
        temp_r31->unk00_field1 = i;
        temp_r31->unk00_field2 = 0;
        temp_r31->unk_06 = 0;
        temp_r31->unk_08 = lbl_801D581C;
        temp_r31->unk_04 = 0xFF;
        boxObj[i]->trans.x = sp10.x + boxOfs[i];
        boxObj[i]->trans.y = lbl_801D585C + sp10.y;
        boxObj[i]->trans.z = sp10.z;
        boxObj[i]->rot.x = lbl_801D581C;
        boxObj[i]->rot.y = lbl_801D5860;
        boxObj[i]->rot.z = lbl_801D581C;
        temp_r31->unk_02 = BoardModelCreate(0x70005, NULL, 0);
        BoardModelPosSet(temp_r31->unk_02, boxObj[i]->trans.x, boxObj[i]->trans.y, boxObj[i]->trans.z);
        BoardModelMotionSpeedSet(temp_r31->unk_02, lbl_801D581C);
        BoardModelLayerSet(temp_r31->unk_02, 2U);        
    }
    
    HuAudFXPlay(0x340);
    if (BoardRandFloat() < lbl_801D5864) {
        var_r28 = 0;
    } else {
        var_r28 = 1;
    }
    itemResult = (s8) var_r28;
    if (BoardRandFloat() < lbl_801D5864) {
        var_r27 = 0;
    } else {
        var_r27 = 1;
    }
    var_r29 = var_r27;
    if (GWBoardGet() == 8) {
        itemResult = 0;
    }
    if (_CheckFlag(0x1000BU) != 0) {
        itemResult = (boardTutorialData[0] ^ 1);
        var_r29 = 0;
    }
    itemMdl = BoardModelCreate(sp8[itemResult], NULL, 0);
    BoardModelVisibilitySet(itemMdl, 0);
    temp_r31 = OM_GET_WORK_PTR(boxObj[var_r29], boxObjWork);
    BoardModelScaleSet(temp_r31->unk_02, lbl_801D5848, lbl_801D5848, lbl_801D5848);
}

void MarkKillBox(void) {
    s32 i;
    boxObjWork* temp_r30;

    for (i = 0; i < ARRAY_COUNT(boxObj); i++) {
        if (boxObj[i]) {
            temp_r30 = OM_GET_WORK_PTR(boxObj[i], boxObjWork);
            temp_r30->unk00_field0 = 1;            
        }
    }
}

void SetBoxHide(s32 arg0) {
    boxObjWork* temp_r31 = OM_GET_WORK_PTR(boxObj[arg0], boxObjWork);

    temp_r31->unk00_field2 = 3;
}

void SetBoxCenter(s32 arg0) {
    boxObjWork* temp_r31 = OM_GET_WORK_PTR(boxObj[arg0], boxObjWork);
    
    temp_r31->unk00_field2 = 4;
    HuAudFXPlay(0x341);
}

void SetBoxShow(s32 arg0) {
    boxObjWork* temp_r31 = OM_GET_WORK_PTR(boxObj[arg0], boxObjWork);

    temp_r31->unk00_field2 = 2;
}

extern f32 lbl_801D5868;

void WaitBoxOpen(s32 arg0) {
    boxObjWork* temp_r31 = OM_GET_WORK_PTR(boxObj[arg0], boxObjWork);
    
    BoardModelMotionSpeedSet(temp_r31->unk_02, lbl_801D5868);
    do {
        HuPrcVSleep();
    } while (BoardModelMotionEndCheck(temp_r31->unk_02) == 0);
}

void WaitBoxCenter(s32 arg0) {
    boxObjWork* temp_r31 = OM_GET_WORK_PTR(boxObj[arg0], boxObjWork);

    while (temp_r31->unk00_field2 != 1) {
        HuPrcVSleep();
    }
}

s32 CheckBox(void) {
    s32 i;
    boxObjWork* box;
    
    for (i = 0; i < ARRAY_COUNT(boxObj); i++) {
        box = OM_GET_WORK_PTR(boxObj[i], boxObjWork);
        if (box->unk00_field7 == 0) {
            return 0;
        }
    }
    return 1;
}

extern f32 lbl_801D5860;
extern s32 lbl_801D586C;
extern s32 lbl_801D5870;
extern f32 lbl_801D5874;
extern f32 lbl_801D5878;
extern f32 lbl_801D587C;
extern f32 lbl_801D5880;
extern f32 lbl_801D5884;
extern s8 itemResult;

void DoItemGive(omObjData* arg0) {
    Point3d sp28;
    Point3d sp1C;
    Point3d sp10;
    s32 sp8[2] = {0, 1};
    itemObjWork* temp_r31;

    temp_r31 = OM_GET_WORK_PTR(arg0, itemObjWork);
    
    if ((temp_r31->unk00_field0 != 0) || (BoardIsKill() != 0)) {
        KillItemMdl();
        itemGiveObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    
    BoardModelPosGet(itemMdl, &sp28);
    BoardModelRotGet(itemMdl, &sp1C);
    BoardPlayerPosGet(temp_r31->unk00_field1, &sp10);
    sp10.y += lbl_801D5860;
    
    switch (temp_r31->unk00_field2) {
    case 2:
        if (temp_r31->unk_02 < 12) {
            temp_r31->unk_04 += lbl_801D5874;
            sp28.y += temp_r31->unk_04;
        } else if (temp_r31->unk_02 <= 24) {
            BoardModelRotSet(itemMdl, lbl_801D5878 * temp_r31->unk_02, lbl_801D581C, lbl_801D581C);
        } else if (temp_r31->unk_02 > 36) {
            temp_r31->unk00_field2 = 0;
            return;
        }
        temp_r31->unk_02++;
        break;
    case 0:
        temp_r31->unk_04 += lbl_801D587C;
        
        if (temp_r31->unk_08 > lbl_801D5880) {
            temp_r31->unk_08 -= lbl_801D5884;
        }
        
        sp28.y += temp_r31->unk_04;
        
        if (sp10.y > sp28.y) {
            BoardModelVisibilitySet(itemMdl, 0);
            HuAudFXPlay(0x30D);
            BoardPlayerItemAdd(temp_r31->unk00_field1, sp8[itemResult]);
            temp_r31->unk00_field2 = 1;
        }
        /* fallthrough */
        case 1:
        default:
            break;
    }

    BoardModelPosSetV(itemMdl, &sp28);
    BoardModelScaleSet(itemMdl, temp_r31->unk_08, temp_r31->unk_08, temp_r31->unk_08);
}

extern Process *boardObjMan;
void DoItemGive(omObjData*);
extern s16 itemMdl;
extern f32 lbl_801D5890;
extern u8 pickerChoice;

void StartItemGive(s32 arg0) {
    Point3d spC;
    itemObjWork* temp_r31;
    boxObjWork* box;

    itemGiveObj = omAddObjEx(boardObjMan, 0x102, 0U, 0U, -1, DoItemGive);
    temp_r31 = OM_GET_WORK_PTR(itemGiveObj, itemObjWork);

    temp_r31->unk00_field0 = 0;
    temp_r31->unk00_field1 = arg0;
    temp_r31->unk00_field2 = 1;
    temp_r31->unk_02 = 0;
    temp_r31->unk_04 = lbl_801D581C;
    temp_r31->unk_08 = lbl_801D5890;
    box = OM_GET_WORK_PTR(boxObj[pickerChoice], boxObjWork);
    BoardModelPosGet(box->unk_02, &spC);
    BoardModelPosSetV(itemMdl, &spC);
}

void KillItemMdl(void) {
    if (itemMdl != -1) {
        BoardModelKill(itemMdl);
        itemMdl = -1;
    }
}

void ShowItemMdl(void) {
    itemObjWork* temp_r31 = OM_GET_WORK_PTR(itemGiveObj, itemObjWork);
    temp_r31->unk00_field2 = 2;

    BoardModelVisibilitySet(itemMdl, 1);
}

void WaitItemGive(void) {
    itemObjWork* temp_r31 = OM_GET_WORK_PTR(itemGiveObj, itemObjWork);

    while (temp_r31->unk00_field2 != 1) {
        HuPrcVSleep();
    }
}