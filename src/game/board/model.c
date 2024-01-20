#include "game/board/main.h"
#include "game/board/model.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/object.h"
#include "unsplit.h"

#define BOARD_MODEL_MAX 256
#define BOARD_MOT_MAX 32

typedef struct board_model {
	struct {
		u8 visible : 1;
		u8 visible_old : 1;
		u8 field00_bit2 : 1;
		u8 field00_bit3 : 1;
		u8 field00_bit4 : 1;
	};
	s8 mot_count;
	s8 character;
	u8 alpha;
	u8 layer;
	u16 camera;
	s16 index;
	s16 id;
	s16 mot_id[BOARD_MOT_MAX];
	s16 curr_mot;
	HsfData *data;
	HsfData *mot_data[BOARD_MOT_MAX];
	float unk_D4;
	s32 data_num;
	float mot_start;
	float mot_end;
	Vec trans;
	Vec rot;
	Vec scale;
} BoardModel;

static s16 modelDataNum;
static omObjData *modelMgrObj;
static BoardModel *modelDataList;

static void ModelMgrFunc(omObjData *object);

static BoardModel *SearchBoardModel(s16 id);
static void KillBoardModel(BoardModel *model);
static s32 CreateBoardModel(BoardModel *model, s32 data_num, s32 link);
static s32 CreateBoardModelMotion(BoardModel *model, s32 count, s32 *data_num);

void BoardModelDummyUpdate(void);
void BoardModelVisibilityUpdate(void);

typedef struct modelmgr_work {
	u8 kill : 1;
} ModelMgrWork;

void BoardModelInit(void)
{
	ModelMgrWork *work;
	s32 i;
	modelDataList = HuMemDirectMallocNum(HEAP_SYSTEM, BOARD_MODEL_MAX*sizeof(BoardModel), MEMORY_DEFAULT_NUM);
	reflectMapNo = 0;
	modelDataNum = 0;
	memset(modelDataList, 0, BOARD_MODEL_MAX*sizeof(BoardModel));
	for(i=0; i<BOARD_MODEL_MAX; i++) {
		modelDataList[i].index = -1;
		modelDataList[i].visible = 0;
	}
	modelMgrObj = omAddObjEx(boardObjMan, 32258, 0, 0, -1, ModelMgrFunc);
	work = OM_GET_WORK_PTR(modelMgrObj, ModelMgrWork);
	work->kill = 0;
	omSetStatBit(modelMgrObj, OM_STAT_NOPAUSE|0x80);
}

void BoardModelKillAll(void)
{
	if(modelMgrObj) {
		ModelMgrWork *work = OM_GET_WORK_PTR(modelMgrObj, ModelMgrWork);
		work->kill = 1;
	}
	if(modelDataList) {
		BoardModel *model;
		for(model=modelDataList; model < &modelDataList[BOARD_MODEL_MAX]; model++) {
			KillBoardModel(model);
		}
		if(modelDataList) {
			HuMemDirectFree(modelDataList);
			modelDataList = NULL;
		}
		
	}
}

static void ModelMgrFunc(omObjData *object)
{
	ModelMgrWork *work = OM_GET_WORK_PTR(modelMgrObj, ModelMgrWork);
	if(work->kill || BoardIsKill()) {
		modelMgrObj = NULL;
		omDelObjEx(HuPrcCurrentGet(), object);
		return;
	}
	BoardModelDummyUpdate();
	BoardModelVisibilityUpdate();
}

void BoardModelDummyUpdate(void)
{
	
}

void BoardModelVisibilityUpdate(void)
{
	s32 i;
	BoardModel *model;
	u32 temp[2];
	Vec pos, target;
	temp[1] = temp[0] = 0;
	BoardCameraPosGet(&pos);
	BoardCameraTargetGet(&target);
	for(i=0, model = modelDataList; i<BOARD_MODEL_MAX; i++, model++) {
		u32 attr;
		if(model->index == -1) {
			continue;
		}
		attr = Hu3DModelAttrGet(model->id);
		if(!model->visible) {
			if(!(attr & 0x1)) {
				Hu3DModelAttrSet(model->id, 1);
			}
		} else {
			if(attr & 0x1) {
				Hu3DModelAttrReset(model->id, 1);
			}
		}
	}
}

