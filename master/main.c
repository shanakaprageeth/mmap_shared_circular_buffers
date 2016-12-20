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
        //int argc = 2;
        //char *argv[2];
        
        
        off_t len;

        struct stat sb;
        char *p;
        int fd;

        struct stat sb_control;
        char *p_control;
        int fd_process_control;


        
        //argv[0] = "/home/shanaka/SharedMemStat";
        //argv[1] = "/home/shanaka/SharedMem";
        
        // resize file to allocate memory size
        int no_of_buffers = 4;
        int fileSize = CIRCULAR_BUFFER_SIZE * no_of_buffers;
        FILE *fp = fopen(argv[2], "w");
        //ftruncate(fileno(fp), fileSize);
        fseek(fp, fileSize , SEEK_SET);
        fputc('\0', fp);
        fclose(fp);


        if (argc < 2) {
                fprintf (stderr, "usage: %s <file>\n", argv[2]);
                return 1;
        }
        
        fd = open (argv[2], O_RDWR);
        fd_process_control = open (argv[1], O_RDWR);

        if (fd == -1) {
                perror ("open");
                return 1;
        }

        if (fstat (fd, &sb) == -1) {
                perror ("fstat");
                return 1;
        }
        if (fstat (fd_process_control, &sb_control) == -1) {
                perror ("fd_process_control");
                return 1;
        }
        if (!S_ISREG (sb.st_mode)) {
                fprintf (stderr, "%s is not a file\n", argv[2]);
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
        

        circular_buffer *cb_master = p;   
        //circular_buffer *cb_master_1 = p + sizeof(circular_buffer) +1 ;   


        CB_init(cb_master);
        //CB_init(cb_master_1);


        printf("%llu  \n" ,  cb_master->size); 
        
        int8_t pull_data = 0;
        int8_t push_data = 0;

        bool cb_push_passed = true;
        
        printf("Circular Buffer initialized \n");

        int whileLoop = 0;

        // send control message stating the mmaps are initialized
        p_control[0] = 0x0;
        while( p_control[0] == 0x0){
            continue;
        }

        while( p_control[0] == 0x1 && whileLoop < LOOP_COUNT ){
            whileLoop++;
            
            push_data++;
            cb_push_passed = CB_push(cb_master, push_data);
            //cb_push_passed = CB_push(cb_master_1, push_data);
        
            if(!cb_push_passed){
                return 1;
            }    

            p_control[1] = 0x0;
            while(p_control[1] == 0x0 && whileLoop < LOOP_COUNT)
                continue;

            //pull_data = CB_pop(cb_master); 
            //pull_data = CB_pop(cb_master_1);     

            if(whileLoop % 1 == 0){
                //printf("cb_master   %d %llu  %llu %llu %llu\n" , pull_data, cb_master->read_offset, cb_master->write_offset,cb_master->count,cb_master->size); 
                //printf("cb_master_1 %d %llu  %llu %llu %llu \n" , push_data, cb_master_1->read_offset, cb_master_1->write_offset,cb_master_1->count,cb_master_1->size); 
                continue;
            }

        } 

        //stop the process using shared memory control bit        
        p_control[0] = 0x2;
        
        if (munmap (p, sb.st_size) == -1) {
                perror ("munmap");
                return 1;
        }

        return 0;
}