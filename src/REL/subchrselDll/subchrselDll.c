#include "subchrselDll.h"

void fn_1_A0(void) {
    void* sp8 = omInitObjMan(0x32, 0x2000);
    Hu3DBGColorSet(0U, 0U, 0U);
    fn_8000C760(&fn_1_164, 0x1000, 0x3000, 0, fn_8000CA3C());
    fn_800414AC(1, 0, -1);
}

u16 fn_1_10C(void) {
    u16 var_r31;

    var_r31 = lbl_801D3AD0;
    if (lbl_1_bss_0 != lbl_801D3AAC) {
        var_r31 |= lbl_801D3AAC;
    }
    return var_r31;
}

// void fn_1_164(void)
