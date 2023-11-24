#include "common.h"
#include "dolphin/dvd.h"

#define PTR_OFFSET(ptr, offset) (void *)(((u8 *)(ptr)+(u32)(offset)))
#define DATA_EFF_SIZE(size) (((size)+1) & ~0x1)

extern void *HuARDirCheck(s32 dir);
extern void HuAR_ARAMtoMRAM(void *dst);
extern void HuAR_ARAMtoMRAMNum(void *dst, s32 num);
extern BOOL HuARDMACheck();

void HuDataDirClose(s32 data_num);
void **HuDataReadMultiSub(s32 *data_ids, BOOL use_num, s32 num);

#define DATA_MAX_READSTAT 128

#define DATADIR_DEFINE(name, path) { path, -1 },

static FileListEntry DataDirStat[DATADIR_COUNT+1] = {
    #include "datadir_table.h"
    { NULL, -1 }
};

#undef DATADIR_DEFINE

static u32 DataDirMax;
static DataStat ReadDataStat[DATA_MAX_READSTAT];

void HuDataInit()
{
    int i = 0;
    FileListEntry *dir_stat = DataDirStat;
    DataStat *read_stat;
    while(dir_stat->name) {
        if((dir_stat->file_id = DVDConvertPathToEntrynum(dir_stat->name)) == -1) {
            OSReport("data.c: Data File Error(%s)\n", dir_stat->name);
            OSPanic("data.c", 65, "\n");
        }
        i++;
        dir_stat++;
    }
    DataDirMax = i;
    for(i=0, read_stat = ReadDataStat; i<DATA_MAX_READSTAT; i++, read_stat++) {
        read_stat->dir_id = -1;
        read_stat->used = FALSE;
        read_stat->status = 0;
    }
}

static int HuDataStatusGet()
{
    int i;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].dir_id == -1) {
            break;
        }
    }
    if(i >= DATA_MAX_READSTAT) {
        i = -1;
    }
    return i;
}

int HuDataReadChk(s32 data_num)
{
    int i;
    data_num >>= 16;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].dir_id == data_num && ReadDataStat[i].status != 1) {
            break;
        }
    }
    if(i >= DATA_MAX_READSTAT) {
        i = -1;
    }
    return i;
}

DataStat *HuDataGetStatus(void *dir_ptr)
{
    int i;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].dir == dir_ptr) {
            break;
        }
    }
    if(i > DATA_MAX_READSTAT) {
        return NULL;
    }
    return &ReadDataStat[i];
}

void *HuDataGetDirPtr(s32 data_num)
{
    int status = HuDataReadChk(data_num);
    if(status < 0) {
        return NULL;
    }
    return ReadDataStat[status].dir;
}

DataStat *HuDataDirRead(s32 data_num)
{
    DataStat *status;
    int status_id;
    s32 dir_id;
    dir_id  = data_num >> 16;
    if(DataDirMax <= dir_id) {
        OSReport("data.c: Data Number Error(%d)\n", data_num);
        return NULL;
    }
    
    if((status_id = HuDataReadChk(data_num)) < 0) {
        void *dir_aram;
        if((dir_aram = HuARDirCheck(data_num))) {
            HuAR_ARAMtoMRAM(dir_aram);
            while(HuARDMACheck());
            status_id = HuDataReadChk(data_num);
            status = &ReadDataStat[status_id];
        } else {
            status_id = HuDataStatusGet();
            if(status_id == -1) {
                OSReport("data.c: Data Work Max Error\n");
                return NULL;
            }
            status = &ReadDataStat[status_id];
            status->dir = HuDvdDataFastRead(DataDirStat[dir_id].file_id);
            if(status->dir) {
                status->dir_id = dir_id;
            }
        }
    } else {
        status = &ReadDataStat[status_id];
    }
    return status;
}

