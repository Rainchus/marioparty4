#include "REL/option.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/process.h"

#include "dolphin.h"
#include "ext_math.h"

typedef struct {
    /* 0x00 */ Vec eyePos;
    /* 0x0C */ Vec lookingAt;
    /* 0x18 */ Vec tilt;
    /* 0x24 */ float zoom;
    /* 0x28 */ float rot;
    /* 0x2C */ Vec prevEyePos;
    /* 0x38 */ Vec prevLookingAt;
    /* 0x44 */ char unk44[0xC];
    /* 0x50 */ float prevZoom;
    /* 0x54 */ float prevRot;
    /* 0x58 */ Vec eyePosTarget;
    /* 0x64 */ Vec lookingAtTarget;
    /* 0x70 */ char unk70[0xC];
    /* 0x7C */ float zoomTarget;
    /* 0x80 */ float rotTarget;
    /* 0x84 */ float eyeVelocity;
    /* 0x88 */ float eyeSpeed;
    /* 0x8C */ float lookingAtVelocity;
    /* 0x90 */ float lookingAtSpeed;
    /* 0x94 */ float rotVelocity;
    /* 0x98 */ float rotSpeed;
} CameraWork; // Size 0x9C

static void fn_1_C58(omObjData *object, float *arg1, float *arg2, float *arg3);
static void HandlerWrapper(omObjData *object);
static void HandleCamera(omObjData *object);
static void fn_1_12E4(omObjData *object);
static void PrintDebugInfo(omObjData *object);

omObjData *lbl_1_bss_10;

static float pad_04_00000000_data[] = { 0.0f, 500.0f, 0.0f, 0.0f, -1.0f, 0.0f };

static s32 pad_04_00000018_data = -1;

omObjData *fn_1_7F8(void)
{
    omObjData *object;
    CameraWork *work;

    object = omAddObjEx(lbl_1_bss_8, 1001, 0, 0, 3, HandlerWrapper);
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(CameraWork), MEMORY_DEFAULT_NUM);
    object->data = work;
    work->eyePos.x = 0.0f;
    work->eyePos.y = 0.0f;
    work->eyePos.z = 0.0f;
    work->lookingAt.x = 0.0f;
    work->lookingAt.y = 0.0f;
    work->lookingAt.z = 0.0f;
    work->tilt.x = 0.0f;
    work->tilt.y = 1.0f;
    work->tilt.z = 0.0f;
    work->zoom = 0.0f;
    work->rot = 0.0f;
    work->lookingAtVelocity = 1.0f;
    work->eyeVelocity = 1.0f;
    work->rotVelocity = 1.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 42.0f, 10.0f, 8000.0f, 1.2f);
    fn_1_B74(object, 600.0f, 60.0f, 120.0f, 1);
    fn_1_A6C(object, 180.0f, 120.0f, 0.0f, 1);
    return object;
}

void fn_1_A3C(omObjData *object)
{
    HuMemDirectFree(object->data);
}

void fn_1_A6C(omObjData *object, float x, float y, float z, s32 duration)
{
    CameraWork *work = object->data;

    work->eyePosTarget.x = x;
    work->eyePosTarget.y = y;
    work->eyePosTarget.z = z;
    work->prevEyePos = work->eyePos;
    work->eyeVelocity = 0.0f;
    work->eyeSpeed = 1.0f / duration;
}

void fn_1_AF0(omObjData *object, float x, float y, float z, s32 duration)
{
    CameraWork *work = object->data;

    work->lookingAtTarget.x = x;
    work->lookingAtTarget.y = y;
    work->lookingAtTarget.z = z;
    work->prevLookingAt = work->lookingAt;
    work->lookingAtVelocity = 0.0f;
    work->lookingAtSpeed = 1.0f / duration;
}

void fn_1_B74(omObjData *object, float zoom, float rot, float y, s32 duration)
{
    CameraWork *work = object->data;

    work->lookingAtTarget.y = y;
    work->zoomTarget = zoom;
    work->rotTarget = rot;
    work->prevLookingAt.y = work->lookingAt.y;
    work->prevZoom = work->zoom;
    work->prevRot = work->rot;
    work->rotVelocity = 0.0f;
    work->rotSpeed = 1.0f / duration;
}

// GetZoom
float fn_1_BF8(omObjData *object)
{
    CameraWork *work = object->data;
    float zoom;

    zoom = work->zoom;
    return zoom;
}

// GetRot
float fn_1_C28(omObjData *object)
{
    CameraWork *work = object->data;
    float rot;

    rot = work->rot;
    return rot;
}

// GetEyePos
static void fn_1_C58(omObjData *object, float *eyePosX, float *eyePosY, float *eyePosZ)
{
    CameraWork *temp_r31 = object->data;

    *eyePosX = temp_r31->eyePos.x;
    *eyePosY = temp_r31->eyePos.y;
    *eyePosZ = temp_r31->eyePos.z;
}

