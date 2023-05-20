#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 100 // maximum number of arguments for a command
#define MAX_LINE 1024 // maximum length of a command line

void execute_command(char **args);
void print_exit_status(int status);

int main() {
    char line[MAX_LINE]; // command line input buffer
    char *args[MAX_ARGS]; // array of pointers to arguments for a command
    int status; // termination status of child process
    pid_t pid; // process id of child process

    while(1) {
        printf("> "); // print prompt
        fgets(line, MAX_LINE, stdin); // read command line input
        
        if (strcmp(line, "exit\n") == 0) // exit if user enters "exit"
            break;

        int n_args = 0; // number of arguments for the command

        // tokenize the command line input into arguments
        char *token = strtok(line, " \n");
        while (token != NULL) {
            args[n_args++] = token;
            token = strtok(NULL, " \n");
        }
        args[n_args] = NULL; // mark end of argument list with NULL
        
        if (n_args > 0) { // execute command only if there are arguments
            if ((pid = fork()) < 0) { // fork error
                printf("Fork error!\n");
                exit(1);
            } else if (pid == 0) { // child process
                execute_command(args);
                exit(0); // exit child process
            } else { // parent process
                waitpid(pid, &status, 0); // wait for child process to terminate
                print_exit_status(status); // print termination status and exit status (if any)
            }
        }
    }

    return 0;
}

void execute_command(char **args) {
    execvp(args[0], args); // execute command with arguments
    printf("Command not found: %s\n", args[0]); // print error if command not found
}

void print_exit_status(int status) {
    if (WIFEXITED(status)) { // check if child process terminated normally
        printf("Termination status: %d\n", WEXITSTATUS(status)); // print termination status
    } else if (WIFSIGNALED(status)) { // check if child process terminated due to signal
        printf("Termination status: Signal %d\n", WTERMSIG(status)); // print signal number
    }
}
