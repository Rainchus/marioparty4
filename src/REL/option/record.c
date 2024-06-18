#include "REL/option.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/window.h"

#include "dolphin.h"
#include "math.h"

#define RECORD_TYPE_BOARD 0
#define RECORD_TYPE_MG 1

#define NUM_CHARACTERS 8
#define NUM_BOARDS 6

#define PLAY_COUNT_NUM_DIGITS 4
#define WIN_COUNT_NUM_DIGITS 3
#define MAX_COINS_NUM_DIGITS 4
#define MAX_STARS_NUM_DIGITS 4
#define MG_DECIMAL_NUM_DIGITS 8
#define MG_TIME_NUM_DIGITS 8

#define DISPLAY_TYPE_TIME 0
#define DISPLAY_TYPE_DECIMAL 1

typedef struct {
    /* 0x00 */ s32 playCount;
    /* 0x04 */ s32 winCounts[8];
    /* 0x24 */ s32 maxCoins;
    /* 0x28 */ s32 maxStars;
} BoardRecordData; // Size 0x2C

typedef struct {
    /* 0x000 */ omObjData *system;
    /* 0x004 */ omObjData *hand;
    /* 0x008 */ WindowWork *window[10];
    /* 0x030 */ s32 mode;
    /* 0x034 */ s16 sprList[153];
    /* 0x166 */ char unk166[6];
    /* 0x16C */ s32 recordType;
    /* 0x170 */ s32 board;
    /* 0x174 */ s32 mgPage;
    /* 0x178 */ BoardRecordData boardRecords[6];
    /* 0x280 */ s32 mgRecords[6];
    /* 0x298 */ s32 cameraDoneF;
    /* 0x29C */ s32 changeTimer;
} RecordWork; // Size 0x2A0

typedef struct {
    /* 0x00 */ s32 id;
    /* 0x04 */ s32 mess;
    /* 0x08 */ s32 displayType;
} MGTable; // Size 0x0C

#define MODE_DISABLED 0
#define MODE_HANDLE_RECORD 1

static void HandleRecord(omObjData *object);
static omObjData *CreateSystem(void);
static void KillSystem(omObjData *system);
static void StartSystemMotion(omObjData *system, s32 type);
static omObjData *CreateHand(void);
static void KillHand(omObjData *hand);
static void CreateSpr(omObjData *object);
static void KillSpr(omObjData *object);
static s32 GetDigitSprAt(s32 n, s32 offsetFromRight);
static void DisplayBoardRecord(omObjData *object, s32 board);
static void HideBoardRecordSpr(omObjData *object);
static void DisplayTotalResults(omObjData *object);
static void HideTotalResultsSpr(omObjData *object);
static void ShowMGRecord(omObjData *object, s32 page);
static void HideMGRecordSpr(omObjData *object);

omObjData *lbl_1_bss_40;

static const s32 mgRecordIdxTbl[] = { 0, 1, 2, 3, 5, 10 };

static omObjFunc modes[] = { NULL, HandleRecord };

omObjData *fn_1_80E4(void)
{
    omObjData *object;
    RecordWork *work;
    s32 i;
    s32 character;

    object = omAddObjEx(lbl_1_bss_8, 1003, 0, 0, 1, NULL);
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(RecordWork), MEMORY_DEFAULT_NUM);
    object->data = work;
    for (i = 0; i < NUM_BOARDS; i++) {
        work->boardRecords[i].playCount = GWBoardPlayCountGet(i);
        work->boardRecords[i].maxStars = GWBoardMaxStarsGet(i);
        work->boardRecords[i].maxCoins = GWBoardMaxCoinsGet(i);
        for (character = 0; character < NUM_CHARACTERS; character++) {
            work->boardRecords[i].winCounts[character] = GWBoardWinCountGet(character, i);
        }
    }
    for (i = 0; i < 6; i++) {
        work->mgRecords[i] = GWMGRecordGet(mgRecordIdxTbl[i]);
    }
    work->board = 0;
    work->mgPage = 0;
    work->recordType = RECORD_TYPE_BOARD;
    work->system = CreateSystem();
    work->hand = CreateHand();
    CreateSpr(object);
    fn_1_82B0(object, MODE_DISABLED);
    return object;
}

