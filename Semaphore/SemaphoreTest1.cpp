#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pid = fork();
    if(pid > 0)
    {
        printf("wait for sub process end in pid %d\n",pid);
        if(waitpid(pid,NULL,0) == 0)
        {
            printf("Success wait untill the sub has end\n");
            return 0;
        }
        
        return -1;
    }
    else
    {
        printf("process %d working! 10 second later will end itself\n",pid);
        alarm(10);
        pause();
        printf("Will not arrive here\n");
        return 0;
    }
}