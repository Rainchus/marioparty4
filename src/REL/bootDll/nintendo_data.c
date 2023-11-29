#include "common.h"

#include "logoNintendoData.inc"

void *logoReadNintendo(void)
{
    u32 *src = (u32 *)logoNintendoData;
    u32 size = *src++;
    void *dst = HuMemDirectMalloc(HEAP_DATA, size);
    int decode_type = *src++;
    if(dst) {
        HuDecodeData(src, dst, size, decode_type);
    }
    return dst;
}