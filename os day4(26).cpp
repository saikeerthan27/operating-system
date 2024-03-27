#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "example.txt";
    char buffer[100];

    // Create a new file
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }

    // Write to the file
    fprintf(file, "Hello, World!\nThis is a test file.");
    fclose(file);

    // Open the file for reading
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read and print the file contents
    printf("File contents:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);

    // Append to the file
    file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file for appending");
        return 1;
    }
    fprintf(file, "\nAppending more data to the file.");
    fclose(file);

    // Open the file again for reading after appending
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read and print the file contents again
    printf("\n\nFile contents after appending:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);

    return 0;
}

