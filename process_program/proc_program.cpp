#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <iostream>
#include <signal.h>
using namespace std;
int main(int argc, char const *argv[])
{
    pid_t pid;
    int count = 0;
    pid = fork();
    if (pid < 0)
    {
        printf("failed to create process\n");
    }
    else if (pid > 0)
    {
        count++;
        printf("I am father process, pid: %d\n", getpid());
    }
    else
    {
        count+=2;
        printf("I am child process pid: %d\n", getpid());
    }
    printf("count: %d\n",count);

    execl("/bin/ls","ls","-al",NULL);
    return 0;
}
