#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int dp[N][5], n, a[N], b[N];

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d %d", &a[i], &b[i]);
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            if (dp[i][j]) {
                for (int k = a[i + 1]; k <= b[i + 1]; k++) {
                    dp[(i + 1)][(j + k) % 5] += dp[i][j];
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < 5; i++) {
        int fin = i * i * i * i + 2 * i * i;
        fin %= 5;
        ans += (fin + 1) * dp[n][i];
    }

    printf("%d", ans);
    return 0;
}
