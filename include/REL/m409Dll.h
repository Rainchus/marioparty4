#include "dolphin.h"

#include "game/object.h"
#include "game/animdata.h"
#include "game/hsfanim.h"
extern s32 rand8(void);

// types
typedef void (*m409Func6)(ModelData*, struct _unkStruct6*, Mtx);
typedef void (*m409PlayerFunc8)(struct _unkStruct8*);

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
} unkStruct5; // sizeof 0x50

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
} unkStruct6; // sizeof 0x68

typedef struct _unkStruct7 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    char unk7[0x3];
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    char unk12[0x1];
    s8 unk13;
    s8 unk14;
    char unk15[0x3];
    s32 unk18;
    s16 unk1C;
    char unk1E[0x6];
    Vec unk24;
    Vec unk30;
    Vec unk3C;
    Vec unk48;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58;
    u8 unk59;
    u8 unk5A[3][2];
    u8 unk60;
    u8 unk61;
    u8 unk62;
    u8 unk63;
    u8 unk64;
    char unk65[0x3];
    Vec unk68;
} unkStruct7; // sizeof 0x74

typedef struct _unkStruct8Sub {
    Vec unk0;
    Vec unkC;
    Vec unk18;
    char unk24[0xC];
    u8 unk30;
    u8 unk31;
    u8 unk32;
    u32 unk34;
    s16 unk38;
    void* unk3C;
    void* unk40;
    void* unk44;
    Vec* unk48;
    GXColor unk4C;
    GXColor unk50;
    struct _unkStruct12* unk54;
    Vec unk58;
    Vec unk64;
    union {
        s16 unk70[0x10];
        struct {
            s16 unk70s;
            f32 unk74;
            f32 unk78;
            f32 unk7C;
        };
    };
} unkStruct8Sub; // sizeof 0x90

typedef struct _unkStruct8 {
    s16 unk0;
    s16 unk2;
    u8 unk4;
    s16 unk6;
    u32 unk8;
    Vec unkC;
    Vec unk18;
    Vec unk24;
    m409PlayerFunc8 unk30;
    s16* unk34;
    char unk38[0x4];
    unkStruct8Sub* unk3C;
    char unk40[0x8];
    Vec unk48;
    Vec unk54;
    s16 unk60[0x20];
} unkStruct8; // sizeof 0xA0

typedef struct _unkStruct9Sub {
    AnimData* unk0;
    s16 unk4;
    s16 unk6;
    u32 unk8;
    Vec unkC;
    Mtx unk18;
    GXColor unk48;
    u8 unk4C;
    s16 unk4E;
    s16 unk50;
    f32 unk54;
    f32 unk58;
    f32 unk5C;
    f32 unk60;
} unkStruct9Sub; // sizeof 0x64

typedef struct _unkStruct9 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    unkStruct9Sub* unkC;
    unkStruct8* unk10;
} unkStruct9; // sizeof 0x14

typedef struct _unkStruct10 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    char unk5[0x3];
    f32 unk8;
    Vec unkC;
    Vec unk18;
    Vec unk24;
    Vec unk30;
    Vec unk3C;
    s8 unk48;
    char unk49[0x3];
    f32 unk4C;
} unkStruct10; // sizeof 0x50

typedef struct unkStruct11 {
    Vec unk0;
    Vec unkC;
    Vec unk18;
    Vec unk24;
} unkStruct11; // sizeof 0x30

typedef struct _unkStruct12 {
    s8 unk0;
    s8 unk1;
    s16 unk2;
    HsfVector2f* unk4;
    u8 unk8;
    s16 unkA;
    f32 unkC;
    f32 unk10;
} unkStruct12;

