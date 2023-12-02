#include "common.h"
#include "REL/executor.h"

extern s16 lbl_1_bss_E;
extern s16 lbl_1_data_38[];

//TODO: fill these in correctly
Vec3f lbl_1_rodata_10 = {0.0f, 0.0f, 0.0f};
Vec3f lbl_1_rodata_1C = {0.0f, 0.0f, 0.0f};

extern f32 lbl_1_bss_1C;
extern Vec3f lbl_1_bss_24;
extern Vec3f lbl_1_bss_3C;
f32 lbl_1_rodata_28;
s32 lbl_1_bss_54;


void fn_1_A0(void) {
    UnkOvl* temp_r3;

    OSReport("******* Boot ObjectSetup *********\n");
    lbl_1_bss_54 = omInitObjMan(0x32, 0x2000);
    lbl_1_bss_3C.x = 0.0f;
    lbl_1_bss_3C.y = 0.0f;
    lbl_1_bss_3C.z = 0.0f;
    lbl_1_bss_24.x = 0.0f;
    lbl_1_bss_24.y = 0.0f;
    lbl_1_bss_24.z = 0.0f;
    lbl_1_bss_1C = 0.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 0.0f, 0.0f, 0.0f, 0.0f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    HuPrcCreate(fn_1_26C, 0x64, 0x3000, 0);
    Hu3DBGColorSet(0, 0, 0);
    temp_r3 = omOvlHisGet(0);
    omOvlHisChg(0, temp_r3->unk0, 1, temp_r3->unk8);
}

//void fn_1_26C(void)

void fn_1_9F8(void) {
    s32 temp_r30;
    s32 i;

    temp_r30 = fn_800578E4();
    for (i = 0; lbl_1_data_38[i*2] != -1; i++) {
        if (temp_r30 == lbl_1_data_38[i*2]) {
            fn_80045F74(lbl_1_bss_E, i + 0x360000);
        }
        if (temp_r30 == lbl_1_data_38[i*2+1]) {
            fn_80044920(lbl_1_bss_E);
        }        
    }
}

//fn_1_AC0

//fn_1_1178

//fn_1_152C

typedef struct temp2 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} temp2;

s32 fn_80008364(s32, s32, s32);
s32 fn_8000DD24(void);    
s32 fn_8000DE48(s32, s32, s32);
s16 fn_8000E0F8(s32);   
void fn_8000E520(s16, s32, s32);
void fn_8000E808(s16, s32, s32);
s32 fn_8000E960(s16, s32, f32, f32);
void fn_8000F038(s16, s32, s32);
s16 fn_800204D0(s32); 
void fn_80021228(s16, s32);
void fn_80022420(s16, s32);
void Hu3DModelLightInfoSet(s16, s32);
extern s16 lbl_1_bss_6;
extern temp2 lbl_1_bss_8;
extern f32 lbl_1_rodata_48;
extern f32 lbl_1_rodata_4C;
extern f32 lbl_1_rodata_98;
extern f32 lbl_1_rodata_9C;
extern f32 lbl_1_rodata_A0;

void fn_1_2100(void) {
    s32 temp_r3_2;
    s32 temp_r3;
    s16 temp_r3_3;

    temp_r3_3 = fn_800204D0(fn_80008364(0x74000B, 0x10000000, 2));
    lbl_1_bss_8.unk0 = temp_r3_3;
    fn_80021228(temp_r3_3, 1);
    fn_80021228(temp_r3_3, 0x40000001);
    temp_r3_3 = fn_800204D0(fn_80008364(0x74000C, 0x10000000, 2));
    lbl_1_bss_8.unk2 = temp_r3_3;
    fn_80021228(temp_r3_3, 1);
    fn_80021228(temp_r3_3, 0x40000001);
    temp_r3_3 = fn_800204D0(fn_80008364(0x74000D, 0x10000000, 2));
    lbl_1_bss_8.unk4 = temp_r3_3;
    fn_80021228(temp_r3_3, 1);
    fn_80021228(temp_r3_3, 0x40000001);
    fn_80022420(temp_r3_3, 1);
    Hu3DModelLightInfoSet(temp_r3_3, 1);
    lbl_1_bss_6 = fn_8000E0F8(4);
    fn_80008364(0x740008, 0x10000000, 2);
    temp_r3 = fn_8000DD24();
    temp_r3_2 = fn_8000DE48(temp_r3, 0, 0);
    fn_8000E520(lbl_1_bss_6, 0, temp_r3_2);
    fn_8000E808(lbl_1_bss_6, 0, 4);
    fn_8000F038(lbl_1_bss_6, 0, 0x7F);
    fn_8000E960(lbl_1_bss_6, 0, lbl_1_rodata_48, lbl_1_rodata_4C);
    fn_80008364(0x74000A, 0x10000000, 2);
    temp_r3 = fn_8000DD24();
    temp_r3_2 = fn_8000DE48(temp_r3, 1, 0);
    fn_8000E520(lbl_1_bss_6, 1, temp_r3_2);
    fn_8000E808(lbl_1_bss_6, 1, 4);
    fn_8000E960(lbl_1_bss_6, 1, lbl_1_rodata_48, lbl_1_rodata_98);
    fn_80008364(0x740002, 0x10000000, 2);
    temp_r3 = fn_8000DD24();
    temp_r3_2 = fn_8000DE48(temp_r3, 2, 0);
    fn_8000E520(lbl_1_bss_6, 2, temp_r3_2);
    fn_8000E808(lbl_1_bss_6, 2, 0xC);
    fn_8000E960(lbl_1_bss_6, 2, lbl_1_rodata_48, lbl_1_rodata_9C);
    fn_80008364(0x740009, 0x10000000, 2);
    temp_r3 = fn_8000DD24();
    temp_r3_2 = fn_8000DE48(temp_r3, 0, 0);
    fn_8000E520(lbl_1_bss_6, 3, temp_r3_2);
    fn_8000E808(lbl_1_bss_6, 3, 0xC);
    fn_8000E960(lbl_1_bss_6, 3, lbl_1_rodata_48, lbl_1_rodata_A0);
}

//fn_1_2474

//fn_1_2944