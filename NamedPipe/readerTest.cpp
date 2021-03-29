#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc , char * argv[])
{
    if(argc != 2)
    {
        printf ("the input parameter  is not equal 2\n");
        return -1;
    }

    char* fileName = argv[1];
    int fd = open(fileName, O_RDONLY);
    if(fd < 0)
    {
        printf("Fail to open the file %s as reader\n",fileName);
        return -1;
    }

    printf("Reader wait for read\n");

    char readBuffer[50];
    read(fd, readBuffer, sizeof(readBuffer));
    
    printf("Success to read message %s \n", readBuffer);
    return 0;
}