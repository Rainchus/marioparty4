#include "REL/m427Dll.h"

#include "ext_math.h"
#include "game/animdata.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/sprite.h"

#define FABS(value) ((value < 0) ? -(value) : (value))

typedef struct M427DllStruct {
    s32 unk0;
    s32 unk4;
} M427DllStruct;

typedef struct M427DllStruct2 {
    s32 unk0[3];
    s32 unkC;
    s32 unk10;
    s32 unk14[7];
    s32 unk30[7];
    HsfVector2f unk4C[7];
    f32 unk84;
    f32 unk88;
    s32 unk8C;
    f32 unk90;
    f32 unk94;
    f32 unk98;
    s32 unk9C;
    s32 unkA0;
} M427DllStruct2; // sizeof 0xA4

typedef struct M427DllStruct3 {
    Vec rot;
    Vec cen;
    f32 zoom;
} M427DllStruct3;

typedef struct M427DllMapStruct {
    char unk_0[0x2];
    s16 unk2;
    s16 unk4;
    char unk_6[0x2];
    AnimData* unk8;
    char unk_C[0x74];
    void* unk80;
    char unk_84[0x14];
} M427DllMapStruct; // sizeof 0x98

typedef struct M427DllMapStruct2 {
    s8 unk0;
    s16 unk2;
    s16 unk4;
} M427DllMapStruct2;

typedef struct M427DllMapSubstruct {
    s16 unk0;
    Vec unk4;
} M427DllMapSubstruct; // sizeof 0x10

typedef struct M427DllMapSubstruct2 {
    s16 unk0;
    Vec unk4;
    s16 unk10;
    s16 unk12;
    s16 unk14[4];
} M427DllMapSubstruct2; // sizeof 0x1C

typedef struct M427DllMapSubstruct4 {
    char unk[0x28];
    AnimData* unk28;
} M427DllMapSubstruct4;

typedef struct M427DllMapSubstruct7 {
    s16 unk0;
    s32 unk4;
    void* unk8;
} M427DllMapSubstruct7;

typedef struct M427DllMapUNKBA {
    s16 unk0;
    char unk[0x2E];
} M427DllMapUNKBA;

typedef struct M427DllMapUNK180 {
    s16 unk0;
    s16 unk2;
} M427DllMapUNK180;

typedef struct M427DllMapSubstruct3 {
    s16 unk0;
    s16 unk2[11];
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    char unk_22[0x3A];
    s16 unk5C;
    char unk_5E[0x1A];
    Vec unk78;
    Vec unk84;
    f32 unk90;
    char unk_94[0x4];
    void* unk98;
    M427DllMapSubstruct7* unk9C;
    char unk_A0[0xC];
    M427DllMapSubstruct4* unkAC;
    char unk_B0[0xA];
    M427DllMapUNKBA unkBA[2][2];
    char unk_17A[0x6];
    M427DllMapUNK180 unk180[2][2];
    char unk_190[0x8];
} M427DllMapSubstruct3; // sizeof 0x198

typedef struct M427DllMapStruct3 {
    u8 unk0;
    M427DllMapSubstruct3 unk4[2];
    AnimData* unk334;
    AnimData* unk338;
    char unk_33C[0x10];
    M427DllMapSubstruct2 unk34C[3];
    M427DllMapSubstruct unk3A0[5];
} M427DllMapStruct3; // sizeof 0x3F0

typedef struct M427DllMapSubstruct5 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    Vec unk8;
    char unk[0x8];
} M427DllMapSubstruct5;

typedef struct M427DllMapStruct4 {
    s16 unk0;
    Vec* unk4;
    Vec2f* unk8;
    Vec* unkC;
    GXColor* unk10;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    M427DllMapSubstruct5* unk1C;
    void* unk20;
    u32 unk24;
    void* unk28;
    u32 unk2C;
    void* unk30;
    u32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    s16 unk48[1];
    s16 unk4A;
} M427DllMapStruct4;

typedef struct M427DllMapStruct5 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} M427DllMapStruct5; // sizeof 0x14

omObjData* lbl_1_bss_548;
M427DllMapStruct3 lbl_1_bss_158;
M427DllMapStruct2 lbl_1_bss_F8[0x10];
M427DllMapStruct* lbl_1_bss_F0;
s16 lbl_1_bss_EC[2];
s16 lbl_1_bss_E8[2];
M427DllMapStruct5* lbl_1_bss_E4;
M427DllMapStruct4 lbl_1_bss_98;
f32 lbl_1_bss_94;

