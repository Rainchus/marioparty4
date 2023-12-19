#include "common.h"
#include "game/window.h"
#include "game/memory.h"
#include "game/process.h"

#include "stdarg.h"
#include "string.h"

#define M_PI 3.141592653589793

typedef struct {
    /* 0x00 */ AnimData** unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
} SomeFontTblStruct; // Size 0x10

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[2];
    /* 0x04 */ s32 unk04[4];
} SomeKeyBufStruct; // Size 0x14

static void MesDispFunc(SpriteData*);
static u8 winBGMake(AnimData*, AnimData*);
static void HuWinProc(void);
static void HuWinDrawMes(s16 arg0);
static s32 HuWinCR(SomeWindowStruct* arg0);
static void _HuWinHomeClear(SomeWindowStruct* arg0);
static void HuWinKeyWait(s16 arg0);
static s16 HuWinSpcFontEntry(SomeWindowStruct* arg0, s16 arg1, s16 arg2, s16 arg3);
static void HuWinSpcFontClear(SomeWindowStruct* arg0);
static void HuWinChoice(SomeWindowStruct* arg0);
static void GetMesMaxSizeSub(u32 arg0);
static s32 GetMesMaxSizeSub2(SomeWindowStruct* arg0, u8* arg1);

void* HuAR_DVDtoARAM(s32);
void* HuAR_ARAMtoMRAMFileRead(s32, s32, s32);
s32 HuAudFXPlay(s32);
void HuAR_ARAMtoMRAM(void*);
void HuDataDirClose(s32);
void* HuDataReadNum(s32, s32);
f64 cos(f64);
f64 sin(f64);
void mtxTransCat(Mtx, f32, f32, f32);
void* HuDvdDataRead(char*);
void* MessData_MesPtrGet(void*, u32);

extern u16 HuPadBtn[4];
extern u8 HuPadDStkRep[4];

SomeWindowStruct ATTRIBUTE_ALIGN(32) winData[32];
u32 winKey[4];
SomeKeyBufStruct winComKeyBuf[256];

AnimData* iconAnim;
AnimData* cursorAnim;
AnimData* cardAnimA;
AnimData* cardAnimB;
Process* winProc;
void* messDataPtr;
s32 messDataNo;
static s16 winMaxWidth;
static s16 winMaxHeight;
static u8 mesWInsert[8];
static u8 winTabSize;
static u8 winInsertF;
static void* winAMemP;
static u8* fontWidthP;
static s32 cancelCRF;
static s16 mesCharCnt;
static s16 comKeyIdxNow;
static s16 comKeyIdx;
static u8 LanguageNo;
AnimData* fontAnim;

static SomeFontTblStruct spcFontTbl[] = {
    {   &iconAnim,  0, 20, 24,  10, 12 },
    {   &iconAnim,  1, 20, 24,  10, 12 },
    {   &iconAnim,  2, 20, 24,  10, 12 },
    {   &iconAnim,  3, 20, 24,  10, 12 },
    {   &iconAnim,  4, 20, 24,  10, 12 },
    {   &iconAnim,  5, 20, 24,  10, 12 },
    {   &iconAnim,  6, 20, 24,  10, 12 },
    {   &iconAnim,  7, 20, 24,  10, 12 },
    {   &iconAnim,  8, 20, 24,  10, 12 },
    {   &iconAnim,  9, 20, 24,  10, 12 },
    {   &iconAnim, 10, 20, 24,  10, 12 },
    {   &iconAnim, 11, 30, 24,  15, 12 },
    {   &iconAnim, 12, 20, 24,  10, 12 },
    {   &iconAnim, 13, 20, 24,  10, 12 },
    {   &iconAnim, 14, 20, 24,  10, 12 },
    {   &iconAnim, 15, 20, 24,  10, 12 },
    {   &iconAnim, 16, 20, 24,  10, 12 },
    {   &iconAnim, 17, 20, 24,  10, 12 },
    {   &iconAnim, 18, 20, 24,  10, 12 },
    {   &iconAnim, 19, 24, 24,  12, 12 },
    { &cursorAnim,  0, 40, 32, -15, 18 },
    {  &cardAnimA,  0, 32, 32,  16, 16 },
    {  &cardAnimB,  0, 32, 32,  16, 16 }
};
u8 charWETbl[] = {
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    20,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 18, 20, 12, 12, 11, 14,
     8, 13, 12, 12, 12, 12, 12, 12, 12,  9, 11, 12, 11, 15, 12, 13,
    12, 13, 12, 12, 11, 12, 11, 15, 12, 13, 11, 12,  6,  8,  8, 12,
    20, 12, 11, 12, 11, 11,  9, 12, 11,  4,  8, 11,  4, 14, 11, 12,
    11, 12,  9, 11,  9, 11, 11, 15, 11, 11, 11,  4, 13,  8, 14, 12,
     9,  8,  8,  8, 20,  4, 12, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 12, 12, 12, 12, 12, 12, 12, 12,  8,  8, 12, 12, 12, 12, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    12, 12,  7, 14, 17, 13, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 16, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20
};
u8 charWJTbl[] = {
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,  0, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
     0,  0, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20
};
static u8 ATTRIBUTE_ALIGN(32) charColPal[] = {
    0x00, 0x00, 0x00,
    0x00, 0x00, 0xFF,
    0xFF, 0x00, 0x00,
    0xFF, 0x00, 0xFF,
    0x00, 0xFF, 0x00,
    0x00, 0xFF, 0xFF,
    0xFF, 0xA0, 0x00,
    0xFF, 0xFF, 0xFF,
    0x60, 0x60, 0x60,
    0x90, 0x90, 0x90,
    0x00, 0x00, 0x00,
    0x60, 0xB0, 0xFF,
    0xFF, 0x40, 0x80,
    0xFF, 0x00, 0xFF,
    0x00, 0xFF, 0x00,
    0x00, 0xFF, 0xFF,
    0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF,
    0x60, 0x60, 0x60,
    0x90, 0x90, 0x90
};
static s32 frameFileTbl[] = {
    0x00860006,
    0x00860007,
    0x00860008,
    0x00860006
};
static char* mesDataTbl[] = {
    "mess/mini.dat",
    "mess/board.dat",
    "mess/mini_e.dat",
    "mess/board_e.dat"
};
static s32 winVoiceTbl[] = {
    0x37, 0x36, 0x38, 0x44,
    0x43, 0x45, 0x41, 0x40,
    0x42, 0x4C, 0x4B, 0x4D,
    0x47, 0x46, 0x48, 0x3E,
    0x3E, 0x3F, 0x49, 0x49,
    0x49
};

s16 winPrio = 1000;

void HuWindowInit(void) {
    s16 var_r31;

    winAMemP = HuAR_DVDtoARAM(0x860000);
    for (var_r31 = 0; var_r31 < 32; var_r31++) {
        winData[var_r31].unk04 = -1;
    }
    winProc = 0;
    winPrio = 1000;
}

void HuWinInit(s32 arg0) {
    s16 var_r30;
    void* var_r31;
    s8 temp_r28;

    if (winProc == 0) {
        HuAR_ARAMtoMRAM(winAMemP);
        winProc = HuPrcCreate(HuWinProc, 0x64, 0x1000, 0);
        HuPrcSetStat(winProc, 0xC);
        temp_r28 = GWGameStat.language;
        LanguageNo = temp_r28;
        messDataNo = arg0;
        fontWidthP = (LanguageNo == 0) ? charWJTbl : charWETbl;
        HuWinMesRead(arg0);
        for (var_r30 = 0; var_r30 < 32; var_r30++) {
            winData[var_r30].unk04 = -1;
        }
        if (fontAnim == 0) {
            if (LanguageNo == 0) {
                var_r31 = HuDataReadNum(0x860000, 0x10000000);
            } else {
                var_r31 = HuDataReadNum(0x860001, 0x10000000);
            }
            fontAnim = HuSprAnimRead(var_r31);
        }
        if (iconAnim == 0) {
            var_r31 = HuDataReadNum(0x860003, 0x10000000);
            iconAnim = HuSprAnimRead(var_r31);
            HuSprAnimLock(iconAnim);
        }
        if (cursorAnim == 0) {
            var_r31 = HuDataReadNum(0x860002, 0x10000000);
            cursorAnim = HuSprAnimRead(var_r31);
            HuSprAnimLock(cursorAnim);
        }
        if (cardAnimA == 0) {
            var_r31 = HuDataReadNum(0x860004, 0x10000000);
            cardAnimA = HuSprAnimRead(var_r31);
            HuSprAnimLock(cardAnimA);
        }
        if (cardAnimB == 0) {
            var_r31 = HuDataReadNum(0x860005, 0x10000000);
            cardAnimB = HuSprAnimRead(var_r31);
            HuSprAnimLock(cardAnimB);
        }
        HuDataDirClose(0x860000);
        HuWinComKeyReset();
        winPrio = 1000;
    }
}

