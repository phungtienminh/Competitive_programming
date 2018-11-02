#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

int n, a[5][N], dp[N][16], mask[N][16];
bool notneg = false;

bool ok (int k) {
    return k == 0 || k == 1 || k == 2 || k == 4 || k == 5 || k == 8 || k == 9 || k == 10;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= 4; i++) for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]), notneg |= (a[i][j] > 0);
    if (!notneg) {
        int ans = -1e9;
        for (int i = 1; i <= 4; i++) for (int j = 1; j <= n; j++) ans = max(ans, a[i][j]);
        printf("%d", ans);
        return 0;
    }

    for (int j = 1; j <= n; j++) {
        for (int i = 0; i < (1 << 4); i++) {
            int sum = 0;
            for (int k = 0; k < 4; k++) {
                if (i & (1 << k)) sum += a[k + 1][j];
            }

            mask[j][i] = sum;
        }
    }

    memset(dp, -0x3f, sizeof(dp)); dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << 4); j++) {
            if (dp[i][j] > -1e9) {
                for (int k = 0; k < (1 << 4); k++) {
                    if ((j & k) == 0 && ok(k)) {
                        dp[i + 1][k] = max(dp[i + 1][k], dp[i][j] + mask[i + 1][k]);
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < 16; i++) ans = max(ans, dp[n][i]);
    printf("%d", ans);
    return 0;
}
