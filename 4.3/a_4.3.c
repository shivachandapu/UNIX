#include "apue.h"
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]){

	DIR *dp;
	struct stat buf;
	struct dirent *dirp;

	if (argc != 2)
		printf("usage: ls directory_name");

	if ((dp = opendir(argv[1])) == NULL)
		printf("can’t open %s", argv[1]);

	while ((dirp = readdir(dp)) != NULL){
		printf("\nFile name: %s", dirp->d_name);

		if (stat(dirp->d_name, &buf) == 0)
			printFileProperties(buf);

		if (stat(dirp->d_name, &buf) < 0)
			printf("stat error");
	}

	closedir(dp);
	exit(0);

}

void printFileProperties(struct stat stats)
{
	struct tm dt;
	
	printf("\nFile access: ");
	if (stats.st_mode & R_OK)
		printf("read ");
	
	if (stats.st_mode & W_OK)
		printf("write ");
	if (stats.st_mode & X_OK)
		printf("execute");
	
	printf("\nFile size: %ld", stats.st_size);
	
	dt = *(gmtime(&stats.st_ctime));
	printf("\nCreated on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, dt.tm_hour, dt.tm_min, dt.tm_sec);
	
	dt = *(gmtime(&stats.st_mtime));
	printf("\nModified on: %d-%d-%d %d:%d:%d\n", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, dt.tm_hour, dt.tm_min, dt.tm_sec);

}