void fn_1_825C(omObjData *object)
{
    RecordWork *work = object->data;

    KillSystem(work->system);
    KillHand(work->hand);
    KillSpr(object);
    HuMemDirectFree(work);
}

void fn_1_82B0(omObjData *object, s32 mode)
{
    RecordWork *work = object->data;

    work->mode = mode;
    object->func = modes[mode];
    object->unk10 = 0;
    object->unk10 = 0;
}

s32 fn_1_82F4(omObjData *object)
{
    RecordWork *work = object->data;

    return work->mode;
}

static void HandleRecord(omObjData *object)
{
    RecordWork *work = object->data;
    Vec sp8;
    s32 i;

    switch (object->unk10) {
        case 0:
            work->window[0] = fn_1_A44C(0);
            work->window[1] = fn_1_A44C(1);
            for (i = 0; i < 8; i++) {
                work->window[i + 2] = fn_1_A44C(3);
            }
            fn_1_AF0(lbl_1_bss_10, 519.0f, 125.0f, 300.0f, 0x28);
            fn_1_A6C(lbl_1_bss_10, 308.98f, 125.0f, 178.74f, 0x28);
            work->board = 0;
            work->mgPage = 0;
            work->cameraDoneF = 0;
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            if (fn_1_CB8(lbl_1_bss_10) != 0) {
                break;
            }
            fn_1_3D54(lbl_1_bss_30);
            espBankSet(work->sprList[47], 0);
            espBankSet(work->sprList[48], 2);
            espPosSet(work->sprList[47], 46.0f, 240.0f);
            espPosSet(work->sprList[48], 494.0f, 240.0f);
            if (work->recordType == RECORD_TYPE_BOARD) {
                fn_1_160(work->sprList[47], 1, 10);
                fn_1_160(work->sprList[48], 1, 10);
                work->changeTimer = 0;
            }
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            HideBoardRecordSpr(object);
            HideMGRecordSpr(object);
            HideTotalResultsSpr(object);
            switch (work->recordType) {
                case RECORD_TYPE_BOARD:
                    if (work->board < 6) {
                        DisplayBoardRecord(object, work->board);
                    }
                    else {
                        DisplayTotalResults(object);
                    }
                    fn_1_A6EC(work->window[0]);
                    fn_1_A71C(work->window[0], MAKE_MESSID(47, 5));
                    break;
                case RECORD_TYPE_MG:
                    ShowMGRecord(object, work->mgPage);
                    fn_1_A6EC(work->window[0]);
                    fn_1_A71C(work->window[0], MAKE_MESSID(47, 6));
                    break;
            }
            fn_1_A6EC(work->window[1]);
            fn_1_A71C(work->window[1], MAKE_MESSID(47, 169));
            if (!work->cameraDoneF) {
                Hu3DModelAttrReset(work->hand->model[0], 1);
                work->cameraDoneF = TRUE;
            }
            sp8.x = 505.0 * -sin(305 * M_PI / 180.0);
            sp8.z = 505.0 * cos(305 * M_PI / 180.0);
            sp8.y = 144.0f - 14.0f * work->recordType;
            omSetTra(work->hand, sp8.x, sp8.y, sp8.z);
            object->unk10 = 3;
            /* fallthrough */
        case 3:
            if (work->changeTimer > 0) {
                work->changeTimer--;
                break;
            }
            espBankSet(work->sprList[47], 0);
            espBankSet(work->sprList[48], 2);
            object->unk10 = 4;
            /* fallthrough */
        case 4:
            if (work->window[1]->state != 0) {
                break;
            }
            if (fn_1_550(PAD_BUTTON_B)) {
                HuAudFXPlay(3);
                object->unk10 = 5;
            }
            else if (fn_1_584(8) != 0 && work->recordType == RECORD_TYPE_MG) {
                work->recordType = RECORD_TYPE_BOARD;
                work->board = 0;
                StartSystemMotion(work->system, work->recordType);
                fn_1_160(work->sprList[47], 1, 5);
                fn_1_160(work->sprList[48], 1, 5);
                work->changeTimer = 5;
                HuAudFXPlay(0x83F);
                object->unk10 = 2;
            }
            else if (fn_1_584(4) != 0 && work->recordType == RECORD_TYPE_BOARD) {
                work->recordType = RECORD_TYPE_MG;
                work->mgPage = 0;
                StartSystemMotion(work->system, work->recordType);
                fn_1_160(work->sprList[47], 0, 5);
                fn_1_160(work->sprList[48], 0, 5);
                work->changeTimer = 5;
                HuAudFXPlay(0x83F);
                object->unk10 = 2;
            }
            else {
                switch (work->recordType) {
                    case RECORD_TYPE_BOARD:
                        if (fn_1_550(PAD_TRIGGER_L)) {
                            if (--work->board < 0) {
                                work->board = 6;
                            }
                            if (GWGameStat.open_w06 == 0 && work->board == 5) {
                                work->board--;
                            }
                            HuAudFXPlay(0x840);
                            espBankSet(work->sprList[47], 1);
                            work->changeTimer = 10;
                            object->unk10 = 2;
                            return;
                        }
                        if (fn_1_550(PAD_TRIGGER_R)) {
                            if (++work->board >= 7) {
                                work->board = 0;
                            }
                            if (GWGameStat.open_w06 == 0 && work->board == 5) {
                                work->board++;
                            }
                            HuAudFXPlay(0x840);
                            espBankSet(work->sprList[48], 3);
                            work->changeTimer = 10;
                            object->unk10 = 2;
                        }
                        break;
                    case RECORD_TYPE_MG:
                        break;
                }
            }
            break;
        case 5:
            fn_1_3E1C(lbl_1_bss_30);
            if (work->recordType == RECORD_TYPE_BOARD) {
                fn_1_160(work->sprList[47], 0, 10);
                fn_1_160(work->sprList[48], 0, 10);
            }
            fn_1_A704(work->window[0]);
            fn_1_A704(work->window[1]);
            Hu3DModelAttrSet(work->hand->model[0], 1);
            object->unk10 = 6;
            /* fallthrough */
        case 6:
            if (work->window[1]->state == 0 && fn_1_3ED0(lbl_1_bss_30) == 0) {
                for (i = 0; i < 10; i++) {
                    fn_1_A6AC(work->window[i]);
                }
                HideBoardRecordSpr(object);
                HideMGRecordSpr(object);
                HideTotalResultsSpr(object);
                fn_1_AF0(lbl_1_bss_10, 519.62f, 120.0f, 300.0f, 40);
                fn_1_A6C(lbl_1_bss_10, 0.0f, 120.0f, 0.0f, 0x28);
                fn_1_82B0(object, MODE_DISABLED);
            }
            break;
    }
}

