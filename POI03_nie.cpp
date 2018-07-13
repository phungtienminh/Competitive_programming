#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 105;
int dp[N][8][8], ways[N][8][8], n, a[N];

signed main(){
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);

    memset(dp, 0, sizeof(dp));
    memset(ways, 0, sizeof(ways));

    for (int i = 0; i < 8; i++) {
        if (a[1] && (i & (1LL << (a[1] - 1)))) continue;

        dp[1][i][0] = __builtin_popcountll(i);
        ways[1][i][0] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 8; j++) {
            for (int l = 0; l < 8; l++) {
                if (ways[i][j][l]) {
                    for (int k = 0; k < 8; k++) {
                        if (a[i + 1] && (k & (1LL << (a[i + 1] - 1)))) continue;

                        if ((j & 4) && (k & 1)) continue;
                        if ((j & 1) && (k & 4)) continue;
                        if (i > 1 && (l & 2) && ((k & 1) || (k & 4))) continue;
                        if (i > 1 && (k & 2) && ((l & 1) || (l & 4))) continue;

                        if (dp[i][j][l] > dp[i + 1][k][j] - __builtin_popcountll(k)) {
                            dp[i + 1][k][j] = dp[i][j][l] + __builtin_popcountll(k);
                            ways[i + 1][k][j] = ways[i][j][l];
                        }
                        else if (dp[i][j][l] == dp[i + 1][k][j] - __builtin_popcountll(k)) {
                            ways[i + 1][k][j] += ways[i][j][l];
                        }
                    }
                }
            }
        }
    }

    int ans = 0;
    int res = 0;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            ans = max(ans, dp[n][i][j]);

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (dp[n][i][j] == ans) res += ways[n][i][j];

    printf("%lld %lld\n", ans, res);
    /*for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 8; j++) {
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 8; j++) {
            cout << ways[i][j] << " ";
        }
        cout << "\n";
    }*/
    return 0;
}
