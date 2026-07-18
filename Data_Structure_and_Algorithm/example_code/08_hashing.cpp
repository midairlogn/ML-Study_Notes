// 08_hashing.cpp - Hash Table: Linear Probing, Quadratic Probing, Chaining
// Knowledge points: Hash functions, collision resolution, rehashing

#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

// ===== Open Addressing: Linear Probing =====
class LinearProbingHashTable {
private:
    int* table;
    int capacity;
    int count;
    static const int EMPTY = -1;
    static const int DELETED = -2;

    int hash(int key) const { return key % capacity; }

public:
    LinearProbingHashTable(int cap = 11) : capacity(cap), count(0) {
        table = new int[capacity];
        for (int i = 0; i < capacity; i++) table[i] = EMPTY;
    }
    ~LinearProbingHashTable() { delete[] table; }

    bool insert(int key) {
        if (count >= capacity / 2) {
            cout << "  Load factor too high, rehashing..." << endl;
            return false;
        }
        int idx = hash(key);
        int startIdx = idx;

        // Linear probing: try idx+1, idx+2, ...
        while (table[idx] != EMPTY && table[idx] != DELETED) {
            if (table[idx] == key) return false;  // duplicate
            idx = (idx + 1) % capacity;
            if (idx == startIdx) return false;  // table full
        }

        table[idx] = key;
        count++;
        cout << "  Inserted " << key << " at index " << idx
             << " (hash=" << hash(key) << ", probes=" << ((idx - hash(key) + capacity) % capacity + 1) << ")" << endl;
        return true;
    }

    bool search(int key) const {
        int idx = hash(key);
        int startIdx = idx;
        int probes = 1;

        while (table[idx] != EMPTY) {
            if (table[idx] == key) {
                cout << "  Found " << key << " at index " << idx << " (probes: " << probes << ")" << endl;
                return true;
            }
            idx = (idx + 1) % capacity;
            probes++;
            if (idx == startIdx) break;
        }
        cout << "  " << key << " not found (probes: " << probes << ")" << endl;
        return false;
    }

    void remove(int key) {
        int idx = hash(key);
        int startIdx = idx;

        while (table[idx] != EMPTY) {
            if (table[idx] == key) {
                table[idx] = DELETED;
                count--;
                cout << "  Removed " << key << " from index " << idx << endl;
                return;
            }
            idx = (idx + 1) % capacity;
            if (idx == startIdx) break;
        }
        cout << "  " << key << " not found for deletion" << endl;
    }

    void print() const {
        for (int i = 0; i < capacity; i++) {
            cout << "  [" << i << "] ";
            if (table[i] == EMPTY) cout << "---";
            else if (table[i] == DELETED) cout << "DEL";
            else cout << table[i];
            cout << endl;
        }
    }
};

// ===== Separate Chaining =====
class ChainingHashTable {
private:
    vector<list<int>> table;
    int capacity;
    int count;

    int hash(int key) const { return key % capacity; }

public:
    ChainingHashTable(int cap = 11) : capacity(cap), count(0) {
        table.resize(capacity);
    }

    void insert(int key) {
        int idx = hash(key);
        // Check for duplicate
        for (int x : table[idx]) {
            if (x == key) return;
        }
        table[idx].push_back(key);
        count++;
        cout << "  Inserted " << key << " at chain " << idx << endl;
    }

    bool search(int key) const {
        int idx = hash(key);
        int comparisons = 0;
        for (int x : table[idx]) {
            comparisons++;
            if (x == key) {
                cout << "  Found " << key << " in chain " << idx
                     << " (comparisons: " << comparisons << ")" << endl;
                return true;
            }
        }
        cout << "  " << key << " not found (comparisons: " << comparisons << ")" << endl;
        return false;
    }

    void remove(int key) {
        int idx = hash(key);
        for (auto it = table[idx].begin(); it != table[idx].end(); ++it) {
            if (*it == key) {
                table[idx].erase(it);
                count--;
                cout << "  Removed " << key << " from chain " << idx << endl;
                return;
            }
        }
        cout << "  " << key << " not found" << endl;
    }

    void print() const {
        for (int i = 0; i < capacity; i++) {
            cout << "  [" << i << "] ";
            if (table[i].empty()) {
                cout << "---";
            } else {
                for (int x : table[i]) cout << x << " -> ";
                cout << "NULL";
            }
            cout << endl;
        }
    }
};

// ===== Quadratic Probing =====
class QuadraticProbingHashTable {
private:
    int* table;
    int capacity;
    int count;
    static const int EMPTY = -1;

    int hash(int key) const { return key % capacity; }

public:
    QuadraticProbingHashTable(int cap = 11) : capacity(cap), count(0) {
        table = new int[capacity];
        for (int i = 0; i < capacity; i++) table[i] = EMPTY;
    }
    ~QuadraticProbingHashTable() { delete[] table; }

    bool insert(int key) {
        int idx = hash(key);
        int probe = 0;

        // Quadratic probing: try h+1^2, h+2^2, h+3^2, ...
        while (table[idx] != EMPTY) {
            if (table[idx] == key) return false;
            probe++;
            idx = (hash(key) + probe * probe) % capacity;
            if (probe >= capacity) return false;
        }

        table[idx] = key;
        count++;
        cout << "  Inserted " << key << " at index " << idx
             << " (hash=" << hash(key) << ", probe=" << probe << ")" << endl;
        return true;
    }

    void print() const {
        for (int i = 0; i < capacity; i++) {
            cout << "  [" << i << "] ";
            if (table[i] == EMPTY) cout << "---";
            else cout << table[i];
            cout << endl;
        }
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "  Hashing Demo" << endl;
    cout << "========================================" << endl;

    // Linear Probing
    cout << "\n--- Linear Probing (h(x) = x % 11) ---" << endl;
    LinearProbingHashTable lpTable(11);
    int lpData[] = {4371, 1323, 6173, 4199, 4344, 9679, 1989};
    for (int x : lpData) lpTable.insert(x);
    cout << "\nTable state:" << endl;
    lpTable.print();

    cout << "\nSearch operations:" << endl;
    lpTable.search(4199);
    lpTable.search(1989);
    lpTable.search(5555);

    // Quadratic Probing
    cout << "\n--- Quadratic Probing (h(x) = x % 11) ---" << endl;
    QuadraticProbingHashTable qpTable(11);
    for (int x : lpData) qpTable.insert(x);
    cout << "\nTable state:" << endl;
    qpTable.print();

    // Separate Chaining
    cout << "\n--- Separate Chaining (h(x) = x % 11) ---" << endl;
    ChainingHashTable chainTable(11);
    for (int x : lpData) chainTable.insert(x);
    cout << "\nTable state:" << endl;
    chainTable.print();

    cout << "\nSearch operations:" << endl;
    chainTable.search(4199);
    chainTable.search(1989);

    cout << "\n========================================" << endl;
    cout << "  Hash Table Properties" << endl;
    cout << "========================================" << endl;
    cout << "Hash function: h(key) = key % table_size (use prime size)" << endl;
    cout << "Load factor = elements / table_size" << endl;
    cout << "Rehash when load factor > threshold (e.g., 0.5)" << endl;
    cout << "Linear Probing: h+1, h+2, ... (primary clustering)" << endl;
    cout << "Quadratic Probing: h+1^2, h+2^2, ... (no primary clustering)" << endl;
    cout << "Double Hashing: h+h2(x), h+2*h2(x), ... (best distribution)" << endl;
    cout << "Separate Chaining: each slot is a linked list" << endl;
    cout << "Average case: O(1) with good hash function and low load factor" << endl;

    return 0;
}
