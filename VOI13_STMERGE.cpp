#include <bits/stdc++.h>

using namespace std;

const int N = 2005;

int t, n, m, a[N][N];
long long f[N][N], g[N][N];

void solve(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
    memset(f, 0x3f, sizeof(f)); memset(g, 0x3f, sizeof(g));
    f[0][0] = g[0][0] = 0;
    for (int i = 1; i <= n + m; i++) {
        for (int j = 1; j <= n + m; j++) {
            f[i][j] = f[i - 1][j - 1];
            g[i][j] = g[i - 1][j - 1];
            if (i >= j && i - j <= m) f[i][j] = min(f[i][j], g[i - 1][i - j] + a[j][i - j]);
            if (i >= j && i - j <= n) g[i][j] = min(g[i][j], f[i - 1][i - j] + a[i - j][j]);
        }
    }

    printf("%d\n", min(f[m + n][n], g[m + n][m]));
}

int main(){
    scanf("%d", &t);
    while (t--) solve();
    return 0;
}
