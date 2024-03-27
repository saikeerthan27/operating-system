#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    printf("Inside the new thread\n");
    pthread_exit(NULL); // Exit the thread
}

int main() {
    pthread_t tid;
    printf("Creating a new thread\n");
    pthread_create(&tid, NULL, thread_function, NULL);
    pthread_join(tid, NULL); // Wait for the thread to finish
    printf("Back to the main thread\n");
    return 0;
}