static omObjData *CreateSystem(void)
{
    omObjData *system;

    system = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    system->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 1));
    Hu3DModelAttrSet(system->model[0], 0x40000002);
    Hu3DModelLayerSet(system->model[0], 0);
    Hu3DMotionStartEndSet(system->model[0], 0.0f, 6.0f);
    Hu3DMotionTimeSet(system->model[0], 6.0f);
    return system;
}

static void KillSystem(omObjData *system)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(system->model[i]);
    }
}

static void StartSystemMotion(omObjData *system, s32 type)
{
    s16 model = system->model[0];

    switch (type) {
        case RECORD_TYPE_BOARD:
            Hu3DMotionStartEndSet(model, 0.0f, 6.0f);
            Hu3DMotionTimeSet(model, 0.0f);
            break;
        case RECORD_TYPE_MG:
            Hu3DMotionStartEndSet(model, 6.0f, 12.0f);
            Hu3DMotionTimeSet(model, 6.0f);
            break;
    }
    Hu3DModelAttrReset(system->model[0], 0x40000002);
}

static omObjData *CreateHand(void)
{
    omObjData *hand;

    hand = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    hand->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 14));
    Hu3DModelLayerSet(hand->model[0], 2);
    Hu3DModelAttrSet(hand->model[0], 0x40000001);
    omSetRot(hand, 30.0f, 190.0f, 0.0f);
    omSetSca(hand, 0.6f, 0.6f, 0.6f);
    Hu3DModelAttrSet(hand->model[0], 1);
    return hand;
}

