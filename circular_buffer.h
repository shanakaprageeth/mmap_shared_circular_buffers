#ifndef CIRCULAR_BUFFER_H_   /* Include guard for header*/
#define CIRCULAR_BUFFER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#ifndef CIRCULAR_BUFFER_SIZE   /* Include guard for buffer size*/
#define CIRCULAR_BUFFER_SIZE 1048576
#endif


typedef int bool;
#define true 1
#define false 0

// circular buffer structure
typedef struct
{
     char buffer[CIRCULAR_BUFFER_SIZE];				/* initalize circular buffer */
     signed long long read_offset;				/* read offset of buffer */
     signed long long write_offset;				/* write offset of buffer */
     signed long long  count;						/* amount of data in buffer */
     signed long long  size;						/* buffer size */
 } circular_buffer;

void CB_init(circular_buffer* cb);  		 	/* initalize circular buffer */
void CB_free(circular_buffer* cb);				/* free circular buffer */
bool CB_push(circular_buffer* cb, char data);	/* push data into circular buffer */
char CB_pop(circular_buffer* cb);				/* pop data from circular buffer */
bool CB_full(circular_buffer* cb);				/* check for buffer full condition */
bool CB_empty(circular_buffer* cb);				/* check for buffer empty condition */

#endif // CIRCULAR_BUFFER_H_