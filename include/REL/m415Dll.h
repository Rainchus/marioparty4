#include "dolphin.h"

#include "game/hsfman.h"
#include "game/object.h"

extern u8 texMtxTbl[];

#define FABS(x) ((x < 0.0f) ? -(x) : (x))

// types
typedef struct _unkStruct {
    s16 unk0[3];
    s16 unk6;
    s16 unk8;
} unkStruct; // sizeof 0xC

typedef struct _unkStruct2 {
    char unk[0xE];
    s8 unkE;
} unkStruct2;

typedef struct _unkStruct3 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    char unk8[0x2];
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    Vec unk2C;
    Vec unk38;
    Vec unk44;
    Vec unk50;
    u8 unk5C;
    u8 unk5D;
    union {
        s32* unk60;
        struct {
            s16 unk60s;
            s16 unk62s;
        };
    };
    s16 unk64;
    s16 unk66;
    s16 unk68;
    Vec unk6C;
} unkStruct3;

typedef struct _unkStruct4 {
    u8 unk0;
    Vec unk4;
    Vec unk10;
    Vec unk1C;
    Vec unk28;
    Vec unk34;
    Vec unk40;
    Vec unk4C;
    Vec unk58;
    Vec unk64[3];
    Vec unk88[3];
    Vec unkAC[3];
    Vec unkD0[3];
    f32 unkF4[3];
    f32 unk100[3];
    f32 unk10C[3];
    f32 unk118[3];
    f32 unk124[3];
    f32 unk130;
    f32 unk134;
    f32 unk138;
    f32 unk13C;
    f32 unk140;
    f32 unk144;
    f32 unk148;
} unkStruct4;

typedef struct _unkSubStruct4 {
    s8 unk0;
    s8 unk1;
    char unk2[0x2];
    HsfVector2f unk4[4];
    u8 unk24;
    char unk25[0x3];
    f32 unk28;
    f32 unk2C;
} unkSubStruct4;

// taken from m438
typedef struct _unkSubStruct {
    Vec unk0;
    Vec unkC;
    Vec unk18;
    char unk24[0xC];
    u8 unk30;
    u8 unk31;
    u8 unk32;
    u8 unk33;
    u32 unk34;
    s16 unk38;
    void* unk3C;
    Vec* unk40;
    GXColor* unk44;
    Vec* unk48;
    GXColor unk4C;
    GXColor unk50;
    unkSubStruct4* unk54;
    char unk58[0x4];
    s8 unk5C;
    char unk5D[0xB];
    Vec unk68;
    char unk74[0x20];
} unkSubStruct; /* size = 0x94 */

typedef void (*unkSubStruct2Func)(struct _unkSubStruct2*);

typedef struct _unkSubStruct2 {
    s16 unk0;
    s16 unk2;
    u8 unk4;
    u32 unk8;
    Vec unkC;
    Vec unk18;
    Vec unk24;
    unkSubStruct2Func unk30;
    s16* unk34;
    char unk38[4];
    unkSubStruct *unk3C;
    char unk40[0x20];
    u8 unk60;
    char unk61[0x1A];
    s16 unk7C;
    s16 unk7E;
    float unk80;
    float unk84;
    float unk88;
    float unk8C;
    float unk90;
    char unk94[0x28];
} unkSubStruct2; /* size = 0xBC */

typedef struct _unkSubStruct3 {
    AnimData* unk0;
    s16 unk4;
    s16 unk6;
    s32 unk8;
    Vec unkC;
    Mtx unk18;
    GXColor unk48;
    u8 unk4C;
    u8 unk4D;
    char unk4E[0x2];
    char unk50[0x8];
    f32 unk58;
    char unk5C[0x4];
    f32 unk60;
} unkSubStruct3; /* size = 0x64 */

typedef struct _unkStruct5 {
    Mtx unk0;
    s16 unk30;
    s16 unk32;
    s16 unk34;
    s16 unk36;
    s16 unk38;
    s16 unk3A;
    unkSubStruct3 *unk3C;
    unkSubStruct2 *unk40;
} unkStruct5; /* size =  */

typedef struct _unkStruct6 {
    Vec unk0;
    Vec unkC;
    Vec unk18;
    Vec unk24;
} unkStruct6;

// bss
extern unkStruct5 lbl_1_bss_36C;

