#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, m, d[N], lef[N], rig[N], tlef[N], trig[N];
vector <pair <int, pair <int, int> > > edges;
vector <pair <int, int> > g[N];

struct disj {
    int par[N];
    void init (int n) {
        for (int i = 1; i <= n; i++) par[i] = i;
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

void dfs (int u, int p) {
    for (auto v: g[u]) {
        if (v.second == p) continue;
        d[v.second] = min(d[u], v.first);
        dfs(v.second, u);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        lef[i] = l; rig[i] = r;
    }

    memset(tlef, 0x3f, sizeof(tlef)); memset(trig, 0x3f, sizeof(trig));
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (v == 1) tlef[u] = i - 1;
        else trig[u] = i - 1;
    }

    for (int i = 1; i <= n; i++) {
        if (lef[i] != -1) edges.push_back({tlef[i], {i, lef[i]}});
        if (rig[i] != -1) edges.push_back({trig[i], {i, rig[i]}});
    }

    sort(edges.begin(), edges.end(), greater <pair <int, pair <int, int> > >());
    dsu.init(n);
    for (auto i: edges) {
        if (dsu.same(i.second.first, i.second.second)) continue;
        dsu.join(i.second.first, i.second.second);
        g[i.second.first].push_back({i.first, i.second.second});
        g[i.second.second].push_back({i.first, i.second.first});
    }

    memset(d, 0x3f, sizeof(d));
    dfs(1, 1);
    for (int i = 1; i <= n; i++) printf("%d\n", d[i] > 1e9 ? -1 : d[i]);
    return 0;
}
