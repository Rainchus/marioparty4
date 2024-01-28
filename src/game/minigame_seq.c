#include "game/armem.h"
#include "game/sprite.h"
#include "game/process.h"
#include "game/gamework_data.h"
#include "game/objsub.h"
#include "game/hsfman.h"
#include "math.h"

#include "stdarg.h"

void MGSeqStub(void);

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
	s16 spr_grp[16];
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
		work->sprite[temp] = work->spr_grp[temp] = -1;
	}
	if(NULL != info->init) {
		temp = info->init(work, params);
		if(temp == 0) {
			work->stat = 0;
			return -1;
		} 
	}
	seqTimer = 30;
	return i;
}

s16 MGSeqCreate(s16 type, ...)
{
	s16 ret;
	va_list params;
	va_start(params, type);
	if(type == 3) {
		if(GWSystem.mg_next == 0xFFFF) {
			type = 8;
		} else {
			type = mgSeqTypeTbl[mgInfoTbl[GWSystem.mg_next].type];
		}
	}
	//FIXME: Fix truncation of type
	ret = CreateSeq(type, params);
	va_end(params);
	return ret;
}

u8 MGSeqStatGet(s16 id)
{
	SeqWork *work;
	u8 ret = 0;
	if(id < 0) {
		int i;
		work = seqWorkData;
		for(i=8; i != 0; i--, work++) {
			ret |= work->stat;
		}
	} else {
		if(id < 8) {
			ret = seqWorkData[id].stat;
		}
	}
	return ret;
}

void MGSeqPosSet(s16 id, float x, float y)
{
	if(id >= 0 && id < 8) {
		seqWorkData[id].x = x;
		seqWorkData[id].y = y;
	}
}

void MGSeqParamSet(s16 id, s16 param1, s16 param2)
{
	if(id >= 0 && id < 8) {
		seqWorkData[id].param[0] = param1;
		seqWorkData[id].param[1] = param2;
	}
}

void MGSeqKill(s16 id, s16 param1, s16 param2)
{
	if(id >= 0 && id < 8) {
		if(seqWorkData[id].stat != 0) {
			seqWorkData[id].stat = 8;
		}
	}
}

void MGSeqKillAll(s16 id, s16 param1, s16 param2)
{
	seqDoneF = 1;
	MGSeqMain();
	seqDoneF = 0;
	MGSeqStub();
	lbl_801D3D94 = 0;
}

s32 MGSeqDoneCheck(void)
{
	u8 stat = MGSeqStatGet(-1);
	if(stat == 0 || (stat & 0xC)) {
		if(seqTimer <= 0 || (stat & 0x8)) {
			return 1;
		}
	}
	return 0;
}

void MGSeqStub(void)
{
	
}

void MGSeqSprKill(SeqWork *work)
{
	int i;
	for(i=0; i<16; i++) {
		if(work->spr_grp[i] >= 0) {
			HuSprGrpKill(work->spr_grp[i]);
		}
		if(work->sprite[i] >= 0) {
			HuSprKill(work->sprite[i]);
		}
	}
}

static void *SeqReadFile(s32 file)
{
	return HuAR_ARAMtoMRAMFileRead(file, MEMORY_DEFAULT_NUM, HEAP_DATA);
}

