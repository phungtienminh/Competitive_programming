#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n, q, a[N], cur[N];
long long res[N], ans = 0;
vector <int> altitude[N];

struct Query {
    int val, id;
    bool operator < (const Query &rhs) const {
        return val < rhs.val;
    }
} queries[N];

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
        ans -= 1LL * sz[y] * (sz[y] + 1) / 2;
        ans -= 1LL * sz[x] * (sz[x] + 1) / 2;
        sz[x] += sz[y];
        ans += 1LL * sz[x] * (sz[x] + 1) / 2;
    }
} dsu;

int main(){
    scanf("%d %d", &n, &q); dsu.init(n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), altitude[a[i]].push_back(i);
    for (int i = 1; i <= q; i++) scanf("%d", &queries[i].val), queries[i].id = i;
    sort(queries + 1, queries + q + 1);

    int ptr = 1;
    for (int i = 1; i <= q; i++) {
        while (ptr <= queries[i].val) {
            while (cur[ptr] < altitude[ptr].size()) {
                //if (ptr == 2) cout << cur[ptr] << " " << ans << "\n";
                int id = altitude[ptr][cur[ptr]]; cur[ptr]++;
                ans++;
                if (id > 1 && a[id - 1] <= a[id]) dsu.join(id, id - 1);
                if (id < n && a[id + 1] <= a[id]) dsu.join(id, id + 1);
            }

            ptr++;
        }

        res[queries[i].id] = ans;
    }

    for (int i = 1; i <= q; i++) printf("%lld\n", res[i]);
    return 0;
}

