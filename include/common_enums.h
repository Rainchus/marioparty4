#ifndef _COMMON_ENUMS_H
#define _COMMON_ENUMS_H

#include "types.h"

#define OVL_DEFINE(name, path) name,

typedef enum {
    #include "ovl_table.h"
    OVL_COUNT
} OverlayID;

#undef OVL_DEFINE

#define DATADIR_DEFINE(name, path) name,

typedef enum {
    #include "datadir_table.h"
    DATADIR_COUNT
} DataDirID;

#undef DATADIR_DEFINE


typedef enum {
    HEAP_SYSTEM,
    HEAP_MUSIC,
    HEAP_DATA,
    HEAP_DVD,
    HEAP_MISC,
    HEAP_MAX
} HeapID;

#endif