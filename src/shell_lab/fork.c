// fork.c
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char* argv[])
{

	pid_t pid; 
	pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    } else if (pid == 0) { // child process
        printf("I am child: my pid = %d\n", getpid());
    } else { // parent process
        printf("I am parent: child pid = %d\n", pid);
    }
    return 0;
}