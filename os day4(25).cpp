#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    // Demonstrate fcntl
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    // Use fcntl here if needed

    // Demonstrate seek
    off_t offset = lseek(fd, 0, SEEK_END);
    printf("File size: %ld bytes\n", (long)offset);

    // Demonstrate stat
    struct stat file_stat;
    if (fstat(fd, &file_stat) == -1) {
        perror("Error getting file status");
        return 1;
    }
    printf("File inode: %ld\n", (long)file_stat.st_ino);

    // Close the file
    close(fd);

    // Demonstrate opendir and readdir
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);

    return 0;
}
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