DataStat *HuDataDirReadNum(s32 data_num, s32 num)
{
    DataStat *status;
    int status_id;
    s32 dir_id;
    dir_id  = data_num >> 16;
    if(DataDirMax <= dir_id) {
        OSReport("data.c: Data Number Error(%d)\n", data_num);
        return NULL;
    }
    
    if((status_id = HuDataReadChk(data_num)) < 0) {
        void *dir_aram;
        if((dir_aram = HuARDirCheck(data_num))) {
            OSReport("ARAM data num %x\n", data_num);
            HuAR_ARAMtoMRAMNum(dir_aram, num);
            while(HuARDMACheck());
            status_id = HuDataReadChk(data_num);
            status = &ReadDataStat[status_id];
            status->used = TRUE;
            status->num = num;
        } else {
            OSReport("data num %x\n", data_num);
            status_id = HuDataStatusGet();
            if(status_id == -1) {
                OSReport("data.c: Data Work Max Error\n");
                return NULL;
            }
            status = &ReadDataStat[status_id];
            status->dir = HuDvdDataFastReadNum(DataDirStat[dir_id].file_id, num);
            if(status->dir) {
                status->dir_id = dir_id;
                status->used = TRUE;
                status->num = num;
            }
        }
    } else {
        status = &ReadDataStat[status_id];
    }
    return status;
}

DataStat *HuDataDirSet(void *dir_ptr, s32 data_num)
{
    DataStat *status = HuDataGetStatus(dir_ptr);
    int status_id;
    if((status_id = HuDataReadChk(status->dir_id << 16)) >= 0) {
        HuDataDirClose(data_num);
    }
    if((status_id = HuDataStatusGet()) == -1) {
        OSReport("data.c: Data Work Max Error\n");
        return NULL;
    } else {
        status = &ReadDataStat[status_id];
        status->dir = dir_ptr;
        status->dir_id = data_num >>16;
        return status;
    }
}

void HuDataDirReadAsyncCallBack(s32 result, DVDFileInfo* fileInfo)
{
    DataStat *status;
    int i;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].status == 1 && ReadDataStat[i].file_info.startAddr == fileInfo->startAddr) {
            break;
        }
    }
    if(i >= DATA_MAX_READSTAT) {
        OSPanic("data.c", 358, "dvd.c AsyncCallBack Error");
    }
    status = &ReadDataStat[i];
    status->status = 0;
    DVDClose(&status->file_info);
}

s32 HuDataDirReadAsync(s32 data_num)
{
    DataStat *status;
    int status_id;
    s32 dir_id;
    dir_id  = data_num >> 16;
    if(DataDirMax <= dir_id) {
        OSReport("data.c: Data Number Error(%d)\n", data_num);
        return -1;
    }
    if((status_id = HuDataReadChk(data_num)) < 0) {
        void *dir_aram;
        dir_aram = HuARDirCheck(data_num);
        if(dir_aram) {
            OSReport("ARAM data num %x\n", data_num);
            HuAR_ARAMtoMRAM(dir_aram);
            status_id = 0x10000;
        } else {
            status_id = HuDataStatusGet();
            if(status_id == -1) {
                OSReport("data.c: Data Work Max Error\n");
                return -1;
            }
            status = &ReadDataStat[status_id];
            status->status = 1;
            status->dir_id = dir_id;
            status->dir = HuDvdDataFastReadAsync(DataDirStat[dir_id].file_id, status);
        }
    } else {
        status_id = -1;
    }
    return status_id;
}

s32 HuDataDirReadNumAsync(s32 data_num, s32 num)
{
    DataStat *status;
    int status_id;
    s32 dir_id;
    dir_id  = data_num >> 16;
    if(DataDirMax <= dir_id) {
        OSReport("data.c: Data Number Error(%d)\n", data_num);
        return -1;
    }
    if((status_id = HuDataReadChk(data_num)) < 0) {
        if((status_id = HuDataStatusGet()) == -1) {
            OSReport("data.c: Data Work Max Error\n");
            return -1;
        }
        ReadDataStat[status_id].status = TRUE;
        ReadDataStat[status_id].dir_id = dir_id;
        status = &ReadDataStat[status_id];
        status->used = TRUE;
        status->num = num;
        status->dir = HuDvdDataFastReadAsync(DataDirStat[dir_id].file_id, status);
    } else {
        status_id = -1;
    }
    return status_id;
}

BOOL HuDataGetAsyncStat(s32 status)
{
    if(status == 0x10000) {
        return HuARDMACheck() == 0;
    } else {
        return ReadDataStat[status].status == 0;
    }
}

