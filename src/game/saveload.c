#include "game/saveload.h"
#include "game/data.h"
#include "game/pad.h"
#include "game/window.h"
#include "game/flag.h"
#include "game/card.h"

#include "string.h"

static s16 SLCreateSaveWin(void);
static void SLKillSaveWin(void);


extern u8 UnMountCnt;

CARDFileInfo curFileInfo;
u8 ATTRIBUTE_ALIGN(32) saveBuf[0x4000];

u64 SLSerialNo;
s32 saveExecF;
u8 curBoxNo;
s16 curSlotNo;

u8 lbl_80132150[64] = {
    "Mario Party 4\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "File 0  00/00/0000"
};

char *SaveFileNameTbl[] = {
    "MARIPA4BOX0",
    "MARIPA4BOX1",
    "MARIPA4BOX2"
};

s32 SaveEnableF = 1;

static char *SlotNameTbl[] = {
    "A",
    "B"
};

static s32 saveMessWin = -1;

s32 SLFileOpen(char *arg0) {
    s32 temp_r3;

    if (SaveEnableF == 0) {
        return 0;
    }
    while (1) {
        temp_r3 = SLCardMount(curSlotNo);
        if (temp_r3 < 0) {
            return temp_r3;
        }
        temp_r3 = HuCardOpen(curSlotNo, arg0, &curFileInfo);
        if (temp_r3 == CARD_RESULT_NOFILE) {
            return CARD_RESULT_NOFILE;
        }
        if (temp_r3 == CARD_RESULT_WRONGDEVICE) {
            SLMessOut(7);
            return CARD_RESULT_FATAL_ERROR;
        }
        if (temp_r3 == CARD_RESULT_FATAL_ERROR) {
            SLMessOut(1);
            return CARD_RESULT_FATAL_ERROR;
        }
        if (temp_r3 == CARD_RESULT_NOCARD) {
            SLMessOut(0);
            return CARD_RESULT_NOCARD;
        }
        if (temp_r3 == CARD_RESULT_BROKEN) {
            temp_r3 = HuCardSectorSizeGet(curSlotNo);
            if (temp_r3 > 0 && temp_r3 != 0x2000) {
                SLMessOut(8);
                return CARD_RESULT_WRONGDEVICE;
            }
            UnMountCnt = 0;
            temp_r3 = SLMessOut(5);
            if (temp_r3 == 0) {
                temp_r3 = SLFormat(curSlotNo);
                if (temp_r3 != 0) {
                    return temp_r3;
                }
            } else {
                return CARD_RESULT_NOFILE;
            }
        } else {
            return CARD_RESULT_READY;
        }
    }
}

