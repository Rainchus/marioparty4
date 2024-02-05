#include "game/armem.h"
#include "game/sprite.h"
#include "game/process.h"
#include "game/gamework_data.h"
#include "game/objsub.h"
#include "game/object.h"
#include "game/hsfman.h"
#include "math.h"

#include "stdarg.h"

#define ABS(x) (((x) < 0) ? -(x) : (x))

void MGSeqStub(void);

void MGSeqPauseEnableCtrl(s32 flag);

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
	HuAR_DVDtoARAM(DATADIR_GAMEMES);
	HuAR_DVDtoARAM(DATADIR_MGCONST);
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

static s16 CreateSeq(s16 seq_no, va_list params)
{
	SeqWork *work;
	SeqInfo *info;
	int i;
	int temp;
	work = seqWorkData;
	info = &seqInfoTbl[(u8)seq_no];
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
	work->seq_no = (u8)seq_no;
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
	spr_anim = HuSprAnimRead(SeqReadFile(DATA_MAKE_NUM(DATADIR_GAMEMES, 2)));
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
	spr_anim = HuSprAnimRead(SeqReadFile(DATA_MAKE_NUM(DATADIR_GAMEMES, 1)));
	sprite = HuSprCreate(spr_anim, 7, 0);
	HuSprGrpMemberSet(spr_grp, 2, sprite);
	HuSprPosSet(spr_grp, 2, 0, 0);
	HuSprTPLvlSet(spr_grp, 2, 0.5f);
	HuSprColorSet(spr_grp, 2, 0, 0, 0);
	spr_anim = HuSprAnimRead(SeqReadFile(DATA_MAKE_NUM(DATADIR_GAMEMES, 0)));
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


static char seqFontAlphaTbl[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '\0'
};

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

static char seqFontNumTbl[] = {
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', '\0'
};

static s32 *letterBufTbl[5] = { };

static char wordStartE[] = "START!";

static char seqPunctTbl[] = {
	'!', '?', '\0'
};

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
		return HuSprAnimRead(SeqReadFile(DATA_MAKE_NUM(DATADIR_GAMEMES, 10)));
	}
	for(id = 0, list=seqFontAlphaTbl; *list != 0; id++, list++) {
		if(*list == c) {
			data_num = DATA_MAKE_NUM(DATADIR_GAMEMES, id+21);
			return HuSprAnimRead(SeqReadFile(data_num));
		}
	}
	for(id = 0, list=seqFontNumTbl; *list != 0; id++, list++) {
		if(*list == c) {
			data_num = DATA_MAKE_NUM(DATADIR_GAMEMES, id+11);
			return HuSprAnimRead(SeqReadFile(data_num));
		}
	}
	for(id = 0, list=seqPunctTbl; *list != 0; id++, list++) {
		if(*list == c) {
			data_num = DATA_MAKE_NUM(DATADIR_GAMEMES, id+154);
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
				data_num = DATA_MAKE_NUM(DATADIR_GAMEMES, id+156);
			} else {
				data_num = DATA_MAKE_NUM(DATADIR_GAMEMES, id+73);
			}
			return HuSprAnimRead(SeqReadFile(data_num));
		}
		id++;
		list++;
	}
	return NULL;
}

static float ForceDefine480()
{
	return 480.0f;
}

static void SeqPlayStartFX(void);

static int SeqInitMGBasic(SeqWork *work, va_list params)
{
	s16 i;
	s16 word_grp;
	
	work->work_s16[1] = va_arg(params, int);
	if(work->work_s16[1] == 2) {
		return SeqInitDraw(work, params);
	}
	work->type = 0;
	work->work_float[0] = 0;
	
	{
		s32 word_katakana;
		s32 word_flag;
		s32 word_ofs;
		word_katakana = 0;
		if(work->work_s16[1] == 2 && seqLanguage == 0) {
			word_katakana = 1;
		}
		if(word_katakana) {
			word_flag = 1;
		} else {
			word_flag = 0;
		}
		if(seqLanguage == 0) {
			word_ofs = 0;
		} else {
			word_ofs = 3;
		}
		word_grp = SeqMakeWord(work, wordMgTbl[work->work_s16[1]+word_ofs], word_flag);
	}
	HuSprGrpPosSet(work->spr_grp[word_grp], 0.0f, 0.0f);
	
	for(i=0; i<work->work_s16[3]; i++) {
		HuSprTPLvlSet(work->spr_grp[word_grp], i, 1.0f);
		HuSprPosSet(work->spr_grp[word_grp], i, -100.0f, 240.0f);
	}
	if(seqPauseF) {
		work->type = 2;
		HuSprAttrSet(word_grp, 0, SPRITE_ATTR_HIDDEN);
	} else {
		work->param[0] = 3;
	}
	return 1;
}

