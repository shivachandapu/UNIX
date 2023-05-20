#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>

void calc(int,int,int,int,int);

void check_and_print_result(int*, int*);

int main() {
    pid_t pid;
    int result[100] = {0}; // initialize all values to 0
    int n_completed = 0;
    char ch = 'y';
    int i=0;
    
    while(1) {
        // check for completed child processes
        check_and_print_result(result, &n_completed);

        int a,b,c,d;
        printf("\nEnter the values of a,b,c,d to compare a^b and c^d: ");
        scanf("%d%d%d%d",&a,&b,&c,&d);
        
        if ((pid = fork()) < 0) {
            printf("\nFork error!\n");
            exit(1);
        } else if (pid == 0) {
            sleep(10); // increased sleep time for testing
            calc(a,b,c,d,i);
            check_and_print_result(result, &n_completed);
            exit(0);
        } else {
            printf("\nChild process %d with PID %d is created.\n", i, pid);
            i++;
            
            while(getchar()!='\n');
            printf("\nDo you want to make another calculation?(y/n): ");
            scanf("%c",&ch);
            
            if (ch == 'y' || ch == 'Y') {
                // continue with loop
            } else if(ch == 'n' || ch == 'N') {
                printf("\nWaiting for all child processes to complete...\n");
                while (wait(NULL) != -1);
                printf("\nAll child processes have completed!\n");
                break;
            } else {
                printf("\nWrong choice!\n");
                exit(1);
            }
            check_and_print_result(result, &n_completed);
        }
    }
    return 0;
}

void calc(int a, int b, int c, int d, int i) {
    if (pow(a,b) < pow(c,d))
        exit(1);
    else if (pow(c,d) < pow(a,b))
        exit(2);
    else
        exit(3);
}

void check_and_print_result(int *result, int *n_completed) {
    int status;
    pid_t child_pid;
    while ((child_pid = waitpid(-1, &status, WNOHANG))>0) {
        if (WIFEXITED(status)) {
            int child_result = WEXITSTATUS(status);
            printf("\nProcess %d has completed with result: %d\n", child_pid, child_result);
            result[child_pid] = child_result;
            (*n_completed)++;
        } else if (WIFSIGNALED(status)) {
            printf("\nProcess %d has terminated with signal %d\n", child_pid, WTERMSIG(status));
        }
    }
    if (*n_completed == 0) {
        printf("\nNo completed processes since last check.\n");
    }
}
