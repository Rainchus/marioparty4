#include "include/REL/w10Dll.h"

//BSS
BoardStateSubStruct* lbl_1_bss_0;
s32 lbl_1_bss_4_pad;
void* lbl_1_bss_8;
s16 lbl_1_bss_C;
s16 lbl_1_bss_E;
s16 lbl_1_bss_10[4];
Process* lbl_1_bss_18;
s16 lbl_1_bss_1C;
s16 lbl_1_bss_1E;
s16 lbl_1_bss_20;
s16 lbl_1_bss_22[11];


//DATA
unkw10Dll lbl_1_data_0[1] = {
    3300.0f, 100.0f, -900.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    0x007B0003
};


s16 lbl_1_data_28 = -1;
s16 lbl_1_data_2A = -1;
s16 lbl_1_data_2C = -1;
s16 lbl_1_data_2E = -1;
s16 lbl_1_data_30 = -1;
s16 lbl_1_data_32 = -1;

//unused?
s16 lbl_1_data_34[] = {
0x005F, 0x0000, 0x001A, 0x0000,
0x006D, 0x0000, 0x008A, 0x0000,
0x0085, 0x0000, 0x0011, 0x0000,
0x000D, 0x0000, 0x0081, 0x0000
};

s32 lbl_1_data_54[2] = {
    0x007B0012,
    -1
};

s32 lbl_1_data_5C[2] = {
    0x00020009,
    -1
};

s32 lbl_1_data_64[2] = {
    0x00020018,
    -1
};

s32 lbl_1_data_6C[2] = {
    0x0002000E,
    -1
};

s32 lbl_1_data_78[2] = {
    0x007B0010,
    -1
};

Vec3f lbl_1_data_80[2] = {
    {70.0f, 355.0f, 200.f},
    {70.0f, 175.0f, 200.f},
};

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

// function is probably global. only inlined in rels?
inline s32 get_current_board(void) {
    return lbl_8018FCF8.unk08 & 0x1F;
}

