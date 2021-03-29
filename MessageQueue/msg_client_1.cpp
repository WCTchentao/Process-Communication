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
        printf("Client fail to create key\n");
        return -1;
    }

    int msgId = msgget(key, IPC_CREAT | 0777);
    if(msgId < 0)
    {
        printf("Client fail to create message queue\n");
        return -1;
    }

    printf("Client success to create message queue %d\n", msgId);

    // init recvBuffer
    MsgBuffer msgRecvBuf;


    //recv message
    int recvRet;
    while(true)
    {
        memset(msgRecvBuf.msgData, 0, sizeof(msgRecvBuf.msgData));
        recvRet = msgrcv(msgId, static_cast<void*>(&msgRecvBuf), sizeof(msgRecvBuf.msgData),100,0);
        printf("Message length %d, message info:%s \n",recvRet, msgRecvBuf.msgData);
    }
    //receive message

    return 0;

}