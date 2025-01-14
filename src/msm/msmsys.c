#include "msm/msmsys.h"
#include "msm/msmfio.h"
#include "msm/msmmem.h"
#include "msm/msmmus.h"
#include "msm/msmse.h"
#include "msm/msmstream.h"

#include "game/msm.h" // TODO remove, only for decomp

static sysData sys;

static void msmSysServer(void)
{
    if (sndIsInstalled() == 1) {
        if (--sys.unk4F8 == 0) {
            sys.unk4F8 = 3;
            msmMusPeriodicProc();
            msmSePeriodicProc();
            msmStreamPeriodicProc();
        }
    }
    sys.unk4F4();
}

static s32 msmSysSetAuxParam(s32 arg0, s32 arg1)
{
    s32 unused_1[2];
    SND_AUX_CALLBACK sp20[2];
    s32 unused_2[2];
    unkSubStruct *temp_r4_2;
    UnkSndAuxUnion *temp_r3;
    u32 var_r0;
    s32 var_r23;

    if (sys.unk18[0] != -2 && arg0 >= 0) {
        sys.unk18[0] = arg0;
    }
    if (sys.unk18[1] != -2 && arg1 >= 0) {
        sys.unk18[1] = arg1;
    }
    if (sys.unk18[0] < 0 && sys.unk18[1] < 0) {
        return 0;
    }
    for (var_r23 = 0; var_r23 < 2; var_r23++) {
        if (sys.unk18[var_r23] < 0) {
            sp20[var_r23] = NULL;
            continue;
        }
        temp_r4_2 = &sys.unk14[sys.unk18[var_r23]];
        temp_r3 = &sys.unk1C[var_r23];
        switch (temp_r4_2->unk0) {
            case 0:
                sp20[var_r23] = sndAuxCallbackReverbHI;
                temp_r3->revHi.tempDisableFX = temp_r4_2->rev.tempDisableFX;
                temp_r3->revHi.coloration = temp_r4_2->rev.coloration;
                temp_r3->revHi.mix = temp_r4_2->rev.mix;
                temp_r3->revHi.time = temp_r4_2->rev.time;
                temp_r3->revHi.damping = temp_r4_2->rev.damping;
                temp_r3->revHi.preDelay = temp_r4_2->rev.preDelay;
                temp_r3->revHi.crosstalk = temp_r4_2->rev.crosstalk;
                var_r0 = sndAuxCallbackPrepareReverbHI(&temp_r3->revHi);
                break;
            case 1:
                sp20[var_r23] = sndAuxCallbackReverbSTD;
                temp_r3->revStd.tempDisableFX = temp_r4_2->rev.tempDisableFX;
                temp_r3->revStd.coloration = temp_r4_2->rev.coloration;
                temp_r3->revStd.mix = temp_r4_2->rev.mix;
                temp_r3->revStd.time = temp_r4_2->rev.time;
                temp_r3->revStd.damping = temp_r4_2->rev.damping;
                temp_r3->revStd.preDelay = temp_r4_2->rev.preDelay;
                var_r0 = sndAuxCallbackPrepareReverbSTD(&temp_r3->revStd);
                break;
            case 2:
                sp20[var_r23] = sndAuxCallbackChorus;
                temp_r3->ch.baseDelay = temp_r4_2->ch.baseDelay;
                temp_r3->ch.variation = temp_r4_2->ch.variation;
                temp_r3->ch.period = temp_r4_2->ch.period;
                var_r0 = sndAuxCallbackPrepareChorus(&temp_r3->ch);
                break;
            case 3:
                sp20[var_r23] = sndAuxCallbackDelay;
                temp_r3->delay.delay[0] = temp_r4_2->delay.delay[0];
                temp_r3->delay.feedback[0] = temp_r4_2->delay.feedback[0];
                temp_r3->delay.output[0] = temp_r4_2->delay.output[0];
                temp_r3->delay.delay[1] = temp_r4_2->delay.delay[1];
                temp_r3->delay.feedback[1] = temp_r4_2->delay.feedback[1];
                temp_r3->delay.output[1] = temp_r4_2->delay.output[1];
                temp_r3->delay.delay[2] = temp_r4_2->delay.delay[2];
                temp_r3->delay.feedback[2] = temp_r4_2->delay.feedback[2];
                temp_r3->delay.output[2] = temp_r4_2->delay.output[2];
                var_r0 = sndAuxCallbackPrepareDelay(&temp_r3->delay);
                break;
        }
        if (var_r0 == 0) {
            return 1;
        }
    }
    sndSetAuxProcessingCallbacks(0, sp20[0], &sys.unk1C[0], 0xFF, 0, sp20[1], &sys.unk1C[1], 0xFF, 0);
    return 0;
}

