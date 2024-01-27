#include "game/armem.h"
#include "game/sprite.h"
#include "game/process.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"

#include "stdarg.h"

extern s16 HuSysVWaitGet(s16 param);

typedef struct seq_work SeqWork;

typedef int (*SeqUpdateFunc)(SeqWork *work);
typedef int (*SeqInitFunc)(SeqWork *work, va_list params);

typedef struct seq_work {
	SeqUpdateFunc update;
	char *data;
	float x;
	float y;
	float scale_x;
	float scale_y;
	float unk_18;
	float work_float[2];
	float unk_24;
	s16 time;
	s16 time_max;
	s16 work_s16[4];
	s16 param[2];
	s16 type;
	s16 sprite_grp[16];
	s16 sprite[16];
	u8 seq_no;
	u8 stat;
	u8 unk_7C;
	u8 unk_7D;
} SeqWork;

typedef struct seq_info {
	SeqInitFunc init;
	SeqUpdateFunc update;
	float x;
	float y;
	float scale_x;
	float scale_y;
	s32 time_max;
} SeqInfo;

static int SeqInitTimer(SeqWork *work, va_list params);
static int SeqUpdateTimer(SeqWork *work);

static int SeqInitType2(SeqWork *work, va_list params);
static int SeqUpdateType2(SeqWork *work);

static int SeqInitMGBasic(SeqWork *work, va_list params);
static int SeqUpdateMGBasic(SeqWork *work);
static int SeqInitMGCommon(SeqWork *work, va_list params);
static int SeqUpdateMG1vs3(SeqWork *work);
static int SeqUpdateMGBattle(SeqWork *work);
static int SeqUpdateMGStory(SeqWork *work);
static int SeqUpdateMG2vs2(SeqWork *work);
static int SeqUpdateMGBowser(SeqWork *work);

static int SeqInitWin(SeqWork *work, va_list params);
static int SeqUpdateWin(SeqWork *work);
static int SeqInitDraw(SeqWork *work, va_list params);
static int SeqUpdateDraw(SeqWork *work);
static int SeqInitRecord(SeqWork *work, va_list params);
static int SeqUpdateRecord(SeqWork *work);

static int SeqInitFlip(SeqWork *work, va_list params);
static int SeqUpdateFlip(SeqWork *work);

s32 mgSeqInitF = -1;

static SeqInfo seqInfoTbl[] = {
	{ NULL, NULL, 292.0f, 240.0f, 1.0f, 1.0f, 60 },
	{ SeqInitTimer, SeqUpdateTimer, 292.0f, 64.0f, 1.0f, 1.0f, 60 },
	{ SeqInitType2, SeqUpdateType2, 292.0f, 240.0f, 0.5f, 0.5f, 60 },
	{ SeqInitMGBasic, SeqUpdateMGBasic, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitMGCommon, SeqUpdateMG1vs3, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitWin, SeqUpdateWin, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitMGCommon, SeqUpdateMGBattle, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitMGCommon, SeqUpdateMGStory, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitMGBasic, SeqUpdateMGBasic, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitMGCommon, SeqUpdateMG2vs2, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitFlip, SeqUpdateFlip, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitMGCommon, SeqUpdateMGBowser, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitWin, SeqUpdateWin, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitDraw, SeqUpdateDraw, 292.0f, 240.0f, 1.0f, 1.0f, 60 },
	{ SeqInitRecord, SeqUpdateRecord, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ NULL, NULL, 292.0f, 240.0f, 1.0f, 1.0f, 60 },
	{ NULL, NULL, 292.0f, 240.0f, 1.0f, 1.0f, 60 },
};

static s32 seqType2SprTbl[6] = {
	0, 0, 0, 0, 0, 0
};

static s16 mgSeqTypeTbl[9] = {
	8,
	4,
	9,
	11,
	6,
	10,
	7,
	11,
	7
};

static char lbl_8012F336[] = {
	0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8,
	0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0,
	0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8,
	0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0,
	0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8,
	0xD9, 0xDA, 0xDB, 0xDC, 0xA6, 0xDD, 0xA7, 0xA8,
	0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB6,
	0xB7, 0xB8, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
	0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xCA, 0xCB, 0xCC,
	0xCD, 0xCE, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0x21,
	0x3F, 0xB0, 0x00
};

static char lbl_8012F389[] = "x first\n";
static char lbl_8012F392[] = "y first\n";

