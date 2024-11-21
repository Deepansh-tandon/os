// // // // #include <iostream>
// // // // #include <vector>
// // // // #include <algorithm>

// // // // using namespace std;

// // // // struct Process {
// // // //     int pid;
// // // //     int burst_time;
// // // //     int arrival_time;
// // // //     int remaining_time;
// // // // };

// // // // bool compareArrivalTime(const Process& a, const Process& b) {
// // // //     return a.arrival_time < b.arrival_time;
// // // // }

// // // // void findavgTime(vector<Process>& proc, int n) {
// // // //     int total_wait_time = 0, total_turnaround_time = 0, t = 0;
// // // //     vector<bool> finished(n, false);

// // // //     while (true) {
// // // //         int shortest = -1;
// // // //         int shortest_remaining_time = INT_MAX;

// // // //         for (int i = 0; i < n; i++) {
// // // //             if (!finished[i] && proc[i].arrival_time <= t && proc[i].remaining_time < shortest_remaining_time && proc[i].remaining_time > 0) {
// // // //                 shortest = i;
// // // //                 shortest_remaining_time = proc[i].remaining_time;
// // // //             }
// // // //         }

// // // //         if (shortest == -1) {
// // // //             break;
// // // //         }

// // // //         t++;
// // // //         proc[shortest].remaining_time--;

// // // //         if (proc[shortest].remaining_time == 0) {
// // // //             finished[shortest] = true;
// // // //             total_wait_time += t - proc[shortest].burst_time - proc[shortest].arrival_time;
// // // //             total_turnaround_time += t - proc[shortest].arrival_time;
// // // //         }
// // // //     }

// // // //     float avg_wait_time = (float)total_wait_time / (float)n;
// // // //     float avg_turnaround_time = (float)total_turnaround_time / (float)n;
// // // //     cout << "\nAverage waiting time = " << avg_wait_time;
// // // //     cout << "\nAverage turn-around time = " << avg_turnaround_time;
// // // // }

// // // // int main() {
// // // //     int n;
// // // //     cout << "Enter the number of processes: ";
// // // //     cin >> n;

// // // //     vector<Process> proc(n);

// // // //     for (int i = 0; i < n; i++) {
// // // //         cout << "Enter process ID, burst time, and arrival time for process " << i + 1 << ": ";
// // // //         cin >> proc[i].pid >> proc[i].burst_time >> proc[i].arrival_time;
// // // //         proc[i].remaining_time = proc[i].burst_time;
// // // //     }

// // // //     sort(proc.begin(), proc.end(), compareArrivalTime);

// // // //     findavgTime(proc, n);

// // // //     return 0;
// // // // }

// // // #include <iostream>
// // // #include <vector>
// // // #include <climits>
// // // #include <algorithm>
// // // using namespace std;

// // // class Process {
// // // public:
// // //     int pid;       // Process ID
// // //     int arr_time;  // Arrival Time
// // //     int bt;        // Burst Time
// // //     int rem_bt;    // Remaining Burst Time (used in Preemptive SJF)
// // //     int wait_time; // Waiting Time
// // //     int tat;       // Turnaround Time

// // //     Process(int id, int at, int burstt) {
// // //         pid = id;
// // //         arr_time = at;
// // //         bt = burstt;
// // //         rem_bt = burstt;        // Initially, remaining burst time is the total burst time
// // //         wait_time = tat = 0;    // Initialize wait time and turnaround time
// // //     }
// // // };

// // // // Helper function to display results
// // // void display(vector<Process> &p, string order) {
// // //     int total_wait_time = 0, total_tat = 0;
// // //     int n = p.size();

// // //     cout << "\nExecution Order: " << order << endl;
// // //     cout << "\nPID\tWaiting Time\tTurnaround Time\n";
// // //     for (auto &proc : p) {
// // //         total_wait_time += proc.wait_time;
// // //         total_tat += proc.tat;
// // //         cout << proc.pid << "\t" << proc.wait_time << "\t\t" << proc.tat << endl;
// // //     }

// // //     cout << "\nAverage Waiting Time = " << (float)total_wait_time / n;
// // //     cout << "\nAverage Turnaround Time = " << (float)total_tat / n << endl;
// // // }

// // // // FCFS Scheduling
// // // void fcfs(vector<Process> &p) {
// // //     sort(p.begin(), p.end(), [](Process &a, Process &b) { return a.arr_time < b.arr_time; });

// // //     int ct = 0;  // Current time
// // //     string order;

