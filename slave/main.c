/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: shanaka
 *
 * Created on December 10, 2016, 2:56 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "../circular_buffer.h"

typedef int bool;

#define true 1
#define false 0

#define LOOP_COUNT 2000

int main (int argc, char **argv)
{       
        if(argc < 2){
            printf("usage \n");
            printf("\toptions \n");
            printf("\t\tshared memory control mmap location \n");
            printf("\t\tshared memory mmap location \n");
            printf("\tExample \n");
            printf("\t\t./a.out SharedMemStatfile SharedMemfile \n");
            return 1;
        }

        struct stat sb;
        char *p;
        int fd;

        struct stat sb_control;
        char *p_control;
        int fd_process_control;

        
        const char* controlFileName = argv[1];
        const char* dataFileName = argv[2];

        fd = open (argv[2], O_RDWR);
        fd_process_control = open (controlFileName, O_RDWR);

        if (fd == -1) {
                perror ("open");
                return 1;
        }

        if (fstat (fd, &sb) == -1) {
                perror ("fstat");
                return 1;
        }
        if (fstat (fd_process_control, &sb_control) == -1) {
                perror ("fstatprocesscontrol");
                return 1;
        }
        if (!S_ISREG (sb.st_mode)) {
                fprintf (stderr, "%s is not a file\n", dataFileName);
                return 1;
        }
        
        // open mmaps for share memory
        p = mmap ( 0, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);        
        p_control = mmap ( 0, sb_control.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_process_control, 0);

        if (p == MAP_FAILED) {
                perror ("mmap");
                return 1;
        }

        if (close (fd) == -1) {
                perror ("close");
                return 1;
        }

                
        printf("mmap initialized \n");
        

        circular_buffer *cb_master = p ;   
        circular_buffer *cb_master_1 = p + sizeof(circular_buffer) +1;   
        
        cb_buffer_struct pull_data;
        cb_buffer_struct push_data;

        strcpy( pull_data.buffer, "aaa\0" );

        bool cb_push_passed = true;
        
        printf("Circular Buffer initialized \n");

        int whileLoop = 0;

        // send control message stating the mmaps are initialized
        p_control[0] = 0x1;

        while( p_control[0] == 0x1 && whileLoop < LOOP_COUNT ){
            whileLoop++;

            p_control[1] = 0x1;

            while(p_control[1] == 0x1 && whileLoop < LOOP_COUNT)
                continue;
        
            if(!cb_push_passed){
                return 1;
            }    

            // pull buffer data 
            pull_data = CB_pop(cb_master);    

            if(whileLoop % 1 == 0){
                printf("cb_master   %s %llu  %llu %llu %llu\n" , pull_data.buffer, cb_master->read_offset, cb_master->write_offset,cb_master->count,cb_master->size); 
            }

        } 

        //stop the process using shared memory control bit        
        p_control[0] = 0x3;
        
        return 0;
}