static void GetFileInfo(DataStat *status, s32 file_num)
{
    u32 *temp_ptr;
    temp_ptr = (u32 *)PTR_OFFSET(status->dir, (file_num * 4))+1;
    status->file = PTR_OFFSET(status->dir, *temp_ptr);
    temp_ptr = status->file;
    status->raw_len = *temp_ptr++;
    status->comp_type = *temp_ptr++;
    status->file = temp_ptr;
}

void *HuDataRead(s32 data_num)
{
    DataStat *status;
    int status_id;
    void *buf;
    if(!HuDataDirRead(data_num)) {
        (void)data_num;
        return NULL;
    }
    if((status_id = HuDataReadChk(data_num)) == -1) {
        return NULL;
    }
    status = &ReadDataStat[status_id];
    GetFileInfo(status, data_num & 0xFFFF);
    buf = HuMemDirectMalloc(0, DATA_EFF_SIZE(status->raw_len));
    if(buf) {
        HuDecodeData(status->file, buf, status->raw_len, status->comp_type);
    }
    return buf;
}

void *HuDataReadNum(s32 data_num, s32 num)
{
    DataStat *status;
    int status_id;
    void *buf;
    if(!HuDataDirReadNum(data_num, num)) {
        return NULL;
    }
    if((status_id = HuDataReadChk(data_num)) == -1) {
        return NULL;
    }
    status = &ReadDataStat[status_id];
    GetFileInfo(status, data_num & 0xFFFF);
    buf = HuMemDirectMallocNum(0, DATA_EFF_SIZE(status->raw_len), num);
    if(buf) {
        HuDecodeData(status->file, buf, status->raw_len, status->comp_type);
    }
    return buf;
}

void *HuDataSelHeapRead(s32 data_num, HeapID heap)
{
    DataStat *status;
    int status_id;
    void *buf;
    if(!HuDataDirRead(data_num)) {
        return NULL;
    }
    if((status_id = HuDataReadChk(data_num)) == -1) {
        return NULL;
    }
    status = &ReadDataStat[status_id];
    GetFileInfo(status, data_num & 0xFFFF);
    switch(heap) {
        case HEAP_MUSIC:
            buf = HuMemDirectMalloc(HEAP_MUSIC, DATA_EFF_SIZE(status->raw_len));
            break;
            
        case HEAP_DATA:
            buf = HuMemDirectMalloc(HEAP_DATA, DATA_EFF_SIZE(status->raw_len));
            break;
            
        case HEAP_DVD:
            buf = HuMemDirectMalloc(HEAP_DVD, DATA_EFF_SIZE(status->raw_len));
            break;
            
        default:
            buf = HuMemDirectMalloc(HEAP_SYSTEM, DATA_EFF_SIZE(status->raw_len));
            break;
    }
    if(buf) {
        HuDecodeData(status->file, buf, status->raw_len, status->comp_type);
    }
    return buf;
}

void *HuDataSelHeapReadNum(s32 data_num, s32 num, HeapID heap)
{
    DataStat *status;
    int status_id;
    void *buf;
    if(!HuDataDirReadNum(data_num, num)) {
        return NULL;
    }
    if((status_id = HuDataReadChk(data_num)) == -1) {
        return NULL;
    }
    status = &ReadDataStat[status_id];
    GetFileInfo(status, data_num & 0xFFFF);
    switch(heap) {
        case HEAP_MUSIC:
            buf = HuMemDirectMalloc(HEAP_MUSIC, DATA_EFF_SIZE(status->raw_len));
            break;
            
        case HEAP_DATA:
            buf = HuMemDirectMallocNum(HEAP_DATA, DATA_EFF_SIZE(status->raw_len), num);
            break;
            
        case HEAP_DVD:
            buf = HuMemDirectMallocNum(HEAP_DVD, DATA_EFF_SIZE(status->raw_len), num);
            break;
            
        default:
            buf = HuMemDirectMallocNum(HEAP_SYSTEM, DATA_EFF_SIZE(status->raw_len), num);
            break;
    }
    if(buf) {
        HuDecodeData(status->file, buf, status->raw_len, status->comp_type);
    }
    return buf;
}

void **HuDataReadMulti(s32 *data_ids)
{
    return HuDataReadMultiSub(data_ids, FALSE, 0);
}