static void KillHand(omObjData *hand)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(hand->model[i]);
    }
}

#define SPR_TBL_SIZE 153

static const s32 sprTbl[SPR_TBL_SIZE] = {
    DATA_MAKE_NUM(DATADIR_OPTION, 55),
    DATA_MAKE_NUM(DATADIR_OPTION, 56),
    DATA_MAKE_NUM(DATADIR_OPTION, 57),
    DATA_MAKE_NUM(DATADIR_OPTION, 58),
    DATA_MAKE_NUM(DATADIR_OPTION, 59),
    DATA_MAKE_NUM(DATADIR_OPTION, 60),
    DATA_MAKE_NUM(DATADIR_OPTION, 61),
    DATA_MAKE_NUM(DATADIR_OPTION, 62),
    DATA_MAKE_NUM(DATADIR_OPTION, 50),
    DATA_MAKE_NUM(DATADIR_OPTION, 51),
    DATA_MAKE_NUM(DATADIR_OPTION, 66),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 49),
    DATA_MAKE_NUM(DATADIR_OPTION, 49),
    DATA_MAKE_NUM(DATADIR_OPTION, 19),
    DATA_MAKE_NUM(DATADIR_OPTION, 20),
    DATA_MAKE_NUM(DATADIR_OPTION, 21),
    DATA_MAKE_NUM(DATADIR_OPTION, 22),
    DATA_MAKE_NUM(DATADIR_OPTION, 23),
    DATA_MAKE_NUM(DATADIR_OPTION, 24),
    DATA_MAKE_NUM(DATADIR_OPTION, 25),
    DATA_MAKE_NUM(DATADIR_OPTION, 26),
    DATA_MAKE_NUM(DATADIR_OPTION, 27),
    DATA_MAKE_NUM(DATADIR_OPTION, 28),
    DATA_MAKE_NUM(DATADIR_OPTION, 29),
    DATA_MAKE_NUM(DATADIR_OPTION, 30),
    DATA_MAKE_NUM(DATADIR_OPTION, 31),
    DATA_MAKE_NUM(DATADIR_OPTION, 32),
    DATA_MAKE_NUM(DATADIR_OPTION, 33),
    DATA_MAKE_NUM(DATADIR_OPTION, 34),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
};

static void CreateSpr(omObjData *object)
{
    RecordWork *work = object->data;
    s32 i;

    for (i = 0; i < SPR_TBL_SIZE; i++) {
        work->sprList[i] = espEntry(sprTbl[i], 0, 0);
        espDrawNoSet(work->sprList[i], 0x40);
        espDispOff(work->sprList[i]);
    }
    espBankSet(work->sprList[47], 0);
    espBankSet(work->sprList[48], 2);
    HuSprExecLayerSet(0x40, 1);
}

static void KillSpr(omObjData *object)
{
    RecordWork *work = object->data;
    s32 i;

    for (i = 0; i < SPR_TBL_SIZE; i++) {
        espKill(work->sprList[i]);
    }
}

static s32 GetDigitSprAt(s32 n, s32 offsetFromRight)
{
    s32 i;

    i = 1;
    while (offsetFromRight-- != 0) {
        i *= 10;
    }
    return (n % (i * 10)) / i;
}

