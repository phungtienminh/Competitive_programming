#include <bits/stdc++.h>

using namespace std;

const int N = 1005;
char a[N][N];
int n, m, d[N][N];

bool checkInside (int x, int y) {
    return (x >= 1 && x <= n && y >= 1 && y <= m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    memset(d, 0x3f, sizeof(d));
    queue <pair <int, int> > q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if (a[i][j] == '1') {
                d[i][j] = 0;
                q.push(make_pair(i, j));
            }
        }
    }

    while (!q.empty()) {
        pair <int, int> u = q.front(); q.pop();

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx != 0 && dy != 0) continue;
                if (dx == 0 && dy == 0) continue;
                if (!checkInside(u.first + dx, u.second + dy)) continue;

                int nextx = u.first + dx;
                int nexty = u.second + dy;

                if (d[nextx][nexty] > d[u.first][u.second] + 1) {
                    d[nextx][nexty] = d[u.first][u.second] + 1;
                    q.push(make_pair(nextx, nexty));
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (j - 1) cout << " ";
            cout << d[i][j];
        }
    }
    return 0;
}
