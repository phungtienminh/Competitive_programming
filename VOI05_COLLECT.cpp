#include <bits/stdc++.h>

using namespace std;

const int N = 5;

struct data {
    int g, s, b, dist;
    data (int g = 0, int s = 0, int b = 0, int dist = 0): g(g), s(s), b(b), dist(dist) {}
};

struct change {
    int g, s, b, ng, ns, nb;
    change (int g = 0, int s = 0, int b = 0, int ng = 0, int ns = 0, int nb = 0): g(g), s(s), b(b), ng(ng), ns(ns), nb(nb) {}
};

struct state {
    int g, s, b;
    state (int g = 0, int s = 0, int b = 0): g(g), s(s), b(b) {}
};

int dist[N][N][N], ng, ns, nb, fg, fs, fb, n, G, S, B, NG, NS, NB;
vector <data> vec;
vector <change> operations;

bool ok (int x, int y, int z, int nx, int ny, int nz, int cx, int cy, int cz) {
    return x >= nx && y >= ny && z >= nz && x - nx + cx < N && y - ny + cy < N && z - nz + cz < N;
}

void bfs(){
    memset(dist, 0x3f, sizeof(dist)); dist[ng][ns][nb] = 0;
    queue <state> q; q.push(state(ng, ns, nb));
    while (!q.empty()) {
        int curg = q.front().g, curs = q.front().s, curb = q.front().b; q.pop();
        if (curg >= fg && curs >= fs && curb >= fb) continue;
        for (auto i: operations) {
            if (ok(curg, curs, curb, i.g, i.s, i.b, i.ng, i.ns, i.nb)) {
                if (dist[curg - i.g + i.ng][curs - i.s + i.ns][curb - i.b + i.nb] > dist[curg][curs][curb] + 1) {
                    dist[curg - i.g + i.ng][curs - i.s + i.ns][curb - i.b + i.nb] = dist[curg][curs][curb] + 1;
                    q.push(state(curg - i.g + i.ng, curs - i.s + i.ns, curb - i.b + i.nb));
                }
            }
        }
    }

    for (int i = fg; i <= 4; i++) for (int j = fs; j <= 4; j++) for (int k = fb; k <= 4; k++) if (dist[i][j][k] <= n) vec.push_back(data(i, j, k, dist[i][j][k]));
}

int main(){
    scanf("%d", &n);
    scanf("%d %d %d %d %d %d", &ng, &ns, &nb, &fg, &fs, &fb);
    while (scanf("%d %d %d %d %d %d", &G, &S, &B, &NG, &NS, &NB) == 6) operations.push_back(change(G, S, B, NG, NS, NB));
    bfs();

    if (vec.size() == 0) printf("%d", -1);
    else {
        printf("%d\n", (int)vec.size());
        for (auto i: vec) printf("%d %d %d %d\n", i.g, i.s, i.b, i.dist);
    }
    return 0;
}
