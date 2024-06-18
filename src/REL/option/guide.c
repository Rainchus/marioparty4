#include "REL/option.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"

#include "dolphin.h"
#include "ext_math.h"

typedef struct {
    /* 0x00 */ s32 mode;
    /* 0x04 */ s16 motionIdx;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ Vec pos;
    /* 0x14 */ Vec newPos;
    /* 0x20 */ Vec rot;
    /* 0x2C */ Vec posChange;
    /* 0x38 */ float distanceToMove;
    /* 0x3C */ float unkAngle;
    /* 0x40 */ float posToMoveTo;
    /* 0x44 */ float distFromCam;
    /* 0x48 */ char unk48[0xC];
    /* 0x54 */ float velocity;
    /* 0x58 */ float speed;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
} GuideWork; // Size 0x64

#define MODE_DISABLED 0
#define MODE_HANDLE_GUIDE 1

static void ChangeMode(omObjData *object, s32 mode);
static s32 GetMode(omObjData *object);
static void HandleGuide(omObjData *object);
static void UpdateGuide(omObjData *object);
static float fn_1_2D00(float arg0, float arg1, float arg2);

omObjData *lbl_1_bss_20;

static const s32 lbl_1_rodata_E0[] = {
    DATA_MAKE_NUM(DATADIR_OPTION, 16),
    DATA_MAKE_NUM(DATADIR_OPTION, 17),
    DATA_MAKE_NUM(DATADIR_OPTION, 18),
};

static omObjFunc modes[] = { NULL, HandleGuide };

omObjData *fn_1_21F8(void)
{
    omObjData *object;
    GuideWork *work;
    s32 i;

    object = omAddObjEx(lbl_1_bss_8, 1002, 1, 3, 2, NULL);
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(GuideWork), MEMORY_DEFAULT_NUM);
    object->data = work;
    work->pos.x = -298.59f;
    work->pos.z = 298.21f;
    work->pos.y = 0.0f;

    work->rot.x = 0.0f;
    work->rot.y = 134.42f;
    work->rot.z = 0.0f;

    work->posChange.x = 0.0f;
    work->posChange.z = 0.0f;
    work->posChange.y = 0.0f;
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 12));
    Hu3DModelLayerSet(object->model[0], 1);
    for (i = 0; i < 3; i++) {
        object->motion[i] = Hu3DJointMotion(object->model[0], HuDataSelHeapReadNum(lbl_1_rodata_E0[i], MEMORY_DEFAULT_NUM, HEAP_DATA));
    }
    work->unk5C = CharModelEffectNpcInit(object->model[0], object->motion[2], 1, 0xC);
    work->unk60 = CharModelEffectNpcInit(object->model[0], object->motion[1], 0, 0xC);
    CharModelLayerSetAll(1);
    Hu3DModelShadowSet(object->model[0]);
    Hu3DMotionShiftSet(object->model[0], object->motion[0], 0.0f, 8.0f, 0x40000001);
    ChangeMode(object, MODE_DISABLED);
    UpdateGuide(object);
    return object;
}

void fn_1_241C(omObjData *object)
{
    GuideWork *work = object->data;
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->model[i]);
    }
    for (i = 0; i < 3; i++) {
        Hu3DMotionKill(object->motion[i]);
    }
    HuMemDirectFree(work);
}

static void ChangeMode(omObjData *object, s32 mode)
{
    GuideWork *work = object->data;

    work->mode = mode;
    object->func = modes[mode];
    object->unk10 = 0;
    object->unk10 = 0;
}

static s32 GetMode(omObjData *object)
{
    GuideWork *work = object->data;

    return work->mode;
}

void fn_1_2508(omObjData *object, float destPos, float distFromCam, s32 walkDuration)
{
    GuideWork *work = object->data;

    work->posToMoveTo = destPos;
    work->distFromCam = distFromCam;
    work->velocity = 0.0f;
    work->speed = 1.0f / walkDuration;
    work->motionIdx = 0;
    ChangeMode(object, MODE_HANDLE_GUIDE);
}

