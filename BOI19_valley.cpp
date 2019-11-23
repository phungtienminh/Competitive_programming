#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, s, q, e, h[N], par[20][N], st[N], en[N], in[N], Time = 0;
long long d[N], ans[N];
vector <pair <int, int> > g[N];
pair <int, pair <int, int> > edge[N];
bool marked[N];
vector <pair <int, int> > queries[N];

struct SegmentTree {
    long long node[N << 2], lz[N << 2];
    void init (int i, int l, int r) {
        if (l == r) {
            node[i] = (marked[in[l]] ? d[in[l]] : (long long)1e18);
            lz[i] = 0;
            return;
        }

        int mid = l + r >> 1;
        init(i << 1, l, mid);
        init(i << 1 | 1, mid + 1, r);
        node[i] = min(node[i << 1], node[i << 1 | 1]);
        lz[i] = 0;
    }

    void propagate (int i, int l, int r) {
        if (lz[i]) {
            node[i] += lz[i];
            if (l != r) {
                lz[i << 1] += lz[i];
                lz[i << 1 | 1] += lz[i];
            }

            lz[i] = 0;
        }
    }

    void update (int i, int l, int r, int a, int b, int val) {
        propagate(i, l, r);
        if (l > r || a > r || b < l) return;
        if (a <= l && r <= b) {
            node[i] += val;
            if (l != r) {
                lz[i << 1] += val;
                lz[i << 1 | 1] += val;
            }

            return;
        }

        int mid = l + r >> 1;
        update(i << 1, l, mid, a, b, val);
        update(i << 1 | 1, mid + 1, r, a, b, val);
        node[i] = min(node[i << 1], node[i << 1 | 1]);
    }

    long long query (int i, int l, int r, int a, int b) {
        if (l > r || a > r || b < l) return (long long)1e18;
        propagate(i, l, r);
        if (a <= l && r <= b) return node[i];

        int mid = l + r >> 1;
        return min(query(i << 1, l, mid, a, b), query(i << 1 | 1, mid + 1, r, a, b));
    }
} it;

void dfs (int u, int p) {
    st[u] = ++Time;
    in[Time] = u;
    for (auto ii: g[u]) {
        int w = ii.first, v = ii.second;
        if (v == p) continue;
        h[v] = h[u] + 1;
        d[v] = d[u] + w;
        par[0][v] = u;
        dfs(v, u);
    }

    en[u] = Time;
}

void makeLCA(){
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j <= n; j++) {
            if (par[i - 1][j] != -1) par[i][j] = par[i - 1][par[i - 1][j]];
        }
    }
}

int LCA (int x, int y) {
    if (h[x] > h[y]) swap(x, y);
    for (int i = 19; i >= 0; i--) {
        if (par[i][y] != -1 && h[y] - (1 << i) >= h[x]) {
            y = par[i][y];
        }
    }

    if (x == y) return x;
    for (int i = 19; i >= 0; i--) {
        if (par[i][x] != -1 && par[i][y] != -1 && par[i][x] != par[i][y]) {
            x = par[i][x];
            y = par[i][y];
        }
    }

    if (x == y) return x;
    return par[0][x];
}

long long dist (int u, int v) {
    return d[u] + d[v] - 2 * d[LCA(u, v)];
}

void solve (int ver, int p) {
    for (auto ii: queries[ver]) {
        int road_id = ii.first, id = ii.second;
        int w = edge[road_id].first, u = edge[road_id].second.first, v = edge[road_id].second.second;
        if (dist(e, v) + dist(u, ver) + w == dist(ver, e)) {
            ans[id] = it.query(1, 1, n, st[u], en[u]);
        }
        else if (dist(e, u) + dist(v, ver) + w == dist(ver, e)) {
            ans[id] = it.query(1, 1, n, st[v], en[v]);
        }
        else {
            ans[id] = -1;
        }
    }

    for (auto ii: g[ver]) {
        int w = ii.first, v = ii.second;
        if (v == p) continue;
        it.update(1, 1, n, st[v], en[v], -w);
        it.update(1, 1, n, 1, st[v] - 1, w);
        it.update(1, 1, n, en[v] + 1, n, w);
        solve(v, ver);
        it.update(1, 1, n, st[v], en[v], w);
        it.update(1, 1, n, 1, st[v] - 1, -w);
        it.update(1, 1, n, en[v] + 1, n, -w);
    }
}

int main(){
    scanf("%d %d %d %d", &n, &s, &q, &e); memset(par, -1, sizeof(par));
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g[u].push_back({w, v});
        g[v].push_back({w, u});
        edge[i] = {w, {u, v}};
    }

    for (int i = 1; i <= s; i++) {
        int u;
        scanf("%d", &u);
        marked[u] = true;
    }

    for (int i = 1; i <= q; i++) {
        int road, village;
        scanf("%d %d", &road, &village);
        queries[village].push_back({road, i});
    }

    dfs(e, e);
    makeLCA();
    it.init(1, 1, n);
    solve(e, e);

    for (int i = 1; i <= q; i++) {
        if (ans[i] == -1) puts("escaped");
        else {
            if (ans[i] < (long long)1e16) printf("%lld\n", ans[i]);
            else puts("oo");
        }
    }
    return 0;
}