void fn_1_372C(void);
void fn_1_4218(omObjData*);
void fn_1_44F4(f32, f32, f32, f32, f32);
void fn_1_48EC(ModelData*, Mtx);
void fn_1_4D7C(ModelData*, Mtx);
void fn_1_50A0(ModelData*, Mtx);
void fn_1_510C(s32, s16, s16);
void fn_1_558C(M427DllMapStruct4*);
void fn_1_618C(ModelData*, Mtx);
void fn_1_6760(omObjData*);
void fn_1_C2C8(Vec*, Vec*, Vec*, void*);
void fn_1_D22C(void);
s16 fn_1_D63C(AnimData*, s32, f32, s32, s32);
void fn_1_DB80(s16);
void fn_1_DC64(s16, void (*)(void));
void fn_1_DC9C(s16, s32);


void fn_1_32F4(Process* arg0) {
    s16 var_r31;
    AnimData* temp_r30;
    s32 var_r29;
    s32 var_r28;

    lbl_1_bss_158.unk0 = 0;
    lbl_1_bss_548 = omAddObjEx(arg0, 0x7F, 0, 0, -1, fn_1_6760);
    lbl_1_bss_F0 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x10 * sizeof(M427DllMapStruct), 0x10000000);
    
    for (var_r31 = 0; var_r31 < 0x10; var_r31++) {
        lbl_1_bss_F0[var_r31].unk2 = -1;
    }
    temp_r30 = HuSprAnimRead(HuDataReadNum(0x3A0017, MEMORY_DEFAULT_NUM));   
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        lbl_1_bss_EC[var_r31] = fn_1_D63C(temp_r30, 0x200, 80.0f, 0x40, 0x40);
        fn_1_DC64(lbl_1_bss_EC[var_r31], &fn_1_D22C);
        fn_1_DC9C(lbl_1_bss_EC[var_r31], 1);
        Hu3DModelLayerSet(lbl_1_bss_EC[var_r31], 7);
        if (var_r31 == 0) {
            var_r29 = 1;
        } else {
            var_r29 = 2;
        }
        Hu3DModelCameraSet(lbl_1_bss_EC[var_r31], var_r29);
    }
    temp_r30 = HuSprAnimRead(HuDataReadNum(0x3A001A, MEMORY_DEFAULT_NUM));
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        lbl_1_bss_E8[var_r31] = fn_1_D63C(temp_r30, 4, 120.0f, 0, 0);
        fn_1_DC9C(lbl_1_bss_E8[var_r31], 1);
        Hu3DModelLayerSet(lbl_1_bss_E8[var_r31], 7);
        if (var_r31 == 0) {
            var_r28 = 1;
        } else {
            var_r28 = 2;
        }
        Hu3DModelCameraSet(lbl_1_bss_E8[var_r31], var_r28);
    }
    fn_1_372C();
    
    for (var_r31 = 0; var_r31 < 0x10; var_r31++) {
        lbl_1_bss_F8[var_r31].unk0 = -1;
        lbl_1_bss_F8[var_r31].unk2 = Hu3DModelCreateFile(0x3A0012);
        Hu3DModelAttrSet(lbl_1_bss_F8[var_r31].unk2, 1);
        Hu3DModelScaleSet(lbl_1_bss_F8[var_r31].unk2, 0.75f, 0.75f, 0.75f);
        Hu3DModelLayerSet(lbl_1_bss_F8[var_r31].unk2, 4);
        Hu3DMotionSpeedSet(lbl_1_bss_F8[var_r31].unk2, 2.0f);
        lbl_1_bss_F8[var_r31].unk4 = Hu3DAnimCreate(HuDataReadNum(0x3A001B, MEMORY_DEFAULT_NUM), lbl_1_bss_F8[var_r31].unk2, "db91");
        Hu3DAnimSpeedSet(lbl_1_bss_F8[var_r31].unk4, 2.0f);
    }
}

