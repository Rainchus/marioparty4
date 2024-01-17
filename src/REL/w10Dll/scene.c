#include "include/REL/w10Dll.h"

void fn_1_D2C(void) {
    fn_1_BA0(0x2E0001);
}

void fn_1_D54(void) {
    fn_1_BA0(0x2E0002);
}

void fn_1_D7C(void) {
    fn_1_BA0(0x2E0003);
}

void fn_1_DA4(void) {
    fn_1_BA0(0x2E0004);
}

void fn_1_DCC(void) {
    fn_1_BA0(0x2E0005);
}

void fn_1_DF4(void) {
    fn_1_BA0(0x2E0006);
}

void fn_1_E1C(void) {
    fn_1_BA0(0x2E0007);
}

void fn_1_E44(void) {
    fn_1_BA0(0x2E0008);
    fn_1_BA0(0x2E0009);
    BoardSpaceStarSetIndex(0);
    BoardModelVisibilitySet(lbl_1_data_2C, 1);
}

void fn_1_E94(void) {
    fn_1_BA0(0x2E000A);
}

void fn_1_EBC(void) {
    fn_1_BA0(0x2E000B);
}

void fn_1_EE4(void) {

}

void fn_1_EE8(void) {
    fn_1_1E3C(0, 0x122, 0x8C);
    fn_1_BA0(0x2E000C);
    fn_1_BA0(0x2E000D);
    fn_1_1FB0();
}

void fn_1_F30(void) {
    fn_1_1E3C(1, 0x122, 0x8C);
    fn_1_BA0(0x2E000E);
    fn_1_1FB0();
}

void fn_1_F6C(void) {
    fn_1_1E3C(2, 0x122, 0x8C);
    fn_1_BA0(0x2E000F);
    fn_1_1FB0();
    BoardTutorialDirInputSet(0, 0x50, 1);
}

void fn_1_FB8(void) {
    fn_1_1E3C(3, 0x122, 0x8C);
    fn_1_BA0(0x2E0010);
    fn_1_1FB0();
    fn_1_BA0(0x2E0011);
    BoardTutorialDirInputSet(-0x50, 0, 1);
}

void fn_1_1010(void) {
    fn_1_1E3C(4, 0x122, 0x8C);
    fn_1_BA0(0x2E0012);
    fn_1_1FB0();
    BoardTutorialDirInputSet(0, 0x50, 1);
}

void fn_1_105C(void) {
    fn_1_1E3C(5, 0x122, 0x8C);
    fn_1_BA0(0x2E0013);
    fn_1_1FB0();
}

void fn_1_1098(void) {
    fn_1_BA0(0x2E0014);
}

void fn_1_10C0(void) {
    fn_1_BA0(0x2E0015);
    BoardTutorialDirInputSet(-0x50, 0, 1);
}

void fn_1_10F8(void) {
    fn_1_1E3C(6, 0x122, 0x8C);
    fn_1_BA0(0x2E0016);
    fn_1_1FB0();
}

void fn_1_1134(void) {
    fn_1_1E3C(7, 0x122, 0x8C);
    fn_1_BA0(0x2E0017);
    fn_1_1FB0();
    BoardCharWheelSetTarget(1);
}

void fn_1_1178(void) {
    fn_1_BA0(0x2E0018);
}

void fn_1_11A0(void) {
    s32 temp;
    
    fn_1_BA0(0x2E0019);
    temp = BoardSpaceFlagSearch(0, 1);
    BoardTutorialBlockSetPos(temp, 0);
}

void fn_1_11EC(void) {
    s32 temp;
    
    fn_1_BA0(0x2E001A);
    temp = BoardSpaceFlagSearch(0, 1);
    BoardTutorialBlockSetPos(temp, 0);
    BoardTutorialItemSet(0);
}

void fn_1_1240(void) {
    fn_1_BA0(0x2E001B);
    BoardTutorialDirInputSet(0x50, 0, 1);
}

void fn_1_1278(void) {
    fn_1_BA0(0x2E001C);
}