static char seqFontAlphaTbl[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

static char seqFontKanaTbl[] = {
	0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8,
	0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0,
	0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8,
	0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0,
	0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8,
	0xD9, 0xDA, 0xDB, 0xDC, 0xA6, 0xDD, 0xA7, 0xA8,
	0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB6,
	0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE,
	0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xCA, 0xCB,
	0xCC, 0xCD, 0xCE, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE,
	0xB0, 0x00
};

static char seqFontNumTbl[] = "0123456789";


static s32 *letterBufTbl[5] = { };

static char wordStartE[] = "START!";

static char punctTbl[] = "!?";

static char wordStartJ[] = {
	0xBD, 0xC0, 0xB0, 0xC4, 0x21, 0x00
};

static char wordFinishJ[] = {
	0xCC, 0xA8, 0xC6, 0xAF, 0xBC, 0xAD, 0x21, 0x00
};

static char wordDrawJ[] = {
	0xCB, 0xB7, 0xDC, 0xB9, 0x21, 0x00
};

static char wordFinishE[] = "FINISH!";
static char wordDrawE[] = "DRAW!";

static char *wordMgTbl[6] = {
	wordStartJ, wordFinishJ, wordDrawJ,
	wordStartE, wordFinishE, wordDrawE,
};

static s16 seqMaxTime[8];
static SeqWork seqWorkData[8];

static s16 seqTimer;
static u8 seqDoneF;
u8 lbl_801D3D94;
static s16 seqSpeed;
static s16 seqPauseF;
static s32 seqRecordVal;
static s32 pauseWaitF;
static s32 pauseExitF;
static s32 pauseActiveF;
static Process *pauseProcess;
static s32 seqLanguage;

void fn_80036BC8(void);


void MGSeqInit(void)
{
	int i;
	SeqWork *work;
	work = &seqWorkData[0];
	for(i=8; i!=0; i--, work++) {
		work->seq_no = 0;
		work->data = NULL;
	}
	seqPauseF = 0;
	seqDoneF = 0;
	lbl_801D3D94 = 0;
	seqTimer = 30;
	HuAR_DVDtoARAM(MAKE_DIR_NUM(DATADIR_GAMEMES));
	HuAR_DVDtoARAM(MAKE_DIR_NUM(DATADIR_MGCONST));
	while(HuARDMACheck());
	fn_80036BC8();
	mgSeqInitF = -1;
	seqLanguage = GWLanguageGet();
}

void MGSeqMain(void)
{
	SeqInfo *info;
	s32 i;
	s32 j;
	s32 alive_flag;
	u8 stat;
	SeqWork *work;
	
	seqSpeed = HuSysVWaitGet(seqSpeed);
	if(Hu3DPauseF) {
		return;
	}
	alive_flag = 0;
	stat = 0;
	work = &seqWorkData[0];
	for(i=0; i<8; i++, work++) {
		if(work->stat == 0) {
			continue;
		}
		if(work->update) {
			alive_flag = work->update(work);
		} else {
			info = &seqInfoTbl[work->seq_no];
			if(work->seq_no != 0 && NULL != info->update) {
				alive_flag = info->update(work);
			}
		}
		if(!alive_flag) {
			work->stat = 0;
			if(!lbl_801D3D94) {
				for(j=0; j<8; j++) {
					if(seqWorkData[j].stat) {
						break;
					}
				}
			}
			if(!work->data) {
				HuMemDirectFree(work->data);
				work->data = NULL;
			}
		}
		stat |= work->stat;
	}
	if(!stat || stat & 0x4) {
		if(seqTimer > 0) {
			seqTimer -= seqSpeed;
		}
	}
}

static s16 CreateSeq(u8 seq_no, va_list params)
{
	SeqWork *work;
	SeqInfo *info;
	int i;
	int temp;
	work = seqWorkData;
	info = &seqInfoTbl[seq_no];
	for(i=0; i<8; i++, work++) {
		if(work->stat == 0) {
			break;
		}
	}
	if(i >= 8) {
		return -1;
	}
	work->stat |= 0x1;
	if(work->data) {
		HuMemDirectFree(work->data);
	}
	work->data = NULL;
	work->seq_no = (s32)seq_no;
	work->time = 0;
	work->x = info->x;
	work->y = info->y;
	work->scale_x = info->scale_x;
	work->scale_y = info->scale_y;
	work->unk_18 = 0.0f;
	work->unk_7D = 255;
	work->time_max = info->time_max;
	work->work_s16[0] = work->work_s16[1] = work->work_s16[2] = work->work_s16[3] = 0;
	work->work_float[0] = work->work_float[1] = 0.0f;
	work->param[0] = work->param[1] = 0;
	for(temp=0; temp<16; temp++) {
		work->sprite[temp] = work->sprite_grp[temp] = -1;
	}
	if(NULL != info->init) {
		temp = info->init(work, params);
		if(temp == 0) {
			work->stat = 0;
			return -1;
		} 
	}
	{
		seqTimer = 30;
		return i;
	}
}
