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

void fn_2_70C(unkStructBSS114* arg0) {
    s16 var_r29;
    unkSubstructBSS114* temp_r30_2;
    s32 i;

    switch (lbl_2_bss_120) {
        case 0:
            break;
        case 1:
            if (lbl_2_bss_BE == 1) {
                lbl_2_bss_120 = 2;
                lbl_2_bss_C0 = fn_80035794(3, 1);
                fn_80033140(lbl_2_bss_A4, 0x64);
            }
            break;
        case 2:
            if (lbl_2_bss_114 == NULL) {
                lbl_2_bss_114 = fn_8002F454(HuPrcCurrentGet(), 0x3E8, 0, 0, -1, &fn_2_C130);
                lbl_2_bss_114->unk_4C = 0;
                var_r29 = 0;
                lbl_2_bss_BA = 0;
                for (i = 0; i < 4; i++) {
                    temp_r30_2 = lbl_2_bss_118[i]->unk_5C;
                    lbl_2_bss_118[i]->unk_14 = &fn_2_48A0;
                    temp_r30_2->unk_00[0] = 5;
                    temp_r30_2->unk_68[0][0] = 0;
                    if (temp_r30_2->unk_68[1][2] > var_r29) {
                        var_r29 = temp_r30_2->unk_68[1][2];
                    }
                    lbl_2_bss_B2[i] = -1;
                    lbl_2_bss_AA[i] = -1;
                }
                if ((s16) var_r29 > 0) {
                    for (i = 0; i < 4; i++) {
                        temp_r30_2 = lbl_2_bss_118[i]->unk_5C;
                        if (temp_r30_2->unk_68[1][2] == var_r29) {
                            lbl_2_bss_AA[lbl_2_bss_BA] = lbl_8018FC10[i].unk_00;
                            lbl_2_bss_B2[lbl_2_bss_BA++] = i;
                            temp_r30_2->unk_68[0][0] = 1;
                        }
                    }
                }
                OSReport(lbl_2_data_6F, lbl_2_bss_BA);
            }
            break;
    }
    if (lbl_801D3CC2 != 0) {
        fn_800414AC(2, 0, 0x3C);
        fn_80033140(lbl_2_bss_A4, 0x64);
        fn_80032BC4(lbl_2_bss_11C);
        arg0->unk_14 = &fn_2_A10;
    }
}

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

void fn_2_11D0(unkStructBSS114* arg0) {
    unkStructBSS114* sp1C;
    Vec3f sp18;
    Vec3f spC;
    unkSubstructBSS114* sp8;
    unkSubstructBSS114* temp_r31;
    s32 i;
    s32 j;
    unkStructBSS114* temp_r28;
    s16 temp;

    temp_r31 = arg0->unk_5C;
    
    for (i = 0; i < 4; i++) {
        sp8 = lbl_2_bss_118[i]->unk_5C;
        if (temp_r31->unk_130[i] != 0) {
            temp_r28 = lbl_2_bss_118[i];
            sp18.x = temp_r28->unk_18.x;
            sp18.y = temp_r28->unk_18.y;
            sp18.z = temp_r28->unk_18.z;
            fn_2_10240(&sp18, &spC);
            
            for (j = 0; j < 3; j++) {
                fn_8003FCC0(temp_r31->unk_50[i][j], -20.0f + spC.x + temp_r31->unk_F0[i] + (f32) (j * 0x10), 20.0f + spC.y + temp_r31->unk_100[i]);
                fn_8003FDA8(temp_r31->unk_50[i][j], temp_r31->unk_90[i]);
            }
            
            temp_r31->unk_C0[i] -= 0.5f;
            temp_r31->unk_100[i] -= 1.0f;
            if (temp_r31->unk_130[i] < 15) {
                temp_r31->unk_90[i] -= 2.0f / 30.0f;
            }
            
            if (--temp_r31->unk_130[i] == 0) {
                fn_8003FBEC(temp_r31->unk_50[i][0]);
                fn_8003FBEC(temp_r31->unk_50[i][1]);
            }
        }
        if (temp_r31->unk_138[i] != 0) {
            temp_r28 = lbl_2_bss_118[i];
            sp18.x = temp_r28->unk_18.x;
            sp18.y = temp_r28->unk_18.y;
            sp18.z = temp_r28->unk_18.z;
            fn_2_10240(&sp18, &spC);
            
            for (j = 0; j < 2; j++) {
                fn_8003FCC0(temp_r31->unk_68[i][j], -20.0f + spC.x + temp_r31->unk_110[i] + (f32) (j * 0x10), -20.0f + spC.y + temp_r31->unk_120[i]);
                fn_8003FDA8(temp_r31->unk_68[i][j], temp_r31->unk_A0[i]);
            }
            
            temp_r31->unk_E0[i] += 0.5f;
            temp_r31->unk_120[i] += 1.0f;
            if (temp_r31->unk_138[i] < 0xF) {
                temp_r31->unk_A0[i] -= 2.0f / 30.0f;
            }
            
            if (--temp_r31->unk_138[i] == 0) {
                fn_8003FBEC(temp_r31->unk_68[i][0]);
                fn_8003FBEC(temp_r31->unk_68[i][1]);
            }
        }
        fn_2_15C4(i);
    }
}

