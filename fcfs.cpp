#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Process {
public:
    int pid;
    int burst_time;
    int arrival_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;

    Process(int pid, int burst_time, int arrival_time) {
        this->pid = pid;
        this->burst_time = burst_time;
        this->arrival_time = arrival_time;

    }
};

bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrival_time < b.arrival_time;
}

void findavgTime(vector<Process>& proc, int n) {
    int total_wait_time = 0, total_turnaround_time = 0, t = 0;
    
    // Sort processes by arrival time
    sort(proc.begin(), proc.end(), compareArrivalTime);

    for(int i=0;i<n;i++){
        if (i == 0) {
            proc[i].start_time = proc[i].arrival_time;
        }
        else{
            proc[i].start_time = max(t, proc[i].arrival_time);
        }
        proc[i].completion_time = proc[i].start_time + proc[i].burst_time;
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time 
        - proc[i].burst_time;
        
        t = proc[i].completion_time;
        
        total_wait_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;

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
    
    vector<Process> proc;
    
    for (int i = 0; i < n; i++) {
        int pid, burst_time, arrival_time;
        cout << "Enter process ID, burst time, and arrival time for process " << i + 1 << ": ";
        cin >> pid >> burst_time >> arrival_time;
        proc.push_back(Process(pid, burst_time, arrival_time));
    }
    
    sort(proc.begin(), proc.end(), compareArrivalTime);
    
    findavgTime(proc, n);
    
    return 0;
}