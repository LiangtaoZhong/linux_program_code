#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
//typedef void (*signal_handler)(int);
int sig_count = 0;
void sig_int_fuc(int signum)
{
    
    printf("count:%d\n", sig_count++);
}

int main(int argc, char const *argv[])
{
    int count = 0;
    signal(SIGINT, sig_int_fuc);
    while (true)
    {
        count++;
        printf("main:%d\n", count);
        sleep(1);
    }

    return 0;
}