s16 HuWinCreate(f32 x, f32 y, s16 w, s16 h, s16 frame) {
    AnimData* temp_r3_3;
    SomeWindowStruct* temp_r31;
    SpriteData* temp_r22;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 var_r29;
    s16 var_r30;
    void* temp_r21;

    for (var_r29 = 0; var_r29 < 32; var_r29++) {
        if (winData[var_r29].unk04 == -1) {
            break;
        }
    }
    if (var_r29 == 0x20) {
        return -1;
    }
    temp_r31 = &winData[var_r29];
    temp_r31->unk04 = temp_r3 = HuSprGrpCreate(0x1E);
    if (frame < 0 || frame >= 4) {
        frame = 0;
    }
    w = (w + 0xF) & 0xFFF0;
    h = (h + 0xF) & 0xFFF0;
    if (x == -10000.0f) {
        temp_r31->unk6C = (576.0f - w) / 2;
    } else {
        temp_r31->unk6C = x;
    }
    if (y == -10000.0f) {
        temp_r31->unk70 = (480.0f - h) / 2;
    } else {
        temp_r31->unk70 = y;
    }
    HuSprGrpCenterSet(temp_r3, w / 2, h / 2);
    HuSprGrpPosSet(temp_r3, temp_r31->unk6C, temp_r31->unk70);
    temp_r21 = HuAR_ARAMtoMRAMFileRead(frameFileTbl[frame], 0x10000000, 2);
    temp_r31->unk50 = HuSprAnimRead(temp_r21);
    temp_r3_2 = temp_r31->unk06[0] = HuSprCreate(temp_r31->unk50, winPrio, 0);
    HuSprGrpMemberSet(temp_r3, 0, temp_r3_2);
    HuSprTPLvlSet(temp_r3, 0, 0.9f);
    temp_r3_3 = HuSprAnimMake(w / 16, h / 16, 6);
    HuSprBGSet(temp_r3, 0, temp_r3_3, 0);
    temp_r31->unk03 = winBGMake(temp_r3_3, temp_r31->unk50);
    temp_r3_2 = temp_r31->unk06[1] = HuSprFuncCreate(MesDispFunc, winPrio);
    temp_r22 = &HuSprData[temp_r3_2];
    temp_r22->work[0] = var_r29;
    HuSprGrpMemberSet(temp_r3, 1, temp_r3_2);
    temp_r31->unk80 = 0;
    temp_r31->unk82 = (w / 8) * (h / 24) * 4;
    temp_r31->unk84 = HuMemDirectMalloc(HEAP_SYSTEM, temp_r31->unk82 * sizeof(UnknownWindowStruct1));
    temp_r31->unk4C = 0;
    temp_r31->unk00 = 0;
    temp_r31->unk8C = 0;
    temp_r31->unk44 = 0;
    temp_r31->unk5C = temp_r31->unk5E = 0;
    temp_r31->unk54 = 8;
    temp_r31->unk58 = 8;
    temp_r31->unk56 = w - 8;
    temp_r31->unk5A = h - 8;
    temp_r31->unk42 = 1;
    temp_r31->unk60 = 7;
    temp_r31->unk62 = 0;
    temp_r31->unk01 = 0xF;
    temp_r31->unk02 = 0;
    temp_r31->unk88 = 0;
    temp_r31->unk90 = 0;
    temp_r31->unkD4 = 0;
    temp_r31->unk48 = winPrio;
    temp_r31->unk64 = 1;
    temp_r31->unk66 = 2;
    temp_r31->unk68 = w;
    temp_r31->unk6A = h;
    temp_r31->unk14A = temp_r31->unk14C = 0;
    temp_r31->unk14E = 0x280;
    temp_r31->unk150 = 0x1E0;
    temp_r31->unk152 = 0x18;
    temp_r31->unk154 = 0x300;
    temp_r31->unk158 = 0;
    if (frame == 0 || frame == 2) {
        memcpy(&temp_r31->unk160, charColPal + 30, 30);
    } else {
        memcpy(&temp_r31->unk160, charColPal, 30);
        temp_r31->unk62 = 9;
    }
    for (var_r30 = 0; var_r30 < 8; var_r30++) {
        temp_r31->unkB4[var_r30] = 0;
    }
    for (var_r30 = 2; var_r30 < 30; var_r30++) {
        temp_r31->unk06[var_r30] = -1;
    }
    winPrio -= 3;
    if (winPrio < 500) {
        winPrio = 1000;
    }
    for (var_r30 = 0; var_r30 < 16; var_r30++) {
        temp_r31->unkDA[var_r30] = 0;
        temp_r31->unkEA[var_r30].unk00 = 0;
    }
    return var_r29;
}

void HuWinKill(s16 arg0) {
    SomeWindowStruct* temp_r31 = &winData[arg0];
    s16 var_r30;

    if (temp_r31->unk04 != -1) {
        HuMemDirectFree(temp_r31->unk84);
        for (var_r30 = 2; var_r30 < 30; var_r30++) {
            if (temp_r31->unk06[var_r30] != -1) {
                HuSprGrpMemberKill(temp_r31->unk04, var_r30);
            }
        }
        HuSprGrpKill(temp_r31->unk04);
        temp_r31->unk04 = -1;
    }
}

void HuWinAllKill(void) {
    s16 var_r30;

    for (var_r30 = 0; var_r30 < 32; var_r30++) {
        if (winData[var_r30].unk04 != -1) {
            HuWinKill(var_r30);
        }
    }
    if (fontAnim != 0) {
        HuSprAnimKill(fontAnim);
        fontAnim = 0;
    }
    if (iconAnim != 0) {
        HuSprAnimKill(iconAnim);
        iconAnim = 0;
    }
    if (cursorAnim != 0) {
        HuSprAnimKill(cursorAnim);
        cursorAnim = 0;
    }
    if (cardAnimA != 0) {
        HuSprAnimKill(cardAnimA);
        cardAnimA = 0;
    }
    if (cardAnimB != 0) {
        HuSprAnimKill(cardAnimB);
        cardAnimB = 0;
    }
    if (winProc != 0) {
        HuPrcKill(winProc);
        winProc = 0;
    }
    if (messDataPtr != 0) {
        HuMemDirectFree(messDataPtr);
        messDataPtr = 0;
    }
    HuDataDirClose(0x860000);
}

static void MesDispFunc(SpriteData* arg0) {
    SomeWindowStruct* temp_r31 = &winData[arg0->work[0]];
    SpriteGroupData* spC;
    f32 temp_f26;
    f32 temp_f25;
    f32 temp_f29;
    f32 temp_f28;
    f32 temp_f27;
    f32 temp_f31;
    f32 temp_f30;
    f32 var_f23;
    s16 var_r29;
    u16 temp_r27;
    s16 temp_r28;
    Mtx sp80;
    Mtx sp50;
    Mtx44 sp10;

    if (temp_r31->unk80 != 0) {
        spC = &HuSprGrpData[temp_r31->unk04];
        GXInvalidateTexAll();
        C_MTXOrtho(sp10, 0.0f, 480.0f, 0.0f, 576.0f, 0.0f, 10.0f);
        GXSetProjection(sp10, GX_ORTHOGRAPHIC);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_S, GX_RGBA8, 0);
        GXSetCullMode(GX_CULL_NONE);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, 0, 0x7D);
        GXSetNumTevStages(1);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_VTX, 1, GX_DF_CLAMP, GX_AF_SPOT);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetZCompLoc(0);
        PSMTXRotRad(sp50, 0x7A, 0.017453292f * arg0->z_rot);
        PSMTXScale(sp80, arg0->scale_x, arg0->scale_y, 1.0f);
        PSMTXConcat(sp50, sp80, sp50);
        mtxTransCat(sp50, arg0->x, arg0->y, 0.0f);
        PSMTXConcat(*arg0->group_mtx, sp50, sp50);
        GXLoadPosMtxImm(sp50, 0);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        HuSprTexLoad(fontAnim, 0, 0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
        GXBegin(GX_QUADS, GX_VTXFMT0, temp_r31->unk80 * 4);
        var_f23 = (LanguageNo == 0) ? 0.05882353f : 0.07692308f;
        for (var_r29 = 0; var_r29 < temp_r31->unk80; var_r29++) {
            temp_f27 = fontWidthP[temp_r31->unk84[var_r29].unk06 + 0x30];
            temp_f29 = 0.0625f * (temp_r31->unk84[var_r29].unk06 % 16);
            temp_f28 = var_f23 * (temp_r31->unk84[var_r29].unk06 / 16);
            temp_f26 = temp_f29 + (temp_f27 / 320.0);
            temp_f25 = temp_f28 + var_f23;
            temp_f31 = temp_r31->unk84[var_r29].unk02;
            temp_f30 = temp_r31->unk84[var_r29].unk04;
            temp_r28 = temp_r31->unk84[var_r29].unk00;
            if (temp_r31->unk42 != 0) {
                temp_r27 = temp_r31->unk84[var_r29].unk01 * 8;
            } else {
                temp_r27 = 0xFF;
            }
            temp_r27 = 0xFF;
            if (temp_r31->unk84[var_r29].unk01 < 0x1F) {
                temp_r31->unk84[var_r29].unk01++;
            }
            GXPosition3f32(temp_f31 + 1.0f, temp_f30, 0.0f);
            GXColor4u8(temp_r31->unk160[temp_r28][0], temp_r31->unk160[temp_r28][1], temp_r31->unk160[temp_r28][2], temp_r27);
            GXTexCoord2f32(temp_f29, temp_f28);
            GXPosition3f32(temp_f31 + temp_f27, temp_f30, 0.0f);
            GXColor4u8(temp_r31->unk160[temp_r28][0], temp_r31->unk160[temp_r28][1], temp_r31->unk160[temp_r28][2], temp_r27);
            GXTexCoord2f32(temp_f26, temp_f28);
            GXPosition3f32(temp_f31 + temp_f27, temp_f30 + 24.0f, 0.0f);
            GXColor4u8(temp_r31->unk160[temp_r28][0], temp_r31->unk160[temp_r28][1], temp_r31->unk160[temp_r28][2], temp_r27);
            GXTexCoord2f32(temp_f26, temp_f25);
            GXPosition3f32(temp_f31 + 1.0f, temp_f30 + 24.0f, 0.0f);
            GXColor4u8(temp_r31->unk160[temp_r28][0], temp_r31->unk160[temp_r28][1], temp_r31->unk160[temp_r28][2], temp_r27);
            GXTexCoord2f32(temp_f29, temp_f25);
        }
        GXEnd();
        mesCharCnt++;
    }
}

