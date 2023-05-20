/*  MTCS-205: CS-2(P): Assignment 3.2
    By: Shiva Krishna
        I MTech CS
        Regd no: 22555   
*/
#include "apue.h"
#include <fcntl.h>

int main(void)
{   
    int s,n,i;
    int fd;
    char y,ow;
    char telbook[10];
    char name[20];
    char num[20];
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
            
            if((fd = open(telbook, O_RDWR | O_CREAT | O_EXCL, FILE_MODE))<0)
                printf("\nOPEN ERROR...\n");
            else{
                printf("\n\tEnter the number of entries: ");
                scanf("%d",&n);
                printf("\nFile is ready!\n");
                
                if(lseek(fd,n*40-1,SEEK_SET) == -1)
                    printf("\nlseek ERROR...\n");
                write(fd,"",1);
            }
            break;
        
        case 2:

            printf("\nEnter the index: ");
            scanf("%d",&i);

            if(lseek(fd,(i-1)*40,SEEK_SET) == -1)
                printf("\nlseek ERROR...\n");
            else{
                read(fd,buf,40);
                if(buf[0]!='\0')
                    printf("\n\tName: %s\n\tNumber: %s\n",buf,buf+20);
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
                    scanf("%s",num);
                    write(fd,num,20);
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
                        scanf("%s",num);
                        write(fd,num,20);
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