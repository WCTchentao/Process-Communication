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
    int msgId = msgget(IPC_PRIVATE, 0777);
    if(msgId < 0)
    {
        printf("Fail to create message queue\n");
        return -1;
    }

    printf("Success to create message queue %d\n", msgId);

    // init sendbuff
    MsgBuffer msgSendBuf;
    msgSendBuf.msgType = 100;

    //send message
    printf("Please enter the message,enter -q for exit\n");
    fgets(msgSendBuf.msgData, sizeof(msgSendBuf.msgData), stdin);
    msgsnd(msgId, static_cast<void*>(&msgSendBuf), strlen(msgSendBuf.msgData), 0);

    //receive message
    MsgBuffer msgRecvBuf;
    int recvRet;
    recvRet = msgrcv(msgId, static_cast<void*>(&msgRecvBuf), sizeof(msgRecvBuf.msgData), 100, 0);
    if(recvRet < 0)
    {
        printf("Fail to get the recv buffer\n");
        return -1;
    }

    printf("Has receive the length %d and message is %s \n", recvRet, msgRecvBuf.msgData);

    return 0;

}