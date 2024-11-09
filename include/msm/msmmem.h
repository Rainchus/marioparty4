#ifndef MSMMEM_H
#define MSMMEM_H

#include "dolphin/types.h"

void msmMemFree(void *);
void *msmMemAlloc(u32);
void msmMemInit(void *, u32);

#endif
