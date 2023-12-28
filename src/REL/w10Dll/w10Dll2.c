#include "REL/w10Dll.h"
#include "game/data.h"

s32 lbl_1_data_78[2] = {
    MAKE_DATA_NUM(DATADIR_W10, 16),
    -1
};

Vec lbl_1_data_80[2] = {
    {70.0f, 355.0f, 200.f},
    {70.0f, 175.0f, 200.f},
};

void fn_1_AEC(void) {
    lbl_1_bss_1C = 0;
    lbl_1_bss_1E = BoardModelCreate(MAKE_DATA_NUM(DATADIR_W10, 15), &lbl_1_data_78, 0);
    BoardModelMotionStart(lbl_1_bss_1E, 1, 0x40000001);
    fn_800B42BC(lbl_1_bss_1E);
    BoardModelLayerSet(lbl_1_bss_1E, 6);
    lbl_1_bss_18 = HuPrcCreate(fn_1_C20, 0x1FFF, 0x1800, 0);
}

void fn_1_BA0(s32 arg0) {
    s32 var_r31;

    switch (lbl_1_bss_1C) {
    case 0:
        var_r31 = 5;
        break;
    case 1:
        var_r31 = 6;
        break;
    }
    BoardWinCreate(var_r31, arg0, -1);
    BoardWinWait();
    BoardWinKill();
}

void fn_1_C10(s16 arg0) {
    lbl_1_bss_1C = arg0;
}

void fn_1_C20(void) {
    Mtx sp20;
    Vec sp14;
    Vec sp8;
    
    while (1) {
        if (BoardIsKill() != 0) {
            BoardModelKill(lbl_1_bss_1E);
            fn_800B42BC(-1);
            HuPrcEnd();
        }
        Hu3D2Dto3D(&lbl_1_data_80[lbl_1_bss_1C], 1, &sp14);
        BoardModelPosSetV(lbl_1_bss_1E, &sp14);
        BoardCameraRotGet(&sp8);
        PSMTXRotRad(sp20, 'y', 0.2617994f);
        BoardModelMtxSet(lbl_1_bss_1E, sp20);
        BoardModelRotSet(lbl_1_bss_1E, sp8.x, 0.0f, 0.0f);
        BoardModelScaleSet(lbl_1_bss_1E, 0.2f, 0.2f, 0.2f);
        HuPrcVSleep();        
    }
}