static int SeqInitTimer(SeqWork *work, va_list params)
{
	AnimData *spr_anim;
	s16 sprite;
	s16 spr_grp;
	int duration, x, y;
	s16 i;
	
	duration = va_arg(params, int);
	x = va_arg(params, int);
	y = va_arg(params, int);
	if(duration <= 0 && duration > 99) {
		duration = 99;
	}
	work->work_s16[0] = duration;
	if(x >= 0) {
		work->x = x;
	}
	if(y >= 0) {
		work->y = y;
	}
	work->work_s16[2] = 0;
	work->work_s16[1] = 2;
	work->work_float[0] = 0;
	work->spr_grp[0] = spr_grp = HuSprGrpCreate(4);
	HuSprGrpScaleSet(spr_grp, work->scale_x, work->scale_y);
	spr_anim = HuSprAnimRead(SeqReadFile(MAKE_DATA_NUM(DATADIR_GAMEMES, 2)));
	x = 12;
	for(i=0; i<2; i++) {
		sprite = HuSprCreate(spr_anim, 5, 0);
		HuSprGrpMemberSet(spr_grp, i, sprite);
		HuSprSpeedSet(spr_grp, i, 0);
		HuSprPosSet(spr_grp, i, x, 0);
		HuSprColorSet(spr_grp, i, 112, 233, 255);
		x -= 24;
		(void)i; //Hack for Matching
	}
	spr_anim = HuSprAnimRead(SeqReadFile(MAKE_DATA_NUM(DATADIR_GAMEMES, 1)));
	sprite = HuSprCreate(spr_anim, 7, 0);
	HuSprGrpMemberSet(spr_grp, 2, sprite);
	HuSprPosSet(spr_grp, 2, 0, 0);
	HuSprTPLvlSet(spr_grp, 2, 0.5f);
	HuSprColorSet(spr_grp, 2, 0, 0, 0);
	spr_anim = HuSprAnimRead(SeqReadFile(MAKE_DATA_NUM(DATADIR_GAMEMES, 0)));
	sprite = HuSprCreate(spr_anim, 6, 0);
	HuSprGrpMemberSet(spr_grp, 3, sprite);
	HuSprPosSet(spr_grp, 3, 0, 0);
	if(seqPauseF) {
		work->work_s16[1] = 1;
		for(i=0; i<2; i++) {
			HuSprAttrSet(spr_grp, i, SPRITE_ATTR_HIDDEN);
			(void)i; //Hack for Matching
		}		
	}
	return 1;
}

