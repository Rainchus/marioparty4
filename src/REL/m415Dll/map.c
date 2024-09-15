#include "REL/m415Dll.h"

#include "game/hsfdraw.h"

void fn_1_8780(s16 arg0, s16 arg1) {
    s32 var_r31;
    unkSubStruct2* var_r29;
    unkSubStruct3* var_r30;

    lbl_1_bss_36C.unk34 = Hu3DHookFuncCreate(fn_1_95C0);
    Hu3DModelLayerSet(lbl_1_bss_36C.unk34, 6);
    lbl_1_bss_36C.unk30 = arg0;
    lbl_1_bss_36C.unk40 = var_r29 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(unkSubStruct2), 0x10000000);
    lbl_1_bss_36C.unk32 = arg1;
    lbl_1_bss_36C.unk3C = var_r30 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(unkSubStruct3), 0x10000000);
    
    for (var_r31 = 0; var_r31 < arg0; var_r31++, var_r29++) {
        var_r29->unk8 = 0;
    }
    
    for (var_r31 = 0; var_r31 < arg1; var_r31++, var_r30++) {
        var_r30->unk6 = 0;
        var_r30->unk8 = 0;
    }
    lbl_1_bss_36C.unk36 = lbl_1_bss_36C.unk38 = lbl_1_bss_36C.unk3A = 0;
}

