#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    struct Event {
        int x;      // coordinate of event
        char type;  // 'l' = start, 'r' = end, 'p' = point
        int index;  // index of point in original array
    };

    vector<Event> events;

    // STEP 1: Add segment starts as 'l'
    for (int i = 0; i < starts.size(); i++) {
        events.push_back({starts[i], 'l', -1});
    }

    // STEP 2: Add segment ends as 'r'
    for (int i = 0; i < ends.size(); i++) {
        events.push_back({ends[i], 'r', -1});
    }

    // STEP 3: Add points as 'p' with original index
    for (int i = 0; i < points.size(); i++) {
        events.push_back({points[i], 'p', i});
    }

    // STEP 4: Sort events by coordinate, tie-breaking: 'l' < 'p' < 'r'
    sort(events.begin(), events.end(), [](const Event &a, const Event &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.type < b.type;
    });

    vector<int> cnt(points.size());
    int active = 0; // Number of currently active segments

    // STEP 5: Sweep line: count active segments for each point
    for (auto &e : events) {
        if (e.type == 'l') active++;         // Open segment
        else if (e.type == 'r') active--;    // Close segment
        else cnt[e.index] = active;          // Assign count to point
    }

    // STEP 6: Return results
    return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> cnt(points.size());

    // Brute-force: check each point against each segment
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j < starts.size(); j++) {
            cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
        }
    }
    return cnt;
}

int main() {
    int n, m;
    cin >> n >> m; // Number of segments and points

    vector<int> starts(n), ends(n);
    for (size_t i = 0; i < starts.size(); i++) {
        cin >> starts[i] >> ends[i]; // Input segment start and end
    }

    vector<int> points(m);
    for (size_t i = 0; i < points.size(); i++) {
        cin >> points[i]; // Input points
    }

    // STEP 7: Compute counts using fast solution
    vector<int> cnt = fast_count_segments(starts, ends, points);

    // STEP 8: Print results
    for (size_t i = 0; i < cnt.size(); i++) {
        cout << cnt[i] << ' ';
    }
}

/*
===============================================================
                PROGRAM EXPLANATION — STEP BY STEP
===============================================================

1. PROBLEM GOAL:
---------------------------------------------------------------
   Given n segments and m points on a line, determine how many
   segments cover each point. Need an efficient solution.

---------------------------------------------------------------
2. HOW THE CODE WORKS:
---------------------------------------------------------------
   → Use sweep line algorithm:
       1. Represent segment starts as 'l', ends as 'r', points as 'p'
       2. Sort all events by coordinate, tie-breaking 'l' < 'p' < 'r'
       3. Initialize counter of active segments
       4. Iterate events:
           'l' → increment active counter
           'r' → decrement active counter
           'p' → assign active counter to that point
   → Return array of counts.

---------------------------------------------------------------
3. EXAMPLE:
---------------------------------------------------------------
   Input:
       n=3, m=2
       Segments: [0,5], [-3,2], [7,10]
       Points: 1 6

   Step-by-step:
   - Events sorted: [-3:l, 0:l, 1:p, 2:r, 5:r, 6:p, 7:l, 10:r]
   - Sweep line:
       [-3:l] active=1
       [0:l] active=2
       [1:p] → result[0]=2
       [2:r] active=1
       [5:r] active=0
       [6:p] → result[1]=0
       [7:l] active=1
       [10:r] active=0

   Output: 2 0

---------------------------------------------------------------
4. OUTPUT:
---------------------------------------------------------------
   m integers, each representing number of segments covering
   the corresponding point.

---------------------------------------------------------------
5. COMPLEXITY:
---------------------------------------------------------------
   Time complexity: O((n+m) log(n+m)) due to sorting
   Space complexity: O(n+m) for events and result array

===============================================================
*/
