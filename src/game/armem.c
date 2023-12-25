#include "game/armem.h"
#include "game/data.h"

typedef struct some_armem_struct0 {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ char unk01[1];
    /* 0x02 */ u16 unk02;
    /* 0x04 */ void *unk04;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ struct some_armem_struct0 *unk0C;
} SomeArmemStruct0; // Size 0x10

typedef struct {
    /* 0x00 */ ARQRequest unk00;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ void *unk24;
} SomeArmemStruct1; // Size 0x28

static void ArqCallBack(u32 pointerToARQRequest);
static void ArqCallBackAM(u32 pointerToARQRequest);
static void ArqCallBackAMFileRead(u32 pointerToARQRequest);

static s32 ATTRIBUTE_ALIGN(32) preLoadBuf[16];
static SomeArmemStruct1 ARQueBuf[16];
static ARQRequest arqReq;
static SomeArmemStruct0 ARInfo[64];

static s32 ARBase;
static s32 arqCnt;
static s16 arqIdx;

void HuARInit(void) {
    s32 temp_r30;
    s16 i;

    if (!ARCheckInit()) {
        ARInit(NULL, 0);
        ARQInit();
    }
    for (i = 0; i < 64; i++) {
        ARInfo[i].unk04 = 0;
    }
    temp_r30 = ARGetSize() - 0x808000;
    ARBase = 0x808000;
    ARInfo[0].unk04 = (void*) ARBase;
    ARInfo[0].unk08 = temp_r30;
    ARInfo[0].unk00 = 0;
    ARInfo[0].unk0C = &ARInfo[1];
    ARInfo[0].unk02 = 0xFFFF;
    ARInfo[1].unk04 = (void*) -1;
    ARInfo[1].unk08 = 0;
    ARInfo[1].unk00 = 1;
    ARInfo[1].unk0C = 0;
    ARInfo[1].unk02 = 0xFFFF;
    arqCnt = 0;
}

void *HuARMalloc(u32 arg0) {
    SomeArmemStruct0 *var_r27;
    SomeArmemStruct0 *var_r30;
    SomeArmemStruct0 *var_r31;
    s16 i;

    arg0 = (arg0 + 0x1F) & ~0x1F;
    var_r31 = var_r27 = ARInfo;
    while (var_r31->unk0C != 0) {
        if (var_r31->unk00 == 0 && var_r31->unk08 >= arg0) {
            break;
        }
        var_r27 = var_r31;
        var_r31 = var_r31->unk0C;
    }
    if (var_r31->unk0C == 0) {
        OSReport("Can't ARAM Allocated %x\n", arg0);
        HuAMemDump();
        return 0;
    }
    var_r31->unk00 = 1;
    if (var_r31->unk08 == arg0 && var_r27 != var_r31) {
        var_r31->unk02 = 0xFFFF;
    } else {
        var_r30 = &ARInfo[1];
        for (i = 0; i < 63; i++, var_r30++) {
            if (var_r30->unk04 == 0) {
                break;
            }
        }
        if (i == 63) {
            OSReport("Can't ARAM Allocated %x\n", arg0);
            return 0;
        }
        var_r30->unk0C = var_r31->unk0C;
        var_r31->unk0C = var_r30;
        var_r30->unk08 = var_r31->unk08 - arg0;
        var_r30->unk04 = (u8*) var_r31->unk04 + arg0;
        var_r31->unk08 = arg0;
        var_r31->unk02 = var_r30->unk02 = 0xFFFF;
        var_r30->unk00 = 0;
    }
    return var_r31->unk04;
}

void HuARFree(void *arg0) {
    SomeArmemStruct0 *var_r30;
    SomeArmemStruct0 *temp_r29;
    SomeArmemStruct0 *var_r31;

    var_r31 = var_r30 = ARInfo;
    while (var_r31->unk0C != 0) {
        if (var_r31->unk04 == arg0) {
            break;
        }
        var_r30 = var_r31;
        var_r31 = var_r31->unk0C;
    }
    if (var_r31->unk00 != 0) {
        if (var_r31->unk0C == 0 && var_r31->unk04 != arg0) {
            OSReport("Can't ARAM Free %x\n", arg0);
            return;
        }
        temp_r29 = var_r31->unk0C;
        if (temp_r29->unk0C != 0 && temp_r29->unk00 == 0) {
            if (var_r31->unk04 > temp_r29->unk04) {
                var_r31->unk04 = temp_r29->unk04;
            }
            var_r31->unk08 += temp_r29->unk08;
            var_r31->unk0C = temp_r29->unk0C;
            temp_r29->unk04 = 0;
        }
        if (var_r30 != var_r31 && var_r30->unk0C != 0 && var_r30->unk00 == 0) {
            if (var_r30->unk04 > var_r31->unk04) {
                var_r30->unk04 = var_r31->unk04;
            }
            var_r30->unk08 += var_r31->unk08;
            var_r30->unk0C = var_r31->unk0C;
            var_r31->unk04 = 0;
        }
        var_r31->unk00 = 0;
        var_r31->unk02 = 0xFFFF;
    }
}

