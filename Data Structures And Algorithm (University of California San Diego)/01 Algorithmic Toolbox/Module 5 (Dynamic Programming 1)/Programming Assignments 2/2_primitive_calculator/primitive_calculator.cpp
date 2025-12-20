#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to compute optimal sequence from 1 to n
vector<int> optimal_sequence(int n) {

    // DP array
    // minOps[i] → minimum number of operations to reach i from 1
    vector<int> minOps(n + 1);

    // Parent array
    // prev[i] → previous number before reaching i
    vector<int> prev(n + 1);

    // Base case
    minOps[1] = 0;

    // Build DP table bottom-up
    for (int i = 2; i <= n; i++) {

        // Operation +1 (from i-1)
        minOps[i] = minOps[i - 1] + 1;
        prev[i] = i - 1;

        // Operation ×2
        if (i % 2 == 0 && minOps[i / 2] + 1 < minOps[i]) {
            minOps[i] = minOps[i / 2] + 1;
            prev[i] = i / 2;
        }

        // Operation ×3
        if (i % 3 == 0 && minOps[i / 3] + 1 < minOps[i]) {
            minOps[i] = minOps[i / 3] + 1;
            prev[i] = i / 3;
        }
    }

    // Reconstruct the optimal sequence
    vector<int> sequence;
    for (int i = n; i >= 1; i = prev[i]) {
        sequence.push_back(i);
        if (i == 1) break;
    }

    //  Reverse to get sequence from 1 to n
    reverse(sequence.begin(), sequence.end());

    return sequence;
}

int main() {

    int n;
    cin >> n;

    //  Get optimal sequence
    vector<int> sequence = optimal_sequence(n);

    //  Print minimum number of operations
    cout << sequence.size() - 1 << endl;

    //  Print the sequence
    for (int x : sequence) {
        cout << x << " ";
    }

    return 0;
}

/*
===============================================================
            PROGRAM EXPLANATION — STEP BY STEP
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
   Given a positive integer n, find the minimum number of
   operations needed to reach n starting from 1.

   Allowed operations:
     - Add 1 (+1)
     - Multiply by 2 (×2)
     - Multiply by 3 (×3)

   The program must also output the sequence of numbers used.

---------------------------------------------------------------
2. HOW THE ALGORITHM WORKS:
---------------------------------------------------------------
   → Dynamic Programming (Bottom-Up approach):

     STEP 1: Create an array minOps[] where:
             minOps[i] = minimum number of operations needed
             to reach i from 1.

     STEP 2: Create an array prev[] to store the previous
             number used to reach i.

     STEP 3: Initialize the base case:
             minOps[1] = 0

     STEP 4: For every number i from 2 to n:
             - Assume the last operation was +1
             - If i is divisible by 2, try ×2
             - If i is divisible by 3, try ×3
             - Choose the operation with minimum cost

     STEP 5: Store the chosen previous number in prev[].

     STEP 6: After filling the DP table, reconstruct the
             optimal sequence by following prev[] backwards
             from n to 1.

---------------------------------------------------------------
3. EXAMPLE:
---------------------------------------------------------------
   Input:
       n = 10

   Optimal sequence:
       1 → 3 → 9 → 10

   Operations:
       1 → 3  (×3)
       3 → 9  (×3)
       9 → 10 (+1)

   Minimum number of operations = 3

---------------------------------------------------------------
4. OUTPUT:
---------------------------------------------------------------
   Line 1: Minimum number of operations
   Line 2: The sequence of numbers from 1 to n

---------------------------------------------------------------
5. COMPLEXITY:
---------------------------------------------------------------
   Time Complexity:
       O(n)

   Space Complexity:
       O(n)

===============================================================
*/