void fn_2_15C4(s16 arg0) {
    s32 temp_r30;
    unkSubstructBSS114* temp_r31;
    unkSubstructBSS114* temp_r29;

    temp_r31 = lbl_2_bss_E0->unk_5C;
    temp_r29 = lbl_2_bss_118[arg0]->unk_5C;
    temp_r30 = temp_r29->unk_68[1][2];
    fn_8003FE90(temp_r31->unk_08[arg0][0], temp_r30 / 10);
    fn_8003FE90(temp_r31->unk_08[arg0][1], temp_r30 % 10);
}

void fn_2_169C(s16 arg0) {
    s32 i;
    unkSubstructBSS114* temp_r28;
    unkSubstructBSS114* temp_r31;

    temp_r31 = lbl_2_bss_E0->unk_5C;
    temp_r28 = lbl_2_bss_118[arg0]->unk_5C;
    for (i = 0; i < 2; i++) {
        fn_8003FBA8(temp_r31->unk_50[arg0][i]);
    }
    temp_r31->unk_90[arg0] = 1.0f;
    temp_r31->unk_C0[arg0] = ((arg0 > 1) * 0x18E) + 0x34;
    temp_r31->unk_B0[arg0] = ((arg0 & 1) * 0x1BA) + 0x29;
    temp_r31->unk_100[arg0] = 0.0f;
    temp_r31->unk_F0[arg0] = 0.0f;
    fn_8003FE90(temp_r31->unk_50[arg0][1], temp_r28->unk_68[2][0]);
    temp_r31->unk_130[arg0] = 0x2D;
}

void fn_2_1858(s16 arg0, s16 arg1) {
    s16 temp_r4;
    s32 temp_r0;
    s32 var_r28;
    unkSubstructBSS114* temp_r29;
    unkSubstructBSS114* temp_r31;

    temp_r31 = lbl_2_bss_E0->unk_5C;
    temp_r29 = lbl_2_bss_118[arg0]->unk_5C;
    for (var_r28 = 0; var_r28 < 2; var_r28++) {
        fn_8003FBA8(temp_r31->unk_68[arg0][var_r28]);
    }
    temp_r31->unk_A0[arg0] = 1.0f;
    temp_r31->unk_E0[arg0] = ((arg0 > 1) * 0x18E) + 0x14;
    temp_r31->unk_D0[arg0] = ((arg0 & 1) * 0x1BA) + 0x29;
    temp_r31->unk_120[arg0] = 0.0f;
    temp_r31->unk_110[arg0] = 0.0f;
    fn_8003FE90(temp_r31->unk_68[arg0][1], arg1);
    temp_r31->unk_138[arg0] = 0x2D;
    temp_r31->unk_140[arg0] = arg1;
    temp_r29->unk_68[1][2] -= arg1;
    if (temp_r29->unk_68[1][2] < 0) {
        temp_r29->unk_68[1][2] = 0;
    }
}

void fn_2_1A38(unkStructBSS114* arg0) {
    Vec3f sp20;
    Vec3f sp14;
    Vec3f sp8;
    unkStructBSS114 *temp;
    unkStructBSS114 *temp2;

    temp = fn_80021444(arg0->unk_40->unk_00[0], lbl_2_data_124);
    temp->unk_04 = 2;
    
    sp20.x = -2500.0f;
    sp20.y = 150.0f;
    sp20.z = -6800.0f;
    sp14.x = 50.0f;
    sp14.y = 50.0f;
    sp14.z = 50.0f;
    sp8.x = 1500.0f;
    sp8.y = 150.0f;
    sp8.z = -4800.0f;
    temp2 = fn_2_FC40(0x12, &sp20, &sp14, &sp8);
    fn_2_E6BC(temp2->unk_4C, 5.0f, 1.5f, 0.2f, 0.8f, 3.0f);
}

