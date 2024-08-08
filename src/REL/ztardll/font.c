#include "game/sprite.h"

#include "REL/ztardll.h"

s32 lbl_1_data_B0[0xC6] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0x150000, 0x150001, 0x150002, 0x150003, 0x150004, 0x150005, 0x150006, 0x150007, 0x150008, 0x150009, 0x150000, 0x150000,
    0x150000, 0x15000A, 0x150000, 0x150000, 0x150000, 0x15000F, 0x150010, 0x150011, 0x150012, 0x150013, 0x150014, 0x150015, 0x150016, 0x150017,
    0x150018, 0x150019, 0x15001A, 0x15001B, 0x15001C, 0x15001D, 0x15001E, 0x15001F, 0x150020, 0x150021, 0x150022, 0x150023, 0x150024, 0x150025,
    0x150026, 0x150027, 0x150028, 0x15001D, 0x15000D, 0x15001D, 0x15001D, 0x15001D, 0x15001D, 0x150029, 0x15002A, 0x15002B, 0x15002C, 0x15002D,
    0x15002E, 0x15002F, 0x150030, 0x150031, 0x150032, 0x150033, 0x150034, 0x150035, 0x150036, 0x150037, 0x150038, 0x150039, 0x15003A, 0x15003B,
    0x15003C, 0x15003D, 0x15003E, 0x15003F, 0x150040, 0x150041, 0x150042, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000,
    0x150000, 0x150000, 0x15000A, 0x15000E, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000,
    0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000,
    0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000,
    0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000,
    0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x150000, 0x15000B, 0x15000C, 0x150000, 0x150000 };

s32 fn_1_7754(ZtarDllUnkStruct *arg0, u8 *arg1)
{
    u8 *var_r31;
    s16 var_r30;
    s16 *var_r29;
    s16 var_r28;
    s32 *var_r27;
    s16 var_r26;
    s16 var_r25;
    s32 var_r24;
    s16 *var_r22;
    AnimData **var_r21;
    s16 var_r20;
    s16 var_r19;

    var_r27 = lbl_1_data_B0;
    for (var_r25 = 0; var_r25 < 0x10; var_r25++) {
        if (arg0->unk_3A[var_r25] == -1) {
            break;
        }
    }
    if (var_r25 == 0x10) {
        return -1;
    }
    var_r21 = HuMemDirectMalloc(HEAP_SYSTEM, 0x190);
    var_r22 = HuMemDirectMalloc(HEAP_SYSTEM, 0xC8);
    var_r29 = HuMemDirectMalloc(HEAP_SYSTEM, 0xC8);
    for (var_r31 = arg1, var_r30 = 0, var_r28 = 0; var_r31[0] != 0; var_r31++) {
        if (var_r31[0] == 0x20 || var_r31[0] == 0x10) {
            var_r30 += 0xE;
        }
        else if (var_r31[0] < 0x30) {
        }
        else if (var_r31[0] == 0x80) {
        }
        else if (var_r31[0] == 0x81) {
        }
        else {
            if (var_r31[1] == 0x80) {
                if ((var_r31[0] >= 0x96) && (var_r31[0] <= 0xA4)) {
                    var_r24 = var_r27[var_r31[0] + 0x6A];
                }
                else if ((var_r31[0] >= 0xAA) && (var_r31[0] <= 0xAE)) {
                    var_r24 = var_r27[var_r31[0] + 0x65];
                }
                else if ((var_r31[0] >= 0xD6) && (var_r31[0] <= 0xE4)) {
                    var_r24 = var_r27[var_r31[0] + 0x43];
                }
                else if ((var_r31[0] >= 0xEA) && (var_r31[0] <= 0xEE)) {
                    var_r24 = var_r27[var_r31[0] + 0x3E];
                }
            }
            else if (var_r31[1] == 0x81) {
                if ((var_r31[0] >= 0xAA) && (var_r31[0] <= 0xAE)) {
                    var_r24 = var_r27[var_r31[0] + 0x6A];
                }
                else if ((var_r31[0] >= 0xEA) && (var_r31[0] <= 0xEE)) {
                    var_r24 = var_r27[var_r31[0] + 0x43];
                }
            }
            else {
                var_r24 = var_r27[var_r31[0]];
            }
            var_r21[var_r28] = HuSprAnimReadFile(var_r24);
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
    arg0->unk_3A[var_r25] = var_r20;
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
    return var_r25;
}