void fn_1_12A0(void) {
    fn_1_BA0(0x2E001D);
    BoardPlayerItemAdd(2, 1);
    BoardTutorialItemSet(1);
}

void fn_1_12DC(void) {
    fn_1_BA0(0x2E001E);
}

void fn_1_1304(void) {
    fn_1_BA0(0x2E001F);
}

void fn_1_132C(void) {
    fn_1_BA0(0x2E0020);
}

void fn_1_1354(void) {
    fn_1_BA0(0x2E0021);
}

void fn_1_137C(void) {
    fn_1_BA0(0x2E0022);
}

void fn_1_13A4(void) {
    s32 i;
    Vec sp14;
    Vec sp8;
    s32 temp_r3_2;
    
    fn_1_BA0(0x2E0023);
    for (i = 0; i < 4; i++) {
        GWPlayer[i].color = 1;
    }
    fn_800A4C88();
    BoardStatusShowSetAll(0);
    fn_1_C10(0);
    fn_1_BA0(0x2E002B);
    sp8.x = -33.0f;
    sp8.y =  sp8.z = 0.0f;
    temp_r3_2 = BoardSpaceFlagSearch(0, 0x80000);
    BoardSpacePosGet(0, temp_r3_2, &sp14);
    BoardModelPosSetV(lbl_1_bss_0->unk8, &sp14);
    BoardCameraMotionStartEx(lbl_1_bss_0->unk8, &sp8, NULL, 3200.0f, -1.0f, 30);
    BoardCameraMotionWait();
    fn_1_BA0(0x2E002C);
    BoardShopTutorialExec(temp_r3_2);
    BoardCameraMotionStartEx(lbl_1_bss_0->unk8, &sp8, NULL, 3200.0f, -1.0f, 30);
    BoardCameraMotionWait();
    temp_r3_2 = BoardSpaceFlagSearch(0, 0x10000000);
    BoardSpacePosGet(0, temp_r3_2, &sp14);
    BoardModelPosSetV(lbl_1_bss_0->unk8, &sp14);
    BoardCameraMotionStartEx(lbl_1_bss_0->unk8, &sp8, NULL, 3200.0f, -1.0f, 30);
    BoardCameraMotionWait();
    fn_1_BA0(0x2E002E);
    BoardLotteryTutorialExec();
    BoardCameraMotionStartEx(lbl_1_bss_0->unk8, &sp8, NULL, 3200.0f, -1.0f, 30);
    BoardCameraMotionWait();
    temp_r3_2 = BoardSpaceFlagSearch(0, 0x08000000);
    BoardSpacePosGet(0, temp_r3_2, &sp14);
    BoardModelPosSetV(lbl_1_bss_0->unk8, &sp14);
    BoardCameraMotionStartEx(lbl_1_bss_0->unk8, &sp8, NULL, 3200.0f, -1.0f, 30);
    BoardCameraMotionWait();
    fn_1_BA0(0x2E0030);
    fn_800A6B10();
    BoardCameraMotionStartEx(lbl_1_bss_0->unk8, &sp8, NULL, 3200.0f, -1.0f, 30);
    BoardCameraMotionWait();
    fn_1_BA0(0x2E0032);
    BoardCameraTargetModelSet(BoardStarHostMdlGet());
    BoardCameraMotionWait();
    fn_1_BA0(0x2E0033);
    fn_1_BA0(0x2E0034);
    fn_1_1E3C(8, 0x122, 0x8C);
    fn_1_BA0(0x2E0035);
    fn_1_1FB0();
    fn_1_1E3C(9, 0x122, 0x8C);
    fn_1_BA0(0x2E0036);
    fn_1_1FB0();
    fn_1_1E3C(0xA, 0x122, 0x8C);
    fn_1_BA0(0x2E0037);
    fn_1_1FB0();
    fn_1_BA0(0x2E0038);
    fn_1_BA0(0x2E0039);
    if (lbl_1_bss_C == 0) {
        lbl_1_bss_C = 1;
        fn_80070EE8(0, 0x1F3);
        BoardKill();
    }
    BoardTutorialHookSet(NULL);
    while (1) {
        HuPrcVSleep();
    }
}
