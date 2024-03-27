#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 3

pthread_mutex_t mutex;
sem_t reader_sem, writer_sem;

int shared_data = 0;
int readers_count = 0;

void *reader(void *arg) {
    int reader_id = *((int *)arg);

    while (1) {
        // Acquire mutex lock
        pthread_mutex_lock(&mutex);
        readers_count++;

        // If this is the first reader, acquire writer semaphore to block writers
        if (readers_count == 1) {
            sem_wait(&writer_sem);
        }

        // Release mutex lock
        pthread_mutex_unlock(&mutex);

        // Read shared data
        printf("Reader %d reads shared data: %d\n", reader_id, shared_data);

        // Acquire mutex lock
        pthread_mutex_lock(&mutex);
        readers_count--;

        // If this is the last reader, release writer semaphore to allow writers
        if (readers_count == 0) {
            sem_post(&writer_sem);
        }

        // Release mutex lock
        pthread_mutex_unlock(&mutex);

        // Simulate some processing time
        sleep(rand() % 2);
    }

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);

    while (1) {
        // Acquire writer semaphore to block readers and other writers
        sem_wait(&writer_sem);

        // Write to shared data
        shared_data++;
        printf("Writer %d writes shared data: %d\n", writer_id, shared_data);

        // Release writer semaphore
        sem_post(&writer_sem);

        // Simulate some processing time
        sleep(rand() % 2);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t reader_threads[NUM_READERS], writer_threads[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize mutex and semaphores
    pthread_mutex_init(&mutex, NULL);
    sem_init(&reader_sem, 0, 1);
    sem_init(&writer_sem, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; ++i) {
        reader_ids[i] = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; ++i) {
        writer_ids[i] = i + 1;
        pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for reader threads to finish
    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_join(reader_threads[i], NULL);
    }

    // Wait for writer threads to finish
    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_join(writer_threads[i], NULL);
    }

    // Destroy mutex and semaphores
    pthread_mutex_destroy(&mutex);
    sem_destroy(&reader_sem);
    sem_destroy(&writer_sem);

    return 0;
}