s32 SLFileCreate(char *arg0, u32 arg1, void *arg2) {
    float sp18[2];
    u32 sp14;
    u32 sp10;
    s32 temp_r30;
    s32 temp_r31;

    if (SaveEnableF == 0) {
        return 0;
    }
    temp_r31 = SLCardMount(curSlotNo);
    if (temp_r31 < 0) {
        return temp_r31;
    }
    temp_r31 = HuCardSectorSizeGet(curSlotNo);
    if (temp_r31 < 0 && temp_r31 != 0x2000) {
        SLMessOut(8);
        return CARD_RESULT_FATAL_ERROR;
    }
    temp_r31 = HuCardFreeSpaceGet(curSlotNo, &sp14, &sp10);
    if (sp10 == 0 && arg1 > sp14) {
        SLMessOut(4);
        return CARD_RESULT_INSSPACE;
    }
    if (sp10 == 0) {
        SLMessOut(2);
        return CARD_RESULT_INSSPACE;
    }
    if (arg1 > sp14) {
        SLMessOut(3);
        return CARD_RESULT_INSSPACE;
    }
    HuWinInit(1);
    HuWinMesMaxSizeGet(1, sp18, 0x10000B);
    temp_r30 = HuWinExCreateStyled(-10000.0f, 200.0f, sp18[0], sp18[1], -1, 2);
    HuWinExAnimIn(temp_r30);
    HuWinMesSet(temp_r30, 0x10000B);
    HuWinMesWait(temp_r30);
    _SetFlag(FLAG_ID_MAKE(3, 0));
    temp_r31 = HuCardCreate(curSlotNo, arg0, arg1, &curFileInfo);
    _ClearFlag(0x30000);
    if (temp_r31 < 0) {
        HuWinExAnimOut(temp_r30);
        HuWinExCleanup(temp_r30);
    }
    if (temp_r31 == CARD_RESULT_NOCARD) {
        SLMessOut(0);
        return CARD_RESULT_NOCARD;
    }
    if (temp_r31 < 0) {
        SLMessOut(1);
        return CARD_RESULT_FATAL_ERROR;
    }
    _SetFlag(FLAG_ID_MAKE(3, 0));
    temp_r31 = HuCardWrite(&curFileInfo, arg2, arg1, 0);
	_ClearFlag(FLAG_ID_MAKE(3, 0));
    if (temp_r31 < 0) {
        HuWinExAnimOut(temp_r30);
        HuWinExCleanup(temp_r30);
    }
    if (temp_r31 == CARD_RESULT_NOCARD) {
        SLMessOut(0);
        return CARD_RESULT_NOCARD;
    }
    if (temp_r31 < 0) {
        SLMessOut(1);
        return CARD_RESULT_FATAL_ERROR;
    }
    _SetFlag(FLAG_ID_MAKE(3, 0));
    temp_r31 = SLStatSet(1);
    _ClearFlag(FLAG_ID_MAKE(3, 0));
    HuWinExAnimOut(temp_r30);
    HuWinExCleanup(temp_r30);
    if (temp_r31 < 0) {
        return temp_r31;
    }
    return 0;
}

s32 SLFileWrite(s32 arg0, void *arg1) {
    float sp10[2];
    s32 temp_r31;
    s32 var_r30;

    if (SaveEnableF == 0) {
        return 0;
    }
    HuWinInit(1);
    HuWinMesMaxSizeGet(1, sp10, 0x10000B);
    temp_r31 = HuWinExCreateStyled(-10000.0f, 200.0f, sp10[0], sp10[1], -1, 2);
    HuWinExAnimIn(temp_r31);
    HuWinMesSet(temp_r31, 0x10000B);
    HuWinMesWait(temp_r31);
    HuPrcSleep(0x3C);
    _SetFlag(FLAG_ID_MAKE(3, 0));
    var_r30 = HuCardWrite(&curFileInfo, arg1, arg0, 0);
    if (var_r30 == 0) {
        var_r30 = SLStatSet(1);
    }
    _ClearFlag(FLAG_ID_MAKE(3, 0));
    HuWinExAnimOut(temp_r31);
    HuWinExCleanup(temp_r31);
    return var_r30;
}

s32 SLFileRead(s32 arg0, void *arg1) {
    s32 temp_r3;

    if (SaveEnableF == 0) {
        return 0;
    }
    temp_r3 = HuCardRead(&curFileInfo, arg1, arg0, 0);
    if (temp_r3 == CARD_RESULT_NOCARD) {
        SLMessOut(0);
    } else if (temp_r3 < 0) {
        SLMessOut(1);
    }
    return temp_r3;
}

s32 SLFileClose(void) {
    s32 temp_r31;

    if (SaveEnableF == 0) {
        return 0;
    }
    temp_r31 = HuCardClose(&curFileInfo);
    return temp_r31;
}

void SLCurSlotNoSet(s16 arg0) {
    curSlotNo = arg0;
}

void SLCurBoxNoSet(s8 arg0) {
    curBoxNo = arg0;
}

void SLSaveFlagSet(s32 arg0) {
    if (arg0 == 0) {
        GWGameStat.party_continue = 0;
        GWGameStat.story_continue = 0;
    }
    SaveEnableF = arg0;
}

s32 SLSaveFlagGet(void) {
    return SaveEnableF;
}

