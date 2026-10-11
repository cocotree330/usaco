#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long c(long long X_start, long long X_end, long long Y_start, long long Y_end) {
    if (X_start > X_end || Y_start > Y_end) return 0;
    
    // if the ranges don't overlap and x is entirely to the left of y
    if (X_end < Y_start) {
        return (X_end - X_start + 1) * (Y_end - Y_start + 1);
    }
    // if x is entirely to the right of y (impossible for x <= y)
    if (X_start > Y_end) {
        return 0;
    }

    long long count = 0;
    // split into x < y_start (independent choices)
    long long left1 = X_start;
    long long right1 = min(X_end, Y_start - 1);
    if (left1 <= right1) {
        count += (right1 - left1 + 1) * (Y_end - Y_start + 1);
    }

    // overlapping part where x >= y_start
    long long left2 = max(X_start, Y_start);
    long long right2 = min(X_end, Y_end);
    if (left2 <= right2) {
        long long n = right2 - left2 + 1;
        long long sum_X = (left2 + right2) * n / 2;
        count += n * (Y_end + 1) - sum_X;
    }
    return count;
}

long long solve(const vector<long long>& S, long long A, long long B, long long C, long long D, int p) {
    int k = S.size();
    long long total_pairs = 0;
    long long INF = 2e9 + 7;

    // --- CASE P = 0 ---
    if (p == 0) {
        // for p = 0, no elements can be inside or on the boundaries of the interval.
        // therefore, the entire interval [min(L,R), max(L,R)] must fit inside a single gap.
        for (int i = 0; i <= k; ++i) {
            long long left_elem = (i > 0) ? S[i - 1] : -INF;
            long long right_elem = (i < k) ? S[i] : INF;

            long long gap_min = left_elem + 1;
            long long gap_max = right_elem - 1;

            if (gap_min <= gap_max) {
                // case 1: l <= r
                long long L_start = max(A, gap_min), L_end = min(B, gap_max);
                long long R_start = max(C, gap_min), R_end = min(D, gap_max);
                total_pairs += c(L_start, L_end, R_start, R_end);

                // case 2: r < l (equivalent to r <= l - 1)
                long long R_start2 = max(C, gap_min), R_end2 = min(D, gap_max);
                long long L_start2 = max(A, gap_min), L_end2 = min(B, gap_max);
                total_pairs += c(R_start2, R_end2, L_start2, L_end2);
                
                // subtract where l == r because it was counted in both case 1 and case 2
                long long overlap_start = max(L_start, R_start2);
                long long overlap_end = min(L_end, R_end2);
                if (overlap_start <= overlap_end) {
                    total_pairs -= (overlap_end - overlap_start + 1);
                }
            }
        }
        return total_pairs;
    }

    // --- CASE P > 0 ---
    for (int i = 0; i <= k - p; ++i) {
        long long window_start_val = S[i];
        long long window_end_val = S[i + p - 1];

        long long left_bound = (i > 0) ? S[i - 1] : -INF;
        long long right_bound = (i + p < k) ? S[i + p] : INF;

        // valid ranges for the lower and upper endpoints of the interval
        long long lower_start = left_bound + 1;
        long long lower_end = window_start_val;

        long long upper_start = window_end_val;
        long long upper_end = right_bound - 1;

        // case 1: l is the lower endpoint, r is the upper endpoint (l <= r)
        long long L_start = max(A, lower_start), L_end = min(B, lower_end);
        long long R_start = max(C, upper_start), R_end = min(D, upper_end);
        total_pairs += c(L_start, L_end, R_start, R_end);

        // case 2: r is the lower endpoint, l is the upper endpoint (r < l)
        long long R_start2 = max(C, lower_start), R_end2 = min(D, lower_end);
        long long L_start2 = max(A, upper_start), L_end2 = min(B, upper_end);
        
        // use r < l condition by shifting L_start2 up to ensure strict inequality 
        // to avoid double counting L == R cases (though with p > 0, l == r is impossible anyway)
        total_pairs += c(R_start2, R_end2, L_start2, L_end2);
    }

    return total_pairs;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long pl, pr, vl, vr, k;
    cin >> pl >> pr >> vl >> vr >> k;
    
    vector<long long> l1;
    l1.push_back(4);
    l1.push_back(7);
    vector<long long> l2;
    l2.push_back(4);
    l2.push_back(7);
    
    int high = max(pr, vr);
    bool done = false;
    while (true) {
        for (int i = 0; i < l1.size(); i++) {
            l2.push_back(l1[i] * 10 + 4);
            l2.push_back(l1[i] * 10 + 7);
            if ((l1[i] * 10 + 7) >= high) {
                done = true;
                break;
            }
        }
        if (done) {
            break;
        }
        l1.swap(l2);
    }
    
    float ans = static_cast<float> (solve(l2, pl, pr, vl, vr, k))/((pr - pl + 1) * (vr - vl + 1));
    cout << solve(l2, pl, pr, vl, vr, k) << endl;
    cout << ans << endl;
    cout << ((pr - pl + 1) * (vr - vl + 1));

    return 0;
}
