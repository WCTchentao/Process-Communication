#include <unistd.h>
#include <stdio.h>
#include <sys/sem.h>

int main()
{
    int semID = semget(IPC_PRIVATE, 4,0777);
    if(semID < 0)
    {
        printf("Fail to create semaphore\n");
        return -1;
    }

    printf("Success to create semaphore %d \n", semID);
    return 0;
}