static s8 msmSysLoadBaseGroup(void *arg0)
{
    DVDFileInfo spC;
    s32 var_r28;
    unkStruct3 *temp_r27;
    unkStruct4 *temp_r25;

    if (msmFioOpen(sys.unk0, &spC) != 1) {
        return MSM_ERR_OPENFAIL;
    }
    for (var_r28 = 0; var_r28 < sys.unk3F4; var_r28++) {
        temp_r27 = sys.unk3F8[var_r28];
        temp_r25 = &sys.unk3EC[sys.unk10->unk29[var_r28]];
        if (msmFioRead(&spC, temp_r27, temp_r25->unk8, temp_r25->unk4 + sys.unkC->unk38) < 0) {
            msmFioClose(&spC);
            return MSM_ERR_READFAIL;
        }
        if (msmFioRead(&spC, arg0, temp_r25->unk10, temp_r25->unkC + sys.unkC->unk40) < 0) {
            msmFioClose(&spC);
            return MSM_ERR_READFAIL;
        }
        if (!sndPushGroup((void*) (temp_r27->unk4 + (u32) temp_r27), temp_r25->unk0, arg0,
            (void*) (temp_r27->unk8 + (u32) temp_r27), (void*) (temp_r27->unk0 + (u32) temp_r27)))
        {
            msmFioClose(&spC);
            return MSM_ERR_20;
        }
        sys.unk8 += temp_r25->unk10;
    }
    msmFioClose(&spC);
    return 0;
}

// TODO: https://decomp.me/scratch/NWiuL
// msmSysSearchGroupStack

s32 msmSysGroupInit(DVDFileInfo *arg0)
{
    s32 var_r7;
    UnkStructSys43C *temp_43C;
    unkStruct4 *temp_r20;

    sys.unk3DC = sys.unk10->unk3;
    sys.unk3E0 = 1;
    sys.unk3F4 = sys.unk10->unk28;
    sys.unk434 = sys.unk10->unk9;
    sys.unk435 = 0;
    sys.unk436 = 0;
    sys.unk46C = sys.unk10->unkA;
    sys.unk46D = 0;
    sys.unk46E = 0;
    if ((sys.unk3EC = msmMemAlloc(sys.unkC->unk24)) == NULL) {
        return MSM_ERR_OUTOFMEM;
    }
    if (msmFioRead(arg0, sys.unk3EC, sys.unkC->unk24, sys.unkC->unk20) < 0) {
        return MSM_ERR_READFAIL;
    }
    if ((sys.unk438 = msmMemAlloc(sys.unk10->unk18 * sys.unk434)) == NULL) {
        return MSM_ERR_OUTOFMEM;
    }
    if ((sys.unk470 = msmMemAlloc(sys.unk10->unk1C * sys.unk46C)) == NULL) {
        return MSM_ERR_OUTOFMEM;
    }
    if (sys.unkC->unk54) {
        if ((sys.unk3F0 = msmMemAlloc(sys.unkC->unk54)) == NULL) {
            return MSM_ERR_OUTOFMEM;
        }
        if (msmFioRead(arg0, sys.unk3F0, sys.unkC->unk54, sys.unkC->unk50) < 0) {
            return MSM_ERR_READFAIL;
        }
    } else {
        sys.unk3F0 = NULL;
    }
    for (var_r7 = 0; var_r7 < sys.unk434; var_r7++) {
        temp_43C = &sys.unk43C[var_r7];
        temp_43C->unk00 = temp_43C->unk01 = 0;
        temp_43C->unk04 = 0;
        temp_43C->unk08 = (void*) ((u32) sys.unk438 + sys.unk10->unk18 * var_r7);
    }
    for (var_r7 = 0; var_r7 < sys.unk46C; var_r7++) {
        temp_43C = &sys.unk474[var_r7];
        temp_43C->unk00 = temp_43C->unk01 = 0;
        temp_43C->unk04 = 0;
        temp_43C->unk08 = (void*) ((u32) sys.unk470 + sys.unk10->unk1C * var_r7);
    }
    sys.unk3E4 = 0;
    for (var_r7 = 0; var_r7 < sys.unk3F4; var_r7++) {
        temp_r20 = &sys.unk3EC[sys.unk10->unk29[var_r7]];
        if ((sys.unk3F8[var_r7] = msmMemAlloc(temp_r20->unk8)) == NULL) {
            return MSM_ERR_OUTOFMEM;
        }
        if (sys.unk3E4 < temp_r20->unk10) {
            sys.unk3E4 = temp_r20->unk10;
        }
        temp_r20->unk10 *= -1;
    }
    sys.unk3E8 = 0;
    for (var_r7 = 1; var_r7 < sys.unk3DC; var_r7++) {
        temp_r20 = &sys.unk3EC[var_r7];
        if (temp_r20->unk10 < 0) {
            temp_r20->unk10 *= -1;
        } else if (sys.unk3E8 < temp_r20->unk10) {
            sys.unk3E8 = temp_r20->unk10;
        }
    }
    return 0;
}

