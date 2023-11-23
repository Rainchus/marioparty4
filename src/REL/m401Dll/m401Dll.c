#include "common.h"
#include "REL/executor.h"

// global data
typedef struct unkStruct18FC10 {
    s16  unk_00;
    char unk_02[8];
} unkStruct18FC10;

void fn_800240EC(f32, f32, u8, u8, u8);
void fn_8002EF20(s16, s16);
void fn_80032F7C(void);
u8 fn_80041600(void);
void fn_8004D6F4(s16);
extern unkStruct18FC10 lbl_8018FC10[];

// local data
void fn_2_10710(void);
extern s16 lbl_2_data_4[8];


// fn_2_A0

// fn_2_70C

void fn_2_A10(void) {
    s32 i;

    if (fn_80041600() == 0) {
        fn_2_10710();
        for (i = 0; i < 4; i++) {
            fn_8004D6F4(lbl_2_data_4[lbl_8018FC10[i].unk_00]);
        }
        
        fn_80032F7C();
        fn_8002EF20(1, 1);
    }
}

void fn_2_A98(void) {
    fn_800240EC(174.0f, 271.0f, 0xA, 0x3C, 0xA0);
    Hu3DBGColorSet(0xAU, 0x3CU, 0xA0U);
}
