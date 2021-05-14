#include <bits/stdc++.h>

using namespace std;

const int N = 505;

struct edge {
    int v, cost, energy;
    edge (int v = 0, int cost = 0, int energy = 0): v(v), cost(cost), energy(energy) {}
};

struct state {
    int dist, idx, energy;
    state (int dist = 0, int idx = 0, int energy = 0): dist(dist), idx(idx), energy(energy) {}
    bool operator < (const state &rhs) const {
        return dist > rhs.dist;
    }
};

int n, m, a[N], dist[N], e[N];
vector <edge> g[N];

int dijkstra(){
    priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > pq;
    int d[N]; memset(d, 0x3f, sizeof(d)); d[1] = 0; pq.push({d[1], 1});
    while (!pq.empty()) {
        int curd = pq.top().first, u = pq.top().second; pq.pop();
        if (curd == d[u]) {
            for (auto v: g[u]) {
                if (d[v.v] > d[u] + v.cost) {
                    d[v.v] = d[u] + v.cost;
                    pq.push({d[v.v], v.v});
                }
            }
        }
    }

    return d[n];
}

int check (int mid) {
    memset(dist, 0x3f, sizeof(dist)); memset(e, 0, sizeof(e)); dist[1] = 0; e[1] = mid;
    priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > pq;
    pq.push({dist[1], 1});
    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second; pq.pop();
        if (d == dist[u]) {
            for (auto v: g[u]) {
                if (dist[v.v] > dist[u] + v.cost && e[u] >= v.energy) {
                    dist[v.v] = dist[u] + v.cost;
                    e[v.v] = (a[v.v] == 1 ? mid : e[u] - v.energy);
                    pq.push({dist[v.v], v.v});
                }
                else if (dist[v.v] == dist[u] + v.cost && e[u] >= v.energy) e[v.v] = max(e[v.v], e[u] - v.energy);
            }
        }
    }

    return dist[n];
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int u, v, t, c;
        scanf("%d %d %d %d", &u, &v, &t, &c);
        g[u].push_back(edge(v, t, c));
        g[v].push_back(edge(u, t, c));
    }

    int pre = dijkstra();
    int l = 1, r = 1e9;

    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid) > pre) l = mid + 1;
        else r = mid - 1;
    }

    printf("%d", l);
    return 0;
}
