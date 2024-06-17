#include "dolphin/types.h"
#include "game/hsfman.h"

#include "game/object.h"
extern s32 rand8(void);

////// TYPES //////
typedef struct _unkStruct {
    f32 zoom;
    Vec center;
    Vec rot;
} unkStruct;

typedef struct _unkStruct2 {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s32 unkC;
    char unk10[0xC];
    s16 unk1C;
    char unk20[0x4];
    f32 unk24;
    char unk28[0x4];
    s16 unk2C;
    s16 unk2E;
    f32 unk30;
} unkStruct2;

typedef struct _unkStruct3 {
    char unk0[0x34];
    f32 unk34;
    char unk38[0x8];
    f32 unk40;
} unkStruct3;

typedef struct _unkStruct4 {
    Vec unk0;
    char unkC[0xC];
    f32 unk18;
    f32 unk1C;
    char unk20[0x4];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    s16 unk34;
    s16 unk36;
    char unk38[0x10];
    Vec unk48;
    Vec unk54;
    s16 unk60;
    s8 unk62;
} unkStruct4; // sizeof 0x64

typedef struct _unkStruct5 { // could be unkStruct3
    s16 unk0;
    s16 unk2;
    char unk4[0x10];
    s16 unk14;
    unkStruct4 *unk18;
    char unk1C[0x8];
    GXColor* unk24; // ?
} unkStruct5;

typedef void (*m440Func5)(omObjData*, unkStruct5*, Mtx*);
typedef void (*m440Func6)(struct _unkStruct6*);

typedef struct _unkStruct8 {
    s16 unk0[3][4];
    s16 unk18[3];
    s16 unk1E;
    char unk20[0x48];
    f32 unk68;
    char unk6C[0x10];
    Vec unk7C;
    Vec unk88;
    Vec unk94;
    Vec unkA0;
    Vec unkAC;
    Vec unkB8;
    Vec unkC4;
} unkStruct8;

typedef struct _unkStruct7 {
    GXColor unk0;
    Vec unk4;
} unkStruct7;

typedef struct _unkStruct9 {
    f32 unk0;
    f32 unk4;
} unkStruct9;

typedef struct _unkStruct6 {
    s16 unk0;
    u16 unk2;
    s16 unk4;
    s16 unk6;
    u32 unk8;
    Vec* unkC;
    Vec* unk10;
    Vec* unk14;
    Vec* unk18;
    unkStruct9* unk1C;
    s32 unk20;
    unkStruct8* unk24;
    HsfMaterial* unk28;
    HsfAttribute* unk2C;
    void* unk30;
    u32 unk34;
    m440Func6 unk38;
    s16 unk3C;
    s16 unk3E;
} unkStruct6; // sizeof 0x40


////// BSS //////
// object.c
extern omObjData* lbl_1_bss_C0[4];
// main.c
extern omObjData* lbl_1_bss_6C;
extern omObjData* lbl_1_bss_68;
extern unkStruct6* lbl_1_bss_64;
extern s16 lbl_1_bss_60;
extern s16 lbl_1_bss_10[10];
extern s16 lbl_1_bss_E;
extern u8 lbl_1_bss_C;
extern u8 lbl_1_bss_B;
extern u8 lbl_1_bss_A;
extern s16 lbl_1_bss_8;
extern s16 lbl_1_bss_6;
extern s16 lbl_1_bss_4;
extern s8 lbl_1_bss_2;
extern s8 lbl_1_bss_1;
extern s8 lbl_1_bss_0;

////// DATA //////
// main.c
extern f32 lbl_1_data_0[5];
extern s16 lbl_1_data_14[6];
extern Vec lbl_1_data_2C;
extern Vec lbl_1_data_38;
extern unkStruct7 lbl_1_data_44;
extern Vec lbl_1_data_54;
extern Vec lbl_1_data_60;
extern Vec lbl_1_data_6C;
extern unkStruct lbl_1_data_78[3];
extern s16 lbl_1_data_E4[2];
extern s16 lbl_1_data_E8[2];
extern s16 lbl_1_data_EC[2];
extern s16 lbl_1_data_F0[2];
extern s32 lbl_1_data_F4[4];
extern s16 lbl_1_data_104[2];
extern s16 lbl_1_data_108[2];
// object.c
extern s16 lbl_1_data_1D8;

////// FUNCTIONS //////
// main.c
extern void ModuleProlog(void);
extern void fn_1_3C4(omObjData* object);
extern void fn_1_434(omObjData* object);
extern s32 fn_1_4A4(void);
extern s32 fn_1_6C8(void);
extern void fn_1_8F0(omObjData* object);
extern void fn_1_AE0(omObjData* object);
extern s32 fn_1_E14(omObjData* object);
extern s32 fn_1_1138(omObjData* object);
extern void fn_1_16D8(void);
extern void fn_1_1708(void);
extern void fn_1_1768(void);
extern s16 fn_1_17CC(void);
extern s16 fn_1_17F4(void);
extern void fn_1_181C(void);
extern u8 fn_1_1890(void);
extern void fn_1_18E0(void);
extern s32 fn_1_1954(void);
extern void fn_1_19B0(void);
extern void fn_1_1CAC(void);
extern void fn_1_2240(omObjData* object, unkStruct5*, Mtx*);
extern u16 fn_1_23E4(u16);
extern void fn_1_2428(u16, u16);
extern void fn_1_2470(omObjData* object);
extern void fn_1_2A74(omObjData* object);
extern void fn_1_2AB4(omObjData* object);
extern void fn_1_2B04(omObjData* object);
extern void fn_1_2CA8(omObjData* object);
extern void fn_1_2D28(omObjData* object);
extern void fn_1_33D4(omObjData* object);
extern void fn_1_3DD8(omObjData* object);
extern void fn_1_4558(omObjData* object);
extern void fn_1_45BC(omObjData* object);
extern void fn_1_4660(omObjData* object);
extern void fn_1_46E0(omObjData* object);
extern void fn_1_4A20(omObjData* object);
extern void fn_1_4B44(omObjData* object);
extern void fn_1_4E00(s16, f32);
extern s16 fn_1_4E2C(void);
extern s16 fn_1_4E54(s16);
extern u16 fn_1_4EA8(u16);
extern void fn_1_4EEC(u16, u16);
extern void fn_1_4F34(unkStruct6*);
extern void fn_1_5010(unkStruct6*, Vec*, f32);
extern void fn_1_57B4(unkStruct6*);
extern void fn_1_5C2C(s16, HsfObject*, unkStruct6*, u16);
// ...
extern f32 fn_1_93C0(f32, f32, f32);