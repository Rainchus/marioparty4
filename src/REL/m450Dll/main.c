#include "REL/executor.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/wipe.h"

#include "game/gamework_data.h"

#include "game/mapspace.h"
#include "game/pad.h"
#include "game/printfunc.h"

#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"

#include "game/esprite.h"
#include "game/sprite.h"

#include "ext_math.h"
#include "rel_sqrt_consts.h"

#undef ABS
#define ABS(x) ((0 > (x)) ? -(x) : (x))

typedef struct unk_bss_358_struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ struct unk_bss_358_struct *unk04;
    /* 0x08 */ struct unk_bss_358_struct *unk08;
} UnkBss358Struct; // Size 0xC

typedef struct unk_bss_340_struct {
    /* 0x00 */ HsfanimStruct00 *unk00;
    /* 0x04 */ s32 *unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ struct unk_bss_340_struct *unk10;
    /* 0x14 */ struct unk_bss_340_struct *unk14;
} UnkBss340Struct; // Size 0x18

typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ s16 unk04;
} UnkBss1B0Struct; // Size 8

UnkBss358Struct lbl_1_bss_358;
UnkBss340Struct lbl_1_bss_340;
Process *lbl_1_bss_33C;
Vec lbl_1_bss_330;
Vec lbl_1_bss_324;
Vec lbl_1_bss_318;
Vec lbl_1_bss_30C;
u32 lbl_1_bss_308;
s32 lbl_1_bss_304;
u32 lbl_1_bss_300;
s16 lbl_1_bss_2FE;
s16 lbl_1_bss_2FC;
s32 lbl_1_bss_2F8;
s32 lbl_1_bss_2F4;
float lbl_1_bss_2F0;
s32 lbl_1_bss_2B0[16];
UnkBss1B0Struct lbl_1_bss_1B0[32];

void fn_1_0(void)
{
    lbl_1_bss_358.unk04 = NULL;
    lbl_1_bss_358.unk08 = NULL;
}

void fn_1_24(u16 arg0, s16 arg1)
{
    UnkBss358Struct *temp_r31;
    UnkBss358Struct *temp_r30;
    UnkBss358Struct *temp_r29;

    temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r31), MEMORY_DEFAULT_NUM);
    temp_r31->unk00 = arg0;
    temp_r31->unk02 = arg1;
    temp_r30 = &lbl_1_bss_358;
    temp_r29 = temp_r30->unk08;
    temp_r30->unk08 = temp_r31;
    if (NULL != temp_r29) {
        temp_r29->unk04 = temp_r31;
    }
    temp_r31->unk04 = temp_r30;
    temp_r31->unk08 = temp_r29;
}

s16 fn_1_AC(s16 arg0)
{
    UnkBss358Struct *var_r31;
    UnkBss358Struct *temp_r29;
    UnkBss358Struct *temp_r30;
    s16 temp_r28;

    var_r31 = lbl_1_bss_358.unk08;
    while (NULL != var_r31) {
        if (arg0 == var_r31->unk00) {
            temp_r28 = var_r31->unk02;
            temp_r29 = var_r31->unk04;
            temp_r30 = var_r31->unk08;
            temp_r29->unk08 = temp_r30;
            if (NULL != temp_r30) {
                temp_r30->unk04 = temp_r29;
            }
            HuMemDirectFree(var_r31);
            return temp_r28;
        }
        var_r31 = var_r31->unk08;
    }
    return -1;
}

void fn_1_150(void)
{
    lbl_1_bss_340.unk10 = NULL;
    lbl_1_bss_340.unk14 = NULL;
}