static int SeqUpdateMGBasic(SeqWork *work)
{
	s16 idx;
	float scale;
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->work_float[0] = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->type == 2) {
		return 1;
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->type = -1;
		work->work_float[0] = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				float pos_x;
				float time;
				s16 i;
				if(work->work_s16[1] == 0) {
					if(work->time <= 40) {
						for(i=0; i<work->work_s16[3]; i++) {
							time = work->time-((20/work->work_s16[3])*(work->work_s16[3]-i-1));
							if(time < 0 || time > 20.0f) {
								continue;
							}
							pos_x = (work->x-(0.5f*(work->work_s16[3]*56)))+28.0f+(i*56);
							if(time == 20.0f) {
								HuSprPosSet(work->spr_grp[0], i, pos_x, work->y);
								HuSprZRotSet(work->spr_grp[0], i, 0.0f);
							} else {
								HuSprPosSet(work->spr_grp[0], i, pos_x-(((1.0-sin(((time*4.5f)*M_PI)/180.0))*(work->work_s16[3]*56*2))), work->y);
								HuSprZRotSet(work->spr_grp[0], i, (time/20.0f)*390.0f);
							}
						}
					} else {
						time = work->time-40;
						scale = work->scale_x+(0.5*sin(((time*9.0f)*M_PI)/180.0));
						for(i=0; i<work->work_s16[3]; i++) {
							pos_x = ((28.0f*scale)+(work->x-(0.5f*(scale*(work->work_s16[3]*56)))))+(scale*(i*56));
							HuSprPosSet(work->spr_grp[0], i, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[0], i, scale, work->scale_y+sin(((time*9.0f)*M_PI)/180.0));
						}
					}
					if(work->time == 40) {
						idx = HuAudFXPlay(36);
						work->stat |= 0x10;
					}
					if(work->time == 60) {
						SeqPlayStartFX();
						work->stat |= 0x4;
					}
					if(work->time >= 60) {
						work->type = 0;
					}
				} else {
					if(work->time == 1) {
						if(work->work_s16[1] == 1) {
							HuAudFXPlay(37);
						} else {
							HuAudFXPlay(40);
						}
						MGSeqPauseEnableCtrl(0);
						work->stat |= 0x10;
					}
					if(work->time <= 20) {
						time = work->time;
						scale = work->scale_x+(0.5*sin(((time*9.0f)*M_PI)/180.0));
						for(i=0; i<work->work_s16[3]; i++) {
							HuSprAttrReset(work->spr_grp[0], i, SPRITE_ATTR_HIDDEN);
							pos_x = ((28.0f*scale)+(work->x-(0.5f*(scale*(work->work_s16[3]*56)))))+(scale*(i*56));
							HuSprPosSet(work->spr_grp[0], i, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[0], i, work->scale_x+sin(((time*9.0f)*M_PI)/180.0), work->scale_y+sin(((time*9.0f)*M_PI)/180.0));
						}
						if(time == 20.0f) {
							for(i=0; i<work->work_s16[3]; i++) {
								HuSprAttrReset(work->spr_grp[0], i, SPRITE_ATTR_HIDDEN);
							}
						}
					} else {
						if(work->time > 80) {
							for(i=0; i<work->work_s16[3]; i++) {
								time = (work->time-80)-((20/work->work_s16[3])*(work->work_s16[3]-i-1));
								if(time < 0.0f || time > 20.0f) {
									continue;
								}
								pos_x = (28.0f+(work->x-(0.5f*(work->work_s16[3]*56))))+(i*56);
								if(time == 20.0f) {
									HuSprAttrSet(work->spr_grp[0], i, SPRITE_ATTR_HIDDEN);
								} else {
									HuSprPosSet(work->spr_grp[0], i, pos_x+((1.0-cos(((time*4.5f)*M_PI)/180.0f))*(work->work_s16[3]*56*2)), work->y);
									HuSprZRotSet(work->spr_grp[0], i, (time/20.0f)*390.0f);
								}
							}
						}
					}
					if(work->time == 110) {
						work->stat |= 0x4;
					}
					if(work->time >= 110) {
						work->type = 0;
						work->stat |= 8;
					}
				}
			}
				break;
				
			case -1:
			{
				work->work_float[0] += seqSpeed*0.1f;
				scale = 1.0f-work->work_float[0];
				if(scale <= 0.0f) {
					scale = 0.0f;
					work->type = 0;
					work->stat |= 0x8;
					if(work->work_s16[1] == 0) {
						MGSeqPauseEnableCtrl(1);
					}
				}
				for(idx=0; idx<work->work_s16[3]; idx++) {
					HuSprTPLvlSet(work->spr_grp[0], idx, scale);
				}
			}
				break;
				
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static int SeqInitMGCommon(SeqWork *work, va_list params)
{
	s16 i;
	float tp_lvl;
	s16 j;
	s16 word_grp;
	
	work->work_s16[1] = va_arg(params, int);
	if(work->work_s16[1] == 2) {
		return SeqInitDraw(work, params);
	}
	work->type = 0;
	work->work_float[0] = 0;
	tp_lvl = 1.0f;
	for(i=0; i<4; i++) {
		if(i == 0)
		{
			s32 word_katakana;
			s32 word_flag;
			s32 word_ofs;
			word_katakana = 0;
			if(work->work_s16[1] == 2 && seqLanguage == 0) {
				word_katakana = 1;
			}
			if(word_katakana) {
				word_flag = 1;
			} else {
				word_flag = 0;
			}
			if(seqLanguage == 0) {
				word_ofs = 0;
			} else {
				word_ofs = 3;
			}
			word_grp = SeqMakeWord(work, wordMgTbl[work->work_s16[1]+word_ofs], word_flag);
		} else {
			s16 grp_idx;
			s32 new_grp;
			for(grp_idx=0; grp_idx<16; grp_idx++) {
				if(work->spr_grp[grp_idx] == -1) {
					break;
				}
			}
			if(grp_idx == 16) {
				new_grp = -1;
			} else {
				work->spr_grp[grp_idx] = HuSprGrpCopy(work->spr_grp[word_grp]);
				new_grp = grp_idx;
			}
			(void)new_grp;
			word_grp = new_grp;
		}
		HuSprGrpPosSet(work->spr_grp[word_grp], 0.0f, 0.0f);
		for(j=0; j<work->work_s16[3]; j++) {
			HuSprTPLvlSet(work->spr_grp[word_grp], j, tp_lvl);
			HuSprPosSet(work->spr_grp[word_grp], j, -100.0f, 240.0f);
			HuSprPriSet(work->spr_grp[word_grp], j, i+5);
			HuSprAttrSet(work->spr_grp[word_grp], i, SPRITE_ATTR_BILINEAR);
		}
		if(i == 0) {
			tp_lvl -= 0.5;
		} else {
			tp_lvl -= 0.1f;
		}
	}
	if(seqPauseF) {
		work->type = 2;
		HuSprAttrSet(word_grp, 0, SPRITE_ATTR_HIDDEN);
	} else {
		work->param[0] = 3;
	}
	return 1;
}

