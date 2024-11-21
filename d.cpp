// #include<iostream>
// #include<vector>
// #include<algorithm>
// using namespace std;

// class Process
// {
//     public :
//     int pid;
//     int arr_time;
//     int wait_time;
//     int tat;
//     int bt;

//     Process(int id, int at, int burstt){
//         pid=id;
//         arr_time=at;
//         bt=burstt;
//     }
// };

// bool compare(Process &a,Process &b){
//     return a.arr_time<b.arr_time;
// }

// void display(vector <Process> &p, string order){
//  int awt=0;
//  int atat=0;
//    cout << "\nExecution Order: " << order << endl;
//     float totalWaitingTime = 0;
//     cout << "\nPID\tWaiting Time\tTurnaround Time\n";
//  int n=p.size();
//  for(auto &a:p){
//     awt+=a.wait_time;
//     cout<<a.pid<< "\t" << a.wait_time << "\t" << a.tat << endl;
//  }
//  cout<<"avg waiting time"<< awt/n<<endl;
// }

// void fcfs(vector <Process> &p){
//     sort(p.begin(),p.end(),compare);
//     int ct=0;string order;
//     for(auto &i:p){
//         if(ct<i.arr_time)
//         ct=i.arr_time;
//         i.wait_time=ct-i.arr_time;
//         ct+=i.bt;
//         i.tat=i.wait_time+i.bt;
//         order+="P" + to_string(i.pid) + " ";
//     }
//     display(p,order);
// } 

// int findnext(vector<Process> &p, int ct,vector<bool> completed){
//     int n=p.size();
//     int s=-1;
//     int sbt=INT_MAX;

//     for (auto &a:p)
//     {
//         if(!completed[a.pid]&&a.arr_time<=ct&&a.bt<=sbt){
//             s=a.pid;
//             sbt=a.bt;
//         }
//     }
//     return s;
// }

// void sjf(vector<Process> &p){
//     int n=p.size();
//     int completiontime=0;
//     int comp=0;
//     vector<bool> completed(n,false);

//     while(comp<n){
//       int i= findnext(p,completiontime,completed);
//       if(i==-1)
//       {
//         completiontime++;
//         continue;
//       }
//       completed[i]=true;
//       comp+=1;

//       if(ct<a)
//     }
// }

// int main(){
//     vector <Process> p;
//     int n;
//     cout<<"Enter the number of processes: ";
//     cin>>n;
//     for(int i=0;i<n;i++)
//     {
//         int id,at,bt;
//         cout<<"Enter the process id, arrival time and burst time for process "<<i+1<<
//         ": ";
//         cin>>id>>at>>bt;
//         p.push_back(Process(id,at,bt));
//     }
//     fcfs(p);
// }

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include<queue>
using namespace std;

class Process {
public:
    int pid;       // Process ID
    int arr_time;  // Arrival Time
    int wait_time; // Waiting Time
    int tat;       // Turnaround Time
    int bt;
    int rbt;  
    int priority;      // Burst Time

    Process(int id, int at, int burstt,int p) {
        pid = id;
        arr_time = at;
        bt = burstt;
        rbt=burstt;
        wait_time = tat = 0; // Initialize wait time and turnaround time
        priority=p;
    }
};

// Comparator for sorting processes by arrival time
bool compare(Process &a, Process &b) {
    return a.arr_time < b.arr_time;
}

// Function to display process details and averages
void display(vector<Process> &p, string order) {
    int total_wait_time = 0, total_tat = 0;
    int n = p.size();

    cout << "\nExecution Order: " << order << endl;
    cout << "\nPID\tWaiting Time\tTurnaround Time\n";

    for (auto &a : p) {
        total_wait_time += a.wait_time;
        total_tat += a.tat;
        cout << a.pid << "\t" << a.wait_time << "\t\t" << a.tat << endl;
    }

    cout << "\nAverage Waiting Time = " << (float)total_wait_time / n;
    cout << "\nAverage Turnaround Time = " << (float)total_tat / n << endl;
}

// First Come First Serve (FCFS) Scheduling
void fcfs(vector<Process> &p) {
    sort(p.begin(), p.end(), compare);
    int ct = 0; // Current time
    string order;

    for (auto &i : p) {
        if (ct < i.arr_time) {
            ct = i.arr_time; // If the process arrives later than current time
        }
        i.wait_time = ct - i.arr_time;
        ct += i.bt;
        i.tat = i.wait_time + i.bt;
        order += "P" + to_string(i.pid) + " ";
    }
    display(p, order);
}

// Find the next process for SJF
int findnext(vector<Process> &p, int ct, vector<bool> &completed) {
    int n = p.size();
    int s = -1;     // Index of the next process
    int sbt = INT_MAX; // Shortest burst time

    for (int i = 0; i < n; i++) {
        if (!completed[i] && p[i].arr_time <= ct && p[i].bt < sbt) {
            s = i;
            sbt = p[i].bt;
        }
    }
    return s;
}

