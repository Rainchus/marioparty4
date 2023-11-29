#include "common.h"
#include "REL/executor.h"

s16 HuWinCreate(float x, float y, s16 w, s16 h, s16 frame);

typedef struct unkw10Dll {
    char unk0[0x0C];
    Vec3f unk0C;
    Vec3f unk18;
    s32 unk24;
} unkw10Dll; //sizeof 0x28

typedef struct w10DllUnk01 {
    u8 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} w10DllUnk01; //sizeof ?

typedef struct w10DllUnk02 {
    char unk00[0x5C];
    w10DllUnk01* unk5C;
} w10DllUnk02; //sizeof ?

//this belongs to m456Dll
w10DllUnk02** fn_8002FAC0(Process*, s32);
void fn_8003FD10(s16, f32, f32);
extern s16 lbl_1_bss_20;
extern f32 lbl_1_rodata_5C;
extern f32 lbl_1_rodata_60;
s16 fn_8003F958(s32, s32, s32);
void fn_8003FBEC(s16);
void fn_8008853C(s32);
extern s32 lbl_801A52E8;
void fn_800B42B4(s32);
void fn_80082AAC(s32);
void fn_800B4264(s32, s32, s32);
void fn_1_1FB0(void);
void fn_1_1E3C(s32, s32, s32);
void fn_8007500C(s32);
void fn_1_BA0(s32);
void fn_8006F0D4(s32, f32);
f32 fn_8006F128(s32);
f64 fmod(f32, f64);
void fn_1_C20(void);
void fn_8006F61C(s16, s32);
void fn_800B42BC(s16);
void fn_80023828(s32, s32);
s32 fn_8006DBD4(s16);
void fn_8005B150(void*, void*);
void fn_1_6D8(void);
void fn_1_E0(void);
void fn_8006F2E8(s32, Vec3f*);
void HuWinMesSet(s16, s32);
void fn_1_1D68(void);
void fn_1_1DEC(void);
void fn_1_AEC(void);
void fn_80042848(s16);
void fn_80045BF4(s16, s32);
void fn_80045D7C(s16, s32, s32, s32, s32);
void fn_80045E84(s16, s32);
void fn_80046F04(s32, f32*, ...);
void fn_8005D10C(void*, void*);
s16 fn_8006D9A4(s32, void*, s32);
void fn_8006DB90(s16);
void fn_8006DDE8(s16, f32);
void fn_8006E2B8(s16, s32, s32);
void fn_8006E878(s16, f32);
void fn_8006F158(s16, void*);
void fn_8006F1A8(s16, f32, f32, f32);
s32 fn_8006F220(s16 arg0, Vec3f* arg1);
void fn_8006F50C(s16, s32);
void fn_80073FF4(void*);
void fn_80073FFC(void*);
void fn_80074004(void*);
s32 fn_800745F0(s32, s32);
void fn_800772EC(s32);
void fn_80077A3C(void);
void fn_80077AAC(s16);
void fn_8007A83C(s16);
void fn_80083EDC(s16);
void fn_800A4F6C(s16);
void fn_800B3FD8(void*);
void fn_800B4274(s32, s32);
void fn_1_1AAC(void);
void fn_1_8C0(void);
void fn_1_904(void);
void fn_1_908(void);
s32 fn_1_90C(void);
void fn_1_91C(void);
void Hu3D2Dto3D(Vec3f*, s32, Vec3f*);
void fn_8005D5C0(Vec3f*);
void fn_8006F338(s16, f32, f32, f32);
s32 fn_8005B6A8(void);
void fn_8006EFBC(s16, Mtx);
void fn_8006F270(s16, f32, f32, f32);
void fn_8003FB08(s16);
extern Vec3f lbl_1_data_80[];
extern f32 lbl_1_rodata_38;
extern f32 lbl_1_rodata_3C;
extern f32 lbl_1_rodata_40;
extern Process* lbl_1_bss_18;
extern s16 lbl_1_bss_1C;
extern s16 lbl_1_bss_1E;
extern s32 lbl_1_data_78; //no idea on the type of this
extern f64 lbl_1_rodata_28;
extern f32 lbl_1_rodata_30;
extern f32 lbl_1_rodata_34;
extern BoardStateSubStruct* lbl_1_bss_0;
extern s16 lbl_1_bss_10[12]; //could be incorrect size
extern void* lbl_1_bss_8; //unknown type
extern s16 lbl_1_bss_C;
extern s16 lbl_1_bss_E;
extern unkw10Dll lbl_1_data_0[1];
extern s16 lbl_1_bss_22[11];
extern s32 lbl_1_data_2A8[11];
extern s16 lbl_1_data_28;
extern s16 lbl_1_data_2A;
extern s16 lbl_1_data_2C;
extern s16 lbl_1_data_2E;
extern s16 lbl_1_data_30;
extern s16 lbl_1_data_32;
extern s32 lbl_1_data_54; //unknown type
extern s32 lbl_1_data_5C;  //unknown type
extern s32 lbl_1_data_64; //unknown type
extern s32 lbl_1_data_6C; //unknown type
extern f32 lbl_1_rodata_10;
extern f32 lbl_1_rodata_14;
extern f32 lbl_1_rodata_18;
extern f32 lbl_1_rodata_1C;
extern BoardState lbl_8018FCF8;

