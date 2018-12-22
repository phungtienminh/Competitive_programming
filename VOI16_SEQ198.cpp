#include <bits/stdc++.h>

using namespace std;

const int N = 2e3 + 5;
const int Mask = (1 << 1) + (1 << 8) + (1 << 9);

int n, a[N], dp[N][1024];

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]); a[0] = -1e9;
    sort(a + 1, a + n + 1); memset(dp, -0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < 1024; mask++) {
            if (dp[i][mask] > -1e9) {
                int val = a[i + 1] - a[i];
                int nmask = val >= 10 ? 0 : ((mask << val) & 1023);
                dp[i + 1][nmask] = max(dp[i + 1][nmask], dp[i][mask]);
                if ((nmask & Mask) == 0) dp[i + 1][nmask | 1] = max(dp[i + 1][nmask | 1], dp[i][mask] + 1);
            }
        }
    }

    int ans = 0;
    for (int mask = 0; mask < 1024; mask++) ans = max(ans, dp[n][mask]);
    printf("%d", n - ans);
    return 0;
}
