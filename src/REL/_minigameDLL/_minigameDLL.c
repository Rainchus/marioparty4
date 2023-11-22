#include "common.h"
#include "REL/executor.h"
#include "dolphin/os.h"

void ModuleProlog(void) {
    OSReport("minigame dll setup\n");
}

unsigned char fn_1_CC(void) {
    return rand8();
}