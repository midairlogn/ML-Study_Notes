// 19_external_sorting.cpp - External Sorting (for data too large for memory)
// Knowledge points: k-way merge, replacement selection, polyphase merge

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <queue>
#include <climits>
using namespace std;

// ===== External Sorting Simulation =====
// When data doesn't fit in memory, we must sort in passes:
// 1. Create initial sorted runs (from memory-sized chunks)
// 2. Merge runs together (k-way merge)

// Simulated "disk" block
struct Block {
    int data[4];  // block size = 4 elements
    int count;
    Block() : count(0) {}
};

// ===== Phase 1: Create Initial Sorted Runs =====
// Read memory-sized chunks, sort them in memory, write to disk
vector<vector<int>> createInitialRuns(const vector<int>& data, int memorySize) {
    vector<vector<int>> runs;
    int n = data.size();

    for (int i = 0; i < n; i += memorySize) {
        // Read chunk into memory
        vector<int> chunk;
        for (int j = i; j < min(i + memorySize, n); j++)
            chunk.push_back(data[j]);

        // Sort in memory
        sort(chunk.begin(), chunk.end());

        // Write sorted run to disk
        runs.push_back(chunk);
        cout << "  Run " << runs.size()-1 << ": ";
        for (int x : chunk) cout << x << " ";
        cout << endl;
    }
    return runs;
}

// ===== Phase 2: K-way Merge =====
// Merge k sorted runs into one sorted output
struct RunElement {
    int value;
    int runIndex;
    int elemIndex;
    bool operator>(const RunElement& o) const { return value > o.value; }
};

vector<int> kWayMerge(vector<vector<int>>& runs) {
    int k = runs.size();
    vector<int> result;

    // Min-heap of (value, runIndex, elemIndex)
    priority_queue<RunElement, vector<RunElement>, greater<RunElement>> pq;

    // Initialize heap with first element from each run
    for (int i = 0; i < k; i++) {
        if (!runs[i].empty()) {
            pq.push({runs[i][0], i, 0});
        }
    }

    int mergePasses = 0;
    while (!pq.empty()) {
        RunElement min = pq.top();
        pq.pop();
        result.push_back(min.value);

        // Advance in the run
        int nextIdx = min.elemIndex + 1;
        if (nextIdx < (int)runs[min.runIndex].size()) {
            pq.push({runs[min.runIndex][nextIdx], min.runIndex, nextIdx});
        }
    }

    return result;
}

// ===== Replacement Selection (create longer runs) =====
// Instead of sorting memory-sized chunks, use a min-heap
// Produces runs that are 2x memory size on average
vector<vector<int>> replacementSelection(const vector<int>& data, int memorySize) {
    vector<vector<int>> runs;
    priority_queue<int, vector<int>, greater<int>> active;
    priority_queue<int, vector<int>, greater<int>> frozen;

    // Fill initial memory
    int idx = 0;
    for (int i = 0; i < memorySize && idx < (int)data.size(); i++, idx++)
        active.push(data[idx]);

    int lastOutput = INT_MIN;
    vector<int> currentRun;

    while (!active.empty() || !frozen.empty()) {
        if (active.empty()) {
            runs.push_back(currentRun);
            currentRun.clear();
            lastOutput = INT_MIN;
            swap(active, frozen);
        }

        // Extract min
        int val = active.top();
        active.pop();

        currentRun.push_back(val);
        lastOutput = val;

        // Refill memory if data remains
        if (idx < (int)data.size()) {
            int nextValue = data[idx++];
            if (nextValue >= lastOutput) active.push(nextValue);
            else frozen.push(nextValue);
        }
    }

    if (!currentRun.empty()) runs.push_back(currentRun);

    cout << "  Runs created by replacement selection: " << runs.size() << endl;
    for (size_t i = 0; i < runs.size(); i++) {
        cout << "  Run " << i << ": ";
        for (int x : runs[i]) cout << x << " ";
        cout << endl;
    }
    return runs;
}

// ===== Sorting Analysis =====
void printSortingAnalysis(int n, int M, int blockSize) {
    cout << "\n========================================" << endl;
    cout << "  External Sorting Analysis" << endl;
    cout << "========================================" << endl;

    int numBlocks = (n + blockSize - 1) / blockSize;
    int memoryBlocks = M / blockSize;
    int initialRuns = (n + M - 1) / M;
    int mergePasses = 0;
    int k = memoryBlocks;  // k-way merge

    int remaining = initialRuns;
    while (remaining > 1) {
        remaining = (remaining + k - 1) / k;
        mergePasses++;
    }

    cout << "Data size: " << n << " elements" << endl;
    cout << "Memory size: " << M << " elements (" << memoryBlocks << " blocks)" << endl;
    cout << "Block size: " << blockSize << " elements" << endl;
    cout << "Number of blocks: " << numBlocks << endl;
    cout << "Initial sorted runs: " << initialRuns << endl;
    cout << "k-way merge (k=" << k << "): " << mergePasses << " passes needed" << endl;
    cout << "Total I/O: O(n/blockSize * log_k(n/M))" << endl;
    cout << "With replacement selection: ~2x longer runs, ~half the passes" << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "  External Sorting Demo" << endl;
    cout << "========================================" << endl;

    // Simulated data too large for memory
    vector<int> data = {15, 3, 8, 12, 1, 9, 4, 11, 7, 2, 6, 14, 5, 10, 13};
    int memorySize = 5;  // can only hold 5 elements in memory

    cout << "\nOriginal data: ";
    for (int x : data) cout << x << " ";
    cout << endl;

    // Phase 1: Create initial sorted runs
    cout << "\n--- Phase 1: Create Initial Sorted Runs ---" << endl;
    vector<vector<int>> runs = createInitialRuns(data, memorySize);
    cout << "Created " << runs.size() << " runs" << endl;

    // Phase 2: K-way merge
    cout << "\n--- Phase 2: K-way Merge ---" << endl;
    vector<int> sorted = kWayMerge(runs);
    cout << "Sorted result: ";
    for (int x : sorted) cout << x << " ";
    cout << endl;

    // Replacement selection
    cout << "\n--- Replacement Selection ---" << endl;
    cout << "Using replacement selection instead of simple sorting:" << endl;
    replacementSelection(data, memorySize);

    // Analysis
    printSortingAnalysis(1000000, 10000, 1024);

    cout << "\n========================================" << endl;
    cout << "  External Sorting Concepts" << endl;
    cout << "========================================" << endl;
    cout << "Why external sorting?" << endl;
    cout << "  - Data too large to fit in main memory" << endl;
    cout << "  - Must use disk I/O (10ms seek time vs 1ns memory)" << endl;
    cout << "\nMultiway Merge:" << endl;
    cout << "  - Use memory as k input buffers + 1 output buffer" << endl;
    cout << "  - Merge k runs simultaneously" << endl;
    cout << "  - Passes = ceil(log_k(n/M))" << endl;
    cout << "\nReplacement Selection:" << endl;
    cout << "  - Use min-heap to produce runs" << endl;
    cout << "  - Run ends when all remaining elements < last output" << endl;
    cout << "  - Average run size = 2M (twice memory size)" << endl;
    cout << "\nPolyphase Merge:" << endl;
    cout << "  - Instead of k-way merge, use (k-1)-way merge" << endl;
    cout << "  - Distribute runs unevenly for optimal merging" << endl;

    return 0;
}
