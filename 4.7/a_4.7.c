/*  Implementation of the ls command.
	It will be able to do the following options: ls -a, ls -l, ls -n, ls -d
*/

#include "apue.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h> 
#include <errno.h>
#include <string.h> 
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <libgen.h>
#include <sys/types.h>
#include <grp.h>

int isDirectory(const char *);
void _ls(const char *, int, int, int, int);

// main function
int main(int argc, const char *argv[]){
	
	if(argc == 1)
		printf("The ls code was not executed!\n");
	else if (argc == 2 && strcmp(argv[1],"ls") == 0)
		_ls(".",0,0,0,0);
	else if (argc == 3){
		if (argv[2][0] == '-'){
			//Checking if option is passed
			//Options supporting: a, l, n, d
			int op_a = 0, op_l = 0 ,op_n = 0, op_d = 0;
			char *p = (char*)(argv[2] + 1);
			while(*p){
				if(*p == 'a') op_a = 1;
				else if(*p == 'l') op_l = 1;
				else if(*p == 'n') op_n = 1;
				else if(*p == 'd') op_d = 1;
				else{
					perror("Option not available");
					exit(0);
				}
				p++;
			}
			_ls(".",op_a,op_l,op_n,op_d);
		}
	}
	return 0;
}

int isDirectory(const char *path){
	struct stat statbuf;
	if (stat(path, &statbuf) != 0){
	    return 0;
	}
	return S_ISDIR(statbuf.st_mode);
}

void _ls(const char *dir,int op_a,int op_l,int op_n,int op_d)
{
	struct dirent *d;
	struct stat statbuf;
	struct passwd *pw;
	struct group *gid; 
	struct tm *tmp;
	DIR *dh = opendir(dir);
	if (!dh){
		if (errno = ENOENT)
			perror("Directory doesn't exist"); //If the directory is not found
		else
			perror("Unable to read directory"); //If the directory is not readable then throw error and exit
		exit(EXIT_FAILURE);
	}

	//While the next entry is not readable we will print directory files
	while ((d = readdir(dh)) != NULL){
		//If hidden files are found we continue
		if(!op_a && d->d_name[0] == '.')
			continue;
		
		else if(op_d){
			char fp[PATH_MAX];
			sprintf(fp, "%s/%s", dir, d->d_name);
			
			if(stat(fp, &statbuf) == -1){
				perror("stat");
				return;   
			}

			if(isDirectory(fp)){
				printf("%s  ", d->d_name);
				continue;
			}   		
		}

		else if(op_l){ 
			char fp[PATH_MAX];
				sprintf(fp, "%s/%s", dir, d->d_name);
				if(stat(fp, &statbuf) == -1) {
					perror("stat");
					return;   
			}
			printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-"); 
			
			printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
			printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
			printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
			
			printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
			printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
			printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
			
			printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
			printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
			printf((statbuf.st_mode & S_IXOTH) ? "x " : "- ");
			printf("%li ", statbuf.st_nlink);
			pw = getpwuid(statbuf.st_uid);  
			
			if(pw == NULL) {
				perror("getpwuid"); 
				printf("%d ", statbuf.st_uid); 
			}
			else{
				printf("%s ", pw->pw_name); 
			}
			
			gid = getgrgid(statbuf.st_gid);
			
			if(gid == NULL) {
				perror("getpwuid"); 
				printf("%d ", statbuf.st_gid); 
			}
			else
				printf("%s ", gid->gr_name); 
			
			printf("%5ld ", statbuf.st_size);
			char outstr[200];
			time_t t = statbuf.st_mtime;
			tmp = localtime(&t);   
			
			if(tmp == NULL) {
				perror("localtime"); 
				exit(EXIT_FAILURE);
			} 
	
			strftime(outstr, sizeof(outstr), "%b %d %R", tmp); 
			printf("%s ", outstr);
			printf("%s\n", d->d_name);
			continue;
		}

		else if(op_n){ 
			char fp[PATH_MAX];
    		sprintf(fp, "%s/%s", dir, d->d_name);
    		
			if(stat(fp, &statbuf) == -1) {
    		    perror("stat");
    		    return;   
   			}
			
			printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-"); 
	        
			printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
	    	printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
    		printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
			
			printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
			printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
			printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
			
			printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
    		printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
    		printf((statbuf.st_mode & S_IXOTH) ? "x " : "- ");
    		
			printf("%li ", statbuf.st_nlink);
    		printf("%d %d ", getuid(), getgid());
    		printf("%5ld ", statbuf.st_size);
    		
			char outstr[200];
    		time_t t = statbuf.st_mtime;
    		tmp = localtime(&t);   
    		
			if(tmp == NULL) {
        	    perror("localtime"); 
        	    exit(EXIT_FAILURE);
    		} 

    		strftime(outstr, sizeof(outstr), "%b %d %R", tmp); 
    		printf("%s ", outstr);
    		printf("%s\n", d->d_name);
    		continue;
		}
		printf("%s  ", d->d_name);
	}

	if(!op_l)
		printf("\n");
}