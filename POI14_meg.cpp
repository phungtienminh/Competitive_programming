#include <bits/stdc++.h>

using namespace std;

const int N = 25e4 + 5;

int head[N], pos[N], node[4 * N], lazy[4 * N], par[N], child[N], n, m;
int cnt = 0;
char s[2];
vector <int> g[N];

void input(){
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    memset(head, 0, sizeof(head));
}

void dfs (int u, int p) {
    child[u] = 1;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == p) continue;

        par[v] = u;
        dfs(v, u);
        child[u] += child[v];
    }
}

void HLD (int u, int p) {
    if (!head[u]) head[u] = u;
    pos[u] = ++cnt;
    int big = -1;

    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == p) continue;

        if (big == -1 || child[big] < child[v]) big = v;
    }

    if (big != -1) {
        head[big] = head[u];
        HLD(big, u);
    }

    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == p || v == big) continue;

        HLD(v, u);
    }
}

void init (int i, int l, int r) {
    if (l > r) return;
    if (l == r) {
        node[i] = 1;
        lazy[i] = 0;
        return;
    }

    int m = (l + r) >> 1;
    init(i << 1, l, m);
    init(i << 1 | 1, m + 1, r);

    node[i] = node[i << 1] + node[i << 1 | 1];
    lazy[i] = 0;
}

void dolazy (int i, int l, int r) {
    if (lazy[i]) {
        node[i] = lazy[i] * (r - l + 1);
        if (l != r) {
            lazy[i << 1] = lazy[i];
            lazy[i << 1 | 1] = lazy[i];
        }

        lazy[i] = 0;
    }
}

void update (int i, int l, int r, int a, int b, int val) {
    dolazy(i, l, r);
    if (l > r || a > r || b < l) return;
    if (a <= l && r <= b) {
        node[i] = 0;
        if (l != r) {
            lazy[i << 1] = 0;
            lazy[i << 1 | 1] = 0;
        }

        return;
    }

    int m = (l + r) >> 1;
    update(i << 1, l, m, a, b, val);
    update(i << 1 | 1, m + 1, r, a, b, val);

    node[i] = node[i << 1] + node[i << 1 | 1];
}

int get (int i, int l, int r, int a, int b) {
    if (l > r || a > r || b < l) return 0;
    dolazy(i, l, r);
    if (a <= l && r <= b) return node[i];

    int m = (l + r) >> 1;
    return get(i << 1, l, m, a, b) + get(i << 1 | 1, m + 1, r, a, b);
}

int query (int u, int v) {
    int ans = 0;
    while (head[u] != head[v]) {
        ans += get(1, 1, cnt, pos[head[u]], pos[u]);
        u = par[head[u]];
    }

    ans += get(1, 1, cnt, pos[v], pos[u]);
    return ans;
}

void solve(){
    scanf("%d", &m);
    for (int i = 1; i <= n + m - 1; i++) {
        scanf("%s", s);
        if (s[0] == 'W') {
            int x;
            scanf("%d", &x);
            printf("%d\n", query(x, 1) - 1);
        }
        else {
            int u, v;
            scanf("%d %d", &u, &v);
            if (v == par[u]) update(1, 1, cnt, pos[u], pos[u], 0);
            else update(1, 1, cnt, pos[v], pos[v], 0);
        }
    }
}

int main(){
    input();
    dfs(1, 1);
    HLD(1, 1);
    init(1, 1, cnt);
    solve();
    return 0;
}
