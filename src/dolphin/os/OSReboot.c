#include <dolphin/dvd.h>
#include <dolphin/os.h>
#include <dolphin/os/OSBootInfo.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>

typedef struct ApploaderHeader {
    // total size: 0x20
    char date[16]; // offset 0x0, size 0x10
    u32 entry; // offset 0x10, size 0x4
    u32 size; // offset 0x14, size 0x4
    u32 rebootSize; // offset 0x18, size 0x4
    u32 reserved2; // offset 0x1C, size 0x4
} ApploaderHeader;

struct {
    // total size: 0x1C
    int valid; // offset 0x0, size 0x4
    unsigned long restartCode; // offset 0x4, size 0x4
    unsigned long bootDol; // offset 0x8, size 0x4
    void *regionStart; // offset 0xC, size 0x4
    void *regionEnd; // offset 0x10, size 0x4
    int argsUseDefault; // offset 0x14, size 0x4
    void *argsAddr; // offset 0x18, size 0x4
} __OSRebootParams; // size: 0x1C, address: 0x0

static ApploaderHeader Header;

extern void *__OSSavedRegionStart;
extern void *__OSSavedRegionEnd;

static void *SaveStart = NULL;
static void *SaveEnd = NULL;

volatile u8 DAT_800030e2 : 0x800030e2;

extern u32 BOOT_REGION_START AT_ADDRESS(0x812FDFF0); //(*(u32 *)0x812fdff0)
extern u32 BOOT_REGION_END AT_ADDRESS(0x812FDFEC); //(*(u32 *)0x812fdfec)
extern u32 UNK_HOT_RESET1 AT_ADDRESS(0x817ffff8);
extern u32 UNK_HOT_RESET2 AT_ADDRESS(0x817ffffc);
// extern u32 OS_RESET_CODE AT_ADDRESS(0x800030F0);
// extern u8 OS_REBOOT_BOOL AT_ADDRESS(0x800030E2); // unknown function, set to true by __OSReboot

extern u32 __OSIsGcam;

static BOOL Prepared = FALSE;

extern void __DVDPrepareResetAsync(DVDCBCallback callback);
extern BOOL DVDCheckDisk(void);
extern BOOL DVDReadAbsAsyncForBS(DVDCommandBlock *block, void *addr, s32 length, s32 offset, DVDCBCallback callback);

void Run(register u32 addr)
{
    OSDisableInterrupts();
    ICFlashInvalidate();
    // clang-format off
	asm {
	    sync
	    isync
	    mtlr addr
	    blr
	}
    // clang-format on
}

static void Callback()
{
    Prepared = TRUE;
}

void ReadApploader(OSTime time1) { }

void __OSReboot(u32 resetCode, u32 bootDol)
{
    // TODO
}

void OSSetSaveRegion(void *start, void *end)
{
    SaveStart = start;
    SaveEnd = end;
}

void OSGetSaveRegion(void **start, void **end)
{
    *start = SaveStart;
    *end = SaveEnd;
}

void OSGetSavedRegion(void **start, void **end)
{
    *start = __OSSavedRegionStart;
    *end = __OSSavedRegionEnd;
}
