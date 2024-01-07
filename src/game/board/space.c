#include "game/gamework_data.h"
#include "game/flag.h"
#include "game/board/main.h"
#include "game/board/space.h"

#include "math.h"

extern s16 BoardStarHostMdlGet(void);
extern void BoardModelPosSetV(s16 model, Vec *pos);


static GXTexObj spaceHiliteTex;
static GXTexObj spaceTex;
s16 boardSpaceStarTbl[8];
static BoardSpace spaceData[2][256];

static s16 spaceCnt[2];
static u32 spaceAttr[2];
static void *spaceTexData;
static void *spaceHiliteTexData;
static GXTexFmt spaceTexFmt;
static GXTexFmt spaceHiliteTexFmt;
s16 lbl_801D3FC4[4];
static BoardSpaceEventFunc landEventFunc;
static BoardSpaceEventFunc walkMiniEventFunc;
static BoardSpaceEventFunc walkEventFunc;
static s32 spaceDrawCnt;
static s16 spaceDrawF;

static s16 spaceDrawMdl = -1;
static s16 starMdl = -1;

s32 BoardSpaceRotGet(s32 layer, s32 index, Vec *rot);
s32 BoardSpaceStarGet(s32 index);
s32 BoardSpaceStarGetCurr(void);

void BoardSpaceWalkEventFuncSet(BoardSpaceEventFunc func)
{
	walkEventFunc = func;
}

void BoardSpaceWalkMiniEventFuncSet(BoardSpaceEventFunc func)
{
	walkMiniEventFunc = func;
}

void BoardSpaceLandEventFuncSet(BoardSpaceEventFunc func)
{
	landEventFunc = func;
}

s32 BoardSpaceWalkEventExec(void)
{
	s32 ret = -1;
	if(walkEventFunc) {
		ret = walkEventFunc();
	}
	return ret;
}

s32 BoardSpaceWalkMiniEventExec(void)
{
	s32 ret = -1;
	if(walkMiniEventFunc) {
		_SetFlag(FLAG_ID_MAKE(1, 8));
		ret = walkMiniEventFunc();
		_ClearFlag(FLAG_ID_MAKE(1, 8));
	}
	return ret;
}

s16 BoardSpaceCountGet(s32 layer)
{
	return spaceCnt[layer];
}

BoardSpace *BoardSpaceGet(s32 layer, s32 index)
{
	if(index <= 0 || index > spaceCnt[layer]) {
		return NULL;
	} else {
		return &spaceData[layer][index-1];
	}
}

void BoardSpaceAttrSet(s32 layer, u32 attr)
{
	spaceAttr[layer] |= attr;
}

void BoardSpaceAttrReset(s32 layer, u32 attr)
{
	spaceAttr[layer] &= ~attr;
}

u32 BoardSpaceFlagGet(s32 layer, s32 index)
{
	if(index <= 0 || index > spaceCnt[layer]) {
		return 0;
	} else {
		return spaceData[layer][index-1].flag;
	}
}

s32 BoardSpaceTypeGet(s32 layer, s32 index)
{
	if(index <= 0 || index > spaceCnt[layer]) {
		return 0;
	} else {
		return spaceData[layer][index-1].type;
	}
}

void BoardSpaceTypeSet(s32 layer, s32 index, s32 type)
{
	if(index <= 0 || index > spaceCnt[layer]) {
		return;
	} else {
		spaceData[layer][index-1].type = type;
	}
}

s32 BoardSpacePosGet(s32 layer, s32 index, Vec *pos)
{
	BoardSpace *space = BoardSpaceGet(layer, index);
	if(!space) {
		return -1;
	} else {
		*pos = space->pos;
		return 0;
	}
}

void BoardSpaceCornerPosGet(s32 index, s32 corner, Vec *pos)
{
	Vec corner_ofs;
	Vec rot;
	s8 corner_pos[4][2] = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
	BoardSpaceRotGet(0, index, &rot);
	BoardSpacePosGet(0, index, pos);
	corner_ofs.x = corner_pos[corner][0]*80.0f;
	corner_ofs.y = 0;
	corner_ofs.z = corner_pos[corner][1]*80.0f;
	corner_ofs.x = (cos((M_PI*rot.z)/180)*corner_ofs.x)+(sin((M_PI*rot.z)/180)*corner_ofs.y);
	corner_ofs.y = (cos((M_PI*rot.x)/180)*cos((M_PI*rot.z)/180)*corner_ofs.y)
		+(sin((M_PI*rot.z)/180)*corner_ofs.x)
		+(sin((M_PI*-rot.x)/180)*corner_ofs.z);
	corner_ofs.z = (sin((M_PI*rot.x)/180)*corner_ofs.y)+(cos((M_PI*rot.x)/180)*corner_ofs.z);
	pos->x += corner_ofs.x;
	pos->y += corner_ofs.y;
	pos->z += corner_ofs.z;
}

