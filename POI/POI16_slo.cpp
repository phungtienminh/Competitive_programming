#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e6 + 5;

int par[N], sum[N], Min[N], a[N], b[N], w[N], sz[N], n;
int minw = 1e9;
bool loop[N];

void init (int n) {
    for (int i = 1; i <= n; ++i) {
        par[i] = i;
        sum[i] = Min[i] = w[i];
        sz[i] = 1;
    }
}

int Find (int x) {
    return (par[x] == x ? x : par[x] = Find(par[x]));
}

bool same (int x, int y) {
    return Find(x) == Find(y);
}

void join (int x, int y) {
    if (same(x, y)) return;

    sum[Find(x)] += sum[Find(y)];
    sz[Find(x)] += sz[Find(y)];
    Min[Find(x)] = min(Min[Find(x)], Min[Find(y)]);
    par[Find(y)] = Find(x);
}

void input(){
    scanf("%lld", &n);
    memset(loop, 0, sizeof(loop));
    for (int i = 1; i <= n; ++i) scanf("%lld", &w[i]);
    for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    for (int i = 1; i <= n; ++i) scanf("%lld", &b[i]);
    for (int i = 1; i <= n; ++i) minw = min(minw, w[i]);
}

void solve(){
    init(n);
    for (int i = 1; i <= n; ++i) join(a[i], b[i]);

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (!loop[Find(i)]) {
            loop[Find(i)] = true;
            if (sz[Find(i)] > 1) ans = ans + min(sum[Find(i)] + Min[Find(i)] * (sz[Find(i)] - 2), sum[Find(i)] - Min[Find(i)] + minw * (sz[Find(i)] - 1) + 2 * (minw + Min[Find(i)]));
        }
    }

    printf("%lld", ans);
}

signed main(){
    input();
    solve();
    return 0;
}

/*
10
3015 4728 4802 4361 135 4444 4313 1413 4581 546
3 10 1 8 9 4 2 7 6 5
4 9 5 3 1 6 10 7 8 2
*/