void SLSaveDataMake(s32 arg0, OSTime *arg1) {
    AnimData *temp_r3;
    u8 *var_r30;
    s32 i;

    var_r30 = saveBuf;
    if (arg0 != 0) {
        for (i = 0; i < 0x4000; i++) {
            var_r30[i] = 0xFF;
        }
    }
    for (i = 0; i < 0x20; i++) {
        var_r30[i] = lbl_80132150[i];
    }
    for (i = 0; i < 0x20; i++) {
        (&var_r30[0x20])[i] = lbl_80132150[i + 0x20];
    }
    temp_r3 = HuSprAnimRead(HuDataSelHeapReadNum(0x86001F, MEMORY_DEFAULT_NUM, HEAP_DATA));
    memcpy(var_r30 + 0x40, temp_r3->bmp->data, 0xC00);
    memcpy(var_r30 + 0xC40, temp_r3->bmp->palData, 0x200);
    temp_r3 = HuSprAnimRead(HuDataSelHeapReadNum(curBoxNo + 0x86001C, MEMORY_DEFAULT_NUM, HEAP_DATA));
    memcpy(var_r30 + 0xE40, temp_r3->bmp->data, 0x1000);
    memcpy(var_r30 + 0x1E40, temp_r3->bmp->palData, 0x200);
    SLSaveDataInfoSet(arg1);
}

void SLSaveDataInfoSet(OSTime *arg0) {
    s16 temp_r30;
    s16 temp_r31;
    OSCalendarTime sp8;

    OSTicksToCalendarTime(*arg0, &sp8);
    saveBuf[0x25] = curBoxNo + 0x31;
    temp_r31 = (sp8.mon + 1) / 10;
    saveBuf[0x28] = temp_r31 + 0x30;
    temp_r31 = (sp8.mon + 1) % 10;
    saveBuf[0x29] = temp_r31 + 0x30;
    temp_r31 = sp8.mday / 10;
    saveBuf[0x2B] = temp_r31 + 0x30;
    temp_r31 = sp8.mday % 10;
    saveBuf[0x2C] = temp_r31 + 0x30;
    temp_r30 = sp8.year;
    temp_r31 = temp_r30 / 1000;
    saveBuf[0x2E] = temp_r31 + 0x30;
    temp_r30 -= temp_r31 * 1000;
    temp_r31 = temp_r30 / 100;
    saveBuf[0x2F] = temp_r31 + 0x30;
    temp_r30 -= temp_r31 * 100;
    temp_r31 = temp_r30 / 10;
    saveBuf[0x30] = temp_r31 + 0x30;
    temp_r30 -= temp_r31 * 10;
    saveBuf[0x31] = temp_r30 + 0x30;
}

void SLCommonSet(void) {
    OSTime temp_r28;

    temp_r28 = OSGetTime();
    GWGameStat.create_time = temp_r28;
    memcpy(saveBuf + 0x2040, &GWGameStat, 0x118);
    SLSaveDataInfoSet(&temp_r28);
}

void SLSaveBoard(void) {
    s16 i;

    memcpy(saveBuf + 0x2158, &GWSystem, 0xDC);
    for (i = 0; i < 4; i++) {
        memcpy(&saveBuf[i * 0x30 + 0x2234], &GWPlayer[i], 0x30);
    }
}

void SLSaveBoardBackup(void) {
    s16 i;

    memcpy(saveBuf + 0x22F4, &GWSystem, 0xDC);
    for (i = 0; i < 4; i++) {
        memcpy(&saveBuf[i * 0x30 + 0x23D0], &GWPlayer[i], 0x30);
    }
}