void fn_1_88B8(unkSubStruct2* arg0) {
    ModelData sp120;
    Mtx spF0;
    Mtx spC0;
    Mtx sp90;
    Mtx sp60;
    Mtx sp30;
    GXColor sp2C;
    s16 sp8;
    s32 var_r25;
    s32 var_r27;
    s16 temp_r23;
    s16 var_r28;
    s16 var_r29;
    s32 var_r24;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;
    s32 var_r19;
    unkSubStruct3* temp_r26;
    unkSubStruct* var_r31;

    mtxRot(sp60, arg0->unk18.x, arg0->unk18.y, arg0->unk18.z);
    MTXScale(sp90, arg0->unk24.x, arg0->unk24.y, arg0->unk24.z);
    MTXConcat(sp60, sp90, sp90);
    mtxTransCat(sp90, arg0->unkC.x, arg0->unkC.y, arg0->unkC.z);
    MTXConcat(Hu3DCameraMtx, sp90, spC0);
    var_r29 = 0;
    var_r28 = 0;
    sp8 = 0;
    
    for (var_r27 = GX_TEXMAP0; var_r27 < arg0->unk4; var_r27++) {
        if (arg0->unk34[var_r27] != 0) {
            temp_r26 = &lbl_1_bss_36C.unk3C[arg0->unk34[var_r27]];
            MTXCopy(temp_r26->unk18, sp30);
            mtxTransCat(sp30, temp_r26->unkC.x, temp_r26->unkC.y, temp_r26->unkC.z);
            switch (temp_r26->unk4) {
                case 0:
                    GXLoadTexMtxImm(sp30, texMtxTbl[var_r28], GX_MTX2x4);
                    var_r22 = texMtxTbl[var_r28];
                    GXSetTexCoordGen2(var_r28, GX_TG_MTX2x4, var_r27 + 4, var_r22, 0, 0x7D);
                    GXSetTevOrder(var_r29, var_r28, var_r27, GX_COLOR0A0);
                    if (var_r27 == GX_TEXMAP0) {
                        if ((temp_r26->unk0->bmp->dataFmt == 7) || (temp_r26->unk0->bmp->dataFmt == 8)) {
                            GXSetTevColor(GX_TEVREG2, temp_r26->unk48);
                            GXSetTevColorIn(var_r29, GX_CC_ZERO, GX_CC_C2, GX_CC_RASC, GX_CC_ZERO);
                        } else {
                            GXSetTevColorIn(var_r29, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                        }
                        GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
                    } else {
                        sp2C.a = temp_r26->unk48.a;
                        GXSetTevColor(GX_TEVREG2, sp2C);
                        GXSetTevColorIn(var_r29, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A2, GX_CC_ZERO);
                        GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
                    }
                    GXSetTevColorOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    GXSetTevAlphaOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    break;
                case 1:
                    GXLoadTexMtxImm(sp30, texMtxTbl[var_r28], GX_MTX2x4);
                    var_r21 = texMtxTbl[var_r28];
                    GXSetTexCoordGen2(var_r28, GX_TG_MTX2x4, var_r27 + 4, var_r21, 0, 0x7D);
                    GXSetTevOrder(var_r29, var_r28, var_r27, GX_COLOR0A0);
                    GXSetTevColorIn(var_r29, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXA, GX_CC_ZERO);
                    GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
                    GXSetTevColorOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    GXSetTevAlphaOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    break;
                case 2:
                    sp2C.a = 0xE0;
                    GXSetTevColor(GX_TEVREG1, sp2C);
                    GXSetTexCoordGen2(var_r28 + 1, GX_TG_BUMP0, var_r28, 0x3C, 0, 0x7D);
                    GXSetTevOrder(var_r29, var_r28, var_r27, GX_COLOR0A0);
                    GXSetTevColorIn(var_r29, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A1, GX_CC_RASC);
                    GXSetTevColorOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                    GXSetTevAlphaOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV);
                    var_r29++;
                    GXSetTevOrder(var_r29, var_r28 + 1, GX_TEXMAP0, GX_COLOR0A0);
                    GXSetTevColorIn(var_r29, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A1, GX_CC_CPREV);
                    GXSetTevColorOp(var_r29, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                    GXSetTevAlphaOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV);
                    break;
                case 3:
                    var_r28--;
                    GXLoadTexMtxImm(sp30, texMtxTbl[var_r28], GX_MTX2x4);
                    var_r20 = texMtxTbl[var_r28];
                    GXSetTexCoordGen2(var_r28, GX_TG_MTX2x4, var_r27 + 4, var_r20, 0, 0x7D);
                    GXSetTevOrder(var_r29, var_r28, var_r27, GX_COLOR0A0);
                    GXSetTevColorIn(var_r29, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
                    GXSetTevColorOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
                    GXSetTevAlphaOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    var_r28++;
                    break;
                case 4:
                    mtxRot(sp60, arg0->unk18.x, arg0->unk18.y, arg0->unk18.z);
                    MTXScale(sp90, arg0->unk24.x, arg0->unk24.y, arg0->unk24.z);
                    MTXConcat(sp60, sp90, sp90);
                    mtxTransCat(sp90, arg0->unkC.x, arg0->unkC.y, arg0->unkC.z);
                    MTXConcat(Hu3DCameraMtx, sp90, sp30);
                    MTXInverse(Hu3DCameraMtx, sp60);
                    MTXConcat(sp60, sp30, sp60);
                    MTXConcat(Hu3DShadowData.unk_68, Hu3DShadowData.unk_38, sp90);
                    MTXConcat(sp90, sp60, sp30);
                    GXLoadTexMtxImm(sp30, texMtxTbl[var_r28], GX_MTX3x4);
                    var_r19 = texMtxTbl[var_r28];
                    GXSetTexCoordGen2(var_r28, GX_TG_MTX3x4, GX_TG_POS, var_r19, 0, 0x7D);
                    GXSetTevOrder(var_r29, var_r28, var_r27, GX_COLOR0A0);
                    if (var_r27 == GX_TEXMAP0) {
                        GXSetTevColorIn(var_r29, GX_CC_ONE, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ZERO);
                        GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
                    } else {
                        GXSetTevColorIn(var_r29, GX_CC_CPREV, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ZERO);
                        GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    }
                    GXSetTevColorOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    GXSetTevAlphaOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV);
                    break;
            }
            var_r29++;
            var_r28++;
            if (temp_r26->unk4D != 0) {
                HuSprTexLoad(temp_r26->unk0, 0, var_r27, 1, 1, 1);
            } else {
                HuSprTexLoad(temp_r26->unk0, 0, var_r27, 0, 0, 1);
            }
        }
    }
    GXSetNumTevStages((s16)var_r29);
    GXSetNumTexGens((s16)var_r28);
    var_r31 = arg0->unk3C;
    
    for (var_r24 = 0; var_r24 < arg0->unk2; var_r24++, var_r31++) {
        if ((var_r31->unk34 != 0) && ((var_r31->unk34 & 4) == 0)) {
            switch (var_r31->unk30) {
                case 0:
                    mtxRot(sp60, var_r31->unkC.x, var_r31->unkC.y, var_r31->unkC.z);
                    if (var_r31->unk31 == 2) {
                        MTXConcat(lbl_1_bss_36C.unk0, sp60, sp60);
                    } else if (var_r31->unk31 == 1) {
                        MTXRotDeg(sp90, 0x59, CRot.y);
                        MTXConcat(sp90, sp60, sp60);
                    }
                    MTXScale(sp90, var_r31->unk18.x, var_r31->unk18.y, var_r31->unk18.z);
                    MTXConcat(sp60, sp90, sp90);
                    mtxTransCat(sp90, var_r31->unk0.x, var_r31->unk0.y, var_r31->unk0.z);
                    MTXConcat(Hu3DCameraMtx, sp90, spF0);
                    break;
                case 1:
                    mtxRot(sp60, var_r31->unkC.x, var_r31->unkC.y, var_r31->unkC.z);
                    if (var_r31->unk31 == 2) {
                        if (HmfInverseMtxF3X3(spC0, sp90) == 0) {
                            MTXIdentity(sp90);
                        }
                        MTXConcat(sp90, sp60, sp60);
                    } else if (var_r31->unk31 == 1) {
                        MTXRotDeg(sp90, 0x59, CRot.y);
                        MTXConcat(sp90, sp60, sp60);
                    }
                    MTXScale(sp90, var_r31->unk18.x, var_r31->unk18.y, var_r31->unk18.z);
                    MTXConcat(sp60, sp90, sp90);
                    mtxTransCat(sp90, var_r31->unk0.x, var_r31->unk0.y, var_r31->unk0.z);
                    MTXConcat(spC0, sp90, spF0);
                    break;
            }
            GXLoadPosMtxImm(spF0, 0);
            MTXInverse(spF0, sp90);
            MTXTranspose(sp90, sp60);
            GXLoadNrmMtxImm(sp60, 0);
            GXSetChanAmbColor(GX_COLOR0A0, var_r31->unk4C);
            GXSetChanMatColor(GX_COLOR0A0, var_r31->unk50);
            GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
            GXSetZCompLoc(0);
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
            if ((var_r31->unk34 & 0x10) != 0) {
                GXSetZMode(0, GX_LEQUAL, 1);
            } else {
                GXSetZMode(1, GX_LEQUAL, 0);
            }
            sp120.attr = 0;
            temp_r23 = Hu3DLightSet(&sp120, &Hu3DCameraMtx, &Hu3DCameraMtxXPose, 0.0f);
            GXSetNumChans(1);
            if ((var_r31->unk34 & 8) != 0) {
                var_r25 = GX_SRC_VTX;
            } else {
                var_r25 = GX_SRC_REG;
            }
            switch (var_r31->unk32) {
                case 0:
                    GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, var_r25, 0, GX_DF_CLAMP, GX_AF_NONE);
                    break;
                case 1:
                    GXSetChanCtrl(GX_COLOR0A0, 1, GX_SRC_REG, var_r25, temp_r23, GX_DF_CLAMP, GX_AF_SPOT);
                    break;
                case 2:
                    GXSetChanCtrl(GX_COLOR0A0, 1, GX_SRC_REG, var_r25, temp_r23, GX_DF_CLAMP, GX_AF_SPEC);
                    break;
            }
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
            GXSetArray(GX_VA_POS, var_r31->unk40, 0xC);
            GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGBA8, 0);
            GXSetArray(GX_VA_CLR0, var_r31->unk44, 4);
            
            for (var_r27 = 0; var_r27 < var_r31->unk33; var_r27++) {
                GXSetVtxDesc(var_r27 + GX_VA_TEX0, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, var_r27 + GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
                GXSetArray(var_r27 + GX_VA_TEX0, var_r31->unk54[var_r27].unk4, 8);
            }
            GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_RGBA6, 0);
            GXSetArray(GX_VA_NRM, var_r31->unk48, 0xC);
            GXCallDisplayList(var_r31->unk3C, var_r31->unk38);
        }
    }
}

