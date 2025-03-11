#include "cb/circular_buffer.h"
#include <stdio.h>

int main() {
    circular_buffer cb;
    CB_init(&cb);

    cb_buffer_struct data1 = {"data"};
    cb_buffer_struct data2 = {"test"};

    CB_push(&cb, data1);
    CB_push(&cb, data2);

    while (!CB_empty(&cb)) {
        cb_buffer_struct data = CB_pop(&cb);
        printf("Popped data: %s\n", data.buffer);
    }

    CB_free(&cb);
    return 0;
}
