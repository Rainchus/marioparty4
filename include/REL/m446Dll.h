#include "dolphin/types.h"

#include "game/process.h"
#include "game/object.h"

typedef struct _unkSubStruct {
    s32 unk0;
    char unk4[0x20];
    s32 unk24;
    char unk28[0x3C];
    u8 unk64;
    u8 unk65;
    u8 unk66;
    s32 unk68;
    char unk6C[0x4];
} unkSubStruct;

typedef struct _unkSubStruct2 {
    s32 unk0;
    s32 unk4;
    char unk8[0x68];
    s32 unk70;
    s32 unk74;
    s32 unk78;
} unkSubStruct2;

typedef struct _unkStruct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    char unk8[0x4];
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    unkSubStruct *unk20;
    s32 unk24;
    s32 unk28;
    unkSubStruct *unk2C[2];
    unkSubStruct2 *unk34;
    s32 unk38[23];
    s32 unk94;
    Process *unk98;
} unkStruct;

typedef struct _unkStruct2 {
    s32 *unk0;
    s32 unk4;
    s32 unk8;
} unkStruct2;

typedef struct _unkStruct3 {
    struct _unkStruct4 *unk0;
    struct _unkStruct3 *unk4;
    struct _unkStruct3 *unk8;
} unkStruct3;

typedef struct _unkStruct4 {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    u8 unk9;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    Vec unk10;
    Vec unk1C;
    Vec unk28;
    Vec unk34;
    Vec unk40;
    Vec unk4C;
    f32 unk58;
    f32 unk5C;
    f32 unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    f32 unk80;
    f32 unk84;
    f32 unk88;
    f32 unk8C;
    f32 unk90;
    f32 unk94;
} unkStruct4;

typedef void (*m446Func1)(unkStruct *);
typedef void (*m446Func4)(unkStruct4 *);

// bss
extern unkStruct3* lbl_1_bss_18;
extern s32 lbl_1_bss_14;
extern s32 lbl_1_bss_10;
extern Process* lbl_1_bss_C;
extern omObjData *lbl_1_bss_8;
extern s32 lbl_1_bss_4;
extern unkStruct* lbl_1_bss_0;

// data
extern Vec lbl_1_data_0;
extern Vec lbl_1_data_C;
extern f32 lbl_1_data_18;
extern Vec lbl_1_data_1C;
extern Vec lbl_1_data_28;
extern f32 lbl_1_data_34;
extern Vec lbl_1_data_38[2];
extern Vec lbl_1_data_50[2];
extern f32 lbl_1_data_68[2];
extern m446Func1 lbl_1_data_A0[5];
extern m446Func4 lbl_1_data_150[3];

// prototypes
extern void ModuleProlog(void);
extern void fn_1_13C(omObjData*);
extern unkStruct* m446FlowCreate(void);
extern void fn_1_3FC(unkStruct*);
extern void fn_1_4B4(unkStruct*);
extern void fn_1_53C(unkStruct*);
extern void fn_1_958(unkStruct*);
extern void fn_1_B78(unkStruct*);
extern void fn_1_C0C(unkStruct*);
extern void fn_1_CA0(unkStruct*);
extern s32 fn_1_17FC(unkStruct*);
extern void fn_1_183C(unkStruct*);
extern void fn_1_1874(unkStruct*);
extern void fn_1_18B0(unkStruct*);
extern void fn_1_19D4(void);
extern unkStruct2* fn_1_1C64(s32);
extern void fn_1_1CF8(unkStruct2*);
extern s32 fn_1_1D30(unkStruct2*, s32);
extern s32 fn_1_1D6C(unkStruct2*, s32*);
extern s32 fn_1_1DA8(unkStruct2*, s32*);
extern BOOL fn_1_1DDC(unkStruct2*);
extern s32 fn_1_1DEC(unkStruct2*);
extern unkStruct3* fn_1_1DF4(unkStruct4*);
extern void fn_1_1E5C(unkStruct3*);
extern void fn_1_1E84(unkStruct3**);
extern void fn_1_1EC8(unkStruct3*, unkStruct3*);
extern void fn_1_1F04(unkStruct3*);
extern void fn_1_1F38(u8*, u8*, s32);
extern void fn_1_1F84(u8*, s8, s32);
extern void fn_1_1FC0(u8*, s32);
extern s32 fn_1_1FFC(s8*, s8*, s32);
extern s32 fn_1_2064(void);
extern void fn_1_207C(void);
extern void fn_1_20D4(void);
extern unkStruct4* fn_1_240C(s32);
extern void fn_1_2688(unkStruct4*);
extern void fn_1_272C(unkStruct4*);
extern void fn_1_2794(unkStruct4*);
extern void fn_1_27FC(unkStruct4*, Vec*, s32);
extern void fn_1_2890(unkStruct4*, Vec*, s32, s32);
extern void fn_1_2928(unkStruct4*, Vec*, s32);
extern void fn_1_29B4(unkStruct4*, s32, f32);
extern void fn_1_2A1C(unkStruct4*);
extern void fn_1_2A58(unkStruct4*);
extern void fn_1_2A94(unkStruct4*);
extern void fn_1_2AA8(unkStruct4*);
extern void fn_1_2D94(unkStruct4*);
extern void fn_1_2DA8(unkStruct4*);
extern void fn_1_2EC0(unkStruct4*, s32);
extern void fn_1_2F64(unkStruct4*);