/*
void fn_1_0(void) {
    fn_8005B150(&fn_1_E0, &fn_1_6D8);
}
*/

// function is probably global. only inlined in rels?
/*
inline s32 get_current_board(void) {
    return lbl_8018FCF8.unk08 & 0x1F;
}
*/

/*
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
    fn_8006DDE8(lbl_1_data_28, lbl_1_rodata_10);
    fn_8006F1A8(lbl_1_data_28, lbl_1_rodata_14, lbl_1_rodata_14, lbl_1_rodata_14);
    fn_8006E2B8(lbl_1_data_28, 0, 0x40000001);
    fn_8006E878(lbl_1_data_28, lbl_1_rodata_18);
    lbl_1_data_2A = fn_8006D9A4(0x7B0002, NULL, 0);
    fn_8006DDE8(lbl_1_data_2A, lbl_1_rodata_10);
    fn_8006F1A8(lbl_1_data_2A, lbl_1_rodata_14, lbl_1_rodata_14, lbl_1_rodata_14);
    fn_8006E2B8(lbl_1_data_2A, 0, 0x40000001);
    lbl_1_data_2C = fn_8006D9A4(0x7B0011, &lbl_1_data_54, 0);
    fn_8006F1A8(lbl_1_data_2C, lbl_1_rodata_14, lbl_1_rodata_14, lbl_1_rodata_14);
    fn_8006E2B8(lbl_1_data_2C, 1, 0x40000001);
    lbl_1_data_2E = fn_8006D9A4(0x20005, &lbl_1_data_5C, 0);
    fn_8006E2B8(lbl_1_data_2E, 1, 0x40000001);
    lbl_1_data_32 = fn_8006D9A4(0x20012, &lbl_1_data_64, 0);
    fn_8006E2B8(lbl_1_data_32, 1, 0x40000001);
    lbl_1_data_30 = fn_8006D9A4(0x2000D, &lbl_1_data_6C, 0);
    fn_8006E2B8(lbl_1_data_30, 1, 0x40000001);
    fn_8005D10C(&fn_1_8C0, &fn_1_904);
    for (i = 0; i < 1; i++) {
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
    fn_80046F04(1, &spC, 0x2E003A);
    lbl_1_bss_E = HuWinCreate(lbl_1_rodata_1C, lbl_1_rodata_20, spC, sp10, 1);
    HuWinMesSet(lbl_1_bss_E, 0x2E003A);
    fn_80045E84(lbl_1_bss_E, 0);
    fn_80045BF4(lbl_1_bss_E, 1);
    fn_80045D7C(lbl_1_bss_E, 7, 0, 0, 0);
}
*/

/*
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
    fn_80042848(lbl_1_bss_E);
    fn_80077A3C();
}
*/

/*
void fn_1_8C0(void) {
    s32 temp = fn_8006DBD4(lbl_1_data_28);
    fn_80023828(temp, 1);
}
*/

/*
void fn_1_904(void) {
}
*/

/*
void fn_1_908(void) {
}
*/

/*
s32 fn_1_90C(void) {
    return 0;
}
*/

/*
void fn_1_914(void) {
}
*/

/*
void fn_1_918(void) {
}
*/

/*
void fn_1_91C(void) {
}
*/

