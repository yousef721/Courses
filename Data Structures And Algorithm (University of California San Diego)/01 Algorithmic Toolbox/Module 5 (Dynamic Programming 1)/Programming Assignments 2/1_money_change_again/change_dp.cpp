#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to compute minimum number of coins
int get_change(int m) {

    // Available coin denominations
    vector<int> coins = {1, 3, 4};

    // DP array
    // minCoins[i] → minimum number of coins needed to make value i
    vector<int> minCoins(m + 1, 10000);

    // Base cases
    minCoins[0] = 0;   // 0 value needs 0 coins

    //  Build solution bottom-up
    for (int i = 1; i <= m; i++) {

        // Try each coin denomination
        for (int coin : coins) {

            // Check if coin can be used
            if (i >= coin) {

                // DP transition
                minCoins[i] = min(
                    minCoins[i],
                    minCoins[i - coin] + 1
                );
            }
        }
    }

    // Return final answer
    return minCoins[m];
}

int main() {
    int m;
    cin >> m;

    // Print minimum number of coins
    cout << get_change(m) << '\n';

    return 0;
}

/*
===============================================================
                PROGRAM EXPLANATION — STEP BY STEP
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
   Given an integer m, the goal is to compute the minimum number
   of coins needed to represent the value m using the coin
   denominations {1, 3, 4}.

---------------------------------------------------------------
2. HOW THE ALGORITHM WORKS:
---------------------------------------------------------------
   → Dynamic Programming (Bottom-Up approach):

     STEP 1: Create a DP array minCoins[] of size (m + 1),
             where:
             minCoins[i] = minimum number of coins needed
             to make value i.

     STEP 2: Initialize all values in minCoins[] with a very
             large number (10000), which represents infinity
             (an unreachable state).

     STEP 3: Set the base case:
             minCoins[0] = 0
             (zero coins are needed to make value 0)

     STEP 4: Iterate through all values from 1 to m.
             For each value i, try all available coin
             denominations {1, 3, 4}.

     STEP 5: For each coin, if coin ≤ i, update:
             minCoins[i] = min(
                 minCoins[i],
                 minCoins[i - coin] + 1
             )

             This represents choosing the current coin and
             adding one coin to the optimal solution of
             (i - coin).

     STEP 6: After filling the DP table, the answer is stored
             in minCoins[m].

---------------------------------------------------------------
3. EXAMPLE:
---------------------------------------------------------------
   Input:
       m = 10

   Possible representations:
       10 = 4 + 3 + 3  → 3 coins
       10 = 1 + 1 + ... + 1 → 10 coins

   Optimal solution:
       Minimum number of coins = 3

---------------------------------------------------------------
4. OUTPUT:
---------------------------------------------------------------
   The program outputs a single integer representing the
   minimum number of coins needed to form the value m.

---------------------------------------------------------------
5. COMPLEXITY:
---------------------------------------------------------------
   Time Complexity:
       O(m × k), where k is the number of coin denominations
       (k = 3 in this problem).

   Space Complexity:
       O(m), due to the DP array minCoins[].

===============================================================
*/
