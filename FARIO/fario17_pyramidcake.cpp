#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

int n, m, a[N][N], col[N][N], Min[N][N];
long long dp[N][N];

int main(){
    #ifdef Futymy
        //freopen("all.inp", "r", stdin);
    #endif // Futymy
    //Read Input.
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);

    //Construct Min.
    memset(Min, 0x3f, sizeof(Min));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            Min[i][j] = min(Min[i - 1][j], Min[i][j - 1]);
            Min[i][j] = min(Min[i][j], a[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = max(dp[i - 1][j] + j * Min[i][j], dp[i][j - 1] + i * Min[i][j]);
        }
    }

    //Solve
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans = max(ans, dp[i][j]);
        }
    }
    printf("%lld", ans);
    return 0;
}
