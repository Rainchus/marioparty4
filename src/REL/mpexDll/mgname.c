#include "ext_math.h"
#include "game/armem.h"
#include "game/audio.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "REL/mpexDll.h"

s32 lbl_1_data_788[0xC6] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x140025,
    0x140026,
    0x140027,
    0x140028,
    0x140029,
    0x14002A,
    0x14002B,
    0x14002C,
    0x14002D,
    0x14002E,
    0x140025,
    0x140025,
    0x140025,
    0x14002F,
    0x140025,
    0x140025,
    0x140025,
    0x140034,
    0x140035,
    0x140036,
    0x140037,
    0x140038,
    0x140039,
    0x14003A,
    0x14003B,
    0x14003C,
    0x14003D,
    0x14003E,
    0x14003F,
    0x140040,
    0x140041,
    0x140042,
    0x140043,
    0x140044,
    0x140045,
    0x140046,
    0x140047,
    0x140048,
    0x140049,
    0x14004A,
    0x14004B,
    0x14004C,
    0x14004D,
    0x140042,
    0x140032,
    0x140042,
    0x140042,
    0x140042,
    0x140042,
    0x14004E,
    0x14004F,
    0x140050,
    0x140051,
    0x140052,
    0x140053,
    0x140054,
    0x140055,
    0x140056,
    0x140057,
    0x140058,
    0x140059,
    0x14005A,
    0x14005B,
    0x14005C,
    0x14005D,
    0x14005E,
    0x14005F,
    0x140060,
    0x140061,
    0x140062,
    0x140063,
    0x140064,
    0x140065,
    0x140066,
    0x140067,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x14002F,
    0x140033,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140030,
    0x140031,
    0x140025,
    0x140025,
};