static u8 winBGMake(AnimData* arg0, AnimData* arg1) {
    AnimBmpData* temp_r25;
    s16 temp_r22;
    s16 temp_r23;
    s16 temp_r27;
    s16 temp_r28;
    s16 var_r30;
    s16 var_r31;
    u8* temp_r3;
    u16* var_r24;

    temp_r28 = arg0->bmp->sizeX;
    temp_r23 = arg0->bmp->sizeY;
    temp_r27 = (temp_r28 + 7) & 0xF8;
    temp_r22 = (temp_r23 + 3) & 0xFC;
    temp_r3 = arg0->bmp->data = HuMemDirectMallocNum(HEAP_SYSTEM, temp_r27 * temp_r22, 0x10000000);
    for (var_r30 = 0; var_r30 < temp_r23; var_r30++) {
        if (var_r30 == 0) {
            for (var_r31 = 0; var_r31 < temp_r28; var_r31++) {
                if (var_r31 == 0) {
                    temp_r3[(var_r31 & 7) + ((var_r31 >> 3) << 5) + (var_r30 >> 2) * (temp_r27 * 4) + (var_r30 & 3) * 8] = 0;
                } else if (var_r31 == temp_r28 - 1) {
                    temp_r3[(var_r31 & 7) + ((var_r31 >> 3) << 5) + (var_r30 >> 2) * (temp_r27 * 4) + (var_r30 & 3) * 8] = 0x10;
                } else {
                    temp_r3[(var_r31 & 7) + ((var_r31 >> 3) << 5) + (var_r30 >> 2) * (temp_r27 * 4) + (var_r30 & 3) * 8] = 0x70;
                }
            }
        } else if (var_r30 == temp_r23 - 1) {
            for (var_r31 = 0; var_r31 < temp_r28; var_r31++) {
                if (var_r31 == 0) {
                    temp_r3[(var_r31 & 7) + ((var_r31 >> 3) << 5) + (var_r30 >> 2) * (temp_r27 * 4) + (var_r30 & 3) * 8] = 0x20;
                } else if (var_r31 == temp_r28 - 1) {
                    temp_r3[(var_r31 & 7) + ((var_r31 >> 3) << 5) + (var_r30 >> 2) * (temp_r27 * 4) + (var_r30 & 3) * 8] = 0x30;
                } else {
                    temp_r3[(var_r31 & 7) + ((var_r31 >> 3) << 5) + (var_r30 >> 2) * (temp_r27 * 4) + (var_r30 & 3) * 8] = 0x60;
                }
            }
        } else {
            for (var_r31 = 0; var_r31 < temp_r28; var_r31++) {
                if (var_r31 == 0) {
                    temp_r3[(var_r31 & 7) + ((var_r31 >> 3) << 5) + (var_r30 >> 2) * (temp_r27 * 4) + (var_r30 & 3) * 8] = 0x40;
                } else if (var_r31 == temp_r28 - 1) {
                    temp_r3[(var_r31 & 7) + ((var_r31 >> 3) << 5) + (var_r30 >> 2) * (temp_r27 * 4) + (var_r30 & 3) * 8] = 0x50;
                } else {
                    temp_r3[(var_r31 & 7) + ((var_r31 >> 3) << 5) + (var_r30 >> 2) * (temp_r27 * 4) + (var_r30 & 3) * 8] = 0x80;
                }
            }
        }
    }
    DCStoreRangeNoSync(arg0->bmp->data, temp_r27 * temp_r22);
    temp_r25 = arg1->bmp;
    var_r24 = temp_r25->palData;
    for (temp_r28 = 0; temp_r28 < temp_r25->palNum; temp_r28++, var_r24++) {
        if (*var_r24 == 0xFC00) {
            *var_r24 = 0x6114;
            break;
        }
    }
    DCStoreRangeNoSync(temp_r25->palData, 0x200);
    return temp_r28;
}

static void HuWinProc(void) {
    SomeWindowStruct* var_r31;
    s16 var_r30;

    while (1) {
        HuPrcVSleep();
        var_r31 = winData;
        for (var_r30 = 0; var_r30 < 32; var_r30++, var_r31++) {
            if (var_r31->unk04 != -1 && !(var_r31->unk4C & 8)) {
                switch (var_r31->unk00) {
                    case 0:
                        break;
                    case 1:
                        HuWinDrawMes(var_r30);
                        break;
                    case 2:
                        HuWinComKeyGet(var_r30, winKey);
                        HuWinKeyWait(var_r30);
                        break;
                    case 3:
                        if (!(var_r31->unk4C & 0x40) || HuWinActiveKeyGetX(var_r31) == 0) {
                            var_r31->unk4C &= ~0x40;
                            HuWinComKeyGet(var_r30, winKey);
                            HuWinChoice(var_r31);
                        }
                        break;
                }
            }
        }
    }
}

static inline void HuWinDrawMesInlineFunc(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    SomeWindowStruct* temp_r28 = &winData[arg0];
    UnknownWindowStruct1* temp_r20 = temp_r28->unk84;

    temp_r20 = &temp_r28->unk84[temp_r28->unk80];
    temp_r20->unk02 = arg1 - temp_r28->unk68 / 2;
    temp_r20->unk04 = arg2 - temp_r28->unk6A / 2;
    temp_r20->unk06 = arg3 - 0x30;
    temp_r20->unk00 = arg4;
    temp_r20->unk01 = 0;
    temp_r28->unk80++;
    if (temp_r28->unk80 >= temp_r28->unk82) {
        temp_r28->unk80 = temp_r28->unk82 - 1;
    }
}