static char lbl_80130705[] = "Can't Find ARAM %x\n";

static inline SomeArmemStruct0 *ArmemInlineFunc1(void *arg0) {
    SomeArmemStruct0 *temp_var1;
    SomeArmemStruct0 *temp_var2;

    temp_var1 = temp_var2 = ARInfo;
    while (temp_var1->unk0C != 0) {
        if (temp_var1->unk04 == arg0) {
            break;
        }
        temp_var2 = temp_var1;
        temp_var1 = temp_var1->unk0C;
    }
    if (temp_var1->unk0C == 0 && temp_var1->unk04 != arg0) {
        OSReport(lbl_80130705, arg0);
        return NULL;
    } else {
        return temp_var1;
    }
}

static inline u32 ArmemInlineFunc2(void *arg0) {
    SomeArmemStruct0 *temp_var1;
    SomeArmemStruct0 *temp_var2;

    temp_var1 = temp_var2 = ARInfo;
    while (temp_var1->unk0C != 0) {
        if (temp_var1->unk04 == arg0) {
            break;
        }
        temp_var2 = temp_var1;
        temp_var1 = temp_var1->unk0C;
    }
    if (temp_var1->unk0C == 0 && temp_var1->unk04 != arg0) {
        OSReport(lbl_80130705, arg0);
        return 0;
    } else {
        return temp_var1->unk08;
    }
}

void HuAMemDump(void) {
    SomeArmemStruct0 *var_r31;

    OSReport("ARAM DUMP ======================\n");
    OSReport("AMemPtr  Stat Length\n");
    for (var_r31 = ARInfo; var_r31->unk0C != 0; var_r31 = var_r31->unk0C) {
        OSReport("%08x:%04x,%08x,%08x\n", var_r31->unk04, var_r31->unk00, var_r31->unk08, var_r31->unk02);
    }
    OSReport("%08x:%04x,%08x\n", var_r31->unk04, var_r31->unk00, var_r31->unk08);
    OSReport("================================\n");
}

void *HuAR_DVDtoARAM(u32 arg0) {
    DataReadStat *temp_r28;
    SomeArmemStruct0 *var_r27;
    void *temp_r3;

    temp_r3 = HuARDirCheck(arg0);
    if (temp_r3 != 0) {
        return temp_r3;
    }
    temp_r28 = HuDataDirRead(arg0);
    DirDataSize = (DirDataSize + 0x1F) & ~0x1F;
    temp_r3 = HuARMalloc(DirDataSize);
    if (temp_r3 == 0) {
        return 0;
    }
    var_r27 = ArmemInlineFunc1(temp_r3);
    var_r27->unk02 = (arg0 >> 16);
    arqCnt++;
    ARQPostRequest(&arqReq, 0x1234, 0, 0, (u32) temp_r28->dir, (u32) temp_r3, DirDataSize, ArqCallBack);
    OSReport("ARAM Trans %x\n", temp_r3);
    while (HuARDMACheck());
    HuDataDirClose(arg0);
    return temp_r3;
}

static void ArqCallBack(u32 pointerToARQRequest) {
    arqCnt--;
    (void)pointerToARQRequest; // required to match (return?)
}

void HuAR_MRAMtoARAM(s32 arg0) {
    HuAR_MRAMtoARAM2(HuDataGetDirPtr(arg0));
}

void *HuAR_MRAMtoARAM2(void *arg0) {
    SomeArmemStruct0 *var_r27;
    DataReadStat *temp_r3_3;
    u32 temp_r28;
    void *temp_r3;

    temp_r3_3 = HuDataGetStatus(arg0);
    temp_r3 = HuARDirCheck(temp_r3_3->dir_id << 16);
    if (temp_r3 != 0) {
        return temp_r3;
    }
    temp_r28 = HuMemMemorySizeGet(arg0);
    temp_r28 = (temp_r28 + 0x1F) & ~0x1F;
    temp_r3 = HuARMalloc(temp_r28);
    if (temp_r3 == 0) {
        return 0;
    }
    var_r27 = ArmemInlineFunc1(temp_r3);
    var_r27->unk02 = temp_r3_3->dir_id;
    arqCnt++;
    ARQPostRequest(&arqReq, 0x1234, 0, 0, (u32) arg0, (u32) temp_r3, temp_r28, ArqCallBack);
    return temp_r3;
}

void HuAR_ARAMtoMRAM(void *dst) {
    HuAR_ARAMtoMRAMNum(dst, 0);
}

