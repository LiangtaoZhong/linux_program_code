#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h> /*for mmap and munmap*/
using namespace std;

int main(int argc, const char **argv)
{
    int fd = -1;
    char filename[] = "./newfile";
    ssize_t size = -1;
    char buf[5] = {0};

    fd = open(filename, O_RDWR); /*open file in writing and reading*/
    if (fd == -1)
    {
        std::cout << "fail to open file " << filename << std::endl;
    }
    else
    {
        std::cout << "open file " << filename << " successfully" << endl;
    }

    while (size) /*read file*/
    {
        size = read(fd, buf, 5);
        if (size == -1)
        {
            close(fd);
            printf("failed to read file!\n");
            return -1;
        }
        else
        {
            if (size > 0)
            {
                for (int i = 0; i < size; i++)
                {
                    printf("%c", *(buf + i));
                }
            }
            else
            {
                printf("\nread file end\n");
            }
        }
    }

    size = -1; /*write char*/
    char write_buf[] = "\nliangtaozhong";
    size = write(fd, write_buf, strlen(write_buf));
    printf("write %ld byte to file\n", size);

    off_t offset = -1;
    offset = lseek(fd, 0, SEEK_SET); /*insert char in the head of file*/
    if (offset == -1)
    {
        printf("lseek failed");
    }
    else
    {
        char buf[] = "hello\n";
        size_t size = write(fd, buf, strlen(buf));
        if (size != strlen(buf))
        {
            printf("write data offset failed!\n");
            close(fd);
            return -1;
        }
    }
    
    struct stat st; /*get status of file*/
    int sta = fstat(fd, &st);
    if (sta == -1)
    {
        printf("failed to return information of file");
        close(fd);
        return -1;
    }
    printf("mode:%d  size:%ldbyte  inode:%ld \n", st.st_mode, st.st_size, st.st_ino);


    char* mem_map=0;   /*mem and file map*/
    mem_map= (char*)mmap(NULL,st.st_size,PROT_READ,MAP_PRIVATE,fd,0);
    printf("mem:\n %s",mem_map);
    munmap(mem_map,st.st_size);
    
   
    if (close(fd) != -1) /*close file*/
    {
        printf("close file %s successfully\n", filename);
    }

    return 0;
}
