#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    DIR *directory;
    struct dirent *entry;

    // Open the current directory
    directory = opendir(".");
    if (directory == NULL) {
        perror("Error opening directory");
        return 1;
    }

    // Read and print directory contents
    printf("Contents of current directory:\n");
    while ((entry = readdir(directory)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(directory);

    return 0;
}