void fn_1_372C(void) {
    M427DllMapSubstruct* var_r29 = &lbl_1_bss_158.unk3A0[0];
    M427DllMapSubstruct2* var_r30 = &lbl_1_bss_158.unk34C[0];
    s16 sp1A[5] = { 0, 0, 1, 1, 0 };
    Vec sp60[5] = {
        { -700.0f, -150.0f, -7000.0f  },
        {    0.0f, -300.0f, -12000.0f },
        {  800.0f, -350.0f, -12700.0f },
        {  600.0f, -350.0f, -13700.0f },
        {  825.0f, -450.0f, -15000.0f }
    };
    s16 sp8[3] = { 1, 1, 0 };
    s16 spE[3][2] =  { { 4, 5 }, { 8, -1 }, { 9, -1 } };
    s16 sp24[3][4] = {
        { 180, 120, 60, 60 },
        { 90, 180, 60, 60 },
        { 90, 180, 60, 60 }
    };
    Vec sp3C[3] = {
        -350.0f, -300.0f, -10000.0f,
        -700.0f, -600.0f, -17000.0f,
         700.0f, -600.0f, -19000.0f
    };
    s16 var_r28;
    s16 var_r31;
    
    for (var_r31 = 0; var_r31 < 5; var_r31++, var_r29++) {
        var_r29->unk0 = sp1A[var_r31];
        var_r29->unk4.x = sp60[var_r31].x;
        var_r29->unk4.y = sp60[var_r31].y;
        var_r29->unk4.z = sp60[var_r31].z;
    }
    
    for (var_r31 = 0; var_r31 < 3; var_r31++, var_r30++) {
        var_r30->unk0 = sp8[var_r31];
        var_r30->unk4.x = sp3C[var_r31].x;
        var_r30->unk4.y = sp3C[var_r31].y;
        var_r30->unk4.z = sp3C[var_r31].z;
        var_r30->unk10 = spE[var_r31][0];
        var_r30->unk12 = spE[var_r31][1];
        for (var_r28 = 0; var_r28 < 4; var_r28++) {
            var_r30->unk14[var_r28] = sp24[var_r31][var_r28];
        }
    }
}

void fn_1_3A88(void) {
    M427DllMapStruct* sp8;
    s16 var_r30;
    M427DllMapSubstruct3* var_r31;

    sp8 = lbl_1_bss_F0;
    HuSprAnimKill(lbl_1_bss_158.unk334);
    HuSprAnimKill(lbl_1_bss_158.unk338);
    
    for (var_r30 = 0, var_r31 = &lbl_1_bss_158.unk4[0]; var_r30 < 2; var_r30++, var_r31++) {
        if (var_r31->unk98) {
            HuMemDirectFree(var_r31->unk98);
        }
    }
}

void fn_1_3B20(s8 arg0, s16 arg1) {
    M427DllMapStruct2* var_r31 = &lbl_1_bss_F8[0];
    M427DllMapSubstruct3* temp_r30 = &lbl_1_bss_158.unk4[arg1];
    Vec sp54[4] = {
        {  110.0f, -20.0f,   0.0f },
        { -110.0f, -20.0f,   0.0f },
        {  110.0f, -20.0f, 190.0f },
        { -110.0f, -20.0f, 190.0f }
    };
    Mtx sp24;
    f32 sp14[4] = { 135.0f, 225.0f, 45.0f, 315.0f };
    Point3d sp8;
    f32 temp_f31;
    s16 var_r29;
    s32 var_r27;

    for (var_r29 = 0; var_r29 < 0x10; var_r29++, var_r31++) {
        if (var_r31->unk0 == -1) break;
    }
    if (var_r29 != 0x10) {
        var_r31->unk0 = arg0;
        temp_f31 = temp_r30->unk90;
        PSMTXRotRad(sp24, 0x59, MTXDegToRad(temp_f31));
        PSMTXMultVec(sp24, &sp54[arg0], &sp8);
        sp8.x += temp_r30->unk84.x;
        sp8.y += temp_r30->unk84.y;
        sp8.z += temp_r30->unk84.z;
        Hu3DModelAttrReset(var_r31->unk2, 1);
        if (arg1 == 0) {
            var_r27 = 1;
        } else {
            var_r27 = 2;
        }
        Hu3DModelCameraSet(var_r31->unk2, var_r27);
        Hu3DModelPosSet(var_r31->unk2, sp8.x, sp8.y, sp8.z);
        Hu3DModelRotSet(var_r31->unk2, 0.0f, temp_f31 + sp14[arg0], 0.0f);
        Hu3DMotionTimeSet(var_r31->unk2, 0.0f);
        if (arg0 < 2) {
            Hu3DModelAmbSet(var_r31->unk2, 1.0f, 1.0f, 1.0f);
        } else {
            Hu3DModelAmbSet(var_r31->unk2, 0.5f, 0.5f, 0.5f);
        }
        Hu3DAnimBankSet(var_r31->unk4, 0);
    }
}

void fn_1_3DBC(void) {
    M427DllMapStruct2* var_r31;
    s16 var_r30;
    f32 temp_f31;

    var_r31 = &lbl_1_bss_F8[0];
    for (var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        if (var_r31->unk0 != -1) {
            temp_f31 = Hu3DMotionMaxTimeGet(var_r31->unk2);
            if (Hu3DMotionTimeGet(var_r31->unk2) >= temp_f31) {
                var_r31->unk0 = -1;
                Hu3DModelAttrSet(var_r31->unk2, 1U);
            }
        }
    }
}

