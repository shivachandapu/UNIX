/*  MTCS-205: CS-2(P): Assignment 3.3
    By: Shiva Krishna
        I MTech CS
        Regd no: 22555   
*/

#include "apue.h"
#include <fcntl.h>
#include <time.h>

int fd,fd_log;
char nam[20],num[20];
time_t current_time;

// function to write to a log book
void write_to_log(char* mod,int index, char* nam, char* num){
    char ind[10];
    char* c_time_string;
    time_t current_time;
    time(&current_time);
    struct tm *curr_t_struct;
    curr_t_struct = gmtime(&current_time );
    c_time_string = asctime(curr_t_struct);
    
    sprintf(ind,"%d",index);
    write(fd_log,ind,strlen(ind));
    write(fd_log," ",strlen(" "));
    write(fd_log,mod,1);
    write(fd_log,"      ",strlen("      "));
    write(fd_log,nam,strlen(nam));
    write(fd_log,"      ",strlen("      "));
    write(fd_log,num,strlen(num));
    write(fd_log,"      ",strlen("      "));
    write(fd_log,c_time_string,strlen(c_time_string));
    write(fd_log,"\n",1);
}

int main(void)
{   
    int s,n,i;    
    char y,ow;
    char telbook[10];
    char name[20];
    char numb[20];
    char buf[40];
    
    do{
    printf("\n**************Operations on a TeleBook**************\n");
    printf("\n\t1. Creation of Telbook.");
    printf("\n\t2. Show the entry at an index.");
    printf("\n\t3. Write at an index.");
    printf("\n\n\tEnter your choice: ");
    scanf("%d",&s);
    
    switch(s){
        case 1:
            printf("\n\tGive a name to create a file: ");
            scanf("%s",telbook);
            
            if((fd = open(telbook, O_RDWR|O_CREAT|O_EXCL, FILE_MODE))<0)    // file descripter for telebook 
                printf("\nOPEN ERROR...\n");
            else{
                printf("\n\tEnter the number of entries: ");
                scanf("%d",&n);
                printf("\nFile is ready!\n");
                
                if(lseek(fd,n*40-1,SEEK_SET) == -1)
                    printf("\nlseek ERROR...\n");
                write(fd,"",1);
                
                fd_log = open("logfile.txt", O_WRONLY|O_APPEND|O_CREAT, FILE_MODE);     // file descripter for log file             
            }
            break;
        
        case 2:

            printf("\nEnter the index: ");
            scanf("%d",&i);

            if(lseek(fd,(i-1)*40,SEEK_SET) == -1)
                printf("\nlseek ERROR...\n");
            else{
                read(fd,buf,40);
                if(buf[0]!='\0'){
                    printf("\n\tName: %s\n\tNumber: %s\n",buf,buf+20);
                    write_to_log("r",i,buf,buf+20);
                }
                else
                    printf("\nThere are no entries at this index.\n");

            }
            break;
        
        case 3:

            printf("\nEnter the index: ");
            scanf("%d",&i);

            if(lseek(fd,(i-1)*40,SEEK_SET) == -1)
                printf("\nlseek ERROR...\n");
            else{
                                
                read(fd,buf,40);
                if(buf[0]=='\0'){
                    lseek(fd,-40,SEEK_CUR);
                    printf("\n\tEnter the name: ");
                    scanf("%s",name);
                    write(fd,name,20);

                    printf("\n\tEnter the phone number: ");
                    scanf("%s",numb);
                    write(fd,numb,20);
                    write_to_log("w",i,name,numb);
                }

                if(buf[0]!='\0'){
                    printf("\nDo you want to over-write the entries?(y): ");
                    getchar();
                    scanf("%c",&ow);
                    
                    if(ow==('y')){
                        lseek(fd,-40,SEEK_CUR);
                        printf("\n\tEnter the name: ");
                        scanf("%s",name);
                        write(fd,name,20);

                        printf("\n\tEnter the phone number: ");
                        scanf("%s",numb);
                        write(fd,numb,20);
                        write_to_log("ow",i,name,numb);
                    }
                    else
                        printf("\n\tAll the best!\n");
                }
            }
            break;
        
        default:break;
    }

    printf("\n\tExit?(y) ");
    getchar();
    scanf("%c",&y);
    }while(y != 'y');
    
    close(fd);
    exit(0);
}