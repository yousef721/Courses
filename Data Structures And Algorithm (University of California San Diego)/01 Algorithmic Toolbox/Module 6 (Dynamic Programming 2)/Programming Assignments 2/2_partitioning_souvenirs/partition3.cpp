#include <iostream>
#include <vector>
#include <numeric>   // for accumulate

using namespace std;

// Function to check if array can be partitioned into 3 subsets with equal sum
int partition3(vector<int> &v) {

    int n = v.size();

    // Compute total sum of all elements
    int totalSum = accumulate(v.begin(), v.end(), 0);

    // If total sum is not divisible by 3, partition is impossible
    if (totalSum % 3 != 0)
        return 0;

    // Each subset must have this sum
    int target = totalSum / 3;

    /*
        DP table:
        dp[i][s1][s2] = true if using the first i elements,
        we can form:
          - subset 1 with sum s1
          - subset 2 with sum s2
        (subset 3 automatically has the remaining sum)
    */
    vector<vector<vector<bool>>> dp(
        n + 1,
        vector<vector<bool>>(target + 1, vector<bool>(target + 1, false))
    );

    // Base case:
    // Using 0 elements, we can make sum 0 in subset 1 and subset 2
    dp[0][0][0] = true;

    // Fill DP table bottom-up
    for (int i = 1; i <= n; i++) {

        int val = v[i - 1];

        for (int s1 = 0; s1 <= target; s1++) {
            for (int s2 = 0; s2 <= target; s2++) {

                // Case 1: Do not take current element
                if (dp[i - 1][s1][s2])
                    dp[i][s1][s2] = true;

                // Case 2: Take element into subset 1
                if (s1 >= val && dp[i - 1][s1 - val][s2])
                    dp[i][s1][s2] = true;

                // Case 3: Take element into subset 2
                if (s2 >= val && dp[i - 1][s1][s2 - val])
                    dp[i][s1][s2] = true;
            }
        }
    }

    // If we can form two subsets with sum = target,
    // the third subset will also have sum = target
    return dp[n][target][target] ? 1 : 0;
}

int main() {

    // Read number of items
    int n;
    cin >> n;

    // Read values of the items
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    // Print result (1 = possible, 0 = not possible)
    cout << partition3(v) << endl;

    return 0;
}


/*
===============================================================
        PROGRAM EXPLANATION — SPLITTING THE PIRATE LOOT
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
   Given:
     - n integers representing loot values

   Goal:
     - Check if they can be partitioned into 3 disjoint subsets
       with equal total sum.

---------------------------------------------------------------
2. KEY OBSERVATION:
---------------------------------------------------------------
   - totalSum = sum of all elements
   - If totalSum % 3 != 0 → partition impossible
   - Otherwise:
       target sum per subset = totalSum / 3

---------------------------------------------------------------
3. HOW THE ALGORITHM WORKS:
---------------------------------------------------------------
   → Dynamic Programming (Bottom-Up approach):

     STEP 1: Define a 3D DP table dp[i][s1][s2]:
             dp[i][s1][s2] = true if using first i elements,
             subset 1 sum = s1, subset 2 sum = s2
             (subset 3 automatically gets remaining sum)

     STEP 2: Base case:
             dp[0][0][0] = true → 0 elements can form sum 0

     STEP 3: Fill DP table:
             - Case 1: Do not take current element
             - Case 2: Take element into subset 1 (if fits)
             - Case 3: Take element into subset 2 (if fits)

     STEP 4: The final answer is dp[n][target][target]

---------------------------------------------------------------
4. EXAMPLE:
---------------------------------------------------------------
   Input:
       n = 13
       v = {1, 2, 3, 4, 5, 5, 7, 7, 8, 10, 12, 19, 25}

   totalSum = 108
   target   = 36

   One valid partition:
       Subset 1: {1, 3, 7, 25}       → sum = 36
       Subset 2: {2, 4, 5, 7, 8, 10} → sum = 36
       Subset 3: {5, 12, 19}         → sum = 36

   Output:
       1

---------------------------------------------------------------
5. OUTPUT:
---------------------------------------------------------------
   Program outputs a single integer:
     1 → partition possible
     0 → partition impossible

---------------------------------------------------------------
6. COMPLEXITY:
---------------------------------------------------------------
   Time Complexity:
       O(n × target × target)

   Space Complexity:
       O(n × target × target)

===============================================================
*/
