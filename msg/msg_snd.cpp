#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <wait.h>
#include <fcntl.h>
#include <stdlib.h>
#define MAX_SIZE 512
struct msg
{
    long int msg_type;
    char data[MAX_SIZE];
};

int main(int argc, char const *argv[])
{
    int running = 1;
    struct msg mydata;
    char buf[BUFSIZ];
    int msgid = msgget((key_t)1, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        fprintf(stderr, "msgget errno:%d\n", errno);
        exit(EXIT_FAILURE);
    }
    while (running)
    {
        printf("input some data:\n");
        fgets(buf, BUFSIZ, stdin);
        mydata.msg_type = 1;
        strcpy(mydata.data, buf);
        if (msgsnd(msgid, (void *)&mydata, MAX_SIZE, 0) == -1)
        {
            fprintf(stderr, "msgsnd:%d\n", errno);
            exit(EXIT_FAILURE);
        }
        if (strncmp(buf, "end", 3) == 0)
        {
            running = 0;
        }
    }

    exit(EXIT_SUCCESS);
    return 0;
}