// Shortest Job First (SJF) Scheduling
void sjf(vector<Process> &p) {
    int n = p.size();
    int completiontime = 0; // Current time
    int completed_count = 0;
    vector<bool> completed(n, false);
    string order;
    sort(p.begin(), p.end(), compare);

    while (completed_count < n) {
        int idx = findnext(p, completiontime, completed);

        if (idx == -1) {
            // If no process is available, move time forward
            completiontime++;
            continue;
        }

        // Process the selected job
        completed[idx] = true;
        completed_count++;

        if (completiontime < p[idx].arr_time) {
            completiontime = p[idx].arr_time; // Adjust time if idle
        }

        p[idx].wait_time = completiontime - p[idx].arr_time;
        completiontime += p[idx].bt;
        p[idx].tat = p[idx].wait_time + p[idx].bt;

        order += "P" + to_string(p[idx].pid) + " ";
    }

    display(p, order);
}

void srtf(vector<Process> &p) {
    int n = p.size();
    int current_time = 0;    // Tracks the current time
    int completed_count = 0; // Number of completed processes
    string order;            // Order of execution
    sort(p.begin(), p.end(), compare); // Sort processes by arrival time

    while (completed_count < n) {
        int shortest_idx = -1;
        int min_remaining_bt = INT_MAX;

        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].arr_time <= current_time && p[i].rbt > 0 && p[i].rbt < min_remaining_bt) {
                shortest_idx = i;
                min_remaining_bt = p[i].rbt;
            }
        }

        if (shortest_idx == -1) {
            current_time++; // If no process is ready, increment time
            continue;
        }

        // Execute the process
        order += "P" + to_string(p[shortest_idx].pid) + " ";
        p[shortest_idx].rbt--;
        current_time++;

        // Check if the process is completed
        if (p[shortest_idx].rbt == 0) {
            completed_count++;
            p[shortest_idx].tat = current_time - p[shortest_idx].arr_time; // Turnaround time
            p[shortest_idx].wait_time = p[shortest_idx].tat - p[shortest_idx].bt; // Waiting time
        }
    }

    display(p, order);
}

void prior(vector<Process> &p){
    int n=p.size();
    int ct=0;
    int  cc=0;
    string order;
    sort(p.begin(),p.end(),compare);
    vector<bool> completed(n,false);

    while(cc<n){
        int idx=-1;
        int maxp=INT_MAX;
        for(int i=0;i<n;i++)
        {
            if(!completed[i]&&p[i].arr_time<ct&&p[i].priority<maxp){
                idx=i;
                maxp=p[i].priority;
            }
        }
        if(idx==-1){
            ct++;
            continue;
        }
        order += "P" + to_string(p[idx].pid) + " ";
        p[idx].rbt--;
        ct++;
        if(p[idx].rbt==0){
            completed[idx]=true;
            cc++;
            p[idx].tat=ct-p[idx].arr_time;
            p[idx].wait_time=p[idx].tat-p[idx].bt;
        }

        }
        display(p,order);
    }

void rr(vector<Process> &p,int tq){
    int n=p.size();
    int ct=0;
    int cc=0;
    queue<int> ready;
    string order;
    int idx=0;
    while(cc<n){
      
            while((idx<n) && (p[idx].arr_time<=ct)){
                ready.push(idx);
                idx++;
            }

            if(ready.empty()){
                ct++;
                continue;
            }
            int currentprocess=ready.front();
            ready.pop();

            if(p[currentprocess].rbt>tq){
                order+="P" + to_string(p[currentprocess].pid) + " ";
                ct+=tq;
                p[currentprocess].rbt-=tq;
                 while((idx<n) && (p[idx].arr_time<=ct)){
                ready.push(idx);
                idx++;
            }
            ready.push(currentprocess);
            }else{
                order+="P" + to_string(p[currentprocess].pid) + " ";
                ct+=p[currentprocess].rbt;
                p[currentprocess].rbt=0;
                p[currentprocess].tat=ct-p[currentprocess].arr_time;
                p[currentprocess].wait_time=p[currentprocess].tat-p[currentprocess].bt;
                cc++;
            }
            
        
    }display(p,order);
}
int main() {
    vector<Process> p;
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int id, at, bt, prio;
        cout << "Enter the process ID, arrival time, burst time, and priority for process " << i + 1 << ": ";
        cin >> id >> at >> bt >> prio;

        if (at < 0 || bt <= 0 || prio < 0) {
            cout << "Invalid input. Please enter non-negative arrival time, positive burst time, and non-negative priority.\n";
            i--; // Retry the input for the same process
            continue;
        }

        p.push_back(Process(id, at, bt, prio));
    }

    cout << "\n--- FCFS Scheduling ---";
    fcfs(p);

    // Reset before next scheduling algorithm
    for (auto &proc : p) {
        proc.wait_time = 0;
        proc.tat = 0;
        proc.rbt = proc.bt;
    }

    cout << "\n--- SJF Scheduling ---";
    sjf(p);

    // Reset
    for (auto &proc : p) {
        proc.wait_time = 0;
        proc.tat = 0;
        proc.rbt = proc.bt;
    }

    cout << "\n--- SRTF Scheduling ---";
    srtf(p);

    // Reset
    for (auto &proc : p) {
        proc.wait_time = 0;
        proc.tat = 0;
        proc.rbt = proc.bt;
    }

    cout << "\n--- Priority Scheduling ---";
    prior(p);

    // Reset
    for (auto &proc : p) {
        proc.wait_time = 0;
        proc.tat = 0;
        proc.rbt = proc.bt;
    }

    cout << "\n--- Round Robin Scheduling ---";
    int tq;
    cout << "\nEnter time quantum for Round Robin: ";
    cin >> tq;
    rr(p, tq);

    return 0;
}
