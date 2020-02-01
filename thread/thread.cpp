#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>

struct data
{
    int count;
    char *buf;
};
void *pthread_test(void *arg)
{
    struct data mydata;
    mydata = *(struct data *)arg;

    printf("%s  count: %d\n", mydata.buf, mydata.count);
    return (void *)0;
}

int main(int argc, char const *argv[])
{
    pthread_t tpid;
    struct data thread_data;
    thread_data.buf = "this is a thread!";
    thread_data.count = 20;

    int ret = pthread_create(&tpid, NULL, pthread_test, (void *)&thread_data);
    if (ret)
    {
        perror("failed to create thread\n");
        exit(EXIT_FAILURE);
    }

    pthread_join(tpid, NULL);
    printf("thread exe ok!\n");
    return 0;
}