static int SeqUpdateTimer(SeqWork *work)
{
	float scale;
	float tp_lvl;
	u8 digits[2];
	s16 i;
	s16 spr_grp = work->spr_grp[0];
	if(work->param[0] != 0 && work->work_s16[1] != -1) {
		switch(work->param[0]) {
			case 2:
				switch(work->param[1]) {
					case -1:
						work->stat |= 0x4;
						work->work_s16[1] = -1;
						work->work_float[0] = 0.0f;
						break;
						
					case 0:
						work->work_s16[1] = 2;
						work->work_float[0] = 0.0f;
						break;
						
					case 1:
						work->work_s16[1] = 3;
						work->work_float[0] = 0.0f;
						break;
						
					default:
						break;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				if(work->param[1] < 0 && !(work->stat & 0x4)) {
					work->stat |= 0x4;
					work->work_s16[1] = -1;
					work->work_float[0] = 0.0f;
				} else {
					if(work->param[1] > 99) {
						work->work_s16[0] = 99;
					} else {
						if(work->work_s16[0] != work->param[1]) {
							work->work_s16[0] = work->param[1];
							if(work->param[1] <= 5) {
								HuAudFXPlay(6);
								work->work_s16[1] = 3;
								work->work_float[0] = 0.0f;
								HuSprColorSet(spr_grp, 0, 255, 112, 160);
								HuSprColorSet(spr_grp, 1, 255, 112, 160);
							} else {
								HuSprColorSet(spr_grp, 0, 112, 233, 255);
								HuSprColorSet(spr_grp, 1, 112, 233, 255);
							}
						}
					}
				}
				work->param[0] = 0;
				break;
				
			case 3:
				for(i=0; i<2; i++) {
					HuSprAttrReset(spr_grp, i, SPRITE_ATTR_HIDDEN);
				}
				work->work_s16[1] = 3;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->work_s16[1] == 1) {
		return 1;
	}
	if(work->work_s16[0] > 99) {
		digits[0] = digits[1] = 9;
	} else {
		s32 value;
		value = work->work_s16[0]/10;
		digits[1] = value;
		digits[0] = work->work_s16[0]-(value*10);
	}
	HuSprGrpPosSet(spr_grp, work->x, work->y);
	HuSprGrpScaleSet(spr_grp, work->scale_x, work->scale_y);
	for(i=0; i<2; i++) {
		HuSprBankSet(spr_grp, i, digits[i]);
	}
	if(work->work_s16[1] != 0) {
		switch(work->work_s16[1]) {
			case 2:
			{
				float scale_x, scale_y;
				scale = fabs(((sin((work->work_float[0]*M_PI)/180)*5.0f)+1.0f)-(sin((130*M_PI)/180)*5.0f));
				scale_x = work->scale_x*scale;
				scale_y = work->scale_y*scale;
				work->work_float[0] += seqSpeed*5.0f;
				if(work->work_float[0] > 130.0f) {
					work->work_s16[1] = 0;
					break;
				}
				HuSprGrpScaleSet(spr_grp, scale_x, scale_y);
			}
				break;
				
			case 3:
			{
				scale = sin((work->work_float[0]*M_PI)/180)+1.0;
				tp_lvl = 1.0-(sin((work->work_float[0]*M_PI)/180)*0.5);
				work->work_float[0] += seqSpeed*18.0f;
				if(work->work_float[0] > 180.0f) {
					work->work_s16[1] = 0;
					scale = 1.0f;
					tp_lvl = 1.0f;
				}
				for(i=0; i<2; i++) {
					HuSprScaleSet(spr_grp, i, scale, scale);
					HuSprTPLvlSet(spr_grp, i, tp_lvl);
				}
			}
				break;
				
			case -1:
				HuSprGrpScaleSet(spr_grp, work->scale_x, work->scale_y);
				for(i=0; i<2; i++) {
					HuSprScaleSet(spr_grp, i, 1.0f, 1.0f);
				}
				work->work_float[0] += 1.0f;
				if(work->work_float[0] < 60.0f) {
					break;
				}
				tp_lvl = 1.0-((work->work_float[0]-60.0f)/20.0f);
				if(tp_lvl <= 0.0f) {
					tp_lvl = 0.0f;
					work->work_s16[1] = 0;
					work->stat |= 0x8;
				}
				
				for(i=0; i<4; i++) {
					HuSprTPLvlSet(spr_grp, i, tp_lvl);
				}
				break;
				
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	} else {
		return 1;
	}
}

static int SeqInitType2(SeqWork *work, va_list params)
{
	s16 spr_idx;
	s16 spr_grp;
	AnimData *anim_tbl[6];
	s32 i;
	s16 len;
	char *str;
	char c;
	int time_max;
	int x, y;
	work->data = va_arg(params, void *);
	time_max = va_arg(params, int);
	x = va_arg(params, int);
	y = va_arg(params, int);
	if(time_max < 0) {
		time_max = -1;
	}
	work->time_max = time_max;
	if(x >= 0) {
		work->x = x;
	}
	if(y >= 0) {
		work->y = y;
	}
	work->work_s16[1] = 0;
	work->work_float[0] = 0.0f;
	x = 0;
	len = 0;
	str=work->data;
	while(c=*str++) {
		if(c >= '0' && c <= '9') {
			x |= 1;
			len++;
		} else if(c >= 'A' && c <= 'Z') {
			x |= 2;
			len++;
		} else if(c >= 'a' && c <= 'z') {
			x |= 4;
			len++;
		} else if(c == '!' || c == '?') {
			x |= 8;
			len++;
		}
	}
	work->work_s16[3] = len;
	for(i=0; i<6; i++) {
		if(x & (1 << i)) {
			anim_tbl[i] = HuSprAnimRead(SeqReadFile(seqType2SprTbl[i]));
		} else {
			anim_tbl[i] = NULL;
		}
	}
	work->spr_grp[0] = spr_grp = HuSprGrpCreate(len);
	x = 0;
	spr_idx = 0;
	str=work->data;
	while(c=*str++) {
		i = -2;
		if(c >= '0' && c <= '9') {
			c -= '0';
			i = 0;
		} else if(c >= 'A' && c <= 'Z') {
			c -= 'A';
			i = 1;
		} else if(c >= 'a' && c <= 'z') {
			c -= 'a';
			i = 2;
		} else if(c == '!' || c == '?') {
			if(c == '!') {
				c = 0;
			} else {
				c = 1;
			}
			i = 3;
		} else if(c == ' ') {
			i = -1;
		}
		work->work_s16[2] = x;
		if(i == -1) {
			x += 32;
		} else if(i >= 0) {
			s16 sprite = HuSprCreate(anim_tbl[i], 5, c);
			HuSprGrpMemberSet(spr_grp, spr_idx, sprite);
			HuSprSpeedSet(spr_grp, spr_idx, 0.0f);
			HuSprPosSet(spr_grp, spr_idx, x, 0.0f);
			spr_idx++;
			x += 64;
		}
	}
	if(seqPauseF) {
		work->work_s16[1] = 1;
		for(i=0; i<work->work_s16[3]; i++) {
			HuSprAttrSet(spr_grp, i, SPRITE_ATTR_HIDDEN);
		}
	}
	return 1;
}

static int SeqUpdateType2(SeqWork *work)
{
	float tp_lvl;
	s16 spr_grp;
	spr_grp = work->spr_grp[0];
	HuSprGrpPosSet(spr_grp, work->x-((0.5f*work->scale_x)*work->work_s16[2]), work->y);
	HuSprGrpScaleSet(spr_grp, work->scale_x, work->scale_y);
	if(work->param[0] != 0 && work->work_s16[1] != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->work_s16[1] = -1;
					work->work_float[0] = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
			{
				s32 i;
				for(i=0; i<work->work_s16[3]; i++) {
					HuSprAttrReset(spr_grp, i, SPRITE_ATTR_HIDDEN);
					(void)i;
				}
				work->work_s16[1] = 0;
				work->param[0] = 0;
			}
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->work_s16[1] == 1) {
		return 1;
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->work_s16[1] != -1) {
		work->stat |= 0x4;
		work->work_s16[1] = -1;
		work->work_float[0] = 0.0f;
	}
	if(work->work_s16[1] != 0) {
		if(work->work_s16[1] != -1) {
			(void)work; //HACK: to introduce extra branch
		} else {
			s16 i;
			work->work_float[0] += seqSpeed*0.1f;
			tp_lvl = 1.0f-work->work_float[0];
			if(tp_lvl <= 0.0f) {
				tp_lvl = 0.0f;
				work->work_s16[1] = 0;
				work->stat |= 0x8;
			}
			for(i=0; i<work->work_s16[3]; i++) {
				HuSprTPLvlSet(spr_grp, i, tp_lvl);
				(void)i;
			}
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	} else {
		return 1;
	}
}


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

static char seqPunctTbl[] = "!?";

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

void fn_80036BC8(void)
{
	if(!letterBufTbl[0]) {
		letterBufTbl[0] = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(s32)*strlen(seqFontAlphaTbl));
		memset(letterBufTbl[0], 0, sizeof(s32)*strlen(seqFontAlphaTbl));
	}
	if(!letterBufTbl[1]) {
		letterBufTbl[1] = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(s32)*strlen(seqFontKanaTbl));
		memset(letterBufTbl[1], 0, sizeof(s32)*strlen(seqFontKanaTbl));
	}
	if(!letterBufTbl[2]) {
		letterBufTbl[2] = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(s32)*strlen(seqFontKanaTbl));
		memset(letterBufTbl[2], 0, sizeof(s32)*strlen(seqFontKanaTbl));
	}
	if(!letterBufTbl[3]) {
		letterBufTbl[3] = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(s32)*strlen(seqFontNumTbl));
		memset(letterBufTbl[3], 0, sizeof(s32)*strlen(seqFontNumTbl));
	}
	if(!letterBufTbl[4]) {
		letterBufTbl[4] = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(s32)*strlen(seqPunctTbl));
		memset(letterBufTbl[4], 0, sizeof(s32)*strlen(seqPunctTbl));
	}
}

