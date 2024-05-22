#include "REL/m446Dll.h"

unkStruct3* lbl_1_bss_28;

s32 fn_1_3924(void);
void fn_1_393C(void);
// ...
void fn_1_3B4C(unkStruct4*);

s32 fn_1_3924(void) {
    lbl_1_bss_28 = NULL;
    return 1;
}

void fn_1_393C(void) {
    unkStruct3* var_r31;
    unkStruct4* var_r30;

    var_r31 = lbl_1_bss_28;
    if (var_r31) {
        do {
            var_r30 = var_r31->unk0;
            fn_1_3B4C(var_r30);
            var_r31 = var_r31->unk8;
        } while (var_r31);
    }
}

void fn_1_3994(void) {
    unkStruct4* sp8;
    unkStruct3* var_r31;

    var_r31 = lbl_1_bss_28;
    if (var_r31) {
        do {
            sp8 = var_r31->unk0;
            var_r31 = var_r31->unk8;
        } while (var_r31);
    }
}