#include <stdio.h>

struct Process {
    int pid;       // Process ID
    int arrival;   // Arrival time
    int burst;     // Burst time
    int priority;  // Priority
    int waiting;   // Waiting time
    int turnaround; // Turnaround time
    int completed; // Flag to indicate if the process has completed execution
};

void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;
    int completedProcesses = 0;
    while (completedProcesses < n) {
        int highestPriority = -1;
        int highestIndex = -1;

        // Find the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival <= currentTime) {
                if (highestPriority == -1 || processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    highestIndex = i;
                }
            }
        }

        // If no process is found, move time forward to the next arrival
        if (highestIndex == -1) {
            int nextArrival = -1;
            for (int i = 0; i < n; i++) {
                if (!processes[i].completed && (nextArrival == -1 || processes[i].arrival < nextArrival)) {
                    nextArrival = processes[i].arrival;
                }
            }
            currentTime = nextArrival;
        } else {
            // Execute the highest priority process
            processes[highestIndex].waiting = currentTime - processes[highestIndex].arrival;
            processes[highestIndex].turnaround = processes[highestIndex].waiting + processes[highestIndex].burst;
            processes[highestIndex].completed = 1;
            currentTime += processes[highestIndex].burst;
            completedProcesses++;
        }
    }
}

void printTable(struct Process processes[], int n) {
    printf("PID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival, 
               processes[i].burst, processes[i].priority, processes[i].waiting, processes[i].turnaround);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival, &processes[i].burst, &processes[i].priority);
        processes[i].pid = i + 1;
        processes[i].completed = 0;
    }

    calculateTimes(processes, n);

    // Print the table
    printf("\nGantt Chart for Priority Scheduling\n");
    printTable(processes, n);

    return 0;
}