void *HuAR_ARAMtoMRAMNum(void *dst, s32 num) {
    SomeArmemStruct0 *var_r25;
    s32 var_r26;
    void *temp_r3;

    var_r25 = ArmemInlineFunc1(dst);
    if (HuDataReadChk(var_r25->unk02 << 16) >= 0) {
        return;
    }
    var_r26 = ArmemInlineFunc2(dst);
    temp_r3 = HuMemDirectMallocNum(HEAP_DVD, var_r26, num);
    if (temp_r3 == 0) {
        return 0;
    }
    DCFlushRangeNoSync(temp_r3, var_r26);
    ARQueBuf[arqIdx].unk20 = (var_r25->unk02 << 16);
    ARQueBuf[arqIdx].unk24 = temp_r3;
    arqCnt++;
    PPCSync();
    ARQPostRequest(&ARQueBuf[arqIdx].unk00, 0x1234, 1, 0, (u32) dst, (u32) temp_r3, var_r26, ArqCallBackAM);
    arqIdx++;
    arqIdx &= 0xF;
    return temp_r3;
}

static void ArqCallBackAM(u32 pointerToARQRequest) {
    SomeArmemStruct1 *sp8 = (SomeArmemStruct1*) pointerToARQRequest;

    arqCnt--;
    HuDataDirSet(sp8->unk24, sp8->unk20);
}

BOOL HuARDMACheck(void) {
    return arqCnt;
}

void *HuARDirCheck(u32 dir) {
    SomeArmemStruct0 *var_r31;

    var_r31 = ARInfo;
    dir >>= 16;
    while (var_r31->unk0C != 0) {
        if (var_r31->unk00 == 1 && var_r31->unk02 == dir) {
            return var_r31->unk04;
        }
        var_r31 = var_r31->unk0C;
    }

    return 0;
}

void HuARDirFree(u32 arg0) {
    SomeArmemStruct0 *var_r31;

    var_r31 = ARInfo;
    arg0 >>= 16;
    while (var_r31->unk0C != 0) {
        if (var_r31->unk02 == arg0) {
            HuARFree(var_r31->unk04);
            break;
        }
        var_r31 = var_r31->unk0C;
    }
}

void *HuAR_ARAMtoMRAMFileRead(u32 arg0, u32 arg1, HeapID arg2) {
    s32 *temp_r29;
    void *temp_r3;
    void *temp_r3_2;
    void *var_r20;
    s32 temp_r24;
    s32 var_r22;
    u8 *var_r17;

    if ((var_r17 = HuARDirCheck(arg0)) == 0) {
        OSReport("Error: data none on ARAM %0x\n", arg0);
        HuAMemDump();
        return 0;
    }
    DCInvalidateRange(&preLoadBuf, sizeof(preLoadBuf));
    var_r20 = var_r17 + ((u32) (((u16) arg0 + 1) * 4) & 0xFFFFFFFE0);
    arqCnt++;
    ARQPostRequest(&ARQueBuf[arqIdx].unk00, 0x1234, 1, 0, (u32) var_r20, (u32) &preLoadBuf, sizeof(preLoadBuf), ArqCallBackAMFileRead);
    arqIdx++;
    arqIdx &= 0xF;
    while (HuARDMACheck());
    temp_r29 = &preLoadBuf[(arg0 + 1) & 7];
    temp_r24 = temp_r29[0];
    var_r20 = var_r17 + (temp_r24 & 0xFFFFFFFE0);
    if (temp_r29[1] - temp_r24 < 0) {
        var_r22 = (ArmemInlineFunc2(var_r17) - temp_r24 + 0x3F) & 0xFFFFFFFE0;
    } else {
        var_r22 = (temp_r29[1] - temp_r24 + 0x3F) & 0xFFFFFFFE0;
    }
    temp_r3_2 = HuMemDirectMalloc(HEAP_DVD, var_r22);
    if (temp_r3_2 == 0) {
        return 0;
    }
    DCFlushRangeNoSync(temp_r3_2, var_r22);
    arqCnt++;
    PPCSync();
    ARQPostRequest(&ARQueBuf[arqIdx].unk00, 0x1234, 1, 0, (u32) var_r20, (u32) temp_r3_2, (u32) var_r22, ArqCallBackAMFileRead);
    arqIdx++;
    arqIdx &= 0xF;
    while (HuARDMACheck());
    temp_r29 = (s32*) ((u8*) temp_r3_2 + (temp_r24 & 0x1F));
    temp_r3 = HuMemDirectMallocNum(arg2, (temp_r29[0] + 1) & ~1, arg1);
    if (temp_r3 == 0) {
        return 0;
    }
    HuDecodeData(&temp_r29[2], temp_r3, temp_r29[0], temp_r29[1]);
    HuMemDirectFree(temp_r3_2);
    return temp_r3;
}

static void ArqCallBackAMFileRead(u32 pointerToARQRequest) {
    arqCnt--;
    (void)pointerToARQRequest; // required to match (return?)
}
