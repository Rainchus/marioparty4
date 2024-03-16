#include "REL/w03Dll.h"
#include "game/data.h"


//file is full of old names and old signatures...needs updating
//is also missing half the functions in this TU

void fn_1_313C(void);
void fn_1_3218(void);
void fn_1_3304(void);
extern Process* lbl_1_bss_70;
extern s8 lbl_1_bss_7C;
extern s16 lbl_1_data_310;

// #define MAKE_DATA_NUM(dir, file) (((dir) << 16)+(file))
// #define MAKE_DIR_NUM(dir) ((dir) << 16)

// #define DATA_NUM_LISTEND -1

s32 lbl_1_data_318[] = {
    DATA_MAKE_NUM(0x0077, 0x0016),
    DATA_MAKE_NUM(0x0077, 0x0017),
    DATA_MAKE_NUM(0x0077, 0x0018),
    DATA_MAKE_NUM(0x0077, 0x0019),
    DATA_MAKE_NUM(0x0077, 0x001A),
    DATA_NUM_LISTEND
};

void fn_1_3058(void) {
    lbl_1_data_310 = fn_8006D9A4(0x770015, &lbl_1_data_318, 0);
    fn_1_3304();
}

s32 fn_1_309C(void) {
    fn_800688E8(0);
    lbl_1_bss_70 = HuPrcChildCreate(fn_1_313C, 0x2003U, 0x2000U, 0, lbl_801D3ED0);
    HuPrcDestructorSet2(lbl_1_bss_70, fn_1_3218);

    while (lbl_1_bss_70) {
        HuPrcVSleep();
    }
    
    fn_800688E8(1);
    return lbl_1_bss_7C;
}

s32 fn_800747C4(s32, s32, s32);                         /* extern */
extern s16 lbl_1_data_310;
extern f64 lbl_1_rodata_100;
extern f32 lbl_1_rodata_108;
extern f32 lbl_1_rodata_E8;
extern f64 lbl_1_rodata_F0;
extern f64 lbl_1_rodata_F8;

void fn_1_3304(void) {
    Point3d sp8;
    f32 temp_f31;
    s32 var_r31;
    

    if (lbl_1_bss_0->unk1 != 0) {
        var_r31 = fn_800745F0(0, 0x4000);
    } else {
        var_r31 = fn_800745F0(0, 0x8000);
    }
    var_r31 = fn_800747C4(0, var_r31, 0x02000000);
    fn_80074210(0, var_r31, &sp8);
    temp_f31 = lbl_1_rodata_E8;
    sp8.x = sp8.x + (lbl_1_rodata_F0 * sin((lbl_1_rodata_F8 * temp_f31) / lbl_1_rodata_100));
    sp8.z = sp8.z + (lbl_1_rodata_F0 * cos((lbl_1_rodata_F8 * temp_f31) / lbl_1_rodata_100));
    sp8.y = 45.0f + sp8.y;
    fn_8006F158(lbl_1_data_310, &sp8);
    fn_8006E2B8(lbl_1_data_310, 2, 0x40000001);
}

s32 fn_1_3478(s32);
void fn_1_3814(s32);
void fn_1_3968(s32);
void fn_1_3E88(s32);
void fn_1_3F5C(s32);
void fn_8005DAC4(f32, f32);
extern s8 lbl_1_bss_7C;
extern f32 lbl_1_rodata_D8;
extern f32 lbl_1_rodata_DC;
extern f32 lbl_1_rodata_E0;
extern f32 lbl_1_rodata_E4;

void fn_1_313C(void) {
    s32 temp_r31;

    temp_r31 = GWSystem.player_curr;
    lbl_1_bss_7C = 0;
    lbl_1_bss_0->unk3 = 1;
    if (fn_1_3478(temp_r31) != 0) {
        fn_8005DAC4(lbl_1_rodata_D8, lbl_1_rodata_DC);
        fn_800884F4(0);
        fn_1_3968(temp_r31);
        fn_1_3E88(temp_r31);
        fn_1_3F5C(temp_r31);
        lbl_1_bss_7C = 1;
    }
    fn_8005DAC4(lbl_1_rodata_E0, lbl_1_rodata_E4);
    fn_1_3814(temp_r31);
    HuPrcEnd();
}

extern s32 lbl_1_bss_70;
extern s16 lbl_1_data_312;
extern s16 lbl_1_data_314;
extern s16 lbl_1_data_316;

void fn_1_3218(void) {
    if (lbl_1_data_316 != -1) {
        HuWinKill(lbl_1_data_316);
        lbl_1_data_316 = -1;
    }
    if (lbl_1_data_314 != -1) {
        fn_8006DB90(lbl_1_data_314);
        lbl_1_data_314 = -1;
    }
    if (lbl_1_data_312 != -1) {
        fn_800637CC(GWSystem.player_curr, lbl_1_data_312);
        lbl_1_data_312 = -1;
    }
    lbl_1_bss_0->unk3 = 0;
    lbl_1_bss_70 = 0;
}

