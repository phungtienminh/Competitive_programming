#include <bits/stdc++.h>

using namespace std;

const int N = 405;

int n, m, a[N], f[N][N], pref[N], dp[N][N];

int main(){
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], pref[i] = pref[i - 1] + a[i];
    for (int i = 1; i <= n; i++) {
        f[i][i] = a[i];
        for (int j = i + 1; j <= n; j++) {
            f[i][j] = max(f[i][j - 1], a[j]);
        }
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) dp[i][0] = f[1][i] * i - pref[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < i; k++) {
                dp[i][j] = min(dp[i][j], dp[k][j - 1] + f[k + 1][i] * (i - k) - pref[i] + pref[k]);
            }
        }
    }

    int ans = (int)1e9;
    for (int i = 0; i <= m; i++) ans = min(ans, dp[n][i]);
    cout << ans << "\n";
    return 0;
}
