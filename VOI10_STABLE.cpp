#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

int n, m, s, d[N], dp[N], ans = 0;
vector <int> g[N];
map <pair <int, int>, int> mm;
priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > pq;

void dijkstra(){
    memset(d, 0x3f, sizeof(d)); d[s] = 0; dp[s] = 1;
    pq.push({d[s], s});
    while (!pq.empty()) {
        int dist = pq.top().first, u = pq.top().second; pq.pop();
        if (dist == d[u]) {
            for (auto v: g[u]) {
                if (d[v] > d[u] + 1) {
                    d[v] = d[u] + 1;
                    dp[v] = dp[u];
                    pq.push({d[v], v});
                }
                else if (d[v] == d[u] + 1) dp[v] += dp[u], dp[v] = min(dp[v], 2);
            }
        }
    }
}

int main(){
    scanf("%d %d %d", &n, &m, &s);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (mm.count({u, v})) continue;
        g[u].push_back(v);
        mm[{u, v}] = 1;
    }

    dijkstra();
    for (int i = 1; i <= n; i++) if (dp[i] > 1) ans++;
    printf("%d", ans);
    return 0;
}
