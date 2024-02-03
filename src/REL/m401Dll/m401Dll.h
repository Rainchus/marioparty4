#include "common.h"
#include "REL/executor.h"
#include <dolphin/mtx.h>
#include "game/objsub.h"

// global data //
typedef struct unkStruct18FC10 {
    s16  unk_00;
    char unk_02[8];
} unkStruct18FC10;
typedef struct unkSubstructBSS114 {
    s16 unk_00[4];
    s16 unk_08[4][3];
    char unk_20[0x30];
    s16 unk_50[4][3];
    s16 unk_68[4][3];
    s16 unk_80[4];
    s16 unk_88[4];
    f32 unk_90[4];
    f32 unk_A0[4];
    char unk_B0[0x10];
    f32 unk_C0[4];
    f32 unk_D0[4];
    f32 unk_E0[4];
    f32 unk_F0[4];
    f32 unk_100[4];
    f32 unk_110[4];
    f32 unk_120[4];
    s16 unk_130[4];
    s16 unk_138[4];
    s16 unk_140[4];
} unkSubstructBSS114;
typedef struct unkStructBSS114 {
    char unk_00[4];
    s32 unk_04;
    char unk_08[0xC];
    void *unk_14;
    Vec3f unk_18;
    char unk_24[0x1C];
    unkSubstructBSS114 *unk_40;
    char unk_44[0x8];
    s32 unk_4C;
    u32 unk_50;
    char unk_54[0x8];
    unkSubstructBSS114 *unk_5C;
} unkStructBSS114;
typedef struct unkStruct18BFC0 {
    char unk_00[0x14];
    Vec3f  unk_14;
} unkStruct18BFC0;
typedef struct unkStruct18C8FC {
    s16  unk_00;
    char unk_02[0x42];
} unkStruct18C8FC;

extern unkStruct18FC10 lbl_8018FC10[];
extern unkStruct18BFC0 lbl_8018BFC0;
extern unkStruct18C8FC lbl_8018C8FC[];
extern s16 lbl_801D3CC2;

extern void Hu3DModelAttrSet(s16, s32);
extern void Hu3DModelAttrReset(s16, s32);
extern omObjData* Hu3DModelObjPtrGet(s16, s32);
extern void Hu3DCameraPosSetV(s32, Vec3f*, Vec3f*, Vec3f*);
extern s16 Hu3DGLightCreateV(Vec3f*, Vec3f*, s32*);
extern void Hu3DGLightInfinitytSet(s16);
extern void Hu3DReflectNoSet(s16);
extern void Hu3DShadowCreate(f32, f32, f32);
extern void Hu3DShadowPosSet(Vec3f*, Vec3f*, Vec3f*);
extern void Hu3DShadowTPLvlSet(f32);
extern void Hu3DFogSet(f32, f32, u8, u8, u8);
extern void omOvlReturnEx(s16, s16);
extern omObjData* omAddObjEx(void*, s16, s16, s16, s16, void*);
extern void omDelObjEx(s32*, omObjData*);
extern void omMakeGroupEx(omObjData*, s16, s16);
extern omObjData* omGetGroupMemberListEx(omObjData*, s16);
extern void omSetTra(omObjData*, f32, f32, f32);
extern void omSetRot(omObjData*, f32, f32, f32);
extern void omSetSca(omObjData*, f32, f32, f32);
extern u8 frand(void);
extern s32 HuAudFXPlay(s32);
extern void HuAudFXStop(s32);
extern s32 HuAudFXEmiterPlay(s32, Vec3f*);
extern void HuAudFXListnerKill(void);
extern void HuAudSeqFadeOut(s32, s32);
extern s16 MGSeqCreate(s32, ...);
extern s16 espEntry(s32, s16, s16);
extern void espDispOn(s16);
extern void espDispOff(s16);
extern void espAttrSet(s16, s16);
extern void espPosSet(s16, f32, f32);
extern void espTPLvlSet(s16, f32);
extern void espColorSet(s16, s8, s8, s8);
extern void espBankSet(s16, s16);
extern void espDrawNoSet(s16, s16);
extern void WipeCreate(s16, s16, s16);
extern u8 WipeStatGet(void);
extern f32 PSVECNormalize(Vec3f*, Vec3f*);

// local data //
typedef struct unkStructBSS54 {
    Vec3f unk_00;
} unkStructBSS54;
typedef struct unkStructBSS100 {
    void *unk_00;
    void *unk_04;
} unkStructBSS100;

