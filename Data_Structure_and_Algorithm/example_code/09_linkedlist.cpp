// 09_linkedlist.cpp - Linked List: Singly, Circular, Doubly
// Knowledge points: Dynamic allocation, insert, remove, dummy header

#include <iostream>
using namespace std;

// ===== Singly Linked List =====
struct SinglyNode {
    int data;
    SinglyNode* next;
    SinglyNode(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
private:
    SinglyNode* head;

public:
    SinglyLinkedList() : head(nullptr) {}
    ~SinglyLinkedList() {
        while (head) {
            SinglyNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Insert at head - O(1)
    void insertFront(int val) {
        SinglyNode* newNode = new SinglyNode(val);
        newNode->next = head;
        head = newNode;
    }

    // Insert sorted - O(n)
    void insertSorted(int val) {
        SinglyNode* newNode = new SinglyNode(val);
        if (head == nullptr || val < head->data) {
            newNode->next = head;
            head = newNode;
            return;
        }
        SinglyNode* curr = head;
        while (curr->next && curr->next->data < val)
            curr = curr->next;
        newNode->next = curr->next;
        curr->next = newNode;
    }

    // Remove first occurrence - O(n)
    void remove(int val) {
        if (head == nullptr) return;
        if (head->data == val) {
            SinglyNode* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        SinglyNode* curr = head;
        while (curr->next && curr->next->data != val)
            curr = curr->next;
        if (curr->next) {
            SinglyNode* temp = curr->next;
            curr->next = temp->next;
            delete temp;
        }
    }

    // Search - O(n)
    bool search(int val) const {
        SinglyNode* curr = head;
        while (curr) {
            if (curr->data == val) return true;
            curr = curr->next;
        }
        return false;
    }

    // Count nodes - O(n)
    int count() const {
        int c = 0;
        SinglyNode* curr = head;
        while (curr) { c++; curr = curr->next; }
        return c;
    }

    void print() const {
        SinglyNode* curr = head;
        while (curr) {
            cout << curr->data;
            if (curr->next) cout << " -> ";
            curr = curr->next;
        }
        cout << " -> NULL" << endl;
    }
};

// ===== Doubly Linked List =====
struct DoublyNode {
    int data;
    DoublyNode* prev;
    DoublyNode* next;
    DoublyNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    DoublyNode* head;
    DoublyNode* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    ~DoublyLinkedList() {
        while (head) {
            DoublyNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertFront(int val) {
        DoublyNode* newNode = new DoublyNode(val);
        newNode->next = head;
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = newNode;
    }

    void insertBack(int val) {
        DoublyNode* newNode = new DoublyNode(val);
        newNode->prev = tail;
        if (tail) tail->next = newNode;
        tail = newNode;
        if (!head) head = newNode;
    }

    // Remove node given pointer - O(1)!
    void removeNode(DoublyNode* node) {
        if (!node) return;
        if (node->prev) node->prev->next = node->next;
        else head = node->next;

        if (node->next) node->next->prev = node->prev;
        else tail = node->prev;

        delete node;
    }

    void remove(int val) {
        DoublyNode* curr = head;
        while (curr) {
            if (curr->data == val) {
                removeNode(curr);
                return;
            }
            curr = curr->next;
        }
    }

    // Backward traversal - O(n)
    void printBackward() const {
        DoublyNode* curr = tail;
        while (curr) {
            cout << curr->data;
            if (curr->prev) cout << " -> ";
            curr = curr->prev;
        }
        cout << " -> NULL" << endl;
    }

    void print() const {
        DoublyNode* curr = head;
        while (curr) {
            cout << curr->data;
            if (curr->next) cout << " <-> ";
            curr = curr->next;
        }
        cout << endl;
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "  Singly Linked List Demo" << endl;
    cout << "========================================" << endl;

    SinglyLinkedList list;
    list.insertSorted(5);
    list.insertSorted(3);
    list.insertSorted(8);
    list.insertSorted(1);
    list.insertSorted(7);
    cout << "Sorted insert 5,3,8,1,7: ";
    list.print();

    list.insertFront(10);
    cout << "Insert front 10:         ";
    list.print();

    list.remove(5);
    cout << "Remove 5:                ";
    list.print();

    list.remove(10);
    cout << "Remove 10:               ";
    list.print();

    cout << "Search 8: " << (list.search(8) ? "Found" : "Not found") << endl;
    cout << "Search 5: " << (list.search(5) ? "Found" : "Not found") << endl;
    cout << "Count: " << list.count() << endl;

    cout << "\n========================================" << endl;
    cout << "  Doubly Linked List Demo" << endl;
    cout << "========================================" << endl;

    DoublyLinkedList dlist;
    dlist.insertBack(1);
    dlist.insertBack(2);
    dlist.insertBack(3);
    dlist.insertFront(0);
    dlist.insertBack(4);
    cout << "Forward:  ";
    dlist.print();
    cout << "Backward: ";
    dlist.printBackward();

    dlist.remove(2);
    cout << "\nAfter remove 2:" << endl;
    cout << "Forward:  ";
    dlist.print();
    cout << "Backward: ";
    dlist.printBackward();

    cout << "\n========================================" << endl;
    cout << "  Linked List Properties" << endl;
    cout << "========================================" << endl;
    cout << "Singly: data + next pointer" << endl;
    cout << "Doubly: data + prev + next pointers" << endl;
    cout << "Circular: last->next = head" << endl;
    cout << "Insert/Remove at head: O(1)" << endl;
    cout << "Insert sorted/Search: O(n)" << endl;
    cout << "No random access (unlike array)" << endl;
    cout << "Advantage: dynamic size, no wasted space" << endl;
    cout << "Disadvantage: extra pointer memory, sequential access" << endl;

    return 0;
}
