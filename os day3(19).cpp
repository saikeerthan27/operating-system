#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define COUNT_LIMIT 10

int count = 0;
pthread_mutex_t count_mutex;

void *increment_counter(void *thread_id) {
    int tid = *((int *)thread_id);

    for (int i = 0; i < COUNT_LIMIT; ++i) {
        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Thread %d incremented count to %d\n", tid, count);
        pthread_mutex_unlock(&count_mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize mutex
    pthread_mutex_init(&count_mutex, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, increment_counter, &thread_ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&count_mutex);

    return 0;
}

