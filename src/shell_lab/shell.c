//shell.c

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv[])
{
    pid_t pid; 
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    } else if (pid == 0) { //child process
        printf("processing ...\n");
        if (execvp(argv[1], &argv[1]) < 0) {
            perror("");
        }
    } else { //parent process
        wait(NULL);
        printf("completed.\n");
    }
    return 0;
}
