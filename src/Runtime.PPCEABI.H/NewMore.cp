#include "PowerPC_EABI_Support/Runtime/New.h"

namespace std {
    class exception {
        public:
            virtual ~exception();
            virtual const char *what() const;
    };
}

const char *std::exception::what() const {
    return "exception";
};

std::exception::~exception() {};
