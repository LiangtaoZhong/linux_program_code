#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
int main(int argc, char const *argv[])
{
    int fd[2];
    int pipe_flag = pipe(fd);
    if(pipe_flag ==-1)
    {
        perror("failed to create pipe\n");
        exit(1);
    }
    
    pid_t pid = fork();
    if(pid<0)
    {
        perror("failed to fork\n");
        exit(1);
    }
    else if(pid>0)  //father
    {
        close(fd[0]);//close read
        char buf[]="test pipe!";
        int len = write(fd[1],buf,strlen(buf));
        wait(NULL);
        close(fd[1]);
    }
    else   //child
    {
        char buf[20];
        close(fd[1]); //close write
        int len = read(fd[0],buf,sizeof(buf));
        write(STDOUT_FILENO,buf,len);
        close(fd[0]);
    }
    
    return 0;
}
