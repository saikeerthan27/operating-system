#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 3 // Number of frames in memory

int main() {
    int reference_string[] = {1, 3, 0, 3, 5, 6, 3}; // Reference string
    int num_pages = sizeof(reference_string) / sizeof(reference_string[0]);
    int frames[FRAME_SIZE]; // Frames in memory
    int page_faults = 0;
    int timestamps[FRAME_SIZE]; // Timestamps for LRU
    int next_timestamp = 1; // Next timestamp value

    printf("Reference String: ");
    for (int i = 0; i < num_pages; ++i) {
        printf("%d ", reference_string[i]);
    }
    printf("\n");

    // Initialize frames with -1 (indicating empty) and timestamps to 0
    for (int i = 0; i < FRAME_SIZE; ++i) {
        frames[i] = -1;
        timestamps[i] = 0;
    }

    // Simulate LRU paging
    printf("\nSimulating LRU Paging:\n");
    for (int i = 0; i < num_pages; ++i) {
        int page = reference_string[i];
        int page_found = 0;

        // Check if page is already in memory
        for (int j = 0; j < FRAME_SIZE; ++j) {
            if (frames[j] == page) {
                page_found = 1;
                timestamps[j] = next_timestamp++;
                break;
            }
        }

        if (!page_found) {
            // Page fault occurred
            ++page_faults;
            printf("Page %d caused a page fault.\n", page);
            int least_recently_used = 0;
            for (int j = 1; j < FRAME_SIZE; ++j) {
                if (timestamps[j] < timestamps[least_recently_used]) {
                    least_recently_used = j;
                }
            }
            frames[least_recently_used] = page;
            timestamps[least_recently_used] = next_timestamp++;
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