void BoardModelHideSetAll(s32 flag)
{
	BoardModel *model;
	if(!modelDataList) {
		return;
	}
	
	for(model=modelDataList; model < &modelDataList[BOARD_MODEL_MAX]; model++) {
		if(model->index == -1) {
			continue;
		}
		if(flag) {
			model->visible_old = model->visible;
			model->visible = 0;
		} else {
			model->visible = model->visible_old;
		}
	}
}

void BoardModelAmbSetAll(float r, float g, float b)
{
	BoardModel *model;
	for(model=modelDataList; model < &modelDataList[BOARD_MODEL_MAX]; model++) {
		if(model->index == -1) {
			continue;
		}
		BoardModelAmbSet(model->index, r, g, b);
	}
}

void BoardModelCameraSetAll(u16 camera)
{
	BoardModel *model;
	for(model=modelDataList; model < &modelDataList[BOARD_MODEL_MAX]; model++) {
		if(model->index == -1) {
			continue;
		}
		if(model->character != -1) {
			continue;
		}
		Hu3DModelCameraSet(model->id, camera);
		model->camera = camera;
	}
}

static s16 CreateInstance(s32 character, s32 data_num, s32 *mot_list, s32 link, s32 arg4)
{
	BoardModel *model;
	s32 i;
	model = NULL;
	for(i=0; i<BOARD_MODEL_MAX; i++) {
		if(modelDataList[i].index == -1) {
			model = &modelDataList[i];
			break;
		}
	}
	if(!model) {
		return -1;
	}
	memset(model, 0, sizeof(BoardModel));
	model->index = i+1;
	model->character = character;
	modelDataNum++;
	if(CreateBoardModel(model, data_num, link) == 0) {
		s32 count;
		count = 0;
		if(mot_list) {
			for(count=0; mot_list[count] >= 0; count++);
			if(count >= BOARD_MOT_MAX) {
				count = BOARD_MOT_MAX;
			}
		}
		for(i=0; i<BOARD_MOT_MAX; i++) {
			model->mot_id[i] = -1;
		}
		if(CreateBoardModelMotion(model, count, mot_list) == 0) {
			model->visible = 1;
			model->visible_old = model->visible;
			model->field00_bit2 = 0;
			model->field00_bit4 = 0;
			model->unk_D4 = 100.0f;
			model->scale.x = model->scale.y = model->scale.z = 1.0f;
			model->curr_mot = 0;
			Hu3DModelCameraSet(model->id, 1);
			Hu3DModelLayerSet(model->id, 0);
			model->field00_bit3 = 0;
			model->alpha = 255;
			BoardModelPosSet(model->index, 0.0f, 0.0f, 0.0f);
			BoardModelRotSet(model->index, 0.0f, 0.0f, 0.0f);
			BoardModelScaleSet(model->index, 1.0f, 1.0f, 1.0f);
			BoardModelAmbSet(model->index, 1.0f, 1.0f, 1.0f);
			return model->index;
		}
	}
	BoardModelKill(model->index);
	return -1;
}

s16 BoardModelCreate(s32 data_num, s32 *mot_list, s32 link)
{
	return CreateInstance(-1, data_num, mot_list, link, 0);
}

s16 BoardModelCreateCharacter(s32 character, s32 data_num, s32 *mot_list, s32 link)
{
	return CreateInstance(character, data_num, mot_list, link, 0);
}

s16 BoardModelCreateParam(BoardModelParam *param, Vec *pos, Vec *rot)
{
	float unk_param;
	s16 model = BoardModelCreate(param->data_num, NULL, param->link);
	if(model == -1) {
		return -1;
	}
	BoardModelMotionStart(model, 0, (param->pause) ? 0x40000001 : 0);
	if(!param->start_mot) {
		BoardModelMotionSpeedSet(model, 0.0f);
	}
	BoardModelExistDupe(model, param->field04_bit0);
	BoardModelVisibilitySet(model, param->visible);
	if(pos) {
		BoardModelPosSetV(model, pos);
	}
	if(rot) {
		BoardModelRotSetV(model, rot);
	}
	OSs16tof32(&param->unk6, &unk_param);
	fn_8006DDE8(model, unk_param);
	return model;
}