static AnimData *SeqLoadFontChar(char *str, s16 flags);

static s32 SeqMakeWord(SeqWork *work, char *str, s16 flags)
{
	s16 *char_pos;
	char *str_ptr;
	s16 spr_grp;
	s16 i;
	s16 x;
	s16 grp_idx;
	s16 len;
	AnimData **char_anim;
	for(grp_idx=0; grp_idx<16; grp_idx++) {
		if(work->spr_grp[grp_idx] == -1) {
			break;
		}
	}
	if(grp_idx == 16) {
		return -1;
	}
	char_anim = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(AnimData *)*100);
	char_pos = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(s16)*100);
	str_ptr = str;
	x = 0;
	len = 0;
	while(*str_ptr != 0) {
		char_anim[len] = SeqLoadFontChar(str_ptr, flags);
		if(char_anim[len]) {
			char_pos[len] = x;
			x += 56;
			len++;
		}
		str_ptr++;
	}
	work->spr_grp[grp_idx] = spr_grp = HuSprGrpCreate(len);
	x = (x/2)-28;
	for(i=0; i<len; i++) {
		s16 sprite = HuSprCreate(char_anim[i], 5, 0);
		HuSprGrpMemberSet(spr_grp, i, sprite);
		HuSprPosSet(spr_grp, i, char_pos[i]-x, 0.0f);
	}
	work->work_s16[3] = len;
	HuMemDirectFree(char_anim);
	HuMemDirectFree(char_pos);
	return grp_idx;
}

