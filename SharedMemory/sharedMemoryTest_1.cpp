#include <unistd.h>
#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>


int main()
{
    int shmid = shmget(IPC_PRIVATE, 126, 0777);
    
    if(shmid < 0)
    {
        printf("Fail to create to shared memory\n");
        return -1;
    }


    printf("Success to create the shared memory wiht momery id %d !\n",shmid);
    system("ipcs -m");
    // char commnd[126];
    // sprintf(commnd,"ipcrm -m %d",shmid);

    // system(commnd);
    return 0;
}
