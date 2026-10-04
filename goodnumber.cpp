/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

long long solve(long long n) {
    // Convert n to base 3
    string s;

    while (n > 0) {
        s += char('0' + n % 3);
        n /= 3;
    }

    reverse(s.begin(), s.end());
    
    bool found = false;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '2') {
            for (int j = i; j < (int)s.size(); j++) {
                s[j] = '0';
            }

            int j = i - 1;

            while (j >= 0 && s[j] == '1') {
                s[j] = '0';
                j--;
            }

            if (j >= 0) {
                s[j] = '1';
            } else {
                s = '1' + s;
            }
            found = true;
            break;
        }
    }

    if (!found) {
        int i = (int)s.size() - 1;

        while (i >= 0 && s[i] == '1') {
            s[i] = '0';
            i--;
        }

        if (i >= 0) {
            s[i] = '1';
        } else {
            s = '1' + s;
        }
    }

    long long ans = 0;

    for (char c : s) {
        ans = ans * 3 + (c - '0');
    }

    return ans;
}


int main() {
    int q;
    cin >> q;
    for (int c = 0; c < q; c++) {
        long long a;
        cin >> a;
        long long ans = solve(a);
        cout << ans << endl;
    }
}