void msmSysIrqDisable(void)
{
    if (sys.unk4EC++ == 0) {
        sys.unk4F0 = OSDisableInterrupts();
    }
}

void msmSysIrqEnable(void)
{
    if (sys.unk4EC != 0) {
        if (--sys.unk4EC == 0) {
            OSRestoreInterrupts(sys.unk4F0);
        }
    }
}

BOOL msmSysCheckBaseGroup(s32 arg0)
{
    s32 var_r6;

    for (var_r6 = 0; var_r6 < sys.unk3F4 + sys.unk436 + sys.unk46E; var_r6++) {
        if (sys.unk3EC[sys.unk10->unk29[var_r6]].unk0 == arg0) {
            return TRUE;
        }
    }
    return FALSE;
}

void *msmSysGetGroupDataPtr(s32 arg0)
{
    UnkStructSys43C *temp_43C;
    s32 var_r6;

    for (var_r6 = 0; var_r6 < sys.unk3F4; var_r6++) {
        if (sys.unk10->unk29[var_r6] == arg0) {
            return sys.unk3F8[var_r6];
        }
    }
    for (var_r6 = 0; var_r6 < sys.unk434; var_r6++) {
        temp_43C = &sys.unk43C[var_r6];
        if (temp_43C->unk04 != 0 && temp_43C->unk00 == arg0) {
            return temp_43C->unk08;
        }
    }
    for (var_r6 = 0; var_r6 < sys.unk46C; var_r6++) {
        temp_43C = &sys.unk474[var_r6];
        if (temp_43C->unk04 != 0 && temp_43C->unk00 == arg0) {
            return temp_43C->unk08;
        }
    }
    return NULL;
}

BOOL msmSysCheckLoadGroupID(s32 arg0)
{
    UnkStructSys43C *temp_43C;
    s32 var_r6;

    for (var_r6 = 0; var_r6 < sys.unk3F4 + sys.unk436 + sys.unk46E; var_r6++) {
        if (sys.unk3EC[sys.unk10->unk29[var_r6]].unk0 == arg0) {
            return TRUE;
        }
    }
    for (var_r6 = 0; var_r6 < sys.unk434; var_r6++) {
        temp_43C = &sys.unk43C[var_r6];
        if (temp_43C->unk04 != 0 && sys.unk3EC[temp_43C->unk00].unk0 == arg0) {
            return TRUE;
        }
    }
    for (var_r6 = 0; var_r6 < sys.unk46C; var_r6++) {
        temp_43C = &sys.unk474[var_r6];
        if (temp_43C->unk04 != 0 && sys.unk3EC[temp_43C->unk00].unk0 == arg0) {
            return TRUE;
        }
    }
    return FALSE;
}

