#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

vector <int> g[N];
int h[N], st[N], en[N], pos[N], node[4 * N], n, m, q, u[N], v[N], res[N], last[N], state[N];
int cnt = 0;

void input(){
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= n - 1; i++) {
        scanf("%d %d", &u[i], &v[i]);
        g[u[i]].push_back(v[i]);
        g[v[i]].push_back(u[i]);
    }

    h[1] = 0;
    memset(state, 0, sizeof(state));
    memset(last, 0, sizeof(last));
    fill(res + 1, res + n + 1, 1);
}

void dfs (int u, int p) {
    st[u] = ++cnt;
    pos[st[u]] = u;

    for (int v: g[u]) {
        if (v == p) continue;

        h[v] = h[u] + 1;
        dfs(v, u);
    }

    en[u] = cnt;
}

void init (int i, int l, int r) {
    if (l > r) return;
    if (l == r) {
        node[i] = en[pos[l]];
        return;
    }

    int m = (l + r) >> 1;
    init(i << 1, l, m);
    init(i << 1 | 1, m + 1, r);

    node[i] = max(node[i << 1], node[i << 1 | 1]);
}

void update (int i, int l, int r, int p, int val) {
    if (l == r) {
        if (l == p) node[i] = val;
        return;
    }

    int m = (l + r) >> 1;
    if (p <= m) update(i << 1, l, m, p, val);
    else update(i << 1 | 1, m + 1, r, p, val);

    node[i] = max(node[i << 1], node[i << 1 | 1]);
}

int get (int i, int l, int r, int p, int val) {
    if (l > p || node[i] < val) return -1;
    if (l == r) return pos[l];

    int m = (l + r) >> 1;
    int res = get(i << 1 | 1, m + 1, r, p, val);
    if (res != -1) return res;
    return get(i << 1, l, m, p, val);
}

void solve(){
    while (m--) {
        int id;
        scanf("%d", &id);
        if (h[u[id]] > h[v[id]]) swap(u[id], v[id]);

        int root = get(1, 0, N, st[u[id]], en[u[id]]);
        if (!state[id]) {
            res[root] += res[v[id]] - last[v[id]];
            update(1, 0, N, st[v[id]], -1);
        }
        else {
            res[v[id]] = res[root];
            last[v[id]] = res[root];
            update(1, 0, N, st[v[id]], en[v[id]]);
        }

        state[id] ^= 1;
    }

    while (q--) {
        int x;
        scanf("%d", &x);
        printf("%d\n", res[get(1, 0, N, st[x], en[x])]);
    }
}

int main(){
    input();
    dfs(1, 1);
    init(1, 0, N);
    solve();
    return 0;
}
