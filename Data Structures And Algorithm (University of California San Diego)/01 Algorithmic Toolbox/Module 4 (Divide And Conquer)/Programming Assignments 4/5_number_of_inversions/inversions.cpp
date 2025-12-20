#include <iostream>
#include <vector>

using namespace std;

// Function to merge two sorted halves and count inversions
long long merge_and_count(vector<int> &a, vector<int> &b, int left, int mid, int right) {
    long long inv_count = 0; // Initialize inversion counter
    int i = left;  // Pointer for left half
    int j = mid;   // Pointer for right half
    int k = left;  // Pointer for temporary array b

    // STEP 1: Merge two halves while counting inversions
    while (i < mid && j < right) {
        if (a[i] <= a[j]) {
            b[k++] = a[i++]; // No inversion, place element from left half
        } else {
            b[k++] = a[j++]; // Place element from right half
            inv_count += (mid - i); // All remaining elements in left half are inversions
        }
    }

    // STEP 2: Copy remaining elements from left half
    while (i < mid) {
        b[k++] = a[i++];
    }

    // STEP 3: Copy remaining elements from right half
    while (j < right) {
        b[k++] = a[j++];
    }

    // STEP 4: Copy merged result back to original array
    for (int i = left; i < right; i++) {
        a[i] = b[i];
    }

    // STEP 5: Return number of inversions counted in this merge
    return inv_count;
}

// Function to recursively count inversions using divide and conquer
long long get_number_of_inversions(vector<int> &a, vector<int> &b, int left, int right) {
    long long number_of_inversions = 0;

    // BASE CASE: single element or empty array → no inversions
    if (right <= left + 1) return number_of_inversions;

    // STEP 1: Divide the array into two halves
    int mid = left + (right - left) / 2;

    // STEP 2: Count inversions in left half
    number_of_inversions += get_number_of_inversions(a, b, left, mid);

    // STEP 3: Count inversions in right half
    number_of_inversions += get_number_of_inversions(a, b, mid, right);

    // STEP 4: Count inversions across halves while merging
    number_of_inversions += merge_and_count(a, b, left, mid, right);

    return number_of_inversions; // Return total inversions
}

int main() {
    int n;
    cin >> n; // Number of elements in the array
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i]; // Input array elements
    }
    vector<int> b(a.size()); // Temporary array for merging

    // STEP 5: Compute and output total number of inversions
    cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
}

/*
===============================================================
                PROGRAM EXPLANATION — STEP BY STEP
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
   Given a sequence of n integers, count the number of inversions:
   An inversion is a pair (i, j) such that i < j and a[i] > a[j].
   Goal → Compute the total number of inversions efficiently in O(n log n) time.

---------------------------------------------------------------
2. HOW THE CODE WORKS:
---------------------------------------------------------------
   → Use divide-and-conquer (MergeSort approach) to split array into halves.
   → Recursively count inversions in left and right halves.
   → Merge the two sorted halves while counting inversions across halves.
   → Merging step ensures that all inversions between two halves are counted in O(n) time.
   → Sum up inversions from left, right, and across halves.

---------------------------------------------------------------
3. EXAMPLE:
---------------------------------------------------------------
   Input:
       n = 5
       Array = 2 3 9 2 9

   Step-by-step:
   - Divide: [2,3] and [9,2,9]
   - Left half: [2,3] → no inversions → [2,3]
   - Right half: [9,2,9] → divide → [9] and [2,9]
     - Merge [2,9] → no inversions
     - Merge [9] and [2,9] → inversions: 9>2 → count=1
   - Merge final halves [2,3] and [2,9,9] → inversions: 3>2 → count+=1
   - Total inversions = 2

---------------------------------------------------------------
4. OUTPUT:
---------------------------------------------------------------
   Prints a single integer → total number of inversions.

---------------------------------------------------------------
5. COMPLEXITY:
---------------------------------------------------------------
   Time complexity: O(n log n)
   Space complexity: O(n) (temporary array for merging)

===============================================================
*/
