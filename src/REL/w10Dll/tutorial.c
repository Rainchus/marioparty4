#include "REL/w10Dll.h"
#include "game/esprite.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/board/ui.h"

void fn_1_1984(void) {
    s32 port;
    s32 i;

    if (lbl_1_bss_C == 0) {
        if (WipeStatGet() != 0) {
            HuWinDispOff(lbl_1_bss_E);
            return;
        }
        HuWinDispOn(lbl_1_bss_E);
        if (BoardIsKill() != 0) {
            return;
        }
        for (i = 0; i < ARRAY_COUNT(GWPlayer); i++) {
            port = GWPlayer[i].port;
            if (port == -1) {
                continue;
            }
            if (HuPadStatGet(port) == 0 && HuPadBtnDown[port] & PAD_BUTTON_START) {
                break;
            }
        }
        if (i != 4) {
            lbl_1_bss_C = 1;
            OSReport("@@@@@@@@@@@@@@ Tutorial Exit @@@@@@@@@@@@@@\n");
            BoardAudSeqFadeOut(0, 0x1F3);
            BoardKill();
            BoardTutorialHookSet(NULL);
        }
    }
}

s16 lbl_1_data_C6[11][3] = {
	1, -1, -1,
	2, -1, -1,
	4, -1, -1,
	5, -1, -1,
	5, -1, -1,
	4, -1, -1,
	1, -1, -1,
	3, -1, -1,
	2, -1, -1,
	4, -1, -1,
	5, 6, -1,
};

w10DllUnk04 lbl_1_data_108[42] = {
	{0x0000, 0000, fn_1_D2C},
	{0x0001, 0000, fn_1_D54},
	{0x0002, 0000, fn_1_D7C},
	{0x0003, 0000, fn_1_DA4},
	{0x0003, 0000, fn_1_DCC},
	{0x0003, 0000, fn_1_DF4},
	{0x0003, 0000, fn_1_E1C},
	{0x0004, 0000, fn_1_E44},
	{0x0005, 0000, fn_1_E94},
	{0x0006, 0000, fn_1_EBC},
	{0x0007, 0000, fn_1_EE4},
	{0x000A, 0000, fn_1_EE8},
	{0x000B, 0000, fn_1_F30},
	{0x0010, 0000, fn_1_F6C},
	{0x0011, 0000, fn_1_FB8},
	{0x000C, 0000, fn_1_1010},
	{0x000D, 0000, fn_1_105C},
	{0x000E, 0000, fn_1_1098},
	{0x000E, 0000, fn_1_10C0},
	{0x000F, 0000, fn_1_10F8},
	{0x0012, 0000, fn_1_1134},
	{0x0014, 0000, fn_1_1178},
	{0x0015, 0000, fn_1_11A0},
	{0x0016, 0000, fn_1_11EC},
	{0x0005, 0000, fn_1_1240},
	{0x0017, 0000, fn_1_1278},
	{0x0007, 0000, fn_1_12A0},
	{0x0005, 0000, fn_1_12DC},
	{0x0017, 0000, fn_1_1304},
	{0x0018, 0000, fn_1_132C},
	{0x0019, 0000, fn_1_1354},
	{0x0008, 0000, fn_1_137C},
	{0x0009, 0000, fn_1_13A4},
	{0x001A, 0000, fn_1_176C},
	{0x001B, 0000, fn_1_179C},
	{0x001B, 0000, fn_1_17F4},
	{0x001B, 0000, fn_1_1834},
	{0x001B, 0000, fn_1_18BC},
	{0x001C, 0000, fn_1_1908},
	{0x001C, 0000, fn_1_1930},
	{0x001C, 0000, fn_1_1958},
	{-1, 0, 0},
};

int fn_1_1AAC(s16 arg0, s32 arg1) {
    if (arg0 == 0x1E) {
        fn_1_1984();
        return;
    }
    if (arg0 != 0x1D) {
        OSReport("Tutorial Hook P0:%d P1:%d P2:%d P3:%d  SCEN:%d  CUE:%d  PRM:%d DICE:%d  MSG:%d\n",
            GWPlayer[0].com, GWPlayer[1].com,
            GWPlayer[2].com, GWPlayer[3].com,
            lbl_1_bss_0->unk0, arg0, arg1, lbl_1_bss_0->unk4, lbl_1_bss_0->unk6);
        if (lbl_1_data_108[lbl_1_bss_0->unk0].unk0 != -1) {
            if (arg0 == 5) {
                BoardRollTutorialSet(&lbl_1_data_C6[lbl_1_bss_0->unk4++][0]);
            }
            if (arg0 == lbl_1_data_108[lbl_1_bss_0->unk0].unk0) {
                void (*temp_r3_3)() = lbl_1_data_108[lbl_1_bss_0->unk0++].unk4;
                temp_r3_3();
            }
        }
    }
}

s32 lbl_1_data_2A8[11] = {
    DATA_MAKE_NUM(DATADIR_W10, 4),
    DATA_MAKE_NUM(DATADIR_W10, 5),
    DATA_MAKE_NUM(DATADIR_W10, 6),
    DATA_MAKE_NUM(DATADIR_W10, 7),
    DATA_MAKE_NUM(DATADIR_W10, 8),
    DATA_MAKE_NUM(DATADIR_W10, 9),
    DATA_MAKE_NUM(DATADIR_W10, 10),
    DATA_MAKE_NUM(DATADIR_W10, 11),
    DATA_MAKE_NUM(DATADIR_W10, 12),
    DATA_MAKE_NUM(DATADIR_W10, 13),
    DATA_MAKE_NUM(DATADIR_W10, 14)
};

void fn_1_1D68(void) {
    s32 temp_r4;
    s32 temp_r5;
    s32 i;

    for (i = 0; i < 11; i++) {
        lbl_1_bss_22[i] = espEntry(lbl_1_data_2A8[i], 0, 0);
        espDispOff(lbl_1_bss_22[i]);
    }
}

void fn_1_1DEC(void) {
    s32 i;

    for (i = 0; i < 11; i++) {
        espKill(lbl_1_bss_22[i]);
    }
}

void fn_1_1E3C(s16 arg0, s16 arg1, s16 arg2) {
    f32 var_f31;
    f32 var_f30;
    u32 i;

    lbl_1_bss_20 = lbl_1_bss_22[arg0];
    espPosSet(lbl_1_bss_20, arg1, arg2);
    var_f31 = 0.0f;
    var_f30 = 0.0f;
    espDispOn(lbl_1_bss_20);
    for (i = 0; i < 15; i++) {
        var_f31 += 0.06666667f;
        var_f30 += 0.06666667f;
        espScaleSet(lbl_1_bss_20, var_f31, var_f30);
        HuPrcVSleep();        
    }
    espScaleSet(lbl_1_bss_20, 1.0f, 1.0f);
}

void fn_1_1FB0(void) {
    f32 var_f31;
    f32 var_f30;
    u32 i;

    var_f31 = 1.0f;
    var_f30 = 1.0f;
    for (i = 0; i < 15; i++) {
        var_f31 -= 0.06666667f;
        var_f30 -= 0.06666667f;
        espScaleSet(lbl_1_bss_20, var_f31, var_f30);
        HuPrcVSleep();        
    }
    espDispOff(lbl_1_bss_20);
}