#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    pthread_t tid = pthread_self();
    printf("Thread ID: %lu\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    printf("Creating a new thread\n");
    pthread_create(&tid, NULL, thread_function, NULL);

    pthread_t current_tid = pthread_self();
    printf("Main Thread ID: %lu\n", current_tid);

    if (pthread_equal(tid, current_tid)) {
        printf("The main thread is equal to the new thread\n");
    } else {
        printf("The main thread is not equal to the new thread\n");
    }

    pthread_join(tid, NULL);
    return 0;
}

