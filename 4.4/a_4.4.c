#include"apue.h"
#include"error.h"
#include<fcntl.h>

int main(void){
	if (creat("tempfile", O_RDWR) < 0)
		err_sys("open error");
	else
		printf("temporary file created!\n");

        if (unlink("tempfile") < 0)
		err_sys("unlink error");

	printf("temporary file deleted!\n");
}

