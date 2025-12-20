#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find the minimum unchangeable amount
int minUnchangeableAmount(vector<int> coins) {
    // STEP 1: Sort coins in ascending order
    sort(coins.begin(), coins.end());

    // STEP 2: Initialize result as 1 (smallest amount we want to check)
    int res = 1;

    // STEP 3: Traverse the coins
    for (int coin : coins) {
        // If coin is <= res, we can form all amounts up to res + coin - 1
        if (coin <= res) {
            res += coin;
        } else {
            // If coin > res, res cannot be formed
            break;
        }
    }

    // STEP 4: Return the minimum unchangeable amount
    return res;
}

int main() {
    int n;
    cin >> n; // Number of coins

    vector<int> coins(n);

    // Read input coins
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    // Compute minimum unchangeable amount
    int result = minUnchangeableAmount(coins);

    // Print result
    cout << result << endl;

    return 0;
}

/*
===============================================================
                PROGRAM EXPLANATION — STEP BY STEP
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
    We have a set of coins with denominations:
        c1 ≤ c2 ≤ ... ≤ cn

    Goal → Find the smallest amount of money that cannot be formed 
        using any combination of these coins.

---------------------------------------------------------------
2. HOW THE CODE WORKS:
---------------------------------------------------------------
    → Sort the coins in ascending order.
    → Initialize res = 1 (smallest amount we want to check).
    → For each coin:
        - If coin <= res → we can form all amounts up to res + coin - 1
            → update res = res + coin
        - Else → res cannot be formed → break
    → Return res as the minimum unchangeable amount.

---------------------------------------------------------------
3. EXAMPLE:
---------------------------------------------------------------
Input:
    4
    1 1 2 5

    Step-by-step:
    - Sort coins: [1,1,2,5]
    - res = 1
    - coin = 1 → 1 <= 1 → res = 1+1 = 2
    - coin = 1 → 1 <= 2 → res = 2+1 = 3
    - coin = 2 → 2 <= 3 → res = 3+2 = 5
    - coin = 5 → 5 <= 5 → res = 5+5 = 10
    - All coins processed → Output: 10

---------------------------------------------------------------
4. OUTPUT:
---------------------------------------------------------------
    Minimum unchangeable amount = 10

---------------------------------------------------------------
5. COMPLEXITY:
---------------------------------------------------------------
    Time complexity: O(n log n) (for sorting)
    Space complexity: O(1) extra space

===============================================================
*/
