#include <stdio.h>

struct Process {
    int pid;       // Process ID
    int arrival;   // Arrival time
    int burst;     // Burst time
    int waiting;   // Waiting time
    int turnaround; // Turnaround time
};

void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        // Waiting time for current process
        processes[i].waiting = currentTime - processes[i].arrival;

        // Turnaround time for current process
        processes[i].turnaround = processes[i].waiting + processes[i].burst;

        // Update current time
        currentTime += processes[i].burst;
    }
}

void printTable(struct Process processes[], int n) {
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival, 
               processes[i].burst, processes[i].waiting, processes[i].turnaround);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
        processes[i].pid = i + 1;
    }

    // Sort processes by arrival time (FCFS doesn't require sorting, but for uniformity)
    // This is just for educational purposes, as FCFS doesn't depend on sorting
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival > processes[j + 1].arrival) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    calculateTimes(processes, n);

    // Print the table
    printf("\nGantt Chart for First Come First Served (FCFS) Scheduling\n");
    printTable(processes, n);

    return 0;
}

