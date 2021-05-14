#include <bits/stdc++.h>

using namespace std;

const int N = 2801;
const int K = 11;

int dp[N][K], pref[N][N], a[N];

signed main(){
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pref[i][j] = abs(a[i] - a[j]);
            if (j > 1) pref[i][j] += pref[i][j - 1];
        }
    }

    for (int i = 0; i <= n; i++) pref[i][0] = pref[0][i] = 0;

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < i; k++) {
                if (dp[k][j - 1] < 1e9) {
                    dp[i][j] = min(dp[i][j], dp[k][j - 1] + pref[(k + 1 + i) / 2][i] - pref[(k + 1 + i) / 2][k]);
                }
            }
        }
    }
//
    printf("%d", dp[n][m]);
    return 0;
}
