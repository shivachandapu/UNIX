/*  MTCS-205: CS-2(P): Assignment 8.1
    By: Shiva Krishna
        I MTech CS
        Regd no: 22555   

Write a program called mpcalc (multi process calc) that will compare two expressions of the form ab and cd
and will print out which is less than (or equal to) which.
These numbers (a, b, c & d) should be accepted from the user (standard input).
This program should be implemented using multiple processes so that the main process can spawn another process to do the calculation
and allow the user to specify another such expression comparison.
In fact you should simulate a time consuming calculation by making the child (expression calculator)
process sleeping for 20 seconds before doing the calculation and printing the result.
The main process should exit when the user indicates that he wants to quit.
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>

void calc(int,int,int,int,int);

void main(){
    pid_t pid;

    char ch = 'y';
    int i=0;
    
    while(1){
        int a,b,c,d;
        printf("\nEnter the values of a,b,c,d to compare c^b and c^d: ");
        scanf("%d%d%d%d",&a,&b,&c,&d);
        
        if((pid = fork()) < 0){
            printf("\n:Fork error!\n");
            exit(1);
        } 
        else if(pid == 0){
            sleep(10);
            calc(a,b,c,d,i);
            exit(0);
        }
        else if (ch=='y' || ch =='Y'){
            printf("\nDo you want to make another calculation?(y/n): ");
            i++;
            
            while(getchar()!='\n');
            scanf("%c",&ch);
            
            if (ch=='y' || ch =='Y');
            else if(ch=='n' || ch=='N'){
                printf("\n\033[1;32m Waiting for all the child processes...\033[0;37m\n");
                while(wait(NULL) != -1);
                printf("\n\033[1;32m All child processes returned!\033[0;0m\n");
                exit(1);
            }
            else{
                printf("\nWrong choice!\n");
                exit(1);
            }
        }
    }
}

void calc(int a,int b,int c,int d, int i){
    if (pow(a,b) < pow(b,c))
        printf("\n\033[1;31m Process %d: \033[0;37m %d^%d is less than %d^%d.\n",i,a,b,c,d);
    else if (pow(b,c) < pow(a,b))
        printf("\n\033[1;31m Process %d: \033[0;37m %d^%d is less than %d^%d.\n",i,c,d,a,b);
    else
        printf("\n\033[1;31m Process %d: \033[0;37m %d^%d is equal to %d^%d.\n",i,a,b,c,d);
}