static void HuWinDrawMes(s16 arg0) {
    SomeWindowStruct* temp_r31 = &winData[arg0];
    SpriteGroupData* sp44 = &HuSprGrpData[temp_r31->unk04];
    s16 var_r30;
    s16 sp34;
    s16 sp32;
    s16 sp30;
    s16 sp2E;
    s16 sp2C;
    s16 sp2A;
    s16 sp28;
    s16 sp26;

    temp_r31->unk44 += 3;
    while (temp_r31->unk44 >= temp_r31->unk42 || (temp_r31->unk4C & 0x2000)) {
        temp_r31->unk44 -= temp_r31->unk42;
        if (temp_r31->unk44 < 0) {
            temp_r31->unk44 = 0;
        }
        sp32 = temp_r31->unk64 + fontWidthP[temp_r31->unk90[0]];
        sp2C = 0;
        if (temp_r31->unk90[0] != 0 && (temp_r31->unk4C & 4)) {
            temp_r31->unk4C &= ~4;
            _HuWinHomeClear(temp_r31);
        }
        while (temp_r31->unk90[0] < 0x30 || temp_r31->unk90[0] == 0xFF) {
            switch (temp_r31->unk90[0]) {
                case 0x0:
                    if (temp_r31->unk88 == 0) {
                        for (sp34 = 0; sp34 < 16; sp34++) {
                            temp_r31->unkDA[sp34] = 0;
                        }
                        temp_r31->unk00 = 0;
                        temp_r31->unk4C &= ~0x80;
                        return;
                    }
                    temp_r31->unk88--;
                    temp_r31->unk90 = temp_r31->unk94[temp_r31->unk88];
                    temp_r31->unk44 = 0;
                    break;
                case 0x1F:
                    temp_r31->unk90++;
                    sp2E = temp_r31->unk90[0] - 1;
                    if (temp_r31->unkB4[sp2E] != 0) {
                        temp_r31->unk94[temp_r31->unk88] = temp_r31->unk90;
                        temp_r31->unk90 = temp_r31->unkB4[sp2E];
                        temp_r31->unk88++;
                        if (temp_r31->unk90[0] != 0xB) {
                            temp_r31->unk90--;
                        }
                    }
                    break;
                case 0xB:
                    temp_r31->unk4C &= ~0x2200;
                    _HuWinHomeClear(temp_r31);
                    if (temp_r31->unk4C & 0x800) {
                        sp26 = GetMesMaxSizeSub2(temp_r31, temp_r31->unk90 + 1);
                        temp_r31->unk5C = (temp_r31->unk56 - sp26) / 2;
                    } else if (temp_r31->unk4C & 0x1000) {
                        sp26 = GetMesMaxSizeSub2(temp_r31, temp_r31->unk90 + 1);
                        temp_r31->unk5C = temp_r31->unk56 - sp26;
                    }
                    break;
                case 0x1E:
                    temp_r31->unk90++;
                    if (!(temp_r31->unk4C & 0x80)) {
                        temp_r31->unk60 = temp_r31->unk90[0] - 1;
                    }
                    break;
                case 0x1D:
                    temp_r31->unk4C ^= 1;
                    break;
                case 0xA:
                    temp_r31->unk4C &= ~0x2020;
                    if (temp_r31->unk4C & 0x200) {
                        if (!(temp_r31->unk4C & 0x100)) {
                            if (HuWinCR(temp_r31) != 0) {
                                temp_r31->unk90++;
                                HuWinKeyWaitEntry(arg0);
                                temp_r31->unk4C |= 2;
                                return;
                            }
                            if (temp_r31->unk4C & 0x800) {
                                sp26 = GetMesMaxSizeSub2(temp_r31, temp_r31->unk90 + 1);
                                temp_r31->unk5C = (temp_r31->unk56 - sp26) / 2;
                            } else if (temp_r31->unk4C & 0x1000) {
                                sp26 = GetMesMaxSizeSub2(temp_r31, temp_r31->unk90 + 1);
                                temp_r31->unk5C = temp_r31->unk56 - sp26;
                            }
                            break;
                        }
                        sp32 = fontWidthP[16] + temp_r31->unk64;
                        /* fallthrough */
                case 0x10:
                case 0x20:
                        temp_r31->unk4C |= 0x200;
                        if (temp_r31->unk5C + sp32 > temp_r31->unk56) {
                            if (HuWinCR(temp_r31) != 0) {
                                temp_r31->unk90++;
                                HuWinKeyWaitEntry(arg0);
                                temp_r31->unk4C |= 2;
                                return;
                            }
                            break;
                        }
                        temp_r31->unk5C += sp32;
                    }
                    break;
                case 0xE:
                    temp_r31->unk4C |= 0x200;
                    temp_r31->unk90++;
                    sp30 = temp_r31->unk64 + spcFontTbl[temp_r31->unk90[0] - 1].unk06;
                    if (temp_r31->unk5C + sp30 > temp_r31->unk56 && HuWinCR(temp_r31) != 0) {
                        temp_r31->unk90--;
                        HuWinKeyWaitEntry(arg0);
                        temp_r31->unk4C |= 2;
                        return;
                    }
                    HuWinSpcFontEntry(temp_r31, temp_r31->unk90[0] - 1, temp_r31->unk54 + temp_r31->unk5C, temp_r31->unk58 + temp_r31->unk5E);
                    temp_r31->unk5C += sp30;
                    sp2C = 1;
                    break;
                case 0x1C:
                    temp_r31->unk90++;
                    HuAudFXPlay(winVoiceTbl[temp_r31->unk90[0] - 1]);
                    break;
                case 0xFF:
                    temp_r31->unk90++;
                    HuWinKeyWaitEntry(arg0);
                    temp_r31->unk4C |= 4;
                    temp_r31->unk4C &= ~0x200;
                    return;
                case 0xF:
                    temp_r31->unk4C |= 0x2000;
                    if (temp_r31->unkDA[temp_r31->unkD4] != 0) {
                        temp_r31->unk4C |= 0x20;
                        temp_r31->unkEA[temp_r31->unkD4].unk00 |= 1;
                    } else {
                        temp_r31->unkEA[temp_r31->unkD4].unk00 &= ~1;
                    }

                    temp_r31->unkEA[temp_r31->unkD4].unk02 = temp_r31->unk5C + temp_r31->unk58;
                    temp_r31->unkEA[temp_r31->unkD4].unk04 = temp_r31->unk5E + temp_r31->unk54;
                    temp_r31->unkD4++;
                    break;
                case 0xC:
                    temp_r31->unk4C |= 0x200;
                    sp30 = temp_r31->unk152 * ((temp_r31->unk5C + temp_r31->unk152) / temp_r31->unk152) - temp_r31->unk5C;
                    if (temp_r31->unk5C + sp30 > temp_r31->unk56) {
                        if (HuWinCR(temp_r31) != 0) {
                            temp_r31->unk90++;
                            HuWinKeyWaitEntry(arg0);
                            temp_r31->unk4C |= 2;
                            return;
                        }
                    } else {
                        temp_r31->unk5C += sp30;
                    }
                    break;
            }
            temp_r31->unk90++;
            sp32 = temp_r31->unk64 + fontWidthP[temp_r31->unk90[0]];
            if (sp2C != 0) {
                break;
            }
        }
        if (sp2C == 0) {
            if (temp_r31->unk5C + sp32 > temp_r31->unk56 && HuWinCR(temp_r31) != 0) {
                HuWinKeyWaitEntry(arg0);
                temp_r31->unk4C |= 2;
                return;
            }
            var_r30 = temp_r31->unk90[0];
            temp_r31->unk4C |= 0x200;
            if (temp_r31->unk90[1] == 0x80) {
                if (var_r30 >= 0x96 && var_r30 <= 0xA4) {
                    var_r30 = var_r30 + 0x6A;
                } else if (var_r30 >= 0xAA && var_r30 <= 0xAE) {
                    var_r30 = var_r30 + 0x65;
                } else if (var_r30 >= 0xD6 && var_r30 <= 0xE4) {
                    var_r30 = var_r30 + 0x43;
                } else if (var_r30 >= 0xEA && var_r30 <= 0xEE) {
                    var_r30 = var_r30 + 0x3E;
                }
                temp_r31->unk90++;
            } else if (temp_r31->unk90[1] == 0x81) {
                if (var_r30 >= 0xAA && var_r30 <= 0xAE) {
                    var_r30 = (var_r30 + 0x6A);
                } else if (var_r30 >= 0xEA && var_r30 <= 0xEE) {
                    var_r30 = (var_r30 + 0x43);
                }
                temp_r31->unk90++;
            }
            sp28 = (temp_r31->unk4C & 0x20) ? 8 : temp_r31->unk60;
            if (temp_r31->unk4C & 1) {
                sp2A = 0;
                if (temp_r31->unk60 == 0 || temp_r31->unk60 == 1) {
                    sp2A = 8;
                }
                HuWinDrawMesInlineFunc(arg0, temp_r31->unk54 + temp_r31->unk5C + 2, temp_r31->unk58 + temp_r31->unk5E    , var_r30, sp2A);
                HuWinDrawMesInlineFunc(arg0, temp_r31->unk54 + temp_r31->unk5C - 2, temp_r31->unk58 + temp_r31->unk5E    , var_r30, sp2A);
                HuWinDrawMesInlineFunc(arg0, temp_r31->unk54 + temp_r31->unk5C    , temp_r31->unk58 + temp_r31->unk5E + 2, var_r30, sp2A);
                HuWinDrawMesInlineFunc(arg0, temp_r31->unk54 + temp_r31->unk5C    , temp_r31->unk58 + temp_r31->unk5E - 2, var_r30, sp2A);
                HuWinDrawMesInlineFunc(arg0, temp_r31->unk54 + temp_r31->unk5C    , temp_r31->unk58 + temp_r31->unk5E    , var_r30, sp28);
            } else {
                HuWinDrawMesInlineFunc(arg0, temp_r31->unk54 + temp_r31->unk5C + 2, temp_r31->unk58 + temp_r31->unk5E + 2, var_r30, temp_r31->unk62);
                HuWinDrawMesInlineFunc(arg0, temp_r31->unk54 + temp_r31->unk5C    , temp_r31->unk58 + temp_r31->unk5E    , var_r30, sp28);
            }
            temp_r31->unk5C += sp32;
            temp_r31->unk90++;
        }
    }
}

static s32 HuWinCR(SomeWindowStruct* arg0) {
    if (arg0->unk5E + 0x30 > arg0->unk5A) {
        arg0->unk5E = 0;
        arg0->unk5C = 0;
        return 1;
    } else {
        arg0->unk5E += arg0->unk66 + 0x18;
        arg0->unk5C = 0;
        return 0;
    }
}

static void _HuWinHomeClear(SomeWindowStruct* arg0) {
    s16 var_r30;

    arg0->unk80 = 0;
    arg0->unk5E = arg0->unk5C = 0;
    arg0->unkD4 = 0;
    HuWinSpcFontClear(arg0);
    arg0->unk4C &= ~0x2020;
    for (var_r30 = 0; var_r30 < 16; var_r30++) {
        arg0->unkEA[var_r30].unk00 = 0;
    }
}

void HuWinHomeClear(s16 arg0) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    _HuWinHomeClear(temp_r31);
}

void HuWinKeyWaitEntry(s16 arg0) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    if (temp_r31->unk4C & 0x400) {
        temp_r31->unk00 = 0;
    } else {
        temp_r31->unk00 = 2;
        temp_r31->unk46 = HuWinSpcFontEntry(temp_r31, 0x13, temp_r31->unk56 - 0x14, temp_r31->unk5A - 0x18);
    }
}

