#include <bits/stdc++.h>

using namespace std;

const int N = 1005;
const int maxn = 1e4 + 5;

struct disj {
    int par[N], sz[N];
    void init (int n) {
        iota(par + 1, par + n + 1, 1);
        fill(sz + 1, sz + n + 1, 1);
    }

    int Find (int x) {
        return par[x] == x ? x : par[x] = Find(par[x]);
    }

    void join (int x, int y) {
        x = Find(x); y = Find(y);
        if (x == y) return;
        par[y] = x;
        sz[x] += sz[y];
    }
} dsu;

struct Query {
    int d, id;
    bool operator < (const Query &rhs) const {
        return d < rhs.d;
    }
} queries[maxn];

int n, q, a[N], b[N], ans[maxn], ptr[N];
vector <pair <double, int> > vec[N];

double dist (int x, int y, int x2, int y2) {
    return sqrt(1.0 * (x2 - x) * (x2 - x) + 1.0 * (y2 - y) * (y2 - y));
}

int main(){
    scanf("%d", &n); dsu.init(n);
    for (int i = 1; i <= n; i++) scanf("%d %d", &a[i], &b[i]);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (i != j) vec[i].push_back({dist(a[i], b[i], a[j], b[j]), j});
    for (int i = 1; i <= n; i++) sort(vec[i].begin(), vec[i].end());

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) scanf("%d", &queries[i].d), queries[i].id = i;
    sort(queries + 1, queries + q + 1);
    for (int i = 1; i <= q; i++) {
        for (int j = 1; j <= n; j++) {
            while (ptr[j] < vec[j].size() && vec[j][ptr[j]].first <= queries[i].d) {
                dsu.join(j, vec[j][ptr[j]].second);
                ptr[j]++;
            }
        }

        ans[queries[i].id] = dsu.sz[dsu.Find(1)];
    }

    for (int i = 1; i <= q; i++) printf("%d\n", n - ans[i]);
    return 0;
}
