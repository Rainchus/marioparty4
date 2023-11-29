#include "include/REL/w10Dll.h"

char lbl_1_data_98[] = "@@@@@@@@@@@@@@ Tutorial Exit @@@@@@@@@@@@@@\n\000";

w10DllUnk03 lbl_1_data_C6[11] = {
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

char lbl_1_data_258[] = "Tutorial Hook P0:%d P1:%d P2:%d P3:%d  SCEN:%d  CUE:%d  PRM:%d DICE:%d  MSG:%d\n";

s32 lbl_1_data_2A8[11] = {
0x007B0004,
0x007B0005,
0x007B0006,
0x007B0007,
0x007B0008,
0x007B0009,
0x007B000A,
0x007B000B,
0x007B000C,
0x007B000D,
0x007B000E
};

void fn_1_13A4(void) {
    s32 i;
    Vec3f sp14;
    Vec3f sp8;
    s32 temp_r3_2;
    
    fn_1_BA0(0x2E0023);
    for (i = 0; i < 4; i++) {
        gPlayerData[i].flags.unk0 = 1;
    }
    fn_800A4C88();
    fn_800884F4(0);
    fn_1_C10(0);
    fn_1_BA0(0x2E002B);
    sp8.x = -33.0f;
    sp8.y =  sp8.z = 0.0f;
    temp_r3_2 = fn_800745F0(0, 0x80000);
    fn_80074210(0, temp_r3_2, &sp14);
    fn_8006F158(lbl_1_bss_0->unk8, &sp14);
    fn_8005DB6C(lbl_1_bss_0->unk8, &sp8, 0, 3200.0f, -1.0f, 0x1E);
    fn_8005E0C0();
    fn_1_BA0(0x2E002C);
    fn_8007A360(temp_r3_2);
    fn_8005DB6C(lbl_1_bss_0->unk8, &sp8, 0, 3200.0f, -1.0f, 0x1E);
    fn_8005E0C0();
    temp_r3_2 = fn_800745F0(0, 0x10000000);
    fn_80074210(0, temp_r3_2, &sp14);
    fn_8006F158(lbl_1_bss_0->unk8, &sp14);
    fn_8005DB6C(lbl_1_bss_0->unk8, &sp8, 0, 3200.0f, -1.0f, 0x1E);
    fn_8005E0C0();
    fn_1_BA0(0x2E002E);
    fn_8007F894();
    fn_8005DB6C(lbl_1_bss_0->unk8, &sp8, 0, 3200.0f, -1.0f, 0x1E);
    fn_8005E0C0();
    temp_r3_2 = fn_800745F0(0, 0x08000000);
    fn_80074210(0, temp_r3_2, &sp14);
    fn_8006F158(lbl_1_bss_0->unk8, &sp14);
    fn_8005DB6C(lbl_1_bss_0->unk8, &sp8, 0, 3200.0f, -1.0f, 0x1E);
    fn_8005E0C0();
    fn_1_BA0(0x2E0030);
    fn_800A6B10();
    fn_8005DB6C(lbl_1_bss_0->unk8, &sp8, 0, 3200.0f, -1.0f, 0x1E);
    fn_8005E0C0();
    fn_1_BA0(0x2E0032);
    fn_80083F84();
    fn_8005D8E8();
    fn_8005E0C0();
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
        fn_8005B5FC();
    }
    fn_800B3FD8(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_176C(void) {
    fn_1_C10(1);
    fn_1_BA0(0x2E0024);
}

void fn_1_179C(void) {
    fn_1_BA0(0x2E0025);
    gPlayerData[1].flags.unk0 = 2;
    gPlayerData[3].flags.unk0 = 2;
}

void fn_1_17F4(void) {
    fn_1_BA0(0x2E0026);
    gPlayerData[0].flags.unk0 = 2;
}

void fn_1_1834(void) {
    fn_1_BA0(0x2E0027);
    gPlayerData[0].flags.unk0 = 1;
    gPlayerData[1].flags.unk0 = 1;
    gPlayerData[2].flags.unk0 = 1;
    gPlayerData[3].flags.unk0 = 2;
}

void fn_1_18BC(void) {
    fn_1_BA0(0x2E0028);
    fn_1_BA0(0x2E0029);
    lbl_801A52E8 = 0;
    fn_8008853C(0);
}

void fn_1_1908(void) {
    fn_1_BA0(0x2E002D);
}

void fn_1_1930(void) {
    fn_1_BA0(0x2E002F);
}

void fn_1_1958(void) {
    fn_1_BA0(0x2E0031);
}

void fn_1_1980(void) {

}

void fn_1_1984(void) {
    s32 contPortIndex;
    s32 i;

    if (lbl_1_bss_C == 0) {
        if (fn_80041600() != 0) {
            HuWinDispOff(lbl_1_bss_E);
            return;
        }
        HuWinDispOn(lbl_1_bss_E);
        if (fn_8005B6A8() != 0) {
            return;
        }
        for (i = 0; i < ARRAY_COUNT(gPlayerData); i++) {
            contPortIndex = gPlayerData[i].controllerPort;
            if (contPortIndex == -1) {
                continue;
            }
            if (HuPadStatGet(contPortIndex) == 0 && HuPadBtnDown[contPortIndex] & 0x1000) {
                break;
            }
        }
        if (i != 4) {
            lbl_1_bss_C = 1;
            OSReport(lbl_1_data_98);
            fn_80070EE8(0, 0x1F3);
            fn_8005B5FC();
            fn_800B3FD8(NULL);
        }
    }
}

int fn_1_1AAC(s16 arg0, s32 arg1) {
    s32 i;
    if (arg0 == 0x1E) {
        if (lbl_1_bss_C == 0) {
            if (fn_80041600() != 0) {
                HuWinDispOff(lbl_1_bss_E);
            } else {
                HuWinDispOn(lbl_1_bss_E);
                if (fn_8005B6A8() == 0) {
                    s32 contPortIndex;
                    for (i = 0; i < ARRAY_COUNT(gPlayerData); i++) {
                        contPortIndex = gPlayerData[i].controllerPort;
                        if (contPortIndex == -1) {
                            continue;
                        }
                        if (HuPadStatGet(contPortIndex) == 0 && HuPadBtnDown[contPortIndex] & 0x1000) {
                            break;
                        }
                    }
                    if (i != 4) {
                        lbl_1_bss_C = 1;
                        OSReport(lbl_1_data_98);
                        fn_80070EE8(0, 0x1F3);
                        fn_8005B5FC();
                        fn_800B3FD8(NULL);
                    }
                }
            }
        }
        return;
    }
    if (arg0 != 0x1D) {
        OSReport(lbl_1_data_258,
            (gPlayerData[0].characterID >> 5) & 1, (gPlayerData[1].characterID >> 5) & 1,
            (gPlayerData[2].characterID >> 5) & 1, (gPlayerData[3].characterID >> 5) & 1,
            lbl_1_bss_0->unk0, arg0, arg1, lbl_1_bss_0->unk4, lbl_1_bss_0->unk6);
        if (lbl_1_data_108[lbl_1_bss_0->unk0].unk0 != -1) {
            if (arg0 == 5) {
                fn_8008831C(&lbl_1_data_C6[lbl_1_bss_0->unk4++]);
            }
            if (arg0 == lbl_1_data_108[lbl_1_bss_0->unk0].unk0) {
                void (*temp_r3_3)() = lbl_1_data_108[lbl_1_bss_0->unk0++].unk4;
                temp_r3_3();
            }
        }
    }
}

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
