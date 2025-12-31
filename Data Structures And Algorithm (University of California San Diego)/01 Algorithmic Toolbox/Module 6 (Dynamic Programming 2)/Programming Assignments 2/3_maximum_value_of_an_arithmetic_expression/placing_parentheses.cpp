#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

// Function to evaluate a single operation
long long eval(long long a, long long b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    return 0;
}

// Function to compute Maximum Value of Expression
long long get_maximum_value(const string& exp) {

    int n = (exp.size() + 1) / 2;

    // Extract digits
    vector<long long> digits(n);
    for (int i = 0; i < n; i++) {
        digits[i] = exp[2 * i] - '0';
    }

    // Extract operators
    vector<char> ops(n - 1);
    for (int i = 0; i < n - 1; i++) {
        ops[i] = exp[2 * i + 1];
    }

    // DP tables
    // minVal[i][j] → minimum value of subexpression from i to j
    // maxVal[i][j] → maximum value of subexpression from i to j
    vector<vector<long long>> minVal(n, vector<long long>(n, 0));
    vector<vector<long long>> maxVal(n, vector<long long>(n, 0));

    // Base case: single digit
    for (int i = 0; i < n; i++) {
        minVal[i][i] = digits[i];
        maxVal[i][i] = digits[i];
    }

    // Fill DP tables bottom-up
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;

            minVal[i][j] = LLONG_MAX;
            maxVal[i][j] = LLONG_MIN;

            // Try all possible splits
            for (int k = i; k < j; k++) {

                long long a = eval(maxVal[i][k], maxVal[k + 1][j], ops[k]);
                long long b = eval(maxVal[i][k], minVal[k + 1][j], ops[k]);
                long long c = eval(minVal[i][k], maxVal[k + 1][j], ops[k]);
                long long d = eval(minVal[i][k], minVal[k + 1][j], ops[k]);

                minVal[i][j] = min(minVal[i][j], min({a, b, c, d}));
                maxVal[i][j] = max(maxVal[i][j], max({a, b, c, d}));
            }
        }
    }

    // Final answer
    return maxVal[0][n - 1];
}

int main() {

    // Read arithmetic expression
    string s;
    cin >> s;

    // Print maximum value
    cout << get_maximum_value(s) << endl;

    return 0;
}

/*
===============================================================
        PROGRAM EXPLANATION — PLACE PARENTHESES
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
   Given:
     - An arithmetic expression consisting of digits
       and operators (+, -, *)

   Goal:
     - Add parentheses in the expression such that:
         • The computed value is maximized
     - Each digit remains in the same order
     - Operator precedence is ignored

---------------------------------------------------------------
2. HOW THE ALGORITHM WORKS:
---------------------------------------------------------------
   → Dynamic Programming (Bottom-Up approach):

     STEP 1: Define two DP tables:
             minVal[i][j] → minimum value of subexpression
             maxVal[i][j] → maximum value of subexpression

             where the subexpression spans from digit i to digit j

     STEP 2: Base cases:
             - A single digit has:
                 minVal[i][i] = maxVal[i][i] = digit[i]

     STEP 3: Fill the DP tables:
             - For each subexpression length
             - Try all possible split points k
             - Evaluate all combinations:
                 • max with max
                 • max with min
                 • min with max
                 • min with min

     STEP 4: Store the minimum and maximum values
             for each subexpression

---------------------------------------------------------------
3. EXAMPLE:
---------------------------------------------------------------
   Input:
       Expression = "1+5*3-2"

   Possible parenthesizations:
       ((1+5)*(3-2)) = 6
       (1+(5*(3-2))) = 6
       ((1+5)*3)-2 = 16
       1+(5*(3-2)) = 6

   Maximum achievable value = 16

---------------------------------------------------------------
4. OUTPUT:
---------------------------------------------------------------
   The program outputs a single integer representing
   the maximum value obtainable by placing parentheses
   in the expression.

---------------------------------------------------------------
5. COMPLEXITY:
---------------------------------------------------------------
   Time Complexity:
       O(n³)

   Space Complexity:
       O(n²)

===============================================================
*/
