#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int pid;            // Process ID
    int burst_time;     // CPU Burst time required by the process
    int arrival_time;   // Arrival time of the process
    int wait_time;      // Waiting time of the process
    int turnaround_time; // Turnaround time of the process
};

// Function to find the process with the shortest burst time available
int findNextProcess(vector<Process>& proc, int current_time, vector<bool>& completed) {
    int n = proc.size();
    int shortest = -1;
    int min_burst_time = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (!completed[i] && proc[i].arrival_time <= current_time && proc[i].burst_time < min_burst_time) {
            shortest = i;
            min_burst_time = proc[i].burst_time;
        }
    }
    return shortest;
}

void findAvgTime(vector<Process>& proc) {
    int n = proc.size();
    vector<bool> completed(n, false);
    int total_wait_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;
    int completed_count = 0;

    while (completed_count < n) {
        int idx = findNextProcess(proc, current_time, completed);

        if (idx == -1) {
            // If no process has arrived, move the time forward
            current_time++;
            continue;
        }

        // Process the selected job
        completed[idx] = true;
        completed_count++;

        if (current_time < proc[idx].arrival_time) {
            current_time = proc[idx].arrival_time;
        }

        proc[idx].wait_time = current_time - proc[idx].arrival_time;
        proc[idx].turnaround_time = proc[idx].wait_time + proc[idx].burst_time;

        total_wait_time += proc[idx].wait_time;
        total_turnaround_time += proc[idx].turnaround_time;

        current_time += proc[idx].burst_time; // Move current time forward
    }

    // Print process details
    cout << "\nProcess ID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n";
    for (const auto &p : proc) {
        cout << p.pid << "\t\t" << p.burst_time << "\t\t" << p.arrival_time
             << "\t\t" << p.wait_time << "\t\t" << p.turnaround_time << "\n";
    }

    cout << "\nAverage Waiting Time = " << (float)total_wait_time / n;
    cout << "\nAverage Turnaround Time = " << (float)total_turnaround_time / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> proc(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter process ID, burst time, and arrival time for process " << i + 1 << ": ";
        cin >> proc[i].pid >> proc[i].burst_time >> proc[i].arrival_time;
        proc[i].wait_time = proc[i].turnaround_time = 0; // Initialize wait and turnaround times
    }

    findAvgTime(proc);

    return 0;
}
