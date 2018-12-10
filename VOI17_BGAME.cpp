#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

struct disj {
    int par[N];
    void init (int n){
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

int n, m, h[N], par[20][N], Max[20][N], Min[20][N], weight[N];
vector <pair <int, int> > g[N];
vector <pair <pair <int, int>, pair <int, int> > > edges;
pair <int, pair <int, int> > edge[N];
bool in[N];

void dfs (int u, int p) {
    for (auto v: g[u]) {
        if (v.second == p) continue;
        h[v.second] = h[u] + 1;
        par[0][v.second] = u;
        Max[0][v.second] = v.first;
        Min[0][v.second] = v.first;
        dfs(v.second, u);
    }
}

void makeLCA(){
    for (int i = 1; i < 20; i++) for (int j = 1; j <= n; j++) if (par[i - 1][j] != -1) par[i][j] = par[i - 1][par[i - 1][j]], Max[i][j] = max(Max[i - 1][j], Max[i - 1][par[i - 1][j]]), Min[i][j] = min(Min[i - 1][j], Min[i - 1][par[i - 1][j]]);
}

int LCAmax (int x, int y) {
    int ans = 0;
    if (h[x] > h[y]) swap(x, y);
    for (int i = 19; i >= 0; i--) if (par[i][y] != -1 && h[y] - (1 << i) >= h[x]) ans = max(ans, Max[i][y]), y = par[i][y];
    for (int i = 19; i >= 0; i--) if (par[i][x] != -1 && par[i][y] != -1 && par[i][x] != par[i][y]) ans = max(ans, max(Max[i][x], Max[i][y])), x = par[i][x], y = par[i][y];
    return x == y ? ans : max(ans, max(Max[0][x], Max[0][y]));
}

int LCAmin (int x, int y) {
    int ans = 2e9;
    if (h[x] > h[y]) swap(x, y);
    for (int i = 19; i >= 0; i--) if (par[i][y] != -1 && h[y] - (1 << i) >= h[x]) ans = min(ans, Min[i][y]), y = par[i][y];
    for (int i = 19; i >= 0; i--) if (par[i][x] != -1 && par[i][y] != -1 && par[i][x] != par[i][y]) ans = min(ans, min(Min[i][x], Min[i][y])), x = par[i][x], y = par[i][y];
    return x == y ? ans : min(ans, min(Min[0][x], Min[0][y]));
}

int main(){
    #ifndef Futymy
        freopen("bgame.inp", "r", stdin);
        freopen("bgame.out", "w", stdout);
    #endif // Futymy
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges.push_back({{w, i}, {u, v}});
    }

    dsu.init(n);
    sort(edges.begin(), edges.end(), greater <pair <pair <int, int>, pair <int, int> > >());
    for (auto i: edges) {
        if (dsu.same(i.second.first, i.second.second)) continue;
        dsu.join(i.second.first, i.second.second);
        g[i.second.first].push_back({i.first.first, i.second.second});
        g[i.second.second].push_back({i.first.first, i.second.first});
        in[i.first.second] = true;
    }

    memset(par, -1, sizeof(par));
    for (int i = 1; i <= n; i++) if (!h[i]) dfs(i, i); makeLCA();

    int ans = 0;
    for (auto i: edges) {
        if (!in[i.first.second]) {
            int mx = LCAmax(i.second.first, i.second.second), mn = LCAmin(i.second.first, i.second.second);
            mx = max(mx, i.first.first);
            mn = min(mn, i.first.first);
            ans = max(ans, mx + mn);
        }
    }

    printf("%d", ans);
    return 0;
}
