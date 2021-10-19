#include <stdio.h> // 입출력 함수
#include <stdlib.h> // exit 함수
#include <sys/types.h> 
#include <unistd.h> // fork 함수
#include <sys/wait.h> // wait 함수

#define NUM 10

int main(void) {
    pid_t pid[NUM];
    int status;

    for (int i = 0; i < NUM; i++) {
        pid[i] = fork();

        if (pid[i] > 0) {
            printf("Parent[pp:%d, p:%d, c:%d]: waiting...\n", getppid(), getpid(), pid[i]);
            sleep(1);
            kill(pid[i], SIGTERM);
            printf("Child[pp:%d, p:%d]: killed...\n", getppid(), getpid());
            wait(&status); // 자식 프로세스 종료 시점까지 대기
            printf("Parent: status is %d\n", status);
        }

        else if (pid[i] == 0) {
            sleep(15);
            printf("Child[pp:%d, p:%d]: bye!\n", getppid(), getpid());
            exit(1234);
        }

        else
            printf("Failed to fork!\n");
    }

    printf("Bye!\n");
    return 0;
}
