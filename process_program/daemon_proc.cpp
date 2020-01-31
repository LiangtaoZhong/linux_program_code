#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

#define MAXFILE 65535
volatile sig_atomic_t _ruuing = 1;

void sigterm_handler(int arg)
{
    _ruuing = 0;
}

int main(int argc, char const *argv[])
{
    int fd, i, len;
    pid_t pc = -1;

    char buf[] = "this is a daemon process\n";
    len = strlen(buf);
    printf("len:%d\n",len);
    pc = fork();   //1
    if (pc < 0)
    {
        printf("error fork!\n");
        exit(1);
    }
    else if (pc > 0)
    {
        printf("create daemon process successfully\n");
        exit(0);
    }

    setsid();   //2
    chdir("/");   //3
    umask(0);  //4
    for (i = 0; i < FILENAME_MAX; i++)   //5
    {
        close(i);
    }
    signal(SIGTERM, sigterm_handler);   //6
    while (_ruuing)
    {
        if (fd = open("/tmp/daemon.log", O_CREAT | O_APPEND | O_WRONLY, 0600) < 0)
        {
            perror("error create daemo.log");
            exit(1);
        }
        write(fd, buf, len + 1);
        close(fd);
        usleep(5 * 1000);//5s
    }
    return 0;
}
