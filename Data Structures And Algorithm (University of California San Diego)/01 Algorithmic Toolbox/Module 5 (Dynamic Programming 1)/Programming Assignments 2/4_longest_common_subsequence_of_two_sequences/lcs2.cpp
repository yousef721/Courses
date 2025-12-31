#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to compute Longest Common Subsequence (LCS)
int lcs2(vector<int> &a, vector<int> &b) {

    int n = a.size();
    int m = b.size();

    // DP table
    // dp[i][j] → length of LCS between
    // first i elements of a and first j elements of b
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Fill DP table bottom-up
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            // If elements are equal
            if (a[i - 1] == b[j - 1]) {

                // Include this element in LCS
                dp[i][j] = dp[i - 1][j - 1] + 1;

            } else {

                // Take maximum by skipping one element
                dp[i][j] = max(
                    dp[i - 1][j],   // Skip element from a
                    dp[i][j - 1]    // Skip element from b
                );
            }
        }
    }

    // Final answer
    return dp[n][m];
}

int main() {

    // Read first sequence
    size_t n;
    cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Read second sequence
    size_t m;
    cin >> m;
    vector<int> b(m);
    for (size_t i = 0; i < m; i++) {
        cin >> b[i];
    }

    // Print LCS length
    cout << lcs2(a, b) << endl;

    return 0;
}

/*
===============================================================
        PROGRAM EXPLANATION — STEP BY STEP (LCS)
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
   Given two sequences (arrays) a and b, determine the length of
   the Longest Common Subsequence (LCS) between them.

   A subsequence:
     - Preserves the original order of elements
     - Does NOT need to be contiguous

---------------------------------------------------------------
2. HOW THE ALGORITHM WORKS:
---------------------------------------------------------------
   → Dynamic Programming (Bottom-Up approach):

     STEP 1: Define a DP table dp[][] where:
             dp[i][j] represents the length of the LCS between:
             - the first i elements of sequence a
             - the first j elements of sequence b

     STEP 2: Initialize base cases:
             - dp[i][0] = 0 → LCS with an empty sequence is 0
             - dp[0][j] = 0 → LCS with an empty sequence is 0

     STEP 3: Fill the DP table:
             - If a[i - 1] == b[j - 1]:
                 dp[i][j] = dp[i - 1][j - 1] + 1
             - Otherwise:
                 dp[i][j] = max(
                     dp[i - 1][j],   // Skip element from a
                     dp[i][j - 1]    // Skip element from b
                 )

     STEP 4: The final LCS length is stored in dp[n][m].

---------------------------------------------------------------
3. EXAMPLE:
---------------------------------------------------------------
   Input:
       a = {1, 3, 4, 1}
       b = {3, 4, 1, 2}

   Longest Common Subsequence:
       {3, 4, 1}

   LCS length = 3

---------------------------------------------------------------
4. OUTPUT:
---------------------------------------------------------------
   The program outputs a single integer representing the
   length of the Longest Common Subsequence between
   the two input sequences.

---------------------------------------------------------------
5. COMPLEXITY:
---------------------------------------------------------------
   Time Complexity:
       O(n × m)

   Space Complexity:
       O(n × m)

===============================================================
*/
