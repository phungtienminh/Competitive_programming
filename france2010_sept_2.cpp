#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int n, m, e, d[N][N], a[N][N];
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};
queue <pair <int, int> > q;

bool inside (int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m && a[x][y] != 1;
}

int main(){
    scanf("%d %d %d", &n, &m, &e);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
    memset(d, 0x3f, sizeof(d)); d[1][1] = 1; q.push({1, 1});
    vector <pair <int, int> > ans;
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second; q.pop();
        if (d[x][y] && d[x][y] % (e + 1) == 0) ans.push_back({x, y});
        for (int i = 0; i < 4; i++) {
            if (inside(x + dx[i], y + dy[i])) {
                if (d[x + dx[i]][y + dy[i]] > d[x][y] + 1) {
                    d[x + dx[i]][y + dy[i]] = d[x][y] + 1;
                    q.push({x + dx[i], y + dy[i]});
                }
            }
        }
    }

    for (auto i: ans) printf("%d %d\n", i.first - 1, i.second - 1);
    return 0;
}
