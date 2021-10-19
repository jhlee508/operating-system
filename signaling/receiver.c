#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// for Message queue
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define BUFFER_SIZE 1024

typedef struct {
    long msgtype;
    int time;
    char buf[BUFFER_SIZE];
} msgbuf;

int main() {
    int key_id;
    msgbuf msg;
    msg.msgtype = 1;
    
    key_id = msgget((key_t) 1234, IPC_CREAT|0666);
    if (key_id == -1) {
        perror("Message Get Failed!\n");
        exit(0);
    }
    
    while (1) {
        if (msgrcv(key_id, &msg, sizeof(msg), 1, IPC_NOWAIT) == -1) {
        perror("Message Receiving Failed!\n");
        exit(0);
        }
        
        printf("time: %d\n", msg.time);
    }
}