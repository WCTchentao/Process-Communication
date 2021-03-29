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
        printf("client fail to create key\n");
        return -1;
    }

    int msgId = msgget(key, IPC_CREAT | 0777);
    if(msgId < 0)
    {
        printf("client fail to create message queue\n");
        return -1;
    }

    printf("client success to create message queue %d\n", msgId);

    int pid = fork();

    //parent process will send message with type 100
    if(pid > 0)
    {
        // init sendbuff
        MsgBuffer msgSendBuf;
        msgSendBuf.msgType = 200;

        //send message
        while(true)
        {
            memset(msgSendBuf.msgData, 0, sizeof(msgSendBuf.msgData));
            printf("Please enter the message,enter -q for exit\n");
            fgets(msgSendBuf.msgData, sizeof(msgSendBuf.msgData), stdin);
            msgsnd(msgId, static_cast<void*>(&msgSendBuf), strlen(msgSendBuf.msgData), 0);
        }
    }

    //child process will receive message with type 100
    if(pid == 0)
    {
        MsgBuffer msgRecBuf;
         //receive message1
        while(true)
        {
            memset(msgRecBuf.msgData,0,sizeof(msgRecBuf));
            msgrcv(msgId, static_cast<void*>(&msgRecBuf), sizeof(msgRecBuf.msgData), 100, 0);
            printf("Server receive message :%s",msgRecBuf.msgData);
        }
    }
    return 0;

}