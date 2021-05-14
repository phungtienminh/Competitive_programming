#include <bits/stdc++.h>

using namespace std;

const int N = 255;

struct state {
    int x, y, turn;

    state (int x = 0, int y = 0, int turn = 0): x(x), y(y), turn(turn) {}
};

int dist[N][N][2], n, m, s1, s2;
vector <int> g[N];
queue <state> q;

int main(){
    scanf("%d %d", &n, &m);
    scanf("%d %d", &s1, &s2);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
    }

    memset(dist, 0x3f, sizeof(dist)); dist[s1][s2][0] = 0;
    q.push(state(s1, s2, 0));

    while (!q.empty()) {
        state curStates = q.front(); q.pop();
        if (curStates.turn == 0) {
            for (auto v: g[curStates.x]) {
                if (dist[v][curStates.y][curStates.turn ^ 1] > dist[curStates.x][curStates.y][curStates.turn] + 1) {
                    dist[v][curStates.y][curStates.turn ^ 1] = dist[curStates.x][curStates.y][curStates.turn] + 1;
                    q.push(state(v, curStates.y, curStates.turn ^ 1));
                }
            }
        }
        else {
            for (auto v: g[curStates.y]) {
                if (dist[curStates.x][v][curStates.turn ^ 1] > dist[curStates.x][curStates.y][curStates.turn] + 1) {
                    dist[curStates.x][v][curStates.turn ^ 1] = dist[curStates.x][curStates.y][curStates.turn] + 1;
                    q.push(state(curStates.x, v, curStates.turn ^ 1));
                }
            }
        }
    }

    int ans = 1e9;
    for (int i = 1; i <= n; i++) ans = min(ans, dist[i][i][0]);

    if (ans >= 1e9) printf("NIE");
    else printf("%d", ans / 2);
    return 0;
}