// GetLookingAt
void fn_1_C88(omObjData *object, float *lookingAtX, float *lookingAtY, float *lookingAtZ)
{
    CameraWork *work = object->data;

    *lookingAtX = work->lookingAt.x;
    *lookingAtY = work->lookingAt.y;
    *lookingAtZ = work->lookingAt.z;
}

// CameraDone
s32 fn_1_CB8(omObjData *object)
{
    CameraWork *work = object->data;
    s32 var_r30 = 1;
    s32 var_r29 = 1;

    if (!(work->lookingAtVelocity < 1.0f) && !(work->rotVelocity < 1.0f)) {
        var_r29 = 0;
    }
    if (var_r29 == 0 && !(work->eyeVelocity < 1.0f)) {
        var_r30 = 0;
    }
    return var_r30;
}

static void HandlerWrapper(omObjData *object)
{
    HandleCamera(object);
}

static void HandleCamera(omObjData *object)
{
    CameraWork *work = object->data;
    float temp_f28;
    float xDiff;
    float zDiff;

    if (work->eyeVelocity < 1.0f) {
        temp_f28 = sind(90.0f * work->eyeVelocity);
        work->eyePos.x = work->prevEyePos.x + temp_f28 * (work->eyePosTarget.x - work->prevEyePos.x);
        work->eyePos.y = work->prevEyePos.y + temp_f28 * (work->eyePosTarget.y - work->prevEyePos.y);
        work->eyePos.z = work->prevEyePos.z + temp_f28 * (work->eyePosTarget.z - work->prevEyePos.z);
        if ((work->eyeVelocity += work->eyeSpeed) >= 1.0f) {
            work->eyePos = work->eyePosTarget;
        }
    }
    if (work->lookingAtVelocity < 1.0f) {
        temp_f28 = sind(90.0f * work->lookingAtVelocity);
        work->lookingAt.x = work->prevLookingAt.x + temp_f28 * (work->lookingAtTarget.x - work->prevLookingAt.x);
        work->lookingAt.y = work->prevLookingAt.y + temp_f28 * (work->lookingAtTarget.y - work->prevLookingAt.y);
        work->lookingAt.z = work->prevLookingAt.z + temp_f28 * (work->lookingAtTarget.z - work->prevLookingAt.z);
        if ((work->lookingAtVelocity += work->lookingAtSpeed) >= 1.0f) {
            work->lookingAt = work->lookingAtTarget;
        }
    }
    if (work->rotVelocity < 1.0f) {
        temp_f28 = sind(90.0f * work->rotVelocity);
        work->lookingAt.y = work->prevLookingAt.y + temp_f28 * (work->lookingAtTarget.y - work->prevLookingAt.y);
        work->zoom = work->prevZoom + temp_f28 * (work->zoomTarget - work->prevZoom);
        work->rot = work->prevRot + temp_f28 * (work->rotTarget - work->prevRot);
        if ((work->rotVelocity += work->rotSpeed) >= 1.0f) {
            work->lookingAt.y = work->lookingAtTarget.y;
            work->zoom = work->zoomTarget;
            work->rot = work->rotTarget;
        }
        work->lookingAt.x = work->zoom * -sind(work->rot);
        work->lookingAt.z = work->zoom * cosd(work->rot);
    }
    xDiff = work->lookingAt.x - work->eyePos.x;
    zDiff = work->lookingAt.z - work->eyePos.z;
    work->zoom = sqrtf(xDiff * xDiff + zDiff * zDiff);
    work->rot = fmod(-atan2d(xDiff, zDiff), 360.0);
    if (work->rot < 0.0f) {
        work->rot += 360.0f;
    }

    Hu3DCameraPosSet(1, work->eyePos.x, work->eyePos.y, work->eyePos.z, work->tilt.x, work->tilt.y, work->tilt.z, work->lookingAt.x,
        work->lookingAt.y, work->lookingAt.z);
}

static void fn_1_12E4(omObjData *object)
{
    CameraWork *work;

    if (HuPadBtn[0] & 0xF) {
        work = object->data;
        work->lookingAt.x += 0.5f * HuPadStkX[0];
        work->lookingAt.y += 0.5f * HuPadStkY[0];
        work->eyePos.z += 0.5f * HuPadTrigL[0];
        work->eyePos.z -= 0.5f * HuPadTrigR[0];
        work->eyePos.x += 0.5f * HuPadSubStkY[0];
        work->eyePos.y += 0.5f * HuPadSubStkX[0];
    }
}

static void PrintDebugInfo(omObjData *object)
{
    CameraWork *work = object->data;

    print8(32, 64, 1.5f, "AT  : x=%.2f y=%.2f z=%.2f", work->lookingAt.x, work->lookingAt.y, work->lookingAt.z);
    print8(32, 80, 1.5f, "EYE : x=%.2f y=%.2f z=%.2f", work->eyePos.x, work->eyePos.y, work->eyePos.z);
    print8(32, 96, 1.5f, "R : %.2f    DEG: %.2f", work->zoom, work->rot);
}