s32 SLSave(void) {
    s32 var_r31;

    while (1) {
        SLCheckSumSet();
        var_r31 = SLFileOpen(SaveFileNameTbl[curBoxNo]);
        if (var_r31 == CARD_RESULT_NOFILE) {
            if (!SLSerialNoCheck()) {
                SLMessOut(9);
            } else {
                SLCreateSaveWin();
                var_r31 = SLFileCreate(SaveFileNameTbl[curBoxNo], 0x4000, saveBuf);
                SLKillSaveWin();
                if (var_r31 >= 0) {
                    SLSerialNoGet();
                    goto block_32;
                }
            }
        } else {
            if (var_r31 == CARD_RESULT_NOCARD) {
                var_r31 = SLMessOut(0xA);
                if (var_r31 != 0) {
                    SLMessOut(0xB);
                    continue;
                }
                SLSaveFlagSet(0);
                break;
            }
            if (var_r31 >= 0) {
                if (!SLSerialNoCheck()) {
                    SLMessOut(9);
                } else {
                    SLCreateSaveWin();
                    var_r31 = SLFileWrite(0x4000, saveBuf);
                    SLKillSaveWin();
                    if (var_r31 == CARD_RESULT_NOCARD) {
                        SLMessOut(0);
                    } else if (var_r31 == CARD_RESULT_WRONGDEVICE) {
                        SLMessOut(7);
                    } else if (var_r31 == CARD_RESULT_BROKEN) {
                        var_r31 = HuCardSectorSizeGet(curSlotNo);
                        if (var_r31 > 0 && var_r31 != 0x2000) {
                            SLMessOut(8);
                            goto block_36;
                        }
                        UnMountCnt = 0;
                        var_r31 = SLMessOut(5);
                        if (var_r31 == 0) {
                            var_r31 = SLFormat(curSlotNo);
                            if (var_r31 != 0) {
                                return var_r31;
                            }
                            continue;
                        } else {
                            var_r31 = CARD_RESULT_BROKEN;
                        }
                    } else if (var_r31 < 0) {
                        SLMessOut(1);
                    }
block_32:
                    SLFileClose();
                    if (var_r31 >= 0) {
                        HuCardUnMount(curSlotNo);
                        return 1;
                    }
                }
            }
        }
block_36:
        var_r31 = SLMessOut(0xA);
        if (var_r31 != 0) {
            SLMessOut(0xB);
        } else {
            SLSaveFlagSet(0);
            break;
        }
    }
    HuCardUnMount(curSlotNo);
    return 0;
}

static s16 SLCreateSaveWin(void) {
    float sp8[2];
    s16 temp_r3;

    HuWinInit(1);
    HuWinInsertMesSizeGet(MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]), 0);
    HuWinMesMaxSizeGet(1, sp8, 0x100044);
    temp_r3 = HuWinExCreateStyled(-10000.0f, 150.0f, sp8[0], sp8[1], -1, 2);
    saveMessWin = temp_r3;
    HuWinExAnimIn(temp_r3);
    HuWinInsertMesSet(temp_r3, MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]), 0);
    HuWinMesSet(temp_r3, 0x100044);
    HuWinMesWait(temp_r3);
    return temp_r3;
}

static void SLKillSaveWin(void) {
    if (saveMessWin != -1) {
        HuWinExAnimOut(saveMessWin);
        HuWinExCleanup(saveMessWin);
        saveMessWin = -1;
    }
}

s32 SLLoad(void) {
    s32 var_r31;
    u16 *temp_r29;
    u16 temp_r27;

    var_r31 = SLFileOpen(SaveFileNameTbl[curBoxNo]);
    if (var_r31 >= 0) {
        var_r31 = SLFileRead(0x4000, saveBuf);
        SLFileClose();
        if (var_r31 >= 0) {
            temp_r29 = (u16*) &saveBuf[0x2490];
            temp_r27 = SLCheckSumGet();
            *temp_r29 == temp_r27;
        }
    }
    HuCardUnMount(curSlotNo);
    return 0;
}

void SLLoadGameStat(void) {
    memcpy(&GWGameStat, saveBuf + 0x2040, 0x118);
}

void SLLoadBoard(void) {
    s16 i;

    memcpy(&GWSystem, saveBuf + 0x2158, 0xDC);
    for (i = 0; i < 4; i++) {
        memcpy(&GWPlayer[i], &saveBuf[i * 0x30 + 0x2234], 0x30);
        GWPlayerCfg[i].character = GWPlayer[i].character;
        GWPlayerCfg[i].pad_idx = GWPlayer[i].port;
        GWPlayerCfg[i].diff = GWPlayer[i].diff;
        GWPlayerCfg[i].iscom = GWPlayer[i].com;
        GWPlayerCfg[i].group = GWPlayer[i].team;
    }
}

