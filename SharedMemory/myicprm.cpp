#include <unistd.h>
#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>

int main(int argc ,char* argv[])
{
    if(argc < 3)
    {
        printf("the parameter is less than 2\n");
        return -1;
    }

    if(strcmp(argv[1],"-m") != 0 )
    {
        printf("the second parameter should be '-m'  \n");
        return -2;
    }

    int shmid = atoi(argv[2]);

    int ret = shmctl(shmid, IPC_RMID, nullptr);
    if(ret < 0)
    {
        printf("the shmid %d is not exsit \n",shmid);
        return -1;
    }

    printf("Success delete the shared memory whose id is %d \n",shmid);
    return 0;
}