void fn_2_1B80(unkStructBSS114* arg0) {
    Vec3f sp14;
    Vec3f sp8;
    unkStructBSS114* temp;
    unkStructBSS114* temp2;

    temp = fn_80021444(arg0->unk_40->unk_00[0], lbl_2_data_124[1]);
    temp->unk_04 = 2;
    sp14.x = -1000.0f;
    sp14.y = 0.0f;
    sp14.z = -9100.0f;
    sp8.x = 150.0f;
    sp8.y = 100.0f;
    sp8.z = 100.0f;
    temp2 = fn_2_FC40(0xE, &sp14, &sp8, &sp14);
    fn_8002FB20(temp2, 3.0f, 0.0f, 0.0f);
    fn_8002FB30(temp2, 0.0f, 0.0f, 50.0f);
    fn_2_E6BC(temp2->unk_4C, 4.5f, 2.5f, 0.08f, 0.9f, 1.0f);
}

void fn_2_1CF0(unkStructBSS114* arg0) {
    Vec3f sp20;
    Vec3f sp14;
    Vec3f sp8;
    unkStructBSS114 *temp;

    temp = fn_80021444(arg0->unk_40->unk_00[0], lbl_2_data_124[2]);
    temp->unk_04 = 2;
    sp20.x = 500.0f;
    sp20.y = 0.0f;
    sp20.z = -24300.0f;
    sp14.x = 200.0f;
    sp14.y = 100.0f;
    sp14.z = 100.0f;
    sp8.x = 1000.0f;
    sp8.y = 0.0f;
    sp8.z = -16300.0f;
    fn_2_FC40(0x28, &sp20, &sp14, &sp8);
}

void fn_2_1DE8(unkStructBSS114* arg0) {
    Vec3f sp2C;
    Vec3f sp20;
    Vec3f sp14;
    Vec3f sp8;
    unkStructBSS114 *temp2;
    unkStructBSS114 *temp;

    temp = fn_80021444(arg0->unk_40->unk_00[0], lbl_2_data_124[3]);
    temp->unk_04 = 2;
    sp2C.x = 0.0f;
    sp2C.y = -150.0f + 0.003921569f * (300.0f * fn_800325F4());
    sp2C.z = -23000.0f;
    fn_2_91AC(lbl_2_bss_100.unk_00, &sp2C);
    sp2C.x = 0.0f;
    sp2C.y = -150.0f + 0.003921569f * (300.0f * fn_800325F4());
    sp2C.z = -25000.0f;
    fn_2_91AC(lbl_2_bss_100.unk_04, &sp2C);
    sp2C.x = 5500.0f;
    sp2C.y = 0.0f;
    sp2C.z = -29800.0f;
    sp20.x = 100.0f;
    sp20.y = 100.0f;
    sp20.z = 100.0f;
    sp14.x = -1500.0f;
    sp14.y = 0.0f;
    sp14.z = -24900.0f;
    temp2 = fn_2_FC40(0x14, &sp2C, &sp20, &sp14);
    fn_2_E6BC(temp2->unk_4C, 6.0f, 1.5f, 0.2f, 0.8f, 3.5f);
    sp8.x = -650.0f;
    sp8.y = -360.0f;
    sp8.z = -26300.0f;
    lbl_2_bss_D0 = fn_2_10A88(&sp8, 3);
    lbl_2_bss_90[0] = fn_80032EAC(0x50B, &sp8);
}

void fn_2_20B0(unkStructBSS114* arg0) {
    Vec3f sp8;
    unkStructBSS114* temp;

    temp = fn_80021444(arg0->unk_40->unk_00[0], lbl_2_data_124[4]);
    temp->unk_04 = 2;
    fn_8002127C(arg0->unk_40->unk_08[1][0], 1);
    sp8.x = 0.0f;
    sp8.y = -370.0f;
    sp8.z = -43000.0f;
    lbl_2_bss_8 = fn_2_10A88(&sp8, 3);
    lbl_2_bss_90[1] = fn_80032EAC(0x50B, &sp8);
    sp8.x = 380.0f;
    sp8.y = -440.0f;
    sp8.z = -32000.0f;
    lbl_2_bss_CC = fn_2_10A88(&sp8, 3);
    lbl_2_bss_90[2] = fn_80032EAC(0x50B, &sp8);
    fn_8002127C(arg0->unk_40->unk_00[2], 1);
    fn_80021228(arg0->unk_40->unk_00[2], -0x3FFFFFFF);
}

