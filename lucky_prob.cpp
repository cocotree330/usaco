#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// get number of overlap between 
long long g(long long l1, long long r1, long long l2, long long r2) {
    long long max_l = max(l1, l2);
    long long min_r = min(r1, r2);
    if (max_l <= min_r) {
        return min_r - max_l + 1;
    }
    return 0;
}

int main() {
    long long pl, pr, vl, vr;
    int k;
    if (!(cin >> pl >> pr >> vl >> vr >> k)) return 0;

    vector<long long> lucky;
    lucky.push_back(4);
    lucky.push_back(7);
    
    size_t head = 0;
    while (head < lucky.size()) {
        long long curr = lucky[head++];
        if (curr <= 100000000) {
            lucky.push_back(curr * 10 + 4);
            lucky.push_back(curr * 10 + 7);
        }
    }
    
    sort(lucky.begin(), lucky.end());
    
    lucky.insert(lucky.begin(), 0); 
    lucky.push_back(2000000005);

    long long favorable_pairs = 0;
    int total_lucky = lucky.size();
    
    for (int i = 1; i + k - 1 < total_lucky - 1; i++) {
        int j = i + k - 1;
        
        long long left_min = lucky[i - 1] + 1;
        long long left_max = lucky[i];
        
        long long right_min = lucky[j];
        long long right_max = lucky[j + 1] - 1;
        
        long long p_left_v_right = g(left_min, left_max, pl, pr) * g(right_min, right_max, vl, vr);
        
        long long v_left_p_right = g(left_min, left_max, vl, vr) * g(right_min, right_max, pl, pr);

        favorable_pairs += p_left_v_right + v_left_p_right;

        // edge case if k = 1
        if (k == 1) {
            if (pl <= lucky[i] && lucky[i] <= pr && vl <= lucky[i] && lucky[i] <= vr) {
                favorable_pairs--;
            }
        }
    }

    long long total_pairs = (pr - pl + 1) * (vr - vl + 1);
    double probability = (double)favorable_pairs / total_pairs;

    cout << fixed << setprecision(12) << probability << "\n";

    return 0;
}
