#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

int main(int argc , char* argv[])
{
    if(argc != 3)
    {
        printf("The input parameter should be 3\n");
        return -1;
    }
    
    if(strcmp(argv[1], "-q") != 0)
    {
        printf("The second parameter should be '-q' \n");
        return -2;
    }

    int msgID = atoi(argv[2]);
    printf("Will  delete the msg queue %d \n",msgID);

    int ret = msgctl(msgID,IPC_RMID, nullptr);
    if (ret < 0)
    {
        printf("the message %d is not exist\n",msgID);
        return -3;
    }

    printf("Success to delete the msg queue %d \n", msgID);
    return 0;
}