void **HuDataReadMultiSub(s32 *data_ids, BOOL use_num, s32 num)
{
    s32 *dir_ids;
    char **paths;
    void **dir_ptrs;
    void **out_ptrs;
    int i, count, total_files;
    u32 dir_id;
    for(i=0, count=0; data_ids[i] != -1; i++) {
        dir_id = data_ids[i] >> 16;
        if(DataDirMax <= dir_id) {
            OSReport("data.c: Data Number Error(%d)\n", data_ids[i]);
            return NULL;
        }
        if(HuDataReadChk(data_ids[i]) < 0) {
            count++;
        }
    }
    total_files = i;
    dir_ids = HuMemDirectMalloc(HEAP_SYSTEM, (count+1)*sizeof(s32));
    for(i=0; i<count+1; i++) {
        dir_ids[i] = -1;
    }
    paths = HuMemDirectMalloc(HEAP_SYSTEM, (count+1)*sizeof(char *));
    for(i=0, count=0; data_ids[i] != -1; i++) {
        dir_id = data_ids[i] >> 16;
        if(HuDataReadChk(data_ids[i]) < 0) {
            int j;
            for(j=0; dir_ids[j] != -1; j++) {
                if(dir_ids[j] == dir_id){
                    break;
                }
            }
            if(dir_ids[j] == -1) {
                dir_ids[j] = dir_id;
                paths[count++] = DataDirStat[dir_id].name;
            }
        }
    }
    dir_ptrs = HuDvdDataReadMulti(paths);
    for(i=0; dir_ids[i] != -1; i++) {
        s32 status;
        if((status = HuDataStatusGet()) == -1) {
            OSReport("data.c: Data Work Max Error\n");
            (void)count;
            HuMemDirectFree(paths);
            HuMemDirectFree(dir_ids);
            return NULL;
        } else {
            ReadDataStat[status].dir = dir_ptrs[i];
            ReadDataStat[status].dir_id = dir_ids[i];
        }
    }
    HuMemDirectFree(dir_ids);
    HuMemDirectFree(paths);
    HuMemDirectFree(dir_ptrs);
    if(use_num) {
        out_ptrs = HuMemDirectMallocNum(HEAP_SYSTEM, (total_files+1)*sizeof(void *), num);
    } else {
        out_ptrs = HuMemDirectMalloc(HEAP_SYSTEM, (total_files+1)*sizeof(void *));
    }
    for(i=0; data_ids[i] != -1; i++) {
        if(use_num) {
            out_ptrs[i] = HuDataReadNum(data_ids[i], num);
        } else {
            out_ptrs[i] = HuDataRead(data_ids[i]);
        }
    }
    out_ptrs[i] = NULL;
    return out_ptrs;
}

s32 HuDataGetSize(s32 data_num)
{
    DataStat *status;
    int status_id;
    if((status_id = HuDataReadChk(data_num)) == -1) {
        return -1;
    }
    status = &ReadDataStat[status_id];
    GetFileInfo(status, data_num & 0xFFFF);
    return DATA_EFF_SIZE(status->raw_len);
}

void HuDataClose(void *ptr)
{
    if(ptr) {
        HuMemDirectFree(ptr);
    }
}

void HuDataCloseMulti(void **ptrs)
{
    int i;
    for(i=0; ptrs[i]; i++) {
        void *ptr = ptrs[i];
        if(ptr) {
            HuMemDirectFree(ptr);
        }
    }
    if(ptrs) {
        HuMemDirectFree(ptrs);
    }
}

void HuDataDirClose(s32 data_id)
{
    DataStat *status;
    int i;
    s32 dir_id = data_id >> 16;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].dir_id == dir_id) {
            break;
        }
    }
    if(i >= DATA_MAX_READSTAT) {
        return;
    }
    status = &ReadDataStat[i];
    if(status->status == 1) {
        OSPanic("data.c", 812, "data.c: Async Close Error\n");
    }
    status->dir_id = -1;
    HuDvdDataClose(status->dir);
    status->dir = NULL;
    status->used = FALSE;
    status->status = 0;
}

void HuDataDirCloseNum(s32 num)
{
    DataStat *status;
    int i;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].used == TRUE && ReadDataStat[i].num == num) {
            HuDataDirClose(ReadDataStat[i].dir_id << 16);
        }
    }
}