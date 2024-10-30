#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "string.h"

#ifndef __MWERKS__
#include "game/esprite.h"
#include "game/frand.h"
#endif

#include "REL/m443Dll.h"

s32 lbl_1_bss_78[6];
omObjData* lbl_1_bss_90[4];

char* lbl_1_data_264[0x8] = {
    "itemhook-r", "itemhook-r", "itemhook-r", "itemhook-r", 
    "itemhook-r", "itemhook-r", "itemhook-r", "itemhook-r"
};

u32 lbl_1_data_284[8][2] = {
    {0x4A0005, 0x4A0006}, {0x4A0007, 0x4A0008}, 
    {0x4A0009, 0x4A000A}, {0x4A000B, 0x4A000C}, 
    {0x4A000D, 0x4A000E}, {0x4A000F, 0x4A0010}, 
    {0x4A0011, 0x4A0012}, {0x4A0013, 0x4A0014}, 
};

s32 lbl_1_data_2C4[4] = {
    0, 0x4A0020, 0x17, 0x72
};

s32 lbl_1_data_324[4] = {
    0x727, 0x728, 0x729, 0x72A,
};
s32 lbl_1_data_334[4] = {
    0x72B, 0x72C, 0x72D, 0x72E,
};

/////
void fn_1_5680(omObjData* object);
void fn_1_5BD4(omObjData*);
void fn_1_8508(omObjData*);
f32 fn_1_8C8C(s32, f32);
/////

void fn_1_5444(Process* arg0) {
    u32 sp18[4];
    u32 sp8[4];
    omObjData* var_r28;
    u32 var_r29;
    s16 var_r30;
    s16 var_r31;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        sp18[var_r31] = GWPlayerCfg[var_r31].group;
        sp8[var_r31] = var_r31;
    }
    
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        for (var_r30 = var_r31 + 1; var_r30 < 4; var_r30++) {
            if (sp18[var_r31] > sp18[var_r30]) {
                var_r29 = sp18[var_r31];
                sp18[var_r31] = sp18[var_r30];
                sp18[var_r30] = var_r29;
                var_r29 = sp8[var_r31];
                sp8[var_r31] = sp8[var_r30];
                sp8[var_r30] = var_r29;
            }
        }
    }
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_78[sp8[var_r31]] = (s16)var_r31;
    }
    omMakeGroupEx(arg0, 0, 4);
    omGetGroupMemberListEx(arg0, 0);
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r28 = lbl_1_bss_90[var_r31] = omAddObjEx(arg0, 0x28, 5, 4, 0, fn_1_5680);
        var_r28->work[0] = var_r31;
    }
}

void fn_1_565C(void) {
    CharModelKill(-1);
}

void fn_1_5680(omObjData* object) {
    f32 spC[4] = {0.25f, 0.5f, 0.75f, 1.0f};
    s32 sp8;
    f32 temp_f0;
    s32 temp_r27;
    s32 temp_r3;
    s32 var_r29;
    u32 temp_r25;
    M443DllWorkStruct* temp_r31;
    HsfanimStruct01* var_r28;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x134, MEMORY_DEFAULT_NUM);
    temp_r31 = object->data;
    memset(temp_r31, 0, 0x134);
    object->stat |= 0x100;
    temp_r25 = object->work[0];
    temp_r27 = GWPlayerCfg[temp_r25].character;
    temp_r31->unk0 = temp_r27;
    sp8 = temp_r31->unk4 = 0;
    temp_r31->unkC = lbl_1_bss_78[object->work[0]];
    temp_r31->unk5C = spC[GWPlayerCfg[temp_r25].diff & 3];
    temp_r31->unk24 = GWPlayerCfg[object->work[0]].iscom;
    object->model[0] = CharModelCreate(temp_r27, 8);
    Hu3DModelLayerSet(object->model[0], 4);
    object->model[1] = Hu3DModelCreateFile(lbl_1_data_284[temp_r27][0]);
    Hu3DModelLayerSet(object->model[1], 4);
    Hu3DMotionSpeedSet(object->model[1], 0.0f);
    object->model[2] = Hu3DModelCreateFile(lbl_1_data_284[temp_r27][1]);
    Hu3DModelLayerSet(object->model[2], 4);
    Hu3DMotionSpeedSet(object->model[2], 0.0f);
    Hu3DModelAttrSet(object->model[2], 1);
    
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        if (lbl_1_data_2C4[var_r29] < 0x10000) {
            object->motion[var_r29] = CharModelMotionCreate(temp_r27, lbl_1_data_2C4[var_r29]);
        } else {
            object->motion[var_r29] = Hu3DJointMotion(object->model[0], HuDataSelHeapReadNum(temp_r27 + lbl_1_data_2C4[var_r29], 0x10000000, HEAP_DATA));
        }
    }
    CharModelMotionDataClose(temp_r27);
    temp_r3 = Hu3DParticleCreate(HuSprAnimReadFile(0x4A001D), 0xC8);
    object->model[3] = temp_r3;
    Hu3DModelLayerSet(temp_r3, 4);
    var_r28 = ((ParticleData*)Hu3DData[temp_r3].unk_120)->unk_48;
    
    for (var_r29 = 0; var_r29 < 0xC8; var_r29++, var_r28++) {
        var_r28->unk2C = 0.0f;
        var_r28->unk40.a = 0;
        var_r28->unk00 = 0;
    }
    
    
    object->trans.x = temp_r31->unkC4.x = temp_r31->unkDC.x = (100.0f * (4.0f * object->work[0])) - 600.0f;
    object->trans.y = temp_r31->unkC4.y = temp_r31->unkDC.y = 0.0f;
    object->trans.z = temp_r31->unkC4.z = temp_r31->unkDC.z = 0.0f;
    
    temp_r31->unkD0.x = temp_r31->unkD0.y = temp_r31->unkD0.z = 0.0f;
    temp_r31->unkE8.x = temp_r31->unkE8.y = temp_r31->unkE8.z = 0.0f;
    temp_r31->unk48 = temp_r31->unk4C = 0.0f;
    temp_r31->unk50 = 0.0f;
    temp_r31->unk54 = 0.02f;
    temp_r31->unk58 = 180.0f;
    temp_r31->unkC0 = 50.0f;
    temp_r31->unkBC = 350.0f;
    temp_r31->unk8 = -1;
    temp_r31->unk1C = 1;
    temp_r31->unk20 = 0;
    temp_r31->unk9C = 1.0f;
    temp_r31->unk98 = 0.0f;
    temp_r31->unkA0 = 0.0f;
    temp_r31->unkA4 = 0.0f;
    temp_r31->unk88 = 1000.0f;
    temp_r31->unk90 = fn_1_8C8C(temp_r31->unk80, temp_r31->unk88);
    temp_r31->unkA8 = temp_r31->unkAC = -1;
    temp_r31->unkB0 = temp_r31->unkB4 = temp_r31->unkB8 = -1;
    temp_r31->unkB4 = HuAudFXPlay(lbl_1_data_334[object->work[0]]);
    temp_r31->unk68 = -1;
    temp_r31->unk60 = 0;
    temp_r31->unk100 = fn_1_4148(object->work[0] + 1);
    temp_r31->unk104 = fn_1_41B0(object->work[0] + 1);
    temp_r31->unk100->unk_00 = 0;
    fn_1_8508(object);
    temp_r31->unk34 = 0;
    object->func = fn_1_5BD4;
}
