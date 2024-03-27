#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 3 // Number of frames in memory

int main() {
    int reference_string[] = {1, 3, 0, 3, 5, 6, 3}; // Reference string
    int num_pages = sizeof(reference_string) / sizeof(reference_string[0]);
    int frames[FRAME_SIZE]; // Frames in memory
    int page_faults = 0;
    int next_frame = 0; // Index of the next frame to be replaced

    printf("Reference String: ");
    for (int i = 0; i < num_pages; ++i) {
        printf("%d ", reference_string[i]);
    }
    printf("\n");

    // Initialize frames with -1 (indicating empty)
    for (int i = 0; i < FRAME_SIZE; ++i) {
        frames[i] = -1;
    }

    // Simulate FIFO paging
    printf("\nSimulating FIFO Paging:\n");
    for (int i = 0; i < num_pages; ++i) {
        int page = reference_string[i];
        int page_found = 0;

        // Check if page is already in memory
        for (int j = 0; j < FRAME_SIZE; ++j) {
            if (frames[j] == page) {
                page_found = 1;
                break;
            }
        }

        if (!page_found) {
            // Page fault occurred
            ++page_faults;
            printf("Page %d caused a page fault.\n", page);
            frames[next_frame] = page;
            next_frame = (next_frame + 1) % FRAME_SIZE;
        }

        // Display current state of frames
        printf("Frames: ");
        for (int j = 0; j < FRAME_SIZE; ++j) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}

