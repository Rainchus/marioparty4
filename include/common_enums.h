#ifndef _COMMON_ENUMS_H
#define _COMMON_ENUMS_H

#include "types.h"

#define OVL_DEFINE(name, path) name,

typedef enum {
    #include "ovl_table.h"
    OVL_COUNT
} OverlayID;

#undef OVL_DEFINE

#endif
