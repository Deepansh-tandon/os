
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int priority;
    int remaining_time;
};

bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrival_time < b.arrival_time;
}

void findavgTime(vector<Process>& proc, int n) {
    int total_wait_time = 0, total_turnaround_time = 0, t = 0;
    vector<bool> finished(n, false);

    while (true) {
        int highest_priority = INT_MAX;
        int highest_priority_process = -1;

        for (int i = 0; i < n; i++) {
            if (!finished[i] && proc[i].arrival_time <= t && proc[i].priority < highest_priority) {
                highest_priority = proc[i].priority;
                highest_priority_process = i;
            }
        }

        if (highest_priority_process == -1) {
            break;
        }

        t++;
        proc[highest_priority_process].remaining_time--;

        if (proc[highest_priority_process].remaining_time == 0) {
            finished[highest_priority_process] = true;
            total_wait_time += t - proc[highest_priority_process].burst_time - proc[highest_priority_process].arrival_time;
            total_turnaround_time += t - proc[highest_priority_process].arrival_time;
        }
    }

    float avg_wait_time = (float)total_wait_time / (float)n;
    float avg_turnaround_time = (float)total_turnaround_time / (float)n;
    cout << "\nAverage waiting time = " << avg_wait_time;
    cout << "\nAverage turn-around time = " << avg_turnaround_time;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> proc(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter process ID, burst time, arrival time, and priority for process " << i + 1 << ": ";
        cin >> proc[i].pid >> proc[i].burst_time >> proc[i].arrival_time >> proc[i].priority;
        proc[i].remaining_time = proc[i].burst_time;
    }

    sort(proc.begin(), proc.end(), compareArrivalTime);

    findavgTime(proc, n);

    return 0;
}