void fn_1_95C0(ModelData* arg0, Mtx arg1) {
    Mtx sp38;
    Mtx sp8;
    s32 var_r30;
    unkSubStruct2* var_r31;

    var_r31 = lbl_1_bss_36C.unk40;
    GXLoadPosMtxImm(arg1, 0);
    PSMTXInverse(arg1, sp38);
    PSMTXTranspose(sp38, sp8);
    GXLoadNrmMtxImm(sp8, 0);
    HmfInverseMtxF3X3(Hu3DCameraMtx, lbl_1_bss_36C.unk0);
    
    for (var_r30 = 0; var_r30 < lbl_1_bss_36C.unk30; var_r30++, var_r31++) {
        if ((var_r31->unk8 != 0) && ((var_r31->unk8 & 2) != 0) && ((var_r31->unk8 & 4) == 0)) {
            if ((u8)omPauseChk() == 0) {
                if (var_r31->unk30) {
                    var_r31->unk30(var_r31);
                }
                if (var_r31->unk8 == 0) continue;
                fn_1_9DC8(var_r31);
                if (var_r31->unk8 == 0) continue;
            }
            fn_1_88B8(var_r31);
        }
    }
}

unkSubStruct2* fn_1_96EC(s16 arg0) {
    return &lbl_1_bss_36C.unk40[arg0];
}

