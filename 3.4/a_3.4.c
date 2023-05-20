/*  MTCS-205: CS-2(P): Assignment 3.4
    By: Shiva Krishna
        I MTech CS
        Regd no: 22555   
*/

#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[]) {

    int fd;
    int val;

    if((fd = open("input.txt", O_RDWR | O_CREAT | O_APPEND, FILE_MODE))<0)
        printf("\nOPEN ERROR...\n");

    if ((val = fcntl(fd, F_GETFL,0)) < 0){
           printf("Couldn't get the file status...\n");
           exit(0);
     }
    
    switch (val & O_ACCMODE) {
        case O_RDONLY:
            printf("read only");
            break;
        case O_WRONLY:
            printf("write only");
            break;
        case O_RDWR:
            printf("read write");
            break;
        default:
            printf("unknow access mode");
    }
    
    if (val & O_APPEND)
        printf(", append");
    if (val & O_NONBLOCK)
        printf(", nonblocking");
    if (val & O_SYNC)
        printf(", synchronous writes");

    printf("\n");    
    exit(0);
}