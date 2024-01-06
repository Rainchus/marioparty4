#include "game/audio.h"
#include "game/memory.h"
#include "game/msm.h"
#include "game/object.h"
#include "game/wipe.h"
#include "game/gamework_data.h"

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s8 unk0C;
    /* 0x0D */ s8 unk0D;
} sndGrpTableData;

static s32 HuSePlay(s32 arg0, UnkMsmStruct_01 *arg1);

extern s16 omSysExitReq;

static s32 charVoiceGroupStat[8];
static s32 sndFXBuf[64][2];

static s16 Hu3DAudVol;
static s16 sndGroupBak;
static s32 auxANoBak;
static s32 auxBNoBak;
static s8 HuAuxAVol;
static s8 HuAuxBVol;
float Snd3DBackSurDisOffset;
float Snd3DFrontSurDisOffset;
float Snd3DStartDisOffset;
float Snd3DSpeedOffset;
float Snd3DDistOffset;
s32 musicOffF;
u8 fadeStat;

static char *lbl_8012E9AC[] = {
    "sound/MPNGC02.son",
    "sound/MPNGC16.son",
    ""
};

void HuAudInit(void) {
    UnkMsmStruct_00 sp8;
    s32 temp_r3;
    s16 i;

    sp8.unk20 = HuMemDirectMalloc(HEAP_MUSIC, 0x13FC00);
    sp8.unk24 = 0x13FC00;
    sp8.unk0C = "/sound/mpgcsnd.msm";
    sp8.unk10 = "/sound/mpgcstr.pdt";
    sp8.unk14 = 0;
    sp8.unk18 = 0;
    sp8.unk1C = 0;
    sp8.unk00 = 1;
    sp8.unk04 = 0x808000;
    temp_r3 = msmSysInit(&sp8.unk0C, &sp8);
    if (temp_r3 < 0) {
        OSReport("MSM(Sound Manager) Error:Error Code %d\n", temp_r3);
        while (1);
    }
    if (OSGetSoundMode() == 0) {
        msmSysSetOutputMode(0);
    } else {
        msmSysSetOutputMode(2);
    }
    for (i = 0; i < 64; i++) {
        sndFXBuf[i][0] = -1;
    }
    for (i = 0; i < 8; i++) {
        charVoiceGroupStat[i] = 0;
    }
    sndGroupBak = -1;
    auxANoBak = auxBNoBak = -1;
    fadeStat = 0;
    musicOffF = 0;
}

s32 HuAudStreamPlay(void) {
    return 0;
}

void HuAudStreamVolSet(s16 vol) {
    AISetStreamVolLeft(vol);
    AISetStreamVolRight(vol);
    Hu3DAudVol = vol;
}

void HuAudStreamPauseOn(void) {
    AISetStreamPlayState(0);
}

void HuAudStreamPauseOff(void) {
    AISetStreamPlayState(1);
}

void HuAudStreamFadeOut(void) {
}

void HuAudAllStop(void) {
    HuAudSeqAllStop();
    HuAudFXAllStop();
    HuAudSStreamAllStop();
}

void HuAudFadeOut(s32 arg0) {
    HuAudFXAllStop();
    HuAudSeqAllFadeOut(arg0);
    HuAudSStreamAllFadeOut(arg0);
}

s32 HuAudFXPlay(s32 arg0) {
    WipeState *wipe = &wipeData;

    if (omSysExitReq != 0 || (wipeData.mode == WIPE_MODE_OUT && wipe->time / wipe->duration > 0.5)) {
        return 0;
    }
    return HuAudFXPlayVolPan(arg0, 0x7F, 0x40);
}

s32 HuAudFXPlayVol(s32 arg0, s16 arg1) {
    if (omSysExitReq != 0) {
        return 0;
    }
    return HuAudFXPlayVolPan(arg0, arg1, 0x40);
}