void fn_1_3E58(omObjData* arg0) {
    s32 sp8[8];
    M427DllMapStruct* var_r26;
    M427DllMapSubstruct3* var_r31;
    ModelData* temp_r25;
    s16 var_r30;
    M427DllMapStruct4* var_r29;
    s16 var_r28;
    s16 var_r27;

    var_r29 = &lbl_1_bss_98;
    for (var_r28 = 0, var_r31 = lbl_1_bss_158.unk4; var_r28 < 2; var_r28++, var_r31++) {
        var_r27 = fn_1_10FE8(var_r31->unk0, &sp8[0]);

        for (var_r30 = 0; var_r30 < var_r27; var_r30++) {
            temp_r25 = &Hu3DData[sp8[var_r30]];
            temp_r25->unk_38[4] = temp_r25->unk_38[5] = temp_r25->unk_38[6] = temp_r25->unk_38[7] = -1;
        }
        
        for (var_r30 = 0; var_r30 < 2; var_r30++) {
            for (var_r27 = 0; var_r27 < 2; var_r27++) {
                Hu3DModelKill(var_r31->unk180[var_r30][var_r27].unk0);
            }
        }
        for (var_r30 = 0; var_r30 < 2; var_r30++) {
            for (var_r27 = 0; var_r27 < 2; var_r27++) {
                Hu3DModelKill(var_r31->unkBA[var_r30][var_r27].unk0);
            }
        }
        HuSprAnimKill(var_r31->unkAC->unk28);
        Hu3DModelKill(var_r31->unk1A);
        Hu3DModelKill(var_r31->unk1C);
        HuMemDirectFree(var_r31->unk98);
        var_r31->unk98 = NULL;
        fn_1_DB80(lbl_1_bss_EC[var_r28]);
        fn_1_DB80(lbl_1_bss_E8[var_r28]);

        for (var_r30 = 0; var_r30 < 11; var_r30++) {
            Hu3DModelKill(var_r31->unk2[var_r30]);
        }
        Hu3DModelKill(var_r31->unk1E);
        Hu3DModelKill(var_r31->unk20);
    }
    for (var_r28 = 0, var_r26 = lbl_1_bss_F0; var_r28 < 0x10; var_r28++, var_r26++) {
        if (var_r26->unk2 != -1) {
            Hu3DModelKill(var_r26->unk4);
            HuSprAnimKill(var_r26->unk8);
            HuMemDirectFree(var_r26->unk80);
        }
    }
    HuMemDirectFree(lbl_1_bss_F0);
    Hu3DFogClear();
    var_r30 = Hu3DModelCreateFile(0x3A0011);
    Hu3DModelCameraSet(var_r30, 1);
    Hu3DModelLayerSet(var_r30, 1);
    Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
    var_r29->unk0 = Hu3DModelCreateFile(0x3A0010);
    Hu3DModelCameraSet(var_r29->unk0, 1);
    Hu3DModelLayerSet(var_r29->unk0, 3);
    Hu3DModelPosSet(var_r29->unk0, 0.0f, 0.0f, 0.0f);
    lbl_1_bss_158.unk0 = 1;
    var_r29->unk48[0] = 0;
    var_r29->unk4A = 0;
    var_r29->unk4 = 0;
    lbl_1_bss_E4 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x10 * sizeof(M427DllMapStruct5), MEMORY_DEFAULT_NUM);
    for (var_r28 = 0; var_r28 < 0x10; var_r28++) {
        lbl_1_bss_E4[var_r28].unk10 = -1.0f;
    }
    fn_1_510C(0, 0x32, 0x32);
    arg0->func = fn_1_4218;
}

void fn_1_4218(omObjData* arg0) {
    f32 var_f31;
    f32 temp_f30;
    f32 var_f29;
    M427DllMapStruct5* var_r31;
    s16 var_r30;
    M427DllMapStruct4* var_r29;
    s32 temp_r28;

    var_r29 = &lbl_1_bss_98;
    var_r31 = &lbl_1_bss_E4[0];
    for (var_r30 = 0; var_r30 < 1; var_r30++) {
        if (--var_r29->unk48[var_r30] < 0.0f) {
            var_r29->unk48[var_r30] = (f32)((((rand8() << 8) | rand8()) % 241) + 0x78);
            var_f31 = ((((rand8() << 8) | rand8()) % 4001) - 0x7D0);
            temp_f30 = -3000.0f;
            var_f29 = ((((rand8() << 8) | rand8()) % 21) + 0xA);
            fn_1_44F4(var_f31, 0.0f, temp_f30, var_f29, 0.0f);
        }
    }
    
    for (var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        if (-1.0f != var_r31->unk10) {
            var_r31->unkC += 20.0f;
            var_r31->unk10 -= 0.2f;
            if (var_r31->unk10 < 0.0f) {
                var_r31->unk10 = -1.0f;
            }
        }
    }
}

