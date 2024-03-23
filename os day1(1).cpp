#include <stdio.h>
#include <unistd.h>

int main() {
    // Create a new process
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process created!\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    } else {
        // Parent process
        printf("Parent process created!\n");
        printf("Parent PID: %d\n", getpid());
        printf("parent PID: %d\n", getppid());
    }

    return 0;
}