unkSubStruct* fn_1_9708(s16 arg0, s16 arg1) {
    return &lbl_1_bss_36C.unk40[arg0].unk3C[arg1];
}

AnimData** fn_1_9734(s16 arg0) {
    return &lbl_1_bss_36C.unk3C[arg0].unk0;
}

void fn_1_9750(unkStruct6** arg0, s16 arg1, f32 arg8, f32 arg9) {
    s32 var_r30;
    unkStruct6* var_r31;
    
    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(unkStruct6), 0x10000000);
    
    for (var_r30 = 0; var_r30 < arg1; var_r31++, var_r30++) {
        var_r31->unk0.x = (-0.5f * arg8);
        var_r31->unk0.y = (0.5f * arg9);
        var_r31->unk0.z = 0.0f;
        var_r31->unkC.x = (0.5f * arg8);
        var_r31->unkC.y = (0.5f * arg9);
        var_r31->unkC.z = 0.0f;
        var_r31->unk18.x = (0.5f * arg8);
        var_r31->unk18.y = (-0.5f * arg9);
        var_r31->unk18.z = 0.0f;
        var_r31->unk24.x = (-0.5f * arg8);
        var_r31->unk24.y = (-0.5f * arg9);
        var_r31->unk24.z = 0.0f;
    }
}

void fn_1_98D4(Vec** arg0, s16 arg1, Vec* arg2) {
    s32 var_r29;
    s32 var_r28;
    Vec* var_r31;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(Vec[4]), MEMORY_DEFAULT_NUM);
    
    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        for (var_r28 = 0; var_r28 < 4; var_r31++, arg2++, var_r28++) {
            var_r31->x = arg2->x;
            var_r31->y = arg2->y;
            var_r31->z = arg2->z;
        }
    }
}

void fn_1_9974(GXColor** arg0, s16 arg1, GXColor* arg2) {
    s32 var_r29;
    s32 var_r28;
    GXColor* var_r31;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(GXColor[4]), MEMORY_DEFAULT_NUM);
    
    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        for (var_r28 = 0; var_r28 < 4; var_r31++, arg2++, var_r28++) {
            var_r31->r = arg2->r;
            var_r31->g = arg2->g;
            var_r31->b = arg2->b;
            var_r31->a = arg2->a;
        }
    }
}

void fn_1_9A1C(Vec** arg0, s16 arg1, Vec* arg2) {
    s32 var_r29;
    Vec* var_r31;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    
    for (var_r29 = 0; var_r29 < arg1; var_r31++, arg2++, var_r29++) {
        var_r31->x = arg2->x;
        var_r31->y = arg2->y;
        var_r31->z = arg2->z;
    }
}

void fn_1_9AA8(HsfVector2f** arg0, s16 arg1, HsfVector2f* arg2) {
    s32 var_r28;
    s32 var_r29;
    HsfVector2f* var_r31;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(HsfVector2f[4]), MEMORY_DEFAULT_NUM);

    for (var_r28 = 0; var_r28 < arg1; var_r28++) {
        for (var_r29 = 0; var_r29 < 4; var_r31++, arg2++, var_r29++) {
            var_r31->x = arg2->x;
            var_r31->y = arg2->y;
        }
    }
}

void fn_1_9B40(unkSubStruct* arg0) {
    void* sp8;
    s32 var_r29;
    s32 var_r31;
    void* temp_r28;

    Vec sp1C[4] = {
        { -50.0f,  50.0f, 0.0f },
        {  50.0f,  50.0f, 0.0f },
        {  50.0f, -50.0f, 0.0f },
        { -50.0f, -50.0f, 0.0f }
    };
    GXColor spC[4] = {
        { 0xFF, 0xFF, 0xFF, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF }
    };
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        arg0->unk40[var_r31] = sp1C[var_r31];
    }
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        arg0->unk44[var_r31] = spC[var_r31];
    }
    arg0->unk48->x = 0.0f;
    arg0->unk48->y = 0.0f;
    arg0->unk48->z = 1.0;
    temp_r28 = arg0->unk3C;
    sp8 = temp_r28;
    GXBeginDisplayList(temp_r28, 0x100U);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        GXPosition1x16(var_r31);
        GXNormal1x16(0);
        GXColor1x16(var_r31);
        for (var_r29 = 0; var_r29 < arg0->unk33; var_r29++) {
            GXTexCoord1x16(var_r31);
        }
    }
    arg0->unk38 = GXEndDisplayList();
}

