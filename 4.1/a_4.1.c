/*  MTCS-205: CS-2(P): Assignment 3.4
    By: Shiva Krishna
        I MTech CS
        Regd no: 22555   
*/

/* Write a program that creates a file with ugo+rwx permissions. */

#include<stdio.h>
#include<fcntl.h>

#define perm (S_IRWXU | S_IRWXO | S_IRWXG)

int main(char argc, char* argv[]){
    int fd;
    
    if(fd = open(argv[1], O_RDWR | O_CREAT | O_EXCL, 0777) < 0){
        perror("Can't open the file...");
    }
}