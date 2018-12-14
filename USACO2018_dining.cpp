#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 5;

int n, m, k, val[N], d[N], d2[N];
vector <pair <int, int> > g[N];
vector <int> vec;

void dijkstra(){
    priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > pq;
    memset(d, 0x3f, sizeof(d)); d[n] = 0; pq.push({d[n], n});
    while (!pq.empty()) {
        int dist = pq.top().first, u = pq.top().second; pq.pop();
        if (dist == d[u]) {
            for (auto i: g[u]) {
                int v = i.second, w = i.first;
                if (d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    pq.push({d[v], v});
                }
            }
        }
    }
}

void redijkstra() {
    priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > pq;
    memset(d2, 0x3f, sizeof(d2));
    for (auto i: vec) d2[i] = d[i] - val[i], pq.push({d2[i], i});
    while (!pq.empty()) {
        int dist = pq.top().first, u = pq.top().second; pq.pop();
        if (dist == d2[u]) {
            for (auto i: g[u]) {
                int w = i.first, v = i.second;
                if (d2[v] > d2[u] + w) {
                    d2[v] = d2[u] + w;
                    pq.push({d2[v], v});
                }
            }
        }
    }
}

int main(){
    #ifndef Futymy
        freopen("dining.in", "r", stdin);
        freopen("dining.out", "w", stdout);
    #endif // Futymy
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g[u].push_back({w, v});
        g[v].push_back({w, u});
    }

    for (int i = 1; i <= k; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        val[x] = max(val[x], y);
        vec.push_back(x);
    }

    dijkstra();
    redijkstra();
    for (int i = 1; i <= n - 1; i++) printf("%d\n", d2[i] <= d[i] ? 1 : 0);
    return 0;
}
