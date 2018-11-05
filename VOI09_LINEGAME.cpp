#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n, a[N];
long long dp[N][2];

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    memset(dp, -0x3f, sizeof(dp)); dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j) dp[i][j] = max(dp[i][j], dp[i - 1][j ^ 1] + a[i]);
            else dp[i][j] = max(dp[i][j], dp[i - 1][j ^ 1] - a[i]);
        }
    }

    printf("%lld", max(dp[n][0], dp[n][1]));
    return 0;
}
