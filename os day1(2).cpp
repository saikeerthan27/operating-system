#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    // Open source file for reading
    int source_fd = open(argv[1], O_RDONLY);
    if(source_fd == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open destination file for writing (create if not exist, truncate to 0 length)
    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(dest_fd == -1) {
        perror("Error opening destination file");
        close(source_fd);
        exit(EXIT_FAILURE);
    }

    // Copy content from source to destination
    while((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if(bytes_written != bytes_read) {
            perror("Write error");
            close(source_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }

    if(bytes_read == -1) {
        perror("Read error");
        close(source_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }

    // Close files
    if(close(source_fd) == -1 || close(dest_fd) == -1) {
        perror("Error closing files");
        exit(EXIT_FAILURE);
    }

    printf("File copied successfully.\n");

    return 0;
}



