#include <bits/stdc++.h>

using namespace std;

const int N = 105;

int n, m, a, b, len, A[N][N], dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0};
long long dp[2][N][N];

bool inside (int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

void maximize (long long &x, long long y) {
    x = max(x, y);
}

int main(){
    scanf("%d %d %d %d %d", &n, &m, &a, &b, &len); len /= 2;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &A[i][j]);
    memset(dp, -0x3f, sizeof(dp)); dp[0][a][b] = 0;

    int lim = min(len, n * m);
    for (int i = 0; i < lim + 1; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= m; k++) {
                dp[(i + 1) % 2][j][k] = -1e18 - 2277;
            }
        }

        if (i == lim) break;
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= m; k++) {
                if (dp[i % 2][j][k] > -1e18) {
                    for (int l = 0; l < 4; l++) {
                        if (!inside(j + dx[l], k + dy[l])) continue;
                        maximize(dp[(i + 1) % 2][j + dx[l]][k + dy[l]], dp[i % 2][j][k] + A[j + dx[l]][k + dy[l]]);
                    }
                }
            }
        }
    }

    if (lim == len) {
        long long ans = 0;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) ans = max(ans, dp[lim % 2][i][j] * 2 - A[i][j]);
        printf("%lld", ans);
        return 0;
    }

    long long ans = 0, temp = (len - n * m) * 2;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            long long res = dp[lim % 2][i][j] * 2 - A[i][j];
            long long cur = 0;
            for (int k = 0; k < 4; k++) {
                if (!inside(i + dx[k], j + dy[k])) continue;
                cur = max(cur, (long long)A[i + dx[k]][j + dy[k]]);
            }

            cur += A[i][j];
            cur = cur * (temp / 2);
            ans = max(ans, res + cur);
        }
    }

    printf("%lld", ans);
    return 0;
}
/*
2 2 1 1 10
0 5
5 10
*/
