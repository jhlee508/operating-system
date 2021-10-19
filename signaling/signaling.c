#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for Linux Compiling (GCC)
#include <signal.h> 


void handlerFunction(int sig) { // Handler Function
  printf("\n>>> Received Keyboard Interupt(Ctrl+c) Signal!\n");
  printf(">>> Program will be terminated, if one more Keyboard Interupt Signal!!!\n");

  // SIGINT: Signal Terminal Interupt
  // SIG_DFL: Default Action for Signal (kill terminal if received SIGINT again)
  signal(SIGINT, SIG_DFL);
}

int main() {
    // Execute 'handlerFunction()' if received SIGINT(Keyboard Interupt: 'Ctrl + c')
    signal(SIGINT, handlerFunction);

    int cnt = 0;
    while(1) {
        printf("Time: %d(sec)\n", cnt++);
        sleep(1);
    }

    printf("Program Terminating...\n");

    exit(0);
}