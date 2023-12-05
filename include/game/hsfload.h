#ifndef _HSFLOAD_H
#define _HSFLOAD_H

#include "game/hsfformat.h"

HsfData *LoadHSF(void *data);
void ClusterAdjustObject(HsfData *model, HsfData *src_model);
char *SetName(u32 *str_ofs);
char *MakeObjectName(char *name);
int CmpObjectName(char *name1, char *name2);

#endif