static int SeqUpdateMGBattle(SeqWork *work)
{
	s16 idx;
	float scale;
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->work_float[0] = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->type == 2) {
		return 1;
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->stat |= 0x4;
		work->type = -1;
		work->work_float[0] = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				s16 i, j;
				float time;
				float pos_x;
				if(work->work_s16[1] == 0) {
					if(work->time < 45) {
						if(work->time > 10 && work->time <= 40) {
							time = work->time-10;
							scale = 10.0f*(1.0f-(time/30.0f));
							pos_x = (work->x-(0.5f*(work->work_s16[3]*56)))+28.0f;
							HuSprPosSet(work->spr_grp[0], 0, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[0], 0, work->scale_x+scale, work->scale_y+scale);
							scale = time/30.0f;
							HuSprTPLvlSet(work->spr_grp[0], 0, scale);
						}
						for(i=0; i<4; i++) {
							time = work->time-i;
							if(time < 0 || time > 40) {
								continue;
							}
							for(j=1; j<work->work_s16[3]; j++) {
								pos_x = (28.0f+(work->x-(0.5f*(work->work_s16[3]*56))))+(j*56);
								if(time == 40.0f) {
									HuSprPosSet(work->spr_grp[i], j, pos_x, work->y);
									HuSprZRotSet(work->spr_grp[i], j, 0.0f);
									HuSprScaleSet(work->spr_grp[i], j, work->scale_x, work->scale_y);
									if(i != 0) {
										HuSprAttrSet(work->spr_grp[i], j, SPRITE_ATTR_HIDDEN);
									}
								} else {
									s16 discard_cnt;
									static float letterOfs[] = {
										30, 20,
										20, 3,
										-4, 20,
										-30, 20,
										20, 20,
										-30, 20,
										-10, 40,
										10, -40
									};
									float x, y;
									float ofs_x, ofs_y;
									float zrot, scale_ang;
									x = pos_x;
									y = work->y;
									ofs_x = letterOfs[((j-1)&0x7)*2];
									ofs_y = letterOfs[(((j-1)&0x7)*2)+1];
									zrot = 0.0f;
									discard_cnt = 0;
									scale_ang = 0.0f;
									for(idx=0; idx<40.0f-time; idx++) {
										if(x+ofs_x > 576 || x+ofs_x < 0) {
											ofs_x = -ofs_x;
											discard_cnt++;
										}
										if(y+ofs_y > 480 || y+ofs_y < 0) {
											ofs_y = -ofs_y;
											discard_cnt++;
										}
										if(discard_cnt) {
											zrot += 20.0f;
											scale_ang = 0.0f;
										}
										x += ofs_x;
										y += ofs_y;
									}
									HuSprPosSet(work->spr_grp[i], j, x, y);
									HuSprScaleSet(work->spr_grp[i], j, work->scale_x*cos((M_PI*scale_ang)/180.0), work->scale_y);
									HuSprZRotSet(work->spr_grp[i], j, zrot);
								}
							}
						}
					} else {
						if(work->time > 60) {
							time = work->time-60;
							scale = 0.5*sin((M_PI*(time*9.0f))/180.0);
							for(j=0; j<work->work_s16[3]; j++) {
								pos_x = (28.0f*(scale+work->scale_x))+(work->x-(0.5f*((work->work_s16[3]*56)*(scale+work->scale_x))))+((j*56)*(scale+work->scale_x));
								HuSprPosSet(work->spr_grp[0], j, pos_x, work->y);
								HuSprScaleSet(work->spr_grp[0], j, work->scale_x+scale, work->scale_y+scale);
							}
						}
					}
					if(work->time == 60) {
						HuAudFXPlay(36);
						work->stat |= 0x10;
					}
					if(work->time == 80) {
						work->stat |= 0x4;
						SeqPlayStartFX();
					}
					if(work->time >= 80) {
						work->type = 0;
					}
				} else {
					if(work->time == 1) {
						if(work->work_s16[1] == 1) {
							HuAudFXPlay(37);
						} else {
							HuAudFXPlay(40);
						}
						MGSeqPauseEnableCtrl(0);
						work->stat |= 0x10;
					}
					if(work->time <= 20) {
						for(i=1; i<4; i++) {
							for(j=0; j<work->work_s16[3]; j++) {
								HuSprAttrSet(work->spr_grp[i], j, SPRITE_ATTR_HIDDEN);
							}
						}
						time = work->time;
						scale = work->scale_x+(0.5*sin((M_PI*(time*9.0f))/180.0));
						for(j=0; j<work->work_s16[3]; j++) {
							HuSprAttrReset(work->spr_grp[0], j, SPRITE_ATTR_HIDDEN);
							pos_x = ((28.0f*scale)+(work->x-(0.5f*(scale*(work->work_s16[3]*56)))))+(scale*(j*56));
							HuSprPosSet(work->spr_grp[0], j, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[0], j, work->scale_x+(sin((M_PI*(time*9.0f))/180.0)), work->scale_y+(sin((M_PI*(time*9.0f))/180.0)));
						}
						if(time == 20.0f) {
							for(j=0; j<work->work_s16[3]; j++) {
								HuSprAttrReset(work->spr_grp[0], j, SPRITE_ATTR_HIDDEN);
							}
						}
					} else {
						if(work->time > 80 && work->time <= 95) {
							time = work->time-80;
							for(j=0; j<work->work_s16[3]; j++) {
								pos_x = (28.0f+(work->x-(0.5f*(work->work_s16[3]*56))))+(j*56);
								HuSprPosSet(work->spr_grp[0], j, pos_x+((288.0f-pos_x)*(1.0-cos((M_PI*(time*6.0))/180.0))), work->y);
							}
							if(time == 15.0f) {
								for(j=0; j<work->work_s16[3]; j++) {
									HuSprAttrReset(work->spr_grp[1], j, SPRITE_ATTR_HIDDEN);
									HuSprPosSet(work->spr_grp[1], j, 288.0f, work->y);
									HuSprTPLvlSet(work->spr_grp[1], j, 1.0f);
								}
							}
						} else {
							if(work->time > 105) {
								for(j=0; j<work->work_s16[3]; j++) {
									time = work->time-105;
									time -= j*3;
									if(time < 0) {
										continue;
									}
									scale = 1.0f-(time/15.0f);
									if(scale < 0.0f) {
										scale = 0.0f;
									}
									HuSprPosSet(work->spr_grp[0], j, 288.0f, work->y+((-100.0f-work->y)*(time/20.0f)));
									HuSprTPLvlSet(work->spr_grp[0], j, scale);
									HuSprPosSet(work->spr_grp[1], j, 288.0f, work->y+((580.0f-work->y)*(time/20.0f)));
									HuSprTPLvlSet(work->spr_grp[1], j, scale);
								}
							}
						}
					}
					if(work->time == 130) {
						work->stat |= 0x4;
					}
					if(work->time >= 130) {
						work->type = 0;
						work->stat |= 0x8;
					}
				}
				
			}
				break;
				
			case -1:
			{
				work->work_float[0] += seqSpeed*0.1f;
				scale = 1.0f-work->work_float[0];
				if(scale <= 0.0f) {
					scale = 0.0f;
					work->type = 0;
					work->stat |= 0x8;
					if(work->work_s16[1] == 0) {
						MGSeqPauseEnableCtrl(1);
					}
				}
				for(idx=0; idx<work->work_s16[3]; idx++) {
					HuSprTPLvlSet(work->spr_grp[0], idx, scale);
				}
			}
				break;
				
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static int SeqUpdateMG1vs3(SeqWork *work)
{
	s16 idx;
	float scale;
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->work_float[0] = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->type == 2) {
		return 1;
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->stat |= 0x4;
		work->type = -1;
		work->work_float[0] = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				float time;
				float scale_x, scale_y;
				float pos_x, pos_y;
				s16 i;
				s16 j;
				if(work->work_s16[1] == 0) {
					if(work->time <= 10) {
						scale = work->time/10.0f;
						time = work->time;
						for(idx=0; idx<work->work_s16[3]; idx++) {
							scale_x = 0.3*work->scale_x;
							scale_y = 0.3*work->scale_y;
							pos_x = ((28.0f*scale_x)+(work->x-(0.5f*(scale_x*(work->work_s16[3]*56)))))+(scale_x*(idx*56));
							pos_y = work->y-(150.0*sin((M_PI*(((16.0f/3.0f)*time)+20.0f))/180.0));
							HuSprPosSet(work->spr_grp[0], idx, pos_x, pos_y);
							HuSprScaleSet(work->spr_grp[0], idx, scale_x, scale_y*cos(M_PI*(12.0f*time)/180.0));
							HuSprTPLvlSet(work->spr_grp[0], idx, scale);
						}
					} else {
						if(work->time <= 60) {
							for(i=0; i<4; i++) {
								for(idx=0; idx<work->work_s16[3]; idx++) {
									time = (work->time-10)-(idx*3)-i;
									if(time < 0.0f) {
										time = 0.0f;
									} else {
										if(time > 30.0f) {
											continue;
										}
									}
									scale = 0.3+(0.7*(1.0-cos((M_PI*(time*3.0f))/180.0)));
									scale_x = work->scale_x*scale;
									scale_y = work->scale_y*scale;
									pos_x = ((28.0f*scale_x)+(work->x-(0.5f*(scale_x*(work->work_s16[3]*56)))))+(scale_x*(idx*56));
									pos_y = work->y-(150.0*sin((M_PI*(((16.0f/3.0f)*time)+20.0f))/180.0));
									HuSprPosSet(work->spr_grp[i], idx, pos_x, pos_y);
									HuSprScaleSet(work->spr_grp[i], idx, scale_x, scale_y*cos(M_PI*(12.0f*time)/180.0));
								}
							}
							if(work->time == 60) {
								for(i=1; i<4; i++) {
									for(j=0; j<work->work_s16[3]; j++) {
										HuSprAttrSet(work->spr_grp[i], j, SPRITE_ATTR_HIDDEN);
									}
								}
							}
						} else {
							if(work->time > 70) {
								time = work->time-70;
								scale = 0.5*sin((M_PI*(time*9.0f))/180.0);
								for(j=0; j<work->work_s16[3]; j++) {
									pos_x = (28.0f*(scale+work->scale_x))+(work->x-(0.5f*((work->work_s16[3]*56)*(scale+work->scale_x))))+((j*56)*(scale+work->scale_x));
									HuSprPosSet(work->spr_grp[0], j, pos_x, work->y);
									HuSprScaleSet(work->spr_grp[0], j, work->scale_x+scale, work->scale_y+scale);
								}
							}
						}
					}
					if(work->time == 70) {
						HuAudFXPlay(36);
						work->stat |= 0x10;
					}
					if(work->time == 90) {
						work->stat |= 0x4;
						SeqPlayStartFX();
					}
					if(work->time >= 90) {
						work->type = 0;
					}
				} else {
					if(work->time == 1) {
						if(work->work_s16[1] == 1) {
							HuAudFXPlay(37);
						} else {
							HuAudFXPlay(40);
						}
						MGSeqPauseEnableCtrl(0);
						work->stat |= 0x10;
					}
					if(work->time <= 20) {
						for(i=1; i<4; i++) {
							for(j=0; j<work->work_s16[3]; j++) {
								HuSprAttrSet(work->spr_grp[i], j, SPRITE_ATTR_HIDDEN);
							}
						}
						time = work->time;
						scale = work->scale_x+(0.5*sin((M_PI*(time*9.0f))/180.0));
						for(j=0; j<work->work_s16[3]; j++) {
							HuSprAttrReset(work->spr_grp[0], j, SPRITE_ATTR_HIDDEN);
							pos_x = ((28.0f*scale)+(work->x-(0.5f*(scale*(work->work_s16[3]*56)))))+(scale*(j*56));
							HuSprPosSet(work->spr_grp[0], j, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[0], j, work->scale_x+(sin((M_PI*(time*9.0f))/180.0)), work->scale_y+(sin((M_PI*(time*9.0f))/180.0)));
						}
						if(time == 20.0f) {
							for(i=1; i<4; i++) {
								for(j=0; j<work->work_s16[3]; j++) {
									HuSprAttrReset(work->spr_grp[i], j, SPRITE_ATTR_HIDDEN);
								}
							}
						}
					} else {
						if(work->time > 80 || work->time < 140) {
							for(i=0; i<4; i++) {
								for(j=0; j<work->work_s16[3]; j++) {
									time = (work->time-80)-i-j;
									if(time < 0 || time > 40) {
										continue;
									}
									if(time <= 20) {
										float pos_base = (28.0f+(work->x-(0.5f*(work->work_s16[3]*56))))+(j*56);
										pos_x = (28.0f+(work->x-(0.5f*(work->work_s16[3]*56))))+((work->work_s16[3]-j-1)*56);
										HuSprPosSet(work->spr_grp[i], j, pos_base+((time/20.0f)*(pos_x-pos_base)), work->y+((440.0f-work->y)*(time/20.0f)));
									} else {
										time -= 20.0f;
										pos_x = (28.0f+(work->x-(0.5f*(work->work_s16[3]*56))))+((work->work_s16[3]-j-1)*56);
										pos_y = 440.0f;
										HuSprPosSet(work->spr_grp[i], j, pos_x, pos_y+((-40.0f-pos_y)*(time/20.0f)));
									}
								}
							}
						}
					}
					if(work->time == 140) {
						work->stat |= 0x4;
					}
					if(work->time >= 140) {
						work->type = 0;
						work->stat |= 0x8;
					}
				}
			}
			break;
			
			case -1:
			{
				work->work_float[0] += seqSpeed*0.1f;
				scale = 1.0f-work->work_float[0];
				if(scale <= 0.0f) {
					scale = 0.0f;
					work->type = 0;
					work->stat |= 0x8;
					if(work->work_s16[1] == 0) {
						MGSeqPauseEnableCtrl(1);
					}
				}
				for(idx=0; idx<work->work_s16[3]; idx++) {
					HuSprTPLvlSet(work->spr_grp[0], idx, scale);
				}
			}
			break;
			
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static int SeqUpdateMGStory(SeqWork *work)
{
	s16 idx;
	float scale;
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->work_float[0] = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->type == 2) {
		return 1;
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->stat |= 0x4;
		work->type = -1;
		work->work_float[0] = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				float pos_x, pos_y;
				float time;
				s16 i;
				s16 j;
				if(work->work_s16[1] == 0) {
					if(work->time <= 30) {
						for(idx=0; idx<work->work_s16[3]; idx++) {
							time = (work->time-(idx*2));
							if(time < 0.0f || time > 15.0f) {
								continue;
							}
							pos_x = -50.0f;
							HuSprPosSet(work->spr_grp[0], idx, pos_x+((288.0f-pos_x)*(time/15.0f)), work->y);
							HuSprTPLvlSet(work->spr_grp[0], idx, 1.0f);
							HuSprZRotSet(work->spr_grp[0], idx, (1.0-(time/15.0f))*180.0);
							pos_x = 626.0f;
							HuSprPosSet(work->spr_grp[1], idx, pos_x+((288.0f-pos_x)*(time/15.0f)), work->y);
							HuSprTPLvlSet(work->spr_grp[1], idx, 1.0f);
							HuSprZRotSet(work->spr_grp[1], idx, (1.0-(time/15.0f))*-180.0);
						}
						if(work->time == 30) {
							for(j=0; j<work->work_s16[3]; j++) {
								HuSprAttrSet(work->spr_grp[1], j, SPRITE_ATTR_HIDDEN);
							}
						}
					} else {
						if(work->time > 35 && work->time <= 45) {
							time = work->time-35;
							for(idx=0; idx<work->work_s16[3]; idx++) {
								pos_x = (work->x-(0.5f*(work->work_s16[3]*56)))+28.0f+(idx*56);
								HuSprPosSet(work->spr_grp[0], idx, 288.0f+((pos_x-288.0f)*(time/10.0f)), work->y);
							}
						} else {
							if(work->time > 55) {
								time = work->time-55;
								scale = 0.5*sin(M_PI*(9.0f*time)/180.0);
								for(j=0; j<work->work_s16[3]; j++) {
									pos_x = (28.0f*(scale+work->scale_x))+(work->x-(0.5f*((work->work_s16[3]*56)*(scale+work->scale_x))))+((j*56)*(scale+work->scale_x));
									HuSprPosSet(work->spr_grp[0], j, pos_x, work->y);
									HuSprScaleSet(work->spr_grp[0], j, work->scale_x+scale, work->scale_y+scale);
								}
							}
						}
					}
					if(work->time == 55) {
						HuAudFXPlay(36);
						work->stat |= 0x10;
					}
					if(work->time == 75) {
						SeqPlayStartFX();
						work->stat |= 0x4;
					}
					if(work->time >= 75) {
						work->type = 0;
					}
				} else {
					if(work->time == 1) {
						if(work->work_s16[1] == 1) {
							HuAudFXPlay(37);
						} else {
							HuAudFXPlay(40);
						}
						MGSeqPauseEnableCtrl(0);
						work->stat |= 0x10;
					}
					if(work->time <= 20) {
						for(i=1; i<4; i++) {
							for(j=0; j<work->work_s16[3]; j++) {
								HuSprAttrSet(work->spr_grp[i], j, SPRITE_ATTR_HIDDEN);
							}
						}
						time = work->time;
						scale = work->scale_x+(0.5*sin((M_PI*(time*9.0f))/180.0));
						for(j=0; j<work->work_s16[3]; j++) {
							HuSprAttrReset(work->spr_grp[0], j, SPRITE_ATTR_HIDDEN);
							pos_x = ((28.0f*scale)+(work->x-(0.5f*(scale*(work->work_s16[3]*56)))))+(scale*(j*56));
							HuSprPosSet(work->spr_grp[0], j, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[0], j, work->scale_x+(sin((M_PI*(time*9.0f))/180.0)), work->scale_y+(sin((M_PI*(time*9.0f))/180.0)));
						}
						if(time == 20.0f){ 
							for(i=1; i<4; i++) {
								for(j=0; j<work->work_s16[3]; j++) {
									HuSprAttrReset(work->spr_grp[i], j, SPRITE_ATTR_HIDDEN);
								}
							}
						}
					} else if(work->time > 80 && work->time < 160) {
						for(i=0; i<4; i++) {
							for(j=0; j<work->work_s16[3]; j++) {
								s16 initF;
								float dx, dy;
								time = (work->time-80)-i;
								if(time < 0 || time > 60) {
									continue;
								}
								pos_x = (28.0f+(work->x-(0.5f*(work->work_s16[3]*56))))+(j*56);
								dx = 28.0f+(work->x-(0.5f*(work->work_s16[3]*56)));
								pos_y = work->y;
								for(idx=initF=0; idx<time; idx++) {
									if(!initF) {
										pos_x -= 20.0f;
										if(pos_x <= dx) {
											pos_x = 28.0f+(work->x-(0.5f*(work->work_s16[3]*56)));
											initF = 1;
											dy = 25.0f;
											dx = 10.0f;
										}
										
									} else {
										pos_x += dx;
										pos_y += dy;
										dx += 0.1;
										dy -= 2.0f;
										if(pos_y < 0.0f) {
											break;
										}
									}
								}
								
								HuSprPosSet(work->spr_grp[i], j, pos_x, pos_y);
							}
						}
					}
					if(work->time == 160) {
						work->stat |= 0x4;
					}
					if(work->time >= 160) {
						work->type = 0;
						work->stat |= 0x8;
					}
				}
			}
			break;
			
			case -1:
			{
				work->work_float[0] += seqSpeed*0.1f;
				scale = 1.0f-work->work_float[0];
				if(scale <= 0.0f) {
					scale = 0.0f;
					work->type = 0;
					work->stat |= 0x8;
					if(work->work_s16[1] == 0) {
						MGSeqPauseEnableCtrl(1);
					}
				}
				for(idx=0; idx<work->work_s16[3]; idx++) {
					HuSprTPLvlSet(work->spr_grp[0], idx, scale);
				}
			}
			break;
			
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static int SeqUpdateMG2vs2(SeqWork *work)
{
	s16 idx;
	float scale;
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->work_float[0] = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->type == 2) {
		return 1;
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->stat |= 0x4;
		work->type = -1;
		work->work_float[0] = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				static s16 letterOfs[] = {
					-10, -50,
					0, -30,
					5, -60,
					-10, 60,
					8, -40,
					5, 50,
					-10, 20
				};
				
				float pos_x;
				float time;
				s16 i;
				s16 j;
				if(work->work_s16[1] == 0) {
					if(work->time <= 30) {
						time = work->time;
						for(idx=0; idx<work->work_s16[3]; idx++) {
							pos_x = (28.0f+(work->x-(0.5f*(work->scale_x*(work->work_s16[3]*56)))))+(idx*56);
							HuSprPosSet(work->spr_grp[0], idx, pos_x+((1.0f-(time/30.0f))*letterOfs[(idx*2)]), work->y+((1.0f-(time/30.0f))*letterOfs[(idx*2)+1])); 
							HuSprTPLvlSet(work->spr_grp[0], idx, time/30.0f);
						}
					} else {
						if(work->time > 40 && work->time <= 60) {
							time = work->time-40;
							scale = 0.5*sin(((time*9.0f)*M_PI)/180.0);
							for(j=0; j<work->work_s16[3]; j++) {
								pos_x = (28.0f*(scale+work->scale_x))+(work->x-(0.5f*((work->work_s16[3]*56)*(scale+work->scale_x))))+((j*56)*(scale+work->scale_x));
								HuSprPosSet(work->spr_grp[0], j, pos_x, work->y);
								HuSprScaleSet(work->spr_grp[0], j, work->scale_x+scale, work->scale_y+scale);
							}
						}
					}
					if(work->time == 40) {
						HuAudFXPlay(36);
						work->stat |= 0x10;
					}
					if(work->time == 60) {
						work->stat |= 0x4;
						SeqPlayStartFX();
					}
					if(work->time >= 60) {
						work->type = 0;
					}
				} else {
					if(work->time == 1) {
						if(work->work_s16[1] == 1) {
							HuAudFXPlay(37);
						} else {
							HuAudFXPlay(40);
						}
						MGSeqPauseEnableCtrl(0);
						work->stat |= 0x10;
					}
					if(work->time <= 20) {
						for(i=1; i<4; i++) {
							for(j=0; j<work->work_s16[3]; j++) {
								HuSprAttrSet(work->spr_grp[i], j, SPRITE_ATTR_HIDDEN);
							}
						}
						time = work->time;
						scale = work->scale_x+(0.5*sin((M_PI*(time*9.0f))/180.0));
						for(j=0; j<work->work_s16[3]; j++) {
							HuSprAttrReset(work->spr_grp[0], j, SPRITE_ATTR_HIDDEN);
							pos_x = ((28.0f*scale)+(work->x-(0.5f*(scale*(work->work_s16[3]*56)))))+(scale*(j*56));
							HuSprPosSet(work->spr_grp[0], j, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[0], j, work->scale_x+(sin((M_PI*(time*9.0f))/180.0)), work->scale_y+(sin((M_PI*(time*9.0f))/180.0)));
						}
						if(time == 20.0f) {
							for(i=1; i<4; i++) {
								for(j=0; j<work->work_s16[3]; j++) {
									HuSprAttrReset(work->spr_grp[i], j, SPRITE_ATTR_HIDDEN);
								}
							}
						}
					} else {
						if(work->time > 80 && work->time < 140) {
							time = work->time-80;
							for(idx=0; idx<work->work_s16[3]; idx++) {
								float radius = (idx*56)-(((work->work_s16[3]-1)*56)/2);
								float angle = (1.0f+(1.0f-(ABS(radius)/320.0f)))*720.0f;
								float new_scale;
								radius *= 1.0-(time/60.0f);
								HuSprPosSet(work->spr_grp[0], idx, (radius*sin(M_PI*(((time/60.0f)*angle)+90.0f)/180.0))+work->x, (radius*cos(M_PI*(((time/60.0f)*angle)+90.0f)/180.0))+work->y);
								HuSprZRotSet(work->spr_grp[0], idx, -(time/60.0f)*720.0f);
								new_scale = 0.5+(0.5*(1.0f-(time/60.0f)));
								HuSprScaleSet(work->spr_grp[0], idx, new_scale, new_scale);
								HuSprTPLvlSet(work->spr_grp[0], idx, 1.0f-(time/60.0f));
							}
						}
					}
					if(work->time == 140) {
						work->stat |= 0x4;
					}
					if(work->time >= 150) {
						work->type = 0;
						work->stat |= 0x8;
					}
				}
			}
			break;
			
			case -1:
			{
				work->work_float[0] += seqSpeed*0.1f;
				scale = 1.0f-work->work_float[0];
				if(scale <= 0.0f) {
					scale = 0.0f;
					work->type = 0;
					work->stat |= 0x8;
					if(work->work_s16[1] == 0) {
						MGSeqPauseEnableCtrl(1);
					}
				}
				for(idx=0; idx<work->work_s16[3]; idx++) {
					HuSprTPLvlSet(work->spr_grp[0], idx, scale);
				}
			}
			break;
			
			default:
				
				break;
				
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static int SeqInitFlip(SeqWork *work, va_list params)
{
	s16 i;
	s16 word_grp;
	s16 word_ofs;
	work->work_s16[1] = va_arg(params, int);
	if(work->work_s16[1] == 2) {
		return SeqInitDraw(work, params);
	}
	work->type = 0;
	work->work_float[0] = 0;
	{
		s32 word_ofs_temp;
		s32 word_katakana;
		s32 word_flag;

		if(seqLanguage == 0) {
			word_ofs_temp = 3;
		} else {
			word_ofs_temp = 0;
		}
		word_ofs = word_ofs_temp;
		word_katakana = 0;
		if(work->work_s16[1] == 2 && word_ofs == 0) {
			word_katakana = 1;
		}
		if(word_katakana) {
			word_flag = 1;
		} else {
			word_flag = 0;
		}
		
		word_grp = SeqMakeWord(work, wordMgTbl[work->work_s16[1]+word_ofs], word_flag);
	}
	HuSprGrpPosSet(work->spr_grp[word_grp], 0.0f, 0.0f);
	for(i=0; i<work->work_s16[3]; i++) {
		HuSprTPLvlSet(work->spr_grp[word_grp], i, 0.0f);
		HuSprPosSet(work->spr_grp[word_grp], i, (28.0f+(work->x-(0.5f*(work->work_s16[3]*56))))+(i*56), work->y);
		HuSprAttrSet(work->spr_grp[word_grp], i, SPRITE_ATTR_BILINEAR);
		HuSprAttrReset(work->spr_grp[word_grp], i, SPRITE_ATTR_HIDDEN);
	}
	work->work_s16[2] = work->work_s16[3];
	{
		s32 word_ofs_temp;
		s32 word_katakana;
		s32 word_flag;
		
		if(seqLanguage == 0) {
			word_ofs_temp = 0;
		} else {
			word_ofs_temp = 3;
		}
		word_ofs = word_ofs_temp;
		word_katakana = 0;
		if(work->work_s16[1] == 2 && word_ofs == 0) {
			word_katakana = 1;
		}
		if(word_katakana) {
			word_flag = 1;
		} else {
			word_flag = 0;
		}
		
		word_grp = SeqMakeWord(work, wordMgTbl[work->work_s16[1]+word_ofs], word_flag);
	}
	HuSprGrpPosSet(work->spr_grp[word_grp], 0.0f, 0.0f);
	for(i=0; i<work->work_s16[3]; i++) {
		HuSprTPLvlSet(work->spr_grp[word_grp], i, 0.0f);
		HuSprPosSet(work->spr_grp[word_grp], i, (28.0f+(work->x-(0.5f*(work->work_s16[3]*56))))+(i*56), work->y);
		HuSprAttrSet(work->spr_grp[word_grp], i, SPRITE_ATTR_BILINEAR);
		HuSprAttrReset(work->spr_grp[word_grp], i, SPRITE_ATTR_HIDDEN);
	}
	if(seqPauseF) {
		work->type = 2;
		HuSprAttrSet(word_grp, 0, SPRITE_ATTR_HIDDEN);
	} else {
		work->param[0] = 3;
	}
	return 1;
}

