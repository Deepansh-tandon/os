
#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int pid;
    int burst_time;
    int remaining_time;
    int arrival_time;
};

void findavgTime(vector<Process>& proc, int n, int time_quantum) {
    int total_wait_time = 0, total_turnaround_time = 0;
    int t = 0;
    bool done = false;

    while (!done) {
        done = true;
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                done = false;
                if (proc[i].remaining_time > time_quantum) {
                    t += time_quantum;
                    proc[i].remaining_time -= time_quantum;
                } else {
                    t += proc[i].remaining_time;
                    total_wait_time += t - proc[i].burst_time - proc[i].arrival_time;
                    total_turnaround_time += t - proc[i].arrival_time;
                    proc[i].remaining_time = 0;
                }
            }
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
        cout << "Enter process ID, burst time, and arrival time for process " << i + 1 << ": ";
        cin >> proc[i].pid >> proc[i].burst_time >> proc[i].arrival_time;
        proc[i].remaining_time = proc[i].burst_time;
    }

    int time_quantum;
    cout << "Enter the time quantum: ";
    cin >> time_quantum;

    findavgTime(proc, n, time_quantum);

    return 0;
}