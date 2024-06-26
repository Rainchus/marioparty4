#include "REL/executor.h"
#include "dolphin/os.h"
#include "rel_sqrt_consts.h"

void ObjectSetup(void) {
    OSReport("minigame dll setup\n");
}

unsigned char fn_1_CC(void) {
    return rand8();
}
