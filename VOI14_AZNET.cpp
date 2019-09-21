#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

struct edge {
    int u, v, id;
    edge (int u = 0, int v = 0, int id = 0): u(u), v(v), id(id) {}
};

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
};

int t, n, m, a[N], b[N], ans = 2e9 + 2277;
vector <edge> edges[2];
vector <int> res;
pair <int, int> rev_ed[N * 10];

void solve (int x) {
    disj dsu; dsu.init(n);
    vector <int> choose;

    for (auto i: edges[1]) {
        if (dsu.same(i.u, i.v)) continue;
        dsu.join(i.u, i.v);
    }

    for (auto i: edges[0]) {
        if (dsu.same(i.u, i.v)) continue;
        dsu.join(i.u, i.v);
        choose.push_back(i.id);
    }

    dsu.init(n);
    for (auto i: choose) dsu.join(rev_ed[i].first, rev_ed[i].second);
    for (auto i: edges[0]) {
        if (choose.size() == x) break;
        if (dsu.same(i.u, i.v)) continue;
        dsu.join(i.u, i.v);
        choose.push_back(i.id);
    }

    for (auto i: edges[1]) {
        if (dsu.same(i.u, i.v)) continue;
        dsu.join(i.u, i.v);
        choose.push_back(i.id);
    }

    if (a[x] + b[n - 1 - x] < ans) {
        ans = a[x] + b[n - 1 - x];
        res = choose;
    }
}

int main(){
    scanf("%d", &t);
    while (t--) {
        for (int i = 0; i < 2; i++) edges[i].clear(); ans = 2e9 + 2277; res.clear();
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n - 1; i++) scanf("%d", &a[i]);
        for (int i = 1; i <= n - 1; i++) scanf("%d", &b[i]);
        for (int i = 1; i <= m; i++) {
            int u, v, type;
            scanf("%d %d %d", &u, &v, &type);
            edges[type - 1].push_back(edge(u, v, i));
            rev_ed[i] = {u, v};
        }

        int l = 0, r = 0;
        disj dsu; dsu.init(n);

        for (auto i: edges[1]) {
            if (dsu.same(i.u, i.v)) continue;
            dsu.join(i.u, i.v);
        }

        for (auto i: edges[0]) {
            if (dsu.same(i.u, i.v)) continue;
            dsu.join(i.u, i.v);
            l++;
        }

        dsu.init(n);
        for (auto i: edges[0]) {
            if (dsu.same(i.u, i.v)) continue;
            dsu.join(i.u, i.v);
            r++;
        }

        for (int i = l; i <= r; i++) solve(i);
        sort(res.begin(), res.end());
        for (auto i: res) printf("%d ", i);
        puts("");
    }
    return 0;
}
