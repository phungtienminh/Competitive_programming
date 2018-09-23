#include <bits/stdc++.h>

using namespace std;

const int N = 105;

class Data {
public:
    int val, x, y;

    Data (int val, int x, int y): val(val), x(x), y(y) {}
    bool operator < (const Data &other) const {
        return val > other.val;
    }
};

int n, m, a[N][N], f[N][N];
priority_queue <Data, vector <Data> > pq;
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

bool onEdge (int x, int y) {
    return x == 1 || x == n || y == 1 || y == m;
}

bool inside (int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

bool check (int x, int y) {
    if (f[x][y] != -1) return false;
    bool ok = false;
    for (int i = 0; i < 4; i++) if (inside(x + dx[i], y + dy[i]) && f[x + dx[i]][y + dy[i]] != -1) ok = true;
    if (onEdge(x, y) || ok) return true;
    return false;
}

void dfs (int x, int y, int curx, int cury) {
    f[x][y] = a[curx][cury];
    for (int i = 0; i < 4; i++) if (inside(x + dx[i], y + dy[i]) && a[x + dx[i]][y + dy[i]] <= a[curx][cury] && f[x + dx[i]][y + dy[i]] == -1) dfs(x + dx[i], y + dy[i], curx, cury);
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    memset(f, -1, sizeof(f));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            pq.push(Data(a[i][j], i, j));
        }
    }

    while (!pq.empty()) {
        Data cur = pq.top(); pq.pop();
        if (check(cur.x, cur.y)) dfs(cur.x, cur.y, cur.x, cur.y);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans += f[i][j] - a[i][j];
        }
    }

    printf("%d", ans);
    return 0;
}
