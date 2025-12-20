#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

// Classic Binary Search: returns ANY index where x appears
int binary_search(const vector<int> &a, int x) {
    int left = 0, right = (int)a.size() - 1;

    while (left <= right)
    {
      int mid = (right + left) / 2;

      if (a[mid] == x)
      {
        return mid; // found -> return immediately
      }
      if (a[mid] < x)
      {
        left = mid + 1; // search right
      }
      else
      {
        right = mid - 1; // search left
      }
    }
    return -1; // not found
}

int linear_search(const vector<int> &a, int x) {
  for (int i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

int main() {
  int n;
  cin >> n;     // size of array
  vector<int> a(n);

  // Input array
  for (int i = 0; i < a.size(); i++) {
    cin >> a[i];
  }

  int m;
  cin >> m;     // number of queries
  vector<int> b(m);

  // Input queries
  for (int i = 0; i < m; ++i) {
    cin >> b[i];
  }

  // For each query, run binary search
  for (int i = 0; i < m; ++i) {
    cout << binary_search(a, b[i]) << ' ';
  }
}

/*
===============================================================
                  PROGRAM EXPLANATION — STEP BY STEP
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
  Given:
    - Sorted array 'a'
    - List of queries 'b'

  For each x in b:
    → Find ANY index where x appears in a.
  If x not found → print -1.

---------------------------------------------------------------
2. HOW THE BINARY SEARCH WORKS:
---------------------------------------------------------------

  binary_search(a, x):

  1) Compute mid index.
  2) If x == a[mid] → return mid immediately.
  3) If x > a[mid] → search RIGHT half.
  4) If x < a[mid] → search LEFT half.
  5) If left > right → x does NOT exist → return -1.

---------------------------------------------------------------
3. EXAMPLE:
---------------------------------------------------------------

  Array:
      a = [1, 3, 4, 6, 8, 9]

  Searching x = 6
  mid = 2 → a[2]=4 <6 → go right
  mid = 4 → a[4]=8 >6 → go left
  mid = 3 → a[3]=6 → FOUND → return 3

---------------------------------------------------------------
4. OUTPUT:
---------------------------------------------------------------
  Print a single line of m numbers:
  each number is the index of x in a,
  or -1 if not found.

---------------------------------------------------------------
5. COMPLEXITY:
---------------------------------------------------------------
  Time:  O(m log n)
  Space: O(1)

===============================================================
*/
