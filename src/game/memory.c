#include "common.h"

struct memory_block {
    u32 size;
    u8 magic;
    u8 flag;
    struct memory_block *prev;
    struct memory_block *next;
    int num;
    u32 retaddr;
};

static void *HuMemMemoryAlloc2(void *heap_ptr, u32 size, int num, u32 retaddr);

void *HuMemHeapInit(void *ptr, u32 size)
{
    struct memory_block *block = ptr;
    block->size = size;
    block->magic = 205;
    block->flag = 0;
    block->prev = block;
    block->next = block;
    block->num = -256;
    block->retaddr = 0xCDCDCDCD;
    return block;
}

void *HuMemMemoryAllocNum(void *heap_ptr, u32 size, int num, u32 retaddr)
{
    return HuMemMemoryAlloc2(heap_ptr, size, num, retaddr);
}

void *HuMemMemoryAlloc(void *heap_ptr, u32 size, u32 retaddr)
{
    return HuMemMemoryAlloc2(heap_ptr, size, -256, retaddr);
}

static void *HuMemMemoryAlloc2(void *heap_ptr, u32 size, int num, u32 retaddr)
{
    
}