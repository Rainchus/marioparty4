#include "common.h"

void* MessData_MesPtrGet(s32* arg0, u32 arg1) {
    u16 var2;
    s32* var_r27;
    s32 var_r28;
    s32* temp_r31;
    s32* var_r26;
    s32* var_r25;
    u16* var_r29;
    s32 var1;
    u16 var_r24;
    s32* var_r30;
    s32 var_r21;

    var2 = arg1 >> 16;
    temp_r31 = arg0;
    var1 = *temp_r31++;
    var_r29 = (u16*)((u8*)arg0 + *temp_r31);
    
    var_r28 = var1;
    while (var_r28 != 0) {
        if (*var_r29 != var2) {
            var_r28--;
            var_r29 += 2;
            continue;
        } else {
            break;
        }
    }
    if (var_r28 == 0) {
        var_r26 = NULL;
    } else {
        temp_r31 = (s32*)((u32)temp_r31 + var_r29[1] * 4);
        var_r26 = (s32*)((u8*)arg0 + *temp_r31);
    }
    var_r27 = var_r26;
    if (var_r27 != 0) {
        var_r24 = arg1;
        var_r30 = var_r27;
        var_r21 = *var_r30;
        var_r30++;
        if (var_r21 <= var_r24) {
            var_r25 = NULL;
        } else {
            var_r30 = var_r30 + var_r24;
            var_r25 = (s32*)((u8*)var_r27 + *var_r30);
        }
        return var_r25;
    }
    return 0;
}