void fn_1_9DC8(unkSubStruct2* arg0) {
    s32 temp_r0;
    s32 var_r25;
    s32 var_r26;
    s32 var_r27;
    unkSubStruct* var_r28;
    unkSubStruct3* temp_r30;
    unkSubStruct4* var_r31;

    var_r27 = 0;
    var_r28 = arg0->unk3C;
    
    for (var_r25 = 0; var_r25 < arg0->unk2; var_r25++, var_r28++) {
        if ((var_r28->unk34 & 4) != 0) {
            var_r27++;
        } else {
            var_r31 = var_r28->unk54;
            
            for (var_r26 = 0; var_r26 < var_r28->unk33; var_r26++, var_r31++) {
                temp_r30 = &lbl_1_bss_36C.unk3C[arg0->unk34[var_r26]];
                var_r31->unk24 &= ~4;
                switch (var_r31->unk24 & 0xF) {
                    case 1:
                        var_r31->unk2C += var_r31->unk28;
                        if (var_r31->unk2C >= 1.0f) {
                            var_r31->unk0++;
                            var_r31->unk2C--;
                        }
                        break;
                    case 2:
                        var_r31->unk2C += var_r31->unk28;
                        if (var_r31->unk2C >= 1.0f) {
                            var_r31->unk0--;
                            var_r31->unk2C--;
                        }
                        break;
                }
                if (var_r31->unk0 >= temp_r30->unk4C) {
                    if ((var_r31->unk24 & 0x10) != 0) {
                        var_r31->unk24 |= 8;
                        var_r31->unk0--;
                    } else if ((var_r31->unk24 & 0x40) != 0) {
                        var_r31->unk24 = (var_r31->unk24 & 0xF0) | 2;
                        var_r31->unk0 -= 2;
                    } else if ((var_r31->unk24 & 0x20) != 0) {
                        var_r31->unk0 = 0;
                    }
                    var_r31->unk24 |= 4;
                } else if (var_r31->unk0 < 0) {
                    if ((var_r31->unk24 & 0x10) != 0) {
                        var_r31->unk24 |= 8;
                        var_r31->unk0 = 0;
                    } else if ((var_r31->unk24 & 0x20) != 0) {
                        if ((var_r31->unk24 & 0x40) != 0) {
                            var_r31->unk24 = (var_r31->unk24 & 0xF0) | 1;
                            var_r31->unk0 = 1;
                        } else {
                            var_r31->unk0 = temp_r30->unk4C - 1;
                        }
                    } else if ((var_r31->unk24 & 0x40) != 0) {
                        var_r31->unk24 |= 8;
                        var_r31->unk0 = 0;
                    }
                    var_r31->unk24 |= 4;
                } else {
                    var_r31->unk24 &= ~8;
                }
                if (var_r31->unk0 != var_r31->unk1) {
                    var_r31->unk4[0].y = var_r31->unk0 * temp_r30->unk58;
                    var_r31->unk4[1].y = var_r31->unk0 * temp_r30->unk58;
                    var_r31->unk4[2].y = ((var_r31->unk0 + 1) * temp_r30->unk58);
                    var_r31->unk4[3].y = ((var_r31->unk0 + 1) * temp_r30->unk58);
                    if ((var_r31->unk0 + 1) < temp_r30->unk4C) {
                        var_r31->unk4[2].y -= temp_r30->unk60;
                        var_r31->unk4[3].y -= temp_r30->unk60;
                    }
                    var_r31->unk1 = var_r31->unk0;
                }
                if ((var_r31->unk24 & 8) != 0) {
                    if ((var_r28->unk34 & 0x40000000) != 0) {
                        var_r28->unk34 |= 4;
                        if ((var_r31->unk24 & 0x40) == 0) {
                            if (var_r31->unk0 <= 0) {
                                var_r31->unk0 = temp_r30->unk4C;
                            } else {
                                var_r31->unk0 = 0;
                            }
                        }
                    } else if ((var_r28->unk34 & 0x80000000) != 0) {
                        fn_1_A800(arg0->unk0);
                    }
                    var_r27++;
                }
            }
        }
    }
    if (var_r27 >= arg0->unk2) {
        if ((arg0->unk8 & 0x40000000) != 0) {
            arg0->unk8 |= 4;
            return;
        }
        if ((arg0->unk8 & 0x80000000) != 0) {
            fn_1_A800(arg0->unk0);
        }
    }
}