#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void GoToilet(int signalID)
{
    if(signalID != 14)
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

int main()
{
    signal(SIGALRM, GoToilet);
    alarm(10);
    printf("Coding! 10 seconds later will go to toliet\n");

    for(int i = 20;i>0;i--)
    {
        printf("Coding! Left %d seconds\n",i);
        sleep(1);
    }

    printf("All done!\n");
    return 0;
}