// // //     for (auto &proc : p) {
// // //         if (ct < proc.arr_time) ct = proc.arr_time;  // Wait for the process to arrive
// // //         proc.wait_time = ct - proc.arr_time;
// // //         ct += proc.bt;
// // //         proc.tat = proc.wait_time + proc.bt;
// // //         order += "P" + to_string(proc.pid) + " ";
// // //     }

// // //     display(p, order);
// // // }

// // // // Preemptive SJF Scheduling
// // // void sjfPreemptive(vector<Process> &p) {
// // //     int n = p.size();
// // //     int completed = 0;         // Number of processes completed
// // //     int current_time = 0;      // Current time
// // //     int prev_time = -1;        // To track CPU idle periods
// // //     string order;              // Execution order

// // //     // Sort by arrival time initially
// // //     sort(p.begin(), p.end(), [](Process &a, Process &b) { return a.arr_time < b.arr_time; });

// // //     vector<bool> completed_flags(n, false); // Track completed processes

// // //     while (completed < n) {
// // //         // Find the process with the shortest remaining burst time that has arrived
// // //         int idx = -1;
// // //         int shortest = INT_MAX;

// // //         for (int i = 0; i < n; i++) {
// // //             if (!completed_flags[i] && p[i].arr_time <= current_time && p[i].rem_bt < shortest) {
// // //                 shortest = p[i].rem_bt;
// // //                 idx = i;
// // //             }
// // //         }

// // //         if (idx == -1) {
// // //             // If no process is ready, increment time
// // //             current_time++;
// // //             continue;
// // //         }

// // //         // Process selected for execution
// // //         if (prev_time != idx) {
// // //             order += "P" + to_string(p[idx].pid) + " ";
// // //             prev_time = idx;
// // //         }

// // //         // Execute the process for one unit of time
// // //         p[idx].rem_bt--;
// // //         current_time++;

// // //         // If the process is completed
// // //         if (p[idx].rem_bt == 0) {
// // //             completed++;
// // //             completed_flags[idx] = true;
// // //             p[idx].tat = current_time - p[idx].arr_time;  // Turnaround time
// // //             p[idx].wait_time = p[idx].tat - p[idx].bt;    // Waiting time
// // //         }
// // //     }

// // //     display(p, order);
// // // }

// // // int main() {
// // //     vector<Process> p;
// // //     int n;

// // //     cout << "Enter the number of processes: ";
// // //     cin >> n;

// // //     for (int i = 0; i < n; i++) {
// // //         int id, at, bt;
// // //         cout << "Enter the process ID, arrival time, and burst time for process " << i + 1 << ": ";
// // //         cin >> id >> at >> bt;
// // //         p.push_back(Process(id, at, bt));
// // //     }

// // //     int choice;
// // //     do {
// // //         cout << "\nSelect Scheduling Algorithm:\n";
// // //         cout << "1. First-Come-First-Serve (FCFS)\n";
// // //         cout << "2. Shortest Job First (SJF) - Preemptive\n";
// // //         cout << "3. Exit\n";
// // //         cout << "Enter your choice: ";
// // //         cin >> choice;

// // //         switch (choice) {
// // //             case 1:
// // //                 cout << "\n--- First-Come-First-Serve (FCFS) Scheduling ---\n";
// // //                 fcfs(p);
// // //                 break;
// // //             case 2:
// // //                 cout << "\n--- Shortest Job First (SJF) - Preemptive Scheduling ---\n";
// // //                 sjfPreemptive(p);
// // //                 break;
// // //             case 3:
// // //                 cout << "Exiting...\n";
// // //                 break;
// // //             default:
// // //                 cout << "Invalid choice. Please try again.\n";
// // //         }
// // //     } while (choice != 3);

// // //     return 0;
// // // }

// // #include <iostream>
// // #include <vector>
// // #include <queue>
// // #include <climits>
// // using namespace std;

// // class Process {
// // public:
// //     int pid;         // Process ID
// //     int arr_time;    // Arrival Time
// //     int bt;          // Burst Time
// //     int priority;    // Priority of the process
// //     int wait_time;   // Waiting Time
// //     int tat;         // Turnaround Time

// //     Process(int id, int at, int burstt, int prio) {
// //         pid = id;
// //         arr_time = at;
// //         bt = burstt;
// //         priority = prio;
// //         wait_time = tat = 0; // Initialize wait time and turnaround time
// //     }
// // };

// // // Comparator for sorting processes by arrival time
// // bool compare(Process &a, Process &b) {
// //     return a.arr_time < b.arr_time;
// // }

