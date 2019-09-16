#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int sq = 320;

int n, a[N], cnt = 0, st[N], en[N], res[N], in[N], Time = 0;
map <int, int> mm;
vector <int> g[N], vec;

struct Query {
    int l, r, id;
    bool operator < (const Query &rhs) const {
        if (l / sq != rhs.l / sq) return l / sq < rhs.l / sq;
        return r < rhs.r;
    }
} queries[N];

struct FenwickTree {
    int bit[N];
    void init() {
        memset(bit, 0, sizeof(bit));
    }

    void update (int x, int val) {
        for (int i = x; i > 0; i -= i & -i) bit[i] += val;
    }

    int query (int x) {
        int ans = 0;
        for (int i = x; i < N; i += i & -i) ans += bit[i];
        return ans;
    }
} bit;

void dfs (int u, int p) {
    st[u] = ++Time;
    in[Time] = u;
    for (auto v: g[u]) {
        if (v == p) continue;
        dfs(v, u);
    }

    en[u] = Time;
}

int main(){
    #ifndef Futymy
        freopen("promote.in", "r", stdin);
        freopen("promote.out", "w", stdout);
    #endif // Futymy

    scanf("%d", &n); bit.init();
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), vec.push_back(a[i]);
    sort(vec.begin(), vec.end());
    for (auto i: vec) mm[i] = ++cnt;
    for (int i = 1; i <= n - 1; i++) {
        int v;
        scanf("%d", &v);
        g[i + 1].push_back(v);
        g[v].push_back(i + 1);
    }

    dfs(1, 1);
    for (int i = 1; i <= n; i++) queries[i] = {st[i], en[i], i};
    sort(queries + 1, queries + n + 1);

    int l = 0, r = 1;
    for (int i = 1; i <= n; i++) {
        while (r <= queries[i].r) {
            bit.update(mm[a[in[r]]], 1);
            r++;
        }

        while (l > queries[i].l) {
            l--;
            bit.update(mm[a[in[l]]], 1);
        }

        while (l < queries[i].l) {
            bit.update(mm[a[in[l]]], -1);
            l++;
        }

        while (r > queries[i].r + 1) {
            bit.update(mm[a[in[r - 1]]], -1);
            r--;
        }

        res[queries[i].id] = bit.query(mm[a[queries[i].id]] + 1);
    }

    for (int i = 1; i <= n; i++) printf("%d\n", res[i]);
    return 0;
}
