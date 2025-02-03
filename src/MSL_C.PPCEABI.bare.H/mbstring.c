#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/ansi_files.h"

static int unicode_to_UTF8(char* s, wchar_t wchar) {
    int number_of_bytes;
    char* target_ptr;
    char first_byte_mark[4] = {0x00, 0x00, 0xc0, 0xe0};

    if (!s) {
        return 0;
    }

    if (wchar < 0x0080)
        number_of_bytes = 1;
    else if (wchar < 0x0800)
        number_of_bytes = 2;
    else
        number_of_bytes = 3;

    target_ptr = s + number_of_bytes;

    switch (number_of_bytes) {
    case 3:
        *--target_ptr = (wchar & 0x003f) | 0x80;
        wchar >>= 6;
    case 2:
        *--target_ptr = (wchar & 0x003f) | 0x80;
        wchar >>= 6;
    case 1:
        *--target_ptr = wchar | first_byte_mark[number_of_bytes];
    }

    return (number_of_bytes);
}

static inline int wctomb(char* s, wchar_t wchar) {
	return (unicode_to_UTF8(s, wchar));
}

size_t wcstombs(char* s, const wchar_t* pwcs, size_t n) {
    int chars_written = 0;
    int result;
    char temp[3];
    wchar_t* source;

    if (!s || !pwcs)
        return (0);

    source = (wchar_t*)pwcs;
    while (chars_written <= n) {
        if (!*source) {
            *(s + chars_written) = '\0';
            break;
        } else {
            result = wctomb(temp, *source++);
            if ((chars_written + result) <= n) {
                strcat(s + chars_written, temp, result);
                chars_written += result;
            } else
                break;
        }
    }

    return (chars_written);
}
