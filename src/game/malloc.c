#include "common.h"

extern int __OSCurrHeap;
extern int currentHeapHandle;

static u32 HeapSizeTbl[5] = { 0x240000, 0x140000, 0xA80000, 0x580000, 0 };
static void *HeapTbl[5];

void HuMemInitAll(void)
{
    int i;
    void *ptr;
    u32 free_size;
    for(i=0; i<4; i++) {
        ptr = OSAllocFromHeap(__OSCurrHeap, HeapSizeTbl[i]);
        if(ptr == NULL) {
            OSReport("HuMem> Failed OSAlloc Size:%d\n", HeapSizeTbl[i]);
            return;
        }
        HeapTbl[i] = HuMemInit(ptr, HeapSizeTbl[i]);
    }
    free_size = OSCheckHeap(currentHeapHandle);
    OSReport("HuMem> left memory space %dKB(%d)\n", free_size/1024, free_size);
    ptr = OSAllocFromHeap(__OSCurrHeap, free_size);
    if(ptr == NULL) {
        OSReport("HuMem> Failed OSAlloc left space\n");
        return;
    }
    HeapTbl[4] = HuMemInit(ptr, free_size);
    HeapSizeTbl[4] = free_size;
}

void *HuMemInit(void *ptr, u32 size)
{
    return HuMemHeapInit(ptr, size);
}

void HuMemDCFlushAll()
{
    HuMemDCFlush(2);
    HuMemDCFlush(0);
}

void HuMemDCFlush(int heap)
{
    DCFlushRangeNoSync(HeapTbl[heap], HeapSizeTbl[heap]);
}

void *HuMemDirectMalloc(int heap, u32 size)
{
    register u32 retaddr;
    asm {
        mflr retaddr
    }
    size = (size+31) & 0xFFFFFFE0;
    return HuMemMemoryAlloc(HeapTbl[heap], size, retaddr);
}

void *HuMemDirectMallocNum(int heap, u32 size, int num)
{
    register u32 retaddr;
    asm {
        mflr retaddr
    }
    size = (size+31) & 0xFFFFFFE0;
    return HuMemMemoryAllocNum(HeapTbl[heap], size, num, retaddr);
}

void HuMemDirectFree(void *ptr)
{
    register u32 retaddr;
    asm {
        mflr retaddr
    }
    HuMemMemoryFree(ptr, retaddr);
}

void HuMemDirectFreeNum(int heap, int num)
{
    register u32 retaddr;
    asm {
        mflr retaddr
    }
    HuMemMemoryFreeNum(HeapTbl[heap], num, retaddr);
}

u32 HuMemUsedMallocSizeGet(int heap)
{
    return HuMemUsedMemorySizeGet(HeapTbl[heap]);
}

u32 HuMemUsedMallocBlockGet(int heap)
{
    return HuMemUsedMemoryBlockGet(HeapTbl[heap]);
}

u32 HuMemHeapSizeGet(int heap)
{
    return HeapSizeTbl[heap];
}

void *HuMemHeapPtrGet(int heap)
{
    return HeapTbl[heap];
}