#include <bits/stdc++.h>

using namespace std;

const int N = 305;

int n, k, a[N];
long long dp[N][N][N];

long long solve (int l, int r, int k) {
    if (k == 0) return dp[l][r][k] = 0;
    if (r - l + 1 < 2 * k) return (long long)-1e18;
    if (l >= r) {
        if (k == 0) return 0;
        return (long long)-1e18;
    }

    long long &ans = dp[l][r][k];
    if (ans > -1e18) return ans;
    ans = max(ans, solve(l, r - 2, k - 1) + abs(a[r - 1] - a[r]));
    ans = max(ans, solve(l + 2, r, k - 1) + abs(a[l] - a[l + 1]));
    ans = max(ans, solve(l + 1, r - 1, k - 1) + abs(a[l] - a[r]));
    ans = max(ans, solve(l + 1, r, k));
    ans = max(ans, solve(l, r - 1, k));
    return ans;
}

int main(){
    freopen("bonus.inp", "r", stdin);
    freopen("bonus.out", "w", stdout);
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    memset(dp, -0x3f, sizeof(dp));
    printf("%lld\n", solve(1, n, k));
    return 0;
}
