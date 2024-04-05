#include "REL/resultdll.h"

s16 lbl_1_bss_1A9C[32];
s16 lbl_1_bss_1A5C[32];
s16 lbl_1_bss_1A1A[33];
s16 lbl_1_bss_1A18;

void fn_1_8FF8(DataListModel *model_list)
{
	DataListModel *list;
	s16 i;
	s16 model;
	s16 clear_i;
	ModelData *model_ptr;
	void *data;
	list = model_list;
	for(clear_i=0; clear_i<32; clear_i++) {
		lbl_1_bss_1A9C[clear_i] = lbl_1_bss_1A5C[clear_i] = -1;
	}
	for(i=0; list->datanum != 0xFFFFFFFF; list++, i++) {
		if(list->type == 0) {
			data = HuDataSelHeapReadNum(list->datanum, MEMORY_DEFAULT_NUM, HEAP_DATA);
			model = Hu3DModelCreate(data);
			lbl_1_bss_1A9C[i] = model;
			Hu3DModelAttrSet(model, list->attr);
			Hu3DModelPosSetV(model, &list->pos);
			Hu3DModelRotSetV(model, &list->rot);
			Hu3DModelScaleSetV(model, &list->scale);
			model_ptr = &Hu3DData[model];
			if(model_ptr->unk_08 != -1) {
				lbl_1_bss_1A5C[i] = model_ptr->unk_08;
			}
		} else if(list->type == 1) {
			data = HuDataSelHeapReadNum(list->datanum, MEMORY_DEFAULT_NUM, HEAP_DATA);
			lbl_1_bss_1A5C[i] = Hu3DJointMotion(lbl_1_bss_1A9C[list->mot_link], data);
			
		}
		(void)i;
	}
	list = model_list;
	for(i=0; list->datanum != 0xFFFFFFFF; list++, i++) {
		if(list->type == 2) {
			model = Hu3DModelLink(lbl_1_bss_1A9C[list->link]);
			lbl_1_bss_1A9C[i] = model;
			Hu3DModelAttrSet(model, list->attr);
			Hu3DModelPosSetV(model, &list->pos);
			Hu3DModelRotSetV(model, &list->rot);
			Hu3DModelScaleSetV(model, &list->scale);
		}
		if(list->mot_link != -1) {
			Hu3DMotionSet(lbl_1_bss_1A9C[i], lbl_1_bss_1A5C[list->mot_link]);
		}
		(void)i;
	}
}

void fn_1_927C(DataListSprite *sprite_list)
{
	DataListSprite *list;
	s16 sprite;
	s16 clear_i;
	s16 i;
	list = sprite_list;
	for(clear_i=0; clear_i<32; clear_i++) {
		lbl_1_bss_1A1A[clear_i] = -1;
	}
	for(i=0; list->datanum; i++, list++) {
		sprite = espEntry(list->datanum, 100, 0);
		lbl_1_bss_1A1A[i] = sprite;
		espPosSet(sprite, list->x, list->y);
		espColorSet(sprite, list->color.r, list->color.g, list->color.b);
		espTPLvlSet(sprite, list->color.a/255.0f);
		espPriSet(sprite, list->prio);
		espAttrSet(sprite, list->attr);
	}
}

void fn_1_93B4(void)
{
	s16 i;
	for(i=0; i<32; i++) {
		if(lbl_1_bss_1A1A[i] != -1) {
			espKill(lbl_1_bss_1A1A[i]);
		}
	}
}