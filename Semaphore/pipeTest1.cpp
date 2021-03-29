#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main()
{
    int fd[2];
    int ret = pipe(fd);
    if (ret < 0)
    {
        printf("Fail to create pipe \n");
        return -1;
    }

    int pid = fork();
    if(pid > 0)
    {
        char writeBuffer[126] = "start";
        for (int i = 10;i > 0;i--)
        {
            printf("%d times  left\n",i);
            sleep(1);
        }
        printf("Start to write\n");
        int ret = write(fd[1], writeBuffer,sizeof(writeBuffer));
        if(ret < 0)
        {
            printf("Fail to write\n");
            return -1;
        }
    }
    else
    {
        char readBuffer[126];
        printf("pid %d wait for read\n", pid);
        int ret = read(fd[0], readBuffer, sizeof(readBuffer));
        if(ret < 0)
        {
            printf("Fail to read\n");
            return -1;
        }

        printf("Has read the string %s \n", readBuffer);
    }

    return 0;
}