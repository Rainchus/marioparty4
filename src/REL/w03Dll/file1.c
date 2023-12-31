#include "common.h"
#include "dolphin.h"
#include "REL/executor.h"
#include "game/process.h"
#include "game/data.h"

//DATA file1
s16 lbl_1_data_280 = -1;
s16 lbl_1_data_282 = -1;
s16 lbl_1_data_284 = -1;
s16 lbl_1_data_286 = -1;
s32 lbl_1_data_288 = -1;

//char lbl_1_data_28C[] = "%d";

//shouldn't use MAKE_DATA_NUM
s32 lbl_1_data_290[] = {
    MAKE_DATA_NUM(0x005F, 0x0062),
    MAKE_DATA_NUM(0x001A, 0x0062),
    MAKE_DATA_NUM(0x006D, 0x0062),
    MAKE_DATA_NUM(0x008A, 0x0062),
    MAKE_DATA_NUM(0x0085, 0x0062),
    MAKE_DATA_NUM(0x0011, 0x0062),
    MAKE_DATA_NUM(0x000D, 0x0062),
    MAKE_DATA_NUM(0x0081, 0x0062),
};

//shouldn't use MAKE_DATA_NUM
s32 lbl_1_data_2B0[] = {
    MAKE_DATA_NUM(0x005F, 0x0033),
    MAKE_DATA_NUM(0x001A, 0x0033),
    MAKE_DATA_NUM(0x006D, 0x0033),
    MAKE_DATA_NUM(0x008A, 0x0033),
    MAKE_DATA_NUM(0x0085, 0x0033),
    MAKE_DATA_NUM(0x0011, 0x0033),
    MAKE_DATA_NUM(0x000D, 0x0033),
    MAKE_DATA_NUM(0x0081, 0x0033),
};

s32 lbl_1_data_2D0[] = {
    0x125, 0x165, 0x1A5, 0x1E5, 0x225, 0x265, 0x2A5, 0x2E5
};

s32 lbl_1_data_2F0[] = {
    0x12E, 0x16E, 0x1AE, 0x1EE, 0x22E, 0x26E, 0x2AE, 0x2EE
};

s16 lbl_1_data_310 = -1;
s16 lbl_1_data_312 = -1;
s16 lbl_1_data_314 = -1;
s16 lbl_1_data_316 = -1;


s32 lbl_1_data_318[] = {
    MAKE_DATA_NUM(0x0077, 0x0016),
    MAKE_DATA_NUM(0x0077, 0x0017),
    MAKE_DATA_NUM(0x0077, 0x0018),
    MAKE_DATA_NUM(0x0077, 0x0019),
    MAKE_DATA_NUM(0x0077, 0x001A),
    DATA_NUM_LISTEND
};

char lbl_1_data_330[] = "itemhook_oya";
char lbl_1_data_33D[] = "jyanA";
char lbl_1_data_343[] = "jyanB";

char* lbl_1_data_34C[] = {
    &lbl_1_data_33D, &lbl_1_data_343
};

char lbl_1_data_354[] = "coin";

char* lbl_1_data_35C[] = {
    &lbl_1_data_33D, &lbl_1_data_343
};