void msmSysRegularProc(void)
{
}

s32 msmSysGetOutputMode(void)
{
    return sys.unk4;
}

s32 msmSysSetOutputMode(SND_OUTPUTMODE mode)
{
    SND_OUTPUTMODE var_r3;
    s32 var_r30;

    var_r30 = 0;
    sys.unk4 = mode;
    switch (mode) {
        case SND_OUTPUTMODE_MONO:
            var_r3 = SND_OUTPUTMODE_MONO;
            break;
        case SND_OUTPUTMODE_SURROUND:
            if (sys.unk10->unkB != 0) {
                var_r3 = SND_OUTPUTMODE_SURROUND;
            } else {
                sys.unk4 = SND_OUTPUTMODE_STEREO;
                var_r3 = SND_OUTPUTMODE_STEREO;
                var_r30 = 1;
            }
            break;
        case SND_OUTPUTMODE_STEREO:
        default:
            var_r3 = SND_OUTPUTMODE_STEREO;
            break;
    }
    sndOutputMode(var_r3);
    msmStreamSetOutputMode(sys.unk4);
    OSSetSoundMode((mode != SND_OUTPUTMODE_MONO) ? 1 : 0);
    return var_r30;
}

s32 msmSysSetAux(s32 arg0, s32 arg1)
{
    s32 var_r28;

    sndSetAuxProcessingCallbacks(0, NULL, NULL, 0, 0, NULL, NULL, 0, 0);
    for (var_r28 = 1; var_r28 >= 0; var_r28--) {
        if (sys.unk18[var_r28] < 0) {
            continue;
        }
        switch (sys.unk14[sys.unk18[var_r28]].unk0) {
            case 0:
                sndAuxCallbackShutdownReverbHI(&sys.unk1C[var_r28].revHi);
                break;
            case 1:
                sndAuxCallbackShutdownReverbSTD(&sys.unk1C[var_r28].revStd);
                break;
            case 2:
                sndAuxCallbackShutdownChorus(&sys.unk1C[var_r28].ch);
                break;
            case 3:
                sndAuxCallbackShutdownDelay(&sys.unk1C[var_r28].delay);
                break;
            }
    }
    if (msmSysSetAuxParam(arg0, arg1) != 0) {
        return MSM_ERR_INVALID_AUXPARAM;
    }
    return 0;
}

s32 msmSysGetSampSize(BOOL baseGrp)
{
    if (baseGrp != 0) {
        return sys.unk3E8;
    }
    return sys.unk3E4;
}

s32 msmSysDelGroupAll(void)
{
    UnkStructSys43C *temp_r28;
    s32 var_r29;

    for (var_r29 = 0; var_r29 < sys.unk46C; var_r29++) {
        temp_r28 = &sys.unk474[var_r29];
        if (temp_r28->unk04 != 0 && temp_r28->unk01 == 0) {
            temp_r28->unk04 = 0;
            sndPopGroup();
            sys.unk8 -= sys.unk3EC[temp_r28->unk00].unk10;
            sys.unk46D--;
        }
    }
    for (var_r29 = 0; var_r29 < sys.unk434; var_r29++) {
        temp_r28 = &sys.unk43C[var_r29];
        if (temp_r28->unk04 != 0 && temp_r28->unk01 == 0) {
            temp_r28->unk04 = 0;
            sndPopGroup();
            sys.unk8 -= sys.unk3EC[temp_r28->unk00].unk10;
            sys.unk435--;
        }
    }
    return 0;
}

