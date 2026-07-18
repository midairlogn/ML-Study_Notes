// 07_sorting.cpp - Sorting Algorithms Comparison
// Knowledge points: Insertion, Bubble, Heap, Merge, Quick sort

#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

// ===== Insertion Sort - O(n^2) =====
// Adaptive: O(n) when already sorted
void insertionSort(int a[], int n) {
    for (int k = 1; k < n; k++) {
        int key = a[k];
        int j = k - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

// ===== Bubble Sort (Flagged) - O(n^2) =====
void bubbleSort(int a[], int n) {
    for (int i = n - 1; i > 0; i--) {
        bool sorted = true;
        int maxVal = a[0];
        for (int j = 1; j <= i; j++) {
            if (a[j] < maxVal) {
                a[j - 1] = a[j];
                sorted = false;
            } else {
                a[j - 1] = maxVal;
                maxVal = a[j];
            }
        }
        a[i] = maxVal;
        if (sorted) break;
    }
}

// ===== Selection Sort - O(n^2) =====
void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[minIdx])
                minIdx = j;
        }
        if (minIdx != i)
            swap(a[i], a[minIdx]);
    }
}

// ===== Heap Sort - O(n log n) =====
void heapify(int a[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;  // 0-indexed
    int right = 2 * i + 2;
    if (left < n && a[left] > a[largest]) largest = left;
    if (right < n && a[right] > a[largest]) largest = right;
    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n) {
    // Build max heap (0-indexed)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
    // Extract elements
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

// ===== Merge Sort - O(n log n), O(n) space =====
void merge(int a[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int* L = new int[n1], *R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = a[left + i];
    for (int j = 0; j < n2; j++) R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
        a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
    delete[] L;
    delete[] R;
}

void mergeSort(int a[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

// ===== Quick Sort - O(n log n) avg, O(n^2) worst =====
int partition(int a[], int low, int high) {
    int pivot = a[high];  // last element as pivot
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j] < pivot) {
            swap(a[++i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(int a[], int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

// ===== Utility Functions =====
void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
}

void copyArray(int src[], int dst[], int n) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

int main() {
    cout << "========================================" << endl;
    cout << "  Sorting Algorithms Comparison" << endl;
    cout << "========================================" << endl;

    int original[] = {34, 15, 65, 59, 79, 42, 40, 80, 50, 61};
    int n = 10;
    int arr[10];

    cout << "\nOriginal array: ";
    printArray(original, n);

    // Insertion Sort
    copyArray(original, arr, n);
    insertionSort(arr, n);
    cout << "Insertion Sort: ";
    printArray(arr, n);

    // Bubble Sort
    copyArray(original, arr, n);
    bubbleSort(arr, n);
    cout << "Bubble Sort:    ";
    printArray(arr, n);

    // Selection Sort
    copyArray(original, arr, n);
    selectionSort(arr, n);
    cout << "Selection Sort: ";
    printArray(arr, n);

    // Heap Sort
    copyArray(original, arr, n);
    heapSort(arr, n);
    cout << "Heap Sort:      ";
    printArray(arr, n);

    // Merge Sort
    copyArray(original, arr, n);
    mergeSort(arr, 0, n - 1);
    cout << "Merge Sort:     ";
    printArray(arr, n);

    // Quick Sort
    copyArray(original, arr, n);
    quickSort(arr, 0, n - 1);
    cout << "Quick Sort:     ";
    printArray(arr, n);

    // ===== Timing Comparison =====
    cout << "\n========================================" << endl;
    cout << "  Timing Comparison (n = 10000)" << endl;
    cout << "========================================" << endl;

    int N = 10000;
    int* testArr = new int[N];
    int* workArr = new int[N];

    srand(42);
    for (int i = 0; i < N; i++) testArr[i] = rand() % 100000;

    clock_t start, end;

    copyArray(testArr, workArr, N);
    start = clock();
    insertionSort(workArr, N);
    end = clock();
    cout << "Insertion Sort: " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    copyArray(testArr, workArr, N);
    start = clock();
    bubbleSort(workArr, N);
    end = clock();
    cout << "Bubble Sort:    " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    copyArray(testArr, workArr, N);
    start = clock();
    heapSort(workArr, N);
    end = clock();
    cout << "Heap Sort:      " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    copyArray(testArr, workArr, N);
    start = clock();
    mergeSort(workArr, 0, N - 1);
    end = clock();
    cout << "Merge Sort:     " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    copyArray(testArr, workArr, N);
    start = clock();
    quickSort(workArr, 0, N - 1);
    end = clock();
    cout << "Quick Sort:     " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    cout << "\n========================================" << endl;
    cout << "  Complexity Summary" << endl;
    cout << "========================================" << endl;
    cout << "Algorithm      Best      Average   Worst     Space    Stable" << endl;
    cout << "Insertion      O(n)      O(n^2)    O(n^2)    O(1)     Yes" << endl;
    cout << "Bubble         O(n)      O(n^2)    O(n^2)    O(1)     Yes" << endl;
    cout << "Heap Sort      O(nlogn)  O(nlogn)  O(nlogn)  O(1)     No" << endl;
    cout << "Merge Sort     O(nlogn)  O(nlogn)  O(nlogn)  O(n)     Yes" << endl;
    cout << "Quick Sort     O(nlogn)  O(nlogn)  O(n^2)    O(logn)  No" << endl;

    delete[] testArr;
    delete[] workArr;

    return 0;
}
