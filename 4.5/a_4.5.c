#include "apue.h"
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc,char* argv[]){
	int i;
	struct stat stat_buf;
	char *ptr;
	char ptr2[50];
	for (i = 1; i < argc; i++) {
		printf("%s: ", argv[i]);
		
		if (lstat(argv[i], &stat_buf) < 0) {
			perror("lstat error\n");
			continue;
		}
		
		if (S_ISLNK(stat_buf.st_mode)){
			ptr = " symbolic link";
			printf("%s\n", ptr);
			
			if(readlink(argv[i],ptr2,50)==-1)
				perror("readlink error\n");
			
			else
				printf("%s\n", ptr2);
		}
		
		else
			printf("\nThe given file is not a symbolic link.\n");
		
	}
 return 0;
}

