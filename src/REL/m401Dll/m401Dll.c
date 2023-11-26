#include "m401Dll.h"

void fn_2_A0(void) {
    s32 i;
    unkStructBSS114 *temp_r30;
    unkStruct18BFC0 *temp_r29;
    s16* temp_r28;
 
    OSReport("**** M401ObjectSetup ****\n");
    HuMemHeapDump(HuMemHeapPtrGet(0), -1);
    HuMemHeapDump(HuMemHeapPtrGet(2), -1);
    HuMemHeapDump(HuMemHeapPtrGet(3), -1);
    lbl_2_bss_1C = omInitObjMan(0x3C, 0x2000);
    fn_80057E80(lbl_2_bss_1C);
    lbl_2_bss_A8 = fn_80022ADC(&lbl_2_data_14, &lbl_2_data_20, &lbl_2_data_2C);
    fn_80022EB4(lbl_2_bss_A8);
    temp_r28 = &lbl_8018C8FC[lbl_2_bss_A8].unk_00;
    *temp_r28 |= 0x8000;
    Hu3DCameraCreate(1);
    temp_r29 = &lbl_8018BFC0;
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0, 480.0, 0.0f, 1.0f);
    lbl_2_bss_114 = fn_8002F454(lbl_2_bss_1C, 0x3E8, 3, 0, -1, &fn_2_BD90);
    lbl_2_bss_114->unk_4C = 0;
    lbl_2_bss_110 = fn_8002F454(lbl_2_bss_1C, 0xA, 0, 0, -1, &fn_2_70C);
    fn_8002F9C4(lbl_2_bss_1C, 0, 4);
    lbl_2_bss_118[0] = fn_8002FAC0(lbl_2_bss_1C, 0);
    fn_8002F9C4(lbl_2_bss_1C, 1, 0x1C);
    for (i = 0; i < 4; i++) {
        temp_r30 = fn_8002F454(lbl_2_bss_1C, 0x4B0, 4, 0xA, 0, &fn_2_3B24);
        temp_r30->unk_4C = i;
    }
    lbl_2_bss_12C = 60.0f;
    lbl_2_bss_128 = 50.0f;
    lbl_2_bss_124 = 25000.0f;
    fn_800241C0(30.0f, 30.0f, 20.0f);
    fn_800243AC(0.35f);
    lbl_2_data_30.y = (f32) (1500.0f + lbl_2_bss_60.y);
    lbl_2_data_30.z = (f32) (500.0f + lbl_2_bss_60.z);
    lbl_2_data_48.y = (f32) lbl_2_bss_60.y;
    lbl_2_data_48.z = (f32) (500.0f + lbl_2_bss_60.z);
    fn_80024348(&lbl_2_data_30, &lbl_2_data_3C, &lbl_2_data_48);
    lbl_2_bss_10C = fn_8002F454(lbl_2_bss_1C, 0x1F4, 0xC, 3, -1, &fn_2_2FA4);
    lbl_2_bss_108 = fn_8002F454(lbl_2_bss_1C, 0x44C, 1, 1, -1, &fn_2_7CB4);
    lbl_2_bss_100.unk_00 = fn_8002F454(lbl_2_bss_1C, 0x456, 1, 1, -1, &fn_2_8E74);
    lbl_2_bss_100.unk_04 = fn_8002F454(lbl_2_bss_1C, 0x456, 1, 1, -1, &fn_2_8E74);
    lbl_2_bss_FC = fn_8002F454(lbl_2_bss_1C, 0x460, 1, 2, -1, &fn_2_95E4);
    lbl_2_bss_C8 = fn_8002F454(lbl_2_bss_1C, 0x64, 0, 0, -1, &fn_2_D088);
    lbl_2_bss_E0 = fn_8002F454(lbl_2_bss_1C, 0x5DC, 0, 0, -1, &fn_2_C1C);
    fn_2_DBCC(0x5A);
    lbl_2_bss_F8 = fn_8002F454(lbl_2_bss_1C, 0x1F4, 9, 0, -1, &fn_2_C6DC);
    fn_2_9D00(lbl_2_bss_1C);
    fn_2_1041C();
    fn_2_1079C();
    lbl_2_bss_F4 = fn_2_14640(lbl_2_bss_1C);
    lbl_2_bss_50 = 0.0f;
    lbl_2_bss_54.unk_00 = temp_r29->unk_14;
    fn_800240E4(0);
    lbl_2_bss_120 = 0;
    lbl_2_bss_BE = 0;
    lbl_2_bss_BA = 0;
    fn_800240EC(3000.0f, 10000.0f, 0xAU, 0x3CU, 0xA0U);
    Hu3DBGColorSet(0xAU, 0x3CU, 0xA0U);
    lbl_2_bss_88 = 3000.0f;
    lbl_2_bss_84 = 142000.0f;
    lbl_2_bss_11C = fn_80032A94(0x50A);
}

// fn_2_70C

void fn_2_A10(void) {
    s32 i;

    if (fn_80041600() == 0) {
        fn_2_10710();
        for (i = 0; i < 4; i++) {
            fn_8004D6F4(lbl_2_data_4[lbl_8018FC10[i].unk_00]);
        }
        
        fn_80032F7C();
        fn_8002EF20(1, 1);
    }
}

