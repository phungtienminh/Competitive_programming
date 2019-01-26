#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int k, n, d[N][N];
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

bool inside (int x, int y) {
    return x >= 0 && x < k && y >= 0 && y < k;
}

int main(){
    scanf("%d %d", &k, &n);
    memset(d, 0x3f, sizeof(d));
    queue <pair <int, int> > q;
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        d[y][x] = 0; q.push({y, x});
    }

    while (!q.empty()) {
        int ux = q.front().first, uy = q.front().second; q.pop();
        for (int i = 0; i < 4; i++) {
            if (inside(ux + dx[i], uy + dy[i])) {
                if (d[ux + dx[i]][uy + dy[i]] > d[ux][uy] + 1) {
                    d[ux + dx[i]][uy + dy[i]] = d[ux][uy] + 1;
                    q.push({ux + dx[i], uy + dy[i]});
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < k; i++) for (int j = 0; j < k; j++) ans = max(ans, d[i][j]);
    printf("%d", ans);
    return 0;
}
