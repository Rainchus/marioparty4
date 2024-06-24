#include "REL/m440Dll.h"

// bss
omObjData* lbl_1_bss_C0[4];

// data

// prototypes
void fn_1_AEE4(omObjData*);
void fn_1_B180(omObjData*);

void fn_1_AE08(Process* arg0) {
    s16 var_r31;

    omMakeGroupEx(arg0, 0, 4);
    omGetGroupMemberListEx(arg0, 0);
    
loop_2:
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_C0[var_r31] = omAddObjEx(arg0, 0x64, 9, 8, 0, fn_1_AEE4);
        lbl_1_bss_C0[var_r31]->work[0] = var_r31;
    }
    omAddObjEx(arg0, 0x65, 0, 0, -1, fn_1_B180);
}
