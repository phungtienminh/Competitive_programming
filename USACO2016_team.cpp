#include <bits/stdc++.h>

using namespace std;

const int N = 1005;
const int mod = 1e9 + 9;

int n, m, p, a[N], b[N], dp[15][N][N];

void add (int &x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}

void sub (int &x, int y) {
    x -= y;
    if (x < 0) x += mod;
}

int main(){
    #ifndef Futymy
        freopen("team.in", "r", stdin);
        freopen("team.out", "w", stdout);
    #endif // Futymy

    scanf("%d %d %d", &n, &m, &p);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++) scanf("%d", &b[i]);
    sort(a + 1, a + n + 1); sort(b + 1, b + m + 1);
    dp[0][0][0] = 1;

    for (int k = 0; k <= p; k++) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i) add(dp[k][i][j], dp[k][i - 1][j]);
                if (j) add(dp[k][i][j], dp[k][i][j - 1]);
                if (i && j) sub(dp[k][i][j], dp[k][i - 1][j - 1]);
                if (k && i && j && a[i] > b[j]) add(dp[k][i][j], dp[k - 1][i - 1][j - 1]);
            }
        }
    }

    printf("%d", dp[p][n][m]);
    return 0;
}
