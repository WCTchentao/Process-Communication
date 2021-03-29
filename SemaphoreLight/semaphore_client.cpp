#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/sem.h>

union semun
{
    int val;
    semid_ds* buf;
    unsigned short *array;
    seminfo *__buf;
};


int main()
{
    int key = ftok("../semphore.c",'a');
    if(key < 0)
    {
        printf("Client fail to get key\n");
        return -1;
    }

    int semID = semget(key, 2, IPC_CREAT | 0777);
    if(semID < 0)
    {
        printf("Client fail to create semID \n");
        return -2;
    }

    printf("Client success to create the sem %d\n",semID);

    //set semaphore
    // semun mySemun;
    // mySemun.val = 0;
    // semctl(semID,0,SETVAL,mySemun);

    sembuf mySemBuf;
    mySemBuf.sem_num = 0;
    mySemBuf.sem_flg = 0;
    mySemBuf.sem_op = -1;
    semop(semID,&mySemBuf,1);

    printf("Client start to run\n");
    for(int i = 0 ;i < 10;++i)
    {
        printf("Client run %d \n",i);
        sleep(1);
    }


    printf("Client work has all done!\n");
    return 0;
}