#include "common.h"

extern int __OSCurrHeap;

static u32 HeapSizeTbl[5] = { 0x240000, 0x140000, 0xA80000, 0x580000, 0x6B1C0 };
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
    free_size = OSCheckHeap(__OSCurrHeap);
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
    register void *retaddr;
    asm {
        mflr retaddr
    }
    size = (size+31) & 0xFFFFFFE0;
    return HuMemMemoryAlloc(HeapTbl[heap], size, retaddr);
}