s32 BoardWinChoiceGet(void);
void fn_1_4354(s32);
s32 fn_80061FDC(s32);
s32 fn_80063EC0(s32);
void fn_80063EEC(s32, s32);
void fn_8006E47C(s16, s32, f32, f32, s32);
s32 fn_8006E91C(s16);
void fn_80070390(s32, s32, s32, s32);
void fn_80070770(s32);
void fn_80072DA8(s32);
s32 fn_800747C4(s32, s16, s32);
extern s16 lbl_1_data_310;
extern f64 lbl_1_rodata_100;
extern f32 lbl_1_rodata_10C;
extern f32 lbl_1_rodata_110;
extern f32 lbl_1_rodata_114;
extern f32 lbl_1_rodata_118;
extern f32 lbl_1_rodata_11C;
extern f32 lbl_1_rodata_E8;
extern f64 lbl_1_rodata_F8;

s32 fn_1_3478(s32 arg0) {
    Point3d sp38;
    Point3d sp2C;
    Point3d sp20;
    f32 sp1C;
    f32 sp18;
    Point3d sp14;
    Point3d sp8;

    s16 temp_r28;
    s32 temp_r3;
    s32 var_r29;
    s32 var_r30;
    s32 temp;
    s32 temp_r26;
    f32 float_temp;
    s32 i, j;

    sp14.x = 0.0f;
    sp14.y = 150.0f;
    sp14.z = 0.0f;

    sp8.x = -15.0f;
    sp8.y = 0.0f;
    sp8.z = 0.0f;

    fn_8005DB6C(lbl_1_data_310, &sp8, &sp14, lbl_1_rodata_114, lbl_1_rodata_118, 0x15);
    temp_r28 = GWPlayer[arg0].space_curr;
    fn_8006310C(arg0, &sp2C);
    temp = fn_800747C4(0, temp_r28, 0x02000000);
    fn_80074210(0, temp, &sp38);
    PSVECSubtract(&sp38, &sp2C, &sp20);
    float_temp = atan2(sp20.x, sp20.z) / 3.141592653589793f * 180.0f;
    fn_80067C90(arg0, (float_temp), 0xF);
    
    while (fn_8006874C(arg0) == 0) {
        HuPrcVSleep();
    }
    
    fn_80067B98(arg0);
    HuAudFXPlay(0x447);
    fn_8006E47C(lbl_1_data_310, 4, 0.0f, 5.0f, 0);
    HuPrcSleep(6);
    
    while (fn_8006E91C(lbl_1_data_310) == 0) {
        HuPrcVSleep();
    }
    
    fn_8006E47C(lbl_1_data_310, 1, 0.0f, 5.0f, 0x40000001);
    temp_r26 = fn_80061FDC(arg0);
    BoardWinCreate(2, 0x160010, 8);
    fn_800706D0(temp_r26, 3);
    BoardWinWait();
    if (fn_80063EC0(arg0) < 5) {
        BoardWinCreate(2, 0x160013, 8);
        BoardWinWait();
        BoardWinKill();
        return 0;
    }
    var_r29 = 0;
    goto test;
    while (1) {
        fn_80070390(2, 0x160011, 8, 0);
        fn_80070770(0x10);
        
        if (GWPlayer[arg0].com != 0) {
            fn_1_4354(arg0);
        }
        
        BoardWinWait();
        BoardWinKill();
        switch (BoardWinChoiceGet()) {
        case 0:
            var_r29 = 1;
            break;
        case 2:
            fn_80072DA8(arg0);
            break;
        default:
        case 1:
            BoardWinCreate(2, 0x160014, 8);
            BoardWinWait();
            BoardWinKill();
            return 0;
        }
        test:
        if (var_r29 != 0) {
            fn_80071034(0, 1, 1000);
            for (j = 0; j < 5; j++) {
                fn_80063EEC(arg0, -1);
                HuAudFXPlay(14);
                HuPrcSleep(6);            
            }
            HuAudFXPlay(15);
            BoardWinKill();
            return 1;
        }
    }
}

extern s8 lbl_1_bss_7C;
extern f32 lbl_1_rodata_120;
extern f32 lbl_1_rodata_124;