void fn_2_A98(void) {
    fn_800240EC(174.0f, 271.0f, 0xA, 0x3C, 0xA0);
    Hu3DBGColorSet(0xAU, 0x3CU, 0xA0U);
}

void fn_2_AEC(s16 arg0) {
    s32 j;
    s32 i;
    unkSubstructBSS114* temp_r31;

    temp_r31 = lbl_2_bss_E0->unk_5C;
    if (arg0 != 0) {
        for (i = 0; i < 4; i++) {
            fn_8003FBA8(temp_r31->unk_00[i]);
            fn_8003FBA8(temp_r31->unk_80[i]);
            fn_8003FBA8(temp_r31->unk_88[i]);
            for (j = 0; j < 2; j++) {
                fn_8003FBA8(temp_r31->unk_08[i][j]);
            }
        }
        return;
    }
    for (i = 0; i < 4; i++) {
        fn_8003FBEC(temp_r31->unk_00[i]);
        fn_8003FBEC(temp_r31->unk_80[i]);
        fn_8003FBEC(temp_r31->unk_88[i]);
        for (j = 0; j < 2; j++) {
            fn_8003FBEC(temp_r31->unk_08[i][j]);
        }
    }
}

void fn_2_C1C(unkStructBSS114* arg0) {
    s16 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 j;
    s32 i;
    unkSubstructBSS114* temp_r31;

    arg0->unk_5C = HuMemDirectMallocNum(0, 0x148, 0x10000000U);
    temp_r31 = arg0->unk_5C;
    for (i = 0; i < 4; i++) {
        temp_r31->unk_00[i] = fn_8003F958(lbl_2_data_80[lbl_8018FC10[i].unk_00], 2, 0);
        fn_8003FBEC(temp_r31->unk_00[i]);
        fn_8003FED8(temp_r31->unk_00[i], 0);
        fn_8003FCC0(temp_r31->unk_00[i], (f32) ((i & 1) * 0x1B6 + 0x25), ((i>1)*0x166)+0x3B);
        temp_r31->unk_80[i] = fn_8003F958(0x20002F, 3, 0);
        fn_8003FBEC(temp_r31->unk_80[i]);
        fn_8003FED8(temp_r31->unk_80[i], 0);
        fn_8003FCC0(temp_r31->unk_80[i], (f32) (((i & 1) * 0x1B6) + 0x49), (((i>1) * 0x166) + 0x3D));
        temp_r31->unk_88[i] = fn_8003F958(0x200030, 4, 0);
        fn_8003FBEC(temp_r31->unk_88[i]);
        fn_8003FED8(temp_r31->unk_88[i], 0);
        fn_8003FCC0(temp_r31->unk_88[i], (f32) (((i & 1) * 0x1B6) + 0x49), (((i>1) * 0x166) + 0x3D));
        fn_8003FDF0(temp_r31->unk_88[i], 0, 0, 0);
        fn_8003FDA8(temp_r31->unk_88[i], 0.5f);
        for (j = 0; j < 2; j++) {
            temp_r31->unk_08[i][j] = fn_8003F958(0x20002E, 1, 0);
            fn_8003FBEC(temp_r31->unk_08[i][j]);
            fn_8003FED8(temp_r31->unk_08[i][j], 0);
            fn_8003FCC0(temp_r31->unk_08[i][j], 0x45 + ((i & 1) * 0x1B6) + (j * 0x14), ((i>1) * 0x166) + 0x3F);
            fn_8003FC30(temp_r31->unk_08[i][j], 1);
        }
        for (j = 0; j < 3; j++) {
            temp_r31->unk_50[i][j] = fn_8003F958(0x20002D, 0, 0);
            fn_8003FBEC(temp_r31->unk_50[i][j]);
            fn_8003FED8(temp_r31->unk_50[i][j], 0);
            fn_8003FC30(temp_r31->unk_50[i][j], 1);
            temp_r31->unk_68[i][j] = fn_8003F958(0x20002D, 0, 0);
            fn_8003FBEC(temp_r31->unk_68[i][j]);
            fn_8003FED8(temp_r31->unk_68[i][j], 0);
            fn_8003FC30(temp_r31->unk_68[i][j], 1);
        }
        fn_8003FE90(temp_r31->unk_50[i][0], 0xA);
        fn_8003FE90(temp_r31->unk_68[i][0], 0xB);
        temp_r31->unk_90[i] = 1.0f;
        temp_r31->unk_A0[i] = 1.0f;
        temp_r31->unk_130[i] = 0;
        temp_r31->unk_138[i] = 0;
    }
    arg0->unk_14 = &fn_2_11D0;
}

void fn_2_14738(unkStructBSS114* arg0) {
    fn_8002FB10(arg0, lbl_2_bss_6C.x, lbl_2_bss_6C.y, lbl_2_bss_6C.z);
    if (arg0->unk_4C == 1U) {
        fn_80021228(*arg0->unk_40, 1);
        fn_8002F7AC(HuPrcCurrentGet(), arg0);
    }
}
