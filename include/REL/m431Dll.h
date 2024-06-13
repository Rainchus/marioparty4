#ifndef M431DLL_H
#define M431DLL_H

#include "game/object.h"

typedef struct bss_12C_inner {
	Vec unk0;
	float unkC;
	s8 unk10;
} Bss12CInner;

typedef struct bss_12c_struct {
	s16 unk0[2];
	u8 unk4[0x8];
	Vec unkC;
	u8 unk18[4];
	Bss12CInner unk1C[2];
	u8 unk44[0xF0];
	s16 unk134[2];
	s16 unk138[2];
} Bss12CStruct;

typedef struct bss_61C_work {
	u8 unk0[0x4];
	s16 unk4;
	s16 unk6[2];
	s16 unkA;
	u8 unkC[8];
	struct bss_61C_work *unk14;
	u8 unk18[0x46];
	s16 unk5E[8];
	s16 unk6E;
	s16 unk70;
	s16 unk72;
	u8 unk74[0x44];
} Bss61CWork;

extern Bss12CStruct lbl_1_bss_12C[4];
extern omObjData *lbl_1_bss_61C[4];
extern float lbl_1_data_1D0;

void fn_1_7ABC(Process *objman);
s32 fn_1_7FB8(s16 arg0);
void fn_1_A7D0(s16 arg0);
void fn_1_A904(s16 arg0);

s32 fn_1_8474(s16 arg0);

#endif
