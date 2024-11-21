#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Process {
    int pid; // Process ID
    int arrivalTime;
    int burstTime;
    int priority;
    int waitingTime = 0;
    int turnAroundTime = 0;
    int remainingTime; // For preemptive algorithms
};

// Utility function to display results
void displayResults(vector<Process> &processes, string executionOrder) {
    cout << "\nExecution Order: " << executionOrder << endl;
    float totalWaitingTime = 0;
    cout << "\nPID\tWaiting Time\tTurnaround Time\n";
    for (auto &p : processes) {
        totalWaitingTime += p.waitingTime;
        cout << p.pid << "\t" << p.waitingTime << "\t\t" << p.turnAroundTime << endl;
    }
    cout << "\nAverage Waiting Time: " << totalWaitingTime / processes.size() << endl;
}

// First-Come-First-Served Scheduling
void fcfs(vector<Process> processes) {
    sort(processes.begin(), processes.end(), [](Process &a, Process &b) {
        return a.arrivalTime < b.arrivalTime;
    });

    string executionOrder;
    int currentTime = 0;
    for (auto &p : processes) {
        if (currentTime < p.arrivalTime) currentTime = p.arrivalTime;
        p.waitingTime = currentTime - p.arrivalTime;
        currentTime += p.burstTime;
        p.turnAroundTime = p.waitingTime + p.burstTime;
        executionOrder += "P" + to_string(p.pid) + " ";
    }

    displayResults(processes, executionOrder);
}

// Shortest Job First (Non-preemptive)
void  sjfNonPreemptive(vector<Process> processes) {
    sort(processes.begin(), processes.end(), [](Process &a, Process &b) {
        return a.arrivalTime < b.arrivalTime;
    });

    string executionOrder;
    int currentTime = 0, completed = 0;
    while (completed < processes.size()) {
        auto it = min_element(processes.begin(), processes.end(), [&](Process &a, Process &b) {
            if (a.remainingTime <= 0) return false;
            if (b.remainingTime <= 0) return true;
            if (currentTime >= a.arrivalTime && currentTime >= b.arrivalTime)
                return a.burstTime < b.burstTime;
            return a.arrivalTime < b.arrivalTime;
        });

        if (it != processes.end() && it->remainingTime > 0 && it->arrivalTime <= currentTime) {
        }
        if (it != processes.end() && it->remainingTime > 0 && it->arrivalTime <= currentTime) {
            Process &p = *it;
            p.waitingTime = currentTime - p.arrivalTime;
            currentTime += p.burstTime;
            p.turnAroundTime = p.waitingTime + p.burstTime;
            p.remainingTime = 0; // Mark as completed
            completed++;
            executionOrder += "P" + to_string(p.pid) + " ";
        } else {
            currentTime++; // Advance time if no process is ready
        }
    }

    displayResults(processes, executionOrder);
}

// Shortest Job First (Preemptive)
void sjfPreemptive(vector<Process> processes) {
    int currentTime = 0, completed = 0;
    string executionOrder;

    while (completed < processes.size()) {
        auto it = min_element(processes.begin(), processes.end(), [&](Process &a, Process &b) {
            if (a.remainingTime <= 0) return false;
            if (b.remainingTime <= 0) return true;
            if (currentTime >= a.arrivalTime && currentTime >= b.arrivalTime)
                return a.remainingTime < b.remainingTime;
            return a.arrivalTime < b.arrivalTime;
        });

        if (it != processes.end() && it->remainingTime > 0 && it->arrivalTime <= currentTime) {
            Process &p = *it;
            executionOrder += "P" + to_string(p.pid) + " ";
            p.remainingTime--;
            currentTime++;

            if (p.remainingTime == 0) {
                completed++;
                p.turnAroundTime = currentTime - p.arrivalTime;
                p.waitingTime = p.turnAroundTime - p.burstTime;
            }
        } else {
            currentTime++; // Advance time if no process is ready
        }
    }

    displayResults(processes, executionOrder);
}

// Priority Scheduling (Non-preemptive)
void priorityScheduling(vector<Process> processes) {
    sort(processes.begin(), processes.end(), [](Process &a, Process &b) {
        return a.arrivalTime < b.arrivalTime;
    });

    string executionOrder;
    int currentTime = 0, completed = 0;
    while (completed < processes.size()) {
        auto it = min_element(processes.begin(), processes.end(), [&](Process &a, Process &b) {
            if (a.remainingTime <= 0) return false;
            if (b.remainingTime <= 0) return true;
            if (currentTime >= a.arrivalTime && currentTime >= b.arrivalTime)
                return a.priority < b.priority;
            return a.arrivalTime < b.arrivalTime;
        });

        if (it != processes.end() && it->remainingTime > 0 && it->arrivalTime <= currentTime) {
            Process &p = *it;
            p.waitingTime = currentTime - p.arrivalTime;
            currentTime += p.burstTime;
            p.turnAroundTime = p.waitingTime + p.burstTime;
            p.remainingTime = 0; // Mark as completed
            completed++;
            executionOrder += "P" + to_string(p.pid) + " ";
        } else {
            currentTime++; // Advance time if no process is ready
        }
    }

    displayResults(processes, executionOrder);
}

// Round Robin Scheduling
void roundRobin(vector<Process> processes, int timeQuantum) {
    queue<Process *> readyQueue;
    int currentTime = 0;
    string executionOrder;

    for (auto &p : processes) {
        p.remainingTime = p.burstTime; // Initialize remaining time
    }

    while (true) {
        bool allCompleted = true;
        for (auto &p : processes) {
            if (p.remainingTime > 0) {
                allCompleted = false;
                if (p.arrivalTime <= currentTime && p.remainingTime > 0) {
                    executionOrder += "P" + to_string(p.pid) + " ";
                    if (p.remainingTime <= timeQuantum) {
                        currentTime += p.remainingTime;
                        p.remainingTime = 0;
                        p.turnAroundTime = currentTime - p.arrivalTime;
                        p.waitingTime = p.turnAroundTime - p.burstTime;
                    } else {
                        currentTime += timeQuantum;
                        p.remainingTime -= timeQuantum;
                    }
                }
            }
        }
        if (allCompleted) break;
    }

    displayResults(processes, executionOrder);
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter arrival time, burst time, and priority for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
        processes[i].pid = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
    }

    cout << "\nSelect a scheduling algorithm:\n";
    cout << "1. FCFS\n2. SJF (Non-preemptive)\n3. SJF (Preemptive)\n4. Priority Scheduling\n5. Round Robin\n";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            fcfs(processes);
            break;
        case 2:
            sjfNonPreemptive(processes);
            break;
        case 3:
            sjfPreemptive(processes);
            break;
        case 4:
            priorityScheduling(processes);
            break;
        case 5:
            int timeQuantum;
            cout << "Enter time quantum for Round Robin: ";
            cin >> timeQuantum;
            roundRobin(processes, timeQuantum);
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }

    return 0;
}