s32 HuAudFXPlayVolPan(s32 arg0, s16 arg1, s16 arg2) {
    UnkMsmStruct_01 sp10;

    if (omSysExitReq != 0) {
        return 0;
    }
    sp10.unk00 = 3;
    sp10.unk04 = arg1;
    sp10.unk05 = arg2;
    return HuSePlay(arg0, &sp10);
}

void HuAudFXStop(s32 arg0) {
    msmSeStop(arg0, 0);
}

void HuAudFXAllStop(void) {
    msmSeStopAll(0, 0);
}

void HuAudFXFadeOut(s32 arg0, s32 arg1) {
    msmSeStop(arg0, arg1);
}

void HuAudFXPanning(s32 arg0, s16 arg1) {
    UnkMsmStruct_01 sp10;

    if (omSysExitReq == 0) {
        sp10.unk00 = 2;
        sp10.unk05 = arg1;
        msmSeSetParam(arg0, &sp10);
    }
}

void HuAudFXListnerSet(s32 arg0, s32 arg1, float arg2, float arg3) {
    if (omSysExitReq == 0) {
        HuAudFXListnerSetEX(arg0, arg1,
            arg2 + Snd3DDistOffset,
            arg3 + Snd3DSpeedOffset,
            Snd3DStartDisOffset,
            Snd3DFrontSurDisOffset + (0.25 * arg2 + Snd3DStartDisOffset),
            Snd3DBackSurDisOffset + (0.25 * arg2 + Snd3DStartDisOffset));
    }
}

void HuAudFXListnerSetEX(s32 arg0, s32 arg1, float sndDist, float sndSpeed, float arg4, float arg5, float arg6) {
    UnkMsmStruct_02 sp1C;

    if (omSysExitReq == 0) {
        sp1C.unk00 = 7;
        sp1C.startDis = arg4 + Snd3DStartDisOffset;
        sp1C.frontSurDis = arg5 + Snd3DFrontSurDisOffset;
        sp1C.backSurDis = arg6 + Snd3DBackSurDisOffset;
        msmSeSetListener(arg0, arg1, sndDist + Snd3DDistOffset, sndSpeed + Snd3DSpeedOffset, &sp1C);
        OSReport("//////////////////////////////////\n");
        OSReport("sndDist %f\n", sndDist);
        OSReport("sndSpeed %f\n", sndSpeed);
        OSReport("startDis %f\n", sp1C.startDis);
        OSReport("frontSurDis %f\n", sp1C.frontSurDis);
        OSReport("backSurDis %f\n", sp1C.backSurDis);
        OSReport("//////////////////////////////////\n");
    }
}

void HuAudFXListnerUpdate(s32 arg0, s32 arg1) {
    if (omSysExitReq == 0) {
        msmSeUpdataListener(arg0, arg1);
    }
}

s32 HuAudFXEmiterPlay(s32 arg0, Vec *arg1) {
    UnkMsmStruct_01 spC;

    if (omSysExitReq != 0) {
        return 0;
    }
    spC.unk00 = 0x40;
    spC.unk10.x = arg1->x;
    spC.unk10.y = arg1->y;
    spC.unk10.z = arg1->z;
    return HuSePlay(arg0, &spC);
}

void HuAudFXEmiterUpDate(s32 arg0, Vec *arg1) {
    UnkMsmStruct_01 spC;

    if (omSysExitReq == 0) {
        spC.unk00 = 0x40;
        spC.unk10.x = arg1->x;
        spC.unk10.y = arg1->y;
        spC.unk10.z = arg1->z;
        msmSeSetParam(arg0, &spC);
    }
}

void HuAudFXListnerKill(void) {
    msmSeDelListener();
}

void HuAudFXPauseAll(s32 arg0) {
    msmSePauseAll(arg0, 0x64);
}

s32 HuAudFXStatusGet(s32 arg0) {
    return msmSeGetStatus(arg0);
}

s32 HuAudFXPitchSet(s32 arg0, s16 arg1) {
    UnkMsmStruct_01 sp10;

    if (omSysExitReq != 0) {
        return 0;
    }
    sp10.unk00 = 4;
    sp10.unk06 = arg1;
    return msmSeSetParam(arg0, &sp10);
}

