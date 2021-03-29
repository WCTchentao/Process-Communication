#include <unistd.h>
#include <stdio.h>
#include <sys/shm.h>
#include <signal.h>

void myfunc(int sid)
{
    return;
}

int main()
{
    int shmid = shmget(IPC_PRIVATE, 256, 0777);
    if(shmid < 0)
    {
        printf("Fail to create the shared memory!\n");
        return -1;
    }

    int pid = fork();
    if(pid > 0)
    {
        char* p = static_cast<char*>(shmat(shmid,nullptr, 0));
        if(p ==  nullptr)
        {
            printf("Parent process fail to map the memory! \n");
            return -2;
        }

        signal(SIGUSR2, myfunc);

        while(true)
        {
            printf("Parent process will enter the message:\n");
            fgets(p, 256, stdin);
            kill(pid, SIGUSR1);
            pause();
        }
    }
    else
    {
        char* p = static_cast<char*>(shmat(shmid, nullptr,0));
        if(p == nullptr)
        {
            printf("Child process fail to map the memory!\n");
            kill(getppid(),SIGKILL);
            return -3;
        }
        
        signal(SIGUSR1, myfunc);
        
        while(true)
        {
            pause();
            printf("Child process receive the message:%s \n",p);
            kill(getppid(),SIGUSR2);
        }

    }
}