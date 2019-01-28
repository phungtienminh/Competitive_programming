#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int n, m, f[N][N], g[N][N], row[N][N], col[N][N];
char a[N][N];
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

int calc (int x, int y, int dir) {
    int ans = 1;
    while (1) {
        if (a[x][y] == '\\') {
            if (dir == 1) dir--;
            else if (dir == 0) dir++;
            else if (dir == 2) dir++;
            else dir--;
        }
        else if (a[x][y] == '/') {
            if (dir == 0) dir = 3;
            else if (dir == 1) dir = 2;
            else if (dir == 2) dir = 1;
            else dir = 0;
        }

        x += dx[dir]; y += dy[dir];
        if (x < 1 || x > n || y < 1 || y > m) return ans;
        ans++;
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) row[i][j] = row[i][j - 1] + (a[i][j] == '.');
    for (int i = 1; i <= m; i++) for (int j = 1; j <= n; j++) col[i][j] = col[i][j - 1] + (a[j][i] == '.');
    for (int i = 1; i <= n; i++) {
        f[i][m + 1] = m + 1;
        for (int j = m; j >= 1; j--) {
            if (a[i][j] == '\\') f[i][j] = j;
            else f[i][j] = f[i][j + 1];
        }
    }

    for (int i = 1; i <= m; i++) {
        g[i][n + 1] = n + 1;
        for (int j = n; j >= 1; j--) {
            if (a[i][j] == '\\') g[i][j] = j;
            else g[i][j] = g[i][j + 1];
        }
    }

    int ans = 0;
    ans = max(ans, calc(1, 1, 2)); ans = max(ans, calc(1, 1, 3));
    ans = max(ans, calc(1, n, 0)); ans = max(ans, calc(1, n, 3));
    ans = max(ans, calc(n, 1, 1)); ans = max(ans, calc(n, 1, 2));
    ans = max(ans, calc(n, n, 0)); ans = max(ans, calc(n, n, 1));
    for (int i = 2; i <= m - 1; i++) ans = max(ans, calc(1, i, 3)), ans = max(ans, calc(n, i, 1));
    for (int i = 2; i <= n - 1; i++) ans = max(ans, calc(i, 1, 2)), ans = max(ans, calc(i, n, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == '/') {
                int nxtcol = f[i][j], nxtrow = g[j][i];
                if (nxtcol > m || nxtrow > n || a[nxtrow][nxtcol] != '/') continue;
                if (row[i][nxtcol] - row[i][j - 1] != nxtcol - (j - 1) - 2) continue;
                if (col[j][nxtrow] - col[j][i - 1] != nxtrow - (i - 1) - 2) continue;
                if (row[nxtrow][nxtcol] - row[nxtrow][j - 1] != nxtcol - (j - 1) - 2) continue;
                if (col[nxtcol][nxtrow] - col[nxtcol][i - 1] != nxtrow - (i - 1) - 2) continue;
                ans = max(ans, (nxtrow - i + 1) * (nxtcol - j + 1));
            }
        }
    }

    cout << ans;
    return 0;
}