static int SeqUpdateFlip(SeqWork *work)
{
	s16 idx;
	float scale;
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->work_float[0] = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->type == 2) {
		return 1;
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->stat |= 0x4;
		work->type = -1;
		work->work_float[0] = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				float time;
				float pos_x;
				s16 i;
				if(work->work_s16[1] == 0) {
					if(work->time <= 10) {
						for(idx=0; idx<work->work_s16[2]; idx++) {
							HuSprTPLvlSet(work->spr_grp[0], idx, work->time/10.0f);
						}
					} else {
						if(work->time <= 30) {
							time = work->time-10;
							if(time <= 10) {
								for(idx=0; idx<work->work_s16[2]; idx++) {
									HuSprScaleSet(work->spr_grp[0], idx, cos(M_PI*((time/10.0f)*90.0f)/180.0), 1.0f);
								}
							} else {
								time -= 10.0f;
								for(idx=0; idx<work->work_s16[3]; idx++) {
									HuSprTPLvlSet(work->spr_grp[1], idx, 1.0f);
									HuSprScaleSet(work->spr_grp[1], idx, sin(M_PI*((time/10.0f)*90.0f)/180.0), 1.0f);
								}
							}
						} else {
							if(work->time > 35 && work->time <= 55) {
								time = work->time-35;
								scale = 0.5*sin(((time*9.0f)*M_PI)/180.0);
								for(i=0; i<work->work_s16[3]; i++) {
									pos_x = (28.0f*(scale+work->scale_x))+(work->x-(0.5f*((work->work_s16[3]*56)*(scale+work->scale_x))))+((i*56)*(scale+work->scale_x));
									HuSprPosSet(work->spr_grp[1], i, pos_x, work->y);
									HuSprScaleSet(work->spr_grp[1], i, work->scale_x+scale, work->scale_y+scale);
								}
							}
						}
					}
					if(work->time == 35) {
						HuAudFXPlay(36);
						work->stat |= 0x10;
					}
					if(work->time == 55) {
						work->stat |= 0x4;
						SeqPlayStartFX();
					}
					if(work->time >= 75) {
						work->type = 0;
					}
				} else {
					if(work->time == 1) {
						if(work->work_s16[1] == 1) {
							HuAudFXPlay(37);
						} else {
							HuAudFXPlay(40);
						}
						MGSeqPauseEnableCtrl(0);
						work->stat |= 0x10;
					}
					if(work->time <= 20) {
						time = work->time;
						scale = 0.5*sin(M_PI*(9.0f*time)/180.0);
						for(i=0; i<work->work_s16[3]; i++) {
							HuSprTPLvlSet(work->spr_grp[1], i, 1.0f);
							pos_x = (28.0f*(scale+work->scale_x))+(work->x-(0.5f*((work->work_s16[3]*56)*(scale+work->scale_x))))+((i*56)*(scale+work->scale_x));
							HuSprPosSet(work->spr_grp[1], i, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[1], i, work->scale_x+scale, work->scale_y+scale);
						}
					} else {
						if(work->time > 80 && work->time <= 160) {
							time = work->time-80;
							for(idx=0; idx<work->work_s16[3]; idx++) {
								scale = time-(idx*2);
								if(scale < 0 || scale > 15.0f) {
									continue;
								}
								HuSprScaleSet(work->spr_grp[1], idx, cos(M_PI*((scale/15.0f)*90.0f)/180.0), 1.0f);
							}
							for(idx=0; idx<work->work_s16[2]; idx++) {
								scale = (time-15.0f)-(idx*2);
								if(scale < 0 || scale > 30.0f) {
									continue;
								}
								HuSprTPLvlSet(work->spr_grp[0], idx, 1.0f);
								HuSprScaleSet(work->spr_grp[0], idx, sin(M_PI*((scale/30.0f)*180.0f)/180.0), 1.0f);
							}
						}
					}
					if(work->time == 160) {
						work->stat |= 0x4;
					}
					if(work->time >= 160) {
						work->type = 0;
						work->stat |= 0x8;
					}
				}
			}
			break;
			
			case -1:
			{
				work->work_float[0] += seqSpeed*0.1f;
				scale = 1.0f-work->work_float[0];
				if(scale <= 0.0f) {
					scale = 0.0f;
					work->type = 0;
					work->stat |= 0x8;
					if(work->work_s16[1] == 0) {
						MGSeqPauseEnableCtrl(1);
					}
				}
				for(idx=0; idx<work->work_s16[3]; idx++) {
					HuSprTPLvlSet(work->spr_grp[1], idx, scale);
				}
			}
			break;
			
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static int SeqUpdateMGBowser(SeqWork *work)
{
	s16 idx;
	float scale;
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->work_float[0] = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->type == 2) {
		return 1;
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->stat |= 0x4;
		work->type = -1;
		work->work_float[0] = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				s16 i;
				s16 j;
				float angle;
				float time_angle;
				float time;
				float pos_x, pos_y;
				
				float temp_f25;
				float center_x;
				s16 spr_idx[16];
				float scale_arr[16];
				
				
				if(work->work_s16[1] == 0) {
					if(work->time <= 60) {
						center_x = (0.5*(work->work_s16[3]*56))+20.0;
						for(idx=0; idx<work->work_s16[3]; idx++) {
							time = work->time-idx;
							if(time < 0) {
								scale_arr[idx] = 0.0f;
								spr_idx[idx] = idx;
							} else {
								if(time > 50.0f) {
									time = 50.0f;
								}
								time_angle = 540.0*(1.0f-(time/50.0f));
								pos_x = (28.0f+(0.5f*-(work->work_s16[3]*56)))+(idx*56);
								angle = 180.0*(atan2(pos_x, center_x)/M_PI);
								pos_x = work->x+(center_x*sin(M_PI*(angle+time_angle)/180.0));
								pos_y = work->y-(240.0*(1.0-(time/50.0f)));
								HuSprPosSet(work->spr_grp[0], idx, pos_x, pos_y);
								temp_f25 = 0.9+(0.1*cos(M_PI*(angle+time_angle)/180.0));
								HuSprScaleSet(work->spr_grp[0], idx, temp_f25*cos(M_PI*(angle+time_angle)/180.0), temp_f25);
								scale_arr[idx] = cos(M_PI*(angle+time_angle)/180.0);
								spr_idx[idx] = idx;
							}
						}
						for(i=1; i<work->work_s16[3]; i++) {
							for(idx=0; idx<work->work_s16[3]-i; idx++) {
								if(scale_arr[idx] > scale_arr[idx+1]) {
									 j= spr_idx[idx];
									spr_idx[idx] = spr_idx[idx+1];
									spr_idx[idx+1] = j;
									angle = scale_arr[idx];
									scale_arr[idx] = scale_arr[idx+1];
									scale_arr[idx+1] = angle;
								}
							}
						}
						for(idx=0; idx<work->work_s16[3]; idx++) {
							HuSprPriSet(work->spr_grp[0], spr_idx[idx], idx+5);
						}
					} else {
						if(work->time > 60 && work->time <= 80) {
							time = work->time-60;
							scale = 0.5*sin(((time*9.0f)*M_PI)/180.0);
							for(i=0; i<work->work_s16[3]; i++) {
								pos_x = (28.0f*(scale+work->scale_x))+(work->x-(0.5f*((work->work_s16[3]*56)*(scale+work->scale_x))))+((i*56)*(scale+work->scale_x));
								HuSprPosSet(work->spr_grp[0], i, pos_x, work->y);
								HuSprScaleSet(work->spr_grp[0], i, work->scale_x+scale, work->scale_y+scale);
							}
						}
						
					}
					if(work->time == 60) {
						HuAudFXPlay(36);
						work->stat |= 0x10;
					}
					if(work->time == 80) {
						work->stat |= 0x4;
						SeqPlayStartFX();
					}
					if(work->time >= 100) {
						work->type = 0;
					}
				} else {
					if(work->time == 1) {
						if(work->work_s16[1] == 1) {
							HuAudFXPlay(37);
						} else {
							HuAudFXPlay(40);
						}
						MGSeqPauseEnableCtrl(0);
						work->stat |= 0x10;
					}
					if(work->time <= 20) {
						for(j=1; j<4; j++) {
							for(i=0; i<work->work_s16[3]; i++) {
								HuSprAttrSet(work->spr_grp[j], i, SPRITE_ATTR_HIDDEN);
							}
						}
						time = work->time;
						scale = work->scale_x+(0.5*sin(((time*9.0f)*M_PI)/180.0));
						for(i=0; i<work->work_s16[3]; i++) {
							HuSprAttrReset(work->spr_grp[0], i, SPRITE_ATTR_HIDDEN);
							pos_x = ((28.0f*scale)+(work->x-(0.5f*(scale*(work->work_s16[3]*56)))))+(scale*(i*56));
							HuSprPosSet(work->spr_grp[0], i, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[0], i, work->scale_x+(sin((M_PI*(time*9.0f))/180.0)), work->scale_y+(sin((M_PI*(time*9.0f))/180.0)));
						}
						if(time == 20.0f) {
							for(j=1; j<4; j++) {
								for(i=0; i<work->work_s16[3]; i++) {
									HuSprAttrReset(work->spr_grp[j], i, SPRITE_ATTR_HIDDEN);
								}
							}
						}
					} else {
						if(work->time > 80 && work->time <= 125) {
							static float letterOfs[] = {
								-30, -30,
								606, -30,
								340, 510,
								606, 510,
								-30, 450,
								606, 120,
								450, -30,
							};
							for(i=0; i<4; i++) {
								time = work->time-80-i;
								if(time < 0.0f || time > 15.0f) {
									continue;
								}
								for(idx=0; idx<work->work_s16[3]; idx++) {
									pos_x = (28.0f+(work->x-(0.5f*(work->work_s16[3]*56))))+(idx*56);
									pos_x += (time/15.0f)*(letterOfs[(idx*2)]-pos_x);
									pos_y = work->y+((time/15.0f)*(letterOfs[(idx*2)+1]-work->y));
									HuSprPosSet(work->spr_grp[i], idx, pos_x, pos_y);
								}
							}
						}
					}
					if(work->time == 125) {
						work->stat |= 0x4;
					}
					if(work->time >= 135) {
						work->type = 0;
						work->stat |= 0x8;
					}
				}
			}
			break;
			
			case -1:
			{
				work->work_float[0] += seqSpeed*0.1f;
				scale = 1.0f-work->work_float[0];
				if(scale <= 0.0f) {
					scale = 0.0f;
					work->type = 0;
					work->stat |= 0x8;
					if(work->work_s16[1] == 0) {
						MGSeqPauseEnableCtrl(1);
					}
				}
				for(idx=0; idx<work->work_s16[3]; idx++) {
					HuSprTPLvlSet(work->spr_grp[0], idx, scale);
				}
			}
			break;
			
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static int SeqInitDraw(SeqWork *work, va_list params)
{
	s16 word_grp;
	work->work_s16[1] = 2;
	work->seq_no = 13;
	work->type = 0;
	work->work_float[0] = 0.0f;
	{
		s32 word_flag;
		s32 word_ofs;

		if(seqLanguage == 0) {
			word_flag = 1;
		} else {
			word_flag = 0;
		}
		if(seqLanguage == 0) {
			word_ofs = 0;
		} else {
			word_ofs = 3;
		}
		
		word_grp = SeqMakeWord(work, wordMgTbl[2+word_ofs], word_flag);
	}
	HuSprGrpPosSet(work->spr_grp[word_grp], 288.0f, 240.0f);
	work->param[0] = 3;
	return 1;
}

