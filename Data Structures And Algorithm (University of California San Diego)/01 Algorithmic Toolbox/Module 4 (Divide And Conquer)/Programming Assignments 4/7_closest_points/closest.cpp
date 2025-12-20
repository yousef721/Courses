#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

// STEP 1: Compute Euclidean distance between two points
double dist(pair<int,int> a, pair<int,int> b) {
    double dx = a.first - b.first;
    double dy = a.second - b.second;
    return sqrt(dx*dx + dy*dy);
}

double solve(vector<pair<int,int>>& pts, int l, int r) {

    // STEP 2: Base Case — ≤ 3 points → brute force
    if (r - l <= 3) {
      double d = 1e18;
      for (int i = l; i <= r; i++)
          for (int j = i + 1; j <= r; j++)
              d = min(d, dist(pts[i], pts[j]));
      return d;
    }

    // STEP 3: Divide — find midpoint and solve left/right halves
    int mid = (l + r) / 2;
    double dl = solve(pts, l, mid);
    double dr = solve(pts, mid + 1, r);

    // STEP 4: Conquer — take minimum of left and right halves
    double d = min(dl, dr);

    // STEP 5: Create strip of points within distance d of mid line
    int midx = pts[mid].first;
    vector<pair<int,int>> strip;

    for (int i = l; i <= r; i++)
      if (abs(pts[i].first - midx) < d)
        strip.push_back(pts[i]);

    // STEP 6: Sort the strip by y-coordinate
    sort(strip.begin(), strip.end(), [](auto& a, auto& b){ return a.second < b.second; });

    // STEP 7: Compare each point with next few points in strip
    for (int i = 0; i < strip.size(); i++) {
        for (int j = i + 1; j < strip.size() && j <= i + 7; j++) {
            if ((strip[j].second - strip[i].second) >= d) break;
            d = min(d, dist(strip[i], strip[j]));
        }
    }

    // STEP 8: Return best distance
        return d;
}

double minimal_distance(vector<int> x, vector<int> y) {

    // STEP 1: Build vector of points (x,y)
    vector<pair<int,int>> pts;
    for (int i = 0; i < x.size(); i++)
        pts.push_back({x[i], y[i]});

    // STEP 2: Sort by x-coordinate
    sort(pts.begin(), pts.end());

    // STEP 3: Apply divide & conquer algorithm
    return solve(pts, 0, pts.size() - 1);
}


int main() {
    // STEP 1: Read input
    size_t n;
    cin >> n;
    vector<int> x(n);
    vector<int> y(n);
    for (size_t i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    // STEP 2: Print result with precision
    cout << fixed;
    cout << setprecision(9) << minimal_distance(x, y) << "\n";
}

/*
===============================================================
                PROGRAM EXPLANATION — STEP BY STEP
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
   Given n points on a 2D plane, the goal is to find the minimum
   distance between any pair of points efficiently.

---------------------------------------------------------------
2. HOW THE ALGORITHM WORKS:
---------------------------------------------------------------
   → Uses Divide & Conquer (O(n log n)):

     STEP 1: Sort points by x.

     STEP 2: Recursively compute closest distance in:
             - Left half
             - Right half

     STEP 3: d = min(left, right)

     STEP 4: Build "strip" — points within distance < d of middle line.

     STEP 5: Sort strip by y-coordinate.

     STEP 6: Compare each point with next ~6 points (geometric property).

     STEP 7: Final answer is the minimum distance found.

---------------------------------------------------------------
3. EXAMPLE:
---------------------------------------------------------------
   Points:
       (0,0), (3,4), (2,1), (7,7)

   Sorted:
       (0,0), (2,1), (3,4), (7,7)

   Left half → min = 1 distance between (0,0) & (2,1)
   Right half → min = distance between (7,7) only

   Strip includes points close to x = 3

   Final answer ≈ 1.4142

---------------------------------------------------------------
4. OUTPUT:
---------------------------------------------------------------
   A floating-point value with 9 decimal digits showing the smallest
   distance between two points.

---------------------------------------------------------------
5. COMPLEXITY:
---------------------------------------------------------------
   Time  : O(n log n)
   Space : O(n)

===============================================================
*/