void fn_1_E0(void) {
    f32 sp10;
    f32 spC;
    s32 sp8;
    
    s32 i;
    unkw10Dll* temp_r30;
    s32 temp;
    s32 temp2;

    temp2 = get_current_board();
    lbl_1_bss_0 = &lbl_8018FCF8.unk10;
    lbl_1_bss_0->unk0 = 0;
    lbl_1_bss_0->unk4 = 0;
    lbl_1_bss_0->unk6 = 0;
    fn_800B3FD8(&fn_1_1AAC);
    fn_1_AEC();
    fn_1_1D68();
    lbl_1_bss_C = 0;
    fn_800772EC(0x7B0000);
    temp = fn_800745F0(0, 1);
    fn_800B4274(temp, 1);
    lbl_1_data_28 = fn_8006D9A4(0x7B0001, NULL, 0);
    fn_8006DDE8(lbl_1_data_28, -1.0f);
    fn_8006F1A8(lbl_1_data_28, 0.0f, 0.0f, 0.0f);
    fn_8006E2B8(lbl_1_data_28, 0, 0x40000001);
    fn_8006E878(lbl_1_data_28, 1.0f);
    lbl_1_data_2A = fn_8006D9A4(0x7B0002, NULL, 0);
    fn_8006DDE8(lbl_1_data_2A, -1.0f);
    fn_8006F1A8(lbl_1_data_2A, 0.0f, 0.0f, 0.0f);
    fn_8006E2B8(lbl_1_data_2A, 0, 0x40000001);
    lbl_1_data_2C = fn_8006D9A4(0x7B0011, lbl_1_data_54, 0);
    fn_8006F1A8(lbl_1_data_2C, 0.0f, 0.0f, 0.0f);
    fn_8006E2B8(lbl_1_data_2C, 1, 0x40000001);
    lbl_1_data_2E = fn_8006D9A4(0x20005, lbl_1_data_5C, 0);
    fn_8006E2B8(lbl_1_data_2E, 1, 0x40000001);
    lbl_1_data_32 = fn_8006D9A4(0x20012, lbl_1_data_64, 0);
    fn_8006E2B8(lbl_1_data_32, 1, 0x40000001);
    lbl_1_data_30 = fn_8006D9A4(0x2000D, lbl_1_data_6C, 0);
    fn_8006E2B8(lbl_1_data_30, 1, 0x40000001);
    fn_8005D10C(&fn_1_8C0, &fn_1_904);
    for (i = 0; i < ARRAY_COUNT(lbl_1_data_0); i++) {
        temp_r30 = &lbl_1_data_0[i];
        if (temp_r30->unk24 != -1) {
            lbl_1_bss_8 = NULL;
            lbl_1_bss_10[i] = fn_8006D9A4(temp_r30->unk24, lbl_1_bss_8, 0);
            fn_8006F158(lbl_1_bss_10[i], temp_r30);
            fn_8006F220(lbl_1_bss_10[i], &temp_r30->unk0C);
            fn_8006F2E8(lbl_1_bss_10[i], &temp_r30->unk18);
            fn_8006F50C(lbl_1_bss_10[i], 1);
            if (lbl_1_bss_8 != NULL) {
                fn_8006E2B8(lbl_1_bss_10[i], 0, 0x40000001);
            }
        }
    }
    fn_8006F50C(lbl_1_bss_10[0], 0);
    lbl_1_bss_0->unk8 = fn_8006D9A4(0x7000A, NULL, 0);
    fn_8006F50C(lbl_1_bss_0->unk8, 0);
    fn_80073FF4(&fn_1_90C);
    fn_80073FFC(&fn_1_91C);
    fn_80074004(&fn_1_908);
    fn_80083EDC(lbl_1_data_2C);
    fn_800A4F6C(lbl_1_data_32);
    fn_80077AAC(lbl_1_data_2E);
    fn_8007A83C(lbl_1_data_30);
    HuWinMesMaxSizeGet(1, &spC, 0x2E003A);
    lbl_1_bss_E = HuWinCreate(-10000.0f, 390.0f, spC, sp10, 1);
    HuWinMesSet(lbl_1_bss_E, 0x2E003A);
    HuWinMesSpeedSet(lbl_1_bss_E, 0);
    HuWinPriSet(lbl_1_bss_E, 1);
    HuWinMesPalSet(lbl_1_bss_E, 7, 0, 0, 0);
}

void fn_1_6D8(void) {
    s32 i;
    for (i = 0; i < 1; i++) {
        if (lbl_1_bss_10[i] != 0) {
            fn_8006DB90(lbl_1_bss_10[i]);
            lbl_1_bss_10[i] = 0;
        }   
    }
    if (lbl_1_data_32 != -1) {
        fn_8006DB90(lbl_1_data_32);
        lbl_1_data_32 = -1;
    }
    if (lbl_1_data_2E != -1) {
        fn_8006DB90(lbl_1_data_2E);
        lbl_1_data_2E = -1;
    }
    if (lbl_1_data_30 != -1) {
        fn_8006DB90(lbl_1_data_30);
        lbl_1_data_30 = -1;
    }
    if (lbl_1_data_2C != -1) {
        fn_8006DB90(lbl_1_data_2C);
        lbl_1_data_2C = -1;
    }
    if (lbl_1_data_28 != -1) {
        fn_8006DB90(lbl_1_data_28);
        lbl_1_data_28 = -1;
    }
    if (lbl_1_data_2A != -1) {
        fn_8006DB90(lbl_1_data_2A);
        lbl_1_data_2A = -1;
    }
    fn_8006DB90(lbl_1_bss_0->unk8);
    fn_1_1DEC();
    HuWinKill(lbl_1_bss_E);
    fn_80077A3C();
}

void fn_1_8C0(void) {
    s32 temp = fn_8006DBD4(lbl_1_data_28);
    Hu3DModelLightInfoSet(temp, 1);
}

void fn_1_904(void) {
}

void fn_1_908(void) {
}

s32 fn_1_90C(void) {
    return 0;
}

void fn_1_914(void) {
}

void fn_1_918(void) {
}

void fn_1_91C(void) {
}