void fn_1_44F4(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    M427DllMapStruct5* var_r31;
    s16 var_r30;

    var_r31 = &lbl_1_bss_E4[0];
    
    for (var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        if (-1.0f == var_r31->unk10) break;
    }
    if (var_r30 != 0x10) {
        var_r31->unk0 = arg0;
        var_r31->unk4 = arg1;
        var_r31->unk8 = arg2;
        var_r31->unkC = arg4;
        var_r31->unk10 = arg3;
    }
}

f32 lbl_1_data_F4 = 450.0f;

f32 fn_1_4570(Vec* arg0) {
    f32 temp_f31;
    f32 temp_f30;
    f32 var_f28;
    f32 var_f27;
    f32 var_f23;
    M427DllMapStruct5* var_r31;
    s16 var_r30;

    var_r31 = &lbl_1_bss_E4[0];
    var_f27 = 0.0f;
    
    for (var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        if (-1.0f != var_r31->unk10) {
            temp_f31 = arg0->x - var_r31->unk0;
            temp_f30 = arg0->z - var_r31->unk8;
            if (FABS(temp_f31) > (var_r31->unkC + lbl_1_data_F4)) {
                if (FABS(temp_f30) > (var_r31->unkC + lbl_1_data_F4)) {
                    continue;
                }
            }
            var_f28 = sqrtf((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
            var_f23 = FABS(var_f28 - var_r31->unkC);
            var_f28 = 1.0f - (var_f23 / lbl_1_data_F4);
            if (var_f28 < 0.0f) {
                var_f28 = 0.0f;
            }
            var_f27 += var_r31->unk10 * sind(90.0f * var_f28);
        }
    }
    return var_f27;
}

void fn_1_48EC(ModelData* arg0, Mtx arg1) {
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    f32 sp8;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;

    sp3C.x = CenterM->x;
    sp3C.y = CenterM->y;
    sp3C.z = CenterM->z;
    sp30.x = CRotM->x;
    sp30.y = CRotM->y;
    sp30.z = CRotM->z;
    temp_f29 = *CZoomM;
    CenterM->x = -CenterM->x;
    CenterM->y = -CenterM->y;
    CenterM->z = CenterM->z;
    CRotM->x = 180.0f +  CRotM->x;
    CRotM->y = 180.0f + -CRotM->y;
    CRotM->z = CRotM->z;
    *CZoomM = *CZoomM;
    temp_f31 = CRotM->x;
    temp_f30 = CRotM->y;
    sp8 = CRotM->z;
    sp24.x = (CenterM->x + (*CZoomM * (sind(temp_f30) * cosd(temp_f31))));
    sp24.y = (CenterM->y + (*CZoomM * -sind(temp_f31)));
    sp24.z = (CenterM->z + (*CZoomM * (cosd(temp_f30) * cosd(temp_f31))));
    spC.x = CenterM->x;
    spC.y = CenterM->y;
    spC.z = CenterM->z;
    sp18.x = (sind(temp_f30) * sind(temp_f31));
    sp18.y = cosd(temp_f31);
    sp18.z = (cosd(temp_f30) * sind(temp_f31));
    Hu3DCameraPosSetV(1, &sp24, &sp18, &spC);
    CenterM->x = sp3C.x;
    CenterM->y = sp3C.y;
    CenterM->z = sp3C.z;
    CRotM->x = sp30.x;
    CRotM->y = sp30.y;
    CRotM->z = sp30.z;
    *CZoomM = temp_f29;
}

void fn_1_4D7C(ModelData* arg0, Mtx arg1) {
    Vec sp24;
    Vec sp18;
    Vec spC;
    f32 sp8;
    f32 temp_f30;
    f32 temp_f31;

    temp_f31 = CRotM->x;
    temp_f30 = CRotM->y;
    sp8 = CRotM->z;
    sp24.x = CenterM->x + sind(temp_f30) * cosd(temp_f31) * *CZoomM;
    sp24.y = CenterM->y + *CZoomM * -sind(temp_f31);
    sp24.z = CenterM->z + cosd(temp_f30) * cosd(temp_f31) * *CZoomM;
    sp18.x = CenterM->x;
    sp18.y = CenterM->y;
    sp18.z = CenterM->z;
    spC.x = sind(temp_f30) * sind(temp_f31);
    spC.y = cosd(temp_f31);
    spC.z = cosd(temp_f30) * sind(temp_f31);
    Hu3DCameraPosSetV(1, &sp24, &spC, &sp18);
    if (lbl_1_bss_98.unk30) {
        GXSetTexCopySrc(0, 0, 0x280, 0x1E0);
        GXSetTexCopyDst(0x280, 0x1E0, GX_TF_RGB5A3, 0);
        GXCopyTex(lbl_1_bss_98.unk30, 1);
    }
}

void fn_1_50A0(ModelData* arg0, Mtx arg1) {
    if (lbl_1_bss_98.unk28) {
        GXSetTexCopySrc(0, 0, 0x280, 0x1E0);
        GXSetTexCopyDst(0x280, 0x1E0, GX_TF_RGB5A3, 0);
        GXCopyTex(lbl_1_bss_98.unk28, 0);
    }
}

void fn_1_510C(s32 arg0, s16 arg1, s16 arg2) {
    s16 sp12;
    s16 sp10;
    s16 spE;
    s16 spC;
    s16 spA;
    s16 sp8;
    M427DllMapStruct4* var_r31;
    M427DllMapSubstruct5* var_r30;
    s16 var_r29;
    ModelData* temp_r28;
    s16 var_r27;
    M427DllMapSubstruct5* var_r26;
    M427DllMapSubstruct5* var_r23;

    var_r31 = &lbl_1_bss_98;
    var_r29 = Hu3DHookFuncCreate(fn_1_618C);
    Hu3DModelCameraSet(var_r29, 1);
    Hu3DModelLayerSet(var_r29, 5);
    temp_r28 = &Hu3DData[var_r29];
    var_r29 = Hu3DHookFuncCreate(fn_1_48EC);
    Hu3DModelCameraSet(var_r29, 1);
    Hu3DModelLayerSet(var_r29, 0);
    var_r29 = Hu3DHookFuncCreate(fn_1_4D7C);
    Hu3DModelCameraSet(var_r29, 1);
    Hu3DModelLayerSet(var_r29, 2);
    var_r29 = Hu3DHookFuncCreate(fn_1_50A0);
    Hu3DModelCameraSet(var_r29, 1);
    Hu3DModelLayerSet(var_r29, 4);
    var_r31->unk38 = var_r31->unk3C = 0.0f;
    var_r31->unk34 = GXGetTexBufferSize(0x280, 0x1E0, 5, 0, 0);
    var_r31->unk30 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk34, temp_r28->unk_48);
    var_r31->unk2C = GXGetTexBufferSize(0x280, 0x1E0, 5, 0, 0);
    var_r31->unk28 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk2C, temp_r28->unk_48);
    var_r31->unk16 = arg1 + 1;
    var_r31->unk18 = arg2 + 1;
    var_r31->unk14 = var_r31->unk16 * var_r31->unk18;
    var_r31->unk4 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk14 * sizeof(Vec), temp_r28->unk_48);
    var_r31->unk8 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk14 * sizeof(Vec2f), temp_r28->unk_48);
    var_r31->unkC = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk14 * sizeof(Vec), temp_r28->unk_48);
    var_r31->unk10 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk14 * sizeof(Vec), temp_r28->unk_48);
    var_r31->unk1C = HuMemDirectMallocNum(HEAP_DATA, arg2 * (arg1 * sizeof(M427DllMapSubstruct5)), temp_r28->unk_48);
    var_r30 = var_r31->unk1C;
    var_r23 = var_r26 = HuMemDirectMallocNum(HEAP_DATA, 0x20000, temp_r28->unk_48);
    DCFlushRange(var_r26, 0x20000);
    GXBeginDisplayList(var_r23, 0x20000);
    GXBegin(GX_QUADS, GX_VTXFMT0, (arg1 * arg2 * 4));
    
    for (var_r29 = 0; var_r29 < arg2; var_r29++) {
        for (var_r27 = 0; var_r27 < arg1; var_r30++, var_r27++) {
            var_r30->unk0 = var_r27 + var_r29 * var_r31->unk16;
            var_r30->unk2 = (var_r29 * var_r31->unk16) + var_r27 + 1;
            var_r30->unk4 = ((var_r29 + 1) * var_r31->unk16) + var_r27 + 1;
            var_r30->unk6 = var_r27 + ((var_r29 + 1) * var_r31->unk16);
            GXPosition1x16(var_r30->unk0);
            GXPosition1x16(var_r30->unk0);
            GXPosition1x16(var_r30->unk0);
            GXPosition1x16(var_r30->unk2);
            GXPosition1x16(var_r30->unk2);
            GXPosition1x16(var_r30->unk2);
            GXPosition1x16(var_r30->unk4);
            GXPosition1x16(var_r30->unk4);
            GXPosition1x16(var_r30->unk4);
            GXPosition1x16(var_r30->unk6);
            GXPosition1x16(var_r30->unk6);
            GXPosition1x16(var_r30->unk6);
            fn_1_C2C8(&var_r31->unk4[var_r30->unk0], &var_r31->unk4[var_r30->unk2], &var_r31->unk4[var_r30->unk4], &var_r30->unk8);
        }
    }
    var_r31->unk24 = GXEndDisplayList();
    var_r31->unk20 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk24, temp_r28->unk_48);
    memcpy(var_r31->unk20, var_r26, var_r31->unk24);
    DCFlushRange(var_r31->unk20, var_r31->unk24);
    HuMemDirectFree(var_r26);
    fn_1_558C(var_r31);
}

