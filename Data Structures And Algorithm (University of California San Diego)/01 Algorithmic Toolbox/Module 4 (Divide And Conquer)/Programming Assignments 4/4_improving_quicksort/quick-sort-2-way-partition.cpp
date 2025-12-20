#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

// ================================================================
//                RANDOMIZED QUICK SORT (2-WAY PARTITION)
// ================================================================

// Partition function (2-way)
// Partitions array a[l..r] around pivot a[l]
// Elements <= pivot go to the left, elements > pivot go to the right
int partition2(vector<int> &a, int l, int r) {
    int x = a[l];    // Choose pivot as first element
    int j = l;       // Index of last element <= pivot

    for (int i = l + 1; i <= r; i++) {
        if (a[i] <= x) {       // Element smaller or equal to pivot
            j++;
            swap(a[i], a[j]);  // Move it to left partition
        }
    }

    swap(a[l], a[j]);  // Place pivot in its correct position
    return j;           // Return index of pivot
}

// Randomized QuickSort function
void randomized_quick_sort(vector<int> &a, int l, int r) {
    if (l >= r) return;      // Base case: 0 or 1 element

    int k = l + rand() % (r - l + 1);  // Pick random pivot index
    swap(a[l], a[k]);                 // Move pivot to start

    int m = partition2(a, l, r);      // Partition array

    randomized_quick_sort(a, l, m - 1); // Sort left partition
    randomized_quick_sort(a, m + 1, r); // Sort right partition
}

// ================================================================
// Main function
// ================================================================
int main() {
    int n;
    cin >> n;                   // Number of elements
    vector<int> a(n);

    // Read array elements
    for (size_t i = 0; i < a.size(); ++i) {
        cin >> a[i];
    }

    // Sort array using Randomized QuickSort
    randomized_quick_sort(a, 0, a.size() - 1);

    // Print sorted array
    for (size_t i = 0; i < a.size(); ++i) {
        cout << a[i] << ' ';
    }
}

/*
===============================================================
                PROGRAM EXPLANATION — STEP BY STEP
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
   Sort a given array of integers using Randomized QuickSort
   with 2-way partitioning.

---------------------------------------------------------------
2. HOW THE CODE WORKS:
---------------------------------------------------------------
   → Randomly pick a pivot element from the current subarray.
   → Swap it with the first element.
   → Partition the array such that:
        - Elements <= pivot go to the left
        - Elements > pivot go to the right
   → Place pivot in its correct position.
   → Recursively sort left and right subarrays.
   → Stop recursion when subarray has 0 or 1 element.

---------------------------------------------------------------
3. PARTITION2 FUNCTION:
---------------------------------------------------------------
   → 'x' is the pivot.
   → 'j' keeps track of last element <= pivot.
   → Scan array from l+1 to r:
       - If a[i] <= pivot, increment j and swap a[i] with a[j].
   → Finally, swap pivot with a[j] to place it correctly.
   → Return index j of pivot.

---------------------------------------------------------------
4. EXAMPLE:
---------------------------------------------------------------
  Input:
      5
      2 3 9 2 2

  Step-by-step:
      - Random pivot chosen, e.g., 3
      - Partition: <=3: 2 2 2 3, >3: 9
      - Pivot 3 is at correct position
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