void SLLoadBoardBackup(void) {
    s16 i;

    memcpy(&GWSystem, saveBuf + 0x22F4, 0xDC);
    for (i = 0; i < 4; i++) {
        memcpy(&GWPlayer[i], &saveBuf[i * 0x30 + 0x23D0], 0x30);
        GWPlayerCfg[i].character = GWPlayer[i].character;
        GWPlayerCfg[i].pad_idx = GWPlayer[i].port;
        GWPlayerCfg[i].diff = GWPlayer[i].diff;
        GWPlayerCfg[i].iscom = GWPlayer[i].com;
        GWPlayerCfg[i].group = 0;
    }
}

void SLSerialNoGet(void) {
    CARDGetSerialNo(curSlotNo, &SLSerialNo);
}

BOOL SLSerialNoCheck(void) {
    s32 var_r31;
    u64 sp8;

    if (SLSerialNo == 0) {
        return TRUE;
    }
    var_r31 = CARDGetSerialNo(curSlotNo, &sp8);
    if (var_r31 < 0) {
        return TRUE;
    }
    if (sp8 != SLSerialNo) {
        return FALSE;
    }
    return TRUE;
}

BOOL SLCheckSumCheck(void) {
    u16 *temp_r31 = (u16*) &saveBuf[0x2490];
    u16 temp_r3 = SLCheckSumGet();

    if (*temp_r31 == temp_r3) {
        return TRUE;
    }
    return FALSE;
}

u16 SLCheckSumGet(void) {
    u32 i;
    u32 var_r30;

    for (i = var_r30 = 0; i < 0x2490; i++) {
        var_r30 += saveBuf[i];
    }
    var_r30 = ~var_r30;
    return (u16) var_r30 & 0xFFFF;
}

void SLCheckSumSet(void) {
    u16 temp_r31 = SLCheckSumGet();

    saveBuf[0x2490] = (temp_r31 >> 8) & 0xFF;
    saveBuf[0x2491] = temp_r31;
}

s32 SLStatSet(s32 arg0) {
    CARDStat sp8;
    s32 temp_r29;
    s32 temp_r3;

    temp_r29 = curFileInfo.fileNo;
    temp_r3 = CARDGetStatus(curSlotNo, temp_r29, &sp8);
    if (temp_r3 == -3) {
        if (arg0 != 0) {
            SLMessOut(0);
        }
        return -3;
    }
    if (temp_r3 < 0) {
        if (arg0 != 0) {
            SLMessOut(1);
        }
        return CARD_RESULT_FATAL_ERROR;
    }
    sp8.commentAddr = 0;
    sp8.iconAddr = 0x40;
	CARDSetBannerFormat(&sp8, CARD_STAT_BANNER_C8);
	CARDSetIconFormat(&sp8, 0, CARD_STAT_ICON_C8);
	CARDSetIconFormat(&sp8, 1, CARD_STAT_ICON_C8);
	CARDSetIconFormat(&sp8, 2, CARD_STAT_ICON_C8);
	CARDSetIconFormat(&sp8, 3, CARD_STAT_ICON_C8);
    CARDSetIconSpeed(&sp8, 0, CARD_STAT_SPEED_MIDDLE);
	CARDSetIconSpeed(&sp8, 1, CARD_STAT_SPEED_MIDDLE);
	CARDSetIconSpeed(&sp8, 2, CARD_STAT_SPEED_MIDDLE);
	CARDSetIconSpeed(&sp8, 3, CARD_STAT_SPEED_MIDDLE);
	CARDSetIconSpeed(&sp8, 4, CARD_STAT_SPEED_END);
    CARDSetIconAnim(&sp8, CARD_STAT_ANIM_LOOP);

    temp_r3 = CARDSetStatus(curSlotNo, temp_r29, &sp8);
    if (temp_r3 == CARD_RESULT_NOCARD) {
        if (arg0 != 0) {
            SLMessOut(0);
        }
        return CARD_RESULT_NOCARD;
    }
    if (temp_r3 < 0) {
        if (arg0 != 0) {
            SLMessOut(1);
        }
        return CARD_RESULT_FATAL_ERROR;
    }
    return temp_r3;
}