s32 HuAudFXVolSet(s32 arg0, s16 arg1) {
    UnkMsmStruct_01 sp10;

    if (omSysExitReq != 0) {
        return 0;
    }
    sp10.unk00 = 1;
    sp10.unk04 = arg1;
    return msmSeSetParam(arg0, &sp10);
}

s32 HuAudSeqPlay(s16 arg0) {
    s32 temp_r31;

    if (musicOffF != 0 || omSysExitReq != 0) {
        return 0;
    }
    temp_r31 = msmMusPlay(arg0, 0);
    return temp_r31;
}

void HuAudSeqStop(s32 arg0) {
    if (musicOffF != 0 || omSysExitReq != 0) {
        return;
    }
    msmMusStop(arg0, 0);
}

void HuAudSeqFadeOut(s32 arg0, s32 arg1) {
    if (musicOffF == 0) {
        msmMusStop(arg0, arg1);
    }
}

void HuAudSeqAllFadeOut(s32 arg0) {
    s16 i;

    for (i = 0; i < 4; i++) {
        if (msmMusGetStatus(i) == 2) {
            msmMusStop(i, arg0);
        }
    }
}

void HuAudSeqAllStop(void) {
    msmMusStopAll(0, 0);
}

void HuAudSeqPauseAll(s32 arg0) {
    msmMusPauseAll(arg0, 0x64);
}

void HuAudSeqPause(s32 arg0, s32 arg1, s32 arg2) {
    if (musicOffF != 0 || omSysExitReq != 0) {
        return;
    }
    msmMusPause(arg0, arg1, arg2);
}

s32 HuAudSeqMidiCtrlGet(s32 arg0, s8 arg1, s8 arg2) {
    if (musicOffF != 0 || omSysExitReq != 0) {
        return 0;
    }
    return msmMusGetMidiCtrl(arg0, arg1, arg2);
}

s32 HuAudSStreamPlay(s16 arg0) {
    s32 spC;
    s32 temp_r31;

    if (musicOffF != 0 || omSysExitReq != 0) {
        return 0;
    }
    spC = 0;
    temp_r31 = msmStreamPlay(arg0, &spC);
    return temp_r31;
}

void HuAudSStreamStop(s32 arg0) {
    if (musicOffF == 0) {
        msmStreamStop(arg0, 0);
    }
}

void HuAudSStreamFadeOut(s32 arg0, s32 arg1) {
    if (musicOffF == 0) {
        msmStreamStop(arg0, arg1);
    }
}

void HuAudSStreamAllFadeOut(s32 arg0) {
    msmStreamPauseAll(arg0);
}

void HuAudSStreamAllStop(void) {
    msmStreamPauseAll(0);
}

s32 HuAudSStreamStatGet(s32 arg0) {
    return msmStreamGetStatus(arg0);
}

