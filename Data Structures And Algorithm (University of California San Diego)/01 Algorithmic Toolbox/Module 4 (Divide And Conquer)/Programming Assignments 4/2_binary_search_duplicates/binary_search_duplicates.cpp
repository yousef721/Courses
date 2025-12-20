#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

// Function to find the FIRST occurrence of x using Binary Search
int binary_search_first(const vector<int> &a, int x) {
    int left = 0, right = (int)a.size() - 1;
    int result = -1; // stores the index of first found occurrence

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (a[mid] == x) {
            result = mid;      // store index
            right = mid - 1;   // continue searching LEFT side
        }
        else if (a[mid] < x) {
            left = mid + 1;    // search in RIGHT half
        }
        else {
            right = mid - 1;   // search in LEFT half
        }
    }
    return result; // returns -1 if x not found
}

// Linear search (used only for comparison)
int linear_search(const vector<int> &a, int x) {
  for (int i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

int main() {
  int n;
  cin >> n;            // size of array a
  vector<int> a(n);

  // Read sorted array
  for (int i = 0; i < a.size(); i++) {
    cin >> a[i];
  }

  int m;
  cin >> m;            // number of queries
  vector<int> b(m);

  // Read query numbers
  for (int i = 0; i < m; ++i) {
    cin >> b[i];
  }

  // For each query, print first occurrence using binary search
  for (int i = 0; i < m; ++i) {
    cout << binary_search_first(a, b[i]) << ' ';
  }
}


/*
===============================================================
                  PROGRAM EXPLANATION — STEP BY STEP
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
We have a sorted array 'a', and a list of m queries.

For each query number x:
   → We want to find the FIRST index where x appears in array a.
If x does not exist → return -1.

---------------------------------------------------------------
2. HOW THE BINARY SEARCH WORKS:
---------------------------------------------------------------

binary_search_first(a, x):

1) We search using the normal binary search idea.
2) Whenever we find x at position mid:
       - We STORE mid as a possible answer.
       - BUT we do NOT stop.
       - We move LEFT (right = mid - 1)
         Because we want the FIRST occurrence.
3) If a[mid] < x → move right.
4) If a[mid] > x → move left.
5) Loop ends → return result.

---------------------------------------------------------------
3. EXAMPLE:
---------------------------------------------------------------

Array:
    a = [1, 2, 2, 2, 5, 7]

Find first index of x = 2

Steps:
- mid = 2 → a[2] = 2 → store result = 2 → go left
- mid = 0 → a[0] = 1 → go right
- mid = 1 → a[1] = 2 → store result = 1 → go left
Loop ends → answer = 1

---------------------------------------------------------------
4. OUTPUT:
---------------------------------------------------------------
For each query we print:
   - The index of the FIRST occurrence of x
   - Or -1 if x not found.

---------------------------------------------------------------
5. COMPLEXITY:
---------------------------------------------------------------
Time:  O(m log n)      (m queries, each binary log n)
Space: O(1)

===============================================================
*/