// prototypes
// main.c
void ObjectSetup(void);
void fn_1_43C(omObjData* object);
void fn_1_4B0(omObjData* object);
void fn_1_7D8(omObjData* object);
void fn_1_14C0(omObjData* object);
void fn_1_1524(s16, char*, f32, Mtx);
void fn_1_15D0(omObjData* object);
void fn_1_1960(omObjData* object);
void fn_1_1A60(unkStruct3*);
void fn_1_2B18(omObjData* object);
void fn_1_2C14(omObjData* object);
void fn_1_2E88(f32, Vec*, Vec*, f32);
void fn_1_2F28(f32, Vec*, Vec*, f32, Vec*, Vec*, f32);
void fn_1_31E0(f32);
void fn_1_3208(omObjData* object);
void fn_1_3640(omObjData* object);
void fn_1_3764(omObjData* object);
void fn_1_3B44(omObjData* object);
void fn_1_4660(omObjData* object);
void fn_1_5B20(unkSubStruct2*);
void fn_1_5FB0(omObjData* object);
void fn_1_6304(omObjData* object);
void fn_1_6368(void);
void* fn_1_63A8(s32);
void fn_1_6448(void*);
void fn_1_64DC(void);
void fn_1_6584(s16, char*, u8, u8, u8);
AnimBmpData* fn_1_668C(s16);
s16 fn_1_66AC(void);
s32 fn_1_679C(void);
f32 fn_1_67F0(f32, f32, f32);
void fn_1_6958(Mtx, f32, f32, f32);
void fn_1_6A78(Mtx, Vec*);
f32 fn_1_6D84(f32, f32, f32, f32);
void fn_1_6DFC(f32*, f32*, f32*, f32*, f32);
f32 fn_1_6F18(f32, f32, f32, f32);
void fn_1_6F90(f32*, f32*, f32*, f32*, f32);
void fn_1_7268(f32*, f32*, f32*, s32);
f32 fn_1_7520(f32, f32*, f32*, f32*, s32);
void fn_1_7674(f32*, Vec*, Vec*, s32);
void fn_1_7A54(f32, Vec*, f32*, Vec*, Vec*, s32);
f32 fn_1_7C68(Vec*);
f32 fn_1_7E00(Vec, Vec, Vec*, f32);
f32 fn_1_7ED8(Vec, Vec, Vec);
f32 fn_1_7F94(Vec*, Vec*, Vec*);
f32 fn_1_82D0(Vec*, Vec*, Vec*, Vec*, Vec*);
// map.c
void fn_1_8780(s16, s16);
void fn_1_95C0(ModelData*, Mtx);
unkSubStruct2* fn_1_96EC(s16);
unkSubStruct* fn_1_9708(s16, s16);
AnimData** fn_1_9734(s16);
void fn_1_9750(unkStruct6**, s16, f32, f32);
void fn_1_98D4(Vec**, s16, Vec*);
void fn_1_9974(GXColor**, s16, GXColor*);
void fn_1_9A1C(Vec**, s16, Vec*);
void fn_1_9AA8(HsfVector2f**, s16, HsfVector2f*);
void fn_1_9B40(unkSubStruct*);
void fn_1_9DC8(unkSubStruct2*);
// ...
s16 fn_1_A2D0(s32, s32);
void fn_1_A800(s16);
s16 fn_1_A94C(s32, s16, s16);
void fn_1_ACF4(s16, s16, s16, s16, s16, s16);
void fn_1_AFC8(s16, s32, s32, s32, s32);
void fn_1_B038(s16, s32, s32);
void fn_1_B0B8(s16, s32, s16);
void fn_1_B634(void);
void fn_1_B864(s16, f32, f32, f32);
void fn_1_B8D0(s16, s16, f32, f32, f32);
void fn_1_BB4C(s16, f32, f32, f32);
void fn_1_BC9C(s16, f32, f32, f32);
void fn_1_BD08(s16, s16, f32, f32, f32);
void fn_1_BE30(s16, s16, s32);
void fn_1_C110(s16, s16, u8, u8, u8, u8);
void fn_1_C264(s16, s32);
void fn_1_C2D0(s16, s32, s32);
void fn_1_C410(s16, s16, u8, u8);
void fn_1_C58C(s16, s16, u8 , f32);
void fn_1_C81C(s16, s32);