sndGrpTableData sndGrpTable[] = {
    { OVL_BOOT     , 0xFFFF, 0,  1, 0xFF, 0xFF },
    { OVL_INST     , 0xFFFF, 0,  1, 0xFF, 0xFF },
    { OVL_M401     , 0x0012, 0,  2, 0x40, 0x40 },
    { OVL_M402     , 0x0013, 0,  3, 0x30, 0x20 },
    { OVL_M403     , 0x0014, 0,  1, 0xFF, 0xFF },
    { OVL_M404     , 0x0015, 0,  1, 0xFF, 0xFF },
    { OVL_M405     , 0x0016, 0,  1, 0x40, 0x20 },
    { OVL_M406     , 0x0017, 0,  1, 0xFF, 0xFF },
    { OVL_M407     , 0x0018, 0,  1, 0xFF, 0xFF },
    { OVL_M408     , 0x0019, 0,  1, 0xFF, 0xFF },
    { OVL_M409     , 0x001A, 0,  4, 0xFF, 0xFF },
    { OVL_M410     , 0x001B, 0,  1, 0xFF, 0xFF },
    { OVL_M411     , 0x001C, 0,  1, 0xFF, 0xFF },
    { OVL_M412     , 0x001D, 0,  1, 0xFF, 0xFF },
    { OVL_M413     , 0x001E, 0,  1, 0xFF, 0xFF },
    { OVL_M414     , 0x001F, 0,  1, 0xFF, 0xFF },
    { OVL_M415     , 0x0020, 0,  1, 0xFF, 0xFF },
    { OVL_M416     , 0x0021, 0,  1, 0xFF, 0xFF },
    { OVL_M417     , 0x0022, 0,  1, 0xFF, 0xFF },
    { OVL_M418     , 0x0023, 0,  1, 0x40, 0x40 },
    { OVL_M419     , 0x0024, 0,  6, 0xFF, 0xFF },
    { OVL_M420     , 0x0025, 0,  1, 0xFF, 0xFF },
    { OVL_M421     , 0x0026, 0,  1, 0xFF, 0xFF },
    { OVL_M422     , 0x0027, 0,  1, 0xFF, 0xFF },
    { OVL_M423     , 0x0028, 0,  1, 0xFF, 0xFF },
    { OVL_M424     , 0x0029, 0,  1, 0xFF, 0xFF },
    { OVL_M425     , 0x002A, 0,  1, 0xFF, 0xFF },
    { OVL_M426     , 0x002B, 0,  1, 0xFF, 0xFF },
    { OVL_M427     , 0x002C, 0,  1, 0x40, 0x48 },
    { OVL_M428     , 0x002D, 0,  1, 0xFF, 0xFF },
    { OVL_M429     , 0x002E, 0,  1, 0xFF, 0xFF },
    { OVL_M430     , 0x002F, 0,  1, 0xFF, 0xFF },
    { OVL_M431     , 0x0030, 0,  1, 0xFF, 0xFF },
    { OVL_M432     , 0x0031, 0,  1, 0x30, 0x20 },
    { OVL_M433     , 0x0032, 0,  1, 0xFF, 0xFF },
    { OVL_M434     , 0x0033, 0,  1, 0xFF, 0xFF },
    { OVL_M435     , 0x0034, 0,  9, 0x20, 0x40 },
    { OVL_M436     , 0x0035, 0, 10, 0x20, 0x40 },
    { OVL_M437     , 0x0036, 0,  1, 0x20, 0x40 },
    { OVL_M438     , 0x0037, 0, 11, 0xFF, 0xFF },
    { OVL_M439     , 0x0038, 0, 12, 0x30, 0x20 },
    { OVL_M440     , 0x0039, 0,  1, 0xFF, 0xFF },
    { OVL_M441     , 0x003A, 0,  1, 0xFF, 0xFF },
    { OVL_M442     , 0x003B, 0,  1, 0xFF, 0xFF },
    { OVL_M443     , 0x003C, 0,  1, 0xFF, 0xFF },
    { OVL_M444     , 0x003D, 0,  1, 0xFF, 0xFF },
    { OVL_M445     , 0x003E, 0,  1, 0xFF, 0xFF },
    { OVL_M446     , 0x003F, 0,  1, 0xFF, 0xFF },
    { OVL_M447     , 0x0040, 0,  1, 0xFF, 0xFF },
    { OVL_M448     , 0x0041, 0,  1, 0xFF, 0xFF },
    { OVL_M449     , 0x0042, 0,  1, 0xFF, 0xFF },
    { OVL_M450     , 0x0043, 0, 13, 0x40, 0x40 },
    { OVL_M451     , 0x0044, 0,  1, 0xFF, 0xFF },
    { OVL_M453     , 0x0045, 0,  1, 0xFF, 0xFF },
    { OVL_M455     , 0x0046, 0,  1, 0xFF, 0xFF },
    { OVL_M456     , 0x0047, 0,  1, 0xFF, 0xFF },
    { OVL_M457     , 0x0048, 0, 14, 0x40, 0x20 },
    { OVL_M458     , 0x0049, 0, 15, 0x40, 0x20 },
    { OVL_M459     , 0x004A, 0,  1, 0xFF, 0xFF },
    { OVL_M460     , 0x004B, 0,  1, 0xFF, 0xFF },
    { OVL_M461     , 0x004C, 0,  1, 0xFF, 0xFF },
    { OVL_M462     , 0x004D, 0,  1, 0xFF, 0xFF },
    { OVL_M463     , 0x004E, 0,  1, 0xFF, 0xFF },
    { OVL_MENT     , 0xFFFF, 0,  1, 0xFF, 0xFF },
    { OVL_MGMODE   , 0x0001, 0,  1, 0xFF, 0xFF },
    { OVL_MODESEL  , 0x0000, 0,  1, 0xFF, 0xFF },
    { OVL_MODELTEST, 0x0012, 0,  1, 0xFF, 0xFF },
    { OVL_MSETUP   , 0x0000, 0,  1, 0xFF, 0xFF },
    { OVL_MSTORY   , 0x0005, 0,  1, 0xFF, 0xFF },
    { OVL_MSTORY2  , 0x0005, 0,  1, 0xFF, 0xFF },
    { OVL_MSTORY3  , 0x0008, 0,  1, 0xFF, 0xFF },
    { OVL_NIS      , 0x0009, 0,  1, 0xFF, 0xFF },
    { OVL_OPTION   , 0xFFFF, 0,  1, 0xFF, 0xFF },
    { OVL_PRESENT  , 0xFFFF, 0,  1, 0xFF, 0xFF },
    { OVL_RESULT   , 0xFFFF, 0,  1, 0xFF, 0xFF },
    { OVL_SAF      , 0x0000, 0,  2, 0x7F, 0x7F },
    { OVL_SELMENU  , 0x0000, 0,  1, 0xFF, 0xFF },
    { OVL_W01      , 0x0009, 0,  1, 0xFF, 0xFF },
    { OVL_W02      , 0x000A, 0,  1, 0xFF, 0xFF },
    { OVL_W03      , 0x000B, 0,  1, 0xFF, 0xFF },
    { OVL_W04      , 0x000C, 0,  1, 0xFF, 0xFF },
    { OVL_W05      , 0x000D, 0,  1, 0xFF, 0xFF },
    { OVL_W06      , 0x000E, 0,  1, 0xFF, 0xFF },
    { OVL_W10      , 0x000F, 0,  1, 0xFF, 0xFF },
    { OVL_W20      , 0x0010, 0,  1, 0xFF, 0xFF },
    { OVL_W21      , 0x0011, 0,  1, 0xFF, 0xFF },
    { OVL_MPEX     , 0x0004, 0,  1, 0xFF, 0xFF },
    { OVL_ZTAR     , 0xFFFF, 0,  1, 0xFF, 0xFF },
    { OVL_E3SETUP  , 0x0000, 0,  1, 0xFF, 0xFF },
    { OVL_STAFF    , 0xFFFF, 0,  1, 0xFF, 0xFF },
    { OVL_INVALID  , 0xFFFF, 0,  1, 0x00, 0x00 }
};