static void HandleGuide(omObjData *object)
{
    GuideWork *work = object->data;
    float var_f31;
    float var_f30;

    switch (object->unk10) {
        case 0:
            work->unkAngle = fmod(-atan2d(work->pos.x, work->pos.z), 360.0);
            if (work->unkAngle < 0.0f) {
                work->unkAngle += 360.0f;
            }
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            var_f30 = sind(90.0f * work->velocity);
            var_f31 = work->unkAngle + var_f30 * (work->posToMoveTo - work->unkAngle);
            work->newPos.x = work->distFromCam * -sind(var_f31);
            work->newPos.z = work->distFromCam * cosd(var_f31);
            work->newPos.y = 0.0f;
            work->posChange.x = work->newPos.x - work->pos.x;
            work->posChange.z = work->newPos.z - work->pos.z;
            if (work->velocity <= 0.0f) {
                work->posChange.x = 0.0f;
                work->posChange.z = 0.0f;
                work->pos = work->newPos;
            }
            if ((work->velocity += work->speed) < 1.0f) {
                break;
            }
            var_f31 = fmod(-atan2d(work->pos.x, work->pos.z), 360.0);
            if (var_f31 < 0.0f) {
                var_f31 += 360.0f;
            }
            work->newPos.x = 422.0 * -sind(var_f31);
            work->newPos.z = 422.0 * cosd(var_f31);
            work->posChange.x = (work->newPos.x - work->pos.x) / 10.0f;
            work->posChange.z = (work->newPos.z - work->pos.z) / 10.0f;
            work->speed = 0.1f;
            work->velocity = 0.0f;
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            if ((work->velocity += work->speed) < 1.0f) {
                break;
            }
            object->unk10 = 3;
            /* fallthrough */
        case 3:
            work->pos = work->newPos;
            work->posChange.x = 0.0f;
            work->posChange.y = 0.0f;
            work->posChange.z = 0.0f;
            UpdateGuide(object);
            ChangeMode(object, MODE_DISABLED);
            break;
    }
    UpdateGuide(object);
}

static void UpdateGuide(omObjData *object)
{
    GuideWork *work = object->data;
    s16 var_r29;

    var_r29 = 0;
    work->distanceToMove = sqrtf(work->posChange.x * work->posChange.x + work->posChange.z * work->posChange.z);
    if (0.001f <= work->distanceToMove) {
        if (14.0f <= work->distanceToMove) {
            work->posChange.x /= work->distanceToMove;
            work->posChange.z /= work->distanceToMove;
            work->distanceToMove = 14.0f;
            work->posChange.x = 14.0f * work->posChange.x;
            work->posChange.z = 14.0f * work->posChange.z;
        }
        work->rot.y = fn_1_2D00(work->rot.y, atan2d(work->posChange.x, work->posChange.z), 0.4f);
        if (8.0f <= work->distanceToMove) {
            var_r29 = 2;
        }
        else {
            var_r29 = 1;
        }
    }
    work->pos.x += work->posChange.x;
    work->pos.z += work->posChange.z;
    if (work->motionIdx != var_r29) {
        Hu3DMotionShiftSet(*object->model, object->motion[var_r29], 0.0f, 8.0f, 0x40000001);
        work->motionIdx = var_r29;
    }
    omSetTra(object, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(object, work->rot.x, work->rot.y, work->rot.z);
}

static float fn_1_2D00(float arg0, float arg1, float arg2)
{
    float var_f30;
    float var_f31;

    var_f31 = fmod(arg1 - arg0, 360.0);
    if (0.0f > var_f31) {
        var_f31 += 360.0f;
    }
    if (180.0f < var_f31) {
        var_f31 -= 360.0f;
    }
    var_f30 = fmod(arg0 + var_f31 * arg2, 360.0);
    if (0.0f > var_f30) {
        var_f30 += 360.0f;
    }
    return var_f30;
}
