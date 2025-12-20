#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Function to find a majority element (appears more than n/2 times)
int get_majority_element(vector<int> &a, int left, int right) {

    // STEP 1: If the range is empty → no majority
    if (left == right) return -1;

    // STEP 2: If the range has only 1 element → it is the candidate
    if (left + 1 == right) return a[left];

    // STEP 3: Split array into two halves
    int mid = left + (right - left) / 2;

    // STEP 4: Recursively find majority candidate in left half
    int left_major = get_majority_element(a, left, mid);

    // STEP 5: Recursively find majority candidate in right half
    int right_major = get_majority_element(a, mid, right);

    // STEP 6: If both halves agree on the same majority candidate, return it
    if (left_major == right_major) return left_major;

    // STEP 7: Count occurrences of each candidate in the whole range
    int left_count = 0;
    int right_count = 0;

    for (int i = left; i < right; i++) {
        if (a[i] == left_major) left_count++;
        if (a[i] == right_major) right_count++;
    }

    // STEP 8: Calculate half size of range
    int half = (right - left) / 2;

    // STEP 9: Check if left candidate is majority
    if (left_count > half) return left_major;

    // STEP 10: Check if right candidate is majority
    if (right_count > half) return right_major;

    // STEP 11: No majority element in this segment
    return -1;
}

int main() {
    int n;
    cin >> n; // read size of array

    vector<int> a(n);

    // Read n numbers
    for (int i = 0; i < a.size(); ++i)
        cin >> a[i];

    // Print 1 if majority exists, 0 otherwise
    cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
/*
===============================================================
                PROGRAM EXPLANATION — STEP BY STEP
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
   We are given a list of n integers.
   A majority element is one that appears MORE than n/2 times.

   Goal → Decide if a majority element exists or not.

---------------------------------------------------------------
2. HOW THE CODE WORKS (Divide & Conquer):
---------------------------------------------------------------
   The array is split into two halves:
       - Left half may contain a majority candidate.
       - Right half may contain a majority candidate.

   Steps:
   → If both halves give the same majority → return it.
   → Otherwise:
       - Count how many times the left candidate appears.
       - Count how many times the right candidate appears.
       - If either appears more than half of the range → it's the majority.
       - Else → NO majority.

   This uses the idea that:
       “A majority element in the whole array must be majority in one half.”

---------------------------------------------------------------
3. EXAMPLE:
---------------------------------------------------------------
   Input:
       n = 5
       [2, 3, 9, 2, 2]

   Divide into halves:
       Left:  [2, 3]
       Right: [9, 2, 2]

   Left half → no majority (-1)
   Right half → 2 is candidate

   Count in full array:
       2 appears 3 times > 5/2 → Majority exists ✓

   Output: 1

---------------------------------------------------------------
4. OUTPUT:
---------------------------------------------------------------
   1 → if a majority element exists
   0 → if no majority element exists

---------------------------------------------------------------
5. COMPLEXITY:
---------------------------------------------------------------
   Time complexity:  O(n log n)
   Space complexity: O(log n)

===============================================================
*/