static int SeqUpdateDraw(SeqWork *work)
{
	s16 idx;
	float scale;
	s16 group = work->spr_grp[0];
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->work_float[0] = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->stat |= 0x4;
		work->type = -1;
		work->work_float[0] = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				float time;
				float scale;
				float zrot;
				if(work->time <= 20) {
					time = work->time;
					zrot = 365.0f*(time/20.0f);
					scale = (double)1.3*sin(M_PI*(90.0f*(time/20.0f))/180.0);
					HuSprGrpScaleSet(group, scale, scale);
					HuSprGrpZRotSet(group, zrot);
				}
				if(work->time > 20 && work->time <= 25) {
					HuSprGrpZRotSet(group, 0.0f);
					time = work->time-20;
					scale = 1.0+(0.3*cos(M_PI*(90.0f*(time/5.0f))/180.0));
					HuSprGrpScaleSet(group, scale, scale);
				}
				if(work->time == 5) {
					HuAudFXPlay(40);
				}
				if(work->time == 60) {
					work->type = 0;
				}
			}
			break;
			
			case -1:
			{
				float tp_lvl;
				work->work_float[0] += seqSpeed*0.1f;
				tp_lvl = 1.0f-work->work_float[0];
				if(tp_lvl <= 0.0f) {
					tp_lvl = 0.0f;
					work->work_s16[1] = 0;
					work->stat |= 0x8;
				}
				HuSprGrpTPLvlSet(group, tp_lvl);
			}
			break;
			
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

void MGSeqPauseEnableCtrl(s32 flag)
{
	if(!_CheckFlag(0x10008)) {
		omSysPauseEnable(flag);
	}
}

static void SeqPlayStartFX(void)
{
	
}