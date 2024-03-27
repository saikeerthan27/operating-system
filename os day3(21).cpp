#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 100
#define PROCESS_SIZE 5

int memory[MEMORY_SIZE];

// Function to initialize memory
void initialize_memory() {
    for (int i = 0; i < MEMORY_SIZE; ++i) {
        memory[i] = 0;
    }
}

// Function to display memory
void display_memory() {
    for (int i = 0; i < MEMORY_SIZE; ++i) {
        printf("%d ", memory[i]);
    }
    printf("\n");
}

// Function to allocate memory using worst fit algorithm
void worst_fit(int process_size) {
    int max_free_space = 0;
    int start_index = -1;
    int count = 0;

    for (int i = 0; i < MEMORY_SIZE; ++i) {
        if (memory[i] == 0) {
            count++;
        } else {
            if (count > max_free_space) {
                max_free_space = count;
                start_index = i - count;
            }
            count = 0;
        }
    }

    if (count > max_free_space) {
        max_free_space = count;
        start_index = MEMORY_SIZE - count;
    }

    if (max_free_space >= process_size) {
        for (int i = start_index; i < start_index + process_size; ++i) {
            memory[i] = 1;
        }
        printf("Process of size %d allocated starting at index %d\n", process_size, start_index);
    } else {
        printf("Not enough memory to allocate process of size %d\n", process_size);
    }
}

int main() {
    initialize_memory();

    // Example allocation requests
    int process_sizes[PROCESS_SIZE] = {10, 20, 5, 30, 15};

    // Allocate memory using worst fit algorithm
    for (int i = 0; i < PROCESS_SIZE; ++i) {
        printf("Memory before allocation of process of size %d: ", process_sizes[i]);
        display_memory();
        worst_fit(process_sizes[i]);
        printf("Memory after allocation of process of size %d: ", process_sizes[i]);
        display_memory();
        printf("\n");
    }

    return 0;
}