void fn_1_174(s16 arg0, HsfanimStruct00 *arg1, s32 arg2, s32 arg3, s32 arg4, Vec *arg5, u8 arg6)
{
    UnkBss340Struct *temp_r27;
    UnkBss340Struct *var_r31;
    UnkBss340Struct *temp_r28;
    s32 i;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*var_r31), MEMORY_DEFAULT_NUM);
    var_r31->unk00 = arg1;
    var_r31->unk08 = arg3;
    var_r31->unk0C = arg4;
    var_r31->unk04 = HuMemDirectMallocNum(HEAP_SYSTEM, arg4 * sizeof(*var_r31->unk04), MEMORY_DEFAULT_NUM);
    for (i = 0; i < arg4; i++, arg5++) {
        var_r31->unk04[i] = Hu3DParManLink(arg0, arg1);
        if (var_r31->unk04[i] >= 0) {
            Hu3DParManAttrReset(var_r31->unk04[i], 1);
            Hu3DParManPosSet(var_r31->unk04[i], arg5->x, arg5->y, arg5->z);
            Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(var_r31->unk04[i]), arg6);
            Hu3DModelLayerSet(Hu3DParManModelIDGet(var_r31->unk04[i]), arg2);
        }
    }
    temp_r28 = &lbl_1_bss_340;
    temp_r27 = temp_r28->unk14;
    temp_r28->unk14 = var_r31;
    if (NULL != temp_r27) {
        temp_r27->unk10 = var_r31;
    }
    var_r31->unk10 = temp_r28;
    var_r31->unk14 = temp_r27;
}

void fn_1_2D8(void)
{
    UnkBss340Struct *var_r31;
    UnkBss340Struct *temp_r28;
    UnkBss340Struct *temp_r29;
    s32 i;

    var_r31 = lbl_1_bss_340.unk14;
    while (NULL != var_r31) {
        var_r31->unk08--;
        if (var_r31->unk08 == 0) {
            for (i = 0; i < var_r31->unk0C; i++) {
                if (var_r31->unk04[i] >= 0) {
                    Hu3DParManAttrSet(var_r31->unk04[i], 1);
                }
            }
        }
        temp_r28 = var_r31->unk10;
        temp_r29 = var_r31->unk14;
        if (-var_r31->unk00->unk00 > var_r31->unk08) {
            for (i = 0; i < var_r31->unk0C; i++) {
                if (var_r31->unk04[i] >= 0) {
                    Hu3DParManKill(var_r31->unk04[i]);
                }
            }
            temp_r28->unk14 = temp_r29;
            if (NULL != temp_r29) {
                temp_r29->unk10 = temp_r28;
            }
            HuMemDirectFree(var_r31->unk04);
            HuMemDirectFree(var_r31);
        }
        var_r31 = temp_r29;
    }
}

void fn_1_414(void)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        lbl_1_bss_1B0[i].unk00 = 0;
        lbl_1_bss_1B0[i].unk04 = -1;
    }
}

s16 fn_1_46C(s32 arg0)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        if (arg0 == lbl_1_bss_1B0[i].unk00) {
            return Hu3DModelLink(lbl_1_bss_1B0[i].unk04);
        }
    }
    for (i = 0; i < 32; i++) {
        if (lbl_1_bss_1B0[i].unk00 == 0) {
            lbl_1_bss_1B0[i].unk00 = arg0;
            lbl_1_bss_1B0[i].unk04 = Hu3DModelCreateFile(arg0);
            return lbl_1_bss_1B0[i].unk04;
        }
    }
    return Hu3DModelCreateFile(arg0);
}

void fn_1_580(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 var_r30;

    espBankSet(arg0[arg1 + 1], 10);
    espBankSet(arg0[arg1 + 4], 11);
    if (36000 <= arg2) {
        arg2 = 35999;
    }
    var_r30 = arg2 / 3600;
    arg2 -= var_r30 * 3600;
    if (var_r30 > 9) {
        var_r30 = 9;
    }
    espBankSet(arg0[arg1], var_r30);
    var_r30 = arg2 / 60;
    arg2 -= var_r30 * 60;
    espBankSet(arg0[arg1 + 2], var_r30 / 10);
    espBankSet(arg0[arg1 + 3], var_r30 % 10);
    var_r30 = 101.5f * arg2 / 60.0f;
    espBankSet(arg0[arg1 + 5], var_r30 / 10);
    espBankSet(arg0[arg1 + 6], var_r30 % 10);
}

void fn_1_798(s32 arg0)
{
    lbl_1_bss_2F0 = 0.0f;
    lbl_1_bss_300 = lbl_1_bss_304;
    GWMGRecordSet(arg0, lbl_1_bss_300);
    fn_1_580(lbl_1_bss_2B0, 7, lbl_1_bss_304);
}

