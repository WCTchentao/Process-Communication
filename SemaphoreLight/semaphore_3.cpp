#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

sem_t sem;

void* childFunc(void *var)
{
    printf("Child function begin to run %s\n",static_cast<char*>(var));
    for(int i = 0; i < 10;i++)
    {
        printf("Child run %d \n",i);
        sleep(1);
    }
   sem_post(&sem);
}

int main()
{
    sem_init(&sem,0,0);

    pthread_t tid;
    char str[] ="hello linux";
    int ret = pthread_create(&tid, NULL, childFunc,str);

    if(ret < 0)
    {
        printf("Fail to create the thread \n");
        return -1;
    }
    
        //p wait
    sem_wait(&sem);

    printf("Main thread start to run\n");
    for(int i = 0 ;i < 10;++i)
    {
        printf("main thread run %d \n",i);
        sleep(1);
    }

    return 0;
}