s32 fn_1_1CB80(MpexDllUnkStruct3 *arg0, u8 *arg1, s16 arg2)
{
    u8 *var_r31;
    s16 var_r30;
    s16 *var_r29;
    s16 var_r28;
    s32 *var_r27;
    s16 var_r26;
    s32 var_r25;
    s16 var_r23;
    s16 *var_r22;
    AnimData **var_r21;
    s16 var_r20;
    s16 var_r19;

    var_r27 = lbl_1_data_788;

    for (var_r23 = 0; var_r23 < 0x10; var_r23++) {
        if (arg0->unk_3A[var_r23] == -1) {
            break;
        }
    }
    if (var_r23 == 0x10) {
        return -1;
    }
    var_r21 = HuMemDirectMalloc(HEAP_SYSTEM, 0x190);
    var_r22 = HuMemDirectMalloc(HEAP_SYSTEM, 0xC8);
    var_r29 = HuMemDirectMalloc(HEAP_SYSTEM, 0xC8);

    for (var_r31 = arg1, var_r30 = 0, var_r28 = 0; var_r31[0] != 0; var_r31++) {
        if (var_r31[0] == 0x20 || var_r31[0] == 0x10) {
            var_r30 += 0xE;
        }
        else if (var_r31[0] < 0x30 || var_r31[0] == 0x80 || var_r31[0] == 0x81) {
            continue;
        }
        else {
            if (var_r31[1] == 0x80) {
                if ((var_r31[0] >= 0x96) && (var_r31[0] <= 0xA4)) {
                    var_r25 = var_r27[var_r31[0] + 0x6A];
                }
                else if ((var_r31[0] >= 0xAA) && (var_r31[0] <= 0xAE)) {
                    var_r25 = var_r27[var_r31[0] + 0x65];
                }
                else if ((var_r31[0] >= 0xD6) && (var_r31[0] <= 0xE4)) {
                    var_r25 = var_r27[var_r31[0] + 0x43];
                }
                else if ((var_r31[0] >= 0xEA) && (var_r31[0] <= 0xEE)) {
                    var_r25 = var_r27[var_r31[0] + 0x3E];
                }
            }
            else if (var_r31[1] == 0x81) {
                if ((var_r31[0] >= 0xAA) && (var_r31[0] <= 0xAE)) {
                    var_r25 = var_r27[var_r31[0] + 0x6A];
                }
                else if ((var_r31[0] >= 0xEA) && (var_r31[0] <= 0xEE)) {
                    var_r25 = var_r27[var_r31[0] + 0x43];
                }
            }
            else {
                var_r25 = var_r27[var_r31[0]];
            }
            var_r21[var_r28] = HuSprAnimReadFile(var_r25);
            var_r22[var_r28] = var_r30;
            if ((var_r31[0] >= 0x61) && (var_r31[0] <= 0x7A)) {
                var_r29[var_r28] = 2;
                var_r30 += 0x12;
            }
            else if ((var_r31[0] == 0xC2) || (var_r31[0] == 0xC3)) {
                var_r29[var_r28] = 0;
                var_r30 += 0x12;
            }
            else if (var_r31[0] == 0x5C) {
                var_r29[var_r28] = 0;
                var_r30 += 8;
            }
            else if ((var_r31[0] >= 0x87) && (var_r31[0] <= 0x8F)) {
                var_r29[var_r28] = 4;
                var_r30 += 0x18;
            }
            else if ((var_r31[0] >= 0xC7) && (var_r31[0] <= 0xCF)) {
                var_r29[var_r28] = 4;
                var_r30 += 0x18;
            }
            else if ((var_r31[0] == 0x3D) || (var_r31[0] == 0x84)) {
                var_r29[var_r28] = 0;
                var_r30 += 0x14;
            }
            else {
                var_r29[var_r28] = 0;
                var_r30 += 0x1C;
            }
            var_r28++;
        }
    }
    var_r20 = HuSprGrpCreate(var_r28);
    arg0->unk_3A[var_r23] = var_r20;
    arg0->unk_30 = var_r30;
    var_r30 = (var_r30 / 2) - 0xE;
    for (var_r26 = 0; var_r26 < var_r28; var_r26++) {
        var_r19 = HuSprCreate(var_r21[var_r26], 0, 0);
        HuSprGrpMemberSet(var_r20, var_r26, var_r19);
        HuSprPosSet(var_r20, var_r26, var_r22[var_r26] - var_r30, var_r29[var_r26]);
    }

    arg0->unk_32 = var_r28;
    HuMemDirectFree(var_r21);
    HuMemDirectFree(var_r22);
    HuMemDirectFree(var_r29);
    return var_r20;
}

s32 fn_1_1D02C(u32 arg0)
{
    MpexDllUnkStruct3 sp10;
    s16 spC[2];

    u8 *var_r31;
    s32 var_r30;
    s16 var_r29;
    u8 *var_r28;
    s32 var_r27;
    s32 var_r26;
    s16 var_r25;

    var_r25 = GWGameStat.language;
    lbl_1_bss_6AC = var_r25;
    for (var_r30 = 0; var_r30 < 0x10; var_r30++) {
        sp10.unk_5A[var_r30] = sp10.unk_3A[var_r30] = -1;
    }
    var_r28 = MessData_MesPtrGet(messDataPtr, arg0);
    var_r31 = var_r28;
    var_r30 = 0;
    var_r29 = 0;

    while (TRUE) {
        if (var_r31[0] == 0 || var_r31[0] == 0xA) {
            if (var_r31[0] == 0) {
                var_r30 = 1;
            }
            var_r31[0] = 0;
            if (lbl_1_bss_6AC == 0) {
                var_r27 = 1;
            }
            else {
                var_r27 = 0;
            }
            var_r26 = fn_1_1CB80(&sp10, var_r28, var_r27);
            HuSprGrpPosSet(sp10.unk_3A[var_r29], 288.0f, 240.0f);
            spC[var_r29] = sp10.unk_30;
            var_r29++;
            if (var_r30 == 0) {
                var_r28 = var_r31 + 1;
            }
            else {
                break;
            }
        }
        var_r31++;
    }
    return var_r26;
}