static void HuWinKeyWait(s16 arg0) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    if (temp_r31->unk154 & HuWinActivePadGet(temp_r31)) {
        temp_r31->unk156 = HuWinActivePadGet(temp_r31);
        temp_r31->unk00 = 1;
        HuAudFXPlay(0x1C);
        HuWinSprKill(arg0, temp_r31->unk46);
        if (temp_r31->unk4C & 2) {
            _HuWinHomeClear(temp_r31);
        }
        temp_r31->unk4C &= ~2;
    }
}

static s16 HuWinSpcFontEntry(SomeWindowStruct* arg0, s16 arg1, s16 arg2, s16 arg3) {
    SpriteGroupData* spC = &HuSprGrpData[arg0->unk04];
    s16 temp_r3;
    s16 var_r30;
    AnimData* temp_r27;

    for (var_r30 = 10; var_r30 < 30; var_r30++) {
        if (arg0->unk06[var_r30] == -1) {
            temp_r27 = *spcFontTbl[arg1].unk00;
            arg0->unk06[var_r30] = temp_r3 = HuSprCreate(temp_r27, arg0->unk48 - 1, spcFontTbl[arg1].unk04);
            HuSprGrpMemberSet(arg0->unk04, var_r30, temp_r3);
            HuSprPosSet(arg0->unk04, var_r30, arg2 + spcFontTbl[arg1].unk0A - arg0->unk68 / 2, arg3 + spcFontTbl[arg1].unk0C - arg0->unk6A / 2);
            break;
        }
    }
    return var_r30;
}

static void HuWinSpcFontClear(SomeWindowStruct* arg0) {
    s16 var_r31;

    for (var_r31 = 10; var_r31 < 30; var_r31++) {
        if (arg0->unk06[var_r31] != -1) {
            HuSprGrpMemberKill(arg0->unk04, var_r31);
            arg0->unk06[var_r31] = -1;
        }
    }
}

static inline void HuWinChoiceInlineFunction(SomeWindowStruct* arg0, s16 arg1, s16 arg2, s16 arg3) {
    SpriteGroupData* temp_var = &HuSprGrpData[arg0->unk04];

    HuSprPosSet(arg0->unk04, arg1, arg2 - arg0->unk68 / 2, arg3 - arg0->unk6A / 2);
}

void HuWinChoice(SomeWindowStruct* arg0) {
    UnknownWindowStruct2* var_r31;
    f32 var_f30;
    f32 var_f31;
    s16 temp_r20;
    s16 temp_r21;
    s16 temp_r25;
    s16 temp_r24;
    s16 temp_r26;
    s16 temp_r27;
    s16 temp_r28;
    s16 var_r19;
    s16 var_r22;
    s16 var_r23;
    s16 var_r30;

    temp_r26 = arg0->unkD6;
    var_r23 = temp_r26;
    var_r19 = -1;
    temp_r21 = HuWinActivePadGet(arg0);
    if (temp_r21 & 1) {
        var_r19 = 0;
    }
    if (temp_r21 & 2) {
        var_r19 = 2;
    }
    if (temp_r21 & 8) {
        var_r19 = 1;
    }
    if (temp_r21 & 4) {
        var_r19 = 3;
    }
    temp_r25 = arg0->unkEA[temp_r26].unk02;
    temp_r24 = arg0->unkEA[temp_r26].unk04;
    var_f31 = 100000.0f;
    var_f30 = var_f31;
    temp_r27 = arg0->unkD4;
    switch (var_r19) {
        case 0:
            for (var_r30 = 0, var_r31 = arg0->unkEA; var_r30 < temp_r27; var_r30++, var_r31++) {
                if (var_r30 != temp_r26 && !(var_r31->unk00 & 1) && var_r31->unk04 == temp_r24 && var_r31->unk02 < temp_r25) {
                    break;
                }
            }
            if (var_r30 != temp_r27) {
                for (var_r30 = 0, var_r31 = arg0->unkEA; var_r30 < temp_r27; var_r30++, var_r31++) {
                    if (var_r30 != temp_r26 && !(var_r31->unk00 & 1) && var_r31->unk04 == temp_r24 && var_r31->unk02 < temp_r25 && var_f30 > temp_r25 - var_r31->unk02) {
                        var_f30 = temp_r25 - var_r31->unk02;
                        var_r23 = var_r30;
                    }
                }
            }
            break;
        case 1:
            for (var_r30 = 0, var_r31 = arg0->unkEA; var_r30 < temp_r27; var_r30++, var_r31++) {
                if (var_r30 != temp_r26 && !(var_r31->unk00 & 1) && var_r31->unk04 < temp_r24) {
                    break;
                }
            }
            if (var_r30 != temp_r27) {
                for (var_r30 = 0, var_r31 = arg0->unkEA; var_r30 < temp_r27; var_r30++, var_r31++) {
                    if (var_r30 != temp_r26 && !(var_r31->unk00 & 1) && var_r31->unk04 < temp_r24) {
                        temp_r20 = temp_r24 - var_r31->unk04;
                        if (temp_r20 <= var_f30) {
                            if (temp_r20 < var_f30) {
                                var_f31 = 100000.0f;
                            }
                            temp_r28 = temp_r25 - var_r31->unk02;
                            temp_r28 = temp_r28 * temp_r28;
                            if (temp_r28 < var_f31) {
                                var_f30 = temp_r20;
                                var_f31 = temp_r28;
                                var_r23 = var_r30;
                            }
                        }
                    }
                }
            } else {
                var_r22 = -1000;
                for (var_r30 = 0, var_r31 = arg0->unkEA; var_r30 < temp_r27; var_r30++, var_r31++) {
                    if (var_r30 != temp_r26 && !(var_r31->unk00 & 1) && var_r31->unk04 > var_r22) {
                        var_r22 = var_r31->unk04;
                    }
                }
                if (var_r22 != temp_r24) {
                    var_f31 = 100000.0f;
                    for (var_r30 = 0, var_r31 = arg0->unkEA; var_r30 < temp_r27; var_r30++, var_r31++) {
                        if (var_r30 != temp_r26 && !(var_r31->unk00 & 1) && var_r31->unk04 == var_r22) {
                            temp_r28 = temp_r25 - var_r31->unk02;
                            temp_r28 = temp_r28 * temp_r28;
                            if (temp_r28 < var_f31) {
                                var_f31 = temp_r28;
                                var_r23 = var_r30;
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            for (var_r30 = 0, var_r31 = arg0->unkEA; var_r30 < temp_r27; var_r30++, var_r31++) {
                if (var_r30 != temp_r26 && !(var_r31->unk00 & 1) && var_r31->unk04 == temp_r24 && var_r31->unk02 > temp_r25) {
                    break;
                }
            }
            if (var_r30 != temp_r27) {
                for (var_r30 = 0, var_r31 = arg0->unkEA; var_r30 < temp_r27; var_r30++, var_r31++) {
                    if (var_r30 != temp_r26 && !(var_r31->unk00 & 1) && var_r31->unk04 == temp_r24 && var_r31->unk02 > temp_r25 && var_f30 > var_r31->unk02 - temp_r25) {
                        var_f30 = var_r31->unk02 - temp_r25;
                        var_r23 = var_r30;
                    }
                }
            }
            break;
        case 3:
            for (var_r30 = 0, var_r31 = arg0->unkEA; var_r30 < temp_r27; var_r30++, var_r31++) {
                if (var_r30 != temp_r26 && !(var_r31->unk00 & 1) && var_r31->unk04 > temp_r24) {
                    break;
                }
            }
            if (var_r30 != temp_r27) {
                for (var_r30 = 0, var_r31 = arg0->unkEA; var_r30 < temp_r27; var_r30++, var_r31++) {
                    if (var_r30 != temp_r26 && !(var_r31->unk00 & 1) && var_r31->unk04 > temp_r24) {
                        temp_r20 = var_r31->unk04 - temp_r24;
                        if (temp_r20 <= var_f30) {
                            if (temp_r20 < var_f30) {
                                var_f31 = 100000.0f;
                            }
                            temp_r28 = temp_r25 - var_r31->unk02;
                            temp_r28 = temp_r28 * temp_r28;
                            if (temp_r28 < var_f31) {
                                var_f30 = temp_r20;
                                var_f31 = temp_r28;
                                var_r23 = var_r30;
                            }
                        }
                    }
                }
            } else {
                var_r22 = 1000;
                for (var_r30 = 0, var_r31 = arg0->unkEA; var_r30 < temp_r27; var_r30++, var_r31++) {
                    if (var_r30 != temp_r26 && !(var_r31->unk00 & 1) && var_r31->unk04 < var_r22) {
                        var_r22 = var_r31->unk04;
                    }
                }
                if (var_r22 != temp_r24) {
                    var_f31 = 100000.0f;
                    for (var_r30 = 0, var_r31 = arg0->unkEA; var_r30 < temp_r27; var_r30++, var_r31++) {
                        if (var_r30 != temp_r26 && !(var_r31->unk00 & 1) && var_r31->unk04 == var_r22) {
                            temp_r28 = temp_r25 - var_r31->unk02;
                            temp_r28 = temp_r28 * temp_r28;
                            if (temp_r28 < var_f31) {
                                var_f31 = temp_r28;
                                var_r23 = var_r30;
                            }
                        }
                    }
                }
            }
            break;
    }
    if (arg0->unkD6 != var_r23) {
        arg0->unkD6 = var_r23;
        HuAudFXPlay(0);
    } else if (temp_r21 & (arg0->unk158 | 0x100)) {
        HuAudFXPlay(2);
        arg0->unk156 = temp_r21;
        arg0->unk00 = 0;
    } else if ((temp_r21 & 0x200) && !(arg0->unk4C & 0x10)) {
        HuAudFXPlay(3);
        arg0->unk156 = temp_r21;
        arg0->unkD6 = -1;
        arg0->unk00 = 0;
    }
    HuWinChoiceInlineFunction(arg0, arg0->unkD8, arg0->unkEA[var_r23].unk02 + spcFontTbl[0x14].unk0A, arg0->unkEA[var_r23].unk04 + spcFontTbl[0x14].unk0C);
}

u32 HuWinActivePadGet(SomeWindowStruct* arg0) {
    s32 var_r30;
    u32 var_r31;

    var_r30 = 0;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (arg0->unk01 & (1 << var_r31)) {
            var_r30 |= winKey[var_r31];
        }
    }
    return var_r30;
}

u32 HuWinActiveKeyGetX(SomeWindowStruct* arg0) {
    u32 var_r29;
    u32 var_r30;
    u32 var_r31;
    u8 temp_r28;

    var_r29 = 0;
    temp_r28 = (arg0->unk01 & ~arg0->unk02);
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        if (temp_r28 & (1 << var_r30)) {
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                if (var_r30 == GWPlayerCfg[var_r31].pad_idx) {
                    break;
                }
            }
            if (var_r31 != 4 && GWPlayerCfg[var_r31].iscom == 0) {
                var_r29 |= HuPadBtn[GWPlayerCfg[var_r31].pad_idx];
            }
        }
    }
    return var_r29;
}

void HuWinPosSet(s16 arg0, f32 arg1, f32 arg2) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    temp_r31->unk6C = arg1;
    temp_r31->unk70 = arg2;
    HuSprGrpPosSet(temp_r31->unk04, arg1, arg2);
}

void HuWinScaleSet(s16 arg0, f32 arg1, f32 arg2) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    temp_r31->unk74 = arg1;
    temp_r31->unk78 = arg2;
    HuSprGrpScaleSet(temp_r31->unk04, arg1, arg2);
}