s32 fn_1_920(s32 arg0, f32 arg8, f32 arg9) {
    s32 var_r31;
    f32 var_f29;
    f32 var_f31;

    var_r31 = 0;
    var_f31 = fn_8006F128(arg0);
    arg8 = fmod(arg8, 360.0);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (arg8 < 0.0f) {
        arg8 += 360.0f;
    }
    if (var_f31 != arg8) {
        var_f29 = arg8 - var_f31;
        if (var_f29 < 0.0f) {
            var_f29 += 360.0f;
        }
        if (var_f29 < 180.0f) {
            if (var_f29 > arg9) {
                var_f31 = var_f31 + arg9;
            } else {
                var_f31 = arg8;
            }
        } else if ((360.0f - var_f29) > arg9) {
            var_f31 = var_f31 - arg9;
        } else {
            var_f31 = arg8;
        }
        if (var_f31 < 0.0f) {
            var_f31 += 360.0f;
        }
        if (var_f31 >= 360.0f) {
            var_f31 -= 360.0f;
        }
        fn_8006F0D4(arg0, var_f31);
    } else {
        var_r31 = 1;
    }
    return var_r31;
}

void fn_1_AEC(void) {
    lbl_1_bss_1C = 0;
    lbl_1_bss_1E = fn_8006D9A4(0x7B000F, &lbl_1_data_78, 0);
    fn_8006E2B8(lbl_1_bss_1E, 1, 0x40000001);
    fn_800B42BC(lbl_1_bss_1E);
    fn_8006F61C(lbl_1_bss_1E, 6);
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
    BoardMessCreate(var_r31, arg0, -1);
    BoardMessWait();
    BoardMessKill();
}

void fn_1_C10(s32 arg0) {
    HuPrcEnd();
}

void fn_1_C20(void) {
    Mtx sp20;
    Vec3f sp14;
    Vec3f sp8;
    
    while (1) {
        if (fn_8005B6A8() != 0) {
            fn_8006DB90(lbl_1_bss_1E);
            fn_800B42BC(-1);
            HuPrcEnd();
        }
        Hu3D2Dto3D(&lbl_1_data_80[lbl_1_bss_1C], 1, &sp14);
        fn_8006F158(lbl_1_bss_1E, &sp14);
        fn_8005D5C0(&sp8);
        PSMTXRotRad(sp20, 'y', 0.2617994f);
        fn_8006EFBC(lbl_1_bss_1E, sp20);
        fn_8006F270(lbl_1_bss_1E, sp8.x, 0.0f, 0.0f);
        fn_8006F338(lbl_1_bss_1E, 0.2f, 0.2f, 0.2f);
        HuPrcVSleep();        
    }
}

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
    fn_8007500C(0);
    fn_8006F50C(lbl_1_data_2C, 1);
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
    fn_800B4264(0, 0x50, 1);
}

void fn_1_FB8(void) {
    fn_1_1E3C(3, 0x122, 0x8C);
    fn_1_BA0(0x2E0010);
    fn_1_1FB0();
    fn_1_BA0(0x2E0011);
    fn_800B4264(-0x50, 0, 1);
}

void fn_1_1010(void) {
    fn_1_1E3C(4, 0x122, 0x8C);
    fn_1_BA0(0x2E0012);
    fn_1_1FB0();
    fn_800B4264(0, 0x50, 1);
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
    fn_800B4264(-0x50, 0, 1);
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
    fn_80082AAC(1);
}

void fn_1_1178(void) {
    fn_1_BA0(0x2E0018);
}

void fn_1_11A0(void) {
    s32 temp;
    
    fn_1_BA0(0x2E0019);
    temp = fn_800745F0(0, 1);
    fn_800B4274(temp, 0);
}

void fn_1_11EC(void) {
    s32 temp;
    
    fn_1_BA0(0x2E001A);
    temp = fn_800745F0(0, 1);
    fn_800B4274(temp, 0);
    fn_800B42B4(0);
}

void fn_1_1240(void) {
    fn_1_BA0(0x2E001B);
    fn_800B4264(0x50, 0, 1);
}

void fn_1_1278(void) {
    fn_1_BA0(0x2E001C);
}

void fn_1_12A0(void) {
    fn_1_BA0(0x2E001D);
    fn_80062B74(2, 1);
    fn_800B42B4(1);
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