static void DisplayBoardRecord(omObjData *object, s32 board)
{
    RecordWork *work = object->data;
    s32 value;
    s32 i;
    s32 j;

    espPosSet(work->sprList[board], 275.0f, 72.0f);
    value = work->boardRecords[work->board].playCount;
    for (i = 0; i < PLAY_COUNT_NUM_DIGITS; i++) {
        espPosSet(work->sprList[i + 11], 323.0f + 20.0f * i, 116.0f);
        if (value > 999) {
            espBankSet(work->sprList[i + 11], i + 10);
        }
        else {
            espBankSet(work->sprList[i + 11], GetDigitSprAt(value, 3 - i));
        }
    }
    espPosSet(work->sprList[8], 416.0f, 120.0f);
    value = work->boardRecords[work->board].maxCoins;
    for (i = 0; i < MAX_COINS_NUM_DIGITS; i++) {
        espPosSet(work->sprList[i + 15], 364.0f + 20.0f * i, 268.0f);
        if (value > 999) {
            espBankSet(work->sprList[i + 15], i + 10);
        }
        else {
            espBankSet(work->sprList[i + 15], GetDigitSprAt(value, 3 - i));
        }
    }
    espPosSet(work->sprList[9], 456.0f, 268.0f);
    value = work->boardRecords[work->board].maxStars;
    for (i = 0; i < MAX_STARS_NUM_DIGITS; i++) {
        espPosSet(work->sprList[i + 19], 364.0f + 20.0f * i, 312.0f);
        if (value > 999) {
            espBankSet(work->sprList[i + 19], i + 10);
        }
        else {
            espBankSet(work->sprList[i + 19], GetDigitSprAt(value, 3 - i));
        }
    }
    espPosSet(work->sprList[10], 456.0f, 312.0f);
    for (i = 0; i < NUM_CHARACTERS; i++) {
        espPosSet(work->sprList[i + 49], 92.0f + 50.0f * i, 200.0f);
        for (j = 0; j < WIN_COUNT_NUM_DIGITS; j++) {
            espPosSet(work->sprList[i * 3 + 23 + j], 80.0f + 50.0f * i + 12.0f * j, 230.0f);
            espBankSet(work->sprList[i * 3 + 23 + j], GetDigitSprAt(work->boardRecords[work->board].winCounts[i], 2 - j));
        }
    }
    espPosSet(work->sprList[47], 48.0f, 240.0f);
    espPosSet(work->sprList[48], 492.0f, 240.0f);
    espDispOn(work->sprList[board]);
    for (i = 0; i < PLAY_COUNT_NUM_DIGITS; i++) {
        espDispOn(work->sprList[i + 11]);
    }
    espDispOn(work->sprList[8]);
    for (i = 0; i < MAX_COINS_NUM_DIGITS; i++) {
        espDispOn(work->sprList[i + 15]);
    }
    espDispOn(work->sprList[9]);
    for (i = 0; i < MAX_STARS_NUM_DIGITS; i++) {
        espDispOn(work->sprList[i + 19]);
    }
    espDispOn(work->sprList[10]);
    for (i = 0; i < NUM_CHARACTERS; i++) {
        espDispOn(work->sprList[i + 49]);
        for (j = 0; j < WIN_COUNT_NUM_DIGITS; j++) {
            espDispOn(work->sprList[i * 3 + 23 + j]);
        }
    }
    for (i = 0; i < 4; i++) {
        fn_1_A7F0(work->window[i + 2]);
    }
    fn_1_A7B0(work->window[2], 64.0f, 96.0f);
    fn_1_A71C(work->window[2], MAKE_MESSID(47, 19));
    fn_1_A7B0(work->window[3], 64.0f, 140.0f);
    fn_1_A71C(work->window[3], MAKE_MESSID(47, 20));
    fn_1_A7B0(work->window[4], 64.0f, 248.0f);
    fn_1_A71C(work->window[4], MAKE_MESSID(47, 21));
    fn_1_A7B0(work->window[5], 64.0f, 292.0f);
    fn_1_A71C(work->window[5], MAKE_MESSID(47, 22));
}

#define BOARD_RECORD_SPR_IDX_TBL_SIZE 53

