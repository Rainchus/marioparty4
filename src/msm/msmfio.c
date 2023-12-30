#include "dolphin.h"

struct msmFio {
	BOOL (*open)(s32, DVDFileInfo *);
	BOOL (*read)(DVDFileInfo *, void *, s32, s32, s32);
	BOOL (*close)(DVDFileInfo *);
};

static struct msmFio fio;

BOOL msmFioClose(DVDFileInfo *fileInfo)
{
	return fio.close(fileInfo);
}

BOOL msmFioRead(DVDFileInfo *fileInfo, void *addr, s32 length, s32 offset)
{
	return fio.read(fileInfo, addr, length, offset, 2);
}

BOOL msmFioOpen(s32 entrynum, DVDFileInfo *fileInfo)
{
	return fio.open(entrynum, fileInfo);
}

void msmFioInit(void *open, void *read, void *close)
{
	if(open) {
		fio.open = open;
	} else {
		fio.open = DVDFastOpen;
	}
	if(read) {
		fio.read = read;
	} else {
		fio.read = DVDReadPrio;
	}
	if(close) {
		fio.close = close;
	} else {
		fio.close = DVDClose;
	}
}