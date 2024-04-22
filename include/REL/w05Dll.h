#include "dolphin/types.h"

#include "game/board/main.h"
#include "game/board/map_object.h"

// functions
void BoardCreate(void);
void BoardDestroy(void);
void fn_1_744(void);
void fn_1_788(void);
s32 fn_1_78C(void);
s32 fn_1_82C(void);
void fn_1_92C(void);
void fn_1_950(void);
void fn_1_954(void);
void fn_1_D4C(void);
void fn_1_D84(void);
void fn_1_E04(void);
void fn_1_E40(void);
s32 fn_1_1114(void);
s32 fn_1_1208(s16, f32, f32);

void fn_1_13D4(void);
void fn_1_14D0(void);
s16 fn_1_14FC(void);
void fn_1_155C(void);
void fn_1_1E44(void);

void fn_1_2B40(void);
void fn_1_2C7C(s32);
void fn_1_3044(void);
void fn_1_3430(void);
void fn_1_3514(void);
void fn_1_3D88(void);
void fn_1_3E8C(void);

void fn_1_3F74(void);
void fn_1_3FD8(void);
void fn_1_4034(s32);
void fn_1_4EB4(s32, s32, Vec*);
void fn_1_5648(void);
void fn_1_5794(s32, s32, Vec*);
void fn_1_6670(void);
omObjData* fn_1_66C0(u32, Vec*);
void fn_1_6914(omObjData*);
void fn_1_62AC(s32, Vec*);
void fn_1_64BC(void);
void fn_1_65E8(void);
void fn_1_6670(void);
omObjData* fn_1_66C0(u32, Vec*);
void fn_1_6914(omObjData*);

// unknown
void fn_1_62AC(s32, Vec*);
void fn_1_64BC();
void fn_1_65E8();
void fn_1_6670();
omObjData* fn_1_66C0(u32, Vec*);
void fn_1_6914(omObjData*);

// structs
typedef struct bitcopy {
    u32 unk_00;
    s8 unk_04;
} bitcopy;

// data
extern BoardMapObject lbl_1_data_0[7];
extern s16 lbl_1_data_118;
extern s16 lbl_1_data_11A;
extern s16 lbl_1_data_11C;
extern s16 lbl_1_data_11E;
extern s16 lbl_1_data_120;
extern s32 lbl_1_data_124[8];
extern s32 lbl_1_data_144[2];
extern s32 lbl_1_data_14C;

extern s32 lbl_1_data_150[5];
extern s16 lbl_1_data_164;
extern u32 lbl_1_data_170[4];
extern s32 lbl_1_data_180;
extern s16 lbl_1_data_184;
extern s32 lbl_1_data_188[4];
extern s32 lbl_1_data_198[2];

extern s32 lbl_1_data_1A8[3];
extern char *lbl_1_data_1C4[2];
extern s32 lbl_1_data_1CC[3];

extern char *lbl_1_data_22C[6];
extern s32 lbl_1_data_244[6];
extern Vec lbl_1_data_25C[6];
extern Vec lbl_1_data_2A4[6];
extern s32 lbl_1_data_2EC[2];
extern s32 lbl_1_data_2F4[6];

// bss
extern s16 lbl_1_bss_72[2];
extern s16 lbl_1_bss_6C[3];
extern s32 lbl_1_bss_68;
extern s16 lbl_1_bss_64;
extern s16 lbl_1_bss_58[6];

extern s16 lbl_1_bss_4E[2];
extern s16 lbl_1_bss_4C;
extern s16 lbl_1_bss_4A;
extern s16 lbl_1_bss_48;
extern s16 lbl_1_bss_44[2];
extern Vec lbl_1_bss_38;
extern s16 lbl_1_bss_30[4];

extern s16 lbl_1_bss_28;

extern s16 lbl_1_bss_14[7];
extern s32* lbl_1_bss_10;
extern s16 lbl_1_bss_8[4];
extern Process* lbl_1_bss_4;
extern bitcopy* lbl_1_bss_0;