// // // Function to display process details and averages
// // void display(vector<Process> &p) {
// //     int total_wait_time = 0, total_tat = 0;
// //     int n = p.size();

// //     cout << "\nPID\tWaiting Time\tTurnaround Time\n";
// //     for (auto &a : p) {
// //         total_wait_time += a.wait_time;
// //         total_tat += a.tat;
// //         cout << a.pid << "\t" << a.wait_time << "\t\t" << a.tat << endl;
// //     }

// //     cout << "\nAverage Waiting Time = " << (float)total_wait_time / n;
// //     cout << "\nAverage Turnaround Time = " << (float)total_tat / n << endl;
// // }

// // // Preemptive Priority Scheduling
// // void preemptivePriorityScheduling(vector<Process> &p) {
// //     int n = p.size();
// //     int current_time = 0;
// //     vector<int> remaining_bt(n);
// //     for (int i = 0; i < n; i++) {
// //         remaining_bt[i] = p[i].bt;  // Initialize remaining burst times
// //     }
// //     vector<bool> completed(n, false);
// //     int completed_count = 0;
// //     string order;
// //     while (completed_count < n) {
// //         int highest_priority = INT_MAX;
// //         int process_idx = -1;
// //         // Find the process with the highest priority (lowest priority number)
// //         for (int i = 0; i < n; i++) {
// //             if (!completed[i] && p[i].arr_time <= current_time && p[i].priority < highest_priority) {
// //                 highest_priority = p[i].priority;
// //                 process_idx = i;
// //             }
// //         }
// //         if (process_idx == -1) {
// //             current_time++; // If no process is available, increase time
// //             continue;
// //         }
// //         // Execute the selected process for one unit of time
// //         order += "P" + to_string(p[process_idx].pid) + " ";
// //         remaining_bt[process_idx]--;
// //         if (remaining_bt[process_idx] == 0) {
// //             completed[process_idx] = true;
// //             completed_count++;
// //             p[process_idx].tat = current_time + 1 - p[process_idx].arr_time;
// //             p[process_idx].wait_time = p[process_idx].tat - p[process_idx].bt;
// //         }
// //         current_time++; // Increase current time
// //     }
// //     display(p);
// // }

// // int main() {
// //     vector<Process> p;
// //     int n;
// //     cout << "Enter the number of processes: ";
// //     cin >> n;

// //     for (int i = 0; i < n; i++) {
// //         int id, at, bt, prio;
// //         cout << "Enter the process ID, arrival time, burst time, and priority for process " << i + 1 << ": ";
// //         cin >> id >> at >> bt >> prio;
// //         p.push_back(Process(id, at, bt, prio));
// //     }

// //     cout << "\n--- Preemptive Priority Scheduling ---";
// //     preemptivePriorityScheduling(p);

// //     return 0;
// // }


// void roundRobin(vector<Process> &p, int time_quantum) {
//     int n = p.size();
//     int current_time = 0; // Tracks the current time
//     int completed_count = 0;
//     queue<int> ready_queue; // Queue of process indices
//     string order;

//     vector<int> remaining_bt(n); // Remaining burst time for each process
//     for (int i = 0; i < n; i++) {
//         remaining_bt[i] = p[i].bt;
//     }

//     // Push processes to the ready queue as they arrive
//     int idx = 0;
//     while (completed_count < n) {
//         while (idx < n && p[idx].arr_time <= current_time) {
//             ready_queue.push(idx);
//             idx++;
//         }

//         if (ready_queue.empty()) {
//             current_time++; // If no process is available, increment time
//             continue;
//         }

//         int current_process = ready_queue.front();
//         ready_queue.pop();

//         // Execute the current process for a time slice or until completion
//         if (remaining_bt[current_process] > time_quantum) {
//             current_time += time_quantum;
//             remaining_bt[current_process] -= time_quantum;

//             order += "P" + to_string(p[current_process].pid) + " ";

//             // Add processes arriving during this time to the queue
//             while (idx < n && p[idx].arr_time <= current_time) {
//                 ready_queue.push(idx);
//                 idx++;
//             }

//             // Re-add the current process to the queue
//             ready_queue.push(current_process);
//         } else {
//             // Process finishes execution
//             current_time += remaining_bt[current_process];
//             remaining_bt[current_process] = 0;

//             order += "P" + to_string(p[current_process].pid) + " ";

//             p[current_process].tat = current_time - p[current_process].arr_time;
//             p[current_process].wait_time = p[current_process].tat - p[current_process].bt;

//             completed_count++;
//         }
//     }

//     display(p, order);
// }