static const s32 boardRecordSprIdxTbl[BOARD_RECORD_SPR_IDX_TBL_SIZE] = { 0, 1, 2, 3, 4, 5, 49, 50, 51, 52, 53, 54, 55, 56, 8, 9, 10, 11, 12, 13, 14,
    23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 38, 39, 40, 35, 36, 37, 41, 42, 43, 44, 45, 46, 15, 16, 17, 18, 19, 20, 21, 22 };

static void HideBoardRecordSpr(omObjData *object)
{
    RecordWork *work = object->data;
    s32 i;

    for (i = 0; i < BOARD_RECORD_SPR_IDX_TBL_SIZE; i++) {
        espDispOff(work->sprList[boardRecordSprIdxTbl[i]]);
    }
    for (i = 0; i < 4; i++) {
        fn_1_A828(work->window[i + 2]);
    }
}

static void DisplayTotalResults(omObjData *object)
{
    RecordWork *work = object->data;
    s32 winCount;
    s32 i;
    s32 j;

    espPosSet(work->sprList[6], 275.0f, 72.0f);
    for (i = 0; i < NUM_CHARACTERS; i++) {
        espPosSet(work->sprList[i + 57], 148.0f + 80.0f * (i % 4), 172.0f + 104.0f * (i / 4));
        for (j = 0, winCount = 0; j < NUM_BOARDS; j++) {
            winCount += work->boardRecords[j].winCounts[i];
        }
        for (j = 0; j < WIN_COUNT_NUM_DIGITS; j++) {
            espPosSet(work->sprList[i * 3 + 65 + j], 132.0f + 80.0f * (i % 4) + 16.0f * j, 218.0f + 104.0f * (i / 4));
            espBankSet(work->sprList[i * 3 + 65 + j], GetDigitSprAt(winCount, 2 - j));
        }
    }
    espDispOn(work->sprList[6]);
    for (i = 0; i < NUM_CHARACTERS; i++) {
        espDispOn(work->sprList[i + 57]);
        for (j = 0; j < 3; j++) {
            espDispOn(work->sprList[i * 3 + 65 + j]);
        }
    }
    fn_1_A7B0(work->window[2], 136.0f, 96.0f);
    fn_1_A71C(work->window[2], MAKE_MESSID(47, 23));
    fn_1_A7F0(work->window[2]);
}

#define TOTAL_RESULTS_SPR_IDX_TBL_SIZE 33

static const s32 totalResultsSprIdxTbl[TOTAL_RESULTS_SPR_IDX_TBL_SIZE]
    = { 6, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88 };

static void HideTotalResultsSpr(omObjData *object)
{
    RecordWork *work = object->data;
    s32 i;

    for (i = 0; i < TOTAL_RESULTS_SPR_IDX_TBL_SIZE; i++) {
        espDispOff(work->sprList[totalResultsSprIdxTbl[i]]);
    }
    fn_1_A828(work->window[2]);
}

static const MGTable mgTbl[6] = {
    { 405, MAKE_MESSID(23, 5), DISPLAY_TYPE_TIME },
    { 407, MAKE_MESSID(23, 7), DISPLAY_TYPE_DECIMAL },
    { 427, MAKE_MESSID(23, 27), DISPLAY_TYPE_TIME },
    { 432, MAKE_MESSID(23, 32), DISPLAY_TYPE_TIME },
    { 443, MAKE_MESSID(23, 43), DISPLAY_TYPE_TIME },
    { 456, MAKE_MESSID(23, 54), DISPLAY_TYPE_TIME },
};