s32 BoardSpaceRotGet(s32 layer, s32 index, Vec *rot)
{
	BoardSpace *space = BoardSpaceGet(layer, index);
	if(!space) {
		return -1;
	} else {
		*rot = space->rot;
		return 0;
	}
}

s32 BoardSpaceFlagSearch(s32 layer, u32 flag)
{
	s32 i;
	for(i=0; i<spaceCnt[layer]; i++) {
		BoardSpace *space = &spaceData[layer][i];
		if((space->flag & flag) == flag) {
			return space-(&spaceData[layer][0])+1;
		}
	}
	return -1;
}

s32 BoardSpaceFlagPosGet(s32 layer, u32 flag, Vec *pos)
{
	s32 space = BoardSpaceFlagSearch(layer, flag);
	if(space == -1) {
		return -1;
	}
	if(pos) {
		BoardSpacePosGet(layer, space, pos);
	}
	return space;
}

s32 BoardSpaceLinkFlagSearch(s32 layer, s32 index, u32 flag)
{
	BoardSpace *link_space;
	BoardSpace *space = BoardSpaceGet(layer, index);
	s32 i;
	if(!space) {
		return -1;
	}
	for(i=0; i<space->link_cnt; i++) {
		link_space = BoardSpaceGet(layer, space->link[i]);
		if(link_space->flag & flag) {
			return link_space-&spaceData[layer][0]+1;
		}
	}
	return -1;
}

s32 BoardSpaceLinkTypeListGet(s32 layer, s32 index, s32 type, s16 *list)
{
	s32 count;
	BoardSpace *space = BoardSpaceGet(layer, index);
	s32 i;
	if(!space) {
		return -1;
	}
	for(count=i=0; i<space->link_cnt; i++) {
		BoardSpace *link_space = BoardSpaceGet(layer, space->link[i]);
		if(link_space->type == type && count < BOARD_SPACE_LINKMAX) {
			list[count] = link_space-&spaceData[layer][0]+1;
			count++;
		}
	}
	return count;
}

s32 BoardSpaceLinkTargetListGet(s32 layer, s32 target, s16 *list)
{
	s32 i, j;
	s32 count;
	BoardSpace *space;
	memset(list, 0, BOARD_SPACE_LINKMAX*sizeof(s16));
	space = &spaceData[layer][0];
	for(count=i=0; i<spaceCnt[layer]; i++, space++) {
		for(j=0; j<space->link_cnt; j++) {
			if(space->link[j] == target && count < BOARD_SPACE_LINKMAX) {
				list[count++] = space-&spaceData[layer][0]+1;
			}
		}
	}
	return count;
}

s32 BoardSpaceLinkTypeSearch(s32 layer, s32 target, u16 type)
{
	s32 i;
	BoardSpace *space = BoardSpaceGet(layer, target);
	if(!space) {
		return -1;
	}
	for(i=0; i<space->link_cnt; i++) {
		BoardSpace *link_space = BoardSpaceGet(layer, space->link[i]);
		if(link_space->type == type) {
			return space->link[i];
		}
	}
	return -1;
}

s32 BoardSpaceLinkTransformGet(s32 flag, Vec *pos, Vec *rot, Vec *scale)
{
	s32 i;
	s32 space_flag = BoardSpaceFlagSearch(0, flag);
	BoardSpace *space = BoardSpaceGet(0, space_flag);
	
	for(i=0; i<space->link_cnt; i++) {
		BoardSpace *link_space = BoardSpaceGet(0, space->link[i]);
		BoardSpace *src_space;
		if(!(link_space->flag & 0x2000000)) {
			continue;
		}
		src_space = BoardSpaceGet(0, link_space->link[0]);
		if(pos) {
			*pos = src_space->pos;
		}
		if(rot) {
			*rot = src_space->rot;
		}
		if(scale) {
			*scale = src_space->scale;
		}
		return 0;
	}
	return -1;
}

