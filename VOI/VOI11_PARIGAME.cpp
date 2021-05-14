#include <bits/stdc++.h>

using namespace std;

const int N = 505;

int t, n, a[N][N];
long long row[N][N], col[N][N];
bool dp[N][N];

int main(){
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n); memset(row, 0, sizeof(row)); memset(col, 0, sizeof(col)); memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) row[i][j] = row[i][j - 1] + a[i][j], col[j][i] = col[j][i - 1] + a[i][j];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (col[j][i] % 2 == 0) dp[i][j] |= (!dp[i][j - 1]);
                if (row[i][j] % 2 == 0) dp[i][j] |= (!dp[i - 1][j]);
            }
        }

        puts(dp[n][n] ? "YES" : "NO");
    }
    return 0;
}
