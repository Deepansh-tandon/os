#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct MemoryBlock {
    int size;
    bool isAllocated;
};
void displayMemory(const vector<MemoryBlock> &memory) {
    cout << "Current Memory State:\n";
    for (size_t i = 0; i < memory.size(); ++i) {
        cout << "Block " << i + 1 << ": Size = " << memory[i].size 
             << ", " << (memory[i].isAllocated ? "Allocated" : "Free") << "\n";
    }
    cout << endl;
}

void firstFit(vector<MemoryBlock> &memory, int requestSize) {
    for (auto &block : memory) {
        if (!block.isAllocated && block.size >= requestSize) {
            block.isAllocated = true;
            block.size -= requestSize;
            cout << "Memory allocated using First Fit.\n";
            return;
        }
    }
    cout << "No suitable memory block found for First Fit.\n";
}

void bestFit(vector<MemoryBlock> &memory, int requestSize) {
    int bestIdx = -1;
    int minSize = INT_MAX;
    for (size_t i = 0; i < memory.size(); ++i) {
        if (!memory[i].isAllocated && memory[i].size >= requestSize && memory[i].size < minSize) {
            bestIdx = i;
            minSize = memory[i].size;
        }
    }
    if (bestIdx != -1) {
        memory[bestIdx].isAllocated = true;
        memory[bestIdx].size -= requestSize;
        cout << "Memory allocated using Best Fit.\n";
    } else {
        cout << "No suitable memory block found for Best Fit.\n";
    }
}

void worstFit(vector<MemoryBlock> &memory, int requestSize) {
    int worstIdx = -1;
    int maxSize = -1;
    for (size_t i = 0; i < memory.size(); ++i) {
        if (!memory[i].isAllocated && memory[i].size >= requestSize && memory[i].size > maxSize) {
            worstIdx = i;
            maxSize = memory[i].size;
        }
    }
    if (worstIdx != -1) {
        memory[worstIdx].isAllocated = true;
        memory[worstIdx].size -= requestSize;
        cout << "Memory allocated using Worst Fit.\n";
    } else {
        cout << "No suitable memory block found for Worst Fit.\n";
    }
}

int main() {
    int n;
    cout << "Enter the number of memory blocks: ";
    cin >> n;
    vector<MemoryBlock> memory(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter size of block " << i + 1 << ": ";
        cin >> memory[i].size;
        memory[i].isAllocated = false;
    }

    while (true) {
        cout << "\nMenu:\n"
             << "1. First Fit\n"
             << "2. Best Fit\n"
             << "3. Worst Fit\n"
             << "4. Exit\n"
             << "Choose an option: ";
        int choice;
        cin >> choice;

        if (choice == 4) {
            cout << "Exiting program.\n";
            break;
        }

        cout << "Enter the size of the memory block to allocate: ";
        int requestSize;
        cin >> requestSize;

        switch (choice) {
            case 1:
                firstFit(memory, requestSize);
                break;
            case 2:
                bestFit(memory, requestSize);
                break;
            case 3:
                worstFit(memory, requestSize);
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }

        displayMemory(memory);
    }

    return 0;
}
