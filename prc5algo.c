// premeive round robin
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;        // Process ID
    int burst_time; // Burst Time
    int wait_time;  // Wait Time
    int tat;        // Turnaround Time
    int remaining_time; // Remaining Time
} Process;

void calculateTimes(Process proc[], int n, int quantum) {
    int time = 0;
    int processes_left = n;

    while (processes_left > 0) {
        for (int i = 0; i < n; ++i) {
            if (proc[i].remaining_time > 0) {
                if (proc[i].remaining_time > quantum) {
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    time += proc[i].remaining_time;
                    proc[i].wait_time = time - proc[i].burst_time;
                    proc[i].remaining_time = 0;
                    proc[i].tat = proc[i].wait_time + proc[i].burst_time;
                    processes_left--;
                }
            }
        }
    }
}

void printAvgTimes(Process proc[], int n) {
    int total_wait_time = 0, total_tat = 0;

    printf("\nPID\tBurst Time\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; ++i) {
        total_wait_time += proc[i].wait_time;
        total_tat += proc[i].tat;
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].wait_time, proc[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_wait_time / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_tat / n);
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process proc[n];

    for (int i = 0; i < n; ++i) {
        proc[i].pid = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].wait_time = 0;
        proc[i].tat = 0;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    calculateTimes(proc, n, quantum);
    printAvgTimes(proc, n);

    return 0;
}

non-preemive- fcfs
#include <stdio.h>

struct Process {
    int pid; // Process ID
    int arrival_time; // Arrival Time
    int burst_time; // Burst Time
    int waiting_time; // Waiting Time
    int turnaround_time; // Turnaround Time
};

void findWaitingTime(struct Process proc[], int n) {
    proc[0].waiting_time = 0; // Waiting time for the first process is 0

    // Calculating waiting time for each process
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i - 1].burst_time + proc[i - 1].waiting_time;
    }
}

void findTurnaroundTime(struct Process proc[], int n) {
    // Calculating turnaround time for each process
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

void findAverageTime(struct Process proc[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;

    findWaitingTime(proc, n);
    findTurnaroundTime(proc, n);

    printf("Processes  Burst Time  Waiting Time  Turnaround Time\n");

    // Calculating total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
        printf("   %d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
    }

    printf("\nAverage waiting time = %.2f", (float)total_waiting_time / n);
    printf("\nAverage turnaround time = %.2f", (float)total_turnaround_time / n);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input burst time and arrival time for each process
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].arrival_time);
        printf("Enter burst time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].burst_time);
    }

    // Sorting processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival_time > proc[j + 1].arrival_time) {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    findAverageTime(proc, n);

    return 0;
}
