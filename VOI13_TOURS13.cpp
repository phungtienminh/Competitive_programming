#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

const int N = 1005;

int t, n, m, d[N][N], adj[N][N];
vector <pair <int, int> > g[N];

void dijkstra (int s) {
    for (int i = 1; i <= n; ++i) d[s][i] = 1e9;
    d[s][s] = 0;
    priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > pq;
    pq.push({d[s][s], s});
    while (!pq.empty()) {
        int dist = pq.top().first, u = pq.top().second; pq.pop();
        if (dist == d[s][u]) {
            for (auto v: g[u]) {
                if (d[s][v.second] > d[s][u] + v.first) {
                    d[s][v.second] = d[s][u] + v.first;
                    pq.push({d[s][v.second], v.second});
                }
            }
        }
    }
}

int readInt() {
    int ans = 0;
    char c;
    while (1) {
        c = getchar();
        if (c == ' ' || c == '\n') return ans;
        ans = (ans << 3) + (ans << 1) + (c - '0');
    }
}

int main(){
    t = readInt();
    while (t--) {
        n = readInt(); m = readInt(); for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) adj[i][j] = 1e9;
        for (int i = 1; i <= n; ++i) g[i].clear();
        for (int i = 1; i <= m; ++i) {
            int u, v, w;
            u = readInt(); v = readInt(); w = readInt();
            adj[u][v] = min(adj[u][v], w);
        }

        for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; j++) if (adj[i][j] < 1e9) g[i].push_back({adj[i][j], j});
        for (int i = 1; i <= n; ++i) sort(g[i].begin(), g[i].end());
        for (int i = 1; i <= n; ++i) dijkstra(i);
        for (int i = 1; i <= n; ++i) {
            int ans = 1e9 + 1;
            for (int j = 1; j <= n; ++j) if (j != i) ans = min(ans, d[i][j] + d[j][i]);
            printf("%d\n", ans > 1e9 ? -1 : ans);
        }
    }
    return 0;
}