void BoardModelKill(s16 model)
{
	BoardModel *model_ptr = SearchBoardModel(model);
	if(model_ptr) {
		KillBoardModel(model_ptr);
	}
}

s16 BoardModelIDGet(s16 model)
{
	BoardModel *model_ptr = SearchBoardModel(model);
	if(!model_ptr) {
		return -1;
	} else {
		return model_ptr->id;
	}
}

s32 fn_8006DC1C(s16 model, s32 arg1)
{
	BoardModel *model_ptr = SearchBoardModel(model);
	if(!model_ptr) {
		return -1;
	} else {
		model_ptr->field00_bit3 = arg1;
		return 0;
	}
}

s32 BoardModelPassSet(s16 model, s32 pass)
{
	BoardModel *model_ptr = SearchBoardModel(model);
	if(!model_ptr) {
		return -1;
	} else {
		if(pass != 0) {
			Hu3DModelAttrSet(model_ptr->id, 2);
		} else {
			Hu3DModelAttrReset(model_ptr->id, 2);
		}
		return 0;
	}
}

s32 BoardModelAmbSet(s16 model, float r, float g, float b)
{
	BoardModel *model_ptr = SearchBoardModel(model);
	if(!model_ptr) {
		return -1;
	} else {
		Hu3DModelAmbSet(model_ptr->id, r, g, b);
		return 0;
	}
}

s32 BoardModelExistCheck(s16 model, s32 arg1)
{
	BoardModel *model_ptr = SearchBoardModel(model);
	if(!model_ptr) {
		return -1;
	} else {
		return 0;
	}
}

s32 BoardModelExistDupe(s16 model, s32 arg1)
{
	BoardModel *model_ptr = SearchBoardModel(model);
	if(!model_ptr) {
		return -1;
	} else {
		return 0;
	}
}

s32 fn_8006DDE8(s16 model, float arg1)
{
	BoardModel *model_ptr = SearchBoardModel(model);
	if(!model_ptr) {
		return -1;
	} else {
		if(arg1 < 0) {
			arg1 = -1;
		}
		model_ptr->unk_D4 = arg1;
		return 0;
	}
}

s32 BoardModelMotionCreate(s16 model, s32 data_num)
{
	BoardModel *model_ptr = SearchBoardModel(model);
	s32 i;
	if(!model_ptr) {
		return -1;
	} else {
		s16 id;
		if(model_ptr->mot_count >= BOARD_MOT_MAX) {
			return -1;
		}
		for(i=1; i<BOARD_MOT_MAX; i++) {
			if(model_ptr->mot_id[i] == -1) {
				break;
			}
		}
		if(model_ptr->character == -1) {
			model_ptr->mot_data[i] = HuDataSelHeapReadNum(data_num, MEMORY_DEFAULT_NUM, HEAP_DATA);
			if(!model_ptr->mot_data[i]) {
				return -1;
			}
			model = Hu3DJointMotion(model_ptr->id, model_ptr->mot_data[i]);
		} else {
			model = CharMotionCreate(model_ptr->character, data_num);
			CharMotionClose(model_ptr->character);
		}
		model_ptr->mot_id[i] = model;
		model_ptr->mot_count++;
		return i;
	}
}

s32 BoardModelMotionKill(s16 model, s32 motion)
{
	BoardModel *model_ptr = SearchBoardModel(model);
	s32 i;
	if(!model_ptr) {
		return -1;
	} else {
		if(motion >= BOARD_MOT_MAX || motion <= 0) {
			return -1;
		}
		if(motion == model_ptr->curr_mot && model_ptr->curr_mot != 0) {
			BoardModelMotionStart(model, 0, 0);
		}
		if(model_ptr->mot_id[motion] > 0) {
			if(model_ptr->character == -1) {
				Hu3DMotionKill(model_ptr->mot_id[motion]);
			} else {
				CharMotionKill(model_ptr->character, model_ptr->mot_id[motion]);
			}
			model_ptr->mot_id[motion] = -1;
		}
		model_ptr->mot_data[motion] = NULL;
		model_ptr->mot_count--;
		return 0;
	}
}

