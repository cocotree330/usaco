/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
    int cases;
    cin >> cases;
    
    for (int c = 0; c < cases; c++) {
        long long ans;
        ans = 0;
        map<int, int> cnt1, cnt2, cnt3, cnt4;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            ans += cnt1[x - y];
            //cout << "a " << ans << endl;
            cnt1[x - y] += 1;
            
            ans += cnt2[x + y];
            cnt2[x+y] += 1;
            
            ans += cnt3[x];
            cnt3[x] += 1;
            
            ans += cnt4[y];
            cnt4[y] += 1;
        }
        cout << ans * 2 << endl;
    }

    return 0;
}