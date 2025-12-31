#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to compute Longest Common Subsequence (LCS)
// among three sequences using Dynamic Programming
int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {

    int n = a.size();
    int m = b.size();
    int l = c.size();

    // 3D DP table
    // dp[i][j][k] → length of LCS between:
    // first i elements of a,
    // first j elements of b,
    // first k elements of c
    vector<vector<vector<int>>> dp(
        n + 1,
        vector<vector<int>>(m + 1, vector<int>(l + 1, 0))
    );

    // Fill DP table bottom-up
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k <= l; k++) {

                // If current elements in all three sequences are equal
                if (a[i - 1] == b[j - 1] && a[i - 1] == c[k - 1]) {

                    // Include this element in LCS
                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;

                } else {

                    // Otherwise, take the maximum by skipping
                    // one element from any of the three sequences
                    dp[i][j][k] = max({
                        dp[i - 1][j][k],   // Skip element from a
                        dp[i][j - 1][k],   // Skip element from b
                        dp[i][j][k - 1]    // Skip element from c
                    });
                }
            }
        }
    }

    // Final answer
    return dp[n][m][l];
}

int main() {

    // Read first sequence
    size_t an;
    cin >> an;
    vector<int> a(an);
    for (size_t i = 0; i < an; i++) {
        cin >> a[i];
    }

    // Read second sequence
    size_t bn;
    cin >> bn;
    vector<int> b(bn);
    for (size_t i = 0; i < bn; i++) {
        cin >> b[i];
    }

    // Read third sequence
    size_t cn;
    cin >> cn;
    vector<int> c(cn);
    for (size_t i = 0; i < cn; i++) {
        cin >> c[i];
    }

    // Print LCS length for three sequences
    cout << lcs3(a, b, c) << endl;

    return 0;
}

/*
===============================================================
   PROGRAM EXPLANATION — STEP BY STEP (LCS of 3 Sequences)
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
   Given three sequences (arrays) a, b, and c, determine the
   length of the Longest Common Subsequence (LCS) shared
   among all three sequences.

   A subsequence:
     - Preserves the original order of elements
     - Does NOT need to be contiguous

---------------------------------------------------------------
2. HOW THE ALGORITHM WORKS:
---------------------------------------------------------------
   → Dynamic Programming (Bottom-Up approach):

     STEP 1: Define a 3D DP table dp[][][] where:
             dp[i][j][k] represents the length of the LCS between:
             - the first i elements of sequence a
             - the first j elements of sequence b
             - the first k elements of sequence c

     STEP 2: Initialize base cases:
             - If any of i, j, or k equals 0:
               dp[i][j][k] = 0
             → LCS with an empty sequence is always 0

     STEP 3: Fill the DP table:
             - If the current elements are equal:
                 a[i - 1] == b[j - 1] == c[k - 1]
               then:
                 dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1

             - Otherwise:
               dp[i][j][k] = max(
                   dp[i - 1][j][k],   // Skip element from a
                   dp[i][j - 1][k],   // Skip element from b
                   dp[i][j][k - 1]    // Skip element from c
               )

     STEP 4: The final answer is stored in dp[n][m][l].

---------------------------------------------------------------
3. EXAMPLE:
---------------------------------------------------------------
   Input:
       a = {1, 2, 3}
       b = {2, 1, 3}
       c = {1, 3, 5}

   Longest Common Subsequence:
       {1, 3}

   LCS length = 2

---------------------------------------------------------------
4. OUTPUT:
---------------------------------------------------------------
   The program outputs a single integer representing the
   length of the Longest Common Subsequence among
   the three input sequences.

---------------------------------------------------------------
5. COMPLEXITY:
---------------------------------------------------------------
   Time Complexity:
       O(n × m × l)

   Space Complexity:
       O(n × m × l)

===============================================================
*/
