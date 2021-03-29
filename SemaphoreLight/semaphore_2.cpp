#include <unistd.h>
#include <stdio.h>
#include <sys/sem.h>
#include <string.h>
#include <stdlib.h>

int main(int argc , char* argv[])
{
    if(argc != 3)
    {
        printf("the parameter should be 3\n");
        return -1;
    }

    if(strcmp(argv[1],"-s") != 0)
    {
        printf("the second parameter should be '-s' \n");
        return -2;
    }

    int semID = atoi(argv[2]);

    if(semctl(semID,0,IPC_RMID) < 0 )
    {
        printf("semid %d is not exist\n", semID);
        return -3;
    }

    printf("Success to remove semaphore %d \n", semID);
    return 0;
}