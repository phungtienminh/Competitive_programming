#include <bits/stdc++.h>

using namespace std;

const int N = 5005;

vector <pair <int, pair <int, int> > > edges;
vector <pair <int, int> > g[N];
int d[2][N], a[N], n, m;

void dijkstra (int type) {
    for (int i = 1; i <= n; i++) d[type][i] = 1e9;
    d[type][1] = 0;
    priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > pq;
    pq.push({d[type][1], 1});
    while (!pq.empty()) {
        int dist = pq.top().first, u = pq.top().second; pq.pop();
        if (dist == d[type][u]) {
            for (auto v: g[u]) {
                if (d[type][v.second] > d[type][u] + v.first) {
                    d[type][v.second] = d[type][u] + v.first;
                    pq.push({d[type][v.second], v.second});
                }
            }
        }
    }
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    scanf("%d", &m);

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges.push_back({w, {u, v}});
        g[u].push_back({w, v});
    }

    dijkstra(0);
    for (int i = 1; i <= n; i++) g[i].clear();
    for (auto i: edges) g[i.second.second].push_back({i.first, i.second.first});
    dijkstra(1);

    int ans = 2e9 + 1e8;
    for (int i = 1; i <= n; i++) ans = min(ans, d[0][i] + d[1][i] + a[i] / 2);
    printf("%d", ans);
    return 0;
}
