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

// semun mySemun;
// sembuf mySemBuf;
void* childFunc(void *var)
{
    sembuf mySemBuf;

    int *semID = static_cast<int*>(var);
    printf("Child function begin to run with semid %d\n",*semID);
    for(int i = 0; i < 10;i++)
    {
        printf("Child run %d \n",i);
        sleep(1);
    }
    mySemBuf.sem_op = 1;
    semop(*semID,&mySemBuf,1);
}

int main()
{
    int semID = semget(IPC_PRIVATE, 3,0777);
    if(semID < 0)
    {
        printf("Fail to create semID \n");
        return -1;
    }

    printf("Success to create the sem %d\n",semID);

    pthread_t tid;
    char str[] ="hello linux";
    int ret = pthread_create(&tid, NULL, childFunc,&semID);

    if(ret < 0)
    {
        printf("Fail to create the thread \n");
        return -1;
    }
    
    //set semaphore
    semun mySemun;
    semctl(semID,0,SETVAL,mySemun);

    sembuf mySemBuf;
    mySemBuf.sem_num = 0;
    mySemBuf.sem_flg = 0;
    mySemun.val = 0;    
    mySemBuf.sem_op = -1;
    semop(semID,&mySemBuf,1);
    printf("Main thread start to run\n");
    for(int i = 0 ;i < 10;++i)
    {
        printf("main thread run %d \n",i);
        sleep(1);
    }

    return 0;
}