void HuAudDllSndGrpSet(u16 ovl) {
    sndGrpTableData *var_r31;
    s16 var_r29;

    var_r31 = sndGrpTable;
    while (1) {
        if (var_r31->unk00 == ovl) {
            var_r29 = var_r31->unk02;
            break;
        }
        if (var_r31->unk00 == OVL_INVALID) {
            var_r29 = 0x12;
            break;
        }
        var_r31++;
    }
    if (var_r29 != -1) {
        OSReport("SOUND ##########################\n");
        HuAudSndGrpSetSet(var_r29);
        if (var_r31->unk04 != auxANoBak || var_r31->unk08 != auxBNoBak) {
            msmSysSetAux(var_r31->unk04, var_r31->unk08);
            OSReport("Change AUX %d,%d\n", var_r31->unk04, var_r31->unk08);
            auxANoBak = var_r31->unk04;
            auxBNoBak = var_r31->unk08;
            HuPrcVSleep();
        }
        HuAudAUXVolSet(var_r31->unk0C, var_r31->unk0D);
        OSReport("##########################\n");
    }
}

void HuAudSndGrpSetSet(s16 arg0) {
    void *temp_r3;
    OSTick temp_r31;
    s32 temp_r26;
    s32 temp_r27;

    if (sndGroupBak != arg0) {
        msmMusStopAll(1, 0);
        msmSeStopAll(1, 0);
        temp_r31 = OSGetTick();
        while ((msmMusGetNumPlay(1) != 0 || msmSeGetNumPlay(1) != 0)
            && OSTicksToMilliseconds(OSGetTick() - temp_r31) < 500);
        OSReport("%d\n", OSTicksToMilliseconds(OSGetTick() - temp_r31));
        if (OSTicksToMilliseconds(OSGetTick() - temp_r31) >= 500) {
            temp_r26 = msmSeGetNumPlay(1);
            OSReport("Timed Out! Mus %d:SE %d\n", msmMusGetNumPlay(1), temp_r26);
        }
        OSReport("GroupSet %d\n", arg0);
        sndGroupBak = arg0;
        temp_r27 = msmSysDelGroupAll();
        temp_r3 = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(1));
        temp_r27 = msmSysLoadGroupSet(arg0, temp_r3);
        OSReport("***********GroupSet Error %d\n", temp_r27);
        HuMemDirectFree(temp_r3);
    }
}

