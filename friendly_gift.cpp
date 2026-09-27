#include <bits/stdc++.h>
using namespace std;

int memo[1000009];
int prefix[10][1000009];

int f(int n) {
    int ans = 1;
    while (n >= 1) {
        if (n % 10 != 0) {
            ans *= n % 10;
        }
        n /= 10;
    }
    return ans;
}

int g(int n) {
    if (n < 10) {
        memo[n] = n;
        return n;
    }
    else {
        if (memo[n] != 0){
            return memo[n];
        }
        else {
            int i = g(f(n));
            memo[n] = i;
            return i;
        }
    }
}

int main()
{
    int total[9];
    for (int i = 1; i <= 1e6; i++) {
        int temp = g(i);
        total[temp]++;
        for(int j = 1; j <= 9; j++){
            prefix[j][i] = total[j];
        }
    }

    int cases;
    cin >> cases;

    for (int c = 0; c < cases; c++) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << prefix[k][r] - prefix[k][l - 1] << endl;
    }

    return 0;
}