void HuWinZRotSet(s16 arg0, f32 arg1) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    temp_r31->unk7C = arg1;
    HuSprGrpZRotSet(temp_r31->unk04, arg1);
}

void HuWinCenterPosSet(s16 arg0, f32 arg1, f32 arg2) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    HuSprGrpCenterSet(temp_r31->unk04, temp_r31->unk68 / 2.0f - arg1, temp_r31->unk6A / 2.0f - arg2);
}

void HuWinDrawNoSet(s16 arg0, s16 arg1) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    HuSprGrpDrawNoSet(temp_r31->unk04, arg1);
}

void HuWinScissorSet(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    HuSprGrpScissorSet(temp_r31->unk04, arg1, arg2, arg3, arg4);
}

void HuWinPriSet(s16 arg0, s16 arg1) {
    SomeWindowStruct* temp_r31 = &winData[arg0];
    s16 var_r30;

    HuSprPriSet(temp_r31->unk04, 0, arg1);
    HuSprPriSet(temp_r31->unk04, 1, arg1);
    for (var_r30 = 2; var_r30 < 30; var_r30++) {
        if (temp_r31->unk06[var_r30] != -1) {
            HuSprPriSet(temp_r31->unk04, var_r30, arg1 - 1);
        }
    }
    temp_r31->unk48 = arg1;
}

void HuWinAttrSet(s16 arg0, s32 arg1) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    temp_r31->unk4C |= arg1;
}

void HuWinAttrReset(s16 arg0, u32 arg1) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    temp_r31->unk4C &= ~arg1;
}

u8 HuWinStatGet(s16 arg0) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    return temp_r31->unk00;
}

void HuWinMesColSet(s16 arg0, u8 arg1) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    temp_r31->unk60 = arg1;
    temp_r31->unk4C |= 0x80;
}

void HuWinMesPalSet(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    temp_r31->unk160[arg1][0] = arg2;
    temp_r31->unk160[arg1][1] = arg3;
    temp_r31->unk160[arg1][2] = arg4;
}

void HuWinBGTPLvlSet(s16 arg0, f32 arg1) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    HuSprTPLvlSet(temp_r31->unk04, 0, arg1);
}

void HuWinBGColSet(s16 arg0, ColorRGB* arg1) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    HuSprColorSet(temp_r31->unk04, 0, arg1->r, arg1->g, arg1->b);
}

void HuWinMesSpeedSet(s16 arg0, s16 arg1) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    temp_r31->unk42 = arg1;
}

void HuWinMesRead(s32 arg0) {
    void* temp_r31;
    char* var_r30;

    if (messDataPtr != 0) {
        HuMemDirectFree(messDataPtr);
    }
    messDataNo = arg0;
    if (LanguageNo == 0) {
        var_r30 = mesDataTbl[messDataNo];
    } else {
        var_r30 = mesDataTbl[messDataNo + 2];
    }
    temp_r31 = HuDvdDataRead(var_r30);
    messDataPtr = HuMemDirectMalloc(HEAP_SYSTEM, DirDataSize);
    memcpy(messDataPtr, temp_r31, DirDataSize);
    HuMemDirectFree(temp_r31);
}

void HuWinMesSet(s16 arg0, u32 arg1) {
    SomeWindowStruct* win = &winData[arg0];

    win->unk00 = 1;
    if ((arg1 & 0x80000000) == 0) {
        if (messDataPtr == 0) {
            OSReport("Error: No Message\n");
            return;
        }
        win->unk90 = MessData_MesPtrGet(messDataPtr, arg1);
        if (win->unk90 == 0) {
            OSReport("Error: No Message data\n");
            HuWinMesSet(arg0, 0);
            return;
        }
    } else {
        win->unk90 = (u8*) arg1;
    }
    if (!(win->unk4C & 0x80)) {
        win->unk60 = 7;
        win->unk44 = 0;
    }
}

void HuWinInsertMesSet(s16 arg0, u32 arg1, s16 arg2) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    if (!(arg1 & 0x80000000)) {
        if (messDataPtr == 0) {
            OSReport("Error: No Message\n");
            return;
        }
        temp_r31->unkB4[arg2] = MessData_MesPtrGet(messDataPtr, arg1);
        if (temp_r31->unkB4[arg2] == 0) {
            OSReport("Error: No Message data\n");
        }
    } else {
        temp_r31->unkB4[arg2] = (void*) arg1;
    }
}

s16 HuWinChoiceGet(s16 arg0, s16 arg1) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    temp_r31->unk4C |= 0x40;
    while (temp_r31->unk00 != 0) {
        HuPrcVSleep();
    }
    for (; arg1 < temp_r31->unkD4; arg1++) {
        if (!(temp_r31->unkEA[arg1].unk00 & 1)) {
            break;
        }
    }
    if (arg1 == temp_r31->unkD4) {
        for (arg1 = 0; arg1 < temp_r31->unkD4; arg1++) {
            if (!(temp_r31->unkEA[arg1].unk00 & 1)) {
                break;
            }
        }
        if (arg1 == temp_r31->unkD4) {
            return -1;
        }
    }
    temp_r31->unkD8 = HuWinSpcFontEntry(temp_r31, 0x14, temp_r31->unkEA[arg1].unk02, temp_r31->unkEA[arg1].unk04);
    temp_r31->unk00 = 3;
    temp_r31->unkD6 = arg1;
    while (temp_r31->unk00 != 0) {
        HuPrcVSleep();
    }
    return temp_r31->unkD6;
}

s16 HuWinChoiceNumGet(s16 arg0) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    return temp_r31->unkD4;
}

void HuWinChoiceDisable(s16 arg0, s16 arg1) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    temp_r31->unkDA[arg1] = 1;
}

s16 HuWinChoiceNowGet(s16 arg0) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    if (temp_r31->unk00 == 3) {
        return temp_r31->unkD6;
    } else {
        return -1;
    }
}

void HuWinMesWait(s16 arg0) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    while (temp_r31->unk00 != 0) {
        HuPrcVSleep();
    }
}

void HuWinAnimSet(s16 arg0, AnimData* arg1, s16 arg2, f32 arg3, f32 arg4) {
    SomeWindowStruct* temp_r31 = &winData[arg0];
    s16 temp_r30;

    temp_r30 = HuSprCreate(arg1, temp_r31->unk48 - 1, arg2);
    HuWinSprSet(arg0, temp_r30, arg3, arg4);
}

