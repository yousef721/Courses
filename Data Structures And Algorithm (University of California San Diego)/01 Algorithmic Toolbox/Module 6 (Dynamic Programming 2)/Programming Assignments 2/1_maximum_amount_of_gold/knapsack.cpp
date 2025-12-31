#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to compute Maximum Amount of Gold
int maxGold(int W, vector<int>& w) {

    int n = w.size();

    // DP table
    // dp[i][j] → maximum weight that can be achieved
    // using the first i gold bars with capacity j
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Fill DP table bottom-up
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {

            // Do not take the i-th gold bar
            dp[i][j] = dp[i - 1][j];

            // Take the i-th gold bar if it fits
            if (w[i - 1] <= j) {
                dp[i][j] = max(
                    dp[i][j],
                    dp[i - 1][j - w[i - 1]] + w[i - 1]
                );
            }
        }
    }

    // Final answer
    return dp[n][W];
}

int main() {

    // Read backpack capacity and number of gold bars
    int W, n;
    cin >> W >> n;

    // Read gold bar weights
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    // Print maximum weight of gold
    cout << maxGold(W, w) << endl;

    return 0;
}

/*
===============================================================
        PROGRAM EXPLANATION — MAXIMUM AMOUNT OF GOLD
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
   Given:
     - A backpack with maximum capacity W
     - n gold bars with integer weights w1, w2, ..., wn

   Goal:
     - Select a subset of gold bars such that:
         • Total weight ≤ W
         • Total weight is maximized
     - Each gold bar can be taken at most once (0/1 Knapsack)

---------------------------------------------------------------
2. HOW THE ALGORITHM WORKS:
---------------------------------------------------------------
   → Dynamic Programming (Bottom-Up approach):

     STEP 1: Define a DP table dp[][] where:
             dp[i][j] represents the maximum total weight
             achievable using:
               - first i gold bars
               - backpack capacity j

     STEP 2: Base cases:
             - dp[0][j] = 0 → no gold bars available
             - dp[i][0] = 0 → backpack capacity is zero

     STEP 3: Fill the DP table:
             - Do NOT take the current gold bar:
                 dp[i][j] = dp[i - 1][j]

             - Take the current gold bar (if it fits):
                 dp[i][j] = dp[i - 1][j - w[i - 1]] + w[i - 1]

             - Choose the maximum of both options

     STEP 4: The final answer is stored in dp[n][W]

---------------------------------------------------------------
3. EXAMPLE:
---------------------------------------------------------------
   Input:
       W = 10
       Gold bars = {1, 4, 8}

   Possible combinations:
       {1, 8} → total weight = 9
       {4}    → total weight = 4
       {8}    → total weight = 8

   Maximum achievable weight = 9

---------------------------------------------------------------
4. OUTPUT:
---------------------------------------------------------------
   The program outputs a single integer representing
   the maximum total weight of gold bars that can be
   placed into the backpack without exceeding capacity.

---------------------------------------------------------------
5. COMPLEXITY:
---------------------------------------------------------------
   Time Complexity:
       O(n × W)

   Space Complexity:
       O(n × W)

===============================================================
*/