extern f32 lbl_2_data_0 = -7.1875f;
extern s16 lbl_2_data_4[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
extern Vec3f lbl_2_data_14 = { 1500.0f, 2500.0f, 1500.0f };
extern Vec3f lbl_2_data_20 = { 0.0f, -1.0f, 0.0f };
extern s32 lbl_2_data_2C = -1;
extern Vec3f lbl_2_data_30 = { 0.0f, 2500.0f, 0.0f };
extern Vec3f lbl_2_data_3C = { 0.0f, 1.0f, -1.0f };
extern Vec3f lbl_2_data_48 = { 0.0f, 0.0f, 0.0f };
extern char lbl_2_data_6F[] = "winnercnt:%d";
extern s32 lbl_2_data_80[8] = { 0x610000, 0x610001, 0x610002, 0x610003, 0x610004, 0x610005, 0x610006, 0x610007 };
extern s32 lbl_2_data_124[5];

extern s32 lbl_2_bss_8;
extern f32 lbl_2_bss_10;
extern unkStruct18FC10* lbl_2_bss_1C;
extern Vec3f lbl_2_bss_2C;
extern Vec3f lbl_2_bss_38;
extern Vec3f lbl_2_bss_44;
extern f32 lbl_2_bss_50;
extern unkStructBSS54 lbl_2_bss_54;
extern Vec3f lbl_2_bss_60;
extern Vec3f lbl_2_bss_6C;
extern f32 lbl_2_bss_84;
extern f32 lbl_2_bss_88;
extern s32 lbl_2_bss_90[4];
extern s32 lbl_2_bss_A4;
extern s16 lbl_2_bss_A8;
extern s16 lbl_2_bss_AA[];
extern s16 lbl_2_bss_B2[];
extern s16 lbl_2_bss_BA;
extern s16 lbl_2_bss_BE;
extern s16 lbl_2_bss_C0;
extern void* lbl_2_bss_C8;
extern s32 lbl_2_bss_CC;
extern s32 lbl_2_bss_D0;
extern s32 lbl_2_bss_D4;
extern s32 lbl_2_bss_D8;
extern unkStructBSS114* lbl_2_bss_E0;
extern s32 lbl_2_bss_F4;
extern omObjData* lbl_2_bss_F8;
extern omObjData* lbl_2_bss_FC;
extern unkStructBSS100 lbl_2_bss_100;
extern omObjData* lbl_2_bss_108;
extern omObjData* lbl_2_bss_10C;
extern omObjData* lbl_2_bss_110;
extern omObjData* lbl_2_bss_114;
extern unkStructBSS114** lbl_2_bss_118;
extern s32 lbl_2_bss_11C;
extern s16 lbl_2_bss_120;
extern f32 lbl_2_bss_124;
extern f32 lbl_2_bss_128;
extern f32 lbl_2_bss_12C;

void M401ObjectSetup(void);
void fn_2_70C(unkStructBSS114*);
void fn_2_A10(void);
void M401SetFogAndBG(void);
void M401SetSpriteDisp(s16);
void fn_2_C1C(unkStructBSS114*);
void fn_2_11D0(unkStructBSS114*);
void fn_2_15C4(s16);
void fn_2_169C(s16);
void fn_2_1858(s16, s16);
void fn_2_1A38(unkStructBSS114*);
void fn_2_1B80(unkStructBSS114*);
void fn_2_1CF0(unkStructBSS114*);
void fn_2_1DE8(unkStructBSS114*);
void fn_2_20B0(unkStructBSS114*);
void fn_2_2FA4(void*);
void fn_2_3B24(void*);
void fn_2_48A0(void*);
void fn_2_7CB4(void*);
void fn_2_8E74(void*);
void fn_2_95E4(void*);
void fn_2_91AC(void*, Vec3f*);
void fn_2_9D00(void*);
void fn_2_BD90(void*);
void fn_2_C6DC(void*);
void fn_2_C130(void);
void fn_2_D088(void*);
void fn_2_DBCC(s16);
void fn_2_E6BC(s32, f32, f32, f32, f32, f32);
unkStructBSS114* fn_2_FC40(s32, Vec3f*, Vec3f*, Vec3f*);
void fn_2_10240(Vec3f*, Vec3f*);
void fn_2_1041C(void);
s32 fn_2_14640(void*);
void fn_2_10710(void);
s16 fn_2_1079C(void);
s32 fn_2_10A88(Vec3f*, s16);