static void ShowMGRecord(omObjData *object, s32 page)
{
    RecordWork *work = object->data;
    s32 value;
    s32 mg;
    s32 digit;
    s32 var_r26;
    s32 var_r17;
    s32 sp5C;
    s32 sp58;
    s32 mgAvail;
    BOOL digitDrawnF;
    s32 nameMess;
    s32 i;
    s32 j;

    espPosSet(work->sprList[7], 275.0f, 72.0f);
    espPosSet(work->sprList[47], 48.0f, 240.0f);
    espPosSet(work->sprList[48], 492.0f, 240.0f);
    espDispOn(work->sprList[7]);
    for (i = 0; i < 8; i++) {
        digitDrawnF = FALSE;
        mg = i + page * 8;
        if (mg >= 6) {
            break;
        }
        mgAvail = GWMGAvailGet(mgTbl[mg].id);
        value = work->mgRecords[mg];
        if (mgAvail) {
            switch (mgTbl[mg].displayType) {
                case DISPLAY_TYPE_DECIMAL:
                    for (j = 0; j < MG_DECIMAL_NUM_DIGITS; j++) {
                        var_r17 = GetDigitSprAt(value, 7 - j);
                        if (var_r17 != 0 || digitDrawnF || j >= 7) {
                            espPosSet(work->sprList[i * 8 + 89 + j], 336.0f + 16.0f * j, 116.0f + 40.0f * i);
                            espBankSet(work->sprList[i * 8 + 89 + j], var_r17);
                            espDispOn(work->sprList[i * 8 + 89 + j]);
                            digitDrawnF = TRUE;
                        }
                    }
                    break;
                case DISPLAY_TYPE_TIME:
                    sp5C = value / 3600;
                    sp58 = (value % 3600) / 60;
                    var_r26 = (value % 3600) % 60;
                    if (mgTbl[mg].id == 405 || mgTbl[mg].id == 432) {
                        var_r26 *= 1.6916667f;
                    }
                    else {
                        var_r26 *= 1.6666666f;
                    }
                    for (j = 1; j < MG_TIME_NUM_DIGITS; j++) {
                        espPosSet(work->sprList[i * 8 + 89 + j], 336.0f + 16.0f * j, 116.0f + 40.0f * i);
                        switch (j) {
                            case 0:
                                digit = GetDigitSprAt(sp5C, 1);
                                break;
                            case 1:
                                digit = GetDigitSprAt(sp5C, 0);
                                break;
                            case 3:
                                digit = GetDigitSprAt(sp58, 1);
                                break;
                            case 4:
                                digit = GetDigitSprAt(sp58, 0);
                                break;
                            case 6:
                                digit = GetDigitSprAt(var_r26, 1);
                                break;
                            case 7:
                                digit = GetDigitSprAt(var_r26, 0);
                                break;
                            case 2:
                                digit = 11;
                                break;
                            case 5:
                                digit = 12;
                                break;
                        }
                        espBankSet(work->sprList[i * 8 + 89 + j], digit);
                        espDispOn(work->sprList[i * 8 + 89 + j]);
                    }
                    break;
            }
        }
        else {
            for (j = 0; j < MG_DECIMAL_NUM_DIGITS; j++) {
                espPosSet(work->sprList[i * 8 + 89 + j], 336.0f + 16.0f * j, 116.0f + 40.0f * i);
                espBankSet(work->sprList[i * 8 + 89 + j], 0);
                espDispOn(work->sprList[i * 8 + 89 + j]);
            }
        }
        fn_1_A7B0(work->window[i + 2], 60.0f, 96.0f + 40.0f * i);
        nameMess = mgAvail ? mgTbl[mg].mess : MAKE_MESSID(35, 0);
        fn_1_A71C(work->window[i + 2], nameMess);
        fn_1_A7F0(work->window[i + 2]);
    }
}

#define MG_RECORD_SPR_IDX_TBL_SIZE 65

static const s32 mgRecordSprIdxTbl[65] = { 7, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140,
    141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152 };

static void HideMGRecordSpr(omObjData *object)
{
    RecordWork *temp_r30 = object->data;
    s32 i;

    for (i = 0; i < MG_RECORD_SPR_IDX_TBL_SIZE; i++) {
        espDispOff(temp_r30->sprList[mgRecordSprIdxTbl[i]]);
    }
    for (i = 0; i < 8; i++) {
        fn_1_A828(temp_r30->window[i + 2]);
    }
}
