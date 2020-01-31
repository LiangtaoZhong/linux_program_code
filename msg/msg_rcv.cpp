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
struct msg
{
    long int my_msg_type;
    char data[BUFSIZ];
};

int main(int argc, char const *argv[])
{
    struct msg mymsg;
    int running = 1;
    long int msg_to_receive = 0;
    int msgid = msgget((key_t)1, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        fprintf(stderr, "msgget failed with error:%d\n", errno);
        exit(EXIT_FAILURE);
    }
    while (running)
    {
        if (msgrcv(msgid, (void *)&mymsg, BUFSIZ, msg_to_receive, 0) == -1)
        {
            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }

        printf("data:%s\n", mymsg.data);
        if (strncmp(mymsg.data, "end", 3) == 0)
        {
            running = 0;
        }
    }

    if (msgctl(msgid, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "msgctl errno:%d\n", errno);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
    return 0;
}
