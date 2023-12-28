#include "include/REL/w10Dll.h"

void fn_1_0(void) {
    BoardInit(&fn_1_E0, &fn_1_6D8);
}

int _prolog(void) {
    const VoidFunc* ctors = _ctors;
    while (*ctors != 0) {
        (**ctors)();
        ctors++;
    }
	fn_1_0();
    return 0;
}

void _epilog(void) {
    const VoidFunc* dtors = _dtors;
    while (*dtors != 0) {
        (**dtors)();
        dtors++;
    }
}