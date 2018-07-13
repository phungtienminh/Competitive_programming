#include <bits/stdc++.h>

#define int long long

using namespace std;

int comb[3][3], t, x, y;

int C (int n, int k) {
    if (n == 0) return (k == 0);
    return (C(n / 3, k / 3) * comb[n % 3][k % 3]) % 3;
}

signed main(){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j > i) comb[i][j] = 0;
            else if (i == 0 || j == 0 || i == j) comb[i][j] = 1;
            else comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % 3;
        }
    }

    scanf("%lld", &t);
    while (t--) {
        scanf("%lld %lld", &x, &y);
        int ans = C(2 * x, y);
        if (y & 1) ans = 3 - ans;
        printf("%lld\n", ans % 3);
    }
    return 0;
}
