#include "common.h"


#define OVL_DEFINE(name, path) { path, 0 },

FileListEntry _ovltbl[OVL_COUNT+1] = {
    #include "ovl_table.h"
    { NULL, -1 }
};

#undef OVL_DEFINE