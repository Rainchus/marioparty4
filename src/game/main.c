#include "game/gamework_data.h"
#include "game/dvd.h"
#include "game/printfunc.h"
#include "game/object.h"
#include "game/wipe.h"
#include "game/init.h"
#include "game/process.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/sprite.h"
#include "game/hsfformat.h"
#include "game/hsfman.h"
#include "game/perf.h"
#include "game/gamework.h"

extern FileListEntry _ovltbl[];
u32 GlobalCounter;
u32 lbl_801D3A50;
u32 lbl_801D3A4C;
u32 lbl_801D3A48;
u32 lbl_801D3A44;
u32 lbl_801D3A40;
u32 lbl_801D3A3C;
u32 lbl_801D3A38;
u32 lbl_801D3A34;
u32 lbl_801D3A30;
u32 lbl_801D3A2C;
u32 lbl_801D3A28;
u32 lbl_801D3A24;
u32 lbl_801D3A20;
u32 lbl_801D3A1C;
u32 lbl_801D3A18;
u32 lbl_801D3A14;
u32 lbl_801D3A10;
u32 lbl_801D3A0C;
u32 lbl_801D3A08;
s32 HuDvdErrWait;
s32 SystemInitF;

void main(void) {
    u32 sp14;
    u32 sp10;
    s32 spC;
    s32 sp8;
    s16 var_r31;
    s32 temp_r30;

    HuDvdErrWait = 0;
    SystemInitF = 0;
    HuSysInit(&GXNtsc480IntDf);
    HuPrcInit();
    HuPadInit();
    GWInit();
    pfInit();
    GlobalCounter = 0;
    HuSprInit();
    Hu3DInit();
    HuDataInit();
    HuPerfInit();
    HuPerfCreate("USR0", 0xFF, 0xFF, 0xFF, 0xFF);
    HuPerfCreate("USR1", 0,    0xFF, 0xFF, 0xFF);
    WipeInit(RenderMode);
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        GWPlayerCfg[var_r31].character = -1;
    }
    
    omMasterInit(0, _ovltbl, 0x63, 1);
    VIWaitForRetrace();
    
    if (VIGetNextField() == 0) {
        OSReport("VI_FIELD_BELOW\n");
        VIWaitForRetrace();
    }
    while (1) {
        temp_r30 = VIGetRetraceCount();
        if (HuSoftResetButtonCheck() != 0 || HuDvdErrWait != 0) {
            continue;
        }
        HuPerfZero();
        HuPerfBegin(2);
        HuSysBeforeRender();
        GXSetGPMetric(GX_PERF0_CLIP_VTX, GX_PERF1_VERTICES);
        GXClearGPMetric();
        GXSetVCacheMetric(GX_VC_ALL);
        GXClearVCacheMetric();
        GXClearPixMetric();
        GXClearMemMetric();
        HuPerfBegin(0);
        Hu3DPreProc();
        HuPadRead();
        pfClsScr();
        HuPrcCall(1);
        MGSeqMain();
        HuPerfBegin(1);
        Hu3DExec();
        HuDvdErrorWatch();
        WipeExecAlways();
        HuPerfEnd(0);
        pfDrawFonts();
        HuPerfEnd(1);
        msmMusFdoutEnd();
        HuSysDoneRender(temp_r30);
        GXReadGPMetric(&sp14, &sp10);
        GXReadVCacheMetric(&lbl_801D3A50, &lbl_801D3A4C, &lbl_801D3A48);
        GXReadPixMetric(&lbl_801D3A44, &lbl_801D3A40, &lbl_801D3A3C, &lbl_801D3A38, &lbl_801D3A34, &lbl_801D3A30);
        GXReadMemMetric(&lbl_801D3A2C, &lbl_801D3A28, &lbl_801D3A24, &lbl_801D3A20, &lbl_801D3A1C, &lbl_801D3A18, &lbl_801D3A14, &lbl_801D3A10, &lbl_801D3A0C, &lbl_801D3A08);
        HuPerfEnd(2);
        GlobalCounter++;
    }
}

void HuSysVWaitSet(s16 arg0) {
    minimumVcount = arg0;
    minimumVcountf = arg0;
}

s16 HuSysVWaitGet(void) {
    return (s16) minimumVcount;
}

s32 rnd_seed = 0x0000D9ED;

s32 rand8(void) {
    rnd_seed = (rnd_seed * 0x41C64E6D) + 0x3039;
    return (u8)(((rnd_seed + 1) >> 0x10) & 0xFF);
}