static BoardModel *SearchBoardModel(s16 id)
{
	BoardModel *model;
	if(id <= 0 || id > BOARD_MODEL_MAX || !modelDataList || BoardIsKill()) {
		return NULL;
	}
	model = &modelDataList[id-1];
	if(model->index != id) {
		return NULL;
	}
	return model;
}

static void KillBoardModel(BoardModel *model)
{
	s32 i;
	if(model->index == -1) {
		return;
	}
	if(model->character == -1) {
		model->mot_id[0] = -1;
		if(model->id >= 0) {
			Hu3DModelKill(model->id);
			model->id = -1;
		}
		for(i=1; i<BOARD_MOT_MAX; i++) {
			if(model->mot_id[i] >= 0) {
				if(i != 0) {
					Hu3DMotionKill(model->mot_id[i]);
				}
				model->mot_id[i] = -1;
			}
			model->mot_data[i] = NULL;
		}
		model->data = NULL;
		model->data_num = 0;
	} else {
		for(i=0; i<BOARD_MOT_MAX; i++) {
			model->mot_id[i] = -1;
			model->mot_data[i] = NULL;
		}
		if(model->data) {
			if(model->id >= 0) {
				model->id = -1;
			}
			model->data = NULL;
		}
		CharModelKill(model->character);
		model->character = -1;
	}
	modelDataNum--;
	model->index = -1;
	model->visible = 0;
}

static BoardModel *FindLinkModel(s32 data_num)
{
	BoardModel *model;
	for(model=modelDataList; model < &modelDataList[BOARD_MODEL_MAX]; model++) {
		if(model->data_num == data_num) {
			return model;
		}
	}
	return NULL;
}

static s32 CreateBoardModel(BoardModel *model, s32 data_num, s32 link)
{
	BoardModel *linked_mdl = NULL;
	if(link && model->character == -1) {
		linked_mdl = FindLinkModel(data_num);
		if(linked_mdl) {
			model->id = Hu3DModelLink(linked_mdl->id);
			model->data = NULL;
			model->data_num = 0;
			return 0;
		}
	}
	if(model->character == -1) {
		model->data = HuDataSelHeapReadNum(data_num, MEMORY_DEFAULT_NUM, HEAP_DATA);
		if(!model->data) {
			s32 size_data, size_dvd;
			size_data = HuMemHeapSizeGet(HEAP_DATA)-HuMemUsedMallocSizeGet(HEAP_DATA);
			size_dvd = HuMemHeapSizeGet(HEAP_DVD)-HuMemUsedMallocSizeGet(HEAP_DVD);
			return -1;
		}
	} else {
		model->data = NULL;
	}
	if(model->character == -1) {
		model->id = Hu3DModelCreate(model->data);
	} else {
		model->id = CharModelCreate(model->character, 2);
	}
	Hu3DModelAttrSet(model->id, 0x4000);
	if(model->id < 0) {
		return -1;
	} else {
		model->data_num = data_num;
		return 0;
	}
}

static s32 CreateBoardModelMotion(BoardModel *model, s32 count, s32 *data_num)
{
	void *data;
	s32 i;
	model->mot_id[0] = Hu3DData[model->id].unk_08;
	if(!data_num) {
		model->mot_count = 1;
		return 0;
	}
	data = NULL;
	for(i=0; i<count; i++) {
		s16 index;
		if(model->character == -1) {
			data = HuDataSelHeapReadNum(data_num[i], MEMORY_DEFAULT_NUM, HEAP_DATA);
			if(!data) {
				return -1;
			}
			index = Hu3DJointMotion(model->id, data);
		} else {
			index = CharMotionCreate(model->character, data_num[i]);
		}
		if(index < 0) {
			return -1;
		}
		model->mot_id[i+1] = index;
		model->mot_data[i+1] = data;
	}
	model->mot_count = count+1;
	return 0;
}