/*
s32 fn_1_920(s32 arg0, f32 arg8, f32 arg9) {
    s32 var_r31;
    f32 var_f29;
    f32 var_f31;

    var_r31 = 0;
    var_f31 = fn_8006F128(arg0);
    arg8 = fmod(arg8, lbl_1_rodata_28);
    if (var_f31 < lbl_1_rodata_14) {
        var_f31 += lbl_1_rodata_30;
    }
    if (arg8 < lbl_1_rodata_14) {
        arg8 += lbl_1_rodata_30;
    }
    if (var_f31 != arg8) {
        var_f29 = arg8 - var_f31;
        if (var_f29 < lbl_1_rodata_14) {
            var_f29 += lbl_1_rodata_30;
        }
        if (var_f29 < lbl_1_rodata_34) {
            if (var_f29 > arg9) {
                var_f31 = var_f31 + arg9;
            } else {
                var_f31 = arg8;
            }
        } else if ((lbl_1_rodata_30 - var_f29) > arg9) {
            var_f31 = var_f31 - arg9;
        } else {
            var_f31 = arg8;
        }
        if (var_f31 < lbl_1_rodata_14) {
            var_f31 += lbl_1_rodata_30;
        }
        if (var_f31 >= lbl_1_rodata_30) {
            var_f31 -= lbl_1_rodata_30;
        }
        fn_8006F0D4(arg0, var_f31);
    } else {
        var_r31 = 1;
    }
    return var_r31;
}
*/

/*
void fn_1_AEC(void) {
    lbl_1_bss_1C = 0;
    lbl_1_bss_1E = fn_8006D9A4(0x7B000F, &lbl_1_data_78, 0);
    fn_8006E2B8(lbl_1_bss_1E, 1, 0x40000001);
    fn_800B42BC(lbl_1_bss_1E);
    fn_8006F61C(lbl_1_bss_1E, 6);
    lbl_1_bss_18 = HuPrcCreate(fn_1_C20, 0x1FFF, 0x1800, 0);
}
*/

/*
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
*/

/*
void fn_1_C10(void) {
    HuPrcEnd();
}
*/

/*
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
        PSMTXRotRad(sp20, 'y', lbl_1_rodata_38);
        fn_8006EFBC(lbl_1_bss_1E, sp20);
        fn_8006F270(lbl_1_bss_1E, sp8.x, lbl_1_rodata_3C, lbl_1_rodata_3C);
        fn_8006F338(lbl_1_bss_1E, lbl_1_rodata_40, lbl_1_rodata_40, lbl_1_rodata_40);
        HuPrcVSleep();        
    }
}
*/

/*
void fn_1_D2C(void) {
    fn_1_BA0(0x2E0001);
}
*/

/*
void fn_1_D54(void) {
    fn_1_BA0(0x2E0002);
}
*/

/*
void fn_1_D7C(void) {
    fn_1_BA0(0x2E0003);
}
*/

/*
void fn_1_DA4(void) {
    fn_1_BA0(0x2E0004);
}
*/

/*
void fn_1_DCC(void) {
    fn_1_BA0(0x2E0005);
}
*/

/*
void fn_1_DF4(void) {
    fn_1_BA0(0x2E0006);
}
*/

/*
void fn_1_E1C(void) {
    fn_1_BA0(0x2E0007);
}
*/

/*
void fn_1_E44(void) {
    fn_1_BA0(0x2E0008);
    fn_1_BA0(0x2E0009);
    fn_8007500C(0);
    fn_8006F50C(lbl_1_data_2C, 1);
}
*/

/*
void fn_1_E94(void) {
    fn_1_BA0(0x2E000A);
}
*/

/*
void fn_1_EBC(void) {
    fn_1_BA0(0x2E000B);
}
*/

/*
void fn_1_EE4(void) {

}
*/

/*
void fn_1_EE8(void) {
    fn_1_1E3C(0, 0x122, 0x8C);
    fn_1_BA0(0x2E000C);
    fn_1_BA0(0x2E000D);
    fn_1_1FB0();
}
*/

/*
void fn_1_F30(void) {
    fn_1_1E3C(1, 0x122, 0x8C);
    fn_1_BA0(0x2E000E);
    fn_1_1FB0();
}
*/

/*
void fn_1_F6C(void) {
    fn_1_1E3C(2, 0x122, 0x8C);
    fn_1_BA0(0x2E000F);
    fn_1_1FB0();
    fn_800B4264(0, 0x50, 1);
}
*/

/*
void fn_1_FB8(void) {
    fn_1_1E3C(3, 0x122, 0x8C);
    fn_1_BA0(0x2E0010);
    fn_1_1FB0();
    fn_1_BA0(0x2E0011);
    fn_800B4264(-0x50, 0, 1);
}
*/

/*
void fn_1_1010(void) {
    fn_1_1E3C(4, 0x122, 0x8C);
    fn_1_BA0(0x2E0012);
    fn_1_1FB0();
    fn_800B4264(0, 0x50, 1);
}
*/

/*
void fn_1_105C(void) {
    fn_1_1E3C(5, 0x122, 0x8C);
    fn_1_BA0(0x2E0013);
    fn_1_1FB0();
}
*/

/*
void fn_1_1098(void) {
    fn_1_BA0(0x2E0014);
}
*/

