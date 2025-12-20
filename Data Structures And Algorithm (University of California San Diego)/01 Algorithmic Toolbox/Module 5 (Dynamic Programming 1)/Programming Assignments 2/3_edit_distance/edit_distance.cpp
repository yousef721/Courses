#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Function to compute Edit Distance between two strings
int edit_distance(const string &str1, const string &str2) {

    // Get lengths of the two strings
    int n = str1.size();
    int m = str2.size();

    // DP table
    // dp[i][j] → minimum operations to convert
    // first i characters of str1 into first j characters of str2
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    // Base cases
    // Converting first i characters to empty string → i deletions
    for (int i = 0; i <= n; i++)
        dp[i][0] = i;

    // Converting empty string to first j characters → j insertions
    for (int j = 0; j <= m; j++)
        dp[0][j] = j;

    // Fill DP table bottom-up
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            // If characters are equal
            if (str1[i - 1] == str2[j - 1]) {

                // No operation needed
                dp[i][j] = dp[i - 1][j - 1];

            } else {

                // Characters are different
                // Take minimum of:
                // 1. Delete
                // 2. Insert
                // 3. Replace
                dp[i][j] = 1 + min({
                    dp[i - 1][j],     // Delete
                    dp[i][j - 1],     // Insert
                    dp[i - 1][j - 1]  // Replace
                });
            }
        }
    }

    // Final answer
    return dp[n][m];
}

int main() {

    // Read input strings
    string str1, str2;
    cin >> str1 >> str2;

    // Print edit distance
    cout << edit_distance(str1, str2) << endl;

    return 0;
}

/*
===============================================================
            PROGRAM EXPLANATION — STEP BY STEP
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
   Given two strings str1 and str2, find the minimum number of
   operations required to convert str1 into str2.

   Allowed operations:
     - Insert a character
     - Delete a character
     - Replace a character

---------------------------------------------------------------
2. HOW THE ALGORITHM WORKS:
---------------------------------------------------------------
   → Dynamic Programming (Bottom-Up approach):

     STEP 1: Define a DP table dp[][] where:
             dp[i][j] represents the minimum number of
             operations needed to convert the first i characters
             of str1 into the first j characters of str2.

     STEP 2: Initialize base cases:
             - dp[i][0] = i  → delete all characters
             - dp[0][j] = j  → insert all characters

     STEP 3: For each pair (i, j):
             - If characters are equal → no operation
             - Otherwise:
               dp[i][j] = 1 + min(delete, insert, replace)

     STEP 4: The answer is stored in dp[n][m].

---------------------------------------------------------------
3. EXAMPLE:
---------------------------------------------------------------
   Input:
       str1 = "short"
       str2 = "ports"

   Operations:
       short → port   (replace 's' with 'p')
       port  → ports  (insert 's')

   Minimum number of operations = 3

---------------------------------------------------------------
4. OUTPUT:
---------------------------------------------------------------
   The program outputs a single integer representing the
   minimum edit distance between the two strings.

---------------------------------------------------------------
5. COMPLEXITY:
---------------------------------------------------------------
   Time Complexity:
       O(n × m)

   Space Complexity:
       O(n × m)

===============================================================
*/
