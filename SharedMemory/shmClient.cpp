#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>

struct MyMessage
{
    int pid;
    char message[126];
};

void myfunc(int sid)
{
    return;
}

int main()
{
    int key = ftok("./test.c",'b');
    if( key < 0)
    {
        printf("Fail to create key\n");
        return -1;
    }

    int shmid = shmget(key,sizeof(MyMessage),IPC_CREAT | 0777);
    if(shmid < 0)
    {
        printf("Fail to create the shared memory \n");
        return -2;
    }

    printf("Client success to create the memory with shmid %d \n",shmid);

    MyMessage* p = static_cast<MyMessage*>(shmat(shmid,nullptr,0));
    if(p == nullptr)
    {
        printf("client fail to map the memory \n");
        return -3;
    }

    signal(SIGUSR2,myfunc);
    
    //client receive the server pid and send its pid
    int serverPid = p->pid;
    printf("Client has reveive the server pid:%d\n",serverPid);
    p->pid = getpid();
    kill(serverPid, SIGUSR1);

    while(true)
    {
        pause();
        printf("Client has received the message:%s",p->message);
        kill(serverPid,SIGUSR1);
    }
    return 0;
}