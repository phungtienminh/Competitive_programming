#include <bits/stdc++.h>

using namespace std;

const int N = 405;

int n, m, f[N][N], l[N], r[N], ans = 0;
char a[N][N];

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) f[i][j] = (a[i][j] == 'X' ? 0 : f[i - 1][j] + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            l[j] = j - 1;
            while (l[j] && f[i][j] <= f[i][l[j]]) l[j] = l[l[j]];
        }

        for (int j = m; j >= 1; j--) {
            r[j] = j + 1;
            while (r[j] <= m && f[i][j] <= f[i][r[j]]) r[j] = r[r[j]];
        }

        for (int j = 1; j <= m; j++) if (a[i][j] == '.') ans = max(ans, 2 * (f[i][j] + r[j] - l[j] - 1) - 1);
    }

    cout << ans;
    return 0;
}
