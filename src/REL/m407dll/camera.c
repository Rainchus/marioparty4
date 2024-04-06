#include "game/process.h"
#include "game/object.h"
#include "game/hsfdraw.h"

#define M_PI 3.141592653589793

void fn_1_1CAC(f32, f32, f32);
void fn_1_1D08(f32, f32, f32);
void fn_1_1D64(f32);
void fn_1_2024(omObjData*);
double cos(double x);
double sin(double x);

Process* lbl_1_bss_34;
omObjData* lbl_1_bss_30;

typedef struct unkDominationData2 {
    s32 unk_00;
    s32 unk_04;
    Point3d unk_08;
    Point3d unk_14;
    f32 unk_20;
    Point3d unk_24;
    Point3d unk_30;
    f32 unk_3C;
    s32 unk_40;
    f32 unk_44;
    f32 unk_48;
} unkDominationData2;

void fn_1_1B1C(Process* arg0) {
    unkDominationData2* unkData;
    
    lbl_1_bss_34 = arg0;
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 45.0f, 10.0f, 40000.0f, 1.2f);
    lbl_1_bss_30 = omAddObjEx(lbl_1_bss_34, 0x80, 0U, 0U, -1, fn_1_2024);
    lbl_1_bss_30->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(unkDominationData2), 0x10000000);
    unkData = OM_GET_DATA_PTR(lbl_1_bss_30, unkDominationData2);
    unkData->unk_04 = 0;
    fn_1_1CAC(0.0f, 0.0f, 0.0f);
    fn_1_1D08(0.0f, 0.0f, 0.0f);
    fn_1_1D64(0.0f);
}

void fn_1_1CA8(void) {

}

void fn_1_1CAC(f32 arg8, f32 arg9, f32 argA) {
    Center.x = arg8;
    Center.y = arg9;
    Center.z = argA;
}

void fn_1_1CD4(f32* arg0, f32* arg1, f32* arg2) {
    *arg0 = Center.x;
    *arg1 = Center.y;
    *arg2 = Center.z;
}

void fn_1_1D08(f32 arg8, f32 arg9, f32 argA) {
    CRot.x = arg8;
    CRot.y = arg9;
    CRot.z = argA;
}

void fn_1_1D30(f32* arg0, f32* arg1, f32* arg2) {
    *arg0 = CRot.x;
    *arg1 = CRot.y;
    *arg2 = CRot.z;
}

void fn_1_1D64(f32 arg8) {
    CZoom = arg8;
}

void fn_1_1D74(f32* arg0) {
    *arg0 = CZoom;
}

s32 fn_1_1D88(void) {
    unkDominationData2* unkData = OM_GET_DATA_PTR(lbl_1_bss_30, unkDominationData2);
    return unkData->unk_04;
}

void fn_1_1DB0(Point3d* arg0, Point3d* arg1, f32* arg2, s32 arg3, s32 arg4) {
    Point3d* var_r30;
    Point3d* var_r29;
    f32 var_f31;
    unkDominationData2* temp_r31;

    temp_r31 = OM_GET_DATA_PTR(lbl_1_bss_30, unkDominationData2);
    temp_r31->unk_00 = arg4;
    
    if (arg0) {
        var_r30 = arg0;
    } else {
        var_r30 = &Center;
    }
    temp_r31->unk_08 = *var_r30;
    if (arg1) {
        var_r29 = arg1;
    } else {
        var_r29 = &CRot;
    }
    
    temp_r31->unk_14 = *var_r29;
    
    if (arg2) {
        var_f31 = *arg2;
    } else {
        var_f31 = CZoom;
    }
    
    temp_r31->unk_20 = var_f31;
    temp_r31->unk_24 = Center;
    temp_r31->unk_30 = CRot;
    temp_r31->unk_3C = CZoom;
    temp_r31->unk_40 = arg3;
    temp_r31->unk_44 = 0.0f;
    temp_r31->unk_48 = 1.0f / arg3;
    temp_r31->unk_04 = 1;
}

f32 fn_1_1F1C(f32 arg8, f32 arg9) {
    if (((arg8 > 0.0f) && (arg9 > 0.0f)) || ((arg8 < 0.0f) && (arg9 < 0.0f))) {
        return abs(arg8 - arg9);
    }
    
    return abs(arg8) + abs(arg9);
}

void fn_1_2024(omObjData* arg0) {
    Vec sp14;
    Vec sp8;
    f32 var_f31;
    f32 cZoomTemp;
    unkDominationData2* temp_r31;

    temp_r31 = OM_GET_DATA_PTR(arg0, unkDominationData2);
    if (temp_r31->unk_04 != 0) {
        switch (temp_r31->unk_00) {
        case 0:
            var_f31 = temp_r31->unk_44;
            break;
        case 1:
            var_f31 = temp_r31->unk_44;
            if (temp_r31->unk_48 > 0.5) {
                temp_r31->unk_00 = 2;
            }
            break;
        case 2:
            var_f31 = (f32) sin((M_PI * (90.0f * temp_r31->unk_44)) / 180.0);
            break;
        case 3:
            var_f31 = (f32) sin((M_PI * (90.0f * temp_r31->unk_44)) / 180.0);
            if (temp_r31->unk_48 > 0.5) {
                temp_r31->unk_00 = 4;
            }
            break;
        case 4:
            var_f31 = sin((M_PI * (90.0f * temp_r31->unk_44)) / 180.0);
            var_f31 *= var_f31;
            break;
        }
        sp14.x = temp_r31->unk_24.x + (var_f31 * (temp_r31->unk_08.x - temp_r31->unk_24.x));
        sp14.y = temp_r31->unk_24.y + (var_f31 * (temp_r31->unk_08.y - temp_r31->unk_24.y));
        sp14.z = temp_r31->unk_24.z + (var_f31 * (temp_r31->unk_08.z - temp_r31->unk_24.z));
        sp8.x = temp_r31->unk_30.x + (var_f31 * (temp_r31->unk_14.x - temp_r31->unk_30.x));
        sp8.y = temp_r31->unk_30.y + (var_f31 * (temp_r31->unk_14.y - temp_r31->unk_30.y));
        sp8.z = temp_r31->unk_30.z + (var_f31 * (temp_r31->unk_14.z - temp_r31->unk_30.z));
        cZoomTemp = temp_r31->unk_3C + (var_f31 * (temp_r31->unk_20 - temp_r31->unk_3C));
        temp_r31->unk_44 += temp_r31->unk_48;
        Center = sp14;
        CRot = sp8;
        CZoom = cZoomTemp;
        if (--temp_r31->unk_40 <= 0) {
            Center = temp_r31->unk_08;
            CRot = temp_r31->unk_14;
            CZoom = temp_r31->unk_20;
            temp_r31->unk_04 = 0;
        }
    }
    omOutView(arg0);
}
