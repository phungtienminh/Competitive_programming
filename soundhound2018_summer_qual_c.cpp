#include <bits/stdc++.h>

using namespace std;

int n, m, d;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> d;

    if (d == 0) cout << fixed << setprecision(9) << (double)(m - 1) / (double)n;
    else cout << fixed << setprecision(9) << (double)(1LL * 2 * (m - 1) * (n - d)) / (double)(1LL * n * n);
    return 0;
}

//d = 0 => (m - 1) / n
//n = 5, m = 4, d = 1 => 24/25
//n = 5, m = 4, d = 2 => 18/25
//n = 5, m = 4, d = 3 => 12/25
//n = 5, m = 4, d = 4 => 6/25
//n = 5, m = 3, d = 1 => 16/25
//n = 5, m = 3, d = 2 => 12/25
//n = 5, m = 3, d = 3 => 8/25
//n = 5, m = 3, d = 4 => 4/25
//n = 5, m = 2, d = 1 => 8/25
//n = 5, m = 2, d = 2 => 6/25
//n = 5, m = 2, d = 3 => 4/25
//n = 5, m = 2, d = 4 => 2/25
//n = 6, m = 4, d = 1 => 5/6
//2(m - 1)(n - d) / n ^ 2