static AnimData *SeqLoadFontChar(char *str, s16 flags)
{
	s32 data_num;
	s16 id;
	char *list;
	char c = *str;
	if(c == 222 || c == 223) {
		return NULL;
	}
	if(c == 32) {
		return HuSprAnimRead(SeqReadFile(MAKE_DATA_NUM(DATADIR_GAMEMES, 10)));
	}
	for(id = 0, list=seqFontAlphaTbl; *list != 0; id++, list++) {
		if(*list == c) {
			data_num = MAKE_DATA_NUM(DATADIR_GAMEMES, id+21);
			return HuSprAnimRead(SeqReadFile(data_num));
		}
	}
	for(id = 0, list=seqFontNumTbl; *list != 0; id++, list++) {
		if(*list == c) {
			data_num = MAKE_DATA_NUM(DATADIR_GAMEMES, id+11);
			return HuSprAnimRead(SeqReadFile(data_num));
		}
	}
	for(id = 0, list=seqPunctTbl; *list != 0; id++, list++) {
		if(*list == c) {
			data_num = MAKE_DATA_NUM(DATADIR_GAMEMES, id+154);
			return HuSprAnimRead(SeqReadFile(data_num));
		}
	}
	if(str[1] == 222) {
		list = seqFontKanaTbl;
		list += 55;
		id = 55;
	} else if(str[1] == 223) {
		list = seqFontKanaTbl;
		list += 75;
		id = 75;
	} else {
		list = seqFontKanaTbl;
		id = 0;
	}
	while(*list != 0) {
		if(*list == c) {
			if(flags & 0x1) {
				data_num = MAKE_DATA_NUM(DATADIR_GAMEMES, id+156);
			} else {
				data_num = MAKE_DATA_NUM(DATADIR_GAMEMES, id+73);
			}
			return HuSprAnimRead(SeqReadFile(data_num));
		}
		id++;
		list++;
	}
	return NULL;
}