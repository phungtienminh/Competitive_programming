#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

struct edges {
    int u, v, w, id;
    edges (int u = 0, int v = 0, int w = 0, int id = 0): u(u), v(v), w(w), id(id) {}
    bool operator < (const edges &rhs) const {
        return w > rhs.w;
    }
};

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

int n, m, a[N], head[N], pos[N], h[N], par[20][N], child[N], in[N], cnt = 0;
bool in_mst[N];
pair <int, pair <int, int> > edge[N];
vector <pair <int, int> > g[N], trees[N];
vector <edges> Edges;
long long ans = 0;

void buildMST(){
    sort(Edges.begin(), Edges.end()); dsu.init(n);
    for (auto i: Edges) {
        if (dsu.same(i.u, i.v)) continue;
        dsu.join(i.u, i.v);
        in_mst[i.id] = true;
    }
}

void rebuild(){
    for (int i = 1; i <= m; i++) {
        if (in_mst[i]) {
            trees[edge[i].second.first].push_back({edge[i].first, edge[i].second.second});
            trees[edge[i].second.second].push_back({edge[i].first, edge[i].second.first});
        }
    }
}

void dfs (int u, int p) {
    child[u] = 1;
    for (auto v: trees[u]) {
        if (v.second == p) continue;
        h[v.second] = h[u] + 1;
        par[0][v.second] = u;
        dfs(v.second, u);
        child[u] += child[v.second];
    }
}

void makeLCA(){
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j <= n; j++) {
            if (par[i - 1][j]) par[i][j] = par[i - 1][par[i - 1][j]];
        }
    }
}

int LCA (int x, int y) {
    if (h[x] > h[y]) swap(x, y);
    for (int i = 19; i >= 0; i--) if (par[i][y] && h[y] - (1 << i) >= h[x]) y = par[i][y];
    for (int i = 19; i >= 0; i--) if (par[i][x] && par[i][y] && par[i][x] != par[i][y]) x = par[i][x], y = par[i][y];
    return (x == y ? x : par[0][x]);
}

void makeWeight(){
    for (int u = 1; u <= n; u++) {
        for (auto v: trees[u]) {
            if (h[u] < h[v.second]) a[v.second] = v.first;
            else a[u] = v.first;
        }
    }
}

void HLD (int u, int p) {
    head[u] = u;
    pos[u] = ++cnt;
    in[cnt] = u;
    int big = -1;
    for (auto v: trees[u]) {
        if (v.second == p) continue;
        if (big == -1 || child[big] < child[v.second]) big = v.second;
    }

    if (big != -1) {
        head[big] = head[u];
        HLD(big, u);
    }

    for (auto v: trees[u]) {
        if (v.second == p || v.second == big) continue;
        HLD(v.second, u);
    }
}

struct seg {
    int node[N << 2];
    void init (int i, int l, int r) {
        if (l == r) {
            node[i] = a[in[l]];
            return;
        }

        int m = (l + r) >> 1;
        init(i << 1, l, m);
        init(i << 1 | 1, m + 1, r);
        node[i] = min(node[i << 1], node[i << 1 | 1]);
    }

    int get (int i, int l, int r, int a, int b) {
        if (l > r || a > r || b < l) return 1e9;
        if (a <= l && r <= b) return node[i];

        int m = (l + r) >> 1;
        return min(get(i << 1, l, m, a, b), get(i << 1 | 1, m + 1, r, a, b));
    }
} it;

int Find (int p, int u) {
    for (int i = 19; i >= 0; i--) if (h[u] - (1 << i) > h[p]) u = par[i][u];
    return u;
}

int query (int u, int v) {
    int p = LCA(u, v), ans = 1e9, nxtu, nxtv;
    nxtu = Find(p, u); nxtv = Find(p, v);

    //if (u == 2 && v == 4) cout << p << " " << nxtu << " " << nxtv << "\n";
    while (head[u] != head[nxtu]) {
        ans = min(ans, it.get(1, 1, cnt, pos[head[u]], pos[u]));
        u = par[0][head[u]];
    }

    //if (u == 2) cout << head[v] << " " << head[nxtv] << " ";
    while (head[v] != head[nxtv]) {
        ans = min(ans, it.get(1, 1, cnt, pos[head[v]], pos[v]));
        v = par[0][head[v]];
    }

    //if (u == 2) cout << head[v] << " ";
    //cout << ans << "\n";
    //if (u == 2) cout << v << "\n";
    if (nxtu != p) ans = min(ans, it.get(1, 1, cnt, pos[nxtu], pos[u]));
    if (nxtv != p) ans = min(ans, it.get(1, 1, cnt, pos[nxtv], pos[v]));
    return ans;
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g[u].push_back({w, v}); g[v].push_back({w, u});
        Edges.push_back(edges(u, v, w, i));
        edge[i] = {w, {u, v}};
    }

    buildMST();
    rebuild();
    dfs(1, 1);
    makeLCA();
    makeWeight();
    HLD(1, 1);
    it.init(1, 1, cnt);

    //for (int i = 1; i <= n; i++) cout << a[i] << " ";
    //cout << "\n";
    for (int i = 1; i <= m; i++) {
        if (!in_mst[i]) {
            int w = edge[i].first, cur = query(edge[i].second.first, edge[i].second.second);
            //cout << w << " " << cur << "\n";
            ans += cur - w;
        }
    }

    printf("%lld", ans);
    return 0;
}
