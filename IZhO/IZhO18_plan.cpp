#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m, dist[N], p, q, h[N], par[20][N], Min[20][N];
vector <pair <int, int> > g[N], tree[N];
priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > pq;

struct edge {
    int u, v, w;

    edge (int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) {}

    bool operator < (const edge &rhs) const {
        return w > rhs.w;
    }
};

vector <edge> e;

struct disj {
    int par[N];
    void init (int n) {
        iota(par + 1, par + n + 1, 1);
    }

    int Find (int x) {
        return par[x] == x ? x : par[x] = Find(par[x]);
    }

    bool same (int x, int y) {
        return Find(x) == Find(y);
    }

    void join (int x, int y) {
        x = Find(x); y = Find(y);
        if (x == y) return;
        par[y] = x;
    }
} dsu;

void dijkstra(){
    memset(dist, 0x3f, sizeof(dist));
    cin >> p;
    for (int i = 1; i <= p; i++) {
        int x;
        cin >> x;
        dist[x] = 0;
        pq.push({dist[x], x});
    }

    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second; pq.pop();
        if (d == dist[u]) {
            for (auto V: g[u]) {
                int w = V.first, v = V.second;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
    }
}

void buildMST(){
    for (auto &i: e) i.w = min(dist[i.u], dist[i.v]);
    sort(e.begin(), e.end());
    for (auto i: e) {
        if (dsu.same(i.u, i.v)) continue;
        dsu.join(i.u, i.v);
        tree[i.u].push_back({i.w, i.v});
        tree[i.v].push_back({i.w, i.u});
    }

    memset(par, -1, sizeof(par)); memset(Min, 0x3f, sizeof(Min));
}

void dfs (int u, int p) {
    for (auto V: tree[u]) {
        int w = V.first, v = V.second;
        if (v == p) continue;
        h[v] = h[u] + 1;
        par[0][v] = u;
        Min[0][v] = w;
        dfs(v, u);
    }
}

void makeLCA(){
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j <= n; j++) {
            if (par[i - 1][j] != -1) {
                par[i][j] = par[i - 1][par[i - 1][j]];
                Min[i][j] = min(Min[i - 1][j], Min[i - 1][par[i - 1][j]]);
            }
        }
    }
}

int LCA (int x, int y) {
    int ans = 1e9;
    if (h[x] > h[y]) swap(x, y);
    for (int i = 19; i >= 0; i--) {
        if (h[y] - (1 << i) >= h[x] && par[i][y] != -1) {
            ans = min(ans, Min[i][y]);
            y = par[i][y];
        }
    }

    if (x == y) return ans;
    for (int i = 19; i >= 0; i--) {
        if (par[i][x] != -1 && par[i][y] != -1 && par[i][x] != par[i][y]) {
            ans = min(ans, Min[i][x]);
            ans = min(ans, Min[i][y]);
            x = par[i][x];
            y = par[i][y];
        }
    }

    if (x == y) return ans;
    ans = min(ans, min(Min[0][x], Min[0][y]));
    return ans;
}

void answerQueries(){
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << LCA(u, v) << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m; dsu.init(n);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({w, v});
        g[v].push_back({w, u});
        e.push_back(edge(u, v, w));
    }

    dijkstra();
    buildMST();
    dfs(1, 1);
    makeLCA();
    answerQueries();
    return 0;
}
/*
9 12
1 9 4
1 2 5
2 3 7
2 4 3
4 3 6
3 6 4
8 7 10
6 7 5
5 8 1
9 5 7
5 4 12
6 8 2
2
4 7
5
1 6
5 3
4 8
5 8
1 5
*/
