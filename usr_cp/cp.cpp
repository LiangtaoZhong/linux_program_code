#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
int main(int argc, const char **argv)
{
    int src, dst;
    src = open(argv[1], O_RDONLY);
    dst = open(argv[2], O_RDWR|O_CREAT, S_IRWXU);

    if (src == -1)
    {
        close(src);
        close(dst);
        printf("failed to open src file %s\n", argv[1]);
        exit(1);
    }
    if (dst == -1)
    {
        close(src);
        close(dst);
        printf("failed to open dst file %s\n", argv[2]);
        exit(1);
    }

    ssize_t size1 = -1, size2 = -1;
    char buf[10];
    memset(buf,0,10);
    
    while (size1)
    {
        size1 = read(src, buf, 10);
        if (size1 == -1)
        {
            close(src);
            close(dst);
            printf("failed to read src file\n ");
            exit(1);
        }
        else
        {
            if (size1 > 0)
            {
                size2 = write(dst, buf, strlen(buf));
                memset(buf,0,strlen(buf));
                if (size2 == -1)
                {
                    close(src);
                    close(dst);
                    printf("failed to write dst file\n");
                    exit(1);
                }
            }
        }
    }
    close(src);
    close(dst);
    printf("copy successfully\n");
    return 0;
}