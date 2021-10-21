#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h> // for thread


int ncount; // shared data
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // thread Initializing

void* thread1(void *data) {
    pthread_mutex_lock(&mutex); // Locking   
    
    for (int i = 0; i < 10; i++) {
        printf("thread1: %d\n", ncount);
        ncount++;
        sleep(1);
    }

    pthread_mutex_unlock(&mutex); // Unlocking
} 

void* thread2(void *data) {    
    // Wait until 'thread1' unlock
    pthread_mutex_lock(&mutex); // Locking
    
    for (int i = 0; i < 10; i++) {
        printf("thread2: %d\n", ncount);
        ncount++;
        sleep(1);
    }

    pthread_mutex_unlock(&mutex); // Unlocking
} 

int main() {  
    int thr_id;
    pthread_t p_thread[2]; // 2 thread
    int status;
    int a = 1;
    ncount = 0;

    // thread 1
    thr_id = pthread_create(&p_thread[0], NULL, thread1, (void*)&a);
    sleep(1);
    // thread 2
    thr_id = pthread_create(&p_thread[1], NULL, thread2, (void*)&a);

    pthread_join(p_thread[0], (void*) &status);
    pthread_join(p_thread[1], (void*) &status);

    status = pthread_mutex_destroy(&mutex); // return 0 if successful

    printf("\ncode = %d", status);
    printf("\nProgram is end!\n");
   
    return 0;
}