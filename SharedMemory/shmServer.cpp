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

    printf("Server success to create the memory with shmid %d \n",shmid);

    MyMessage* p = static_cast<MyMessage*>(shmat(shmid,nullptr,0));
    if(p == nullptr)
    {
        printf("Server fail to map the memory \n");
        return -3;
    }

    signal(SIGUSR1,myfunc);
    
    //Server wait to receive the client pid
    printf("Server wait for client pid\n");
    p->pid = getpid();
    pause();

    //child pid has been set in p->pid
    int childPID = p->pid;
    printf("Server has received the client pid %d\n",childPID);
    while(true)
    {
        printf("Server enter the message:\n");
        fgets(p->message, sizeof(p->message), stdin);
        kill(childPID,SIGUSR2);
        pause();
    }
    return 0;
}