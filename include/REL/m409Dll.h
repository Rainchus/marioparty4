#include "dolphin.h"

#include "game/object.h"
#include "game/animdata.h"
#include "game/hsfanim.h"
extern s32 rand8(void);

// types
typedef void (*m409Func6)(ModelData*, struct _unkStruct6*, Mtx);

typedef struct _unkStruct {
    f32 zoom;
    Vec center;
    Vec rot;
} unkStruct;

typedef struct _unkStruct2 {
    GXColor unk0;
    Vec unk4;
} unkStruct2; // sizeof 0x10

typedef struct _unkStruct3 {
    s8 unk0;
    s8 unk1;
    s16 unk2;
    struct _unkStruct4* unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    f32 unk14;
} unkStruct3;

typedef struct _unkStruct4 {
    union {
        u16 unk0;
        u8 unk0b;
    };
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    f32 unk10;
    s16 unk14;
    s16 unk16;
    f32 unk18;
    f32 unk1C;
    struct _unkStruct4* unk20;
} unkStruct4; // sizeof 0x24

typedef struct _unkStruct5 {
    Vec unk0;
    Vec unkC;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    f32 unk30;
    Vec unk34;
    Vec unk40;
    s16 unk4C;
    s8 unk4E;
} unkStruct5;

typedef struct _unkStruct6 {
    s16 unk0;
    s16 unk2;
    u32 unk4;
    u8 unk8;
    m409Func6 unkC;
    AnimData* unk10;
    s16 unk14;
    unkStruct5* unk18;
    Vec* unk1C;
    HsfVector2f* unk20;
    GXColor* unk24;
    void* unk28;
    Vec unk2C;
    Vec unk38;
    Vec unk44;
    Vec unk50;
    HsfVector2f* unk5C;
    f32 unk60;
    f32 unk64;
} unkStruct6;

// bss
extern Process* lbl_1_bss_E8;
extern s16 lbl_1_bss_E4;
extern omObjData* lbl_1_bss_E0;
extern omObjData* lbl_1_bss_DC;
extern Vec lbl_1_bss_D0;
extern unkStruct4 lbl_1_bss_40[4];
extern s32 lbl_1_bss_3C;
extern unkStruct3 lbl_1_bss_24;
extern s8 lbl_1_bss_21;
extern u8 lbl_1_bss_20;
extern f32 lbl_1_bss_1C;
extern f32 lbl_1_bss_18;
extern s16 lbl_1_bss_16;
extern s8 lbl_1_bss_14;
extern f32 lbl_1_bss_10;
extern f32 lbl_1_bss_C;
extern s8 lbl_1_bss_A;
extern s16 lbl_1_bss_8;
extern s8 lbl_1_bss_6;
extern s16 lbl_1_bss_4;
extern s16 lbl_1_bss_2;
extern s8 lbl_1_bss_0;

// data
extern Vec lbl_1_data_0;
extern Vec lbl_1_data_C;
extern unkStruct2 lbl_1_data_18;
extern Vec lbl_1_data_28;
extern Vec lbl_1_data_34;
extern Vec lbl_1_data_40;
extern unkStruct lbl_1_data_4C[4];
extern u32 lbl_1_data_BC;
extern s32 lbl_1_data_C0;

// prototypes
extern void ModuleProlog(void);
extern void fn_1_434(omObjData* object);
extern void fn_1_4DC(omObjData* object);
extern s8 fn_1_524(void);
extern s8 fn_1_B80(void);
extern void fn_1_DDC(omObjData* object);
extern void fn_1_F70(omObjData* object);
extern s8 fn_1_10E8(omObjData* object);
extern s8 fn_1_1B74(omObjData* object);
extern void fn_1_2098(omObjData* object);
extern void fn_1_2414(u16, u16);
extern u16 fn_1_2454(u16);
extern void fn_1_2484(omObjData* object);
extern void fn_1_2DCC(omObjData* object);
extern void fn_1_3840(void);
extern void fn_1_3988(unkStruct4*, s16, s16);
extern s32 fn_1_3AD8(s32, f32, f32, f32, f32, f32, f32);
extern void fn_1_40A4(Mtx, Mtx);
extern f32 fn_1_4120(f32, f32, f32, f32);
extern void fn_1_417C(void);
extern void fn_1_44F0(s16, f32, f32, f32, s8, s16);
extern void fn_1_4FFC(s16, f32, f32, f32, s16);
extern void fn_1_5408(ModelData*, struct _unkStruct6*, Mtx);
extern void fn_1_55E0(ModelData*, struct _unkStruct6*, Mtx);
extern void fn_1_57DC(ModelData*, struct _unkStruct6*, Mtx);
extern unkStruct5* fn_1_58E0(s16, Vec*, Vec*, f32, GXColor*);
extern s16 fn_1_5A18(AnimData*, s16, f32, s16, s16);
extern void fn_1_5F5C(s16);
extern void fn_1_5FBC(s16, m409Func6);
extern void fn_1_5FF4(s16, u8);
extern void fn_1_602C(ModelData*, Mtx);
extern void fn_1_6608(HsfVector2f*, s16, s16, f32, f32);
extern void fn_1_66D4(HsfVector2f*, HsfVector2f*, s16, f32, f32);
extern void fn_1_6778(Vec*, Vec*, Vec*, s16);
// player.c
extern void fn_1_67E0(Process*);
extern void fn_1_6900(void);