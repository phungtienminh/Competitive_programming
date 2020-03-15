#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

static int cnt = 0;
int n, head[N], pos[N], h[N], par[20][N], subt[N];
vector <pair <int, pair <int, int> > > g[N];
pair <int, int> val[N];

struct SegmentTree {
    long long node[N << 2];
    int lazy[N << 2];
    void init (int i, int l, int r) {
        if (l == r) {
            node[i] = lazy[i] = 0;
            return;
        }

        int mid = l + r >> 1;
        init(i << 1, l, mid);
        init(i << 1 | 1, mid + 1, r);
        node[i] = 0;
        lazy[i] = 0;
    }

    void dolazy (int i, int l, int r) {
        if (lazy[i]) {
            node[i] += 1LL * lazy[i] * (r - l + 1);
            if (l != r) {
                lazy[i << 1] += lazy[i];
                lazy[i << 1 | 1] += lazy[i];
            }

            lazy[i] = 0;
        }
    }

    void update (int i, int l, int r, int a, int b, int val) {
        dolazy(i, l, r);
        if (l > r || a > r || b < l) return;
        if (a <= l && r <= b) {
            node[i] += 1LL * val * (r - l + 1);
            if (l != r) {
                lazy[i << 1] += val;
                lazy[i << 1 | 1] += val;
            }

            return;
        }

        int mid = l + r >> 1;
        update(i << 1, l, mid, a, b, val);
        update(i << 1 | 1, mid + 1, r, a, b, val);
        node[i] = node[i << 1] + node[i << 1 | 1];
    }

    long long query (int i, int l, int r, int a, int b) {
        if (l > r || a > r || b < l) return 0;
        dolazy(i, l, r);
        if (a <= l && r <= b) return node[i];
        int mid = l + r >> 1;
        return query(i << 1, l, mid, a, b) + query(i << 1 | 1, mid + 1, r, a, b);
    }
} it;

void dfs (int u, int p) {
    subt[u] = 1;
    for (auto V: g[u]) {
        int v = V.first, c1 = V.second.first, c2 = V.second.second;
        if (v == p) continue;
        h[v] = h[u] + 1;
        par[0][v] = u;
        val[v] = {c1, c2};
        dfs(v, u);
        subt[u] += subt[v];
    }
}

void makeLCA(){
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j <= n; j++) {
            if (par[i - 1][j] != -1) {
                par[i][j] = par[i - 1][par[i - 1][j]];
            }
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

void HLD (int u, int p) {
    if (!head[u]) head[u] = u;
    pos[u] = ++cnt;

    int big = -1;
    for (auto V: g[u]) {
        int v = V.first;
        if (v == p) continue;
        if (big == -1 || subt[big] < subt[v]) big = v;
    }

    if (big != -1) {
        head[big] = head[u];
        HLD(big, u);
    }

    for (auto V: g[u]) {
        int v = V.first;
        if (v == p || v == big) continue;
        HLD(v, u);
    }
}

void augment_path (int u, int v) {
    int p = LCA(u, v);
    while (head[u] != head[p]) {
        it.update(1, 1, cnt, pos[head[u]], pos[u], 1);
        u = par[0][head[u]];
    }

    while (head[v] != head[p]) {
        it.update(1, 1, cnt, pos[head[v]], pos[v], 1);
        v = par[0][head[v]];
    }

    it.update(1, 1, cnt, pos[p], pos[u], 1);
    it.update(1, 1, cnt, pos[p], pos[v], 1);
    it.update(1, 1, cnt, pos[p], pos[p], -2);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n; memset(par, -1, sizeof(par));
    for (int i = 1; i <= n - 1; i++) {
        int u, v, c1, c2;
        cin >> u >> v >> c1 >> c2;
        g[u].push_back({v, {c1, c2}});
        g[v].push_back({u, {c1, c2}});
    }

    dfs(1, 1);
    makeLCA();
    HLD(1, 1);
    it.init(1, 1, cnt);

    for (int i = 1; i < n; i++) augment_path(i, i + 1);

    long long ans = 0;
    for (int i = 1; i <= n; i++) ans += min(1LL * val[i].first * it.query(1, 1, cnt, pos[i], pos[i]), (long long)val[i].second);
    cout << ans;
    return 0;
}
