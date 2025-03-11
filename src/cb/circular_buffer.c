#include "cb/circular_buffer.h"

void CB_init(circular_buffer* cb) {
    cb->read_offset = 0;
    cb->write_offset = 0;
    cb->count = 0;
    cb->size = CIRCULAR_BUFFER_SIZE;
}

void CB_free(circular_buffer* cb) {
    // No dynamic memory to free in this implementation
}

bool CB_push(circular_buffer* cb, cb_buffer_struct data) {
    if (CB_full(cb)) {
        return false;
    }
    cb->buffer[cb->write_offset] = data;
    cb->write_offset = (cb->write_offset + 1) % cb->size;
    cb->count++;
    return true;
}

cb_buffer_struct CB_pop(circular_buffer* cb) {
    cb_buffer_struct data = {0};
    if (CB_empty(cb)) {
        return data;
    }
    data = cb->buffer[cb->read_offset];
    cb->read_offset = (cb->read_offset + 1) % cb->size;
    cb->count--;
    return data;
}

bool CB_full(circular_buffer* cb) {
    return cb->count == cb->size;
}

bool CB_empty(circular_buffer* cb) {
    return cb->count == 0;
}
