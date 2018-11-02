#include <bits/stdc++.h>

using namespace std;

const int N = 205;

struct state {
    int x, y, dir, dist;
    state (int x = 0, int y = 0, int dir = 0, int dist = 0): x(x), y(y), dir(dir), dist(dist) {}
};

int dist[N][N][5], n, m, p, q, s, t;
bool ban[N][N];
deque <state> dq;
int dx[4] = {-1, 1, 1, -1};
int dy[4] = {1, 1, -1, -1};

bool inside (int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n && !ban[x][y];
}

int bfs(){
    memset(dist, 0x3f, sizeof(dist)); dist[p][q][0] = 0; dq.push_back(state(p, q, 0, 0));
    while (!dq.empty()) {
        state u = dq.front(); dq.pop_front();
        int x = u.x, y = u.y, dir = u.dir, dt = u.dist;
        if (dt != dist[x][y][dir]) continue;

        if (dir == 0) {
            for (int i = 0; i < 4; i++) {
                if (inside(x + dx[i], y + dy[i])) {
                    if (dist[x + dx[i]][y + dy[i]][i + 1] > dist[x][y][dir]) {
                        dist[x + dx[i]][y + dy[i]][i + 1] = dist[x][y][dir];
                        dq.push_front(state(x + dx[i], y + dy[i], i + 1, dist[x + dx[i]][y + dy[i]][i + 1]));
                    }
                }
            }
        }
        else {
            for (int i = 0; i < 4; i++) {
                if (inside(x + dx[i], y + dy[i])) {
                    if (dist[x + dx[i]][y + dy[i]][i + 1] > dist[x][y][dir] + ((i + 1) != dir)) {
                        dist[x + dx[i]][y + dy[i]][i + 1] = dist[x][y][dir] + ((i + 1) != dir);
                        if (i != dir) dq.push_back(state(x + dx[i], y + dy[i], i + 1, dist[x + dx[i]][y + dy[i]][i + 1]));
                        else dq.push_front(state(x + dx[i], y + dy[i], i + 1, dist[x + dx[i]][y + dy[i]][i + 1]));
                    }
                }
            }
        }
    }

    int ans = 1e9;
    for (int i = 1; i <= 4; i++) ans = min(ans, dist[s][t][i]);
    return ans >= 1e9 ? -1 : ans + 1;
}

int main(){
    scanf("%d %d %d %d %d %d", &n, &m, &p, &q, &s, &t);
    for (int i = 1; i <= m; i++) {
        int x, y; scanf("%d %d", &x, &y);
        ban[x][y] = true;
    }

    printf("%d", bfs());
    return 0;
}
