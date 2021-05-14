#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

int n, m, a[N], b[N], dp[N][N][2][2];

void maximize (int &x, int y) {
    x = max(x, y);
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++) scanf("%d", &b[i]);
    memset(dp, -0x3f, sizeof(dp));
    for (int i = 0; i <= n; i++) dp[i][0][0][0] = 0;
    for (int i = 0; i <= m; i++) dp[0][i][0][0] = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 2; l++) {
                    if (dp[i][j][k][l] > -1e9) {
                        if (i < n && j < m) {
                            if (a[i + 1] == b[j + 1]) {
                                if (!k && !l) maximize(dp[i + 1][j + 1][1][1], dp[i][j][k][l] + 1);
                                else {
                                    maximize(dp[i + 1][j][0][l], dp[i][j][k][l]);
                                    maximize(dp[i][j + 1][k][0], dp[i][j][k][l]);
                                }
                            }
                            else {
                                maximize(dp[i + 1][j][0][l], dp[i][j][k][l]);
                                maximize(dp[i][j + 1][k][0], dp[i][j][k][l]);
                            }
                        }
                        else {
                            if (i < n) maximize(dp[i + 1][j][0][l], dp[i][j][k][l]);
                            if (j < m) maximize(dp[i][j + 1][k][0], dp[i][j][k][l]);
                        }
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) maximize(ans, dp[n][m][i][j]);
    printf("%d", ans);
    return 0;
}
