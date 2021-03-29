#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

struct  MsgBuffer
{
    long msgType;
    char msgData[256];
};


int main()
{
    int key = ftok("./msg.c",'a');
    if(key < 0)
    {
        printf("Server fail to create key\n");
        return -1;
    }

    int msgId = msgget(key, IPC_CREAT | 0777);
    if(msgId < 0)
    {
        printf("Server fail to create message queue\n");
        return -1;
    }

    printf("Server success to create message queue %d\n", msgId);

    // init sendbuff
    MsgBuffer msgSendBuf;
    msgSendBuf.msgType = 100;

    //send message
    while(true)
    {
        memset(msgSendBuf.msgData, 0, sizeof(msgSendBuf.msgData));
        printf("Please enter the message,enter -q for exit\n");
        fgets(msgSendBuf.msgData, sizeof(msgSendBuf.msgData), stdin);
        msgsnd(msgId, static_cast<void*>(&msgSendBuf), strlen(msgSendBuf.msgData), 0);
    }
    //receive message

    return 0;

}