s32 SLCardMount(s16 arg0) {
    s32 temp_r3;

    while (1) {
        temp_r3 = HuCardMount(curSlotNo);
        if (temp_r3 == CARD_RESULT_WRONGDEVICE) {
            SLMessOut(7);
            return temp_r3;
        }
        if (temp_r3 == CARD_RESULT_FATAL_ERROR) {
            SLMessOut(1);
            return CARD_RESULT_FATAL_ERROR;
        }
        if (temp_r3 == CARD_RESULT_NOCARD) {
            SLMessOut(0);
            return CARD_RESULT_NOCARD;
        }
        if (temp_r3 == CARD_RESULT_BROKEN) {
            temp_r3 = HuCardSectorSizeGet(curSlotNo);
            if (temp_r3 > 0 && temp_r3 != 0x2000) {
                SLMessOut(8);
                return CARD_RESULT_WRONGDEVICE;
            }
            UnMountCnt = 0;
            temp_r3 = SLMessOut(5);
            if (temp_r3 == 0) {
                temp_r3 = SLFormat(curSlotNo);
                if (temp_r3 != 0) {
                    return temp_r3;
                }
            } else {
                return CARD_RESULT_FATAL_ERROR;
            }
        } else {
            break;
        }
    }
    temp_r3 = HuCardSectorSizeGet(curSlotNo);
    if (temp_r3 < 0) {
        SLMessOut(1);
        return temp_r3;
    }
    if (temp_r3 != 0x2000) {
        SLMessOut(8);
        return CARD_RESULT_WRONGDEVICE;
    }
    return 0;
}

s32 SLFormat(s16 arg0) {
    float sp8[2];
    s16 temp_r24;
    s16 temp_r3;
    s16 temp_r3_2;
    OSTime temp_r19;

    HuWinInit(1);
    HuWinInsertMesSizeGet(MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]), 0);
    HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(16, 56));
    temp_r3 = HuWinExCreateStyled(-10000.0f, 150.0f, sp8[0], sp8[1], -1, 2);
    HuWinExAnimIn(temp_r3);
    HuWinInsertMesSet(temp_r3, MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]), 0);
    HuWinMesSet(temp_r3, MAKE_MESSID(16, 56));
    HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(16, 11));
    temp_r3_2 = HuWinExCreateStyled(-10000.0f, 200.0f, sp8[0], sp8[1], -1, 2);
    HuWinExAnimIn(temp_r3_2);
    HuWinMesSet(temp_r3_2, MAKE_MESSID(16, 11));
    HuWinMesWait(temp_r3_2);
    HuPrcSleep(0x1E);
    if (UnMountCnt & (1 << curSlotNo)) {
        HuWinExAnimOut(temp_r3);
        HuWinExCleanup(temp_r3);
        HuWinExAnimOut(temp_r3_2);
        HuWinExCleanup(temp_r3_2);
        SLMessOut(0xC);
        return 0;
    }
    _SetFlag(FLAG_ID_MAKE(3, 0));
    temp_r24 = HuCardFormat(curSlotNo);
    _ClearFlag(FLAG_ID_MAKE(3, 0));
    if (temp_r24 < 0) {
        HuWinExAnimOut(temp_r3);
        HuWinExCleanup(temp_r3);
        HuWinExAnimOut(temp_r3_2);
        HuWinExCleanup(temp_r3_2);
    }
    if (temp_r24 == CARD_RESULT_FATAL_ERROR) {
        SLMessOut(6);
        SLMessOut(1);
        return CARD_RESULT_FATAL_ERROR;
    }
    if (temp_r24 == CARD_RESULT_NOCARD) {
        SLMessOut(0);
        return CARD_RESULT_NOCARD;
    }
    if (temp_r24 == CARD_RESULT_WRONGDEVICE) {
        SLMessOut(7);
        return temp_r24;
    }
    HuWinExAnimOut(temp_r3);
    HuWinExCleanup(temp_r3);
    HuWinExAnimOut(temp_r3_2);
    HuWinExCleanup(temp_r3_2);
    CARDGetSerialNo(curSlotNo, &SLSerialNo);
    curBoxNo = 0;
    temp_r19 = OSGetTime();
    SLSaveDataMake(0, &temp_r19);
    SLCheckSumSet();
    return temp_r24;
}

