#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

vector <int> g[N], ans;
int n, m, k, par[20][N], node[8 * N], pref[N], h[N], queries[N], st[N], en[N], cnt = 0;
map <pair <int, int>, int > mm;

void dfs (int u, int p) {
    st[u] = ++cnt;
    for (int v: g[u]) {
        if (v != p) {
            h[v] = h[u] + 1;
            par[0][v] = u;
            dfs(v, u);
        }
    }

    en[u] = ++cnt;
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
        if (par[i][y] != -1 && h[y] - (1 << i) >= h[x]) y = par[i][y];
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

void init (int i, int l, int r) {
    if (l == r) {
        node[i] = 0;
        return;
    }

    int m = (l + r) >> 1;
    init(i << 1, l, m);
    init(i << 1 | 1, m + 1, r);

    node[i] = 0;
}

void update (int i, int l, int r, int pos, int val) {
    if (l == r) {
        node[i] += val;
        return;
    }

    int m = (l + r) >> 1;
    if (pos <= m) update(i << 1, l, m, pos, val);
    else update(i << 1 | 1, m + 1, r, pos, val);

    node[i] = node[i << 1] + node[i << 1 | 1];
}

int get (int i, int l, int r, int a, int b) {
    if (l > r || a > r || b < l) return 0;
    if (a <= l && r <= b) return node[i];

    int m = (l + r) >> 1;
    return get(i << 1, l, m, a, b) + get(i << 1 | 1, m + 1, r, a, b);
}

int kthNode (int dist, int u) {
    for (int i = log2(dist); i >= 0; i--) {
        if (dist & (1 << i)) u = par[i][u];
    }

    return u;
}

void redfs (int u, int p) {
    for (int v: g[u]) {
        if (v == p) continue;
        redfs(v, u);
        pref[u] += pref[v];
    }

    if (u != 1 && pref[u] >= k) ans.push_back(mm[{u, par[0][u]}]);
}

int main(){
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
        mm[{u, v}] = mm[{v, u}] = i;
    }

    h[1] = 0; memset(par, -1, sizeof(par));
    dfs(1, 1);
    makeLCA();
    init(1, 1, 2 * n);

    while (m--) {
        int num; scanf("%d", &num);
        for (int i = 1; i <= num; i++) scanf("%d", &queries[i]);
        //cout << st[queries[1]] << "\n";

        int lca = queries[1];
        for (int i = 2; i <= num; i++) lca = LCA(lca, queries[i]);
        pref[lca]--; pref[queries[1]]++;
        update(1, 1, 2 * n, st[queries[1]], 1);

        for (int j = 2; j <= num; j++) {
            int sum = 0;
            for (int i = 19; i >= 0; i--) {
                int cur = kthNode(sum + (1 << i), queries[j]);
                if (cur > 0 && get(1, 1, 2 * n, st[cur], en[cur]) == 0) sum += (1 << i);
            }

            int v = kthNode(sum, queries[j]);
            if (get(1, 1, 2 * n, st[v], en[v]) == 0) {
                pref[par[0][v]]--;
                pref[queries[j]]++;
            }

            update(1, 1, 2 * n, st[queries[j]], 1);
        }

        for (int j = 1; j <= num; j++) update(1, 1, 2 * n, st[queries[j]], -1);
    }

    redfs(1, 1);
    sort(ans.begin(), ans.end());
    printf("%d\n", (int)ans.size());
    for (int i: ans) printf("%d ", i);
    return 0;
}