s16 HuWinSprSet(s16 arg0, s16 arg1, f32 arg2, f32 arg3) {
    SomeWindowStruct* temp_r31 = &winData[arg0];
    SpriteGroupData* temp_r29 = &HuSprGrpData[temp_r31->unk04];
    s16 var_r30;

    for (var_r30 = 2; var_r30 <= 9; var_r30++) {
        if (temp_r31->unk06[var_r30] == -1) {
            temp_r31->unk06[var_r30] = arg1;
            HuSprGrpMemberSet(temp_r31->unk04, var_r30, arg1);
            HuSprPosSet(temp_r31->unk04, var_r30, arg2 - temp_r29->center_x, arg3 - temp_r29->center_y);
            break;
        }
    }
    return var_r30;
}

void HuWinSprPosSet(s16 arg0, s16 arg1, f32 arg2, f32 arg3) {
    SomeWindowStruct* temp_r31 = &winData[arg0];
    SpriteGroupData* temp_r30 = &HuSprGrpData[temp_r31->unk04];

    HuSprPosSet(temp_r31->unk04, arg1, arg2 - temp_r30->center_x, arg3 - temp_r30->center_y);
}

void HuWinSprPriSet(s16 arg0, s16 arg1, s16 arg2) {
    SomeWindowStruct* temp_r31 = &winData[arg0];
    SpriteGroupData* sp10 = &HuSprGrpData[temp_r31->unk04];

    HuSprPriSet(temp_r31->unk04, arg1, arg2);
}

s16 HuWinSprIDGet(s16 arg0, s16 arg1) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    return temp_r31->unk06[arg1];
}

void HuWinSprKill(s16 arg0, s16 arg1) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    HuSprGrpMemberKill(temp_r31->unk04, arg1);
    temp_r31->unk06[arg1] = -1;
}

void HuWinDispOff(s16 arg0) {
    SomeWindowStruct* temp_r31 = &winData[arg0];
    s16 var_r30;

    for (var_r30 = 0; var_r30 < 30; var_r30++) {
        if (temp_r31->unk06[var_r30] != -1) {
            HuSprAttrSet(temp_r31->unk04, var_r30, 4);
        }
    }
    temp_r31->unk4C |= 8;
}

void HuWinDispOn(s16 arg0) {
    SomeWindowStruct* temp_r31 = &winData[arg0];
    s16 var_r30;

    for (var_r30 = 0; var_r30 < 30; var_r30++) {
        if (temp_r31->unk06[var_r30] != -1) {
            HuSprAttrReset(temp_r31->unk04, var_r30, 4);
        }
    }
    temp_r31->unk4C = temp_r31->unk4C & ~8;
}

void HuWinComKeyWait(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s16 arg4) {
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    if (arg3 == -1) {
        var_r31 = -1;
    } else {
        var_r31 = 0;
    }
    if (arg2 == -1) {
        var_r30 = -1;
    } else {
        var_r30 = 0;
    }
    if (arg1 == -1) {
        var_r29 = -1;
    } else {
        var_r29 = 0;
    }
    if (arg0 == -1) {
        var_r28 = -1;
    } else {
        var_r28 = 0;
    }
    _HuWinComKeySet(var_r28, var_r29, var_r30, var_r31, arg4);
    _HuWinComKeySet(arg0, arg1, arg2, arg3, 1);
}

void HuWinComKeySet(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    _HuWinComKeySet(arg0, arg1, arg2, arg3, 1);
}

void _HuWinComKeySet(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s16 arg4) {
    winComKeyBuf[comKeyIdx].unk04[0] = arg0;
    winComKeyBuf[comKeyIdx].unk04[1] = arg1;
    winComKeyBuf[comKeyIdx].unk04[2] = arg2;
    winComKeyBuf[comKeyIdx].unk04[3] = arg3;
    winComKeyBuf[comKeyIdx].unk00 = arg4;
    comKeyIdx++;
    comKeyIdx &= 0xFF;
}

void HuWinComKeyGet(s16 arg0, u32* arg1) {
    SomeWindowStruct* temp_r30 = &winData[arg0];
    s16 var_r31;

    if (comKeyIdx == comKeyIdxNow) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (!(temp_r30->unk02 & (1 << var_r31))) {
                arg1[var_r31] = HuPadDStkRep[var_r31] | HuPadBtnDown[var_r31];
            } else {
                arg1[var_r31] = 0;
            }
        }
    } else {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            arg1[var_r31] = winComKeyBuf[comKeyIdxNow].unk04[var_r31];
            if (arg1[var_r31] == 0xFFFFFFFF) {
                if (!(temp_r30->unk02 & (1 << var_r31))) {
                    arg1[var_r31] = HuPadDStkRep[var_r31] | HuPadBtnDown[var_r31];
                } else {
                    arg1[var_r31] = 0;
                }
            }
        }
        winComKeyBuf[comKeyIdxNow].unk00--;
        if (winComKeyBuf[comKeyIdxNow].unk00 <= 0) {
            comKeyIdxNow++;
            comKeyIdxNow &= 0xFF;
        }
    }
}

void HuWinComKeyReset(void) {
    comKeyIdx = comKeyIdxNow = 0;
}

void HuWinMesMaxSizeGet(s16 arg0, f32* arg1, ...) {
    s16 var_r31;
    u32 temp_r29;
    va_list list;

    winInsertF = 0;
    va_start(list, arg1);
    winMaxWidth = winMaxHeight = 0;
    for (var_r31 = 0; var_r31 < arg0; var_r31++) {
        temp_r29 = va_arg(list, u32);
        GetMesMaxSizeSub(temp_r29);
    }
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        mesWInsert[var_r31] = 0;
    }
    winTabSize = 0x18;
    cancelCRF = 0;
    arg1[0] = (winMaxWidth + 0x1F) & 0xFFF0;
    arg1[1] = winMaxHeight + 0x10;
    va_end(list);
}

void HuWinInsertMesSizeGet(s32 arg0, s16 arg1) {
    winInsertF = 1;
    winMaxWidth = winMaxHeight = 0;
    GetMesMaxSizeSub(arg0);
    mesWInsert[arg1] = winMaxWidth;
}

void HuWinMesSizeCancelCRSet(s32 arg0) {
    cancelCRF = arg0;
}

void HuWinMesMaxSizeBetGet(f32* arg0, u32 arg1, u32 arg2) {
    u32 var_r31;

    if (arg2 < arg1) {
        arg0[0] = arg0[1] = 100.0f;
    } else {
        winInsertF = 0;
        winMaxWidth = winMaxHeight = 0;
        for (var_r31 = arg1; var_r31 <= arg2; var_r31++) {
            GetMesMaxSizeSub(var_r31);
        }
        for (var_r31 = 0; var_r31 < 8; var_r31++) {
            mesWInsert[var_r31] = 0;
        }
        winTabSize = 0x18;
        cancelCRF = 0;
        arg0[0] = (winMaxWidth + 0x1F) & 0xFFF0;
        arg0[1] = winMaxHeight + 0x10;
    }
}

static void GetMesMaxSizeSub(u32 arg0) {
    s16 var_r28;
    s16 var_r29;
    s16 var_r30;
    u8* var_r24;
    s16 var_r23;
    s16 var_r27;
    s32 var_r26;
    u8* var_r31;

    var_r24 = 0;
    var_r26 = 0;
    if (arg0 > 0x80000000) {
        var_r23 = 0;
        var_r31 = (u8*) arg0;
    } else {
        var_r23 = 1;
        var_r31 = var_r24 = MessData_MesPtrGet(messDataPtr, arg0);
    }
    var_r28 = 0x1A;
    var_r30 = 0;
    while (*var_r31 != 0) {
        var_r27 = 0;
        var_r29 = fontWidthP[*var_r31] + 1;
        switch (*var_r31) {
            case 0x10:
            case 0x20:
                break;
            case 0x1E:
                var_r31++;
                var_r29 = 0;
                break;
            case 0xA:
                if (var_r26 != 0) {
                    if (cancelCRF == 0) {
                        if (winMaxWidth < var_r30) {
                            winMaxWidth = var_r30;
                        }
                        var_r30 = var_r29 = 0;
                        if (var_r31[1] != 0) {
                            var_r27 = 0x1A;
                        }
                    } else {
                        var_r29 = fontWidthP[0x10] + 1;
                    }
                }
                break;
            case 0xFF:
                var_r30 += var_r29;
                /* fallthrough */
            case 0xB:
                var_r26 = 0;
                if (winInsertF == 0) {
                    if (winMaxWidth < var_r30) {
                        winMaxWidth = var_r30;
                    }
                    if (winMaxHeight < var_r28) {
                        winMaxHeight = var_r28;
                    }
                    var_r28 = 0x1A;
                    var_r27 = 0;
                    var_r30 = var_r29 = 0;
                }
                break;
            case 0x1C:
                var_r31++;
                /* fallthrough */
            case 0xF:
            case 0x1D:
                var_r29 = 0;
                break;
            case 0xC:
                var_r29 = winTabSize * ((var_r30 + winTabSize) / winTabSize) - var_r30;
                break;
            case 0xE:
                var_r31++;
                var_r29 = spcFontTbl[*var_r31 - 1].unk06 + 1;
                break;
            case 0x1F:
                var_r31++;
                var_r29 = mesWInsert[*var_r31 - 1];
                break;
        }
        if ((*var_r31 != 0xFF && *var_r31 >= 0x20) || *var_r31 == 0x10) {
            var_r26 = 1;
        }
        var_r30 += var_r29;
        var_r28 += var_r27;
        var_r31++;
    }
    if (winMaxWidth < var_r30) {
        winMaxWidth = var_r30;
    }
    if (winMaxHeight < var_r28) {
        winMaxHeight = var_r28;
    }
}