void HuAudSndGrpSet(s16 arg0) {
    void *temp_r3;

    temp_r3 = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(arg0));
    msmSysLoadGroup(arg0, temp_r3, 0);
    HuMemDirectFree(temp_r3);
}

void HuAudSndCommonGrpSet(s16 arg0, s32 arg1) {
    s16 temp_r30;
    OSTick temp_r27;
    void *temp_r3;
    s16 i;

    for (i = 0; i < 8; i++) {
        charVoiceGroupStat[i] = 0;
    }
    msmMusStopAll(1, 0);
    msmSeStopAll(1, 0);
    temp_r27 = OSGetTick();
    while ((msmMusGetNumPlay(1) != 0 || msmSeGetNumPlay(1) != 0)
        && OSTicksToMilliseconds(OSGetTick() - temp_r27) < 500);
    OSReport("CommonGrpSet %d\n", arg0);
    if (arg1 != 0) {
        temp_r30 = msmSysDelGroupBase(0);
        if (temp_r30 < 0) {
            OSReport("Del Group Error %d\n", temp_r30);
        }
    }
    temp_r3 = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(arg0));
    msmSysLoadGroupBase(arg0, temp_r3);
    HuMemDirectFree(temp_r3);
    sndGroupBak = -1;
}

void HuAudAUXSet(s32 arg0, s32 arg1) {
    if (arg0 == -1) {
        arg0 = 0;
    }
    if (arg1 == -1) {
        arg1 = 1;
    }
    msmSysSetAux(arg0, arg1);
}

void HuAudAUXVolSet(s8 arg0, s8 arg1) {
    HuAuxAVol = arg0;
    HuAuxBVol = arg1;
}

