#include <bits/stdc++.h>

using namespace std;

const int N = 505;

int dp[N][N], n, m, p, a[N], b[N];

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i <= m; i++) cin >> b[i];

    memset(dp, -0x3f, sizeof(dp)); dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= p; j++) {
            if (dp[i][j] > -1e9) {
                int lim = min(p - j, m - a[i + 1]);
                for (int k = 0; k <= lim; k++) dp[i + 1][j + k] = max(dp[i + 1][j + k], dp[i][j] + b[a[i + 1] + k]);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= p; i++) ans = max(ans, dp[n][i]);
    cout << ans;
    return 0;
}