s32 msmSysDelGroupBase(s32 grpNum)
{
    s32 var_r4;
    UnkStructSys43C *temp_r26;
    s32 var_r27;
    s8 var_r31;
    s8 var_r25;
    s32 var_r6;

    if (sys.unk436 + sys.unk46E == 0) {
        return 0;
    }
    if (grpNum >= sys.unk436 + sys.unk46E) {
        grpNum = 0;
    }
    if (grpNum != 0) {
        msmSysDelGroupAll();
        for (var_r27 = 0; var_r27 < grpNum; var_r27++) {
            var_r6 = 0;
            for (var_r4 = 0; var_r4 < sys.unk434; var_r4++) {
                temp_r26 = &sys.unk43C[var_r4];
                if (temp_r26->unk04 > var_r6) {
                    var_r6 = temp_r26->unk04;
                    var_r31 = var_r4;
                    var_r25 = 0;
                }
            }
            for (var_r4 = 0; var_r4 < sys.unk46C; var_r4++) {
                temp_r26 = &sys.unk474[var_r4];
                if (temp_r26->unk04 > var_r6) {
                    var_r6 = temp_r26->unk04;
                    var_r31 = var_r4;
                    var_r25 = 1;
                }
            }
            if (var_r25 == 0) {
                temp_r26 = &sys.unk43C[var_r31];
                sys.unk435--;
                sys.unk436--;
            } else {
                temp_r26 = &sys.unk474[var_r31];
                sys.unk46D--;
                sys.unk46E--;
            }
            sndPopGroup();
            sys.unk8 -= sys.unk3EC[temp_r26->unk00].unk10;
            temp_r26->unk01 = 0;
            temp_r26->unk04 = 0;
        }
    } else {
        for (var_r27 = 0; var_r27 < sys.unk434; var_r27++) {
            temp_r26 = &sys.unk43C[var_r27];
            if (temp_r26->unk04 != 0) {
                sndPopGroup();
                sys.unk8 -= sys.unk3EC[temp_r26->unk00].unk10;
                temp_r26->unk01 = 0;
                temp_r26->unk04 = 0;
            }
        }
        for (var_r27 = 0; var_r27 < sys.unk46C; var_r27++) {
            temp_r26 = &sys.unk474[var_r27];
            if (temp_r26->unk04 != 0) {
                sndPopGroup();
                sys.unk8 -= sys.unk3EC[temp_r26->unk00].unk10;
                temp_r26->unk01 = 0;
                temp_r26->unk04 = 0;
            }
        }
        sys.unk46E = 0;
        sys.unk46D = 0;
        sys.unk436 = 0;
        sys.unk435 = 0;
    }
    return 0;
}

// TODO: https://decomp.me/scratch/zexTY
// msmSysLoadGroupBase

// msmSysLoadGroupSet

// msmSysLoadGroupSub

// TODO: https://decomp.me/scratch/AhvXa
// msmSysLoadGroup

void msmSysCheckInit(void)
{
    sndIsInstalled();
}

