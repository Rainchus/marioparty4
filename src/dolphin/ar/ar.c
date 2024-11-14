#include "dolphin/ar.h"

#include "dolphin/hw_regs.h"
#include "dolphin/os.h"

static ARCallback __AR_Callback;
static u32 __AR_Size;
static u32 __AR_InternalSize;
static u32 __AR_ExpansionSize;

static u32 __AR_StackPointer;
static u32 __AR_FreeBlocks;
static u32* __AR_BlockLength;

static volatile BOOL __AR_init_flag = FALSE;

static void __ARHandler(__OSInterrupt interrupt, OSContext* context);
static void __ARChecksize(void);
static void __ARClearArea(u32 start_addr, u32 length);

ARCallback ARRegisterDMACallback(ARCallback callback) {
	ARCallback oldCb;
	BOOL enabled;
	oldCb = __AR_Callback;
	enabled = OSDisableInterrupts();
	__AR_Callback = callback;
	OSRestoreInterrupts(enabled);
	return oldCb;
}

u32 ARGetDMAStatus() {
	BOOL enabled;
	u32 val;
	enabled = OSDisableInterrupts();
	val = __DSPRegs[5] & 0x0200;
	OSRestoreInterrupts(enabled);
	return val;
}

void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length) {
	BOOL enabled;

	enabled = OSDisableInterrupts();

	__DSPRegs[16] = (u16)(__DSPRegs[16] & ~0x3ff) | (u16)(mainmem_addr >> 16);
	__DSPRegs[17] = (u16)(__DSPRegs[17] & ~0xffe0) | (u16)(mainmem_addr & 0xffff);
	__DSPRegs[18] = (u16)(__DSPRegs[18] & ~0x3ff) | (u16)(aram_addr >> 16);
	__DSPRegs[19] = (u16)(__DSPRegs[19] & ~0xffe0) | (u16)(aram_addr & 0xffff);
	__DSPRegs[20] = (u16)((__DSPRegs[20] & ~0x8000) | (type << 15));
	__DSPRegs[20] = (u16)(__DSPRegs[20] & ~0x3ff) | (u16)(length >> 16);
	__DSPRegs[21] = (u16)(__DSPRegs[21] & ~0xffe0) | (u16)(length & 0xffff);
	OSRestoreInterrupts(enabled);
}

u32 ARAlloc(u32 length) {
	u32 tmp;
	BOOL enabled;

	enabled = OSDisableInterrupts();
	tmp = __AR_StackPointer;
	__AR_StackPointer += length;
	*__AR_BlockLength = length;
	__AR_BlockLength++;
	__AR_FreeBlocks--;
	OSRestoreInterrupts(enabled);

	return tmp;
}

#if NONMATCHING
u32 ARFree(u32* length) {
	BOOL old;

	old = OSDisableInterrupts();

	__AR_BlockLength--;

	if (length) {
		*length = *__AR_BlockLength;
	}

	__AR_StackPointer -= *__AR_BlockLength;

	__AR_FreeBlocks++;

	OSRestoreInterrupts(old);

	return __AR_StackPointer;
}
#else
/* clang-format off */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm u32 ARFree(u32* length) {
	nofralloc
	mflr r0
	stw r0, 4(r1)
	stwu r1, -0x18(r1)
	stw r31, 0x14(r1)
	mr r31, r3
	bl OSDisableInterrupts
	lwz r4, __AR_BlockLength
	cmplwi r31, 0
	addi r0, r4, -4
	stw r0, __AR_BlockLength
	beq lbl_8036DAB4
	lwz r4, __AR_BlockLength
	lwz r0, 0(r4)
	stw r0, 0(r31)
lbl_8036DAB4:
	lwz r5, __AR_BlockLength
	lwz r4, __AR_FreeBlocks
	lwz r6, 0(r5)
	addi r0, r4, 1
	lwz r5, __AR_StackPointer
	stw r0, __AR_FreeBlocks
	subf r0, r6, r5
	stw r0, __AR_StackPointer
	bl OSRestoreInterrupts
	lwz r3, __AR_StackPointer
	lwz r0, 0x1c(r1)
	lwz r31, 0x14(r1)
	addi r1, r1, 0x18
	mtlr r0
	blr
}
#pragma pop
/* clang-format on */
#endif

BOOL ARCheckInit() { return __AR_init_flag; }