void fn_1_3814(s32 arg0) {
    Point3d sp14;
    Point3d sp8;
    f32 temp;

    fn_8006E47C(lbl_1_data_310, 2, 0.0f, 10.0f, 0x40000001);
    temp = (180.0f + fn_80063448(arg0));
    fn_80067C90(arg0, temp, 0xF);
    
    while (fn_8006874C(arg0) == 0) {
        HuPrcVSleep();
    }
    
    fn_8005D284(1);
    fn_8005D834(arg0);
    if (lbl_1_bss_7C != 0) {
        fn_80074210(0, GWPlayer[arg0].space_curr, &sp14);
        fn_8006310C(arg0, &sp8);
        fn_80066F44(arg0, &sp8, &sp14, 0x14);
        while (GWPlayer[arg0].moving) {
            HuPrcVSleep();
        }
    }
    fn_80067B98(arg0);
    fn_8005E0C0();
}

void fn_1_3968(s32 arg0) {
    s32 var_r29 = 0;
    s32 var_r28 = 0;
    s32 sp48[] = {0x005F0065, 0x001A0065, 0x006D0065, 0x008A0065, 0x00850065, 0x00110065, 0x000D0065, 0x00810065};
    Point3d sp3C;
    Point3d sp30;
    Point3d sp24;
    Point3d sp18;
    s32 sp10[2] = {0x00770013, 0x00770014};
    f32 spC;
    s16 sp8;
    
    f32 temp_f30;
    f32 temp_f28;
    f32 temp_f31;
    f32 temp_f27;

    s16 character;

    lbl_1_data_314 = fn_8006D9A4(sp10[lbl_1_bss_0->unk1], NULL, 0);
    character = GWPlayer[arg0].character;
    lbl_1_data_312 = fn_8006374C(arg0, sp48[character]);
    
    Hu3DModelObjPosGet(fn_8006DBD4(lbl_1_data_310), "itemhook_oya", &sp3C);
    fn_8006310C(arg0, &sp30);
    temp_f30 = fn_8005FBE8(&sp3C, &sp30);
    PSVECSubtract(&sp3C, &sp30, &sp24);
    PSVECNormalize(&sp24, &sp24);
    PSVECScale(&sp24, &sp24, temp_f30 / lbl_1_rodata_108);
    fn_80063A1C(arg0, 4, 0.0f, lbl_1_rodata_11C, 0);
    HuPrcSleep(5);
    
    spC = fn_80063448(arg0);
    temp_f27 = 180.0f + spC;
    var_r29 = 0;
    sp8 = 0;
    temp_f28 = 40.0f;
    
    while (1) {
        temp_f31 = __OSs16tof32(&sp8);
        sp24.y = temp_f28 + (lbl_1_rodata_154 * (lbl_1_rodata_158 * (temp_f31 * temp_f31)));
        PSVECAdd(&sp30, &sp24, &sp30);
        temp_f30 = fn_8005FBE8(&sp3C, &sp30);
        if (temp_f30 < lbl_1_rodata_11C) {
            sp24.x = sp24.z = 0.0f;
            sp30.x = sp3C.x;
            sp30.z = sp3C.z;
        }
        
        if (var_r29 == 0) {
            if (sp3C.y < sp30.y) {
                var_r29 = 1;
            }
        } else {
            fn_8005FF28(&spC, temp_f27, lbl_1_rodata_15C);
            fn_80063374(arg0, spC);
        }
        
        if (sp30.y <= sp3C.y && var_r29 != 0) {
            sp30.y = sp3C.y;
            break;
        }
        fn_80062FA4(arg0, &sp30);
        HuPrcVSleep();
        sp8 += 1;        
    }
    
    fn_80070DEC(1, 0x18, 0x7F, 0);
    fn_80063040(arg0, 0.0f, 0.0f, 0.0f);
    
    
    fn_8006F73C(lbl_1_data_310, "itemhook_oya",  GetCurrentPlayerIndex(GetCurrentPlayer(arg0)));
    fn_8006394C(arg0, lbl_1_data_312, 0x40000001);
    HuAudFXPlay(0x44F);
    fn_8006E47C(lbl_1_data_310, 5, 0.0f, lbl_1_rodata_11C, 0);
    
    sp18.x = -15.0f;
    sp18.y = 180.0f;
    sp18.z = 0.0f;
    
    fn_8005DB6C(lbl_1_data_310, &sp18, 0, lbl_1_rodata_160, lbl_1_rodata_118, 0x150);
    
    for (var_r28 = 0, sp8 = 0; ; sp8++) {
        if (var_r28 == 0) {
            if (sp8 == 0x78U) {
                WipeColorSet(0, 0, 0);
                WipeCreate(2, 0, -1);
                var_r28 = 1;
            }
        } else if (WipeStatGet() == 0) {
            break;
        }
        HuPrcVSleep();
    }
}


void fn_8005D7B4(s32);                                   /* extern */
void fn_80062FA4(s32, Point3d*);                       /* extern */
void fn_8006F800(s16);                                 /* extern */
extern f32 lbl_1_rodata_108;
extern f32 lbl_1_rodata_124;
extern f64 lbl_1_rodata_F0;