s32 msmSysInit(MSM_INIT *init, MSM_ARAM *aram)
{
    s32 var_r26;
    void *temp_r3_8;

    SND_HOOKS sp4C = { msmMemAlloc, msmMemFree };
    DVDFileInfo sp10;
    if (sndIsInstalled() == 1) {
        return MSM_ERR_INSTALLED;
    }
    var_r26 = 0; // retErr
    sys.unk4EC = 0;
    msmMemInit(init->heap, init->heapSize);
    msmFioInit(init->open, init->read, init->close);
    sys.unk0 = DVDConvertPathToEntrynum(init->msmPath);
    if (sys.unk0 < 0) {
        return MSM_ERR_OPENFAIL;
    }
    if (msmFioOpen(sys.unk0, &sp10) != 1) {
        return MSM_ERR_OPENFAIL;
    }
    if ((sys.unkC = msmMemAlloc(0x60)) == NULL) {
        msmFioClose(&sp10);
        return MSM_ERR_OUTOFMEM;
    }
    if (msmFioRead(&sp10, sys.unkC, 0x60, 0) < 0) {
        msmFioClose(&sp10);
        return MSM_ERR_READFAIL;
    }
    if (sys.unkC->unk4 != 2) {
        msmFioClose(&sp10);
        return MSM_ERR_INVALIDFILE;
    }
    if ((sys.unk10 = msmMemAlloc(sys.unkC->unk14)) == NULL) {
        msmFioClose(&sp10);
        return MSM_ERR_OUTOFMEM;
    }
    if (msmFioRead(&sp10, sys.unk10, sys.unkC->unk14, sys.unkC->unk10) < 0) {
        msmFioClose(&sp10);
        return MSM_ERR_READFAIL;
    }
    if (aram != NULL) {
        if (aram->skipARInit == 0) {
            ARInit(aram->stackIndex, aram->aramEnd);
            ARQInit();
            aram = (MSM_ARAM *)ARAlloc(sys.unk10->unk14);
            if ((u32)aram != ARGetBaseAddress()) {
                msmFioClose(&sp10);
                return MSM_ERR_OUTOFAMEM;
            }
            sys.unk7 = 0;
        }
        else {
            if ((sys.unk10->unk14 + ARGetBaseAddress()) > aram->aramEnd) {
                msmFioClose(&sp10);
                return MSM_ERR_OUTOFAMEM;
            }
            ARInit(NULL, 0);
            ARQInit();
            sys.unk7 = 1;
        }
    }
    var_r26 = msmSysGroupInit(&sp10);
    if (var_r26 != 0) {
        msmFioClose(&sp10);
        return var_r26;
    }
    var_r26 = msmMusInit(&sys, &sp10);
    if (var_r26 != 0) {
        msmFioClose(&sp10);
        return var_r26;
    }
    var_r26 = msmSeInit(&sys, &sp10);
    if (var_r26 != 0) {
        msmFioClose(&sp10);
        return var_r26;
    }
    sys.unk18[0] = sys.unk10->unkE == -2 ? -2 : -1;
    sys.unk18[1] = sys.unk10->unkF == -2 ? -2 : -1;
    if ((s32)sys.unkC->unk1C == 0) {
        var_r26 = 0;
    }
    else {
        if ((sys.unk14 = msmMemAlloc(sys.unkC->unk1C)) == NULL) {
            var_r26 = MSM_ERR_OUTOFMEM;
        }
        else {
            if (msmFioRead(&sp10, sys.unk14, sys.unkC->unk1C, sys.unkC->unk18) < 0) {
                var_r26 = MSM_ERR_READFAIL;
            }
            else {
                var_r26 = 0;
            }
        }
    }
    if (var_r26 != 0) {
        msmFioClose(&sp10);
        return var_r26;
    }
    msmFioClose(&sp10);
    var_r26 = msmStreamInit(init->pdtPath);
    if (var_r26 < 0) {
        return var_r26;
    }
    AIInit(NULL);
    sndSetHooks(&sp4C);
    if (sndInit(sys.unk10->unk0, sys.unk10->unk1, sys.unk10->unk2, 1, 0, sys.unk10->unk14) != 0) {
        return MSM_ERR_1E;
    }
    sys.unk4F4 = AIRegisterDMACallback(msmSysServer);
    sys.unk4F8 = 1;
    var_r26 = msmStreamAmemAlloc();
    if (var_r26 < 0) {
        sndQuit();
        return var_r26;
    }
    sys.unk8 = var_r26 + 0x500;
    if ((s32)sys.unk10->unk10 != 0) {
        temp_r3_8 = msmMemAlloc(sys.unk10->unk10 + 0x100);
        if (temp_r3_8 == NULL) {
            msmStreamAmemFree();
            sndQuit();
            return MSM_ERR_OUTOFMEM;
        }
        msmMemFree(temp_r3_8);
    }
    if (msmSysSetAuxParam(sys.unk10->unkE, sys.unk10->unkF) != 0) {
        msmStreamAmemFree();
        sndQuit();
        return MSM_ERR_INVALID_AUXPARAM;
    }
    msmSysSetOutputMode(OSGetSoundMode() == 0 ? SND_OUTPUTMODE_MONO : SND_OUTPUTMODE_STEREO);
    sndVolume(0x7F, 0, 0xFF);
    return 0;
}
