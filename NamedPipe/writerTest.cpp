#include <unistd.h>
#include <stdio.h>
// #include <sys/types.h>
// #include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("the input parameter count is less than 2\n");
        return -1;
    }

    char* fileName = argv[1];
    int fd = open(argv[1],O_WRONLY);
    if(fd < 0)
    {
        printf("Fail to open the fifo file %s\n", fileName);
        return -1;
    }

    char writeBuffer[50] = "Wuchentao";
    printf("10 seconds later will write %s\n", writeBuffer);
    sleep(10);
    write(fd,writeBuffer,sizeof(writeBuffer));
    printf("all has been write\n");
    return 0;

}