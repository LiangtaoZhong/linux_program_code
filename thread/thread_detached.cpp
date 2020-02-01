#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // !_GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

void clear_thread(void *arg)
{
    printf("clear up thread test:%d\n", *(int *)arg);
}
void *thread_detached(void *arg)
{
    pthread_attr_t thread_attr;
    int stat, i;
    pthread_cleanup_push(clear_thread, &stat);

    sleep(2);
    int ret = pthread_getattr_np(pthread_self(), &thread_attr);
    if (ret)
    {
        perror("failed to get np!\n");
        exit(EXIT_FAILURE);
    }

    ret = pthread_attr_getdetachstate(&thread_attr, &stat);
    if (ret)
    {
        perror("fail to get attr state of detached!\n");
        exit(EXIT_FAILURE);
    }

    if (stat == PTHREAD_CREATE_JOINABLE)
    {
        printf("stat: PTHREAD_CREATE_JOINABLE\n");
        pthread_detach(pthread_self());
    }

    ret = pthread_getattr_np(pthread_self(), &thread_attr);
    if (ret)
    {
        perror("failed to get np!\n");
        exit(EXIT_FAILURE);
    }

    ret = pthread_attr_getdetachstate(&thread_attr, &stat);
    if (ret)
    {
        perror("fail to get attr state of detached!\n");
        exit(EXIT_FAILURE);
    }

    if (stat == PTHREAD_CREATE_JOINABLE)
    {
        printf("stat: PTHREAD_CREATE_JOINABLE\n");
    }
    else if (stat == PTHREAD_CREATE_DETACHED)
    {
        printf("stat: PTHREAD_CREATE_DETACHED\n");
    }

    pthread_attr_destroy(&thread_attr);

    printf("this is a child thread!\n");
    return (void *)0;
    pthread_cleanup_pop(0);
}

int main(int argc, char const *argv[])
{
    pthread_t tpid;
    pthread_attr_t thread_attr;

    int ret = pthread_attr_init(&thread_attr);
    if (ret)
    {
        perror("failed to init attr_state!\n");
        exit(EXIT_FAILURE);
    }

    if (pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE) != 0)
    {
        perror("failed to set state!\n");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&tpid, &thread_attr, thread_detached, NULL) != 0)
    {
        perror("failed to create thread!\n");
        exit(EXIT_FAILURE);
    }

    pthread_exit(NULL);
    printf("main thread can not execuate!\n");
    return 0;
}