void BoardSpaceStarSet(s32 space)
{
	s16 host_space;
	Vec pos;
	BoardSpace *space_plat;
	BoardSpaceTypeSet(0, space, 8);
	host_space = BoardSpaceLinkFlagSearch(0, space, 0x04000000);
	BoardSpacePosGet(0, host_space, &pos);
	BoardModelPosSetV(BoardStarHostMdlGet(), &pos);
}

static inline s16 BoardStarMdlGet(void)
{
	return starMdl;
}

static inline s32 BoardStarSpaceTypeGet(s16 index)
{
	return BoardSpaceTypeGet(0, BoardSpaceStarGet(index));
}

void BoardSpaceStarSetIndex(s32 index)
{
	Vec pos;
	Vec rot;
	s16 space;
	if(_CheckFlag(FLAG_ID_MAKE(1, 1))) {
		BoardSpaceTypeSet(0, boardSpaceStarTbl[GWSystem.star_pos], 1);
	}
	GWSystem.star_pos = index & 0x7;
	BoardSpaceStarSet(BoardSpaceStarGetCurr());
	space = BoardSpaceLinkFlagSearch(0, BoardSpaceStarGetCurr(), 0x04000000);
	BoardSpacePosGet(0, space, &pos);
	BoardModelPosSetV(BoardStarMdlGet(), &pos);
	BoardSpaceRotGet(0, space, &rot);
	BoardModelRotYSet(BoardStarMdlGet(), rot.y);
	BoardModelVisibilitySet(BoardStarMdlGet(), 1);
}

s32 BoardSpaceStarGetNext(void)
{
	s16 random_pos;
	s16 star_total;
	s16 star_pos;
	star_total = GWSystem.star_total;
	star_pos = GWSystem.star_pos;
	if(BoardCurrGet() == 5) {
		s16 i;
		s32 count;
		s32 last_free;
		last_free = -1;
		for(count=i=0; i<8; i++) {
			if((1 << i) & GWSystem.star_flag) {
				count++;
			} else {
				last_free = i;
			}
		}
		if(count == 7) {
			if(BoardSpaceTypeGet(0, BoardSpaceStarGet(last_free)) == 10) {
				GWSystem.star_flag = 0;
			}
		}
	}
	begin:
	random_pos = BoardRandMod(8);
	if(star_pos == random_pos || BoardStarSpaceTypeGet(random_pos) == 10) {
		goto begin;
	}
	switch(GWSystem.board) {
		case 0:
			if(star_total >= 2) {
				break;
			}
			if(random_pos != 6 && random_pos != 7) {
				break;
			}
			goto begin;
			
		case 1:
			if(star_total >= 2) {
				break;
			}
			if(random_pos != 6 && random_pos != 7) {
				break;
			}
			goto begin;
		
		case 2:
			if(star_total == 1) {
				if(random_pos < 3 || random_pos > 5) {
					break;
				}
				goto begin;
			} else {
				if(star_total != 2) {
					break;
				}
				if(random_pos != 3 && random_pos != 4) {
					break;
				}
				goto begin;
			}
			
		case 3:
			if(star_total == 1) {
				if(random_pos < 5 || random_pos > 7) {
					break;
				}
				goto begin;
			} else {
				if(star_total != 2) {
					break;
				}
				if(random_pos == 5) {
					goto begin;
				}
				break;
			}
			
		case 4:
			if(star_total == 1) {
				if(random_pos <= 1 || random_pos >= 4) {
					goto begin;
				}
			}
			break;
			
		case 5:
			if(star_total == 1) {
				if(random_pos == 1 || random_pos == 4 || random_pos == 5) {
					goto begin;
				}
			}
			if(star_total != 2) {
				break;
			}
			if(random_pos == 5) {
				goto begin;
			}
	}
	if((1 << random_pos) & GWSystem.star_flag) {
		goto begin;
	}
	return random_pos;
}

s32 BoardSpaceStarGetRandom(s32 excl_pos)
{
	s8 new_pos;
	int i;
	for(i=0; i<1024; i++) {
		new_pos = BoardRandMod(8);
		if(new_pos == GWSystem.star_pos) {
			continue;
		}
		if(GWSystem.turn == 1 && new_pos <= 2) {
			continue;
		}
		if(new_pos != excl_pos) {
			break;
		}
	}
	return new_pos;
}

