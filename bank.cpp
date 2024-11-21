// #include<iostream>
// using namespace std;

// const int p=5,r=3;

// bool isSafe(int avail[], int allocated[p][r],int max[p][r],int need[p][r]){
//     int work[r];
//     int finish[p]={false};
//     for(int i=0;i<r;i++){
//         work[i]=avail[i];
//     }
//     int safe[p];
//     int count=0;
//     while(count<p){
//         bool found=false;
//         for(int i=0;i<p;i++){
//             if(!finish[i]){
//                 bool canfin=true;
//                 for(int j=0;j<r;j++){
//                     if(need[i][j]>avail[j]){
//                         canfin=false;
//                         break;
//                     }
//                 }
//                 if(canfin==true){
//                     for(int j=0;j<r;j++){
//                         work[j]+=allocated[i][j];
//                     }
//                     finish[i]=true;
//                     safe[count++]=i;
//                     found=true;
//                 }

//             }
//             if(!found){
//                 cout<<"sys nt inm safe state";
//                 return false;
//             }
//         }
//         cout<<"s6ys in safe state \n sequence is";
//         for(int i=0;i<count;i++){
//             cout<<safe[i]<<" ";
//         }return true;
//     }
// }

#include <iostream>
using namespace std;

const int p = 5; // Number of processes
const int r = 3; // Number of resources

bool isSafe(int avail[], int allocated[p][r], int max[p][r], int need[p][r]) {
    int work[r];
    bool finish[p] = {false};
    int safe[p];
    int count = 0;

    // Initialize work with available resources
    for (int i = 0; i < r; i++) {
        work[i] = avail[i];
    }

    while (count < p) {
        bool found = false;

        for (int i = 0; i < p; i++) {
            if (!finish[i]) {
                // Check if the process can be completed
                bool canFinish = true;
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }

                if (canFinish) {
                    // Update work with allocated resources of the process
                    for (int j = 0; j < r; j++) {
                        work[j] += allocated[i][j];
                    }
                    safe[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        // If no process was found in this iteration, system is not in a safe state
        if (!found) {
            cout << "System is NOT in a safe state.\n";
            return false;
        }
    }

    // If all processes are completed, the system is in a safe state
    cout << "System is in a safe state.\nSafe sequence is: ";
    for (int i = 0; i < count; i++) {
        cout << "P" << safe[i] << (i == count - 1 ? "" : " -> ");
    }
    cout << endl;
    return true;
}

int main() {
    // Example input for testing
    int avail[r] = {3, 3, 2}; // Available resources

    int max[p][r] = { // Maximum demand
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int allocated[p][r] = { // Allocated resources
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int need[p][r]; // Need matrix

    // Calculate the need matrix
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }

    // Check if the system is in a safe state
    isSafe(avail, allocated, max, need);

    return 0;
}