void fn_1_9EC(void)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        espDispOn(lbl_1_bss_2B0[i]);
    }
}

void fn_1_A40(void)
{
    float temp_f31;
    s32 i;

    if (0.0f <= lbl_1_bss_2F0) {
        lbl_1_bss_2F0 += 16.0f;
        temp_f31 = 1.0 + 0.2f * sind(lbl_1_bss_2F0);
        for (i = 7; i <= 14; i++) {
            espScaleSet(lbl_1_bss_2B0[i], temp_f31, temp_f31);
        }
    }
}

void fn_1_B4C(float arg0, s32 arg1)
{
    float temp_f30;
    float temp_f31;
    s32 i;

    temp_f31 = 288.0f;
    temp_f30 = arg0;
    lbl_1_bss_2B0[15] = espEntry(arg1, 0, 0);
    espTPLvlSet(lbl_1_bss_2B0[15], 0.5f);
    espColorSet(lbl_1_bss_2B0[15], 0, 0, 0);
    espPosSet(lbl_1_bss_2B0[15], temp_f31, temp_f30);
    temp_f31 = 248.0f;
    temp_f30 = arg0 - 8.0f;
    lbl_1_bss_2B0[14] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 55), 0, 0);
    espPosSet(lbl_1_bss_2B0[14], temp_f31 - 18.0f, temp_f30);
    for (i = 7; i <= 13; i++) {
        lbl_1_bss_2B0[i] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 48), 0, 0);
        espPosSet(lbl_1_bss_2B0[i], temp_f31, temp_f30);
        temp_f31 += 16.0f;
    }
    fn_1_580(lbl_1_bss_2B0, 7, lbl_1_bss_300);
    temp_f31 = 248.0f;
    temp_f30 = arg0 + 8.0f;
    for (i = 0; i <= 6; i++) {
        lbl_1_bss_2B0[i] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 49), 0, 0);
        espPosSet(lbl_1_bss_2B0[i], temp_f31, temp_f30);
        temp_f31 += 16.0f;
    }
    fn_1_580(lbl_1_bss_2B0, 0, 0);
    for (i = 0; i < 16; i++) {
        espDrawNoSet(lbl_1_bss_2B0[i], 0);
        espDispOff(lbl_1_bss_2B0[i]);
        espAttrSet(lbl_1_bss_2B0[i], HUSPR_ATTR_NOANIM);
        espPriSet(lbl_1_bss_2B0[i], 0x80 + i);
    }
}

void fn_1_11F4(float arg0, Vec *arg1, Vec *arg2, Vec *arg3)
{
    float temp_f31;

    if (1.0f < arg0) {
        arg0 = 1.0f;
    }
    temp_f31 = sind(90.0f * arg0) * sind(90.0f * arg0);
    arg3->x = arg1->x + temp_f31 * (arg2->x - arg1->x);
    arg3->y = arg1->y + temp_f31 * (arg2->y - arg1->y);
    arg3->z = arg1->z + temp_f31 * (arg2->z - arg1->z);
}

void fn_1_1350(Vec *arg0, Vec *arg1, Vec *arg2)
{
    Hu3DCameraPosSetV(1, arg0, arg1, arg2);
    lbl_1_bss_330 = *arg0;
    lbl_1_bss_318 = *arg2;
}

s32 fn_1_13DC(float arg0, Vec *arg1)
{
    Vec sp18;
    Vec spC;

    fn_1_11F4(arg0, &lbl_1_bss_330, &lbl_1_bss_324, &sp18);
    fn_1_11F4(arg0, &lbl_1_bss_318, &lbl_1_bss_30C, &spC);
    Hu3DCameraPosSetV(1, &sp18, arg1, &spC);
    if (1.0f <= arg0) {
        return 1;
    }
    else {
        lbl_1_bss_2F4 = 1;
        return 0;
    }
}

void fn_1_1710(float arg0, Vec *arg1)
{
    Vec sp18;
    Vec spC;

    fn_1_11F4(arg0, &lbl_1_bss_330, &lbl_1_bss_324, &sp18);
    fn_1_11F4(arg0, &lbl_1_bss_318, &lbl_1_bss_30C, &spC);
    fn_1_1350(&sp18, arg1, &spC);
    lbl_1_bss_2F4 = 1;
}

