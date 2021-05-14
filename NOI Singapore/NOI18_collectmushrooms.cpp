#include <bits/stdc++.h>

using namespace std;

int n, m, d, k;
vector <vector <int> > f;
vector <vector <char> > a;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> d >> k;
    a.assign(n + 5, vector <char>(m + 5, '#')); f.assign(n + 5, vector <int>(m + 5, 0));
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == 'S') {
                int x = i - d, y = j - d, x2 = i + d, y2 = j + d;
                x = max(x, 1); y = max(y, 1); x2 = min(x2, n); y2 = min(y2, m);
                f[x][y]++; f[x2 + 1][y]--; f[x][y2 + 1]--; f[x2 + 1][y2 + 1]++;
            }
        }
    }

    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) f[i][j] += f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1];

    int ans = 0;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (a[i][j] == 'M' && f[i][j] >= k) ans++;
    cout << ans;
    return 0;
}
