#ifndef _MSL_COMMON_ANSI_FILES_H
#define _MSL_COMMON_ANSI_FILES_H

#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

typedef unsigned long __file_handle;
typedef unsigned long fpos_t;
#ifndef __cplusplus
typedef unsigned short wchar_t;
#endif

#define set_error(file)                                                        \
	do {                                                                       \
		(file)->file_state.error = 1;                                          \
		(file)->buffer_length    = 0;                                          \
	} while (0)

enum __file_kinds {
	__closed_file,
	__disk_file,
	__console_file,
	__string_file,
	__unavailable_file
};

enum __file_orientation {
	/* 0x0 */ UNORIENTED,
	/* 0x1 */ CHAR_ORIENTED,
	/* 0x2 */ WIDE_ORIENTED
};

typedef struct _file_modes {
	unsigned int open_mode : 2;
	unsigned int io_mode : 3;
	unsigned int buffer_mode : 2;
	unsigned int file_kind : 3;
	unsigned int file_orientation : 2;
	unsigned int binary_io : 1;
} file_modes;

enum __io_modes {
	__read       = 1,
	__write      = 2,
	__read_write = 3,
	__append     = 4
};

enum __io_states {
	__neutral,
	__writing,
	__reading,
	__rereading
};

enum __io_results {
	__no_io_error,
	__io_error,
	__io_EOF
};

typedef struct _file_states {
	unsigned int io_state : 3;
	unsigned int free_buffer : 1;
	unsigned char eof;
	unsigned char error;
} file_states;

typedef void (*__idle_proc)(void);
typedef int (*__pos_proc)(__file_handle file, fpos_t* position, int mode,
                          __idle_proc idle_proc);
typedef int (*__io_proc)(__file_handle file, unsigned char* buff, size_t* count,
                         __idle_proc idle_proc);
typedef int (*__close_proc)(__file_handle file);

typedef struct _FILE {
	__file_handle handle;
	file_modes file_mode;
	file_states file_state;

	unsigned char is_dynamically_allocated;
	char char_buffer;
	char char_buffer_overflow;
	char ungetc_buffer[2];
	wchar_t ungetc_wide_buffer[2];

	unsigned long position;
	unsigned char* buffer;
	unsigned long buffer_size;
	unsigned char* buffer_ptr;
	unsigned long buffer_length;
	unsigned long buffer_alignment;
	unsigned long save_buffer_length;
	unsigned long buffer_position;

	__pos_proc position_fn;
	__io_proc read_fn;
	__io_proc write_fn;
	__close_proc close_fn;
	__idle_proc idle_fn;
	struct _FILE* next_file_struct;
} FILE;

#define _IONBF 0
#define _IOLBF 1
#define _IOFBF 2

extern FILE __files[];
extern int __close_console(__file_handle file);
extern int __write_console(__file_handle file, unsigned char* buf,
                           size_t* count, __idle_proc idle_fn);
extern int __read_console(__file_handle file, unsigned char* buf, size_t* count,
                          __idle_proc idle_fn);

unsigned int __flush_all(void);
void __close_all(void);

#ifdef __cplusplus
};
#endif

#endif /* _MSL_COMMON_ANSI_FILES_H */
