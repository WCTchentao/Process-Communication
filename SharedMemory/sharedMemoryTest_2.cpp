#include <unistd.h>
#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <wait.h>

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
    // system("ipcs -m");

    char* p = static_cast<char*>(shmat(shmid, NULL, 0));
    if( p  == nullptr)
    {
        printf("Fail to do memory map of id %d\n",shmid);
        return -1;
    }

    int pid  = fork();
    if(pid > 0)
    {
        fgets(p, 126,stdin);
        wait(NULL);
    }
    else
    {
        sleep(10);
        printf("get the data %s \n",p);
    }

    return 0;
}
