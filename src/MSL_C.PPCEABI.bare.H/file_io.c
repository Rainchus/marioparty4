#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"

int fclose(FILE* file) {
    int flush_result, close_result;

    if (file == NULL) {
        return -1;
    }
    if (file->file_mode.file_kind == __closed_file) {
        return 0;
    }
    flush_result = fflush(file);
    close_result = file->close_fn(file->handle);
    file->file_mode.file_kind = __closed_file;
    file->handle = NULL;
    if (file->file_state.free_buffer) {
        free(file->buffer);
    }
    return (flush_result || close_result) ? -1 : 0;
}

int fflush(FILE* file) {
    unsigned long pos;

    if (file == NULL) {
        return __flush_all();
    }
    if (file->file_state.error != 0 || file->file_mode.file_kind == __closed_file) {
        return -1;
    }
    if (file->file_mode.io_mode == __read) {
        return 0;
    }
    if (file->file_state.io_state >= __rereading) {
        file->file_state.io_state = __reading;
    }
    if (file->file_state.io_state == __reading) {
        file->buffer_length = 0;
    }
    if (file->file_state.io_state != __writing) {
        file->file_state.io_state = __neutral;
        return 0;
    }
    if (file->file_mode.file_kind != __disk_file) {
        pos = 0;
    } else {
        pos = ftell(file);
    }
    if (__flush_buffer(file, 0) != __no_io_error) {
        file->file_state.error = 1;
        file->buffer_length = 0;
        return -1;
    }
    file->file_state.io_state = __neutral;
    file->position = pos;
    file->buffer_length = 0;
    return 0;
}
