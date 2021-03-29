#include <unistd.h>
#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>


int main()
{
    int key = ftok("./test.c",'a');
    if (key < 0)
    {
        printf("Fail to create key\n");
        return -1;
    }

    printf("Success to create key %X\n",key);
    
    int shmid = shmget(key, 126, IPC_CREAT | 0777);
    
    if(shmid < 0)
    {
        printf("Fail to create to shared memory\n");
        return -1;
    }

    printf("Success to create the shared memory wiht momery id %d !\n",shmid);

    char* p =  nullptr;
    p = static_cast<char*>(shmat(shmid, NULL ,0 ));
    if(p == nullptr)
    {
        printf("Fail to map the memory!\n");
        return -1;
    }

    fgets(p, 126, stdin);

    printf("the input one is %s\n",p);

    shmdt(p);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