s16 SLMessOut(s16 arg0) {
    WindowData *var_r26;
    float sp8[2];
    u32 var_r29;
    s32 var_r31;
    s32 var_r27;
    s16 temp_r3;
    s16 var_r28;

    var_r28 = -1;
    var_r29 = 0;
    var_r27 = 0;
    HuWinInit(1);
	SLKillSaveWin();
    switch (arg0) {
        case 0:
            var_r31 = MAKE_MESSID(16, 2);
            break;
        case 1:
            var_r31 = MAKE_MESSID(16, 83);
            HuWinInsertMesSizeGet(MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]), 0);
            var_r29 = MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]);
            break;
        case 2:
            HuWinInsertMesSizeGet(MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]), 0);
            var_r29 = MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]);
            var_r31 = MAKE_MESSID(16, 74);
            break;
        case 3:
            var_r31 = MAKE_MESSID(16, 74);
            HuWinInsertMesSizeGet(MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]), 0);
            var_r29 = MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]);
            break;
        case 4:
            var_r31 = MAKE_MESSID(16, 74);
            HuWinInsertMesSizeGet(MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]), 0);
            var_r29 = MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]);
            break;
        case 5:
            HuWinInsertMesSizeGet(MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]), 0);
            var_r29 = MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]);
            var_r31 = MAKE_MESSID(16, 4);
            var_r27 = 1;
            break;
        case 6:
            var_r31 = MAKE_MESSID(16, 54);
            break;
        case 7:
            HuWinInsertMesSizeGet(MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]), 0);
            var_r29 = MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]);
            var_r31 = MAKE_MESSID(16, 55);
            break;
        case 8:
            HuWinInsertMesSizeGet(MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]), 0);
            var_r29 = MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]);
            var_r31 = MAKE_MESSID(16, 57);
            break;
        case 9:
            HuWinInsertMesSizeGet(MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]), 0);
            var_r29 = MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]);
            var_r31 = MAKE_MESSID(16, 69);
            break;
        case 10:
            var_r31 = MAKE_MESSID(16, 70);
            var_r27 = 1;
            break;
        case 11:
            HuWinInsertMesSizeGet(MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]), 0);
            var_r29 = MAKE_MESSID_PTR(SlotNameTbl[curSlotNo]);
            var_r31 = MAKE_MESSID(16, 72);
            break;
        case 12:
            var_r31 = MAKE_MESSID(16, 80);
            break;
    }
    if (var_r31 == MAKE_MESSID(16, 4)) {
        HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(16, 78));
    } else {
        HuWinMesMaxSizeGet(1, sp8, var_r31);
    }
    temp_r3 = HuWinExCreateStyled(-10000.0f, 200.0f, sp8[0], sp8[1], -1, 2);
    var_r26 = &winData[temp_r3];
    var_r26->active_pad = 1;
    if (var_r29 != 0) {
        HuWinInsertMesSet(temp_r3, var_r29, 0);
    }
    HuWinAttrSet(temp_r3, 0x10);
    HuWinExAnimIn(temp_r3);
    HuWinMesSet(temp_r3, var_r31);
    HuWinMesWait(temp_r3);
    if (var_r27 != 0) {
        var_r28 = HuWinChoiceGet(temp_r3, 1);
        if (arg0 == 5 && var_r28 == 0) {
            HuWinMesSet(temp_r3, MAKE_MESSID(16, 78));
            HuWinMesWait(temp_r3);
            var_r28 = HuWinChoiceGet(temp_r3, 1);
        }
    }
    if (arg0 == 0xB) {
        while (!(HuPadBtnDown[0] & 0x100)) {
            HuPrcVSleep();
        }
    }
    HuWinExAnimOut(temp_r3);
    HuWinExCleanup(temp_r3);
    return var_r28;
}
