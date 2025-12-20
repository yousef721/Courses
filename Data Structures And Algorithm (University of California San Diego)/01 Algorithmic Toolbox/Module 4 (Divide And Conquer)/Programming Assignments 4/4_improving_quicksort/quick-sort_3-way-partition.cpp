#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

// ================================================================
//                 3-WAY RANDOMIZED QUICK SORT
// ================================================================

// Function to perform 3-way partitioning
// Efficiently handles arrays with duplicates
void partition3(vector<int> &a, int l, int r, int &m1, int &m2) {
    int pivot = a[l];      // Choose first element as pivot
    int lt = l;            // a[l..lt-1] < pivot
    int gt = r;            // a[gt+1..r] > pivot
    int i = l;             // Current index

    while (i <= gt) {
        if (a[i] < pivot) {       // Element less than pivot
            swap(a[i], a[lt]);    // Move to left part
            lt++;
            i++;
        } else if (a[i] > pivot) { // Element greater than pivot
            swap(a[i], a[gt]);    // Move to right part
            gt--;
        } else {                   // Element equal to pivot
            i++;                   // Stay in middle
        }
    }

    m1 = lt;  // Start index of elements equal to pivot
    m2 = gt;  // End index of elements equal to pivot
}

// Randomized QuickSort using 3-way partition
void randomized_quick_sort(vector<int> &a, int l, int r) {
    if (l >= r) return;          // Base case: 0 or 1 element

    int k = l + rand() % (r - l + 1); // Pick random pivot
    swap(a[l], a[k]);                 // Move pivot to start

    int m1, m2;
    partition3(a, l, r, m1, m2);     // Partition array around pivot

    randomized_quick_sort(a, l, m1 - 1);  // Sort left part
    randomized_quick_sort(a, m2 + 1, r);  // Sort right part
}

int main() {
    int n;
    cin >> n;                   // Number of elements
    vector<int> a(n);

    // Read array elements
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Sort array using randomized 3-way QuickSort
    randomized_quick_sort(a, 0, n - 1);

    // Print sorted array
    for (int i = 0; i < n; ++i) {
        cout << a[i] << ' ';
    }
}

/*
===============================================================
                PROGRAM EXPLANATION — STEP BY STEP
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
   Sort a given array of integers (may contain duplicates)
   using a modification of Randomized QuickSort that works 
   in O(n log n) expected time.

---------------------------------------------------------------
2. HOW THE CODE WORKS:
---------------------------------------------------------------
   → Randomly pick a pivot element in the current subarray.
   → Partition the array into 3 parts:
        - Elements less than pivot
        - Elements equal to pivot
        - Elements greater than pivot
   → Recursively sort the left and right parts only.
   → Elements equal to pivot are already in correct position.
   → Repeat until base case of 0 or 1 element.

---------------------------------------------------------------
3. PARTITION3 FUNCTION:
---------------------------------------------------------------
   → lt keeps track of the end of elements < pivot
   → gt keeps track of the start of elements > pivot
   → i scans the array from l to gt
   → Swap elements to move them to correct partition
   → Result: m1 = start of middle partition
             m2 = end of middle partition

---------------------------------------------------------------
4. EXAMPLE:
---------------------------------------------------------------
    Input:
        5
        2 3 9 2 2

    Step-by-step:
        - Random pivot chosen, e.g., 3
        - Partition: <3: 2 2 2, =3: 3, >3: 9
        - Recursively sort left: 2 2 2 (already sorted)
        - Recursively sort right: 9 (single element)
    Output:
        2 2 2 3 9

---------------------------------------------------------------
5. OUTPUT:
---------------------------------------------------------------
   Sorted array in non-decreasing order

---------------------------------------------------------------
6. COMPLEXITY:
---------------------------------------------------------------
   Expected Time Complexity: O(n log n)
   Space Complexity: O(log n) due to recursion stack

===============================================================
*/
