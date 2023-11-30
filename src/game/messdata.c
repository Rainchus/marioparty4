#include "common.h"

static void *MessData_MesDataGet(void *messdata, u32 id)
{
    s32 i;
    s32 max_bank;
    u16 *banks;
    u16 bank;
    s32 *data;
    bank = id >> 16;
    data = messdata;
    max_bank = *data;
    data++;
    banks = (u16 *)(((u8 *)messdata)+(*data));
    for(i=max_bank; i != 0; i--, banks += 2) {
        if(*banks == bank) {
            break;
        }
    }
    if(i == 0) {
        return NULL;
    } else {
        data += banks[1];
        return (((u8 *)messdata)+(*data));
    }
}

static void *_MessData_MesPtrGet(void *messbank, u32 id)
{
    u16 index;
    s32 max_index;
    s32 *data;
    
    index = id & 0xFFFF;
    data = messbank;
    max_index = *data;
    data++;
    if(max_index <= index) {
        return NULL;
    } else {
        data =  data+index;
        return (((u8 *)messbank)+(*data));
    }
}

void *MessData_MesPtrGet(void *messdata, u32 id)
{
    void *bank = MessData_MesDataGet(messdata, id);
    if(bank) {
        return _MessData_MesPtrGet(bank, id);
    }
    return NULL;
}