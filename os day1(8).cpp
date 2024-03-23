#include <stdio.h>

#define MAX_PROCESSES 10
#define TIME_QUANTUM 2

struct Process {
    int pid;          // Process ID
    int burst;        // Burst time
    int remaining;    // Remaining burst time
    int waiting;      // Waiting time
    int turnaround;   // Turnaround time
};

void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;
    int completedProcesses = 0;
    int timeQuantum = TIME_QUANTUM;
    int nextProcess = 0;

    while (completedProcesses < n) {
        if (processes[nextProcess].remaining > 0) {
            // Execute the current process for the time quantum or until it completes
            if (processes[nextProcess].remaining <= timeQuantum) {
                currentTime += processes[nextProcess].remaining;
                processes[nextProcess].waiting += currentTime - processes[nextProcess].burst - processes[nextProcess].turnaround;
                processes[nextProcess].remaining = 0;
                processes[nextProcess].turnaround = currentTime;
                completedProcesses++;
            } else {
                currentTime += timeQuantum;
                processes[nextProcess].waiting += currentTime - processes[nextProcess].burst - processes[nextProcess].turnaround;
                processes[nextProcess].remaining -= timeQuantum;
            }
        }

        // Move to the next process in a circular manner
        nextProcess = (nextProcess + 1) % n;
    }
}

void printTable(struct Process processes[], int n) {
    printf("PID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst, 
               processes[i].waiting, processes[i].turnaround);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[MAX_PROCESSES];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst);
        processes[i].pid = i + 1;
        processes[i].remaining = processes[i].burst;
        processes[i].waiting = 0;
        processes[i].turnaround = 0;
    }

    calculateTimes(processes, n);

    // Print the table
    printf("\nGantt Chart for Round Robin Scheduling with Time Quantum %d\n", TIME_QUANTUM);
    printTable(processes, n);

    return 0;
}