// bss
// player.c
extern omObjData* lbl_1_bss_3A0[4];
extern omObjData* lbl_1_bss_39C;
extern s32 lbl_1_bss_38C[4];
extern unkStruct10 lbl_1_bss_10C[8];
extern s16 lbl_1_bss_108;
extern s16 lbl_1_bss_106;
extern s16 lbl_1_bss_104;
extern unkStruct9 lbl_1_bss_F0;
// main.c
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
// main.c
extern Vec lbl_1_data_0;
extern Vec lbl_1_data_C;
extern unkStruct2 lbl_1_data_18;
extern Vec lbl_1_data_28;
extern Vec lbl_1_data_34;
extern Vec lbl_1_data_40;
extern unkStruct lbl_1_data_4C[4];
extern u32 lbl_1_data_BC;
extern s32 lbl_1_data_C0;
// player.c
extern u32 lbl_1_data_138; // unk
extern s32 lbl_1_data_13C[7];
extern GXColor lbl_1_data_158[8];
extern HsfVector2f lbl_1_data_178[4];
extern GXColor lbl_1_data_198[8];
extern u32 lbl_1_data_1EC;

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
extern void fn_1_23EC(s16);
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
extern void fn_1_5408(ModelData*, unkStruct6*, Mtx);
extern void fn_1_55E0(ModelData*, unkStruct6*, Mtx);
extern void fn_1_57DC(ModelData*, unkStruct6*, Mtx);
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
extern void fn_1_6928(omObjData*);
extern void fn_1_7344(omObjData*);
extern void fn_1_7FE8(omObjData*);
extern void fn_1_8838(unkStruct8*);
extern s8 fn_1_8D08(u8);
extern void fn_1_8D6C(unkStruct8*);
extern void fn_1_91C0(omObjData*);
extern void fn_1_962C(omObjData*);
extern s32 fn_1_A584(unkStruct10*);
extern s8 fn_1_A9C0(Vec*, f32*);
extern s32 fn_1_ABB4(void);
extern void fn_1_AC08(s32*, s32);
extern f32 fn_1_AD40(f32, f32, f32);
extern f32 fn_1_AE94(f32, f32, f32, f32);
extern void fn_1_AF0C(f32*, f32*, f32*, f32*, f32);
extern f32 fn_1_B028(f32, f32, f32, f32);
extern void fn_1_B0A0(f32*, f32*, f32*, f32*, f32);
extern f32 fn_1_B378(Vec*);
extern f32 fn_1_B6A4(Vec*, Vec*, Vec*);
extern f32 fn_1_B9E0(Vec*, Vec*, Vec*, Vec*, Vec*);
extern f32 fn_1_BF38(s16);
// cursor.c
extern void fn_1_BF88(s16, s16);
extern void fn_1_C0C0(void);
extern void fn_1_C164(unkStruct8*);
extern void fn_1_CB98(ModelData* model, Mtx matrix);
extern unkStruct8* fn_1_CCB0(s16 idx);
extern unkStruct8Sub* fn_1_CCCC(s16, s16);
extern void fn_1_CCF8(unkStruct11**, s16, f32, f32);
extern void fn_1_CE7C(Vec**, s16, Vec*);
extern void fn_1_CF1C(GXColor**, s16, GXColor*);
extern void fn_1_CFC4(Vec**, s16, Vec*);
extern void fn_1_D050(HsfVector2f**, s16, HsfVector2f*);
extern void fn_1_D0E8(unkStruct8Sub*);
extern void fn_1_D430(unkStruct8*);
extern s16 fn_1_DA48(u8, u8);
extern void fn_1_DDB8(s16);
extern void fn_1_DEF4(s16, s16, u8);
extern s16 fn_1_DF20(u32, s16, s16);
extern void fn_1_E228(s16);
extern s32 fn_1_E2A8(s16, u8, u32, s16, s16);
extern s32 fn_1_E7C8(s16, u8, u32);
extern void fn_1_E818(s16, f32, f32, f32);
extern void fn_1_E85C(s16, s16, f32, f32, f32);
extern void fn_1_E8CC(s16, f32, f32, f32);
extern void fn_1_E940(s16, f32, f32, f32);
extern void fn_1_E99C(s16, s16, f32, f32, f32);
extern void fn_1_E940(s16, f32, f32, f32);
extern void fn_1_EA24(s16, f32, f32, f32);
extern void fn_1_EAB0(s16, f32, f32, f32);
extern void fn_1_EAF4(s16, s16, f32, f32, f32);
extern void fn_1_EB64(s16, f32, f32, f32);
extern void fn_1_EBD8(s16, f32, f32, f32);
extern void fn_1_EC1C(s16, s16, f32, f32, f32);
extern void fn_1_EC8C(s16, f32, f32, f32);
extern void fn_1_ED00(s16, s32);
extern void fn_1_ED44(s16, s16, s32);
extern void fn_1_EDB4(s16, s32);
extern void fn_1_EE24(s16, u32);
extern void fn_1_EE68(s16, s16, u32);
extern void fn_1_EED8(s16, u32);
extern s32 fn_1_EF48(s16, s32);
extern s32 fn_1_EFA4(s16, s16, s32);
extern void fn_1_F024(s16, s16, u8, u8, u8, u8);
extern void fn_1_F098(s16, u8, u8, u8, u8);
extern void fn_1_F110(s16, s16, u8);
extern void fn_1_F17C(s16, s16, u8, u8);
extern void fn_1_F1F4(s16, u8);
extern void fn_1_F28C(s16, s16, f32);
extern void fn_1_F2F8(s16, s16, u8, f32);
extern void fn_1_F370(s16, f32);
extern void fn_1_F408(s16, s16, u8);
extern void fn_1_F478(s16, s16, u8, u8);
extern void fn_1_F4F0(s16, u8);