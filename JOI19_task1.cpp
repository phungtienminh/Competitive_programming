#include <bits/stdc++.h>

using namespace std;

const int N = 3005;

int n, m, row[N][N], col[N][N];
char a[N][N];
long long ans = 0;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) row[i][j] = row[i][j - 1] + (a[i][j] == 'O');
    for (int i = 1; i <= m; i++) for (int j = 1; j <= n; j++) col[i][j] = col[i][j - 1] + (a[j][i] == 'I');
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == 'J') ans += 1LL * (row[i][m] - row[i][j]) * (col[j][n] - col[j][i]);
        }
    }

    cout << ans;
    return 0;
}
