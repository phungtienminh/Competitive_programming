#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 5;

int n, q, head[N], pos[N], cnt = 0, subt[N], par[17][N], h[N];
vector <int> g[N];

void dfs (int u, int p) {
    subt[u] = 1;
    for (auto v: g[u]) {
        if (v == p) continue;
        h[v] = h[u] + 1;
        par[0][v] = u;
        dfs(v, u);
        subt[u] += subt[v];
    }
}

void makeLCA(){
    for (int i = 1; i < 17; i++) {
        for (int j = 1; j <= n; j++) {
            if (par[i - 1][j] != -1) par[i][j] = par[i - 1][par[i - 1][j]];
        }
    }
}

int LCA (int x, int y) {
    if (h[x] > h[y]) swap(x, y);
    for (int i = 16; i >= 0; i--) if (par[i][y] != -1 && h[y] - (1 << i) >= h[x]) y = par[i][y];
    if (x == y) return x;
    for (int i = 16; i >= 0; i--) {
        if (par[i][x] != par[i][y] && par[i][x] != -1 && par[i][y] != -1) {
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
    for (auto v: g[u]) {
        if (v == p) continue;
        if (big == -1 || subt[v] > subt[big]) big = v;
    }

    if (big != -1) {
        head[big] = head[u];
        HLD(big, u);
    }

    for (auto v: g[u]) {
        if (v == p || v == big) continue;
        HLD(v, u);
    }
}

struct SegmentTree {
    struct Node {
        int Max, lz;
        Node (int Max = 0, int lz = 0): Max(Max), lz(lz) {}
        Node operator + (const Node &rhs) const {
            return Node(max(Max, rhs.Max), lz);
        }
    } node[N << 2];

    void init (int i, int l, int r) {
        if (l == r) {
            node[i] = Node();
            return;
        }

        int mid = l + r >> 1;
        init(i << 1, l, mid);
        init(i << 1 | 1, mid + 1, r);
        node[i] = node[i << 1] + node[i << 1 | 1];
    }

    void push (int i, int l, int r) {
        if (node[i].lz) {
            node[i].Max += node[i].lz;
            if (l != r) {
                node[i << 1].lz += node[i].lz;
                node[i << 1 | 1].lz += node[i].lz;
            }

            node[i].lz = 0;
        }
    }

    void update (int i, int l, int r, int a, int b, int val) {
        push(i, l, r);
        if (l > r || a > r || b < l) return;
        if (a <= l && r <= b) {
            node[i].Max += val;
            if (l != r) {
                node[i << 1].lz += val;
                node[i << 1 | 1].lz += val;
            }

            return;
        }

        int mid = l + r >> 1;
        update(i << 1, l, mid, a, b, val);
        update(i << 1 | 1, mid + 1, r, a, b, val);
        node[i] = node[i << 1] + node[i << 1 | 1];
    }

    int query (int i, int l, int r, int a, int b) {
        if (l > r || a > r || b < l) return 0;
        push(i, l, r);
        if (a <= l && r <= b) return node[i].Max;

        int mid = l + r >> 1;
        return max(query(i << 1, l, mid, a, b), query(i << 1 | 1, mid + 1, r, a, b));
    }
} it;

void process (int u, int v) {
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
    it.update(1, 1, cnt, pos[p], pos[p], -1);
}

int main(){
    #ifndef Futymy
        freopen("maxflow.in", "r", stdin);
        freopen("maxflow.out", "w", stdout);
    #endif // Futymy
    scanf("%d %d", &n, &q); memset(par, -1, sizeof(par));
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 1);
    makeLCA();
    HLD(1, 1);
    it.init(1, 1, cnt);
    while (q--) {
        int u, v;
        scanf("%d %d", &u, &v);
        process(u, v);
    }

    printf("%d", it.query(1, 1, cnt, 1, cnt));
    return 0;
}