void fn_1_1A60(Vec *arg0, s16 arg1, Vec *arg2)
{
    Mtx sp1C;
    Vec sp10;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float temp_f31;
    CameraData *temp_r31;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg1 & (1 << i)) {
            break;
        }
    }
    temp_r31 = &Hu3DCamera[i];
    MTXLookAt(sp1C, &temp_r31->pos, &temp_r31->up, &temp_r31->target);
    MTXMultVec(sp1C, arg0, &sp10);
    temp_f30 = sp10.z * (sind(temp_r31->fov / 2) / cosd(temp_r31->fov / 2)) * temp_r31->aspect;
    temp_f29 = sp10.z * (sind(temp_r31->fov / 2) / cosd(temp_r31->fov / 2));
    temp_f28 = 0.9f * temp_r31->viewport_x;
    temp_f31 = 0.9f * temp_r31->viewport_w;
    arg2->x = temp_f31 / 2 + sp10.x * ((temp_f31 / 2) / -temp_f30) + temp_f28;
    arg2->y = temp_r31->viewport_h / 2 + sp10.y * ((temp_r31->viewport_h / 2) / temp_f29) + temp_r31->viewport_y;
    arg2->z = 0.0f;
}

void fn_1_1D18(s16 arg0, char *arg1, Vec *arg2)
{
    Mtx sp10;

    Hu3DModelObjMtxGet(arg0, arg1, sp10);
    arg2->x = sp10[0][3];
    arg2->y = sp10[1][3];
    arg2->z = sp10[2][3];
}

void fn_1_1D70(s16 arg0, char *arg1, Vec *arg2, Mtx arg3)
{
    Mtx spC;
    ModelData *var_r30;

    var_r30 = &Hu3DData[arg0];
    Hu3DModelObjMtxGet(arg0, arg1, spC);
    PSMTXConcat(var_r30->unk_F0, spC, spC);
    if (NULL != arg3) {
        PSMTXCopy(spC, arg3);
    }
    arg2->x = spC[0][3];
    arg2->y = spC[1][3];
    arg2->z = spC[2][3];
}

float fn_1_1E20(float arg0, float arg1, float arg2)
{
    float var_f31;
    float var_f30;

    var_f31 = fmod(arg1 - arg0, 360.0);
    if (0.0f > var_f31) {
        var_f31 += 360.0f;
    }
    if (180.0f < var_f31) {
        var_f31 -= 360.0f;
    }
    var_f30 = fmod(arg0 + var_f31 * arg2, 360.0);
    if (0.0f > var_f30) {
        var_f30 += 360.0f;
    }
    return var_f30;
}

void fn_1_1F24(s32 arg0)
{
    lbl_1_bss_2F8 = HuAudSeqPlay((s32)arg0);
}

void fn_1_1F58(s32 arg0)
{
    if (lbl_1_bss_2F8 >= 0) {
        if (arg0 < 0) {
            arg0 = 1000;
        }
        HuAudSeqFadeOut(lbl_1_bss_2F8, arg0);
    }
    lbl_1_bss_2F8 = -1;
}

void fn_1_1FC4(Vec *arg0, float *arg1, s32 arg2, s32 arg3)
{
    Vec sp18;
    float var_f28;
    s32 var_r30;

    sp18.x = 0.0f;
    sp18.y = 0.0f;
    sp18.z = 0.0f;
    sp18.x = arg2 / 4.0f;
    sp18.z = -(float)arg3 / 4.0f;
    var_r30 = 0;
    var_f28 = VECMagXZ(&sp18);
    if (0.5f <= var_f28) {
        if (10.0f <= var_f28) {
            sp18.x /= var_f28;
            sp18.z /= var_f28;
            var_f28 = 10.0f;
            sp18.x = 10.0f * sp18.x;
            sp18.z = 10.0f * sp18.z;
        }
        *arg1 = fn_1_1E20(*arg1, atan2d(sp18.x, sp18.z), 0.4f);
        if (8.0f <= var_f28) {
            var_r30 = 2;
        }
        else {
            var_r30 = 1;
        }
    }
    VECAdd((Vec *)&arg0, &sp18, (Vec *)&arg0);
}
