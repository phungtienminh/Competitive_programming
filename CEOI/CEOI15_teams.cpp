#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;
const int mod = 1e6 + 7;

int n, a[N], f[N];
vector <int> dp, dp2;

int readInt(){
    char c;
    int ans = 0;
    while (1) {
        c = getchar();
        if (c == ' ' || c == '\n') return ans;
        ans = (ans << 3) + (ans << 1) + (c - '0');
    }
}

int main(){
    n = readInt();
    for (int i = 1; i <= n; i++) a[i] = readInt(), f[i] = max(f[i - 1], a[i]);
    dp.assign(n + 2, 0); dp2.assign(n + 2, 0);
    int ans = 0;
    for (int i = 0; i <= n + 1; i++) dp[i] = 1;
    ans += a[n];
    for (int i = 1; i < n; i++) {
        int val = min(n, f[n - i - 1] + n - i);
        for (int j = val; j >= 1; j--) {
            dp2[j] = 1LL * dp[j] * j % mod + dp[j + 1];
            if (dp2[j] >= mod) dp2[j] -= mod;
        }
        //cout << ans << " " << f[n - i - 1] << " " << dp2[f[n - i - 1]] << "\n";
        ans += 1LL * (a[n - i] - 1) * dp2[f[n - i - 1]] % mod;
        if (ans >= mod) ans -= mod;
        dp.swap(dp2);
    }

    if (ans >= mod) ans -= mod;
    printf("%d", ans);
    return 0;
}
