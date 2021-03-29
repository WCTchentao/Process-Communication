#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void GoToilet(int signalID)
{
    if(signalID != SIGUSR1)
    {
        printf("Don't receive the signal %d \n", signalID);
        return;
    }

    for(int i = 10;i >0; i--)
    {
        printf("Doing toliet left %d seconds \n",i);
        sleep(1);
    }

    printf("Finish doing toilet and coding 10 seconds \n");

}

void KillMyChild(int signalID)
{
    printf("I will manage my child\n");
    wait(NULL);
    return ;
}

int main()
{
    int pid = fork();
    if(pid > 0)
    {
        signal(SIGUSR1, GoToilet);
        signal(SIGCHLD, KillMyChild);
        for(int i = 20;i>0;i--)
        {
            printf("Coding! Left %d seconds\n", i);
            sleep(1);
        }

        printf("All done!\n");
    }
    else
    {
        printf("5 second later , I will send a singal to parent\n");
        sleep(5);
        printf("I want to go toilet\n");
        kill(getppid(),SIGUSR1);
        printf("Has notice my father I want to go toilet\n");
    }

    return 0;
}