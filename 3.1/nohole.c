#include "apue.h"
#include <fcntl.h>
#include<unistd.h>

char    buf1[] = "abcdefghij";
char    buf2[] = "ABCDEFGHIJ";

int
main(void)
{
    int     fd;

    if ((fd = creat("file.nohole", FILE_MODE)) < 0)
        printf("creat error");

    while(lseek(fd,0,SEEK_END)<16394)
    {
        if (write(fd, buf1, 10) != 10)
        printf("buf1 write error");
    }

    exit(0);
}