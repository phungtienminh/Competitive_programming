#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;

int n, a[4][N], dp[N][2];

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d %d %d", &a[1][i], &a[2][i], &a[3][i]);
    memset(dp, -0x3f, sizeof(dp)); dp[1][0] = 0;
    for (int i = 1; i < n; i++) {
        dp[i + 1][0] = max(dp[i + 1][0], dp[i][0]);
        dp[i + 1][0] = max(dp[i + 1][0], dp[i][1]);
        dp[i + 1][1] = max(dp[i + 1][1], dp[i][0] + a[1][i] + a[1][i + 1] + a[2][i] + a[2][i + 1]);
        dp[i + 1][1] = max(dp[i + 1][1], dp[i][0] + a[2][i] + a[2][i + 1] + a[3][i] + a[3][i + 1]);
    }

    printf("%d", max(dp[n][0], dp[n][1]));
    return 0;
}
