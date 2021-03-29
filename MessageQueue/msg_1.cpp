#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>

int main()
{
    int msgId = msgget(IPC_PRIVATE, 0777);
    if(msgId < 0)
    {
        printf("Fail to create message queue\n");
        return -1;
    }

    printf("Success to create message queue %d\n", msgId);
    return 0;
}