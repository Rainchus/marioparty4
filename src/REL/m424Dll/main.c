#include "REL/m424Dll.h"

#include "game/hsfman.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/audio.h"

// BSS
Process* lbl_1_bss_4C;
s32 lbl_1_bss_48;
s32 lbl_1_bss_44;
s32 lbl_1_bss_40;
s32 lbl_1_bss_3C;
s32 lbl_1_bss_34;
s32 lbl_1_bss_2C;
s16 lbl_1_bss_24[4];
s16 lbl_1_bss_1C[4];
omObjData* lbl_1_bss_18;

// data
Vec lbl_1_data_54 = { 1000.0f, 2000.0f, 1000.0f };
Vec lbl_1_data_60 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_6C = { 0.0f, 0.0f, -450.0f };

// PROTO
void fn_1_264(omObjData* object);
void fn_1_FF0(void);

/// FUNCTIONS ///

void ObjectSetup(void) {
    s32 var_r31;
    Process* var_r30;
    CameraData* var_r29;

    OSReport("******* M424ObjectSetup *********");
    var_r30 = omInitObjMan(0x32, 0x2000);
    lbl_1_bss_4C = var_r30;
    omGameSysInit(var_r30);
    fn_1_FF0();
    var_r29 = &Hu3DCamera[0];
    var_r29->fov = -1.0f;
    Hu3DLightAllKill();
    Hu3DLighInit();
    HuAudSndGrpSet(0x31);
    lbl_1_bss_18 = omAddObjEx(var_r30, 0xFF, 2, 0, -1, fn_1_264);
    lbl_1_bss_48 = lbl_1_bss_44 = -1;
    lbl_1_bss_40 = 0;
    lbl_1_bss_3C = 0;
    lbl_1_bss_34 = 0;
    lbl_1_bss_2C = -1;
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_24[var_r31] = -1;
        lbl_1_bss_1C[var_r31] = -1;
    }
    Hu3DShadowCreate(30.0f, 1000.0f, 250000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&lbl_1_data_54, &lbl_1_data_60, &lbl_1_data_6C);
    Hu3DBGColorSet(0xFFU, 0xFFU, 0xFFU);
}