static s32 GetMesMaxSizeSub2(SomeWindowStruct* arg0, u8* arg1) {
    s32 sp8;
    u8 var_r26;
    s16 var_r28;
    s16 var_r29;
    s16 var_r30;
    s32 var_r27;
    s16 var_r25;
    u8* var_r31;

    sp8 = 0;
    var_r27 = 0;
    var_r31 = arg1;
    var_r28 = 0x1A;
    var_r30 = 0;
    var_r26 = 0;
    while (*var_r31 != 0 && var_r26 == 0) {
        var_r25 = 0;
        var_r29 = fontWidthP[*var_r31] + 1;
        switch (*var_r31) {
            case 0x10:
            case 0x20:
                break;
            case 0xA:
                if (var_r27 != 0 && !(arg0->unk4C & 0x100)) {
                    var_r29 = 0;
                    var_r26 = 1;
                }
                break;
            case 0xFF:
                var_r30 += var_r29;
                /* fallthrough */
            case 0xB:
                var_r27 = 0;
                var_r28 = 0x1A;
                var_r25 = 0;
                var_r30 = var_r29 = 0;
                break;
            case 0x1C:
            case 0x1E:
                var_r31++;
                /* fallthrough */
            case 0xF:
            case 0x1D:
                var_r29 = 0;
                break;
            case 0xC:
                var_r29 = winTabSize * ((var_r30 + winTabSize) / winTabSize) - var_r30;
                break;
            case 0xE:
                var_r31++;
                var_r29 = spcFontTbl[*var_r31 - 1].unk06 + 1;
                break;
            case 0x1F:
                var_r31++;
                break;
        }
        if ((*var_r31 != 0xFF && *var_r31 >= 0x20) || *var_r31 == 0x10) {
            var_r27 = 1;
        }
        var_r30 += var_r29;
        var_r28 += var_r25;
        var_r31++;
    }
    return var_r30;
}

s32 HuWinKeyWaitNumGet(u32 arg0) {
    s32 var_r30;
    u8* var_r31;

    if (arg0 > 0x80000000) {
        var_r31 = (u8*) arg0;
    } else {
        var_r31 = MessData_MesPtrGet(messDataPtr, arg0);
    }
    for (var_r30 = 0; *var_r31 != 0; var_r31++) {
        if (*var_r31 == 0xFF) {
            var_r30++;
        }
    }
    return var_r30;
}

void HuWinPushKeySet(s16 arg0, s16 arg1) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    temp_r31->unk154 = arg1;
}

void HuWinDisablePlayerSet(s16 arg0, u8 arg1) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    temp_r31->unk02 |= arg1;
}

void HuWinDisablePlayerReset(s16 arg0, s32 arg1) {
    SomeWindowStruct* temp_r31 = &winData[arg0];

    temp_r31->unk02 &= ~arg1;
}

void HuWinExCreate(f32 arg0, f32 arg1, s16 arg2, s16 arg3, s16 arg4) {
    HuWinExCreateStyled(arg0, arg1, arg2, arg3, arg4, 0);
}

static s32 winPortraitTbl[] = {
    0x0086000F,
    0x00860010,
    0x00860011,
    0x00860012,
    0x00860013,
    0x00860014,
    0x00860015,
    0x00860016,
    0x00860017,
    0x00860018,
    0x00860019,
    0x0086001A,
    0x0086001B,
    0x00860009,
    0x0086000A,
    0x0086000B,
    0x0086000C,
    0x0086000D,
    0x0086000E
};

static inline void HuWinExCreateStyledInlineFunc(s16 arg0, s16 arg1, f32 arg2, f32 arg3) {
    s16 var_1;
    AnimData* var_2;
    SomeWindowStruct* var_3;
    void* var_4;

    var_4 = HuAR_ARAMtoMRAMFileRead(winPortraitTbl[arg1], 0x10000000, 2);
    var_2 = HuSprAnimRead(var_4);
    var_3 = &winData[arg0];
    var_1 = HuSprCreate(var_2, var_3->unk48 - 1, 0);
    HuWinSprSet(arg0, var_1, arg2, arg3);
}

s16 HuWinExCreateStyled(f32 arg0, f32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    SomeWindowStruct* temp_r24;
    s16 temp_r28;

    if (arg4 >= 0) {
        arg3 = (arg3 < 0x54) ? 0x54 : arg3;
    }
    temp_r28 = HuWinCreate(arg0, arg1, arg2, arg3, arg5);
    temp_r24 = &winData[temp_r28];
    if (arg5 == 1) {
        temp_r24->unk62 = 9;
    }
    if (arg4 >= 0) {
        HuWinExCreateStyledInlineFunc(temp_r28, arg4, 48.0f, 48.0f);
    }
    HuWinDispOff(temp_r28);
    return temp_r28;
}

void HuWinExAnimIn(s16 arg0) {
    SomeWindowStruct* temp_r31 = &winData[arg0];
    s16 var_r30;
    s16 temp_r22;

    _HuWinHomeClear(temp_r31);
    if (temp_r31->unk06[2] == -1) {
        HuSprScaleSet(temp_r31->unk04, 0, 1.0f, 0.0f);
        HuWinDispOn(arg0);
        for (var_r30 = 0; var_r30 <= 10; var_r30++) {
            HuSprScaleSet(temp_r31->unk04, 0, 1.0f, 1.0 - 1.1 * cos(M_PI * (9.0f * var_r30) / 180.0));
            HuPrcVSleep();
        }
        HuSprScaleSet(temp_r31->unk04, 0, 1.0f, 1.0f);
    } else {
        HuSprScaleSet(temp_r31->unk04, 0, 1.0f, 0.0f);
        HuSprScaleSet(temp_r31->unk04, 2, 1.0f, 0.0f);
        HuWinDispOn(arg0);
        for (var_r30 = 0; var_r30 <= 20; var_r30++) {
            if (var_r30 <= 10) {
                HuSprScaleSet(temp_r31->unk04, 0, 1.0f, 1.1 * (1.0 - cos(M_PI * (9.0f * var_r30) / 180.0)));
            } else {
                HuSprScaleSet(temp_r31->unk04, 0, 1.0f, 1.0f);
            }
            if (var_r30 > 10) {
                temp_r22 = var_r30 - 10;
                HuSprScaleSet(temp_r31->unk04, 2, 1.0f, 1.0 - 1.1 * cos(M_PI * (9.0f * temp_r22) / 180.0));
            }
            HuPrcVSleep();
        }
        HuSprScaleSet(temp_r31->unk04, 2, 1.0f, 1.0f);
    }
}

void HuWinExAnimOut(s16 arg0) {
    SomeWindowStruct* temp_r31 = &winData[arg0];
    s16 var_r24;
    s16 var_r30;
    s16 temp_r22;

    _HuWinHomeClear(temp_r31);
    if (temp_r31->unk06[2] == -1) {
        for (var_r30 = 0; var_r30 <= 10; var_r30++) {
            HuSprScaleSet(temp_r31->unk04, 0, 1.0f, cos(M_PI * (9.0f * var_r30) / 180.0));
            HuPrcVSleep();
        }
        HuWinDispOff(arg0);
    } else {
        for (var_r30 = 0; var_r30 <= 15; var_r30++) {
            if (var_r30 <= 10) {
                HuSprScaleSet(temp_r31->unk04, 2, 1.0f, cos(M_PI * (9.0f * var_r30) / 180.0));
            }
            if (var_r30 > 5) {
                temp_r22 = var_r30 - 5;
                HuSprScaleSet(temp_r31->unk04, 0, 1.0f, cos(M_PI * (9.0f * temp_r22) / 180.0));
            }
            HuPrcVSleep();
        }
        HuWinDispOff(arg0);
    }
}

void HuWinExCleanup(s16 arg0) {
    HuWinKill(arg0);
}

void HuWinExAnimPopIn(s16 arg0, s16 arg1) {
    SomeWindowStruct* temp_r28 = &winData[arg0];
    s16 var_r30;

    for (var_r30 = 0; var_r30 <= 10; var_r30++) {
        HuSprScaleSet(temp_r28->unk04, 2, 1.0f, cos(M_PI * (9.0f * var_r30) / 180.0));
        HuPrcVSleep();
    }
    HuWinSprKill(arg0, 2);
    HuWinExCreateStyledInlineFunc(arg0, arg1, 48.0f, 48.0f);
    for (var_r30 = 0; var_r30 <= 10; var_r30++) {
        HuSprScaleSet(temp_r28->unk04, 2, 1.0f, sin(M_PI * (9.0f * var_r30) / 180.0));
        HuPrcVSleep();
    }
    HuSprScaleSet(temp_r28->unk04, 2, 1.0f, 1.0f);
}
