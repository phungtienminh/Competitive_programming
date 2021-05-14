#include <bits/stdc++.h>

using namespace std;

const int N = 505;
const int mod = 30011;
const int maxn = 124751;

int n, k, dp[2][maxn], pref[2][maxn];
//DP(n, k) = sum of DP(n - 1, k - i) where i from 0 to n - 1.
//DP(*, 0) = 1
//DP(0, *) = 0

void input(){
    scanf("%d %d", &n, &k);
}

void add (int &x, int y) {
    x = (x + y) % mod;
}

void solve(){
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    int p = 1;
    int q = 0;

    if (k > n * (n - 1) / 4) k = n * (n - 1) / 2 - k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            dp[p][j] = 0;
            if (j == 0) pref[q][j] = dp[q][j];
            else pref[q][j] = (pref[q][j - 1] + dp[q][j]) % mod;

            add(dp[p][j], pref[q][j] - (j > (i - 1) ? pref[q][j - (i - 1) - 1] : 0));
        }

        p ^= 1;
        q ^= 1;
    }

    if (dp[q][k] < 0) dp[q][k] += mod;
    printf("%d", dp[q][k]);
}

int main(){
    input();
    solve();
    return 0;
}