void HuAudVoiceInit(s16 ovl) {
    sndGrpTableData *var_r29;
    OSTick temp_r23;
    s16 temp_r26;
    s16 temp_r25;
    s16 temp_r30;
    s16 var_r27;
    void *temp_r3;
    s16 i;

    if (ovl != OVL_INVALID) {
        var_r29 = sndGrpTable;
        while (1) {
            if (var_r29->unk00 == ovl && var_r29->unk02 == -1) {
                return;
            }
            if (var_r29->unk00 == OVL_INVALID) {
                break;
            }
            var_r29++;
        }
    }
    for (i = var_r27 = 0; i < 4; i++) {
        temp_r30 = GWPlayerCfg[i].character;
        if (temp_r30 < 0 || temp_r30 >= 8 || temp_r30 == 0xFF || charVoiceGroupStat[temp_r30] != 0) {
            var_r27++;
        }
    }
    if (var_r27 < 4) {
        for (i = 0; i < 8; i++) {
            charVoiceGroupStat[i] = 0;
        }
        msmMusStopAll(1, 0);
        msmSeStopAll(1, 0);
        temp_r23 = OSGetTick();
        while ((msmMusGetNumPlay(1) != 0 || msmSeGetNumPlay(1) != 0)
            && OSTicksToMilliseconds(OSGetTick() - temp_r23) < 500);
        OSReport("############CharGrpSet\n");
        temp_r25 = msmSysDelGroupBase(0);
        if (temp_r25 < 0) {
            OSReport("Del Group Error %d\n", temp_r25);
        } else {
            OSReport("Del Group OK\n");
        }
        for (i = 0; i < 4; i++) {
            temp_r30 = GWPlayerCfg[i].character;
            if (temp_r30 >= 0 && temp_r30 < 8 && temp_r30 != 0xFF) {
                charVoiceGroupStat[temp_r30] = 1;
                temp_r26 = temp_r30 + 0xA;
                temp_r3 = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(temp_r26));
                msmSysLoadGroupBase(temp_r26, temp_r3);
                HuMemDirectFree(temp_r3);
            }
        }
        sndGroupBak = -1;
    }
}

void HuAudPlayerVoicePlay(s16 arg0, s16 arg1) {
    s16 temp_r31 = GWPlayerCfg[arg0].character;

    HuAudCharVoicePlay(temp_r31, arg1);
}

void HuAudPlayerVoicePlayPos(s16 arg0, s16 arg1, Vec *arg2) {
    s16 temp_r31 = GWPlayerCfg[arg0].character;

    HuAudCharVoicePlayPos(temp_r31, arg1, arg2);
}

void HuAudPlayerVoicePlayEntry(s16 arg0, s16 arg1) {
    s16 temp_r31 = GWPlayerCfg[arg0].character;

    HuAudCharVoicePlayEntry(temp_r31, arg1);
}

s32 HuAudCharVoicePlay(s16 arg0, s16 arg1) {
    UnkMsmStruct_01 spC;

    if (omSysExitReq != 0) {
        return 0;
    }
    arg1 += (arg0 << 6);
    spC.unk00 = 0;
    if (HuAuxAVol != -1) {
        spC.unk00 |= 0x10;
    }
    if (HuAuxBVol != -1) {
        spC.unk00 |= 0x20;
    }
    spC.unk09 = HuAuxAVol;
    spC.unk0A = HuAuxBVol;
    return HuSePlay(arg1, &spC);
}

s32 HuAudCharVoicePlayPos(s16 arg0, s16 arg1, Vec *arg2) {
    UnkMsmStruct_01 spC;

    if (omSysExitReq != 0) {
        return 0;
    }
    arg1 += (arg0 << 6);
    spC.unk00 = 0x40;
    if (HuAuxAVol != -1) {
        spC.unk00 |= 0x10;
    }
    if (HuAuxBVol != -1) {
        spC.unk00 |= 0x20;
    }
    spC.unk09 = HuAuxAVol;
    spC.unk0A = HuAuxBVol;
    spC.unk10.x = arg2->x;
    spC.unk10.y = arg2->y;
    spC.unk10.z = arg2->z;
    return HuSePlay(arg1, &spC);
}

void HuAudCharVoicePlayEntry(s16 arg0, s16 arg1) {
    s32 spC[30]; // size unknown (min: 30, max: 33)
    u16 temp_r29;
    u16 i;

    arg1 += (arg0 << 6);
    temp_r29 = msmSeGetEntryID(arg1, spC);
    for (i = 0; i < temp_r29; i++) {
        msmSeStop(spC[i], 0);
    }
}

static s32 HuSePlay(s32 arg0, UnkMsmStruct_01 *arg1) {
    s32 temp_r3;

    temp_r3 = msmSePlay(arg0, arg1);
    if (temp_r3 < 0) {
        OSReport("#########SE Entry Error<SE %d:ErrorNo %d>\n", arg0, temp_r3);
    }
    return temp_r3;
}