f32 lbl_1_data_F8 = -1.0f;

void fn_1_558C(M427DllMapStruct4* arg0) {
    Mtx spAC;
    Mtx sp7C;
    Mtx sp4C;
    Vec2f sp44;
    Vec2f sp3C;
    Vec2f sp34;
    Vec2f sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 var_f26;
    f32 var_f25;
    f32 var_f20;
    M427DllMapSubstruct5* var_r30;
    Vec* var_r29;
    Vec* var_r28;
    s16 var_r27;
    M427DllMapStruct5* var_r26;
    Vec2f* var_r25;
    s16 var_r24;
    CameraData* var_r23;
    s16 var_r22;

    var_r23 = &Hu3DCamera[0];
    if (lbl_1_data_F8 == -1.0f) {
        lbl_1_bss_94 = 720.0f / arg0->unk16;
        lbl_1_data_F8 = 1440.0f / arg0->unk18;
    }
    if (omPauseChk() == 0) {
        arg0->unk40 += 1.0f;
        arg0->unk44 += 1.5f;
    }
    if (arg0->unk40 >= 360.0f) {
        arg0->unk40 -= 360.0f;
    }
    if (arg0->unk44 >= 360.0f) {
        arg0->unk44 -= 360.0f;
    }
    var_r28 = arg0->unk4;
    var_r29 = arg0->unkC;
    sp3C.x = 2000.0f;
    sp3C.y = -2000.0f;
    sp44.x = 1000.0f;
    sp44.y = -2500.0f;
    sp2C.x = sp44.x;
    sp2C.y = (sp44.y - sp44.x) / (arg0->unk18 - 1);
    var_f25 = arg0->unk44;
    
    for (var_r27 = 0; var_r27 < arg0->unk18; var_r27++) {
        sp34.x = sp3C.x;
        sp34.y = (sp3C.y - sp3C.x) / (arg0->unk16 - 1);
        var_f26 = arg0->unk40;
        
        for (var_r24 = 0; var_r24 < arg0->unk16; var_r28++, var_r29++, var_r24++) {
            var_r28->x = sp34.x;
            var_r28->z = sp2C.x;
            sp24 = 5.0 * sind(var_f26) + 10.0 * sind(var_f25);
            sp34.x += sp34.y;
            var_f26 += lbl_1_bss_94;
            if (var_f26 >= 360.0f) {
                var_f26 -= 360.0f;
            }
            var_r28->y = sp24 + fn_1_4570(var_r28);
            var_r29->x = var_r29->y = var_r29->z = 0.0f;
        }
        sp2C.x += sp2C.y;
        var_f25 += lbl_1_data_F8;
        if (var_f25 >= 360.0f) {
            var_f25 -= 360.0f;
        }
    }
    var_r30 = arg0->unk1C;
    var_r24 = (arg0->unk16 - 1) * (arg0->unk18 - 1);
    
    for (var_r27 = 0; var_r27 < var_r24; var_r27++, var_r30++) {
        fn_1_C2C8(&arg0->unk4[var_r30->unk0], &arg0->unk4[var_r30->unk2], &arg0->unk4[var_r30->unk4], &var_r30->unk8);
        arg0->unkC[var_r30->unk0].x += var_r30->unk8.x;
        arg0->unkC[var_r30->unk0].y += var_r30->unk8.y;
        arg0->unkC[var_r30->unk0].z += var_r30->unk8.z;
        arg0->unkC[var_r30->unk2].x += var_r30->unk8.x;
        arg0->unkC[var_r30->unk2].y += var_r30->unk8.y;
        arg0->unkC[var_r30->unk2].z += var_r30->unk8.z;
        arg0->unkC[var_r30->unk4].x += var_r30->unk8.x;
        arg0->unkC[var_r30->unk4].y += var_r30->unk8.y;
        arg0->unkC[var_r30->unk4].z += var_r30->unk8.z;
        arg0->unkC[var_r30->unk6].x += var_r30->unk8.x;
        arg0->unkC[var_r30->unk6].y += var_r30->unk8.y;
        arg0->unkC[var_r30->unk6].z += var_r30->unk8.z;
    }
    
    var_r29 = arg0->unkC;
    for (var_r27 = 0; var_r27 < arg0->unk14; var_r27++, var_r29++) {
        var_f20 = sqrtf((var_r29->x * var_r29->x) + (var_r29->y * var_r29->y) + (var_r29->z * var_r29->z));
        var_r29->x /= var_f20;
        var_r29->y /= var_f20;
        var_r29->z /= var_f20;
    }
    var_r28 = arg0->unk4;
    var_r25 = arg0->unk8;
    C_MTXLookAt(spAC, &var_r23->pos, &var_r23->up, &var_r23->target);
    GXGetProjectionv(&sp7C[0][0]);
    GXGetViewportv(&sp4C[0][0]);
    
    for (var_r27 = 0; var_r27 < arg0->unk14; var_r27++, var_r28++, var_r25++) {
        GXProject(var_r28->x, var_r28->y, var_r28->z, spAC, &sp7C[0][0], &sp4C[0][0], &sp28, &sp24, &sp20);
        var_r25->x = 0.0015625f * sp28;
        var_r25->y = 0.0020833f * sp24;
        var_r25->x += 0.05f * arg0->unkC[var_r27].x;
        var_r25->y += 0.05f * arg0->unkC[var_r27].z;
        arg0->unk10[var_r27].r = 0xFF;
        arg0->unk10[var_r27].g = 0xFF;
        arg0->unk10[var_r27].b = 0xFF;
        arg0->unk10[var_r27].a = 0xFF;
    }
    DCFlushRangeNoSync(arg0->unk4, arg0->unk14 * 0xC);
    DCFlushRangeNoSync(arg0->unkC, arg0->unk14 * 0xC);
    DCFlushRangeNoSync(arg0->unk8, arg0->unk14 * 8);
    DCFlushRangeNoSync(arg0->unk10, arg0->unk14 * 4);
    PPCSync();
}