/*
void fn_1_10C0(void) {
    fn_1_BA0(0x2E0015);
    fn_800B4264(-0x50, 0, 1);
}
*/

/*
void fn_1_10F8(void) {
    fn_1_1E3C(6, 0x122, 0x8C);
    fn_1_BA0(0x2E0016);
    fn_1_1FB0();
}
*/

/*
void fn_1_1134(void) {
    fn_1_1E3C(7, 0x122, 0x8C);
    fn_1_BA0(0x2E0017);
    fn_1_1FB0();
    fn_80082AAC(1);
}
*/

/*
void fn_1_1178(void) {
    fn_1_BA0(0x2E0018);
}
*/

/*
void fn_1_11A0(void) {
    s32 temp;
    
    fn_1_BA0(0x2E0019);
    temp = fn_800745F0(0, 1);
    fn_800B4274(temp, 0);
}
*/

/*
void fn_1_11EC(void) {
    s32 temp;
    
    fn_1_BA0(0x2E001A);
    temp = fn_800745F0(0, 1);
    fn_800B4274(temp, 0);
    fn_800B42B4(0);
}
*/

/*
void fn_1_1240(void) {
    fn_1_BA0(0x2E001B);
    fn_800B4264(0x50, 0, 1);
}
*/

/*
void fn_1_1278(void) {
    fn_1_BA0(0x2E001C);
}
*/

/*
void fn_1_12A0(void) {
    fn_1_BA0(0x2E001D);
    fn_80062B74(2, 1);
    fn_800B42B4(1);
}
*/

/*
void fn_1_12DC(void) {
    fn_1_BA0(0x2E001E);
}
*/

/*
void fn_1_1304(void) {
    fn_1_BA0(0x2E001F);
}
*/

/*
void fn_1_132C(void) {
    fn_1_BA0(0x2E0020);
}
*/

/*
void fn_1_1354(void) {
    fn_1_BA0(0x2E0021);
}
*/

/*
void fn_1_137C(void) {
    fn_1_BA0(0x2E0022);
}
*/

// fn_1_13A4

/*
void fn_1_176C(void) {
    fn_1_C10(1);
    fn_1_BA0(0x2E0024);
}
*/

/*
void fn_1_179C(void) {
    fn_1_BA0(0x2E0025);
    gPlayerData[1].flags.unk0 = 2;
    gPlayerData[3].flags.unk0 = 2;
}
*/

/*
void fn_1_17F4(void) {
    fn_1_BA0(0x2E0026);
    gPlayerData[0].flags.unk0 = 2;
}
*/

/*
void fn_1_1834(void) {
    fn_1_BA0(0x2E0027);
    gPlayerData[0].flags.unk0 = 1;
    gPlayerData[1].flags.unk0 = 1;
    gPlayerData[2].flags.unk0 = 1;
    gPlayerData[3].flags.unk0 = 2;
}
*/

/*
void fn_1_18BC(void) {
    fn_1_BA0(0x2E0028);
    fn_1_BA0(0x2E0029);
    lbl_801A52E8 = 0;
    fn_8008853C(0);
}
*/

/*
void fn_1_1908(void) {
    fn_1_BA0(0x2E002D);
}
*/

/*
void fn_1_1930(void) {
    fn_1_BA0(0x2E002F);
}
*/

/*
void fn_1_1958(void) {
    fn_1_BA0(0x2E0031);
}
*/

/*
void fn_1_1980(void) {

}
*/

// fn_1_1984

// fn_1_1AAC

/*
void fn_1_1D68(void) {
    s32 temp_r4;
    s32 temp_r5;
    s32 i;

    for (i = 0; i < 11; i++) {
        lbl_1_bss_22[i] = fn_8003F958(lbl_1_data_2A8[i], 0, 0);
        fn_8003FBEC(lbl_1_bss_22[i]);
    }
}
*/

/*
void fn_1_1DEC(void) {
    s32 i;

    for (i = 0; i < 11; i++) {
        fn_8003FB08(lbl_1_bss_22[i]);
    }
}
*/

// fn_1_1E3C

/*
void fn_1_1FB0(void) {
    f32 var_f31;
    f32 var_f30;
    u32 i;

    var_f31 = lbl_1_rodata_60;
    var_f30 = lbl_1_rodata_60;
    for (i = 0; i < 15; i++) {
        var_f31 -= lbl_1_rodata_5C;
        var_f30 -= lbl_1_rodata_5C;
        fn_8003FD10(lbl_1_bss_20, var_f31, var_f30);
        HuPrcVSleep();        
    }
    fn_8003FBEC(lbl_1_bss_20);
}
*/