void BoardSpaceStarMove(void)
{
	u8 star_total;
	s16 star_pos;
	s16 star_next;
	if(_CheckFlag(FLAG_ID_MAKE(1, 1))) {
		star_pos = GWSystem.star_pos;
		GWSystem.star_flag |= (u8)(1 << star_pos);
		if(GWSystem.star_flag == 0xFF) {
			GWSystem.star_flag = 0;
		}
		if(GWSystem.star_total >= 99) {
			star_total = 99;
			GWSystem.star_total = star_total;
		} else {
			star_total = GWSystem.star_total++;
		}
	}
	star_next = BoardSpaceStarGetNext();
	BoardSpaceStarSetIndex(star_next);
}

s32 BoardSpaceStarGet(s32 index)
{
	return boardSpaceStarTbl[index & 0x7];
}

s32 BoardSpaceStarGetCurr(void)
{
	return BoardSpaceStarGet(GWSystem.star_pos);
}

s32 BoardSpaceStarCheck(s32 index)
{
	s32 ret;
	BoardSpace *space = BoardSpaceGet(0, index);
	BoardSpace *star_space;
	if(BoardCurrGet() == 7 || BoardCurrGet() == 8) {
		ret = 0;
		goto end;
	}
	star_space = BoardSpaceGet(0, boardSpaceStarTbl[GWSystem.star_pos]);
	if(space == star_space) {
		ret = 1;
	} else {
		ret = 0;
	}
	end:
	return ret;
}

void BoardSpaceLandExec(s32 player, s32 space)
{
	BoardSpace *space_ptr = BoardSpaceGet(0, space);
	switch(space_ptr->type) {
		case 1:
			GWPlayer[player].blue_count++;
			if(GWPlayer[player].blue_count > 99) {
				GWPlayer[player].blue_count = 99;
			}
			BoardLandBlueExec(player, space);
			break;
			
		case 2:
			GWPlayer[player].red_count++;
			if(GWPlayer[player].red_count > 99) {
				GWPlayer[player].red_count = 99;
			}
			BoardLandRedExec(player, space);
			break;
			
		case 3:
			GWPlayer[player].bowser_count++;
			if(GWPlayer[player].bowser_count > 99) {
				GWPlayer[player].bowser_count = 99;
			}
			BoardBowserExec(player, space);
			break;
			
		case 4:
			GWPlayer[player].mushroom_count++;
			if(GWPlayer[player].mushroom_count > 99) {
				GWPlayer[player].mushroom_count = 99;
			}
			BoardMushroomExec(player, space);
			break;
			
		case 5:
			GWPlayer[player].battle_count++;
			if(GWPlayer[player].battle_count > 99) {
				GWPlayer[player].battle_count = 99;
			}
			BoardBattleExec(player, space);
			break;
			
		case 6:
			GWPlayer[player].question_count++;
			if(GWPlayer[player].question_count > 99) {
				GWPlayer[player].question_count = 99;
			}
			if(_CheckFlag(FLAG_ID_MAKE(1, 11))) {
				HuAudFXPlay(842);
				BoardCameraViewSet(2);
				BoardPlayerAnimBlendSet(player, 0, 15);
				while(!BoardPlayerAnimBlendCheck(player)) {
					HuPrcVSleep();
				}
				BoardCameraMotionWait();
				BoardTutorialHookExec(16, 0);
			} else {
				if(landEventFunc) {
					HuAudFXPlay(842);
					omVibrate(player, 12, 4, 2);
					landEventFunc();
				}
			}
			GWPlayer[player].color = 3;
			break;
			
		case 7:
			GWPlayer[player].fortune_count++;
			if(GWPlayer[player].fortune_count > 99) {
				GWPlayer[player].fortune_count = 99;
			}
			BoardFortuneExec(player, space);
			break;
			
		case 9:
			GWPlayer[player].warp_count++;
			if(GWPlayer[player].warp_count > 99) {
				GWPlayer[player].warp_count = 99;
			}
			BoardWarpExec(player, space);
			break;
			
		case 8:
			BoardStarExec(player, space);
			break;
	}
}