void fn_1_48EC(s32);                                   /* extern */
void fn_1_4A9C(void);                                      /* extern */
void fn_1_5838(s32);                                   /* extern */
s32 fn_1_62D0(void);                                    /* extern */
void fn_80088638(s32);                                 /* extern */
void fn_80088790(s32, s32);                              /* extern */
extern s8 lbl_1_bss_7D;


void fn_1_3E88(s32 arg0) {
    lbl_1_bss_7D = 0;
    fn_1_48EC(arg0);
    fn_1_5838(arg0);
    lbl_1_bss_7D = 1;
    fn_80088638(arg0);
    fn_80088790(arg0, 1);
    WipeCreate(1, 0, 0x15);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    while (fn_1_62D0() != 3) {
        HuPrcVSleep();
    }
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    fn_1_4A9C();
    fn_80071034(0, 0, 0x3E8);
}

void fn_1_3F5C(s32 arg0) {
    Mtx sp38;
    Point3d sp2C;
    Point3d sp20;
    Point3d sp14;
    Point3d sp8;
    f32 temp_f31;
    s16 temp_r28;
    s32 var_r31;
    s16 var_r30;

    if (lbl_1_bss_0->unk1 != 0) {
        lbl_1_bss_0->unk1 = 0;
        var_r30 = fn_800745F0(0, 0x8000);
    } else {
        lbl_1_bss_0->unk1 = 1;
        var_r30 = fn_800745F0(0, 0x4000);
    }
    temp_r28 = fn_800747C4(0, var_r30, 0x02000000);
    fn_8005D7B4(0);
    fn_8006F800(lbl_1_data_310);
    if (lbl_1_bss_0->unk1 != 0) {
        var_r31 = fn_800745F0(0, 0x4000);
    } else {
        var_r31 = fn_800745F0(0, 0x8000);
    }
    var_r31 = fn_800747C4(0, var_r31, 0x02000000);
    fn_80074210(0, var_r31, &sp8);
    temp_f31 = 0.0f;
    sp8.x = (sp8.x + (lbl_1_rodata_F0 * sin((lbl_1_rodata_F8 * temp_f31) / 180.0f)));
    sp8.z = (sp8.z + (lbl_1_rodata_F0 * cos((lbl_1_rodata_F8 * temp_f31) / 180.0f)));
    sp8.y = 45.0f + sp8.y;
    fn_8006F158(lbl_1_data_310, &sp8);
    fn_8006E2B8(lbl_1_data_310, 2, 0x40000001);
    fn_8006E2B8(lbl_1_data_310, 1, 0x40000001);
    fn_8006F0D4(lbl_1_data_310, 0.0f);
    PSMTXIdentity(sp38);
    fn_8006EFBC(lbl_1_data_310, sp38);
    sp20.x = 0.0f;
    sp20.y = 150.0f;
    sp20.z = 0.0f;
    sp14.x = -15.0f;
    sp14.y = 0.0f;
    sp14.z = 0.0f;
    fn_8005DB6C(lbl_1_data_310, &sp14, &sp20, lbl_1_rodata_114, lbl_1_rodata_118, 1);
    fn_80074210(0, temp_r28, &sp2C);
    fn_80062FA4(arg0, &sp2C);
    GWPlayer[arg0].space_curr = var_r30;
    fn_80063374(arg0, lbl_1_rodata_124);
    fn_80067B98(arg0);
    HuPrcSleep(2);
    fn_8005D7B4(1);
    fn_8006E2B8(lbl_1_bss_C[2], 0, 0x40000001);
    fn_8006E0B0(lbl_1_bss_C[2], 1, 0x64);
    fn_8008853C(0);
    HuPrcSleep(2);
    fn_8008853C(1);
    WipeCreate(1, 0, 0x15);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    BoardWinCreate(2, 0x16000F, 8);
    BoardWinWait();
    BoardWinKill();
}

void fn_800712C8(void);                                    /* extern */
void fn_80071328(void);                                    /* extern */

void fn_1_4354(s32 arg0) {
    s32 sp8;
    s32 starPos;
    s32 var_r30;

    var_r30 = 0;
    starPos = GWSystem.star_pos;
    
    if (lbl_1_bss_0->unk1 != 0) {
        if ((starPos == 1) || (starPos == 2) || (starPos == 3) || (starPos == 4)) {
            var_r30 = 1;
        }
    } else if ((starPos == 0) || (starPos == 5) || (starPos == 6) || (starPos == 7)) {
        var_r30 = 1;
    }
    if (fn_80063EC0(arg0) < 0x14) {
        var_r30 = 1;
    }
    if (var_r30 != 0) {
        fn_800712C8();
        return;
    }
    fn_80071328();
}