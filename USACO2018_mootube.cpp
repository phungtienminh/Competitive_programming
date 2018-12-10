#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, q;
vector <pair <int, pair <int, int> > > edges;

struct Query {
    int k, u, id;
    Query (int k = 0, int u = 0, int id = 0): k(k), u(u), id(id) {}
    bool operator < (const Query &rhs) const {
        return k > rhs.k;
    }
};

vector <Query> queries;

struct disj {
    int par[N], sz[N];
    void init (int n) {
        iota(par + 1, par + n + 1, 1);
        for (int i = 1; i <= n; i++) sz[i] = 1;
    }

    int Find (int x) {
        return par[x] == x ? x : par[x] = Find(par[x]);
    }

    void join (int x, int y) {
        x = Find(x); y = Find(y);
        if (x == y) return;
        par[y] = x; sz[x] += sz[y];
    }
} dsu;

int ans[N];

int main(){
    #ifndef Futymy
        freopen("mootube.in", "r", stdin);
        freopen("mootube.out", "w", stdout);
    #endif // Futymy

    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges.push_back({w, {u, v}});
    }

    for (int i = 1; i <= q; i++) {
        int k, u;
        scanf("%d %d", &k, &u);
        queries.push_back(Query(k, u, i));
    }

    sort(queries.begin(), queries.end());
    sort(edges.begin(), edges.end(), greater <pair <int, pair <int, int> > >()); dsu.init(n);
    int ptr = 0;

    for (auto i: queries) {
        while (ptr < edges.size() && edges[ptr].first >= i.k) dsu.join(edges[ptr].second.first, edges[ptr].second.second), ptr++;
        ans[i.id] = dsu.sz[dsu.Find(i.u)];
    }

    for (int i = 1; i <= q; i++) printf("%d\n", ans[i] - 1);
    return 0;
}