u32 ARInit(u32* stack_index_addr, u32 num_entries) {

	BOOL old;
	u16 refresh;

	if (__AR_init_flag == TRUE) {
		return 0x4000;
	}

	old = OSDisableInterrupts();

	__AR_Callback = NULL;

	__OSSetInterruptHandler(__OS_INTERRUPT_DSP_ARAM, __ARHandler);
	__OSUnmaskInterrupts(OS_INTERRUPTMASK_DSP_ARAM);

	__AR_StackPointer = 0x4000;
	__AR_FreeBlocks = num_entries;
	__AR_BlockLength = stack_index_addr;

	refresh = (u16)(__DSPRegs[13] & 0x000000ff);

	__DSPRegs[13] = (u16)((__DSPRegs[13] & ~0x000000ff) | (refresh & 0x000000ff));

	__ARChecksize();

	__AR_init_flag = TRUE;

	OSRestoreInterrupts(old);

	return __AR_StackPointer;
}

u32 ARGetBaseAddress(void) { return 0x4000; }

void ARSetSize(void)
{
	
}

u32 ARGetSize() { return __AR_Size; }

static void __ARHandler(__OSInterrupt interrupt, OSContext* context) {

	OSContext exceptionContext;
	u16 tmp;

	tmp = __DSPRegs[5];
	tmp = (u16)((tmp & ~0x00000088) | 0x20);
	__DSPRegs[5] = tmp;

	OSClearContext(&exceptionContext);
	OSSetCurrentContext(&exceptionContext);

	if (__AR_Callback) {
		(*__AR_Callback)();
	}

	OSClearContext(&exceptionContext);
	OSSetCurrentContext(context);
}

#define RoundUP32(x) (((u32)(x) + 32 - 1) & ~(32 - 1))

void __ARClearInterrupt(void) {

	u16 tmp;
	tmp = __DSPRegs[5];
	tmp = (u16)((tmp & ~(0x00000080 | 0x00000008)) | 0x00000020);
	__DSPRegs[5] = tmp;
}
u16 __ARGetInterruptStatus(void) { return ((u16)(__DSPRegs[5] & 0x0200)); }

static void __ARWaitForDMA(void) {

	while (__DSPRegs[5] & 0x0200) {
	}
}

static void __ARWriteDMA(u32 mmem_addr, u32 aram_addr, u32 length) {

	__DSPRegs[16] = (u16)((__DSPRegs[16] & ~0x03ff) | (u16)(mmem_addr >> 16));
	__DSPRegs[16 + 1] = (u16)((__DSPRegs[16 + 1] & ~0xffe0) | (u16)(mmem_addr & 0xffff));

	__DSPRegs[18] = (u16)((__DSPRegs[18] & ~0x03ff) | (u16)(aram_addr >> 16));
	__DSPRegs[18 + 1] = (u16)((__DSPRegs[18 + 1] & ~0xffe0) | (u16)(aram_addr & 0xffff));

	__DSPRegs[20] = (u16)(__DSPRegs[20] & ~0x8000);

	__DSPRegs[20] = (u16)((__DSPRegs[20] & ~0x03ff) | (u16)(length >> 16));
	__DSPRegs[20 + 1] = (u16)((__DSPRegs[20 + 1] & ~0xffe0) | (u16)(length & 0xffff));

	__ARWaitForDMA();

	__ARClearInterrupt();
}

static void __ARReadDMA(u32 mmem_addr, u32 aram_addr, u32 length) {

	__DSPRegs[16] = (u16)((__DSPRegs[16] & ~0x03ff) | (u16)(mmem_addr >> 16));
	__DSPRegs[16 + 1] = (u16)((__DSPRegs[16 + 1] & ~0xffe0) | (u16)(mmem_addr & 0xffff));

	__DSPRegs[18] = (u16)((__DSPRegs[18] & ~0x03ff) | (u16)(aram_addr >> 16));
	__DSPRegs[18 + 1] = (u16)((__DSPRegs[18 + 1] & ~0xffe0) | (u16)(aram_addr & 0xffff));

	__DSPRegs[20] = (u16)(__DSPRegs[20] | 0x8000);

	__DSPRegs[20] = (u16)((__DSPRegs[20] & ~0x03ff) | (u16)(length >> 16));
	__DSPRegs[20 + 1] = (u16)((__DSPRegs[20 + 1] & ~0xffe0) | (u16)(length & 0xffff));

	__ARWaitForDMA();

	__ARClearInterrupt();
}

static void __ARChecksize(void) {
	//TODO: Implement for this SDK version
}