void fn_1_618C(ModelData* arg0, Mtx arg1) {
    Mtx sp64;
    Mtx sp34;
    GXTexObj sp14;
    GXColor spC;
    M427DllMapStruct4* var_r31 = &lbl_1_bss_98;
    AnimData** var_r30 = &lbl_1_bss_158.unk334;
    
    fn_1_558C(var_r31);
    GXLoadPosMtxImm(arg1, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
    GXSetArray(GX_VA_POS, var_r31->unk4, 0xC);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
    GXSetArray(GX_VA_TEX0, var_r31->unk8, 8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGBA8, 0);
    GXSetArray(GX_VA_CLR0, var_r31->unk10, 4);
    GXInitTexObj(&sp14, var_r31->unk30, 0x280, 0x1E0, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&sp14, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
    GXLoadTexObj(&sp14, GX_TEXMAP0);
    GXInitTexObj(&sp14, var_r31->unk28, 0x280, 0x1E0, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&sp14, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
    GXLoadTexObj(&sp14, GX_TEXMAP1);
    HuSprTexLoad(*var_r30, 0, 2, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetNumTevStages(3);
    spC.r = 0;
    spC.g = 0x10;
    spC.b = 0x1E;
    spC.a = 0x4C;
    GXSetTevColor(GX_TEVREG2, spC);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVREG0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVREG0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_TEXC, GX_CC_C0, GX_CC_A2, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVREG1);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVREG1);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C2);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP2);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, 1, 0, GX_ITM_0);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    PSMTXScale(sp64, -0.1f, 0.0f, 1.0f);
    GXSetIndTexMtx(GX_ITM_0, (f32(*)[3])(sp64), 0);
    GXSetNumTexGens(2);
    if (omPauseChk() == 0) {
        var_r31->unk38 += 0.001f;
        var_r31->unk3C += 0.0005f;
    }
    PSMTXRotRad(sp64, 0x58, 1.5707964f);
    PSMTXScale(sp34, 0.001f, 0.001f, 0.001f);
    PSMTXConcat(sp64, sp34, sp64);
    mtxTransCat(sp64, var_r31->unk38, var_r31->unk3C, 0.0f);
    GXLoadTexMtxImm(sp64, 0x1E, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_POS, 0x1E, 0, 0x7D);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(0);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXCallDisplayList(var_r31->unk20, var_r31->unk24);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
}