void fn_2_21F8(unkStructBSS114* arg0) {
    Vec3f sp2C;
    Vec3f sp20;
    Vec3f sp14;
    Vec3f sp8;
    s32 i;
    s32 var_r30_2;
    unkStructBSS114* temp;

    temp = fn_80021444(arg0->unk_40->unk_00[0], *lbl_2_data_124);
    temp->unk_04 = 2;
    
    fn_8002127C(arg0->unk_40->unk_00[0], 1);
    fn_8002127C(arg0->unk_40->unk_00[1], 1);
    fn_80021228(arg0->unk_40->unk_00[0], 0x40000001);
    fn_80021228(arg0->unk_40->unk_00[1], 0x40000001);
    fn_8002127C(arg0->unk_40->unk_00[3], 1);
    lbl_2_bss_44.x = 0.0f;
    lbl_2_bss_44.y = 100.0f;
    lbl_2_bss_44.z = 0.0f;
    lbl_2_bss_38.x = 0.0f;
    lbl_2_bss_38.y = 1000.0f;
    lbl_2_bss_38.z = -1500.0f;
    lbl_2_bss_2C.x = 0.0f;
    lbl_2_bss_2C.y = 1.0f;
    lbl_2_bss_2C.z = 0.0f;
    fn_80022144(1, &lbl_2_bss_44, &lbl_2_bss_2C, &lbl_2_bss_38);
    Hu3DCameraPerspectiveSet(1, lbl_2_bss_12C, lbl_2_bss_128, lbl_2_bss_124, 1.2f);
    lbl_2_bss_54.unk_00 = lbl_2_bss_44;
    fn_2_D088(NULL);
    sp20 = lbl_2_bss_44;
    PSVECSubtract(&lbl_2_bss_38, &lbl_2_bss_44, &sp2C);
    fn_800BBFB0(&sp2C, &sp2C);
    fn_80032D3C(&sp20, &sp2C, lbl_2_bss_88, lbl_2_bss_84, 0x12C, 0x12C, 0x12C);
    sp14.x = 300.0f;
    sp14.y = -450.0f;
    sp14.z = -3100.0f;
    lbl_2_bss_D8 = fn_2_10A88(&sp14, 3);
    lbl_2_bss_90[0] = fn_80032EAC(0x50B, &sp14);
    sp14.x = -300.0f;
    sp14.y = -340.0f;
    sp14.z = -4720.0f;
    lbl_2_bss_D4 = fn_2_10A88(&sp14, 3);
    lbl_2_bss_90[1] = fn_80032EAC(0x50B, &sp14);
    fn_8002127C(arg0->unk_40->unk_00[2], 1);
    fn_80021228(arg0->unk_40->unk_00[2], -0x3FFFFFFF);

    var_r30_2 = 4;
    for (i = 0; i < var_r30_2; i++) {
        sp8.x = -340.0f + (0.003921569f * (680.0f * fn_800325F4()));
        sp8.y = -250.0f + (0.003921569f * (500.0f * fn_800325F4()));
        sp8.z = ((-1550.0f - (f32) (i * 0x104)) - 40.0f) + (0.003921569f * (80.0f * fn_800325F4()));
        fn_2_10A88(&sp8, 0);
    }
}

void fn_2_33B4(unkStructBSS114* arg0) {
    fn_800210CC(arg0->unk_40->unk_00[3], 110.0f, 5.0 * fn_800EB910(M_PI * (f64) lbl_2_bss_10 / 180.0), -1500.0);
    lbl_2_bss_10 += 2.0f;
    if (lbl_2_bss_10 >= 360.0f) {
        lbl_2_bss_10 -= 360.0f;
    }
}

void fn_2_14738(unkStructBSS114* arg0) {
    fn_8002FB10(arg0, lbl_2_bss_6C.x, lbl_2_bss_6C.y, lbl_2_bss_6C.z);
    if (arg0->unk_4C == 1U) {
        fn_80021228(arg0->unk_40->unk_00[0], 1);
        fn_8002F7AC(HuPrcCurrentGet(), arg0);
    }
}
