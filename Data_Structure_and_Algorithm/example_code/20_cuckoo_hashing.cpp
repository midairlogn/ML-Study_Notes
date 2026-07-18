// 20_cuckoo_hashing.cpp - Advanced Hashing: Cuckoo, Hopscotch, Extendible
// Knowledge points: worst-case O(1) lookup, dynamic resizing

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// ===== Cuckoo Hashing =====
// Two hash tables, two hash functions
// On collision: evict existing element to its alternate table
// Worst-case O(1) lookup, insert, delete
// Amortized O(1) insert (occasional rehash)
class CuckooHashTable {
private:
    vector<int> table1, table2;
    int size;
    int count;
    int h1(int key) const { return key % size; }
    int h2(int key) const { return (key / size) % size; }

    void rehash() {
        vector<int> old;
        for (int x : table1) if (x != -1) old.push_back(x);
        for (int x : table2) if (x != -1) old.push_back(x);
        size *= 2;
        table1.assign(size, -1);
        table2.assign(size, -1);
        count = 0;
        for (int x : old) insert(x);
    }

public:
    CuckooHashTable(int s = 7) : size(s), count(0) {
        table1.assign(size, -1);
        table2.assign(size, -1);
    }

    bool insert(int key) {
        if (search(key)) return false;
        int pos = h1(key);
        // Try table1
        for (int i = 0; i < 2 * size; i++) {
            if (table1[pos] == -1) {
                table1[pos] = key;
                count++;
                return true;
            }
            // Evict and try table2
            swap(table1[pos], key);
            pos = h2(key);
            if (table2[pos] == -1) {
                table2[pos] = key;
                count++;
                return true;
            }
            // Evict and try table1
            swap(table2[pos], key);
            pos = h1(key);
        }
        // Too many evictions -> rehash
        rehash();
        return insert(key);
    }

    bool search(int key) const {
        return table1[h1(key)] == key || table2[h2(key)] == key;
    }

    void remove(int key) {
        if (table1[h1(key)] == key) { table1[h1(key)] = -1; count--; }
        else if (table2[h2(key)] == key) { table2[h2(key)] = -1; count--; }
    }

    void print() const {
        cout << "Table 1: ";
        for (int i = 0; i < size; i++)
            cout << (table1[i] == -1 ? "_" : to_string(table1[i])) << " ";
        cout << endl;
        cout << "Table 2: ";
        for (int i = 0; i < size; i++)
            cout << (table2[i] == -1 ? "_" : to_string(table2[i])) << " ";
        cout << endl;
    }
};

// ===== Extendible Hashing =====
// For disk-based databases: minimize disk accesses
// Directory of pointers, global depth, local depth per bucket
class ExtendibleHashing {
private:
    struct Bucket {
        int localDepth;
        int capacity;
        vector<int> data;
        Bucket(int d, int cap) : localDepth(d), capacity(cap) {}
        bool isFull() const { return (int)data.size() >= capacity; }
    };

    vector<Bucket*> directory;
    int globalDepth;
    int bucketCapacity;

    int hash(int key) const { return key % directory.size(); }

    void splitBucket(int idx) {
        Bucket* old = directory[idx];

        if (old->localDepth >= globalDepth) {
            // Double directory
            int oldSize = directory.size();
            directory.resize(oldSize * 2);
            for (int i = 0; i < oldSize; i++)
                directory[oldSize + i] = directory[i];
            globalDepth++;
        }

        old->localDepth++;
        int newLD = old->localDepth;
        Bucket* b0 = new Bucket(newLD, bucketCapacity);
        Bucket* b1 = new Bucket(newLD, bucketCapacity);

        // Redistribute directory entries and elements
        for (int i = 0; i < (int)directory.size(); i++) {
            if (directory[i] == old) {
                // Use the new localDepth bit to decide
                if (i & (1 << (newLD - 1)))
                    directory[i] = b1;
                else
                    directory[i] = b0;
            }
        }

        // Redistribute elements from old bucket
        for (int x : old->data) {
            int h = hash(x);
            if (h & (1 << (newLD - 1)))
                b1->data.push_back(x);
            else
                b0->data.push_back(x);
        }
        delete old;
    }

public:
    ExtendibleHashing(int depth = 1, int cap = 4)
        : globalDepth(depth), bucketCapacity(cap) {
        directory.resize(1 << depth);
        for (auto& d : directory) d = new Bucket(depth, cap);
    }

    ~ExtendibleHashing() {
        vector<Bucket*> deleted;
        for (Bucket* bucket : directory) {
            if (find(deleted.begin(), deleted.end(), bucket) == deleted.end()) {
                deleted.push_back(bucket);
                delete bucket;
            }
        }
    }

    void insert(int key) {
        int idx = hash(key);
        Bucket* b = directory[idx];
        if (!b->isFull()) {
            b->data.push_back(key);
            return;
        }
        splitBucket(idx);
        insert(key);
    }

    bool search(int key) const {
        int idx = hash(key);
        for (int x : directory[idx]->data)
            if (x == key) return true;
        return false;
    }

    void print() const {
        cout << "Global depth: " << globalDepth
             << " (directory size: " << directory.size() << ")" << endl;
        vector<Bucket*> printed;
        for (int i = 0; i < (int)directory.size(); i++) {
            if (find(printed.begin(), printed.end(), directory[i]) == printed.end()) {
                printed.push_back(directory[i]);
                cout << "  Bucket (localDepth=" << directory[i]->localDepth << "): ";
                for (int x : directory[i]->data) cout << x << " ";
                cout << endl;
            }
        }
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "  Cuckoo Hashing Demo" << endl;
    cout << "========================================" << endl;

    CuckooHashTable cuckoo;
    int data[] = {10, 22, 31, 4, 15, 28, 17, 88, 55};
    for (int x : data) {
        cuckoo.insert(x);
        cout << "Insert " << x << endl;
    }
    cuckoo.print();

    cout << "\nSearch:" << endl;
    cout << "  22: " << (cuckoo.search(22) ? "Found" : "Not found") << endl;
    cout << "  99: " << (cuckoo.search(99) ? "Found" : "Not found") << endl;

    cout << "\n--- Cuckoo Hashing Properties ---" << endl;
    cout << "  Two tables, two hash functions" << endl;
    cout << "  On collision: evict to alternate table" << endl;
    cout << "  Worst-case O(1) lookup, insert, delete" << endl;
    cout << "  Occasionally needs full rehash" << endl;
    cout << "  Poor cache performance (two separate tables)" << endl;

    cout << "\n========================================" << endl;
    cout << "  Extendible Hashing Demo" << endl;
    cout << "========================================" << endl;

    ExtendibleHashing ext(1, 3);
    for (int x : {10, 22, 31, 4, 15, 28, 17, 88, 55, 12, 6}) {
        ext.insert(x);
        cout << "Insert " << x << endl;
    }
    ext.print();

    cout << "\nSearch 22: " << (ext.search(22) ? "Found" : "Not found") << endl;
    cout << "Search 99: " << (ext.search(99) ? "Found" : "Not found") << endl;

    cout << "\n--- Extendible Hashing Properties ---" << endl;
    cout << "  Directory doubles/halves as needed" << endl;
    cout << "  Buckets split when full" << endl;
    cout << "  Only affected buckets need rewriting on split" << endl;
    cout << "  Good for: database index, disk-based storage" << endl;

    return 0;
}
