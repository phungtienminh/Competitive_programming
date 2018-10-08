#include <bits/stdc++.h>

using namespace std;

const int N = 305;

void minimize (int &x, int y) {
    x = min(x, y);
}

int dp[N][N][N][2], n, m, a[N];

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    sort(a, a + n + 1);

    int ans = 0;
    int pos = lower_bound(a, a + n + 1, 0) - a;
    memset(dp, 0x3f, sizeof(dp));
    for (int j = 0; j <= n; j++) for (int k = 0; k <= n; k++) dp[0][j][k][0] = dp[0][j][k][1] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = j; k <= n; k++) {
                if (j) minimize(dp[i][j][k][0], dp[i - 1][j - 1][k][0] + i * (a[j] - a[j - 1]));
                if (k < n) minimize(dp[i][j][k][0], dp[i - 1][j][k + 1][1] + i * (a[k + 1] - a[j]));
                if (k < n) minimize(dp[i][j][k][1], dp[i - 1][j][k + 1][1] + i * (a[k + 1] - a[k]));
                if (j) minimize(dp[i][j][k][1], dp[i - 1][j - 1][k][0] + i * (a[k] - a[j - 1]));
            }
        }

        ans = max(ans, i * m - dp[i][pos][pos][0]);
    }

    printf("%d", ans);
    return 0;
}
