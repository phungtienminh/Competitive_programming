#include <bits/stdc++.h>

using namespace std;

const int N = 105;

int n, m, sx, sy, fx, fy, d[N][N][4];
char a[N][N];
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

bool ok (int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m && a[x][y] != 'X';
}

int dir (char c) {
    return (c == 'L' ? 0 : c == 'U' ? 1 : c == 'R' ? 2 : 3);
}

struct State {
    int dist, x, y, directions;
    State (int dist = 0, int x = 0, int y = 0, int directions = 0): dist(dist), x(x), y(y), directions(directions) {}
};

int bfs(){
    deque <State> dq;
    memset(d, 0x3f, sizeof(d)); d[sx][sy][dir(a[sx][sy])] = 0;
    dq.push_back(State(0, sx, sy, dir(a[sx][sy])));
    while (!dq.empty()) {
        State u = dq.front(); dq.pop_front();
        int dist = u.dist, x = u.x, y = u.y, directions = u.directions;
        if (dist != d[x][y][directions]) continue;

        //Move on the same directions
        if (ok(x + dx[directions], y + dy[directions])) {
            if (d[x + dx[directions]][y + dy[directions]][directions] > d[x][y][directions]) {
                d[x + dx[directions]][y + dy[directions]][directions] = d[x][y][directions];
                dq.push_front(State(d[x + dx[directions]][y + dy[directions]][directions], x + dx[directions], y + dy[directions], directions));
            }
        }

        //Change directions
        int ndirections = dir(a[x][y]);
        if (directions == ndirections) continue;
        if ((directions == 0 && ndirections == 2) || (directions == 2 && ndirections == 0)) continue;
        if ((directions == 1 && ndirections == 3) || (directions == 3 && ndirections == 1)) continue;
        if (ok(x + dx[ndirections], y + dy[ndirections])) {
            if (d[x + dx[ndirections]][y + dy[ndirections]][ndirections] > d[x][y][directions] + 1) {
                d[x + dx[ndirections]][y + dy[ndirections]][ndirections] = d[x][y][directions] + 1;
                dq.push_back(State(d[x + dx[ndirections]][y + dy[ndirections]][ndirections], x + dx[ndirections], y + dy[ndirections], ndirections));
            }
        }
    }

    int ans = 1e9;
    for (int i = 0; i < 4; i++) ans = min(ans, d[fx][fy][i]);
    return ans + 1;
}

int main(){
    #ifndef Futymy
        freopen("mazein.txt", "r", stdin);
        freopen("mazeout.txt", "w", stdout);
    #endif // Futymy
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> sx >> sy;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j], fx = (a[i][j] == 'F' ? i : fx), fy = (a[i][j] == 'F' ? j : fy);
    if (sx == fx && sy == fy) cout << 0;
    else cout << bfs();
    return 0;
}
/*
3 4
1 1
FLUX
DULL
URDU
*/
