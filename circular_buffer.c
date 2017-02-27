
#include "circular_buffer.h"

void CB_init(circular_buffer* cb)
{        
    cb->size = CIRCULAR_BUFFER_SIZE; 
    cb->read_offset = 0;
    cb->write_offset = 0;
    cb->count = 0;
}

void CB_free(circular_buffer* cb)
{
    free(cb);
}

bool CB_push(circular_buffer* cb, cb_buffer_struct data)
{
    if (cb == NULL || cb->buffer == NULL)
        return false;

    if (CB_full(cb))
        printf("warning: circular buffer is full. failed to push data to circular buffer. \n");
    else{
        //cb->buffer[write_offset] = data;
        *(cb->buffer + cb->write_offset) = data;   
        cb->write_offset+=1;
        cb->count+=1;
    }
    
    if ( cb->write_offset == cb->size - 1)
        cb->write_offset = 0;

    return true;
}

cb_buffer_struct CB_pop(circular_buffer* cb)
{    
    cb_buffer_struct data;
    if (cb == NULL || cb->buffer == NULL)
        strcpy( data.buffer, "\0" );;

    if(CB_empty(cb))
        printf("warning: circular buffer is empty. waiting for data\n");
    else{
        //data =  cb->buffer[read_offset];
        data = *(cb->buffer + cb->read_offset);
        cb->read_offset += 1;
        if (cb->read_offset == cb->size - 1)
            cb->read_offset = 0;
        cb->count -= 1;
    }
    return data;
}

bool CB_full(circular_buffer* cb)
{   if(cb->count == cb->size){
        return 1;
    }
    return 0;    
}

bool CB_empty(circular_buffer* cb)
{   if(cb->count == 0){
        return 1;
    }
    return 0;    
}

