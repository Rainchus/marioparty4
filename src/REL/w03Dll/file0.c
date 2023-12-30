#include "common.h"
#include "dolphin.h"
#include "REL/executor.h"
#include "game/process.h"
#include "game/data.h"

void fn_8005B150(void*, void*);
void fn_1_740(void);
void fn_1_E0(void);
typedef void (*VoidFunc)(void);
extern const VoidFunc _ctors[];
extern const VoidFunc _dtors[];

typedef struct w03StructUnk0 {
/* 0x00 */ Vec unk_00;
/* 0x0C */ Vec unk_0C;
/* 0x18 */ Vec unk_18;
/* 0x24 */ s32 datanum;
} w03StructUnk0;

typedef struct w03State {
           s8 unk0;
           u8 unk1;
           u8 unk2;
           s8 unk3;
           u16 unk4;
           u16 unk6;
           s16 unk8;
} w03State;

//DATA
w03StructUnk0 lbl_1_data_0[] = {
{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAKE_DATA_NUM(0x0077, 0x0004)},
{{145.099f, 65.6173f, -2004.14f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAKE_DATA_NUM(0x0077, 0x0005)},
{{-2004.14f, -1148.76f, -1095.54f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAKE_DATA_NUM(0x0077, 0x0006)},
{{1050.0f, 50.0f, -1810.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAKE_DATA_NUM(0x0077, 0x000B)},
{{-1950.0f, 50.0f, 1790.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.914f, 1.0f}, MAKE_DATA_NUM(0x0077, 0x000B)},
{{1050.0f, 0.0f, -1750.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAKE_DATA_NUM(0x0077, 0x000A)},
{{-1950.0f, 0.0f, 1850.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.914f, 1.0f}, MAKE_DATA_NUM(0x0077, 0x000A)},
{{1950.0f, 0.0f, -1800.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAKE_DATA_NUM(0x0077, 0x0010)},
{{-3150.0f, 0.0f, -600.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAKE_DATA_NUM(0x0077, 0x0011)},
{{-3150.0f, 270.0f, -600.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAKE_DATA_NUM(0x0077, 0x0012)},
{{2080.0f, 0.0f, -1635.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAKE_DATA_NUM(0x0002, 0x000D)},
{{-3000.0f, 0.0f, -500.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAKE_DATA_NUM(0x0002, 0x000D)},
};

s16 lbl_1_data_1E0 = 1;
s16 lbl_1_data_1E2 = 1;
s16 lbl_1_data_1E4 = 1;
s16 lbl_1_data_1E6 = 1;
s16 lbl_1_data_1E8 = 1;

typedef struct w03StructUnk1 {
    f32 unk_00;
    f32 unk_04;
    f32 unk_08;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
} w03StructUnk1;

w03StructUnk1 lbl_1_data_1EC = {
	0.0f, 118.0f, 120.0f, 180.0f, 180.0f, 240.0f, 240.0f, 300.0f
};

s32 lbl_1_data_20C = {
    MAKE_DATA_NUM(0x0077, 0x001C),
	DATA_NUM_LISTEND
};

s32 lbl_1_data_214 = {
    MAKE_DATA_NUM(0x0002, 0x000E),
	DATA_NUM_LISTEND
};

s32 lbl_1_data_21C[] = {
    -1, -1, -1, -1
};

Vec lbl_1_data_22C[] = {
    {3900.0f, 0.0f, 2100.0f},
    {3900.0f, 0.0f, 3600.0f},
    {2700.0f, 0.0f, 5400.0f},
    {2700.0f, 0.0f, 6300.0f},
};

s32 lbl_1_data_25C[] = {
    0x0000044B, 0x00000439, 0x00000439, 0x0000044D
};

s32 lbl_1_data_26C[] = {
    0x0000044C, 0x0000043A, 0x0000043A, 0x0000044E
};

//BSS
w03State* lbl_1_bss_0;

void fn_1_CF4(void);

void fn_1_0(void) {
    fn_8005B150(&fn_1_E0, &fn_1_740);
}

int _prolog(void) {
    const VoidFunc* ctors = _ctors;
    while (*ctors != 0) {
        (**ctors)();
        ctors++;
    }
    fn_8005B150(&fn_1_E0, &fn_1_740);
    return 0;
}

void _epilog(void) {
    const VoidFunc* dtors = _dtors;
    while (*dtors != 0) {
        (**dtors)();
        dtors++;
    }
}

void fn_1_E0(void) {
    Vec* var_r29;
    f32 var_f30;
    f32 var_f31;
    s32 var_r31;
    s32 var_r31_2;
    w03StructUnk0* temp_r30;
    s32 i;

    lbl_1_bss_0 = (w03State*)&GWSystem.board_data;
    lbl_1_bss_0->unk3 = 0;
    fn_800772EC(0x770000);
    lbl_1_data_1E0 = fn_8006D9A4(0x770001, NULL, 0);
    fn_8006DDE8(lbl_1_data_1E0, -1.0f);
    fn_8006F1A8(lbl_1_data_1E0, 0.0f, 0.0f, 0.0f);
    fn_8006E2B8(lbl_1_data_1E0, 0, 0x40000001);
    lbl_1_data_1E8 = fn_8006D9A4(0x770003, NULL, 0);
    fn_8006DDE8(lbl_1_data_1E8, -1.0f);
    fn_8006F1A8(lbl_1_data_1E8, 0.0f, 0.0f, 0.0f);
    fn_8006F61C(lbl_1_data_1E8, 2);
    lbl_1_data_1E2 = fn_8006D9A4(0x770002, NULL, 0);
    fn_8006DDE8(lbl_1_data_1E2, -1.0f);
    fn_8006F1A8(lbl_1_data_1E2, 0.0f, 0.0f, 0.0f);
    fn_8006E2B8(lbl_1_data_1E2, 0, 0x40000001);
    lbl_1_data_1E4 = fn_8006D9A4(0x77001B, &lbl_1_data_20C, 0);
    fn_8006F1A8(lbl_1_data_1E4, 0.0f, 0.0f, 0.0f);
    fn_8006E2B8(lbl_1_data_1E4, 1, 0x40000001);
    lbl_1_data_1E6 = fn_8006D9A4(0x2000D, &lbl_1_data_214, 0);
    fn_8006F1A8(lbl_1_data_1E6, 0.0f, 0.0f, 0.0f);
    fn_8006E2B8(lbl_1_data_1E6, 1, 0x40000001);

    for (i = 0; i < 0xC; i++) {
        temp_r30 = &lbl_1_data_0[i];
        if (temp_r30->datanum != -1) {
            if ((i == 10) || (i == 11)) {
                var_r29 = &lbl_1_data_214;
            } else {
                var_r29 = NULL;
            }
            lbl_1_bss_C[i]= fn_8006D9A4(temp_r30->datanum, var_r29, 0);
            fn_8006F158(lbl_1_bss_C[i], temp_r30);
            fn_8006F220(lbl_1_bss_C[i], &temp_r30->unk_0C);
            fn_8006F2E8(lbl_1_bss_C[i], &temp_r30->unk_18);
            fn_8006F50C(lbl_1_bss_C[i], 1);
        }
    }
    fn_8006E2B8(lbl_1_bss_C[10], 1, 0x40000001);
    fn_8006E2B8(lbl_1_bss_C[11], 1, 0x40000001);
    fn_8006E2B8(lbl_1_bss_C[7], 0, 0x40000002);
    fn_8006E2B8(lbl_1_bss_C[9], 0, 0x40000002);
    fn_8006E2B8(lbl_1_bss_C[1], 0, 0x40000002);
    fn_1_3058();
    fn_1_6494();
    fn_1_7ABC();
    fn_1_9A7C();
    fn_8005D10C(&fn_1_884, &fn_1_8F0);
    fn_80073FF4(&fn_1_910);
    fn_80073FFC(&fn_1_A74);
    fn_80074004(&fn_1_AF8);
    fn_80083EDC(lbl_1_data_1E4);
    fn_800A4F6C(lbl_1_data_1E6);
    fn_8007A83C(lbl_1_data_1E6);
    fn_80077AAC(lbl_1_data_1E6);
    fn_80064D84(0x0000C000);
    fn_80064D84(0x3000);
    fn_1_CF4();
    fn_8006E2B8(lbl_1_bss_C[0], 0, 0x40000001);
    if (lbl_1_bss_0->unk0 != 0) {
        var_f30 = lbl_1_data_1EC.unk_10;
        var_f31 = lbl_1_data_1EC.unk_14;
        fn_1_63F4(0);
    } else {
        var_f30 = lbl_1_data_1EC.unk_00;
        var_f31 = lbl_1_data_1EC.unk_04;
        fn_1_63F4(1);
    }
    fn_8006E0B0(lbl_1_bss_C[0], var_f30, var_f31);
    fn_8006E2B8(lbl_1_bss_C[2], 0, 0x40000001);
    fn_8006E0B0(lbl_1_bss_C[2], 1, 0x64);
    fn_1_785C();
    if (lbl_1_bss_0->unk2 != 0) {
        for (i = 0; i < 4; i++) {
            if ((lbl_1_bss_0->unk2 & (1 << i)) != 0) {
                fn_80064338(i, &fn_1_2930);
                break;
            }
        }
    }
    fn_1_DEC();
}

void fn_1_740(void) {
    s32 i;

    fn_1_10B0();
    fn_1_9A9C();
    fn_1_7B58();
    for (i = 0; i < 0x0C; i++) {
        fn_8006DB90(lbl_1_bss_C[i]);
        lbl_1_bss_C[i] = -1;        
    }
    if (lbl_1_data_1E6 != -1) {
        fn_8006DB90(lbl_1_data_1E6);
        lbl_1_data_1E6 = -1;
    }
    if (lbl_1_data_1E4 != -1) {
        fn_8006DB90(lbl_1_data_1E4);
        lbl_1_data_1E4 = -1;
    }
    if (lbl_1_data_1E0 != -1) {
        fn_8006DB90(lbl_1_data_1E0);
        lbl_1_data_1E0 = -1;
    }
    if (lbl_1_data_1E2 != -1) {
        fn_8006DB90(lbl_1_data_1E2);
        lbl_1_data_1E2 = -1;
    }
}

extern f32 lbl_1_rodata_18;
extern f32 lbl_1_rodata_1C;

void fn_1_884(void) {
    s32 var = fn_8006DBD4(lbl_1_data_1E0);
    Hu3DModelLightInfoSet(var, 1);
    Hu3DFogSet(lbl_1_rodata_18, lbl_1_rodata_1C, 0xE4U, 0xF0U, 0xFFU);
}

void fn_1_8F0(void) {
    Hu3DFogClear();
}

s32 fn_1_910(void) {
    u32 temp_r3;
    s32 cur_player_index;
    s32 unkC;

    cur_player_index = GWSystem.player_curr;
    unkC = GWPlayer[cur_player_index].unkC;
    temp_r3 = fn_80074138(0, unkC);
    if (temp_r3 & 0xC000) {
        if ((fn_8006413C(cur_player_index) == 2) || ((u8) (( GWPlayer[cur_player_index].placement >> 4U) & 1))) {
            return 0;
        }
        if (temp_r3 & 0x4000) {
            if (lbl_1_bss_0->unk1 == 0) {
                return 0;
            }
        }
        else if (temp_r3 & 0x8000 && lbl_1_bss_0->unk1 != 0) {
            return 0;
        }
        
        return fn_1_309C();
    }
    if (temp_r3 & 0x200) {
        if ((fn_8006413C(cur_player_index) == 2) || ((u8) ((GWPlayer[cur_player_index].placement >> 4U) & 1) != 0)) {
            return 0;
        }
        return fn_1_675C();
    }
    return 0;
}

void fn_1_A74(void) {
    s16 temp = GWPlayer[GWSystem.player_curr].unkC;
    u32 var = fn_80074138(0, temp) & 0x600000;
    if (var + -0x200000 == 0) {
        fn_1_7BA8();
        return;
    }
    if (var + -0x400000 == 0) {
        fn_1_9AA0();
    }
}

void fn_1_AF8(void) {
    if ((fn_8006413C(GWSystem.player_curr) == 0) && (fn_1_12C8() != 0) && (lbl_1_bss_0->unk2 != 0)) {
        fn_80064D84(0xC00);
    }
}
void fn_1_B5C(s32 arg0) {
    f32 var_f31;
    f32 var_f30;
    f32 var_f29;
    f32 var_f28;
    f32 temp;

    if (arg0 != 0) {
        var_f30 = lbl_1_data_1EC.unk_08;
        var_f29 = lbl_1_data_1EC.unk_0C;
        var_f31 = lbl_1_data_1EC.unk_10;
        var_f28 = lbl_1_data_1EC.unk_14;
        fn_1_63F4(0);
    } else {
        var_f30 = lbl_1_data_1EC.unk_18;
        var_f29 = lbl_1_data_1EC.unk_1C;
        var_f31 = lbl_1_data_1EC.unk_00;
        var_f28 = lbl_1_data_1EC.unk_04;
        fn_1_63F4(1);
    }
    fn_8006E2B8(lbl_1_bss_C[0], 0, 0);
    fn_8006E674(lbl_1_bss_C[0], var_f30);
    while (1) {
        temp = fn_8006E6F8(lbl_1_bss_C[0]);
        if (temp >= var_f29) {
            break;
        }
        HuPrcVSleep();
    }
    fn_8006E5C4(lbl_1_bss_C[0], 0x40000001);
    fn_8006E674(lbl_1_bss_C[0], var_f31);
    fn_8006E0B0(lbl_1_bss_C[0], (s32) var_f31, (s32) var_f28);
}

void fn_1_CF4(void) {
    s16 var;
    s32 i, j;
    spaceData* temp_r28;
    spaceData* temp_r31;

    for (i = 0; i < fn_800740B4(0); i++) {
        var = i + 1;
        temp_r31 = fn_800740C4(0, var);
        for (j = 0; j < temp_r31->num_links; j++) {
            if (fn_80074138(0, temp_r31->links[j]) & 0xC00) {
                temp_r28 = fn_800740C4(0, temp_r31->links[j]);
                if (lbl_1_bss_0->unk0 != 0) {
                    temp_r28->flag |= 0x04000000;
                    fn_80064D84(0xC00);
                } else {
                    temp_r28->flag &= ~0x04000000;
                    fn_80064D94(0xC00);
                }
            }            
        }
    }
}

void fn_1_DEC(void) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    omObjData* temp_r3;
    s32 var_r31;
    s32 var_r31_2;
    w03UnkStruct2* temp_r29;
    s32 i;

    temp_r3 = omAddObjEx(lbl_801D3ED4, 0x101, 0, 0, -1, &fn_1_10E4);
    lbl_1_bss_4 = temp_r3;
    temp_r29 = (w03UnkStruct2*)&temp_r3->work[0];
    temp_r29->unk0 = 0;
    lbl_1_bss_8 = 0;
    fn_8005D530(&sp20);
    fn_8005D628(&sp14);
    HuAudFXListnerSetEX(&sp20, &sp14, 1200.0f, 4800.0f, 36000.0f, 0.0f, 1200.0f);
    for (i = 0; i < 4; i++) {
        sp8.x = lbl_1_data_22C[i].x - 3600.0f;
        sp8.y = lbl_1_data_22C[i].y;
        sp8.z = lbl_1_data_22C[i].z - 3600.0f;
        if (lbl_1_bss_0->unk2 != 0) {
            lbl_1_data_21C[i] = HuAudFXEmiterPlay(lbl_1_data_26C[i], &sp8);
        } else {
            lbl_1_data_21C[i] = HuAudFXEmiterPlay(lbl_1_data_25C[i], &sp8);
        }
    }

    for (i = 0; i < 4; i++) {
        if ((WipeStatGet() != 0) || (_CheckFlag(0x1001CU) != 0)) {
            HuAudFXVolSet(lbl_1_data_21C[i], 0);
        } else {
            HuAudFXVolSet(lbl_1_data_21C[i], 0x7F);
        }        
    }

    if (_CheckFlag(0x10010) == 0) {
        if (lbl_1_bss_8 == 0) {
            HuAudFXPauseAll(1);
            lbl_1_bss_8 = 1;
        }
    } else if (lbl_1_bss_8 != 0) {
        HuAudFXPauseAll(0);
        lbl_1_bss_8 = 0;
    }
}

void fn_1_10B0(void) {
    if (lbl_1_bss_4) {
        ((w03UnkStruct2*)&lbl_1_bss_4->work[0])->unk0 = 1;
    }
}

void fn_1_10E4(omObjData* arg0) {
    Vec sp14;
    Vec sp8;
    s32 i;
    w03UnkStruct2* temp_r29;

    temp_r29 = (w03UnkStruct2*)&arg0->work[0];
    if (temp_r29->unk0 != 0 || (fn_8005B6A8() != 0)) {
        for (i = 0; i < 4; i++) {
            if (lbl_1_data_21C[i] != -1) {
                HuAudFXFadeOut(lbl_1_data_21C[i], 100);
            }            
        }
        HuAudFXListnerKill();
        lbl_1_bss_4 = 0;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    fn_8005D628(&sp8);
    fn_8005D578(&sp14);

    for (i = 0; i < 4; i++) {
        if ((WipeStatGet() != 0) || (_CheckFlag(0x1001C) != 0)) {
            HuAudFXVolSet(lbl_1_data_21C[i], 0);
        } else {
            HuAudFXVolSet(lbl_1_data_21C[i], 0x7F);
        }
    }

    sp14.y += 2000.0f;
    if (_CheckFlag(0x10010) == 0) {
        if (lbl_1_bss_8 == 0) {
            HuAudFXPauseAll(1);
            lbl_1_bss_8 = 1;
        }
    } else if (lbl_1_bss_8 != 0) {
        HuAudFXPauseAll(0);
        lbl_1_bss_8 = 0;
    }
    HuAudFXListnerUpdate(&sp14, &sp8);
}