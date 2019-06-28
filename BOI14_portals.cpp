#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int n, m, d[N][N], nxt[N][N][4], f[N][N];
char a[N][N];
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

bool in (int x, int y) {
    return x >= 0 && x <= n + 1 && y >= 0 && y <= m + 1;
}

bool in2 (int x, int y) {
    return x >= 0 && x <= n + 1 && y >= 0 && y <= m + 1 && a[x][y] != '#';
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i <= n + 1; i++) for (int j = 0; j <= m + 1; j++) if (i == 0 || i == n + 1 || j == 0 || j == m + 1) a[i][j] = '#';
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j];
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            if (a[i][j] == '#') nxt[i][j][0] = j;
            else nxt[i][j][0] = nxt[i][j - 1][0];
        }

        for (int j = m + 1; j >= 0; j--) {
            if (a[i][j] == '#') nxt[i][j][2] = j;
            else nxt[i][j][2] = nxt[i][j + 1][2];
        }
    }

    for (int j = 0; j <= m + 1; j++) {
        for (int i = 0; i <= n + 1; i++) {
            if (a[i][j] == '#') nxt[i][j][1] = i;
            else nxt[i][j][1] = nxt[i - 1][j][1];
        }

        for (int i = n + 1; i >= 0; i--) {
            if (a[i][j] == '#') nxt[i][j][3] = i;
            else nxt[i][j][3] = nxt[i + 1][j][3];
        }
    }

    memset(f, 0x3f, sizeof(f));
    queue <pair <int, int> > q;
    for (int i = 0; i <= n + 1; i++) for (int j = 0; j <= m + 1; j++) if (a[i][j] == '#') f[i][j] = 0, q.push({i, j});
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second; q.pop();
        for (int i = 0; i < 4; i++) {
            if (in(x + dx[i], y + dy[i]) && f[x + dx[i]][y + dy[i]] > f[x][y] + 1) {
                f[x + dx[i]][y + dy[i]] = f[x][y] + 1;
                q.push({x + dx[i], y + dy[i]});
            }
        }
    }

    memset(d, 0x3f, sizeof(d));
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (a[i][j] == 'S') d[i][j] = 0, q.push({i, j});
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second; q.pop();
        for (int i = 0; i < 4; i++) {
            if (in2(x + dx[i], y + dy[i]) && d[x + dx[i]][y + dy[i]] > d[x][y] + 1) {
                d[x + dx[i]][y + dy[i]] = d[x][y] + 1;
                q.push({x + dx[i], y + dy[i]});
            }
        }

        for (int i = 0; i <= 2; i += 2) {
            int ny = nxt[x][y][i];
            if (y < ny) {
                if (in2(x, ny - 1) && d[x][ny - 1] > d[x][y] + f[x][y]) {
                    d[x][ny - 1] = d[x][y] + f[x][y];
                    q.push({x, ny - 1});
                }
            }
            else {
                if (in2(x, ny + 1) && d[x][ny + 1] > d[x][y] + f[x][y]) {
                    d[x][ny + 1] = d[x][y] + f[x][y];
                    q.push({x, ny + 1});
                }
            }
        }

        for (int i = 1; i <= 3; i += 2) {
            int nx = nxt[x][y][i];
            if (x < nx) {
                if (in2(nx - 1, y) && d[nx - 1][y] > d[x][y] + f[x][y]) {
                    d[nx - 1][y] = d[x][y] + f[x][y];
                    q.push({nx - 1, y});
                }
            }
            else {
                if (in2(nx + 1, y) && d[nx + 1][y] > d[x][y] + f[x][y]) {
                    d[nx + 1][y] = d[x][y] + f[x][y];
                    q.push({nx + 1, y});
                }
            }
        }
    }

    int ans = -1;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (a[i][j] == 'C') ans = d[i][j];
    cout << ans;
    return 0;
}
